/*=============================================================
 * Copyright C        Realtek Semiconductor Corporation, 2013 *
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/
/**
 * @file: for some global function like math, etc.
 
 * @Author: Sophia_xu
 
 * @date 2013/03/28
 
 * @version { 1.0 }
 *
 */

#include <rtd_types_qc.h>

#define REG32( addr )		  (*(volatile UINT32 *)(addr))
 
int abs(int x)
{
	int result;

	if(x>0)
		result = x;
	else
		result = 0-x;

	return result;
}

UINT32 GetFieldVal(UINT8 msb, UINT8 lsb)
{
	UINT32 FieldVal = 0;

	UINT32 i; 
	for (i=lsb; i<msb+1; i++)
	{
		FieldVal |= 1<<i;
	}

	return FieldVal;
}

/*
* eva_sun
* get maskval for rtd_maskl(addr, maskval, orval);
*
*/
UINT32 GetMaskAnd(UINT32 msb,UINT32 lsb)
{
	UINT32 i;
   	UINT32 SetML=0xFFFFFFFF;
	
   	for(i = lsb;i<=msb;i++)
        	SetML&=~(1<<i);
	
	return SetML;
}


/************************************************************************
 *
 *                          sys_get_time & sys_get_time_freq
 *  Description : 
 *  ---------------
 *  get current time & get current count frequency
 *
 *
 *  Return values :
 *  ---------------
 *  
 *  Author: sophia
 *
 *  None
 *
 ************************************************************************/

void sys_get_time(UINT32* time)
{
	*time = REG32(0xb801b628);//timer2
}

void sys_get_time_freq(UINT32* freq)
{
//#ifdef FPGA
    	//*freq = 33000;
//#else
   	*freq = 27000000;
//#endif
}



