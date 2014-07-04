#include <stdio.h>
//#include <string.h>
#include <sysdefs.h>
#include "util.h"
#include "pin_share_reg_rtd298x.h"

/************************************************************************
 *  Definitions for print to UART0
*************************************************************************/
#define _2_LINE		//# without TDS, RDS pins

#define POLLSIZE 		0x405	// 1029
#define HW_LIMIT_STOP	(POLLSIZE-64)  /* RTS OFF when 64 chars in buf */
#define HW_LIMIT_START	(POLLSIZE-32)  /* RTS  ON when 32 chars in buf */
#define SERIAL_MCR_DTR           0x01    /* Data Terminal Ready         */
#define SERIAL_MCR_RTS           0x02    /* Request To Send             */
#define SERIAL_LSR_DR            0x01    /* Character ready             */
#define SERIAL_LSR_THRE          0x20    /* Transmit Holding empty      */
#define SERIAL_MSR_CTS           0x10    /* Clear to send               */	//# b218


#define USE_NEW_MALLOC	1

/************************************************************************
 *  Public variables
 ************************************************************************/
UINT8 sys_l2cache_enabled = 0;	// do not use it

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int __heap_start_addr;

/* utl/cache_v7.c */
extern void flush_cache   (unsigned long, unsigned long);
extern void flush_dcache_all(void);
extern void flush_dcache_range(unsigned long start, unsigned long stop);
extern void invalidate_dcache_range(unsigned long start, unsigned long stop);
extern void invalidate_dcache_all(void);
extern void invalidate_icache_all(void);

/************************************************************************
 *  Static variables
 ************************************************************************/
static UINT16  recv_buffer[POLLSIZE];
static UINT16 *putptr = &recv_buffer[0];
static UINT16 *getptr = &recv_buffer[0];

static int serial_poll();
static void serial_write(UINT8  *p_param);

unsigned int UartReg = (unsigned int )UART0_REG_BASE; 


/************************************************************************
 *
 *                          sync
 *  Description :
 *  -------------
 *
 *
 *
 *  Parameters :
 *  ------------
 *
 *
 *
 *  Return values :
 *  ---------------
 *
 *
 *
 *
 ************************************************************************/

void init_uart(void)
{
//remove init, use u-boot init
#if 0
#ifdef ENABLE_UART_FUNC

	// init uart0
	REG32(U0LCR) = 0x90;
#ifdef FPGA
	REG32(U0RBR_THR_DLL) = 0xe;	// 115200 baud (for FPGA 25MHz) 25*1000*1000/115200/16
#else
	REG32(U0RBR_THR_DLL) = 0xf;	// 115200 baud (for ASIC 27MHz)
#endif
	REG32(U0IER_DLH) = 0;
	REG32(U0LCR) = 0x3;		// 8-N-1
	REG32(U0IIR_FCR) = 0xb7;
	REG32(U0IER_DLH) = 0;


#endif
#endif


#if 1
#define MIPS_UART_REG_BASE_ADDR			(0x000000c4)

	unsigned int uart_base;

	UartReg = (unsigned int)UART0_REG_BASE;

	if ((((REG32(GPIO_ST_MUXCFG_1) >> 27) & 0x1f) == 0x9) && (((REG32(GPIO_MUXCFG_17) >> 27) & 0x1f) == 0x2)) {
		uart_base = swap_endian(REG32(MIPS_UART_REG_BASE_ADDR));
		if (((uart_base >> 24) & 0xff) == 0xb8) {
			uart_base = uart_base & (~0xE0000000);
			if (uart_base == UART0_REG_BASE) {
				UartReg = (unsigned int)UART0_REG_BASE;
				printf("\nuse UART0, base=0x%x\n", uart_base);
			}
			else {
				UartReg = (unsigned int)UART1_REG_BASE;
				printf("\nuse UART1, base=0x%x\n", uart_base);		
			}
			return;
		}
		else { //something goes wrong ,set default
			UartReg = (unsigned int)UART0_REG_BASE;
			printf("\nuse default UART0 %x\n");
		}			
	} else {
		if (((REG32(GPIO_ST_MUXCFG_1) >> 27) & 0x1f) == 0x9) {
			UartReg = (unsigned int)UART0_REG_BASE;
			printf("\nuse UART0\n");
		}
		else {
			UartReg = (unsigned int)UART1_REG_BASE;
			printf("\nuse UART1\n");
		}
	}
#endif	

}

#ifdef SYNC_ASM
void sync()
{
	asm(".set mips3");
	asm("sync");
	asm(".set mips1");
}
#else
void sync()
{
	__SYNC();
}
#endif


void print_uart(char *message)
{
#ifdef ENABLE_UART_FUNC

/*
	unsigned int i=0;
	while(message[i] != '\0') {
		if (message[i] == '\n') {
			REG32(UART0_REG) = 0xd;
			REG32(UART0_REG) = 0xa;
			i++;
		} else
			REG32(UART0_REG) = message[i++];
	}
	sync();
*/

	UINT8 ch;
	while(*message != '\0') {
		ch = *message++;

		if (ch == '\n') {
			ch = 0xd;
			serial_write(&ch);
			ch = 0xa;
		}
		serial_write(&ch);
	}
#endif
}

int puts(char *message)
{
	print_uart(message);
	return 0;
}

static int serial_poll()
{

    UINT32 lstat;
    UINT32 rdata;
    //UINT32 room;
#ifdef ENABLE_UART_FUNC

    for(lstat = REG32(UartReg + 0x14); lstat & SERIAL_LSR_DR; lstat = REG32(UartReg + 0x14))
    {
        rdata = REG32(UartReg) & 0xff;

        /* compute room left in buffer, AFTER this byte has been put */
        // modify by alan
        //room = ((UINT32)getptr - (UINT32)putptr - 1) &
        //                     ((POLLSIZE - 1) * sizeof(*putptr));
        //room = ((UINT32)getptr - (UINT32)putptr - 1) & buff_size_factor;

#ifndef _2_LINE
        if (room <= HW_LIMIT_STOP * sizeof(*putptr) )
        {
            REG32(UartReg + 0x10) &= ~SERIAL_MCR_RTS;
        }
#endif
	/*
        if(room == 0)
        {
        */
            /* overwrite previous char (overflow anyway) */
        /*
            if (--putptr < &recv_buffer[0])
                putptr= &recv_buffer[POLLSIZE-1];
        }
	*/

        *putptr = (lstat << 8) | rdata;


        /* increase putptr to its future position */
        if( ++putptr >= &recv_buffer[POLLSIZE] )
            putptr= &recv_buffer[0];


        // check if the buffer is full (add by alan)
	if (putptr == getptr)
	{
	    // stay putptr in the same position
	    if (putptr == &recv_buffer[0])
	    	putptr = &recv_buffer[POLLSIZE-1];
	    else
	    	putptr--;
	}

    }
#endif
    return lstat;
}

static void serial_write(UINT8  *p_param)
{
#ifdef ENABLE_UART_FUNC

   UINT32 x;
#ifndef _2_LINE
   UINT32 y;
#endif

    for (;;)
    {
        /* OBS: LSR_OE, LSR_PE, LSR_FE and LSR_BI are cleared on read */
        x = serial_poll();
        x = x & SERIAL_LSR_THRE;
#ifndef _2_LINE
        y = REG32(UartReg + 0x18);
        y = y & SERIAL_MSR_CTS;
        if ( x && y )
#else
        if ( x )
#endif
             break;
    }


    REG32(UartReg) = *p_param;
#endif
}

void set_memory(void *dst, UINT8 value, UINT32 size)
{
	UINT32 i;
	for (i=0; i<size; i++)
		REG8(((UINT32)dst) + i) = value;
}

void copy_memory(void *dst, void *src, UINT32 size)
{
	UINT32 i;
	for (i=0; i<size; i++)
		REG8(((UINT32)dst) + i) = REG8(((UINT32)src) + i);
}

int compare_memory(void *s1, void *s2, UINT32 size)
{
	UINT32 i;
	char *p1, *p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	for (i = 0; i < size; i++)
	{
		if (p1[i] != p2[i])
			return (int)p1[i] - (int)p2[i];
	}

	return 0;
}

int memcmp(void *s1, void *s2, UINT32 size)
{
	UINT32 i;
	char *p1, *p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	for (i = 0; i < size; i++)
	{
		if (p1[i] != p2[i])
			return (int)p1[i] - (int)p2[i];
	}

	return 0;
}

int memcpy(void *destination, void *source, UINT32 size)
{
	UINT32 i;
	char *p1, *p2;

	p1 = (char *)destination;
	p2 = (char *)source;
	for (i = 0; i < size; i++)
	{
		p1[i] = p2[i];
	}

	return 0;
}

int compare_str(const char *s1, const char *s2)
{
	UINT32 i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (int)s1[i] - (int)s2[i];
		i++;
	}

	return 0;
}

void print_val(UINT32 val, UINT32 len)
{
	unsigned char ch;

	len--;
	do {
		ch = (val >> (len << 2)) & 0xf;
		ch += (ch < 0xa ? 0x30 : 0x37);
		serial_write(&ch);
	} while(len--);
}

void  mask_register(const unsigned int reg_addr, const unsigned int AND_filter, const unsigned int OR_filter)
{
	REG32(reg_addr) = (REG32(reg_addr) & AND_filter) | OR_filter;
}

void sys_dcache_flush(unsigned long start, unsigned long size)
{
	flush_cache(start, size);
}

void sys_dcache_flush_all(void)
{
	flush_dcache_all();
}

void sys_dcache_flush_invalidate_range(unsigned long start, unsigned long stop)
{
	invalidate_dcache_range(start, stop);
}

void sys_dcache_flush_invalidate_all(void)
{
	invalidate_dcache_all();
}

#if 1
void put_char(char ch)
{
#ifdef ENABLE_UART_FUNC
	char tmp;

	if (ch == '\n') {
		tmp = 0xd;
		serial_write((UINT8 *)&tmp);
		tmp = 0xa;
		serial_write((UINT8 *)&tmp);
	}
	else {
		serial_write((UINT8 *)&ch);
	}
#endif
}
#endif

unsigned int hexstr2int(char *s)
{
	return (unsigned int) strtoul (s, (char **) 0, 16);
}

void *simple_malloc(unsigned int n_bytes)
{
	static unsigned int alloc_count = 0;
	void *p;
#ifndef USE_NEW_MALLOC
	static unsigned int alloc_current = MALLOC_BASE;
#else
	static void *ptr = (void *)&__heap_start_addr;
#endif

	if ((alloc_count + n_bytes) > MAX_MALLOC_SIZE) {
		// exceed limit
		return NULL;
	}

	// always aligned to 8B boundary
	if (n_bytes & 0x7)
		n_bytes = (n_bytes & ((unsigned int)~0x7)) + 0x8;

#ifndef USE_NEW_MALLOC
	p = (void *)(alloc_current);
	alloc_current += n_bytes;
	alloc_count += n_bytes;
	return p;
#else
	p = ptr;
	ptr += n_bytes;
	alloc_count += n_bytes;
	return p;
#endif
}

int is_hex_digit(char c)
{
	if ((c >= '0') && (c <='9'))
		return 0;
	else if ((c >= 'A') && (c <= 'F'))
		return 0;
	else if ((c >= 'a') && (c <= 'f'))
		return 0;
	else
		return -1;
}
#if 0
void hexdump(const void *buf, unsigned int length)
{
	unsigned int i;
	char *ptr = (char *)buf;

	if ((buf == NULL) || (length == 0)) {
		printf("NULL\n");
		return;
	}

	printf("===> %s(0x%x, 0x%x):\n", __FUNCTION__, (UINT32)buf, length);
	for (i = 0; i < length; i++) {
		if (ptr[i] < 0x10)
			printf("0%X ", ptr[i]);
		else
			printf("%2X ", ptr[i]);

		if ((i & 0xf) == 0xf)
			printf("\n");
	}
	printf("\n");
}
#else
void prints(const char *ch)
{
#ifdef ENABLE_UART_FUNC

	unsigned char ch8;

	while (*ch != '\0') {
		ch8 = *ch;
		if (*ch++ == '\n') {
			ch8 = 0x0d;
			serial_write((UINT8 *)&ch8);
			ch8 = 0x0a;
		}
		serial_write((UINT8 *) &ch8);
	}
#endif
}
void print_hex(unsigned int value)
{
#ifdef ENABLE_UART_FUNC

	print_val(value, 8);
#endif
}


void hexdump(const char *str, const void *buf, unsigned int length)
{
	unsigned int i;
	char *ptr = (char *)buf;

	if ((buf == NULL) || (length == 0)) {
		prints("NULL\n");
		return;
	}

	prints(str == NULL ? __FUNCTION__ : str);
	prints(" (0x");
	print_hex((UINT32)buf);
	prints(")\n");

	for (i = 0; i < length; i++) {
		print_val((unsigned int)(ptr[i]), 2);

		if ((i & 0xf) == 0xf)
			prints("\n");
		else
			prints(" ");
	}
	prints("\n");
}
#endif

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void * memset(void * s,int c,unsigned int count)
{
	unsigned long *sl = (unsigned long *) s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if ( ((ulong)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}

unsigned int swap_endian(unsigned int input)
{
	UINT32 output;

	output = (input & 0xff000000)>>24|
			 (input & 0x00ff0000)>>8|
			 (input & 0x0000ff00)<<8|
			 (input & 0x000000ff)<<24;

	return output;
}
