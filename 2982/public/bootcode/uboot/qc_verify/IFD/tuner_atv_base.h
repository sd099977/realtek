#ifndef _TUNER_ATV_BASE_H
#define _TUNER_ATV_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#define YES 1
#define NO 0
#define bool char

typedef struct ATV_TUNER_MODULE_TAG ATV_TUNER_MODULE;
typedef struct SYS_MODULE_TAG SYS_MODULE;
typedef struct I2C_MODULE_TAG I2C_MODULE;

typedef enum {
	I2C_NOADDR=0,
	I2C_ADDR_8=1,
	I2C_ADDR_16=2,
	I2C_CMD_CONTINUE=3, // the i2c command continual sending
} I2C_ADDR_TYPE;

typedef enum TUNER_INPUT_SEL {
        TUNER_INPUT_SEL_CATV = 0,
	 TUNER_INPUT_SEL_AIR = 1,
}TUNER_INPUT_SEL;

typedef enum TV_SCAN_FLOW_TYPE {
        TV_SCAN_FLOW_TYPE_ATV_DTV_indep = 0, // scan all RF freq (40M ~ 900M) in ATV mode, then scan all RF freq in DTV mode
	 TV_SCAN_FLOW_TYPE_ADAD = 1, // scan alternativlye between ATV and DTV per frequency
}TV_SCAN_FLOW_TYPE;

typedef enum {
	TUNER_ATV_VIDEO_MODE_NTSC=0,
	TUNER_ATV_VIDEO_MODE_PAL=1,
	TUNER_ATV_VIDEO_MODE_SECAM,
	TUNER_ATV_VIDEO_MODE_SECAMLA,
	TUNER_ATV_VIDEO_MODE_SCAN=0xfe,
	TUNER_ATV_VIDEO_MODE_UNKNOWN=0xff,
} TUNER_ATV_VIDEO_MODE;

typedef enum {
	TUNER_ATV_AUDIO_MODE_MN=0,
	TUNER_ATV_AUDIO_MODE_B=1,
	TUNER_ATV_AUDIO_MODE_GH,
	TUNER_ATV_AUDIO_MODE_I,
	TUNER_ATV_AUDIO_MODE_DK,
	TUNER_ATV_AUDIO_MODE_L,
	TUNER_ATV_AUDIO_MODE_LA,
	TUNER_ATV_AUDIO_MODE_FM_RADIO,
	TUNER_ATV_AUDIO_MODE_UNKNOWN=0xff,
} TUNER_ATV_AUDIO_MODE;
//Function pointer definition
//*******************************************************
//
// Tuner function
//
//*******************************************************
typedef void
(*ATV_TUNER_FP_GET_TUNER_TYPE)(
	ATV_TUNER_MODULE *pTuner,
	UINT8 *pTunerType
	);
typedef void
(*ATV_TUNER_FP_GET_DEVICE_ADDR)(
	ATV_TUNER_MODULE *pTuner,
	UINT8 *pDeviceAddr
	);
typedef UINT8
(*ATV_TUNER_FP_INITIALIZE)(
	ATV_TUNER_MODULE *pTuner
	);
typedef UINT8
(*ATV_TUNER_FP_SET_RF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz
	);
typedef UINT8
(*ATV_TUNER_FP_GET_RF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pRfFreqHz
	);
typedef UINT8
(*ATV_TUNER_FP_SET_RF_FREQ_SEARCH_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz
	);
typedef UINT8
(*ATV_TUNER_FP_GET_RF_FREQ_SEARCH_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pRfFreqHz
	);
typedef UINT8
(*ATV_TUNER_FP_SET_RF_FREQ_AFC_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz
	);

typedef UINT8
(*ATV_TUNER_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pIfFreqHz
	);
typedef UINT8
(*ATV_TUNER_FP_GET_DIVER_RATIO)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz,
	UINT16 *DiverRatio
	);
typedef UINT8
(*ATV_TUNER_FP_GET_RATIO_IN_STEPSIZE)(
	ATV_TUNER_MODULE *pTuner,
	UINT16 *RatioInStepSize
	);
typedef UINT8
(*ATV_TUNER_FP_CHECK_BAND)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz,
	UINT8 *Band
	);
typedef UINT8
(*ATV_TUNER_FP_SET_STD_MODE)(
	ATV_TUNER_MODULE *pTuner,
	TUNER_ATV_VIDEO_MODE video_mode,
	TUNER_ATV_AUDIO_MODE audio_mode
	);
typedef UINT8
(*ATV_TUNER_FP_GET_STD_MODE)(
	ATV_TUNER_MODULE *pTuner,
	TUNER_ATV_VIDEO_MODE* video_mode,
	TUNER_ATV_AUDIO_MODE* audio_mode
	);
//*******************************************************
//
// I2C function
//
//*******************************************************
typedef UINT8
(*I2C_FP_WRITE)(
	I2C_MODULE *pI2CModule,
	UINT8 *pWriteArray
	);
typedef UINT8
(*I2C_FP_READ)(
	I2C_MODULE *pI2CModule, 
	UINT8 *pReadArray);

//*******************************************************
//
// System function
//
//*******************************************************
#if 1
typedef void
(*TIMER_FP_DELAY_MS)(
	UINT32 ms
	);

#else
typedef bool
(*TIMER_FP_DELAY_MS)(
	UINT32 ms
	);
#endif


struct I2C_MODULE_TAG
{
	UINT8 master_id;
	UINT8 device_id;
	UINT16 slave_addr;
	UINT8 len;
	UINT8 addrtype;//0: no addr 1: 8bit 2:16bit

	//I2C interface function
	I2C_FP_WRITE i2c_write;
	I2C_FP_READ i2c_read;
};


struct SYS_MODULE_TAG
{
	//System function
	TIMER_FP_DELAY_MS timer_delay_ms;
};





//Tuner definition

////////////////////////////////////////////////////////////////////////////////////////////////
//
// NXP TDA18272
//
////////////////////////////////////////////////////////////////////////////////////////////////

// TDA18272 extra module
typedef struct TDA18272_EXTRA_MODULE_TAG TDA18272_EXTRA_MODULE;

#if 0
// TDA18272 bandwidth mode setting function pointer
typedef int
(*TDA18272_FP_SET_STANDARD_BANDWIDTH_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int StandardBandwidthMode
	);

// TDA18272 bandwidth mode getting function pointer
typedef int
(*TDA18272_FP_GET_STANDARD_BANDWIDTH_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int *pStandardBandwidthMode
	);
#endif
// TDA18272 power mode setting function pointer
typedef int
(*TDA18272_FP_SET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int PowerMode
	);

// TDA18272 power mode getting function pointer
typedef int
(*TDA18272_FP_GET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int *pPowerMode
	);

// TDA18272 IF frequency getting function pointer
typedef int
(*TDA18272_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	unsigned long *pIfFreqHz
	);

// TDA18272 extra module
struct TDA18272_EXTRA_MODULE_TAG
{
	// TDA18272 extra variables
	unsigned long CrystalFreqHz;
	int UnitNo;
	int IfOutputVppMode;
	int StandardBandwidthMode;
	int IsStandardBandwidthModeSet;
	int PowerMode;
	int IsPowerModeSet;

	// TDA18272 extra function pointers
	//TDA18272_FP_SET_STANDARD_BANDWIDTH_MODE   SetStandardBandwidthMode;
	//TDA18272_FP_GET_STANDARD_BANDWIDTH_MODE   GetStandardBandwidthMode;
	TDA18272_FP_SET_POWER_MODE                SetPowerMode;
	TDA18272_FP_GET_POWER_MODE                GetPowerMode;
	TDA18272_FP_GET_IF_FREQ_HZ                GetIfFreqHz;
};
////////////////////////////////////////////////////////////////////////////////////////////////
//
// NXP TDA18273
//
////////////////////////////////////////////////////////////////////////////////////////////////

// TDA18273 extra module
typedef struct TDA18273_EXTRA_MODULE_TAG TDA18273_EXTRA_MODULE;

// TDA18273 power mode setting function pointer
typedef int
(*TDA18273_FP_SET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int PowerMode
	);

// TDA18273 power mode getting function pointer
typedef int
(*TDA18273_FP_GET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int *pPowerMode
	);

// TDA18273 IF frequency getting function pointer
typedef int
(*TDA18273_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	unsigned long *pIfFreqHz
	);

// TDA18273 extra module
struct TDA18273_EXTRA_MODULE_TAG
{
	// TDA18273 extra variables
	unsigned long CrystalFreqHz;
	int UnitNo;
	int IfOutputVppMode;
	int StandardMode;
	int IsStandardModeSet;
	int PowerMode;
	int IsPowerModeSet;

	// TDA18273 extra function pointers
	TDA18273_FP_SET_POWER_MODE                SetPowerMode;
	TDA18273_FP_GET_POWER_MODE                GetPowerMode;
	TDA18273_FP_GET_IF_FREQ_HZ                GetIfFreqHz;
};
////////////////////////////////////////////////////////////////////////////////////////////////
//
// FRESCO FM2150
//
////////////////////////////////////////////////////////////////////////////////////////////////

// FM2150 extra module
typedef struct FM2150_EXTRA_MODULE_TAG FM2150_EXTRA_MODULE;

// FM2150 power mode setting function pointer
typedef int
(*FM2150_FP_SET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int PowerMode
	);

// FM2150 power mode getting function pointer
typedef int
(*FM2150_FP_GET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int *pPowerMode
	);

// FM2150 IF frequency getting function pointer
typedef int
(*FM2150_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	unsigned long *pIfFreqHz
	);

// FM2150 extra module
struct FM2150_EXTRA_MODULE_TAG
{
	// FM2150 extra variables
	unsigned long CrystalFreqHz;
	int UnitNo;
	int IfOutputVppMode;
	int StandardMode;
	int IsStandardModeSet;
	int PowerMode;
	int IsPowerModeSet;

	// FM2150 extra function pointers
	FM2150_FP_SET_POWER_MODE                SetPowerMode;
	FM2150_FP_GET_POWER_MODE                GetPowerMode;
	FM2150_FP_GET_IF_FREQ_HZ                GetIfFreqHz;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
// SONY RX201 
//
////////////////////////////////////////////////////////////////////////////////////////////////

// RX201 extra module
typedef struct SONYRX201_EXTRA_MODULE_TAG SONYRX201_EXTRA_MODULE;

typedef enum {
    PORT1 = 1,                    /* use IFOUT1 port & AGC1 port        */
    PORT2,                        /* use IFOUT2 port & AGC2 port        */
} IFOUT_AGC_PORT;

typedef UINT16
(*SONYRX201_FP_WAKE_UP)(
	ATV_TUNER_MODULE *pTuner
	);


typedef UINT16
(*SONYRX201_FP_SLEEP)(
	ATV_TUNER_MODULE *pTuner
	);

typedef UINT16
(*SONYRX201_FP_SET_IF_PORT)(
	ATV_TUNER_MODULE *pTuner,
	IFOUT_AGC_PORT port
	);

// SONYRX201 extra module
struct SONYRX201_EXTRA_MODULE_TAG
{


	UINT8 	port;
	UINT8	TunerRegion;
	UINT16	TunerMode;
	UINT32 	TunerPIF;
	const UINT8* 	param;

	SONYRX201_FP_WAKE_UP                	WakeUp;
	SONYRX201_FP_SLEEP                		Sleep;
	SONYRX201_FP_SET_IF_PORT                SetIfPort;

};



////////////////////////////////////////////////////////////////////////////////////////////////
//
// MAXLINEAR_MXL301RF
//
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct MXL301RF_EXTRA_MODULE_TAG MXL301RF_EXTRA_MODULE;

// MXL301RF extra module
struct MXL301RF_EXTRA_MODULE_TAG
{
	// MXL301RF extra variables

	// MXL301RF extra function pointers

};



////////////////////////////////////////////////////////////////////////////////////////////////
//
// XCEIVE_XC5200
//
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct XCEIVEXC5200_EXTRA_MODULE_TAG XCEIVEXC5200_EXTRA_MODULE;

// XCEIVEXC5200 extra module
typedef UINT16
(*XCEIVEXC5200_FP_SET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner
	);
struct XCEIVEXC5200_EXTRA_MODULE_TAG
{
	// XCEIVEXC5200 extra variables
	UINT16	TunerMode;
	UINT32 	TunerPIF;
	UINT32 	TunerIF;
	UINT16	TunerSTD;
	const UINT8* 	param;

	XCEIVEXC5200_FP_SET_IF_FREQ_HZ	SetIFFreqHz;

	// XCEIVEXC5200 extra function pointers

};

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entropic EN402X
//
////////////////////////////////////////////////////////////////////////////////////////////////

// EN402X extra module
typedef struct EN402X_EXTRA_MODULE_TAG EN402X_EXTRA_MODULE;

// EN402X power mode setting function pointer
typedef int
(*EN402X_FP_SET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int PowerMode
	);

// EN402X power mode getting function pointer
typedef int
(*EN402X_FP_GET_POWER_MODE)(
	ATV_TUNER_MODULE *pTuner,
	int *pPowerMode
	);

// EN402X IF frequency getting function pointer
typedef int
(*EN402X_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	unsigned long *pIfFreqHz
	);

// EN402X extra module
struct EN402X_EXTRA_MODULE_TAG
{
	// EN402X extra variables
	unsigned long CrystalFreqHz;
	int UnitNo;
	int IfOutputVppMode;
	int StandardBandwidthMode;
	int IsStandardBandwidthModeSet;
	int PowerMode;
	int IsPowerModeSet;

	// EN402X extra function pointers
	EN402X_FP_SET_POWER_MODE                SetPowerMode;
	EN402X_FP_GET_POWER_MODE                GetPowerMode;
	EN402X_FP_GET_IF_FREQ_HZ                GetIfFreqHz;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
// SILICONLABS SI2156
//
////////////////////////////////////////////////////////////////////////////////////////////////

// SI2156 extra module
typedef struct SI2156_EXTRA_MODULE_TAG SI2156_EXTRA_MODULE;


typedef void 
(*SI2156_FP_GET_RF_STREGTH)(
	int *TuneComplete, 
	int *InputLevel, 
	int *AtvTunerLockStatus, 
	int *AtvOffset);
typedef void 
(*SI2156_FP_SET_LNA_ONOFF)(
	bool enable);
typedef int
(*SI2156_FP_GET_ATV_AGC_SPEED)(
	ATV_TUNER_MODULE *pTuner, 
	int *pStandardAGCSPEED);

typedef void 
(*SI2156_FP_SET_ATV_AGC_SPEED)(
	UINT8 agc_speed_mode);

typedef void 
(*SI2156_FP_SET_ATV_RF_AGC_TOP)(
	UINT8 rf_agc_top_mode);

typedef  int 
(*SI2156_FP_GET_ATV_RF_AGC_TOP)(
	ATV_TUNER_MODULE *pTuner, int *pStandardRFTOP);


typedef void 
(*SI2156_FP_SET_ATV_IF_PORT_AUXIF_AGC)(
	UINT8 if_port_auxif_agc_mode);

typedef int  
(*SI2156_FP_GET_ATV_IF_PORT_AUXIF_AGC)(
ATV_TUNER_MODULE *pTuner, int *pStandardAUXIFAGC);

typedef void 
(*SI2156_FP_SET_ATV_IF_OUTPUT_AMP)(
	UINT8 if_output_amp_value);

typedef int  
(*SI2156_FP_GET_ATV_IF_OUTPUT_AMP)(
ATV_TUNER_MODULE *pTuner, int *pStandardAmpValue);

typedef void 
(*SI2156_FP_SET_ATV_AFC_ENABLE)(
	bool enable);

typedef int  
(*SI2156_FP_GET_ATV_AFC_ENABLE)(
bool *enable);


// SI2156 extra module
struct SI2156_EXTRA_MODULE_TAG
{
	// SI2156 extra variables
	unsigned long CrystalFreqHz;
	int UnitNo;
	int IfOutputVppMode;
	int StandardBandwidthMode;
	UINT8 set_bandwidth;
	int IsStandardBandwidthModeSet;
	int PowerMode;
	int IsPowerModeSet;
	int video_mode; 
	int audio_mode;
	UINT8 agc_speed_mode;
	int pStandardAGCSPEED;
	UINT8 rf_agc_top_mode;
	int pStandardRFTOP;
	UINT8 if_port_auxif_agc_mode;
	int pStandardAUXIFAGC;
	UINT8 if_output_amp_value;
	int pStandardAmpValue;
	// SI2156 extra function pointers
	SI2156_FP_GET_RF_STREGTH		  GetRfStregth;
	SI2156_FP_SET_LNA_ONOFF				SetLNAOnOff;
	SI2156_FP_SET_ATV_AGC_SPEED	SetATVAgcSpeed;
	SI2156_FP_GET_ATV_AGC_SPEED	GetATVAgcSpeed;
	SI2156_FP_SET_ATV_RF_AGC_TOP       SetATVRFAgcTop;
	SI2156_FP_GET_ATV_RF_AGC_TOP       GetATVRFAgcTop;
	SI2156_FP_SET_ATV_IF_PORT_AUXIF_AGC	 SetATVIFPAUXIFAGC;
	SI2156_FP_GET_ATV_IF_PORT_AUXIF_AGC GetATVIFPAUXIFAGC;
	SI2156_FP_SET_ATV_IF_OUTPUT_AMP		SetATVIFPOUTPUTAMP;
	SI2156_FP_GET_ATV_IF_OUTPUT_AMP 	GetATVIFPOUTPUTAMP;
	SI2156_FP_SET_ATV_AFC_ENABLE		SetATVAfcEnable;
	SI2156_FP_GET_ATV_AFC_ENABLE 		GetATVAfcEnable;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
// RF TUNER
//
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct RFTUNER_EXTRA_MODULE_TAG RFTUNER_EXTRA_MODULE;

#if 0
typedef UINT8
(*RFTUNER_FP_GET_IF_FREQ_HZ)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 *pIfFreqHz
	);
typedef UINT8
(*RFTUNER_FP_GET_DIVER_RATIO)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz,
	UINT16 *DiverRatio
	);
typedef UINT8
(*RFTUNER_FP_GET_RATIO_IN_STEPSIZE)(
	ATV_TUNER_MODULE *pTuner,
	UINT16 *RatioInStepSize
	);
typedef UINT8
(*RFTUNER_FP_CHECK_BAND)(
	ATV_TUNER_MODULE *pTuner,
	UINT32 RfFreqHz,
	UINT8 *Band
	);
#endif
// RFTUNER extra module
struct RFTUNER_EXTRA_MODULE_TAG
{
	// RFTUNER extra variables

	// RFTUNER extra function pointers
	#if 0
	RFTUNER_FP_GET_IF_FREQ_HZ			GetIfFreqHz;
	RFTUNER_FP_GET_DIVER_RATIO			GeDiverRatio;
	RFTUNER_FP_GET_RATIO_IN_STEPSIZE	GetRatioInStepSize;
	RFTUNER_FP_CHECK_BAND				CheckBand;
	#endif
};



////////////////////////////////////////////////////////////////////////////////////////////////

struct ATV_TUNER_MODULE_TAG
{
	// Private variables
	UINT8   TunerType;									///<   Tuner type
	UINT8   DeviceAddr;									///<   Tuner I2C device address
	UINT32  RfFreqHz;										///<   Tuner RF frequency in Hz
	UINT8   IsRfFreqHzSet;											///<   Tuner RF frequency in Hz (setting status)
	UINT32 RfFreqHz_Max;
	UINT32 RfFreqHz_Min;
	TUNER_INPUT_SEL RfInput_Sel;
	UINT8 video_mode;
	UINT8 audio_mode;
	
	union														///<   Tuner extra module used by driving module
	{
		RFTUNER_EXTRA_MODULE    rf_tuner;	
		TDA18272_EXTRA_MODULE    Tda18272;
		TDA18273_EXTRA_MODULE    Tda18273;
		SONYRX201_EXTRA_MODULE	SonyRx201;
		MXL301RF_EXTRA_MODULE	mxl301rf;
		XCEIVEXC5200_EXTRA_MODULE	xc5200;
		EN402X_EXTRA_MODULE	En402x;
		FM2150_EXTRA_MODULE Fm2150;
		SI2156_EXTRA_MODULE Si2156;

	}
	Extra;
	
	SYS_MODULE *pSysModule;						///<   Base interface module
	I2C_MODULE *pI2cModule;								///<   I2C bridge module

	// Tuner manipulating functions
	ATV_TUNER_FP_GET_TUNER_TYPE    GetTunerType;				///<   Tuner type getting function pointer
	ATV_TUNER_FP_GET_DEVICE_ADDR   GetDeviceAddr;				///<   Tuner I2C device address getting function pointer

	ATV_TUNER_FP_INITIALIZE        Initialize;					///<   Tuner initializing function pointer
	ATV_TUNER_FP_SET_RF_FREQ_HZ    SetRfFreqHz;					///<   Tuner RF frequency setting function pointer
	ATV_TUNER_FP_GET_RF_FREQ_HZ    GetRfFreqHz;					///<   Tuner RF frequency getting function pointer
	ATV_TUNER_FP_SET_RF_FREQ_SEARCH_HZ SetRfFreqSearchHz;
	ATV_TUNER_FP_GET_RF_FREQ_SEARCH_HZ    GetRfFreqSearchHz;	
	ATV_TUNER_FP_SET_RF_FREQ_AFC_HZ SetRfFreqAfcHz;
	ATV_TUNER_FP_SET_STD_MODE    SetStandardMode;
	ATV_TUNER_FP_GET_STD_MODE    GetStandardMode;

	ATV_TUNER_FP_GET_IF_FREQ_HZ			GetIfFreqHz;
	ATV_TUNER_FP_GET_DIVER_RATIO			GeDiverRatio;
	ATV_TUNER_FP_GET_RATIO_IN_STEPSIZE	GetRatioInStepSize;
	ATV_TUNER_FP_CHECK_BAND				CheckBand;
	

	
};



#ifdef __cplusplus
}
#endif

#endif





















