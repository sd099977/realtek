#ifndef BIG_UTIL_H
#define BIG_UTIL_H

/************************************************************************
 *  Definitions
 ************************************************************************/
#define MEMORY_POOL
#define FREE_MEMORY

/************************************************************************
 *  Function prototypes
 ************************************************************************/
void *my_malloc(UINT32 NBYTES);
void my_free(UINT32 NBYTES);   //dennistuan add 20130222
void my_freeAll(void);
unsigned int do_RSA(const unsigned int signature_addr,
	const unsigned int rsa_key_addr,
	const unsigned int output_addr);

#endif /* BIG_UTIL_H */
