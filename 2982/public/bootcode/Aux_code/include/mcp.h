/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for Sirius MCP function in Aux code
 *
 ************************************************************************/

#ifndef MCP_H
#define MCP_H

/************************************************************************
 *  Definition
 ************************************************************************/

/* 256 bit SHA256 initial vector */
#define SHA256_H0		0x6A09E667
#define SHA256_H1		0xBB67AE85
#define SHA256_H2		0x3C6EF372
#define SHA256_H3		0xA54FF53A
#define SHA256_H4		0x510E527F
#define SHA256_H5		0x9B05688C
#define SHA256_H6		0x1F83D9AB
#define SHA256_H7		0x5BE0CD19


#define SHA256_SIZE		32

#define RSA_SIZE		(2048/8)

#define K_REG 0
#define S_REG 1

#define ON_DMEM 0
#define ON_DDR 1

#define ALGO_ID_AES_ECB		0
#define ALGO_ID_AES_CBC		1

/* CP 42K SRAM region */
#define CP_SRAM_BASE		CP42K_SRAM_ADDR
#define CP_SRAM_SIZE		0xa800
//#define CP_DESCRIPTOR_ADDR	(CP_SRAM_BASE + 0xa700)	/* CP descriptor address (in CP42K SRAM) */
//#define CP_HASH_ADDR		(CP_SRAM_BASE + 0xa780)	/* CP SHA256 output address (in CP42K SRAM) */

#define PHYS_CP_SRAM(addr)	(addr - CP_SRAM_BASE)
#define IS_IN_CP_SRAM(addr)	(PHYS_CP_SRAM(addr) < CP_SRAM_SIZE)

#define CP_DSCPT_DDR		0xa0000100	/* CP descriptor address (in DDR) */
#define CP_HASH_DDR		0xa00000a0	/* CP SHA256 output address (in DDR) */

typedef struct mcp_descriptor
{
    unsigned int mode;
    unsigned int key[6];
    unsigned int ini_key[4];
    unsigned int src_addr;
    unsigned int dst_addr;
    unsigned int length;
} __attribute__((aligned(8))) t_mcp_descriptor;

typedef struct rcp_descriptor
{
	unsigned int reg_set;
	unsigned int reg_set1;
	unsigned int reg_set2;
	unsigned int key[4];
	unsigned int data_in[4];
	unsigned int iv[4];
} t_rcp_descriptor;

/************************************************************************
 *  Public function prototypes
 ************************************************************************/
int SHA256_hash(unsigned char *src_addr, int length, unsigned char *dst_addr, unsigned int iv[8]);
int AES_decrypt_key_in_CW(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry);

#endif /* #ifndef MCP_H */
