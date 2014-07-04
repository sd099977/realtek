#include <asm/io.h>
#include <common.h>
#include <qc_verify_common.h>
#include "bisr_qc.h"
#include "dtv_demod_reg.h"

#if 0
void Clear_I2C0_Sts(void)
{
	rtd_inl(0xb8062640);    //CLR_INTR           
	rtd_inl(0xb8062644);    //CLR_RX_UNDER   
	rtd_inl(0xb8062648);    //CLR_RX_OVER   
	rtd_inl(0xb806264c);    //CLR_TX_OVER   
	rtd_inl(0xb8062650);    //CLR_RD_REQ         
	rtd_inl(0xb8062654);    //CLR_TX_ABRT      
	rtd_inl(0xb8062658);    //CLR_RX_DONE      
	rtd_inl(0xb806265c);    //CLR_ACTIVITY   
	rtd_inl(0xb8062660);    //CLR_STOP_DET   
	rtd_inl(0xb8062664);    //CLR_START_DET
	rtd_inl(0xb8062668);    //CLR_GEN_CALL 
}

int Demod_BISR(void)
{
	UINT32 loop_en, reg_data;
	UINT32 i, Scan=10000; 
	UINT32  j, loop = 200;
	int    Sts = SUCCESS;


	// ========== Pin MUX ==========
	#if 1
    //I2C0 clock enable
    rtd_setbits(CRT_ST_CLKEN0_VADDR, BIT6);
    rtd_clearbits(CRT_ST_CLKEN0_VADDR, BIT6);
    rtd_clearbits(CRT_ST_SRST0_VADDR, BIT6);
    rtd_setbits(CRT_ST_SRST0_VADDR, BIT6);
    rtd_setbits(CRT_ST_CLKEN0_VADDR, BIT6);
    //Global I2C0 INT
    //rtd_outl(0xb8062100,0x00000002);//Clear I2C0_INT read only
    //rtd_outl(ISO_MISC_OFF_INT_EN_reg, (rtd_inl(ISO_MISC_OFF_INT_EN_reg)|0x2));//Clear I2C0_INT	
	//#else
	rtd_maskl(SOFT_RESET1_reg, ~_BIT30, 0); // SOFT_RESET1_reg, bit30:rstn_demod	
	rtd_maskl(SOFT_RESET1_reg, ~_BIT30, _BIT30); // SOFT_RESET1_reg, bit30:rstn_demod
	rtd_maskl(0xb8000004, ~_BIT27, _BIT27); //rstn_i2c_0, I2C0 use 27MHz
	rtd_outl(CLOCK_ENABLE1_reg, 0xffffffff);    // CLOCK_ENABLE1_reg, bit27:clk_en_demod
	rtd_outl(TP_DEMOD_CTRL_reg, (0<<4)|(0<<3)); // bit4:DEMOD_I2C_SADDR_SEL=0
	                                      // bit3:Set Initernal I2C Master Access DTV Demod
	//rtd_outl(ST_Pin_Mux_Ctrl0_reg, (0<<6));     // bit6:DTV_i2c_sel=0 (int i2c)
	rtd_maskl(ST_Pin_Mux_Ctrl0_reg, 0xfffff07f, 0x0);//[11:7]=0x0
	//rtd_outl(ST_CFG_0_reg, ((0 & 0x1f)<<27)|((0 & 0x1f)<<18)); // Disable PAD_ST_GPIO_23 (SDA) to DTV Demod
	                                                     // Disable PAD_ST_GPIO_22 (SCL) to DTV Demod
	rtd_maskl(ST_CFG_0_reg, 0x0783ffff, 0x7fbfffff); //ST_GPIO23[31:27]=0xf,I2C0_SCL_SRC0; ST_GPIO24[22:18]=0xf,I2C0_SDA_SRC0
	printf("Set pin mux for demod\n");
	#endif															   
	// ========== Configuration MISC I2C0 ========== 
	rtd_outl(0xb80602a0, 0x00000000);
	rtd_outl(IC0_ENABLE_reg,       0x00000000); // Diable MISC I2C0
	rtd_outl(IC0_INTR_MASK_reg,    0x00000000); // MASK all the interrupts
	rtd_outl(IC0_TAR_reg,          0x00000012); // Target address, & Set 7 bit address mode
	rtd_outl(IC0_CON_reg,          0x00000025); // 7 bit address mode, slave_en, full speed mode, restart_en
	rtd_outl(IC0_SAR_reg,          0x00000055); // Slave address
	rtd_outl(IC0_HS_MADDR_reg,     0x00000002); // HS Master Mode Code Address
	#if 1
	rtd_outl(IC0_SS_SCL_HCNT_reg,  0x00000013); // Standard Speed I2C Clock SCL High Count
	rtd_outl(IC0_SS_SCL_LCNT_reg,  0x00000024); // Standard Speed I2C Clock SCL Low Count
	rtd_outl(IC0_FS_SCL_HCNT_reg,  0x0000000f); // Full Speed I2C Clock SCL High Count
	rtd_outl(IC0_FS_SCL_LCNT_reg,  0x00000021); // Full Speed I2C Clock SCL Low Count
	rtd_outl(IC0_HS_SCL_HCNT_reg,  0x00000006); // High Speed I2C Clock SCL High Count
	rtd_outl(IC0_HS_SCL_LCNT_reg,  0x00000008); // High Speed I2C Clock SCL Low Count
	rtd_outl(IC0_TX_TL_reg,        0x00000001); // TX FIFO threshold level	
	#else
	rtd_outl(0xb8062614, 0x00000060);
	rtd_outl(0xb8062618, 0x000000b0);
	rtd_outl(0xb806261c, 0x0000001a);
	rtd_outl(0xb8062620, 0x00000030);
	rtd_outl(0xb8062624, 0x00000020);
	rtd_outl(0xb8062628, 0x00000026);
	rtd_outl(0xb806263c, 0x00000000);		
	#endif
	rtd_outl(IC0_RX_TL_reg,        0x00000002); // RX FIFO threshold level
	rtd_outl(IC0_ENABLE_reg,       0x00000001); // Enable MISC I2C0


	//rtd_inl(IC0_COMP_PARAM_1_reg); // I2C0 Component Parameter Register 1
	printf("Configuration MISC I2C0\n");
	
	// ========== MISC I2C0 : Write Addr:0xc001, Data:0x01 (soft rst) ==========
Clear_I2C0_Sts();
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000001); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	// Wait MISC I2C0 transfer done, Check STOP_DET=1
	for(i=0; i<=Scan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
	  	{
			printk("Scan = %d\n",i);
printf("0xb8062634=0x%x, 0xb8062680=0x%x\n",rtd_inl(0xb8062634),rtd_inl(0xb8062680));			
	  		break;
		}
	   	else if(i==Scan)
	   	{
			printf("->(1)Can't wait MISC I2C0 transfer done!\n"); 
		   	return FAILED;
  	 	}
  	}	
	//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();	

	// ========== MISC I2C0 : Write Addr:0xc016, Data:0x01 (bisr rst) ==========
	rtd_outl(IC0_DATA_CMD_reg, 0x000004c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000016); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	// Wait MISC I2C0 transfer done, Check STOP_DET=1
	for(i=0; i<=Scan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
	  	{
			printk("Scan = %d\n",i);
			break;
		}
	   	else if(i==Scan)
	   	{
			printf("->(2)Can't wait MISC I2C0 transfer done!\n"); 
printf("0xb8062634=0x%x, 0xb8062680=0x%x\n",rtd_inl(0xb8062634),rtd_inl(0xb8062680));
			return FAILED;
  	 	}
  	}	
	//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();

	// Wait for BISR Done
	for(j=0; j<=loop; j++)
	{
		// ========== MISC I2C0 : Read Addr:0xc83e ==========
		rtd_outl(IC0_DATA_CMD_reg, 0x000000c8); // DATA_CMD
		rtd_outl(IC0_DATA_CMD_reg, 0x0000023e); // DATA_CMD & Send Stop

		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		for(i=0; i<=Scan; i++)
		{  
			udelay(100);  	 
			// Wait MISC I2C0 transfer done, Check STOP_DET=1
			if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
				break;
			else if(i==Scan)
		   	{
				printf("->(3)Can't wait MISC I2C0 transfer done!\n"); 
			   	return FAILED;
	  	 	}
	  	}	
		//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();		

		rtd_outl(IC0_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read)

		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		for(i=0; i<=Scan; i++)
		{  
			udelay(100);  	 
			// Wait MISC I2C0 transfer done, Check STOP_DET=1
			if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
				break;
			else if(i==Scan)
		   	{
				printf("->(4)Can't wait MISC I2C0 transfer done!\n"); 
			   	return FAILED;
	  	 	}
	  	}	
		//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();		

		// Read 0xc83e bit 4 = 1 (bisr_done)
		reg_data = rtd_inl(IC0_DATA_CMD_reg);
		if ((reg_data & 0x10) == 0x10) 
		{
			printf("->(V)Demod BISR done(%d)\n",j);
			break;
		} 
		else if (j==loop)
		{
			printf("->(X)Can't wait Demod BISR done bit (0x%x)\n", reg_data);			
			return FAILED;
		}			
	}

	// Read BISR Status
	// ========== MISC I2C0 : Read Addr:0xc833 ==========
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c8); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000233); // DATA_CMD & Send Stop

	// Wait MISC I2C0 transfer done, Check STOP_DET=1
	for(i=0; i<=Scan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
			break;
		else if(i==Scan)
	   	{
			printf("->(5)Can't wait MISC I2C0 transfer done!\n"); 
		   	return FAILED;
  	 	}
  	}
	//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();	

	rtd_outl(IC0_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read)

	// Wait MISC I2C0 transfer done, Check STOP_DET=1
	for(i=0; i<=Scan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
			break;
		else if(i==Scan)
	   	{
			printf("->(6)Can't wait MISC I2C0 transfer done!\n"); 
		   	return FAILED;
  	 	}
  	}
	//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();	

	// Read 0xc833
	reg_data = rtd_inl(IC0_DATA_CMD_reg);
	if ((reg_data & 0xff) == 0x00) // No BISR_FAIL
	{ 
		// Set Hold BISR
		// ========== MISC I2C0 : Write Addr:0xc01a, Data:0x03 (hold bisr) ==========
		rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
		rtd_outl(IC0_DATA_CMD_reg, 0x0000001a); // DATA_CMD
		rtd_outl(IC0_DATA_CMD_reg, 0x00000203); // DATA_CMD & Send Stop

		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		for(i=0; i<=Scan; i++)
		{  
			udelay(100);  	 
			// Wait MISC I2C0 transfer done, Check STOP_DET=1
			if ((rtd_inl(IC0_RAW_INTR_STAT_reg) & 0x200) == 0x200)
				break;
			else if(i==Scan)
		   	{
				printf("->(7)Can't wait MISC I2C0 transfer done!\n"); 
			   	return FAILED;
	  	 	}
	  	}
		//rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
Clear_I2C0_Sts();		
	} 
	else 
	{
    	printf("->(X)Demod BISR failed\n");
		return FAILED;
	}

	printf("->(V)Demod BISR pass!\n");  
	return SUCCESS;
}
#endif
#if 0
int Demod_BISR(void)
{
	UINT8 bScan = 10000;
	UINT8 loop = 50;
	int reg_data, tmp_data;
	int i, j;

    //I2C0 clock enable
    rtd_setbits(CRT_ST_CLKEN0_VADDR, BIT6);
    rtd_clearbits(CRT_ST_CLKEN0_VADDR, BIT6);
    rtd_clearbits(CRT_ST_SRST0_VADDR, BIT6);
    rtd_setbits(CRT_ST_SRST0_VADDR, BIT6);
    rtd_setbits(CRT_ST_CLKEN0_VADDR, BIT6);
    //Global I2C0 INT
    //rtd_outl(0xb8062100,0x00000002);//Clear I2C0_INT read only
    rtd_outl(ISO_MISC_OFF_INT_EN_reg, (rtd_inl(ISO_MISC_OFF_INT_EN_reg)|0x2));//Clear I2C0_INT
	
	/* ========== Configuration MISC I2C0 ========== */
	rtd_outl(0xb80602a0, 0x00000000);
	rtd_outl(0xb806266c, 0x00000000);
	rtd_outl(0xb8062630, 0x00000000);
	rtd_outl(0xb8062604, 0x00000012);
	rtd_outl(0xb8062600, 0x00000025);
	rtd_outl(0xb8062608, 0x00000055);
	rtd_outl(0xb806260c, 0x00000002);
	rtd_outl(0xb8062614, 0x00000060);
	rtd_outl(0xb8062618, 0x000000b0);
	rtd_outl(0xb806261c, 0x0000001a);
	rtd_outl(0xb8062620, 0x00000030);
	rtd_outl(0xb8062624, 0x00000020);
	rtd_outl(0xb8062628, 0x00000026);
	rtd_outl(0xb806263c, 0x00000000);
	rtd_outl(0xb8062638, 0x00000002);
	rtd_outl(0xb806266c, 0x00000001);
	printf("Configuration MISC I2C0\n");
	//rtd_inl(IC1_COMP_PARAM_1_reg); // I2C0 Component Parameter Register 1

	/* ========== MISC I2C0 : Write Addr:0xf001, Data:0x01 ========== */
	rtd_outl(IC0_DATA_CMD_reg, 0x000000f0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000001); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  		break;
	   	else if(i==bScan)
	   	{
			printf("->(I)Can't wait MISC I2C0 transfer done!\n"); 
		   	return FAILED;
  	 	}
  	}
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
    //rtd_outl(0xb806266c, 0x00000000);
    //rtd_outl(0xb806266c, 0x00000001);

	/* ========== MISC I2C0 : Write Addr:0xe40e, Data:0x01 ========== */
	rtd_outl(IC0_DATA_CMD_reg, 0x000000e4); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x0000000e); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(II)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	} 	
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET 	
    //rtd_outl(0xb806266c, 0x00000000);
    //rtd_outl(0xb806266c, 0x00000001);  	

	/* ========== MISC I2C0 : Write Addr:0xc017, Data:0x01 ========== */
	//notice!! shotern drf bist time
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000017); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(III)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}	
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);  	

	/* ========== MISC I2C0 : Write Addr:0xc018, Data:0x00 ========== */
	// notice!! shotern drf bist time
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000018); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000200); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(IV)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}  
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);  	

	/* ========== MISC I2C0 : Write Addr:0xc001, Data:0x01 ========== */
	// Release reg soft rst
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000001); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(V)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}  
	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);	

	/* ========== MISC I2C0 : Write Addr:0xc016, Data:0x01 ========== */
	//Release reg bisr rst
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000016); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop
 
	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(VI)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}   
	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);	

	/* ========== MISC I2C0 : Write Addr:0xc016, Data:0x01 ========== */
	//Release reg bisr rst
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000016); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop
 
	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(VII)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}   
	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);	

	/* ========== MISC I2C0 : Read Addr:0xc83e (Check BISR Done) ========== */
	// 0xc83e {3'b0, dmbt_bisr_done_all, ldpc_bisr_done, outer_bisr_done[1:0], inrx_bisr_done}
	for(j=0; j<=loop; j++)
	{
		rtd_outl(IC0_DATA_CMD_reg, 0x000000c8); // DATA_CMD
		rtd_outl(IC0_DATA_CMD_reg, 0x0000023e); // DATA_CMD & Send Stop
    
		for(i=0; i<=bScan; i++)
		{  
			udelay(100);  	 
			// Wait MISC I2C0 transfer done, Check STOP_DET=1
			if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
		  	 	break;
		   	else if(i==bScan)
		   	{
		 	   	printf("->(VIII)Can't wait MISC I2C0 transfer done!\n");	 	
			   	return FAILED;
	  	 	}
	  	}  			
	    rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	    
    	rtd_outl(0xb806266c, 0x00000000);
    	rtd_outl(0xb806266c, 0x00000001);	    
	    
	    rtd_outl(IC0_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read & Send Stop)
    
		for(i=0; i<=bScan; i++)
		{  
			udelay(100);  	 
			// Wait MISC I2C0 transfer done, Check STOP_DET=1
			if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
		  	 	break;
		   	else if(i==bScan)
		   	{
		 	   	printf("->(VIIII)Can't wait MISC I2C0 transfer done!\n");	 	
			   	return FAILED;
	  	 	}
	  	} 
		rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET
    	rtd_outl(0xb806266c, 0x00000000);
	    rtd_outl(0xb806266c, 0x00000001);

		reg_data = rtd_inl(IC0_DATA_CMD_reg); // Read DATA_CMD Value
		tmp_data = reg_data;
		if ((tmp_data & 0x1f) == 0x1f) //or 0x1f?????
		{ // check dmbt_bisr_done_all
			printf("->(V)Demod BISR done\n");
			break;
		}
		else if (j==loop)
		{
			printf("->(X)Can't wait Demod BISR done bit (0x%x)\n", tmp_data);
			
			return FAILED;
		}		
	}  

	/* ========== MISC I2C0 : Read Addr:0xc833 (Check ) ========== */
	// 0xc833 {1'b0, ldpc_bisr_fail,outer_bisr_fail[1:0],inrx_bisr_fail[3:0]}
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c8); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000233); // DATA_CMD & Send Stop
    
	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(X)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}  		
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);
	
  	rtd_outl(IC0_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read & Send Stop)
  
	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(XI)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}  	
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET 	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);
	
  	reg_data = rtd_inl(IC0_DATA_CMD_reg); // Read DATA_CMD Value
  	tmp_data = reg_data;
  	if ((tmp_data & 0xff) != 0x0)
	{ 
    	printf("->(X)Demod BISR failed\n");
		return FAILED;
  	}

	// ===========================================================================
	// HOLD BISR 

	/* ========== MISC I2C0 : Write Addr:0xc01a, Data:0x07 ========== */
	// Set bit2~bit0
	rtd_outl(IC0_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x0000001a); // DATA_CMD
	rtd_outl(IC0_DATA_CMD_reg, 0x00000207); // DATA_CMD & Send Stop

	for(i=0; i<=bScan; i++)
	{  
		udelay(100);  	 
		// Wait MISC I2C0 transfer done, Check STOP_DET=1
		if((rtd_inl(IC0_RAW_INTR_STAT_reg)&0x710) == 0x710)
	  	 	break;
	   	else if(i==bScan)
	   	{
	 	   	printf("->(XII)Can't wait MISC I2C0 transfer done!\n");	 	
		   	return FAILED;
  	 	}
  	}   		
  	rtd_inl(IC0_CLR_STOP_DET_reg); // Clear STOP_DET	
    rtd_outl(0xb806266c, 0x00000000);
    rtd_outl(0xb806266c, 0x00000001);

  	printf("->(V)Demod BISR pass!\n");  
	return SUCCESS;
}
#endif
int ACPU_BISR(void)
{
	UINT16 i;
	UINT8 bScan = 100;
	int   bStatus = SUCCESS;   
	
	//ACPU clock enable
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
	rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
	rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22); // aio, ae
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6); // ade, acpu
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
	rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
	udelay(10);
	// rst = 1
	rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);
	rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT0);
	rtd_setbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);
	udelay(10);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
	rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);
	
	//BISR reset
	rtd_maskl(ACPU_BISR_RSTN, ~(BIT1|BIT0), (BIT1|BIT0));
	rtd_setbits(CRT_CRT_BISR_PWR_RSTN1_VADDR, _BIT1 | _BIT0); //power reset
	
	for(i=0;i<=bScan;i++)
	{
		udelay(100);
		if((rtd_inl(ACPU_BISR_DONE)&BIT0) == BIT0)
		{
			if(rtd_inl(ACPU_BISR_FAIL) == 0) //no fail signal
			{
				rtd_maskl(ACPU_BISR_REMAP, ~(BIT1|BIT0), (BIT1|BIT0)); //hold remap				
				printf("->(V)ACPU BISR(reset BISR and hold remap)\n");
				break;
			}
			else
			{
				printf("->(X)ACPU BISR group fail(reset BISR)!\n");
				bStatus = FAILED;
			}
		}
		else if(i == bScan)
		{
			printf("->(X)ACPU BISR(reset BISR failed)\n");
			bStatus = FAILED;
		}
	}
	
	if((rtd_inl(ACPU_BISR_REMAP)&BIT1) == BIT1)
	{
		printf("->(V)ACPU BISR(reset BISR and hold remap)\n");
		return bStatus;
	}
	else
	{
		printk("->(X)ACPU BISR(hold remap set fail)!\n");
		return FAILED;
	}
}

int KCPU_BISR(void)
{
	UINT16 i;
	UINT8 bScan = 10;
	int   bStatus = SUCCESS;
	
	if((rtd_inl(KCPU_BISR_REMAP)&BIT3) == BIT3) //hold remap
		printf("->(V)KCPU BISR(set hold remap in ROM code)\n");
	else	
	{
		//KCPU reset	
		//BISR reset
		rtd_maskl(KCPU_BISR_RSTN, ~BIT3, BIT3);
		rtd_maskl(0xb8000590, ~(BIT3|BIT0), (BIT3|BIT0)); //power reset
		
		for(i=0;i<=bScan;i++)
		{
			udelay(100);
			if((rtd_inl(KCPU_BISR_DONE)&BIT5) == BIT5)
			{
				if(rtd_inl(KCPU_BISR_FAIL) == 0) //no fail signal
				{
					rtd_maskl(KCPU_BISR_REMAP, ~BIT3, BIT3); //hold remap				
					printf("->(V)KCPU BISR(reset BISR and hold remap)\n");
					break;
				}
				else
				{
					printf("->(X)KCPU BISR group fail(reset BISR)!\n");
					bStatus = FAILED;
				}
			}
			else if(i == bScan)
			{
				printf("->(X)KCPU BISR(reset BISR failed)\n");
				bStatus = FAILED;
			}
		}					
	}
	return bStatus;
}

int CP42K_BISR(void)
{
	UINT16 i;
	UINT8 bScan = 10;
	int   bStatus = SUCCESS;
	
	if((rtd_inl(CP42K_BISR_REMAP)&BIT4) == BIT4) //hold remap
		printf("->(V)CP42K BISR(set hold remap in ROM code)\n");
	else	
	{
		//CP42K reset		
		//BISR reset
		rtd_maskl(CP42K_BISR_RSTN, ~BIT4, BIT4);
		rtd_maskl(0xb8000590, ~(BIT4|BIT0), (BIT4|BIT0)); //power reset
		
		for(i=0;i<=bScan;i++)
		{
			udelay(100);
			if((rtd_inl(CP42K_BISR_DONE)&BIT3) == BIT3)
			{
				if(rtd_inl(CP42K_BISR_FAIL) == 0) //no fail signal
				{
					rtd_maskl(CP42K_BISR_REMAP, ~BIT4, BIT4); //hold remap				
					printf("->(V)CP42K BISR(reset BISR and hold remap)\n");
					break;
				}
				else
				{
					printf("->(X)CP42K BISR group fail(reset BISR)!\n");
					bStatus = FAILED;
				}
			}
			else if(i == bScan)
			{
				printf("->(X)CP42K BISR(reset BISR failed)\n");
				bStatus = FAILED;
			}
		}					
	}
	return bStatus;
}

int DISPI_BISR(void)
{
	UINT16 i;
	UINT8 bScan = 100;
	int   bStatus = SUCCESS;
	
	if((rtd_inl(DISPI_BISR_DONE)&0x0b000000) == 0x0b000000) //done[27,25:24]
	{	
		if(rtd_inl(DISPI_BISR_FAIL) == 0) //no fail signal
		{
			if((rtd_inl(DISPI_BISR_REMAP)&0xb) != 0xb) //hold remap[3,1:0]
				rtd_maskl(DISPI_BISR_REMAP, ~0xb, 0xb); 
		
			printf("->(V)DISPI BISR\n");
		}
		else
		{
			printf("->(X)DISPI BISR group fail!\n");
			bStatus = FAILED;
		}
	}
	else	
	{
		//BISR reset
		rtd_maskl(DISPI_BISR_RSTN, ~0xF, 0xF);
		for(i=0;i<=bScan;i++)
		{
			udelay(100);
			if((rtd_inl(DISPI_BISR_DONE)&0x0b000000) == 0x0b000000) //done[27,25:24]
			{
				if(rtd_inl(DISPI_BISR_FAIL) == 0) //no fail signal
				{
					rtd_maskl(DISPI_BISR_REMAP, ~0xb, 0xb); //hold remap[3,1:0]				
					break;
				}
				else
				{
					printf("->(X)DISPI BISR group fail(reset BISR)!\n");
					bStatus = FAILED;
				}
			}
			else if(i == bScan)
			{
				printf("->(X)DISPI BISR(reset BISR failed)\n");
				bStatus = FAILED;
			}
		}					
	}
	
	if((rtd_inl(DISPI_BISR_REMAP)&0xb) == 0xb)
	{
		printf("->(V)DISPI BISR(reset BISR and hold remap)\n");
		return bStatus;
	}
	else
	{
		printk("->(X)DISPI BISR(hold remap set fail)!\n");
		return FAILED;
	}
}

int SCPU_BISR(void)
{
	UINT16 i;
	UINT8 bScan = 100;
	int   bStatus = SUCCESS;
	
	if((rtd_inl(SCPU_BISR_DONE)&BIT0) == BIT0) //done
	{	
		if(rtd_inl(SCPU_BISR_FAIL) == 0) //no fail signal
		{
			if((rtd_inl(SCPU_BISR_REMAP)&BIT0) != BIT0) //hold remap
			{
				rtd_maskl(SCPU_BISR_REMAP, ~BIT0, BIT0); 
			}		
			printf("->(V)SCPU BISR(hold remap)\n");
		}
		else
		{
			printf("->(X)SCPU BISR group fail!\n");
			bStatus = FAILED;
		}
	}
	else	
	{
		//SCPU BISR reset
		rtd_maskl(SCPU_BISR_RSTN, ~BIT0, BIT0);
		rtd_maskl(0xb801CA98, ~BIT0, BIT0); //power reset
		for(i=0;i<=bScan;i++)
		{
			udelay(100);
			if((rtd_inl(SCPU_BISR_DONE)&BIT0) == BIT0)
			{
				if(rtd_inl(SCPU_BISR_FAIL) == 0) //no fail signal
				{
					rtd_maskl(SCPU_BISR_REMAP, ~BIT0, BIT0); //hold remap				
					break;
				}
				else
				{
					printf("->(X)SCPU BISR group fail(reset BISR)!\n");
					bStatus = FAILED;
				}
			}
			else if(i == bScan)
			{
				printf("->(X)SCPU BISR(reset BISR failed)\n");
				bStatus = FAILED;
			}
		}					
	}
	
	if((rtd_inl(SCPU_BISR_REMAP)&BIT0) == BIT0)
	{
		printf("->(V)SCPU BISR(reset BISR and hold remap)\n");
		return bStatus;
	}
	else
	{
		printk("->(X)SCPU BISR(hold remap set fail)!\n");
		return FAILED;
	}		
}

int VCPU_BISR(void)
{
	UINT8 i;
	UINT8 bScan = 100;
	int   bStatus = SUCCESS;

	rtd_outl(0xb801a000, 0x1); //hold HW semaphore

	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// rst = 1
	rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
	
	rtd_setbits(CRT_CRT_BISR_RSTN1_VADDR, _BIT2 | _BIT0); //bisr reset
	rtd_setbits(CRT_CRT_BISR_PWR_RSTN1_VADDR, _BIT2 | _BIT0); //bisr power reset

	for(i=0;i<=bScan;i++)
	{
		udelay(100);
		if((rtd_inl(VCPU_BISR_DONE)&BIT4) == BIT4)
		{
			if((rtd_inl(VCPU_BISR_FAIL)&0xf) == 0) //no fail signal
			{
				rtd_maskl(VCPU_BISR_REMAP, ~(BIT2|BIT0), (BIT2|BIT0)); //hold remap				
				break;
			}
			else
			{
				printf("->(X)VCPU BISR group fail(reset BISR)!\n");
				bStatus = FAILED;
			}
		}
		else if(i == bScan)
		{
			printf("->(X)VCPU BISR(reset BISR failed)\n");
			bStatus = FAILED;
		}
	}
	
	if((rtd_inl(VCPU_BISR_REMAP)&BIT2) == BIT2)
	{
		printf("->(V)VCPU BISR(reset BISR and hold remap)\n");
		return bStatus;
	}
	else
	{
		printk("->(X)VCPU BISR(hold remap set fail)!\n");
		return FAILED;
	}

#if 0	
	udelay(100);
	while(!(rtd_inl(0xb8001120) & _BIT4)) 
	{
		bScan--;
		udelay(100);
		if( bScan == 0 )
		{
			printf("->(X)VCPU BISR(reset BISR fail)\n");
			bStatus = FAILED;
			break;
		}
	}

	if(bStatus == SUCCESS)
	{
		if((rtd_inl(VCPU_BISR_FAIL)&(0xf)) == 0) //no fail
			rtd_maskl(VCPU_BISR_REMAP, ~(BIT2|BIT0), (BIT2|BIT0));

		printf("VCPU_BISR_FAIL = 0x%x\n",rtd_inl(VCPU_BISR_FAIL));
					
		if((rtd_inl(VCPU_BISR_REMAP)&BIT2) == BIT2)
		{
			printf("->(V)VCPU BISR(reset BISR and hold remap)\n");
			bStatus = SUCCESS;
		}
		else
		{
			printf("->(X)VCPU BISR(hold remap fail)\n");
			bStatus = FAILED;
		}
	}
	rtd_outl(0xb801a000, 0x0); //release HW semaphore
	return bStatus;
#endif	
}

int QC_Verifier_BISR(void)
{
	int bStatus[7];
	UINT8 i, item=7;

	bStatus[0] = SCPU_BISR();
	bStatus[1] = VCPU_BISR();
	bStatus[2] = DISPI_BISR();
	bStatus[3] = ACPU_BISR();
	bStatus[4] = KCPU_BISR(); //did in ROM code	
	bStatus[5] = CP42K_BISR(); //did in ROM code	
	//bStatus[6] = Demod_BISR();

	for(i = 0; i < item; i++)
	{
		if(bStatus[i] == FAILED)
			return FAILED;
	}
	return SUCCESS;
} 
