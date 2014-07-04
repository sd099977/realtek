#
# Makefile
#


.PHONY: all clean purge


#-----------------------------------------------------------
# Mandatory variable check
#-----------------------------------------------------------


NHT_CC              ?= gcc -g -c -Wno-unused-parameter
NHT_CFLAGS          ?=
NHT_AR              ?= ar
NHT_ARFLAGS         ?= rcs

BUILD_DIR           ?= ./build
DISTRIB_DIR         ?= ./distrib

NHT_LIB_TARGET_NAME ?= libcsdserver.a
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
