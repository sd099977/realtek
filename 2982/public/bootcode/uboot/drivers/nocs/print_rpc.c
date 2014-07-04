#include "nocs_bsd_env.h"
#include "print_rpc.h"

void rtk_putc(char c,unsigned int dev_no)
{
    while ((rtd_inl(dev_no+UART_LSR) & 0x60) == 0);

    rtd_outl((dev_no+UART_THR),c);

}

unsigned char rtk_getc(unsigned char* ch,unsigned int dev_no)
{
    if(rtd_inl(dev_no + UART_LSR) & 0x1)
    {
        *ch = (unsigned char)rtd_inl(dev_no + UART_RBR);
        return 1;
    }else{
        return 0;
    }
}

void _rtk_putc(const char c,unsigned int dev_no)
{
    if (c == '\n')
        rtk_putc('\r',dev_no);

    rtk_putc(c,dev_no);
}

void rtk_u1_puts(const char *s,unsigned int dev_no)
{
    while (*s) {
        _rtk_putc(*s++,dev_no);
    }
}

void rtkbsd_rpc_puts(unsigned char *s,int cnt)
{
    int put_cnt;
    put_cnt = cnt;
    while (put_cnt--) {
        rtk_putc(*s++,RPC_DEV);
    }
}

/* printf function is only used for debugging at console mode */
int printf1(const char *fmt, ...)
{
    va_list args;
    unsigned int  i;
    char printbuffer[512];

    va_start(args, fmt);

    /* For this to work, printbuffer must be larger than
     * anything we ever want to print.
     */
    i = vscnprintf(printbuffer, sizeof(printbuffer), fmt, args);
    va_end(args);

    /* Print the string */
    rtk_u1_puts(printbuffer,CON_DEV);
    return i;
}

/* printf function is only used for debugging at console mode */
int print_rpc(const char *fmt, ...)
{
    va_list args;
    unsigned int  i;
    char printbuffer[512];

    va_start(args, fmt);

    /* For this to work, printbuffer must be larger than
     * anything we ever want to print.
     */
    i = vscnprintf(printbuffer, sizeof(printbuffer), fmt, args);
    va_end(args);

    /* Print the string */
    rtk_u1_puts(printbuffer,RPC_DEV);
    return i;
}