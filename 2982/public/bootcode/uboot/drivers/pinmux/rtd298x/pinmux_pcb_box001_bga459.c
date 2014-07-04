#include <common.h>
#include <asm/io.h>
#include <platform_lib/board/pcb.h>

#if 1
	#define DEBUG_PRINT(fmt,args...)
#else
	#define DEBUG_PRINT(fmt,args...)	 printf(fmt,## args);
#endif

void PinMuxInit(void) {
// TODO: Fix Me
printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

//bb_aiol_GPI_EN [3] bb_aior_GPI_EN [2]
rtd_maskl(0xB80008F4, ~0xC, (1<<3)|(1<<2));

// PAD_NAME: VDAC_IDACO_TV_APAD 0
rtd_maskl(0xB80008EC, 0xFFC1FFFF, (((RTD18X5_BGA459_PIN_W3 << 4)) << 13));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AI2L_APAD 1
rtd_maskl(0xB80008F0, 0x07FFFFFF, (((RTD18X5_BGA459_PIN_Y3 << 4)) << 23));
if (RTD18X5_BGA459_PIN_Y3 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x4&0x7)<<17)); }; // 11: P_RXER_SRC4,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y3 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x4&0x7)<<18)); }; // 10: P_COL_SRC4,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y3 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x0&0xf)<<23)); }; // 6: CR_SD_WP_SRC0,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AI2R_APAD 2
rtd_maskl(0xB80008F0, 0xF83FFFFF, (((RTD18X5_BGA459_PIN_AA1 << 4)) << 18));
if (RTD18X5_BGA459_PIN_AA1 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x4&0x7)<<11)); }; // 11: P_RXDV_SRC4,<I>,<HS>
if (RTD18X5_BGA459_PIN_AA1 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x5&0x7)<<20)); }; // 8: uart1_rXdi_src5,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AI3L_APAD 3
rtd_maskl(0xB80008F0, 0xFFC1FFFF, (((RTD18X5_BGA459_PIN_AA2 << 4)) << 13));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AI3R_APAD 4
rtd_maskl(0xB80008F0, 0xFFFE0FFF, (((RTD18X5_BGA459_PIN_AA3 << 4)) << 8));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AIO1L_APAD 5
rtd_maskl(0xB80008F4, 0xF83FFFFF, (((RTD18X5_BGA459_PIN_AD1 << 4)) << 18));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_AIO1R_APAD 6
rtd_maskl(0xB80008F4, 0xFFC1FFFF, (((RTD18X5_BGA459_PIN_AD2 << 4)) << 13));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_HPOL_APAD:2 7
rtd_maskl(0xB80008F4, 0xFFFE0FFF, (((RTD18X5_BGA459_PIN_AE2 << 4)) << 8));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_HPOR_APAD:2 8
rtd_maskl(0xB80008F4, 0xFFFFF07F, (((RTD18X5_BGA459_PIN_AE1 << 4)) << 3));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: BB_DIO3_APAD 9
rtd_maskl(0xB80008F8, 0xFFC1FFFF, (((RTD18X5_BGA459_PIN_AB4 << 4)) << 13));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_0_io 10
rtd_maskl(0xB8000800, 0x07FFFFFF, (((RTD18X5_BGA459_PIN_AE4 << 4)) << 23));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_1_io 11
rtd_maskl(0xB8000800, 0xFF83FFFF, (((RTD18X5_BGA459_PIN_AB10 << 4)) << 14));
if (RTD18X5_BGA459_PIN_AB10 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // 16: TP0_Data_bit4_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB10 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SCL_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_AB10 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SCL_SRC7,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_2_io 12
rtd_maskl(0xB8000804, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AB9 << 4) | (RTD18X5_BGA459_PIN_AB9_UP << 3) | (RTD18X5_BGA459_PIN_AB9_PD << 2) |(RTD18X5_BGA459_PIN_AB9_DS << 1) | (RTD18X5_BGA459_PIN_AB9_SR)) << 23));
if (RTD18X5_BGA459_PIN_AB9 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<23), ((0x2&0x3)<<23)); }; // 16: TP0_Data_bit3_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB9 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SDA_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_AB9 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SDA_SRC7,<I/O>
// PAD_NAME: pad_gpio_16_io 13
rtd_maskl(0xB8000814, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_Y14 << 4) | (RTD18X5_BGA459_PIN_Y14_UP << 3) | (RTD18X5_BGA459_PIN_Y14_PD << 2) |(RTD18X5_BGA459_PIN_Y14_DS << 1) | (RTD18X5_BGA459_PIN_Y14_SR)) << 5));
if (RTD18X5_BGA459_PIN_Y14 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x3&0x7)<<13)); }; // 15:
if (RTD18X5_BGA459_PIN_Y14 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2
if (RTD18X5_BGA459_PIN_Y14 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x1&0x3)<<11)); }; // 2: EMMC_Data_bit7_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_Y14 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 1: TP0_Data_bit0_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y14 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<24), ((0x1&0x1)<<24)); }; // 0: TP2_Data_bit0_SRC1,<I>,<HS>
// PAD_NAME: pad_gpio_17_io 14
rtd_maskl(0xB8000818, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD13 << 4) | (RTD18X5_BGA459_PIN_AD13_UP << 3) | (RTD18X5_BGA459_PIN_AD13_PD << 2) |(RTD18X5_BGA459_PIN_AD13_DS << 1) | (RTD18X5_BGA459_PIN_AD13_SR)) << 23));
if (RTD18X5_BGA459_PIN_AD13 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x3&0x7)<<9)); }; // 15: VBY1_
if (RTD18X5_BGA459_PIN_AD13 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x9&0xf)<<5)); }; // 8: SC1_DATA0_SRC9,<I/O>
if (RTD18X5_BGA459_PIN_AD13 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x5&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src5,<I/O>
if (RTD18X5_BGA459_PIN_AD13 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x1&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AD13 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<9), ((0x0&0x3)<<9)); }; // 1: TP0_SYNC_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_AD13 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<28), ((0x1&0x1)<<28)); }; // 0: TP2_SYNC_SRC1,<I>,<HS>
// PAD_NAME: pad_gpio_18_io 15
rtd_maskl(0xB8000818, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AE13 << 4) | (RTD18X5_BGA459_PIN_AE13_UP << 3) | (RTD18X5_BGA459_PIN_AE13_PD << 2) |(RTD18X5_BGA459_PIN_AE13_DS << 1) | (RTD18X5_BGA459_PIN_AE13_SR)) << 14));
if (RTD18X5_BGA459_PIN_AE13 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<10), ((0x2&0x3)<<10)); }; // 16:
if (RTD18X5_BGA459_PIN_AE13 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2_SDA_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_AE13 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x5&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_AE13 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x1&0x3)<<15)); }; // 2: EMMC_Data_bit5_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AE13 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 1: TP0_VAL_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_AE13 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<26), ((0x1&0x1)<<26)); }; // 0: TP2_VAL_SRC1,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_19_io 16
rtd_maskl(0xB8000818, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AD14 << 4) | (RTD18X5_BGA459_PIN_AD14_UP << 3) | (RTD18X5_BGA459_PIN_AD14_PD << 2) |(RTD18X5_BGA459_PIN_AD14_DS << 1) | (RTD18X5_BGA459_PIN_AD14_SR)) << 5));
if (RTD18X5_BGA459_PIN_AD14 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xb&0xf)<<10)); }; // 8: SC1_CD_SRC11,<I>
if (RTD18X5_BGA459_PIN_AD14 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AD14 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 1: TP0_CLK_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_AD14 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<30), ((0x1&0x1)<<30)); }; // 0: TP2_CLK_SRC1,<I>,<HS>
// PAD_NAME: pad_gpio_39_io 17
rtd_maskl(0xB8000830, 0x007FFFFF, (((RTD18X5_BGA459_PIN_Y19 << 4) | (RTD18X5_BGA459_PIN_Y19_UP << 3) | (RTD18X5_BGA459_PIN_Y19_PD << 2) |(RTD18X5_BGA459_PIN_Y19_DS << 1) | (RTD18X5_BGA459_PIN_Y19_SR)) << 23));
if (RTD18X5_BGA459_PIN_Y19 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 15: GSPI
// PAD_NAME: pad_gpio_40_io 18
rtd_maskl(0xB8000830, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AB19 << 4) | (RTD18X5_BGA459_PIN_AB19_UP << 3) | (RTD18X5_BGA459_PIN_AB19_PD << 2) |(RTD18X5_BGA459_PIN_AB19_DS << 1) | (RTD18X5_BGA459_PIN_AB19_SR)) << 14));
if (RTD18X5_BGA459_PIN_AB19 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x0&0x7)<<12)); }; // 15: GSPI_DI_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_AB19 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x0&0x7)<<25)); }; // 14: EPI_LOCK_src0,<I>
if (RTD18X5_BGA459_PIN_AB19 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<22), ((0x2&0x3)<<22)); }; // 10: P_TXC_SRC2,<I>,<HS>
// PAD_NAME: pad_gpio_41_io 19
rtd_maskl(0xB8000830, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AE20 << 4) | (RTD18X5_BGA459_PIN_AE20_UP << 3) | (RTD18X5_BGA459_PIN_AE20_PD << 2) |(RTD18X5_BGA459_PIN_AE20_DS << 1) | (RTD18X5_BGA459_PIN_AE20_SR)) << 5));
if (RTD18X5_BGA459_PIN_AE20 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x0&0x7)<<8)); }; // 15:
if (RTD18X5_BGA459_PIN_AE20 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x9&0xf)<<10)); }; // 14: SC1_C
// PAD_NAME: pad_gpio_42_io 20
rtd_maskl(0xB8000834, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AA19 << 4) | (RTD18X5_BGA459_PIN_AA19_UP << 3) | (RTD18X5_BGA459_PIN_AA19_PD << 2) |(RTD18X5_BGA459_PIN_AA19_DS << 1) | (RTD18X5_BGA459_PIN_AA19_SR)) << 23));
if (RTD18X5_BGA459_PIN_AA19 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 15: GSPI_DO_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AA19 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<25), ((0x2&0x3)<<25)); }; // 10: P_RXC_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AA19 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x4&0xf)<<5)); }; // 8: SC1_DATA0_SRC4,<I/O>
if (RTD18X5_BGA459_PIN_AA19 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x3&0x7)<<24)); }; // 7: SC0_DATA0_SRC3,<I/O>
// PAD_NAME: pad_gpio_35_io 21
rtd_maskl(0xB8000828, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AC13 << 4) | (RTD18X5_BGA459_PIN_AC13_UP << 3) | (RTD18X5_BGA459_PIN_AC13_PD << 2) |(RTD18X5_BGA459_PIN_AC13_DS << 1) | (RTD18X5_BGA459_PIN_AC13_SR)) << 5));
// PAD_NAME: pad_gpio_44_io 22
rtd_maskl(0xB8000834, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AC14 << 4) | (RTD18X5_BGA459_PIN_AC14_UP << 3) | (RTD18X5_BGA459_PIN_AC14_PD << 2) |(RTD18X5_BGA459_PIN_AC14_DS << 1) | (RTD18X5_BGA459_PIN_AC14_SR)) << 5));
if (RTD18X5_BGA459_PIN_AC14 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<26), ((0x0&0x3)<<26)); }; // 2: EMMC_Data_bit0_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_45_io 23
rtd_maskl(0xB8000838, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AC12 << 4) | (RTD18X5_BGA459_PIN_AC12_UP << 3) | (RTD18X5_BGA459_PIN_AC12_PD << 2) |(RTD18X5_BGA459_PIN_AC12_DS << 1) | (RTD18X5_BGA459_PIN_AC12_SR)) << 23));
if (RTD18X5_BGA459_PIN_AC12 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<24), ((0x0&0x3)<<24)); }; // 2: EMMC_Data_bit1_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_46_io 24
rtd_maskl(0xB8000838, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AE16 << 4) | (RTD18X5_BGA459_PIN_AE16_UP << 3) | (RTD18X5_BGA459_PIN_AE16_PD << 2) |(RTD18X5_BGA459_PIN_AE16_DS << 1) | (RTD18X5_BGA459_PIN_AE16_SR)) << 14));
if (RTD18X5_BGA459_PIN_AE16 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<22), ((0x0&0x3)<<22)); }; // 2: EMMC_Data_bit2_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_47_io 25
rtd_maskl(0xB8000838, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AD17 << 4) | (RTD18X5_BGA459_PIN_AD17_UP << 3) | (RTD18X5_BGA459_PIN_AD17_PD << 2) |(RTD18X5_BGA459_PIN_AD17_DS << 1) | (RTD18X5_BGA459_PIN_AD17_SR)) << 5));
if (RTD18X5_BGA459_PIN_AD17 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<20), ((0x0&0x3)<<20)); }; // 2: EMMC_Data_bit3_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_48_io 26
rtd_maskl(0xB800083C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AE17 << 4) | (RTD18X5_BGA459_PIN_AE17_UP << 3) | (RTD18X5_BGA459_PIN_AE17_PD << 2) |(RTD18X5_BGA459_PIN_AE17_DS << 1) | (RTD18X5_BGA459_PIN_AE17_SR)) << 23));
if (RTD18X5_BGA459_PIN_AE17 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_49_io 27
rtd_maskl(0xB800083C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AC16 << 4) | (RTD18X5_BGA459_PIN_AC16_UP << 3) | (RTD18X5_BGA459_PIN_AC16_PD << 2) |(RTD18X5_BGA459_PIN_AC16_DS << 1) | (RTD18X5_BGA459_PIN_AC16_SR)) << 14));
if (RTD18X5_BGA459_PIN_AC16 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x0&0x3)<<15)); }; // 2: EMMC_Data_bit5_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_50_io 28
rtd_maskl(0xB800083C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AC18 << 4) | (RTD18X5_BGA459_PIN_AC18_UP << 3) | (RTD18X5_BGA459_PIN_AC18_PD << 2) |(RTD18X5_BGA459_PIN_AC18_DS << 1) | (RTD18X5_BGA459_PIN_AC18_SR)) << 5));
if (RTD18X5_BGA459_PIN_AC18 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x6&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src6,<I/O>
if (RTD18X5_BGA459_PIN_AC18 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x6&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src6,<I/O>
if (RTD18X5_BGA459_PIN_AC18 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_51_io 29
rtd_maskl(0xB8000840, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD18 << 4) | (RTD18X5_BGA459_PIN_AD18_UP << 3) | (RTD18X5_BGA459_PIN_AD18_PD << 2) |(RTD18X5_BGA459_PIN_AD18_DS << 1) | (RTD18X5_BGA459_PIN_AD18_SR)) << 23));
if (RTD18X5_BGA459_PIN_AD18 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x6&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC6,<I/O>
if (RTD18X5_BGA459_PIN_AD18 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x6&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC6,<I/O>
if (RTD18X5_BGA459_PIN_AD18 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 2: EMMC_Data_bit7_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_52_io 30
rtd_maskl(0xB8000840, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AC19 << 4) | (RTD18X5_BGA459_PIN_AC19_UP << 3) | (RTD18X5_BGA459_PIN_AC19_PD << 2) |(RTD18X5_BGA459_PIN_AC19_DS << 1) | (RTD18X5_BGA459_PIN_AC19_SR)) << 14));
if (RTD18X5_BGA459_PIN_AC19 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x1&0x7)<<25)); }; // 14: EP
if (RTD18X5_BGA459_PIN_AC19 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x5&0xf)<<23)); }; // 6: CR_SD_WP_SRC5,<I>,<HS>
if (RTD18X5_BGA459_PIN_AC19 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x6&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC6,<I>
if (RTD18X5_BGA459_PIN_AC19 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x2&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC2,<I>
// PAD_NAME: pad_gpio_56_io 31
rtd_maskl(0xB8000844, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AE19 << 4) | (RTD18X5_BGA459_PIN_AE19_UP << 3) | (RTD18X5_BGA459_PIN_AE19_PD << 2) |(RTD18X5_BGA459_PIN_AE19_DS << 1) | (RTD18X5_BGA459_PIN_AE19_SR)) << 5));
if (RTD18X5_BGA459_PIN_AE19 == 0x12) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x3&0x1f)<<7)); }; // 12: I2C0_SDA_SRC3,<I/
if (RTD18X5_BGA459_PIN_AE19 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x0&0xf)<<10)); }; // 8: SC1_CD_SRC0,<I>
if (RTD18X5_BGA459_PIN_AE19 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 7: SC0_CD_SRC4,<I>
if (RTD18X5_BGA459_PIN_AE19 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 6: CR_SD_CMD_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AE19 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 2: EMMC_CMD_SRC1,<I/O>,<HS>
// PAD_NAME: pad_gpio_53_io 32
rtd_maskl(0xB8000840, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AD20 << 4) | (RTD18X5_BGA459_PIN_AD20_UP << 3) | (RTD18X5_BGA459_PIN_AD20_PD << 2) |(RTD18X5_BGA459_PIN_AD20_DS << 1) | (RTD18X5_BGA459_PIN_AD20_SR)) << 5));
if (RTD18X5_BGA459_PIN_AD20 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x4&0x7)<<13)); }; // 15:
if (RTD18X5_BGA459_PIN_AD20 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x3&0x7)<<1)); }; // 10:
if (RTD18X5_BGA459_PIN_AD20 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F:
if (RTD18X5_BGA459_PIN_AD20 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x0&0x7)<<26)); }; // 9: uart2_rXdi_src0,<I>
if (RTD18X5_BGA459_PIN_AD20 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x5&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC5,<I>
if (RTD18X5_BGA459_PIN_AD20 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x5&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_AD20 == 0x2) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x0&0x7)<<20)); }; // 2: uart1_rXdi_src0,<I>
// PAD_NAME: pad_gpio_54_io 33
rtd_maskl(0xB8000844, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AC20 << 4) | (RTD18X5_BGA459_PIN_AC20_UP << 3) | (RTD18X5_BGA459_PIN_AC20_PD << 2) |(RTD18X5_BGA459_PIN_AC20_DS << 1) | (RTD18X5_BGA459_PIN_AC20_SR)) << 23));
if (RTD18X5_BGA459_PIN_AC20 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x4&0x7)<<9)); }; // 15:
if (RTD18X5_BGA459_PIN_AC20 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 10:
if (RTD18X5_BGA459_PIN_AC20 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F:
if (RTD18X5_BGA459_PIN_AC20 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x8&0xf)<<5)); }; // 8: SC1_DATA0_SRC8,<I/O>
if (RTD18X5_BGA459_PIN_AC20 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x5&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src5,<I/O>
// PAD_NAME: PLT_P0_TXHP 34
rtd_maskl(0xB80008B8, 0x07FFFFFF, (RTD18X5_BGA459_PIN_F24) << 27);
if (RTD18X5_BGA459_PIN_F24 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x2&0x3)<<15)); }; // 10: P_CRS_SRC2,<I>,<HS>
// PAD_NAME: PLT_P0_TXGP 35
rtd_maskl(0xB80008B8, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_F23) << 17);
if (RTD18X5_BGA459_PIN_F23 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11:
if (RTD18X5_BGA459_PIN_F23 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x2&0x7)<<18)); }; // 10:
if (RTD18X5_BGA459_PIN_F23 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x2&0x3)<<4)); }; // 7: DEMOD_ANT_TX_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_F23 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 2: EMMC_CMD_SRC3,<I/O>,<HS>
// PAD_NAME: PLT_P0_TXGN 36
rtd_maskl(0xB80008B8, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_E25) << 12);
if (RTD18X5_BGA459_PIN_E25 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11:
if (RTD18X5_BGA459_PIN_E25 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x2&0x7)<<17)); }; // 10: P_RXE
if (RTD18X5_BGA459_PIN_E25 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x2&0x3)<<0)); }; // 7: DEMOD_ANT_OE_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_E25 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x2&0x7)<<19)); }; // 6: CR_SD_CD_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_E25 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x0&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src0,<I/O>
if (RTD18X5_BGA459_PIN_E25 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x0&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src0,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXFP 37
rtd_maskl(0xB80008B8, 0xFFFFF07F, (RTD18X5_BGA459_PIN_E24) << 7);
if (RTD18X5_BGA459_PIN_E24 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // A: USB_PWR_FLAG0_SRC2,<I>
if (RTD18X5_BGA459_PIN_E24 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: 
if (RTD18X5_BGA459_PIN_E24 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x1&0xf)<<23)); }; // 6: CR_SD_WP_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_E24 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x1&0x3)<<4)); }; // 7: DEMOD_ANT_TX_SRC1,<I/O>
// PAD_NAME: PLT_P0_TXFN 38
rtd_maskl(0xB80008B8, 0xFFFFFF83, (RTD18X5_BGA459_PIN_E23) << 2);
if (RTD18X5_BGA459_PIN_E23 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: I2C2_SDA_SRC2,<I/O
if (RTD18X5_BGA459_PIN_E23 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x2&0x3)<<19)); }; // B: USB_PWR_FLAG1_SRC2,<I>
if (RTD18X5_BGA459_PIN_E23 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x1&0x3)<<0)); }; // 7: DEMOD_ANT_OE_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_E23 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x3&0x7)<<19)); }; // 6: CR_SD_CD_SRC3,<I>,<HS>
// PAD_NAME: PLT_P0_TXEP 39
rtd_maskl(0xB80008BC, 0x07FFFFFF, (RTD18X5_BGA459_PIN_D24) << 27);
if (RTD18X5_BGA459_PIN_D24 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 15: VBY1_HTPD_src1,<I>
// PAD_NAME: PLT_P0_TXEN 40
rtd_maskl(0xB80008BC, 0xF83FFFFF, (RTD18X5_BGA459_PIN_D23) << 22);
if (RTD18X5_BGA459_PIN_D23 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x1&0x7)<<9)); }; // 15: VBY1_LOCK_src1,<I>
// PAD_NAME: PLT_P0_TXDP 41
rtd_maskl(0xB80008BC, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_C25) << 17);
if (RTD18X5_BGA459_PIN_C25 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x8&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC8,<I>
if (RTD18X5_BGA459_PIN_C25 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x4&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC4,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXDN 42
rtd_maskl(0xB80008BC, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_B25) << 12);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCP 43
rtd_maskl(0xB80008BC, 0xFFFFF07F, (RTD18X5_BGA459_PIN_A25) << 7);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCN 44
rtd_maskl(0xB80008BC, 0xFFFFFF83, (RTD18X5_BGA459_PIN_C24) << 2);
// PAD_NAME: PLT_P0_TXBP 45
rtd_maskl(0xB80008C0, 0x07FFFFFF, (RTD18X5_BGA459_PIN_A24) << 27);
if (RTD18X5_BGA459_PIN_A24 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 15: VBY1_HTPD_src0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXBN 46
rtd_maskl(0xB80008C0, 0xF83FFFFF, (RTD18X5_BGA459_PIN_B24) << 22);
if (RTD18X5_BGA459_PIN_B24 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x0&0x7)<<9)); }; // 15: VBY1_LOCK_src0,<I>
// PAD_NAME: PLT_P0_TXAP 47
rtd_maskl(0xB80008C0, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_C23) << 17);
if (RTD18X5_BGA459_PIN_C23 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SCL_SRC10,<I/O>
if (RTD18X5_BGA459_PIN_C23 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SCL_SRC8,<I/O>
if (RTD18X5_BGA459_PIN_C23 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x2&0x3)<<2)); }; // 7: DEMOD_ANT_RX_SRC2,<I>
// PAD_NAME: PLT_P0_TXAN 48
rtd_maskl(0xB80008C0, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_B23) << 12);
if (RTD18X5_BGA459_PIN_B23 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SDA_SRC10,<I/O>
if (RTD18X5_BGA459_PIN_B23 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SDA_SRC8,<I/O>
// PAD_NAME: PLT_P1_TXGP 49
rtd_maskl(0xB80008C0, 0xFFFFF07F, (RTD18X5_BGA459_PIN_E22) << 7);
if (RTD18X5_BGA459_PIN_E22 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x4&0x7)<<1)); }; // 11:
if (RTD18X5_BGA459_PIN_E22 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x2&0x7)<<11)); }; // 10:
if (RTD18X5_BGA459_PIN_E22 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F:
if (RTD18X5_BGA459_PIN_E22 == 0xA) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x1&0x7)<<20)); }; // A: uart1_rXdi_src1,<I>
if (RTD18X5_BGA459_PIN_E22 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x1&0x7)<<26)); }; // 9: uart2_rXdi_src1,<I>
if (RTD18X5_BGA459_PIN_E22 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x6&0xf)<<23)); }; // 6: CR_SD_WP_SRC6,<I>,<HS>
if (RTD18X5_BGA459_PIN_E22 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_E22 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x0&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC0,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXGN 50
rtd_maskl(0xB80008C0, 0xFFFFFF83, (RTD18X5_BGA459_PIN_F22) << 2);
if (RTD18X5_BGA459_PIN_F22 == 0x11) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 11:
if (RTD18X5_BGA459_PIN_F22 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x2&0x3)<<8)); }; // 10:
if (RTD18X5_BGA459_PIN_F22 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F: I2C2_SDA_SRC3,<I/O>
if (RTD18X5_BGA459_PIN_F22 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 6: CR_SD_CMD_SRC3,<I/O>,<HS>
// PAD_NAME: PLT_P1_TXFP 51
rtd_maskl(0xB80008C4, 0x07FFFFFF, (RTD18X5_BGA459_PIN_D21) << 27);
if (RTD18X5_BGA459_PIN_D21 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11:
if (RTD18X5_BGA459_PIN_D21 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10:
if (RTD18X5_BGA459_PIN_D21 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x0&0x3)<<21)); }; // A: USB_PWR_FLAG0_SRC0,<I>
if (RTD18X5_BGA459_PIN_D21 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC3,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_D21 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x7&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC7,<I>
if (RTD18X5_BGA459_PIN_D21 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC3,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXFN 52
rtd_maskl(0xB80008C4, 0xF83FFFFF, (RTD18X5_BGA459_PIN_D22) << 22);
if (RTD18X5_BGA459_PIN_D22 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11:
if (RTD18X5_BGA459_PIN_D22 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10:
if (RTD18X5_BGA459_PIN_D22 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x0&0x3)<<19)); }; // B: USB_PWR_FLAG1_SRC0,<I>
if (RTD18X5_BGA459_PIN_D22 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x1&0x3)<<2)); }; // 7: DEMOD_ANT_RX_SRC1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXEP 53
rtd_maskl(0xB80008C4, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_F21) << 17);
// PAD_NAME: PLT_P1_TXEN 54
rtd_maskl(0xB80008C4, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_E21) << 12);
// PAD_NAME: PLT_P1_TXDP 55
rtd_maskl(0xB80008C4, 0xFFFFF07F, (RTD18X5_BGA459_PIN_C22) << 7);
if (RTD18X5_BGA459_PIN_C22 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SCL_SRC6,<I/O>
if (RTD18X5_BGA459_PIN_C22 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x0&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC0,<I>
if (RTD18X5_BGA459_PIN_C22 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x0&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC0,<I>
// PAD_NAME: PLT_P1_TXDN 56
rtd_maskl(0xB80008C4, 0xFFFFFF83, (RTD18X5_BGA459_PIN_B22) << 2);
if (RTD18X5_BGA459_PIN_B22 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SDA_SRC6,<I/O>
// PAD_NAME: PLT_P1_TXCP 57
rtd_maskl(0xB80008C8, 0x07FFFFFF, (RTD18X5_BGA459_PIN_A22) << 27);
// PAD_NAME: PLT_P1_TXCN 58
rtd_maskl(0xB80008C8, 0xF83FFFFF, (RTD18X5_BGA459_PIN_C21) << 22);
// PAD_NAME: PLT_P1_TXBP 59
rtd_maskl(0xB80008C8, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_A21) << 17);
if (RTD18X5_BGA459_PIN_A21 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SCL_SRC9,<I/O>
if (RTD18X5_BGA459_PIN_A21 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x2&0x7)<<16)); }; // 8: uart0_rXdi_src2,<I>
if (RTD18X5_BGA459_PIN_A21 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x7&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC7,<I/O>
if (RTD18X5_BGA459_PIN_A21 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x7&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC7,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXBN 60
rtd_maskl(0xB80008C8, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_B21) << 12);
if (RTD18X5_BGA459_PIN_B21 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SDA_SRC9,<I/O>
// PAD_NAME: PLT_P1_TXAP 61
rtd_maskl(0xB80008C8, 0xFFFFF07F, (RTD18X5_BGA459_PIN_C20) << 7);
if (RTD18X5_BGA459_PIN_C20 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SCL_SRC8,<I/O>
if (RTD18X5_BGA459_PIN_C20 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x4&0x7)<<20)); }; // 8: uart1_rXdi_src4,<I>
// PAD_NAME: PLT_P1_TXAN 62
rtd_maskl(0xB80008C8, 0xFFFFFF83, (RTD18X5_BGA459_PIN_B20) << 2);
if (RTD18X5_BGA459_PIN_B20 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SDA_SRC8,<I/O>
if (RTD18X5_BGA459_PIN_B20 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x7&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src7,<I/O>
if (RTD18X5_BGA459_PIN_B20 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x7&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src7,<I/O>
// PAD_NAME: pad_st_gpio_7_io 63
rtd_maskl(0xB806024C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_E9 << 4) | (RTD18X5_BGA459_PIN_E9_UP << 3) | (RTD18X5_BGA459_PIN_E9_PD << 2) |(RTD18X5_BGA459_PIN_E9_DS << 1) | (RTD18X5_BGA459_PIN_E9_SR)) << 5));
// PAD_NAME: pad_st_gpio_8_io 64
rtd_maskl(0xB806024C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_C10 << 4) | (RTD18X5_BGA459_PIN_C10_UP << 3) | (RTD18X5_BGA459_PIN_C10_PD << 2) |(RTD18X5_BGA459_PIN_C10_DS << 1) | (RTD18X5_BGA459_PIN_C10_SR)) << 14));
if (RTD18X5_BGA459_PIN_C10 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x1&0x7)<<16)); }; // 15: GSPI_SCLK_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C10 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 11: VFD_D_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_C10 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x0&0x7)<<2)); }; // 8: irrX_src0,<I>
if (RTD18X5_BGA459_PIN_C10 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<4), ((0x0&0x1)<<4)); }; // 3: PCMCIA_IREQ1_N_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_9_io 65
rtd_maskl(0xB806024C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_F9 << 4) | (RTD18X5_BGA459_PIN_F9_UP << 3) | (RTD18X5_BGA459_PIN_F9_PD << 2) |(RTD18X5_BGA459_PIN_F9_DS << 1) | (RTD18X5_BGA459_PIN_F9_SR)) << 23));
if (RTD18X5_BGA459_PIN_F9 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x5&0x7)<<13)); }; // 15:
if (RTD18X5_BGA459_PIN_F9 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x1&0x7)<<12)); }; // 14: GSPI_
if (RTD18X5_BGA459_PIN_F9 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SCL_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_F9 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x3&0x7)<<16)); }; // 8: uart0_rXdi_src3,<I>
if (RTD18X5_BGA459_PIN_F9 == 0x3) { rtd_maskl(0xb8000928, ~((0x3)<<0), ((0x0&0x3)<<0)); }; // 3: PCMCIA_CD1_N_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_10_io 66
rtd_maskl(0xB8060248, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_B9 << 4) | (RTD18X5_BGA459_PIN_B9_UP << 3) | (RTD18X5_BGA459_PIN_B9_PD << 2) |(RTD18X5_BGA459_PIN_B9_DS << 1) | (RTD18X5_BGA459_PIN_B9_SR)) << 5));
if (RTD18X5_BGA459_PIN_B9 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x5&0x7)<<9)); }; // 15:
if (RTD18X5_BGA459_PIN_B9 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x1&0x7)<<8)); }; // 14: GSPI_CS_N_SRC1,
if (RTD18X5_BGA459_PIN_B9 == 0x13) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x2&0x7)<<25)); }; // 13: EPI_LOCK_src2,<I>
if (RTD18X5_BGA459_PIN_B9 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SDA_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_B9 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // A: uart1_cts_n_src0,<I>
if (RTD18X5_BGA459_PIN_B9 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 9: uart0_cts_n_src0,<I>
// PAD_NAME: pad_st_gpio_11_io 67
rtd_maskl(0xB8060248, 0xFF803FFF, (((RTD18X5_BGA459_PIN_C8 << 4) | (RTD18X5_BGA459_PIN_C8_UP << 3) | (RTD18X5_BGA459_PIN_C8_PD << 2) |(RTD18X5_BGA459_PIN_C8_DS << 1) | (RTD18X5_BGA459_PIN_C8_SR)) << 14));
// PAD_NAME: pad_st_gpio_12_io 68
rtd_maskl(0xB8060248, 0x007FFFFF, (((RTD18X5_BGA459_PIN_E10 << 4) | (RTD18X5_BGA459_PIN_E10_UP << 3) | (RTD18X5_BGA459_PIN_E10_PD << 2) |(RTD18X5_BGA459_PIN_E10_DS << 1) | (RTD18X5_BGA459_PIN_E10_SR)) << 23));
if (RTD18X5_BGA459_PIN_E10 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x1&0x7)<<4)); }; // 15:
if (RTD18X5_BGA459_PIN_E10 == 0x12) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0xa&0xf)<<5)); }; // 12:
if (RTD18X5_BGA459_PIN_E10 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SCL_SRC4,<I/O>
if (RTD18X5_BGA459_PIN_E10 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x2&0xf)<<23)); }; // 6: CR_SD_WP_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_E10 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x0&0x7)<<19)); }; // 5: CR_SD_CD_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_E10 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<6), ((0x0&0x1)<<6)); }; // 3: PCMCIA_INPACK1_N_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_13_io 69
rtd_maskl(0xB8060244, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_B10 << 4) | (RTD18X5_BGA459_PIN_B10_UP << 3) | (RTD18X5_BGA459_PIN_B10_PD << 2) |(RTD18X5_BGA459_PIN_B10_DS << 1) | (RTD18X5_BGA459_PIN_B10_SR)) << 5));
if (RTD18X5_BGA459_PIN_B10 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SDA_SRC4,<I/O>
// PAD_NAME: pad_st_gpio_14_io 70
rtd_maskl(0xB8060204, 0x007FFFFF, (((RTD18X5_BGA459_PIN_C4 << 4) | (RTD18X5_BGA459_PIN_C4_UP << 3) | (RTD18X5_BGA459_PIN_C4_PD << 2) |(RTD18X5_BGA459_PIN_C4_DS << 1) | (RTD18X5_BGA459_PIN_C4_SR)) << 23));
if (RTD18X5_BGA459_PIN_C4 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SDA_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_C4 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x1&0x3)<<8)); }; // 5: HDDC0_SDA_SRC1,<I/O>
// PAD_NAME: pad_st_gpio_15_io 71
rtd_maskl(0xB8060200, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C5 << 4) | (RTD18X5_BGA459_PIN_C5_UP << 3) | (RTD18X5_BGA459_PIN_C5_PD << 2) |(RTD18X5_BGA459_PIN_C5_DS << 1) | (RTD18X5_BGA459_PIN_C5_SR)) << 5));
if (RTD18X5_BGA459_PIN_C5 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SCL_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_C5 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 9: uart0_rXdi_src0,<I>
if (RTD18X5_BGA459_PIN_C5 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x1&0x3)<<5)); }; // 5: HDDC0_SCL_SRC1,<I>
// PAD_NAME: pad_st_gpio_16_io 72
rtd_maskl(0xB8060244, 0xFF803FFF, (((RTD18X5_BGA459_PIN_D4 << 4) | (RTD18X5_BGA459_PIN_D4_UP << 3) | (RTD18X5_BGA459_PIN_D4_PD << 2) |(RTD18X5_BGA459_PIN_D4_DS << 1) | (RTD18X5_BGA459_PIN_D4_SR)) << 14));
if (RTD18X5_BGA459_PIN_D4 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x1&0x7)<<2)); }; // 9: irrX_src1,<I>
if (RTD18X5_BGA459_PIN_D4 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 6: CR_SD_CMD_SRC0,<I/O>,<HS>
// PAD_NAME: pad_st_gpio_17_io 73
rtd_maskl(0xB8060204, 0xFF803FFF, (((RTD18X5_BGA459_PIN_D5 << 4) | (RTD18X5_BGA459_PIN_D5_UP << 3) | (RTD18X5_BGA459_PIN_D5_PD << 2) |(RTD18X5_BGA459_PIN_D5_DS << 1) | (RTD18X5_BGA459_PIN_D5_SR)) << 14));
// PAD_NAME: pad_st_gpio_18_io 74
rtd_maskl(0xB8060204, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_E5 << 4) | (RTD18X5_BGA459_PIN_E5_UP << 3) | (RTD18X5_BGA459_PIN_E5_PD << 2) |(RTD18X5_BGA459_PIN_E5_DS << 1) | (RTD18X5_BGA459_PIN_E5_SR)) << 5));
if (RTD18X5_BGA459_PIN_E5 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x4&0x7)<<2)); }; // 8: irrX_src4,<I>
// PAD_NAME: pad_st_gpio_19_io 75
rtd_maskl(0xB8060244, 0x007FFFFF, (((RTD18X5_BGA459_PIN_E4 << 4) | (RTD18X5_BGA459_PIN_E4_UP << 3) | (RTD18X5_BGA459_PIN_E4_PD << 2) |(RTD18X5_BGA459_PIN_E4_DS << 1) | (RTD18X5_BGA459_PIN_E4_SR)) << 23));
if (RTD18X5_BGA459_PIN_E4 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x5&0xf)<<10)); }; // 8: SC1_CD_SRC5,<I>
if (RTD18X5_BGA459_PIN_E4 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 7: SC0_CD_SRC0,<I>
if (RTD18X5_BGA459_PIN_E4 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x7&0xf)<<23)); }; // 6: CR_SD_WP_SRC7,<I>,<HS>
// PAD_NAME: pad_st_gpio_20_io 76
rtd_maskl(0xB8060208, 0x007FFFFF, (((RTD18X5_BGA459_PIN_F5 << 4) | (RTD18X5_BGA459_PIN_F5_UP << 3) | (RTD18X5_BGA459_PIN_F5_PD << 2) |(RTD18X5_BGA459_PIN_F5_DS << 1) | (RTD18X5_BGA459_PIN_F5_SR)) << 23));
if (RTD18X5_BGA459_PIN_F5 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x1&0x7)<<19)); }; // 6: CR_SD_CD_SRC1,<I>,<HS>
// PAD_NAME: pad_st_gpio_21_io 77
rtd_maskl(0xB8060208, 0xFF803FFF, (((RTD18X5_BGA459_PIN_F4 << 4) | (RTD18X5_BGA459_PIN_F4_UP << 3) | (RTD18X5_BGA459_PIN_F4_PD << 2) |(RTD18X5_BGA459_PIN_F4_DS << 1) | (RTD18X5_BGA459_PIN_F4_SR)) << 14));
if (RTD18X5_BGA459_PIN_F4 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x6&0xf)<<5)); }; // 8: SC1_DATA0_SRC6,<I/O>
if (RTD18X5_BGA459_PIN_F4 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 7: SC0_DATA0_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_F4 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x1&0x7)<<15)); }; // 6: CR_SD_Data_bit0_SRC1,<I/O>,<HS>
// PAD_NAME: pad_st_gpio_22_io 78
rtd_maskl(0xB8060240, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_G4 << 4) | (RTD18X5_BGA459_PIN_G4_UP << 3) | (RTD18X5_BGA459_PIN_G4_PD << 2) |(RTD18X5_BGA459_PIN_G4_DS << 1) | (RTD18X5_BGA459_PIN_G4_SR)) << 5));
if (RTD18X5_BGA459_PIN_G4 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x1&0x7)<<11)); }; // 6: CR_SD_Data_bit1_SRC1,<I/O>,<HS>
// PAD_NAME: pad_st_gpio_23_io 79
rtd_maskl(0xB8060200, 0x007FFFFF, (((RTD18X5_BGA459_PIN_G5 << 4) | (RTD18X5_BGA459_PIN_G5_UP << 3) | (RTD18X5_BGA459_PIN_G5_PD << 2) |(RTD18X5_BGA459_PIN_G5_DS << 1) | (RTD18X5_BGA459_PIN_G5_SR)) << 23));
if (RTD18X5_BGA459_PIN_G5 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SCL_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_G5 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // A: uart1_cts_n_src1,<I>
if (RTD18X5_BGA459_PIN_G5 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 9: uart0_cts_n_src1,<I>
if (RTD18X5_BGA459_PIN_G5 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x1&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_G5 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x0&0x3)<<5)); }; // 4: HDDC0_SCL_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_24_io 80
rtd_maskl(0xB8060200, 0xFF803FFF, (((RTD18X5_BGA459_PIN_H5 << 4) | (RTD18X5_BGA459_PIN_H5_UP << 3) | (RTD18X5_BGA459_PIN_H5_PD << 2) |(RTD18X5_BGA459_PIN_H5_DS << 1) | (RTD18X5_BGA459_PIN_H5_SR)) << 14));
if (RTD18X5_BGA459_PIN_H5 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xa&0xf)<<10)); }; // 14: SC1_CD_SRC10,<I>
if (RTD18X5_BGA459_PIN_H5 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SDA_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_H5 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x1&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_H5 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x0&0x3)<<8)); }; // 4: HDDC0_SDA_SRC0,<I/O>
// PAD_NAME: LSADC_REF_APAD 81
rtd_maskl(0xB806020C, 0x07FFFFFF, (RTD18X5_BGA459_PIN_D7) << 27);
// PAD_NAME: LSADC0_APAD 82
rtd_maskl(0xB8060210, 0x07FFFFFF, (RTD18X5_BGA459_PIN_B7) << 27);
// PAD_NAME: LSADC1_APAD 83
rtd_maskl(0xB806020C, 0xFFFFFF83, (RTD18X5_BGA459_PIN_C6) << 2);
// PAD_NAME: LSADC2_APAD 84
rtd_maskl(0xB806020C, 0xFFFFF07F, (RTD18X5_BGA459_PIN_A7) << 7);
// PAD_NAME: LSADC7_APAD 85
rtd_maskl(0xB806020C, 0xF83FFFFF, (RTD18X5_BGA459_PIN_C7) << 22);
// PAD_NAME: VSYNC_APAD 86
rtd_maskl(0xB80008D8, 0x007FFFFF, (((RTD18X5_BGA459_PIN_M1 << 4) | (RTD18X5_BGA459_PIN_M1_UP << 3) | (RTD18X5_BGA459_PIN_M1_PD << 2) |(RTD18X5_BGA459_PIN_M1_DS << 1) | (RTD18X5_BGA459_PIN_M1_SR)) << 23));
// PAD_NAME: HSYNC_APAD 87
rtd_maskl(0xB80008D8, 0xFC03FFFF, (((RTD18X5_BGA459_PIN_M2 << 4) | (RTD18X5_BGA459_PIN_M2_UP << 3) | (RTD18X5_BGA459_PIN_M2_PD << 2) |(RTD18X5_BGA459_PIN_M2_DS << 1) | (RTD18X5_BGA459_PIN_M2_SR)) << 18));
// PAD_NAME: VIN_0P_APAD 88
rtd_maskl(0xB80008DC, 0x007FFFFF, (((RTD18X5_BGA459_PIN_M3 << 4) | (RTD18X5_BGA459_PIN_M3_UP << 3) | (RTD18X5_BGA459_PIN_M3_PD << 2) |(RTD18X5_BGA459_PIN_M3_DS << 1) | (RTD18X5_BGA459_PIN_M3_SR)) << 23));
// PAD_NAME: VIN_BN_APAD 89
rtd_maskl(0xB80008DC, 0xFC03FFFF, (((RTD18X5_BGA459_PIN_N2 << 4) | (RTD18X5_BGA459_PIN_N2_UP << 3) | (RTD18X5_BGA459_PIN_N2_PD << 2) |(RTD18X5_BGA459_PIN_N2_DS << 1) | (RTD18X5_BGA459_PIN_N2_SR)) << 18));
// PAD_NAME: VIN_1P_APAD 90
rtd_maskl(0xB80008DC, 0xFFE01FFF, (((RTD18X5_BGA459_PIN_N3 << 4) | (RTD18X5_BGA459_PIN_N3_UP << 3) | (RTD18X5_BGA459_PIN_N3_PD << 2) |(RTD18X5_BGA459_PIN_N3_DS << 1) | (RTD18X5_BGA459_PIN_N3_SR)) << 13));
// PAD_NAME: VIN_2P_APAD 91
rtd_maskl(0xB80008DC, 0xFFFF00FF, (((RTD18X5_BGA459_PIN_P2 << 4) | (RTD18X5_BGA459_PIN_P2_UP << 3) | (RTD18X5_BGA459_PIN_P2_PD << 2) |(RTD18X5_BGA459_PIN_P2_DS << 1) | (RTD18X5_BGA459_PIN_P2_SR)) << 8));
// PAD_NAME: VIN_13P_APAD 92
rtd_maskl(0xB80008E8, 0x007FFFFF, (((RTD18X5_BGA459_PIN_U1 << 4) | (RTD18X5_BGA459_PIN_U1_UP << 3) | (RTD18X5_BGA459_PIN_U1_PD << 2) |(RTD18X5_BGA459_PIN_U1_DS << 1) | (RTD18X5_BGA459_PIN_U1_SR)) << 23));
// PAD_NAME: VIN_A0N_APAD 93
rtd_maskl(0xB80008E4, 0xFFE01FFF, (((RTD18X5_BGA459_PIN_V2 << 4) | (RTD18X5_BGA459_PIN_V2_UP << 3) | (RTD18X5_BGA459_PIN_V2_PD << 2) |(RTD18X5_BGA459_PIN_V2_DS << 1) | (RTD18X5_BGA459_PIN_V2_SR)) << 13));
// PAD_NAME: VIN_12P_APAD 94
rtd_maskl(0xB80008E4, 0xFC03FFFF, (((RTD18X5_BGA459_PIN_V3 << 4) | (RTD18X5_BGA459_PIN_V3_UP << 3) | (RTD18X5_BGA459_PIN_V3_PD << 2) |(RTD18X5_BGA459_PIN_V3_DS << 1) | (RTD18X5_BGA459_PIN_V3_SR)) << 18));
if (RTD18X5_BGA459_PIN_V3 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xc&0x1f)<<7)); }; // F: I2C0_SCL_SRC12,<I/O>
// PAD_NAME: BB_AI4L_APAD 95
rtd_maskl(0xB80008F0, 0xFFFFF807, (((RTD18X5_BGA459_PIN_AB2 << 4) | (RTD18X5_BGA459_PIN_AB2_UP << 3) | (RTD18X5_BGA459_PIN_AB2_PD << 2) |(RTD18X5_BGA459_PIN_AB2_DS << 1) | (RTD18X5_BGA459_PIN_AB2_SR)) << 3));
// PAD_NAME: BB_AI4R_APAD 96
rtd_maskl(0xB80008F4, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AB3 << 4) | (RTD18X5_BGA459_PIN_AB3_UP << 3) | (RTD18X5_BGA459_PIN_AB3_PD << 2) |(RTD18X5_BGA459_PIN_AB3_DS << 1) | (RTD18X5_BGA459_PIN_AB3_SR)) << 23));
// PAD_NAME: HSDM_2_APAD 97
rtd_maskl(0xB80008F8, 0xFFFFF807, (((RTD18X5_BGA459_PIN_AD8 << 4) | (RTD18X5_BGA459_PIN_AD8_UP << 3) | (RTD18X5_BGA459_PIN_AD8_PD << 2) |(RTD18X5_BGA459_PIN_AD8_DS << 1) | (RTD18X5_BGA459_PIN_AD8_SR)) << 3));
if (RTD18X5_BGA459_PIN_AD8 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xe&0xf)<<8)); }; // 11: I2C2_SDA_SRC14,<I/O>
if (RTD18X5_BGA459_PIN_AD8 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x3&0x3)<<15)); }; // 10: P_CRS_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_AD8 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xe&0x1f)<<7)); }; // F: I2C0_SDA_SRC14,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: HSDP_2_APAD 98
rtd_maskl(0xB80008F8, 0xFFFF00FF, (((RTD18X5_BGA459_PIN_AC8 << 4) | (RTD18X5_BGA459_PIN_AC8_UP << 3) | (RTD18X5_BGA459_PIN_AC8_PD << 2) |(RTD18X5_BGA459_PIN_AC8_DS << 1) | (RTD18X5_BGA459_PIN_AC8_SR)) << 8));
if (RTD18X5_BGA459_PIN_AC8 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xe&0xf)<<8)); }; // 11: I2C2_SCL_SRC14,<I/O>
if (RTD18X5_BGA459_PIN_AC8 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x3&0x7)<<18)); }; // 10: P_COL_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_AC8 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xe&0x1f)<<7)); }; // F: I2C0_SCL_SRC14,<I/O>
if (RTD18X5_BGA459_PIN_AC8 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x4&0x7)<<16)); }; // 8: uart0_rXdi_src4,<I>
// PAD_NAME: LSADC4_APAD 99
rtd_maskl(0xB806020C, 0xFFFE0FFF, (RTD18X5_BGA459_PIN_A5) << 12);
// PAD_NAME: LSADC6_APAD 100
rtd_maskl(0xB806020C, 0xFFC1FFFF, (RTD18X5_BGA459_PIN_B6) << 17);
// PAD_NAME: pad_gpio_3_io 101
rtd_maskl(0xB8000894, 0x007FFFFF, (((RTD18X5_BGA459_PIN_M5 << 4) | (RTD18X5_BGA459_PIN_M5_UP << 3) | (RTD18X5_BGA459_PIN_M5_PD << 2) |(RTD18X5_BGA459_PIN_M5_DS << 1) | (RTD18X5_BGA459_PIN_M5_SR)) << 23));
if (RTD18X5_BGA459_PIN_M5 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<22), ((0x0&0x3)<<22)); }; // 10: P_TXC_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_M5 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x5&0xf)<<5)); }; // 8: SC1_DATA0_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_M5 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x1&0x7)<<24)); }; // 7: SC0_DATA0_SRC1,<I/O>
// PAD_NAME: pad_gpio_4_io 102
rtd_maskl(0xB8000894, 0xFF803FFF, (((RTD18X5_BGA459_PIN_M6 << 4) | (RTD18X5_BGA459_PIN_M6_UP << 3) | (RTD18X5_BGA459_PIN_M6_PD << 2) |(RTD18X5_BGA459_PIN_M6_DS << 1) | (RTD18X5_BGA459_PIN_M6_SR)) << 14));
if (RTD18X5_BGA459_PIN_M6 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x7&0x7)<<20)); }; // 9: uart1_rXdi_src7,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_5_io 103
rtd_maskl(0xB8000808, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AA9 << 4) | (RTD18X5_BGA459_PIN_AA9_UP << 3) | (RTD18X5_BGA459_PIN_AA9_PD << 2) |(RTD18X5_BGA459_PIN_AA9_DS << 1) | (RTD18X5_BGA459_PIN_AA9_SR)) << 23));
if (RTD18X5_BGA459_PIN_AA9 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<12), ((0x2&0x3)<<12)); }; // 16:
if (RTD18X5_BGA459_PIN_AA9 == 0x15) { rtd_maskl(0xb8000920, ~((0x1)<<24), ((0x0&0x1)<<24)); }; // 15:
if (RTD18X5_BGA459_PIN_AA9 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xd&0x1f)<<7)); }; // 11:
if (RTD18X5_BGA459_PIN_AA9 == 0x9) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x0&0x3)<<4)); }; // 9: DEMOD_ANT_TX_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_AA9 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x3&0x7)<<15)); }; // 6: CR_SD_Data_bit0_SRC3,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AA9 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x2&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC2,<I/O>
// PAD_NAME: pad_gpio_6_io 104
rtd_maskl(0xB8000808, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AE10 << 4) | (RTD18X5_BGA459_PIN_AE10_UP << 3) | (RTD18X5_BGA459_PIN_AE10_PD << 2) |(RTD18X5_BGA459_PIN_AE10_DS << 1) | (RTD18X5_BGA459_PIN_AE10_SR)) << 14));
if (RTD18X5_BGA459_PIN_AE10 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<20), ((0x2&0x3)<<20)); }; // 16:
if (RTD18X5_BGA459_PIN_AE10 == 0x15) { rtd_maskl(0xb8000920, ~((0x1)<<30), ((0x0&0x1)<<30)); }; // 15:
if (RTD18X5_BGA459_PIN_AE10 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xd&0x1f)<<7)); }; // 11:
if (RTD18X5_BGA459_PIN_AE10 == 0x9) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x0&0x3)<<0)); }; // 9: DEMOD_ANT_OE_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_AE10 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x3&0x7)<<11)); }; // 6: CR_SD_Data_bit1_SRC3,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AE10 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x2&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC2,<I>
if (RTD18X5_BGA459_PIN_AE10 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x2&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC2,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_7_io 105
rtd_maskl(0xB8000808, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AC9 << 4) | (RTD18X5_BGA459_PIN_AC9_UP << 3) | (RTD18X5_BGA459_PIN_AC9_PD << 2) |(RTD18X5_BGA459_PIN_AC9_DS << 1) | (RTD18X5_BGA459_PIN_AC9_SR)) << 5));
if (RTD18X5_BGA459_PIN_AC9 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<22), ((0x2&0x3)<<22)); }; // 16:
if (RTD18X5_BGA459_PIN_AC9 == 0x15) { rtd_maskl(0xb8000920, ~((0x1)<<28), ((0x0&0x1)<<28)); }; // 15:
if (RTD18X5_BGA459_PIN_AC9 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xd&0xf)<<8)); }; // 11: I2C2_SCL_SRC13
if (RTD18X5_BGA459_PIN_AC9 == 0x9) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x0&0x3)<<2)); }; // 9: DEMOD_ANT_RX_SRC0,<I>
if (RTD18X5_BGA459_PIN_AC9 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x4&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC4,<I/O>,<HS>
// PAD_NAME: pad_gpio_8_io 106
rtd_maskl(0xB800080C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_Y10 << 4) | (RTD18X5_BGA459_PIN_Y10_UP << 3) | (RTD18X5_BGA459_PIN_Y10_PD << 2) |(RTD18X5_BGA459_PIN_Y10_DS << 1) | (RTD18X5_BGA459_PIN_Y10_SR)) << 23));
if (RTD18X5_BGA459_PIN_Y10 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<17), ((0x2&0x3)<<17)); }; // 16:
if (RTD18X5_BGA459_PIN_Y10 == 0x15) { rtd_maskl(0xb8000920, ~((0x1)<<26), ((0x0&0x1)<<26)); }; // 15:
if (RTD18X5_BGA459_PIN_Y10 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xd&0xf)<<8)); }; // 11:
if (RTD18X5_BGA459_PIN_Y10 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x1&0x3)<<21)); }; // A: USB_PWR_FLAG0_SRC1,<I>
if (RTD18X5_BGA459_PIN_Y10 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x4&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC4,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_Y10 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x2&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src2,<I/O>
// PAD_NAME: pad_gpio_9_io 107
rtd_maskl(0xB800080C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AC10 << 4) | (RTD18X5_BGA459_PIN_AC10_UP << 3) | (RTD18X5_BGA459_PIN_AC10_PD << 2) |(RTD18X5_BGA459_PIN_AC10_DS << 1) | (RTD18X5_BGA459_PIN_AC10_SR)) << 14));
if (RTD18X5_BGA459_PIN_AC10 == 0x15) { rtd_maskl(0xb8000920, ~((0x1)<<22), ((0x0&0x1)<<22)); }; // 15:
if (RTD18X5_BGA459_PIN_AC10 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x1&0x3)<<19)); }; // B: USB_PWR_FLAG1_SRC1,<I>
if (RTD18X5_BGA459_PIN_AC10 == 0x1) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 1: EMMC_CMD_SRC4,<I/O>,<HS>
// PAD_NAME: pad_gpio_10_io 108
rtd_maskl(0xB800080C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AB12 << 4) | (RTD18X5_BGA459_PIN_AB12_UP << 3) | (RTD18X5_BGA459_PIN_AB12_PD << 2) |(RTD18X5_BGA459_PIN_AB12_DS << 1) | (RTD18X5_BGA459_PIN_AB12_SR)) << 5));
if (RTD18X5_BGA459_PIN_AB12 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<15), ((0x2&0x3)<<15)); }; // 16: TP0_Data_bit7_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB12 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x2&0x7)<<1)); }; // 11: P_RXD2_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB12 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x3&0x7)<<17)); }; // 10: P_RXER_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB12 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<24), ((0x0&0x1)<<24)); }; // 0: TP1_Data_bit0_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_11_io 109
rtd_maskl(0xB8000810, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD11 << 4) | (RTD18X5_BGA459_PIN_AD11_UP << 3) | (RTD18X5_BGA459_PIN_AD11_PD << 2) |(RTD18X5_BGA459_PIN_AD11_DS << 1) | (RTD18X5_BGA459_PIN_AD11_SR)) << 23));
if (RTD18X5_BGA459_PIN_AD11 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<16), ((0x2&0x3)<<16)); }; // 16: PCMCIA_D_bit7_SRC2,<I/O
if (RTD18X5_BGA459_PIN_AD11 == 0x11) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x2&0x7)<<28)); }; // 11: P_RXD3_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AD11 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x3&0x7)<<11)); }; // 10: P_RXDV_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_AD11 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x7&0xf)<<5)); }; // 8: SC1_DATA0_SRC7,<I/O>
if (RTD18X5_BGA459_PIN_AD11 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x5&0x7)<<24)); }; // 7: SC0_DATA0_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_AD11 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<30), ((0x0&0x1)<<30)); }; // 0: TP1_CLK_SRC0,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_12_io 110
rtd_maskl(0xB8000810, 0xFF803FFF, (((RTD18X5_BGA459_PIN_Y11 << 4) | (RTD18X5_BGA459_PIN_Y11_UP << 3) | (RTD18X5_BGA459_PIN_Y11_PD << 2) |(RTD18X5_BGA459_PIN_Y11_DS << 1) | (RTD18X5_BGA459_PIN_Y11_SR)) << 14));
if (RTD18X5_BGA459_PIN_Y11 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x2&0x7)<<13)); }; // 15: VBY1_HTPD_src2,<I>
if (RTD18X5_BGA459_PIN_Y11 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x3&0x3)<<8)); }; // 10: P_RXD0_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y11 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<8), ((0x0&0x1)<<8)); }; // 0: TP1_SYNC_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_13_io 111
rtd_maskl(0xB8000810, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_Y12 << 4) | (RTD18X5_BGA459_PIN_Y12_UP << 3) | (RTD18X5_BGA459_PIN_Y12_PD << 2) |(RTD18X5_BGA459_PIN_Y12_DS << 1) | (RTD18X5_BGA459_PIN_Y12_SR)) << 5));
if (RTD18X5_BGA459_PIN_Y12 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x2&0x7)<<9)); }; // 15: VBY1_LOCK_src2,<I>
if (RTD18X5_BGA459_PIN_Y12 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<5), ((0x3&0x3)<<5)); }; // 10: P_RXD1_SRC3,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y12 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x8&0xf)<<10)); }; // 8: SC1_CD_SRC8,<I>
if (RTD18X5_BGA459_PIN_Y12 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x5&0x7)<<28)); }; // 7: SC0_CD_SRC5,<I>
if (RTD18X5_BGA459_PIN_Y12 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<26), ((0x0&0x1)<<26)); }; // 0: TP1_VAL_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_14_io 112
rtd_maskl(0xB8000814, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD12 << 4) | (RTD18X5_BGA459_PIN_AD12_UP << 3) | (RTD18X5_BGA459_PIN_AD12_PD << 2) |(RTD18X5_BGA459_PIN_AD12_DS << 1) | (RTD18X5_BGA459_PIN_AD12_SR)) << 23));
if (RTD18X5_BGA459_PIN_AD12 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<25), ((0x0&0x3)<<25)); }; // 1: TP0_Data_bit2_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_15_io 113
rtd_maskl(0xB8000814, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AA12 << 4) | (RTD18X5_BGA459_PIN_AA12_UP << 3) | (RTD18X5_BGA459_PIN_AA12_PD << 2) |(RTD18X5_BGA459_PIN_AA12_DS << 1) | (RTD18X5_BGA459_PIN_AA12_SR)) << 14));
if (RTD18X5_BGA459_PIN_AA12 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x5&0x7)<<28)); }; // 2: EMMC_CMD_SRC5,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AA12 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<27), ((0x0&0x3)<<27)); }; // 1: TP0_Data_bit1_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_20_io 114
rtd_maskl(0xB800081C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AA13 << 4) | (RTD18X5_BGA459_PIN_AA13_UP << 3) | (RTD18X5_BGA459_PIN_AA13_PD << 2) |(RTD18X5_BGA459_PIN_AA13_DS << 1) | (RTD18X5_BGA459_PIN_AA13_SR)) << 23));
if (RTD18X5_BGA459_PIN_AA13 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x10&0x1f)<<7)); }; // 11: I2C0_
if (RTD18X5_BGA459_PIN_AA13 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x5&0x7)<<26)); }; // 9: uart2_rXdi_src5,<I>
if (RTD18X5_BGA459_PIN_AA13 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<20), ((0x1&0x3)<<20)); }; // 2: EMMC_Data_bit3_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AA13 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<22), ((0x1&0x1)<<22)); }; // 0: TP2_ERR_SRC1,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_21_io 115
rtd_maskl(0xB800081C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AA15 << 4) | (RTD18X5_BGA459_PIN_AA15_UP << 3) | (RTD18X5_BGA459_PIN_AA15_PD << 2) |(RTD18X5_BGA459_PIN_AA15_DS << 1) | (RTD18X5_BGA459_PIN_AA15_SR)) << 14));
if (RTD18X5_BGA459_PIN_AA15 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xf&0xf)<<8)); }; // 11: I2C2_SCL_SRC15,<I/O>
if (RTD18X5_BGA459_PIN_AA15 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x6&0x7)<<20)); }; // 9: uart1_rXdi_src6,<I>
if (RTD18X5_BGA459_PIN_AA15 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x4&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src4,<I/O>
if (RTD18X5_BGA459_PIN_AA15 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<24), ((0x1&0x3)<<24)); }; // 2: EMMC_Data_bit1_SRC1,<I/O>,<HS>
// PAD_NAME: pad_gpio_22_io 116
rtd_maskl(0xB800081C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_Y15 << 4) | (RTD18X5_BGA459_PIN_Y15_UP << 3) | (RTD18X5_BGA459_PIN_Y15_PD << 2) |(RTD18X5_BGA459_PIN_Y15_DS << 1) | (RTD18X5_BGA459_PIN_Y15_SR)) << 5));
if (RTD18X5_BGA459_PIN_Y15 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x10&0x1f)<<7)); }; // 11: I2C0_SDA_SRC16,<I/O>
if (RTD18X5_BGA459_PIN_Y15 == 0xB) { rtd_maskl(0xb8000904, ~((0x1)<<31), ((0x0&0x1)<<31)); }; // B: SPDIF_IN_src0,<I>
if (RTD18X5_BGA459_PIN_Y15 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x4&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC4,<I/O>
if (RTD18X5_BGA459_PIN_Y15 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<22), ((0x1&0x3)<<22)); }; // 2: EMMC_Data_bit2_SRC1,<I/O>,<HS>
// PAD_NAME: pad_gpio_23_io 117
rtd_maskl(0xB8000820, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AB15 << 4) | (RTD18X5_BGA459_PIN_AB15_UP << 3) | (RTD18X5_BGA459_PIN_AB15_PD << 2) |(RTD18X5_BGA459_PIN_AB15_DS << 1) | (RTD18X5_BGA459_PIN_AB15_SR)) << 23));
if (RTD18X5_BGA459_PIN_AB15 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xf&0xf)<<8)); }; // 11: I2C2_SDA_SRC15,<I/O>
if (RTD18X5_BGA459_PIN_AB15 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x4&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC4,<I>
if (RTD18X5_BGA459_PIN_AB15 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x4&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC4,<I/O>
if (RTD18X5_BGA459_PIN_AB15 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<26), ((0x1&0x3)<<26)); }; // 2: EMMC_Data_bit0_SRC1,<I/O>,<HS>
// PAD_NAME: pad_gpio_24_io 118
rtd_maskl(0xB8000850, 0x007FFFFF, (((RTD18X5_BGA459_PIN_G24 << 4) | (RTD18X5_BGA459_PIN_G24_UP << 3) | (RTD18X5_BGA459_PIN_G24_PD << 2) |(RTD18X5_BGA459_PIN_G24_DS << 1) | (RTD18X5_BGA459_PIN_G24_SR)) << 23));
if (RTD18X5_BGA459_PIN_G24 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<28), ((0x2&0x3)<<28)); }; // 16: PCMCIA_D_bit1_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_G24 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x2&0x7)<<24)); }; // 7: SC0_DATA0_SRC2,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_25_io 119
rtd_maskl(0xB8000820, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AE14 << 4) | (RTD18X5_BGA459_PIN_AE14_UP << 3) | (RTD18X5_BGA459_PIN_AE14_PD << 2) |(RTD18X5_BGA459_PIN_AE14_DS << 1) | (RTD18X5_BGA459_PIN_AE14_SR)) << 14));
if (RTD18X5_BGA459_PIN_AE14 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x4&0x7)<<26)); }; // 9: uart2_rXdi_src4,<I>
// PAD_NAME: pad_gpio_26_io 120
rtd_maskl(0xB8000820, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AA16 << 4) | (RTD18X5_BGA459_PIN_AA16_UP << 3) | (RTD18X5_BGA459_PIN_AA16_PD << 2) |(RTD18X5_BGA459_PIN_AA16_DS << 1) | (RTD18X5_BGA459_PIN_AA16_SR)) << 5));
if (RTD18X5_BGA459_PIN_AA16 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x2&0xf)<<5)); }; // 8: SC1_DATA0_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_AA16 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x4&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src4,<I/O>
// PAD_NAME: pad_gpio_27_io 121
rtd_maskl(0xB8000824, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AB16 << 4) | (RTD18X5_BGA459_PIN_AB16_UP << 3) | (RTD18X5_BGA459_PIN_AB16_PD << 2) |(RTD18X5_BGA459_PIN_AB16_DS << 1) | (RTD18X5_BGA459_PIN_AB16_SR)) << 23));
// PAD_NAME: pad_gpio_28_io 122
rtd_maskl(0xB8000824, 0xFF803FFF, (((RTD18X5_BGA459_PIN_Y17 << 4) | (RTD18X5_BGA459_PIN_Y17_UP << 3) | (RTD18X5_BGA459_PIN_Y17_PD << 2) |(RTD18X5_BGA459_PIN_Y17_DS << 1) | (RTD18X5_BGA459_PIN_Y17_SR)) << 14));
if (RTD18X5_BGA459_PIN_Y17 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x2&0xf)<<10)); }; // 8: SC1_CD_SRC2,<I>
// PAD_NAME: pad_gpio_29_io 123
rtd_maskl(0xB800084C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_G23 << 4) | (RTD18X5_BGA459_PIN_G23_UP << 3) | (RTD18X5_BGA459_PIN_G23_PD << 2) |(RTD18X5_BGA459_PIN_G23_DS << 1) | (RTD18X5_BGA459_PIN_G23_SR)) << 23));
if (RTD18X5_BGA459_PIN_G23 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<25), ((0x2&0x3)<<25)); }; // 16: TP0_Data_bit2_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_G23 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x2&0x7)<<28)); }; // 7: SC0_CD_SRC2,<I>
// PAD_NAME: pad_gpio_30_io 124
rtd_maskl(0xB8000824, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AA17 << 4) | (RTD18X5_BGA459_PIN_AA17_UP << 3) | (RTD18X5_BGA459_PIN_AA17_PD << 2) |(RTD18X5_BGA459_PIN_AA17_DS << 1) | (RTD18X5_BGA459_PIN_AA17_SR)) << 5));
if (RTD18X5_BGA459_PIN_AA17 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<14), ((0x2&0x3)<<14)); }; // 16: PCMCIA_INPACK0_N_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AA17 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 6: CR_SD_CMD_SRC4,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_31_io 125
rtd_maskl(0xB8000828, 0x007FFFFF, (((RTD18X5_BGA459_PIN_Y16 << 4) | (RTD18X5_BGA459_PIN_Y16_UP << 3) | (RTD18X5_BGA459_PIN_Y16_PD << 2) |(RTD18X5_BGA459_PIN_Y16_DS << 1) | (RTD18X5_BGA459_PIN_Y16_SR)) << 23));
if (RTD18X5_BGA459_PIN_Y16 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<8), ((0x2&0x3)<<8)); }; // 16: PCMCIA_WAIT0_N_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y16 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x3&0xf)<<23)); }; // 6: CR_SD_WP_SRC3,<I>,<HS>
// PAD_NAME: pad_gpio_32_io 126
rtd_maskl(0xB800084C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_H23 << 4) | (RTD18X5_BGA459_PIN_H23_UP << 3) | (RTD18X5_BGA459_PIN_H23_PD << 2) |(RTD18X5_BGA459_PIN_H23_DS << 1) | (RTD18X5_BGA459_PIN_H23_SR)) << 14));
if (RTD18X5_BGA459_PIN_H23 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<24), ((0x1&0x3)<<24)); }; // A: uart2_cts_n_src1,<I>
if (RTD18X5_BGA459_PIN_H23 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x3&0x7)<<13)); }; // 9: uart0_cts_n_src3,<I>
// PAD_NAME: pad_gpio_33_io 127
rtd_maskl(0xB800084C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_H24 << 4) | (RTD18X5_BGA459_PIN_H24_UP << 3) | (RTD18X5_BGA459_PIN_H24_PD << 2) |(RTD18X5_BGA459_PIN_H24_DS << 1) | (RTD18X5_BGA459_PIN_H24_SR)) << 5));
if (RTD18X5_BGA459_PIN_H24 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<26), ((0x2&0x3)<<26)); }; // 16: PCMCIA_D_bit2_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_H24 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x2&0x7)<<20)); }; // 8: uart1_rXdi_src2,<I>
// PAD_NAME: pad_gpio_34_io 128
rtd_maskl(0xB8000828, 0xFF803FFF, (((RTD18X5_BGA459_PIN_Y18 << 4) | (RTD18X5_BGA459_PIN_Y18_UP << 3) | (RTD18X5_BGA459_PIN_Y18_PD << 2) |(RTD18X5_BGA459_PIN_Y18_DS << 1) | (RTD18X5_BGA459_PIN_Y18_SR)) << 14));
if (RTD18X5_BGA459_PIN_Y18 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<29), ((0x2&0x3)<<29)); }; // 16: TP0_Data_bit0_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y18 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x4&0x7)<<19)); }; // 6: CR_SD_CD_SRC4,<I>,<HS>
if (RTD18X5_BGA459_PIN_Y18 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<15), ((0x0&0x3)<<15)); }; // 1: TP0_Data_bit7_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_36_io 129
rtd_maskl(0xB800082C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AA18 << 4) | (RTD18X5_BGA459_PIN_AA18_UP << 3) | (RTD18X5_BGA459_PIN_AA18_PD << 2) |(RTD18X5_BGA459_PIN_AA18_DS << 1) | (RTD18X5_BGA459_PIN_AA18_SR)) << 23));
if (RTD18X5_BGA459_PIN_AA18 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<9), ((0x2&0x3)<<9)); }; // 16: TP0_SYNC_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AA18 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x2&0x7)<<15)); }; // 6: CR_SD_Data_bit0_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AA18 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<17), ((0x0&0x3)<<17)); }; // 1: TP0_Data_bit6_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_37_io 130
rtd_maskl(0xB800082C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AB18 << 4) | (RTD18X5_BGA459_PIN_AB18_UP << 3) | (RTD18X5_BGA459_PIN_AB18_PD << 2) |(RTD18X5_BGA459_PIN_AB18_DS << 1) | (RTD18X5_BGA459_PIN_AB18_SR)) << 14));
if (RTD18X5_BGA459_PIN_AB18 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<11), ((0x2&0x3)<<11)); }; // 16: TP0_VAL_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_AB18 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x2&0x7)<<11)); }; // 6: CR_SD_Data_bit1_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AB18 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<19), ((0x0&0x3)<<19)); }; // 1: TP0_Data_bit5_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_38_io 131
rtd_maskl(0xB800082C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AC15 << 4) | (RTD18X5_BGA459_PIN_AC15_UP << 3) | (RTD18X5_BGA459_PIN_AC15_PD << 2) |(RTD18X5_BGA459_PIN_AC15_DS << 1) | (RTD18X5_BGA459_PIN_AC15_SR)) << 5));
if (RTD18X5_BGA459_PIN_AC15 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<30), ((0x2&0x3)<<30)); }; // 16: PCMCIA_D_bit0_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AC15 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x2&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AC15 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<21), ((0x0&0x3)<<21)); }; // 1: TP0_Data_bit4_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_43_io 132
rtd_maskl(0xB8000834, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AD15 << 4) | (RTD18X5_BGA459_PIN_AD15_UP << 3) | (RTD18X5_BGA459_PIN_AD15_PD << 2) |(RTD18X5_BGA459_PIN_AD15_DS << 1) | (RTD18X5_BGA459_PIN_AD15_SR)) << 14));
if (RTD18X5_BGA459_PIN_AD15 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x3&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC2,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_AD15 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<23), ((0x0&0x3)<<23)); }; // 1: TP0_Data_bit3_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_55_io 133
rtd_maskl(0xB8000844, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AD19 << 4) | (RTD18X5_BGA459_PIN_AD19_UP << 3) | (RTD18X5_BGA459_PIN_AD19_PD << 2) |(RTD18X5_BGA459_PIN_AD19_DS << 1) | (RTD18X5_BGA459_PIN_AD19_SR)) << 14));
if (RTD18X5_BGA459_PIN_AD19 == 0x12) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x3&0x1f)<<7)); }; // 12: I2C0_SCL_SRC3,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_92_io:2 134
rtd_maskl(0xB800085C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_D15 << 4) | (RTD18X5_BGA459_PIN_D15_UP << 3) | (RTD18X5_BGA459_PIN_D15_PD << 2) |(RTD18X5_BGA459_PIN_D15_DS << 1) | (RTD18X5_BGA459_PIN_D15_SR)) << 23));
if (RTD18X5_BGA459_PIN_D15 == 0x15) { rtd_maskl(0xb8000924, ~((0x3)<<23), ((0x1&0x3)<<23)); }; // 15:
if (RTD18X5_BGA459_PIN_D15 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x2&0x7)<<16)); }; // 14:
if (RTD18X5_BGA459_PIN_D15 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x7&0xf)<<8)); }; // F: I2C2_SCL_SRC7,<I/O
if (RTD18X5_BGA459_PIN_D15 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x3&0x7)<<20)); }; // 9: uart1_rXdi_src3,<I>
if (RTD18X5_BGA459_PIN_D15 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x1&0x7)<<16)); }; // 8: uart0_rXdi_src1,<I>
if (RTD18X5_BGA459_PIN_D15 == 0x6) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x6&0x7)<<24)); }; // 6: SC0_DATA0_SRC6,<I/O>
if (RTD18X5_BGA459_PIN_D15 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x2&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src2,<I/O>
// PAD_NAME: pad_gpio_93_io:2 135
rtd_maskl(0xB800085C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_B17 << 4) | (RTD18X5_BGA459_PIN_B17_UP << 3) | (RTD18X5_BGA459_PIN_B17_PD << 2) |(RTD18X5_BGA459_PIN_B17_DS << 1) | (RTD18X5_BGA459_PIN_B17_SR)) << 14));
if (RTD18X5_BGA459_PIN_B17 == 0x15) { rtd_maskl(0xb8000924, ~((0x3)<<21), ((0x1&0x3)<<21)); }; // 15:
if (RTD18X5_BGA459_PIN_B17 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x1&0x7)<<18)); }; // 10: P_COL_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_B17 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x7&0xf)<<8)); }; // F: I2C2_SDA_SRC7,<I/O>
if (RTD18X5_BGA459_PIN_B17 == 0x7) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x3&0xf)<<5)); }; // 7: SC1_DATA0_SRC3,<I/O>
if (RTD18X5_BGA459_PIN_B17 == 0x6) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x6&0x7)<<28)); }; // 6: SC0_CD_SRC6,<I>
// PAD_NAME: pad_gpio_94_io 136
rtd_maskl(0xB800085C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C16 << 4) | (RTD18X5_BGA459_PIN_C16_UP << 3) | (RTD18X5_BGA459_PIN_C16_PD << 2) |(RTD18X5_BGA459_PIN_C16_DS << 1) | (RTD18X5_BGA459_PIN_C16_SR)) << 5));
if (RTD18X5_BGA459_PIN_C16 == 0x15) { rtd_maskl(0xb8000928, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // 15: PCMCIA_D_bit6_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C16 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<21), ((0x1&0x3)<<21)); }; // 10: P_MDIO_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C16 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x3&0x7)<<26)); }; // 9: uart2_rXdi_src3,<I>
if (RTD18X5_BGA459_PIN_C16 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x0&0x7)<<15)); }; // 5: CR_SD_Data_bit0_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C16 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<22), ((0x0&0x3)<<22)); }; // 1: PCMCIA_D_bit4_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_95_io 137
rtd_maskl(0xB8000860, 0x007FFFFF, (((RTD18X5_BGA459_PIN_B15 << 4) | (RTD18X5_BGA459_PIN_B15_UP << 3) | (RTD18X5_BGA459_PIN_B15_PD << 2) |(RTD18X5_BGA459_PIN_B15_DS << 1) | (RTD18X5_BGA459_PIN_B15_SR)) << 23));
if (RTD18X5_BGA459_PIN_B15 == 0x15) { rtd_maskl(0xb8000928, ~((0x3)<<16), ((0x1&0x3)<<16)); }; // 15: PCMCIA_D_bit7_SRC1,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_B15 == 0xE) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xf&0x1f)<<7)); }; // E: I2C0_SCL_SRC15,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_96_io 138
rtd_maskl(0xB8000860, 0xFF803FFF, (((RTD18X5_BGA459_PIN_B14 << 4) | (RTD18X5_BGA459_PIN_B14_UP << 3) | (RTD18X5_BGA459_PIN_B14_PD << 2) |(RTD18X5_BGA459_PIN_B14_DS << 1) | (RTD18X5_BGA459_PIN_B14_SR)) << 14));
if (RTD18X5_BGA459_PIN_B14 == 0x15) { rtd_maskl(0xb8000924, ~((0x3)<<19), ((0x1&0x3)<<19)); }; // 15:
if (RTD18X5_BGA459_PIN_B14 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x1&0x7)<<17)); }; // 10: P_RXER_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_B14 == 0xE) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xf&0x1f)<<7)); }; // E: I2C0_SDA_SRC15,<I/O>
if (RTD18X5_BGA459_PIN_B14 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x0&0x7)<<11)); }; // 5: CR_SD_Data_bit1_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_B14 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<20), ((0x0&0x3)<<20)); }; // 1: PCMCIA_D_bit5_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_97_io 139
rtd_maskl(0xB8000860, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C11 << 4) | (RTD18X5_BGA459_PIN_C11_UP << 3) | (RTD18X5_BGA459_PIN_C11_PD << 2) |(RTD18X5_BGA459_PIN_C11_DS << 1) | (RTD18X5_BGA459_PIN_C11_SR)) << 5));
if (RTD18X5_BGA459_PIN_C11 == 0x15) { rtd_maskl(0xb8000924, ~((0x3)<<17), ((0x1&0x3)<<17)); }; // 15: TP0_Data_bit6_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C11 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x7&0xf)<<10)); }; // 14: SC1_CD_SRC7,<I>
if (RTD18X5_BGA459_PIN_C11 == 0x11) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x1&0x3)<<15)); }; // 11: P_CRS_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C11 == 0x8) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x4&0x7)<<24)); }; // 8: SC0_DATA0_SRC4,<I/O>
if (RTD18X5_BGA459_PIN_C11 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 7: SC0_CD_SRC3,<I>
// PAD_NAME: pad_gpio_98_io 140
rtd_maskl(0xB8000864, 0x007FFFFF, (((RTD18X5_BGA459_PIN_D16 << 4) | (RTD18X5_BGA459_PIN_D16_UP << 3) | (RTD18X5_BGA459_PIN_D16_PD << 2) |(RTD18X5_BGA459_PIN_D16_DS << 1) | (RTD18X5_BGA459_PIN_D16_SR)) << 23));
if (RTD18X5_BGA459_PIN_D16 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x1&0x7)<<11)); }; // 10: P_RXDV_SRC1,<I>,<HS>
// PAD_NAME: pad_gpio_99_io 141
rtd_maskl(0xB8000864, 0xFF803FFF, (((RTD18X5_BGA459_PIN_C13 << 4) | (RTD18X5_BGA459_PIN_C13_UP << 3) | (RTD18X5_BGA459_PIN_C13_PD << 2) |(RTD18X5_BGA459_PIN_C13_DS << 1) | (RTD18X5_BGA459_PIN_C13_SR)) << 14));
if (RTD18X5_BGA459_PIN_C13 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x1&0x3)<<8)); }; // 10: P_RXD0_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C13 == 0xB) { rtd_maskl(0xb8000904, ~((0x1)<<31), ((0x1&0x1)<<31)); }; // B: SPDIF_IN_src1,<I>
if (RTD18X5_BGA459_PIN_C13 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x5&0x7)<<28)); }; // 5: CR_SD_CMD_SRC5,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C13 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 2: EMMC_CMD_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_100_io 142
rtd_maskl(0xB8000864, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C17 << 4) | (RTD18X5_BGA459_PIN_C17_UP << 3) | (RTD18X5_BGA459_PIN_C17_PD << 2) |(RTD18X5_BGA459_PIN_C17_DS << 1) | (RTD18X5_BGA459_PIN_C17_SR)) << 5));
if (RTD18X5_BGA459_PIN_C17 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<5), ((0x1&0x3)<<5)); }; // 10: P_RXD1_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C17 == 0x5) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x0&0xf)<<23)); }; // 5: CR_SD_WP_SRC8,<I>,<HS>
if (RTD18X5_BGA459_PIN_C17 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<14), ((0x0&0x3)<<14)); }; // 1: PCMCIA_INPACK0_N_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_101_io 143
rtd_maskl(0xB8000868, 0x007FFFFF, (((RTD18X5_BGA459_PIN_C14 << 4) | (RTD18X5_BGA459_PIN_C14_UP << 3) | (RTD18X5_BGA459_PIN_C14_PD << 2) |(RTD18X5_BGA459_PIN_C14_DS << 1) | (RTD18X5_BGA459_PIN_C14_SR)) << 23));
if (RTD18X5_BGA459_PIN_C14 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x1&0x7)<<1)); }; // 10: P_RXD2_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C14 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x0&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_C14 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x6&0x7)<<19)); }; // 5: CR_SD_CD_SRC6,<I>,<HS>
if (RTD18X5_BGA459_PIN_C14 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // 1: PCMCIA_D_bit6_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_102_io 144
rtd_maskl(0xB8000868, 0xFF803FFF, (((RTD18X5_BGA459_PIN_D13 << 4) | (RTD18X5_BGA459_PIN_D13_UP << 3) | (RTD18X5_BGA459_PIN_D13_PD << 2) |(RTD18X5_BGA459_PIN_D13_DS << 1) | (RTD18X5_BGA459_PIN_D13_SR)) << 14));
if (RTD18X5_BGA459_PIN_D13 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xb&0x1f)<<7)); }; // 11: I2C0_SCL_SRC11,<I/O>
if (RTD18X5_BGA459_PIN_D13 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 10: P_RXD3_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_D13 == 0xF) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x1&0x7)<<4)); }; // F: I2C1_SCL_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_D13 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x0&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_D13 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x4&0x7)<<15)); }; // 5: CR_SD_Data_bit0_SRC4,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_D13 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<16), ((0x0&0x3)<<16)); }; // 1: PCMCIA_D_bit7_SRC0,<I/O>,<HS>
// PAD_NAME: pad_gpio_103_io 145
rtd_maskl(0xB8000868, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C12 << 4) | (RTD18X5_BGA459_PIN_C12_UP << 3) | (RTD18X5_BGA459_PIN_C12_PD << 2) |(RTD18X5_BGA459_PIN_C12_DS << 1) | (RTD18X5_BGA459_PIN_C12_SR)) << 5));
if (RTD18X5_BGA459_PIN_C12 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xb&0x1f)<<7)); }; // 11: I2C0_SDA_SRC11,<I/O>
if (RTD18X5_BGA459_PIN_C12 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<25), ((0x1&0x3)<<25)); }; // 10: P_RXC_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_C12 == 0xF) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x1&0x7)<<4)); }; // F: I2C1_SDA_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_C12 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x4&0x7)<<11)); }; // 5: CR_SD_Data_bit1_SRC4,<I/O>,<HS>
// PAD_NAME: pad_gpio_104_io 146
rtd_maskl(0xB800086C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_F10 << 4) | (RTD18X5_BGA459_PIN_F10_UP << 3) | (RTD18X5_BGA459_PIN_F10_PD << 2) |(RTD18X5_BGA459_PIN_F10_DS << 1) | (RTD18X5_BGA459_PIN_F10_SR)) << 23));
if (RTD18X5_BGA459_PIN_F10 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<22), ((0x1&0x3)<<22)); }; // 10: P_TXC_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_F10 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<12), ((0x0&0x3)<<12)); }; // 1: PCMCIA_CD0_N_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_F10 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x5&0x7)<<7)); }; // 5: CR_SD_Data_bit2_SRC5,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_105_io 147
rtd_maskl(0xB800086C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_D12 << 4) | (RTD18X5_BGA459_PIN_D12_UP << 3) | (RTD18X5_BGA459_PIN_D12_PD << 2) |(RTD18X5_BGA459_PIN_D12_DS << 1) | (RTD18X5_BGA459_PIN_D12_SR)) << 14));
if (RTD18X5_BGA459_PIN_D12 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x5&0x7)<<3)); }; // 5: CR_SD_Data_bit3_SRC5,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_D12 == 0x1) { rtd_maskl(0xb8000928, ~((0x3)<<10), ((0x0&0x3)<<10)); }; // 1: PCMCIA_IREQ0_N_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_142_io 148
rtd_maskl(0xB8000850, 0xFF803FFF, (((RTD18X5_BGA459_PIN_H25 << 4) | (RTD18X5_BGA459_PIN_H25_UP << 3) | (RTD18X5_BGA459_PIN_H25_PD << 2) |(RTD18X5_BGA459_PIN_H25_DS << 1) | (RTD18X5_BGA459_PIN_H25_SR)) << 14));
if (RTD18X5_BGA459_PIN_H25 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<0), ((0x2&0x3)<<0)); }; // 16: PCMCIA_CD1_N_SRC2,<I>
// PAD_NAME: pad_gpio_143_io 149
rtd_maskl(0xB8000848, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AC17 << 4) | (RTD18X5_BGA459_PIN_AC17_UP << 3) | (RTD18X5_BGA459_PIN_AC17_PD << 2) |(RTD18X5_BGA459_PIN_AC17_DS << 1) | (RTD18X5_BGA459_PIN_AC17_SR)) << 23));
if (RTD18X5_BGA459_PIN_AC17 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x5&0x7)<<19)); }; // 6: CR_SD_CD_SRC5,<I>,<HS>
// PAD_NAME: pad_gpio_145_io 150
rtd_maskl(0xB8000894, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_M4 << 4) | (RTD18X5_BGA459_PIN_M4_UP << 3) | (RTD18X5_BGA459_PIN_M4_PD << 2) |(RTD18X5_BGA459_PIN_M4_DS << 1) | (RTD18X5_BGA459_PIN_M4_SR)) << 5));
// PAD_NAME: pad_gpio_146_io 151
rtd_maskl(0xB8000898, 0x007FFFFF, (((RTD18X5_BGA459_PIN_N5 << 4) | (RTD18X5_BGA459_PIN_N5_UP << 3) | (RTD18X5_BGA459_PIN_N5_PD << 2) |(RTD18X5_BGA459_PIN_N5_DS << 1) | (RTD18X5_BGA459_PIN_N5_SR)) << 23));
if (RTD18X5_BGA459_PIN_N5 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x4&0x7)<<8)); }; // 15: GSPI_CS_N_SRC4,<I/O>,<HS>
// PAD_NAME: pad_gpio_147_io 152
rtd_maskl(0xB8000898, 0xFF803FFF, (((RTD18X5_BGA459_PIN_N4 << 4) | (RTD18X5_BGA459_PIN_N4_UP << 3) | (RTD18X5_BGA459_PIN_N4_PD << 2) |(RTD18X5_BGA459_PIN_N4_DS << 1) | (RTD18X5_BGA459_PIN_N4_SR)) << 14));
if (RTD18X5_BGA459_PIN_N4 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x4&0x7)<<16)); }; // 15: GSPI_SCLK_SRC4,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_148_io 153
rtd_maskl(0xB8000898, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_N6 << 4) | (RTD18X5_BGA459_PIN_N6_UP << 3) | (RTD18X5_BGA459_PIN_N6_PD << 2) |(RTD18X5_BGA459_PIN_N6_DS << 1) | (RTD18X5_BGA459_PIN_N6_SR)) << 5));
if (RTD18X5_BGA459_PIN_N6 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x4&0x7)<<4)); }; // 15: GSPI_DO_SRC4,<I/O>,<HS>
// PAD_NAME: pad_gpio_149_io 154
rtd_maskl(0xB800089C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_P5 << 4) | (RTD18X5_BGA459_PIN_P5_UP << 3) | (RTD18X5_BGA459_PIN_P5_PD << 2) |(RTD18X5_BGA459_PIN_P5_DS << 1) | (RTD18X5_BGA459_PIN_P5_SR)) << 23));
if (RTD18X5_BGA459_PIN_P5 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x4&0x7)<<12)); }; // 15: GSPI_DI_SRC4,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_P5 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x0&0x7)<<18)); }; // 10: P_COL_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_P5 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<2), ((0x0&0x1)<<2)); }; // 3: PCMCIA_WAIT1_N_SRC0,<I>
// PAD_NAME: pad_gpio_150_io 155
rtd_maskl(0xB8000958, 0xFF803FFF, (((RTD18X5_BGA459_PIN_A12 << 4) | (RTD18X5_BGA459_PIN_A12_UP << 3) | (RTD18X5_BGA459_PIN_A12_PD << 2) |(RTD18X5_BGA459_PIN_A12_DS << 1) | (RTD18X5_BGA459_PIN_A12_SR)) << 14));
if (RTD18X5_BGA459_PIN_A12 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x6&0x7)<<28)); }; // 2: EMMC_CMD_SRC6,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_151_io 156
rtd_maskl(0xB8000958, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_A16 << 4) | (RTD18X5_BGA459_PIN_A16_UP << 3) | (RTD18X5_BGA459_PIN_A16_PD << 2) |(RTD18X5_BGA459_PIN_A16_DS << 1) | (RTD18X5_BGA459_PIN_A16_SR)) << 5));
if (RTD18X5_BGA459_PIN_A16 == 0x15) { rtd_maskl(0xb8000928, ~((0x3)<<30), ((0x1&0x3)<<30)); }; // 15: PCMCIA_D_bit0_SRC1,<I/O>,<HS>
// PAD_NAME: pad_gpio_152_io 157
rtd_maskl(0xB80008A0, 0x007FFFFF, (((RTD18X5_BGA459_PIN_B13 << 4) | (RTD18X5_BGA459_PIN_B13_UP << 3) | (RTD18X5_BGA459_PIN_B13_PD << 2) |(RTD18X5_BGA459_PIN_B13_DS << 1) | (RTD18X5_BGA459_PIN_B13_SR)) << 23));
if (RTD18X5_BGA459_PIN_B13 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x2&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_153_io 158
rtd_maskl(0xB80008A0, 0xFF803FFF, (((RTD18X5_BGA459_PIN_B12 << 4) | (RTD18X5_BGA459_PIN_B12_UP << 3) | (RTD18X5_BGA459_PIN_B12_PD << 2) |(RTD18X5_BGA459_PIN_B12_DS << 1) | (RTD18X5_BGA459_PIN_B12_SR)) << 14));
if (RTD18X5_BGA459_PIN_B12 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<20), ((0x2&0x3)<<20)); }; // 2: EMMC_Data_bit3_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_157_io 159
rtd_maskl(0xB80008A4, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_D10 << 4) | (RTD18X5_BGA459_PIN_D10_UP << 3) | (RTD18X5_BGA459_PIN_D10_PD << 2) |(RTD18X5_BGA459_PIN_D10_DS << 1) | (RTD18X5_BGA459_PIN_D10_SR)) << 5));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_169_io 160
rtd_maskl(0xB8000874, 0xFF803FFF, (((RTD18X5_BGA459_PIN_C15 << 4) | (RTD18X5_BGA459_PIN_C15_UP << 3) | (RTD18X5_BGA459_PIN_C15_PD << 2) |(RTD18X5_BGA459_PIN_C15_DS << 1) | (RTD18X5_BGA459_PIN_C15_SR)) << 14));
if (RTD18X5_BGA459_PIN_C15 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<17), ((0x0&0x3)<<17)); }; // A: USB_PWR_FLAG2_SRC0,<I>
if (RTD18X5_BGA459_PIN_C15 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x2&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_170_io 161
rtd_maskl(0xB8000874, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_C9 << 4) | (RTD18X5_BGA459_PIN_C9_UP << 3) | (RTD18X5_BGA459_PIN_C9_PD << 2) |(RTD18X5_BGA459_PIN_C9_DS << 1) | (RTD18X5_BGA459_PIN_C9_SR)) << 5));
if (RTD18X5_BGA459_PIN_C9 == 0xF) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x3&0x7)<<4)); }; // F: I2C1_SDA_SRC3,<I/O>
// PAD_NAME: pad_gpio_171_io 162
rtd_maskl(0xB8000878, 0x007FFFFF, (((RTD18X5_BGA459_PIN_F11 << 4) | (RTD18X5_BGA459_PIN_F11_UP << 3) | (RTD18X5_BGA459_PIN_F11_PD << 2) |(RTD18X5_BGA459_PIN_F11_DS << 1) | (RTD18X5_BGA459_PIN_F11_SR)) << 23));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_173_io 163
rtd_maskl(0xB8000878, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_A15 << 4) | (RTD18X5_BGA459_PIN_A15_UP << 3) | (RTD18X5_BGA459_PIN_A15_PD << 2) |(RTD18X5_BGA459_PIN_A15_DS << 1) | (RTD18X5_BGA459_PIN_A15_SR)) << 5));
if (RTD18X5_BGA459_PIN_A15 == 0x12) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xc&0xf)<<8)); }; // 12: I2C2_SCL_SRC12,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_174_io 164
rtd_maskl(0xB800087C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_B16 << 4) | (RTD18X5_BGA459_PIN_B16_UP << 3) | (RTD18X5_BGA459_PIN_B16_PD << 2) |(RTD18X5_BGA459_PIN_B16_DS << 1) | (RTD18X5_BGA459_PIN_B16_SR)) << 23));
if (RTD18X5_BGA459_PIN_B16 == 0x15) { rtd_maskl(0xb8000924, ~((0x3)<<15), ((0x1&0x3)<<15)); }; // 15: TP0_Data_bit7_SRC1,<I>,<HS>
if (RTD18X5_BGA459_PIN_B16 == 0x12) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xc&0xf)<<8)); }; // 12: I2C2_SDA_SRC12,<I/O>
// PAD_NAME: pad_gpio_181_io 165
rtd_maskl(0xB8000884, 0xFF803FFF, (((RTD18X5_BGA459_PIN_B11 << 4) | (RTD18X5_BGA459_PIN_B11_UP << 3) | (RTD18X5_BGA459_PIN_B11_PD << 2) |(RTD18X5_BGA459_PIN_B11_DS << 1) | (RTD18X5_BGA459_PIN_B11_SR)) << 14));
if (RTD18X5_BGA459_PIN_B11 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<22), ((0x2&0x3)<<22)); }; // 2: EMMC_Data_bit2_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_182_io 166
rtd_maskl(0xB8000884, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_A13 << 4) | (RTD18X5_BGA459_PIN_A13_UP << 3) | (RTD18X5_BGA459_PIN_A13_PD << 2) |(RTD18X5_BGA459_PIN_A13_DS << 1) | (RTD18X5_BGA459_PIN_A13_SR)) << 5));
if (RTD18X5_BGA459_PIN_A13 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x2&0x3)<<11)); }; // 2: EMMC_Data_bit7_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_183_io 167
rtd_maskl(0xB8000888, 0x007FFFFF, (((RTD18X5_BGA459_PIN_A10 << 4) | (RTD18X5_BGA459_PIN_A10_UP << 3) | (RTD18X5_BGA459_PIN_A10_PD << 2) |(RTD18X5_BGA459_PIN_A10_DS << 1) | (RTD18X5_BGA459_PIN_A10_SR)) << 23));
if (RTD18X5_BGA459_PIN_A10 == 0xF) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x3&0x7)<<4)); }; // F: I2C1_SCL_SRC3,<I/O>
// PAD_NAME: pad_gpio_184_io 168
rtd_maskl(0xB8000888, 0xFF803FFF, (((RTD18X5_BGA459_PIN_F12 << 4) | (RTD18X5_BGA459_PIN_F12_UP << 3) | (RTD18X5_BGA459_PIN_F12_PD << 2) |(RTD18X5_BGA459_PIN_F12_DS << 1) | (RTD18X5_BGA459_PIN_F12_SR)) << 14));
if (RTD18X5_BGA459_PIN_F12 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<26), ((0x2&0x3)<<26)); }; // 2: EMMC_Data_bit0_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_185_io 169
rtd_maskl(0xB8000888, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_E12 << 4) | (RTD18X5_BGA459_PIN_E12_UP << 3) | (RTD18X5_BGA459_PIN_E12_PD << 2) |(RTD18X5_BGA459_PIN_E12_DS << 1) | (RTD18X5_BGA459_PIN_E12_SR)) << 5));
if (RTD18X5_BGA459_PIN_E12 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<24), ((0x2&0x3)<<24)); }; // 2: EMMC_Data_bit1_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_188_io 170
rtd_maskl(0xB800088C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_E11 << 4) | (RTD18X5_BGA459_PIN_E11_UP << 3) | (RTD18X5_BGA459_PIN_E11_PD << 2) |(RTD18X5_BGA459_PIN_E11_DS << 1) | (RTD18X5_BGA459_PIN_E11_SR)) << 5));
if (RTD18X5_BGA459_PIN_E11 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x2&0x3)<<15)); }; // 2: EMMC_Data_bit5_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_189_io 171
rtd_maskl(0xB8000890, 0x007FFFFF, (((RTD18X5_BGA459_PIN_K4 << 4) | (RTD18X5_BGA459_PIN_K4_UP << 3) | (RTD18X5_BGA459_PIN_K4_PD << 2) |(RTD18X5_BGA459_PIN_K4_DS << 1) | (RTD18X5_BGA459_PIN_K4_SR)) << 23));
if (RTD18X5_BGA459_PIN_K4 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x0&0x7)<<1)); }; // 10: P_RXD2_SRC0,<I>,<HS>
// PAD_NAME: pad_gpio_190_io 172
rtd_maskl(0xB8000890, 0xFF803FFF, (((RTD18X5_BGA459_PIN_L6 << 4) | (RTD18X5_BGA459_PIN_L6_UP << 3) | (RTD18X5_BGA459_PIN_L6_PD << 2) |(RTD18X5_BGA459_PIN_L6_DS << 1) | (RTD18X5_BGA459_PIN_L6_SR)) << 14));
if (RTD18X5_BGA459_PIN_L6 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 10: P_RXD3_SRC0,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_191_io 173
rtd_maskl(0xB8000890, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_L5 << 4) | (RTD18X5_BGA459_PIN_L5_UP << 3) | (RTD18X5_BGA459_PIN_L5_PD << 2) |(RTD18X5_BGA459_PIN_L5_DS << 1) | (RTD18X5_BGA459_PIN_L5_SR)) << 5));
if (RTD18X5_BGA459_PIN_L5 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<25), ((0x0&0x3)<<25)); }; // 10: P_RXC_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_L5 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x4&0xf)<<10)); }; // 8: SC1_CD_SRC4,<I>
if (RTD18X5_BGA459_PIN_L5 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 7: SC0_CD_SRC1,<I>
// PAD_NAME: pad_gpio_197_io 174
rtd_maskl(0xB8000948, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD9 << 4) | (RTD18X5_BGA459_PIN_AD9_UP << 3) | (RTD18X5_BGA459_PIN_AD9_PD << 2) |(RTD18X5_BGA459_PIN_AD9_DS << 1) | (RTD18X5_BGA459_PIN_AD9_SR)) << 23));
if (RTD18X5_BGA459_PIN_AD9 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<24), ((0x2&0x3)<<24)); }; // 16: PCMCIA_D_bit3_SRC2,<I/O>,<HS>
// PAD_NAME: pad_gpio_198_io 175
rtd_maskl(0xB8000948, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AA10 << 4) | (RTD18X5_BGA459_PIN_AA10_UP << 3) | (RTD18X5_BGA459_PIN_AA10_PD << 2) |(RTD18X5_BGA459_PIN_AA10_DS << 1) | (RTD18X5_BGA459_PIN_AA10_SR)) << 14));
if (RTD18X5_BGA459_PIN_AA10 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<19), ((0x2&0x3)<<19)); }; // 16: TP0_Data_bit5_SRC2,<I>,<HS>
// PAD_NAME: pad_gpio_199_io 176
rtd_maskl(0xB8000948, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AD10 << 4) | (RTD18X5_BGA459_PIN_AD10_UP << 3) | (RTD18X5_BGA459_PIN_AD10_PD << 2) |(RTD18X5_BGA459_PIN_AD10_DS << 1) | (RTD18X5_BGA459_PIN_AD10_SR)) << 5));
if (RTD18X5_BGA459_PIN_AD10 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<18), ((0x2&0x3)<<18)); }; // 16: PCMCIA_D_bit6_SRC2,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_200_io 177
rtd_maskl(0xB800094C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AC11 << 4) | (RTD18X5_BGA459_PIN_AC11_UP << 3) | (RTD18X5_BGA459_PIN_AC11_PD << 2) |(RTD18X5_BGA459_PIN_AC11_DS << 1) | (RTD18X5_BGA459_PIN_AC11_SR)) << 23));
// PAD_NAME: pad_gpio_201_io 178
rtd_maskl(0xB800094C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AE11 << 4) | (RTD18X5_BGA459_PIN_AE11_UP << 3) | (RTD18X5_BGA459_PIN_AE11_PD << 2) |(RTD18X5_BGA459_PIN_AE11_DS << 1) | (RTD18X5_BGA459_PIN_AE11_SR)) << 14));
// PAD_NAME: pad_gpio_202_io 179
rtd_maskl(0xB800094C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_AB13 << 4) | (RTD18X5_BGA459_PIN_AB13_UP << 3) | (RTD18X5_BGA459_PIN_AB13_PD << 2) |(RTD18X5_BGA459_PIN_AB13_DS << 1) | (RTD18X5_BGA459_PIN_AB13_SR)) << 5));
// PAD_NAME: pad_gpio_203_io 180
rtd_maskl(0xB8000950, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AD16 << 4) | (RTD18X5_BGA459_PIN_AD16_UP << 3) | (RTD18X5_BGA459_PIN_AD16_PD << 2) |(RTD18X5_BGA459_PIN_AD16_DS << 1) | (RTD18X5_BGA459_PIN_AD16_SR)) << 23));
// PAD_NAME: pad_gpio_204_io 181
rtd_maskl(0xB8000950, 0xFF803FFF, (((RTD18X5_BGA459_PIN_AA11 << 4) | (RTD18X5_BGA459_PIN_AA11_UP << 3) | (RTD18X5_BGA459_PIN_AA11_PD << 2) |(RTD18X5_BGA459_PIN_AA11_DS << 1) | (RTD18X5_BGA459_PIN_AA11_SR)) << 14));
// PAD_NAME: pad_gpio_205_io 182
rtd_maskl(0xB8000950, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_Y13 << 4) | (RTD18X5_BGA459_PIN_Y13_UP << 3) | (RTD18X5_BGA459_PIN_Y13_PD << 2) |(RTD18X5_BGA459_PIN_Y13_DS << 1) | (RTD18X5_BGA459_PIN_Y13_SR)) << 5));
// PAD_NAME: pad_gpio_206_io 183
rtd_maskl(0xB8000954, 0x007FFFFF, (((RTD18X5_BGA459_PIN_AA14 << 4) | (RTD18X5_BGA459_PIN_AA14_UP << 3) | (RTD18X5_BGA459_PIN_AA14_PD << 2) |(RTD18X5_BGA459_PIN_AA14_DS << 1) | (RTD18X5_BGA459_PIN_AA14_SR)) << 23));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_25_io 184
rtd_maskl(0xB8060240, 0xFF803FFF, (((RTD18X5_BGA459_PIN_E8 << 4) | (RTD18X5_BGA459_PIN_E8_UP << 3) | (RTD18X5_BGA459_PIN_E8_PD << 2) |(RTD18X5_BGA459_PIN_E8_DS << 1) | (RTD18X5_BGA459_PIN_E8_SR)) << 14));
if (RTD18X5_BGA459_PIN_E8 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x6&0x7)<<13)); }; // 15:
if (RTD18X5_BGA459_PIN_E8 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x1&0x3)<<29)); }; // 11: VFD_D_SRC1,<I/O>
if (RTD18X5_BGA459_PIN_E8 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x5&0xf)<<8)); }; // F: I2C2_SCL_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_E8 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x2&0x7)<<28)); }; // 6: CR_SD_CMD_SRC2,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_26_io 185
rtd_maskl(0xB8060240, 0x007FFFFF, (((RTD18X5_BGA459_PIN_A3 << 4) | (RTD18X5_BGA459_PIN_A3_UP << 3) | (RTD18X5_BGA459_PIN_A3_PD << 2) |(RTD18X5_BGA459_PIN_A3_DS << 1) | (RTD18X5_BGA459_PIN_A3_SR)) << 23));
if (RTD18X5_BGA459_PIN_A3 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x6&0x7)<<9)); }; // 15:
if (RTD18X5_BGA459_PIN_A3 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x2&0x3)<<29)); }; // 11:
if (RTD18X5_BGA459_PIN_A3 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // 10: P_MDIO_SRC2,<I/
if (RTD18X5_BGA459_PIN_A3 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x5&0xf)<<8)); }; // F: I2C2_SDA_SRC5,<I/O>
if (RTD18X5_BGA459_PIN_A3 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<24), ((0x1&0x1)<<24)); }; // 0: TP1_Data_bit0_SRC1,<I>,<HS>
// PAD_NAME: pad_st_gpio_27_io 186
rtd_maskl(0xB806023C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_B3 << 4) | (RTD18X5_BGA459_PIN_B3_UP << 3) | (RTD18X5_BGA459_PIN_B3_PD << 2) |(RTD18X5_BGA459_PIN_B3_DS << 1) | (RTD18X5_BGA459_PIN_B3_SR)) << 5));
if (RTD18X5_BGA459_PIN_B3 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x2&0x7)<<2)); }; // 9: irrX_src2,<I>
if (RTD18X5_BGA459_PIN_B3 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x0&0xf)<<5)); }; // 8: SC1_DATA0_SRC0,<I/O>
if (RTD18X5_BGA459_PIN_B3 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<30), ((0x1&0x1)<<30)); }; // 0: TP1_CLK_SRC1,<I>,<HS>
// PAD_NAME: pad_st_gpio_28_io 187
rtd_maskl(0xB806023C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_A2 << 4) | (RTD18X5_BGA459_PIN_A2_UP << 3) | (RTD18X5_BGA459_PIN_A2_PD << 2) |(RTD18X5_BGA459_PIN_A2_DS << 1) | (RTD18X5_BGA459_PIN_A2_SR)) << 14));
if (RTD18X5_BGA459_PIN_A2 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<5), ((0x2&0x3)<<5)); }; // 10: P_RXD1_SRC2,<I>,<HS>
if (RTD18X5_BGA459_PIN_A2 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x3&0x7)<<2)); }; // 9: irrX_src3,<I>
if (RTD18X5_BGA459_PIN_A2 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<8), ((0x1&0x1)<<8)); }; // 0: TP1_SYNC_SRC1,<I>,<HS>
// PAD_NAME: pad_st_gpio_29_io 188
rtd_maskl(0xB806023C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_B2 << 4) | (RTD18X5_BGA459_PIN_B2_UP << 3) | (RTD18X5_BGA459_PIN_B2_PD << 2) |(RTD18X5_BGA459_PIN_B2_DS << 1) | (RTD18X5_BGA459_PIN_B2_SR)) << 23));
if (RTD18X5_BGA459_PIN_B2 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x6&0xf)<<10)); }; // 8: SC1_CD_SRC6,<I>
if (RTD18X5_BGA459_PIN_B2 == 0x0) { rtd_maskl(0xb8000918, ~((0x1)<<26), ((0x1&0x1)<<26)); }; // 0: TP1_VAL_SRC1,<I>,<HS>
// PAD_NAME: pad_st_gpio_30_io 189
rtd_maskl(0xB8060238, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_E6 << 4) | (RTD18X5_BGA459_PIN_E6_UP << 3) | (RTD18X5_BGA459_PIN_E6_PD << 2) |(RTD18X5_BGA459_PIN_E6_DS << 1) | (RTD18X5_BGA459_PIN_E6_SR)) << 5));
if (RTD18X5_BGA459_PIN_E6 == 0x10) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xb&0xf)<<8)); }; // 10: I2C2_SCL_SRC11,<I/O>
if (RTD18X5_BGA459_PIN_E6 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xa&0x1f)<<7)); }; // F: I2C0_SCL_SRC10,<I/O>
if (RTD18X5_BGA459_PIN_E6 == 0xE) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x2&0x7)<<4)); }; // E: I2C1_SCL_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_E6 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x4&0xf)<<23)); }; // 6: CR_SD_WP_SRC4,<I>,<HS>
// PAD_NAME: pad_st_gpio_31_io 190
rtd_maskl(0xB8060238, 0xFF803FFF, (((RTD18X5_BGA459_PIN_F6 << 4) | (RTD18X5_BGA459_PIN_F6_UP << 3) | (RTD18X5_BGA459_PIN_F6_PD << 2) |(RTD18X5_BGA459_PIN_F6_DS << 1) | (RTD18X5_BGA459_PIN_F6_SR)) << 14));
if (RTD18X5_BGA459_PIN_F6 == 0x10) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xb&0xf)<<8)); }; // 10: I2C2_SDA_SRC11,<I/O>
if (RTD18X5_BGA459_PIN_F6 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xa&0x1f)<<7)); }; // F: I2C0_SDA_SRC10,<I/O>
if (RTD18X5_BGA459_PIN_F6 == 0xE) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x2&0x7)<<4)); }; // E: I2C1_SDA_SRC2,<I/O>
if (RTD18X5_BGA459_PIN_F6 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<24), ((0x0&0x3)<<24)); }; // A: uart2_cts_n_src0,<I>
if (RTD18X5_BGA459_PIN_F6 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x2&0x7)<<13)); }; // 9: uart0_cts_n_src2,<I>
// PAD_NAME: pad_st_gpio_32_io 191
rtd_maskl(0xB8060238, 0x007FFFFF, (((RTD18X5_BGA459_PIN_G6 << 4) | (RTD18X5_BGA459_PIN_G6_UP << 3) | (RTD18X5_BGA459_PIN_G6_PD << 2) |(RTD18X5_BGA459_PIN_G6_DS << 1) | (RTD18X5_BGA459_PIN_G6_SR)) << 23));
if (RTD18X5_BGA459_PIN_G6 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<21), ((0x0&0x3)<<21)); }; // 10: P_MDIO_SRC0,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_G6 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x2&0x7)<<26)); }; // 9: uart2_rXdi_src2,<I>
if (RTD18X5_BGA459_PIN_G6 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x5&0x7)<<2)); }; // 8: irrX_src5,<I>
// PAD_NAME: pad_st_gpio_33_io 192
rtd_maskl(0xB8060234, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_H6 << 4) | (RTD18X5_BGA459_PIN_H6_UP << 3) | (RTD18X5_BGA459_PIN_H6_PD << 2) |(RTD18X5_BGA459_PIN_H6_DS << 1) | (RTD18X5_BGA459_PIN_H6_SR)) << 5));
// PAD_NAME: pad_st_gpio_34_io 193
rtd_maskl(0xB8060234, 0xFF803FFF, (((RTD18X5_BGA459_PIN_J6 << 4) | (RTD18X5_BGA459_PIN_J6_UP << 3) | (RTD18X5_BGA459_PIN_J6_PD << 2) |(RTD18X5_BGA459_PIN_J6_DS << 1) | (RTD18X5_BGA459_PIN_J6_SR)) << 14));
if (RTD18X5_BGA459_PIN_J6 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x0&0x7)<<17)); }; // 10: P_RXER_SRC0,<I>,<HS>
// PAD_NAME: pad_st_gpio_36_io 195
rtd_maskl(0xB8060230, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_D8 << 4) | (RTD18X5_BGA459_PIN_D8_UP << 3) | (RTD18X5_BGA459_PIN_D8_PD << 2) |(RTD18X5_BGA459_PIN_D8_DS << 1) | (RTD18X5_BGA459_PIN_D8_SR)) << 5));
if (RTD18X5_BGA459_PIN_D8 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x3&0x7)<<16)); }; // 15: GSPI_SCLK_SRC3,<I/O>,<HS>
if (RTD18X5_BGA459_PIN_D8 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x3&0x3)<<29)); }; // 11: VFD_D_SRC3,<I/O>
if (RTD18X5_BGA459_PIN_D8 == 0x6) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x3&0x7)<<14)); }; // 6: ld_spi0_p2_sck_src3,<I/O>
if (RTD18X5_BGA459_PIN_D8 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x3&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src3,<I/O>
// PAD_NAME: pad_st_gpio_39_io 198
rtd_maskl(0xB806022C, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_B8 << 4) | (RTD18X5_BGA459_PIN_B8_UP << 3) | (RTD18X5_BGA459_PIN_B8_PD << 2) |(RTD18X5_BGA459_PIN_B8_DS << 1) | (RTD18X5_BGA459_PIN_B8_SR)) << 5));
if (RTD18X5_BGA459_PIN_B8 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x6&0x7)<<16)); }; // 9: uart0_rXdi_src6,<I>
if (RTD18X5_BGA459_PIN_B8 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<2), ((0x1&0x1)<<2)); }; // 3: PCMCIA_WAIT1_N_SRC1,<I>
// PAD_NAME: pad_st_gpio_40_io 199
rtd_maskl(0xB806022C, 0xFF803FFF, (((RTD18X5_BGA459_PIN_A8 << 4) | (RTD18X5_BGA459_PIN_A8_UP << 3) | (RTD18X5_BGA459_PIN_A8_PD << 2) |(RTD18X5_BGA459_PIN_A8_DS << 1) | (RTD18X5_BGA459_PIN_A8_SR)) << 14));
// PAD_NAME: pad_st_gpio_41_io 200
rtd_maskl(0xB806022C, 0x007FFFFF, (((RTD18X5_BGA459_PIN_J5 << 4) | (RTD18X5_BGA459_PIN_J5_UP << 3) | (RTD18X5_BGA459_PIN_J5_PD << 2) |(RTD18X5_BGA459_PIN_J5_DS << 1) | (RTD18X5_BGA459_PIN_J5_SR)) << 23));
if (RTD18X5_BGA459_PIN_J5 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x0&0x3)<<15)); }; // 10: P_CRS_SRC0,<I>,<HS>
// PAD_NAME: pad_st_gpio_42_io 201
rtd_maskl(0xB8060228, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_J4 << 4) | (RTD18X5_BGA459_PIN_J4_UP << 3) | (RTD18X5_BGA459_PIN_J4_PD << 2) |(RTD18X5_BGA459_PIN_J4_DS << 1) | (RTD18X5_BGA459_PIN_J4_SR)) << 5));
if (RTD18X5_BGA459_PIN_J4 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x0&0x7)<<11)); }; // 10: P_RXDV_SRC0,<I>,<HS>
if (RTD18X5_BGA459_PIN_J4 == 0x1) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x2&0x7)<<28)); }; // 1: EMMC_CMD_SRC2,<I/O>,<HS>
// PAD_NAME: pad_st_gpio_43_io 202
rtd_maskl(0xB8060228, 0xFF803FFF, (((RTD18X5_BGA459_PIN_K6 << 4) | (RTD18X5_BGA459_PIN_K6_UP << 3) | (RTD18X5_BGA459_PIN_K6_PD << 2) |(RTD18X5_BGA459_PIN_K6_DS << 1) | (RTD18X5_BGA459_PIN_K6_SR)) << 14));
if (RTD18X5_BGA459_PIN_K6 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x0&0x3)<<8)); }; // 10: P_RXD0_SRC0,<I>,<HS>
// PAD_NAME: pad_st_gpio_44_io 203
rtd_maskl(0xB8060228, 0x007FFFFF, (((RTD18X5_BGA459_PIN_K5 << 4) | (RTD18X5_BGA459_PIN_K5_UP << 3) | (RTD18X5_BGA459_PIN_K5_PD << 2) |(RTD18X5_BGA459_PIN_K5_DS << 1) | (RTD18X5_BGA459_PIN_K5_SR)) << 23));
if (RTD18X5_BGA459_PIN_K5 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<5), ((0x0&0x3)<<5)); }; // 10: P_RXD1_SRC0,<I>,<HS>
// PAD_NAME: PLT_P0_TXHN 204
rtd_maskl(0xB80008B8, 0xF83FFFFF, (RTD18X5_BGA459_PIN_F25) << 22);
// PAD_NAME: SCART_FSW_0_APAD 205
rtd_maskl(0xB80008EC, 0x07FFFFFF, (RTD18X5_BGA459_PIN_Y9) << 27);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: VDAC_VDBSO_APAD 206
rtd_maskl(0xB80008EC, 0xFC03FFFF, (((RTD18X5_BGA459_PIN_AA4 << 4) | (RTD18X5_BGA459_PIN_AA4_UP << 3) | (RTD18X5_BGA459_PIN_AA4_PD << 2) |(RTD18X5_BGA459_PIN_AA4_DS << 1) | (RTD18X5_BGA459_PIN_AA4_SR)) << 18));
// PAD_NAME: VIN_10P_APAD 207
rtd_maskl(0xB80008E4, 0xFFFFF807, (((RTD18X5_BGA459_PIN_U3 << 4) | (RTD18X5_BGA459_PIN_U3_UP << 3) | (RTD18X5_BGA459_PIN_U3_PD << 2) |(RTD18X5_BGA459_PIN_U3_DS << 1) | (RTD18X5_BGA459_PIN_U3_SR)) << 3));
// PAD_NAME: VIN_6P_APAD 208
rtd_maskl(0xB80008E0, 0x007FFFFF, (((RTD18X5_BGA459_PIN_R3 << 4) | (RTD18X5_BGA459_PIN_R3_UP << 3) | (RTD18X5_BGA459_PIN_R3_PD << 2) |(RTD18X5_BGA459_PIN_R3_DS << 1) | (RTD18X5_BGA459_PIN_R3_SR)) << 23));
// PAD_NAME: VIN_7P_APAD 209
rtd_maskl(0xB80008E0, 0xFFE01FFF, (((RTD18X5_BGA459_PIN_T3 << 4) | (RTD18X5_BGA459_PIN_T3_UP << 3) | (RTD18X5_BGA459_PIN_T3_PD << 2) |(RTD18X5_BGA459_PIN_T3_DS << 1) | (RTD18X5_BGA459_PIN_T3_SR)) << 13));
if (RTD18X5_BGA459_PIN_T3 == 0x10) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x0&0xf)<<8)); }; // 10: I2C2_SCL_SRC0,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: VIN_8P_APAD 210
rtd_maskl(0xB80008E0, 0xFFFF00FF, (((RTD18X5_BGA459_PIN_U2 << 4) | (RTD18X5_BGA459_PIN_U2_UP << 3) | (RTD18X5_BGA459_PIN_U2_PD << 2) |(RTD18X5_BGA459_PIN_U2_DS << 1) | (RTD18X5_BGA459_PIN_U2_SR)) << 8));
if (RTD18X5_BGA459_PIN_U2 == 0x10) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x0&0xf)<<8)); }; // 10: I2C2_SDA_SRC0,<I/O>
// PAD_NAME: VIN_9P_APAD 211
rtd_maskl(0xB80008E4, 0x007FFFFF, (((RTD18X5_BGA459_PIN_W2 << 4) | (RTD18X5_BGA459_PIN_W2_UP << 3) | (RTD18X5_BGA459_PIN_W2_PD << 2) |(RTD18X5_BGA459_PIN_W2_DS << 1) | (RTD18X5_BGA459_PIN_W2_SR)) << 23));
if (RTD18X5_BGA459_PIN_W2 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xc&0x1f)<<7)); }; // F: I2C0_SDA_SRC12,<I/O>
// PAD_NAME: VIN_A2N_APAD 212
rtd_maskl(0xB80008E4, 0xFFFF00FF, (((RTD18X5_BGA459_PIN_V1 << 4) | (RTD18X5_BGA459_PIN_V1_UP << 3) | (RTD18X5_BGA459_PIN_V1_PD << 2) |(RTD18X5_BGA459_PIN_V1_DS << 1) | (RTD18X5_BGA459_PIN_V1_SR)) << 8));
// PAD_NAME: VIN_Y1N_APAD 213
rtd_maskl(0xB80008E0, 0xFC03FFFF, (((RTD18X5_BGA459_PIN_T2 << 4) | (RTD18X5_BGA459_PIN_T2_UP << 3) | (RTD18X5_BGA459_PIN_T2_PD << 2) |(RTD18X5_BGA459_PIN_T2_DS << 1) | (RTD18X5_BGA459_PIN_T2_SR)) << 18));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: RTC_XTLI_APAD 201
rtd_maskl(0xB8060218, 0x07FFFFFF, (RTD18X5_BGA459_PIN_F7 << 27));
// PAD_NAME: RTC_XTLO_APAD 202
rtd_maskl(0xB8060218, 0xF83FFFFF, (RTD18X5_BGA459_PIN_E7 << 22));

// PAD_NAME: pad_gpio_85_io:2 134
rtd_maskl(0xB8000850, 0xFFFFC01F, (((RTD18X5_BGA459_PIN_G22 << 4) | (RTD18X5_BGA459_PIN_G22_UP << 3) | (RTD18X5_BGA459_PIN_G22_PD << 2) |(RTD18X5_BGA459_PIN_G22_DS << 1) | (RTD18X5_BGA459_PIN_G22_SR)) << 5));
}
