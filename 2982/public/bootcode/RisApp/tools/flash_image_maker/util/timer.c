//=================================================================================================
// Copyright (c) 2009 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: timer.c
// Abstract:
//   Hardware IO Control Functions in Viking Timer
//
// History:
//	 2009-01-20			cyyang			Initial Version
//=================================================================================================

#ifndef _TIMER_H_
#include "timer.h"
#endif

// add by alan: switch between timer mode (use interrupt) or counter mode (use polling)
//#define USE_TIMER_MODE

//=================================================================================================
// Name: InitTimer
// Description: Initial Register for Timer
// Input: 
//	- (UINT8) byTimerId: Timer ID
//
// Output: None
//=================================================================================================
void InitTimer(unsigned char byTimerId, unsigned int dwInit)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

	//Disable Interrupt
   REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_ICR)) = TIMERINFO_INTERRUPT_DISABLE;

	//Disable Timer
	REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_CR)) = TIMERINFO_TIMER_DISABLE;

#ifdef USE_TIMER_MODE
	//Set The Initial Value
	REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_TVR)) = dwInit;

	//Enable Timer Mode
	REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_CR)) = TIMERINFO_TIMER_ENABLE;
#else
	//Set The Initial Value
	REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_TVR)) = 0xffffffff;

	//Enable Timer Mode
	REG32((TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_CR)) = TIMERINFO_COUNTER_ENABLE;
#endif

	// Clear Interrupt Pending (must after enable)
   REG32(TIMERINFO_INT_BASE_ADDRESS) = 1 << (byTimerId+TIMERINFO_INT_TIMER0_BIT);

}
//=================================================================================================
#ifndef USE_TIMER_MODE
static void wait_us(unsigned char byTimerId, unsigned int dwMicroSecond)
{
    unsigned int first, current, last;
    unsigned int reg_cvr_addr;

    reg_cvr_addr = (TIMERREG_BASE_ADDRESS_TIMER0 + (byTimerId*TIMERREG_REGISTER_NUMBER)+TIMERREG_OFFSET_ADDRESS_CVR);
    first = REG32(reg_cvr_addr);
    
#ifdef FPGA
    last  = first + 25*dwMicroSecond;
#else
    last  = first + 27*dwMicroSecond;
#endif
  
    if (last >= first)
    do
    {
	/* no wrap - continue while between first and last */
        current = REG32(reg_cvr_addr);
       
    }
    while( current < last && current >= first );
    else
    do
    {
	/* wrap - continue until between first and last */
        current = REG32(reg_cvr_addr);
        
    }
    while( current < last || current >= first );
}
#endif

//=================================================================================================
// Name: SystemDelay
// Description: Delay Specific Time
// Input: 
//	- (UINT32) dwMicroSecond: Delay Time (Unit: 1 us)
//
// Output: None
//=================================================================================================
void mdelay(unsigned int dwMiniSecond)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

#ifdef ENV_SIMULATION
	//Initial Timer 7
	InitTimer(TIMERINFO_ID_TIMER7, 1*TIMERINFO_MSEC);
#else
	//Initial Timer 7
	InitTimer(TIMERINFO_ID_TIMER7, dwMiniSecond*TIMERINFO_MSEC);
#endif

#ifdef USE_TIMER_MODE
	//Wait for Interrupt Pending Status
	while(SystemTimeout(TIMERINFO_ID_TIMER7) == FALSE);
#else
	// polling until specified time
	wait_us(TIMERINFO_ID_TIMER7, dwMiniSecond * 1000);
#endif
}
//=================================================================================================
void udelay(unsigned int dwMicroSecond)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

#ifdef ENV_SIMULATION
	//Initial Timer 7
	InitTimer(TIMERINFO_ID_TIMER7, 1*TIMERINFO_USEC);
#else
	//Initial Timer 7
    InitTimer(TIMERINFO_ID_TIMER7, dwMicroSecond*TIMERINFO_USEC);
#endif
 
#ifdef USE_TIMER_MODE
   //Wait for Interrupt Pending Status
    while(SystemTimeout(TIMERINFO_ID_TIMER7) == FALSE);	
#else
	// polling until specified time
	wait_us(TIMERINFO_ID_TIMER7, dwMicroSecond);
#endif
}
//=================================================================================================
#ifdef USE_TIMER_MODE
bool SystemTimeout(unsigned char byTimerId)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

	bool	bIoStatus = FALSE;
	UINT32 	bitmask = 1 << (byTimerId+TIMERINFO_INT_TIMER0_BIT);

	if(REG32(TIMERINFO_INT_BASE_ADDRESS) & bitmask)
	{
		bIoStatus = TRUE;
	}

	return bIoStatus;
}
#endif
//=================================================================================================
// End of File
