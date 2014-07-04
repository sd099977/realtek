#include <qc_verify_common.h>


//HDMI CEC register
#define HDMI_CEC_CR0_VADDR                      (0xb8061e00)
#define HDMI_CEC_RTCR0_VADDR                    (0xb8061e04)
#define HDMI_CEC_RXCR0_VADDR                    (0xb8061e08)
#define HDMI_CEC_TXCR0_VADDR                    (0xb8061e0c)
#define HDMI_CEC_TXDR0_VADDR                    (0xb8061e10)
#define HDMI_CEC_TXDR1_VADDR                    (0xb8061e14)
#define HDMI_CEC_TXDR2_VADDR                    (0xb8061e18)
#define HDMI_CEC_TXDR3_VADDR                    (0xb8061e1c)
#define HDMI_CEC_TXDR4_VADDR                    (0xb8061e20)
#define HDMI_CEC_RXDR1_VADDR                    (0xb8061e24)
#define HDMI_CEC_RXDR2_VADDR                    (0xb8061e28)
#define HDMI_CEC_RXDR3_VADDR                    (0xb8061e2c)
#define HDMI_CEC_RXDR4_VADDR                    (0xb8061e30)
#define HDMI_CEC_RXTCR0_VADDR                   (0xb8061e34)
#define HDMI_CEC_TXTCR0_VADDR                   (0xb8061e38)
#define HDMI_CEC_TXTCR1_VADDR                   (0xb8061e3c)
#define GDI_CEC_COMPARE_OPCODE_01_VADDR    (0xb8061e40)
#define GDI_CEC_SEND_OPCODE_01_VADDR       (0xb8061e44)
#define GDI_CEC_SEND_OPERAND_NUMBER_01_VADDR  (0xb8061e48)
#define GDI_CEC_OPERAND_01_VADDR           (0xb8061e4c)
#define GDI_CEC_OPERAND_02_VADDR           (0xb8061e50)
#define GDI_CEC_OPERAND_03_VADDR           (0xb8061e54)
#define GDI_CEC_COMPARE_OPCODE_02_VADDR    (0xb8061e58)
#define GDI_CEC_SEND_OPCODE_02_VADDR       (0xb8061e5c)
#define GDI_CEC_SEND_OPERAND_NUMBER_02_VADDR  (0xb8061e60)
#define GDI_CEC_OPERAND_04_VADDR           (0xb8061e64)
#define GDI_CEC_OPERAND_05_VADDR           (0xb8061e68)
#define GDI_CEC_OPERAND_06_VADDR           (0xb8061e6c)
#define GDI_CEC_COMPARE_OPCODE_03_VADDR    (0xb8061e70)
#define GDI_CEC_SEND_OPCODE_03_VADDR       (0xb8061e74)
#define GDI_CEC_SEND_OPERAND_NUMBER_03_VADDR  (0xb8061e78)
#define GDI_CEC_OPERAND_07_VADDR           (0xb8061e7c)
#define GDI_CEC_OPERAND_08_VADDR           (0xb8061e80)
#define GDI_CEC_OPERAND_09_VADDR           (0xb8061e84)
#define GDI_CEC_COMPARE_OPCODE_04_VADDR    (0xb8061e88)
#define GDI_CEC_SEND_OPCODE_04_VADDR       (0xb8061e8c)
#define GDI_CEC_SEND_OPERAND_NUMBER_04_VADDR  (0xb8061e90)
#define GDI_CEC_OPERAND_10_VADDR           (0xb8061e94)
#define GDI_CEC_OPERAND_11_VADDR           (0xb8061e98)
#define GDI_CEC_OPERAND_12_VADDR           (0xb8061e9c)
#define GDI_CEC_COMPARE_OPCODE_05_VADDR    (0xb8061ea0)
#define GDI_CEC_COMPARE_OPCODE_06_VADDR    (0xb8061ea4)
#define GDI_CEC_COMPARE_OPCODE_07_VADDR    (0xb8061ea8)
#define GDI_CEC_COMPARE_OPCODE_08_VADDR    (0xb8061eac)
#define GDI_CEC_COMPARE_OPCODE_09_VADDR    (0xb8061eb0)
#define GDI_CEC_COMPARE_OPCODE_10_VADDR    (0xb8061eb4)
#define GDI_CEC_COMPARE_OPCODE_11_VADDR    (0xb8061eb8)
#define GDI_CEC_COMPARE_OPCODE_12_VADDR    (0xb8061ebc)
#define GDI_CEC_COMPARE_OPCODE_13_VADDR    (0xb8061ec0)
#define GDI_CEC_COMPARE_OPCODE_14_VADDR    (0xb8061ec4)
#define GDI_CEC_COMPARE_OPCODE_15_VADDR    (0xb8061ec8)
#define GDI_CEC_OPCODE_ENABLE_VADDR        (0xb8061ecc)
#define GDI_POWER_SAVING_MODE_VADDR        (0xb8061ed0)
#define CEC_RXACKTCR0_VADDR                (0xb8061ed4)
#define CEC_RXACKTCR1_VADDR                (0xb8061ed8)


#if 0
#define _ZERO   						0x00
#define _BIT0   						0x01
#define _BIT1   						0x02
#define _BIT2   						0x04
#define _BIT3   						0x08
#define _BIT4   						0x10
#define _BIT5   						0x20
#define _BIT6   						0x40
#define _BIT7   						0x80
#define _BIT8   						0x0100
#define _BIT9   						0x0200
#define _BIT10  						0x0400
#define _BIT11  						0x0800
#define _BIT12  						0x1000
#define _BIT13  						0x2000
#define _BIT14  						0x4000
#define _BIT15  						0x8000
#define _BIT16   						0x00010000
#define _BIT17  						0x00020000
#define _BIT18   						0x00040000
#define _BIT19   						0x00080000
#define _BIT20   						0x00100000
#define _BIT21   						0x00200000
#define _BIT22   						0x00400000
#define _BIT23   						0x00800000
#define _BIT24   						0x01000000
#define _BIT25   						0x02000000
#define _BIT26  						0x04000000
#define _BIT27  						0x08000000
#define _BIT28  						0x10000000
#define _BIT29  						0x20000000
#define _BIT30  						0x40000000
#define _BIT31  						0x80000000
#endif


#define CEC_CTS_7_9 1
#define GDI_POWER_SAVING 0
#define HDMI_CEC_TEST 1

void  cec_wait_ms(unsigned long ms)
{
	while(ms-->0)
		udelay(1000);
}

int CCec_Test(void)
{
#if 1
	UINT32 CEC_DATA[2][4];
	UINT8 i,timeoutcnt=255;
	
	CEC_DATA[0][0]=0x00112233;
	CEC_DATA[0][1]=0x44556677;
	CEC_DATA[0][2]=0x8899aabb;
	CEC_DATA[0][3]=0xccddee00;
	rtd_maskl(HDMI_CEC_RTCR0_VADDR,~ (_BIT16 | _BIT17), _BIT16 | _BIT17); // FW mode, let loopback output waveform correct, and default pull high
	rtd_outl(GDI_POWER_SAVING_MODE_VADDR,0x00000013);  //CEC pull high from 2.7 to 3.16
	cec_wait_ms(500);
	printk("pull high....\n");
	rtd_outl(HDMI_CEC_CR0_VADDR,0xc714fc00);		//CEC loop back enable, RBUS=202MHz, addr is 0x7	
	//rtd_outl(HDMI_CEC_CR0_ADDR,0xc714221f);		//CEC loop back enable, RBUS=27MHz, addr is 0x7
	rtd_outl(HDMI_CEC_TXCR0_VADDR,0x0507c0);		//CEC TX addr is 0x5, dest addr is 0x7 
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT20,_BIT20);		//CEC TX addr enable

	rtd_outl(HDMI_CEC_TXDR1_VADDR,CEC_DATA[0][0]);		//CEC TX FIFO 
	rtd_outl(HDMI_CEC_TXDR2_VADDR,CEC_DATA[0][1]);		//CEC TX FIFO
	rtd_outl(HDMI_CEC_TXDR3_VADDR,CEC_DATA[0][2]);		//CEC TX FIFO
	rtd_outl(HDMI_CEC_TXDR4_VADDR,CEC_DATA[0][3]);		//CEC TX FIFO
	rtd_outl(HDMI_CEC_TXDR0_VADDR,0xf);					//CEC TX FIFO num

	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT14,_BIT14);		//CEC RX reset
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT14,_BIT14);		//CEC TX reset
	udelay(1000);
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT14,0x0);		//CEC RX reset
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT14,0x0);		//CEC TX reset
	udelay(1000);

	rtd_maskl(HDMI_CEC_TXDR0_VADDR,~_BIT6,_BIT6);		//CEC TX FIFO num double buffer load
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT15,_BIT15);		//CEC RX reset
	udelay(1000);
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT15,_BIT15);		//CEC TX enable
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT6,_BIT6);		//clr RX interrupt flag
	
	do 											//wait RX ok flag
	{
		udelay(5000);
		if((rtd_inl(HDMI_CEC_RXCR0_VADDR) & _BIT6))
			break;
 	} while (--timeoutcnt);
	if (timeoutcnt==0)
		printk("wait CEC RX timeout!!!\n");

	CEC_DATA[1][0]=rtd_inl(HDMI_CEC_RXDR1_VADDR);
	CEC_DATA[1][1]=rtd_inl(HDMI_CEC_RXDR2_VADDR);
	CEC_DATA[1][2]=rtd_inl(HDMI_CEC_RXDR3_VADDR);
	CEC_DATA[1][3]=rtd_inl(HDMI_CEC_RXDR4_VADDR);

	for (i=0;i<4;i++)
		{
		if (CEC_DATA[0][i]!=CEC_DATA[1][i])
			return FALSE;		
		}
	return TRUE;
#else
#if CEC_CTS_7_9	
	UINT32 CEC_DATA[2][4];
	UINT32 timeoutcnt=25500;
	UINT32 init_addr,broadcast_flag;
	UINT8  i=0,rx_len=0,j=0;

	
	
while(i<2){	
	printk("CEC Init ...\n");
	i++;
	CEC_DATA[0][0]=0x00112233;
	CEC_DATA[0][1]=0x44556677;
	CEC_DATA[0][2]=0x8899aabb;
	CEC_DATA[0][3]=0xccddee00;
	rtd_maskl(HDMI_CEC_RTCR0_VADDR,~ (_BIT16 | _BIT17), _BIT16 | _BIT17); // FW mode, let loopback output waveform correct, and default pull high
	rtd_outl(HDMI_CEC_CR0_VADDR,0x4014fc00);		//CEC enable, RBUS=202MHz, addr is 0x0 Pad_rise_time set 0x4 or ox1f occur error
	rtd_outl(GDI_POWER_SAVING_MODE_VADDR,0x00000013);  //CEC pull high from 2.7 to 3.16
	//rtd_outl(HDMI_CEC_CR0_ADDR,0x40142200);		//CEC enable, RBUS=27MHz, addr is 0x0
	rtd_outl(HDMI_CEC_TXCR0_VADDR,0x0507c0);		//CEC TX addr is 0x5, dest addr is 0x7 
	//rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT20,_BIT20);		//CEC TX addr enable
	
	rtd_outl(HDMI_CEC_TXDR1_VADDR,CEC_DATA[0][0]);		//CEC TX FIFO 
	rtd_outl(HDMI_CEC_TXDR2_VADDR,CEC_DATA[0][1]);		//CEC TX FIFO
	rtd_outl(HDMI_CEC_TXDR3_VADDR,CEC_DATA[0][2]);		//CEC TX FIFO
	rtd_outl(HDMI_CEC_TXDR4_VADDR,CEC_DATA[0][3]);		//CEC TX FIFO
	//rtd_outl(HDMI_CEC_TxDR0_ADDR,0xf);					//CEC TX FIFO num
	
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT14,_BIT14);		//CEC RX reset
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT14,_BIT14);		//CEC TX reset
	udelay(1000);
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT14,0x0);		//CEC RX normal
	rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT14,0x0);		//CEC TX normal
	udelay(1000);
	//rtd_maskl(HDMI_CEC_TxDR0_ADDR,~_BIT6,_BIT6);		//CEC TX FIFO num double buffer load
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT15,_BIT15);		//CEC RX enable
	udelay(1000);
	//rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT15,_BIT15);		//CEC TX enable
	rtd_maskl(HDMI_CEC_RXCR0_VADDR,~_BIT6,_BIT6);		//clr RX interrupt flag



#if GDI_POWER_SAVING
	rtd_outl(GDI_CEC_COMPARE_OPCODE_01_VADDR,0xff);
	rtd_outl(GDI_CEC_SEND_OPCODE_01_VADDR,0x00);
	rtd_outl(GDI_CEC_COMPARE_OPCODE_02_VADDR,0x83);
	rtd_outl(GDI_CEC_SEND_OPCODE_02_VADDR,0x84);	
	rtd_outl(GDI_CEC_OPERAND_04_VADDR,0x10);
	rtd_outl(GDI_CEC_OPERAND_05_VADDR,0x00);
	rtd_outl(GDI_CEC_SEND_OPERAND_NUMBER_01_VADDR,0x00);		//opcode number = 0
	rtd_outl(GDI_CEC_SEND_OPERAND_NUMBER_02_VADDR,0x02);		//opcode number = 2
	rtd_outl(GDI_CEC_OPCODE_ENABLE_VADDR,0x03);				//compare opcode1,opcode2 enable
	rtd_maskl(GDI_POWER_SAVING_MODE_VADDR,~_BIT8,_BIT8);		//Irq enable
#endif 

	do 											//wait RX ok flag
	{
		udelay(5000);
		if((rtd_inl(HDMI_CEC_RXCR0_VADDR) & _BIT6))
			break;
 	} while (--timeoutcnt);
	if (timeoutcnt==0)
		printk("wait CEC RX timeout!!!\n");
	
	init_addr=(rtd_inl(HDMI_CEC_RXCR0_VADDR)&0x0f00);
	broadcast_flag = (rtd_inl(HDMI_CEC_RXCR0_VADDR)>>31);
	rx_len= rtd_inl(HDMI_CEC_RXCR0_VADDR)&0x1f;
	CEC_DATA[1][0]=rtd_inl(HDMI_CEC_RXDR1_VADDR);
	CEC_DATA[1][1]=rtd_inl(HDMI_CEC_RXDR2_VADDR);
	CEC_DATA[1][2]=rtd_inl(HDMI_CEC_RXDR3_VADDR);
	CEC_DATA[1][3]=rtd_inl(HDMI_CEC_RXDR4_VADDR);

	printk("init_addr = %x\n",init_addr);
	printk("broadcast_flag = %x\n",broadcast_flag);
	printk("rx_len = %d\n",rx_len);
	if (rx_len>0)
		printk("CEC_DATA[1][0] = %x\n",CEC_DATA[1][0]);

	if(rx_len>4)
		printk("CEC_DATA[1][1] = %x\n",CEC_DATA[1][1]);
	
	if(rx_len>8)
		printk("CEC_DATA[1][2] = %x\n",CEC_DATA[1][2]);	

	if(rx_len>12)
		printk("CEC_DATA[1][3] = %x\n",CEC_DATA[1][3]);

#if GDI_POWER_SAVING
	if((rtd_inl(GDI_POWER_SAVING_MODE_VADDR) & _BIT31))
		printk("GDI_POWER_SAVING_MODE IRQ PENDING\n");

	rtd_maskl(GDI_POWER_SAVING_MODE_VADDR,~_BIT31,_BIT31);		//clr Irq
	j=20;
	do 										
	{
		udelay(5000);

 	} while (--j);
#else

	if (((CEC_DATA[1][0]>>24) == 0xff)&&(broadcast_flag == 0))//cmd=Abort
	{
		CEC_DATA[0][0]=(0x00<<24);
		rtd_outl(HDMI_CEC_TXDR1_VADDR,CEC_DATA[0][0]);		//CEC TX FIFO 
		rtd_outl(HDMI_CEC_TXDR0_VADDR,0x1);					//CEC TX FIFO num=1
		rtd_maskl(HDMI_CEC_TXDR0_VADDR,~_BIT6,_BIT6);		//CEC TX FIFO num double buffer load
		rtd_maskl(HDMI_CEC_TXCR0_VADDR,~0x00000f00,init_addr);		//dest addr	
		rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT15,_BIT15);		//CEC TX enable
		printk("CEC TX send <Feature Abort >\n");
		do 											//wait TX ok flag
		{
			udelay(5000);
			if((rtd_inl(HDMI_CEC_TXCR0_VADDR) & _BIT6))
				break;
	 	} while (--timeoutcnt);

		if (timeoutcnt==0)
			printk("wait CEC TX timeout!!!\n");
	}
	else if (((CEC_DATA[1][0]>>24)== 0x83)&&(broadcast_flag == 0))//cmd=Give Physical Address
	{
		init_addr = (0xf<<8);//broadcast
		CEC_DATA[0][0]=(0x84<<24)|(0x10<<16)|(0x00<<8);//physical address = 0x1000
		rtd_outl(HDMI_CEC_TXDR1_VADDR,CEC_DATA[0][0]);		//CEC TX FIFO 
		rtd_outl(HDMI_CEC_TXDR0_VADDR,0x3);					//CEC TX FIFO num=3 
		rtd_maskl(HDMI_CEC_TXDR0_VADDR,~_BIT6,_BIT6);		//CEC TX FIFO num double buffer load
		rtd_maskl(HDMI_CEC_TXCR0_VADDR,~0x00000f00,init_addr);		//dest addr	
		rtd_maskl(HDMI_CEC_TXCR0_VADDR,~_BIT15,_BIT15);		//CEC TX enable
		printk("CEC TX send <Report Physical Address> = %x\n",CEC_DATA[0][0]);
		do 											//wait TX ok flag
		{
			udelay(5000);
			if((rtd_inl(HDMI_CEC_TXCR0_VADDR) & _BIT6))
				break;
	 	} while (--timeoutcnt);

		if (timeoutcnt==0)
			printk("wait CEC TX timeout!!!\n");
	}
#endif
}
#endif

	return TRUE;
#endif
}

int CEC_256_Pad_Check(void)
{

    //test_mode_pad_en set 1 enable
    rtd_outl(HDMI_CEC_CR0_VADDR,0x97142240);     //CEC test output high
    //Pin 179 HDMI_HPD1 / ST_GPIO19
 
    rtd_maskl(0xb806022c,~(_BIT7|_BIT6|_BIT5|_BIT4),(_BIT7|_BIT6|_BIT5|_BIT4));     //PAD_ST_GPIO_19  pin share
    rtd_maskl(0xb8061100,~_BIT19,0);        //PAD_ST_GPIO_0 set to GPI
    udelay(5000);
    if (!(rtd_inl(0xb8061110)&_BIT19))
    {
        printk("CEC pad FAIL at high\n");
        return FALSE;
    }

    rtd_outl(HDMI_CEC_CR0_VADDR,0x97142200);     //CEC test output low
    udelay(5000);
    if (rtd_inl(0xb8061110)&_BIT19)
    {
        printk("CEC pad FAIL at low\n");
        return FALSE;
    }

    return TRUE;
  
}

int QC_Verifier_CEC(void)
{
#if HDMI_CEC_TEST
	bool verifyResult = 0;

	//check bandgap init, if bootcode not setting
	//bus clock 202M
//	rtd_outl(0xb8000420,0x00351B52);	//max 405, set 27*15 = 405MHz
	rtd_maskl(0xb8060044,~_BIT7,_BIT7); //cec clock enable 
	rtd_maskl(0xb8060034,~_BIT7,_BIT7); // cec reset release

	if (!CCec_Test())
	{
		printk("CEC loop back test FAIL#\n");
		verifyResult = FAILED;
	}
	else
		printk("CEC loop back test PASS@\n");

	
#ifdef CONFIG_256_PKG
	 if (!CEC_256_Pad_Check())
	 {
        	printk("CEC Pad FAIL#\n"),
       	 verifyResult = FAILED;
	 }
        else
       	 printk("CEC Pad PASS@\n");
#endif

	return verifyResult;


	
#endif
} 

