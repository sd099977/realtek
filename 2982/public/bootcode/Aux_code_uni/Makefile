################################################################################
#                                                                              #
# compile option for different environment                                     #
#

DEFINE_OPTS = -DCONFIG_CHIP_SIRIUS

ifeq ($(origin env), command line)

ifeq ($(env), fpga)
	DEFINE_OPTS += -DENV_FPGA
	ROM_SYMBOL_POSFIX = fpga
else ifeq ($(env), sim)
	DEFINE_OPTS += -DENV_SIMULATION
	ROM_SYMBOL_POSFIX = sim
else
	DEFINE_OPTS += -DENV_REALCHIP
	ROM_SYMBOL_POSFIX = realchip
endif

endif

ifeq ($(origin env), undefined)
	DEFINE_OPTS += -DENV_REALCHIP
	ROM_SYMBOL_POSFIX = realchip
endif
#                                                                              #
#                                                                              #
################################################################################

PWD         = $(shell /bin/pwd)
SRC_DIR     = $(PWD)/src
OBJ_DIR     = $(PWD)/obj
SCRIPT_DIR  = $(PWD)/script
INCLUDE_DIR = $(PWD)/include
ARM_REDIRECT_DIR = $(PWD)/arm_redirect
HW_SETTING_DIR   = $(PWD)/hw_setting
MAKE_SCRIPT_DIR  = $(PWD)/tools/MakefileScripts
ALL_OBJ     = $(notdir $(wildcard $(OBJ_DIR)/*.o))

#SVN REV
SVN_REV        = $(shell svnversion -c ./ | awk -F":" '{ print $$2 }')

# Tool-chain used for compilation of target code.
BOOTCODE_ROOT := $(PWD)/..
TOOLCHAIN_PREFIX := rsdk-1.5.9
TOOLCHAIN_READY := $(wildcard ../tmp/$(TOOLCHAIN_PREFIX))
ifeq ($(strip $(TOOLCHAIN_READY)),)
   $(warning toolchain $(TOOLCHAIN_PREFIX) is not ready, installing...)
   $(shell mkdir -p ../tmp)
   $(shell tar xfj $(BOOTCODE_ROOT)/toolchain/$(TOOLCHAIN_PREFIX)-linux-newlib.tar.bz2 -C $(BOOTCODE_ROOT)/tmp)
endif

TOOLCHAIN_PATH = $(BOOTCODE_ROOT)/tmp/$(TOOLCHAIN_PREFIX)/linux/newlib/bin

GCC = $(TOOLCHAIN_PATH)/mips-elf-gcc
LD = $(TOOLCHAIN_PATH)/mips-elf-ld
OBJCOPY = $(TOOLCHAIN_PATH)/mips-elf-objcopy
OBJDUMP = $(TOOLCHAIN_PATH)/mips-elf-objdump
NM = $(TOOLCHAIN_PATH)/mips-elf-nm
#DBGINFO = -gdwarf-2 -Wa,--gdwarf2 -g
DBGINFO = -gdwarf-2
PERL = perl
CONVERT_SYMBOL = $(SCRIPT_DIR)/convert_symbol.pl

LINKER_SCRIPT = $(PWD)/link.ld

APP = Aux_code_uni
ELF_FILE = $(PWD)/$(APP).elf
MAP_FILE = $(PWD)/$(APP).map
BIN_FILE = $(PWD)/$(APP).bin
DIS_FILE = $(PWD)/$(APP).dis
NM_FILE = $(PWD)/$(APP).symbol
DUMP_FILE = $(PWD)/$(APP).txt
ifeq ($(origin env), undefined)
OUTPUT_IMG = $(PWD)/$(APP).img
else
OUTPUT_IMG = $(PWD)/$(APP)_$(env).img
endif
ARM_REDIRECT_IMG = $(ARM_REDIRECT_DIR)/arm_start.o
ARM_REDIRECT2_IMG = $(ARM_REDIRECT_DIR)/arm_start2.o
AUTOCONF_HW_SETTING_FILE = $(INCLUDE_DIR)/autoconf_hw_setting.h

# symbol file comes from ROM code
ROM_SYMBOL_FILE = $(SCRIPT_DIR)/reset-00.00.nm

# endian select
ENDIAN = EL
#ENDIAN = EB

# enable this to compile with 16-bit instruction
USE_MIPS16 = -mips16

BASICFLAGS = -march=4181 -G0 -O2 -nostdinc -save-temps -mno-abicalls -finhibit-lt -finhibit-st -fomit-frame-pointer -fno-common -fno-pic -I. -I$(INCLUDE_DIR) -c -$(ENDIAN) -Wall $(DBGINFO) $(DEFINE_OPTS)
AS = $(CYGWINPATH)$(GCC) $(BASICFLAGS) -x assembler-with-cpp
GCCFLAGS = -mno-gpopt -msoft-float
CC = $(CYGWINPATH)$(GCC) $(BASICFLAGS) $(GCCFLAGS) 
#LD_OPTS = -nostartfiles -nostdlib --oformat=elf32-tradlittlemips -T$(LINKER_SCRIPT) -Wl,-Map $(MAP_FILE) -$(ENDIAN) 
LD_OPTS = -nostartfiles -nostdlib --static -T$(LINKER_SCRIPT) -Map $(MAP_FILE) -$(ENDIAN) 
AFLAG       = $(BASICFLAGS)
CFLAG       = $(BASICFLAGS) $(USE_MIPS16)
CDEF        = -D$(ENDIAN)
ADEF        = $(CDEF) -D_ASSEMBLER_

$(ELF_FILE): clean src arm_redirect
	@touch $(MAP_FILE)
	cd $(OBJ_DIR); \
	$(CYGWINPATH)$(LD) $(LD_OPTS) $(ALL_OBJ) -o $(ELF_FILE)
	$(CYGWINPATH)$(OBJCOPY) -O binary $@ $(BIN_FILE)
	$(CYGWINPATH)$(OBJDUMP) -S -D $@ > $(DIS_FILE)
	$(CYGWINPATH)$(NM) $@ | sort $1 > $(NM_FILE)
	$(CYGWINPATH)$(OBJDUMP) -h $@ > $(DUMP_FILE)
	cp $(BIN_FILE) $(OUTPUT_IMG)
	@echo
	@echo "Output binary =====>" \"$(notdir $(OUTPUT_IMG))\"

.s.o:
	$(AS) -o $(OBJ_DIR)/$@ $<

.S.o:
	$(AS) -o $(OBJ_DIR)/$@ $<

.c.o:
	$(CC) -o $(OBJ_DIR)/$@ $<

#.PHONY: clean hw_setting src rom_symbol arm_redirect
.PHONY: clean src rom_symbol arm_redirect svn_ver
clean:
	rm -f $(ELF_FILE) $(DIS_FILE) $(MAP_FILE) $(BIN_FILE) $(NM_FILE) $(DUMP_FILE)
	rm -f *.o *.cdb *.img
	rm -f $(OBJ_DIR)/*.o
	rm -f $(SRC_DIR)/*.i $(SRC_DIR)/*.s
	rm -f $(MAKE_SCRIPT_DIR)/kconfig/mconf $(MAKE_SCRIPT_DIR)/kconfig/conf $(MAKE_SCRIPT_DIR)/kconfig/*.o
	rm -f $(MAKE_SCRIPT_DIR)/lxdialog/lxdialog $(MAKE_SCRIPT_DIR)/lxdialog/*.o
	rm -f $(INCLUDE_DIR)/svnver.h
	
svn_ver:
	$(shell echo "#define SVN_REV \"$(SVN_REV)\"" > $(INCLUDE_DIR)/svnver.h)	
	
hw_setting:
	cd $(HW_SETTING_DIR);\
	make mconf;\
	../tools/MakefileScripts/kconfig/mconf -a -c$(HW_SETTING).config -kKconfig -H$(AUTOCONF_HW_SETTING_FILE);\
	make

src: svn_ver
	cd $(SRC_DIR);\
	make CC=$(GCC) CFLAG='$(CFLAG)' AFLAG='$(AFLAG)' CDEF='$(CDEF)' ADEF='$(ADEF)' OBJ_DIR='$(OBJ_DIR)'\
    	 INCLUDE='-I$(PWD) -I. -I$(INCLUDE_DIR)'

rom_symbol: $(ROM_SYMBOL_FILE)
	$(PERL) $(CONVERT_SYMBOL) $(ROM_SYMBOL_FILE) > $(INCLUDE_DIR)/rom_symbol_$(ROM_SYMBOL_POSFIX).h

arm_redirect:
ifeq ($(env), sim)
	@echo "======================================================="
	@echo " skip ARM redirect images in simulation to reduce size "
	@echo "======================================================="
else
	$(CYGWINPATH)$(OBJCOPY) --add-section .arm_start_img=$(ARM_REDIRECT_IMG) $(OBJ_DIR)/empty.o
	$(CYGWINPATH)$(OBJCOPY) --add-section .arm_start2_img=$(ARM_REDIRECT2_IMG) $(OBJ_DIR)/empty.o
endif

