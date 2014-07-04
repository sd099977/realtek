#ifndef IFD_DRIVER_H
#define IFD_DRIVER_H

#include "ifd_sirius.h"

#define _Tuner_MAX_NO 1
//=================================================================
//Define for IFD Driver
//=================================================================

#ifndef MHz
#define MHz 1000000
#endif
#ifndef kHz
#define kHz 1000
#endif

#define IFD_ENABLE  (1)
#define IFD_DISABLE (0)
#define CR_BPF_TABLE_NUM (11)
#define CR_BPF_TABLE_SIZE (41)
#define GP_BPF_TABLE_SIZE (34)
#define OUPUT_LPF_TABLE_SIZE (96)
#define EQ_TABLE_SIZE (32)
#define PGA_TABLE_SIZE (144)
#define IFD_FLASH_MAGIC_CODE					0x69666421
#define IFD_CRLOCK_THR_RATIO	0x10UL
#define IFD_FREQ_UNIT kHz*10
#define INPUT_FILTER_TABLE_SIZE (72)

//Initial Value
#define	IFD_AGC_KRF						0x400UL
#define	IFD_CR_OFFSET_SAT					0x0000A000UL
#define	IFD_CLAMP_MAX_THD				0x1fffUL
#define	IFD_CLAMP_MIN_THD				0x3500UL
#define	IFD_CLAMP_MID_THD_NEG			0x3a00UL
#define	IFD_CLAMP_MID_THD_POS			0x0100UL
#define	IFD_UNLOCK_MAX_DEC_CNT			0x20UL
#define	IFD_LOCK_MAX_DEC_CNT				0x20UL
#define	IFD_UNLOCK_MAX2_DEC_CNT			0x10UL
#define	IFD_LOCK_MAX2_DEC_CNT			0x10UL
#define	IFD_PEAK_DEC_CNT					0xdb0UL
#define	IFD_PEAK2_DEC_CNT					0xdb0UL
#define	IFD_LOOP1_AGC_LOCK_IN_THD		0x10UL
#define	IFD_LOOP1_AGC_LOCK_OUT_THD		0x18UL
#define	IFD_LOOP2_AGC_LOCK_IN_THD		0x10UL
#define	IFD_LOOP2_AGC_LOCK_OUT_THD		0x18UL
#define	IFD_AGC_2STEP_DGAIN_LOW_THD	0x7f00UL
#define	IFD_AGC_2STEP_DGAIN_HIGH_THD	0xfff0UL
#define	IFD_AGC_2STEP_PGA_STEP              	0x04UL
#define	IFD_VSmode1_Hstart_NTSC			0xadUL
#define	IFD_VSmode1_Hend_NTSC			0xbdUL
#define	IFD_VSmode1_Vstart_NTSC			0x0100UL //@@@
#define	IFD_VSmode1_Vend_NTSC			0x0150UL //@@@
#define	IFD_VSmode1_Hstart_PAL			0xb5UL
#define	IFD_VSmode1_Hend_PAL				0xc5UL
#define	IFD_VSmode1_Vstart_PAL			0x8080UL
#define	IFD_VSmode1_Vend_PAL				0x0993UL
#define	IFD_VSmode1_Hstart_SECAM			0xb2UL  
#define	IFD_VSmode1_Hend_SECAM			0xc2UL  
#define	IFD_VSmode1_Vstart_SECAM			0x8180UL//0x8080UL
#define	IFD_VSmode1_Vend_SECAM			0x0800UL//0x0993UL
#define	IFD_OUTPUTLPF_VSYNC_START_PAL	0x8200UL
#define	IFD_OUTPUTLPF_VSYNC_END_PAL		0x0E00UL
#define	IFD_OUTPUTLPF_VSYNC_START_NTSC	0x6c00UL
#define	IFD_OUTPUTLPF_VSYNC_END_NTSC	0x0200UL
#define	IFD_OUTPUTLPF_VSYNC_START_SECAM 0x8200UL
#define	IFD_OUTPUTLPF_VSYNC_END_SECAM	0x0E00UL
#define	IFD_CR_VSYNC_START_PAL	0x8200UL
#define	IFD_CR_VSYNC_END_PAL		0x0200UL
#define	IFD_CR_VSYNC_START_NTSC	0x6c00UL
#define	IFD_CR_VSYNC_END_NTSC	0x0200UL
#define	IFD_CR_VSYNC_START_SECAM 0x8200UL
#define	IFD_CR_VSYNC_END_SECAM	0x0200UL
#define   IFD_NONSTD_STABLE_CNTNUM 10
#define   IFD_NONSTD_DGAIN_200 0x36b
#define   IFD_NONSTD_DGAIN_50 0x4cf
#define   IFD_NONSTD_DGAIN_THR 0x10
#define   IFD_PRE_DISTORTION_RF_THD  400
#define   IFD_PRE_DISTORTION_PGA_THD	120
#define   IFD_PRE_DISTORTION_DGAIN_THD      5000
#define	IFD_CR_FREQ_ERROR_AVG_VINTERVAL 0x10
#define	IFD_CR_FREQ_ERROR_AVG_INTERVAL 0x200
#define	IFD_CR_FREQ_ERROR_AVG_LENGTH 0x2
#define	IFD_CR_FREQ_ERROR_AVG_LINEBASE 0x0
#define	IFD_CR_PHASE_ERROR_AVG_INTERVAL 0x200
#define	IFD_CR_PHASE_ERROR_AVG_LENGTH 0x2
#define	IFD_CR_PHASE_ERROR_AVG_LINEBASE 0x0




typedef enum _TUNER_AGCTYPE_SEL {
        TUNER_NONE_IC_RFAGC = 0,
        TUNER_RFAGC_IC_IFAGC,
        TUNER_NONE_IC_RFAGC_IFAGC,
}TUNER_AGCTYPE_SEL;

typedef enum _TUNER_TYPE_SEL {
	TUNER_NORMAL = 0,
	TUNER_SILICON_NORMAL,
	TUNER_LOW_IF,
	TUNER_ZERO_IF,
}TUNER_TYPE_SEL;

typedef enum {
	TUNER_IF_TYPE_NEG=0,
	TUNER_IF_TYPE_POS=1,
} TUNER_IF_TYPE;

typedef enum _TUNER_AGCPOLARITY_SEL {
        TUNER_RF_POS_IF_POS = 0,
        TUNER_RF_POS_IF_NONE,
        TUNER_RF_POS_IF_NEG,
        TUNER_RF_NONE_IF_POS,
        TUNER_RF_NONE_IF_NONE,
        TUNER_RF_NONE_IF_NEG,
        TUNER_RF_NEG_IF_POS,
        TUNER_RF_NEG_IF_NONE,
        TUNER_RF_NEG_IF_NEG,
}TUNER_AGCPOLARITY_SEL;

typedef enum  {
	IFD_AGC_DOUBLE_NOIFAMP_PGA=0,
	IFD_AGC_DOUBLE_IFAMP_NOPGA,
	IFD_AGC_DOUBLE_IFAMP_FIXPGA,
	IFD_AGC_2STEP_NOIFAMP_PGA,
	IFD_AGC_2STEP_IFAMP_NOPGA,
}IFD_MODE_AGC_PGA_CONFIG;

typedef enum  {
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N7DB=-8,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N6DB=-7,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N5DB=-6,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N4DB=-5,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N3DB=-4,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N2DB=-3,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_N1DB=-2,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_2P5DB=-1,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_6DB=0,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_7DB=1,
	IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_8DB=2,
	//Add by yourself
}IFD_MODE_AGC_PGA_FIXGAIN_LEVEL;

typedef enum  {
    IFD_MODE_CH_SCAN=0,
    IFD_MODE_CH_SET,
}IFD_MODE_OPERATE;

typedef enum  {
    IFD_CR_STATE_SET_TUNER=0,
    IFD_CR_STATE_CHECK,
    IFD_CR_FLOW_STATE_ENABLE_BY_FACTORYMODE,
    IFD_CR_FLOW_STATE_DISABLE_BY_FACTORYMODE,
}IFD_CR_FLOW_STATE;

typedef enum  {
	IFD_CLAMP_RESET_NEG = 0  ,
	IFD_CLAMP_RESET_POS,
}IFD_CLAMP_RESET_POLARITY;

typedef enum  {
	IFD_CR_LOCK_THD_150K = 1500,
	IFD_CR_LOCK_THD_300K = 3000,
	IFD_CR_LOCK_THD_500K = 5000,
}IFD_CR_LOCK_THD;

typedef enum  {
	IFD_CR_LOCK_OFFSET_THD_150K = 0xb6,
	IFD_CR_LOCK_OFFSET_THD_300K = 0x16c,
	IFD_CR_LOCK_OFFSET_THD_500K = 0x25e,
}IFD_CR_LOCK_OFFSET_THD;

//=================================================================
//Input Filter Table
//=================================================================
typedef struct {
	bool		InputFilter_En;
	UINT16	InputFilter_Table[INPUT_FILTER_TABLE_SIZE];
} StructInputFltCoef;
//IFD
#define IFD_INPUTFILTER_TABLE_MNB					\
       {  \
              0x1FFE, 0x0003, 0x0002, 0x1FF8, 0x0007,   \
              0x0004, 0x1FF3, 0x0009, 0x0003, 0x1FFA,   \
              0x0001, 0x1FFF, 0x000C, 0x1FF0, 0x1FFE,   \
              0x0017, 0x1FEA, 0x0000, 0x000B, 0x1FFF,   \
              0x1FFE, 0x1FEC, 0x0022, 0x1FF8, 0x1FDD,   \
              0x002A, 0x1FF7, 0x1FF4, 0x1FFD, 0x0009,   \
              0x001D, 0x1FBF, 0x0021, 0x002A, 0x1FBC,   \
              0x0018, 0x0009, 0x0010, 0x1FE1, 0x1FDE,   \
              0x0070, 0x1FAF, 0x1FDA, 0x0062, 0x1FD3,   \
              0x1FFD, 0x1FD2, 0x0053, 0x0017, 0x1F4C,   \
              0x00AC, 0x000B, 0x1F7D, 0x0042, 0x0001,   \
              0x0069, 0x1F2F, 0x0026, 0x0128, 0x1E90,   \
              0x0047, 0x00B4, 0x1FAF, 0x1FD8, 0x1EF4,   \
              0x02AF, 0x1E8E, 0x1CFE, 0x0601, 0x1CF3,   \
              0x1C2D, 0x0773,   \
       }//6MHz
#define IFD_INPUTFILTER_TABLE_DKL				\
       {  \
              0x0001, 0x0000, 0x0002, 0x1FFB, 0x0006,   \
              0x0001, 0x1FF8, 0x0007, 0x1FFF, 0x0002,   \
              0x1FF7, 0x0009, 0x0005, 0x1FEF, 0x000C,   \
              0x1FFF, 0x0003, 0x1FF2, 0x000B, 0x000E,   \
              0x1FE2, 0x0012, 0x0001, 0x0005, 0x1FE9,   \
              0x000A, 0x001F, 0x1FCF, 0x0016, 0x0005,   \
              0x000B, 0x1FE0, 0x0002, 0x003B, 0x1FB8,   \
              0x0016, 0x000B, 0x0014, 0x1FD5, 0x1FEF,   \
              0x0066, 0x1F9E, 0x000F, 0x0012, 0x0024,   \
              0x1FCC, 0x1FC8, 0x00A7, 0x1F80, 0x1FFE,   \
              0x001A, 0x003F, 0x1FC9, 0x1F7B, 0x0111,   \
              0x1F5E, 0x1FDA, 0x0021, 0x0071, 0x1FD9,   \
              0x1ECC, 0x01EB, 0x1F26, 0x1F7D, 0x0026,   \
              0x00FD, 0x003B, 0x1BDF, 0x0635, 0x1DBF,   \
              0x1A9E, 0x094C,   \
       }//8MHz
#define IFD_INPUTFILTER_TABLE_G				\
       {  \
              0x1FFE, 0x0002, 0x0002, 0x1FF9, 0x0007,   \
              0x0002, 0x1FF7, 0x0007, 0x0000, 0x0000,   \
              0x1FFA, 0x0003, 0x000C, 0x1FEC, 0x0009,   \
              0x0008, 0x1FF6, 0x0000, 0x1FFD, 0x0016,   \
              0x1FE7, 0x1FFD, 0x001F, 0x1FE7, 0x0002,   \
              0x1FFD, 0x0017, 0x1FF0, 0x1FE1, 0x003D,   \
              0x1FE0, 0x1FF1, 0x0010, 0x000A, 0x0006,   \
              0x1FBF, 0x004F, 0x1FF9, 0x1FBF, 0x0035,   \
              0x1FFC, 0x0016, 0x1FAD, 0x003E, 0x003F,   \
              0x1F70, 0x0051, 0x000F, 0x0001, 0x1FBE,   \
              0x0000, 0x00AF, 0x1F21, 0x0033, 0x0076,   \
              0x1FB1, 0x1FED, 0x1FA6, 0x0133, 0x1F04,   \
              0x1F7D, 0x0188, 0x1F1B, 0x1FF9, 0x1F55,   \
              0x01E7, 0x1F77, 0x1C4C, 0x0638, 0x1D48,   \
              0x1B6E, 0x085A,   \
       }//7MHz
// VD
#ifdef CONFIG_Pacific_prime
#define IFD_INPUT_FILTER_COEF_VD_55M     \
       {  \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000,   \
       }
#define IFD_INPUT_FILTER_COEF_VD_60M     \
       {  \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000,   \
       }
#define IFD_INPUT_FILTER_COEF_VD_65M     \
       {  \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000,   \
       }
#define IFD_INPUT_FILTER_COEF_VD_70M     \
       {  \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000,   \
       }
#define IFD_INPUT_FILTER_COEF_VD_75M     \
       {  \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   \
       0x0000, 0x0000,   \
       }
#endif
//=================================================================
//CRBPF Table
//=================================================================
typedef enum  {
	IFD_IF_FREQ_33P9M = 339000,
	IFD_IF_FREQ_36P88M = 368800,
	IFD_IF_FREQ_38M = 380000,
	IFD_IF_FREQ_38P9M = 389000,
	IFD_IF_FREQ_32P2M = 322000,
	IFD_IF_FREQ_33P1M = 331000,
	IFD_IF_FREQ_45P75M = 457500,
	IFD_IF_FREQ_1P25M = 12500,
	IFD_IF_FREQ_2P2M = 22000,
	IFD_IF_FREQ_2P25M = 22500,
	IFD_IF_FREQ_3P52M = 35200,
	IFD_IF_FREQ_4M = 40000,
	IFD_IF_FREQ_5M = 50000,
	IFD_IF_FREQ_5P4M = 54000,
	IFD_IF_FREQ_5P5M = 55000,
	IFD_IF_FREQ_5P6M = 56000,
	IFD_IF_FREQ_5P75M = 57500,
	IFD_IF_FREQ_5P8M = 58000,
	IFD_IF_FREQ_5P82M = 58200,
	IFD_IF_FREQ_6P4M = 64000,
	IFD_IF_FREQ_6P6M = 66000,
	IFD_IF_FREQ_6P75M = 67500,
	IFD_IF_FREQ_6P85M = 68500,
	IFD_IF_FREQ_7P02M = 70200,
	IFD_IF_FREQ_7P25M = 72500,
	IFD_IF_FREQ_7P3M = 73000,
	IFD_IF_FREQ_7P45M = 74500,
	IFD_IF_FREQ_7P5M = 75000,
	IFD_IF_FREQ_7P75M = 77500,
	IFD_IF_FREQ_7P8M = 78000,
	IFD_IF_FREQ_7P82M = 78200,
	IFD_IF_FREQ_8P2M = 82000,
}IFD_IF_FREQ;

//NEG
#define IFD_CRBPF_NEG_5M_N0P5M					\
	{										\
     		0x0028, 0x0008, 0xFFE0, 0xFFB8, 0xFFA8, 	\
     		0xFFC8, 0x0010, 0x0078, 0x00C8, 0x00D8, 	\
     		0x0088, 0xFFD8, 0xFF00, 0xFE50, 0xFE30, 	\
     		0xFEC0, 0x0008, 0x0190, 0x02D8, 0x0348, 	\
     		0x0280, 0x00A0, 0xFE28, 0xFC00, 0xFAF8, 	\
     		0xFBB0, 0xFE10, 0x0170, 0x04A8, 0x0690, 	\
     		0x0648, 0x03C8, 0xFFC0, 0xFB90, 0xF8A8, 	\
     		0xF828, 0xFA50, 0xFE80, 0x0348, 0x0708, 	\
     		0x0870, 								\
	}
#define IFD_CRBPF_NEG_5P4M_N0P9M 				\
	{										\
     		0x0010, 0x0028, 0x0020, 0x0000, 0xFFC8,	\
     		0xFF90, 0xFF80, 0xFFB0, 0x0030, 0x00C8, 	\
     		0x0138, 0x0130, 0x0088, 0xFF68, 0xFE38, 	\
     		0xFD88, 0xFDC8, 0xFF20, 0x0128, 0x0328, 	\
    		0x0428, 0x0390, 0x0150, 0xFE28, 0xFB40, 	\
     		0xF9F0, 0xFAF0, 0xFE28, 0x0278, 0x0640, 	\
     		0x07E0, 0x0678, 0x0260, 0xFD18, 0xF8A0, 	\
     		0xF6D8, 0xF888, 0xFD30, 0x0308, 0x07C8, 	\
     		0x09A0, 								\
	}
#define IFD_CRBPF_NEG_5P5M_N1P0M 				\
	{  \
		   0x0030, 0x0050, 0x0048, 0x0000, 0xFF88,	 \
		   0xFF10, 0xFEE8, 0xFF50, 0x0048, 0x0188,	 \
		   0x0280, 0x0290, 0x0160, 0xFF20, 0xFC90,	 \
		   0xFAE8, 0xFB20, 0xFDA8, 0x01D8, 0x0628,	 \
		   0x08A0, 0x07D0, 0x0378, 0xFCE8, 0xF698,	 \
		   0xF360, 0xF4F8, 0xFB60, 0x0468, 0x0C98,	 \
		   0x1068, 0x0DE0, 0x0598, 0xFA80, 0xF0F0,	 \
		   0xECE8, 0xF038, 0xF9D8, 0x0620, 0x1030,	 \
		   0x1410,	 \
	}


#define IFD_CRBPF_NEG_5P6M_N1P1M 				\
	{ 										\
		0xFFE0, 0x0000, 0x0028, 0x0040, 0x0030,  \
		0xFFF0, 0xFF98, 0xFF60, 0xFF68, 0xFFD8,  \
		0x0088, 0x0130, 0x0168, 0x00E8, 0xFFC8,  \
		0xFE78, 0xFD90, 0xFDA8, 0xFEF8, 0x0108,  \
		0x0310, 0x0400, 0x0338, 0x00D0, 0xFDA8,  \
		0xFB18, 0xFA70, 0xFC38, 0xFFE0, 0x0400,  \
		0x06B8, 0x06B8, 0x03D0, 0xFF08, 0xFA68,  \
		0xF7F8, 0xF8D8, 0xFCC8, 0x0230, 0x06C0,  \
		0x0888,                                                    \
	 }
#define IFD_CRBPF_NEG_5P75M_N1P25M                          \
    {                                       \
		0xFFEE,	0x001E,	0x0023,	0x001C,	0xFFFC,	 \
		0xFFC8,	0xFF99,	0xFF90,	0xFFC9,	0x003E,	 \
		0x00C8,	0x011D,	0x00FA,	0x0045,	0xFF2C,	 \
		0xFE22,	0xFDB6,	0xFE49,	0xFFDA,	0x01E2,	 \
		0x0382,	0x03DD,	0x0283,	0xFFC2,	0xFCA0,	 \
		0xFA7A,	0xFA72,	0xFCD8,	0x00ED,	0x0516,	 \
		0x0783,	0x06FA,	0x0372,	0xFE34,	0xF95E,	 \
		0xF704,	0xF844,	0xFCBC,	0x02A9,	0x079C,	 \
		0x0987,	                                 \
	}

#define IFD_CRBPF_NEG_5P8M_N1P3M					\
 	{										\
		0xFFE3, 0xFFF5, 0x0018, 0x003B,		\
		0x0044, 0x001E, 0xFFCC, 0xFF74,		\
		0xFF4E, 0xFF87, 0x0023, 0x00E7,		\
		0x016E, 0x0153, 0x0073, 0xFF11,		\
		0xFDCB, 0xFD57, 0xFE29, 0x001C,		\
		0x026E, 0x0403, 0x03EA, 0x01E3,		\
		0xFE9E, 0xFB81, 0xFA17, 0xFB46,		\
		0xFECF, 0x0348, 0x06AF, 0x0756,		\
		0x04B4, 0xFFC3, 0xFAA0, 0xF7A0, 		\
		0xF838, 0xFC45, 0x0211, 0x070E,		\
		0x0902,								\
	}
#define IFD_CRBPF_NEG_5P82M_N1P32M				\
	{										\
		0xFFE2, 0xFFF3, 0x0016, 0x003C,		\
		0x0049, 0x0025, 0xFFD2, 0xFF74,		\
		0xFF44, 0xFF78, 0x0014, 0x00E2,		\
		0x0178, 0x016B, 0x0090, 0xFF23,		\
		0xFDC7, 0xFD3B, 0xFDFE, 0xFFF7,		\
		0x0262, 0x0419, 0x041B, 0x021A,		\
		0xFEBF, 0xFB7B, 0xF9EA, 0xFB07,		\
		0xFE9B, 0x033A, 0x06D0, 0x0794,		\
		0x04F1, 0xFFE0, 0xFA8F, 0xF769,		\
		0xF7F8, 0xFC1D, 0x0216, 0x073D,		\
		0x0943,                        				\
	}
#define IFD_CRBPF_NEG_6P2M_N1P7M							\
{																							\
		0xFFEB,	0x0000,	0x001E,	0x004A,	0x0071,		\
		0x0073,	0x003D,	0xFFCF,	0xFF4A,	0xFEE8,		\
		0xFEDF,	0xFF4A,	0x000E,	0x00E3,	0x0173,		\
		0x0184,	0x0116,	0x0066,	0xFFC7,	0xFF76,		\
		0xFF6F,	0xFF70,	0xFF2C,	0xFE89,	0xFDCD,		\
		0xFD90,	0xFE6E,	0x0096,	0x038B,	0x0623,		\
		0x06FC,	0x0527,	0x00C2,	0xFB24,	0xF674,		\
		0xF4CA,	0xF735,	0xFD28,	0x0490,	0x0A9E,		\
		0x0CF1,																		\
	}
#define IFD_CRBPF_NEG_6P3M_N1P8M							\
{																		\
		0xFFDB,	0xFFDC,	0xFFF1,	0x002C,	0x0080,	\
		0x00C4,	0x00C7,	0x0064,	0xFFA5,	0xFECB,	\
		0xFE37,	0xFE45,	0xFF0E,	0x0059,	0x01A5,	\
		0x0268,	0x0252,	0x0177,	0x0042,	0xFF3A,	\
		0xFEB0,	0xFE98,	0xFE9A,	0xFE60,	0xFDEA,	\
		0xFDAA,	0xFE51,	0x0051,	0x0366,	0x0672,	\
		0x07D9,	0x064F,	0x01A8,	0xFB37,	0xF579,	\
		0xF30F,	0xF579,	0xFC41,	0x04FA,	0x0C37,	\
		0x0F05,																	\
		}
#define IFD_CRBPF_NEG_6P4M_N0P9M						\
	{  \
              0x0038, 0x0008, 0xFFC8, 0xFF90, 0xFFA8,   \
              0x0018, 0x00B0, 0x0100, 0x00B8, 0xFFC0,   \
              0xFE98, 0xFE08, 0xFE98, 0x0050, 0x0258,   \
              0x0368, 0x0290, 0xFFE8, 0xFCA8, 0xFAC8,   \
              0xFBB8, 0xFF70, 0x0420, 0x0728, 0x0670,   \
              0x01D8, 0xFB90, 0xF710, 0xF730, 0xFC50,   \
              0x0400, 0x0A18, 0x0B00, 0x05E0, 0xFD38,   \
              0xF5A8, 0xF378, 0xF800, 0x0100, 0x0998,   \
              0x0D18,   \
       }
#define IFD_CRBPF_NEG_6P6M_N1P1M						\
	{  \
		   0xFFE0, 0x0038, 0x0058, 0x0010, 0xFF88,	 \
		   0xFF28, 0xFF60, 0x0050, 0x0168, 0x01D8,	 \
		   0x00F0, 0xFEF0, 0xFD08, 0xFCC0, 0xFEC8,	 \
		   0x0258, 0x0538, 0x0520, 0x0168, 0xFBD8,	 \
		   0xF7F8, 0xF8C0, 0xFE90, 0x0650, 0x0B30,	 \
		   0x0970, 0x0158, 0xF758, 0xF1B8, 0xF490,	 \
		   0xFEE8, 0x0AD8, 0x10F0, 0x0CF0, 0x00B8,	 \
		   0xF370, 0xED48, 0xF250, 0xFFC0, 0x0D90,	 \
		   0x1358,	 \
	}
#define IFD_CRBPF_NEG_6P75M_N1P25M							\
	{  \
		   0xFFF8, 0x0048, 0x0048, 0xFFE8, 0xFF60,	 \
		   0xFF20, 0xFF98, 0x00B0, 0x01C0, 0x01D0,	 \
		   0x0078, 0xFE38, 0xFC80, 0xFCD0, 0xFF90,	 \
		   0x0370, 0x0600, 0x0500, 0x0058, 0xFA60,	 \
		   0xF6E8, 0xF8D0, 0xFFD0, 0x0828, 0x0C88,	 \
		   0x0988, 0x0008, 0xF550, 0xF008, 0xF430,	 \
		   0x0010, 0x0CF0, 0x12D8, 0x0DB0, 0xFFE8,	 \
		   0xF180, 0xEB30, 0xF120, 0x0008, 0x0F30,	 \
		   0x1580,	 \
	}

#define IFD_CRBPF_NEG_6P85M_N1P35M							\
	{  \
		   0xFFC8, 0x0038, 0x0070, 0x0038, 0xFFA0,	 \
		   0xFF08, 0xFF18, 0x0008, 0x0160, 0x0228,	 \
		   0x0178, 0xFF58, 0xFCF8, 0xFC20, 0xFDF8,	 \
		   0x01E0, 0x0578, 0x0610, 0x0278, 0xFC58,	 \
		   0xF770, 0xF778, 0xFD50, 0x05F8, 0x0C08,	 \
		   0x0B00, 0x0298, 0xF770, 0xF088, 0xF2E0,	 \
		   0xFDD0, 0x0B18, 0x1260, 0x0E98, 0x0170,	 \
		   0xF2C0, 0xEBA8, 0xF0E0, 0xFF80, 0x0EA8,	 \
		   0x1508,	 \
	}

#define IFD_CRBPF_NEG_7P02M_N0P52M			\
      {  \
		0xFFFB,	0xFFF5,	0xFFEA,	0xFFDF,	0xFFD5,	\
		0xFFD3,	0xFFDD,	0xFFF8,	0x0026,	0x0062,	\
		0x00A0,	0x00D1,	0x00E1,	0x00C1,	0x0066,	\
		0xFFD5,	0xFF21,	0xFE6D,	0xFDE4,	0xFDB2,	\
		0xFDF9,	0xFEC1,	0xFFF9,	0x016F,	0x02D8,	\
		0x03E3,	0x0446,	0x03D1,	0x0282,	0x0088,	\
		0xFE3C,	0xFC13,	0xFA87,	0xF9F6,	0xFA91,	\
		0xFC4A,	0xFED2,	0x01AE,	0x0449,	0x061B,	\
		0x06C2,	                                \
       }
#define IFD_CRBPF_NEG_7P25M_N0P75M							\
       {  \
              0xFFE8, 0xFFE8, 0x0010, 0x0048, 0x0048,   \
              0x0000, 0xFF90, 0xFF50, 0xFF98, 0x0068,   \
              0x0130, 0x0138, 0x0040, 0xFEC0, 0xFDC8,   \
              0xFE58, 0x0060, 0x02A0, 0x0360, 0x01B0,   \
              0xFE60, 0xFBA0, 0xFBA8, 0xFEE8, 0x0378,   \
              0x0630, 0x04C0, 0xFFC0, 0xFA58, 0xF860,   \
              0xFBA8, 0x0240, 0x07C8, 0x0840, 0x0310,   \
              0xFB80, 0xF6B8, 0xF818, 0xFEE8, 0x0688,   \
              0x09D8,   \
       }
#define IFD_CRBPF_NEG_7P3M_N0P8M                          \
    {                                       \
		0xFFE6,	0x000B,	0x0022,	0x0029,	0x000B,	\
		0xFFCE,	0xFF9B,	0xFFAB,	0x0012,	0x009B,	\
		0x00DA,	0x007D,	0xFF93,	0xFEAC,	0xFE87,	\
		0xFF7D,	0x0124,	0x0260,	0x0224,	0x003F,	\
		0xFDBC,	0xFC57,	0xFD52,	0x006A,	0x03BF,	\
		0x04F7,	0x02E1,	0xFE80,	0xFA9C,	0xF9FB,	\
		0xFD66,	0x02E8,	0x06E9,	0x0692,	0x01D2,	\
		0xFB9A,	0xF803,	0xF98C,	0xFF59,	0x05AC,	\
		0x0860,	                                \
    }
#define IFD_CRBPF_NEG_7P45M_N1P45M							\
	{  \
		   0x0018, 0xFFB8, 0xFFB8, 0x0028, 0x00B0,	 \
		   0x00C0, 0xFFF8, 0xFED0, 0xFE50, 0xFF38,	 \
		   0x0148, 0x02F8, 0x0290, 0xFFC0, 0xFC40,	 \
		   0xFAE8, 0xFD80, 0x02E0, 0x0728, 0x06A0,	 \
		   0x00A0, 0xF8F0, 0xF560, 0xF988, 0x0358,	 \
		   0x0C18, 0x0CC8, 0x03E0, 0xF700, 0xEF80,	 \
		   0xF390, 0x0130, 0x0EF8, 0x12C0, 0x0918,	 \
		   0xF860, 0xEC70, 0xEE28, 0xFCA8, 0x0DC8,	 \
		   0x1548,	 \
	}
#define IFD_CRBPF_NEG_7P5M_N1P0M							\
       {  \
              0x0018, 0xFFE0, 0xFFD0, 0xFFF8, 0x0048,   \
              0x0068, 0x0030, 0xFFA0, 0xFF30, 0xFF60,   \
              0x0040, 0x0138, 0x0168, 0x0060, 0xFEB0,   \
              0xFDA8, 0xFE60, 0x00A0, 0x02F0, 0x0350,   \
              0x0108, 0xFD80, 0xFB50, 0xFC80, 0x00A8,   \
              0x04E8, 0x05F0, 0x0280, 0xFCB8, 0xF8E0,   \
              0xFA10, 0xFFD8, 0x0630, 0x0858, 0x0470,   \
              0xFD10, 0xF788, 0xF808, 0xFE58, 0x05F8,   \
              0x0958,   \
       }
#define IFD_CRBPF_NEG_7P75M_N1P25M							\
	{  \
		   0x0040, 0x0000, 0xFF98, 0xFF88, 0x0000,	 \
		   0x00C0, 0x0110, 0x0060, 0xFEF0, 0xFE00,	 \
		   0xFEB0, 0x00E8, 0x0308, 0x0300, 0x0028,	 \
		   0xFC58, 0xFAD8, 0xFD90, 0x0310, 0x0718,	 \
		   0x05D0, 0xFF50, 0xF838, 0xF680, 0xFC78,	 \
		   0x0640, 0x0C30, 0x08E0, 0xFDF8, 0xF398,	 \
		   0xF238, 0xFBC0, 0x0968, 0x1080, 0x0B00,	 \
		   0xFCA0, 0xF048, 0xEFC8, 0xFBC8, 0x0B40,	 \
		   0x1230,	 \
	}

#define IFD_CRBPF_NEG_7P8M_N1P3M							\
     	{										\
		0x0018, 0xFFFC, 0xFFD7, 0xFFD2,		\
		0x0006, 0x0054, 0x006E, 0x001B,		\
		0xFF81, 0xFF24, 0xFF7F, 0x007E,		\
		0x0164, 0x0146, 0xFFED, 0xFE3B,		\
		0xFDA9, 0xFF09, 0x019D, 0x0363,		\
		0x029D, 0xFF6F, 0xFC20, 0xFB7E,		\
		0xFE86, 0x0340, 0x05F9, 0x042B,		\
		0xFEC2, 0xF9C1, 0xF943, 0xFE1A, 		\
		0x04D6, 0x083B, 0x0560, 0xFE2D,		\
		0xF815, 0xF7E6, 0xFDF1, 0x05AA,		\
		0x0922,								\
	}
#define IFD_CRBPF_NEG_7P82M_N1P32M					\
	{										\
		0x0018, 0xFFFE, 0xFFD7, 0xFFCF,		\
		0x0002, 0x0052, 0x0073, 0x0023,		\
		0xFF86, 0xFF1F, 0xFF71, 0x0072,		\
		0x0166, 0x0158, 0x0003, 0xFE41,		\
		0xFD96, 0xFEE9, 0x018A, 0x036F,		\
		0x02C2, 0xFF90, 0xFC21, 0xFB5A,		\
		0xFE5A, 0x0330, 0x0614, 0x045C,		\
		0xFEE1, 0xF9B3, 0xF914, 0xFDF1,		\
		0x04D6, 0x0863, 0x058E, 0xFE39,		\
		0xF7F5, 0xF7B9, 0xFDDF, 0x05C3,		\
		0x094F,                        				\
	}
#define IFD_CRBPF_NEG_8P2M_N1P7M                          \
    {                                       \
		0xFFF8,	0x0034,	0x0000,	0xFFD1,	0xFFBC,	\
		0xFFEC,	0x0051,	0x008E,	0x004A,	0xFF97,	\
		0xFF06,	0xFF45,	0x005A,	0x0175,	0x0178,	\
		0x0009,	0xFE29,	0xFD8F,	0xFF1F,	0x01E1,	\
		0x037C,	0x0233,	0xFEA7,	0xFBB4,	0xFC24,	\
		0x001A,	0x0489,	0x0589,	0x01CB,	0xFC14,	\
		0xF935,	0xFBF0,	0x0260,	0x073D,	0x063E,	\
		0xFFEA,	0xF965,	0xF82F,	0xFD76,	0x04F1,	\
		0x0865,	                                \
}
#define IFD_CRBPF_NEG_21P6M_N15P1M				\
	{									\
        	0x7FAA, 0x00F6, 0x7EE3, 0x009A,	\
 		0x004B, 0x7F08, 0x00FF, 0x7F85,	\
 		0x7FFF, 0x7FF3, 0x0095, 0x7F1C,	\
 		0x003C, 0x0166, 0x7CFA, 0x033E,	\
 		0x7E9C, 0x7E41, 0x0444, 0x7B82,	\
 		0x0249, 0x00B9, 0x7D9C, 0x01D5,	\
 		0x7FC0, 0x7FFB, 0x7DB6, 0x05BF,	\
 		0x7939, 0x0267, 0x06C4, 0x7046,	\
 		0x11C0, 0x76E6, 0x7890, 0x171B,	\
 		0x63EA, 0x11DB, 0x0338, 0x682B,	\
 		0x2056,							\
	}
#define IFD_CRBPF_NEG_22P5M_N16M				\
	{									\
		0x0000,	0x0000,	0x0057,	0x00B8,	\
		0x0027,	0x7FC6,	0x7FD6,	0x00B7,	\
		0x7EEC,	0x00F2,	0x7FB8,	0x7F6D,	\
		0x011A,	0x7F03,	0x006D,	0x0004,	\
		0x0024,	0x7F3B,	0x012D,	0x7F64,	\
		0x7F04,	0x02BE,	0x7C9A,	0x024E,	\
		0x7FF5,	0x7E1F,	0x0233,	0x7EFA,	\
		0x7FE7,	0x7F6B,	0x0353,	0x79D2,	\
		0x060E,	0x7EE4,	0x78B5,	0x0EAD,	\
		0x7009,	0x08EB,	0x03E2,	0x6FF4,	\
		0x1505,							\
	}							

//POS 
#define IFD_CRBPF_POS_1P25M_N7P75M				\
       {  \
              0xFFD0, 0xFFA0, 0xFF58, 0xFF00, 0xFEA0,   \
              0xFE48, 0xFE00, 0xFDD8, 0xFDE0, 0xFE20,   \
              0xFEA8, 0xFF70, 0x0078, 0x01A8, 0x02E0,   \
              0x0400, 0x04E0, 0x0558, 0x0548, 0x0490,   \
              0x0338, 0x0148, 0xFED8, 0xFC28, 0xF978,   \
              0xF720, 0xF578, 0xF4D8, 0xF588, 0xF7B8,   \
              0xFB80, 0x00D0, 0x0780, 0x0F30, 0x1778,   \
              0x1FD0, 0x27A8, 0x2E70, 0x33B0, 0x3700,   \
              0x3820,   \
       }

#define IFD_CRBPF_POS_2P2M_N8P7M                          \
    {                                       \
    		0xFFFA,	0xFFF3,	0xFFE7,	0xFFD6,	0xFFC0,	\
		0xFFA5,	0xFF8A,	0xFF71,	0xFF62,	0xFF62,	\
		0xFF79,	0xFFAB,	0xFFFC,	0x006D,	0x00F7,	\
		0x0191,	0x022D,	0x02B7,	0x031B,	0x0342,	\
		0x031D,	0x029D,	0x01BF,	0x008B,	0xFF14,	\
		0xFD76,	0xFBD7,	0xFA64,	0xF946,	0xF8A6,	\
		0xF8A2,	0xF948,	0xFA96,	0xFC78,	0xFECA,	\
		0x0157,	0x03E4,	0x0632,	0x0809,	0x0937,	\
		0x099F,	                                \
	}
#define IFD_CRBPF_POS_2P25M_N8P75M				\
       {  \
              0x0000, 0xFFF8, 0xFFF0, 0xFFD8, 0xFFB8,   \
              0xFF90, 0xFF58, 0xFF18, 0xFED8, 0xFEA0,   \
              0xFE88, 0xFE90, 0xFED8, 0xFF60, 0x0038,   \
              0x0150, 0x02A0, 0x0400, 0x0550, 0x0658,   \
              0x06E0, 0x06C0, 0x05D0, 0x0410, 0x0180,   \
              0xFE50, 0xFAD0, 0xF758, 0xF450, 0xF220,   \
              0xF128, 0xF198, 0xF390, 0xF6F8, 0xFB88,   \
              0x00C8, 0x0638, 0x0B40, 0x0F50, 0x11F8,   \
              0x12E0,   \
       }
#define IFD_CRBPF_POS_8P25M_N12P75M							\
	{										\
		0x0003, 0x0001, 0xFFF2, 0xFFD8,		\
		0xFFC8, 0xFFE4, 0x0032, 0x007F,		\
		0x0074, 0xFFEB, 0xFF32, 0xFEF9,		\
		0xFFB3, 0x0104, 0x01CA, 0x010D,		\
		0xFF0A, 0xFD62, 0xFDD3, 0x007B,		\
		0x034F, 0x0399, 0x0086, 0xFC5E,		\
		0xFAE4, 0xFDF4, 0x0363, 0x0670,		\
		0x03F2, 0xFD8B, 0xF8B5, 0xFA0B,		\
		0x00E2, 0x076F, 0x07BE, 0x0128,		\
		0xF93E, 0xF707, 0xFCA8, 0x0552,		\
		0x096A,								\
	}
#define IFD_CRBPF_POS_3P52M_N8P02M							\
	{										\
		0xFFF9,	0xFFF1,	0xFFE3,	0xFFD4,	0xFFC7,	\
		0xFFC4,	0xFFD1,	0xFFF6,	0x0033,	0x0082,	\
		0x00D5,	0x0116,	0x012C,	0x0101,	0x0088,	\
		0xFFC7,	0xFED7,	0xFDE7,	0xFD30,	0xFCEE,	\
		0xFD4C,	0xFE57,	0xFFF7,	0x01E9,	0x03CB,	\
		0x052F,	0x05B2,	0x0516,	0x0358,	0x00B5,	\
		0xFDA5,	0xFAC4,	0xF8B4,	0xF7F3,	0xF8C2,	\
		0xFB0D,	0xFE6E,	0x023D,	0x05B7,	0x0824,	\
		0x0903,																	\
	}
#define IFD_CRBPF_POS_15P1M_N21P6M							\
	{										\
		0x000D, 0x000A, 0xFFE0, 0xFFEC,		\
		0x003F, 0x0011, 0xFF91, 0x000C,		\
		0x00A8, 0xFFAD, 0xFF2C, 0x00CC,		\
		0x00D6, 0xFE91, 0xFF76, 0x021E,		\
		0xFFD4, 0xFD5D, 0x014E, 0x02BE,		\
		0xFD43, 0xFDCE, 0x0431, 0x00E0,		\
		0xFABB, 0x0127, 0x0593, 0xFC69,		\
		0xFB34, 0x05F3, 0x02E0, 0xF857,		\
		0xFFFB, 0x0839, 0xFCB9, 0xF8A6,		\
		0x065A, 0x0517, 0xF778, 0xFE2E,		\
		0x0951,								\
	}
#define  IFD_CRBPF_POS_16M_N22P5							\
	{										\
		0xFFEF, 0xFFE2, 0x0015, 0x002D,		\
		0xFFC9, 0xFFD2, 0x0073, 0x0006,		\
		0xFF4E, 0x0062, 0x00C5, 0xFEFB,		\
		0xFF91, 0x01A9, 0xFF8A, 0xFE1C,		\
		0x01C9, 0x014B, 0xFCF2, 0x0050,		\
		0x038C, 0xFD68, 0xFD60, 0x04B3,		\
		0x0027, 0xFA78, 0x033E, 0x0447,		\
		0xF9BC, 0xFF15, 0x0776, 0xFC77,		\
		0xFA13, 0x075E, 0x01DC, 0xF721,		\
		0x035D, 0x072E, 0xF84B, 0xFD40, 		\
		0x0964,								\
	}

//=================================================================
//GroupDelay Table
//=================================================================

typedef struct {
	UINT16	GroupDelay_Table[GP_BPF_TABLE_SIZE];
} StructGroupDelay;

#define IFD_GROUPDELAY_TABLE_BG_CURVE_B  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}                                   
#define IFD_GROUPDELAY_TABLE_BG_CURVE_A  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_OIRT  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_SWEDEN  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_NEWZEALAND  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_AUSTRALIA  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_INDIA  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_BG_DENMARK  \
{                                   \
	0x02A,	0x7E0,	0x7D7,	0x0E2,	0x2CF,\
	0x11F,	0x716,	0x01A,	0x0BF,	0x6A9,\
	0x14A,	0x717,	0x075,	0x7E6,	0x7E7,\
	0x02C,	0x7D4,	0x024,	0x7E5,	0x012,\
	0x7F6,	0x004,	0x000,	0x7FD,	0x004,\
	0x7FC,	0x003,	0x7FE,	0x001,	0x7FF,\
	0x000,	0x000,	0x000,	0x000,\
}
#define IFD_GROUPDELAY_TABLE_DK_POLAND  \
{                                   \
    0x026,0x7F4,0x7E7,0x7DE,        \
    0x146,0x207,0x1BF,0x711,        \
    0x7B5,0x086,0x052,0x69A,        \
    0x185,0x71E,0x018,0x065,        \
    0x77B,0x072,0x7B4,0x027,        \
    0x7F8,0x7F5,0x012,0x7EF,        \
    0x00D,0x7F6,0x007,0x7FC,        \
    0x001,0x002,0x7FD,0x004,        \
    0x7FD,0x000,                          \
}
#define IFD_GROUPDELAY_TABLE_DK_CZECH  \
{                                   \
    0x026,0x7F4,0x7E7,0x7DE,        \
    0x146,0x207,0x1BF,0x711,        \
    0x7B5,0x086,0x052,0x69A,        \
    0x185,0x71E,0x018,0x065,        \
    0x77B,0x072,0x7B4,0x027,        \
    0x7F8,0x7F5,0x012,0x7EF,        \
    0x00D,0x7F6,0x007,0x7FC,        \
    0x001,0x002,0x7FD,0x004,        \
    0x7FD,0x000,                          \
}
#define IFD_GROUPDELAY_TABLE_M                           \
{                                                   \
	0x026,0x7F4,0x7E7,0x7DE,\
	0x146,0x207,0x1BF,0x711,\
	0x7B5,0x086,0x052,0x69A,\
	0x185,0x71E,0x018,0x065,\
	0x77B,0x072,0x7B4,0x027,\
	0x7F8,0x7F5,0x012,0x7EF,\
	0x00D,0x7F6,0x007,0x7FC,\
	0x001,0x002,0x7FD,0x004,\
	0x7FD,0x000,\
}                                                   
#define IFD_GROUPDELAY_TABLE_N                           \
{                                                   \
    0x023,    0x7A2,    0x09C,    0x729,    0x116,  \
    0x6E0,    0x08A,    0x09F,    0x1C8,    0x26D,  \
    0x74D,    0x739,    0x0F7,    0x7D6,    0x780,  \
    0x06E,    0x002,    0x7BF,    0x025,    0x003,  \
    0x7E9,    0x011,    0x7FE,    0x7F7,    0x009,  \
    0x7FD,    0x7FC,    0x005,    0x7FE,    0x7FE,  \
    0x003,    0x7FF,    0x7FF,    0x000,                 \
}
/////////////////////////////////////////////////
//Follow Standard Table To Add any new special table.
/////////////////////////////////////////////////
#define IFD_GROUPDELAY_TABLE_M_OTHER1	\
{ 											\
	0x017, 0x010, 0x7EA, 0x7DD, 0x0B0,			\
	0x1FB, 0x243, 0x07D, 0x744, 0x023,			\
	0x081, 0x75A, 0x012, 0x061, 0x786,			\
	0x04B, 0x7ED, 0x7F4, 0x016, 0x7E9,			\
	0x012, 0x7F4, 0x004, 0x001, 0x7FE,			\
	0x002, 0x7FE, 0x002, 0x7FF, 0x002,			\
	0x7FF, 0x000, 0x000, 0x7FE,				\
}
#define IFD_GROUPDELAY_TABLE_DK_OTHER1 \
       {  \
              0x000, 0x000, 0x000, 0x000,   \
              0x002, 0x000, 0x7FC, 0x008,   \
              0x7F8, 0x7FC, 0x01A, 0x7D8,   \
              0x014, 0x030, 0x76A, 0x0F4,   \
              0x2E4, 0x0F4, 0x76A, 0x030,   \
              0x014, 0x7D8, 0x01A, 0x7FC,   \
              0x7F8, 0x008, 0x7FC, 0x000,   \
              0x002, 0x000, 0x000, 0x000,   \
              0x000, 0x000,   \
       }
//=================================================================
//Output LPF Table
//=================================================================
typedef struct {
	UINT16	StructOuputLpfCoef_Table[OUPUT_LPF_TABLE_SIZE];
} StructOuputLpfCoef;

#define IFD_OUTPUTLPF_COEF_TABLE_MN		 \
       {  \
              0x3FFF, 0x000A, 0x0019, 0x0002, 0x3FE6,   \
              0x0003, 0x001A, 0x3FF1, 0x3FED, 0x001A,   \
              0x0004, 0x3FE3, 0x0010, 0x0013, 0x3FE2,   \
              0x0001, 0x001E, 0x3FE9, 0x3FF3, 0x0022,   \
              0x3FF3, 0x3FE7, 0x0020, 0x0000, 0x3FDF,   \
              0x001B, 0x000D, 0x3FDA, 0x0012, 0x0019,   \
              0x3FDA, 0x0006, 0x0022, 0x3FDD, 0x3FFA,   \
              0x002A, 0x3FE4, 0x3FED, 0x002D, 0x3FEE,   \
              0x3FE1, 0x002E, 0x3FFA, 0x3FD6, 0x002B,   \
              0x0007, 0x3FCD, 0x0024, 0x0016, 0x3FC8,   \
              0x001A, 0x0025, 0x3FC5, 0x000D, 0x0033,   \
              0x3FC7, 0x3FFD, 0x003F, 0x3FCC, 0x3FEB,   \
              0x004A, 0x3FD6, 0x3FD7, 0x0051, 0x3FE4,   \
              0x3FC2, 0x0055, 0x3FF7, 0x3FAD, 0x0053,   \
              0x000F, 0x3F98, 0x004D, 0x002C, 0x3F84,   \
              0x003F, 0x004F, 0x3F71, 0x0029, 0x007B,   \
              0x3F60, 0x0007, 0x00B2, 0x3F52, 0x3FD2,   \
              0x00FD, 0x3F46, 0x3F79, 0x0174, 0x3F3D,   \
              0x3EC0, 0x027D, 0x3F38, 0x3C09, 0x0930,   \
              0x148C,   \
       }
#define IFD_OUTPUTLPF_COEF_TABLE_BG		 \
       {  \
              0x3FEE, 0x3FF4, 0x0013, 0x3FF8, 0x3FF8,   \
              0x0012, 0x3FF0, 0x0003, 0x000B, 0x3FED,   \
              0x0011, 0x3FFB, 0x3FF6, 0x0014, 0x3FEC,   \
              0x000A, 0x0006, 0x3FED, 0x0017, 0x3FEF,   \
              0x0002, 0x000F, 0x3FE7, 0x0017, 0x3FF5,   \
              0x3FF9, 0x0017, 0x3FE3, 0x0015, 0x3FFC,   \
              0x3FF0, 0x001E, 0x3FE2, 0x0011, 0x0005,   \
              0x3FE7, 0x0023, 0x3FE2, 0x000B, 0x000E,   \
              0x3FDE, 0x0027, 0x3FE5, 0x0002, 0x0019,   \
              0x3FD6, 0x002A, 0x3FE9, 0x3FF9, 0x0024,   \
              0x3FCD, 0x002B, 0x3FF0, 0x3FED, 0x0031,   \
              0x3FC6, 0x002A, 0x3FF9, 0x3FDE, 0x003E,   \
              0x3FBF, 0x0027, 0x0006, 0x3FCC, 0x004E,   \
              0x3FB8, 0x0021, 0x0017, 0x3FB6, 0x0060,   \
              0x3FB3, 0x0017, 0x002F, 0x3F99, 0x0076,   \
              0x3FAE, 0x0005, 0x0053, 0x3F6F, 0x0095,   \
              0x3FAA, 0x3FE6, 0x008F, 0x3F2A, 0x00C7,   \
              0x3FA8, 0x3FA7, 0x010D, 0x3E8E, 0x0142,   \
              0x3FA6, 0x3ECE, 0x031A, 0x3B0F, 0x0645,   \
              0x193F,   \
       }
#define IFD_OUTPUTLPF_COEF_TABLE_I		 \
       {  \
              0x3FEE, 0x3FF4, 0x0013, 0x3FF8, 0x3FF8,   \
              0x0012, 0x3FF0, 0x0003, 0x000B, 0x3FED,   \
              0x0011, 0x3FFB, 0x3FF6, 0x0014, 0x3FEC,   \
              0x000A, 0x0006, 0x3FED, 0x0017, 0x3FEF,   \
              0x0002, 0x000F, 0x3FE7, 0x0017, 0x3FF5,   \
              0x3FF9, 0x0017, 0x3FE3, 0x0015, 0x3FFC,   \
              0x3FF0, 0x001E, 0x3FE2, 0x0011, 0x0005,   \
              0x3FE7, 0x0023, 0x3FE2, 0x000B, 0x000E,   \
              0x3FDE, 0x0027, 0x3FE5, 0x0002, 0x0019,   \
              0x3FD6, 0x002A, 0x3FE9, 0x3FF9, 0x0024,   \
              0x3FCD, 0x002B, 0x3FF0, 0x3FED, 0x0031,   \
              0x3FC6, 0x002A, 0x3FF9, 0x3FDE, 0x003E,   \
              0x3FBF, 0x0027, 0x0006, 0x3FCC, 0x004E,   \
              0x3FB8, 0x0021, 0x0017, 0x3FB6, 0x0060,   \
              0x3FB3, 0x0017, 0x002F, 0x3F99, 0x0076,   \
              0x3FAE, 0x0005, 0x0053, 0x3F6F, 0x0095,   \
              0x3FAA, 0x3FE6, 0x008F, 0x3F2A, 0x00C7,   \
              0x3FA8, 0x3FA7, 0x010D, 0x3E8E, 0x0142,   \
              0x3FA6, 0x3ECE, 0x031A, 0x3B0F, 0x0645,   \
              0x193F,   \
       }	
/*       {  \
              0x0019, 0x0009, 0x3FEA, 0x0014, 0x3FF7,   \
              0x3FFC, 0x000F, 0x3FEB, 0x0014, 0x3FF3,   \
              0x0003, 0x0008, 0x3FEF, 0x0016, 0x3FEA,   \
              0x0010, 0x3FFA, 0x3FFB, 0x0010, 0x3FE9,   \
              0x0019, 0x3FEA, 0x000E, 0x3FFE, 0x3FF6,   \
              0x0015, 0x3FE5, 0x001D, 0x3FE8, 0x000E,   \
              0x3FFF, 0x3FF3, 0x0019, 0x3FE0, 0x0022,   \
              0x3FE4, 0x0011, 0x3FFE, 0x3FF2, 0x001C,   \
              0x3FDA, 0x0028, 0x3FDE, 0x0016, 0x3FFC,   \
              0x3FF1, 0x0020, 0x3FD4, 0x0030, 0x3FD5,   \
              0x001D, 0x3FF7, 0x3FF2, 0x0024, 0x3FCC,   \
              0x003B, 0x3FC9, 0x0029, 0x3FEF, 0x3FF5,   \
              0x0027, 0x3FC3, 0x0049, 0x3FB8, 0x0039,   \
              0x3FE2, 0x3FFB, 0x002A, 0x3FB7, 0x005E,   \
              0x3F9E, 0x0053, 0x3FCC, 0x0007, 0x002C,   \
              0x3FA4, 0x007F, 0x3F73, 0x0082, 0x3FA4,   \
              0x001F, 0x002E, 0x3F83, 0x00C1, 0x3F15,   \
              0x00EE, 0x3F3F, 0x0061, 0x002F, 0x3F1B,   \
              0x01B3, 0x3D7C, 0x0343, 0x3C23, 0x0440,   \
              0x1B9D,   \
       }*/
#define IFD_OUTPUTLPF_COEF_TABLE_DKL		 \
       {  \
              0x3FEE, 0x3FF4, 0x0013, 0x3FF8, 0x3FF8,   \
              0x0012, 0x3FF0, 0x0003, 0x000B, 0x3FED,   \
              0x0011, 0x3FFB, 0x3FF6, 0x0014, 0x3FEC,   \
              0x000A, 0x0006, 0x3FED, 0x0017, 0x3FEF,   \
              0x0002, 0x000F, 0x3FE7, 0x0017, 0x3FF5,   \
              0x3FF9, 0x0017, 0x3FE3, 0x0015, 0x3FFC,   \
              0x3FF0, 0x001E, 0x3FE2, 0x0011, 0x0005,   \
              0x3FE7, 0x0023, 0x3FE2, 0x000B, 0x000E,   \
              0x3FDE, 0x0027, 0x3FE5, 0x0002, 0x0019,   \
              0x3FD6, 0x002A, 0x3FE9, 0x3FF9, 0x0024,   \
              0x3FCD, 0x002B, 0x3FF0, 0x3FED, 0x0031,   \
              0x3FC6, 0x002A, 0x3FF9, 0x3FDE, 0x003E,   \
              0x3FBF, 0x0027, 0x0006, 0x3FCC, 0x004E,   \
              0x3FB8, 0x0021, 0x0017, 0x3FB6, 0x0060,   \
              0x3FB3, 0x0017, 0x002F, 0x3F99, 0x0076,   \
              0x3FAE, 0x0005, 0x0053, 0x3F6F, 0x0095,   \
              0x3FAA, 0x3FE6, 0x008F, 0x3F2A, 0x00C7,   \
              0x3FA8, 0x3FA7, 0x010D, 0x3E8E, 0x0142,   \
              0x3FA6, 0x3ECE, 0x031A, 0x3B0F, 0x0645,   \
              0x193F,   \
       }

//=================================================================
//EQ notch Table
//=================================================================

typedef struct {
	UINT16	EQNotch_Table[EQ_TABLE_SIZE];
} StructEQNotch;

#define IFD_EQ_TABLE_NTSC_0 \
       {  \
              0x000, 0x000, 0x000, 0x000,   \
              0x3ff, 0x000, 0x000, 0x000,   \
              0x000, 0x000, 0x000, 0x001,   \
              0x000, 0x3ff, 0x001, 0x001,   \
              0x3fe, 0x000, 0x001, 0x3ff,   \
              0x001, 0x3ff, 0x3fd, 0x007,   \
              0x001, 0x3f0, 0x008, 0x01a,   \
              0x3dc, 0x3db, 0x090, 0x113,   \
       }
#define IFD_EQ_TABLE_NTSC_SI2156 \
	{  \
		   0x000, 0x000, 0x000, 0x000,	 \
		   0x000, 0x000, 0x000, 0x000,	 \
		   0x000, 0x000, 0x000, 0x3ff,	 \
		   0x001, 0x000, 0x000, 0x001,	 \
		   0x3ff, 0x002, 0x3fc, 0x001,	 \
		   0x003, 0x3fc, 0x003, 0x3fd,	 \
		   0x008, 0x3fd, 0x3ec, 0x01e,	 \
		   0x3f6, 0x3ce, 0x094, 0x135,	 \
	}
#define IFD_EQ_TABLE_PALBG_0 \
       {  \
              0x000, 0x3ff, 0x001, 0x3ff,   \
              0x000, 0x000, 0x000, 0x000,   \
              0x001, 0x3ff, 0x000, 0x000,   \
              0x3ff, 0x000, 0x001, 0x3fe,   \
              0x002, 0x3ff, 0x3ff, 0x001,   \
              0x000, 0x3fd, 0x006, 0x3fb,   \
              0x001, 0x003, 0x000, 0x3f4,   \
              0x022, 0x3c3, 0x052, 0x1a5,   \
       }
#define IFD_EQ_TABLE_PALBG_SI2156 \
	{  \
		   0x001, 0x3ff, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x000,	 \
		   0x000, 0x001, 0x3ff, 0x002,	 \
		   0x3ff, 0x000, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x3fe,	 \
		   0x003, 0x3fe, 0x3ff, 0x006,	 \
		   0x3f5, 0x00e, 0x3f9, 0x3f8,	 \
		   0x022, 0x3c8, 0x06b, 0x15f,	 \
	}

#define IFD_EQ_TABLE_PALI_0 \
       {  \
              0x001, 0x3ff, 0x002, 0x3fe,   \
              0x002, 0x3ff, 0x001, 0x000,   \
              0x000, 0x001, 0x3ff, 0x002,   \
              0x3fe, 0x001, 0x001, 0x3fe,   \
              0x003, 0x3fe, 0x001, 0x000,   \
              0x000, 0x001, 0x3ff, 0x004,   \
              0x3fa, 0x009, 0x3fc, 0x3fd,   \
              0x019, 0x3dd, 0x06e, 0x131,   \
       }
#define IFD_EQ_TABLE_PALI_SI2156 \
	{  \
		   0x001, 0x3ff, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x000,	 \
		   0x000, 0x001, 0x3ff, 0x002,	 \
		   0x3ff, 0x000, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x3fe,	 \
		   0x003, 0x3fe, 0x3ff, 0x006,	 \
		   0x3f5, 0x00e, 0x3f9, 0x3f8,	 \
		   0x022, 0x3c8, 0x06b, 0x15f,	 \
	}

#define IFD_EQ_TABLE_PALDKL_0 \
       {  \
              0x000, 0x3ff, 0x001, 0x3ff,   \
              0x000, 0x000, 0x000, 0x000,   \
              0x001, 0x3ff, 0x000, 0x000,   \
              0x3ff, 0x000, 0x001, 0x3fe,   \
              0x002, 0x3ff, 0x3ff, 0x001,   \
              0x000, 0x3fd, 0x006, 0x3fb,   \
              0x001, 0x003, 0x000, 0x3f4,   \
              0x022, 0x3c3, 0x052, 0x1a5,   \
       }

#define IFD_EQ_TABLE_PALDKL_SI2156 \
	{  \
		   0x001, 0x3ff, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x000,	 \
		   0x000, 0x001, 0x3ff, 0x002,	 \
		   0x3ff, 0x000, 0x001, 0x3ff,	 \
		   0x001, 0x3ff, 0x001, 0x3fe,	 \
		   0x003, 0x3fe, 0x3ff, 0x006,	 \
		   0x3f5, 0x00e, 0x3f9, 0x3f8,	 \
		   0x022, 0x3c8, 0x06b, 0x15f,	 \
	}

//Ring
#define IFD_EQ_TABLE_PALDKL_2 \
{  \
	   0x000, 0x000, 0x000, 0x000,	 \
	   0x000, 0x000, 0x000, 0x3ff,	 \
	   0x001, 0x000, 0x000, 0x001,	 \
	   0x3fe, 0x000, 0x3fe, 0x3ff,	 \
	   0x002, 0x3fe, 0x005, 0x3fe,	 \
	   0x001, 0x000, 0x3f9, 0x008,	 \
	   0x3f5, 0x005, 0x005, 0x3fc,	 \
	   0x016, 0x3c2, 0x071, 0x171,	 \
}


#define IFD_TUNER_BAND_MAX 24
#define IFD_TUNER_REG_MAX 4
#define IFD_TUNER_REG_BAND_MAX IFD_TUNER_BAND_MAX*IFD_TUNER_REG_MAX
#define IFD_CR_BPF_TABLE_SIZE 41
#define IFD_OUTPUT_LPF_TABLE_SIZE 96
#define IFD_EQ_TABLE_SIZE (32)
#define IFD_GP_BPF_TABLE_SIZE 34
#define IFD_INPUT_FILTER_TABLE_SIZE 72


typedef struct {
	UINT8	tunerI2C_ADD;
	UINT32	tunerMinFreq;
	UINT32	tunerVHF_LowFreq;
	UINT32	tunerVHF_HighFreq;
	UINT32	tunerMaxFreq;
	UINT32	tunerPIF;
	UINT32	tunerPIF_MN;
	UINT32 	tunerPIF_B;
	UINT32	tunerPIF_GH;
	UINT32	tunerPIF_I;
	UINT32	tunerPIF_DK;
	UINT32	tunerPIF_L;
	UINT32	tunerPIF_LA;
	UINT32	tunerPIF_SCAN;
	bool		tunerIFType;
	UINT32	tunerRATIOStepSize;
	UINT32	tunerBandFreq[IFD_TUNER_BAND_MAX];
	UINT8	tunerRegisterByte[IFD_TUNER_REG_BAND_MAX];
	UINT8	tunerRegisterByteSearch[IFD_TUNER_REG_BAND_MAX];
	UINT8	tunerRfInputSwitchUsedTag;
	UINT8	tunerRfInputByte;
	UINT8	tunerRfInputLocation;
	UINT8	tunerFLStatusBit;
	UINT8	tunerBandNo;
	UINT8	tunerRegNoPerBand;
	UINT8	tunerUsedTag;
	UINT8	tunerAGCtype;
	UINT8	tunerAGCpolarity;
	UINT8	tunerType;
	UINT32	tunerSpecificTag;
	UINT8	tunerID;
	//ATV_TUNER_MODULE *pTuner;
} StructTunerDataType;

typedef struct {
	UINT32	ifdMagicCode;
	UINT8	ifdAGCPGAMode;
	UINT16	ifdAGCFixPGAValue;
	UINT16	AGCVtop[IFD_TUNER_BAND_MAX];
    	UINT16	AGC_PGA_MIN[IFD_TUNER_BAND_MAX];
	UINT16	SCANdelay;
	UINT16	SETCHANNELdelay;
	UINT16	CRPhaseInverseThr;
	UINT8	CRinverse_debounce;
	UINT8	CRSt3pgain;
	UINT8	CRSt3igain;
	UINT8	CRSt2pgain;
	UINT8	CRSt2igain;
	UINT8	CRSt0pgain;
	UINT8	CRSt0igain;
	UINT8	CRpgain;
	UINT8	CRigain;
	UINT8	CRlock_err_thd;
	UINT8	CRweight_speed;
	UINT8	CRphasebad_en;
	UINT32	CRvariance_thr;
	UINT16	CRBpf_Table_MN[IFD_CR_BPF_TABLE_SIZE];
	UINT16 	CRBpf_Table_B[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_GH[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_I[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_DK[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_L[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_LA[IFD_CR_BPF_TABLE_SIZE];
	UINT16	CRBpf_Table_SCAN[IFD_CR_BPF_TABLE_SIZE];
	UINT8	CRInnerLpf_MN;
	UINT8 	CRInnerLpf_BGH;
	UINT8	CRInnerLpf_IDKL;
	UINT8	CRInnerLpf_LA;
	UINT8	CRInnerLpf_SCAN;
	bool		GRPdelayM_En;
	bool		GRPdelayN_En;
	bool		GRPdelayBG_En;
	bool		GRPdelayDKL_En;
	UINT16	GRPdelayTableM[IFD_GP_BPF_TABLE_SIZE];
	UINT16	GRPdelayTableN[IFD_GP_BPF_TABLE_SIZE];
	UINT16	GRPdelayTableBG[IFD_GP_BPF_TABLE_SIZE];
	UINT16	GRPdelayTableDKL[IFD_GP_BPF_TABLE_SIZE];
	bool        InputFltNtsc_En;
	bool        InputFltPalD_En;
	bool		InputFltPalB_En;
	bool		InputFltPalN_En;
	UINT16   InputFltTableNtsc[IFD_INPUT_FILTER_TABLE_SIZE];
	UINT16   InputFltTablePalD[IFD_INPUT_FILTER_TABLE_SIZE];
	UINT16   InputFltTablePalB[IFD_INPUT_FILTER_TABLE_SIZE];
	UINT16   InputFltTablePalN[IFD_INPUT_FILTER_TABLE_SIZE];
	UINT16	VideoLpfNTSC[IFD_OUTPUT_LPF_TABLE_SIZE];
	UINT16	VideoLpfPAL_BG[IFD_OUTPUT_LPF_TABLE_SIZE];
	UINT16	VideoLpfPAL_I[IFD_OUTPUT_LPF_TABLE_SIZE];
	UINT16	VideoLpfPAL_DKL[IFD_OUTPUT_LPF_TABLE_SIZE];
	UINT16	VideoLpfSECAM[IFD_OUTPUT_LPF_TABLE_SIZE];
	bool		EQ_Table_NTSC_En;
	bool		EQ_Table_PAL_BG_En;
	bool		EQ_Table_PAL_I_En;
	bool		EQ_Table_PAL_DKL_En;
	UINT16	EQ_Table_NTSC[IFD_EQ_TABLE_SIZE];
	UINT16	EQ_Table_PAL_BG[IFD_EQ_TABLE_SIZE];
	UINT16	EQ_Table_PAL_I[IFD_EQ_TABLE_SIZE];
	UINT16	EQ_Table_PAL_DKL[IFD_EQ_TABLE_SIZE];
       UINT16    AGC_rf_max[IFD_TUNER_BAND_MAX];
       UINT16    AGC_rf_min[IFD_TUNER_BAND_MAX];
   	UINT16    AGC_krf[IFD_TUNER_BAND_MAX];
	UINT16	AGC_if_max;
	UINT16    AGC_if_min;
	UINT16	AGCloop1_maxtargetNTSC;
	UINT16	AGCloop1_maxtargetPAL;
	UINT16	AGCloop1_maxtargetSECAM;
	UINT16	AGCloop1_difftarget;
	UINT16	AGCloop1_peaktarget;
	bool		AGCloop1_peakforce_en;
	UINT8	AGCloop1_kpgain;
	UINT8	AGCloop1_kigain;
	UINT8	AGCloop1_kpkishift;
	UINT16	AGCloop1_dnsample;
	UINT16	AGCloop1_finednsample;
	UINT8	AGCloop2_kpgain;
	UINT8	AGCloop2_kigain;
	UINT8	AGCloop2_kpshift;
	UINT8	AGCloop2_kishift;
	UINT16	AGCloop2_dnsample;
	UINT16	AGCloop2_finednsample;
	bool 	AGC_RfHasten_en;
	UINT8	AGC_RfHasten_ki;
	UINT16	AGC_RfHasten_cntl;
	UINT16	AGC_RfHasten_thr;
	bool		AGC_SepRfIf_en;
	UINT8	AGC_SepRfIf_IfKp;
	UINT8	AGC_SepRfIf_IfKi;
	UINT16	AGCadapt_fineinterval;
	UINT16	AGCadapt_interval;
	UINT8 	AGCadapt_en;
	UINT16	AGCadapt_incthr;
	UINT16	AGCadapt_mindifftarget;
	UINT16	AGCadapt_minmaxtarget;
	UINT16	AGCadapt_finetargetthr;
	UINT16	AGCadapt_diffcoarsestep;
	UINT16	AGCImpulsive_GateEnd;
	UINT16	AGCImpulsive_DetThr;
	bool		AGCImpulsive_Input;
	bool		AGCImpulsive_MakeEn;
	bool		AGCImpulsive_DetEn;
	UINT8	AGCImpulsive_DetStop;
	UINT16	AGCImpulsive_GateDelay;
	UINT8	AGCHum_Debounce;
	bool		AGCHum_UpdateSel;
	bool		AGCHum_En;
	UINT16	AGCHum_MaxThrOut;
	UINT16	AGCHum_MaxThrIn;
	UINT16	AGCHum_SyncThrOut;
	UINT16	AGCHum_SyncThrIn;
	UINT8	AGCSigmaDeltaDnSel;
	UINT16    AGCDataTarg;
	UINT8	DataGainSel;
	UINT8	CLAMPscale_scanch;
	UINT8	CLAMPscale_setch;
	UINT8	SHAPEfilter_bw;
	UINT8	ADCInput_ShaGain;
	UINT8	ADCInput_FullScale;
	UINT8     ADCInput_clock;
	UINT8     ADCinput_dn_filter_sel;
	UINT8	AFClockthd;
       UINT8     AFC_STAGE_MAX_COUNT;
	UINT8     AFC_Max_Freq;
	//StructTunerDataType	tunerPara;
} StructIFDDataType;



extern StructIFDDataType stIFDUserData;
/*
extern StructIFDDataType	stIFDUserDataArray[_Tuner_MAX_NO];
extern StructIFDDataType	stIFDdefaultUserData;
*/
//extern UINT8				gTunerNo;
//extern UINT8				gTunerActiveID;
extern StructTunerDataType	gTunerData[_Tuner_MAX_NO];
//extern ATV_TUNER_MODULE *pTuner;


#define GET_ATV_IFD_MAGICCODE()                                        stIFDUserData.ifdMagicCode
#define GET_ATV_IFD_AGCPGAMODE()                                       stIFDUserData.ifdAGCPGAMode
#define GET_ATV_IFD_AGCFIXPGAVALUE()                                   stIFDUserData.ifdAGCFixPGAValue
#define GET_ATV_IFD_AGCVTOP(x)                                          stIFDUserData.AGCVtop[x]
#define GET_ATV_IFD_AGC_PGA_MIN(x)                                      stIFDUserData.AGC_PGA_MIN[x]
#define GET_ATV_IFD_SCANDELAY()                                           stIFDUserData.SCANdelay
#define GET_ATV_IFD_SETCHANNELDELAY()                                     stIFDUserData.SETCHANNELdelay
#define GET_ATV_IFD_CRPHASEINVERSETHR()                                   stIFDUserData.CRPhaseInverseThr
#define GET_ATV_IFD_CRINVERSE_DEBOUNCE()                                  stIFDUserData.CRinverse_debounce
#define GET_ATV_IFD_CRST3PGAIN()                                          stIFDUserData.CRSt3pgain
#define GET_ATV_IFD_CRST3IGAIN()                                          stIFDUserData.CRSt3igain
#define GET_ATV_IFD_CRST2PGAIN()                                          stIFDUserData.CRSt2pgain
#define GET_ATV_IFD_CRST2IGAIN()                                          stIFDUserData.CRSt2igain
#define GET_ATV_IFD_CRST0PGAIN()                                          stIFDUserData.CRSt0pgain
#define GET_ATV_IFD_CRST0IGAIN()                                          stIFDUserData.CRSt0igain
#define GET_ATV_IFD_CRPGAIN()                                             stIFDUserData.CRpgain
#define GET_ATV_IFD_CRIGAIN()                                             stIFDUserData.CRigain
#define GET_ATV_IFD_CRLOCK_ERR_THD()                                      stIFDUserData.CRlock_err_thd
#define GET_ATV_IFD_CRWEIGHT_SPEED()                                      stIFDUserData.CRweight_speed
#define GET_ATV_IFD_CRPHASEBAD_EN()                                       stIFDUserData.CRphasebad_en
#define GET_ATV_IFD_CRVARIANCE_THR()                                      stIFDUserData.CRvariance_thr
#define GET_ATV_IFD_CRBPF_TABLE_MN()                                      &stIFDUserData.CRBpf_Table_MN[0]
#define GET_ATV_IFD_CRBPF_TABLE_B()                                       &stIFDUserData.CRBpf_Table_B[0]
#define GET_ATV_IFD_CRBPF_TABLE_GH()                                      &stIFDUserData.CRBpf_Table_GH[0]
#define GET_ATV_IFD_CRBPF_TABLE_I()                                       &stIFDUserData.CRBpf_Table_I[0]
#define GET_ATV_IFD_CRBPF_TABLE_DK()                                      &stIFDUserData.CRBpf_Table_DK[0]
#define GET_ATV_IFD_CRBPF_TABLE_L()                                       &stIFDUserData.CRBpf_Table_L[0]
#define GET_ATV_IFD_CRBPF_TABLE_LA()                                      &stIFDUserData.CRBpf_Table_LA[0]
#define GET_ATV_IFD_CRBPF_TABLE_SCAN()                                    &stIFDUserData.CRBpf_Table_SCAN[0]
#define GET_ATV_IFD_CRINNERLPF_MN()                                       stIFDUserData.CRInnerLpf_MN
#define GET_ATV_IFD_CRINNERLPF_BGH()                                      stIFDUserData.CRInnerLpf_BGH
#define GET_ATV_IFD_CRINNERLPF_IDKL()                                     stIFDUserData.CRInnerLpf_IDKL
#define GET_ATV_IFD_CRINNERLPF_LA()                                       stIFDUserData.CRInnerLpf_LA
#define GET_ATV_IFD_CRINNERLPF_SCAN()                                     stIFDUserData.CRInnerLpf_SCAN
#define GET_ATV_IFD_GRPDELAYM_EN()                                        stIFDUserData.GRPdelayM_En
#define GET_ATV_IFD_GRPDELAYN_EN()                                        stIFDUserData.GRPdelayN_En
#define GET_ATV_IFD_GRPDELAYBG_EN()                                       stIFDUserData.GRPdelayBG_En
#define GET_ATV_IFD_GRPDELAYDKL_EN()                                      stIFDUserData.GRPdelayDKL_En
#define GET_ATV_IFD_GRPDELAYTABLEM()                                      &stIFDUserData.GRPdelayTableM[0]
#define GET_ATV_IFD_GRPDELAYTABLEN()                                      &stIFDUserData.GRPdelayTableN[0]
#define GET_ATV_IFD_GRPDELAYTABLEBG()                                     &stIFDUserData.GRPdelayTableBG[0]
#define GET_ATV_IFD_GRPDELAYTABLEDKL()                                    &stIFDUserData.GRPdelayTableDKL[0]
#define GET_ATV_IFD_INPUTFLTNTSC_EN()                                     stIFDUserData.InputFltNtsc_En
#define GET_ATV_IFD_INPUTFLTPALD_EN()                                     stIFDUserData.InputFltPalD_En
#define GET_ATV_IFD_INPUTFLTPALB_EN()                                     stIFDUserData.InputFltPalB_En
#define GET_ATV_IFD_INPUTFLTPALN_EN()                                     stIFDUserData.InputFltPalN_En
#define GET_ATV_IFD_INPUTFLTTABLENTSC()                                   &stIFDUserData.InputFltTableNtsc[0]
#define GET_ATV_IFD_INPUTFLTTABLEPALD()                                   &stIFDUserData.InputFltTablePalD[0]
#define GET_ATV_IFD_INPUTFLTTABLEPALB()                                   &stIFDUserData.InputFltTablePalB[0]
#define GET_ATV_IFD_INPUTFLTTABLEPALN()                                   &stIFDUserData.InputFltTablePalN[0]
#define GET_ATV_IFD_VIDEOLPFNTSC()                                        &stIFDUserData.VideoLpfNTSC[0]
#define GET_ATV_IFD_VIDEOLPFPAL_BG()                                      &stIFDUserData.VideoLpfPAL_BG[0]
#define GET_ATV_IFD_VIDEOLPFPAL_I()                                       &stIFDUserData.VideoLpfPAL_I[0]
#define GET_ATV_IFD_VIDEOLPFPAL_DKL()                                     &stIFDUserData.VideoLpfPAL_DKL[0]
#define GET_ATV_IFD_VIDEOLPFSECAM()                                       &stIFDUserData.VideoLpfSECAM[0]
#define GET_ATV_IFD_EQ_TABLE_NTSC_EN()                                    stIFDUserData.EQ_Table_NTSC_En
#define GET_ATV_IFD_EQ_TABLE_PAL_BG_EN()                                  stIFDUserData.EQ_Table_PAL_BG_En
#define GET_ATV_IFD_EQ_TABLE_PAL_I_EN()                                   stIFDUserData.EQ_Table_PAL_I_En
#define GET_ATV_IFD_EQ_TABLE_PAL_DKL_EN()                                 stIFDUserData.EQ_Table_PAL_DKL_En
#define GET_ATV_IFD_EQ_TABLE_NTSC()                                       &stIFDUserData.EQ_Table_NTSC[0]
#define GET_ATV_IFD_EQ_TABLE_PAL_BG()                                     &stIFDUserData.EQ_Table_PAL_BG[0]
#define GET_ATV_IFD_EQ_TABLE_PAL_I()                                      &stIFDUserData.EQ_Table_PAL_I[0]
#define GET_ATV_IFD_EQ_TABLE_PAL_DKL()                                    &stIFDUserData.EQ_Table_PAL_DKL[0]
#define GET_ATV_IFD_AGC_RF_MAX(x)                                       stIFDUserData.AGC_rf_max[x]
#define GET_ATV_IFD_AGC_RF_MIN(x)                                       stIFDUserData.AGC_rf_min[x]
#define GET_ATV_IFD_AGC_KRF(x)                                          stIFDUserData.AGC_krf[x]
#define GET_ATV_IFD_AGC_IF_MAX()                                          stIFDUserData.AGC_if_max
#define GET_ATV_IFD_AGC_IF_MIN()                                          stIFDUserData.AGC_if_min
#define GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC()                              stIFDUserData.AGCloop1_maxtargetNTSC
#define GET_ATV_IFD_AGCLOOP1_MAXTARGETPAL()                               stIFDUserData.AGCloop1_maxtargetPAL
#define GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM()                             stIFDUserData.AGCloop1_maxtargetSECAM
#define GET_ATV_IFD_AGCLOOP1_DIFFTARGET()                                 stIFDUserData.AGCloop1_difftarget
#define GET_ATV_IFD_AGCLOOP1_PEAKTARGET()                                 stIFDUserData.AGCloop1_peaktarget
#define GET_ATV_IFD_AGCLOOP1_PEAKFORCE_EN()                                 stIFDUserData.AGCloop1_peakforce_en
#define GET_ATV_IFD_AGCLOOP1_KPGAIN()                                     stIFDUserData.AGCloop1_kpgain
#define GET_ATV_IFD_AGCLOOP1_KIGAIN()                                     stIFDUserData.AGCloop1_kigain
#define GET_ATV_IFD_AGCLOOP1_KPKISHIFT()                                  stIFDUserData.AGCloop1_kpkishift
#define GET_ATV_IFD_AGCLOOP1_DNSAMPLE()                                   stIFDUserData.AGCloop1_dnsample
#define GET_ATV_IFD_AGCLOOP1_FINEDNSAMPLE()                               stIFDUserData.AGCloop1_finednsample
#define GET_ATV_IFD_AGCLOOP2_KPGAIN()                                    stIFDUserData.AGCloop2_kpgain
#define GET_ATV_IFD_AGCLOOP2_KIGAIN()                                     stIFDUserData.AGCloop2_kigain
#define GET_ATV_IFD_AGCLOOP2_KPSHIFT()                                    stIFDUserData.AGCloop2_kpshift
#define GET_ATV_IFD_AGCLOOP2_KISHIFT()                                    stIFDUserData.AGCloop2_kishift
#define GET_ATV_IFD_AGCLOOP2_DNSAMPLE()                                   stIFDUserData.AGCloop2_dnsample
#define GET_ATV_IFD_AGCLOOP2_FINEDNSAMPLE()                               stIFDUserData.AGCloop2_finednsample
#define GET_ATV_IFD_AGC_RFHASTEN_EN()                                     stIFDUserData.AGC_RfHasten_en
#define GET_ATV_IFD_AGC_RFHASTEN_KI()                                     stIFDUserData.AGC_RfHasten_ki
#define GET_ATV_IFD_AGC_RFHASTEN_CNTL()                                   stIFDUserData.AGC_RfHasten_cntl
#define GET_ATV_IFD_AGC_RFHASTEN_THR()                                    stIFDUserData.AGC_RfHasten_thr
#define GET_ATV_IFD_AGC_SEPRFIF_EN()                                      stIFDUserData.AGC_SepRfIf_en
#define GET_ATV_IFD_AGC_SEPRFIF_IFKP()                                    stIFDUserData.AGC_SepRfIf_IfKp
#define GET_ATV_IFD_AGC_SEPRFIF_IFKI()                                    stIFDUserData.AGC_SepRfIf_IfKi
#define GET_ATV_IFD_AGCADAPT_FINEINTERVAL()                               stIFDUserData.AGCadapt_fineinterval
#define GET_ATV_IFD_AGCADAPT_INTERVAL()                                   stIFDUserData.AGCadapt_interval
#define GET_ATV_IFD_AGCADAPT_EN()                                         stIFDUserData.AGCadapt_en
#define GET_ATV_IFD_AGCADAPT_INCTHR()                                     stIFDUserData.AGCadapt_incthr
#define GET_ATV_IFD_AGCADAPT_MINDIFFTARGET()                              stIFDUserData.AGCadapt_mindifftarget
#define GET_ATV_IFD_AGCADAPT_MINMAXTARGET()                               stIFDUserData.AGCadapt_minmaxtarget
#define GET_ATV_IFD_AGCADAPT_FINETARGETTHR()                              stIFDUserData.AGCadapt_finetargetthr
#define GET_ATV_IFD_AGCADAPT_DIFFCOARSESTEP()                             stIFDUserData.AGCadapt_diffcoarsestep
#define GET_ATV_IFD_AGCIMPULSIVE_GATEEND()                                stIFDUserData.AGCImpulsive_GateEnd
#define GET_ATV_IFD_AGCIMPULSIVE_DETTHR()                                 stIFDUserData.AGCImpulsive_DetThr
#define GET_ATV_IFD_AGCIMPULSIVE_INPUT()                                  stIFDUserData.AGCImpulsive_Input
#define GET_ATV_IFD_AGCIMPULSIVE_MAKEEN()                                 stIFDUserData.AGCImpulsive_MakeEn
#define GET_ATV_IFD_AGCIMPULSIVE_DETEN()                                  stIFDUserData.AGCImpulsive_DetEn
#define GET_ATV_IFD_AGCIMPULSIVE_DETSTOP()                                stIFDUserData.AGCImpulsive_DetStop
#define GET_ATV_IFD_AGCIMPULSIVE_GATEDELAY()                              stIFDUserData.AGCImpulsive_GateDelay
#define GET_ATV_IFD_AGCHUM_DEBOUNCE()                                     stIFDUserData.AGCHum_Debounce
#define GET_ATV_IFD_AGCHUM_UPDATESEL()                                    stIFDUserData.AGCHum_UpdateSel
#define GET_ATV_IFD_AGCHUM_EN()                                           stIFDUserData.AGCHum_En
#define GET_ATV_IFD_AGCHUM_MAXTHROUT()                                    stIFDUserData.AGCHum_MaxThrOut
#define GET_ATV_IFD_AGCHUM_MAXTHRIN()                                     stIFDUserData.AGCHum_MaxThrIn
#define GET_ATV_IFD_AGCHUM_SYNCTHROUT()                                   stIFDUserData.AGCHum_SyncThrOut
#define GET_ATV_IFD_AGCHUM_SYNCTHRIN()                                    stIFDUserData.AGCHum_SyncThrIn
#define GET_ATV_IFD_AGCSIGMADELTADNSEL()                                  stIFDUserData.AGCSigmaDeltaDnSel
#define GET_ATV_IFD_AGCDATATARG()                                         stIFDUserData.AGCDataTarg
#define GET_ATV_IFD_DATAGAINSEL()                                         stIFDUserData.DataGainSel
#define GET_ATV_IFD_CLAMPSCALE_SCANCH()                                   stIFDUserData.CLAMPscale_scanch
#define GET_ATV_IFD_CLAMPSCALE_SETCH()                                    stIFDUserData.CLAMPscale_setch
#define GET_ATV_IFD_SHAPEFILTER_BW()                                      stIFDUserData.SHAPEfilter_bw
#define GET_ATV_IFD_ADCINPUT_SHAGAIN()                                    stIFDUserData.ADCInput_ShaGain
#define GET_ATV_IFD_ADCINPUT_FULLSCALE()                                  stIFDUserData.ADCInput_FullScale
#define GET_ATV_IFD_ADCINPUT_CLOCK()                                      stIFDUserData.ADCInput_clock
#define GET_ATV_IFD_ADCINPUT_DN_FILTER_SEL()                              stIFDUserData.ADCinput_dn_filter_sel
#define GET_ATV_IFD_AFCLOCKTHD()                                          stIFDUserData.AFClockthd
#define GET_ATV_IFD_AFC_STAGE_MAX_COUNT()                                 stIFDUserData.AFC_STAGE_MAX_COUNT
#define GET_ATV_IFD_AFC_MAX_FREQ()                                        stIFDUserData.AFC_Max_Freq

#if 1
#define GET_ATV_TUNER_I2C_ADD()                gTunerData[0].tunerI2C_ADD                                   
#define GET_ATV_TUNER_MINFREQ()                gTunerData[0].tunerMinFreq                                   
#define GET_ATV_TUNER_VHF_LOWFREQ()            gTunerData[0].tunerVHF_LowFreq                               
#define GET_ATV_TUNER_VHF_HIGHFREQ()           gTunerData[0].tunerVHF_HighFreq                              
#define GET_ATV_TUNER_MAXFREQ()                gTunerData[0].tunerMaxFreq                                   
#define GET_ATV_TUNER_PIF()                    gTunerData[0].tunerPIF                                       
#define GET_ATV_TUNER_PIF_MN()                 gTunerData[0].tunerPIF_MN                                    
#define GET_ATV_TUNER_PIF_B()                  gTunerData[0].tunerPIF_B                                     
#define GET_ATV_TUNER_PIF_GH()                 gTunerData[0].tunerPIF_GH                                    
#define GET_ATV_TUNER_PIF_I()                  gTunerData[0].tunerPIF_I                                     
#define GET_ATV_TUNER_PIF_DK()                 gTunerData[0].tunerPIF_DK                                    
#define GET_ATV_TUNER_PIF_L()                  gTunerData[0].tunerPIF_L                                     
#define GET_ATV_TUNER_PIF_LA()                 gTunerData[0].tunerPIF_LA                                    
#define GET_ATV_TUNER_PIF_SCAN()               gTunerData[0].tunerPIF_SCAN                                  
#define GET_ATV_TUNER_IFTYPE()                 gTunerData[0].tunerIFType                                
#define GET_ATV_TUNER_RATIOSTEPSIZE()          gTunerData[0].tunerRATIOStepSize                             
#define GET_ATV_TUNER_BANDFREQ(x)              gTunerData[0].tunerBandFreq[x]              
#define GET_ATV_TUNER_REGISTERBYTE(x)          gTunerData[0].tunerRegisterByte[x]      
#define GET_ATV_TUNER_REGISTERBYTESEARCH(x)    gTunerData[0].tunerRegisterByteSearch[x]
#define GET_ATV_TUNER_RFINPUTSWITCHUSEDTAG()   gTunerData[0].tunerRfInputSwitchUsedTag                      
#define GET_ATV_TUNER_RFINPUTBYTE()            gTunerData[0].tunerRfInputByte                               
#define GET_ATV_TUNER_RFINPUTLOCATION()        gTunerData[0].tunerRfInputLocation                           
#define GET_ATV_TUNER_FLSTATUSBIT()            gTunerData[0].tunerFLStatusBit                               
#define GET_ATV_TUNER_BANDNO()                 gTunerData[0].tunerBandNo                                    
#define GET_ATV_TUNER_REGNOPERBAND()           gTunerData[0].tunerRegNoPerBand                              
#define GET_ATV_TUNER_USEDTAG()                gTunerData[0].tunerUsedTag                                   
#define GET_ATV_TUNER_AGCTYPE()                gTunerData[0].tunerAGCtype                                   
#define GET_ATV_TUNER_AGCPOLARITY()            gTunerData[0].tunerAGCpolarity                               
#define GET_ATV_TUNER_TYPE()                   gTunerData[0].tunerType                                      
#define GET_ATV_TUNER_SPECIFICTAG()            gTunerData[0].tunerSpecificTag                               
#define GET_ATV_TUNER_ID()                     gTunerData[0].tunerID                
#endif

void drv_ifd_system_init(void);
INT32 drv_ifd_get_cr_offset_100hz(UINT8 afc);
UINT32 drv_ifd_cal_nco(UINT32 pif_freq);
void drv_ifd_clamp_reset(IFD_CLAMP_RESET_POLARITY polarity);
void drv_ifd_agc_polarity(TUNER_AGCPOLARITY_SEL polarity);
//void drv_ifd_set_videomode(UINT8 mode);//by Lee, 07
void drv_ifd_set_video_ntsc(void);
void drv_ifd_set_video_ntsc_dk(void);
void drv_ifd_set_video_pal(void);
void drv_ifd_set_video_secaml(void);
void drv_ifd_set_video_secamla();
void drv_ifd_set_video_fm_radio(void);
//void drv_ifd_group_delay_coe_table(IFD_GROUPDELAY table_index);
void drv_ifd_set_adc_init(void);
void drv_ifd_agc_mode_set(IFD_MODE_AGC_PGA_CONFIG ifd_agc_mode, IFD_MODE_AGC_PGA_FIXGAIN_LEVEL pga_fix_value);
bool drv_ifd_pointer_check(void);
void drv_ifd_specific_function_enable(bool enable);
void drv_ifd_para_change_with_tunerband();


void drv_ifd_tuner_data_init(void);
void drv_ifd_tuner_BuildTuner(void);
//void drv_ifd_user_data_init(void);//by Lee


#endif //#ifndef IFD_DRIVER_H
