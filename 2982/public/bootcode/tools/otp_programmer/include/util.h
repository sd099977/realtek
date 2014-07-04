#include <sysdefs.h>
#include "io.h"

#ifndef _typedef_H_
#define _typedef_H_

   // Define Data type (already defined in sysdefs.h)
/*
   typedef unsigned long long INT64U;
   typedef unsigned int       INT32U;
   typedef unsigned short int INT16U;
   typedef unsigned char      INT8U;
   typedef int                INT32;
   typedef short int          INT16;
   typedef char               INT8;
   typedef unsigned char      BOOLEAN;
*/
   #define INT64U             UINT64
   #define INT32U             UINT32
   #define INT16U             UINT16
   #define INT8U              UINT8
   #define BOOLEAN            UINT8
   
   #define true               (1 == 1)
   #define false              (0 == 1)
   #define OK                 true
   #define NG                 false
   #define M1_0               ((INT32U)(0x1))
   #define M1_1               ((INT32U)(0x1) << 1)
   #define M1_2               ((INT32U)(0x1) << 2)
   #define M1_3               ((INT32U)(0x1) << 3)
   #define M1_4               ((INT32U)(0x1) << 4)
   #define M1_5               ((INT32U)(0x1) << 5)
   #define M1_6               ((INT32U)(0x1) << 6)
   #define M1_7               ((INT32U)(0x1) << 7)
   #define M1_8               ((INT32U)(0x1) << 8)
   #define M1_9               ((INT32U)(0x1) << 9)
   #define M1_10              ((INT32U)(0x1) << 10)
   #define M1_11              ((INT32U)(0x1) << 11)
   #define M1_12              ((INT32U)(0x1) << 12)
   #define M1_13              ((INT32U)(0x1) << 13)
   #define M1_14              ((INT32U)(0x1) << 14)
   #define M1_15              ((INT32U)(0x1) << 15)
   #define M1_16              ((INT32U)(0x1) << 16)
   #define M1_17              ((INT32U)(0x1) << 17)
   #define M1_18              ((INT32U)(0x1) << 18)
   #define M1_19              ((INT32U)(0x1) << 19)
   #define M1_20              ((INT32U)(0x1) << 20)
   #define M1_21              ((INT32U)(0x1) << 21)
   #define M1_22              ((INT32U)(0x1) << 22)
   #define M1_23              ((INT32U)(0x1) << 23)
   #define M1_24              ((INT32U)(0x1) << 24)
   #define M1_25              ((INT32U)(0x1) << 25)
   #define M1_26              ((INT32U)(0x1) << 26)
   #define M1_27              ((INT32U)(0x1) << 27)
   #define M1_28              ((INT32U)(0x1) << 28)
   #define M1_29              ((INT32U)(0x1) << 29)
   #define M1_30              ((INT32U)(0x1) << 30)
   #define M1_31              ((INT32U)(0x1) << 31)
   #define M0_0               (~M1_0 )
   #define M0_1               (~M1_1 )
   #define M0_2               (~M1_2 )
   #define M0_3               (~M1_3 )
   #define M0_4               (~M1_4 )
   #define M0_5               (~M1_5 )
   #define M0_6               (~M1_6 )
   #define M0_7               (~M1_7 )
   #define M0_8               (~M1_8 )
   #define M0_9               (~M1_9 )
   #define M0_10              (~M1_10)
   #define M0_11              (~M1_11)
   #define M0_12              (~M1_12)
   #define M0_13              (~M1_13)
   #define M0_14              (~M1_14)
   #define M0_15              (~M1_15)
   #define M0_16              (~M1_16)
   #define M0_17              (~M1_17)
   #define M0_18              (~M1_18)
   #define M0_19              (~M1_19)
   #define M0_20              (~M1_20)
   #define M0_21              (~M1_21)
   #define M0_22              (~M1_22)
   #define M0_23              (~M1_23)
   #define M0_24              (~M1_24)
   #define M0_25              (~M1_25)
   #define M0_26              (~M1_26)
   #define M0_27              (~M1_27)
   #define M0_28              (~M1_28)
   #define M0_29              (~M1_29)
   #define M0_30              (~M1_30)
   #define M0_31              (~M1_31)

#define NULL		          ((void *)0)

#endif  // _typedef_H_

#ifndef _RegisterAccess_H_
#define _RegisterAccess_H_

// macro definition

#if 0
#define READ_REG_INT64U(Addr)        *((volatile INT64U*)(Addr))
#define WRITE_REG_INT64U(Addr,Value) *((volatile INT64U*)(Addr))=Value
#define READ_REG_INT32U(Addr)        *((volatile INT32U*)(Addr))
#define WRITE_REG_INT32U(Addr,Value) *((volatile INT32U*)(Addr))=Value
#define READ_REG_INT8U(Addr)         *((volatile INT8U*)(Addr))
#define WRITE_REG_INT8U(Addr,Value)  *((volatile INT8U*)(Addr))=Value
#else
#define READ_REG_INT32U(Addr)        rtd_inl(Addr)
#define WRITE_REG_INT32U(Addr,Value) rtd_outl(Addr, Value)
#define READ_REG_INT8U(Addr)         rtd_inb(Addr)
#define WRITE_REG_INT8U(Addr,Value)  rtd_outb(Addr, Value)
#endif

//#define REG8( addr )		  READ_REG_INT8U(addr)
//#define REG32( addr )		  READ_REG_INT32U(addr)

#endif  // _RegisterAccess_H_

#define HW_SEMAPHORE_ADDR	KSEG1(0x1801a000)
//#define SW_MUTEX_RESET		KSEG1(0x1801a600)
//#define SW_MUTEX_1		KSEG1(0x1801a604)

/************************************************************************
 *  Public function
 ************************************************************************/

void print_uart(char *message);
void print_val(INT32U val);
void set_memory(void *dst, UINT8 value, UINT32 size);
void copy_memory(void *dst, void *src, unsigned int size);
int compare_memory(void *s1, void *s2, unsigned int size);
int compare_str(const char *s1, const char *s2);

void sys_wait_us(INT32U us);
void tx_byte(INT8U data);
unsigned int hexstr2int(char *s);
//char get_sw_lock(int delay);
//void release_sw_lock(void);
unsigned int swap_endian(unsigned int input);
