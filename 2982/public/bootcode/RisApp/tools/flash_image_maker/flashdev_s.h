/************************************************
 Comments in Big5:				
	此檔描述 款Flash Memory 
	動作時所需的函式				
				
************************************************/
#ifndef __FLASHDEV_S_H__
#define __FLASHDEV_S_H__

#include "flash/flash_spi_list.h"

/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_s(void  *dev,
               unsigned int* dest,
               unsigned int   rem_size);

int do_write_s(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset);

int do_identify_s(void **dev);

int do_init_s(void *dev);

void do_exit_s(void *dev);

#endif
