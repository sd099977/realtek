#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

#include "ifd_driver.h"

#define ROS_ENTER_CRITICAL()
#define ROS_EXIT_CRITICAL()
//#define IFD_I2C_DRIVER//by Lee, 0715

#ifdef IFD_I2C_DRIVER
//I2C function-Debug use only, remove after system team ok.
//*********************************************************************
#define I2C_USE I2C_MASTER1
#define I2C_MASTER0 0
#define I2C_MASTER1 1
#define IO_BASE0 0xb8061600
#define IO_BASE1 0xb801b400
#define IO_BASE (I2C_USE==IO_BASE0)?IO_BASE0:IO_BASE1

//*********************************************************************

void tuner_i2c_init(void)
{
	//rtd_maskl(0xb8000814,~((0xf<<20)|(0xf<<12)),(0x5<<20)|(0x5<<12));
	//rtd_maskl(0xb80008c0,~(0xf<<6),0x2<<6);//
	//rtd_maskl(0xb80008c4,~((0x1<<14)|(0x1<<11)),(0x0<<14)|(0x1<<11));
	rtd_maskl(0xb8000870,~((0xf<<20)|(0xf<<12)),(0x5<<20)|(0x5<<12)); 
       rtd_maskl(0xb80008c0,~(0xf<<0),0x2<<0);//20130303, by Lee

	//rtd_maskl(0xb80602a0,0xffffffcf,0x30);

	rtd_maskl(0xb8000814,0xff0f0fff,0x00505000);
	rtd_maskl(0xb80008C0,0xfffffc3f,0x00000140);

	rtd_outl(0xb801b46c,0x0);	// disable I2C for I2C1

	rtd_outl(0xb801b400,0x63);  // 7-bit address

	rtd_outl(0xb801b404,0x0060);	// master address 0x40 --> random, need same as slave address  7-bit address

	ScalerTimer_DelayXms(1);

	rtd_outl(0xb801b46c,0x1);	// enable I2C1
	ScalerTimer_DelayXms(1);

}

bool tuner_i2c_write(unsigned char id, unsigned short Addr, unsigned short nData, unsigned char* pData, int Flag)
{
	unsigned short i;
	unsigned long pData1;
	
	for (i=0;i<nData;i++) {
		pData1=(pData[i]|0x80000);
		//IFD_QC_MSG("pData[%d]=%x \n",i,pData1);
		rtd_outl(IO_BASE+0xa0,pData1);
	}
	rtd_outl(IO_BASE+0xa0,0xc0000);
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
      		timeout = 0x10;
		rtd_outl(IO_BASE+0x10,0x100);
		while(!(rtd_inl(IO_BASE+0x70) & _BIT3))
		{
			ScalerTimer_DelayXms(1);
			timeout--;
			if(timeout==0) break;
		}
		if(timeout==0) return _TRUE;
		pData[i]=rtd_inl(IO_BASE+0x10)&0xff;
	}
	return _FALSE;
}

#endif

void drvif_scaleri2c_tuner_init() 
{
	I2C_Init();
	return;
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

	//printk("###drvif_scaleri2c_tuner_write()###\n");//by Lee
	
	UINT8 device_id_local;
	UINT16 addr_local;
	UINT16 data_len=7;
	UINT8 data[16];
	int i2c_flag=0;

	UINT8 i, j;
	UINT8 retry = 3;
	UINT8 result = 0;
     
	tuner_write_retry:

	//device_id_local = pI2CModule->device_id/*>>1*/;
	device_id_local = pI2CModule->device_id>>1;//by Lee, 07


	while(retry) {
		retry --;

		//init I2C
		#ifndef IFD_I2C_DRIVER
		//I2C_Init();
		//I2C_SetSpeed(pI2CModule->master_id, 100);
		//rtd_outl(0xb801b06c, 0x8012);
		#else
		tuner_i2c_init();//debug
		#endif
		//init address
		if((pI2CModule->addrtype==0)||(pI2CModule->addrtype==3))
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

				for (j=0 ; j<data_len; j++) 
				{
					data[j]=pWriteArray[i+j];
				}
				#ifndef IFD_I2C_DRIVER
				result = I2C_Write_EX(pI2CModule->master_id, device_id_local, data_len, data/*, i2c_flag*/);//by Lee, 0715
				#else
				//result = tuner_i2c_write(pI2CModule->master_id, device_id_local, data_len, data, i2c_flag);//by Lee, 0715
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
				//for (j=0 ; j<data_len; j++) IFD_DEBUG_MSG(IFD_MSG_TUNER, "@@@I2C write@@@data[%x]=%x\n", j+data[0], data[j+1]);
				udelay(10000);
				result = I2C_Write_EX(pI2CModule->master_id, device_id_local, 1+data_len, data/*, i2c_flag*/);//by Lee,0715
				#else
				//result = tuner_i2c_write(pI2CModule->master_id, device_id_local, 1+data_len, data, i2c_flag);//by Lee, 0715
				//for (j=1 ; j<data_len+1; j++) IFD_DEBUG_MSG(IFD_MSG_TUNER, "@@@I2C write@@@data[%2x]=%2x\n", j+data[0], data[j]);
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
				result = /*tuner_i2c_write*/I2C_Write_EX(pI2CModule->master_id, device_id_local, 2+data_len, data/*, i2c_flag*/);//by Lee,0715
				#else
				//result = tuner_i2c_write(pI2CModule->master_id, device_id_local, 2+data_len, data, i2c_flag);//by Lee, 0715
				#endif
			}
			else if(pI2CModule->addrtype==3)
			{
				if((pI2CModule->len-i)>9)
					data_len = 9;
				else
					data_len = (pI2CModule->len-i);

				for (j=0 ; j<data_len; j++) data[j]=pWriteArray[i+j];
				#ifndef IFD_I2C_DRIVER
				result = I2C_Write_EX(pI2CModule->master_id, device_id_local, data_len, data/*, i2c_flag*/);//by Lee,0715
				//for (j=0 ; j<data_len; j++) IFD_DEBUG_MSG(IFD_MSG_TUNER, "@@@I2C write@@@data[%d]=%x\n", j, data[j]);
				udelay(10000);
				#else
				//result = tuner_i2c_write(pI2CModule->master_id, device_id_local, data_len, data, i2c_flag);//by Lee, 0715
				//for (j=1 ; j<data_len+1; j++) IFD_DEBUG_MSG(IFD_MSG_TUNER, "@@@I2C write@@@data[%2x]=%2x\n", j+data[0], data[j]);
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
	
	//printk("###drvif_scaleri2c_tuner_read()###\n");//by Lee
	
	UINT8 device_id_local;
	UINT16 addressbyte_num;
	UINT16 address_local;
	UINT8 address_byte[2];
	UINT16 databyte_num;
	int i2c_flag=0;

	UINT8 i, result;
	UINT8 retry = 0;

	UINT8 j;

	//device_id_local = pI2CModule->device_id/*>>1*/;
	device_id_local = pI2CModule->device_id>>1;//by Lee, 07
	address_local = pI2CModule->slave_addr;
   
	//init I2C
	#ifndef IFD_I2C_DRIVER
	//I2C_Init();
	//I2C_SetSpeed(pI2CModule->master_id, 100);//50 by Lee, 07, default is 100.
	#else
	tuner_i2c_init();//debug
	#endif

	for (i = 0; i<pI2CModule->len;) {

		if(pI2CModule->addrtype==0)
		{
			databyte_num = ((pI2CModule->len - i) < 8) ? (pI2CModule->len - i) : 8;
			address_byte[0] = 0;
			address_byte[1] = 0;
		}
		else if(pI2CModule->addrtype==1)
		{
			databyte_num = ((pI2CModule->len - i) < 8) ? (pI2CModule->len - i) : 8;
			address_byte[0] = address_local & 0xFF;
			address_byte[1] = 0;
		}
		else if(pI2CModule->addrtype==3)
		{
			databyte_num = ((pI2CModule->len - i) < 20) ? (pI2CModule->len - i) : 20;
			address_byte[0] = address_local & 0xFF;
			address_byte[1] = 0;
		}
		else
		{
			databyte_num = ((pI2CModule->len - i) < 8) ? (pI2CModule->len - i) : 8;
			address_byte[0] = address_local >> 8;
			address_byte[1] = address_local & 0xFF;
		}
		if(pI2CModule->addrtype<3)
			addressbyte_num = pI2CModule->addrtype;
		else
			addressbyte_num = 0;
		retry = 0;
		do {
			#if !defined(CONFIG_I2C_PRE_COMMAND_ENABLE)
			ROS_ENTER_CRITICAL();
			#endif
			
			//IFD_DEBUG_MSG(IFD_MSG_TUNER, "addressbyte_num=%d, address_byte=%x, databyte_num=%d,\n", addressbyte_num, address_byte[0], databyte_num);
			#ifndef IFD_I2C_DRIVER
			result = I2C_Read_EX(pI2CModule->master_id,device_id_local, addressbyte_num, &address_byte[0],databyte_num, &pReadArray[address_local-pI2CModule->slave_addr]/*, i2c_flag*/);//by Lee, 0715
			//for (j=0 ; j<databyte_num; j++) IFD_DEBUG_MSG(IFD_MSG_TUNER, "@@@I2C read@@@data[%x]=%x\n", j+address_byte[0], pReadArray[j+i]);//by LEE
			udelay(10000);
			#else
			//result = tuner_i2c_read(pI2CModule->master_id,device_id_local, addressbyte_num, &address_byte[0],databyte_num, &pReadArray[address_local-pI2CModule->slave_addr], i2c_flag);//by Lee, 0715
			//for (j=0 ; j<databyte_num; j++) printf("@@@I2C read@@@data[%x]=%x\n", j+address_byte[0], pReadArray[j+i]);
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

//=================================================================
//Tuner Interface driver
//=================================================================

/*=============================================================*/
UINT32 CTunerGetChanelMaxFreq(void)
{
	return GET_ATV_TUNER_MAXFREQ();
}

/*=============================================================*/
UINT32 CTunerGetChanelMinFreq(void)
{
	return  GET_ATV_TUNER_MINFREQ();
}


