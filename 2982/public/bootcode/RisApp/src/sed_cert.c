#include "sed_common.h"
#include "sed_drv_cert.h"
#include "sed_drv_gpio.h"
#include "sed_drv_kt.h"

//#define CERT_COMMAND_EXCHANGE_DEBUG
#define CERT_CMD_BLOCK_LEN	37
#define CERT_CMD_DATA_IDX	0
#define CERT_CMD_OPCODE_IDX	32
#define CERT_CMD_PULSE_IDX	36
#define YES	0x01
#define NO	0x00
#define PRINT_ALL	0x11
#define PRINT_LAST	0x01
#define CLEAN		0x00

#ifndef SKIP_SED_FUNC
int sed_cmd_cert_exchange (uint8 *ibuf, uint8 *obuf) //TODO: implement operations
{
	uint8 numOfCmd = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX), i;
	uint8 numOfRun = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 1), j;
	uint8 showSts = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 2);
	uint8 showOut = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 3), k;
	//uint32 ramPos = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 4); // [Discard]
	uint16 curCmdIdx, rspDataLen = 0;
	uint32 status;
	uint32 odata[8];
	uint8 sts = CERT_NO_ERROR;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	for (j = 0; j < numOfRun; j++)
	{
		curCmdIdx = CMD_DATA_IN_IDX + 8;
		for (i = 0; i < numOfCmd; i++)
		{
			uint8 pulseFlag = get_cmd_data_uint8(ibuf, curCmdIdx + CERT_CMD_PULSE_IDX);

			REG32(CERT_DATA_IN_0) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX);
			REG32(CERT_DATA_IN_1) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x4);
			REG32(CERT_DATA_IN_2) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x8);
			REG32(CERT_DATA_IN_3) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0xC);
			REG32(CERT_DATA_IN_4) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x10);
			REG32(CERT_DATA_IN_5) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x14);
			REG32(CERT_DATA_IN_6) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x18);
			REG32(CERT_DATA_IN_7) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX+0x1C);

#ifdef CERT_COMMAND_EXCHANGE_DEBUG
			int z;
			sed_printf("CMD[%d]:\n", i);
			for (z = 0; z < 8; z++)
				sed_printf(" %08X ", get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_DATA_IDX + (z<<2)));
			sed_printf("\n");
#endif
			/* Fill OPCODE */
			REG32(CERT_COMMAND) = get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_OPCODE_IDX);

#ifdef CERT_COMMAND_EXCHANGE_DEBUG
			sed_printf(" OPCODE: %08X\n", get_cmd_data_uint32(ibuf, curCmdIdx + CERT_CMD_OPCODE_IDX));
#endif

			/* Trigger pulse if needed */
			if (pulseFlag)
				GPIO_pulse();

			/* Polling COMMAND[0] or timeout */
			while (REG32(CERT_COMMAND) & 0x1); //check 1 means busy or done

			/* Trigger pulse if needed */
			if (pulseFlag)
				GPIO_pulse();

			/* Retrive STATUS_AKL */
			status = REG32(CERT_STATUS_AKL);
			/* Check if output STATUS */
			if ((showSts == YES) || ((showSts == NO) && (i == (numOfCmd - 1)))) {
				set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + rspDataLen, status);
				rspDataLen += 4;
			}

			/* Retrive DATA_OUT */
			odata[0] = REG32(CERT_DATA_OUT_0);
			odata[1] = REG32(CERT_DATA_OUT_1);
			odata[2] = REG32(CERT_DATA_OUT_2);
			odata[3] = REG32(CERT_DATA_OUT_3);
			odata[4] = REG32(CERT_DATA_OUT_4);
			odata[5] = REG32(CERT_DATA_OUT_5);
			odata[6] = REG32(CERT_DATA_OUT_6);
			odata[7] = REG32(CERT_DATA_OUT_7);

			/* Check if output OUT_DATA */
			if ((showOut == PRINT_ALL) || ((showOut == PRINT_LAST) && (i == (numOfCmd - 1)))) {
				for (k = 0; k < 8; k++) {
					set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + rspDataLen, odata[k]);
					rspDataLen += 4;
				}
			}
			curCmdIdx += CERT_CMD_BLOCK_LEN;
		}
	}

	return sed_command_exit(obuf, C_CERT_EXCHANGE, rspDataLen, sts);
}

#define ODD		0x81
#define EVEN	0x80
int sed_cmd_set_cert_enc_key (uint8 *ibuf, uint8 *obuf) //TODO: implement operations
{
	uint8 algoId = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX);
	uint8 parity = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 1);
	uint32 status = 0;
	uint8 sts = SET_CERT_KEY_NO_ERROR;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check Parameter (EMI/Usage, parity) */
	sed_printf("AlgoID: %02X, Parity: %02X\n", algoId, parity);

	GPIO_pulse();

	/* Check if there is key pending on CERT bus */
#if defined (SIRIUS)
	status = REG32(CERT_STATUS_AKL);  //TODO: polling until true, or report error?
#endif
	if (!(status & STS_KEYOUT_IF)) {
		sts = SET_CERT_KEY_ERROR;
		goto done;
	}

	/* Set key table index & Fetch key and usage on CERT bus */
#if defined (SIRIUS)
	REG32(KT_WADR) = KT_CERT_KEY_IDX|KT_WADR_WT_EN;
#endif
	/* Wait until HW finish */
#if defined (SIRIUS)
	while(REG32(KT_WADR) & KT_WADR_WT_EN); //TODO: need timeout?
#endif
	GPIO_pulse();

done:
	return sed_command_exit(obuf, C_SET_CERT_ENCRYPT_KEY, 0, sts);
}

int sed_cmd_set_cert_dec_key (uint8 *ibuf, uint8 *obuf) //TODO: implement operations
{
	uint8 algoId = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX);
	uint8 parity = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 1);
	uint32 status = 0;
	uint8 sts = SET_CERT_KEY_NO_ERROR;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check Parameter (EMI/Usage, parity) */
	sed_printf("AlgoID: %02X, Parity: %02X\n", algoId, parity);

	GPIO_pulse();

	/* Check if there is key pending on CERT bus */
#if defined (SIRIUS)
	status = REG32(CERT_STATUS_AKL);  //TODO: polling until true, or report error?
#endif
	if (!(status & STS_KEYOUT_IF)) {
		sts = SET_CERT_KEY_ERROR;
		goto done;
	}

	/* Set key table index & Fetch key and usage on CERT bus */
#if defined (SIRIUS)
	REG32(KT_WADR) = KT_CERT_KEY_IDX|KT_WADR_WT_EN;
#endif
	/* Wait until HW finish */
#if defined (SIRIUS)
	while(REG32(KT_WADR) & KT_WADR_WT_EN); //TODO: need timeout?
#endif
	GPIO_pulse();

done:
	return sed_command_exit(obuf, C_SET_CERT_DECRYPT_KEY, 0, sts);
}

#endif //?#ifndef SKIP_SED_FUNC
