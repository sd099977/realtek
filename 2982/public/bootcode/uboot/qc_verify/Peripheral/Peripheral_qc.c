#include <qc_verify_common.h>

#define EN_Verify_GPIO
#define EN_Verify_LSADC
//#if CONFIG_BGA
//   #define EN_Verify_Uart
//#endif
#define EN_Verify_Timer	
#define EN_Verify_RTC	


int QC_Verifier_PERIPHERAL(void)
{
  	UINT32    debug_result=0;
  	UINT32    fail_result = 0;
	UINT32	temp;
	UINT32	i;

	// GPIO verify
#ifdef EN_Verify_GPIO
	debug_result =Verifier_GPIO();
	fail_result |= debug_result;
	if (debug_result)
		printk("GPIO failed\n");
	else
		printk("GPIO pass\n");
#endif



	// LSADC verify
#ifdef EN_Verify_LSADC
	debug_result =Verifier_LSADC();
	fail_result |= debug_result;
	if (debug_result)
		printk("LSADC failed\n");
	else
		printk("LSADC pass\n");
#endif


/*
	// I2C_DDC verify	
	debug_result =Verifier_I2C_DDC();
	fail_result |= debug_result;
	if (debug_result)
		printk("I2C_DDC failed\n");
	else
		printk("I2C_DDC pass\n");	
*/

/*
	// Irda verify	
	debug_result =Verifier_Irda();
	fail_result |= debug_result;
	if (debug_result)
		printk("Irda failed\n");
	else
		printk("Irda pass\n");
*/

#ifdef EN_Verify_Uart
	debug_result = Verify_Uart();	//no enough uart & eqc_path no ready
	fail_result |= debug_result;
	if (debug_result)
		printk("xxxxxxxxxxxxxxxxxxx Uart  failed!xxxxxxxxxxxxxxxxxxx \n");
	else
		printk("=============== Uart  pass! =============== \n");
#endif

	// Timer verify	
#ifdef EN_Verify_Timer
	debug_result = Verify_Timer(2);
	fail_result |= debug_result;
	if (debug_result)
		printk("xxxxxxxxxxxxxxxxxxx Timer failed!xxxxxxxxxxxxxxxxxxx\n");
	else
		printk("=============== Timer pass! ===============\n");
#endif

     // RTC verify
#ifdef EN_Verify_RTC
	debug_result =Verifier_DRTC();
    #if CONFIG_BOX
	    debug_result |=Verifier_ARTC();
	#endif

	fail_result |= debug_result;
	if (debug_result)
		printk("RTC failed\n");
	else
		printk("RTC pass\n");
#endif


	//conclude results
	if(fail_result)   	 //  fail  return 1 ;   pass return 0 ;  
		return 1;
	else
		return 0;

}
