#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/stddef.h>

#include <common.h>
#include <parse_h.h>
#include <asm/arch/bootparam.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <factorylib.h>

bootparam_t bootparam;

#define DEBUG(msg,arg...)   do { printf("[%s %3d]:", __FILE__, __LINE__); printf(msg,##arg); } while(0)
//#define DEBUG(msg,arg...)

#define BOOT_PARAM_FILE_NAME	FACTORY_HEADER_FILE_NAME"bin_panel/000BootParam.h"
#define BOOT_PART_FILE_NAME		FACTORY_HEADER_FILE_NAME"layout.txt"

extern int boot_power_on_mode;
extern uchar boot_ac_on;
extern uchar boot_music_enable;
extern uchar boot_logo_enable;
extern uint custom_video1_leng;
extern uint custom_video2_leng;
extern uint custom_audio1_leng;
extern uint custom_audio2_leng;
extern int prev_power_on_status;
extern uint  custom_audio1_length ;
extern uint  custom_video1_length ;
extern uint  custom_audio2_length ;
extern uint  custom_video2_length ;

extern uint boot_part;

/************************************************************************
**
** get boot info in factory area of flash
**
*************************************************************************/
void get_bootparam(void)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	printf("%s:\n", __FUNCTION__);

//	display_evaluate_time("get_bootparam-0");

	memset(&bootparam, 0, sizeof(bootparam));

	if (factory_read(BOOT_PARAM_FILE_NAME, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", BOOT_PARAM_FILE_NAME);
		bootparam.prev_power_state = POWER_ON;
		bootparam.boot_music_enable = 0;
		bootparam.boot_logo_enable = 0;
		bootparam.backlight_value = 50;
		bootparam.local_upgrade_en = 0;
	}
	else {
		printf("------------%s found\n", BOOT_PARAM_FILE_NAME);

		if (parse_h("BOOT_POWER_ON_MODE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.prev_power_state = retVal;
			printf("BOOT_POWER_ON_MODE=%d\n", retVal);
                        EXECUTE_CUSTOMIZE_FUNC(0);
		}
		else {
			bootparam.prev_power_state = POWER_ON;
			DEBUG("can't find power state\n");
		}

	    if (parse_h("BOOT_LOGO_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.boot_logo_enable = retVal;
			printf("BOOT_LOGO_ENABLE=%d\n", retVal);
		}
		else {
			bootparam.boot_logo_enable = 0;
			DEBUG("can't find boot_logo_enable\n");
		}

	    if (parse_h("CUSTOM_VIDEO1_LENG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.custom_video1_leng = retVal;
			printf("CUSTOM_VIDEO1_LENG=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_video1_leng\n");
		}

	    if (parse_h("CUSTOM_VIDEO2_LENG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.custom_video2_leng = retVal;
			printf("CUSTOM_VIDEO2_LENG=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_video2_leng\n");
		}

		if (parse_h("BOOT_MUSIC_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.boot_music_enable = retVal;
			printf("BOOT_MUSIC_ENABLE=%d\n", retVal);
		}
		else {
			bootparam.boot_music_enable = 0;
			DEBUG("can't find music enable state\n");
		}

		if (parse_h("CUSTOM_AUDIO1_LENG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.custom_audio1_leng = retVal;
			printf("CUSTOM_AUDIO1_LENG=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_audio1_leng\n");
		}

		if (parse_h("CUSTOM_AUDIO2_LENG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.custom_audio2_leng = retVal;
			printf("CUSTOM_AUDIO2_LENG=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_audio2_leng\n");
		}

		if (parse_h("LOCAL_UPGRADE_EN", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.local_upgrade_en = retVal;
			printf("LOCAL_UPGRADE_EN=%d\n", retVal);
		}
		else {
			bootparam.local_upgrade_en = 0;
			DEBUG("can't find local_upgrade_en\n");
		}

#ifdef ENABLE_BOOTUP_POLICY
		//0:bootup whatever AC on/off; 1:do not bootup whatever AC on/off; 2:bootup decide by previous power state
		if (parse_h("BOOTUP_POLICY", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.bootup_policy = retVal;
			printf("BOOTUP_POLICY=%d\n", retVal);
		}
		else {
			bootparam.bootup_policy = 2; //auto by prev_status
			DEBUG("can't find bootup_policy\n");
		}
#endif
	}

	// RTK config don't care prev_power_state and always power on
	boot_power_on_mode = POWER_ON;
	prev_power_on_status = bootparam.prev_power_state;

#if defined(CONFIG_BOOTUP_BY_PREV_POWER_STATUS) || defined(ENABLE_BOOTUP_POLICY)
	if(bootparam.prev_power_state == 0 && boot_ac_on)
		boot_power_on_mode = POWER_OFF;
#endif

#ifdef ENABLE_BOOTUP_POLICY
	printf("bootup_policy=%d\n", bootparam.bootup_policy);
	if(bootparam.bootup_policy != 2)	//0: always powerOff, 1: always powerOn, 2:auto by prev_status
		boot_power_on_mode = bootparam.bootup_policy;
#endif

#if !defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) && !defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
	if (GET_IC_VERSION() == VERSION_A)		//bcoz ver.A ac_on detect has bug. fix always enter standby mode
		boot_power_on_mode = POWER_ON;
#endif

	printf("boot_power_on_mode=%d\n", boot_power_on_mode);

#if defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) || defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
        #ifndef CONFIG_CUSTOMIZE_FUNC_REGISTER
        printf("XXXXXX boot_power_on_mode = %d\n", boot_power_on_mode);
        if(boot_power_on_mode != POWER_OFF)
                tv005_update_led();
        #endif
#endif

	boot_music_enable = bootparam.boot_music_enable;
	boot_logo_enable = bootparam.boot_logo_enable;

	custom_video1_length = bootparam.custom_video1_leng;
	custom_video2_length = bootparam.custom_video2_leng;
	custom_audio1_length = bootparam.custom_audio1_leng;
	custom_audio2_length = bootparam.custom_audio2_leng;

	if(bootparam.local_upgrade_en)
		boot_mode = BOOT_RESCUE_MODE;

//	display_evaluate_time("get_bootparam-1");
}

#define DBG_PRINTF printf
void set_bootparam_power_state(uint val)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	printf("%s(%d)\n",__FUNCTION__,val);
//	if(&bootparam == NULL)
//		return;

	if(factory_read(BOOT_PARAM_FILE_NAME, &dst_addr, &dst_length))
		return;

	if(parse_h("BOOT_POWER_ON_MODE", dst_addr, (uint)dst_length, &retVal, &retAddr))
		return;

	if(val == retVal)
		return;

	if (val == 0)
		*retAddr = 0x30;
	else if (val == 1)
		*retAddr = 0x31;
	else
		return;

	if(factory_write(BOOT_PARAM_FILE_NAME, dst_addr, dst_length)!=0) {
		DBG_PRINTF("[DEBUG]%s factory_write error\n",__FUNCTION__);
	}

	if(factory_save()!=0) {
		DBG_PRINTF("[DEBUG]%s factory_save error\n",__FUNCTION__);
	}
}

void set_bootparam_upgrade(int val)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	printf("%s(%d)\n",__FUNCTION__,val);
//	if(&bootparam == NULL)
//		return;

	if(factory_read(BOOT_PARAM_FILE_NAME, &dst_addr, &dst_length))
		return;

	if(parse_h("LOCAL_UPGRADE_EN", dst_addr, (uint)dst_length, &retVal, &retAddr))
		return;

	if(val == retVal)
		return;

	if (val == 0)
		*retAddr = 0x30;
	else if (val == 1)
		*retAddr = 0x31;
	else
		return;

	if(factory_write(BOOT_PARAM_FILE_NAME, dst_addr, dst_length)!=0) {
		DBG_PRINTF("[DEBUG]%s factory_write error\n",__FUNCTION__);
	}

	if(factory_save()!=0) {
		DBG_PRINTF("[DEBUG]%s factory_save error\n",__FUNCTION__);
	}
}

/************************************************************************
**
** get layout.txt in factory area of flash
**
*************************************************************************/
void get_layout(void)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	printf("%s:\n", __FUNCTION__);

//	display_evaluate_time("get_layout-0");

	if (factory_read(BOOT_PART_FILE_NAME, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", BOOT_PART_FILE_NAME);
		boot_part = 0;
	}
	else {
		printf("------------%s found\n", BOOT_PART_FILE_NAME);

		if (parse_h("BOOTPART", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			boot_part = retVal;
			printf("BOOTPART=%d\n", retVal);
		}
		else {
			DEBUG("can't find boot part\n");
		}

		if (parse_h("TAG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			boot_tag = retVal;
			printf("TAG=%d\n", retVal);
		}
		else {
			DEBUG("can't find boot tag\n");
		}
	}

//	display_evaluate_time("get_layout-1");
}


