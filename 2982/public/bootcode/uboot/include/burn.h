#ifndef __BURN_H_
#define __BURN_H_

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

enum ENCRPTION_TYPE
{
    ENCRYPTION_AES_128_ECB = 0,
    ENCRYPTION_AES_128_CBC
};

#define SRING_SIZE 256

#define WIDEVINE_SIZE 136
#define WIDEVINE_DATA_SIZE 128

#define STRING_WIDEVINE_HEADER  "RTK_Widevine"

#define deviceID_ARRAY_SIZE 16

#if 1
#define PRINT_DEBUG printf
#else
#define PRINT_DEBUG(fmt,args...)
#endif

int do_burn_efuse_rsa (void);
int do_burn_efuse_aes (void);
int do_burn_efuse_deviceID (void);
int do_get_efuse_deviceID (void);
int do_burn_efuse_secure_mode_enable_bit (void);
int do_burn_efuse_aes_check (void);
int do_burn_efuse_all (void);
int read_efuse (void);

int read_efuse_deviceID (unsigned int * Kh_key);
int do_cp_test (void);

int read_efuse_sn(unsigned char * pcSN);

extern unsigned int burn_aes_key[4];

#if 0
int do_burn_decrypt (unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int do_burn_encrypt (unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
#else
int do_burn_encrypt 
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],int type);

int do_burn_decrypt 
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],int type);
#endif

#endif
