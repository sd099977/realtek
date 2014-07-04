#ifndef _UART_H_
   #define _UART_H_

#if defined(CONFIG_CHIP_SIRIUS)
   #define UART0Base    0xb8062300  //see "Sirius-DesignSpec-ISO_MISC_OFF_UART.doc"
#else
   #define UART0Base    (0xb8007800)
#endif

   #define UART0_RBR    (UART0Base + 0x00) // Receive Buffer Register (when DLAB=0)
   #define UART0_THR    (UART0Base + 0x00) // Transmit Holding Register (when DLAB=0)
   #define UART0_DLL    (UART0Base + 0x00) // Divisor Latch Low (when DLAB=1)
   #define UART0_IER    (UART0Base + 0x04) // Interrupt Enable Register (when DLAB=0)
   #define UART0_DLH    (UART0Base + 0x04) // Divisor Latch High (when DLAB=1)
   #define UART0_IIR    (UART0Base + 0x08) // Interrupt Identify Register (read only)
   #define UART0_FCR    (UART0Base + 0x08) // FIFO Control Register (write only)
   #define UART0_LCR    (UART0Base + 0x0C) // Line Control Register
   #define UART0_MCR    (UART0Base + 0x10) // Modem Control Register
   #define UART0_LSR    (UART0Base + 0x14) // Line Status Register
   #define UART0_MSR    (UART0Base + 0x18) // Modem Status Register
   #define UART0_SCR    (UART0Base + 0x1C) // Scratch Register

#if defined(CONFIG_CHIP_SIRIUS)
   #define UART1Base    0xb801bc00  //see "Sirius_MISC_Arch_Spec.doc"
#else
   #define UART1Base    (0xb8007900)
#endif

   #define UART1_RBR    (UART1Base + 0x00) // Receive Buffer Register (when DLAB=0)
   #define UART1_THR    (UART1Base + 0x00) // Transmit Holding Register (when DLAB=0)
   #define UART1_DLL    (UART1Base + 0x00) // Divisor Latch Low (when DLAB=1)
   #define UART1_IER    (UART1Base + 0x04) // Interrupt Enable Register (when DLAB=0)
   #define UART1_DLH    (UART1Base + 0x04) // Divisor Latch High (when DLAB=1)
   #define UART1_IIR    (UART1Base + 0x08) // Interrupt Identify Register (read only)
   #define UART1_FCR    (UART1Base + 0x08) // FIFO Control Register (write only)
   #define UART1_LCR    (UART1Base + 0x0C) // Line Control Register
   #define UART1_MCR    (UART1Base + 0x10) // Modem Control Register
   #define UART1_LSR    (UART1Base + 0x14) // Line Status Register
   #define UART1_MSR    (UART1Base + 0x18) // Modem Status Register
   #define UART1_SCR    (UART1Base + 0x1C) // Scratch Register

   #define LSR_DR    (0x01 << 0)  // LSR_0, Data Ready
   #define LSR_OE    (0x01 << 1) // LSR_1, Overrun Error
   #define LSR_PE    (0x01 << 2) // LSR_2, Parity Error
   #define LSR_FE    (0x01 << 3) // LSR_3, Frame Error
   #define LSR_BI    (0x01 << 4) // LSR_4, Break Interrupt
   #define LSR_THRE  (0x01 << 5) // LSR_5, THR empty
#endif  // _UART_H_

