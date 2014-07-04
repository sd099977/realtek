
//?#include <stdio.h>


#define    	U8x          unsigned char
#define    	U16x        unsigned short
#define    	U32x        unsigned long
#define 		BYTEx 	unsigned char
#define	       FALSEx           0

#define DEBUG_ON	//UARTの通信を止める

extern dResult_e eI2CWrite(unsigned short usSlaveAddr, unsigned short usRegIdx, unsigned short usDatas );
extern dResult_e eI2CRead(unsigned short usSlaveAddr, unsigned short usRegIdx, unsigned short* pusDatas );
extern void MDrv_Timer_Delayms( int iTimes );

#if 0
typedef enum {
	FALSE,
	TRUE
} BOOL;
#else					//20111005
typedef enum {			//20111005
	SH_FALSE,			//20111005
	SH_TRUE				//20111005
} SH_BOOL;				//20111005
#define FALSE SH_FALSE	//20111005
#define TRUE SH_TRUE	//20111005
#endif					//20111005

typedef struct
{
	int		(*I2C_WRITE)(U16x, U8x, U8x *, U16x, U8x *);
	/* U16x u16BusNumSlaveID, U8x AddrCnt, U8x* pu8addr, U16x u16size, U8x* pBuf */
	int		(*I2C_READ)(U16x, U8x, U8x *, U16x, U8x *);
	/* U16x u16BusNumSlaveID, U8x ucSubAdr, U8x* paddr, U16x ucBufLen, U8x* pBuf */
	int		(*MS_WAIT)(int);
	/* int iTime(ms) */
} DriverRegistFunctions;

// extern
//dI2cFunctionInformation dI2CSharp;

