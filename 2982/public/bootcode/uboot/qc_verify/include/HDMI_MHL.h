#ifndef  _HDMI_MHL_H_
#define _HDMI_MHL_H_

//Display consant
#define NoDisplay 0
#define HDMI_1080i 745
#define HDMI_1080p 1485
//BITn
#define _ZERO                       			0x0
#ifndef _BIT0
#define _BIT0   						0x1
#define _BIT1   						0x2
#define _BIT2   						0x4
#define _BIT3   						0x8
#define _BIT4   						0x10
#define _BIT5   						0x20
#define _BIT6   						0x40
#define _BIT7   						0x80
#define _BIT8   						0x0100
#define _BIT9   						0x0200
#define _BIT10  						0x0400
#define _BIT11  						0x0800
#define _BIT12  						0x1000
#define _BIT13  						0x2000
#define _BIT14  						0x4000
#define _BIT15  						0x8000
#define _BIT16   						0x00010000
#define _BIT17  						0x00020000
#define _BIT18   						0x00040000
#define _BIT19   						0x00080000
#define _BIT20   						0x00100000
#define _BIT21   						0x00200000
#define _BIT22   						0x00400000
#define _BIT23   						0x00800000
#define _BIT24   						0x01000000
#define _BIT25   						0x02000000
#define _BIT26  						0x04000000
#define _BIT27  						0x08000000
#define _BIT28  						0x10000000
#define _BIT29  						0x20000000
#define _BIT30  						0x40000000
#define _BIT31  						0x80000000
#endif

#define HDMI_CONST					const
#define	RTD_XTAL 		27000
#define _AUDIO_128_TIMES        1
#define _AUDIO_256_TIMES        2
#define _AUDIO_MCK_32000        _AUDIO_256_TIMES
#define _AUDIO_MCK_44100        _AUDIO_256_TIMES
#define _AUDIO_MCK_48000        _AUDIO_256_TIMES
#define _AUDIO_MCK_88200        _AUDIO_256_TIMES
#define _AUDIO_MCK_96000        _AUDIO_256_TIMES
#define _AUDIO_MCK_176400       _AUDIO_128_TIMES
#define _AUDIO_MCK_192000       _AUDIO_128_TIMES
#if 0
typedef struct {
	int 	   freq;
	UINT8 coeff;
	UINT8 rate;
} HDMI_AUDIO_PLL_COEFF_T;

typedef struct {

	UINT8 N;
	UINT8 M;
	UINT8 O;
	UINT8 S;
	UINT8 S1;
	UINT32 D_HighByte;
	UINT32 D_LowByte;
	char *sample_rate;

} HDMI_AUDIO_PLL_PARAM_T;
#endif

typedef struct {
	
		UINT16 M_code;
		UINT16 N_code;
		UINT8 N_bypass;
		UINT8 MD_adj;
		UINT8 CK_LDOA;
		UINT8 CK_LDOD;
		UINT8 CK_CS;
		UINT8 CK_RS;
		UINT8 EQ_adj;
		UINT8 CDR_bias;
		UINT8 CDR_KP;
		UINT8 CDR_KP2;
		UINT8 CDR_KI;
		UINT8 CDR_KD;
		UINT8 EQ_gain;
		UINT8 EQ_bias;
		UINT8 CK_Icp;
		UINT8 PR;
	//	UINT8 reg_RESERVED_02;
		//UINT8 reg_RESERVED_05;
		//UINT8 reg_ADAPTIVE_EQUALIZER;
		//UINT8 reg_RESERVED_FA;
		char *band_name;
	
} HDMI_PHY_PARAM_T;

#endif

