# ********************************************************************
# Macro Specifics.
# ********************************************************************
# SRC_C	= $(wildcard *.c)
SRC_S	= $(wildcard *.S)
SRC		= $(SRC_C) $(SRC_S)

SRC_C  =	app_main.c otp_util.c sed_common.c sed_drv_sfc.c sed_r2r.c ctype.c printf.c sed_drv_gpio.c sed_drv_uart.c sed_rtk.c doprntx.c sed_cert.c sed_drv_pinmux.c sed_drv_wdog.c sed_setup.c memchr.c sed_drv_rng.c sed_otp.c strlen.c sed_drv_timer.c rtaes_rtk.c rtaes_testapp.c big_int.c big_util.c
#SRC_C  =	app_main.c otp_util.c sed_common.c sed_drv_sfc.c sed_r2r.c ctype.c printf.c sed_drv_gpio.c sed_drv_uart.c sed_rtk.c doprntx.c sed_cert.c sed_drv_pinmux.c sed_drv_wdog.c sed_setup.c memchr.c sed_drv_rng.c sed_otp.c strlen.c sed_drv_timer.c rtaes_rtk.c rtaes_testapp.c
#SRC_C  =	app_main.c otp_util.c sed_common.c sed_drv_sfc.c sed_r2r.c ctype.c printf.c sed_drv_gpio.c sed_drv_uart.c sed_rtk.c doprntx.c sed_cert.c sed_drv_pinmux.c sed_drv_wdog.c sed_setup.c memchr.c sed_drv_rng.c sed_otp.c strlen.c sed_drv_timer.c rtaes_rtk.c rtaes_testapp.c

#rtaes_rtk.c
#rtaes_testapp.c	\


SRC_C_RAW  = sed_char.c


OBJ_C  =  $(patsubst %.c, %.o, $(SRC_C))
OBJ_C_RAW  =  $(patsubst %.c, %.o, $(SRC_C_RAW))
OBJ_S	= $(patsubst %.S, %.o, $(SRC_S))
OBJ		= $(OBJ_C) $(OBJ_S)

# ********************************************************************
# Compile Directives.
# ********************************************************************
all: $(OBJ_C) $(OBJ_C_RAW) $(OBJ_S)

$(OBJ_C_RAW) : %.o : %.c
	$(CC) -c $(CFLAG) $(CDEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<

$(OBJ_C) : %.o : %.c
	$(CC) -c $(CFLAG) -O2 $(CDEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<

$(OBJ_S) : %.o : %.S
	$(CC) -c $(AFLAG) $(ADEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<
