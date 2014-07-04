#include <audio_qc_rbus.h>
#include <rtd_types_qc.h>
#include <audio_qc.h>
#include <qc_verify_common.h>

#define printk printf

//global paramenter
UINT32 g_audio_initialize_done ;
UINT32 pRdBuf[DMACHANNELS][DMABUFSAMPLES] ALIGN64;// cuz rd_start_addr LSB 5 bits are reserved , it needs ALIGN64
UINT32 pWrBuf[DMACHANNELS][DMABUFSAMPLES] ALIGN64;// cuz wr_start_addr LSB 5 bits are reserved , it needs ALIGN64

//function
static void WriteRegister(UINT32 address, UINT32 data)
{
	//(*(volatile UINT32 *)(address) = data) ;
	rtd_outl(address, data);
}

static UINT32 ReadRegister(UINT32 address)
{
//	return (*(volatile UINT32 *) (address)) ;
	return (rtd_inl(address));
}

static void WriteMaskRegister(UINT32 address, UINT32 mask, UINT32 data)
{
	UINT32 target_value;
	target_value=rtd_inl(address);
	target_value=target_value&(~mask);
	target_value=(target_value|data);
	WriteRegister(address, target_value);
}
void Delay_ms(int value)
{
	int i,j,k;
	for(i=0; i<value; i++)
		for(j=0;j<0xfffff;j++)
			k++;
}

void aud_Delay(int delayMS)
{

	//volatile register int loop=delayMS*100;
	UINT32 current_count, target_count;
	//printk("[Audio] Enter aud_Delay\n");	//debug
	//WriteMaskRegister(AUDIO_GLOBAL_CTRL_1_VADDR, _BIT15|_BIT14|_BIT7|_BIT6, _BIT14|_BIT6);//PLL AUDIO = 49.152MHz
	WriteMaskRegister(AUDIO_AIO_TIMER_EN_VADDR, _BIT1, _BIT1);	
	current_count=ReadRegister(AUDIO_AIN_COUNTER_VADDR);
//	printk("[pedro] current count %x\n", current_count);
	do{
		target_count=ReadRegister(AUDIO_AIN_COUNTER_VADDR);
		//printk("[Audio] target_count=0x%x ; current_count=0x%x ; delayMS=0x%x\n",target_count,current_count,delayMS); //debug
		}while(target_count < (current_count+(0xc000)*delayMS));
	//printk("[pedro] target count %x\n", target_count);	
	WriteMaskRegister(AUDIO_AIO_TIMER_EN_VADDR, _BIT1, 0);
	//printk("[Audio] Exit aud_Delay\n"); //debug
}

#ifdef config_AudioInit
void aud_DrPLL()
{
	printk("Init pll\n");
	// PLL AUDIO
	WriteMaskRegister(AUDIO_SYS_PLL_AUD1_VADDR,_BIT0, 0);//PLLAUD, no tst
	WriteMaskRegister(AUDIO_SYS_PLL_AUD3_VADDR, _BIT0, 0);//PLLAUD power on
	WriteMaskRegister(AUDIO_SYS_PLL_AUD3_VADDR, _BIT3, 0);//PLLAUD reset
	WriteMaskRegister(AUDIO_SYS_PLL_AUD3_VADDR, _BIT2|_BIT1, 0);//PLLAUD output
	WriteMaskRegister(AUDIO_SYS_PLL_AUD3_VADDR, _BIT3, _BIT3);//PLLAUD no reset


/*	// PLL SPDIF
	WriteMaskRegister(SYS_PLL_PSAUD1_VADDR, _BIT3|_BIT2, _BIT3|_BIT2);//PSAUD enable
	WriteMaskRegister(SYS_PLL_PSAUD1_VADDR, _BIT1|_BIT0, 0);//PSAUD, no test
	
	// PLL 512
	WriteRegister(SYS_PLL_512FS1_VADDR,0x01ea20a4);	//PLL512fs, no WD, no test, 48k
	WriteMaskRegister(SYS_PLL_512FS2_VADDR, _BIT0, 1);//PLL512 power on
	WriteMaskRegister(SYS_PLL_512FS2_VADDR, _BIT2|_BIT1, 0);//reset, output enable
	WriteMaskRegister(SYS_PLL_512FS2_VADDR, _BIT1, _BIT1);//PLL512 no reset
*/
	while(ReadRegister(AUDIO_SYS_PLL_AUD3_VADDR!=0x8))
		{
		printk("Retry Init pll \n");
		WriteRegister(AUDIO_SYS_PLL_AUD3_VADDR, 0x8);
		}
	
}

void aud_AIOpinmux()
{
	printk("Init AIO pinmux setting\n");  
	WriteMaskRegister(0xb80008F0, _BIT31|_BIT30|_BIT29|_BIT28|_BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22, _BIT30|_BIT29|_BIT25|_BIT24); 	// AI2 pin mux
	WriteMaskRegister(0xb80008F0, _BIT21|_BIT20|_BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12, _BIT20|_BIT19|_BIT15|_BIT14); 	// AI3 pin mux
	WriteMaskRegister(0xb80008F0, _BIT11|_BIT10|_BIT9|_BIT8|_BIT7, _BIT10|_BIT9); 	// AI4_L pin mux
	WriteMaskRegister(0xb80008F4, _BIT31|_BIT30|_BIT29|_BIT28|_BIT27, _BIT30|_BIT29); 	// AI4_R pin mux
	WriteMaskRegister(0xb80008F4, _BIT26|_BIT25|_BIT24|_BIT23|_BIT22|_BIT21|_BIT20|_BIT19|_BIT18|_BIT17, _BIT25|_BIT24|_BIT20|_BIT19); 	// AIO1 pin mux
	WriteMaskRegister(0xb80008F4, _BIT16|_BIT15|_BIT14|_BIT13|_BIT12|_BIT11|_BIT10|_BIT9|_BIT8|_BIT7, _BIT15|_BIT14|_BIT10|_BIT9); 	// HP pin mux

}


void aud_DrClock()
{
	printk("Init clk\n");  
	WriteMaskRegister(AUDIO_GLOBAL_CTRL_1_VADDR, _BIT31|_BIT30|_BIT29|_BIT28, _BIT31|_BIT30|_BIT29|_BIT28);//SDRAM on
	WriteMaskRegister(AUDIO_GLOBAL_CTRL_1_VADDR, _BIT20, _BIT20);//SIF ADC CLOCK on
	WriteMaskRegister(AUDIO_GLOBAL_CTRL_1_VADDR, _BIT13|_BIT12|_BIT5|_BIT4, _BIT13|_BIT5);//PLL AUDIO

}

void aud_DrBaseband()
{
	printk("Init bb\n");
	WriteMaskRegister(AUDIO_ANALOG_DEPOP2_VADDR, _BIT8|_BIT7|_BIT3, _BIT8|_BIT7|_BIT3);//enable output normal mode FOR HP/AIO1/AIO2
	WriteMaskRegister(VDAC_VADDR, _BIT20,_BIT20);// turn on "REG_VDAC_POWMBIAS" for BB audio
	WriteRegister(AUDIO_ANALOG_POWER_VADDR, 0x00007ff8);// turn on all Audio Power exclude bit11 of bit0~bit14
// Clayton 2014/1/9
// No Line driver in Sirius
	//WriteMaskRegister(AUDIO_ANALOG_CAPLESS_LINEOUT_DEPOP_VADDR, _BIT8|_BIT4|_BIT3,0);//CLO depop & pull-low disable
	//WriteMaskRegister(AUDIO_ANALOG_CAPLESS_LINEOUT_CONTROL_VADDR, _BIT0,_BIT0);//enable charge-pump normal mode
	#ifdef config_Audio_biascurrent_30u
	WriteMaskRegister(AUDIO_ANALOG_CI01_VADDR ,_BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22, _BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22);//AIO1 & AIO2 & HP BIAS current 30u
	#endif
}

void aud_DrGpio()
{
	printk("Init gpio\n");
	/*// spdif out
	WriteMaskRegister(0xb8000868, 0xF0, 0xA0); // SPDIF_OUT
	// spdif in
	WriteMaskRegister(0xb8000868, 0xF000, 0xB000); // SPDIF_IN_0
	WriteMaskRegister(0xb80008c8, _BIT24, 0); // SPDIF_IN_0
	// i2s out
	WriteMaskRegister(0xb8000840, 0xF0F0F0, 0xb0b0b0); // I2S_O_SCLK, I2S_O_WS, I2S_O_MCLK
	WriteMaskRegister(0xb8000840, 0xF0000000, 0xb0000000); // I2S_O_D0
	// i2s in
	//WriteMaskRegister(0xb8060220, 0xF0, 0x90); // I2S_I_MCLK_1
	//WriteMaskRegister(0xb8060224, 0xF0F00000, 0x90900000); // I2S_I_WS_1, I2S_I_SCLK_1
	//WriteMaskRegister(0xb8060208, 0xF00, 0x900); // I2S_I_Data0_1
	*/
}

void aud_DrSIF()
{
/*
	printk("sif\n");
	WriteRegister(0xb8000500, 0x11100001);
	WriteRegister(0xb8000504, 0x00000f00);
	WriteRegister(0xb8000508, 0x00000003);
	WriteRegister(0xb8033020, 0x11111111);//ADC power

	WriteRegister(0xb8033030, 0x18800200);
	WriteRegister(0xb803303C, 0x00080000);
	WriteRegister(0xb8033040, 0x00011111);
	WriteRegister(0xb8033044, 0x01010101);
	WriteRegister(0xb803304C, 0x00000003);
	WriteRegister(0xb8033050, 0x000aaa08);
	WriteRegister(0xb8033054, 0x00000202);

	WriteRegister(0xb8032368, 0x00000000); // input bypass
	WriteMaskRegister(0xb8033030, _BIT17|_BIT16, _BIT17);//CLK_24576
	WriteMaskRegister(0xb8033044, _BIT1|_BIT0, 0);//SIF_GPA
*/
}

void aud_DrInitialize()
{
	//aud_DrPLL();
	rtd_outl(AUDIO_SYS_PLL_AUD3_VADDR, _BIT3);
	WriteMaskRegister(0xb8000000, _BIT15, _BIT15);	//Reset bit of AIO
	WriteMaskRegister(0xb8000008, _BIT8|_BIT7|_BIT6, _BIT8|_BIT7|_BIT6); //Reset bit of Audio
	WriteMaskRegister(0xb800000c, _BIT10, _BIT10); //Clock enable bit for AIO
	WriteMaskRegister(0xb8000014, _BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12, _BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12); // Clock enable bit for Audio ¡V ADC and DAC1 analog_part 

	aud_DrClock();
	aud_AIOpinmux();
	aud_DrBaseband();
	aud_DrGpio();
	aud_DrSIF();
	WriteRegister(AUDIO_AIN_COMPARE_VADDR, 0xFFFFFFFF);// set Ain timer
	WriteRegister(AUDIO_AOUT_COMPARE_VADDR, 0xFFFFFFFF);;// set AOUT timer
	aud_Delay(20);	//[fixed me]
	printk("Init Audio Done\n");
	g_audio_initialize_done = 1;
}
#endif

#ifdef config_AudioPath_Digital
void dx_I2sSetInputPri(QC_I2SIO_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_I2S_IN_PRIMARY_VADDR, _BIT31|_BIT30, src_select<<30);
}

UINT32 dx_I2sGetWordLength(UINT32 is_sec_module)
{
	return (ReadRegister(AUDIO_I2S_IN_PRIMARY_VADDR)&0x7F);
}

UINT32 dx_I2sGetSampleRate()
{
//	printk("[pedro] get i2s sample rate\n");
      aud_Delay(10);
	return ((ReadRegister(AUDIO_I2S_IN_PRIMARY_VADDR)>>8)&0xF);
}

void dx_I2sSetOutput(QC_I2SIO_SrcSel  src_select, UINT32 pcm_src)
{
	WriteMaskRegister(AUDIO_I2S_OUT_VADDR, _BIT30|_BIT29|_BIT28, src_select<<28);
	WriteMaskRegister(AUDIO_I2S_OUT_SEL_VADDR, _BIT30|_BIT29|_BIT28, pcm_src<<28);	// Clayton 2014/1/8, fixed bit mapping error
	if(pcm_src>=3)
		WriteMaskRegister(AUDIO_GLOBAL_CTRL_0_VADDR, _BIT24, _BIT24);
	else
		WriteMaskRegister(AUDIO_GLOBAL_CTRL_0_VADDR, _BIT24, 0);
}

void dx_SpdifSetInput(QC_SPDIFIO_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_SPDIF_IN_VADDR, _BIT31|_BIT30, src_select<<30);
}

UINT32 dx_SpdifGetSampleRate()
{
//	printk("[pedro] get spdif sample rate\n");
	return (ReadRegister(AUDIO_SPDIF_IN_VADDR)&0xF);
}

void dx_SpdifSetOutput(QC_SPDIFIO_SrcSel src_select, UINT32 pcm_src)
{
	WriteMaskRegister(AUDIO_SPDIF_OUT_VADDR, _BIT31|_BIT30, src_select<<30);
	WriteMaskRegister(AUDIO_SPDIF_OUT_VADDR, _BIT26|_BIT25|_BIT24|_BIT23, pcm_src<<23);

	if((pcm_src=3) || (pcm_src=6) || (pcm_src=6))		//Clayton 2014/1/9
		WriteMaskRegister(AUDIO_GLOBAL_CTRL_0_VADDR, _BIT25, _BIT25);	// TS Path
	else
		WriteMaskRegister(AUDIO_GLOBAL_CTRL_0_VADDR, _BIT25, 0);	//PB path
}
#endif
#ifdef config_AudioPath_Analog
void dx_AdcSetInput(QC_AIO_SrcSel src_select)
{
	switch(src_select)
		{
		case AIN1: 
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT6|_BIT0, 0x0); // AIN1 - ADC
			break;
		case AIN2:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT7|_BIT1, 0x0);// AIN2 - ADC
			break;
		case AIN3:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT8|_BIT2, 0x0); // AIN3 - ADC
			break;
		case AIN4:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT9|_BIT3, 0x0);// AIN4 - ADC
			break;
		case AIO1:
			WriteMaskRegister(AUDIO_ANALOG_POWER_VADDR,_BIT14,0);// cahnge AIO1 to AIN mode
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT10|_BIT4, 0x0);// AIO1 - ADC
			break;
		case AIO2:
			WriteMaskRegister(AUDIO_ANALOG_POWER_VADDR,_BIT13,0);// cahnge AIO2 to AIN mode
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT11|_BIT5, 0x0);// AIO2 - ADC
			break;
			
		default:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, 0xfFF, 0xFFF);// Mute All Ain
			break;
		}
	
}
void dx_FifoPlay_CH01(QC_FIFO_SrcSel play_src_select) // main ch0/1
{
	WriteMaskRegister(AUDIO_DOWN_SAMPLE_FIFO_SOURCE_SEL_VADDR, 0xF, play_src_select);
}

void dx_FifoTs_CH01(QC_FIFO_SrcSel ts_src_select) // main ch0/1
{
	WriteMaskRegister(AUDIO_DOWN_SAMPLE_CONTROL_FOR_TS_VADDR, 0xF000, ts_src_select<<12);
}
void dx_Dac0SetOutput(QC_DAC_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_DAC0_1_SRC_SEL_VADDR, _BIT2|_BIT1|_BIT0, src_select);
}

void dx_Dac1SetOutput(QC_DAC_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_DAC0_1_SRC_SEL_VADDR, _BIT21|_BIT20|_BIT19, src_select<<19);
}
void dx_HPSetOutput(QC_AIO_SrcSel src_select)
{
	switch(src_select)
		{
		case DAC1:
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR,0x3ff,0x3ff);	// Mute all source of HP
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR, _BIT7|_BIT2, 0x0); // choose DAC1
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR,0x1fc0000,0x1fc0000);
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR, _BIT19, 0);
			break;
		case DAC0:
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR,0x3ff,0x3ff);	// Mute all source of HP
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR, _BIT8|_BIT3, 0x0);	// choose DAC0
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR,0x1fc0000,0x1fc0000);
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR, _BIT19, 0);
			break;
		case ADCFE:
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR,0x3ff,0x3ff);	// Mute all source of HP
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR, _BIT6|_BIT1, 0x0);	// choose ADCFE
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR,0x1fc0000,0x1fc0000);
			//WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR, _BIT19, 0);
			break;
		default: //Mute all
			WriteMaskRegister(AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR,0x3ff,0x3ff);	// Mute all source of HP
		}

}

void dx_LOSetOutput(QC_AIO_SrcSel src_select)
{
	dx_AIO1SetOutput(src_select);
}
void dx_AIO1SetOutput(QC_AIO_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_ANALOG_POWER_VADDR,_BIT14,_BIT14);// cahnge AIO1 to AOUT mode;

	switch(src_select)
		{
		case DAC1:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT30|_BIT26, 0x0);	// Unmute DAC1 of AIO1
			break;
		case DAC0:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT31|_BIT27, 0x0);	// Unmute DAC0 of AIO1
			break;
		case ADCFE:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT29|_BIT25, 0x0);	// Unmute ADCFE of AIO1
			break;
		default: //Mute All
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
		}


}

void dx_AIO2SetOutput(QC_AIO_SrcSel src_select)
{
	WriteMaskRegister(AUDIO_ANALOG_POWER_VADDR,_BIT13,_BIT13);// cahnge AIO2 to AOUT mode;
	switch(src_select)
		{
		case DAC1:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT22|_BIT18, 0x0);	// Unmute DAC1 of AIO2
			break;
		case DAC0:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT23|_BIT19, 0x0);	// Unmute DAC0 of AIO2
			break;
		case ADCFE:
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR, _BIT21|_BIT17, 0x0);	// Unmute ADCFE of AIO2
			break;
		default: //Mute All
			WriteMaskRegister(AUDIO_ANALOG_FRONTEND_MUTE_VADDR,0xFFFF0000,0xFFFF0000);	// Mute all output of AIO1 / AIO2
		}
}

#endif

#ifdef config_AudioFunction
UINT32 dx_AutotSineCheck(UINT32 amplitude, UINT32 cntthd, UINT32 frequency ,QC_LRCH_Sel ch_select)
{
	UINT32 cntgolden;
	
	cntgolden= 48000/(2*frequency);
	WriteMaskRegister(AUDIO_SINE_AUTO_CHK_VADDR, _BIT31, 0);
	aud_Delay(100);
	WriteMaskRegister(AUDIO_SINE_AUTO_CHK_VADDR, _BIT30|_BIT29|_BIT28, ch_select<<28);
	WriteMaskRegister(AUDIO_SINE_AUTO_CHK_VADDR, _BIT21|_BIT20, amplitude<<20);
	WriteMaskRegister(AUDIO_SINE_AUTO_CHK_VADDR, 0x3FFFF, (cntthd<<12)+cntgolden);
	aud_Delay(10);
	WriteMaskRegister(AUDIO_SINE_AUTO_CHK_VADDR, _BIT31, _BIT31);
	aud_Delay(500);
	if((ReadRegister(AUDIO_SINE_AUTO_CHK_VADDR)&_BIT24)>>24)
		{
		return 0;
		}
	else
		{
		printk("realgolden = %d \n",ReadRegister(AUDIO_SINE_WAVE_VALUE_VADDR)&(0x00000fff) );
		return 1;
		}
	
}
UINT32 dx_PeakDetectSet(QC_PeakDetect_Sel peakdetect_select, QC_FIFO_SrcSel src_select, QC_LRCH_Sel ch_select)
{
	UINT32 peak;
	switch(peakdetect_select)
		{
		case PostPeakDetect:
			//printk("Postpeak\n");
			WriteMaskRegister(AUDIO_POST_PEAK_CONTORL_VADDR, _BIT4, 0);
			//WriteMaskRegister(AUDIO_POST_PEAK_CONTORL_VADDR,_BIT3|_BIT2|_BIT1|_BIT0, src_select);
			WriteMaskRegister(AUDIO_POST_PEAK_STATUS_R_VADDR , 0xFFFF, 0);
			WriteMaskRegister(AUDIO_POST_PEAK_STATUS_L_VADDR , 0xFFFF, 0);
			WriteMaskRegister(AUDIO_POST_PEAK_CONTORL_VADDR, _BIT4, _BIT4);
			aud_Delay(100);
			if(ch_select)
				peak = ReadRegister(AUDIO_POST_PEAK_STATUS_R_VADDR )&0xFFFF;
			else
				peak = ReadRegister(AUDIO_POST_PEAK_STATUS_L_VADDR )&0xFFFF;
		break;
		
		case PrePeakDetect:
			//printk("Prepeak\n");
			WriteMaskRegister(AUDIO_PEAK_CONTORL_VADDR , _BIT4, 0);
			WriteMaskRegister(AUDIO_PEAK_CONTORL_VADDR, _BIT3|_BIT2|_BIT1|_BIT0, src_select);
			WriteMaskRegister(AUDIO_PEAK_STATUS_R_VADDR, 0xFFFF, 0);
			WriteMaskRegister(AUDIO_PEAK_STATUS_L_VADDR, 0xFFFF, 0);
			WriteMaskRegister(AUDIO_PEAK_CONTORL_VADDR, _BIT4, _BIT4);
			aud_Delay(100);
			if(ch_select)
				peak= ReadRegister(AUDIO_PEAK_STATUS_R_VADDR)&0xFFFF;
			else
				peak = ReadRegister(AUDIO_PEAK_STATUS_L_VADDR)&0xFFFF;
		break;
		
		}
	return peak;
}

#endif

#ifdef config_AudioDMA
void dx_DmaTsPath(QC_DMA_PATH is_ts_dma){
	WriteMaskRegister(AUDIO_DVOL_CONTROL_VADDR, _BIT0, is_ts_dma);
}
void dx_DmaDsPath(QC_DMA_PATH is_play_dma){
	WriteMaskRegister(AUDIO_HW_PROCESS_CONTROL_VADDR, _BIT5, is_play_dma<<5);
}
void dx_InternalPatternGenerator(QC_InternalPeattern_Sel test_case, QC_ChannelNumber_Sel chs) 
{

	switch(test_case){
		case triangular_wave:
			// pattern generate triangular wave 2ch or 8ch
			if(chs== twoCH) {
				WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT28);
				dx_DmaDsPath(DMA_Play);
				}
			else{
				WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT28|_BIT21|_BIT20);
				dx_DmaDsPath(DMA_Play);
				}
			break;
		
		case increase_count_wave:
			//pattern generate increase count wave 2ch or 8ch
			if(chs==twoCH){
				WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29);
				dx_DmaDsPath(DMA_Play);
				}
			else{
				WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29|_BIT21|_BIT20);
				dx_DmaDsPath(DMA_Play);
				}
			break;
		default:
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29|_BIT28|_BIT21|_BIT20);
			dx_DmaDsPath(DMA_Play);
			
		}

	return ;
}

void dx_InternalPatternGeneratorTS(QC_InternalPeattern_Sel test_case, QC_ChannelNumber_Sel chs) 
{

	switch(test_case){
		case triangular_wave:
			// pattern generate triangular wave 2ch or 8ch
			if(chs== twoCH) {
				WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT28);
				dx_DmaTsPath(DMA_Play);
				}
			else{
				WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT28|_BIT21|_BIT20);
				dx_DmaTsPath(DMA_Play);
				}
			break;
		
		case increase_count_wave:
			//pattern generate increase count wave 2ch or 8ch
			if(chs==twoCH){
				WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29);
				dx_DmaTsPath(DMA_Play);
				}
			else{
				WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29|_BIT21|_BIT20);
				dx_DmaTsPath(DMA_Play);
				}
			break;
		default:
			WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28|_BIT21|_BIT20, _BIT29|_BIT28|_BIT21|_BIT20);
			dx_DmaTsPath(DMA_Play);
			
		}

	return ;
}

int dx_DmaSetWrAddr(int is_play_dma, int buf_samples, int channels, unsigned int* wr_buf_addr)
{
	int i;
//	printk("DMA WR ADDR\n");	
	if(is_play_dma){
		if(channels>2)
			channels=2;
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, 0xE0000, (channels-1)<<17);
		for(i=0; i<channels; i++)
			WriteMaskRegister(AUDIO_ADMA_WSADR0_VADDR+i*4, 0xFFFFFFC0, wr_buf_addr + i*buf_samples);
	}
	else{
		if(channels>2)
			channels=2;
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, 0xE0000, (channels-1)<<17);
		for(i=0; i<channels; i++)
			WriteMaskRegister(AUDIO_TS_ADMA_WSADR0_VADDR+i*4, 0xFFFFFFC0, wr_buf_addr + i*buf_samples);
	}
	return 0;
}

int dx_DmaSetRdAddr(int is_play_dma, int buf_samples, int channels, unsigned int* rd_buf_addr)
{
	int i;
//	printk("DMA RD ADDR\n");
	if(is_play_dma){
		if(channels>4)
			channels=4;
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, 0xE000, (channels-1)<<13);

		for(i=0; i<channels; i++)
			WriteMaskRegister(AUDIO_ADMA_RSADR0_VADDR+i*4, 0xFFFFFFC0, rd_buf_addr + i*buf_samples);
	}
	else{
		// TS DMA 3-ch Read not support here
		if(channels>3)
			channels=3;
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, 0xE000, (channels-1)<<13);

		for(i=0; i<channels; i++)
			WriteMaskRegister(AUDIO_TS_ADMA_RSADR0_VADDR+i*4, 0xFFFFFFC0, rd_buf_addr + i*buf_samples);
	}
	return 0;
}

QC_DMA_CFG dx_DmaConfig(QC_DMA_SrcSel dma_src,QC_DMA_Format dma_type, 
	QC_ChannelNumber_Sel wr_channel, QC_ChannelNumber_Sel rd_channel, UINT32 samples,QC_Path_Sel is_playback)
{
	QC_DMA_CFG dma_cfg;
	
	dma_cfg.src_from = dma_src;
	dma_cfg.pcm_format = dma_type;
	dma_cfg.wr_channels = wr_channel;
	dma_cfg.rd_channels = rd_channel;
	dma_cfg.samples = samples;
	dma_cfg.is_playback = is_playback;

	return dma_cfg;
	
}

void dx_DmaSetEnv(QC_DMA_CFG dma_cfg, unsigned int* pOut_wr_addr, unsigned int* pOut_rd_addr)
{
	UINT32 Mem_Shift;
	Mem_Shift = (0xA0000000-((UINT32)pOut_wr_addr&0xF0000000))/sizeof(pOut_wr_addr);//memory address mapping(start from 0xa0000000)
	//set R/W buffer
	dx_DmaSetRdAddr(dma_cfg.is_playback, dma_cfg.samples, dma_cfg.rd_channels, pOut_rd_addr+Mem_Shift);
	dx_DmaSetWrAddr(dma_cfg.is_playback, dma_cfg.samples, dma_cfg.wr_channels, pOut_wr_addr+Mem_Shift);
	if(dma_cfg.is_playback){
		
		//DMA initial setting
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT29|_BIT28, 0); //DMA output from DMA read
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT27|_BIT26, 0); //DMA R/W TV format
		
		//DMA user setting
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT31|_BIT30, (dma_cfg.src_from)<<30);
		WriteMaskRegister(AUDIO_ADMA_CHCONF_VADDR, 0x7FFF0000, (dma_cfg.samples/16)<<16);
		WriteMaskRegister(AUDIO_ADMA_CHCONF_VADDR, 0x7FFF, (dma_cfg.samples/16));
		WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT16|_BIT12, (dma_cfg.pcm_format)<<16|(dma_cfg.pcm_format)<<12);
	}
	else{
		
		//DMA initial setting
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT29|_BIT28, 0); //TS DMA output from TS DMA read
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT27|_BIT26, 0);
		
		//DMA user setting
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT31|_BIT30, (dma_cfg.src_from)<<30);
		WriteMaskRegister(AUDIO_TS_ADMA_CHCONF_VADDR, 0x7FFF0000, (dma_cfg.samples/16)<<16);
		WriteMaskRegister(AUDIO_TS_ADMA_CHCONF_VADDR, 0x7FFF, (dma_cfg.samples/16));
		WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT16|_BIT12, (dma_cfg.pcm_format)<<16|(dma_cfg.pcm_format)<<12);
	}		
	return;
}

int dx_DmaSetPattern(QC_DMA_CFG dma_cfg, unsigned int* rdBufAddr, int patternX)
{
	int i, j, k;
	UINT32 Mem_Shift;
	Mem_Shift = (0xA0000000-((UINT32)rdBufAddr&0xF0000000))/sizeof(rdBufAddr);//memory address mapping(start from 0xa0000000)
	switch(patternX){
		case 4:
			// 2 ch 0xFFFFFF + 2ch 0x0
			for(i=0; i<2; i++)
				for(j=0; j<dma_cfg.samples; j++)
					WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j, 0x0);
				
			for(i=2; i<4; i++)
				for(j=0; j<dma_cfg.samples; j++)
					WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j, 0xFFFFFF);
			break;

		case 3:
			// 8 ch 0xFFFFFF
			for(i=0; i<dma_cfg.rd_channels; i++)
				for(j=0; j<dma_cfg.samples; j++)
					WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j, 0xFFFFFF);
			break;

		case 30:
			// 8ch 0x0
			for(i=0; i<dma_cfg.rd_channels; i++)
				for(j=0; j<dma_cfg.samples; j++)
					WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j, 0x0);
			break;
		case 40:
			// 2ch 0x12345678
			for(i=0; i<dma_cfg.rd_channels; i++)
				for(j=0; j<dma_cfg.samples; j++)
					WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j, 0x12345678);
			break;

		case 1:
		case 2:
		case 20:
			for(i=0; i<dma_cfg.rd_channels; i++){
				for(j=0; j<dma_cfg.samples/16  ; j++){
					// little-endian in 4KE, -12dBFS
					// 1500Hz -6dBFS sinc wave
					for(k=0; k<8; k++)
						WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j*16+k, 0xFFFF1F);
					for(k=8; k<16; k++)
						WriteRegister(rdBufAddr+Mem_Shift+i*dma_cfg.samples+j*16+k, 0x0000E0);
				}
			}
			break;
		default:
		
		for(i=0; i<dma_cfg.rd_channels; i++){
			for(j=0; j<dma_cfg.samples; j++){
				//CPU lexra version
				//WriteRegister(rdBufAddr+(i*bufSamples+j)*4, 0+(i<<29)+(0xC<<24)+(j<<12)+((j%8)<<8));
				//CPU 4KE version
				//if(i==1&&j==0)
					//printk("ch2= %x , %x, %x\n",rdBufAddr,i*dma_cfg.samples,rdBufAddr+(i*dma_cfg.samples+j));
				WriteRegister(rdBufAddr+Mem_Shift+(i*dma_cfg.samples+j), (i<<1)+((j%8)<<4)+(j<<8));
				
			}
		}
		break;	
	}
	return 0;
}

int dx_DmaCleanTargetBuffer(QC_DMA_CFG dma_cfg, unsigned int* wr_buf_addr)
{
	int i, j;
	UINT32 Mem_Shift;
	Mem_Shift = (0xA0000000-((UINT32)wr_buf_addr&0xF0000000))/sizeof(wr_buf_addr);//memory address mapping(start from 0xa0000000)
	for(i=0; i<dma_cfg.wr_channels; i++){
		for(j=0; j<dma_cfg.samples; j++){
					//printk("WR = %x, %x\n", wr_buf_addr+(i*dma_cfg.samples+j), wr_buf_addr);
			WriteRegister(wr_buf_addr+Mem_Shift+(i*dma_cfg.samples+j), 0x0dead000);
		}
	}
	return 0;
}

UINT32 dx_DmaCompare(QC_DMA_CFG dma_cfg, UINT32* wr_buf_addr,UINT32* rd_buf_addr)
{
	UINT32 i, j, nStartIndex, nResult,Mem_Shift;
	nResult=0;
	nStartIndex=dma_cfg.samples;

	Mem_Shift = (0xA0000000-((UINT32)wr_buf_addr&0xF0000000))/sizeof(wr_buf_addr);//memory address mapping(start from 0xa0000000)
	//Mem_Shift = 0;

	for(i=0; i<dma_cfg.wr_channels; i++){
		for(j=0; j<dma_cfg.samples; j++){
			if( ReadRegister(wr_buf_addr+Mem_Shift+j) == ReadRegister(rd_buf_addr+Mem_Shift) ){
				nStartIndex=j;
				//printk("index %x R %x : %x, %x\n",wr_buf_addr+Mem_Shift+nStartIndex+j,rd_buf_addr+Mem_Shift,ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex+j) ,ReadRegister(rd_buf_addr+Mem_Shift));
				//printk("Inedex = %d\n", j);
				break;
			}
		}

		if(nStartIndex==dma_cfg.samples){
			printk("CH %d fail to search\n", i);
			return 1;
		}
		else
			//printk("%d sIndex ", nStartIndex);
		//printk("comparing ch %d\n", i);
#if 1
		// sample-by-sample comparision
		for(j=0; j<(dma_cfg.samples-nStartIndex); j++){//WR: nStartIndex~samples ;RD: 0~samples-nStartIndex
			if(ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex+j) != ReadRegister(rd_buf_addr+Mem_Shift+j)){
				//printk("W1 %x R %x : %x, %x\n",wr_buf_addr+Mem_Shift+nStartIndex+j,rd_buf_addr+Mem_Shift+j,ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex+j) ,ReadRegister(rd_buf_addr+Mem_Shift+j));
				if(ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex+j) != ReadRegister(rd_buf_addr+Mem_Shift+j)){
					nResult++;
					if(nResult<30)
					printk("w2 %x R %x : %x, %x\n",wr_buf_addr+Mem_Shift+nStartIndex+j,rd_buf_addr+Mem_Shift+j,ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex+j) ,ReadRegister(rd_buf_addr+Mem_Shift+j));
				}
			}
		}
		//printk("\n");
		for(j=dma_cfg.samples-nStartIndex; j<dma_cfg.samples; j++){//WR: 0~nStartIndex ;RD samples-nStartIndex ~ samples
			if(ReadRegister(wr_buf_addr+Mem_Shift+nStartIndex-dma_cfg.samples+j) != ReadRegister(rd_buf_addr+Mem_Shift+j)){
				//printk("E%x",wr_buf_addr+nStartIndex+j);
				nResult++;
			}
		}
		//printk("\n");
#endif
	}
//	printk("finish DMA comparison %d\n", nResult);
	return nResult;
}



int dx_DmaExecute(QC_Path_Sel is_playback, int edgecute)
{
	if(is_playback){
		if(edgecute){
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT7|_BIT6, _BIT7|_BIT6);
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT7|_BIT6, 0);
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT4|_BIT5, _BIT4|_BIT5);
		}
		else{
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT4, 0);
			WriteMaskRegister(AUDIO_ADMA_CSR_VADDR, _BIT5, 0);
		}
	}
	else{
		if(edgecute){
			WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT7|_BIT6, _BIT7|_BIT6);
			WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT7|_BIT6, 0);
			WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT5|_BIT4, _BIT5|_BIT4);
		}
		else
			WriteMaskRegister(AUDIO_TSADMA_CSR_VADDR, _BIT5|_BIT4, 0);
	}
	return 0;
}
#endif

//i2s internal path samplerate detection
UINT32 aud_esd_I2s()
{
	UINT32 i2sSampleRate=0x1F;
	dx_I2sSetInputPri(I2S_loopback); // from internal
	dx_I2sSetOutput(0, 0); // from HPP PCM
	i2sSampleRate = dx_I2sGetSampleRate();

	if(i2sSampleRate != 0x9)
		{
		printk("[ESD] I2S   Pad    Fail SR %d\n", i2sSampleRate);
		printk("%d\n",ReadRegister(AUDIO_I2S_IN_PRIMARY_VADDR));
		return 1;
		}
	else
		{
		printk("[ESD] I2S    Pad    OK\n");
		return 0;
		}

}

//spdif internal path samplerate detection
UINT32 aud_esd_Spdif()
{
	UINT32 spdifSampleRate=0x1F;

	dx_SpdifSetInput(SPDIF_loopback); // from PAD
	dx_SpdifSetOutput(0, 0); // from HPP PCM
	aud_Delay(10);
	spdifSampleRate = dx_SpdifGetSampleRate();

	if(spdifSampleRate != 0x9)
		{
		printk("[ESD] SPDIF  Pad    Fail SR %d\n", spdifSampleRate);
		return 1;
		}
	else
		{
		printk("[ESD] SPDIF  Pad    OK\n");
		return 0;
		}
}


//all of aud_baseband_PeakDetection ( analog path peak detection )
UINT32 aud_baseband_PeakDetection(QC_AudioTestcase test_case)
{
	UINT32 adcPeakValueL=0x0, adcPeakValueR=0x0;
	UINT32 esdBasebandResult=0;

	dx_Dac0SetOutput(0);	// PB DMA --> DAC0
	dx_Dac1SetOutput(3);	// TS DMA --> DAC1
	switch(test_case){
		
		case PCB_QFP:			
			// Internal pattern <PB DMA>--> AIO2 --> AIN2
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO2SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN2);
			dx_AIO2SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC0 --> AIO2 --> AIN2   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <TS DMA>--> HP --> AIN3
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_HPSetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN3);
			dx_HPSetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC1 --> HP --> AIN3   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <PB DMA> --> AIO1 --> AIN1
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN1);
			dx_AIO1SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC0 --> AIO1 --> AIN3   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);
			break;
			
		case PCB_BGA:
			// Internal pattern <PB DMA>--> AIO2 --> AIN2
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO2SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN2);
			dx_AIO2SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC0 --> AIO2 --> AIN2   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <TS DMA>--> HP --> AIN3
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_HPSetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN3);
			dx_HPSetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC1 --> HP --> AIN3   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <PB DMA> --> AIO1 --> AIN1
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN1);
			dx_AIO1SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC0 --> AIO1 --> AIN3   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);
			
			// Internal pattern <TS DMA> --> AIO1 --> AIN4
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN4);
			dx_AIO1SetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(triangular_wave, twoCH) ;
			aud_Delay(50);
			adcPeakValueL = dx_PeakDetectSet(PrePeakDetect, ADC, CHL);
			adcPeakValueR = dx_PeakDetectSet(PrePeakDetect, ADC, CHR);
			printk("\n[BB] DAC0 --> AIO1 --> AIN4   L-%d R-%d ", adcPeakValueL, adcPeakValueR);
			if( adcPeakValueL < 0x1000 || adcPeakValueR < 0x1000){
				printk("Fail", adcPeakValueL, adcPeakValueR);
				esdBasebandResult++;
			}
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);
			break;
			
		default :
			printk("PeakDetection Failed\n");
			esdBasebandResult ++;
			
	}
	printk("\n\n");
	return esdBasebandResult;
}

UINT32 aud_baseband_AutoSineCheck(QC_AudioTestcase test_case)
{
	UINT32 flagL=0, flagR=0;
	UINT32 esdBasebandResult=0;

	dx_Dac0SetOutput(0);
	dx_Dac1SetOutput(3);

	switch(test_case){
		
		case PCB_QFP:
			// Internal pattern <PB DMA>--> AIO2 --> AIN2
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO2SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN2);
			dx_AIO2SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC0 --> AIO2 --> AIN2   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC0 --> AIO2 --> AIN2   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <TS DMA>--> HP --> AIN3
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_HPSetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN3);
			dx_HPSetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC1 --> HP --> AIN3   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC1 --> HP --> AIN3   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <PB DMA>--> AIO1 --> AIN1
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN1);
			dx_AIO1SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC0 --> AIO1 --> AIN1   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC0 --> AIO1 --> AIN1   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);
			break;
			
		case PCB_BGA:
			// Internal pattern <PB DMA>--> AIO2 --> AIN2
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO2SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN2);
			dx_AIO2SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC0 --> AIO2 --> AIN2   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC0 --> AIO2 --> AIN2   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <TS DMA>--> HP --> AIN3
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_HPSetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN3);
			dx_HPSetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC1 --> HP --> AIN3   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC1 --> HP --> AIN3   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <PB DMA>--> AIO1 --> AIN1
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN1);
			dx_AIO1SetOutput(DAC0);
			aud_Delay(10);
			dx_InternalPatternGenerator(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC0 --> AIO1 --> AIN1   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC0 --> AIO1 --> AIN1   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);

			// Internal pattern <TS DMA>--> AIO1 --> AIN4
			dx_InternalPatternGenerator(zeros, twoCH) ;
			dx_InternalPatternGeneratorTS(zeros, twoCH) ;
			dx_AdcSetInput(MUTEALL);
			dx_AIO1SetOutput(MUTEALL);
			aud_Delay(10);
			dx_FifoPlay_CH01(ADC);
			dx_AdcSetInput(AIN4);
			dx_AIO1SetOutput(DAC1);
			aud_Delay(10);
			dx_InternalPatternGeneratorTS(increase_count_wave, twoCH) ;
			aud_Delay(50);
			flagL=dx_AutotSineCheck(2,2,750,CHL);
			flagR=dx_AutotSineCheck(2,2,750,CHR);
			if(flagL||flagR){
				printk("[BB] DAC1 --> AIO1 --> AIN4   ASC Fail L%dR%d\n",flagL,flagR);
				esdBasebandResult++;
			}
			else
				printk("[BB] DAC1 --> AIO1 --> AIN4   ASC Ok\n");
			dx_DmaDsPath(DMA_Bypass);
			dx_DmaTsPath(DMA_Bypass);
			break;
			
		default :
			printk("AutoSineCheck Failed\n");
			esdBasebandResult ++;
			
	}
	printk("\n\n");
	return esdBasebandResult;
}

int aud_QcDma(unsigned int *wr_ptr, unsigned int *rd_ptr)
{
	int nResult=0;
	QC_DMA_CFG dma_cfg_PB;
	QC_DMA_CFG dma_cfg_TS;

	// 2ch internal loopback
	dma_cfg_PB = dx_DmaConfig(test_RX_FIFO,DMA_PCM,twoCH,twoCH,DMABUFSAMPLES,PB_Path);
	dx_DmaSetEnv(dma_cfg_PB,wr_ptr,rd_ptr);
	dx_DmaSetPattern(dma_cfg_PB, rd_ptr,0);
	dx_DmaCleanTargetBuffer(dma_cfg_PB, wr_ptr);
	aud_Delay(50);
	dx_DmaExecute(dma_cfg_PB.is_playback, 1);
	aud_Delay(200);
	dx_DmaExecute(dma_cfg_PB.is_playback, 0);
	if(dx_DmaCompare(dma_cfg_PB, wr_ptr, rd_ptr)==0)
		printk("[QC]  DMA loopback  Ok\n");
	else{
		printk("[QC]  DMA loopbak  Fail\n");
		nResult++;
	}
	
	// 2ch PB spdif loopback
	dma_cfg_PB = dx_DmaConfig(pre_HWP,DMA_PCM,twoCH,twoCH,DMABUFSAMPLES,PB_Path);
	dx_DmaSetEnv(dma_cfg_PB,wr_ptr,rd_ptr);
	dx_DmaSetPattern(dma_cfg_PB, rd_ptr,0);
	dx_DmaCleanTargetBuffer(dma_cfg_PB, wr_ptr);
	dx_SpdifSetInput(SPDIF_loopback); // from PAD
	//dx_SpdifSetInput(SPDIF_normal);
	dx_SpdifSetOutput(SPDIF_normal, 0); 
	dx_FifoPlay_CH01(SPDIFin);
	dx_DmaDsPath(DMA_Play);
	aud_Delay(50);
	dx_DmaExecute(dma_cfg_PB.is_playback, 1);
	aud_Delay(200);
	dx_DmaExecute(dma_cfg_PB.is_playback, 0);

	if(dx_DmaCompare(dma_cfg_PB, wr_ptr, rd_ptr)==0)
		printk("[QC]  DMA DS_SPDIF  Ok\n");
	else{
		printk("[QC]  DMA DS_SPDIF  Fail\n");
		nResult++;
	}

	// 2ch TS I2S loopback
	dma_cfg_TS= dx_DmaConfig(pre_HWP,DMA_PCM,twoCH,twoCH,DMABUFSAMPLES,TS_Path);
	dx_DmaSetEnv(dma_cfg_TS,wr_ptr,rd_ptr);
	dx_DmaSetPattern(dma_cfg_TS, rd_ptr,3);
	dx_DmaCleanTargetBuffer(dma_cfg_TS, wr_ptr);
	dx_I2sSetInputPri(I2S_loopback); // from PAD
	dx_I2sSetOutput(I2S_normal, 3); 
	dx_FifoTs_CH01(I2Sch01);
	dx_DmaTsPath(DMA_Play);
	aud_Delay(50);
	dx_DmaExecute(dma_cfg_TS.is_playback, 1);
	aud_Delay(200);
	dx_DmaExecute(dma_cfg_TS.is_playback, 0);

	if(dx_DmaCompare(dma_cfg_TS, wr_ptr, rd_ptr)==0)
		printk("[QC]  DMA TS_I2S    Ok\n");
	else{
		printk("[QC]  DMA TS_I2S    Fail\n");
		nResult++;
	}
	
	// 2ch NonPCM spdif loopback
	dma_cfg_PB = dx_DmaConfig(pre_HWP,DMA_nonPCM,oneCH,oneCH,DMABUFSAMPLES,PB_Path);
	dx_DmaSetEnv(dma_cfg_PB,wr_ptr,rd_ptr);
	dx_DmaSetPattern(dma_cfg_PB, rd_ptr,40);
	dx_DmaCleanTargetBuffer(dma_cfg_PB, wr_ptr);
	dx_SpdifSetInput(SPDIF_loopback); // from PAD
	dx_SpdifSetOutput(SPDIF_normal, 5); 
	dx_FifoPlay_CH01(SPDIFin);
	dx_DmaDsPath(DMA_Play);
	aud_Delay(50);
	dx_DmaExecute(dma_cfg_PB.is_playback, 1);
	aud_Delay(200);
	dx_DmaExecute(dma_cfg_PB.is_playback, 0);

	if(dx_DmaCompare(dma_cfg_PB, wr_ptr, rd_ptr)==0)
		printk("[QC]  DMA NonPCM    Ok\n");
	else{
		printk("[QC]  DMA NonPCM    Fail\n");
		nResult++;
	}
	return nResult;
}
#ifdef audio_debug
UINT32 aud_DMA_dacout_test()
{
	QC_DMA_CFG dma_cfg_PB;
	QC_DMA_CFG dma_cfg_TS;
	dma_cfg_PB = dx_DmaConfig(pre_HWP,DMA_PCM,twoCH,twoCH,5000000,PB_Path);//buffer 50k
	dx_DmaSetEnv(dma_cfg_PB,pWrBuf,pWrBuf);
	dx_AdcSetInput(MUTEALL);
	aud_Delay(50);
	dx_DmaDsPath(DMA_Play);
	dx_FifoPlay_CH01(ADC);
	dx_AdcSetInput(AIN3);
	dx_HPSetOutput(DAC0);
	aud_Delay(50);
	dx_DmaExecute(PB_Path,1);
	
}
#endif
int QC_Verifier_AUDIO(void)
{
	UINT32 	aioResult; /* 0 means Zero Error, other means something goes wrong */
	QC_AudioTestcase test_case;
	char ICPackage[20];
	
	printk("Hello Audio!\n");
	g_audio_initialize_done = 0;
	aud_DrInitialize();
	if( g_audio_initialize_done == 0){
		printk("Init Audio Failed!\n");
		return FAILED;
	}
	aioResult = 0;
	
	#if  CONFIG_BGA// For BGA
	test_case = PCB_BGA;
	strcpy(ICPackage,"Sirius BGA");	

	#else // For QFP
	test_case = PCB_QFP;
	strcpy(ICPackage,"Sirius QFP");
	
	#endif	

	printk("QC Audio Test %s!\n",ICPackage);
	
	aioResult += aud_QcDma(pWrBuf, pRdBuf);
	aioResult += aud_esd_Spdif();
	aioResult += aud_esd_I2s();
	aioResult += aud_baseband_AutoSineCheck(test_case);
	aioResult += aud_baseband_PeakDetection(test_case);
	
	if(aioResult==0)
		return SUCCESS;
	else
		return FAILED;
}

