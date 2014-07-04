#ifndef TURNKEY_I2C_H
#define TURNKEY_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif //cplusplus

#include "frdapi.h"
//?#include <stdio.h>
//?#include <unistd.h>

#define		U8x		unsigned char
#define		U16x	unsigned short
#define		U32x	unsigned long
#define		BYTEx	unsigned char
#define		FALSEx	0

typedef unsigned char	MS_BOOL;
typedef U8x	BOOLEANx;

// define I2C function
// For ex

//extern BOOLEANx MDrv_IIC_WriteBytes(U16x u16BusNumSlaveID, U8x AddrCnt, U8x* pu8addr, U16x u16size, U8x* pBuf);
//extern BOOLEANx MDrv_IIC_ReadBytes(U16x u16BusNumSlaveID, U8x ucSubAdr, U8x* paddr, U16x ucBufLen, U8x* pBuf);

//extern MS_BOOL MApi_SWI2C_WriteBytes(U16x u16BusNumSlaveID, U8x AddrCnt, U8x* pu8addr, U16x u16size, U8x* pBuf);	//sakata20111027
//extern MS_BOOL MApi_SWI2C_ReadBytes(U16x u16BusNumSlaveID, U8x ucSubAdr, U8x* paddr, U16x ucBufLen, U8x* pBuf);		//sakata20111027

// define Sleep function
// For ex

//#define MDrv_Timer_Delayms(ms) usleep(ms*1000)

// I2C Wrapper for SHARP

extern int vfrdDriverRegistrationFunction(int (*I2CWrite)(U16x, U8x, U8x *, U16x, U8x *), 
										int (*I2CRead)(U16x, U8x, U8x *, U16x, U8x *),
										int (*Wait)(int));

#ifdef __cplusplus
}
#endif //__cplusplus


#endif /* TURNKEY_I2C_H */

