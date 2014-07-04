#ifndef __OTP_DEBUG_H__
#define __OTP_DEBUG_H__

//#define OTP_DBG_EN
#ifdef OTP_DBG_EN
#define OTP_DBG(fmt, args...)          printf("[OTP][DBG]" fmt, ##args)
#else
#define OTP_DBG(fmt, args...)
#endif

#define OTP_WARNING(fmt, args...)      printf("[OTP][WARNING]" fmt, ##args)

#endif  // __OTP_DEBUG_H__