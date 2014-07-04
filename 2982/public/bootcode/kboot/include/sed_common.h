#ifndef __SED_H__
#define __SED_H__

#include <stdio.h>
#include "sed_types.h"

#define SED_DEBUG
#define SED_USE_FUNC

#ifdef SED_DEBUG
#define sed_printf(...)	printf(__VA_ARGS__)
#else
#define sed_printf(...)	do{}while(0)
#endif

/* Buffer length */
#define IO_BUF_MAX_LEN  512

/* Command index define */
#define CMD_CMD_TYPE_IDX	0
#define CMD_DATA_LEN_H_IDX	1
#define CMD_DATA_LEN_L_IDX	2
#define CMD_DATA_IN_IDX		3

#ifndef SED_USE_FUNC
#define get_cmd_cmd_type(ibuf)	ibuf[CMD_CMD_TYPE_IDX]
#define get_cmd_data_len(ibuf)	(((uint16)(ibuf[CMD_DATA_LEN_H_IDX])<<8)|ibuf[CMD_DATA_LEN_L_IDX])
#define get_cmd_data_uint8(ibuf,ofs) ibuf[ofs]
#define get_cmd_data_uint32(ibuf,ofs)	\
	(((uint32)(ibuf[ofs])<<24)|((uint32)(ibuf[ofs+1])<<16)|	\
	((uint32)(ibuf[ofs+2])<<8)|(ibuf[ofs+3]&0xFF))
#define get_cmd_data_addr64(ibuf,ofs)   \
	(((addr64)(ibuf[ofs])<<56)|((addr64)(ibuf[ofs+1])<<48)| \
	((addr64)(ibuf[ofs+2])<<40)|((addr64)(ibuf[ofs+3])<<32)| \
	((addr64)(ibuf[ofs+4])<<24)|((addr64)(ibuf[ofs+5])<<16)| \
	((addr64)(ibuf[ofs+6])<<8)|(ibuf[ofs+7]&0xFF))
#endif

/* Response index define */
#define RSP_CMD_ACK1_IDX	0
#define RSP_DATA_LEN_H_IDX	1
#define RSP_DATA_LEN_L_IDX	2
#define RSP_CMD_ACK2_IDX	3
#define RSP_CMD_STAS_IDX	4
#define RSP_DATA_OUT_IDX	5

#ifndef SED_USE_FUNC
#define set_rsp_cmd_ack1(obuf,ack)	obuf[RSP_CMD_ACK1_IDX]=ack
#define set_rsp_cmd_ack2(obuf,ack)	obuf[RSP_CMD_ACK2_IDX]=ack
#define set_rsp_data_len(obuf,len)	\
	do{	\
		obuf[RSP_DATA_LEN_H_IDX]=((len)>>8)&0xFF;	\
		obuf[RSP_DATA_LEN_L_IDX]=(len)&0xFF;	\
	}while(0)
#define set_rsp_data_uint8(obuf,ofs,val) obuf[ofs]=val
#define set_rsp_data_uint32(obuf,ofs,val)	\
	do{	\
		obuf[ofs]=((val)>>24)&0xFF;	\
		obuf[ofs+1]=((val)>>16)&0xFF; \
		obuf[ofs+2]=((val)>>8)&0xFF; \
		obuf[ofs+3]=(val)&0xFF;	\
	}while(0)
#define set_rsp_data_addr64(obuf,ofs,val)	\
	do{	\
		obuf[ofs]=((val)>>56)&0xFF;	\
		obuf[ofs+1]=((val)>>48)&0xFF; \
		obuf[ofs+2]=((val)>>40)&0xFF; \
		obuf[ofs+3]=((val)>>32)&0xFF; \
		obuf[ofs+4]=((val)>>24)&0xFF; \
		obuf[ofs+5]=((val)>>16)&0xFF; \
		obuf[ofs+6]=((val)>>8)&0xFF; \
		obuf[ofs+7]=(val)&0xFF;	\
	}while(0)
#define set_rsp_cmd_stas(obuf,sts)	obuf[RSP_CMD_STAS_IDX]=sts
#define set_rsp_xor_chek(obuf,len,val)	obuf[RSP_DATA_LEN_H_IDX+len]=val
#define get_rsp_xor_indx(len)	(RSP_DATA_LEN_H_IDX+len)
#endif

/* Command define */
#define C_CHIP_RESET			0xB3
#define C_SET_CONFIG			0x80
#define C_GET_CONFIG			0x81
#define C_CERT_EXCHANGE			0x90
#define C_SET_CERT_ENCRYPT_KEY	0x91
#define C_SET_CERT_DECRYPT_KEY	0x92
#define C_R2R_CERT_KEY			0x93
#define C_R2R_HOST_KEY			0x94
#define C_GET_NUID				0xA0
#define C_SET_STBCASN			0xA2
#define C_GET_STBCASN			0xA3
#define C_SET_MSID				0xA4
#define C_GET_MSID				0xA5
#define C_HOST_OTP_DUMP			0xA1
#define C_HOST_OTP_READ			0xA6
#define C_HOST_OTP_WRITE		0xA7
#define C_HOST_READ				0xA8
#define C_HOST_WRITE			0xA9
#define C_HOST_READ_ITER		0xAA
#define C_HOST_LINEAR			0xAD
#define C_READ_INFINITE			0xAB
#define C_HOST_CONDITIONAL		0xAE
#define C_GET_RANDOM			0xB1
#define C_HOST_RNG				0xB2

/* RTK commands */
#define R_READ_REG			0xE1
#define R_WRITE_REG		0xE2
#define R_VISUALIZE_DEBUG	0xE3


/* Return value define */
#define C_SET_CONFIG_OK				0xAA
#define C_SET_CONFIG_PARAM_ERROR	0xBB
#define C_SET_CONFIG_ERROR			0x55
#define C_GET_CONFIG_OK				0xAA
#define C_GET_CONFIG_ERROR			0x55
#define CERT_ERROR_INVALID_PARAM	0x99
#define CERT_NO_ERROR				0xAA
#define CERT_ERROR_TIMEOUT			0x77
#define CERT_ERROR					0x55
#define SET_CERT_KEY_ERROR_INVALID_PARAM	0x99
#define SET_CERT_KEY_NO_ERROR		0xAA
#define SET_CERT_KEY_ERROR_BAD_EMI	0x77
#define SET_CERT_KEY_ERROR_BAD_USAGE		0x33
#define SET_CERT_KEY_ERROR			0x55
#define R2R_NO_ERROR				0xAA
#define R2R_ERROR_INVALID_PARAM		0x99
#define R2R_ERROR_OPERATION_NOT_SUPPORTED	0xBB
#define R2R_ERROR					0x55
#define NUID_READ_OK				0xAA
#define NUID_READ_ERROR				0x55
#define OTP_WRITE_INVALID_PARAM		0x77
#define OTP_WRITE_OK				0xAA
#define OTP_WRITE_NOT_ALLOWED		0x99
#define OTP_WRITE_ERROR				0x55
#define OTP_READ_OK					0xAA
#define OTP_READ_ERROR				0x55
#define C_HOST_READ_OK				0xAA
#define C_HOST_READ_ADDR_NOT_ALLOW	0x99
#define C_HOST_READ_ADDR_OUT_RANGE	0x77
#define C_HOST_READ_ERROR			0x55
#define C_HOST_WRITE_INVALID_PARAM	0x77
#define C_HOST_WRITE_OK				0xAA
#define C_HOST_WRITE_NOT_ALLOWED	0x99
#define C_HOST_WRITE_ERROR			0x55
#define C_HOST_LINEAR_OK			0xAA
#define C_HOST_LINEAR_ERROR			0x55
#define C_HOST_INFINITE_ERROR		0x55
#define C_HOST_COND_OK				0xAA
#define C_HOST_COND_ERROR			0x55
#define C_GET_RANDOM_OK				0xAA
#define C_GET_RANDOM_ERROR			0x55
#define C_HOST_RNG_OK				0xAA
#define C_HOST_RNG_ERROR			0x55

/* Function prototype */
void sed_command_entry (uint8 *obuf, uint16 len);
int sed_command_exit (uint8 *obuf, uint8 ack, uint16 dlen, uint8 sts);
void GPIO_reset (void);
void GPIO_toggle (void);
void GPIO_pulse (void);
void sed_format_print (uint8 *buf, uint16 len);

#ifdef SED_USE_FUNC
#define get_cmd_cmd_type(ibuf)	ibuf[CMD_CMD_TYPE_IDX]
uint16 get_cmd_data_len(uint8 *ibuf);
#define get_cmd_data_uint8(ibuf,ofs) ibuf[ofs]
uint32 get_cmd_data_uint32(uint8 *ibuf, uint32 ofs);
addr64 get_cmd_data_addr64(uint8 *ibuf, uint32 ofs);

#define set_rsp_cmd_ack1(obuf,ack)	obuf[RSP_CMD_ACK1_IDX]=ack
#define set_rsp_cmd_ack2(obuf,ack)	obuf[RSP_CMD_ACK2_IDX]=ack
void set_rsp_data_len(uint8 *obuf, uint16 len);
#define set_rsp_data_uint8(obuf,ofs,val) obuf[ofs]=val
void set_rsp_data_uint32(uint8 *obuf, uint32 ofs, uint32 val);
void set_rsp_data_addr64(uint8 *obuf, uint32 ofs, addr64 val);
#define set_rsp_cmd_stas(obuf,sts)	obuf[RSP_CMD_STAS_IDX]=sts
#define set_rsp_xor_chek(obuf,len,val)	obuf[RSP_DATA_LEN_H_IDX+len]=val
#define get_rsp_xor_indx(len)	(RSP_DATA_LEN_H_IDX+len)
#endif

#endif
