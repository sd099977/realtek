#ifndef __SED_DRV_OTP_H__
#define __SED_DRV_OTP_H__

#if defined (FPGA)
#define OTP_BASE		0x81000000
#define DP_NUID_H_REG   0x81000000
#define DP_NUID_L_REG   0x81000000

#elif defined (SIRIUS)
#define OTP_BASE		0xB8017000
//#define DP_NUID_H_REG   0xB8017A14
//#define DP_NUID_L_REG   0xB8017A10
#define DP_NUID_H_REG   0xB8017B00
#define DP_NUID_L_REG   0xB8017B04
#define DP_NUID2_H_REG   0xB8017B08
#define DP_NUID2_L_REG   0xB8017B0C

#else
uint32 fakeRAM[64] = {0};
#define OTP_BASE		(uint32)fakeRAM
#define DP_NUID_H_REG	(uint32)fakeRAM
#define DP_NUID_L_REG	(uint32)fakeRAM
#endif

#define OTP_STBCASN		(OTP_BASE + 0x21C) // bit 4320 ~ 4351
#define OTP_MSID		(OTP_BASE + 0x270) // bit 4992 ~ 5023

#endif
