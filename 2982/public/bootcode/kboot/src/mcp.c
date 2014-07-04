
/***********************************************************************
 *
 *  mcp.c
 *
 *  Implementation of hardware CP module
 *
 *
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
#include "sysdefs.h"
#include "sed_types.h"
#include "sed_common.h"
#include "sed_drv_common.h"
#include "error_type.h"
#include "malloc.h"
#include "cp_reg.h"
#include "mcp.h"
#include "otp_reg.h"
#include "big_util.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned char __attribute__((aligned(8))) mcp_hash_result[SHA256_SIZE];

/************************************************************************
 *  Static variables
 ************************************************************************/
static t_mcp_descriptor mcp_dscpt[2];

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern void dcache_flush_invalidate(void);
extern int compare_memory(void *s1, void *s2, unsigned int size);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int do_mcp(t_mcp_descriptor *dscpt);
static t_mcp_descriptor *alloc_mcp_descriptor(void);
static int load_otp(void);

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/

#if 0
int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4], UINT32 reg_mode)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

	t_mcp_descriptor *dscpt;
	int res;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return ERR_INVALID_PARAM;

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints(__FUNCTION__);
	prints("(");
	print_hex((UINT32) src_addr);
	prints(", ");
	print_hex(length);
	prints(", ");
	print_hex((UINT32) dst_addr);
	prints(")\n");
	if (key != NULL) {
		hexdump("AES key", (char *)key, 0x10);
	}
#endif

	if (key == NULL) {
		if ((res = load_otp()))
			return res;

		dscpt->mode = 0x1005;	// key from OTP
	}
	else {
		dscpt->mode = 0x0005;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr =  PHYS(src_addr);
	dscpt->dst_addr =  PHYS(dst_addr);


	dscpt->length = length;

#if defined(ENV_SIMULATION) || defined(CONFIG_DEBUG_SIMULATION_PRINT)
	sim_debug_print(0xae500ecb);
	sim_debug_print((UINT32) src_addr);
	sim_debug_print((UINT32) dst_addr);
	sim_debug_print(length);
	sim_debug_print(0xae50ffff);
#endif
	if (reg_mode == S_REG)
		return do_s_mcp(dscpt);
	else
		return do_k_mcp(dscpt);

}

#endif

unsigned int swap_endian(unsigned int input)
{
#if 0 //defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("\n");
#endif

	UINT32 output;

	output = (input & 0xff000000)>>24|
			 (input & 0x00ff0000)>>8|
			 (input & 0x0000ff00)<<8|
			 (input & 0x000000ff)<<24;

	return output;
}

int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;
	int res;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return ERR_INVALID_PARAM;

	if (key == NULL) {
		if ((res = load_otp()))
			return res;

		dscpt->mode = 0x1045;	// key from OTP
	}
	else {
		dscpt->mode = 0x0045;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}

	dscpt->src_addr =  PHYS(src_addr);
	dscpt->dst_addr =  PHYS(dst_addr);
	dscpt->length = length;

	return do_mcp(dscpt);
}

int AES_ECB_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL) {
		printf("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -1;
	}

	if (key == NULL) {
		if (load_otp()) {
			printf("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__ );
			return -2;
		}

		dscpt->mode = 0x1025;	// key from OTP
	}
	else {
		dscpt->mode = 0x0025;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}

	dscpt->src_addr =  PHYS((unsigned int)src_addr );
	dscpt->dst_addr =  PHYS((unsigned int)dst_addr );
	dscpt->length = length;

	return do_mcp(dscpt);
}

int SHA256_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[8])
{
	t_mcp_descriptor *dscpt;
	UINT32 from, to;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return ERR_INVALID_PARAM;

	// switch Dbus to DDR
//	REG32(MCP_RW_42K) = 0;

	// MCP descriptor in fixed address
	dscpt = alloc_mcp_descriptor();
	from = PHYS((UINT32) src_addr);
	to = PHYS((UINT32) dst_addr);

	dscpt->mode = 0xb;

	if (iv == NULL) {
		dscpt->key[0] = SHA256_H0;
		dscpt->key[1] = SHA256_H1;
		dscpt->key[2] = SHA256_H2;
		dscpt->key[3] = SHA256_H3;
		dscpt->key[4] = SHA256_H4;
		dscpt->key[5] = SHA256_H5;
		dscpt->ini_key[0] = SHA256_H6;
		dscpt->ini_key[1] = SHA256_H7;
	}
	else {
		dscpt->key[0] = iv[0];
		dscpt->key[1] = iv[1];
		dscpt->key[2] = iv[2];
		dscpt->key[3] = iv[3];
		dscpt->key[4] = iv[4];
		dscpt->key[5] = iv[5];
		dscpt->ini_key[0] = iv[6];
		dscpt->ini_key[1] = iv[7];
	}

	dscpt->src_addr = from;
	dscpt->dst_addr = to;
	dscpt->length = length;
	return do_mcp(dscpt);
}


static int do_mcp(t_mcp_descriptor *dscpt)
{
	int res;
	unsigned int base_addr;

	if (dscpt == NULL)
		return ERR_INVALID_PARAM;

	dcache_flush_invalidate();

	// disable interrupt
	REG32(K_MCP_EN) = 0xfe;

	// disable go bit
	REG32(K_MCP_CTRL) = 0x2;

	base_addr = PHYS((UINT32) dscpt);

	// set ring buffer register
	REG32(K_MCP_BASE)  = base_addr;
	REG32(K_MCP_LIMIT) = base_addr + sizeof(t_mcp_descriptor) * 2;
	REG32(K_MCP_RDPTR) = base_addr;
	REG32(K_MCP_WRPTR) = base_addr + sizeof(t_mcp_descriptor);	// writer pointer cannot be equal to limit

	sync();

	// swap descriptor content (KCPU is little-endian)
	REG32(K_MCP_CTRL) = 0x9;

	// go
	REG32(K_MCP_CTRL) = 0x3;
	while ((REG32(K_MCP_STATUS) & 0x6) == 0)
		;

	// check result
	if (REG32(K_MCP_STATUS) & 0x4)
		res = ERR_MCP_ERROR;	// error happened
	else if (REG32(K_MCP_STATUS) & 0x2)
		res = 0;		// completed without error
	else
		res = ERR_UNKNOWN_TYPE;	// ???

	// clear MCP register
	REG32(K_MCP_CTRL) = 0x2;
	REG32(K_MCP_STATUS) = 0x6;

	dcache_flush_invalidate();

	return res;
}

static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	memset(mcp_dscpt, 0, sizeof(mcp_dscpt));

	return mcp_dscpt;
}

static int load_otp(void)
{
	unsigned int i;

	REG32(CP_OTP_LOAD) = 0x1;

	for (i = 0; i < 0x10000; i++) {
		if ((REG32(CP_OTP_LOAD) & 0x1) == 0)
			return 0;
	}

	return ERR_TIMEOUT;
}

int check_key_already_in_cw(void)
{
	int i;

	for (i = 0; i < 0x4000; i++) {
		if ((REG32(CP_CW_AGENT) & 0x1))
			return 0;
	}

	return ERR_TIMEOUT;
}

int AES_decrypt_key_in_CW(UINT32 algo_id, UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key_entry)
{
	UINT32 mode;
	t_mcp_descriptor *dscpt;
	UINT32 from, to;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return ERR_INVALID_PARAM;

	// switch Dbus to DDR
	REG32(MCP_RW_42K) = 0;

	// MCP descriptor in fixed address
	dscpt = alloc_mcp_descriptor();
	from = PHYS((UINT32) src_addr);
	to = PHYS((UINT32) dst_addr);

	if (algo_id == ALGO_ID_AES_ECB)
		mode = MCP_BCM_ECB;
	else if (algo_id == ALGO_ID_AES_CBC)
		mode = MCP_BCM_CBC;
	else
		return ERR_UNKNOWN_TYPE;

	dscpt->mode = mode | (MCP_KEY_FROM_CW | MCP_DECRYPT | MCP_MODE_AES);
	dscpt->key[0] = REG_SET2_KEY_ENTRY(key_entry);
	dscpt->key[1] = dscpt->key[2] = dscpt->key[3] = 0;
	dscpt->length = length;
	dscpt->src_addr = from;
	dscpt->dst_addr = to;

	return do_mcp(dscpt);
}

void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length )
{
	unsigned int i, j, rows, count;
	sed_printf("======================================================\n");
	sed_printf("%s(base=0x%08x)\n", str, (unsigned int)(pcBuf));
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		sed_printf("%03x :", i<<4 );
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			sed_printf(" %02x",  *pcBuf );
			count++;
			pcBuf++;
		}
		sed_printf("\n");
	}
}

void reverse_signature( unsigned char * pSignature )
{
	unsigned char temp;
	unsigned int i;

	for( i = 0; i < 128; i ++ )  {
		temp = pSignature[i];
		pSignature[i] = pSignature[255-i];
		pSignature[255-i] = temp;
	}
}

int check_image_hash(char *p_img, unsigned int img_size, char *p_hash, char *p_mcp_sha256)
{
	int res;
	unsigned char *result = (unsigned char *)p_mcp_sha256;

	if ((p_img == NULL) || (p_hash == NULL))
		return ERR_INVALID_PARAM;

	// calculate image SHA256 p_hash value
	if ((res = SHA256_hash((unsigned char*)p_img, img_size, result, NULL)))
		return res;

	// compare p_hash value match?
	res = compare_memory(result, p_hash, SHA256_SIZE) ? ERR_NOT_MATCH : 0;

	if (res) {
		sed_printf("%s failed.\n", __FUNCTION__);
		rtk_hexdump("the 32-byte result", result, SHA256_SIZE );
		rtk_hexdump("the 32-byte p_hash", (unsigned char *)p_hash, SHA256_SIZE );
	}

	return res;
}

int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_hash_result_buf)
{
	int res;
	unsigned char *calc_hash = (unsigned char *)p_hash_result_buf;	// hash value calculated by CP
	unsigned char *recover_hash;	// hash value recovered by RSA
	unsigned char rsa_output[256];	//RSA output buffer
	unsigned int tmp;

	if ((p_img == NULL) || (p_sig == NULL))
		return ERR_INVALID_PARAM;

	if (p_rsa_key == NULL) {
		p_rsa_key = (char *)OTP_RSA_PUBLIC_KEY;	// key from OTP
	}

	/* calculate image hash value */
	if ((res = SHA256_hash((unsigned char *)p_img, img_size, calc_hash, NULL)))
		return res;

	/* recover hash value from RSA signature */
	tmp = do_RSA((unsigned int)p_sig, (unsigned int)p_rsa_key, (const unsigned int)rsa_output);
	recover_hash = (unsigned char *)tmp;

	/* compare hash value match? */
	res = (compare_memory(calc_hash, recover_hash, SHA256_SIZE) ? ERR_NOT_MATCH : 0);

	if ( res ) {
		sed_printf("%s failed.\n", __FUNCTION__);
		rtk_hexdump("the 32-byte hash1 (MCP calc)", calc_hash, SHA256_SIZE );
		rtk_hexdump("the 32-byte hash2 (RSA recover)", recover_hash, SHA256_SIZE );
	}

	return res;
}


