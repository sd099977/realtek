
RM = rm -f

#TOPDIR  := $(shell /bin/pwd)
#ROMCODE_ROOT := $(TOPDIR)/../../../

#TOOLCHAIN_PATH = $(ROMCODE_ROOT)/tmp/rsdk-1.5.9/linux/newlib/bin

#CC        = $(TOOLCHAIN_PATH)/mips-elf-gcc
CC        = mips-elf-gcc
#LD        = $(TOOLCHAIN_PATH)/mips-elf-ld
#OBJCOPY   = $(TOOLCHAIN_PATH)/mips-elf-objcopy
#OBJDUMP   = $(TOOLCHAIN_PATH)/mips-elf-objdump


ASSEMBLY = pad_header.S
# Options to objdump
OBJDUMP_OPTS = -S --disassemble-all
TARGET = pad_header.o

#OPTION += -static

all: $(TARGET)

$(TARGET) : $(ASSEMBLY)
	$(CC) -c $(ASSEMBLY)


.PHONY: clean
clean:
	$(RM) *.o


