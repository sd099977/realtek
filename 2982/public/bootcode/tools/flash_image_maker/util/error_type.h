/************************************************************************
 *
 *  error_type.h
 *
 *  Defines for MacArthur2 ROM code error types
 *
 ************************************************************************/

#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define ERR_KEY_SIGNATURE_NOT_FOUND	0xf

#define ERR_HWSETTING_TOO_LARGE		0x10
#define ERR_HWSETTING_NOT_FOUND		0x11
#define ERR_HWSETTING_FAILED		0x12
#define ERR_HWSETTING_NOT_FINISH	0x13
#define ERR_HWSETTING_VER_NOT_MATCH	0x14
#define ERR_HWSETTING_VERIFY_FAIL	0x15

#define ERR_BOOTCODE_NOT_FOUND		0x20
#define ERR_BOOTCODE_FAILED		0x21
#define ERR_BOOTCODE_INVALID_SIZE	0x22
#define ERR_BOOTCODE_VER_NOT_MATCH	0x24
#define ERR_REE_BOOTCODE_VERIFY_FAIL	0x25
#define ERR_TEE_BOOTCODE_VERIFY_FAIL	0x26



#define ERR_MCP_ERROR			0x30
#define ERR_KPUBLIC_M_NOT_MATCH		0x3c
#define ERR_KEY_SIG_NOT_MATCH		0x3d
#define ERR_BOOTCODE_NOT_MATCH		0x3e
#define ERR_NOT_MATCH			0x3f

#define ERR_NF_RESET_FAIL           0x40
#define ERR_NF_READ_ID_FAIL         0x41
#define ERR_NF_IDENTIFY_FAIL        0x42
#define ERR_NF_READ_ECC_FAIL        0x43

#define ERR_EMMC_INIT_FAIL          0x50    /* emmc initial flow fail */
#define ERR_EMMC_HOST_FAIL          0x51    /* mmc host reset fail */
#define ERR_EMMC_CMD1_FAIL          0x52    /* mmc cmd1 fail present initial process fail */
#define ERR_EMMC_DMA_ERROR          0x53    /* 0xb8010404 b:1 */
#define ERR_EMMC_CMD_ERR_RSP        0x54    /* 0xb8010414 b:2 at respone cmd */
#define ERR_EMMC_CMD_ERR_STR        0x55    /* 0xb8010414 b:2 at stream cmd*/
#define ERR_EMMC_CMD_TOUT_RSP       0x56    /* respone cmd timeout */
#define ERR_EMMC_CMD_TOUT_STR       0x57    /* stream cmd timeout */
#define ERR_EMMC_STATUS_FAIL        0x58    /* emmc wait ststus fail*/
#define ERR_EMMC_BUS_WIDTH          0x59    /* emmc change bit width fail*/
#define ERR_EMMC_XXX_XXA            0x5A    /* */
#define ERR_EMMC_XXX_XXB            0x5B    /* */
#define ERR_EMMC_XXX_XXC            0x5C    /* */
#define ERR_EMMC_XXX_XXD            0x5D    /* */
#define ERR_EMMC_XXX_XXE            0x5E    /* */
#define ERR_EMMC_XXX_XXF            0x5F    /* */

#define ERR_NOCS_CERTIFICATE_NOT_MATCH	0x60
#define ERR_GET_NOCS_CERTIFICATE_FAILED 0x61
#define ERR_PARAM_AREA_NOT_MATCH	0x64
#define ERR_GET_PARAM_AREA_FAILED       0x65
#define ERR_AUX_CODE_AREA_NOT_MATCH     0x68
#define ERR_GET_AUX_CODE_AREA_FAILED    0x69
#define ERR_AUX_CODE_AREA_SIZE_OVERFLOW	0x6a
#define ERR_EXT_FW_AREA_NOT_MATCH       0x6c

#define ERR_SCS_INVALID_KEY_RIGHTS	0x70
#define ERR_SCS_INVALID_MSID		0x71
#define ERR_SCS_INVALID_VERSIONING	0x72

#define ERR_INVALID_ADDRESS		0x90
#define ERR_TIMEOUT			0x91
#define ERR_UNKNOWN_TYPE		0x92
#define ERR_INVALID_PARAM		0x93
#define ERR_ALLOC_FAILED		0x94
#define ERR_FUNC_NOT_AVAILABLE      0x95
#define ERR_INVALID_SIZE		0x96
#define ERR_UART_BUFFER_FULL		0x9e
#define ERR_UNEXPECTED_RETURN		0x9f

#define ERR_DEFAULT			0xfe	/* default value (not assigned yet) */
#endif /* #ifndef ERROR_TYPE_H */
