
#include <qc_verify.h>


//#define DEBUGMODE  


int Verifier_LSADC(void)
{
    //***********************************************************
	//Lsadc0:
	//pkg176_pin124_ JS39_2:sw51:4 on(notice:use pin124_Lsadc0)
	//BGA_B7_JP11_2 :sw133_3

	//Lsadc1:
	//pkg176=>176_PIN125: JS41_1 SW57_2(notice:use pin125_lsadc1)
	//BGA=>Pin_C6:JP17_2  SW121_2

	//Lsadc2:
	//pkg176=>176_PIN126: JS41_2 SW57_3
	//BGA=>Pin_A7:JP11_3 SW133_2

	//Lsadc4:
	//BGA=>Pin_A5:JP17_3 SW121_1

	//Lsadc6:
	//BGA=>Pin_B6:JP14_2 SW118_4

	//Lsadc7:
	//pkg176=>176_Pin127 JS42_2 SW58_2
	//BGA=>Pin_C7:JP14_3 SW118_2

	//JS84:12,34,56,11,12 connected
	//***********************************************************
	//CRT INIT
	 ew(0xb8060044,0x00000801); 	//clken:1
	 ew(0xb8060044,0x00000000); 	//clken:0
	 ew(0xb8060034,0x00000000); 	//RSTN:0
	 ew(0xb8060034,0x00000801); 	//RSTN:1 
	 ew(0xb8060044,0x00000801);  	//clken:1


	UINT32 Data;
	UINT32 ADDR;

	ew(0xb8061500, 0x00000000);
	ew(0xb8061504, 0x00000000);
	ew(0xb8061508, 0x00000000);
	ew(0xb806150c, 0x00000000);
	ew(0xb8061510, 0x00000000);
	ew(0xb8061514, 0x00000000);
	ew(0xb8061518, 0x00000000);
	ew(0xb806151c, 0x00000000);
	ew(0xb8061520, 0x16000000);
	ew(0xb8061524, 0x00000000);
	ew(0xb8061528, 0x00011000);
	ew(0xb806152C, 0x00000000);
	
	//lsadcOpen(&keyConfig);

#if CONFIG_BGA
    ROSPrintf("LSADC BGA:\n");
    ew(0xb8061500, 0x80050000);
    ew(0xb8061504, 0x80051100);
	ew(0xb8061508, 0x80052100);
	ew(0xb806150c, 0x80053100);
	ew(0xb8061510, 0x80054100);
	ew(0xb8061514, 0x80055100);
	ew(0xb8061518, 0x80056100);
	ew(0xb806151c, 0x80057100);
#else
    ROSPrintf("LSADC QFP:\n");
    ew(0xb8061500, 0x80050000);
    ew(0xb8061504, 0x80051100);
	ew(0xb8061508, 0x80052100);
	ew(0xb806150c, 0x80053000);
	ew(0xb8061510, 0x80054000);
	ew(0xb8061514, 0x80055000);
	ew(0xb8061518, 0x80056000);
	ew(0xb806151c, 0x80057100);
#endif

	 ew(0xb8061528, 0x00010101);       //Analog Enable
	 ew(0xb8061520, 0x16100000);       //Digital setting
	 ew(0xb8061520, 0x16100001);       //Digital Enable

	
	udelay(20000);

	//pinshare
	ew(0xb806020c,0x6318c630);// LSADCREF,7,6,4,2,1
	ew(0xb8060210, 0x60000000);// LSADC0	
	

    bool bFail=0;

	udelay(5000);  //wait for value steady
	

#ifdef DEBUGMODE

    printk("Address:0xb8060040=>0x%x\n",dw(0xb8060040));
	printk("Address:0xb8060044=>0x%x\n",dw(0xb8060044));
	printk("Address:0xb8060030=>0x%x\n",dw(0xb8060030));
    printk("Address:0xb8060034=>0x%x\n",dw(0xb8060034));
	
    printk("Address:0xb806020c=>0x%x\n",dw(0xb806020c));
	printk("Address:0xb8060210=>0x%x\n",dw(0xb8060210));

    for(ADDR = 0xb8061500;ADDR<=0xb806152c;ADDR+=4)
    {
	    Data = dw(ADDR);
		printk("Address:0x%x=>0x%x\n",ADDR,Data);
	}	

#endif


#if CONFIG_BGA

	Data = dw(0xb8061500)&0x3f;     //   mean= 0x1F   ,  voltage mode 
	if(Data<0x1A || Data>0x25)  	
		{
		ROSPrintf("PAD0=0x%x\n",Data);
		bFail = 1;
		}
		
	udelay(20000);	

	Data = dw(0xb8061504)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K
		{
		ROSPrintf("PAD1=0x%x\n",Data);
		bFail = 1;
		}

	udelay(20000);	

	Data = dw(0xb8061508)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K
		{
		ROSPrintf("PAD2=0x%x\n",Data);
		bFail = 1;
		}

	udelay(20000);
	
	Data = dw(0xb806151c)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K
		{
		ROSPrintf("PAD4=0x%x\n",Data);
		bFail = 1;
		}
	
	udelay(20000);
	
	Data = dw(0xb8061518)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K 
		{
		ROSPrintf("PAD6=0x%x\n",Data);
		bFail = 1;
		}
	
	udelay(5000);  //wait for value steady
	
	Data = dw(0xb806151c)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K
		{
		ROSPrintf("PAD7=0x%x\n",Data);
		bFail = 1;
		}

#else

	Data = dw(0xb8061500)&0x3f;     //   mean = 0x1f   ,   voltage mode
	if(Data<0x1A || Data>0x25) 
		{
		ROSPrintf("PAD0=0x%x\n",Data);
		bFail = 1;
		}
		
	udelay(20000);


	Data = dw(0xb8061504)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K 
		{
		ROSPrintf("PAD1=0x%x\n",Data);
		bFail = 1;
		}

	udelay(20000);	

	Data = dw(0xb8061508)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K   
		{
		ROSPrintf("PAD2=0x%x\n",Data);
		bFail = 1;
		}

	udelay(5000);  //wait for value steady


    Data = dw(0xb806151c)&0x3f;     //   mean = 0xA   ,   current mode
	if(Data<0x5 || Data>0xf)       //R = 10K  
		{
		ROSPrintf("PAD7=0x%x\n",Data);
		bFail = 1;
		}
	
#endif

	ew(0xb8061528,0x0);

	return bFail;


}
