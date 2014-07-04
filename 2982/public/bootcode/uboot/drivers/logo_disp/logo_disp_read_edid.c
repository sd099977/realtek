/************************************************************************
 *
 *  logo_disp_read_edid.c
 *
 *  get monitor mode (DVI/HDMI) from display device
 *
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include <common.h>
#include <extern_param.h>

#define S_OK         0
#define S_FALSE     -1

#define DEBUG__LOGO_DISP_READ_EDID
#ifndef DEBUG__LOGO_DISP_READ_EDID
#define printf(...) ;
#endif

#define I2C_Read(args...)                I2C_Read_EX(0, args)

static int Read_EDID(unsigned char *EDID_buf);
static int Read_EDID_block(int block, unsigned char *EDID_buf);
static int Read_EDID_From_TV(unsigned char *EDID_buf);
static int Chk_HotPlug(unsigned char *state);

/************************************************************************
 *  Implementation : Global functions
 ************************************************************************/
void LOGO_DISP_get_Monitor_mode(unsigned char *is_hdmi_mode)
{
	unsigned char EDID_Info[128];
	int ret;

	ret = Read_EDID(EDID_Info);
	if (ret == S_FALSE) {
		printf("[HDMI]: TV is not connected.\n");
		*is_hdmi_mode = 0;
		return;
	}

	if (!EDID_Info[126]) {
		printf("DVI DEVICE\n");
		*is_hdmi_mode = 0;
	}
	else {
		printf("HDMI DEVICE\n");
		*is_hdmi_mode = 1;
	}
}


static int Read_EDID(unsigned char *EDID_buf)
{
	int i;
	int ret;
	int chksum = 0;
	int i2c_speed;
	unsigned char link;

	i2c_speed=50;
	printf("[HDMI]: Set I2C Speed = %d kHz\n",i2c_speed);
	I2C_SetSpeed(0,i2c_speed);
	if (Chk_HotPlug(&link) == S_OK)
	{
		if(link==0)
		{
			printf("[HDMI]: Read_EDID abort, HDMI cable plug off.\n");
			return S_FALSE;
		}
	}
	ret=Read_EDID_From_TV(EDID_buf);
	for(i=0;i<128;i++)
		chksum+=EDID_buf[i];
	if(!(chksum&0xff))
	{
			printf("[HDMI]: EDID chksum valid!!! chksum=%d \n", chksum);
	}
	else
	{
		printf("[HDMI]: EDID chksum invalid!!! chksum=%d !!!!!!!\t=> Re-Read EDID again.\n", chksum);
		//PrintEDID(EDID_buf);
		sys_wait_ms(20);
		//i2c_speed=50;
		printf("[HDMI]: Increase i2c pull-low strength.\n");
		//I2C_SetSpeed(0,i2c_speed);
		rtd_outl(0xb80003e0, 0xc80);
		if (Chk_HotPlug(&link) == S_OK)
		{
			if(link==0)
			{
				printf("[HDMI]: Read_EDID abort, HDMI cable plug off.\n");
				return S_FALSE;
			}
		}
		ret=Read_EDID_From_TV(EDID_buf);
		chksum = 0;
		for(i=0;i<128;i++)
			chksum+=EDID_buf[i];
		if(!(chksum&0xff))
		{
			printf("[HDMI]: EDID chksum valid!!! chksum=%d\n", chksum);
		}
		else
		{
			printf("[HDMI]: EDID chksum invalid!!! chksum=%d !!!!!!!\t\n", chksum);
			return S_FALSE;
		}
	}
	return S_OK;
}

static int Read_EDID_block(int block, unsigned char *EDID_buf)
{
	int ret;
	int i;
	unsigned char EDID_4_bytes[4];
	unsigned char i2c_addr;
	unsigned char SubAddr;
	unsigned short nSubAddrByte;
	unsigned short nDataByte;
	unsigned char  Segment;

	printf("[HDMI]: Tx Reads EDID from Rx. block=%d\n",block);
	if(block<=1)
	{
		i2c_addr=0x50;
		nSubAddrByte=1;
		nDataByte=4;
		for(i=0;i<32;i++)
		{
			SubAddr=4*i+128*block;
			if (I2C_Read(i2c_addr,nSubAddrByte,&SubAddr, nDataByte, EDID_4_bytes)==S_FALSE)
			{
				printf("[HDMI]: Read EDID fails, I2C fail, i=%d\n",i);
				return S_FALSE;
			}
			else
			{
				memcpy(EDID_buf+4*i,EDID_4_bytes, 4);
				//printf("[HDMI]: Read EDID OK, i=%d.\n",i);
				//printf("data: 0x%02x %02x %02x %02x\n",EDID_4_bytes[0],EDID_4_bytes[1],EDID_4_bytes[2],EDID_4_bytes[3]);
			}
			//sys_wait_us(20000);	//wait 0.02 sec, I2C won't be so busy.
		}
	}
	else
	{
		printf("[HDMI]: Tx Reads EDID from Rx. Need Segmentation pointer block=%d\n",block);
/*
		nSubAddrByte=1;
		nDataByte=4;
		Segment=block/2;
		for(i=0;i<32;i++)
		{
			SubAddr=4*i+128*block;
			if (I2C_Read_Segment(Segment,nSubAddrByte,&SubAddr, nDataByte, EDID_4_bytes)==S_FALSE)
			{
				printf("[HDMI]: Read EDID fails, I2C fail(segment), i=%d\n",i);
				return S_FALSE;
			}
			else
			{
				memcpy(EDID_buf+4*i,EDID_4_bytes, 4);
				//printf("[HDMI]: Read EDID OK, i=%d.\n",i);
				//printf("data: 0x%02x %02x %02x %02x\n",EDID_4_bytes[0],EDID_4_bytes[1],EDID_4_bytes[2],EDID_4_bytes[3]);
			}
		}
*/
	}
	ret=S_OK;
	return S_OK;
}

static int Read_EDID_From_TV(unsigned char *EDID_buf)
{
	return Read_EDID_block(0, EDID_buf);
}


static int Chk_HotPlug(unsigned char *state)
{
	#if 0 // need to check
	if((REG32(KSEG1(MIS_GP3DATI))&0x800000)!=0x800000)	//GPIO119_Jupiter
	{
		printf("[HDMI]: Chk_HotPlug() TV is not connected.\n");
		*state = 0;
	}
	else
	{
		printf("[HDMI]: Chk_HotPlug() TV is connected.\n");
		*state = 1;
	}
	#endif
	return S_OK;
}


