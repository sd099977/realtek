
/************************************************************************
 *  Include files
 ************************************************************************/
#include <sysdefs.h>
//#include <stdio.h>
//#include <string.h>
#include "util.h"
#include "UART.h"
#include "rom_symbol.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
#if defined(ENV_FPGA)
extern void (*rom_hexdump)(const char *str, const void *buf, unsigned int length);
#endif

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
#if 1
/* wait interval in microseconds */
void sys_wait_us(volatile INT32U us)
{
#if 1
int i = us*0x100000;
int j=0;
int k;
while(i>0)
{
 i--;
	
}

return;
#endif
#define MIS_TC1CVR	0xb801b604
	INT32U first, current, last;
	//INT32U cycle_per_count;
	
	first = REG32(MIS_TC1CVR);
	
	last  = first + 27*us;
	
	if (last >= first)
		do {
			/* no wrap - continue while between first and last */
			current = REG32(MIS_TC1CVR);
		}
		while( current < last && current >= first );
	else
		do {
			/* wrap - continue until between first and last */
			current = REG32(MIS_TC1CVR);
		}
		while( current < last || current >= first );
#undef MIS_TC1CVR
}


int compare_memory(void *s1, void *s2, unsigned int size)
{
	unsigned int i;
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
#endif

void tx_byte(INT8U data)
{
#if 1
#define UART_LSR UART0_LSR
#define UART_THR UART0_THR
#else
#define UART_LSR UART1_LSR
#define UART_THR UART1_THR
#endif

   while ((READ_REG_INT32U(UART_LSR) & LSR_THRE) != LSR_THRE){
      // wait for THRE==1 (TX FIFO empty)
   }
   WRITE_REG_INT32U(UART_THR, (INT32U)data);

#undef UART_LSR
#undef UART_THR
}

void print_uart(char *message)
{
	unsigned int i=0;
	while(message[i] != '\0') {
		if (message[i] == '\n') {
			tx_byte(0xd);
			tx_byte(0xa); 
		}
		else {
			tx_byte(message[i]);
		}

		i++;
	}
}

int puts(char *s)
{
	print_uart(s);
	return 0;
}

int putchar(int c)
{
	tx_byte(c);
	return c;
}

#if 1
void print_val(INT32U val)
{
	char ch;
	int leading;
	int len;
	
	if (val == 0) {
		ch = 0x30;
		tx_byte(ch);
		return;
	}
	
	len = 7;
	leading = 0;
	
	do {
		ch=(val>>(len<<2))&0xf;
		// skip leading zero
		if ((ch == 0) && (leading == 0))
			continue;
		
		if (leading == 0)
			leading = 1;
	    
		if(ch<0xa)	ch+=0x30;
		else		ch+=0x37;
		
		tx_byte(ch);
	} while(len--);		
}
#endif

#if 0
unsigned int hexstr2int(char *s)
{
	return (unsigned int) strtoul (s, (char **) 0, 16);
}
#endif

void set_memory(void *dst, UINT8 value, UINT32 size)
{
	UINT32 i;	
	for (i=0; i<size; i++)
		REG8(((UINT32)dst) + i) = value;
}

void copy_memory(void *dst, void *src, unsigned int size)
{
	unsigned int i;	
	for (i=0; i<size; i++)
		REG8(((unsigned int)dst) + i) = REG8(((unsigned int)src) + i);
}

int IsHexStr(char *s)
{
	int i;
	for(i=0;i<8;i++)
	{
		if (!(((s[i]>='0')&&(s[i]<='9'))||((s[i]>='A')&&(s[i]<='F'))||
		    ((s[i]>='a')&&(s[i]<='f'))))
		    return -1;		
	}
	return 1;
}

int IsAllZeroStr(char *s)
{
	int i;
	for(i=0;i<8;i++)
	{
		if (s[i]!='0')
		    return -1;		
	}
	return 1;
}

void hexdump(const char *str, const void *buf, unsigned int length)
{
#if 0// defined(ROM__T__hexdump)
	// call function in ROM code (FPGA environment)
	rom_hexdump(str, buf, length);
#else
	unsigned int i;
	unsigned char *ptr = (unsigned char *)buf;
	
	if ((buf == NULL) || (length == 0)) {
		printf("NULL\n");
		return;
	}

	printf("\n%s (0x%x)\n\n", (str == NULL ? __FUNCTION__ : str), (unsigned int )buf);

	for (i = 0; i < length; i++) {
		printf("%02x ", ptr[i]);

		if ((i & 0xf) == 0xf)
			printf("\n\n");
	}
	printf("\n\n");
#endif
}

void wait_loop(volatile unsigned int count)
{
	while (count--)
		;
}

void bitwise_AND_OR(const unsigned int addr, const unsigned int AND_filter, 
	const unsigned int OR_filter)
{
	REG32(addr) = (REG32(addr) & AND_filter) | OR_filter;
}


void polling_done(const unsigned int addr, const unsigned int mask, const unsigned int value)
{
	while ((REG32(addr) & mask) != value)
			;
}

int swap_endian(UINT32 input)
{
	UINT32 output;

	output = (input & 0xff000000)>>24|
			 (input & 0x00ff0000)>>8|
			 (input & 0x0000ff00)<<8|
			 (input & 0x000000ff)<<24;
	
	return output;
}

// write back the dcache and invalidate
void dcache_flush_invalidate(void)
{
	asm volatile (
         "mfc0  $8, $20\n"
         "nop\n"
         "and   $8, 0xfffffdff\n"
         "mtc0  $8, $20\n"
         "nop\n"
         "or    $9, $8, 0x00000200\n"
         "mtc0  $9, $20\n"
         "nop\n"
         "mtc0  $8, $20\n"
         "nop\n"
   );
}

// write back the dcache
void dcache_flush(void)
{
   asm volatile (
         "mfc0  $8, $20\n"
         "nop\n"
         "and   $8, 0xfffffeff\n"
         "mtc0  $8, $20\n"
         "nop\n"
         "or    $9, $8, 0x00000100\n"
         "mtc0  $9, $20\n"
         "nop\n"
         "mtc0  $8, $20\n"
         "nop\n"
   );
}

