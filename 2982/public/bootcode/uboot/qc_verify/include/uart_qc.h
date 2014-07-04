#include <rtd_types_qc.h>
#include <asm/arch/io.h> 

#define UART0REG_U0RbrTheDll 0x18062300
#define UART1REG_U1RbrTheDll 0x1801bc00
#define UART0REG_U0Lsr       0x18062314
#define UART1REG_U1Lsr       0x1801bc14

#define	UARTINFO_TEMT_MASK					0x40
#define	UARTINFO_THRE_MASK					0x20
#define UARTINFO_TRANSMITTER_READY_MASK		(UARTINFO_TEMT_MASK | UARTINFO_THRE_MASK)
#define	UARTINFO_DATA_READY_MASK			0x01


UINT8 UartDataRead(void);					//Read Data from UART0
void UartDataWrite(UINT8 byWriteData);	//Write Data to UART0
UINT8 Uart1DataRead(void);					//Read Data from UART1
void Uart1DataWrite(UINT8 byWriteData);	//Write Data to UART1
