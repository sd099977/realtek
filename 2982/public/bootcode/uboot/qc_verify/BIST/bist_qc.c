#include <qc_verify_common.h>
#include "bist_qc.h"

#define BIST_NUM 52
typedef struct
{
	char *flag;
	UINT32 set_addr;    
	UINT32 done_addr;     
	UINT32 fail_addr;
	UINT16 set_bit;
	UINT16 done_bit;
	UINT16 fail_bit;  
} BIST_ADDR;

BIST_ADDR   Bist_test[] = {
 {"ACPU", ACPU_BIST_ADDR, ACPU_BIST_DONE_ADDR, ACPU_BIST_FAIL_ADDR, ACPU_BIST_SET_BIT, ACPU_BIST_DONE_BIT, ACPU_BIST_FAIL_BIT}, 	
 {"AE", AE_BIST_ADDR, AE_BIST_DONE_ADDR, AE_BIST_FAIL_ADDR, AE_BIST_SET_BIT, AE_BIST_DONE_BIT, AE_BIST_FAIL_BIT}, 
 {"DISPI", DISPI_BIST_ADDR, DISPI_BIST_DONE_ADDR, DISPI_BIST_FAIL_ADDR, DISPI_BIST_SET_BIT, DISPI_BIST_DONE_BIT, DISPI_BIST_FAIL_BIT},
 {"DISPM", DISPM_BIST_ADDR, DISPM_BIST_DONE_ADDR, DISPM_BIST_FAIL_ADDR, DISPM_BIST_SET_BIT, DISPM_BIST_DONE_BIT, DISPM_BIST_FAIL_BIT},
 {"DISPD", DISPD_BIST_ADDR, DISPD_BIST_DONE_ADDR, DISPD_BIST_FAIL_ADDR, DISPD_BIST_SET_BIT, DISPD_BIST_DONE_BIT, DISPD_BIST_FAIL_BIT}, 
 {"VODMA", VODMA_BIST_ADDR, VODMA_BIST_DONE_ADDR, VODMA_BIST_FAIL_ADDR, VODMA_BIST_SET_BIT, VODMA_BIST_DONE_BIT, VODMA_BIST_FAIL_BIT},
 {"VODMA2", VODMA2_BIST_ADDR, VODMA2_BIST_DONE_ADDR, VODMA2_BIST_FAIL_ADDR, VODMA2_BIST_SET_BIT, VODMA2_BIST_DONE_BIT, VODMA2_BIST_FAIL_BIT},
 {"VODMA3", VODMA3_BIST_ADDR, VODMA3_BIST_DONE_ADDR, VODMA3_BIST_FAIL_ADDR, VODMA3_BIST_SET_BIT, VODMA3_BIST_DONE_BIT, VODMA3_BIST_FAIL_BIT},
 {"VODMA4", VODMA4_BIST_ADDR, VODMA4_BIST_DONE_ADDR, VODMA4_BIST_FAIL_ADDR, VODMA4_BIST_SET_BIT, VODMA4_BIST_DONE_BIT, VODMA4_BIST_FAIL_BIT},
 {"AUDIO", AUDIO_BIST_ADDR, AUDIO_BIST_DONE_ADDR, AUDIO_BIST_FAIL_ADDR, AUDIO_BIST_SET_BIT, AUDIO_BIST_DONE_BIT, AUDIO_BIST_FAIL_BIT},
 {"CP", CP_BIST_ADDR, CP_BIST_DONE_ADDR, CP_BIST_FAIL_ADDR, CP_BIST_SET_BIT, CP_BIST_DONE_BIT, CP_BIST_FAIL_BIT},
 {"DCPHY", DCPHY_BIST_ADDR, DCPHY_BIST_DONE_ADDR, DCPHY_BIST_FAIL_ADDR, DCPHY_BIST_SET_BIT, DCPHY_BIST_DONE_BIT, DCPHY_BIST_FAIL_BIT},
 {"DISP2TVE", DISP2TVE_BIST_ADDR, DISP2TVE_BIST_DONE_ADDR, DISP2TVE_BIST_FAIL_ADDR, DISP2TVE_BIST_SET_BIT, DISP2TVE_BIST_DONE_BIT, DISP2TVE_BIST_FAIL_BIT}, //DISP2TVE_HD
 {"DISP2TVE2", DISP2TVE2_BIST_ADDR, DISP2TVE2_BIST_DONE_ADDR, DISP2TVE2_BIST_FAIL_ADDR, DISP2TVE2_BIST_SET_BIT, DISP2TVE2_BIST_DONE_BIT, DISP2TVE2_BIST_FAIL_BIT}, //DISP2TVE_SD
 {"DISP2TVE3", DISP2TVE3_BIST_ADDR, DISP2TVE3_BIST_DONE_ADDR, DISP2TVE3_BIST_FAIL_ADDR, DISP2TVE3_BIST_SET_BIT, DISP2TVE3_BIST_DONE_BIT, DISP2TVE3_BIST_FAIL_BIT}, //DISP2TVE_BUF
 {"DDC", DDC_BIST_ADDR, DDC_BIST_DONE_ADDR, DDC_BIST_FAIL_ADDR, DDC_BIST_SET_BIT, DDC_BIST_DONE_BIT, DDC_BIST_FAIL_BIT},
 {"DDC2", DDC2_BIST_ADDR, DDC2_BIST_DONE_ADDR, DDC2_BIST_FAIL_ADDR, DDC2_BIST_SET_BIT, DDC2_BIST_DONE_BIT, DDC2_BIST_FAIL_BIT},
 {"DDC3", DDC3_BIST_ADDR, DDC3_BIST_DONE_ADDR, DDC3_BIST_FAIL_ADDR, DDC3_BIST_SET_BIT, DDC3_BIST_DONE_BIT, DDC3_BIST_FAIL_BIT},
 {"DDC4", DDC4_BIST_ADDR, DDC4_BIST_DONE_ADDR, DDC4_BIST_FAIL_ADDR, DDC4_BIST_SET_BIT, DDC4_BIST_DONE_BIT, DDC4_BIST_FAIL_BIT},
 {"ETN", ETN_BIST_ADDR, ETN_BIST_DONE_ADDR, ETN_BIST_FAIL_ADDR, ETN_BIST_SET_BIT, ETN_BIST_DONE_BIT, ETN_BIST_FAIL_BIT},
 {"GETN", GETN_BIST_ADDR, GETN_BIST_DONE_ADDR, GETN_BIST_FAIL_ADDR, GETN_BIST_SET_BIT, GETN_BIST_DONE_BIT, GETN_BIST_FAIL_BIT},
 {"GETN_MCU", GETN_MCU_BIST_ADDR, GETN_MCU_BIST_DONE_ADDR, GETN_MCU_BIST_FAIL_ADDR, GETN_MCU_BIST_SET_BIT, GETN_MCU_BIST_DONE_BIT, GETN_MCU_BIST_FAIL_BIT}, //GETN_MCU
 {"HDMI", HDMI_BIST_ADDR, HDMI_BIST_DONE_ADDR, HDMI_BIST_FAIL_ADDR, HDMI_BIST_SET_BIT, HDMI_BIST_DONE_BIT, HDMI_BIST_FAIL_BIT},
 {"HDMITX", HDMITX_BIST_ADDR, HDMITX_BIST_DONE_ADDR, HDMITX_BIST_FAIL_ADDR, HDMITX_BIST_SET_BIT, HDMITX_BIST_DONE_BIT, HDMITX_BIST_FAIL_BIT},  
 {"MCU", MCU_BIST_ADDR, MCU_BIST_DONE_ADDR, MCU_BIST_FAIL_ADDR, MCU_BIST_SET_BIT, MCU_BIST_DONE_BIT, MCU_BIST_FAIL_BIT},
 {"MD", MD_BIST_ADDR, MD_BIST_DONE_ADDR, MD_BIST_FAIL_ADDR, MD_BIST_SET_BIT, MD_BIST_DONE_BIT, MD_BIST_FAIL_BIT},
 {"KCPU", KCPU_BIST_ADDR, KCPU_BIST_DONE_ADDR, KCPU_BIST_FAIL_ADDR, KCPU_BIST_SET_BIT, KCPU_BIST_DONE_BIT, KCPU_BIST_FAIL_BIT},
 {"SE", SE_BIST_ADDR, SE_BIST_DONE_ADDR, SE_BIST_FAIL_ADDR, SE_BIST_SET_BIT, SE_BIST_DONE_BIT, SE_BIST_FAIL_BIT}, 
 {"TP", TP_BIST_ADDR, TP_BIST_DONE_ADDR, TP_BIST_FAIL_ADDR, TP_BIST_SET_BIT, TP_BIST_DONE_BIT, TP_BIST_FAIL_BIT}, 
 {"TVE", TVE_BIST_ADDR, TVE_BIST_DONE_ADDR, TVE_BIST_FAIL_ADDR, TVE_BIST_SET_BIT, TVE_BIST_DONE_BIT, TVE_BIST_FAIL_BIT}, 
 {"TVE_VBIDAM", TVE_VBIDAM_BIST_ADDR, TVE_VBIDAM_BIST_DONE_ADDR, TVE_VBIDAM_BIST_FAIL_ADDR, TVE_VBIDAM_BIST_SET_BIT, TVE_VBIDAM_BIST_DONE_BIT, TVE_VBIDAM_BIST_FAIL_BIT}, //TVE_VBIDMA 
 {"USB", USB_BIST_ADDR, USB_BIST_DONE_ADDR, USB_BIST_FAIL_ADDR, USB_BIST_SET_BIT, USB_BIST_DONE_BIT, USB_BIST_FAIL_BIT}, 
 {"USB2", USB2_BIST_ADDR, USB2_BIST_DONE_ADDR, USB2_BIST_FAIL_ADDR, USB2_BIST_SET_BIT, USB2_BIST_DONE_BIT, USB2_BIST_FAIL_BIT},  
 {"VBI", VBI_BIST_ADDR, VBI_BIST_DONE_ADDR, VBI_BIST_FAIL_ADDR, VBI_BIST_SET_BIT, VBI_BIST_DONE_BIT, VBI_BIST_FAIL_BIT}, 
 {"VCPU", VCPU_BIST_ADDR, VCPU_BIST_DONE_ADDR, VCPU_BIST_FAIL_ADDR, VCPU_BIST_SET_BIT, VCPU_BIST_DONE_BIT, VCPU_BIST_FAIL_BIT}, 
 {"VDE", VDE_BIST_ADDR, VDE_BIST_DONE_ADDR, VDE_BIST_FAIL_ADDR, VDE_BIST_SET_BIT, VDE_BIST_DONE_BIT, VDE_BIST_FAIL_BIT},  
 {"VE", VE_BIST_ADDR, VE_BIST_DONE_ADDR, VE_BIST_FAIL_ADDR, VE_BIST_SET_BIT, VE_BIST_DONE_BIT, VE_BIST_FAIL_BIT},
 {"DCSYS_DC2", DCSYS_DC2_BIST_ADDR, DCSYS_DC2_BIST_DONE_ADDR, DCSYS_DC2_BIST_FAIL_ADDR, DCSYS_DC2_BIST_SET_BIT, DCSYS_DC2_BIST_DONE_BIT, DCSYS_DC2_BIST_FAIL_BIT}, //DCSYS_DC2
 {"DCSYS_DC3", DCSYS_DC3_BIST_ADDR, DCSYS_DC3_BIST_DONE_ADDR, DCSYS_DC3_BIST_FAIL_ADDR, DCSYS_DC3_BIST_SET_BIT, DCSYS_DC3_BIST_DONE_BIT, DCSYS_DC3_BIST_FAIL_BIT}, //DCSYS_DC3
 {"EMMC", EMMC_BIST_ADDR, EMMC_BIST_DONE_ADDR, EMMC_BIST_FAIL_ADDR, EMMC_BIST_SET_BIT, EMMC_BIST_DONE_BIT, EMMC_BIST_FAIL_BIT}, 
 {"IRTX", IRTX_BIST_ADDR, IRTX_BIST_DONE_ADDR, IRTX_BIST_FAIL_ADDR, IRTX_BIST_SET_BIT, IRTX_BIST_DONE_BIT, IRTX_BIST_FAIL_BIT}, 
 {"KT", KT_BIST_ADDR, KT_BIST_DONE_ADDR, KT_BIST_FAIL_ADDR, KT_BIST_SET_BIT, KT_BIST_DONE_BIT, KT_BIST_FAIL_BIT},
 {"MISCDDC", MISCDDC_BIST_ADDR, MISCDDC_BIST_DONE_ADDR, MISCDDC_BIST_FAIL_ADDR, MISCDDC_BIST_SET_BIT, MISCDDC_BIST_DONE_BIT, MISCDDC_BIST_FAIL_BIT},
 {"NAND", NAND_BIST_ADDR, NAND_BIST_DONE_ADDR, NAND_BIST_FAIL_ADDR, NAND_BIST_SET_BIT, NAND_BIST_DONE_BIT, NAND_BIST_FAIL_BIT},
 {"OSD", OSD_BIST_ADDR, OSD_BIST_DONE_ADDR, OSD_BIST_FAIL_ADDR, OSD_BIST_SET_BIT, OSD_BIST_DONE_BIT, OSD_BIST_FAIL_BIT},
 {"SD", SD_BIST_ADDR, SD_BIST_DONE_ADDR, SD_BIST_FAIL_ADDR, SD_BIST_SET_BIT, SD_BIST_DONE_BIT, SD_BIST_FAIL_BIT}, 
 {"SENSIO", SENSIO_BIST_ADDR, SENSIO_BIST_DONE_ADDR, SENSIO_BIST_FAIL_ADDR, SENSIO_BIST_SET_BIT, SENSIO_BIST_DONE_BIT, SENSIO_BIST_FAIL_BIT}, 
 {"SFG", SFG_BIST_ADDR, SFG_BIST_DONE_ADDR, SFG_BIST_FAIL_ADDR, SFG_BIST_SET_BIT, SFG_BIST_DONE_BIT, SFG_BIST_FAIL_BIT}, 
 {"VBY1", VBY1_BIST_ADDR, VBY1_BIST_DONE_ADDR, VBY1_BIST_FAIL_ADDR, VBY1_BIST_SET_BIT, VBY1_BIST_DONE_BIT, VBY1_BIST_FAIL_BIT}, 
 {"VD", VD_BIST_ADDR, VD_BIST_DONE_ADDR, VD_BIST_FAIL_ADDR, VD_BIST_SET_BIT, VD_BIST_DONE_BIT, VD_BIST_FAIL_BIT},
 {"HDMITX2", HDMITX2_BIST_ADDR, HDMITX2_BIST_DONE_ADDR, HDMITX2_BIST_FAIL_ADDR, HDMITX2_BIST_SET_BIT, HDMITX2_BIST_DONE_BIT, HDMITX2_BIST_FAIL_BIT},   
//{"GPU", GPU_BIST_ADDR, GPU_BIST_DONE_ADDR, GPU_BIST_FAIL_ADDR, GPU_BIST_SET_BIT, GPU_BIST_DONE_BIT, GPU_BIST_FAIL_BIT},
};

#if 0
int SCPU_BIST(void)
{
	int   bStatus = SUCCESS;
	UINT8 i, j;
	UINT8 bScan = 50;

	UINT32 SCPU_Fail_addr[8]={SCPU_BIST_FAIL_ADDR,SCPU_BIST_FAIL_ADDR2,SCPU_BIST_FAIL_ADDR3,SCPU_BIST_FAIL_ADDR4,
		SCPU_BIST_FAIL_ADDR5,SCPU_BIST_FAIL_ADDR6,SCPU_BIST_FAIL_ADDR7,SCPU_BIST_FAIL_ADDR8};
	UINT32 SCPU_Fail_bit[8]={SCPU_BIST_FAIL_BIT,SCPU_BIST_FAIL_BIT2,SCPU_BIST_FAIL_BIT3,SCPU_BIST_FAIL_BIT4,
		SCPU_BIST_FAIL_BIT5,SCPU_BIST_FAIL_BIT6,SCPU_BIST_FAIL_BIT7,SCPU_BIST_FAIL_BIT8};	

	for(i=0; i<8; i++)
	{
		rtd_maskl(SCPU_BIST_ADDR, ~(1<<i), (1<<i)); //set bist mode
		for(j = 0; j <= bScan; j++)
		{
			udelay(100);
			if((rtd_inl(SCPU_BIST_DONE_ADDR) & (1<<i)) == (1<<i)) //bist done
			{
				if((rtd_inl(SCPU_Fail_addr[i]) & SCPU_Fail_bit[i]) == 0) //check fail bit
					printf("SCPU_%d BIST done and no fail!\n",(i+1));
				else
				{
					printf("SCPU_%d BIST fail(0x%x)!\n",(i+1),rtd_inl(SCPU_Fail_addr[i]));
					bStatus = FAILED;
				}
				break;
			}
			else if(j == bScan)
			{
				printf("Can't wait SCPU_%d BIST done bit(0x%x)\n",(i+1), rtd_inl(SCPU_BIST_DONE_ADDR));
				bStatus = FAILED;
			}
		}
		rtd_maskl(SCPU_BIST_ADDR, ~(1<<i), 0); //disable bist mode	
	}
}
#endif
void ACPU_clk_en(void)
{
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
}

void VCPU_clk_en(void)
{
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
}

void USB_clk_en(void)
{	
	rtd_maskl(0xb8000000, 0xFFFFF8FF, 0x00000700); // release phy reset
	udelay(1000);
	rtd_maskl(0xb800000c, 0xFFFFFFeb, 0x00000014); // mac clock enable
	udelay(1000);
	rtd_maskl(0xb800000c, 0xFFFFFFeb, 0x00000000); // mac clock disable
	udelay(1000);
	rtd_maskl(0xb8000000, 0xFFFFFF8F, 0x00000070); // release mac reset
	udelay(1000);
	rtd_maskl(0xb800000c, 0xFFFFFFeb, 0x00000014); // mac clock enable
	udelay(1000);
}

void DDC_clk_en(void)
{
	//clken:1	
	rtd_maskl(0xb8000014,0xFFFFFFBF,0x00000040);//clken_ddc[6]:1	
	rtd_maskl(0xb8060044,0xFFFF1FFD,0x0000E002);//clken_ddc3/2/1[15:13] clken_ddc[1]:1
	//clken:0
	rtd_maskl(0xb8000014,0xFFFFFFBF,0x0);//clken_ddc[6]:0
	rtd_maskl(0xb8060044,0xFFFF1FFD,0x0);//clken_ddc3/2/1[15:13] clken_ddc[1]:0
	//RSTN:0
	rtd_maskl(0xb8000000,0xFFFFF7FF,0x0);//rstn_ddc:0
	rtd_maskl(0xb8060034,0xFFFF1FFD,0x0);//rstn_ddc3/2/1[15:13] rstn_ddc0[1]:0
	//RSTN:1
	rtd_maskl(0xb8000000,0xFFFFF7FF,0x00000800);//rstn_ddc:1
	rtd_maskl(0xb8060034,0xFFFF1FFD,0x0000E002);//rstn_ddc3/2/1[15:13] rstn_ddc[1]:1
	//clken:1
	rtd_maskl(0xb8000014,0xFFFFFFBF,0x00000040);//clken_ddc[6]:1
	rtd_maskl(0xb8060044,0xFFFF1FFD,0x0000E002);//clken_ddc3/2/1[15:13] clken_ddc[1]:1	
}

int BIST(void)
{	
	int bStatus = SUCCESS;
	UINT32 tmp_addr;
	UINT8  bScan = 50;	
	UINT8  i, j, k;
	
	INT32	argc = 0;
  	INT8	**argv = NULL; 
	#define	QCINFO_CMD_BUFFER_SIZE	128
	UINT8	abyCommandBuffer[QCINFO_CMD_BUFFER_SIZE];

	//if(SCPU_BIST() == FAILED)
		//bStatus = FAILED;
	
	while(1){
			printk("Enter test number: ");		
			memset(abyCommandBuffer, 0, QCINFO_CMD_BUFFER_SIZE);
			GetLine(abyCommandBuffer, QCINFO_CMD_BUFFER_SIZE, 1);			
  			printk("\n");
					
			//Parse Argument Count by Input Data
  			argc = GetArgc((const INT8 *) abyCommandBuffer);
  			
  			//Parse Argument String by Input Data
  			argv = (INT8 **) GetArgv((const INT8 *) abyCommandBuffer);
  			
  			if(argc < 1)
  			{
  			  	continue;
  			}
  			
  			//Convert Argument String to Upper Case
  			StrUpr(argv[0]);						
			i = strtoul((const INT8 *) (argv[0]), (INT8 **) NULL, 10);	

			if(i == 60)
				break;
	//for(i = 0; i < BIST_NUM; i++)
	{		
		rtd_maskl(Bist_test[i].set_addr, ~Bist_test[i].set_bit, Bist_test[i].set_bit); //set bist mode
		udelay(20000);		
		for(j = 0; j <= bScan; j++)
		{
			udelay(100);
			if((rtd_inl(Bist_test[i].done_addr)&Bist_test[i].done_bit) == Bist_test[i].done_bit) //bist done
			{
				if(Bist_test[i].flag == "VE")
				{				
					printk("0x%x, 0x%x\n", rtd_inl(0x1800FF88),rtd_inl(0x1800FF90));
					for(k=1; k<17; k++)
					{
						if((rtd_inl(VE_BIST_DONE_ADDR+k*8)&Bist_test[i].done_bit) == Bist_test[i].done_bit)
							printf("0x%x BIST done.\n", VE_BIST_DONE_ADDR+k*8);
						else
						{
							printf("Can't wait VE_%d BIST done bit(0x%x)\n", k, rtd_inl(VE_BIST_DONE_ADDR+k*8));
							bStatus = FAILED;
						}
					}
				}
				else if((rtd_inl(Bist_test[i].fail_addr)&Bist_test[i].fail_bit) == 0) //check fail bit
					printf("%s BIST done and no fail!\n", Bist_test[i].flag);
				else
				{
					printf("%s BIST fail(0x%x)!\n", Bist_test[i].flag, rtd_inl(Bist_test[i].fail_addr));
					bStatus = FAILED;
				}
				break;
			}
			else if(j == bScan)
			{
				printf("Can't wait %s BIST done bit(0x%x)\n", Bist_test[i].flag, rtd_inl(Bist_test[i].done_addr));
				bStatus = FAILED;
			}
		}
		rtd_maskl(Bist_test[i].set_addr, ~Bist_test[i].set_bit, 0); //disable bist mode	
	}
	} //while
	return bStatus;
}

int QC_Verifier_BIST(void)
{
	int Status;

	//for ACPU,AE,
	ACPU_clk_en();
	//for SE,VPU,VDE,VE
	VCPU_clk_en();
	//for DDC
	DDC_clk_en();
	//for DISP2TVE
	rtd_maskl(0xb8000014, ~_BIT22, _BIT22); //CLKEN_DISP2TVE
	rtd_maskl(0xb8026000, ~(_BIT31|_BIT30|_BIT29|_BIT28), _BIT31|_BIT30|_BIT29|_BIT28); //disp2tve_global enable	
	//for OSD
	rtd_maskl(0xb8000008, ~_BIT15, _BIT15); //rstn=1
	rtd_maskl(0xb8000014, ~_BIT25, _BIT25); //clk=1
	rtd_maskl(0xb8035004, ~(_BIT1|_BIT0), _BIT1|_BIT0); //osd_en
	rtd_maskl(0xb8035014, ~(_BIT1|_BIT0), _BIT1|_BIT0);
	//for MISCDDC
	rtd_maskl(0xb8000000, ~_BIT11, _BIT11); //rstn=1
	rtd_maskl(0xb8000014, ~_BIT6, _BIT6); //clk=1
	//for USB
	USB_clk_en();
	//for TVE_VBIDAM
	rtd_maskl(0xb8000008, ~_BIT20, _BIT20); //RSTN_TVSB1_TVE
	rtd_maskl(0xb800000c, ~_BIT28, _BIT28); //CLKEN_TVSB1_TVE
	//for IRTX
	rtd_maskl(0xb8000004, ~_BIT22, _BIT22); //rstn_ir
	rtd_maskl(0xb8000010, ~_BIT12, _BIT12); //clk_en_misc_ir
	//for KT
	rtd_maskl(0xb8000008, ~_BIT27, _BIT27); //rstn_kt
	rtd_maskl(0xb8000014, ~_BIT7, _BIT7); //clk_en_kt	
	//for SD
	rtd_maskl(0xb8000004, ~_BIT10, _BIT10); //rstn_cr,Reset bit of card reader
	rtd_maskl(0xb800000c, ~_BIT25, _BIT25); //clk_en_cr	
	//for VBI
	rtd_maskl(0xb8000008, ~_BIT9, _BIT9); //RSTN_VBIS0
	rtd_maskl(0xb8000014, ~_BIT20, _BIT20); //CLKEN_VBIS0	
	//for audio
	rtd_maskl(0xb8000008, ~(_BIT8|_BIT7|_BIT6), (_BIT8|_BIT7|_BIT6)); //reset [8]AUDIO2_DAC,[7]AUDIO_ADC,[6]AUDIO_DAC
	//for CP, 
	//1:Try to saving power  0:Always has clock
	rtd_maskl(0xb80151e0,~(_BIT22|_BIT21|_BIT20), _BIT21);//en_cp[22]=0,en_mcp[21]=1,en_cdpu[20]=0
	//for HDMI_RX
	rtd_maskl(0xb800710c, ~_BIT0, 0);//Audio_BIST_CLKSEL[0],0:From PLL 1:From pixel clock
	rtd_maskl(0xb8007404, ~(_BIT2|_BIT1), 0x2);//DPLL_FREEZE[2]=0; DPLL_VCORSTB[1]=1
	                                        //[2]DPLL Output Freeze 0:Normal 1:Freeze (active high)
											//[1]RESET VCO  (active low, 0:Reset, 1:Normal) 	
	rtd_maskl(0xb8007B6C, ~_BIT3, _BIT3); //[3]reg_dpll_pow on
	//for DC_PHY
	rtd_maskl(0xb8008ffc, ~(_BIT2|_BIT1|_BIT0), (_BIT2|_BIT1|_BIT0)); //dc_phy_ptg release reset
	rtd_maskl(0xb8008fc0, ~_BIT8, _BIT8); //DC_PHY_BIST_CLKSEL=1
	//for VBy1
	rtd_maskl(0xb8000c54, ~_BIT30, _BIT30); 
	//for MCU
	rtd_maskl(0xb8060034, ~(_BIT10|_BIT9), 0x400);
	rtd_maskl(0xb8060044, ~_BIT9, _BIT9);

	Status = BIST();
	
	return Status;
}
