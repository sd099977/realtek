
void drv_ifd_analog_preset(void)
{

	/************** From drvif_module_vdc_PowerCtrl() ****************/
	rtd_maskl(0xb8000004, 0xffffffff, _BIT16 | _BIT17);
	rtd_maskl(0xb8000008, 0xffffffff, _BIT19 | _BIT4 | _BIT10);
	rtd_maskl(0xb800000c, 0xffffffff, _BIT26);
	rtd_maskl(0xb8000014, 0xffffffff, _BIT27 | _BIT24);
	rtd_maskl(0xb8000018, ~(_BIT17), 0x0);
	rtd_maskl(0xb8000240,0xffffff80, 0x0E);
	rtd_maskl(0xb800024C, ~(_BIT12 | _BIT17), _BIT25 | _BIT13 | _BIT16);
	rtd_outl(0xb8000248, 0x00000000);      //Power off and rst PLL27x
	rtd_outl(0xb8000248, 0x00000017);			 //Power on PLL27x
	udelay(5);
	rtd_outl(0xb8020000,0x000000FF); 
	rtd_outl(0xb802005C,0x20000003); 
	rtd_outl(0xb8020054,0x04680001); 
	rtd_maskl(0xb8020058, 0xfffffffc, 0x0); 

	/************** IFD API ****************/
	//System Clock and Reset
	rtd_maskl(CRT_SOFT_RESET2_VADDR, ~(_BIT16 | _BIT17), _BIT16 | _BIT17);   
	rtd_maskl(CRT_SOFT_RESET3_VADDR, ~(_BIT11|_BIT5),  _BIT11|_BIT5);//IFD_SOFT_RESET3
	rtd_maskl(CRT_GROUP1_CK_EN_VADDR, ~(_BIT26|_BIT23|_BIT16),  _BIT26|_BIT23|_BIT16);//CLKEN_IF_DEMOD 
	rtd_maskl(CRT_GROUP1_CK_SEL_VADDR, ~_BIT17, 0<<17);	//ATVIN_CLK_SEL
	//PLL27, ADC CLK **drv_ifd_adc_clock_default()
	rtd_outl(CRT_SYS_PLL_27X1_VADDR, 0x02240016);
	rtd_outl(CRT_SYS_PLL_27X2_VADDR, 0x00105511);
	rtd_outl(CRT_SYS_PLL_27X4_VADDR, 0x420FCD05);
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, 0x00000000);      		//Power off and rst PLL27x
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, 0x0000001f);		//Power on PLL27x
	drv_ifd_adc_clock_source_set(IFD_ANA_DEMOD);
	rtd_maskl(CRT_GROUP1_CK_SEL_VADDR, ~(_BIT17), 0);	//ATV Input clcok select 1: Video Decoder Clock 0: IF Demod Clock
	//IFADC and RSSI, LSADC **drv_ifd_adc_default();
	rtd_maskl(IFD_ANALOG_IFADC_POW_VADDR,~(_BIT28|_BIT24|_BIT20|_BIT16|_BIT12|_BIT8),(_BIT28|_BIT24|_BIT20|_BIT16|_BIT12|_BIT8)); 
	rtd_outl(IFD_ANALOG_IFADC_CTRL1_VADDR, (0x2<<28)|(0x1<<16)|(0x0));
       rtd_outl(IFD_ANALOG_IFADC_CTRL2_VADDR, (0x1<<28)|(0x2<<20)|(0x4<<16)|(0x0));
	rtd_outl(IFD_ANALOG_IFADC_SERVO_VADDR, (0x0));	
	rtd_outl(IFD_ANALOG_IFADC_MBIAS_VADDR, (0xaaa<<20)|(0x2<<16)|(0x0));
	rtd_outl(IFD_ANALOG_LSADC_RSSI_CTRL_VADDR, (0x2<<8)|(0x2<<4)|(0x1));
	rtd_outl(IFD_ANALOG_LSADC_RSSI_POW_MBIAS_VADDR, (0x1)<<8|(0x2<<4)|(0x1));
	//DAC **drv_ifd_dac_default();
	rtd_outl(IFD_ANALOG_VDAC_BSO_VADDR, (0x1<<12)|(0x4<<8)|(0x5<<4)|(0x2));
	rtd_outl(IFD_ANALOG_VDAC_VADDR, (0x1<<20)|(0x2<<16)|(0x0));
	rtd_outl(IFD_ANALOG_VDAC_TV_CTRL1_VADDR, (0x1<<16)|(0x1<<12)|(0xf<<4)|(0x0));
	rtd_outl(IFD_ANALOG_VDAC_TV_CTRL2_VADDR, (0x6<<8)|(0x1<<4)|(0x1));
	rtd_outl(IFD_ANALOG_VDAC_TV_SRC_SEL_VADDR, (0x0));
	return;
}

void drv_ifd_power_on(bool enable)
{
	if(enable) 
		rtd_maskl(IFD_ANALOG_IFADC_POW_VADDR,~(_BIT28|_BIT24|_BIT20|_BIT16|_BIT12|_BIT8),(_BIT28|_BIT24|_BIT20|_BIT16|_BIT12|_BIT8));
	else
		rtd_maskl(IFD_ANALOG_IFADC_POW_VADDR,~(_BIT28|_BIT24|_BIT20|_BIT16|_BIT12),0);
	return;
}

void drv_ifd_set_adcinput_swing(IFD_ADC_SHAGAIN setting1, IFD_ADC_FULLSCALE setting2)
{
	IFADC_CTRL2_RBUS ifadc_ctrl2_rbus_data;

	ifadc_ctrl2_rbus_data.regValue = rtd_inl(IFD_ANALOG_IFADC_CTRL2_VADDR);
	ifadc_ctrl2_rbus_data.reg_adc2x_vref_sel = setting2;
	rtd_outl(IFD_ANALOG_IFADC_CTRL2_VADDR, ifadc_ctrl2_rbus_data.regValue);

}

void drv_ifd_adc_clock_source_set(IFD_IFADC_MUX value)
{
	sys_pll_27x4_RBUS adc_clock_source_rbus_data;

	adc_clock_source_rbus_data.regValue = rtd_inl(CRT_SYS_PLL_27X4_VADDR);
	adc_clock_source_rbus_data.pll_ck_ifadc_mux =value;
	rtd_outl(CRT_SYS_PLL_27X4_VADDR, adc_clock_source_rbus_data.regValue);

}

void drv_ifd_adc_input_sel(IFD_ADC_INPUT_SEL input_source)
{

	IFADC_CTRL1_RBUS ain_sel_rbus_data;
       IFADC_POW_RBUS adc_ifgpapow_rbus_data;

	ain_sel_rbus_data.regValue = rtd_inl(IFD_ANALOG_IFADC_CTRL1_VADDR);
	ain_sel_rbus_data.reg_adc2x_insel = input_source;
	rtd_outl(IFD_ANALOG_IFADC_CTRL1_VADDR, ain_sel_rbus_data.regValue);

       adc_ifgpapow_rbus_data.regValue = rtd_inl(IFD_ANALOG_IFADC_POW_VADDR); // power dn pga when not used
       if(input_source ==IFD_ADC_INPUT_SEL_IFPGA)
           adc_ifgpapow_rbus_data.reg_adc2x_ifpgapow = IFD_ENABLE;
       else
           adc_ifgpapow_rbus_data.reg_adc2x_ifpgapow = IFD_DISABLE;
       rtd_outl(IFD_ANALOG_IFADC_POW_VADDR, adc_ifgpapow_rbus_data.regValue);
}

void drv_ifd_adc_clock_default(void)//modify for mac2
{
	//ADC 162M with VCO648M
	rtd_outl(CRT_SYS_PLL_27X1_VADDR, 0x02240016);
	rtd_outl(CRT_SYS_PLL_27X2_VADDR, 0x00105511);
	rtd_outl(CRT_SYS_PLL_27X4_VADDR, 0x420FCD05);
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, 0x00000000);      		//Power off and rst PLL27x
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, 0x0000001f);			//Power on PLL27x
	drv_ifd_adc_clock_source_set(IFD_ANA_DEMOD);
	rtd_maskl(CRT_GROUP1_CK_SEL_VADDR, ~(_BIT17), 0);	//ATV Input clcok select 1: Video Decoder Clock 0: IF Demod Clock
}

void drv_ifd_adc_clock(IFD_CLK_RATE adc_clock)
{
	drv_ifd_adc_clock_default();//Clear setting to default
	switch(adc_clock)
	{
		case IFD_CLK_RATE_54M:
			rtd_maskl(CRT_SYS_PLL_27X1_VADDR, ~((0x7<<16)|(0x7F)), (0x4<<16)|(0xe));
			rtd_maskl(CRT_SYS_PLL_27X2_VADDR, ~(0x3<<4), (0x2<<4));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x0<<8));//PLL27X_IFADC_CKO_EN=0x0, for change ifadc duty
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~((0x3<<29)|(0x3<<16)|(0x3<<10)|(0x1<<9)) ,(0x2<<29)|(0x1<<16)|(0x1<<10)|(0x0<<9));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x1<<8));
		break;
		case IFD_CLK_RATE_108M:
			rtd_maskl(CRT_SYS_PLL_27X1_VADDR, ~((0x7<<16)|(0x7F)), (0x4<<16)|(0xe));
			rtd_maskl(CRT_SYS_PLL_27X2_VADDR, ~(0x3<<4), (0x2<<4));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x0<<8));//PLL27X_IFADC_CKO_EN=0x0, for change ifadc duty
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~((0x3<<29)|(0x3<<16)|(0x3<<10)|(0x1<<9)) ,(0x2<<29)|(0x1<<16)|(0x2<<10)|(0x0<<9));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x1<<8));
		break;
		case IFD_CLK_RATE_135M:
			rtd_maskl(CRT_SYS_PLL_27X1_VADDR, ~((0x7<<16)|(0x7F)), (0x3<<16)|(0x12));
			rtd_maskl(CRT_SYS_PLL_27X2_VADDR, ~(0x3<<4), (0x3<<4));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x0<<8));//PLL27X_IFADC_CKO_EN=0x0, for change ifadc duty
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~((0x3<<29)|(0x3<<16)|(0x3<<10)|(0x1<<9)) ,(0x2<<29)|(0x0<<16)|(0x3<<10)|(0x0<<9));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x1<<8));
		break;
		default:
		case IFD_CLK_RATE_162M:
			rtd_maskl(CRT_SYS_PLL_27X1_VADDR, ~((0x7<<16)|(0x7F)), (0x2<<16)|(0xa));
			rtd_maskl(CRT_SYS_PLL_27X2_VADDR, ~(0x3<<4), (0x0<<4));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x0<<8));//PLL27X_IFADC_CKO_EN=0x0, for change ifadc duty
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~((0x3<<29)|(0x3<<16)|(0x3<<10)|(0x1<<9)) ,(0x1<<29)|(0x2<<16)|(0x3<<10)|(0x1<<9));
			rtd_maskl(CRT_SYS_PLL_27X4_VADDR, ~(0x1<<8), (0x1<<8));
		break;
	}
}

void drv_ifd_adc_pga_gain_fix(bool enable, IFD_ADC_PGAFIX_CTRL fix_pga_gain)
{
	IFADC_CTRL1_RBUS ifdadc_ctrl1_rbus_data;

	ifdadc_ctrl1_rbus_data.regValue = rtd_inl(IFD_ANALOG_IFADC_CTRL1_VADDR);
	ifdadc_ctrl1_rbus_data.reg_adc2x_fixgain_en = enable; //1:FIX 2.5dB
	ifdadc_ctrl1_rbus_data.reg_adc2x_fixgain_ctrl = fix_pga_gain;
	rtd_outl(IFD_ANALOG_IFADC_CTRL1_VADDR, ifdadc_ctrl1_rbus_data.regValue);
}
