#if defined(CHIP_VER_B)
#include "rom_symbol_realchip_b.h"
#elif defined(CHIP_VER_C)
#include "rom_symbol_realchip_c.h"
#else

#if defined(ENV_FPGA)
#include "rom_symbol_fpga.h"
#elif defined(ENV_SIMULATION)
#include "rom_symbol_sim.h"
#elif defined(ENV_REALCHIP)
#include "rom_symbol_realchip.h"
#endif

#endif

/* check if ROM code symbol contain SPI-NAND or NAND functions */
#if defined(ROM__T__spi_n_read_image)
#define ROM_SYMBOL_SPI_N
#endif

#if defined(ROM__T__nf_read_image)
#define ROM_SYMBOL_NAND
#endif

#if defined(ROM__T__mmc_blk_read)
#define ROM_SYMBOL_EMMC
#endif
