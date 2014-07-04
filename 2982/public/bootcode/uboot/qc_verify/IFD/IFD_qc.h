#ifndef _IFD_QC_H
#define _IFD_QC_H

#define IFD_QC_FUNC() 							IFD_QC_MSG("%s\n", __FUNCTION__);
#define IFD_QC_MSG(string,args...) 				//printk("[IFD][QC][DEBUG]");printk(string, ##args);
#define IFD_QC_MSG_INFO(string,args...) 			printk("[IFD][QC][INFO]");printk(string, ##args);
#define IFD_QC_MSG_WARNING(string,args...) 		printk("[IFD][QC][WARNING]");printk(string, ##args);
#define ScalerTimer_DelayXms(ms) 				drv_ifd_delay_ms(ms)

//------------------------------------------
// Definitions of Bits
//------------------------------------------

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
#define _BIT16						0x10000
#define _BIT17						0x20000
#define _BIT18	 					0x40000
#define _BIT19						0x80000
#define _BIT20						0x100000
#define _BIT21						0x200000
#define _BIT22        					0x400000
#define _BIT23        					0x800000
#define _BIT24        					0x1000000
#define _BIT25						0x2000000
#define _BIT26						0x4000000
#define _BIT27						0x8000000
#define _BIT28						0x10000000
#define _BIT29						0x20000000
#define _BIT30						0x40000000
#define _BIT31						0x80000000


/********************************************/
//Config Definition
/********************************************/
//Normal IF tuner
//#define CONFIG_TUNER_RF_TYPE
//#define CONFIG_TUNER_XUGUANG_HFT3_86H_115CW
//Low IF tuner
#define CONFIG_TUNER_LOWIF_TYPE
#define CONFIG_TUNER_NXP_TDA18273

#define Test_IFD_QC_CRC_Verify
#define Test_IFD_QC_TunerIfdFreq_Verify
#define Test_IFD_QC_Gain_Verify
#define Test_IFD_QC_AudioPerFoms_Verify
#undef Test_IFD_QC_AVOUT_Verify //DAC verify at BOX
#undef CONFIG_OLT

#define _FAIL				       1
#define _SUCCESS  			       0
#define _TRUE                                  1
#define _FALSE					0

typedef struct {
	UINT16	kpi_shift;
	UINT16	kp;
	UINT16	ki;
} StructAGCPara;

#define rtdf_setBits(offset, Mask) 				rtd_outl(offset, (rtd_inl(offset) |Mask))
#define rtdf_clearBits(offset, Mask) 			rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#define rtdf_inl(Address)						(*(volatile UINT32 *) (Address))		//Read 32-bit Data from Specific Memory Address
#define rtdf_outl(Address, Data)				(*(volatile UINT32 *) (Address) = Data)	//Write 32-bit Data to Specific Memory Address
#define rtdf_maskl(Address, AndMask, OrMask)	rtd_outl(Address, ((rtd_inl(Address) & (AndMask)) | (OrMask)))

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

//VD
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

#define	AD_YorCVBS		0
#define	AD_BorPb		1
#define	AD_CorRorPr	2
#define	AD_G			3
//end of VD

#define GET_IFD_AGCLOOP1_MAXTARGET_NTSC() 0x2b0

#endif //_IFD_QC_H

