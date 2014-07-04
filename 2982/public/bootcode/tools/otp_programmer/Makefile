# Detect compiling environment.
# ********************************************************************
TOPDIR  := $(shell /bin/pwd)
BOOTCODE_ROOT := $(TOPDIR)/../../
TOOLCHAIN_PREFIX := asdk-4.8.3-a7-EL-3.7-0.9.33-a32nt-140428
TOOLCHAIN_READY := $(wildcard ../../tmp/$(TOOLCHAIN_PREFIX))
ifeq ($(strip $(TOOLCHAIN_READY)),)
   $(warning toolchain $(TOOLCHAIN_PREFIX) is not ready, installing...)
   $(shell mkdir -p ../../tmp)
   $(shell tar xfj $(BOOTCODE_ROOT)/toolchain/$(TOOLCHAIN_PREFIX).tar.bz2 -C $(BOOTCODE_ROOT)/tmp)
endif

# Tool-chain used for compilation of target code.
TOOLCHAIN_PATH = $(BOOTCODE_ROOT)/tmp/$(TOOLCHAIN_PREFIX)/bin

GCC       = $(TOOLCHAIN_PATH)/asdk-linux-gcc
LD        = $(TOOLCHAIN_PATH)/asdk-linux-ld
OBJCOPY   = $(TOOLCHAIN_PATH)/asdk-linux-objcopy
OBJDUMP   = $(TOOLCHAIN_PATH)/asdk-linux-objdump

#use ARM_A7 for programming
CFLAGS        = -g -fno-common -ffixed-r8 -msoft-float \
				-fno-builtin -ffreestanding -nostdinc -pipe -marm \
				-mno-thumb-interwork -mabi=aapcs-linux -march=armv7-a -mno-unaligned-access
CXXFLAGS      = $(CFLAGS) -Wa,--gdwarf2
EXTRACFLAGS   = -Wall
EXTRACXXFLAGS = $(EXTRACFLAGS) -fno-exceptions 
LDFLAGS       = -nostartfiles -I../include -EL
LD_SCRIPT     = -T $(PWD)/link.ld 

CFLAG       = $(CFLAGS)
AFLAG       = $(CXXFLAGS) 
CDEF        = $(EXTRACFLAGS) -DEL
ADEF        = $(EXTRACXXFLAGS) -D_ASSEMBLER_



SRC_DIR = $(PWD)/src
OBJ_DIR	 = $(PWD)/obj
INCLUDE_DIR = $(PWD)/include
ALL_OBJ = $(notdir $(wildcard $(OBJ_DIR)/*.o))

#GCC = sde-gcc
#OBJCOPY = sde-objcopy
#OBJDUMP = sde-objdump
#DBGINFO = -gdwarf-2 -Wa,--gdwarf2 -g
#DBGINFO = -gdwarf-2

#LINKER_SCRIPT = $(PWD)/link.ld

APP = program_rtd298x_otp
ELF_FILE = $(PWD)/$(APP).elf
MAP_FILE = $(PWD)/$(APP).map
BIN_FILE = $(PWD)/$(APP).bin
DIS_FILE = $(PWD)/$(APP).dis

#BASICFLAGS = -mips32 -G0 -O0 -nostdinc -I. -I$(INCLUDE_DIR) -c -EL -Wall $(DBGINFO) 
#AS = $(CYGWINPATH)$(GCC) $(BASICFLAGS) -x assembler-with-cpp
#GCCFLAGS = -mno-gpopt -msoft-float
#CC = $(CYGWINPATH)$(GCC) $(BASICFLAGS) $(GCCFLAGS)
#LD = $(CYGWINPATH)$(GCC) -nostartfiles -nostdlib -T$(LINKER_SCRIPT) -Wl,-Map $(MAP_FILE) -EL
#AFLAG       = $(BASICFLAGS) -no-traditional-cpp
#CDEF        = -DEL
#ADEF        = $(CDEF) -D_ASSEMBLER_

BUILTIN_OTP_MAP_TARGET=$(PWD)/otp_map.bin
BIN_ARGS = "builtin_otp_map="$(BUILTIN_OTP_MAP_TARGET)

$(ELF_FILE): clean b2a src
	@touch $(MAP_FILE)
#	$(LD) $? -o $@
	cd $(OBJ_DIR); \
	$(LD) $(LDFLAGS) -e _ram_boot -o $(ELF_FILE) $(ALL_OBJ) \
	$(LD_SCRIPT) -Map $(MAP_FILE)	
	$(OBJCOPY) -O binary $@ $(BIN_FILE)
	$(OBJDUMP) -S --disassemble-all $@ > $(DIS_FILE)
	@echo
	@echo "Binary generated =====>" \"$(notdir $(BIN_FILE))\"

.s.o:
	$(AS) -o $(OBJ_DIR)/$@ $<

.S.o:
	$(AS) -o $(OBJ_DIR)/$@ $<

.c.o:
	$(CC) -o $(OBJ_DIR)/$@ $<
	
.PHONY: clean src b2a
clean:
	rm -f $(ELF_FILE) $(DIS_FILE) $(MAP_FILE) $(BIN_FILE)
	rm -f *.o
	rm -f *.cdb
	rm -f *.rc
	rm -f $(OBJ_DIR)/*.o  $(SRC_DIR)/temp_target_array.S

src:
	cd $(SRC_DIR);\
	make CC=$(GCC) CFLAG='$(CFLAG)' AFLAG='$(AFLAG)' CDEF='$(CDEF)' ADEF='$(ADEF)' OBJ_DIR='$(OBJ_DIR)'\
    	 INCLUDE='-I$(PWD) -I. -I$(INCLUDE_DIR)'
		 
b2a:
	chmod +x ./bin2ascii
	./bin2ascii $(BIN_ARGS) > $(SRC_DIR)/temp_target_array.S
		 
