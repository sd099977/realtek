#ifndef __OTP_UTIL_H__
#define __OTP_UTIL_H__

typedef struct
{
    unsigned int  ofst;
    unsigned char   msb;
    unsigned char   lsb;
}OTP_PARAM;

int otp_write_bits( unsigned int ofst,
                    unsigned char msb,unsigned char lsb,
                    unsigned int val );
int otp_read_bits( unsigned int ofst,
                   unsigned char msb,unsigned char lsb,
                   unsigned int* pval );

#define otp_read_ex(otp_parm, pval) \
            otp_read_bits(otp_parm.ofst, otp_parm.msb, otp_parm.lsb, pval)
#define otp_write_ex(otp_parm, val) \
            otp_write_bits(otp_parm.ofst, otp_parm.msb, otp_parm.lsb, val)


#endif  // __OTP_UTIL_H__