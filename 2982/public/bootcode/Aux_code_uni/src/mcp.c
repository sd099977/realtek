/****************************************************************************************
* Program Name:     
* Author:               
* Date:                 
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "mcp.h"
#include "cp_reg.h"
#include "reset_def.h"
#include "error_type.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define sys_dcache_flush_all dcache_flush_invalidate

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static t_mcp_descriptor mcp_dscpt[2];

/************************************************************************
 *  External function prototype
 ************************************************************************/

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/
static int do_k_mcp(t_mcp_descriptor *dscpt);
#if 0
static int do_s_mcp(t_mcp_descriptor *dscpt);
static int load_otp(void);
#endif
static t_mcp_descriptor *alloc_mcp_descriptor(void);

/************************************************************************
 *  Function body
 ************************************************************************/
/*======================================================================
 * Func : RCP_WRITE_SRAM
 *
 * Desc : Write 8 Bytes data to internal SRAM
 *
 * Parm : id   : SRAM Entry
 *		  data : SRAM data
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
void RCP_WRITE_SRAM(unsigned int id, unsigned int data[2])
{
#ifdef RCP_DEBUG
	prints("\n======================================");
	prints("\n");
	prints(__FUNCTION__);
#endif

	REG32(CW_TP_REG_INFO) =  data[0];
	REG32(CW_TP_REG_INFO + 4) = data[1];
	REG32(CW_TP_REG_CTRL) = (id | 0x80);  // write 8 bytes
	REG32(CW_TP_REG_INFO) =  0;
	REG32(CW_TP_REG_INFO + 4) = 0;

#if defined(ENV_SIMULATION) || defined(CONFIG_ENV_SIMULATION)
	sim_debug_print(0xdec0de00);
	sim_debug_print(data[0]);
	sim_debug_print(data[1]);
	sim_debug_print(0xdec0deff);
#endif

#ifdef RCP_DEBUG
	prints("\nid (");
	print_hex(id);
	prints(")\n");

	prints("CW_TP_REG_CTRL = ");
	print_hex(REG32(CW_TP_REG_CTRL));

	prints("\nwrite");
	hexdump("data ->", (const void *)data, 8);
	prints("data[0] = ");
	print_hex(data[0]);
	prints(", data[1] = ");
	print_hex(data[1]);
	prints("\n");

	prints("\nread back");
	REG32(CW_TP_REG_CTRL) = id;  // write 8 bytes
	hexdump("data ->", (const void *)CW_TP_REG_INFO, 8);
	prints("data[0] = ");
	print_hex(REG32(CW_TP_REG_INFO));
	prints(", data[1] = ");
	print_hex(REG32(CW_TP_REG_INFO + 4));
	prints("\n======================================");
#endif
}

/*======================================================================
 * Func : RCP_SET_CW
 *
 * Desc : Set Control Word to CW Area
 *
 * Parm : id   : CW Entry offset
 *		  pCW  : CW data
 *		  len  : size of CW data
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int RCP_SET_CW(unsigned int id, unsigned int* pCW, unsigned int len)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(");
	print_hex(id);
	prints(", ");
	print_hex((UINT32) pCW);
	prints(", ");
	print_hex(len);
	prints(")\n");
#endif

	while (len)
	{
		if (len<8)
		{
			RCP_WRITE_SRAM(id++, pCW);
			break;
		}

		RCP_WRITE_SRAM(id++, pCW);
		pCW += 2;
		len -= 8;
	}

	return 0;
}

static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	memset(mcp_dscpt, 0, sizeof(mcp_dscpt));
	return mcp_dscpt;

}

static int do_k_mcp(t_mcp_descriptor *dscpt)
{
	int res;
	unsigned int base_addr;

	if (dscpt == NULL)
		return ERR_INVALID_PARAM;

	sys_dcache_flush_all();
/*
	printf("mode:%x\n", dscpt->mode);
	printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
	printf("base: 0x%x, %p\n", (UINT32) dscpt, (void *)dscpt);
*/

	// disable interrupt
	REG32(K_MCP_EN) = 0xfe;

	// disable go bit
	REG32(K_MCP_CTRL) = 0x2;

	if (IS_IN_CP_SRAM((UINT32) dscpt))
		base_addr = PHYS_CP_SRAM((UINT32) dscpt);
	else
		base_addr = PHYS((UINT32) dscpt);

	// set ring buffer register
	REG32(K_MCP_BASE)  = base_addr;
	REG32(K_MCP_LIMIT) = base_addr + sizeof(t_mcp_descriptor) * 2;
	REG32(K_MCP_RDPTR) = base_addr;
	REG32(K_MCP_WRPTR) = base_addr + sizeof(t_mcp_descriptor);	// writer pointer cannot be equal to limit


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
	printf("\nMCP ring buffer registers:\n");
	printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n",
		REG32(K_MCP_BASE), REG32(K_MCP_LIMIT), REG32(K_MCP_RDPTR), REG32(K_MCP_WRPTR));
#endif

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

#ifdef MCP_DEBUG
	printf("MCP status: 0x%x\n\n", REG32(K_MCP_STATUS));
#elif defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\nMCP status: ");
	print_hex(REG32(K_MCP_STATUS));
	prints("\n");
#endif

	// clear MCP register
	REG32(K_MCP_CTRL) = 0x2;
	REG32(K_MCP_STATUS) = 0x6;

	sys_dcache_flush_all();

	return res;
}

#if 0

static int do_s_mcp(t_mcp_descriptor *dscpt)
{
	int res;

	if (dscpt == NULL)
		return ERR_INVALID_PARAM;

	sys_dcache_flush_all();
/*
	printf("mode:%x\n", dscpt->mode);
	printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
	printf("base: 0x%x, %p\n", (UINT32) dscpt, (void *)dscpt);
*/

	// disable interrupt
	REG32(MCP_EN) = 0xfe;

	// disable go bit
	REG32(MCP_CTRL) = 0x2;

	// set ring buffer register
	//REG32(K_MCP_BASE)  = (((UINT32) dscpt) & 0x0fffffff);
	//REG32(K_MCP_LIMIT) = (((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2) & 0x0fffffff);
	//REG32(K_MCP_RDPTR) = (((UINT32) dscpt) & 0x0fffffff);
	//REG32(K_MCP_WRPTR) = (((UINT32) dscpt + sizeof(t_mcp_descriptor)) & 0x0fffffff);	// writer pointer cannot be equal to limit
	REG32(MCP_BASE)  = PHYS(dscpt);
	REG32(MCP_LIMIT) = PHYS((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2);
	REG32(MCP_RDPTR) = PHYS(dscpt);
	REG32(MCP_WRPTR) = PHYS((UINT32) dscpt + sizeof(t_mcp_descriptor));	// writer pointer cannot be equal to limit


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
	printf("\nMCP ring buffer registers:\n");
	printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n",
		REG32(MCP_BASE), REG32(MCP_LIMIT), REG32(MCP_RDPTR), REG32(MCP_WRPTR));
#endif

	sync();

	// change endian
	REG32(MCP_CTRL) = 0x8;

	// go
	REG32(MCP_CTRL) = 0x3;
	while ((REG32(MCP_STATUS) & 0x6) == 0)
		;

	// check result
	if (REG32(MCP_STATUS) & 0x4)
		res = ERR_MCP_ERROR;	// error happened
	else if (REG32(MCP_STATUS) & 0x2)
		res = 0;		// completed without error
	else
		res = ERR_UNKNOWN_TYPE;	// ???

#ifdef MCP_DEBUG
	printf("MCP status: 0x%x\n\n", REG32(MCP_STATUS));
#elif defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("MCP status: ");
	print_hex(REG32(MCP_STATUS));
	prints("\n");
#endif

	// clear MCP register
	REG32(MCP_CTRL) = 0x2;
	REG32(MCP_STATUS) = 0x6;

	sys_dcache_flush_all();

	return res;
}

static int do_k_mcp_ddr(t_mcp_descriptor *dscpt)
{
	int res;
#if defined(DEBUG)
	int i;
#endif

	if (dscpt == NULL)
		return ERR_INVALID_PARAM;

	// disable interrupt
	REG32(K_MCP_EN) = 0xfe;

	// disable go bit
	REG32(K_MCP_CTRL) = 0x2;

	// set ring buffer register
	REG32(K_MCP_BASE)  = PHYS((UINT32) dscpt);
	REG32(K_MCP_LIMIT) = PHYS((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2);
	REG32(K_MCP_RDPTR) = PHYS((UINT32) dscpt);
	REG32(K_MCP_WRPTR) = PHYS((UINT32) dscpt + sizeof(t_mcp_descriptor));	// writer pointer cannot be equal to limit

#if defined(DEBUG)
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
	printf("\nMCP ring buffer registers:\n");
	printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n", 
		REG32(K_MCP_BASE), REG32(K_MCP_LIMIT), REG32(K_MCP_RDPTR), REG32(K_MCP_WRPTR));
#endif

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
	
#if defined(DEBUG)
	printf("MCP status: 0x%x\n\n", REG32(K_MCP_STATUS));
#endif

	// clear MCP register
	REG32(K_MCP_CTRL) = 0x2;
	REG32(K_MCP_STATUS) = 0x6;
	
	//sys_dcache_flush_all();
	
	return res;
}

static int load_otp(void)
{
	unsigned int i;

	REG32(CP_OTP_LOAD) = 0x1;
	for (i = 0; i < 0x10000; i++) {
		if ((REG32(CP_OTP_LOAD) & 0x1) == 0)
			return 0;
	}

	debug("timeout\n");
	return ERR_TIMEOUT;
}
#endif

int SHA256_hash(unsigned char *src_addr, int length, unsigned char *dst_addr, unsigned int iv[8])
{
	t_mcp_descriptor *dscpt;
	UINT32 from, to;
	int src_in_cp_sram, dst_in_cp_sram;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return ERR_INVALID_PARAM;

	// check if src & dst address in the same Dbus range
	src_in_cp_sram = (IS_IN_CP_SRAM((UINT32)src_addr) ? 1 : 0);
	dst_in_cp_sram = (IS_IN_CP_SRAM((UINT32)dst_addr) ? 1 : 0);
	if ((src_in_cp_sram + dst_in_cp_sram) == 1)
		return ERR_INVALID_PARAM;

	if (src_in_cp_sram) {
		// switch Dbus to SRAM
		REG32(MCP_RW_42K) = 0x1;

		dscpt = alloc_mcp_descriptor();
		if (dscpt == NULL)
				return ERR_ALLOC_FAILED;

		from = PHYS_CP_SRAM((UINT32) src_addr);
		to = PHYS_CP_SRAM((UINT32) dst_addr);
	}
	else {
		// switch Dbus to DDR
		REG32(MCP_RW_42K) = 0;
		// MCP descriptor in fixed address
		dscpt = (t_mcp_descriptor *)CP_DSCPT_DDR;
		set_memory(dscpt, 0, sizeof(t_mcp_descriptor)*2);
		from = PHYS((UINT32) src_addr);
		to = PHYS((UINT32) dst_addr);
	}

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints(__FUNCTION__);
	prints("(");
	print_hex((UINT32) src_addr);
	prints("=");
	print_hex(from);
	prints(", ");
	print_hex(length);
	prints(", ");
	print_hex((UINT32) dst_addr);
	prints("=");
	print_hex(to);
	prints(")\n");
#elif defined(ENV_SIMULATION) || defined(CONFIG_DEBUG_SIMULATION_PRINT)
	sim_debug_print(0x5a5a0256);
	sim_debug_print(from);
	sim_debug_print(to);
	sim_debug_print(length);
	sim_debug_print(0x5a5affff);
#endif

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
	return do_k_mcp(dscpt);
}

int AES_decrypt_key_in_CW(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry)
{
	unsigned int mode;
	int src_in_cp_sram, dst_in_cp_sram;
	t_mcp_descriptor *dscpt;
	unsigned int from , to;

#if defined(DEBUG)
	printf("%s(0x%x, 0x%x, 0x%x, 0x%x, key_entry=0x%x)\n", __FUNCTION__, algo_id, (unsigned int)src_addr, length, (unsigned int)dst_addr, key_entry);
#endif
	if ((src_addr == NULL) || (dst_addr == NULL))
		return ERR_INVALID_PARAM;

	// check if src & dst address in the same Dbus range
	src_in_cp_sram = (IS_IN_CP_SRAM((unsigned int)src_addr) ? 1 : 0);
	dst_in_cp_sram = (IS_IN_CP_SRAM((unsigned int)dst_addr) ? 1 : 0);
	if ((src_in_cp_sram + dst_in_cp_sram) == 1)
		return ERR_INVALID_PARAM;

	if (src_in_cp_sram) {
		// switch Dbus to SRAM
		REG32(MCP_RW_42K) = 0x1;

		if ((dscpt = alloc_mcp_descriptor()) == NULL)
			return ERR_INVALID_PARAM;

		from = PHYS_CP_SRAM((UINT32) src_addr);
		to = PHYS_CP_SRAM((UINT32) dst_addr);
	}
	else {
		// switch Dbus to DDR
		REG32(MCP_RW_42K) = 0;
		// MCP descriptor in fixed address
		dscpt = (t_mcp_descriptor *)CP_DSCPT_DDR;
		set_memory(dscpt, 0, sizeof(t_mcp_descriptor)*2);
		from = PHYS((UINT32) src_addr);
		to = PHYS((UINT32) dst_addr);
	}

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

	return do_k_mcp(dscpt);
}
