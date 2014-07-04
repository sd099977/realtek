//#ifndef _TVE_INCLUDED_
//#define _TVE_INCLUDED_

extern unsigned int *mv_flag1;
extern unsigned int *RGB_flag1;
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
#define ScalerTimer_DelayXms(mSec)		udelay(mSec)
#define rtdf_setBits(offset, Mask) 			rtd_outl(offset, (rtd_inl(offset) |Mask))
#define rtdf_clearBits(offset, Mask) 		rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#define rtdf_inl(Address)					(*(volatile UINT32 *) (Address))		//Read 32-bit Data from Specific Memory Address
#define rtdf_outl(Address, Data)				(*(volatile UINT32 *) (Address) = Data)	//Write 32-bit Data to Specific Memory Address
#define rtdf_maskl(Address, AndMask, OrMask)	rtd_outl(Address, ((rtd_inl(Address) & (AndMask)) | (OrMask)))


//#endif

