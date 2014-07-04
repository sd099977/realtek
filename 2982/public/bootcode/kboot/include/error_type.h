/************************************************************************
 *
 *  error_type.h
 *
 *  Defines for error types
 *
 ************************************************************************/

#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H

/************************************************************************
 *  Definition
 ************************************************************************/

#define ERR_MCP_ERROR			0x30
#define ERR_KPUBLIC_M_NOT_MATCH		0x3c
#define ERR_KEY_SIG_NOT_MATCH		0x3d
#define ERR_BOOTCODE_NOT_MATCH		0x3e
#define ERR_NOT_MATCH			0x3f

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
