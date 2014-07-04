#ifndef __SED_UART_H__
#define __SED_UART_H__

#include "sed_types.h"

/* UART0 */
#if defined(FPGA)
#define UART0_REG_BASE	0xb801bc00 //MISC UART1
#else
#define UART0_REG_BASE  0xb8062300 //ISO UART
#endif

#define U0RBR_THR_DLL	(UART0_REG_BASE + 0x0)
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

/* UART1 */
#if defined(FPGA)
#define UART1_REG_BASE	0xb801b100 //MISC UART2
#else
#define UART1_REG_BASE	0xb801bc00 //MISC UART1
#endif

#define U1RBR_THR_DLL	(UART1_REG_BASE + 0x0)
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

#define UARTINFO_DATA_READY_MASK		0x01
#define UARTINFO_TEMT_MASK				0x40
#define UARTINFO_THRE_MASK				0x20
#define UARTINFO_TRANSMITTER_READY_MASK	(UARTINFO_TEMT_MASK | UARTINFO_THRE_MASK)

typedef union _UARTREG_RBR_THR_DLL
{
	uint32 Value;

	struct {                   //Register: UART_RBR_THR_DLL (0x1801_B200)
		uint32 Reserved: 24;   //IO[31:8]: Reserved
		uint32 DLL: 8;         //IO[7:0]: Divisor Latch LSB
	} Fields0;

	struct {                   //Register: UART_RBR_THR_DLL (0x1801_B200)
		uint32 Reserved: 24;   //IO[31:8]: Reserved
		uint32 RBD: 8;         //IO[7:0]: Read: Receiver Buffer Data
	} Fields1;

	struct {                   //Register: UART_RBR_THR_DLL (0x1801_B200)
		uint32 Reserved: 24;   //IO[31:8]: Reserved
		uint32 THD: 8;         //IO[7:0]: Write: Transmitter Holding Data
	} Fields2;
} UARTREG_RBR_THR_DLL;

typedef union _UARTREG_IER_DLM
{
	uint32 Value;

	struct {                    //Register: UART_IER_DLH (0x1801_B204)
		uint32 Reserved: 24;    //IO[31:8]: Reserved
		uint32 DLM: 8;          //IO[7:0]: Divisor Latch MSB
	} Fields0;

	struct {                    //Register: UART_IER_DLM (0x1801_B204)
		uint32 Reserved: 28;    //IO[31:4]: Reserved
		uint32 EDSSI: 1;        //IO[3]: Enable modem status register interrupt
		uint32 ELSI: 1;         //IO[2]: Enable receiver line status interrupt
        uint32 ETBEI: 1;        //IO[1]: Enable transmitter holding register empty interrupt
		uint32 ERBI: 1;         //IO[0]: Enable received data available interrupt
	} Fields1;
} UARTREG_IER_DLM;

typedef union _UARTREG_IIR_FCR
{
	uint32 Value;

	struct {                    //Register: UART_IIR_FCR (0x1801_B208)
		uint32 Reserved1: 24;   //IO[31:8]: Reserved
		uint32 FIFO16: 2;		//IO[7:6]: FIFO16
								//		 - 00b = no FIFO
								//		 - 11b = 16-byte FIFO
		uint32 Reserved0: 2;	//IO[5:4]: Reserved
		uint32 IID: 3;			//IO[3:1]: IID
        						//		 - 000b: Modem Status Changed
								//		 - 001b: THR empty
								//		 - 010b: Received Data available
								//		 - 011b: Receiver Status
								//		 - 110b: Character Time Out
		uint32 IPND: 1;         //IO[0]: Interrupt pending
								//		 - 0b = interrupt pending
	} Fields0;

	struct {                    //Register: UART_IIR_FCR (0x1801_B208)
		uint32 Reserved1: 24;   //IO[31:8]: Reserved
		uint32 RTRG: 2;			//IO[7:6]: Receiver trigger level
								//		   Trigger level: 14-byte
								//		  - 00b = 01 Bytes
								//		  - 01b = 04 Bytes
								//		  - 10b = 08 Bytes
								//		  - 11b = 14 Bytes
		uint32 Reserved0: 2;	//IO[5:4]: Reserved
		uint32 DMAM: 1;		    //IO[3]: DMA mode enable
		uint32 TFRST: 1;		//IO[2]: Transmitter FIFO reset.
        						//		 Writes 1 to clear the transmitter FIFO.
		uint32 RFRST: 1;		//IO[1]: Receiver FIFO reset. 
        						//		 Writes 1 to clear the receiver FIFO.
		uint32 EFIFO: 1;        //IO[0]: Enable FIFO.
        						//		 When this bit is set, enable the transmitter
        						//		 and receiver FIFOs. Changing this bit clears
        						//		 the FIFOs.
	} Fields1;
} UARTREG_IIR_FCR;

typedef union _UARTREG_LCR
{
	uint32 Value;
	struct {                    //Register: UART_LCR (0x1801_B20C)
		uint32 Reserved: 24;    //IO[31:8]: Reserved
		uint32 DLAB: 1;			//IO[7]: Divisor latch access bit
		uint32 BRK: 1;			//IO[6]: Break control.
								//		 Set this bit force TXD to the spacing (low) state.
								//		 Clear this bit to disable break condition.
		uint32 EPS: 2;			//IO[5:4]: Even parity select
								//		  - 00b: odd parity
								//		  - 01b: even parity
								//		  - 10b: mark parity
								//		  - 11b: space parity
 		uint32 PEN: 1;			//IO[3]: Parity enable
		uint32 STP: 1;			//IO[2]: Number of stop bits
								//		  - 0b: 1 bit
								//		  - 1b: 2 bits
		uint32 WLS: 2;          //IO[1:0]: Word length select
								//		  - 00b: 5 bits
								//		  - 01b: 6 bits
								//		  - 10b: 7 bits
								//		  - 11b: 8 bits
	} Fields;
} UARTREG_LCR;

typedef union _UARTREG_MCR
{
	uint32 Value;
	struct {                    //Register: UART_MCR (0x1801_B210)
		uint32 Reserved1: 27;   //IO[31:5]: Reserved
		uint32 LOOP: 1;			//IO[4]: Loopback
		uint32 Reserved0: 2;	//IO[3:2]: Reserved
		uint32 RTS: 1;			//IO[1]: Request to send
								//		  - 0b: Set RTS# high
								//		  - 1b: Set RTS# low
		uint32 DTR: 1;          //IO[0]: Data terminal Ready.
								//		  - 0b: Set DTR# high
								//		  - 1b: Set DTR# low
	} Fields;
} UARTREG_MCR;

typedef union _UARTREG_LSR
{
	uint32 Value;
	struct {                    //Register: UART_LSR (0x1801_B214)
		uint32 Reserved: 24;    //IO[31:8]: Reserved
		uint32 RFE: 1;			//IO[7]: Errors in receiver FIFO.
        						//		 At least one parity, framing and break error in the FIFO
		uint32 TEMT: 1;			//IO[6]: Transmitter empty
								//		 - Character mode: both THR and TSR are empty.
								//		 - FIFO mode: both transmitter FIFO and TSR are empty
		uint32 THRE: 1;			//IO[5]: Transmitter holding register empty.
								//		 - Character mode: THR is empty.
								//		 - FIFO mode: transmitter FIFO is empty
		uint32 BI: 1;			//IO[4]: Break interrupt indicator
		uint32 FE: 1;			//IO[3]: Framing error
		uint32 PE: 1;			//IO[2]: Parity error
		uint32 OE: 1;			//IO[1]: Overrun error.
        						//		 An overrun occurs when the receiver FIFO is
        						//		 full and the next character is completely received
        						//		 in the receiver shift register. An OE is indicated.
        						//		 The character in the shift register will be overwritten
 		uint32 DR: 1;           //IO[0]: Data ready.
								//		 - Character mode: data ready in RBR
								//		 - FIFO mode: receiver FIFO is not empty
	} Fields;
} UARTREG_LSR;

typedef union _UARTREG_MSR
{
	uint32 Value;
	struct {                    //Register: UART_MSR (0x1801_B218)
		uint32 Reserved1: 24;   //IO[31:8]: Reserved
		uint32 DCD: 1;			//IO[7]: DCD
        						//		 - In loopback mode, returns the bit 2 of MCR.
        						//		 - In normal mode, returns 1.
		uint32 RI: 1;			//IO[6]: RI
        						//		 - In loopback mode, returns the bit 3 of MCR.
        						//		 - In normal mode, returns 0.
		uint32 DSR: 1;			//IO[5]: DSR
        						//		 - In loopback mode, returns the bit 0 of MCR
								//		 - In normal mode, returns 1.
		uint32 CTS: 1;			//IO[4]: Clear to send.
								//		 - 0b: CTS# detected high
								//		 - 1b: CTS# detected low
		uint32 Reserved0: 3;	//IO[3:1]: Reserved
		uint32 DCTS: 1;         //IO[0]: Delta clear to send.
        						//		 CTS# signal transits.
	} Fields;
} UARTREG_MSR;

typedef union _UARTREG_SCR
{
	uint32 Value;
	struct {                    //Register: UART_SCR (0x1801_B21C)
		uint32 Reserved: 24;    //IO[31:8]: Reserved
		uint32 SCR: 8;			//IO[7:0]: Scratch Register
	} Fields;
} UARTREG_SCR;

//==========================================================================
typedef struct _UARTREG
{
	UARTREG_RBR_THR_DLL	UartRbrTheDll;	//0x1801_B200: UART_RBR_THR_DLL
	UARTREG_IER_DLM		UartIerDlm;    	//0x1801_B204: UART_IER_DLM
	UARTREG_IIR_FCR		UartIirFcr;    	//0x1801_B208: UART_IIR_FCR
	UARTREG_LCR			UartLcr;       	//0x1801_B20C: UART_LCR
	UARTREG_MCR			UartMcr;       	//0x1801_B210: UART_MCR
	UARTREG_LSR			UartLsr;       	//0x1801_B214: UART_LSR
	UARTREG_MSR			UartMsr;       	//0x1801_B218: UART_MSR
	UARTREG_SCR			UartScr;       	//0x1801_B21C: UART_SCR	
} UARTREG;

void sed_uart_init (void);
int sed_uart_read (uint8 *ch);
void sed_uart_write (uint8 *ch);

#endif
