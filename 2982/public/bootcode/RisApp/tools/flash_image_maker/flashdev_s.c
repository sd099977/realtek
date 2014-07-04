#include <sysdefs.h>
#include <stdio.h>
#include "flashdev_s.h"
#include "util.h"

// comment by alan (not in use?)
//#define INV_DATA_SEG 0xa1000000

extern UINT8  verify_after_write;


static void switch_read_mode(void)
{
	UINT8 tmp;
	UINT8 * temp_ptr = (UINT8 *)0xbfc10000;

	REG32(0xb801a800)=0x00000003; //switch flash to read mode
	REG32(0xb801a804)=0x00000018; //command cycle
	tmp = *temp_ptr;
	// restore register (avoid read flash bus hang)
	REG32(0xb801a81c) = 0x0;
	REG32(0xb801a818) = 0x0;
	REG32(0xb801a80c) = 0x00070707;
}

/************************************************************************
 *
 *                          do_erase_s 
 *  Description :
 *  -------------
 *  implement the flash erase
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/

int do_erase_s(void *dev,
               unsigned int* dest,
               unsigned int   rem_size)
{
    volatile unsigned char tmp;
    unsigned int size;
    s_device_type *device = (s_device_type *)dev;                                         
    unsigned char *loc;
    
    loc = (unsigned char *) dest;
    while(rem_size > 0)
    {
        /* show '/' in console */
	print_uart("/");
        //REG32(UART0_REG)= 0x2f ; //cy test
        
        /* write enable */
        REG32(0xb801a800)=0x00520006;
        REG32(0xb801a804)=0x00180000;
        tmp = *loc;
        

        //image size >= 256K
        if (rem_size >= 0x40000)
        {
            if (device->sec_256k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x40000;
            }
            else if (device->sec_64k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x10000;
            }
            else if (device->sec_32k_en == 1)
            {
                REG32(0xb801a800)=0x00000052;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x8000;
            }
            else if (device->sec_4k_en == 1)
            {
                if (device->id==PMC_4Mbit)
                    REG32(0xb801a800)=0x000000d7;
                else
                    REG32(0xb801a800)=0x00000020;
                
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x1000;
            }
        }
        //256K > image size >= 64K
        else if ((0x40000 > rem_size) && (rem_size >= 0x10000))
        {
            if (device->sec_64k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x10000;
            }
            else if (device->sec_32k_en == 1)
            {
                REG32(0xb801a800)=0x00000052;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x8000;
            }
            else if (device->sec_4k_en == 1)
            {
                if (device->id==PMC_4Mbit)
                    REG32(0xb801a800)=0x000000d7;
                else
                    REG32(0xb801a800)=0x00000020;
                
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x1000;
            }
            else if (device->sec_256k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x40000;
            }
        }
        //64K > image size >= 32K
        else if ((0x10000 > rem_size) && (rem_size >= 0x8000))
        {
            if (device->sec_32k_en == 1)
            {
                REG32(0xb801a800)=0x00000052;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x8000;
            }
            else if (device->sec_4k_en == 1)
            {
                if (device->id==PMC_4Mbit)
                    REG32(0xb801a800)=0x000000d7;
                else
                    REG32(0xb801a800)=0x00000020;
                
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x1000;
            }
            else if (device->sec_64k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x10000;
            }
            else if (device->sec_256k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x40000;
            }
        }
        //32K > image size 
        else if (0x8000 > rem_size)
        {
            
            if (device->sec_4k_en == 1)
            {
                if (device->id==PMC_4Mbit)
                    REG32(0xb801a800)=0x000000d7;
                else
                    REG32(0xb801a800)=0x00000020;
                
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x1000;
            }
            else if (device->sec_32k_en == 1)
            {
                REG32(0xb801a800)=0x00000052;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x8000;
            }
            else if (device->sec_64k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x10000;
            }
            else if (device->sec_256k_en == 1)
            {
                REG32(0xb801a800)=0x000000d8;
                REG32(0xb801a804)=0x00000008;
                tmp = *loc;
                size = 0x40000;
            }
        }
        
        /* read status registers until write operation completed*/
        do
        {
            REG32(0xb801a800)=0x00000005;
            REG32(0xb801a804)=0x00000010;
        } while((tmp = *loc)&0x1);
        
        size = (rem_size > size)? size : rem_size ;
        rem_size-=size;
        
        loc+=size;
    }
    
    return 0;
}
/************************************************************************
 *
 *                          do_write
 *  Description :
 *  -------------
 *  implement the flash write 
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_s(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset)
{
#ifdef ENABLE_UART_FUNC
		int i = 0;
#endif
		s_device_type *device = (s_device_type *)dev;
		unsigned char *loc, *src;
		unsigned int length = rem_size;
		
		loc = (unsigned char *)dest;
		src = (unsigned char *)array_ptr;

		//add by angus
		REG32(0xb801a81c)=	0x00000106;
		REG32(0xb801a818)=	0x00000105;
		REG32(0xb801a80c)=	0x00ffffff;

		//issue write command
		REG32(0xb801a800) =  0x00000002;
		REG32(0xb801a804) =  0x00000018;

		// if dest address is not on 256 byte boundary, use byte program until reach boundary
		while ((((UINT32)loc) & 0xff) && (rem_size > 0))
		{
			*loc++ = *array_ptr++;
			rem_size--;

			/* show '.' in console */
			if ((rem_size & 0xff )== 0xff) {
				//REG32(UART0_REG)= 0x2e ; //cy test
				print_uart(".");
			}
		}

 
		
		//if flash support page program, we can use page program to reduce program time
		if (device->page_program)
		{
			//if writing data greater than one page(256 bytes)
			while(rem_size >= 256)
			{ 
#ifdef ENABLE_UART_FUNC
	
				/* show '.' in console */
				if ( !(i++ % 4)) {
					//REG32(UART0_REG)= 0x2f ; //cy test
					print_uart("/");
				}
#endif
		 
				copy_memory((UINT8 *)loc, array_ptr, 256);
				
				/* shift to next page to writing */
				array_ptr+=256;
				loc+=256;
				rem_size-=256;
			
			}//end of page program
			
		}//end of page program
	 
		
		/* left data in-sufficient to one page, we write it using byte program 
		   or flash doesn't support page program mode */
		while(rem_size--)
		{ 
#ifdef ENABLE_UART_FUNC
	
			/* show '.' in console */
			if ((rem_size % 1024 )== 1023) {
				//REG32(UART0_REG)= 0x2e ; //cy test
				print_uart(".");
			}
#endif

			*loc++ = *array_ptr++;	
		}
	

		if (verify_after_write)
		{
			switch_read_mode();
			printf("verify: (0x%x, 0x%x, 0x%x)\n", (UINT32) dest, (UINT32) src, length);
			if (compare_memory(dest, src, length))
			{
				printf("verify failed (0x%x, 0x%x, 0x%x)\n", (UINT32) dest, (UINT32) src, length);
				return -1;
			}
		}

		return 0;
}

/************************************************************************
 *
 *                          do_identify_s
 *  Description :
 *  -------------
 *  implement the identyfy flash type
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_identify_s(void **dev)
{
	UINT32 id;
	UINT32 idx;

	UINT8 * temp_ptr = (UINT8 *)0xbfc10000;
	//UINT8 * temp_ptr = (UINT8 *)0xb8100000;


	/* switch to in-order mode */
	sync();
	//disable w-merge and r-bypass
	REG32(0xb801a018)=((REG32(0xb801a018) | 0x80000 ) & ~0x30000);
	sync();
	//enable command inorder
	REG32(0xb801a018)= (REG32(0xb801a018) | 0xc0000);
	sync();

    REG32(0xb801a814)=0x00000001;   //set serial flash controller latch data at rising edge
    /* hcy :ice boot lower more */
    REG32(0xb801a808)=0x0101000b;   //lowering frequency
    REG32(0xb801a80c)=0x00090101;   //setup control edge	
	
	/* read Manufacture & device ID */
    REG32(0xb801a800)=0x0000009f;
    REG32(0xb801a804)=0x00000010;
    id = *(unsigned int*)temp_ptr;
    id >>= 8;
    //printf("\nflash id [0x%x]\n", id);

	print_uart("\nflash id [0x");
	print_val(id,4);
	print_uart("]\n");

	
    /* find the match flash brand */
    for (idx = 0; idx < DEV_SIZE_S; idx++)
    {
        if ( s_device[idx].id == id )
        {
        	//special case: the same id have two mode, check ext-id
        	if (id == SPANSION_128Mbit)
        	{
        		/* read extended device ID */
                	REG32(0xb801a800)=0x0000009f;
                	REG32(0xb801a804)=0x00000013;
                	id = *(UINT32 *)temp_ptr;
                	id >>= 16;
                	printf("\textension id [0x%x]\n", id);
        		continue;
        	}
        	
            *dev = (void *)&s_device[idx];
	    switch_read_mode();
            return 0;
        }
    }
    
    
    
    //device not found, down freq and try again
    if (idx == DEV_SIZE_S)
    {
        /* maybe not JEDEC , lower the freq. try again*/
        REG32(0xb801a808)=0x0101000b;  //lower frequency 
        REG32(0xb801a800)=0x00000090;  //read id
        REG32(0xb801a804)=0x00000010;  //issue command
        id = *(unsigned int*)temp_ptr;
        id >>= 16;
           
        for (idx = 0; idx < DEV_SIZE_S; idx++)
        {
            if ( s_device[idx].id == id )
            {
            	//special case: the same id have two mode, check ext-id
            	if (id == SPANSION_128Mbit)
            	{
            		/* read extended device ID */
                    REG32(0xb801a800)=0x00000090;
                    REG32(0xb801a804)=0x0000001b;
                    id = *(unsigned int*)temp_ptr;
                	id >>= 16;
            		continue;
            	}

                *dev = (void *)&s_device[idx];
		switch_read_mode();
                return 0;
            }
        }
                
        if (idx == DEV_SIZE_S)
        {
        	*dev = (void *)0x0;
            return -1;
        }
    }

	*dev = (void *)0x0;
	switch_read_mode();
	return -1;
}
/************************************************************************
 *
 *                          do_init_s
 *  Description :
 *  -------------
 *  implement the init flash controller
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_init_s(void *dev)
{
	UINT8 tmp;
	UINT8 * temp_ptr = (UINT8 *)0xbfc10000;
	//UINT8 * temp_ptr = (UINT8 *)0xb8100000;
	
	/* configure serial flash controller */
   
	sync();
	//disable w-merge and r-bypass
	REG32(0xb801a018)=((REG32(0xb801a018) | 0x80000 ) & ~0x30000);
	sync();
	//enable command inorder
	REG32(0xb801a018)= (REG32(0xb801a018) | 0xc0000);
	sync();
    
//    REG32(0xb801a808)=0x01010004;   //setup freq divided no
    REG32(0xb801a808)=0x0101000b;   //lowering frequency

    REG32(0xb801a80c)=0x00090101;   //setup control edge

    REG32(0xb801a810)=0x00000000;	//disable hardware potection
	
    /* enable write status register */        
    REG32(0xb801a800)=0x00000050;
    REG32(0xb801a804)=0x00000000;
    tmp = *temp_ptr;
    *temp_ptr = 0x00;
    
    /* write status register , no memory protection*/
    REG32(0xb801a800)=0x00000001; 
    REG32(0xb801a804)=0x00000010;
    *temp_ptr = 0x00;
    
    return 0;
}
/************************************************************************
 *
 *                          do_exit_s
 *  Description :
 *  -------------
 *  implement the exit flash writing operation
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void do_exit_s(void *dev)
{
	//UINT8 tmp;
	//UINT8 * temp_ptr = (UINT8 *)0xbfc10000;
	//UINT8 * temp_ptr = (UINT8 *)0xb8100000;
		
    //tmp = *temp_ptr;
	switch_read_mode();
   
}
