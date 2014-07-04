#ifndef __KL_REG_H__
#define __KL_REG_H__

#define KL_STATUS_1                     0xb806F800
    #define KL_STATUS_KEY_CNT(x)                        ((x >>16) & 0x7)
    #define KL_STATUS_SCE_SM_STATUS(x)                  ((x >>8) & 0x1F)
    #define KL_STATUS_EVER_K1EQK2                       (1<<5)
    #define KL_STATUS_KDF_K1_KEY_GEN_DONE               (1<<4)
    #define KL_STATUS_MASTER_ROOTKEY2_CHECK_SUM_READY   (1<<3)
    #define KL_STATUS_MASTER_ROOTKEY1_CHECK_SUM_READY   (1<<2)
    #define KL_STATUS_FLASH_PROT_ROOTKEY_READY          (1<<1)
    #define KL_STATUS_DEBUG_PASSWORD_READY              (1)

#define KL_ERROR_STATUS                 0xb806F804
    #define KL_ERROR_STATUS_TDES_K1EQK2                 (1)

#define KL_CTRL1                        0xb806F808
    #define KL_CTRL1_ALLOW_DECRYPT      (1<<13)
    #define KL_CTRL1_ALLOW_ENCRYPT      (1<<12)
    #define KL_CTRL1_KDF_K1_KEY_GEN_SEL_AES      (0)
    #define KL_CTRL1_KDF_K1_KEY_GEN_SEL_TDES     (1)
    #define KL_CTRL1_KDF_K1_KEY_GEN_SEL_DVB_CSA2 (2)
    #define KL_CTRL1_KDF_K1_KEY_GEN_SEL_DVB_CSA3 (3)

#define KL_CTRL2                        0xb806F80C
    #define KL_CTRL2_KDF_K1_KEY_GEN_START        (1)

#define KL_CIPHER_PROTECT_KEY_L2_0      0xb806F818
#define KL_CIPHER_PROTECT_KEY_L2_1      0xb806F81C
#define KL_CIPHER_PROTECT_KEY_L2_2      0xb806F820
#define KL_CIPHER_PROTECT_KEY_L2_3      0xb806F824

#define KL_CIPHER_PROTECT_KEY_L1_0      0xb806F828
#define KL_CIPHER_PROTECT_KEY_L1_1      0xb806F82C
#define KL_CIPHER_PROTECT_KEY_L1_2      0xb806F830
#define KL_CIPHER_PROTECT_KEY_L1_3      0xb806F834

#define KL_CIPHER_CONTENT_KEY_0         0xb806F838
#define KL_CIPHER_CONTENT_KEY_1         0xb806F83C
#define KL_CIPHER_CONTENT_KEY_2         0xb806F840
#define KL_CIPHER_CONTENT_KEY_3         0xb806F844

#define KL_CONTENT_KEY_IV_0             0xb806F848
#define KL_CONTENT_KEY_IV_1             0xb806F84C
#define KL_CONTENT_KEY_IV_2             0xb806F850
#define KL_CONTENT_KEY_IV_3             0xb806F854

#endif
