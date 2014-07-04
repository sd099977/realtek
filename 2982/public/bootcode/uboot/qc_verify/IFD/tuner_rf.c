#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

#if 0
#ifndef _PACIFIC_H_
#include <pacific.h>
#endif

#ifndef _MONITOR_H_
#include <monitor.h>
#endif

#ifndef _UART_H_
#include <uart.h>
#endif

#include <rtd_lib.h>
#include <timer.h>
#endif

#include "../include/rbusTypes.h"
#include "../include/rbusIFDReg.h"
#include "../include/rbusIFD_27MReg.h"
#include "../include/rbusIFD_49MReg.h"
#include "../include/rbusIFD_108MReg.h"
#include "../include/rbusIFD_AnalogReg.h"
#include "../include/rbusVDTopReg.h"
#include "../include/rbusVDPQReg.h"
#include "../include/rbusAdcReg.h"
#include "../include/rbusPinmuxReg.h"
#include "../include/rbusVDIFDinReg.h"
#include "../include/rbusSYSTEMReg.h"

//Tuner
#include "tuner_atv.h"
#include "tuner_atv_base.h"

//IFD
#include "IFD_qc.h"
#include "ifd_driver.h"
#include "ifd_driver.h"
#include "ifd_magellan_analog.h"
#include "ifd_magellan_cr.h"
#include "ifd_magellan_agc.h"
#include "ifd_magellan_audio.h"
#include "ifd_magellan_video.h"

extern UINT8 g_tuner_bytenum, g_tuner_byte[9];//UINT8 g_tuner_bytenum=9, g_tuner_byte[9]={0,0,0,0,0,0,0,0,0};

//-------------------------------------------------------------
// Local define
//-------------------------------------------------------------
//-------------------------------------------------------------
// Local variable
//-------------------------------------------------------------

//StructTunerDataType	gTunerData[_Tuner_MAX_NO];
//UINT8				gTunerNo = 0;
//UINT8				gTunerActiveID = TUNER_NULL;
UINT32  g_rftuner_curr_freq=0, g_rftuner_curr_freq_search=0;
INT32 g_rftuner_freq_offset=0;
TUNER_ATV_VIDEO_MODE g_rftuner_video_mode;
TUNER_ATV_AUDIO_MODE g_rftuner_audio_mode;


//-------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------
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
	UINT8 IfOutputVppMode)
{
       printk("BuildRFTuner()\n");

	ATV_TUNER_MODULE *pTuner;
	RFTUNER_EXTRA_MODULE *pExtra;

	// Set tuner module pointer.
	*ppTuner = pTunerModuleMemory;

	// Get tuner module.
	pTuner = *ppTuner;

	// Get tuner extra module.
	pExtra = &(pTuner->Extra.rf_tuner);

	// Set tuner type.
	pTuner->TunerType = TUNER_NORMAL;

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
	pTuner->GetTunerType  = RFTunerGetTunerType;
	pTuner->GetDeviceAddr = RFTunerGetDeviceAddress;

	pTuner->Initialize  = RFTunerInit;
	pTuner->SetRfFreqHz = RFTunerSetFreq;
	pTuner->GetRfFreqHz = RFTunerGetFreq;
	pTuner->SetRfFreqSearchHz = RFTunerSetFreqSearch;
	pTuner->GetRfFreqSearchHz = RFTunerGetFreqSearch;
	pTuner->SetRfFreqAfcHz = RFTunerSetFreq;

	pTuner->GetIfFreqHz = RFTunerGetPictureInterFreq;
	pTuner->GeDiverRatio = RFTunerGetDiverRatio;
	pTuner->GetRatioInStepSize = RFTunerGetRatioInStepSize;
	pTuner->CheckBand = RFTunerCheckBand;

	pTuner->SetStandardMode = RFTunerSetStandardMode;
	pTuner->GetStandardMode = RFTunerGetStandardMode;

	// Initialize tuner extra module variables.

	// Set tuner extra module function pointers.
	#if 0
	pExtra->GetIfFreqHz = RFTunerGetPictureInterFreq;
	pExtra->GeDiverRatio = RFTunerGetDiverRatio;
	pExtra->GetRatioInStepSize = RFTunerGetRatioInStepSize;
	pExtra->CheckBand = RFTunerCheckBand;
	#endif

	return;
}

/*=============================================================*/
/**
	This routine will set init.
	@param
	@return
*/

UINT8 RFTunerInit(ATV_TUNER_MODULE *pTuner)
{
       printk("RFTunerInit()\n");
	g_rftuner_curr_freq=0;
	g_rftuner_curr_freq_search=0;
	g_rftuner_freq_offset=0;
	g_rftuner_video_mode= TUNER_ATV_VIDEO_MODE_UNKNOWN;
	g_rftuner_audio_mode= TUNER_ATV_AUDIO_MODE_UNKNOWN;
	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get tuner type.
	@param
	@return
*/
void RFTunerGetTunerType(ATV_TUNER_MODULE *pTuner, UINT8 *pTunerType)
{
	*pTunerType = pTuner->TunerType;

	return;
}

/*=============================================================*/
/**
	This routine will get device address.
	@param
	@return
*/
void RFTunerGetDeviceAddress(ATV_TUNER_MODULE *pTuner, UINT8 *pDeviceAddr)
{
	*pDeviceAddr = pTuner->DeviceAddr;

	return;
}

/*=============================================================*/
/**
	This routine will set TV to specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/

UINT8 RFTunerSetFreq(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz)
{
	UINT8 setting[10], i;
	UINT8 tunerBANDno;
	UINT8 tunerRegno;
	UINT8 tunerBand;
	UINT16 divider_freq;
	I2C_MODULE *pI2CModule;
	UINT32 RfFreqHz_Set;
	UINT8 Retry=10;
	pI2CModule = pTuner->pI2cModule;

	for(i=0;i<10;i++) setting[i]=0;

	RfFreqHz_Set = RfFreqHz + g_rftuner_freq_offset;

	RFTunerGetDiverRatio(pTuner, RfFreqHz_Set, &divider_freq);//CTunerGetDiverRatio(RfFreqHz);

	pTuner->IsRfFreqHzSet = YES;

       g_rftuner_curr_freq = RfFreqHz;

	tunerBANDno = GET_ATV_TUNER_BANDNO();
	tunerRegno = GET_ATV_TUNER_REGNOPERBAND() ;
	pI2CModule->len= tunerRegno + 2;
	setting[0] = (UINT8)((divider_freq>>8)& 0xff);
	setting[1] = (UINT8)(divider_freq & 0xff);
	RFTunerCheckBand(pTuner, RfFreqHz_Set, &tunerBand);
	//Check Rf Input Switch
	if(GET_ATV_TUNER_RFINPUTSWITCHUSEDTAG()==_TRUE)
	{
		if(pTuner->RfInput_Sel == TUNER_INPUT_SEL_AIR)
		{
			GET_ATV_TUNER_REGISTERBYTE(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=GET_ATV_TUNER_REGISTERBYTE(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)|GET_ATV_TUNER_RFINPUTLOCATION();
			GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=
				GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)|GET_ATV_TUNER_RFINPUTLOCATION();
		}
		else //TUNER_INPUT_SEL_CATV or NULL
		{
			GET_ATV_TUNER_REGISTERBYTE(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=GET_ATV_TUNER_REGISTERBYTE(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)&(~(GET_ATV_TUNER_RFINPUTLOCATION()));
			GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=
				GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)&(~(GET_ATV_TUNER_RFINPUTLOCATION()));

		}
	}
	//-----------------------------------------------------------------------------------
	if(0/*GET_ATV_TUNER_TYPE()==TUNER_NORMAL*/)
	{
			for(i=0; i<tunerRegno; i++)
				setting[i+2] = GET_ATV_TUNER_REGISTERBYTESEARCH(i+tunerRegno*tunerBand);
			pI2CModule->i2c_write(pI2CModule, setting);

			for(i=0;i<Retry;i++)
			{
				if(RFTunerReadStatus(pTuner)==_TRUE)
				{
					IFD_DEBUG_MSG(IFD_MSG_SETCH,"\n[IFD] Tuner FL state OK at  %d times!!\n",i);
					break;
				}
				else
				{
					IFD_DEBUG_MSG(IFD_MSG_SETCH,"\n[IFD] Tuner FL state still not ready at  %d times!!\n",i);
					ScalerTimer_DelayXms(20);
				}
			}
			pI2CModule->len= tunerRegno + 2;
			for(i=0; i<tunerRegno; i++)
				setting[i+2] = GET_ATV_TUNER_REGISTERBYTE(i+tunerRegno*tunerBand);
			pI2CModule->i2c_write(pI2CModule, setting);
	}
	else
	{
			for(i=0; i<tunerRegno; i++)
				setting[i+2] = GET_ATV_TUNER_REGISTERBYTE(i+tunerRegno*tunerBand);
			pI2CModule->i2c_write(pI2CModule, setting);
	}

	g_tuner_bytenum = GET_ATV_TUNER_REGNOPERBAND() +3;
	if(g_tuner_bytenum>9) g_tuner_bytenum = 9;
	g_tuner_byte[0] = GET_ATV_TUNER_I2C_ADD();
	for(i=1;i<g_tuner_bytenum;i++)
		g_tuner_byte[i] = setting[i-1];
	return _TRUE;
}

/*=============================================================*/
/**
	This routine will set TV to specific frequency  in Search mode
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerSetFreqSearch(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz)
{
	UINT8 setting[10], i;
	UINT8 tunerBANDno;
	UINT8 tunerRegno;
	UINT8 tunerBand;
	UINT16 divider_freq;
	I2C_MODULE *pI2CModule;
	UINT32 RfFreqHz_Set;
	pI2CModule = pTuner->pI2cModule;

	RfFreqHz_Set = RfFreqHz + g_rftuner_freq_offset;

	for(i=0;i<10;i++) setting[i]=0;

	RFTunerGetDiverRatio(pTuner, RfFreqHz_Set, &divider_freq);//CTunerGetDiverRatio(RfFreqHz);

	pTuner->IsRfFreqHzSet = YES;

	g_rftuner_curr_freq_search = RfFreqHz;

	tunerBANDno = GET_ATV_TUNER_BANDNO();
	tunerRegno = GET_ATV_TUNER_REGNOPERBAND() ;
	pI2CModule->len= tunerRegno + 2;

	setting[0] = (UINT8)((divider_freq>>8)& 0xff);
	setting[1] = (UINT8)(divider_freq & 0xff);
	RFTunerCheckBand(pTuner, RfFreqHz_Set, &tunerBand);
	//Check Rf Input Switch
	if(GET_ATV_TUNER_RFINPUTSWITCHUSEDTAG()==_TRUE)
	{
		if(pTuner->RfInput_Sel == TUNER_INPUT_SEL_AIR)
			GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=
				GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)|GET_ATV_TUNER_RFINPUTLOCATION();
		else //TUNER_INPUT_SEL_CATV or NULL
			GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)=
				GET_ATV_TUNER_REGISTERBYTESEARCH(GET_ATV_TUNER_RFINPUTBYTE()+tunerRegno*tunerBand)&(~(GET_ATV_TUNER_RFINPUTLOCATION()));
	}
	//-----------------------------------------------------------------------------------
	for(i=0; i<tunerRegno; i++)
		setting[i+2] = GET_ATV_TUNER_REGISTERBYTESEARCH(i+tunerRegno*tunerBand);

	pI2CModule->i2c_write(pI2CModule, setting);

	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get TV to current frequency.
	@param			void
	@return 			Return the freq	frequency
*/

UINT8 RFTunerGetFreq(ATV_TUNER_MODULE *pTuner, UINT32 *pRfFreqHz)
{
	*pRfFreqHz =  g_rftuner_curr_freq;

	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get TV to current frequency.
	@param			void
	@return 			Return the freq	frequency
*/

UINT8 RFTunerGetFreqSearch(ATV_TUNER_MODULE *pTuner, UINT32 *pRfFreqHz)
{
	*pRfFreqHz =  g_rftuner_curr_freq_search;

	return _TRUE;
}
/*=============================================================*/
/**
	This routine will set TV standard mode
	@param			video_mode/audio_mode		TUNER_ATV_VIDEO_MODE/TUNER_ATV_AUDIO_MODE
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerSetStandardMode(ATV_TUNER_MODULE *pTuner, TUNER_ATV_VIDEO_MODE video_mode, TUNER_ATV_AUDIO_MODE audio_mode)
{
	g_rftuner_video_mode = video_mode;
	g_rftuner_audio_mode = audio_mode;

	if(g_rftuner_video_mode==TUNER_ATV_VIDEO_MODE_SECAMLA) g_rftuner_freq_offset = SECAM_LA_FREQ_OFFSET;
	else {
		/*if(GET_TUNER_ID() == TUNER_SHARP_2403_DIF)
			g_rftuner_freq_offset=9000; //FIX the uncompitable SAW in SHARP 2403
		else*/
			g_rftuner_freq_offset=0;
	}

	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get TV standard mode
	@param			none
	@return 			Return video_mode/audio_mode		TUNER_ATV_VIDEO_MODE/TUNER_ATV_AUDIO_MODE
*/
UINT8 RFTunerGetStandardMode(ATV_TUNER_MODULE *pTuner, TUNER_ATV_VIDEO_MODE* video_mode, TUNER_ATV_AUDIO_MODE* audio_mode)
{
	*video_mode=g_rftuner_video_mode;
	*audio_mode=g_rftuner_audio_mode;

	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get divider ratio for specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerGetDiverRatio(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT16 *DiverRatio)
{
	*DiverRatio = (UINT16)((RfFreqHz + (UINT32)GET_ATV_TUNER_PIF())/(UINT32)GET_ATV_TUNER_RATIOSTEPSIZE());
	return _TRUE;
}

/*=============================================================*/
/**
	This routine will check tuner receiving frequency band(VHF Low¡BVHF High¡BUHF).
	@param 			freq	       					tuner receiving frequency(divider)
	@return 			Return tuner receiving frequency band(01¡B02 or 04)
*/
UINT8 RFTunerCheckBand(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT8 *Band)
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
UINT32 RFTunerNToFrequencyNum(UINT16 N)
{
	UINT32 freq;
	// according to N = (freq + 38.9MHz) / 62.5 KHz
	// freq = N * 0.0625 MHz - 38.9 MHz
	// 100 * freq = N * 6.25 - 3890
	// 100 * freq = N * (25 / 4) - 3890

	// freq = N * 0.03125 MHz - 38.9 MHz
	// 100 * freq = N * 3.125 - 3890
	// 100 * freq = N *(12.5 / 4) - 3890

	freq = (UINT32)N * GET_ATV_TUNER_RATIOSTEPSIZE();
	freq = (freq - GET_ATV_TUNER_PIF()) * 100;
	return freq;
}
/*=============== Read Tuner I2C data ===========================*/
UINT8 RFTunerReadStatus(ATV_TUNER_MODULE *pTuner)
{
	UINT8 DataArray=0;
	I2C_MODULE *pI2CModule;

	pI2CModule = pTuner->pI2cModule;
	pI2CModule->len=1;
	pI2CModule->i2c_read(pI2CModule,&DataArray);

	if((DataArray&(GET_ATV_TUNER_FLSTATUSBIT()))==GET_ATV_TUNER_FLSTATUSBIT())   //return tuner FL status
		return _TRUE;
	else
		return _FALSE;

}
/*=============================================================*/
UINT8 RFTunerGetRatioInStepSize(ATV_TUNER_MODULE *pTuner, UINT16 *RatioInStepSize)
{
	*RatioInStepSize = GET_ATV_TUNER_RATIOSTEPSIZE();
	return _TRUE;
}

/*=============================================================*/
UINT8 RFTunerGetPictureInterFreq(ATV_TUNER_MODULE *pTuner, UINT32 *pIfFreqHz)
{
	*pIfFreqHz = GET_ATV_TUNER_PIF()+ g_rftuner_freq_offset;
	return _TRUE;
}

/*=============================================================*/
UINT32 RFTunerGetChanelMaxFreq(void)
{
	return GET_ATV_TUNER_MAXFREQ();
}

/*=============================================================*/
UINT32 RFTunerGetChanelMinFreq(void)
{
	return GET_ATV_TUNER_MINFREQ();
}

/*=============================================================*/
UINT32 RFTunerGetVHF_LowFreq(void)
{
	return GET_ATV_TUNER_VHF_LOWFREQ();
}

/*=============================================================*/
UINT32 RFTunerGetVHF_HighFreq(void)
{
	return GET_ATV_TUNER_VHF_HIGHFREQ();
}
