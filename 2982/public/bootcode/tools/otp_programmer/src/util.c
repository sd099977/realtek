#include <sysdefs.h>
#include <stdio.h>
//#include <string.h>
#include "util.h"
#include "UART.h"
#include "io.h"

extern unsigned long strtoul(const char *str, char **endptr, int base);

unsigned int UartReg = (unsigned int )UART0_REG_BASE; 

#define MIPS_UART_REG_BASE_ADDR  (0x000000c4)
#define ST_PINMUX_REG_BASE       (0x18060200)
#define GPIO_ST_MUXCFG_1         (ST_PINMUX_REG_BASE + 0x04)
#define PINMUX_REG_BASE          (0x18000800)
#define GPIO_MUXCFG_17           (PINMUX_REG_BASE + 0x44)

//Change to auto-detect UART port mode, by Andy
void init_uart(void)
{
//remove init, use u-boot init
	unsigned int uart_base;
	UartReg = (unsigned int)UART0_REG_BASE;
	if ((((rtd_inl(GPIO_ST_MUXCFG_1) >> 27) & 0x1f) == 0x9) && (((rtd_inl(GPIO_MUXCFG_17) >> 27) & 0x1f) == 0x2)) {
		uart_base = swap_endian(rtd_inl(MIPS_UART_REG_BASE_ADDR));
		if (((uart_base >> 24) & 0xff) == 0xb8) {
			uart_base = uart_base & (~0xE0000000);
			if (uart_base == UART0_REG_BASE) {
				UartReg = (unsigned int)UART0_REG_BASE;
				//printf("\nuse UART0, base=0x%x\n", uart_base);
			}
			else {
				UartReg = (unsigned int)UART1_REG_BASE;
				//printf("\nuse UART1, base=0x%x\n", uart_base);		
			}
			return;
		}
		else { //something goes wrong ,set default
			UartReg = (unsigned int)UART0_REG_BASE;
			//printf("\nuse default UART0 %x\n");
		}			
	} else {
		if (((REG32(GPIO_ST_MUXCFG_1) >> 27) & 0x1f) == 0x9) {
			UartReg = (unsigned int)UART0_REG_BASE;
			//printf("\nuse UART0\n");
		}
		else {
			UartReg = (unsigned int)UART1_REG_BASE;
			//printf("\nuse UART1\n");
		}
	}
}

/* wait interval in microseconds */
void sys_wait_us(INT32U us)
{
#define TC7CVR 0x1801b63c

	INT32U first, current, last;
	//INT32U cycle_per_count;
	
	first = rtd_inl(TC7CVR);
	
	last  = first + 27*us;
	
	if (last >= first)
		do {
			/* no wrap - continue while between first and last */
			current = rtd_inl(TC7CVR);
		}
		while( current < last && current >= first );
	else
		do {
			/* wrap - continue until between first and last */
			current = rtd_inl(TC7CVR);
		}
		while( current < last || current >= first );
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

#if 0 //Change to auto-detect UART port mode, by Andy
void tx_byte(INT8U data)
{
   while ((READ_REG_INT32U(UART1_LSR) & LSR_THRE) != LSR_THRE){
      // wait for THRE==1 (TX FIFO empty)
   }
   WRITE_REG_INT32U(UART1_THR, (INT32U)data);
}
#else
void tx_byte(INT8U data)
{
   while ((READ_REG_INT32U(UartReg + 0x14) & LSR_THRE) != LSR_THRE){
      // wait for THRE==1 (TX FIFO empty)
   }
   WRITE_REG_INT32U(UartReg, (INT32U)data);
}
#endif

void print_uart(char *message)
{
	unsigned int i=0;
	while(message[i] != '\0') {
		if (message[i] == '\n') {
			tx_byte(0xd);
			tx_byte(0xa); 
			i++;
		}
		else
			tx_byte(message[i++]);
	}
}

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

unsigned int hexstr2int(char *s)
{
	return (unsigned int) strtoul (s, (char **) 0, 16);
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

/*
char get_sw_lock(int delay)
{
	int i, timeout;

	timeout = 0x800;	// guess value
	do {
		if (REG32(KSEG1(HW_SEMAPHORE_ADDR)) == 1) {
			if (REG32(KSEG1(SW_MUTEX_1)) == 1) {
				REG32(KSEG1(SW_MUTEX_1)) = 0;
				REG32(KSEG1(HW_SEMAPHORE_ADDR)) = 0;
				return 0;
			}
		}

		// delay for a while (if specified)
		i = delay;
		while (i--);
	} while (timeout--);
	
	printf("[WARN] %s timeout!\n", __FUNCTION__);
	return -1;
}

void release_sw_lock(void)
{
	if (REG32(KSEG1(SW_MUTEX_1)) == 0)
		REG32(KSEG1(SW_MUTEX_1)) = 1;
	else
		printf("[WARN] sw lock already released\n");
}
*/

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

unsigned int swap_endian(unsigned int input)
{
	UINT32 output;

	output = (input & 0xff000000)>>24|
			 (input & 0x00ff0000)>>8|
			 (input & 0x0000ff00)<<8|
			 (input & 0x000000ff)<<24;

	return output;
}
