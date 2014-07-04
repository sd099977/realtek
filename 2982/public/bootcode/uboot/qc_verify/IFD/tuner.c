/*
#include <rtd_types.h>
#include <rtd_system.h>
#include <rtd_lib.h>
#include <columbus.h>
*/
/*=============================================================
 * Copyright (c)      Realtek Semiconductor Corporation, 2005 *
 * All rights reserved.                                       *
 *============================================================*/
/*======================= Description ========================*/
/**
 * @file
 * @author
 * @date        2005/10/13
 * @version     0.1
 * @ingroup
 *
 * @Note
 */

/*======================= CVS Headers =========================
  $Header$
  $Log$
  Revision 1.2  2006/02/16 10:30:10  hill
  +:add TV HRC/IRC freq

  Revision 1.1.1.1  2006/02/06 06:03:22  forster
  no message

  Revision 1.1.1.1  2006/01/16 09:33:56  frankcheng
  2533v code refine.

  Revision 1.8  2005/11/23 05:29:39  hill
  *:update _VHF_LOW_FREQ / _VHF_HIGH_FREQ for NTSC

  Revision 1.7  2005/11/15 14:16:57  hill
  *: add monitor new code to our standard code

  Revision 1.6  2005/11/15 08:00:20  hill
  +: add for Techview board setting

  Revision 1.5  2005/10/13 14:11:40  joshlin
  *:update for audio function

*=============================================================*/
/* basic */
#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

//#ifndef _PACIFIC_H_
//#include <pacific.h>
//#endif

//#ifndef _MONITOR_H_
//#include <monitor.h>
//#endif

//#ifndef _UART_H_
//#include <uart.h>
//#endif

//#include <rtd_system.h>
//#include <rtd_lib.h>
//#include <columbus.h>

#include "rtd_types_qc.h"
#include "tuner.h"
#include "IFD_qc.h"

//#include "i2c_verify.h"
//#include "../../drivers/i2c/i2c_verify.h"


//*********************************************************************
//Definition tuner model
//*********************************************************************
#define I2C_USE I2C_MASTER1
#define CONFIG_I2C_PRE_COMMAND_ENABLE
#define IFD_I2C_DRIVER

//*********************************************************************
#define I2C_MASTER0 0
#define I2C_MASTER1 1
#define IO_BASE0 0xb8061600
#define IO_BASE1 0xb801b400
#define IO_BASE (I2C_USE==IO_BASE0)?IO_BASE0:IO_BASE1

//*********************************************************************
void tuner_i2c_init(void)
{
	rtd_maskl(0xb8000814,~((0xf<<20)|(0xf<<12)),(0x5<<20)|(0x5<<12)); 
	rtd_maskl(0xb80008c0,~(0xf<<6),0x2<<6);//
	//rtd_maskl(0xb80602a0,0xffffffcf,0x30);  
 	rtd_outl(IO_BASE+0x6c,0x0); // I2C Disable
 	rtd_outl(IO_BASE+0x00,0xcb); // Normal Mode
 	rtd_outl(IO_BASE+0x14,0x7a);	// high duty	
	rtd_outl(IO_BASE+0x18,0x8f);		 // low duty
 	rtd_outl(IO_BASE+0x1c,0x2c); // high duty 
 	rtd_outl(IO_BASE+0x20,0x2c);   // low duty
 	rtd_outl(IO_BASE+0x04,0x60); // TAR Address
 	rtd_outl(IO_BASE+0x6c,0x1); // I2C Enable
}
bool tuner_i2c_write(unsigned char id, unsigned short Addr, unsigned short nData, unsigned char* pData, int Flag)
{
	unsigned short i;
	//for (i=0;i<nData;i++) printk("%x=%x\n", i, pData[i]);
	//rtd_outl(IO_BASE+0x04,Addr); // TAR Address
	for (i=0;i<nData;i++) {
		rtd_outl(IO_BASE+0x10,pData[i]); 
	}
	return _FALSE;
	
}
bool tuner_i2c_read(unsigned char id, unsigned short Addr, unsigned short nSubAddr, unsigned char* pSubAddr, unsigned short nData, unsigned char* pData, int Flag)
{
	unsigned short i, timeout=0xff;

	rtd_outl(IO_BASE+0x04,Addr); // TAR Address
	if(nSubAddr!=0)
	{
		for (i=0;i<nSubAddr;i++) rtd_outl(IO_BASE+0x10,pSubAddr[i]); 
	}
	ScalerTimer_DelayXms(1); 
	tuner_i2c_init();
	ScalerTimer_DelayXms(1); 
	for (i=0;i<nData;i++) 
      {
      		timeout = 0xff;
		rtd_outl(IO_BASE+0x10,0x100); 
		while(!(rtd_inl(IO_BASE+0x70) & _BIT3))
		{
			ScalerTimer_DelayXms(1); 
			timeout--;
		}
		if(timeout==0) return _FALSE;
		pData[i]=rtd_inl(IO_BASE+0x10)&0xff; 
	}
	
	return _FALSE;
}
//=================================================================
/**
 * drvif_scaleri2c_tuner_write
 *
 *
 * @param <pI2CModule><pWriteArray>
 *		pI2CModule: Address Type, Device ID, Slave Address
 *		pWriteArray: Only Data
 * @return { _TRUE/_FALSE }
 */
UINT8 drvif_scaleri2c_tuner_write(I2C_MODULE *pI2CModule, UINT8 *pWriteArray) {
	UINT8 device_id_local;
	UINT16 addr_local;
	UINT16 data_len=7;
	UINT8 data[16];
	int i2c_flag=0;

	UINT8 i, j;
	UINT8 retry = 3;
	UINT8 result = 0;
	
	tuner_write_retry:

	device_id_local = pI2CModule->device_id>>1;

	while(retry) {
		retry --;

		//init I2C
		#ifndef IFD_I2C_DRIVER 
		I2C_Init();
		I2C_SetSpeed(pI2CModule->master_id, 50);
		#else
		tuner_i2c_init();//debug
		#endif
		//init address
		if(pI2CModule->addrtype==0)
			addr_local = 0;//No Address
		else
			addr_local = pI2CModule->slave_addr;
		
		for (i = 0; i<pI2CModule->len;) 
		{
			#if !defined(CONFIG_I2C_PRE_COMMAND_ENABLE)
			ROS_ENTER_CRITICAL();
			#endif
			
			if(pI2CModule->addrtype==0)
			{
				if((pI2CModule->len-i)>7)
					data_len = 7;
				else
					data_len = (pI2CModule->len-i);

				for (j=0 ; j<data_len; j++) data[j]=pWriteArray[i+j];
				#ifndef IFD_I2C_DRIVER 
				result = /*tuner_i2c_write*/I2C_Write_EX(pI2CModule->master_id, device_id_local, data_len, data, i2c_flag);
				#else
				result = tuner_i2c_write(pI2CModule->master_id, device_id_local, data_len, data, i2c_flag);
				#endif
			}
			else if(pI2CModule->addrtype==1)
			{
				if((pI2CModule->len-i)>6)
					data_len = 6;
				else
					data_len = (pI2CModule->len-i);

				data[0]=addr_local&0xff;
				for (j=0 ; j<data_len; j++) data[j+1]=pWriteArray[i+j];
				#ifndef IFD_I2C_DRIVER 
				result = /*tuner_i2c_write*/I2C_Write_EX(pI2CModule->master_id, device_id_local, 1+data_len, data, i2c_flag);
				#else
				result = tuner_i2c_write(pI2CModule->master_id, device_id_local, 1+data_len, data, i2c_flag);
				#endif
			}
			else if(pI2CModule->addrtype==2){
				if((pI2CModule->len-i)>5)
					data_len = 5;
				else
					data_len = (pI2CModule->len-i);

				data[0]=(addr_local>>8)&0xff;
				data[1]=addr_local&0xff;
				for (j=0 ; j<data_len; j++) data[j+2]=pWriteArray[i+j];
				#ifndef IFD_I2C_DRIVER 
				result = /*tuner_i2c_write*/I2C_Write_EX(pI2CModule->master_id, device_id_local, 2+data_len, data, i2c_flag);
				#else
				result = tuner_i2c_write(pI2CModule->master_id, device_id_local, 2+data_len, data, i2c_flag);
				#endif
			}
			#if !defined(CONFIG_I2C_PRE_COMMAND_ENABLE)
			ROS_EXIT_CRITICAL();
			#endif
			if (result == 1) {
					IFD_DEBUG_MSG(IFD_MSG_TUNER, "tuner write error : I2C error\n");
					#ifndef IFD_I2C_DRIVER 
					I2C_UnInit();
					#endif
					goto tuner_write_retry;
			}

			 i+=data_len;
			addr_local+=data_len;
		}

		return _TRUE;
	}

	return _FALSE;

}
UINT8 drvif_scaleri2c_tuner_read(I2C_MODULE *pI2CModule, UINT8 *pReadArray) {
	UINT8 device_id_local;
	UINT16 addressbyte_num;
	UINT16 address_local;
	UINT8 address_byte[2];
	UINT16 databyte_num;
	int i2c_flag=0;

	UINT8 i, result;
	UINT8 retry = 0;
	
	device_id_local = pI2CModule->device_id>>1;
	address_local = pI2CModule->slave_addr;

	//init I2C
	#ifndef IFD_I2C_DRIVER 
	I2C_Init();
	I2C_SetSpeed(pI2CModule->master_id, 50);
	#else
	tuner_i2c_init();//debug
	#endif

	for (i = 0; i<pI2CModule->len;) {

		databyte_num = ((pI2CModule->len - i) < 8) ? (pI2CModule->len - i) : 8;
		if(pI2CModule->addrtype==0)
		{
			address_byte[0] = 0;
			address_byte[1] = 0;
		}
		else if(pI2CModule->addrtype==1)
		{
			address_byte[0] = address_local & 0xFF;
			address_byte[1] = 0;
		}
		else
		{
			address_byte[0] = address_local >> 8;
			address_byte[1] = address_local & 0xFF;
		}
		addressbyte_num = pI2CModule->addrtype;
		retry = 0;
		do {
			#if !defined(CONFIG_I2C_PRE_COMMAND_ENABLE)
			ROS_ENTER_CRITICAL();
			#endif
			IFD_DEBUG_MSG(IFD_MSG_TUNER, "read index=%d\n", address_local-pI2CModule->slave_addr);
			#ifndef IFD_I2C_DRIVER 
			result = /*tuner_i2c_read*/I2C_Read_EX(pI2CModule->master_id,device_id_local, addressbyte_num, &address_byte[0],databyte_num, &pReadArray[address_local-pI2CModule->slave_addr], i2c_flag);
			#else
			result = tuner_i2c_read(pI2CModule->master_id,device_id_local, addressbyte_num, &address_byte[0],databyte_num, &pReadArray[address_local-pI2CModule->slave_addr], i2c_flag);
			#endif
			if(result ==1) {
   				IFD_DEBUG_MSG(IFD_MSG_TUNER, "tuner read error : I2C error-->Retry %d\n", retry);
				#ifndef IFD_I2C_DRIVER 
				I2C_UnInit();
				#endif
			}
			#if !defined(CONFIG_I2C_PRE_COMMAND_ENABLE)
			ROS_EXIT_CRITICAL();
			#endif
			retry++;
		}while((result== 1) && (retry<= 3));

		if (retry>=4) 
		{
			IFD_DEBUG_MSG(IFD_MSG_TUNER, "tuner read error\n");
			return _FALSE;
		}
		address_local+=databyte_num;
		i+=databyte_num;
	}

	return _TRUE;
}

//-------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------
StructTunerDataType gTunerData;
UINT32  g_rftuner_curr_freq=0;
UINT8				gTunerNo = 1;
I2C_MODULE gTunerpI2CModule;
//I2C_MODULE *pI2CModule;
//-------------------------------------------------------------
// Core Function
//-------------------------------------------------------------
void CTunerInit(void)
{
#ifdef CONFIG_TUNER_SHARP_2403
	gTunerData.tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData.tunerMinFreq = 432500;//430000;
	gTunerData.tunerVHF_LowFreq = 1452500;//1459000;
	gTunerData.tunerVHF_HighFreq = 4292500;//4299000;
	gTunerData.tunerMaxFreq = 8702500;//8700000;
	gTunerData.tunerPIF = 380000;
	gTunerData.tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData.tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData.tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData.tunerBandFreq[0] = 1379000;
	gTunerData.tunerBandFreq[1] = 1459000;
	gTunerData.tunerBandFreq[2] = 4299000;
	gTunerData.tunerBandFreq[3] = 8700000;
	gTunerData.tunerRegisterByte[0] = 0xbd; //band0
	gTunerData.tunerRegisterByte[1] = 0x11;
	gTunerData.tunerRegisterByte[2] = 0xdd;
	gTunerData.tunerRegisterByte[3] = 0xbd; //band1
	gTunerData.tunerRegisterByte[4] = 0x12;
	gTunerData.tunerRegisterByte[5] = 0xdd;
	gTunerData.tunerRegisterByte[6] = 0xbd;  //band2
	gTunerData.tunerRegisterByte[7] = 0x12;
	gTunerData.tunerRegisterByte[8] = 0xdd;
	gTunerData.tunerRegisterByte[9] = 0xbd; //band3
	gTunerData.tunerRegisterByte[10] = 0x14;
	gTunerData.tunerRegisterByte[11] = 0xdd;
	gTunerData.tunerRegisterByteSearch[0] = 0xbd; //band0
	gTunerData.tunerRegisterByteSearch[1] = 0x11;
	gTunerData.tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData.tunerRegisterByteSearch[3] = 0xbd; //band1
	gTunerData.tunerRegisterByteSearch[4] = 0x12;
	gTunerData.tunerRegisterByteSearch[5] = 0xfd; 
	gTunerData.tunerRegisterByteSearch[6] = 0xbd; // band2
	gTunerData.tunerRegisterByteSearch[7] = 0x12; 
	gTunerData.tunerRegisterByteSearch[8] = 0xfd;
	gTunerData.tunerRegisterByteSearch[9] = 0xbd; //band3
	gTunerData.tunerRegisterByteSearch[10] = 0x14;
	gTunerData.tunerRegisterByteSearch[11] = 0xfd;
	gTunerData.tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData.tunerRfInputByte = 0;
	gTunerData.tunerRfInputLocation = 0;
	gTunerData.tunerFLStatusBit=_BIT6;

	gTunerData.tunerBandNo = 4;
	gTunerData.tunerRegNoPerBand= 3;
	gTunerData.tunerUsedTag = _FALSE;
	gTunerData.tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData.tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData.tunerType = TUNER_NORMAL;
	gTunerData.tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData.tunerSpecificTag = 0;
	gTunerData.tunerID = TUNER_SHARP_2403;
#else
	gTunerData.tunerI2C_ADD = 0xc0; // tuner i2c device address
	gTunerData.tunerMinFreq = 432500;//430000;
	gTunerData.tunerVHF_LowFreq = 1452500;//1459000;
	gTunerData.tunerVHF_HighFreq = 4292500;//4299000;
	gTunerData.tunerMaxFreq = 8702500;//8700000;
	gTunerData.tunerPIF = 380000;
	gTunerData.tunerPIF_MN = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_B = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_GH = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_I = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_DK = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_L = IFD_IF_FREQ_38M;
	gTunerData.tunerPIF_LA = IFD_IF_FREQ_32P2M;
	gTunerData.tunerPIF_SCAN= IFD_IF_FREQ_38M;
	gTunerData.tunerRATIOStepSize =500;  // this tuner only provide two reference divider ratio=24 or  80

	gTunerData.tunerBandFreq[0] = 1379000;
	gTunerData.tunerBandFreq[1] = 1459000;
	gTunerData.tunerBandFreq[2] = 4299000;
	gTunerData.tunerBandFreq[3] = 8700000;
	gTunerData.tunerRegisterByte[0] = 0xbd; //band0
	gTunerData.tunerRegisterByte[1] = 0x11;
	gTunerData.tunerRegisterByte[2] = 0xdd;
	gTunerData.tunerRegisterByte[3] = 0xbd; //band1
	gTunerData.tunerRegisterByte[4] = 0x12;
	gTunerData.tunerRegisterByte[5] = 0xdd;
	gTunerData.tunerRegisterByte[6] = 0xbd;  //band2
	gTunerData.tunerRegisterByte[7] = 0x12;
	gTunerData.tunerRegisterByte[8] = 0xdd;
	gTunerData.tunerRegisterByte[9] = 0xbd; //band3
	gTunerData.tunerRegisterByte[10] = 0x14;
	gTunerData.tunerRegisterByte[11] = 0xdd;
	gTunerData.tunerRegisterByteSearch[0] = 0xbd; //band0
	gTunerData.tunerRegisterByteSearch[1] = 0x11;
	gTunerData.tunerRegisterByteSearch[2] = 0xfd; 
	gTunerData.tunerRegisterByteSearch[3] = 0xbd; //band1
	gTunerData.tunerRegisterByteSearch[4] = 0x12;
	gTunerData.tunerRegisterByteSearch[5] = 0xfd; 
	gTunerData.tunerRegisterByteSearch[6] = 0xbd; // band2
	gTunerData.tunerRegisterByteSearch[7] = 0x12; 
	gTunerData.tunerRegisterByteSearch[8] = 0xfd;
	gTunerData.tunerRegisterByteSearch[9] = 0xbd; //band3
	gTunerData.tunerRegisterByteSearch[10] = 0x14;
	gTunerData.tunerRegisterByteSearch[11] = 0xfd;
	gTunerData.tunerRfInputSwitchUsedTag = _FALSE;
	gTunerData.tunerRfInputByte = 0;
	gTunerData.tunerRfInputLocation = 0;
	gTunerData.tunerFLStatusBit=_BIT6;

	gTunerData.tunerBandNo = 4;
	gTunerData.tunerRegNoPerBand= 3;
	gTunerData.tunerUsedTag = _FALSE;
	gTunerData.tunerAGCtype = TUNER_NONE_IC_RFAGC;
	gTunerData.tunerAGCpolarity = TUNER_RF_POS_IF_NONE;
	gTunerData.tunerType = TUNER_NORMAL;
	gTunerData.tunerIFType = TUNER_IF_TYPE_NEG;
	gTunerData.tunerSpecificTag = 0;
	gTunerData.tunerID = TUNER_SHARP_2403;
#endif
}

UINT8 CTunerSetFreq(UINT32 freq)
{
	UINT8 setting[10], i;
	UINT8 tunerBANDno;
	UINT8 tunerRegno;
       UINT16 divider_freq = CTunerGeDiverRatio(freq);
	unsigned char dev_addr;

	g_rftuner_curr_freq = freq;
	printk("g_rftuner_curr_freq =%d\n",g_rftuner_curr_freq);
	
	tunerBANDno = gTunerData.tunerBandNo;
	tunerRegno = gTunerData.tunerRegNoPerBand;

	setting[0] = (UINT8)((divider_freq>>8)& 0xff);
	setting[1] = (UINT8)(divider_freq & 0xff);

	
	for(i=0; i<tunerRegno; i++)
	setting[i+2] = gTunerData.tunerRegisterByte[i+tunerRegno*CTunerCheckBand(freq)];

	gTunerpI2CModule.addrtype=0;
	gTunerpI2CModule.device_id=dev_addr;
	gTunerpI2CModule.master_id=I2C_USE;
	gTunerpI2CModule.slave_addr=0;
	gTunerpI2CModule.len= tunerRegno+2;
	
	for(i=0; i<gTunerpI2CModule.len; i++) printk("i2c %x=%x\n", i, setting[i]);
	drvif_scaleri2c_tuner_write(&gTunerpI2CModule, &setting[0]);
#if 0	
	printk("addrtype=%x\n", gTunerpI2CModule.addrtype);
	printk("device_id=%x\n", gTunerpI2CModule.device_id=dev_addr);
	printk("master_id=%x\n", gTunerpI2CModule.master_id);
	printk("slave_addr=%x\n", gTunerpI2CModule.slave_addr);
	printk("len=%x\n", gTunerpI2CModule.len= tunerRegno+2);
	
	UINT8 setting[10], i;
	UINT8 tunerBANDno;
	UINT8 tunerRegno;
       UINT16 divider_freq = CTunerGeDiverRatio(freq);
	unsigned char dev_addr;

	g_rftuner_curr_freq = freq;
	tunerBANDno = gTunerData.tunerBandNo;
	tunerRegno = gTunerData.tunerRegNoPerBand;

	setting[0] =  gTunerData.tunerI2C_ADD;
	setting[1] = (UINT8)((divider_freq>>8)& 0xff);
	setting[2] = (UINT8)(divider_freq & 0xff);

	
	for(i=0; i<tunerRegno; i++)
		setting[i+3] = gTunerData.tunerRegisterByte[i+tunerRegno*CTunerCheckBand(freq)];

	setting[i+3] = 0x00;

	//drvif_scaleri2c_code_write(I2C_MASTER0, gTunerData.tunerI2C_ADD,setting);
	
	dev_addr = ((i2c_verify_get_addr(I2C_MASTER1, I2C_ADDR_7) & 0xff) << 1);

#if 0 //ives for I2C
    	if (dev_addr != gTunerData.tunerI2C_ADD)
        i2c_verify_set_addr(I2C_MASTER1, 0x0, gTunerData.tunerI2C_ADD >> 1, I2C_ADDR_7);

	printk("CTunerSetFreq dev_addr= 0x%x \n", dev_addr );

    	if (i2c_verify_write(I2C_MASTER1, tunerRegno+2, setting+1) != 1) {
        	printk("%s: config tuner error\n ", __FUNCTION__);
        	return _FALSE;
    	}
#else
rtd_outl(IO_BASE+0x6c,0x0);	// I2C Disable
rtd_outl(IO_BASE+0x00,0xcb);	// Fast Mode
rtd_outl(IO_BASE+0x14,0x7a);	// high duty	
rtd_outl(IO_BASE+0x18,0x8f);		 // low duty
rtd_outl(IO_BASE+0x1c,0x2c);	// high duty	
rtd_outl(IO_BASE+0x20,0x2c);		 // low duty
rtd_outl(IO_BASE+0x04,0x60);	// TAR Address //A0
rtd_outl(IO_BASE+0x6c,0x1);	// I2C Enable
rtd_outl(IO_BASE+0x10,setting[1]);	
rtd_outl(IO_BASE+0x10,setting[2]);	
rtd_outl(IO_BASE+0x10,setting[3]);	
rtd_outl(IO_BASE+0x10,setting[4]);	
rtd_outl(IO_BASE+0x10,setting[5]);	
#endif

	return _TRUE;		

#endif
}

/*=============================================================*/
/**
	This routine will set TV to specific frequency  in Search mode
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 CTunerSetFreqSearch(UINT32 freq)
{
	UINT8 setting[10], i;
	UINT8 tunerBANDno;
	UINT8 tunerRegno;
       UINT16 divider_freq = CTunerGeDiverRatio(freq);
	tunerBANDno = gTunerData.tunerBandNo;
	tunerRegno = gTunerData.tunerRegNoPerBand;

	setting[0] =  tunerRegno + 3;
	setting[1] = (UINT8)((divider_freq>>8)& 0xff);
	setting[2] = (UINT8)(divider_freq & 0xff);

	for(i=0; i<tunerRegno; i++)
		setting[i+3] = gTunerData.tunerRegisterByteSearch[i+tunerRegno*CTunerCheckBand(freq)];

	setting[i+3] = 0x00;

#if 0 //ives for I2C
	drvif_scaleri2c_code_write(I2C_MASTER0, gTunerData.tunerI2C_ADD,setting);
#else
rtd_outl(IO_BASE+0x6c,0x0);	// I2C Disable
rtd_outl(IO_BASE+0x00,0xcb);	// Fast Mode
rtd_outl(IO_BASE+0x14,0x7a);	// high duty	
rtd_outl(IO_BASE+0x18,0x8f);		 // low duty
rtd_outl(IO_BASE+0x1c,0x2c);	// high duty	
rtd_outl(IO_BASE+0x20,0x2c);		 // low duty
rtd_outl(IO_BASE+0x04,0x60);	// TAR Address //A0
rtd_outl(IO_BASE+0x6c,0x1);	// I2C Enable
rtd_outl(IO_BASE+0x10,setting[1]);	
rtd_outl(IO_BASE+0x10,setting[2]);	
rtd_outl(IO_BASE+0x10,setting[3]);	
rtd_outl(IO_BASE+0x10,setting[4]);	
rtd_outl(IO_BASE+0x10,setting[5]);	
#endif
	return _TRUE;
}
/*=============================================================*/
/**
	This routine will get divider ratio for specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT16 CTunerGeDiverRatio(UINT32 freq)
{
	return (freq + gTunerData.tunerPIF) / gTunerData.tunerRATIOStepSize;
}

/*=============================================================*/
/**
	This routine will check tuner receiving frequency band(VHF Low¡BVHF High¡BUHF).
	@param 			freq	       					tuner receiving frequency(divider)
	@return 			Return tuner receiving frequency band(01¡B02 or 04)
*/
UINT8 CTunerCheckBand(UINT32 freq)
{
	UINT8 i;
	UINT8 tunerBANDno;

	tunerBANDno = gTunerData.tunerBandNo;
	for (i=0; i<tunerBANDno; ) {
		if (freq <= gTunerData.tunerBandFreq[i])
			return (i);
		i++;
	}
	return tunerBANDno-1;
}

/*=============================================================*/
UINT32 CTunerNToFrequencyNum(UINT16 N)
{
	UINT32 freq;

	// according to N = (freq + 38.9MHz) / 62.5 KHz
	// freq = N * 0.0625 MHz - 38.9 MHz
	// 100 * freq = N * 6.25 - 3890
	// 100 * freq = N * (25 / 4) - 3890

	// freq = N * 0.03125 MHz - 38.9 MHz
	// 100 * freq = N * 3.125 - 3890
	// 100 * freq = N *(12.5 / 4) - 3890

	freq = (UINT32)N * gTunerData.tunerRATIOStepSize;
	freq = (freq - gTunerData.tunerPIF) * 100;

	return freq;
}

/*=============================================================*/
UINT32 CTunerGetRatioInStepSize(void)
{
	return gTunerData.tunerRATIOStepSize;
}

/*=============================================================*/
UINT32 CTunerGetPictureInterFreq(void)
{
	return gTunerData.tunerPIF;
}

/*=============================================================*/
UINT32 CTunerGetChanelMaxFreq(void)
{
	return gTunerData.tunerMaxFreq;
}

/*=============================================================*/
UINT32 CTunerGetChanelMinFreq(void)
{
	return gTunerData.tunerMinFreq;
}

/*=============================================================*/
UINT32 CTunerGetVHF_LowFreq(void)
{
	return gTunerData.tunerVHF_LowFreq;
}

/*=============================================================*/
UINT32 CTunerGetVHF_HighFreq(void)
{
	return gTunerData.tunerVHF_HighFreq;
}
/*=============================================================*/
UINT8 CTunerGetTunerType(void)
{
	return gTunerData.tunerType;
}


BOOL IFDVerifier_tuner(void)
{
	//example
	printk("IFDVerifier_tuner\n");
	rtd_maskl(0xb8000840, 0xFFFF0FFF, 5<<12);
	rtd_outl(0xb8027220,0x00000021);
	rtd_inl(0xb8027250);
	
	printk("\n");	


	return SUCCESS;
}



