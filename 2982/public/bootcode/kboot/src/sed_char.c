#include "sed_common.h"
#include "sed_drv_gpio.h"
#include "sed_drv_rng.h"

//#define _DEBUG_CHAR_DRIVER

#define CHAR_CPU_INTERNAL_REGS   5
int sed_cmd_char_host_read (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2, reg3, reg4, reg5;
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;
	uint32 edc = 0;
	uint8 sts = C_HOST_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Read value from address into internal registers */
	//sed_printf("Addr: 0x%08X\n", (uint32)ptr);
#if defined (SIRIUS) || defined (FPGA)
	__asm__ __volatile__ (
		"lw    %1, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %2, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %3, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %4, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %5, 0(%6);"
		: "=r" (ptr), "=r" (reg1), "=r" (reg2), "=r" (reg3), "=r" (reg4), "=r" (reg5)
		: "0" (ptr)
	);
#else
	reg1 = *(ptr++);
	reg2 = *(ptr++);
	reg3 = *(ptr++);
	reg4 = *(ptr++);
	reg5 = *(ptr);
#endif
	GPIO_pulse();

	/* Compute XOR of all values and store in response */
#if defined (SIRIUS) || defined (FPGA)
	__asm__ __volatile__ (
		"xor %0, %1, %2;"
		"xor %0, %1, %3;"
		"xor %0, %1, %4;"
		"xor %0, %1, %5;"
		"xor %0, %1, %6;"
		: "=r" (edc)
		: "0" (edc), "r" (reg1), "r" (reg2), "r" (reg3), "r" (reg4), "r" (reg5)
	);
#else
	edc ^= reg1;
	edc ^= reg2;
	edc ^= reg3;
	edc ^= reg4;
	edc ^= reg5;
#endif
	GPIO_toggle();

	/* Write the addr used to fetch last value to response */
	set_rsp_data_addr64(obuf, RSP_DATA_OUT_IDX, (addr64)(uint32)ptr);

	GPIO_toggle();

	/* Transfer results from internal register to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 12, reg2);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 16, reg3);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 20, reg4);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 24, reg5);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8 + (CHAR_CPU_INTERNAL_REGS<<2), edc);

	GPIO_toggle();

	return sed_command_exit(obuf, C_HOST_READ, 8 + (CHAR_CPU_INTERNAL_REGS << 2) + 4, sts);
}

int sed_cmd_char_host_write (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2, reg3, reg4, reg5;
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;
	uint8 sts = C_HOST_WRITE_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check input parameters */
	if ((((uint32) ptr) >= 0xb807a800)||(((uint32) ptr) < 0xb8000000)) {
		sts = C_HOST_WRITE_INVALID_PARAM;
		return sed_command_exit(obuf, C_HOST_WRITE, 8 + (CHAR_CPU_INTERNAL_REGS << 2), sts);
	}

	GPIO_pulse();

	/* Write input value to all available internal registers */
	reg1 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 8);
	reg2 = reg1;
	reg3 = reg1;
	reg4 = reg1;
	reg5 = reg1;
//	sed_printf("Value: 0x%08X\n", reg1);

	GPIO_toggle();

	/* Write values from internal registers to addr */
//	sed_printf("Addr: 0x%08X\n", (uint32)ptr);
#if defined (SIRIUS) || defined (FPGA)
	__asm__ __volatile__ (
		"sw    %2, 0(%1);"
		"addiu %0,   %1, 4;"
		"sw    %3, 0(%1);"
		"addiu %0,   %1, 4;"
		"sw    %4, 0(%1);"
		"addiu %0,   %1, 4;"
		"sw    %5, 0(%1);"
		"addiu %0,   %1, 4;"
		"sw    %6, 0(%1);"
		: "=r" (ptr)
		: "0" (ptr), "r" (reg1), "r" (reg2), "r" (reg3), "r" (reg4), "r" (reg5)
		: "memory"
	);
#else
	*(ptr++) = reg1;
	*(ptr++) = reg2;
	*(ptr++) = reg3;
	*(ptr++) = reg4;
	*(ptr) = reg5;
#endif
	GPIO_pulse();

	/* Read values from addr to internal registers */
	ptr = (uint32 *)(uint32) addr;
#if defined (SIRIUS) || defined (FPGA)
	__asm__ __volatile__ (
		"lw    %1, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %2, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %3, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %4, 0(%6);"
		"addiu %0,   %6, 4;"
		"lw    %5, 0(%6);"
		: "=r" (ptr), "=r" (reg1), "=r" (reg2), "=r" (reg3), "=r" (reg4), "=r" (reg5)
		: "0" (ptr)
	);
#else
	reg1 = *(ptr++);
	reg2 = *(ptr++);
	reg3 = *(ptr++);
	reg4 = *(ptr++);
	reg5 = *(ptr);
#endif
	GPIO_toggle();

	/* Write address used to fetch last value and all values into response */
	set_rsp_data_addr64(obuf, RSP_DATA_OUT_IDX, (addr64)(uint32)ptr);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 12, reg2);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 16, reg3);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 20, reg4);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 24, reg5);

	GPIO_toggle();

	return sed_command_exit(obuf, C_HOST_WRITE, 8 + (CHAR_CPU_INTERNAL_REGS << 2), sts);
}

int sed_cmd_char_host_read_iter (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1;
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;
	uint8 numRun = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 8), i;
	uint32 edc = 0;
	uint8 sts = C_HOST_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	edc = 0;

	GPIO_pulse();

	//sed_printf("Addr: 0x%08X\n", (uint32)ptr);
	for (i = 0; i < numRun; i++) {
		/* Read value from addr to internal register */
		reg1 = *(ptr);
		/* XOR */
		edc ^= reg1;
		/* Copy value from internal register to response */
		set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8 + (i << 2), reg1);
	}
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8 + (i << 2), edc);

	GPIO_toggle();

	/* Store addr used to fetch value into resonse  */
	set_rsp_data_addr64(obuf, RSP_DATA_OUT_IDX, (addr64)(uint32)ptr);

	GPIO_pulse();

	return sed_command_exit(obuf, C_HOST_READ_ITER, 8 + (numRun << 2) + 4, sts);
}

int sed_cmd_char_host_linear (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1;
	uint8 sts = C_HOST_LINEAR_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Set counter initial value to internal register */
	reg1 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX);
	//sed_printf("Init: 0x%08X\n", reg1);

	GPIO_toggle();

	/* Perform 100 increment instructions sequentially (no loops) */
#if defined (SIRIUS) || defined (FPGA)
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
	__asm__ __volatile__("addiu %0, %1, 1":"=r"(reg1):"0"(reg1));
#else
	reg1 += 100;
#endif
	GPIO_toggle();

	/* Transfer the content of register to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);

	GPIO_pulse();

	return sed_command_exit(obuf, C_HOST_LINEAR, 4, sts);
}

int sed_cmd_char_read_infinite (uint8 *ibuf, uint8 *obuf)
{
	addr64 addr = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX);
	uint32 *ptr = (uint32 *)(uint32) addr;
	uint32 value;
	uint8 sts = C_HOST_INFINITE_ERROR;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Infinite read, should not exit */
	//sed_printf("Addr: 0x%08X\n", (uint32)ptr);
	while (1) {
		value = *ptr;
	}

	GPIO_pulse();

	/* Store last value read into response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, value);

	return sed_command_exit(obuf, C_READ_INFINITE, 4, sts);
}

int sed_cmd_char_host_cond (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2;
	uint8 sts = C_HOST_COND_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Set internal register 1 to init */
	reg1 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX);
	//sed_printf("Init: 0x%08X\n", reg1);

	/* Set internal register 2 to 0x5A5A5A5A */
	reg2 = 0x5A5A5A5A;

	GPIO_toggle();

	/* We have checked the assembly code,
	  this code won't be compiled optimized */
	/* Decrement loop until register 1 is 0 */
	while (reg1) {
		reg1--;
	}

	GPIO_toggle();

	/* Copy register 1 to register 2 */
	reg2 = reg1;

	GPIO_toggle();

	/* Store register 1, 2 and edc into response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 4, reg2);
	reg1 = reg1 ^ reg2;
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg1);

	GPIO_pulse();

	return sed_command_exit(obuf, C_HOST_CONDITIONAL, 12, sts);
}

int sed_cmd_char_get_rand (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1;
	uint8 sts = C_GET_RANDOM_OK;
	unsigned long retry_count = 0;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Sample TRNG output and store in internal register */
	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG failed, wait RNG ready timeout\n");
			#endif
			break;
            	}
     	}

	reg1 = REG32(RNG_RESULTR);

	GPIO_toggle();

	//sed_printf("sed_cmd_char_get_rand: 0x%08X\n", reg1);

	/* Transfer the result from internal register to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);

	GPIO_pulse();

	return sed_command_exit(obuf, C_GET_RANDOM, 4, sts);
}

int sed_cmd_char_host_rng (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2, reg3, reg4, reg5;
	uint8 sts = C_HOST_RNG_OK;
	unsigned long retry_count = 0;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Read N TRNG outputs and store in internal registers */

	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG1 failed, wait RNG ready timeout\n");
			#endif
			sts = C_HOST_RNG_ERROR;
			break;
            	}
     	}
	reg1 = REG32(RNG_RESULTR);
	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG2 failed, wait RNG ready timeout\n");
			#endif
			sts = C_HOST_RNG_ERROR;
			break;
            	}
     	}
	reg2 = REG32(RNG_RESULTR);
	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG3 failed, wait RNG ready timeout\n");
			#endif
			sts = C_HOST_RNG_ERROR;
			break;
            	}
     	}
	reg3 = REG32(RNG_RESULTR);
	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG4 failed, wait RNG ready timeout\n");
			#endif
			sts = C_HOST_RNG_ERROR;
			break;
            	}
     	}
	reg4 = REG32(RNG_RESULTR);
	while ((REG32(RNG_RETURN3) & 0x1)==0)
        {
		retry_count++;
            if (retry_count > 0xff000) {
			#ifdef _DEBUG_CHAR_DRIVER
			sed_printf("get RNG5 failed, wait RNG ready timeout\n");
			#endif
			sts = C_HOST_RNG_ERROR;
			break;
            	}
     	}
	reg5 = REG32(RNG_RESULTR);

	GPIO_toggle();

#if _DEBUG_CHAR_DRIVER
	sed_printf("sed_cmd_char_host_rng1: 0x%08X\n", reg1);
	sed_printf("sed_cmd_char_host_rng2: 0x%08X\n", reg2);
	sed_printf("sed_cmd_char_host_rng3: 0x%08X\n", reg3);
	sed_printf("sed_cmd_char_host_rng4: 0x%08X\n", reg4);
	sed_printf("sed_cmd_char_host_rng5: 0x%08X\n", reg5);
#endif

	/* Transfer the result from internal register to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 4, reg2);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg3);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 12, reg4);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 16, reg5);

	GPIO_pulse();

	return sed_command_exit(obuf, C_HOST_RNG, (CHAR_CPU_INTERNAL_REGS << 2), sts);
}

