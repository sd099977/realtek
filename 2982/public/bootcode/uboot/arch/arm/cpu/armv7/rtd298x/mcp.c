
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
#include <common.h>
#include <asm/arch/system.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/flash_writer_u/otp_reg.h>
#include <asm/arch/flash_writer_u/rsa_key_2048_big.h>
#include <asm/arch/flash_writer_u/rsa_key_2048_little.h>
#include <asm/arch/flash_writer_u/error_type.h>
#include <asm/arch/flash_writer_u/big_util.h>

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned int mcp_dscpt_addr;
const unsigned int Kh_key_default[4] = { SECURE_KH_KEY0, SECURE_KH_KEY1, SECURE_KH_KEY2, SECURE_KH_KEY3 };

/************************************************************************
 *  Public function
 ************************************************************************/
//extern void sys_dcache_flush_all(void);

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
#if 0 // cklai@mark unused code
static void update_initial_vector(t_mcp_descriptor *dscpt, unsigned char * vector);
#endif
static int load_otp(void);
static int do_AES_key_in_CW(unsigned int algo_id, unsigned int mode_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry);

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/
static int do_AES_key_in_CW(unsigned int algo_id, unsigned int mode_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry)
{
	unsigned int mode;
	t_mcp_descriptor *dscpt;
	unsigned int from, to;

	if ((src_addr == NULL) || (dst_addr == NULL))
		return ERR_INVALID_PARAM;

	dscpt = alloc_mcp_descriptor();

	from = PHYS((unsigned int) src_addr);
	to = PHYS((unsigned int) dst_addr);

	if (algo_id == ALGO_ID_AES_ECB)
		mode = MCP_BCM_ECB;
	else if (algo_id == ALGO_ID_AES_CBC)
		mode = MCP_BCM_CBC;
	else
		return ERR_UNKNOWN_TYPE;

	dscpt->mode = mode | (MCP_KEY_FROM_CW | mode_id | MCP_MODE_AES);
	dscpt->key[0] = REG_SET2_KEY_ENTRY(key_entry);
	dscpt->key[1] = dscpt->key[2] = dscpt->key[3] = 0;
	dscpt->length = length;
	dscpt->src_addr = from;
	dscpt->dst_addr = to;

    return do_mcp(dscpt);
}

int AES_CBC_decrypt1 
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],unsigned int ini_key[4])
{
    t_mcp_descriptor *dscpt;

    dscpt = alloc_mcp_descriptor();
    if (dscpt == NULL)
            return -1;

    if (key == NULL) {
        if (load_otp())
            return -2;

        dscpt->mode = 0x1045;   // key from OTP
    }
    else {
        dscpt->mode = 0x0045;   // key from descriptor
        dscpt->key[0] = key[0];
        dscpt->key[1] = key[1];
        dscpt->key[2] = key[2];
        dscpt->key[3] = key[3];

        dscpt->ini_key[0] = ini_key[0];
        dscpt->ini_key[1] = ini_key[1];
        dscpt->ini_key[2] = ini_key[2];
        dscpt->ini_key[3] = ini_key[3];
    }
    
    dscpt->src_addr = (unsigned int) src_addr;
    dscpt->dst_addr = (unsigned int) dst_addr;
    dscpt->length = length;
    return do_mcp(dscpt);
}


int AES_CBC_encrypt1 
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],unsigned int ini_key[4])
{
    t_mcp_descriptor *dscpt;

    dscpt = alloc_mcp_descriptor();
    if (dscpt == NULL)
            return -1;

    if (key == NULL) {
        if (load_otp())
            return -2;

        dscpt->mode = 0x1065;   // key from OTP
    }
    else {
        dscpt->mode = 0x0065;   // key from descriptor
        dscpt->key[0] = key[0];
        dscpt->key[1] = key[1];
        dscpt->key[2] = key[2];
        dscpt->key[3] = key[3];

        dscpt->ini_key[0] = ini_key[0];
        dscpt->ini_key[1] = ini_key[1];
        dscpt->ini_key[2] = ini_key[2];
        dscpt->ini_key[3] = ini_key[3];
    }
    
    dscpt->src_addr = (unsigned int) src_addr;
    dscpt->dst_addr = (unsigned int) dst_addr;
    dscpt->length = length;
    return do_mcp(dscpt);
}

int AES_CBC_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4])
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

int AES_CBC_decrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry)
{
	return do_AES_key_in_CW(ALGO_ID_AES_CBC, MCP_DECRYPT, src_addr, length, dst_addr, key_entry);
}

int AES_CBC_encrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry)
{
	return do_AES_key_in_CW(ALGO_ID_AES_CBC, MCP_ENCRYPT, src_addr, length, dst_addr, key_entry);
}

int AES_ECB_decrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry)
{
	return do_AES_key_in_CW(ALGO_ID_AES_ECB, MCP_DECRYPT, src_addr, length, dst_addr, key_entry);
}

int AES_ECB_encrypt_key_in_CW(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key_entry)
{
	return do_AES_key_in_CW(ALGO_ID_AES_ECB, MCP_ENCRYPT, src_addr, length, dst_addr, key_entry);
}

#if 0 // cklai@mark unused code
int AES_CBC_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4])
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
#endif

#if 1 // cklai@mark unused code
int AES_ECB_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4])
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
	dscpt->src_addr = PHYS((unsigned int) src_addr);
	dscpt->dst_addr = PHYS((unsigned int) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}
#endif


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


#if 0 // cklai@mark unused code
int AES_hash_one(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr)
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
	dscpt->src_addr = PHYS((unsigned int) src_addr);
	dscpt->dst_addr = PHYS((unsigned int) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}
#endif


#if 0 // cklai@mark unused code
int AES_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int block_size)
{
	t_mcp_descriptor *dscpt;
	unsigned char * src_ptr;
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
	dscpt->dst_addr = (unsigned int) dst_addr;

	res = 0;
	while (length > 0) {
		dscpt->src_addr = (unsigned int) src_ptr;
		dscpt->length = length < block_size ? length: block_size;
		length -= block_size;

		res = do_mcp(dscpt);
		if (res)
			return res;

		if (length > 0) {
			// update descriptor for next block
			update_initial_vector(dscpt, (unsigned char *)dst_addr);
			src_ptr += dscpt->length;
		}
		else
			break;
	}

	return res;
}
#endif


#if 0 // cklai@mark unused code
int SHA1_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int iv[5])
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

	dscpt->src_addr = PHYS((unsigned int) src_addr);
	dscpt->dst_addr = PHYS((unsigned int) dst_addr);
	dscpt->length = length;


	return do_mcp(dscpt);
}
#endif

int SHA256_padding(char *p_buff, const unsigned int length)
{
   unsigned long long bit_len;
   int pad_len;

   if ((length == 0) || (p_buff == NULL)) {
      return -1;
   }

   // calculate padding length
   pad_len = 64 - (length & 0x3f);
   if (pad_len <= 8)
      pad_len += 64;

   bit_len = (unsigned long long)(length << 3);

   // fill padding pattern
   memset(p_buff, 0, pad_len);
   *p_buff = 0x80;

   // pad bit length in big endian format
   p_buff   += pad_len - 8;
   *p_buff++ = (bit_len >> 56) & 0xFF;
   *p_buff++ = (bit_len >> 48) & 0xFF;
   *p_buff++ = (bit_len >> 40) & 0xFF;
   *p_buff++ = (bit_len >> 32) & 0xFF;
   *p_buff++ = (bit_len >> 24) & 0xFF;
   *p_buff++ = (bit_len >> 16) & 0xFF;
   *p_buff++ = (bit_len >>  8) & 0xFF;
   *p_buff++ = (bit_len)       & 0xFF;

   return pad_len;
}

int SHA256_hash(unsigned char * src_addr, unsigned int length, unsigned char *dst_addr, unsigned int iv[8])
{
	t_mcp_descriptor *dscpt;

	if ((src_addr == NULL) || (dst_addr == NULL)) {
		return ERR_INVALID_PARAM;
	}

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL) {
	        return ERR_ALLOC_FAILED;
    }

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
	return do_mcp(dscpt);
}

int Verify_SHA256_hash( unsigned char * src_addr, unsigned int length, unsigned char * ref_sha256, unsigned int do_recovery )
{
	unsigned int ret = 0;
	unsigned char * hash1; // hash value calculated by CP engine
	unsigned char * hash2; // hash value recovery from RSA signature
	unsigned int signature_key_address;
	unsigned int sys_rsa_key_address;
	int padding_len = 0;

	#if 0
		sys_rsa_key_address = OTP_DATA;
	#else
		#if 1 // little endian
			//sys_rsa_key_address = (unsigned int)rsa_key_2048_little;
			sys_rsa_key_address = 0; //use string as input
		#else // big endian
			sys_rsa_key_address = (unsigned int)rsa_key_2048_big;
		#endif
	#endif

	// if length is un-aligned, do the padding
	padding_len = SHA256_padding(src_addr + length, length);
//	rtk_hexdump("hash 256 padding", src_addr + length, padding_len);
	length += padding_len;

	signature_key_address = (unsigned int)ref_sha256;

	mcp_dscpt_addr = 0;
	hash1 = (unsigned char *)SECURE_IMAGE2HASH_BUF; // temp use this address (use malloc is better?)
	hash2 = (unsigned char *)signature_key_address;

	flush_dcache_all();

	ret = SHA256_hash((unsigned char *)src_addr, length, hash1, NULL);
	if( ret ) {
		printf("[ERR] %s: caculate hash1 fail(%d)\n", __FUNCTION__, ret );
		return -1;
	}

	if( do_recovery ) {
		//rtk_hexdump("signature form ref_sha256", ref_sha256, 256 );
		//rtk_hexdump("RSA key", (unsigned char *)sys_rsa_key_address, 256 );
		ret = do_RSA( signature_key_address, sys_rsa_key_address, SECURE_SIGN2HASH_BUF );
		if( ret == 0 ) {
			printf("[ERR] %s: do_RSA return 0\n", __FUNCTION__ );
			return -3;
		}
		hash2 = (unsigned char *)ret;
	}

	ret = memcmp(hash1, hash2, 32);
	if( ret ) {
		printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
		rtk_hexdump("hash 1", hash1, 32 );
		rtk_hexdump("hash 2", hash2, 32 );
		return -2;
	}

	return 0;
}

static int do_mcp(t_mcp_descriptor *dscpt)
{
#ifdef MCP_DEBUG
	int i;
#endif
	int res;
	int count;
	unsigned int org;

	if (dscpt == NULL)
		return -1;

	flush_dcache_all();

	// disable interrupt
	rtd_outl(K_MCP_EN, 0xfe);

	// disable go bit
	rtd_outl(K_MCP_CTRL, 0x2);


	// change to DBUS
	org = rtd_inl(MCP_RW_42K);
	rtd_outl(MCP_RW_42K, org & (~0x1));

	// set ring buffer register
	rtd_outl(K_MCP_BASE, PHYS(((unsigned int) dscpt)) );
	rtd_outl(K_MCP_LIMIT, PHYS(((unsigned int) dscpt + sizeof(t_mcp_descriptor) * 2) ));
	rtd_outl(K_MCP_RDPTR, PHYS(((unsigned int) dscpt) ));
	rtd_outl(K_MCP_WRPTR, PHYS(((unsigned int) dscpt + sizeof(t_mcp_descriptor)) )); // writer pointer cannot be equal to limit

	////flush_cache((unsigned long)dscpt, sizeof(t_mcp_descriptor));

	//hexdump("[do_mcp]dscpt:", dscpt, sizeof(t_mcp_descriptor));
	//hexdump("[do_mcp]KSEG1(dscpt):", KSEG1(dscpt), sizeof(t_mcp_descriptor));

	//hexdump("[do_mcp]src_addr:", dscpt->src_addr, dscpt->length);
#ifdef MCP_DEBUG
	printf("MCP descriptor (addr 0x%x):\n", (unsigned int) dscpt);
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
	printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n",
		rtd_inl(K_MCP_BASE), rtd_inl(K_MCP_LIMIT), rtd_inl(K_MCP_RDPTR), rtd_inl(K_MCP_WRPTR));
#endif

	//asm(".set mips3");
	asm("DSB");
	//asm(".set mips1");

	// change endian
	//rtd_outl(K_MCP_CTRL, 0x8); //we don't have to do this due to SCPU is little endian

	// go
	rtd_outl(K_MCP_CTRL, 0x3);
	count = 0;
	while ((rtd_inl(K_MCP_STATUS) & 0x6) == 0) {
		count++;
		if (count == 0x800000) {
#ifdef MCP_DEBUG
			printf("%s timeout\n", __FUNCTION__);
			printf("REG32(MCP_CTRL): 0x%x\n", rtd_inl(K_MCP_CTRL));
			printf("REG32(MCP_STATUS): 0x%x\n", rtd_inl(K_MCP_STATUS));
#endif
			return -3;
		}
	}

#ifdef MCP_DEBUG
	printf("mcp done counter: 0x%x\n", count);
	printf("MCP status: 0x%x\n", rtd_inl(K_MCP_STATUS));
#endif

	// check result
	if (rtd_inl(K_MCP_STATUS) & 0x2)
		res = 0;		// ring buffer is empty
	else if (rtd_inl(K_MCP_STATUS) & 0x4)
		res = -1;		// error happened
	else
		res = -2;		// ???

	// clear MCP register
	rtd_outl(K_MCP_CTRL, 0x2);
	rtd_outl(K_MCP_STATUS, 0x6);
	//restore
	rtd_outl(MCP_RW_42K, org);

//	sys_dcache_flush_all();

	return res;
}

static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	//static unsigned int mcp_dscpt_addr;
	t_mcp_descriptor *current;

#ifdef MCP_DEBUG
	printf("===> mcp_dscpt_addr: 0x%x\n", mcp_dscpt_addr);
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

#ifdef MCP_DEBUG
	printf("%s\n\tmcp_dscpt_addr: 0x%x, return dscpt: 0x%x\n", __FUNCTION__, mcp_dscpt_addr, (unsigned int) current);
#endif

	return current;

}


#if 0 // cklai@mark unused code
static void update_initial_vector(t_mcp_descriptor *dscpt, unsigned char * vector)
{
	if ((dscpt == NULL) || (vector == NULL))
		return;

	dscpt->ini_key[0] = (vector[0] << 24) | (vector[1] << 16) | (vector[2] << 8) | vector[3];
	dscpt->ini_key[1] = (vector[4] << 24) | (vector[5] << 16) | (vector[6] << 8) | vector[7];
	dscpt->ini_key[2] = (vector[8] << 24) | (vector[9] << 16) | (vector[10] << 8) | vector[9];
	dscpt->ini_key[3] = (vector[12] << 24) | (vector[13] << 16) | (vector[14] << 8) | vector[15];
}
#endif

static int load_otp(void)
{
	unsigned int i;
    static int flag=0;

    if (flag==0)
    {
    	rtd_outl(CP_OTP_LOAD, 0x1);
    	for( i = 0; i < 0x10000; i++ ) {
    		if ((rtd_inl(CP_OTP_LOAD) & 0x1) == 0) {
                flag=1;
    			return 0;
    		}
    	}
        #if 1 //#ifdef MCP_DEBUG
        printf("%s timeout\n", __FUNCTION__);
        #endif
        return -1;
    }
    else
    {
        return 0;
    }
}

int reload_otp(void)
{
	unsigned int i;

    {
    	rtd_outl(CP_OTP_LOAD, 0x1);
    	for( i = 0; i < 0x10000; i++ ) {
    		if ((rtd_inl(CP_OTP_LOAD) & 0x1) == 0) {
    			return 0;
    		}
    	}
        #if 1 //#ifdef MCP_DEBUG
        printf("reload %s timeout\n", __FUNCTION__);
        #endif
        return -1;
    }
}

void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length )
{
	unsigned int i, j, rows, count;
	printf("======================================================\n");
	printf("%s(base=0x%08x)\n", str, (unsigned int)(pcBuf));
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		printf("%03x :", i<<4 );
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			printf(" %02x",  *pcBuf );
			count++;
			pcBuf++;
		}
		printf("\n");
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
