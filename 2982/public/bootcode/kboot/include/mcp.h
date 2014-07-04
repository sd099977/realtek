/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for MCP function
 *
 ************************************************************************/

#ifndef MCP_H
#define MCP_H

/************************************************************************
 *  Definition
 ************************************************************************/

/* 128 bit of AES_H initial vector(h0) */
#define AES_H_IV_0		0x2dc2df39
#define AES_H_IV_1		0x420321d0
#define AES_H_IV_2		0xcef1fe23
#define AES_H_IV_3		0x74029d95

/* 160 bit SHA1 initial vector */
#ifndef SHA1_IV_0
#define SHA1_IV_0		0x67452301
#define SHA1_IV_1		0xEFCDAB89
#define SHA1_IV_2		0x98BADCFE
#define SHA1_IV_3		0x10325476
#define SHA1_IV_4		0xC3D2E1F0
#endif

#define SHA1_SIZE		20

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
#define RSA_SIGNATURE_LENGTH			(256)
#define RSA_2048_KEY_LENGTH				(256)		/* RSA 2048 key length (2048 bit) */

#define K_REG 0
#define S_REG 1

#define ON_DMEM 0
#define ON_DDR 1

#define ALGO_ID_AES_ECB		0
#define ALGO_ID_AES_CBC		1

/* CP 42K SRAM region */
#define CP42K_SRAM_ADDR		0xb8070000
#define CP_SRAM_BASE		CP42K_SRAM_ADDR
#define CP_SRAM_SIZE		0xa800

#define PHYS_CP_SRAM(addr)	(addr - CP_SRAM_BASE)
#define IS_IN_CP_SRAM(addr)	((unsigned int)PHYS_CP_SRAM(addr) < CP_SRAM_SIZE)

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
int SHA1_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[5]);
int SHA256_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[8]);
int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4], UINT32 reg_mode);
int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_ECB_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int check_key_already_in_cw(void);
int AES_decrypt_key_in_CW(UINT32 algo_id, UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key_entry);

void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
void reverse_signature( unsigned char * pSignature );

int check_image_hash(char *p_img, unsigned int img_size, char *p_hash, char *p_mcp_sha256);
int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_hash_result_buf);

extern unsigned char __attribute__((aligned(8))) mcp_hash_result[SHA256_SIZE];

#endif /* #ifndef MCP_H */
