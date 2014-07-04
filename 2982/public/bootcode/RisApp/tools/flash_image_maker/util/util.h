#ifndef __UTIL_H__
#define __UTIL_H__

#include <project_config.h>
#include <platform_iso.h>

#define DUMP_NAND_FLASH
#define DUMP_SPI_FLASH
#define DUMP_SPI_NAND_FLASH
//#define DUMP_EMMC_FLASH
//#define FAKE_EMMC_API

#define NONE_SECURE_BOOT	0
#define NAGRA_SECURE_BOOT	1
#define RTK_SECURE_BOOT		2
#define DCAS_SECURE_BOOT	3

//#define FLASH_TYPE_NOR_PARALLEL		0x0
#define FLASH_TYPE_NAND       0x0
#define FLASH_TYPE_SPI        0x1
#define FLASH_TYPE_SPI_NAND   0x2
#define FLASH_TYPE_EMMC       0x3



#define REG8( addr )		  (*(volatile UINT8 *) (addr))
#define REG16( addr )		  (*(volatile UINT16 *)(addr))
#define REG32( addr )		  (*(volatile UINT32 *)(addr))
#define REG64( addr )		  (*(volatile UINT64 *)(addr))

#define CPU_TO_BE32( value ) ( (                ((UINT32)value)  << 24) |   \
                               ((0x0000FF00UL & ((UINT32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((UINT32)value)) >>  8) |   \
                               (                ((UINT32)value)  >> 24)   )
#define BE32_TO_CPU( value ) CPU_TO_BE32( value )


typedef unsigned char		UINT8;
typedef signed char			INT8;
typedef unsigned short		UINT16;
typedef signed short		INT16;
typedef unsigned int		UINT32;
typedef signed int			INT32;
typedef unsigned long long	UINT64;
typedef signed long long	INT64;
typedef UINT8				bool;






#define KUSEG_MSK		  0x80000000
#define KSEG_MSK		  0xE0000000
#define KUSEGBASE		  0x00000000
#define KSEG0BASE		  0x80000000
#define KSEG1BASE		  0xA0000000
#define KSSEGBASE		  0xC0000000
#define KSEG3BASE		  0xE0000000

#define UBOOT_DDR_OFFSET  0xa0000000

#define KSEG0(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG1BASE)
#define KSSEG(addr)	(((UINT32)(addr) & ~KSEG_MSK)  | KSSEGBASE)
#define KSEG3(addr)	(((UINT32)(addr) & ~KSEG_MSK)  | KSEG3BASE)
#define KUSEG(addr)	(((UINT32)(addr) & ~KUSEG_MSK) | KUSEGBASE)
#define PHYS(addr) 	((UINT32)(addr)  & ~KSEG_MSK)

#define offsetof(TYPE, MEMBER) ((unsigned int) &((TYPE *)0)->MEMBER)

#define MAX_MALLOC_SIZE		16*1024*1024
#define MALLOC_BASE		(0xa5000000 - UBOOT_DDR_OFFSET) //modify by angus, orininal value is 0xa6000000

#if 1
#if defined(FPGA)
#define UART0_REG_BASE		0x1801bc00  // 298x FPGA use MISC UART1
#else
#define UART0_REG_BASE		0x18062300  //
#endif
#else
#define UART0_REG_BASE		0x1801bc00  // force UART1
#endif

#define UART0_REG				UART0_REG_BASE

/* UART0 */
#define U0RBR_THR_DLL		(UART0_REG_BASE + 0x0)
#define U0IER_DLH		(UART0_REG_BASE + 0x4)
#define U0IIR_FCR		(UART0_REG_BASE + 0x8)
#define U0LCR			(UART0_REG_BASE + 0xc)
#define U0MCR			(UART0_REG_BASE + 0x10)
#define U0LSR			(UART0_REG_BASE + 0x14)
#define U0MSR			(UART0_REG_BASE + 0x18)
#define U0SCR			(UART0_REG_BASE + 0x1c)

#define U0FAR			(UART0_REG_BASE + 0x70)
#define U0TFR			(UART0_REG_BASE + 0x74)
#define U0RFW			(UART0_REG_BASE + 0x78)
#define U0USR			(UART0_REG_BASE + 0x7c)
#define U0TFL			(UART0_REG_BASE + 0x80)
#define U0RFL			(UART0_REG_BASE + 0x84)
#define U0SRR			(UART0_REG_BASE + 0x88)
#define U0SBCR			(UART0_REG_BASE + 0x8c)
#define U0BCR			(UART0_REG_BASE + 0x90)
#define U0SDMAM			(UART0_REG_BASE + 0x94)
#define U0SFE			(UART0_REG_BASE + 0x98)
#define U0SRT			(UART0_REG_BASE + 0x9c)
#define U0STET			(UART0_REG_BASE + 0xa0)
#define U0HTX			(UART0_REG_BASE + 0xa4)
#define U0DMASA			(UART0_REG_BASE + 0xa8)
#define U0CPR			(UART0_REG_BASE + 0xf4)
#define U0UCV			(UART0_REG_BASE + 0xf8)
#define U0CTR			(UART0_REG_BASE + 0xfc)


#if defined(FPGA)
#define UART1_REG_BASE		0x1801bc00  //see "298x_MISC_Arch_Spec.doc"
#else
#define UART1_REG_BASE		0x1801bc00  // use MISC UART2
#endif

/* UART1 */                                   
#define U1RBR_THR_DLL		(UART1_REG_BASE + 0x0)
#define U1IER_DLH		(UART1_REG_BASE + 0x4)
#define U1IIR_FCR		(UART1_REG_BASE + 0x8)
#define U1LCR			(UART1_REG_BASE + 0xc)
#define U1MCR			(UART1_REG_BASE + 0x10)
#define U1LSR			(UART1_REG_BASE + 0x14)
#define U1MSR			(UART1_REG_BASE + 0x18)
#define U1SCR			(UART1_REG_BASE + 0x1c)

#define U1FAR			(UART1_REG_BASE + 0x70)
#define U1TFR			(UART1_REG_BASE + 0x74)
#define U1RFW			(UART1_REG_BASE + 0x78)
#define U1USR			(UART1_REG_BASE + 0x7c)
#define U1TFL			(UART1_REG_BASE + 0x80)
#define U1RFL			(UART1_REG_BASE + 0x84)
#define U1SRR			(UART1_REG_BASE + 0x88)
#define U1SBCR			(UART1_REG_BASE + 0x8c)
#define U1BCR			(UART1_REG_BASE + 0x90)
#define U1SDMAM			(UART1_REG_BASE + 0x94)
#define U1SFE			(UART1_REG_BASE + 0x98)
#define U1SRT			(UART1_REG_BASE + 0x9c)
#define U1STET			(UART1_REG_BASE + 0xa0)
#define U1HTX			(UART1_REG_BASE + 0xa4)
#define U1DMASA			(UART1_REG_BASE + 0xa8)
#define U1CPR			(UART1_REG_BASE + 0xf4)
#define U1UCV			(UART1_REG_BASE + 0xf8)
#define U1CTR			(UART1_REG_BASE + 0xfc)




#define MAGIC_SYNC_ADDRESS 0x1801a020
#define __SYNC() 	do {REG32(KSEG1(MAGIC_SYNC_ADDRESS)) = 0; } while(0)


//#define printf
//#define puts pirnt_uart
#define ENABLE_UART_FUNC


//booting flash type
#define NAND_FLASH_BOOT		0
#define SPI_FLASH_BOOT		1
#define EMMC_BOOT		2
#define SPI_NAND_FLASH_BOOT	3
#define UNKNOWN_BOOT		(-1)


/************************************************************************
 *  Public function
 ************************************************************************/
void sync();
void init_uart(void);

void print_uart(char *message);
void print_val(UINT32 val, UINT32 len);
int is_hex_digit(char c);

void set_memory(void *dst, UINT8 value, UINT32 size);
void copy_memory(void *dest, void *src, UINT32 size);
int compare_memory(void *s1, void *s2, UINT32 size);
int memcmp(void *s1, void *s2, UINT32 size);
int memcpy(void *destination, void *source, UINT32 size);
int compare_str(const char *s1, const char *s2);
void mask_register(const unsigned int reg_addr, const unsigned int AND_filter, const unsigned int OR_filter);
void sys_dcache_flush(unsigned long start, unsigned long size);
void sys_dcache_flush_all(void);
void sys_dcache_flush_invalidate_range(unsigned long start, unsigned long stop);
void sys_dcache_flush_invalidate_all(void);
void put_char(char ch);
unsigned int hexstr2int(char *s);
void *simple_malloc(unsigned int n_bytes);
unsigned int swap_endian(unsigned int input);
#if 0
void hexdump(const void *buf, unsigned int length);
#else
void hexdump(const char *str, const void *buf, unsigned int length);
#endif
extern void * memset(void * s,int c,unsigned int count);

#endif
