#include <common.h>
#include <asm/io.h>
#include <platform_lib/board/pcb.h>

#if 1
	#define DEBUG_PRINT(fmt,args...)
#else
	#define DEBUG_PRINT(fmt,args...)	 printf(fmt,## args);
#endif

#if defined(CONFIG_BOARD_298X_TV001_QFP176_EMMC) || defined(CONFIG_BOARD_298X_TV001_QFP176_NAND) \
	|| defined(CONFIG_BOARD_298X_TV003_QFP176_NAND)|| defined (CONFIG_BOARD_298X_TV003_QFP176_V2_NAND) \
	|| defined (CONFIG_BOARD_298X_TV003_OEM_QFP176_V2_NAND) \
	|| defined (CONFIG_BOARD_298X_TV032_ATSC_QFP176_NAND)
/***********************************************************************/
/*                                                                                                                        */
/* This is used for QFP176 v1 & v2                                                                         */
/*                                                                                                                        */
/***********************************************************************/

void PinMuxInit(void) {
// TODO: Fix Me
printf("%s %s %d v1 v2\n", __FILE__, __FUNCTION__, __LINE__);

//bb_aiol_GPI_EN [3] bb_aior_GPI_EN [2] set as GPIO mode
rtd_maskl(0xB80008F4, ~0xC, (1<<3)|(1<<2));

// PAD_NAME: VDAC_IDACO_TV_APAD 0
rtd_maskl(0xB80008EC, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_1) << 17));
// PAD_NAME: BB_AI2L_APAD 1
rtd_maskl(0xB80008F0, 0x07FFFFFF, ((RTD298X_QFP176_PIN_6) << 27));
if (RTD298X_QFP176_PIN_6 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x4&0x7)<<17)); }; // 11: P_RXER_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_6 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x4&0x7)<<18)); }; // 10: P_COL_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_6 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x0&0xf)<<23)); }; // 6: CR_SD_WP_SRC0,<I>,<HS>
// PAD_NAME: BB_AI2R_APAD 2
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
rtd_maskl(0xB80008F0, 0xF83FFFFF, ((RTD298X_QFP176_PIN_7) << 22));
if (RTD298X_QFP176_PIN_7 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x4&0x7)<<11)); }; // 11: P_RXDV_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_7 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x5&0x7)<<20)); }; // 8: uart1_rXdi_src5,<I>
// PAD_NAME: BB_AI3L_APAD 3
rtd_maskl(0xB80008F0, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_8) << 17));
// PAD_NAME: BB_AI3R_APAD 4
rtd_maskl(0xB80008F0, 0xFFFE0FFFF, ((RTD298X_QFP176_PIN_9) << 12));
// PAD_NAME: BB_AIO1L_APAD 5
rtd_maskl(0xB80008F4, 0xF83FFFFF, ((RTD298X_QFP176_PIN_11) << 22));
// PAD_NAME: BB_AIO1R_APAD 6
rtd_maskl(0xB80008F4, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_12) << 17));
// PAD_NAME: BB_HPOL_APAD:2 7
rtd_maskl(0xB80008F4, 0xFFFE0FFF, ((RTD298X_QFP176_PIN_14) << 12));
// PAD_NAME: BB_HPOR_APAD:2 8
rtd_maskl(0xB80008F4, 0xFFFFF07F, ((RTD298X_QFP176_PIN_15) << 7));
// PAD_NAME: BB_DIO1_APAD 9
rtd_maskl(0xB80008F8, 0x07FFFFFF, ((RTD298X_QFP176_PIN_16) << 27));
if (RTD298X_QFP176_PIN_16 == 0x6) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x5&0x7)<<16)); }; // 6: uart0_rXdi_src5,<I>
// PAD_NAME: BB_DIO2_APAD 10
rtd_maskl(0xB80008F8, 0xF83FFFFF, ((RTD298X_QFP176_PIN_17) << 22));
// PAD_NAME: BB_DIO3_APAD 11
rtd_maskl(0xB80008F8, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_18) << 17));
// PAD_NAME: pad_gpio_0_io 12
rtd_maskl(0xB8000800, 0x007FFFFF, (((RTD298X_QFP176_PIN_38 << 4) | (RTD298X_QFP176_PIN_38_UP << 3) | (RTD298X_QFP176_PIN_38_PD << 2) |(RTD298X_QFP176_PIN_38_DS << 1) | (RTD298X_QFP176_PIN_38_SR)) << 23));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_1_io 13
rtd_maskl(0xB8000800, 0xFF803FFF, (((RTD298X_QFP176_PIN_39 << 4) | (RTD298X_QFP176_PIN_39_UP << 3) | (RTD298X_QFP176_PIN_39_PD << 2) |(RTD298X_QFP176_PIN_39_DS << 1) | (RTD298X_QFP176_PIN_39_SR)) << 14));
if (RTD298X_QFP176_PIN_39 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // 16: TP0_Data_bit4_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_39 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SCL_SRC0,<I/O>
if (RTD298X_QFP176_PIN_39 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SCL_SRC7,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_2_io 14
rtd_maskl(0xB8000804, 0x807FFFFF, (((RTD298X_QFP176_PIN_40 << 4) | (RTD298X_QFP176_PIN_40_UP << 3) | (RTD298X_QFP176_PIN_40_PD << 2) |(RTD298X_QFP176_PIN_40_DS << 1) | (RTD298X_QFP176_PIN_40_SR)) << 23));
if (RTD298X_QFP176_PIN_40 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<23), ((0x2&0x3)<<23)); }; // 16: TP0_Data_bit3_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_40 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SDA_SRC0,<I/O>
if (RTD298X_QFP176_PIN_40 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SDA_SRC7,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_16_io 15
rtd_maskl(0xB8000814, 0xFFFFC01F, (((RTD298X_QFP176_PIN_42 << 4) | (RTD298X_QFP176_PIN_42_UP << 3) | (RTD298X_QFP176_PIN_42_PD << 2) |(RTD298X_QFP176_PIN_42_DS << 1) | (RTD298X_QFP176_PIN_42_SR)) << 5));
if (RTD298X_QFP176_PIN_42 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x3&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_42 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_42 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x1&0x3)<<11)); }; // 2:
if (RTD298X_QFP176_PIN_42 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 1: I2C2_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_42 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<24), ((0x1&0x1)<<24)); }; // 0:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_17_io 16
rtd_maskl(0xB8000818, 0x007FFFFF, (((RTD298X_QFP176_PIN_43 << 4) | (RTD298X_QFP176_PIN_43_UP << 3) | (RTD298X_QFP176_PIN_43_PD << 2) |(RTD298X_QFP176_PIN_43_DS << 1) | (RTD298X_QFP176_PIN_43_SR)) << 23));
if (RTD298X_QFP176_PIN_43 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x3&0x7)<<9)); }; // 15: VBY1_
if (RTD298X_QFP176_PIN_43 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x9&0xf)<<5)); }; // 8: SC1_DATA0_SRC9,<I/O>
if (RTD298X_QFP176_PIN_43 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x5&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src5,<I/O>
if (RTD298X_QFP176_PIN_43 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x1&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_43 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<9), ((0x0&0x3)<<9)); }; // 1: TP0_SYNC_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_43 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<28), ((0x1&0x1)<<28)); }; // 0: TP2_SYNC_SRC1,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_18_io 17
rtd_maskl(0xB8000818, 0xFF803FFF, (((RTD298X_QFP176_PIN_44 << 4) | (RTD298X_QFP176_PIN_44_UP << 3) | (RTD298X_QFP176_PIN_44_PD << 2) |(RTD298X_QFP176_PIN_44_DS << 1) | (RTD298X_QFP176_PIN_44_SR)) << 14));
if (RTD298X_QFP176_PIN_44 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<10), ((0x2&0x3)<<10)); }; // 16:
if (RTD298X_QFP176_PIN_44 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2_SDA_SRC1,<I/O>
if (RTD298X_QFP176_PIN_44 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x5&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC5,<I/O>
if (RTD298X_QFP176_PIN_44 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x1&0x3)<<15)); }; // 2: EMMC_Data_bit5_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_44 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 1: TP0_VAL_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_44 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<26), ((0x1&0x1)<<26)); }; // 0: TP2_VAL_SRC1,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_19_io 18
rtd_maskl(0xB8000818, 0xFFFFC01F, (((RTD298X_QFP176_PIN_45 << 4) | (RTD298X_QFP176_PIN_45_UP << 3) | (RTD298X_QFP176_PIN_45_PD << 2) |(RTD298X_QFP176_PIN_45_DS << 1) | (RTD298X_QFP176_PIN_45_SR)) << 5));
if (RTD298X_QFP176_PIN_45 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xb&0xf)<<10)); }; // 8: SC1_CD_SRC11,<I>
if (RTD298X_QFP176_PIN_45 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_45 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 1: TP0_CLK_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_45 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<30), ((0x1&0x1)<<30)); }; // 0: TP2_CLK_SRC1,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_39_io 19
rtd_maskl(0xB8000830, 0x007FFFFF, (((RTD298X_QFP176_PIN_46 << 4) | (RTD298X_QFP176_PIN_46_UP << 3) | (RTD298X_QFP176_PIN_46_PD << 2) |(RTD298X_QFP176_PIN_46_DS << 1) | (RTD298X_QFP176_PIN_46_SR)) << 23));
if (RTD298X_QFP176_PIN_46 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 15: GSPI

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_40_io 20
rtd_maskl(0xB8000830, 0xFF803FFF, (((RTD298X_QFP176_PIN_47 << 4) | (RTD298X_QFP176_PIN_47_UP << 3) | (RTD298X_QFP176_PIN_47_PD << 2) |(RTD298X_QFP176_PIN_47_DS << 1) | (RTD298X_QFP176_PIN_47_SR)) << 14));
if (RTD298X_QFP176_PIN_47 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x0&0x7)<<12)); }; // 15: GSPI_DI_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_47 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x0&0x7)<<25)); }; // 14: EPI_LOCK_src0,<I>
if (RTD298X_QFP176_PIN_47 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<22), ((0x2&0x3)<<22)); }; // 10: P_TXC_SRC2,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_41_io 21
rtd_maskl(0xB8000830, 0xFFFFC01F, (((RTD298X_QFP176_PIN_48 << 4) | (RTD298X_QFP176_PIN_48_UP << 3) | (RTD298X_QFP176_PIN_48_PD << 2) |(RTD298X_QFP176_PIN_48_DS << 1) | (RTD298X_QFP176_PIN_48_SR)) << 5));
if (RTD298X_QFP176_PIN_48 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x0&0x7)<<8)); }; // 15: GSPI_CS_N_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_48 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x9&0xf)<<10)); }; // 14: SC1_CD_SRC9,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_42_io 22
rtd_maskl(0xB8000834, 0x007FFFFF, (((RTD298X_QFP176_PIN_49 << 4) | (RTD298X_QFP176_PIN_49_UP << 3) | (RTD298X_QFP176_PIN_49_PD << 2) |(RTD298X_QFP176_PIN_49_DS << 1) | (RTD298X_QFP176_PIN_49_SR)) << 23));
if (RTD298X_QFP176_PIN_49 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 15: GSPI_DO_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_49 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<25), ((0x2&0x3)<<25)); }; // 10: P_RXC_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_49 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x4&0xf)<<5)); }; // 8: SC1_DATA0_SRC4,<I/O>
if (RTD298X_QFP176_PIN_49 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x3&0x7)<<24)); }; // 7: SC0_DATA0_SRC3,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_35_io 23
rtd_maskl(0xB8000828, 0xFFFFC01F, (((RTD298X_QFP176_PIN_53 << 4) | (RTD298X_QFP176_PIN_53_UP << 3) | (RTD298X_QFP176_PIN_53_PD << 2) |(RTD298X_QFP176_PIN_53_DS << 1) | (RTD298X_QFP176_PIN_53_SR)) << 5));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_44_io 24
rtd_maskl(0xB8000834, 0xFFFFC01F, (((RTD298X_QFP176_PIN_54 << 4) | (RTD298X_QFP176_PIN_54_UP << 3) | (RTD298X_QFP176_PIN_54_PD << 2) |(RTD298X_QFP176_PIN_54_DS << 1) | (RTD298X_QFP176_PIN_54_SR)) << 5));
if (RTD298X_QFP176_PIN_54 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<26), ((0x0&0x3)<<26)); }; // 2: EMMC_Data_bit0_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_45_io 25
rtd_maskl(0xB8000838, 0x007FFFFF, (((RTD298X_QFP176_PIN_55 << 4) | (RTD298X_QFP176_PIN_55_UP << 3) | (RTD298X_QFP176_PIN_55_PD << 2) |(RTD298X_QFP176_PIN_55_DS << 1) | (RTD298X_QFP176_PIN_55_SR)) << 23));
if (RTD298X_QFP176_PIN_55 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<24), ((0x0&0x3)<<24)); }; // 2: EMMC_Data_bit1_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_46_io 26
rtd_maskl(0xB8000838, 0xFF803FFF, (((RTD298X_QFP176_PIN_56 << 4) | (RTD298X_QFP176_PIN_56_UP << 3) | (RTD298X_QFP176_PIN_56_PD << 2) |(RTD298X_QFP176_PIN_56_DS << 1) | (RTD298X_QFP176_PIN_56_SR)) << 14));
if (RTD298X_QFP176_PIN_56 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<22), ((0x0&0x3)<<22)); }; // 2:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_47_io 27
rtd_maskl(0xB8000838, 0xFFFFC01F, (((RTD298X_QFP176_PIN_57 << 4) | (RTD298X_QFP176_PIN_57_UP << 3) | (RTD298X_QFP176_PIN_57_PD << 2) |(RTD298X_QFP176_PIN_57_DS << 1) | (RTD298X_QFP176_PIN_57_SR)) << 5));
if (RTD298X_QFP176_PIN_57 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<20), ((0x0&0x3)<<20)); }; // 2:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_48_io 28
rtd_maskl(0xB800083C, 0x007FFFFF, (((RTD298X_QFP176_PIN_58 << 4) | (RTD298X_QFP176_PIN_58_UP << 3) | (RTD298X_QFP176_PIN_58_PD << 2) |(RTD298X_QFP176_PIN_58_DS << 1) | (RTD298X_QFP176_PIN_58_SR)) << 23));
if (RTD298X_QFP176_PIN_58 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_49_io 29
rtd_maskl(0xB800083C, 0xFF803FFF, (((RTD298X_QFP176_PIN_59 << 4) | (RTD298X_QFP176_PIN_59_UP << 3) | (RTD298X_QFP176_PIN_59_PD << 2) |(RTD298X_QFP176_PIN_59_DS << 1) | (RTD298X_QFP176_PIN_59_SR)) << 14));
if (RTD298X_QFP176_PIN_59 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x0&0x3)<<15)); }; // 2:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_50_io 30
rtd_maskl(0xB800083C, 0xFFFFC01F, (((RTD298X_QFP176_PIN_60 << 4) | (RTD298X_QFP176_PIN_60_UP << 3) | (RTD298X_QFP176_PIN_60_PD << 2) |(RTD298X_QFP176_PIN_60_DS << 1) | (RTD298X_QFP176_PIN_60_SR)) << 5));
if (RTD298X_QFP176_PIN_60 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x6&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src6,<I/O>
if (RTD298X_QFP176_PIN_60 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x6&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src6,<I/O>
if (RTD298X_QFP176_PIN_60 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_51_io 31
rtd_maskl(0xB8000840, 0x007FFFFF, (((RTD298X_QFP176_PIN_61 << 4) | (RTD298X_QFP176_PIN_61_UP << 3) | (RTD298X_QFP176_PIN_61_PD << 2) |(RTD298X_QFP176_PIN_61_DS << 1) | (RTD298X_QFP176_PIN_61_SR)) << 23));
if (RTD298X_QFP176_PIN_61 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x6&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC6,<I/O>
if (RTD298X_QFP176_PIN_61 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x6&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC6,<I/O>
if (RTD298X_QFP176_PIN_61 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 2: EMMC_Data_bit7_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_52_io 32
rtd_maskl(0xB8000840, 0xFF803FFF, (((RTD298X_QFP176_PIN_62 << 4) | (RTD298X_QFP176_PIN_62_UP << 3) | (RTD298X_QFP176_PIN_62_PD << 2) |(RTD298X_QFP176_PIN_62_DS << 1) | (RTD298X_QFP176_PIN_62_SR)) << 14));
if (RTD298X_QFP176_PIN_62 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x1&0x7)<<25)); }; // 14: EPI_LOCK_src1,<I>
if (RTD298X_QFP176_PIN_62 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x5&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_62 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x6&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_62 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x2&0x7)<<7)); }; // 4: EPI_LOCK_src1,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_56_io 33
rtd_maskl(0xB8000844, 0xFFFFC01F, (((RTD298X_QFP176_PIN_63 << 4) | (RTD298X_QFP176_PIN_63_UP << 3) | (RTD298X_QFP176_PIN_63_PD << 2) |(RTD298X_QFP176_PIN_63_DS << 1) | (RTD298X_QFP176_PIN_63_SR)) << 5));
if (RTD298X_QFP176_PIN_63 == 0x12) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x3&0x1f)<<7)); }; // 12: I2C0_SDA_SRC3,<I/O>
if (RTD298X_QFP176_PIN_63 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x0&0xf)<<10)); }; // 8:
if (RTD298X_QFP176_PIN_63 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 7: test_en_bit20,<I/O>
if (RTD298X_QFP176_PIN_63 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 6:
if (RTD298X_QFP176_PIN_63 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 2: I2C0_SDA_SRC3,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_53_io 34
rtd_maskl(0xB8000840, 0xFFFFC01F, (((RTD298X_QFP176_PIN_64 << 4) | (RTD298X_QFP176_PIN_64_UP << 3) | (RTD298X_QFP176_PIN_64_PD << 2) |(RTD298X_QFP176_PIN_64_DS << 1) | (RTD298X_QFP176_PIN_64_SR)) << 5));
if (RTD298X_QFP176_PIN_64 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x4&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_64 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x3&0x7)<<1)); }; // 10:
if (RTD298X_QFP176_PIN_64 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F: MIS_GPIO_bit53,<I/O>
if (RTD298X_QFP176_PIN_64 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x0&0x7)<<26)); }; // 9:
if (RTD298X_QFP176_PIN_64 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x5&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_64 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x5&0x7)<<10)); }; // 4:
if (RTD298X_QFP176_PIN_64 == 0x2) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x0&0x7)<<20)); }; // 2: uart1_rXdi_src0,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_54_io 35
rtd_maskl(0xB8000844, 0x007FFFFF, (((RTD298X_QFP176_PIN_65 << 4) | (RTD298X_QFP176_PIN_65_UP << 3) | (RTD298X_QFP176_PIN_65_PD << 2) |(RTD298X_QFP176_PIN_65_DS << 1) | (RTD298X_QFP176_PIN_65_SR)) << 23));
if (RTD298X_QFP176_PIN_65 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x4&0x7)<<9)); }; // 15:
if (RTD298X_QFP176_PIN_65 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 10:
if (RTD298X_QFP176_PIN_65 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F: MIS_GPIO_bit54,<I/O>
if (RTD298X_QFP176_PIN_65 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x8&0xf)<<5)); }; // 8: SC1_DATA0_SRC8,<I/O>
if (RTD298X_QFP176_PIN_65 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x5&0x7)<<14)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXHP 36
rtd_maskl(0xB80008B8, 0x07FFFFFF, (RTD298X_QFP176_PIN_74) << 27);
if (RTD298X_QFP176_PIN_74 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x2&0x3)<<15)); }; // 10: P_CRS_SRC2,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXGP 37
rtd_maskl(0xB80008B8, 0xFFC1FFFF, (RTD298X_QFP176_PIN_75) << 17);
if (RTD298X_QFP176_PIN_75 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11:
if (RTD298X_QFP176_PIN_75 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x2&0x7)<<18)); }; // 10:
if (RTD298X_QFP176_PIN_75 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x2&0x3)<<4)); }; // 7: DEMOD_ANT_TX_SRC2,<I/O>
if (RTD298X_QFP176_PIN_75 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 2:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXGN 38
rtd_maskl(0xB80008B8, 0xFFFE0FFF, (RTD298X_QFP176_PIN_76) << 12);
if (RTD298X_QFP176_PIN_76 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11: I2C2_SDA_SRC9,<I/O>
if (RTD298X_QFP176_PIN_76 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x2&0x7)<<17)); }; // 10: P_RXER_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_76 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x2&0x3)<<0)); }; // 7:
if (RTD298X_QFP176_PIN_76 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x2&0x7)<<19)); }; // 6:
if (RTD298X_QFP176_PIN_76 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x0&0xf)<<28)); }; // 5:
if (RTD298X_QFP176_PIN_76 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x0&0x7)<<14)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXFP 39
rtd_maskl(0xB80008B8, 0xFFFFF07F, (RTD298X_QFP176_PIN_77) << 7);
if (RTD298X_QFP176_PIN_77 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // A:
if (RTD298X_QFP176_PIN_77 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: I2C2_SCL_SRC2,<I/O>
if (RTD298X_QFP176_PIN_77 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x1&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_77 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x1&0x3)<<4)); }; // 7: test_en_bit30,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXFN 40
rtd_maskl(0xB80008B8, 0xFFFFFF83, (RTD298X_QFP176_PIN_78) << 2);
if (RTD298X_QFP176_PIN_78 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: I2C2_SDA_SRC2,<I/O>
if (RTD298X_QFP176_PIN_78 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x2&0x3)<<19)); }; // B:
if (RTD298X_QFP176_PIN_78 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x1&0x3)<<0)); }; // 7: test_en_bit31,<I/O>
if (RTD298X_QFP176_PIN_78 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x3&0x7)<<19)); }; // 6:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXEP 41
rtd_maskl(0xB80008BC, 0x07FFFFFF, (RTD298X_QFP176_PIN_79) << 27);
if (RTD298X_QFP176_PIN_79 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 15: VBY1_HTPD_src1,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXEN 42
rtd_maskl(0xB80008BC, 0xF83FFFFF, (RTD298X_QFP176_PIN_80) << 22);
if (RTD298X_QFP176_PIN_80 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x1&0x7)<<9)); }; // 15: VBY1_LOCK_src1,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXDP 43
rtd_maskl(0xB80008BC, 0xFFC1FFFF, (RTD298X_QFP176_PIN_81) << 17);
if (RTD298X_QFP176_PIN_81 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x8&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC8,<I>
if (RTD298X_QFP176_PIN_81 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x4&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC4,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXDN 44
rtd_maskl(0xB80008BC, 0xFFFE0FFF, (RTD298X_QFP176_PIN_82) << 12);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCP 45
rtd_maskl(0xB80008BC, 0xFFFFF07F, (RTD298X_QFP176_PIN_83) << 7);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCN 46
rtd_maskl(0xB80008BC, 0xFFFFFF83, (RTD298X_QFP176_PIN_84) << 2);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXBP 47
rtd_maskl(0xB80008C0, 0x07FFFFFF, (RTD298X_QFP176_PIN_85) << 27);
if (RTD298X_QFP176_PIN_85 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 15: VBY1_HTPD_src0,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXBN 48
rtd_maskl(0xB80008C0, 0xF83FFFFF, (RTD298X_QFP176_PIN_86) << 22);
if (RTD298X_QFP176_PIN_86 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x0&0x7)<<9)); }; // 15: VBY1_LOCK_src0,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXAP 49
rtd_maskl(0xB80008C0, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_87) << 17));
if (RTD298X_QFP176_PIN_87 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SCL_SRC10,<I/O>
if (RTD298X_QFP176_PIN_87 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SCL_SRC8,<I/O>
if (RTD298X_QFP176_PIN_87 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x2&0x3)<<2)); }; // 7:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXAN 50
rtd_maskl(0xB80008C0, 0xFFFE0FFF, ((RTD298X_QFP176_PIN_88) << 12) );
if (RTD298X_QFP176_PIN_88 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SDA_SRC10,<I/O>
if (RTD298X_QFP176_PIN_88 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SDA_SRC8,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXGP 51
rtd_maskl(0xB80008C0, 0xFFFFF07F, (RTD298X_QFP176_PIN_90) << 7);
if (RTD298X_QFP176_PIN_90 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x4&0x7)<<1)); }; // 11:
if (RTD298X_QFP176_PIN_90 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x2&0x7)<<11)); }; // 10:
if (RTD298X_QFP176_PIN_90 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F: I2C2_SCL_SRC3,<I/O>
if (RTD298X_QFP176_PIN_90 == 0xA) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x1&0x7)<<20)); }; // A:
if (RTD298X_QFP176_PIN_90 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x1&0x7)<<26)); }; // 9:
if (RTD298X_QFP176_PIN_90 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x6&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_90 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 5:
if (RTD298X_QFP176_PIN_90 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x0&0x7)<<10)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXGN 52
rtd_maskl(0xB80008C0, 0xFFFFFF83, (RTD298X_QFP176_PIN_91) << 2);
if (RTD298X_QFP176_PIN_91 == 0x11) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 11:
if (RTD298X_QFP176_PIN_91 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x2&0x3)<<8)); }; // 10:
if (RTD298X_QFP176_PIN_91 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F: I2C2_SDA_SRC3,<I/O>
if (RTD298X_QFP176_PIN_91 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 6: CR_SD_CMD_SRC3,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXFP 53
rtd_maskl(0xB80008C4, 0x07FFFFFF, (RTD298X_QFP176_PIN_92) << 27);
if (RTD298X_QFP176_PIN_92 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11: I2C2_SCL_SRC4,<I/O>
if (RTD298X_QFP176_PIN_92 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10: I2C0_SCL_SRC6,<I/O>
if (RTD298X_QFP176_PIN_92 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x0&0x3)<<21)); }; // A:
if (RTD298X_QFP176_PIN_92 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 6:
if (RTD298X_QFP176_PIN_92 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x7&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC7,<I>
if (RTD298X_QFP176_PIN_92 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC3,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXFN 54
rtd_maskl(0xB80008C4, 0xF83FFFFF, (RTD298X_QFP176_PIN_93) << 22);
if (RTD298X_QFP176_PIN_93 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11:
if (RTD298X_QFP176_PIN_93 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10:
if (RTD298X_QFP176_PIN_93 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x0&0x3)<<19)); }; // B: USB_PWR_FLAG1_SRC0,<I>
if (RTD298X_QFP176_PIN_93 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x1&0x3)<<2)); }; // 7: DEMOD_ANT_RX_SRC1,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXEP 55
rtd_maskl(0xB80008C4, 0xFFC1FFFF, (RTD298X_QFP176_PIN_94) << 17);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXEN 56
rtd_maskl(0xB80008C4, 0xFFFE0FFF, (RTD298X_QFP176_PIN_95) << 12);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXDP 57
rtd_maskl(0xB80008C4, 0xFFFFF07F, (RTD298X_QFP176_PIN_96) << 7);
if (RTD298X_QFP176_PIN_96 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SCL_SRC6,<I/O>
if (RTD298X_QFP176_PIN_96 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x0&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_96 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x0&0x7)<<7)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXDN 58
rtd_maskl(0xB80008C4, 0xFFFFFF83, (RTD298X_QFP176_PIN_97) << 2);
if (RTD298X_QFP176_PIN_97 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SDA_SRC6,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXCP 59
rtd_maskl(0xB80008C8, 0x07FFFFFF, (RTD298X_QFP176_PIN_98) << 27);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXCN 60
rtd_maskl(0xB80008C8, 0xF83FFFFF, (RTD298X_QFP176_PIN_99) << 22);

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXBP 61
rtd_maskl(0xB80008C8, 0xFFFFF07F, (RTD298X_QFP176_PIN_100) << 17);
if (RTD298X_QFP176_PIN_100 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SCL_SRC9,<I/O>
if (RTD298X_QFP176_PIN_100 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x2&0x7)<<16)); }; // 8: uart0_rXdi_src2,<I>
if (RTD298X_QFP176_PIN_100 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x7&0x7)<<24)); }; // 5:
if (RTD298X_QFP176_PIN_100 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x7&0x7)<<10)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXBN 62
rtd_maskl(0xB80008C8, 0xFFFE0FFF, (RTD298X_QFP176_PIN_101) << 12);
if (RTD298X_QFP176_PIN_101 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SDA_SRC9,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXAP 63
rtd_maskl(0xB80008C8, 0xFFFFF07F, (RTD298X_QFP176_PIN_102) << 7);
if (RTD298X_QFP176_PIN_102 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SCL_SRC8,<I/O>
if (RTD298X_QFP176_PIN_102 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x4&0x7)<<20)); }; // 8: uart1_rXdi_src4,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXAN 64
rtd_maskl(0xB80008C8, 0xFFFFFF83, (RTD298X_QFP176_PIN_103) << 2);
if (RTD298X_QFP176_PIN_103 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SDA_SRC8,<I/O>
if (RTD298X_QFP176_PIN_103 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x7&0xf)<<28)); }; // 5:
if (RTD298X_QFP176_PIN_103 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x7&0x7)<<14)); }; // 4:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_7_io 65
rtd_maskl(0xB806024C, 0xFFFFC01F, (((RTD298X_QFP176_PIN_105 << 4) | (RTD298X_QFP176_PIN_105_UP << 3) | (RTD298X_QFP176_PIN_105_PD << 2) |(RTD298X_QFP176_PIN_105_DS << 1) | (RTD298X_QFP176_PIN_105_SR)) << 5));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_8_io 66
rtd_maskl(0xB806024C, 0xFF803FFF, (((RTD298X_QFP176_PIN_106 << 4) | (RTD298X_QFP176_PIN_106_UP << 3) | (RTD298X_QFP176_PIN_106_PD << 2) |(RTD298X_QFP176_PIN_106_DS << 1) | (RTD298X_QFP176_PIN_106_SR)) << 14));
if (RTD298X_QFP176_PIN_106 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x1&0x7)<<16)); }; // 15: GSPI_SCLK_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_106 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 11: VFD_D_SRC0,<I/O>
if (RTD298X_QFP176_PIN_106 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x0&0x7)<<2)); }; // 8: irrX_src0,<I>
if (RTD298X_QFP176_PIN_106 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<4), ((0x0&0x1)<<4)); }; // 3: PCMCIA_IREQ1_N_SRC0,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_9_io 67
rtd_maskl(0xB806024C, 0x007FFFFF, (((RTD298X_QFP176_PIN_107 << 4) | (RTD298X_QFP176_PIN_107_UP << 3) | (RTD298X_QFP176_PIN_107_PD << 2) |(RTD298X_QFP176_PIN_107_DS << 1) | (RTD298X_QFP176_PIN_107_SR)) << 23));
if (RTD298X_QFP176_PIN_107 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x5&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_107 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x1&0x7)<<12)); }; // 14: GSPI_DI_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_107 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_107 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x3&0x7)<<16)); }; // 8:
if (RTD298X_QFP176_PIN_107 == 0x3) { rtd_maskl(0xb8000928, ~((0x3)<<0), ((0x0&0x3)<<0)); }; // 3: PCMCIA_CD1_N_SRC0,<I>


DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_10_io 68
rtd_maskl(0xB8060248, 0xFFFFC01F, (((RTD298X_QFP176_PIN_108 << 4) | (RTD298X_QFP176_PIN_108_UP << 3) | (RTD298X_QFP176_PIN_108_PD << 2) |(RTD298X_QFP176_PIN_108_DS << 1) | (RTD298X_QFP176_PIN_108_SR)) << 5));
if (RTD298X_QFP176_PIN_108 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x5&0x7)<<9)); }; // 15: VBY1_LOCK_src5,<I>
if (RTD298X_QFP176_PIN_108 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x1&0x7)<<8)); }; // 14: GSPI_CS_N_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_108 == 0x13) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x2&0x7)<<25)); }; // 13: EPI_LOCK_src2,<I>
if (RTD298X_QFP176_PIN_108 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SDA_SRC1,<I/O>
if (RTD298X_QFP176_PIN_108 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // A:
if (RTD298X_QFP176_PIN_108 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 9:

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_11_io 69
rtd_maskl(0xB8060248, 0xFF803FFF, (((RTD298X_QFP176_PIN_109 << 4) | (RTD298X_QFP176_PIN_109_UP << 3) | (RTD298X_QFP176_PIN_109_PD << 2) |(RTD298X_QFP176_PIN_109_DS << 1) | (RTD298X_QFP176_PIN_109_SR)) << 14));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_12_io 70
rtd_maskl(0xB8060248, 0x007FFFFF, (((RTD298X_QFP176_PIN_110 << 4) | (RTD298X_QFP176_PIN_110_UP << 3) | (RTD298X_QFP176_PIN_110_PD << 2) |(RTD298X_QFP176_PIN_110_DS << 1) | (RTD298X_QFP176_PIN_110_SR)) << 23));
if (RTD298X_QFP176_PIN_110 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x1&0x7)<<4)); }; // 15: GSPI_DO_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_110 == 0x12) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0xa&0xf)<<5)); }; // 12: SC1_DATA0_SRC10,<I/O>
if (RTD298X_QFP176_PIN_110 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SCL_SRC4,<I/O>
if (RTD298X_QFP176_PIN_110 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x2&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_110 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x0&0x7)<<19)); }; // 5: GSPI_DO_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_110 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<6), ((0x0&0x1)<<6)); }; // 3: I2S_out_MCLK,<O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_13_io 71
rtd_maskl(0xB8060244, 0xFFFFC01F, (((RTD298X_QFP176_PIN_111 << 4) | (RTD298X_QFP176_PIN_111_UP << 3) | (RTD298X_QFP176_PIN_111_PD << 2) |(RTD298X_QFP176_PIN_111_DS << 1) | (RTD298X_QFP176_PIN_111_SR)) << 5));
if (RTD298X_QFP176_PIN_111 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SDA_SRC4,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_14_io 72
rtd_maskl(0xB8060204, 0x007FFFFF, (((RTD298X_QFP176_PIN_112 << 4) | (RTD298X_QFP176_PIN_112_UP << 3) | (RTD298X_QFP176_PIN_112_PD << 2) |(RTD298X_QFP176_PIN_112_DS << 1) | (RTD298X_QFP176_PIN_112_SR)) << 23));
if (RTD298X_QFP176_PIN_112 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SDA_SRC2,<I/O>
if (RTD298X_QFP176_PIN_112 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x1&0x3)<<8)); }; // 5: HDDC0_SDA_SRC1,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_15_io 73
rtd_maskl(0xB8060200, 0xFFFFC01F, (((RTD298X_QFP176_PIN_113 << 4) | (RTD298X_QFP176_PIN_113_UP << 3) | (RTD298X_QFP176_PIN_113_PD << 2) |(RTD298X_QFP176_PIN_113_DS << 1) | (RTD298X_QFP176_PIN_113_SR)) << 5));
if (RTD298X_QFP176_PIN_113 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SCL_SRC2,<I/O>
if (RTD298X_QFP176_PIN_113 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 9: uart0_rXdi_src0,<I>
if (RTD298X_QFP176_PIN_113 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x1&0x3)<<5)); }; // 5: HDDC0_SCL_SRC1,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_16_io 74
rtd_maskl(0xB8060244, 0xFF803FFF, (((RTD298X_QFP176_PIN_114 << 4) | (RTD298X_QFP176_PIN_114_UP << 3) | (RTD298X_QFP176_PIN_114_PD << 2) |(RTD298X_QFP176_PIN_114_DS << 1) | (RTD298X_QFP176_PIN_114_SR)) << 14));
if (RTD298X_QFP176_PIN_114 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x1&0x7)<<2)); }; // 9: irrX_src1,<I>
if (RTD298X_QFP176_PIN_114 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 6: CR_SD_CMD_SRC0,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_17_io 75
//rtd_maskl(0xB8060204, 0xFFC03FFF, (((RTD298X_QFP176_PIN_115 << 4) | (RTD298X_QFP176_PIN_115_UP << 3) | (RTD298X_QFP176_PIN_115_PD << 2) |(RTD298X_QFP176_PIN_115_DS << 1) | (RTD298X_QFP176_PIN_115_SR)) << 14));
rtd_maskl(0xB8060204, 0xFF803FFF, (((RTD298X_QFP176_PIN_115 << 4) | (RTD298X_QFP176_PIN_115_UP << 3) | (RTD298X_QFP176_PIN_115_PD << 2) |(RTD298X_QFP176_PIN_115_DS << 1) | (RTD298X_QFP176_PIN_115_SR)) << 14));

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_18_io 76
rtd_maskl(0xB8060204, 0xFFFFC01F, (((RTD298X_QFP176_PIN_116 << 4) | (RTD298X_QFP176_PIN_116_UP << 3) | (RTD298X_QFP176_PIN_116_PD << 2) |(RTD298X_QFP176_PIN_116_DS << 1) | (RTD298X_QFP176_PIN_116_SR)) << 5));
if (RTD298X_QFP176_PIN_116 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x4&0x7)<<2)); }; // 8: irrX_src4,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_19_io 77
rtd_maskl(0xB8060244, 0x007FFFFF, (((RTD298X_QFP176_PIN_117 << 4) | (RTD298X_QFP176_PIN_117_UP << 3) | (RTD298X_QFP176_PIN_117_PD << 2) |(RTD298X_QFP176_PIN_117_DS << 1) | (RTD298X_QFP176_PIN_117_SR)) << 23));
if (RTD298X_QFP176_PIN_117 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x5&0xf)<<10)); }; // 8: SC1_CD_SRC5,<I>
if (RTD298X_QFP176_PIN_117 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 7: SC0_CD_SRC0,<I>
if (RTD298X_QFP176_PIN_117 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x7&0xf)<<23)); }; // 6: CR_SD_WP_SRC7,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_20_io 78
//rtd_maskl(0xB8060208, 0x807FFFFF, (((RTD298X_QFP176_PIN_118 << 4) | (RTD298X_QFP176_PIN_118_UP << 3) | (RTD298X_QFP176_PIN_118_PD << 2) |(RTD298X_QFP176_PIN_118_DS << 1) | (RTD298X_QFP176_PIN_118_SR)) << 23));
rtd_maskl(0xB8060208, 0x007FFFFF, (((RTD298X_QFP176_PIN_118 << 4) | (RTD298X_QFP176_PIN_118_UP << 3) | (RTD298X_QFP176_PIN_118_PD << 2) |(RTD298X_QFP176_PIN_118_DS << 1) | (RTD298X_QFP176_PIN_118_SR)) << 23));
if (RTD298X_QFP176_PIN_118 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x1&0x7)<<19)); }; // 6: CR_SD_CD_SRC1,<I>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_21_io 79
rtd_maskl(0xB8060208, 0xFF803FFF, (((RTD298X_QFP176_PIN_119 << 4) | (RTD298X_QFP176_PIN_119_UP << 3) | (RTD298X_QFP176_PIN_119_PD << 2) |(RTD298X_QFP176_PIN_119_DS << 1) | (RTD298X_QFP176_PIN_119_SR)) << 14));
if (RTD298X_QFP176_PIN_119 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x6&0xf)<<5)); }; // 8: SC1_DATA0_SRC6,<I/O>
if (RTD298X_QFP176_PIN_119 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 7: SC0_DATA0_SRC0,<I/O>
if (RTD298X_QFP176_PIN_119 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x1&0x7)<<15)); }; // 6: CR_SD_Data_bit0_SRC1,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_22_io 80
rtd_maskl(0xB8060240, 0xFFFFC01F, (((RTD298X_QFP176_PIN_120 << 4) | (RTD298X_QFP176_PIN_120_UP << 3) | (RTD298X_QFP176_PIN_120_PD << 2) |(RTD298X_QFP176_PIN_120_DS << 1) | (RTD298X_QFP176_PIN_120_SR)) << 5));
if (RTD298X_QFP176_PIN_120 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x1&0x7)<<11)); }; // 6: CR_SD_Data_bit1_SRC1,<I/O>,<HS>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_23_io 81
rtd_maskl(0xB8060200, 0x007FFFFF, (((RTD298X_QFP176_PIN_121 << 4) | (RTD298X_QFP176_PIN_121_UP << 3) | (RTD298X_QFP176_PIN_121_PD << 2) |(RTD298X_QFP176_PIN_121_DS << 1) | (RTD298X_QFP176_PIN_121_SR)) << 23));
if (RTD298X_QFP176_PIN_121 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SCL_SRC0,<I/O>
if (RTD298X_QFP176_PIN_121 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // A: uart1_cts_n_src1,<I>
if (RTD298X_QFP176_PIN_121 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 9: uart0_cts_n_src1,<I>
if (RTD298X_QFP176_PIN_121 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x1&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_121 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x0&0x3)<<5)); }; // 4: HDDC0_SCL_SRC0,<I>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_24_io 82
rtd_maskl(0xB8060200, 0xFF803FFF, (((RTD298X_QFP176_PIN_122 << 4) | (RTD298X_QFP176_PIN_122_UP << 3) | (RTD298X_QFP176_PIN_122_PD << 2) |(RTD298X_QFP176_PIN_122_DS << 1) | (RTD298X_QFP176_PIN_122_SR)) << 14));
if (RTD298X_QFP176_PIN_122 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xa&0xf)<<10)); }; // 14: SC1_CD_SRC10,<I>
if (RTD298X_QFP176_PIN_122 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SDA_SRC0,<I/O>
if (RTD298X_QFP176_PIN_122 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x1&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_122 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x0&0x3)<<8)); }; // 4: HDDC0_SDA_SRC0,<I/O>

DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: LSADC_REF_APAD 83
rtd_maskl(0xB806020C, 0x07FFFFFF, (RTD298X_QFP176_PIN_123) << 27);
// PAD_NAME: LSADC0_APAD 84
rtd_maskl(0xB8060210, 0x07FFFFFF, (RTD298X_QFP176_PIN_124) << 27);
// PAD_NAME: LSADC1_APAD 85
rtd_maskl(0xB806020C, 0xFFFFFF83, (RTD298X_QFP176_PIN_125) << 2);
// PAD_NAME: LSADC2_APAD 86
rtd_maskl(0xB806020C, 0xFFFFF07F, (RTD298X_QFP176_PIN_126) << 7);
// PAD_NAME: LSADC7_APAD 87
rtd_maskl(0xB806020C, 0xF83FFFFF, (RTD298X_QFP176_PIN_127) << 22);
// PAD_NAME: STB_GPIO_APAD 88
rtd_maskl(0xB8060218, 0xFFC01FFF, (((RTD298X_QFP176_PIN_129 << 4) | (RTD298X_QFP176_PIN_129_UP << 3) | (RTD298X_QFP176_PIN_129_PD << 2) |(RTD298X_QFP176_PIN_129_DS << 1) | (RTD298X_QFP176_PIN_129_SR)) << 13));
// PAD_NAME: VSYNC_APAD 89
rtd_maskl(0xB80008D8, 0x007FFFFF, (((RTD298X_QFP176_PIN_161 << 4) | (RTD298X_QFP176_PIN_161_UP << 3) | (RTD298X_QFP176_PIN_161_PD << 2) |(RTD298X_QFP176_PIN_161_DS << 1) | (RTD298X_QFP176_PIN_161_SR)) << 23));
// PAD_NAME: HSYNC_APAD 90
rtd_maskl(0xB80008D8, 0xF803FFFF, (((RTD298X_QFP176_PIN_162 << 4) | (RTD298X_QFP176_PIN_162_UP << 3) | (RTD298X_QFP176_PIN_162_PD << 2) |(RTD298X_QFP176_PIN_162_DS << 1) | (RTD298X_QFP176_PIN_162_SR)) << 18));
// PAD_NAME: VIN_0P_APAD 91
rtd_maskl(0xB80008DC, 0x007FFFFF, (((RTD298X_QFP176_PIN_163 << 4) | (RTD298X_QFP176_PIN_163_UP << 3) | (RTD298X_QFP176_PIN_163_PD << 2) |(RTD298X_QFP176_PIN_163_DS << 1) | (RTD298X_QFP176_PIN_163_SR)) << 23));
// PAD_NAME: VIN_BN_APAD 92
rtd_maskl(0xB80008DC, 0xF803FFFF, (((RTD298X_QFP176_PIN_164 << 4) | (RTD298X_QFP176_PIN_164_UP << 3) | (RTD298X_QFP176_PIN_164_PD << 2) |(RTD298X_QFP176_PIN_164_DS << 1) | (RTD298X_QFP176_PIN_164_SR)) << 18));
// PAD_NAME: VIN_1P_APAD 93
rtd_maskl(0xB80008DC, 0xFFC01FFF, (((RTD298X_QFP176_PIN_165 << 4) | (RTD298X_QFP176_PIN_165_UP << 3) | (RTD298X_QFP176_PIN_165_PD << 2) |(RTD298X_QFP176_PIN_165_DS << 1) | (RTD298X_QFP176_PIN_165_SR)) << 13));
// PAD_NAME: VIN_2P_APAD 94
rtd_maskl(0xB80008DC, 0xFFFE00FF, (((RTD298X_QFP176_PIN_166 << 4) | (RTD298X_QFP176_PIN_166_UP << 3) | (RTD298X_QFP176_PIN_166_PD << 2) |(RTD298X_QFP176_PIN_166_DS << 1) | (RTD298X_QFP176_PIN_166_SR)) << 8));
// PAD_NAME: VIN_10P_APAD 95
rtd_maskl(0xB80008E4, 0xFFFFF807, (((RTD298X_QFP176_PIN_172 << 4) | (RTD298X_QFP176_PIN_172_UP << 3) | (RTD298X_QFP176_PIN_172_PD << 2) |(RTD298X_QFP176_PIN_172_DS << 1) | (RTD298X_QFP176_PIN_172_SR)) << 3));
// PAD_NAME: VIN_A0N_APAD 96
rtd_maskl(0xB80008E4, 0xFFC01FFF, (((RTD298X_QFP176_PIN_173 << 4) | (RTD298X_QFP176_PIN_173_UP << 3) | (RTD298X_QFP176_PIN_173_PD << 2) |(RTD298X_QFP176_PIN_173_DS << 1) | (RTD298X_QFP176_PIN_173_SR)) << 13));
// PAD_NAME: VIN_12P_APAD 97
rtd_maskl(0xB80008E4, 0xF803FFFF, (((RTD298X_QFP176_PIN_174 << 4) | (RTD298X_QFP176_PIN_174_UP << 3) | (RTD298X_QFP176_PIN_174_PD << 2) |(RTD298X_QFP176_PIN_174_DS << 1) | (RTD298X_QFP176_PIN_174_SR)) << 18));
if (RTD298X_QFP176_PIN_174 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xc&0x1f)<<7)); }; // F: I2C0_SCL_SRC12,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
}

#else /* else of #if defined(CONFIG_BOARD_298X_TV001_QFP176_EMMC)*/

/***********************************************************************/
/*                                                                                                                        */
/* This is used for QFP176 v3                                                                              */
/*                                                                                                                        */
/***********************************************************************/

void PinMuxInit(void) {
// TODO: Fix Me
printf("%s %s %d v3\n", __FILE__, __FUNCTION__, __LINE__);

//bb_aiol_GPI_EN [3] bb_aior_GPI_EN [2] set as GPIO mode
rtd_maskl(0xB80008F4, ~0xC, (1<<3)|(1<<2));

// PAD_NAME: VDAC_IDACO_TV_APAD 0
rtd_maskl(0xB80008EC, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_1) << 17));
// PAD_NAME: BB_AI2L_APAD 1
rtd_maskl(0xB80008F0, 0x07FFFFFF, ((RTD298X_QFP176_PIN_5) << 27));
if (RTD298X_QFP176_PIN_5 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x4&0x7)<<17)); }; // 11: P_RXER_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_5 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x4&0x7)<<18)); }; // 10: P_COL_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_5 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x0&0xf)<<23)); }; // 6: CR_SD_WP_SRC0,<I>,<HS>
// PAD_NAME: BB_AI2R_APAD 2
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
rtd_maskl(0xB80008F0, 0xF83FFFFF, ((RTD298X_QFP176_PIN_6) << 22));
if (RTD298X_QFP176_PIN_6 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x4&0x7)<<11)); }; // 11: P_RXDV_SRC4,<I>,<HS>
if (RTD298X_QFP176_PIN_6 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x5&0x7)<<20)); }; // 8: uart1_rXdi_src5,<I>
// PAD_NAME: BB_AI3L_APAD 3
rtd_maskl(0xB80008F0, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_7) << 17));
// PAD_NAME: BB_AI3R_APAD 4
rtd_maskl(0xB80008F0, 0xFFFE0FFF, ((RTD298X_QFP176_PIN_8) << 12));
// PAD_NAME: BB_AIO1L_APAD 5
rtd_maskl(0xB80008F4, 0xF83FFFFF, ((RTD298X_QFP176_PIN_10) << 22));
// PAD_NAME: BB_AIO1R_APAD 6
rtd_maskl(0xB80008F4, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_11) << 17));
// PAD_NAME: BB_HPOL_APAD:2 7
rtd_maskl(0xB80008F4, 0xFFFE0FFF, ((RTD298X_QFP176_PIN_13) << 12));
// PAD_NAME: BB_HPOR_APAD:2 8
rtd_maskl(0xB80008F4, 0xFFFFF07F, ((RTD298X_QFP176_PIN_14) << 7));
// PAD_NAME: BB_DIO3_APAD 11
rtd_maskl(0xB80008F8, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_15) << 17));
// PAD_NAME: HSDP_2_APAD 98
rtd_maskl(0xB80008F8, 0xFFFF00FF, (((RTD298X_QFP176_PIN_36 << 4) | (RTD298X_QFP176_PIN_36_UP << 3) | (RTD298X_QFP176_PIN_36_PD << 2) |(RTD298X_QFP176_PIN_36_DS << 1) | (RTD298X_QFP176_PIN_36_SR)) << 8));
if (RTD298X_QFP176_PIN_36 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xe&0xf)<<8)); }; // 11: I2C2_SCL_SRC14,<I/O>
if (RTD298X_QFP176_PIN_36 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x3&0x7)<<18)); }; // 10: P_COL_SRC3,<I>,<HS>
if (RTD298X_QFP176_PIN_36 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xe&0x1f)<<7)); }; // F: I2C0_SCL_SRC14,<I/O>
if (RTD298X_QFP176_PIN_36 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x4&0x7)<<16)); }; // 8: uart0_rXdi_src4,<I>
// PAD_NAME: HSDM_2_APAD 97
rtd_maskl(0xB80008F8, 0xFFFFF807, (((RTD298X_QFP176_PIN_37 << 4) | (RTD298X_QFP176_PIN_37_UP << 3) | (RTD298X_QFP176_PIN_37_PD << 2) |(RTD298X_QFP176_PIN_37_DS << 1) | (RTD298X_QFP176_PIN_37_SR)) << 3));
if (RTD298X_QFP176_PIN_37 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xe&0xf)<<8)); }; // 11: I2C2_SDA_SRC14,<I/O>
if (RTD298X_QFP176_PIN_37 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x3&0x3)<<15)); }; // 10: P_CRS_SRC3,<I>,<HS>
if (RTD298X_QFP176_PIN_37 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xe&0x1f)<<7)); }; // F: I2C0_SDA_SRC14,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_0_io 12
rtd_maskl(0xB8000800, 0x007FFFFF, (((RTD298X_QFP176_PIN_38 << 4) | (RTD298X_QFP176_PIN_38_UP << 3) | (RTD298X_QFP176_PIN_38_PD << 2) |(RTD298X_QFP176_PIN_38_DS << 1) | (RTD298X_QFP176_PIN_38_SR)) << 23));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_1_io 13
rtd_maskl(0xB8000800, 0xFF803FFF, (((RTD298X_QFP176_PIN_39 << 4) | (RTD298X_QFP176_PIN_39_UP << 3) | (RTD298X_QFP176_PIN_39_PD << 2) |(RTD298X_QFP176_PIN_39_DS << 1) | (RTD298X_QFP176_PIN_39_SR)) << 14));
if (RTD298X_QFP176_PIN_39 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // 16: TP0_Data_bit4_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_39 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SCL_SRC0,<I/O>
if (RTD298X_QFP176_PIN_39 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SCL_SRC7,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_2_io 14
rtd_maskl(0xB8000804, 0x807FFFFF, (((RTD298X_QFP176_PIN_40 << 4) | (RTD298X_QFP176_PIN_40_UP << 3) | (RTD298X_QFP176_PIN_40_PD << 2) |(RTD298X_QFP176_PIN_40_DS << 1) | (RTD298X_QFP176_PIN_40_SR)) << 23));
if (RTD298X_QFP176_PIN_40 == 0x16) { rtd_maskl(0xb8000924, ~((0x3)<<23), ((0x2&0x3)<<23)); }; // 16: TP0_Data_bit3_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_40 == 0x12) { rtd_maskl(0xb80008fc, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 12: I2C1_SDA_SRC0,<I/O>
if (RTD298X_QFP176_PIN_40 == 0x11) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x7&0x1f)<<7)); }; // 11: I2C0_SDA_SRC7,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_16_io 15
rtd_maskl(0xB8000814, 0xFFFFC01F, (((RTD298X_QFP176_PIN_42 << 4) | (RTD298X_QFP176_PIN_42_UP << 3) | (RTD298X_QFP176_PIN_42_PD << 2) |(RTD298X_QFP176_PIN_42_DS << 1) | (RTD298X_QFP176_PIN_42_SR)) << 5));
if (RTD298X_QFP176_PIN_42 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x3&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_42 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_42 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x1&0x3)<<11)); }; // 2:
if (RTD298X_QFP176_PIN_42 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 1: I2C2_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_42 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<24), ((0x1&0x1)<<24)); }; // 0:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_17_io 16
rtd_maskl(0xB8000818, 0x007FFFFF, (((RTD298X_QFP176_PIN_43 << 4) | (RTD298X_QFP176_PIN_43_UP << 3) | (RTD298X_QFP176_PIN_43_PD << 2) |(RTD298X_QFP176_PIN_43_DS << 1) | (RTD298X_QFP176_PIN_43_SR)) << 23));
if (RTD298X_QFP176_PIN_43 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x3&0x7)<<9)); }; // 15: VBY1_
if (RTD298X_QFP176_PIN_43 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x9&0xf)<<5)); }; // 8: SC1_DATA0_SRC9,<I/O>
if (RTD298X_QFP176_PIN_43 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x5&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src5,<I/O>
if (RTD298X_QFP176_PIN_43 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x1&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_43 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<9), ((0x0&0x3)<<9)); }; // 1: TP0_SYNC_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_43 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<28), ((0x1&0x1)<<28)); }; // 0: TP2_SYNC_SRC1,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_18_io 17
rtd_maskl(0xB8000818, 0xFF803FFF, (((RTD298X_QFP176_PIN_44 << 4) | (RTD298X_QFP176_PIN_44_UP << 3) | (RTD298X_QFP176_PIN_44_PD << 2) |(RTD298X_QFP176_PIN_44_DS << 1) | (RTD298X_QFP176_PIN_44_SR)) << 14));
if (RTD298X_QFP176_PIN_44 == 0x16) { rtd_maskl(0xb8000928, ~((0x3)<<10), ((0x2&0x3)<<10)); }; // 16:
if (RTD298X_QFP176_PIN_44 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x1&0xf)<<8)); }; // 11: I2C2_SDA_SRC1,<I/O>
if (RTD298X_QFP176_PIN_44 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x5&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC5,<I/O>
if (RTD298X_QFP176_PIN_44 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x1&0x3)<<15)); }; // 2: EMMC_Data_bit5_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_44 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 1: TP0_VAL_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_44 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<26), ((0x1&0x1)<<26)); }; // 0: TP2_VAL_SRC1,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_19_io 18
rtd_maskl(0xB8000818, 0xFFFFC01F, (((RTD298X_QFP176_PIN_45 << 4) | (RTD298X_QFP176_PIN_45_UP << 3) | (RTD298X_QFP176_PIN_45_PD << 2) |(RTD298X_QFP176_PIN_45_DS << 1) | (RTD298X_QFP176_PIN_45_SR)) << 5));
if (RTD298X_QFP176_PIN_45 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xb&0xf)<<10)); }; // 8: SC1_CD_SRC11,<I>
if (RTD298X_QFP176_PIN_45 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_45 == 0x1) { rtd_maskl(0xb8000924, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 1: TP0_CLK_SRC0,<I>,<HS>
if (RTD298X_QFP176_PIN_45 == 0x0) { rtd_maskl(0xb8000920, ~((0x1)<<30), ((0x1&0x1)<<30)); }; // 0: TP2_CLK_SRC1,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_39_io 19
rtd_maskl(0xB8000830, 0x007FFFFF, (((RTD298X_QFP176_PIN_46 << 4) | (RTD298X_QFP176_PIN_46_UP << 3) | (RTD298X_QFP176_PIN_46_PD << 2) |(RTD298X_QFP176_PIN_46_DS << 1) | (RTD298X_QFP176_PIN_46_SR)) << 23));
if (RTD298X_QFP176_PIN_46 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 15: GSPI
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_40_io 20
rtd_maskl(0xB8000830, 0xFF803FFF, (((RTD298X_QFP176_PIN_47 << 4) | (RTD298X_QFP176_PIN_47_UP << 3) | (RTD298X_QFP176_PIN_47_PD << 2) |(RTD298X_QFP176_PIN_47_DS << 1) | (RTD298X_QFP176_PIN_47_SR)) << 14));
if (RTD298X_QFP176_PIN_47 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x0&0x7)<<12)); }; // 15: GSPI_DI_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_47 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x0&0x7)<<25)); }; // 14: EPI_LOCK_src0,<I>
if (RTD298X_QFP176_PIN_47 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<22), ((0x2&0x3)<<22)); }; // 10: P_TXC_SRC2,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_41_io 21
rtd_maskl(0xB8000830, 0xFFFFC01F, (((RTD298X_QFP176_PIN_48 << 4) | (RTD298X_QFP176_PIN_48_UP << 3) | (RTD298X_QFP176_PIN_48_PD << 2) |(RTD298X_QFP176_PIN_48_DS << 1) | (RTD298X_QFP176_PIN_48_SR)) << 5));
if (RTD298X_QFP176_PIN_48 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x0&0x7)<<8)); }; // 15: GSPI_CS_N_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_48 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x9&0xf)<<10)); }; // 14: SC1_CD_SRC9,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_42_io 22
rtd_maskl(0xB8000834, 0x007FFFFF, (((RTD298X_QFP176_PIN_49 << 4) | (RTD298X_QFP176_PIN_49_UP << 3) | (RTD298X_QFP176_PIN_49_PD << 2) |(RTD298X_QFP176_PIN_49_DS << 1) | (RTD298X_QFP176_PIN_49_SR)) << 23));
if (RTD298X_QFP176_PIN_49 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x0&0x7)<<4)); }; // 15: GSPI_DO_SRC0,<I/O>,<HS>
if (RTD298X_QFP176_PIN_49 == 0x10) { rtd_maskl(0xb800091c, ~((0x3)<<25), ((0x2&0x3)<<25)); }; // 10: P_RXC_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_49 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x4&0xf)<<5)); }; // 8: SC1_DATA0_SRC4,<I/O>
if (RTD298X_QFP176_PIN_49 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x3&0x7)<<24)); }; // 7: SC0_DATA0_SRC3,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_35_io 23
rtd_maskl(0xB8000828, 0xFFFFC01F, (((RTD298X_QFP176_PIN_53 << 4) | (RTD298X_QFP176_PIN_53_UP << 3) | (RTD298X_QFP176_PIN_53_PD << 2) |(RTD298X_QFP176_PIN_53_DS << 1) | (RTD298X_QFP176_PIN_53_SR)) << 5));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_44_io 24
rtd_maskl(0xB8000834, 0xFFFFC01F, (((RTD298X_QFP176_PIN_54 << 4) | (RTD298X_QFP176_PIN_54_UP << 3) | (RTD298X_QFP176_PIN_54_PD << 2) |(RTD298X_QFP176_PIN_54_DS << 1) | (RTD298X_QFP176_PIN_54_SR)) << 5));
if (RTD298X_QFP176_PIN_54 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<26), ((0x0&0x3)<<26)); }; // 2: EMMC_Data_bit0_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_45_io 25
rtd_maskl(0xB8000838, 0x007FFFFF, (((RTD298X_QFP176_PIN_55 << 4) | (RTD298X_QFP176_PIN_55_UP << 3) | (RTD298X_QFP176_PIN_55_PD << 2) |(RTD298X_QFP176_PIN_55_DS << 1) | (RTD298X_QFP176_PIN_55_SR)) << 23));
if (RTD298X_QFP176_PIN_55 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<24), ((0x0&0x3)<<24)); }; // 2: EMMC_Data_bit1_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_46_io 26
rtd_maskl(0xB8000838, 0xFF803FFF, (((RTD298X_QFP176_PIN_56 << 4) | (RTD298X_QFP176_PIN_56_UP << 3) | (RTD298X_QFP176_PIN_56_PD << 2) |(RTD298X_QFP176_PIN_56_DS << 1) | (RTD298X_QFP176_PIN_56_SR)) << 14));
if (RTD298X_QFP176_PIN_56 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<22), ((0x0&0x3)<<22)); }; // 2:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_47_io 27
rtd_maskl(0xB8000838, 0xFFFFC01F, (((RTD298X_QFP176_PIN_57 << 4) | (RTD298X_QFP176_PIN_57_UP << 3) | (RTD298X_QFP176_PIN_57_PD << 2) |(RTD298X_QFP176_PIN_57_DS << 1) | (RTD298X_QFP176_PIN_57_SR)) << 5));
if (RTD298X_QFP176_PIN_57 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<20), ((0x0&0x3)<<20)); }; // 2:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_48_io 28
rtd_maskl(0xB800083C, 0x007FFFFF, (((RTD298X_QFP176_PIN_58 << 4) | (RTD298X_QFP176_PIN_58_UP << 3) | (RTD298X_QFP176_PIN_58_PD << 2) |(RTD298X_QFP176_PIN_58_DS << 1) | (RTD298X_QFP176_PIN_58_SR)) << 23));
if (RTD298X_QFP176_PIN_58 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // 2: EMMC_Data_bit4_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_49_io 29
rtd_maskl(0xB800083C, 0xFF803FFF, (((RTD298X_QFP176_PIN_59 << 4) | (RTD298X_QFP176_PIN_59_UP << 3) | (RTD298X_QFP176_PIN_59_PD << 2) |(RTD298X_QFP176_PIN_59_DS << 1) | (RTD298X_QFP176_PIN_59_SR)) << 14));
if (RTD298X_QFP176_PIN_59 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<15), ((0x0&0x3)<<15)); }; // 2:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_50_io 30
rtd_maskl(0xB800083C, 0xFFFFC01F, (((RTD298X_QFP176_PIN_60 << 4) | (RTD298X_QFP176_PIN_60_UP << 3) | (RTD298X_QFP176_PIN_60_PD << 2) |(RTD298X_QFP176_PIN_60_DS << 1) | (RTD298X_QFP176_PIN_60_SR)) << 5));
if (RTD298X_QFP176_PIN_60 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x6&0xf)<<28)); }; // 5: ld_spi1_p2_sck_src6,<I/O>
if (RTD298X_QFP176_PIN_60 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x6&0x7)<<14)); }; // 4: ld_spi0_p2_sck_src6,<I/O>
if (RTD298X_QFP176_PIN_60 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<13), ((0x0&0x3)<<13)); }; // 2: EMMC_Data_bit6_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_51_io 31
rtd_maskl(0xB8000840, 0x007FFFFF, (((RTD298X_QFP176_PIN_61 << 4) | (RTD298X_QFP176_PIN_61_UP << 3) | (RTD298X_QFP176_PIN_61_PD << 2) |(RTD298X_QFP176_PIN_61_DS << 1) | (RTD298X_QFP176_PIN_61_SR)) << 23));
if (RTD298X_QFP176_PIN_61 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x6&0x7)<<24)); }; // 5: ld_spi1_p3_sdo_SRC6,<I/O>
if (RTD298X_QFP176_PIN_61 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x6&0x7)<<10)); }; // 4: ld_spi0_p3_sdo_SRC6,<I/O>
if (RTD298X_QFP176_PIN_61 == 0x2) { rtd_maskl(0xb8000914, ~((0x3)<<11), ((0x0&0x3)<<11)); }; // 2: EMMC_Data_bit7_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_52_io 32
rtd_maskl(0xB8000840, 0xFF803FFF, (((RTD298X_QFP176_PIN_62 << 4) | (RTD298X_QFP176_PIN_62_UP << 3) | (RTD298X_QFP176_PIN_62_PD << 2) |(RTD298X_QFP176_PIN_62_DS << 1) | (RTD298X_QFP176_PIN_62_SR)) << 14));
if (RTD298X_QFP176_PIN_62 == 0x14) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x1&0x7)<<25)); }; // 14: EPI_LOCK_src1,<I>
if (RTD298X_QFP176_PIN_62 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x5&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_62 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x6&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_62 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x2&0x7)<<7)); }; // 4: EPI_LOCK_src1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_56_io 33
rtd_maskl(0xB8000844, 0xFFFFC01F, (((RTD298X_QFP176_PIN_63 << 4) | (RTD298X_QFP176_PIN_63_UP << 3) | (RTD298X_QFP176_PIN_63_PD << 2) |(RTD298X_QFP176_PIN_63_DS << 1) | (RTD298X_QFP176_PIN_63_SR)) << 5));
if (RTD298X_QFP176_PIN_63 == 0x12) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x3&0x1f)<<7)); }; // 12: I2C0_SDA_SRC3,<I/O>
if (RTD298X_QFP176_PIN_63 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x0&0xf)<<10)); }; // 8:
if (RTD298X_QFP176_PIN_63 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 7: test_en_bit20,<I/O>
if (RTD298X_QFP176_PIN_63 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 6:
if (RTD298X_QFP176_PIN_63 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x1&0x7)<<28)); }; // 2: I2C0_SDA_SRC3,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_53_io 34
rtd_maskl(0xB8000840, 0xFFFFC01F, (((RTD298X_QFP176_PIN_64 << 4) | (RTD298X_QFP176_PIN_64_UP << 3) | (RTD298X_QFP176_PIN_64_PD << 2) |(RTD298X_QFP176_PIN_64_DS << 1) | (RTD298X_QFP176_PIN_64_SR)) << 5));
if (RTD298X_QFP176_PIN_64 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x4&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_64 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x3&0x7)<<1)); }; // 10:
if (RTD298X_QFP176_PIN_64 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F: MIS_GPIO_bit53,<I/O>
if (RTD298X_QFP176_PIN_64 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x0&0x7)<<26)); }; // 9:
if (RTD298X_QFP176_PIN_64 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x5&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_64 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x5&0x7)<<10)); }; // 4:
if (RTD298X_QFP176_PIN_64 == 0x2) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x0&0x7)<<20)); }; // 2: uart1_rXdi_src0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_gpio_54_io 35
rtd_maskl(0xB8000844, 0x007FFFFF, (((RTD298X_QFP176_PIN_65 << 4) | (RTD298X_QFP176_PIN_65_UP << 3) | (RTD298X_QFP176_PIN_65_PD << 2) |(RTD298X_QFP176_PIN_65_DS << 1) | (RTD298X_QFP176_PIN_65_SR)) << 23));
if (RTD298X_QFP176_PIN_65 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x4&0x7)<<9)); }; // 15:
if (RTD298X_QFP176_PIN_65 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 10:
if (RTD298X_QFP176_PIN_65 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x5&0x1f)<<7)); }; // F: MIS_GPIO_bit54,<I/O>
if (RTD298X_QFP176_PIN_65 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x8&0xf)<<5)); }; // 8: SC1_DATA0_SRC8,<I/O>
if (RTD298X_QFP176_PIN_65 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x5&0x7)<<14)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXHP 36
rtd_maskl(0xB80008B8, 0x07FFFFFF, (RTD298X_QFP176_PIN_74) << 27);
if (RTD298X_QFP176_PIN_74 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<15), ((0x2&0x3)<<15)); }; // 10: P_CRS_SRC2,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXGP 37
rtd_maskl(0xB80008B8, 0xFFC1FFFF, (RTD298X_QFP176_PIN_75) << 17);
if (RTD298X_QFP176_PIN_75 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11:
if (RTD298X_QFP176_PIN_75 == 0x10) { rtd_maskl(0xb800091c, ~((0x7)<<18), ((0x2&0x7)<<18)); }; // 10:
if (RTD298X_QFP176_PIN_75 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x2&0x3)<<4)); }; // 7: DEMOD_ANT_TX_SRC2,<I/O>
if (RTD298X_QFP176_PIN_75 == 0x2) { rtd_maskl(0xb8000914, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 2:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXGN 38
rtd_maskl(0xB80008B8, 0xFFFE0FFF, (RTD298X_QFP176_PIN_76) << 12);
if (RTD298X_QFP176_PIN_76 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x9&0xf)<<8)); }; // 11: I2C2_SDA_SRC9,<I/O>
if (RTD298X_QFP176_PIN_76 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<17), ((0x2&0x7)<<17)); }; // 10: P_RXER_SRC2,<I>,<HS>
if (RTD298X_QFP176_PIN_76 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x2&0x3)<<0)); }; // 7:
if (RTD298X_QFP176_PIN_76 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x2&0x7)<<19)); }; // 6:
if (RTD298X_QFP176_PIN_76 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x0&0xf)<<28)); }; // 5:
if (RTD298X_QFP176_PIN_76 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x0&0x7)<<14)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXFP 39
rtd_maskl(0xB80008B8, 0xFFFFF07F, (RTD298X_QFP176_PIN_77) << 7);
if (RTD298X_QFP176_PIN_77 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x2&0x3)<<21)); }; // A:
if (RTD298X_QFP176_PIN_77 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: I2C2_SCL_SRC2,<I/O>
if (RTD298X_QFP176_PIN_77 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x1&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_77 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<4), ((0x1&0x3)<<4)); }; // 7: test_en_bit30,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXFN 40
rtd_maskl(0xB80008B8, 0xFFFFFF83, (RTD298X_QFP176_PIN_78) << 2);
if (RTD298X_QFP176_PIN_78 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x2&0xf)<<8)); }; // 11: I2C2_SDA_SRC2,<I/O>
if (RTD298X_QFP176_PIN_78 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x2&0x3)<<19)); }; // B:
if (RTD298X_QFP176_PIN_78 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<0), ((0x1&0x3)<<0)); }; // 7: test_en_bit31,<I/O>
if (RTD298X_QFP176_PIN_78 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x3&0x7)<<19)); }; // 6:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXEP 41
rtd_maskl(0xB80008BC, 0x07FFFFFF, (RTD298X_QFP176_PIN_79) << 27);
if (RTD298X_QFP176_PIN_79 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 15: VBY1_HTPD_src1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXEN 42
rtd_maskl(0xB80008BC, 0xF83FFFFF, (RTD298X_QFP176_PIN_80) << 22);
if (RTD298X_QFP176_PIN_80 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x1&0x7)<<9)); }; // 15: VBY1_LOCK_src1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXDP 43
rtd_maskl(0xB80008BC, 0xFFC1FFFF, (RTD298X_QFP176_PIN_81) << 17);
if (RTD298X_QFP176_PIN_81 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x8&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC8,<I>
if (RTD298X_QFP176_PIN_81 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x4&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC4,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXDN 44
rtd_maskl(0xB80008BC, 0xFFFE0FFF, (RTD298X_QFP176_PIN_82) << 12);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCP 45
rtd_maskl(0xB80008BC, 0xFFFFF07F, (RTD298X_QFP176_PIN_83) << 7);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXCN 46
rtd_maskl(0xB80008BC, 0xFFFFFF83, (RTD298X_QFP176_PIN_84) << 2);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXBP 47
rtd_maskl(0xB80008C0, 0x07FFFFFF, (RTD298X_QFP176_PIN_85) << 27);
if (RTD298X_QFP176_PIN_85 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 15: VBY1_HTPD_src0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXBN 48
rtd_maskl(0xB80008C0, 0xF83FFFFF, (RTD298X_QFP176_PIN_86) << 22);
if (RTD298X_QFP176_PIN_86 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x0&0x7)<<9)); }; // 15: VBY1_LOCK_src0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXAP 49
rtd_maskl(0xB80008C0, 0xFFC1FFFF, ((RTD298X_QFP176_PIN_87) << 17));
if (RTD298X_QFP176_PIN_87 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SCL_SRC10,<I/O>
if (RTD298X_QFP176_PIN_87 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SCL_SRC8,<I/O>
if (RTD298X_QFP176_PIN_87 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x2&0x3)<<2)); }; // 7:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P0_TXAN 50
rtd_maskl(0xB80008C0, 0xFFFE0FFF, ((RTD298X_QFP176_PIN_88) << 12) );
if (RTD298X_QFP176_PIN_88 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0xa&0xf)<<8)); }; // 11: I2C2_SDA_SRC10,<I/O>
if (RTD298X_QFP176_PIN_88 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x8&0x1f)<<7)); }; // F: I2C0_SDA_SRC8,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXGP 51
rtd_maskl(0xB80008C0, 0xFFFFF07F, (RTD298X_QFP176_PIN_90) << 7);
if (RTD298X_QFP176_PIN_90 == 0x11) { rtd_maskl(0xb8000918, ~((0x7)<<1), ((0x4&0x7)<<1)); }; // 11:
if (RTD298X_QFP176_PIN_90 == 0x10) { rtd_maskl(0xb8000918, ~((0x7)<<11), ((0x2&0x7)<<11)); }; // 10:
if (RTD298X_QFP176_PIN_90 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F: I2C2_SCL_SRC3,<I/O>
if (RTD298X_QFP176_PIN_90 == 0xA) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x1&0x7)<<20)); }; // A:
if (RTD298X_QFP176_PIN_90 == 0x9) { rtd_maskl(0xb80008fc, ~((0x7)<<26), ((0x1&0x7)<<26)); }; // 9:
if (RTD298X_QFP176_PIN_90 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x6&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_90 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 5:
if (RTD298X_QFP176_PIN_90 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x0&0x7)<<10)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXGN 52
rtd_maskl(0xB80008C0, 0xFFFFFF83, (RTD298X_QFP176_PIN_91) << 2);
if (RTD298X_QFP176_PIN_91 == 0x11) { rtd_maskl(0xb800091c, ~((0x7)<<28), ((0x4&0x7)<<28)); }; // 11:
if (RTD298X_QFP176_PIN_91 == 0x10) { rtd_maskl(0xb8000918, ~((0x3)<<8), ((0x2&0x3)<<8)); }; // 10:
if (RTD298X_QFP176_PIN_91 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x3&0xf)<<8)); }; // F: I2C2_SDA_SRC3,<I/O>
if (RTD298X_QFP176_PIN_91 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x3&0x7)<<28)); }; // 6: CR_SD_CMD_SRC3,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXFP 53
rtd_maskl(0xB80008C4, 0x07FFFFFF, (RTD298X_QFP176_PIN_92) << 27);
if (RTD298X_QFP176_PIN_92 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11: I2C2_SCL_SRC4,<I/O>
if (RTD298X_QFP176_PIN_92 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10: I2C0_SCL_SRC6,<I/O>
if (RTD298X_QFP176_PIN_92 == 0xA) { rtd_maskl(0xb8000904, ~((0x3)<<21), ((0x0&0x3)<<21)); }; // A:
if (RTD298X_QFP176_PIN_92 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 6:
if (RTD298X_QFP176_PIN_92 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x7&0xf)<<18)); }; // 5: ld_spi1_p4_sdi_SRC7,<I>
if (RTD298X_QFP176_PIN_92 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x3&0x7)<<7)); }; // 4: ld_spi0_p4_sdi_SRC3,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXFN 54
rtd_maskl(0xB80008C4, 0xF83FFFFF, (RTD298X_QFP176_PIN_93) << 22);
if (RTD298X_QFP176_PIN_93 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x4&0xf)<<8)); }; // 11:
if (RTD298X_QFP176_PIN_93 == 0x10) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x6&0x1f)<<7)); }; // 10:
if (RTD298X_QFP176_PIN_93 == 0xB) { rtd_maskl(0xb8000904, ~((0x3)<<19), ((0x0&0x3)<<19)); }; // B: USB_PWR_FLAG1_SRC0,<I>
if (RTD298X_QFP176_PIN_93 == 0x7) { rtd_maskl(0xb8000900, ~((0x3)<<2), ((0x1&0x3)<<2)); }; // 7: DEMOD_ANT_RX_SRC1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXEP 55
rtd_maskl(0xB80008C4, 0xFFC1FFFF, (RTD298X_QFP176_PIN_94) << 17);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXEN 56
rtd_maskl(0xB80008C4, 0xFFFE0FFF, (RTD298X_QFP176_PIN_95) << 12);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXDP 57
rtd_maskl(0xB80008C4, 0xFFFFF07F, (RTD298X_QFP176_PIN_96) << 7);
if (RTD298X_QFP176_PIN_96 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SCL_SRC6,<I/O>
if (RTD298X_QFP176_PIN_96 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<18), ((0x0&0xf)<<18)); }; // 5:
if (RTD298X_QFP176_PIN_96 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<7), ((0x0&0x7)<<7)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXDN 58
rtd_maskl(0xB80008C4, 0xFFFFFF83, (RTD298X_QFP176_PIN_97) << 2);
if (RTD298X_QFP176_PIN_97 == 0x11) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x6&0xf)<<8)); }; // 11: I2C2_SDA_SRC6,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXCP 59
rtd_maskl(0xB80008C8, 0x07FFFFFF, (RTD298X_QFP176_PIN_98) << 27);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXCN 60
rtd_maskl(0xB80008C8, 0xF83FFFFF, (RTD298X_QFP176_PIN_99) << 22);
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXBP 61
rtd_maskl(0xB80008C8, 0xFFFFF07F, (RTD298X_QFP176_PIN_100) << 17);
if (RTD298X_QFP176_PIN_100 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SCL_SRC9,<I/O>
if (RTD298X_QFP176_PIN_100 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x2&0x7)<<16)); }; // 8: uart0_rXdi_src2,<I>
if (RTD298X_QFP176_PIN_100 == 0x5) { rtd_maskl(0xb8000900, ~((0x7)<<24), ((0x7&0x7)<<24)); }; // 5:
if (RTD298X_QFP176_PIN_100 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<10), ((0x7&0x7)<<10)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXBN 62
rtd_maskl(0xB80008C8, 0xFFFE0FFF, (RTD298X_QFP176_PIN_101) << 12);
if (RTD298X_QFP176_PIN_101 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x9&0x1f)<<7)); }; // F: I2C0_SDA_SRC9,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXAP 63
rtd_maskl(0xB80008C8, 0xFFFFF07F, (RTD298X_QFP176_PIN_102) << 7);
if (RTD298X_QFP176_PIN_102 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SCL_SRC8,<I/O>
if (RTD298X_QFP176_PIN_102 == 0x8) { rtd_maskl(0xb80008fc, ~((0x7)<<20), ((0x4&0x7)<<20)); }; // 8: uart1_rXdi_src4,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: PLT_P1_TXAN 64
rtd_maskl(0xB80008C8, 0xFFFFFF83, (RTD298X_QFP176_PIN_103) << 2);
if (RTD298X_QFP176_PIN_103 == 0xF) { rtd_maskl(0xb80008fc, ~((0xf)<<8), ((0x8&0xf)<<8)); }; // F: I2C2_SDA_SRC8,<I/O>
if (RTD298X_QFP176_PIN_103 == 0x5) { rtd_maskl(0xb8000900, ~((0xf)<<28), ((0x7&0xf)<<28)); }; // 5:
if (RTD298X_QFP176_PIN_103 == 0x4) { rtd_maskl(0xb8000900, ~((0x7)<<14), ((0x7&0x7)<<14)); }; // 4:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_7_io 65
rtd_maskl(0xB806024C, 0xFFFFC01F, (((RTD298X_QFP176_PIN_105 << 4) | (RTD298X_QFP176_PIN_105_UP << 3) | (RTD298X_QFP176_PIN_105_PD << 2) |(RTD298X_QFP176_PIN_105_DS << 1) | (RTD298X_QFP176_PIN_105_SR)) << 5));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_8_io 66
rtd_maskl(0xB806024C, 0xFF803FFF, (((RTD298X_QFP176_PIN_106 << 4) | (RTD298X_QFP176_PIN_106_UP << 3) | (RTD298X_QFP176_PIN_106_PD << 2) |(RTD298X_QFP176_PIN_106_DS << 1) | (RTD298X_QFP176_PIN_106_SR)) << 14));
if (RTD298X_QFP176_PIN_106 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<16), ((0x1&0x7)<<16)); }; // 15: GSPI_SCLK_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_106 == 0x11) { rtd_maskl(0xb80602a0, ~((0x3)<<29), ((0x0&0x3)<<29)); }; // 11: VFD_D_SRC0,<I/O>
if (RTD298X_QFP176_PIN_106 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x0&0x7)<<2)); }; // 8: irrX_src0,<I>
if (RTD298X_QFP176_PIN_106 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<4), ((0x0&0x1)<<4)); }; // 3: PCMCIA_IREQ1_N_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_9_io 67
rtd_maskl(0xB806024C, 0x007FFFFF, (((RTD298X_QFP176_PIN_107 << 4) | (RTD298X_QFP176_PIN_107_UP << 3) | (RTD298X_QFP176_PIN_107_PD << 2) |(RTD298X_QFP176_PIN_107_DS << 1) | (RTD298X_QFP176_PIN_107_SR)) << 23));
if (RTD298X_QFP176_PIN_107 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<13), ((0x5&0x7)<<13)); }; // 15:
if (RTD298X_QFP176_PIN_107 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<12), ((0x1&0x7)<<12)); }; // 14: GSPI_DI_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_107 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SCL_SRC1,<I/O>
if (RTD298X_QFP176_PIN_107 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x3&0x7)<<16)); }; // 8:
if (RTD298X_QFP176_PIN_107 == 0x3) { rtd_maskl(0xb8000928, ~((0x3)<<0), ((0x0&0x3)<<0)); }; // 3: PCMCIA_CD1_N_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_10_io 68
rtd_maskl(0xB8060248, 0xFFFFC01F, (((RTD298X_QFP176_PIN_108 << 4) | (RTD298X_QFP176_PIN_108_UP << 3) | (RTD298X_QFP176_PIN_108_PD << 2) |(RTD298X_QFP176_PIN_108_DS << 1) | (RTD298X_QFP176_PIN_108_SR)) << 5));
if (RTD298X_QFP176_PIN_108 == 0x15) { rtd_maskl(0xb8000904, ~((0x7)<<9), ((0x5&0x7)<<9)); }; // 15: VBY1_LOCK_src5,<I>
if (RTD298X_QFP176_PIN_108 == 0x14) { rtd_maskl(0xb8000920, ~((0x7)<<8), ((0x1&0x7)<<8)); }; // 14: GSPI_CS_N_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_108 == 0x13) { rtd_maskl(0xb8000904, ~((0x7)<<25), ((0x2&0x7)<<25)); }; // 13: EPI_LOCK_src2,<I>
if (RTD298X_QFP176_PIN_108 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x1&0x1f)<<7)); }; // F: I2C0_SDA_SRC1,<I/O>
if (RTD298X_QFP176_PIN_108 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x0&0x3)<<18)); }; // A:
if (RTD298X_QFP176_PIN_108 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x0&0x7)<<13)); }; // 9:
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_11_io 69
rtd_maskl(0xB8060248, 0xFF803FFF, (((RTD298X_QFP176_PIN_109 << 4) | (RTD298X_QFP176_PIN_109_UP << 3) | (RTD298X_QFP176_PIN_109_PD << 2) |(RTD298X_QFP176_PIN_109_DS << 1) | (RTD298X_QFP176_PIN_109_SR)) << 14));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_12_io 70
rtd_maskl(0xB8060248, 0x007FFFFF, (((RTD298X_QFP176_PIN_110 << 4) | (RTD298X_QFP176_PIN_110_UP << 3) | (RTD298X_QFP176_PIN_110_PD << 2) |(RTD298X_QFP176_PIN_110_DS << 1) | (RTD298X_QFP176_PIN_110_SR)) << 23));
if (RTD298X_QFP176_PIN_110 == 0x15) { rtd_maskl(0xb8000920, ~((0x7)<<4), ((0x1&0x7)<<4)); }; // 15: GSPI_DO_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_110 == 0x12) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0xa&0xf)<<5)); }; // 12: SC1_DATA0_SRC10,<I/O>
if (RTD298X_QFP176_PIN_110 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SCL_SRC4,<I/O>
if (RTD298X_QFP176_PIN_110 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x2&0xf)<<23)); }; // 6:
if (RTD298X_QFP176_PIN_110 == 0x5) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x0&0x7)<<19)); }; // 5: GSPI_DO_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_110 == 0x3) { rtd_maskl(0xb8000928, ~((0x1)<<6), ((0x0&0x1)<<6)); }; // 3: I2S_out_MCLK,<O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_13_io 71
rtd_maskl(0xB8060244, 0xFFFFC01F, (((RTD298X_QFP176_PIN_111 << 4) | (RTD298X_QFP176_PIN_111_UP << 3) | (RTD298X_QFP176_PIN_111_PD << 2) |(RTD298X_QFP176_PIN_111_DS << 1) | (RTD298X_QFP176_PIN_111_SR)) << 5));
if (RTD298X_QFP176_PIN_111 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x4&0x1f)<<7)); }; // F: I2C0_SDA_SRC4,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_14_io 72
rtd_maskl(0xB8060204, 0x007FFFFF, (((RTD298X_QFP176_PIN_112 << 4) | (RTD298X_QFP176_PIN_112_UP << 3) | (RTD298X_QFP176_PIN_112_PD << 2) |(RTD298X_QFP176_PIN_112_DS << 1) | (RTD298X_QFP176_PIN_112_SR)) << 23));
if (RTD298X_QFP176_PIN_112 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SDA_SRC2,<I/O>
if (RTD298X_QFP176_PIN_112 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x1&0x3)<<8)); }; // 5: HDDC0_SDA_SRC1,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_15_io 73
rtd_maskl(0xB8060200, 0xFFFFC01F, (((RTD298X_QFP176_PIN_113 << 4) | (RTD298X_QFP176_PIN_113_UP << 3) | (RTD298X_QFP176_PIN_113_PD << 2) |(RTD298X_QFP176_PIN_113_DS << 1) | (RTD298X_QFP176_PIN_113_SR)) << 5));
if (RTD298X_QFP176_PIN_113 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x2&0x1f)<<7)); }; // F: I2C0_SCL_SRC2,<I/O>
if (RTD298X_QFP176_PIN_113 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<16), ((0x0&0x7)<<16)); }; // 9: uart0_rXdi_src0,<I>
if (RTD298X_QFP176_PIN_113 == 0x5) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x1&0x3)<<5)); }; // 5: HDDC0_SCL_SRC1,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_16_io 74
rtd_maskl(0xB8060244, 0xFF803FFF, (((RTD298X_QFP176_PIN_114 << 4) | (RTD298X_QFP176_PIN_114_UP << 3) | (RTD298X_QFP176_PIN_114_PD << 2) |(RTD298X_QFP176_PIN_114_DS << 1) | (RTD298X_QFP176_PIN_114_SR)) << 14));
if (RTD298X_QFP176_PIN_114 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x1&0x7)<<2)); }; // 9: irrX_src1,<I>
if (RTD298X_QFP176_PIN_114 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 6: CR_SD_CMD_SRC0,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_17_io 75
rtd_maskl(0xB8060204, 0xFF803FFF, (((RTD298X_QFP176_PIN_115 << 4) | (RTD298X_QFP176_PIN_115_UP << 3) | (RTD298X_QFP176_PIN_115_PD << 2) |(RTD298X_QFP176_PIN_115_DS << 1) | (RTD298X_QFP176_PIN_115_SR)) << 14));
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_18_io 76
rtd_maskl(0xB8060204, 0xFFFFC01F, (((RTD298X_QFP176_PIN_116 << 4) | (RTD298X_QFP176_PIN_116_UP << 3) | (RTD298X_QFP176_PIN_116_PD << 2) |(RTD298X_QFP176_PIN_116_DS << 1) | (RTD298X_QFP176_PIN_116_SR)) << 5));
if (RTD298X_QFP176_PIN_116 == 0x8) { rtd_maskl(0xb80602a0, ~((0x7)<<2), ((0x4&0x7)<<2)); }; // 8: irrX_src4,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_19_io 77
rtd_maskl(0xB8060244, 0x007FFFFF, (((RTD298X_QFP176_PIN_117 << 4) | (RTD298X_QFP176_PIN_117_UP << 3) | (RTD298X_QFP176_PIN_117_PD << 2) |(RTD298X_QFP176_PIN_117_DS << 1) | (RTD298X_QFP176_PIN_117_SR)) << 23));
if (RTD298X_QFP176_PIN_117 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0x5&0xf)<<10)); }; // 8: SC1_CD_SRC5,<I>
if (RTD298X_QFP176_PIN_117 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<28), ((0x0&0x7)<<28)); }; // 7: SC0_CD_SRC0,<I>
if (RTD298X_QFP176_PIN_117 == 0x6) { rtd_maskl(0xb8000910, ~((0xf)<<23), ((0x7&0xf)<<23)); }; // 6: CR_SD_WP_SRC7,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_20_io 78
rtd_maskl(0xB8060208, 0x007FFFFF, (((RTD298X_QFP176_PIN_118 << 4) | (RTD298X_QFP176_PIN_118_UP << 3) | (RTD298X_QFP176_PIN_118_PD << 2) |(RTD298X_QFP176_PIN_118_DS << 1) | (RTD298X_QFP176_PIN_118_SR)) << 23));
if (RTD298X_QFP176_PIN_118 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<19), ((0x1&0x7)<<19)); }; // 6: CR_SD_CD_SRC1,<I>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_21_io 79
rtd_maskl(0xB8060208, 0xFF803FFF, (((RTD298X_QFP176_PIN_119 << 4) | (RTD298X_QFP176_PIN_119_UP << 3) | (RTD298X_QFP176_PIN_119_PD << 2) |(RTD298X_QFP176_PIN_119_DS << 1) | (RTD298X_QFP176_PIN_119_SR)) << 14));
if (RTD298X_QFP176_PIN_119 == 0x8) { rtd_maskl(0xb800090c, ~((0xf)<<5), ((0x6&0xf)<<5)); }; // 8: SC1_DATA0_SRC6,<I/O>
if (RTD298X_QFP176_PIN_119 == 0x7) { rtd_maskl(0xb800090c, ~((0x7)<<24), ((0x0&0x7)<<24)); }; // 7: SC0_DATA0_SRC0,<I/O>
if (RTD298X_QFP176_PIN_119 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<15), ((0x1&0x7)<<15)); }; // 6: CR_SD_Data_bit0_SRC1,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_22_io 80
rtd_maskl(0xB8060240, 0xFFFFC01F, (((RTD298X_QFP176_PIN_120 << 4) | (RTD298X_QFP176_PIN_120_UP << 3) | (RTD298X_QFP176_PIN_120_PD << 2) |(RTD298X_QFP176_PIN_120_DS << 1) | (RTD298X_QFP176_PIN_120_SR)) << 5));
if (RTD298X_QFP176_PIN_120 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<11), ((0x1&0x7)<<11)); }; // 6: CR_SD_Data_bit1_SRC1,<I/O>,<HS>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_23_io 81
rtd_maskl(0xB8060200, 0x007FFFFF, (((RTD298X_QFP176_PIN_121 << 4) | (RTD298X_QFP176_PIN_121_UP << 3) | (RTD298X_QFP176_PIN_121_PD << 2) |(RTD298X_QFP176_PIN_121_DS << 1) | (RTD298X_QFP176_PIN_121_SR)) << 23));
if (RTD298X_QFP176_PIN_121 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SCL_SRC0,<I/O>
if (RTD298X_QFP176_PIN_121 == 0xA) { rtd_maskl(0xb80008fc, ~((0x3)<<18), ((0x1&0x3)<<18)); }; // A: uart1_cts_n_src1,<I>
if (RTD298X_QFP176_PIN_121 == 0x9) { rtd_maskl(0xb80602a0, ~((0x7)<<13), ((0x1&0x7)<<13)); }; // 9: uart0_cts_n_src1,<I>
if (RTD298X_QFP176_PIN_121 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<7), ((0x1&0x7)<<7)); }; // 6: CR_SD_Data_bit2_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_121 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<5), ((0x0&0x3)<<5)); }; // 4: HDDC0_SCL_SRC0,<I>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: pad_st_gpio_24_io 82
rtd_maskl(0xB8060200, 0xFF803FFF, (((RTD298X_QFP176_PIN_122 << 4) | (RTD298X_QFP176_PIN_122_UP << 3) | (RTD298X_QFP176_PIN_122_PD << 2) |(RTD298X_QFP176_PIN_122_DS << 1) | (RTD298X_QFP176_PIN_122_SR)) << 14));
if (RTD298X_QFP176_PIN_122 == 0x14) { rtd_maskl(0xb800090c, ~((0xf)<<10), ((0xa&0xf)<<10)); }; // 14: SC1_CD_SRC10,<I>
if (RTD298X_QFP176_PIN_122 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0x0&0x1f)<<7)); }; // F: I2C0_SDA_SRC0,<I/O>
if (RTD298X_QFP176_PIN_122 == 0x6) { rtd_maskl(0xb8000910, ~((0x7)<<3), ((0x1&0x7)<<3)); }; // 6: CR_SD_Data_bit3_SRC1,<I/O>,<HS>
if (RTD298X_QFP176_PIN_122 == 0x4) { rtd_maskl(0xb8000914, ~((0x3)<<8), ((0x0&0x3)<<8)); }; // 4: HDDC0_SDA_SRC0,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
// PAD_NAME: LSADC_REF_APAD 83
rtd_maskl(0xB806020C, 0x07FFFFFF, (RTD298X_QFP176_PIN_123) << 27);
// PAD_NAME: LSADC0_APAD 84
rtd_maskl(0xB8060210, 0x07FFFFFF, (RTD298X_QFP176_PIN_124) << 27);
// PAD_NAME: LSADC1_APAD 85
rtd_maskl(0xB806020C, 0xFFFFFF83, (RTD298X_QFP176_PIN_125) << 2);
// PAD_NAME: LSADC2_APAD 86
rtd_maskl(0xB806020C, 0xFFFFF07F, (RTD298X_QFP176_PIN_126) << 7);
// PAD_NAME: LSADC7_APAD 87
rtd_maskl(0xB806020C, 0xF83FFFFF, (RTD298X_QFP176_PIN_127) << 22);
// PAD_NAME: STB_GPIO_APAD 88
rtd_maskl(0xB8060218, 0xFFC01FFF, (((RTD298X_QFP176_PIN_129 << 4) | (RTD298X_QFP176_PIN_129_UP << 3) | (RTD298X_QFP176_PIN_129_PD << 2) |(RTD298X_QFP176_PIN_129_DS << 1) | (RTD298X_QFP176_PIN_129_SR)) << 13));
// PAD_NAME: VSYNC_APAD 89
rtd_maskl(0xB80008D8, 0x007FFFFF, (((RTD298X_QFP176_PIN_161 << 4) | (RTD298X_QFP176_PIN_161_UP << 3) | (RTD298X_QFP176_PIN_161_PD << 2) |(RTD298X_QFP176_PIN_161_DS << 1) | (RTD298X_QFP176_PIN_161_SR)) << 23));
// PAD_NAME: HSYNC_APAD 90
rtd_maskl(0xB80008D8, 0xF803FFFF, (((RTD298X_QFP176_PIN_162 << 4) | (RTD298X_QFP176_PIN_162_UP << 3) | (RTD298X_QFP176_PIN_162_PD << 2) |(RTD298X_QFP176_PIN_162_DS << 1) | (RTD298X_QFP176_PIN_162_SR)) << 18));
// PAD_NAME: VIN_0P_APAD 91
rtd_maskl(0xB80008DC, 0x007FFFFF, (((RTD298X_QFP176_PIN_163 << 4) | (RTD298X_QFP176_PIN_163_UP << 3) | (RTD298X_QFP176_PIN_163_PD << 2) |(RTD298X_QFP176_PIN_163_DS << 1) | (RTD298X_QFP176_PIN_163_SR)) << 23));
// PAD_NAME: VIN_BN_APAD 92
rtd_maskl(0xB80008DC, 0xF803FFFF, (((RTD298X_QFP176_PIN_164 << 4) | (RTD298X_QFP176_PIN_164_UP << 3) | (RTD298X_QFP176_PIN_164_PD << 2) |(RTD298X_QFP176_PIN_164_DS << 1) | (RTD298X_QFP176_PIN_164_SR)) << 18));
// PAD_NAME: VIN_1P_APAD 93
rtd_maskl(0xB80008DC, 0xFFC01FFF, (((RTD298X_QFP176_PIN_165 << 4) | (RTD298X_QFP176_PIN_165_UP << 3) | (RTD298X_QFP176_PIN_165_PD << 2) |(RTD298X_QFP176_PIN_165_DS << 1) | (RTD298X_QFP176_PIN_165_SR)) << 13));
// PAD_NAME: VIN_2P_APAD 94
rtd_maskl(0xB80008DC, 0xFFFE00FF, (((RTD298X_QFP176_PIN_166 << 4) | (RTD298X_QFP176_PIN_166_UP << 3) | (RTD298X_QFP176_PIN_166_PD << 2) |(RTD298X_QFP176_PIN_166_DS << 1) | (RTD298X_QFP176_PIN_166_SR)) << 8));
// PAD_NAME: VIN_13P_APAD 95
rtd_maskl(0xB80008E8, 0x007FFFFF, (((RTD298X_QFP176_PIN_172 << 4) | (RTD298X_QFP176_PIN_172_UP << 3) | (RTD298X_QFP176_PIN_172_PD << 2) |(RTD298X_QFP176_PIN_172_DS << 1) | (RTD298X_QFP176_PIN_172_SR)) << 23));
// PAD_NAME: VIN_A0N_APAD 96
rtd_maskl(0xB80008E4, 0xFFC01FFF, (((RTD298X_QFP176_PIN_173 << 4) | (RTD298X_QFP176_PIN_173_UP << 3) | (RTD298X_QFP176_PIN_173_PD << 2) |(RTD298X_QFP176_PIN_173_DS << 1) | (RTD298X_QFP176_PIN_173_SR)) << 13));
// PAD_NAME: VIN_12P_APAD 97
rtd_maskl(0xB80008E4, 0xF803FFFF, (((RTD298X_QFP176_PIN_174 << 4) | (RTD298X_QFP176_PIN_174_UP << 3) | (RTD298X_QFP176_PIN_174_PD << 2) |(RTD298X_QFP176_PIN_174_DS << 1) | (RTD298X_QFP176_PIN_174_SR)) << 18));
if (RTD298X_QFP176_PIN_174 == 0xF) { rtd_maskl(0xb80602a0, ~((0x1f)<<7), ((0xc&0x1f)<<7)); }; // F: I2C0_SCL_SRC12,<I/O>
DEBUG_PRINT("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
} 

#endif /* endif of #if defined(CONFIG_BOARD_298X_TV001_QFP176_EMMC)*/
