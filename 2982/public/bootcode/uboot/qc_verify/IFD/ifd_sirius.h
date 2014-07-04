#ifndef _IFD_PACIFICP_H_
#define _IFD_PACIFICP_H_

//********************************************************************
//CONFIG definition
//********************************************************************
#undef CONFIG_ATV_IFD_VERIFY

#ifdef __cplusplus
extern "C" {
#endif

//********************************************************************
//Include file
//********************************************************************

#if 0
#include "dragon.h"
#include "global.h"
#include "scaler_timer.h"
#include "audio/audio_api.h"
#include <misc.h>
#include "struct.h"
#include "hwtimer.h"
#include "scaler_timer.h"
#endif

#include <qc_verify_common.h>

//rbus
#include "../include/rbusTypes.h"
#include "../include/rbusIFDReg.h"
#include "../include/rbusIFD_27MReg.h"
#include "../include/rbusIFD_49MReg.h"
#include "../include/rbusIFD_108MReg.h"
#include "../include/rbusIFD_AnalogReg.h"
#include "../include/rbusVDTopReg.h"
#include "../include/rbusVDPQReg.h"
#include "../include/audio_qc_rbus.h"
#include "../include/rbusAdcReg.h"
#include "../include/rbusVDIFDinReg.h"
#include "../../../uboot/include/asm/arch-rtd298x/rbus/rbusPinmuxReg.h"
#include "../../../uboot/include/asm/arch-rtd298x/rbus/crt_sys_reg.h"

//I2C
#include "../../uboot/include/rtk_i2c_lib.h"

//Tuner
#include "tuner_atv.h"
#include "tuner_atv_base.h"

//IFD
#include "IFD_qc.h"

#if 1//yuki: need to modify
	#ifdef CONFIG_TUNER_XUGUANG_HFT3_86H_115CW
	#include "../drivers/tv/tuner/tuner_rf.h"
	#elif defined(CONFIG_TUNER_LOWIF_TYPE)
       #ifdef CONFIG_TUNER_NXP_TDA18273
       #include "tuner_nxp_tda18273.h"
       #elif defined(CONFIG_TUNER_SONY_RX201V050)
       #include "../drivers/tv/tuner/tuner_sony_rx201_v050.h"
       #elif defined(CONFIG_TUNER_RAFEL_RT810)
       #include "../drivers/tv/tuner/tuner_rafael_rt810.h"
       #elif defined(CONFIG_TUNER_MAXIM_MAX3543)
       #include "../drivers/tv/tuner/tuner_maxim_max3543.h"
       #elif defined(CONFIG_TUNER_MAXLINEAR_MXL301RF)
       #include "../drivers/tv/tuner/tuner_maxlinear_mxl301rf.h"
       #elif defined(CONFIG_TUNER_XCEIVE_XC5200)
       #include "../drivers/tv/tuner/tuner_xceive_xc5200.h"
       #elif defined(CONFIG_TUNER_ENRT_EN4020)
       #include "../drivers/tv/tuner/tuner_entr_en4020.h"
       #elif defined(CONFIG_TUNER_FRESCO_FM2150)
       #include "../drivers/tv/tuner/tuner_fresco_fm2150.h"
	#elif defined(CONFIG_TUNER_SILICONLABS_SI2156)
       #include "../drivers/tv/tuner/tuner_siliconlabs_si2156.h"
	#endif			
	#endif
#endif


//********************************************************************
//System Function Define
//********************************************************************
//debug, it should be removed if audio driver is ready.


#if 0//yuki: need to modify, use chip id to enable or disable
#ifndef UINT8
typedef  unsigned char UINT8;
#endif
#ifndef UINT16
typedef  unsigned short UINT16;
#endif
#ifndef UINT32
typedef  unsigned int UINT32;
#endif
#ifndef UINT64
typedef unsigned long long      	UINT64;
#endif
#endif

#if 0//yuki: need to modify, use chip id to enable or disable
#define rtd_outl(x, y)     								IoReg_Write32(x,y)
#define rtd_inl(x)     									IoReg_Read32(x)
#define rtd_maskl(x, y, z)     							IoReg_Mask32(x,y,z)
#endif

#define bool char

#ifndef rtd_maskl
#define rtd_maskl rtdf_maskl
#endif

#ifndef CONFIG_Tuner_Max_NUMBER
#ifdef AFEIF_RTKATV_TUNER_MAX
#define CONFIG_Tuner_Max_NUMBER AFEIF_RTKATV_TUNER_MAX
#else
#define CONFIG_Tuner_Max_NUMBER 1
#endif
#endif

#ifndef CONFIG_Tuner_Max_NUMBER
#define CONFIG_Tuner_Max_NUMBER 1
#endif
#ifndef _Tuner_MAX_NO
#define _Tuner_MAX_NO CONFIG_Tuner_Max_NUMBER
#endif

#define IFD_CODE 
#define IFD_XDATA 
#define _TRUE 1
#define _FALSE 0
//#define _SUCCESS 1
#define I2C_MASTER0		1
#define ROS_ENTER_CRITICAL() 
#define ROS_EXIT_CRITICAL()
//#define ScalerTimer_DelayXms(ms) ScalerTimer_DelayXms(ms)

//********************************************************************
//Debug Msg definition
//********************************************************************
typedef enum {
	IFD_MSG_NONE=_ZERO,
	IFD_MSG_TUNER=_BIT0,
	IFD_MSG_SCANCH=_BIT1,
	IFD_MSG_SETCH=_BIT2,
	IFD_MSG_AUTO=_BIT3,
	IFD_MSG_AFC=_BIT4,
	IFD_MSG_ADAPTIVE_TARGET=_BIT5,
	IFD_MSG_CR_STATE=_BIT6,
	IFD_MSG_STRONG_SIGNAL=_BIT7,
	IFD_MSG_DUMP_REG=_BIT8,
	IFD_MSG_AGC_VAR=_BIT9,
	IFD_MSG_INIT=_BIT10,
	IFD_MSG_OTHERS=_BIT15,
	IFD_MSG_ALL_MSG=0xFFFF,
}IFD_MSG_LEVEL;

extern IFD_MSG_LEVEL g_ifd_msg_level;
	
#define IFD_CALLER(ifd_level)  \
{                                                                                      \
    if((g_ifd_msg_level&ifd_level)!=0)                            \
    {                                                                                  \
    	 asm("or $5,$31,$0");                                                 \
    	 printf( "$$$$$$IFD API called at %x --- ");                 \
    }                                                                                  \
}
#define IFD_DEBUG_MSG(ifd_level,string,args...)\
{									\
	if(((g_ifd_msg_level&ifd_level)!=0)) {	\
		if(ifd_level==IFD_MSG_TUNER)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][TUNER]");				\
		}								\
		if(ifd_level==IFD_MSG_SCANCH)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][SCAN_CH]");				\
		}								\
		if(ifd_level==IFD_MSG_SETCH)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][SET_CH]");				\
		}								\
		if(ifd_level==IFD_MSG_AUTO)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][SET_CH]");				\
		}								\
		if(ifd_level==IFD_MSG_AFC)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][AFC]");				\
		}								\
		if(ifd_level==IFD_MSG_ADAPTIVE_TARGET)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][ADAPTIVE_TARGET]");				\
		}								\
		if(ifd_level==IFD_MSG_CR_STATE)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][CR_STATE]");				\
		}								\
		if(ifd_level==IFD_MSG_STRONG_SIGNAL)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][STRONG_SIGNAL]");				\
		}								\
		if(ifd_level==IFD_MSG_DUMP_REG)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][DUMP_REG]");				\
		}								\
		if(ifd_level==IFD_MSG_AGC_VAR)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][AGC_VAR]");				\
		}								\
		if(ifd_level==IFD_MSG_INIT)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][INIT]");				\
		}								\
		if(ifd_level==IFD_MSG_OTHERS)	\
		{								\
			ROSPrintf("\n[IFD_DEBUG][OTHERS]");				\
		}								\
		ROSPrintf(string, ##args);				\
	}\
}	

//********************************************************************
//Version ID definition
//********************************************************************
#define IFD_CHIP_VER()      (rtd_inl(SYSTEM_SC_VERID_VADDR)&0xFFFF)
typedef enum _IFD_CHIP_VERID {
	IFD_CHIP_VERID_A=0x0000,
	IFD_CHIP_VERID_B=0x0001,
	IFD_CHIP_VERID_C=0x0002,
	IFD_CHIP_VERID_UNKNOWN=0xFFFF,
} IFD_CHIP_VERID;
//********************************************************************
//Timer Event definition
//********************************************************************
#define IFD_ScalerTimer_CancelTimerEvent(event) ScalerTimer_CancelTimerEvent(event)
#define IFD_ReactiveTimerEvent(ms, event) ScalerTimer_ReactiveTimerEvent(ms, event)
//********************************************************************
//Other definition
//********************************************************************
extern UINT16  group_delay_table1[];
extern UINT16  group_delay_table2[];
extern UINT16  group_delay_table3[];
extern UINT16  group_delay_table4[];
extern UINT16  group_delay_table5[];

typedef enum _IFD_DEBUG_MODE_CLK_CONFIG {
	CLK54=0,
	CLK49,
	CLK108,
} IFD_DEBUG_MODE_CLK_CONFIG;

typedef enum _IFD_DEBUG_MODE_CONFIG { //Please sync with ifd_factorymode.cpp 
	ADC_OUT=0,
	FIFO_OUT,
	DGAIN_OUT,
	DEMOD_OUT,
	CVBS_OUT,
	AGC_RF,
	AGC_IF,
	AGC_LOOP1_LPF_OUT,
	AGC_LOOP1_MAX_OUT,
	AGC_LOOP1_DGAIN,
	AGC_LOOP1_DIFF_ERR,
	AGC_LOOP1_ERR0,
	AGC_LOOP1_PEAK_ERR,
	AGC_LOOP1_PEAK,
	AGC_LOOP1_LPF_OUT_DGAINED,
	AGC_LOOP2_DGAIN,
	AGC_LOOP2_DIFF_ERR,
	AGC_LOOP2_PEAK_ERR,
	AGC_LOOP2_PEAK,	
	CR_COS,
	CR_LPF_OUT,
	CR_PHASE_ERROR,
	SIF_OUT,
	IFD_RESERVE_1,
	IFD_RESERVE_2,
	IFD_DMA_ALL,	
} IFD_DEBUG_MODE_CONFIG;
/*=============================================================*/
/**
 * drvif_ifd_dma_data
 *
 *
 * @param <debug_mode>
 * @return { void }
 */
void drvif_ifd_dma_data(IFD_DEBUG_MODE_CONFIG debug_mode);


//=================================================================
//IFD local driver
//=================================================================
#include "ifd_sirius_analog.h"
#include "ifd_sirius_cr.h"
#include "ifd_sirius_agc.h"
#include "ifd_sirius_audio.h"
#include "ifd_sirius_video.h"

#if 0
#ifdef CONFIG_ATV_IFD_VERIFY
#include "if_demod/ifd_pacificp_verify.h"
#endif
#endif

void drv_ifd_tuner_data_init(void);
void drv_ifd_tuner_BuildTuner(void);
void drv_ifd_user_data_init(void);
void drv_ifd_dma_data_sel_en(bool dma_data_sel_en);
void drv_ifd_debug_mode(IFD_DEBUG_MODE_CLK_CONFIG clk,UINT8 debug_mode);



#ifdef __cplusplus
}
#endif

#endif // _IFD_PACIFICP_H_







