/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for CP module
 *
 ************************************************************************/

#ifndef __MCP_H__
#define __MCP_H__

//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>
//#include "sysdefs.h"
#include <asm/arch/system.h>

/************************************************************************
 *  Memory usage
 ************************************************************************/
#define SECURE_IMAGE2HASH_BUF		(rtk_mem_info->secure_mcp_mem_buffer_addr)
#define SECURE_SIGN2HASH_BUF		(rtk_mem_info->secure_mcp_mem_buffer_addr + 0x200)
#define SECURE_SIGN2HASH_TEMP_BUF   (rtk_mem_info->secure_mcp_mem_buffer_addr + 0x800)
#define SECURE_MAX_ALLOC_SIZE		(UBOOT_SECURE_MCP_MEMORY_SIZE)	// (32UL << 20)
#define SECURE_MALLOC_BASE 			SECURE_SIGN2HASH_TEMP_BUF

/************************************************************************
 *  Definition
 ************************************************************************/
#define  DEFAULT_KEY_PTR			NULL // Kh_key_default

#define  CP_REG_BASE				0xb8015000

#define  CP_OTP_LOAD				(CP_REG_BASE + 0x19c)

#if 0
	//for KCPU & ACPU
	/* MCP General Registers */
#define  K_MCP_CTRL					(CP_REG_BASE + 0x900)
#define  K_MCP_STATUS				(CP_REG_BASE + 0x904)
#define  K_MCP_EN					(CP_REG_BASE + 0x908)

	/* MCP Ring-Buffer Registers */
#define  K_MCP_BASE					(CP_REG_BASE + 0x90c)
#define  K_MCP_LIMIT				(CP_REG_BASE + 0x910)
#define  K_MCP_RDPTR				(CP_REG_BASE + 0x914)
#define  K_MCP_WRPTR				(CP_REG_BASE + 0x918)
#define  K_MCP_DES_COUNT			(CP_REG_BASE + 0x934)
#define  K_MCP_DES_COMPARE			(CP_REG_BASE + 0x938)

	/* MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY			(CP_REG_BASE + 0x91C)
#define  K_MCP_AES_INI_KEY			(CP_REG_BASE + 0x924)
#else
	//for SCPU
	/* MCP General Registers */
#define  K_MCP_CTRL					(CP_REG_BASE + 0x100)
#define  K_MCP_STATUS				(CP_REG_BASE + 0x104)
#define  K_MCP_EN					(CP_REG_BASE + 0x108)

	/* MCP Ring-Buffer Registers */
#define  K_MCP_BASE					(CP_REG_BASE + 0x10c)
#define  K_MCP_LIMIT				(CP_REG_BASE + 0x110)
#define  K_MCP_RDPTR				(CP_REG_BASE + 0x114)
#define  K_MCP_WRPTR				(CP_REG_BASE + 0x118)
#define  K_MCP_DES_COUNT			(CP_REG_BASE + 0x134)
#define  K_MCP_DES_COMPARE			(CP_REG_BASE + 0x138)

	/* MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY			(CP_REG_BASE + 0x11C)
#define  K_MCP_AES_INI_KEY			(CP_REG_BASE + 0x124)
#endif

#define MCP_RW_42K					(CP_REG_BASE + 0x1fc)

#define UBOOT_DDR_OFFSET        	0xA0000000  //for RTD299X

#define CP_DESCRIPTOR_ADDR			(0xa000ff00 - UBOOT_DDR_OFFSET)	/* CP descriptor address */
#define CP_DSCPT_POOL_BASE_ADDR		(0xa0010000 - UBOOT_DDR_OFFSET)	/* CP descriptor pool base address */
#define CP_DSCPT_POOL_SIZE			0x800							/* CP descriptor pool size */
#define CP_DSCPT_POOL_MAX_ADDR		(CP_DSCPT_POOL_BASE_ADDR + CP_DSCPT_POOL_SIZE)


typedef struct mcp_descriptor
{
    unsigned int mode;
    unsigned int key[6];
    unsigned int ini_key[4];
    unsigned int src_addr;
    unsigned int dst_addr;
    unsigned int length;
} t_mcp_descriptor ;

/* 128 bit of AES_H initial vector(h0) */
#define AES_H_IV_0		            0x2dc2df39
#define AES_H_IV_1		            0x420321d0
#define AES_H_IV_2		            0xcef1fe23
#define AES_H_IV_3		            0x74029d95

/* 160 bit SHA1 initial vector */
#ifndef SHA1_IV_0
    #define SHA1_IV_0		        0x67452301
    #define SHA1_IV_1		        0xEFCDAB89
    #define SHA1_IV_2		        0x98BADCFE
    #define SHA1_IV_3		        0x10325476
    #define SHA1_IV_4		        0xC3D2E1F0
#endif

#define SHA1_SIZE					20

/* 256 bit SHA256 initial vector */
#define SHA256_H0					0x6A09E667
#define SHA256_H1					0xBB67AE85
#define SHA256_H2					0x3C6EF372
#define SHA256_H3					0xA54FF53A
#define SHA256_H4					0x510E527F
#define SHA256_H5					0x9B05688C
#define SHA256_H6					0x1F83D9AB
#define SHA256_H7					0x5BE0CD19


#define SHA256_SIZE					32


#define SECURE_KH_KEY_STR 			"abcdef1213572468a1b2c3d49090babe"
#define SECURE_KH_KEY0 				0xabcdef12
#define SECURE_KH_KEY1 				0x13572468
#define SECURE_KH_KEY2 				0xa1b2c3d4
#define SECURE_KH_KEY3 				0x9090babe

#define RSA_SIGNATURE_LENGTH		256

#define PHYS(addr)              	((uint)(addr))



#define REG_SET1_KEY_MODE(x)         ((x & 0x3)<<6)
#define REG_SET1_KEY_MODE_REGISTER   REG_SET1_KEY_MODE(0)
#define REG_SET1_KEY_MODE_CW         REG_SET1_KEY_MODE(1)
#define REG_SET1_KEY_MODE_OTP        REG_SET1_KEY_MODE(2)
#define REG_SET1_KEY_MODE_MASK       REG_SET1_KEY_MODE(3)

#define REG_SET1_IV_MODE(x)          ((x & 0x3)<<4)
#define REG_SET1_IV_MODE_REG         REG_SET1_IV_MODE(0)
#define REG_SET1_IV_MODE_CW          REG_SET1_IV_MODE(1)

#define REG_SET1_INPUT_MODE(x)       ((x & 0x3)<<2)
#define REG_SET1_INPUT_MODE_REG      REG_SET1_INPUT_MODE(0)
#define REG_SET1_INPUT_MODE_CW       REG_SET1_INPUT_MODE(1)

#define REG_SET1_OUTPUT_MODE(x)      ((x & 0x3))
#define REG_SET1_OUTPUT_MODE_REG     REG_SET1_OUTPUT_MODE(0)
#define REG_SET1_OUTPUT_MODE_CW      REG_SET1_OUTPUT_MODE(1)

#define REG_SET2_OUTPUT_ENTRY(x)     ((x & 0x7F)<<24)
#define REG_SET2_INPUT_ENTRY(x)      ((x & 0x7F)<<16)
#define REG_SET2_KEY_ENTRY(x)        ((x & 0x7F)<<8)
#define REG_SET2_IV_ENTRY(x)         ((x & 0x7F))



#define ALGO_ID_AES_ECB		0
#define ALGO_ID_AES_CBC		1

#define BIT(x)               (1 <<x)
#define REG_SET_WR_EN5      BIT(17)
#define REG_SET_MODE(x)     ((x & 0x7)<<13)
#define REG_SET_MODE_AES    REG_SET_MODE(0)
#define REG_SET_MODE_TDES   REG_SET_MODE(1)
#define REG_SET_MODE_DES    REG_SET_MODE(2)
#define REG_SET_MODE_SHA256    REG_SET_MODE(3)
#define REG_SET_MODE_MASK   REG_SET_MODE(7)
#define REG_SET_WR_EN4     BIT(11)    
#define REG_SET_ENDIAN_BIG       (REG_SET_WR_EN4 | 0)
#define REG_SET_ENDIAN_LITTLE  (REG_SET_WR_EN4 | BIT(10))

#define REG_SET_WR_EN2      BIT(6)
#define REG_SET_CBC         BIT(4)
#define REG_SET_ECB         0x0
#define REG_SET_WR_EN1      BIT(3)
#define REG_SET_FIRST_128   BIT(2)  
#define REG_SET_WR_EN0      BIT(1)
#define REG_SET_ENC         BIT(0)
#define REG_SET_DEC         0x0

#define RCP_AES_128_ECB_ENC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_ECB_DEC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)
#define RCP_AES_128_CBC_ENC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_CBC_DEC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)
#define RCP_SHA256                        (REG_SET_WR_EN5 | REG_SET_MODE_SHA256 | REG_SET_WR_EN0 | REG_SET_ENC)

#define REG_SET1_KEY_MODE(x)         ((x & 0x3)<<6)
#define REG_SET1_KEY_MODE_REGISTER   REG_SET1_KEY_MODE(0)
#define REG_SET1_KEY_MODE_CW         REG_SET1_KEY_MODE(1)
#define REG_SET1_KEY_MODE_OTP        REG_SET1_KEY_MODE(2)
#define REG_SET1_KEY_MODE_MASK       REG_SET1_KEY_MODE(3)

#define REG_SET1_IV_MODE(x)          ((x & 0x3)<<4)
#define REG_SET1_IV_MODE_REG         REG_SET1_IV_MODE(0)
#define REG_SET1_IV_MODE_CW          REG_SET1_IV_MODE(1)
                                         
#define REG_SET1_INPUT_MODE(x)       ((x & 0x3)<<2)
#define REG_SET1_INPUT_MODE_REG      REG_SET1_INPUT_MODE(0)
#define REG_SET1_INPUT_MODE_CW       REG_SET1_INPUT_MODE(1)

#define REG_SET1_OUTPUT_MODE(x)      ((x & 0x3))
#define REG_SET1_OUTPUT_MODE_REG     REG_SET1_OUTPUT_MODE(0)
#define REG_SET1_OUTPUT_MODE_CW      REG_SET1_OUTPUT_MODE(1)

#define REG_SET2_OUTPUT_ENTRY(x)     ((x & 0x7F)<<24)
#define REG_SET2_INPUT_ENTRY(x)      ((x & 0x7F)<<16)        
#define REG_SET2_KEY_ENTRY(x)        ((x & 0x7F)<<8)
#define REG_SET2_IV_ENTRY(x)         ((x & 0x7F))

/* MCP descriptor define */
#define MCP_KEY_SEL(x)               ((x & 0x3) << 12)
#define MCP_KEY_FROM_DSCPT           MCP_KEY_SEL(0)
#define MCP_KEY_FROM_OTP             MCP_KEY_SEL(1)
#define MCP_KEY_FROM_CW              MCP_KEY_SEL(2)
#define MCP_KEY_FROM_DDR             MCP_KEY_SEL(3)


#define MCP_BCM_SEL(x)               ((x & 0xf) << 6)
#define MCP_BCM_ECB                  MCP_BCM_SEL(0)
#define MCP_BCM_CBC                  MCP_BCM_SEL(1)
#define MCP_BCM_CTR                  MCP_BCM_SEL(2)
#define MCP_BCM_RCBC_CS              MCP_BCM_SEL(3)

#define MCP_ENCRYPT                  BIT(5)
#define MCP_DECRYPT                  0x0

#define MCP_MODE_SEL(x)              (x & 0x1f)
#define MCP_MODE_DES                 MCP_MODE_SEL(0x0)
#define MCP_MODE_3DES                MCP_MODE_SEL(0x1)
#define MCP_MODE_MD5                 MCP_MODE_SEL(0x3)
#define MCP_MODE_SHA1                MCP_MODE_SEL(0x4)
#define MCP_MODE_AES                 MCP_MODE_SEL(0x5)
#define MCP_MODE_AES_G               MCP_MODE_SEL(0x6)
#define MCP_MODE_AES_H               MCP_MODE_SEL(0x7)
#define MCP_MODE_CMAC                MCP_MODE_SEL(0x8)
#define MCP_MODE_CSA                 MCP_MODE_SEL(0x9)
#define MCP_MODE_MULTI2              MCP_MODE_SEL(0xa)
#define MCP_MODE_SHA256              MCP_MODE_SEL(0xb)



//#define MCP_DEBUG
/************************************************************************
 *  Public functions
 ************************************************************************/
int AES_CBC_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_CBC_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_ECB_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_ECB_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_CBC_decrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry);
int AES_CBC_encrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry);
int AES_ECB_decrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry);
int AES_ECB_encrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry);
int AES_hash_one(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr);
int AES_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int block_size);
int SHA1_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int iv[5]);
int SHA256_hash(unsigned char * src_addr, unsigned int length, unsigned char *dst_addr, unsigned int iv[8]);
int Verify_SHA256_hash( unsigned char * src_addr, unsigned int length, unsigned char * ref_sha256, unsigned int do_recovery );
void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
void reverse_signature( unsigned char * pSignature );
int reload_otp(void);

#endif // __MCP_H__
