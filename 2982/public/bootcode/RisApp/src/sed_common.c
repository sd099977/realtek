#include "sed_common.h"
#include "sed_drv_gpio.h"

void sed_command_entry (uint8 *obuf, uint16 len)
{
#ifndef SKIP_SED_FUNC
	uint16 i;

	/* Set GPIO to 0 */
	GPIO_reset();

	/* Initialize output buffer */
	for (i = 0; i < len; i++)
		obuf[i] = i;
#endif
}

int sed_command_exit (uint8 *obuf, uint8 ack, uint16 dlen, uint8 sts)
{

	uint8 val = 0;
	uint16 len = dlen + 4, i;
#ifndef SKIP_SED_FUNC
	/* Format response */
	set_rsp_cmd_ack1(obuf,ack);
	set_rsp_cmd_ack2(obuf,ack);
	set_rsp_data_len(obuf,len);
	set_rsp_cmd_stas(obuf,sts);

	/* Compute XOR check */
	for (i = 0; i < get_rsp_xor_indx(len); i++)
		val ^= obuf[i];

	set_rsp_xor_chek(obuf,len,val);
#endif
	return len + 3; // sizeof(len + ack1) = 3

}

void sed_format_print (uint8 *buf, uint16 len)
{
#ifndef SKIP_SED_FUNC
	uint16 i;

	for (i = 0; i < len; i++) {
		if (i && !(i % 16))
			sed_printf("\n");
		sed_printf(" %02X ", buf[i]);
	}
	if (len)
		sed_printf("\n");

	return;
#endif
}

#ifdef SED_USE_FUNC
uint16 get_cmd_data_len(uint8 *ibuf)
{
	return (((uint16)(ibuf[CMD_DATA_LEN_H_IDX])<<8)|ibuf[CMD_DATA_LEN_L_IDX]);
}

uint32 get_cmd_data_uint32(uint8 *ibuf, uint32 ofs)
{
	return (((uint32)(ibuf[ofs])<<24)|((uint32)(ibuf[ofs+1])<<16)|
			((uint32)(ibuf[ofs+2])<<8)|(ibuf[ofs+3]&0xFF));
}

addr64 get_cmd_data_addr64(uint8 *ibuf, uint32 ofs)
{
	return (((addr64)(ibuf[ofs])<<56)|((addr64)(ibuf[ofs+1])<<48)|
			((addr64)(ibuf[ofs+2])<<40)|((addr64)(ibuf[ofs+3])<<32)|
			((addr64)(ibuf[ofs+4])<<24)|((addr64)(ibuf[ofs+5])<<16)|
			((addr64)(ibuf[ofs+6])<<8)|(ibuf[ofs+7]&0xFF));
}

void set_rsp_data_len(uint8 *obuf, uint16 len)
{
	obuf[RSP_DATA_LEN_H_IDX]=((len)>>8)&0xFF;
	obuf[RSP_DATA_LEN_L_IDX]=(len)&0xFF;
}

void set_rsp_data_uint32(uint8 *obuf, uint32 ofs, uint32 val)
{
	obuf[ofs]=((val)>>24)&0xFF;
	obuf[ofs+1]=((val)>>16)&0xFF;
	obuf[ofs+2]=((val)>>8)&0xFF;
	obuf[ofs+3]=(val)&0xFF;
}

void set_rsp_data_addr64(uint8 *obuf, uint32 ofs, addr64 val)
{
	obuf[ofs]=((val)>>56)&0xFF;
	obuf[ofs+1]=((val)>>48)&0xFF;
	obuf[ofs+2]=((val)>>40)&0xFF;
	obuf[ofs+3]=((val)>>32)&0xFF;
	obuf[ofs+4]=((val)>>24)&0xFF;
	obuf[ofs+5]=((val)>>16)&0xFF;
	obuf[ofs+6]=((val)>>8)&0xFF;
	obuf[ofs+7]=(val)&0xFF;
}
#endif
