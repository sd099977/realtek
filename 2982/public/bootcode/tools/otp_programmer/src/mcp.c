
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

#include <stdio.h>
#include "mcp.h"
#include "util.h"

/************************************************************************
 *  Definitions
 ************************************************************************/


/************************************************************************
 *  Public variables
 ************************************************************************/


/************************************************************************
 *  Static variables
 ************************************************************************/


/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int do_mcp(t_mcp_descriptor *dscpt);
static t_mcp_descriptor *alloc_mcp_descriptor(void);
static void update_initial_vector(t_mcp_descriptor *dscpt, unsigned char *vector);
static int load_otp(void);

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/


int AES_CBC_decrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4])
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
	dscpt->src_addr = (unsigned int) src_addr;
	dscpt->dst_addr = (unsigned int) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_CBC_encrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4])
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
	dscpt->src_addr = (unsigned int) src_addr;
	dscpt->dst_addr = (unsigned int) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_decrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4])
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
	dscpt->src_addr = (unsigned int) src_addr;
	dscpt->dst_addr = (unsigned int) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_encrypt(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key[4])
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
	dscpt->src_addr = (unsigned int) src_addr;
	dscpt->dst_addr = (unsigned int) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_hash(unsigned char *src_addr, int length, unsigned char *dst_addr, int block_size)
{
	t_mcp_descriptor *dscpt;
	unsigned char *src_ptr;
	
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
	dscpt->dst_addr = (unsigned int) dst_addr;
	
	while (length > 0) {
		dscpt->src_addr = (unsigned int) src_ptr;
		dscpt->length = length < block_size ? length: block_size;
		length -= block_size;
		
		if (do_mcp(dscpt))
			return -1;
		
		if (length > 0) {
			// update descriptor for next block
			update_initial_vector(dscpt, (unsigned char *)dst_addr);
			src_ptr += dscpt->length;
		} 
		else
			break;
	}
	
	return 0;
}


static int do_mcp(t_mcp_descriptor *dscpt)
{
	int res = -1;
	unsigned int count;
	
	if (dscpt == NULL)
		return -1;
	
	//sys_dcache_flush_all();
#ifdef MCP_DEBUG
	printf("mode:%x\n", dscpt->mode);
	printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
	printf("base: 0x%x, %p\n", (unsigned int) dscpt, (void *)dscpt);
#endif

#if 0
	print_uart("[");
	print_val(dscpt->mode);
	print_uart(",");
	for (res = 0; res < 6; res++) {
		print_val(dscpt->key[res]);
		print_uart(",");
	}
	for (res = 0; res < 4; res++) {
		print_val(dscpt->ini_key[res]);
		print_uart(",");
	}
	print_val(dscpt->src_addr);
	print_uart(",");
	print_val(dscpt->dst_addr);
	print_uart(",");
	print_val(dscpt->length);
	print_uart("]\n");
#endif

	// disable interrupt
	REG32(MCP_EN) = 0xfe;

	// set ring buffer register
	REG32(MCP_BASE)  = (unsigned int) dscpt;
	REG32(MCP_LIMIT) = (unsigned int) dscpt + sizeof(t_mcp_descriptor) * 2;
	REG32(MCP_RDPTR) = (unsigned int) dscpt;
	REG32(MCP_WRPTR) = (unsigned int) dscpt + sizeof(t_mcp_descriptor);	// writer pointer cannot be equal to limit

	// go
	REG32(MCP_CTRL) = 0x3;	
	count = 0;
	while ((REG32(MCP_STATUS) & 0x6) == 0) {
		count++;
		if (count == 0x100000)
			return -3;
	}

#ifdef MCP_DEBUG
	printf("mcp done counter: 0x%x\n", count);
	printf("MCP status: 0x%x\n", REG32(MCP_STATUS));
#endif
	
	// check result
	if (REG32(MCP_STATUS) & 0x2)
		res = 0;		// ring buffer is empty
	else if (REG32(MCP_STATUS) & 0x4)
		res = -1;		// error happened
	else
		res = -2;		// ???
	
	// clear MCP register
	REG32(MCP_CTRL) = 0x2;
	REG32(MCP_STATUS) = 0x6;
	
	//sys_dcache_flush_all();
	
	return res;
}


static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	t_mcp_descriptor *dscpt;
	int i;

	dscpt = (t_mcp_descriptor *)0xa3ff0000;
	for (i = 0; i < sizeof(t_mcp_descriptor); i+=4)
		REG32(0xa3ff0000 + i) = 0;
	
	return dscpt;
}


static void update_initial_vector(t_mcp_descriptor *dscpt, unsigned char *vector)
{
	if ((dscpt == NULL) || (vector == NULL))
		return;
	
	dscpt->ini_key[0] = (vector[0] << 24) | (vector[1] << 16) | (vector[2] << 8) | vector[3];
	dscpt->ini_key[1] = (vector[4] << 24) | (vector[5] << 16) | (vector[6] << 8) | vector[7];
	dscpt->ini_key[2] = (vector[8] << 24) | (vector[9] << 16) | (vector[10]<< 8) | vector[9];
	dscpt->ini_key[3] = (vector[12]<< 24) | (vector[13]<< 16) | (vector[14]<< 8) | vector[15];
}

static int load_otp(void)
{
	unsigned int i;
	
	REG32(MCP_OTP_LOAD) = 0x1;
	for (i = 0; i < 0x10000; i++) {
		if ((REG32(MCP_OTP_LOAD) & 0x1) == 0)
			return 0;
	}
	
	printf("%s timeout\n", __FUNCTION__);
	return -1;
}
