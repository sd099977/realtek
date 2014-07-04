# ===========================================================================
# Kernel configuration targets
# These targets are used from top-level makefile

# mconf:  Used for the mconfig target.
#         Utilizes the lxdialog package
# object files used by all kconfig flavours
export CC := gcc
export CFLAGS := -Wall -Wstrict-prototypes -g -fomit-frame-pointer 

hostprogs-y	:= conf mconf
conf-objs	:= mconf.o  zconf.tab.o
mconf-objs	:= mconf.o zconf.tab.o

clean-files	:= conf.o zconf.tab.o mconf.o conf mconf

always: $(mconf-objs) $(conf-objs) $(hostprogs-y) 

conf: $(conf-objs)
	$(CC) -o $@ $^

mconf: $(mconf-objs)
	$(CC) -o $@ $^

clean:
	rm -f $(clean-files)

%.o:%.c
	$(CC) -c $< $(CFLAGS) -o $@
