/****************************************************************************************
* Program Name:     
* Author:               
* Date:                 
* Description:   
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "otp_reg.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
//extern int atoi(char *s);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/
//static int get_options(int argc, char **argv);
//static void show_help(void);

/************************************************************************
 *  Function body
 ************************************************************************/

static unsigned int get_random_number(void)
{
	// polling RNG until random number ready
	while ((REG32(0xb800182c) & 0x1) == 0)
		;

	return REG32(0xb8001838);
}

#if defined(ENV_SIMULATION)
void init_memory_simulation(void)
{
	unsigned int value;
	unsigned int dc_mem_scramble_total[7];

	if (OTP_MEM_OBF_EN == OTP_MEM_OBF_ENABLED) {
		unsigned int idx;

		// release rstn_scpu before access SCPU scramble register
		REG32(0xb8000004) |= 0x10;

		// Note: DC_SYS scramble registers are not continuous
		dc_mem_scramble_total[0] = 0xb8008608;
		dc_mem_scramble_total[1] = 0xb800860c;
		dc_mem_scramble_total[2] = 0xb8008610;
		dc_mem_scramble_total[3] = 0xb8008614;
		dc_mem_scramble_total[4] = 0xb8008618;
		dc_mem_scramble_total[5] = 0xb8008620;
		dc_mem_scramble_total[6] = 0xb8008624;

		// DC_SYS/SCPU scramble
		for(idx = 0; idx < 7; idx++) {
			value = get_random_number();
			REG32(dc_mem_scramble_total[idx]) = value;
			REG32((0xb801cf44 + idx*4)) = value;
		}

		/* DC_PHY */
		for(idx = 0; idx < 16; idx++) {
			value = get_random_number();
			REG32((0xb8008e78 + idx*4)) = value;
		}

		REG32(0xb8008e74) = 0x3;  // phy scramble enable
		REG32(0xb801a844) = 0x1;  //KEY LOCK
		
		for(idx = 0; idx < 16; idx++) {
			REG32((0xa0080000 + idx*4) ) =  idx;
		}

		for(idx = 0; idx < 16; idx++) {
			if(REG32((0xa0080000 + idx*4)) !=  idx ){
				sim_debug_print(0xdeaddead); // Simlation FAIL flag.
				while(1) ;
			}
		}

		// restore state of rstn_scpu
		REG32(0xb8000004) &= ~0x10;
		
		sim_debug_print(0xbeef6330); // Simlation Pass flag.
	}

}
#endif

#if defined(ENV_FPGA)
void init_memory_fpga(void)
{
	// no RNG in FPGA
}
#endif

int init_memory(void)
{
	int res = 0;

#if defined(ENV_FPGA)
	init_memory_fpga();
#elif defined(ENV_SIMULATION)
	init_memory_simulation();
#endif

	return res;
}

