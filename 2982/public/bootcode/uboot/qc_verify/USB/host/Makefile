include $(TOPDIR)/config.mk

LIB	:= $(obj)lib_usbhc.o

COBJS-y       := rl6233.o


COBJS-$(CONFIG_BOOT_USB_OHCI) += usb_ohci.o
COBJS-$(CONFIG_BOOT_USB_EHCI) += usb_ehci.o
COBJS-$(CONFIG_BOOT_USB_XHCI) += usb_xhci.o


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

