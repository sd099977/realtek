#include <qc_verify_common.h>

#define Only_One_UART

static int debug_mode=1;

//plus loopback function
static bool Sel_clk98 = 0; 
static bool Open_LoopBack = 1; 

int Verify_Uart_Single(bool bSel_clk98, bool bEnLoopBack)
{
	/* UART ADDR */
	//uart A addr = UART1
	//UART1:0xB801BC00~0xB801B11C		
	UINT32 addr_A_DLL_FIFO_vaL = 0xb801bC00; 	//MIS_U1RBR_THR_DLL(Value): 
	UINT32 addr_A_FIFO_ctrl = 0xb801bC08;		//MIS_U1IIR_FCR(FIFO CTRL): 
	UINT32 addr_A_Line_ctrl = 0xb801bC0C;			//MIS_U1LCR(Line CTRL): DLAB ctrl
	UINT32 addr_A_Modem_ctrl = 0xb801bC10;		//MIS_U1MCR: loopback & rts & cts
	UINT32 orgBaudrate = 0xEA;   // eg.115200; RX/TX FIFO data(DLAB=0) 432M/(16 *115200)

	/* UART PS  //eqc path not ready
	//uart A 
	//inputmux/ps:               		
	rtd_maskl(0xB80008C4,GetMaskAnd(10,8),0x5<<8); 		//src5: 0xB80008C4[10:8]=0x5
	rtd_maskl(0xB8060200,GetMaskAnd(15,12),0x8<<12);		//  rx: 0xB8060200[15:12]=0x8/vddc_scl_ps/U5/JS20-1,SW22-1ON
	rtd_maskl(0xB8060200,GetMaskAnd(07,04),0x8<<4);		//  tx: 0xB8060200[7:4]  =0x8/vddc_sda_ps/U4/JS20-2,SW22-2ON         
	*/ 
	
	printk("----------will : verify [uart A = UART1]-------- \n");
	//-----------------------------------------------------------------

	/* init uart1 */
	
	//select clk
	if(bSel_clk98)
	{
		//main clk --> uart1, set in crt file
		//rtd_part_inl(0xb8000204,0,0,0);
	//	rtd_maskl(0xb8000204,GetMaskAnd(0,0),0x0<<0);	//0-98m, 1-27m
		//rtd_part_inl(0xb8000204,0,0,0);

	//	orgBaudrate = 0x36;
	}
		
	//uart settings
	rtd_outl(addr_A_Line_ctrl,0x83);			//MIS_U1LCR(Line CTRL): DLAB:1; Word length:8	
	rtd_outl(addr_A_DLL_FIFO_vaL,orgBaudrate);	//MIS_U1RBR_THR_DLL(Value): Timing Setting/DLL(DLAB=1) eg.115200; RX/TX FIFO data(DLAB=0)  
	rtd_outl(addr_A_Line_ctrl,0x03);  		//MIS_U1LCR(Line CTRL): DLAB:0; DLL --> RX/TX FIFO
	rtd_outl(addr_A_FIFO_ctrl,0xc6);		//MIS_U1IIR_FCR(FIFO CTRL): FIFO Reset:FIFO En; receiver line status
	rtd_outl(addr_A_FIFO_ctrl,0xc1);		//MIS_U1IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_outl(addr_A_Line_ctrl,0x03);			//MIS_U1LCR(Line CTRL): DLAB:0, DLL --> RX/TX FIFO

	//check fifo info settings 
	rtd_inl(addr_A_Line_ctrl);					//MIS_U1LCR(Line CTRL): DLAB:0 DLL --> RX/TX FIFO; 0x03?
	rtd_inl(addr_A_FIFO_ctrl);					//MIS_U1IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_inl(addr_A_DLL_FIFO_vaL);   			//MIS_U1RBR_THR_DLL(Value): read: read fifo data value
	
	//------------------- start check -------------------------
	UINT32 j;	//Timing setting val
	UINT32 sendVal;			//rx/tx data
	UINT32 getVal;

	int  tmp_rst = 0;
	int  old_rst = 0;
	
	for(j=orgBaudrate; j<=orgBaudrate; j++)	
	{ 
		//uart A tx
		rtd_outl(addr_A_Line_ctrl,0x83);			//Line CTRL: DLAB:1; Word length:8	
		rtd_outl(addr_A_DLL_FIFO_vaL,j);		//U1RBR_THR_DLL: (DLAB=1) --> Timing Setting(DLL):default=115200
		rtd_outl(addr_A_Line_ctrl,0x03);  		//Line CTRL: DLAB:0; DLL --> RX/TX FIFO

		//******* Add loopback function *******
		if(bEnLoopBack)
		{
			//Open loopback mode: rx-tx connect in ic
			rtd_maskl(addr_A_Modem_ctrl, GetMaskAnd(4,4),0x1<<4); 		//rtd_part_outl(0xb801b110,4,4,0x1);

			//TEST uart1 after loopback
			rtd_outl(addr_A_Line_ctrl,0x03);		//Line CTRL: DLAB:0; DLL --> RX/TX FIFO
			for(sendVal=0x30; sendVal<0x33; sendVal++)
			{
				rtd_outl(addr_A_DLL_FIFO_vaL,sendVal);			
				udelay(100);
				//printk("UART A TX: sendVal=0x%x \n", sendVal);
			}
			for(sendVal=0x30; sendVal<0x33; sendVal++)
			{
				getVal = rtd_inl(addr_A_DLL_FIFO_vaL);			

				old_rst = tmp_rst;
				if(sendVal>0x33)		//over send length
				{
					if(getVal == sendVal)
						tmp_rst++;
				}
				else
				{
					if(getVal != sendVal)
						tmp_rst++;
				}

				if(tmp_rst>old_rst)		//if tmp_rst increase in this round, mean error
					printk("[Error!]UART A TX: sendVal=0x%x <--> getVal=0x%x \n", sendVal, getVal);
				else
				{
					if(debug_mode)
						printk("UART A TX: sendVal=0x%x <--> getVal=0x%x \n", sendVal, getVal);
				}
			}


			//Close loopback mode: rx-tx connect in ic
			rtd_maskl(addr_A_Modem_ctrl, GetMaskAnd(4,4),0x0<<4); 		//rtd_part_outl(0xb801b110,4,4,0x0);
			//FIFO Disable
			rtd_maskl(addr_A_FIFO_ctrl, GetMaskAnd(0,0), 0x0);   			//rtd_part_outl(0xb801b108, 0,0, 0x0);     

		}
						
	}
	if(tmp_rst>0)
			return 1;


	return 0;			
}

int Verify_Uart_External(void)
{
	/* UART ADDR */
	//uart A addr = UART1
	//UART1: 0xB801B100 ~ 0xB801B11C		
	UINT32 addr_A_DLL_FIFO_vaL = 0xb801bC00; 	//MIS_U1RBR_THR_DLL(Value): 
	UINT32 addr_A_FIFO_ctrl = 0xb801bC08;		//MIS_U1IIR_FCR(FIFO CTRL): 
	UINT32 addr_A_Line_ctrl = 0xb801bC0C;			//MIS_U1LCR(Line CTRL): DLAB ctrl
	
	
	//uart B addr = IS0 Uart0
	//uart2:0xB801BE00~0xB801BEFC 		                                                                    
	UINT32 addr_B_DLL_FIFO_vaL = 0xB801BE00; 	//MIS_U2RBR_THR_DLL(Value): 
	UINT32 addr_B_FIFO_ctrl = 0xB801BE08;		//MIS_U2IIR_FCR(FIFO CTRL): 
	UINT32 addr_B_Line_ctrl = 0xB801BE0C;			//MIS_U2LCR(Line CTRL): DLAB ctrl etc
	
	//crt for uart1
	/*
	rtd_maskl(0xB8000010,GetMaskAnd(28,28),1<<31);
	rtd_maskl(0xB8000010,GetMaskAnd(28,28),0<<31);
	rtd_maskl(0xB8000004,GetMaskAnd(28,28),0<<31);
	rtd_maskl(0xB8000004,GetMaskAnd(28,28),1<<31);
	rtd_maskl(0xB8000010,GetMaskAnd(28,28),1<<31);
*/	
	
//crt for uart2
	rtd_maskl(0xB8000010,GetMaskAnd(31,31),1<<31);
	rtd_maskl(0xB8000010,GetMaskAnd(31,31),0<<31);
	rtd_maskl(0xB8000004,GetMaskAnd(31,31),0<<31);
	rtd_maskl(0xB8000004,GetMaskAnd(31,31),1<<31);
	rtd_maskl(0xB8000010,GetMaskAnd(31,31),1<<31);

	// UART PS //eqc path not ready
	//uart A 
	//inputmux/ps:               		
	rtd_maskl(0xB80008FC,GetMaskAnd(22,20),0x0<<20); 		//src0: 
	rtd_maskl(0xB8000840,GetMaskAnd(13,9),0x2<<9);		//  rx:
	rtd_maskl(0xB8000844,GetMaskAnd(31,27),0x2<<27);		//  tx:       
	                                                                                                    
	//uart B 
	//inputmux/ps:               		                                                                    
	rtd_maskl(0xB80008FC,GetMaskAnd(28,26),0x2<<26);		//src2:                              
	rtd_maskl(0xB8060238,GetMaskAnd(31,27),0x9<<27);		//  rx: 
	rtd_maskl(0xB8060234,GetMaskAnd(13,9),0x9<<9);		//  tx: 


	printk("----------will: verify [uart A = UART1, TX  to UAERT B =UART2 's RX ]-------- \n");
	//-----------------------------------------------------------------

	/* init uart1 */	
	//uart settings
	rtd_outl(addr_A_Line_ctrl,0x83);			//MIS_U1LCR(Line CTRL): DLAB:1; Word length:8	
	rtd_outl(addr_A_DLL_FIFO_vaL,0xEA);	//MIS_U1RBR_THR_DLL(Value): Timing Setting/DLL(DLAB=1) eg.115200; RX/TX FIFO data(DLAB=0)  
	rtd_outl(addr_A_Line_ctrl,0x03);  		//MIS_U1LCR(Line CTRL): DLAB:0; DLL --> RX/TX FIFO
	rtd_outl(addr_A_FIFO_ctrl,0xc6);		//MIS_U1IIR_FCR(FIFO CTRL): FIFO Reset:FIFO En; receiver line status
	rtd_outl(addr_A_FIFO_ctrl,0xc1);		//MIS_U1IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_outl(addr_A_Line_ctrl,0x03);			//MIS_U1LCR(Line CTRL): DLAB:0, DLL --> RX/TX FIFO

	//check fifo info settings 
	rtd_inl(addr_A_Line_ctrl);					//MIS_U1LCR(Line CTRL): DLAB:0 DLL --> RX/TX FIFO; 0x03?
	rtd_inl(addr_A_FIFO_ctrl);					//MIS_U1IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_inl(addr_A_DLL_FIFO_vaL);   			//MIS_U1RBR_THR_DLL(Value): read: read fifo data value


	/* init uart2 */	
	//uart settings
	rtd_outl(addr_B_Line_ctrl,0x83);			//MIS_U2LCR(Line CTRL): DLAB:1; Word length:8	
	rtd_outl(addr_B_DLL_FIFO_vaL,0x0f);	//MIS_U2RBR_THR_DLL(Value): Timing Setting/DLL(DLAB=1) eg.115200; RX/TX FIFO data(DLAB=0)  
	rtd_outl(addr_B_Line_ctrl,0x03);  		//MIS_U2LCR(Line CTRL): DLAB:0; DLL --> RX/TX FIFO
	rtd_outl(addr_B_FIFO_ctrl,0xc6);		//MIS_U2IIR_FCR(FIFO CTRL): FIFO Reset:FIFO En; receiver line status
	rtd_outl(addr_B_FIFO_ctrl,0xc1);		//MIS_U2IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_outl(addr_B_Line_ctrl,0x03);			//MIS_U2LCR(Line CTRL): DLAB:0, DLL --> RX/TX FIFO


	//check fifo info settings 
	rtd_inl(addr_B_Line_ctrl);					//MIS_U2LCR(Line CTRL): DLAB:0 DLL --> RX/TX FIFO; 0x03?
	rtd_inl(addr_B_FIFO_ctrl);					//MIS_U2IIR_FCR(FIFO CTRL): FIFO Enable:FIFO En; no interrupt pending;
	rtd_inl(addr_B_DLL_FIFO_vaL);   			//MIS_U2RBR_THR_DLL(Value): read: read fifo data value



	//------------------- start check -------------------------
	UINT32 j;	//Timing setting val
	UINT32 sendVal;			//rx/tx data
	UINT32 getVal;

	int  tmp_rst = 0;
	int  old_rst = 0;
	
	printk("hehhee\n");
	
	for(j=0x0f; j<=0x0f; j++)	
	{ 
		//uart A tx
//		rtd_outl(addr_A_Line_ctrl,0x83);			//Line CTRL: DLAB:1; Word length:8	
//		rtd_outl(addr_A_DLL_FIFO_vaL,0xEA);		//U1RBR_THR_DLL: (DLAB=1) --> Timing Setting(DLL):default=115200
//		rtd_outl(addr_A_Line_ctrl,0x03);  		//Line CTRL: DLAB:0; DLL --> RX/TX FIFO

		//uart B rx
//		rtd_outl(addr_B_Line_ctrl,0x83);			//MIS_U2LCR(Line CTRL): DLAB:1; Word length:8	
//		rtd_outl(addr_B_DLL_FIFO_vaL,0x0f);	//MIS_U2RBR_THR_DLL(Value): Timing Setting/DLL(DLAB=1) eg.115200; RX/TX FIFO data(DLAB=0)  
//		rtd_outl(addr_B_Line_ctrl,0x03);  		//MIS_U2LCR(Line CTRL): DLAB:0; DLL --> RX/TX FIFO

		printk("UART A  TX --> UART B RX  in baudrate: %x\n", j);
			
		//*******TEST uartA tx -> uartB rx*******
		for(sendVal=0x30; sendVal<=0x51; sendVal++)
		{
			rtd_outl(addr_A_DLL_FIFO_vaL,sendVal);			//uartA tx
			udelay(100);
		}
		for(sendVal=0x30; sendVal<=0x51; sendVal++)
		{
			getVal = rtd_inl(addr_B_DLL_FIFO_vaL);   		//uartB rx

			old_rst = tmp_rst;
			if(sendVal>0x4f)	//over fifo length
			{
				if(getVal == sendVal)
					tmp_rst++;
			}
			else
			{
				if(getVal != sendVal)
					tmp_rst++;
			}

			if(tmp_rst>old_rst)
				printk("[Error!]UART A --> UART B: sendVal=0x%x,  getVal=0x%x \n", sendVal, getVal);
			else
			{
				if(debug_mode)
					printk("UART A --> UART B: sendVal=0x%x,  getVal=0x%x \n", sendVal, getVal);
			}
				
		}

	//*******TEST uartB tx -> uartA rx*******
		for(sendVal=0x30; sendVal<=0x51; sendVal++)
		{
			rtd_outl(addr_B_DLL_FIFO_vaL,sendVal);			//uartB tx
			udelay(100);
		}
		for(sendVal=0x30; sendVal<=0x51; sendVal++)
		{
			getVal = rtd_inl(addr_A_DLL_FIFO_vaL);   		//uartA rx

			old_rst = tmp_rst;
			if(sendVal>0x4f)	//over fifo length
			{
				if(getVal == sendVal)
					tmp_rst++;
			}
			else
			{
				if(getVal != sendVal)
					tmp_rst++;
			}
			
			if(tmp_rst>old_rst)
				printk("[Error!]UART B --> UART A: sendVal=0x%x,  getVal=0x%x \n", sendVal, getVal);
			else
			{
				if(debug_mode)
					printk("UART B --> UART A: sendVal=0x%x,  getVal=0x%x \n", sendVal, getVal);
			}
		}

		if(tmp_rst>0)
			return 1;

	}

	return 0;		
	
}


int Verify_Uart(void)
{
	
#ifdef Only_One_UART
	bool retVal = 0;
	
	
	retVal = Verify_Uart_Single(Sel_clk98, Open_LoopBack); 
  
  retVal = retVal |Verify_Uart_External();	//invalied
  return retVal;
#endif
}
