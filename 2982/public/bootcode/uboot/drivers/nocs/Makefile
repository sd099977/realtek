#
# (C) Copyright 2006
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

# CONFIG_RTK_MMC was defined in default config

include $(TOPDIR)/config.mk

LIB	:= $(obj)libnocs.o

COBJS-$(CONFIG_NOCS_BSD) += print_rpc.o
COBJS-$(CONFIG_NOCS_BSD) += mcp_buff.o
COBJS-$(CONFIG_NOCS_BSD) += sha256.o
COBJS-$(CONFIG_NOCS_BSD) += mcp_dgst.o
COBJS-$(CONFIG_NOCS_BSD) += mcp.o
COBJS-$(CONFIG_NOCS_BSD) += otp_util.o
COBJS-$(CONFIG_NOCS_BSD) += bsd_crc32.o
COBJS-$(CONFIG_NOCS_BSD) += ca_cert.o
COBJS-$(CONFIG_NOCS_BSD) += nocs_bsd.o


COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)
$(LIB): $(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
