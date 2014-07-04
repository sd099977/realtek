#ifndef __OTP_UTIL_H__
#define __OTP_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned short  ofst;
    unsigned char   msb;
    unsigned char   lsb;
}OTP_PARAM;

extern int otp_read(unsigned int ofst, unsigned int* pval);
extern int otp_write(unsigned int ofst, unsigned int val);

extern int otp_read_bits(unsigned int ofst, unsigned char msb, unsigned char lsb, unsigned int* pval);
extern int otp_write_bits(unsigned int ofst, unsigned char msb, unsigned char lsb, unsigned int val);

#define otp_read_ex(otp_parm, pval)   otp_read_bits(otp_parm.ofst, otp_parm.msb, otp_parm.lsb, pval)

#define otp_write_ex(otp_parm, val)   otp_write_bits(otp_parm.ofst, otp_parm.msb, otp_parm.lsb, val)

#ifdef __cplusplus
}
#endif

#endif  // __OTP_UTIL_H__