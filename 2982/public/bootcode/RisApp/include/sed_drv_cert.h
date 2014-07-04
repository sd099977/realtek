#ifndef __SED_DRV_CERT_H__
#define __SED_DRV_CERT_H__

#include "sed_drv_common.h"

#ifdef FPGA
#define CERT_REG_BASE	0xB8000000 //TODO: check base addr
#else
#define CERT_REG_BASE	0xb801D000

#endif

#define CERT_DATA_IN_0		(CERT_REG_BASE + 0x0)
#define CERT_DATA_IN_1  	(CERT_REG_BASE + 0x4)
#define CERT_DATA_IN_2  	(CERT_REG_BASE + 0x8)
#define CERT_DATA_IN_3  	(CERT_REG_BASE + 0xC)
#define CERT_DATA_IN_4  	(CERT_REG_BASE + 0x10)
#define CERT_DATA_IN_5  	(CERT_REG_BASE + 0x14)
#define CERT_DATA_IN_6  	(CERT_REG_BASE + 0x18)
#define CERT_DATA_IN_7  	(CERT_REG_BASE + 0x1C)
#define CERT_DATA_OUT_0  	(CERT_REG_BASE + 0x20)
#define CERT_DATA_OUT_1  	(CERT_REG_BASE + 0x24)
#define CERT_DATA_OUT_2  	(CERT_REG_BASE + 0x28)
#define CERT_DATA_OUT_3  	(CERT_REG_BASE + 0x2C)
#define CERT_DATA_OUT_4  	(CERT_REG_BASE + 0x30)
#define CERT_DATA_OUT_5  	(CERT_REG_BASE + 0x34)
#define CERT_DATA_OUT_6  	(CERT_REG_BASE + 0x38)
#define CERT_DATA_OUT_7  	(CERT_REG_BASE + 0x3C)
#define CERT_STATUS_AKL  	(CERT_REG_BASE + 0x40)
#define CERT_COMMAND  		(CERT_REG_BASE + 0x44)

/* NOCS3_IP_Block_NSR_Realtek_v010004.docx */
#define STS_KEYOUT_IF		0x2 //STATUS_AKL[1]: key output interface info
 
#if 0
void sed_cert_set_data_in (uint8 *buf, uint16 len);
void sed_cert_set_opcode (uint32 opcode);
void sed_cert_get_data_out (uint8 *buf, uint16 len);
#endif

#endif
