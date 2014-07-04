#include <qc_verify_common.h>

extern char __arm_advsimd_start[]; 
extern char __arm_advsimd_end[]; 
extern char __arm_vfp_start[]; 
extern char __arm_vfp_end[]; 

int QC_Verifier_SCPU(void)
{
	unsigned int entry = 0x0;
	int (*callbk_func)(void);
	unsigned char is_failed = 0;
	int ret = 0;

	// ca7_advsimd_functional test 
	printf("ARM SIMD test......");
	invalidate_icache_all();
	callbk_func = (void *)entry;
	memcpy((void *)entry, (void *)__arm_advsimd_start, __arm_advsimd_end - __arm_advsimd_start);
	ret = callbk_func();	// if it failed, return -1
	if (!ret)
		printf("PASS\n");
	else {
		printf("FAILED\n");
		is_failed = 1;
	}

	// ca7_vfp_functional test
	printf("ARM VFP test......");
   invalidate_icache_all();
   callbk_func = (void *)entry;
   memcpy((void *)entry, (void *)__arm_vfp_start, __arm_vfp_end - __arm_vfp_start);
   ret = callbk_func(); // if it failed, return -1
   if (!ret)
      printf("PASS\n");
   else {
      printf("FAILED\n");
		is_failed = 1;
	}

	if (is_failed)
		return FAILED;
	else
		return SUCCESS;
} 
