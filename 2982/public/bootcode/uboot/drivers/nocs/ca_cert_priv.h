#ifndef __CA_CERT_PRIV_H__
#define __CA_CERT_PRIV_H__


#define WRITE_REG32(addr, val)      rtd_outl(addr, val);
#define READ_REG32(addr)            rtd_inl(addr)

#define CERT_REG_BASE               0xb801D000
#define CERT_REG_DATA_IN(x)         (CERT_REG_BASE + (x <<2))
#define CERT_REG_DATA_OUT(x)        (CERT_REG_BASE + 0x20 + (x <<2))
#define CERT_REG_STATUS_AKL         (CERT_REG_BASE + 0x40)
    #define CERT_STATUS_AKL_CERT_IP_ERROR           (0x1)
    #define CERT_STATUS_AKL_KEY_OUTPUT_PENDING      (0x1<<1)
    #define CERT_STATUS_AKL_OTP_RECORD1_LOCKED      (0x1<<2)
    #define CERT_STATUS_AKL_OTP_RECORD1_PROGRAMMED  (0x1<<3)
    #define CERT_STATUS_AKL_OTP_RECORD1_AUTHENTICATION_PASSED   (0x1<<4)

    #define CERT_STATUS_AKL_OTP_RECORD2_LOCKED      (0x1<<5)
    #define CERT_STATUS_AKL_OTP_RECORD2_PROGRAMMED  (0x1<<6)
    #define CERT_STATUS_AKL_OTP_RECORD2_AUTHENTICATION_PASSED   (0x1<<7)

    #define CERT_STATUS_AKL_OTP_RECORD3_LOCKED      (0x1<<8)
    #define CERT_STATUS_AKL_OTP_RECORD3_PROGRAMMED  (0x1<<9)
    #define CERT_STATUS_AKL_OTP_RECORD3_AUTHENTICATION_PASSED   (0x1<<10)

    #define CERT_STATUS_AKL_OTP_RECORD4_LOCKED      (0x1<<11)
    #define CERT_STATUS_AKL_OTP_RECORD4_PROGRAMMED  (0x1<<12)
    #define CERT_STATUS_AKL_OTP_RECORD4_AUTHENTICATION_PASSED   (0x1<<13)

#define CERT_REG_COMMAND            (CERT_REG_BASE + 0x44)
    #define CERT_COMMAND_START                      (0x1)
    #define CERT_COMMAND_BUSY                       (0x1)
    #define CERT_COMMAND_TOKEN(x)                   ((x & 0x7FFFFFFF)<<1)
#define CERT_REG_INTERRUPT          (CERT_REG_BASE + 0x48)

#define SET_CERT_DATA_IN(i, val)        WRITE_REG32(CERT_REG_DATA_IN(i), val)
#define SET_CERT_COMMAND(val)           WRITE_REG32(CERT_REG_COMMAND, val)
#define GET_CERT_DATA_OUT(i)            READ_REG32(CERT_REG_DATA_OUT(i))
#define GET_CERT_STATUS_AKL()           READ_REG32(CERT_REG_STATUS_AKL)
#define GET_CERT_COMMAND()              READ_REG32(CERT_REG_COMMAND)
#define GET_CERT_INTERRUPT()            READ_REG32(CERT_REG_INTERRUPT)

#define B4TOL(b0, b1, b2, b3)      ((b0<<24) + (b1<<16) + (b2<<8) + b3)

#endif /* __CA_CERT_PRIV_H__ */

