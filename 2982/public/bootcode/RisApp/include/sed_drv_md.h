#ifndef __SED_DRV_MD_H__
#define __SED_DRV_MD_H__

#include "sed_drv_common.h"

#define MD_DSC_CNTL             0xb800b160
    #define MD_DSC_CNTL_DSC_IDEL    (0x1 <<2)
    #define MD_DSC_CNTL_DSC_GO      (0x1 <<1)
    #define MD_DSC_CNTL_WRITE_DATA  0x1
    
#define MD_DSC_SADDR            0xb800b164
#define MD_DSC_DESTADDR         0xb800b168
#define MD_DSC_TOTLENGTH        0xb800b16C
#define MD_DSC_HEADERLEN        0xb800b170
#define MD_DSC_PKTLEN           0xb800b174
#define MD_DSC_DATATYPE         0xb800b178

    #define MD_DSC_DATATYPE_WRITE_EN2           (1<<5)    
    #define MD_DSC_DATATYPE_DSC_M2M_TYPE_DATA   0
    #define MD_DSC_DATATYPE_DSC_M2M_TYPE_PACKET (1<<4)
    #define MD_DSC_DATATYPE_WRITE_EN1           (1<<3)    
    #define MD_DSC_DATATYPE_DSC_TYPE_AES         0
    #define MD_DSC_DATATYPE_DSC_TYPE_TDES        1
    #define MD_DSC_DATATYPE_DSC_TYPE_CSA3        0x5
    #define MD_DSC_DATATYPE_DSC_TYPE_CSA2        0x6
        
#define MD_KT_CTRL              0xb800b17C
    
    #define MD_KT_CTRL_WRITE_EN5           (1<<17)    
    #define MD_KT_CTRL_MD_KT_CRYPTO_AES    (0<<14)
    #define MD_KT_CTRL_MD_KT_CRYPTO_TDES   (1<<14)
    #define MD_KT_CTRL_MD_KT_CRYPTO_CSA3   (5<<14)
    #define MD_KT_CTRL_MD_KT_CRYPTO_CSA2   (6<<14)
    #define MD_KT_CTRL_WRITE_EN4           (1<<13)    
    #define MD_KT_CTRL_MD_KT_AES_MODE_ECB  (0<<11)
    #define MD_KT_CTRL_MD_KT_AES_MODE_CBC_TERMINATE_IN_CLEAR  (1<<11)
    #define MD_KT_CTRL_MD_KT_AES_MODE_CTR  (2<<11)
    #define MD_KT_CTRL_MD_KT_AES_MODE_ATIS (3<<11)
    #define MD_KT_CTRL_WRITE_EN3           (1<<10)    
    #define MD_KT_CTRL_MD_KT_TDES_MODE_ECB (0<<9)
    #define MD_KT_CTRL_MD_KT_TDES_MODE_CBC (1<<9)
    #define MD_KT_CTRL_WRITE_EN2           (1<<8)    
    #define MD_KT_CTRL_MD_KT_ENCRYPT       (0<<7)
    #define MD_KT_CTRL_MD_KT_DECRYPT       (1<<7)
    #define MD_KT_CTRL_WRITE_EN1           (1<<6)    
    #define MD_KT_CTRL_MD_KT_KEY_INDEX(x)  ((x) & 0x3F)    
    
#endif
