/************************************************************************
 *
 *  otp_info.h
 *
 *  Public header file for Nike OTP info
 *
 ************************************************************************/
#ifndef OTP_INFO_H
#define OTP_INFO_H

/************************************************************************
 *  Definition
 ************************************************************************/
//sirius
#define OTP_BIT_NUM            7168		//sirius OTP bits size
#define OTP_SIZE               (OTP_BIT_NUM / 8)

#define BIT_OFFSET(number)     ((number / 32) * 4)	// register offset of input OTP bit number
#define BIT_SHIFT(number)      (number % 32)		// register shift of input OTP bit number

#define LEN_64BIT	       (64 / 8)
#define LEN_128BIT	       (128 / 8)
#define LEN_552BIT	       (552 / 8)
#define LEN_2048BIT	       (2048 / 8)

#define OTP_UNREADABLE_START	2048
#define OTP_UNREADABLE_END	3007
/************************************************************************
 *  Public functions
 ************************************************************************/

#endif /* #ifndef OTP_INFO_H */

