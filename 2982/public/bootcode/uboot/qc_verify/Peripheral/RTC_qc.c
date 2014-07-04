#include <qc_verify_common.h>


#define ADDR_DRTCSEC   (0xb8061900)
#define ADDR_DRTCMIN   (0xb8061904)
#define ADDR_DRTCHR    (0xb8061908)
#define ADDR_DRTCDATE1 (0xb806190c)
#define ADDR_DRTCDATE2 (0xb8061910)
#define ADDR_DALMMIN   (0xb8061914)
#define ADDR_DALMHR    (0xb8061918)
#define ADDR_DALMDATE1 (0xb806191c)
#define ADDR_DALMDATE2 (0xb8061920)
#define ADDR_DRTCSTOP  (0xb8061924)
#define ADDR_DRTCACR   (0xb8061928)
#define ADDR_DRTCEN    (0xb806192c)
#define ADDR_DRTCCR    (0xb8061930)

#define ADDR_ARTCSEC   (0xb8061700)
#define ADDR_ARTCMIN   (0xb8061704)
#define ADDR_ARTCHR    (0xb8061708)
#define ADDR_ARTCDATE1 (0xb806170c)
#define ADDR_ARTCDATE2 (0xb8061710)
#define ADDR_AALMMIN   (0xb8061714)
#define ADDR_AALMHR    (0xb8061718)
#define ADDR_AALMDATE1 (0xb806171c)
#define ADDR_AALMDATE2 (0xb8061720)
#define ADDR_ARTCSTOP  (0xb8061724)
#define ADDR_ARTCACR   (0xb8061728)
#define ADDR_ARTCEN    (0xb806172c)
#define ADDR_ARTCCR    (0xb8061730)



 typedef union _RTC_Time
 {
	UINT8  rtc_times[5];
	
 	struct
	{ 
	UINT8	rtc_sec;
	UINT8 	rtc_min;
	UINT8	rtc_hour;
	UINT8	rtc_date1;
	UINT8	rtc_date2;
 	};
}RTC_Time;

RTC_Time SetRTCTime(UINT8* input)
{
	UINT32 i;

    RTC_Time temp;
    for(i =0;i<5;i++)
    {
        temp.rtc_times[i]=input[i];
    }
	return temp;	
}

int Verifier_DRTC(void)
{
    printk("//DRTC Verifying\n");
    bool bResult_Fail = 0;

	RTC_Time set_times,get_times;
	UINT8 andbits[5]={0x7f,0x3f,0x1f,0xff,0x7f};//sec;min,hour,date1,date2
	UINT32 i;
	
	//RTC Init:	(diff from Magellan)
	rtd_maskl(ADDR_DRTCACR,GetMaskAnd(6,0),0x7);//RTCACR:  CO,CI to 0,CLKSEL to 1,BC to 3 :27MHz
    rtd_maskl(ADDR_DRTCSTOP,GetMaskAnd(3,1),0x7<<1);//RTCSTOP: VREF:3  27Mclk_en:1   only set this can RTC begin count and running.

    //---------check RTC Reset-------------------------------------------
	rtd_outl(ADDR_DRTCEN,0x0);//RTCEN:disable RCT
	rtd_maskl(ADDR_DRTCCR,GetMaskAnd(6,6),0x1<<6); //RTCCR:reset	

	for(i=0;i<5;i++)
	{	
		get_times.rtc_times[i] = dw(ADDR_DRTCSEC+i*4)&andbits[i];	//get current time
		bResult_Fail|= (get_times.rtc_times[i]!=0);		
	}

	//rtd_outl(ADDR_DRTCEN,0x5a);//RTCEN:enable RCT
	rtd_maskl(ADDR_DRTCCR,GetMaskAnd(6,6),0x0<<6); //RTCCR:end reset test

	if(bResult_Fail)
	{
		printk("RTC(RTCRST) reset failed!\n");
		printk("Get Current Time=>\n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);
		return bResult_Fail;
	}	

	//--------check RTC Set Time. and  timer can run---------------------
	//Set time
	UINT8 temp[5]={0x0,0x6,0x2,0x1,0x0};
	set_times = SetRTCTime(temp);
	for(i=0;i<5;i++)	
		ew(ADDR_DRTCSEC+i*4,set_times.rtc_times[i]);

	ew(ADDR_DRTCEN,0x5a);//enable RCT
	//printk("Enable RCT:0xb806172c:0x%x\n",dw(0xb806172c));
	//printk("Read RCT:0xb8061724:0x%x\n",dw(0xb8061724)); //see if is running

	for(i=0;i<5;i++)	
		printk("Read Time[%d]=0x%x;\n",i,dw(ADDR_DRTCSEC+i*4)&andbits[i]);
	
	//Delay 5s
	mdelay(5000);
	
	//Read back	
	for(i=0;i<5;i++)	
		get_times.rtc_times[i] = dw(ADDR_DRTCSEC+i*4)&andbits[i];

	//Compare: 1.Timer runs 5s;	 2.others should be same as set time.
	bResult_Fail|= !((get_times.rtc_sec>=set_times.rtc_sec+8)&&(get_times.rtc_sec<=set_times.rtc_sec+12));//Timer running 5s.
	if(bResult_Fail)
	{
		printk("RTC is not running correct!(should be 5s.)\n");
		printk("Get Current Time=> \n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);

		return bResult_Fail;
	}
	
	for(i=1;i<5;i++)
	{
		bResult_Fail|= (get_times.rtc_times[i]!=set_times.rtc_times[i]);
	}

	if(bResult_Fail)
	{
		printk("RTC set time failed!\n");
		printk("Get Current Time=> \n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);

		return bResult_Fail;
	}	
	
	//----------------check RTC ALM Flag-----------------------------------
	rtd_outl(ADDR_DRTCEN,0x0);//RTCEN:disable RCT
	//set ALM TIME
    ew(ADDR_DALMMIN,0x0);//write ALM minute
	ew(ADDR_DALMHR,0x0);//write  ALM hour
	ew(ADDR_DALMDATE1,0x2);//write  ALM Data LSB
	ew(ADDR_DALMDATE2,0x0);//write  ALM Data MSB
	ew(ADDR_DRTCCR,0xf8000000);//clear RTC interrupt
	bResult_Fail = ((dw(ADDR_DRTCCR)&0xf0000000)!=0);//read back to check.
	if(bResult_Fail)
	{
		printk("RTC INT Flag can not be cleared!\n");
		return bResult_Fail;
	}
	//enable INT
	ew(ADDR_DRTCCR,0xf800001f);//Enable RTC interrupt
	
    //set current Time: date:1,h:23,min:59,sec:59
	UINT8 temp1[5]={0x76,0x3b,0x17,0x1,0x0};
	set_times = SetRTCTime(temp1); 
	for(i=0;i<5;i++)	
		ew(ADDR_DRTCSEC+i*4,set_times.rtc_times[i]);
	
    ew(ADDR_DRTCEN,0x5a);//enable RCT
    
	//Delay 1s
	mdelay(1200);

	//check INT falgs
	UINT8 Flag_INT = (dw(ADDR_DRTCCR)&0xf0000000)>>28;
	bResult_Fail = (Flag_INT!=0xf);
	if(bResult_Fail)
	{
		printk("RTC INT Flag did not all raised!falg status:0x%d(alm,date,hour,min)!\n",Flag_INT);
		return bResult_Fail;
	}

	return bResult_Fail;	
}




int Verifier_ARTC(void)
{
    printk("//ARTC Verifying\n");
    bool bResult_Fail = 0;

	RTC_Time set_times,get_times;
	UINT8 andbits[5]={0x7f,0x3f,0x1f,0xff,0x7f};//sec;min,hour,date1,date2
	UINT32 i;
	
	//RTC Init:	(diff from Magellan)
	rtd_maskl(ADDR_ARTCACR,GetMaskAnd(6,0),0x3);//RTCACR:  CO,CI to 0,CLKSEL to 0,BC to 3 :32.768KHz
    rtd_maskl(ADDR_ARTCSTOP,GetMaskAnd(3,1),0x3<<1);//RTCSTOP: VREF:3  27Mclk_en:0   only set this can RTC begin count and running.

    //---------check RTC Reset-------------------------------------------
	rtd_outl(ADDR_ARTCEN,0x0);//RTCEN:disable RCT
	rtd_maskl(ADDR_ARTCCR,GetMaskAnd(6,6),0x1<<6); //RTCCR:reset	

	for(i=0;i<5;i++)
	{	
		get_times.rtc_times[i] = dw(ADDR_ARTCSEC+i*4)&andbits[i];	//get current time
		bResult_Fail|= (get_times.rtc_times[i]!=0);		
	}

	//rtd_outl(ADDR_ARTCEN,0x5a);//RTCEN:enable RCT
	rtd_maskl(ADDR_ARTCCR,GetMaskAnd(6,6),0x0<<6); //RTCCR:end reset test

	if(bResult_Fail)
	{
		printk("RTC(RTCRST) reset failed!\n");
		printk("Get Current Time=>\n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);
		return bResult_Fail;
	}	

	//--------check RTC Set Time. and  timer can run---------------------
	//Set time
	UINT8 temp[5]={0x0,0x6,0x2,0x1,0x0};
	set_times = SetRTCTime(temp);
	for(i=0;i<5;i++)	
		ew(ADDR_ARTCSEC+i*4,set_times.rtc_times[i]);

	ew(ADDR_ARTCEN,0x5a);//enable RCT
	//printk("Enable RCT:0xb806172c:0x%x\n",dw(0xb806172c));
	//printk("Read RCT:0xb8061724:0x%x\n",dw(0xb8061724)); //see if is running

	for(i=0;i<5;i++)	
		printk("Read Time[%d]=0x%x;\n",i,dw(ADDR_ARTCSEC+i*4)&andbits[i]);
	
	//Delay 5s
	mdelay(5000);
	
	//Read back	
	for(i=0;i<5;i++)	
		get_times.rtc_times[i] = dw(ADDR_ARTCSEC+i*4)&andbits[i];

	//Compare: 1.Timer runs 5s;	 2.others should be same as set time.
	bResult_Fail|= !((get_times.rtc_sec>=set_times.rtc_sec+8)&&(get_times.rtc_sec<=set_times.rtc_sec+12));//Timer running 5s.
	if(bResult_Fail)
	{
		printk("RTC is not running correct!(should be 5s.)\n");
		printk("Get Current Time=> \n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);

		return bResult_Fail;
	}
	
	for(i=1;i<5;i++)
	{
		bResult_Fail|= (get_times.rtc_times[i]!=set_times.rtc_times[i]);
	}

	if(bResult_Fail)
	{
		printk("RTC set time failed!\n");
		printk("Get Current Time=> \n  second:0x%x;minute:0x%x;hour:0x%x;Data1:0x%x;Data2:0x%x\n", get_times.rtc_sec,get_times.rtc_min,get_times.rtc_hour,get_times.rtc_date1,get_times.rtc_date2);

		return bResult_Fail;
	}	
	
	//----------------check RTC ALM Flag-----------------------------------
	rtd_outl(ADDR_ARTCEN,0x0);//RTCEN:disable RCT
	//set ALM TIME
    ew(ADDR_AALMMIN,0x0);//write ALM minute
	ew(ADDR_AALMHR,0x0);//write  ALM hour
	ew(ADDR_AALMDATE1,0x2);//write  ALM Data LSB
	ew(ADDR_AALMDATE2,0x0);//write  ALM Data MSB
	ew(ADDR_ARTCCR,0xf8000000);//clear RTC interrupt
	bResult_Fail = ((dw(ADDR_ARTCCR)&0xf0000000)!=0);//read back to check.
	if(bResult_Fail)
	{
		printk("RTC INT Flag can not be cleared!\n");
		return bResult_Fail;
	}
	//enable INT
	ew(ADDR_ARTCCR,0xf800001f);//Enable RTC interrupt
	
    //set current Time: date:1,h:23,min:59,sec:59
	UINT8 temp1[5]={0x76,0x3b,0x17,0x1,0x0};
	set_times = SetRTCTime(temp1); 
	for(i=0;i<5;i++)	
		ew(ADDR_ARTCSEC+i*4,set_times.rtc_times[i]);
	
    ew(ADDR_ARTCEN,0x5a);//enable RCT
    
	//Delay 1s
	mdelay(1200);

	//check INT falgs
	UINT8 Flag_INT = (dw(ADDR_ARTCCR)&0xf0000000)>>28;
	bResult_Fail = (Flag_INT!=0xf);
	if(bResult_Fail)
	{
		printk("RTC INT Flag did not all raised!falg status:0x%d(alm,date,hour,min)!\n",Flag_INT);
		return bResult_Fail;
	}

	return bResult_Fail;	
}
