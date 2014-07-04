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

void PA168_i2c_cmd(void);
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

typedef enum {
	P_LVDS_2K1K_NO_DEFINED =0,
	P_IWATT7018_LG_42_SFK1=4,
	P_IWATT7018_LG_47_SFK1 =5
}LVDS_2K1K_PANEL_INDEX; //LVDS 2K1K PANEL_CUSTOM_INDEX;


/************************************************************************
 *  Private functions
 ************************************************************************/

#endif /* #ifndef PANEL_API_H */
