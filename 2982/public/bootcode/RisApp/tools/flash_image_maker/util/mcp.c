
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

#include <sysdefs.h>
//#include <syserror.h>
//#include <string.h>
#include <stdio.h>
#include "mcp.h"
#include "util.h"//modify by angus

/************************************************************************
 *  Definitions
 ************************************************************************/


/************************************************************************
 *  Public variables
 ************************************************************************/
extern void sys_dcache_flush_all(void);
extern void sys_dcache_flush_invalidate_all(void);


/************************************************************************
 *  Static variables
 ************************************************************************/
// reserve 2 descriptor for do_mcp (writer pointer cannot be equal to limit)
// (must be 8B boundary)
//static t_mcp_descriptor mcp_dscpt[2] __attribute__ ((aligned (8)));


/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int do_mcp(t_mcp_descriptor *dscpt);
static t_mcp_descriptor *alloc_mcp_descriptor(void);
static void update_initial_vector(t_mcp_descriptor *dscpt, UINT8 *vector);
static int load_otp(void);

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/


int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1045;	// key from OTP
	}
	else {
		dscpt->mode = 0x0045;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}

int AES_CBC_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1065;	// key from OTP
	}
	else {
		dscpt->mode = 0x0065;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1005;	// key from OTP
	}
	else {
		dscpt->mode = 0x0005;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1025;	// key from OTP
	}
	else {
		dscpt->mode = 0x0025;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
#if 0
			dscpt->src_addr =  ((UINT32)src_addr & 0x0fffffff);
			dscpt->dst_addr =  ((UINT32)dst_addr & 0x0fffffff);
#else
	dscpt->src_addr =  PHYS((UINT32)src_addr);
	dscpt->dst_addr =  PHYS((UINT32)dst_addr);
#endif
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_hash_one(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr)
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	// only once
	dscpt->mode = 0x27;
	dscpt->ini_key[0] = AES_H_IV_0;
	dscpt->ini_key[1] = AES_H_IV_1;
	dscpt->ini_key[2] = AES_H_IV_2;
	dscpt->ini_key[3] = AES_H_IV_3;
	dscpt->src_addr = (UINT32) src_addr;
	dscpt->dst_addr = (UINT32) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, INT32 block_size)
{
	t_mcp_descriptor *dscpt;
	UINT8 *src_ptr;
	int res;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return -1;

	if ((length <= 0) || (block_size <= 0))
		return -1;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	// IV from dscpt, AES hash
	dscpt->mode = 0x27;
	dscpt->ini_key[0] = AES_H_IV_0;
	dscpt->ini_key[1] = AES_H_IV_1;
	dscpt->ini_key[2] = AES_H_IV_2;
	dscpt->ini_key[3] = AES_H_IV_3;
	src_ptr = src_addr;
	dscpt->dst_addr = (UINT32) dst_addr;

	res = 0;
	while (length > 0) {
		dscpt->src_addr = (UINT32) src_ptr;
		dscpt->length = length < block_size ? length: block_size;
		length -= block_size;

		res = do_mcp(dscpt);
		if (res)
			return res;

		if (length > 0) {
			// update descriptor for next block
			update_initial_vector(dscpt, (UINT8 *)dst_addr);
			src_ptr += dscpt->length;
		}
		else
			break;
	}

	return res;
}


int SHA1_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[5])
{
	t_mcp_descriptor *dscpt;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return -1;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	dscpt->mode = 0x0004;

	if (iv == NULL) {
		// Mars style (always the same IV)
		dscpt->key[0] = SHA1_IV_0;
		dscpt->key[1] = SHA1_IV_1;
		dscpt->key[2] = SHA1_IV_2;
		dscpt->key[3] = SHA1_IV_3;
		dscpt->key[4] = SHA1_IV_4;
	}
	else {
		dscpt->key[0] = iv[0];
		dscpt->key[1] = iv[1];
		dscpt->key[2] = iv[2];
		dscpt->key[3] = iv[3];
		dscpt->key[4] = iv[4];
	}

#if 0
		dscpt->src_addr =  ((UINT32)src_addr & 0x0fffffff);
		dscpt->dst_addr =  ((UINT32)dst_addr & 0x0fffffff);
#else
		dscpt->src_addr =  ((UINT32)src_addr );
		dscpt->dst_addr =  ((UINT32)dst_addr );

#endif
	dscpt->length = length;


	return do_mcp(dscpt);
}


static int do_mcp(t_mcp_descriptor *dscpt)
{
#ifdef MCP_DEBUG
	int i;
#endif
	int res;
	int count;

	if (dscpt == NULL)
		return -1;

	sys_dcache_flush_all();

	// disable interrupt
	REG32(K_MCP_EN) = 0xfe;

	// disable go bit
	REG32(K_MCP_CTRL) = 0x2;

	// MCP¡¦s DBUS mapped to DDR
	REG32(MCP_RW_42K) = 0x0;

#if 0
		// set ring buffer register
		REG32(K_MCP_BASE)  = (((UINT32) dscpt) & 0x0fffffff);
		REG32(K_MCP_LIMIT) = (((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2) & 0x0fffffff);
		REG32(K_MCP_RDPTR) = (((UINT32) dscpt) & 0x0fffffff);
		REG32(K_MCP_WRPTR) = (((UINT32) dscpt + sizeof(t_mcp_descriptor)) & 0x0fffffff);	// writer pointer cannot be equal to limit
#else
		// set ring buffer register
		REG32(K_MCP_BASE)  = PHYS(((UINT32) dscpt) );
		REG32(K_MCP_LIMIT) = PHYS(((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2) );
		REG32(K_MCP_RDPTR) = PHYS(((UINT32) dscpt) );
		REG32(K_MCP_WRPTR) = PHYS(((UINT32) dscpt + sizeof(t_mcp_descriptor)) );	// writer pointer cannot be equal to limit

#endif

	//hexdump("[do_mcp]dscpt:", dscpt, sizeof(t_mcp_descriptor));
	//hexdump("[do_mcp]KSEG1(dscpt):", KSEG1(dscpt), sizeof(t_mcp_descriptor));

	//hexdump("[do_mcp]src_addr:", dscpt->src_addr, dscpt->length);
#ifdef MCP_DEBUG
	printf("MCP descriptor (addr 0x%x):\n", (UINT32) dscpt);
	printf("word 0: %x\n", dscpt->mode);
	printf("word 1~6:\n");
	for (i = 0; i < sizeof(dscpt->key)/sizeof(int); i++) {
		printf("\t%x\n", dscpt->key[i]);
	}

	printf("word 7~10:\n");
	for (i = 0; i < sizeof(dscpt->ini_key)/sizeof(int); i++) {
		printf("\t%x\n", dscpt->ini_key[i]);
	}

	printf("word 11: %x\n", dscpt->src_addr);
	printf("word 12: %x\n", dscpt->dst_addr);
	printf("word 13: %x\n", dscpt->length);
	//printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
	printf("\nMCP ring buffer registers:\n");
	printf("\tK_MCP_BASE: 0x%x\n\tK_MCP_LIMIT: 0x%x\n\tK_MCP_RDPTR: 0x%x\n\tK_MCP_WRPTR: 0x%x\n",
		REG32(K_MCP_BASE), REG32(K_MCP_LIMIT), REG32(K_MCP_RDPTR), REG32(K_MCP_WRPTR));
#endif

	sync();

	// swap descriptor content (KCPU is little-endian)
	REG32(K_MCP_CTRL) = 0x9;

	// go
	REG32(K_MCP_CTRL) = 0x3;
	count = 0;
	while ((REG32(K_MCP_STATUS) & 0x6) == 0) {
		count++;
		if (count == 0x80000) {
#ifdef MCP_DEBUG
			printf("%s timeout\n", __FUNCTION__);
			printf("REG32(K_MCP_CTRL): 0x%x\n", REG32(K_MCP_CTRL));
			printf("REG32(K_MCP_STATUS): 0x%x\n", REG32(K_MCP_STATUS));
#endif
			return -3;
		}
	}

#ifdef MCP_DEBUG
	printf("mcp done counter: 0x%x\n", count);
	printf("MCP status: 0x%x\n", REG32(K_MCP_STATUS));
#endif

	// check result
	if (REG32(K_MCP_STATUS) & 0x2)
		res = 0;		// ring buffer is empty
	else if (REG32(K_MCP_STATUS) & 0x4)
		res = -1;		// error happened
	else
		res = -2;		// ???

	// clear MCP register
	REG32(K_MCP_CTRL) = 0x2;
	REG32(K_MCP_STATUS) = 0x6;

	//sys_dcache_flush_all();
	//sys_dcache_flush_invalidate_all();

	return res;
}

#if 0
static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	//set_memory(mcp_dscpt, 0, sizeof(mcp_dscpt));
	memset(mcp_dscpt, 0, sizeof(mcp_dscpt));
	return &mcp_dscpt[0];
}
#else
static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
#if 0
	int i;

	//memset((t_mcp_descriptor *)CP_DESCRIPTOR_ADDR, 0, sizeof(t_mcp_descriptor));
	for (i = 0; i < sizeof(t_mcp_descriptor); i += 4)
		REG32(CP_DESCRIPTOR_ADDR + i) = 0;
	return (t_mcp_descriptor *)CP_DESCRIPTOR_ADDR;

#else

	static unsigned int mcp_dscpt_addr;
	t_mcp_descriptor *current;

#ifdef ROM_DEBUG
	prints("===> mcp_dscpt_addr: 0x");
	print_hex(mcp_dscpt_addr);
	prints("\n");
#endif

	// check if pool is full (descriptor address overflow)
	if ((mcp_dscpt_addr + sizeof(t_mcp_descriptor) > CP_DSCPT_POOL_MAX_ADDR)  || (mcp_dscpt_addr == 0)) {
		// wrap-around (allocate from base)
		mcp_dscpt_addr = CP_DSCPT_POOL_BASE_ADDR;
		// reset pool
		memset((char *)CP_DSCPT_POOL_BASE_ADDR, 0, CP_DSCPT_POOL_SIZE);
	}

	current = (t_mcp_descriptor *)mcp_dscpt_addr;
	memset(current, 0, sizeof(t_mcp_descriptor));
	mcp_dscpt_addr += sizeof(t_mcp_descriptor);	// move forward

#ifdef ROM_DEBUG
	prints(__FUNCTION__);
	prints("\n\tmcp_dscpt_addr: 0x");
	print_hex(mcp_dscpt_addr);
	prints(", return dscpt: 0x");
	print_hex((UINT32) current);
	prints("\n");
#endif

	return current;
#endif
}

#endif

static void update_initial_vector(t_mcp_descriptor *dscpt, UINT8 *vector)
{
	if ((dscpt == NULL) || (vector == NULL))
		return;

	dscpt->ini_key[0] = (vector[0] << 24) | (vector[1] << 16) | (vector[2] << 8) | vector[3];
	dscpt->ini_key[1] = (vector[4] << 24) | (vector[5] << 16) | (vector[6] << 8) | vector[7];
	dscpt->ini_key[2] = (vector[8] << 24) | (vector[9] << 16) | (vector[10] << 8) | vector[9];
	dscpt->ini_key[3] = (vector[12] << 24) | (vector[13] << 16) | (vector[14] << 8) | vector[15];
}

static int load_otp(void)
{
	unsigned int i;

	REG32(CP_OTP_LOAD) = 0x1;
	for (i = 0; i < 0x10000; i++) {
		if ((REG32(CP_OTP_LOAD) & 0x1) == 0)
			return 0;
	}
#ifdef MCP_DEBUG
	printf("%s timeout\n", __FUNCTION__);
#endif
	return -1;
}

static int do_k_rcp(t_rcp_descriptor *dscpt)
{
	int i;

	if (dscpt == NULL)
		return -1;

#if defined(RCP_DEBUG)
	printf("RCP descriptor:\n");
	printf("\treg_set: 0x%x\n", dscpt->reg_set);
	printf("\treg_set1: 0x%x\n", dscpt->reg_set1);
	printf("\treg_set2: 0x%x\n", dscpt->reg_set2);
	for (i = 0; i < 4; i++) {
		printf("\tkey[%d]: 0x%x\n", i, dscpt->key[i]);
	}
	for (i = 0; i < 4; i++) {
		printf("\tiv[%d]: 0x%x\n", i, dscpt->iv[i]);
	}
	for (i = 0; i < 4; i++) {
		printf("\tdata_in[%d]: 0x%x\n", i, dscpt->data_in[i]);
	}
#endif

	REG32(K_RCP_REG_SET) = dscpt->reg_set;
	REG32(K_RCP_REG_SET1) = dscpt->reg_set1;
	REG32(K_RCP_REG_SET2) = dscpt->reg_set2;
	for (i = 0; i < 4; i++)
		REG32(K_RCP_REG_KEY + i * 4) = dscpt->key[i];
	for (i = 0; i < 4; i++)
		REG32(K_RCP_REG_IV + i * 4) = dscpt->iv[i];
	for (i = 0; i < 4; i++)
		REG32(K_RCP_REG_DATAIN + i * 4) = dscpt->data_in[i];

	return 0;
}

/*
int RCP_AES_decrypt_flash_protection_key(unsigned int *p_in, unsigned int *p_out)
{
	int res, i;
	t_rcp_descriptor rcp;

	memset(&rcp, 0, sizeof(rcp));
	// AES ECB mode decryption
	rcp.reg_set = REG_SET_WR_EN5 | REG_SET_MODE_AES |
		REG_SET_WR_EN2 | REG_SET_ECB |
		REG_SET_WR_EN1 | REG_SET_FIRST_128 |
		REG_SET_WR_EN0 | REG_SET_DEC;
	// key from CW, input from register, output to register
	rcp.reg_set1 = REG_SET1_KEY_MODE_CW | REG_SET1_INPUT_MODE_REG | REG_SET1_OUTPUT_MODE_REG;
	// flash_protection_root_key in entry 126
	rcp.reg_set2 = REG_SET2_KEY_ENTRY(126);

	// fill input data
	for (i = 0; i < 4; i++) {
		rcp.data_in[i] = p_in[i];
	}

	res = do_k_rcp(&rcp);

	for (i = 0; i < 4; i++) {
		p_out[i] = REG32(K_RCP_REG_DATAOUT + i * 4);
	}

#if defined(RCP_DEBUG)
	printf("%s result:\n", __FUNCTION__);
	for (i = 0; i < 4; i++) {
		printf("\t0x%x,\n", p_out[i]);
	}
#endif
	return res;
}

int RCP_AES_ECB_encrypt(unsigned int *p_in, unsigned int *p_out)
{
	int res, i;
	t_rcp_descriptor rcp;

	memset(&rcp, 0, sizeof(rcp));
	// AES ECB mode decryption
	rcp.reg_set = REG_SET_WR_EN5 | REG_SET_MODE_AES |
		REG_SET_WR_EN2 | REG_SET_ECB |
		REG_SET_WR_EN1 | REG_SET_FIRST_128 |
		REG_SET_WR_EN0 | REG_SET_ENC;
	// key from CW, input from register, output to register
	rcp.reg_set1 = REG_SET1_KEY_MODE_CW | REG_SET1_INPUT_MODE_REG | REG_SET1_OUTPUT_MODE_REG;
	// flash_protection_root_key in entry 126
	rcp.reg_set2 = REG_SET2_KEY_ENTRY(126);

	// fill input data
	for (i = 0; i < 4; i++) {
		rcp.data_in[i] = p_in[i];
	}

	res = do_k_rcp(&rcp);

	for (i = 0; i < 4; i++) {
		p_out[i] = REG32(K_RCP_REG_DATAOUT + i * 4);
	}

#if defined(RCP_DEBUG)
	printf("%s result:\n", __FUNCTION__);
	for (i = 0; i < 4; i++) {
		printf("\t0x%x,\n", p_out[i]);
	}
#endif
	return res;
}
*/

int AES_ECB_decrypt_key_in_CW(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key_entry)
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	dscpt->mode = 0x2005;	// key from CW
	dscpt->key[0] = REG_SET2_KEY_ENTRY(key_entry);
	dscpt->key[1] = 0;
	dscpt->key[2] = 0;
	dscpt->key[3] = 0;
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}
