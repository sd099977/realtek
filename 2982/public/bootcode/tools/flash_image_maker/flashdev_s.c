#include <sysdefs.h>
#include <stdio.h>
#include "flashdev_s.h"
#include "util.h"
#include "flashdev_sn_reg.h"

// comment by alan (not in use?)
//#define INV_DATA_SEG 0xa1000000

extern UINT8  verify_after_write;
extern unsigned int UartReg;
#define SPI_BASE_ADDRESS  0x1ec00000
#define _SFC_DELAY 100

static void unlock_flash(void)
{
	printf("%s\n", __FUNCTION__);
	
	UINT8 tmp;
	UINT8 *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;

	/* read status register */		  
	REG32(SFC_OPCODE) = 0x05;
	REG32(SFC_CTL) = 0x10;
	sync();
	udelay(_SFC_DELAY); 						
	tmp = REG8(temp_ptr);

	printf("before status reg = 0x%x\n", tmp);

	/* write enable */
	REG32(SFC_OPCODE) = 0x06;
	REG32(SFC_CTL) = 0x00;
	sync();
	udelay(_SFC_DELAY); 	
	tmp = REG8(temp_ptr);

	/* write status register , no memory protection */
	REG32(SFC_OPCODE) = 0x01; 
	REG32(SFC_CTL) = 0x10;
	sync();
	udelay(_SFC_DELAY); 						
	REG8(temp_ptr) = 0x00;

	/* read status registers until write operation completed */
	do
	{
	   REG32(SFC_OPCODE) = 0x05;
	   REG32(SFC_CTL) = 0x10;			
	   sync();
	} while((tmp = REG8(temp_ptr))&0x1);

	printf("after status reg = 0x%x\n", tmp);

	return;
}

static void lock_flash(void)
{
	printf("%s\n", __FUNCTION__);

	UINT8 tmp;
	UINT8 *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;

	/* read status register */		  
	REG32(SFC_OPCODE) = 0x05;
	REG32(SFC_CTL) = 0x10;
	sync();
	udelay(_SFC_DELAY); 						
	tmp = REG8(temp_ptr);

	printf("before status reg = 0x%x\n", tmp);

	/* write enable */
	REG32(SFC_OPCODE) = 0x06;
	REG32(SFC_CTL) = 0x00;
	sync();
	udelay(_SFC_DELAY); 	
	tmp = REG8(temp_ptr);

	/* write status register , all memory protection*/
	REG32(SFC_OPCODE) = 0x01; 
	REG32(SFC_CTL) = 0x10;
	sync();
	udelay(_SFC_DELAY); 						
	REG8(temp_ptr) = 0x3c;

	/* read status registers until write operation completed*/
	do
	{
	   REG32(SFC_OPCODE) = 0x05;
	   REG32(SFC_CTL) = 0x10;			
	   sync();
	} while((tmp = REG8(temp_ptr))&0x1);

	printf("after status reg = 0x%x\n", tmp);

	return;
}

static void switch_read_mode(void)
{
	UINT8 tmp;
	UINT8 *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;

	REG32(SFC_OPCODE) = 0x00000003; //switch flash to read mode
	REG32(SFC_CTL) = 0x00000018; //command cycle
	tmp = REG8(temp_ptr);
	// restore register (avoid read flash bus hang)
	REG32(SFC_EN_WR) = 0x0;
	REG32(SFC_WAIT_WR) = 0x0;
	REG32(SFC_CE) = 0x00070707;
	sync();	
	udelay(_SFC_DELAY);
}

static void write_enable(void)
{
	unsigned char tmp;
	unsigned char *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;
	unsigned int sfc_opcode_org, sfc_ctl_org;
	
	sfc_opcode_org = REG32(SFC_OPCODE);
	sfc_ctl_org = REG32(SFC_CTL);

	/* read status registers until write operation completed*/
	REG32(SFC_OPCODE) = 0x06;
	REG32(SFC_CTL) = 0x00;			 
	sync();
	udelay(_SFC_DELAY);
	tmp = REG8(temp_ptr);

	REG32(SFC_OPCODE) = sfc_opcode_org;
	REG32(SFC_CTL) = sfc_ctl_org;
	sync();
	udelay(_SFC_DELAY);	
}

static void wait_done(void)
{
#if 1	
	udelay(_SFC_DELAY);
#else
	unsigned char *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;
	unsigned int sfc_opcode_org, sfc_ctl_org;
	
	sfc_opcode_org = REG32(SFC_OPCODE);
	sfc_ctl_org = REG32(SFC_CTL);

	/* read status registers until write operation completed*/
	REG32(SFC_OPCODE) = 0x05;
	REG32(SFC_CTL) = 0x10;			 
	sync();
	udelay(_SFC_DELAY);
	do
	{
		mdelay(1);
	} while(REG8(temp_ptr)&0x1);

	REG32(SFC_OPCODE) = sfc_opcode_org;
	REG32(SFC_CTL) = sfc_ctl_org;
	sync();
	udelay(_SFC_DELAY);
#endif
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
    unsigned char tmp;
    unsigned int size;
    s_device_type *device = (s_device_type *)dev;                                         
    unsigned char *loc;
    
    loc = (unsigned char *) dest;
	while(rem_size > 0)
	{
      /* show '/' in console */
	  print_uart("/");
		 
      /* write enable */
      REG32(SFC_OPCODE) = 0x06;
      REG32(SFC_CTL) = 0x00;
      sync();
	  udelay(_SFC_DELAY);	  
	  tmp = REG8(loc);

      //modify by Andy
      if ((rem_size >= 0x40000) && (((unsigned int)loc&(0x40000-1)) == 0) && (device->sec_256k_en == 1)) {	  	
         print_uart("(256k)");
         REG32(SFC_OPCODE) = 0xd8;
         REG32(SFC_CTL) = 0x08;
         sync();
         tmp = REG8(loc);
         size = 0x40000;
      }
      else if ((rem_size >= 0x10000) && (((unsigned int)loc&(0x10000-1)) == 0) && (device->sec_64k_en == 1)) {
		 print_uart("(64k)");
         REG32(SFC_OPCODE) = 0xd8;
         REG32(SFC_CTL) = 0x08;         
         sync();
         tmp = REG8(loc);
         size = 0x10000;
      }
      else if ((rem_size >= 0x8000) && (((unsigned int)loc&(0x8000-1)) == 0) && (device->sec_32k_en == 1)) {
		 print_uart("(32k)");
         REG32(SFC_OPCODE) = 0x52;
         REG32(SFC_CTL) = 0x08;
         sync();
         tmp = REG8(loc);
         size = 0x8000;
      }
      else if ((rem_size >= 0x1000) && (((unsigned int)loc&(0x1000-1)) == 0) && (device->sec_4k_en == 1)) {
		 print_uart("(4k)");
         if (device->id == PMC_4Mbit)
            REG32(SFC_OPCODE) = 0xd7;
         else
            REG32(SFC_OPCODE) = 0x20;
         REG32(SFC_CTL) = 0x08;
         sync();
         tmp = REG8(loc);
         size = 0x1000;
      }

      /* read status registers until write operation completed*/
      do
      {
         REG32(SFC_OPCODE) = 0x05;
         REG32(SFC_CTL) = 0x10;			  
         sync();
      } while((tmp = REG8(loc))&0x1);

      size = (rem_size > size)? size : rem_size ;
      rem_size -= size;

      loc += size;
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
	int i = 0;
	unsigned char tmp;
	s_device_type *device = (s_device_type *)dev;
	unsigned char *loc, *src;
	unsigned int length = rem_size;

	loc = (unsigned char *)dest;
	src = (unsigned char *)array_ptr;

	//need to swap data endian , if programmed by ARM
#if 1
	//swap endian
	printf("data swap endian, src = 0x%x\n", src);
	if ((((unsigned int)loc & 0x3) == 0) && (((unsigned int)src & 0x3) == 0) && (((unsigned int)length & 0x3) == 0)) {
		for (i = 0;i < length; i+=4) {
			//swap endian
			REG32(src) = swap_endian(REG32(src));
			src += 4;
		}
		src = (unsigned char *)array_ptr;
	}else {
		printf("dst = 0x%x, src = 0x%x, size = 0x%x not aligned to 4\n", loc, src, length);
		return -1;
	}
#endif

	//add by angus
	REG32(SFC_EN_WR) = 0x00000106;
	REG32(SFC_WAIT_WR) = 0x00000105;
	REG32(SFC_CE) = 0x00ffffff;

	/* write enable */
	REG32(SFC_OPCODE) = 0x06;
	REG32(SFC_CTL) = 0x00;
	sync();
	udelay(_SFC_DELAY);		
	tmp = REG8(loc);

	//issue write command
	REG32(SFC_OPCODE) = 0x02;
	REG32(SFC_CTL) = 0x18;
	sync();

	// if dest address is not on 256 byte boundary, use byte program until reach boundary
	while ((((UINT32)loc) & 0xff) && (rem_size > 0))
	{
		REG8(loc) = REG8(array_ptr);
		loc++;
		array_ptr++;

		rem_size--;

		/* show '.' in console */
		if ((rem_size & 0xff) == 0xff) {
			print_uart(".");
		}
		wait_done();
	} 

	//if flash support page program, we can use page program to reduce program time
	if (device->page_program)
	{
		//if writing data greater than one page(256 bytes)
		while(rem_size >= 256)
		{ 	
			/* show '.' in console */
			if ( !(i++ % 4)) {
				print_uart("p");
			}
			
			copy_memory((UINT8 *)loc, array_ptr, 256);
			
			/* shift to next page to writing */
			array_ptr += 256;
			loc += 256;
			rem_size -= 256;
			wait_done();
		}//end of page program
		
	}//end of page program


	/* left data in-sufficient to one page, we write it using byte program 
	   or flash doesn't support page program mode */
	while(rem_size--)
	{ 
		//*loc++ = *array_ptr++;
		REG8(loc) = REG8(array_ptr);
		loc++;
		array_ptr++;

		/* show '.' in console */
		if ((rem_size & 0xff) == 0xff) {
			print_uart(".");
		}			
		wait_done();
	}	

#if 0
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
#else
	if (verify_after_write)
	{

		loc = (unsigned char *)dest;
		i = 0;

		switch_read_mode();
		printf("\nverify: (0x%x, 0x%x, 0x%x)\n", (UINT32) loc, (UINT32) src, length);
		do {
			if (*loc != *src) {
				printf("0x%08x -> 0x%02x,  0x%08x -> 0x%02x\n", (UINT32)loc, *loc, (UINT32)src, *src);
				return -1;
			}
			loc++;
			src++;
			sync();
		} while (++i < length);
	}
#endif
	switch_read_mode();

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

	UINT8 *temp_ptr = (UINT8 *)SPI_BASE_ADDRESS;

#if 0
	/* switch to in-order mode */
	sync();
	//disable w-merge and r-bypass
	REG32(0x1801a018)=((REG32(0x1801a018) | 0x80000 ) & ~0x30000);
	sync();
	//enable command inorder
	REG32(0x1801a018)= (REG32(0x1801a018) | 0xc0000);
	sync();

    //REG32(SFC_POS_LATCH) = 0x00000001;   //set serial flash controller latch data at rising edge
    REG32(SFC_POS_LATCH) = 0x00000000;
    /* hcy :ice boot lower more */
    REG32(SFC_SCK) = 0x0101000f;   //lowering frequency
    REG32(SFC_CE) = 0x00090101;   //setup control edge	
#else
    REG32(SFC_SCK) = 0xf;   //lowering frequency
    mdelay(10);
    //REG32(SFC_POS_LATCH) = 0x1;   //set serial flash controller latch data at rising edge
    REG32(SFC_POS_LATCH) = 0x0;  //set serial flash controller latch data at falling edge	
    REG32(SFC_CE) = 0x00202020;   //setup control edge
	sync();
#endif

    mdelay(10);

	/* read Manufacture & device ID */
    REG32(SFC_OPCODE) = 0x9f;
    REG32(SFC_CTL) = 0x10;	
	sync();
	udelay(_SFC_DELAY); 	
    id = REG32(temp_ptr);

	print_uart("\nflash id [0x");
	print_val(id,8);
	print_uart("]\n");

	id = swap_endian(id);
    id >>= 8;
    //printf("\nflash id [0x%x]\n", id);

	print_uart("\nflash id [0x");
	print_val(id,6);
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
                	REG32(SFC_OPCODE) = 0x9f;
                	REG32(SFC_CTL) = 0x13;
					sync();
					udelay(_SFC_DELAY); 						
                	id = REG32(temp_ptr);
                	id >>= 16;
                	printf("\textension id [0x%x]\n", id);
        		//continue;
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
        REG32(0x1801a808) = 0xf;  //lower frequency 
        REG32(SFC_OPCODE) = 0x90;  //read id
        REG32(SFC_CTL) = 0x10;  //issue command
		sync();
		udelay(_SFC_DELAY); 						        
        id = REG32(temp_ptr);
        id >>= 16;
           
        for (idx = 0; idx < DEV_SIZE_S; idx++)
        {
            if ( s_device[idx].id == id )
            {
            	//special case: the same id have two mode, check ext-id
            	if (id == SPANSION_128Mbit)
            	{
            		/* read extended device ID */
                    REG32(SFC_OPCODE) = 0x90;
                    REG32(SFC_CTL) = 0x1b;
					sync();
					udelay(_SFC_DELAY); 											
                    id = REG32(temp_ptr);
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

#if 0	
	/* configure serial flash controller */
   
	sync();
	//disable w-merge and r-bypass
	REG32(0x1801a018) = ((REG32(0x1801a018) | 0x80000 ) & ~0x30000);
	sync();
	//enable command inorder
	REG32(0x1801a018) = (REG32(0x1801a018) | 0xc0000);
	sync();
    
//    REG32(0x1801a808) = 0x01010004;   //setup freq divided no
    REG32(0x1801a808) = 0x0101000f;   //lowering frequency

    REG32(SFC_CE) = 0x00090101;   //setup control edge

    REG32(SFC_WP) = 0x00000000;	//disable hardware potection
#endif

	unlock_flash();

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
	lock_flash();
	switch_read_mode();  
}
