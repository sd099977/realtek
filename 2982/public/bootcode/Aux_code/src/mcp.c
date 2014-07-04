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

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void (*rom_sync)(void);
extern int (*rom_SHA256_hash)(unsigned char *src_addr, int length, unsigned char *dst_addr, unsigned int iv[8]);
extern int (*rom_AES_decrypt_key_in_CW)(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

static int do_k_mcp_ddr(t_mcp_descriptor *dscpt)
{
#if defined(DEBUG)
	int i;
	printf("%s\n", __FUNCTION__);
#endif
	int res;

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

	rom_sync();

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

int SHA256_hash(unsigned char *src_addr, int length, unsigned char *dst_addr, unsigned int iv[8])
{
	int res;
	int src_in_cp_sram, dst_in_cp_sram;
	t_mcp_descriptor *dscpt;

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
		res = rom_SHA256_hash(src_addr, length, dst_addr, iv);
	}
	else {
		// switch Dbus to DDR
		REG32(MCP_RW_42K) = 0;
		// MCP descriptor in fixed address
		dscpt = (t_mcp_descriptor *)CP_DSCPT_DDR;
		set_memory(dscpt, 0, sizeof(t_mcp_descriptor)*2);
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
	
		dscpt->src_addr = PHYS((unsigned int) src_addr);
		dscpt->dst_addr = PHYS((unsigned int) dst_addr);
		dscpt->length = length;
		res = do_k_mcp_ddr(dscpt);
	}

	return res;
}

int AES_decrypt_key_in_CW(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry)
{
	int res;
	unsigned int mode;
	int src_in_cp_sram, dst_in_cp_sram;
	t_mcp_descriptor *dscpt;

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
		res = rom_AES_decrypt_key_in_CW(algo_id, src_addr, length, dst_addr, key_entry);
	}
	else {
		// switch Dbus to DDR
		REG32(MCP_RW_42K) = 0;
		// MCP descriptor in fixed address
		dscpt = (t_mcp_descriptor *)CP_DSCPT_DDR;
		set_memory(dscpt, 0, sizeof(t_mcp_descriptor)*2);

		if (algo_id == ALGO_ID_AES_ECB)
			mode = MCP_BCM_ECB;
		else if (algo_id == ALGO_ID_AES_CBC)
			mode = MCP_BCM_CBC;
		else
			return ERR_UNKNOWN_TYPE;

		dscpt->mode = mode | (MCP_KEY_FROM_CW | MCP_DECRYPT | MCP_MODE_AES);
		dscpt->key[0] = REG_SET2_KEY_ENTRY(key_entry);
		dscpt->src_addr = PHYS(src_addr);
		dscpt->dst_addr = PHYS(dst_addr);
		dscpt->length = length;
		res = do_k_mcp_ddr(dscpt);
	}

	return res;
}
