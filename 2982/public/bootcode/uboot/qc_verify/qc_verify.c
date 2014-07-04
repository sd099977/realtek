#include <qc_verify.h>

/*

	QC VERIFY AUTO RUN FUNCTION

*/
QC_IP_VERIFY_ENTRY_T  qc_ip_verify_run_list[] = {	
/*#####	SCPU :	qc_verify/SCPU #####*/
/*#####	BIST :	qc_verify/BIST #####*/
#if CONFIG_QC_BIST
	{"BIST_QC",QC_Verifier_BIST},		
#endif

/*#####	BISR :	qc_verify/BISR #####*/
#if CONFIG_QC_BISR
	{"BISR_QC",QC_Verifier_BISR},		
#endif

#if CONFIG_QC_SCPU
	{"SCPU_QC",QC_Verifier_SCPU},		
#endif

/*#####	GPU :	qc_verify/GPU #####*/
#if CONFIG_QC_GPU
	{"GPU_QC",QC_Verifier_GPU},		
#endif

/*#####	VE :	qc_verify/VE #####*/
#if CONFIG_QC_VE
	{"VE_QC",QC_Verifier_VE},		
#endif

#if CONFIG_QC_8051
	{"8051_QC",QC_Verifier_8051},		
#endif

/*#####	AUDIO :	qc_verify/Audio #####*/
#if CONFIG_QC_AUDIO
	{"AUDIO_QC",QC_Verifier_AUDIO},		
#endif

/*#####	HDMI_TX	:	qc_verify/HDMI_TX #####*/
#if CONFIG_QC_HDMI_TX
	{"HDMI_TX_QC",QC_Verifier_HDMI_TX},		
#endif

/*#####	HDMI_RX	:	qc_verify/HDMI_RX #####*/
#if CONFIG_QC_HDMI_RX
	{"HDMI_RX_QC",QC_Verifier_HDMI_RX},		
#endif

/*#####	IFD :	qc_verify/IFD #####*/
#if CONFIG_QC_IFD
	{"IFD_QC",QC_Verifier_IFD},		
#endif

/*#####	VDC :	qc_verify/VDC #####*/
#if CONFIG_QC_VDC
	{"VDC_QC",QC_Verifier_VDC},		
#endif

/*#####	CEC :	qc_verify/CEC #####*/
#if CONFIG_QC_CEC
	{"CEC_QC",QC_Verifier_CEC},		
#endif

/*#####	USB :	qc_verify/USB #####*/
#if CONFIG_QC_USB
	{"USB_QC",QC_Verifier_USB},		
#endif

/*#####	VIP :	qc_verify/VIP #####*/
#if CONFIG_QC_VIP
	{"VIP_QC",QC_Verifier_VIP},		
#endif

/*#####	TVE_TV :	qc_verify/TVE_TV #####*/
#if CONFIG_QC_TVE_TV
	{"TVE_TV_QC",QC_Verifier_TVE_TV},		
#endif

/*#####	TVE_BOX :	qc_verify/TVE_BOX #####*/
#if CONFIG_QC_TVE_BOX
	{"TVE_BOX_QC",QC_Verifier_TVE_BOX},		
#endif

/*#####	I3DDMA :	qc_verify/I3DDMA #####*/
#if CONFIG_QC_I3DDMA
	{"I3DDMA_QC",QC_Verifier_I3DDMA},		
#endif	

/*#####	DTV_Demod :	qc_verify/DTV_Demod #####*/
#if CONFIG_QC_DTV_Demod
	{"DTV_Demod_QC",QC_Verifier_DTV_Demod},		
#endif	

/*#####	EMMC :	qc_verify/EMMC #####*/
#if CONFIG_QC_EMMC
	{"EMMC_QC",QC_Verifier_EMMC},		
#endif	

/*#####	CARDREADER :	qc_verify/CardReader #####*/
#if CONFIG_QC_CARDREADER
	{"CardReader_QC",QC_Verifier_CardReader},		
#endif	

/*#####	SPI :	qc_verify/SPI_Flash #####*/
#if CONFIG_QC_SPI
	{"SPI_QC",QC_Verifier_SPI},		
#endif	

/*#####	SPI_NAND :	qc_verify/SPI_NAND #####*/
#if CONFIG_QC_SPI_NAND
	{"SPI_NAND_QC",QC_Verifier_SPI_Nand},		
#endif

/*#####	NAND	:	qc_verify/NAND #####*/
#if CONFIG_QC_NAND
	{"NAND_QC",QC_Verifier_NAND},		
#endif	

/*#####	EPI :	qc_verify/EPI #####*/
#if CONFIG_QC_EPI
	{"EPI_QC",QC_Verifier_EPI},		
#endif

/*#####	ETN :	qc_verify/GETN #####*/
#if CONFIG_QC_GETN
	{"GETN_QC",QC_Verifier_GETN},
#endif

/*#####	MHL :	qc_verify/MHL #####*/
#if CONFIG_QC_MHL
	{"MHL_QC",QC_Verifier_MHL},		
#endif

/*#####	VBI :	qc_verify/VBI #####*/
#if CONFIG_QC_VBI
	{"VBI_QC",QC_Verifier_VBI},		
#endif

/*#####	DDR	:	qc_verify/DDR #####*/
#if CONFIG_QC_DDR
	{"DDR_QC",QC_Verifier_DDR},	
#endif	

/*#####	Standby :	qc_verify/Standby #####*/
#if CONFIG_QC_STANDBY
	{"I_DOMAIN_QC",QC_Verifier_Standby},		
#endif

/*#####	PERIPHERAL	:	qc_verify/Peripheral #####*/
#if CONFIG_QC_PERIPHERAL
	{"PERIPHERAL_QC",QC_Verifier_PERIPHERAL},		
#endif

/*#####	MD_DOMAIN :	qc_verify/MD_Domain #####*/
#if CONFIG_QC_MD_DOMAIN
	{"MD_DOMAIN_QC",QC_Verifier_MD_Domain},		
#endif

/*#####	I_DOMAIN :	qc_verify/I_Domain #####*/
#if CONFIG_QC_I_DOMAIN
	{"I_DOMAIN_QC",QC_Verifier_I_Domain},		
#endif

/*#####	YPPADC :	qc_verify/YPPADC #####*/
#if CONFIG_QC_YPPADC
	{"YPPADC_QC",QC_Verifier_YPPADC},		
#endif



/*#####	TVE_CGMS_TEST :	qc_verify/TVE_TEST #####*/
#if CONFIG_QC_TVE_CGMS_YPP_OUTPUT_TEST
	{"TVE_CGMS_YPP_OUTPUT_TEST",QC_Verifier_TVE_TEST_CGMS},		
#endif

	{ "", NULL}
};

/* Timer Reset */
void timer_7_reset(void)
{
	rtd_outl(TC7CR, 0x00000000);
	rtd_outl(TC7TVR, 0xffffffff);   //xz-159s;
	rtd_outl(TC7ICR, 0x80000000);   //enable
	rtd_outl(TC7CR, 0x80000000);  //timer7 enable	
}
//extern void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock);

/* U-boot qc command entry */
void qc_verify(int option)
{
	#define	CONSOLE_MODE_QC_PROMPT	"EnterNumber :"	
	#define	QCINFO_CMD_BUFFER_SIZE	128
	#define	ESTIME 1

	INT32	argc = 0;
  	INT8	**argv = NULL; 

	int	total, fail, pass,i;
	int	tNum;
	char tResl[64];
	unsigned int	rst=0;
	unsigned int	totcnt = 0;
	UINT8	abyCommandBuffer[QCINFO_CMD_BUFFER_SIZE];
	UINT32	loops;
	UINT32	item;	
	UINT32	tMs;	
	UINT32	FailCnt = 0;		

	//LED light on, ST_GPIO4_JS86_1_N5, sw95_1 on
	/*rtd_maskl(0xB8060230,0xffffff0f,0x000000f0);//Pinshare
	rtd_maskl(0xb8061100,0xfffffef,0x00000010);//GPO
	rtd_maskl(0xb8061108,0xfffffef,0x00000000);//low_light on

	//BL enable, ST_GPIO6_JS67_2_R6, sw77_3 on
	rtd_maskl(0xB8060234,0xff0fffff,0x00f00000);//Pinshare
	rtd_maskl(0xb8061100,0xffffffbf,0x00000040);//GPO
	rtd_maskl(0xb8061108,0xffffffbf,0x00000000);//low */
	
	total = 0;
	fail   = 0;
	pass = 0;
	loops = 0;

	printk(" == QC CODE TEST LIST ==\n");
	while(qc_ip_verify_run_list[total].entry_function != 0)
	{
		printk("  %d).%s\n",total,qc_ip_verify_run_list[total].entry_name);
		total++;
	}
	printk("  %d).ALL (not support now)\n",total);
	total++;
	//printk("  %d).ALL LOOPS [Shift+A to break loops]\n",total);
	printk("  %d).ALL LOOPS (not support now)\n",total);
	total++;
	printk("  %d).ESC\n",total);	
	printk("\r\n");	
	
	item = total -2;
	while(TRUE)
	{
		#if CONFIG_QC_VERIFY_ATO
		
		if (GETCHAR_ESC)
			break;
	
		tNum = (total-2);
			
		if(option==1)
		{
			printk("%s", CONSOLE_MODE_QC_PROMPT);		
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
			tNum = strtoul((const INT8 *) (argv[0]), (INT8 **) NULL, 10);			
		}
		#else	
		if(option==2)
		{	
			tNum = (total-2);	//for once auto run
		}	
		else
		{	
			printk("%s", CONSOLE_MODE_QC_PROMPT);							
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
			tNum = strtoul((const INT8 *) (argv[0]), (INT8 **) NULL, 10);
		}
		#endif					
	
		if (tNum==total) 
		{	//ESC
			break;
		}
		else if (tNum==(total-2))
		{			
			for (i=0;i<(item);i++)
			{				
				if(GETCHAR_ESC)
					break;
				
				#if defined(ESTIME)
				timer_7_reset();
				#endif

				//reset modules
				//enable_clock(SYS_SRST1, 0x00FFFFFF, SYS_CLKEN1, 0x00FFFFFF);
				//enable_clock(SYS_SRST2, 0x0E000800, SYS_CLKEN2, 0x0E000800);
				
				if (qc_ip_verify_run_list[i].entry_function()) 
				{
					fail++;
					tResl[i] = 'F';
					FailCnt++;

					#if defined(ESTIME)
					tMs = rtd_inl(TC7CVR); //Timer7
					tMs = tMs/27000;
					printk("  %d).%s IP test Fail time=%d ms\n\n", i,qc_ip_verify_run_list[i].entry_name,tMs);
					#endif

					#ifdef CONFIG_EQC
					//LED light off, GPIO141
					rtd_maskl(0xb801b12c,0xffffdfff,0x00000000); //GPO_Set low if failed						
					#endif	
				}
				else
				{
					pass++;
					tResl[i] = 'S';
				
					#if defined(ESTIME)
					tMs = rtd_inl(TC7CVR);
					tMs = tMs/27000;
					printk("  %d).%s IP test Pass time=%d ms\n\n",i,qc_ip_verify_run_list[i].entry_name,tMs);
					#endif				
				}					
				printk("========== tot err count ======================>> %d \n",FailCnt);									
			}
			//local_uart1_enable();					
					
			//Succ IP
			#if CONFIG_FT
			rtd_maskl(0xb801b11c,0xfff1ffff,0x00000000);//GPO19~17[19:17]=0, version 0		
			rtd_maskl(0xb8061108,0xfffffdff,0x00000200);//ST_GPO9[9]=0x1 end
			//  pass 
			if(fail==0)
			{
				rtd_maskl(0xb801b11c,0xfffeffff,0x00000000);//GPO16[16]=0x0 is pass
			}
			else// fail
			{
				rtd_maskl(0xb801b11c,0xfffeffff,0x00010000);//GPO16[16]=0x1 is fail
			}	
			#endif
			
			//Fail IP 
			printk("\r\n *** FAIL IP ***\n"); 
			for (i=0;i<(item);i++)
			{
				if (FailCnt==0)
				{
					printk("\r\n"); 
					printk("\n+++++++++++++++++\n"); 
					printk("+++ No Fail IP ++"); 
					printk("\n+++++++++++++++++\n"); 
					printk("\r\n"); 
					printk("\r\n"); 
					break;
				}
									
				if (tResl[i]=='F') 
					printk("  %d).%s\n\n",i ,qc_ip_verify_run_list[i].entry_name);	
			}												

			#if CONFIG_QC_ONCE_ALL			
				break;
			#endif
		}
		else if (tNum==(total-1)) 
		{	//ALL LOOPS			
			//printk("ALL LOOPS =>%d\n",tNum);
			loops = 0;
			fail = 0;
			while(TRUE)
			{
				if (GETCHAR_ESC)
				break;

				for (i=0;i<(item);i++)
				{
					//local_uart1_disable();
					if (qc_ip_verify_run_list[i].entry_function()) 
					{
						//local_uart1_enable();	
						fail++;
						tResl[i] = 'F';
					}
					else
					{
						//local_uart1_enable();	
						pass++;
						tResl[i] = 'S';
					}
				}						
					
				loops++;
				printk("\r\n =========== QC VERIFY LOOPS [%d] ============ \n",loops);
				//Succ IP	
				printk("\r\n *** SUCCESS IP ***\n"); 
				for (i=0;i<(item);i++)
				{
					if (tResl[i]=='S') 
						printk("  %d).%s\n",i, qc_ip_verify_run_list[i].entry_name);	
				}
					
				//Fail IP 
				printk("\r\n *** FAIL IP ***\n"); 
				for (i=0;i<(item);i++)
				{
					if (tResl[i]=='F') 
						printk("  %d).%s\n",i ,qc_ip_verify_run_list[i].entry_name);		
				}
					
				if (fail>0)
				break;
			}
		}	 	
		else
		{		
			printk("\r\n *** RESULT ***\n");		

			//reset modules
			//enable_clock(SYS_SRST1, 0x00FFFFFF, SYS_CLKEN1, 0x00FFFFFF);
			//enable_clock(SYS_SRST2, 0x0E000800, SYS_CLKEN2, 0x0E000800);
			
			#if defined(ESTIME)
			timer_7_reset();
			#endif				

			if (qc_ip_verify_run_list[tNum].entry_function()) 
			{	
				#if defined(ESTIME)
				tMs = rtd_inl(TC7CVR);
				tMs = tMs/27000;
				printk("  %d).%s IP test Fail time=%d ms\n\n", tNum,qc_ip_verify_run_list[tNum].entry_name,tMs);
				#else
				printk("  %d).%s IP test Fail\n\n", tNum,qc_ip_verify_run_list[tNum].entry_name);
				#endif			
			}
			else
			{			
				#if defined(ESTIME)
				tMs = rtd_inl(TC7CVR);
				tMs = tMs/27000;
				printk("  %d).%s IP test Pass time=%d ms\n\n",tNum,qc_ip_verify_run_list[tNum].entry_name,tMs);
				#else
				printk("  %d).%s IP test Pass\n\n",tNum,qc_ip_verify_run_list[tNum].entry_name);
				#endif
			}	
		}		
		
		#if CONFIG_QC_VERIFY_ATO

		if (fail>0)
			break;
		
		if (GETCHAR_ESC)	/* stop loop */
			break;

		if(option==2)
		{
			totcnt = rtd_inl(0xb8060118); //SCPU Context register value (NMI exception)
			totcnt++;
			rtd_outl(0xb8060118,	totcnt);	
			
			//watch dog reset
			rtd_outl(TCWOV,	0x080BEFC0); //overflow time: 5s
			rtd_outl(TCWCR,	0x00000f00); //watch enable
  		
			printk("WatchDog Reset CNT = %x\n",totcnt);
  		
			while(1)
			{
				if((rst%32768)==0)
					rst++;
			}
		}	
		#endif	
	}
}
