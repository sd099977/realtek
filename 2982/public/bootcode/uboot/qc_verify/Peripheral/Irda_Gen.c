#include <qc_verify_common.h>


#define	ew(reg_addr,para)			rtd_outl(reg_addr,para)
#define	dw(reg_addr)				rtd_inl(reg_addr)
#define ROSPrintf printk


//#define DEBUG_ir 0

//------------------------------------------------------------------------------------------------------------------------------
//For Irda Gen.
typedef struct _PINSHARE_INFO{
  UINT32 addr;
  UINT8  msb;
  UINT8  lsb;
  UINT32 val;
}PinShare_Info;

static PinShare_Info pinshare_info;

//GPIO Mapping

UINT32 GP0DIR = 0xb8061100;//Misc:0xb801b100;
UINT32 GP0DATO = 0xb8061108;//Misc:0xb801b11c;

UINT32 nAddr_GPO_IO;
UINT8  N_bit_GPO;
UINT32 nAddr_GPO_HL;

//Init GPIO Addr used and Pinshare Info.
void SetGPIOOut(UINT8 nGPIO_Num,UINT32 Pinshare_addr,UINT8 Pinshare_msb,UINT8 Pinshare_lsb,UINT32 Pinshare_val)
{
    nAddr_GPO_IO = GP0DIR + (nGPIO_Num/32)*4;
	nAddr_GPO_HL = GP0DATO + (nGPIO_Num/32)*4;
    N_bit_GPO =  nGPIO_Num - (nGPIO_Num/32)*32;
	pinshare_info.addr = Pinshare_addr;
	pinshare_info.msb = Pinshare_msb;
	pinshare_info.lsb = Pinshare_lsb;
	pinshare_info.val = Pinshare_val;	

//  1.pinshare to GPIO   2.Set to GPO  
    rtd_maskl(pinshare_info.addr,GetMaskAnd(pinshare_info.msb ,pinshare_info.lsb ),pinshare_info.val<<pinshare_info.lsb );   //Pinshare to GPIO
    rtd_maskl(nAddr_GPO_IO,GetMaskAnd(N_bit_GPO,N_bit_GPO),1<<N_bit_GPO);   //GPIO Set to GPO

	rtd_maskl(nAddr_GPO_HL,GetMaskAnd(N_bit_GPO,N_bit_GPO),1<<N_bit_GPO);   //Init=> GPO output HIGH!
}

void SetGPOHL(bool bHL)
{   
    rtd_maskl(nAddr_GPO_HL,GetMaskAnd(N_bit_GPO,N_bit_GPO),bHL<<N_bit_GPO);   //GPO set to H/L
}

void Irda_HL(bool b1,char* protocal)
{
	if(strcmp(protocal,"NEC")==0)
	{
        if(b1)
		{
			SetGPOHL(0);
				udelay(560);
			SetGPOHL(1);
				udelay(1690);			
        }
		else
		{
			SetGPOHL(0);
				udelay(560);
			SetGPOHL(1);
				udelay(560);	
		}  
	}
	
	else if(strcmp(protocal,"RC5")==0)
	{
        if(b1)
		{
			SetGPOHL(0);
				udelay(889);
			SetGPOHL(1);
				udelay(889);			
        }
		else
		{
			SetGPOHL(1);
				udelay(889);
			SetGPOHL(0);
				udelay(889);	
		}  
	
	}

	else if(strcmp(protocal,"SHARP")==0)
	{
        if(b1)
		{
			SetGPOHL(0);
				udelay(320);
			SetGPOHL(1);
				udelay(1680);			
        }
		else
		{
			SetGPOHL(0);
				udelay(320);
			SetGPOHL(1);
				udelay(680);	
		} 	
	
	}
	else if(strcmp(protocal,"SONY")==0)
	{
        if(b1)
		{
			SetGPOHL(0);
				udelay(1200);
			SetGPOHL(1);
				udelay(600);			
        }
		else
		{
			SetGPOHL(0);
				udelay(600);
			SetGPOHL(1);
				udelay(600);	
		} 		
	}
}


//Irda Protocal:"NEC","RC5","SHARP","Sony SIRC"
//Write Address/Command you want to Gen.

void Irad_NEC(UINT16 nAddr,UINT16 nCommand,UINT8 nRepeatTimes,bool bExtend)
{
    printk("\x1b[33m\tGen Irda Protocol NEC\x1b[0m\n");


	//Head of NEC:
	SetGPOHL(0);
		udelay(9000);
	SetGPOHL(1);
		udelay(4500);

	//Address
	if(!bExtend)
	{
		//Address, ~Address
		nAddr&=0xFF;		
		int i;
		for(i=0;i<8;i++)
			{
				Irda_HL((nAddr>>i)&0x1,"NEC");//Lsb-->Msb
			}


		for(i=0;i<8;i++)
			{
				Irda_HL(!((nAddr>>i)&0x1),"NEC");//Lsb-->Msb

			}	

	}           
    else 
	{
		int i;
		for(i=0;i<16;i++)
			{
				Irda_HL((nAddr>>i)&0x1,"NEC");//Lsb-->Msb
			}	
	}

	
	//Command,~Command
	nCommand&=0xFF;	
	int i;	
	for(i=0;i<8;i++)
		{
			Irda_HL((nCommand>>i)&0x1,"NEC");//Lsb-->Msb			
		}

	for(i=0;i<8;i++)
		{
			Irda_HL(!((nCommand>>i)&0x1),"NEC");//Lsb-->Msb
		}

	//after transmit command finish
    SetGPOHL(0);
		udelay(560);
	SetGPOHL(1);
	
	if(nRepeatTimes)
	{ 	    
	    //transmit command cost time:8*(1.12+2.25)=26.96ms
	    //110ms-26.96ms = 83.04ms.		
		mdelay(80);
		udelay(3040);
		nRepeatTimes--;

		//Repeat code		
		while(nRepeatTimes--)//110ms once a time.
			{
				SetGPOHL(0);
					udelay(9000);
				SetGPOHL(1);
					udelay(2250);
				SetGPOHL(0);
					udelay(560);
					
				SetGPOHL(1);	
				mdelay(98);
				udelay(190);
			}
	}	
}
void Irad_RC5(UINT16 nAddr,UINT16 nCommand,bool bToggle,bool bExtend)
{
    printk("\x1b[31mRC5\x1b[0m\n");

	//Head of RC_5:
    Irda_HL(1,"RC5");
	if(!bExtend)
		Irda_HL(1,"RC5");
	else// use as command bit7 when extended.
		Irda_HL((nCommand>>6)&0x1,"RC5");

	Irda_HL(bToggle,"RC5");

	//Address
	nAddr&=0x1F;//5 bits
	int i;
	for(i=4;i>=0;i--)
		{
			Irda_HL((nAddr>>i)&0x1,"RC5");//Msb-->Lsb
		}
	
	//Command
	nCommand&=0x3F;//6 bits

	for(i=5;i>=0;i--)
		{
			Irda_HL((nCommand>>i)&0x1,"RC5");//Msb-->Lsb
		}	

	SetGPOHL(1);	
}


void Irad_Sharp(UINT16 nAddr,UINT16 nCommand)
{
    printk("\x1b[31mSharp\x1b[0m\n");

    //Head of Sharp----none


	//Address
	nAddr&=0x1F;
	int i;
	for(i=0;i<5;i++)
		{
			Irda_HL((nAddr>>i)&0x1,"SHARP");//Lsb-->Msb
		}

	//Command
	nCommand&=0xFF;

	for(i=0;i<8;i++)
		{
			Irda_HL((nCommand>>i)&0x1,"SHARP");//Lsb-->Msb
		}

	//bExp and bChk
	Irda_HL(1,"SHARP");
	Irda_HL(0,"SHARP");

	

	//delay 40ms(GPO high) ,then transmit again,with all bits inverted.
    SetGPOHL(1); 
	mdelay(40);

	//then transmit again,with all bits inverted except address.
	//Address
	nAddr&=0x1F;

	for(i=0;i<5;i++)
		{
			Irda_HL((nAddr>>i)&0x1,"SHARP");//Lsb-->Msb
		}

	//Command
	nCommand&=0xFF;

	for(i=0;i<8;i++)
		{
			Irda_HL(!(nCommand>>i)&0x1,"SHARP");//Lsb-->Msb
		}

	//bExp and bChk--inverted
	Irda_HL(0,"SHARP");
	Irda_HL(1,"SHARP");

	SetGPOHL(1);	
}


void Irad_Sony(UINT16 nAddr,UINT16 nCommand)
{
    printk("\x1b[31mSony\x1b[0m\n");
	
    //Head of Sharp
    
	SetGPOHL(0);
		udelay(2400);
	SetGPOHL(1);
		udelay(600);		
		
	//Command
	nCommand&=0xFF;
	int i;	
	for(i=0;i<8;i++)
		{
			Irda_HL((nCommand>>i)&0x1,"SONY");//Lsb-->Msb
		}

	//Address
	nAddr&=0x1F;
	
	for(i=0;i<5;i++)
		{
			Irda_HL((nAddr>>i)&0x1,"SONY");//Lsb-->Msb
		}

	SetGPOHL(1);
}

void Irda_Out(char* protocal,UINT16 nAddr,UINT16 nCommand,UINT8 nRepeatTimes,bool bExtend)
{
    //Use ST_GPIO8 to Gen Irda signal.
    SetGPIOOut(8,0xb806024C,22,18,0x1f);
	printk("Write Data:0x%x==> Address:0x%x\n", nCommand,nAddr);
	
	if(strcmp(protocal,"NEC")==0)
		Irad_NEC(nAddr,nCommand,nRepeatTimes,bExtend);
	else if(strcmp(protocal,"RC5")==0)
		{
		bool bToggle = 0;
		Irad_RC5(nAddr,nCommand,bToggle,bExtend);
		}
	else if(strcmp(protocal,"SHARP")==0)
		Irad_Sharp(nAddr,nCommand);
	else if(strcmp(protocal,"SONY")==0)
		Irad_Sony(nAddr, nCommand);

	printk("Gen Irda Protocol finish!\n");
}































