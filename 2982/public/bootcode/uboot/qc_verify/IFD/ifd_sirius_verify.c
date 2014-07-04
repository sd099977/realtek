
void drv_ifd_verify_cr_freq_phase_variance(void)
{
	UINT8 i;
	INT16 phase_error_mean, freq_error_mean, min_mean=0x0, max_mean=0x8000, power_diff;
	UINT16 phase_error_var,freq_error_var, min_var=0xffff, max_var=0x0000;

	min_mean=0x0;
	max_mean=0x8000;
	min_var=0xffff; 
	max_var=0x0;
	printf("1024 point, line base, ");
	rtd_maskl(IFD_CR_FREQ_ERROR_AVG_SET_VADDR, ~((0xfff<<8)|0x1), (0x400<<8)|0x1);
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		freq_error_mean = drv_ifd_cr_freq_error_mean_get_info();
		freq_error_var = drv_ifd_cr_freq_error_var_get_info();
		if(freq_error_mean<min_mean) min_mean=freq_error_mean;
		if(freq_error_mean>max_mean) max_mean=freq_error_mean;
		if(freq_error_var<min_var) min_var=freq_error_var;
		if(freq_error_var>max_var) max_var=freq_error_var;
		ScalerTimer_DelayXms(100);
	}
	printf( "freq_error_mean=0x%04x~0x%04x, freq_error_var=0x%04x~0x%04x\n", min_mean, max_mean, min_var, max_var);

	min_mean=0x0;
	max_mean=0x8000;
	min_var=0xffff; 
	max_var=0x0;
	printf( "512 point, point base, ");
	rtd_maskl(IFD_CR_FREQ_ERROR_AVG_SET_VADDR, ~((0xfff<<8)|0x1), (0x200<<8)|0x0); 
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		freq_error_mean = drv_ifd_cr_freq_error_mean_get_info();
		freq_error_var = drv_ifd_cr_freq_error_var_get_info();
		if(freq_error_mean<min_mean) min_mean=freq_error_mean;
		if(freq_error_mean>max_mean) max_mean=freq_error_mean;
		if(freq_error_var<min_var) min_var=freq_error_var;
		if(freq_error_var>max_var) max_var=freq_error_var;
		ScalerTimer_DelayXms(100);
	}
	printf( "freq_error_mean=0x%04x~0x%04x, freq_error_var=0x%04x~0x%04x\n", min_mean, max_mean, min_var, max_var);

	min_mean=0x0;
	max_mean=0x8000;
	min_var=0xffff; 
	max_var=0x0;
	printf( "1024 point, point base, ");
	rtd_maskl(IFD_CR_FREQ_ERROR_AVG_SET_VADDR, ~((0xfff<<8)|0x1), (0x400<<8)|0x0);
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		freq_error_mean = drv_ifd_cr_freq_error_mean_get_info();
		freq_error_var = drv_ifd_cr_freq_error_var_get_info();
		if(freq_error_mean<min_mean) min_mean=freq_error_mean;
		if(freq_error_mean>max_mean) max_mean=freq_error_mean;
		if(freq_error_var<min_var) min_var=freq_error_var;
		if(freq_error_var>max_var) max_var=freq_error_var;
		ScalerTimer_DelayXms(100);
	}
	printf( "freq_error_mean=0x%04x~0x%04x, freq_error_var=0x%04x~0x%04x\n", min_mean, max_mean, min_var, max_var);
	//Restore
	rtd_maskl(IFD_CR_FREQ_ERROR_AVG_SET_VADDR, ~((0x7ff<<21)|(0x1<<20)|(0xfff<<8)|(0x7<<4)|0x1), (IFD_CR_FREQ_ERROR_AVG_VINTERVAL<<21)|(0x1<<20)|(IFD_CR_FREQ_ERROR_AVG_INTERVAL<<8)|(IFD_CR_FREQ_ERROR_AVG_LENGTH<<4)|IFD_CR_FREQ_ERROR_AVG_LINEBASE);

	min_mean=0x0;
	max_mean=0x8000;
	min_var=0xffff; 
	max_var=0x0;
	printf("1024 point, line base, ");
	rtd_maskl(IFD_CR_PHASE_ERROR_AVG_SET_VADDR, ~((0xfff<<8)|0x1), (0x400<<8)|0x1);
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		phase_error_mean = drv_ifd_cr_phase_error_mean_get_info();
		phase_error_var = drv_ifd_cr_phase_error_var_get_info();
		if(phase_error_mean<min_mean) min_mean=phase_error_mean;
		if(phase_error_mean>max_mean) max_mean=phase_error_mean;
		if(phase_error_var<min_var) min_var=phase_error_var;
		if(phase_error_var>max_var) max_var=phase_error_var;
		ScalerTimer_DelayXms(100);
	}
	printf( "phase_error_mean=0x%04x~0x%04x, phase_error_var=0x%04x~0x%04x\n", min_mean, max_mean, min_var, max_var);

	min_mean=0x0;
	max_mean=0x8000;
	min_var=0xffff; 
	max_var=0x0;
	printf( "512 point, point base, ");
	rtd_maskl(IFD_CR_PHASE_ERROR_AVG_SET_VADDR, ~((0xfff<<8)|0x1), (0x200<<8)|0x0); 
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		phase_error_mean = drv_ifd_cr_phase_error_mean_get_info();
		phase_error_var = drv_ifd_cr_phase_error_var_get_info();
		if(phase_error_mean<min_mean) min_mean=phase_error_mean;
		if(phase_error_mean>max_mean) max_mean=phase_error_mean;
		if(phase_error_var<min_var) min_var=phase_error_var;
		if(phase_error_var>max_var) max_var=phase_error_var;
		ScalerTimer_DelayXms(100);
	}
	printf( "phase_error_mean=0x%04x~0x%04x, phase_error_var=0x%04x~0x%04x\n", min_mean, max_mean, min_var, max_var);

//Restore
	rtd_maskl(IFD_CR_PHASE_ERROR_AVG_SET_VADDR, ~((0x1<<25)|(0x1<<20)|(0xfff<<8)|(0x7<<4)|0x1), (0x1<<25)|(0x1<<20)|(IFD_CR_PHASE_ERROR_AVG_INTERVAL<<8)|(IFD_CR_PHASE_ERROR_AVG_LENGTH<<4)|IFD_CR_PHASE_ERROR_AVG_LINEBASE); //Enable to take the cr frequency error sample in vertival sync. Area


	min_mean=0x0;
	max_mean=0x8000;
	printf( "power diff ");
	rtd_maskl(IFD_POWER_CAL_VADDR, ~((0x1<<8)), (0x0<<8)); 
	ScalerTimer_DelayXms(500);
	for(i=0;i<10;i++){
		power_diff = rtd_inl(IFD_DIFF_POWER_STATUS_VADDR)&0xFFFF;
		if(power_diff<min_mean) min_mean=power_diff;
		if(power_diff>max_mean) max_mean=power_diff;
		ScalerTimer_DelayXms(100);
	}
	printf( "power_diff=0x%04x~0x%04x\n", min_mean, max_mean);

//Restore
	rtd_maskl(IFD_POWER_CAL_VADDR, ~((0x1<<8)), (0x1<<8)); 

}




