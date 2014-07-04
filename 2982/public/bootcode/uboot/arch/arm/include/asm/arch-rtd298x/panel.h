/************************************************************************
 *
 *  panel.h
 *
 ************************************************************************/

#ifndef PANEL_API_H
#define PANEL_API_H

#define S_OK	0
#define S_FALSE -1
/************************************************************************
 *  Include files
 ************************************************************************/


/************************************************************************
 *  Public functions
 ************************************************************************/

void panel_init_1st(void);
void panel_init_2nd(void);
int panel_init(void);
//void disable_force_bg(void);
void panel_interface_common(void);


void PA168_i2c_cmd(void);
#if 0
typedef enum {
	P_LVDS_2K1K,	//VDS output 2k1k timing only
	P_VBY1_4K2K,	//V By 1	 output 4k2k timing only
	P_LVDS_4K_2K,	//LVDS output 4k2k and 2k1k timing
	P_EPI_TYPE,
	P_LVDS_TO_HDMI,
	P_DISP_TO_TVOX,
	P_RESERVED
}PANEL_TYPE;

typedef enum {
	VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1,
	VBY_ONE_PANEL_CMI_V500_4K2K_VBY1,
	VBY_ONE_PANEL_CMI_60_4K2K_VBY1,
	VBY_ONE_PANEL_RESERVED
}VBY_ONE_PANEL_TYPE; //VBY1 PANEL_CUSTOM_INDEX;

typedef enum {
	P_NO_DEFINED = 0,
	P_M3_CMI_55 = 1,		// Millet3 + CMI 55" 4k2k panel
	P_M3_CMI_55_P1032 = 3,	// Millet3 + TV010 CMI 55" 4k2k panel
	P_SKY_RDL420FY_ADF,
	P_SKY_SDL470FY_LDF,
	P_SKY_SDL550FY_LDF,
	P_SKY_V420DK1_LS1,
	P_SKY_V500DK2_LS1,
	P_MILLET_SERIES_PANEL_MAX = 0x50,
	P_PA168_AU_55,		// PA168 + AU 55" 4k2k panel
}LVDS_4K2K_PANEL_INDEX; //LVDS 4K2K PANEL_CUSTOM_INDEX;
#else

typedef enum {
	P_LVDS_2K1K,				//VDS output 2k1k timing only
	P_VBY1_4K2K,				//V By 1	 output 4k2k timing only
	P_LVDS_4K_2K_BOOTCODE_2K,	//LVDS output 4k2k and 2k1k timing, bootcode use 2k1k120
	P_LVDS_4K_2K_BOOTCODE_4K,	//LVDS output 4k2k and 2k1k timing, bootcode use 4k2k30
	P_EPI_TYPE,
	P_LVDS_TO_HDMI,
	P_DISP_TO_TVOX,	
	P_MINI_LVDS,
	P_RESERVED
}PANEL_TYPE;

typedef enum {
		
	/* 4k2k30 / 2k1k120 dynamic output timing series*/	
	DYNAMIC_OUTPUT_PANEL_SERIES_BEGIN=0x20,
	P_M3_CMI_55,		// Millet3 + CMI 55" 4k2k panel
	P_M3_CMI_55_P1032,	// Millet3 + Skyworth CMI 55" 4k2k panel
	P_SKY_V420DK1_LS1,
	P_SKY_V500DK2_LS1,
	VBY_ONE_PANEL_INX8903_4K2K_VBY1,
	VBY_ONE_PANEL_INX8901_4K2K_VBY1,		// Millet4
	VBY_ONE_PANEL_INX8922_4K2K_VBY1,	
	P_M4_Default_4k2k,
	P_M4_Default_2k1k,	
	P_PA168_AU_55,
	DYNAMIC_OUTPUT_PANEL_SERIES_MAX=0x60,

	P_EPI_LG_47_ART5,

}PANEL_CUSTOM_INDEX;	//PANEL_CUSTOM_INDEX;

typedef enum {
	_3D_TIMING_2K1K_60,
	_3D_TIMING_2K05K120,
	_3D_TIMING_2K05K240,
	_3D_TIMING_2K1K_120,
	_3D_TIMING_2K1K_240,
	_3D_TIMING_4K1K_120,
	_3D_TIMING_4K05K_240,
	_3D_TIMING_4K1K_240,
	_3D_TIMING_4K2K_120,
}PANEL_3D_TIMING_INDEX;	//PANEL_CUSTOM_INDEX;


#endif // __PANEL_API_H__

typedef enum {
	P_LVDS_2K1K_NO_DEFINED =0,
	P_IWATT7018_LG_42_SFK1=4,
	P_IWATT7018_LG_47_SFK1 =5
}LVDS_2K1K_PANEL_INDEX; //LVDS 2K1K PANEL_CUSTOM_INDEX;


/************************************************************************
 *  Private functions
 ************************************************************************/

#endif /* #ifndef PANEL_API_H */
