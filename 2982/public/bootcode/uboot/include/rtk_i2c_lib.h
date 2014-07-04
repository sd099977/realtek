#ifndef __RTK_I2C_LIB_H__
#define __RTK_I2C_LIB_H__

#define I2C_Read(args...)                I2C_Read_EX(0, args)
#define I2C_Write(args...)               I2C_Write_EX(0, args)

//#define MAX_I2C_CNT                      3
//#define FIFO_THRESHOLD                   4
//#define DEFAULT_SPEED                    100

#define S_OK         0
#define S_FALSE     -1

extern void I2C_Init(void);
extern int I2C_Write_EX(unsigned char id, unsigned short Addr, unsigned short nData, unsigned char* pData);
extern int I2C_Read_EX(unsigned char id, unsigned short Addr, unsigned short nSubAddr, unsigned char* pSubAddr, unsigned short nData, unsigned char* pData);
#ifdef CONFIG_PANEL_SHARP_60_MEMC
extern int I2C_Write_EX2(unsigned short Addr, unsigned char nSubAddr, unsigned char* pSubAddr, unsigned short nData, unsigned char* pData);
extern int I2C_Read_EX2(unsigned short Addr, unsigned char nSubAddr, unsigned char* pSubAddr, unsigned short nData, unsigned char* pData);
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC
extern int I2C_SetSpeed(unsigned char Id, int KHz);

extern int I2C_StartXfer(
    unsigned char           Id,
    unsigned short          Addr,
    unsigned short          nSubAddr,
    unsigned char*          pSubAddr,
    unsigned short          nData,
    unsigned char*          pData
    );

extern unsigned char I2C_GetBusCount(void);

#endif

