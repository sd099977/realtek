#include <qc_verify_common.h>
#include <VBI_qc.h>
#include <VBI_verify.h>
#include <rbusVbiReg.h>
#include <rbusVDTopReg.h>


void vbi_delay(UINT32 count)
{
	UINT32 ulDelay;
	for(ulDelay=0;ulDelay<count;ulDelay++)
	{
        	udelay(100);
	}
}

void Clock_setting_script(void)
{
	//PLL RST and Enable CLK
	rtd_maskl(0xb8000004,0xFFFFFFFF,0x00030000);//Reset bit [16] RSTN_ATVIN [17]RSTN_ATVIN2
	rtd_maskl(0xb8000008,0xFFFFFFFF,0x00080410);//Reset bit [19] RSTN_VDEC Reset bit of  Video Decode (active low) [4] RSTN_APLL_ADC Reset bit of APLL_ADC [10] RSTN_VDEC2
	rtd_maskl(0xb800000c,0xFFFFFFFF,0x04000000);//[26] CLKEN_VDEC
	rtd_maskl(0xb8000014,0xFFFFFFFF,0x09000000);//Clock enable bit [27]Clock enable bit for ATV Input Control of Video Decoder [24] Clock enable bit for APLL_ADC
	rtd_maskl(0xb8000018,0xFFFFFFFF,0x00020000);//ATVIN_CLK_SEL[17], 0x0: IFD, 0x1: VD

	////PLL27x Clock : 108M
	rtd_maskl(0xb8000240,0xFFFFFFE0,0x0000000E);//PLL27X_M[6:0] = 0x0E

	//-------- VD ADC CLOCK------------------------------------------------
	//for Y/C
	//rtd_outl(0xb800024C,0x4007FC04); //[25]PLL_L2H_CML_POW = 1[12] PLL27X_YPPADC_CK54M_EN = 1; for Y/C switch [13]pll27x_yppadc_cko_en = 1
	//for CVBS
	//rtd_outl(0xb800024C,0x420de905); //[25]PLL_L2H_CML_POW = 1[12] PLL27X_YPPADC_CK54M_EN = 0; for Y [13]pll27x_yppadc_cko_en = 1 //4207EC04
	//---------------------------------------------------------------------
	rtd_maskl(0xb800024C,0xFFFCFFFF,0x02012000);	//[25]PLL_L2H_CML_POW = 1[12] PLL27X_YPPADC_CK54M_EN = 0; for Y [13]pll27x_yppadc_cko_en = 1 [17:16] = 0x1 01: divide by 4 (use when VCO=432MHz)
	rtd_outl(0xb8000248, 0x00000000);		//Power off and rst PLL27x
	rtd_outl(0xb8000248, 0x00000017);		//Power on PLL27x

	rtd_outl(0xb8003764,0x0008007F);		// bit[9:8]=01, select Select the VCO freq = 432M			// MISC_CONTROL
////////// VBI clock setting //////////
	rtd_outl(0xb8000008,0xFE0E7FFF);	// bit 8=1, set reset bit to 1
	rtd_outl(0xb8000014,0xE911179F);	// bit 20=1, VBI clock enable
	rtd_outl(0xb8000018,0x00020001);	// bit 5, VBI source, 0: Video Decoder,1: YPBPR
}

void  Silcer_Initial(void)
{
//	printk("Silcer_Initial...  \n");
//	printk("drvif_module_vdc_Initial done ...  \n");

//----------------       VD setting   start ------------------------------ 
//	rtd_outl(0xb8000508,0x000000B3); 	// enable VDC 27x clock bit[0,1,4,5,7]
//	printk("rtd_inl(0xb8000508)=%x  \n", rtd_inl(0xb8000508));
//	rtd_outl(0xb800050C,0x03031201); 	// select PLL27X_CKOUT_YPPADC_33V = 108M
//	printk("rtd_inl(0xb800050C)=%x  \n", rtd_inl(0xb800050C));
//	rtd_outl(VDC_MISC_CONTROL_VADDR,0x0002017F); 	// bit[9:8]=01, select Select the VCO freq = 540M
//	printk("rtd_inl(0xb8019764)=%x  \n", rtd_inl(0xb8019764));
//----------------       VD setting   end ------------------------------

//----------------       CC  setting  start ------------------------------
        //rtd_outl(VBI_VBISL0_VADDR, 0x01600022);  
        //rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x005a2717);  //  auto adjust slicer level 
        //rtd_outl(VBI_TT_VBI_NOISY_CTRL1_VADDR, 0x2050a023);  // bit 29  set that data from vd put through 16 tape low pass filter
        rtd_outl(VBI_TT_VBI_NOISY_CTRL4_VADDR, 0x0f141110);  //  resample data don't do "rounding" 

        rtd_outl(VBI_VBISL0_VADDR, 0x90000000);
        rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x006c2713);      // fix slicer level =6C 
        rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_9_12_VADDR, 0x00000000);	//line 9,10,11,12
        rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_13_16_VADDR, 0x00000000);
        rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_17_20_VADDR, 0x00000000);	//line 17,18,19,20
        rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR, 0x00001100);	//line 21,22,23,24
        rtd_outl(VBI_TT_VBI_DTO_REGISTER1_VADDR, 0x00001ad0);
        rtd_outl(VBI_TT_VBI_NOISY_CTRL3_VADDR, 0x005a0100);
        rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x00000000);
        rtd_outl(VBI_TT_VBI_NOISY_CTRL1_VADDR, 0x0f043110);
        rtd_outl(VBI_TT_VBI_PATTERN_SEL_VADDR, 0x0f001000);

	//rtd_outl(0xb8030800, 0x90000000);
	//rtd_outl(0xb8030a08, 0x00000000);		//line 9,10,11,12
	//rtd_outl(0xb8030a0c, 0x00000000);
	//rtd_outl(0xb8030a10, 0x00000000);		//line 17,18,19,20	
	//rtd_outl(0xb8030a14, 0x00001100);		//line 21,22,23,24
	//rtd_outl(0xb8030a20, 0x00001ad0);
	//rtd_outl(0xb8030a68, 0x005a0100);

        //rtd_outl(0xb8030a00, 0x4b4b2713);   
        //rtd_outl(0xb8030a30, 0x00004600);   
        //rtd_outl(0xb8030a6c, 0x00000000);   
        //rtd_outl(0xb8030a74, 0x0f143110);   
        //rtd_outl(0xb80193c4, 0x00000003); 

        rtd_outl(VBI_VBI_DEBUG_MODE_VADDR, 0x80000109);//CC,CGMS pattern gen enable  
        rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_25_26_VADDR, 0x00001111);//designed error ,need select all line except 7~25
//----------------       CC  setting  end ------------------------------
		

//----------------       CGMS  setting  start ------------------------------
       rtd_outl(VBI_VBISL0_VADDR,0x00000080);
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x00000000);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006413);
	rtd_outl(VBI_CGMS_C1_VADDR, 0x000a0027); 
	rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130);
	rtd_outl(VBI_CGMS_C5_VADDR, 0x0010241a);

        //rtd_outl(0xb8030900,0x0700641F);
        //rtd_outl(0xb8030904,0x000a0027);
        //rtd_outl(0xb8030908,0x00300130);
        //rtd_outl(0xb8030914,0x0010241a);
        rtd_outl(VBI_VBI_DEBUG_MODE_VADDR,0x00000100);

//看 0x5910=0x01080001  => CGMS 正確
//----------------       CGMS  setting  end ------------------------------
//	printk("Silcer_Initial done !!!  \n");
}

#ifdef Slicer_CC_test
UINT8 module_Slicer_CC_test(void)
{
	UINT32 i,j;
	UINT32 cc_detect;
	cc_detect = _FAIL;
	////////// check CC //////////
//	printk("Slicer_CC_test start   \n");

	i = 0;
    	while(i<first_delay)
    	{
        	udelay(100);
        	i++;
        	if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT17)==_BIT17) // Bit17 = 1
        	{	
//        		printk("VBI_TT_VBI_DATA_STATUS_VADDR=_BIT17   \n");

            		cc_detect = rtd_inl(VBI_TT_VBI_CCWSS_DATA_VADDR)&0x0000ffff;

            		if(cc_detect != CC_VALUE)
            		{
                     	j=0;
                       	while(j<two_delay)
                    		{
	                            udelay(50);
	                            udelay(50);
	                            j++;
	                           if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT17)==_BIT17) // Bit17 = 1
	                           {
						cc_detect = rtd_inl(VBI_TT_VBI_CCWSS_DATA_VADDR)&0x0000ffff;
						if(cc_detect != CC_VALUE)
						{
							printk("[Slicer #1] CC fai,the value==>%x  , j=%d \n", cc_detect,j );
							cc_detect = _FAIL;
						}
						else
						{
//							printk("[Slicer #1] CC pass!!\n");
							cc_detect = _SUCCESS;
							return cc_detect;
						}
	                            }
                            	rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT17, _BIT17);
                             	udelay(50);
                             	udelay(50);
                    		}
			}
			else
			{
				rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT17, _BIT17);
				udelay(50);
				udelay(50);
				udelay(50);
				udelay(50);
				udelay(50);

//				printk("[Slicer #1] CC pass!!\n");
				cc_detect = _SUCCESS;
				return cc_detect;
              	}
			
			rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT17, _BIT17);
			udelay(50);
			udelay(50);
			udelay(50);
			udelay(50);
			udelay(50);
		}
	}

	if(cc_detect == _FAIL)
	{
		printk("the VDC slicer1 detect cc is fail the detect value\n" );
		return _FAIL;
	}
}
#endif

#ifdef Slicer_CGMS_test
UINT8 module_Slicer_CGMS_test(void)
{
	UINT32 i,j;
	UINT32 cgms_detect;
	////////// check CGMS //////////
	i = 0;
	cgms_detect = _FAIL;
	rtd_maskl(VBI_CGMS_C4_VADDR, ~_BIT24, _BIT24);
	udelay(50);
	udelay(50);
	while(i<first_delay)
	{
		udelay(100);
		i++;
		if((rtd_inl(VBI_CGMS_C4_VADDR)&_BIT24)==_BIT24) // Bit24 = 1
		{
			cgms_detect = rtd_inl(VBI_CGMS_C4_VADDR)&0x000fffff;

			if(cgms_detect != CGMS_VALUE)
			{
				j=0;
				while(j<two_delay)
				{
					j++;
					udelay(50);
					udelay(50);
					if((rtd_inl(VBI_CGMS_C4_VADDR)&_BIT24)==_BIT24) // Bit24 = 1
					{
						cgms_detect = rtd_inl(VBI_CGMS_C4_VADDR)&0x000fffff;

						if(cgms_detect != CGMS_VALUE)
						{
							printk("[Slicer #1] CGMS fai,the value==>%x \n", cgms_detect );
							cgms_detect = _FAIL;
						}
						else
						{
//							printk("[Slicer #1] CGMS pass!!\n");
							cgms_detect = _SUCCESS;
							return cgms_detect;
						}
					}
					rtd_maskl(VBI_CGMS_C4_VADDR, ~_BIT24, _BIT24);
					udelay(50);
					udelay(50);
				}
			}
			else
			{	  
				rtd_maskl(VBI_CGMS_C4_VADDR, ~_BIT24, _BIT24);
				udelay(50);
				udelay(50);
				udelay(50);
				udelay(50);
				udelay(50);
//				printk("[Slicer #1] CGMS pass!!\n");
				cgms_detect = _SUCCESS;
				return cgms_detect;		
			}
			rtd_maskl(VBI_CGMS_C4_VADDR, ~_BIT24, _BIT24);
			udelay(50);
			udelay(50);
			udelay(50);
			udelay(50);
			udelay(50);
		}
	}

	if(cgms_detect == _FAIL)
	{
		printk("the VDC slicer1 detect CGMS is fail the detect value\n" );
		return _FAIL;
	}
}
#endif

#ifdef Slicer_mbist_test
UINT8 mbist_test(void)
{
	UINT8 i=0;

	rtd_maskl(SYSTEM_GROUP1_CK_EN_VADDR, ~_BIT20, 0);//reset VBI
	udelay(10);
	rtd_maskl(SYSTEM_GROUP1_CK_EN_VADDR, ~_BIT20, _BIT20);
	udelay(10);

	rtd_maskl(SYSTEM_SOFT_RESET3_VADDR, ~_BIT9, 0);//reset VBI
	udelay(10);
	rtd_maskl(SYSTEM_SOFT_RESET3_VADDR, ~_BIT9, _BIT9);

	rtd_maskl(VBI_BIST_TEST1_VADDR, ~_BIT0, _BIT0);//Sram power on
	rtd_maskl(VBI_BIST_MODE_VADDR, ~_BIT0, _BIT0);//bist_mode 設 1

	for (i=0; i < 50;i++)
	{
		udelay(1000);
		if (rtd_inl(VBI_BIST_DONE_VADDR)&_BIT0)
		{
			break;
		}
	}

	if (i == 50)
		printk("[Slicer] mbist test time out!!\n");
	else
	{
		if((rtd_inl(VBI_BIST_FAIL_VADDR)&_BIT0) == 0)
			return _SUCCESS;
	}
	return _FAIL;
}
#endif

#ifdef Slicer_mbist_drf_test
UINT8 mbist_drf_test(void)
{
	UINT8 i =0;
	
	rtd_maskl(SYSTEM_GROUP1_CK_EN_VADDR, ~_BIT20, 0);//reset VBI
	udelay(10);
	rtd_maskl(SYSTEM_GROUP1_CK_EN_VADDR, ~_BIT20, _BIT20);
	udelay(10);

	rtd_maskl(SYSTEM_SOFT_RESET3_VADDR, ~_BIT9, 0);//reset VBI
	udelay(10);
	rtd_maskl(SYSTEM_SOFT_RESET3_VADDR, ~_BIT9, _BIT9);

	rtd_maskl(VBI_BIST_TEST1_VADDR, ~_BIT0, _BIT0);//Sram power on
	rtd_maskl(VBI_BIST_DRF_MODE_VADDR, ~_BIT0, _BIT0);//bist_mode_drf 設 1

	for (i=0; i < 50;i++)
	{
		udelay(1000);
		if (rtd_inl(VBI_BIST_DRF_PAUSE_VADDR)&_BIT0)//bist_drf_start_pause 舉1 
		{
			break;
		}
	}
	if (i == 50)
		printk("[Slicer] mbist_drf  test time out 1!!\n");
	
	rtd_maskl(VBI_BIST_DRF_RESUME_VADDR, ~_BIT0,_BIT0);//Mbist_dma resume
	udelay(1000);
	rtd_maskl(VBI_BIST_DRF_RESUME_VADDR, ~_BIT0,0);
	
	for (i=0; i < 50;i++)
	{
		udelay(1000);
		if (rtd_inl(VBI_BIST_DRF_PAUSE_VADDR)&_BIT0)//bist_drf_start_pause 舉1 
		{
			break;
		}
	}
	if (i == 50)
		printk("[Slicer] mbist_drf  test time out 2!!\n");	

	rtd_maskl(VBI_BIST_DRF_RESUME_VADDR, ~_BIT0,_BIT0);//Mbist_dma resume
	udelay(1000);
	rtd_maskl(VBI_BIST_DRF_RESUME_VADDR, ~_BIT0,0);

	for (i=0; i < 50;i++)
	{
		udelay(1000);
		if (rtd_inl(VBI_BIST_DONE_DRF_VADDR)&_BIT0)
		{
			break;
		}
	}	

	if (i == 50)
		printk("[Slicer] mbist_drf  test time out 3!!\n");	
	else
	{
		if((rtd_inl(VBI_BIST_FAIL_DRF_VADDR)&_BIT0) == 0)
			return _SUCCESS;
	}
	return _FAIL;		
	

}
#endif







int QC_Verifier_VBI(void)
{
	UINT32 i;
	Clock_setting_script();

//== QC_test start ======================================
#ifdef QC_test
	Silcer_Initial();

	vbi_delay(1000);

#ifdef Slicer_CC_test
	if(module_Slicer_CC_test()==_SUCCESS)
		printk("[Slicer] CC pass!!\n");
	else
	{
		printk("[Slicer] CC fail!!\n");
		return _FAIL;
	}
#endif
#ifdef Slicer_CGMS_test
	if(module_Slicer_CGMS_test()==_SUCCESS)
		printk("[Slicer] CGMS pass!!\n");
	else
	{
		printk("[Slicer] CGMS fail!!\n");
		return _FAIL;
	}
#endif 
#ifdef Slicer_mbist_test	
	if (mbist_test() == _SUCCESS)
		printk("[Slicer] mbist pass!!\n");
	else
	{
		printk("[Slicer] mbist fail!!\n");
		return _FAIL;
	}
#endif
#ifdef Slicer_mbist_drf_test
	if (mbist_drf_test() == _SUCCESS)
		printk("[Slicer] mbist_drf pass!!\n");
	else
	{
		printk("[Slicer] mbist_drf fail!!\n");
		return _FAIL;
	}
#endif
//== QC_test end  ======================================
#else
	Display_Init();
	rtd_outl(VBI_VBI_DEBUG_MODE_VADDR, 0x00000000);//CC,CGMS pattern gen disable
#endif

//== CC_verify_test start ==================================
#ifdef CC_verify_test
#ifdef AV_Input
	AV_Init();
#endif
#ifdef IFD_Input
	IFD_Init();
#endif
	if((rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & _BIT0) == 0)
	{
		CC_Init();
		vbi_delay(1500);
		CC_verify();
	}
	else
		printk("Error : CC_verify_test no signal ~\n");
#endif
//== CC_verify_test end  ==================================

//== CGMS_test start ====================================
#ifdef CGMS_test
#ifdef AV_Input
	AV_Init();
#endif
#ifdef YPP_Input
	YPbPr_Init();
#endif
	CGMS_Init();
	CGMS_verify();
#endif
//== CGMS_test end  ====================================

//== TT_WSS_VPS_test start ===============================
#ifdef TT_WSS_VPS_test
#ifdef AV_Input
	AV_Init();
#endif
#ifdef IFD_Input
	IFD_Init();
#endif
	vbi_delay(1500);
	TT_WSS_VPS_Init();
#ifdef TT_DMA_test
	DMA_Init();
#endif
	TT_WSS_VPS_verify();
#endif
//== TT_WSS_VPS_test end  ===============================

	return _SUCCESS;
}



