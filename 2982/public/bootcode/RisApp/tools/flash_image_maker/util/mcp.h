/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for Mars CP module
 *
 ************************************************************************/

#ifndef MCP_H
#define MCP_H

#include <sysdefs.h>

/************************************************************************
 *  Definition
 ************************************************************************/
#define  CP_REG_BASE		0x18015000

#define  CP_OTP_LOAD		(CP_REG_BASE + 0x19c)

/* KCPU's RCP Register */
#define K_RCP_REG_KEY			(CP_REG_BASE + 0x834)
#define K_RCP_REG_DATAIN		(CP_REG_BASE + 0x844)
#define K_RCP_REG_DATAOUT		(CP_REG_BASE + 0x854)
#define K_RCP_REG_IV			(CP_REG_BASE + 0x864)
#define K_RCP_REG_SET			(CP_REG_BASE + 0x874)
#define K_RCP_REG_SET1			(CP_REG_BASE + 0x878)
#define K_RCP_REG_SET2			(CP_REG_BASE + 0x87c)

/* KCPU's MCP General Registers */
#define  K_MCP_CTRL		(CP_REG_BASE + 0x900)
#define  K_MCP_STATUS		(CP_REG_BASE + 0x904)
#define  K_MCP_EN		(CP_REG_BASE + 0x908)

/* KCPU's MCP Ring-Buffer Registers */
#define  K_MCP_BASE		(CP_REG_BASE + 0x90c)
#define  K_MCP_LIMIT		(CP_REG_BASE + 0x910)
#define  K_MCP_RDPTR		(CP_REG_BASE + 0x914)
#define  K_MCP_WRPTR		(CP_REG_BASE + 0x918)
#define  K_MCP_DES_COUNT	(CP_REG_BASE + 0x934)
#define  K_MCP_DES_COMPARE	(CP_REG_BASE + 0x938)

/* KCPU's MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY	(CP_REG_BASE + 0x91C)
#define  K_MCP_AES_INI_KEY	(CP_REG_BASE + 0x924)

	/* MCP General Registers */
#define  MCP_CTRL		(CP_REG_BASE + 0x100)
#define  MCP_STATUS		(CP_REG_BASE + 0x104)
#define  MCP_EN			(CP_REG_BASE + 0x108)

	/* MCP Ring-Buffer Registers */
#define  MCP_BASE		(CP_REG_BASE + 0x10c)
#define  MCP_LIMIT		(CP_REG_BASE + 0x110)
#define  MCP_RDPTR		(CP_REG_BASE + 0x114)
#define  MCP_WRPTR		(CP_REG_BASE + 0x118)
#define  MCP_DES_COUNT	(CP_REG_BASE + 0x134)
#define  MCP_DES_COMPARE	(CP_REG_BASE + 0x138)

	/* MCP Ini_Key Registers */
#define  MCP_DES_INI_KEY	(CP_REG_BASE + 0x11C)
#define  MCP_AES_INI_KEY	(CP_REG_BASE + 0x124)

/* 42K SCS SRAM Register */
#define MCP_RW_42K				(CP_REG_BASE + 0x1fc)

#define BIT(x)               (1 <<x)
#define REG_SET_WR_EN5      BIT(17)
#define REG_SET_MODE(x)     ((x & 0x7)<<13)
#define REG_SET_MODE_AES    REG_SET_MODE(0)
#define REG_SET_MODE_TDES   REG_SET_MODE(1)
#define REG_SET_MODE_DES    REG_SET_MODE(2)
#define REG_SET_MODE_SHA256    REG_SET_MODE(3)
#define REG_SET_MODE_MASK   REG_SET_MODE(7)
//#define REG_SET_WR_EN4     BIT(11)
//#define REG_SET_ENDIAN_BIG       (REG_SET_WR_EN4 | 0)
//#define REG_SET_ENDIAN_LITTLE  (REG_SET_WR_EN4 | BIT(10))

#define REG_SET_WR_EN2      BIT(5)
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


#define CP_DESCRIPTOR_ADDR	(0xa000ff00 - UBOOT_DDR_OFFSET)	/* CP descriptor address */
#define CP_DSCPT_POOL_BASE_ADDR	(0xa0010000 - UBOOT_DDR_OFFSET)	/* CP descriptor pool base address */
#define CP_DSCPT_POOL_SIZE	0x800		/* CP descriptor pool size */
#define CP_DSCPT_POOL_MAX_ADDR	(CP_DSCPT_POOL_BASE_ADDR + CP_DSCPT_POOL_SIZE)


typedef struct mcp_descriptor
{
    UINT32 mode;
    UINT32 key[6];
    UINT32 ini_key[4];
    UINT32 src_addr;
    UINT32 dst_addr;
    UINT32 length;
} t_mcp_descriptor ;

typedef struct rcp_descriptor
{
	unsigned int reg_set;
	unsigned int reg_set1;
	unsigned int reg_set2;
	unsigned int key[4];
	unsigned int data_in[4];
	unsigned int iv[4];
} t_rcp_descriptor;


/* 128 bit of AES_H initial vector(h0) */
#define AES_H_IV_0		0x2dc2df39
#define AES_H_IV_1		0x420321d0
#define AES_H_IV_2		0xcef1fe23
#define AES_H_IV_3		0x74029d95

/* 160 bit SHA1 initial vector */
#define SHA1_IV_0		0x67452301
#define SHA1_IV_1		0xEFCDAB89
#define SHA1_IV_2		0x98BADCFE
#define SHA1_IV_3		0x10325476
#define SHA1_IV_4		0xC3D2E1F0

#define SHA1_SIZE		20
#define SHA256_SIZE		32

#define MCP_DEBUG
#define RCP_DEBUG

/************************************************************************
 *  Public functions
 ************************************************************************/
int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_CBC_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_ECB_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_hash_one(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr);
int AES_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, INT32 block_size);
int SHA1_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[5]);

//int RCP_AES_decrypt_flash_protection_key(unsigned int *p_in, unsigned int *p_out);
//int RCP_AES_ECB_encrypt(unsigned int *p_in, unsigned int *p_out);
int AES_ECB_decrypt_key_in_CW(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key_entry);

#endif /* #ifndef MCP_H */
