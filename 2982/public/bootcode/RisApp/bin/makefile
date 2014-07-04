
ifeq "$(PRJ)" ""
PRJ = RTD2994
endif

include $(PRJ).inc

# ********************************************************************
# Detect compiling environment.
# ********************************************************************
UNAME = $(shell uname)
LINUX_ENV = "LINUX"
CYGWIN_ENV = "CYGWIN"
ENV = $(CYGWIN_ENV) # default

ifneq "$(filter Linux%,$(UNAME))" ""
ENV = $(LINUX_ENV)
endif

ifneq "$(filter CYGWIN%,$(UNAME))" ""
ENV = $(CYGWIN_ENV)
endif

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

CONFIGCONV_DIR  = $(TOOLS_DIR)/configconv
FLASH_IMAGE_MAKER_DIR = $(TOOLS_DIR)/flash_image_maker
SCRIPT_DIR      = $(TOOLS_DIR)/script

INCLUDE_DIR     = $(FLASH_IMAGE_MAKER_DIR)/util/
TOOLS_DIR       = $(TOP_DIR)/tools
SED_DIR         = $(TOP_DIR)/
SED_TARGET      = $(SED_DIR)/out/ap_template.bin

VERSION         = $(Param_companyID).$(Param_boardID).$(Param_version)


#LINKOUT_FMAT   = -EB
LINKOUT_FMAT   = --oformat elf32-tradlittlemips -EL
#elf32-tradlittlemips


RESET_LINK_SCRIPT   = link.xn

CONFIGCONV_SCRIPT   = configconv.pl
SRECCONV_SCRIPT     = srecconv.pl
SRECCONV_OPTS       = -ES B -EB B -A 29


HW_SETTING_MAKER_AP = generate_config
RTSSL               = $(TOOLS_DIR)/RSA_Tool/RtSSL


#SPLIT_AES_KEY       = $(TOOLS_DIR)/script/split_AES_key.pl
BINARY_TO_ASCII     = $(TOOLS_DIR)/script/binary2ascii.pl
STR2BIN             = $(TOOLS_DIR)/script/str2bin.pl
REVERSE_BIN         = $(TOOLS_DIR)/script/revsre.pl
RSA_KEY_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File)
RSA_INF_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File).inf
RSA_KEY0_PATH       = $(IMAGE_DIR)/$(Config_Secure_RSA_Key0_File)
RSA_INF0_PATH       = $(IMAGE_DIR)/$(Config_Secure_RSA_Key0_File).inf
#AES_KEY_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key_File)
#AES_INF_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key_File).inf
AES_SEED_PATH       = $(IMAGE_DIR)/$(Config_Secure_AES_Seed_File)

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

prj: clean configconv flash_image 

clean:
	$(RM) $(OBJ_DIR)/* $(TMP_DIR)/* dvrboot.exe.bin rescue.exe.bin dvrboot.rescue.exe.bin bootloader.tar

configconv: rsa_key aes_seed rsa_key0
	$(PERL) $(SCRIPT_DIR)/$(CONFIGCONV_SCRIPT) \
		$(INCLUDE_DIR)/project_config.h \
		$(BIN_DIR)/$(PRJ).inc \
		$(RSA_INF_PATH) \
		$(RSA_INF0_PATH)

rsa_key:
	if [ $(Config_Secure_RSA_Key_File) ]; then \
		echo Config_Secure_RSA_MODULUS=\"`$(RTSSL) rsa -print -modulous -i $(RSA_KEY_PATH)`\" > $(RSA_INF_PATH) ;\
	else \
		echo "Config_Secure_RSA_Key_File not defined in $(PRJ).inc"; \
	fi

rsa_key0:
	if [ $(Config_Secure_RSA_Key0_File) ]; then \
		echo Config_Secure_RSA0_MODULUS=\"`$(RTSSL) rsa -print -modulous -i $(RSA_KEY0_PATH)`\" > $(RSA_INF0_PATH) ;\
	else \
		echo "Config_Secure_RSA_Key0_File not defined in $(PRJ).inc"; \
	fi

#aes_key:
#	if [ $(Config_Secure_AES) ]; then \
#		$(SPLIT_AES_KEY) `head -n 1 $(AES_KEY_PATH)` > $(AES_INF_PATH) ;\
#	else \
#		echo "Config_Secure_AES not defined in $(PRJ).inc"; \
#	fi

aes_seed:
	if [ $(Config_Secure_AES_Seed_File) ]; then \
		echo 'unsigned char kimg_seed[] = {' `$(BINARY_TO_ASCII) $(AES_SEED_PATH)` '};' > $(INCLUDE_DIR)/kimg_seed.h; \
	else \
		echo "Config_Secure_AES_Seed_File not defined in $(PRJ).inc"; \
	fi

SED:
	$(CD) $(SED_DIR); \
	make clean; \
	make; \
	$(CP) $(SED_TARGET) $(IMAGE_DIR)/$(Config_Aux_Code_Image_File)
		
flash_image: SED
	$(CD) $(FLASH_IMAGE_MAKER_DIR);\
	make PRJ=$(PRJ) clean;\
	make PRJ=$(PRJ) output=bootcode b2a;\
	make PRJ=$(PRJ) output=bootcode dvrboot;\
	cp -vf dvrboot.exe.bin $(TOP_DIR)/bin/dvrboot.exe.bin

# ********************************************************************
# Include specifics.
# ********************************************************************cd 

