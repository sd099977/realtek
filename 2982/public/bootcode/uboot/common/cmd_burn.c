#include <command.h>
#include <common.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/flash_writer_u/otp_reg.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/system.h>
#include <malloc.h>
#include <burn.h>

#ifndef AUTO_UPDATE_MAC_HDCP
#include <yek.h> //For secure reasion, yek.h can't store in svn.
#else
//Fake key define for avoid compile error
#define SECURE_KEY0       0
#define SECURE_KEY1       0
#define SECURE_KEY2       0
#define SECURE_KEY3       0

#define UART_AES_KEY_0    0
#define UART_AES_KEY_1    0
#define UART_AES_KEY_2    0
#define UART_AES_KEY_3    0

#define S_AES_KEY_0       0
#define S_AES_KEY_1       0
#define S_AES_KEY_2       0
#define S_AES_KEY_3       0

#define K_AES_KEY_0       0
#define K_AES_KEY_1       0
#define K_AES_KEY_2       0
#define K_AES_KEY_3       0

#define N_AES_KEY_0       0
#define N_AES_KEY_1       0
#define N_AES_KEY_2       0
#define N_AES_KEY_3       0
#endif


int do_burn_hdcp_xx(unsigned int hdcp_ver);
int do_burn_hdcp_xx_l54xx(unsigned int hdcp_ver);

#define _KEY_PRE_ENCRYPT

typedef enum {
	PROJECT_L4300 = 0,
	PROJECT_MOZART,
	PROJECT_GENERIC,
} TARGET_MODEL_T;

unsigned int burn_aes_key[4]=
{
	SECURE_KH_KEY0,
	SECURE_KH_KEY1,
	SECURE_KH_KEY2,
	SECURE_KH_KEY3
};

unsigned char buffer[512];

const unsigned char test_pattern[16] =
{ 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'C', 'C', 'C', 'C', 'D', 'D', 'D', 'D', };
const unsigned char n_enc_test_pattern[16] =
{0x08,0xA4,0x97,0xFB,0x19,0x4B,0x1E,0xB7,0xEB,0xC4,0x37,0x4F,0x29,0xCA,0x3C,0xBA, };
const unsigned char s_enc_test_pattern[16] =
{0x41,0xE0,0x04,0xC6,0x38,0xF5,0x24,0x32,0x1D,0xF8,0x33,0xFA,0x8C,0x1C,0x2E,0xB4, };

static int otp_aes_key_is_programmed;

//#define _DEBUG_CMD_BURN

#if defined(_DEBUG_CMD_BURN)
void hexdump(const void *buf, unsigned int length)
{
	unsigned int i;
	unsigned char *ptr = (unsigned char *)buf;

	if ((buf == NULL) || (length == 0))
	{
		printf("NULL\n");
		return;
	}

	printf("===> %s(0x%x, 0x%x):\n", __FUNCTION__, (unsigned int)buf, length);
	for (i = 0; i < length; i++)
	{
		printf("%02X ", ptr[i]);

		if ((i & 0xf) == 0xf)
		{
			printf("\n");
		}
	}
	printf("\n");
}
#endif

void clear_buffer(void *p,unsigned int s)
{
	memset(p, 0 , s);
	flush_cache(p, s);
	return;
}

unsigned int burn_cal_checksum( unsigned int start_address, unsigned int len )
{
	unsigned int i, checksum = 0;
	unsigned char * pcBuf = (unsigned char *) start_address;
	for( i=0; i<len; i++ )
	{
		checksum += pcBuf[i];
	}
	return checksum;
}

unsigned int burn_get_checksum( unsigned int checksum_address )
{
	unsigned int checksum_ref = 0;
	unsigned char * pcBuf = (unsigned char *) checksum_address;
	checksum_ref = pcBuf[0];
	checksum_ref = (checksum_ref<<8) | pcBuf[1];
	checksum_ref = (checksum_ref<<8) | pcBuf[2];
	checksum_ref = (checksum_ref<<8) | pcBuf[3];
	return checksum_ref;
}

int do_burn_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],int type)
{
	int ret;
	unsigned int key_tmp[4] = {0, 0, 0, 0};

	if ((src_addr == NULL) || (length == NULL) || (dst_addr == NULL))
	{
		return 1;
	}

	flush_cache( src_addr, length );
	flush_cache( dst_addr, length );
	if (key)
	{
		flush_cache( key, 16 );
	}

	if (type == ENCRYPTION_AES_128_ECB)
	{
		ret = AES_ECB_encrypt(src_addr, length, dst_addr, key);
	}
	else if (type == ENCRYPTION_AES_128_CBC)
	{
		ret = AES_CBC_encrypt1(src_addr, length, dst_addr, key,key_tmp);
	}
	else
	{
		//type not defined
		return -1;
	}
	
	if (ret)
	{
		return ret;
	}

	return 0;
}

int do_burn_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],int type)
{
	int ret;
	unsigned int key_tmp[4] = {0, 0, 0, 0};

	if ((src_addr == NULL) || (length == NULL) || (dst_addr == NULL))
	{
		return 1;
	}

	flush_cache( src_addr, length );
	flush_cache( dst_addr, length );
	if (key)
	{
		flush_cache( key, 16 );
	}

	if (type == ENCRYPTION_AES_128_ECB)
	{
		ret = AES_ECB_decrypt(src_addr, length, dst_addr, key);
	}
	else if (type == ENCRYPTION_AES_128_CBC)
	{
		ret = AES_CBC_decrypt1(src_addr, length, dst_addr, key, key_tmp);
	}
	else
	{
		//type not defined
		return -1;
	}
	
	if (ret)
	{
		return ret;
	}

	return 0;
}


int do_burn_hdcp_14(void)
{
	return do_burn_hdcp_xx_l54xx(14);
}

int do_burn_hdcp_21(void)
{
	return do_burn_hdcp_xx_l54xx(21);
}

int do_burn_hdcp_22 (void)
{
	return do_burn_hdcp_xx_l54xx(22);
}

int do_burn_hdcp_xx_l54xx(const unsigned int hdcp_ver)
{
	printf("new\n");
	char * cmd;
	char * image_name = FACTORY_RO_HDCP_2_2_BIN;
	int rcode = CMD_RET_SUCCESS;
	unsigned int Kh_key[4];
	unsigned int Kh_key_hdcp2x[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size;
	unsigned int input_size;
	unsigned int write_size;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR + 0x00100000;
	unsigned int checksum, checksum_ref;
	unsigned int do_checksum_verify;

	if (hdcp_ver == 14) {
		image_name = FACTORY_RO_HDCP_1_4_BIN;
		input_size = 325; // 325
		write_size = 325;
	}
	else if (hdcp_ver == 21) {
		image_name = FACTORY_RO_HDCP_2_1_BIN;
		input_size = 1016; // 1016
		write_size = 1016;
	}
	else if (hdcp_ver == 22) {
		image_name = FACTORY_RO_HDCP_2_2_BIN;
		input_size = 1016; // 1016
		write_size = 1016;
	}
	else {
		// not supported version
		goto FAIL;
	}

	cmd = (char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd, 0, SRING_SIZE);
	
	do_checksum_verify = 0;
	
	//1. download image file to image_A_addr
	snprintf(cmd, sizeof(cmd), "loady %x", image_A_addr);
	printf("%s...\n", cmd);
	rcode = run_command(cmd, 0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size != input_size)
	{
		if( image_size == (input_size+4) ) {
			do_checksum_verify = 1;
		}
		else {
			printf("[INFO %s] %s: failed, image_size not %d\n", __FUNCTION__, cmd, input_size);
			goto FAIL;
		}
	}

#if 0
	//2.1 decrypt pre-encrypted data
	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt(image_A_addr, image_size, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] decrypt hdcp2.x failed. \n", __FUNCTION__);
		goto FAIL;
	}
	//hexdump(image_B_addr, image_size);
#else
	//	  copy image_A_addr to image_B_addr
	memcpy(image_B_addr, image_A_addr, image_size);
#endif
	image_size = write_size; // [ 325, 1016, 1016 ]

	//2.2 verify checksum
	checksum = burn_cal_checksum(image_B_addr, image_size);
	printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
	
	if( do_checksum_verify ) {
		checksum_ref = burn_get_checksum(image_B_addr + write_size);
		if( checksum != checksum_ref ) {
			printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
			printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
			printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
			goto FAIL;
		}
	}
	else {
		checksum_ref = checksum; // veirfy later
	}

	//2.3 copy image_B_addr to image_A_addr
	memcpy(image_A_addr, image_B_addr, image_size);
	
	if(hdcp_ver != 14) {
#if defined(_KEY_PRE_ENCRYPT)		
		//3.1 get hdcp 2.x key
		rcode = do_get_hdcp2x_key(Kh_key_hdcp2x);
		if(rcode)
		{
			printf("[INFO %s] do_get_hdcp2x_key failed(%d)\n", __FUNCTION__, rcode);
			goto FAIL;
		}
	
		//3.2
		rcode = do_burn_decrypt(image_A_addr, 976, image_B_addr, Kh_key_hdcp2x, ENCRYPTION_AES_128_CBC);
		if(rcode)
		{
			printf("[INFO %s] decrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}

#if defined(_DEBUG_CMD_BURN)		
		printf("\nimage_B_addr(decrypted data):\n");
		hexdump(image_B_addr, image_size);
#endif	
#else
		printf("[INFO %s] skip do_burn_decrypt\n", __FUNCTION__);
#endif		
		//4.1 encrypt hdcp 2.x key with deviceID
		read_efuse_deviceID(Kh_key_devID);
		if( rcode )
		{
			printf("[INFO %s] read_efuse_deviceID %d failed\n", __FUNCTION__, rcode);
			goto FAIL;
		}
	
		//4.2 Note ( not use deviceID to encrypt data, so we may pas sstep 4.1 )
		rcode = do_burn_encrypt(image_B_addr, 976, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);
		if(rcode)
		{
			printf("[INFO %s] encrypt hdcp2.x image failed\n", __FUNCTION__, rcode);
			goto FAIL;
		}

#if defined(_DEBUG_CMD_BURN)		
		printf("\nimage_A_addr(encrypted data):\n");
		hexdump(image_A_addr, image_size);
#endif	
			
	}

	//5. write image file from DDR to facro section
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save", image_name, image_A_addr, write_size);
	printf("%s...\n", cmd);
	rcode = run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}

	memset((char *)image_A_addr, 0x16, 1024);
	memset((char *)image_B_addr, 0x17, 1024);
	
	//6. read image file from facro section and compare
	printf("read %s to 0x%08x...\n", image_name, image_B_addr);
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] %s %s: failed\n", __FUNCTION__,image_name,"file not found");
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	if (hdcp_ver != 14) {
		//7.1 ( had been read in step 4.1
		//rcode = read_efuse_deviceID(Kh_key_devID);
		//if( rcode )
		//{
		//	  printf("[INFO %s] %s: %d failed\n", __FUNCTION__,"read_efuse_deviceID",rcode);
		//	  goto FAIL;
		//}

		//7.2 Note ( not use deviceID to encrypt data, so we may pas sstep 7.1 )
		rcode = do_burn_decrypt(image_B_addr, 976, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);
		if( rcode )
		{
			printf("[INFO %s] decrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}
	
#if defined(_KEY_PRE_ENCRYPT)		
		//8.1
		rcode = do_burn_encrypt(image_A_addr, 976, image_B_addr, Kh_key_hdcp2x, ENCRYPTION_AES_128_CBC);
		if (rcode)
		{
			printf("[INFO %s] encrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}
#else
		memcpy(image_B_addr, image_A_addr, 976);
#endif		
	}

	//9 caculate checksum again
	checksum = burn_cal_checksum( image_B_addr, write_size);
	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	clear_buffer(Kh_key_hdcp2x, sizeof(Kh_key_hdcp2x));

	if (cmd)
	{
		free(cmd);
	}

	if (hdcp_ver == 14) {
		printf("save hdcp1.4 success\n");
	}
	else if(hdcp_ver == 21) {
		printf("save hdcp2.1 success\n");
	}
	else if(hdcp_ver == 22) {
		printf("save hdcp2.2 success\n");
	}
	return CMD_RET_SUCCESS;

FAIL:

	clear_buffer(Kh_key_hdcp2x, sizeof(Kh_key_hdcp2x));

	if (cmd)
	{
		free(cmd);
	}

	if (hdcp_ver == 14) {
		printf("save hdcp1.4 fail\n");
	}
	else if(hdcp_ver == 21) {
		printf("save hdcp2.1 fail\n");
	}
	else if(hdcp_ver == 22) {
		printf("save hdcp2.2 fail\n");
	}
	return CMD_RET_FAILURE;
}

int do_burn_hdcp_xx(unsigned int hdcp_ver)
{
	char * cmd;
	char * image_name = NULL;
	int rcode = CMD_RET_SUCCESS;
	unsigned int Kh_key[4];
	unsigned int Kh_key_hdcp2x[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size;
	unsigned int input_size;
	unsigned int write_size;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR + 0x00100000;
	unsigned int checksum, checksum_ref;

	if( hdcp_ver == 14 ) {
		image_name = FACTORY_RO_HDCP_1_4_BIN;
		input_size = 336; // 325+4 --> RTAESCrypt_Debug_win_static_lib.exe --> 336
		write_size = 325;
	}
	else if( hdcp_ver == 21 ) {
		image_name = FACTORY_RO_HDCP_2_1_BIN;
		input_size = 1024; // 1016+4 --> RTAESCrypt_Debug_win_static_lib.exe --> 1024
		write_size = 1016;
	}
	else if( hdcp_ver == 22 ) {
		image_name = FACTORY_RO_HDCP_2_2_BIN;
		input_size = 1024; // 1016+4 --> RTAESCrypt_Debug_win_static_lib.exe --> 1024
		write_size = 1016;
	}
	else {
		// not supported version
		goto FAIL;
	}

	cmd = (char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd, 0, SRING_SIZE);

	/* load image to DDR */
	//1. download image file to image_A_addr
	snprintf(cmd, sizeof(cmd), "loady %x", image_A_addr);
	printf("%s...\n", cmd);
	rcode = run_command(cmd, 0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size != input_size)
	{
		printf("[INFO %s] %s: failed, image_size not %d\n", __FUNCTION__, cmd, input_size);
		goto FAIL;
	}

#if defined(_PRE_ENCRYPT_DATA)
	//2.1 decrypt pre-encrypted data
	Kh_key[0] = SECURE_KH_KEY0;
	Kh_key[1] = SECURE_KH_KEY1;
	Kh_key[2] = SECURE_KH_KEY2;
	Kh_key[3] = SECURE_KH_KEY3;
	rcode = do_burn_decrypt(image_A_addr, image_size, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] decrypt hdcp2.x failed. \n", __FUNCTION__);
		goto FAIL;
	}
	
#if defined(_DEBUG_CMD_BURN)
	printf("\nimage_A_addr(encrypted data):\n");
	hexdump(image_A_addr, image_size);
		
	printf("\nimage_B_addr(decrypted data):\n");
	hexdump(image_B_addr, image_size);
#endif	
#endif /* #if defined(PRE_ENCRYPT_DATA) */

	image_size = write_size; // [ 325, 1016, 1016 ]

#if defined(_VERIFY_CHECKSUM)
	//2.2 verify checksum
	checksum = burn_cal_checksum(image_B_addr, image_size);
	checksum_ref = burn_get_checksum(image_B_addr + write_size);
	if(checksum != checksum_ref) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}
#endif
	//2.3 copy 1016 byte 
	//	  copy image_B_addr to image_A_addr
	memcpy(image_A_addr, image_B_addr, image_size);
	
	if (hdcp_ver != 14) {
		//3.1 get hdcp 2.2 AES key
		rcode = do_get_hdcp2x_key(Kh_key_hdcp2x);
		if(rcode)
		{
			printf("[INFO %s] do_get_hdcp2x_key failed(%d)\n", __FUNCTION__, rcode);
			goto FAIL;
		}
		
#if defined(_DEBUG_CMD_BURN)
		printf("\nKh_key_hdcp2x:\n");
		hexdump(Kh_key_hdcp2x, 16);
#endif	
	
		//3.2
		rcode = do_burn_decrypt(image_A_addr, 976, image_B_addr, Kh_key_hdcp2x, ENCRYPTION_AES_128_CBC);
		if(rcode)
		{
			printf("[INFO %s] decrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}
		
#if defined(_DEBUG_CMD_BURN)
		printf("\nimage_A_addr(encrypted data):\n");
		hexdump(image_A_addr, image_size);
			
		printf("\nimage_B_addr(decrypted data):\n");
		hexdump(image_B_addr, image_size);
#endif	
		
		//4.1 encrypt hdcp 2.2 AES key with deviceID
		read_efuse_deviceID(Kh_key_devID);
		if(rcode)
		{
			printf("[INFO %s] read_efuse_deviceID %d failed\n", __FUNCTION__, rcode);
			goto FAIL;
		}

#if defined(_DEBUG_CMD_BURN)
		printf("\nKh_key_devID:\n");
		hexdump(Kh_key_devID, 16);
#endif	

		//4.2 Note ( not use deviceID to encrypt data, so we may pas sstep 4.1 )
		rcode = do_burn_encrypt(image_B_addr, 976, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);
		if(rcode)
		{
			printf("[INFO %s] encrypt hdcp2.x image failed\n", __FUNCTION__, rcode);
			goto FAIL;
		}
	}

	//5. write image file from DDR to facro section
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save", image_name, image_A_addr, write_size);
	printf("%s...\n", cmd);
	rcode = run_command(cmd, 0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}


	/* Verify */
	memset((char *)image_A_addr, 0x16, 1024);
	memset((char *)image_B_addr, 0x17, 1024);
	
	//6. read image file from facro section and compare
	printf("read %s to 0x%08x...\n", image_name, image_B_addr);
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] %s %s: failed\n", __FUNCTION__,image_name,"file not found");
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	if (hdcp_ver != 14) {
		//7.1 ( had been read in step 4.1
		//rcode = read_efuse_deviceID(Kh_key_devID);
		//if( rcode )
		//{
		//	  printf("[INFO %s] %s: %d failed\n", __FUNCTION__,"read_efuse_deviceID",rcode);
		//	  goto FAIL;
		//}
	
		//7.2 Note ( not use deviceID to encrypt data, so we may pas sstep 7.1 )
		rcode = do_burn_decrypt(image_B_addr, 976, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);
		if (rcode)
		{
			printf("[INFO %s] decrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}
		
		//8.1
		rcode = do_burn_encrypt(image_A_addr, 976, image_B_addr, Kh_key_hdcp2x, ENCRYPTION_AES_128_CBC);
		if (rcode)
		{
			printf("[INFO %s] encrypt hdcp2.x image error %d\n", __FUNCTION__, rcode);
			goto FAIL;
		}
	}

	//9 caculate checksum again
	checksum = burn_cal_checksum(image_B_addr, write_size);
	if(checksum != checksum_ref) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	clear_buffer(Kh_key_hdcp2x, sizeof(Kh_key_hdcp2x));

	if (cmd)
	{
		free(cmd);
	}

	if (hdcp_ver == 14) {
		printf("save hdcp1.4 success\n");
	}
	else if (hdcp_ver == 21) {
		printf("save hdcp2.1 success\n");
	}
	else if (hdcp_ver == 22) {
		printf("save hdcp2.2 success\n");
	}
	else {
		printf("[ERR %s] hdcp ver %d.%d not supported\n", __FUNCTION__, hdcp_ver/10, hdcp_ver%10); // shouldn't happened
		return CMD_RET_FAILURE;
	}
	return CMD_RET_SUCCESS;

FAIL:
	
	clear_buffer(Kh_key_hdcp2x, sizeof(Kh_key_hdcp2x));

	if (cmd)
	{
		free(cmd);
	}

	if (hdcp_ver == 14) {
		printf("save hdcp1.4 fail\n");
	}
	else if (hdcp_ver == 21) {
		printf("save hdcp2.1 fail\n");
	}
	else if (hdcp_ver == 22) {
		printf("save hdcp2.2 fail\n");
	}
	else {
		printf("[ERR %s] hdcp ver %d.%d not supported\n", __FUNCTION__, hdcp_ver/10, hdcp_ver%10);
	}
	return CMD_RET_FAILURE;
}

int do_burn_mac ( char * mac_address )
{
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS;
	unsigned int image_size;
	unsigned int image_size2;
	unsigned int image_A_addr;
	unsigned int image_B_addr;

	image_name = FACTORY_RO_MAC_BIN;
	image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned int checksum, checksum_ref;

	cmd=(char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd,0,SRING_SIZE);

	//1. get mac address from uart
	if( mac_address == NULL ) {
		snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
		PRINT_DEBUG(cmd);
		PRINT_DEBUG("\n");
		rcode=run_command(cmd,0);
		if (rcode != 0)
		{
			printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
			goto FAIL;
		}
		image_size = getenv_ulong("filesize", 16, 0);
		if (image_size==0)
		{
			printf("[INFO %s] %s failed. image_size is zero\n", __FUNCTION__, cmd);
			goto FAIL;
		}
	}
	else {
		image_size = strlen("xx.xx.xx.xx.xx.xx");
		printf("str len \"%s\" is %d\n", mac_address, strlen(mac_address) );
		if( strlen(mac_address) != image_size ) {
			printf("[INFO %s] input mac string error, expected %d bytes\n", __FUNCTION__, image_size);
			goto FAIL;				
		}
		memcpy( image_A_addr, mac_address, image_size );
	}
	
	checksum_ref = burn_cal_checksum( image_A_addr, image_size );
	
	//2. write image file from DDR to facro section
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save", image_name, image_A_addr, image_size);
	printf("%s...\n", cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	//3. read and check
	memset(image_B_addr, 0, 32);
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size2);
	if (rcode)
	{
		printf("[INFO %s] file %s not found\n", __FUNCTION__, image_name);
		goto FAIL;
	}
	if( image_size2 != image_size ) {
		printf("[INFO %s] file size not match\n", __FUNCTION__);
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	checksum = burn_cal_checksum( image_B_addr, image_size );
	
	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save mac success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save mac fail\n");
	return CMD_RET_FAILURE;
}

int do_burn_ci (void)
{
	unsigned int Kh_key[4], image_size = 0;
	char *cmd = NULL;
	unsigned int image_src_addr,image_dst_addr;
	char * image_name = NULL;
	int rcode = CMD_RET_SUCCESS;

	cmd=(char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd,0,SRING_SIZE);

	image_name=FACTORY_RO_CI_BIN;
	image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	image_dst_addr=image_src_addr+1*1024*1024;

	//1. get CI+ file
	snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
	PRINT_DEBUG(cmd);
	PRINT_DEBUG("\n");
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s: failed.	image_size ==0 \n", __FUNCTION__,cmd);
		goto FAIL;
	}


	//3. decrypt CI+ using	AES-128-ECB (efuse AES key)
	printf("image_size=%d		%x\n",image_size,image_size);
	do_burn_decrypt(image_src_addr, image_size, image_dst_addr, NULL, ENCRYPTION_AES_128_ECB);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt CI+");
		goto FAIL;
	}
	memcpy(image_src_addr,image_dst_addr,image_size);

	//4. encrpt CI+ using AES-128-ECB (efuse deviceID)
	rcode=read_efuse_deviceID(Kh_key);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
		goto FAIL;
	}

	rcode = do_burn_encrypt(image_src_addr, image_size, image_dst_addr, Kh_key,ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt ci+ image error",rcode);
		goto FAIL;
	}

	//5. write encrpyed widevine image to factory_ro
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_dst_addr,image_size);
	PRINT_DEBUG(cmd);
	PRINT_DEBUG("\n");
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save CI+ success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save CI+ fail\n");
	return CMD_RET_FAILURE;

}

typedef enum OEMCryptoResult
{
	OEMCrypto_SUCCESS = 0,
	OEMCrypto_ERROR_INIT_FAILED,
	OEMCrypto_ERROR_TERMINATE_FAILED,
	OEMCrypto_ERROR_ENTER_SECURE_PLAYBACK_FAILED,
	OEMCrypto_ERROR_EXIT_SECURE_PLAYBACK_FAILED,
	OEMCrypto_ERROR_SHORT_BUFFER,
	OEMCrypto_ERROR_NO_DEVICE_KEY,
	OEMCrypto_ERROR_NO_ASSET_KEY,
	OEMCrypto_ERROR_KEYBOX_INVALID,
	OEMCrypto_ERROR_NO_KEYDATA,
	OEMCrypto_ERROR_NO_CW,
	OEMCrypto_ERROR_DECRYPT_FAILED,
	OEMCrypto_ERROR_WRITE_KEYBOX,
	OEMCrypto_ERROR_WRAP_KEYBOX,
	OEMCrypto_ERROR_BAD_MAGIC,
	OEMCrypto_ERROR_BAD_CRC,
	OEMCrypto_ERROR_NO_DEVICEID,
	OEMCrypto_ERROR_RNG_FAILED,
	OEMCrypto_ERROR_RNG_NOT_SUPPORTED,
	OEMCrypto_ERROR_SETUP
} OEMCryptoResult;

static unsigned int CRC32[256] =
{
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
	0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
	0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
	0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
	0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
	0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
	0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
	0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
	0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
	0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
	0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
	0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
	0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
	0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
	0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
	0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
	0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
	0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
	0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
	0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
	0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
	0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
	0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
	0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
	0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
	0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
	0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
	0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
	0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
	0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
	0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
	0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
	0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
	0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
	0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
	0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
	0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
	0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
	0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
	0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
	0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
	0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
	0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
	0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
	0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
	0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
	0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
	0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
	0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
	0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
	0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
	0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
	0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
	0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

unsigned int  wvrunningcrc32 (unsigned char * p_begin, int i_count, unsigned int i_crc)
{

	/* Calculate the CRC */
	while (i_count > 0)
	{
		i_crc = (i_crc << 8) ^ CRC32[(i_crc >> 24) ^ ((unsigned int) * p_begin)];
		p_begin++;
		i_count--;
	}

	return(i_crc);
}

OEMCryptoResult OEMCrypto_IsKeyboxValid (unsigned char * addr)
{
	unsigned int crc_value,*addr2, *addr3;
	unsigned char *addr1;

	//1. check magic number
	addr1=addr+128;
	if( strncmp((char*)addr1, "kbox", 4) != 0 )
	{
		printf("Magic is not 'kbox'\n");
		printf("Widevine Magic value error	  %c:%c:%c:%c\n",addr1[0],addr1[1],addr1[2],addr1[3]);
		return OEMCrypto_ERROR_BAD_MAGIC;
	}
	printf("Widevine Magic value valid\n");

#if 1
	//2. check CRC value
	memcpy(buffer,addr,120);
	memcpy(buffer+120,addr+128,4);
	//hexdump(buffer,124);
	crc_value=wvrunningcrc32(buffer, 124, 0xffffffff);

#if 0 // jinn - dirty patch - also take input CRC value in big-endian format
	addr2=(unsigned int *)(addr+132);
	*addr3 = addr[132];
	*addr3 = ((*addr3)<<8) + addr[133];
	*addr3 = ((*addr3)<<8) + addr[134];
	*addr3 = ((*addr3)<<8) + addr[135];
	if ( (crc_value==(*addr2)) || (crc_value==(*addr3)) )
#elif 1 // jinn - always take input CRC value in big-endian format
	*addr2 = addr[132];
	*addr2 = ((*addr2)<<8) + addr[133];
	*addr2 = ((*addr2)<<8) + addr[134];
	*addr2 = ((*addr2)<<8) + addr[135];
	if (crc_value==(*addr2))
#else
	addr2=(unsigned int *)(addr+132);
	if (crc_value==(*addr2))
#endif
	{
		printf("Widevine CRC value valid\n");
	}
	else
	{
		printf("Widevine CRC value error		%08x : %08x\n",(*addr2),crc_value);
		return OEMCrypto_ERROR_BAD_CRC;
	}
#else
	printf("Widevine CRC value valid\n");
#endif

	return OEMCrypto_SUCCESS;
}

#if 1
int do_burn_widevine (void)
{
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS, i;
	unsigned int Kh_key[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size = 0;
	unsigned int image_size_16 = 0;
	unsigned int image_size_sb = 0;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned int checksum, checksum_ref;
	unsigned char * pcA;
	unsigned char * pcB;
	
	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;

	cmd=(char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd,0,SRING_SIZE);

	image_name = FACTORY_RO_WIDEVINE_BIN;
	
	//1. get widevine file
	snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
	printf("%s...\n",cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s failed. image_size is zero\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	
	if( image_size == 140 ) {
		//printf("input size is 140\n");
	}
	else {
		printf("[INFO %s] widevine file size not valid\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	
	checksum = burn_cal_checksum( image_A_addr, 136 );
	checksum_ref = burn_get_checksum( image_A_addr + 136 );
	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}
	
	image_size -= 4;
	image_size_16 = image_size & 0xFFFFFFF0; // 16 byte alignmebt
	image_size_sb = image_size & 0x0000000F; // short-block valid length

	//printf("first 136-byte checksum_ref is 0x%08x\n", checksum_ref);
	//printf("===> input data\n");
	//hexdump( image_A_addr, 136 );

	//2. decrypt widevine using AES-128-CBC (efuse AES key)
	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt( image_A_addr, image_size_16, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] decrypt widevine failed\n", __FUNCTION__);
		goto FAIL;
	}

	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcB[image_size_16+i] = pcB[image_size_16-16+i] ^ pcA[image_size_16+i];
		}
	}
	
	checksum_ref = burn_cal_checksum( image_B_addr, image_size );

//	printf("===> decrypt input data\n");
//	hexdump( image_B_addr, image_size );
	
	//3. check Magic:6b626f78 and CRC
	rcode =OEMCrypto_IsKeyboxValid((unsigned char * )image_B_addr);
	if (rcode != 0)
	{
		printf("[INFO %s] OEMCrypto_IsKeyboxValid failed\n", __FUNCTION__);
		goto FAIL;
	}

#if 0
	//4.1 encrpt widevine using AES-128-ECB (efuse deviceID)
	rcode = read_efuse_deviceID(Kh_key_devID);
	if (rcode != 0)
	{
		printf("[INFO %s] read_efuse_deviceID failed\n", __FUNCTION__);
		goto FAIL;
	}
#endif
	
	//4.2 encrypted 128
	rcode = do_burn_encrypt(image_B_addr, image_size_16, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);

	if( rcode )
	{
		printf("[INFO %s] encrypt widevine image error(%d)\n", __FUNCTION__, rcode);
		goto FAIL;
	}

	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcA[image_size_16+i] = pcB[image_size_16-16+i] ^ pcB[image_size_16+i];
		}
	}
	
//	printf("===> encrypt data\n");
//	hexdump( image_A_addr, image_size );
	
	//5. write encrypted widevine image to factory_ro (136 bytes)
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name, image_A_addr, image_size);
	printf("%s...\n",cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}

	//memset( image_A_addr, 0, 512);
	//memset( image_B_addr, 0, 512);

	//6. read image from  factory_ro to DDR
	image_name = FACTORY_RO_WIDEVINE_BIN;
	rcode = do_verify_read_facro(image_name, image_A_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] %s file not found\n", __FUNCTION__, image_name);
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
//	printf("===> facro data\n");
//	hexdump( image_A_addr, image_size );
	
	//7 decrypt data
	rcode=do_burn_decrypt(image_A_addr, image_size_16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] encrypt widevine image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}

	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcB[image_size_16+i] = pcB[image_size_16-16+i] ^ pcA[image_size_16+i];
		}
	}
//	printf("===>after decrypt\n");
//	hexdump( image_B_addr, image_size );

	checksum = burn_cal_checksum( image_B_addr, image_size );
	
	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save widevine success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save widevine fail\n");
	return CMD_RET_FAILURE;

}
#else // old - toshiba format
int do_burn_widevine_old_TSBs (void)
{
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS;
	unsigned int image_size;
	unsigned int Kh_key[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned int checksum, checksum_ref;
	char tail_8_bytes[8];
	
	TARGET_MODEL_T model;

	cmd=(char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		goto FAIL;
	}
	memset(cmd,0,SRING_SIZE);

	image_name = FACTORY_RO_WIDEVINE_BIN;
	
	//1. get widevine file
	snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
	printf("%s...\n",cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s failed. image_size is zero \n", __FUNCTION__, cmd);
		goto FAIL;
	}
	
	if( image_size == 144 ) {
#if defined(_BOARD_FOR_L4300)
		printf("input size is 144 (for L4300 model)\n");
		model = PROJECT_L4300;
#elif defined(_BOARD_FOR_GENERIC)
		printf("input size is 144 (for Generic model)\n");
		model = PROJECT_GENERIC;
#else
		printf("input size is 144 (for Generic model)\n");
		model = PROJECT_GENERIC;
#endif
	}
	else if( image_size == 148 ) {
		printf("input size is 148 (for Mozart model)\n");
		model = PROJECT_MOZART;
	}
	else {
		printf("[INFO %s] widevine file size not valid\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	
	if( model == PROJECT_MOZART ) {
		checksum = burn_cal_checksum( image_A_addr, 144 );
		checksum_ref = burn_get_checksum( image_A_addr + 144 );
		if( checksum != checksum_ref ) {
			printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
			printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
			printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
			goto FAIL;
		}
		image_size -= 4; // to compatible with L4300 model
	}

	checksum_ref = burn_cal_checksum( image_A_addr, 136 );

//	printf("first 136-byte checksum_ref is 0x%08x\n", checksum_ref);
//	printf("===> input data\n");
//	hexdump( image_A_addr, 144 );

	//2. decrypt widevine using AES-128-CBC (efuse AES key)
	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt( image_A_addr, image_size, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt widevine");
		goto FAIL;
	}
	memcpy( image_A_addr, image_B_addr, image_size); // copy B to A
	memcpy( tail_8_bytes, image_A_addr+136, 8 ); // svae tail 8 bytes
//	printf("===> decrypt input data\n");
//	hexdump( image_A_addr, 144 );
	
	//3. check Magic:6b626f78 and CRC
	rcode =OEMCrypto_IsKeyboxValid((unsigned char * )image_A_addr);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"OEMCrypto_IsKeyboxValid");
		goto FAIL;
	}

	//4.1 encrpt widevine using AES-128-ECB (efuse deviceID)
	rcode = read_efuse_deviceID(Kh_key_devID);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
		goto FAIL;
	}
	//4.2 encrypted 128
	if( model == PROJECT_GENERIC ) { // use SCPU AES key
		rcode = do_burn_encrypt(image_A_addr, WIDEVINE_DATA_SIZE, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	}
	else { // use device ID as key
		rcode = do_burn_encrypt(image_A_addr, WIDEVINE_DATA_SIZE, image_B_addr, Kh_key_devID, ENCRYPTION_AES_128_ECB);
	}
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt widevine image error",rcode);
		goto FAIL;
	}
	//4.3 copy magic and CRC from A to B
	memcpy( image_B_addr+128, image_A_addr+128, 16); // copy B to A
//	printf("===> encrypt data with deviceID(128bytes)\n");
//	hexdump( image_B_addr, 144 );
	

	//5. write encrypted widevine image to factory_ro (136 bytes)
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name, image_B_addr, 136);
	printf("%s...\n",cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	//memset( image_A_addr, 0, 512);
	//memset( image_B_addr, 0, 512);

	//6. read image from  factory_ro to DDR
	image_name = FACTORY_RO_WIDEVINE_BIN;
	rcode = do_verify_read_facro(image_name, image_A_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
//	printf("===> facro data\n");
//	hexdump( image_A_addr, 144 );
	
	//7.1 get key
	//rcode=read_efuse_deviceID(Kh_key_devID);
	//if (rcode != 0)
	//{
	//	  printf("[INFO %s] read_efuse_deviceID failed %d\n", __FUNCTION__, rcode);
	//	  goto FAIL;
	//}
	//7.2 decrypt image 128
	if( model == PROJECT_GENERIC ) { // use SCPU AES key
		rcode=do_burn_decrypt(image_A_addr, 128, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	}
	else { // use device ID as key
		rcode=do_burn_decrypt(image_A_addr, 128, image_B_addr, Kh_key_devID, ENCRYPTION_AES_128_ECB);
	}
	if( rcode )
	{
		printf("[INFO %s] encrypt widevine image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
	memcpy( image_B_addr+128, image_A_addr+128, 8); // copy B to A
	memcpy( image_B_addr+136, tail_8_bytes, 8 ); // restore tail 8 bytes
//	printf("===> after decrypt first 128 bytes\n");
//	hexdump( image_B_addr, 144 );

	//8 encrypt using AES
	//Kh_key[0]=SECURE_KH_KEY0;
	//Kh_key[1]=SECURE_KH_KEY1;
	//Kh_key[2]=SECURE_KH_KEY2;
	//Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_encrypt(image_B_addr, 144, image_A_addr, Kh_key, ENCRYPTION_AES_128_CBC);
//	printf("===> after encrypt first 144 bytes\n");
//	hexdump( image_A_addr, 144 );
	checksum = burn_cal_checksum( image_A_addr, 136 );
//	printf("first 136-byte checksum is 0x%08x\n",checksum);
	printf("src=%x,size=%x\n", image_A_addr, 136);
	
	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save widevine success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save widevine fail\n");
	return CMD_RET_FAILURE;

}
#endif

int do_burn_DTCP (void)
{
#if 1
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS,i;
	unsigned int Kh_key[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size = 0;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;    
	unsigned int checksum, checksum_ref;

	cmd = (char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		printf("[INFO %s] cmd malloc failed. \n", __FUNCTION__);
		goto FAIL;
	}
	memset(cmd, 0, SRING_SIZE);

	image_name = FACTORY_RO_DTCP_BIN;

	//1. get DTCP file
	snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
	printf("%s...\n", cmd);
	rcode = run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s failed. image_size is zero \n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	printf("image_size=%d		%x\n",image_size, image_size); // (4+152+4+4)+4=164
//	printf("===> input data\n");
//	hexdump( image_A_addr, image_size );
	checksum = burn_cal_checksum( image_A_addr, image_size-4 );
	checksum_ref = burn_get_checksum( image_A_addr+image_size-4 );

	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt(image_A_addr, image_size-4, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt dtcp");
		goto FAIL;
	}
//	printf("===> decrypted data\n");
//	hexdump( image_B_addr, image_size-4 );

	checksum_ref = burn_cal_checksum( image_B_addr, image_size-4 ); // (4+152+4+4)=160

	//4. encrpt DTCP using AES-128-ECB (efuse deviceID)
	rcode=read_efuse_deviceID(Kh_key_devID);
	if (rcode != 0)
	{
		printf("[INFO %s] read_efuse_deviceID failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
	
	memset( image_A_addr, 0xCC, 512 );

	image_size = image_size-4; // (4+152+4+4)=160
	rcode = do_burn_encrypt(image_B_addr, image_size, image_A_addr, Kh_key_devID, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] encrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}

//	printf("===> encrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	//5. write encrpyed DTCP image to factory_ro
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name , image_A_addr, image_size);
	printf("%s...\n", cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	memset( image_B_addr, 0xEE, 512 );
	
	//6. read encrpyed DTCP image to ddr
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] file %s not found %d\n", __FUNCTION__, image_name, rcode);
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	memset( image_A_addr, 0xFF, 512 );

	rcode = do_burn_decrypt(image_B_addr, image_size, image_A_addr, Kh_key_devID, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] decrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
//	printf("===> decrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	checksum = burn_cal_checksum( image_A_addr, image_size );

	if( checksum != checksum_ref ) {
		printf("[INFO %s] checksum = 0x%08x\n", __FUNCTION__, checksum);
		printf("[INFO %s] checksum_ref = 0x%08x\n", __FUNCTION__, checksum_ref);
		printf("[INFO %s] compare checksum failed\n", __FUNCTION__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save DTCP success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save DTCP fail\n");
	return CMD_RET_FAILURE;
#else
	unsigned int Kh_key[4];
	char *cmd = NULL,* image_name=NULL;
	unsigned int image_src_addr,image_dst_addr,image_size=0;
	unsigned char * addr;
	unsigned int * addr32;
	int rcode = CMD_RET_SUCCESS,i;

	cmd=(char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		printf("[INFO %s] cmd malloc failed. \n", __FUNCTION__);
		goto FAIL;
	}
	memset(cmd,0,SRING_SIZE);

	image_name=FACTORY_RO_DTCP_BIN;
	image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	image_dst_addr=image_src_addr+1*1024*1024;

	//1. get DTCP file
	snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
	PRINT_DEBUG(cmd);
	PRINT_DEBUG("\n");
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s: failed.	image_size ==0 \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	//2. decrypt widevine using AES-128-CBC (efuse AES key)
	image_size = getenv_ulong("filesize", 16, 0);
	printf("image_size=%d		%x\n",image_size,image_size);

	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	//printf("image_src_addr=0x%08x\n",image_src_addr);
	//hexdump( image_src_addr, image_size );
	rcode = do_burn_decrypt(image_src_addr, image_size, image_dst_addr, Kh_key,ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt dtcp");
		goto FAIL;
	}
	//printf("image_dst_addr=0x%08x\n",image_dst_addr);
	//hexdump( image_dst_addr, image_size );
	memcpy(image_src_addr,image_dst_addr,image_size);

	//3. check checksum
	UINT32	checksum= 0,checksum1=0;
	addr=(unsigned char *)image_src_addr;
	for(i=0; i<(image_size-8); i++)
	{
		checksum+= addr[i];
	}
	//printf("checksum=0x%08x\n",checksum);
	addr32=(unsigned int *)(image_src_addr+(image_size-8));
	//printf("ref. checksum=0x%08x\n",*addr32);
	if (checksum!=*addr32)
	{
		printf("[INFO %s] 1st checksum failed.	%x	%x\n", __FUNCTION__,checksum,*addr32);
		goto FAIL;
	}

	//4. encrpt DTCP using AES-128-ECB (efuse deviceID)
	image_size=image_size-8;
	rcode=read_efuse_deviceID(Kh_key);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
		goto FAIL;
	}

	//image_src_addr+=strlen(STRING_WIDEVINE_HEADER);
	//hexdump(image_src_addr,32);
	rcode = do_burn_encrypt(image_src_addr, image_size, image_dst_addr, Kh_key,ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt dtcp image error",rcode);
		goto FAIL;
	}
	//printf("encrypt...\n");
	//hexdump( image_dst_addr, image_size );
	//memcpy((void *)(image_dst_addr+WIDEVINE_DATA_SIZE),(const void *) (image_src_addr+WIDEVINE_DATA_SIZE),8);

	//5. write encrpyed DTCP image to factory_ro
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_dst_addr,image_size);
	PRINT_DEBUG(cmd);
	PRINT_DEBUG("\n");
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	//6. read encrpyed DTCP image to ddr
	rcode = do_verify_read_facro(image_name, image_src_addr,&image_size);
	//printf("read...\n");
	//hexdump( image_src_addr, image_size );
	if (rcode)
	{
		printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
		goto FAIL;
	}

	rcode = do_burn_decrypt(image_src_addr, image_size, image_dst_addr, Kh_key,ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"decrypt dtcp image error",rcode);
		goto FAIL;
	}
	//printf("decrypt...\n");
	//hexdump( image_dst_addr, image_size );

	addr=(unsigned char *)image_dst_addr;
	for(i=0; i<(image_size); i++)
	{
		checksum1+= addr[i];
	}
	//printf("checksum1=0x%08x\n",checksum1);
	if (checksum!=checksum1)
	{
		printf("[INFO %s] 2nd checksum failed.	%x	%x\n", __FUNCTION__,checksum,checksum1);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save DTCP success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save DTCP fail\n");
	return CMD_RET_FAILURE;
#endif
}


int do_get_hdcp2x_key (unsigned int * Kh_key)
{
	unsigned int _key[4] = 
	{
		SECURE_KEY0,
		SECURE_KEY1,
		SECURE_KEY2,
		SECURE_KEY3,
	};

	unsigned int key[4] =
	{
		0x084466bc,
		0xbd43bf05,
		0x9b4ecc6b,
		0x56133f51
	};
	
	unsigned char *pimage_src_addr, *pimage_dst_addr;

	pimage_src_addr = (unsigned char *)(((unsigned int)buffer)&0xFFFFFFE0UL);
	pimage_src_addr += 0x20; // 32-byte alignment
	pimage_dst_addr = pimage_src_addr + 0x20; // 32-byte alignment

	memcpy(pimage_src_addr, key, deviceID_ARRAY_SIZE);

	flush_cache(pimage_src_addr, deviceID_ARRAY_SIZE);
	flush_cache(pimage_dst_addr, deviceID_ARRAY_SIZE);

	AES_ECB_decrypt(pimage_src_addr, deviceID_ARRAY_SIZE, pimage_dst_addr, _key);

	//printf("===> pimage_src_addr\n");
	//hexdump(pimage_src_addr, 16);
	//printf("===> pimage_dst_addr\n");
	//hexdump(pimage_dst_addr, 16);

	memcpy(Kh_key, pimage_dst_addr, deviceID_ARRAY_SIZE);
	flush_cache(Kh_key, deviceID_ARRAY_SIZE);

	memset(buffer, 0 , sizeof(buffer));
	flush_cache(buffer, sizeof(buffer));

	return 0;
}

int do_burn_ree_customer_data_01 (void)
{
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS,i;	
	unsigned int Kh_key[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size = 0;
	unsigned int image_size_16 = 0;
	unsigned int image_size_sb = 0;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;    
	unsigned int checksum, checksum_ref;
	unsigned char * pcA;
	unsigned char * pcB;

	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;

	cmd = (char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		printf("[INFO %s] cmd malloc failed. \n", __FUNCTION__);
		goto FAIL;
	}
	memset(cmd, 0, SRING_SIZE);

	image_name = FACTORY_RO_REE_BIN;

	//1. get playreadt file
	snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
	printf("%s...\n", cmd);
	rcode = run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s failed. image_size is zero \n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	printf("image_size=%d		%x\n",image_size, image_size); // (4+152+4+4)+4=164
//	printf("===> input data\n");
//	hexdump( image_A_addr, image_size );
	checksum = burn_cal_checksum( image_A_addr, image_size-4 );
	checksum_ref = burn_get_checksum( image_A_addr+image_size-4 );

	if( checksum != checksum_ref ) {
		printf("[INFO %s %d] checksum = 0x%08x\n", __FUNCTION__, __LINE__, checksum);
		printf("[INFO %s %d] checksum_ref = 0x%08x\n", __FUNCTION__, __LINE__, checksum_ref);
		printf("[INFO %s %d] compare checksum failed\n", __FUNCTION__, __LINE__);		
		goto FAIL;
	}
	
	image_size    = image_size-4;
	image_size_16 = image_size & 0xFFFFFFF0; // 16 byte alignmebt
	image_size_sb = image_size & 0x0000000F; // short-block valid length

	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt(image_A_addr, image_size_16, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt dtcp");
		goto FAIL;
	}

	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcB[image_size_16+i] = pcB[image_size_16-16+i] ^ pcA[image_size_16+i];
		}
	}

//	printf("===> decrypted data\n");
//	hexdump( image_B_addr, image_size );

	checksum_ref = burn_cal_checksum( image_B_addr, image_size );

#if 0
	//4. encrypt playready using AES-128-ECB (efuse deviceID)
	rcode=read_efuse_deviceID(Kh_key_devID);
	if (rcode != 0)
	{
		printf("[INFO %s] read_efuse_deviceID failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
#endif	
	
	memset( image_A_addr, 0xCC, 512 );

	rcode = do_burn_encrypt(image_B_addr, image_size_16, image_A_addr, NULL/*Kh_key_devID*/, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] encrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
	
	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcA[image_size_16+i] = pcB[image_size_16-16+i] ^ pcB[image_size_16+i];
		}
	}

//	printf("===> encrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	//5. write encrpyed playready key to factory_ro
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name , image_A_addr, image_size);
	printf("%s...\n", cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	memset( image_B_addr, 0xEE, 512 );
	
	//6. read encrpyed playready image to ddr
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] file %s not found %d\n", __FUNCTION__, image_name, rcode);
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	image_size_16 = image_size & 0xFFFFFFF0; // 16 byte alignmebt
	image_size_sb = image_size & 0x0000000F; // short-block valid length
	
	memset( image_A_addr, 0xFF, 512 );

	rcode = do_burn_decrypt(image_B_addr, image_size_16, image_A_addr, NULL/*Kh_key_devID*/, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] decrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}

	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcA[image_size_16+i] = pcA[image_size_16-16+i] ^ pcB[image_size_16+i];
		}
	}

//	printf("===> decrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	checksum = burn_cal_checksum( image_A_addr, image_size );

	if( checksum != checksum_ref ) {
		printf("[INFO %s %d] checksum = 0x%08x\n", __FUNCTION__, __LINE__, checksum);
		printf("[INFO %s %d] checksum_ref = 0x%08x\n", __FUNCTION__, __LINE__, checksum_ref);
		printf("[INFO %s %d] compare checksum failed\n", __FUNCTION__, __LINE__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save playready success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save playready fail\n");
	return CMD_RET_FAILURE;
}

int do_burn_tee_customer_data_02 (void)
{
	char * cmd;
	char * image_name;
	int rcode = CMD_RET_SUCCESS,i;	
	unsigned int Kh_key[4];
	unsigned int Kh_key_devID[4];
	unsigned int image_size = 0;
	unsigned int image_size_16 = 0;
	unsigned int image_size_sb = 0;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;    
	unsigned int checksum, checksum_ref;
	unsigned char * pcA;
	unsigned char * pcB;

	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;

	cmd = (char *)malloc(SRING_SIZE);
	if (!cmd)
	{
		printf("[INFO %s] cmd malloc failed. \n", __FUNCTION__);
		goto FAIL;
	}
	memset(cmd, 0, SRING_SIZE);

	image_name = FACTORY_RO_TEE_BIN;

	//1. get playreadt file
	snprintf(cmd, sizeof(cmd),"loady %x", image_A_addr);
	printf("%s...\n", cmd);
	rcode = run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s failed\n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	if (image_size==0)
	{
		printf("[INFO %s] %s failed. image_size is zero \n", __FUNCTION__, cmd);
		goto FAIL;
	}
	image_size = getenv_ulong("filesize", 16, 0);
	printf("image_size=%d		%x\n",image_size, image_size); // (4+152+4+4)+4=164
//	printf("===> input data\n");
//	hexdump( image_A_addr, image_size );
	checksum = burn_cal_checksum( image_A_addr, image_size-4 );
	checksum_ref = burn_get_checksum( image_A_addr+image_size-4 );

	if( checksum != checksum_ref ) {
		printf("[INFO %s %d] checksum = 0x%08x\n", __FUNCTION__, __LINE__, checksum);
		printf("[INFO %s %d] checksum_ref = 0x%08x\n", __FUNCTION__, __LINE__, checksum_ref);
		printf("[INFO %s %d] compare checksum failed\n", __FUNCTION__, __LINE__);
		goto FAIL;
	}
	
	image_size = image_size-4;	
	image_size_16 = image_size & 0xFFFFFFF0; // 16 byte alignmebt
	image_size_sb = image_size & 0x0000000F; // short-block valid length

	Kh_key[0]=SECURE_KH_KEY0;
	Kh_key[1]=SECURE_KH_KEY1;
	Kh_key[2]=SECURE_KH_KEY2;
	Kh_key[3]=SECURE_KH_KEY3;
	rcode = do_burn_decrypt(image_A_addr, image_size_16, image_B_addr, Kh_key, ENCRYPTION_AES_128_CBC);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,"decrypt dtcp");
		goto FAIL;
	}
	
	if( image_size_sb ) {
		for( i = 0; i < image_size_sb; i++ ) {
			pcB[image_size_16+i] = pcB[image_size_16-16+i] ^ pcA[image_size_16+i];
		}
	}

//	printf("===> decrypted data\n");
//	hexdump( image_B_addr, image_size );

	checksum_ref = burn_cal_checksum( image_B_addr, image_size );
	
#if 0 // not encrypt netflix key here, because it had been encrypted by off-line tool with KCPU's AES key
#if 0
	//4. encrypt netflix using AES-128-ECB (efuse deviceID)
	rcode=read_efuse_deviceID(Kh_key_devID);
	if (rcode != 0)
	{
		printf("[INFO %s] read_efuse_deviceID failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
#endif	
	
	memset( image_A_addr, 0xCC, 512 );

	rcode = do_burn_encrypt(image_B_addr, image_size, image_A_addr, NULL/*Kh_key_devID*/, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] encrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
#else
	// copy image_B_addr to image_A_addr
	memcpy(image_A_addr, image_B_addr, image_size);
#endif

//	printf("===> encrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	//5. write netflix key to factory_ro
	snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name , image_A_addr, image_size);
	printf("%s...\n", cmd);
	rcode=run_command(cmd,0);
	if (rcode != 0)
	{
		printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
		goto FAIL;
	}

	memset( image_B_addr, 0xEE, 512 );
	
	//6. read netflix image to ddr
	rcode = do_verify_read_facro(image_name, image_B_addr, &image_size);
	if (rcode)
	{
		printf("[INFO %s] file %s not found %d\n", __FUNCTION__, image_name, rcode);
		goto FAIL;
	}
	printf("reading size is %d\n", image_size);
	
	memset( image_A_addr, 0xFF, 512 );

#if 0 // not encrypt netflix key here, because it had been encrypted by off-line tool with KCPU's AES key
	rcode = do_burn_decrypt(image_B_addr, image_size, image_A_addr, NULL/*Kh_key_devID*/, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] decrypt dtcp image error failed %d\n", __FUNCTION__, rcode);
		goto FAIL;
	}
#else
	// copy image_B_addr to image_A_addr
	memcpy(image_A_addr, image_B_addr, image_size);
#endif

//	printf("===> decrypted data (%d)\n", image_size);
//	hexdump( image_A_addr, image_size );

	checksum = burn_cal_checksum( image_A_addr, image_size );

	if( checksum != checksum_ref ) {
		printf("[INFO %s %d] checksum = 0x%08x\n", __FUNCTION__, __LINE__, checksum);
		printf("[INFO %s %d] checksum_ref = 0x%08x\n", __FUNCTION__, __LINE__, checksum_ref);
		printf("[INFO %s %d] compare checksum failed\n", __FUNCTION__, __LINE__);
		goto FAIL;
	}

	if (cmd)
	{
		free(cmd);
	}
	printf("save netflix success\n");
	return CMD_RET_SUCCESS;

FAIL:
	if (cmd)
	{
		free(cmd);
	}
	printf("save nexflix fail\n");
	return CMD_RET_FAILURE;
}

int do_burn_sn (const char * sn)
{
	int tmp, length;
	int rcode = CMD_RET_SUCCESS, i, j;	
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned int image_C_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100010;
	unsigned char * pcA;
	unsigned char * pcB;
	unsigned char * pcC;
	unsigned int * piA;
	unsigned int * piB;
	unsigned int * piC;
	
	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;
	pcC = (unsigned char *)image_C_addr;
	piA = (unsigned int *)image_A_addr;
	piB = (unsigned int *)image_B_addr;
	piC = (unsigned int *)image_C_addr;

	length = strlen(sn);

	if( length != 9 ) {
		printf("[INFO %s] sn length(%d) invalid\n", __FUNCTION__, length);
		goto FAIL;
	}

	memset(pcA,0,16);
	
	// check string format 
	for( i = 0; i < 9; i++) {
		if( ( '0' <= sn[i] ) && ( sn[i] <= '9' ) ) {
			pcA[i] = sn[i];
		}
		else {
			printf("[INFO %s] sn foramt error\n", __FUNCTION__);
			goto FAIL;
		}
	}

	// backup
	memcpy( pcC, pcA, 16);
	
	// pre-check
	read_efuse_sn( pcB );
	if( piB[0] || piB[1] || piB[2] ||  piB[3] ) {
		printf("[INFO %s] sn had been programed\n", __FUNCTION__);
		// check key is same
		rcode = do_burn_decrypt(image_B_addr, 16, image_A_addr, NULL, ENCRYPTION_AES_128_ECB);
		if( rcode )
		{
			printf("[INFO %s] decrypt sn error(%d)\n", __FUNCTION__, rcode);
			goto FAIL;
		}
		// check programmed sn
		for( i = 0; i < 16; i++) {
			if(	pcA[i] != pcC[i] ) {
				printf("[INFO %s] sn conflict\n", __FUNCTION__);
				printf("CUR:");
				for( j = 0; j < 16; j++) {
					printf(" %02x", pcA[j]);
				}
				printf("\n");
				printf("NEW:");
				for( j = 0; j < 16; j++) {
					printf(" %02x", pcC[j]);
				}
				printf("\n");
				goto FAIL;
			}
		}
		printf("save sn success\n");
		return CMD_RET_SUCCESS;
	}	
	
	// encrypted
	rcode = do_burn_encrypt(image_A_addr, 16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt sn error",rcode);
		goto FAIL;
	}
	printf("SN1:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcA[i]);
	}
	printf("\n");
	printf("SN2:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcB[i]);
	}
	printf("\n");
	
	otp_init();
	// burn sn to OTP
	otp_write( OTP_DEVICEID_OFFSET,    piB[0], 1);
	otp_write( OTP_DEVICEID_OFFSET+4,  piB[1], 1);
	otp_write( OTP_DEVICEID_OFFSET+8,  piB[2], 1);
	otp_write( OTP_DEVICEID_OFFSET+12, piB[3], 1);
	
	// read sn from OTP
	memset(pcA,0,16);
	otp_read( OTP_DEVICEID_OFFSET,    &piA[0]);
	otp_read( OTP_DEVICEID_OFFSET+4,  &piA[1]);
	otp_read( OTP_DEVICEID_OFFSET+8,  &piA[2]);
	otp_read( OTP_DEVICEID_OFFSET+12, &piA[3]);
	
	// decrypted
	memset(pcB,0,16);
	rcode = do_burn_decrypt(image_A_addr, 16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] decrypt sn error(%d)\n", __FUNCTION__, rcode);
		goto FAIL;
	}
	printf("SN1:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcA[i]);
	}
	printf("\n");
	printf("SN2:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcB[i]);
	}
	printf("\n");
	
	// compare
	for( i = 0; i < 16; i++) {
		if( pcB[i] != pcC[i] ) {
			printf("[INFO %s] program SN failed\n", __FUNCTION__);
			goto FAIL;
		}
	}	

	printf("save sn success\n");
	return CMD_RET_SUCCESS;
	
FAIL:
	printf("save sn fail\n");
	return CMD_RET_FAILURE;		
}

int do_read_sn (void)
{
	int tmp;
	int rcode = CMD_RET_SUCCESS, i;	
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned int image_C_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100010;
	unsigned char * pcA;
	unsigned char * pcB;
	unsigned char * pcC;
	
	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;
	pcC = (unsigned char *)image_C_addr;

	memset(pcA,0xFF,16);
	
	// read sn from OTP
	read_efuse_sn( pcA );

	// decrypted
	rcode = do_burn_decrypt(image_A_addr, 16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
	if( rcode )
	{
		printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"decrypt sn error",rcode);
		goto FAIL;
	}
	
	// show
	printf("SN1:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcA[i]);
	}
	printf("\n");
	printf("SN2:");
	for( i = 0; i < 16; i++) {
		printf(" %02x", pcB[i]);
	}
	printf("\n");

	printf("read sn success\n");
	return CMD_RET_SUCCESS;
	
FAIL:
	printf("read sn fail\n");
	return CMD_RET_FAILURE;		
}

int do_burn_efuse (const char * type)
{
	//printf("efuse burn type:	  %s\n",type);

	if (strcmp(type, "deviceID") == 0)
	{
		return do_burn_efuse_deviceID();
	}
	else if (strcmp(type, "read_deviceID") == 0)
	{
		return do_get_efuse_deviceID();
	}
	else if (strcmp(type, "secure_mode_enable_bit") == 0)
	{
#if 0	// for L4300 and Mozart
		return do_burn_efuse_secure_mode_enable_bit();
#else
		printf("\nthis model not necessary to burn efuse secure bit\n\n");
		return CMD_RET_FAILURE;
#endif
	}
	else if (strcmp(type, "aes_check") == 0)
	{
		return do_burn_efuse_aes_check();
	}
#if 0
	else if (strcmp(type, "rsa") == 0)
	{
		return do_burn_efuse_rsa();
	}
	else if (strcmp(type, "rsa") == 0)
	{
		return do_burn_efuse_rsa();
	}
	else if (strcmp(type, "aes") == 0)
	{
		return do_burn_efuse_aes();
	}
	else if (strcmp(type, "all") == 0)
	{
		return do_burn_efuse_all();
	}
	else if (strcmp(type, "dcas") == 0)
	{
		//start_program(PROGRAM_DCAS_RSA_START_BYTE, dcas_rsa_pub_key_size, dcas_rsa_pub_key);
		return CMD_RET_FAILURE; //no support
	}
#endif

	return CMD_RET_USAGE;
}

unsigned int swap_endian( unsigned int data)
{
	unsigned int output;	
	
	output =  (data & 0x000000FF)<<24;
	output |= (data & 0x0000FF00)<<8;
	output |= (data & 0x00FF0000)>>8;
	output |= (data & 0xFF000000)>>24;
	
	return output;
}

int pre_check_aes_key(void)
{
	int rcode = CMD_RET_SUCCESS, i;
	unsigned int image_size = 0;
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
	unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
	unsigned char * pcA;
	unsigned char * pcB;
	int do_aes_programming;
	int is_aes_programming_ok;
	unsigned int Kh_key[4];
	
	pcA = (unsigned char *)image_A_addr;
	pcB = (unsigned char *)image_B_addr;
	
	if( !otp_aes_key_is_programmed ) {
#if 1
		memcpy( pcA, test_pattern, 16);
		// encrypted data with S-CPU AES key
		rcode = do_burn_encrypt(image_A_addr, 16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
		if( rcode )
		{
			printf("[INFO %s] encrypt data failed\n", __FUNCTION__);
			goto FAIL;
		}
		// compare encrypted data with pre-encrypted data 
		do_aes_programming = 1;
		for( i = 0; i < 16; i++ ) {
			if( pcB[i] != n_enc_test_pattern[i] ) {
				do_aes_programming = 0;
				break;
			}	
		}
		printf("D1:");
		for( i = 0; i < 16; i++) {
			printf(" %02x", pcA[i]);
		}
		printf("\n");
		printf("D2:");
		for( i = 0; i < 16; i++) {
			printf(" %02x", pcB[i]);
		}
		printf("\n");
#else
		do_aes_programming = 1;// force
#endif	
		// write new S-CPU AES key ad K-CPU AES key
		if( do_aes_programming ) {
			printf("[INFO %s] start to burn AES key\n", __FUNCTION__);
			otp_init();
			// burn S-CPU AES key to OTP
			otp_write( OTP_SAESKEY_OFFSET,     S_AES_KEY_3, 0);
			otp_write( OTP_SAESKEY_OFFSET+4,   S_AES_KEY_2, 0);
			otp_write( OTP_SAESKEY_OFFSET+8,   S_AES_KEY_1, 0);
			otp_write( OTP_SAESKEY_OFFSET+12,  S_AES_KEY_0, 0);

			// burn K-CPU AES key to OTP
			otp_write( OTP_KAESKEY_OFFSET,     K_AES_KEY_3, 0);
			otp_write( OTP_KAESKEY_OFFSET+4,   K_AES_KEY_2, 0);
			otp_write( OTP_KAESKEY_OFFSET+8,   K_AES_KEY_1, 0);
			otp_write( OTP_KAESKEY_OFFSET+12,  K_AES_KEY_0, 0);

			// re-load otp data
			reload_otp();

			// check again
			memcpy( pcA, test_pattern, 16);
			rcode = do_burn_encrypt(image_A_addr, 16, image_B_addr, NULL, ENCRYPTION_AES_128_ECB);
			if( rcode )
			{
				printf("[INFO %s] encrypt data failed\n", __FUNCTION__);
				goto FAIL;
			}
			// compare encrypted data with pre-encrypted data 
			is_aes_programming_ok = 1;
			for( i = 0; i < 16; i++ ) {
				if( pcB[i] != s_enc_test_pattern[i] ) {
					is_aes_programming_ok = 0;
					break;
				}	
			}printf("D1:");
			for( i = 0; i < 16; i++) {
				printf(" %02x", pcA[i]);
			}
			printf("\n");
			printf("D2:");
			for( i = 0; i < 16; i++) {
				printf(" %02x", pcB[i]);
			}
			printf("\n");
			otp_aes_key_is_programmed = 1;
			if( is_aes_programming_ok ) {
				printf("[INFO %s] burn aes key success\n", __FUNCTION__);
				return CMD_RET_SUCCESS;
			}
			else {
				printf("[INFO %s] burn aes key failed\n", __FUNCTION__);
				return CMD_RET_FAILURE;
			}
		}
		otp_aes_key_is_programmed = 1;
	}

	return CMD_RET_SUCCESS;

FAIL:
	return CMD_RET_FAILURE;
}

int do_burn (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

	if (argc >= 2)
	{
		if (strcmp(argv[1], "hdcp1.4") == 0)
		{
			return do_burn_hdcp_14();
		}
		else if (strcmp(argv[1], "hdcp2.1") == 0)
		{
			pre_check_aes_key();
			return do_burn_hdcp_21();
		}
		else if (strcmp(argv[1], "hdcp2.2") == 0)
		{
			pre_check_aes_key();
			return do_burn_hdcp_22();
		}
		else if (strcmp(argv[1], "mac") == 0)
		{
			if( argc >=3 ) {
				return do_burn_mac(argv[2]);
			}
			else {
				return do_burn_mac("2a.3a.4a.5a.6a.7a");				
			}
		}
		else if (strcmp(argv[1], "CI+") == 0)
		{
			pre_check_aes_key();
			return do_burn_ci();
		}
		else if (strcmp(argv[1], "widevine") == 0)
		{
			pre_check_aes_key();
			return do_burn_widevine();
		}
		else if (strcmp(argv[1], "DTCP") == 0)
		{
			pre_check_aes_key();
			return do_burn_DTCP();
		}
		else if (strcmp(argv[1], "ree") == 0)
		{
			pre_check_aes_key();
			return do_burn_ree_customer_data_01();
		}
		else if (strcmp(argv[1], "tee") == 0)
		{
			pre_check_aes_key();
			return do_burn_tee_customer_data_02();
		}
		else if (strcmp(argv[1], "sn") == 0)
		{
			if( argc >=3 ) {
				pre_check_aes_key();
				return do_burn_sn(argv[2]);
			}
		}
		else if (strcmp(argv[1], "readsn") == 0)
		{
			return do_read_sn();
		}
		else if (strcmp(argv[1], "aeskey") == 0)
		{
			pre_check_aes_key();
			return CMD_RET_SUCCESS;
		}
#if 1
		else if (strcmp(argv[1], "efuse") == 0)
		{
			if( argc >=3 ) {
				return do_burn_efuse(argv[2]);
			}
		}
#endif

	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD
(
	burn, 3, 1,   do_burn,
	"burn image to factory via uart by rtice",
	"argu\n"
	"burn hdcp1.4\n"
	"burn hdcp2.1\n"
	"burn mac \n"
	"burn CI+\n"
	"burn widevine\n"
	"burn playready\n"
	"burn netflix\n"
	"burn sn\n"
	"burn readsn\n"
	"burn efuse devideID\n"
	"burn efuse aes_check\n"
	"burn efuse secure_mode_enable_bit\n"
);
