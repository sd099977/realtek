#include"ifd_driver.h"

extern UINT8 drvif_scaleri2c_tuner_read(I2C_MODULE *pI2CModule, UINT8 *pReadArray);
extern UINT8 drvif_scaleri2c_tuner_write(I2C_MODULE *pI2CModule, UINT8 *pWriteArray);
extern ATV_TUNER_MODULE *pTuner;
extern IFD_MSG_LEVEL g_ifd_msg_level;

ATV_TUNER_MODULE pTunerModuleMemory[_Tuner_MAX_NO];
SYS_MODULE *pSysModule;
I2C_MODULE *pI2CModule;
SYS_MODULE pSysModuleMemory[_Tuner_MAX_NO];
I2C_MODULE pI2CModuleMemory[_Tuner_MAX_NO];

#define I2C_MASTER0 0
#define I2C_MASTER1 1

StructTunerDataType	/*IFD_CODE*/ gTunerData[_Tuner_MAX_NO] = 
{
#ifdef CONFIG_TUNER_SHARP_2403
	0xc0, //tunerI2C_ADD;
	432500,//tunerMinFreq;
	1452500,//tunerVHF_LowFreq;
	4292500,//tunerVHF_HighFreq;
	8702500,//tunerMaxFreq;
	380000,                  //tunerPIF;
	IFD_IF_FREQ_38M,      //tunerPIF_MN;
	IFD_IF_FREQ_38M,       //tunerPIF_B;
	IFD_IF_FREQ_38M,      //tunerPIF_GH;
	IFD_IF_FREQ_38M,       //tunerPIF_I;
	IFD_IF_FREQ_38M,      //tunerPIF_DK;
	IFD_IF_FREQ_38M,       //tunerPIF_L;
	IFD_IF_FREQ_32P2M,    //tunerPIF_LA;
	IFD_IF_FREQ_38M,     //tunerPIF_SCAN;
	TUNER_IF_TYPE_NEG,  //tunerIFType;
	500,//tunerRATIOStepSize;
	{//tunerBandFreq[IFD_TUNER_BAND_MAX];
	    1379000,1459000,4299000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,
	},
	{//tunerRegisterByte[IFD_TUNER_REG_BAND_MAX];
	    0xbd,0x11,0xdd, //band0
	    0xbd,0x12,0xdd, //band1
	    0xbd,0x12,0xdd, //band2
	    0xbd,0x14,0xdd, //band3 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00,
	}, 
	{//tunerRegisterByteSearch[IFD_TUNER_REG_BAND_MAX];
	    0xbd,0x11,0xfd, //band0
	    0xbd,0x12,0xfd, //band1
	    0xbd,0x12,0xfd, //band2
	    0xbd,0x14,0xfd, //band3 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00,
	}, 
	_FALSE,//tunerRfInputSwitchUsedTag;
	0,//tunerRfInputByte;
	0,//tunerRfInputLocation;
	_BIT6,//tunerFLStatusBit;
	4,//tunerBandNo;
	3,//tunerRegNoPerBand;
	_FALSE,//tunerUsedTag;
	TUNER_NONE_IC_RFAGC,//tunerAGCtype;
	TUNER_RF_POS_IF_NONE,//tunerAGCpolarity;
	TUNER_NORMAL,//tunerType;
	0,//tunerSpecificTag;
	TUNER_SHARP_2403,//tunerID;
#endif


#ifdef CONFIG_TUNER_XUGUANG_HFT3_86H_115CW
	0xc0, //tunerI2C_ADD;
	482500,//tunerMinFreq;
	1282500,//tunerVHF_LowFreq;
	4242500,//tunerVHF_HighFreq;
	8632500,//tunerMaxFreq;
	IFD_IF_FREQ_38M,                  //tunerPIF;
	IFD_IF_FREQ_38M,      //tunerPIF_MN;
	IFD_IF_FREQ_38M,       //tunerPIF_B;
	IFD_IF_FREQ_38M,      //tunerPIF_GH;
	IFD_IF_FREQ_38M,       //tunerPIF_I;
	IFD_IF_FREQ_38M,      //tunerPIF_DK;
	IFD_IF_FREQ_38M,       //tunerPIF_L;
	IFD_IF_FREQ_32P2M,    //tunerPIF_LA;
	IFD_IF_FREQ_38M,     //tunerPIF_SCAN;
	TUNER_IF_TYPE_NEG,  //tunerIFType;
	625,//tunerRATIOStepSize;
	{//tunerBandFreq[IFD_TUNER_BAND_MAX];
	    1282500,4242500,8632500,8700000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,
	},
	{//tunerRegisterByte[IFD_TUNER_REG_BAND_MAX];
	    0x8e,0x01, //band0
	    0x8e,0x02, //band1
	    0x8e,0x08, //band2
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00,
	}, 
	{//tunerRegisterByteSearch[IFD_TUNER_REG_BAND_MAX];
	    0xce,0x01, //band0
	    0xce,0x02, //band1
	    0xce,0x08, //band2
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00,
	}, 
	_FALSE,//tunerRfInputSwitchUsedTag;
	0,//tunerRfInputByte;
	0,//tunerRfInputLocation;
	_BIT6,//tunerFLStatusBit;
	3,//tunerBandNo;
	2,//tunerRegNoPerBand;
	_FALSE,//tunerUsedTag;
	TUNER_NONE_IC_RFAGC,//tunerAGCtype;
	TUNER_RF_POS_IF_NONE,//tunerAGCpolarity;
	TUNER_NORMAL,//tunerType;
	0,//tunerSpecificTag;
	TUNER_XUGUANG_HFT3_86H_115CW,//tunerID;
#endif


#ifdef CONFIG_TUNER_NXP_TDA18273
	0xc0, //tunerI2C_ADD;
	452500,//tunerMinFreq;
	3680000,//tunerVHF_LowFreq;
	8660000,//tunerVHF_HighFreq;
	8660000,//tunerMaxFreq;
	55000,                  //tunerPIF;
	IFD_IF_FREQ_5P5M,      //tunerPIF_MN;
	IFD_IF_FREQ_6P6M,       //tunerPIF_B;
	IFD_IF_FREQ_6P6M,      //tunerPIF_GH;
	IFD_IF_FREQ_7P45M,       //tunerPIF_I;
	IFD_IF_FREQ_6P85M,      //tunerPIF_DK;
	IFD_IF_FREQ_6P75M,       //tunerPIF_L;
	IFD_IF_FREQ_1P25M,    //tunerPIF_LA;
	IFD_IF_FREQ_6P85M,     //tunerPIF_SCAN;
	TUNER_IF_TYPE_NEG,  //tunerIFType;
	500,//tunerRATIOStepSize;
	{//tunerBandFreq[IFD_TUNER_BAND_MAX];
	    3680000,8660000,8660000,8660000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,8700000,
	    8700000,8700000,8700000,8700000,
	},
	{//tunerRegisterByte[IFD_TUNER_REG_BAND_MAX];
	    0x00,0x00,0x00, //band0
	    0x00,0x00,0x00, //band1
	    0x00,0x00,0x00, //band2
	    0x00,0x00,0x00, //band3 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00, 
	    0x00,0x00,0x00,
	}, 
	{//tunerRegisterByteSearch[IFD_TUNER_REG_BAND_MAX];
		0x00,0x00,0x00, //band0
		0x00,0x00,0x00, //band1
		0x00,0x00,0x00, //band2
		0x00,0x00,0x00, //band3 
		0x00,0x00,0x00, 
		0x00,0x00,0x00, 
		0x00,0x00,0x00, 
		0x00,0x00,0x00,
	}, 
	_FALSE,//tunerRfInputSwitchUsedTag;
	0,//tunerRfInputByte;
	0,//tunerRfInputLocation;
	0,//tunerFLStatusBit;
	0,//tunerBandNo;
	0,//tunerRegNoPerBand;
	_FALSE,//tunerUsedTag;
	TUNER_RFAGC_IC_IFAGC,//tunerAGCtype;
	TUNER_RF_POS_IF_NONE,//tunerAGCpolarity;
	TUNER_LOW_IF,//tunerType;
	0,//tunerSpecificTag;
	TUNER_NXP_TDA18273,//tunerID;
#endif
}; 

UINT8				gTunerNo = 0;
UINT8				gTunerActiveID = TUNER_NULL;
UINT8 g_tuner_bytenum=9, g_tuner_byte[9]={0,0,0,0,0,0,0,0,0};
    
void tuner_rf_data_init(void);
void tuner_lowif_data_init(void);
      
void
BuildInterface(
	SYS_MODULE **ppSysModule,
	SYS_MODULE *pSysModuleMemory,
	I2C_MODULE **ppI2CModule,
	I2C_MODULE *pI2CModuleMemory,
	I2C_FP_READ I2cRead,
	I2C_FP_WRITE I2cWrite,
	TIMER_FP_DELAY_MS WaitMs,
	UINT8 master_id,
	UINT8 device_id,
	UINT8 addrtype
	)
{
       //IFD_QC_MSG( "BuildInterface()\n");//by Lee, 07
        
	// Set base interface module pointer.
	*ppSysModule = pSysModuleMemory;
	*ppI2CModule = pI2CModuleMemory;


	// Set all base interface function pointers and arguments.
	(*ppI2CModule)->i2c_read                   = I2cRead;
	(*ppI2CModule)->i2c_write                  = I2cWrite;
	(*ppSysModule)->timer_delay_ms        = WaitMs;
	(*ppI2CModule)->master_id		= master_id;
	(*ppI2CModule)->device_id		= device_id;
	(*ppI2CModule)->addrtype		= addrtype;
	(*ppI2CModule)->len	= 0;
	(*ppI2CModule)->slave_addr = 0;
	
	return;
}
void drv_ifd_tuner_data_init(void){

	IFD_DEBUG_MSG(IFD_MSG_INIT,"drv_ifd_tuner_data_init\n");
	gTunerNo = 0;

	tuner_rf_data_init();
	tuner_lowif_data_init();
	#ifdef CONFIG_TUNER_DEFAULT
	if(gTunerActiveID == TUNER_NULL)
		gTunerActiveID = CONFIG_TUNER_DEFAULT;
	IFD_DEBUG_MSG(IFD_MSG_INIT,"gTunerActiveID=%d\n", gTunerActiveID);
	#else
	if(gTunerActiveID == TUNER_NULL)
		gTunerActiveID = gTunerData[0].tunerID;
	#endif	
}


void drv_ifd_tuner_BuildTuner(void)
{
	UINT8 i=0;
	IFD_QC_MSG("drv_ifd_tuner_BuildTuner\n");
	IFD_QC_MSG("gTunerNo=%d\n", gTunerNo);


	#ifdef CONFIG_TUNER_RF_TYPE
	BuildInterface(
		&pSysModule,
		&pSysModuleMemory[i],
		&pI2CModule,
		&pI2CModuleMemory[i],
		drvif_scaleri2c_tuner_read,
		drvif_scaleri2c_tuner_write,
		//udelay,
		sys_wait_us,
		I2C_MASTER0,
		gTunerData[i].tunerI2C_ADD,
		I2C_NOADDR
	);
	BuildRFTuner(&pTuner, &pTunerModuleMemory[i], pSysModule,
		pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x00);
		
	#elif defined(CONFIG_TUNER_LOWIF_TYPE)
		#ifdef CONFIG_TUNER_MAXLINEAR_MXL301RF
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_ADDR_8
		);
		BuildMxl301rfModule(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq);
		#elif defined(CONFIG_TUNER_NXP_TDA18273)
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			udelay,
			I2C_MASTER1,
			gTunerData[i].tunerI2C_ADD,
			I2C_ADDR_8
		);		
		BuildTda18273Module(&pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x7);		
		IFD_QC_MSG("CONFIG_TUNER_NXP_TDA18273\n");
		
		#elif CONFIG_TUNER_RAFAEL_RT810
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_NOADDR
		);

		BuildRt810Module(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x7);
		#elif CONFIG_TUNER_MAXIM_MAX3543
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_ADDR_8
		);
		BuildMax3543Module(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x7);
		#elif CONFIG_SONY_RX201
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_ADDR_8
		);
		BuildSonyRx201Module(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq);
									
		#elif CONFIG_TUNER_FRESCO_FM2150
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_ADDR_8
		);
		BuildFM2150Module(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
			pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x7);
							
		#elif CONFIG_TUNER_SILICONLABS_SI2156
		BuildInterface(
			&pSysModule,
			&pSysModuleMemory[i],
			&pI2CModule,
			&pI2CModuleMemory[i],
			drvif_scaleri2c_tuner_read,
			drvif_scaleri2c_tuner_write,
			//udelay,
			sys_wait_us,
			I2C_MASTER0,
			gTunerData[i].tunerI2C_ADD,
			I2C_CMD_CONTINUE
		);
		IFD_DEBUG_MSG(IFD_MSG_INIT,"@@BuildSi2156Module\n");
		BuildSi2156Module(&gTunerData[i].pTuner, &pTunerModuleMemory[i], pSysModule,
		pI2CModule, gTunerData[i].tunerI2C_ADD, 0x00, gTunerData[i].tunerMaxFreq, gTunerData[i].tunerMinFreq, 0x00, 0x7);
		IFD_DEBUG_MSG(IFD_MSG_INIT,"@@2\n");
							
		#endif
	#endif

}

void tuner_rf_data_init(void){
#if 0
	UINT8 i=gTunerNo;

	IFD_DEBUG_MSG(IFD_MSG_INIT,"tuner_rf_data_init\n");
// Tuner Parameters
#ifdef CONFIG_TUNER_LG_TDTK_C842D_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	        IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1282500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 500;
	gTunerData[i].tunerBandFreq[0] = 1282500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;

	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbd; //band2
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByte[7] = 0x18;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x18;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LG_TDTK_C842D_DIF;
	
	i++;
#endif

#ifdef CONFIG_TUNER_XUGUANG_DFT_96H_116CW_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	        IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1282500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;
	gTunerData[i].tunerBandFreq[0] = 1282500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;

	gTunerData[i].tunerRegisterByte[0] = 0xbb; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbb; //band2
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbb; //band3
	gTunerData[i].tunerRegisterByte[7] = 0x18;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbb; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbb; //band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbb; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x18;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_DFT_96H_116CW_DIF;
	
	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_HFT_86H_115HR
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4322500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4322500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT_86H_115HR;
	
	i++;
#endif

#ifdef CONFIG_TUNER_XUGUANG_TDQ6K_T116CW
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4322500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500;
	gTunerData[i].tunerBandFreq[1] = 4322500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ6K_T116CW;
	
	i++;
#endif

#ifdef CONFIG_TUNER_ALPS_TDAG4_D01A
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}

	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4322500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 1250000;
	gTunerData[i].tunerBandFreq[1] = 3020000;
	gTunerData[i].tunerBandFreq[2] = 3660000;
	gTunerData[i].tunerBandFreq[3] = 4700000;
	gTunerData[i].tunerBandFreq[4] = 7260000;
	gTunerData[i].tunerBandFreq[5] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x92;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x85;
	gTunerData[i].tunerRegisterByte[2] = 0xc2;
	gTunerData[i].tunerRegisterByte[3] = 0x92;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x86;
	gTunerData[i].tunerRegisterByte[5] = 0xc2;
	gTunerData[i].tunerRegisterByte[6] = 0x92;//band3
	gTunerData[i].tunerRegisterByte[7] = 0xc6;
	gTunerData[i].tunerRegisterByte[8] = 0xc2;
	gTunerData[i].tunerRegisterByte[9] = 0x92;//band4
	gTunerData[i].tunerRegisterByte[10] = 0x8c;
	gTunerData[i].tunerRegisterByte[11] = 0xc2;
	gTunerData[i].tunerRegisterByte[12] = 0x92;//band5
	gTunerData[i].tunerRegisterByte[13] = 0xcc;
	gTunerData[i].tunerRegisterByte[14] = 0xc2;
	gTunerData[i].tunerRegisterByte[15] = 0x92;//band6
	gTunerData[i].tunerRegisterByte[16] = 0x0c;
	gTunerData[i].tunerRegisterByte[17] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x92;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x85;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[3] = 0x92;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x86;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[6] = 0x92;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0xc6;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[9] = 0x92;//band4
	gTunerData[i].tunerRegisterByteSearch[10] = 0x8c;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[12] = 0x92;//band5
	gTunerData[i].tunerRegisterByteSearch[13] = 0xcc;
	gTunerData[i].tunerRegisterByteSearch[14] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[15] = 0x92;//band6
	gTunerData[i].tunerRegisterByteSearch[16] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[17] = 0xc2;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 6;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_ALPS_TDAG4_D01A;

	i++;
#endif
#ifdef CONFIG_TUNER_LG_TDTC_G29D
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4232500;
	gTunerData[i].tunerMaxFreq = 8552500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4232500;
	gTunerData[i].tunerBandFreq[2] = 8552500;
	gTunerData[i].tunerRegisterByte[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbd;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x02;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbd;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LG_TDTC_G29D;

	i++;
#endif
#ifdef CONFIG_TUNER_KEH_FTDC3S20V04
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_FTDC3S20V04;

	i++;
#endif
#ifdef CONFIG_TUNER_KEH_FTDC3S20V04_BJT2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_FTDC3S20V04_BJT2;

	i++;
#endif
#ifdef CONFIG_TUNER_KEH_FTDC3S20BV04
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1437500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1437500;
	gTunerData[i].tunerBandFreq[1] = 4272500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_FTDC3S20BV04;

	i++;
#endif
#ifdef CONFIG_TUNER_KEH_FTDC3S20BV04_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1437500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1437500;
	gTunerData[i].tunerBandFreq[1] = 4272500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_FTDC3S20BV04_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_KEH_FTDC3S20BV04_BJT2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1437500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1437500;
	gTunerData[i].tunerBandFreq[1] = 4272500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_FTDC3S20BV04_BJT2;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_TDQ_6FT_W116H
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1482500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1482500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_6FT_W116H;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_TDQ_6FT_W116H_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1482500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1482500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_6FT_W116H_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_HFT2_8F_115CW
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1322500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1322500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT2_8F_115CW;

	i++;
#endif

#ifdef CONFIG_TUNER_KEH_TDQ_6FT_W116H_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1482500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1482500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_KEH_TDQ_6FT_W116H_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_TDQ_6ID_GW115HR
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 392500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_6ID_GW115HR;

	i++;
#endif

#if defined(CONFIG_TUNER_XUGUANG_HFT_98H_115CW_BJT)||defined(CONFIG_TUNER_XUGUANG_HFT_99H_116HR_BJT)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1282500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1282500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT_98H_115CW_BJT;

	i++;
#endif

#if defined(CONFIG_TUNER_XUGUANG_HFT3_86H_115CW_BJT)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1282500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1282500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT3_86H_115CW_BJT;

	i++;
#endif


#ifdef CONFIG_TUNER_XUGUANG_TDQ_6ID_GW115HR_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 392500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4282500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4282500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_6ID_GW115HR_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_TDQ_B6_116H_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1322500;
	gTunerData[i].tunerVHF_HighFreq = 4277500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1322500;
	gTunerData[i].tunerBandFreq[1] = 4277500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_B6_116H_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_TDQ_6PD_LW115CWADC

	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_TDQ_6PD_LW115CWADC;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_HFT8B_115CW

	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8652500;//8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8622500;
	gTunerData[i].tunerBandFreq[3] = 8652500;//8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1    
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByte[6] = 0x8e; //band4
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT8B_115CW;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_HFT8B1_V116CW_BJT

	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8652500;//8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8622500;
	gTunerData[i].tunerBandFreq[3] = 8652500;//8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1    
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByte[6] = 0x8e; //band4
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_HFT8B1_V116CW_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_XUGUANG_DVT_8ADC1_W41F9
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1632500;
	gTunerData[i].tunerVHF_HighFreq = 4572500;
	gTunerData[i].tunerMaxFreq = 8612500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1632500;
	gTunerData[i].tunerBandFreq[1] = 4572500;
	gTunerData[i].tunerBandFreq[2] = 8612500;
	gTunerData[i].tunerRegisterByte[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x04;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x04;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_DVT_8ADC1_W41F9;

	i++;
#endif

#ifdef CONFIG_TUNER_XUGUANG_DVT_8ADC1_T41F0HS
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1632500;
	gTunerData[i].tunerVHF_HighFreq = 4572500;
	gTunerData[i].tunerMaxFreq = 8612500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1632500;
	gTunerData[i].tunerBandFreq[1] = 4572500;
	gTunerData[i].tunerBandFreq[2] = 8612500;
	gTunerData[i].tunerRegisterByte[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x04;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x04;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_DVT_8ADC1_T41F0HS;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F25WT_13NXR_E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1542500;
	gTunerData[i].tunerVHF_HighFreq = 4422500;
	gTunerData[i].tunerMaxFreq = 8012500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1542500; 
	gTunerData[i].tunerBandFreq[1] = 4422500; 
	gTunerData[i].tunerBandFreq[2] = 8012500; 
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x0c;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F25WT_13NXR_E;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F25WT_13NXR_E_BJT2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1542500;
	gTunerData[i].tunerVHF_HighFreq = 4422500;
	gTunerData[i].tunerMaxFreq = 8012500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1542500; 
	gTunerData[i].tunerBandFreq[1] = 4422500; 
	gTunerData[i].tunerBandFreq[2] = 8012500; 
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x0c;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F25WT_13NXR_E_BJT2;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F25WT_3DXR_E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1482500;
	gTunerData[i].tunerVHF_HighFreq = 4522500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1482500; 
	gTunerData[i].tunerBandFreq[1] = 4522500; 
	gTunerData[i].tunerBandFreq[2] = 8632500; 
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x0c;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F25WT_3DXR_E;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F25WT_3DXR_E_BJT2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1482500;
	gTunerData[i].tunerVHF_HighFreq = 4522500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1482500; 
	gTunerData[i].tunerBandFreq[1] = 4522500; 
	gTunerData[i].tunerBandFreq[2] = 8632500; 
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x0c;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F25WT_3DXR_E_BJT2;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F25WT_3BXR_E_BJT2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1507500;
	gTunerData[i].tunerVHF_HighFreq = 4512500;
	gTunerData[i].tunerMaxFreq = 8552500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1507500; 
	gTunerData[i].tunerBandFreq[1] = 4512500; 
	gTunerData[i].tunerBandFreq[2] = 8552500; 
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x0c;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x0c;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F25WT_3BXR_E_BJT2;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F41CT_2_E)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1497500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1497500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4272500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_2_E;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F17CT_2DA_E)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1497500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1497500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4272500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F17CT_2DA_E;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F41CT_2_E_BJT) 
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1497500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1497500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4272500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_2_E_BJT;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F41CT_2_E_TIamp) 
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1497500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1497500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4272500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_2_E_TIamp;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F41CT_2B_E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1497500;
	gTunerData[i].tunerVHF_HighFreq = 4272500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1497500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4272500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_2B_E;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F41CT_6N_E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1492500;
	gTunerData[i].tunerVHF_HighFreq = 4292500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 1492500;
	gTunerData[i].tunerBandFreq[1] = 4292500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x88; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x88; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x88; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc8; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc8; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc8; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_6N_E;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F41CT_6N_E_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1492500;
	gTunerData[i].tunerVHF_HighFreq = 4292500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 1492500;
	gTunerData[i].tunerBandFreq[1] = 4292500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x88; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x88; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x88; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc8; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc8; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc8; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F41CT_6N_E_BJT;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F86WT_2_E_BJT)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500; //487500; //2011.11.25 cy_tsai modify min freq because TPV OSD request
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4482500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4482500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F86WT_2_E_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F86WT_17_E_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500; //487500; //2011.11.25 cy_tsai modify min freq because TPV OSD request
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4482500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500; //1472500;
	gTunerData[i].tunerBandFreq[1] = 4482500; //4232500;
	gTunerData[i].tunerBandFreq[2] = 8632500; //8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F86WT_17_E_DIF;

	i++;
#endif
#if defined(CONFIG_TUNER_TCL_F86WT_13N_E_BJT)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 542500;
	gTunerData[i].tunerVHF_LowFreq = 1452500;
	gTunerData[i].tunerVHF_HighFreq = 4512500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1452500; 
	gTunerData[i].tunerBandFreq[1] = 4512500; 
	gTunerData[i].tunerBandFreq[2] = 8632500; 
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F86WT_13N_E_BJT;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F35CT_2_E_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1522500;
	gTunerData[i].tunerVHF_HighFreq = 4522500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1522500;
	gTunerData[i].tunerBandFreq[1] = 4522500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F35CT_2_E_BJT;

	i++;
#endif


#if defined(CONFIG_TUNER_TCL_DA89CT_6_E_BJT)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 540000;
	gTunerData[i].tunerVHF_LowFreq = 1650000;
	gTunerData[i].tunerVHF_HighFreq = 4500000;
	gTunerData[i].tunerMaxFreq = 8640000;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 1650000; 
	gTunerData[i].tunerBandFreq[1] = 4500000; 
	gTunerData[i].tunerBandFreq[2] = 8640000; 
	gTunerData[i].tunerRegisterByte[0] = 0xbf; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xdd; 
	gTunerData[i].tunerRegisterByte[3] = 0xbf;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x02; 
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbf;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x08; 
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbf; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbf;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbf;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08; 
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_DA89CT_6_E_BJT;

	i++;
#endif

#if defined(CONFIG_TUNER_CHANGHONG_DTI1_E4I12VH) || defined(CONFIG_TUNER_CHANGHONG_DTI5_C400F1VH)
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 1402500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1402500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x9b;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x41;
	gTunerData[i].tunerRegisterByte[2] = 0xc2;
	gTunerData[i].tunerRegisterByte[3] = 0x9b;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x42;
	gTunerData[i].tunerRegisterByte[5] = 0xc2;
	gTunerData[i].tunerRegisterByte[6] = 0x9b;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x48;
	gTunerData[i].tunerRegisterByte[8] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x9b;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x41;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xe2;
	gTunerData[i].tunerRegisterByteSearch[3] = 0x9b;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x42;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xe2;
	gTunerData[i].tunerRegisterByteSearch[6] = 0x9b;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x48;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xe2;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_CHANGHONG_DTI1_E4I12VH;

	i++;
#endif
#ifdef CONFIG_TUNER_ALPS_TDAU3XD01A
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1380000;
	gTunerData[i].tunerVHF_HighFreq = 3780000;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1380000;
	gTunerData[i].tunerBandFreq[1] = 3780000;
	gTunerData[i].tunerBandFreq[2] = 7380000;
	gTunerData[i].tunerBandFreq[3] = 8640000;
	gTunerData[i].tunerRegisterByte[0] = 0x9b;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x80;
	gTunerData[i].tunerRegisterByte[2] = 0xc2;
	gTunerData[i].tunerRegisterByte[3] = 0x9b;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x83;
	gTunerData[i].tunerRegisterByte[5] = 0xc2;
	gTunerData[i].tunerRegisterByte[6] = 0x9b;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x48;
	gTunerData[i].tunerRegisterByte[8] = 0xc2;
	gTunerData[i].tunerRegisterByte[9] = 0x9b;//band4
	gTunerData[i].tunerRegisterByte[10] = 0xc8;
	gTunerData[i].tunerRegisterByte[11] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x9b;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x80;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[3] = 0x9b;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x83;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[6] = 0x9b;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x48;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xc2;
	gTunerData[i].tunerRegisterByteSearch[9] = 0x9b;//band4
	gTunerData[i].tunerRegisterByteSearch[10] = 0xc8;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xc2;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_ALPS_TDAU3XD01A;

	i++;
#endif

#ifdef CONFIG_TUNER_LINGHUA_TDP_1H1E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LINGHUA_TDP_1H1E;

	i++;
	
#endif

#ifdef CONFIG_TUNER_LINGHUA_TDP_1H1E_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LINGHUA_TDP_1H1E_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_LINGHUA_TDP_2A1RE_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1362500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1362500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LINGHUA_TDP_2A1RE_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_TCL_F13WP_2DP_E
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1522500;
	gTunerData[i].tunerVHF_HighFreq = 4402500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1522500;
	gTunerData[i].tunerBandFreq[1] = 4402500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x04;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x04;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F13WP_2DP_E;

	i++;
#endif

#ifdef CONFIG_TUNER_QINGJIA_AFT7_W000G
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1602500;
	gTunerData[i].tunerVHF_HighFreq = 4642500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1602500;
	gTunerData[i].tunerBandFreq[1] = 4642500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_QINGJIA_AFT7_W000G;

	i++;
#endif

#ifdef CONFIG_TUNER_QINGJIA_AFT7_W305G
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1572500;
	gTunerData[i].tunerVHF_HighFreq = 4512500;
	gTunerData[i].tunerMaxFreq = 8022500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1572500;
	gTunerData[i].tunerBandFreq[1] = 4512500;
	gTunerData[i].tunerBandFreq[2] = 8022500;
	gTunerData[i].tunerRegisterByte[0] = 0x86; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x86; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc6; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc6; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xc6; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_QINGJIA_AFT7_W305G;

	i++;
#endif
// USER:wjchen DATE:2010/5/5, 
// Add a setting for CDT_3FC2I2 tuner
#ifdef CONFIG_TUNER_CDT_3FC2I2
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 1612500;
	gTunerData[i].tunerVHF_HighFreq = 4642500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1612500;
	gTunerData[i].tunerBandFreq[1] = 4642500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_CDT_3FC2I2;

	i++;
#endif

// USER:wjchen DATE:2010/5/5, 
// Add a setting for CDT_3FC2I2_BJT tuner
#ifdef CONFIG_TUNER_CDT_3FC2I2_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 1612500;
	gTunerData[i].tunerVHF_HighFreq = 4642500;
	gTunerData[i].tunerMaxFreq = 8652500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1612500;
	gTunerData[i].tunerBandFreq[1] = 4642500;
	gTunerData[i].tunerBandFreq[2] = 8622500;
	gTunerData[i].tunerBandFreq[3] = 8652500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByte[6] = 0x8e; //band4
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xce; //band4
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_CDT_3FC2I2_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_NUTUNE_TT2124
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1542500;
	gTunerData[i].tunerVHF_HighFreq = 4392500;
	gTunerData[i].tunerMaxFreq = 8552500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1542500;
	gTunerData[i].tunerBandFreq[1] = 4392500;
	gTunerData[i].tunerBandFreq[2] = 8552500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x04;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x04;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NUTUNE_TT2124;

	i++;
#endif

#ifdef CONFIG_TUNER_SHARP_2403
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;//430000;
	gTunerData[i].tunerVHF_LowFreq = 1452500;//1459000;
	gTunerData[i].tunerVHF_HighFreq = 4292500;//4299000;
	gTunerData[i].tunerMaxFreq = 8702500;//8700000;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData[i].tunerBandFreq[0] = 1379000;
	gTunerData[i].tunerBandFreq[1] = 1459000;
	gTunerData[i].tunerBandFreq[2] = 4299000;
	gTunerData[i].tunerBandFreq[3] = 8700000;
	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xdd;
	gTunerData[i].tunerRegisterByte[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbd;  //band2
	gTunerData[i].tunerRegisterByte[7] = 0x12;
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByte[9] = 0xbd; //band3
	gTunerData[i].tunerRegisterByte[10] = 0x14;
	gTunerData[i].tunerRegisterByte[11] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; // band2
	gTunerData[i].tunerRegisterByteSearch[7] = 0x12; 
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRegisterByteSearch[9] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[10] = 0x14;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SHARP_2403;

	i++;
#endif

#ifdef CONFIG_TUNER_SHARP_2403_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;//430000;
	gTunerData[i].tunerVHF_LowFreq = 1452500;//1459000;
	gTunerData[i].tunerVHF_HighFreq = 4292500;//4299000;
	gTunerData[i].tunerMaxFreq = 8702500;//8700000;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80
	gTunerData[i].tunerBandFreq[0] = 1459000;
	gTunerData[i].tunerBandFreq[1] = 4299000;
	gTunerData[i].tunerBandFreq[2] = 8700000;
	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xdd;
	gTunerData[i].tunerRegisterByte[3] = 0xbd;  //band2
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByte[7] = 0x14;
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; // band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x14;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SHARP_2403_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_SHARP_2403_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;//430000;
	gTunerData[i].tunerVHF_LowFreq = 1452500;//1459000;
	gTunerData[i].tunerVHF_HighFreq = 4292500;//4299000;
	gTunerData[i].tunerMaxFreq = 8702500;//8700000;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData[i].tunerBandFreq[0] = 1459000;
	gTunerData[i].tunerBandFreq[1] = 4299000;
	gTunerData[i].tunerBandFreq[2] = 8700000;
	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbd;  //band2
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByte[7] = 0x14;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; // band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x14;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SHARP_2403_DIF;

	i++;
#endif

#ifdef CONFIG_TUNER_SHARP_2406
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 472500;//430000;
	gTunerData[i].tunerVHF_LowFreq = 1429000;//1459000;
	gTunerData[i].tunerVHF_HighFreq = 4299000;//4299000;
	gTunerData[i].tunerMaxFreq = 8700000;//8700000;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData[i].tunerBandFreq[0] = 1429000;
	gTunerData[i].tunerBandFreq[1] = 4299000;
	gTunerData[i].tunerBandFreq[2] = 8700000;
	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xdd;
	gTunerData[i].tunerRegisterByte[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbd; //band2
	gTunerData[i].tunerRegisterByte[7] = 0x14;
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band2
	gTunerData[i].tunerRegisterByteSearch[7] = 0x14;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SHARP_2406;

	i++;
#endif

#ifdef CONFIG_TUNER_SHARP_8402
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;//430000;
	gTunerData[i].tunerVHF_LowFreq = 1612500;//1459000;
	gTunerData[i].tunerVHF_HighFreq = 4262500;//4299000;
	gTunerData[i].tunerMaxFreq = 8642500;//8700000;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData[i].tunerBandFreq[0] = 1612500;
	gTunerData[i].tunerBandFreq[1] = 1812500;
	gTunerData[i].tunerBandFreq[2] = 4262500;
	gTunerData[i].tunerBandFreq[3] = 8642500;
	gTunerData[i].tunerRegisterByte[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByte[1] = 0x11;
	gTunerData[i].tunerRegisterByte[2] = 0xdd;
	gTunerData[i].tunerRegisterByte[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByte[4] = 0x12;
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbd;  //band2
	gTunerData[i].tunerRegisterByte[7] = 0x12;
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByte[9] = 0xbd; //band3
	gTunerData[i].tunerRegisterByte[10] = 0x14;
	gTunerData[i].tunerRegisterByte[11] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd; //band0
	gTunerData[i].tunerRegisterByteSearch[1] = 0x11;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band1
	gTunerData[i].tunerRegisterByteSearch[4] = 0x12;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; // band2
	gTunerData[i].tunerRegisterByteSearch[7] = 0x12; 
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRegisterByteSearch[9] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[10] = 0x14;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _TRUE;
	gTunerData[i].tunerRfInputByte = 1;
	gTunerData[i].tunerRfInputLocation = _BIT3;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 4;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SHARP_8402;

	i++;
#endif

#ifdef CONFIG_TUNER_XUGUANG_DMCT_6A111S_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 432500;
	gTunerData[i].tunerVHF_LowFreq = 1480000;
	gTunerData[i].tunerVHF_HighFreq = 4310000;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1091000;
	gTunerData[i].tunerBandFreq[1] = 1480000;
	gTunerData[i].tunerBandFreq[2] = 1571000;	
	gTunerData[i].tunerBandFreq[3] = 3271000;
	gTunerData[i].tunerBandFreq[4] = 4310000;
	gTunerData[i].tunerBandFreq[5] = 4451000;
	gTunerData[i].tunerBandFreq[6] = 6071000;
	gTunerData[i].tunerBandFreq[7] = 7511000;
	gTunerData[i].tunerBandFreq[8] = 8243500;
	gTunerData[i].tunerBandFreq[9] = 8632500;

	gTunerData[i].tunerRegisterByte[0] = 0xbb; //band1 43.25~109.1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xc0;

	gTunerData[i].tunerRegisterByte[3] = 0xbb; //band2 109.1~148
	gTunerData[i].tunerRegisterByte[4] = 0x01;
	gTunerData[i].tunerRegisterByte[5] = 0xc0;

	gTunerData[i].tunerRegisterByte[6] = 0xbb; //band3 148~157.1
	gTunerData[i].tunerRegisterByte[7] = 0x42;
	gTunerData[i].tunerRegisterByte[8] = 0xc0;

	gTunerData[i].tunerRegisterByte[9] = 0xbb; //band4 157.1~327.1
	gTunerData[i].tunerRegisterByte[10] = 0x02;
	gTunerData[i].tunerRegisterByte[11] = 0xc0;

       gTunerData[i].tunerRegisterByte[12] = 0xbb;  //band5 327.1~431
	gTunerData[i].tunerRegisterByte[13] = 0x82;
	gTunerData[i].tunerRegisterByte[14] = 0xc0;

	gTunerData[i].tunerRegisterByte[15] = 0xbb; //band6 431~445.1
	gTunerData[i].tunerRegisterByte[16] = 0x88;
	gTunerData[i].tunerRegisterByte[17] = 0xc0;

	gTunerData[i].tunerRegisterByte[18] = 0xbb; //band7 445.1~607.1
	gTunerData[i].tunerRegisterByte[19] = 0x48;
	gTunerData[i].tunerRegisterByte[20] = 0xc0;

       gTunerData[i].tunerRegisterByte[21] = 0xbb;  //band8 607.1~751.1
	gTunerData[i].tunerRegisterByte[22] = 0x88;
	gTunerData[i].tunerRegisterByte[23] = 0xc0;
	
	gTunerData[i].tunerRegisterByte[24] = 0xbb; //band9 751.1~824.35
	gTunerData[i].tunerRegisterByte[25] = 0xc8;
	gTunerData[i].tunerRegisterByte[26] = 0xc0;

	gTunerData[i].tunerRegisterByte[27] = 0xbb; //band10 824.35~864.25
	gTunerData[i].tunerRegisterByte[28] = 0xc8;
	gTunerData[i].tunerRegisterByte[29] = 0xc0;
	
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbb; //band1 43.25~109.1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[3] = 0xbb; //band2 109.1~148
	gTunerData[i].tunerRegisterByteSearch[4] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[6] = 0xbb; //band3 148~157.1
	gTunerData[i].tunerRegisterByteSearch[7] = 0x42;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[9] = 0xbb; //band4 157.1~327.1
	gTunerData[i].tunerRegisterByteSearch[10] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xc0;

       gTunerData[i].tunerRegisterByteSearch[12] = 0xbb;  //band5 327.1~431
	gTunerData[i].tunerRegisterByteSearch[13] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[14] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[15] = 0xbb; //band6 431~445.1
	gTunerData[i].tunerRegisterByteSearch[16] = 0x88;
	gTunerData[i].tunerRegisterByteSearch[17] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[18] = 0xbb; //band7 445.1~607.1
	gTunerData[i].tunerRegisterByteSearch[19] = 0x48;
	gTunerData[i].tunerRegisterByteSearch[20] = 0xc0;

       gTunerData[i].tunerRegisterByteSearch[21] = 0xbb;  //band8 607.1~751.1
	gTunerData[i].tunerRegisterByteSearch[22] = 0x88;
	gTunerData[i].tunerRegisterByteSearch[23] = 0xc0;
	
	gTunerData[i].tunerRegisterByteSearch[24] = 0xbb; //band9 751.1~824.35
	gTunerData[i].tunerRegisterByteSearch[25] = 0xc8;
	gTunerData[i].tunerRegisterByteSearch[26] = 0xc0;

	gTunerData[i].tunerRegisterByteSearch[27] = 0xbb; //band10 824.35~864.25
	gTunerData[i].tunerRegisterByteSearch[28] = 0xc8;
	gTunerData[i].tunerRegisterByteSearch[29] = 0xc0;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 10;	
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XUGUANG_DMCT_6A111S_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_LG_TDTR_T032D
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;//4
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner recommend 50KHz for analog use

	gTunerData[i].tunerBandFreq[0] = 1442500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0xbf; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xdd;
	gTunerData[i].tunerRegisterByte[3] = 0xbf;  //band2
	gTunerData[i].tunerRegisterByte[4] = 0x02;
	gTunerData[i].tunerRegisterByte[5] = 0xdd;
	gTunerData[i].tunerRegisterByte[6] = 0xbf; //band3
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByte[8] = 0xdd;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbf; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbf; // band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xfd;
       gTunerData[i].tunerRegisterByteSearch[6] = 0xbf; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfd;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LG_TDTR_T032D;

	i++;
#endif

#ifdef CONFIG_TUNER_LG_TDTR_T032D_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;//4
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner recommend 50KHz for analog use

	gTunerData[i].tunerBandFreq[0] = 1482500;
	gTunerData[i].tunerBandFreq[1] = 4277500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xc1;
	gTunerData[i].tunerRegisterByte[3] = 0xbd;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x02;
	gTunerData[i].tunerRegisterByte[5] = 0xc1;
	gTunerData[i].tunerRegisterByte[6] = 0xbd;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByte[8] = 0xc1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xe1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xe1;
       gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xe1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LG_TDTR_T032D_DIF;
	i++;
#endif

#ifdef CONFIG_TUNER_TCL_DTC86WT_2_E_DIF
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 480000;
	gTunerData[i].tunerVHF_LowFreq = 1470000;
	gTunerData[i].tunerVHF_HighFreq = 4480000;//4
	gTunerData[i].tunerMaxFreq = 8630000;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize =500;  // this tuner recommend 50KHz for analog use

	gTunerData[i].tunerBandFreq[0] = 1480000;
	gTunerData[i].tunerBandFreq[1] = 4485000;
	gTunerData[i].tunerBandFreq[2] = 8630000;
	gTunerData[i].tunerRegisterByte[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbd;//band2
	gTunerData[i].tunerRegisterByte[4] = 0x02;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbd;//band3
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbd;//band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbd; //band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02; 
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
       gTunerData[i].tunerRegisterByteSearch[6] = 0xbd; //band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_DTC86WT_2_E_DIF;
	i++;
#endif


#ifdef CONFIG_TUNER_CHANGHONG_TAF8_C4I13VH
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_CHANGHONG_TAF8_C4I13VH;

	i++;
#endif

#ifdef CONFIG_TUNER_CHANGHONG_TAF8_C4I13VH_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4242500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500;
	gTunerData[i].tunerBandFreq[1] = 4242500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_CHANGHONG_TAF8_C4I13VH_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_TCL_F35CT_6N_E_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 552500;
	gTunerData[i].tunerVHF_LowFreq = 1452500;
	gTunerData[i].tunerVHF_HighFreq = 4512500;
	gTunerData[i].tunerMaxFreq = 8612500;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1452500;
	gTunerData[i].tunerBandFreq[1] = 4512500;
	gTunerData[i].tunerBandFreq[2] = 8612500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F35CT_6N_E_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_NUTUNE_TH2603_BJT

	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1570000;
	gTunerData[i].tunerVHF_HighFreq = 4430000;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize =625;  
	
	gTunerData[i].tunerBandFreq[0] = 1301000;
	gTunerData[i].tunerBandFreq[1] = 1401000;
	gTunerData[i].tunerBandFreq[2] = 1501000;
	gTunerData[i].tunerBandFreq[3] = 1570000;
	gTunerData[i].tunerBandFreq[4] = 3671000;
	gTunerData[i].tunerBandFreq[5] = 3991000;
	gTunerData[i].tunerBandFreq[6] = 4221000;
	gTunerData[i].tunerBandFreq[7] = 4430000;
	gTunerData[i].tunerBandFreq[8] = 7111000;
	gTunerData[i].tunerBandFreq[9] = 7781000;
	gTunerData[i].tunerBandFreq[10] = 8231000;
	gTunerData[i].tunerBandFreq[11] = 8431000;
	gTunerData[i].tunerBandFreq[12] = 8561000;
	gTunerData[i].tunerBandFreq[13] = 8632500;
	
	
	gTunerData[i].tunerRegisterByte[0] = 0xc0; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x86;
	gTunerData[i].tunerRegisterByte[3] = 0x01;
	
	gTunerData[i].tunerRegisterByte[4] = 0xc0; //band2
	gTunerData[i].tunerRegisterByte[5] = 0x21;
	gTunerData[i].tunerRegisterByte[6] = 0x86;
	gTunerData[i].tunerRegisterByte[7] = 0x21;
	
	gTunerData[i].tunerRegisterByte[8] = 0xc0; //band3
	gTunerData[i].tunerRegisterByte[9] = 0x41;
	gTunerData[i].tunerRegisterByte[10] = 0x86;
	gTunerData[i].tunerRegisterByte[11] = 0x41;
	
	gTunerData[i].tunerRegisterByte[12] = 0xc0; //band4
	gTunerData[i].tunerRegisterByte[13] = 0x61;
	gTunerData[i].tunerRegisterByte[14] = 0x86;
	gTunerData[i].tunerRegisterByte[15] = 0x61;
	
	gTunerData[i].tunerRegisterByte[16] = 0xc0; //band5
	gTunerData[i].tunerRegisterByte[17] = 0x02;
	gTunerData[i].tunerRegisterByte[18] = 0x86;
	gTunerData[i].tunerRegisterByte[19] = 0x02;
	
	gTunerData[i].tunerRegisterByte[20] = 0xc0; //band6
	gTunerData[i].tunerRegisterByte[21] = 0x22;
	gTunerData[i].tunerRegisterByte[22] = 0x86;
	gTunerData[i].tunerRegisterByte[23] = 0x22;
	
	gTunerData[i].tunerRegisterByte[24] = 0xc0; //band7
	gTunerData[i].tunerRegisterByte[25] = 0x42;
	gTunerData[i].tunerRegisterByte[26] = 0x86;
	gTunerData[i].tunerRegisterByte[27] = 0x42;
	
	gTunerData[i].tunerRegisterByte[28] = 0xc0; //band8
	gTunerData[i].tunerRegisterByte[29] = 0x62;
	gTunerData[i].tunerRegisterByte[30] = 0x86;
	gTunerData[i].tunerRegisterByte[31] = 0x62;
	
	gTunerData[i].tunerRegisterByte[32] = 0xc0; //band9
	gTunerData[i].tunerRegisterByte[33] = 0x04;
	gTunerData[i].tunerRegisterByte[34] = 0x86;
	gTunerData[i].tunerRegisterByte[35] = 0x04;
	
	gTunerData[i].tunerRegisterByte[36] = 0xc0; //band10
	gTunerData[i].tunerRegisterByte[37] = 0x24;
	gTunerData[i].tunerRegisterByte[38] = 0x86;
	gTunerData[i].tunerRegisterByte[39] = 0x24;
	
	gTunerData[i].tunerRegisterByte[40] = 0xc0; //band11
	gTunerData[i].tunerRegisterByte[41] = 0x44;
	gTunerData[i].tunerRegisterByte[42] = 0x86;
	gTunerData[i].tunerRegisterByte[43] = 0x44; 
	
	gTunerData[i].tunerRegisterByte[44] = 0xc0; //band12
	gTunerData[i].tunerRegisterByte[45] = 0x64;
	gTunerData[i].tunerRegisterByte[46] = 0x86;
	gTunerData[i].tunerRegisterByte[47] = 0x64;	

	gTunerData[i].tunerRegisterByte[48] = 0xc0; //band13
	gTunerData[i].tunerRegisterByte[49] = 0x84;
	gTunerData[i].tunerRegisterByte[50] = 0x86;
	gTunerData[i].tunerRegisterByte[51] = 0x84;	

	gTunerData[i].tunerRegisterByte[52] = 0xc0; //band14
	gTunerData[i].tunerRegisterByte[53] = 0xa4;
	gTunerData[i].tunerRegisterByte[54] = 0x86;
	gTunerData[i].tunerRegisterByte[55] = 0xa4; 	

	
	gTunerData[i].tunerRegisterByteSearch[0] = 0xc0; //band1 
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01; 
	gTunerData[i].tunerRegisterByteSearch[2] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[3] = 0x01;

	gTunerData[i].tunerRegisterByteSearch[4] = 0xc0; //band2 
	gTunerData[i].tunerRegisterByteSearch[5] = 0x21; 
	gTunerData[i].tunerRegisterByteSearch[6] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[7] = 0x21;

	gTunerData[i].tunerRegisterByteSearch[8] = 0xc0; //band3 
	gTunerData[i].tunerRegisterByteSearch[9] = 0x41; 
	gTunerData[i].tunerRegisterByteSearch[10] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[11] = 0x41;

	gTunerData[i].tunerRegisterByteSearch[12] = 0xc0; //band4 
	gTunerData[i].tunerRegisterByteSearch[13] = 0x61; 
	gTunerData[i].tunerRegisterByteSearch[14] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[15] = 0x61;

	gTunerData[i].tunerRegisterByteSearch[16] = 0xc0; //band5 
	gTunerData[i].tunerRegisterByteSearch[17] = 0x02; 
	gTunerData[i].tunerRegisterByteSearch[18] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[19] = 0x02;

	gTunerData[i].tunerRegisterByteSearch[20] = 0xc0; //band6 
	gTunerData[i].tunerRegisterByteSearch[21] = 0x22; 
	gTunerData[i].tunerRegisterByteSearch[22] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[23] = 0x22;

	gTunerData[i].tunerRegisterByteSearch[24] = 0xc0; //band7 
	gTunerData[i].tunerRegisterByteSearch[25] = 0x42; 
	gTunerData[i].tunerRegisterByteSearch[26] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[27] = 0x42;

	gTunerData[i].tunerRegisterByteSearch[28] = 0xc0; //band8 
	gTunerData[i].tunerRegisterByteSearch[29] = 0x62; 
	gTunerData[i].tunerRegisterByteSearch[30] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[31] = 0x62;

	gTunerData[i].tunerRegisterByteSearch[32] = 0xc0; //band9 
	gTunerData[i].tunerRegisterByteSearch[33] = 0x04; 
	gTunerData[i].tunerRegisterByteSearch[34] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[35] = 0x04;

	gTunerData[i].tunerRegisterByteSearch[36] = 0xc0; //band10 
	gTunerData[i].tunerRegisterByteSearch[37] = 0x24; 
	gTunerData[i].tunerRegisterByteSearch[38] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[39] = 0x24;

	gTunerData[i].tunerRegisterByteSearch[40] = 0xc0; //band11 
	gTunerData[i].tunerRegisterByteSearch[41] = 0x44; 
	gTunerData[i].tunerRegisterByteSearch[42] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[43] = 0x44; 

	gTunerData[i].tunerRegisterByteSearch[44] = 0xc0; //band12 
	gTunerData[i].tunerRegisterByteSearch[45] = 0x64; 
	gTunerData[i].tunerRegisterByteSearch[46] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[47] = 0x64;	

	gTunerData[i].tunerRegisterByteSearch[48] = 0xc0; //band13 
	gTunerData[i].tunerRegisterByteSearch[49] = 0x84; 
	gTunerData[i].tunerRegisterByteSearch[50] = 0x8e; 
	gTunerData[i].tunerRegisterByteSearch[51] = 0x84;	

	gTunerData[i].tunerRegisterByteSearch[52] = 0xc0; //band14 
	gTunerData[i].tunerRegisterByteSearch[53] = 0xa4; 
	gTunerData[i].tunerRegisterByteSearch[54] = 0x8e;
	gTunerData[i].tunerRegisterByteSearch[55] = 0xa4;
	
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 14;
	gTunerData[i].tunerRegNoPerBand= 4;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NUTUNE_TH2603_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_NUTUNE_FH2608

	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 482500;
	gTunerData[i].tunerVHF_LowFreq = 1472500;
	gTunerData[i].tunerVHF_HighFreq = 4152500;
	gTunerData[i].tunerMaxFreq = 8552500;
	gTunerData[i].tunerPIF = 389000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerRATIOStepSize =625;  
	
	gTunerData[i].tunerBandFreq[0] = 971000;
	gTunerData[i].tunerBandFreq[1] = 1271000;
	gTunerData[i].tunerBandFreq[2] = 1472500;
	gTunerData[i].tunerBandFreq[3] = 3371000;
	gTunerData[i].tunerBandFreq[4] = 3771000;
	gTunerData[i].tunerBandFreq[5] = 4152500;
	gTunerData[i].tunerBandFreq[6] = 6471000;
	gTunerData[i].tunerBandFreq[7] = 7971000;
	gTunerData[i].tunerBandFreq[8] = 8552500;
	
	gTunerData[i].tunerRegisterByte[0] = 0xbe; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x81;
	gTunerData[i].tunerRegisterByte[2] = 0x9e;
	gTunerData[i].tunerRegisterByte[3] = 0x20;
	
	gTunerData[i].tunerRegisterByte[4] = 0xf6;  //band2
	gTunerData[i].tunerRegisterByte[5] = 0x81;
	gTunerData[i].tunerRegisterByte[6] = 0xde;
	gTunerData[i].tunerRegisterByte[7] = 0x20;
	
	gTunerData[i].tunerRegisterByte[8] = 0xfe; //band3
	gTunerData[i].tunerRegisterByte[9] = 0x81;
	gTunerData[i].tunerRegisterByte[10] = 0xde;
	gTunerData[i].tunerRegisterByte[11] = 0x20;

	gTunerData[i].tunerRegisterByte[12] = 0xbe; //band4
	gTunerData[i].tunerRegisterByte[13] = 0x82;
	gTunerData[i].tunerRegisterByte[14] = 0x9e;
	gTunerData[i].tunerRegisterByte[15] = 0x20;

       gTunerData[i].tunerRegisterByte[16] = 0xf6;  //band5
	gTunerData[i].tunerRegisterByte[17] = 0x82;
	gTunerData[i].tunerRegisterByte[18] = 0xde;
	gTunerData[i].tunerRegisterByte[19] = 0x20;

	gTunerData[i].tunerRegisterByte[20] = 0xfe; //band6
	gTunerData[i].tunerRegisterByte[21] = 0x82;
	gTunerData[i].tunerRegisterByte[22] = 0xde;
	gTunerData[i].tunerRegisterByte[23] = 0x20;

	gTunerData[i].tunerRegisterByte[24] = 0xbe; //band7
	gTunerData[i].tunerRegisterByte[25] = 0x84;
	gTunerData[i].tunerRegisterByte[26] = 0x9e;
	gTunerData[i].tunerRegisterByte[27] = 0x20;

       gTunerData[i].tunerRegisterByte[28] = 0xf6;  //band8
	gTunerData[i].tunerRegisterByte[29] = 0x84;
	gTunerData[i].tunerRegisterByte[30] = 0xde;
	gTunerData[i].tunerRegisterByte[31] = 0x20;

	gTunerData[i].tunerRegisterByte[32] = 0xfe; //band9
	gTunerData[i].tunerRegisterByte[33] = 0x84;
	gTunerData[i].tunerRegisterByte[34] = 0xde;
	gTunerData[i].tunerRegisterByte[35] = 0x20;
	
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbe; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x81;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x9e;
	gTunerData[i].tunerRegisterByteSearch[3] = 0x20;
	
	gTunerData[i].tunerRegisterByteSearch[4] = 0xf6;  //band2
	gTunerData[i].tunerRegisterByteSearch[5] = 0x81;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[7] = 0x20;
	
	gTunerData[i].tunerRegisterByteSearch[8] = 0xfe; //band3
	gTunerData[i].tunerRegisterByteSearch[9] = 0x81;
	gTunerData[i].tunerRegisterByteSearch[10] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[11] = 0x20;

	gTunerData[i].tunerRegisterByteSearch[12] = 0xbe; //band4
	gTunerData[i].tunerRegisterByteSearch[13] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[14] = 0x9e;
	gTunerData[i].tunerRegisterByteSearch[15] = 0x20;

       gTunerData[i].tunerRegisterByteSearch[16] = 0xf6;  //band5
	gTunerData[i].tunerRegisterByteSearch[17] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[18] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[19] = 0x20;

	gTunerData[i].tunerRegisterByteSearch[20] = 0xfe; //band6
	gTunerData[i].tunerRegisterByteSearch[21] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[22] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[23] = 0x20;

	gTunerData[i].tunerRegisterByteSearch[24] = 0xbe; //band7
	gTunerData[i].tunerRegisterByteSearch[25] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[26] = 0x9e;
	gTunerData[i].tunerRegisterByteSearch[27] = 0x20;

       gTunerData[i].tunerRegisterByteSearch[28] = 0xf6;  //band8
	gTunerData[i].tunerRegisterByteSearch[29] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[30] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[31] = 0x20;

	gTunerData[i].tunerRegisterByteSearch[32] = 0xfe; //band9
	gTunerData[i].tunerRegisterByteSearch[33] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[34] = 0xde;
	gTunerData[i].tunerRegisterByteSearch[35] = 0x20;

	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 9;
	gTunerData[i].tunerRegNoPerBand= 4;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NUTUNE_FH2608;

	i++;
#endif
#ifdef CONFIG_TUNER_NUTUNE_FA2333_RFAGC  //modified tuner control setting for NUTUNE sugestion
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0;  // tuner i2c device address
	gTunerData[i].tunerMinFreq = 540000;
	gTunerData[i].tunerVHF_LowFreq = 1900000;
	gTunerData[i].tunerVHF_HighFreq = 4730000;
	gTunerData[i].tunerMaxFreq = 8620000;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;//500

	gTunerData[i].tunerBandFreq[0] = 1360000;
	gTunerData[i].tunerBandFreq[1] = 1660000;
	gTunerData[i].tunerBandFreq[2] = 1890000;
	gTunerData[i].tunerBandFreq[3] = 3760000;
	gTunerData[i].tunerBandFreq[4] = 4360000;
	gTunerData[i].tunerBandFreq[5] = 4720000;
	gTunerData[i].tunerBandFreq[6] = 5060000;
	gTunerData[i].tunerBandFreq[7] = 6860000;
	gTunerData[i].tunerBandFreq[8] = 8360000;
	gTunerData[i].tunerBandFreq[9] = 9030000;
	
	gTunerData[i].tunerRegisterByte[0] = 0xbb;//band0, 
	gTunerData[i].tunerRegisterByte[1] = 0x41;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbb;//band1 //ad
	gTunerData[i].tunerRegisterByte[4] = 0x82;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbb;//band2 //ad
	gTunerData[i].tunerRegisterByte[7] = 0x82;
	gTunerData[i].tunerRegisterByte[8] = 0xd3;
	gTunerData[i].tunerRegisterByte[9] = 0xbb;//band3 //ad
	gTunerData[i].tunerRegisterByte[10] = 0x82;
	gTunerData[i].tunerRegisterByte[11] = 0xd1;
	gTunerData[i].tunerRegisterByte[12] = 0xbb;//band4 //ad
	gTunerData[i].tunerRegisterByte[13] = 0x02;
	gTunerData[i].tunerRegisterByte[14] = 0xd3;
	gTunerData[i].tunerRegisterByte[15] = 0xbb;//band5 //ad
	gTunerData[i].tunerRegisterByte[16] = 0x84;
	gTunerData[i].tunerRegisterByte[17] = 0xd3;
	gTunerData[i].tunerRegisterByte[18] = 0xbb;//band6 //ad
	gTunerData[i].tunerRegisterByte[19] = 0x84;
	gTunerData[i].tunerRegisterByte[20] = 0xd1;
	gTunerData[i].tunerRegisterByte[21] = 0xbb;//band7 //ad
	gTunerData[i].tunerRegisterByte[22] = 0x84;
	gTunerData[i].tunerRegisterByte[23] = 0xd1;
	gTunerData[i].tunerRegisterByte[24] = 0xbb;//band8 //ad
	gTunerData[i].tunerRegisterByte[25] = 0x44;
	gTunerData[i].tunerRegisterByte[26] = 0xd3;
	gTunerData[i].tunerRegisterByte[27] = 0xbb;//band9 //ad
	gTunerData[i].tunerRegisterByte[28] = 0x84;
	gTunerData[i].tunerRegisterByte[29] = 0xd3;


	gTunerData[i].tunerRegisterByteSearch[0] = 0xbb;//band0, 
	gTunerData[i].tunerRegisterByteSearch[1] = 0x41;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xd1; // ives check 
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbb;//band1 //ad
	gTunerData[i].tunerRegisterByteSearch[4] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbb;//band2 //ad
	gTunerData[i].tunerRegisterByteSearch[7] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf3;
	gTunerData[i].tunerRegisterByteSearch[9] = 0xbb;//band3 //ad
	gTunerData[i].tunerRegisterByteSearch[10] = 0x82;
	gTunerData[i].tunerRegisterByteSearch[11] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[12] = 0xbb;//band4 //ad
	gTunerData[i].tunerRegisterByteSearch[13] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[14] = 0xf3;
	gTunerData[i].tunerRegisterByteSearch[15] = 0xbb;//band5 //ad
	gTunerData[i].tunerRegisterByteSearch[16] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[17] = 0xf3;
	gTunerData[i].tunerRegisterByteSearch[18] = 0xbb;//band6 //ad
	gTunerData[i].tunerRegisterByteSearch[19] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[20] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[21] = 0xbb;//band7 //ad
	gTunerData[i].tunerRegisterByteSearch[22] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[23] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[24] = 0xbb;//band8 //ad
	gTunerData[i].tunerRegisterByteSearch[25] = 0x44;
	gTunerData[i].tunerRegisterByteSearch[26] = 0xf3;
	gTunerData[i].tunerRegisterByteSearch[27] = 0xbb;//band9 //ad
	gTunerData[i].tunerRegisterByteSearch[28] = 0x84;
	gTunerData[i].tunerRegisterByteSearch[29] = 0xf3;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

		

	gTunerData[i].tunerBandNo = 10;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NUTUNE_FA2333_RFAGC;

	i++;
#endif
#ifdef CONFIG_TUNER_TCL_F21WT_3DKR_BJT
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 497500;
	gTunerData[i].tunerVHF_LowFreq = 1602500;
	gTunerData[i].tunerVHF_HighFreq = 4642500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1602500;
	gTunerData[i].tunerBandFreq[1] = 4642500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x8e; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0x8e; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x02;
	gTunerData[i].tunerRegisterByte[4] = 0x8e; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xce; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xce; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[4] = 0xce; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x08;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 2;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_TCL_F21WT_3DKR_BJT;

	i++;
#endif

#ifdef CONFIG_TUNER_PANASONIC_ENV56XXXD8F
	if((i+1)>_Tuner_MAX_NO)                                                                                 
       {                                                                                                  
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");     
		while(1);                                                                                             
	}                                                                                                       
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address //c2
	gTunerData[i].tunerMinFreq = 522500;//542500
	gTunerData[i].tunerVHF_LowFreq = 1680000;
	gTunerData[i].tunerVHF_HighFreq = 4680000;
	gTunerData[i].tunerMaxFreq = 8640000;
	gTunerData[i].tunerPIF = 457500;  
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize =625;  
                                                                                                          
	gTunerData[i].tunerBandFreq[0] = 1440000;                                                               
	gTunerData[i].tunerBandFreq[1] = 1680000;                                                               
	gTunerData[i].tunerBandFreq[2] = 4320000;                                                               
	gTunerData[i].tunerBandFreq[3] = 4680000;                                                               
	gTunerData[i].tunerBandFreq[4] = 8120000;
	gTunerData[i].tunerBandFreq[5] = 8640000;


	gTunerData[i].tunerRegisterByte[0] = 0xa3;  // 0xbb; //band1  //0xa3: Tuner RFAGC, IC IFAGC, 0xbb: IC RF/IFAGC
	gTunerData[i].tunerRegisterByte[1] = 0x09;                                                              
	gTunerData[i].tunerRegisterByte[2] = 0xd1;                             
	gTunerData[i].tunerRegisterByte[3] = 0xa3;  // 0xbb;  //band2                                                     
	gTunerData[i].tunerRegisterByte[4] = 0x49;                                                              
	gTunerData[i].tunerRegisterByte[5] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[6] = 0xa3;  // 0xbb; //band3                                                      
	gTunerData[i].tunerRegisterByte[7] = 0x02;                                                              
	gTunerData[i].tunerRegisterByte[8] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[9] = 0xa3;  // 0xbb; //band4
	gTunerData[i].tunerRegisterByte[10] = 0x42;                                                              
	gTunerData[i].tunerRegisterByte[11] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[12] = 0xa3;  // 0xbb; //band5                                                      
	gTunerData[i].tunerRegisterByte[13] = 0x04;                                                              
	gTunerData[i].tunerRegisterByte[14] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[15] = 0xa3;  // 0xbb; //band6
	gTunerData[i].tunerRegisterByte[16] = 0x44;                                                              
	gTunerData[i].tunerRegisterByte[17] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xa3;  // 0xbb; //band1                                                
	gTunerData[i].tunerRegisterByteSearch[1] = 0x09;                                                        
	gTunerData[i].tunerRegisterByteSearch[2] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[3] = 0xa3;  // 0xbb; //band2  
	gTunerData[i].tunerRegisterByteSearch[4] = 0x49;                                                        
	gTunerData[i].tunerRegisterByteSearch[5] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xa3;  // 0xbb; //band3                                           
	gTunerData[i].tunerRegisterByteSearch[7] = 0x02;                                                        
	gTunerData[i].tunerRegisterByteSearch[8] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[9] = 0xa3;  // 0xbb; //band4
	gTunerData[i].tunerRegisterByteSearch[10] = 0x42;                                                        
	gTunerData[i].tunerRegisterByteSearch[11] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[12] = 0xa3;  // 0xbb; // band5                                               
	gTunerData[i].tunerRegisterByteSearch[13] = 0x04;                                                        
	gTunerData[i].tunerRegisterByteSearch[14] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[15] = 0xa3;  // 0xbb; //band6                                           
	gTunerData[i].tunerRegisterByteSearch[16] = 0x44;                                                        
	gTunerData[i].tunerRegisterByteSearch[17] = 0xd1;  
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;
	
	gTunerData[i].tunerBandNo = 6; 
	gTunerData[i].tunerRegNoPerBand= 3;                                                                     
	gTunerData[i].tunerUsedTag = _FALSE;                                                                    
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;                                                       
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_PANASONIC_ENV56XXXD8F;                     
                                                                                                         
	i++;                                                                                                    
#endif                                                                                                    




#ifdef CONFIG_TUNER_PANASONIC_ENV56XXXD8F_RFAGC

	if((i+1)>_Tuner_MAX_NO)                                                                                 
       {                                                                                                  
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");     
		while(1);                                                                                             
	}                                                                                                       
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address //c2
	gTunerData[i].tunerMinFreq = 522500;
	gTunerData[i].tunerVHF_LowFreq = 1680000;
	gTunerData[i].tunerVHF_HighFreq = 4680000;
	gTunerData[i].tunerMaxFreq = 8640000;
	gTunerData[i].tunerPIF = 457500;        
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;                                                                       
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize =625;  
                                                                                                          
	gTunerData[i].tunerBandFreq[0] = 1440000;                                                               
	gTunerData[i].tunerBandFreq[1] = 1680000;                                                               
	gTunerData[i].tunerBandFreq[2] = 4320000;                                                               
	gTunerData[i].tunerBandFreq[3] = 4680000;                                                               
	gTunerData[i].tunerBandFreq[4] = 8120000;
	gTunerData[i].tunerBandFreq[5] = 8640000;

	gTunerData[i].tunerRegisterByte[0] = 0xbb;  // 0xbb; //band1  //0xa3: Tuner RFAGC, IC IFAGC, 0xbb: IC RF/IFAGC
	gTunerData[i].tunerRegisterByte[1] = 0x09;                                                              
	gTunerData[i].tunerRegisterByte[2] = 0xd1;                             
	gTunerData[i].tunerRegisterByte[3] = 0xbb;  // 0xbb;  //band2                                                     
	gTunerData[i].tunerRegisterByte[4] = 0x49;                                                              
	gTunerData[i].tunerRegisterByte[5] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[6] = 0xbb;  // 0xbb; //band3                                                      
	gTunerData[i].tunerRegisterByte[7] = 0x02;                                                              
	gTunerData[i].tunerRegisterByte[8] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[9] = 0xbb;  // 0xbb; //band4
	gTunerData[i].tunerRegisterByte[10] = 0x42;                                                              
	gTunerData[i].tunerRegisterByte[11] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[12] = 0xbb;  // 0xbb; //band5                                                      
	gTunerData[i].tunerRegisterByte[13] = 0x04;                                                              
	gTunerData[i].tunerRegisterByte[14] = 0xd1;                                                              
	gTunerData[i].tunerRegisterByte[15] = 0xbb;  // 0xbb; //band6
	gTunerData[i].tunerRegisterByte[16] = 0x44;                                                              
	gTunerData[i].tunerRegisterByte[17] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbb;  // 0xbb; //band1                                                
	gTunerData[i].tunerRegisterByteSearch[1] = 0x09;                                                        
	gTunerData[i].tunerRegisterByteSearch[2] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbb;  // 0xbb; //band2  
	gTunerData[i].tunerRegisterByteSearch[4] = 0x49;                                                        
	gTunerData[i].tunerRegisterByteSearch[5] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbb;  // 0xbb; //band3                                           
	gTunerData[i].tunerRegisterByteSearch[7] = 0x02;                                                        
	gTunerData[i].tunerRegisterByteSearch[8] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[9] = 0xbb;  // 0xbb; //band4
	gTunerData[i].tunerRegisterByteSearch[10] = 0x42;                                                        
	gTunerData[i].tunerRegisterByteSearch[11] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[12] = 0xbb;  // 0xbb; // band5                                               
	gTunerData[i].tunerRegisterByteSearch[13] = 0x04;                                                        
	gTunerData[i].tunerRegisterByteSearch[14] = 0xd1;                                                        
	gTunerData[i].tunerRegisterByteSearch[15] = 0xbb;  // 0xbb; //band6                                           
	gTunerData[i].tunerRegisterByteSearch[16] = 0x44;                                                        
	gTunerData[i].tunerRegisterByteSearch[17] = 0xd1;    
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0; 
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 6; 
	gTunerData[i].tunerRegNoPerBand= 3;                                                                     
	gTunerData[i].tunerUsedTag = _FALSE;                                                                    
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC; //TUNER_NONE_IC_RFAGC;                                                       
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_PANASONIC_ENV56XXXD8F_RFAGC;                     
                                                                                                         
	i++;                                                                                                    
#endif                                                                                                    

#ifdef CONFIG_TUNER_LG_TDTK_H801F
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 540000;
	gTunerData[i].tunerVHF_LowFreq = 1650000;
	gTunerData[i].tunerVHF_HighFreq = 4490000;
	gTunerData[i].tunerMaxFreq = 8660000;
	gTunerData[i].tunerPIF = 457500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_45P75M;       
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_45P75M;
	gTunerData[i].tunerRATIOStepSize = 625;//500

	gTunerData[i].tunerBandFreq[0] = 1650000;
	gTunerData[i].tunerBandFreq[1] = 4490000;
	gTunerData[i].tunerBandFreq[2] = 8660000;
	gTunerData[i].tunerRegisterByte[0] = 0xbb;//band1, //ab //ad,  //RFAGC bb
	gTunerData[i].tunerRegisterByte[1] = 0x01;
	gTunerData[i].tunerRegisterByte[2] = 0xd1;
	gTunerData[i].tunerRegisterByte[3] = 0xbb;//band2 //ad
	gTunerData[i].tunerRegisterByte[4] = 0x02;
	gTunerData[i].tunerRegisterByte[5] = 0xd1;
	gTunerData[i].tunerRegisterByte[6] = 0xbb;//band3 //ad
	gTunerData[i].tunerRegisterByte[7] = 0x08;
	gTunerData[i].tunerRegisterByte[8] = 0xd1;
	gTunerData[i].tunerRegisterByteSearch[0] = 0xbb;//band1 //0xad
	gTunerData[i].tunerRegisterByteSearch[1] = 0x01;
	gTunerData[i].tunerRegisterByteSearch[2] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[3] = 0xbb;//band2
	gTunerData[i].tunerRegisterByteSearch[4] = 0x02;
	gTunerData[i].tunerRegisterByteSearch[5] = 0xf1;
	gTunerData[i].tunerRegisterByteSearch[6] = 0xbb;//band3
	gTunerData[i].tunerRegisterByteSearch[7] = 0x08;
	gTunerData[i].tunerRegisterByteSearch[8] = 0xf1;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=_BIT6;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 3;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_POS_IF_POS;
	gTunerData[i].tunerType = TUNER_NORMAL;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_LG_TDTK_H801F;

	i++;
#endif

	gTunerNo = i;
	//if(gTunerActiveID == TUNER_NULL)
	//	gTunerActiveID = gTunerData[0].tunerID;

	for(i=0;i<gTunerNo;i++)
		gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
#endif
}
//#endif
//#if defined(CONFIG_TUNER_LOWIF_TYPE)||(CONFIG_Tuner_Max_NUMBER>1)
void tuner_lowif_data_init(void){
#if 0
	UINT8 i=gTunerNo;
	
	IFD_DEBUG_MSG(IFD_MSG_INIT,"tuner_lowif_data_init\n");

	#ifdef CONFIG_TUNER_NXP_TDA18272
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 3680000;
	gTunerData[i].tunerVHF_HighFreq = 8660000;
	gTunerData[i].tunerMaxFreq = 8660000;
	gTunerData[i].tunerPIF = 54000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_5P4M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_6P4M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P25M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_7P5M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_2P25M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 3680000;
	gTunerData[i].tunerBandFreq[1] = 8660000;
	gTunerData[i].tunerBandFreq[2] = 8660000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 2;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NXP_TDA18272;

	i++;
	#endif
	#ifdef CONFIG_TUNER_NXP_TDA18273
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 3680000;
	gTunerData[i].tunerVHF_HighFreq = 8660000;
	gTunerData[i].tunerMaxFreq = 8660000;
	gTunerData[i].tunerPIF = 54000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_5P5M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_6P6M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_6P6M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P45M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_6P85M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_1P25M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_6P85M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 3680000;
	gTunerData[i].tunerBandFreq[1] = 8660000;
	gTunerData[i].tunerBandFreq[2] = 8660000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 2;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_NXP_TDA18273;

	i++;
	#endif
	#ifdef CONFIG_TUNER_SONY_RX201
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	IFD_DEBUG_MSG(IFD_MSG_INIT, "[IFD ]Tuner table SONY RX201 \n" );
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 1792500;
	gTunerData[i].tunerVHF_HighFreq = 4672500;
	gTunerData[i].tunerMaxFreq = 8660000;
	gTunerData[i].tunerPIF = 57500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_5P4M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_6P4M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P25M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_7P5M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_2P25M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 3680000;
	gTunerData[i].tunerBandFreq[1] = 8660000;
	gTunerData[i].tunerBandFreq[2] = 8660000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 2;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_NEG;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SONY_RX201;

	i++;
	#endif
	#ifdef CONFIG_TUNER_RAFAEL_RT810
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0x34; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 1442500;
	gTunerData[i].tunerVHF_HighFreq = 4322500;
	gTunerData[i].tunerMaxFreq = 9000000;
	gTunerData[i].tunerPIF = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_5P82M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_7P82M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1442500;
	gTunerData[i].tunerBandFreq[1] = 4322500;
	gTunerData[i].tunerBandFreq[2] = 9000000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_RAFAEL_RT810;

	i++;
	#endif
	#ifdef CONFIG_TUNER_MAXIM_MAX3543
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	//TODO : need to be confirmed
	gTunerData[i].tunerI2C_ADD = 0xc2; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 472500;
	gTunerData[i].tunerVHF_LowFreq = 1960000;
	gTunerData[i].tunerVHF_HighFreq = 4400000;
	gTunerData[i].tunerMaxFreq = 8620000;
	gTunerData[i].tunerPIF = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_33P1M;//todo : have to check
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38P9M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1960000;
	gTunerData[i].tunerBandFreq[1] = 4400000;
	gTunerData[i].tunerBandFreq[2] = 8620000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_SILICON_NORMAL; // this is silicon tuner with normal IF freq
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_MAXIM_MAX3543;

	i++;
	#endif
	#ifdef CONFIG_TUNER_MAXLINEAR_MXL301RF
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 442500;
	gTunerData[i].tunerVHF_LowFreq = 3342500;
	gTunerData[i].tunerVHF_HighFreq = 10022500;
	gTunerData[i].tunerMaxFreq = 10022500;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_5P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P25M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_7P25M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_7P25M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_1P25M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_6P75M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 3342500;
	gTunerData[i].tunerBandFreq[1] = 10022500;
	gTunerData[i].tunerBandFreq[2] = 10022500;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_MAXLINEAR_MXL301RF;

	i++;
	#endif


	#ifdef CONFIG_TUNER_XCEIVE_XC5200
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	//TODO : need to be confirmed
	gTunerData[i].tunerI2C_ADD = 0xc2; 
	gTunerData[i].tunerMinFreq = 422500;
	gTunerData[i].tunerVHF_LowFreq = 3342500;
	gTunerData[i].tunerVHF_HighFreq = 10022500;
	gTunerData[i].tunerMaxFreq = 8650000;
	gTunerData[i].tunerPIF = 380000;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_3P52M;
	//gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_7P02M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_3P52M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_POS;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 3342500;
	gTunerData[i].tunerBandFreq[1] = 10022500;
	gTunerData[i].tunerBandFreq[2] = 10022500;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_XCEIVE_XC5200;

	i++;
	#endif

	#ifdef CONFIG_TUNER_ENTR_EN402X
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_LOG_LEVEL, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 472500;
	gTunerData[i].tunerVHF_LowFreq = 1960000;
	gTunerData[i].tunerVHF_HighFreq = 4400000;
	gTunerData[i].tunerMaxFreq = 8620000;
	gTunerData[i].tunerPIF = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_38M;//todo : have to check
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1960000;
	gTunerData[i].tunerBandFreq[1] = 4400000;
	gTunerData[i].tunerBandFreq[2] = 8620000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_SILICON_NORMAL; // this is silicon tuner with normal IF freq
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_ENTR_EN402X;

	i++;
	#endif

	#ifdef CONFIG_TUNER_FRESCO_FM2150
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_TUNER, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 472500;
	gTunerData[i].tunerVHF_LowFreq = 1960000;
	gTunerData[i].tunerVHF_HighFreq = 4400000;
	gTunerData[i].tunerMaxFreq = 8620000;
	gTunerData[i].tunerPIF = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_38M;//todo : have to check
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 625;

	gTunerData[i].tunerBandFreq[0] = 1960000;
	gTunerData[i].tunerBandFreq[1] = 4400000;
	gTunerData[i].tunerBandFreq[2] = 8620000;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 3;
	gTunerData[i].tunerRegNoPerBand= 1;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_SILICON_NORMAL; // this is silicon tuner with normal IF freq
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_FRESCO_FM2150;

	i++;
	#endif

	#ifdef CONFIG_TUNER_SILICONLABS_SI2156
	if((i+1)>_Tuner_MAX_NO)
       {
	       IFD_DEBUG_MSG(IFD_MSG_INIT, "The number of tuner selected exceed the Tuner Max Number.\n");
		while(1);
	}
	gTunerData[i].tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData[i].tunerMinFreq = 452500;
	gTunerData[i].tunerVHF_LowFreq = 8632500;
	gTunerData[i].tunerVHF_HighFreq = 8632500;
	gTunerData[i].tunerMaxFreq = 8632500;
	gTunerData[i].tunerPIF = 77500;
	gTunerData[i].tunerPIF_MN = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_B = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_GH = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_I = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_DK = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_L = IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerPIF_LA = IFD_IF_FREQ_2P25M;
	gTunerData[i].tunerPIF_SCAN= IFD_IF_FREQ_7P75M;
	gTunerData[i].tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData[i].tunerRATIOStepSize = 500;

	gTunerData[i].tunerBandFreq[0] = 8632500;
	gTunerData[i].tunerBandFreq[1] = 8632500;
	gTunerData[i].tunerBandFreq[2] = 8632500;
	gTunerData[i].tunerRegisterByte[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByte[1] = 0x00;
	gTunerData[i].tunerRegisterByte[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByte[3] = 0x00;
	gTunerData[i].tunerRegisterByte[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByte[5] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[0] = 0x00; //band1
	gTunerData[i].tunerRegisterByteSearch[1] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[2] = 0x00; //band2
	gTunerData[i].tunerRegisterByteSearch[3] = 0x00;
	gTunerData[i].tunerRegisterByteSearch[4] = 0x00; //band3
	gTunerData[i].tunerRegisterByteSearch[5] = 0x00;
	gTunerData[i].tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData[i].tunerRfInputByte = 0;
	gTunerData[i].tunerRfInputLocation = 0;
	gTunerData[i].tunerFLStatusBit=0;

	gTunerData[i].tunerBandNo = 0;
	gTunerData[i].tunerRegNoPerBand= 0;
	gTunerData[i].tunerUsedTag = _FALSE;
	gTunerData[i].tunerAGCtype = TUNER_RFAGC_IC_IFAGC;
	gTunerData[i].tunerAGCpolarity = TUNER_RF_NONE_IF_POS;
	gTunerData[i].tunerType = TUNER_LOW_IF;
	gTunerData[i].tunerSpecificTag = 0;
	gTunerData[i].tunerID = TUNER_SILICONLABS_SI2156;

	i++;
	#endif

	gTunerNo = i;
	//if(gTunerActiveID == TUNER_NULL)
		//gTunerActiveID = gTunerData[2].tunerID;
#endif
}
//#endif


