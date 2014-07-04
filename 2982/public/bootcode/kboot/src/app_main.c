/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description: test code for Sirius FPGA
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "sed_common.h"
#include "sed_setup.h"
#include "sed_cert.h"
#include "sed_r2r.h"
#include "sed_otp.h"
#include "sed_char.h"
#include "sed_rtk.h"
#include "sed_boot.h"
#include "sed_drv_uart.h"
#include "sed_drv_sfc.h"
#include "sed_drv_rng.h"
#include "sed_drv_gpio.h"
#include "sed_nand.h"
#include "malloc.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define LZMA_TEST
#define ENCRYPT_TEST

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
/* Command/Response buffer */
uint8 ibuf[IO_BUF_MAX_LEN];
uint8 obuf[IO_BUF_MAX_LEN];
uint8 visualize_print_disable = 1;

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void sed_init_config();
extern void get_flash_shared_semaphore(void);
extern void release_flash_shared_semaphore(void);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

#ifdef LZMA_TEST
#include "lzma_tools.h"

extern uint get_mem_layout_when_read_image(MEM_LAYOUT_WHEN_READ_IMAGE_T *mem_layout);

int lzma_test(void)
{
	SizeT decompressedSize;
	SizeT imageSize = 1762007;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;

	/* get memory layout before copy kernel image */
	mem_layout.bIsEncrypted = 0;
	mem_layout.bIsCompressed = 1;
	mem_layout.image_target_addr = (K_NORMAL_LINUX_ENTRY | MIPS_KSEG0BASE);

	get_mem_layout_when_read_image(&mem_layout);

	if (lzmaBuffToBuffDecompress(
		(unsigned char *)mem_layout.decompressed_addr,
		&decompressedSize,
		(unsigned char *)mem_layout.compressed_addr,
		imageSize) != 0)
	{
		sed_printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);
		return 1;
	}

	return 0;
}
#endif

int sed_cmd_handler (uint8 *ibuf, uint8 *obuf)
{
	uint32 rsp_len = 0;

	switch (get_cmd_cmd_type(ibuf)) {
#if 0
		case C_CHIP_RESET:
			sed_cmd_chip_rst(ibuf, obuf);
			break;
		case C_SET_CONFIG:
			rsp_len = sed_cmd_set_config(ibuf, obuf);
			break;
		case C_GET_CONFIG:
			rsp_len = sed_cmd_get_config(ibuf, obuf);
			break;
		case C_CERT_EXCHANGE:
			rsp_len = sed_cmd_cert_exchange(ibuf, obuf);
			break;
		case C_SET_CERT_ENCRYPT_KEY:
			rsp_len = sed_cmd_set_cert_enc_key(ibuf, obuf);
			break;
		case C_SET_CERT_DECRYPT_KEY:
			rsp_len = sed_cmd_set_cert_dec_key(ibuf, obuf);
			break;
		case C_R2R_CERT_KEY:
			rsp_len = sed_cmd_r2r_cert_key(ibuf, obuf);
			break;
		case C_R2R_HOST_KEY:
			rsp_len = sed_cmd_r2r_host_key(ibuf, obuf);
			break;
		case C_GET_NUID:
			rsp_len = sed_cmd_otp_get_nuid(ibuf, obuf);
			break;
		case C_SET_STBCASN:
			rsp_len = sed_cmd_otp_set_stbcasn(ibuf, obuf);
			break;
		case C_GET_STBCASN:
			rsp_len = sed_cmd_otp_get_stbcasn(ibuf, obuf);
			break;
		case C_SET_MSID:
			rsp_len = sed_cmd_otp_set_msid(ibuf, obuf);
			break;
		case C_GET_MSID:
			rsp_len = sed_cmd_otp_get_msid(ibuf, obuf);
			break;
		case C_HOST_OTP_DUMP:
			rsp_len = sed_cmd_otp_dump(ibuf, obuf);
			break;
		case C_HOST_OTP_READ:
			rsp_len = sed_cmd_otp_read(ibuf, obuf);
			break;
		case C_HOST_OTP_WRITE:
			rsp_len = sed_cmd_otp_write(ibuf, obuf);
			break;
		case C_HOST_READ:
			rsp_len = sed_cmd_char_host_read(ibuf, obuf);
			break;
		case C_HOST_WRITE:
			rsp_len = sed_cmd_char_host_write(ibuf, obuf);
			break;
		case C_HOST_READ_ITER:
			rsp_len = sed_cmd_char_host_read_iter(ibuf, obuf);
			break;
		case C_HOST_LINEAR:
			rsp_len = sed_cmd_char_host_linear(ibuf, obuf);
			break;
		case C_READ_INFINITE:
			rsp_len = sed_cmd_char_read_infinite(ibuf, obuf);
			break;
		case C_HOST_CONDITIONAL:
			rsp_len = sed_cmd_char_host_cond(ibuf, obuf);
			break;
		case C_GET_RANDOM:
			rsp_len = sed_cmd_char_get_rand(ibuf, obuf);
			break;
		case C_HOST_RNG:
			rsp_len = sed_cmd_char_host_rng(ibuf, obuf);
			break;
		case R_READ_REG:
			rsp_len = sed_cmd_rtk_reg_read(ibuf, obuf);
			break;
		case R_WRITE_REG:
			rsp_len = sed_cmd_rtk_reg_write(ibuf, obuf);
			break;
		case R_VISUALIZE_DEBUG:
			visualize_print_disable = ibuf[CMD_DATA_IN_IDX];
			rsp_len = -1;
			break;
#endif
		default:
			return -1;
	}

	return rsp_len;
}

#define CR	0x0D
#define LF	0x0A
int sed_command_receive (uint8 *ibuf)
{
	int ret, len = 0;
	uint8 ch;
	uint16 dLen = 0;

	while (1) {
		ret = sed_uart_read(&ch);
		if (ret == 0)
			ibuf[len++] = ch;
		if (len == 3)
			dLen = get_cmd_data_len(ibuf);

		if (len == (dLen + 3))
			break;
	}

	if (!visualize_print_disable) {
		sed_printf("Command(%d): ", len);
		sed_format_print(ibuf, len);
	}

	return len;
}

int sed_response_transfer (uint8 *obuf, uint16 len)
{
	uint16 i;

	if (!visualize_print_disable) {
		sed_printf("Response(%d):", len);
		sed_format_print(obuf, len);
	} else {
		for (i = 0; i < len; i++)
			sed_uart_write(&(obuf[i]));
	}

	return len;
}

int app_main(int argc, char **argv)
{
	int ret, i;
	void (*jump)(void);
	ulong malloc_start = (KCPU_BOOT_HEAP_START | MIPS_KSEG0BASE);
	ulong malloc_size = KCPU_BOOT_HEAP_SIZE;
	uint32 regAddr = KCPU_WAIT_JUMP_DUMMY_REG;
	uint32 regValue;

	sed_printf("--- kboot %s %s ---\n", __TIME__, __DATE__);
	sed_printf("--- heap start:0x%x size:%d K ---\n",
		malloc_start,
		malloc_size / 1024);

	/* Mem init */
	mem_malloc_init (malloc_start, malloc_size);

	//nand flash init
	get_flash_shared_semaphore();
	sed_nand_init();
	release_flash_shared_semaphore();

	while(1) {

		if (REG32(KCPU_WAIT_HW_SEM_REG) == 0x1) /* Wait for KCPU hw semaphore */
		{
			regValue = REG32(regAddr); /* Get dummy register for KCPU action */

			if (regValue == MAGIC_KCPU_OP_SETUP_NORMAL) /* Check if enter normal kernel */
			{
				sed_printf("Setup normal kernel:\n");

				ret = kboot_setup_kernel(); /* Read normal kernel */

				if (ret) {
					REG32(regAddr) = MAGIC_KCPU_ST_FAIL;
				}
				else {
					REG32(regAddr) = MAGIC_KCPU_ST_OK;
				}
			}
			else if (regValue == MAGIC_KCPU_OP_SETUP_RESCUE) /* Check if enter rescue kernel */
			{
				sed_printf("Setup rescue kernel:\n");

				ret = kboot_setup_rescue(); /* Read rescue */

				if (ret) {
					REG32(regAddr) = MAGIC_KCPU_ST_FAIL;
				}
				else {
					REG32(regAddr) = MAGIC_KCPU_ST_OK;
				}
			}
			else if (regValue == MAGIC_KCPU_OP_GO_NORMAL) /* Check if go normal linux */
			{
				sed_printf("Go normal linux:\n");

				ret = kboot_go_linux(); /* Prepare boot param and kernel command line */

				if (ret) {
					REG32(regAddr) = MAGIC_KCPU_ST_FAIL;
				}
				else {
					REG32(regAddr) = MAGIC_KCPU_ST_OK;
					jump = (void *)(K_NORMAL_LINUX_ENTRY | MIPS_KSEG0BASE);
					jump();
				}
			}
			else if (regValue == MAGIC_KCPU_OP_GO_RESCUE) /* Check if go rescue linux */
			{
				sed_printf("Go rescue linux:\n");

				ret = kboot_go_linux(); /* Prepare boot param and kernel command line */

				if (ret) {
					REG32(regAddr) = MAGIC_KCPU_ST_FAIL;
				}
				else {
					REG32(regAddr) = MAGIC_KCPU_ST_OK;
					jump = (void *)(K_RESCUE_LINUX_ENTRY | MIPS_KSEG0BASE);
					jump();
				}
			}
			else if (regValue == MAGIC_KCPU_TEST_DECRYPT)
			{
				sed_printf("decrypt_test removed.\n");
			}
			else if (regValue == MAGIC_KCPU_TEST_LZMA)
			{
				sed_printf("Lzma_test start:\n");

				ret = lzma_test();

				if (ret) {
					sed_printf("FAILED.\n");
				}
				else {
					sed_printf("PASS.\n");
				}
			}
			else
			{
				/* KCPU get hw semaphore but don't know what to do */
				sed_printf("FATAL ERROR. (unknown magic:%x)\n", regValue);
			}
		}

		for(i = 0;i < 1024;i++) /* Reduce rbus traffic */
			;

	}

	return -1;

}

