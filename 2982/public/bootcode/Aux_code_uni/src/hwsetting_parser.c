
/************************************************************************
 *
 *  hwsetting.c
 *
 *  Parse HW setting function for Magellan internal ROM
 *
 * 
 * Copyright (c) 2012 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
//#include "typedef.h"
#include "reset_def_sirius.h"
//#include "uart.h"
//#include "error_type.h"
//#include "utility.h"
#include "timer.h"
//#include "mis_reg.h"

#include "util.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#ifdef ENV_SIMULATION
#define	WRITE_WAIT_TIMEOUT	1
#else
#define	WRITE_WAIT_TIMEOUT	10
#endif

#define MAGIC_DUMMY_SYMBOL				0x00000000
#define MAGIC_HWSETTING_END_SYMBOL	0xffffffff
#define MAGIC_HWSETTING_HIDDEN_SYMBOL	0xfffffffe

#define MAGIC_CONDITIONAL_MASK						0xffffff00

#define MAGIC_CONDITIONAL_IF_EQUAL_ADDRESS		0xffffff08
#define MAGIC_CONDITIONAL_IF_NOT_EQUAL_ADDRESS	0xffffff28
#define MAGIC_CONDITIONAL_IF_MASK					0xffffff68
#define MAGIC_CONDITIONAL_IF_VALUE					0xffffff88
#define MAGIC_CONDITIONAL_IF_START					0xffffffa8
#define MAGIC_CONDITIONAL_IF_END						0xffffffc8

#define SPECIAL_ADDRESS_NEED_DELAY1	0xb8060050
#define SPECIAL_ADDRESS_NEED_DELAY2	0xb801a800
#define SPECIAL_ADDRESS_MASK_NEED_DELAY2	0xffffff00

#define CONDITIONAL_TYPE_NOT_DEFINED   0
#define CONDITIONAL_TYPE_IF_EQUAL		1
#define CONDITIONAL_TYPE_IF_NOT_EQUAL	2

//#define udelay(s)		sys_wait_us(s)

#if defined(DEBUG)
#define PRINTS print_uart
#define PRINT_HEX print_val
#else
#define PRINTS(x)
#define PRINT_HEX(x)
#endif

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static bool g_can_exec_cmd = TRUE;
static unsigned char g_conditional_type = CONDITIONAL_TYPE_NOT_DEFINED;
static unsigned int g_conditional_addr = 0;
static unsigned int g_conditional_mask = 0;
static unsigned int g_conditional_value = 0;


/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int *rom_sys_boot_flash_type;

/************************************************************************
 *  Static function prototypes
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

/*
 * parse & execute instruction in the HW setting 
 *
 * input argument:
 *	ptr: pointer to HW setting buffer
 *	limit: HW setting size (0 means ignore size check. parse until get terminating symbol)
 *	parsed_bytes: number of parsed bytes
 *	skip: 0 means execute HW setting, otherwise skip HW setting (only accumulate parsed bytes)
 * return:
 *	0 means exceeds HW size limit, 1 means get terminating sybmol (0xffffffff)
 */
int parse_hw_setting_c(unsigned int *ptr, const unsigned int limit,
	 unsigned int *parsed_bytes, const char skip)
	{
		unsigned int i, type;
		unsigned int addr, value, mask;
		unsigned int temp, count;
	
		i = 0; count = 0;
	
		// clear watchdog counter
		//REG32(MIS_TCWTR) = 0x1; 	
		PRINTS("\n");
	
		while (1) {

			PRINT_HEX(count);
			PRINTS(" ");

			/* check if parsed bytes exceed limit */
			if (limit != 0) {
				if (count >= limit)
					break;
			}
	
			/* get first word of instruction */
			temp = ptr[i++];
	
			count += 4;

			PRINTS("[");
			PRINT_HEX(temp);
			PRINTS("] ");

			if (temp == MAGIC_DUMMY_SYMBOL)
				continue;	// skip dummy instruction
			else if (temp == MAGIC_HWSETTING_END_SYMBOL) {
				*parsed_bytes = count;
				return 1;	// exit when get terminating symbol
			}
			else if (temp == MAGIC_HWSETTING_HIDDEN_SYMBOL) {
				*parsed_bytes = 0;
				return 2;	// exit when get hidden symbol
			}
	
			/* determine instruction type (two LSB bits in first word) */
			type = temp & 0x3;
			addr = temp & ~0x3; // remember to strip two LSB bits
			switch (type) {
				case 0: // write instruction
					value = ptr[i++];
					count += 4;


					if (skip)
						break;
	
					if(((addr & MAGIC_CONDITIONAL_MASK) != MAGIC_CONDITIONAL_MASK))
					{
						if (!g_can_exec_cmd) {
							PRINTS("conditional skip     (2) ");			
							PRINTS("write 0x");
							PRINT_HEX(addr);
							PRINTS(" = 0x");
							PRINT_HEX(value);
							PRINTS("\n");
							break;
						}
				
					REG32(addr) = value;
					//to check this register need delay or not
					if((addr == SPECIAL_ADDRESS_NEED_DELAY1) || ((addr & SPECIAL_ADDRESS_MASK_NEED_DELAY2) == SPECIAL_ADDRESS_NEED_DELAY2))
					{
						udelay(WRITE_WAIT_TIMEOUT);
					}
					PRINTS("write 0x");
					PRINT_HEX(addr);
					PRINTS(" = 0x");
					PRINT_HEX(value);
					PRINTS("\n");
					break;
				}

				PRINTS("conditional 0x");
				PRINT_HEX(value);
				PRINTS("\n");
				
				if (addr == MAGIC_CONDITIONAL_IF_EQUAL_ADDRESS) {
					g_conditional_type = CONDITIONAL_TYPE_IF_EQUAL;
					g_conditional_addr = value;
				} else if (addr == MAGIC_CONDITIONAL_IF_NOT_EQUAL_ADDRESS) {
					g_conditional_type = CONDITIONAL_TYPE_IF_NOT_EQUAL;
					g_conditional_addr = value;				
				} else if (addr == MAGIC_CONDITIONAL_IF_MASK) {
					g_conditional_mask = value;
				} else if (addr == MAGIC_CONDITIONAL_IF_VALUE) {
					g_conditional_value = value;
				} else if ((addr == MAGIC_CONDITIONAL_IF_START) && (g_conditional_type != CONDITIONAL_TYPE_NOT_DEFINED)) {
					if (g_conditional_type == CONDITIONAL_TYPE_IF_EQUAL) {
						if ((REG32(g_conditional_addr) & g_conditional_mask) == g_conditional_value) {
							g_can_exec_cmd = TRUE;
						} else {
							g_can_exec_cmd = FALSE;
						}
				}
					else if (g_conditional_type == CONDITIONAL_TYPE_IF_NOT_EQUAL) {
						if ((REG32(g_conditional_addr) & g_conditional_mask) != g_conditional_value) {
							g_can_exec_cmd = TRUE;
						} else {
							g_can_exec_cmd = FALSE;
						}
					}
				} else if (addr == MAGIC_CONDITIONAL_IF_END) {
					g_conditional_type = CONDITIONAL_TYPE_NOT_DEFINED;
					g_can_exec_cmd = TRUE;
				}

					break;
	
				case 1: // polling instruction
					mask = ptr[i++];
					value = ptr[i++];
					count += 8;
					
					if (skip||(!g_can_exec_cmd)){
						if (!g_can_exec_cmd) {
							PRINTS("conditional skip	  (3) ");			
							PRINTS("polling 0x");
							PRINT_HEX(addr);
							PRINTS(" & 0x");
							PRINT_HEX(mask);
							PRINTS(" = 0x");
							PRINT_HEX(value);
							PRINTS("\n");
						}
						break;
					}
				
					polling_done(addr, mask, value);

					PRINTS("polling 0x");
					PRINT_HEX(addr);
					PRINTS(" & 0x");
					PRINT_HEX(mask);
					PRINTS(" = 0x");
					PRINT_HEX(value);
					PRINTS("\n");

					break;
	
				case 2: // mask instruction
					mask = ptr[i++];	// AND mask
					value = ptr[i++];	// OR mask
					
					count += 8;
					
					if (skip||(!g_can_exec_cmd)) {
						if (!g_can_exec_cmd) {
							PRINTS("conditional skip     (3) ");
							PRINTS("set 0x");
							PRINT_HEX(addr);
							PRINTS(" & 0x");
							PRINT_HEX(mask);
							PRINTS(" | 0x");
							PRINT_HEX(value);
							PRINTS("\n");
						}
						break;
					}
				
					bitwise_AND_OR(addr, mask, value);

					PRINTS("set 0x");
					PRINT_HEX(addr);
					PRINTS(" & 0x");
					PRINT_HEX(mask);
					PRINTS(" | 0x");
					PRINT_HEX(value);
					PRINTS("\n");

					break;
	
				case 3: // NOP instruction
					value = ptr[i++];
	
					count += 4;
					if (skip||(!g_can_exec_cmd)) {

						if (!g_can_exec_cmd) {
							PRINTS("conditional skip	  (2) ");
							PRINTS("wait ");
							PRINT_HEX(value);
							PRINTS(" NOP loop\n");
						}

						break;
					}

					wait_loop(value);

					PRINTS("wait ");
					PRINT_HEX(value);
					PRINTS(" NOP loop\n");

					break;
	
				default:	// should not happen
					PRINTS("unknown instruction: ");
					PRINT_HEX(type);

					break;
			}
		}
	
		*parsed_bytes = count;
		return 0;	// exceeds HW size limit (HW setting is yet not finished)
}
