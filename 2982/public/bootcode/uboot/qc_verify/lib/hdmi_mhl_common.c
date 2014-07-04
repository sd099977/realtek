#include <qc_verify_common.h>
#include <rbusHDMIReg.h>
#include <rbusDFEReg.h>
#include <rbusMHLCbus.h>
#include <rbusMiscDDCReg.h>
//#include <crt_sys_reg.h>
#include <iso_reg.h>
#include <MHL_cbus.h>

//================for sirius k offset=========================================

#define k_offset_manual       0x10 
#define k_offset_manual_range       2
#define  HBR_enbuffer_off   1 
#define  LBR_enbuffer_off    2 
#define  LBR_enbuffer_on    3 
#define  MHL_3G_enbuffer_on   4
#define  HBR_enbuffer_on     5

#define foreground_range  2
UINT8  HBR_enbuffer_off_R,HBR_enbuffer_off_G,HBR_enbuffer_off_B;
UINT8  LBR_enbuffer_off_R,LBR_enbuffer_off_G,LBR_enbuffer_off_B;
UINT8  LBR_enbuffer_on_R,LBR_enbuffer_on_G,LBR_enbuffer_on_B;
UINT8  MHL_3G_enbuffer_on_B;
UINT8  HBR_enbuffer_on_R,HBR_enbuffer_on_G,HBR_enbuffer_on_B;

UINT8  HBR_enbuffer_off_R_range,HBR_enbuffer_off_G_range,HBR_enbuffer_off_B_range;
UINT8  LBR_enbuffer_off_R_range,LBR_enbuffer_off_G_range,LBR_enbuffer_off_B_range;
UINT8  LBR_enbuffer_on_R_range,LBR_enbuffer_on_G_range,LBR_enbuffer_on_B_range;
UINT8  MHL_3G_enbuffer_on_B_range;
UINT8  HBR_enbuffer_on_R_range,HBR_enbuffer_on_G_range,HBR_enbuffer_on_B_range;
UINT8  bVerbEQ_toggle;
UINT8 Koffset_result_flag = 1; //0=pass; 1=failed

#define HDMI_AUDIO_PCM				0
#define HDMI_AUDIO_NPCM			1
#define GET_HDMI_AUDIO_TYPE()		(audio_pcm_mode)
#define SET_HDMI_AUDIO_TYPE(x)		(audio_pcm_mode=(x))
UINT8 audio_pcm_mode = HDMI_AUDIO_PCM;
unsigned long ul_audio_freq;


void drvif_Hdmi_Init_CRT_INIT(void);
void drvif_Hdmi_HPD(char channel_index, char high);
char drvif_EDIDEnable(UINT8 ddc_index, char enable);
void drvif_EDID_DDC12_AUTO_Enable(UINT8 ddc_index,char enable);
void drvif_Hdmi_LoadEDID(char channel_index, unsigned char *EDID, int len);
void Hdmi_HdcpInit(void);

UINT8 HDMI_EDID_TABLE[256] = 
{
	0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x54,0x4C,0x01,0x00,0x00,0x00,
	0x0C,0x11,0x01,0x03,0x81,0x46,0x27,0x78,0x8A,0xA5,0x8E,0xA6,0x54,0x4A,0x9C,0x26,
	0x12,0x45,0x46,0xAD,0xCE,0x00,0x81,0x40,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,0x28,
	0x55,0x00,0xB9,0x88,0x21,0x00,0x00,0x1E,0x9A,0x29,0xA0,0xD0,0x51,0x84,0x22,0x30,
	0x50,0x98,0x36,0x00,0xB9,0x88,0x21,0x00,0x00,0x1C,0x00,0x00,0x00,0xFD,0x00,0x32,
	0x4B,0x18,0x3C,0x0B,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
	0x00,0x33,0x32,0x56,0x33,0x48,0x2D,0x48,0x36,0x41,0x0A,0x20,0x20,0x20,0x01,0xE3,
	0x02,0x03,0x21,0x71,0x4E,0x06,0x07,0x02,0x03,0x15,0x96,0x11,0x12,0x13,0x04,0x14,
	0x05,0x1F,0x90,0x23,0x09,0x07,0x07,0x83,0x01,0x00,0x00,0x65,0x03,0x0C,0x00,0x10,
	0x00,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,0xB9,0x88,0x21,
	0x00,0x00,0x18,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,0x00,0xB9,
	0x88,0x21,0x00,0x00,0x9E,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,0x25,
	0x80,0xB9,0x88,0x21,0x00,0x00,0x9E,0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,
	0x28,0x55,0x40,0xB9,0x88,0x21,0x00,0x00,0x1E,0x02,0x3A,0x80,0xD0,0x72,0x38,0x2D,
	0x40,0x10,0x2C,0x45,0x80,0xB9,0x88,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0xD0,	
};

UINT8 hdmi_Cbus_edid[256] = 
{
	//monitor table
	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x4a,0x8b,0x3b,0x2a,0x01,0x01,0x01,0x01,
	0x0d,0x16,0x01,0x03,0x80,0x3c,0x22,0x78,0x2a,0x2c,0xc5,0xa5,0x55,0x54,0xa1,0x27,
	0x0c,0x50,0x54,0xad,0xcf,0x00,0xd1,0xc0,0x81,0x80,0x81,0xc0,0x95,0x00,0xb3,0x00,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1d,0x00,0x72,0x51,0xd0,0x1e,0x20,0x6e,0x28,
	0x55,0x00,0x40,0x84,0x63,0x00,0x00,0x1e,0x66,0x21,0x50,0xb0,0x51,0x00,0x1b,0x30,
	0x40,0x70,0x36,0x00,0x56,0x50,0x21,0x00,0x00,0x1e,0x00,0x00,0x00,0xfc,0x00,0x56,
	0x53,0x32,0x37,0x30,0x42,0x47,0x54,0x57,0x50,0x0a,0x20,0x20,0x00,0x00,0x00,0xfd,
	0x00,0x38,0x4b,0x1e,0x53,0x11,0x00,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0xe7,
	0x02,0x03,0x22,0xf1,0x4f,0xa2,0x14,0x10,0x1f,0x04,0x13,0x03,0x12,0x02,0x11,0x01,
	0x06,0x07,0x15,0x16,0x23,0x09,0x07,0x01,0x83,0x01,0x00,0x00,0x65,0x03,0x0c,0x00,
	0x20,0x00,0x8c,0x0a,0xd0,0x8a,0x20,0xe0,0x2d,0x10,0x10,0x3e,0x96,0x00,0x56,0x50,
	0x21,0x00,0x00,0x18,0x01,0x1d,0x00,0x72,0x51,0xd0,0x1e,0x20,0x6e,0x28,0x55,0x00,
	0x56,0x50,0x21,0x00,0x00,0x1e,0x8c,0x0a,0xd0,0x8a,0x20,0xe0,0x2d,0x10,0x10,0x3e,
	0x96,0x00,0x56,0x50,0x21,0x00,0x00,0x18,0x8c,0x0a,0xd0,0x90,0x20,0x40,0x31,0x20,
	0x0c,0x40,0x55,0x00,0x56,0x50,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2a,
};

/*HDCP key table*/

#if 0 //ng test key
UINT8 HDCP_BKSV[]= { 0xf5, 0xe1, 0x65, 0x44, 0x56 };
UINT8 HDCP_KEY_TABLE[] =
{
0x44,0x3a,0x10,0x1a,0x7d,0x3e,0x45,0x24,0x77,0x49,0x25,0x3b,0x33,0x6d,0x17,0x20,
0x27,0x57,0x1a,0x4f,0x71,0x04,0x13,0x78,0x45,0x12,0x53,0x4d,0x3b,0x34,0x60,0x60,
0x2a,0x16,0x6f,0x2e,0x44,0x5b,0x66,0x50,0x33,0x5e,0x5b,0x3e,0x2c,0x23,0x6a,0x67,
0x37,0x00,0x2d,0x07,0x06,0x27,0x44,0x45,0x48,0x6e,0x1e,0x37,0x55,0x69,0x6a,0x20,
0x02,0x4e,0x23,0x11,0x1c,0x67,0x2c,0x49,0x31,0x47,0x75,0x26,0x69,0x0b,0x05,0x02,
0x10,0x3e,0x3a,0x3f,0x65,0x40,0x74,0x6f,0x6d,0x2b,0x71,0x4b,0x1f,0x1a,0x33,0x68,
0x32,0x48,0x00,0x51,0x2a,0x2a,0x64,0x61,0x75,0x42,0x1f,0x4e,0x6a,0x04,0x23,0x09,
0x0d,0x2c,0x48,0x3d,0x77,0x56,0x23,0x5c,0x14,0x2a,0x45,0x5c,0x3a,0x50,0x71,0x5d,
0x68,0x4d,0x3b,0x14,0x1c,0x04,0x13,0x06,0x5f,0x52,0x5e,0x06,0x40,0x75,0x34,0x5f,
0x5a,0x6e,0x25,0x5c,0x15,0x5b,0x03,0x4e,0x6a,0x4c,0x5f,0x5a,0x1b,0x19,0x07,0x60,
0x56,0x38,0x57,0x4e,0x32,0x3c,0x70,0x5c,0x4a,0x0b,0x68,0x3e,0x2f,0x09,0x5a,0x64,
0x6d,0x4c,0x38,0x31,0x26,0x52,0x65,0x31,0x27,0x75,0x20,0x05,0x6d,0x6d,0x30,0x2b,
0x7c,0x0b,0x05,0x78,0x00,0x16,0x3e,0x46,0x0d,0x59,0x27,0x02,0x03,0x37,0x49,0x4b,
0x5a,0x71,0x26,0x7b,0x6e,0x03,0x48,0x6a,0x42,0x54,0x7c,0x60,0x44,0x7c,0x3d,0x3e,
0x7f,0x51,0x48,0x66,0x25,0x34,0x18,0x11,0x03,0x47,0x60,0x39,0x5f,0x4b,0x3f,0x03,
0x2c,0x7b,0x5f,0x16,0x27,0x5c,0x39,0x4b,0x3c,0x6c,0x4c,0x0f,0x53,0x11,0x5b,0x56,
0x7c,0x06,0x57,0x34,0x46,0x62,0x73,0x42,0x7c,0x19,0x4a,0x31,0x44,0x03,0x46,0x13,
0x50,0x23,0x63,0x31,0x5a,0x6d,0x54,0x26,0x61,0x2b,0x57,0x1c,0x46,0x63,0x16,0x2f,
0x24,0x10,0x69,0x54,0x6d,0x1a,0x1a,0x1a,0x6e,0x39,0x44,0x7a,0x3d,0x15,0x0a,0x22,
0x4c,0x3d,0x43,0x28,0x06,0x6c,0x7b,0x6b,0x79,0x09,0x6a,0x4c,0x1d,0x6f,0x2f,0x21,
};
#else
UINT8 HDCP_BKSV[]= { 0xb7, 0x28, 0xa9, 0x51, 0xd6 };
UINT8 HDCP_KEY_TABLE[] =
{
    0x3a, 0x21, 0x17, 0x06, 0x72, 0x60, 0x3b, 0x6e,     // Key0
    0x0c, 0x58, 0x16, 0x4c, 0x5b, 0x3b, 0x68, 0x4b,     // Key1
    0x2f, 0x7b, 0x5d, 0x64, 0x10, 0x60, 0x71, 0x41,     // Key2
    0x6d, 0x4a, 0x1f, 0x48, 0x35, 0x78, 0x4b, 0x6a,     // Key3
    0x4b, 0x3c, 0x69, 0x2a, 0x20, 0x38, 0x55, 0x1c,     // Key4
    0x10, 0x16, 0x09, 0x5d, 0x0d, 0x07, 0x6e, 0x7a,     // Key5
    0x75, 0x1a, 0x35, 0x55, 0x7b, 0x5c, 0x26, 0x0d,     // Key6
    0x2c, 0x49, 0x1a, 0x1b, 0x3e, 0x55, 0x1f, 0x40,     // Key7
    0x11, 0x24, 0x4b, 0x4a, 0x5d, 0x56, 0x4b, 0x5c,     // Key8
    0x62, 0x70, 0x0b, 0x10, 0x52, 0x3f, 0x2b, 0x4d,     // Key9
    0x5d, 0x06, 0x78, 0x16, 0x72, 0x70, 0x2e, 0x06,     // Key10
    0x3a, 0x2c, 0x60, 0x06, 0x12, 0x6c, 0x32, 0x55,     // Key11
    0x54, 0x62, 0x38, 0x05, 0x13, 0x42, 0x49, 0x40,     // Key12
    0x61, 0x54, 0x28, 0x0c, 0x4a, 0x21, 0x7c, 0x32,     // Key13
    0x4b, 0x74, 0x04, 0x5d, 0x10, 0x69, 0x72, 0x62,     // Key14
    0x5d, 0x77, 0x55, 0x0d, 0x19, 0x79, 0x59, 0x43,     // Key15
    0x0a, 0x5f, 0x0d, 0x50, 0x58, 0x4f, 0x48, 0x42,     // Key16
    0x14, 0x64, 0x65, 0x54, 0x2f, 0x7a, 0x75, 0x04,     // Key17
    0x48, 0x35, 0x00, 0x59, 0x16, 0x0e, 0x2f, 0x4b,     // Key18
    0x4a, 0x7b, 0x04, 0x6c, 0x1a, 0x6d, 0x4b, 0x44,     // Key19
    0x50, 0x11, 0x63, 0x63, 0x47, 0x6e, 0x1a, 0x6b,     // Key20
    0x0f, 0x4c, 0x3e, 0x17, 0x66, 0x0d, 0x3b, 0x3a,     // Key21
    0x47, 0x62, 0x5a, 0x25, 0x3d, 0x0e, 0x1d, 0x55,     // Key22
    0x42, 0x0f, 0x43, 0x60, 0x3e, 0x7e, 0x56, 0x3c,     // Key23
    0x44, 0x4a, 0x44, 0x3b, 0x69, 0x17, 0x1b, 0x47,     // Key24
    0x19, 0x77, 0x2c, 0x7d, 0x72, 0x03, 0x66, 0x53,     // Key25
    0x7f, 0x5a, 0x03, 0x26, 0x17, 0x01, 0x28, 0x5e,     // Key26
    0x09, 0x1d, 0x43, 0x13, 0x35, 0x26, 0x4c, 0x15,     // Key27
    0x1e, 0x7f, 0x4d, 0x6b, 0x4d, 0x52, 0x46, 0x00,     // Key28
    0x3c, 0x38, 0x5c, 0x64, 0x6f, 0x72, 0x78, 0x11,     // Key29
    0x30, 0x65, 0x47, 0x70, 0x7a, 0x3c, 0x38, 0x69,     // Key30
    0x78, 0x26, 0x35, 0x09, 0x37, 0x14, 0x34, 0x57,     // Key31
    0x73, 0x4d, 0x28, 0x28, 0x7e, 0x5a, 0x28, 0x09,     // Key32
    0x08, 0x28, 0x6c, 0x69, 0x42, 0x43, 0x31, 0x15,     // Key33
    0x54, 0x23, 0x60, 0x1c, 0x03, 0x48, 0x7d, 0x48,     // Key34
    0x25, 0x5f, 0x2b, 0x04, 0x6c, 0x42, 0x22, 0x66,     // Key35
    0x11, 0x2a, 0x1a, 0x14, 0x29, 0x68, 0x59, 0x73,     // Key36
    0x76, 0x61, 0x16, 0x00, 0x3e, 0x11, 0x31, 0x20,     // Key37
    0x10, 0x59, 0x13, 0x44, 0x54, 0x32, 0x4f, 0x0e,     // Key38
    0x76, 0x47, 0x13, 0x6f, 0x7e, 0x24, 0x5a, 0x6a,     // Key39
};
#endif

HDMI_CONST VIDEO_DPLL_RATIO_T dpll_ratio[] = {

	{ 	15, 15, 	1, 1	},	// 24 bits
	{ 	12, 15, 	4, 5	},	// 30 bits
	{ 	10, 15, 	2, 3	},	// 36 bits
	{ 	15, 30, 	1, 2	},	// 48 bits
};

HDMI_CONST unsigned int AUDIO_CHANNEL_STATUS[] = {
	44100,
	   0,				   // 000 indicate standard no support
    48000,
    32000,
    22000,
	   0,
	24000,
	   0,
	88200,
	   0,
	96000,
	   0,
	176000,
	   0,
	192000,
	   0,	
};


HDMI_CONST HDMI_AUDIO_PLL_COEFF_T audio_pll_coeff[] = {
	{ 32000, _AUDIO_256_TIMES, 0},
	{ 44100, _AUDIO_256_TIMES, 0},
	{ 48000, _AUDIO_256_TIMES, 0},
	{ 88200, _AUDIO_256_TIMES, 1},
	{ 96000, _AUDIO_256_TIMES, 1},
	{ 176400, _AUDIO_128_TIMES, 2},
	{ 192000, _AUDIO_128_TIMES, 3}
};


static unsigned int ACR_N=0;
unsigned char HDMI_Audio_Conut = 0;
HDMI_AUDIO_PLL_PARAM_T hdmi_audiopll_param[] = {

		{ 2,   20,  2,  8,  1,  0x1D, 0xDC,  "32K"     },//0x1E, 0xB0
		{ 2,   20,  2,  6,  1,  0xFE, 0x7A,  "44.1K"  },//0xFC, 0x68
		{ 2,   22,  2,  6,  1,  0x07, 0x40,  "48K"     },
		{ 2,   20,  1,  6,  1,  0xFE, 0x7A,  "88.2K"  },
		{ 2,   22,  1,  6,  1,  0x07, 0x40,  "96K"     },
		{ 2,   20,  1,  6,  0,  0xFE, 0x7A,  "176.4K" },
		{ 2,   22,  1,  6,  0,  0x07, 0x40,  "192K"    }

};

HDMI_CONST HDMI_PHY_PARAM_T hdmi_phy_param[] = 
{
//RD SD suggestion
			//	M_code	  N_bypass  *CK_LDOA 		   CK_CS		       *EQ_manual		   CDR_KP 		          CDR_KI				    *EQ_bias               PR
			//		N_code	  MD_adj		   *CK_LDOD 	         CK_RS			  *CDR_bias		         *CDR_KP2 		     CDR_KD   *EQ_gain 		     CK_Icp
	
	{3319, 1896,  18,	  2,	   0,	    0,	0x3,		0x3,		0x3,		0x4,		0x2,		0x1,	   (0xf<<2),		0x0,		0x0,		 0x0,      0x0,		0x1 ,	0x6,    0x0,  "200M~350M half rate"},  // 200~350 M
	{ 1896, 948, 	18,	  2,	   0,	    1,	0x3,		0x3,		0x3,		0x4,		0x4,		0x1,	   (0xc<<2),		0x4,		0x0,		 0x0,      0x1,		0x1 ,	0x2,    0x0,  "100M~200M full rate"},	// 100~200 M
	{ 948, 474 ,   18,	  0,	   0,	    2,	0x3,		0x3,		0x3,		0x4,		0x9,		0x1,	   (0xc<<2),		0x0,		0x0,		 0x0,      0x1,		0x1 ,	0x6 ,   0x1,  "50M~100M full rate+DS1"},	// 50~100 M
	{ 474, 237,    18,	  0,	   1,	    2,	0x3,		0x3,		0x3,		0x4,		0x4,		0x1,	   (0xc<<2),		0x0,		0x0,		 0x0,      0x1,		0x1 ,	0x6,    0x2,  "25M~50M full rate+DS2"},	//25~50M			
	{  237, 118,    38,	  0,	   1,	    2,	0x3,		0x3,		0x3,		0x4,		0x4,		0x1,	   (0xc<<2),		0x0,		0x0,		 0x0,      0x1,		0x1 ,	0x6,    0x3,  "12.5M~25M full rate+DS3"}, // 12.5~25M
//	{ 38,	0,	1,	5,	 0x3,		0x3,		0x4,		0x2,		0x4,		0x1,		0x1,		0x0,		       0x0,		 0x0,      0x1,		0x1 ,	0x4, "<12.5M or >350M unknow"}, // <12.5M or >350M
};


HDMI_CONST HDMI_PHY_PARAM_T  mhl_phy_param[] = {
//RD SD suggestion
//	                       M_code	  		N_bypass				CK_LDOA 	     CK_CS			     EQ_adj		    CDR_KP			 CDR_KI	     CDR_KD                EQ_bias              PR
//		                       	N_code	 	              MD_adj				CK_LDOD				CK_RS			CDR_bias		     CDR_KP2		   		          EQ_gain               CK_Icp
//	{  711,  635,      13,	       0,	          1,        	0,	       0x3,	       0x3,		0x3,		       0x6,	      0x2,		0x1,	     (0x0a<<2),0x0,	           0x1,		 0x0,      0x0,		0x1 ,	0x6,    0x0,  "67M~75M half rate"}, // 2010~2250 M  20140604
	{  711,  635,      13,	       0,	          1,        	0,	       0x3,	0x3,		0x3,		       0x7,	0x2,		0x1,	     (0x09<<2),0x0,	    0x0,		 0x0,      0x0,		0x1 ,	0x1,    0x0,  "67M~75M half rate"}, // 2010~2250 M
	{  635,  317,      13,	       0,	          1,       	1,	       0x3,	0x3,		0x3,		       0x7,	0x4,		0x1,	     (0x09<<2),0x4,	    0x0,		 0x0,      0x1,		0x1 ,	0x1,    0x0,  "33.5M~67M full rate"},// 1005~2010 M
	{  317,  237,      28,	       0,	          1,	       2,	       0x3,	0x3,		0x3,		       0x7,	0x9,		0x1,	     (0x09<<2),0x0,	    0x0,		 0x0,      0x1,		0x1 ,	0x1 ,   0x1,  "25M~33.5M full rate+DS1"},	
	{  237,     0,      28,	       0,	          1,        2,	       0x3,	0x3,		0x3,		       0x7,	 0x9,	0x1,	     (0x09<<2),0x0,	    0x0,		 0x0,      0x1,		0x1 ,	0x1 ,   0x1,  "25M~33.5M full rate+DS1"}, // 
};

HDMI_CONST HDMI_PHY_PARAM_T  mhl_phy_pp_param[] = {
//RD SD suggestion
//	                       M_code	  				N_bypass				CK_LDOA 			CK_CS			EQ_adj			  CDR_KP			          CDR_KI	        CDR_KD             EQ_bias             PR
//		                       		 	N_code	 	              MD_adj				CK_LDOD				CK_RS			CDR_bias				CDR_KP2		   		               EQ_gain                  CK_Icp
//	{  711,  635,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x7,		0x2,		0x1,	            0x3c,	0x0,		  0x0,		 0x0,       0x0,		0x1 ,	0x1,    0x0,  "50M~75M half rate"},  // 20140219 skywalk  test 1
//	{  711,  635,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x6,		0x2,		0x1,	            (0x0a<<2), 0x0,		0x1,		      0x0,       0x0,		0x1 ,	0x6,    0x0,  "50M~75M half rate"},  // 20140219 skywalk  test 1
	{  711,  635,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x7,		0x2,		0x1,	            (0x09<<2), 0x0,		0x0,		      0x0,       0x0,		0x1 ,	0x1,    0x0,  "50M~75M half rate"},  // 20140604
	{  635,  317,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x7,		0x2,		0x1,	            0x28,	  0x0,		0x0,		      0x0,       0x0,		0x1 ,	0x1,    0x0,  "50M~75M half rate"}, 
	{  317,  237,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x7,		0x2,		0x1,	            0x28,	  0x0,		0x0,		      0x0,       0x0,		0x1 ,	0x1,    0x0,  "50M~75M half rate"}, 
	{  237,     0,         18,	                  0,	             1,	      0,	       0x3,	0x3,		       0x3,	0x7,		0x2,		0x1,	            0x28,	  0x0,		0x0,		      0x0,       0x0,		0x1 ,	0x1,    0x0,  "50M~75M half rate"}, 
};

char Hdmi_IsbReady(void)
{
	//if( (REG_CK_RESULT_get_ck_md_ok(rtd_inl(REG_CK_RESULT_reg)) == 0)|((rtd_inl(HDMI_CLKDETSR_reg)&HDMI_CLKDETSR_clk_in_target_mask) == 0)) {
	if( (REG_CK_RESULT_get_ck_md_ok(rtd_inl(REG_CK_RESULT_reg)) == 0)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

void Hdmi_TriggerbMeasurement(void)
{
	rtd_maskl(REG_CK_RESULT_reg,~REG_CK_RESULT_ck_md_ok_mask, REG_CK_RESULT_ck_md_ok_mask);			//cloud modify for magellan2013 0108  Restart measure b	
	rtd_maskl(HDMI_CLKDETCR_reg,~_BIT0, 0);			//PMM clk detect function disable
	rtd_maskl(HDMI_CLKDETSR_reg,~_BIT0, _BIT0);			//clr PMM clk detect flag
	rtd_maskl(HDMI_CLKDETCR_reg,~_BIT0, _BIT0);			//PMM clk detect function enable	
}


int Hdmi_get_b_value(void) {
UINT8  bTimeout = 5;
int wValue;
	rtd_maskl(REG_CK_RESULT_reg,~REG_CK_RESULT_ck_md_ok_mask,REG_CK_RESULT_ck_md_ok_mask);
	do
	{
		HDMI_DELAYMS(1);
		bTimeout --;
	}while((!REG_CK_RESULT_get_ck_md_ok(rtd_inl(REG_CK_RESULT_reg)))&&(bTimeout));

	//HDMI_PRINTF("Hdmi_get_b_value = %d \n",bTimeout); 
	if(bTimeout !=0)
	{
		wValue = REG_CK_RESULT_get_ck_md_count(rtd_inl(REG_CK_RESULT_reg));
	}
	else
	{
		wValue = 0;
	}
	return wValue ;  //cloud modify for magellan2013 0108

}

UINT8 Hdmi_DFE_EQ_Set(UINT32 b)
{
	UINT8 dfe_mode;
//	UINT32  bClock_Boundry_2G,bClock_Boundry_1p3G;

	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask,HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask);	//DFE register release



#if MHL_SUPPORT
	if ( GET_ISMHL() )
	{
		dfe_mode = 3;
		if( MHL_IsPPMode() )
		{
//			bClock_Boundry_2G =    474 ;//1895/4   ;
//			bClock_Boundry_1p3G = 320;//1280 /4;
			HDMI_PRINTF("[MHL] Hdmi_DFE_EQ_Set PPmode   \n");
		}
		else
		{
//			bClock_Boundry_2G =   632;// 1895/3   ;
//			bClock_Boundry_1p3G = 427;   //1280 /3;
			HDMI_PRINTF("[MHL] Hdmi_DFE_EQ_Set  24bit mode  \n");
		}
	}else
	{
		if (b>430 && b < 1060 )  // 45M~1.1G set mode 2 
    		{
        		dfe_mode = 2;
		}
		else
		{
        		dfe_mode = 3;
    		}
		//HDMI 
//		bClock_Boundry_2G = 1895;
//		bClock_Boundry_1p3G =  1280 ;
	}
#else
	{
	    	if (b>430 && b < 1060 )  // 45M~1.1G set mode 2 
    		{
        		dfe_mode = 2;
    		}
    		else
    		{
        		dfe_mode = 3;
    		}
		//HDMI 
//		bClock_Boundry_2G = 1895;
//		bClock_Boundry_1p3G =  1280 ;
	}
#endif
	//HDMI_PRINTF("DFE Mode = %d\n",dfe_mode);	

	if ( GET_IC_VERSION() != VERSION_A)
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_back_koff_en, R_EQ_back_koff_en);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_back_koff_en, G_EQ_back_koff_en);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_back_koff_en, B_EQ_back_koff_en);		// EQ1_output short disable // see Garren 0411 mail
	}

	rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_BG_Range_mask,R_KOFF_BG_Range(3));	//R foreground K Off range
	rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_BG_Range_mask,G_KOFF_BG_Range(3));	//G foreground K Off range
	rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_BG_Range_mask,B_KOFF_BG_Range(3));	//B foreground K Off range

	//=========DEF initial===========	
	//rtd_maskl(HDMIPHY_REG_R_5_8_reg,~r_DFE_RVTH_mask,r_DFE_RVTH(3));				//VTH setting
	//rtd_maskl(HDMIPHY_REG_G_5_8_reg,~g_DFE_RVTH_mask,g_DFE_RVTH(3));				//VTH setting
	//rtd_maskl(HDMIPHY_REG_B_5_8_reg,~b_DFE_RVTH_mask,b_DFE_RVTH(3));				//VTH setting

	//rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_de_packet_en_lane0_mask,REG_DFE_INIT1_L0_de_packet_en_lane0(1));	//data packet area disable DFE calibration
	//rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_de_packet_en_lane2_mask,REG_DFE_INIT1_L1_de_packet_en_lane2(1));	
	//rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_de_packet_en_lane2_mask,REG_DFE_INIT1_L2_de_packet_en_lane2(1));
/*
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_enbuffer3_mask, HDMIPHY_REG_R_5_8_enbuffer3(1)); // 20140304
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_enbuffer3_mask, HDMIPHY_REG_G_5_8_enbuffer3(1)); // 20140304
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_enbuffer3_mask, HDMIPHY_REG_B_5_8_enbuffer3(1)); // 20140304
	*/
	/*
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_tap0_bias_cur_mask, HDMIPHY_REG_R_9_12_tap0_bias_cur(2)); // 20140304
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~HDMIPHY_REG_G_9_12_tap0_bias_cur_mask, HDMIPHY_REG_G_9_12_tap0_bias_cur(2)); // 20140304
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~HDMIPHY_REG_B_9_12_tap0_bias_cur_mask, HDMIPHY_REG_B_9_12_tap0_bias_cur(2)); // 20140304
	*/
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_adapt_mode_mask,REG_DFE_MODE_adapt_mode(dfe_mode));	//adaptive mode sel 
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_gray_en_mask,REG_DFE_MODE_gray_en(0x1e));	//gray code 0xA1--> 0x1e
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_transition_only_mask,REG_DFE_MODE_transition_only(1));	//transition mode enable
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_le_auto_reload_mask,0);	//auto reload enable
	//
	//cloud test for DFE 20140227
	//rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_cs_mode_mask,REG_DFE_MODE_cs_mode(1));	//Current step mode select
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_cs_mode_mask,REG_DFE_MODE_cs_mode(0));
	//cloud test for dfe  20140227
	//rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_set_cs_manual_lane0_mask,REG_DFE_INIT1_L0_dfe_set_cs_manual_lane0(0));	//Current step mode select	//Auto
	//rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_set_cs_manual_lane1_mask,REG_DFE_INIT1_L1_dfe_set_cs_manual_lane1(0));	//Current step mode select
	//rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_set_cs_manual_lane2_mask,REG_DFE_INIT1_L2_dfe_set_cs_manual_lane2(0));	//Current step mode select

	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_set_cs_manual_lane0_mask,REG_DFE_INIT1_L0_dfe_set_cs_manual_lane0(1));	
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_set_cs_manual_lane1_mask,REG_DFE_INIT1_L1_dfe_set_cs_manual_lane1(1));	//Current step mode select
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_set_cs_manual_lane2_mask,REG_DFE_INIT1_L2_dfe_set_cs_manual_lane2(1));

	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0_mask,REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0(1));	
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1_mask,REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1(1));	//buffer mode select
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2_mask,REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2(1));

	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_set_cs_lane0_mask,REG_DFE_INIT1_L0_dfe_set_cs_lane0(1));	//Current step set
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_set_cs_lane1_mask,REG_DFE_INIT1_L1_dfe_set_cs_lane1(1));	//Current step set
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_set_cs_lane2_mask,REG_DFE_INIT1_L2_dfe_set_cs_lane2(1));	//Current step set	

	//rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0_mask,REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0(1));	//enable buffer		//Auto
	//rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1_mask,REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1(1));	//enable buffer
	//rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2_mask,REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2(1));	//enable buffer

	//rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_en_buffer_lane0_mask,REG_DFE_INIT1_L0_dfe_en_buffer_lane0(0));	//enable buffer step
	//rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_en_buffer_lane1_mask,REG_DFE_INIT1_L1_dfe_en_buffer_lane1(0));	//enable buffer step
	//rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_en_buffer_lane2_mask,REG_DFE_INIT1_L2_dfe_en_buffer_lane2(0));	//enable buffer step	

	//limit
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap0_max_mask,REG_DFE_LIMIT0_tap0_max(0x12));	//TAP0_MAX  0xf 0x12
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap1_min_mask,REG_DFE_LIMIT0_tap1_min(0x2e));	//  cloud modify 20140325 TAP1_MIN 0x37
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap2_max_mask,REG_DFE_LIMIT0_tap2_max(0xA));	//TAP2_MAX 
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap2_min_mask,REG_DFE_LIMIT0_tap2_min(0x19));	//TAP2_MIN
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap3_max_mask,REG_DFE_LIMIT0_tap3_max(6));	//TAP3_MAX
	rtd_maskl(REG_DFE_LIMIT0_reg,~REG_DFE_LIMIT0_tap3_min_mask,REG_DFE_LIMIT0_tap3_min(0x19));	//TAP3_MIN
	rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_tap4_max_mask,REG_DFE_LIMIT1_tap4_max(6));	//TAP4_MAX
	rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_tap4_min_mask,REG_DFE_LIMIT1_tap4_min(0x19));	//TAP4_MIN

	//threshold
	rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_tap0_threshold_mask,REG_DFE_LIMIT1_tap0_threshold(0x0));	//TAP0 threshold 0xc
	rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_vth_threshold_mask, REG_DFE_LIMIT1_vth_threshold(0x0)); // 20140304  0x05 

	//divisor
	rtd_maskl(REG_DFE_LIMIT2_reg,~REG_DFE_LIMIT2_servo_divisor_mask,REG_DFE_LIMIT2_servo_divisor(0x28));	//servo divisor
	rtd_maskl(REG_DFE_LIMIT2_reg,~REG_DFE_LIMIT2_tap_divisor_mask,REG_DFE_LIMIT2_tap_divisor(0xa));	//tap divisor
	rtd_maskl(REG_DFE_LIMIT2_reg,~REG_DFE_LIMIT2_vth_divisor_mask,REG_DFE_LIMIT2_vth_divisor(0xf));	//Vth divisor
	//delay
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_tap1_delay_mask,REG_DFE_MODE_tap1_delay(7));	//tap1 delay
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_tap24_delay_mask,REG_DFE_MODE_tap24_delay(7));	//tap24 delay
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_servo_delay_mask,1);	//servo delay  cloud modify 2014 0326 set 1 

	//lane timer enable
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_timer_ctrl_en_lane0_mask,REG_DFE_EN_L0_timer_ctrl_en_lane0(1));	//lane0 timer enable
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_timer_ctrl_en_lane1_mask,REG_DFE_EN_L1_timer_ctrl_en_lane1(1));	//lane1 timer enable
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_timer_ctrl_en_lane2_mask,REG_DFE_EN_L2_timer_ctrl_en_lane2(1));	//lane2 timer enable
	//run-length detect threshold
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_rl_threshold_lane0_mask,REG_DFE_EN_L0_rl_threshold_lane0(1));	//lane0 run-length detect threshold
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_rl_threshold_lane1_mask,REG_DFE_EN_L1_rl_threshold_lane1(1));	//lane1 run-length detect threshold
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_rl_threshold_lane2_mask,REG_DFE_EN_L2_rl_threshold_lane2(1));	//lane2 run-length detect threshold
	//run-length detect enable
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_rl_det_mode_lane0_mask,REG_DFE_EN_L0_rl_det_mode_lane0(1));	//lane0 run-length mode
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_rl_det_mode_lane1_mask,REG_DFE_EN_L1_rl_det_mode_lane1(1));	//lane1 run-length mode
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_rl_det_mode_lane2_mask,REG_DFE_EN_L2_rl_det_mode_lane2(1));	//lane2 run-length mode
      //20140319 test
	rtd_maskl(REG_DFE_MODE_reg,~(REG_DFE_MODE_servo_notrans_mask|REG_DFE_MODE_tap0_notrans_mask),REG_DFE_MODE_servo_notrans_mask|REG_DFE_MODE_tap0_notrans_mask);	//notrans

      //
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_rl_det_en_lane0_mask,0);	//lane0 run-length detect disable
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_rl_det_en_lane1_mask,0);	//lane1 run-length detect disable
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_rl_det_en_lane2_mask,0);	//lane2 run-length detect disable

	//Gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_tap0_gain_mask,REG_DFE_GAIN_tap0_gain(2));	//tap0 gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_tap1_gain_mask,REG_DFE_GAIN_tap1_gain(2));	//tap1 gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_tap2_gain_mask,REG_DFE_GAIN_tap2_gain(1));	//tap2 gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_tap3_gain_mask,REG_DFE_GAIN_tap3_gain(1));	//tap3 gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_tap4_gain_mask,REG_DFE_GAIN_tap4_gain(1));	//tap4 gain
	rtd_maskl(REG_DFE_GAIN_reg,~REG_DFE_GAIN_servo_gain_mask,REG_DFE_GAIN_servo_gain(1));	//servo gain

	//LE
    //20140306  test 
    /*
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_le_min_lane0_mask,REG_DFE_EN_L0_le_min_lane0(0xc));	//lane0 LE coefficient min		//0x18
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_le_min_lane1_mask,REG_DFE_EN_L1_le_min_lane1(0xc));	//lane1 LE coefficient min		//0x18
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_le_min_lane2_mask,REG_DFE_EN_L2_le_min_lane2(0xc));	//lane2 LE coefficient min		//0x18
    */
    
    rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_le_min_lane0_mask,REG_DFE_EN_L0_le_min_lane0(0xf));	//lane0 LE coefficient min		//0x18
    rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_le_min_lane1_mask,REG_DFE_EN_L1_le_min_lane1(0xf));	//lane1 LE coefficient min		//0x18
    rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_le_min_lane2_mask,REG_DFE_EN_L2_le_min_lane2(0xf));	//lane2 LE coefficient min		//0x18
    
#if 0 
	if (b<450)
	{
		if (dfe_mode == 2)
		{
			rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_le_init_lane0_mask,REG_DFE_EN_L0_le_init_lane0(0x3)),	//lane0  LE coefficient initial
			rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_le_init_lane1_mask,REG_DFE_EN_L1_le_init_lane1(0x3)),	//lane1  LE coefficient initial
			rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_le_init_lane2_mask,REG_DFE_EN_L2_le_init_lane2(0x3));	//lane2  LE coefficient initial
		}
	}

#endif
	

	//servo loop&Tap initial value
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_servo_init_lane0_mask,REG_DFE_INIT0_L0_servo_init_lane0(0xf));	//lane0 servo initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_servo_init_lane1_mask,REG_DFE_INIT0_L1_servo_init_lane1(0xf));	//lane1 servo initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_servo_init_lane2_mask,REG_DFE_INIT0_L2_servo_init_lane2(0xf));	//lane2 servo initial

	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap0_init_lane0_mask,REG_DFE_INIT0_L0_tap0_init_lane0(0xf));	//lane0 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap0_init_lane1_mask,REG_DFE_INIT0_L1_tap0_init_lane1(0xf));	//lane1 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap0_init_lane2_mask,REG_DFE_INIT0_L2_tap0_init_lane2(0xf));	//lane2 tap0 initial	//0xc

	if (dfe_mode == 2)
	{
	// mode 2   tap1 = tap1   LE = LE set in tap1 initial 
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap1_init_lane0_mask,REG_DFE_INIT0_L0_tap1_init_lane0(0x0));	//lane0 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap1_init_lane1_mask,REG_DFE_INIT0_L1_tap1_init_lane1(0x0));	//lane1 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap1_init_lane2_mask,REG_DFE_INIT0_L2_tap1_init_lane2(0x0));	//lane2 tap1 initial

	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_le_init_lane0_mask,REG_DFE_EN_L0_le_init_lane0(0x7));	//lane0  LE coefficient initial
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_le_init_lane1_mask,REG_DFE_EN_L1_le_init_lane1(0x7));	//lane1  LE coefficient initial
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_le_init_lane2_mask,REG_DFE_EN_L2_le_init_lane2(0x7));	//lane2  LE coefficient initial
	}
	else    // mode 3 
	{
	// mode 3   tap1 = tap1 +LE set in tap1 initial 
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap1_init_lane0_mask,REG_DFE_INIT0_L0_tap1_init_lane0(0xc));	//lane0 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap1_init_lane1_mask,REG_DFE_INIT0_L1_tap1_init_lane1(0xc));	//lane1 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap1_init_lane2_mask,REG_DFE_INIT0_L2_tap1_init_lane2(0xc));	//lane2 tap1 initial
	}
#if 0
	else	
	{

	if (b<450)
	{
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap1_init_lane0_mask,REG_DFE_INIT0_L0_tap1_init_lane0(0x1)),	//lane0 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap1_init_lane1_mask,REG_DFE_INIT0_L1_tap1_init_lane1(0x1)),	//lane1 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap1_init_lane2_mask,REG_DFE_INIT0_L2_tap1_init_lane2(0x1));	//lane2 tap1 initial
	}
	else

	{
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap1_init_lane0_mask,REG_DFE_INIT0_L0_tap1_init_lane0(0xc)),	//lane0 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap1_init_lane1_mask,REG_DFE_INIT0_L1_tap1_init_lane1(0xc)),	//lane1 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap1_init_lane2_mask,REG_DFE_INIT0_L2_tap1_init_lane2(0xc));	//lane2 tap1 initial
	}
	}
#endif
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap2_init_lane0_mask,0);		//lane0 tap2 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap2_init_lane1_mask,0);		//lane1 tap2 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap2_init_lane2_mask,0);		//lane2 tap2 initial

	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap3_init_lane0_mask,0);		//lane0 tap3 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap3_init_lane1_mask,0);		//lane1 tap3 initial	
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap3_init_lane2_mask,0);		//lane2 tap3 initial	

	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_vth_init_lane0_mask,REG_DFE_INIT0_L0_vth_init_lane0(5));		//lane0 Vth initial	//8
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_vth_init_lane1_mask,REG_DFE_INIT0_L1_vth_init_lane1(5));		//lane1 Vth initial	//8
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_vth_init_lane2_mask,REG_DFE_INIT0_L2_vth_init_lane2(5));		//lane2 Vth initial	//8
	//Load initial value
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_load_in_init_lane0_mask,0);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_load_in_init_lane1_mask,0);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_load_in_init_lane2_mask,0);		//lane2  initial load
	HDMI_DELAYMS(1);
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_load_in_init_lane0_mask,REG_DFE_INIT1_L0_load_in_init_lane0(0xff));		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_load_in_init_lane1_mask,REG_DFE_INIT1_L1_load_in_init_lane1(0xff));		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_load_in_init_lane2_mask,REG_DFE_INIT1_L2_load_in_init_lane2(0xff));		//lane2  initial load
	HDMI_DELAYMS(1);
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_load_in_init_lane0_mask,0);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_load_in_init_lane1_mask,0);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_load_in_init_lane2_mask,0);		//lane2  initial load

	//LE Gain set
	//rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_BIAS_ENHANCE_mask,0);		//R bias enhance
	//rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_BIAS_ENHANCE_mask,0);		//G bias enhance
	//rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_BIAS_ENHANCE_mask,0);		//B bias enhance

  
    rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_vth_min_mask,REG_DFE_LIMIT1_vth_min(0));	//Vth min 2014 0326 set 0 judge Vth 
    

	//rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_vth_min_mask,REG_DFE_LIMIT1_vth_min((b>bClock_Boundry_2G)?1:1));	//Vth min 6 for over 2GHz
	rtd_maskl(REG_DFE_LIMIT1_reg,~REG_DFE_LIMIT1_vth_dis_buf_range_mask,0);	//Vth_dis_buf_range 0

	//PHY Tap en
//    if (b>bClock_Boundry_1p3G)	//>1.35G
	{
		rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_TAPEN4321,R_DFE_TAPEN4321);		//R tap1~4 enable
		rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_TAPEN4321,G_DFE_TAPEN4321);		//G tap1~4 enable
		rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_TAPEN4321,B_DFE_TAPEN4321);		//B tap1~4 enable
	}
	/*
	else		//<1.35G
	{
		rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_TAPEN4321,R_DFE_TAPEN21);	//R tap1~2 enable
		rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_TAPEN4321,G_DFE_TAPEN21);	//G tap1~2 enable
		rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_TAPEN4321,B_DFE_TAPEN21);	//B tap1~2 enable
	}
    */
	//DFE reset (write initial value) 20140109
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_dfe_adapt_rstb_mask,0);		//lane0~2 reset adaptive
	HDMI_DELAYMS(1);
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_dfe_adapt_rstb_mask,REG_DFE_MODE_dfe_adapt_rstb(0xf));		//lane0~2 reset adaptive
	//PHY adaptive en
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_ADAPT_EN,R_DFE_ADAPT_EN);	//R adaptive enable
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_ADAPT_EN,G_DFE_ADAPT_EN);	//G adaptive enable
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_ADAPT_EN,B_DFE_ADAPT_EN);	//B adaptive enable

	return dfe_mode;

}
//***********************************************************************
//Function name :  void Hdmi_DFE_EQ_Write_back(UINT8 lane)
//PARAM : lane 0 1 2   RGB channel 
//RETURN : none 
//descript :release MAC reset 
//***********************************************************************
void Hdmi_DFE_EQ_Write_back(UINT8 lane)
{
		UINT8 max;

		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);	
		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(0));
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		max=get_Tap0_max(rtd_inl(REG_DFE_READBACK_reg));
		HDMI_PRINTF("[HDMI] Lane%d Manual Tap0 = 0x%02x  ",lane,max);
		rtd_maskl((REG_DFE_INIT0_L0_reg+(0x10*lane)),~REG_DFE_INIT0_L0_tap0_init_lane0_mask,max<<REG_DFE_INIT0_L0_tap0_init_lane0_shift);	//lane0 tap1 initial
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,0);		//lane0  initial load
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,load_in_init_lane0_tap0);		//lane0  initial load
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,0);		//lane0  initial load	
//Channel B LE set the max value, for trace attenuation			
		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);	
		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(4));
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		max=get_LEQ_max(rtd_inl(REG_DFE_READBACK_reg));
		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);
		rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(2));
		udelay(10);	//1000
		//HDMI_PRINTF("delay  \n");
		max += get_Tap1_max(rtd_inl(REG_DFE_READBACK_reg));
		HDMI_PRINTF("Lane%d Manual LE = 0x%02x\n",lane,max);
		rtd_maskl((REG_DFE_INIT0_L0_reg+(0x10*lane)),~REG_DFE_INIT0_L0_tap1_init_lane0_mask,max<<REG_DFE_INIT0_L0_tap1_init_lane0_shift);	//lane0 tap1 initial
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,0);		//lane0  initial load
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,load_in_init_lane0_tap1);		//lane0  initial load
		udelay(10);		//1000
		//HDMI_PRINTF("delay  \n");
		rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,0);		//lane0  initial load
}
//***********************************************************************
//Function name :  void OPEN_RST_MAC(void)
//PARAM : tmds clock
//RETURN : none 
//descript :release MAC reset 
//***********************************************************************
void OPEN_RST_MAC(void)
{
	rtd_maskl(TMDS_Z0CC_reg,~TMDS_Z0CC_hde_mask,TMDS_Z0CC_hde(1));
	udelay(100);
	//HDMI_PRINTF("0xb800d01c=0x%x--MAC reset\n",rtd_inl(TMDS_PWDCTL_reg));
	rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),(TMDS_PWDCTL_ebip(1)|TMDS_PWDCTL_egip(1)|TMDS_PWDCTL_erip(1)|TMDS_PWDCTL_ecc(1)));                         //enable TMDS input
	//HDMI_PRINTF("0xb800d01c=0x%x--MAC set\n",rtd_inl(TMDS_PWDCTL_reg));
	rtd_maskl(TMDS_DPC_SET0_reg,~(TMDS_DPC_SET0_dpc_en_mask),TMDS_DPC_SET0_dpc_en_mask);  
}

void K_Offset_Manual(void)
{
//    HDMI_PRINTF("[HDMI]K_Offset_Manual\n");
    rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(k_offset_manual));
    rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(k_offset_manual));
    rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(k_offset_manual));
    rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(k_offset_manual_range));	
    rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(k_offset_manual_range));	
    rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(k_offset_manual_range));
}

void FORGROUND_OFFSET_MODE(UINT8 mode)
{
    if(rtd_inl(SC_VERID_reg)>VERSION_B) //for verC
    {
        // auto k fore ground offset 
        if (mode == HBR_enbuffer_off)
        {
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(HBR_enbuffer_off_R));
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(HBR_enbuffer_off_G));
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(HBR_enbuffer_off_B));
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(HBR_enbuffer_off_R_range));	
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(HBR_enbuffer_off_G_range));	
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(HBR_enbuffer_off_B_range));
        }
        else if (mode == LBR_enbuffer_off)
        {
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(LBR_enbuffer_off_R));
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(LBR_enbuffer_off_G));
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(LBR_enbuffer_off_B));
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(LBR_enbuffer_off_R_range));	
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(LBR_enbuffer_off_G_range));	
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(LBR_enbuffer_off_B_range));
        }
        else if (mode == LBR_enbuffer_on)
        {
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(LBR_enbuffer_on_R));
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(LBR_enbuffer_on_G));
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(LBR_enbuffer_on_B));
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(LBR_enbuffer_on_R_range));	
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(LBR_enbuffer_on_G_range));	
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(LBR_enbuffer_on_B_range));
        }
        else if (mode == MHL_3G_enbuffer_on)
        {
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(MHL_3G_enbuffer_on_B));
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(MHL_3G_enbuffer_on_B_range));
        }
        else if (mode == HBR_enbuffer_on)
        {
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(HBR_enbuffer_on_R));
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(HBR_enbuffer_on_G));
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(HBR_enbuffer_on_B));
            rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(HBR_enbuffer_on_R_range));	
            rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(HBR_enbuffer_on_G_range));	
            rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(HBR_enbuffer_on_B_range));
        }
    }
    else   // default offset setting
    {
    // fix  fore ground offset 
         K_Offset_Manual();
    }
}


void EQ3_Enable_buffer_Setting(UINT8 enable)
{
	if (enable ==1)
	{
		rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_enbuffer3_mask, HDMIPHY_REG_R_5_8_enbuffer3(1)); // 20140304
		rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_enbuffer3_mask, HDMIPHY_REG_G_5_8_enbuffer3(1)); // 20140304
		rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_enbuffer3_mask, HDMIPHY_REG_B_5_8_enbuffer3(1)); // 20140304
	}
	else
	{
		rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_enbuffer3_mask, HDMIPHY_REG_R_5_8_enbuffer3(0)); // 20140304
		rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_enbuffer3_mask, HDMIPHY_REG_G_5_8_enbuffer3(0)); // 20140304
		rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_enbuffer3_mask, HDMIPHY_REG_B_5_8_enbuffer3(0)); // 20140304
	}
}

void EQ_Enable_buffer_bit22(UINT8 enable)
{
	if ( enable )
	{
            rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_bit22_mask, HDMIPHY_REG_R_5_8_bit22(1));
            rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_bit22_mask, HDMIPHY_REG_G_5_8_bit22(1));
            rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_bit22_mask, HDMIPHY_REG_B_5_8_bit22(1));
	}
	else
	{
	    rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_bit22_mask, HDMIPHY_REG_R_5_8_bit22(0));
           rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_bit22_mask, HDMIPHY_REG_G_5_8_bit22(0));
           rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_bit22_mask, HDMIPHY_REG_B_5_8_bit22(0));
	}
}

//***********************************************************************
//Function name : void EQ_HBR_Setting(void)
//PARAM : tmds clock
//RETURN : none 
//descript : EQsirius 1.2G LBR boosterpoint  2.2G HBR booster point
//***********************************************************************
void EQ_HBR_Setting_EQ_bias_1X(void)
{

        rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_bias_current_mask,R_EQ_bias_current(6));		//R EQ bias 6 for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_bias_current_mask,G_EQ_bias_current(6));			//G EQ bias 6 for over 1.1 GHz
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_bias_current_mask,B_EQ_bias_current(6));//B EQ bias 6 for over 1.1 GHz
	   
        rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_Rhase_Routator_Resistor,R_Rhase_Routator_Resistor),		//R PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_Rhase_Routator_Resistor,G_Rhase_Routator_Resistor),		//G PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_Rhase_Routator_Resistor,B_Rhase_Routator_Resistor),		//B PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_HBR,R_EQ_HBR),		//R High bit rate  for over 1.1GHz	
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_HBR,G_EQ_HBR),	//G High bit rate  for over 1.1GHz	
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_HBR,B_EQ_HBR);		//B High bit rate  for over 1.1GHz
}
//***********************************************************************
//Function name : void EQ_HBR_Setting(void)
//PARAM : tmds clock
//RETURN : none 
//descript : EQsirius 1.2G LBR boosterpoint  2.2G HBR booster point
//***********************************************************************
void EQ_HBR_Setting_EQ_bias_1p33X(void)
{

   	  rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_bias_current_mask,R_EQ_bias_current(7));			//R EQ bias 6 for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_bias_current_mask,G_EQ_bias_current(7));			//G EQ bias 6 for over 1.1 GHz
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_bias_current_mask,B_EQ_bias_current(7));	

        rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_Rhase_Routator_Resistor,R_Rhase_Routator_Resistor),		//R PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_Rhase_Routator_Resistor,G_Rhase_Routator_Resistor),		//G PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_Rhase_Routator_Resistor,B_Rhase_Routator_Resistor),		//B PRR for over 1.1GHz
        rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_HBR,R_EQ_HBR),		//R High bit rate  for over 1.1GHz	
        rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_HBR,G_EQ_HBR),	//G High bit rate  for over 1.1GHz	
        rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_HBR,B_EQ_HBR);		//B High bit rate  for over 1.1GHz
}
//***********************************************************************
//Function name : void EQ_HBR_Setting(void)
//PARAM : tmds clock
//RETURN : none 
//descript : EQsirius 1.2G LBR boosterpoint  2.2G HBR booster point
//***********************************************************************
void EQ_LBR_Setting(void)
{
	/* test
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_bias_current_mask,R_EQ_bias_current(0)),			//R EQ bias 0 for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_bias_current_mask,G_EQ_bias_current(0)),			//G EQ bias 0 for below 1.1 GHz
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_bias_current_mask,B_EQ_bias_current(0)),			//B EQ bias 0 for below 1.1 GHz
	*/
#if 1
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_bias_current_mask,R_EQ_bias_current(5)),			//R EQ bias 0 for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_bias_current_mask,G_EQ_bias_current(5)),			//G EQ bias 0 for below 1.1 GHz
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_bias_current_mask,B_EQ_bias_current(5)),			//B EQ bias 0 for below 1.1 GHz
#endif
#if 0
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_bias_current_mask,R_EQ_bias_current(3)),			//R EQ bias 0 for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_bias_current_mask,G_EQ_bias_current(3)),			//G EQ bias 0 for below 1.1 GHz
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_bias_current_mask,B_EQ_bias_current(3)),			//B EQ bias 0 for below 1.1 GHz
#endif


	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_Rhase_Routator_Resistor,0),		//R PRR for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_Rhase_Routator_Resistor,0),		//G PRR for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_Rhase_Routator_Resistor,0),		//B PRR for below 1.1GHz
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_EQ_HBR,0),		//R low bit rate  for below 1.1GHz	
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_EQ_HBR,0),		//G low bit rate  for below 1.1GHz	
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_EQ_HBR,0);		//B low bit rate  for below 1.1GHz
}


void hdmi_Phy_EQ_Toggle(void)	
{
    //	 bVerbEQ_toggle ++;
    if((bVerbEQ_toggle%2))
    {
        EQ3_Enable_buffer_Setting(1);
        FORGROUND_OFFSET_MODE(HBR_enbuffer_on);
        EQ_HBR_Setting_EQ_bias_1X();
        //HDMI_PRINTF("hdmi_Phy_EQ_Toggle  buffer on \n ");
    }
    else
    {
        EQ3_Enable_buffer_Setting(0);
        FORGROUND_OFFSET_MODE(HBR_enbuffer_off);
        EQ_HBR_Setting_EQ_bias_1X();
        //HDMI_PRINTF("hdmi_Phy_EQ_Toggle  buffer off\n ");			
    }
    bVerbEQ_toggle ++;

}

//***********************************************************************
//Function name :  void EQ_bias_band_setting(UINT32 b)
//PARAM : tmds clock
//RETURN : none 
//descript : EQ bias gain setting 
//***********************************************************************

void EQ_bias_band_setting(UINT32 b)
{
	UINT16  bClock_Boundry_point ,bclock_75M_point;
#if MHL_SUPPORT
	if (!GET_ISMHL())
	{
   		bClock_Boundry_point = 2200 ;//1900 ; // 2G 1042;//2150;//1042;
		bclock_75M_point = 720;
	}
	else
	{
		if(MHL_IsPPMode())  // pp mode 
		{
			bClock_Boundry_point = 550;//347;
			bclock_75M_point = 180;
		}
		else
		{
			bClock_Boundry_point = 700;//347;
			bclock_75M_point = 240;
		}
	}
#else
  	bClock_Boundry_point = 2200;   //hdmi
	bclock_75M_point = 720;
#endif
	if (b>bClock_Boundry_point)	//>2.25G    HBR
	{
	#if MHL_SUPPORT
		if(GET_ISMHL())  //MHL
		{
			EQ3_Enable_buffer_Setting(1);  // for min swing setting
			FORGROUND_OFFSET_MODE(MHL_3G_enbuffer_on);
			EQ_HBR_Setting_EQ_bias_1p33X();
			HDMI_PRINTF("[HDMI] MHL EQ_HBR_Setting_EQ_bias_1p33X\n");
		} 
		else               //HDMI
		{    
		 #if  VER_B_DC_BUFFER_FLOW
		    	if(rtd_inl(SC_VERID_reg) < 0x63300002)  // for Ver C 
		 	 {
        			hdmi_Phy_EQ_Toggle();
		 	 }
			 else  //for verA & VerB 
		 #endif
			 {
                            EQ3_Enable_buffer_Setting(0);
                            FORGROUND_OFFSET_MODE(HBR_enbuffer_off);
                            EQ_HBR_Setting_EQ_bias_1X();
                            //HDMI_PRINTF("EQ_HBR_Setting\n ");
			 }
		}
       #else
	   #if  VER_B_DC_BUFFER_FLOW
                 if(rtd_inl(SC_VERID_reg) < 0x63300002)  // for Ver C 
		 	 {
        			hdmi_Phy_EQ_Toggle();
		 	 }
			 else  //for verA & VerB 
	  #endif
			 {
                            EQ3_Enable_buffer_Setting(0);
                            FORGROUND_OFFSET_MODE(HBR_enbuffer_off);
                            EQ_HBR_Setting_EQ_bias_1X();
	  			//HDMI_PRINTF("EQ_HBR_Setting\n ");
			 }
	#endif
	}
	else   //LBR
	{  
		if (b>bclock_75M_point)//>75M
		{
			EQ3_Enable_buffer_Setting(0);
			FORGROUND_OFFSET_MODE(LBR_enbuffer_off);
		}
		else
		{
			EQ3_Enable_buffer_Setting(1);
			FORGROUND_OFFSET_MODE(LBR_enbuffer_on);
		}
		EQ_LBR_Setting();
	}

        if ( !GET_ISMHL() && (b>246 && b<266) ) // fixed: Nike TX HDMI 27Mhz swing issue (low temperature); solution for Ver.B or later 
        {
            EQ_Enable_buffer_bit22(1);
        }
        else
        {
            EQ_Enable_buffer_bit22(0);	
        }

}


//***********************************************************************
//Function name :  void EQ_bias_band_setting(UINT32 b)
//PARAM : tmds clock
//RETURN : none 
//descript : EQ bias gain setting 
//***********************************************************************

void DFE_Manual_Set(void)
{
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask,HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask);	//DFE register release
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_adapt_mode_mask,REG_DFE_MODE_adapt_mode(3));	//adaptive mode sel 
	rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_le_min_lane0_mask,REG_DFE_EN_L0_le_min_lane0(0xf));	//lane0 LE coefficient min		//0x18
	rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_le_min_lane1_mask,REG_DFE_EN_L1_le_min_lane1(0xf));	//lane1 LE coefficient min		//0x18
	rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_le_min_lane2_mask,REG_DFE_EN_L2_le_min_lane2(0xf));	//lane2 LE coefficient min		//0x18
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap1_init_lane0_mask,REG_DFE_INIT0_L0_tap1_init_lane0(8));	//lane0 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap1_init_lane1_mask,REG_DFE_INIT0_L1_tap1_init_lane1(8));	//lane1 tap1 initial
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap1_init_lane2_mask,REG_DFE_INIT0_L2_tap1_init_lane2(8));	//lane2 tap1 initial
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_load_in_init_lane0_mask,REG_DFE_INIT1_L0_load_in_init_lane0(2));		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_load_in_init_lane1_mask,REG_DFE_INIT1_L1_load_in_init_lane1(2));		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_load_in_init_lane2_mask,REG_DFE_INIT1_L2_load_in_init_lane2(2));		//lane2  initial load
	HDMI_DELAYMS(1);	//10000
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_load_in_init_lane0_mask,0);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_load_in_init_lane1_mask,0);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_load_in_init_lane2_mask,0);		//lane2  initial load
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_TAPEN4321,R_DFE_TAPEN1);	//R tap1 enable
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_TAPEN4321,G_DFE_TAPEN1);	//G tap1 enable
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_TAPEN4321,B_DFE_TAPEN1);	//B tap1 enable
}


//***********************************************************************
//Function name :  Dump_MHL_DFE_Para()
//PARAM : NONE
//RETURN : Success 1  or Fail  0
//descript : This function is set for cbus detect and MHL flow ok
//***********************************************************************
void Dump_DFE_Para(UINT8 lane)
{
	//HDMI_I2C_MASK(DFE_REG_DFE_READBACK_VADDR,~(_BIT31),_BIT31);	//enable record function
	//ScalerTimer_DelayXms(50);
	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);	
	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,0);
	//HDMI_DELAYMS(1);	//1000
	HDMI_PRINTF("[HDMI] ********************Lane%d******************\n",lane);
	HDMI_PRINTF("[HDMI] Lane%d Tap0 max = 0x%02x  ",lane,get_Tap0_max(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(1));
	//HDMI_DELAYMS(1);	//1000
	HDMI_PRINTF(" min = 0x%02x\n",get_Tap0_min(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(2));
	//udelay(10);	//1000
	HDMI_PRINTF("[HDMI] Lane%d Tap1 max = 0x%02x  ",lane,get_Tap1_max(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(3));
	//udelay(10);	//1000
	HDMI_PRINTF(" min = 0x%02x\n",get_Tap1_min(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(4));
	//udelay(10);	//1000
	HDMI_PRINTF("[HDMI] Lane%d LE   max = 0x%02x  ",lane,get_LEQ_max(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(5));
	//udelay(10);	//1000
	HDMI_PRINTF(" min = 0x%02x\n",get_LEQ_min(rtd_inl(REG_DFE_READBACK_reg)));

	//read DFE result
	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_lane_mask,lane<<coef_set_lane_shift);	
	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,0);
	//udelay(10);	//5000
	HDMI_PRINTF("[HDMI] Lane%d Vth COEF = 0x%x\n",lane,get_VTH_coef(rtd_inl(REG_DFE_READBACK_reg)));
	HDMI_PRINTF("[HDMI] Lane%d current Step = 0x%x\n",lane,get_CurrentStep_coef(rtd_inl(REG_DFE_READBACK_reg)));
	HDMI_PRINTF("[HDMI] Lane%d Buffer mode = 0x%x\n",lane,get_BufferMode_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(1));
	//udelay(10);	//5000
	HDMI_PRINTF("[HDMI] Lane%d COEF Tap0=0x%02x  ",lane,get_TAP0_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(2));
	//udelay(10);	//5000
	HDMI_PRINTF("Tap1=0x%02x  ", get_TAP1_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(3));
	//udelay(10);	//5000
	HDMI_PRINTF("Tap2=%+d  ", (get_TAP2_coef_sign(rtd_inl(REG_DFE_READBACK_reg)))? -get_TAP2_coef(rtd_inl(REG_DFE_READBACK_reg)): get_TAP2_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(4));
	//udelay(10);	//5000
	HDMI_PRINTF("Tap3=%+d  ", (get_TAP3_coef_sign(rtd_inl(REG_DFE_READBACK_reg)))? -get_TAP3_coef(rtd_inl(REG_DFE_READBACK_reg)): get_TAP3_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(5));
	//udelay(10);	//5000
	HDMI_PRINTF("Tap4=%+d\n", (get_TAP4_coef_sign(rtd_inl(REG_DFE_READBACK_reg)))? -get_TAP4_coef(rtd_inl(REG_DFE_READBACK_reg)): get_TAP4_coef(rtd_inl(REG_DFE_READBACK_reg)));

	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(6));
	//udelay(10);	//5000
	HDMI_PRINTF("[HDMI] Lane%d Servo COEF = 0x%x\n",lane,get_SERVO_coef(rtd_inl(REG_DFE_READBACK_reg)));
		 
	rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(7));
	//udelay(10);	//5000
	HDMI_PRINTF("[HDMI] Lane%d LE COEF = 0x%x\n\n",lane,get_LE1_coef(rtd_inl(REG_DFE_READBACK_reg)));

}

#if CONFIG_QC_MHL
//***********************************************************************
//Function name :  MHL_Set_Phy_Table()
//PARAM : NONE
//RETURN : Success 1  or Fail  0
//descript : This function is set for cbus detect and MHL flow ok
//***********************************************************************
void MHL_Set_Phy_Table(int mode)
{
	if (!MHL_IsPPMode())
	{
		//if (mode>2)	mode=0;
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~CCO_Band_mask,(mode>2)?0: CCO_Band(1));	//CCO band 2~3.4GHz set 1
		// PHY parameter setting
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVM_MASK,mhl_phy_param[mode].M_code<<HDMIPHY_REG_CK_1_4_CK_DIVM_shift);		//M code set
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_MASK,mhl_phy_param[mode].N_code<<HDMIPHY_REG_CK_1_4_CK_DIVN_shift);		//N code set
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS,mhl_phy_param[mode].N_bypass<<HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS_shift);		//N bypass

		//rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~ck_md_adj_mask,ck_md_adj(mhl_phy_param[mode].MD_adj));		//CK Freq. mode set	
		rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_CDR_Rate_mask,R_CDR_Rate(mhl_phy_param[mode].MD_adj));		//R Freq. mode set
		//rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_CDR_Rate_mask,G_CDR_Rate(mhl_phy_param[mode].MD_adj));		//G Freq. mode set
		rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_CDR_Rate_mask,B_CDR_Rate(mhl_phy_param[mode].MD_adj));		//B Freq. mode set
		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel(mhl_phy_param[mode].MD_adj)); 	//DCDR mode set

		rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_divider_after_PR_mask,R_divider_after_PR(mhl_phy_param[mode].PR));		//R PR set
		//rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_divider_after_PR_mask,G_divider_after_PR(mhl_phy_param[mode].PR));		//G PR set
		rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_divider_after_PR_mask,B_divider_after_PR(mhl_phy_param[mode].PR));		//B PR set

		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_SELCS_MASK,mhl_phy_param[mode].CK_CS<<HDMIPHY_REG_CK_1_4_CK_SELCS_shift);		//CK CS set
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_RS,mhl_phy_param[mode].CK_RS<<HDMIPHY_REG_CK_5_8_CK_RS_shift);					//CK RS set
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_ICP,mhl_phy_param[mode].CK_Icp<<HDMIPHY_REG_CK_5_8_CK_ICP_shift);				//CK Icp set

		//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,mhl_phy_param[mode].CDR_bias<<HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_shift);		//R CDR bias SBIAS set
		//rtd_maskl(HDMIPHY_REG_G_9_12_reg,~HDMIPHY_REG_G_9_12_reg_G_CDR_SBIAS_MASK,mhl_phy_param[mode].CDR_bias<<HDMIPHY_REG_G_9_12_reg_G_CDR_SBIAS_shift);	//G CDR bias SBIAS set
		//rtd_maskl(HDMIPHY_REG_B_9_12_reg,~HDMIPHY_REG_B_9_12_reg_B_CDR_SBIAS_MASK,mhl_phy_param[mode].CDR_bias<<HDMIPHY_REG_B_9_12_reg_B_CDR_SBIAS_shift);		//B CDR bias SBIAS set

		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp(mhl_phy_param[mode].CDR_KP));	//DCDR KP1
		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki(mhl_phy_param[mode].CDR_KI)); 	//DCDR KI
		//HDMI_PRINTF("24bit mode \n");
	}
	else
	{
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~CCO_Band_mask,CCO_Band(1));	//CCO band 2~3.4GHz set 1  
		// PHY parameter setting
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVM_MASK,mhl_phy_pp_param[mode].M_code<<HDMIPHY_REG_CK_1_4_CK_DIVM_shift);		//M code set
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_MASK,mhl_phy_pp_param[mode].N_code<<HDMIPHY_REG_CK_1_4_CK_DIVN_shift);		//N code set
		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS,mhl_phy_pp_param[mode].N_bypass<<HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS_shift);		//N bypass

		//rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~ck_md_adj_mask,ck_md_adj(mhl_phy_param[mode].MD_adj));		//CK Freq. mode set	
		rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_CDR_Rate_mask,R_CDR_Rate(mhl_phy_pp_param[mode].MD_adj));		//R Freq. mode set
		//rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_CDR_Rate_mask,G_CDR_Rate(mhl_phy_param[mode].MD_adj));		//G Freq. mode set
		rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_CDR_Rate_mask,B_CDR_Rate(mhl_phy_pp_param[mode].MD_adj));		//B Freq. mode set
		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel(mhl_phy_pp_param[mode].MD_adj)); 	//DCDR mode set

		rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_divider_after_PR_mask,R_divider_after_PR(mhl_phy_pp_param[mode].PR));		//R PR set
		//rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_divider_after_PR_mask,G_divider_after_PR(mhl_phy_param[mode].PR));		//G PR set
		rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_divider_after_PR_mask,B_divider_after_PR(mhl_phy_pp_param[mode].PR));		//B PR set

		rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_SELCS_MASK,mhl_phy_pp_param[mode].CK_CS<<HDMIPHY_REG_CK_1_4_CK_SELCS_shift);		//CK CS set
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_RS,mhl_phy_pp_param[mode].CK_RS<<HDMIPHY_REG_CK_5_8_CK_RS_shift);					//CK RS set
		rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_ICP,mhl_phy_pp_param[mode].CK_Icp<<HDMIPHY_REG_CK_5_8_CK_ICP_shift);				//CK Icp set

		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp(mhl_phy_pp_param[mode].CDR_KP));	//DCDR KP1
		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki(mhl_phy_pp_param[mode].CDR_KI)); 	//DCDR KI
		//		HDMI_PRINTF("pp  mode \n");
	}
}

void SetupMHLTMDSPhy(UINT32 bvalue, char force)
{
	int mode;
	UINT8 lane;
	force = force; //avoid warning

	#if VER_B_DC_BUFFER_FLOW
		bError_Cnt_Flag = 0;
	#endif
       if(rtd_inl(SC_VERID_reg)!=0x63300000) //for verA
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_back_koff_en, R_EQ_back_koff_en);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_back_koff_en, G_EQ_back_koff_en);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_back_koff_en, B_EQ_back_koff_en);		// see Garren 0411 mail

		rtd_maskl(HDMIPHY_REG_R_5_8_reg, ~(R_S_BIAS_DFE|R_RL_SELB), R_RL_SELB);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_5_8_reg, ~(G_S_BIAS_DFE|G_RL_SELB), G_RL_SELB);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_5_8_reg, ~(B_S_BIAS_DFE|B_RL_SELB), B_RL_SELB);		// see Garren 0411 mail
	 }

	//rtd_maskl(HDMIPHY_DPLL_CTRL_reg,~(HDMIPHY_DPLL_CTRL_reg_dpll_pow_mask|HDMIPHY_DPLL_CTRL_pow_ldo_mask),(HDMIPHY_DPLL_CTRL_reg_dpll_pow(1)|HDMIPHY_DPLL_CTRL_pow_ldo(1)));	//DPLL 1.8V enable, ALDO 1.1V enable

	//rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_ldo_ref_mask,HDMIPHY_REG_PHY_CTL_ldo_ref(5));//LDO 1.161
	rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_ldo_sel_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_ldo_sel(2));//LDO 1.1

	//rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~CK_IBN20U_Current_mask,CK_IBN20U_Current(2));                 //CK SBIAS set
	//   rtd_maskl(HDMIPHY_REG_B_5_8_reg,~(HDMIPHY_REG_B_5_8_reg_b_8_DFE_RXVCM),_BIT14);      //LV -0.25V

	//cloud modify MHL
	hdmiport_mask(TMDS_OUTCTL_reg , ~(TMDS_OUTCTL_clk25xinv_b_mask),0);// 
	//cloud modify for magellan
   	#if  1
	rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),0);                         //disable TMDS input
	rtd_maskl(TMDS_Z0CC_reg,~TMDS_Z0CC_hde_mask,0);                            //HDMI&DVI function disable
	#endif
	//analog cdr reset 
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//RGB CRD release


	for ( mode=0; mode<4; mode++) {
		if (mhl_phy_param[mode].b_upper > bvalue && mhl_phy_param[mode].b_lower <= bvalue) {
			HDMI_PRINTF("[MHL] SetupMHLTMDSPhy  %x\n",mode);    

			//PHY parameter setting
			//if(hdmi_in(HDMI_AFCR_reg)&MHL_CTS_TEST_ON)   // bit 31 
			//{
			//	_bMhl_clk_mode = (hdmi_in(HDMI_AFCR_reg)&MHL_CTS_TEST_PP_MODE)>>30;
			//	HDMI_PRINTF("[MHL] CTS  mode set  _bMhl_phy_clk_mode =%x   !!!!!!! \n",_bMhl_clk_mode);
			//}
			//else
			//{
			//	_bMhl_clk_mode = MHL_IsPPMode();
			//}
/*
			rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_CMP_HSMODE,R_DFE_CMP_HSMODE);		//high speed mode
			rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_CMP_HSMODE,G_DFE_CMP_HSMODE);		//high speed mode
			rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_CMP_HSMODE,B_DFE_CMP_HSMODE);		//high speed mode
			*/
			EQ_bias_band_setting(bvalue);

			if ( Auto_EQ )
			{
				HDMI_PRINTF("[MHL] Auto EQ Enable\n");
				Hdmi_DFE_EQ_Set(bvalue);		
			}
			else
			{
				DFE_Manual_Set();			
			}

			MHL_Set_Phy_Table(mode);                             
			//if (_bMhl_clk_mode)	mode=3;

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask),0);	//PLL clk reset
			HDMI_DELAYMS(1);
			//rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//DPHY CDR reset
			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask),(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask));	//PLL clk reset
			//udelay(100);	//1000

			if ( Auto_EQ )
			{
				if (bvalue>426)	//>1.35GHz	
					rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_DFE_EN_L2_dfe_adapt_en_lane2(0xff));	//lane2 adaptive enable
				else		//<1.35GHz		
					rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_DFE_EN_L2_dfe_adapt_en_lane2(0xe7));	//lane2 adaptive enable


                         //20140319 
				//rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_reduce_adapt_gain_lane0_mask,REG_DFE_EN_L0_reduce_adapt_gain_lane0(2));	//lane0 adaptive gain reduce
				//rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_reduce_adapt_gain_lane1_mask,REG_DFE_EN_L1_reduce_adapt_gain_lane1(2));	//lane1 adaptive gain reduce
				//rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask,REG_DFE_EN_L2_reduce_adapt_gain_lane2(2));	//lane2 adaptive gain reduce
			}

#if MAC2_DIC_RESET	
			//20131111 14:00 R.S.
			//rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//DPHY CDR reset
			//HDMI_PRINTF("0xb8007b44=0x%x--DPHY CDR reset \n",rtd_inl(HDMIPHY_REG_PHY_CTL_reg));
			udelay(1000);

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask),
			    HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask);	//RGB CRD release
			//HDMI_PRINTF("0xb8007b44=0x%x--CDR set \n",rtd_inl(HDMIPHY_REG_PHY_CTL_reg));
			udelay(1000);

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask),
			    0);	//RGB CRD reset
			//HDMI_PRINTF("0xb8007b44=0x%x--CDR reset \n",rtd_inl(HDMIPHY_REG_PHY_CTL_reg));
			udelay(1000);
#endif
			//HDMI_PRINTF("[MHL] Only B channel\n");
			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),
			    (HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask));	//B CRD release



			if ( Auto_EQ )
			{
				HDMI_DELAYMS(1);	//100000
				rtd_maskl(REG_DFE_READBACK_reg,~REG_DFE_READBACK_record_limit_en_mask,REG_DFE_READBACK_record_limit_en(1));		//limit value record	
				HDMI_DELAYMS(1);//50000
				rtd_maskl(REG_DFE_READBACK_reg,~REG_DFE_READBACK_record_limit_en_mask,0);		//limit value record

				rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,0);	//lane0 adaptive disable
				//rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,0);	//lane1 adaptive disable
				rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,0);	//lane2 adaptive disable

				//read result max and min value
				lane = 2; // sirius 
				Dump_DFE_Para(lane);

				//this section may have problem 20140214

		#if MHL_ReloadMax
				//Need record limit enable
				//Channel B Tap0 set the max value, for trace attenuation
				Hdmi_DFE_EQ_Write_back(lane);
		#endif
			}
			//	return;
		}

	}

	OPEN_RST_MAC();
}
#endif





//***********************************************************************
//Function name :  HDMI_Set_Phy_Table()
//PARAM : NONE
//RETURN : Success 1  or Fail  0
//descript : This function is set for cbus detect and MHL flow ok
//***********************************************************************
void HDMI_Set_Phy_Table(UINT8 mode)
{
	// PHY parameter setting
	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVM_MASK,hdmi_phy_param[mode].M_code<<HDMIPHY_REG_CK_1_4_CK_DIVM_shift);		//M code set
	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_MASK,hdmi_phy_param[mode].N_code<<HDMIPHY_REG_CK_1_4_CK_DIVN_shift);		//N code set
	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS,hdmi_phy_param[mode].N_bypass<<HDMIPHY_REG_CK_1_4_CK_DIVN_BYPASS_shift);		//N bypass

	//rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~ck_md_adj_mask,ck_md_adj(hdmi_phy_param[mode].MD_adj));		//CK Freq. mode set	
	//for Sirius APHY bug
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~R_CDR_Rate_mask,R_CDR_Rate((hdmi_phy_param[mode].MD_adj>3)?3:hdmi_phy_param[mode].MD_adj));		//R Freq. mode set
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~G_CDR_Rate_mask,G_CDR_Rate((hdmi_phy_param[mode].MD_adj>3)?3:hdmi_phy_param[mode].MD_adj));		//G Freq. mode set
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~B_CDR_Rate_mask,B_CDR_Rate((hdmi_phy_param[mode].MD_adj>3)?3:hdmi_phy_param[mode].MD_adj));		//B Freq. mode set
	//for Sirius APHY bug_end
	rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_cdr_rate_sel(hdmi_phy_param[mode].MD_adj)); 	//DCDR mode set

	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_divider_after_PR_mask,R_divider_after_PR(hdmi_phy_param[mode].PR));		//R PR set
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_divider_after_PR_mask,G_divider_after_PR(hdmi_phy_param[mode].PR));		//G PR set
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_divider_after_PR_mask,B_divider_after_PR(hdmi_phy_param[mode].PR));		//B PR set

	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~HDMIPHY_REG_CK_1_4_CK_SELCS_MASK,hdmi_phy_param[mode].CK_CS<<HDMIPHY_REG_CK_1_4_CK_SELCS_shift);		//CK CS set
	rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_RS,hdmi_phy_param[mode].CK_RS<<HDMIPHY_REG_CK_5_8_CK_RS_shift);					//CK RS set
	rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~HDMIPHY_REG_CK_5_8_CK_ICP,hdmi_phy_param[mode].CK_Icp<<HDMIPHY_REG_CK_5_8_CK_ICP_shift);				//CK Icp set

	//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,hdmi_phy_param[mode].CDR_bias<<HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_shift);		//R CDR bias SBIAS set
	//rtd_maskl(HDMIPHY_REG_G_9_12_reg,~HDMIPHY_REG_G_9_12_reg_G_CDR_SBIAS_MASK,hdmi_phy_param[mode].CDR_bias<<HDMIPHY_REG_G_9_12_reg_G_CDR_SBIAS_shift);	//G CDR bias SBIAS set
	//rtd_maskl(HDMIPHY_REG_B_9_12_reg,~HDMIPHY_REG_B_9_12_reg_B_CDR_SBIAS_MASK,hdmi_phy_param[mode].CDR_bias<<HDMIPHY_REG_B_9_12_reg_B_CDR_SBIAS_shift);		//B CDR bias SBIAS set

	rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_kp(hdmi_phy_param[mode].CDR_KP));	//DCDR KP1
	rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_2_reg_ki(hdmi_phy_param[mode].CDR_KI)); 	//DCDR KI
}



void SetupTMDSPhy(UINT32 b, char force)
{
UINT8 mode, dfe_mode, lane, max=0;
UINT8  servo_lan[3];
    #if VER_B_DC_BUFFER_FLOW
		bError_Cnt_Flag = 0;
    #endif
  //  mode=REG_CK_RESULT_get_ck_rate(rtd_inl(REG_CK_RESULT_reg)),
 /*   cloud mark 20140326
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_CMP_HSMODE,R_DFE_CMP_HSMODE);		//high speed mode
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_CMP_HSMODE,G_DFE_CMP_HSMODE);		//high speed mode
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_CMP_HSMODE,B_DFE_CMP_HSMODE);		//high speed mode
*/
	EQ_bias_band_setting(b);
	if ( GET_IC_VERSION() != VERSION_A )
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_back_koff_en, R_EQ_back_koff_en);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_back_koff_en, G_EQ_back_koff_en);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_back_koff_en, B_EQ_back_koff_en);		// see Garren 0411 mail

		rtd_maskl(HDMIPHY_REG_R_5_8_reg, ~(R_S_BIAS_DFE|R_RL_SELB), R_RL_SELB);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_5_8_reg, ~(G_S_BIAS_DFE|G_RL_SELB), G_RL_SELB);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_5_8_reg, ~(B_S_BIAS_DFE|B_RL_SELB), B_RL_SELB);		// see Garren 0411 mail
	}
  
   	#if  1
	//add 2014 0212 deep color flow
	rtd_maskl(TMDS_DPC_SET0_reg,~(TMDS_DPC_SET0_dpc_en_mask),0);           
	rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),0);                         //disable TMDS input
	rtd_maskl(TMDS_Z0CC_reg,~TMDS_Z0CC_hde_mask,0);                            //HDMI&DVI function disable
	#endif
	//analog cdr reset 
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//RGB CRD release  

	if ( Auto_EQ )
	{
		if (b>430 ) //  TMDS 45M > set auto EQ
		{
			HDMI_PRINTF("[HDMI] Auto EQ Enable\n");
			dfe_mode = Hdmi_DFE_EQ_Set(b);	
		}  
		else
		{
			dfe_mode = 3;
			DFE_Manual_Set();
			HDMI_PRINTF("[HDMI] Manual mode \n");
		}
	}  
	else
	{
		dfe_mode = 3;
		DFE_Manual_Set();
	}

	for ( mode=0; mode<5; mode++) {
		if (hdmi_phy_param[mode].b_upper > b && hdmi_phy_param[mode].b_lower <= b) { 
			// if (mode>4)	mode=4;

			rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~CCO_Band_mask,(mode)?0: CCO_Band(1));	//CCO band 2~3.4GHz

			HDMI_Set_Phy_Table(mode); 

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask),0);	//PLL clk reset
			HDMI_DELAYMS(1);
			//rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//DPHY CDR reset
			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask),(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask));	//PLL clk reset
			//udelay(100);	//1000

			if ( Auto_EQ )
			{
				if (b>430 )
				{
					//  if (b>=1280)	//>1.35GHz
					if (dfe_mode == 2 )  // don't open LE 
					{
                                        //cloud modify for BOK player for LE fix may bad signal 

                                        rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,REG_dfe_adapt_en_lane0_TAP0|REG_dfe_adapt_en_lane0_TAP1|REG_dfe_adapt_en_lane0_TAP2|REG_dfe_adapt_en_lane0_TAP3|REG_dfe_adapt_en_lane0_TAP4|REG_dfe_adapt_en_lane0_SERVO|REG_dfe_adapt_en_lane0_Vth);	//lane0 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,REG_dfe_adapt_en_lane1_TAP0|REG_dfe_adapt_en_lane1_TAP1|REG_dfe_adapt_en_lane1_TAP2|REG_dfe_adapt_en_lane1_TAP3|REG_dfe_adapt_en_lane1_TAP4|REG_dfe_adapt_en_lane1_SERVO|REG_dfe_adapt_en_lane1_Vth);	//lane1 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_dfe_adapt_en_lane2_TAP0|REG_dfe_adapt_en_lane2_TAP1|REG_dfe_adapt_en_lane2_TAP2|REG_dfe_adapt_en_lane2_TAP3|REG_dfe_adapt_en_lane2_TAP4|REG_dfe_adapt_en_lane2_SERVO|REG_dfe_adapt_en_lane2_Vth);	//lane2 adaptive enable

                                        /*
                                        rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,REG_DFE_EN_L0_dfe_adapt_en_lane0(0xff));	//lane0 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,REG_DFE_EN_L1_dfe_adapt_en_lane1(0xff));	//lane1 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_DFE_EN_L2_dfe_adapt_en_lane2(0xff));	//lane2 adaptive enable
                                        */					
                                   }
					else if (dfe_mode == 3 ) 
					{
#if 1  // all open
                                        rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,REG_DFE_EN_L0_dfe_adapt_en_lane0(0xff));	//lane0 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,REG_DFE_EN_L1_dfe_adapt_en_lane1(0xff));	//lane1 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_DFE_EN_L2_dfe_adapt_en_lane2(0xff));	//lane2 adaptive enable
#else  // closed 234  

                                        {
                                        rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,REG_dfe_adapt_en_lane0_TAP0|REG_dfe_adapt_en_lane0_TAP1|REG_dfe_adapt_en_lane0_SERVO|REG_dfe_adapt_en_lane0_Vth|REG_dfe_adapt_en_lane0_LE);	//lane0 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,REG_dfe_adapt_en_lane1_TAP0|REG_dfe_adapt_en_lane1_TAP1|REG_dfe_adapt_en_lane1_SERVO|REG_dfe_adapt_en_lane1_Vth|REG_dfe_adapt_en_lane1_LE);	//lane1 adaptive enable
                                        rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,REG_dfe_adapt_en_lane2_TAP0|REG_dfe_adapt_en_lane2_TAP1|REG_dfe_adapt_en_lane2_SERVO|REG_dfe_adapt_en_lane2_Vth|REG_dfe_adapt_en_lane2_LE);	//lane2 adaptive enable
                                        }
#endif				
                                    }
					//cloud modify 20140319
					/*
					rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_reduce_adapt_gain_lane0_mask,REG_DFE_EN_L0_reduce_adapt_gain_lane0(2));	//lane0 adaptive gain reduce
					rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_reduce_adapt_gain_lane1_mask,REG_DFE_EN_L1_reduce_adapt_gain_lane1(2));	//lane1 adaptive gain reduce
					rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask,REG_DFE_EN_L2_reduce_adapt_gain_lane2(2));	//lane2 adaptive gain reduce
					*/
				}
			}

#if RGBlane == 'R'
    #define REG_PHY_CTL_BIT HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask
			HDMI_PRINTF("Only R channel\n");
#elif RGBlane == 'B'
    #define REG_PHY_CTL_BIT HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask
			HDMI_PRINTF("Only B channel\n");
#else
    #define REG_PHY_CTL_BIT (HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask)
#endif

#if MAC2_DIC_RESET	
			udelay(1000);

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask),
			    REG_PHY_CTL_BIT);	//RGB CRD release
			udelay(1000);

			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
    			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask),
			    0);	//RGB CRD reset
			udelay(1000);
#endif
			rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,
			    ~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),
        			(REG_PHY_CTL_BIT|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask));	//DPHY CDR set

			if ( Auto_EQ )
			{
			      if (b>430 )
				{
				HDMI_DELAYMS(1);
				rtd_maskl(REG_DFE_READBACK_reg,~REG_DFE_READBACK_record_limit_en_mask,REG_DFE_READBACK_record_limit_en(1));		//limit value record	
				HDMI_DELAYMS(1);
				rtd_maskl(REG_DFE_READBACK_reg,~REG_DFE_READBACK_record_limit_en_mask,0);		//limit value record

				rtd_maskl(REG_DFE_EN_L0_reg,~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask,0);	//lane0 adaptive disable
				rtd_maskl(REG_DFE_EN_L1_reg,~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask,0);	//lane1 adaptive disable
				rtd_maskl(REG_DFE_EN_L2_reg,~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask,0);	//lane2 adaptive disable

				//read result max and min value
				for (lane=0; lane<3; lane++)
				{
					Dump_DFE_Para(lane);
					rtd_maskl(REG_DFE_READBACK_reg,~coef_set_mask,coef_sel(6));
					servo_lan[lane] = get_SERVO_coef(rtd_inl(REG_DFE_READBACK_reg));
				}

#if ReloadMax
				//Need record limit enable
				for (lane=0; lane<3; lane++)
				{

					if (b>449)
					{
						//Channel B Tap0 set the max value, for trace attenuation
						rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);	
						rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(0));
						HDMI_DELAYMS(1);
						max=get_Tap0_max(rtd_inl(REG_DFE_READBACK_reg));
						HDMI_PRINTF("[HDMI] Lane%d Manual Tap0 = 0x%02x  ",lane,max);
						rtd_maskl((REG_DFE_INIT0_L0_reg+(0x10*lane)),~REG_DFE_INIT0_L0_tap0_init_lane0_mask,max<<REG_DFE_INIT0_L0_tap0_init_lane0_shift);	//lane0 tap1 initial
						rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,0);		//lane0  initial load
						HDMI_DELAYMS(1);
						rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,load_in_init_lane0_tap0);		//lane0  initial load
						HDMI_DELAYMS(1);
						rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap0,0);		//lane0  initial load	
						//Channel B LE set the max value, for trace attenuation			
						rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);	
						rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(4));
						HDMI_DELAYMS(1);
						max=get_LEQ_max(rtd_inl(REG_DFE_READBACK_reg));
					}

					if (b>449)
					{
						if (dfe_mode == 2)
						{
							HDMI_PRINTF("[HDMI] Lane%d Manual LE = 0x%02x\n",lane,max);
							rtd_maskl((REG_DFE_EN_L0_reg+(0x10*lane)),~REG_DFE_EN_L0_le_init_lane0_mask,max<<REG_DFE_EN_L0_le_init_lane0_shift);	//lane0 tap1 initial
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_LE,0);		//lane0  initial load
							HDMI_DELAYMS(1);
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_LE,load_in_init_lane0_LE);		//lane0  initial load
							HDMI_DELAYMS(1);
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_LE,0);		//lane0  initial load
						}
						else	
						{
							rtd_maskl(REG_DFE_READBACK_reg,~limit_set_lane_mask,lane<<limit_set_lane_shift);
							rtd_maskl(REG_DFE_READBACK_reg,~limit_set_mask,limit_sel(2));
							HDMI_DELAYMS(1);
							max += get_Tap1_max(rtd_inl(REG_DFE_READBACK_reg));
							HDMI_PRINTF("[HDMI] Lane%d Manual LE = 0x%02x\n",lane,max);
							rtd_maskl((REG_DFE_INIT0_L0_reg+(0x10*lane)),~REG_DFE_INIT0_L0_tap1_init_lane0_mask,max<<REG_DFE_INIT0_L0_tap1_init_lane0_shift);	//lane0 tap1 initial
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,0);		//lane0  initial load
							HDMI_DELAYMS(1);
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,load_in_init_lane0_tap1);		//lane0  initial load
							HDMI_DELAYMS(1);
							rtd_maskl((REG_DFE_INIT1_L0_reg+(0x10*lane)),~load_in_init_lane0_tap1,0);		//lane0  initial load
						}
					}
				}
				
			#if   1 //SERVO_BUG
				if(rtd_inl(SC_VERID_reg)==0x63300000) //for verA
				{
					rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_servo_init_lane0_mask,REG_DFE_INIT0_L0_servo_init_lane0(servo_lan[0]));	//lane0 servo initial
					rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_servo_init_lane1_mask,REG_DFE_INIT0_L1_servo_init_lane1(servo_lan[1]));	//lane1 servo initial
					rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_servo_init_lane2_mask,REG_DFE_INIT0_L2_servo_init_lane2(servo_lan[2]));	//lane2 servo initial
					// reload servo result 
					rtd_maskl(REG_DFE_INIT1_L0_reg,~_BIT29,_BIT29);		//lane0  initial load
					rtd_maskl(REG_DFE_INIT1_L1_reg,~_BIT29,_BIT29);		//lane1  initial load
					rtd_maskl(REG_DFE_INIT1_L2_reg,~_BIT29,_BIT29);		//lane2  initial load
					//enable servo HW 
					rtd_maskl(REG_DFE_EN_L0_reg,~_BIT21,_BIT21);	//lane0 servo can't tun off
					rtd_maskl(REG_DFE_EN_L1_reg,~_BIT21,_BIT21);	//lane1 servo can't tun off
					rtd_maskl(REG_DFE_EN_L2_reg,~_BIT21,_BIT21);	//lane2 servo can't tun off
				}
			#endif
#endif
			}
			}
			//HDMI_PRINTF("****************** ");
			//HDMI_PRINTF("setup phy %d %d", hdmi_ioctl_struct.b,b);
			//HDMI_PRINTF("****************** ");

			OPEN_RST_MAC();
		}
	}
}




void DFEinitial(void)
{
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask,0);	//DFE reset
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_DFE_ADAPT_EN,0);	//R adaptive disable
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_DFE_ADAPT_EN,0);	//G adaptive disable
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_DFE_ADAPT_EN,0);	//B adaptive disable
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask),0);	//RGB CDR reset
}

void Z0_Calibration (void)
{
	//HDMI setting
	rtd_maskl(REG_MHL_CTRL_reg,~REG_MHL_CTRL_reg_mhlpow_mask,REG_MHL_CTRL_reg_mhlpow(0));
	rtd_maskl(REG_MHL_CTRL_reg,~REG_MHL_CTRL_reg_mhl_hdmisel_mask,REG_MHL_CTRL_reg_mhl_hdmisel(1));
	rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K,MHL_Z100K);		//Z100K disable
	rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask),(REG_MHL_CTRL_reg_z300pow(7)|REG_MHL_CTRL_reg_z300_sel_2(1)|REG_MHL_CTRL_reg_z300_sel_1(1)|REG_MHL_CTRL_reg_z300_sel_0(1)));	//Z300 enable & sel Vterm
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask),(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(7)));		//Z60 register on
	
#ifndef ManualZ0
	UINT8 TimeOut = 10;
//Z0 calibration
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_z0tune_mask,HDMIPHY_REG_BANDGAP_Z0_z0tune(1));		//Z0 calibration sel auto
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_z0pow_mask,HDMIPHY_REG_BANDGAP_Z0_z0pow(1));			//Z0 calibration power on
	do																			
	{
		udelay(1);
		if(rtd_inl(HDMIPHY_REG_BANDGAP_Z0_reg) & HDMIPHY_REG_BANDGAP_Z0_z0_ok_mask)		//wait Z0 calibrate finish
		{
			HDMI_PRINTF("[HDMI] Z0 calibrate result = 0x%x\n",HDMIPHY_REG_BANDGAP_Z0_get_z0_res(rtd_inl(HDMIPHY_REG_BANDGAP_Z0_reg)));
			break;
		}
	} while (--TimeOut);
	if (!TimeOut) {
		HDMI_PRINTF("[HDMI] Auto Z0 Calibration Time Out\n");
	}
#else
	//Z0 manual
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_z0tune_mask,0);
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_reg,~(HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_0_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_1_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_2_mask),(HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_0(ManualZ0)|HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_1(ManualZ0)|HDMIPHY_REG_BANDGAP_Z0_CTRL_adjr_2(ManualZ0)));
#endif
}

void EQ_KOFF_Cali(UINT8 Range, UINT8 mode)
{
	UINT8 TimeOut, i;
	UINT32 reg7be0, reg7b50;

	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~(R_InOff|R_Xtal_for_Koffset_enable),(R_InOff|R_Xtal_for_Koffset_enable));		//R input short GND
  //Load initial tap0 value
#if 1     //20140307

	// rtd_maskl(HDMIPHY_REG_R_9_12_reg,~(R_InOff|R_Xtal_for_Koffset_enable),(R_InOff|R_Xtal_for_Koffset_enable));		//R input short GND
	//Load initial tap0 value

    if (mode ==MHL_3G_enbuffer_on)
    {
    	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap0_init_lane0_mask,REG_DFE_INIT0_L0_tap0_init_lane0(0x12));	//lane0 tap0 initial	//0xc
    	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap0_init_lane1_mask,REG_DFE_INIT0_L1_tap0_init_lane1(0x12));	//lane1 tap0 initial	//0xc
    	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap0_init_lane2_mask,REG_DFE_INIT0_L2_tap0_init_lane2(0x12));	//lane2 tap0 initial	//0xc
    }
    else
    {
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap0_init_lane0_mask,REG_DFE_INIT0_L0_tap0_init_lane0(0xc));	//lane0 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap0_init_lane1_mask,REG_DFE_INIT0_L1_tap0_init_lane1(0xc));	//lane1 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap0_init_lane2_mask,REG_DFE_INIT0_L2_tap0_init_lane2(0xc));	//lane2 tap0 initial	//0xc

    }
	
	rtd_maskl(REG_DFE_INIT1_L0_reg,~(_BIT24),0);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~(_BIT24),0);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~(_BIT24),0);		//lane2  initial load
	HDMI_DELAYMS(1);
	rtd_maskl(REG_DFE_INIT1_L0_reg,~(_BIT24),_BIT24);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~(_BIT24),_BIT24);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~(_BIT24),_BIT24);		//lane2  initial load
	HDMI_DELAYMS(1);
	rtd_maskl(REG_DFE_INIT1_L0_reg,~(_BIT24),0);		//lane0  initial load
	rtd_maskl(REG_DFE_INIT1_L1_reg,~(_BIT24),0);		//lane1  initial load
	rtd_maskl(REG_DFE_INIT1_L2_reg,~(_BIT24),0);		//lane2  initial load
	//HDMI_PRINTF("set tap0 initial \n");
#endif
	/*  // close En_able buffer 
	rtd_maskl(HDMIPHY_REG_R_5_8_reg,~HDMIPHY_REG_R_5_8_enbuffer3_mask, HDMIPHY_REG_R_5_8_enbuffer3(1)); // 20140304
	rtd_maskl(HDMIPHY_REG_G_5_8_reg,~HDMIPHY_REG_G_5_8_enbuffer3_mask, HDMIPHY_REG_G_5_8_enbuffer3(1)); // 20140304
	rtd_maskl(HDMIPHY_REG_B_5_8_reg,~HDMIPHY_REG_B_5_8_enbuffer3_mask, HDMIPHY_REG_B_5_8_enbuffer3(1)); // 20140304
	*/
	//   rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_ldo_sel_mask,HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_ldo_sel(3));//LDO 1.1

	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_tap0_bias_cur_mask, HDMIPHY_REG_R_9_12_tap0_bias_cur(2)); // 20140304
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~HDMIPHY_REG_G_9_12_tap0_bias_cur_mask, HDMIPHY_REG_G_9_12_tap0_bias_cur(2)); // 20140304
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~HDMIPHY_REG_B_9_12_tap0_bias_cur_mask, HDMIPHY_REG_B_9_12_tap0_bias_cur(2)); // 20140304

	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,_BIT19); // 20140304
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK, _BIT19); // 20140304
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK, _BIT19); // 20140304


	Koffset_result_flag = 0;

	reg7be0 = rtd_inl(REG_MHL_CTRL_reg);
	reg7b50 = rtd_inl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg);
	rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask), 0);	//Z300 disable
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask), 0);		//Z60 register off

	rtd_maskl(HDMIPHY_REG_R_5_8_reg, ~R_EQ_HBR, 0);
	rtd_maskl(HDMIPHY_REG_G_5_8_reg, ~G_EQ_HBR, 0);
	rtd_maskl(HDMIPHY_REG_B_5_8_reg, ~B_EQ_HBR, 0);
	rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_KOFF_BG_Range_mask, 0);	//R background K Off range
	rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_KOFF_BG_Range_mask, 0);	//G background K Off range
	rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_KOFF_BG_Range_mask, 0);	//B background K Off range
//Koffset calibration
	//CK channel CKPOW1 on
	//Reg_Z300-->1, Reg_HML_HDMI-->1, (Z0_POW-->0?)
	rtd_maskl(REG_MHL_CTRL_reg,~REG_MHL_CTRL_reg_mhl_hdmisel_mask,REG_MHL_CTRL_reg_mhl_hdmisel(1));	//HDMI sel
	rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_SCHR0|R_SCHR1|R_SCHR2),0);					//R input port sel
	rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_SCHG0|G_SCHG1|G_SCHG2),0);					//G input port sel
	rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_SCHB0|B_SCHB1|B_SCHB2),0);					//B input port sel
	
	//R channel foreground K off set
	//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~(R_InOff|R_Xtal_for_Koffset_enable),(R_InOff|R_Xtal_for_Koffset_enable));		//R input short GND
	rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_Stune|R_KOFF_Fore_mode|R_KOFF_EN),(R_KOFF_Stune|R_KOFF_Fore_mode|R_KOFF_EN));	//R foreground K Off Set Auto & enable 
	//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,(_BIT19));		//R SBIAS set	

	for (i=Range;;i++)
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_EQ_FG_power,0);	//R foreground K Off Set power down
		rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_KOFF_FG_Range_mask,R_KOFF_FG_Range(i));	//R foreground K Off range
		rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_EQ_FG_power,R_EQ_FG_power);	//R foreground K Off Set power on
		TimeOut = 100;
		do												
		{
			HDMI_DELAYMS(1);
			if(rtd_inl(HDMIPHY_REG_R_RESULT_reg) & HDMIPHY_REG_R_RESULT_r_koffok_mask)		//wait Koffset calibrate finish
				break;
		} while (--TimeOut);
		if (!TimeOut)
			HDMI_PRINTF("[HDMI] R channel foreground K Off Set Time Out\n");
		if(!(rtd_inl(HDMIPHY_REG_R_RESULT_reg) & HDMIPHY_REG_R_RESULT_r_koff_bound_mask))		//check  K Off Set boundary
		{
		      if (mode == HBR_enbuffer_off)
		      	{
		      		HBR_enbuffer_off_R = HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_off_R_range = i ;
		      	}
			else if (mode == LBR_enbuffer_off)
			{
				LBR_enbuffer_off_R = HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_off_R_range =i;
			}
			else if (mode == LBR_enbuffer_on)
			{
				LBR_enbuffer_on_R = HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_on_R_range = i;
			}
			else if (mode == HBR_enbuffer_on)
			{
				HBR_enbuffer_on_R = HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_on_R_range = i;
			}
			//OFFSET_Result = HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
			//HDMI_PRINTF("[HDMI] R Koffset Range = %d, R Koffset calibrate result = 0x%x\n",i,OFFSET_Result);
			//rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_FG_Manual_mode_mask),R_KOFF_FG_Manual(OFFSET_Result));
			break;
		}
		else if (i>2)
		{
			Koffset_result_flag++;
			HDMI_PRINTF("[HDMI] R Koffset Range = %d, R Koffset calibrate result = 0x%x\n!!!!!ESD R Koffset result fail!!!!!\n",i,HDMIPHY_REG_RGB_KOFF_SEL_get_r_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg)));
			break;
		}			
	}

	//G channel foreground K off set
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~(G_InOff|G_Xtal_for_Koffset_enable),(G_InOff|G_Xtal_for_Koffset_enable));		//G input short GND
	rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_Stune|G_KOFF_Fore_mode|G_KOFF_EN),(G_KOFF_Stune|G_KOFF_Fore_mode|G_KOFF_EN));	//G foreground K Off Set Auto & enable 
	//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,(_BIT19));		//R SBIAS set	

	for (i=Range;;i++)
	{
		rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_EQ_FG_power,0);	//G foreground K Off Set power down
		rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_KOFF_FG_Range_mask,G_KOFF_FG_Range(i));	//G foreground K Off range
		rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_EQ_FG_power,G_EQ_FG_power);	//G foreground K Off Set power on
		TimeOut = 100;
		do												
		{
			HDMI_DELAYMS(1);
			if(rtd_inl(HDMIPHY_REG_G_RESULT_reg) & HDMIPHY_REG_G_RESULT_g_koffok_mask)		//wait Koffset calibrate finish
				break;
		} while (--TimeOut);
		if (!TimeOut)
			HDMI_PRINTF("[HDMI] G channel foreground K Off Set Time Out\n");
		if(!(rtd_inl(HDMIPHY_REG_G_RESULT_reg) & HDMIPHY_REG_G_RESULT_g_koff_bound_mask))		//check  K Off Set boundary
		{
			if (mode == HBR_enbuffer_off)
			{
				HBR_enbuffer_off_G = HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_off_G_range = i;
			}
			else if (mode == LBR_enbuffer_off)
			{
				LBR_enbuffer_off_G = HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_off_G_range = i;
			}
			else if (mode == LBR_enbuffer_on)
			{
				LBR_enbuffer_on_G = HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_on_G_range = i;
			}
			else if (mode == HBR_enbuffer_on)
			{
				HBR_enbuffer_on_G = HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_on_G_range = i;
			}
			//OFFSET_Result = HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
			//HDMI_PRINTF("[HDMI] G Koffset Range = %d, G Koffset calibrate result = 0x%x\n",i,OFFSET_Result);
			//rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_FG_Manual_mode_mask),G_KOFF_FG_Manual(OFFSET_Result));
			break;
		}
		else if (i>2)
		{
			Koffset_result_flag++;
			HDMI_PRINTF("[HDMI] G Koffset Range = %d, G Koffset calibrate result = 0x%x\n!!!!!ESD G Koffset result fail!!!!!\n",i,HDMIPHY_REG_RGB_KOFF_SEL_get_g_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg)));
			break;
		}			
	}

	//B channel foreground K off set
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~(B_InOff|B_Xtal_for_Koffset_enable),(B_InOff|B_Xtal_for_Koffset_enable));		//B input short GND
	rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_Stune|B_KOFF_Fore_mode|B_KOFF_EN),(B_KOFF_Stune|B_KOFF_Fore_mode|B_KOFF_EN));	//B foreground K Off Set Auto & enable 
	//rtd_maskl(HDMIPHY_REG_R_9_12_reg,~HDMIPHY_REG_R_9_12_reg_R_CDR_SBIAS_MASK,(_BIT19));		//R SBIAS set	

	for (i=Range;;i++)
	{
		rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_EQ_FG_power,0);	//B foreground K Off Set power down
		rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_KOFF_FG_Range_mask,B_KOFF_FG_Range(i));	//B foreground K Off range
		rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_EQ_FG_power,B_EQ_FG_power);	//B foreground K Off Set power on
		TimeOut = 100;
		do												
		{
			HDMI_DELAYMS(1);
			if(rtd_inl(HDMIPHY_REG_B_RESULT_reg) & HDMIPHY_REG_B_RESULT_b_koffok_mask)		//wait Koffset calibrate finish
				break;
		} while (--TimeOut);
		if (!TimeOut)
			HDMI_PRINTF("[HDMI] B channel foreground K Off Set Time Out\n");
		if(!(rtd_inl(HDMIPHY_REG_B_RESULT_reg) & HDMIPHY_REG_B_RESULT_b_koff_bound_mask))		//check  K Off Set boundary
		{
			if (mode == HBR_enbuffer_off)
			{
				HBR_enbuffer_off_B = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_off_B_range = i;
			}
			else if (mode == LBR_enbuffer_off)
			{
				LBR_enbuffer_off_B = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_off_B_range =i;
			}
			else if (mode == LBR_enbuffer_on)
			{
				LBR_enbuffer_on_B = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				LBR_enbuffer_on_B_range = i;
			}
			else if (mode == MHL_3G_enbuffer_on)
			{
				MHL_3G_enbuffer_on_B = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				MHL_3G_enbuffer_on_B_range = i;
			}
			else if (mode == HBR_enbuffer_on)
			{
				HBR_enbuffer_on_B = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
				HBR_enbuffer_on_B_range = i;
			}
			//OFFSET_Result = HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg));
			//HDMI_PRINTF("[HDMI] B Koffset Range = %d, B Koffset calibrate result = 0x%x\n",i,OFFSET_Result);
			//rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_FG_Manual_mode_mask),B_KOFF_FG_Manual(OFFSET_Result));
			break;
		}
		else if (i>2)
		{
			Koffset_result_flag++;
			HDMI_PRINTF("[HDMI] B Koffset Range = %d, B Koffset calibrate result = 0x%x\n!!!!!ESD B Koffset result fail!!!!!\n",i,HDMIPHY_REG_RGB_KOFF_SEL_get_b_koff_sel(rtd_inl(HDMIPHY_REG_RGB_KOFF_SEL_reg)));
			break;
		}			
	}
	
	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~R_InOff,0);		//R inoff disable	
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~G_InOff,0);		//G inoff disable	
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~B_InOff,0);		//B inoff disable

	rtd_outl(REG_MHL_CTRL_reg, reg7be0);
	rtd_outl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg, reg7b50);
	// set manual 
	//7b10 20 30 note bit31 =0
	rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_KOFF_Stune),0);
	rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_KOFF_Stune),0);
	rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_KOFF_Stune),0);

	rtd_maskl(HDMIPHY_REG_R_9_12_reg,~(R_Xtal_for_Koffset_enable),0);
	rtd_maskl(HDMIPHY_REG_G_9_12_reg,~(G_Xtal_for_Koffset_enable),0);
	rtd_maskl(HDMIPHY_REG_B_9_12_reg,~(B_Xtal_for_Koffset_enable),0);
}

#if 0
void DFE_ForeGround_Set (void)
{
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask,HDMIPHY_REG_PHY_CTL_dfe_rstn_n_mask);	//DFE register release
	rtd_maskl(REG_DFE_MODE_reg,~REG_DFE_MODE_gray_en_mask,REG_DFE_MODE_gray_en(0x1e));	//gray code 0xA1--> 0x1e

//enable buffer manual mode
	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0_mask,REG_DFE_INIT1_L0_dfe_en_buffer_manual_lane0(1));	//enable buffer		
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1_mask,REG_DFE_INIT1_L1_dfe_en_buffer_manual_lane1(1));	//enable buffer
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2_mask,REG_DFE_INIT1_L2_dfe_en_buffer_manual_lane2(1));	//enable buffer

	rtd_maskl(REG_DFE_INIT1_L0_reg,~REG_DFE_INIT1_L0_dfe_en_buffer_lane0_mask,REG_DFE_INIT1_L0_dfe_en_buffer_lane0(2));	//enable buffer step
	rtd_maskl(REG_DFE_INIT1_L1_reg,~REG_DFE_INIT1_L1_dfe_en_buffer_lane1_mask,REG_DFE_INIT1_L1_dfe_en_buffer_lane1(2));	//enable buffer step
	rtd_maskl(REG_DFE_INIT1_L2_reg,~REG_DFE_INIT1_L2_dfe_en_buffer_lane2_mask,REG_DFE_INIT1_L2_dfe_en_buffer_lane2(2));	//enable buffer step	

//Tap0 0x12
	rtd_maskl(REG_DFE_INIT0_L0_reg,~REG_DFE_INIT0_L0_tap0_init_lane0_mask,REG_DFE_INIT0_L0_tap0_init_lane0(0x12));	//lane0 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L1_reg,~REG_DFE_INIT0_L1_tap0_init_lane1_mask,REG_DFE_INIT0_L1_tap0_init_lane1(0x12));	//lane1 tap0 initial	//0xc
	rtd_maskl(REG_DFE_INIT0_L2_reg,~REG_DFE_INIT0_L2_tap0_init_lane2_mask,REG_DFE_INIT0_L2_tap0_init_lane2(0x12));	//lane2 tap0 initial	//0xc
}
#endif



void K_Different_Offset_Condition(void)
{ 
	UINT8 mode;

	if ( GET_IC_VERSION() != VERSION_A)
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_OUTPUT_SHORT_DISABLE, 0);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_OUTPUT_SHORT_DISABLE, 0);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_OUTPUT_SHORT_DISABLE, 0);		// EQ1_output short disable // see Garren 0411 mail
		
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_back_koff_en, 0);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_back_koff_en, 0);		// see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_back_koff_en, 0);		// see Garren 0411 mail
	}

	for(mode =1 ;mode < HBR_enbuffer_on+1;mode++)
	{
		switch(mode)
		{
		case HBR_enbuffer_off:
	      EQ_HBR_Setting_EQ_bias_1X();
		EQ3_Enable_buffer_Setting(0);  
		EQ_KOFF_Cali(foreground_range,HBR_enbuffer_off);
			HDMI_PRINTF("[HDMI] mode=%d, KOffset Result(R,G,B)=(0x%02x, 0x%02x, 0x%02x), ",mode,HBR_enbuffer_off_R,HBR_enbuffer_off_G,HBR_enbuffer_off_B);
			HDMI_PRINTF("Range(R,G,B)=(%d,%d,%d)\n", HBR_enbuffer_off_R_range, HBR_enbuffer_off_G_range, HBR_enbuffer_off_B_range);
			break;
		case LBR_enbuffer_off:
		EQ_LBR_Setting();
		EQ3_Enable_buffer_Setting(0);  
             EQ_KOFF_Cali(foreground_range,LBR_enbuffer_off);
			HDMI_PRINTF("[HDMI] mode=%d, KOffset Result(R,G,B)=(0x%02x, 0x%02x, 0x%02x), ",mode,LBR_enbuffer_off_R,LBR_enbuffer_off_G,LBR_enbuffer_off_B);	 
			HDMI_PRINTF("Range(R,G,B)=(%d,%d,%d)\n", LBR_enbuffer_off_R_range, LBR_enbuffer_off_G_range, LBR_enbuffer_off_B_range);
			break;
		case LBR_enbuffer_on:
		EQ_LBR_Setting();
		EQ3_Enable_buffer_Setting(1);  
		EQ_KOFF_Cali(foreground_range,LBR_enbuffer_on);
			HDMI_PRINTF("[HDMI] mode=%d, KOffset Result(R,G,B)=(0x%02x, 0x%02x, 0x%02x), ",mode,LBR_enbuffer_on_R,LBR_enbuffer_on_G,LBR_enbuffer_on_B);
			HDMI_PRINTF("Range(R,G,B)=(%d,%d,%d)\n", LBR_enbuffer_on_R_range, LBR_enbuffer_on_G_range, LBR_enbuffer_on_B_range);
			break;
		case MHL_3G_enbuffer_on:
			EQ_HBR_Setting_EQ_bias_1p33X();
		EQ3_Enable_buffer_Setting(1);  
		EQ_KOFF_Cali(foreground_range,MHL_3G_enbuffer_on);
			HDMI_PRINTF("[HDMI] mode=%d, KOffset Result(B) =(0x%02x) ", mode, MHL_3G_enbuffer_on_B);
			HDMI_PRINTF("Range(B) = %d\n", MHL_3G_enbuffer_on_B_range);
			break;
		case HBR_enbuffer_on:
			EQ_HBR_Setting_EQ_bias_1X();	
			//for test 
			//EQ_HBR_Setting_EQ_bias_1p33X();  // for IC sorting 
			EQ3_Enable_buffer_Setting(1);
			EQ_KOFF_Cali(foreground_range,HBR_enbuffer_on);
			HDMI_PRINTF("[HDMI] mode=%d, KOffset Result(R,G,B)=(0x%02x, 0x%02x, 0x%02x), ",mode,HBR_enbuffer_on_R,HBR_enbuffer_on_G,HBR_enbuffer_on_B);
			HDMI_PRINTF("Range(R,G,B)=(%d,%d,%d)\n", HBR_enbuffer_on_R_range, HBR_enbuffer_on_G_range, HBR_enbuffer_on_B_range);
			break;	
		}
	}

	if ( GET_IC_VERSION() != VERSION_A )
	{
		rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_OUTPUT_SHORT_DISABLE, R_EQ_OUTPUT_SHORT_DISABLE);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_OUTPUT_SHORT_DISABLE, G_EQ_OUTPUT_SHORT_DISABLE);		// EQ1_output short disable // see Garren 0411 mail
		rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_OUTPUT_SHORT_DISABLE, B_EQ_OUTPUT_SHORT_DISABLE);		// EQ1_output short disable // see Garren 0411 mail
	}
}

void Hdmi_PhyInit(void)
{
	rtd_maskl(HDMIPHY_DPLL_CTRL_reg,~(HDMIPHY_DPLL_CTRL_reg_dpll_pow_mask|HDMIPHY_DPLL_CTRL_pow_ldo_mask),(HDMIPHY_DPLL_CTRL_reg_dpll_pow(1)|HDMIPHY_DPLL_CTRL_pow_ldo(1)));	//DPLL 1.8V enable, ALDO 1.1V enable
	HDMI_DELAYMS(1);
	DFEinitial();
#ifdef High_Speed_Test_Dye
	rtd_outl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_hspow_mask,HDMIPHY_REG_BANDGAP_Z0_hspow(1));
	HDMI_PRINTF("[HDMI] HDMI High Speed Test\n");	
#endif

	//Power initial
	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~(HDMIPHY_REG_CK_1_4_CK_PLLPOW|HDMIPHY_REG_CK_1_4_CK_AFE_FORW_POW1),(HDMIPHY_REG_CK_1_4_CK_PLLPOW|HDMIPHY_REG_CK_1_4_CK_AFE_FORW_POW1));	//PLL Power On & HDMI PLL LDO 1.8V power on, Clock AFE power on
	rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_DFEPOW,R_DFEPOW);		//R DAPOW on
	rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_DFEPOW,G_DFEPOW);		//G DAPOW on
	rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_DFEPOW,B_DFEPOW);		//B DAPOW on

	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~(MDCK_sel),(0));
	

	Z0_Calibration();
#if 0// 20140220 For AIC flow 
	MHL_DFE_ForeGround_Set();
#endif
//    EQ_KOFF_Cali(0);

	K_Different_Offset_Condition();
	rtd_maskl(HDMIPHY_REG_CK_MD_reg,~HDMIPHY_REG_CK_MD_ck_md_auto_mask,HDMIPHY_REG_CK_MD_ck_md_auto(1));
	rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~CKAFE_hysterisis,Clock_Hysteresis);
	//set pll ldo    1.92V
	rtd_maskl(HDMIPHY_REG_CK_5_8_reg,~CK_PLL_LDO_SET_mask, CK_PLL_LDO_SET(PLL_LDO1v8));

    rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_DFEPOW,0);		//R DAPOW off
    rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_DFEPOW,0);		//G DAPOW off
    rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_DFEPOW,0);		//B DAPOW off

    if(rtd_inl(SC_VERID_reg) > VERSION_B)  // for Ver C
    {
        rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_SELB_125U_110U|R_RSW_SELB_LEQ_4th|R_RSW_SELB_LEQ_1st),(R_RSW_SELB_LEQ_4th|R_RSW_SELB_LEQ_1st));	
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_SELB_125U_110U|G_RSW_SELB_LEQ_4th|G_RSW_SELB_LEQ_1st),(G_RSW_SELB_LEQ_4th|G_RSW_SELB_LEQ_1st));	
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_SELB_125U_110U|B_RSW_SELB_LEQ_4th|B_RSW_SELB_LEQ_1st),(B_RSW_SELB_LEQ_4th|B_RSW_SELB_LEQ_1st));	
    }
}


void drvif_Hdmi_Init(void)
{
UINT8 j;

    //-------- PLL BUS -------------------------------------------------
    rtd_outl(0xb8000130,0x00351B52); // max 405, set 27*15 = 405MHz

#if QC_RESET
        rtd_outl(0xb8007b00, 0x00004000);
        rtd_outl(0xb8007b04, 0x0a400000);
        //rtd_outl(0xb8007b08, 0x00000000);
        rtd_outl(0xb8007b0c, 0x2bf00001);
        rtd_outl(0xb8007b10, 0x00000000);
        rtd_outl(0xb8007b14, 0x10000000);
        rtd_outl(0xb8007b18, 0x00080000);
        rtd_outl(0xb8007b1c, 0x10000000);
        rtd_outl(0xb8007b20, 0x00000000);
        rtd_outl(0xb8007b24, 0x10000000);
        rtd_outl(0xb8007b28, 0x00080000);
        rtd_outl(0xb8007b2c, 0x10000000);
        rtd_outl(0xb8007b30, 0x00100000);
        rtd_outl(0xb8007b34, 0x10000000);
        rtd_outl(0xb8007b38, 0x00080000);
        rtd_outl(0xb8007b3c, 0x10000000);
        rtd_outl(0xb8007b40, 0x4aa00402);
        rtd_outl(0xb8007b44, 0x00000000);
        rtd_outl(0xb8007b48, 0x00000010);
        rtd_outl(0xb8007b4c, 0x00000000);
        rtd_outl(0xb8007b50, 0x00047770);
        rtd_outl(0xb8007b54, 0x00000000);
        rtd_outl(0xb8007b58, 0x000003ff);
        rtd_outl(0xb8007b5c, 0x00000000);
        rtd_outl(0xb8007b60, 0x000003ff);
#endif

        drvif_Hdmi_Init_CRT_INIT();

#if CRT_ALL_ON	
        //-------- Module Clock & Reset Enable ---------
        rtd_outl(0xb800000c, 0xFFFFFFFF);
        rtd_outl(0xb8000010, 0x9303FFFE);
        rtd_outl(0xb8000014, 0xFFFFFFFF);

        rtd_outl(0xb8000000, 0xFFFFFFFF);
        rtd_outl(0xb8000004, 0xFFFFFFFF);
        rtd_outl(0xb8000008, 0xFFFFFFFF);

        //-------- STANDBY Module Clock & Reset Enable ----------
        rtd_outl(0xb8060030, 0xFFFFFFFF);
        rtd_outl(0xb8060034, 0xFFFFFFFF);

        rtd_outl(0xb8060040, 0xFFFFFFFF);
        rtd_outl(0xb8060044, 0x0003F9FF);
#endif

	for (j=0; j<3; j++) {
		drvif_Hdmi_HPD(j, 0);
	}
	for (j=0; j<3; j++) {
		drvif_Hdmi_LoadEDID(j, HDMI_EDID_TABLE, 256);
	}

	Hdmi_HdcpInit();
	Hdmi_PhyInit();

#if CONFIG_QC_MHL==1
	drvif_CBUS_LoadEDID(hdmi_Cbus_edid,256);

	rtd_maskl(0xb8060244,~(_BIT8|_BIT7),_BIT7);  // for mhl cable in setting 
//	rtd_maskl(0xb8061100,~(_BIT9|_BIT13),_BIT9);  // for MHL_HDMI_SEL
	//HDMI_MHL_Sel ST_GPIO9
	rtd_maskl(ISO_GPDIR_reg, ~_BIT9, _BIT9); 
	rtd_maskl(ISO_GPDATO_reg, ~_BIT9, 0); 
	
	CBUS_InitialPHYSettings();
	MHLInitialMACSettings();
	MHLTmdsInitial();
	CBUS_LinkerSetting(202.5);
	Cbus_Power(0);
	CBUSSwitch(0);
#endif
}


UINT8 get_Koffset_result(void)
{
	return Koffset_result_flag;
}

void Hdmi_Power(char enable)
{
    if ( enable )
    {
#if ENABLE_PWR_IP_CLOSE_SIRIUS
        rtd_maskl(HDMIPHY_DPLL_CTRL_reg,~(HDMIPHY_DPLL_CTRL_reg_dpll_pow_mask|HDMIPHY_DPLL_CTRL_pow_ldo_mask),(HDMIPHY_DPLL_CTRL_reg_dpll_pow_mask|HDMIPHY_DPLL_CTRL_pow_ldo_mask));
#endif
        rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_DFEPOW,R_DFEPOW);		//R DAPOW on
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_DFEPOW,G_DFEPOW);		//G DAPOW on
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_DFEPOW,B_DFEPOW);		//B DAPOW on

        rtd_maskl(HDMIPHY_REG_CK_1_4_reg, ~(HDMIPHY_REG_CK_1_4_CK_PLLPOW|HDMIPHY_REG_CK_1_4_CK_AFE_FORW_POW1), (HDMIPHY_REG_CK_1_4_CK_PLLPOW|HDMIPHY_REG_CK_1_4_CK_AFE_FORW_POW1));	//CK PLL&AFE
        rtd_maskl(TMDS_OUTCTL_reg,~(TMDS_OUTCTL_tbcoe_mask | TMDS_OUTCTL_tgcoe_mask | TMDS_OUTCTL_trcoe_mask | TMDS_OUTCTL_ocke_mask)
					,(TMDS_OUTCTL_tbcoe(1) | TMDS_OUTCTL_tgcoe(1) | TMDS_OUTCTL_trcoe(1) | TMDS_OUTCTL_ocke(1)));		//enable PLL TMDS, RGB clock output        
					
        rtd_maskl(HDMIPHY_REG_PHY_CTL_reg, ~(HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask), (HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask));	//CK PLL&AFE
#if ENABLE_PWR_IP_CLOSE_SIRIUS
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg, 
        	~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask),
        	(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask));
#endif

        hdmiport_mask(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_2_mask), 
            (REG_MHL_CTRL_reg_z300pow(0x07)|REG_MHL_CTRL_reg_z300_sel_2(1)|REG_MHL_CTRL_reg_z300_sel_1(1)|REG_MHL_CTRL_reg_z300_sel_0(1)));

#if ENABLE_PWR_IP_CLOSE_SIRIUS
	hdmiport_mask(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhlpow_mask), REG_MHL_CTRL_reg_mhlpow_mask);
#endif
/*
        rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_FG_power, R_EQ_FG_power);	//R foreground K Off Set power on
        rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_FG_power, G_EQ_FG_power);	//G foreground K Off Set power on
        rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_FG_power, B_EQ_FG_power);	//B foreground K Off Set power on
*/        
        hdmiport_mask(HDMI_AVMCR_reg, ~(HDMI_AVMCR_aoc_mask|HDMI_AVMCR_ve_mask), (HDMI_AVMCR_aoc_mask|HDMI_AVMCR_ve_mask));  //audio & vedio output enable
    }
    else
    {
        rtd_maskl(HDMI_VPLLCR1_reg, ~HDMI_VPLLCR1_dpll_pwdn_mask,HDMI_VPLLCR1_dpll_pwdn_mask);// Disable video PLL   _BIT0
        rtd_maskl(HDMI_APLLCR1_reg, ~HDMI_APLLCR1_dpll_pwdn_mask,HDMI_APLLCR1_dpll_pwdn_mask);// Disable audio PLL	  _BIT0
        rtd_maskl( HDMIPHY_REG_CK_9_12_reg, ~MHL_Z100K, MHL_Z100K); // turn off cbus 100k
        
        hdmiport_mask(HDMI_AVMCR_reg, ~(HDMI_AVMCR_aoc_mask|HDMI_AVMCR_ve_mask), 0);  //audio & vedio output disable
/*        
        rtd_maskl(HDMIPHY_REG_R_1_4_reg, ~R_EQ_FG_power, 0);	//R foreground K Off Set power off
        rtd_maskl(HDMIPHY_REG_G_1_4_reg, ~G_EQ_FG_power, 0);	//G foreground K Off Set power off
        rtd_maskl(HDMIPHY_REG_B_1_4_reg, ~B_EQ_FG_power, 0);	//B foreground K Off Set power off
*/
        hdmiport_mask(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_2_mask), 
            (REG_MHL_CTRL_reg_z300pow(0)|REG_MHL_CTRL_reg_z300_sel_2(1)|REG_MHL_CTRL_reg_z300_sel_1(1)|REG_MHL_CTRL_reg_z300_sel_0(1)));
#if ENABLE_PWR_IP_CLOSE_SIRIUS
	hdmiport_mask(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhlpow_mask), 0);
#endif

        rtd_maskl(HDMIPHY_REG_PHY_CTL_reg, ~(HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask), 0);	//CK PLL&AFE

#if ENABLE_PWR_IP_CLOSE_SIRIUS
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg, 
	~(HDMIPHY_REG_PHY_CTL_b_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_b_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_g_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_cdr_rstb_mask|HDMIPHY_REG_PHY_CTL_r_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_dig_rstb_mask|HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask),
	0);
#endif

        rtd_maskl(TMDS_OUTCTL_reg,~(TMDS_OUTCTL_tbcoe_mask | TMDS_OUTCTL_tgcoe_mask | TMDS_OUTCTL_trcoe_mask | TMDS_OUTCTL_ocke_mask)
					,(TMDS_OUTCTL_tbcoe(0) | TMDS_OUTCTL_tgcoe(0) | TMDS_OUTCTL_trcoe(0) | TMDS_OUTCTL_ocke(0)));		//disable PLL TMDS, RGB clock output        

        rtd_maskl(HDMIPHY_REG_CK_1_4_reg, ~(HDMIPHY_REG_CK_1_4_CK_PLLPOW|HDMIPHY_REG_CK_1_4_CK_AFE_FORW_POW1), 0);	//CK PLL&AFE        
        rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg, //Z0 resister
            ~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask),
            (HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow(0)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(0)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(0)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(0)));
            
	 rtd_maskl(HDMIPHY_REG_R_1_4_reg,~R_DFEPOW,0);		//R DAPOW on
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~G_DFEPOW,0);		//G DAPOW on
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~B_DFEPOW,0);		//B DAPOW on
#if ENABLE_PWR_IP_CLOSE_SIRIUS
	rtd_maskl(HDMIPHY_DPLL_CTRL_reg,~(HDMIPHY_DPLL_CTRL_reg_dpll_pow_mask|HDMIPHY_DPLL_CTRL_pow_ldo_mask),0);
#endif
    }
}

void hdmi_phy_port_select(int port, char enable)
{
//  turn on all Z0 for CEC compliance
//    rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,  //Z0 resister
//            ~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask),
//            (HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow(1<<port)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(1<<port)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(1<<port)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(1<<port)));
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,
	    ~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask),
	    (HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_ck_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(7)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(7)));		//Z60 register on

    switch ( port )
    {
    case 0:
        rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_SCHR0|R_SCHR1|R_SCHR2),R_SCHR0),						//R input port sel
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_SCHG0|G_SCHG1|G_SCHG2),G_SCHG0),					//G input port sel
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_SCHB0|B_SCHB1|B_SCHB2),B_SCHB0),						//B input port sel
        rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~(CK_SCHCK0|CK_SCHCK1|CK_SCHCK2),CK_SCHCK0),	//CLK input port sel
        rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask|HDMIPHY_REG_PHY_CTL_reg_ckdet_mask),(HDMIPHY_REG_PHY_CTL_reg_ckcmp(1)|HDMIPHY_REG_PHY_CTL_reg_ckdet(1)));	//CLK PMM detect sel
        break;
    case 1:
        rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_SCHR0|R_SCHR1|R_SCHR2),R_SCHR1),						//R input port sel
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_SCHG0|G_SCHG1|G_SCHG2),G_SCHG1),					//G input port sel
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_SCHB0|B_SCHB1|B_SCHB2),B_SCHB1),						//B input port sel
        rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~(CK_SCHCK0|CK_SCHCK1|CK_SCHCK2),CK_SCHCK1),				//CLK input port sel
        rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask|HDMIPHY_REG_PHY_CTL_reg_ckdet_mask),(HDMIPHY_REG_PHY_CTL_reg_ckcmp(1)|HDMIPHY_REG_PHY_CTL_reg_ckdet(2)));	//CLK PMM detect sel
        break;
    case 2:
        rtd_maskl(HDMIPHY_REG_R_1_4_reg,~(R_SCHR0|R_SCHR1|R_SCHR2),R_SCHR2),						//R input port sel
        rtd_maskl(HDMIPHY_REG_G_1_4_reg,~(G_SCHG0|G_SCHG1|G_SCHG2),G_SCHG2),					//G input port sel
        rtd_maskl(HDMIPHY_REG_B_1_4_reg,~(B_SCHB0|B_SCHB1|B_SCHB2),B_SCHB2),						//B input port sel
        rtd_maskl(HDMIPHY_REG_CK_1_4_reg,~(CK_SCHCK0|CK_SCHCK1|CK_SCHCK2),CK_SCHCK2),	//CLK input port sel
        rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_reg_ckcmp_mask|HDMIPHY_REG_PHY_CTL_reg_ckdet_mask),(HDMIPHY_REG_PHY_CTL_reg_ckcmp(1)|HDMIPHY_REG_PHY_CTL_reg_ckdet(4)));	//CLK PMM detect sel
        break;
    default:
        HDMI_PRINTF("unknown port\n");
        break;
    }
    // for DFE PHY
    rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask),0);	//PLL clk reset
    HDMI_DELAYMS(1);
    rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask),(HDMIPHY_REG_PHY_CTL_ck_vcorstb_mask|HDMIPHY_REG_PHY_CTL_ck_pllrstb_mask|HDMIPHY_REG_PHY_CTL_ck_md_rstb_mask));	//PLL clk reset
}


bool  Hdmi_TmdsInit(void)
{
	//initial HDMI
	rtd_maskl(MHL_DEMUX_CTRL_reg,~(MHL_DEMUX_CTRL_mhl_pp_en_mask|MHL_DEMUX_CTRL_mhl_en_mask),0),
	rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_pp_mode_output_mask|MHL_HDMI_MAC_CTRL_packet_mhl_en_mask|MHL_HDMI_MAC_CTRL_xor_pixel_sel_mask|MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask),0);

	//for BCH & debounce
	rtd_maskl(TMDS_ERRC_reg,~TMDS_ERRC_nl_mask,TMDS_ERRC_nl(4));		// 1+8 cycle debounce + de masking transition of vs/hs + masking first 8-line de	
	rtd_maskl(HDMI_BCHCR_reg,~(HDMI_BCHCR_enrwe_mask|HDMI_BCHCR_bche_mask),(HDMI_BCHCR_enrwe(1)|HDMI_BCHCR_bche(1)));	// BCH function enable
	
	//rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),(TMDS_PWDCTL_ebip(1)|TMDS_PWDCTL_egip(1)|TMDS_PWDCTL_erip(1)|TMDS_PWDCTL_ecc(1)));				//enable TMDS input
	rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),0);				//enable TMDS input
	//HDMI_PRINTF("0xb800d01c=0x%x--MAC reset\n",rtd_inl(TMDS_PWDCTL_reg));
	
	//rtd_maskl(TMDS_Z0CC_reg,~TMDS_Z0CC_hde_mask,TMDS_Z0CC_hde(1));					//HDMI&DVI function enable
	rtd_maskl(TMDS_Z0CC_reg,~TMDS_Z0CC_hde_mask,0);					//HDMI&DVI function disable
	//HDMI_PRINTF("0xb800d020=0x%x--MAC reset\n",rtd_inl(TMDS_Z0CC_reg));
#ifdef Debug_LDO
	//Debug low yield
	rtd_maskl(HDMIPHY_REG_PHY_CTL_reg,~HDMIPHY_REG_PHY_CTL_ldo_ref_mask,HDMIPHY_REG_PHY_CTL_ldo_ref(7));	//LDO 1.2V
	//HDMI_PRINTF("0xb800db44=0x%x--LDO level\n",rtd_inl(HDMIPHY_REG_PHY_CTL_reg));
#endif
	
#if RGBlane == 'R'
	//R & B Swap
	rtd_maskl(TMDS_PWDCTL_reg ,~TMDS_PWDCTL_brcw_mask,TMDS_PWDCTL_brcw(1));				//enable TMDS input
	//B value measure choose whitch channel
	rtd_maskl(TMDS_CPS_reg,~TMDS_CPS_clkv_meas_sel_mask,0);
	//Mac choose whitch channel clock
	rtd_maskl(HDMI_VCR_reg,~HDMI_VCR_iclk_sel_mask,HDMI_VCR_iclk_sel(2));
#else
	rtd_maskl(HDMI_VCR_reg,~HDMI_VCR_iclk_sel_mask,HDMI_VCR_iclk_sel(0));
	rtd_maskl(TMDS_CPS_reg,~TMDS_CPS_clkv_meas_sel_mask,TMDS_CPS_clkv_meas_sel(3));		//measure input clock source sel 
#endif		
	rtd_maskl(HDMI_AVMCR_reg,~HDMI_AVMCR_ve_mask,HDMI_AVMCR_ve(1));					//need to enable video before enable TMDS clock
	rtd_maskl(TMDS_OUTCTL_reg,~(TMDS_OUTCTL_ocke_mask|TMDS_OUTCTL_tbcoe_mask|TMDS_OUTCTL_tgcoe_mask|TMDS_OUTCTL_trcoe_mask),(TMDS_OUTCTL_ocke(1)|TMDS_OUTCTL_tbcoe(1)|TMDS_OUTCTL_tgcoe(1)|TMDS_OUTCTL_trcoe(1)));		//enable TMDS output
	rtd_maskl(TMDS_DPC_SET0_reg,~TMDS_DPC_SET0_dpc_bypass_dis_mask,TMDS_DPC_SET0_dpc_en(1));					// video function block enable	
	
	return TRUE;
}

bool Hdmi_MacInit(void)
{
	hdmiport_out(HDMI_HDMI_SCR_VADDR , 0x122);//DVI/HDMI condition(A,B) select
	hdmiport_out(HDMI_HDMI_AFCR_VADDR , 0x06);//Enable Audio FIFO
	hdmiport_out(HDMI_HDMI_AVMCR_VADDR , 0x48);//enable video & audio output
	hdmiport_out(HDMI_HDMI_WDCR0_VADDR , 0x00);  //disable watch dog
	hdmiport_out(HDMI_HDMI_BCHCR_VADDR , 0x19);	// Enable BCH Function
	hdmiport_out(HDMI_HDMI_PVGCR0_VADDR , 0x09);	//For HDMI Packet
#if 1 //fix panasonic issue((dvd mode + hdcp) fail)
	//hdmiport_mask(HDCP_PCR_reg , ~HDCP_PCR_km_clk_sel_mask,0);
	hdmiport_mask(HDCP_PCR_reg , ~(HDCP_PCR_km_clk_sel_mask|HDCP_PCR_hdcp_vs_sel_mask),HDCP_PCR_hdcp_vs_sel_mask);// vsync virtual 
#endif
	rtd_maskl(HDMI_VCR_reg, ~(HDMI_VCR_csam_mask | HDMI_VCR_prdsam_mask), HDMI_VCR_csam(1) | HDMI_VCR_prdsam(1));
	//	hdmiport_mask(HDMI_HDMI_AOCR_VADDR,(unsigned char)~(0xff),0x00);//Disable SPDIF/I2S Output
	//	hdmiport_mask(HDMI_HDMI_AOCR_VADDR,~_BIT10,_BIT10);//Hold avmute value outside v-sync region
	hdmiport_out(HDMI_HDMI_MAGCR0_VADDR, 0xE000/*0x14*/);
	hdmiport_out(HDMI_HDMI_PTRSV1_VADDR, 0x82);
	// clear HDMI interrupt control register
	hdmiport_out(HDMI_HDMI_INTCR_VADDR, 0);
	hdmiport_mask(HDMI_HDMI_VCR_VADDR, ~(_BIT7) , 0);  // not inverse EVEN/ODD

	hdmiport_mask(HDMI_HDMI_PAMICR_VADDR ,~_BIT0, 0x00);//Disable packet variation Watch Dog
	//hdmiport_mask(HDMI_HDMI_AOCR_VADDR,0x00, 0x00);//Disable SPDIF/I2S Output
	hdmiport_mask(HDMI_AOCR_reg,(~0x0ff),0xFF);	//Enable SPDIF/I2S Output

	//Magellan_clock set
	/*
	rtd_outl(HDMI_CLKDET_GDI_TMDSCLK_SETTING_00_VADDR,0x10010); //Set TC
	rtd_outl(HDMI_CLKDET_GDI_TMDSCLK_SETTING_01_VADDR,0x7800047); //clk detect disable
	*/
	//
	hdmiport_mask (TMDS_ERRC_reg,~TMDS_ERRC_nl_mask,TMDS_ERRC_nl(4)); // cycle debounce 
	//cloud modify Mac2 bug 20130716
	if (Debug_FIFOclock==2)
		rtd_maskl(TMDS_OUTCTL_reg ,~TMDS_OUTCTL_clk25xinv_r_mask,TMDS_OUTCTL_clk25xinv_r(CLOCK_INVERT));	//R channel input clock positive
	else if (Debug_FIFOclock==1)
		rtd_maskl(TMDS_OUTCTL_reg ,~TMDS_OUTCTL_clk25xinv_g_mask,TMDS_OUTCTL_clk25xinv_g(CLOCK_INVERT));	//G channel input clock positive
	else
		rtd_maskl(TMDS_OUTCTL_reg ,~TMDS_OUTCTL_clk25xinv_b_mask,TMDS_OUTCTL_clk25xinv_b(CLOCK_INVERT));	//B channel input clock positive

	//BCH function enable
	rtd_maskl(HDMI_BCHCR_reg,~(HDMI_BCHCR_enrwe_mask|HDMI_BCHCR_bche_mask),(HDMI_BCHCR_enrwe(1)|HDMI_BCHCR_bche(1)));   // BCH function enable

	return TRUE;
}


void drvif_Hdmi_InitSrc(UINT8 channel)
{
#if HotPlugDetect
	drvif_Hdmi_HPD(channel, 0);
#endif

	hdmi_phy_port_select(channel, 1);
	rtd_maskl(HDMI_VCR_reg, ~HDMI_VCR_hdcp_ddc_chsel_mask,HDMI_VCR_hdcp_ddc_chsel(channel));	//HDCP DDC channel sel

#if Load_EDID_HDCP_KEY
	// Remind to check pin share: 0xb8060204, 0xb8060208, 0xb8060200
	drvif_EDIDEnable(channel, 1);
	drvif_EDID_DDC12_AUTO_Enable(channel, 0);
#endif
	
#if HotPlugDetect
	drvif_Hdmi_HPD(channel, 1);
#endif

	Hdmi_Power(1);
	Hdmi_TmdsInit();
	Hdmi_MacInit();

}









UINT32 HdmiMeasureVedioClock(void)
{
#define TOTAL_LOOP 100
UINT8 Nloop = TOTAL_LOOP, stable_cnt=0;
UINT32 b = 0, bsave = 0, mode= 0;

    while (--Nloop)
    {	
        if (Hdmi_IsbReady() == TRUE)
        {
            b =  Hdmi_get_b_value();
            mode=REG_CK_RESULT_get_ck_rate(rtd_inl(REG_CK_RESULT_reg));
            if ( ((b+3) > bsave) && ((b-3) < bsave) )
            {
                if ( (stable_cnt++ > 9) && (b>123 && b<2845) ) // wait for continous stable 6 times
                {
                    break;
                }
            }
            else
            {
                bsave = b;
                stable_cnt = 0;
            }
        }
        else
        {
            b = 0;
            bsave = 0;
            stable_cnt = 0;
        }
        Hdmi_TriggerbMeasurement();
        mdelay(10);
    }

    HDMI_PRINTF("[HDMI] TMDS clock = %dMHz(b=%d mode=%d) within %d loop.\n", (b*27+128)>>8, b, mode, (TOTAL_LOOP-Nloop));

    if ( !Nloop )
    {
        if ( b==0 )
        {
            HDMI_PRINTF("[HDMI] WARNING: No input!!\n");
        }
        else
        {
            b = 0;
            HDMI_PRINTF("[HDMI] WARNING: Clock is not stable!!\n");
        }
    }

    return b;
}


UINT8 drvif_Hdmi_GetColorDepth(void)
{
	if (GET_HDMI_CD() >= 4) {
		return (GET_HDMI_CD()-4);
	} else {
		return 0;
	}
}

bool HDMI_FormatDetect(void)
{
	if (rtd_inl(HDMI_SR_reg)&HDMI_SR_mode_mask)
		return TRUE;
	else
		return FALSE;
}

void HDMI_RgbYuvDetect(bool qc_set_scaler)
{
	UINT8 tempvalue=0;
	
	rtd_maskl(HDMI_VCR_reg,~HDMI_VCR_csam_mask,HDMI_VCR_csam(1));			//Color space auto detection
	udelay(20000);
	tempvalue=HDMI_VCR_get_csc_r(rtd_inl(HDMI_VCR_reg));		//read color space mode
	if (tempvalue == 0x3)
	{
		HDMI_PRINTF("[HDMI] YCbCr_420\n");
	}
	else if (tempvalue == 0x2)
	{
		if ( qc_set_scaler )
		{
			rtd_maskl(0xb8023000, ~(_BIT4|_BIT0), 0);
			rtd_maskl(0xb8023028, ~(_BIT0), 0);
		}
		HDMI_PRINTF("[HDMI] YCbCr_444\n");
	}
	else if (tempvalue)
	{
		if ( qc_set_scaler )
		{
			rtd_maskl(0xb8023000, ~(_BIT4|_BIT0), 0);
			rtd_maskl(0xb8023028, ~(_BIT0), _BIT0);
		}
		HDMI_PRINTF("[HDMI] YCbCr_422\n");
	}
	else
	{
		rtd_maskl(0xb8023000, ~(_BIT4|_BIT0), (_BIT4|_BIT0));
		HDMI_PRINTF("[HDMI] RGB\n");
	}
}

bool Hdmi_VideoPLLSetting(int b, int cd, int Enable2X)
{
//  Fin =   Fxtal * 1024 / b
//  Target vco = ( Fin * m / n )     , TagretVco_HB = 400 ,  TagretVco_LB=200
//  Fin * M / N / 2^o / 2 * s = Fout = Fin * [24/30, 24/36, 24/48] ,  [10bits, 12bits,16bits]
//  200 <  ( Fin * m / n )  < 400  -->  200 <   Fin * 2^o * s * [ 8/5 , 4/3, 1 ]   < 400
//  Scode_LB =  200 * 15 * b  / ( Fxtal *1024 * [24,20,15] )
//  Scode_HB =  400 * 15 * b  / ( Fxtal *1024 * [24,20,15] )
//  Smean = (Scode_LB +Scode_HB ) /2
//  M/N = [8/5 , 4/3 , 1 ] * S

	unsigned int large_ratio, Smean,Stest, m, n, o, fraction1, fraction2, pixel_clockx1024, fvco;

	if (b <= 0)
		return FALSE;

	if (cd >= 4) cd = 0;

	//rtd_maskl(HDMI_VPLLCR1_reg, (~(_BIT0|_BIT1 |_BIT2|_BIT3|_BIT11|_BIT12|_BIT13)),_BIT0|_BIT2);// Disable PLL
	//cloud modify for magellan remove bit 16~bit 10
       rtd_maskl(HDMI_VPLLCR1_reg, (~(HDMI_VPLLCR1_dpll_pwdn_mask|HDMI_VPLLCR1_dpll_vcorstb_mask |HDMI_VPLLCR1_dpll_freeze_mask|HDMI_VPLLCR1_dpll_stop_mask)),HDMI_VPLLCR1_dpll_pwdn_mask|HDMI_VPLLCR1_dpll_freeze_mask);// Disable PLL
	#define FCVO_MIN	250
	#define FCVO_MAX	500
#if HDMI_OLD_CLK_DETECT
	pixel_clockx1024 = ((27 * 1024 * 1024 * dpll_ratio[cd].SM ) + (b * ((unsigned int) dpll_ratio[cd].SN)/2)) / b/ dpll_ratio[cd].SN;
#else
	pixel_clockx1024 =(b * 27 * dpll_ratio[cd].SM * 1024) / (dpll_ratio[cd].SN * 256);
#endif
	//HDMI_PRINTF("pixel_clock = %d\n", pixel_clockx1024);

	if (pixel_clockx1024 < (160 * 1024) && Enable2X == 0) {
		Enable2X = 1;		// if pixel_clock is under 160MHz then enable 2X clock maybe for DI
	}


      #if MHL_SUPPORT

        // interlace must 2 x   , MHL not 
	//if ((Enable2X)&((!GET_ISMHL())|((hdmi.tx_timing.progressive) == 0))) {
	if ((Enable2X)&(!GET_ISMHL())) {
		large_ratio = 2;
	      rtd_maskl(TMDS_CPS_reg, ~TMDS_CPS_pll_div2_en_mask, TMDS_CPS_pll_div2_en(1));
	} 	else  {
		large_ratio = 1;
		rtd_maskl(TMDS_CPS_reg, ~TMDS_CPS_pll_div2_en_mask, TMDS_CPS_pll_div2_en(0));
		
	}
	
       //if  ((cd || Enable2X)&&((!GET_ISMHL())|((hdmi.tx_timing.progressive) == 0))) {
 	if  ((cd || Enable2X)&&((!GET_ISMHL()))) {
		 rtd_maskl(TMDS_DPC_SET0_reg, ~TMDS_DPC_SET0_dpc_bypass_dis_mask, TMDS_DPC_SET0_dpc_bypass_dis(1));		 
	 } else {
	  	 rtd_maskl(TMDS_DPC_SET0_reg, ~TMDS_DPC_SET0_dpc_bypass_dis_mask, TMDS_DPC_SET0_dpc_bypass_dis(0));
	 }

	#else
	if (Enable2X) {
		large_ratio = 2;
		rtd_maskl(TMDS_CPS_reg, ~TMDS_CPS_pll_div2_en_mask, TMDS_CPS_pll_div2_en(1));
	} 	else  {
		large_ratio = 1;
		rtd_maskl(TMDS_CPS_reg, ~TMDS_CPS_pll_div2_en_mask, TMDS_CPS_pll_div2_en(0));
		
	}

	if  (cd || Enable2X) {
		 rtd_maskl(TMDS_DPC_SET0_reg, ~TMDS_DPC_SET0_dpc_bypass_dis_mask, TMDS_DPC_SET0_dpc_bypass_dis(1));		 
	 } else {
	  	 rtd_maskl(TMDS_DPC_SET0_reg, ~TMDS_DPC_SET0_dpc_bypass_dis_mask, TMDS_DPC_SET0_dpc_bypass_dis(0));
	 }
      #endif
	if (large_ratio != 1)
	{
#if HDMI_OLD_CLK_DETECT
		pixel_clockx1024 = ((27 * 1024 * 1024 * dpll_ratio[cd].SM * large_ratio) + (b * ((unsigned int) dpll_ratio[cd].SN)/2)) / b/ dpll_ratio[cd].SN;
#else
		pixel_clockx1024 =(b * 27 * dpll_ratio[cd].SM * 1024 * 2) / (dpll_ratio[cd].SN * 256);
#endif
		//HDMI_PRINTF("large_ratio=%d, 2X pixel clock PLL = %d\n", large_ratio, pixel_clockx1024);
	}


	if (pixel_clockx1024 == 0) {
		HDMI_PRINTF("pixel_clockx1024 is zero\n");
		return FALSE;
	}

	o = 1;
	Smean = 0;
	Stest = 1;
	while(pixel_clockx1024 <= (200*1024)){
		if (Smean == 0) Stest = 1;
  		else Stest = Smean * 2;
		// 2---> 2^o
		if (((pixel_clockx1024*2)*Stest)>= (FCVO_MIN*1024))
			break;
		Smean ++;
	};

	if (pixel_clockx1024 > (200*1024)){// >200MHz
		o = 0;
		Smean = 0;
	}
	/*else if (pixel_clockx1024 > (100*1024)){//100MHz ~200MHz
		o = 1;
		Smean = 0;
	}
	else if (pixel_clockx1024 > (50*1024)){//50MHz ~100MHz
		o = 1;
		Smean = 1;
	}
	else if (pixel_clockx1024 > (25*1024)){//25MHz ~50MHz
		o = 1;
		Smean = 2;
	}
	else {//13.5MHz~25MHz
		o = 1;
		Smean = 4;
	}*/

	//HDMI_PRINTF( "Smean =  %d\n", Smean);

 	//if (Smean == 0) Stest = 1;
  	//else Stest = Smean * 2;


		n = 0;
	do {
     		n += dpll_ratio[cd].RatioN;
          	m =((dpll_ratio[cd].RatioM * Stest * n * large_ratio)<<o) / dpll_ratio[cd].RatioN;
 		//HDMI_PRINTF( "%d %d\n", m, n);
 	}while(n < 2);

#if HDMI_OLD_CLK_DETECT
	fvco = (27 * m * 1024) / b / n;
#else
	fvco = (b * 27 * m) / (256 * n);
#endif

#if 0 // 20091111 kist
	fraction1 = ((unsigned long)m *4 * 100 / 1067) ;    // 2bit fractional part
	fraction2 = 0x00;

    if (fraction1 >=10)
       fraction1 -= 10;

    if(fraction1 >= 40)        // 2bit fractional part
    {
        fraction1 -= 40;
        fraction2 |= 0x04;
    }

    if(fraction1 >= 20)        // 2bit fractional part
    {
        fraction1 -= 20;
       fraction2 |= 0x02;
    }

    if(fraction1 >= 10)        // 2bit fractional part
    {
        fraction1 -= 10;
        fraction2 |= 0x01;
    }
    fraction2|= 0x70;
#else	//20110830 adams modify for darwin
	//	Icp x (N/M) x (27M/Fin) = 0.95uA	
//	Icp x (N/M) x (27M/(27Mx1024/b) = 0.95
//	Icp x (N/M) x (b/1024) = 0.95
//	Icp x (N/M) x (b/1024) x 100 = 95
//	Icp = (Mx1024x95)/(Nxbx100)
#if HDMI_OLD_CLK_DETECT
	fraction1 = ((unsigned long)m *1024 *95 *4 /(n *b *100)) ;    // 2bit fractional part
#else
	fraction1 = ((unsigned long)m *95 *4 *b /(n *256 *100)) ;    // 2bit fractional part
#endif
	fraction2 = 0x00;
	//HDMI_PRINTF("***************fraction1=%d\n",fraction1);
	//if(((fraction1&0x01) == 0x00)||(fraction1 > 80))
		//fraction2 |= 0x40;

	if (fraction1 >=10)
       fraction1 -= 10;

    	if(fraction1 >= 40)        // 2bit fractional part
    	{
       fraction1 -= 40;
       fraction2 |= 0x04;
    	}

    	if(fraction1 >= 20)        // 2bit fractional part
    	{
       fraction1 -= 20;
       fraction2 |= 0x02;
    	}

    	if(fraction1 >= 10)        // 2bit fractional part
    	{
       fraction1 -= 10;
       fraction2 |= 0x01;
    	}
	//HDMI_PRINTF("***************fraction2=%d\n",fraction2);
	//fraction2 |= 0x18;
#endif
	//HDMI_PRINTF("***************cd=%d\n",cd);
	//HDMI_PRINTF("***************m=%d\n",m);
	//HDMI_PRINTF("***************n=%d\n",n);
	//HDMI_PRINTF("***************o=%d\n",o);
	//HDMI_PRINTF("***************s=%d\n",Smean);
	//HDMI_PRINTF("***************fraction1=%d\n",fraction1);
	//HDMI_PRINTF("***************fraction2=%d\n",fraction2);
	//HDMI_PRINTF("***************pixel_clockx1024=%d\n",pixel_clockx1024);
	//HDMI_PRINTF("***************fvco=%d MHz\n",fvco);
	//HDMI_PRINTF("***************larget=%d\n",large_ratio);


	rtd_outl(HDMI_VPLLCR0_reg, HDMI_VPLLCR0_dpll_m(m-2) |HDMI_VPLLCR0_dpll_o(o) |HDMI_VPLLCR0_dpll_n(n-2) |HDMI_VPLLCR0_dpll_rs(3) |HDMI_VPLLCR0_dpll_ip(fraction2));// | fraction2);	//set video PLL parameter
	rtd_outl(MN_SCLKG_DIVS_reg,Smean);		//set video PLL output divider
	//rtd_maskl(HDMI_VPLLCR1_reg, (~(_BIT0 | _BIT1 | _BIT2)),_BIT1|_BIT3); 	// Enable PLL
	rtd_maskl(MN_SCLKG_CTRL_reg,~_BIT4,_BIT4);		//video PLL double buffer load
	//rtd_maskl(HDMI_VPLLCR1_reg, (~(_BIT0|_BIT1 |_BIT2|_BIT3)),_BIT1|_BIT3);// Enable PLL
	rtd_maskl(HDMI_VPLLCR1_reg, ~((HDMI_VPLLCR1_dpll_pwdn_mask|HDMI_VPLLCR1_dpll_vcorstb_mask |HDMI_VPLLCR1_dpll_freeze_mask|HDMI_VPLLCR1_dpll_stop_mask)),(HDMI_VPLLCR1_dpll_vcorstb_mask|HDMI_VPLLCR1_dpll_stop_mask));
	//cloud modify cause magellan remove  16~10
	/*
	HDMI_DELAYMS(1);
	rtd_maskl(HDMI_VPLLCR1_reg, ~_BIT11,_BIT11);//Reg DPLL_CMPEN
	HDMI_DELAYMS(1);
	rtd_maskl(HDMI_VPLLCR1_reg, ~_BIT12,_BIT12);// Reg DPLL_CALLCH
	HDMI_DELAYMS(1);
	rtd_maskl(HDMI_VPLLCR1_reg, ~_BIT13,_BIT13);// Reg DPLL_CALSW
	*/

	return TRUE;
}

bool Hdmi_DetectMode(UINT32 b)
{
    rtd_maskl(MHL_DEMUX_CTRL_reg, ~MHL_DEMUX_CTRL_dvi_ch_sync_mask, 0);
    rtd_maskl(HDMI_VCR_reg, ~(HDMI_VCR_se_mask|HDMI_VCR_eot_mask|HDMI_VCR_int_pro_chg_flag_mask), HDMI_VCR_eot_mask); //clear status, prepare to check interlace/progressive
    rtd_maskl(HDMI_SCR_reg,~(HDMI_SCR_cabs_mask|HDMI_SCR_fcddip_mask),HDMI_SCR_cabs(1));	// set HDMI/DVI decide condiftion
    mdelay(300);  //Hdmi_WaitVsync(4); in HDMI_MS_MODE_ONESHOT mode in AP code
    
    if ( HDMI_FormatDetect() )
    {
        HDMI_PRINTF("[HDMI] HDMI Mode\n");
        rtd_maskl(HDMI_VCR_reg,~(HDMI_VCR_prdsam_mask|HDMI_VCR_se_mask|HDMI_VCR_eot_mask|HDMI_VCR_int_pro_chg_flag_mask),HDMI_VCR_prdsam(1)); 		//Enable pixel repetition down sampling auto mode
        rtd_maskl(HDMI_SR_reg,~(HDMI_SR_vic_mask|HDMI_SR_pllsts_mask|HDMI_SR_afifoof_mask|HDMI_SR_afifouf_mask),(HDMI_SR_vic(1)|HDMI_SR_pllsts(1) |HDMI_SR_afifoof(1)|HDMI_SR_afifouf(1)));	//Clear HDMI watch dog
        udelay(10000);
        //
        if (!(rtd_inl(HDMI_SR_reg)&HDMI_SR_avmute_mask))							// Clear av_mute
        {
            rtd_maskl(HDMI_AVMCR_reg,~HDMI_AVMCR_ve_mask,HDMI_AVMCR_ve(1)), 	// enable DVI/HDMI video output
            rtd_maskl(HDMI_WDCR0_reg,~HDMI_WDCR0_asmfe_mask,0); 	// Disable Set_AVMute watch dog , from MONITOR TBD
        }
        else
        {
            return FALSE;
        }
        //Try it bit13~10 clear 
        rtd_maskl(HDMI_GPVS_reg,~(HDMI_GPVS_gmps_v_mask|HDMI_GPVS_vsps_v_mask|HDMI_GPVS_gmps_mask|HDMI_GPVS_vsps_mask),
                    (HDMI_GPVS_gmps_v(1)|HDMI_GPVS_vsps_v(1)|HDMI_GPVS_gmps(1)|HDMI_GPVS_vsps(1)|HDMI_GPVS_nps(1)|HDMI_GPVS_pis_8(1)|HDMI_GPVS_pis_7(1)|HDMI_GPVS_pis_6(1)|HDMI_GPVS_pis_5(1)|HDMI_GPVS_pvs_4(1)|HDMI_GPVS_pvs_3(1)|HDMI_GPVS_pvs_2(1)|HDMI_GPVS_pvs_1(1)|HDMI_GPVS_pvs_0(1)));		//clear packet variation status	

        HDMI_RgbYuvDetect((rtd_inl(REG_MHL_CTRL_reg) & REG_MHL_CTRL_reg_mhl_hdmisel_mask)?1:0);

    }
    else
    {
        HDMI_PRINTF("[HDMI] DVI Mode\n");
#if CONFIG_QC_MHL
        if ( !MHL_IsPPMode())
        {
            rtd_maskl(MHL_DEMUX_CTRL_reg, ~MHL_DEMUX_CTRL_dvi_ch_sync_mask, MHL_DEMUX_CTRL_dvi_ch_sync_mask);
        }
#endif
    }


    UINT8 is_interlace = (rtd_inl(HDMI_VCR_reg) & HDMI_VCR_eot_mask);
    if ( is_interlace )
    {
#if HDMI_AUTO_DEONLY
        rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_deo_mask), TMDS_PWDCTL_deo(0));
#endif
        HDMI_PRINTF("[HDMI] interlace\n");
    }
    else
    {
#if HDMI_AUTO_DEONLY
        rtd_maskl(TMDS_PWDCTL_reg,~(TMDS_PWDCTL_deo_mask), TMDS_PWDCTL_deo(1));
#endif
        HDMI_PRINTF("[HDMI] progressive\n");
    }

    UINT8 cd = drvif_Hdmi_GetColorDepth();
    switch ( cd )
    {
        case 0:
            HDMI_PRINTF("[HDMI] 24 bit mode\n");
            break;
        case 1:
            HDMI_PRINTF("[HDMI] 30 bit mode\n");
            break;
        case 2:
            HDMI_PRINTF("[HDMI] 36 bit mode\n");
            break;
        case 3:
            HDMI_PRINTF("[HDMI] 48 bit mode\n");
            break;
        default:
            HDMI_PRINTF("[HDMI] Unknown color deep mode\n");
            break;
    }

    Hdmi_VideoPLLSetting(b, cd, is_interlace);

    return TRUE;
}

unsigned char Hdmi_WaitAudioSample(void);
void Hdmi_GetAudioFreq(HDMI_AUDIO_FREQ_T *freq, HDMI_AUDIO_TRACK_MODE *track_mode);
unsigned char Hdmi_AudioPLLSetting(int freq, HDMI_AUDIO_TRACK_MODE track_mode);
void Hdmi_AudioOutputDisable(void);
void Hdmi_AudioOutputEnable(void);

bool Hdmi_Audio_Start(void)
{
	//HDMI_PRINTF("[HDMI] AUDIO_FSM_AUDIO_START\n");
	SET_HDMI_AUDIO_TYPE(HDMI_AUDIO_PCM);

	hdmiport_out(HDMI_HDMI_DBCR_VADDR , 0x00);
	/*Disable audio watch dog*/
	hdmiport_mask(HDMI_HDMI_WDCR0_VADDR ,(~_BIT15), 0x00);	//disable  tmds clock audio watch dog
	hdmiport_mask(HDMI_HDMI_WDCR0_VADDR , ~(_BIT1 |_BIT2|_BIT3 | _BIT4 ),0x00);
	Hdmi_AudioOutputDisable();

	/*Disable FIFO trend tracking*/
	hdmiport_out(HDMI_PSCR_reg,0xE2);
	/*Update Double Buffer*/
	hdmiport_out(HDMI_CMCR_reg,0x50);   //K code =2
	if(Hdmi_WaitAudioSample() == FALSE)
		return FALSE;
//	if ( HDMI_AUDIO_IS_LPCM() ||HDMI_AUDIO_SUPPORT_NON_PCM()) {
//
//	} else {
//	//				break;
//	}
	//#if HDMI_DEBUG_AUDIO_PLL_RING
	//			HDMI_DELAYMS(1000);
	//			HdmiAudioPLLSampleDump();
	//#endif
	return TRUE;
}

bool Hdmi_Audio_Freq_Detect(void)
{
	unsigned char HDMI_Audio_Conut = 0;
	HDMI_AUDIO_FREQ_T t, t2;
 	HDMI_AUDIO_TRACK_MODE track_mode;

	//HDMI_PRINTF("[HDMI] AUDIO_FSM_FREQ_DETECT\n");
	ul_audio_freq = 0;
	if (HDMI_AUDIO_IS_LPCM() == 0) {
		HDMI_PRINTF("[HDMI] NON-PCM Audio\n");
		SET_HDMI_AUDIO_TYPE(HDMI_AUDIO_NPCM);
	}
	if (HDMI_AUDIO_IS_LPCM() || HDMI_AUDIO_SUPPORT_NON_PCM()) {
		Hdmi_GetAudioFreq(&t, &track_mode);
		/*detect HDMI audio freq twice for stable freq
		USER:alanli DATE:2010/04/06*/
		Hdmi_GetAudioFreq(&t2, &track_mode);
		//HDMI_PRINTF("Hdmi_GetAudioFreq t=%d\n",t.ACR_freq);
		//HDMI_PRINTF("Hdmi_GetAudioFreq t2=%d\n",t2.ACR_freq);
		if ((t.ACR_freq != 0 )&& (t.ACR_freq==t2.ACR_freq)) {
			if (HDMI_Audio_Conut == 0){
				HDMI_Audio_Conut = 1;
				if (Hdmi_AudioPLLSetting(t.ACR_freq, track_mode) == TRUE) {
					ul_audio_freq = t.ACR_freq;
					return TRUE;
				}
			}
			else{//HDMI_Audio_Conut  = 1, force to trend_boundary tracking
				HDMI_Audio_Conut = 0;
				if (Hdmi_AudioPLLSetting(t.ACR_freq, HDMI_AUDIO_TREND_BOUND) == TRUE) {
					ul_audio_freq = t.ACR_freq;
					return TRUE;
				}
			}
		} else {
			if ((t.ACR_freq == 0)||(t2.ACR_freq == 0)){//cts = 0,use t.SPDIF_freq and force to trend_boundary tracking
				if (Hdmi_AudioPLLSetting(t.SPDIF_freq, HDMI_AUDIO_TREND_BOUND) == TRUE) {
					if (t.SPDIF_freq == t2.SPDIF_freq){
						ul_audio_freq = t.SPDIF_freq;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

bool Hdmi_Audio_Wait_PLL_Ready(void)
{
	UINT8 i;
	//HDMI_PRINTF("[HDMI] AUDIO_FSM_AUDIO_WAIT_PLL_READY\n");

	for (i = 0; i < 5; i++) {
		hdmiport_out(HDMI_HDMI_NCPER_VADDR,0xff);
		HDMI_DELAYMS(20);
		if ((hdmi_in(HDMI_HDMI_SR_VADDR) & (_BIT3|_BIT2|_BIT1))==0)
			break;
		hdmi_mask(HDMI_HDMI_SR_VADDR,~(_BIT3|_BIT2|_BIT1),(_BIT3|_BIT2|_BIT1));
	}

	//HDMI_PRINTF( "FIFO timeout count2= %d\n",i);
	if (hdmi_in(HDMI_HDMI_SR_VADDR) & (_BIT1|_BIT2|_BIT3)){
		HDMI_PRINTF("[HDMI] WARNING: Audio PLL not ready = %x\n",hdmi_in(HDMI_HDMI_SR_VADDR));
		return FALSE;
	}

	return TRUE;
}

bool Hdmi_Audio_Output(void)
{
	unsigned int i, d_code;
	
	//HDMI_PRINTF("AUDIO_FSM_AUDIO_START_OUT\n");
	rtd_maskl(HDMI_DBCR_reg , 0xF0, 0x0F);
	// FIXME:
	d_code = rtd_inl(HDMI_APLLCR3_reg);

	for (i=0; i<5; i++) {
		if (d_code == hdmiport_in(HDMI_APLLCR3_reg)) break;
	}

	hdmiport_out(HDMI_HDMI_DCAPR0_VADDR, d_code);	//pre-set D code


	hdmiport_out(HDMI_PSCR_reg,0xE2);		//pre-disable N/CTS tracking & FIFO depth
//#if HDMI_DEBUG_AUDIO_PLL_RING
//	HDMI_DELAYMS(1000);
//	HdmiAudioPLLSampleDump();
//#endif
	//Enable audio Overflow & Underflow watch dog but not Audio type wdg
	hdmiport_mask(HDMI_HDMI_WDCR0_VADDR ,(~(_BIT1|_BIT2|_BIT3 | _BIT4)), _BIT1|_BIT2|_BIT3 | _BIT4);
	hdmiport_mask(HDMI_HDMI_WDCR0_VADDR , (~_BIT15),_BIT15);//Enable audio tmds clock  watch dog

	//Hdmi_VideoOutputEnable();
	Hdmi_AudioOutputEnable();

	hdmiport_mask(HDMI_AOCR_reg,(unsigned char)(~0x0ff),0xFF);	//Enable SPDIF/I2S Output

	return TRUE;
}

bool Hdmi_Audio_Check(void)
{
	// if FIFO overflow then restart Audio process
	if (hdmi_in(HDMI_HDMI_SR_VADDR) & (_BIT3)) {
		HDMI_PRINTF( "Audio Output Disable cause by pll unlock :%x\n",hdmi_in(HDMI_HDMI_SR_VADDR));
		Hdmi_AudioOutputDisable();
		return FALSE;
	}
	if(hdmi_in(HDMI_HDMI_SR_VADDR) & (_BIT1|_BIT2)) {
		HDMI_PRINTF( "Audio Output Disable cause by over_underflow :%x\n",hdmi_in(HDMI_HDMI_SR_VADDR));
		Hdmi_AudioOutputDisable();
		return FALSE;
	}

	if ((hdmi_in(HDMI_HDMI_AVMCR_VADDR) & (_BIT5)) == 0) {
		HDMI_PRINTF( "Audio Output Disable cause by AVMCR output disable:%x\n",hdmi_in(HDMI_HDMI_AVMCR_VADDR));
		Hdmi_AudioOutputDisable();
		return FALSE;
	}

	if ((HDMI_AUDIO_IS_LPCM() == 0) && (HDMI_AUDIO_SUPPORT_NON_PCM()==0)) {		// if TX change audio mode to non-LPCM
		Hdmi_AudioOutputDisable();
		HDMI_PRINTF( "Audio Output Disable cause non-Linear PCM\n");
		return FALSE;
	}
	if ( ((HDMI_AUDIO_IS_LPCM()) && GET_HDMI_AUDIO_TYPE()) || ((HDMI_AUDIO_IS_LPCM() == 0) && (GET_HDMI_AUDIO_TYPE()==0))) {
		Hdmi_AudioOutputDisable();
		HDMI_PRINTF( "Audio Type change \n");
		return FALSE;
	}
	return TRUE;
}

bool Hdmi_AudioModeDetect(void)
{
unsigned long ul_fq;
	if ( !Hdmi_Audio_Start() ) {
		HDMI_PRINTF("[HDMI] WARNING: No audio sample.\n");
		return FALSE;
	}
	mdelay(20);
	if ( !Hdmi_Audio_Freq_Detect() ) {
		HDMI_PRINTF("[HDMI] WARNING: Cannot detect audio freq.\n");
		return FALSE;
	}
	mdelay(20);
	if ( !Hdmi_Audio_Wait_PLL_Ready() ) {
		HDMI_PRINTF("[HDMI] WARNING: Audio PLL is not ready.\n");
		return FALSE;
	}
	mdelay(20);
	if ( !Hdmi_Audio_Output() ) {
		return FALSE;
	}

	#include "HDMI_AUDIO/sirius_init_audio.tbl"
	#include "HDMI_AUDIO/sirius_SPDIF_fromHDMI.tbl"
	#include "HDMI_AUDIO/sirius_DAC1_HP.tbl"

	ul_fq = ul_audio_freq/1000;
	if ( ul_fq==32 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_32K.tbl"
	}
	else if ( ul_fq==44 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_441K.tbl"
	}
	else if ( ul_fq==48 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_48K.tbl"
	}
	else if ( ul_fq==88 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_882K.tbl"
	}
	else if ( ul_fq==96 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_96K.tbl"
	}
	else if ( ul_fq==176 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_1764K.tbl"
	}
	else if ( ul_fq==192 ) {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_192K.tbl"
	}
	else {
		#include "HDMI_AUDIO/Sirius_PLLSPDIF_48K.tbl"
	}
	return TRUE;
}

unsigned char Hdmi_WaitAudioSample(void)
{
	char   timeout_cnt = 6;
	/*
		looking for ACR info using RSV2
	*/

	rtd_maskl(HDMI_HDMI_PTRSV1_VADDR, ~0x00FF00, 0x02<< 8 );		// Wait for ACR : Packet Type = 0x01
	hdmi_out(HDMI_HDMI_GPVS_VADDR, _BIT6);  // Clear RSV2 indicator
	
	for (;timeout_cnt>0;timeout_cnt--)  { // Wait 30ms max. to wait ACR
		 HDMI_DELAYMS(10);
		if (hdmi_in(HDMI_HDMI_GPVS_VADDR) & _BIT6)	{
			hdmi_out(HDMI_HDMI_PSAP_VADDR, 110);

			if (hdmi_in(HDMI_HDMI_PSDP_VADDR) & 0x10) {
//				SET_HDMI_AUDIO_LAYOUT(1);
			} else {
//				SET_HDMI_AUDIO_LAYOUT(0);
			}
//			HDMI_PRINTF("Layout = %d\n", GET_HDMI_AUDIO_LAYOUT());
#if HDMI_SUPPORT_HBR
		timeout_cnt = 6;
//		hdmi_out(HDMI_HBR_PACKET_VADDR,0x06);
		for (;timeout_cnt>0;timeout_cnt--)  { // Wait 30ms max. to wait HBR
			 HDMI_DELAYMS(5);
			if  (hdmi_in(HDMI_HBR_PACKET_VADDR) & 0x01) {
//				hdmi_out(HDMI_HBR_PACKET_VADDR,0x04);
				SET_HDMI_HBR_MODE(0);
		       	HDMI_PRINTF("Both Packet 2 and HBR exist\n");
			}
		}
#else
		hdmi_out(HDMI_HIGH_BIT_RATE_AUDIO_PACKET_VADDR, 0x04);
		//HDMI_PRINTF("Audio sample counter = %d\n",timeout_cnt);
#endif
		return TRUE;
		}

	}
#if HDMI_SUPPORT_HBR
		timeout_cnt = 6;
//		hdmi_out(HDMI_HBR_PACKET_VADDR,0x06);
		for (;timeout_cnt>0;timeout_cnt--)  { // Wait 30ms max. to wait HBR
			 HDMI_DELAYMS(5);
			if  (hdmi_in(HDMI_HBR_PACKET_VADDR) & 0x01) {
//				hdmi_out(HDMI_HBR_PACKET_VADDR,0x06);
				SET_HDMI_HBR_MODE(1);
				//hdmiport_out(0x61, 0xd8); //for arrange HBR channel
			       HDMI_PRINTF("Only HBR exist\n");
   				return TRUE;
			}
		}
#endif
	//HDMI_PRINTF("Audio Sample miss\n");
	return FALSE;
}

unsigned char inline Hdmi_PacketSRAMRead(unsigned char addr)
{
	hdmi_out(HDMI_HDMI_PSAP_VADDR, addr);
	return hdmi_in(HDMI_HDMI_PSDP_VADDR) ;
}

unsigned char Hdmi_WaitACR(void)
{

	char   timeout_cnt = 6;

	/*
		looking for ACR info using RSV1
	*/

	hdmiport_mask(HDMI_HDMI_PTRSV1_VADDR, ~0xFF0000, 0x01<<16);		// Wait for ACR : Packet Type = 0x01
	hdmi_mask(HDMI_HDMI_GPVS_VADDR, ~(_BIT7), _BIT7);  // Clear RSV3 indicator

	for (;timeout_cnt>0;timeout_cnt--)  { // Wait 30ms max. to wait ACR
		if (hdmi_in(HDMI_HDMI_GPVS_VADDR) & _BIT7)
				if(Hdmi_PacketSRAMRead(140) == 0)  return TRUE;  // if ACR in BCH correct
		 HDMI_DELAYMS(5);
	}
	//HDMI_PRINTF("[HDMI] N&CTS counter= %d \n",timeout_cnt);
	// timeout
	return FALSE;
}

int Hdmi_AudioFreqCorrect(unsigned int freq, unsigned long b, HDMI_AUDIO_TRACK_MODE *track_mode)
{

	/*
		TO-DO : use ABS function
	*/
	unsigned int b_ratio=1000;
	*track_mode = HDMI_AUDIO_N_CTS_TREND_BOUND;

	freq *= 10;
	if((freq >= (31700*b_ratio/100)) && (freq <= (32300*b_ratio/100)))
            freq = 32000;
	else if((freq >= (43500*b_ratio/100)) && (freq <= (44600*b_ratio/100)))
            freq = 44100;
	else if((freq >= 47500*b_ratio/100) && (freq <= (48500*b_ratio/100)))
            freq = 48000;
	else if((freq >= (87700*b_ratio/100)) && (freq <= (88700*b_ratio/100)))
            freq = 88200;
	else if((freq >= (95500*b_ratio/100)) && (freq <= (96500*b_ratio/100)))
            freq = 96000;
	else if((freq >= (175400*b_ratio/100)) && (freq <= (177400*b_ratio/100)))
            freq = 176400;
	else if((freq >= (191000*b_ratio/100)) && (freq <= (193000*b_ratio/100)))
            freq = 192000;
	else
	     freq = 0;


	return freq;
}

void Hdmi_GetAudioFreq(HDMI_AUDIO_FREQ_T *freq, HDMI_AUDIO_TRACK_MODE *track_mode)
{
	unsigned long cts, n , b;
	unsigned char count=0;
//	HDMIRX_IOCTL_STRUCT_T isr_info;

	freq->ACR_freq = 0;
	freq->AudioInfo_freq = 0;
	freq->SPDIF_freq = 0;

	/*
		Set trigger to get CTS&N and LPCM Channel Status Info
	*/

	//Start Pop up N_CTS value
	hdmiport_mask(HDMI_HDMI_ACRCR_VADDR, ~(_BIT1|_BIT0),_BIT1|_BIT0);

	// Restart measure b
	hdmiport_mask(HDMI_HDMI_NTX1024TR0_VADDR,~ _BIT3,_BIT3);


	// Clear Info Frame update indicator
	hdmiport_out(HDMI_HDMI_ASR0_VADDR, 0x07);


	if (Hdmi_WaitACR() == FALSE) {
		HDMI_PRINTF("[HDMI] No CTS & N Packet\n");
	};

	//HDMI_DELAYMS(25 * 6);
	for (count = 0; count < 150; count++) {
	//while(1) {

		//HDMI_LOG("HDMI_HDMI_ACRCR_VADDR=%x\n",hdmi_in(HDMI_HDMI_ACRCR_VADDR));

		//HDMI_LOG("HDMI_HDMI_NTX1024TR0_VADDR=%x\n",hdmi_in(HDMI_HDMI_NTX1024TR0_VADDR));

//		if (((hdmiport_in(HDMI_HDMI_ACRCR_VADDR) & (_BIT1|_BIT0)) == 0) && ((hdmiport_in(HDMI_HDMI_ASR0_VADDR) & 0x03) == 0x03))	//adams modify form 0x3 ot 0x1, 20120612,for STB LT5K no sound
		if (((hdmiport_in(HDMI_HDMI_ACRCR_VADDR) & (_BIT1|_BIT0)) == 0) && ((hdmiport_in(HDMI_HDMI_ASR0_VADDR) & 0x01) == 0x01))
			break;

		HDMI_DELAYMS(1);
	}

	cts= HDMI_ACRSR0_get_cts(rtd_inl(HDMI_ACRSR0_reg));
	n =  HDMI_ACRSR1_get_n(rtd_inl(HDMI_ACRSR1_reg));

	ACR_N = n;
//	HdmiGetStruct(&isr_info);
	b = Hdmi_get_b_value();

	HDMI_PRINTF("[HDMI] cts=%ld n=%ld b=%ld\n",cts, n, b);

	if(cts==0 || n==0 || b == 0)  goto METHOD_AUDIO_INFO;

	// 128fs = 1024/b * fx * N / CTS  =>  fs = (1024 * fx *N)/(128 * b * CTS) = (8 * fx *N)/(b*CTS)
	// calculate freq in 0.1kHz unit
	// freq = (unsigned long)8 * 2 * 10000 * HDMI_RTD_XTAL/ cts * n / ((unsigned long)b * 1000);
#if HDMI_OLD_CLK_DETECT
	freq->ACR_freq = (8 * 2 * 27000 *10/b)*n/cts;
	freq->ACR_freq  = (freq->ACR_freq >> 1) + (freq->ACR_freq & 0x01); 	//四捨五入//
	freq->ACR_freq *= 100;
#else 
	freq->ACR_freq = ((((270000 * b)/256)/128) * n) / (cts);
	freq->ACR_freq *= 100;
#endif
	freq->ACR_freq = Hdmi_AudioFreqCorrect(freq->ACR_freq, b, track_mode);

	/*
		Get Audio Frequency from Audio Info Frame
	*/
	METHOD_AUDIO_INFO:

//	if ((hdmiport_in(HDMI_HDMI_ASR0_VADDR) & 0x03) == 0x03)  {		//adams modify form 0x3 ot 0x1, 20120612,for STB LT5K no sound
	if ((hdmiport_in(HDMI_HDMI_ASR0_VADDR) & 0x01) == 0x01)  {

		freq->SPDIF_freq = AUDIO_CHANNEL_STATUS[hdmiport_in(HDMI_HDMI_ASR1_VADDR)&0xf];

	}

	HDMI_PRINTF("[HDMI] SPDIF freq=%ld; ACR_freq=%ld\n", freq->SPDIF_freq, freq->ACR_freq);

}

unsigned char Hdmi_AudioPLLSetting(int freq, HDMI_AUDIO_TRACK_MODE track_mode)
{

	//UINT8 coeff = 0, rate = 0, lvr=0;
	UINT8 i;
	int timeout = 10;
	UINT32 tmp1;
	UINT32 I_Code=0,S=0;
	//UINT32 b;//cts,n,b;
	//HDMIRX_IOCTL_STRUCT_T isr_info;
	//HDMI_LOG( "HDMI_HDMI_AVMCR_VADDR = %x\n", hdmiport_in(HDMI_HDMI_AVMCR_VADDR));


	for (i=0; i < 7; i++) {
		if (audio_pll_coeff[i].freq == freq)  {
			//coeff = audio_pll_coeff[i].coeff;
			//rate = audio_pll_coeff[i].rate;
			goto PLL_SETTING;
		}
	}
	HDMI_PRINTF( "[HDMI] Unsupport audio freq = %d\n", freq);
	return FALSE;

	PLL_SETTING:
/*						//adams mask 20120612,for STB LT5K no sound
	if (ACR_N == 0) {
		HDMI_PRINTF( "ACR_N = 0\n");
		return FALSE;
	}
*/
	/*(2)audio output enable = auto mode*/
	rtd_maskl(HDMI_AFCR_reg,~_BIT6,_BIT6);
	/*(3)Disable trend and boundary tracking*/
	rtd_maskl(HDMI_WDCR0_reg,~HDMI_WDCR0_bt_track_en_mask,0x0);//<2>Disable trend and boundary tracking
	rtd_maskl(HDMI_PSCR_reg, ~(_BIT3 |_BIT2),0x00);//<1>Disable trend and boundary tracking
	rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);//Update Double Buffer
	/*(4)FSM back to Pre-mode*/
	rtd_maskl(HDMI_AVMCR_reg , ~_BIT5,0x00);
	/*(5)Disable N/CTS tracking*/
	rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~_BIT20,0x0);		//CTS has glitch not to tracking disable
	rtd_maskl(AUDIO_N_UP_BOUND_reg,~_BIT20,0x0);			//N has glitch not to tracking disable
	rtd_maskl(HDMI_PSCR_reg , ~_BIT4,0x00);
	rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);//Update Double Buffer
	/*(6)Disable SDM*/
	rtd_maskl(HDMI_AAPNR_reg, ~_BIT1,0x0);
	/*(7)Disable PLL*/
	//rtd_maskl(HDMI_APLLCR1_reg,  ~( _BIT2 | _BIT0| _BIT13| _BIT12| _BIT11), (_BIT2 | _BIT0)); // Disable PLL
	// cloud modify magellan remove bit 16 ~bit10  , need check
	rtd_maskl(HDMI_APLLCR1_reg,  ~( HDMI_APLLCR1_dpll_freeze_mask | HDMI_APLLCR1_dpll_pwdn_mask), (HDMI_APLLCR1_dpll_freeze_mask | HDMI_APLLCR1_dpll_pwdn_mask)); // Disable PLL
	/*(8)resetS &S1 code to avoid dead lock*/
	rtd_maskl(HDMI_CMCR_reg,  ~( _BIT6|_BIT5), 0x0); // PLL output clk sel from crystal
	rtd_outl(HDMI_SCAPR_reg,0x00);	//S1 & S2 code clear to 0 , to avoid dead lock
	rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);//Update Double Buffer
	HDMI_DELAYMS(1);
	rtd_maskl(HDMI_CMCR_reg,  ~( _BIT6|_BIT5), (_BIT6)); // PLL output clk sel from VCO
	rtd_outl(HDMI_CMCR_reg,  0x50);	//Enable Double Buffer
	/*(9)D code*/
	rtd_outl(HDMI_DCAPR0_reg, (hdmi_audiopll_param[i].D_HighByte << 8) | hdmi_audiopll_param[i].D_LowByte);
	rtd_maskl(HDMI_CMCR_reg,~(HDMI_CMCR_dbdcb_mask),HDMI_CMCR_dbdcb(1));				//Enable Double Buffer for K/M/S/D/O

	/*(10)Initial PLL*/
	rtd_maskl(HDMI_APLLCR0_reg, ~(HDMI_APLLCR0_dpll_m_mask |HDMI_APLLCR0_dpll_o_mask |HDMI_APLLCR0_dpll_n_mask),
									HDMI_APLLCR0_dpll_m(hdmi_audiopll_param[i].M - 2) | HDMI_APLLCR0_dpll_o(hdmi_audiopll_param[i].O));
	rtd_maskl(HDMI_CMCR_reg,~(HDMI_CMCR_dbdcb_mask),HDMI_CMCR_dbdcb(1));				//Enable Double Buffer for K/M/S/D/O

	if (hdmi_audiopll_param[i].N < 2) {
		rtd_maskl(HDMI_APLLCR0_reg, ~(HDMI_APLLCR0_dpll_bpn_mask | HDMI_APLLCR0_dpll_n_mask), 	HDMI_APLLCR0_dpll_bpn(1) |	HDMI_APLLCR0_dpll_n(0));		//set audio PLL N code
	} else {
		rtd_maskl(HDMI_APLLCR0_reg, ~(HDMI_APLLCR0_dpll_bpn_mask | HDMI_APLLCR0_dpll_n_mask),
									HDMI_APLLCR0_dpll_bpn(0) |	HDMI_APLLCR0_dpll_n(hdmi_audiopll_param[i].N-2));		//set audio PLL N code
	}
	rtd_maskl(HDMI_CMCR_reg,~(HDMI_CMCR_dbdcb_mask),HDMI_CMCR_dbdcb(1));				//Enable Double Buffer for K/M/S/D/O
	rtd_outl(HDMI_SCAPR_reg,  (hdmi_audiopll_param[i].S1) ? ((hdmi_audiopll_param[i].S / 2) | 0x80) : (hdmi_audiopll_param[i].S / 2));
	rtd_outl(PRESET_S_CODE1_reg, 0xf800);		//S1 code
	rtd_maskl(HDMI_APLLCR0_reg,~(_BIT2|_BIT1|_BIT0), 0x3);		//set Icp
	rtd_maskl(HDMI_CMCR_reg,~_BIT4,_BIT4);				//Enable Double Buffer for K/M/S/D/O
	rtd_maskl(HDMI_APLLCR0_reg,~(_BIT5|_BIT4|_BIT3),(_BIT4| _BIT3) );	//set RS=13k
	rtd_maskl(HDMI_CMCR_reg,~_BIT4,_BIT4);				//Enable Double Buffer for K/M/S/D/O

	//rtd_maskl(HDMI_APLLCR1_reg,~(_BIT18|_BIT17),(_BIT18|_BIT17) );			//set CS=42pf
	rtd_maskl(HDMI_APLLCR1_reg,~(HDMI_APLLCR1_dpll_CS_MASK),(HDMI_APLLCR1_dpll_CS_66P) );			//set CS=42pf
	//rtd_maskl(HDMI_HDMI_APLLCR1_ADDR,~_BIT1,_BIT1);			// Enable divider K and enable VCOSTART
	rtd_maskl(HDMI_CMCR_reg,~_BIT4,_BIT4);				//Enable Double Buffer for K/M/S/D/O
	//rtd_maskl(HDMI_APLLCR1_reg,~(_BIT3 | _BIT1 |_BIT0), (_BIT3 | _BIT1));//Enable PLL
	rtd_maskl(HDMI_APLLCR1_reg,~(HDMI_APLLCR1_dpll_stop_mask | HDMI_APLLCR1_dpll_vcorstb_mask |HDMI_APLLCR1_dpll_pwdn_mask), (HDMI_APLLCR1_dpll_stop_mask | HDMI_APLLCR1_dpll_vcorstb_mask));//Enable PLL
	//PLL Calibration
	//rtd_maskl(HDMI_APLLCR1_reg,  ~(_BIT15|_BIT16), _BIT16); // Set VCO default    //cloud mark for magellan 2013 0110
       //HDMI_DELAYMS(1);
      // rtd_maskl(HDMI_APLLCR1_reg, ~_BIT11, _BIT11);         // Reg DPLL_CMPEN       //cloud mark for magellan 2013 0110
      // HDMI_DELAYMS(1);
      // rtd_maskl(HDMI_APLLCR1_reg, ~_BIT12, _BIT12);         // Reg DPLL_CALLCH      //cloud mark for magellan 2013 0110
      // HDMI_DELAYMS(1);
      // rtd_maskl(HDMI_APLLCR1_reg, ~_BIT13, _BIT13);         // Reg DPLL_CALSW      //cloud mark for magellan 2013 0110
	//HDMI_PRINTF(" m = %x\n o = %x\n s = %x\n ", hdmi_audiopll_param[i].M, hdmi_audiopll_param[i].O, hdmi_audiopll_param[i].S);
       //Wait PLL Stable
       HDMI_DELAYMS(1);
	//PLL un-freeze
	//rtd_maskl(HDMI_APLLCR1_reg,~_BIT2, 0x0); //DPLL normal->clk really output to fifo for read
	rtd_maskl(HDMI_APLLCR1_reg,~HDMI_APLLCR1_dpll_freeze_mask,0x0);//
	/*(11)Enable SDM*/
	//rtd_maskl(HDMI_AAPNR_reg, ~_BIT1,_BIT1);
	rtd_maskl(HDMI_AAPNR_reg, ~HDMI_AAPNR_esdm_mask,HDMI_AAPNR_esdm_mask);
	HDMI_DELAYMS(1);

	if(track_mode == HDMI_AUDIO_N_CTS_TREND_BOUND)
	{
		HDMI_PRINTF("[HDMI] *****N/CTS Trend& Boundary Tracking*****\n");
	/*(12)Enable N/CTS tracking*/
		/*Modify N/CTS tracking parameter  USER:kistlin DATE:2011/08/04*/
		//for phase error count source Fpec = Fdds = Fvco/4
		//PEpec x Tpec = delta(Tvco)xNxSxPLLO = Tvco(1/8)(D[15:0]/2^16)xNxSxPLLO
		//D[15:0] = PEpec x Tpec /[Tvco(1/8)(1//2^16)xNxSxPLLO]
		//and D[15:0] = PEpec x (1/8)Icode
		//Icode calculate I code =2^24/(N*S*PLLO)	
		 
		//for phase error count source = fvco/4,fdds
		//Icode calculate I code =2*2048*2^10/(N*S*PLLO)-->x2 才夠力 20110701 kist
			if (hdmi_audiopll_param[i].S1)
				S = hdmi_audiopll_param[i].S*2;
			else 
				S = hdmi_audiopll_param[i].S;
			//HDMI_PRINTF("S = %d , ACR_N=%d , 	hdmi_audiopll_param[i].O = %d\n",S, ACR_N, hdmi_audiopll_param[i].O ); 		
			if (ACR_N)
				{
				I_Code =16*1024*1024/(ACR_N*S*(hdmi_audiopll_param[i].O<<1));
				I_Code = I_Code;
				}
			else
				I_Code = 0x02;

		//calculate 4*N*(1/128fa) or 4*CTS*Tv, 4x for delay (HDMI_DELAYMS(1) 約為300us)
		tmp1 = 4*ACR_N*1000/(128*freq);
		if (tmp1 < 5)
			tmp1 = tmp1;//CTS*Tv < tmp1/4 > 2* CTS*Tv,  CTS*Tv(0.67ms~3.3ms)
		else if (tmp1 < 9)
			tmp1 = tmp1+2;
		else
			tmp1 = tmp1+3;

		//HDMI_PRINTF( "I Code = %d\n",I_Code);
		//HDMI_PRINTF( "tmp1 = %d\n",tmp1);

		rtd_outl(HDMI_ICPSNCR0_reg,I_Code);     //Set I code of Ncts[15:8]
		rtd_outl(HDMI_PCPSNCR0_reg,0x0000);	//Set P code of Ncts [15:8]
	//	rtd_maskl(HDMI_NPECR_reg,~_BIT30,_BIT30);	//N_CTS tracking re-enable toggle function enable
	      rtd_maskl(HDMI_NPECR_reg,~HDMI_NPECR_ncts_re_enable_off_en_mask,HDMI_NPECR_ncts_re_enable_off_en_mask);
		rtd_outl(HDMI_PSCR_reg,0x92);	//Enable N_CTS tracking & set FIFO depth
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer
#if 0
		if (tmp1 > 9)
			{
			HDMI_DELAYMS(tmp1-9);// HDMI_DELAYMS 要小於10 才行,所以做兩次,因為兩個的單位不大一樣
			HDMI_DELAYMS(9);
			}
		else
			HDMI_DELAYMS(tmp1);
#endif	
		rtd_outl(HDMI_PETR_reg,0x1e);//phase error threshold
     		 for (timeout = 0; timeout < 25; timeout++) {
			rtd_maskl(HDMI_SR_reg,~_BIT3,_BIT3);
			rtd_outl(HDMI_NCPER_reg,0xff);
			HDMI_DELAYMS(20);
			if ((rtd_inl(HDMI_HDMI_SR_VADDR) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
		{
			HDMI_PRINTF( "[HDMI] WARNING: PLL 1st check not lock = %x\n",rtd_inl(HDMI_NCPER_reg));
		}
		else
		{
			//HDMI_PRINTF( "[HDMI] PLL 1st check lock count = %d\n",timeout);
		}


		//rtd_maskl(HDMI_PSCR_reg,~_BIT4,0);	//disable N_CTS tracking
		rtd_maskl(HDMI_PSCR_reg,~HDMI_PSCR_etcn_mask,0);
		//rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer
		rtd_maskl(HDMI_CMCR_reg,~HDMI_CMCR_dbdcb_mask , HDMI_CMCR_dbdcb_mask);	//Update Double Buffer
		//rtd_maskl(HDMI_NPECR_reg,~_BIT30,0);	//N_CTS tracking re-enable toggle function disable
	      rtd_maskl(HDMI_NPECR_reg,~HDMI_NPECR_ncts_re_enable_off_en_mask,0);
		//rtd_outl(HDMI_ICPSNCR0_reg,0x0002);     //Set I code of Ncts[15:8]
		rtd_outl(HDMI_ICPSNCR0_reg,(HDMI_ICPSNCR0_icl(0x02)|HDMI_ICPSNCR0_ich(0)));     //Set I code of Ncts[15:8]
		//rtd_outl(HDMI_PCPSNCR0_reg,0x2000);	//Set P code of Ncts [15:8]
		rtd_outl(HDMI_PCPSNCR0_reg,(HDMI_PCPSNCR0_pcl(0x0)|HDMI_PCPSNCR0_pch(0x20)));	//Set P code of Ncts [15:8]
	      //rtd_maskl(HDMI_PSCR_reg,~_BIT4,_BIT4);	//enable N_CTS tracking
		rtd_maskl(HDMI_PSCR_reg,~HDMI_PSCR_etcn_mask,HDMI_PSCR_etcn_mask);
		//rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer
		rtd_maskl(HDMI_CMCR_reg,~HDMI_CMCR_dbdcb_mask,HDMI_CMCR_dbdcb_mask);
		//N&CTS boundary set
		//rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~0xfffff,0x6ddd0);		//CTS up boundary set 450000
		rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~(AUDIO_CTS_UP_BOUND_cts_up_bound_mask),AUDIO_CTS_UP_BOUND_cts_up_bound(450000));		//CTS up boundary set 450000
		rtd_maskl(AUDIO_CTS_LOW_BOUND_reg,~0xfffff,0x4e20);		//CTS low boundary set 20000
		rtd_maskl(AUDIO_N_UP_BOUND_reg,~0xfffff,0x13880);		//N up boundary set 80000
		rtd_maskl(AUDIO_N_LOW_BOUND_reg,~0xfffff,0x7d0);		//N low boundary set 2000
		rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~_BIT20,_BIT20);		//CTS has glitch not to tracking enable
		rtd_maskl(AUDIO_N_UP_BOUND_reg,~_BIT20,_BIT20);			//N has glitch not to tracking enable 

       	/*(13)Wait PLL lock by N&CTS tracking*/
       	rtd_outl(HDMI_PETR_reg,0x1e);//phase error threshold
     		 for (timeout = 0; timeout < 25; timeout++) {
			rtd_maskl(HDMI_SR_reg,~_BIT3,_BIT3);
			rtd_outl(HDMI_NCPER_reg,0xff);
			HDMI_DELAYMS(20);
			if ((rtd_inl(HDMI_HDMI_SR_VADDR) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
		{
			HDMI_PRINTF( "[HDMI] WARNING: PLL not lock = %x\n",rtd_inl(HDMI_NCPER_reg));
		}
		else
		{
			//HDMI_PRINTF( "[HDMI] PLL lock count = %d\n",timeout);
		}
	
		/*(14)FSM Initial*/
		//hdmiport_out(HDMI_HDMI_FBR_VADDR,0x77);//Target FIFO depth = 14 ,Boundary address distance = 7
		rtd_outl(HDMI_FBR_reg,0x74);
		//hdmiport_out(HDMI_HDMI_FTR_VADDR,0x03);//target times for summation of one trend to decide the trend
		rtd_maskl(HDMI_AVMCR_reg,~_BIT6,_BIT6);//FSM entry Pre-mode (AOC=1)
		rtd_maskl(HDMI_AVMCR_reg,~_BIT5,_BIT5);//FSM entry next step (AOMC=1)
		HDMI_DELAYMS(1);//wait fifo to target fifo level

		/*(15)Enable trend and boundary tracking*/
		rtd_outl(HDMI_ICTPSR0_reg,0x0005);      	//Set I code  of trend [15:8]
		rtd_outl(HDMI_PCTPSR0_reg,0x02FF);	//Set P code of trend [15:8]
		rtd_outl(HDMI_ICBPSR0_reg,0x0005);      //Set I code of bnd [15:8]
		rtd_outl(HDMI_PCBPSR0_reg,0x02FF);	//Set P code of bnd [15:8]
		rtd_outl(HDMI_STBPR_reg,0x01);		//Set Boundary Tracking Update Response Time
		rtd_maskl(HDMI_PSCR_reg , ~(_BIT3|_BIT2), (_BIT3|_BIT2));//<1>Enable trend and boundary tracking
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);//Update Double Buffer
		HDMI_DELAYMS(20);
		rtd_maskl(HDMI_WDCR0_reg,~HDMI_WDCR0_bt_track_en_mask,HDMI_WDCR0_bt_track_en_mask);//<2>Enable trend and boundary tracking
	}
	else if(track_mode == HDMI_AUDIO_TREND_BOUND)
	{
		HDMI_PRINTF("[HDMI] ***** TREND_BOUND Tracking*****\n");
		/*(14)FSM Initial*/
		//hdmiport_out(HDMI_HDMI_FBR_VADDR,0x77);//Target FIFO depth = 14 ,Boundary address distance = 7
		rtd_outl(HDMI_FBR_reg,0x74);
		//hdmiport_out(HDMI_HDMI_FTR_VADDR,0x03);//target times for summation of one trend to decide the trend
		rtd_maskl(HDMI_AVMCR_reg,~_BIT6,_BIT6);//FSM entry Pre-mode (AOC=1)
		rtd_maskl(HDMI_AVMCR_reg,~_BIT5,_BIT5);//FSM entry next step (AOMC=1)
		HDMI_DELAYMS(1);//wait fifo to target fifo level

		/*(15)Enable trend and boundary tracking*/
		rtd_outl(HDMI_ICTPSR0_reg,0x0005);      	//Set I code  of trend [15:8]
		rtd_outl(HDMI_PCTPSR0_reg,0x02FF);	//Set P code of trend [15:8]
		rtd_outl(HDMI_ICBPSR0_reg,0x0001);      //Set I code of bnd [15:8]
		rtd_outl(HDMI_PCBPSR0_reg,0x02FF);	//Set P code of bnd [15:8]
		rtd_outl(HDMI_STBPR_reg,0x01);		//Set Boundary Tracking Update Response Time
		rtd_outl(HDMI_PSCR_reg,  (HDMI_PSCR_fdint(4) | HDMI_PSCR_etcn(0) | HDMI_PSCR_etfd(1) | HDMI_PSCR_etfbc(1) |HDMI_PSCR_pecs(2)));// FIFO depth tracking
		rtd_maskl(HDMI_PSCR_reg , ~(_BIT3|_BIT2), (_BIT3|_BIT2));//<1>Enable trend and boundary tracking
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);//Update Double Buffer
		HDMI_DELAYMS(20);
		rtd_maskl(HDMI_WDCR0_reg,~HDMI_WDCR0_bt_track_en_mask,HDMI_WDCR0_bt_track_en_mask);//<2>Enable trend and boundary tracking
	}else{//  H/W N/CTS Tracking
		HDMI_PRINTF("[HDMI] ***** N/CTS Tracking*****\n");
		/*(12)Enable N/CTS tracking*/
		if (hdmi_audiopll_param[i].S1)
				S = hdmi_audiopll_param[i].S*2;
			else 
				S = hdmi_audiopll_param[i].S;
			//HDMI_PRINTF("S = %d , ACR_N=%d , 	hdmi_audiopll_param[i].O = %d\n",S, ACR_N, hdmi_audiopll_param[i].O ); 		
			if (ACR_N)
				{
				I_Code =16*1024*1024/(ACR_N*S*(hdmi_audiopll_param[i].O<<1));
				I_Code = I_Code;
				}
			else
				I_Code = 0x02;

		//calculate 4*N*(1/128fa) or 4*CTS*Tv, 4x for delay (HDMI_DELAYMS(1) 約為300us)
		tmp1 = 4*ACR_N*1000/(128*freq);
		if (tmp1 < 5)
			tmp1 = tmp1;//CTS*Tv < tmp1/4 > 2* CTS*Tv,  CTS*Tv(0.67ms~3.3ms)
		else if (tmp1 < 9)
			tmp1 = tmp1+2;
		else
			tmp1 = tmp1+3;

		//HDMI_PRINTF( "I Code = %d\n",I_Code);
		//HDMI_PRINTF( "tmp1 = %d\n",tmp1);

		rtd_outl(HDMI_ICPSNCR0_reg,I_Code);     //Set I code of Ncts[15:8]
		rtd_outl(HDMI_PCPSNCR0_reg,0x0000);	//Set P code of Ncts [15:8]
		//rtd_maskl(HDMI_NPECR_reg,~_BIT30,_BIT30);	//N_CTS tracking re-enable toggle function enable
		rtd_maskl(HDMI_NPECR_reg,~HDMI_NPECR_ncts_re_enable_off_en_mask,HDMI_NPECR_ncts_re_enable_off_en_mask);
		rtd_outl(HDMI_PSCR_reg,0x92);	//Enable N_CTS tracking & set FIFO depth
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer
#if 0
		if (tmp1 > 9)
			{
			HDMI_DELAYMS(tmp1-9);// HDMI_DELAYMS 要小於10 才行,所以做兩次,因為兩個的單位不大一樣
			HDMI_DELAYMS(9);
			}
		else
			HDMI_DELAYMS(tmp1);
#endif	
		rtd_outl(HDMI_PETR_reg,0x1e);//phase error threshold
     		 for (timeout = 0; timeout < 25; timeout++) {
			rtd_maskl(HDMI_SR_reg,~_BIT3,_BIT3);
			rtd_outl(HDMI_NCPER_reg,0xff);
			HDMI_DELAYMS(20);
			if ((rtd_inl(HDMI_HDMI_SR_VADDR) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
		{
			HDMI_PRINTF( "[HDMI] WARNING: PLL 1st check not lock = %x\n",rtd_inl(HDMI_NCPER_reg));
		}
		else
		{
			//HDMI_PRINTF( "[HDMI] PLL 1st check lock count = %d\n",timeout);
		}


		rtd_maskl(HDMI_PSCR_reg,~_BIT4,0);	//disable N_CTS tracking
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer
		//rtd_maskl(HDMI_NPECR_reg,~_BIT30,0);	//N_CTS tracking re-enable toggle function disable
		rtd_maskl(HDMI_NPECR_reg,~HDMI_NPECR_ncts_re_enable_off_en_mask,0);//N_CTS tracking re-enable toggle function disable
		rtd_outl(HDMI_ICPSNCR0_reg,0x0002);     //Set I code of Ncts[15:8]
		rtd_outl(HDMI_PCPSNCR0_reg,0x2000);	//Set P code of Ncts [15:8]
		rtd_maskl(HDMI_PSCR_reg,~_BIT4,_BIT4);	//enable N_CTS tracking
		rtd_maskl(HDMI_CMCR_reg,~_BIT4 , _BIT4);	//Update Double Buffer

		//N&CTS boundary set
		rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~0xfffff,0x6ddd0);		//CTS up boundary set 450000
		rtd_maskl(AUDIO_CTS_LOW_BOUND_reg,~0xfffff,0x4e20);		//CTS low boundary set 20000
		rtd_maskl(AUDIO_N_UP_BOUND_reg,~0xfffff,0x13880);		//N up boundary set 80000
		rtd_maskl(AUDIO_N_LOW_BOUND_reg,~0xfffff,0x7d0);		//N low boundary set 2000
		rtd_maskl(AUDIO_CTS_UP_BOUND_reg,~_BIT20,_BIT20);		//CTS has glitch not to tracking enable
		rtd_maskl(AUDIO_N_UP_BOUND_reg,~_BIT20,_BIT20);			//N has glitch not to tracking enable 

       	/*(13)Wait PLL lock by N&CTS tracking*/
       	rtd_outl(HDMI_PETR_reg,0x1e);//phase error threshold
     		 for (timeout = 0; timeout < 25; timeout++) {
			rtd_maskl(HDMI_SR_reg,~_BIT3,_BIT3);
			rtd_outl(HDMI_NCPER_reg,0xff);
			HDMI_DELAYMS(20);
			if ((rtd_inl(HDMI_SR_reg) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
		{
			HDMI_PRINTF( "[HDMI] WARNING: PLL not lock = %x\n",rtd_inl(HDMI_NCPER_reg));
		}
		else
		{
			//HDMI_PRINTF( "[HDMI] PLL lock count = %d\n",timeout);
		}

		/*(14)FSM Initial*/
		rtd_outl(HDMI_FBR_reg,0x77);//Target FIFO depth = 14 ,Boundary address distance = 7
		rtd_maskl(HDMI_AVMCR_reg,~_BIT6,_BIT6);//FSM entry Pre-mode (AOC=1)
		rtd_maskl(HDMI_AVMCR_reg,~_BIT5,_BIT5);//FSM entry next step (AOMC=1)
		HDMI_DELAYMS(1);//wait fifo to target fifo level
	}
#if 0
			hdmiport_out(HDMI_HDMI_PTRSV1_VADDR, 0x01);		// Wait for ACR : Packet Type = 0x01
			for (i=0; i<100; i++) {
			hdmiport_out(HDMI_HDMI_NCPER_VADDR,0xff);
			if ((hdmi_in(HDMI_HDMI_SR_VADDR) & (_BIT2|_BIT1))!=0)
				hdmi_mask(HDMI_HDMI_SR_VADDR,~(_BIT2|_BIT1),(_BIT2|_BIT1));
			HdmiGetStruct(&isr_info);
			b = isr_info.b;
			HDMI_DELAYMS(20);

			HDMI_PRINTF( "Sum C  = %x  %x \n",hdmiport_in(HDMI_HDMI_DPCR4_VADDR),hdmiport_in(HDMI_HDMI_DPCR5_VADDR));
			//if ((hdmiport_in(HDMI_HDMI_DPCR4_VADDR)&0xff)!=0x7)
			{
				//cts = Hdmi_PacketSRAMRead(113)<<16;
				//cts = cts|Hdmi_PacketSRAMRead(114)<<8;
				//cts = cts|Hdmi_PacketSRAMRead(115);
				//n = Hdmi_PacketSRAMRead(116)<<16;
				//n = n|Hdmi_PacketSRAMRead(117)<<8;
				//n = n|Hdmi_PacketSRAMRead(118);
				//HDMI_PRINTF( "CTS = %d  N = %d  \n",cts,n);
				HDMI_PRINTF( "FIFO depth  =%x  %x\n",hdmiport_in(HDMI_HDMI_FDDR_VADDR),hdmiport_in(HDMI_HDMI_FDDF_VADDR));
				HDMI_PRINTF( "b=%d Phase err = %x\n",b,hdmiport_in(HDMI_HDMI_NCPER_VADDR));
				HDMI_PRINTF("FIFO Check  = %x\n", hdmi_in(HDMI_HDMI_SR_VADDR));
			}
			}

#endif

	/*(16)Wait FIFO stable*/
	for (timeout = 0; timeout < 5; timeout++) {
		rtd_outl(HDMI_HDMI_NCPER_VADDR,0xff);
		HDMI_DELAYMS(20);
		if ((rtd_inl(HDMI_HDMI_SR_VADDR) & (_BIT3|_BIT2|_BIT1))==0)
			break;
		rtd_maskl(HDMI_HDMI_SR_VADDR,~(_BIT3|_BIT2|_BIT1),(_BIT3|_BIT2|_BIT1));
	}

	if (timeout == 5)
	{
		HDMI_PRINTF("[HDMI] WARNING: FIFO Unstable  = %x \n",rtd_inl(HDMI_SR_reg));
	}
	else
	{
		//HDMI_PRINTF("FIFO timeout count = %d\n",timeout);
	}

	//HDMI_PRINTF("HDMI_HDMI_AVMCR_VADDR = %x\n", rtd_inl(HDMI_AVMCR_reg));

	return TRUE;

}

void Hdmi_AudioOutputDisable(void)
{
	//USER: jacklong DATE: 20100722   K-8256A  changing  hdmi timing ,tv will reboot
	if (HDMI_IS_AUDIO_SPDIF_PATH())
		hdmiport_mask(HDMI_AOCR_reg,(~0x0ff),0x00);	//Disable SPDIF/I2S Output

	hdmiport_mask(HDMI_AVMCR_reg,~(_BIT6 | _BIT5), _BIT6);
	hdmiport_out(HDMI_CMCR_reg,0x50);   //K code =2

	//printf("Audio Disable\n");
	//HDMI_DELAYMS(100);
	//HdmiAudioPLLSampleDump();
}


/**
 * Hdmi_AudioOutputEnable
 * Enable HDMI Audio Ouput
 *
 * @param
 * @return
 * @ingroup drv_hdmi
 */
void Hdmi_AudioOutputEnable(void)
{
	hdmiport_mask(HDMI_HDMI_AVMCR_VADDR,~(_BIT6|_BIT5),(_BIT6|_BIT5));
}


bool Hdmi_CRC_en(void)
{
	UINT8 tmo=50;
	// read CRC value first
	rtd_maskl(TMDS_CRCC_reg,~TMDS_CRCC_crcc_mask,0);	//CRC check disable
	rtd_maskl(TMDS_CRCC_reg,~TMDS_CRCC_crcc_mask,TMDS_CRCC_crcc(1));	//CRC check enable

	while(!(rtd_inl(TMDS_CRCC_reg)&TMDS_CRCC_crc_done_mask))//wait CRC done bit
	{
		udelay(10000);
		if (!tmo--) 
		{
			//HDMI_PRINTF("[HDMI] WARNING: FAIL: Wait CRC Timeout !!!\n");
			return FALSE;
		}
	}
	return TRUE;
}


bool QC_CRCCheck(void)
{
    bool is_interlace;
    UINT32 i = 500, stable_cnt = 0, CRC_READ[3][2];
    UINT32 err_cnt_crc = 0, err_cnt_rgbhv = 0;

#if RGBlane == '3'
    if (!(TMDS_CTRL_get_bcd(rtd_inl(TMDS_CTRL_reg))&&TMDS_CTRL_get_gcd(rtd_inl(TMDS_CTRL_reg))&&TMDS_CTRL_get_rcd(rtd_inl(TMDS_CTRL_reg))))
#elif RGBlane == 'B'
    if (!TMDS_CTRL_get_bcd(rtd_inl(TMDS_CTRL_reg)))
#endif
    {
        HDMI_PRINTF("[HDMI] WARNING: No Input Signal\n");
        return FALSE;
    }

     // Waiting for pattern is in stable status
    if ( !Hdmi_CRC_en() )
    {
        HDMI_PRINTF("[HDMI] WARNING: FAIL: Wait CRC Timeout !!!\n");
        return FALSE;
    }

    CRC_READ[0][0] = 0;
    CRC_READ[0][1] = 0;
    CRC_READ[1][0] = 0;
    CRC_READ[1][1] = 0;
    is_interlace=(rtd_inl(HDMI_VCR_reg) & HDMI_VCR_eot_mask);
    
    do {
        CRC_READ[2][0] = rtd_inl(TMDS_CRCO0_reg);
        CRC_READ[2][1] = rtd_inl(TMDS_CRCO1_reg);
        if ( is_interlace )
        {
            if (( (CRC_READ[0][0]==CRC_READ[2][0])  && (CRC_READ[0][1]==CRC_READ[2][1])  ) ||
            ( (CRC_READ[1][0]==CRC_READ[2][0]) && (CRC_READ[1][1] ==CRC_READ[2][1])  ) )
            {
                if ( stable_cnt++ > 50 )
                {
                    break;
                }
            }
            else
            {
                CRC_READ[0][0] = CRC_READ[1][0];
                CRC_READ[0][1] = CRC_READ[1][1];
                CRC_READ[1][0] = CRC_READ[2][0];
                CRC_READ[1][1] = CRC_READ[2][1];
                stable_cnt = 0;
            }
        }
        else
        {
            if ( (CRC_READ[0][0] == CRC_READ[2][0]) && (CRC_READ[0][1] == CRC_READ[2][1]) && !(rtd_inl(TMDS_CRCC_reg)&TMDS_CRCC_crc_nonstable_mask) )
            {
                if ( stable_cnt++ > 50 )
                {
                    break;
                }
            }
            else
            {
                CRC_READ[0][0] = CRC_READ[2][0];
                CRC_READ[0][1] = CRC_READ[2][1];
                stable_cnt = 0;
                rtd_maskl(TMDS_CRCC_reg,~TMDS_CRCC_crc_nonstable_mask,TMDS_CRCC_crc_nonstable(1));	//CRC unstable clear
                //HDMI_PRINTF("[HDMI] CRC_READ[0]=0x%08x|0x%08x\n", CRC_READ[0][0], CRC_READ[0][1]);
            }
        }
        
        udelay(10000);
    }while( --i );

    if (CRC_READ[0][0]==0x0)
    {
        HDMI_PRINTF("[HDMI] WARNING: CRC=0\n");
        return FALSE;
    }

    rtd_maskl(TMDS_CRCC_reg,~TMDS_CRCC_crc_nonstable_mask,TMDS_CRCC_crc_nonstable(1));	//CRC unstable clear
    udelay(10000);
    i = 0;
    do {
        if ((CRC_COUNT>20) && GETCHAR_x)
        {
            HDMI_PRINTF("\n[HDMI] User abort\n");
            break;
        }

        if ( is_interlace )
        {
            CRC_READ[2][0] = rtd_inl(TMDS_CRCO0_reg);
            CRC_READ[2][1] = rtd_inl(TMDS_CRCO1_reg);
            if (( (CRC_READ[0][0] != CRC_READ[2][0])  || (CRC_READ[0][1] !=CRC_READ[2][1])  ) &&
            ( (CRC_READ[1][0] != CRC_READ[2][0])  || (CRC_READ[1][1] !=CRC_READ[2][1])  ) )
            {
                CRC_READ[0][0] = CRC_READ[1][0];
                CRC_READ[0][1] = CRC_READ[1][1];
                CRC_READ[1][0] = CRC_READ[2][0];
                CRC_READ[1][1] = CRC_READ[2][1];
                err_cnt_crc++;
            }
        }
        else if (rtd_inl(TMDS_CRCC_reg)&TMDS_CRCC_crc_nonstable_mask)
        {
            rtd_maskl(TMDS_CRCC_reg,~TMDS_CRCC_crc_nonstable_mask,TMDS_CRCC_crc_nonstable(1));	//CRC unstable clear
            CRC_READ[0][0] = rtd_inl(TMDS_CRCO0_reg);
            CRC_READ[0][1] = rtd_inl(TMDS_CRCO1_reg);;
            err_cnt_crc++;
        }
#if RGBlane == '3'
        else if ( rtd_inl(TMDS_CTRL_reg) != 0xf8 )	//no r,g,b,h,v?
        {
            err_cnt_rgbhv++;
        }
#endif

        i++;
        printk("[HDMI] CRC=%08X|%08X: Pass=%d, crc failed=%d, no data=%d %s\r", 
                                CRC_READ[0][0], CRC_READ[1][0],
                                (i-err_cnt_crc-err_cnt_rgbhv), err_cnt_crc, err_cnt_rgbhv, (CRC_COUNT>20)?"(press 'x' to quit)":"");

        if ( ERR_BREAK && (err_cnt_crc|err_cnt_rgbhv))
        {
            break;
        }

        udelay(100000);
    }while( i<CRC_COUNT );
    HDMI_PRINTF("\n");

    if ( err_cnt_crc|err_cnt_rgbhv)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}



void drvif_Hdmi_Init_CRT_INIT(void)
{
	//Enable CRT
	rtd_maskl(ST_SRST1_reg,~(RSTN_CBUS_TX|RSTN_CBUS),(RSTN_CBUS_TX|RSTN_CBUS));                //CBUS Tx Rx release reset
	rtd_maskl(ST_CLKEN1_reg,~(CLKEN_CBUS_TX_IP|CLKEN_CBUS_TX|CLKEN_CBUS),(CLKEN_CBUS_TX_IP|CLKEN_CBUS_TX|CLKEN_CBUS));                //CBUS Tx Rx clock enable
	rtd_maskl(SOFT_RESET3_reg,~(RSTN_IFADC|RSTN_APLL_ADC),(RSTN_IFADC|RSTN_APLL_ADC));            //IFADC & APLL ADC release reset
	rtd_maskl(GROUP1_CK_EN_reg,~(CLKEN_APLL_ADC|CLKEN_IFADC),(CLKEN_APLL_ADC|CLKEN_IFADC));               //IFADC & APLL ADC clock enable

	//Enable ADC PLL LDO
	rtd_maskl(PLL_CTRL_reg,~APLLLDOPOW,APLLLDOPOW);            //APLL ADC LDO1v1 enable

	//For HDMI clock detect REG
	rtd_maskl(ST_SRST1_reg,~(RSTN_HDMI_DET),(RSTN_HDMI_DET));                //CBUS Tx Rx release reset
	rtd_maskl(ST_CLKEN1_reg,~(CLKEN_HDMI_DET),(CLKEN_HDMI_DET));                //CBUS Tx Rx clock enable

	//VIP CRT clock 
	rtd_maskl(GROUP1_CK_EN_reg,~(_BIT31|_BIT30|_BIT29|_BIT24|_BIT4|_BIT3),(_BIT31|_BIT30|_BIT29|_BIT24|_BIT4|_BIT3));
	rtd_maskl(SOFT_RESET3_reg,~(RSTN_IFADC|RSTN_DISPIM),(RSTN_IFADC|RSTN_DISPIM));

	// for HDMI
	rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_bgpow_mask,HDMIPHY_REG_BANDGAP_Z0_bgpow(1));		//BG power on (Bit25)
}

void drvif_Hdmi_HPD(char channel_index, char high)
{
	if ( channel_index == 2 )
	{
		rtd_maskl(CBUS_PHY_1_reg, ~CBUS_PHY_1_sel_cbusb_gpio_mask,CBUS_PHY_1_sel_cbusb_gpio(1));
		rtd_maskl(CBUS_PHY_0_reg, ~CBUS_PHY_0_cbus_e_mask,CBUS_PHY_0_cbus_e(1));
		if (high)
			rtd_maskl(CBUS_PHY_0_reg, ~CBUS_PHY_0_cbus_i_mask,CBUS_PHY_0_cbus_i(1));			
		else
			rtd_maskl(CBUS_PHY_0_reg, ~CBUS_PHY_0_cbus_i_mask,CBUS_PHY_0_cbus_i(0));			
	}
	else if ( channel_index==1 )
	{
		rtd_maskl(0xb8060244,~(_BIT31|_BIT30|_BIT29|_BIT28|_BIT27),(_BIT31|_BIT30|_BIT29|_BIT28|_BIT27));	//ST_GPIO19 define GPIO
		rtd_maskl(ISO_GPDIR_reg,~_BIT19,_BIT19);
		if ( high )
			rtd_maskl(ISO_GPDATO_reg,~_BIT19,0);		//Hotplug high
		else
			rtd_maskl(ISO_GPDATO_reg,~_BIT19,_BIT19); 	//Hotplug low
	}
	else
	{
		rtd_maskl(0xb8060240,~(_BIT13|_BIT12|_BIT11|_BIT10|_BIT9),(_BIT13|_BIT12|_BIT11|_BIT10|_BIT9));	//ST_GPIO22 define GPIO
		rtd_maskl(ISO_GPDIR_reg,~_BIT22,_BIT22);
		if (high )
			rtd_maskl(ISO_GPDATO_reg,~_BIT22,0);		//Hotplug high
		else
			rtd_maskl(ISO_GPDATO_reg,~_BIT22,_BIT22); 	//Hotplug low
	}
	
}


void drvif_EDID_DDC_CRT_EN(void) {

	rtd_maskl(CRT_SOFT_RESET2_VADDR,~(_BIT25), (_BIT25)); //reset I2C_2  SYS_SOFT_RESET2_reg
	rtd_maskl(CRT_CLOCK_ENABLE2_VADDR,~(_BIT24),( _BIT24)); //clock en I2C_2
	rtd_maskl(GROUP1_CK_EN_reg,~_BIT6, _BIT6); //need for 0xb801b300

	rtd_maskl(ST_SRST1_reg,~(_BIT13|_BIT14|_BIT15), (_BIT13|_BIT14|_BIT15)); //satndby top 
	rtd_maskl(ST_CLKEN1_reg,~(_BIT13|_BIT14|_BIT15), (_BIT13|_BIT14|_BIT15)); //satndby top 
}

char drvif_EDIDLoad(UINT8 ddc_index, unsigned char* EDID, int len)
{
	int i;
	int Edid_addr;

	drvif_EDID_DDC_CRT_EN();

//	if (ddc_index >= DDC_NOTUSED) return FALSE;
//	if (EDIDIsValid(EDID) == FALSE) return FALSE;

	Edid_addr =  DDC1_I2C_CR_reg + 0x100 *(ddc_index+1) ;

	//Disable DDC func, write EDID data to sram
	rtd_maskl(Edid_addr + REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en(0));
	for(i=0; i< len; i++) //total 0 ~ 127
	{
			rtd_outl(Edid_addr+REG_DDC_SIR_OFFSET, i);
			rtd_outl(Edid_addr+REG_DDC_SAP_OFFSET, EDID[i]);
//			udelay(10); //only for QC code
	}
	rtd_outl(Edid_addr, 0x30);

	//Enable DDC func
	rtd_maskl(Edid_addr + REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en(1));

	return TRUE;

}

char drvif_EDIDEnable(UINT8 ddc_index, char enable)
{
	int Edid_addr;

	//	if (ddc_index >= DDC_NOTUSED) return FALSE;

	Edid_addr =  DDC1_I2C_CR_reg + 0x100 *(ddc_index+1) ;
	rtd_maskl(Edid_addr+REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en((enable)?1:0));

	return TRUE;
}


void drvif_EDID_DDC12_AUTO_Enable(UINT8 ddc_index,char enable)
{
	int Edid_addr;

//	if (ddc_index >= DDC_NOTUSED) return;
	Edid_addr =  DDC1_I2C_CR_reg + 0x100 *(ddc_index+1) ;
	rtd_maskl(Edid_addr +REG_EDID_CTL_OFFSET, ~(DDC1_EDID_CR_ddc1_force_mask | DDC1_EDID_CR_ddc2b_force_mask),
				(DDC1_EDID_CR_ddc1_force(0) | DDC1_EDID_CR_ddc2b_force((enable)?0:1)));

}

void drvif_Hdmi_EnableEDID(char channel_index, char enable)
{
	drvif_EDIDEnable(channel_index, enable);				
	drvif_EDID_DDC12_AUTO_Enable(channel_index, 0);
}

void drvif_Hdmi_LoadEDID(char channel_index, unsigned char *EDID, int len)
{
	drvif_EDIDLoad(channel_index, EDID, len);
	drvif_EDIDEnable(channel_index, 1);
	drvif_EDID_DDC12_AUTO_Enable(channel_index, 0);
}

void drvif_CBUS_EDID_DDC12_AUTO_Enable(UINT8 enable) 
{
	UINT32 Edid_addr;
	
	Edid_addr = DDC5_CBUS_DDC_reg ;
	//enable = (enable)?0:1;
	//Enable DDC func
	rtd_maskl(Edid_addr +REG_EDID_CTL_OFFSET, ~(DDC1_EDID_CR_ddc1_force_mask | DDC1_EDID_CR_ddc2b_force_mask),
				(DDC1_EDID_CR_ddc1_force(0) | DDC1_EDID_CR_ddc2b_force((enable)?0:1)));

}

/***************************************************************************************/
//Function :  char drvif_CBUSEDIDLoad(DDC_NUMBER_T ddc_index, unsigned char* EDID, int len)
//Description: LOAD EDID to on chip SRAM
//Parameter:  DDC 1 -  HDMI1     DDC2 - HDMI2       DDC3 - HDMI3
//return: no need return
/**************************************************************************************/
bool drvif_CBUS_EDIDEnable(UINT8 enable) 
{
	UINT32 Edid_addr;

	Edid_addr = DDC5_CBUS_DDC_reg ;
	//enable = (enable)?1:0;
	//Enable/disable DDC func
	rtd_maskl(Edid_addr+REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en((enable)?1:0));
	return TRUE;
}

/***************************************************************************************/
//Function :  char drvif_CBUSEDIDLoad(DDC_NUMBER_T ddc_index, unsigned char* EDID, int len)
//Description: LOAD EDID to on chip SRAM
//Parameter:  DDC 1 -  HDMI1     DDC2 - HDMI2       DDC3 - HDMI3
//return: no need return
/**************************************************************************************/
bool drvif_CBUS_EDIDLoad( unsigned char* EDID, UINT16 len) 
{
	UINT32 Edid_addr;
	UINT16 i;	

	Edid_addr = DDC5_CBUS_DDC_reg ;
	//Disable DDC func, write EDID data to sram
	rtd_maskl(Edid_addr + REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en(0));

	for(i=0; i< len; i++) //total 0 ~ 127
		rtd_outl(Edid_addr+REG_DDC_SIR_OFFSET, i),
		rtd_outl(Edid_addr+REG_DDC_SAP_OFFSET, EDID[i]);	
		//HDMI_PRINTF("drvif_CBUS_EDIDLoad index = %d , value = %d  \n", i,EDID[i]);
	rtd_outl(Edid_addr, 0x30);
	//Enable DDC func
	rtd_maskl(Edid_addr + REG_EDID_CTL_OFFSET, ~DDC1_EDID_CR_edid_en_mask, DDC1_EDID_CR_edid_en(1));
	return TRUE;
}

void drvif_CBUS_LoadEDID( unsigned char *EDID, int len) 
{
	rtd_maskl(HDCP_PCR_reg, ~HDCP_PCR_km_clk_sel_mask, 0);
	drvif_CBUS_EDIDLoad(EDID,len);
	drvif_CBUS_EDIDEnable(1);
	drvif_CBUS_EDID_DDC12_AUTO_Enable(0);
}
void inline Hdmi_HdcpPortCWrite(unsigned char addr ,HDMI_CONST unsigned char* value ,unsigned char num )
{
	hdmi_mask(HDMI_HDCP_PCR_VADDR, ~_BIT0, 0);
	hdmi_out(HDMI_HDCP_AP_VADDR, addr);

	while(num--)
		hdmi_out(HDMI_HDCP_DP_VADDR, *(value++));

	hdmi_mask(HDMI_HDCP_PCR_VADDR, ~_BIT0, _BIT0);
}

void inline Hdmi_HdcpPortWrite(unsigned char addr ,unsigned char value)
{
	hdmi_out(HDMI_HDCP_AP_VADDR, addr);
	hdmi_out(HDMI_HDCP_DP_VADDR, value);
}

unsigned char  Hdmi_HdcpPortRead(unsigned char addr)
{
	hdmi_out(HDMI_HDCP_AP_VADDR, addr);
	return hdmi_in(HDMI_HDCP_DP_VADDR);
}

void Hdmi_HdcpInit(void)
{
	int i;
		
	// Disable HDCP and clear HDCP address
	hdmi_out(HDMI_HDCP_CR_VADDR,0x06);
	hdmi_mask(HDCP_PCR_reg ,~(HDCP_PCR_km_clk_sel_mask|HDCP_PCR_enc_tog_mask),0);

	// write BKsv into DDC channel
	//HDMI_PRINTF("[HDMI] HDCP BKSV = ");
	//for(i=0;i<5;i++) {
	//	HDMI_PRINTF("%x ", HDCP_BKSV[i]);
	//}
	//HDMI_PRINTF("\n");

	Hdmi_HdcpPortCWrite(0x00 , HDCP_BKSV, 5 );	//set KSV 40 bits
	#if defined (ENABLE_HDMI_1_1_SUPPORT)
	Hdmi_HdcpPortWrite(0x40,HDCP_11_HDMI);				//set OESS for DVI
	#else
	Hdmi_HdcpPortWrite(0x40,HDCP_10_DVI);				//set OESS for DVI
	#endif

	/*Write device private key*/
	for(i=0;i<320;i++) {
		hdmi_out(HDMI_HDCP_DKAP_VADDR, HDCP_KEY_TABLE[i]);
		//udelay(1); //only for QC code
	}

	hdmi_out(HDMI_HDCP_CR_VADDR,0x00);

	// enable HDCP function for all
	hdmi_mask(HDMI_HDCP_CR_VADDR,~(_BIT7|_BIT0),(_BIT7|_BIT0));//for New_AC_Mode Enable,fix simplay bug

#if defined(CONFIG_HDCP_KEY_PRINT)
	hdmi_out(HDMI_HDCP_CR_VADDR,0x06);
	HDMI_PRINTF("\nHDMI BKSV Flag = %x, %x ,%x ,%x, %x \n",
		Hdmi_HdcpPortRead(0x00), 
		Hdmi_HdcpPortRead(0x01), 
		Hdmi_HdcpPortRead(0x02), 
		Hdmi_HdcpPortRead(0x03), 
		Hdmi_HdcpPortRead(0x04));
	HDMI_PRINTF("HDCP key 320 byte read=\n");
	for(i=0;i<320;i++) {
		if (i% 16 == 0) HDMI_PRINTF("\n");
		HDMI_PRINTF("%x ", hdmi_in(HDMI_HDCP_DKAP_VADDR));
	}
	hdmi_out(HDMI_HDCP_CR_VADDR,0x00);
	hdmi_mask(HDMI_HDCP_CR_VADDR,~(_BIT7|_BIT0),(_BIT7|_BIT0));
#endif //#ifdef CONFIG_HDCP_KEY_PRINT

	Hdmi_HdcpPortWrite(0xc4,0x00); // keep old setting

}



#include <platform_lib/board/lsadc.h>
#define ST_CFG_4_reg				0xb8060210

int adc_init(int index, int voltage_mode)
{
	st_lsadc_ctrl_RBUS st_lsadc_ctrl_reg;
	st_pad0_RBUS st_pad0_reg;

	if (index >= 8) {
		return -1;
	}

	rtd_maskl(CRT_ST_CLKEN0_VADDR, ~0x00000005, 0x00000005);
	rtd_maskl(CRT_ST_CLKEN1_VADDR, ~0x00000001, 0x00000001);
	rtd_maskl(CRT_ST_SRST0_VADDR, ~0x00000005, 0x00000005);
	rtd_maskl(CRT_ST_SRST1_VADDR, ~0x00000001, 0x00000001);
	rtd_maskl(ST_CFG_4_reg, ~0x60000000, 0x60000000);

	rtd_outl(ST_LSADC_ANALOG_CTRL_reg, 0x00010101);

	udelay(1000);
	st_lsadc_ctrl_reg.regValue = rtd_inl(ST_LSADC_CTRL_reg);
	if (st_lsadc_ctrl_reg.enable != 0) {
		st_lsadc_ctrl_reg.enable = 0;
		rtd_outl(ST_LSADC_CTRL_reg, st_lsadc_ctrl_reg.regValue);
	}

	st_pad0_reg.regValue = 0;
	st_pad0_reg.pad0_active = 1;
	st_pad0_reg.pad0_sw = index;

	if (voltage_mode) {	// if voltage mode
		st_pad0_reg.pad0_ctrl = 0;
	}
	else {
		st_pad0_reg.pad0_ctrl = 1;
	}
	
	rtd_outl(ST_PAD0_reg + index * 4, st_pad0_reg.regValue);
	
	return 0;
}


int adc_get(int index)
{
	st_lsadc_ctrl_RBUS st_lsadc_ctrl_reg;
	st_pad0_RBUS st_pad0_reg;

	if (index >= 8) {
		return -1;
	}

	st_lsadc_ctrl_reg.regValue = rtd_inl(ST_LSADC_CTRL_reg);
	if (st_lsadc_ctrl_reg.enable == 0) {
		st_lsadc_ctrl_reg.enable = 1;
		rtd_outl(ST_LSADC_CTRL_reg, st_lsadc_ctrl_reg.regValue);
	}
	//add by keven_yuan begin
	udelay(1000);
	//add by keven_yuan end
	st_pad0_reg.regValue = rtd_inl(ST_PAD0_reg + index * 4);

	return st_pad0_reg.adc_val0;
}

