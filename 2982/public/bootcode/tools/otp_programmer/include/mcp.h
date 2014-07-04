/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for Mars CP module 
 *
 ************************************************************************/

#ifndef MCP_H
#define MCP_H


/************************************************************************
 *  Definition
 ************************************************************************/
#define  MCP_REG_BASE              (0xb8015000)

#define  MCP_OTP_LOAD              (MCP_REG_BASE + 0x19c)

/* MCP General Registers */
#define  MCP_CTRL                  (MCP_REG_BASE + 0x900)
#define  MCP_STATUS                (MCP_REG_BASE + 0x904)
#define  MCP_EN                    (MCP_REG_BASE + 0x908)

/* MCP Ring-Buffer Registers */
#define  MCP_BASE                  (MCP_REG_BASE + 0x90c)
#define  MCP_LIMIT                 (MCP_REG_BASE + 0x910)
#define  MCP_RDPTR                 (MCP_REG_BASE + 0x914)
#define  MCP_WRPTR                 (MCP_REG_BASE + 0x918)
#define  MCP_DES_COUNT             (MCP_REG_BASE + 0x934)
#define  MCP_DES_COMPARE           (MCP_REG_BASE + 0x938)

/* MCP Ini_Key Registers */
#define  MCP_DES_INI_KEY           (MCP_REG_BASE + 0x91C)
#define  MCP_AES_INI_KEY           (MCP_REG_BASE + 0x924)


typedef struct mcp_descriptor
{
    unsigned int mode;
    unsigned int key[6];
    unsigned int ini_key[4];
    unsigned int src_addr;
    unsigned int dst_addr;
    unsigned int length;
} __attribute__((aligned(8))) t_mcp_descriptor ;

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

/* 256 bit SHA256 initial vector */
#define SHA256_H0		0x6A09E667
#define SHA256_H1		0xBB67AE85
#define SHA256_H2		0x3C6EF372
#define SHA256_H3		0xA54FF53A
#define SHA256_H4		0x510E527F
#define SHA256_H5		0x9B05688C
#define SHA256_H6		0x1F83D9AB
#define SHA256_H7		0x5BE0CD19

/*#define MCP_DEBUG*/
/************************************************************************
 *  Public functions
 ************************************************************************/
int AES_CBC_encrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4]);
int AES_CBC_decrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4]);
int AES_ECB_decrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4]);
int AES_ECB_encrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4]);
//int AES_hash(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr);
int AES_hash(unsigned char *src_addr, int length, unsigned char *dst_addr, int block_size);

#endif /* #ifndef MCP_H */

