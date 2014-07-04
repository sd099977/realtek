#ifndef __OTP_H__
#define __OTP_H__

#define OTP_BASE		0xB8017000
#define DP_NUID_H_REG   0xB8017A14
#define DP_NUID_L_REG   0xB8017A10

#define OTP_STBCASN		(OTP_BASE + 0x21C) // bit 4320 ~ 4351
#define OTP_MSID		(OTP_BASE + 0x270) // bit 4992 ~ 5023

#endif  //?#ifndef __OTP_H__
