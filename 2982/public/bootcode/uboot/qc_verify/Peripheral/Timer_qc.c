#include <qc_verify_common.h>
//#define DEBUGMODE

int Verify_Timer_Unit(UINT8 NSec, UINT8 nTimerSta, UINT8 nTimerEnd)
{

	//Timer0-7 index
	UINT8 i = 0;

    	//27000000*5s ->0x80befc0; 1s->0x19bfcc0; 2s->0x337f980; 3s->0x4d3f640
    	UINT32 target_val = 27000000*NSec;

	//*****MSK-interrupt flag:13:6 =>0x3fc0*****
	UINT8 lsb = 6 + nTimerSta;
	UINT8 msb = lsb + nTimerEnd-nTimerSta;
	UINT32 ref_int_val = GetFieldVal(msb, lsb);	 
	UINT32 get_int_val;
	UINT32 get_val = 0;

	UINT32 addr_UMISR_INT = 0xb801b008;
	UINT32 addr_ISR_INT = 0xb801b00c;
	
	UINT32 addr_timer_ctrl = 0xb801b640+ 0x4*nTimerSta;			// 0xb801b640 ~ 0xb801b65c
	UINT32 addr_timer_int_ctrl = 0xb801b660+ 0x4*nTimerSta;		//0xb801b660 ~ 0xb801b67c
	UINT32 addr_timer_target_val = 0xb801B600+ 0x4*nTimerSta;	//0xb801B600 ~ 0xb801B61c
	UINT32 addr_timer_current_val = 0xb801b620+ 0x4*nTimerSta;	//0xb801b620 ~ 0xb801b63c
	UINT32 addr_timer_systime = 0xb801b63c;
	UINT32 addr;

	printk("-----  Start Verify %d~%d of Timer0~7, %ds int = 0x%x-----\n", nTimerSta, nTimerEnd,  NSec, ref_int_val);

	UINT32 t1,t2,tc; 
    	//sys_get_time_freq(&tc);				
    	tc = 27000000;
    	printk("=>Pass get_tbclk: %d\n", tc);

	//disable timer
	addr = addr_timer_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_maskl(addr,0x7fffffff,0);	//Timer/Counter Control Register: disable timer
		addr +=0x4;
	}

	//disable timer interrupt
	addr = addr_timer_int_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_outl(addr,0x00000000);
		addr +=0x4;
	}

	//clear timer MSK-interrupt flag
	rtd_inl(addr_ISR_INT);
	rtd_outl(addr_ISR_INT,0xfffffffe);  	//write 0xfffffffe to clear; write 0x81£¬will raise up 0x80(time 0)

	//set timer target value = 27000000*5s ->0x80befc0; 1s->0x19bfcc0; 2s->0x337f980; 3s->0x4d3f640
	addr = addr_timer_target_val;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_outl(addr,target_val);		//set timer0 target value = 27000000*Ns, must before "clear timer UMSKISR flag"
		addr +=0x4;
	}

	//pre-check timer current value before start timer
	addr = addr_timer_current_val;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_inl(addr);		//*****timer current value*****
		addr +=0x4;
	}

	//rtd_inl(addr_ISR_INT);	//*****pre-check MSK-interrupt flag*****	    	
	get_int_val = rtd_inl(addr_ISR_INT) & ref_int_val;   
    	printk("Timer INT Flag:0x%x \n", get_int_val);
	if(get_int_val != 0)
	{
		printk("Timer INT Flag have't be cleared => 0x%x!\n", get_int_val);
		return 1;
	}

	//enable timer interrupt
	addr = addr_timer_int_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_outl(addr,0x80000000);
		addr +=0x4;
	}

	//set timer mode and enable
	addr = addr_timer_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_outl(addr,0xc0000000);
		addr +=0x4;
	}

	//---------wait to check int flag-------------

    t1 = rtd_inl(addr_timer_systime);
    	printk("=>Pass get_ticks: t1 = %d\n", t1);

	int cnt = 0;	
	do
	{
		get_int_val =  rtd_inl(addr_ISR_INT)  & ref_int_val;		
		if(get_int_val == ref_int_val)
        	{
				t2 = rtd_inl(addr_timer_systime);
    			printk("=>Pass get_ticks: t2 = %d\n", t2);
			break;
        	}
		
		//printk("%dth: get_int_val =0x%x,  ref_int_val=0x%x \n", cnt, get_int_val, ref_int_val);
        	udelay(100000);			//ms	
        	cnt++;
			
	}while(cnt<30);
	
	//---------------------------------------

	//disable timer
	addr = addr_timer_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_maskl(addr,0x7fffffff,0);		//Timer/Counter Control Register: disable timer
		addr +=0x4;
	}

	//disable timer interrupt
	addr = addr_timer_int_ctrl;
	for(i =nTimerSta; i<nTimerEnd+1; i++)
	{
		rtd_outl(addr,0x00000000);
		addr +=0x4;
	}


	//--------------------check result--------------------------
	int T0, Toffset, Ttolerance;
	Ttolerance = 1;
	T0 = (t2- t1)/tc;
	Toffset = T0-NSec; 
	printk("Timer INT Flag raised in %d secs,  offset %d  to %d secs \n", T0, Toffset, NSec);
	if(Toffset > Ttolerance || Toffset<(0-Ttolerance))
	{
	    printk("Timer INT Flag failed to raised in limit-time! \n");
	    return 1;
	}
		


	printk("Timer Verify success! \n");
	return 0;
	
}


int Verify_Timer(UINT8 NSec)
{
#ifdef DEBUGMODE
//Check which time is running
    printk("Check which timer is Runing:\n");
    int data,i;
	for(i =0;i<8;i++)
		{
		  data = rtd_inl(0xb801b620+4*i);
	      printk("Current time of Timer:%d =>0x%x\n",i,data);

		  udelay(1000);
		  
		  data = rtd_inl(0xb801b620+4*i);
	      printk("Current time of Timer:%d =>0x%x\n",i,data);

		}
#endif


	int  debug_result=0;
	UINT8 nTimerSta , nTimerEnd;
	
	nTimerSta = 0;
	nTimerEnd = 1;
	debug_result  =  Verify_Timer_Unit( NSec,nTimerSta, nTimerEnd);
	if(debug_result)
	{
		printk("Verify_Timer_Unit Fail: %d ~ %d", nTimerSta, nTimerEnd);
		return 1;
	}

	nTimerSta = 3;
	nTimerEnd = 6;	
	debug_result  =  Verify_Timer_Unit( NSec,nTimerSta, nTimerEnd);
	if(debug_result)
	{
		printk("Verify_Timer_Unit Fail: %d ~ %d", nTimerSta, nTimerEnd);
		return 1;
	}



	printk("All Timer Verify success! \n");
	return 0;
}

