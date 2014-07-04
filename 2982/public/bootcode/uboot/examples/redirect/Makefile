#########################################################################
# Path Setting
#########################################################################
#PRJ_ROOT=../../..
#RSDK=$(PRJ_ROOT)/tmp/asdk-4.8.2-a7-EL-3.7-0.9.33-a32nt-131122/bin

# object directories
OBJ_DIR=.

#########################################################################
# MPU specific arguments
#########################################################################
#GCCVER=$(RSDK)
#CC=$(GCCVER)/arm-linux-gcc
#LD=$(GCCVER)/arm-linux-ld
#NM=$(GCCVER)/arm-linux-nm
#AR=$(GCCVER)/arm-linux-ar
#OBJDUMP=$(RSDK)/arm-linux-objdump
#OBJCOPY=$(RSDK)/arm-linux-objcopy

GCC_INC_DIR := $(shell $(CC) -print-file-name=include)
GCC_LIB_DIR := $(shell $(CC) -print-libgcc-file-name)

ASM=$(CC)

INC_PATH = -I./include/ 

CFLAGS :=
CFLAGS += -gdwarf-2
CFLAGS += -Os
CFLAGS += -DUSE_GNU_GCC
CFLAGS += -fomit-frame-pointer
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -mlong-calls
CFLAGS += -nostdinc
CFLAGS += -I.

LDFLAGS :=
LDFLAGS += -EL -Bstatic
LDFLAGS += $(GCC_LIB_DIR)


LINK_SCR = link.ld


#########################################################################
# Sources
#########################################################################
C_SOURCE = 

# section name from link.lds
REDIRECT_SECTION_1 = .start
REDIRECT_SECTION_2 = .start2

# redirect code part1 and part2
REDIRECT_TARGET_1 = redirect_1.bin
REDIRECT_TARGET_2 = redirect_2.bin

ASM_SOURCE = start.S start2.S

#########################################################################
# Objects
#########################################################################
C_OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SOURCE))
ASM_OBJS := $(patsubst %.S,$(OBJ_DIR)/%.o,$(ASM_SOURCE))
APP_NAME := redirect

#########################################################################
# D flags
#########################################################################
DFLAGS =  

#########################################################################
# Rules
#########################################################################
.PHONY: all clean

all: $(APP_NAME).elf

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o: %.S
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.s
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@


$(APP_NAME).elf:$(ASM_OBJS) $(C_OBJS)
	$(LD) -Tlink.lds -o $(APP_NAME).elf $(C_OBJS) $(LDFLAGS) 
	$(OBJDUMP) -DS $(APP_NAME).elf > $(APP_NAME).text
	$(OBJCOPY) -O binary $(APP_NAME).elf  $(APP_NAME).bin
	$(OBJCOPY) -O binary -j $(REDIRECT_SECTION_1) $(APP_NAME).elf $(REDIRECT_TARGET_1)
	$(OBJCOPY) -O binary -j $(REDIRECT_SECTION_2) $(APP_NAME).elf $(REDIRECT_TARGET_2)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f *.elf
	rm -f *.map
	rm -f *.text
	rm -f *.bin

do_pack:
	perl packer.pl $(APP_NAME)
#########################################################################
# End
#########################################################################
#	$(LD) $^ -Tlink.lds $(LINK_SCR)  -o $(APP_NAME).elf $(LDFLAGS) -Map $(APP_NAME).map
#	$(LD) -Tlink.lds -o $(APP_NAME).elf $(C_OBJS) $(LDFLAGS) 
