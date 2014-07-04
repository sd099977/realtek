#include "uart_qc.h" 

//=================================================================================================
// Name: UartDataWrite
// Description: Write Data to UART 
// Input: 
//	- (UINT8) byWriteData: User Data for Write Operation 
// Output: None
//=================================================================================================
void UartDataWrite(UINT8 byWriteData)
{
	while((rtd_inl(UART0REG_U0Lsr) & UARTINFO_TRANSMITTER_READY_MASK) != UARTINFO_TRANSMITTER_READY_MASK);
 	rtd_outl(UART0REG_U0RbrTheDll, (UINT32) byWriteData); 
}
//=================================================================================================
// Name: UartDataRead
// Description: Read Data from UART 
// Input: None
// Output:
//	- (UINT8) Specific Value from UART Port 
//=================================================================================================
UINT8 UartDataRead(void)
{
	while((rtd_inl(UART0REG_U0Lsr) & UARTINFO_DATA_READY_MASK) != UARTINFO_DATA_READY_MASK);
	return (UINT8) (rtd_inl(UART0REG_U0RbrTheDll) & 0xFF);
}
//=================================================================================================
// Name: Uart1DataWrite
// Description: Write Data to UART1 
// Input: 
//	- (UINT8) byWriteData: User Data for Write Operation   
// Output: None
//=================================================================================================
void Uart1DataWrite(UINT8 byWriteData)
{
	while((rtd_inl(UART1REG_U1Lsr) & UARTINFO_TRANSMITTER_READY_MASK) != UARTINFO_TRANSMITTER_READY_MASK);
 	rtd_outl(UART1REG_U1RbrTheDll, (UINT32) byWriteData); 
}
//=================================================================================================
// Name: Uart1DataRead
// Description: Read Data from UART1 
// Input: None 
// Output:
//	- (UINT8) Specific Value from UART1 Port 
//=================================================================================================
UINT8 Uart1DataRead(void)
{
	while((rtd_inl(UART1REG_U1Lsr) & UARTINFO_DATA_READY_MASK) != UARTINFO_DATA_READY_MASK);
	return (UINT8) (rtd_inl(UART1REG_U1RbrTheDll) & 0xFF);	
}
