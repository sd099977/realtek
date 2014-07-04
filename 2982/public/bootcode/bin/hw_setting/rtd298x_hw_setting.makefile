HW_SETTING_FILE = Pre_CRT.tbl

HW_SETTING_FILE += ddr_freq.tbl

ifeq ($(CONFIG_QFP),y)
HW_SETTING_FILE += DDR_Setting_QFP.tbl
else ifeq ($(CONFIG_BGA),y)
HW_SETTING_FILE += DDR_Setting_BGA.tbl
endif

HW_SETTING_FILE += Post_CRT_arbitration.tbl
