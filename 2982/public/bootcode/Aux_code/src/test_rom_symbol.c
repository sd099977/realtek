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
#include "NOCS.h"
#include "rom_symbol.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern NOCS_Certificate *rom_cert;
extern NOCS_Params *rom_params;
extern NOCS_Aux_Code_Tail *rom_aux_code_tail;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static int (*p_init_spi)(void);

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int (*rom_get_boot_flash_type)(void);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

#if defined(ENV_FPGA)
static void test_rom_symbol_fpga(void)
{
	int res;
	printf("in %s\n", __FUNCTION__);
	p_init_spi = (int (*)(void))ROM__T__init_spi;

	res = p_init_spi();
	printf("init_spi: %d\n", res);
	res = rom_get_boot_flash_type();
	printf("get_boot_flash_type: %d\n", res);

	printf(">>>>>> NOCS_Certificate\n\n");
	if (rom_cert != NULL) {
		hexdump("External_Public_RSA_Key", rom_cert->External_Public_RSA_Key, sizeof(rom_cert->External_Public_RSA_Key));
		printf("Key_Rights: 0x%x\n", rom_cert->Key_Rights);
		printf("Size_Of_SCS_Params_Area: 0x%x\n", rom_cert->Size_Of_SCS_Params_Area);
		printf("Address_Of_SCS_Param_Area: 0x%x\n", rom_cert->Address_Of_SCS_Param_Area);
	}

	printf(">>>>>> NOCS_Params\n\n");
	if (rom_params != NULL) {
		printf("Key_Rights_CheckID: 0x%x\n", rom_params->Key_Rights_CheckID);
		printf("External_Flash_Device_Params: 0x%x\n", rom_params->External_Flash_Device_Params);
		printf("External_RAM_Params: 0x%x\n", rom_params->External_RAM_Params);
		printf("External_Boot_Specific_Params: 0x%x\n", rom_params->External_Boot_Specific_Params);
		printf("STR_Default_Region_Min_Size: 0x%x\n", rom_params->STR_Default_Region_Min_Size);
		printf("Address_of_Aux_Code_Area: 0x%x\n", rom_params->Address_of_Aux_Code_Area);
		printf("Size_of_Aux_Code_Area: 0x%x\n", rom_params->Size_of_Aux_Code_Area);
		printf("Address_of_Boot_Code_Area: 0x%x\n", rom_params->Address_of_Boot_Code_Area);
		hexdump("Total_Area_Size", rom_params->Total_Area_Size, sizeof(rom_params->Total_Area_Size));
		printf("Total_Area_Size_Selection: 0x%x\n", rom_params->Total_Area_Size_Selection);
		hexdump("Flash_Protection_Key", rom_params->Flash_Protection_Key, sizeof(rom_params->Flash_Protection_Key));
	}

	printf(">>>>>> NOCS_Aux_Code_Tail\n\n");
	if (rom_aux_code_tail != NULL) {
		printf("Key_Rights: 0x%x\n", rom_aux_code_tail->Key_Rights);
	}
}
#endif

#if defined(ENV_SIMULATION)
static void test_rom_symbol_sim(void)
{
	int res;
	// test of Aux code call function in ROM
	sim_debug_print(0x08001122);
	p_init_spi = (int (*)(void))ROM__T__init_spi;
	sim_debug_print(ROM__T__init_spi);
	res = p_init_spi();	// should return 0
	sim_debug_print(res);
	sim_debug_print(0x08003344);
}
#endif

#if defined(ENV_REALCHIP)
static void test_rom_symbol_realchip(void)
{
}
#endif

void test_rom_symbol(void)
{
#if defined(ENV_FPGA)
	test_rom_symbol_fpga();
#elif defined(ENV_SIMULATION)
	test_rom_symbol_sim();
#elif defined(ENV_REALCHIP)
	test_rom_symbol_realchip();
#endif
}
