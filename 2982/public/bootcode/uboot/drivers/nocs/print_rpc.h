#ifndef __PRINT_RPC_H__
#define __PRINT_RPC_H__

#define UART0_BASE      0x18062300
#define UART1_BASE      0x1801bc00

#define UART_RBR        0x00
#define UART_THR        0x00
#define UART_DLL        0x00
#define UART_DLM        0x04
#define UART_FCR        0x08
#define UART_LCR        0x0C
#define UART_MCR        0x10
#define UART_LSR        0x14
#define UART_MSR        0x18
#define UART_SCR        0x1C

#define RPC_PORT 1
#if (RPC_PORT==0)   //use uart0 as rpc port

#define RPC_DEV        UART0_BASE
#define CON_DEV        UART1_BASE

#define BDPRINT(fmt, args...)			\
            printf1(fmt,## args)
#define BDPRINT_FUNC(fmt, args...)			\
            printf1("%s(%d)" fmt,__func__ ,__LINE__,## args)

#define BD_INFO(fmt, args...)			\
             printf1("%s(%d)" fmt,__func__ ,__LINE__,## args)

#else   //use uart1 as rpc port

#define RPC_DEV        UART1_BASE
#define CON_DEV        UART0_BASE
#define BDPRINT(fmt, args...)			\
            printf(fmt,## args)
#define BDPRINT_FUNC(fmt, args...)			\
            printf("%s(%d)\n" fmt,__func__ ,__LINE__,## args)

#define BD_INFO(fmt, args...)			\
            printf("%s(%d)" fmt,__func__ ,__LINE__,## args)

/*
#define OTP_DBG(fmt, args...)         \
            printf("[OTP][DBG]" fmt, ##args)
*/
#endif

void rtkbsd_rpc_puts(unsigned char *s,int cnt);
void rtk_putc(char c,unsigned int dev_no);
unsigned char rtk_getc(unsigned char* ch,unsigned int dev_no);
int printf1(const char *fmt, ...);
int print_rpc(const char *fmt, ...);




#endif  //?#define __PRINT_RPC_H__