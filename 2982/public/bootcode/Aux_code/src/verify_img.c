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
#include "error_type.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int *rom_alloc_count;
extern unsigned int *rom_alloc_current;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int (*rom_compare_memory)(void *s1, void *s2, unsigned int size);
extern int (*rom_check_image_hash)(char *p_img, unsigned int img_size, char *p_hash);
extern int (*rom_verify_image_signature)(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
extern int (*rom_append_padding)(char *p_buff, const unsigned int length);
extern unsigned int (*rom_do_RSA)(const unsigned int signature_addr, const unsigned int rsa_key_addr, const unsigned int rsa_key_addr_r2, const unsigned int output_addr);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int check_image_hash(char *p_img, unsigned int img_size, char *p_img_hash, char *p_mcp_sha256)
{
	int res;
	unsigned char *result = (unsigned char *)p_mcp_sha256;	// MCP SHA256 buffer

	// append padding after image
	res = rom_append_padding((p_img + img_size), img_size);
	if (res == -1)
		return ERR_INVALID_PARAM;
	else {
#if defined(DEBUG)
		hexdump("padding", (p_img + img_size), res);
#endif
		img_size += res;
	}

	// calculate image SHA256 hash value
	if ((res = SHA256_hash((unsigned char*)p_img, img_size, result, NULL)))
		return res;
	
	// compare hash value match?
	res = rom_compare_memory(result, p_img_hash, SHA256_SIZE) ? ERR_NOT_MATCH : 0;

#if defined(DEBUG)
	hexdump("result", result, SHA256_SIZE);
	hexdump("p_img_hash", p_img_hash, SHA256_SIZE);
#endif

	return res;
}

int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256)
{
	int res;
	unsigned char *hash0 = (unsigned char *)p_mcp_sha256;	// hash value calculated by CP
	unsigned char *hash2;	// hash value recovered by RSA
	unsigned char rsa_output[256];	//RSA output buffer
	unsigned int tmp;
	//@TODO:
	// append padding after image
	res = rom_append_padding((p_img + img_size), img_size);
	if (res == -1)
		return ERR_INVALID_PARAM;
	else {
#if defined(DEBUG)
		hexdump("padding", (p_img + img_size), res);
#endif
		img_size += res;
	}

	if (p_rsa_key == NULL)
		return ERR_INVALID_PARAM;

	/* calculate image hash value */
	if ((res = SHA256_hash((unsigned char *)p_img, img_size, hash0, NULL)))
		return res;

#if defined(DEBUG)
	hexdump("hash0 from CP", (char *)hash0, SHA256_SIZE);
#endif

#if defined(DEBUG)
	hexdump("signature", (char *)p_sig, RSA_SIZE);
#endif

#if defined(DEBUG)
	hexdump("rsa key", (char *)p_rsa_key, RSA_SIZE);
#endif

#if defined(DEBUG)
	hexdump("rsa key r2", (char *)p_rsa_key_r2, RSA_SIZE);
#endif

	*rom_alloc_count = 0;
	*rom_alloc_current = 0;
	
	/* recover hash value from RSA signature */
	tmp = rom_do_RSA((unsigned int)p_sig, (unsigned int)p_rsa_key, (unsigned int)p_rsa_key_r2, (const unsigned int)rsa_output);
	hash2 = (unsigned char *)tmp;

#if defined(DEBUG)
	hexdump("rsa_output from RSA output", (char *)rsa_output, 0x100);
	hexdump("hash2 recovered by RSA", (char *)hash2, SHA256_SIZE);
#endif

	/* compare hash value match? */
	res = (rom_compare_memory(hash0, hash2, SHA256_SIZE) ? ERR_NOT_MATCH : 0);
	return res;
}
