#
# Makefile
#


.PHONY: all clean purge


#-----------------------------------------------------------
# Mandatory variable check
#-----------------------------------------------------------
#TOOLCHAIN_VER	:= asdk-4.8.2-a7-EL-3.7-0.9.33-a32nt-131122
TOOLCHAIN_VER   := asdk-4.8.3-a7-EL-3.7-0.9.33-a32nt-140428
//BOOTCODE_DIR	:= /home/alexkh/nfs/kernel/sirius/bootcode_NOCS
BOOTCODE_DIR	:= ../../../../../../../../../../../
TOOLHAIN_DIR	:= $(BOOTCODE_DIR)/tmp/$(TOOLCHAIN_VER)/bin
NOCS_DIR		:= $(BOOTCODE_DIR)/uboot/drivers/nocs
RPC_TOP_DIR		:= $(NOCS_DIR)/rpc
BSD_EAPI_DIR	:= $(RPC_TOP_DIR)/chipset/EAPI

RTK_CC	:= asdk-linux-gcc
RTK_AR	:= asdk-linux-ar


NHT_CC              := $(TOOLHAIN_DIR)/$(RTK_CC)
NHT_CFLAGS          := -fPIC -g -c -fno-common -ffixed-r8 -msoft-float  \
                       -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x00020000 \
                       -DLITTLE_ENDIAN  -fno-builtin -ffreestanding \
                       -marm -mno-thumb-interwork -mabi=aapcs-linux -march=armv7-a \
                       -mno-unaligned-access  \
					   -I $(NOCS_DIR)/ \
					   -I $(BSD_EAPI_DIR)/NOCS/EBSD/TAGS/3.0.1/distrib/inc/ \
					   -I $(BSD_EAPI_DIR)/nht_term/TAGS/1.2.0/distrib/inc/
NHT_AR              :=$(TOOLHAIN_DIR)/$(RTK_AR)
NHT_ARFLAGS         ?= rcs

BUILD_DIR           ?= ./build
DISTRIB_DIR         ?= ./distrib

NHT_LIB_TARGET_NAME ?= libbsdserver.a
NHT_LIB_TARGET      ?= $(DISTRIB_DIR)/$(NHT_LIB_TARGET_NAME)


#------------------------------------------------------------
# Include distribution resources
#------------------------------------------------------------

include ./BuildTools/distrib.imk
include ./BuildTools/incs.imk
include ./BuildTools/srcs.imk
include ./BuildTools/rules.imk


#------------------------------------------------------------
# Set 'NHT component version' compiler option
#------------------------------------------------------------

ifeq ($(strip $(NHT_COMPONENT_VERSION_STR)),)
  NHT_CFLAG_VERSION_STR :=
else
  NHT_CFLAG_VERSION_STR := -DNHT_COMPONENT_VERSION_STR="$(subst ",\",$(subst \,\\,$(NHT_COMPONENT_VERSION_STR)))"
endif


#------------------------------------------------------------
# Setup distrib obj files
#------------------------------------------------------------

NHT_LIB_OBJ_FILES = $(call NHT_CC_Get_objs, $(NHT_SRCS))


#------------------------------------------------------------
# Build compilation include files
#------------------------------------------------------------

NHT_COMPILER_INCS = $(addprefix -I, $(NHT_CC_INC_DIRS))


#------------------------------------------------------------
# compilation function
#------------------------------------------------------------

compile = $(NHT_CC) $(NHT_CFLAGS) $(NHT_COMPILER_INCS) $(NHT_CFLAG_VERSION_STR) -o  $2 $1


#------------------------------------------------------------
# Target Rules
#------------------------------------------------------------

$(BUILD_DIR) $(DISTRIB_DIR):
	-@if [ ! -d $@ ]; then mkdir -p $@; fi

$(NHT_LIB_TARGET) : $(NHT_LIB_OBJ_FILES)
	$(NHT_AR) $(NHT_ARFLAGS) $@ $(NHT_LIB_OBJ_FILES)


#------------------------------------------------------------
# Phony Rules
#------------------------------------------------------------

clean:
	-rm -rf $(BUILD_DIR)

purge : clean
	-rm $(NHT_LIB_TARGET)

all: $(BUILD_DIR) $(DISTRIB_DIR) $(NHT_LIB_TARGET)
