#ifndef __OTP_CP_REG_H__
#define __OTP_CP_REG_H__

/****************************************************************************/
/*                                                                          */
/* ==================== CP Register DEFINE ==================== */
/*                                                                          */
/****************************************************************************/
#define CW_AGENT            0xb80150e0
#define KEY_IN_CW           (0x01UL)

#define K_CP_REG_KEY        (0xb8015834)
#define K_CP_REG_KEY0		(K_CP_REG_KEY)
#define K_CP_REG_KEY1       (K_CP_REG_KEY0+(1<<2))
#define K_CP_REG_KEY2       (K_CP_REG_KEY0+(2<<2))
#define K_CP_REG_KEY3       (K_CP_REG_KEY0+(3<<2))

#define K_CP_REG_DATAIN     (0xb8015844)
#define K_CP_REG_DATAIN0    (K_CP_REG_DATAIN)
#define K_CP_REG_DATAIN1    (K_CP_REG_DATAIN0+(1<<2))
#define K_CP_REG_DATAIN2    (K_CP_REG_DATAIN0+(2<<2))
#define K_CP_REG_DATAIN3    (K_CP_REG_DATAIN0+(3<<2))

#define K_CP_REG_DATAOUT    (0xb8015854)
#define K_CP_REG_DATAOUT0   (K_CP_REG_DATAOUT)
#define K_CP_REG_DATAOUT1   (K_CP_REG_DATAOUT0+(1<<2))
#define K_CP_REG_DATAOUT2   (K_CP_REG_DATAOUT0+(2<<2))
#define K_CP_REG_DATAOUT3   (K_CP_REG_DATAOUT0+(3<<2))

#define K_CP_REG_IV         (0xb8015864)
#define K_CP_REG_IV0        (K_CP_REG_IV)
#define K_CP_REG_IV1        (K_CP_REG_IV0+(1<<2))
#define K_CP_REG_IV2        (K_CP_REG_IV0+(2<<2))
#define K_CP_REG_IV3        (K_CP_REG_IV0+(3<<2))

#define K_CP_REG_SET        0xb8015874
    #define WRT_EN3         (0x01UL<<17)
    #define CP_MODE_SHT     (13)
    #define CP_MODE_MASK    (0xfUL<<CP_MODE_SHT)
    #define CP_AES_DCAS     (0)
    #define CP_TDES         (0x1UL<<CP_MODE_SHT)
    #define CP_DES          (0x2UL<<CP_MODE_SHT)
    #define CP_TDES_DCAS_L  (0x5UL<<CP_MODE_SHT)
    #define CP_DES_DCAS_L   (0x6UL<<CP_MODE_SHT)
    #define CP_TDES_DCAS_M  (0xdUL<<CP_MODE_SHT)
    #define CP_DES_DCAS_M   (0xeUL<<CP_MODE_SHT)
    #define WRT_EN2         (0x01UL<<5)
    #define CBC_CBC         (0x01UL<<4)
    #define CBC_ECB         (0x00UL<<4)
    #define WRT_EN1         (0x01UL<<3)
    #define REG_1ST         (0x01UL<<2)
    #define WRT_EN0         (0x01UL<<1)
    #define REG_ENDE        (0x01UL)


#define K_CP_REG_SET1       0xb8015878
#define DES_KEY_ORDER       (0x01UL<<9)
#define CP_KEY_MODE_SHT     (6)
#define CP_KEY_MODE_MASK    (0x7UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_REG        (0x0UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_CW         (0x1UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_OTP_K      (0x2UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_SCK        (0x3UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_SMK        (0x4UL<<CP_KEY_MODE_SHT)
#define KEY_MODE_OTP_S      (0x5UL<<CP_KEY_MODE_SHT)

#define IV_MODE_SHT         (4)
#define IV_MODE_MASK        (0x3<<IV_MODE_SHT)
#define IV_MODE_REG         (0x0<<IV_MODE_SHT)
#define IV_MODE_CW          (0x1<<IV_MODE_SHT)

#define INPUT_MODE_SHT      (2)
#define INPUT_MODE_MASK     (0x3<<INPUT_MODE_SHT)
#define INPUT_MODE_REG      (0x0<<INPUT_MODE_SHT)
#define INPUT_MODE_CW       (0x1<<INPUT_MODE_SHT)

#define OUTPUT_MODE_SHT     (0)
#define OUTPUT_MODE_MASK    (0x3)
#define OUTPUT_MODE_REG     (0x0)
#define OUTPUT_MODE_CW      (0x1)

#define K_CP_REG_SET2       0xb801587c
#define OUTPUT_ENTRY_SHT    (24)
#define OUTPUT_ENTRY_MASK   (0x7fUL<<OUTPUT_ENTRY_SHT)
#define INPUT_ENTRY_SHT     (16)
#define INPUT_ENTRY_MASK    (0x7fUL<<INPUT_ENTRY_SHT)
#define KEY_ENTRY_SHT       (8)
#define KEY_ENTRY_MASK      (0x7fUL<<KEY_ENTRY_SHT)
#define IV_ENTRY_SHT        (0)
#define IV_ENTRY_MASK       (0x7fUL)


#endif  //?#ifndef __OTP_CP_REG_H__