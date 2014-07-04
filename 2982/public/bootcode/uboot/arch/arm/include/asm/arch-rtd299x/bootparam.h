#ifndef __BOOT_PARAM_H__
#define __BOOT_PARAM_H__

typedef enum {
	POWER_OFF = 0,
	POWER_ON,
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
	unsigned int local_upgrade_en;
	unsigned int bootup_policy;
} bootparam_t;

void get_bootparam(void);
void get_layout(void);
void set_bootparam_power_state(uint val);

extern bootparam_t bootparam;

#endif /* #define __BOOT_PARAM_H__ */

