/************************************************
 Comments in Big5:				
	此檔描述 款Flash Memory 
	動作時所需的函式				
				
************************************************/
#ifndef __FLASHDEV_SN_H__
#define __FLASHDEV_SN_H__

#include "flash/flash_spi_nand_list.h"
#include "flash/flash_nand_profile.h"
#include "nand_mgr.h"

/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_sn(void	*dev,
					unsigned int* dest,
					unsigned int	rem_size);

int do_write_sn(void *dev,
					unsigned char* array_ptr,
					unsigned int* dest,
					unsigned int	rem_size,
					unsigned int	signature,
					const unsigned int page_offset);
					
int do_read_sn(void *dev,
					unsigned int*	start_blk,	
					unsigned char* dest, 	
					unsigned int	rem_size,		
					unsigned int	signature); 				  
					

int do_identify_sn(void **dev);

int do_init_sn(void *dev);

void do_exit_sn(void *dev);

int get_env_sn(void *dev, unsigned char *buf);

int save_env_sn(void *dev, unsigned char *buf);
//void NF_dump_flash(n_device_type *device, UINT32 dst_addr, UINT32 src_page, UINT32 page_len);


#endif
