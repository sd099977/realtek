#ifndef BIG_UTIL_H

/************************************************************************
 *  Definitions
 ************************************************************************/
#define memset set_memory
//#define printf RSA_prints
#define print_hex RSA_print_hex


#define MEMORY_POOL
#define FREE_MEMORY


#define REG_RSA_X		0xB806E000
#define REG_RSA_Y		0xB806E100
#define REG_RSA_M		0xB806E200
#define REG_RSA_A		0xB806E300
#define REG_RSA_CTRL	0xB806E400
#define REG_RSA_CTRL1	0xB806E410
#define REG_ECC_P		0xB806E300
#define REG_ECC_P_W12	0xB806E330
#define REG_ECC_V       0xB806E368
#define REG_ECC_V_W12	0xB806E398
#define REG_ECC_U       0xB806E334
#define REG_ECC_R       0xB806E39C
#define REG_ECC_CTRL	0xB806E414

/************************************************************************
 *  Function prototypes
 ************************************************************************/
void *my_malloc(UINT32 NBYTES);
void my_free(UINT32 NBYTES);   //dennistuan add 20130222

void my_freeAll(void);
//int strlen(const char *str);
int rsa_strlen(const char *str);
void set_memory(void *dst, UINT8 value, UINT32 size);

/* HardWare RSA */
//unsigned int do_RSA(const unsigned int signature_addr, const unsigned int rsa_key_addr,const unsigned int rsa_key_addr_r2,
//	const unsigned int output_addr);

/* SoftWare RSA */
//unsigned int do_RSA(const unsigned int signature_addr,
//					const unsigned int rsa_key_addr,
//					const unsigned int output_addr);

unsigned int do_RSA(unsigned char op,
					const unsigned int text_addr,
					const unsigned int rsa_key_addr,
					const unsigned int output_addr);



//void RSA_prints(const char *message);
//void RSA_print_hex(const unsigned int val);
unsigned int skip_pkcs_v1_5_padding(char *ptr);

#define BIG_UTIL_H
#endif /* BIG_UTIL_H */
