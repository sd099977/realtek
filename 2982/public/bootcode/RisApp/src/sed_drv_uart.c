#include "sed_drv_common.h"
#include "sed_drv_pinmux.h"
#include "sed_drv_uart.h"

volatile UARTREG *UartReg  = (UARTREG *)UART0_REG_BASE; //Use UART0
volatile UARTREG *Uart1Reg = (UARTREG *)UART1_REG_BASE; //Use UART1

#define RPC_DEV        UART0_REG_BASE
#define CON_DEV        UART1_REG_BASE

unsigned char rtk_getc(unsigned char* ch,unsigned int dev_no)
{
	if ((REG32(dev_no + UART_LSR) & UARTINFO_DATA_READY_MASK) == 0)
		return -1;

	*ch = (uint8) (REG32(dev_no + UART_RBR) & 0xFF);
	return 0;
}

void rtk_putc(char c,unsigned int dev_no)
{
    while ((REG32(dev_no+UART_LSR) & 0x60) == 0);
    REG32(dev_no+UART_THR) = c;
}

void sed_uart_init (void)
{
	sed_pinmux_uart();

#if defined (SIRIUS)
	//sed_pinmux_uart();

	/* Initial UART0 */
	REG32(U0LCR) = 0x90;
#if defined(FPGA)
	REG32(U0RBR_THR_DLL) = 0xe;	// 115200 baud (for FPGA 25MHz) 25*1000*1000/115200/16
#else
	REG32(U0RBR_THR_DLL) = 0xf;	// 115200 baud (for ASIC 27MHz)
#endif
	REG32(U0IER_DLH) = 0;
	REG32(U0LCR) = 0x3;		// 8-N-1
	REG32(U0IIR_FCR) = 0xb7;
	REG32(U0IER_DLH) = 0;

#if !defined(FPGA)
	/* Initial UART1 */
	REG32(U1LCR) = 0x90;
#if defined(FPGA)
	REG32(U1RBR_THR_DLL) = 0xe;	 // 115200 baud (for FPGA 25MHz) 25*1000*1000/115200/16
#else
	REG32(U1RBR_THR_DLL) = 0xea; // 115200 baud (for ASIC 432MHz)
#endif
	REG32(U1IER_DLH) = 0;
	REG32(U1LCR) = 0x3; 	// 8-N-1
	REG32(U1IIR_FCR) = 0xb7;
	REG32(U1IER_DLH) = 0;
#endif
#endif
}

void sed_uart_write (uint8 *ch)
{
	//while((UartReg->UartLsr.Value & UARTINFO_TRANSMITTER_READY_MASK) !=
	//								UARTINFO_TRANSMITTER_READY_MASK);
	//UartReg->UartRbrTheDll.Value = *ch;
	rtk_putc(*ch,UART0_REG_BASE);
}

int sed_uart_read (uint8 *ch)
{
//	if ((UartReg->UartLsr.Value & UARTINFO_DATA_READY_MASK) == 0)
//		return -1;
//
//	*ch = (uint8) (UartReg->UartRbrTheDll.Value & 0xFF);
//	return 0;
	return rtk_getc(ch,UART0_REG_BASE);
}

//void rtk_putc(uint8 ch){
//	while((Uart1Reg->UartLsr.Value & UARTINFO_TRANSMITTER_READY_MASK) !=
//									UARTINFO_TRANSMITTER_READY_MASK);
//	Uart1Reg->UartRbrTheDll.Value = ch;
//}

void sed_uart1_write (uint8 *ch)
{
	//rtk_putc(*ch);
	rtk_putc(*ch,UART1_REG_BASE);
}

int sed_uart1_read (uint8 *ch)
{
//	if ((Uart1Reg->UartLsr.Value & UARTINFO_DATA_READY_MASK) == 0)
//		return -1;
//
//	*ch = (uint8) (Uart1Reg->UartRbrTheDll.Value & 0xFF);
//	return 0;
	return rtk_getc(ch,UART1_REG_BASE);
}

