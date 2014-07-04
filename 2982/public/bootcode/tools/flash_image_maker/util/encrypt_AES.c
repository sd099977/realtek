
/***********************************************************************
 *
 *  encrypt_AES.c
 *
 *  Encrypt image with AES algorithm
 *
 *
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/

#include <sysdefs.h>
//#include <string.h>
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


/************************************************************************
 *  External function prototypes
 ************************************************************************/


/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/


/*
 *
 * Encrypt image with AES CBC mode
 * (also handle short block)
 *
 * Input:
 *	src	pointer to source image
 *	dst	pointer to destination of encrypted data
 *	length	source image length
 *	key	AES key (use Efuse instead if NULL)
 *
 * Return:
 *	0	success
 *	-1	fail
 *
 */
int encrypt_image_CBC(UINT8 *src, UINT8 *dst, UINT32 length, UINT32 *key)
{
	int i, res;
	UINT32 sblock_len;
	UINT8 *sblock_dst, *sblock_src;
	UINT32 reversed_key[4];

	printf("encrypt from 0x%x to 0x%x, len:0x%x\n", (UINT32)src, (UINT32)dst, length);
	memset(reversed_key, 0, sizeof(reversed_key));
	for (i = 0; i < sizeof(reversed_key)/sizeof(UINT32); i++)
		reversed_key[i] = BE32_TO_CPU(key[i]);

	// get short block size
	sblock_len = length & 0xf;

	res = AES_CBC_encrypt((UINT8 *)src, length - sblock_len, (UINT8 *)dst, reversed_key);
	if (res)
		return res;

	// handle short block (<16B)
	if (sblock_len) {
		// take the last 16B of AES CBC result as input, do AES ECB encrypt
		sblock_src = src + (length - sblock_len);
		sblock_dst = dst + (length - sblock_len);
		//printf("sblock_src: 0x%p, sblock_dst: 0x%p\n", sblock_src, sblock_dst);
		res = AES_ECB_encrypt((UINT8 *)(sblock_dst - 16), 16, sblock_dst, reversed_key);
		if (res)
			return res;

		// XOR with short block data to generate encrypted result
		for (i = 0; i < sblock_len; i++)
			sblock_dst[i] ^= sblock_src[i];
	}

	return 0;
}
