#ifndef __KT_REG_H__
#define __KT_REG_H__

#define MAX_KEY_TABLE_ENTRY     64

#define KT_WADR_REG             0xb8035804
#define KT_WADR_AKL_WT_EN       (1<<8)
#define KT_WADR_WT_ADDR_TO_SRAM(x) (X & 0x3F)


#define KT_HOSTKEY1_REG         0xb803580C
#define KT_HOSTKEY2_REG         0xb8035810
#define KT_HOSTKEY3_REG         0xb8035814
#define KT_HOSTKEY4_REG         0xb8035818

#define KT_HOSTKEY_IV1_REG      0xb803581C
#define KT_HOSTKEY_IV2_REG      0xb8035820
#define KT_HOSTKEY_IV3_REG      0xb8035824
#define KT_HOSTKEY_IV4_REG      0xb8035828

#define KT_HOSTKEY_USAGE_REG    0xb8035830

#define KT_HOSTKEY_USAGE_HOSTKEY_IV_ONLY    (1<<9)
#define KT_HOSTKEY_USAGE_HOSTKEY_VALID      (1<<8)
#define KT_HOSTKEY_USAGE_DECRYPT_EN         (1<<5)
#define KT_HOSTKEY_USAGE_ENCRYPT_EN         (1<<4)
#define KT_HOSTKEY_USAGE_KEY_LEN_128        (1<<3)
#define KT_HOSTKEY_USAGE_KEY_LEN_64         (0)
#define KT_HOSTKEY_USAGE_ALGO_AES           (0x0)
#define KT_HOSTKEY_USAGE_ALGO_TDES          (0x1)
#define KT_HOSTKEY_USAGE_ALGO_ASA           (0x4)
#define KT_HOSTKEY_USAGE_ALGO_DVB_CSA3      (0x5)
#define KT_HOSTKEY_USAGE_ALGO_DVB_CSA2      (0x6)

#define KT_RDKEY_USAGE_REG      0xb8035834

#define KT_RDKEY_USAGE_RD_KEY_EN            (1<<16)
#define KT_RDKEY_USAGE_KEY_INDEX(x)         ((x & 0x3F)<<8)
#define KT_RDKEY_USAGE_TDES_MODE_ECB        (0<<7)
#define KT_RDKEY_USAGE_TDES_MODE_CBC        (1<<7)
#define KT_RDKEY_USAGE_AES_MODE_ECB         (0<<5)
#define KT_RDKEY_USAGE_AES_MODE_CBC         (1<<5)
#define KT_RDKEY_USAGE_AES_MODE_CTR         (2<<5)
#define KT_RDKEY_USAGE_AES_ATIS             (3<<5)
#define KT_RDKEY_USAGE_ENCRYPT_EN(x)        ((x)<<4)
#define KT_RDKEY_USAGE_CRYPTO_ENGINE_AES    (0)
#define KT_RDKEY_USAGE_CRYPTO_ENGINE_TDES   (1)
#define KT_RDKEY_USAGE_CRYPTO_ENGINE_ASA    (4)
#define KT_RDKEY_USAGE_CRYPTO_ENGINE_CSA3   (5)
#define KT_RDKEY_USAGE_CRYPTO_ENGINE_CSA2   (6)

#endif
