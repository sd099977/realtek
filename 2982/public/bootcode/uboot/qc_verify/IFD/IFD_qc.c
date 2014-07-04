#if 1
/******************************************************
 Include Files
******************************************************/
#include <qc_verify_common.h>
#include "IFD_qc.h"
#include "ifd_driver.h"

#include "ifd_sirius_agc.c"
#include "ifd_sirius_analog.c"
#include "ifd_sirius_audio.c"
#include "ifd_sirius_cr.c"
#include "ifd_sirius_video.c"

/******************************************************
General Variations 
******************************************************/
bool g_scan_flag=0;
UINT8 g_scan_curr_audio_std=0xff;
UINT8 g_curr_audio_std=0xff;

extern StructIFDDataType stIFDUserData;
extern ATV_TUNER_MODULE *pTuner;

/******************************************************
Functions Definition
******************************************************/
void drv_ifd_reset_nco()
{
	rtd_outl(IFD_CR_FREQ_SAT_VADDR , 0x00000000);
	ScalerTimer_DelayXms(300); 
	rtd_outl(IFD_CR_FREQ_SAT_VADDR , 0x0a000);
}

static  void drv_ifd_reset(void)	 //reset vdc by delezue for ifd
{
	rtd_maskl(CRT_SOFT_RESET2_VADDR, ~(_BIT16 | _BIT17), _BIT16 | _BIT17);   
	rtd_maskl(CRT_SOFT_RESET3_VADDR, ~(_BIT11|_BIT5),  _BIT11|_BIT5);//IFD_SOFT_RESET3
	rtd_maskl(CRT_GROUP1_CK_EN_VADDR, ~(_BIT26|_BIT23|_BIT16),  _BIT26|_BIT23|_BIT16);//CLKEN_IF_DEMOD 
	rtd_maskl(CRT_GROUP1_CK_SEL_VADDR, ~_BIT17, 0<<17);	//ATVIN_CLK_SEL
	udelay(100000);
}

static void drv_ifd_vd_reset(void)	//reset vdc by delezue for ifd
{
	soft_reset3_RBUS soft_reset3_reg;
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec = 0;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
	udelay(10000);
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec = 1;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
}

void drv_ifd_pinshare(void)
{
	IFD_QC_FUNC();
	
	//If AGC 
	rtd_maskl(PINMUX_GPIO_CFG_0_VADDR,~(0xff<<24),(0x9C<<24));

	//I2C pin mux
	#if CONFIG_BGA
		rtd_maskl(0xb80008fc,~(0x7<<4),(0x3<<4));
		rtd_maskl(0xb8000888,~(0x1f<<27),(0xf<<27));
		rtd_maskl(0xb8000874,~(0x1f<<9),(0xf<<9));
	#else
		#if 0//I2C0
		rtd_maskl(0xb80602a0,~(0x1f<<7),(0x7<<7));
		rtd_maskl(PINMUX_GPIO_CFG_0_VADDR,~(0x1f<<18),(0x11<<18));
		rtd_maskl(PINMUX_GPIO_CFG_1_VADDR,~(0x1f<<27),(0x11<<27));
		#else//I2C1
		rtd_maskl(0xb80602a0,~(0x1f<<7),(0x0<<7));
		rtd_maskl(PINMUX_GPIO_CFG_0_VADDR,~(0x1f<<18),(0x12<<18));
		rtd_maskl(PINMUX_GPIO_CFG_1_VADDR,~(0x1f<<27),(0x12<<27));
		#endif
	#endif
	
}

void drvif_ifd_init(void)
{
	IFD_QC_FUNC();
	drv_ifd_tuner_BuildTuner();
	drv_ifd_set_adc_init();
	drvif_scaleri2c_tuner_init();//initial I2C
}

void drv_ifd_delay_ms(UINT32 ms)
{
	UINT32 test_i;
	for(test_i=0;test_i++;test_i<10000) ;
}

/******************************************************
Variations Definition (by Config)
******************************************************/
#ifdef Test_IFD_QC_TunerIfdFreq_Verify
#define VIDEO_TEST_TIME 100
#define RF_FREQ_NUM 3
UINT32 rf_freq[RF_FREQ_NUM]={772500,2232500,5292500,};
UINT8 rf_status[RF_FREQ_NUM];
#endif

#ifdef Test_IFD_QC_Gain_Verify
#define GAIN_FREQ_NUM 1
#define GAIN_AVG_SHIFT 3
#define GAIN_TEST_TIME (1<<GAIN_AVG_SHIFT)
UINT32 gain_freq[GAIN_FREQ_NUM]={4152500,};
UINT8 gain_status[GAIN_FREQ_NUM];
#define GAIN_TARGET 0x100
#endif

/******************************************************
Functions Definition (by Config)
******************************************************/
#ifdef Test_IFD_QC_TunerIfdFreq_Verify
void drvif_vdc_ifd_path_setting(UINT8 on_off)
{
	if(on_off)
		rtd_maskl(VDC_INOUT_CTRL_VADDR,~(_BIT3|_BIT1|_BIT0), _BIT3|_BIT1|_BIT0); // 1_9080, INOUT_CTRL
	else
		rtd_maskl(VDC_INOUT_CTRL_VADDR,~(_BIT3|_BIT1|_BIT0), 0x00);	// 1_9080
}
UINT8 drv_ifd_vd_check_hvlock(void)
{
	UINT32 Data[1];
	udelay(100);
	Data[0]=(UINT32)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR);
	IFD_QC_MSG("[drv_ifd_vd_check_hvlock] =%x\n",(Data[0]&0xf));
	if (!(Data[0] & _BIT0))
	{
		if ((Data[0] & _BIT1) && (Data[0] & _BIT2))
		{
			IFD_QC_MSG( "[drv_ifd_vd_check_hvlock] VDC Locked\n");
			return 1;
		}
	}
	return 0;
}
UINT8 drv_ifd_vd_get_noise_status(void)
{
	UINT8 noise;
	noise = (UINT8)rtd_inl(VDC_NOISE_STATUS_VADDR);	
	return noise;
}
#endif

#ifdef Test_IFD_QC_AudioPerFoms_Verify
 void drv_ifd_audio_aud_DrClock()
{
	rtd_maskl(AUDIO_GLOBAL_CTRL_1_VADDR, ~(_BIT31|_BIT30|_BIT29|_BIT28), _BIT31|_BIT30|_BIT29|_BIT28);//SDRAM on
	rtd_maskl(AUDIO_GLOBAL_CTRL_1_VADDR, ~(_BIT20), _BIT20);//SIF ADC CLOCK on
	rtd_maskl(AUDIO_GLOBAL_CTRL_1_VADDR, ~(_BIT13|_BIT12|_BIT5|_BIT4), _BIT13|_BIT5);//PLL AUDIO

}
void drv_ifd_audio_aud_DrBaseband()
{
	rtd_maskl(AUDIO_ANALOG_DEPOP2_VADDR, ~(_BIT8|_BIT7|_BIT3), _BIT8|_BIT7|_BIT3);//enable output normal mode FOR HP/AIO1/AIO2
	rtd_maskl(VDAC_VADDR, ~(_BIT20),_BIT20);// turn on "REG_VDAC_POWMBIAS" for BB audio
	rtd_outl(AUDIO_ANALOG_POWER_VADDR, 0x00007ff8);// turn on all Audio Power exclude bit11 of bit0~bit14
	#ifdef config_Audio_biascurrent_30u
	rtd_maskl(AUDIO_ANALOG_CI01_VADDR, ~(_BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22), _BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22);//AIO1 & AIO2 & HP BIAS current 30u
	#endif
}
void drv_ifd_audio_aud_DrGpio()
{
}
void drv_ifd_audio_aud_DrSIF()
{
}
static void drv_ifd_audio_initial()
{
	IFD_QC_FUNC();
	//aud_DrPLL();
	rtd_outl(AUDIO_SYS_PLL_AUD3_VADDR, _BIT3);
	rtd_maskl(0xb8000000, ~(_BIT15), _BIT15);	//Reset bit of AIO
	rtd_maskl(0xb8000008, ~(_BIT8|_BIT7|_BIT6), _BIT8|_BIT7|_BIT6); //Reset bit of Audio
	rtd_maskl(0xb800000c, ~(_BIT10), _BIT10); //Clock enable bit for AIO
	rtd_maskl(0xb8000014, ~(_BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12), _BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12); // Clock enable bit for Audio ¡V ADC and DAC1 analog_part 
	drv_ifd_audio_aud_DrClock();
	drv_ifd_audio_aud_DrBaseband();
	drv_ifd_audio_aud_DrGpio();
	drv_ifd_audio_aud_DrSIF();
	rtd_outl(AUDIO_AIN_COMPARE_VADDR, 0xFFFFFFFF);// set Ain timer
	rtd_outl(AUDIO_AOUT_COMPARE_VADDR, 0xFFFFFFFF);;// set AOUT timer
	// SIF audio related setting
	rtd_outl(0xb8006180, 0x000b0180); //SIF HW AGC enable
	rtd_outl(0xb8006350, 0x00000000); //from IFD
	//Audio MSD setting
	rtd_outl(0xb8006200, 0x30C80617); //HW msd_en all hw scan
	rtd_outl(0xb8006300, 0x00000004); //HW md_en
	udelay(20);
	IFD_QC_MSG("Init Audio Done\n");
}
#endif

#ifdef Test_IFD_QC_AVOUT_Verify
bool module_ifd_vdc_Test_Y_Path(UINT8 Y_path, UINT8 Gnd_path)
{
	return _SUCCESS;
}
#endif

/******************************************************
IFD QC Code
******************************************************/
#ifdef Test_IFD_QC_CRC_Verify

UINT8 CIFD_CRC_108M_New(bool eq_en, UINT16 *eqTable, bool output_en, UINT16 *outputTable, bool grpdelay_en, UINT16 *grdyTable, UINT32 crc_in)
{

	UINT8 RetryCRC=5, Diff_Cnt=0;
	UINT32 crc_out;
	UINT8 Sta_Value=_FAIL;
	UINT32 bw=0,delay=0,EQ_FILTER=0;
	IFD_QC_MSG( "[CRC108M] IFD CRC 108M Start xxxxxxxxxxxxxxxxx\n");
	IFD_QC_MSG( "[CRC108M] eq_en=%d, output_en=%d, grpdelay_en=%d\n",eq_en, output_en,grpdelay_en);

	drv_ifd_power_on(IFD_DISABLE);
	udelay(500);
	drv_ifd_power_on(IFD_ENABLE);
	udelay(500);

	//CRC enable
	rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x4c);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x03);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x80);
	
	//setting
	drv_ifd_set_eq_coef(eqTable);
	drv_ifd_eq_en(eq_en);
	drv_ifd_video_outputlpf_coef_update(output_en, outputTable);
	drv_ifd_grp_delay_en(grpdelay_en, grdyTable);
	if(output_en==1) drv_ifd_set_video_bw(1);
	else drv_ifd_set_video_bw(0);
	IFD_QC_MSG( "[CRC108M]eq_en=%d, output_en=%d, grpdelay_en=%d\n",drv_ifd_eq_en_get_info(), drv_ifd_video_outputlpf_en_get_info(),drv_ifd_grp_delay_en_get_info());
	
	drv_ifd_eq_en(0);
	drv_ifd_soft_reset(1);
	udelay(500);
	drv_ifd_eq_en(eq_en);
	drv_ifd_soft_reset(0);
	udelay(500);

	do {
		crc_out=rtd_inl(IFD_108M_CRC3_CTRL_RESULT_VADDR)>>4;	
		IFD_QC_MSG(  "[CRC108M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
		if(crc_in==crc_out) break;
		udelay(100);
		RetryCRC--;
    	}while(RetryCRC);
	
	rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x00);
	
	if(RetryCRC>0)
	{          
		Sta_Value =_SUCCESS;
		IFD_QC_MSG( "[CRC108M]IFD CRC 108M Verify OK \n");
	}
	else
	{
		IFD_QC_MSG_WARNING( "[CRC108M] IFD CRC 108M Verify Wrong \n");
		IFD_QC_MSG_WARNING( "[CRC108M] eq_en=%d, output_en=%d, grpdelay_en=%d\n",drv_ifd_eq_en_get_info(), drv_ifd_video_outputlpf_en_get_info(),drv_ifd_grp_delay_en_get_info());
		IFD_QC_MSG_WARNING( "[CRC108M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
          	Sta_Value =_FAIL;
	}
	return  Sta_Value;

}

UINT8 CIFD_CRC_108M_Test_Case(void)
{

	UINT8  IFD_Value = _SUCCESS;
	UINT8 i, j, k,I=0,J=0,K=0;
	UINT8 Index_table[]={1,1,1,1};
	
	StructEQNotch EqTable[]=
	{
		 
		{  
              0x001, 0x3ff, 0x002, 0x3fe,   
              0x002, 0x3ff, 0x001, 0x000,   
              0x000, 0x001, 0x3ff, 0x002,   
              0x3fe, 0x001, 0x001, 0x3fe,   
              0x003, 0x3fe, 0x001, 0x000,   
              0x000, 0x001, 0x3ff, 0x004,   
              0x3fa, 0x009, 0x3fc, 0x3fd,   
              0x019, 0x3dd, 0x06e, 0x131,   
       	},
	};
	StructOuputLpfCoef OuputLpfCoefTable[]=
	{
		
		{  
              0x3FFF, 0x000A, 0x0019, 0x0002, 0x3FE6,  
              0x0003, 0x001A, 0x3FF1, 0x3FED, 0x001A,   
              0x0004, 0x3FE3, 0x0010, 0x0013, 0x3FE2,   
              0x0001, 0x001E, 0x3FE9, 0x3FF3, 0x0022,   
              0x3FF3, 0x3FE7, 0x0020, 0x0000, 0x3FDF,   
              0x001B, 0x000D, 0x3FDA, 0x0012, 0x0019,   
              0x3FDA, 0x0006, 0x0022, 0x3FDD, 0x3FFA,   
              0x002A, 0x3FE4, 0x3FED, 0x002D, 0x3FEE,   
              0x3FE1, 0x002E, 0x3FFA, 0x3FD6, 0x002B,   
              0x0007, 0x3FCD, 0x0024, 0x0016, 0x3FC8,   
              0x001A, 0x0025, 0x3FC5, 0x000D, 0x0033,   
              0x3FC7, 0x3FFD, 0x003F, 0x3FCC, 0x3FEB,   
              0x004A, 0x3FD6, 0x3FD7, 0x0051, 0x3FE4,   
              0x3FC2, 0x0055, 0x3FF7, 0x3FAD, 0x0053,   
              0x000F, 0x3F98, 0x004D, 0x002C, 0x3F84,   
              0x003F, 0x004F, 0x3F71, 0x0029, 0x007B,   
              0x3F60, 0x0007, 0x00B2, 0x3F52, 0x3FD2,   
              0x00FD, 0x3F46, 0x3F79, 0x0174, 0x3F3D,   
              0x3EC0, 0x027D, 0x3F38, 0x3C09, 0x0930,   
              0x148C,   
       	},
	};
	StructGroupDelay GroupDelayTable[]=
	{
		
		{  
           	0x02A, 0x7E0, 0x7D7, 0x0E2, 0x2CF,
           	0x11F, 0x716, 0x01A, 0x0BF, 0x6A9,
           	0x14A, 0x717, 0x075, 0x7E6, 0x7E7,
           	0x02C, 0x7D4, 0x024, 0x7E5, 0x012,
           	0x7F6, 0x004, 0x000, 0x7FD, 0x004,
          	0x7FC, 0x003, 0x7FE, 0x001, 0x7FF,
           	0x000, 0x000, 0x000, 0x000,
		},
	};
	UINT32 crc_table[]=
	{0x1548, 0xd587, 0x0742, 0xe4b5, 0xe00, 0xddf2, 0x1d4c, 0x2e38}; //{0x1548, 0xd587, 0x0742, 0xe4b5, 0xe0e00, 0xddf2, 0x1d4c, 0x11f8}
       UINT8 eq_en[]=
       {0,0,0,0,1,1,1,1};
	UINT8 output_en[]=
       {0,0,1,1,0,0,1,1};
	UINT8 grpdelay_en[]=
	{0,1,0,1,0,1,0,1};
	UINT8 len, eq=0, opt=0, dely=0, crc=0;

	len=0.5*(sizeof(Index_table)/sizeof(UINT8));
	
	IFD_QC_MSG("CRC 108M START......\n");
	
	for(i=0;i<len;i=i+1)
	{	
		for(j=0;j<len;j=j+1)
		{
			for(k=0;k<len;k=k+1)
			{	
				eq=0; 
				opt=0; 
				dely=0;
				IFD_Value = CIFD_CRC_108M_New(eq_en[crc], EqTable[eq].EQNotch_Table, output_en[crc], OuputLpfCoefTable[opt].StructOuputLpfCoef_Table, grpdelay_en[crc], GroupDelayTable[dely].GroupDelay_Table, crc_table[crc]);
				if(IFD_Value==_FAIL) return _FAIL;
				crc++;
				K=K+2;
			}
			K=0;
			J=J+2;
		}
		J=0;
		I=I+2;
	}
	I=0;
	IFD_QC_MSG("CRC 108M DONE\n");
	return _SUCCESS;
}

UINT8 CIFD_CRC_54M_New(UINT8 decimation_en, UINT8 shaping_image_sel, UINT8 shaping_bw_sel, UINT32 crc_in)//Return _SUCCESS or _FAIL
{
	UINT8 RetryCRC=5, Diff_Cnt=0;
	UINT32 crc_out;
	UINT8 Sta_Value=_FAIL;

	IFD_QC_MSG( "[CRC54M] IFD CRC 54M Start xxxxxxxxxxxxxxxxx\n");
	IFD_QC_MSG( "[CRC54M] decimation_en=%d, shaping_image_sel=%d, shaping_bw_sel=%d\n",decimation_en, shaping_image_sel,shaping_bw_sel);
	drv_ifd_power_on(IFD_DISABLE);
	udelay(500);
	drv_ifd_power_on(IFD_ENABLE);
	//rtd_outl(0xb8000518, 0x8);//PLLAUD power on
	//rtd_outl(0xb80004e4, 0x8);//PLLAUD power on
	udelay(500);
	//CRC enable
	rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x4c);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x03);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x80);
	//Settings
	drv_ifd_set_54to27_decimation_enable(decimation_en);
	drv_ifd_set_shaping_filter(shaping_bw_sel);
	drv_ifd_set_shaping_img(shaping_image_sel);
	drv_ifd_soft_reset(1);
	udelay(100);
	drv_ifd_soft_reset(0);
	udelay(100);
	do {
		crc_out=rtd_inl(IFD_CRC2_RESULT_VADDR);
		IFD_QC_MSG(  "[CRC54M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
		if(crc_in==crc_out) break;//Diff_Cnt++;
		udelay(500);
		RetryCRC--;
    	}while(RetryCRC);
	rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x00);
	
	if(RetryCRC>0)
	{          
		Sta_Value =_SUCCESS;
		IFD_QC_MSG( "[CRC54M] IFD CRC 54M Verify OK \n");
	}
	else
	{
		IFD_QC_MSG_WARNING( "[CRC54M] IFD CRC 54M Verify Wrong \n");
		IFD_QC_MSG_WARNING( "[CRC54M] decimation_en=%d, shaping_image_sel=%d, shaping_bw_sel=%d\n",decimation_en, shaping_image_sel,shaping_bw_sel);
		IFD_QC_MSG_WARNING( "[CRC54M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
          	Sta_Value =_FAIL;
	}
	return  Sta_Value;
}

UINT8 CIFD_CRC_54M_Test_Case(void)
{
	UINT8  IFD_Value = _SUCCESS;
	UINT8 i, j, k;
	UINT8 decimation_en_table[]={0x0, 0x1};
	UINT8 shaping_image_table[]={0x0, 0x1};
	UINT8 shaping_bw_table[]={0x0, 0x1, 0x2, 0x3};
	UINT32 crc_table[]=
	{
		0x9ab9c20b,0x60afe85f,0x2c40eeb9,0x68824344,
		0x9ab9c20b,0xf6a36d9c,0x2b0dd92b,0xc2da5e8f,  
		0x9ab9c20b,0x60afe85f,0x2c40eeb9,0x68824344,  
		0x9ab9c20b,0xf6a36d9c,0x2b0dd92b,0xc2da5e8f,
	};
	UINT8 len_i, len_j, len_k;
	len_i = sizeof(decimation_en_table)/sizeof(UINT8);
	len_j = sizeof(shaping_image_table)/sizeof(UINT8);
	len_k = sizeof(shaping_bw_table)/sizeof(UINT8);
	IFD_QC_MSG("CRC 54M START......\n");
	for(i=0;i<len_i;i++)
	{
		for(j=0;j<len_j;j++)
		{
			for(k=0;k<len_k;k++)
			{
				IFD_Value = CIFD_CRC_54M_New(decimation_en_table[i],shaping_image_table[j],shaping_bw_table[k], crc_table[i*len_k*len_j+j*len_k+k]);
				if(IFD_Value==_FAIL) return _FAIL;
			}
		}
	}
	IFD_QC_MSG("CRC 54M DONE\n");
	return _SUCCESS;
}

UINT8 CIFD_CRC_49M_New(UINT8 audio_bp_sel, UINT8 audio_upsample_lp_sel, UINT32 gain, UINT32 crc_in, bool bpf_input_div2_sel)//Return _SUCCESS or _FAIL
{

	UINT8 RetryCRC=5, Diff_Cnt=0; 
	UINT32	crc_out = 0;
	UINT8 Sta_Value=_FAIL;
	
	IFD_QC_MSG( "[CRC49M] IFD CRC 49M Start xxxxxxxxxxxxxxxxx\n");
	IFD_QC_MSG( "[CRC49M] audio_bp_sel=%d, audio_upsample_lp_sel=%d, gain=%d\n",audio_bp_sel, audio_upsample_lp_sel,gain);
	
	drv_ifd_power_on(IFD_DISABLE);
	udelay(500);
	drv_ifd_power_on(IFD_ENABLE);
	udelay(500);

	//CRC enable
	rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x4C);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x03);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x80);
	
	//setting
	drv_ifd_audio_gain_en(1); //gain manual disable
	udelay(100);
	drv_ifd_set_audio_bp_up_lp(audio_bp_sel, audio_upsample_lp_sel, bpf_input_div2_sel);
	drv_ifd_audio_gain_en(0); //gain manual enable
	drv_ifd_audio_gain_manual(gain); //gain
	udelay(100);
	
	// soft reset
	drv_ifd_soft_reset(1);
	udelay(100);
	drv_ifd_soft_reset(0);
	udelay(100);

	do {
		crc_out=rtd_inl(IFD_49M_CRC1_RESULT_VADDR);	
		IFD_QC_MSG(  "[CRC49M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
		if(crc_in==crc_out) break;//Diff_Cnt++;
		udelay(500);
		RetryCRC--;
    	}while(RetryCRC);

	drv_ifd_audio_gain_en(1); //gain manual disable
       rtd_outl(IFD_CRC_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_49M_CRC1_CTRL_REGISTER_VADDR, 0x00);
	rtd_outl(IFD_108M_CRC3_CTRL_RESULT_VADDR, 0x00);
	
	if(RetryCRC>0)
	{          
		Sta_Value =_SUCCESS;
		IFD_QC_MSG("[CRC49M] IFD CRC 49M Verify OK \n");
	}
	else
	{
		IFD_QC_MSG_WARNING( "[CRC49M] IFD CRC 49M Verify Wrong \n");
		IFD_QC_MSG_WARNING( "[CRC49M] audio_bp_sel=%d, audio_upsample_lp_sel=%d, gain=%d\n",audio_bp_sel, audio_upsample_lp_sel,gain);
		IFD_QC_MSG_WARNING( "[CRC49M] IFD crc_in =0x%x, crc_out=0x%x\n", crc_in, crc_out);
          	Sta_Value =_FAIL;
	}
	return  Sta_Value;

}

UINT8 CIFD_CRC_49M_Test_Case(void)
{

	UINT8  IFD_Value = _SUCCESS;
	UINT8 i, j, k;
	bool output_bpf_input_div2 = 1;
	UINT8 audio_bp_table[]={0x0, 0x16, 0x17};
	UINT8 audio_upsample_lp_table[]={0x0, 0x2};
	#if 0
	UINT32 manual_gain_table[]={0x000, 0x010, 0x020, 0x040, 0x080, 0x100, 0x200, 0x400, 0x800, 0xfff};
	UINT32 crc_table[]=
	{
		0x2159, 0xac6c, 0x8874, 0x86a2, 0xac6c, 0x8874, 0x86a2, 0xac6c, 0x8874,0x6acc,
		0x802f, 0x5d58, 0xb649, 0xe4c9, 0x5d58, 0xb649, 0xe4c9, 0x5d58,0xb649, 0xd118,
		0xb405, 0xb100, 0xda62, 0xfe80, 0xb100, 0xda62, 0xfe80,0xb100, 0xda62, 0xfd9d,
		0x9382, 0x887d, 0x938b, 0xec4a, 0x887d, 0x938b,0xec4a, 0x887d, 0x938b, 0xb5f7,
		0x3b91, 0xdd47, 0xed88, 0x819a, 0xdd47,0xed88, 0x819a, 0xdd47, 0xed88, 0xa4ea,
		0x8f86, 0x50cf, 0xcf03, 0x164,0x50cf, 0xcf03, 0x164,   0x50cf, 0xcf03, 0x1d3a,
	};
	#endif
	UINT32 manual_gain_table[]={0x000, 0x002, 0x004, 0x008, 0x010, 0x020, 0x040, 0x080, 0x100, 0x1ff};
	UINT32 crc_table[]=
	{
		0xfb0e, 0x2790, 0x6d1c, 0x965f, 0x17a3, 0xa783, 0x2fcb, 0x17a3, 0xa783,0xa783,
		0x429a, 0x72eb, 0x597b, 0x2e05, 0x387a, 0xf37e, 0x385e, 0x387a,0xf37e, 0xf37e,
		0x308d, 0x10f8, 0x60a9, 0x4a64, 0xdd8e, 0x1658, 0x0dd0,0xdd8e, 0x1658, 0x1658,
		0xd2fa, 0x6e46, 0xeea6, 0x0151, 0x4668, 0x7784,0x824e, 0x4668, 0x7784, 0x7784,
		0xf75e, 0xc9dd, 0xbfa8, 0x1c97, 0x0d31,0x5764, 0x89cb, 0x0d31, 0x5764, 0x5764,
		0xe7d7, 0xd5a2, 0x7623, 0x9ce7,0x8646, 0x596c, 0x3fd4, 0x8646, 0x596c, 0x596c,
	};
	
	UINT8 len_i, len_j, len_k;

	len_i = sizeof(audio_bp_table)/sizeof(UINT8);
	len_j = sizeof(audio_upsample_lp_table)/sizeof(UINT8);
	len_k = sizeof(manual_gain_table)/sizeof(UINT32);
	
	IFD_QC_MSG("CRC 49M START......\n");
	
	for(i=0;i<len_i;i++)
	{
		for(j=0;j<len_j;j++)
		{
			for(k=0;k<len_k;k++)
			{
				IFD_Value = CIFD_CRC_49M_New(audio_bp_table[i], audio_upsample_lp_table[j], manual_gain_table[k], crc_table[i*len_k*len_j+j*len_k+k], output_bpf_input_div2);
				if(IFD_Value==_FAIL) return _FAIL;
			}
		}
	}
	IFD_QC_MSG("CRC 49M DONE\n");
	return _SUCCESS;

}

UINT8 CIFD_QC_CRC_Verify(void)
{
       IFD_QC_MSG_INFO("*==IFD CIFD_QC_CRC_Verify==*\n");

	UINT8 Crc_Bit0=_FAIL,Crc_Bit1=_FAIL,Crc_Bit2=_FAIL;
	
	Crc_Bit0 = CIFD_CRC_54M_Test_Case();
	Crc_Bit1 = CIFD_CRC_49M_Test_Case();
	Crc_Bit2 = CIFD_CRC_108M_Test_Case();
	
	IFD_QC_MSG("CRC_54M=%x CRC_49M=%x  CRC_180M=%x \n",Crc_Bit0,Crc_Bit1, Crc_Bit2);

	if((Crc_Bit0==_SUCCESS)&&(Crc_Bit1==_SUCCESS)&&(Crc_Bit2==_SUCCESS))
	{
	    	return _SUCCESS ;
	}
	else
	{
		IFD_QC_MSG_WARNING("CRC verify fail ... CRC_54M=%x CRC_49M=%x  CRC_180M=%x\n",Crc_Bit0,Crc_Bit1, Crc_Bit2);
	    	return _FAIL;
	}

}
#endif

#ifdef Test_IFD_QC_TunerIfdFreq_Verify
UINT8 CIFD_QC_TunerIfdFreq_Verify()
{
       IFD_QC_MSG_INFO( "*==IFD CIFD_QC_TunerIfdFreq_Verify==*\n");

	UINT8  RetryCheck=RF_FREQ_NUM;
	UINT8 afc=0, i, j,k,result,flag=0;
	UINT32 curr_freq=0;
	INT32 offset = 0;
	UINT8 delay_cnt;
	UINT8 cr_count_thr=5;
	UINT8 cr_count=100;
	UINT8 AScan_Noise_stas[VIDEO_TEST_TIME]={0};
	UINT8 HVlock[VIDEO_TEST_TIME]={0};
	
	//clear status
	for (i=0;i<RF_FREQ_NUM;i++) rf_status[i]=0;

	do    
	{
		curr_freq =rf_freq[RF_FREQ_NUM-RetryCheck];
				
		drv_ifd_soft_reset(1);
		udelay(100);
		drv_ifd_soft_reset(0);
		udelay(100);
	
		drv_ifd_set_video_ntsc();
		drvif_vdc_ifd_path_setting(1);
		pTuner->SetRfFreqHz(pTuner, curr_freq);
		udelay(500);
		
		j=0;
		for(delay_cnt=0;delay_cnt<=cr_count;delay_cnt++)
		{
			udelay(1000);
			IFD_QC_MSG("delay_cnt=%d,drv_ifd_get_cr_lock_status() = %d\n", delay_cnt, drv_ifd_get_cr_lock_status());
			if(drv_ifd_get_cr_lock_status()==_TRUE)
			{ 
				j++;
				if (j>=cr_count_thr) break;
			}
		}
		
		if(j<cr_count_thr)
		{
			IFD_QC_MSG_WARNING("CR unlock with frequency=%d\n",curr_freq);
			rf_status[RF_FREQ_NUM-RetryCheck]=0;
		}
		else
		{
			offset = drv_ifd_get_cr_offset_100hz(afc);
			IFD_QC_MSG("offset= %d\n", offset);
			if(offset!=0)
			{
				curr_freq  = curr_freq + offset;	
				pTuner->SetRfFreqHz(pTuner, curr_freq);
				udelay(500);			
			}
			IFD_QC_MSG("CR lock with frequency=%d\n",curr_freq);
			rf_status[RF_FREQ_NUM-RetryCheck]=1;
		}	
	}while(--RetryCheck);
 	 
	for (i=0;i<RF_FREQ_NUM;i++) 
	{
		result=result+rf_status[i];
	}

	//drv_ifd_vd_reset();
	udelay(100000);
	// Check HV
	if (result==RF_FREQ_NUM)
	{
		for(i=0;i<VIDEO_TEST_TIME;i++)
		{
			//clear
			AScan_Noise_stas[i]=0;
			HVlock[i]=0;

			udelay(1000);
			AScan_Noise_stas[i] = (drv_ifd_vd_get_noise_status()&0xff);
	    		HVlock[i]=drv_ifd_vd_check_hvlock();
	    		IFD_QC_MSG("VD noise status=%x ; HV lock status=%x\n ; Count=%d\n",AScan_Noise_stas[i],HVlock[i],i);
			if((AScan_Noise_stas[i]<0xe0)&&(HVlock[i]==1))
			{	
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			IFD_QC_MSG("Tuner IF CR lock and HV lock, verify ok\n");
			return _SUCCESS;
		}
		else
		{
			IFD_QC_MSG_WARNING("Tuner IF CR lock,  HV unlock, verify fail\n");
			return _FAIL;
		}
       }
	else
	{
		IFD_QC_MSG_WARNING("Tuner IF CR unlock, verify fail\n");
		return _FAIL;
	}

}
#endif

#ifdef Test_IFD_QC_Gain_Verify

#ifdef CONFIG_TUNER_NXP_TDA18273
UINT32 CIFD_QC_Count_if_output(void)
{
	UINT8 RetryCheck=0,delay_cnt=0;
	UINT32 curr_freq;
	UINT32 if_gain;	
	UINT32 if_gain_sum=0;
	UINT32 if_gain_ave[2]={0};
	UINT32  per_if_gain_ave=0;
	UINT32 rf_full[3]={0};
	UINT32 rf_max=0; 
	INT32 PGA_gain[2]={0};
	INT8 i=1,situation=0;    
		if_gain_sum=0;

		for(i=1;i<=GAIN_TEST_TIME;i++)
		{
			udelay(50);
			
			if_gain= drv_ifd_agc_get_if_output();
	   
   			if_gain_sum = if_gain + if_gain_sum;


			IFD_QC_MSG("IFD the %dth if_gain_sum =%x  \n", i,if_gain_sum);
			IFD_QC_MSG("IFD the %dth if_gain =%x  \n",i, if_gain);
	

		}
		if_gain_ave[0]=if_gain_sum>>GAIN_AVG_SHIFT;//depend on max
		per_if_gain_ave=if_gain_ave[0];
		IFD_QC_MSG("[IFD]if gain ave[0]=%x\n",if_gain_ave[0]);

		return per_if_gain_ave;

}


UINT8 CIFD_QC_Gain_Verify(void)
{
       IFD_QC_MSG_INFO( "*==IFD CIFD_QC_Gain_Verify==*\n");

	UINT8 RetryCheck=0,delay_cnt=0;
	UINT32 curr_freq;
	UINT32 if_gain;	
	UINT32 if_gain_sum=0;
	UINT32 if_gain_ave=0;
	UINT32  per_if_gain_ave=0,max_output=0;
	UINT32 rf_full[3]={0};
	UINT32 rf_max=0; 
	INT32 PGA_gain[2]={0};
	INT8 i=1,situation=0;      

	do{
		/////////////////////////////////////////////////////
		//Calculate RF/IF gavg gain
		/////////////////////////////////////////////////////
		//clear sum
		per_if_gain_ave=CIFD_QC_Count_if_output();	
		IFD_QC_MSG("per_if_gain_ave =%x  \n",per_if_gain_ave);	
		
		//clear sum
		if_gain_sum=0;
		if((per_if_gain_ave<0xf00)&&(per_if_gain_ave>0x650))
		{
			drv_ifd_agc_targ_val(0x400);
			if_gain_ave=CIFD_QC_Count_if_output();	
			IFD_QC_MSG("the signal is normal , the if max target is rise ,then the  per_if_gain_ave =%x  \n",per_if_gain_ave);	
			IFD_QC_MSG("the signal is normal , the if max target is rise ,then the  if agc =%x  \n",if_gain_ave);
			if(if_gain_ave>per_if_gain_ave)
			{
				IFD_QC_MSG("Gain_Verify : the signal is normal , the if max target is rise ,the test is ok\n");	
				drv_ifd_agc_targ_val(GET_IFD_AGCLOOP1_MAXTARGET_NTSC());
				return _SUCCESS;
			}
			else
			{
				IFD_QC_MSG_WARNING("Gain_Verify : the signal is normal , the if max target is rise ,the test is fail\n");	
				drv_ifd_agc_targ_val(GET_IFD_AGCLOOP1_MAXTARGET_NTSC());
				return _FAIL;
			}
		}

		if((per_if_gain_ave==0xf00))
		{
			max_output=rtd_inl(IFD_AGC_MAX_STATUS_VADDR);
			drv_ifd_agc_targ_val(max_output/2);
			if_gain_ave=CIFD_QC_Count_if_output();	
			IFD_QC_MSG("the signal is normal , the if max target is weak ,then the  per_if_gain_ave =%x  \n",per_if_gain_ave);	
			IFD_QC_MSG("the signal is normal , the if max target is weak ,then the  if agc =%x  \n",if_gain_ave);
			if(per_if_gain_ave>if_gain_ave)
			{
				IFD_QC_MSG("Gain_Verify : the signal is normal , the if max target is weak ,the test is ok\n");	
				drv_ifd_agc_targ_val(GET_IFD_AGCLOOP1_MAXTARGET_NTSC());
				return _SUCCESS;
			}
			else
			{
				IFD_QC_MSG_WARNING("Gain_Verify : the signal is normal , the if max target is weak ,the test is fail\n");	
				drv_ifd_agc_targ_val(GET_IFD_AGCLOOP1_MAXTARGET_NTSC());
				return _FAIL;
			}
		}
		RetryCheck++;
	}while(RetryCheck<GAIN_FREQ_NUM);
}
#endif

#ifdef CONFIG_TUNER_XUGUANG_HFT3_86H_115CW
UINT8 CIFD_QC_Gain_Verify(void)
{
	UINT32 RetryCheck=0,delay_cnt=0;
	UINT32 if_gain, rf_gain, max_out2;	
	UINT32 if_gain_sum=0,rf_gain_sum=0, max_out2_sum=0;
	UINT32 if_gain_ave[2]={0}, rf_gain_ave[2]={0}, max_out2_ave[2]={0};
	UINT32 rf_full[3]={0};
	UINT32 rf_max=0; 
	INT32 PGA_gain[2]={0};
	INT8 i=1,situation=0;      

	if(drv_ifd_get_agc_2step_en()==_TRUE) 
	{
		do{
			/*
			for(delay_cnt=0;delay_cnt<10000;delay_cnt++)
			{
				udelay(10);
				IFD_QC_MSG("delay_cnt=%x\n",delay_cnt);
				if_gain= drv_ifd_agc_acc3_get_info();
		       	rf_gain = drv_ifd_agc_get_rf_output();
				max_out2 = drv_ifd_agc_get_loop2_max_out();
		   		IFD_QC_MSG("IFD the %dth if_gain =%x  \n", delay_cnt,if_gain);
				IFD_QC_MSG("IFD the %dth rf_gain =%x  \n",delay_cnt, rf_gain);
				IFD_QC_MSG("IFD the %dth max_out2 =%x  \n", delay_cnt,max_out2);

				if(drv_ifd_agc_get_loop1_lock()==_TRUE) break;
			}*/

			rf_max=drv_ifd_agc_rf_max_get_info();
		 	IFD_QC_MSG("rf max value=%x\n",rf_max);

			// check weak signal
			if((drv_ifd_agc_get_rf_output()==rf_max)||drv_ifd_rf_full_get_info())
				rf_full[0]=1;
			
			IFD_QC_MSG("**RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));
			IFD_QC_MSG("**RF_full flag=%d\n",rf_full[0]);

			/////////////////////////////////////////////////////
			//Calculate RF/IF gavg gain
			/////////////////////////////////////////////////////
			//clear sum
			if_gain_sum=0;
		   	rf_gain_sum=0;
			max_out2_sum=0;
			for(i=1;i<=GAIN_TEST_TIME;i++)
			{
				udelay(50);
				
				if_gain= drv_ifd_agc_acc3_get_info();
		       	rf_gain = drv_ifd_agc_get_rf_output();
				max_out2 = drv_ifd_agc_get_loop2_max_out();
		   
	   			if_gain_sum = if_gain + if_gain_sum;
				rf_gain_sum = rf_gain + rf_gain_sum;
				max_out2_sum = max_out2 + max_out2_sum;

				IFD_QC_MSG("IFD the %dth if_gain_sum =%x  \n", i,if_gain_sum);
				IFD_QC_MSG("IFD the %dth if_gain =%x  \n",i, if_gain);
				IFD_QC_MSG("IFD the %dth rf_gain_sum =%x  \n", i,rf_gain_sum);
				IFD_QC_MSG("IFD the %dth rf_gain =%x  \n",i, rf_gain);

			}
			if_gain_ave[0]=if_gain_sum>>GAIN_AVG_SHIFT;//depend on max
			rf_gain_ave[0]=rf_gain_sum>>GAIN_AVG_SHIFT;//depend on max
			max_out2_ave[0]=max_out2_sum>>GAIN_AVG_SHIFT;//depend on max
			IFD_QC_MSG("[IFD]rf gain ave[0]=%x\n",rf_gain_ave[0]);
			IFD_QC_MSG("[IFD]if gain ave[0]=%x\n",if_gain_ave[0]);
			IFD_QC_MSG("[IFD]max_out2_ave[0]=%x\n",max_out2_ave[0]);
			//clear sum
			if_gain_sum=0;
		   	rf_gain_sum=0;
			max_out2_sum=0;


			// check weak signal again
			udelay(1000);
			if((drv_ifd_agc_get_rf_output()==rf_max)||drv_ifd_rf_full_get_info())
				rf_full[1]=1;
			IFD_QC_MSG("**RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));
			IFD_QC_MSG("**RF_full flag=%d\n",rf_full[1]);

			if(rf_full[0]!=rf_full[1])             //This means weak to non-weak signal or non-weak to weak signal
			{
				// check weak signal again
				udelay(100);
				if((drv_ifd_agc_get_rf_output()==rf_max)||drv_ifd_rf_full_get_info())
					rf_full[2]=1;

				IFD_QC_MSG("**RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));
				IFD_QC_MSG("**RF_full flag=%d\n",rf_full[1]);

				//yuki need to check
	              	PGA_gain[0]=rtd_inl(IFD_READ_PGA_VADDR);
	              	IFD_QC_MSG("**if raise status=%x\n",PGA_gain[0]);
			
			  
				//---signal situation judgement----//
	          
				if(rf_full[2]!=rf_full[1])
				{
					IFD_QC_MSG("\nWarning!! The input signal has problem !!\n");
				}
				else
				{
					if(rf_full[2]==1)
					{
						situation=1;
						IFD_QC_MSG("This signal is non-weak --> weak signal \n\n");
						
					}
					else
					{
						situation=4;
						IFD_QC_MSG("This signal is weak --> non-weak signal \n\n");
					}
					
				}
			}
			else
			{
				PGA_gain[0]=rtd_inl(IFD_READ_PGA_VADDR);
		              IFD_QC_MSG("**if raise status=%x\n",PGA_gain[0]);

				if(rf_full[1]==1)
				{
					if((if_gain_ave[0]<0xa00)&&(max_out2_ave[0]>drv_ifd_agc_targ_val_get_info()-0x10)){
						situation=3;
						IFD_QC_MSG("This signal is all weak signal \n\n");
						drv_ifd_agc_targ_val(0x700);
						rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x0);
					}
					else
					{
						situation=5;
						IFD_QC_MSG("This signal is very very weak signal \n\n");
						/*if(max_out2_ave[0]>0x100)
						{
							drv_ifd_agc_targ_val(max_out2_ave[0]-0x100);
						}
						else
						{
							drv_ifd_agc_targ_val(0x10);
						}*/
						drv_ifd_agc_targ_val(max_out2_ave[0]>>1);
						
						//drv_ifd_agc_targ_val(drv_ifd_agc_targ_val_get_info()-0x100);
						rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x0);
					}
				}
				else
				{
					situation=2;
					IFD_QC_MSG("This signal is all non-weak signal \n\n");
					//drv_ifd_agc_2step_pga_minimum(drv_ifd_agc_2step_pga_minimum_get_info()+0x20);
					drv_ifd_agc_targ_val(GAIN_TARGET);
					//drv_ifd_agc_loop2_target(GET_IFD_AGCLOOP2_MAXTARGET_NTSC()>>1);
				}
			}

			for(delay_cnt=0;delay_cnt<10000;delay_cnt++)
			{
				udelay(10);
				if(drv_ifd_agc_get_loop1_lock()==_TRUE) break;
			}
			udelay(300000);
			max_out2 = drv_ifd_agc_get_loop2_max_out();
			IFD_QC_MSG("max_out2=%x\n",max_out2);
			/////////////////////////////////////////////////////
			//Calculate RF/IF gavg gain
			/////////////////////////////////////////////////////
			//clear sum
			if_gain_sum=0;
		   	rf_gain_sum=0;
			max_out2_sum=0;
			for(i=1;i<=GAIN_TEST_TIME;i++)
			{
				udelay(50);//chihwei@070917
				//if_gain=drv_ifd_agc_get_if_output(); //yuki need to check:IFD_AGC_ACC3_STATUS_VADDR or IFD_AGC_INNER_STATUS_VADDR
	       		//rf_gain=drv_ifd_agc_get_rf_output();
				if_gain= drv_ifd_agc_acc3_get_info();
		       	rf_gain = drv_ifd_agc_get_rf_output();
		   		max_out2 = drv_ifd_agc_get_loop2_max_out();
		   
	   			if_gain_sum = if_gain + if_gain_sum;
				rf_gain_sum = rf_gain + rf_gain_sum;
				max_out2_sum = max_out2 + max_out2_sum;

				IFD_QC_MSG("IFD the %dth if_gain_sum =%x  \n", i,if_gain_sum);
				IFD_QC_MSG("IFD the %dth if_gain =%x  \n",i, if_gain);
			   	IFD_QC_MSG("IFD the %dth rf_gain_sum =%x  \n", i,rf_gain_sum);
				IFD_QC_MSG("IFD the %dth rf_gain =%x  \n",i, rf_gain);
			}
			if_gain_ave[1]=if_gain_sum>>GAIN_AVG_SHIFT;//depend on max
			rf_gain_ave[1]=rf_gain_sum>>GAIN_AVG_SHIFT;//depend on max
			max_out2_ave[1]=max_out2_sum>>GAIN_AVG_SHIFT;//depend on max
			IFD_QC_MSG("[IFD]rf gain ave[1]=%x\n",rf_gain_ave[1]);
			IFD_QC_MSG("[IFD]if gain ave[1]=%x\n",if_gain_ave[1]);
			IFD_QC_MSG("[IFD]max_out2_ave[1]=%x\n",max_out2_ave[1]);
			//clear sum
			if_gain_sum=0;
		   	rf_gain_sum=0;
			max_out2_sum=0;

			//rf/if gain is incorrect, wait for it 
			if(situation==3)
			{
				if(if_gain_ave[0]>=if_gain_ave[1])
				{
					for(i=0;i<40;i++)
					{
							udelay(100000);
							IFD_QC_MSG("\n++RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));

							//yuki need to check
					  		PGA_gain[1]=rtd_inl(IFD_READ_PGA_VADDR);
							if(PGA_gain[0]!=PGA_gain[1])
							{
								IFD_QC_MSG("\n++IFD++ if raise status=%x\n",PGA_gain[1]);
								break;
							}
					}	
				}
			}
			else if(situation==5)
			{
				if((if_gain_ave[0]<=if_gain_ave[1])&&(if_gain_ave[1]<0xa00))
				{
					for(i=0;i<40;i++)
					{
							udelay(100000);
							IFD_QC_MSG("\n++RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));

							//yuki need to check
					  		PGA_gain[1]=rtd_inl(IFD_READ_PGA_VADDR);
							if(PGA_gain[0]!=PGA_gain[1])
							{
								IFD_QC_MSG("\n++IFD++ if raise status=%x\n",PGA_gain[1]);
								break;
							}
					}	
				}
			}
			#if 1
			else if(situation==2)
			{
				if(if_gain_ave[0]<if_gain_ave[1])
				{
					for(i=0;i<40;i++)
					{
							udelay(100000);
							IFD_QC_MSG("\n++RF status register=%x\n",rtd_inl(IFD_AGC_2STEP_STATUS_VADDR));

							//yuki need to check
					  		PGA_gain[1]=rtd_inl(IFD_READ_PGA_VADDR);
							if(PGA_gain[0]!=PGA_gain[1])
							{
								IFD_QC_MSG("\n++IFD++ if raise status=%x\n",PGA_gain[1]);
								break;
							}
					}	
				}
			}
			#endif
			else
				udelay(100000);
			   	
			//yuki need to check
			PGA_gain[1]=rtd_inl(IFD_READ_PGA_VADDR);
		       IFD_QC_MSG("**if raise status=%x\n",PGA_gain[1]);

			drv_ifd_para_change_with_tunerband();
			//yuki need to refine for test above 2 freq.
			if(situation==1)
			{
				IFD_QC_MSG("\n situation=%d \n",situation);
				IFD_QC_MSG( "\nThis is a non-weak--> weak signal \n");
				IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
				IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
				IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
				rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x1000);
			  	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				return _SUCCESS;
			}
			else if(situation==2 && (rf_gain_ave[0]>=rf_gain_ave[1])&&(if_gain_ave[0]>=if_gain_ave[1]))
			{

				IFD_QC_MSG("\n situation=%d \n",situation);
				IFD_QC_MSG( "\nThis is a non-weak--> non-weak signal \n");
				IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
				IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
				IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
					
				IFD_QC_MSG( "IFD if_gain_ave[0] =%x  \n", if_gain_ave[0]);
				IFD_QC_MSG( "IFD if_gain_ave[1] =%x  \n", if_gain_ave[1]);
				drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x1000);
				return _SUCCESS;
			}
			else if(situation==3 && ((if_gain_ave[0]<if_gain_ave[1])||(PGA_gain[0]!=PGA_gain[1])))
			{
				IFD_QC_MSG("\n situation=%d \n",situation);
		    		IFD_QC_MSG( "\nThis is a weak--> weak signal \n");
		    		IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
		    		IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
		    		IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
			
		    		IFD_QC_MSG( "IFD if_gain_ave[0] =%x  \n", if_gain_ave[0]);
		    		IFD_QC_MSG( "IFD if_gain_ave[1] =%x  \n", if_gain_ave[1]);
				drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x1000);
				return _SUCCESS;
			}
			else if(situation==5 && ((max_out2_ave[0]>max_out2_ave[1])||(PGA_gain[0]!=PGA_gain[1])))
			{
				IFD_QC_MSG("\n situation=%d \n",situation);
		    		IFD_QC_MSG( "\nThis is a very weak--> very weak signal \n");
		    		IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
		    		IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
		    		IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
			
		    		IFD_QC_MSG( "IFD if_gain_ave[0] =%x  \n", if_gain_ave[0]);
		    		IFD_QC_MSG( "IFD if_gain_ave[1] =%x  \n", if_gain_ave[1]);
				drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				rtd_maskl(IFD_AGC_PEAK_DETECT_VADDR,0xffffefff,0x1000);
				return _SUCCESS;
			}
			else if(situation==4)
			{
				IFD_QC_MSG("\n situation=%d \n",situation);
				IFD_QC_MSG( "\nThis is a non-weak--> weak signal \n");
				IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
				IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
				IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
			  	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				return _SUCCESS;
			}
			else
			{
				IFD_QC_MSG("\n situation=%d \n",situation);
				IFD_QC_MSG( "\n[IFD] Gain check error \n");
				IFD_QC_MSG( "\nIFD rf_gain_check xxxxxxxxxxxxxxxxx  \n");
				IFD_QC_MSG( "IFD rf_gain_ave[0] =%x  \n", rf_gain_ave[0]);
				IFD_QC_MSG( "IFD rf_gain_ave[1] =%x  \n", rf_gain_ave[1]);
				
				IFD_QC_MSG( "IFD if_gain_ave[0] =%x  \n", if_gain_ave[0]);
				IFD_QC_MSG( "IFD if_gain_ave[1] =%x  \n", if_gain_ave[1]);
				drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
				return _FAIL;
			}
			RetryCheck++;
		}while(RetryCheck<GAIN_FREQ_NUM);
	}
	else //else of if(drv_ifd_get_agc_2step_en()==_TRUE)
	{
		drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());
		return _FAIL;
	}//end of if(drv_ifd_get_agc_2step_en()==_TRUE)
}
#endif 
#endif

#ifdef Test_IFD_QC_AudioPerFoms_Verify
UINT8 CIFD_QC_AudioPerFoms_Verify(void)
{
	UINT32 Check_SoundCarrier_Energy[2]={0};
	UINT8 delay_cnt=0,ierr=0; 

	IFD_QC_MSG_INFO( "*==IFD CIFD_QC_AudioPerFoms_Verify==*\n");
	drv_ifd_audio_initial();
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC());  // modified gain traget after QC gain verify
	
redo:
	udelay(10000);
	if(drv_ifd_get_cr_lock_status()==_TRUE)
	{
		IFD_QC_MSG( "*** IFD CIFD_QC_AudioPerFoms_Verify - CR locked\n");
		udelay(100000);
		Check_SoundCarrier_Energy[0]=rtd_inl(AUDIO_MSD_MAG_4_5_VADDR);
		IFD_QC_MSG( "*** IFD SoundCarrier Energy status=%x\n",Check_SoundCarrier_Energy[0]);
		udelay(100000);	
		Check_SoundCarrier_Energy[1]=rtd_inl(AUDIO_MSD_MAG_4_5_VADDR);
		IFD_QC_MSG( "*** IFD SoundCarrier Energy status=%x\n",Check_SoundCarrier_Energy[1]);

		if((Check_SoundCarrier_Energy[0]>0x2000)||(Check_SoundCarrier_Energy[1]>0x2000))
		{
			return _SUCCESS;
		}
		else
		{
			if (ierr<10)
			{	
		 		ierr++;
				goto redo;
			}
		}
		IFD_QC_MSG_WARNING( "AudioPerFoms Verify fail -- Audio Tone small\n");
		return _FAIL;
	}
	else
	{
		IFD_QC_MSG_WARNING( "AudioPerFoms Verify fail -- CR unlock\n");
		return _FAIL;
	}
}
#endif

#ifdef Test_IFD_QC_AVOUT_Verify
UINT8 CIFD_QC_AVOUT_Verify()
{
	IFD_QC_MSG( "*==IFD CIFD_QC_AVOUT_Verify==*\n");
	//VD	   
       UINT8 no_signal;
	UINT8 mode_check;
	UINT8 av_mode;
	UINT32 i;

	#if 1//BOARD QFP CONFIG
	if(module_ifd_vdc_Test_Y_Path(VIDEO_INPUT6, VIDEO_GNDY1) != _SUCCESS)
	{
		return _FAIL;
	}
	udelay(2000);
	
	if(module_ifd_vdc_Test_Y_Path(VIDEO_INPUT7, VIDEO_GNDY1) != _SUCCESS)
	{
		return _FAIL;	
	}
	udelay(2000);

	if(module_ifd_vdc_Test_Y_Path(VIDEO_INPUT8, VIDEO_GNDY1) != _SUCCESS)
	{
		return _FAIL;
	}
	udelay(2000);
	#endif
	return  _SUCCESS;	  
}
#endif

/*********************************************************************/
UINT8 CIFD_QC_VERIFY(void)
{
	
	IFD_QC_MSG("***IFD QC Verify test start *** \n\n");
       
	drv_ifd_pinshare();
	drvif_ifd_init();
	pTuner->Initialize(pTuner);
	
	#ifdef Test_IFD_QC_CRC_Verify
	//=======CRC Performanc  Check===========//
	if(CIFD_QC_CRC_Verify()!=_FAIL) 
	{
		IFD_QC_MSG_INFO("*==IFD CRC QC Verify Success==* \n\n");
	}
	else
	{
		IFD_QC_MSG_INFO("*==IFD CRC QC Verify fails==* \n\n");
		goto IFD_tst_Open_fail;
	}
	#endif

	#ifdef Test_IFD_QC_TunerIfdFreq_Verify
	//=======TunerIf Performanc  Check===========//
	if(CIFD_QC_TunerIfdFreq_Verify()!=_FAIL)
	{
		IFD_QC_MSG_INFO("*==IFD TunerIfdFreq QC Verify Success ==*\n\n");
	}
	else
	{
		IFD_QC_MSG_INFO("*==IFD TunerIfdFreq QC Verify fail ==*\n\n");
		goto IFD_tst_Open_fail;
	}
	#endif

	#ifdef Test_IFD_QC_Gain_Verify
	//=======QC gain Performanc  Check===========//
	if(CIFD_QC_Gain_Verify()!=_FAIL)
	{
		IFD_QC_MSG_INFO("*==IFD Gain QC Verify Success ==*\n\n");
	}
	else
	{
		IFD_QC_MSG_INFO("*==IFD Gain QC Verify fail ==*\n\n");
		goto IFD_tst_Open_fail;
	}
 	#endif

	#ifdef Test_IFD_QC_AudioPerFoms_Verify
	//=======Audio Performanc  Check===========//
	if(CIFD_QC_AudioPerFoms_Verify()!=_FAIL)
	{
		IFD_QC_MSG_INFO("*==IFD Audio Performanc QC Verify Success==* \n\n");
	}
	else
	{
		IFD_QC_MSG_INFO("*==IFD Audio Performanc QC Verify fail==* \n\n");
		goto IFD_tst_Open_fail;
	}
	#endif

	#ifdef Test_IFD_QC_AVOUT_Verify
	//========= AVOUT performance Check==========//
	if(CIFD_QC_AVOUT_Verify()!=_FAIL)
	{
		IFD_QC_MSG("*==IFD AVOUT QC Verify Success==* \n\n");
	}
	else
	{
		IFD_QC_MSG("*==IFD AVOUT QC Verify fail==* \n\n");
		goto IFD_tst_Open_fail;
	}
	#endif

	#ifdef CONFIG_OLT
	//===========IFD OLT Check=============//
	IFD_QC_MSG("***IFD OLT*** \n");
	drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(60000));
	//It need to add CR offset thd =  150k (yuki)
	drv_ifd_reset_nco();	
	printk("0xb8032014=%x\n", rtd_inl(0xb8032014));//by Lee
	if(drv_ifd_get_cr_lock_status()==0)
	{
		IFD_QC_MSG("***CR un lock*** \n");
		goto IFD_tst_Open_fail;
	}
	#endif
	drv_ifd_reset();
	//drv_ifd_vd_reset();
	return _SUCCESS;
	
IFD_tst_Open_fail:
    
       drv_ifd_reset();
	//drv_ifd_vd_reset();
       return _FAIL;
	   
}

int QC_Verifier_IFD(void)
{
	#if 0//loop
	int ii=1000,r=_FAIL;
	while(ii)
	{
		printk("\n\n\n\n*==QC verify=%d times==*\n",(1000-ii+1));
		ii--;
		r=CIFD_QC_VERIFY();
		if(r==_FAIL) break;
	}
	#else// 1 time	
	if(CIFD_QC_VERIFY()==_SUCCESS)
	{
		printk("IFDVerifier is ok\n");
		return _SUCCESS;	
	}
	else
	{
	 	printk("IFD Verifier is fail\n");
		return _FAIL;
	}
	#endif
} 
#else
#include <qc_verify_common.h>
int QC_Verifier_IFD(void)
{
	return FAILED;
} 
#endif
