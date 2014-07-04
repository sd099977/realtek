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
#include "sed_drv_uart.h"
#include "sed_drv_sfc.h"
#include "sed_drv_rng.h"
#include "sed_drv_gpio.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
/* Command/Response buffer */
#ifndef SKIP_SED_FUNC
uint8 ibuf[IO_BUF_MAX_LEN];
uint8 obuf[IO_BUF_MAX_LEN];
#endif
uint8 visualize_print_disable = 1;


/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void sed_init_config();

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
#ifndef SKIP_SED_FUNC
int sed_cmd_handler (uint8 *ibuf, uint8 *obuf)
{
	uint32 rsp_len = 0;

	switch (get_cmd_cmd_type(ibuf)) {
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
#endif	//?#ifndef SKIP_SED_FUNC

#define MIS_REG_BASE		0xb801b000
/* Timer */
#define MIS_TCWCR		(MIS_REG_BASE + 0x6f0)

extern void testapp(void);
#define RTK_AUX_CODE_ENV "--- RTK AUX_Code Environment ---"
int app_main(int argc, char **argv)
{
	int ret, i;
	sed_printf0("\n%s_001\n",RTK_AUX_CODE_ENV);
	sed_printf1("\n%s_002\n",RTK_AUX_CODE_ENV);
	/* disable hw watchdog first */
	REG32(MIS_TCWCR) = 0xa5;

	/* HW init */
	//sed_uart_init();

	//sed_sfc_init();

	//sed_ddr_init();

	/* Read CLK setting from persistent memory and apply */
	//sed_init_config();

	sed_printf0("\n%s1\n",RTK_AUX_CODE_ENV);
	sed_printf1("\n%s2\n",RTK_AUX_CODE_ENV);

	/* Step 0: chipset reset post process */
	//sed_cmd_chip_rst_post();
	sed_printf0("%s(%d)\n",__func__,__LINE__);
	//sed_printf("--- SED post done ---\n");

	/* HW init */
	//sed_rng_init();
	sed_printf0("%s(%d)\n",__func__,__LINE__);

	sed_gpio_init();
	sed_printf0("%s(%d)\n",__func__,__LINE__);
	testapp();

#ifndef SKIP_SED_FUNC
	while (1) {
		/* Step 1: Receive command */
		for (i = 0; i < IO_BUF_MAX_LEN; i++)
			ibuf[i] = 0;
		ret = sed_command_receive(ibuf);

		if (ret <= 0)
			continue;

		/* Step 2: Command handler */
		ret = sed_cmd_handler(ibuf, obuf);
		if (ret < 0)
			continue;

		/* Step 3: Transfer response */
		sed_response_transfer(obuf, ret);
	}
#endif	//?#ifndef SKIP_SED_FUNC
	return -1;

}

