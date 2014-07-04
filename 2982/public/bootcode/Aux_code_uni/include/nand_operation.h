//==============================================================================
// Copyright (c) 2013 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: nand_operation.h
// Abstract:
//   NAND flash basic operations of Hardware Control for NAND
//
// History:
//	 2013-06-20			     		Initial Version
//==============================================================================

#ifndef _NAND_OPERATION_H_
#define _NAND_OPERATION_H_

//==============================================================================
//  Definition
//==============================================================================
#define NF_WRITE_FUNCTION
#define NF_ERASE_FUNCTION

//==============================================================================
//  Public function prototype
//==============================================================================
int nand_op_read_page(const unsigned int page_no, char *dest_addr, const unsigned int page_size);
int nand_op_read_to_PP_first(const unsigned int col_addr, const unsigned int page_addr, const unsigned int length);
int nand_op_D_read_to_PP(void);
int nand_op_is_6bit_ecc(void);
int nand_op_is_12bit_ecc(void);
int nand_op_spare_ddr_enabled(void);
unsigned int nand_op_get_sram(const int mapping, const unsigned int offset);
unsigned int nand_op_get_spare(void);
void nand_op_set_timing(const int t1, const int t2, const int t3, const int delay_cnt);
int nand_op_reset(void);
int nand_op_read_id(unsigned int addr, unsigned int *id);
int nand_op_is_random_mode(void);
void nand_op_set_random_col_addr(unsigned int data_col, unsigned spare_col);
#ifdef NF_WRITE_FUNCTION
int nand_op_write_page(const unsigned int page_no, const char *buf, const unsigned int page_size);
void nand_op_set_spare(const unsigned int spare, const unsigned int offset, const int page_size);
#endif
#ifdef NF_ERASE_FUNCTION
int nand_op_erase_block(const unsigned int page_addr);
#endif
int nand_op_read_onfi_params(unsigned int *buffer, unsigned int len);

#endif

//==============================================================================
// End of File
