#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

#include "ifd_driver.h"

//ben remove StructIFDDataType stIFDdefaultUserData;
//ben remove StructIFDDataType stIFDUserData;

StructIFDDataType /*IFD_CODE*/ stIFDUserData=
{
#ifdef CONFIG_TUNER_XUGUANG_HFT3_86H_115CW
		IFD_FLASH_MAGIC_CODE,											//ifdMagicCode
		IFD_AGC_2STEP_NOIFAMP_PGA,										//ifdAGCPGAMode;
		0,																//ifdAGCFixPGAValue;
		{0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00,
		  0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00,
		  0xa00, 0xa00, 0xa00, 0xa00, },										//AGCVtop[IFD_TUNER_BAND_MAX];
		{0, 7, 25, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
		  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
		  0x22, 0x22, 0x22, 0x22, },											//AGC_PGA_MIN[IFD_TUNER_BAND_MAX]
		0,																//SCANdelay;
		0, 																//SETCHANNELdelay;
		0,																//CRPhaseInverseThr;
		16,																//CRinverse_debounce;
		0x1,//CRSt3pgain;
		0x6,//CRSt3igain;
		0x2,//CRSt2pgain;
		0x7,//CRSt2igain;
		0x5,//CRSt0pgain;
		0x9,//CRSt0igain;
		0x2,//CRpgain;
		0x7,//CRigain;
		0x8,//CRlock_err_thd;
		0x0,//CRweight_speed;
		IFD_DISABLE,//CRphasebad_en;
		0x52,//CRvariance_thr;
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_MN[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_B[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_GH[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_I[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_DK[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_L[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_21P6M_N15P1M,//CRBpf_Table_LA[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_POS_16M_N22P5,//CRBpf_Table_SCAN[IFD_CR_BPF_TABLE_SIZE];
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_MN;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_BGH;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_IDKL;
		IFD_CR_INNER_LPF_STOP_6P2M,//CRInnerLpf_LA;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_SCAN;
		IFD_ENABLE,//GRPdelayM_En;
		IFD_ENABLE,//GRPdelayN_En;
		IFD_DISABLE,//GRPdelayBG_En;
		IFD_DISABLE,//GRPdelayDKL_En;
		IFD_GROUPDELAY_TABLE_M,//GRPdelayTableM[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_N,//GRPdelayTableN[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_BG_CURVE_B,//GRPdelayTableBG[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_DK_CZECH,//GRPdelayTableDKL[IFD_GP_BPF_TABLE_SIZE];
		IFD_ENABLE,//InputFltNtsc_En;
		IFD_ENABLE,//InputFltPalD_En;
		IFD_ENABLE,//InputFltPalB_En;
		IFD_ENABLE,//InputFltPalN_En;
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTableNtsc[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_DKL,//InputFltTablePalD[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTablePalB[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTablePalN[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_MN,//VideoLpfNTSC[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_BG,//VideoLpfPAL_BG[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_I,//VideoLpfPAL_I[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_DKL,//VideoLpfPAL_DKL[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_DKL,//VideoLpfSECAM[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_ENABLE,//EQ_Table_NTSC_En;
		IFD_ENABLE,//EQ_Table_PAL_BG_En;
		IFD_DISABLE,//EQ_Table_PAL_I_En;
		IFD_DISABLE,//EQ_Table_PAL_DKL_En;
		IFD_EQ_TABLE_NTSC_0,//EQ_Table_NTSC[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALBG_0,//EQ_Table_PAL_BG[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALI_0,//EQ_Table_PAL_I[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALDKL_0,//EQ_Table_PAL_DKL[IFD_EQ_TABLE_SIZE];
		{0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00,
		  0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00, 0x1d00,
		  0x1d00, 0x1d00, 0x1d00, 0x1d00, },		//AGC_rf_max[IFD_TUNER_BAND_MAX];
		{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, },					//AGC_rf_min[IFD_TUNER_BAND_MAX];
		{0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400,
		  0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400,
		  0x400, 0x400, 0x400, 0x400, },	//AGC_krf[IFD_TUNER_BAND_MAX];
		0x1fff,//AGC_if_max;
		0x0,//AGC_if_min;
		0x300,//AGCloop1_maxtargetNTSC;
		0x300,//AGCloop1_maxtargetPAL;
		0x300,//AGCloop1_maxtargetSECAM;
		0x110,//AGCloop1_difftarget;
		0x790,//AGCloop1_peaktarget;
		IFD_DISABLE,//AGCloop1_peakforce_en
		0x18,//AGCloop1_kpgain;
		0x0,//AGCloop1_kigain;
		0x5,//AGCloop1_kpkishift;
		0xf,//AGCloop1_dnsample;
		0x000,//AGCloop1_finednsample;
		0x1,//AGCloop2_kpgain;
		0x0,//AGCloop2_kigain;
		0x3,//AGCloop2_kpshift;
		0x7,//AGCloop2_kishift;
		0x0f,//AGCloop2_dnsample;
		0x0fff,//AGCloop2_finednsample;
		IFD_DISABLE, //AGC_RfHasten_en;
		0x6,         //AGC_RfHasten_ki;
		0x1,       //AGC_RfHasten_cntl;
		0x5c0,      //AGC_RfHasten_thr;
		IFD_DISABLE,  //AGC_SepRfIf_en;
		0x0,          //AGC_SepRfIf_IfKp;
		0x3,          //AGC_SepRfIf_IfKi;
		0x7f,      //AGCadapt_fineinterval;
		0xf,           //AGCadapt_interval;
		IFD_ENABLE,          //AGCadapt_en;
		0x100,           //AGCadapt_incthr;
		0x10,     //AGCadapt_mindifftarget;
		0x40,      //AGCadapt_minmaxtarget;
		0x70,     //AGCadapt_finetargetthr;
		0x8,     //AGCadapt_diffcoarsestep;
		0x0,//AGCImpulsive_GateEnd;
		0x0,//AGCImpulsive_DetThr;
		0x0,//AGCImpulsive_Input;
		0x0,//AGCImpulsive_MakeEn;
		0x0,//AGCImpulsive_DetEn;
		0x0,//AGCImpulsive_DetStop;
		0x0,//AGCImpulsive_GateDelay;
		0x0,//AGCHum_Debounce;
		0x0,//AGCHum_UpdateSel;
		0x0,//AGCHum_En;
		0x0,//AGCHum_MaxThrOut;
		0x0,//AGCHum_MaxThrIn;
		0x0,//AGCHum_SyncThrOut;
		0x0,//AGCHum_SyncThrIn;
		0x4,//AGCSigmaDeltaDnSel;
		0x400,//AGCDataTarg;
		IFD_VIDEOPATH_OUTPUT_GAIN_ADAPTIVE,//DataGainSel;
		IFD_CLAMP_SCALE_1D4,//CLAMPscale_scanch;
		IFD_CLAMP_SCALE_1D64,//CLAMPscale_setch;
		IFD_SHAPING_BW_SEL_0P86M,//SHAPEfilter_bw;
		IFD_ADC_SHAGAIN_1P0X,//ADCInput_ShaGain;
		IFD_ADC_FULLSCALE_1P40V,//ADCInput_FullScale;
		IFD_CLK_RATE_162M,//ADCInput_clock;
		IFD_INPUT_DN_FILTER_162M_BPF,//ADCinput_dn_filter_sel;
		3,//AFClockthd;
		15,//AFC_STAGE_MAX_COUNT;
		1,//AFC_Max_Freq;
#elif defined(CONFIG_TUNER_NXP_TDA18273)
		IFD_FLASH_MAGIC_CODE,											//ifdMagicCode
		IFD_AGC_DOUBLE_IFAMP_NOPGA,										//ifdAGCPGAMode;
		0,																//ifdAGCFixPGAValue;
		{0x800, 0x800, 0x800, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00,
		  0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00, 0xa00,
		  0xa00, 0xa00, 0xa00, 0xa00, },										//AGCVtop[IFD_TUNER_BAND_MAX];
		{0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
		  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
		  0x22, 0x22, 0x22, 0x22, },											//AGC_PGA_MIN[IFD_TUNER_BAND_MAX]
		0,//SCANdelay;
		0,//SETCHANNELdelay;
		0,//CRPhaseInverseThr;
		16,//CRinverse_debounce;
		0x1,//CRSt3pgain;
		0x6,//CRSt3igain;
		0x2,//CRSt2pgain;
		0x7,//CRSt2igain;
		0x5,//CRSt0pgain;
		0x9,//CRSt0igain;
		0x2,//CRpgain;
		0x7,//CRigain;
		0x8,//CRlock_err_thd;
		0x0,//CRweight_speed;
		IFD_DISABLE,//CRphasebad_en;
		0x52,//CRvariance_thr;
		IFD_CRBPF_NEG_5P5M_N1P0M,//CRBpf_Table_MN[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_6P6M_N1P1M,//CRBpf_Table_B[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_6P6M_N1P1M,//CRBpf_Table_GH[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_7P45M_N1P45M,//CRBpf_Table_I[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_6P85M_N1P35M,//CRBpf_Table_DK[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_6P75M_N1P25M,//CRBpf_Table_L[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_21P6M_N15P1M,//CRBpf_Table_LA[IFD_CR_BPF_TABLE_SIZE];
		IFD_CRBPF_NEG_6P85M_N1P35M,//CRBpf_Table_SCAN[IFD_CR_BPF_TABLE_SIZE];
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_MN;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_BGH;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_IDKL;
		IFD_CR_INNER_LPF_STOP_6P2M,//CRInnerLpf_LA;
		IFD_CR_INNER_LPF_STOP_9P3M,//CRInnerLpf_SCAN;
		IFD_ENABLE,//GRPdelayM_En;
		IFD_ENABLE,//GRPdelayN_En;
		IFD_DISABLE,//GRPdelayBG_En;
		IFD_DISABLE,//GRPdelayDKL_En;
		IFD_GROUPDELAY_TABLE_M,//GRPdelayTableM[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_N,//GRPdelayTableN[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_BG_CURVE_B,//GRPdelayTableBG[IFD_GP_BPF_TABLE_SIZE];
		IFD_GROUPDELAY_TABLE_DK_CZECH,//GRPdelayTableDKL[IFD_GP_BPF_TABLE_SIZE];
		IFD_DISABLE,//InputFltNtsc_En;
		IFD_DISABLE,//InputFltPalD_En;
		IFD_DISABLE,//InputFltPalB_En;
		IFD_DISABLE,//InputFltPalN_En;
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTableNtsc[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTablePalD[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTablePalB[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_INPUTFILTER_TABLE_MNB,//InputFltTablePalN[IFD_INPUT_FILTER_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_MN,//VideoLpfNTSC[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_BG,//VideoLpfPAL_BG[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_I,//VideoLpfPAL_I[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_DKL,//VideoLpfPAL_DKL[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_OUTPUTLPF_COEF_TABLE_DKL,//VideoLpfSECAM[IFD_OUTPUT_LPF_TABLE_SIZE];
		IFD_ENABLE,//EQ_Table_NTSC_En;
		IFD_ENABLE,//EQ_Table_PAL_BG_En;
		IFD_DISABLE,//EQ_Table_PAL_I_En;
		IFD_DISABLE,//EQ_Table_PAL_DKL_En;
		IFD_EQ_TABLE_NTSC_0,//EQ_Table_NTSC[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALBG_0,//EQ_Table_PAL_BG[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALI_0,//EQ_Table_PAL_I[IFD_EQ_TABLE_SIZE];
		IFD_EQ_TABLE_PALDKL_0,//EQ_Table_PAL_DKL[IFD_EQ_TABLE_SIZE];
		{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, },		//AGC_rf_max[IFD_TUNER_BAND_MAX];
		{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		  0x0, 0x0, 0x0, 0x0, },					//AGC_rf_min[IFD_TUNER_BAND_MAX];
		{0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400,
		  0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400,
		  0x400, 0x400, 0x400, 0x400, },	//AGC_krf[IFD_TUNER_BAND_MAX];
		0xf00,//AGC_if_max;
		0x650,//AGC_if_min;
		0x2b0,//AGCloop1_maxtargetNTSC;
		0x2b0,//AGCloop1_maxtargetPAL;
		0x2b0,//AGCloop1_maxtargetSECAM;
		0x110,//AGCloop1_difftarget;
		0x790,//AGCloop1_peaktarget;
		IFD_DISABLE,//AGCloop1_peakforce_en
		0x12,//AGCloop1_kpgain;
		0x7,//AGCloop1_kigain;
		0xb,//AGCloop1_kpkishift;
		0x3,//AGCloop1_dnsample;
		0x000,//AGCloop1_finednsample;
		0x1,//AGCloop2_kpgain;
		0x0,//AGCloop2_kigain;
		0x3,//AGCloop2_kpshift;
		0x7,//AGCloop2_kishift;
		0x0f,//AGCloop2_dnsample;
		0x0fff,//AGCloop2_finednsample;
		IFD_DISABLE, //AGC_RfHasten_en;
		0x6,         //AGC_RfHasten_ki;
		0x1,       //AGC_RfHasten_cntl;
		0x5c0,      //AGC_RfHasten_thr;
		IFD_DISABLE,  //AGC_SepRfIf_en;
		0x0,          //AGC_SepRfIf_IfKp;
		0x3,          //AGC_SepRfIf_IfKi;
		0x7f,      //AGCadapt_fineinterval;
		0xf,           //AGCadapt_interval;
		IFD_ENABLE,          //AGCadapt_en;
		0x100,           //AGCadapt_incthr;
		0x10,     //AGCadapt_mindifftarget;
		0x40,      //AGCadapt_minmaxtarget;
		0x70,     //AGCadapt_finetargetthr;
		0x8,     //AGCadapt_diffcoarsestep;
		0x0,//AGCImpulsive_GateEnd;
		0x0,//AGCImpulsive_DetThr;
		0x0,//AGCImpulsive_Input;
		0x0,//AGCImpulsive_MakeEn;
		0x0,//AGCImpulsive_DetEn;
		0x0,//AGCImpulsive_DetStop;
		0x0,//AGCImpulsive_GateDelay;
		0x0,//AGCHum_Debounce;
		0x0,//AGCHum_UpdateSel;
		0x0,//AGCHum_En;
		0x0,//AGCHum_MaxThrOut;
		0x0,//AGCHum_MaxThrIn;
		0x0,//AGCHum_SyncThrOut;
		0x0,//AGCHum_SyncThrIn;
		0x4,//AGCSigmaDeltaDnSel;
		0x500,//AGCDataTarg;
		IFD_VIDEOPATH_OUTPUT_GAIN_1,//DataGainSel;
		IFD_CLAMP_SCALE_1D4,//CLAMPscale_scanch;
		IFD_CLAMP_SCALE_1D64,//CLAMPscale_setch;
		IFD_SHAPING_BW_SEL_0P86M,//SHAPEfilter_bw;
		IFD_ADC_SHAGAIN_0P6X,//ADCInput_ShaGain;
		IFD_ADC_FULLSCALE_1P40V,//ADCInput_FullScale;
		IFD_CLK_RATE_108M,//ADCInput_clock;
		IFD_INPUT_DN_FILTER_108M_LPF,//ADCinput_dn_filter_sel;
		3,//AFClockthd;
		15,//AFC_STAGE_MAX_COUNT;
		1,//AFC_Max_Freq;
#endif
};



