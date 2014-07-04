#include <qc_verify_common.h>

#define PATTERN_LEN 0x76a700
#define DDR_LEN 0x20000000
#define QC_JUMP_ADDR  0xb200000
#define QC_JUMP_ADDR2 0xb280000 //end of heap (b200000~b280000)
#define QC_JUMP_ADDR3 0x2000000//0xd4000  //end of TLB (d0000~d4000)

int QC_Verifier_MD_Domain(void)
{
	int bIoStatus = SUCCESS;
	int bSts = SUCCESS;	
	UINT32 CAP_CRC = 0xbb7f471b;
	UINT32 DISP_CRC = 0xbb7f471b;
	UINT32 PANEL_CRC = 0xf928aa3;
	UINT32 FRC_ADDR, cval, tmp_addr;
	UINT16 loop, loop_max, bRound=1;	
	UINT16 i, bScan = 1;

	//-------- Module Clock & Reset Enable ---------
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000014, 0x1effffe7, 0x00000000);// disable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00000000);// hold TVSB1~3,APLL_ADC,I/M/D domain reset
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00007016);// release TVSB1~3,APLL_ADC,I/M/D domain reset
	udelay(8000);
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock
	
	#include "case8_ipg1080p_frc_fhd.tbl"
	rtd_maskl(0xb802210c, ~0x1, 0x0); //IPTG disable
	rtd_maskl(0xb802210c, ~0x1, 0x1); //IPTG enable		
	udelay(1000);
	
	//--------------------- M-domain Main channel CRC check -------------------------------------------
	for(i=0; i<=100; i++)
	{		
		udelay(1000);
		rtd_outl(0xb8025220,0x00000001); 
		while((rtd_inl(0xb8025220)&0x01) == 1);
		rtd_outl(0xb8029040,0x00000001); 
		while((rtd_inl(0xb8029040)&0x01) == 1);	

		if((rtd_inl(0xb8025224) == CAP_CRC) && (rtd_inl(0xb8029044) == DISP_CRC))
			break;	
	}	

	for(i=0; i<=bScan; i++)
	{
		rtd_outl(0xb8025220,0x00000001); 
		while((rtd_inl(0xb8025220)&0x01) == 1);		
		if(rtd_inl(0xb8025224) != CAP_CRC)
		{
			printk("%d)M domain Cap CRC fail! CRC = %x (Golden is %x)\n", i,rtd_inl(0xb8025224), CAP_CRC);
			bIoStatus = FAILED;
		}

		rtd_outl(0xb8029040,0x00000001); 
		while((rtd_inl(0xb8029040)&0x01) == 1);		
		if(rtd_inl(0xb8029044) != DISP_CRC)
		{
			printk("%d)M domain Disp FIFO CRC fail! CRC = %x (Golden is %x)\n",i, rtd_inl(0xb8029044), DISP_CRC);		
			bIoStatus = FAILED;			
		}
	}

	if(bIoStatus == SUCCESS)
		printk("M domain Capture/Display PASS.\n");
	else 
		printk("M domain Capture/Display FAIL!!!\n");
	
	//--------------------- D-domain CRC check (SFG output CRC)-------------------------------------------
	for(i=0; i<=bScan; i++)
	{
		rtd_outl(0xb802d110,0x00000001); 
		while((rtd_inl(0xb802d110)&0x01) == 1);		
		if(rtd_inl(0xb802d114) != PANEL_CRC)
		{
			printk("D-domain panel interface CRC fail! CRC = %x (Golden is %x)\n", rtd_inl(0xb802d114), PANEL_CRC);	
			printk("D-domain FAIL!!!\n");
			bSts = FAILED;
			bIoStatus = FAILED;
		}
	}
	if(bSts == SUCCESS)
		printk("D-domain PASS!!!\n");
	
 	//DDR full scan
	if(bIoStatus == FAILED)
		return FAILED;	
	else
	{	
		printk("DDR full scan from 0xab24a500 to 0xbfffffff\n");
		//scan 0x20000000 to 0xb280000
		loop_max = ((DDR_LEN - QC_JUMP_ADDR2)/PATTERN_LEN)+1;
		//loop_max = ((DDR_LEN - 0x001122c0)/PATTERN_LEN);
		FRC_ADDR = DDR_LEN-PATTERN_LEN;	
		
		rtd_outl(0xb8029040, 0x000a1800); //stop CRC
	  	rtd_maskl(0xb8028058, 0xe000ffff, 0x00010000); //iv2dv_line,[28:16]=0x1	
		rtd_maskl(0xb8028000, 0xfbffffff, 0x04000000); //frame sync mode
		rtd_outl(0xb802732c, 0x00000001); //bit0 = 1, single buffer, display enable
		rtd_outl(0xb8027220, 0x00000001); //for capture single buffer and clear FIFO
		rtd_outl(0xb8027228, 0x00000001); //enable the cap FIFO
		rtd_outl(0xb8027208, FRC_ADDR); // cap0 start address1		
		rtd_outl(0xb8028228, 0x8000000F); //enable line compare, [30]=0 once mode, line=15	
		rtd_outl(0xb8029040, 0x000a1803); //continuous mode, start CRC	
		while(rtd_inl(0xb8028228)&0x80000000); //line compare once mode status[31], HW auto clear
		rtd_maskl(0xb80280f4, ~0x10, 0x10); //line compare once mode status[4],write 1 to clear

		#if 0 //signal measurement by GPIO
		for(i = 0; i<35; i++)
		{
			#if 1
			rtd_outl(0xb8029040, 0x000a1801); //continuous mode, start CRC	//mac2 modify
			while((rtd_inl(0xb8029040)&0x1));
			tmp = (rtd_inl(0xb801bc18)&0x80000);
			rtd_maskl(0xb801bc18,0xfff7ffff,~tmp); //GPIO19		
			#else
			udelay(3000);	
			rtd_outl(0xb8028228, 0x800001F4);; //enable line cmp		
			while((rtd_inl(0xb8028228)&0x80000000)); //line compare once mode status[31]
			rtd_maskl(0xb80280f4, ~0x10, 0x10); //[4]write 1 to clear
			tmp = rtd_inl(0xb801bc18)&0x80000;				
			rtd_maskl(0xb801bc18,0xfff7ffff,~tmp); //GPIO19
		/*	#else
			rtd_outl(0xb802730c, FRC_ADDR);
			rtd_outl(0xb8027334, 0x00000007); //for display register change	
			while((rtd_inl(0xb8027334)&0x1));
			tmp = rtd_inl(0xb801bc18)&0x80000;				
			rtd_maskl(0xb801bc18,0xfff7ffff,~tmp); //GPIO19
			FRC_ADDR -= 0x10;*/
			#endif	
		}
		printk("i=%d\n",i);
		#endif
		
		for(i=0; i<=bRound; i++)
		{
			for(loop=0; loop<=(loop_max+1); loop++)
			{	
				//pattern = loop%3;			
				while(rtd_inl(0xb8028228)&0x80000000); //line compare once mode status[31], HW auto clear
				//rtd_outl(0xb802211c, pat[pattern]); //change pattern
				rtd_maskl(0xb80280f4, ~0x10, 0x10); //line compare once mode status[4],write 1 to clear
				rtd_maskl(0xb8028228, 0x7fffffff, 0x80000000); //enable line cmp
				
				if(loop < loop_max)
				{
			
					rtd_outl(0xb8027208, FRC_ADDR); //cap(N) start address1
					rtd_outl(0xb802730c, FRC_ADDR);
					rtd_outl(0xb8027334, 0x00000007); //for display register change	
				}			
	
				//check CRC of disp(N-2)
				if(loop >= 2)
				{
					cval = rtd_inl(0xb8029044); //CRC result
					tmp_addr = FRC_ADDR+PATTERN_LEN*2;
					printk("FRC addr is %x to %x\n",(tmp_addr+0xa0000000), (tmp_addr+0xa0000000+PATTERN_LEN-4));
					if (cval != DISP_CRC)
					{							
						printk(" ->Disp FIFO CRC fail = %x (Golden is %x)\n", cval, DISP_CRC);
						bIoStatus = FAILED;
					}
				}
				FRC_ADDR -= PATTERN_LEN;
			}
			if(i==0)
			{
				//scan 0xa076ff00 to 0xb200000	
				FRC_ADDR = QC_JUMP_ADDR - PATTERN_LEN;						
				loop_max = ((QC_JUMP_ADDR - QC_JUMP_ADDR3)/PATTERN_LEN);
				printk("DDR full scan from 0x%x to 0x%x\n", QC_JUMP_ADDR3, QC_JUMP_ADDR);				
			}
			/*else 
			{
				//scan 0xd4000 to 0x83e700	
				FRC_ADDR = QC_JUMP_ADDR3;						
				loop_max = 1;
			}*/
			rtd_maskl(0xb8028228,0x7fffffff, 0x80000000); //enable line compare	
		}

		if(bIoStatus == FAILED)
			return FAILED;
		else
		{	
			//rtd_maskl(0xb801bc18,0xfff7ffff,0x00000000); //for FRC test, pass=0, fail=1	
			return SUCCESS;		
		}	
	}
}
