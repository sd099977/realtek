/************************************************
 Comments in Big5:				
	此檔描述 款Flash Memory 
	動作時所需的函式				
				
************************************************/
#ifndef __FLASHDEV_N_H__
#define __FLASHDEV_N_H__


#include "flash/flash_nand_list.h"
#include "flash/flash_nand_profile.h"
#include "nand_mgr.h"


/****************************************************************************
*	nand data layout
****************************************************************************/
#define NAND_EXT_PARAM_BLK_ADDR			0x10		//BLOCK 0x16
#define NAND_EXT_PARAM_BYTE_SIZE	0x00000800
#define NAND_RESCURE_LOGO_BLK_ADDR	(NAND_EXT_PARAM_BLK_ADDR+1)

/* NAND flash ECC type */
#define NAND_ECC_TYPE_6BIT		0
#define NAND_ECC_TYPE_12BIT	1
/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_n(void  *dev,
               unsigned int* dest,
               unsigned int   rem_size);

int do_write_n(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset);
               
int do_read_n(void *dev,
               unsigned int*  start_blk,	
               unsigned char* dest,		
               unsigned int   rem_size,		
               unsigned int   signature);               
               

int do_identify_n(void **dev);

int do_init_n(void *dev);

void do_exit_n(void *dev);

int get_env_n(void *dev, unsigned char *buf);

int save_env_n(void *dev, unsigned char *buf);
void NF_dump_flash(n_device_type *device, UINT32 dst_addr, UINT32 src_page, UINT32 page_len);

#endif
