
#if 1
#define _ZERO   						0x00
#define _BIT0   						0x01
#define _BIT1   						0x02
#define _BIT2   						0x04
#define _BIT3   						0x08
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

#define rtdf_setBits(offset, Mask) 			rtd_outl(offset, (rtd_inl(offset) |Mask))
#define rtdf_clearBits(offset, Mask) 		rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#define rtdf_inl(Address)					(*(volatile UINT32 *) (Address))		//Read 32-bit Data from Specific Memory Address
#define rtdf_outl(Address, Data)				(*(volatile UINT32 *) (Address) = Data)	//Write 32-bit Data to Specific Memory Address
#define rtdf_maskl(Address, AndMask, OrMask)	rtd_outl(Address, ((rtd_inl(Address) & (AndMask)) | (OrMask)))

#ifndef BOOL
#define BOOL 					bool
#endif



#define _SUCCESS					0
#define _FAIL   						1
#define _HSLCK      _BIT1
#define _VLINF      _BIT2
//Signal
typedef enum {
	VIDEO_INPUT0 = 0,
	VIDEO_INPUT1,
	VIDEO_INPUT2,
	VIDEO_INPUT3,
	VIDEO_INPUT4,
	VIDEO_INPUT5,
	VIDEO_INPUT6,
	VIDEO_INPUT7,
	VIDEO_INPUT8,
	VIDEO_INPUT9,
	VIDEO_INPUT10,
	VIDEO_INPUT11,
	VIDEO_INPUT12,
	VIDEO_INPUT13,
	VIDEO_INPUT14,
	TV_INPUT,
} VIDEO_PATH;

typedef enum {
   VIDEO_GNDA0 = 0,
   VIDEO_GNDA1,
   VIDEO_GNDA2,
   VIDEO_GNDR,
   VIDEO_GNDG,
   VIDEO_GNDB,
   VIDEO_GNDY0,
   VIDEO_GNDY1,
}VIDEO_GND_PATH;

typedef enum {
   VIDEO_SV_NORMAL,
   VIDEO_SV_SWAP,
}VIDEO_SV_FUNC;

typedef enum {
_NTSC = 0,
_PALM,
_NTSC50,
_PALN,
_NTSC443,
_PAL60,
_PALI,
_SECAM,
}VIDEO_MODE;

//av out 
#define	VDC_AVOUT_CVBS_NO_FIL_NO_AGC     0 
#define	VDC_AVOUT_CVBS_WITH_FIL_NO_AGC  1
#define	VDC_AVOUT_CVBS_WITH_FIL_WITH_AGC 2
#define	VDC_AVOUT_YC_WITH_FIL_NO_AGC  3
#define	VDC_AVOUT_YC_WITH_FIL_WITH_AGC 4
#define	VDC_AVOUT_IFD_DATA 5
#define	VDC_AVOUT_BYPASS_VIN0P 6
#define	VDC_AVOUT_BYPASS_VIN1P 7 
#define	VDC_AVOUT_BYPASS_VIN2P 8
#define	VDC_AVOUT_BYPASS_VIN3P 9
#define	VDC_AVOUT_BYPASS_VIN4P 0xa
#define	VDC_AVOUT_BYPASS_VIN5P 0xb
#define	VDC_AVOUT_BYPASS_VIN6P 0xc
#define	VDC_AVOUT_BYPASS_VIN7P 0xd
#define	VDC_AVOUT_BYPASS_VIN8P 0xe
#define	VDC_AVOUT_BYPASS_VIN9P 0xf
#define	VDC_AVOUT_NO_USE 0x10

#define	Swap_C_Path 1

#define	AVOUT1 0
#define	AVOUT2 1

#define	by_pass_enable  1
#define	by_pass_disable  0

//#define _3D_One_Frame_Use   0x1B11B 
#define	vd_show_message	1

/*==================== Variables ================== */
#if 0
#define	AD_BorPb		0
#define	AD_G			1
#define	AD_CorRorPr	2
#define	AD_YorCVBS		3
#endif

#if 1
#define	AD_YorCVBS		0
#define	AD_BorPb		1
#define	AD_CorRorPr	2
#define	AD_G			3
#endif

//extern  UINT8 drvif_module_vdc_CheckHVisLocked(void);
//extern void drvif_module_vdc_Initial(void);
//extern void module_vdc_SetInput_Y(UINT8 Y_path, UINT8 Y_Gnd_path);
extern void vdc_open_vin7p_for_ifd_loopback_test(void);

//extern void drvif_module_vdc_for_ypbpr_test_OLT(UINT8 ON_OFF);

