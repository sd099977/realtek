/**
**  @file nocs_bsd_impl.h
**
*/

#ifndef __NOCS_BSD_IMPL_H__
#define __NOCS_BSD_IMPL_H__

//#include <linux/types.h>

#include "mcp_dgst.h"
#include "ca_defs.h"

#define EXTERNAL_BSD_STATUS_OFFSET  0

#define SEC_TYPE_RAM2RAM 0
#define SEC_TYPE_STREAM  1
#define SEC_TYPE_NO_USE  0xFF

struct SBsdInitParameters
{
    unsigned int rtk_BsdInitParameters;
};

struct SBsdTerminateParameters
{
    unsigned int rtk_BsdTerminateParameters;
};

struct SBsdCipherSession
{

    TUnsignedInt8   last_key;       //the last key set in the key table
#define BSD_USE_CERT_KEY                0
#define BSD_USE_KEY_LADDER_KEY          1
#define BSD_USE_CLEAR_TEXT_KEY          2
#define BSD_USE_FLASH_PROTECTION_KEY    3
#define BSD_USE_LEGACY_KEY              4
#define BSD_UNSET_KEY              		5

    TUnsignedInt8   en_de;          //Encryption or Descryption
#define BSD_DECRYPTION              0
#define BSD_ENCRYPTION              1

    TUnsignedInt16  Emi;            //Encryption Method Indicator
    TUnsignedInt8   KeyTableIndex;  //the index of  NOCS Key Table
#define BSD_KEY_TBL_FREE           0xFF
};


struct SBsdHashContext {
    //unsigned char  mcp_ctx;
    MCP_MD_CTX  mcp_ctx;
};


#endif /* #define __NOCS_BSD_IMPL_H__ */

/* end of file */
