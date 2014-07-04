#include $(TOPDIR)/.config

#O_TARGET := libfs.a

#obj-y := fat/fat.o fat/file.o disk/part.o disk/part_dos.o

#include ../../bin/Rules.make

# ********************************************************************
# Macro Specifics.
# ********************************************************************
SRC_C = $(wildcard *.c)
OBJ_C = $(patsubst %.c, %.o, $(SRC_C))
#SRC_C = fat/fat.c fat/file.c disk/part.c disk/part_dos.c
#OBJ_C = fat.o file.o part.o part_dos.o

# ********************************************************************
# Compile Directives.
# ********************************************************************

CFLAGS += -DCONFIG_USB_PATCH -DCONFIG_DOS_PARTITION

all: $(OBJ_C)
	@ echo $(OBJ_C) $(SRC_C)

$(OBJ_C) : %.o : %.c 
	$(CC) -c $(CFLAG) $(CFLAGS) $(CDEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<
