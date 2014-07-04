#include "sed_common.h"
#include "sed_drv_otp.h"
#include "sed_drv_gpio.h"
#include "otp_util.h"

const OTP_PARAM OTP_StbCaSnRef32              = {0x21C, 31,  0};
const OTP_PARAM OTP_StbCaSnRef32Lock          = {0x220,  0,  0};
const OTP_PARAM OTP_MsidRef                   = {0x270, 31,  0};
const OTP_PARAM OTP_MsidRefLock               = {0x274,  0,  0};

#define OTP_NUID_LEN	8
int sed_cmd_otp_get_nuid (uint8 *ibuf, uint8 *obuf)
{
	uint8 sts = NUID_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Read NUID and store in response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, REG32(DP_NUID_H_REG));
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 4, REG32(DP_NUID_L_REG));

	GPIO_pulse();

	return sed_command_exit(obuf, C_GET_NUID, OTP_NUID_LEN, sts);
}


int sed_cmd_otp_set_stbcasn (uint8 *ibuf, uint8 *obuf)
{
	uint32 stbcasn = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX);
	uint32 val;
	uint8  sts = OTP_WRITE_OK;
	uint32 ret;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check input parameters */

	GPIO_pulse();

	/* Write STBCASN to OTP */
	ret = otp_read_ex(OTP_StbCaSnRef32Lock, &val);

	if (ret) {
		sts = OTP_WRITE_ERROR;
		goto final;
	}

	if (val==0) {
		if (otp_write_ex(OTP_StbCaSnRef32, stbcasn)) {
			sts =  OTP_WRITE_ERROR;
		}
	} else {
		//        sed_printf("write STB serial number failed, STB_CA_SN is locked\n");
		sts = OTP_WRITE_NOT_ALLOWED;
	}

final:
	GPIO_pulse();

	return sed_command_exit(obuf, C_SET_STBCASN, 0, sts);
}



#define OTP_STBCASN_LEN	4
int sed_cmd_otp_get_stbcasn (uint8 *ibuf, uint8 *obuf)
{
	uint32 stbcasn = 0;
	uint8 sts = OTP_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Get STBCASN from OTP */
	otp_read_ex(OTP_StbCaSnRef32, &stbcasn);

	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, stbcasn);

	GPIO_pulse();

	return sed_command_exit(obuf, C_GET_STBCASN, OTP_STBCASN_LEN, sts);
}

int sed_cmd_otp_set_msid (uint8 *ibuf, uint8 *obuf)
{
	uint32 msid = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX);
	uint32 msid_lock, ret;
	uint8 sts = OTP_WRITE_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check input parameters */

     //  sed_printf("MSID: 0x%08X\n", msid);

	GPIO_pulse();

	/* Write MSID to OTP */

	ret = otp_read_ex(OTP_MsidRefLock, &msid_lock);

	if (ret) {
		sts = OTP_WRITE_ERROR;
		goto final;
	}

	if (msid_lock) {
		//   sed_printf("set market segment id failed, MSID is locked\n");
		sts = OTP_WRITE_NOT_ALLOWED;
	} else {
        	if (otp_write_ex(OTP_MsidRef, msid)) {
			sts = OTP_WRITE_ERROR;
        	}
    	}

final:
	GPIO_pulse();

	return sed_command_exit(obuf, C_SET_MSID, 0, sts);
}

#define OTP_MSID_LEN	4
int sed_cmd_otp_get_msid (uint8 *ibuf, uint8 *obuf)
{
	uint32 msid;
	uint8 sts = OTP_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	GPIO_pulse();

	/* Get MSID from OTP */
	otp_read_ex(OTP_MsidRef, &msid);

	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, msid);

	GPIO_pulse();

	return sed_command_exit(obuf, C_GET_MSID, OTP_MSID_LEN, sts);
}

int sed_cmd_otp_dump (uint8 *ibuf, uint8 *obuf)
{
	uint16 dLen = get_cmd_data_len(ibuf);
	uint32 offset = (uint32) get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX + (dLen - 9));
	uint8 numWord = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + dLen - 1), i;
	uint8 sts = OTP_READ_OK;
	uint32 val;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Read numWord OTP value starting from offset */
	//sed_printf("Addr: 0x%08X, numWord: %d\n", offset, numWord);

	if (offset & 0x3) {
   //     sed_printf("sed_cmd_otp_dump failed, addr should be 4 bytes align\n");
		sts = OTP_READ_ERROR;
	} else {
		for (i = 0; i < numWord; i++) {
			otp_read(offset+(i<<2), &val);
			set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + (i << 2), val);
		}
	}

	/* Need EDC ??? */ // [Discard]

	return sed_command_exit(obuf, C_HOST_OTP_DUMP, (numWord << 2), sts);
}



#define OTP_CPU_INTERNAL_REGS	5
int sed_cmd_otp_read (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2, reg3, reg4, reg5;
	uint16 dLen = get_cmd_data_len(ibuf);
	addr64 offset = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX + (dLen - 8));
	volatile uint32 *ptr = (volatile uint32 *)(OTP_BASE + (uint32)offset);
	uint8 sts = OTP_READ_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	//sed_printf("Addr: 0x%08X\n", (uint32)ptr);

	GPIO_pulse();   // This GPIO is used for OTP read time measurement

	/* Read OTP values to internal registers (linear) */
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

	GPIO_pulse();   // This GPIO is used for OTP read time measurement

	/* Copy from internal registers to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 4, reg2);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg3);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 12, reg4);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 16, reg5);

	GPIO_toggle();

	return sed_command_exit(obuf, C_HOST_OTP_READ, (OTP_CPU_INTERNAL_REGS << 2), sts);
}

int sed_cmd_otp_write (uint8 *ibuf, uint8 *obuf)
{
	register uint32 reg1, reg2, reg3, reg4, reg5;
	uint16 dLen = get_cmd_data_len(ibuf);
	uint16 oLen = dLen - (OTP_CPU_INTERNAL_REGS << 2); // len of offset
	addr64 offset = get_cmd_data_addr64(ibuf, CMD_DATA_IN_IDX + (oLen - 8));
	volatile uint32 *ptr = (volatile uint32 *)(OTP_BASE + (uint32)offset);
	uint8 sts = OTP_WRITE_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Check input parameters */
	reg1 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + oLen);
	reg2 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + oLen + 4);
	reg3 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + oLen + 8);
	reg4 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + oLen + 12);
	reg5 = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + oLen + 16);

	//sed_printf("Addr: 0x%08X\n", (uint32)ptr);

	GPIO_pulse();

	/* Write input values into OTP offset */
	otp_write((uint32)offset,      reg1);
	otp_write((uint32)offset+0x4,  reg2);
	otp_write((uint32)offset+0x8,  reg3);
	otp_write((uint32)offset+0xC,  reg4);
	otp_write((uint32)offset+0x10, reg5);

	/* How to know has been programmed??? */

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

	GPIO_pulse();

	/* Read OTP values to internal registers */
	ptr = (volatile uint32 *)(OTP_BASE + (uint32)offset);

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

	GPIO_toggle();

	/* Copy from internal registers to response */
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX, reg1);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 4, reg2);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 8, reg3);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 12, reg4);
	set_rsp_data_uint32(obuf, RSP_DATA_OUT_IDX + 16, reg5);

	GPIO_toggle();

	return sed_command_exit(obuf, C_HOST_OTP_WRITE, (OTP_CPU_INTERNAL_REGS << 2), sts);
}

