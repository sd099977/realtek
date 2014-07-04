/*=============================================================
 * Copyright (c)      Realtek Semiconductor Corporation, 2013 * 
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/ 
/**
 * @file audio_app.h
 * This file is a header file for LasVegas Audio PostPorcessing library.
 * @author Clayton Wu , <clayton@realtek.com>
 * @date 2014.1.8
 * @version 0.1
 *
 */
//#include "rbusTypes.h"
#ifndef __AUDIO_QC_H__
#define __AUDIO_QC_H__

#ifdef __cplusplus
extern "C" {
#endif
#define ALIGN64 __attribute__ ((aligned(64)))
/*======================== Audio Config =========================*/ 
#define config_AudioInit
#define config_AudioPath_Analog
#define config_AudioPath_Digital
#define config_AudioDMA
#define config_AudioFunction
#undef config_Audio_biascurrent_30u

/*======================== Constant ===========================*/ 

#define _BIT0 (0x1)
#define _BIT1 (0x2)
#define _BIT2 (0x4)
#define _BIT3 (0x8)
#define _BIT4 (0x10)
#define _BIT5 (0x20)
#define _BIT6 (0x40)
#define _BIT7 (0x80)
#define _BIT8 (0x100)
#define _BIT9 (0x200)

#define _BIT10 (0x400)
#define _BIT11 (0x800)
#define _BIT12 (0x1000)
#define _BIT13 (0x2000)
#define _BIT14 (0x4000)
#define _BIT15 (0x8000)
#define _BIT16 (0x10000)
#define _BIT17 (0x20000)
#define _BIT18 (0x40000)
#define _BIT19 (0x80000)

#define _BIT20 (0x100000)
#define _BIT21 (0x200000)
#define _BIT22 (0x400000)
#define _BIT23 (0x800000)
#define _BIT24 (0x1000000)
#define _BIT25 (0x2000000)
#define _BIT26 (0x4000000)
#define _BIT27 (0x8000000)
#define _BIT28 (0x10000000)
#define _BIT29 (0x20000000)

#define _BIT30 (0x40000000)
#define _BIT31 (0x80000000)

#define DMABUFSAMPLES (8192) 	// 8192 samples, 8192*4 bytes = 32kbytes
#define DMACHANNELS (2) 		// 2 channels

/*======================== Type Defines ========================*/ 
typedef enum {
	//DSFIFO source select
	TV_audio					=0x0,
 	ADC						=0x1,
 	SPDIFin					=0x2,
	I2Sch01					=0x4,
 	I2Sch23					=0x5,
	I2Sch45					=0x6,
	I2Sch67					=0x7,
}QC_FIFO_SrcSel;

typedef enum {
	//DSFIFO source select
	BF_AVC1					=0x0,
 	BF_AVC2					=0x1,
 	AF_AVC2					=0x2,
	BF_TSDVC				=0x3,
 	AF_TSDVC				=0x4,
	AF_AVC1					=0x5
}QC_DAC_SrcSel;

typedef enum {
	//PlayBack/TimeShiting path select
	TS_Path					=0x0,
 	PB_Path					=0x1,
}QC_Path_Sel;

typedef enum {
	//R/L channel select
	CHL						=0x0,
 	CHR						=0x1,
}QC_LRCH_Sel;

typedef enum {
	DMA_nonPCM				=0x1,
	DMA_PCM				=0x0,
}QC_DMA_Format;

typedef enum {
	DMA_Play				=0x1,
	DMA_Bypass 				=0x0,
}QC_DMA_PATH;

typedef enum {
	pre_HWP					=0x0,
	post_HWP				=0x1,
	test_RX_FIFO				=0x3
}QC_DMA_SrcSel;

typedef enum {
	zeros					=0x0,
	triangular_wave			=0x1,
	increase_count_wave		=0x2,
}QC_InternalPeattern_Sel;

typedef enum {
	oneCH					=0x1,
	twoCH					=0x2,
	threeCH					=0x3,
	fourCH					=0x4,
	fiveCH					=0x5,
	sixCH					=0x6,
	sevenCH					=0x7,
	eightCH					=0x8,
}QC_ChannelNumber_Sel;

typedef enum {
	CH0						=0x0,
	CH1						=0x1,
	CH2						=0x2,
	CH3						=0x3,
	CH4						=0x4,
	CH5						=0x5,
	CH6						=0x6,
	CH7						=0x7,
}QC_Channel_Sel;

typedef enum {
	PrePeakDetect			=0x0,
	PostPeakDetect			=0x1,
}QC_PeakDetect_Sel;

typedef enum {
	//I2S IN source select
	I2S_normal            	 		=0x0,
	I2S_HDMI		  		=0x1,
	I2S_loopback			 	=0x2,
	I2S_disable			 	=0x3,
}QC_I2SIO_SrcSel;

typedef enum {
	//SPDIF IN/Out source select
	SPDIF_normal              		=0x0,
	SPDIF_HDMI		 		=0x1,
	SPDIF_loopback			=0x2,
	SDIF_disable			 	=0x3,
}QC_SPDIFIO_SrcSel;

typedef enum {
	//Analog input/output source select
	AIN1					=0x0,
	AIN2					=0x1,
	AIN3					=0x2,
	AIN4					=0x4,
	AIN5					=0x5,
	AIO1					=0x6,
	AIO2					=0x7,
	ADCFE					=0x8,
	DAC0					=0x9,
	DAC1					=0x10,
	AIO						=0x11,
	
	MUTEALL					=-1,
}QC_AIO_SrcSel;

typedef enum {
	//QC test case select
	PCB_QFP				=0x0,
	PCB_BGA				=0x1,
}QC_AudioTestcase;

typedef struct {
	UINT32 src_from;
	//UINT32 tv_bu_format;
	UINT32 pcm_format;
	//UINT32 lsb_random;
	UINT32 wr_channels;
	UINT32 rd_channels;
	//UINT32 hbr_mode;
	//UINT32 hbr_wr_channels;
	UINT32 samples;
	//UINT32 dma_pattern;
	UINT32 is_playback;
}QC_DMA_CFG;

/*===================== Routines Prototype ====================*/
// Register R/W
static void WriteRegister(UINT32 address, UINT32 data);
static UINT32 ReadRegister(UINT32 address);
static void WriteMaskRegister(UINT32 address, UINT32 mask, UINT32 data);
void aud_Delay(int delayMS);

//config_AudioInit
void aud_DrPLL();
void aud_DrClock();
void aud_DrBaseband();
void aud_DrGpio();
void aud_DrSIF();
void aud_DrInitialize();

//config_AudioPath_Digital
/*---I2S---*/
void dx_I2sSetInputPri(QC_I2SIO_SrcSel src_select);
UINT32 dx_I2sGetWordLength(UINT32 is_sec_module);
UINT32 dx_I2sGetSampleRate();
void dx_I2sSetOutput(QC_I2SIO_SrcSel  src_select, UINT32 pcm_src);
/*---SPDIF---*/
void dx_SpdifSetInput(QC_SPDIFIO_SrcSel src_select);
UINT32 dx_SpdifGetSampleRate();
void dx_SpdifSetOutput(QC_SPDIFIO_SrcSel src_select, UINT32 pcm_src);

//config_AudioPath_Analog
void dx_AdcSetInput(QC_AIO_SrcSel src_select);
void dx_FifoPlay_CH01(QC_FIFO_SrcSel play_src_select);
void dx_FifoTs_CH01(QC_FIFO_SrcSel ts_src_select);
void dx_Dac0SetOutput(UINT32 src_select);
void dx_Dac1SetOutput(UINT32 src_select);
void dx_HPSetOutput(QC_AIO_SrcSel src_select);
void dx_LOSetOutput(QC_AIO_SrcSel src_select);
void dx_AIO1SetOutput(QC_AIO_SrcSel src_select);
void dx_AIO2SetOutput(QC_AIO_SrcSel src_select);

//config_AudioFunction
UINT32 dx_AutotSineCheck(UINT32 amplitude, UINT32 cntthd, UINT32 frequency ,QC_LRCH_Sel ch_select);
UINT32 dx_PeakDetectSet(QC_PeakDetect_Sel peakdetect_select, QC_FIFO_SrcSel src_select, QC_LRCH_Sel ch_select);

//config_AudioDMA
void dx_DmaTsPath(QC_DMA_PATH is_ts_dma);
void dx_DmaDsPath(QC_DMA_PATH is_play_dma);
void dx_InternalPatternGenerator(QC_InternalPeattern_Sel test_case, QC_ChannelNumber_Sel chs);
void dx_InternalPatternGeneratorTS(QC_InternalPeattern_Sel test_case, QC_ChannelNumber_Sel chs);

/*---QC test function---*/
//i2s internal path samplerate detection
UINT32 aud_esd_I2s();
//spdif internal path samplerate detection
UINT32 aud_esd_Spdif();
//all of aud_baseband_PeakDetection ( analog path peak detection ) is added ycwu
UINT32 aud_baseband_PeakDetection(QC_AudioTestcase test_case);
UINT32 aud_baseband_AutoSineCheck(QC_AudioTestcase test_case);
int aud_QcDma();


#endif

