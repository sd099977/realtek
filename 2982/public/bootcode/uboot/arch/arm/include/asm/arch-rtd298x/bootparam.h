#ifndef __BOOT_PARAM_H__
#define __BOOT_PARAM_H__

typedef enum {
	POWER_OFF = 0,
	POWER_ON,
	BACKLIGHT_OFF,
} POWER_MODE_T;

typedef struct {
	unsigned int prev_power_state;
	unsigned int boot_logo_enable;
	unsigned int boot_music_enable;
	unsigned int backlight_value;
	unsigned int custom_video1_leng;
	unsigned int custom_video2_leng;
	unsigned int custom_audio1_leng;
	unsigned int custom_audio2_leng;
#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	unsigned int custom_image_leng;
#endif
	unsigned int local_upgrade_en;
	unsigned int bootup_policy;
#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)//20140506  xq_xiao
	unsigned int konka_boot_vol;
	unsigned int konka_sleepled_mode;
	unsigned int konka_uart_enable;	
#endif
	unsigned char install_file_name[64];
} bootparam_t;

void get_bootparam(void);
void get_layout(void);
void set_bootparam_power_state(uint val);
#ifdef CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC//20140506  xq_xiao
void set_bootparam_uart(int val);
#endif
extern bootparam_t bootparam;

#endif /* #define __BOOT_PARAM_H__ */

