#include <common.h>

#ifndef __PANEL_CONFIG_PARAM_H__
#define __PANEL_CONFIG_PARAM_H__

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

typedef struct _PANEL_CONFIG_PARAMETER{

	UINT8 iCONFIG_DISPLAY_PORT:2;				//0: single port, 1: double port, 2:4 port
	UINT8 iCONFIG_DISPLAY_COLOR_BITS:2;			//0: 30bits, 1:24 bits, 2: 18bits
	UINT8 iCONFIG_DISPLAY_EVEN_RSV1_BIT:1;		//0: Indicate 0, 1: Indicate 1
	UINT8 iCONFIG_DISPLAY_ODD_RSV1_BIT:1;		//0: Indicate 0, 1: Indicate 1
	UINT8 iCONFIG_DISPLAY_BITMAPPING_TABLE:1;	//0: Table1, 1:Table2
	UINT8 iCONFIG_DISPLAY_PORTAB_SWAP:1;		//0: No Swap, 1: Swap , 4 port lvds has 24 type mapping tables
	//1 byte

	UINT8 iCONFIG_DISPLAY_RED_BLUE_SWAP:1;		//0: No Swap, 1: Swap
	UINT8 iCONFIG_DISPLAY_MSB_LSB_SWAP:1;		//0: No Swap, 1: Swap
	UINT8 iCONFIG_DISPLAY_SKEW_DATA_OUTPUT:1;	//0: Disable, 1: Skew data output
	UINT8 iCONFIG_DISPLAY_OUTPUT_INVERSE:1;		//0: No Swap, 1: Swap
	UINT8 iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL:1;
	UINT8 iCONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL:1;
	UINT8 iCONFIG_DISPLAY_RATIO_4X3:2;
	//2 bytes

	UINT16 iCONFIG_DISPLAY_CLOCK_MAX;		//119
	UINT16 iCONFIG_DISPLAY_CLOCK_MIN;
	UINT8 iCONFIG_DISPLAY_REFRESH_RATE;			//75
	UINT32 iCONFIG_DISPLAY_CLOCK_TYPICAL;		//70*1000000 // hsliao 20081008
        //11 bytes

	UINT16 iCONFIG_DISP_HORIZONTAL_TOTAL;		//(1688 -1)
	UINT16 iCONFIG_DISP_VERTICAL_TOTAL;			//(1066 - 1)
        //15 bytes

	UINT8 iCONFIG_DISP_HSYNC_WIDTH;				//(32 - 1)
	UINT8 iCONFIG_DISP_VSYNC_LENGTH;			//(6 - 1)
        //17 bytes

	UINT16 iCONFIG_DISP_DEN_STA_HPOS;			//200//201//32
	UINT16 iCONFIG_DISP_DEN_END_HPOS;// 				1480//1482//1312
	UINT16 iCONFIG_DISP_DEN_STA_VPOS;// 				16//frank@1118 Change 5bits to 16 bits to solve overflow problem
	UINT16 iCONFIG_DISP_DEN_END_VPOS;// 				1040
        //25 bytes

	UINT16 iCONFIG_DISP_ACT_STA_HPOS:3;// 				0
	UINT16 iCONFIG_DISP_ACT_END_HPOS:13;// 				1280
	UINT16 iCONFIG_DISP_ACT_STA_VPOS:3;// 				0
	UINT16 iCONFIG_DISP_ACT_END_VPOS:13;// 				1024
        //33 bytes

	UINT16 iCONFIG_DISP_HSYNC_LASTLINE;// 				(1688 - 1)
	UINT8 iCONFIG_DISP_DCLK_DELAY;// 					0
	UINT8 _iCONFIG_DISP_ACT_STA_BIOS;// 				0x00
	UINT8 iCONFIG_DEFAULT_DPLL_M_DIVIDER;//			0x68 //hpwang 20071119 set default DCLK=(27*104/8)/2/2=87.75MHz
	UINT8 iCONFIG_DEFAULT_DPLL_N_DIVIDER;//			0x18
        //39 bytes

	UINT16 iPANEL_TO_LVDS_ON_ms;//						50 // Delay(T1+T2): Panel Power --> LVDS Signal
	UINT16 iLVDS_TO_LIGHT_ON_ms;//						200 // Delay(T3):    Settings: LVDS Signal --> Backlight On

	UINT16 iLIGHT_TO_LDVS_OFF_ms;//					200 // Delay(T4):    Turn Off backlight and delay to turn off LVDS signal
	UINT16 iLVDS_TO_PANEL_OFF_ms;//					40 // Delay(T5+T6): LVDS Signal Off --> Panel Power Off
        //47 bytes

	UINT16 iPANEL_OFF_TO_ON_ms;//						1000 // Delay(T7):    Totally Off --> Next On
	UINT16 iCONFIG_BACKLIGHT_PWM_FREQ;//				10000
	UINT8 iCONFIG_BACKLIGHT_PWM_DUTY;//				10
	UINT8 iFIX_LAST_LINE_ENABLE;//				0
	UINT8 iFIX_LAST_LINE_4X_ENABLE;//				0
	UINT8 iVFLIP;//									0
        //55 bytes

	UINT8 iPICASSO_CONTROL_ON;
	UINT8 i3D_DISPLAY_SUPPORT;
	UINT8 i3D_LINE_ALTERNATIVE_SUPPORT;
	UINT8 i3D_PR_OUTPUT_LR_SWAP;
	UINT8 i3D_SG_OUTPUT_120HZ_ON;
	UINT8 i3D_SG_24HZ_OUTPUT_FHD_ON;
	UINT8 iSCALER_2D_3D_CVT_HWSHIFT_ENABLE;
        //62 bytes

	//append new parameters 2012-3-21
	UINT16 iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN;
	UINT16 iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX;
	UINT16 iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN;
	UINT16 iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX;
        //70 bytes

	UINT8 iCONFIG_LVDS_4_PORTS_INDEX;
	UINT8 iCONFIG_LVDS_PN_SWAP;
	UINT8 iCONFIG_LVDS_MIRROR;
        //73 bytes

	UINT32 iCONFIG_DISPLAY_PORT_CONFIG1;
	UINT32 iCONFIG_DISPLAY_PORT_CONFIG2;
	UINT8 iCONFIG_SR_MODE;
	UINT8 iCONFIG_SR_PIXEL_MODE;
	UINT8 iCONFIG_SFG_SEG_NUM;
	UINT8 iCONFIG_SFG_PORT_NUM;
	UINT8 iCONFIG_PANEL_TYPE;	// (0:LVDS 2k1k only), (1: VBY_ONE 4k2K), (2: LVDS 4k2k+2k1k (NEED define CUSTOM INDEX))
	UINT8 iCONFIG_PANEL_CUSTOM_INDEX; // 0: none, 1: M3_CMI_55, 2: PA168_AU55,
        //87 bytes

	UINT8 i3D_DISPLAY_TIMING;
	// 88 byte
	
        UINT8 iCONFIG_CUSTOMER_PANEL_ID;

	//Reserve for new parameters
	UINT16 iCONFIG_DISP_RESVER05;
	UINT32 iCONFIG_DISP_RESVER06; //sizeof is 100byte now. don't add more item
        //95 bytes

	//96 bytes
	char sPanelName[32];
} __attribute__((aligned(4))) PANEL_CONFIG_PARAMETER;

extern struct _PANEL_CONFIG_PARAMETER  default_panel_parameter;

#endif//#ifndef __PANEL_CONFIG_PARAM_H__

