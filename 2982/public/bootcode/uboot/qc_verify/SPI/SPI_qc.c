#include <qc_verify_common.h>

int ReadID(void)
{


UINT32 temp_ptr=0xbec00000;
int data;


//Pinshare setting
rtd_maskl(0xb8000830,GetMaskAnd(31,27),0x1<<27); //SPI_SCLK
rtd_maskl(0xb8000830,GetMaskAnd(22,18),0x1<<18); //SPI_DI
rtd_maskl(0xb8000830,GetMaskAnd(13,9),0x1<<9);  //SPI_CS_N
rtd_maskl(0xb8000834,GetMaskAnd(31,27),0x1<<27); //SPI_DO



rtd_outl(0xb801a814,0x00000000);   //set serial flash controller latch data at falling edge

/* read Manufacture & device ID */
rtd_outl(0xb801a800,0x0000009f);
rtd_outl(0xb801a804,0x00000010);

printk("read ID start\n");

udelay(0x1000);

data = rtd_inl(temp_ptr); //chip ID
if(data==0xc21720c2) //MXIC MX25L6406E
	{
		printk("MXIC MX25L6406E_read ID= 0x%x pass \n",rtd_inl(temp_ptr));
		return 0; //IP pass
	}
else if(data==0x1c17301c) //Eon EN25Q64, EN25Q64_104HIP
	{
		printk("Eon EN25Q64_read ID= 0x%x pass \n",rtd_inl(temp_ptr));
		return 0; //IP pass
	}

else
	printk("NO support type_read ID= 0x%x fail\n",rtd_inl(temp_ptr));
	return 1; //IP fail
}

int Read(void)
{

	int arry[64]={0x00781a40,0x11011b3c,0x01cd7b37,0xb0007a13\
,0x00000000,0x5a021b3c,0x01c67b37,0x6d007a13\
,0x00000000,0xa5011b3c,0x01c67b37,0x97007a13\
,0x00000000,0x01000010,0x00000000,0x00780440\
,0x1c01f00f,0x21280000,0x00680440,0x1c01f00f\
,0x21280000,0x00700440,0x1c01f00f,0x21280000\
,0x00400440,0x1c01f00f,0x21280000,0x2120a003\
,0x1c01f00f,0x21280000,0x21204003,0x1c01f00f\
,0x21280000,0xffff0010,0x00000000,0x0090093c\
,0x0000298d,0x0d000a24,0x0a000b24,0x00002aad\
,0x00002bad,0x000024ad,0x00002aad,0x00002bad\
,0x9d0cf077,0x00000000,0x00000824,0x07000215\
,0x00000000,0x6a01f00f,0x00000000,0xc0bf083c\
,0xe4050825,0x08000001,0x00000000,0xc0bf083c\
,0x61440825,0x09f80001,0x00000000,0xffff0010\
,0x00000000,0x00000000,0x00000000,0x00000000};

	UINT32 i=0;
	UINT32 spiaddr2;
	
	for(i=0;i<=63;i++)
	{

	spiaddr2 = 0xbec00000+0x4*i; //64 byte
	/* fast read */                                    
	rtd_outl(0xb801a800,0x0000000b);              
	rtd_outl(0xb801a804,0x00000019);              


	udelay(0x1000);


	if((rtd_inl(spiaddr2))==arry[i]) 		
	{		
		printk("Read pass, addr = 0x%x , data= 0x%x , k = %d \n",spiaddr2, rtd_inl(spiaddr2),i);
			if(i==63)
			{
				return 0;
			}
	}

else	
	{
		printk("Read fail, addr = 0x%x , data= 0x%x , k = %d \n",spiaddr2, rtd_inl(spiaddr2),i);	
		return 1;
	}
	}

}


int QC_Verifier_SPI(void)
{
	UINT32		debug_result = 0;
	UINT32		fail_result = 0;
	
	debug_result = ReadID();	
	fail_result |= debug_result;		

	if (debug_result)
		printk("Read ID failed\n");
	else
		printk("Read ID pass\n");

#if CONFIG_EQC
	debug_result = Read();	
	fail_result |= debug_result;		

	if (debug_result)
		printk("Read failed\n");
	else
		printk("Read pass\n");
#endif

	if(fail_result)    //	  pass return 0  ;	fail  return 1	; 
		return 1;
	else
		return 0;

	
}
