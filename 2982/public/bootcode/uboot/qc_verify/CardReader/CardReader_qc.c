//#include <qc_verify_common.h>
//#include <common.h>
//#include <command.h>
//#include <linux/compiler.h>
//#include <rbus/crt_reg.h>
//#include <asm/arch/io.h>
#include <qc_verify_common.h>

#define	SETBIT(x,n)		x = x | (1<<n)
#define	CLRBIT(x,n)		x = x & ~(1<<n)
#define SetBit(addr, nbit)	  	*((volatile unsigned int *) (addr-0xa0000000)) |= 1<<nbit
#define ResetBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) &= ~(1<<nbit)
#define ToggleBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) ^= 1<<nbit
#define WReg(addr, data)		*((volatile unsigned int *) (addr-0xa0000000)) = data
#define RReg(addr) 		    	*((volatile unsigned int *) (addr-0xa0000000))

#define		SD_STAT			0xb8010c00 
#define		SD_CMD0			0xb8010c10
#define		SD_CMD1			0xb8010c14
#define		SD_CMD2			0xb8010c18
#define		SD_CMD3			0xb8010c1c
#define		SD_CMD4			0xb8010c20

#define		SD_RSP0			0xb8010c10
#define		SD_RSP1			0xb8010c14
#define		SD_RSP2			0xb8010c18
#define		SD_RSP3			0xb8010c1c
#define		SD_RSP4			0xb8010c20

#define		SD_EXT_RSP0		0xb8010c88
#define		SD_EXT_RSP1		0xb8010c8c
#define		SD_EXT_RSP2		0xb8010c90
#define		SD_EXT_RSP3		0xb8010c94
#define		SD_EXT_RSP4		0xb8010c98
#define		SD_EXT_RSP5		0xb8010c9c
#define		SD_EXT_RSP6		0xb8010ca0
#define		SD_EXT_RSP7		0xb8010ca4
#define		SD_EXT_RSP8		0xb8010ca8
#define		SD_EXT_RSP9		0xb8010cac
#define		SD_EXT_RSP10		0xb8010cb0
#define		SD_EXT_RSP11		0xb8010cb4
#define		SD_EXT_RSP12		0xb8010cb8
#define		SD_EXT_RSP13		0xb8010cbc
#define		SD_EXT_RSP14		0xb8010cc0


#define		SD_ARB_STS			0xb8010cc4
#define		SD_SRAM_DATA		0xb8010cc8

#define		SD_CP_CTRL			0xb8010c84
#define		Dbus_option     0xb8010c4c

#define		SD_RSTN		0xb8000c14
#define		SD_CLK		0xb8000c10
#define		SD_CMD		0xb8000c04
#define		SD_D0			0xb8000c10
#define		SD_D1			0xb8000c18
#define		SD_D2			0xb8000c14
#define		SD_D3			0xb8000c18
#define		SD_D4			0xb8000c10
#define		SD_D5			0xb8000c14
#define		SD_D6			0xb8000c10
#define		SD_D7			0xb8000c14
#define		SD_Freq	  0xb8000204

//#define		DIV				  0x40        //DIV 256
#define		DIV				  0x20        //DIV 128
#define		NO_DIV			0x0
#define		timeout     50000
#define		busy        50000

static unsigned int transfer_enable = 0;
static unsigned int BUS_WIDTH = 0;
static unsigned int HS_TIMMING = 0;
static unsigned int RCA_H = 0;
static unsigned int RCA_L = 0;
static unsigned int SET_BLOCKLEN = 0;

static unsigned int BUS_WIDTH_HS = 0;
static unsigned int DDR_ADDR = 0;
static unsigned int DATA_ADDR = 0;
static unsigned int Byte_Count = 0;
static unsigned int BYTE_CNT = 128;

static unsigned int Block_Count = 0;
static unsigned int SD_freq = 0;
static unsigned int i = 0, j = 0,m = 0;


static int INDEX = 0;

//void rtd_part_outl( unsigned int addr, unsigned int B, unsigned int C, unsigned int D )
//{
//	unsigned int X,A,value;
//	X=( 1<<( B-C+1 ) )-1;
//	A=RReg( addr );
//	value = A&( ~( X<<C ) )|( D<<C );
//	WReg( addr,value );
////    return ((A&(~(X<<C)))|(D<<C));
//}
//
//unsigned int rtd_part_inl( unsigned int addr, unsigned int B, unsigned int C )
//{
//	unsigned int X,A;
//	X=( 1<<( B-C+1 ) )-1;
//	A=RReg( addr );
//	return ( A>>C )&X;
//}
//
//unsigned int part_value( unsigned int value, unsigned int B, unsigned int C )
//{
//	unsigned int X,A;
//	X=( 1<<( B-C+1 ) )-1;
//	A=value;
//	return ( A>>C )&X;
//}




static void SD_pin_mux_setting()
{
//-------- Sirius Cardreader Pinmux Setting for BGA --------------------------------------  
   
rtd_part_outl(0xb8000910,30,28,0x5);  //CMD GP99
rtd_part_outl(0xb8000910,26,23,0x8);  //WP GP100
rtd_part_outl(0xb8000910,21,19,0x6);  //CD GP101
rtd_part_outl(0xb8000910,17,15,0x4);  //D0 GP102
rtd_part_outl(0xb8000910,13,11,0x4);  //D1 GP103
rtd_part_outl(0xb8000910,9,7,0x5);  //D2 GP102
rtd_part_outl(0xb8000910,5,3,0x5);  //D3 GP105

rtd_part_outl(0xb8000864,31,27,0x5);  //CLK GP98
rtd_part_outl(0xb8000864,22,18,0x5);  //CMD GP99
rtd_part_outl(0xb8000864,13,9,0x5);  //WP GP100
rtd_part_outl(0xb8000868,31,27,0x5);  //CD GP101
rtd_part_outl(0xb8000868,22,18,0x5);  //D0 GP102
rtd_part_outl(0xb8000868,13,9,0x5);  //D1 GP103
rtd_part_outl(0xb800086c,31,27,0x5);  //D2 GP102
rtd_part_outl(0xb800086c,22,18,0x5);  //D3 GP105
rtd_part_outl(0xb8000878,31,27,0x1f);  //SD Power enable GPIO171 

	
	printf( "check pinmux reg value.\n");
	printf( "rtd_inl(0xb8000910) = 0x%08x\n", RReg( 0xb8000910 ) );
	printf( "rtd_inl(0xb8000864) = 0x%08x\n", RReg( 0xb8000864 ) );
	printf( "rtd_inl(0xb8000868) = 0x%08x\n", RReg( 0xb8000868 ) );
	printf( "rtd_inl(0xb800086c) = 0x%08x\n", RReg( 0xb800086c ) );
	printf( "rtd_inl(0xb8000878) = 0x%08x\n", RReg( 0xb8000878 ) );
}


static void SD_PWR_EN()
{
//rtd_maskl(0xb8000878,0x07ffffff,0xf8000000); //pinshare for SD Power enable GPIO171
rtd_part_outl(0xb8000878,31,27,0x1f);  //SD Power enable GPIO171 
rtd_part_outl(0xb801B114,11,11,0x1);   // set output
rtd_part_outl(0xb801B130,11,11,0x1);   // set output high

printf( "open sd power enable.\n");
	 

}



static void SD_change_freq()
{
		rtd_part_outl(0xb8000040,31,30,0x2);   // SD/SD clock source selection    10: from rbus_clk    11: from dbus_clk
		//rtd_part_outl(0xb8000040,31,30,0x3);   // SD/SD clock source selection    10: from rbus_clk    11: from dbus_clk	
		
			rtd_part_outl(0xb8000040,3,0,SD_freq);    // SD freq divide select,   write_en=1 
 		//rtd_part_outl(0xb8000040,3,0,0x8);    // SD freq divide select: 0: div2    50M       115M    
 		//rtd_part_outl(0xb8000040,3,0,0x9);    // SD freq divide select: 1: div3  33.3M     73.5M
		//rtd_part_outl(0xb8000040,3,0,0xa);    // SD freq divide select: 2: div4  25M       56.2M    
		//rtd_part_outl(0xb8000040,3,0,0xb);    // SD freq divide select: 3: div5  20M       44.2M
		//rtd_part_outl(0xb8000040,3,0,0xc);    // SD freq divide select: 4: div6  16.7M     37.2M
		//rtd_part_outl(0xb8000040,3,0,0xd);    // SD freq divide select: 5: div8  12.5M     27.9M
		//rtd_part_outl(0xb8000040,3,0,0xe);    // SD freq divide select: 6: div10 10M       22.8M
	
	printf( "change freq reg value.\n");
	printf( "rtd_inl(0xb8000040) = 0x%08x\n", RReg( 0xb8000040 ) );
}


static void ddr_pattern_write( unsigned int PATTERN, unsigned int DDR_ADDR, unsigned int BYTE_CNT )
{
	printf( "\nwrite ddr \n");
	unsigned int i,DDR_VAL;
	DDR_VAL	 =	PATTERN;
	//DDR_ADDR = 	0xA2000000; //addr=0xc000_0000-0xa000_0000=0x2000_0000
	//BYTE_CNT =  128;
	printf( "write ddr from addr = 0x%08x\n",( DDR_ADDR) );
	for( i=0; i < BYTE_CNT; i++ ) {
		WReg( DDR_ADDR , DDR_VAL );
		DDR_ADDR = DDR_ADDR + 4;
	}
}

static void ddr_pattern_erase( unsigned int DDR_ADDR, unsigned int BYTE_CNT )
{
	printf( "\nerase ddr \n");
	unsigned int i, DDR_VAL;
	DDR_VAL	 =	0x0;
	//DDR_ADDR = 	0xA2000000;
	//BYTE_CNT =  128;
	printf( "erase ddr from addr = 0x%08x\n",( DDR_ADDR-0xa0000000 ) );
	for( i=0; i < BYTE_CNT; i++ ) {
		WReg( DDR_ADDR , DDR_VAL );
		DDR_ADDR = DDR_ADDR + 4;
	}
}

static void ddr_pattern_read( unsigned int DDR_ADDR, unsigned int BYTE_CNT,unsigned int PATTERN )
{
	printf( "\nread ddr \n");
	unsigned int i;
	//DDR_ADDR = 	0xA2000000;
	//BYTE_CNT =  128;
	//printf( "read ddr\n" );
	for( i=0; i < BYTE_CNT; i++ ) 
	{
		
		if( RReg( DDR_ADDR ) != PATTERN){
			INDEX = -1;
			//break;
		}
		//printf( "DDR_ADDR=0x%08x, Value=0x%08x\n",( DDR_ADDR-0xa0000000),RReg( DDR_ADDR ) );
		DDR_ADDR =DDR_ADDR+ 4;
	}
	
	if(i == BYTE_CNT)
	printf("\ncheck ddr pattern ok, ByteCNT = %d\n",i);
	else
		return -1;
}


static void print_normal_resp()                                         
{                                                                      
j = 0;
for(i = 0 ; i < 5; i++)
	{ 	
	// printf("SD_resp[%d]: rtd(0x%08x) = 0x%08x\n",i,( 0xb8010c10 + j),RReg( 0xb8010c10 + j));
   j += 4; 
  
  }                                                                   
  //printf("tansfer code is: rtd(0xb8010c08) = 0x%08x\n",RReg( 0xb8010c08));                                                                  
}

static void print_long_resp()                                         
{                                                                      
j = 0;
for(i = 0 ; i < 15; i++)  //Total 17Byte  0x1801_0888~0x1801_08C0
	{ 	
	 //printf("SD_lresp[%d]: rtd(0x%08x) = 0x%08x\n",i,( 0xb8010c88 + j),RReg( 0xb8010c88 + j));
   j += 4; 
  
  }                                                                   
                                                                     
}


static void check_transfer(unsigned int cmd_code)   
//cmd_code:  68 SEND_CMD_GET_RSP,60 NORMAL_WRITE,61 AUTO_WRITE3,62 AUTO_WRITE4,65 AUTO_READ3
//           66 AUTO_READ4,69 AUTO_WRITE1,6a AUTO_WRITE2,6c NORMAL_READ1,6d AUTO_READ1,6e AUTO_READ2

{
   for(i = 0; i < timeout; i++)
   {
  	transfer_enable = rtd_inl(0xb8010c08); 
  	
  	if (transfer_enable == cmd_code)
  		{
  		printf("timeout break at number %d \n", i);
  	  break;
  	  }		
   }
  	if (transfer_enable == cmd_code)
  		printf( "SD CMD PASS,cmd code = %d\n",transfer_enable);
  		else
		  {
		  printf( "SD CMD TIMEOUT,cmd code = %d\n",transfer_enable);
		  return FAILED; 
	    }
}  	


static int check_transfer_status()
{
	int i;
	i=0;
	while( 1 ) {
		if( rtd_part_inl( 0xb8010c08,6,6 ) == 1 ) {
			//printf( "transfer done" );

			if( rtd_part_inl( 0xb8010c08,4,4 ) == 1 ) {
				if( rtd_part_inl( SD_STAT,7,7 )==1 )
					printf( " -->CRC7 Error\n" );
				if( rtd_part_inl( SD_STAT,6,6 )==1 )
					printf( " -->CRC16 Error\n" );
				if( rtd_part_inl( SD_STAT,5,5 )==1 )
					printf( " -->Write Error\n" );
				printf( " -->DAT0 = %x\n",rtd_part_inl( SD_STAT,1,1 ) );
				INDEX = -1;
			} else {
				printf( " -->Correct\n" );
				//return 0;
			}
			break;
		}
		mdelay( 10 );
		i++;
		if( i == 500 ) {
			printf( "transfer didn't complete, End bit = 0\n" );

			break;
		}
	} 
	 printf("tansfer code is: rtd(0xb8010c08) = 0x%08x\n",RReg( 0xb8010c08));  
}
	
static void check_cid()
{
	unsigned int mid_num;
	printf( "CID register value\n" );
	printf( "CID[127:120]=0x%02x\n",RReg( SD_EXT_RSP0 ) );
	printf( "CID[119:112]=0x%02x\n",RReg( SD_EXT_RSP1 ) );
	printf( "CID[111:104]=0x%02x\n",RReg( SD_EXT_RSP2 ) );
	printf( "CID[103: 96]=0x%02x\n",RReg( SD_EXT_RSP3 ) );
	printf( "CID[ 95: 88]=0x%02x\n",RReg( SD_EXT_RSP4 ) );
	printf( "CID[ 87: 80]=0x%02x\n",RReg( SD_EXT_RSP5 ) );
	printf( "CID[ 79: 72]=0x%02x\n",RReg( SD_EXT_RSP6 ) );
	printf( "CID[ 71: 64]=0x%02x\n",RReg( SD_EXT_RSP7 ) );
	printf( "CID[ 63: 56]=0x%02x\n",RReg( SD_EXT_RSP8 ) );
	printf( "CID[ 55: 48]=0x%02x\n",RReg( SD_EXT_RSP9 ) );
	printf( "CID[ 47: 40]=0x%02x\n",RReg( SD_EXT_RSP10 ) );
	printf( "CID[ 39: 32]=0x%02x\n",RReg( SD_EXT_RSP11 ) );
	printf( "CID[ 31: 24]=0x%02x\n",RReg( SD_EXT_RSP12 ) );
	printf( "CID[ 23: 16]=0x%02x\n",RReg( SD_EXT_RSP13 ) );
	printf( "CID[ 15:  8]=0x%02x\n",RReg( SD_EXT_RSP14 ) );


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
printf( "CSD register\n" );
	printf( "CSD[127:120]=0x%02x\n",RReg( SD_EXT_RSP0 ) );
	printf( "CSD[119:112]=0x%02x\n",RReg( SD_EXT_RSP1 ) );
	printf( "CSD[111:104]=0x%02x\n",RReg( SD_EXT_RSP2 ) );
	printf( "CSD[103: 96]=0x%02x\n",RReg( SD_EXT_RSP3 ) );
	printf( "CSD[ 95: 88]=0x%02x\n",RReg( SD_EXT_RSP4 ) );
	printf( "CSD[ 87: 80]=0x%02x\n",RReg( SD_EXT_RSP5 ) );
	printf( "CSD[ 79: 72]=0x%02x\n",RReg( SD_EXT_RSP6 ) );
	printf( "CSD[ 71: 64]=0x%02x\n",RReg( SD_EXT_RSP7 ) );
	printf( "CSD[ 63: 56]=0x%02x\n",RReg( SD_EXT_RSP8 ) );
	printf( "CSD[ 55: 48]=0x%02x\n",RReg( SD_EXT_RSP9 ) );
	printf( "CSD[ 47: 40]=0x%02x\n",RReg( SD_EXT_RSP10 ) );
	printf( "CSD[ 39: 32]=0x%02x\n",RReg( SD_EXT_RSP11 ) );
	printf( "CSD[ 31: 24]=0x%02x\n",RReg( SD_EXT_RSP12 ) );
	printf( "CSD[ 23: 16]=0x%02x\n",RReg( SD_EXT_RSP13 ) );
	printf( "CSD[ 15:  8]=0x%02x\n",RReg( SD_EXT_RSP14 ) );
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
	rtd_outl( 0xb8010c10, 0x40 ); //  transmission bit =  0x1 ;
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x04 );	//  no response and  no crc check
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}


static void cmd_8()
{
	printf( "\ncmd8 : check voltage range\n" );
	rtd_outl( 0xb8010c10, 0x48 ); //  transmission bit =  0x1 ;
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x01 );
	rtd_outl( 0xb8010c20, 0xaa );
	rtd_outl( 0xb8010c0c, 0x01 );	//  
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}


static void cmd_55()
{
	printf( "\ncmd55 : send cmd55 before acmd\n" );
	rtd_outl( 0xb8010c10, 0x77 ); //  transmission bit =  0x1 ;
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x01 );	//  
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}


static void cmd_55_RCA()
{
	printf( "\ncmd55 : send cmd55 before acmd\n" );
	rtd_outl( 0xb8010c10, 0x77 ); //  transmission bit =  0x1 ;
	rtd_outl( 0xb8010c14, RCA_H );
	rtd_outl( 0xb8010c18, RCA_L );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x01 );	//  
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}

static unsigned int acmd_41()
{
	printf( "\nacmd41: SEND_OP_COND\n" );

	//ask the card to send its OCR contents
	rtd_outl( 0xb8010c10, 0x69 );		//  transmission bit =  0x1 ;
	rtd_outl( 0xb8010c14, 0x40 );		// [31]: power up status, [30:29] access mode:2'b10 sector mode, [28:24] reserved
	rtd_outl( 0xb8010c18, 0x3c );		// [23:15]  2.7~3.6V
	rtd_outl( 0xb8010c1c, 0x00 ); 		// [14:8] 2.0~2.6V [7] 1.70~1.95V
	rtd_outl( 0xb8010c20, 0x00 );
	rtd_outl( 0xb8010c0c, 0x5 );		//  check crc7 off  6 byte response
	rtd_outl( 0xb8010c04, DIV );		//diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_OCR();
	return ( rtd_part_inl( SD_RSP1,7,7 ) );  // C0     [7]: busy bit  [6:5] sector/byte mode
}

static void cmd_2()
{
	printf( "\ncmd2 : ALL_SEND_CID\n" );
	//ask the card to send its CID contents
	rtd_outl( 0xb8010c10, 0x42 ); //  transmission bit =  0x1 ;  command = 0x2
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_long_resp();
	//check_cid();

}

static void cmd_3()
{
//	int ret;
	printf( "\ncmd3 : SET_RELATIVE_ADDR\n" );
	rtd_outl( 0xb8010c10, 0x43 ); //  transmission bit =  0x1 ;  command = 0x3
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x10 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x1 );	//  6 byte response and CRC check
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	printf( "Assign SD address: RCA_H=0x%02x, RCA_L=0x%02x\n",RCA_H,RCA_L );
}

static void acmd_6(UINT32 value )    //value, 0:1-bit, 1:4-bit 2:8-bit
{
	printf( "\ncmd6 : SWITCH\n" );
	//printf("change bus_width = %d-bit\n",bus_width);

	rtd_outl( 0xb8010c10, 0x46 );		 
	rtd_outl( 0xb8010c14, 0x0 );		 
	rtd_outl( 0xb8010c18, 0x0 );		 
	rtd_outl( 0xb8010c1c, 0x0 );		//[15:8] value, 0:1-bit, 1:4-bit 2:8-bit
	rtd_outl( 0xb8010c20, value );		 
	rtd_outl( 0xb8010c0c, 0x1 );		 
	rtd_outl( 0xb8010c04, DIV );		 
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}


static setting_bus_width( UINT32 bus_width ) 
{
	
	switch ( bus_width ) {
		case 1:
			cmd_55_RCA();
			BUS_WIDTH = 0x1;
			acmd_6(BUS_WIDTH );
			printf( "Set bus width = 1-bit\n" );
			break;
		case 4:
			cmd_55_RCA();
			BUS_WIDTH = 0x2;
			acmd_6(BUS_WIDTH );
			printf( "Set bus width = 4-bit\n" );
			break;
		default:
			printf( "Bus Width setting is invalid\n" );
			break;
	}
}


// HS_TIMING  [185] [7:4] Selected Driver Strength  ,[3:0] Hspeed mode

static setting_HS_Mode()   // Value= 1, high speed,default = 0, backwards compatibility interface timming
{                                               // Value= 2, HS200
rtd_outl(0xb8010c40, 0x22000000); //DDR address
rtd_outl(0xb8010c44, 0x22000000); //DDR address
rtd_outl(0xb8010c10, 0x46);		//A0
//rtd_outl(0xb8010c14, 0x0);		//A1, [31:24], 0x80:switch function, 0x0:check function
rtd_outl(0xb8010c14, 0x80);		//A1, [31:24], 0x80:switch function, 0x0:check function
rtd_outl(0xb8010c18, 0xff);		//A2, [23:16]
rtd_outl(0xb8010c1c, 0xff);		//A3, [15:8]
rtd_outl(0xb8010c20, 0xf1);		//A4, [7:0]    high speed
rtd_outl(0xb8010c0c, 0x41);	//   6 byte response
rtd_outl(0xb8010c04, 0x0);	//  no diviede ; 1-bit
//rtd_outl(0xb8010c04, 0x1);	//  no diviede  ; 4 -bit   
//rtd_outl(0xb8010c04, 0x11);	//  no diviede  ; 4 -bit
//rtd_outl(0xb8010c04, 0x2);	//  no diviede  ; 8 -bit
rtd_outl(0xb8010c24, 0x0);	// byte count [7:0]
rtd_outl(0xb8010c28, 0x2);	// byte count [10:8]
rtd_outl(0xb8010c2c, 0x01);	// block count [7:0]
rtd_outl(0xb8010c30, 0x0);	// block count [11:8]
rtd_outl(0xb8010c08, 0xc);
rtd_outl(0xb8010c08, 0x8c);
rtd_inl(0xb8010c08);
rtd_inl(0xb8010c08);
rtd_inl(0xb8010c08);
rtd_inl(0xb8010c08);
rtd_inl(0xb8010c08);
rtd_inl(0xb8010c10);
rtd_inl(0xb8010c14);
rtd_inl(0xb8010c18);
rtd_inl(0xb8010c1c);
rtd_inl(0xb8010c20);

	check_transfer_status();
	print_normal_resp();
	//printf( "\n\nExtended CSD Value\n" );
	
	//ddr_pattern_read
	
	//unsigned int i;
	DDR_ADDR = 	0xc2000000;
	//BYTE_CNT =  128;
	//printf( "read ddr\n" );
	
	for( i=0; i < 128; i++ ) {
		
		//printf( "DDR_ADDR = 0x%08x, Value = 0x%08x\n",( DDR_ADDR - 0xa0000000 ), RReg( DDR_ADDR ) );
		
		DDR_ADDR =DDR_ADDR+ 4;
	}
	


}




static void cmd_7()
{
	printf( "\ncmd7 : SELECT/DESELECT_CARD  RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	rtd_outl( 0xb8010c10, 0x47 ); 	//  transmission bit =  0x1 ;  command = 0x7
	rtd_outl( 0xb8010c14, RCA_H );
	rtd_outl( 0xb8010c18, RCA_L );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x1 );	//  6 byte response and CRC check
	rtd_outl( 0xb8010c04, NO_DIV );	//  divide  256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_7_0()
{
	printf( "\ncmd7 RCA_H=%x, RCA_L=%x\n",0,0 );
	rtd_outl( 0xb8010c10, 0x47 ); 	//  transmission bit =  0x1 ;  command = 0x7
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x0 );		// need no response
	rtd_outl( 0xb8010c04, DIV );	//  divide  256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_9()
{
	printf( "\ncmd9 : SEND_CSD RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	rtd_outl( 0xb8010c10, 0x49 ); //  transmission bit =  0x1 ;  command = 0x9
	rtd_outl( 0xb8010c14, RCA_H );
	rtd_outl( 0xb8010c18, RCA_L );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010c04, DIV );	//  diviede 256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_long_resp();
	//check_csd();
}

static void cmd_10()
{
	printf( "\ncmd10 : SEND_CID RCA_H=%x, RCA_L=%x\n",RCA_H,RCA_L );
	//ask the card to send its CID contents
	rtd_outl( 0xb8010c10, 0x4A ); //  transmission bit =  0x1 ;  command = 0xA
	rtd_outl( 0xb8010c14, RCA_H );
	rtd_outl( 0xb8010c18, RCA_L );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x2 );	//  17 byte response and CRC check
	rtd_outl( 0xb8010c04, DIV );	//   diviede_256
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_long_resp();
	//check_cid();

}


static void cmd_12()
{
	printf( "\ncmd12 : STOP_TRANSMISSION\n" );
	rtd_outl( 0xb8010c10, 0x4C );
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, 0x0 );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c24, 0x5 );
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 ); 	//1000 command response
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_13()
{
	printf( "\ncmd13 : SEND_STATUS\n" );
	rtd_outl( 0xb8010c10, 0x4d );		//transmission bit =  0x1 ;  command = 0xd
	rtd_outl( 0xb8010c14, RCA_H );		//[31:24] RCA
	rtd_outl( 0xb8010c18, RCA_L );		//[23:16]RCA
	rtd_outl( 0xb8010c1c, 0x0 );  		//stuff bit
	rtd_outl( 0xb8010c20, 0x0 );		//stuff bit
	rtd_outl( 0xb8010c0c, 0x1 );		//  6 byte response and CRC check
	rtd_outl( 0xb8010c08, 0x8 );
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_16()
{
	printf( "\ncmd16 : SET_BLOCKLEN\n" );

	rtd_outl( 0xb8010c10, 0x50 );		//  transmission bit =  0x1 ;  command = 0x10
	rtd_outl( 0xb8010c14, 0x0 );
	rtd_outl( 0xb8010c18, 0x0 );
	rtd_outl( 0xb8010c1c, SET_BLOCKLEN );
	rtd_outl( 0xb8010c20, 0x0 );
	rtd_outl( 0xb8010c0c, 0x1 );		//  6 byte response and CRC check
	rtd_outl( 0xb8010c04, 0x1 );	//  no divide
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
	//check_status();
}

static void cmd_18()
{
	printf( "\ncmd18 : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010c10, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010c08, 0x8 ); // normal cmd
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}


static void cmd_25()
{
	printf( "\ncmd25 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010c10, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response


	rtd_outl( 0xb8010c08, 0x8 ); // normal cmd
	rtd_outl( 0xb8010c08, 0x88 );
	check_transfer_status();
	print_normal_resp();
}			



static void auto_read_1()
{
	printf( "\nauto_read_1 : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010c10, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010c08, 0xd ); // auto read1:0xd, auto read2:0xe
	rtd_outl( 0xb8010c08, 0x8d );
	//check_transfer_status();
	for(m=0;m<busy;m++)
{
	//mdelay(1);
	check_transfer_status(); 

 	if( rtd_part_inl( 0xb8010c08,6,6 ) == 1 ) 
		break;
	}
	print_normal_resp();
}


static void auto_read_2()
{
	printf( "\nauto_read_2() : READ_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010c10, 0x52 ); //  transmission bit ,  0x12 ;
	
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010c08, 0xe ); // auto read1:0xd, auto read2:0xe
	rtd_outl( 0xb8010c08, 0x8e );
	check_transfer_status();
	print_normal_resp();
}

static void auto_read_3()
{
	printf( "\nauto_read_3 : READ_MULTIPLE_BLOCK\n" );
	
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010c08, 0x5 ); // auto read3:0x5, auto read4:0x6
	rtd_outl( 0xb8010c08, 0x85 );
	check_transfer_status();
	print_normal_resp();
}

static void auto_read_4()
{
	printf( "\nauto_read_4 : READ_MULTIPLE_BLOCK\n" );
	
	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response
 
	rtd_outl( 0xb8010c08, 0x6 ); // auto read3:0x5, auto read4:0x6
	rtd_outl( 0xb8010c08, 0x86 );
	check_transfer_status();
	print_normal_resp();
}


static void auto_write_1()
{
	printf( "\nautowrite_1 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010c10, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response


	rtd_outl( 0xb8010c08, 0x9 ); // auto write1: 0x9, auto write2:0xA
	rtd_outl( 0xb8010c08, 0x89 );
	//check_transfer_status();
	for(m=0;m<busy;m++)
{
	//mdelay(1);
	check_transfer_status(); 

 	if( rtd_part_inl( 0xb8010c08,6,6 ) == 1 ) 
		break;
	}
	print_normal_resp();
}			

static void auto_write_2()
{
	printf( "\nauto_write_2 : WRITE_MULTIPLE_BLOCK\n" );
	rtd_outl( 0xb8010c10, 0x59 ); //  transmission bit ,  0x19 ;

	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response


	rtd_outl( 0xb8010c08, 0xa ); // auto write2: 0x9, auto write2:0xA
	rtd_outl( 0xb8010c08, 0x8a );
	check_transfer_status();
	print_normal_resp();
}	

static void auto_write_3()
{
	printf( "\nauto_write_3 : WRITE_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response

	rtd_outl( 0xb8010c08, 0x1 ); // auto write3: 0x1, auto write4:0x2
	rtd_outl( 0xb8010c08, 0x81 );
	check_transfer_status();
	print_normal_resp();
}	

static void auto_write_4()
{
	printf( "\nauto_write_4 : WRITE_MULTIPLE_BLOCK\n" );

	rtd_outl( 0xb8010c0c, 0x1 );	//   6 byte response

	rtd_outl( 0xb8010c08, 0x2 ); // auto write3: 0x1, auto write4:0x2
	rtd_outl( 0xb8010c08, 0x82 );
	check_transfer_status();
	print_normal_resp();
}	

	
static setting_device_io_driver( unsigned int driver_type )  // Hspeed driver type 0 1 2 3
{

	switch ( driver_type ) {
		case 0:
			cmd_6_switch( 0xB9,0x01 );
			printf( "Set driver_type = 0\n" );
			break;
		case 1:
			cmd_6_switch( 0xB9,0x11 );
			printf( "Set driver_type = 1\n" );
			break;
		case 2:
			cmd_6_switch( 0xB9,0x21 );
			printf( "Set driver_type = 2\n" );
			break;
		case 3:
			cmd_6_switch( 0xB9,0x31 );
			printf( "Set driver_type = 3\n" );
			break;
		default:
			printf( "driver_type is invalid\n" );
			break;
	}

	cmd_8();
	printf( "driver_type = 0x%x\n",rtd_part_inl( 0xc00000b8,7,4 ) );  //? 185 Byte  

}


static void sram_read(unsigned int SRAM_Data)
{
	unsigned int i,SRAM_ADDR,BYTE_CNT;
	SRAM_ADDR = SD_SRAM_DATA;
	BYTE_CNT =  128;
	printf( "read sram\n" );
	for( i=0; i<BYTE_CNT; i++ ) {
		if( RReg( SD_SRAM_DATA ) != SRAM_Data ){
			INDEX = -1;
			break;
		}
		//printf( "SRAM_ADDR=0x%03x, Value=0x%08x\n",( SRAM_ADDR ),RReg( SD_SRAM_DATA ) );
		//SRAM_ADDR =SRAM_ADDR+ 4;
	}
}


static void SD_r_w_setting(UINT32 DDR_A, UINT32 DATA_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010c40, DDR_A ); //DDR address: card to ddr
	rtd_outl( 0xb8010c44, DDR_A ); //DDR address ddr to card
	rtd_outl( 0xb8010c14, (DATA_A & 0xff000000)>>24 );
	rtd_outl( 0xb8010c18, (DATA_A & 0x00ff0000)>>16 );
	rtd_outl( 0xb8010c1c, (DATA_A & 0x0000ff00)>>8 );
	rtd_outl( 0xb8010c20, (DATA_A & 0x000000ff) );
	
	rtd_outl( 0xb8010c04, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010c24, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010c28, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb8010c2c, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb8010c30, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
	//printf( "\nSD_r_w_setting:\n" );   
	//
	//printf( "REG ADDR:0xb8010c40 = 0x%08x\n",rtd_inl( 0xb8010c40 ) );
	//printf( "REG ADDR:0xb8010c44 = 0x%08x\n",rtd_inl( 0xb8010c44 ) );
	//printf( "REG ADDR:0xb8010c14 = 0x%08x\n",rtd_inl( 0xb8010c14 ) );
	//printf( "REG ADDR:0xb8010c18 = 0x%08x\n",rtd_inl( 0xb8010c18 ) );
	//printf( "REG ADDR:0xb8010c1c = 0x%08x\n",rtd_inl( 0xb8010c1c ) );
	//printf( "REG ADDR:0xb8010c20 = 0x%08x\n",rtd_inl( 0xb8010c20 ) );
	//printf( "REG ADDR:0xb8010c04 = 0x%08x\n",rtd_inl( 0xb8010c04 ) );
	//printf( "REG ADDR:0xb8010c24 = 0x%08x\n",rtd_inl( 0xb8010c24 ) ); 
	//printf( "REG ADDR:0xb8010c28 = 0x%08x\n",rtd_inl( 0xb8010c28 ) ); 
	//printf( "REG ADDR:0xb8010c2c = 0x%08x\n",rtd_inl( 0xb8010c2c ) ); 
	//printf( "REG ADDR:0xb8010c30 = 0x%08x\n",rtd_inl( 0xb8010c30 ) ); 
	
	}

static void SD_r_w_cmd_setting(UINT32 DATA_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010c14, (DATA_A & 0xff000000)>>24 );
	rtd_outl( 0xb8010c18, (DATA_A & 0x00ff0000)>>16 );
	rtd_outl( 0xb8010c1c, (DATA_A & 0x0000ff00)>>8 );
	rtd_outl( 0xb8010c20, (DATA_A & 0x000000ff) );
	
	rtd_outl( 0xb8010c04, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010c24, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010c28, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb8010c2c, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb8010c30, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
	//printf( "\nSD_r_w_cmd_setting:\n" );   
	//
	//printf( "REG ADDR:0xb8010c14 = 0x%08x\n",rtd_inl( 0xb8010c14 ) );
	//printf( "REG ADDR:0xb8010c18 = 0x%08x\n",rtd_inl( 0xb8010c18 ) );
	//printf( "REG ADDR:0xb8010c1c = 0x%08x\n",rtd_inl( 0xb8010c1c ) );
	//printf( "REG ADDR:0xb8010c20 = 0x%08x\n",rtd_inl( 0xb8010c20 ) );
	//printf( "REG ADDR:0xb8010c04 = 0x%08x\n",rtd_inl( 0xb8010c04 ) );
	//printf( "REG ADDR:0xb8010c24 = 0x%08x\n",rtd_inl( 0xb8010c24 ) ); 
	//printf( "REG ADDR:0xb8010c28 = 0x%08x\n",rtd_inl( 0xb8010c28 ) ); 
	//printf( "REG ADDR:0xb8010c2c = 0x%08x\n",rtd_inl( 0xb8010c2c ) ); 
	//printf( "REG ADDR:0xb8010c30 = 0x%08x\n",rtd_inl( 0xb8010c30 ) ); 
	
	}


	
	
static void SD_r_w_3_4_setting(UINT32 DDR_A, UINT32 Bus_Width_Highspeed_Byte ,UINT32 Byte_CNT, UINT32 Block_CNT)
{
	rtd_outl( 0xb8010c40, DDR_A ); //DDR address: card to ddr
	rtd_outl( 0xb8010c44, DDR_A ); //DDR address ddr to card
		
	rtd_outl( 0xb8010c04, Bus_Width_Highspeed_Byte );	//0:1-bit, 1:4-bit 2:8-bit

	rtd_outl( 0xb8010c10, (Byte_CNT & 0x000000ff) );	// byte count [7:0]
	rtd_outl( 0xb8010c14, (Byte_CNT & 0x0000ff00)>>8 );	// byte count [10:8]   512Byte
	rtd_outl( 0xb8010c18, (Block_CNT & 0x000000ff) );	// block count [7:0]
	rtd_outl( 0xb8010c1c, (Block_CNT & 0x0000ff00)>>8 );	// block count [11:8]
	
	//printf( "\nSD_r_w_3_4_setting:\n" );   
	//
	//printf( "REG ADDR:0xb8010c40 = 0x%08x\n",rtd_inl( 0xb8010c40 ) );
	//printf( "REG ADDR:0xb8010c44 = 0x%08x\n",rtd_inl( 0xb8010c44 ) );
	//printf( "REG ADDR:0xb8010c10 = 0x%08x\n",rtd_inl( 0xb8010c14 ) );	
	//printf( "REG ADDR:0xb8010c14 = 0x%08x\n",rtd_inl( 0xb8010c14 ) );
	//printf( "REG ADDR:0xb8010c18 = 0x%08x\n",rtd_inl( 0xb8010c18 ) );
	//printf( "REG ADDR:0xb8010c1c = 0x%08x\n",rtd_inl( 0xb8010c1c ) );

	//printf( "REG ADDR:0xb8010c04 = 0x%08x\n",rtd_inl( 0xb8010c04 ) );
	}
	
	
static void sram_mode_test()
{
	
	printf( "\n/*** SD sram_mode_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  ddr_pattern_write(0x87654321,0xc2000000,128);
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_1();
  
  //WReg( 0xb8010c84,0x00000018 );

	printf( "rtd_inl(0xb80010c84) = 0x%08x\n", RReg( 0xb8010c84 ) );

  SetBit( SD_CP_CTRL,8 );	//big endian = 1 
  SetBit( SD_CP_CTRL,3 );	//boot_from_cr = 1 

	
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  SetBit( SD_CP_CTRL,8 );	//big endian = 1 
  auto_read_1();
  
  sram_read(0x87654321);
  
	ResetBit( SD_CP_CTRL,3 );
	
	//WReg( 0xb8010c84,0x00000000 );

	printf( "rtd_inl(0xb80010c84) = 0x%08x\n", RReg( 0xb8010c84 ) );
}
	
static void sram_mode_42k_test()
{
	
	printf( "\n/*** SD 42k_sram_mode_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000054;    //84 block  42K 
	
  ddr_pattern_write(0x5a5aa5a5,0xc2000000,10752);  //128x84block
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_1();
  
  SetBit( Dbus_option,3 );	//Dbus_option = 42k sram enable
  
  DDR_ADDR =  0x18071000;
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_1();
  
  ddr_pattern_read(0xb8071000,10752,0x5a5aa5a5);  //42k sram read and compare  //128x84block
  
	ResetBit( Dbus_option,3 );
}	


void SD_cp_mode()
{
	DDR_ADDR =  0x20000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	printf("\n/*** SD cp mode Test ***/\n");
	     
	printf("\nSD cp mode enable\n");
	
	rtd_outl(0xb8015084, 0x8746bca3);                                                     
	rtd_outl(0xb8015088, 0xcdef89ab);                                                     
	rtd_outl(0xb801508c, 0x54369923);                                                     
	rtd_outl(0xb8015090, 0xcdefbcab);                                                     
	                                                                                                                                                                          
	rtd_outl(0xb8015094, 0x8746bca3);                                                     
	rtd_outl(0xb8015098, 0xcdef89ab);                                                     
	rtd_outl(0xb801509c, 0x54369923);                                                     
	rtd_outl(0xb80150a0, 0xcdefbcab);                                                     
	                                                                                      
	rtd_outl(0xb80150a4, 0x20); //  CP_NF_SET                                        
	//rtd_outl(0xb8010330, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
  rtd_outl(0xb8010380, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
	rtd_outl(0xb8010c84, 0x1);  //CP mode enable    
                                          
	ddr_pattern_write(0x55555555,0xc0000000,128); 
	
	SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
	
	auto_write_1();	//write to SD
		
	ddr_pattern_erase(0xc0000000,128);
	
	rtd_outl(0xb8015084, 0x8746bca3);                                                     
	rtd_outl(0xb8015088, 0xcdef89ab);                                                     
	rtd_outl(0xb801508c, 0x54369923);                                                     
	rtd_outl(0xb8015090, 0xcdefbcab);                                                     
	                                                                                                                                                                          
	rtd_outl(0xb8015094, 0x8746bca3);                                                     
	rtd_outl(0xb8015098, 0xcdef89ab);                                                     
	rtd_outl(0xb801509c, 0x54369923);                                                     
	rtd_outl(0xb80150a0, 0xcdefbcab);                                                     
	                                                                                      
	rtd_outl(0xb80150a4, 0x20); //  CP_NF_SET                                         
	//rtd_outl(0xb8010330, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
  rtd_outl(0xb8010380, 0x1);  // CP_NF_CR_MUX   Nf/CR mux to CP, 0: NF, 1 : CR
	rtd_outl(0xb8010c84, 0x1);  //CP mode enable  

	SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
	
	auto_read_1();	//read from SD to DDR
	
	ddr_pattern_read(0xc0000000,128,0x55555555); //compare	 
	
	rtd_outl(0xb8010c84, 0x0);  //CP mode disable  

}

						


	
static void auto_r_w_1_test( )
{
  
  printf( "\n/*** SD auto_r_w_1_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0xff00ff00,0xc2000000,128);
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_1();
  
  ddr_pattern_erase(0xc2000000,128);
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_1();
  
 
  ddr_pattern_read(0xc2000000,128,0xff00ff00);
}


static void auto_r_w_2_test( )
{
  
  printf( "\n/*** SD auto_r_w_2_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0x55555555,0xc2000000,128);
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  auto_write_2();
  cmd_12();
  
  ddr_pattern_erase(0xc2000000,128);
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count); 
  
  auto_read_2();
  cmd_12();
 
  ddr_pattern_read(0xc2000000,128,0x55555555);
}

static void auto_r_w_3_test( )
{
  
  printf( "\n/*** SD auto_r_w_3_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0x10101010,0xc2000000,128);
  
  SD_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);      
  
  cmd_25();
  
  SD_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_write_3();
  cmd_12();
  
  ddr_pattern_erase(0xc2000000,128);
  
  SD_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  
  cmd_18();
  
  SD_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_read_3();
  cmd_12();
 
  ddr_pattern_read(0xc2000000,128,0x10101010);
}


static void auto_r_w_4_test( )
{
  
  printf( "\n/*** SD auto_r_w_1_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x1;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  //ddr_pattern_write(0x12345678,0xc2000000,128);
  ddr_pattern_write(0xffffffff,0xc2000000,128);
  
  SD_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  
  cmd_25();
  
  SD_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);
  
  auto_write_4();
  
  ddr_pattern_erase(0xc2000000,128);

  SD_r_w_cmd_setting(DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  

  cmd_18();

  SD_r_w_3_4_setting(DDR_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);

  auto_read_4();
  
 
  ddr_pattern_read(0xc2000000,128,0xffffffff);
}


static void bootpartition_test( )
{
  
  printf( "\n/*** bootpartition_test ***/\n");
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x0000007d; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;  
	
  printf( "\n/*** write data to bootpartition 1 ***/\n");	
  cmd_6_switch( 0xB3,0x1 );   // 179 Byte for boot partition 1 enable
  ddr_pattern_write(0x12121212,0xc2000000,128);  
  ddr_pattern_read(0xc2000000,128,0x12121212);
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  auto_write_1();  
  ddr_pattern_erase(0xc2000000,128);
  cmd_8();
	//printf( "bootpartition_type = 0x%x\n",rtd_part_inl( 0xc20000b0,26,24 ) );  //179 Byte 
  printf( "bootpartition_type = 0x%x\n",rtd_inl( 0xc20000b0 ) );  //179 Byte
  
  printf( "\n/*** write data to bootpartition 2 ***/\n");	
  
  cmd_6_switch( 0xB3,0x2 );   // 179 Byte for boot partition 2 enable
  
  ddr_pattern_write(0x21212121,0xc2000000,128);  
  ddr_pattern_read(0xc2000000,128,0x21212121);
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x0000007d; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001;
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  auto_write_1();  
  ddr_pattern_erase(0xc2000000,128);
  cmd_8();
	//printf( "bootpartition_type = 0x%x\n",rtd_part_inl( 0xc20000b0,26,24 ) );  //179 Byte
	printf( "bootpartition_type = 0x%x\n",rtd_inl( 0xc20000b0 ) );  //179 Byte
  
  printf( "\n/*** bootpartition enable to default ***/\n");
  cmd_6_switch( 0xB3,0x0 );   // 179 Byte for boot partition 1,2 disable
  
  cmd_8();
	//printf( "bootpartition_type = 0x%x\n",rtd_part_inl( 0xc20000b0,26,24 ) );  //179 Byte
	printf( "bootpartition_type = 0x%x\n",rtd_inl( 0xc20000b0 ) );  //179 Byte  
	
	
	printf( "\n/*** read data from bootpartition 1 ***/\n");	
	cmd_6_switch( 0xB3,0x1 );   // 179 Byte for boot partition 1 enable
	
	
	DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x0000007d; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001; 
	
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  auto_read_1();  
  ddr_pattern_read(0xc2000000,128,0x12121212);
  cmd_8();
	//printf( "bootpartition_type = 0x%x\n",rtd_part_inl( 0xc20000b0,26,24 ) );  //179 Byte
	printf( "bootpartition_type = 0x%x\n",rtd_inl( 0xc20000b0 ) );  //179 Byte
	
	
	printf( "\n/*** read data from bootpartition 2 ***/\n");
	
  cmd_6_switch( 0xB3,0x2 );   // 179 Byte for boot partition 2 enable
  
  DDR_ADDR =  0x22000000;      
	DATA_ADDR = 0x0000007d; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count =  0x00000200;    
	Block_Count = 0x00000001; 
  
  SD_r_w_setting(DDR_ADDR,DATA_ADDR,BUS_WIDTH_HS,Byte_Count,Block_Count);  
  auto_read_1();  
  ddr_pattern_read(0xc2000000,128,0x21212121);
  cmd_8();
	//printf( "bootpartition_type = 0x%x\n",rtd_part_inl( 0xc20000b0,26,24 ) );  //179 Byte
	printf( "bootpartition_type = 0x%x\n",rtd_inl( 0xc20000b0 ) );  //179 Byte  
}


int SD_init()
{
	unsigned int pwr_up_status,i;
	i=0;
	BUS_WIDTH = 4;		//set 1,4
	 
	SET_BLOCKLEN = 0x02;	//
	RCA_H = 0x00;
	RCA_L = 0x00;
  SD_freq = 0x08;  // 50MHz 
  
	//setting SD source clock frequency
	SD_change_freq();   

	printf( "\n****** Card identification mode *******\n" );
	
	cmd_0();
	cmd_8();
	
	while( 1 ) {
		cmd_55();
		pwr_up_status = acmd_41();
		if( pwr_up_status == 1 ) {
		printf("\n ****** Read transmission done ******\n");
			break;
		}
		mdelay( 100 );
		i++;
		if( i == 20 ) {
			printf( "acmd41 fail\n" );
			break;
		}
	}

	cmd_2();     //send_cid 
	cmd_3();     // set RCA 
	
	RCA_H = rtd_inl(0xb8010c14);
	RCA_L = rtd_inl(0xb8010c18);
	
  printf( "\n sd card RCA ADDR is: RCA_H=%x, RCA_L=%x\n",RCA_H ,RCA_L );	
 

	printf( "\n****** Data transfer mode *******\n" );
	
	cmd_9();		//send_csd
	cmd_10();	  //send_cid same as cmd_2
	
	cmd_7();		//select card
	cmd_7_0();		//deselect card with RCA 00
  cmd_7();		//select card
  
  setting_bus_width( BUS_WIDTH );   // set 1 , 4  or 8 bit
  setting_HS_Mode();       
  cmd_13();
	cmd_16();		//SET_BLOCKLEN
}

int QC_Verifier_CardReader(void)
{
	int i =0;
	INDEX = 0;
	
	DDR_ADDR = 0xa2000000;      
	DATA_ADDR = 0x00002000; 
	BUS_WIDTH_HS = 0x2;      
	Byte_Count = 0x00000200;    
	Block_Count = 0x00000001;    
 
	//SD_pin_mux_setting();
	//SD_PWR_EN();

	 
//printf( "rtd_inl(0xb8000878) = 0x%08x\n", RReg( 0xb8000878 ) );
//printf( "rtd_inl(0xb801b114) = 0x%08x\n", RReg( 0xb8000878 ) );
//printf( "rtd_inl(0xb801b130) = 0x%08x\n", RReg( 0xb8000878 ) );

	
	
WReg( 0xb8000910,0x543222a8);	
WReg( 0xb8000864,0x28140a00);	
WReg( 0xb8000868,0x28140a00);	
WReg( 0xb800086c,0x28140000);	
WReg( 0xb8000878,0xf8000000);	

WReg( 0xb801b114,0x00000800 );
WReg( 0xb801b130,0x00000800 );

	//printf( "rtd_inl(0xb8000910) = 0x%08x\n", RReg( 0xb8000910 ) );
	//printf( "rtd_inl(0xb8000864) = 0x%08x\n", RReg( 0xb8000864 ) );
	//printf( "rtd_inl(0xb8000868) = 0x%08x\n", RReg( 0xb8000868 ) );
	//printf( "rtd_inl(0xb800086c) = 0x%08x\n", RReg( 0xb800086c ) );
	//printf( "rtd_inl(0xb8000878) = 0x%08x\n", RReg( 0xb8000878 ) );
	
//printf( "rtd_inl(0xb8000878) = 0x%08x\n", RReg( 0xb8000878 ) );
//printf( "rtd_inl(0xb801b114) = 0x%08x\n", RReg( 0xb8001b114) );
//printf( "rtd_inl(0xb801b130) = 0x%08x\n", RReg( 0xb8001b130) );	
	
	//ResetBit( 0xb8000004,10 ); //rst enable
	//ResetBit( 0xb800000c,25 ); //clk enable
	//udelay( 10 );
	//SetBit( 0xb8000004,10 );
	//SetBit( 0xb800000c,25 );
	
	ResetBit( 0xb8000004,10 ); //rst=0

  ResetBit( 0xb800000c,25 ); //clk=0

  udelay( 10 );

  SetBit( 0xb800000c,25 ); //clk=1

  udelay( 10 );

  ResetBit( 0xb800000c,25 ); //clk=0

  udelay( 10 );

  SetBit( 0xb8000004,10 ); //rst=1

  udelay( 10 );

  SetBit( 0xb800000c,25 ); //clk=1


	
		
  SD_init();

  //SD_cp_mode();                                 
                                                    
  //rtd_outl(0xb8010c84, 0x0);  //CP mode enable off   
  
 
   auto_r_w_1_test();
   

   //auto_r_w_2_test();
   //auto_r_w_3_test();
   //auto_r_w_4_test();
 
   //sram_mode_test();

 
 
//	for(i=0;i<3;i++)
//	{
//	auto_r_w_1_test();
//	printf("number %d w/r test\n",i);
//  }
	
	
	//ResetBit( 0xb8000004,10 ); //rst enable
	//ResetBit( 0xb800000c,25 ); //clk enable
	//udelay( 10 );
	//SetBit( 0xb8000004,10 );
	//SetBit( 0xb800000c,25 );	
	//
	//sram_mode_test(); 
   
	
	if(INDEX == -1) return INDEX;
		
	//return INDEX;	//SUCCESS=0, FAILED =-1
	return 0;

	
	//return FAILED;
}
