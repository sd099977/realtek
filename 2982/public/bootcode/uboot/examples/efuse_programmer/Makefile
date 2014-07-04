#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

LOAD_ADDR = 0x01500000

# ********************************************************************
# Detect compiling environment.
# ********************************************************************
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

# ********************************************************************
# Directories specifics.
# ********************************************************************

PERL    = perl
RM      = rm -rf
CD      = cd
CAT     = cat
CP      = cp

TOP_DIR         = $(shell cd .; pwd)
INCLUDE_DIR     = $(TOP_DIR)/include

RSA_PUB_KEY_TARGET = $(TOP_DIR)/secure_key/rsa-public-key-inv-rev.bin
DCAS_RSA_PUB_KEY_TARGET = $(TOP_DIR)/secure_key/dcas-public-key-inv-rev.bin
ACPU_AES_KEY_TARGET = $(TOP_DIR)/secure_key/acpu-aes-key-rev.bin
SCPU_AES_KEY_TARGET = $(TOP_DIR)/secure_key/scpu-aes-key-rev.bin

BIN_ARGS = "rsa_pub_key="$(RSA_PUB_KEY_TARGET)
BIN_ARGS += "dcas_rsa_pub_key="$(DCAS_RSA_PUB_KEY_TARGET)
BIN_ARGS += "aes_key_acpu="$(ACPU_AES_KEY_TARGET)
BIN_ARGS += "aes_key_scpu="$(SCPU_AES_KEY_TARGET)

#TARGET_EXE = $(TOP_DIR)/efuse_programmer
#TARGET_BIN = $(TOP_DIR)/$(TARGET_NAME).bin
#TARGET_DIS = $(TOP_DIR)/$(TARGET_NAME).dis

#-------------------------------------------------
include $(TOPDIR)/config.mk

ELF-y        := efuse_programmer

#
# Some versions of make do not handle trailing white spaces properly;
# leading to build failures. The problem was found with GNU Make 3.80.
# Using 'strip' as a workaround for the problem.
#
ELF := $(strip $(ELF-y))

SREC := $(addsuffix .srec,$(ELF))
BIN  := $(addsuffix .bin,$(ELF))
DIS  := $(addsuffix .dis,$(ELF))

SOBJS	:= temp_target_array.o
SOBJS	+= start.o
COBJS	:= efusemain.o
COBJS	+= util.o
COBJS	+= strlen.o
COBJS	+= strstr.o
COBJS	+= strtoul.o
COBJS	+= ctype.o
COBJS	+= timer.o
LIB	= $(obj)

LIBCOBJS = 

LIBOBJS	= $(addprefix $(obj),$(LIBAOBJS) $(LIBCOBJS))

SRCS	:= $(COBJS:.o=.c) $(LIBCOBJS:.o=.c) $(LIBAOBJS:.o=.S) $(SOBJS:.o=.S)
OBJS	:= $(addprefix $(obj),$(COBJS))
SSOBJS	:= $(addprefix $(obj),$(SOBJS))

gcclibdir := $(shell dirname `$(CC) -print-libgcc-file-name`)

CPPFLAGS += -I.. -I$(INCLUDE_DIR) -I$(TOP_DIR)/include
INCDIRS =  -I$(TOP_DIR)/../../include -I.. -I$(INCLUDE_DIR) 

# For PowerPC there's no need to compile standalone applications as a
# relocatable executable.  The relocation data is not needed, and
# also causes the entry point of the standalone application to be
# inconsistent.
ifeq ($(ARCH),powerpc)
AFLAGS := $(filter-out $(RELFLAGS),$(AFLAGS))
CFLAGS := $(filter-out $(RELFLAGS),$(CFLAGS))
CPPFLAGS := $(filter-out $(RELFLAGS),$(CPPFLAGS))
endif

# We don't want gcc reordering functions if possible.  This ensures that an
# application's entry point will be the first function in the application's
# source file.
CFLAGS = -g -Os -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv7-a -D__EL__
CFLAGS += $(INCDIRS)
all:	clean b2a $(obj).depend $(OBJS) $(SSOBJS) $(LIB) $(ELF) $(SREC) $(BIN)

b2a:
	chmod +x ./bin2ascii
	./bin2ascii $(BIN_ARGS) > temp_target_array.h

clean:
	-rm -f $(ELF) *.o temp_target_array.h *.bin *.map *.dis *.srec
	
#########################################################################
$(LIB):	$(obj).depend $(LIBOBJS)
	$(call cmd_link_o_target, $(LIBOBJS))

$(ELF): 	$(LIB) 
		$(LD) $(LDFLAGS) -g -Ttext $(LOAD_ADDR) \
			-o $@ -e start $(SOBJS) $(COBJS) $(LIB) \
			-L$(gcclibdir) -lgcc -Map efuse_programmer.map

$(SREC):
$(obj)%.srec:	$(obj)%
		$(OBJCOPY) -O srec $< $@ 2>/dev/null

$(BIN):
$(obj)%.bin:	$(obj)%
		$(OBJCOPY) -O binary $< $@ 2>/dev/null
		$(OBJDUMP) -DS $<  >$(DIS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################

