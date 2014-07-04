# ********************************************************************
# Macro Specifics.
# ********************************************************************
# SRC_C	= $(wildcard *.c)
SRC_S	= $(wildcard *.S)
SRC		= $(SRC_C) $(SRC_S)

SRC_C  =  app_main.c \
		  big_int.c \
		  big_util.c \
		  ctype.c \
		  div64.c \
		  dlmalloc.c \
		  doprntx.c \
		  lzma_dec.c \
		  lzma_tools.c \
		  mcp.c \
		  mem.c \
		  otp_util.c \
		  printf.c \
		  sed_boot.c \
		  sed_cert.c \
		  sed_common.c \
		  sed_drv_gpio.c \
		  sed_drv_pinmux.c \
		  sed_drv_rng.c \
		  sed_drv_sfc.c \
		  sed_drv_timer.c \
		  sed_drv_uart.c \
		  sed_drv_wdog.c \
		  sed_drv_nand.c \
		  sed_rtk_nand.c \
		  sed_rtk_nand_base.c \
		  nand_crc32.c \
		  sed_otp.c \
		  sed_r2r.c \
		  sed_rtk.c \
		  sed_setup.c \
		  string.c \
		  util.c \
		  vsprintf.c

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
	$(CC) -c $(CFLAG) $(CDEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<

$(OBJ_S) : %.o : %.S
	$(CC) -c $(AFLAG) $(ADEF) $(INCLUDE) -o $(OBJ_DIR)/$@ $<
