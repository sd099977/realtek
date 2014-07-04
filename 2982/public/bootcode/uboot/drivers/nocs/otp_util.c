#include "nocs_bsd_env.h"
#include "otp_util.h"
#include "otp_reg.h"
#include "otp_debug.h"
#include "print_rpc.h"

/*
 * reference below :
 * http://172.21.0.100/svn/col/DVR/branches/software/system/src/Platform_Lib/OTPControl
 */

static void otp_udelay(u32 us)
{
    int i;
    while(us--)
        for (i=0; i<100; i++);
}

#define OTP_BIT_MASK(i)       (0xFFFFFFFF >> (32-(i)))

/*-----------------------------------------------------------------------------
 * Func : _otp_get_bits
 *
 * Desc : get specified bits
 *
 * Parm :
 *
 * Retn :
 *-----------------------------------------------------------------------------*/
static int _otp_get_bits(u32* pval, u8 msb, u8 lsb)
{
    BD_INFO("\n");
    if (msb < lsb || lsb > 31 || msb > 31){
        BD_INFO("\n");
        return -1;
    }

    *pval >>= lsb;
    *pval &= OTP_BIT_MASK(msb - lsb + 1);
    BD_INFO("*pval=0x%x\n",*pval);

    return 0;
}

/*-----------------------------------------------------------------------------
 * Func : bsd_otp_read
 *
 * Desc : read OTP word
 *
 * Parm : ofst : byte offsets, it should be 4 bytes alignments
 *
 * Retn : OTP words
 *-----------------------------------------------------------------------------*/
static int bsd_otp_read(u32 ofst,u32* pval)
{
    BD_INFO("ofst=%d, *pval=0x%x\n",ofst,*pval);
    if (ofst & 0x3)
    {
        BD_INFO("read otp failed, ofst 0x%08x is not 4 bytes alignments\n", ofst);
        return -1;
    }

    *pval = rtd_inl(OTP_DDR_MAP_BASE + ofst);
    BD_INFO("ofst=%d, *pval=0x%x\n",ofst,*pval);

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
int otp_read_bits(u32 ofst,
                  u8 msb,
                  u8 lsb,
                  u32* pval )
{
    int ret;
    BD_INFO("ofst=%d msb=%d lsb=%d *pval=0x%x\n",
            ofst,msb,lsb,*pval);
    ret = bsd_otp_read(ofst, pval);
    BD_INFO("*pval=0x%x\n",*pval);
    // do not mask bits if it is non readable
    if (ret==0 && *pval != 0xdeaddead){
        BD_INFO("\n");
        ret = _otp_get_bits(pval, msb, lsb);
    }

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
int otp_write(u32 ofst,u32 val)
{
    u32 org;
    u32 status;
    u32 addr;
    int i;
    int wait_count;
    int ret = 0;

    if (ofst & 0x3)
    {
        BD_INFO("write OTP failed, ofst %x is not 4 bytes alignments\n", ofst);
        return -1;
    }

    if (ofst >= MAX_OTP_OFST)
    {
        BD_INFO("write OTP failed, ofst %x >= MAX_OTP_OFST(%x)\n", ofst, MAX_OTP_OFST);
        return -1;
    }

    bsd_otp_read(ofst, &org);

    if (org==0xdeaddead)
    {
        BD_INFO("otp[0x%x] is non readable, no re-program check\n", ofst);
        org = 0;
    }

	rtd_outl(OTP_STATUS,0);

	rtd_outl(OTP_CTRL1, SET_OTP_CTRL1_WRITE_EN1(1) |
	                       SET_OTP_CTRL1_EN_PROG_FUNC(OTP_PROG_MAGIC));

    BD_INFO("val=%08x\n", val);

    for (i = 0; i < 32; i++)
    {
        addr = (ofst <<3) + i;

        if ((val & (1<<i))==0) {
            continue;
        }

        BD_INFO("program otp bit %d (%08x, %08x)\n", addr, val, (1<<i));

        if (org & (1<<i))
        {
            BD_INFO("otp bit %d has been programmed, write it anyway\n", addr);
            continue;
        }

        BD_INFO("start otp bit %d programing\n", addr);

        rtd_outl(OTP_CTRL,
					SET_OTP_CTRL_WRITE_EN1(1) |
					SET_OTP_CTRL_MAX_PROG_NUM(0x14) |
					SET_OTP_CTRL_PROG(1) |
					SET_OTP_CTRL_A(addr));

        wait_count = 0;
        do
        {
            status = rtd_inl(OTP_STATUS);
            BD_INFO("Status = %08x\n", status);

        	if (status & MASK_OTP_STATUS_OTP_FAIL_REG_WR)
            {
        		BD_INFO("[ERROR] program OTP bit %d failed, status: 0x%x\n", addr, status);
        		ret = -1;
        		goto final;
        	}

        	if (wait_count++ > 0)
        	    break;

        	otp_udelay(1000);

        }while((status & MASK_OTP_STATUS_OTP_DONE_REG_WR)==0);

		BD_INFO("otp bit %d programing completed\n", addr);

        rtd_outl(OTP_STATUS, status & ~(MASK_OTP_STATUS_OTP_FAIL_REG_WR | MASK_OTP_STATUS_OTP_DONE_REG_WR));
	}

final:

	rtd_outl(OTP_CTRL1, 0);
	rtd_outl(OTP_STATUS, 0);

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
int otp_write_bits(u32 ofst,u8 msb,u8 lsb,u32 val )
{
    if (msb < lsb || lsb > 31 || msb > 31){
        BD_INFO("\n");
        return -1;
    }

    val &= OTP_BIT_MASK(msb - lsb + 1);
    val <<= lsb;                            // generate value

    BD_INFO("ofst=%d val-0x%x\n",ofst,val);
    return otp_write(ofst, val);
}
