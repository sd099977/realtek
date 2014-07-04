#include <qc_verify_common.h>
#include "TVE_reg.h"
#include "TVE.h"
#include "VO_reg.h"
#include "crt_sys_reg.h"
#include "qc_verify.h"
//#include "TV_NTSC_M.c"
//#include "TV_NTSC_J.c"
//#include "TV_525i.c"
//#include "TV_525p_700.c"
//#include "TV_525p_714.c"
//#include "TV_PAL.c"
//#include "TV_625i.c"
//#include "TV_625p.c"
//#include "TV_720p50.c"
//#include "TV_720p60.c"
//#include "TV_1080i50.c"
//#include "TV_1080i60.c"
//#include "TV_1080p24.c"

//#include "TV_1080p50.c"
//#include "TV_1080p60.c"
//#include "TV_NTSC_443.c"
//#include "TV_PAL_60.c"
//#include "TV_PAL_CN.c"
//#include "TV_PAL_M.c"
//#include "TV_PAL_N.c"
unsigned int *RGB_flag1=(unsigned int *)0xa010001c;
unsigned int *mv_flag1=(unsigned	int *)0xa0100020;
unsigned int *ClkSel = 0xb800c084;
unsigned int *DebugAddx=0xa1001000;
unsigned int *CC_NTSC_flag=(unsigned int *)0xa0100000;
unsigned int *CC_PAL_flag=(unsigned int	*)0xa0100004;
unsigned int *WSS_flag=(unsigned int *)0xa0100008;
unsigned int *CGMS_flag=(unsigned int *)0xa010000c;
unsigned int *TT_flag=(unsigned	int *)0xa0100010;
unsigned int *VPS_flag=(unsigned int *)0xa0100014;
unsigned int *DrawingMode_flag=(unsigned int *)0xa0100018;
UINT32 TVE_Enable3D=0;
UINT32 TVE_Format3D=0;  
UINT32 TVE_TimingGen=1;
UINT8 *TVE_UART_flag = 1;

#define rtdf_setBits(offset, Mask) 			rtd_outl(offset, (rtd_inl(offset) |Mask))
#define rtdf_clearBits(offset, Mask) 		rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#define rtdf_inl(Address)					(*(volatile UINT32 *) (Address))		//Read 32-bit Data from Specific Memory Address
#define rtdf_outl(Address, Data)				(*(volatile UINT32 *) (Address) = Data)	//Write 32-bit Data to Specific Memory Address
#define rtdf_maskl(Address, AndMask, OrMask)	rtd_outl(Address, ((rtd_inl(Address) & (AndMask)) | (OrMask)))


//###########################################################################################################################

UINT8 TVE_gpio_result()
{
#if 1
	return  SUCCESS;
#else
	while(1)
	{
	   if(1)
		return  SUCCESS;
	   else if(0)
		return  FAILED;
	}
#endif
}

void TVE_BusyWaiting(UINT32 count)
{
    UINT32 i=0;
    if(count>10000)
        count=10000;
    while(count>0)
    {
        i=5; //about 200uS
        while(i>0) i--;
        count--;
    }
}
void TVE_PLLDDSA(UINT8 M_Code,UINT8 N_Code,UINT8 K_Code)
{
	UINT16 VCO_freq=0,X_clk=27;

	rtd_maskl(SYS_PLL_DISP_SD4_reg,~(_BIT2|_BIT1|_BIT0),(_BIT2|_BIT0));	//PLL_POW=1, Power on,output disable
	rtd_maskl(SYS_PLL_DISP_SD4_reg,~_BIT1,_BIT1);						//PLL_RSTB=1, Release reset,K=1

	VCO_freq = X_clk*M_Code/N_Code;

	if ((VCO_freq == 432)||(VCO_freq == 297))
	{
		rtd_maskl(SYS_PLL_DISP_SD1_reg,0xff801fff,	(_BIT21|_BIT16));	//Icp=7.5uA,RS=13.5k,CS=46.2pF,CP=1.3pF
	}
	
	N_Code = N_Code - 1;
	M_Code = M_Code - 2;
	K_Code = K_Code - 1;
	rtd_maskl(SYS_PLL_DISP_SD1_reg,0x007fffff,((((UINT32) N_Code)<<30)|(((UINT32) M_Code)<<23)));
	//must be
	TVE_BusyWaiting(10000);       	        											//Delay for Stable Value 
	rtd_maskl(SYS_PLL_DISP_SD4_reg,~(_BIT5|_BIT4|_BIT2|_BIT1|_BIT0),((K_Code<<4)|_BIT1|_BIT0));	//PLL_OEB=0, Output enable
	TVE_BusyWaiting(10000);       	        											//Delay for Stable Value

}

void TVE_PLLDISP(UINT8 M_Code,UINT8 N_Code,UINT8 Q1_Code,UINT8 Q2_Code)
{
	UINT16 VCO_freq=0,X_clk=27;

//rtd_outl(0xb8000134,0x00804c90);		//M(bit[17:11])=11,N=1,Q1(bit[19:18])=1,Q2(bit[25:24])=1,vco freq = 297M,clk1=297M,clk2=297M//
//rtd_outl(0xb8000134,0x01847490);		//M(bit[17:11])=16,N=1,Q1(bit[19:18])=2,Q2(bit[25:24])=2,vco freq = 432M,clk1=216M,clk2=216M//
//rtd_outl(0xb8000134,0x0208fe80);		//M(bit[17:11])=33,N=2,Q1(bit[19:18])=3,Q2(bit[25:24])=3,vco freq = 445.5M,clk1=148.5M,clk2=148.5M

	rtd_maskl(SYS_PLL_DISP_HD2_reg,~(_BIT3|_BIT2|_BIT1|_BIT0),(_BIT3|_BIT2|_BIT0));	//PLL_POW=1, Power on,output disable
	rtd_maskl(SYS_PLL_DISP_HD2_reg,~_BIT1,_BIT1);						//PLL_RSTB=1, Release reset

	VCO_freq = X_clk*M_Code/N_Code;

	if ((VCO_freq == 432)||(VCO_freq == 297))
	{
		rtd_maskl(SYS_PLL_DISP_HD1_reg,0xfffff80f,	(_BIT10|_BIT4));	//Icp=7.5uA,RS=16k,CS=42pF
	}

	M_Code = M_Code - 2;
	Q1_Code = Q1_Code - 1;
	Q2_Code = Q2_Code - 1;
	
	if (N_Code > 1){
		N_Code = N_Code - 2;
		rtd_maskl(SYS_PLL_DISP_HD1_reg,0x000007ff,((((UINT32) Q2_Code)<<24)|(((UINT32) N_Code)<<20)|(((UINT32) Q1_Code)<<18)|(((UINT32) M_Code)<<11)));
	}else{
		rtd_maskl(SYS_PLL_DISP_HD1_reg,0x000007ff,((((UINT32) Q2_Code)<<24)|(((UINT32) Q1_Code)<<18)|(((UINT32) M_Code)<<11)|_BIT23));//disable N
	}
	//must be
	TVE_BusyWaiting(10000);       	        											//Delay for Stable Value 
	rtd_maskl(SYS_PLL_DISP_HD2_reg,~(_BIT3|_BIT2|_BIT1|_BIT0),(_BIT1|_BIT0));					//PLL_OEB=0, Output enable
	TVE_BusyWaiting(10000);           	        											//Delay for Stable Value

}
void TVE_GO_function(UINT32 display_mode)
{
    switch(display_mode)
    {
        case 1 ://525i
            //0xb8018000
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0)); 
            break;
        case 2 ://525p(700/300)
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 3 ://625i
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 4 ://625p
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 5 ://720p60
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 6 ://1080i50
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 7 ://1080i60
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 17 ://525p(714/286)
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 18 ://1080p24
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 19 ://1080p30
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 20 ://720p50
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en6(1)|TVE_SYNCGEN_RST_ph_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
    } //switch(display_mode)
    return;
}

//###########################################################################################################################
void TVE_Display(UINT32 mode, UINT32 colorbar, UINT32 RGB_mode, UINT32 video_format)
{
		 printk(" TVE_Display...test go go og ogo go go \n");
    //==========================================================================
    //Only for Saturn FPGA setting
    //==========================================================================
    //clock select
#if 0
    if((mode <= 4) || (mode >= 9) && (mode <= 14))
			*ClkSel = *ClkSel & 0xfcffffff;//27MHz
    else
			*ClkSel = *ClkSel | 0x02000000;//74.25MHz

    rtd_outl(0xb8005040, 0x03);//Enable PVO multiple requests to DCU.
#endif
    //==========================================================================
    //Component high frequency enhancement
    //==========================================================================
		if(0)//READ_REG_INT32U(0xa2100000)&0x01)
		{
//			//FIR coeficients, high frequency enhancement
//			//0xb801837c
//		 	rtd_outl(TVE_DAC1_FIR_1_reg, 0x00001000);
//		 	//0xb8018380
//		 	rtd_outl(TVE_DAC1_FIR_2_reg, 0x00000000);
//		 	//0xb8018388
//		 	rtd_outl(TVE_DAC2_FIR_1_reg, 0x3f0b146d);
//		 	//0xb801838c
//		 	rtd_outl(TVE_DAC2_FIR_2_reg, 0x001b3e99);
//		 	//0xb8018390
//		 	rtd_outl(TVE_DAC3_FIR_1_reg, 0x3f0b146d);
//		 	//0xb8018394
//		 	rtd_outl(TVE_DAC3_FIR_2_reg, 0x001b3e99);
//		 	//0xb8018398
//		 	rtd_outl(TVE_DAC4_FIR_1_reg, 0x3f0b146d);
//		 	//0xb801839c
//		 	rtd_outl(TVE_DAC4_FIR_2_reg, 0x001b3e99);
		 	rtd_outl(TVE_DAC1_FIR_1_reg, 0x3f0b146d);
		 	//0xb8018380
		 	rtd_outl(TVE_DAC1_FIR_2_reg, 0x001b3e99);
		 	//0xb8018388
		 	rtd_outl(TVE_DAC2_FIR_1_reg, 0x3f0b146d);
		 	//0xb801838c
		 	rtd_outl(TVE_DAC2_FIR_2_reg, 0x001b3e99);
		 	//0xb8018390
		 	rtd_outl(TVE_DAC3_FIR_1_reg, 0x3f0b146d);
		 	//0xb8018394
		 	rtd_outl(TVE_DAC3_FIR_2_reg, 0x001b3e99);
		 	//0xb8018398
		 	rtd_outl(TVE_DAC4_FIR_1_reg, 0x3f0b146d);
		 	//0xb801839c
		 	rtd_outl(TVE_DAC4_FIR_2_reg, 0x001b3e99);
		 }
		 else
		 {//default value
		 	rtd_outl(TVE_DAC1_FIR_1_reg, 0x00001000);
		 	//0xb8018380
		 	rtd_outl(TVE_DAC1_FIR_2_reg, 0x00000000);
		 	//0xb8018388
		 	rtd_outl(TVE_DAC2_FIR_1_reg, 0x00001000);
		 	//0xb801838c                                   
		 	rtd_outl(TVE_DAC2_FIR_2_reg, 0x00000000);
		 	//0xb8018390
		 	rtd_outl(TVE_DAC3_FIR_1_reg, 0x00001000);
		 	//0xb8018394                                   
		 	rtd_outl(TVE_DAC3_FIR_2_reg, 0x00000000);
		 	//0xb8018398
		 	rtd_outl(TVE_DAC4_FIR_1_reg, 0x00001000);
		 	//0xb801839c                                   
		 	rtd_outl(TVE_DAC4_FIR_2_reg, 0x00000000);
	 	}
			 printk(" TVE_Display...test\n");
    switch(mode)
    {
    	  case 1: 
         case 2: 
         case 3: 
         case 4: 
    	  case 9: 
         case 10: 
         case 11: 
         case 12: 	
         case 13: 
         case 14: 
         case 17: 
		 	#if 0
		  rtd_maskl(SYS_PLL_HDMI2_reg,~(_BIT3|_BIT0),_BIT3);//TMDS_POWBIAS on,PLLHDMI power off	      
		  TVE_PLLDDSA(16,1,1);//432MHz
		  //0xb8000024
		  rtd_maskl(SYS_DISP_PLL_DIV2_reg,0xfffe0000,(_BIT16|_BIT14|_BIT12|_BIT10|_BIT8|_BIT5|_BIT4|_BIT0));//sel_pllhdmi_clk=0,sel_plldisp_clk2=0,hdmi_div=1(27M),tve_div=1(27M)			
			#endif
		break;
         case 5: 
         case 6: 
         case 7: 
    	  case 15: 
         case 16: 
         case 18: 
         case 20:
		 	#if 0
		   rtd_maskl(SYS_PLL_HDMI2_reg,~(_BIT3|_BIT0),_BIT3);//TMDS_POWBIAS on,PLLHDMI power off
                TVE_PLLDISP(11,1,1,2);//M=11,N=1,Q1=1,Q2=2,vco freq = 297M,clk1=297M,clk2=148.5M
		  rtd_maskl(SYS_DISP_PLL_DIV2_reg,0xfffe0000,(_BIT16|_BIT14|_BIT12|_BIT10|_BIT8|_BIT7|_BIT4|_BIT1));//sel_pllhdmi_clk=0,sel_plldisp_clk2=0,hdmi_div=4(74.25M),tve_div=2(74.25M)
			#endif
		break;	


    	}
		 
	 printk(" TVE_Display...test ,99999=%d\n",mode);
    switch(mode)
    {
        case 1 :
            //TV_525i(RGB_mode, video_format);
            printk(" TVE_TV_NTSC_M\n");
            TVE_TV_NTSC_M();
	     printk(" TVE_TV_525i\n");		
            TVE_TV_525i(RGB_mode, video_format);
//TV_525p_714();
            TVE_GO_function(mode);
            break;
        case 2 :
            //TV_525p_700();
            TVE_TV_NTSC_M();
            TVE_TV_525p_700();
            TVE_GO_function(mode);
            break;
        case 3 :
	     printk(" TVE_TV_PAL\n");			
            TVE_TV_PAL();
	      	printk(" TVE_TV_625i\n");
            TVE_TV_625i(RGB_mode);
//TV_625p();
            TVE_GO_function(mode);
            break;
        case 4 :
            //TV_625p();
            printk(" TVE_TV_PAL\n");
            TVE_TV_PAL();
	     
            TVE_TV_625p();	
            TVE_GO_function(mode);
            break;
        case 5 :
            TVE_TV_720p60();
            TVE_GO_function(mode);
            break;
        case 6 :
            TVE_TV_1080i50();
            TVE_GO_function(mode);
            break;
        case 7 :
	     
            TVE_TV_1080i60();
            TVE_GO_function(mode);
            break;
        case 8 : 
            break;
        case 9 :
            //TV_NTSC_J(RGB_mode, video_format);
            TVE_TV_NTSC_J();
            TVE_TV_525i(RGB_mode, video_format);
//TV_525p_714();
            TVE_GO_function(mode);
            break;
        case 10 :
            TVE_TV_NTSC_443(colorbar);
            TVE_GO_function(mode);
            break;
        case 11 :
            TVE_TV_PAL_M(colorbar);
            TVE_GO_function(mode);
            break;
        case 12 :
            TVE_TV_PAL_N(colorbar);
            TVE_GO_function(mode);
            break;
        case 13 :
            TVE_TV_PAL_60(colorbar);
            TVE_GO_function(mode);
            break;
        case 14 :
            TVE_TV_PAL_CN(colorbar);
            TVE_GO_function(mode);
            break;
        case 15 :
            TVE_TV_1080p50();
            TVE_GO_function(mode);
            break;
        case 16 :
	     printk(" TVE_TV_1080p60...start\n");
            TVE_TV_1080p60();
            TVE_GO_function(mode);
	     	     printk(" TVE_TV_1080p60...end\n");
            break;
        case 17 :
            TVE_TV_NTSC_M();
            TVE_TV_525p_714();
            TVE_GO_function(mode);
            break;
        case 18 :
            TVE_TV_1080p24();
            TVE_GO_function(mode);
            break;
        case 19 :
            break;
        case 20 :
            TVE_TV_720p50();
            TVE_GO_function(mode);
            break;
        default:
            break;
    }
    *DebugAddx = mode;
     //CGMS_enable(mode);
    
    return;
}
#if 0
//###########################################################################################################################
void TVE_Run_loop(UINT32 mode, UINT32 RGB_mode, UINT32 video_format, UINT32 colorbar,
              UINT32 CC_NTSC_enable, UINT32 CC_PAL_enable, UINT32 WSS_PAL_enable, UINT32 CGMS_NTSC_enable, UINT32 TT_PAL_enable, UINT32 VPS_enable, UINT32 DrawingMode_enable,UINT32 Enable_3D, UINT32 Format_3D,UINT32 Timing_Gen)

{
    int flagTopBottom = 0;
    int flagLeftRight = 0;

    switch(mode)
    {
        case 1: //525i
        case 9: //NTSC-J
        case 10: //NTSC-4.43
        case 11: //PAL-M
        case 13: //PAL-60
            if(colorbar==4)  //colorbar==4表示資料從v0過來
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(1)|
                                         VO_V1_INDEX_3D_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(480));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(240));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(240));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(480));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else//////////////////////////////////////////////////////enable ==0//////////////////////
                {
       /*
	 case 1: //525i
        case 9: //NTSC-J
        case 10: //NTSC-4.43
        case 11: //PAL-M
        case 13: //PAL-60


       */
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(0));
                    if(Timing_Gen)
                    {
                        //0xb8005000
                        rtd_outl(VO_MODE_reg,
                                         VO_MODE_ch2i(0)|
                                         VO_MODE_ch2(0)|
                                         VO_MODE_ch1i(0)|
                                         VO_MODE_ch1(1)|
                                         VO_MODE_write_data(1));
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(1)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005000
                        rtd_outl(VO_MODE_reg,
                                         VO_MODE_ch2i(0)|
                                         VO_MODE_ch2(0)|
                                         VO_MODE_ch1i(0)|
                                         VO_MODE_ch1(1)|
                                         VO_MODE_write_data(1));
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(1)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(1)|
                                     VO_V1_INDEX_y(0));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(480));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(480));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));

                    rtd_outl(VO_CH2_BUF_reg,
                                     VO_CH2_BUF_write_en2(0)|VO_CH2_BUF_th(0)|
                                     VO_CH2_BUF_write_en1(1)|VO_CH2_BUF_b(256));
                                  
                                     
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    if(Timing_Gen)
                    {
                        //0xb80057fc
                        rtd_outl(VO_CH1_reg,
                                         VO_CH1_itop(0)|
                                         VO_CH1_ireint(0)|
                                         VO_CH1_top(0)|
                                         VO_CH1_reint(1)|
                                         VO_CH1_write_data(1));
                    }
                    else
                    {
                        //0xb80057fc
                        rtd_outl(VO_CH1_reg,
                                         VO_CH1_itop(0)|
                                         VO_CH1_ireint(0)|
                                         VO_CH1_top(0)|
                                         VO_CH1_reint(1)|
                                         VO_CH1_write_data(1));
                    }
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
               // UART_READ();
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1) //3D----------------------------------------
                    {
                        if(TVE_Format3D==0)
                        {
                            //***L odd frame***
                      /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }  
                            */
                        }
                        if(TVE_Format3D==6)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            */
                        } 
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            */
                        }
/*
			if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
  */
                    }
                    else
                    {
                        if(Timing_Gen)// hdm1==1 or tve==0
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                            
                                flagTopBottom = 1;
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& flagTopBottom)
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                            
                                flagTopBottom = 0;
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
    */
                        }
                        else
                        {
                            if(TVE_INTST_get_intst_i(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(1)|
                                                 TVE_INTST_intst_i(1)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                flagTopBottom = TVE_SYNCGEN_STATUS_I_get_i_field(*(volatile unsigned int *)TVE_SYNCGEN_STATUS_I_reg);
                                //0xb8018024
                                rtd_outl(TVE_INTPOS_I_reg,
                                                 TVE_INTPOS_I_write_en2(1)|TVE_INTPOS_I_int_vpos(flagTopBottom ? 2 : 270)|
                                                 TVE_INTPOS_I_write_en1(1)|TVE_INTPOS_I_int_hpos(0));
                                //0xb80057fc
                                
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1-flagTopBottom));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
				 }
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	
                        }
                    }
                }
            }
            break;

        case 2: //480p
        case 17: //525p_714
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(1)|
                                         VO_V1_INDEX_3D_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(480));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(240));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(240));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(480));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else//=========================TVE_Enable3D==0=============
/*
		 case 2: //480p
        	case 17: //525p_714	


*/		
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(1)|
                                     VO_V1_INDEX_y(0));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(480));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(480));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
                //UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;

                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
     /*mark by sky
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            */
                        }
                        if(TVE_Format3D==6)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            */
                        } 
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            */
                        }
						/*
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }*/
                    }
                    else
                    {
                        if(Timing_Gen)
                        {
                       /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
     */
                        }
                        else
                        {
                            if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	
                        }
                    }
                }
            }
            break;

        case 3: //576i
        case 12: //PAL-N
        case 14: //PAL-CN
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(3)|
                                         VO_V1_INDEX_3D_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(576));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(288));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(288));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(576));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }//===========TVE_Enable3D====0/////////////////////////

                else
                {
        
/*
         case 3: //576i
        case 12: //PAL-N
        case 14: //PAL-CN


           */
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(1)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(3)|
                                     VO_V1_INDEX_y(2));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(576));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(576));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
			//0xb80057f8
			rtd_outl(VO_CH2_BUF_reg,
                                     VO_CH2_BUF_write_en2(0)|VO_CH2_BUF_th(0)|
                                     VO_CH2_BUF_write_en1(1)|VO_CH2_BUF_b(256));
                                  
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
    
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
               // UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
                            //***L odd frame***
                            /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }  
                            */
                        }
                        if(TVE_Format3D==6)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            */
                        } 
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }*/
                        }
						/*
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }*/
                        
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            
                        
                    }
                    else
                    {
                   /*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& !flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 1;
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1-flagTopBottom));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 0;
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1-flagTopBottom));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        */
                        if(Timing_Gen)
                        {
                        /*
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }*/
                        }
                        else
                        {
                        /*
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                            */
                            if(TVE_INTST_get_intst_i(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(1)|
                                                 TVE_INTST_intst_i(1)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                flagTopBottom = TVE_SYNCGEN_STATUS_I_get_i_field(*(volatile unsigned int *)TVE_SYNCGEN_STATUS_I_reg);
                                //0xb8018024
                                rtd_outl(TVE_INTPOS_I_reg,
                                                 TVE_INTPOS_I_write_en2(1)|TVE_INTPOS_I_int_vpos(flagTopBottom ? 2 : /*270*/313)|
                                                 TVE_INTPOS_I_write_en1(1)|TVE_INTPOS_I_int_hpos(0));
				//0xb80057fc
					     rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1-flagTopBottom));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            
                        }
                    }
                }
            }
            break;

        case 4: //576p
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(3)|
                                         VO_V1_INDEX_3D_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(576));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(288));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(288));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(576));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(3)|
                                     VO_V1_INDEX_y(2));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(576));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(576));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
               // UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
               /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                           */
/*
				if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;                                
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            */
                        }
                        if(TVE_Format3D==6)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        } 
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                    /*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }                            	
                            }
                        }*/
				if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	

					
                    }
                }
            }
            break;

        case 5: //720p_60
        case 20: //720p_50
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(5)|
                                         VO_V1_INDEX_3D_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1280)|
                                         VO_V1_SIZE_h(720));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1280)|
                                         VO_M1_SIZE_h(720));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1280)|
                                         VO_V1_SIZE_h(360));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1280)|
                                         VO_M1_SIZE_h(360));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(640)|
                                         VO_V1_SIZE_h(720));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(640)|
                                         VO_M1_SIZE_h(720));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(1280)|
                                     VO_V1_SIZE_h(720));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(1280)|
                                     VO_M1_SIZE_h(720));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
              }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
              //  UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;

                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        /*
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;                                
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }*/
                        }
                        if(TVE_Format3D==6)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        } 
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
          		/*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }                            	
                            }
                        }*/	
				if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	
		

				
                    }
                }
            }
            break;

        case 6: //1080i_50
		  if(colorbar==4)
		{
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(7)|
                                         VO_V1_INDEX_3D_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(540));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(270));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(270));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(960)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(960)|
                                         VO_M1_SIZE_h(540));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(1920)|
                                     VO_V1_SIZE_h(540));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(1920)|
                                     VO_M1_SIZE_h(540));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
    
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb801802c  //50i
                rtd_outl(TVE_INTPOS_P2_reg,
                                 TVE_INTPOS_P2_write_en2(1)|TVE_INTPOS_P2_int_vpos(565)|
                                 TVE_INTPOS_P2_write_en1(1)|TVE_INTPOS_P2_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
		while(*TVE_UART_flag==1)
            {
             //   UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
                            //***L odd frame***
                            /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                            /*
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }  */
                        }
                        if(TVE_Format3D==6)
                        {/*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        }
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }*/
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                    /*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& !flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 1;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(0));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&&flagTopBottom==1)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 0;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(1));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        */
                        if(Timing_Gen)
                        {
                        /*
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }*/
                        }
                        else
                        {
                        /*
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                            */
				if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	

						
                        }
                    }
                }
            }
            break;
		
        case 7: //1080i_60
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(7)|
                                         VO_V1_INDEX_3D_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(540));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(270));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(270));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(960)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(960)|
                                         VO_M1_SIZE_h(540));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(1920)|
                                     VO_V1_SIZE_h(540));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(1920)|
                                     VO_M1_SIZE_h(540));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
    
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb801802c
                rtd_outl(TVE_INTPOS_P2_reg,
                                 TVE_INTPOS_P2_write_en2(1)|TVE_INTPOS_P2_int_vpos(565)|
                                 TVE_INTPOS_P2_write_en1(1)|TVE_INTPOS_P2_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
             //   UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
                            //***L odd frame***
                            /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                            /*
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }  */
                        }
                        if(TVE_Format3D==6)
                        {/*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        }
                        if(TVE_Format3D==8)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }*/
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                    /*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& !flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 1;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(0));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&&flagTopBottom==1)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
    
                            flagTopBottom = 0;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(1));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        */
                        if(Timing_Gen)
                        {
                        /*
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }*/
                        }
                        else
                        {
                        /*
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                            */
				if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            	

						
                        }
                    }
                }
            }
            break;

        case 18: //1080p24
        case 19: //1080p30
        case 15: //1080p50
        case 16: //1080p60
            if(colorbar==4)
            {
                if(TVE_Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|  
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(TVE_Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(7)|
                                         VO_V1_INDEX_3D_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(1080));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(1080));
                    }
                    if(TVE_Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(540));
                    }
                    if(TVE_Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(960)|
                                         VO_V1_SIZE_h(1080));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(960)|
                                         VO_M1_SIZE_h(1080));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                //0xb8005000
                rtd_outl(VO_MODE_reg,
                                 VO_MODE_ch2i(1)|
                                 VO_MODE_ch2(1)|
                                 VO_MODE_ch1i(1)|
                                 VO_MODE_ch1(0)|
                                 VO_MODE_write_data(0));
                //0xb8005000
                rtd_outl(VO_MODE_reg,
                                 VO_MODE_ch2i(0)|
                                 VO_MODE_ch2(0)|
                                 VO_MODE_ch1i(0)|
                                 VO_MODE_ch1(1)|
                                 VO_MODE_write_data(1));
                if(Timing_Gen)
                {
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                }
                else
                {
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(1));
                }
                //0xb8005008
                rtd_outl(VO_MIX1_reg,
                                 VO_MIX1_i_vbi(1)|
                                 VO_MIX1_csr(1)|
                                 VO_MIX1_osd2(1)|
                                 VO_MIX1_osd1(1)|
                                 VO_MIX1_sub1(1)|
                                 VO_MIX1_v2(1)|
                                 VO_MIX1_v1(1)|
                                 VO_MIX1_pic(1)|
                                 VO_MIX1_bg(1)|
                                 VO_MIX1_write_data(0));
                //0xb8005008
                rtd_outl(VO_MIX1_reg,
                                 VO_MIX1_i_vbi(0)|
                                 VO_MIX1_vbi(0)|
                                 VO_MIX1_csr(0)|
                                 VO_MIX1_osd2(0)|
                                 VO_MIX1_osd1(0)|
                                 VO_MIX1_sub1(0)|
                                 VO_MIX1_v2(0)|
                                 VO_MIX1_v1(1)|
                                 VO_MIX1_pic(0)|
                                 VO_MIX1_bg(1)|  
                                 VO_MIX1_write_data(1));
                //0xb8005020
                rtd_outl(VO_V1_reg,
                                 VO_V1_d3_dbh(1)|
                                 VO_V1_d3_dbw(1)|
                                 VO_V1_d3_dup(1)|
                                 VO_V1_st(1)|
                                 VO_V1_cd(1)|
                                 VO_V1_gfx(1)|
                                 VO_V1_di(1)|
                                 VO_V1_f422(1)|
                                 VO_V1_vs(1)|
                                 VO_V1_vs_near(1)|
                                 VO_V1_vs_yodd(1)|
                                 VO_V1_vs_codd(1)|
                                 VO_V1_hs(1)|
                                 VO_V1_hs_yodd(1)|
                                 VO_V1_hs_codd(1)|
                                 VO_V1_topfield(1)|
                                 VO_V1_dmaweave(1)|
                                 VO_V1_write_data(0));
                //0xb8005020
                rtd_outl(VO_V1_reg,
                                 VO_V1_d3_dbh(0)|
                                 VO_V1_d3_dbw(0)|
                                 VO_V1_d3_dup(0)|
                                 VO_V1_st(0)|
                                 VO_V1_cd(0)|
                                 VO_V1_gfx(0)|
                                 VO_V1_di(0)|
                                 VO_V1_f422(1)|
                                 VO_V1_vs(0)|
                                 VO_V1_vs_near(0)|
                                 VO_V1_vs_yodd(0)|
                                 VO_V1_vs_codd(0)|
                                 VO_V1_hs(0)|
                                 VO_V1_hs_yodd(0)|
                                 VO_V1_hs_codd(0)|
                                 VO_V1_topfield(0)|
                                 VO_V1_dmaweave(0)|
                                 VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(7)|
                                     VO_V1_INDEX_y(6));

                //0xb8005058
                rtd_outl(VO_V1_SIZE_reg,
                                 VO_V1_SIZE_w(1920)|
                                 VO_V1_SIZE_h(1080));
                //0xb8005788
                rtd_outl(VO_M1_SIZE_reg,
                                 VO_M1_SIZE_w(1920)|
                                 VO_M1_SIZE_h(1080));
                //0xb8005794
                rtd_outl(VO_V1_XY_reg,
                                 VO_V1_XY_x(0)|
                                 VO_V1_XY_y(0));
                //0xb80057f4
                rtd_outl(VO_CHI_BUF_reg,
                                 VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                 VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                //0xb80057fc
                rtd_outl(VO_CH1_reg,
                                 VO_CH1_itop(1)|
                                 VO_CH1_ireint(1)|
                                 VO_CH1_top(1)|
                                 VO_CH1_reint(1)|
                                 VO_CH1_write_data(0));
                //0xb80056e0
                rtd_outl(VO_DMA_reg,
                                 VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                 VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                 VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                 VO_DMA_write_en1(0)|VO_DMA_l(0));
              }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

            while(*TVE_UART_flag==1)
            {
            //    UART_READ();
                if(*CC_NTSC_flag==0) CC_NTSC_enable=0;
                else CC_NTSC_enable=1;
                if(*CC_PAL_flag==0) CC_PAL_enable=0;
                else CC_PAL_enable=1;
                if(*WSS_flag==0) WSS_PAL_enable=0;
                else WSS_PAL_enable=1;
                if(*TT_flag==0) TT_PAL_enable=0;
                else TT_PAL_enable=1;
                if(*CGMS_flag==0) CGMS_NTSC_enable=0;
                else CGMS_NTSC_enable=1;
                if(*VPS_flag==0) VPS_enable=0;
                else VPS_enable=1;
                if(*DrawingMode_flag==0) DrawingMode_enable=0;
                else DrawingMode_enable=1;
                if(colorbar==4)
                {
                    if(TVE_Enable3D==1)
                    {
                        if(TVE_Format3D==0)
                        {
                        /*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;                                
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }*/
                        }
                        if(TVE_Format3D==6)
                        {/*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        } 
                        if(TVE_Format3D==8)
                        {/*
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));                            
                            }*/
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {/*
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }                            	
                            }
                        }*/
				if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }                            		

						
                    }
                }
            }
            break;
    }
    return;
}
#endif

void tve_init_setting()
{
	 printk(" tve_init_setting\n");

	rtd_maskl(0xb8000000,~_BIT19, _BIT19);
	rtd_outl(0xb8000004, 0xffffffff);
	rtd_outl(0xb8000008, 0xffffffff);
	rtd_outl(0xb800000C, 0xffffffff);
	rtd_outl(0xb8000010, 0xffffffff);
	rtd_outl(0xb8000014, 0xffffffff);
	rtd_outl(0xb8000018, 0x00000000);      //ATVIN_CLK_SEL 0x0:IFD
	rtd_outl(0xb8020104,0x00050009);  // APLL_ADC LDO power, for PLL27X

	 printk(" tve_init_setting..end\n");

}
int QC_Verifier_TVE_BOX(void)
{
	UINT32 mode, colorbar, pattern;
	UINT32 RGB_mode, video_format;
	UINT32 CC_NTSC_enable = 1;
    	UINT32 CC_PAL_enable = 1;
    	UINT32 WSS_PAL_enable = 1;
    	UINT32 CGMS_NTSC_enable = 1;
   	 UINT32 TT_PAL_enable = 1;
   	 UINT32 VPS_enable = 1;
   	 UINT32 DrawingMode_enable = 1;
	 UINT32 test_pattern[]={3,1,1,16};
	 UINT8 i=0;
	 int result=0;
	/*Default display type=============================================
	 480i ntsc cvbs mode=1
 	 576i  pal cvbs mode=3
        1080p50  mode=15
	 1080p60  mode=16
	
	==========================================================*/




#if 1
	for(i=0;i<=3;i++)
       {
	   
		mode =test_pattern[i];
		printk("  mode=%d\n",mode);
		colorbar = 15;
		pattern=0;
		RGB_mode = 1;
		video_format = 1;
	    	*CC_NTSC_flag=1;
	       *CC_PAL_flag=1;
	       *WSS_flag=1;
	       *CGMS_flag=1;
	       *TT_flag=1;
	       *VPS_flag=1;
	       *DrawingMode_flag=1;	
		  printk(" tve init is start\n");
		 tve_init_setting();
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		TVE_Display(mode, colorbar, RGB_mode, video_format);		//TVE_Run_loop(mode,RGB_mode,video_format,colorbar,CC_NTSC_enable,CC_PAL_enable,WSS_PAL_enable,CGMS_NTSC_enable,TT_PAL_enable,VPS_enable,DrawingMode_enable,0,0,0);//,0);
		udelay(20);  




	printk("  test pattern=%d\n",test_pattern[i]);
	//#ifndef CONFIG_OLT
	switch(i)
	{
		  case 0:
		  	printk(" test  cvbs pal\n");
        		result=UART1_to_MAC(VDC_EQC,1);
			//result=UART1_to_MAC(VDC_EQC,0);
			if(result==FAILED)
				printk(" test  cvbs pal ....fail\n");
		 break;	
		   case 1:
		   	printk(" test  cvbs ntsc\n");
			result=UART1_to_MAC(VDC_EQC,0);
			if(result==FAILED)
				printk(" test  cvbs ntsc ....fail\n");
		 break;
		 case 2:
		 	printk(" test  ypbpr 480i(ntsc )\n");
			result=UART1_to_MAC(IMD_EQC,0);
			if(result==FAILED)
				printk(" test  ypbpr 480i(ntsc).....fail\n");
		 break;
		   case 3:
		   	printk(" test  ypbpr 1080p\n");
			result=UART1_to_MAC(IMD_EQC,1);
			if(result==FAILED)
				printk(" test  ypbpr 1080p......fail\n");
		 break;
	}	
	//#endif
		if(result==FAILED)
	return FAILED;

	}
		return  SUCCESS;
#else

	#if 0
		i=1;//0
	       mode =test_pattern[i];
		colorbar = 15;
		pattern=0;
		RGB_mode = 1;
		video_format = 1;
	    	*CC_NTSC_flag=1;
	       *CC_PAL_flag=1;
	       *WSS_flag=1;
	       *CGMS_flag=1;
	       *TT_flag=1;
	       *VPS_flag=1;
	       *DrawingMode_flag=1;
		 printk(" tve init is start\n");
		 tve_init_setting();
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		TVE_Display(mode, colorbar, RGB_mode, video_format);		//TVE_Run_loop(mode,RGB_mode,video_format,colorbar,CC_NTSC_enable,CC_PAL_enable,WSS_PAL_enable,CGMS_NTSC_enable,TT_PAL_enable,VPS_enable,DrawingMode_enable,0,0,0);//,0);
		//MV_set(RGB_mode,8);
		printk(" test  cvbs ntsc\n");
		result=UART1_to_MAC(VDC_EQC,0);
			if(result==FAILED)
				printk(" test  cvbs ntsc ....fail\n");

		return  SUCCESS;
		//return FAILED;
	#else
		i=3; //0
	       mode =test_pattern[i];
		colorbar = 15;
		pattern=0;
		RGB_mode = 1;
		video_format = 1;
	    	*CC_NTSC_flag=1;
	       *CC_PAL_flag=1;
	       *WSS_flag=1;
	       *CGMS_flag=1;
	       *TT_flag=1;
	       *VPS_flag=1;
	       *DrawingMode_flag=1;
		 printk(" tve init is start\n");
		 tve_init_setting();
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		 printk(" tve init is end\n");
		TVE_Display(mode, colorbar, RGB_mode, video_format);		//TVE_Run_loop(mode,RGB_mode,video_format,colorbar,CC_NTSC_enable,CC_PAL_enable,WSS_PAL_enable,CGMS_NTSC_enable,TT_PAL_enable,VPS_enable,DrawingMode_enable,0,0,0);//,0);
		//MV_set(RGB_mode,8);
			result=UART1_to_MAC(IMD_EQC,1);
			if(result==FAILED)
				printk(" test  ypbpr 1080p ....fail\n");

		return  SUCCESS;
		//return FAILED;


	#endif
#endif

}
