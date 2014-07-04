
/************************************************************************
 *  Include files
 ************************************************************************/
#include "sysdefs.h"
#include "big_util.h"
#include "big_int.h"
#include "otp_reg.h"
#include "sed_drv_common.h"
#include "sed_common.h"
#include "mcp.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#if defined(MEMORY_POOL)
//used for  RSA
#define MEMORY_POOL_SIZE	(5*1024)

// Aux code decryption will reuse this memory for original data
// I would like it align the the _f_data_cp_sram address. (It is 0xb8079000 now)
unsigned char memory_pool[MEMORY_POOL_SIZE];
#define MAX_ALLOC_SIZE MEMORY_POOL_SIZE
#define MALLOC_BASE (UINT32)memory_pool
#else
#define MAX_ALLOC_SIZE	32*1024*1024
#define MALLOC_BASE 0x82000000
#endif

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static UINT32 alloc_current;
static UINT32 alloc_count = 0;

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
void *my_malloc(UINT32 NBYTES)
{
	void *p;

	if ((alloc_count + NBYTES) > MAX_ALLOC_SIZE) {	// exceed limit
		return NULL;
	}

	if (alloc_count == 0)
		alloc_current = MALLOC_BASE;

	p = (void *)(alloc_current);

	// always aligned to word boundary
	if (NBYTES & 0x3)
		NBYTES = ((NBYTES >> 2) << 2) + 0x4;

	alloc_current += NBYTES;
	alloc_count += NBYTES;

	return p;
}

//dennistuan add start 20130222
void my_free(UINT32 NBYTES)
{
	// always aligned to word boundary
	if (NBYTES & 0x3)
		NBYTES = ((NBYTES >> 2) << 2) + 0x4;

	alloc_count -= NBYTES;
	alloc_current -= NBYTES;
}
//dennistuan add end 20130222

void my_freeAll(void)
{
	// reset all memory allocated by my_malloc()
	alloc_count = 0;
	alloc_current = MALLOC_BASE;
}

unsigned int do_RSA( const unsigned int signature_addr,
                     const unsigned int rsa_key_addr,
                     const unsigned int output_addr )
{
    BI *base, *exp, *mod, *res;
    unsigned int t1, tmp;
    int i;
    unsigned char * ptr;
    const char algo_id[19] = {
        0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
        0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
        0x00, 0x04, 0x20};

    // necessary
    alloc_count = 0;
    alloc_current = MALLOC_BASE;

    base = InPutFromAddr((unsigned char *)signature_addr, RSA_SIGNATURE_LENGTH);
    if(base == NULL) {
        my_freeAll();
		sed_printf("[ERR] %s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }

    mod = InPutFromAddr((unsigned char *)rsa_key_addr, RSA_SIGNATURE_LENGTH);
    if(mod == NULL) {
        my_freeAll();
		sed_printf("[ERR] %s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }

    // public exponent is always 65537
    exp = move_p(65537);
    if(exp == NULL) {
        my_freeAll();
		sed_printf("[ERR] %s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }

    res = Exp_Mod(base, exp, mod);
    if(res == NULL) {
        my_freeAll();
		sed_printf("[ERR] %s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }

    OutPutToAddr(res, (unsigned char *)output_addr, 1);

    // bypass PKCS#1 v1.5 block format
    t1 = output_addr;
    ptr = (unsigned char *)t1;
    if ((*ptr == 0) && (*(ptr+1) == 0x1)) {
        // skip padding
        // (padding format: 00 01 ff ff ff ... 00)
        t1 += 2;
        ptr += 2;

        while (*ptr == 0xff) {
            ptr++;
            t1++;
        }

        if (*ptr == 0) {
            ptr++;
            t1++;
        }

        tmp = t1;

        // skip digest algorithm identifier
        for (i = 0; i < sizeof(algo_id); i++) {
            if (*ptr != algo_id[i]) {
                t1 = tmp;   // restore to previous postition
                break;
            }
            ptr++;
            t1++;
        }
    }

    my_freeAll();

    return t1;
}
