/* basic */
#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

#include "tuner_nxp_tda18273.h"
#include "ifd_driver.h"
#include "../../../uboot/include/rtk_i2c_lib.h"


#define NO 0
#define YES 1
#define FUNCTION_SUCCESS 1
#define FUNCTION_ERROR 0

//UINT32  				g_tda18273_curr_freq=0;
//UINT32  				g_tda18273_curr_freq_search=0;
extern UINT8 g_tuner_bytenum, g_tuner_byte[9];

I2C_MODULE *pI2CModule_tda18273;
SYS_MODULE *pSYSModule_tda18273;

TUNER_ATV_VIDEO_MODE g_tda18273_video_mode;
TUNER_ATV_AUDIO_MODE g_tda18273_audio_mode;

#define TUNER_DEBUG_MSG(string, args...)

/**

@brief   TDA18273 tuner module builder

Use BuildTda18273Module() to build TDA18273 module, set all module function pointers with the corresponding functions,
and initialize module private variables.


@param [in]   ppTuner                      Pointer to TDA18273 tuner module pointer
@param [in]   pTunerModuleMemory           Pointer to an allocated tuner module memory
@param [in]   pBaseInterfaceModuleMemory   Pointer to an allocated base interface module memory
@param [in]   pI2cBridgeModuleMemory       Pointer to an allocated I2C bridge module memory
@param [in]   DeviceAddr                   TDA18273 I2C device address
@param [in]   CrystalFreqHz                TDA18273 crystal frequency in Hz
@param [in]   UnitNo                       TDA18273 unit number
@param [in]   IfOutputVppMode              TDA18273 IF output Vp-p mode


@note
	-# One should call BuildTda18273Module() to build TDA18273 module before using it.

*/
void
BuildTda18273Module(ATV_TUNER_MODULE **ppTuner,
	ATV_TUNER_MODULE *pTunerModuleMemory,
	SYS_MODULE *pSysModuleMemory,
	I2C_MODULE *pI2cModuleMemory,
	unsigned char DeviceAddr,
	unsigned long CrystalFreqHz,
	UINT32 RfFreqHz_Max,
	UINT32 RfFreqHz_Min,
	int UnitNo,
	int IfOutputVppMode)
{
       //printk("###Start BuildTda18273Module()###\n");
	   
	ATV_TUNER_MODULE *pTuner;
	TDA18273_EXTRA_MODULE *pExtra;

	// Set tuner module pointer.
	*ppTuner = pTunerModuleMemory;

	// Get tuner module.
	pTuner = *ppTuner;

	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Set tuner type.
	pTuner->TunerType = TUNER_LOW_IF;

	// Set tuner I2C device address.
	pTuner->DeviceAddr = DeviceAddr;

	// Set base interface module pointer and I2C bridge module pointer.
	pTuner->pSysModule = pSysModuleMemory;
	pTuner->pI2cModule = pI2cModuleMemory;

	// Initialize tuner parameter setting status.
	pTuner->IsRfFreqHzSet = NO;
	pTuner->RfFreqHz_Max=RfFreqHz_Max;
	pTuner->RfFreqHz_Min=RfFreqHz_Min;

	// Set tuner module manipulating function pointers.
	pTuner->GetTunerType  = tda18273_GetTunerType;
	pTuner->GetDeviceAddr = tda18273_GetDeviceAddr;

	pTuner->Initialize  = tda18273_Initialize;
	pTuner->SetRfFreqHz = tda18273_SetRfFreqHz;
	pTuner->GetRfFreqHz = tda18273_GetRfFreqHz;
	pTuner->SetRfFreqSearchHz = tda18273_SetRfFreqSearchHz;
	pTuner->GetRfFreqSearchHz = tda18273_GetRfFreqSearchHz;
	pTuner->SetRfFreqAfcHz = tda18273_SetRfFreqHz;

	pTuner->GetIfFreqHz = tda18273_GetIfFreqHz;
	pTuner->GeDiverRatio = tda18273_GetDiverRatio;
	pTuner->GetRatioInStepSize = tda18273_GetRatioInStepSize;
	pTuner->CheckBand = tda18273_CheckBand;

	pTuner->SetStandardMode = tda18273_SetStandardMode;
	pTuner->GetStandardMode = tda18273_GetStandardMode;
	
	// Initialize tuner extra module variables.
	pExtra->CrystalFreqHz              = CrystalFreqHz;
	pExtra->UnitNo                     = tmUnit0;//UnitNo;
	pExtra->IfOutputVppMode            = IfOutputVppMode;
	pExtra->IsPowerModeSet             = NO;

	// Set tuner extra module function pointers.
	pExtra->SetPowerMode             = tda18273_SetPowerMode;
	pExtra->GetPowerMode             = tda18273_GetPowerMode;

	//printk("###End BuildTda18273Module()###\n");
	
	return;
}


/**

@see   TUNER_FP_GET_TUNER_TYPE

*/
void
tda18273_GetTunerType(
	ATV_TUNER_MODULE *pTuner,
	UINT8 *pTunerType
	)
{
	// Get tuner type from tuner module.
	*pTunerType = pTuner->TunerType;


	return;
}





/**

@see   TUNER_FP_GET_DEVICE_ADDR

*/
void
tda18273_GetDeviceAddr(
	ATV_TUNER_MODULE *pTuner,
	UINT8 *pDeviceAddr
	)
{
	// Get tuner I2C device address from tuner module.
	*pDeviceAddr = pTuner->DeviceAddr;


	return;
}


/**

@see   TUNER_FP_INITIALIZE

*/
UINT8 tda18273_Initialize(ATV_TUNER_MODULE *pTuner)
{
       //printk("###Start tda18273_Initialize()###\n");
	   
	TDA18273_EXTRA_MODULE *pExtra;

	int UnitNo=0;
	tmbslFrontEndDependency_t  sSrvTunerFunc;

	pI2CModule_tda18273 = pTuner->pI2cModule;
	pSYSModule_tda18273 = pTuner->pSysModule;


	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = tmUnit0;//pExtra->UnitNo;

	pExtra->SetPowerMode(pTuner, 0);
	// Set user-defined function to tuner structure.
	sSrvTunerFunc.sIo.Write             = tda18273_Write;
	sSrvTunerFunc.sIo.Read              = tda18273_Read;
	sSrvTunerFunc.sTime.Get             = Null;
	sSrvTunerFunc.sTime.Wait            = tda18273_Wait;
	sSrvTunerFunc.sDebug.Print          = tda18273_Printf;
	sSrvTunerFunc.sMutex.Init           = Null;
	sSrvTunerFunc.sMutex.DeInit         = Null;
	sSrvTunerFunc.sMutex.Acquire        = Null;
	sSrvTunerFunc.sMutex.Release        = Null;
	sSrvTunerFunc.dwAdditionalDataSize  = 0;
	sSrvTunerFunc.pAdditionalData       = Null;

	// De-initialize tuner.
	// Note: 1. tmbslTDA18273DeInit() doesn't access hardware.
	//       2. Doesn't need to check tmbslTDA18273DeInit() return, because we will get error return when the module is
	//          un-initialized.
	tmbslTDA18273DeInit(UnitNo);

	// Initialize tuner.
	// Note: tmbslTDA18273Init() doesn't access hardware.
	if(tmbslTDA18273Init(UnitNo, &sSrvTunerFunc) != TM_OK)
		goto error_status_initialize_tuner;

	// Reset tuner.
	if(tmbslTDA18273Reset(UnitNo) != TM_OK)
		goto error_status_initialize_tuner;

       //printk("###End tda18273_Initialize()###\n");
	   
	return FUNCTION_SUCCESS;


error_status_initialize_tuner:
	return FUNCTION_ERROR;
}





/**

@see   TUNER_FP_SET_RF_FREQ_HZ

*/
UINT8
tda18273_SetRfFreqHz(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz
	)
{
       //printk("###tda18273_SetRfFreqHz()###\n");
	TDA18273_EXTRA_MODULE *pExtra;
	int UnitNo;
	int IfOutputVppMode;


	//g_tda18273_curr_freq = RfFreqHz;
	
	pTuner->RfFreqHz      = RfFreqHz;

	
	RfFreqHz = RfFreqHz*100;//Hz

	
	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = pExtra->UnitNo;

	// Get IF output Vp-p mode.
	IfOutputVppMode = pExtra->IfOutputVppMode;

	
	// Set tuner RF frequency.
	if(tmbslTDA18273SetRf(UnitNo, RfFreqHz/*, (UInt8)IfOutputVppMode*/) != TM_OK)
		goto error_status_set_tuner_rf_frequency;


	// Set tuner RF frequency parameter.
	pTuner->IsRfFreqHzSet = YES;


	return FUNCTION_SUCCESS;


error_status_set_tuner_rf_frequency:
	return FUNCTION_ERROR;
}





/**

@see   TUNER_FP_GET_RF_FREQ_HZ

*/
UINT8
tda18273_GetRfFreqHz(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pRfFreqHz
	)
{
		TDA18273_EXTRA_MODULE *pExtra;
		tmUnitSelect_t UnitNo;
		UInt32 freq=0;
	
	
	
		// Get tuner extra module.
		pExtra = &(pTuner->Extra.Tda18273);
	
		// Get unit number.
		UnitNo = pExtra->UnitNo;
	
	
		// Get tuner IF frequency in Hz.
		if(tmbslTDA18273_GetRF(UnitNo, &freq) != TM_OK)
			goto error_status_get_tuner_rf_frequency;
	
		*pRfFreqHz = freq/100;
		return FUNCTION_SUCCESS;
	
	
	error_status_get_tuner_rf_frequency:
		*pRfFreqHz = freq;
		return FUNCTION_ERROR;

}

/**

@see   TUNER_FP_SET_RF_FREQ_HZ

*/
UINT8
tda18273_SetRfFreqSearchHz(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz
	)
{
	TDA18273_EXTRA_MODULE *pExtra;
	int UnitNo;
	int IfOutputVppMode;


	//g_tda18273_curr_freq_search= RfFreqHz;
	
	pTuner->RfFreqHz      = RfFreqHz;

	
	RfFreqHz = RfFreqHz*100;//Hz

	
	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = pExtra->UnitNo;

	// Get IF output Vp-p mode.
	IfOutputVppMode = pExtra->IfOutputVppMode;

	
	// Set tuner RF frequency.
	if(tmbslTDA18273SetRf(UnitNo, RfFreqHz/*, (UInt8)IfOutputVppMode*/) != TM_OK)
		goto error_status_set_tuner_rf_frequency;


	// Set tuner RF frequency parameter.
	pTuner->IsRfFreqHzSet = YES;


	return FUNCTION_SUCCESS;


error_status_set_tuner_rf_frequency:
	return FUNCTION_ERROR;
}





/**

@see   TUNER_FP_GET_RF_FREQ_HZ

*/
UINT8
tda18273_GetRfFreqSearchHz(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pRfFreqHz
	)
{
		TDA18273_EXTRA_MODULE *pExtra;
		tmUnitSelect_t UnitNo;
		UInt32 freq=0;
	
	
	
		// Get tuner extra module.
		pExtra = &(pTuner->Extra.Tda18273);
	
		// Get unit number.
		UnitNo = pExtra->UnitNo;
	
	
		// Get tuner IF frequency in Hz.
		if(tmbslTDA18273_GetRF(UnitNo, &freq) != TM_OK)
			goto error_status_get_tuner_rf_frequency;
	
		*pRfFreqHz = freq/100;
		return FUNCTION_SUCCESS;
	
	
	error_status_get_tuner_rf_frequency:
		*pRfFreqHz = freq;
		return FUNCTION_ERROR;

}

/**

@brief   Set TDA18273 tuner standard and bandwidth mode.

*/
UINT8
tda18273_SetStandardMode(
	ATV_TUNER_MODULE *pTuner, 
	TUNER_ATV_VIDEO_MODE video_mode, 
	TUNER_ATV_AUDIO_MODE audio_mode
	)
{
	TDA18273_EXTRA_MODULE *pExtra;
	int UnitNo;
	TDA18273StandardMode_t StandardMode;

	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	//printk("%s %d\n",__FILE__, __LINE__);
	// Get unit number.
	UnitNo = pExtra->UnitNo;
	
	// Set tuner standard and bandwidth mode.
	switch(audio_mode)
	{
		case TUNER_ATV_AUDIO_MODE_MN:
			StandardMode=tmTDA18273_ANLG_MN;
			break;
		case TUNER_ATV_AUDIO_MODE_B:
			StandardMode=tmTDA18273_ANLG_B;
			break;
		case TUNER_ATV_AUDIO_MODE_GH:
			StandardMode=tmTDA18273_ANLG_GH;
			break;
		case TUNER_ATV_AUDIO_MODE_I:
			StandardMode=tmTDA18273_ANLG_I;
			break;
		case TUNER_ATV_AUDIO_MODE_DK:
			StandardMode=tmTDA18273_ANLG_DK;
			break;
		case TUNER_ATV_AUDIO_MODE_L:
			StandardMode=tmTDA18273_ANLG_L;
			break;
		case TUNER_ATV_AUDIO_MODE_LA:
			StandardMode=tmTDA18273_ANLG_LL;
			break;
		default:
			if(video_mode==TUNER_ATV_VIDEO_MODE_NTSC)
			{
				StandardMode=tmTDA18273_ANLG_MN;
			}
			else if(video_mode==TUNER_ATV_VIDEO_MODE_SECAM)
			{
				StandardMode=tmTDA18273_ANLG_L;
			}
			else if(video_mode==TUNER_ATV_VIDEO_MODE_SECAMLA)
			{
				StandardMode=tmTDA18273_ANLG_LL;
			}
			else if(video_mode==TUNER_ATV_VIDEO_MODE_SCAN)
			{
				StandardMode=tmTDA18273_Scanning;
			}
			else
			{
				StandardMode=tmTDA18273_ANLG_I;
			}
			break;
	}

	//printk("%s %d\n",__FILE__, __LINE__);
	// Set tuner standard and bandwidth mode.
	if(tmbslTDA18273SetStandardMode(UnitNo, StandardMode) != TM_OK)
		goto error_status_set_tuner_standard_mode;
	
	// Set tuner bandwidth mode parameter.
	pExtra->StandardMode      = StandardMode;
	pExtra->IsStandardModeSet = YES;

	g_tda18273_video_mode=video_mode;
	g_tda18273_audio_mode=audio_mode;
	
	return FUNCTION_SUCCESS;


error_status_set_tuner_standard_mode:
	return FUNCTION_ERROR;
}




/**

@brief   Get TDA18273 tuner standard and bandwidth mode.

*/
UINT8
tda18273_GetStandardMode(
	ATV_TUNER_MODULE *pTuner, 
	TUNER_ATV_VIDEO_MODE* video_mode, 
	TUNER_ATV_AUDIO_MODE* audio_mode
	)
{

	*video_mode = g_tda18273_video_mode;
	*audio_mode = g_tda18273_audio_mode;
			
	return FUNCTION_SUCCESS;


}




/**

@brief   Set TDA18273 tuner power mode.

*/
int
tda18273_SetPowerMode(
	ATV_TUNER_MODULE *pTuner,
	int PowerMode
	)
{
	TDA18273_EXTRA_MODULE *pExtra;
	int UnitNo;


	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = pExtra->UnitNo;


	// Set tuner power mode.
	if(tmbslTDA18273SetPowerState((tmUnitSelect_t)UnitNo, (TDA18273PowerState_t)PowerMode) != TM_OK)
		goto error_status_set_tuner_power_mode;


	// Set tuner power mode parameter.
	pExtra->PowerMode      = PowerMode;
	pExtra->IsPowerModeSet = YES;


	return FUNCTION_SUCCESS;


error_status_set_tuner_power_mode:
	return FUNCTION_ERROR;
}





/**

@brief   Get TDA18273 tuner power mode.

*/
int
tda18273_GetPowerMode(
	ATV_TUNER_MODULE *pTuner,
	int *pPowerMode
	)
{
	TDA18273_EXTRA_MODULE *pExtra;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);


	// Get tuner power mode from tuner module.
	if(pExtra->IsPowerModeSet != YES)
		goto error_status_get_tuner_power_mode;

	*pPowerMode = pExtra->PowerMode;


	return FUNCTION_SUCCESS;


error_status_get_tuner_power_mode:
	return FUNCTION_ERROR;
}




/*=============================================================*/
/**
	This routine will get divider ratio for specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 tda18273_GetDiverRatio(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT16 *DiverRatio)
{
	TDA18273_EXTRA_MODULE *pExtra;
	tmUnitSelect_t UnitNo;
	UInt32 freq=0;
	
	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = pExtra->UnitNo;
	
	tmbslTDA18273GetIF(UnitNo, &freq);
	*DiverRatio = (UINT16)((RfFreqHz + ((UINT32)freq/100)) / (UINT32)GET_ATV_TUNER_RATIOSTEPSIZE());
	return _TRUE;
}

/*=============================================================*/
/**
	This routine will check tuner receiving frequency band(VHF Low¡BVHF High¡BUHF).
	@param 			freq	       					tuner receiving frequency(divider)
	@return 			Return tuner receiving frequency band(01¡B02 or 04)
*/
UINT8 tda18273_CheckBand(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT8 *Band)
{
	UINT8 i;
	UINT8 tunerBANDno;

	tunerBANDno = GET_ATV_TUNER_BANDNO();

	for (i=0; i<tunerBANDno; ) 
	{
		if (RfFreqHz <= GET_ATV_TUNER_BANDFREQ(i))
		{
			*Band = i;
			return _TRUE;
		}
		i++;
	}
	*Band = tunerBANDno-1;
	
	return _FALSE;
}
/*=============================================================*/
UINT8 tda18273_GetRatioInStepSize(ATV_TUNER_MODULE *pTuner, UINT16 *RatioInStepSize)
{
	*RatioInStepSize = GET_ATV_TUNER_RATIOSTEPSIZE();

	return _TRUE;
}
/**

@brief   Get TDA18273 tuner IF frequency in Hz.

*/
UINT8
tda18273_GetIfFreqHz(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pIfFreqHz
	)
{
	TDA18273_EXTRA_MODULE *pExtra;
	tmUnitSelect_t UnitNo;
	UInt32 freq=0;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Tda18273);

	// Get unit number.
	UnitNo = pExtra->UnitNo;


	// Get tuner IF frequency in Hz.
	if(tmbslTDA18273GetIF(UnitNo, &freq) != TM_OK)
		goto error_status_get_tuner_if_frequency;

	*pIfFreqHz = freq/100;
	return FUNCTION_SUCCESS;


error_status_get_tuner_if_frequency:
	*pIfFreqHz = freq;
	return FUNCTION_ERROR;
}


// The following context is implemented for TDA18273 source code.


// Read TDA18273 registers.
tmErrorCode_t
tda18273_Read(
	tmUnitSelect_t tUnit,
	UInt32 AddrSize,
	UInt8* pAddr,
	UInt32 ReadLen,
	UInt8* pData
	)
{
	unsigned long i;
	
	#if 0
	// Set tuner register reading address.
	// Note: The I2C format of tuner register reading address setting is as follows:
	//       start_bit + (DeviceAddr | writing_bit) + addr * N + stop_bit
	if(pI2cBridge->ForwardI2cWritingCmd(pI2cBridge, pAddr, (unsigned char)AddrSize) != FUNCTION_SUCCESS)
		goto error_status_set_tuner_register_reading_address;

	// Get tuner register byte.
	// Note: The I2C format of tuner register byte getting is as follows:
	//       start_bit + (DeviceAddr | reading_bit) + read_data * N + stop_bit
	if(pI2cBridge->ForwardI2cReadingCmd(pI2cBridge, pData, (unsigned char)ReadLen) != FUNCTION_SUCCESS)
		goto error_status_get_tuner_registers;
	#else

	pI2CModule_tda18273->device_id=0xc0;
	pI2CModule_tda18273->slave_addr = pAddr[0];
	pI2CModule_tda18273->len = ReadLen;
	pI2CModule_tda18273->addrtype = 1;
	if(AddrSize>1) 
	{
		for(i = 1; i < AddrSize; i++)
		{
			pI2CModule_tda18273->slave_addr= pI2CModule_tda18273->slave_addr<<8;
			pI2CModule_tda18273->slave_addr |= pAddr[1];
		}
	}

	if(pI2CModule_tda18273->i2c_read(pI2CModule_tda18273, pData)==_FALSE)
		goto error_status_get_tuner_registers;

	#endif

	return TM_OK;


error_status_get_tuner_registers:


	return TM_ERR_READ;
}





// Write TDA18273 registers.
tmErrorCode_t
tda18273_Write(
	tmUnitSelect_t tUnit,
	UInt32 AddrSize,
	UInt8* pAddr,
	UInt32 WriteLen,
	UInt8* pData
	)
{
	unsigned long i;
	unsigned char WritingByteNum;

	// Calculate writing byte number.
	WritingByteNum = (unsigned char)(AddrSize + WriteLen);


	// Set writing bytes.
	// Note: The I2C format of tuner register byte setting is as follows:
	//       start_bit + (DeviceAddr | writing_bit) + addr * N + data * N + stop_bit

	#if 0
	// Set tuner register bytes with writing buffer.
	if(pI2cBridge->ForwardI2cWritingCmd(pI2cBridge, WritingBuffer, WritingByteNum) != FUNCTION_SUCCESS)
		goto error_status_set_tuner_registers;
	#else
	pI2CModule_tda18273->device_id=0xc0;
	pI2CModule_tda18273->slave_addr = pAddr[0];
	pI2CModule_tda18273->len = WriteLen;
	pI2CModule_tda18273->addrtype = 1;


	if(AddrSize>1) 
	{
		for(i = 1; i < AddrSize; i++)
		{
			pI2CModule_tda18273->slave_addr= pI2CModule_tda18273->slave_addr<<8;
			pI2CModule_tda18273->slave_addr |= pAddr[1];
		}
	}
	
	if(pI2CModule_tda18273->i2c_write(pI2CModule_tda18273, pData)==_FALSE)
		goto error_status_set_tuner_registers;
	#endif


	return TM_OK;


error_status_set_tuner_registers:
	return TM_ERR_WRITE;
}





// Wait a time.
tmErrorCode_t
tda18273_Wait(
	tmUnitSelect_t tUnit,
	UInt32 tms
	)
{

	// Wait a time.
	pSYSModule_tda18273->timer_delay_ms(tms);


	return TM_OK;
}
tmErrorCode_t
tda18273_Printf(UInt32 level, /*const*/ char* format, ...)
{

	IFD_DEBUG_MSG(IFD_MSG_TUNER, format); 
	IFD_DEBUG_MSG(IFD_MSG_TUNER, "\n"); 
	
	return TM_OK;
}





TDA18273StdCoefficients  /*IFD_CODE*/ gTDA18273Instance_Std_Array[TDA18273_StandardMode_Max-1] =
{
	TDA18273_INSTANCE_CUSTOM_STD_DEF,
};




// The following context is source code provided by NXP.




// NXP source code - .\tmbslTDA18273\src\tmbslTDA18273_RegDef.c
/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18273_RegDef.c
 *
 *                %version: 3 %
 *
 * \date          %modify_time%
 *
 * \author        Christophe CAZETTES
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18273_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
*/

/* File generated automatically from register description file */


/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#if 0
#include "tmNxTypes.h"
#include "tmNxCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#endif
/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#if 0
#include "tmbslTDA18273.h"
#include "tmbslTDA18273_RegDef.h"
#endif
/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/* TDA18273 Register ID_byte_1 0x00 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_1 = { 0x00, 0x00, 0x08, 0x00 };
/* MS bit(s): Indicate if Device is a Master or a Slave */
/*  1 => Master device */
/*  0 => Slave device */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_1__MS = { 0x00, 0x07, 0x01, 0x00 };
/* Ident_1 bit(s): MSB of device identifier */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_1__Ident_1 = { 0x00, 0x00, 0x07, 0x00 };


/* TDA18273 Register ID_byte_2 0x01 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_2 = { 0x01, 0x00, 0x08, 0x00 };
/* Ident_2 bit(s): LSB of device identifier */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_2__Ident_2 = { 0x01, 0x00, 0x08, 0x00 };


/* TDA18273 Register ID_byte_3 0x02 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_3 = { 0x02, 0x00, 0x08, 0x00 };
/* Major_rev bit(s): Major revision of device */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_3__Major_rev = { 0x02, 0x04, 0x04, 0x00 };
/* Major_rev bit(s): Minor revision of device */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_ID_byte_3__Minor_rev = { 0x02, 0x00, 0x04, 0x00 };


/* TDA18273 Register Thermo_byte_1 0x03 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Thermo_byte_1 = { 0x03, 0x00, 0x08, 0x00 };
/* TM_D bit(s): Device temperature */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Thermo_byte_1__TM_D = { 0x03, 0x00, 0x07, 0x00 };


/* TDA18273 Register Thermo_byte_2 0x04 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Thermo_byte_2 = { 0x04, 0x00, 0x08, 0x00 };
/* TM_ON bit(s): Set device temperature measurement to ON or OFF */
/*  1 => Temperature measurement ON */
/*  0 => Temperature measurement OFF */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Thermo_byte_2__TM_ON = { 0x04, 0x00, 0x01, 0x00 };


/* TDA18273 Register Power_state_byte_1 0x05 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_Power_state_byte_1 = { 0x05, 0x00, 0x08, 0x00 };
/* POR bit(s): Indicates that device just powered ON */
/*  1 => POR: No access done to device */
/*  0 => At least one access has been done to device */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_1__POR = { 0x05, 0x07, 0x01, 0x00 };
/* AGCs_Lock bit(s): Indicates that AGCs are locked */
/*  1 => AGCs locked */
/*  0 => AGCs not locked */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_1__AGCs_Lock = { 0x05, 0x02, 0x01, 0x00 };
/* Vsync_Lock bit(s): Indicates that VSync is locked */
/*  1 => VSync locked */
/*  0 => VSync not locked */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_1__Vsync_Lock = { 0x05, 0x01, 0x01, 0x00 };
/* LO_Lock bit(s): Indicates that LO is locked */
/*  1 => LO locked */
/*  0 => LO not locked */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_1__LO_Lock = { 0x05, 0x00, 0x01, 0x00 };


/* TDA18273 Register Power_state_byte_2 0x06 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_2 = { 0x06, 0x00, 0x08, 0x00 };
/* SM bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_2__SM = { 0x06, 0x01, 0x01, 0x00 };
/* SM_XT bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_state_byte_2__SM_XT = { 0x06, 0x00, 0x01, 0x00 };


/* TDA18273 Register Input_Power_Level_byte 0x07 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Input_Power_Level_byte = { 0x07, 0x00, 0x08, 0x00 };
/* Power_Level bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Input_Power_Level_byte__Power_Level = { 0x07, 0x00, 0x08, 0x00 };


/* TDA18273 Register IRQ_status 0x08 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status = { 0x08, 0x00, 0x08, 0x00 };
/* IRQ_status bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__IRQ_status = { 0x08, 0x07, 0x01, 0x00 };
/* MSM_XtalCal_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_XtalCal_End = { 0x08, 0x05, 0x01, 0x00 };
/* MSM_RSSI_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_RSSI_End = { 0x08, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_LOCalc_End = { 0x08, 0x03, 0x01, 0x00 };
/* MSM_RFCal_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_RFCal_End = { 0x08, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_IRCAL_End = { 0x08, 0x01, 0x01, 0x00 };
/* MSM_RCCal_End bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_status__MSM_RCCal_End = { 0x08, 0x00, 0x01, 0x00 };


/* TDA18273 Register IRQ_enable 0x09 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable = { 0x09, 0x00, 0x08, 0x00 };
/* IRQ_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__IRQ_Enable = { 0x09, 0x07, 0x01, 0x00 };
/* MSM_XtalCal_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_XtalCal_Enable = { 0x09, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_RSSI_Enable = { 0x09, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_LOCalc_Enable = { 0x09, 0x03, 0x01, 0x00 };
/* MSM_RFCal_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_RFCal_Enable = { 0x09, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_IRCAL_Enable = { 0x09, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_enable__MSM_RCCal_Enable = { 0x09, 0x00, 0x01, 0x00 };


/* TDA18273 Register IRQ_clear 0x0A */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear = { 0x0A, 0x00, 0x08, 0x00 };
/* IRQ_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__IRQ_Clear = { 0x0A, 0x07, 0x01, 0x00 };
/* MSM_XtalCal_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_XtalCal_Clear = { 0x0A, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_RSSI_Clear = { 0x0A, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_LOCalc_Clear = { 0x0A, 0x03, 0x01, 0x00 };
/* MSM_RFCal_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_RFCal_Clear = { 0x0A, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_IRCAL_Clear = { 0x0A, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Clear bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_clear__MSM_RCCal_Clear = { 0x0A, 0x00, 0x01, 0x00 };


/* TDA18273 Register IRQ_set 0x0B */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set = { 0x0B, 0x00, 0x08, 0x00 };
/* IRQ_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__IRQ_Set = { 0x0B, 0x07, 0x01, 0x00 };
/* MSM_XtalCal_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_XtalCal_Set = { 0x0B, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_RSSI_Set = { 0x0B, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_LOCalc_Set = { 0x0B, 0x03, 0x01, 0x00 };
/* MSM_RFCal_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_RFCal_Set = { 0x0B, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_IRCAL_Set = { 0x0B, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Set bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IRQ_set__MSM_RCCal_Set = { 0x0B, 0x00, 0x01, 0x00 };


/* TDA18273 Register AGC1_byte_1 0x0C */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_AGC1_byte_1 = { 0x0C, 0x00, 0x08, 0x00 };
/* AGC1_TOP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_1__AGC1_TOP = { 0x0C, 0x00, 0x04, 0x00 };


/* TDA18273 Register AGC1_byte_2 0x0D */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_2 = { 0x0D, 0x00, 0x08, 0x00 };
/* AGC1_Top_Mode_Val bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode_Val = { 0x0D, 0x03, 0x02, 0x00 };
/* AGC1_Top_Mode bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode = { 0x0D, 0x00, 0x03, 0x00 };


/* TDA18273 Register AGC2_byte_1 0x0E */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_AGC2_byte_1 = { 0x0E, 0x00, 0x08, 0x00 };
/* AGC2_TOP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC2_byte_1__AGC2_TOP = { 0x0E, 0x00, 0x03, 0x00 };


/* TDA18273 Register AGCK_byte_1 0x0F */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCK_byte_1 = { 0x0F, 0x00, 0x08, 0x00 };
/* AGCs_Up_Step_assym bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCK_byte_1__AGCs_Up_Step_assym = { 0x0F, 0x06, 0x02, 0x00 };
/* Pulse_Shaper_Disable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCK_byte_1__Pulse_Shaper_Disable = { 0x0F, 0x04, 0x01, 0x00 };
/* AGCK_Step bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCK_byte_1__AGCK_Step = { 0x0F, 0x02, 0x02, 0x00 };
/* AGCK_Mode bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCK_byte_1__AGCK_Mode = { 0x0F, 0x00, 0x02, 0x00 };


/* TDA18273 Register RF_AGC_byte 0x10 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_AGC_byte = { 0x10, 0x00, 0x08, 0x00 };
/* PD_AGC_Adapt3x bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_AGC_byte__PD_AGC_Adapt3x = { 0x10, 0x06, 0x02, 0x00 };
/* RFAGC_Adapt_TOP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_AGC_byte__RFAGC_Adapt_TOP = { 0x10, 0x04, 0x02, 0x00 };
/* RFAGC_Low_BW bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_AGC_byte__RFAGC_Low_BW = { 0x10, 0x03, 0x01, 0x00 };
/* RFAGC_Top bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_AGC_byte__RFAGC_Top = { 0x10, 0x00, 0x03, 0x00 };


/* TDA18273 Register W_Filter_byte 0x11 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte = { 0x11, 0x00, 0x08, 0x00 };
/* VHF_III_mode bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__VHF_III_mode = { 0x11, 0x07, 0x01, 0x00 };
/* RF_Atten_3dB bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__RF_Atten_3dB = { 0x11, 0x06, 0x01, 0x00 };
/* W_Filter_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__W_Filter_Enable = { 0x11, 0x05, 0x01, 0x00 };
/* W_Filter_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__W_Filter_Bypass = { 0x11, 0x04, 0x01, 0x00 };
/* W_Filter bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__W_Filter = { 0x11, 0x02, 0x02, 0x00 };
/* W_Filter_Offset bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_W_Filter_byte__W_Filter_Offset = { 0x11, 0x00, 0x02, 0x00 };


/* TDA18273 Register IR_Mixer_byte_1 0x12 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_1 = { 0x12, 0x00, 0x08, 0x00 };
/* S2D_Gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_1__S2D_Gain = { 0x12, 0x04, 0x02, 0x00 };
/* IR_Mixer_Top bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_1__IR_Mixer_Top = { 0x12, 0x00, 0x04, 0x00 };


/* TDA18273 Register AGC5_byte_1 0x13 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_1 = { 0x13, 0x00, 0x08, 0x00 };
/* AGCs_Do_Step_assym bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_1__AGCs_Do_Step_assym = { 0x13, 0x05, 0x02, 0x00 };
/* AGC5_Ana bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_1__AGC5_Ana = { 0x13, 0x04, 0x01, 0x00 };
/* AGC5_TOP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_1__AGC5_TOP = { 0x13, 0x00, 0x04, 0x00 };


/* TDA18273 Register IF_AGC_byte 0x14 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_AGC_byte = { 0x14, 0x00, 0x08, 0x00 };
/* IFnotchToRSSI bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_AGC_byte__IFnotchToRSSI = { 0x14, 0x07, 0x01, 0x00 };
/* LPF_DCOffset_Corr bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_AGC_byte__LPF_DCOffset_Corr = { 0x14, 0x06, 0x01, 0x00 };
/* IF_level bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_AGC_byte__IF_level = { 0x14, 0x00, 0x03, 0x00 };


/* TDA18273 Register IF_Byte_1 0x15 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_Byte_1 = { 0x15, 0x00, 0x08, 0x00 };
/* IF_HP_Fc bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_Byte_1__IF_HP_Fc = { 0x15, 0x06, 0x02, 0x00 };
/* IF_ATSC_Notch bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_Byte_1__IF_ATSC_Notch = { 0x15, 0x05, 0x01, 0x00 };
/* LP_FC_Offset bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_Byte_1__LP_FC_Offset = { 0x15, 0x03, 0x02, 0x00 };
/* LP_Fc bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_IF_Byte_1__LP_Fc = { 0x15, 0x00, 0x03, 0x00 };


/* TDA18273 Register Reference_Byte 0x16 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Reference_Byte = { 0x16, 0x00, 0x08, 0x00 };
/* Digital_Clock_Mode bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode = { 0x16, 0x06, 0x02, 0x00 };
/* XTout bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Reference_Byte__XTout = { 0x16, 0x00, 0x02, 0x00 };


/* TDA18273 Register IF_Frequency_byte 0x17 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IF_Frequency_byte = { 0x17, 0x00, 0x08, 0x00 };
/* IF_Freq bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_IF_Frequency_byte__IF_Freq = { 0x17, 0x00, 0x08, 0x00 };


/* TDA18273 Register RF_Frequency_byte_1 0x18 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_1 = { 0x18, 0x00, 0x08, 0x00 };
/* RF_Freq_1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_1__RF_Freq_1 = { 0x18, 0x00, 0x04, 0x00 };


/* TDA18273 Register RF_Frequency_byte_2 0x19 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_2 = { 0x19, 0x00, 0x08, 0x00 };
/* RF_Freq_2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_2__RF_Freq_2 = { 0x19, 0x00, 0x08, 0x00 };


/* TDA18273 Register RF_Frequency_byte_3 0x1A */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_3 = { 0x1A, 0x00, 0x08, 0x00 };
/* RF_Freq_3 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Frequency_byte_3__RF_Freq_3 = { 0x1A, 0x00, 0x08, 0x00 };


/* TDA18273 Register MSM_byte_1 0x1B */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1 = { 0x1B, 0x00, 0x08, 0x00 };
/* RSSI_Meas bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__RSSI_Meas = { 0x1B, 0x07, 0x01, 0x00 };
/* RF_CAL_AV bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__RF_CAL_AV = { 0x1B, 0x06, 0x01, 0x00 };
/* RF_CAL bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__RF_CAL = { 0x1B, 0x05, 0x01, 0x00 };
/* IR_CAL_Loop bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__IR_CAL_Loop = { 0x1B, 0x04, 0x01, 0x00 };
/* IR_Cal_Image bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__IR_Cal_Image = { 0x1B, 0x03, 0x01, 0x00 };
/* IR_CAL_Wanted bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_MSM_byte_1__IR_CAL_Wanted = { 0x1B, 0x02, 0x01, 0x00 };
/* RC_Cal bit(s):  */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/gTDA18273_Reg_MSM_byte_1__RC_Cal = { 0x1B, 0x01, 0x01, 0x00 };
/* Calc_PLL bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_1__Calc_PLL = { 0x1B, 0x00, 0x01, 0x00 };


/* TDA18273 Register MSM_byte_2 0x1C */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_MSM_byte_2 = { 0x1C, 0x00, 0x08, 0x00 };
/* XtalCal_Launch bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_MSM_byte_2__XtalCal_Launch = { 0x1C, 0x01, 0x01, 0x00 };
/* MSM_Launch bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_MSM_byte_2__MSM_Launch = { 0x1C, 0x00, 0x01, 0x00 };


/* TDA18273 Register PowerSavingMode 0x1D */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode = { 0x1D, 0x00, 0x08, 0x00 };
/* PSM_AGC1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_AGC1 = { 0x1D, 0x07, 0x01, 0x00 };
/* PSM_Bandsplit_Filter bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_Bandsplit_Filter = { 0x1D, 0x05, 0x02, 0x00 };
/* PSM_RFpoly bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_RFpoly = { 0x1D, 0x04, 0x01, 0x00 };
/* PSM_Mixer bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_Mixer = { 0x1D, 0x03, 0x01, 0x00 };
/* PSM_Ifpoly bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_Ifpoly = { 0x1D, 0x02, 0x01, 0x00 };
/* PSM_Lodriver bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_PowerSavingMode__PSM_Lodriver = { 0x1D, 0x00, 0x02, 0x00 };


/* TDA18273 Register Power_Level_byte_2 0x1E */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Level_byte_2 = { 0x1E, 0x00, 0x08, 0x00 };
/* PD_PLD_read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Level_byte_2__PD_PLD_read = { 0x1E, 0x07, 0x01, 0x00 };
/* IR_Target bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Level_byte_2__PLD_Temp_Slope = { 0x1E, 0x05, 0x02, 0x00 };
/* IR_GStep bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Level_byte_2__PLD_Gain_Corr = { 0x1E, 0x00, 0x05, 0x00 };


/* TDA18273 Register Adapt_Top_byte 0x1F */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Adapt_Top_byte = { 0x1F, 0x00, 0x08, 0x00 };
/* Fast_Mode_AGC bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Adapt_Top_byte__Fast_Mode_AGC = { 0x1F, 0x06, 0x01, 0x00 };
/* Range_LNA_Adapt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_Adapt_Top_byte__Range_LNA_Adapt = { 0x1F, 0x05, 0x01, 0x00 };
/* Index_K_LNA_Adapt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Adapt_Top_byte__Index_K_LNA_Adapt = { 0x1F, 0x03, 0x02, 0x00 };
/* Index_K_Top_Adapt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Adapt_Top_byte__Index_K_Top_Adapt = { 0x1F, 0x01, 0x02, 0x00 };
/* Ovld_Udld_FastUp bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Adapt_Top_byte__Ovld_Udld_FastUp = { 0x1F, 0x00, 0x01, 0x00 };


/* TDA18273 Register Vsync_byte 0x20 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte = { 0x20, 0x00, 0x08, 0x00 };
/* Neg_modulation bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte__Neg_modulation = { 0x20, 0x07, 0x01, 0x00 };
/* Tracer_Step bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte__Tracer_Step = { 0x20, 0x05, 0x02, 0x00 };
/* Vsync_int bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte__Vsync_int = { 0x20, 0x04, 0x01, 0x00 };
/* Vsync_Thresh bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte__Vsync_Thresh = { 0x20, 0x02, 0x02, 0x00 };
/* Vsync_Len bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_byte__Vsync_Len = { 0x20, 0x00, 0x02, 0x00 };


/* TDA18273 Register Vsync_Mgt_byte 0x21 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte = { 0x21, 0x00, 0x08, 0x00 };
/* PD_Vsync_Mgt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__PD_Vsync_Mgt = { 0x21, 0x07, 0x01, 0x00 };
/* PD_Ovld bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__PD_Ovld = { 0x21, 0x06, 0x01, 0x00 };
/* PD_Ovld_RF bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__PD_Ovld_RF = { 0x21, 0x05, 0x01, 0x00 };
/* AGC_Ovld_TOP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__AGC_Ovld_TOP = { 0x21, 0x02, 0x03, 0x00 };
/* Up_Step_Ovld bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__Up_Step_Ovld = { 0x21, 0x01, 0x01, 0x00 };
/* AGC_Ovld_Timer bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Vsync_Mgt_byte__AGC_Ovld_Timer = { 0x21, 0x00, 0x01, 0x00 };


/* TDA18273 Register IR_Mixer_byte_2 0x22 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_2 = { 0x22, 0x00, 0x08, 0x00 };
/* IR_Mixer_loop_off bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_2__IR_Mixer_loop_off = { 0x22, 0x07, 0x01, 0x00 };
/* IR_Mixer_Do_step bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_2__IR_Mixer_Do_step = { 0x22, 0x05, 0x02, 0x00 };
/* Hi_Pass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_2__Hi_Pass = { 0x22, 0x01, 0x01, 0x00 };
/* IF_Notch bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Mixer_byte_2__IF_Notch = { 0x22, 0x00, 0x01, 0x00 };


/* TDA18273 Register AGC1_byte_3 0x23 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_3 = { 0x23, 0x00, 0x08, 0x00 };
/* AGC1_loop_off bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_3__AGC1_loop_off = { 0x23, 0x07, 0x01, 0x00 };
/* AGC1_Do_step bit(s):  */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_3__AGC1_Do_step = { 0x23, 0x05, 0x02, 0x00 };
/* Force_AGC1_gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain = { 0x23, 0x04, 0x01, 0x00 };
/* AGC1_Gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC1_byte_3__AGC1_Gain = { 0x23, 0x00, 0x04, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_1 0x24 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1 = { 0x24, 0x00, 0x08, 0x00 };
/* PLD_DAC_Scale bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_DAC_Scale = { 0x24, 0x07, 0x01, 0x00 };
/* PLD_CC_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable = { 0x24, 0x06, 0x01, 0x00 };
/* PLD_Temp_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_Temp_Enable = { 0x24, 0x05, 0x01, 0x00 };
/* TH_AGC_Adapt34 bit(s):  */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1__TH_AGC_Adapt34 = { 0x24, 0x04, 0x01, 0x00 };
/* RFAGC_Sense_Enable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1__RFAGC_Sense_Enable = { 0x24, 0x02, 0x01, 0x00 };
/* RFAGC_K_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1__RFAGC_K_Bypass = { 0x24, 0x01, 0x01, 0x00 };
/* RFAGC_K_8 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_1__RFAGC_K_8 = { 0x24, 0x00, 0x01, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_2 0x25 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_2 = { 0x25, 0x00, 0x08, 0x00 };
/* RFAGC_K bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_2__RFAGC_K = { 0x25, 0x00, 0x08, 0x00 };


/* TDA18273 Register AGC5_byte_2 0x26 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_2 = { 0x26, 0x00, 0x08, 0x00 };
/* AGC5_loop_off bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_2__AGC5_loop_off = { 0x26, 0x07, 0x01, 0x00 };
/* AGC5_Do_step bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_2__AGC5_Do_step = { 0x26, 0x05, 0x02, 0x00 };
/* Force_AGC5_gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_2__Force_AGC5_gain = { 0x26, 0x03, 0x01, 0x00 };
/* AGC5_Gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGC5_byte_2__AGC5_Gain = { 0x26, 0x00, 0x03, 0x00 };


/* TDA18273 Register RF_Cal_byte_1 0x27 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_1 = { 0x27, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog0 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog0 = { 0x27, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog1 bit(s):  */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog1 = { 0x27, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog2 = { 0x27, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog3 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog3 = { 0x27, 0x00, 0x02, 0x00 };


/* TDA18273 Register RF_Cal_byte_2 0x28 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_2 = { 0x28, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog4 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog4 = { 0x28, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog5 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog5 = { 0x28, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog6 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog6 = { 0x28, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog7 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog7 = { 0x28, 0x00, 0x02, 0x00 };


/* TDA18273 Register RF_Cal_byte_3 0x29 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RF_Cal_byte_3 = { 0x29, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog8 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog8 = { 0x29, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog9 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog9 = { 0x29, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog10 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog10 = { 0x29, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog11 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog11 = { 0x29, 0x00, 0x02, 0x00 };


/* TDA18273 Register Bandsplit_Filter_byte 0x2A */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Bandsplit_Filter_byte = { 0x2A, 0x00, 0x08, 0x00 };
/* Bandsplit_Filter_SubBand bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Bandsplit_Filter_byte__Bandsplit_Filter_SubBand = { 0x2A, 0x00, 0x02, 0x00 };


/* TDA18273 Register RF_Filters_byte_1 0x2B */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1 = { 0x2B, 0x00, 0x08, 0x00 };
/* RF_Filter_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Bypass = { 0x2B, 0x07, 0x01, 0x00 };
/* AGC2_loop_off bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off = { 0x2B, 0x05, 0x01, 0x00 };
/* Force_AGC2_gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain = { 0x2B, 0x04, 0x01, 0x00 };
/* RF_Filter_Gv bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Gv = { 0x2B, 0x02, 0x02, 0x00 };
/* RF_Filter_Band bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Band = { 0x2B, 0x00, 0x02, 0x00 };


/* TDA18273 Register RF_Filters_byte_2 0x2C */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RF_Filters_byte_2 = { 0x2C, 0x00, 0x08, 0x00 };
/* RF_Filter_Cap bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_2__RF_Filter_Cap = { 0x2C, 0x00, 0x08, 0x00 };


/* TDA18273 Register RF_Filters_byte_3 0x2D */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_3 = { 0x2D, 0x00, 0x08, 0x00 };
/* AGC2_Do_step bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_3__AGC2_Do_step = { 0x2D, 0x06, 0x02, 0x00 };
/* Gain_Taper bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Filters_byte_3__Gain_Taper = { 0x2D, 0x00, 0x06, 0x00 };


/* TDA18273 Register RF_Band_Pass_Filter_byte 0x2E */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Band_Pass_Filter_byte = { 0x2E, 0x00, 0x08, 0x00 };
/* RF_BPF_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RF_Band_Pass_Filter_byte__RF_BPF_Bypass = { 0x2E, 0x07, 0x01, 0x00 };
/* RF_BPF bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RF_Band_Pass_Filter_byte__RF_BPF = { 0x2E, 0x00, 0x03, 0x00 };


/* TDA18273 Register CP_Current_byte 0x2F */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_CP_Current_byte = { 0x2F, 0x00, 0x08, 0x00 };
/* LO_CP_Current bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_CP_Current_byte__LO_CP_Current = { 0x2F, 0x07, 0x01, 0x00 };
/* N_CP_Current bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_CP_Current_byte__N_CP_Current = { 0x2F, 0x00, 0x07, 0x00 };


/* TDA18273 Register AGCs_DetOut_byte 0x30 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte = { 0x30, 0x00, 0x08, 0x00 };
/* Up_AGC5 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_AGCs_DetOut_byte__Up_AGC5 = { 0x30, 0x07, 0x01, 0x00 };
/* Do_AGC5 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Do_AGC5 = { 0x30, 0x06, 0x01, 0x00 };
/* Up_AGC4 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_AGCs_DetOut_byte__Up_AGC4 = { 0x30, 0x05, 0x01, 0x00 };
/* Do_AGC4 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Do_AGC4 = { 0x30, 0x04, 0x01, 0x00 };
/* Up_AGC2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Up_AGC2 = { 0x30, 0x03, 0x01, 0x00 };
/* Do_AGC2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Do_AGC2 = { 0x30, 0x02, 0x01, 0x00 };
/* Up_AGC1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Up_AGC1 = { 0x30, 0x01, 0x01, 0x00 };
/* Do_AGC1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_AGCs_DetOut_byte__Do_AGC1 = { 0x30, 0x00, 0x01, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_3 0x31 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RFAGCs_Gain_byte_3 = { 0x31, 0x00, 0x08, 0x00 };
/* AGC2_Gain_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_3__AGC2_Gain_Read = { 0x31, 0x04, 0x02, 0x00 };
/* AGC1_Gain_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read = { 0x31, 0x00, 0x04, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_4 0x32 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_4 = { 0x32, 0x00, 0x08, 0x00 };
/* Cprog_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_4__Cprog_Read = { 0x32, 0x00, 0x08, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_5 0x33 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5 = { 0x33, 0x00, 0x08, 0x00 };
/* RFAGC_Read_K_8 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__RFAGC_Read_K_8 = { 0x33, 0x07, 0x01, 0x00 };
/* Do_AGC1bis bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__Do_AGC1bis = { 0x33, 0x06, 0x01, 0x00 };
/* AGC1_Top_Adapt_Low bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__AGC1_Top_Adapt_Low = { 0x33, 0x05, 0x01, 0x00 };
/* Up_LNA_Adapt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__Up_LNA_Adapt = { 0x33, 0x04, 0x01, 0x00 };
/* Do_LNA_Adapt bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__Do_LNA_Adapt = { 0x33, 0x03, 0x01, 0x00 };
/* TOP_AGC3_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_5__TOP_AGC3_Read = { 0x33, 0x00, 0x03, 0x00 };


/* TDA18273 Register RFAGCs_Gain_byte_6 0x34 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_6 = { 0x34, 0x00, 0x08, 0x00 };
/* RFAGC_Read_K bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RFAGCs_Gain_byte_6__RFAGC_Read_K = { 0x34, 0x00, 0x08, 0x00 };


/* TDA18273 Register IFAGCs_Gain_byte 0x35 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IFAGCs_Gain_byte = { 0x35, 0x00, 0x08, 0x00 };
/* AGC5_Gain_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IFAGCs_Gain_byte__AGC5_Gain_Read = { 0x35, 0x03, 0x03, 0x00 };
/* AGC4_Gain_Read bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IFAGCs_Gain_byte__AGC4_Gain_Read = { 0x35, 0x00, 0x03, 0x00 };


/* TDA18273 Register RSSI_byte_1 0x36 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_1 = { 0x36, 0x00, 0x08, 0x00 };
/* RSSI bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_1__RSSI = { 0x36, 0x00, 0x08, 0x00 };


/* TDA18273 Register RSSI_byte_2 0x37 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_2 = { 0x37, 0x00, 0x08, 0x00 };
/* RSSI_AV bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_RSSI_byte_2__RSSI_AV = { 0x37, 0x05, 0x01, 0x00 };
/* RSSI_Cap_Reset_En bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_2__RSSI_Cap_Reset_En = { 0x37, 0x03, 0x01, 0x00 };
/* RSSI_Cap_Val bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_2__RSSI_Cap_Val = { 0x37, 0x02, 0x01, 0x00 };
/* RSSI_Ck_Speed bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_2__RSSI_Ck_Speed = { 0x37, 0x01, 0x01, 0x00 };
/* RSSI_Dicho_not bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_RSSI_byte_2__RSSI_Dicho_not = { 0x37, 0x00, 0x01, 0x00 };


/* TDA18273 Register Misc_byte 0x38 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Misc_byte = { 0x38, 0x00, 0x08, 0x00 };
/* RFCALPOR_I2C bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_Misc_byte__RFCALPOR_I2C = { 0x38, 0x06, 0x01, 0x00 };
/* PD_Underload bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Misc_byte__PD_Underload = { 0x38, 0x05, 0x01, 0x00 };
/* DDS_Polarity bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Misc_byte__DDS_Polarity = { 0x38, 0x04, 0x01, 0x00 };
/* IRQ_Mode bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Misc_byte__IRQ_Mode = { 0x38, 0x01, 0x01, 0x00 };
/* IRQ_Polarity bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Misc_byte__IRQ_Polarity = { 0x38, 0x00, 0x01, 0x00 };


/* TDA18273 Register rfcal_log_0 0x39 */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/ gTDA18273_Reg_rfcal_log_0 = { 0x39, 0x00, 0x08, 0x00 };
/* rfcal_log_0 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_0__rfcal_log_0 = { 0x39, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_1 0x3A */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_1 = { 0x3A, 0x00, 0x08, 0x00 };
/* rfcal_log_1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_1__rfcal_log_1 = { 0x3A, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_2 0x3B */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_2 = { 0x3B, 0x00, 0x08, 0x00 };
/* rfcal_log_2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_2__rfcal_log_2 = { 0x3B, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_3 0x3C */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_3 = { 0x3C, 0x00, 0x08, 0x00 };
/* rfcal_log_3 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_3__rfcal_log_3 = { 0x3C, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_4 0x3D */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_4 = { 0x3D, 0x00, 0x08, 0x00 };
/* rfcal_log_4 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_4__rfcal_log_4 = { 0x3D, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_5 0x3E */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_5 = { 0x3E, 0x00, 0x08, 0x00 };
/* rfcal_log_5 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_5__rfcal_log_5 = { 0x3E, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_6 0x3F */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_6 = { 0x3F, 0x00, 0x08, 0x00 };
/* rfcal_log_6 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_6__rfcal_log_6 = { 0x3F, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_7 0x40 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_7 = { 0x40, 0x00, 0x08, 0x00 };
/* rfcal_log_7 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_7__rfcal_log_7 = { 0x40, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_8 0x41 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_8 = { 0x41, 0x00, 0x08, 0x00 };
/* rfcal_log_8 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_8__rfcal_log_8 = { 0x41, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_9 0x42 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_9 = { 0x42, 0x00, 0x08, 0x00 };
/* rfcal_log_9 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_9__rfcal_log_9 = { 0x42, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_10 0x43 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_10 = { 0x43, 0x00, 0x08, 0x00 };
/* rfcal_log_10 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_10__rfcal_log_10 = { 0x43, 0x00, 0x08, 0x00 };


/* TDA18273 Register rfcal_log_11 0x44 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_11 = { 0x44, 0x00, 0x08, 0x00 };
/* rfcal_log_11 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_rfcal_log_11__rfcal_log_11 = { 0x44, 0x00, 0x08, 0x00 };



/* TDA18273 Register Main_Post_Divider_byte 0x51 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_Main_Post_Divider_byte = { 0x51, 0x00, 0x08, 0x00 };
/* LOPostDiv bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Main_Post_Divider_byte__LOPostDiv = { 0x51, 0x04, 0x03, 0x00 };
/* LOPresc bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Main_Post_Divider_byte__LOPresc = { 0x51, 0x00, 0x04, 0x00 };


/* TDA18273 Register Sigma_delta_byte_1 0x52 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_1 = { 0x52, 0x00, 0x08, 0x00 };
/* LO_Int bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_1__LO_Int = { 0x52, 0x00, 0x07, 0x00 };


/* TDA18273 Register Sigma_delta_byte_2 0x53 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_2 = { 0x53, 0x00, 0x08, 0x00 };
/* LO_Frac_2 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_2__LO_Frac_2 = { 0x53, 0x00, 0x07, 0x00 };


/* TDA18273 Register Sigma_delta_byte_3 0x54 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_3 = { 0x54, 0x00, 0x08, 0x00 };
/* LO_Frac_1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_3__LO_Frac_1 = { 0x54, 0x00, 0x08, 0x00 };


/* TDA18273 Register Sigma_delta_byte_4 0x55 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_4 = { 0x55, 0x00, 0x08, 0x00 };
/* LO_Frac_0 bit(s):  */
/*const*/ TDA18273_BitField_t/*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_4__LO_Frac_0 = { 0x55, 0x00, 0x08, 0x00 };


/* TDA18273 Register Sigma_delta_byte_5 0x56 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_5 = { 0x56, 0x00, 0x08, 0x00 };
/* N_K_correct_manual bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_5__N_K_correct_manual = { 0x56, 0x01, 0x01, 0x00 };
/* LO_Calc_Disable bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Sigma_delta_byte_5__LO_Calc_Disable = { 0x56, 0x00, 0x01, 0x00 };


/* TDA18273 Register Regulators_byte 0x58 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Regulators_byte = { 0x58, 0x00, 0x08, 0x00 };
/* RF_Reg bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Regulators_byte__RF_Reg = { 0x58, 0x02, 0x02, 0x00 };


/* TDA18273 Register IR_Cal_byte_5 0x5B */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Cal_byte_5 = { 0x5B, 0x00, 0x08, 0x00 };
/* Mixer_Gain_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass = { 0x5B, 0x07, 0x01, 0x00 };
/* IR_Mixer_Gain bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_IR_Cal_byte_5__IR_Mixer_Gain = { 0x5B, 0x04, 0x03, 0x00 };


/* TDA18273 Register Power_Down_byte_2 0x5F */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_2 = { 0x5F, 0x00, 0x08, 0x00 };
/* PD_LNA bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_2__PD_LNA = { 0x5F, 0x07, 0x01, 0x00 };
/* PD_Det4 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/gTDA18273_Reg_Power_Down_byte_2__PD_Det4 = { 0x5F, 0x03, 0x01, 0x00 };
/* PD_Det3 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_2__PD_Det3 = { 0x5F, 0x02, 0x01, 0x00 };
/* PD_Det1 bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_2__PD_Det1 = { 0x5F, 0x00, 0x01, 0x00 };

/* TDA18273 Register Power_Down_byte_3 0x60 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_3 = { 0x60, 0x00, 0x08, 0x00 };
/* Force_Soft_Reset bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_3__Force_Soft_Reset = { 0x60, 0x01, 0x01, 0x00 };
/* Soft_Reset bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Power_Down_byte_3__Soft_Reset = { 0x60, 0x00, 0x01, 0x00 };

/* TDA18273 Register Charge_pump_byte 0x64 */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Charge_pump_byte = { 0x64, 0x00, 0x08, 0x00 };
/* ICP_Bypass bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Charge_pump_byte__ICP_Bypass = { 0x64, 0x07, 0x01, 0x00 };
/* ICP bit(s):  */
/*const*/ TDA18273_BitField_t /*IFD_CODE*/ gTDA18273_Reg_Charge_pump_byte__ICP = { 0x64, 0x00, 0x02, 0x00 };




// NXP source code - .\tmbslTDA18273\src\tmbslTDA18273.c

/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18273.c
 *
 *                %version: CFR_FEAP#39 %
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *                Christophe CAZETTES
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18273_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
*/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#if 0
#include "tmNxTypes.h"
#include "tmNxCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#endif
/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#if 0
#include "tmbslTDA18273.h"

#include "tmbslTDA18273_RegDef.h"
#include "tmbslTDA18273_Local.h"
#include "tmbslTDA18273_Instance.h"
#include "tmbslTDA18273_InstanceCustom.h"
#endif

/*============================================================================*/
/* Static internal functions:                                                 */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_SetLLPowerState(pTDA18273Object_t pObj, TDA18273PowerState_t powerState);

static tmErrorCode_t
iTDA18273_OverrideBandsplit(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_OverrideDigitalClock(pTDA18273Object_t pObj, UInt32 uRF);

static tmErrorCode_t
iTDA18273_OverrideICP(pTDA18273Object_t pObj, UInt32 freq);

static tmErrorCode_t
iTDA18273_OverrideWireless(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_FirstPassPLD_CC(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_LastPassPLD_CC(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_WaitXtalCal_End(pTDA18273Object_t pObj, UInt32 timeOut, UInt32 waitStep);

static tmErrorCode_t
iTDA18273_CalculatePostDivAndPrescaler(UInt32 LO, Bool growingOrder, UInt8* PostDiv, UInt8* Prescaler);

static tmErrorCode_t
iTDA18273_FindPostDivAndPrescalerWithBetterMargin(UInt32 LO, UInt8* PostDiv, UInt8* Prescaler);

static tmErrorCode_t
iTDA18273_CalculateNIntKInt(UInt32 LO, UInt8 PostDiv, UInt8 Prescaler, UInt32* NInt, UInt32* KInt);

static tmErrorCode_t
iTDA18273_SetPLL(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_FirstPassLNAPower(pTDA18273Object_t pObj);

static tmErrorCode_t
iTDA18273_LastPassLNAPower(pTDA18273Object_t pObj);

/*============================================================================*/
/* Static variables:                                                          */
/*============================================================================*/
typedef struct _TDA18273_PostDivPrescalerTableDef_
{
    UInt32 LO_max;
    UInt32 LO_min;
    UInt8 Prescaler;
    UInt8 PostDiv;
} TDA18273_PostDivPrescalerTableDef;

/* Table that maps LO vs Prescaler & PostDiv values */
static TDA18273_PostDivPrescalerTableDef /*IFD_CODE*/ PostDivPrescalerTable[35] =
{
    /* PostDiv 1 */
    {974000, 852250, 7, 1},
    {852250, 745719, 8, 1},
    {757556, 662861, 9, 1},
    {681800, 596575, 10, 1},
    {619818, 542341, 11, 1},
    {568167, 497146, 12, 1},
    {524462, 458904, 13, 1},
    /* PostDiv 2 */
    {487000, 426125, 7, 2},
    {426125, 372859, 8, 2},
    {378778, 331431, 9, 2},
    {340900, 298288, 10, 2},
    {309909, 271170, 11, 2},
    {284083, 248573, 12, 2},
    {262231, 229452, 13, 2},
    /* PostDiv 4 */
    {243500, 213063, 7, 4},
    {213063, 186430, 8, 4},
    {189389, 165715, 9, 4},
    {170450, 149144, 10, 4},
    {154955, 135585, 11, 4},
    {142042, 124286, 12, 4},
    {131115, 114726, 13, 4},
    /* PostDiv 8 */
    {121750, 106531, 7, 8},
    {106531, 93215, 8, 8},
    {94694, 82858, 9, 8},
    {85225, 74572, 10, 8},
    {77477, 67793, 11, 8},
    {71021, 62143, 12, 8},
    {65558, 57363, 13, 8},
    /* PostDiv 16 */
    {60875, 53266, 7, 16},
    {53266, 46607, 8, 16},
    {47347, 41429, 9, 16},
    {42613, 37286, 10, 16},
    {38739, 33896, 11, 16},
    {35510, 31072, 12, 16},
    {32779, 28681, 13, 16}
};

/* Middle of VCO frequency excursion : VCOmin + (VCOmax - VCOmin)/2 in KHz */
#define TDA18273_MIDDLE_FVCO_RANGE ((6818000 - 5965750) / 2 + 5965750)

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_Open:                                           */
/*                                                                            */
/* DESCRIPTION: Opens driver setup environment.                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_Open(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /* I: setup parameters */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Test parameter(s) */
    if(psSrvFunc == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Get a driver instance */
        err = iTDA18273_GetInstance(tUnit, &pObj);
    }

    /* Check driver instance state */
    if(err == TM_OK || err == TDA18273_ERR_ERR_NO_INSTANCES)
    {
        if(P_OBJ_VALID && pObj->init == True)
        {
            err = TDA18273_ERR_ALREADY_SETUP;
        }
        else 
        {
            if(P_OBJ_VALID == False)
            {
                /* Try to allocate an instance of the driver */
                err = iTDA18273_AllocInstance(tUnit, &pObj);
                if(err != TM_OK || pObj == Null)
                {
                    err = TDA18273_ERR_ERR_NO_INSTANCES;
                }
            }

            if(err == TM_OK)
            {
#ifndef CPU_C51
                /* Initialize the Object by default values */
                P_SIO = P_FUNC_SIO(psSrvFunc);
                P_STIME = P_FUNC_STIME(psSrvFunc);
                P_SDEBUG = P_FUNC_SDEBUG(psSrvFunc);

#ifdef _TVFE_IMPLEMENT_MUTEX
                if(    P_FUNC_SMUTEX_OPEN_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_CLOSE_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_ACQUIRE_VALID(psSrvFunc)
                    && P_FUNC_SMUTEX_RELEASE_VALID(psSrvFunc) )
                {
                    P_SMUTEX = psSrvFunc->sMutex;

                    err = P_SMUTEX_OPEN(&P_MUTEX);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Open(%x) failed.", tUnit));
                }
#endif
#endif
                tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_Open(%x)", (unsigned long)tUnit);

                if(err == TM_OK)
                {
                    pObj->init = True;
                }
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_Close:                                          */
/*                                                                            */
/* DESCRIPTION: Closes driver setup environment.                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_Close(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    if(err == TM_OK)
    {
#ifdef _TVFE_IMPLEMENT_MUTEX
        /* Try to acquire driver mutex */
        err = iTDA18273_MutexAcquire(pObj, TDA18273_MUTEX_TIMEOUT);

        if(err == TM_OK)
        {
#endif
            tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_Close(%x)", tUnit);

#ifdef _TVFE_IMPLEMENT_MUTEX
            P_SMUTEX_ACQUIRE = Null;

            /* Release driver mutex */
            (void)iTDA18273_MutexRelease(pObj);

            if(P_SMUTEX_CLOSE_VALID && P_MUTEX_VALID)
            {
                err = P_SMUTEX_CLOSE(P_MUTEX);
            }

            P_SMUTEX_OPEN = Null;
            P_SMUTEX_CLOSE = Null;
            P_SMUTEX_RELEASE = Null;

            P_MUTEX = Null;
        }
#endif

        err = iTDA18273_DeAllocInstance(pObj);
    }

    return err;
}


#ifndef CODE_LITE_ENABLE
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetSWVersion:                                   */
/*                                                                            */
/* DESCRIPTION: Gets the versions of the driver.                              */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetSWVersion(
    ptmSWVersion_t  pSWVersion  /* I: Receives SW Version */
)
{
    pSWVersion->compatibilityNr = TDA18273_COMP_NUM;
    pSWVersion->majorVersionNr  = TDA18273_MAJOR_VER;
    pSWVersion->minorVersionNr  = TDA18273_MINOR_VER;

    return TM_OK;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetSWSettingsVersion:                           */
/*                                                                            */
/* DESCRIPTION: Returns the version of the driver settings.                   */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetSWSettingsVersion(
    ptmSWSettingsVersion_t pSWSettingsVersion   /* O: Receives SW Settings Version */
)
{
    pSWSettingsVersion->customerNr      = TDA18273_SETTINGS_CUSTOMER_NUM;
    pSWSettingsVersion->projectNr       = TDA18273_SETTINGS_PROJECT_NUM;
    pSWSettingsVersion->majorVersionNr  = TDA18273_SETTINGS_MAJOR_VER;
    pSWSettingsVersion->minorVersionNr  = TDA18273_SETTINGS_MINOR_VER;

    return TM_OK;
}
#endif

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_CheckHWVersion:                                 */
/*                                                                            */
/* DESCRIPTION: Checks TDA18273 HW Version.                                   */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_CheckHWVersion(
    tmUnitSelect_t tUnit    /* I: Unit number */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt16              uIdentity = 0;
    UInt8               ID_byte_1 = 0;
    UInt8               ID_byte_2 = 0;
    UInt8               majorRevision = 0;
    UInt8               minorRevision = 0;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_CheckHWVersion(%x)", tUnit);

    err = iTDA18273_ReadRegMap(pObj, gTDA18273_Reg_ID_byte_1.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_ID_byte_1__Ident_1, gTDA18273_Reg_ID_byte_3));
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_ReadRegMap(%x) failed.", tUnit));
	
    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_ID_byte_1__Ident_1, &ID_byte_1, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_ID_byte_2__Ident_2, &ID_byte_2, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        /* Construct Identity */
        uIdentity = (ID_byte_1 << 8) | ID_byte_2;
	
        if(uIdentity == 18273)
        {
            /* TDA18273 found. Check Major & Minor Revision*/
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_ID_byte_3__Major_rev, &majorRevision, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));

            err = iTDA18273_Read(pObj, &gTDA18273_Reg_ID_byte_3__Minor_rev, &minorRevision, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));

            switch (majorRevision)
            {
                case 1:
                {
                    switch (minorRevision)
                    {
                        case 1:
                            /* ES2 is supported */
                            err = TM_OK;
                            break;

                        default:
                            /* Only TDA18273 ES2 are supported */
                            err = TDA18273_ERR_BAD_VERSION;
                            break;
                    }
                }
                break;

                default:
                    /* Only TDA18273 ES2 are supported */
                    err = TDA18273_ERR_BAD_VERSION;
                    break;
            }
        }
        else
        {
            err = TDA18273_ERR_BAD_VERSION;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetPowerState                                   */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t  powerState  /* I: Power state */
 )
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetPowerState(%x)", tUnit);

    if(powerState>=tmPowerMax)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        if(pObj->mapLLPowerState[powerState] != pObj->curLLPowerState)
        {
            err = iTDA18273_SetLLPowerState(pObj, pObj->mapLLPowerState[powerState]);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetLLPowerState(%x, %d) failed.", tUnit, (int)pObj->mapLLPowerState[powerState]));

            if(err == TM_OK)
            {
                /* Store power state in driver instance */
                pObj->curPowerState = powerState;
            }
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetPowerState:                                  */
/*                                                                            */
/* DESCRIPTION: Gets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t* pPowerState /* O: Power state */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetPowerState(%x)", tUnit);

    /* Test parameter(s) */
    if(pPowerState == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pPowerState = pObj->curPowerState;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetLLPowerState                                 */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA18273PowerState_t    powerState  /* I: Power state of TDA18273 */
 )
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetLLPowerState(%x)", tUnit);

    pObj->curPowerState = tmPowerMax;

    err = iTDA18273_SetLLPowerState(pObj, powerState);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetLLPowerState(%x, %d) failed.", tUnit, (int)powerState));

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetLLPowerState                                 */
/*                                                                            */
/* DESCRIPTION: Gets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetLLPowerState(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    TDA18273PowerState_t*   pPowerState /* O: Power state of TDA18273 */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;


    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetLLPowerState(%x)", tUnit);

    /* Test parameter(s) */
    if(pPowerState == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_state_byte_2, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        if(!(uValue&(TDA18273_SM|TDA18273_SM_XT)))
        {
            *pPowerState = TDA18273_PowerNormalMode;
        }
        else if( (uValue&TDA18273_SM) && !(uValue&TDA18273_SM_XT) )
        {
            *pPowerState = TDA18273_PowerStandbyWithXtalOn;
        }
        else if( (uValue&TDA18273_SM) && (uValue&TDA18273_SM_XT) )
        {
            *pPowerState = TDA18273_PowerStandby;
        }
        else
        {
            err = TDA18273_ERR_NOT_SUPPORTED;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetStandardMode                                 */
/*                                                                            */
/* DESCRIPTION: Sets the standard mode.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetStandardMode(
    tmUnitSelect_t          tUnit,          /* I: Unit number */
    TDA18273StandardMode_t  StandardMode    /* I: Standard mode of this device */
)
{
    pTDA18273Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;
    pTDA18273StdCoefficients    prevPStandard = Null;
#if 0 // move to set RF freq
//#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
    UInt8 uPD_Det2;
#endif

//printk("%s %d\n",__FILE__, __LINE__);
    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

//printk("%s %d\n",__FILE__, __LINE__);
    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetStandardMode(%x)", tUnit);
//printk("%s %d\n",__FILE__, __LINE__);
    /* Check if Hw is ready to operate */
    err = iTDA18273_CheckHwState(pObj, TDA18273_HwStateCaller_SetStd);
	//printk("%s %d\n",__FILE__, __LINE__);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckHwState(%x) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* Store standard mode */
        pObj->StandardMode = StandardMode;

        /* Reset standard map pointer */
        prevPStandard = pObj->pStandard;
        pObj->pStandard = Null;

        if(pObj->StandardMode>TDA18273_StandardMode_Unknown && pObj->StandardMode<TDA18273_StandardMode_Max)
        {
            /* Update standard map pointer */
            pObj->pStandard = &gTDA18273Instance_Std_Array/*&pObj->Std_Array*/[pObj->StandardMode - 1];

            /****************************************************************/
            /* IF SELECTIVITY Settings                                      */
            /****************************************************************/

            /* Set LPF */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Byte_1__LP_Fc, pObj->pStandard->LPF, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                /* Set LPF Offset */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Byte_1__LP_FC_Offset, pObj->pStandard->LPF_Offset, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set DC_Notch_IF_PPF */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_2__IF_Notch, pObj->pStandard->DC_Notch_IF_PPF, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Enable/disable HPF */
                if(pObj->pStandard->IF_HPF == TDA18273_IF_HPF_Disabled )
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_2__Hi_Pass, 0x00, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
                else
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_2__Hi_Pass, 0x01, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                    if(err == TM_OK)
                    {
                        /* Set IF HPF */
                        err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Byte_1__IF_HP_Fc, (UInt8)(pObj->pStandard->IF_HPF - 1), Bus_None);
                        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                    }
                }
            }

            if(err == TM_OK)
            {
                /* Set IF Notch */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Byte_1__IF_ATSC_Notch, pObj->pStandard->IF_Notch, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set IF notch to RSSI */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_AGC_byte__IFnotchToRSSI, pObj->pStandard->IFnotchToRSSI, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* AGC TOP Settings                                             */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set AGC1 TOP I2C DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_1__AGC1_TOP, pObj->pStandard->AGC1_TOP_I2C_DN_UP, Bus_NoRead); 
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC1 Adapt TOP DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode_Val, pObj->pStandard->AGC1_Adapt_TOP_DN_UP, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
	    if(err == TM_OK)
            {
            /* Set AGC1 DN Time Constant */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_Do_step, pObj->pStandard->AGC1_DN_Time_Constant, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
           }
#endif

            if(err == TM_OK)
            {
                /* Set AGC1 mode */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode, pObj->pStandard->AGC1_Mode, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set Range_LNA_Adapt */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Adapt_Top_byte__Range_LNA_Adapt, pObj->pStandard->Range_LNA_Adapt, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set LNA_Adapt_RFAGC_Gv_Threshold */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Adapt_Top_byte__Index_K_LNA_Adapt, pObj->pStandard->LNA_Adapt_RFAGC_Gv_Threshold, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC1_Top_Adapt_RFAGC_Gv_Threshold */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Adapt_Top_byte__Index_K_Top_Adapt, pObj->pStandard->AGC1_Top_Adapt_RFAGC_Gv_Threshold, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC2 TOP DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC2_byte_1__AGC2_TOP, pObj->pStandard->AGC2_TOP_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
		if(err == TM_OK)
        {
            /* Set AGC2 DN Time Constant */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_3__AGC2_Do_step, pObj->pStandard->AGC2_DN_Time_Constant, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        }
#endif

// CONFIG_TUNER_NXP_VIETNAM_PATCH: move AGC3 Settings  to Set RF
#ifndef CONFIG_TUNER_NXP_VIETNAM_PATCH

            if(err == TM_OK)
            {
                /* Set AGC3 RF AGC Top */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Top, pObj->pStandard->AGC3_TOP_I2C_Low_Band, Bus_NoRead); 
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC3 Adapt TOP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Adapt_TOP, pObj->pStandard->AGC3_Adapt_TOP_Low_Band, Bus_NoRead); 
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
#endif
            if(err == TM_OK)
            {
                /* Set AGC4 TOP DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_1__IR_Mixer_Top, pObj->pStandard->AGC4_TOP_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC5 TOP DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_1__AGC5_TOP, pObj->pStandard->AGC5_TOP_DN_UP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC3_Top_Adapt_Algorithm */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__PD_AGC_Adapt3x, pObj->pStandard->AGC3_Top_Adapt_Algorithm, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGC Overload TOP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_Mgt_byte__AGC_Ovld_TOP, pObj->pStandard->AGC_Overload_TOP, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set Adapt TOP 34 Gain Threshold */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__TH_AGC_Adapt34, pObj->pStandard->TH_AGC_Adapt34, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set RF atten 3dB */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__RF_Atten_3dB, pObj->pStandard->RF_Atten_3dB, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set IF Output Level */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_AGC_byte__IF_level, pObj->pStandard->IF_Output_Level, Bus_NoRead); 
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set S2D gain */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_1__S2D_Gain, pObj->pStandard->S2D_Gain, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set Negative modulation */
#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
     err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_byte__Neg_modulation, pObj->pStandard->Negative_Modulation, Bus_NoRead);
#else
     err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_byte__Neg_modulation, pObj->pStandard->Negative_Modulation, Bus_None);
#endif
       
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* GSK Settings                                                 */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set AGCK Step */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__AGCK_Step, pObj->pStandard->AGCK_Steps, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Set AGCK Time Constant */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__AGCK_Mode, pObj->pStandard->AGCK_Time_Constant, Bus_NoRead); 
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

	     if(err == TM_OK)
            {
        	  /* Enable Internal Vsync */
        	  tmbslTDA18273_SetInternalVsync(pObj->tUnitW, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273_SetInternalVsync(%x) failed.", pObj->tUnitW));
	      }

            if(err == TM_OK)
            {
                /* Set AGC5 HPF */
                UInt8 wantedValue = pObj->pStandard->AGC5_HPF;

                if(pObj->pStandard->AGC5_HPF == TDA18273_AGC5_HPF_Enabled)
                {
                    UInt8 checked = 0;

                    /* Check if Internal Vsync is selected */
                    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Vsync_byte__Vsync_int, &checked, Bus_RW);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

                    if(err == TM_OK && checked == 0)
                    {
                        /* Internal Vsync is OFF, so override setting to OFF */
                        wantedValue = TDA18273_AGC5_HPF_Disabled;
                    }
                }

                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_1__AGC5_Ana, wantedValue, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
            }

            if(err == TM_OK)
            {
                /* Set Pulse Shaper Disable */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__Pulse_Shaper_Disable, pObj->pStandard->Pulse_Shaper_Disable, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* H3H5 Settings                                                */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set VHF_III_Mode */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__VHF_III_mode, pObj->pStandard->VHF_III_Mode, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* PLL Settings                                                 */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set LO_CP_Current */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_CP_Current_byte__LO_CP_Current, pObj->pStandard->LO_CP_Current, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            /****************************************************************/
            /* IF Settings                                                  */
            /****************************************************************/

            if(err == TM_OK)
            {
                /* Set IF */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Frequency_byte__IF_Freq, (UInt8)((pObj->pStandard->IF - pObj->pStandard->CF_Offset)/50000), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                /* Update IF in pObj */
                pObj->uIF = pObj->pStandard->IF;
            }

            if(err == TM_OK)
            {
                /* Write AGC1_byte_1 (0x0C) to IF_Byte_1 (0x15) Registers */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_AGC1_byte_1.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_AGC1_byte_1, gTDA18273_Reg_IF_Byte_1));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write IF_Frequency_byte (0x17) Register */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_IF_Frequency_byte.Address, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write Adapt_Top_byte (0x1F) Register */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_Adapt_Top_byte.Address, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write Vsync_byte (0x20) to IR_Mixer_byte_2 (0x22) Registers */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_Vsync_byte.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_Vsync_byte, gTDA18273_Reg_IR_Mixer_byte_2));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write RFAGCs_Gain_byte_1 (0x24) Register */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_RFAGCs_Gain_byte_1.Address, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write CP_Current_byte (0x2F) Register */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_CP_Current_byte.Address, 1);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }



#if 0//move to RF freq
	/****************************************************************/
        /* MISC Settings                                                */
        /****************************************************************/

	if(err == TM_OK)
        {
            /* Set PD Underload (0x38)*/
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Misc_byte__PD_Underload, pObj->pStandard->PD_Underload, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        }
		/* AGC2 freeze workaround */
		if ( pObj->pStandard->AGC2_freeze == _TRUE)		
			{
			RTD_Log(LOGGER_DEBUG, "[NXP] Vietnam Patch\n");
			
  		    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2, &uPD_Det2, Bus_RW);
			uPD_Det2 = uPD_Det2 | 0x02 ;
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det2, Bus_NoRead);				
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 0x1, Bus_NoRead);
			}				
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain, 0x1, Bus_NoRead);
			}				
			if(err == TM_OK)
			{
            		        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Gv, 0x0, Bus_NoRead);
			}
		}
		else
		{
  		    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2, &uPD_Det2, Bus_RW);

			uPD_Det2 = uPD_Det2 & 0xFD ;
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det2, Bus_NoRead);				
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 0x0, Bus_NoRead);
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain, 0x0, Bus_NoRead);
			}
		}
	/**************End MISC************/	
#endif // Move to set RF 
        }
	 if(err == TM_OK)
        {
        	/* Enable Internal Vsync */
        	tmbslTDA18273_SetInternalVsync(pObj->tUnitW, 1);
              tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273_SetInternalVsync(%x) failed.", pObj->tUnitW));
	 }
        /* Update driver state machine */
        pObj->eHwState = TDA18273_HwState_SetStdDone;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetStandardMode                                 */
/*                                                                            */
/* DESCRIPTION: Gets the standard mode.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetStandardMode(
    tmUnitSelect_t          tUnit,          /* I: Unit number */
    TDA18273StandardMode_t  *pStandardMode  /* O: Standard mode of this device */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetStandardMode(%x)", tUnit);

    if(pStandardMode == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Get standard mode */
        *pStandardMode = pObj->StandardMode;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetRF:                                          */
/*                                                                            */
/* DESCRIPTION: Tunes to a RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uRF     /* I: RF frequency in hertz */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
    UInt8 uPD_Det2;
#endif

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetRF(%x)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA18273_StandardMode_Unknown
       || pObj->StandardMode>=TDA18273_StandardMode_Max
       || pObj->pStandard == Null)
    {
        err = TDA18273_ERR_STD_NOT_SET;
    }

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA18273_CheckHwState(pObj, TDA18273_HwStateCaller_SetRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckHwState(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
     	  /* Enable Internal Vsync */
     	  tmbslTDA18273_SetInternalVsync(pObj->tUnitW, 1);
         tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273_SetInternalVsync(%x) failed.", pObj->tUnitW));
    }

        /* Set the proper settings depending on the standard & RF frequency */

#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
        /****************************************************************/
        /* AGC TOP Settings                                             */
        /****************************************************************/
        pObj->uRF = uRF;

        if(err == TM_OK)
        {
            /* Set AGC3 TOP I2C */
	if ((pObj->uRF + pObj->pStandard->CF_Offset) < pObj->pStandard->Freq_Start_LTE)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Top, pObj->pStandard->AGC3_TOP_I2C_Low_Band, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }				
            }
            else
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Top, pObj->pStandard->AGC3_TOP_I2C_High_Band, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        }

        if(err == TM_OK)
        {
            /* Set AGC3 Adapt TOP */
	if ((pObj->uRF + pObj->pStandard->CF_Offset) < pObj->pStandard->Freq_Start_LTE)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Adapt_TOP, pObj->pStandard->AGC3_Adapt_TOP_Low_Band, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
            else
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_AGC_byte__RFAGC_Adapt_TOP, pObj->pStandard->AGC3_Adapt_TOP_High_Band, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
        }
        /* End of settings */

#endif //END CONFIG_TUNER_NXP_VIETNAM_PATCH


#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH

	/****************************************************************/
        /* MISC Settings                                                */
        /****************************************************************/

	if(err == TM_OK)
        {
            /* Set PD Underload (0x38)*/
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Misc_byte__PD_Underload, pObj->pStandard->PD_Underload, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        }
		/* AGC2 freeze workaround */
		if(( pObj->pStandard->AGC2_freeze == _TRUE) && (pObj->uRF + pObj->pStandard->CF_Offset < _TUNER_FIXAGC_FREQ))
			{
			RTD_Log(LOGGER_DEBUG, "[NXP] Vietnam Patch, AGC2_freeze = %x, RF freq = %x Hz\n", (UINT32)pObj->pStandard->AGC2_freeze,(UINT32)pObj->uRF);
			
  		    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2, &uPD_Det2, Bus_RW);
			uPD_Det2 = uPD_Det2 | 0x02 ;
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det2, Bus_NoRead);				
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 0x1, Bus_NoRead);
			}				
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain, 0x1, Bus_NoRead);
			}				
			if(err == TM_OK)
			{
            		        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Gv, 0x0, Bus_NoRead);
			}
		}
		else
		{
  		    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2, &uPD_Det2, Bus_RW);

			uPD_Det2 = uPD_Det2 & 0xFD ;
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det2, Bus_NoRead);				
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 0x0, Bus_NoRead);
			}			
			if(err == TM_OK)
			{
		                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain, 0x0, Bus_NoRead);
			}

			/*Free AGC1 */
			if(err == TM_OK)
			{
            		        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, 0x0, Bus_NoRead);
			}

		}
	/**************End MISC************/	

#if config_tuner_read_enable
//CTunerReadRegMap(); 
#endif


#endif // END CONFIG_TUNER_NXP_VIETNAM_PATCH
    if(err == TM_OK)
    {
        pObj->uRF = uRF;
        pObj->uProgRF = pObj->uRF + pObj->pStandard->CF_Offset;

        err = iTDA18273_SetRF(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetRF(%x) failed.", tUnit));

        if(err == TM_OK)
        {
            /* Update driver state machine */
            pObj->eHwState = TDA18273_HwState_SetRFDone;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetRF:                                          */
/*                                                                            */
/* DESCRIPTION: Gets tuned RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puRF    /* O: RF frequency in hertz */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetRF(%x)", tUnit);

    if(puRF == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }
    if(err == TM_OK)
    {
        /* Get RF */
        *puRF =  pObj->uRF /*- pObj->pStandard->CF_Offset*/;
    }
    _MUTEX_RELEASE(TDA18273)

    return err;
}
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_HwInit:                                         */
/*                                                                            */
/* DESCRIPTION: Initializes TDA18273 Hardware.                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_HwInit(
    tmUnitSelect_t  tUnit   /* I: Unit number */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValuePOR;
#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
	UInt8 uPD_Det1;
#endif

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_HwInit(%x)", tUnit);

    /* Reset standard mode & Hw State */
    pObj->StandardMode = TDA18273_StandardMode_Max;
    pObj->eHwState = TDA18273_HwState_InitNotDone;

    /* Read POR bit to see if it is the first init after POR */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_state_byte_1__POR, &uValuePOR, Bus_RW);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    /* Check for XtalCal End only when bufferMode is not used */
    if (pObj->bBufferMode == False)
    {
        err = iTDA18273_WaitXtalCal_End(pObj, 2000, 200);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitXtalCal_End(%x) failed.", pObj->tUnitW));
    }
    if(err == TM_OK)
    {
        /* Read all bytes */
        err = iTDA18273_ReadRegMap(pObj, 0x00, TDA18273_REG_MAP_NB_BYTES);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_ReadRegMap(%x) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        /* Check if Calc_PLL algorithm is in automatic mode */
        err = iTDA18273_CheckCalcPLL(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckCalcPLL(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /****************************************************/
        /* Change POR values                                */
        /****************************************************/

        /* Up_Step_Ovld: POR = 1 -> 0 */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_Mgt_byte__Up_Step_Ovld, 0x00, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* PLD_CC_Enable: POR = 1 -> 0 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* RFCAL_Offset0 : 0 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog0, 0x00, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                /* RFCAL_Offset1 : 0 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog1, 0x00, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset2 : 0 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog2, 0x00, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset3 : 0 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog3, 0x00, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset4 : 3 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog4, 0x03, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset5 : 0 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog5, 0x00, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset6 : 3 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog6, 0x03, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset7 : 3 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog7, 0x03, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* RFCAL_Offset8 : 1 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog8, 0x01, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Write RF_Cal_byte_1 (0x27) to RF_Cal_byte_3 (0x29) Registers */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_RF_Cal_byte_1.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_RF_Cal_byte_1, gTDA18273_Reg_RF_Cal_byte_3));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
            }
        }

        if(err == TM_OK)
        {
            /* PLD_Temp_Enable: POR = 1 -> 0 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_Temp_Enable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Power Down Vsync Management: POR = 0 -> 1 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_Mgt_byte__PD_Vsync_Mgt, 0x01, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    if(err == TM_OK)
    {
        /* Set IRQ_clear */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_IRQ_clear, TDA18273_IRQ_Global|TDA18273_IRQ_HwInit|TDA18273_IRQ_IrCal, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Set power state on */
        err = iTDA18273_SetLLPowerState(pObj, TDA18273_PowerNormalMode);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetLLPowerState(%x, PowerNormalMode) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        pObj->curPowerState = tmPowerOn;

        /* Launch tuner calibration */

        /****************************************/
        /* PLD spread fix                       */    
        /****************************************/

        /* Perform this workaround only for the 2nd init and onwards */
        if (uValuePOR == 0)
        {
            /* Set digital clock mode to 16 Mhz before resetting the IC to avoid unclocking the digital part*/
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, 0x00, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

            if (pObj->bBufferMode == False)
            {
                /* Reset XTALCAL_End bit */
                if(err == TM_OK)
                {
                    /* Set IRQ_clear */
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_IRQ_clear, TDA18273_IRQ_Global|TDA18273_IRQ_XtalCal|TDA18273_IRQ_HwInit|TDA18273_IRQ_IrCal, Bus_NoRead);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
            }

            /* Perform a SW reset to reset the digital calibrations */
            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_3, 0x03, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_3, 0x00, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if (pObj->bBufferMode == False)
            {
                /* Launch XTALCAL */
                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_MSM_byte_2__XtalCal_Launch, 0x01, Bus_RW);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_MSM_byte_2__XtalCal_Launch, 0x00, Bus_RW);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
                
                /* Wait XTALCAL_End bit */
                if(err == TM_OK)
                {
                    err = iTDA18273_WaitXtalCal_End(pObj, 1000, 100);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitXtalCal_End(%x) failed.", pObj->tUnitW));
                }
            }

            /* Set digital clock mode to sub-LO */
            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, 0x03, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
        }

        /****************************************/
        /* End of PLD spread fix                */
        /****************************************/

        /* Set state machine (all CALs except IRCAL) and Launch it */
        if(err == TM_OK)
        {
            err = iTDA18273_SetMSM(pObj, TDA18273_MSM_HwInit, True);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetMSM(%x, TDA18273_MSM_HwInit) failed.", pObj->tUnitW));
        }

        /* Inform that init phase has started */
        if(err == TM_OK)
        {
            pObj->eHwState = TDA18273_HwState_InitPending;
        }

        if(err == TM_OK && pObj->bIRQWaitHwInit)
        {
            /* State reached after 500 ms max */
            err = iTDA18273_WaitIRQ(pObj, 2000, 200, TDA18273_IRQ_HwInit);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitIRQ(%x) failed.", tUnit));
        }

        /****************************************/
        /* PLD spread fix                       */    
        /****************************************/

        if(err == TM_OK)
        {
            /* Set IRQ_clear */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_IRQ_clear, TDA18273_IRQ_Global|TDA18273_IRQ_HwInit|TDA18273_IRQ_IrCal, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        /* Launch IRCALs after all other CALs are finished */
        if(err == TM_OK)
        {
            err = iTDA18273_SetMSM(pObj, TDA18273_MSM_IrCal, True);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetMSM(%x, TDA18273_MSM_IrCal) failed.", pObj->tUnitW));
        }

        if(err == TM_OK && pObj->bIRQWaitHwInit)
        {
            /* State reached after 500 ms max, 10 ms step due to CAL ~ 30ms */
            err = iTDA18273_WaitIRQ(pObj, 2000, 200, TDA18273_IRQ_IrCal);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitIRQ(%x) failed.", tUnit));
        }
        /****************************************/
        /* End of PLD spread fix                */
        /****************************************/
//  Issue description           :  Modify the NXP driver for 1/2 RF interference to NX driver SSG2.17
//                                           
//  Issue severity level            :  ***
//  Issue resolved name         :  Ives
//  Issue date                        :  2011/09/22
#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
//NXP  ver. SSG2.17
		/* workaround for LNA toggling at startup */
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetAGC2_loop_off(tUnit, 1);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 1, Bus_NoRead);
 		}
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetIR_Mixer_loop_off(tUnit, 1);
					err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_2__IR_Mixer_loop_off, 1, Bus_NoRead);
			}
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetAGC5_loop_off(tUnit, 1);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_2__AGC5_loop_off, 1, Bus_NoRead);
			}

            if(err == TM_OK)
            {
                /* Set AGC1 Adapt TOP DN/UP */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode_Val, TDA18273_AGC1_Adapt_TOP_DN_UP_0_Step, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
			
            if(err == TM_OK)
            {
				//err = tmddTDA18273SetForce_AGC1_gain(tUnit, 1);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, 1, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmddTDA18273SetForce_AGC1_gain(%x) failed.", tUnit));
			}
            if(err == TM_OK)
            {
				//err = tmddTDA18273SetAGC1_Gain(tUnit, 10); /* 20dB */
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_Gain, 10, Bus_NoRead);	
			}
            if(err == TM_OK)
            {
				//err = tmddTDA18273Read ( tUnit, 0x5F, 1, &uPD_Det1 );
				err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2, &uPD_Det1, Bus_RW);		
			}
		if(err == TM_OK) /*  power down all gains AGC2, 4, 5 */
		{
			    uPD_Det1 = uPD_Det1 | 0x1E ;
				//err = tmddTDA18273Write ( tUnit, 0x5F, 1, &uPD_Det1 );
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det1, Bus_NoRead);				
		}

            if(err == TM_OK)
            {
		            err = iTDA18273_Wait(pObj, 150);

			}
            if(err == TM_OK)
            {
				//err = tmddTDA18273SetForce_AGC1_gain(tUnit, 0);
			        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, 0, Bus_NoRead);
			}
            if(err == TM_OK)
            {
		            err = iTDA18273_Wait(pObj, 150);
		}
	if(err == TM_OK)  /*  active all gains AGC2, 4, 5 */
	{
			    uPD_Det1 = uPD_Det1 & 0xE1 ;
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2, uPD_Det1, Bus_NoRead);				
		}			
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetAGC2_loop_off(tUnit, 0);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__AGC2_loop_off, 0, Bus_NoRead);
			}
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetIR_Mixer_loop_off(tUnit, 0);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Mixer_byte_2__IR_Mixer_loop_off, 0, Bus_NoRead);
			}
            if(err == TM_OK)
            {
				//err =  tmddTDA18273SetAGC5_loop_off(tUnit, 0);
				err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_2__AGC5_loop_off, 0, Bus_NoRead);
			}

	#if config_tuner_read_enable
		//CTunerReadRegMap(); 
	#endif


#endif // Vietnam


        if(err == TM_OK && pObj->eHwState == TDA18273_HwState_InitPending)
        {
            pObj->eHwState = TDA18273_HwState_InitDone;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetIF:                                          */
/*                                                                            */
/* DESCRIPTION: Gets programmed IF.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetIF(%x)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA18273_StandardMode_Unknown
        || pObj->StandardMode>=TDA18273_StandardMode_Max
        || pObj->pStandard == Null
        || puIF == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *puIF = pObj->uIF /*- pObj->pStandard->CF_Offset*/;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}
#ifndef CODE_LITE_ENABLE
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetIF:                                          */
/*                                                                            */
/* DESCRIPTION: Sets programmed IF.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32          uIF     /* I: IF Frequency in hertz */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA18273_StandardMode_Unknown
        || pObj->StandardMode>=TDA18273_StandardMode_Max
        || pObj->pStandard == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Update IF in pObj structure */
        pObj->uIF = uIF + pObj->pStandard->CF_Offset;

        /* Update IF in TDA18273 registers */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_IF_Frequency_byte__IF_Freq, (UInt8)(uIF/50000), Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetCF_Offset:                                   */
/*                                                                            */
/* DESCRIPTION: Gets CF Offset.                                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetCF_Offset(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32*         puOffset    /* O: Center frequency offset in hertz */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetCF_Offset(%x)", tUnit);

        /* Test parameter(s) */
        if(   pObj->StandardMode<=TDA18273_StandardMode_Unknown
            || pObj->StandardMode>=TDA18273_StandardMode_Max
            || pObj->pStandard == Null
            || puOffset == Null)
        {
            err = TDA18273_ERR_BAD_PARAMETER;
        }

        if(err == TM_OK)
        {
            *puOffset = pObj->pStandard->CF_Offset;
        }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetLockStatus:                                  */
/*                                                                            */
/* DESCRIPTION: Gets PLL Lock Status.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetLockStatus(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0, uValueLO = 0;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetLockStatus(%x)", tUnit);

    if( pLockStatus == Null )
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_state_byte_1__LO_Lock, &uValueLO, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status__IRQ_status, &uValue, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            uValue = uValue & uValueLO;

            *pLockStatus =  (uValue)? tmbslFrontEndStateLocked : tmbslFrontEndStateNotLocked;
        }
        else
        {
            *pLockStatus = tmbslFrontEndStateUnknown;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetPowerLevel:                                  */
/*                                                                            */
/* DESCRIPTION: Gets HW Power Level.   1/2 steps dBµV                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetPowerLevel
(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*          pPowerLevel /* O: Power Level in 1/2 steps dBµV */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetPowerLevel(%x)", tUnit);

    /* Test parameter(s) */
    if( pPowerLevel == Null ||
        pObj->StandardMode<=TDA18273_StandardMode_Unknown ||
        pObj->StandardMode>=TDA18273_StandardMode_Max ||
        pObj->pStandard == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pPowerLevel = 0;

        /* Implement PLD CC algorithm to increase PLD read immunity to interferer */
        /*
            -PLD CC ON.
            -Wait 40ms.
            -PLD read standard.
            -PLD CC OFF. 
        */

        /* Do the algorithm only if asked and not in analog mode */
        if( (pObj->PLD_CC_algorithm == True) && isTDA18273_ANLG_STD(pObj->StandardMode) == False )
        {
            /* PLD_CC_Enable: 1 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable, 0x01, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", tUnit));

            if(err == TM_OK)
            {
                /* Wait 40 ms */
                err = iTDA18273_Wait(pObj, 40);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", tUnit));
            }
        }

        if(err == TM_OK)
        {
            /* Read Power Level */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_Input_Power_Level_byte__Power_Level, pPowerLevel, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));
        }

        if( (err == TM_OK) && (pObj->uProgRF <= 145408000))
        {
            /* RF <= 145.408 MHz, then apply minus 3 dB */
            /* 1 step = 0.5 dB */
            if (*pPowerLevel >= 6)
                *pPowerLevel -= 6;
            else
                *pPowerLevel = 0;
        }

        /* Finish the algorithm only if asked and not in analog mode */
        if( (pObj->PLD_CC_algorithm == True) && isTDA18273_ANLG_STD(pObj->StandardMode) == False )
        {
            /* PLD_CC_Enable: 0 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", tUnit));
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}
#endif
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetInternalVsync:                               */
/*                                                                            */
/* DESCRIPTION: Enables or disable the internal VSYNC                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool            bEnabled    /* I: Enable of disable the internal VSYNC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetInternalVsync(%x)", tUnit);

    if(err == TM_OK)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Vsync_byte__Vsync_int, ((bEnabled == True) ? 1 : 0), Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", tUnit));
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}
#ifndef CODE_LITE_ENABLE
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetInternalVsync:                               */
/*                                                                            */
/* DESCRIPTION: Get the current status of the internal VSYNC                  */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetInternalVsync(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    Bool*           pbEnabled   /* O: current status of the internal VSYNC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA182I4_SetInternalVsync(%x)", tUnit);

    if(pbEnabled == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_Vsync_byte__Vsync_int, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", tUnit));
    }

    if(err == TM_OK)
    {
        if (uValue == 1)
        {
            *pbEnabled = True;
        }
        else
        {
            *pbEnabled = False;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetPllManual:                                   */
/*                                                                            */
/* DESCRIPTION: Sets bOverridePLL flag.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool            bOverridePLL   /* I: Determine if we need to put PLL in manual mode in SetRF */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetPllManual(%x)", tUnit);

    pObj->bOverridePLL = bOverridePLL;

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetIRQWait:                                     */
/*                                                                            */
/* DESCRIPTION: Sets IRQWait flag.                                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetIRQWait(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIRQWait(%x)", tUnit);

    pObj->bIRQWait = bWait;

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetPllManual:                                   */
/*                                                                            */
/* DESCRIPTION: Gets bOverridePLL flag.                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetPllManual(
    tmUnitSelect_t  tUnit,         /* I: Unit number */
    Bool*           pbOverridePLL  /* O: Determine if we need to put PLL in manual mode in SetRF */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetPllManual(%x)", tUnit);

    if(pbOverridePLL == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbOverridePLL = pObj->bOverridePLL;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetIRQWait:                                     */
/*                                                                            */
/* DESCRIPTION: Gets IRQWait flag.                                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetIRQWait(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetIRQWait(%x)", tUnit);

    if(pbWait == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbWait = pObj->bIRQWait;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetIRQWaitHwInit:                               */
/*                                                                            */
/* DESCRIPTION: Sets IRQWait flag.                                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetIRQWaitHwInit(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIRQWaitHwInit(%x)", tUnit);

    pObj->bIRQWaitHwInit = bWait;

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetIRQWaitHwInit:                               */
/*                                                                            */
/* DESCRIPTION: Gets IRQWait flag.                                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetIRQWaitHwInit(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetIRQWaitHwInit(%x)", tUnit);

    if(pbWait == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbWait = pObj->bIRQWaitHwInit;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetIRQ:                                         */
/*                                                                            */
/* DESCRIPTION: Gets IRQ status.                                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetIRQ(
    tmUnitSelect_t  tUnit   /* I: Unit number */,
    Bool*           pbIRQ   /* O: IRQ triggered */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetIRQ(%x)", tUnit);

    if(pbIRQ == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbIRQ = 0;

        err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status__IRQ_status, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            *pbIRQ = uValue;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_WaitIRQ:                                        */
/*                                                                            */
/* DESCRIPTION: Waits for the IRQ to raise.                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_WaitIRQ(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt32          timeOut,    /* I: timeOut for IRQ wait */
    UInt32          waitStep,   /* I: wait step */
    UInt8           irqStatus   /* I: IRQs to wait */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_WaitIRQ(%x)", tUnit);

    err = iTDA18273_WaitIRQ(pObj, timeOut, waitStep, irqStatus);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitIRQ(%x) failed.", tUnit));

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetXtalCal_End:                                 */
/*                                                                            */
/* DESCRIPTION: Gets XtalCal_End status.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetXtalCal_End(
    tmUnitSelect_t  tUnit           /* I: Unit number */,
    Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    UInt8               uValue = 0;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetXtalCal_End(%x)", tUnit);

    if(pbXtalCal_End == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        *pbXtalCal_End = 0;

        err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status__MSM_XtalCal_End, &uValue, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            *pbXtalCal_End = uValue;
        }
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetFineRF:                                      */
/*                                                                            */
/* DESCRIPTION: Fine tunes RF with given step.                                */
/*              (tmbslTDA18273_SetRF must be called before calling this API)  */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetFineRF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    Int8            step    /* I: step (-1, +1) */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* LO wanted = RF wanted + IF in KHz */
    UInt32 LO = 0;

    /* PostDiv */
    UInt8 PostDiv = 0;
    UInt8 LOPostDiv = 0;

    /* Prescaler */
    UInt8 Prescaler = 0;

    /* Algorithm that calculates N, K */
    UInt32 N_int = 0;
    UInt32 K_int = 0;

    UInt8 i = 0;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetFineRF(%x)", tUnit);

    /* Test parameter(s) */
    if(   pObj->StandardMode<=TDA18273_StandardMode_Unknown
        || pObj->StandardMode>=TDA18273_StandardMode_Max
        || pObj->pStandard == Null)
    {
        err = TDA18273_ERR_STD_NOT_SET;
    }

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA18273_CheckHwState(pObj, TDA18273_HwStateCaller_SetFineRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckHwState(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Write the offset into 4 equal steps of 15.625 KHz = 62.5 KHz*/
        for (i=0; i < 4; i++)
        {
            /* Calculate wanted LO = RF + IF */
            pObj->uRF += step*15625;
            pObj->uProgRF += step*15625;
            LO = (pObj->uRF + pObj->uIF)/1000;

            /* Don't touch on Prescaler and PostDiv programmed during setRF */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPostDiv, &LOPostDiv, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                err = iTDA18273_Read(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPresc, &Prescaler, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
            }


            if (err == TM_OK)
            {
                /* Decode PostDiv */
                switch(LOPostDiv)
                {
                    case 1:
                        PostDiv = 1;
                        break;
                    case 2:
                        PostDiv = 2;
                        break;
                    case 3:
                        PostDiv = 4;
                        break;
                    case 4:
                        PostDiv = 8;
                        break;
                    case 5:
                        PostDiv = 16;
                        break;
                    default:
                        err = TDA18273_ERR_BAD_PARAMETER;
                        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslTDA18273_SetFineRF(%x) LO_PostDiv value is wrong.", tUnit));
                        break;
                }

                /* Calculate N & K values of the PLL */
                err = iTDA18273_CalculateNIntKInt(LO, PostDiv, Prescaler, &N_int, &K_int);

                /* Affect registers */
                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_4__LO_Frac_0, (UInt8)(K_int & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_3__LO_Frac_1, (UInt8)((K_int >> 8) & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_2__LO_Frac_2, (UInt8)((K_int >> 16) & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_1__LO_Int, (UInt8)(N_int & 0xFF), Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    /* Force manual selection mode : 0x3 at @0x56 */
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x01, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                    if(err == TM_OK)
                    {
                        /* Force manual selection mode : 0x3 at @0x56 */
                        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x01, Bus_None);
                        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                    }
                }

// To avoid channel losing issue, ives 0913
#if 0
		/* Set the new PLL values */
                if(err == TM_OK)
                {
                    /* Write bytes Sigma_delta_byte_1 (0x52) to Sigma_delta_byte_5 (0x56) */
                    err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_Sigma_delta_byte_1.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_Sigma_delta_byte_1, gTDA18273_Reg_Sigma_delta_byte_5));
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
#endif
            }
        }

        /* Update driver state machine */
        pObj->eHwState = TDA18273_HwState_SetFineRFDone;
    }

    _MUTEX_RELEASE(TDA18273)

    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_Write                                           */
/*                                                                            */
/* DESCRIPTION: Writes in TDA18273 hardware                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_Write(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    /*const*/ TDA18273_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    eBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_Write(%x)", tUnit);

    err = iTDA18273_Write(pObj, pBitField, uData, eBusAccess);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    _MUTEX_RELEASE(TDA18273)

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_Read                                            */
/*                                                                            */
/* DESCRIPTION: Reads in TDA18273 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_Read(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    /*const*/ TDA18273_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    eBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_Read(%x)", tUnit);

    err = iTDA18273_Read(pObj, pBitField, puData, eBusAccess);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    _MUTEX_RELEASE(TDA18273)

    return err;
}
#endif
/*============================================================================*/
/* Internal functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    iTDA18273_CheckHwState                                        */
/*                                                                            */
/* DESCRIPTION: Checks if Hw is ready to operate.                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_CheckHwState(
    pTDA18273Object_t       pObj,   /* I: Driver object */
    TDA18273HwStateCaller_t caller  /* I: Caller API */
)
{
    tmErrorCode_t   err = TM_OK;
    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_CheckHwState(%x)", pObj->tUnitW);
    switch(pObj->eHwState)
    {
    case TDA18273_HwState_InitNotDone:
        switch(caller)
        {
        case TDA18273_HwStateCaller_SetPower:
            break;

        default:
            err = TDA18273_ERR_NOT_INITIALIZED;
            break;
        }
        break;

    case TDA18273_HwState_InitDone:
        switch(caller)
        {
        case TDA18273_HwStateCaller_SetRF:
        case TDA18273_HwStateCaller_SetFineRF:
            /* SetStandardMode API must be called before calling SetRF and SetFineRF */
            err = TDA18273_ERR_STD_NOT_SET;
            break;

        default:
            break;
        }
        break;

    case TDA18273_HwState_SetStdDone:
        switch(caller)
        {
        case TDA18273_HwStateCaller_SetFineRF:
            /* SetRF API must be called before calling SetFineRF */
            err = TDA18273_ERR_RF_NOT_SET;
            break;

        default:
            break;
        }
        break;

    case TDA18273_HwState_SetRFDone:
    case TDA18273_HwState_SetFineRFDone:
        break;

    case TDA18273_HwState_InitPending:
	
        /* Hw Init pending. Check if IRQ triggered. No wait. */
        err = iTDA18273_WaitIRQ(pObj, 1, 1, TDA18273_IRQ_HwInit);	
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitIRQ(%x) failed.", pObj->tUnitW));
   
        if(err == TM_OK)
        {    
            /* Init Done. Call iTDA18273_CheckHwState to check after Hw Initialization. */
            err = iTDA18273_CheckHwState(pObj, caller);	
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckHwState(%x) failed.", pObj->tUnitW));
            break;
        }
    default:
        err = TDA18273_ERR_NOT_READY;
        break;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_CheckCalcPLL                                        */
/*                                                                            */
/* DESCRIPTION: Checks if CalcPLL Algo is enabled. Enable it if not.          */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_CheckCalcPLL(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uValue = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_CheckCalcPLL(%x)", pObj->tUnitW);

    /* Check if Calc_PLL algorithm is in automatic mode */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__LO_Calc_Disable, &uValue, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    if(err == TM_OK && uValue != 0x00)
    {
        /* Enable Calc_PLL algorithm by putting PLL in automatic mode */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x00, Bus_NoRead); 
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_SetLLPowerState                                     */
/*                                                                            */
/* DESCRIPTION: Sets the power state.                                         */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_SetLLPowerState(
    pTDA18273Object_t       pObj,       /* I: Driver object */
    TDA18273PowerState_t    powerState  /* I: Power state of TDA18273 */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uValue = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_SetLLPowerState(%x)", pObj->tUnitW);

    if(err == TM_OK)
    {
        /* Check if Hw is ready to operate */
        err = iTDA18273_CheckHwState(pObj, TDA18273_HwStateCaller_SetPower);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckHwState(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        switch(powerState)
        {
            case TDA18273_PowerNormalMode:
                /* If we come from any standby mode, then power on the IC with LNA off */
                /* Then powering on LNA with the minimal gain on AGC1 to avoid glitches at RF input will */
                /* be done during SetRF */
                if(pObj->curLLPowerState != TDA18273_PowerNormalMode)
                {
                    /* Workaround to limit the spurs occurence on RF input, do it before entering normal mode */
                    /* PD LNA */
                    err = iTDA18273_FirstPassLNAPower(pObj);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_FirstPassLNAPower(%x) failed.", pObj->tUnitW));  
                }

                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_state_byte_2, TDA18273_SM_NONE, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                if(err == TM_OK)
                {
                    /* Set digital clock mode to sub-LO if normal mode is entered */
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, 0x03, Bus_RW);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                /* Reset uValue to use it as a flag for below test */
                uValue = 0;
                break;

            case TDA18273_PowerStandbyWithXtalOn:
                uValue = TDA18273_SM;
                break;

            case TDA18273_PowerStandby:
            default:
                /* power state not supported */
                uValue = TDA18273_SM|TDA18273_SM_XT;
                break;
        }

        if(err == TM_OK && uValue!=0)
        {
            /* Set digital clock mode to 16 Mhz before entering standby */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, 0x00, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_state_byte_2, uValue, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
        }

        if(err == TM_OK)
        {
            /* Store low-level power state in driver instance */
            pObj->curLLPowerState = powerState;
        }
    }

    return err;
}


/*============================================================================*/
/* FUNCTION:    iTDA18273_SetRF:                                              */
/*                                                                            */
/* DESCRIPTION: Tunes to a RF.                                                */
/*                                                                            */
/* RETURN:      TM_OK                                                         */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_SetRF(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_SetRF(%x)", pObj->tUnitW);

    if(pObj->curPowerState != tmPowerOn)
    {
        /* Set power state ON */
        err = iTDA18273_SetLLPowerState(pObj, TDA18273_PowerNormalMode);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetLLPowerState(%x, PowerNormalMode) failed.", pObj->tUnitW));
    }

    /* Workaround to limit the spurs occurence on RF input */
    /* Check if LNA is powered down, if yes, power it up */
    if(err == TM_OK)
    {
        pObj->curPowerState = tmPowerOn;

        err = iTDA18273_LastPassLNAPower(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_LastPassLNAPower(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Check if Calc_PLL algorithm is in automatic mode */
        err = iTDA18273_CheckCalcPLL(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_CheckCalcPLL(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Setting Bandsplit parameters */
        err = iTDA18273_OverrideBandsplit(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_OverrideBandsplit(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Implement PLD read immunity against interferers: first pass before channel change */
        err = iTDA18273_FirstPassPLD_CC(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_FirstPassPLD_CC(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Set RF frequency */
        err = iTDA18273_SetRF_Freq(pObj, pObj->uProgRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetRF_Freq(%x) failed.", pObj->tUnitW));
    }

    /* Implement PLD read immunity against interferers: last pass after channel change */
    if(err == TM_OK)
    {
        err = iTDA18273_LastPassPLD_CC(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_LastPassPLD_CC(%x) failed.", pObj->tUnitW));
    }

    /* Bypass ROM settings for wireless filters */
    if(err == TM_OK)
    {
        err = iTDA18273_OverrideWireless(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_OverrideWireless(%x) failed.", pObj->tUnitW));
    }

#if config_tuner_read_enable
	//CTunerReadRegMap();
#endif


    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_SetRF_Freq                                          */
/*                                                                            */
/* DESCRIPTION: Sets Tuner Frequency registers.                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_SetRF_Freq(
    pTDA18273Object_t   pObj,   /* I: Driver object */
    UInt32              uRF     /* I: Wanted frequency */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          uRFLocal = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_SetRF_Freq(%x)", pObj->tUnitW);

    /* Set IRQ_clear */
    err = iTDA18273_Write(pObj, &gTDA18273_Reg_IRQ_clear, TDA18273_IRQ_Global|TDA18273_IRQ_SetRF, Bus_NoRead);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    /* Set RF */
    uRFLocal = (uRF + 500) / 1000;

    if(err == TM_OK)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Frequency_byte_1__RF_Freq_1, (UInt8)((uRFLocal & 0x00FF0000) >> 16), Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Frequency_byte_2__RF_Freq_2, (UInt8)((uRFLocal & 0x0000FF00) >> 8), Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Frequency_byte_3__RF_Freq_3, (UInt8)(uRFLocal & 0x000000FF), Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_RF_Frequency_byte_1.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_RF_Frequency_byte_1, gTDA18273_Reg_RF_Frequency_byte_3));
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Set state machine and Launch it */
        err = iTDA18273_SetMSM(pObj, TDA18273_MSM_SetRF, True);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetMSM(%x, TDA18273_MSM_SetRF) failed.", pObj->tUnitW));
    }

    if(err == TM_OK && pObj->bIRQWait)
    {
        /* Wait for IRQ to trigger */
        err = iTDA18273_WaitIRQ(pObj, 50, 5, TDA18273_IRQ_SetRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WaitIRQ(%x, 50, 5, TDA18273_IRQ_SetRF) failed.", pObj->tUnitW));
    }

    if(err == TM_OK && pObj->bOverridePLL)
    {
        /* Override the calculated PLL to get the best margin in case fine tuning is used */
        /* which means set the PLL in manual mode that provides the best occurence of LO tuning (+-2 MHz) */
        /* without touching PostDiv and Prescaler */
        err = iTDA18273_SetPLL(pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetPLL failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Override ICP */
        err = iTDA18273_OverrideICP(pObj, pObj->uProgRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_OverrideICP(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* Override Digital Clock */
        err = iTDA18273_OverrideDigitalClock(pObj, pObj->uProgRF);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_OverrideDigitalClock(%x) failed.", pObj->tUnitW));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_OverrideDigitalClock                                */
/*                                                                            */
/* DESCRIPTION: Overrides Digital clock.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_OverrideDigitalClock(
    pTDA18273Object_t   pObj,   /* I: Driver object */
    UInt32              uRF     /* I: Wanted RF */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uDigClock = 0;
    UInt8           uPrevDigClock = 0;
    UInt8           uProgIF = 0;

    /* LO < 55 MHz then Digital Clock set to 16 MHz else subLO */

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_OverrideDigitalClock(%x)", pObj->tUnitW);

    /* Read Current IF */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_IF_Frequency_byte__IF_Freq, &uProgIF, Bus_NoWrite);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    /* Read Current Digital Clock */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, &uPrevDigClock, Bus_NoWrite);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    /* LO = RF + IF */
    if ((uRF + (uProgIF*50000)) < 55000000)
    {
        uDigClock = 0; /* '00' = 16 MHz */
    }
    else
    {
        uDigClock = 3; /* '11' = subLO */
    }

    if(err == TM_OK && (uPrevDigClock != uDigClock) )
    {
        /* Set Digital Clock bits */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Reference_Byte__Digital_Clock_Mode, uDigClock, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_OverrideICP                                         */
/*                                                                            */
/* DESCRIPTION: Overrides ICP.                                                */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_OverrideICP(
    pTDA18273Object_t   pObj,   /* I: Driver object */
    UInt32              uRF     /* I: Wanted frequency */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          uIF = 0;
    UInt8           ProgIF = 0;
    UInt8           LOPostdiv = 0;
    UInt8           LOPrescaler = 0;
    UInt32          FVCO = 0;
    UInt8           uICPBypass = 0;
    UInt8           ICP = 0;
    UInt8           uPrevICP = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_OverrideICP(%x)", pObj->tUnitW);

    /*
    if fvco<6352 MHz ==> icp = 150?(register = 01b)
    if fvco<6592 MHz ==> icp = 300?(register = 10b)
    500µA elsewhere (register 00b)

    Reminder : fvco = postdiv*presc*(RFfreq+IFfreq) 
    */

    /* Read PostDiv et Prescaler */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Main_Post_Divider_byte, &LOPostdiv, Bus_RW);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* PostDiv */
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPostDiv, &LOPostdiv, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* Prescaler */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPresc, &LOPrescaler, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* IF */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_IF_Frequency_byte__IF_Freq, &ProgIF, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Decode IF */
            uIF = ProgIF*50000;
            
            /* Decode PostDiv */
            switch(LOPostdiv)
            {
                case 1:
                    LOPostdiv = 1;
                    break;
                case 2:
                    LOPostdiv = 2;
                    break;
                case 3:
                    LOPostdiv = 4;
                    break;
                case 4:
                    LOPostdiv = 8;
                    break;
                case 5:
                    LOPostdiv = 16;
                    break;
                default:
                    err = TDA18273_ERR_BAD_PARAMETER;
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_OverrideICP(%x) LOPostDiv value is wrong.", pObj->tUnitW));
                    break;
            }
        }
        if(err == TM_OK)
        {
            /* Calculate FVCO in MHz*/
            FVCO = LOPostdiv * LOPrescaler * ((uRF + uIF) / 1000000);

            /* Set correct ICP */

            if(FVCO < 6352)
            {
                /* Set ICP to 01 (= 150)*/
                ICP = 0x01;
            }
            else if(FVCO < 6592)
            {
                /* Set ICP to 10 (= 300)*/
                ICP = 0x02;
            }
            else
            {
                /* Set ICP to 00 (= 500)*/
                ICP = 0x00;
            }


            /* Get ICP_bypass bit */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_Charge_pump_byte__ICP_Bypass, &uICPBypass, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

            if(err == TM_OK)
            {
                /* Get ICP */
                err = iTDA18273_Read(pObj, &gTDA18273_Reg_Charge_pump_byte__ICP, &uPrevICP, Bus_NoRead);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK && (uICPBypass == False || uPrevICP != ICP) )
            {
                /* Set ICP_bypass bit */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Charge_pump_byte__ICP_Bypass, 0x01, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                if(err == TM_OK)
                {
                    /* Set ICP */
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Charge_pump_byte__ICP, ICP, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }

                if(err == TM_OK)
                {
                    /* Write Charge_pump_byte register */
                    err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_Charge_pump_byte.Address, 1);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
                }
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_OverrideBandsplit                                   */
/*                                                                            */
/* DESCRIPTION: Overrides Bandsplit settings.                                 */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_OverrideBandsplit(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           Bandsplit = 0;
    UInt8           uPrevPSM_Bandsplit_Filter = 0;
    UInt8           PSM_Bandsplit_Filter = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_OverrideBandsplit(%x)", pObj->tUnitW);

    /* Setting PSM bandsplit at -3.9 mA for some RF frequencies */

    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Bandsplit_Filter_byte__Bandsplit_Filter_SubBand, &Bandsplit, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_PowerSavingMode__PSM_Bandsplit_Filter, &uPrevPSM_Bandsplit_Filter, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        switch(Bandsplit)
        {
        default:
        case 0:
            /* LPF0 133MHz - LPF1 206MHz - HPF0 422MHz */
            if(pObj->uProgRF < 133000000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 1:
            /* LPF0 139MHz - LPF1 218MHz - HPF0 446MHz */
            if(pObj->uProgRF < 139000000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 2:
            /* LPF0 145MHz - LPF1 230MHz - HPF0 470MHz */
            if(pObj->uProgRF < 145000000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;

        case 3:
            /* LPF0 151MHz - LPF1 242MHz - HPF0 494MHz */
            if(pObj->uProgRF < 151000000)
            {
                /* Set PSM bandsplit at -3.9 mA */
                PSM_Bandsplit_Filter = 0x03;
            }
            else
            {
                /* Set PSM bandsplit at nominal */
                PSM_Bandsplit_Filter = 0x02;
            }
            break;
        }

        if(uPrevPSM_Bandsplit_Filter != PSM_Bandsplit_Filter)
        {
            /* Write PSM bandsplit */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_PowerSavingMode__PSM_Bandsplit_Filter, PSM_Bandsplit_Filter, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_OverrideWireless                                    */
/*                                                                            */
/* DESCRIPTION: Overrides Wireless settings.                                  */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_OverrideWireless(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           uPrevW_Filter_byte = 0;
    UInt8           uW_Filter_byte = 0;
    UInt8           W_Filter = 0;
    UInt8           W_Filter_Bypass = 0;
    UInt8           W_Filter_Offset = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_OverrideWireless(%x)", pObj->tUnitW);

    /* Bypass ROM for wireless filters */
    /* WF7 = 1.7GHz - 1.98GHz */
    /* WF8 = 1.98GHz - 2.1GHz */
    /* WF9 = 2.1GHz - 2.4GHz */
    /* For all frequencies requiring WF7 and WF8, add -8% shift */
    /* For all frequencies requiring WF9, change to WF8 and add +4% shift */

    /* Check for filter WF9 */
    if(
        ((pObj->uProgRF > 474000000) && (pObj->uProgRF < 536000000)) ||
        ((pObj->uProgRF > 794000000) && (pObj->uProgRF < 866000000))
        )
    {
        /* ROM is selecting WF9 */

        /* Bypass to WF8 */
        W_Filter_Bypass = 0x01;
        W_Filter = 0x01;

        /* Apply +4% shift */
        W_Filter_Offset = 0x00;
    }
    else
    {
        /* Let ROM do the job */
        W_Filter_Bypass = 0x00;
        W_Filter = 0x00;

        /* Check for filter WF7 & WF8 */
        if(
            ((pObj->uProgRF > 336000000) && (pObj->uProgRF < 431000000)) ||
            ((pObj->uProgRF > 563500000) && (pObj->uProgRF < 721000000))
            )
        {
            /* ROM is selecting WF7 or WF8 */

            /* Apply -8% shift */
            W_Filter_Offset = 0x03;
        }
        else
        {
            /* Nominal */
            W_Filter_Offset = 0x01;
        }
    }

    /* Read current W_Filter_byte */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_W_Filter_byte, &uPrevW_Filter_byte, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* Set Wireless Filter Bypass */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__W_Filter_Bypass, W_Filter_Bypass, Bus_NoRead); 
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* Set Wireless Filter */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__W_Filter, W_Filter, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Set Wireless Filter Offset */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__W_Filter_Offset, W_Filter_Offset, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Set Wireless filters ON */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_W_Filter_byte__W_Filter_Enable, 0x01, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Read above-modified W_Filter_byte */
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_W_Filter_byte, &uW_Filter_byte, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK && uPrevW_Filter_byte != uW_Filter_byte)
        {
            /* W_Filter_byte changed: Update it */
            err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_W_Filter_byte.Address, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_FirstPassPLD_CC                                     */
/*                                                                            */
/* DESCRIPTION: Implements the first pass of the PLD_CC algorithm.            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_FirstPassPLD_CC(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_FirstPassPLD_CC(%x)", pObj->tUnitW);

    /* Implement PLD CC algorithm to increase PLD read immunity to interferer */
    /* 
        - set AGCK mode to 8ms.
        - PLD CC ON.
        - Set RF
        - Loop of Read of AGC Lock:
            - if((AGClock green) or  TIMEOUT(200ms)) then next Step Else (Wait 1ms and next Read)
        - Wait 20ms.
        - PLD CC OFF.
        - Wait 1ms.
        - set AGCK mode back to initial mode
    */

    /* Do the algorithm only if asked and not in analog mode */
    if( (pObj->PLD_CC_algorithm == True) && isTDA18273_DGTL_STD(pObj->StandardMode) )
    {
        /* Set AGCK Time Constant */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__AGCK_Mode, TDA18273_AGCK_Time_Constant_8_192ms, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

        if(err == TM_OK)
        {
            /* PLD_CC_Enable: 1 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable, 0x01, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_LastPassPLD_CC                                      */
/*                                                                            */
/* DESCRIPTION: Implements the last pass of the PLD_CC algorithm.             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_LastPassPLD_CC(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           counter = 200; /* maximum 200 loops so max wait time = 200ms */
    UInt8           agcs_lock = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_LastPassPLD_CC(%x)", pObj->tUnitW);

    /* Finish the algorithm only if asked and not in analog mode */
    if( (pObj->PLD_CC_algorithm == True) && isTDA18273_DGTL_STD(pObj->StandardMode) )
    {
        /* Get initial AGCs_Lock */
        if(err == TM_OK)
        {
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_state_byte_1__AGCs_Lock, &agcs_lock, Bus_RW);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
        }

        /* Perform the loop to detect AGCs_Lock = 1 or error or timeout */
        while((err == TM_OK) && ((--counter)>0) && (agcs_lock == 0))
        {
			// kick watch dog
		//flow_timer_Reset_WatchDog();

            /* Wait 1 ms */
            err = iTDA18273_Wait(pObj, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", pObj->tUnit));

            if(err == TM_OK)
            {
                err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_state_byte_1__AGCs_Lock, &agcs_lock, Bus_RW);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
            }
        }

        /* Wait 20 ms */
        if(err == TM_OK)
        {
            err = iTDA18273_Wait(pObj, 20);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", pObj->tUnit));
        }

        /* PLD_CC_Enable: 0 */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable, 0x00, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
        
        /* Wait 1 ms */
        if(err == TM_OK)
        {
            err = iTDA18273_Wait(pObj, 1);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", pObj->tUnit));
        }

        /* Set AGCK Time Constant */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__AGCK_Mode, pObj->pStandard->AGCK_Time_Constant, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_FirstPassLNAPower                                   */
/*                                                                            */
/* DESCRIPTION: Power down the LNA                                            */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_FirstPassLNAPower(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{

    tmErrorCode_t err = TM_OK;

    /* PD LNA */
    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2__PD_LNA, 0x1, Bus_RW);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    if(err == TM_OK)
    {
        /* PD Detector AGC1 */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2__PD_Det1, 0x1, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        /* AGC1 Detector loop off */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_loop_off, 0x1, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_LastPassLNAPower                                    */
/*                                                                            */
/* DESCRIPTION: Power up the LNA                                              */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_LastPassLNAPower(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t err = TM_OK;
    UInt8 uValue;

    /* Check if LNA is PD */
    err = iTDA18273_Read(pObj, &gTDA18273_Reg_Power_Down_byte_2__PD_LNA, &uValue, Bus_NoWrite);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    if ((uValue == 1) && (err == TM_OK))
    {
        /* LNA is Powered Down, so power it up */

        /* Force gain to -10dB */
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_Gain, 0x0, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        
        /* Force LNA gain control */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, 0x1, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        /* PD LNA */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2__PD_LNA, 0x0, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        /* Release LNA gain control */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, 0x0, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* PD Detector AGC1 */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Power_Down_byte_2__PD_Det1, 0x0, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* AGC1 Detector loop off */
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_loop_off, 0x0, Bus_NoRead);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_SetPLL                                              */
/*                                                                            */
/* DESCRIPTION: Set the PLL in manual mode                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_SetPLL(
    pTDA18273Object_t   pObj    /* I: Driver object */
)
{
    tmErrorCode_t err = TM_OK;

    /* LO wanted = RF wanted + IF in KHz */
    UInt32 LO = 0;

    /* Algorithm that calculates PostDiv */
    UInt8 PostDiv = 0; /* absolute value */
    UInt8 LOPostDiv = 0; /* register value */

    /* Algorithm that calculates Prescaler */
    UInt8 Prescaler = 0;

    /* Algorithm that calculates N, K */
    UInt32 N_int = 0;
    UInt32 K_int = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_SetPLL(%x)", pObj->tUnitW);

    /* Calculate wanted LO = RF + IF in Hz */
    LO = (pObj->uRF + pObj->uIF) / 1000;

    /* Calculate the best PostDiv and Prescaler : the ones that provide the best margin */
    /* in case of fine tuning +-2 MHz */
    err = iTDA18273_FindPostDivAndPrescalerWithBetterMargin(LO, &PostDiv, &Prescaler);

    if (err == TM_OK)
    {
        /* Program the PLL only if valid values are found, in that case err == TM_OK */

        /* Decode PostDiv */
        switch(PostDiv)
        {
            case 1:
                LOPostDiv = 1;
                break;
            case 2:
                LOPostDiv = 2;
                break;
            case 4:
                LOPostDiv = 3;
                break;
            case 8:
                LOPostDiv = 4;
                break;
            case 16:
                LOPostDiv = 5;
                break;
            default:
                err = TDA18273_ERR_BAD_PARAMETER;
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_SetPLL(%x) *PostDiv value is wrong.", pObj->tUnitW));
                break;
        }

        /* Affect register map without writing into IC */
        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPostDiv, LOPostDiv, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            err = iTDA18273_Write(pObj, &gTDA18273_Reg_Main_Post_Divider_byte__LOPresc, Prescaler, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
        }

        if(err == TM_OK)
        {
            /* Calculate N & K values of the PLL */
            err = iTDA18273_CalculateNIntKInt(LO, PostDiv, Prescaler, &N_int, &K_int);

            /* Affect registers map without writing to IC */
            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_4__LO_Frac_0, (UInt8)(K_int & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_3__LO_Frac_1, (UInt8)((K_int >> 8) & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_2__LO_Frac_2, (UInt8)((K_int >> 16) & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_1__LO_Int, (UInt8)(N_int & 0xFF), Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }

            if(err == TM_OK)
            {
                /* Force manual selection mode : 0x3 at @0x56 */
                err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__N_K_correct_manual, 0x01, Bus_None);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

                if(err == TM_OK)
                {
                    /* Force manual selection mode : 0x3 at @0x56 */
                    err = iTDA18273_Write(pObj, &gTDA18273_Reg_Sigma_delta_byte_5__LO_Calc_Disable, 0x01, Bus_None);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
                }
            }

// To avoid channel losing issue
#if 0
            if(err == TM_OK)
            {
                /* Write bytes Main_Post_Divider_byte (0x51) to Sigma_delta_byte_5 (0x56) */
                err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_Main_Post_Divider_byte.Address, TDA18273_REG_DATA_LEN(gTDA18273_Reg_Main_Post_Divider_byte, gTDA18273_Reg_Sigma_delta_byte_5));
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
            }
#endif
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_CalculatePostDivAndPrescaler                        */
/*                                                                            */
/* DESCRIPTION: Calculate PostDiv and Prescaler by starting from lowest value */
/*              of LO or not                                                  */
/*              LO must be passed in Hz                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_FindPostDivAndPrescalerWithBetterMargin(
    UInt32 LO,          /* In Hz */
    UInt8* PostDiv,     /* Directly the value to set in the register  */
    UInt8* Prescaler    /* Directly the value to set in the register  */
)
{
    /* Initialize to error in case no valuable values are found */
    tmErrorCode_t err = TM_OK;

    UInt8 PostDivGrowing;
    UInt8 PrescalerGrowing;
    UInt8 PostDivDecreasing;
    UInt8 PrescalerDecreasing;
    UInt32 FCVOGrowing = 0;
    UInt32 DistanceFCVOGrowing = 0;
    UInt32 FVCODecreasing = 0;
    UInt32 DistanceFVCODecreasing = 0;

    /* Get the 2 possible values for PostDiv & Prescaler to find the one
    which provides the better margin on LO */
    err = iTDA18273_CalculatePostDivAndPrescaler(LO, True, &PostDivGrowing, &PrescalerGrowing);
    if (err == TM_OK)
    {
        /* Calculate corresponding FVCO value in kHz */
        FCVOGrowing = LO * PrescalerGrowing * PostDivGrowing;
    }

    err = iTDA18273_CalculatePostDivAndPrescaler(LO, False, &PostDivDecreasing, &PrescalerDecreasing);
    if (err == TM_OK)
    {
        /* Calculate corresponding FVCO value in kHz */
        FVCODecreasing = LO * PrescalerDecreasing * PostDivDecreasing;
    }

    /* Now take the values that are providing the better margin, the goal is +-2 MHz on LO */
    /* So take the point that is the nearest of (FVCOmax - FVCOmin)/2 = 6391,875 MHz */
    if (FCVOGrowing != 0)
    {
        if (FCVOGrowing >= TDA18273_MIDDLE_FVCO_RANGE)
        {
            DistanceFCVOGrowing = FCVOGrowing - TDA18273_MIDDLE_FVCO_RANGE;
        }
        else
        {
            DistanceFCVOGrowing = TDA18273_MIDDLE_FVCO_RANGE - FCVOGrowing;
        }
    }

    if (FVCODecreasing != 0)
    {
        if (FVCODecreasing >= TDA18273_MIDDLE_FVCO_RANGE)
        {
            DistanceFVCODecreasing = FVCODecreasing - TDA18273_MIDDLE_FVCO_RANGE;
        }
        else
        {
            DistanceFVCODecreasing = TDA18273_MIDDLE_FVCO_RANGE - FVCODecreasing;
        }
    }

    if (FCVOGrowing == 0)
    {
        if (FVCODecreasing == 0)
        {
            /* No value at all are found */
            err = TDA18273_ERR_BAD_PARAMETER;
        }
        else
        {
            /* No value in growing mode, so take the decreasing ones */
            *PostDiv = PostDivDecreasing;
            *Prescaler = PrescalerDecreasing;
        }
    }
    else
    {
        if (FVCODecreasing == 0)
        {
            /* No value in decreasing mode, so take the growing ones */
            *PostDiv = PostDivGrowing;
            *Prescaler = PrescalerGrowing;
        }
        else
        {
            /* Find the value which are the nearest of the middle of VCO range */
            if (DistanceFCVOGrowing <= DistanceFVCODecreasing)
            {
                *PostDiv = PostDivGrowing;
                *Prescaler = PrescalerGrowing;
            }
            else
            {
                *PostDiv = PostDivDecreasing;
                *Prescaler = PrescalerDecreasing;
            }
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_CalculateNIntKInt                                   */
/*                                                                            */
/* DESCRIPTION: Calculate PLL N & K values                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_CalculateNIntKInt(
    UInt32 LO, 
    UInt8 PostDiv, 
    UInt8 Prescaler, 
    UInt32* NInt, 
    UInt32* KInt
)
{
    tmErrorCode_t err = TM_OK;

    /* Algorithm that calculates N_K */
    UInt32 FVCO = 0;
    UInt32 N_K_prog = 0;

    /* Algorithm that calculates N, K corrected */
    UInt32 Nprime = 0;
    UInt32 KforceK0_1 = 0;
    UInt32 K2msb = 0;
    UInt32 N0 = 0;
    UInt32 Nm1 = 0;

    /* Calculate N_K_Prog */
    FVCO = LO * Prescaler * PostDiv;
    N_K_prog = (FVCO * 128) / 125;

    /* Calculate N & K corrected values */
    Nprime = N_K_prog & 0xFF0000;

    /* Force LSB to 1 */
    KforceK0_1 = 2*(((N_K_prog - Nprime) << 7) / 2) + 1;

    /* Check MSB bit around 2 */
    K2msb = KforceK0_1 >> 21;
    if (K2msb < 1)
    {
        N0 = 1;
    }
    else
    {
        if (K2msb >= 3)
        {
            N0 = 1;
        }
        else
        {
            N0 = 0;
        }
    }
    if (K2msb < 1)
    {
        Nm1 = 1;
    }
    else
    {
        Nm1 = 0;
    }

    /* Calculate N */
    *NInt = (2 * ((Nprime >> 16) - Nm1) + N0) - 128;

    /* Calculate K */
    if (K2msb < 1)
    {
        *KInt = KforceK0_1 + (2 << 21);
    }
    else
    {
        if (K2msb >= 3)
        {
            *KInt = KforceK0_1 - (2 << 21);
        }
        else
        {
            *KInt = KforceK0_1;
        }
    }

    /* Force last 7 bits of K_int to 0x5D, as the IC is doing for spurs optimization */
    *KInt &= 0xFFFFFF80;
    *KInt |= 0x5D;

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_CalculatePostDivAndPrescaler                        */
/*                                                                            */
/* DESCRIPTION: Calculate PostDiv and Prescaler by starting from lowest value */
/*              of LO or not                                                  */
/*              LO must be passed in Hz                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_CalculatePostDivAndPrescaler(
    UInt32 LO,         /* In Hz */
    Bool growingOrder, /* Start from LO = 28.681 kHz or LO = 974 kHz */
    UInt8* PostDiv,    /* Absolute value */
    UInt8* Prescaler   /* Absolute value  */
)
{
    tmErrorCode_t err = TM_OK;
    Int8 index;
    Int8 sizeTable = sizeof(PostDivPrescalerTable) / sizeof(TDA18273_PostDivPrescalerTableDef);

    if (growingOrder == True)
    {
        /* Start from LO = 28.681 kHz */
        for (index = (sizeTable - 1); index >= 0; index--)
        {
            if (
                (LO > PostDivPrescalerTable[index].LO_min) &&
                (LO < PostDivPrescalerTable[index].LO_max)
               )
            {
                /* We are at correct index in the table */
                break;
            }
        }
    }
    else
    {
        /* Start from LO = 974000 kHz */
        for (index = 0; index < sizeTable; index++)
        {
            if (
                (LO > PostDivPrescalerTable[index].LO_min) &&
                (LO < PostDivPrescalerTable[index].LO_max)
               )
            {
                /* We are at correct index in the table */
                break;
            }
        }
    }

    if ((index == -1) || (index == sizeTable))
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }
    else
    {
        /* Write Prescaler */
        *Prescaler = PostDivPrescalerTable[index].Prescaler;

        /* Decode PostDiv */
        *PostDiv = PostDivPrescalerTable[index].PostDiv;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_WaitXtalCal_End                                     */
/*                                                                            */
/* DESCRIPTION: Wait the XtalCal_End to trigger                               */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
static tmErrorCode_t
iTDA18273_WaitXtalCal_End(
    pTDA18273Object_t pObj, /* I: Driver object */
    UInt32 timeOut,         /* I: timeout */
    UInt32 waitStep         /* I: wait step */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStep ms */
    UInt8           uMSM_XtalCal_End = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_WaitXtalCal_End(%x)", pObj->tUnitW);

    while(counter > 0)
    {
			// kick watch dog
			//flow_timer_Reset_WatchDog();

        /* Don't check for I2C error because it can occur, just after POR, that I2C is not yet available */
        /* MSM_XtalCal_End must occur between POR and POR+70ms */
        /* Check for XtalCal End */
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status__MSM_XtalCal_End, &uMSM_XtalCal_End, Bus_RW);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));

        if(uMSM_XtalCal_End)
        {
            /* MSM_XtalCal_End is triggered => exit */
            break;
        }

        if(counter)
        {
            /* Decrease the counter */
            counter--;

            /* Wait for a step */
            err = iTDA18273_Wait(pObj, waitStep);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", pObj->tUnitW));
        }
    }

    if(counter == 0)
    {
        err = TDA18273_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_SetMSM                                              */
/*                                                                            */
/* DESCRIPTION: Set the MSM bit(s).                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_SetMSM(
    pTDA18273Object_t   pObj,   /* I: Driver object */
    UInt8               uValue, /* I: Item value */
    Bool                bLaunch /* I: Launch MSM */
)
{
    tmErrorCode_t   err = TM_OK;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_SetMSM(%x)", pObj->tUnitW);

    /* Set state machine and Launch it */
    err = iTDA18273_Write(pObj, &gTDA18273_Reg_MSM_byte_1, uValue, Bus_None);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    if(err == TM_OK && bLaunch)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_MSM_byte_2__MSM_Launch, 0x01, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK)
    {
        err = iTDA18273_WriteRegMap(pObj, gTDA18273_Reg_MSM_byte_1.Address, bLaunch?0x02:0x01);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_WriteRegMap(%x) failed.", pObj->tUnitW));
    }

    if(err == TM_OK && bLaunch)
    {
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_MSM_byte_2__MSM_Launch, 0x00, Bus_None);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_WaitIRQ                                             */
/*                                                                            */
/* DESCRIPTION: Wait the IRQ to trigger                                       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_WaitIRQ(
    pTDA18273Object_t   pObj,       /* I: Driver object */
    UInt32              timeOut,    /* I: timeout */
    UInt32              waitStep,   /* I: wait step */
    UInt8               irqStatus   /* I: IRQs to wait */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt32          counter = timeOut/waitStep; /* Wait max timeOut/waitStep ms */
    UInt8           uIRQ = 0;
    UInt8           uIRQStatus = 0;
    Bool            bIRQTriggered = False;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_WaitIRQ(%x)", pObj->tUnitW);

    while(err == TM_OK && (counter--)>0)
    {
		// kick watch dog
		//flow_timer_Reset_WatchDog();

         udelay(4000);//udelay by Lee, mac2
	  err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status__IRQ_status, &uIRQ, Bus_RW);
         tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
         udelay(4000);

        if(err == TM_OK && uIRQ == 1)
        {
            bIRQTriggered = True;
        }

        if(bIRQTriggered)
        {
            /* IRQ triggered => Exit */
            break;
        }

        if(err == TM_OK && irqStatus != 0x00)
        {
            udelay(4000);
            err = iTDA18273_Read(pObj, &gTDA18273_Reg_IRQ_status, &uIRQStatus, Bus_None);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Read(%x) failed.", pObj->tUnitW));
	     udelay(4000);

            if(irqStatus == uIRQStatus)
            {
                bIRQTriggered = True;
            }
        }

        if(counter)
        {
            udelay(4000);
            err = iTDA18273_Wait(pObj, waitStep);
            udelay(4000);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Wait(%x) failed.", pObj->tUnitW));
        }
    }

    if(err == TM_OK && bIRQTriggered == False)
    {
        err = TDA18273_ERR_NOT_READY;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_Write                                               */
/*                                                                            */
/* DESCRIPTION: Writes in TDA18273 hardware                                   */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_Write(
    pTDA18273Object_t           pObj,       /* I: Driver object */
    /*const*/ TDA18273_BitField_t*  pBitField, /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    eBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           RegAddr = 0;
    UInt32          DataLen = 1;
    UInt8           RegData = 0;
    pUInt8          pRegData = Null;
    UInt32          RegMask = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_Write(%x)", (unsigned long)pObj->tUnitW);

    if(pBitField == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        /* Set Register Address */
        RegAddr = pBitField->Address;

        if(RegAddr < TDA18273_REG_MAP_NB_BYTES)
        {
            pRegData = (UInt8 *)(&(pObj->RegMap)) + RegAddr;
        }
        else
        {
            pRegData = &RegData;
        }

        if( (eBusAccess&Bus_NoRead) == False /*&& P_SIO_READ_VALID*/)
        {
            /* Read data from TDA18273 */
            err = tda18273_Read/*P_SIO_READ*/(pObj->tUnitW, TDA18273_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(%x, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));
        }

        if(err == TM_OK)
        {
            RegMask = ( (1 << pBitField->WidthInBits) - 1);
            /* Limit uData to WidthInBits */
            uData &= RegMask;

            /* Set Data */
            RegMask = RegMask << pBitField->PositionInBits;
            *pRegData &= (UInt8)(~RegMask);
            *pRegData |= uData << pBitField->PositionInBits;

            if( (eBusAccess&Bus_NoWrite) == False /*&& P_SIO_WRITE_VALID*/)
            {
                /* Write data to TDA18273 */
                err = tda18273_Write/*P_SIO_WRITE*/(pObj->tUnitW, TDA18273_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Write(%x, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));

        	}
        }
			 	
    }
    	

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_Read                                                */
/*                                                                            */
/* DESCRIPTION: Reads in TDA18273 hardware                                    */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_Read(
    pTDA18273Object_t           pObj,       /* I: Driver object */
    /*const*/ TDA18273_BitField_t*  pBitField, /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    eBusAccess_t                eBusAccess  /* I: Access to bus */
)
{
    tmErrorCode_t   err = TM_OK;
    UInt8           RegAddr = 0;
    UInt32          DataLen = 1;
    UInt8           RegData = 0;
    pUInt8          pRegData = Null;
    UInt32          RegMask = 0;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_Read(%x)", pObj->tUnitW);

    if(pBitField == Null)
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {//printk("%s %d\n",__FILE__, __LINE__);

        /* Set Register Address */
        RegAddr = pBitField->Address;
//printk("%s %d\n",__FILE__, __LINE__);

        if(RegAddr < TDA18273_REG_MAP_NB_BYTES)
        {
            pRegData = (UInt8 *)(&(pObj->RegMap)) + RegAddr;
        }
        else
        {
            pRegData = &RegData;
        }

        if( (eBusAccess&Bus_NoRead) == False /*&& P_SIO_READ_VALID*/)
        {//printk("%s %d\n",__FILE__, __LINE__);

            /* Read data from TDA18273 */
            err = tda18273_Read/*P_SIO_READ*/(pObj->tUnitW, TDA18273_REG_ADD_SZ, &RegAddr, DataLen, pRegData);
//printk("%s %d\n",__FILE__, __LINE__);
		tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(%x, 1, 0x%02X, %d) failed.", pObj->tUnitW, RegAddr, DataLen));
        }

        if(err == TM_OK && puData != Null)
        {//printk("%s %d\n",__FILE__, __LINE__);

            /* Copy Raw Data */
            *puData = *pRegData;
//printk("%s %d\n",__FILE__, __LINE__);

            /* Get Data */
            RegMask = ( (1 << pBitField->WidthInBits) - 1) << pBitField->PositionInBits;
            *puData &= (UInt8)RegMask;
            *puData = (*puData) >> pBitField->PositionInBits;//printk("%s %d\n",__FILE__, __LINE__);

        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_WriteRegMap                                         */
/*                                                                            */
/* DESCRIPTION: Writes driver RegMap cached data to TDA18273 hardware.        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_WriteRegMap(
    pTDA18273Object_t   pObj,       /* I: Driver object */
    UInt8               uAddress,   /* I: Data to write */
    UInt32              uWriteLen   /* I: Number of data to write */
)
{
    tmErrorCode_t   err = TM_OK;
    pUInt8          pRegData = Null;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_WriteRegMap(%x)", pObj->tUnitW);

    if( uAddress < TDA18273_REG_MAP_NB_BYTES &&
        (uAddress + uWriteLen) <= TDA18273_REG_MAP_NB_BYTES )
    {
        pRegData = (UInt8 *)(&(pObj->RegMap)) + uAddress;
    }
    else
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK /*&& P_SIO_WRITE_VALID*/)
    {
        /* Write data to TDA18273 */
        err = tda18273_Write/*P_SIO_WRITE*/(pObj->tUnitW, TDA18273_REG_ADD_SZ, &uAddress, uWriteLen, pRegData);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Write(%x, 1, 0x%02X, %d) failed.", pObj->tUnitW, uAddress, uWriteLen));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_ReadRegMap                                          */
/*                                                                            */
/* DESCRIPTION: Reads driver RegMap cached data from TDA18273 hardware.       */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
iTDA18273_ReadRegMap(
    pTDA18273Object_t   pObj,       /* I: Driver object */
    UInt8               uAddress,   /* I: Data to read */
    UInt32              uReadLen    /* I: Number of data to read */
)
{
    tmErrorCode_t   err = TM_OK;
    pUInt8          pRegData = Null;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_ReadRegMap(%x)", pObj->tUnitW);

    if( uAddress < TDA18273_REG_MAP_NB_BYTES &&
       (uAddress + uReadLen) <= TDA18273_REG_MAP_NB_BYTES )
    {
        pRegData = (UInt8 *)(&(pObj->RegMap)) + uAddress;
    }
    else
    {
        err = TDA18273_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK /*&& P_SIO_READ_VALID*/)
    {
        /* Read data from TDA18273 */
        err = tda18273_Read/*P_SIO_READ*/(pObj->tUnitW, TDA18273_REG_ADD_SZ, &uAddress, uReadLen, pRegData);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "IO_Read(%x, 1, 0x%02X, %d) failed.", pObj->tUnitW, uAddress, uReadLen));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_Wait                                                */
/*                                                                            */
/* DESCRIPTION: Waits for requested time.                                     */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t 
iTDA18273_Wait(
    pTDA18273Object_t   pObj,   /* I: Driver object */
    UInt32              Time    /* I: time to wait for */
)
{
    tmErrorCode_t   err = TDA18273_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_Wait(%x)", pObj->tUnitW);

    if(1/*P_STIME_WAIT_VALID*/)
    {
        /* Wait Time ms */
        err = tda18273_Wait/*P_STIME_WAIT*/(pObj->tUnitW, Time);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "TIME_Wait(%x, %d) failed.", pObj->tUnitW, Time));
    }

    return err;
}

#ifdef _TVFE_IMPLEMENT_MUTEX

/*============================================================================*/
/* FUNCTION:    iTDA18273_MutexAcquire:                                       */
/*                                                                            */
/* DESCRIPTION: Acquires driver mutex.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_MutexAcquire(
    pTDA18273Object_t   pObj,
    UInt32              timeOut
)
{
    tmErrorCode_t   err = TDA18273_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_MutexAcquire(%x)", pObj->tUnitW);

    if(P_SMUTEX_ACQUIRE_VALID && P_MUTEX_VALID)
    {
        err = P_SMUTEX_ACQUIRE(P_MUTEX, timeOut);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Acquire(%x, %d) failed.", pObj->tUnitW, timeOut));
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_MutexRelease:                                       */
/*                                                                            */
/* DESCRIPTION: Releases driver mutex.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_MutexRelease(
    pTDA18273Object_t   pObj
)
{
    tmErrorCode_t   err = TDA18273_ERR_NULL_CONTROLFUNC;

    tmDBGPRINTEx(DEBUGLVL_INOUT, "iTDA18273_MutexRelease(%x)", pObj->tUnitW);

    if(P_SMUTEX_RELEASE_VALID && P_MUTEX_VALID)
    {
        err = P_SMUTEX_RELEASE(P_MUTEX);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Mutex_Release(%x) failed.", pObj->tUnitW));
    }

    return err;
}

#endif

//  Issue description           :  Modify the NXP driver for 1/2 RF interference 
//                                           
//  Issue severity level            :  ***
//  Issue resolved name         :  Ives
//  Issue date                        :  2011/09/22
#ifdef CONFIG_TUNER_NXP_VIETNAM_PATCH
/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC1:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGC1 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC1(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8          uGAIN,     /* I: AGC GAIN */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);


	if(bEnabled)
	{
	  	  if(uGAIN <= 0xa) //AGC1 fix from 0~A
    		{
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__AGC1_Gain, uGAIN, Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	    	}
	}
	/* set AGC1 gain frozen enable*/
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_3__Force_AGC1_gain, (UInt8)bEnabled, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));


    _MUTEX_RELEASE(TDA18273)


    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC2:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGC2 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC2(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8          uGAIN,     /* I: AGC GAIN */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);


	if(bEnabled)
	{
	  	  if(uGAIN <= 0x3) //AGC2 fix from 0~3
    		{
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__RF_Filter_Gv, uGAIN, Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	    	}
	}
	/* set AGC1 gain frozen enable*/
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RF_Filters_byte_1__Force_AGC2_gain, (UInt8)bEnabled, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));


    _MUTEX_RELEASE(TDA18273)

	//RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_SetAGC2, bEnable = %x , uGAIN = %x\n", (UINT32)bEnabled, (UINT32)uGAIN);
    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC3:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGC3 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC3(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8          uGAIN,     /* I: AGC GAIN */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);


	if(bEnabled)
	{
	  	  if(uGAIN <= 0xff) //AGC3 fix from 0~ 0xff
    		{
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_2__RFAGC_K, uGAIN, Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	    	}
	}
	/* set AGC1 gain frozen enable*/
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_1__RFAGC_K_Bypass, (UInt8)bEnabled, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));


    _MUTEX_RELEASE(TDA18273)

	//RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_SetAGC3, bEnable = %x , uGAIN = %x\n", (UINT32)bEnabled, (UINT32)uGAIN);

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC4:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGC4 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC4(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8          uGAIN,     /* I: AGC GAIN */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);


	if(bEnabled)
	{
	  	  if(uGAIN <= 0x4) //Mixer AGC4 fix from 0~4 (2, 5, 8, 11, 14dB)
    		{
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Cal_byte_5__IR_Mixer_Gain, uGAIN, Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	    	}
	}
	/* set AGC1 gain frozen enable*/
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass, (UInt8)bEnabled, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

    _MUTEX_RELEASE(TDA18273)

	//RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_SetAGC4, bEnable = %x , uGAIN = %x\n", (UINT32)bEnabled, (UINT32)uGAIN);		

    return err;
}

/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC5:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGC5 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC5(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8          uGAIN,     /* I: AGC GAIN */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);

#if 1
	if(bEnabled)
	{
	  	  if(uGAIN <= 0x7) //IFAGC5  fix from 0~7
    		{
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_2__AGC5_Gain, uGAIN, Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	    	}
	}
	/* set AGC1 gain frozen enable*/
        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC5_byte_2__Force_AGC5_gain, (UInt8)bEnabled, Bus_NoRead);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));

#else
                /* Set AGCK Time Constant */

          err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGCK_byte_1__AGCK_Mode, uGAIN, Bus_NoRead);

#endif





    _MUTEX_RELEASE(TDA18273)

	//RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_SetAGC5, bEnable = %x , uGAIN = %x\n", (UINT32)bEnabled, (UINT32)uGAIN);
    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_SetAGC1_ADAP:                                          */
/*                                                                            */
/* DESCRIPTION: Sets AGCa_ADAP value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_SetAGC1_ADAP(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
   TDA18273AGC1_Mode_t          uMode,     /* I: AGC MODE */
    Bool            bEnabled    /* I: Enable of Fix AGC */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_SetIF(%x)", tUnit);


	if(bEnabled && (uMode <= 0x7))
		uMode = uMode;
	else
		uMode = (UInt8)TDA18273_AGC1_Mode_LNA_ADAPT_TOP_ADAPT; //set as default
	
	  
	        err = iTDA18273_Write(pObj, &gTDA18273_Reg_AGC1_byte_2__AGC1_Top_Mode, (UInt8)(uMode&0x7), Bus_NoRead);
        	tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "iTDA18273_Write(%x) failed.", pObj->tUnitW));
	


    _MUTEX_RELEASE(TDA18273)

	//RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_SetAGC1_ADAP, bEnable = %x , uMode = %x\n", (UINT32)bEnabled, (UINT32)uMode);
    return err;
}


/*============================================================================*/
/* FUNCTION:    tmbslTDA18273_GetAGC1:                                          */
/*                                                                            */
/* DESCRIPTION: Gets AGC1 value.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/*============================================================================*/
tmErrorCode_t
tmbslTDA18273_GetAGC1(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt8*          uAGC1_Read     /* I: AGC GAIN */
)
{
    pTDA18273Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;
    /* Get a driver instance */
    err = iTDA18273_GetInstance(tUnit, &pObj);

    _MUTEX_ACQUIRE(TDA18273)

    tmDBGPRINTEx(DEBUGLVL_INOUT, "tmbslTDA18273_GetAGC1(%x)", tUnit);


    *uAGC1_Read = 0;
	
    if(err == TM_OK)
    {
        err = iTDA18273_Read(pObj, &gTDA18273_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read, uAGC1_Read, Bus_RW);
	}

    _MUTEX_RELEASE(TDA18273)


	#if config_tuner_read_enable
	//CTunerReadRegMap();
 	RTD_Log(LOGGER_DEBUG, "tmbslTDA18273_GetAGC1, uAGC1_Read = %x \n", (UINT32)*uAGC1_Read);
	#endif
	
    return err;
}



#endif //END Vietnam




// NXP source code - .\tmbslTDA18273\src\tmbslTDA18273Instance.c

/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18273_Instance.c
 *
 *                %version: 3 %
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *                Christophe CAZETTES
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18273_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 *
*/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#if 0
#include "tmNxTypes.h"
#include "tmNxCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "tmUnitParams.h"
#endif
/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#if 0
#include "tmbslTDA18273.h"

#include "tmbslTDA18273_RegDef.h"
#include "tmbslTDA18273_Local.h"
#include "tmbslTDA18273_Instance.h"
#include "tmbslTDA18273_InstanceCustom.h"
#endif

/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/* Driver instance */
TDA18273Object_t gTDA18273Instance[TDA18273_MAX_UNITS] = 
{
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        #ifndef CPU_C51
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        #endif
        TDA18273_INSTANCE_CUSTOM_0          /* Instance Customizable Settings */
    #ifndef CPU_C51		
    },
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA18273_INSTANCE_CUSTOM_1          /* Instance Customizable Settings */
    #endif
    }
};

/*============================================================================*/
/* Internal functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    iTDA18273_AllocInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Allocates an instance.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_AllocInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number */
    ppTDA18273Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA18273_ERR_ERR_NO_INSTANCES;
    pTDA18273Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Find a free instance */
    for (uLoopCounter = 0; uLoopCounter<TDA18273_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gTDA18273Instance[uLoopCounter];
        if (pObj->init == False)
        {
            err = TM_OK;

            pObj->tUnit = tUnit;
            pObj->tUnitW = tUnit;

            err = iTDA18273_ResetInstance(pObj);

            if(err == TM_OK)
            {
                *ppDrvObject = pObj;
            }
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_DeAllocInstance:                                    */
/*                                                                            */
/* DESCRIPTION: Deallocates an instance.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_DeAllocInstance(
    pTDA18273Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK;

    if(pDrvObject != Null)
    {
        pDrvObject->init = False;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_GetInstance:                                        */
/*                                                                            */
/* DESCRIPTION: Gets an instance.                                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_GetInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number   */
    ppTDA18273Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA18273_ERR_ERR_NO_INSTANCES;
    pTDA18273Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Get instance */
    for (uLoopCounter = 0; uLoopCounter<TDA18273_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gTDA18273Instance[uLoopCounter];
        if (pObj->init == True && pObj->tUnit == GET_INDEX_TYPE_TUNIT(tUnit))
        {
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18273_ResetInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Resets an instance.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18273_ResetInstance(
    pTDA18273Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK ;

    pDrvObject->curPowerState = TDA18273_INSTANCE_CUSTOM_CURPOWERSTATE_DEF;
    pDrvObject->curLLPowerState = TDA18273_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF;
    pDrvObject->uRF = TDA18273_INSTANCE_CUSTOM_RF_DEF;
    pDrvObject->uProgRF = TDA18273_INSTANCE_CUSTOM_PROG_RF_DEF;

    pDrvObject->StandardMode = TDA18273_INSTANCE_CUSTOM_STANDARDMODE_DEF;

    pDrvObject->eHwState = TDA18273_HwState_InitNotDone;

    return err;
}












