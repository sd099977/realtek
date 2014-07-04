#ifndef SYSAPI_H
#define SYSAPI_H
//?#include <stdio.h>




/**********/
/* typedef */
/**********/
//typedef unsigned char flag;


/**********/
/* enum */
/**********/
//ALL_TCONÍÑ
/*
typedef enum {
	FALSE,
	TRUE
} BOOL;
*/

/**********/
/* Address */
/**********/
#define IIC_SLV_ADDR_TCON			0xE8

/***************Plaice*******************/
/*frdlcdplapi.h*/
/*frdplapi.h*/
/*****************************************/

/***************Arugula******************/
#define ADV_LCDC_ADDR_CTL			0x0000
#define ADV_LCDC_ADDR_CGN			0x0080
#define ADV_LCDC_ADDR_LCDC_SBR		0x1000
#define ADV_LCDC_ADDR_PPDS			0x2000
#define ADV_LCDC_ADDR_QS_LUT		0x2600
#define ADV_LCDC_ADDR_TIMING_GEN	0x2A00
#define ADV_LCDC_ADDR_DATA_PATH		0x2C00
#define ADV_LCDC_ADDR_DAC			0x2C80
#define ADV_LCDC_ADDR_ETC			0x2CC0
#define ADV_LCDC_ADDR_SBR_PARAM		0x3000
#define ADV_LCDC_ADDR_PNL			0x0300
#define ADV_LCDC_ADDR_LCDC			0x4000
#define ADV_LCDC_ADDR_FRC			0x8000
/*****************************************/

#endif /* SYSAPI_H */
