include $(PRJ).inc

# ********************************************************************
# Detect compiling environment.
# ********************************************************************

# ********************************************************************
# Toolchain specifics.
# ********************************************************************
PERL    = perl
RM      = rm -rf
CD      = cd
CAT     = cat
CP      = cp

# ********************************************************************
# Directories specifics.
# ********************************************************************
TOP_DIR         = $(shell cd ..; pwd)
BIN_DIR         = $(TOP_DIR)/bin
IMAGE_DIR       = $(BIN_DIR)/image
LINK_DIR        = $(BIN_DIR)/link
OBJ_DIR         = $(BIN_DIR)/obj
TMP_DIR         = $(BIN_DIR)/tmp
HW_SETTING_DIR  = $(BIN_DIR)/hw_setting

SRC_DIR         = $(TOP_DIR)/src
INCLUDE_DIR     = $(SRC_DIR)/include
U_BOOT_DIR      = $(TOP_DIR)/uboot
AUX_CODE_DIR	= $(TOP_DIR)/Aux_code
AUX_CODE_UNI_DIR	= $(TOP_DIR)/Aux_code_uni
TOOLS_DIR       = $(TOP_DIR)/tools
RIS_APP_DIR		= $(TOP_DIR)/RisApp

CONFIGCONV_DIR  = $(TOOLS_DIR)/configconv
FLASH_IMAGE_MAKER_DIR = $(TOOLS_DIR)/flash_image_maker
HW_SETTING_MAKER_DIR = $(TOOLS_DIR)/hw_setting_maker
HW_SETTING_HEADER_MAKER_DIR = $(TOOLS_DIR)/hw_setting_header_maker
OTP_PROGAMMER_DIR = $(TOOLS_DIR)/otp_programmer
SCRIPT_DIR      = $(TOOLS_DIR)/script

VERSION         = $(Param_companyID).$(Param_boardID).$(Param_version)

U_BOOT_BIN          = $(U_BOOT_DIR)/u-boot.bin
U_BOOT_MAP          = $(U_BOOT_DIR)/u-boot.map
U_BOOT_DIS          = $(U_BOOT_DIR)/u-boot.dis
U_BOOT_SREC         = $(U_BOOT_DIR)/u-boot.srec
U_BOOT_TARGET       = u-boot.bin

ARM_REDIR_1_BIN     = $(U_BOOT_DIR)/examples/redirect/redirect_1.bin
ARM_REDIR_2_BIN     = $(U_BOOT_DIR)/examples/redirect/redirect_2.bin
ARM_REDIR_ELF       = $(U_BOOT_DIR)/examples/redirect/redirect.elf
ARM_REDIR_TEXT      = $(U_BOOT_DIR)/examples/redirect/redirect.text
ARM_REDIR_1_TARGET  = arm_start.o
ARM_REDIR_2_TARGET  = arm_start2.o

AUX_CODE_BIN		= $(AUX_CODE_DIR)/Aux_code.bin
AUX_CODE_MAP		= $(AUX_CODE_DIR)/Aux_code.map
AUX_CODE_DIS		= $(AUX_CODE_DIR)/Aux_code.dis
AUX_CODE_ARM_REDIR	= $(AUX_CODE_DIR)/arm_redirect
AUX_CODE_TARGET		= Aux_code.bin

AUX_CODE_UNI_BIN		= $(AUX_CODE_UNI_DIR)/Aux_code_uni.bin
AUX_CODE_UNI_MAP		= $(AUX_CODE_UNI_DIR)/Aux_code_uni.map
AUX_CODE_UNI_DIS		= $(AUX_CODE_UNI_DIR)/Aux_code_uni.dis
AUX_CODE_UNI_ARM_REDIR	= $(AUX_CODE_UNI_DIR)/arm_redirect
AUX_CODE_UNI_TARGET		= Aux_code_uni.bin

RIS_APP_BIN				= $(RIS_APP_DIR)/out/ap_template.bin

ifeq ($(ENV), $(CYGWIN_ENV))
LINKOUT_FMAT   = -oformat elf32-littlemips
endif
ifeq ($(ENV), $(LINUX_ENV))
#LINKOUT_FMAT   = -EB
LINKOUT_FMAT   = --oformat elf32-tradlittlemips -EL
#elf32-tradlittlemips
endif


RESET_LINK_SCRIPT   = link.xn

CONFIGCONV_SCRIPT   = configconv.pl
SRECCONV_SCRIPT     = srecconv.pl
SRECCONV_OPTS       = -ES B -EB B -A 29

HW_SETTING_MAKER_AP = generate_config
RTSSL               = $(TOOLS_DIR)/RSA_Tool/RtSSL
R2MODM              = $(TOOLS_DIR)/r2modm/r2modm

#SPLIT_AES_KEY       = $(TOOLS_DIR)/script/split_AES_key.pl
BINARY_TO_ASCII     = $(TOOLS_DIR)/script/binary2ascii.pl
STR2BIN             = $(TOOLS_DIR)/script/str2bin.pl
REVERSE             = $(TOOLS_DIR)/script/reverse.pl
# get from customer folder
RSA_KEY_PATH        = $(BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_RSA_Key_File)
RSA_ROOT_KEY_PATH   = $(BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_RSA_Root_Key_File)
RSA_EXT_KEY_PTATH   = $(BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_RSA_Ext_Key_File)
RSA_INF_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File).inf
RSA_R2_INF_PATH     = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File)_R2.inf

RSA_KEY_RAW_BIN     = $(TMP_DIR)/rsa_key_raw.bin
RSA_KEY_R2_BIN      = $(TMP_DIR)/rsa_key_r2.bin

ifeq ($(strip $(Config_NOR_BOOT_NAND)), TRUE)
  ROM2_IN_NOR      = 1
else
  ROM2_IN_NOR      = 0
endif

# DTE Bootcode default config
Config_DTE_Bootcode_ARCH_Value = arm
Config_DTE_Bootcode_CPU_Value = armv7
Config_DTE_Bootcode_Vendor_Value = realtek
Config_DTE_Bootcode_Options_Value =


# ********************************************************************
# make selection specifics.
# ********************************************************************

#Unmark it to build with aux_code and mark the second line.
ifeq ($(Config_RIS_APP), TRUE)
prj: clean_ris configconv checkfile ris_app aux_code flash_image otp build_done
else
#prj: clean configconv checkfile key uboot aux_code flash_image otp build_done
prj: clean configconv checkfile key uboot flash_image otp build_done
endif


.PHONY: hw_setting uboot otp key

clean:
	$(RM) $(OBJ_DIR)/* $(TMP_DIR)/* dvrboot.exe.bin rescue.exe.bin dvrboot.rescue.exe.bin pgm_otp.bin bootloader.tar $(IMAGE_DIR)/$(Config_DTE_Bootcode_Image_File)

clean_ris:
	$(RM) $(OBJ_DIR)/* $(TMP_DIR)/* dvrboot.exe.bin rescue.exe.bin dvrboot.rescue.exe.bin pgm_otp.bin bootloader.tar

checkfile:
ifeq ($(Config_OTP_Secure_Boot), TRUE)
	@test -s $(RSA_KEY_PATH) || { echo "$(RSA_KEY_PATH) does not exist! Exiting..."; exit 1; }
	@test -s $(RSA_ROOT_KEY_PATH) || { echo "$(RSA_ROOT_KEY_PATH) does not exist! Exiting..."; exit 1; }
	@test -s $(RSA_EXT_KEY_PTATH) || { echo "$(RSA_EXT_KEY_PTATH) does not exist! Exiting..."; exit 1; }
endif

configconv:
	$(PERL) $(SCRIPT_DIR)/$(CONFIGCONV_SCRIPT) \
		$(INCLUDE_DIR)/project_config.h \
		$(BIN_DIR)/$(PRJ).inc \
		$(RSA_INF_PATH) \
		$(RSA_R2_INF_PATH)

key:
ifeq ($(Config_OTP_Secure_Boot), TRUE)
	@# generate rsa key inf
	@echo Config_Secure_RSA_MODULUS=\"`$(RTSSL) rsa -print -modulous -i $(RSA_KEY_PATH)`\" > $(RSA_INF_PATH);
	@# generate rsa key R2 inf
	@$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY_PATH)` > $(RSA_KEY_RAW_BIN)
	@$(R2MODM) $(RSA_KEY_RAW_BIN) $(RSA_KEY_R2_BIN) > /dev/null 2>&1	
	@$(REVERSE) $(RSA_KEY_R2_BIN) > $(RSA_KEY_R2_BIN).rev	
	@echo Config_Secure_RSA_R2=\"`hexdump -e '256/1 "%02X"' $(RSA_KEY_R2_BIN).rev`\" > $(RSA_R2_INF_PATH);
endif
	
uboot:
	$(CD) $(U_BOOT_DIR); \
		make distclean; \
		echo "$(Config_DTE_Bootcode_Config_Value) $(Config_DTE_Bootcode_ARCH_Value) $(Config_DTE_Bootcode_CPU_Value) $(Config_DTE_Bootcode_Board_name_Value) $(Config_DTE_Bootcode_Vendor_Value) $(Config_DTE_Bootcode_SOC_Value) $(Config_DTE_Bootcode_Options_Value)" > boards.cfg; \
		make $(Config_DTE_Bootcode_Config_Value)

	$(CD) $(TMP_DIR); \
		$(CP) $(U_BOOT_BIN) $(U_BOOT_TARGET); \
		$(CP) $(U_BOOT_MAP) $(U_BOOT_DIS) $(U_BOOT_SREC) ./; \
		$(CP) $(U_BOOT_TARGET) $(IMAGE_DIR)/$(Config_DTE_Bootcode_Image_File)

	$(CD) $(AUX_CODE_ARM_REDIR); \
		$(CP) $(ARM_REDIR_1_BIN) ./$(ARM_REDIR_1_TARGET); \
		$(CP) $(ARM_REDIR_2_BIN) ./$(ARM_REDIR_2_TARGET); \
		$(CP) $(ARM_REDIR_ELF) $(ARM_REDIR_TEXT) ./

	$(CD) $(AUX_CODE_UNI_ARM_REDIR); \
		$(CP) $(ARM_REDIR_1_BIN) ./$(ARM_REDIR_1_TARGET); \
		$(CP) $(ARM_REDIR_2_BIN) ./$(ARM_REDIR_2_TARGET); \
		$(CP) $(ARM_REDIR_ELF) $(ARM_REDIR_TEXT) ./

ris_app:
	$(CD) $(RIS_APP_DIR); \
		make clean; \
		make

	$(CP) $(RIS_APP_BIN) $(U_BOOT_TARGET); \
		$(CP) $(U_BOOT_TARGET) $(IMAGE_DIR)/$(Config_DTE_Bootcode_Image_File)

aux_code:
ifeq ($(strip $(Config_RIS_APP)), TRUE)
		echo "Riscure Test App Build"; \
		echo '#define CONFIG_RIS_APP '  > $(AUX_CODE_DIR)/include/ris_app.h;
		echo '#define CONFIG_RIS_APP '  > $(AUX_CODE_UNI_DIR)/include/ris_app.h;
else
		echo ' '  > $(AUX_CODE_DIR)/include/ris_app.h;
		echo ' '  > $(AUX_CODE_UNI_DIR)/include/ris_app.h;
endif
	if [ $(shell echo $(Config_Aux_Code_Image_File) | grep fpga) != "" ]; then \
		$(CD) $(AUX_CODE_DIR); \
		make clean; \
		make env=fpga ver=$(Config_Chip_Version); \
		echo "Aux code -> fpga $(Config_Chip_Version)"; \
		$(CP) $(AUX_CODE_TARGET) $(IMAGE_DIR)/$(Config_Aux_Code_Image_File); \
	elif [ $(shell echo $(Config_Aux_Code_Image_File) | grep realchip) != "" ]; then \
		$(CD) $(AUX_CODE_DIR); \
		make clean; \
		make env=realchip ver=$(Config_Chip_Version); \
		echo "Aux code - > realchip $(Config_Chip_Version)"; \
		$(CP) $(AUX_CODE_TARGET) $(IMAGE_DIR)/$(Config_Aux_Code_Image_File); \
	else \
		$(CD) $(AUX_CODE_UNI_DIR); \
		make clean; \
		make; \
		echo "Aux code universal version"; \
		$(CP) $(AUX_CODE_UNI_TARGET) $(IMAGE_DIR)/$(Config_Aux_Code_Image_File); \
	fi

flash_image: hw_setting
ifeq ($(strip $(Rescue_Source)), FLASH)
	$(CD) $(FLASH_IMAGE_MAKER_DIR); \
	make PRJ=$(PRJ) clean; \
	make PRJ=$(PRJ) output=rescue b2a; \
	make PRJ=$(PRJ) output=rescue dvrboot; \
	$(CP) -vf dvrboot.exe.bin $(TOP_DIR)/bin/rescue.exe.bin
	$(CD) $(FLASH_IMAGE_MAKER_DIR); \
	make PRJ=$(PRJ) clean; \
	make PRJ=$(PRJ) b2a; \
	make PRJ=$(PRJ) dvrboot; \
	$(CP) -vf dvrboot.exe.bin $(TOP_DIR)/bin/dvrboot.rescue.exe.bin
endif
	$(CD) $(FLASH_IMAGE_MAKER_DIR); \
	make PRJ=$(PRJ) clean; \
	make PRJ=$(PRJ) output=bootcode b2a; \
	make PRJ=$(PRJ) output=bootcode dvrboot; \
	make PRJ=$(PRJ) package; \
	$(CP) -vf dvrboot.exe.bin $(TOP_DIR)/bin/dvrboot.exe.bin; \
	$(CP) -vf bootloader.tar $(TOP_DIR)/bin/bootloader.tar

otp: flash_image
ifeq ($(strip $(Config_OTP_Secure_Boot)), TRUE)
	$(CD) $(OTP_PROGAMMER_DIR); \
	make clean; \
	make; \
	$(CP) -vf program_rtd298x_otp.bin $(TOP_DIR)/bin/pgm_otp.bin
endif

hw_setting:
	cd $(HW_SETTING_DIR);make build_config HW_CONFIG=$(Config_Aux_Code_HW_SETTING);
	cd $(HW_SETTING_DIR);make hw_setting;
	@if test -n "$$(find $(HW_SETTING_DIR)/hw_setting.bin -size +4096c)" ; then echo "error! hwsetting size too large. Exiting...";exit 1; fi

build_done:
	@echo "Build done!!!"
	@echo ""
	@echo "==========================================================================="
	@echo ""
	@echo "         Project config :" $(PRJ);
ifeq ($(strip $(Config_RIS_APP)), TRUE)
	@echo ""
	@echo "         === Riscure Test App Build ==="
	@echo ""
endif
	@echo ""
	@echo "           auxcode file : "$(Config_Aux_Code_Image_File);
	@echo "         hwsetting file : "$(Config_Aux_Code_HW_SETTING);
	@echo "           package type : "$(Config_Package_type);
	@echo "            package ver : "$(Config_Chip_Version);
	@echo ""
	@echo "==========================================================================="
	@echo ""
	@echo "   output => bin/dvrboot.exe.bin          (bootcode only)"
ifeq ($(strip $(Rescue_Source)), FLASH)
	@echo "   output => bin/rescue.exe.bin           (rescue linux only)"
	@echo "   output => bin/dvrboot.rescue.exe.bin   (bootcode and rescue linux)"
endif
ifeq ($(strip $(Config_OTP_Secure_Boot)), TRUE)
	@echo ""
	@echo "   output => bin/pgm_otp.bin              (otp programmer)"
	@echo ""
endif
	@echo "   ------------------------------------------------------------------"
	@echo "   output => bin/bootloader.tar           (install package)"
	@echo ""
	@echo "   Build date:  "$(shell date);
	@echo "==========================================================================="
	@echo ""
ifeq ($(strip $(Config_OTP_Secure_Boot)), TRUE)
	@echo -e "\e[1;32m   Warning: This is a OTP Sercure Boot Package!\e[0m"
	@echo -e "\e[1;32m            Please make sure your target board had programmed OTP.\e[0m"
	@echo ""
endif

# ********************************************************************
# Include specifics.
# ********************************************************************



