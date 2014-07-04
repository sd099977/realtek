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
#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
extern uint  custom_image_length ;
#endif

extern uint boot_part;

#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)//20140506  xq_xiao
extern int konka_boot_vol;
extern int konka_sleepled_mode;
extern int konka_uart_enable; 
#endif


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

#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	   	if (parse_h("CUSTOM_IMAGE_LENG", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			bootparam.custom_image_leng = retVal;
			printf("CUSTOM_IMAGE_LENG=%d\n", retVal);
		}
		else {
			bootparam.custom_image_leng = 11;
			DEBUG("can't find custom_image_leng (default=11)\n");
		}
#endif

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

#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
		memset(bootparam.install_file_name, 0, sizeof(bootparam.install_file_name));
		if (parse_h("IMGFILE_PATTERN", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			strncpy(bootparam.install_file_name, retAddr, bootparam.custom_image_leng);
			printf("IMGFILE_PATTERN=[%s]\n", bootparam.install_file_name);
      		}
      		else{
			bootparam.install_file_name[0] = 'i';
			bootparam.install_file_name[1] = 'n';
			bootparam.install_file_name[2] = 's';
			bootparam.install_file_name[3] = 't';
			bootparam.install_file_name[4] = 'a';
			bootparam.install_file_name[5] = 'l';
			bootparam.install_file_name[6] = 'l';
			bootparam.install_file_name[7] = '.';
			bootparam.install_file_name[8] = 'i';
			bootparam.install_file_name[9] = 'm';
			bootparam.install_file_name[10] = 'g';
			bootparam.install_file_name[11] = '\0';
         		DEBUG("can't IMGFILE_PATTERN (default=install.img)\n");
      		}
#else
		memset(bootparam.install_file_name, 0, sizeof(bootparam.install_file_name));
		if (parse_h("IMGFILE_PATTERN", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			strncpy(bootparam.install_file_name, retAddr+1, retVal-2);	// exclude two " symbols
			printf("IMGFILE_PATTERN=%s\n", bootparam.install_file_name);
      		}
      		else{
         		DEBUG("can't IMGFILE_PATTERN\n");
      		}
#endif
			
	}

	// RTK config don't care prev_power_state and always power on
	boot_power_on_mode = POWER_ON;
	prev_power_on_status = bootparam.prev_power_state;
#ifdef CONFIG_BOARD_298X_TV013_QFP176_EMMC
	if (parse_h("BOOTUP_POLICY", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
		bootparam.bootup_policy = retVal;
		printf("BOOTUP_POLICY=%d\n", retVal);
	}
	else {
		bootparam.bootup_policy = 2; //auto by prev_status
		DEBUG("can't find bootup_policy\n");
	}
	if(bootparam.bootup_policy == 5 || boot_ac_on == 1)
		boot_power_on_mode = bootparam.prev_power_state;

#elif defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC) //20140506  xq_xiao 
	if (parse_h("BOOT_BACKLIGHT_VALUE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
		bootparam.backlight_value = retVal;
		printf("BOOT_BACKLIGHT_VALUE=%d\n", retVal);
	}
	else {
		bootparam.backlight_value = 254;
		DEBUG("can't find backlight value\n");
	}

	if (parse_h("BOOT_KONKA_BOOT_VOL", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
		bootparam.konka_boot_vol = retVal;
		printf("BOOT_KONKA_BOOT_VOL=%d\n", retVal);
	}
	else {
		bootparam.konka_boot_vol = 0;
		DEBUG("can't find konka_boot_vol\n");
	}
	
	if (parse_h("BOOT_KONKA_SLEEPLED_MODE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
		bootparam.konka_sleepled_mode = retVal;
		printf("BOOT_KONKA_SLEEPLED_MODE=%d\n", retVal);
	}
	else {
		bootparam.konka_sleepled_mode = 0;
		DEBUG("can't find konka_sleepled_mode\n");
	}
	
	if (parse_h("BOOT_KONKA_UART_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
		bootparam.konka_uart_enable = retVal;
		printf("BOOT_KONKA_UART_ENABLE=%d\n", retVal);
	}
	else {
		bootparam.konka_uart_enable = 0;
		DEBUG("can't find konka_uart_enable\n");
	}

	if (bootparam.konka_uart_enable)
	{
         printf("bootparam.konka_uart_enable = 1\n");
         //2982  0x18060204
         rtd_maskl(0xb8060204, 0x07FFFFFF, 9<<27);//TX
        //rtd_maskl(0xb8060200, 0xFFFFC1FF, 0x9<<9);//RX

	}
	else
	{    
	   printf("bootparam.konka_uart_enable = 0\n");
       //2982                          07 fff fff
        rtd_maskl(0xb8060204, 0x07FFFFFF, 31<<27);//TX
	    //rtd_maskl(0xb8060200, 0xFFFFC1FF, 0x1F<<9);//RX	
	}

	
	konka_boot_vol = bootparam.konka_boot_vol;
	konka_sleepled_mode = bootparam.konka_sleepled_mode;
	konka_uart_enable = bootparam.konka_uart_enable;

	boot_power_on_mode = bootparam.prev_power_state;
	if ( boot_ac_on == 0 )	 //DC  ON
	{
		boot_power_on_mode = POWER_ON;
		set_bootparam_power_state(POWER_ON);
		mdelay(10);
	}
#elif (defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1))
	if(boot_ac_on == 1)
		boot_power_on_mode = bootparam.prev_power_state;
	else{
		boot_power_on_mode = POWER_ON;
		set_bootparam_power_state(POWER_ON);
		mdelay(10);
	}
#endif

#if defined(CONFIG_BOOTUP_BY_PREV_POWER_STATUS) || defined(ENABLE_BOOTUP_POLICY)
	if(boot_ac_on)
		boot_power_on_mode = bootparam.prev_power_state;
#endif

#ifdef ENABLE_BOOTUP_POLICY
	printf("bootup_policy=%d\n", bootparam.bootup_policy);
	if(bootparam.bootup_policy != 2)	//0: always powerOff, 1: always powerOn, 2:auto by prev_status
		{
		if(boot_ac_on)
			boot_power_on_mode = bootparam.bootup_policy;
		else
			boot_power_on_mode = POWER_ON;
		}
#endif

//	if (GET_IC_VERSION() == VERSION_A)		//bcoz ver.A ac_on detect has bug. fix always enter standby mode
//		boot_power_on_mode = POWER_ON;

	printf("boot_power_on_mode=%d\n", boot_power_on_mode);

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

#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)//20140506  xq_xiao
void set_bootparam_uart(int val)
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

	if(parse_h("BOOT_KONKA_UART_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr))
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
#elif defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)
void set_bootparam_policy(int val)
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

	if(parse_h("BOOTUP_POLICY", dst_addr, (uint)dst_length, &retVal, &retAddr))
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
#endif

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


