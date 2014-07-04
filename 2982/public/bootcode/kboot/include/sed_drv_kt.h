#ifndef __SED_DRV_KT_H__
#define __SED_DRV_KT_H__

#include "sed_drv_common.h"

#define KT_REG_BASE		0xB8035800

#define KT_CTRL			(KT_REG_BASE + 0x0)
#define KT_WADR			(KT_REG_BASE + 0x4)
#define KT_KEYCOPY		(KT_REG_BASE + 0x8)
#define KT_HOSTKEY1		(KT_REG_BASE + 0xC)
#define KT_HOSTKEY2     (KT_REG_BASE + 0x10)
#define KT_HOSTKEY3     (KT_REG_BASE + 0x14)
#define KT_HOSTKEY4     (KT_REG_BASE + 0x18)
#define KT_HTKEY_USAGE	(KT_REG_BASE + 0x30)
#define KT_RDKEY_USAGE	(KT_REG_BASE + 0x34)

/* Register bit define */
#define KT_WADR_WT_EN       	0x100   //KT_WADR[8]

#define KT_HTKEY_USAGE_CE_AES	0x0     //KT_KTKEY_USAGE[0:2]
#define KT_HTKEY_USAGE_CE_TDES	0x1
#define KT_HTKEY_USAGE_CE_CSAV3	0x5
#define KT_HTKEY_USAGE_CE_CSAV2	0x6
#define KT_HTKEY_USAGE_KS_64	0x0     //KT_KTKEY_USAGE[3]
#define KT_HTKEY_USAGE_KS_128	0x8
#define KT_HTKEY_USAGE_ENC		0x10    //KT_KTKEY_USAGE[4]
#define KT_HTKEY_USAGE_DEC      0x20    //KT_KTKEY_USAGE[5]
#define KT_HTKEY_USAGE_VALID	0x100   //KT_KTKEY_USAGE[8]

#define KT_RDKEY_USAGE_CE_AES	0x0     //KT_RDKEY_USAGE[0:2]
#define KT_RDKEY_USAGE_CE_TDES	0x1
#define KT_RDKEY_USAGE_CE_ASA	0x4
#define KT_RDKEY_USAGE_CE_CSAV3	0x5
#define KT_RDKEY_USAGE_CE_CSAV2	0x6
#define KT_RDKEY_USAGE_ENC		0x10    //KT_RDKEY_USAGE[4]
#define KT_RDKEY_USAGE_DEC		0x00
#define KT_RDKEY_USAGE_AES_ECB	0x00    //KT_RDKEY_USAGE[5:6]
#define KT_RDKEY_USAGE_TDES_ECB	0x00    //KT_RDKEY_USAGE[7]
#define KT_RDKEY_USAGE_EN		0x10000 //KT_RDKEY_USAGE[16]

/* Key table index for CERT/Host Key (Not specify in SED Spec, can be defined by us) */
#define KT_CERT_KEY_IDX		0x0
#define KT_HOST_KEY_IDX		0x1

#define KT_RDKEY_USAGE_CERT_KEY_IDX		(KT_CERT_KEY_IDX << 8)
#define KT_RDKEY_USAGE_HOST_KEY_IDX     (KT_HOST_KEY_IDX << 8)

#endif
