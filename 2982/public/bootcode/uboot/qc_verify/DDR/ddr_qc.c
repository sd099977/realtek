#include <qc_verify_common.h>
#include "ddr_qc.h"

int MD_SCPU(MD_PARA *para)
{		
	#define MAC_loop 100
	UINT8 i;
	
	//SCPU command queue
	rtd_outl(para->dwCmd_addr, para->dwMD_mode);
	rtd_outl(para->dwCmd_addr+4, para->dwDest_addr);
	rtd_outl(para->dwCmd_addr+8, para->dwStr_addr);
	rtd_outl(para->dwCmd_addr+12, para->wLen);

	rtd_outl(0xb800b000, 0x00000000);
	rtd_outl(0xb800b008, 0x00000018); //flash dma done interrupt enable
	rtd_outl(0xb800b00c, para->dwCmd_addr);
	rtd_outl(0xb800b010, para->dwCmd_addr+0x100);
	rtd_outl(0xb800b014, para->dwCmd_addr);
	rtd_outl(0xb800b018, para->dwCmd_addr+0x10);
	rtd_outl(0xb800b000, MD_GO);

	for (i = 0; i<MAC_loop; i++)
	{
		udelay(0x500);
		if(((rtd_inl(0xb800b004) & 0x08) == 0x08) && ((rtd_inl(0xb800b000) & 0x08) == 0x08)) //flash dma done, smq_empty
			break;
	}	
	if (i==MAC_loop)
	{
		printk("Reset %x to %x by MD is fail!\n",para->dwDest_addr, (para->dwDest_addr+0xffffc));
		return FAILED;
	}
}

int QC_Verifier_DDR(void)
{
	MD_PARA MD;
	UINT32 CMD_addr = 0xA2000000;
	UINT32 Str_addr = 0xA1000000;
	UINT32 Dest_addr[3] = {0xA2300000, 0xA1800000, 0xA2700000};
	UINT32 wLen = 0x100000; //1MB
	UINT32 i, str_val, dest_val[3];	
	UINT32 dwDC_PICT_SET;	
	UINT16 wPic_w_scale;
	UINT16 wBlk_w = 2048;
	UINT16 wBlk_h = 512;
	UINT16 wY_Blk = 0;
	UINT16 wX_Blk = 0;

	//MD reset
	rtd_maskl(0xb8000000, 0xfbffffff, 0x00000000);
	rtd_maskl(0xb8000000, 0xfbffffff, 0x04000000);	
	udelay(0x100);

	// memory set
	MD.dwMD_mode = (1<<INPUT_SEL_OFFSET)|(SEQ2SEQ<<MD_MODE_OFFSET)|NORMAL_MODE; //fill constant value
	MD.dwCmd_addr = CMD_addr;		
	MD.wLen = wLen; //1MB = wBlk_w * wBlk_h
	if(wLen = LEN_1MB)
		MD.wLen = 0;
	
	for (i = 0; i < 3; i++)
	{   
		MD.dwDest_addr = Dest_addr[i];		
		MD.dwStr_addr = i; //constant value		
		MD_SCPU(&MD);
	}

	// memory set
	MD.dwMD_mode = (1<<INPUT_SEL_OFFSET)|(SEQ2SEQ<<MD_MODE_OFFSET)|NORMAL_MODE; //fill constant value
	MD.dwCmd_addr = CMD_addr;		
	MD.wLen = wLen; //1MB = wBlk_w * wBlk_h
	if(wLen = LEN_1MB)
		MD.wLen = 0;
	
	for (i = 0; i < 3; i++)
	{   
		MD.dwDest_addr = Dest_addr[i];		
		MD.dwStr_addr = i; //constant value
		MD_SCPU(&MD);		
	}	

	//seq2seq
	MD.dwMD_mode = (0<<INPUT_SEL_OFFSET)|(SEQ2SEQ<<MD_MODE_OFFSET)|NORMAL_MODE;
	MD.dwStr_addr = Str_addr;
	MD.dwDest_addr = Dest_addr[0];
	MD.dwCmd_addr = CMD_addr+0x10;	
	MD_SCPU(&MD);
	
	//seq2blk
	wPic_w_scale = (wBlk_w/WIDTH_UNIT)+1;
	dwDC_PICT_SET = (wPic_w_scale<<PICT_W_SCALE_OFFSET)|0;	
	rtd_outl(0xb8008000, dwDC_PICT_SET); //width scale = 9, if w_scale=1 the max width is 256	

	MD.dwMD_mode = (wBlk_h<<H_BLK_OFFSET)|(wBlk_w<<W_BLK_OFFSET)|(SEQ2BLK<<MD_MODE_OFFSET)|NORMAL_MODE;
	MD.dwDest_addr = (wY_Blk<<Y_BLK_OFFSET)|(wX_Blk<<X_BLK_OFFSET); //x, y coordinates
	MD.dwStr_addr = Dest_addr[0]; //str addr of seq
	MD.dwCmd_addr = CMD_addr+0x20; 
	MD_SCPU(&MD);

	//blk2seq
	MD.dwMD_mode = (wBlk_h<<H_BLK_OFFSET)|(wBlk_w<<W_BLK_OFFSET)|(BLK2SEQ<<MD_MODE_OFFSET)|NORMAL_MODE;
	MD.dwDest_addr = (wY_Blk<<Y_BLK_OFFSET)|(wX_Blk<<X_BLK_OFFSET); //x, y coordinates
	MD.dwStr_addr = Dest_addr[1]; //str addr of seq
	MD.dwCmd_addr = CMD_addr+0x30; 
	MD_SCPU(&MD);
	
	//seq2seq
	MD.dwMD_mode = (0<<INPUT_SEL_OFFSET)|(SEQ2SEQ<<MD_MODE_OFFSET)|NORMAL_MODE;
	MD.dwStr_addr = Dest_addr[1];
	MD.dwDest_addr = Dest_addr[2];
	MD.dwCmd_addr = CMD_addr+0x40;
	MD_SCPU(&MD);	

	//data check
	for( i = 0; i < wLen; i=i+4)
	{
		str_val = rtd_inl(Str_addr+i);
		dest_val[0] = rtd_inl(Dest_addr[0]+i);
		dest_val[1] = rtd_inl(Dest_addr[1]+i);
		dest_val[2] = rtd_inl(Dest_addr[2]+i);		
		if((str_val != dest_val[0]) || (str_val != dest_val[1]) || (str_val != dest_val[2]))
		{
			if (str_val != dest_val[0])
			{
				printk("MD fail! Test range is 0x%x to 0x%x\n", Dest_addr[0], (Dest_addr[0]+0xffffc));	
				return FAILED;
			}
			else if (str_val != dest_val[1])
			{
				printk("MD fail! Test range is 0x%x to 0x%x\n", Dest_addr[1], (Dest_addr[1]+0xffffc));	
				return FAILED;			
			}
			else
			{
				printk("MD fail! Test range is 0x%x to 0x%x\n", Dest_addr[2], (Dest_addr[2]+0xffffc));	
				return FAILED;						
			}
		}			
	}
	return SUCCESS;	
}
