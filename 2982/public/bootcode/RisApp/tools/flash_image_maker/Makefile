# Detect compiling environment.
# ********************************************************************
TOPDIR  := $(shell /bin/pwd)
#$(warning TOPDIR is  $(TOPDIR)!!)
BOOTCODE_ROOT := $(TOPDIR)/../../..
#$(warning bBOOTCODE_ROOT is  $(BOOTCODE_ROOT)!!)
#TOOLCHAIN_PREFIX := asdk-4.8.2-a7-EL-3.7-0.9.33-a32nt-131122
TOOLCHAIN_PREFIX := asdk-4.8.3-a7-EL-3.7-0.9.33-a32nt-140428
TOOLCHAIN_READY := $(wildcard $(BOOTCODE_ROOT)/tmp/$(TOOLCHAIN_PREFIX))
ifeq ($(strip $(TOOLCHAIN_READY)),)
   $(warning toolchain $(TOOLCHAIN_PREFIX) is not ready, !!!)
#   $(shell mkdir -p ../../tmp)
#   $(shell tar xfj $(BOOTCODE_ROOT)/toolchain/$(TOOLCHAIN_PREFIX).tar.bz2 -C $(BOOTCODE_ROOT)/tmp)
endif

# Tool-chain used for compilation of target code.
TOOLCHAIN_PATH = $(BOOTCODE_ROOT)/tmp/$(TOOLCHAIN_PREFIX)/bin

XCC       = $(TOOLCHAIN_PATH)/asdk-linux-gcc
LD        = $(TOOLCHAIN_PATH)/asdk-linux-ld
OBJCOPY   = $(TOOLCHAIN_PATH)/asdk-linux-objcopy
OBJDUMP   = $(TOOLCHAIN_PATH)/asdk-linux-objdump
XCXX      = $(XCC)

UNAME = $(shell uname)
LINUX_ENV = "LINUX"
CYGWIN_ENV = "CYGWIN"
ENV = $(CYGWIN_ENV)	# default

ifneq "$(filter Linux%,$(UNAME))" ""
ENV = $(LINUX_ENV)
endif

ifneq "$(filter CYGWIN%,$(UNAME))" ""
ENV = $(CYGWIN_ENV)
endif

PRO_CPU = ARM_A7

# ********************************************************************
# Include specifics.
# ********************************************************************

TOP_DIR         = $(shell cd .; pwd)
PRJ_DIR         = $(PWD)/../..
PRJ_BIN_DIR     = $(PRJ_DIR)/bin
PRJ_INC_DIR     = $(PRJ_DIR)/src/include
PRJ_TOOL_DIR	= $(PRJ_DIR)/tools
IMAGE_DIR       = $(PRJ_DIR)/bin/image
#AES_DIR         = $(PRJ_TOOL_DIR)/aes/Debug
PACKAGE_DIR     = $(PWD)/temp_package
ENCRYPTOR_DIR   = $(PRJ_TOOL_DIR)/FileHashGenerator
UTIL_DIR        = $(PWD)/util
OBJ_DIR	        = $(PWD)/obj
SHA_DIR		= $(PRJ_TOOL_DIR)/do_sha256
RSA_TOOL_DIR    = $(PRJ_TOOL_DIR)/RSA_Tool
RTSSL2_DIR      = $(PRJ_TOOL_DIR)/RtSSL
SCRIPT_DIR      = $(PRJ_TOOL_DIR)/script
CRC32_DIR       = $(PRJ_TOOL_DIR)/crc32
INVERSE_DIR     = $(PRJ_TOOL_DIR)/inverse
IMG_PREPROCESSOR_DIR = $(PRJ_TOOL_DIR)/image_preprocessor

include $(PRJ_BIN_DIR)/$(PRJ).inc

SHELL_PROD_DIR	= $(PRJ_DIR)/src/apps/shell/product/$(Config_Product)

# ********************************************************************
# VARIABLES specifics.
# ********************************************************************

ifeq ($(PRO_CPU), ARM_A7)
#use ARM_A7 for programming
CFLAGS        = -g -fno-common -ffixed-r8 -msoft-float \
				-fno-builtin -ffreestanding -nostdinc -pipe -marm \
				-mno-thumb-interwork -mabi=aapcs-linux -march=armv7-a -mno-unaligned-access
CXXFLAGS      = $(CFLAGS) -Wa,--gdwarf2
EXTRACFLAGS   = -Wall
EXTRACXXFLAGS = $(EXTRACFLAGS) -fno-exceptions
LDFLAGS       = -nostartfiles -L/lib -I/include -EL
LD_SCRIPT     = -T $(PWD)/dvrboot.ld

CFLAG       = $(CFLAGS)
AFLAG       = $(CFLAG)
CDEF        = -DEL
ADEF        = $(CDEF) -D_ASSEMBLER_

BIN2ASCII   = bin2ascii
else
#use KCPU for programming
CFLAGS        = -mno-gpopt -gdwarf-2 -O0 -G0 -DEJTAG -march=4181 -Wall -mno-abicalls -nostdinc -finhibit-lt -finhibit-st -fomit-frame-pointer -fno-common -fno-pic -EL

CXXFLAGS      = $(CFLAGS) -Wa,--gdwarf2
EXTRACFLAGS   = -Wall
EXTRACXXFLAGS = $(EXTRACFLAGS) -fno-exceptions
LDFLAGS       = -nostartfiles -L/lib -I/include -EL
LD_SCRIPT     = -T $(PWD)/dvrboot.ld

CFLAG       = $(CFLAGS)
AFLAG       = $(CFLAG)
CDEF        = -DEL
ADEF        = $(CDEF) -D_ASSEMBLER_

BIN2ASCII   = bin2ascii
endif

# ********************************************************************
# TOOL related.
# ********************************************************************

ifeq ($(ENV), $(CYGWIN_ENV))
CRC32         = $(CRC32_DIR)/crc32.exe
endif
ifeq ($(ENV), $(LINUX_ENV))
CRC32         = $(CRC32_DIR)/crc32
endif

ifeq ($(ENV), $(CYGWIN_ENV))
SHA_EXE       = $(SHA_DIR)/do_sha256.exe
endif
ifeq ($(ENV), $(LINUX_ENV))
SHA_EXE       = $(SHA_DIR)/do_sha256
endif

ifeq ($(ENV), $(CYGWIN_ENV))
INVERSE       = $(INVERSE_DIR)/inverse.exe
endif
ifeq ($(ENV), $(LINUX_ENV))
INVERSE       = $(INVERSE_DIR)/inverse
endif

ifeq ($(ENV), $(CYGWIN_ENV))
RTSSL_EXE     = $(RSA_TOOL_DIR)/RtSSL.exe
endif
ifeq ($(ENV), $(LINUX_ENV))
RTSSL_EXE     = $(RSA_TOOL_DIR)/RtSSL
endif

RTSSL2_EXE    = $(RTSSL2_DIR)/RtSSL2


# ********************************************************************
# SCRIPT related.
# ********************************************************************

STR2BIN           = $(SCRIPT_DIR)/str2bin.pl
GETFILESIZE       = $(SCRIPT_DIR)/get_size.pl
GETBOOTCODESIZE   = $(SCRIPT_DIR)/get_bootcode_size.pl


ifeq ($(strip $(secure)), on)
  SECURE_PACK     = 1
else
  SECURE_PACK     = 0
endif

ifeq ($(strip $(test_secure)), on)
  TEST_SECURE_PACK= 1
else
  TEST_SECURE_PACK= 0
endif


# ********************************************************************
# FILE PARAMETER DEFINE related.
# ********************************************************************

HW_SETTING_TARGET_SRC = $(PRJ_BIN_DIR)/hw_setting/hw_setting.bin
HW_SETTING_TARGET = hw_setting.bin
HW_SETTING_TARGET_INVERSE = hw_setting_inv.bin
DRAM_STR      = _$(Board_DRAM_Block)x$(Board_DRAM_Number)
##BIN_ARGS      = "hw_setting="$(HW_SETTING_TARGET_INVERSE)


PRJ_CONFIG_TARGET = $(PRJ_INC_DIR)/project_config.h

TARGET            = $(PRJ)
TARGET_NAME       = $(PRJ)
MEMORY_LAYOUT     = $(PWD)/xMemoryLayout.map
TARGET_EXE        = $(PWD)/dvrboot.exe
TARGET_BIN        = $(PWD)/$(TARGET_NAME).bin
TARGET_DIS        = $(PWD)/$(TARGET_NAME).dis
ALL_OBJ           = $(notdir $(wildcard $(OBJ_DIR)/*.o))

OUTPUT_BIN        = $(PWD)/qq.bin


AES_SEED_FILE     = $(PRJ_BIN_DIR)/image/$(Config_Secure_AES_Seed_File)
RSA_KEY_FILE      = $(PRJ_BIN_DIR)/image/$(Config_Secure_RSA_Key_File)
RSA_KEY0_FILE      = $(PRJ_BIN_DIR)/image/$(Config_Secure_RSA_Key0_File)
SIGNATURE_TARGET  = signature.bin


LINUX_RESCUE_TARGET           = $(IMAGE_DIR)/$(Rescue_File_Name)
LINUX_RESCUE_PADDING_TARGET   = $(TOP_DIR)/$(Rescue_File_Name)_sha256_padding.bin
LINUX_RESCUE_DIGEST_TARGET    = $(TOP_DIR)/$(Rescue_File_Name)_sha256_digest.bin
LINUX_RESCUE_HASH_TARGET      = $(TOP_DIR)/$(Rescue_File_Name)_hash_target.bin
LINUX_RESCUE_SIGNATURE_TARGET = $(Rescue_File_Name)_signature.bin
LINUX_RESCUE_HASH_TARGET_AES  = $(TOP_DIR)/$(Rescue_File_Name)_hash_target.aes


PACKAGE_PRJ_CONFIG= $(PACKAGE_DIR)/project_config.h
PACKAGE_SYS_CONFIG= $(PACKAGE_DIR)/sys_param.h
PACKAGE_RESET     = $(PACKAGE_DIR)/resetrom-new.bin
PACKAGE_HWSETTING = $(PACKAGE_DIR)/hwsetting.bin
PACKAGE_LINUX_RESCUE = $(PACKAGE_DIR)/vmlinux.rescue.rtd298x.bin.lzma

SCS_NOCS_CERT_TDB     = $(IMG_PREPROCESSOR_DIR)/output/scs_nocs_certificate.tdb
SCS_NOCS_CERT_EM      = $(IMG_PREPROCESSOR_DIR)/output/scs_nocs_certificate.em
SCS_NOCS_CERT_SIG     = $(IMG_PREPROCESSOR_DIR)/output/scs_nocs_certificate_sig.bin
SCS_PARAMS_AREA_TDB   = $(IMG_PREPROCESSOR_DIR)/output/scs_params_area.tdb
SCS_PARAMS_AREA_EM    = $(IMG_PREPROCESSOR_DIR)/output/scs_params_area.em
SCS_PARAMS_AREA_SIG   = $(IMG_PREPROCESSOR_DIR)/output/scs_params_area_sig.bin
SCS_AUX_CODE_TDB      = $(IMG_PREPROCESSOR_DIR)/output/scs_aux_code.tdb
SCS_AUX_CODE_EM       = $(IMG_PREPROCESSOR_DIR)/output/scs_aux_code.em
SCS_AUX_CODE_SIG      = $(IMG_PREPROCESSOR_DIR)/output/scs_aux_code_sig.bin
SCS_DTE_BOOTCODE_TDB  = $(IMG_PREPROCESSOR_DIR)/output/scs_dte_bootcode.tdb
SCS_DTE_BOOTCODE_EM   = $(IMG_PREPROCESSOR_DIR)/output/scs_dte_bootcode.em
SCS_DTE_BOOTCODE_SIG  = $(IMG_PREPROCESSOR_DIR)/output/scs_dte_bootcode_sig.bin



# ********************************************************************
# EXTERN DEFINE related.
# ********************************************************************

# burn NAND flash in FPGA
ifeq ($(strip $(flash_type)), nand)
  CFLAGS += -D_FPGA_NAND_
endif



# ********************************************************************
# Function.
# ********************************************************************
#$(call rsa-sign, input_binary, output_padding, output_digest, input_rsa_key_file, output_signature)
rsa-sign =                                                             \
	$(SHA_EXE) $(1) $(2) $(3);                                     \
	$(RTSSL_EXE) enc -e -rsa -i $(3) -k $(4) -o $(5);

# ********************************************************************
# Object specifics.
# ********************************************************************

#OBJECTS       = ram_boot.o flashdev_n.o flashdev_s.o dvrmain.o flashdev_e.o
OBJECTS       = ram_boot.o flashdev_n.o flashdev_s.o flashdev_sn.o flashdev_e.o dvrmain.o dvrload.o

# ********************************************************************
# RULES specifics.
# ********************************************************************
.PHONY: all clean utility image_preprocessor

all: clean b2a dvrboot package

clean:
	-rm -f $(TARGET_EXE) $(OBJ_DIR)/*.o  *.o temp ram_boot.S *.tar *.bin *.map *.dis
	-rm -rf $(PACKAGE_DIR) $(SIGNATURE_TARGET).reverse

image_preprocessor: $(INVERSE) $(SHA_EXE)
	@# preprocess image
	cd $(IMG_PREPROCESSOR_DIR);\
	make PRJ=$(PRJ)
	@# add image into dvrload.o
	if [ -e $(SCS_NOCS_CERT_TDB) ]; then	\
		$(OBJCOPY) --add-section .scs_nocs_cert_tdb=$(SCS_NOCS_CERT_TDB) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_nocs_cert_em=$(SCS_NOCS_CERT_EM) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_nocs_cert_sig=$(SCS_NOCS_CERT_SIG) $(OBJ_DIR)/dvrload.o; \
	fi
	if [ -e $(SCS_PARAMS_AREA_TDB) ]; then	\
		$(OBJCOPY) --add-section .scs_params_area_tdb=$(SCS_PARAMS_AREA_TDB) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_params_area_em=$(SCS_PARAMS_AREA_EM) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_params_area_sig=$(SCS_PARAMS_AREA_SIG) $(OBJ_DIR)/dvrload.o; \
	fi
	if [ -e $(SCS_AUX_CODE_TDB) ]; then	\
		$(OBJCOPY) --add-section .scs_aux_code_tdb=$(SCS_AUX_CODE_TDB) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_aux_code_em=$(SCS_AUX_CODE_EM) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_aux_code_sig=$(SCS_AUX_CODE_SIG) $(OBJ_DIR)/dvrload.o; \
	fi
	if [ -e $(SCS_DTE_BOOTCODE_TDB) ]; then	\
		$(OBJCOPY) --add-section .scs_dte_bootcode_tdb=$(SCS_DTE_BOOTCODE_TDB) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_dte_bootcode_em=$(SCS_DTE_BOOTCODE_EM) $(OBJ_DIR)/dvrload.o; \
		$(OBJCOPY) --add-section .scs_dte_bootcode_sig=$(SCS_DTE_BOOTCODE_SIG) $(OBJ_DIR)/dvrload.o; \
	fi


b2a:
	./$(BIN2ASCII) $(BIN_ARGS) > temp
	cat rambootdummy temp > ram_boot.S
	cp temp $(MEMORY_LAYOUT)

dvrboot: $(OBJECTS) image_preprocessor utility
	cd $(OBJ_DIR); \
	$(LD) $(LDFLAGS) -e _ram_boot -o $(TARGET_EXE) $(ALL_OBJ) \
	$(LD_SCRIPT)  -Map $(MEMORY_LAYOUT)
	$(OBJCOPY) -O binary  $(TARGET_EXE) $(TARGET_BIN)
	cp $(TARGET_BIN) $(TARGET_EXE).bin
	cp $(TARGET_BIN) $(OUTPUT_BIN)

dis: $(TARGET_EXE)
	$(OBJDUMP) -S --disassemble-all $(TARGET_EXE) > $(TARGET_DIS)

utility:
	cd $(UTIL_DIR);\
	make CC=$(XCC) CFLAG='$(CFLAG)' AFLAG='$(AFLAG)' CDEF='$(CDEF)' ADEF='$(ADEF)' OBJ_DIR='$(OBJ_DIR)'\
    	 INCLUDE='-I$(PWD) -I$(PRJ_INC_DIR) -I$(UTIL_DIR)'

$(SHA_EXE):

$(RTSSL2_EXE):

$(RTSSL_EXE):

$(INVERSE):


package:
	rm -rf $(PACKAGE_DIR)
	rm -f $(TOP_DIR)/bootloader.tar
	mkdir $(PACKAGE_DIR)

	# copy binary to temp_package folder
	#cp -f  $(PRJ_CONFIG_TARGET) $(PACKAGE_PRJ_CONFIG)
	cp -f $(BOOTCODE_SYS_PARAM_TARGET) $(PACKAGE_SYS_CONFIG)
	cp -f  $(HW_SETTING_TARGET_INVERSE) $(PACKAGE_HWSETTING)
	cp -f  $(LINUX_RESCUE_HASH_TARGET) $(PACKAGE_LINUX_RESCUE)
	cd $(PACKAGE_DIR);tar -cvf $(TOP_DIR)/$(TARGET_NAME).tar  *
	cp -f $(TARGET_NAME).tar $(TOP_DIR)/bootloader.tar

%.o: %.c
	$(XCC) -c -o $(OBJ_DIR)/$*.o $(CFLAGS) $(EXTRACFLAGS) $< -I$(PRJ_INC_DIR) -I$(SHELL_PROD_DIR) -I$(UTIL_DIR)

%.o: %.cxx
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<

%.o: %.C
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<

%.o: %.cc
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<

%.o: %.cpp
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<

%.o: %.s
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<

%.o: %.S
	$(XCXX) -c -o $(OBJ_DIR)/$*.o $(CXXFLAGS) $(EXTRACXXFLAGS) $<
