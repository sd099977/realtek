#ifndef _DDR_ADDR_

//#define TEST_ON_SRAM
#ifdef TEST_ON_SRAM
#define DRAM_BASE   0x90010400
#define DRAM_SIZE   0x00000800
#define TEST_BLOCK  0x00000400
#define SRAM_BASE   0x90010000
#else
#define DRAM_BASE   0x00040000
#define DRAM_SIZE   0x00400000
#define TEST_BLOCK  0x00000400
#define SRAM_BASE   0x00018000
#endif 
#endif //_DDR_ADDR_

