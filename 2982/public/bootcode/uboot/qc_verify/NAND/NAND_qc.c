#include <qc_verify_common.h>
int QC_Verifier_NAND(void)
{

#define NAND_src_clk 0x00000100
#define NAND_T3 0x02
#define NAND_T2 0x03  
#define NAND_T1 0x02 
#define READ_program_EDO 0x20
#define EARSE_EDO  0x30

//#define NAND_src_clk 0x100
//#define NAND_T3 0x01
//#define NAND_T2 0x01  
//#define NAND_T1 0x01 
//#define READ_program_EDO 0x00
//#define EARSE_EDO  0x00

//#define NAND_PAGE_SIZE 2048  
typedef struct    //芯片的ID信息
{
 UINT32 IDm; //厂商ID
 UINT32 IDd; 
 UINT32 ID3rd;
 UINT32 ID4th;
 UINT32 ID5th;
} Simple;
 Simple nand_id;

 UINT32 xfer_cmd_flag;
 UINT32 xfer_adr_flag;
 UINT32 xfer_data1_flag;
 UINT32 xfer_data2_flag;
 UINT32 xfer_data3_flag;
 UINT32 xfer_data4_flag;
 UINT32 xfer_data5_flag;
 UINT32 earse_trig_flag;
 UINT32 earse_trig_poll;                  
 UINT32 program_DMA_flag;
 UINT32 program_DMA_xfer;
 UINT32 program_trig_poll;
 UINT32 read_DMA_flag;
 UINT32 read_DMA_xfer;
 UINT32 ECC_flag;
 UINT32 R_xfer_cmd_flag;
 UINT32 reset_trig_poll;
 UINT32 status_xfer_cmd_flag;
 UINT32 status_xfer_data_flag;
 UINT32 status_reg;
 
 
 UINT32 insert0_xfer_addr_flag;
 UINT32 insert0_xfer_data_flag;
 UINT32 insert0_xfer_cmd2_flag;
 UINT32 insert0_trig_poll;
 UINT32 blankcheck_readDMA_flag;
 UINT32 blankcheck_readDMA_xfer;
 UINT32 blankcheck_ecc;
 UINT32 blankcheck_zeronum;
 UINT32 blankcheck_allone;
 
 int read_ID_flag=1;
 int earse_flag=1;
 int program_DMA=1;
 int read_DMA=1;
 int i;
 
/////rtd_maskl(0xb8000830, 0x0000001f, 0x00000000); //CLE WR CE0
rtd_maskl(0xb8000828, 0xffffc01f, 0x00000000); //CE0 176pin
rtd_maskl(0xb8000830, 0x00002fff, 0x00000000); //CLE WR
rtd_maskl(0xb8000834, 0x007fc01f, 0x00000000); //ALE D0
rtd_maskl(0xb8000838, 0x0000001f, 0x00000000); //D1 D2 D3
rtd_maskl(0xb800083c, 0x0000001f, 0x00000000); //D4 D5 D6
rtd_maskl(0xb8000840, 0x00003fff, 0x00000000); //D7  RD
rtd_maskl(0xb8000844, 0xffffc01f, 0x00000000); //RDY 176pin
//rtd_maskl(0xb8000844, 0xff80001f, 0x00000000); //RDY CE0 BGA
////rtd_maskl(0xb8000820, 0xff803fff, 0x00000000); //WP#

/////rtd_maskl(0xb8000214, 0xfffff8ff, 0x00000100); 
 rtd_outl(0xb8000038, 0x00000001); 
     
     
    
     rtd_outl(0xb8010234, NAND_T3);
     rtd_outl(0xb8010238, NAND_T2);
     rtd_outl(0xb801023c, NAND_T1);
     rtd_outl(0xb8010130, 0x1E);
     //rtd_outl(0xb801027c, 0x00);
     rtd_outl(0xb801027c, READ_program_EDO);
     rtd_outl(0xb8010228, 0x00);  
     
       //**reset**//
       rtd_outl(0xb8010010, 0xFF);
       rtd_outl(0xb8010018, 0x80);
     printk("reset xfer command flag=%X\n", rtd_inl(0xb8010018));
     for(i=0;i<=20;i++)
     {
     	R_xfer_cmd_flag=rtd_inl(0xb8010018)&0x80;
     	if(R_xfer_cmd_flag==0x00000000)
     		{
     			printk("reset xfer command flag=%X\n", R_xfer_cmd_flag);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("reset xfer command flag=%X\n", R_xfer_cmd_flag);
     			printk("reset xfer command failed...");
     		}	
     	}
     	
     	rtd_outl(0xb8010030, 0xd);
     for(i=0;i<=2000;i++)
     {
     	reset_trig_poll= rtd_inl(0xb8010030);
     	if(reset_trig_poll==0xc)
     		{
     			printk("reset trig poll=%X\n",reset_trig_poll);
     		break;
     		}
     	else if(i==2000)
     		{
     			printk("reset trig poll=%X\n",reset_trig_poll);
     			printk("reset Trigger polling Flash Status busy...\n");
     		}	
     	}
     	
//int nand_read_id(void)
//{
     rtd_outl(0xb8010104, 0x80);
      printk("xfer command flag=%X\n", rtd_inl(0xb8010104));
     rtd_outl(0xb8010010, 0x90);
     rtd_outl(0xb8010018, 0x80);
     printk("xfer command flag=%X\n", rtd_inl(0xb8010018));
     for(i=0;i<=20;i++)
     {
     	xfer_cmd_flag=rtd_inl(0xb8010018)&0x80;
     	if(xfer_cmd_flag==0x00000000)
     		{
     			printk("xfer command flag=%X\n", xfer_cmd_flag);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer command flag=%X\n", xfer_cmd_flag);
     			printk("read id xfer command failed...");
     			return 1;
     		}	
     	}
     
     rtd_outl(0xb8010000, 0x0);
     rtd_outl(0xb8010004, 0x0);
     rtd_outl(0xb8010008, 0xE0);
     rtd_outl(0xb801002c, 0x0); 
     rtd_outl(0xb8010018, 0x81);
      for(i=0;i<=20;i++)
     {
     	xfer_adr_flag=rtd_inl(0xb8010018)&0x81;
     	if(xfer_adr_flag==0x00000001)
     		{
     			printk("xfer address flag=%X\n", xfer_adr_flag);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer address flag=%X\n", xfer_adr_flag);
     			printk("read id xfer address failed...");
     			return 1;
     		}	
     	}
     	
     
     rtd_outl(0xb8010018, 0x82);
      for(i=0;i<=20;i++)
     {
     	xfer_data1_flag=rtd_inl(0xb8010018)&0x82;
     	if(xfer_data1_flag==0x00000002)
     		{
     			printk("xfer data1 flag=%X\n", xfer_data1_flag);
     			nand_id.IDm=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer data1 flag=%X\n", xfer_data1_flag);
     			printk("read id xfer data1 failed...\n");
     			return 1;
     		}	
     	}
     
     rtd_outl(0xb8010018, 0x82);
           for(i=0;i<=20;i++)
     {
     	xfer_data2_flag=rtd_inl(0xb8010018)&0x82;
     	if(xfer_data2_flag==0x00000002)
     		{
     			printk("xfer data2 flag=%X\n", xfer_data2_flag);
     			nand_id.IDd=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20000)
     		{
     			printk("xfer data2 flag=%X\n", xfer_data2_flag);
     			printk("read id xfer data2 failed...");
     			return 1;
     		}	
     	}
    
     rtd_outl(0xb8010018, 0x82);
            for(i=0;i<=20;i++)
     {
     	xfer_data3_flag=rtd_inl(0xb8010018)&0x82;
     	if(xfer_data3_flag==0x00000002)
     		{
     			printk("xfer data3 flag=%X\n", xfer_data3_flag);
     			 nand_id.ID3rd=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer data3 flag=%X\n", xfer_data3_flag);
     			printk("read id xfer data3 failed...");
     			return 1;
     		}	
     	}
     	
     rtd_outl(0xb8010018, 0x82);
          for(i=0;i<=20;i++)
     {
     	xfer_data4_flag=rtd_inl(0xb8010018)&0x82;
     	if(xfer_data4_flag==0x00000002)
     		{
     			printk("xfer data4 flag=%X\n", xfer_data4_flag);
     			nand_id.ID4th=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer data4 flag=%X\n", xfer_data4_flag);
     			printk("read id xfer data4 failed...");
     			return 1;
     		}	
     	}
     	
     rtd_outl(0xb8010018, 0x82);
           for(i=0;i<=20;i++)
     {
     	xfer_data4_flag=rtd_inl(0xb8010018)&0x82;
     	if(xfer_data4_flag==0x00000002)
     		{
     			printk("xfer data4 flag=%X\n", xfer_data5_flag);
     			nand_id.ID5th=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("xfer data5 flag=%X\n", xfer_data5_flag);
     			printk("read id xfer data5 failed...\n");
     			return 1;
     		}	
     	}
    
     //打印ID信息
 
     printk("Read NAND Flash ID:\n");
     printk("NAND Mark code=%X\n",nand_id.IDm);
     printk("NAND Device code=%X\n",nand_id.IDd);
     printk("NAND 3rdID code=%X\n",nand_id.ID3rd);
     printk("NAND 4thID code=%X\n",nand_id.ID4th);
     printk("NAND 5thID code=%X\n",nand_id.ID5th);

     if((nand_id.IDm==0x2c)&&(nand_id.IDd==0x38)&&(nand_id.ID3rd==0x00)&&(nand_id.ID4th==0x26)&&(nand_id.ID5th==0x85)) //29f8g08abada
   {
     	printk("read id pass!\n");
      read_ID_flag=0;
     }
else if((nand_id.IDm==0xad)&&(nand_id.IDd==0xda)&&(nand_id.ID3rd==0x10)&&(nand_id.ID4th==0x95)&&(nand_id.ID5th==0x44))
{
     	printk("read id pass!\n");
      read_ID_flag=0;
     }
else if((nand_id.IDm==0x98)&&(nand_id.IDd==0xdc)&&(nand_id.ID3rd==0x90)&&(nand_id.ID4th==0x15)&&(nand_id.ID5th==0x76)) //TOSHIBA TC58NVG2S3ETAOO

     {
     	printk("read id pass!\n");
      read_ID_flag=0;
     }
     else
     	return 1;  
     	
    //**status reg**// 	
    rtd_outl(0xb8010010, 0x70);
     rtd_outl(0xb8010018, 0x80);
     printk("status_xfer command flag=%X\n", rtd_inl(0xb8010018));
     for(i=0;i<=20;i++)
     {
     	status_xfer_cmd_flag=rtd_inl(0xb8010018)&0x80;
     	if(status_xfer_cmd_flag==0x00000000)
     		{
     			printk("status_xfer command flag=%X\n", status_xfer_cmd_flag);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("status_xfer command flag=%X\n", status_xfer_cmd_flag);
     			printk("status reg check xer command failed...");
     			return 1;
     		}	
     	}
    rtd_outl(0xb8010018, 0x82);
      for(i=0;i<=20;i++)
     {
     	status_xfer_data_flag=rtd_inl(0xb8010018)&0x82;
     	if(status_xfer_data_flag==0x00000002)
     		{
     			printk("status xfer data flag=%X\n", status_xfer_data_flag);
     			status_reg=rtd_inl(0xb8010014);
     		break;
     		}
     	else if(i==20)
     		{
     			printk("status xfer data flag=%X\n", status_xfer_data_flag);
     			printk("status read failed...\n");
     			return 1;
     		}	
     	}                      
    printk("status_reg=%X\n", status_reg);
   if(status_reg==0xE0)
   	{printk("nand is not protect...\n");}
   	
   //**earse**//  
    rtd_outl(0xb8010010, 0x60);	// read id command	
    rtd_outl(0xb8010274, 0xd0);
    rtd_outl(0xb8010028, 0x70);
    rtd_outl(0xb8010000, 0x0);	 // page number
    rtd_outl(0xb8010004, 0x0);	
    rtd_outl(0xb8010008, 0x80);	
    //rtd_outl(0xb801027c, 0x10);
      rtd_outl(0xb801027c, EARSE_EDO);
    rtd_outl(0xb8010200, 0x8a);
    printk("earse trigger=%X\n",earse_trig_flag);
      for(i=0;i<=2000;i++)
     {
     	earse_trig_flag=rtd_inl(0xb8010200);
     	if(earse_trig_flag==0x0000002a)
     		{
     			printk("earse trigger=%X\n",earse_trig_flag);
     		break;
     		}
     	else if(i==2000)
     		{
     			printk("earse trigger=%X\n",earse_trig_flag);
     			printk("earse trigger failed...\n");
     			return 1;
     		}	
     	}
     	
     rtd_outl(0xb8010030, 0xd);
     for(i=0;i<=2000;i++)
     {
     	earse_trig_poll= rtd_inl(0xb8010030);
     	if(earse_trig_poll==0xc)
     		{
     			printk("earse trig poll=%X\n",earse_trig_poll);
     		break;
     		}
     	else if(i==2000)
     		{
     			printk("earse trig poll=%X\n",earse_trig_poll);
     			printk("earse Trigger polling Flash Status busy...\n");
     			return 1;
     		}	
     	}
     	
   if(earse_trig_flag==0x0000002a&&earse_trig_poll==0xc)
   	{
   		earse_flag=0;
   		printk("earse pass!\n");
   	}
   else 
   	return 1;
   	
     	//**program_DMA**//
     	 rtd_outl(0xb8010100, 0x00000000); 	     
       rtd_outl(0xb8010104, 0x00000002); 	     
       rtd_outl(0xb8010270, 0x00000004);
       rtd_outl(0xb8010228, 0x00000000);
       rtd_outl(0xb8010110, 0x00000000);
       rtd_outl(0xb801012c, 0x00000000); 
       rtd_outl(0xb801013c, 0x00000000); 
     //  rtd_outl(0xb8010348, 0x30000000);
     rtd_outl(0xb8010348, 0x30380000);
       rtd_outl(0xb8010010, 0x00000080); 
       rtd_outl(0xb8010274, 0x00000010);   
       rtd_outl(0xb8010028, 0x00000070);
       
       rtd_outl(0xb8010000, 0x00000000); 
       rtd_outl(0xb8010004, 0x00000000); 	
       rtd_outl(0xb8010008, 0x00000020); 
       rtd_outl(0xb801002c, 0x00000000); 
       rtd_outl(0xb801000c, 0x00000000);  
       rtd_outl(0xb801003c, 0x00000000); 	
       
       //rtd_outl(0xb801027c, 0x00000000);
       rtd_outl(0xb801027c, READ_program_EDO);
       
       rtd_outl(0xb8010264, 0x00000080);
      // rtd_outl(0xb8010304, 0x00002400); //Dram start address for DMA transfer.
      rtd_outl(0xb8010304,0x00300000);
       rtd_outl(0xb8010308, 0x00000004);
       
       rtd_outl(0xb801030c, 0x00000001);
       rtd_outl(0xb8010200, 0x00000081);
       	printk("program DMA trigger=%X\n",rtd_inl(0xb8010200));
       	printk("program DMA xfer=%X\n",rtd_inl(0xb801030c));
       for(i=0;i<=20000;i++)
     {
     	program_DMA_flag=rtd_inl(0xb8010200)&0x81;
     	program_DMA_xfer=rtd_inl(0xb801030c);
     	if(program_DMA_flag==0x01&&program_DMA_xfer==0x00)
     		{
     			printk("program DMA trigger=%X\n",program_DMA_flag);
     			printk("program DMA xfer=%X\n",program_DMA_xfer);
     		break;
     		}
     	else if(i==20000&&program_DMA_xfer==0x00)
     		{
     			printk("program DMA trigger\n =%X\n",program_DMA_flag);
     			printk("program DMA trigger failed...\n");
     			return 1;
     		}	
     	else if(i==20000&&program_DMA_flag==0x01)
     		{
     			printk("program DMA xfer=%X\n",program_DMA_xfer);
     			printk("program DMA xfer failed...\n");
     			return 1;
     		}	
     	else
     		{ printk("program DMA trigger=%X\n",program_DMA_flag);
     			printk("program DMA xfer=%X\n",program_DMA_xfer);
     			printk("program DMA trigger and xfer failed...");
     			return 1;
     		}
     		 
     	} 
     rtd_outl(0xb8010030, 0xd);
     for(i=0;i<=2000;i++)
     {
     	program_trig_poll=rtd_inl(0xb8010030);
     	if(program_trig_poll==0xc)
     		{
     			printk("program trig poll=%X\n",program_trig_poll);
     		break;
     		}
     	else if(i==2000)
     		{
     			printk("program trig poll=%X\n",program_trig_poll);
     			printk("program Trigger polling Flash Status busy...\n");
     			return 1;
     		}	
     	}
     	if(program_DMA_flag==0x01&&program_DMA_xfer==0x00&&program_trig_poll==0xc)
     	{
     		program_DMA=0;
     		printk("program DMA pass!\n");
     	}
     	else
     	return 1;
    	printk("read DMA!\n");  	
     	//**read DMA**//

     //	 printk("read DMA!\n");   
      // rtd_outl(0xb8010348,0x60001e00);
        rtd_outl(0xb8010348, 0x30380000);
       rtd_outl(0xb8010228, 0x00000000); 	     
       rtd_outl(0xb8010110, 0x00000002);
       rtd_outl(0xb801012c, 0x00000000);
       
       rtd_outl(0xb8010110, 0x00000000);
       
       rtd_outl(0xb8010010, 0x00000000); 	     
       rtd_outl(0xb8010274, 0x00000030); 	    
       rtd_outl(0xb8010028, 0x00000070);
       
       rtd_outl(0xb8010034, 0x00000001);
       
       rtd_outl(0xb801000c, 0x00000000);//c
       rtd_outl(0xb801003c, 0x00000000);
       
       rtd_outl(0xb8010000, 0x00000000);  //page address   
       rtd_outl(0xb8010004, 0x00000000); 	   
       rtd_outl(0xb8010008, 0x00000020);   
     	 rtd_outl(0xb801002c, 0x00000000); 
     	 
     	 //rtd_outl(0xb801027c, 0x00000000);
     	 rtd_outl(0xb801027c, READ_program_EDO); 	    
       rtd_outl(0xb8010264, 0x00000080); 
       rtd_outl(0xb8010260,0x0000004a);
       
     //   rtd_outl(0xb8010304,0x00002400);
         rtd_outl(0xb8010304,0x00300000);
       rtd_outl(0xb8010308, 0x00000004); 	//??   
       rtd_outl(0xb8010100, 0x00000000);	
     	 rtd_outl(0xb8010104, 0x00000082); 
     	 
     	 rtd_outl(0xb8010228, 0x00000080);
     	 
     	 rtd_outl(0xb8010270, 0x00000004);
     	 
     	 rtd_outl(0xb801030c, 0x00000003); 	  
       rtd_outl(0xb8010200, 0x00000082); 
       
     printk("read DMA trigger=%X\n",rtd_inl(0xb8010200));
     	printk("read DMA xfer=%X\n",rtd_inl(0xb801030c));
     
       for(i=0;i<=2000;i++)
     {
     	read_DMA_flag=rtd_inl(0xb8010200)&0x82;
     	read_DMA_xfer=rtd_inl(0xb801030c)&0x03;
     	if(read_DMA_flag==0x02&&read_DMA_xfer==0x02)
     		{
     			printk("read DMA trigger=%X\n",read_DMA_flag);
     			printk("read DMA xfer=%X\n",read_DMA_xfer);
     			printk("read DMA pass!\n");
     			read_DMA=0;
     		break;
     		}
     	else if(i==2000&&read_DMA_xfer==0x02)
     		{
     			printk("read DMA trigger=%X\n",read_DMA_flag);
     			printk("read DMA trigger failed...\n");
     			return 1;
     		}	
     	else if(i==2000&&read_DMA_flag==0x02)
     		{
     			printk("read DMA xfer=%X\n",read_DMA_xfer);
     			printk("read DMA xfer failed...\n");
     			return 1;
     		}	
     	else if(i==2000)
     		{ printk("read DMA trigger=%X\n",read_DMA_flag);
     			printk("read DMA xfer=%X\n",read_DMA_xfer);
     			printk("read DMA trigger and xfer failed...");
     			return 1;
     		}
      }
     // printk("read DMA pass!\n");
     
       
       rtd_outl(0xb8010228, 0x00000000);
       rtd_outl(0xb8010110, 0x00000002);
       printk("nand IP pass!\n");  
              
 if((read_ID_flag==0)&&(earse_flag==0)&&(program_DMA==0)&&(read_DMA==0))
 	{
 		printk("nand IP pass!\n");
 		return 0;
  }
 else
 	return 1;
                                                                      

} 
