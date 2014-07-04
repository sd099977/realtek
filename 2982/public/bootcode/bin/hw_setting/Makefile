-include .config
include rtd298x_hw_setting.makefile

AUTOCONF_HW_SETTING_DIR  = .
AUTOCONF_HW_SETTING_NAME = autoconf_hw_setting.h
AUTOCONF_HW_SETTING_FILE = $(AUTOCONF_HW_SETTING_DIR)/$(AUTOCONF_HW_SETTING_NAME)


HW_SETTING_MAKER_DIR = ../../tools/hw_setting_maker
HW_SETTING_MAKER_AP = $(HW_SETTING_MAKER_DIR)/generate_config

.PHONY: clean build_config syntax_check hw_setting menuconfig mconf

all : hw_setting

mconf:
	$(MAKE) -C ./tools/MakefileScripts/kconfig/
	$(MAKE) -C ./tools/MakefileScripts/lxdialog/

menuconfig: mconf
	./tools/MakefileScripts/kconfig/mconf -kKconfig -C.config -H$(AUTOCONF_HW_SETTING_FILE)

build_config: clean mconf
	@test -s $(HW_CONFIG).config || { echo "$(HW_CONFIG).config does not exist! Exiting..."; exit 1; }
	./tools/MakefileScripts/kconfig/mconf -a -c$(HW_CONFIG).config -kKconfig -H$(AUTOCONF_HW_SETTING_FILE);	
	
$(HW_SETTING_MAKER_AP):
	cd $(HW_SETTING_MAKER_DIR);\
	make;


AUTOCONF_HW_SETTING_READY := $(strip $(wildcard $(AUTOCONF_HW_SETTING_FILE)))
#AUTOCONF_HW_SETTING_READY := $(wildcard $(AUTOCONF_HW_SETTING_FILE))
#ifeq ($(strip $(AUTOCONF_HW_SETTING_READY)),)
AUTOCONF_HW_SETTING = y
ifdef $(AUTOCONF_HW_SETTING_READY)
#$(shell exit 1;)
endif


hw_setting: syntax_check $(HW_SETTING_MAKER_AP)
	@echo "#define rtd_outl(a,b) w a,b" >head.config;
	@echo "#define rtd_maskl(a,b,c) m a,b,c" >>head.config;
	@echo "#define rtd_inl(a) " >>head.config;
	@echo "#define ScalerTimer_DelayXms(a) n a " >>head.config;
	cat head.config $(AUTOCONF_HW_SETTING_FILE) $(HW_SETTING_FILE) >hw_setting.c ;\
	cat $(AUTOCONF_HW_SETTING_FILE) $(HW_SETTING_FILE) >hw_setting.config.c ;\
    gcc -E hw_setting.c |grep -v "^#" |sed -n 's/;$$//p' >hw_setting.config; \
    gcc -E hw_setting.config.c |grep -v "^#" |sed -n 's/;$$//p' >hw_setting.tbl; \
    ./$(HW_SETTING_MAKER_AP) hw_setting.config hw_setting.bin
	@rm -f *.c *.o tmp.head tmp.tail head.config

clean :
	@echo "make clean"
	@rm -f hw_setting.config hw_setting.config.tmp hw_setting.bin
	@rm -f *.c *.o tmp.head tmp.tail head.config $(AUTOCONF_HW_SETTING_FILE)

syntax_check :
	@echo $(AUTOCONF_HW_SETTING_READY)
ifndef AUTOCONF_HW_SETTING_READY
	@echo "autoconf_hw_setting.h does not exist, please make menuconfig ...";
	@exit 1;
endif	
	@echo "config syntax check"
	@echo $(HW_SETTING_FILE)
	@set -e; \
	for d in $(HW_SETTING_FILE);    \
	do \
	echo "int rtd_outl(unsigned int,unsigned int);" >tmp.head; \
	echo "int rtd_maskl(unsigned int,unsigned int,unsigned int);" >>tmp.head; \
	echo "int rtd_inl(unsigned int);" >>tmp.head; \
	echo "int ScalerTimer_DelayXms(unsigned int);" >>tmp.head; \
	echo "void func(void) {" >>tmp.head; \
	echo "}" >tmp.tail; \
	cat tmp.head $$d tmp.tail >$$d.c;        \
	gcc -c $$d.c -Wall -Werror ;\
	done


