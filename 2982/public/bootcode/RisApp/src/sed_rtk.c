#include "sed_common.h"
#include "sed_drv_gpio.h"
#include "sed_drv_rng.h"

#ifndef SKIP_SED_FUNC
#define CHAR_CPU_INTERNAL_REGS   1
int sed_cmd_rtk_reg_read (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1;
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Read value from address into internal registers */
	sed_printf("Addr: 0x%08X\n", (uint32)ptr);
  	reg1 = *(ptr++);

	sed_printf("Value: 0x%08X\n", (uint32)reg1);

 	return -1;
}

int sed_cmd_rtk_reg_write (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1;
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

 	/* Write input value to all available internal registers */
	reg1 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 8);

 	/* Write values from internal registers to addr */
	sed_printf("Addr: 0x%08X\n", (uint32)ptr);

	*(ptr++) = reg1;

 	/* Read values from addr to internal registers */
	ptr = (uint32 *)(uint32) addr;
 	reg1 = *(ptr++);

	sed_printf("Value: 0x%08X\n", (uint32)reg1);

	return -1;
}

#endif //?#ifndef SKIP_SED_FUNC