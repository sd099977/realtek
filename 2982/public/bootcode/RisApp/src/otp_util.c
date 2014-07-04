#include <sysdefs.h>
#include "sed_common.h"
#include "sed_drv_common.h"
#include "otp_util.h"
#include "otp_reg.h"
#include "otp_debug.h"

#if 1
#define WRITE_REG32(addr, val)      do { REG32(addr) = val; }while(0)
#define READ_REG32(addr)            REG32(addr)
#else

void WRITE_REG32(unsigned int addr, unsigned int val)
{
    printf("[OTP][REG] WR[%08lx]=%08lx\n", addr, val);
    REG32(addr) = val;
}

unsigned int READ_REG32(unsigned int addr)
{
    unsigned int value = REG32(addr);
    printf("[OTP][REG] RD[%08lx]=%08lx\n", addr, value );
    return value;
}

#endif

void otp_udelay(unsigned int us)
{
    int i;
    while(us--)
        for (i=0; i<100; i++);
}



#define BIT_MASK(i)       (0xFFFFFFFF >> (32-(i)))



/*-----------------------------------------------------------------------------
 * Func : _otp_get_bits
 *
 * Desc : get specified bits
 *
 * Parm :
 *
 * Retn :
 *-----------------------------------------------------------------------------*/
int _otp_get_bits(unsigned int* pval, unsigned char msb, unsigned char lsb)
{
    if (msb < lsb || lsb > 31 || msb > 31)
        return -1;

    *pval >>= lsb;
    *pval &= BIT_MASK(msb - lsb + 1);

    return 0;
}



/*-----------------------------------------------------------------------------
 * Func : otp_read
 *
 * Desc : read OTP word
 *
 * Parm : ofst : byte offsets, it should be 4 bytes alignments
 *
 * Retn : OTP words
 *-----------------------------------------------------------------------------*/
int otp_read(
    unsigned int           ofst,
    unsigned int*          pval
    )
{
    if (ofst & 0x3)
    {
        OTP_WARNING("read otp failed, ofst %08x is not 4 bytes alignments\n", ofst);
        return -1;
    }

    *pval = READ_REG32(OTP_DDR_MAP_BASE + ofst);

    return 0;
}



/*-----------------------------------------------------------------------------
 * Func : otp_read_bits
 *
 * Desc : read OTP bits
 *
 * Parm : ofst : byte offsets, it should be 4 bytes alignments
 *
 * Retn : OTP words
 *-----------------------------------------------------------------------------*/
int otp_read_bits(
    unsigned int           ofst,
    unsigned char           msb,
    unsigned char           lsb,
    unsigned int*          pval
    )
{
    int ret = otp_read(ofst, pval);

    if (ret==0 && *pval != 0xdeaddead)  // do not mask bits if it is non readable
        ret = _otp_get_bits(pval, msb, lsb);
   else
   	ret = -1;

    return ret;
}



/*-----------------------------------------------------------------------------
 * Func : otp_write
 *
 * Desc : write OTP words
 *
 * Parm : ofst : byte offsets, it should be 4 bytes alignments
 *        val  : value of OTP words
 *
 * Retn : OTP words
 *-----------------------------------------------------------------------------*/
int otp_write(
    unsigned int           ofst,
    unsigned int           val
    )
{
    unsigned int org;
    unsigned int status;
    unsigned int addr;
    int i;
//    int wait_count;
    int ret = 0;

    if (ofst & 0x3)
    {
        OTP_WARNING("write OTP failed, ofst %x is not 4 bytes alignments\n", ofst);
        return -1;
    }

    if (ofst >= MAX_OTP_OFST)
    {
        OTP_WARNING("write OTP failed, ofst %x >= MAX_OTP_OFST(%x)\n", ofst, MAX_OTP_OFST);
        return -1;
    }


    otp_read(ofst, &org);

    if (org==0xdeaddead)
    {
        printf("otp[0x%x] is non readable, no re-program check\n", ofst);
        org = 0;
    }
	WRITE_REG32(OTP_STATUS,0);

	WRITE_REG32(OTP_CTRL1, SET_OTP_CTRL1_WRITE_EN1(1) |
	                       SET_OTP_CTRL1_EN_PROG_FUNC(OTP_PROG_MAGIC));

    OTP_DBG("val=%08lx\n", val);

    for (i = 0; i < 32; i++)
    {
        addr = (ofst <<3) + i;

        if ((val & (1<<i))==0) {
            continue;
        }

        OTP_DBG("program otp bit %d (%08lx, %08lx)\n", addr, val, (1<<i));

        if (org & (1<<i))
        {
            OTP_DBG("otp bit %d has been programmed, write it anyway\n", addr);
            continue;
        }

        OTP_DBG("start otp bit %d programing\n", addr);

        WRITE_REG32(OTP_CTRL,
					SET_OTP_CTRL_WRITE_EN1(1) |
					SET_OTP_CTRL_MAX_PROG_NUM(0x14) |
					SET_OTP_CTRL_PROG(1) |
					SET_OTP_CTRL_A(addr));

//        wait_count = 0;
        do
        {
            status = READ_REG32(OTP_STATUS);
            OTP_DBG("Status = %08lx\n", status);

        	if (status & MASK_OTP_STATUS_OTP_FAIL_REG_WR)
            {
        		OTP_DBG("[ERROR] program OTP bit %d failed, status: 0x%x\n", addr, status);
        		ret = -1;
        		goto final;
        	}
#if 0
        	if (wait_count++ > 0xfffff00) {
        		ret = -1;  // Time out
			break;
        	}
#endif
        	//otp_udelay(1000);

        }while((status & MASK_OTP_STATUS_OTP_DONE_REG_WR)==0);

		OTP_DBG("otp bit %d programing completed\n", addr);

        WRITE_REG32(OTP_STATUS, status & ~(MASK_OTP_STATUS_OTP_FAIL_REG_WR | MASK_OTP_STATUS_OTP_DONE_REG_WR));
	}

final:

	WRITE_REG32(OTP_CTRL1, 0);
	WRITE_REG32(OTP_STATUS, 0);

    return ret;
}



/*-----------------------------------------------------------------------------
 * Func : otp_write_bits
 *
 * Desc : write OTP bits
 *
 * Parm : ofst : byte offsets, it should be 4 bytes alignments
 *        val  : value of OTP words
 *
 * Retn : OTP words
 *-----------------------------------------------------------------------------*/
int otp_write_bits(
    unsigned int           ofst,
    unsigned char           msb,
    unsigned char           lsb,
    unsigned int           val
    )
{
    if (msb < lsb || lsb > 31 || msb > 31)
        return -1;

    val &= BIT_MASK(msb - lsb + 1);
    val <<= lsb;                            // generate value

    return otp_write(ofst, val);
}
