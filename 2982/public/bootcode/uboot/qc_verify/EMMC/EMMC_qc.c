//#include <common.h>
//#include <command.h>
//#include <linux/compiler.h>
//#include <rbus/crt_reg.h>
//#include <asm/arch/io.h>
#include <qc_verify_common.h>
//#include "ecpu_stb_ap.h"

#define	SETBIT(x,n)		x = x | (1<<n)
#define	CLRBIT(x,n)		x = x & ~(1<<n)
#define SetBit(addr, nbit)	  	*((volatile unsigned int *) (addr-0xa0000000)) |= 1<<nbit
#define ResetBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) &= ~(1<<nbit)
#define ToggleBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) ^= 1<<nbit
#define WReg(addr, data)		*((volatile unsigned int *) (addr-0xa0000000)) = data
#define RReg(addr) 		    	*((volatile unsigned int *) (addr-0xa0000000))

#define		SD_STAT			0xb8010800
#define		SD_CMD0			0xb8010810
#define		SD_CMD1			0xb8010814
#define		SD_CMD2			0xb8010818
#define		SD_CMD3			0xb801081c
#define		SD_CMD4			0xb8010820

#define		SD_RSP0			0xb8010810
#define		SD_RSP1			0xb8010814
#define		SD_RSP2			0xb8010818
#define		SD_RSP3			0xb801081c
#define		SD_RSP4			0xb8010820

#define		SD_EXT_RSP0		0xb8010888
#define		SD_EXT_RSP1		0xb801088c
#define		SD_EXT_RSP2		0xb8010890
#define		SD_EXT_RSP3		0xb8010894
#define		SD_EXT_RSP4		0xb8010898
#define		SD_EXT_RSP5		0xb801089c
#define		SD_EXT_RSP6		0xb80108a0
#define		SD_EXT_RSP7		0xb80108a4
#define		SD_EXT_RSP8		0xb80108a8
#define		SD_EXT_RSP9		0xb80108ac
#define		SD_EXT_RSP10		0xb80108b0
#define		SD_EXT_RSP11		0xb80108b4
#define		SD_EXT_RSP12		0xb80108b8
#define		SD_EXT_RSP13		0xb80108bc
#define		SD_EXT_RSP14		0xb80108c0


#define		SD_ARB_STS			0xb80108c4
#define		SD_SRAM_DATA		0xb80108c8

#define		SD_CP_CTRL			0xb8010884

#define		EMMC_RSTN		0xb8000814
#define		EMMC_CLK		0xb8000810
#define		EMMC_CMD		0xb8000804
#define		EMMC_D0			0xb8000810
#define		EMMC_D1			0xb8000818
#define		EMMC_D2			0xb8000814
#define		EMMC_D3			0xb8000818
#define		EMMC_D4			0xb8000810
#define		EMMC_D5			0xb8000814
#define		EMMC_D6			0xb8000810
#define		EMMC_D7			0xb8000814
#define		EMMC_Freq	  0xb8000204

#define		DIV				  0x20
#define		NO_DIV			0x0
#define		timeout     50000
#define   busy        50000

static unsigned int transfer_enable = 0;
static unsigned int BUS_WIDTH = 0; //cck 0-->1
static unsigned int Set_BUS_WIDTH = 0; //cck 0-->1
static unsigned int HS_TIMMING = 0;
static unsigned int RCA_H = 0;
static unsigned int RCA_L = 0;
static unsigned int SET_BLOCKLEN = 0x2;

static unsigned int BUS_WIDTH_HS = 0;
static unsigned int DDR_ADDR = 0;
static unsigned int DATA_ADDR = 0;
static unsigned int Byte_Count = 0;
static unsigned int BYTE_CNT = 128;

static unsigned int Block_Count = 0;
static unsigned int emmc_freq = 0;
static unsigned int i = 0, j = 0 ,k = 0, m = 0,n = 0;


static int INDEX = 0;



static void emmc_pin_mux_setting()
{
#if CONFIG_BGA
//-------- Sirius eMMC Pinmux Setting for TV BGA China--------------------------------------
//rtd_maskl(0xb8000914,0x000000ff,0x6aa95000); // EMMC_Source control reg(BGA)
//rtd_maskl(0xb80008a4,0xffffc000,0x00000400); // EMMC_CLK gpio_157  
//rtd_maskl(0xb8000958,0x00000000,0x007c3e00); // EMMC_CMD/RST gpio_150/151 
//rtd_maskl(0xb8000888,0xff800000,0x00080400); // EMMC_DAT0/1 gpio_184/185  
//rtd_maskl(0xb8000884,0xff800000,0x00080400); // EMMC_DAT2/7 gpio_181/182 
//rtd_maskl(0xb800088c,0xffffc000,0x00000400); // EMMC_DAT5 gpio_188 
//rtd_maskl(0xb8000874,0x00003fff,0x00080000); // EMMC_DAT6 gpio_169 
//rtd_maskl(0xb80008A0,0x00003fff,0x10080000); // EMMC_DAT4/EMMC_DAT3 gpio_152/gpio_153
//
//rtd_inl(0xb8000914);
//rtd_inl(0xb80008a4);
//rtd_inl(0xb8000958);
//rtd_inl(0xb8000888);
//rtd_inl(0xb8000884);
//rtd_inl(0xb800088c);
//rtd_inl(0xb8000874);
//rtd_inl(0xb80008A0); 
	
rtd_part_outl(0xb8000914,30,28,0x6);   // EMMC_Source control reg(BGA)
rtd_part_outl(0xb8000914,27,20,0xaa);   // EMMC_Source control reg(BGA)
rtd_part_outl(0xb8000914,19,18,0x2);   // EMMC_Source control reg(BGA)
rtd_part_outl(0xb8000914,16,11,0x2a);   // EMMC_Source control reg(BGA)

rtd_part_outl(0xb80008a4,13,5,0x20);  // EMMC_CLK gpio_157 
rtd_part_outl(0xb8000958,22,18,0x2);   // EMMC_CMD/RST gpio_150/151
rtd_part_outl(0xb8000958,17,14,0x0);   // EMMC_CMD/RST gpio_150/151
rtd_part_outl(0xb8000958,13,9,0x1F);   // EMMC_CMD/RST gpio_150/151
rtd_part_outl(0xb8000958,8,5,0x0);   // EMMC_CMD/RST gpio_150/151
rtd_part_outl(0xb8000888,22,18,0x2);   // EMMC_DAT0/1 gpio_184/185  
rtd_part_outl(0xb8000888,17,14,0x0);   // EMMC_DAT0/1 gpio_184/185  
rtd_part_outl(0xb8000888,13,9,0x2);   // EMMC_DAT0/1 gpio_184/185  
rtd_part_outl(0xb8000888,8,5,0x0);   // EMMC_DAT0/1 gpio_184/185  

rtd_part_outl(0xb8000884,22,18,0x2);   // EMMC_DAT2/7 gpio_181/182
rtd_part_outl(0xb8000884,17,14,0x0);   // EMMC_DAT2/7 gpio_181/182 
rtd_part_outl(0xb8000884,13,9,0x2);   // EMMC_DAT2/7 gpio_181/182 
rtd_part_outl(0xb8000884,8,5,0x0);   // EMMC_DAT2/7 gpio_181/182  


rtd_part_outl(0xb800088c,13,9,0x2);  // EMMC_DAT5 gpio_188 
rtd_part_outl(0xb800088c,8,5,0x0);  // EMMC_DAT5 gpio_188 
rtd_part_outl(0xb8000874,21,18,0x2);     //EMMC_DAT6 gpio_169 
rtd_part_outl(0xb8000874,17,14,0x0);     //EMMC_DAT6 gpio_169 
rtd_part_outl(0xb80008a0,31,27,0x2);     //EMMC_DAT4/EMMC_DAT3 gpio_152/gpio_153
rtd_part_outl(0xb80008a0,26,23,0x0);     //EMMC_DAT4/EMMC_DAT3 gpio_152/gpio_153
rtd_part_outl(0xb80008a0,22,18,0x2);     //EMMC_DAT4/EMMC_DAT3 gpio_152/gpio_153
rtd_part_outl(0xb80008a0,17,14,0x0);     //EMMC_DAT4/EMMC_DAT3 gpio_152/gpio_153

rtd_inl(0xb8000914);
rtd_inl(0xb80008a4);
rtd_inl(0xb8000958);
rtd_inl(0xb8000888);
rtd_inl(0xb8000884);
rtd_inl(0xb800088c);
rtd_inl(0xb8000874);
rtd_inl(0xb80008A0);	 
#else	
	//-------- Sirius eMMC Pinmux Setting for TV 176LQFP --------------------------------------
rtd_maskl(0xb8000914,0x000000ff,0x10000000); // EMMC_Source control reg(176/256 QFP)
rtd_maskl(0xb8060248,0x00ffffff,0x08000000); // EMMC_CLK st_gpio_12  
rtd_maskl(0xb8000844,0xffffc000,0x00000400); // EMMC_CMD gpio_56 
rtd_maskl(0xb8000834,0xffffc000,0x00000400); // EMMC_DAT0 gpio_44 
rtd_maskl(0xb8000838,0x00000000,0x10080400); // EMMC_DAT1/2/3 gpio_45/46/47 
rtd_maskl(0xb800083c,0x00000000,0x10080400); // EMMC_DAT4/5/6 gpio_48/49/50 
rtd_maskl(0xb8000840,0x007fffff,0x10000000); // EMMC_DAT7 gpio_51
rtd_maskl(0xb80008F8,0xffc0fffff,0x003e0000); //EMMC_RST_N 0x1800_08F8[21:17]=0x1F  bb_dio3_ps  GPIO196

rtd_inl(0xb8000914);
rtd_inl(0xb8060248);
rtd_inl(0xb8000844);
rtd_inl(0xb8000834);
rtd_inl(0xb8000838);
rtd_inl(0xb800083c);
rtd_inl(0xb8000840);
rtd_inl(0xb80008F8); 
#endif    


//printf( "check pinmux reg value.\n");                            	
//printf( "rtd_inl(0xb8000914) = 0x%08x\n", RReg( 0xb8000914 ) );  	
//printf( "rtd_inl(0xb80008a4) = 0x%08x\n", RReg( 0xb80008a4 ) );  	
//printf( "rtd_inl(0xb8000958) = 0x%08x\n", RReg( 0xb8000958 ) );  	
//printf( "rtd_inl(0xb8000888) = 0x%08x\n", RReg( 0xb8000888 ) );  	
//printf( "rtd_inl(0xb8000884) = 0x%08x\n", RReg( 0xb8000884 ) );  	
//printf( "rtd_inl(0xb800088c) = 0x%08x\n", RReg( 0xb800088c ) );  	
//printf( "rtd_inl(0xb8000874) = 0x%08x\n", RReg( 0xb8000874 ) );  	
//printf( "rtd_inl(0xb80008a0) = 0x%08x\n", RReg( 0xb80008a0 ) );  	
                                                                  	


//printf( "check pinmux reg value.\n");                           
//printf( "rtd_inl(0xb8000914) = 0x%08x\n", RReg( 0xb8000914 ) ); 
//printf( "rtd_inl(0xb8060248) = 0x%08x\n", RReg( 0xb8060248 ) ); 
//printf( "rtd_inl(0xb8000844) = 0x%08x\n", RReg( 0xb8000844 ) ); 
//printf( "rtd_inl(0xb8000834) = 0x%08x\n", RReg( 0xb8000834 ) ); 
//printf( "rtd_inl(0xb8000838) = 0x%08x\n", RReg( 0xb8000838 ) );
	//printf( "rtd_inl(0xb800083c) = 0x%08x\n", RReg( 0xb800083c ) );
	//printf( "rtd_inl(0xb8000840) = 0x%08x\n", RReg( 0xb8000840 ) );
  //printf( "rtd_inl(0xb80008f8) = 0x%08x\n", RReg( 0xb80008f8 ) );
}

static void emmc_change_freq()
{
		//rtd_part_outl(0xb8000040,31,30,0x2);   // SD/EMMC clock source selection    10: from rbus_clk    11: from dbus_clk
		//rtd_part_outl(0xb8000040,31,30,0x3);   // SD/EMMC clock source selection    10: from rbus_clk    11: from dbus_clk	
		//ResetBit( 0xb8000040,4 );  
		//ResetBit( 0xb8000040,5 );
		//ResetBit( 0xb8000040,6 );
		//SetBit( 0xb8000040,7 );
	//printf( "rtd_inl(0xb8000040) = 0x%08x\n", RReg( 0xb8000040 ) );    		
	//WReg(0xb8000040, 0x8e);	
		
	  //rtd_part_outl(0xb8000040,7,4,emmc_freq);    // EMMC freq divide select,   write_en=1 
 		//rtd_part_outl(0xb8000040,7,4,0x8);    // EMMC freq divide select: 0: div2    50M       115M    
 		//rtd_part_outl(0xb8000040,7,4,0x9);    // EMMC freq divide select: 1: div3  33.3M     73.5M
		//rtd_part_outl(0xb8000040,7,4,0xa);    // EMMC freq divide select: 2: div4  25M       56.2M    
		//rtd_part_outl(0xb8000040,7,4,0xb);    // EMMC freq divide select: 3: div5  20M       44.2M
		//rtd_part_outl(0xb8000040,7,4,0xc);    // EMMC freq divide select: 4: div6  16.7M     37.2M
		//rtd_part_outl(0xb8000040,7,4,0xd);    // EMMC freq divide select: 5: div8  12.5M     27.9M
		//rtd_part_outl(0xb8000040,7,4,0xe);    // EMMC freq divide select: 6: div10 10M       22.8M
	
	printf( "change freq reg value.\n");
	printf( "rtd_inl(0xb8000040) = 0x%08x\n", RReg( 0xb8000040 ) );
}

static void emmc_reset()
{
	ResetBit( 0xb8000004,11 ); //rst enable
	ResetBit( 0xb800000c,24 ); //clk enable
	udelay( 10 );
	SetBit( 0xb8000004,11 );
	SetBit( 0xb800000c,24 );
		

	/*
	 * eMMC reset pin
	 * 1. 0xB800_0814[31:28] = F    --> pin share as gpio
	 * 2. 0x1801_BC00[20] = 1  --> output mode
	 * 3. 0x1801_BC18[20]   is output data
	*/
	printf( "\neMMC reset\n" );
	rtd_maskl(0xb80008F8,0xffc0fffff,0x003e0000); //EMMC_RST_N 0x1800_08F8[21:17]=0x1F  bb_dio3_ps  GPIO196
	SetBit( 0xb801b118,4 );      //set gpio196 to output pin
	ResetBit( 0xb801b134,4 );    // set output low
	mdelay( 1 );
	SetBit( 0xb801b134,4 );     // set output high
	//rtd_part_outl( 0xb8000814,31,28,0xF ); // for magellan
	//SetBit( 0xb801bc00,20 );
	//ResetBit( 0xb801bc18,20 );
	//mdelay( 1 );
	//SetBit( 0xb801bc18,20 );

	/* issue sram mode autoread3 to send bus clock */
	SetBit( 0xb8010884,3 );

	// 512 byte
	rtd_outl( 0xb8010824, 0x0 );	// byte count [7:0]
	rtd_outl( 0xb8010828, 0x2 );	// byte count [10:8]

	// 1 block
	rtd_outl( 0xb801082c, 0x1 );	// block count [7:0]
	rtd_outl( 0xb8010830, 0x0 );	// block count [11:8]

	rtd_outl( 0xb8010804, DIV );	//  diviede 256

	rtd_outl( 0xb8010808, 0x5 );
	rtd_outl( 0xb8010808, 0x85 );

	mdelay( 100 );

	ResetBit( 0xb8000004,11 ); //rst enable
	ResetBit( 0xb800000c,24 ); //clk enable
	udelay( 10 );
	SetBit( 0xb8000004,11 );
	SetBit( 0xb800000c,24 );
//
//	return 0;

}





static void ddr_pattern_write( unsigned int PATTERN, unsigned int DDR_ADDR, unsigned int BYTE_CNT )
{
	printf( "\nwrite ddr \n");
	unsigned int i,DDR_VAL;
	DDR_VAL	 =	PATTERN;
	printf( "write ddr from addr = 0x%08x\n",( DDR_ADDR) );
	for( i=0; i < BYTE_CNT; i++ ) {
		//WReg( DDR_ADDR , DDR_VAL );
		rtd_outl(DDR_ADDR, DDR_VAL);
		DDR_ADDR = DDR_ADDR + 4;
	}
}

static void ddr_pattern_erase( unsigned int DDR_ADDR, unsigned int BYTE_CNT )
{
	printf( "\nerase ddr \n");
	unsigned int i, DDR_VAL;
	DDR_VAL	 =	0x0;
	for( i=0; i < BYTE_CNT; i++ ) {
		//WReg( DDR_ADDR , DDR_VAL );
		rtd_outl(DDR_ADDR, DDR_VAL);
		DDR_ADDR = DDR_ADDR + 4;
	}
}

static void ddr_pattern_read( unsigned int DDR_ADDR, unsigned int BYTE_CNT,unsigned int PATTERN )
{
	printf( "\nread ddr \n");
	unsigned int i;
	for( i=0; i < BYTE_CNT; i++ ) 
	{
		if( rtd_inl(DDR_ADDR) != PATTERN){
		//if( RReg( DDR_ADDR ) != PATTERN){
			INDEX = -1;
			//break;
		}
		//printf( "DDR_ADDR=0x%08x, Value=0x%08x\n",( DDR_ADDR-0xa0000000),RReg( DDR_ADDR ) );  
	//	printf( "DDR_ADDR=0x%08x, Value=0x%08x\n",DDR_ADDR,rtd_inl(DDR_ADDR) );
		DDR_ADDR =DDR_ADDR+ 4;
	}
	
	if(i == BYTE_CNT)
	printf("\ncheck ddr pattern ok, ByteCNT = %d\n",i);
	//printf("\n ");
	else
		return -1;
}

static void print_normal_resp()                                         
{                                                                      
j = 0;
for(i = 0 ; i < 5; i++)
	{ 	
	 //printf("emmc_resp[%d]: rtd(0x%08x) = 0x%08x\n",i,( 0xb8010810 + j),RReg( 0xb8010810 + j));
   j += 4; 
  
  }                                                                   
  //printf("tansfer code is: rtd(0xb8010808) = 0x%08x\n",RReg( 0xb8010808));                                                                  
}

static void print_long_resp()                                         
{                                                                      
j = 0;
for(i = 0 ; i < 15; i++)  //Total 17Byte  0x1801_0888~0x1801_08C0
	{ 	
	 //printf("emmc_lresp[%d]: rtd(0x%08x) = 0x%08x\n",i,( 0xb8010888 + j),RReg( 0xb8010888 + j));
   j += 4; 
  
  }                                                                   
                                                                     
}


static void check_transfer(unsigned int cmd_code)   
//cmd_code:  68 SEND_CMD_GET_RSP,60 NORMAL_WRITE,61 AUTO_WRITE3,62 AUTO_WRITE4,65 AUTO_READ3
//           66 AUTO_READ4,69 AUTO_WRITE1,6a AUTO_WRITE2,6c NORMAL_READ1,6d AUTO_READ1,6e AUTO_READ2

{
   for(i = 0; i < timeout; i++)
   {
  	transfer_enable = rtd_inl(0xb8010808); 
  	
  	if (transfer_enable == cmd_code)
  		{
  		printf("timeout break at number %d \n", i);
  	  break;
  	  }		
   }
  	if (transfer_enable == cmd_code)
  		printf( "EMMC CMD PASS,cmd code = %d\n",transfer_enable);
  		else
		  {
		  printf( "EMMC CMD TIMEOUT,cmd code = %d\n",transfer_enable);
		  //return FAILED;
		  INDEX = -1; 
	    }
}  	


static int check_transfer_status()
{
	int i;
	i=0;
	while( 1 ) {
		if( rtd_part_inl( 0xb8010808,6,6 ) == 1 ) {
			//printf( "transfer done" ); 
			//printf( "\n" );

			if( rtd_part_inl( 0xb8010808,4,4 ) == 1 ) {
				if( rtd_part_inl( SD_STAT,7,7 )==1 )
					printf( " -->CRC7 Error\n" );
				if( rtd_part_inl( SD_STAT,6,6 )==1 )
					printf( " -->CRC16 Error\n" );
				if( rtd_part_inl( SD_STAT,5,5 )==1 )
					printf( " -->Write Error\n" );
				printf( " -->DAT0 = %x\n",rtd_part_inl( SD_STAT,1,1 ) );
				INDEX = -1;
			} else {
				//printf( " -->Correct\n" );
				printf( "\n" );
				}
			break;
		}
		mdelay( 1 );
		i++;
		if( i == 200 ) {
			printf( "transfer didn't complete, End bit = 0\n" );
      return FAILED;
			break;
		}
	} 
	printf("tansfer code is: rtd(0xb8010808) = 0x%08x\n",RReg( 0xb8010808));  
}
	
static void check_cid()
{
	unsigned int mid_num;
	//printf( "CID register value\n" );
	//printf( "CID[127:120]=0x%02x\n",RReg( SD_EXT_RSP0 ) );
	//printf( "CID[119:112]=0x%02x\n",RReg( SD_EXT_RSP1 ) );
	//printf( "CID[111:104]=0x%02x\n",RReg( SD_EXT_RSP2 ) );
	//printf( "CID[103: 96]=0x%02x\n",RReg( SD_EXT_RSP3 ) );
	//printf( "CID[ 95: 88]=0x%02x\n",RReg( SD_EXT_RSP4 ) );
	//printf( "CID[ 87: 80]=0x%02x\n",RReg( SD_EXT_RSP5 ) );
	//printf( "CID[ 79: 72]=0x%02x\n",RReg( SD_EXT_RSP6 ) );
	//printf( "CID[ 71: 64]=0x%02x\n",RReg( SD_EXT_RSP7 ) );
	//printf( "CID[ 63: 56]=0x%02x\n",RReg( SD_EXT_RSP8 ) );
	//printf( "CID[ 55: 48]=0x%02x\n",RReg( SD_EXT_RSP9 ) );
	//printf( "CID[ 47: 40]=0x%02x\n",RReg( SD_EXT_RSP10 ) );
	//printf( "CID[ 39: 32]=0x%02x\n",RReg( SD_EXT_RSP11 ) );
	//printf( "CID[ 31: 24]=0x%02x\n",RReg( SD_EXT_RSP12 ) );
	//printf( "CID[ 23: 16]=0x%02x\n",RReg( SD_EXT_RSP13 ) );
	//printf( "CID[ 15:  8]=0x%02x\n",RReg( SD_EXT_RSP14 ) );


	mid_num = RReg( SD_EXT_RSP0 );
	switch ( mid_num ) 
	{
		case 0x2:
			printf( "Manufacturer:Sandisk (MID=0x%02x)\n", mid_num );
			break;

		case 0x11:
			printf( "Manufacturer:Toshiba (MID=0x%02x)\n", mid_num );
			break;

		case 0x15:
			printf( "Manufacturer:Samsung (MID=0x%02x)\n", mid_num );
			break;

		case 0x70:
			printf( "Manufacturer:Kingston (MID=0x%02x)\n", mid_num );
			break;

		case 0x90:
			printf( "Manufacturer:SKhynix (MID=0x%02x)\n", mid_num );
			break;

		case 0xfe:
			printf( "Manufacturer:Micron (MID=0x%02x)\n", mid_num );
			break;

		default:
			printf( "Manufacturer:Unknow (MID=0x%02x)\n", mid_num );
			break;
	}
	if( ( RReg( SD_EXT_RSP14 )&0x0F ) == 0 )
		printf( "No manufacturing date\n" );
	else
		printf( "Manufacturing date:%d/%02d\n",( RReg( SD_EXT_RSP14 )&0x0F )+1997,( RReg( SD_EXT_RSP14 )>>4 ) );
}

static void check_csd()
{
//printf( "CSD register\n" );
	//printf( "CSD[127:120]=0x%02x\n",RReg( SD_EXT_RSP0 ) );
	//printf( "CSD[119:112]=0x%02x\n",RReg( SD_EXT_RSP1 ) );
	//printf( "CSD[111:104]=0x%02x\n",RReg( SD_EXT_RSP2 ) );
	//printf( "CSD[103: 96]=0x%02x\n",RReg( SD_EXT_RSP3 ) );
	//printf( "CSD[ 95: 88]=0x%02x\n",RReg( SD_EXT_RSP4 ) );
	//printf( "CSD[ 87: 80]=0x%02x\n",RReg( SD_EXT_RSP5 ) );
	//printf( "CSD[ 79: 72]=0x%02x\n",RReg( SD_EXT_RSP6 ) );
	//printf( "CSD[ 71: 64]=0x%02x\n",RReg( SD_EXT_RSP7 ) );
	//printf( "CSD[ 63: 56]=0x%02x\n",RReg( SD_EXT_RSP8 ) );
	//printf( "CSD[ 55: 48]=0x%02x\n",RReg( SD_EXT_RSP9 ) );
	//printf( "CSD[ 47: 40]=0x%02x\n",RReg( SD_EXT_RSP10 ) );
	//printf( "CSD[ 39: 32]=0x%02x\n",RReg( SD_EXT_RSP11 ) );
	//printf( "CSD[ 31: 24]=0x%02x\n",RReg( SD_EXT_RSP12 ) );
	//printf( "CSD[ 23: 16]=0x%02x\n",RReg( SD_EXT_RSP13 ) );
	//printf( "CSD[ 15:  8]=0x%02x\n",RReg( SD_EXT_RSP14 ) );
}


static void check_OCR()
{
	printf( "OCR register\n" );
	printf( "OCR[31:24]=0x%02x\n",RReg( SD_RSP1 ) );
	printf( "OCR[23:16]=0x%02x\n",RReg( SD_RSP2 ) );
	printf( "OCR[15: 8]=0x%02x\n",RReg( SD_RSP3 ) );
	printf( "OCR[ 7: 0]=0x%02x\n",RReg( SD_RSP4 ) );
}

static void check_status()
{
  unsigned int status_num;

	printf( "cmd index=%d\n",rtd_part_inl( SD_RSP0,5,0 ) );
//	printf( "card status[31:24]=0x%02x\n",RReg( SD_RSP1 ) );
//	printf( "card status[23:16]=0x%02x\n",RReg( SD_RSP2 ) );
//	printf( "card status[15: 8]=0x%02x\n",RReg( SD_RSP3 ) );
//	printf( "card status[ 7: 0]=0x%02x\n",RReg( SD_RSP4 ) );

	status_num = rtd_part_inl( SD_RSP3,4,1 );
	switch( status_num ) 
	{
		case 0:
			printf( "current_state = Idle\n" );
			break;
		case 1:
			printf( "current_state = Ready\n" );
			break;
		case 2:
			printf( "current_state = Ident\n" );
			break;
		case 3:
			printf( "current_state = Stby\n" );
			break;
		case 4:
			printf( "current_state = Tran\n" );
			break;
		case 5:
			printf( "current_state = Data\n" );
			break;
		case 6:
			printf( "current_state = Rcv\n" );
			break;
		case 7:
			printf( "current_state = Prg\n" );
			break;
		case 8:
			printf( "current_state = Dis\n" );
			break;
		case 9:
			printf( "current_state = Btst\n" );
			break;
		default:
			printf( "error state\n" );
			break;
	}
}

			
static void cmd_0()
{
	printf( "\ncmd0 : GO_IDLE_STATE\n" );
	rtd_outl( 0xb8010810, 0x40 ); //  transmission bit =  0x1 ;
	rtd_outl( 0xb8010814, 0x0 );
	rtd_outl( 0xb8010818, 0x0 );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x04 );	//  no response and  no crc check
	rtd_outl( 0xb8010804, DIV );	//  diviede 256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
}

static unsigned int cmd_1()
{
	printf( "\ncmd1: SEND_OP_COND\n" );

	//ask the card to send its OCR contents
	rtd_outl( 0xb8010810, 0x41 );		//  transmission bit =  0x1 ;
	rtd_outl( 0xb8010814, 0x40 );		// [31]: power up status, [30:29] access mode:2'b10 sector mode, [28:24] reserved
	rtd_outl( 0xb8010818, 0xff );		// [23:15]  2.7~3.6V
	rtd_outl( 0xb801081c, 0x80 ); 		// [14:8] 2.0~2.6V [7] 1.70~1.95V
	rtd_outl( 0xb8010820, 0x00 );
	rtd_outl( 0xb801080c, 0x5 );		//  check crc7 off  6 byte response
	rtd_outl( 0xb8010804, DIV );		//diviede 256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_OCR();
	return ( rtd_part_inl( SD_RSP1,7,7 ) );  // C0     [7]: busy bit  [6:5] sector/byte mode
}

static void cmd_2()
{
	printf( "\ncmd2 : ALL_SEND_CID\n" );
	//ask the card to send its CID contents
	rtd_outl( 0xb8010810, 0x42 ); //  transmission bit =  0x1 ;  command = 0x2
	rtd_outl( 0xb8010814, 0x0 );
	rtd_outl( 0xb8010818, 0x0 );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010804, DIV );	//  diviede 256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_long_resp();
	//check_cid();

}

static void cmd_3()
{
//	int ret;
	printf( "\ncmd3 : SET_RELATIVE_ADDR\n" );
	rtd_outl( 0xb8010810, 0x43 ); //  transmission bit =  0x1 ;  command = 0x3
	rtd_outl( 0xb8010814, RCA_H );
	rtd_outl( 0xb8010818, RCA_L );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x1 );	//  6 byte response and CRC check
	rtd_outl( 0xb8010804, DIV );	//  diviede 256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	printf( "Assign eMMC address: RCA_H=0x%02x, RCA_L=0x%02x\n",RCA_H,RCA_L );
}

static void cmd_6_switch_bit(unsigned int value )    //value, 0:1-bit, 1:4-bit 2:8-bit
{
	printf( "\ncmd6 : SWITCH\n" );
	//printf("change bus_width = %d-bit\n",bus_width);

	rtd_outl( 0xb8010810, 0x46 );		//  transmission bit =  0x1 ;
	rtd_outl( 0xb8010814, 0x03 );		//[31:26] set 0, [25:24] access, =2b'11, Write byte
	rtd_outl( 0xb8010818, 0xB7 );		//[23:16] index,
	rtd_outl( 0xb801081c, value );		//[15:8] value, 0:1-bit, 1:4-bit 2:8-bit
	rtd_outl( 0xb8010820, 0x00 );		//[7:3] set 0, [2:0] cmd set
	rtd_outl( 0xb801080c, 0x1 );		//  6 byte response
	rtd_outl( 0xb8010804, DIV );		//  no diviede
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_6_switch(unsigned int value )	// Value= 1, high speed,default = 0
{
	printf( "\ncmd6 : SWITCH\n" );
	//printf("change bus_width = %d-bit\n",bus_width);
	rtd_outl( 0xb8010810, 0x46 );		//  transmission bit =  0x1 ;
	rtd_outl( 0xb8010814, 0x03 );		//[31:26] set 0, [25:24] access, =2b'11, Write byte
  rtd_outl(0xb8010818, 0xB9);	
  rtd_outl(0xb801081c, value);	// Value= 1, high speed,default = 0
	rtd_outl( 0xb8010820, 0x00 );		//[7:3] set 0, [2:0] cmd set
	rtd_outl( 0xb801080c, 0x1 );		//  6 byte response
	rtd_outl( 0xb8010804, DIV );		//  no diviede
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void setting_bus_width( unsigned int bus_width ) 
{
	
	switch ( bus_width ) {
		case 1:
			Set_BUS_WIDTH = 0x0;
			cmd_6_switch_bit(Set_BUS_WIDTH );
			printf( "Set bus width = 1-bit\n" );
			break;
		case 4:
			Set_BUS_WIDTH = 0x1;
			cmd_6_switch_bit(Set_BUS_WIDTH );
			printf( "Set bus width = 4-bit\n" );
			break;
		case 8:
			Set_BUS_WIDTH = 0x2;
			cmd_6_switch_bit(Set_BUS_WIDTH );
			printf( "Set bus width = 8-bit\n" );
			break;
		default:
			printf( "Bus Width setting is invalid\n" );
			break;
	}
}


// HS_TIMING  [185] [7:4] Selected Driver Strength  ,[3:0] Hspeed mode

static setting_HS_Mode( unsigned int HSpeed )   // Value= 1, high speed,default = 0, backwards compatibility interface timming
{                                               // Value= 2, HS200
	unsigned int Highspeed = 0;
	
	switch ( HSpeed ){
		case 0:
			Highspeed = 0;
			cmd_6_switch(Highspeed);
			printf( "Set Normal Speed Mode\n" );
			break;
		case 1:
			Highspeed = 1;
			cmd_6_switch(Highspeed);
			printf( "Set High Speed Mode\n" );
			break;
		case 2:
			Highspeed = 2;
			cmd_6_switch(Highspeed);
			printf( "Set HS200 Mode\n" );
			break;	
		default:
			printf( "Speed Mode setting is invalid\n" );
			break;
	}
}




static void cmd_7()
{
	printf( "\ncmd7 : SELECT/DESELECT_CARD  RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	rtd_outl( 0xb8010810, 0x47 ); 	//  transmission bit =  0x1 ;  command = 0x7
	rtd_outl( 0xb8010814, RCA_H );
	rtd_outl( 0xb8010818, RCA_L );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x1 );	//  6 byte response and CRC check
	rtd_outl( 0xb8010804, DIV );	//  divide  256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_7_0()
{
	printf( "\ncmd7 RCA_H=%x, RCA_L=%x\n",0,0 );
	rtd_outl( 0xb8010810, 0x47 ); 	//  transmission bit =  0x1 ;  command = 0x7
	rtd_outl( 0xb8010814, 0x0 );
	rtd_outl( 0xb8010818, 0x0 );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x0 );		// need no response
	rtd_outl( 0xb8010804, DIV );	//  divide  256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_8()
{
	printf( "\ncmd8 : SEND_EXT_CSD\n" );
	rtd_outl( 0xb8010840, 0x22000000 ); //DDR address: card to ddr
	rtd_outl(0xb8010840, 0x22000000); //DDR address
  rtd_outl(0xb8010844, 0x22000000); //DDR address 
	rtd_outl( 0xb8010810, 0x48 );		//A0, CMD8, Read single block
	rtd_outl( 0xb8010814, 0x00 );		//A1, data address [31:24]
	rtd_outl( 0xb8010818, 0x00 );		//A2, data address [23:16]
	rtd_outl( 0xb801081c, 0x20 );		//A3, data address [15:8]
	rtd_outl( 0xb8010820, 0x00 );		//A4, data address [7:0]

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
	//rtd_outl( 0xb801080c, 0x41 );	//   6 byte response
//	rtd_outl( 0xb8010804, BUS_WIDTH );	//  no diviede  ; 8 -bit
	rtd_outl( 0xb8010804, 0x2 );	//  no diviede  ; 8 -bit
	// 512 byte
	rtd_outl( 0xb8010824, 0x0 );	// byte count [7:0]
	rtd_outl( 0xb8010828, 0x2 );	// byte count [10:8]

	// 1 block
	rtd_outl( 0xb801082c, 0x1 );	// block count [7:0]
	rtd_outl( 0xb8010830, 0x0 );	// block count [11:8]

	//normal read
	rtd_outl( 0xb8010808, 0xc );
	rtd_outl( 0xb8010808, 0x8c ); // 1100 normalread

	check_transfer_status();
	//print_normal_resp();
	printf( "\n\nExtended CSD Value\n" );
	
	//ddr_pattern_read
	
	//unsigned int i;
	DDR_ADDR = 	0xc2000000;
	//BYTE_CNT =  128;
	//printf( "read ddr\n" );
	
	for( i=0; i < 128; i++ ) {
		
		printf( "DDR_ADDR = 0x%08x, Value = 0x%08x\n",( DDR_ADDR - 0xa0000000 ), RReg( DDR_ADDR ) );
		
		DDR_ADDR =DDR_ADDR+ 4;
	}
}


static void cmd_9()
{
	printf( "\ncmd9 : SEND_CSD RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	rtd_outl( 0xb8010810, 0x49 ); //  transmission bit =  0x1 ;  command = 0x9
	rtd_outl( 0xb8010814, RCA_H );
	rtd_outl( 0xb8010818, RCA_L );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010804, DIV );	//  diviede 256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_long_resp();
	check_csd();
}

static void cmd_10()
{
	printf( "\ncmd10 : SEND_CID RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	//ask the card to send its CID contents
	rtd_outl( 0xb8010810, 0x4A ); //  transmission bit =  0x1 ;  command = 0xA
	rtd_outl( 0xb8010814, RCA_H );
	rtd_outl( 0xb8010818, RCA_L );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010804, DIV );	//   diviede_256
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_long_resp();
	check_cid();

}


static void cmd_12()
{
	printf( "\ncmd12 : STOP_TRANSMISSION\n" );
	rtd_outl( 0xb8010810, 0x4C );
	rtd_outl( 0xb8010814, 0x0 );
	rtd_outl( 0xb8010818, 0x0 );
	rtd_outl( 0xb801081c, 0x0 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb8010824, 0x5 );
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
	//rtd_outl( 0xb8010804, 0x1);	//  auto2/3 set this reg
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 ); 	//1000 command response
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_13()
{
	printf( "\ncmd13 : SEND_STATUS\n" );
	rtd_outl( 0xb8010810, 0x4d );		//transmission bit =  0x1 ;  command = 0xd
	rtd_outl( 0xb8010814, RCA_H );		//[31:24] RCA
	rtd_outl( 0xb8010818, RCA_L );		//[23:16]RCA
	rtd_outl( 0xb801081c, 0x0 );  		//stuff bit
	rtd_outl( 0xb8010820, 0x0 );		//stuff bit
	rtd_outl( 0xb801080c, 0x1 );		//  6 byte response and CRC check
	rtd_outl( 0xb8010804, NO_DIV );	//  no divide
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_16()
{
	printf( "\ncmd16 : SET_BLOCKLEN\n" );

	rtd_outl( 0xb8010810, 0x50 );		//  transmission bit =  0x1 ;  command = 0x10
	rtd_outl( 0xb8010814, 0x0 );
	rtd_outl( 0xb8010818, 0x0 );
	rtd_outl( 0xb801081c, SET_BLOCKLEN );
  //rtd_outl( 0xb801081c, 0x2 );
	rtd_outl( 0xb8010820, 0x0 );
	rtd_outl( 0xb801080c, 0x1 );		//  6 byte response and CRC check
	rtd_outl( 0xb8010804, NO_DIV );	//  no divide
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_18()
{
	printf( "\ncmd18 : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010810, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010808, 0x8 ); // normal cmd
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
}


static void cmd_25()
{
	printf( "\ncmd25 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010810, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response


	rtd_outl( 0xb8010808, 0x8 ); // normal cmd
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
}			



static void auto_read_1()
{
	printf( "\nauto_read_1 : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010810, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010808, 0xd ); // auto read1:0xd, auto read2:0xe
	rtd_outl( 0xb8010808, 0x8d );
	check_transfer_status();
	print_normal_resp();
}


static void auto_read_2()
{
	printf( "\nauto_read_2 : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010810, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response
 
	rtd_outl( 0xb8010808, 0xe ); // auto read1:0xd, auto read2:0xe
	rtd_outl( 0xb8010808, 0x8e );
	check_transfer_status();
	print_normal_resp();
}

static void auto_read_3()
{
	printf( "\nauto_read_3 : READ_MULTIPLE_BLOCK\n" );
	
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response
 
	rtd_outl( 0xb8010808, 0x5 ); // auto read3:0x5, auto read4:0x6
	rtd_outl( 0xb8010808, 0x85 );
	check_transfer_status();
	print_normal_resp();
}

static void auto_read_4()
{
	printf( "\nauto_read_4 : READ_MULTIPLE_BLOCK\n" );
	
	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response
 
	rtd_outl( 0xb8010808, 0x6 ); // auto read3:0x5, auto read4:0x6
	rtd_outl( 0xb8010808, 0x86 );
	check_transfer_status();
	print_normal_resp();
}


static void auto_write_1()
{
	printf( "\nauto_write_1 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010810, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response


	rtd_outl( 0xb8010808, 0x9 ); // auto write1: 0x9, auto write2:0xA
	rtd_outl( 0xb8010808, 0x89 );
	check_transfer_status();
	print_normal_resp();
}			

static void auto_write_2()
{
	printf( "\nauto_write_2 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010810, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response


	rtd_outl( 0xb8010808, 0xa ); // auto write2: 0x9, auto write2:0xA
	rtd_outl( 0xb8010808, 0x8a );
	check_transfer_status();
	print_normal_resp();
}	

static void auto_write_3()
{
	printf( "\nauto_write_3 : WRITE_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response

	rtd_outl( 0xb8010808, 0x1 ); // auto write3: 0x1, auto write4:0x2
	rtd_outl( 0xb8010808, 0x81 );
	check_transfer_status();
	print_normal_resp();
}	

static void auto_write_4()
{
	printf( "\nauto_write_4 : WRITE_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb801080c, 0x1 );	//   6 byte response
  //rtd_outl( 0xb801080c, 0x41 );	//   6 byte response
  
	rtd_outl( 0xb8010808, 0x2 ); // auto write3: 0x1, auto write4:0x2
	rtd_outl( 0xb8010808, 0x82 );
	check_transfer_status();
	print_normal_resp();
}	


static void cmd_6_write_162(unsigned int value )	// Value= 1, high speed,default = 0
{
	printf( "\ncmd6 : write byte\n" );
	rtd_outl( 0xb8010810, 0x46 );		//  transmission bit =  0x1 ;
	rtd_outl( 0xb8010814, 0x03 );		//[31:26] set 0, [25:24] access, =2b'11, Write byte
  rtd_outl(0xb8010818, 0xA2);	
  rtd_outl(0xb801081c, value);	// Value= 1, open hardware reset enable permanently
	rtd_outl( 0xb8010820, 0x00 );		//[7:3] set 0, [2:0] cmd set
	rtd_outl( 0xb801080c, 0x1 );		//  6 byte response
	rtd_outl( 0xb8010804, NO_DIV );		//  no diviede
	rtd_outl( 0xb8010808, 0x8 );
	rtd_outl( 0xb8010808, 0x88 );
	check_transfer_status();
	print_normal_resp();
	check_status();
}



static sram_read(unsigned int SRAM_Data)
{
	unsigned int i,SRAM_ADDR,BYTE_CNT;
	SRAM_ADDR = SD_SRAM_DATA;
	BYTE_CNT =  128;
	printf( "read sram\n" );
	for( i=0; i<BYTE_CNT; i++ ) {
		if( RReg( SD_SRAM_DATA ) != SRAM_Data ){
		break;
		}
		//printf( "SRAM_ADDR=0x%03x, Value=0x%08x\n",( SRAM_ADDR ),RReg( SD_SRAM_DATA ) );
		SRAM_ADDR =SRAM_ADDR+ 4;
	}
	if(i == BYTE_CNT)
	printf("\ncheck sram data ok, ByteCNT = %d\n",i);
	else
		{
		printf("\ncheck sram data fail, ByteCNT = %d\n",i);
		return FAILED;
	}
}


static void emmc_r_w_setting(UINT32 DDR_A, UINT32 DATA_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010840, DDR_A ); //DDR address: card to ddr
	rtd_outl( 0xb8010844, DDR_A ); //DDR address ddr to card
	rtd_outl( 0xb8010814, (DATA_A & 0xff000000)>>24 );
	rtd_outl( 0xb8010818, (DATA_A & 0x00ff0000)>>16 );
	rtd_outl( 0xb801081c, (DATA_A & 0x0000ff00)>>8 );
	rtd_outl( 0xb8010820, (DATA_A & 0x000000ff) );
	
	rtd_outl( 0xb8010804, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010824, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010828, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb801082c, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb8010830, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
 //printf( "\nemmc_r_w_setting:\n" );   
 //
 //printf( "REG ADDR:0xb8010840 = 0x%08x\n",rtd_inl( 0xb8010840 ) );
 //printf( "REG ADDR:0xb8010844 = 0x%08x\n",rtd_inl( 0xb8010844 ) );
 //printf( "REG ADDR:0xb8010814 = 0x%08x\n",rtd_inl( 0xb8010814 ) );
 //printf( "REG ADDR:0xb8010818 = 0x%08x\n",rtd_inl( 0xb8010818 ) );
 //printf( "REG ADDR:0xb801081c = 0x%08x\n",rtd_inl( 0xb801081c ) );
 //printf( "REG ADDR:0xb8010820 = 0x%08x\n",rtd_inl( 0xb8010820 ) );
 //printf( "REG ADDR:0xb8010804 = 0x%08x\n",rtd_inl( 0xb8010804 ) );
 //printf( "REG ADDR:0xb8010824 = 0x%08x\n",rtd_inl( 0xb8010824 ) ); 
 //printf( "REG ADDR:0xb8010828 = 0x%08x\n",rtd_inl( 0xb8010828 ) ); 
 //printf( "REG ADDR:0xb801082c = 0x%08x\n",rtd_inl( 0xb801082c ) ); 
 //printf( "REG ADDR:0xb8010830 = 0x%08x\n",rtd_inl( 0xb8010830 ) ); 
	
	}

static void emmc_r_w_cmd_setting(UINT32 DATA_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010814, (DATA_A & 0xff000000)>>24 );
	rtd_outl( 0xb8010818, (DATA_A & 0x00ff0000)>>16 );
	rtd_outl( 0xb801081c, (DATA_A & 0x0000ff00)>>8 );
	rtd_outl( 0xb8010820, (DATA_A & 0x000000ff) );
	
	rtd_outl( 0xb8010804, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010824, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010828, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb801082c, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb8010830, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
	//printf( "\nemmc_r_w_cmd_setting:\n" );   
	//
	//printf( "REG ADDR:0xb8010814 = 0x%08x\n",rtd_inl( 0xb8010814 ) );
	//printf( "REG ADDR:0xb8010818 = 0x%08x\n",rtd_inl( 0xb8010818 ) );
	//printf( "REG ADDR:0xb801081c = 0x%08x\n",rtd_inl( 0xb801081c ) );
	//printf( "REG ADDR:0xb8010820 = 0x%08x\n",rtd_inl( 0xb8010820 ) );
	//printf( "REG ADDR:0xb8010804 = 0x%08x\n",rtd_inl( 0xb8010804 ) );
	//printf( "REG ADDR:0xb8010824 = 0x%08x\n",rtd_inl( 0xb8010824 ) ); 
	//printf( "REG ADDR:0xb8010828 = 0x%08x\n",rtd_inl( 0xb8010828 ) ); 
	//printf( "REG ADDR:0xb801082c = 0x%08x\n",rtd_inl( 0xb801082c ) ); 
	//printf( "REG ADDR:0xb8010830 = 0x%08x\n",rtd_inl( 0xb8010830 ) ); 
	
	}


	
	
static void emmc_r_w_3_4_setting(UINT32 DDR_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010840, DDR_A ); //DDR address: card to ddr
	rtd_outl( 0xb8010844, DDR_A ); //DDR address ddr to card
		
	rtd_outl( 0xb8010804, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010810, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010814, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb8010818, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb801081c, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
	//printf( "\nemmc_r_w_3_4_setting:\n" );   
	//
	//printf( "REG ADDR:0xb8010840 = 0x%08x\n",rtd_inl( 0xb8010840 ) );
	//printf( "REG ADDR:0xb8010844 = 0x%08x\n",rtd_inl( 0xb8010844 ) );
	//printf( "REG ADDR:0xb8010810 = 0x%08x\n",rtd_inl( 0xb8010814 ) );	
	//printf( "REG ADDR:0xb8010814 = 0x%08x\n",rtd_inl( 0xb8010814 ) );
	//printf( "REG ADDR:0xb8010818 = 0x%08x\n",rtd_inl( 0xb8010818 ) );
	//printf( "REG ADDR:0xb801081c = 0x%08x\n",rtd_inl( 0xb801081c ) );

	//printf( "REG ADDR:0xb8010804 = 0x%08x\n",rtd_inl( 0xb8010804 ) );
	}
	
	
static void sram_mode_test()
{
	
	printf( "\n/*** emmc sram_mode_test ***|\n");
	
  ResetBit( SD_CP_CTRL,3 );
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  ddr_pattern_write(0x87654321,0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_1();
  
  SetBit( SD_CP_CTRL,3 );	//boot_from_cr = 1 
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_1();
  
  udelay(10);
  sram_read(0x87654321);
  
}
	
	


void emmc_cp_mode()
{
	DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	printf("\n/*** eMMC cp mode Test ***|\n");
	     
	printf("\neMMC cp mode enable\n");
	
	rtd_outl(0xb8015084, 0x8746bca3);                                                     
	rtd_outl(0xb8015088, 0xcdef89ab);                                                     
	rtd_outl(0xb801508c, 0x54369923);                                                     
	rtd_outl(0xb8015090, 0xcdefbcab);                                                     
	                                                                                                                                                                          
	rtd_outl(0xb8015094, 0x8746bca3);                                                     
	rtd_outl(0xb8015098, 0xcdef89ab);                                                     
	rtd_outl(0xb801509c, 0x54369923);                                                     
	rtd_outl(0xb80150a0, 0xcdefbcab);                                                     
	                                                                                      
	rtd_outl(0xb80150a4, 0x20); //  CP_NF_SET                                        
	rtd_outl(0xb8010330, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
	rtd_outl(0xb8010884, 0x1);  //CP mode enable    
                                          
	ddr_pattern_write(0x55555555,0xc2000000,128); 
	
	emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
	
	auto_write_1();	//write to eMMC
		
	ddr_pattern_erase(0xc2000000,128);
	
	rtd_outl(0xb8015084, 0x8746bca3);                                                     
	rtd_outl(0xb8015088, 0xcdef89ab);                                                     
	rtd_outl(0xb801508c, 0x54369923);                                                     
	rtd_outl(0xb8015090, 0xcdefbcab);                                                     
	                                                                                                                                                                          
	rtd_outl(0xb8015094, 0x8746bca3);                                                     
	rtd_outl(0xb8015098, 0xcdef89ab);                                                     
	rtd_outl(0xb801509c, 0x54369923);                                                     
	rtd_outl(0xb80150a0, 0xcdefbcab);                                                     
	                                                                                      
	rtd_outl(0xb80150a4, 0x20); //  CP_NF_SET                                         
	rtd_outl(0xb8010330, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
	rtd_outl(0xb8010884, 0x1);  //CP mode enable  

	emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
	
	auto_read_1();	//read from eMMC to DDR
	
	udelay(10);
	ddr_pattern_read(0xc2000000,128,0x55555555); //compare	 
	
//	rtd_outl(0xb8010884, 0x0);  //CP mode disable  
//	auto_read();	//read from eMMC to DDR
//	printf("0xb8010800=%x\n",RReg(0xb8010800));
//	ddr_pattern_read(0xc2000000,128); //compare
}

						
	
static setting_device_io_driver( unsigned int driver_type )  // Hspeed driver type 0 1 2 3
{

	switch ( driver_type ) {
		case 0:
			cmd_6_switch( 0x01 );
			printf( "Set driver_type = 0\n" );
			break;
		case 1:
			cmd_6_switch( 0x11 );
			printf( "Set driver_type = 1\n" );
			break;
		case 2:
			cmd_6_switch( 0x21 );
			printf( "Set driver_type = 2\n" );
			break;
		case 3:
			cmd_6_switch( 0x31 );
			printf( "Set driver_type = 3\n" );
			break;
		default:
			printf( "driver_type is invalid\n" );
			break;
	}

	cmd_8();
	printf( "driver_type = 0x%x\n",rtd_part_inl( 0xc00000b8,7,4 ) );

}

static void write_nblock(UINT32 nDATA_ADDR,UINT32 nBlock_Count)
{
  
  //printf( "\n/*** emmc write n block ***|\n");
  
  DDR_ADDR =  0x22000000;    
	//DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x2;         
	Byte_Count =  0x00000200;   
	//Block_Count = 0x00000200; 
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  //ddr_pattern_write(0xff00ff00,0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,nDATA_ADDR,BUS_WIDTH_HS,Byte_Count,nBlock_Count);     
  
  auto_write_1();
 } 
 
 
static void read_nblock(nDATA_ADDR,nBlock_Count)
{
  
  //printf( "\n/*** emmc read n block ***|\n");
  
  DDR_ADDR =  0x22000000;      
	//DATA_ADDR = 0x00002000;    

	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	//Block_Count = 0x00000400;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  //ddr_pattern_write(0xff00ff00,0xc2000000,128); 
 
  //ddr_pattern_erase(0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,nDATA_ADDR,BUS_WIDTH_HS,Byte_Count,nBlock_Count); 
  
  auto_read_1();
  
 
  //ddr_pattern_read(0xc2000000,128,0xff00ff00);
}
	
static void auto_r_w_1_test( )
{
  
  printf( "\n/*** emmc auto_r_w_1_test ***|\n");
  
  DDR_ADDR =  0xa2000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  ddr_pattern_write(0x12345678,0xa2000000,128);
  //ddr_pattern_write(0xff00ff00,0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_1();
  
  ddr_pattern_erase(0xa2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_1();
  
  udelay(100);
  ddr_pattern_read(0xa2000000,128,0x12345678);
}


static void auto_r_w_2_test( )
{
  
  printf( "\n/*** emmc auto_r_w_2_test ***|\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0x55555555,0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_2();
  cmd_12();
  
  ddr_pattern_erase(0xc2000000,128);
  
  emmc_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_2();
  cmd_12();
 
  udelay(100);
  ddr_pattern_read(0xc2000000,128,0x55555555);
}

static void auto_r_w_3_test( )
{
  
  printf( "\n/*** emmc auto_r_w_3_test ***|\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0x10101010,0xc2000000,128);
  
  emmc_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  cmd_25();
  
  emmc_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_write_3();
  cmd_12();
  
  ddr_pattern_erase(0xc2000000,128);
  
  emmc_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  
  cmd_18();
  
  emmc_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_read_3();
  cmd_12();
 
  udelay(100);
  ddr_pattern_read(0xc2000000,128,0x10101010);
}


static void auto_r_w_4_test( )
{
  
  printf( "\n/*** emmc auto_r_w_4_test ***|\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0xffffffff,0xc2000000,128);
  
  emmc_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  
  cmd_25();
  
  emmc_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_write_4();
  
  ddr_pattern_erase(0xc2000000,128);

  emmc_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  

  cmd_18();

  emmc_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);

  auto_read_4();
  
  udelay(100);
  ddr_pattern_read(0xc2000000,128,0xffffffff);
}



int emmc_init()
{
	unsigned int pwr_up_status,i;
	i=0;
	BUS_WIDTH = 8;		//set 1,4,8  //cck 8-->4
	HS_TIMMING = 0x01;		//0:, 1:high speed, 2:HS200
	SET_BLOCKLEN = 0x02;	//
	RCA_H = 0x00;
	RCA_L = 0x20;
  emmc_freq = 0x02;  // 33.75MHz 
  
	//setting eMMC source clock frequency
	emmc_change_freq();   

	printf( "\n****** Card identification mode *******\n" );
	
	cmd_0();
	
	while( 1 ) {
		pwr_up_status = cmd_1();
		if( pwr_up_status == 1 ) {
		printf("\n ****** Read transmission done ******\n");
			break;
		}
		mdelay( 1 );
		i++;
		if( i == 50 ) {
			printf( "cmd1 fail\n" );
			break;
		}
	}

	cmd_2();     //send_cid 
	cmd_3();     // set RCA 

	printf( "\n****** Data transfer mode *******\n" );
	
	cmd_9();		//send_csd
	cmd_10();	  //send_cid same as cmd_2
	

	
	cmd_7();		//select card
	cmd_7_0();		//deselect card with RCA 00
  cmd_7();		//select card
  
  setting_bus_width( BUS_WIDTH );   // set 1 , 4  or 8 bit
  setting_HS_Mode( HS_TIMMING );     // set high speed = 1   

  cmd_13();
	cmd_16();		//SET_BLOCKLEN
}


//static unsigned int y = 1U;
//
//unsigned int rand_r(unsigned int *seedp)
//{
//	*seedp ^= (*seedp << 13);
//	*seedp ^= (*seedp >> 17);
//	*seedp ^= (*seedp << 5);
//
//	return *seedp;
//}
//
//unsigned int rand(void)
//{
//	 return rand_r(&y);
//}
//
//void srand(unsigned int seed)
//{
//	y = seed;
//}
//
//
//void sys_get_time1(UINT32* time)
//{
//        *time = RReg(0xb801b628);//timer2
//}
//
//
//static void emcu_init( void )
//{
//	//printk( "*** init_emcu ***\n" );
//	rtd_maskl( 0xB8060034, 0xFFFFFDFF, 0x00000000 ); //bit9 : RSTN_EMCU_CORE = 0
//	mdelay( 1 );
//	rtd_maskl( 0xB8060044, 0xFFFFFDFF, 0x00000000 ); //bit9 : CLKEN_EMCU_CORE = 0
//	mdelay( 1 );
//	rtd_maskl( 0xB8060034, 0xFFFFFBFF, 0x00000000 ); //bit10 : RSTN_EMCU_TOP = 0
//	mdelay( 1 );
//	rtd_maskl( 0xB8060034, 0xFFFFFBFF, 0x00000400 ); //bit10 : RSTN_EMCU_TOP =1
//	mdelay( 1 );
//	rtd_maskl( 0xB8060044, 0xFFFFFDFF, 0x00000200 ); //bit9 : CLKEN_EMCU_CORE = 1
//}
//static void load_emcu_code( void )
//{
//	printf( "\nload emcu code\n" );
//
//	int i;
//	rtd_maskl( 0xB8060434, 0xFFFF7FFF, 0x00008000 );
//	rtd_outl( 0xB8060430,0x00000001 );  //program enable
//
//	for( i=0; i<ecpu_stb_ap_size; i++ ) {
//		rtd_outl( 0xB8060438,ecpu_stb_ap[i] );
//	}
//	printf( "\nload emcu code --> done\n" );
//
//}
//
//static void suspend_to_ram_setting()
//{
//	printf( "\n Enter Self-refresh\n" );
//	rtd_outl( 0xb8008828,0x00000008 );
//}
//
//static void emcu_run()
//{
//	rtd_maskl( 0xB8060430, 0xFFFFFFFE, 0x00000000 ); //program disable
////	rtd_maskl( 0xB8060044, 0xFFFFFDFF, 0x00000200 );
//	rtd_maskl( 0xB8060034, 0xFFFFFDFF, 0x00000200 ); //bit9 : RSTN_EMCU_CORE = 1
////	rtd_maskl(0xb8000008, 0xfffffffe, 0x00000000 );  //SB2_RSTN=0
////	rtd_maskl(0xb8000008, 0xfffffffe, 0x00000001 );  //SB2_RSTN=1
////	printf("\n\nreset SB2\n\n");
//}
//
//
////static void emcu_on_off()
////{
//	//printf( "\ninit emcu\n" );
//	//emcu_init();
//	//load_emcu_code();
////	suspend_to_ram_setting();
//	//emcu_run();
//	//printf( "\n*** emcu running ***\n" );
//
////}
//
//static void QC_Verifier_Standby()
//{
//	printf( "\ninit emcu\n" );
//	emcu_init();
//	load_emcu_code();
////	suspend_to_ram_setting();
//	emcu_run();
//	printf( "\n*** emcu running ***\n" );
//
//}
//
//
//void EMMC_TEST_NUM(unsigned int emmc_test_num)
//{
//	printf("\ntest_num=%d\n\n", emmc_test_num);
//	//QC_Verifier_Standby();
//		//you can save emmc_test_num parameter and call QC_Verifier_EMMC()to start test
//  WReg(0xb8060120, emmc_test_num);	
//  printf("save test loop value is: %d\n",RReg(0xb8060120));
//  QC_Verifier_EMMC();
//  
//}

int QC_Verifier_EMMC(void)   
{
	
	 int i =0;
	INDEX = 0;
	
	DDR_ADDR = 0xa2000000;      
	DATA_ADDR = 0x00010000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count = 0x00000200;    
	Block_Count = 0x00000001;    
	
	emmc_pin_mux_setting();
	
  ResetBit( 0xb8000004,11 ); //rst enable
  ResetBit( 0xb800000c,24 ); //clk enable
  udelay( 5 );
  SetBit( 0xb8000004,11 );
  SetBit( 0xb800000c,24 );
		
  emmc_init();

  auto_r_w_1_test();	
  
 // printf( "INDEX = %d\n",INDEX );
  

	if(INDEX == -1) return INDEX;
 	
 //return INDEX;	//SUCCESS=0, FAILED =-1
 return 0;
	}























