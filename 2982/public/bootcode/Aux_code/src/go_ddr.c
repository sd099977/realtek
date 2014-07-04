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
#include "sys_reg.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int _f_arm_start, _e_arm_start;
extern unsigned int _f_arm_start2, _e_arm_start2;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
/*
	static const unsigned int while_loop_mips[] = {
		0x1000ffff,		// 1: 	b	1b 
		0x0			// 	nop
	};
*/
	// ARM instruction from DV
	static const unsigned char arm_instruction[] = {
		0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5,
		0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5, 0x1c, 0xf0, 0x9f, 0xe5,
		0x10, 0xf0, 0x9f, 0xe5, 0x00, 0x01, 0x50, 0x00, 0x04, 0x01, 0x50, 0x00, 0x08, 0x01, 0x50, 0x00,
		0x0c, 0x01, 0x50, 0x00, 0x10, 0x01, 0x50, 0x00, 0x20, 0x30, 0x00, 0x00, 0x18, 0x01, 0x50, 0x00,
		0x1c, 0x01, 0x50, 0x00, 0x00, 0xf0, 0x20, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void (*rom_copy_memory)(void *dst, void *src, unsigned int size);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

#if defined(ENV_SIMULATION)
void go_ddr_simulation(void)
{
	int i;

/*	// DV will do this job
	// prepare MIPS code on DDR
	for (i = 0; i < sizeof(while_loop_mips); i+=4) {
		REG32(0x80204000 + i) = while_loop_mips[i];	// for ACPU
		REG32(0x80304000 + i) = while_loop_mips[i];	// for KCPU
	}
*/

	// prepare ARM code on DDR
	for (i = 0; i < sizeof(arm_instruction); i++) {
		REG8(0xa0000000 + i) = arm_instruction[i];
	}

	/* set jump address to test pass */
	REG32(0xb801a608) = 0x80304000;		// KCPU
	//REG32(0xb801a610) = 0x80004000;		// SCPU
	REG32(0xb806012c) = 0x80204000;		// ACPU
	//REG32(0xb801a61c) = 0x80104000;		// VCPU

	/* enable CPU clock */
	REG32(0xb8000004) |= 0x00000110;
	REG32(0xb8000008) |= 0x06000000;
	REG32(0xb8000010) |= 0x0000000e;

	sim_debug_print(0x0800dddd);
}
#endif

#if defined(ENV_FPGA)||defined(ENV_REALCHIP)
void go_ddr_realchip(void)
{
	unsigned char *p_start, *p_end;

	debug("prepare ARM redirect image on DDR\n");
	p_start = (unsigned char *)&_f_arm_start;
	p_end = (unsigned char *)&_e_arm_start;
	copy_memory((unsigned char *)0xa0000000, p_start, p_end - p_start);
	p_start = (unsigned char *)&_f_arm_start2;
	p_end = (unsigned char *)&_e_arm_start2;
	copy_memory((unsigned char *)0xa001f800, p_start, p_end - p_start);
}
#endif

void go_ddr(void)
{
#if defined(ENV_SIMULATION)
	go_ddr_simulation();
#else
	go_ddr_realchip();
#endif
}
