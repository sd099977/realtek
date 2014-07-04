/************************************************************************
 *  Include files
 ************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
//#include <getopt.h>
#include <errno.h>
//#include <asm/types.h>
#include "otp_info.h"

/************************************************************************
 *  Definition
 ************************************************************************/
#define BUFFER_SIZE	(OTP_BIT_NUM / 16)

#define SixteenBit_Mask 0xffff                   
#define DATA_BUFF_SET(idx, reg)							\
		do{								\
			data_buf[idx] = (unsigned short int)(reg>>16)&0xffff;	\
			data_buf[idx+1] = (unsigned short int)(reg&0xffff);	\
		}while(0);
			//printf("DATA_BUFF_SET[%d]: 0x%04x 0x%04x\n", idx,data_buf[idx],data_buf[idx+1]);
		
#define DATA_BUFF_BIT_OR_SET(idx, offset)					\
		do{								\
			UINT32 tmp,exTMP;					\
			tmp = (data_buf[idx+1]<<16)|data_buf[idx];		\
			tmp &= ~(1<<offset);					\
			tmp |= (1<<offset);					\
			exTMP = exchange_short_int(tmp);			\
			DATA_BUFF_SET(idx, exTMP);				\
		}while(0);

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned short int data_buf[BUFFER_SIZE] = {0}; 

unsigned short int b00=0, b01=0,b02=0, b03=0, b04=0, b05=0, b06=0, b07=0, b08=0, b09=0, 
                   b10=0, b11=0, b12=0, b13=0, c00=0, c01=0, c02=0, a00=0, a01=0, a02=0, a03=0, a04=0, 
                   a05=0, a06=0, a07=0, a08=0, a09=0, a10=0, a11=0, a12=0, a13=0, a14=0, 
                   crc_o=0xffff, crc_result=0xffff, d00=0, d01=0, d02=0, d03=0, d04=0, 
                   d05=0, d06=0, d07=0, d08=0, d09=0, d10=0, d11=0, d12=0, d13=0, d14=0, d15=0;
                   
/************************************************************************
 *  Public function prototype
 ************************************************************************/
unsigned short int inline ToBit( unsigned short int value)
{
	value = value & 0x0001;
	return value;
}

void encode_ecc_byte(unsigned short int crc_data_in)
{

 crc_data_in=  crc_data_in &	SixteenBit_Mask;		

 // xor tree

 b00       = ToBit(crc_data_in>>15) ^ ToBit(crc_result>>15) ;
 a00       = b00 ^ ToBit(crc_result>>14);
 c00       = b00 ^ ToBit(crc_result>>1);
 b01       = ToBit(crc_data_in>>14) ^ a00;
 a01       = b01 ^ ToBit(crc_result>>13);
 c01       = b01 ^ ToBit(crc_result);
 b02       = ToBit(crc_data_in>>13) ^ a01;
 a02       = b02 ^ ToBit(crc_result>>12);
 c02       = b02 ^ b00;
 b03       = ToBit(crc_data_in>>12) ^ a02;
 a03       = b03 ^ ToBit(crc_result>>11);
 b04       = ToBit(crc_data_in>>11) ^ a03;
 a04       = b04 ^ ToBit(crc_result>>10);
 b05       = ToBit(crc_data_in>>10) ^ a04;
 a05       = b05 ^ ToBit(crc_result>>9 );
 b06       = ToBit(crc_data_in>>9 ) ^ a05;
 a06       = b06 ^ ToBit(crc_result>>8 );
 b07       = ToBit(crc_data_in>>8 ) ^ a06;
 a07       = b07 ^ ToBit(crc_result>>7 );
 b08       = ToBit(crc_data_in>>7 ) ^ a07;
 a08       = b08 ^ ToBit(crc_result>>6 );
 b09       = ToBit(crc_data_in>>6 ) ^ a08;
 a09       = b09 ^ ToBit(crc_result>>5 );
 b10       = ToBit(crc_data_in>>5 ) ^ a09;
 a10       = b10 ^ ToBit(crc_result>>4 );
 b11       = ToBit(crc_data_in>>4 ) ^ a10;
 a11       = b11 ^ ToBit(crc_result>>3 );
 b12       = ToBit(crc_data_in>>3 ) ^ a11;
 a12       = b12 ^ ToBit(crc_result>>2 );
 b13       = ToBit(crc_data_in>>2 ) ^ a12;
 a13       = b13 ^ c00;
 d01       = ToBit(crc_data_in>>1 ) ^ a13;  
 a14       = c01 ^ d01;
 d00       = ToBit(crc_data_in>>0 ) ^ a14;
 d15       = c02 ^ d00;
 				            
 

 d14       		 = b03 ^ b01;               
 d13 			 = b04 ^ b02;               
 d12 			 = b05 ^ b03;               
 d11			 = b06 ^ b04;               
 d10			 = b07 ^ b05;               
 d09			 = b08 ^ b06;               
 d08			 = b09 ^ b07;               
 d07			 = b10 ^ b08;               
 d06			 = b11 ^ b09;               
 d05			 = b12 ^ b10;               
 d04			 = b13 ^ b11;               
 d03			 = b12 ^ d01;  
 d02			 = b13 ^ d00;  

//printf("a00=%x\n", a00);
//printf("a01=%x\n", a01);
//printf("a02=%x\n", a02);
//printf("a03=%x\n", a03);
//printf("a04=%x\n", a04);
//printf("a05=%x\n", a05);
//printf("a06=%x\n", a06);
//printf("a07=%x\n", a07);
//printf("a08=%x\n", a08);
//printf("a09=%x\n", a09);
//printf("a10=%x\n", a10);
//printf("a11=%x\n", a11);
//printf("a12=%x\n", a12);
//printf("a13=%x\n", a13);
//printf("a14=%x\n", a14);
//printf("b00=%x\n", b00);
//printf("b01=%x\n", b01);
//printf("b02=%x\n", b02);
//printf("b03=%x\n", b03);
//printf("b04=%x\n", b04);
//printf("b05=%x\n", b05);
//printf("b06=%x\n", b06);
//printf("b07=%x\n", b07);
//printf("b08=%x\n", b08);
//printf("b09=%x\n", b09);
//printf("b10=%x\n", b10);
//printf("b11=%x\n", b11);
//printf("b12=%x\n", b12);
//printf("b13=%x\n", b13);
//printf("crc_o=%x\n", crc_o);
 crc_result=(unsigned short int)((d15<<15)|(d14<<14)|(d13<<13)|(d12<<12)|(d11<<11)|(d10<<10)|
 						(d09<<9)|(d08<<8)|(d07<<7)|(d06<<6)|(d05<<5)|(d04<<4)|
 						(d03<<3)|(d02<<2)|(d01<<1)|(d00<<0));
// return crc_result;
}

UINT32 exchange_short_int(UINT32 reg)
{
	UINT32 tmpREG=0x00000000,tmpH=0, tmpL=0;
	
	printf("%s...\n", __FUNCTION__);

	tmpH = (reg>>16)&0xffff;
	tmpL = (reg&0xffff);
	tmpREG= (tmpL<<16)|tmpH;
	
	printf("OriREG:0x%08x, excREG:0x%08x \n", reg, tmpREG);
	return tmpREG;
}

/* comment by alan
int set_rsa_key(UINT32 base)
{
	UINT32 tmpREG=0x00000000, exREG=0x00000000;
	int i=0;
	
	printf("%s...\n", __FUNCTION__);

	for(i = 0; i < (2048 / 32); i++)
	{
		tmpREG = REG32(base+(i*4));
		//20110920, to make sure the key in memeory is correct
		if (tmpREG == 0x00)
			return -1;
		exREG = exchange_short_int(tmpREG);
		DATA_BUFF_SET(i*2, exREG);
	}
	return 1;
	//dump_crc_data_buf();
}

void set_aes_key(UINT32 *key, UINT32 offset)
{
	UINT32 tmp;
	int i,j;
	
	printf("%s...\n", __FUNCTION__);
	
	for(i=0,j=3;i<4;i++,j--)
	{
		tmp = exchange_short_int(key[j]);
		DATA_BUFF_SET(0x100/2+2+(i*2), tmp);   	//0xb801b904
	}
	//assign extra aes bits to 0xff, 0xb801b914
	//DATA_BUFF_SET(0x100/2+2+(4*2), 0x00ff0000); //testing, check with do_init()
	//dump_crc_data_buf();
}
*/

void set_data_buf_bit(UINT32 base, int offset)
{
	//UINT32 tmp, exTMP;
	
	printf("%s...\n", __FUNCTION__);

	DATA_BUFF_BIT_OR_SET(base/2, offset);
}

/* comment by alan
void set_data_buf_uID(UINT32 *val)
{
	UINT32 tmp;
	
	printf("%s...\n", __FUNCTION__);
	tmp = exchange_short_int(val[1]);
	DATA_BUFF_SET(161-1, tmp);   	//0xb801b940, from 0
	tmp = exchange_short_int(val[0]);
	DATA_BUFF_SET(163-1, tmp);   	//0xb801b942, from 0
}

static void init_data_buf()
{
	int i;
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		if (i==141)
			//20110616, for current status, some chips don't set CP bit
			//data_buf[i] = 0x0008;
			data_buf[i] = 0x0000;
		else
			data_buf[i] = 0x0000;
	}
	//dump_crc_data_buf();
}

static void dump_crc_data_buf()
{
	int i;

	printf("dump crc data buf\n");
	for(i=0;i<BUFFER_SIZE;i+=8)
	{
		if (i>=20*8)
			printf("0x%04x 0x%04x 0x%04x 0x%04x\n", data_buf[i], data_buf[i+1], data_buf[i+2], data_buf[i+3]);
		else
			printf("0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n", data_buf[i], data_buf[i+1], data_buf[i+2], data_buf[i+3], data_buf[i+4], data_buf[i+5], data_buf[i+6], data_buf[i+7]);
	}
}
*/

void crc_init(bool all_reset)
{
	b00=0;b01=0;b02=0;b03=0;b04=0;b05=0;b06=0;b07=0;b08=0;b09=0; 
  b10=0;b11=0;b12=0;b13=0;c00=0;c01=0;c02=0;a00=0;a01=0;a02=0;a03=0;a04=0;
	a05=0;a06=0;a07=0;a08=0;a09=0;a10=0;a11=0;a12=0;a13=0;a14=0; 
	crc_o=0xffff;crc_result=0xffff;d00=0;d01=0;d02=0;d03=0;d04=0;
	d05=0;d06=0;d07=0;d08=0;d09=0;d10=0;d11=0;d12=0;d13=0;d14=0;d15=0;
}

unsigned short int crc_get()
{
	return crc_result;
}

#if 0
int main(int argc, char **argv)
{
	int i;
	unsigned short int crc_final;
	for ( i=0; i< 148 ; i++){
		encode_ecc_byte(data_buf[i]);
	    printf("crc_result=%x\n", crc_result);
     }
	
    system("PAUSE"); 
    return 0;		
}
#endif
