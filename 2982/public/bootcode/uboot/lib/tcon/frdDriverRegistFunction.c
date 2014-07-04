
//@@@@@@@@@@@@@@@@@@@@@@@@
#define TURNKEY1 1
#define printf(...)
#include <common.h>
//@@@@@@@@@@@@@@@@@@@@@@@@

//#include "A.h"
//?#include <stdio.h>
#define DEBUG_ON
//#include "frdDriverRegistFunction.h"	/* Open to Other Company */
#include <tcon/frdapi.h>
#include <tcon/Internal_RegistrationFunction.h>

#define SaveAddr_Sharp		0x9E  //0xA4
#define HIBYTE(value)  ((unsigned char)((value) / 0x100))
#define LOBYTE(value)  ((unsigned char)(value))

/* I2C Function structure */
static DriverRegistFunctions dDriverRegistFunctions;

/* Define I2C structure */
int ifrdSetDriver( int (*I2C_READ)(U16x, U8x, U8x *, U16x, U8x *),
					int (*I2C_WRITE)(U16x, U8x, U8x *, U16x, U8x *),
					int (*MS_WAIT)(int) )
{
	printf("Sharp:tcon:ifrdSetDriver\r\n");
	int iReason = 0;
	
	if(I2C_WRITE == NULL)
	{
		printf("I2CWrite == NULL\n");
		iReason = -1 + iReason;
	}
	if(I2C_READ == NULL)
	{
		printf("I2CRead == NULL\n");
		iReason = -2 + iReason;
	}
	if(MS_WAIT == NULL)
	{
		printf("Sleep == NULL\n");
		iReason = -4 + iReason;
	}
	
	dDriverRegistFunctions.I2C_WRITE = I2C_WRITE;
	dDriverRegistFunctions.I2C_READ = I2C_READ;
	dDriverRegistFunctions.MS_WAIT = MS_WAIT;
	
	return iReason;
}

dResult_e eI2CWrite(unsigned short usSlaveAddr, unsigned short usRegIdx, unsigned short usDatas )
{
    unsigned char u8ID;
 
    unsigned char pu8addr[2];
    unsigned char pu8Data[2];
	
    unsigned char u8AddrLen;
    unsigned char u8BufLen;
	
	u8ID = usSlaveAddr;///SaveAddr_Sharp;
	
//#ifndef DEBUG_ON
//	printf("\r\n u8ID  = %x", u8ID);  
//#endif

	u8AddrLen = 2;
	pu8addr[1] = LOBYTE(usRegIdx);
	pu8addr[0] = HIBYTE(usRegIdx);

//#ifndef DEBUG_ON
//	printf("\r\n pu8addr[0]  = %x", pu8addr[0]);  
//	printf("\r\n pu8addr[1]  = %x", pu8addr[1]);  
//#endif

	u8BufLen = 2; ///1
	pu8Data[1] = LOBYTE(usDatas);
	pu8Data[0] = HIBYTE(usDatas);

	//pu8Addr[1] = pusDatas->usAddr ;

//#ifndef DEBUG_ON
//	printf("\r\n pu8Data[0]  = %x", pu8Data[0]);  
//	printf("\r\n pu8Data[1]  = %x", pu8Data[1]);  
//#endif
	 
 //u8ID  = A4 ,pu8addr  = 195F9A ,pBuf  = 5A ,u8AddrLen  = 2 ,ucBufLen  = 1
     //printf("\r\n u8ID  = %x", u8ID);  //j100127
     //printf(" ,pu8addr  = %x", pu8addr);
    // printf(" ,pBuf  = %x", *pBuf);

     //printf(" ,u8AddrLen  = %x", u8AddrLen); //=2
     //printf(" ,ucBufLen  = %x", ucBufLen);  //=1
	
	if(dDriverRegistFunctions.I2C_WRITE == NULL)
	{
		printf("SharpI2CWrite == NULL\n");///ASSERT(0);
		return    S_FAILURE;
	}
	
    /* if( MDrv_IIC_WriteBytes(u8ID, u8AddrLen, pu8addr, (U16x)u8BufLen, pu8Data) == FALSEx )*/
    //if ( (dDriverRegistFunctions.I2C_WRITE)( (U16x)u8ID, (U8x)u8AddrLen, (U8x *)pu8addr, (U16x)u8BufLen, (U8x *)pu8Data) == FALSEx)
    if ( (dDriverRegistFunctions.I2C_WRITE)( (U16x)u8ID, (U8x)u8AddrLen, (U8x *)pu8addr, (U16x)u8BufLen, (U8x *)pu8Data) == -1)
    {
//#ifndef DEBUG_ON
		printf("IIC I2C_WRITE fail\n");///ASSERT(0);
//#endif
		return    S_FAILURE;
    }

//	 printf("\r\n IIC Write Success");

	return S_SUCCESS;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//use point
dResult_e eI2CRead(unsigned short usSlaveAddr, unsigned short usRegIdx, unsigned short* pusDatas )
{
    unsigned char u8ID;
 
    unsigned char pu8addr[2];
    unsigned char pu8Data[2];
	
    unsigned char u8AddrLen;
    unsigned char u8BufLen;
	
	u8ID = usSlaveAddr;///SaveAddr_Sharp;

//#ifndef DEBUG_ON
//	printf("\r\n u8ID  = %x", u8ID);
//#endif

	u8AddrLen = 2;
	pu8addr[1] = LOBYTE(usRegIdx);
	pu8addr[0] = HIBYTE(usRegIdx);

//#ifndef DEBUG_ON
//	printf("\r\n pu8addr[0]  = %x\r\n", pu8addr[0]);
//	printf("\r\n pu8addr[1]  = %x\r\n", pu8addr[1]);
//#endif
	 
	//u8ID  = A4 ,pu8addr  = 195F9A ,pBuf  = 5A ,u8AddrLen  = 2 ,ucBufLen  = 1
	//printf("\r\n u8ID  = %x", u8ID);  //j100127
	//printf(" ,pu8addr  = %x", pu8addr);
	// printf(" ,pBuf  = %x", *pBuf);

	//printf(" ,u8AddrLen  = %x", u8AddrLen); //=2
	//printf(" ,ucBufLen  = %x", ucBufLen);  //=1
	u8BufLen = 2; ///1
	
	if(dDriverRegistFunctions.I2C_READ == NULL)
	{
		printf("SharpI2CWrite == NULL\n");///ASSERT(0);
		return    S_FAILURE;
	}
	
    //if ( (dDriverRegistFunctions.I2C_READ)( (U16x)u8ID, (U8x)u8AddrLen, (U8x *)pu8addr, (U16x)u8BufLen, (U8x *)pu8Data) == FALSEx )
    if ( (dDriverRegistFunctions.I2C_READ)( (U16x)u8ID, (U8x)u8AddrLen, (U8x *)pu8addr, (U16x)u8BufLen, (U8x *)pu8Data) == -1 )
    {
//#ifndef DEBUG_ON
		printf("IIC I2C_READ fail\n");///ASSERT(0);
//#endif
		return    0;
    }

//#ifndef DEBUG_ON
//	printf("\r\n pu8Data[0]  = %x", pu8Data[0]);
//	printf("\r\n pu8Data[1]  = %x", pu8Data[1]);  
//#endif

	*pusDatas = (unsigned short)pu8Data[0]<<8 | pu8Data[1] ;
	//pu8Data[1] = LOBYTE(usDatas);
	//pu8Data[0] = HIBYTE(usDatas);

//#ifndef DEBUG_ON
//	printf("\r\n *pusDatas  = %x", *pusDatas);
//#endif

//	printf("\r\n IIC Read Success");

	return S_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// sleep Function

void MDrv_Timer_Delayms( int iTimes )
{
	if(dDriverRegistFunctions.MS_WAIT == NULL)
	{
		printf("MS_WAIT == NULL\n");///ASSERT(0);
	}
	
    (dDriverRegistFunctions.MS_WAIT)( (int)iTimes );
    
	printf("\r\n sleep Times = %d", iTimes);

}

