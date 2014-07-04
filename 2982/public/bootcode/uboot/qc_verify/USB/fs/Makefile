include $(TOPDIR)/config.mk

LIB	:= $(obj)lib_fs.o
COBJS-y       := fat/fat.o
COBJS-y		  += fat/fat_write.o
COBJS-y       += fat/file.o
COBJS-y       += disk/part_dos.o
COBJS-y       += disk/part.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################

