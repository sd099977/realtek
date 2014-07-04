
/************************************************************************
 *  Include files
 ************************************************************************/
#include <sysdefs.h>
//#include <stdio.h>
//#include <string.h>
#include "util.h"
#include "UART.h"
//#include "rom_symbol.h"
#include "reset_def.h"

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

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
/*
 * bypass PKCS#1 v1.5 block format
 */
unsigned int skip_pkcs_v1_5_padding(char *ptr)
{
#if defined(ROM_DEBUG) || defined (CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(");
	print_hex((unsigned int)ptr);
	prints(")\n");
#endif
	unsigned int skipped;
	int i;
	const char algo_id[19] = {
		0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
		0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
		0x00, 0x04, 0x20};
	char pkcs_padding[0xe0];

	// construct padding header
	pkcs_padding[0] = 0;
	pkcs_padding[1] = 0x1;
	i = sizeof(pkcs_padding) - sizeof(algo_id);
	memset(pkcs_padding + 2, 0xff, i - 3);
	pkcs_padding[i - 1] = 0;
	copy_memory(pkcs_padding + i, (char *)algo_id, sizeof(algo_id));

//#if defined(ROM_DEBUG) || defined (CONFIG_DEBUG_UART_PRINT)
#if 0
	hexdump("pkcs_padding", pkcs_padding, sizeof(pkcs_padding));
	prints("\n");
#endif

	if (compare_memory(pkcs_padding, ptr, sizeof(pkcs_padding)) == 0)
		skipped = sizeof(pkcs_padding);
	else
		skipped = 0;

#if defined(ROM_DEBUG) || defined (CONFIG_DEBUG_UART_PRINT)
	prints("\nskip ");
	print_hex(skipped);
	prints(" bytes\n");
#endif

	return skipped;
}

void sync(void)
{
	REG32(KSEG1(MAGIC_SYNC_ADDRESS)) = 0;
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

void *memset(const void *dst, int c, unsigned int len)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(");
	print_hex((unsigned int)dst);
	prints(", ");
	print_hex(c);
	prints(", ");
	print_hex(len);
	prints(")\n");
#endif

	unsigned int i;
	char *buf;

	if (dst != NULL) {
		buf = (char *)dst;
		for (i = 0; i < len; i++)
			buf[i] = c;
	}

	return (void *)dst;
}
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

unsigned int calculate_image_checksum(unsigned int start_addr, unsigned int len)
{
	int i;
	unsigned int checksum;

	for (checksum = 0, i = 0; i < len; i++)
		checksum += REG8(start_addr + i);

	return checksum;
}

void hexdump(const char *str, const void *buf, unsigned int length)
{
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

unsigned int get_ic_version(void) {
	static unsigned int ver;
	if (ver == 0x0) {
		ver = rtd_inl(0xb8060000);
		debug("ver = 0x%x\n", ver);
	}
	return ver;
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
