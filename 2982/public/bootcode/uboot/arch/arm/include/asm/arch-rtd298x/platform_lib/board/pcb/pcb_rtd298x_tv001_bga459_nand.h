#include <platform_lib/board/pcb_rtd298x_bga459_library.h>
#include "pcb_define.h"

// PAD_NAME: VDAC_IDACO_TV_APAD 0
#define RTD298X_BGA459_PIN_W3								(0x0C&0x1F)//0xB80008EC[21:17];
																							//03: TCON_bit16,<O>
																							//0C: VDAC_OUT,<AO>
																							//1F: MIS_GPIO_bit129,<I/O>
																							//def: VDAC_OUT,<AO>
//not in 0xB800_08EC
//#define RTD298X_BGA459_PIN_W3_UP							(1&0x01)// 0xB80008EC[16]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_W3_PD							(0&0x01)// 0xB80008EC[15]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_W3_DS							(0&0x01)// 0xB80008EC[14]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_W3_SR							(0&0x01)// 0xB80008EC[13]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI2L_APAD 1
#define RTD298X_BGA459_PIN_Y3								(0x0C&0x1F)//0xB80008F0[31:27];
																							//06: CR_SD_WP_SRC0,<I>,<HS>
																							//08: uart1_tXdo,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: BB_AI2L,<AI>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_6,<OD>
																							//10: P_COL_SRC4,<I>,<HS>
																							//11: P_RXER_SRC4,<I>,<HS>
																							//1F: MIS_GPIO_bit130,<I/O>
																							//def: BB_AI2L,<AI>
//not in 0xB800_08F0
//#define RTD298X_BGA459_PIN_Y3_UP							(1&0x01)// 0xB80008F0[26]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_Y3_PD							(0&0x01)// 0xB80008F0[25]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_Y3_DS							(0&0x01)// 0xB80008F0[24]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_Y3_SR							(0&0x01)// 0xB80008F0[23]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI2R_APAD 2
#define RTD298X_BGA459_PIN_AA1								(0x0C&0x1F)//0xB80008F0[26:22];
																							//08: uart1_rXdi_src5,<I>
																							//09: ETN_LED_TXRX,<O>
																							//0C: BB_AI2R,<AI>
																							//0D: misc_uni_pwm1,<O>
																							//0E: misc_pwm_5,<OD>
																							//11: P_RXDV_SRC4,<I>,<HS>
																							//1F: MIS_GPIO_bit131,<I/O>
																							//def: BB_AI2R,<AI>																		
//not in 0xB800_08F0
//#define RTD298X_BGA459_PIN_AA1_UP							(1&0x01)// 0xB80008F0[21]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA1_PD							(0&0x01)// 0xB80008F0[20]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA1_DS							(0&0x01)// 0xB80008F0[19]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AA1_SR							(0&0x01)// 0xB80008F0[18]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI3L_APAD 3
#define RTD298X_BGA459_PIN_AA2								(0x0C&0x1F)//0xB80008F0[21:17];
																							//0C: BB_AI3L,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_7,<OD>
																							//1F: MIS_GPIO_bit132,<I/O>
																							//def: BB_AI3L,<AI>
//not in 0xB800_08F0
//#define RTD298X_BGA459_PIN_AA2_UP							(1&0x01)// 0xB80008F0[16]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA2_PD							(0&0x01)// 0xB80008F0[15]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA2_DS							(0&0x01)// 0xB80008F0[14]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AA2_SR							(0&0x01)// 0xB80008F0[13]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI3R_APAD 4
#define RTD298X_BGA459_PIN_AA3								(0x0C&0x1F)//0xB80008F0[16:12];
																							//0A: SPDIF_OUT,<O>
																							//0C: BB_AI3R,<AI>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_6,<OD>
																							//1F: MIS_GPIO_bit133,<I/O>
																							//def: BB_AI3R,<AI>
//not in 0xB800_08F0
//#define RTD298X_BGA459_PIN_AA3_UP							(1&0x01)// 0xB80008F0[11]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA3_PD							(0&0x01)// 0xB80008F0[10]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AA3_DS							(0&0x01)// 0xB80008F0[9]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AA3_SR							(0&0x01)// 0xB80008F0[8]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AIO1L_APAD 5
#define RTD298X_BGA459_PIN_AD1								(0x12&0x1F)//0xB80008F4[26:22];
																							//03: TCON_bit19,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: BB_AIO1L,<AO>
																							//0D: misc_uni_pwm1,<O>
																							//0E: misc_pwm_5,<OD>
																							//12: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit136,<I/O>
																							//def: BB_AIO1L,<AO>
//not in 0xB800_08F4
//#define RTD298X_BGA459_PIN_AD1_UP							(1&0x01)// 0xB80008F4[21]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AD1_PD							(0&0x01)// 0xB80008F4[20]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AD1_DS							(0&0x01)// 0xB80008F4[19]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AD1_SR							(0&0x01)// 0xB80008F4[18]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AIO1R_APAD 6
#define RTD298X_BGA459_PIN_AD2								(0x12&0x1F)//0xB80008F4[21:17];
																							//03: TCON_bit1,<O>
																							//0C: BB_AIO1R,<AO>
																							//12: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit137,<I/O>
																							//def: BB_AIO1R,<AO>
//not in 0xB800_08F4
//#define RTD298X_BGA459_PIN_AD2_UP							(1&0x01)// 0xB80008F4[16]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AD2_PD							(0&0x01)// 0xB80008F4[15]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AD2_DS							(0&0x01)// 0xB80008F4[14]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AD2_SR							(0&0x01)// 0xB80008F4[13]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_HPOL_APAD:2 7
#define RTD298X_BGA459_PIN_AE2								(0x0C&0x1F)//0xB80008F4[16:12];
																							//03: TCON_bit2,<O>
																							//0C: BB_HPOL,<AO>
																							//0D: misc_uni_pwm4,<O>
																							//0E: misc_pwm_4,<OD>
																							//1F: MIS_GPIO_bit138,<I/O>
																							//def: BB_HPOL,<AO>
//not in 0xB800_08F4
//#define RTD298X_BGA459_PIN_AE2_UP							(1&0x01)// 0xB80008F4[11]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE2_PD							(0&0x01)// 0xB80008F4[10]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE2_DS							(0&0x01)// 0xB80008F4[9]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AE2_SR							(0&0x01)// 0xB80008F4[8]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_HPOR_APAD:2 8
#define RTD298X_BGA459_PIN_AE1								(0x0C&0x1F)//0xB80008F4[11:7];
																							//03: TCON_bit3,<O>
																							//0C: BB_HPOR,<AO>
																							//1F: MIS_GPIO_bit139,<I/O>
																							//def: BB_HPOR,<AO>
//not in 0xB800_08F4
//#define RTD298X_BGA459_PIN_AE1_UP							(1&0x01)// 0xB80008F4[6]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE1_PD							(0&0x01)// 0xB80008F4[5]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE1_DS							(0&0x01)// 0xB80008F4[4]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AE1_SR							(0&0x01)// 0xB80008F4[3]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_DIO3_APAD 9
#define RTD298X_BGA459_PIN_AB4								(0x1F&0x1F)//0xB80008F8[21:17];
																							//03: TCON_bit6,<O>
																							//04: TCON_bit22,<O>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_7,<OD>
																							//1F: MIS_GPIO_bit196,<I/O>
																							//def: MIS_GPIO_bit196,<I/O>
//not in 0xB800_08F8
//#define RTD298X_BGA459_PIN_AB4_UP							(1&0x01)// 0xB80008F8[16]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AB4_PD							(0&0x01)// 0xB80008F8[15]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AB4_DS							(0&0x01)// 0xB80008F8[14]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AB4_SR							(0&0x01)// 0xB80008F8[13]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_0_io 10
#define RTD298X_BGA459_PIN_AE4								(0x13&0x1F)//0xB8000800[31:27];
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//17: test_en_bit0,<I/O>
																							//1F: MIS_GPIO_bit0,<I/O>
																							//def: MIS_GPIO_bit0,<I/O>
//not in 0xB800_08F8
//#define RTD298X_BGA459_PIN_AE4_UP							(1&0x01)// 0xB8000800[26]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE4_PD							(0&0x01)// 0xB8000800[25]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AE4_DS							(0&0x01)// 0xB8000800[24]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AE4_SR							(0&0x01)// 0xB8000800[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_1_io 11
#define RTD298X_BGA459_PIN_AB10								(0x16&0x1F)//0xB8000800[22:18];
																							//03: DEMOD_I2C_SCL_RELAY,<OD>
																							//11: I2C0_SCL_SRC7,<I/O>
																							//12: I2C1_SCL_SRC0,<I/O>
																							//16: TP0_Data_bit4_SRC2,<I>,<HS>
																							//17: test_en_bit1,<I/O>
																							//1F: MIS_GPIO_bit1,<I/O>
																							//def: MIS_GPIO_bit1,<I/O>
//not in 0xB800_08F8
//#define RTD298X_BGA459_PIN_AB10_UP							(1&0x01)// 0xB8000800[17]: Pull Up 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AB10_PD							(0&0x01)// 0xB8000800[16]: Pull Down 0:disable 1:enable
//#define RTD298X_BGA459_PIN_AB10_DS							(0&0x01)// 0xB8000800[15]: Driving Strength 0:4mA 1:8mA
//#define RTD298X_BGA459_PIN_AB10_SR							(0&0x01)// 0xB8000800[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_2_io 12
#define RTD298X_BGA459_PIN_AB9								(0x16&0x1F)//0xB8000804[31:27];
																							//03: DEMOD_I2C_SDA_RELAY,<I/O>
																							//11: I2C0_SDA_SRC7,<I/O>
																							//12: I2C1_SDA_SRC0,<I/O>
																							//16: TP0_Data_bit3_SRC2,<I>,<HS>
																							//17: test_en_bit2,<I/O>
																							//1F: MIS_GPIO_bit2,<I/O>
																							//def: MIS_GPIO_bit2,<I/O>
#define RTD298X_BGA459_PIN_AB9_UP							(1&0x01)// 0xB8000804[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB9_PD							(0&0x01)// 0xB8000804[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB9_DS							(0&0x01)// 0xB8000804[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB9_SR							(0&0x01)// 0xB8000804[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_16_io 13
#define RTD298X_BGA459_PIN_Y14								(0x16&0x1F)//0xB8000814[13:9];
																							//00: TP2_Data_bit0_SRC1,<I>,<HS>
																							//01: TP0_Data_bit0_SRC0,<I>,<HS>
																							//02: EMMC_Data_bit7_SRC1,<I/O>,<HS>
																							//03: TCON_bit6,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//11: I2C2_SCL_SRC1,<I/O>
																							//16: TPO_Data_bit3_pad,<O>,<HS>
																							//17: test_en_bit3,<I/O>
																							//1F: MIS_GPIO_bit16,<I/O>
																							//def: MIS_GPIO_bit16,<I/O>
#define RTD298X_BGA459_PIN_Y14_UP							(1&0x01)// 0xB8000814[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y14_PD							(0&0x01)// 0xB8000814[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y14_DS							(0&0x01)// 0xB8000814[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y14_SR							(0&0x01)// 0xB8000814[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_17_io 14
#define RTD298X_BGA459_PIN_AD13								(0x16&0x1F)//0xB8000818[31:27];
																							//00: TP2_SYNC_SRC1,<I>,<HS>
																							//01: TP0_SYNC_SRC0,<I>,<HS>
																							//02: EMMC_Data_bit6_SRC1,<I/O>,<HS>
																							//03: TCON_bit7,<O>
																							//05: ld_spi1_p2_sck_src5,<I/O>
																							//08: SC1_DATA0_SRC9,<I/O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1,<OD>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//15: VBY1_LOCK_src3,<I>
																							//16: TPO_VAL_pad,<O>,<HS>
																							//17: test_en_bit4,<I/O>
																							//1F: MIS_GPIO_bit17,<I/O>
																							//def: MIS_GPIO_bit17,<I/O>
#define RTD298X_BGA459_PIN_AD13_UP							(1&0x01)// 0xB8000818[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD13_PD							(0&0x01)// 0xB8000818[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD13_DS							(0&0x01)// 0xB8000818[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD13_SR							(0&0x01)// 0xB8000818[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_18_io 15
#define RTD298X_BGA459_PIN_AE13								(0x16&0x1F)//0xB8000818[22:18];
																							//00: TP2_VAL_SRC1,<I>,<HS>
																							//01: TP0_VAL_SRC0,<I>,<HS>
																							//02: EMMC_Data_bit5_SRC1,<I/O>,<HS>
																							//03: TCON_bit12,<O>
																							//05: ld_spi1_p3_sdo_SRC5,<I/O>
																							//08: SC1_RST,<OD>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_5,<OD>
																							//11: I2C2_SDA_SRC1,<I/O>
																							//12: I2S_out_Data0,<O>
																							//13: I2S_out_SCLK,<O>
																							//16: PCMCIA_IREQ0_N_SRC2,<I>,<HS>
																							//17: test_en_bit5,<I/O>
																							//1F: MIS_GPIO_bit18,<I/O>
																							//def: MIS_GPIO_bit18,<I/O>
#define RTD298X_BGA459_PIN_AE13_UP							(1&0x01)// 0xB8000818[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE13_PD							(0&0x01)// 0xB8000818[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE13_DS							(0&0x01)// 0xB8000818[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE13_SR							(0&0x01)// 0xB8000818[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_19_io 16
#define RTD298X_BGA459_PIN_AD14								(0x16&0x1F)//0xB8000818[13:9];
																							//00: TP2_CLK_SRC1,<I>,<HS>
																							//01: TP0_CLK_SRC0,<I>,<HS>
																							//02: EMMC_Data_bit4_SRC1,<I/O>,<HS>
																							//03: TCON_bit13,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//08: SC1_CD_SRC11,<I>
																							//09: ETN_LED_TXRX,<O>
																							//0B: I2S_out_Data0,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//10: I2S_out_MCLK,<O>
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//16: PCMCIA_WE_N,<O>,<HS>
																							//17: test_en_bit6,<I/O>
																							//1F: MIS_GPIO_bit19,<I/O>
																							//def: MIS_GPIO_bit19,<I/O>
#define RTD298X_BGA459_PIN_AD14_UP							(1&0x01)// 0xB8000818[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD14_PD							(0&0x01)// 0xB8000818[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD14_DS							(0&0x01)// 0xB8000818[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD14_SR							(0&0x01)// 0xB8000818[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_39_io 17
#define RTD298X_BGA459_PIN_Y19								(0x00&0x1F)//0xB8000830[31:27];
																							//00: nf_tmX_cle,<O>,<HS>
																							//01: SPI_SCLK,<O>,<HS>
																							//02: EMMC_CLK,<O>,<HS>
																							//03: TCON_bit14,<O>
																							//06: CR_SD_CLK,<O>,<HS>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_TXRX,<O>
																							//0A: ETN_LED_LINK,<O>
																							//0D: misc_pwm_5,<OD>
																							//0F: TCON_bit23,<O>
																							//10: P_TXD0,<O>,<HS>
																							//15: GSPI_SCLK_SRC0,<I/O>,<HS>
																							//17: test_en_bit7,<I/O>
																							//1F: MIS_GPIO_bit39,<I/O>
																							//def: MIS_GPIO_bit39,<I/O>
#define RTD298X_BGA459_PIN_Y19_UP							(0&0x01)// 0xB8000830[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y19_PD							(0&0x01)// 0xB8000830[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y19_DS							(0&0x01)// 0xB8000830[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y19_SR							(0&0x01)// 0xB8000830[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_40_io 18
#define RTD298X_BGA459_PIN_AB19								(0x00&0x1F)//0xB8000830[22:18];
																							//00: nf_tmX_wr_n,<O>,<HS>
																							//01: SPI_DI,<I/O>,<HS>
																							//03: TCON_bit15,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0B: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm2,<O>
																							//0D: misc_pwm_6,<OD>
																							//0F: TCON_bit24,<O>
																							//10: P_TXC_SRC2,<I>,<HS>
																							//14: EPI_LOCK_src0,<I>
																							//15: GSPI_DI_SRC0,<I/O>
																							//17: test_en_bit8,<I/O>
																							//1F: MIS_GPIO_bit40,<I/O>
																							//def: MIS_GPIO_bit40,<I/O>
#define RTD298X_BGA459_PIN_AB19_UP							(0&0x01)// 0xB8000830[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB19_PD							(0&0x01)// 0xB8000830[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB19_DS							(0&0x01)// 0xB8000830[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB19_SR							(0&0x01)// 0xB8000830[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_41_io 19
#define RTD298X_BGA459_PIN_AE20								(0x00&0x1F)//0xB8000830[13:9];
																							//00: nf_tmX_ce_n_bit0,<O>,<HS>
																							//01: SPI_CS_N,<O>,<HS>
																							//03: TCON_bit16,<O>
																							//07: SC0_RST,<OD>
																							//08: SC1_RST,<OD>
																							//09: ETN_LED_LINK,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0B: SPDIF_OUT,<O>
																							//0D: misc_pwm_7,<OD>
																							//0F: TCON_bit20,<O>
																							//12: SC0_PWR_SEL,<OD>
																							//13: SC1_PWR_SEL,<OD>
																							//14: SC1_CD_SRC9,<I>
																							//15: GSPI_CS_N_SRC0,<I/O>,<HS>
																							//17: test_en_bit9,<I/O>
																							//1F: MIS_GPIO_bit41,<I/O>
																							//def: MIS_GPIO_bit41,<I/O>
#define RTD298X_BGA459_PIN_AE20_UP							(1&0x01)// 0xB8000830[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE20_PD							(0&0x01)// 0xB8000830[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE20_DS							(0&0x01)// 0xB8000830[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE20_SR							(0&0x01)// 0xB8000830[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_42_io 20
#define RTD298X_BGA459_PIN_AA19								(0x00&0x1F)//0xB8000834[31:27];
																							//00: nf_tmX_ale,<O>,<HS>
																							//01: SPI_DO,<I/O>,<HS>
																							//03: TCON_bit17,<O>
																							//07: SC0_DATA0_SRC3,<I/O>
																							//08: SC1_DATA0_SRC4,<I/O>
																							//0F: TCON_bit21,<O>
																							//10: P_RXC_SRC2,<I>,<HS>
																							//15: GSPI_DO_SRC0,<I/O>,<HS>
																							//17: test_en_bit10,<I/O>
																							//1F: MIS_GPIO_bit42,<I/O>
																							//def: MIS_GPIO_bit42,<I/O>
#define RTD298X_BGA459_PIN_AA19_UP							(0&0x01)// 0xB8000834[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA19_PD							(0&0x01)// 0xB8000834[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA19_DS							(0&0x01)// 0xB8000834[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA19_SR							(0&0x01)// 0xB8000834[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_35_io 21
#define RTD298X_BGA459_PIN_AC13								(0x16&0x1F)//0xB8000828[13:9];
																							//00: nf_tmX_ce_n_bit0,<O>,<HS>
																							//01: TPO_Data_bit1_pad,<O>,<HS>
																							//02: TTL_hsout,<O>,<HS>
																							//03: TCON_bit8,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//06: CR_SD_CLK,<O>,<HS>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm6,<O>
																							//0D: misc_pwm_3,<OD>
																							//13: I2S_out_Data1,<O>
																							//16: PCMCIA_ADDR_bit6,<OD>,<HS>
																							//17: test_en_bit11,<I/O>
																							//1F: MIS_GPIO_bit35,<I/O>
																							//def: MIS_GPIO_bit35,<I/O>
#define RTD298X_BGA459_PIN_AC13_UP							(1&0x01)// 0xB8000828[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC13_PD							(0&0x01)// 0xB8000828[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC13_DS							(0&0x01)// 0xB8000828[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC13_SR							(0&0x01)// 0xB8000828[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_44_io 22
#define RTD298X_BGA459_PIN_AC14								(0x00&0x1F)//0xB8000834[13:9];
																							//00: nf_tmX_bit0,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit9,<OD>,<HS>
																							//02: EMMC_Data_bit0_SRC0,<I/O>,<HS>
																							//03: TCON_bit3,<O>
																							//0D: misc_pwm_0,<OD>
																							//0F: TCON_bit20,<O>
																							//13: I2S_out_MCLK,<O>
																							//17: test_en_bit12,<I/O>
																							//1F: MIS_GPIO_bit44,<I/O>
																							//def: MIS_GPIO_bit44,<I/O>
#define RTD298X_BGA459_PIN_AC14_UP							(0&0x01)// 0xB8000834[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC14_PD							(0&0x01)// 0xB8000834[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC14_DS							(0&0x01)// 0xB8000834[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC14_SR							(0&0x01)// 0xB8000834[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_45_io 23
#define RTD298X_BGA459_PIN_AC12								(0x00&0x1F)//0xB8000838[31:27];
																							//00: nf_tmX_bit1,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit8,<OD>,<HS>
																							//02: EMMC_Data_bit1_SRC0,<I/O>,<HS>
																							//03: TCON_bit4,<O>
																							//0D: misc_pwm_1,<OD>
																							//0F: TCON_bit21,<O>
																							//13: I2S_out_WCLK,<O>
																							//17: test_en_bit13,<I/O>
																							//1F: MIS_GPIO_bit45,<I/O>
																							//def: MIS_GPIO_bit45,<I/O>
#define RTD298X_BGA459_PIN_AC12_UP							(0&0x01)// 0xB8000838[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC12_PD							(0&0x01)// 0xB8000838[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC12_DS							(0&0x01)// 0xB8000838[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC12_SR							(0&0x01)// 0xB8000838[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_46_io 24
#define RTD298X_BGA459_PIN_AE16								(0x00&0x1F)//0xB8000838[22:18];
																							//00: nf_tmX_bit2,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit13,<OD>,<HS>
																							//02: EMMC_Data_bit2_SRC0,<I/O>,<HS>
																							//03: TCON_bit5,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_2,<OD>
																							//13: I2S_out_SCLK,<O>
																							//17: test_en_bit14,<I/O>
																							//1F: MIS_GPIO_bit46,<I/O>
																							//def: MIS_GPIO_bit46,<I/O>
#define RTD298X_BGA459_PIN_AE16_UP							(0&0x01)// 0xB8000838[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE16_PD							(0&0x01)// 0xB8000838[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE16_DS							(0&0x01)// 0xB8000838[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE16_SR							(0&0x01)// 0xB8000838[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_47_io 25
#define RTD298X_BGA459_PIN_AD17								(0x00&0x1F)//0xB8000838[13:9];
																							//00: nf_tmX_bit3,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit14,<OD>,<HS>
																							//02: EMMC_Data_bit3_SRC0,<I/O>,<HS>
																							//03: TCON_bit6,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: misc_pwm_3,<OD>
																							//13: I2S_out_Data0,<O>
																							//17: test_en_bit15,<I/O>
																							//1F: MIS_GPIO_bit47,<I/O>
																							//def: MIS_GPIO_bit47,<I/O>
#define RTD298X_BGA459_PIN_AD17_UP							(0&0x01)// 0xB8000838[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD17_PD							(0&0x01)// 0xB8000838[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD17_DS							(0&0x01)// 0xB8000838[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD17_SR							(0&0x01)// 0xB8000838[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_48_io 26
#define RTD298X_BGA459_PIN_AE17								(0x00&0x1F)//0xB800083C[31:27];
																							//00: nf_tmX_bit4,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit5,<OD>,<HS>
																							//02: EMMC_Data_bit4_SRC0,<I/O>,<HS>
																							//03: TCON_bit7,<O>
																							//0D: misc_pwm_4,<OD>
																							//13: I2S_out_Data1,<O>
																							//17: test_en_bit16,<I/O>
																							//1F: MIS_GPIO_bit48,<I/O>
																							//def: MIS_GPIO_bit48,<I/O>
#define RTD298X_BGA459_PIN_AE17_UP							(0&0x01)// 0xB800083C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE17_PD							(0&0x01)// 0xB800083C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE17_DS							(0&0x01)// 0xB800083C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE17_SR							(0&0x01)// 0xB800083C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_49_io 27
#define RTD298X_BGA459_PIN_AC16								(0x00&0x1F)//0xB800083C[22:18];
																							//00: nf_tmX_bit5,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit3,<OD>,<HS>
																							//02: EMMC_Data_bit5_SRC0,<I/O>,<HS>
																							//03: TCON_bit8,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_5,<OD>
																							//13: I2S_out_MCLK,<O>
																							//17: test_en_bit17,<I/O>
																							//1F: MIS_GPIO_bit49,<I/O>
																							//def: MIS_GPIO_bit49,<I/O>
#define RTD298X_BGA459_PIN_AC16_UP							(0&0x01)// 0xB800083C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC16_PD							(0&0x01)// 0xB800083C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC16_DS							(0&0x01)// 0xB800083C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC16_SR							(0&0x01)// 0xB800083C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_50_io 28
#define RTD298X_BGA459_PIN_AC18								(0x00&0x1F)//0xB800083C[13:9];
																							//00: nf_tmX_bit6,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit4,<OD>,<HS>
																							//02: EMMC_Data_bit6_SRC0,<I/O>,<HS>
																							//03: TCON_bit13,<O>
																							//04: ld_spi0_p2_sck_src6,<I/O>
																							//05: ld_spi1_p2_sck_src6,<I/O>
																							//09: ETN_LED_LINK,<O>
																							//0D: misc_pwm_6,<OD>
																							//13: I2S_out_WCLK,<O>
																							//17: test_en_bit18,<I/O>
																							//1F: MIS_GPIO_bit50,<I/O>
																							//def: MIS_GPIO_bit50,<I/O>
#define RTD298X_BGA459_PIN_AC18_UP							(0&0x01)// 0xB800083C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC18_PD							(0&0x01)// 0xB800083C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC18_DS							(0&0x01)// 0xB800083C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC18_SR							(0&0x01)// 0xB800083C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_51_io 29
#define RTD298X_BGA459_PIN_AD18								(0x00&0x1F)//0xB8000840[31:27];
																							//00: nf_tmX_bit7,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit2,<OD>,<HS>
																							//02: EMMC_Data_bit7_SRC0,<I/O>,<HS>
																							//03: TCON_bit18,<O>
																							//04: ld_spi0_p3_sdo_SRC6,<I/O>
																							//05: ld_spi1_p3_sdo_SRC6,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: misc_pwm_7,<OD>
																							//13: I2S_out_SCLK,<O>
																							//17: test_en_bit19,<I/O>
																							//1F: MIS_GPIO_bit51,<I/O>
																							//def: MIS_GPIO_bit51,<I/O>
#define RTD298X_BGA459_PIN_AD18_UP							(0&0x01)// 0xB8000840[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD18_PD							(0&0x01)// 0xB8000840[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD18_DS							(0&0x01)// 0xB8000840[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD18_SR							(0&0x01)// 0xB8000840[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_52_io 30
#define RTD298X_BGA459_PIN_AC19								(0x00&0x1F)//0xB8000840[22:18];
																							//00: nf_tmX_rd_n,<O>,<HS>
																							//02: EMMC_CLK,<O>,<HS>
																							//03: TCON_bit19,<O>
																							//04: ld_spi0_p4_sdi_SRC2,<I>
																							//05: ld_spi1_p4_sdi_SRC6,<I>
																							//06: CR_SD_WP_SRC5,<I>,<HS>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_0,<OD>
																							//0F: TCON_bit22,<O>
																							//13: I2S_out_Data0,<O>
																							//14: EPI_LOCK_src1,<I>
																							//1F: MIS_GPIO_bit52,<I/O>
																							//def: MIS_GPIO_bit52,<I/O>
#define RTD298X_BGA459_PIN_AC19_UP							(0&0x01)// 0xB8000840[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC19_PD							(0&0x01)// 0xB8000840[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC19_DS							(0&0x01)// 0xB8000840[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC19_SR							(0&0x01)// 0xB8000840[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_56_io 31
#define RTD298X_BGA459_PIN_AE19								(0x00&0x1F)//0xB8000844[13:9];
																							//00: tmX_nf_rdy,<I/O>,<HS>
																							//02: EMMC_CMD_SRC1,<I/O>,<HS>
																							//03: TCON_bit12,<O>
																							//04: ld_spi0_p6_h_sync,<O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//06: CR_SD_CMD_SRC1,<I/O>,<HS>
																							//07: SC0_CD_SRC4,<I>
																							//08: SC1_CD_SRC0,<I>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_1,<OD>
																							//12: I2C0_SDA_SRC3,<I/O>
																							//17: test_en_bit20,<I/O>
																							//1F: MIS_GPIO_bit56,<I/O>
																							//def: MIS_GPIO_bit56,<I/O>
#define RTD298X_BGA459_PIN_AE19_UP							(0&0x01)// 0xB8000844[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE19_PD							(0&0x01)// 0xB8000844[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE19_DS							(0&0x01)// 0xB8000844[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE19_SR							(0&0x01)// 0xB8000844[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_53_io 32
#define RTD298X_BGA459_PIN_AD20								(0x02&0x1F)//0xB8000840[13:9];
																							//02: uart1_rXdi_src0,<I>
																							//03: TCON_bit11,<O>
																							//04: ld_spi0_p3_sdo_SRC5,<I/O>
																							//05: ld_spi1_p4_sdi_SRC5,<I>
																							//08: SC1_SCLK,<OD>
																							//09: uart2_rXdi_src0,<I>
																							//0A: ETN_LED_LINK,<O>
																							//0B: I2S_out_MCLK,<O>
																							//0C: misc_uni_pwm3,<O>
																							//0D: misc_pwm_5,<OD>
																							//0E: ETN_CLK_OUT,<O>,<HS>
																							//0F: I2C0_SCL_SRC5,<I/O>
																							//10: P_RXD2_SRC3,<I>,<HS>
																							//15: VBY1_HTPD_src4,<I>
																							//1F: MIS_GPIO_bit53,<I/O>
																							//def: MIS_GPIO_bit53,<I/O>
#define RTD298X_BGA459_PIN_AD20_UP							(1&0x01)// 0xB8000840[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD20_PD							(0&0x01)// 0xB8000840[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD20_DS							(0&0x01)// 0xB8000840[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD20_SR							(0&0x01)// 0xB8000840[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_54_io 33
#define RTD298X_BGA459_PIN_AC20								(0x02&0x1F)//0xB8000844[31:27];
																							//00: nf_tmX_ce_n_bit1,<O>,<HS>
																							//02: uart1_tXdo,<O>
																							//03: TCON_bit10,<O>
																							//04: ld_spi0_p2_sck_src5,<I/O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//06: SC0_PWR_SEL,<OD>
																							//08: SC1_DATA0_SRC8,<I/O>
																							//09: uart2_tXdo,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0B: I2S_out_Data0,<O>
																							//0C: misc_uni_pwm2,<O>
																							//0D: misc_pwm_2,<OD>
																							//0E: SPDIF_OUT,<O>
																							//0F: I2C0_SDA_SRC5,<I/O>
																							//10: P_RXD3_SRC3,<I>,<HS>
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//15: VBY1_LOCK_src4,<I>
																							//1F: MIS_GPIO_bit54,<I/O>
																							//def: MIS_GPIO_bit54,<I/O>
#define RTD298X_BGA459_PIN_AC20_UP							(1&0x01)// 0xB8000844[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC20_PD							(0&0x01)// 0xB8000844[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC20_DS							(0&0x01)// 0xB8000844[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC20_SR							(0&0x01)// 0xB8000844[23]: Slew rate 0:fast 1:slow


// PAD_NAME: PLT_P0_TXHP 34
#define RTD298X_BGA459_PIN_F24								(0x0D&0x1F)//0xB80008B8[31:27];
																							//00: LVDS_A_HP,<AO>
																							//01: SPI_CS_N,<O>,<HS>
																							//03: TCON_bit8,<O>
																							//09: IRTX,<O>
																							//0C: misc_uni_pwm6,<O>
																							//0D: misc_pwm_3_src0,<I/O>
																							//0F: TCON_bit20,<O>
																							//10: P_CRS_SRC2,<I>,<HS>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data0,<O>
																							//1F: MIS_GPIO_bit141,<I/O>
																							//def: MIS_GPIO_bit141,<I/O>


// PAD_NAME: PLT_P0_TXGP 35
#define RTD298X_BGA459_PIN_F23								(0x0A&0x1F)//0xB80008B8[21:17];
																							//00: LVDS_PORT_1_D5P,<AO>
																							//02: EMMC_CMD_SRC3,<I/O>,<HS>
																							//03: TCON_bit0,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//07: DEMOD_ANT_TX_SRC2,<I/O>
																							//08: IRTX,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm6,<O>
																							//0D: misc_pwm_3_src1,<I/O>
																							//0F: TCON_bit22,<O>
																							//10: P_COL_SRC2,<I>,<HS>
																							//11: I2C2_SCL_SRC9,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_Data1,<O>
																							//1F: MIS_GPIO_bit81,<I/O>
																							//def: MIS_GPIO_bit81,<I/O>


// PAD_NAME: PLT_P0_TXGN 36
#define RTD298X_BGA459_PIN_E25								(0x1F&0x1F)//0xB80008B8[16:12];
																							//00: LVDS_PORT_1_D5N,<AO>
																							//03: TCON_bit1,<O>
																							//04: ld_spi0_p2_sck_src0,<I/O>
																							//05: ld_spi1_p2_sck_src0,<I/O>
																							//06: CR_SD_CD_SRC2,<I>,<HS>
																							//07: DEMOD_ANT_OE_SRC2,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1_src1,<I/O>
																							//0F: TCON_bit23,<O>
																							//10: P_RXER_SRC2,<I>,<HS>
																							//11: I2C2_SDA_SRC9,<I/O>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data0,<O>
																							//1F: MIS_GPIO_bit82,<I/O>
																							//def: MIS_GPIO_bit82,<I/O>


// PAD_NAME: PLT_P0_TXFP 37
#define RTD298X_BGA459_PIN_E24								(0x00&0x1F)//0xB80008B8[11:7];
																							//00: LVDS_A_FP,<AO>
																							//02: TTL_denout,<O>,<HS>
																							//03: TCON_bit2,<O>
																							//06: CR_SD_WP_SRC1,<I>,<HS>
																							//07: DEMOD_ANT_TX_SRC1,<I/O>
																							//09: ETN_LED_LINK,<O>
																							//0A: USB_PWR_FLAG0_SRC2,<I>
																							//0B: USB_PWR_CTRL1,<O>
																							//0C: misc_uni_pwm2,<O>
																							//0D: misc_pwm_2_src0,<I/O>
																							//10: P_HIF_en,<I>
																							//11: I2C2_SCL_SRC2,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//17: test_en_bit30,<I/O>
																							//1F: MIS_GPIO_bit57,<I/O>
																							//def: MIS_GPIO_bit57,<I/O>


// PAD_NAME: PLT_P0_TXFN 38
#define RTD298X_BGA459_PIN_E23								(0x00&0x1F)//0xB80008B8[6:2];
																							//00: LVDS_A_FN,<AO>
																							//02: TTL_vsout,<O>,<HS>
																							//03: TCON_bit3,<O>
																							//06: CR_SD_CD_SRC3,<I>,<HS>
																							//07: DEMOD_ANT_OE_SRC1,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0A: USB_PWR_CTRL0,<O>
																							//0B: USB_PWR_FLAG1_SRC2,<I>
																							//0C: misc_uni_pwm3,<O>
																							//0D: misc_pwm_3_src2,<I/O>
																							//11: I2C2_SDA_SRC2,<I/O>
																							//12: I2S_out_Data0,<O>
																							//13: I2S_out_SCLK,<O>
																							//17: test_en_bit31,<I/O>
																							//1F: MIS_GPIO_bit58,<I/O>
																							//def: MIS_GPIO_bit58,<I/O>


// PAD_NAME: PLT_P0_TXEP 39
#define RTD298X_BGA459_PIN_D24								(0x00&0x1F)//0xB80008BC[31:27];
																							//00: LVDS_A_EP,<AO>
																							//02: TTL_bout_bit5,<O>,<HS>
																							//03: TCON_bit4,<O>
																							//10: p_hif_clk_en,<I>,<HS>
																							//15: VBY1_HTPD_src1,<I>
																							//17: test_en_bit32,<I/O>
																							//1F: MIS_GPIO_bit59,<I/O>
																							//def: MIS_GPIO_bit59,<I/O>


// PAD_NAME: PLT_P0_TXEN 40
#define RTD298X_BGA459_PIN_D23								(0x00&0x1F)//0xB80008BC[26:22];
																							//00: LVDS_A_EN,<AO>
																							//02: TTL_bout_bit4,<O>,<HS>
																							//03: TCON_bit5,<O>
																							//10: P_HIF_RDY,<O>
																							//15: VBY1_LOCK_src1,<I>
																							//17: test_en_bit33,<I/O>
																							//1F: MIS_GPIO_bit60,<I/O>
																							//def: MIS_GPIO_bit60,<I/O>


// PAD_NAME: PLT_P0_TXDP 41
#define RTD298X_BGA459_PIN_C25								(0x00&0x1F)//0xB80008BC[21:17];
																							//00: LVDS_A_DP,<AO>
																							//02: TTL_bout_bit3,<O>,<HS>
																							//03: TCON_bit6,<O>
																							//04: ld_spi0_p4_sdi_SRC4,<I>
																							//05: ld_spi1_p4_sdi_SRC8,<I>
																							//10: P_HIF_Data_bit0,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_Data0,<O>
																							//17: test_en_bit34,<I/O>
																							//1F: MIS_GPIO_bit61,<I/O>
																							//def: MIS_GPIO_bit61,<I/O>


// PAD_NAME: PLT_P0_TXDN 42
#define RTD298X_BGA459_PIN_B25								(0x00&0x1F)//0xB80008BC[16:12];
																							//00: LVDS_A_DN,<AO>
																							//02: TTL_bout_bit2,<O>,<HS>
																							//03: TCON_bit7,<O>
																							//04: ld_spi0_p6_h_sync,<O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//10: P_HIF_Data_bit1,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_Data1,<O>
																							//17: test_en_bit35,<I/O>
																							//1F: MIS_GPIO_bit62,<I/O>
																							//def: MIS_GPIO_bit62,<I/O>


// PAD_NAME: PLT_P0_TXCP 43
#define RTD298X_BGA459_PIN_A25								(0x00&0x1F)//0xB80008BC[11:7];
																							//00: LVDS_A_CP,<AO>
																							//02: TTL_bout_bit1,<O>,<HS>
																							//03: TCON_bit8,<O>
																							//10: P_HIF_Data_bit2,<I/O>
																							//1F: MIS_GPIO_bit63,<I/O>
																							//def: MIS_GPIO_bit63,<I/O>


// PAD_NAME: PLT_P0_TXCN 44
#define RTD298X_BGA459_PIN_C24								(0x00&0x1F)//0xB80008BC[6:2];
																							//00: LVDS_A_CN,<AO>
																							//02: TTL_bout_bit0,<O>,<HS>
																							//03: TCON_bit9,<O>
																							//10: P_HIF_Data_bit3,<I/O>
																							//1F: MIS_GPIO_bit64,<I/O>
																							//def: MIS_GPIO_bit64,<I/O>


// PAD_NAME: PLT_P0_TXBP 45
#define RTD298X_BGA459_PIN_A24								(0x00&0x1F)//0xB80008C0[31:27];
																							//00: LVDS_A_BP,<AO>
																							//02: TTL_gout_bit5,<O>,<HS>
																							//03: TCON_bit10,<O>
																							//10: P_HIF_Data_bit4,<I/O>
																							//15: VBY1_HTPD_src0,<I>
																							//1F: MIS_GPIO_bit65,<I/O>
																							//def: MIS_GPIO_bit65,<I/O>


// PAD_NAME: PLT_P0_TXBN 46
#define RTD298X_BGA459_PIN_B24								(0x00&0x1F)//0xB80008C0[26:22];
																							//00: LVDS_A_BN,<AO>
																							//02: TTL_gout_bit4,<O>,<HS>
																							//03: TCON_bit11,<O>
																							//10: P_HIF_Data_bit5,<I/O>
																							//15: VBY1_LOCK_src0,<I>
																							//1F: MIS_GPIO_bit66,<I/O>
																							//def: MIS_GPIO_bit66,<I/O>


// PAD_NAME: PLT_P0_TXAP 47
#define RTD298X_BGA459_PIN_C23								(0x00&0x1F)//0xB80008C0[21:17];
																							//00: LVDS_A_AP,<AO>
																							//02: TTL_gout_bit3,<O>,<HS>
																							//03: TCON_bit12,<O>
																							//07: DEMOD_ANT_RX_SRC2,<I>
																							//09: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm4,<O>
																							//0D: misc_pwm_4_src0,<I/O>
																							//0F: I2C0_SCL_SRC8,<I/O>
																							//10: P_HIF_Data_bit6,<I/O>
																							//11: I2C2_SCL_SRC10,<I/O>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data0,<O>
																							//1F: MIS_GPIO_bit67,<I/O>
																							//def: MIS_GPIO_bit67,<I/O>


// PAD_NAME: PLT_P0_TXAN 48
#define RTD298X_BGA459_PIN_B23								(0x00&0x1F)//0xB80008C0[16:12];
																							//00: LVDS_A_AN,<AO>
																							//02: TTL_gout_bit2,<O>,<HS>
																							//03: TCON_bit13,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_5_src0,<I/O>
																							//0F: I2C0_SDA_SRC8,<I/O>
																							//10: P_HIF_Data_bit7,<I/O>
																							//11: I2C2_SDA_SRC10,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit68,<I/O>
																							//def: MIS_GPIO_bit68,<I/O>


// PAD_NAME: PLT_P1_TXGP 49
#define RTD298X_BGA459_PIN_E22								(0x12&0x1F)//0xB80008C0[11:7];
																							//00: LVDS_PORT_2_D5P,<AO>
																							//01: TCON_bit20,<O>
																							//03: TCON_bit14,<O>
																							//04: ld_spi0_p3_sdo_SRC0,<I/O>
																							//05: ld_spi1_p3_sdo_SRC0,<I/O>
																							//06: CR_SD_WP_SRC6,<I>,<HS>
																							//08: IRTX,<O>
																							//09: uart2_rXdi_src1,<I>
																							//0A: uart1_rXdi_src1,<I>
																							//0C: misc_uni_pwm6,<O>
																							//0D: misc_pwm_6_src0,<I/O>
																							//0F: I2C2_SCL_SRC3,<I/O>
																							//10: P_RXDV_SRC2,<I>,<HS>
																							//11: P_RXD2_SRC4,<I>,<HS>
																							//12: I2S_out_Data0,<O>
																							//13: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit83,<I/O>
																							//def: MIS_GPIO_bit83,<I/O>


// PAD_NAME: PLT_P1_TXGN 50
#define RTD298X_BGA459_PIN_F22								(0x1F&0x1F)//0xB80008C0[6:2];
																							//00: LVDS_PORT_2_D5N,<AO>
																							//01: TCON_bit21,<O>
																							//03: TCON_bit15,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//06: CR_SD_CMD_SRC3,<I/O>,<HS>
																							//09: uart2_tXdo,<O>
																							//0A: uart1_tXdo,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_7_src0,<I/O>
																							//0F: I2C2_SDA_SRC3,<I/O>
																							//10: P_RXD0_SRC2,<I>,<HS>
																							//11: P_RXD3_SRC4,<I>,<HS>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit84,<I/O>
																							//def: MIS_GPIO_bit84,<I/O>


// PAD_NAME: PLT_P1_TXFP 51
#define RTD298X_BGA459_PIN_D21								(0x00&0x1F)//0xB80008C4[31:27];
																							//00: LVDS_B_FP,<AO>
																							//01: TCON_bit23,<O>
																							//02: TTL_hsout,<O>,<HS>
																							//03: TCON_bit16,<O>
																							//04: ld_spi0_p4_sdi_SRC3,<I>
																							//05: ld_spi1_p4_sdi_SRC7,<I>
																							//06: CR_SD_Data_bit2_SRC3,<I/O>,<HS>
																							//09: SPDIF_OUT,<O>
																							//0A: USB_PWR_FLAG0_SRC0,<I>
																							//0B: USB_PWR_CTRL1,<O>
																							//0D: misc_pwm_6_src1,<I/O>
																							//10: I2C0_SCL_SRC6,<I/O>
																							//11: I2C2_SCL_SRC4,<I/O>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data0,<O>
																							//1F: MIS_GPIO_bit69,<I/O>
																							//def: MIS_GPIO_bit69,<I/O>


// PAD_NAME: PLT_P1_TXFN 52
#define RTD298X_BGA459_PIN_D22								(0x00&0x1F)//0xB80008C4[26:22];
																							//00: LVDS_B_FN,<AO>
																							//01: TCON_bit24,<O>
																							//02: TTL_CLK,<O>,<HS>
																							//03: TCON_bit17,<O>
																							//04: ld_spi0_p6_h_sync,<O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//06: CR_SD_Data_bit3_SRC3,<I/O>,<HS>
																							//07: DEMOD_ANT_RX_SRC1,<I>
																							//0A: USB_PWR_CTRL0,<O>
																							//0B: USB_PWR_FLAG1_SRC0,<I>
																							//0D: misc_pwm_7_src1,<I/O>
																							//10: I2C0_SDA_SRC6,<I/O>
																							//11: I2C2_SDA_SRC4,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit70,<I/O>
																							//def: MIS_GPIO_bit70,<I/O>


// PAD_NAME: PLT_P1_TXEP 53
#define RTD298X_BGA459_PIN_F21								(0x00&0x1F)//0xB80008C4[21:17];
																							//00: LVDS_B_EP,<AO>
																							//02: TTL_gout_bit1,<O>,<HS>
																							//03: TCON_bit18,<O>
																							//10: P_HIF_Data_bit8,<I/O>
																							//1F: MIS_GPIO_bit71,<I/O>
																							//def: MIS_GPIO_bit71,<I/O>


// PAD_NAME: PLT_P1_TXEN 54
#define RTD298X_BGA459_PIN_E21								(0x00&0x1F)//0xB80008C4[16:12];
																							//00: LVDS_B_EN,<AO>
																							//02: TTL_gout_bit0,<O>,<HS>
																							//03: TCON_bit19,<O>
																							//10: P_HIF_Data_bit9,<I/O>
																							//1F: MIS_GPIO_bit72,<I/O>
																							//def: MIS_GPIO_bit72,<I/O>


// PAD_NAME: PLT_P1_TXDP 55
#define RTD298X_BGA459_PIN_C22								(0x00&0x1F)//0xB80008C4[11:7];
																							//00: LVDS_B_DP,<AO>
																							//03: TCON_bit0,<O>
																							//04: ld_spi0_p4_sdi_SRC0,<I>
																							//05: ld_spi1_p4_sdi_SRC0,<I>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm0,<O>
																							//0D: misc_pwm_0_src0,<I/O>
																							//11: I2C2_SCL_SRC6,<I/O>
																							//13: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit73,<I/O>
																							//def: MIS_GPIO_bit73,<I/O>


// PAD_NAME: PLT_P1_TXDN 56
#define RTD298X_BGA459_PIN_B22								(0x00&0x1F)//0xB80008C4[6:2];
																							//00: LVDS_B_DN,<AO>
																							//03: TCON_bit1,<O>
																							//04: ld_spi0_p6_h_sync,<O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1_src2,<I/O>
																							//11: I2C2_SDA_SRC6,<I/O>
																							//13: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit74,<I/O>
																							//def: MIS_GPIO_bit74,<I/O>


// PAD_NAME: PLT_P1_TXCP 57
#define RTD298X_BGA459_PIN_A22								(0x00&0x1F)//0xB80008C8[31:27];
																							//00: LVDS_B_CP,<AO>
																							//02: TTL_rout_bit5,<O>,<HS>
																							//03: TCON_bit2,<O>
																							//10: P_HIF_Data_bit10,<I/O>
																							//1F: MIS_GPIO_bit75,<I/O>
																							//def: MIS_GPIO_bit75,<I/O>


// PAD_NAME: PLT_P1_TXCN 58
#define RTD298X_BGA459_PIN_C21								(0x00&0x1F)//0xB80008C8[26:22];
																							//00: LVDS_B_CN,<AO>
																							//02: TTL_rout_bit4,<O>,<HS>
																							//03: TCON_bit3,<O>
																							//10: P_HIF_Data_bit11,<I/O>
																							//1F: MIS_GPIO_bit76,<I/O>
																							//def: MIS_GPIO_bit76,<I/O>


// PAD_NAME: PLT_P1_TXBP 59
#define RTD298X_BGA459_PIN_A21								(0x00&0x1F)//0xB80008C8[21:17];
																							//00: LVDS_B_BP,<AO>
																							//02: TTL_rout_bit3,<O>,<HS>
																							//03: TCON_bit4,<O>
																							//04: ld_spi0_p3_sdo_SRC7,<I/O>
																							//05: ld_spi1_p3_sdo_SRC7,<I/O>
																							//08: uart0_rXdi_src2,<I>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_2_src1,<I/O>
																							//0F: I2C0_SCL_SRC9,<I/O>
																							//10: P_HIF_Data_bit12,<I/O>
																							//12: I2S_out_Data0,<O>
																							//13: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit77,<I/O>
																							//def: MIS_GPIO_bit77,<I/O>


// PAD_NAME: PLT_P1_TXBN 60
#define RTD298X_BGA459_PIN_B21								(0x00&0x1F)//0xB80008C8[16:12];
																							//00: LVDS_B_BN,<AO>
																							//02: TTL_rout_bit2,<O>,<HS>
																							//03: TCON_bit5,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//08: uart0_tXdo,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: misc_pwm_3_src3,<I/O>
																							//0F: I2C0_SDA_SRC9,<I/O>
																							//10: P_HIF_Data_bit13,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit78,<I/O>
																							//def: MIS_GPIO_bit78,<I/O>
																							

// PAD_NAME: PLT_P1_TXAP 61
#define RTD298X_BGA459_PIN_C20								(0x00&0x1F)//0xB80008C8[11:7];
																							//00: LVDS_B_AP,<AO>
																							//02: TTL_rout_bit1,<O>,<HS>
																							//03: TCON_bit6,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//08: uart1_rXdi_src4,<I>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_4_src1,<I/O>
																							//0F: I2C2_SCL_SRC8,<I/O>
																							//10: P_HIF_Data_bit14,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_Data1,<O>
																							//1F: MIS_GPIO_bit79,<I/O>
																							//def: MIS_GPIO_bit79,<I/O>


// PAD_NAME: PLT_P1_TXAN 62
#define RTD298X_BGA459_PIN_B20								(0x00&0x1F)//0xB80008C8[6:2];
																							//00: LVDS_B_AN,<AO>
																							//02: TTL_rout_bit0,<O>,<HS>
																							//03: TCON_bit7,<O>
																							//04: ld_spi0_p2_sck_src7,<I/O>
																							//05: ld_spi1_p2_sck_src7,<I/O>
																							//08: uart1_tXdo,<O>
																							//0D: misc_pwm_5_src1,<I/O>
																							//0F: I2C2_SDA_SRC8,<I/O>
																							//10: P_HIF_Data_bit15,<I/O>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data0,<O>
																							//1F: MIS_GPIO_bit80,<I/O>
																							//def: MIS_GPIO_bit80,<I/O>


// PAD_NAME: pad_st_gpio_7_io 63
#define RTD298X_BGA459_PIN_E9								(0x1F&0x1F)//0xB806024C[13:9];
																							//02: ST_dbg_bit0,<I/O>
																							//03: TCON_bit16,<O>
																							//1F: ISO_MIS_GPIO_bit7,<I/O>
																							//def: ISO_MIS_GPIO_bit7,<I/O>
#define RTD298X_BGA459_PIN_E9_UP							(1&0x01)// 0xB806024C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E9_PD							(0&0x01)// 0xB806024C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E9_DS							(0&0x01)// 0xB806024C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E9_SR							(0&0x01)// 0xB806024C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_8_io 64
#define RTD298X_BGA459_PIN_C10								(0x08&0x1F)//0xB806024C[22:18];
																							//02: ST_dbg_bit1,<I/O>
																							//03: PCMCIA_IREQ1_N_SRC0,<I>
																							//04: TCON_bit17,<O>
																							//08: irrX_src0,<I>
																							//09: ETN_LED_LINK,<O>
																							//11: VFD_D_SRC0,<I/O>
																							//15: GSPI_SCLK_SRC1,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit8,<I/O>
																							//def: ISO_MIS_GPIO_bit8,<I/O>
#define RTD298X_BGA459_PIN_C10_UP							(1&0x01)// 0xB806024C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C10_PD							(0&0x01)// 0xB806024C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C10_DS							(0&0x01)// 0xB806024C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C10_SR							(0&0x01)// 0xB806024C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_9_io 65
#define RTD298X_BGA459_PIN_F9								(0x1F&0x1F)//0xB806024C[31:27];
																							//02: ST_dbg_bit2,<I/O>
																							//03: PCMCIA_CD1_N_SRC0,<I>
																							//04: TCON_bit10,<O>
																							//05: TCON_bit0,<O>
																							//06: VSYNC_DIG,<I>
																							//08: uart0_rXdi_src3,<I>
																							//09: uart0_rts_n,<O>
																							//0A: uart1_rts_n,<O>
																							//0B: SPDIF_OUT,<O>
																							//0F: I2C0_SCL_SRC1,<I/O>
																							//10: P_TXD2,<O>,<HS>
																							//11: VFD_CLK,<OD>
																							//14: GSPI_DI_SRC1,<I/O>,<HS>
																							//15: VBY1_HTPD_src5,<I>
																							//1F: ISO_MIS_GPIO_bit9,<I/O>
																							//def: ISO_MIS_GPIO_bit9,<I/O>
#define RTD298X_BGA459_PIN_F9_UP							(1&0x01)// 0xB806024C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F9_PD							(0&0x01)// 0xB806024C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F9_DS							(0&0x01)// 0xB806024C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F9_SR							(0&0x01)// 0xB806024C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_10_io 66
#define RTD298X_BGA459_PIN_B9								(0x1F&0x1F)//0xB8060248[13:9];
																							//02: ST_dbg_bit29,<I/O>
																							//03: TCON_bit1,<O>
																							//04: TCON_bit11,<O>
																							//05: CR_SD_CLK,<O>,<HS>
																							//06: HSYNC_DIG,<I>
																							//08: uart0_tXdo,<O>
																							//09: uart0_cts_n_src0,<I>
																							//0A: uart1_cts_n_src0,<I>
																							//0F: I2C0_SDA_SRC1,<I/O>
																							//10: P_TXD3,<O>,<HS>
																							//13: EPI_LOCK_src2,<I>
																							//14: GSPI_CS_N_SRC1,<I/O>,<HS>
																							//15: VBY1_LOCK_src5,<I>
																							//1F: ISO_MIS_GPIO_bit10,<I/O>
																							//def: ISO_MIS_GPIO_bit10,<I/O>
#define RTD298X_BGA459_PIN_B9_UP							(1&0x01)// 0xB8060248[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B9_PD							(0&0x01)// 0xB8060248[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B9_DS							(0&0x01)// 0xB8060248[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B9_SR							(0&0x01)// 0xB8060248[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_11_io 67
#define RTD298X_BGA459_PIN_C8								(0x1F&0x1F)//0xB8060248[22:18];
																							//02: ST_dbg_bit3,<I/O>
																							//03: PCMCIA_RST1,<OD>
																							//04: TCON_bit18,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: iso_misc_uni_pwm0,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//10: P_TXEN,<O>,<HS>
																							//11: VFD_CS_N,<OD>
																							//1F: ISO_MIS_GPIO_bit11,<I/O>
																							//def: ISO_MIS_GPIO_bit11,<I/O>
#define RTD298X_BGA459_PIN_C8_UP							(1&0x01)// 0xB8060248[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C8_PD							(0&0x01)// 0xB8060248[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C8_DS							(0&0x01)// 0xB8060248[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C8_SR							(0&0x01)// 0xB8060248[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_12_io 68
#define RTD298X_BGA459_PIN_E10								(0x1F&0x1F)//0xB8060248[31:27];
																							//01: EMMC_CLK,<O>,<HS>
																							//02: ST_dbg_bit4,<I/O>
																							//03: PCMCIA_INPACK1_N_SRC0,<I>
																							//04: TCON_bit19,<O>
																							//05: CR_SD_CD_SRC0,<I>,<HS>
																							//06: CR_SD_WP_SRC2,<I>,<HS>
																							//08: IRTX,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//0F: I2C0_SCL_SRC4,<I/O>
																							//11: VFD_CS_N,<OD>
																							//12: SC1_DATA0_SRC10,<I/O>
																							//13: I2S_out_MCLK,<O>
																							//15: GSPI_DO_SRC1,<I/O>,<HS>
																							//17: test_en_bit23,<I/O>
																							//1F: ISO_MIS_GPIO_bit12,<I/O>
																							//def: ISO_MIS_GPIO_bit12,<I/O>
#define RTD298X_BGA459_PIN_E10_UP							(1&0x01)// 0xB8060248[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E10_PD							(0&0x01)// 0xB8060248[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E10_DS							(0&0x01)// 0xB8060248[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E10_SR							(0&0x01)// 0xB8060248[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_13_io 69
#define RTD298X_BGA459_PIN_B10								(0x1F&0x1F)//0xB8060244[13:9];
																							//02: ST_dbg_bit30,<I/O>
																							//03: PCMCIA_RST1,<OD>
																							//08: IRTX,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//0F: I2C0_SDA_SRC4,<I/O>
																							//13: I2S_out_Data0,<O>
																							//1F: ISO_MIS_GPIO_bit13,<I/O>
																							//def: ISO_MIS_GPIO_bit13,<I/O>
#define RTD298X_BGA459_PIN_B10_UP							(0&0x01)// 0xB8060244[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B10_PD							(1&0x01)// 0xB8060244[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B10_DS							(0&0x01)// 0xB8060244[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B10_SR							(0&0x01)// 0xB8060244[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_14_io 70
#define RTD298X_BGA459_PIN_C4								(0x09&0x1F)//0xB8060204[31:27];
																							//02: ST_dbg_bit5,<I/O>
																							//04: VDDC_SDA,<I/O>
																							//05: HDDC0_SDA_SRC1,<I/O>
																							//09: uart0_tXdo,<O>
																							//0A: emcu_ur_tX,<O>
																							//0B: SPDIF_OUT,<O>
																							//0F: I2C0_SDA_SRC2,<I/O>
																							//17: test_en_bit28,<I/O>
																							//1F: ISO_MIS_GPIO_bit14,<I/O>
																							//def: ISO_MIS_GPIO_bit14,<I/O>
#define RTD298X_BGA459_PIN_C4_UP							(1&0x01)// 0xB8060204[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C4_PD							(0&0x01)// 0xB8060204[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C4_DS							(0&0x01)// 0xB8060204[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C4_SR							(0&0x01)// 0xB8060204[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_15_io 71
#define RTD298X_BGA459_PIN_C5								(0x09&0x1F)//0xB8060200[13:9];
																							//02: ST_dbg_bit6,<I/O>
																							//04: VDDC_SCL,<I>
																							//05: HDDC0_SCL_SRC1,<I>
																							//09: uart0_rXdi_src0,<I>
																							//0A: emcu_ur_rX,<I>
																							//0F: I2C0_SCL_SRC2,<I/O>
																							//11: VFD_CS_N,<OD>
																							//17: test_en_bit29,<I/O>
																							//1F: ISO_MIS_GPIO_bit15,<I/O>
																							//def: ISO_MIS_GPIO_bit15,<I/O>
#define RTD298X_BGA459_PIN_C5_UP							(1&0x01)// 0xB8060200[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C5_PD							(0&0x01)// 0xB8060200[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C5_DS							(0&0x01)// 0xB8060200[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C5_SR							(0&0x01)// 0xB8060200[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_16_io 72
#define RTD298X_BGA459_PIN_D4								(0x1F&0x1F)//0xB8060244[22:18];
																							//02: ST_dbg_bit14,<I/O>
																							//06: CR_SD_CMD_SRC0,<I/O>,<HS>
																							//07: SC0_RST,<OD>
																							//08: SC1_RST,<OD>
																							//09: irrX_src1,<I>
																							//1F: ISO_MIS_GPIO_bit16,<I/O>
																							//def: ISO_MIS_GPIO_bit16,<I/O>
#define RTD298X_BGA459_PIN_D4_UP							(1&0x01)// 0xB8060244[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D4_PD							(0&0x01)// 0xB8060244[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D4_DS							(0&0x01)// 0xB8060244[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D4_SR							(0&0x01)// 0xB8060244[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_17_io 73
#define RTD298X_BGA459_PIN_D5								(0x04&0x1F)//0xB8060204[22:18];
																							//02: ST_dbg_bit7,<I/O>
																							//04: HDDC2_SCL,<I>
																							//06: CR_SD_CLK,<O>,<HS>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_LINK,<O>
																							//17: test_en_bit21,<I/O>
																							//1F: ISO_MIS_GPIO_bit17,<I/O>
																							//def: ISO_MIS_GPIO_bit17,<I/O>
#define RTD298X_BGA459_PIN_D5_UP							(1&0x01)// 0xB8060204[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D5_PD							(0&0x01)// 0xB8060204[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D5_DS							(0&0x01)// 0xB8060204[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D5_SR							(0&0x01)// 0xB8060204[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_18_io 74
#define RTD298X_BGA459_PIN_E5								(0x04&0x1F)//0xB8060204[13:9];
																							//02: ST_dbg_bit31,<I/O>
																							//04: HDDC2_SDA,<I/O>
																							//08: irrX_src4,<I>
																							//09: ETN_LED_TXRX,<O>
																							//1F: ISO_MIS_GPIO_bit18,<I/O>
																							//def: ISO_MIS_GPIO_bit18,<I/O>
#define RTD298X_BGA459_PIN_E5_UP							(1&0x01)// 0xB8060204[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E5_PD							(0&0x01)// 0xB8060204[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E5_DS							(0&0x01)// 0xB8060204[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E5_SR							(0&0x01)// 0xB8060204[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_19_io 75
#define RTD298X_BGA459_PIN_E4								(0x1F&0x1F)//0xB8060244[31:27];
																							//02: ST_dbg_bit8,<I/O>
																							//06: CR_SD_WP_SRC7,<I>,<HS>
																							//07: SC0_CD_SRC0,<I>
																							//08: SC1_CD_SRC5,<I>
																							//17: test_en_bit22,<I/O>
																							//1F: ISO_MIS_GPIO_bit19,<I/O>
																							//def: ISO_MIS_GPIO_bit19,<I/O>
#define RTD298X_BGA459_PIN_E4_UP							(1&0x01)// 0xB8060244[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E4_PD							(0&0x01)// 0xB8060244[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E4_DS							(0&0x01)// 0xB8060244[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E4_SR							(0&0x01)// 0xB8060244[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_20_io 76
#define RTD298X_BGA459_PIN_F5								(0x04&0x1F)//0xB8060208[31:27];
																							//02: ST_dbg_bit9,<I/O>
																							//04: HDDC1_SCL,<I>
																							//06: CR_SD_CD_SRC1,<I>,<HS>
																							//0A: SPDIF_OUT,<O>
																							//17: test_en_bit24,<I/O>
																							//1F: ISO_MIS_GPIO_bit20,<I/O>
																							//def: ISO_MIS_GPIO_bit20,<I/O>
#define RTD298X_BGA459_PIN_F5_UP							(1&0x01)// 0xB8060208[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F5_PD							(0&0x01)// 0xB8060208[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F5_DS							(0&0x01)// 0xB8060208[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F5_SR							(0&0x01)// 0xB8060208[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_21_io 77
#define RTD298X_BGA459_PIN_F4								(0x04&0x1F)//0xB8060208[22:18];
																							//02: ST_dbg_bit10,<I/O>
																							//04: HDDC1_SDA,<I/O>
																							//06: CR_SD_Data_bit0_SRC1,<I/O>,<HS>
																							//07: SC0_DATA0_SRC0,<I/O>
																							//08: SC1_DATA0_SRC6,<I/O>
																							//17: test_en_bit25,<I/O>
																							//1F: ISO_MIS_GPIO_bit21,<I/O>
																							//def: ISO_MIS_GPIO_bit21,<I/O>
#define RTD298X_BGA459_PIN_F4_UP							(1&0x01)// 0xB8060208[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F4_PD							(0&0x01)// 0xB8060208[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F4_DS							(0&0x01)// 0xB8060208[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F4_SR							(0&0x01)// 0xB8060208[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_22_io 78
#define RTD298X_BGA459_PIN_G4								(0x1F&0x1F)//0xB8060240[13:9];
																							//02: ST_dbg_bit13,<I/O>
																							//06: CR_SD_Data_bit1_SRC1,<I/O>,<HS>
																							//08: SC1_SCLK,<OD>
																							//09: uart0_rts_n,<O>
																							//0A: uart1_rts_n,<O>
																							//1F: ISO_MIS_GPIO_bit22,<I/O>
																							//def: ISO_MIS_GPIO_bit22,<I/O>
#define RTD298X_BGA459_PIN_G4_UP							(1&0x01)// 0xB8060240[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G4_PD							(0&0x01)// 0xB8060240[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G4_DS							(0&0x01)// 0xB8060240[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G4_SR							(0&0x01)// 0xB8060240[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_23_io 79
#define RTD298X_BGA459_PIN_G5								(0x04&0x1F)//0xB8060200[31:27];
																							//02: ST_dbg_bit11,<I/O>
																							//03: DEMOD_I2C_DBG_SCL,<I>
																							//04: HDDC0_SCL_SRC0,<I>
																							//06: CR_SD_Data_bit2_SRC1,<I/O>,<HS>
																							//09: uart0_cts_n_src1,<I>
																							//0A: uart1_cts_n_src1,<I>
																							//0F: I2C0_SCL_SRC0,<I/O>
																							//11: VFD_CS_N,<OD>
																							//14: SC1_RST,<OD>
																							//17: test_en_bit26,<I/O>
																							//1F: ISO_MIS_GPIO_bit23,<I/O>
																							//def: ISO_MIS_GPIO_bit23,<I/O>
#define RTD298X_BGA459_PIN_G5_UP							(1&0x01)// 0xB8060200[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G5_PD							(0&0x01)// 0xB8060200[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G5_DS							(0&0x01)// 0xB8060200[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G5_SR							(0&0x01)// 0xB8060200[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_24_io 80
#define RTD298X_BGA459_PIN_H5								(0x04&0x1F)//0xB8060200[22:18];
																							//02: ST_dbg_bit12,<I/O>
																							//03: DEMOD_I2C_DBG_SDA,<I/O>
																							//04: HDDC0_SDA_SRC0,<I/O>
																							//06: CR_SD_Data_bit3_SRC1,<I/O>,<HS>
																							//07: SC0_PWR_SEL,<OD>
																							//08: SC1_PWR_SEL,<OD>
																							//0F: I2C0_SDA_SRC0,<I/O>
																							//14: SC1_CD_SRC10,<I>
																							//17: test_en_bit27,<I/O>
																							//1F: ISO_MIS_GPIO_bit24,<I/O>
																							//def: ISO_MIS_GPIO_bit24,<I/O>
#define RTD298X_BGA459_PIN_H5_UP							(1&0x01)// 0xB8060200[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_H5_PD							(0&0x01)// 0xB8060200[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_H5_DS							(0&0x01)// 0xB8060200[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_H5_SR							(0&0x01)// 0xB8060200[14]: Slew rate 0:fast 1:slow


// PAD_NAME: LSADC_REF_APAD 81
#define RTD298X_BGA459_PIN_D7								(0x1F&0x1F)//0xB806020C[31:27];
																							//0C: LSADC_REF,<AI>
																							//1F: ISO_MIS_GPIO_bit0,<I/O>
																							//def: ISO_MIS_GPIO_bit0,<I/O>


// PAD_NAME: LSADC0_APAD 82
#define RTD298X_BGA459_PIN_B7								(0x0C&0x1F)//0xB8060210[31:27];
																							//0C: LSADC0,<AI>
																							//1F: ISO_MIS_GPIO_bit1,<I/O>
																							//def: ISO_MIS_GPIO_bit1,<I/O>


// PAD_NAME: LSADC1_APAD 83
#define RTD298X_BGA459_PIN_C6								(0x0C&0x1F)//0xB806020C[6:2];
																							//0C: LSADC1,<AI>
																							//1F: ISO_MIS_GPIO_bit2,<I/O>
																							//def: ISO_MIS_GPIO_bit2,<I/O>


// PAD_NAME: LSADC2_APAD 84
#define RTD298X_BGA459_PIN_A7								(0x1F&0x1F)//0xB806020C[11:7];
																							//0C: LSADC2,<AI>
																							//1F: ISO_MIS_GPIO_bit3,<I/O>
																							//def: ISO_MIS_GPIO_bit3,<I/O>


// PAD_NAME: LSADC7_APAD 85
#define RTD298X_BGA459_PIN_C7								(0x1F&0x1F)//0xB806020C[26:22];
																							//0C: LSADC7,<AI>
																							//1F: ISO_MIS_GPIO_bit6,<I/O>
																							//def: ISO_MIS_GPIO_bit6,<I/O>


// PAD_NAME: VSYNC_APAD 86
#define RTD298X_BGA459_PIN_M1								(0x0C&0x1F)//0xB80008D8[31:27];
																							//0C: VSYNC,<AI>
																							//1F: MIS_GPIO_bit111,<I/O>
																							//def: VSYNC,<AI>
#define RTD298X_BGA459_PIN_M1_UP							(1&0x01)// 0xB80008D8[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M1_PD							(0&0x01)// 0xB80008D8[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M1_DS							(0&0x01)// 0xB80008D8[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M1_SR							(0&0x01)// 0xB80008D8[23]: Slew rate 0:fast 1:slow


// PAD_NAME: HSYNC_APAD 87
#define RTD298X_BGA459_PIN_M2								(0x0C&0x1F)//0xB80008D8[26:22];
																							//0C: HSYNC,<AI>
																							//1F: MIS_GPIO_bit112,<I/O>
																							//def: HSYNC,<AI>
#define RTD298X_BGA459_PIN_M2_UP							(1&0x01)// 0xB80008D8[21]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M2_PD							(0&0x01)// 0xB80008D8[20]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M2_DS							(0&0x01)// 0xB80008D8[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M2_SR							(0&0x01)// 0xB80008D8[18]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_0P_APAD 88
#define RTD298X_BGA459_PIN_M3								(0x0C&0x1F)//0xB80008DC[31:27];
																							//03: TCON_bit0,<O>
																							//0C: VIN_0P,<AI>
																							//1F: MIS_GPIO_bit113,<I/O>
																							//def: VIN_0P,<AI>
#define RTD298X_BGA459_PIN_M3_UP							(1&0x01)// 0xB80008DC[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M3_PD							(0&0x01)// 0xB80008DC[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M3_DS							(0&0x01)// 0xB80008DC[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M3_SR							(0&0x01)// 0xB80008DC[23]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_BN_APAD 89
#define RTD298X_BGA459_PIN_N2								(0x0C&0x1F)//0xB80008DC[26:22];
																							//03: TCON_bit1,<O>
																							//0C: VIN_BN,<AI>
																							//1F: MIS_GPIO_bit114,<I/O>
																							//def: VIN_BN,<AI>
#define RTD298X_BGA459_PIN_N2_UP							(1&0x01)// 0xB80008DC[21]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_N2_PD							(0&0x01)// 0xB80008DC[20]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_N2_DS							(0&0x01)// 0xB80008DC[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_N2_SR							(0&0x01)// 0xB80008DC[18]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_1P_APAD 90
#define RTD298X_BGA459_PIN_N3								(0x0C&0x1F)//0xB80008DC[21:17];
																							//03: TCON_bit2,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: VIN_1P,<AI>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_3,<OD>
																							//1F: MIS_GPIO_bit115,<I/O>
																							//def: VIN_1P,<AI>
#define RTD298X_BGA459_PIN_N3_UP							(1&0x01)// 0xB80008DC[16]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_N3_PD							(0&0x01)// 0xB80008DC[15]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_N3_DS							(0&0x01)// 0xB80008DC[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_N3_SR							(0&0x01)// 0xB80008DC[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_2P_APAD 91
#define RTD298X_BGA459_PIN_P2								(0x0C&0x1F)//0xB80008DC[16:12];
																							//03: TCON_bit3,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: VIN_2P,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//1F: MIS_GPIO_bit116,<I/O>
																							//def: VIN_2P,<AI>
#define RTD298X_BGA459_PIN_P2_UP							(1&0x01)// 0xB80008DC[11]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_P2_PD							(0&0x01)// 0xB80008DC[10]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_P2_DS							(0&0x01)// 0xB80008DC[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_P2_SR							(0&0x01)// 0xB80008DC[8]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_13P_APAD 92
#define RTD298X_BGA459_PIN_U1								(0x1F&0x1F)//0xB80008E8[31:27];
																							//03: TCON_bit13,<O>
																							//0C: VIN_13P,<AI>
																							//1F: MIS_GPIO_bit126,<I/O>
																							//def: VIN_13P,<AI>
#define RTD298X_BGA459_PIN_U1_UP							(1&0x01)// 0xB80008E8[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_U1_PD							(0&0x01)// 0xB80008E8[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_U1_DS							(0&0x01)// 0xB80008E8[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_U1_SR							(0&0x01)// 0xB80008E8[23]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_A0N_APAD 93
#define RTD298X_BGA459_PIN_V2								(0x0C&0x1F)//0xB80008E4[21:17];
																							//03: TCON_bit10,<O>
																							//0C: VIN_A0N,<AI>
																							//1F: MIS_GPIO_bit123,<I/O>
																							//def: VIN_A0N,<AI>
#define RTD298X_BGA459_PIN_V2_UP							(1&0x01)// 0xB80008E4[16]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_V2_PD							(0&0x01)// 0xB80008E4[15]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_V2_DS							(0&0x01)// 0xB80008E4[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_V2_SR							(0&0x01)// 0xB80008E4[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_12P_APAD 94
#define RTD298X_BGA459_PIN_V3								(0x0C&0x1F)//0xB80008E4[26:22];
																							//03: TCON_bit9,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: VIN_12P,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//0F: I2C0_SCL_SRC12,<I/O>
																							//1F: MIS_GPIO_bit122,<I/O>
																							//def: VIN_12P,<AI>
#define RTD298X_BGA459_PIN_V3_UP							(1&0x01)// 0xB80008E4[21]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_V3_PD							(0&0x01)// 0xB80008E4[20]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_V3_DS							(0&0x01)// 0xB80008E4[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_V3_SR							(0&0x01)// 0xB80008E4[18]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI4L_APAD 95
#define RTD298X_BGA459_PIN_AB2								(0x1F&0xC)//0xB80008F0[11:7];
																							//03: TCON_bit17,<O>
																							//0C: BB_AI4L,<AI>
																							//1F: MIS_GPIO_bit134,<I/O>
																							//def: BB_AI4L,<AI>
#define RTD298X_BGA459_PIN_AB2_UP							(1&0x01)// 0xB80008F0[6]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB2_PD							(0&0x01)// 0xB80008F0[5]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB2_DS							(0&0x01)// 0xB80008F0[4]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB2_SR							(0&0x01)// 0xB80008F0[3]: Slew rate 0:fast 1:slow


// PAD_NAME: BB_AI4R_APAD 96
#define RTD298X_BGA459_PIN_AB3								(0x1F&0xC)//0xB80008F4[31:27];
																							//03: TCON_bit18,<O>
																							//0C: BB_AI4R,<AI>
																							//1F: MIS_GPIO_bit135,<I/O>
																							//def: BB_AI4R,<AI>
#define RTD298X_BGA459_PIN_AB3_UP							(1&0x01)// 0xB80008F4[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB3_PD							(0&0x01)// 0xB80008F4[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB3_DS							(0&0x01)// 0xB80008F4[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB3_SR							(0&0x01)// 0xB80008F4[23]: Slew rate 0:fast 1:slow


// PAD_NAME: HSDM_2_APAD 97
#define RTD298X_BGA459_PIN_AD8								(0x1F&0x1F)//0xB80008F8[11:7];
																							//03: TCON_bit13,<O>
																							//04: TCON_bit24,<O>
																							//08: uart0_tXdo,<O>
																							//0B: I2S_out_Data0,<O>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//0F: I2C0_SDA_SRC14,<I/O>
																							//10: P_CRS_SRC3,<I>,<HS>
																							//11: I2C2_SDA_SRC14,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//14: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit110,<I/O>
																							//def: MIS_GPIO_bit110,<I/O>
#define RTD298X_BGA459_PIN_AD8_UP							(1&0x01)// 0xB80008F8[6]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD8_PD							(0&0x01)// 0xB80008F8[5]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD8_DS							(0&0x01)// 0xB80008F8[4]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD8_SR							(0&0x01)// 0xB80008F8[3]: Slew rate 0:fast 1:slow


// PAD_NAME: HSDP_2_APAD 98
#define RTD298X_BGA459_PIN_AC8								(0x1F&0x1F)//0xB80008F8[16:12];
																							//03: TCON_bit12,<O>
																							//04: TCON_bit23,<O>
																							//08: uart0_rXdi_src4,<I>
																							//0B: I2S_out_Data0,<O>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_4,<OD>
																							//0F: I2C0_SCL_SRC14,<I/O>
																							//10: P_COL_SRC3,<I>,<HS>
																							//11: I2C2_SCL_SRC14,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_WCLK,<O>
																							//14: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit109,<I/O>
																							//def: MIS_GPIO_bit109,<I/O>
#define RTD298X_BGA459_PIN_AC8_UP							(1&0x01)// 0xB80008F8[11]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC8_PD							(0&0x01)// 0xB80008F8[10]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC8_DS							(0&0x01)// 0xB80008F8[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC8_SR							(0&0x01)// 0xB80008F8[8]: Slew rate 0:fast 1:slow


// PAD_NAME: LSADC4_APAD 99
#define RTD298X_BGA459_PIN_A5								(0x1F&0x1F)//0xB806020C[16:12];
																							//0C: LSADC4,<AI>
																							//1F: ISO_MIS_GPIO_bit4,<I/O>
																							//def: ISO_MIS_GPIO_bit4,<I/O>


// PAD_NAME: LSADC6_APAD 100
#define RTD298X_BGA459_PIN_B6								(0x1F&0x1F)//0xB806020C[21:17];
																							//0C: LSADC6,<AI>
																							//1F: ISO_MIS_GPIO_bit5,<I/O>
																							//def: ISO_MIS_GPIO_bit5,<I/O>


// PAD_NAME: pad_gpio_3_io 101
#define RTD298X_BGA459_PIN_M5								(0x1F&0x1F)//0xB8000894[31:27];
																							//03: TCON_bit10,<O>
																							//07: SC0_DATA0_SRC1,<I/O>
																							//08: SC1_DATA0_SRC5,<I/O>
																							//10: P_TXC_SRC0,<I>,<HS>
																							//1F: MIS_GPIO_bit3,<I/O>
																							//def: MIS_GPIO_bit3,<I/O>
#define RTD298X_BGA459_PIN_M5_UP							(1&0x01)// 0xB8000894[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M5_PD							(0&0x01)// 0xB8000894[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M5_DS							(0&0x01)// 0xB8000894[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M5_SR							(0&0x01)// 0xB8000894[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_4_io 102
#define RTD298X_BGA459_PIN_M6								(0x1F&0x1F)//0xB8000894[22:18];
																							//03: TCON_bit19,<O>
																							//07: SC0_PWR_SEL,<OD>
																							//08: SC1_PWR_SEL,<OD>
																							//09: uart1_rXdi_src7,<I>
																							//0A: SPDIF_OUT,<O>
																							//10: P_TXD0,<O>,<HS>
																							//1F: MIS_GPIO_bit4,<I/O>
																							//def: MIS_GPIO_bit4,<I/O>
#define RTD298X_BGA459_PIN_M6_UP							(1&0x01)// 0xB8000894[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M6_PD							(0&0x01)// 0xB8000894[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M6_DS							(0&0x01)// 0xB8000894[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M6_SR							(0&0x01)// 0xB8000894[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_5_io 103
#define RTD298X_BGA459_PIN_AA9								(0x16&0x1F)//0xB8000808[31:27];
																							//00: TP1_Data_bit5,<I>,<HS>
																							//02: TTL_denout,<O>,<HS>
																							//03: TCON_bit20,<O>
																							//05: ld_spi1_p3_sdo_SRC2,<I/O>
																							//06: CR_SD_Data_bit0_SRC3,<I/O>,<HS>
																							//07: SC0_PWR_SEL,<OD>
																							//08: SC1_PWR_SEL,<OD>
																							//09: DEMOD_ANT_TX_SRC0,<I/O>
																							//0A: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_3,<OD>
																							//0F: TCON_bit2,<O>
																							//11: I2C0_SCL_SRC13,<I/O>
																							//13: I2S_out_Data1,<O>
																							//14: I2S_in_WCLK,<I>
																							//15: TP2_Data_bit0_SRC0,<I>,<HS>
																							//16: PCMCIA_CD0_N_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit5,<I/O>
																							//def: MIS_GPIO_bit5,<I/O>
#define RTD298X_BGA459_PIN_AA9_UP							(1&0x01)// 0xB8000808[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA9_PD							(0&0x01)// 0xB8000808[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA9_DS							(0&0x01)// 0xB8000808[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA9_SR							(0&0x01)// 0xB8000808[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_6_io 104
#define RTD298X_BGA459_PIN_AE10								(0x16&0x1F)//0xB8000808[22:18];
																							//00: TP1_Data_bit4,<I>,<HS>
																							//02: TTL_vsout,<O>,<HS>
																							//03: TCON_bit21,<O>
																							//04: ld_spi0_p3_sdo_SRC2,<I/O>
																							//05: ld_spi1_p4_sdi_SRC2,<I>
																							//06: CR_SD_Data_bit1_SRC3,<I/O>,<HS>
																							//09: DEMOD_ANT_OE_SRC0,<I/O>
																							//0A: ETN_LED_TXRX,<O>
																							//0B: SPDIF_OUT,<O>
																							//0D: misc_pwm_5,<OD>
																							//0F: TCON_bit3,<O>
																							//11: I2C0_SDA_SRC13,<I/O>
																							//13: I2S_out_SCLK,<O>
																							//14: I2S_in_SCLK,<I>
																							//15: TP2_CLK_SRC0,<I>,<HS>
																							//16: PCMCIA_D_bit5_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit6,<I/O>
																							//def: MIS_GPIO_bit6,<I/O>
#define RTD298X_BGA459_PIN_AE10_UP							(1&0x01)// 0xB8000808[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE10_PD							(0&0x01)// 0xB8000808[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE10_DS							(0&0x01)// 0xB8000808[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE10_SR							(0&0x01)// 0xB8000808[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_7_io 105
#define RTD298X_BGA459_PIN_AC9								(0x16&0x1F)//0xB8000808[13:9];
																							//00: TP1_Data_bit3,<I>,<HS>
																							//02: TTL_hsout,<O>,<HS>
																							//03: TCON_bit22,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//06: CR_SD_Data_bit2_SRC4,<I/O>,<HS>
																							//08: ETN_LED_LINK,<O>
																							//09: DEMOD_ANT_RX_SRC0,<I>
																							//0B: SPDIF_OUT,<O>
																							//0F: TCON_bit4,<O>
																							//11: I2C2_SCL_SRC13,<I/O>
																							//13: I2S_out_WCLK,<O>
																							//14: I2S_in_Data0,<I>
																							//15: TP2_SYNC_SRC0,<I>,<HS>
																							//16: PCMCIA_D_bit4_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit7,<I/O>
																							//def: MIS_GPIO_bit7,<I/O>
#define RTD298X_BGA459_PIN_AC9_UP							(1&0x01)// 0xB8000808[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC9_PD							(0&0x01)// 0xB8000808[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC9_DS							(0&0x01)// 0xB8000808[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC9_SR							(0&0x01)// 0xB8000808[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_8_io 106
#define RTD298X_BGA459_PIN_Y10								(0x16&0x1F)//0xB800080C[31:27];
																							//00: TP1_Data_bit2,<I>,<HS>
																							//01: EMMC_CLK,<O>,<HS>
																							//02: TTL_CLK,<O>,<HS>
																							//03: TCON_bit23,<O>
																							//04: ld_spi0_p2_sck_src2,<I/O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//06: CR_SD_Data_bit3_SRC4,<I/O>,<HS>
																							//08: ETN_LED_TXRX,<O>
																							//0A: USB_PWR_FLAG0_SRC1,<I>
																							//0B: USB_PWR_CTRL1,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_3,<OD>
																							//0F: TCON_bit5,<O>
																							//10: I2S_out_MCLK,<O>
																							//11: I2C2_SDA_SRC13,<I/O>
																							//14: I2S_in_MCLK,<I>
																							//15: TP2_VAL_SRC0,<I>,<HS>
																							//16: TP0_Data_bit6_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit8,<I/O>
																							//def: MIS_GPIO_bit8,<I/O>
#define RTD298X_BGA459_PIN_Y10_UP							(1&0x01)// 0xB800080C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y10_PD							(0&0x01)// 0xB800080C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y10_DS							(0&0x01)// 0xB800080C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y10_SR							(0&0x01)// 0xB800080C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_9_io 107
#define RTD298X_BGA459_PIN_AC10								(0x16&0x1F)//0xB800080C[22:18];
																							//00: TP1_Data_bit1,<I>,<HS>
																							//01: EMMC_CMD_SRC4,<I/O>,<HS>
																							//03: TCON_bit7,<O>
																							//08: IRTX,<O>
																							//09: SPDIF_OUT,<O>
																							//0A: USB_PWR_CTRL0,<O>
																							//0B: USB_PWR_FLAG1_SRC1,<I>
																							//0F: I2S_out_Data0,<O>
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//15: TP2_ERR_SRC0,<I>,<HS>
																							//16: PCMCIA_ADDR_bit10,<OD>,<HS>
																							//1F: MIS_GPIO_bit9,<I/O>
																							//def: MIS_GPIO_bit9,<I/O>
#define RTD298X_BGA459_PIN_AC10_UP							(1&0x01)// 0xB800080C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC10_PD							(0&0x01)// 0xB800080C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC10_DS							(0&0x01)// 0xB800080C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC10_SR							(0&0x01)// 0xB800080C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_10_io 108
#define RTD298X_BGA459_PIN_AB12								(0x16&0x1F)//0xB800080C[13:9];
																							//00: TP1_Data_bit0_SRC0,<I>,<HS>
																							//03: TCON_bit8,<O>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//0F: I2S_out_MCLK,<O>
																							//10: P_RXER_SRC3,<I>,<HS>
																							//11: P_RXD2_SRC2,<I>,<HS>
																							//16: TP0_Data_bit7_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit10,<I/O>
																							//def: MIS_GPIO_bit10,<I/O>
#define RTD298X_BGA459_PIN_AB12_UP							(1&0x01)// 0xB800080C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB12_PD							(0&0x01)// 0xB800080C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB12_DS							(0&0x01)// 0xB800080C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB12_SR							(0&0x01)// 0xB800080C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_11_io 109
#define RTD298X_BGA459_PIN_AD11								(0x16&0x1F)//0xB8000810[31:27];
																							//00: TP1_CLK_SRC0,<I>,<HS>
																							//03: TCON_bit9,<O>
																							//07: SC0_DATA0_SRC5,<I/O>
																							//08: SC1_DATA0_SRC7,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1,<OD>
																							//10: P_RXDV_SRC3,<I>,<HS>
																							//11: P_RXD3_SRC2,<I>,<HS>
																							//13: I2S_out_MCLK,<O>
																							//16: PCMCIA_D_bit7_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit11,<I/O>
																							//def: MIS_GPIO_bit11,<I/O>
#define RTD298X_BGA459_PIN_AD11_UP							(1&0x01)// 0xB8000810[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD11_PD							(0&0x01)// 0xB8000810[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD11_DS							(0&0x01)// 0xB8000810[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD11_SR							(0&0x01)// 0xB8000810[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_12_io 110
#define RTD298X_BGA459_PIN_Y11								(0x16&0x1F)//0xB8000810[22:18];
																							//00: TP1_SYNC_SRC0,<I>,<HS>
																							//03: TCON_bit10,<O>
																							//07: SC0_RST,<OD>
																							//08: SC1_RST,<OD>
																							//0A: SPDIF_OUT,<O>
																							//10: P_RXD0_SRC3,<I>,<HS>
																							//13: I2S_out_SCLK,<O>
																							//15: VBY1_HTPD_src2,<I>
																							//16: TPO_SYNC_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit12,<I/O>
																							//def: MIS_GPIO_bit12,<I/O>
#define RTD298X_BGA459_PIN_Y11_UP							(1&0x01)// 0xB8000810[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y11_PD							(0&0x01)// 0xB8000810[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y11_DS							(0&0x01)// 0xB8000810[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y11_SR							(0&0x01)// 0xB8000810[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_13_io 111
#define RTD298X_BGA459_PIN_Y12								(0x16&0x1F)//0xB8000810[13:9];
																							//00: TP1_VAL_SRC0,<I>,<HS>
																							//03: TCON_bit6,<O>
																							//07: SC0_CD_SRC5,<I>
																							//08: SC1_CD_SRC8,<I>
																							//10: P_RXD1_SRC3,<I>,<HS>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_Data0,<O>
																							//15: VBY1_LOCK_src2,<I>
																							//16: PCMCIA_IORD_N,<O>,<HS>
																							//1F: MIS_GPIO_bit13,<I/O>
																							//def: MIS_GPIO_bit13,<I/O>
#define RTD298X_BGA459_PIN_Y12_UP							(1&0x01)// 0xB8000810[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y12_PD							(0&0x01)// 0xB8000810[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y12_DS							(0&0x01)// 0xB8000810[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y12_SR							(0&0x01)// 0xB8000810[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_14_io 112
#define RTD298X_BGA459_PIN_AD12								(0x16&0x1F)//0xB8000814[31:27];
																							//01: TP0_Data_bit2_SRC0,<I>,<HS>
																							//02: EMMC_CLK,<O>,<HS>
																							//09: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm0,<O>
																							//0D: misc_pwm_0,<OD>
																							//12: I2S_out_Data0,<O>
																							//13: I2S_out_MCLK,<O>
																							//16: PCMCIA_ADDR_bit11,<OD>,<HS>
																							//1F: MIS_GPIO_bit14,<I/O>
																							//def: MIS_GPIO_bit14,<I/O>
#define RTD298X_BGA459_PIN_AD12_UP							(1&0x01)// 0xB8000814[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD12_PD							(0&0x01)// 0xB8000814[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD12_DS							(0&0x01)// 0xB8000814[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD12_SR							(0&0x01)// 0xB8000814[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_15_io 113
#define RTD298X_BGA459_PIN_AA12								(0x16&0x1F)//0xB8000814[22:18];
																							//01: TP0_Data_bit1_SRC0,<I>,<HS>
																							//02: EMMC_CMD_SRC5,<I/O>,<HS>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1,<OD>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_SCLK,<O>
																							//14: I2S_out_WCLK,<O>
																							//16: TPO_Data_bit0_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit15,<I/O>
																							//def: MIS_GPIO_bit15,<I/O>
#define RTD298X_BGA459_PIN_AA12_UP							(1&0x01)// 0xB8000814[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA12_PD							(0&0x01)// 0xB8000814[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA12_DS							(0&0x01)// 0xB8000814[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA12_SR							(0&0x01)// 0xB8000814[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_20_io 114
#define RTD298X_BGA459_PIN_AA13								(0x01&0x1F)//0xB800081C[31:27];
																							//00: TP2_ERR_SRC1,<I>,<HS>
																							//01: TPO_data_bit7_pad,<O>,<HS>
																							//02: EMMC_Data_bit3_SRC1,<I/O>,<HS>
																							//03: TCON_bit2,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//09: uart2_rXdi_src5,<I>
																							//0B: I2S_out_Data1,<O>
																							//0D: misc_pwm_4,<OD>
																							//10: I2S_out_SCLK,<O>
																							//11: I2C0_SCL_SRC16,<I/O>
																							//1F: MIS_GPIO_bit20,<I/O>
																							//def: MIS_GPIO_bit20,<I/O>
#define RTD298X_BGA459_PIN_AA13_UP							(1&0x01)// 0xB800081C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA13_PD							(0&0x01)// 0xB800081C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA13_DS							(0&0x01)// 0xB800081C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA13_SR							(0&0x01)// 0xB800081C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_21_io 115
#define RTD298X_BGA459_PIN_AA15								(0x01&0x1F)//0xB800081C[22:18];
																							//00: nf_tmX_ce_n_bit1,<O>,<HS>
																							//01: TPO_Data_bit6_pad,<O>,<HS>
																							//02: EMMC_Data_bit1_SRC1,<I/O>,<HS>
																							//03: TCON_bit3,<O>
																							//05: ld_spi1_p2_sck_src4,<I/O>
																							//09: uart1_rXdi_src6,<I>
																							//0D: misc_pwm_3,<OD>
																							//10: I2S_out_WCLK,<O>
																							//11: I2C2_SCL_SRC15,<I/O>
																							//1F: MIS_GPIO_bit21,<I/O>
																							//def: MIS_GPIO_bit21,<I/O>
#define RTD298X_BGA459_PIN_AA15_UP							(1&0x01)// 0xB800081C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA15_PD							(0&0x01)// 0xB800081C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA15_DS							(0&0x01)// 0xB800081C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA15_SR							(0&0x01)// 0xB800081C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_22_io 116
#define RTD298X_BGA459_PIN_Y15								(0x01&0x1F)//0xB800081C[13:9];
																							//01: TPO_CLK_pad,<O>,<HS>
																							//02: EMMC_Data_bit2_SRC1,<I/O>,<HS>
																							//03: TCON_bit4,<O>
																							//05: ld_spi1_p3_sdo_SRC4,<I/O>
																							//09: uart2_tXdo,<O>
																							//0B: SPDIF_IN_src0,<I>
																							//10: I2S_out_MCLK,<O>
																							//11: I2C0_SDA_SRC16,<I/O>
																							//1F: MIS_GPIO_bit22,<I/O>
																							//def: MIS_GPIO_bit22,<I/O>
#define RTD298X_BGA459_PIN_Y15_UP							(1&0x01)// 0xB800081C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y15_PD							(0&0x01)// 0xB800081C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y15_DS							(0&0x01)// 0xB800081C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y15_SR							(0&0x01)// 0xB800081C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_23_io 117
#define RTD298X_BGA459_PIN_AB15								(0x01&0x1F)//0xB8000820[31:27];
																							//01: TPO_Data_bit5_pad,<O>,<HS>
																							//02: EMMC_Data_bit0_SRC1,<I/O>,<HS>
																							//03: TCON_bit5,<O>
																							//04: ld_spi0_p3_sdo_SRC4,<I/O>
																							//05: ld_spi1_p4_sdi_SRC4,<I>
																							//08: SC1_PWR_SEL,<OD>
																							//09: uart1_tXdo,<O>
																							//10: I2S_out_Data0,<O>
																							//11: I2C2_SDA_SRC15,<I/O>
																							//1F: MIS_GPIO_bit23,<I/O>
																							//def: MIS_GPIO_bit23,<I/O>
#define RTD298X_BGA459_PIN_AB15_UP							(1&0x01)// 0xB8000820[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB15_PD							(0&0x01)// 0xB8000820[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB15_DS							(0&0x01)// 0xB8000820[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB15_SR							(0&0x01)// 0xB8000820[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_24_io 118
#define RTD298X_BGA459_PIN_G24								(0x16&0x1F)//0xB8000850[31:27];
																							//01: PCMCIA_ADDR_bit10,<OD>,<HS>
																							//03: TCON_bit11,<O>
																							//07: SC0_DATA0_SRC2,<I/O>
																							//08: uart1_tXdo,<O>
																							//13: I2S_out_Data0,<O>
																							//16: PCMCIA_D_bit1_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit24,<I/O>
																							//def: MIS_GPIO_bit24,<I/O>
#define RTD298X_BGA459_PIN_G24_UP							(1&0x01)// 0xB8000850[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G24_PD							(0&0x01)// 0xB8000850[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G24_DS							(0&0x01)// 0xB8000850[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G24_SR							(0&0x01)// 0xB8000850[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_25_io 119
#define RTD298X_BGA459_PIN_AE14								(0x16&0x1F)//0xB8000820[22:18];
																							//01: TPO_Data_bit4_pad,<O>,<HS>
																							//03: TCON_bit6,<O>
																							//04: ld_spi0_p1_cs1,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//08: SC1_SCLK,<OD>
																							//09: uart2_rXdi_src4,<I>
																							//16: PCMCIA_ADDR_bit12,<OD>,<HS>
																							//1F: MIS_GPIO_bit25,<I/O>
																							//def: MIS_GPIO_bit25,<I/O>
#define RTD298X_BGA459_PIN_AE14_UP							(1&0x01)// 0xB8000820[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE14_PD							(0&0x01)// 0xB8000820[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE14_DS							(0&0x01)// 0xB8000820[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE14_SR							(0&0x01)// 0xB8000820[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_26_io 120
#define RTD298X_BGA459_PIN_AA16								(0x16&0x1F)//0xB8000820[13:9];
																							//01: TPO_VAL_pad,<O>,<HS>
																							//03: TCON_bit7,<O>
																							//04: ld_spi0_p2_sck_src4,<I/O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//08: SC1_DATA0_SRC2,<I/O>
																							//09: uart2_tXdo,<O>
																							//0A: ETN_CLK_OUT,<O>,<HS>
																							//16: PCMCIA_RST0,<OD>,<HS>
																							//1F: MIS_GPIO_bit26,<I/O>
																							//def: MIS_GPIO_bit26,<I/O>
#define RTD298X_BGA459_PIN_AA16_UP							(1&0x01)// 0xB8000820[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA16_PD							(0&0x01)// 0xB8000820[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA16_DS							(0&0x01)// 0xB8000820[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA16_SR							(0&0x01)// 0xB8000820[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_27_io 121
#define RTD298X_BGA459_PIN_AB16								(0x16&0x1F)//0xB8000824[31:27];
																							//01: TPO_Data_bit3_pad,<O>,<HS>
																							//03: TCON_bit8,<O>
																							//08: SC1_RST,<OD>
																							//16: TP0_CLK_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit27,<I/O>
																							//def: MIS_GPIO_bit27,<I/O>
#define RTD298X_BGA459_PIN_AB16_UP							(1&0x01)// 0xB8000824[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB16_PD							(0&0x01)// 0xB8000824[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB16_DS							(0&0x01)// 0xB8000824[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB16_SR							(0&0x01)// 0xB8000824[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_28_io 122
#define RTD298X_BGA459_PIN_Y17								(0x16&0x1F)//0xB8000824[22:18];
																							//01: TPO_Data_bit2_pad,<O>,<HS>
																							//03: TCON_bit9,<O>
																							//08: SC1_CD_SRC2,<I>
																							//16: PCMCIA_REG_N,<O>,<HS>
																							//1F: MIS_GPIO_bit28,<I/O>
																							//def: MIS_GPIO_bit28,<I/O>
#define RTD298X_BGA459_PIN_Y17_UP							(1&0x01)// 0xB8000824[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y17_PD							(0&0x01)// 0xB8000824[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y17_DS							(0&0x01)// 0xB8000824[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y17_SR							(0&0x01)// 0xB8000824[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_29_io 123
#define RTD298X_BGA459_PIN_G23								(0x16&0x1F)//0xB800084C[31:27];
																							//01: PCMCIA_RST0,<OD>,<HS>
																							//03: TCON_bit10,<O>
																							//07: SC0_CD_SRC2,<I>
																							//09: uart0_rts_n,<O>
																							//0A: uart2_rts_n,<O>
																							//0B: ETN_LED_LINK,<O>
																							//16: TP0_Data_bit2_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit29,<I/O>
																							//def: MIS_GPIO_bit29,<I/O>
#define RTD298X_BGA459_PIN_G23_UP							(1&0x01)// 0xB800084C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G23_PD							(0&0x01)// 0xB800084C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G23_DS							(0&0x01)// 0xB800084C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G23_SR							(0&0x01)// 0xB800084C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_30_io 124
#define RTD298X_BGA459_PIN_AA17								(0x16&0x1F)//0xB8000824[13:9];
																							//01: TPO_Data_bit0_pad,<O>,<HS>
																							//03: TCON_bit0,<O>
																							//06: CR_SD_CMD_SRC4,<I/O>,<HS>
																							//09: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_3,<OD>
																							//16: PCMCIA_INPACK0_N_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit30,<I/O>
																							//def: MIS_GPIO_bit30,<I/O>
#define RTD298X_BGA459_PIN_AA17_UP							(1&0x01)// 0xB8000824[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA17_PD							(0&0x01)// 0xB8000824[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA17_DS							(0&0x01)// 0xB8000824[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA17_SR							(0&0x01)// 0xB8000824[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_31_io 125
#define RTD298X_BGA459_PIN_Y16								(0x16&0x1F)//0xB8000828[31:27];
																							//01: TPO_SYNC_pad,<O>,<HS>
																							//03: TCON_bit1,<O>
																							//06: CR_SD_WP_SRC3,<I>,<HS>
																							//0C: misc_uni_pwm2,<O>
																							//0D: misc_pwm_2,<OD>
																							//16: PCMCIA_WAIT0_N_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit31,<I/O>
																							//def: MIS_GPIO_bit31,<I/O>
#define RTD298X_BGA459_PIN_Y16_UP							(1&0x01)// 0xB8000828[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y16_PD							(0&0x01)// 0xB8000828[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y16_DS							(0&0x01)// 0xB8000828[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y16_SR							(0&0x01)// 0xB8000828[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_32_io 126
#define RTD298X_BGA459_PIN_H23								(0x16&0x1F)//0xB800084C[22:18];
																							//01: PCMCIA_IOWR_N,<O>,<HS>
																							//04: TCON_bit0,<O>
																							//07: SC0_SCLK,<OD>
																							//09: uart0_cts_n_src3,<I>
																							//0A: uart2_cts_n_src1,<I>
																							//0C: misc_uni_pwm3,<O>
																							//0D: misc_pwm_5,<OD>
																							//16: TP0_Data_bit1_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit32,<I/O>
																							//def: MIS_GPIO_bit32,<I/O>
#define RTD298X_BGA459_PIN_H23_UP							(1&0x01)// 0xB800084C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_H23_PD							(0&0x01)// 0xB800084C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_H23_DS							(0&0x01)// 0xB800084C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_H23_SR							(0&0x01)// 0xB800084C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_33_io 127
#define RTD298X_BGA459_PIN_H24								(0x16&0x1F)//0xB800084C[13:9];
																							//01: PCMCIA_IORD_N,<O>,<HS>
																							//03: TTL_denout,<O>,<HS>
																							//04: ATV_VSYNC_OUT,<O>
																							//05: TCON_bit1,<O>
																							//07: SC0_RST,<OD>
																							//08: uart1_rXdi_src2,<I>
																							//13: I2S_out_MCLK,<O>
																							//16: PCMCIA_D_bit2_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit33,<I/O>
																							//def: MIS_GPIO_bit33,<I/O>
#define RTD298X_BGA459_PIN_H24_UP							(1&0x01)// 0xB800084C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_H24_PD							(0&0x01)// 0xB800084C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_H24_DS							(0&0x01)// 0xB800084C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_H24_SR							(0&0x01)// 0xB800084C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_34_io 128
#define RTD298X_BGA459_PIN_Y18								(0x16&0x1F)//0xB8000828[22:18];
																							//01: TP0_Data_bit7_SRC0,<I>,<HS>
																							//02: TTL_vsout,<O>,<HS>
																							//03: TCON_bit7,<O>
																							//06: CR_SD_CD_SRC4,<I>,<HS>
																							//08: uart1_tXdo,<O>
																							//0A: SPDIF_OUT,<O>
																							//13: I2S_out_Data0,<O>
																							//16: TP0_Data_bit0_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit34,<I/O>
																							//def: MIS_GPIO_bit34,<I/O>
#define RTD298X_BGA459_PIN_Y18_UP							(1&0x01)// 0xB8000828[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y18_PD							(0&0x01)// 0xB8000828[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y18_DS							(0&0x01)// 0xB8000828[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y18_SR							(0&0x01)// 0xB8000828[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_36_io 129
#define RTD298X_BGA459_PIN_AA18								(0x16&0x1F)//0xB800082C[31:27];
																							//01: TP0_Data_bit6_SRC0,<I>,<HS>
																							//02: TTL_CLK,<O>,<HS>
																							//03: TCON_bit9,<O>
																							//06: CR_SD_Data_bit0_SRC2,<I/O>,<HS>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//16: TP0_SYNC_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit36,<I/O>
																							//def: MIS_GPIO_bit36,<I/O>
#define RTD298X_BGA459_PIN_AA18_UP							(1&0x01)// 0xB800082C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA18_PD							(0&0x01)// 0xB800082C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA18_DS							(0&0x01)// 0xB800082C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA18_SR							(0&0x01)// 0xB800082C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_37_io 130
#define RTD298X_BGA459_PIN_AB18								(0x16&0x1F)//0xB800082C[22:18];
																							//00: nf_tmX_cle,<O>,<HS>
																							//01: TP0_Data_bit5_SRC0,<I>,<HS>
																							//06: CR_SD_Data_bit1_SRC2,<I/O>,<HS>
																							//16: TP0_VAL_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit37,<I/O>
																							//def: MIS_GPIO_bit37,<I/O>
#define RTD298X_BGA459_PIN_AB18_UP							(1&0x01)// 0xB800082C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB18_PD							(0&0x01)// 0xB800082C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB18_DS							(0&0x01)// 0xB800082C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB18_SR							(0&0x01)// 0xB800082C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_38_io 131
#define RTD298X_BGA459_PIN_AC15								(0x16&0x1F)//0xB800082C[13:9];
																							//00: nf_tmX_wr_n,<O>,<HS>
																							//01: TP0_Data_bit4_SRC0,<I>,<HS>
																							//06: CR_SD_Data_bit2_SRC2,<I/O>,<HS>
																							//16: PCMCIA_D_bit0_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit38,<I/O>
																							//def: MIS_GPIO_bit38,<I/O>
#define RTD298X_BGA459_PIN_AC15_UP							(1&0x01)// 0xB800082C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC15_PD							(0&0x01)// 0xB800082C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC15_DS							(0&0x01)// 0xB800082C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC15_SR							(0&0x01)// 0xB800082C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_43_io 132
#define RTD298X_BGA459_PIN_AD15								(0x16&0x1F)//0xB8000834[22:18];
																							//00: nf_tmX_ale,<O>,<HS>
																							//01: TP0_Data_bit3_SRC0,<I>,<HS>
																							//06: CR_SD_Data_bit3_SRC2,<I/O>,<HS>
																							//16: PCMCIA_ADDR_bit0,<OD>,<HS>
																							//1F: MIS_GPIO_bit43,<I/O>
																							//def: MIS_GPIO_bit43,<I/O>
#define RTD298X_BGA459_PIN_AD15_UP							(1&0x01)// 0xB8000834[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD15_PD							(0&0x01)// 0xB8000834[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD15_DS							(0&0x01)// 0xB8000834[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD15_SR							(0&0x01)// 0xB8000834[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_55_io 133
#define RTD298X_BGA459_PIN_AD19								(0x00&0x1F)//0xB8000844[22:18];
																							//00: nf_tmX_ce_n_bit0,<O>,<HS>
																							//03: TCON_bit11,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0A: ETN_LED_LINK,<O>
																							//0B: SPDIF_OUT,<O>
																							//0D: misc_pwm_0,<OD>
																							//10: P_TXD1,<O>,<HS>
																							//12: I2C0_SCL_SRC3,<I/O>
																							//13: I2S_out_Data1,<O>
																							//1F: MIS_GPIO_bit55,<I/O>
																							//def: MIS_GPIO_bit55,<I/O>
#define RTD298X_BGA459_PIN_AD19_UP							(1&0x01)// 0xB8000844[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD19_PD							(0&0x01)// 0xB8000844[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD19_DS							(0&0x01)// 0xB8000844[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD19_SR							(0&0x01)// 0xB8000844[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_92_io:2 134
#define RTD298X_BGA459_PIN_D15								(0x06&0x1F)//0xB800085C[31:27];
																							//01: PCMCIA_ADDR_bit7,<OD>,<HS>
																							//03: TCON_bit17,<O>
																							//05: ld_spi1_p2_sck_src2,<I/O>
																							//06: SC0_DATA0_SRC6,<I/O>
																							//07: SC1_RST,<OD>
																							//08: uart0_rXdi_src1,<I>
																							//09: uart1_rXdi_src3,<I>
																							//0A: ETN_LED_LINK,<O>
																							//0C: misc_uni_pwm0,<O>
																							//0D: misc_pwm_0,<OD>
																							//0F: I2C2_SCL_SRC7,<I/O>
																							//10: P_TXEN,<O>,<HS>
																							//13: I2S_out_Data0,<O>
																							//14: GSPI_SCLK_SRC2,<I/O>,<HS>
																							//15: TP0_Data_bit3_SRC1,<I>,<HS>
																							//1F: MIS_GPIO_bit92,<I/O>
																							//def: MIS_GPIO_bit92,<I/O>
#define RTD298X_BGA459_PIN_D15_UP							(1&0x01)// 0xB800085C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D15_PD							(0&0x01)// 0xB800085C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D15_DS							(0&0x01)// 0xB800085C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D15_SR							(0&0x01)// 0xB800085C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_93_io:2 135
#define RTD298X_BGA459_PIN_B17								(0x06&0x1F)//0xB800085C[22:18];
																							//01: PCMCIA_ADDR_bit6,<OD>,<HS>
																							//03: TCON_bit18,<O>
																							//06: SC0_CD_SRC6,<I>
																							//07: SC1_DATA0_SRC3,<I/O>
																							//08: uart0_tXdo,<O>
																							//09: uart1_tXdo,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1,<OD>
																							//0F: I2C2_SDA_SRC7,<I/O>
																							//10: P_COL_SRC1,<I>,<HS>
																							//13: I2S_out_Data1,<O>
																							//15: TP0_Data_bit4_SRC1,<I>,<HS>
																							//1F: MIS_GPIO_bit93,<I/O>
																							//def: MIS_GPIO_bit93,<I/O>
#define RTD298X_BGA459_PIN_B17_UP							(1&0x01)// 0xB800085C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B17_PD							(0&0x01)// 0xB800085C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B17_DS							(0&0x01)// 0xB800085C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B17_SR							(0&0x01)// 0xB800085C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_94_io 136
#define RTD298X_BGA459_PIN_C16								(0x06&0x1F)//0xB800085C[13:9];
																							//01: PCMCIA_D_bit4_SRC0,<I/O>,<HS>
																							//03: TCON_bit19,<O>
																							//05: CR_SD_Data_bit0_SRC0,<I/O>,<HS>
																							//06: SC0_SCLK,<OD>
																							//07: SC1_PWR_SEL,<OD>
																							//09: uart2_rXdi_src3,<I>
																							//0C: misc_uni_pwm4,<O>
																							//0D: misc_pwm_6,<OD>
																							//10: P_MDIO_SRC1,<I/O>,<HS>
																							//15: PCMCIA_D_bit6_SRC1,<I/O>,<HS>
																							//1F: MIS_GPIO_bit94,<I/O>
																							//def: MIS_GPIO_bit94,<I/O>
#define RTD298X_BGA459_PIN_C16_UP							(1&0x01)// 0xB800085C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C16_PD							(0&0x01)// 0xB800085C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C16_DS							(0&0x01)// 0xB800085C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C16_SR							(0&0x01)// 0xB800085C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_95_io 137
#define RTD298X_BGA459_PIN_B15								(0x06&0x1F)//0xB8000860[31:27];
																							//01: PCMCIA_CE1_N,<O>,<HS>
																							//03: TCON_bit1,<O>
																							//06: SC0_RST,<OD>
																							//09: uart2_tXdo,<O>
																							//0E: I2C0_SCL_SRC15,<I/O>
																							//10: P_MDC,<O>,<HS>
																							//15: PCMCIA_D_bit7_SRC1,<I/O>,<HS>
																							//1F: MIS_GPIO_bit95,<I/O>
																							//def: MIS_GPIO_bit95,<I/O>
#define RTD298X_BGA459_PIN_B15_UP							(1&0x01)// 0xB8000860[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B15_PD							(0&0x01)// 0xB8000860[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B15_DS							(0&0x01)// 0xB8000860[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B15_SR							(0&0x01)// 0xB8000860[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_96_io 138
#define RTD298X_BGA459_PIN_B14								(0x1F&0x1F)//0xB8000860[22:18];
																							//01: PCMCIA_D_bit5_SRC0,<I/O>,<HS>
																							//03: TCON_bit6,<O>
																							//05: CR_SD_Data_bit1_SRC0,<I/O>,<HS>
																							//06: SC0_PWR_SEL,<OD>
																							//0D: misc_pwm_7,<OD>
																							//0E: I2C0_SDA_SRC15,<I/O>
																							//10: P_RXER_SRC1,<I>,<HS>
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//15: TP0_Data_bit5_SRC1,<I>,<HS>
																							//1F: MIS_GPIO_bit96,<I/O>
																							//def: MIS_GPIO_bit96,<I/O>
#define RTD298X_BGA459_PIN_B14_UP							(1&0x01)// 0xB8000860[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B14_PD							(0&0x01)// 0xB8000860[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B14_DS							(0&0x01)// 0xB8000860[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B14_SR							(0&0x01)// 0xB8000860[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_97_io 139
#define RTD298X_BGA459_PIN_C11								(0x1F&0x1F)//0xB8000860[13:9];
																							//03: PCMCIA_CE2_N,<O>
																							//05: CR_SD_CLK,<O>,<HS>
																							//07: SC0_CD_SRC3,<I>
																							//08: SC0_DATA0_SRC4,<I/O>
																							//09: IRTX,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_6,<OD>
																							//10: P_TXD1,<O>,<HS>
																							//11: P_CRS_SRC1,<I>,<HS>
																							//14: SC1_CD_SRC7,<I>
																							//15: TP0_Data_bit6_SRC1,<I>,<HS>
																							//1F: MIS_GPIO_bit97,<I/O>
																							//def: MIS_GPIO_bit97,<I/O>
#define RTD298X_BGA459_PIN_C11_UP							(1&0x01)// 0xB8000860[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C11_PD							(0&0x01)// 0xB8000860[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C11_DS							(0&0x01)// 0xB8000860[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C11_SR							(0&0x01)// 0xB8000860[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_98_io 140
#define RTD298X_BGA459_PIN_D16								(0x05&0x1F)//0xB8000864[31:27];
																							//01: PCMCIA_ADDR_bit1,<OD>,<HS>
																							//02: EMMC_CLK,<O>,<HS>
																							//05: CR_SD_CLK,<O>,<HS>
																							//10: P_RXDV_SRC1,<I>,<HS>
																							//15: PCMCIA_OE_N,<O>,<HS>
																							//1F: MIS_GPIO_bit98,<I/O>
																							//def: MIS_GPIO_bit98,<I/O>
#define RTD298X_BGA459_PIN_D16_UP							(1&0x01)// 0xB8000864[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D16_PD							(0&0x01)// 0xB8000864[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D16_DS							(0&0x01)// 0xB8000864[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D16_SR							(0&0x01)// 0xB8000864[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_99_io 141
#define RTD298X_BGA459_PIN_C13								(0x05&0x1F)//0xB8000864[22:18];
																							//01: PCMCIA_ADDR_bit0,<OD>,<HS>
																							//02: EMMC_CMD_SRC0,<I/O>,<HS>
																							//05: CR_SD_CMD_SRC5,<I/O>,<HS>
																							//09: ETN_LED_LINK,<O>
																							//0B: SPDIF_IN_src1,<I>
																							//10: P_RXD0_SRC1,<I>,<HS>
																							//15: PCMCIA_ADDR_bit11,<OD>,<HS>
																							//1F: MIS_GPIO_bit99,<I/O>
																							//def: MIS_GPIO_bit99,<I/O>
#define RTD298X_BGA459_PIN_C13_UP							(1&0x01)// 0xB8000864[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C13_PD							(0&0x01)// 0xB8000864[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C13_DS							(0&0x01)// 0xB8000864[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C13_SR							(0&0x01)// 0xB8000864[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_100_io 142
#define RTD298X_BGA459_PIN_C17								(0x05&0x1F)//0xB8000864[13:9];
																							//01: PCMCIA_INPACK0_N_SRC0,<I>,<HS>
																							//05: CR_SD_WP_SRC8,<I>,<HS>
																							//09: ETN_LED_LINK,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//10: P_RXD1_SRC1,<I>,<HS>
																							//15: PCMCIA_ADDR_bit8,<OD>,<HS>
																							//1F: MIS_GPIO_bit100,<I/O>
																							//def: MIS_GPIO_bit100,<I/O>
#define RTD298X_BGA459_PIN_C17_UP							(1&0x01)// 0xB8000864[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C17_PD							(0&0x01)// 0xB8000864[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C17_DS							(0&0x01)// 0xB8000864[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C17_SR							(0&0x01)// 0xB8000864[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_101_io 143
#define RTD298X_BGA459_PIN_C14								(0x05&0x1F)//0xB8000868[31:27];
																							//01: PCMCIA_D_bit6_SRC0,<I/O>,<HS>
																							//05: CR_SD_CD_SRC6,<I>,<HS>
																							//06: CR_SD_Data_bit2_SRC0,<I/O>,<HS>
																							//09: ETN_LED_LINK,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0C: misc_uni_pwm4,<O>
																							//0D: misc_pwm_0,<OD>
																							//10: P_RXD2_SRC1,<I>,<HS>
																							//15: PCMCIA_IOWR_N,<O>,<HS>
																							//1F: MIS_GPIO_bit101,<I/O>
																							//def: MIS_GPIO_bit101,<I/O>
#define RTD298X_BGA459_PIN_C14_UP							(1&0x01)// 0xB8000868[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C14_PD							(0&0x01)// 0xB8000868[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C14_DS							(0&0x01)// 0xB8000868[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C14_SR							(0&0x01)// 0xB8000868[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_102_io 144
#define RTD298X_BGA459_PIN_D13								(0x05&0x1F)//0xB8000868[22:18];
																							//01: PCMCIA_D_bit7_SRC0,<I/O>,<HS>
																							//05: CR_SD_Data_bit0_SRC4,<I/O>,<HS>
																							//06: CR_SD_Data_bit3_SRC0,<I/O>,<HS>
																							//0F: I2C1_SCL_SRC1,<I/O>
																							//10: P_RXD3_SRC1,<I>,<HS>
																							//11: I2C0_SCL_SRC11,<I/O>
																							//15: PCMCIA_ADDR_bit13,<OD>,<HS>
																							//1F: MIS_GPIO_bit102,<I/O>
																							//def: MIS_GPIO_bit102,<I/O>
#define RTD298X_BGA459_PIN_D13_UP							(1&0x01)// 0xB8000868[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D13_PD							(0&0x01)// 0xB8000868[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D13_DS							(0&0x01)// 0xB8000868[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D13_SR							(0&0x01)// 0xB8000868[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_103_io 145
#define RTD298X_BGA459_PIN_C12								(0x05&0x1F)//0xB8000868[13:9];
																							//01: PCMCIA_OE_N,<O>,<HS>
																							//05: CR_SD_Data_bit1_SRC4,<I/O>,<HS>
																							//0F: I2C1_SDA_SRC1,<I/O>
																							//10: P_RXC_SRC1,<I>,<HS>
																							//11: I2C0_SDA_SRC11,<I/O>
																							//15: TPO_Data_bit0_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit103,<I/O>
																							//def: MIS_GPIO_bit103,<I/O>
#define RTD298X_BGA459_PIN_C12_UP							(1&0x01)// 0xB8000868[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C12_PD							(0&0x01)// 0xB8000868[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C12_DS							(0&0x01)// 0xB8000868[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C12_SR							(0&0x01)// 0xB8000868[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_104_io 146
#define RTD298X_BGA459_PIN_F10								(0x05&0x1F)//0xB800086C[31:27];
																							//01: PCMCIA_CD0_N_SRC0,<I>,<HS>
																							//05: CR_SD_Data_bit2_SRC5,<I/O>,<HS>
																							//0A: SPDIF_OUT,<O>
																							//10: P_TXC_SRC1,<I>,<HS>
																							//15: PCMCIA_WE_N,<O>,<HS>
																							//1F: MIS_GPIO_bit104,<I/O>
																							//def: MIS_GPIO_bit104,<I/O>
#define RTD298X_BGA459_PIN_F10_UP							(1&0x01)// 0xB800086C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F10_PD							(0&0x01)// 0xB800086C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F10_DS							(0&0x01)// 0xB800086C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F10_SR							(0&0x01)// 0xB800086C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_105_io 147
#define RTD298X_BGA459_PIN_D12								(0x05&0x1F)//0xB800086C[22:18];
																							//01: PCMCIA_IREQ0_N_SRC0,<I>,<HS>
																							//05: CR_SD_Data_bit3_SRC5,<I/O>,<HS>
																							//10: P_TXD0,<O>,<HS>
																							//15: TPO_VAL_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit105,<I/O>
																							//def: MIS_GPIO_bit105,<I/O>
#define RTD298X_BGA459_PIN_D12_UP							(1&0x01)// 0xB800086C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D12_PD							(0&0x01)// 0xB800086C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D12_DS							(0&0x01)// 0xB800086C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D12_SR							(0&0x01)// 0xB800086C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_142_io 148
#define RTD298X_BGA459_PIN_H25								(0x1F&0x1F)//0xB8000850[22:18];
																							//01: PCMCIA_ADDR_bit11,<OD>,<HS>
																							//03: TCON_bit12,<O>
																							//07: SC0_PWR_SEL,<OD>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1_src3,<I/O>
																							//13: I2S_out_Data1,<O>
																							//16: PCMCIA_CD1_N_SRC2,<I>
																							//1F: MIS_GPIO_bit142,<I/O>
																							//def: MIS_GPIO_bit142,<I/O>
#define RTD298X_BGA459_PIN_H25_UP							(1&0x01)// 0xB8000850[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_H25_PD							(0&0x01)// 0xB8000850[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_H25_DS							(0&0x01)// 0xB8000850[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_H25_SR							(0&0x01)// 0xB8000850[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_143_io 149
#define RTD298X_BGA459_PIN_AC17								(0x16&0x1F)//0xB8000848[31:27];
																							//00: nf_tmX_rd_n,<O>,<HS>
																							//02: EMMC_CLK,<O>,<HS>
																							//06: CR_SD_CD_SRC5,<I>,<HS>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_pwm_0,<OD>
																							//13: I2S_out_Data1,<O>
																							//16: PCMCIA_ADDR_bit1,<OD>,<HS>
																							//1F: MIS_GPIO_bit143,<I/O>
																							//def: MIS_GPIO_bit143,<I/O>
#define RTD298X_BGA459_PIN_AC17_UP							(1&0x01)// 0xB8000848[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC17_PD							(0&0x01)// 0xB8000848[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC17_DS							(0&0x01)// 0xB8000848[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC17_SR							(0&0x01)// 0xB8000848[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_145_io 150
#define RTD298X_BGA459_PIN_M4								(0x1F&0x1F)//0xB8000894[13:9];
																							//03: TCON_bit8,<O>
																							//09: uart1_tXdo,<O>
																							//10: P_TXD1,<O>,<HS>
																							//1F: MIS_GPIO_bit145,<I/O>
																							//def: MIS_GPIO_bit145,<I/O>
#define RTD298X_BGA459_PIN_M4_UP							(1&0x01)// 0xB8000894[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_M4_PD							(0&0x01)// 0xB8000894[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_M4_DS							(0&0x01)// 0xB8000894[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_M4_SR							(0&0x01)// 0xB8000894[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_146_io 151
#define RTD298X_BGA459_PIN_N5								(0x1F&0x1F)//0xB8000898[31:27];
																							//03: TCON_bit0,<O>
																							//10: P_TXD2,<O>,<HS>
																							//15: GSPI_CS_N_SRC4,<I/O>,<HS>
																							//1F: MIS_GPIO_bit146,<I/O>
																							//def: MIS_GPIO_bit146,<I/O>
#define RTD298X_BGA459_PIN_N5_UP							(1&0x01)// 0xB8000898[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_N5_PD							(0&0x01)// 0xB8000898[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_N5_DS							(0&0x01)// 0xB8000898[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_N5_SR							(0&0x01)// 0xB8000898[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_147_io 152
#define RTD298X_BGA459_PIN_N4								(0x1F&0x1F)//0xB8000898[22:18];
																							//03: TCON_bit1,<O>
																							//10: P_TXD3,<O>,<HS>
																							//15: GSPI_SCLK_SRC4,<I/O>,<HS>
																							//1F: MIS_GPIO_bit147,<I/O>
																							//def: MIS_GPIO_bit147,<I/O>
#define RTD298X_BGA459_PIN_N4_UP							(1&0x01)// 0xB8000898[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_N4_PD							(0&0x01)// 0xB8000898[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_N4_DS							(0&0x01)// 0xB8000898[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_N4_SR							(0&0x01)// 0xB8000898[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_148_io 153
#define RTD298X_BGA459_PIN_N6								(0x09&0x1F)//0xB8000898[13:9];
																							//03: TCON_bit2,<O>
																							//08: IRTX,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_3,<OD>
																							//10: P_TXEN,<O>,<HS>
																							//15: GSPI_DO_SRC4,<I/O>,<HS>
																							//1F: MIS_GPIO_bit148,<I/O>
																							//def: MIS_GPIO_bit148,<I/O>
#define RTD298X_BGA459_PIN_N6_UP							(1&0x01)// 0xB8000898[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_N6_PD							(0&0x01)// 0xB8000898[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_N6_DS							(0&0x01)// 0xB8000898[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_N6_SR							(0&0x01)// 0xB8000898[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_149_io 154
#define RTD298X_BGA459_PIN_P5								(0x09&0x1F)//0xB800089C[31:27];
																							//03: PCMCIA_WAIT1_N_SRC0,<I>
																							//04: TCON_bit3,<O>
																							//07: SC0_RST,<OD>
																							//09: ETN_LED_TXRX,<O>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//10: P_COL_SRC0,<I>,<HS>
																							//15: GSPI_DI_SRC4,<I/O>,<HS>
																							//1F: MIS_GPIO_bit149,<I/O>
																							//def: MIS_GPIO_bit149,<I/O>
#define RTD298X_BGA459_PIN_P5_UP							(1&0x01)// 0xB800089C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_P5_PD							(0&0x01)// 0xB800089C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_P5_DS							(0&0x01)// 0xB800089C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_P5_SR							(0&0x01)// 0xB800089C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_150_io 155
#define RTD298X_BGA459_PIN_A12								(0x02&0x1F)//0xB8000958[22:18];
																							//02: EMMC_CMD_SRC6,<I/O>,<HS>
																							//03: TCON_bit17,<O>
																							//15: PCMCIA_ADDR_bit0,<OD>,<HS>
																							//1F: MIS_GPIO_bit150,<I/O>
																							//def: MIS_GPIO_bit150,<I/O>
#define RTD298X_BGA459_PIN_A12_UP							(1&0x01)// 0xB8000958[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A12_PD							(0&0x01)// 0xB8000958[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A12_DS							(0&0x01)// 0xB8000958[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A12_SR							(0&0x01)// 0xB8000958[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_151_io 156
#define RTD298X_BGA459_PIN_A16								(0x1F&0x1F)//0xB8000958[13:9];
																							//03: TCON_bit18,<O>
																							//08: IRTX,<O>
																							//15: PCMCIA_D_bit0_SRC1,<I/O>,<HS>
																							//1F: MIS_GPIO_bit151,<I/O>
																							//def: MIS_GPIO_bit151,<I/O>
#define RTD298X_BGA459_PIN_A16_UP							(1&0x01)// 0xB8000958[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A16_PD							(0&0x01)// 0xB8000958[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A16_DS							(0&0x01)// 0xB8000958[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A16_SR							(0&0x01)// 0xB8000958[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_152_io 157
#define RTD298X_BGA459_PIN_B13								(0x02&0x1F)//0xB80008A0[31:27];
																							//02: EMMC_Data_bit4_SRC2,<I/O>,<HS>
																							//03: TCON_bit19,<O>
																							//15: PCMCIA_ADDR_bit3,<OD>,<HS>
																							//1F: MIS_GPIO_bit152,<I/O>
																							//def: MIS_GPIO_bit152,<I/O>
#define RTD298X_BGA459_PIN_B13_UP							(1&0x01)// 0xB80008A0[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B13_PD							(0&0x01)// 0xB80008A0[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B13_DS							(0&0x01)// 0xB80008A0[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B13_SR							(0&0x01)// 0xB80008A0[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_153_io 158
#define RTD298X_BGA459_PIN_B12								(0x02&0x1F)//0xB80008A0[22:18];
																							//02: EMMC_Data_bit3_SRC2,<I/O>,<HS>
																							//03: TCON_bit20,<O>
																							//15: PCMCIA_ADDR_bit2,<OD>,<HS>
																							//1F: MIS_GPIO_bit153,<I/O>
																							//def: MIS_GPIO_bit153,<I/O>
#define RTD298X_BGA459_PIN_B12_UP							(1&0x01)// 0xB80008A0[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B12_PD							(0&0x01)// 0xB80008A0[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B12_DS							(0&0x01)// 0xB80008A0[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B12_SR							(0&0x01)// 0xB80008A0[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_157_io 159
#define RTD298X_BGA459_PIN_D10								(0x02&0x1F)//0xB80008A4[13:9];
																							//02: EMMC_CLK,<O>,<HS>
																							//03: TCON_bit24,<O>
																							//15: PCMCIA_ADDR_bit1,<OD>,<HS>
																							//1F: MIS_GPIO_bit157,<I/O>
																							//def: MIS_GPIO_bit157,<I/O>
#define RTD298X_BGA459_PIN_D10_UP							(1&0x01)// 0xB80008A4[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D10_PD							(0&0x01)// 0xB80008A4[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D10_DS							(0&0x01)// 0xB80008A4[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D10_SR							(0&0x01)// 0xB80008A4[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_169_io 160
#define RTD298X_BGA459_PIN_C15								(0x02&0x1F)//0xB8000874[22:18];
																							//02: EMMC_Data_bit6_SRC2,<I/O>,<HS>
																							//03: TCON_bit6,<O>
																							//0A: USB_PWR_FLAG2_SRC0,<I>
																							//15: PCMCIA_ADDR_bit12,<OD>,<HS>
																							//1F: MIS_GPIO_bit169,<I/O>
																							//def: MIS_GPIO_bit169,<I/O>
#define RTD298X_BGA459_PIN_C15_UP							(1&0x01)// 0xB8000874[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C15_PD							(0&0x01)// 0xB8000874[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C15_DS							(0&0x01)// 0xB8000874[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C15_SR							(0&0x01)// 0xB8000874[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_170_io 161
#define RTD298X_BGA459_PIN_C9								(0x0F&0x1F)//0xB8000874[13:9];
																							//03: TCON_bit7,<O>
																							//0A: USB_PWR_CTRL2,<O>
																							//0F: I2C1_SDA_SRC3,<I/O>
																							//15: TPO_Data_bit5_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit170,<I/O>
																							//def: MIS_GPIO_bit170,<I/O>
#define RTD298X_BGA459_PIN_C9_UP							(1&0x01)// 0xB8000874[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_C9_PD							(0&0x01)// 0xB8000874[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_C9_DS							(0&0x01)// 0xB8000874[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_C9_SR							(0&0x01)// 0xB8000874[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_171_io 162
#define RTD298X_BGA459_PIN_F11								(0x1F&0x1F)//0xB8000878[31:27];
																							//03: TCON_bit8,<O>
																							//0B: SPDIF_OUT,<O>
																							//15: TPO_data_bit7_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit171,<I/O>
																							//def: MIS_GPIO_bit171,<I/O>
#define RTD298X_BGA459_PIN_F11_UP							(1&0x01)// 0xB8000878[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F11_PD							(0&0x01)// 0xB8000878[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F11_DS							(0&0x01)// 0xB8000878[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F11_SR							(0&0x01)// 0xB8000878[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_173_io 163
#define RTD298X_BGA459_PIN_A15								(0x1F&0x1F)//0xB8000087[13:9];
																							//03: TCON_bit10,<O>
																							//12: I2C2_SCL_SRC12,<I/O>
																							//15: PCMCIA_ADDR_bit10,<OD>,<HS>
																							//1F: MIS_GPIO_bit173,<I/O>
																							//def: MIS_GPIO_bit173,<I/O>
#define RTD298X_BGA459_PIN_A15_UP							(1&0x01)// 0xB8000087[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A15_PD							(0&0x01)// 0xB8000087[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A15_DS							(0&0x01)// 0xB8000087[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A15_SR							(0&0x01)// 0xB8000087[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_174_io 164
#define RTD298X_BGA459_PIN_B16								(0x1F&0x1F)//0xB800087C[31:27];
																							//03: TCON_bit11,<O>
																							//12: I2C2_SDA_SRC12,<I/O>
																							//15: TP0_Data_bit7_SRC1,<I>,<HS>
																							//1F: MIS_GPIO_bit174,<I/O>
																							//def: MIS_GPIO_bit174,<I/O>
#define RTD298X_BGA459_PIN_B16_UP							(1&0x01)// 0xB800087C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B16_PD							(0&0x01)// 0xB800087C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B16_DS							(0&0x01)// 0xB800087C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B16_SR							(0&0x01)// 0xB800087C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_181_io 165
#define RTD298X_BGA459_PIN_B11								(0x02&0x1F)//0xB8000884[22:18];
																							//02: EMMC_Data_bit2_SRC2,<I/O>,<HS>
																							//15: TPO_CLK_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit181,<I/O>
																							//def: MIS_GPIO_bit181,<I/O>
#define RTD298X_BGA459_PIN_B11_UP							(1&0x01)// 0xB8000884[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B11_PD							(0&0x01)// 0xB8000884[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B11_DS							(0&0x01)// 0xB8000884[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B11_SR							(0&0x01)// 0xB8000884[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_182_io 166
#define RTD298X_BGA459_PIN_A13								(0x02&0x1F)//0xB8000884[13:9];
																							//02: EMMC_Data_bit7_SRC2,<I/O>,<HS>
																							//15: PCMCIA_ADDR_bit7,<OD>,<HS>
																							//1F: MIS_GPIO_bit182,<I/O>
																							//def: MIS_GPIO_bit182,<I/O>
#define RTD298X_BGA459_PIN_A13_UP							(1&0x01)// 0xB8000884[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A13_PD							(0&0x01)// 0xB8000884[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A13_DS							(0&0x01)// 0xB8000884[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A13_SR							(0&0x01)// 0xB8000884[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_183_io 167
#define RTD298X_BGA459_PIN_A10								(0x0F&0x1F)//0xB8000888[31:27];
																							//0F: I2C1_SCL_SRC3,<I/O>
																							//15: TPO_Data_bit6_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit183,<I/O>
																							//def: MIS_GPIO_bit183,<I/O>
#define RTD298X_BGA459_PIN_A10_UP							(1&0x01)// 0xB8000888[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A10_PD							(0&0x01)// 0xB8000888[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A10_DS							(0&0x01)// 0xB8000888[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A10_SR							(0&0x01)// 0xB8000888[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_184_io 168
#define RTD298X_BGA459_PIN_F12								(0x02&0x1F)//0xB8000888[22:18];
																							//02: EMMC_Data_bit0_SRC2,<I/O>,<HS>
																							//15: PCMCIA_ADDR_bit6,<OD>,<HS>
																							//1F: MIS_GPIO_bit184,<I/O>
																							//def: MIS_GPIO_bit184,<I/O>
#define RTD298X_BGA459_PIN_F12_UP							(1&0x01)// 0xB8000888[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F12_PD							(0&0x01)// 0xB8000888[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F12_DS							(0&0x01)// 0xB8000888[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F12_SR							(0&0x01)// 0xB8000888[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_185_io 169
#define RTD298X_BGA459_PIN_E12								(0x02&0x1F)//0xB8000888[13:9];
																							//02: EMMC_Data_bit1_SRC2,<I/O>,<HS>
																							//15: PCMCIA_ADDR_bit5,<OD>,<HS>
																							//1F: MIS_GPIO_bit185,<I/O>
																							//def: MIS_GPIO_bit185,<I/O>
#define RTD298X_BGA459_PIN_E12_UP							(1&0x01)// 0xB8000888[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E12_PD							(0&0x01)// 0xB8000888[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E12_DS							(0&0x01)// 0xB8000888[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E12_SR							(0&0x01)// 0xB8000888[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_188_io 170
#define RTD298X_BGA459_PIN_E11								(0x02&0x1F)//0xB800088C[13:9];
																							//02: EMMC_Data_bit5_SRC2,<I/O>,<HS>
																							//0A: USB_PWR_CTRL2,<O>
																							//15: PCMCIA_ADDR_bit4,<OD>,<HS>
																							//1F: MIS_GPIO_bit188,<I/O>
																							//def: MIS_GPIO_bit188,<I/O>
#define RTD298X_BGA459_PIN_E11_UP							(1&0x01)// 0xB800088C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E11_PD							(0&0x01)// 0xB800088C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E11_DS							(0&0x01)// 0xB800088C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E11_SR							(0&0x01)// 0xB800088C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_189_io 171
#define RTD298X_BGA459_PIN_K4								(0x1F&0x1F)//0xB8000890[31:27];
																							//03: TCON_bit13,<O>
																							//07: SC0_RST,<OD>
																							//08: SC1_RST,<OD>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_3,<OD>
																							//10: P_RXD2_SRC0,<I>,<HS>
																							//1F: MIS_GPIO_bit189,<I/O>
																							//def: MIS_GPIO_bit189,<I/O>
#define RTD298X_BGA459_PIN_K4_UP							(1&0x01)// 0xB8000890[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_K4_PD							(0&0x01)// 0xB8000890[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_K4_DS							(0&0x01)// 0xB8000890[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_K4_SR							(0&0x01)// 0xB8000890[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_190_io 172
#define RTD298X_BGA459_PIN_L6								(0x1F&0x1F)//0xB8000890[22:18];
																							//03: TCON_bit12,<O>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//10: P_RXD3_SRC0,<I>,<HS>
																							//1F: MIS_GPIO_bit190,<I/O>
																							//def: MIS_GPIO_bit190,<I/O>
#define RTD298X_BGA459_PIN_L6_UP							(1&0x01)// 0xB8000890[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_L6_PD							(0&0x01)// 0xB8000890[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_L6_DS							(0&0x01)// 0xB8000890[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_L6_SR							(0&0x01)// 0xB8000890[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_191_io 173
#define RTD298X_BGA459_PIN_L5								(0x1F&0x1F)//0xB8000890[13:9];
																							//03: TCON_bit11,<O>
																							//07: SC0_CD_SRC1,<I>
																							//08: SC1_CD_SRC4,<I>
																							//10: P_RXC_SRC0,<I>,<HS>
																							//1F: MIS_GPIO_bit191,<I/O>
																							//def: MIS_GPIO_bit191,<I/O>
#define RTD298X_BGA459_PIN_L5_UP							(1&0x01)// 0xB8000890[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_L5_PD							(0&0x01)// 0xB8000890[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_L5_DS							(0&0x01)// 0xB8000890[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_L5_SR							(0&0x01)// 0xB8000890[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_197_io 174
#define RTD298X_BGA459_PIN_AD9								(0x16&0x1F)//0xB8000948[31:27];
																							//16: PCMCIA_D_bit3_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit197,<I/O>
																							//def: MIS_GPIO_bit197,<I/O>
#define RTD298X_BGA459_PIN_AD9_UP							(1&0x01)// 0xB8000948[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD9_PD							(0&0x01)// 0xB8000948[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD9_DS							(0&0x01)// 0xB8000948[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD9_SR							(0&0x01)// 0xB8000948[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_198_io 175
#define RTD298X_BGA459_PIN_AA10								(0x16&0x1F)//0xB8000948[22:18];
																							//16: TP0_Data_bit5_SRC2,<I>,<HS>
																							//1F: MIS_GPIO_bit198,<I/O>
																							//def: MIS_GPIO_bit198,<I/O>
#define RTD298X_BGA459_PIN_AA10_UP							(1&0x01)// 0xB8000948[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA10_PD							(0&0x01)// 0xB8000948[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA10_DS							(0&0x01)// 0xB8000948[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA10_SR							(0&0x01)// 0xB8000948[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_199_io 176
#define RTD298X_BGA459_PIN_AD10								(0x16&0x1F)//0xB8000948[13:9];
																							//16: PCMCIA_D_bit6_SRC2,<I/O>,<HS>
																							//1F: MIS_GPIO_bit199,<I/O>
																							//def: MIS_GPIO_bit199,<I/O>
#define RTD298X_BGA459_PIN_AD10_UP							(1&0x01)// 0xB8000948[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD10_PD							(0&0x01)// 0xB8000948[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD10_DS							(0&0x01)// 0xB8000948[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD10_SR							(0&0x01)// 0xB8000948[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_200_io 177
#define RTD298X_BGA459_PIN_AC11								(0x16&0x1F)//0xB800094C[31:27];
																							//16: PCMCIA_OE_N,<O>,<HS>
																							//1F: MIS_GPIO_bit200,<I/O>
																							//def: MIS_GPIO_bit200,<I/O>
#define RTD298X_BGA459_PIN_AC11_UP							(1&0x01)// 0xB800094C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC11_PD							(0&0x01)// 0xB800094C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AC11_DS							(0&0x01)// 0xB800094C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AC11_SR							(0&0x01)// 0xB800094C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_201_io 178
#define RTD298X_BGA459_PIN_AE11								(0x16&0x1F)//0xB800094C[22:18];
																							//16: PCMCIA_CE1_N,<O>,<HS>
																							//1F: MIS_GPIO_bit201,<I/O>
																							//def: MIS_GPIO_bit201,<I/O>
#define RTD298X_BGA459_PIN_AE11_UP							(1&0x01)// 0xB800094C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE11_PD							(0&0x01)// 0xB800094C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AE11_DS							(0&0x01)// 0xB800094C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AE11_SR							(0&0x01)// 0xB800094C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_202_io 179
#define RTD298X_BGA459_PIN_AB13								(0x16&0x1F)//0xB800094C[13:9];
																							//16: PCMCIA_IOWR_N,<O>,<HS>
																							//1F: MIS_GPIO_bit202,<I/O>
																							//def: MIS_GPIO_bit202,<I/O>
#define RTD298X_BGA459_PIN_AB13_UP							(1&0x01)// 0xB800094C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB13_PD							(0&0x01)// 0xB800094C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AB13_DS							(0&0x01)// 0xB800094C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AB13_SR							(0&0x01)// 0xB800094C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_203_io 180
#define RTD298X_BGA459_PIN_AD16								(0x02&0x1F)//0xB8000950[31:27];
																							//15: PCMCIA_ADDR_bit7,<OD>,<HS>
																							//16: PCMCIA_ADDR_bit8,<OD>,<HS>
																							//1F: MIS_GPIO_bit203,<I/O>
																							//def: MIS_GPIO_bit203,<I/O>
#define RTD298X_BGA459_PIN_AD16_UP							(1&0x01)// 0xB8000950[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD16_PD							(0&0x01)// 0xB8000950[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AD16_DS							(0&0x01)// 0xB8000950[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AD16_SR							(0&0x01)// 0xB8000950[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_204_io 181
#define RTD298X_BGA459_PIN_AA11								(0x16&0x1F)//0xB8000950[22:18];
																							//16: TPO_Data_bit1_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit204,<I/O>
																							//def: MIS_GPIO_bit204,<I/O>
#define RTD298X_BGA459_PIN_AA11_UP							(1&0x01)// 0xB8000950[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA11_PD							(0&0x01)// 0xB8000950[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA11_DS							(0&0x01)// 0xB8000950[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA11_SR							(0&0x01)// 0xB8000950[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_205_io 182
#define RTD298X_BGA459_PIN_Y13								(0x16&0x1F)//0xB8000950[13:9];
																							//16: TPO_Data_bit4_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit205,<I/O>
																							//def: MIS_GPIO_bit205,<I/O>
#define RTD298X_BGA459_PIN_Y13_UP							(1&0x01)// 0xB8000950[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y13_PD							(0&0x01)// 0xB8000950[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_Y13_DS							(0&0x01)// 0xB8000950[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_Y13_SR							(0&0x01)// 0xB8000950[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_206_io 183
#define RTD298X_BGA459_PIN_AA14								(0x16&0x1F)//0xB8000954[31:27];
																							//16: TPO_Data_bit2_pad,<O>,<HS>
																							//1F: MIS_GPIO_bit206,<I/O>
																							//def: MIS_GPIO_bit206,<I/O>
#define RTD298X_BGA459_PIN_AA14_UP							(1&0x01)// 0xB8000954[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA14_PD							(0&0x01)// 0xB8000954[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA14_DS							(0&0x01)// 0xB8000954[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA14_SR							(0&0x01)// 0xB8000954[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_25_io 184
#define RTD298X_BGA459_PIN_E8								(0x1F&0x1F)//0xB8060240[22:18];
																							//01: TCON_bit12,<O>
																							//02: ST_dbg_bit15,<I/O>
																							//03: TCON_bit2,<O>
																							//06: CR_SD_CMD_SRC2,<I/O>,<HS>
																							//07: SC0_PWR_SEL,<OD>
																							//08: IRTX,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//0F: I2C2_SCL_SRC5,<I/O>
																							//11: VFD_D_SRC1,<I/O>
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_Data1,<O>
																							//14: SC1_SCLK,<OD>
																							//15: VBY1_HTPD_src6,<I>
																							//1F: ISO_MIS_GPIO_bit25,<I/O>
																							//def: ISO_MIS_GPIO_bit25,<I/O>
#define RTD298X_BGA459_PIN_E8_UP							(1&0x01)// 0xB8060240[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E8_PD							(0&0x01)// 0xB8060240[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E8_DS							(0&0x01)// 0xB8060240[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E8_SR							(0&0x01)// 0xB8060240[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_26_io 185
#define RTD298X_BGA459_PIN_A3								(0x00&0x1F)//0xB8060240[31:27];
																							//00: TP1_Data_bit0_SRC1,<I>,<HS>
																							//01: TCON_bit13,<O>
																							//02: ST_dbg_bit16,<I/O>
																							//03: TCON_bit3,<O>
																							//07: SC0_PWR_SEL,<OD>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_TXRX,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1,<OD>
																							//0F: I2C2_SDA_SRC5,<I/O>
																							//10: P_MDIO_SRC2,<I/O>,<HS>
																							//11: VFD_D_SRC2,<I/O>
																							//12: I2S_out_MCLK,<O>
																							//13: I2S_out_MCLK,<O>
																							//15: VBY1_LOCK_src6,<I>
																							//1F: ISO_MIS_GPIO_bit26,<I/O>
																							//def: ISO_MIS_GPIO_bit26,<I/O>
#define RTD298X_BGA459_PIN_A3_UP							(1&0x01)// 0xB8060240[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A3_PD							(0&0x01)// 0xB8060240[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A3_DS							(0&0x01)// 0xB8060240[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A3_SR							(0&0x01)// 0xB8060240[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_27_io 186
#define RTD298X_BGA459_PIN_B3								(0x00&0x1F)//0xB806023C[13:9];
																							//00: TP1_CLK_SRC1,<I>,<HS>
																							//01: TCON_bit14,<O>
																							//02: ST_dbg_bit17,<I/O>
																							//03: TCON_bit4,<O>
																							//08: SC1_DATA0_SRC0,<I/O>
																							//09: irrX_src2,<I>
																							//0A: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm5,<O>
																							//0D: misc_pwm_3,<OD>
																							//10: P_MDC,<O>,<HS>
																							//11: VFD_CLK,<OD>
																							//13: SC0_PWR_SEL,<OD>
																							//14: SC1_PWR_SEL,<OD>
																							//1F: ISO_MIS_GPIO_bit27,<I/O>
																							//def: ISO_MIS_GPIO_bit27,<I/O>
#define RTD298X_BGA459_PIN_B3_UP							(1&0x01)// 0xB806023C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B3_PD							(0&0x01)// 0xB806023C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B3_DS							(0&0x01)// 0xB806023C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B3_SR							(0&0x01)// 0xB806023C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_28_io 187
#define RTD298X_BGA459_PIN_A2								(0x00&0x1F)//0xB806023C[22:18];
																							//00: TP1_SYNC_SRC1,<I>,<HS>
																							//01: TCON_bit15,<O>
																							//02: ST_dbg_bit18,<I/O>
																							//03: TCON_bit5,<O>
																							//08: SC1_RST,<OD>
																							//09: irrX_src3,<I>
																							//0A: ETN_LED_LINK,<O>
																							//0B: SPDIF_OUT,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//10: P_RXD1_SRC2,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit28,<I/O>
																							//def: ISO_MIS_GPIO_bit28,<I/O>
#define RTD298X_BGA459_PIN_A2_UP							(1&0x01)// 0xB806023C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A2_PD							(0&0x01)// 0xB806023C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A2_DS							(0&0x01)// 0xB806023C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A2_SR							(0&0x01)// 0xB806023C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_29_io 188
#define RTD298X_BGA459_PIN_B2								(0x00&0x1F)//0xB806023C[31:27];
																							//00: TP1_VAL_SRC1,<I>,<HS>
																							//01: TCON_bit16,<O>
																							//02: ST_dbg_bit19,<I/O>
																							//03: TCON_bit6,<O>
																							//08: SC1_CD_SRC6,<I>
																							//0A: ETN_LED_TXRX,<O>
																							//0C: iso_misc_uni_pwm1,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//1F: ISO_MIS_GPIO_bit29,<I/O>
																							//def: ISO_MIS_GPIO_bit29,<I/O>
#define RTD298X_BGA459_PIN_B2_UP							(1&0x01)// 0xB806023C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B2_PD							(0&0x01)// 0xB806023C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B2_DS							(0&0x01)// 0xB806023C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B2_SR							(0&0x01)// 0xB806023C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_30_io 189
#define RTD298X_BGA459_PIN_E6								(0x1F&0x1F)//0xB8060238[13:9];
																							//02: ST_dbg_bit20,<I/O>
																							//03: TCON_bit19,<O>
																							//06: CR_SD_WP_SRC4,<I>,<HS>
																							//08: SC1_PWR_SEL,<OD>
																							//09: uart0_rts_n,<O>
																							//0A: uart2_rts_n,<O>
																							//0C: ETN_LED_LINK,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//0E: I2C1_SCL_SRC2,<I/O>
																							//0F: I2C0_SCL_SRC10,<I/O>
																							//10: I2C2_SCL_SRC11,<I/O>
																							//11: VFD_CS_N,<OD>
																							//1F: ISO_MIS_GPIO_bit30,<I/O>
																							//def: ISO_MIS_GPIO_bit30,<I/O>
#define RTD298X_BGA459_PIN_E6_UP							(1&0x01)// 0xB8060238[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E6_PD							(0&0x01)// 0xB8060238[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E6_DS							(0&0x01)// 0xB8060238[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E6_SR							(0&0x01)// 0xB8060238[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_31_io 190
#define RTD298X_BGA459_PIN_F6								(0x1F&0x1F)//0xB8060238[22:18];
																							//02: ST_dbg_bit21,<I/O>
																							//03: TCON_bit18,<O>
																							//08: SC1_RST,<OD>
																							//09: uart0_cts_n_src2,<I>
																							//0A: uart2_cts_n_src0,<I>
																							//0B: SPDIF_OUT,<O>
																							//0C: ETN_LED_TXRX,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//0E: I2C1_SDA_SRC2,<I/O>
																							//0F: I2C0_SDA_SRC10,<I/O>
																							//10: I2C2_SDA_SRC11,<I/O>
																							//11: VFD_CLK,<OD>
																							//1F: ISO_MIS_GPIO_bit31,<I/O>
																							//def: ISO_MIS_GPIO_bit31,<I/O>
#define RTD298X_BGA459_PIN_F6_UP							(1&0x01)// 0xB8060238[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F6_PD							(0&0x01)// 0xB8060238[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F6_DS							(0&0x01)// 0xB8060238[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F6_SR							(0&0x01)// 0xB8060238[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_32_io 191
#define RTD298X_BGA459_PIN_G6								(0x1F&0x1F)//0xB8060238[31:27];
																							//02: ST_dbg_bit22,<I/O>
																							//03: TCON_bit17,<O>
																							//08: irrX_src5,<I>
																							//09: uart2_rXdi_src2,<I>
																							//0A: SPDIF_OUT,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//10: P_MDIO_SRC0,<I/O>,<HS>
																							//11: VFD_CS_N,<OD>
																							//1F: ISO_MIS_GPIO_bit32,<I/O>
																							//def: ISO_MIS_GPIO_bit32,<I/O>
#define RTD298X_BGA459_PIN_G6_UP							(1&0x01)// 0xB8060238[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G6_PD							(0&0x01)// 0xB8060238[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G6_DS							(0&0x01)// 0xB8060238[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G6_SR							(0&0x01)// 0xB8060238[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_33_io 192
#define RTD298X_BGA459_PIN_H6								(0x1F&0x1F)//0xB8060234[13:9];
																							//02: ST_dbg_bit23,<I/O>
																							//03: TCON_bit16,<O>
																							//08: IRTX,<O>
																							//09: uart2_tXdo,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//10: P_MDC,<O>,<HS>
																							//1F: ISO_MIS_GPIO_bit33,<I/O>
																							//def: ISO_MIS_GPIO_bit33,<I/O>
#define RTD298X_BGA459_PIN_H6_UP							(1&0x01)// 0xB8060234[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_H6_PD							(0&0x01)// 0xB8060234[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_H6_DS							(0&0x01)// 0xB8060234[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_H6_SR							(0&0x01)// 0xB8060234[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_34_io 193
#define RTD298X_BGA459_PIN_J6								(0x1F&0x1F)//0xB8060234[22:18];
																							//02: ST_dbg_bit24,<I/O>
																							//03: TCON_bit7,<O>
																							//04: TCON_bit17,<O>
																							//09: ETN_LED_LINK,<O>
																							//0B: SPDIF_OUT,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//10: P_RXER_SRC0,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit34,<I/O>
																							//def: ISO_MIS_GPIO_bit34,<I/O>
#define RTD298X_BGA459_PIN_J6_UP							(1&0x01)// 0xB8060234[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_J6_PD							(0&0x01)// 0xB8060234[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_J6_DS							(0&0x01)// 0xB8060234[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_J6_SR							(0&0x01)// 0xB8060234[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_35_io 194
#define RTD298X_BGA459_PIN_E7								(0x1F&0x1F)//0xB8060234[31:27];
																							//01: TCON_bit12,<O>
																							//02: ST_dbg_bit32,<I/O>
																							//03: PCMCIA_INPACK1_N_SRC1,<I>
																							//04: TCON_bit2,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//06: ld_spi0_p1_cs1,<O>
																							//08: IRTX,<O>
																							//09: ETN_LED_LINK,<O>
																							//0C: iso_misc_uni_pwm1,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//11: VFD_CS_N,<OD>
																							//15: GSPI_CS_N_SRC3,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit35,<I/O>
																							//def: ISO_MIS_GPIO_bit35,<I/O>
#define RTD298X_BGA459_PIN_E7_UP							(1&0x01)// 0xB8060234[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_E7_PD							(0&0x01)// 0xB8060234[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_E7_DS							(0&0x01)// 0xB8060234[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_E7_SR							(0&0x01)// 0xB8060234[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_36_io 195
#define RTD298X_BGA459_PIN_D8								(0x01&0x1F)//0xB8060230[13:9];
																							//01: TCON_bit13,<O>
																							//02: ST_dbg_bit33,<I/O>
																							//04: TCON_bit3,<O>
																							//05: ld_spi1_p2_sck_src3,<I/O>
																							//06: ld_spi0_p2_sck_src3,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: iso_misc_uni_pwm0,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//11: VFD_D_SRC3,<I/O>
																							//15: GSPI_SCLK_SRC3,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit36,<I/O>
																							//def: ISO_MIS_GPIO_bit36,<I/O>
#define RTD298X_BGA459_PIN_D8_UP							(1&0x01)// 0xB8060230[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_D8_PD							(0&0x01)// 0xB8060230[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_D8_DS							(0&0x01)// 0xB8060230[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_D8_SR							(0&0x01)// 0xB8060230[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_37_io 196
#define RTD298X_BGA459_PIN_F8								(0x1F&0x1F)//0xB8060230[22:18];
																							//01: TCON_bit14,<O>
																							//02: ST_dbg_bit34,<I/O>
																							//03: PCMCIA_IREQ1_N_SRC1,<I>
																							//04: TCON_bit4,<O>
																							//05: ld_spi1_p3_sdo_SRC3,<I/O>
																							//06: ld_spi0_p3_sdo_SRC3,<I/O>
																							//0D: iso_misc_pwm_1,<OD>
																							//11: VFD_CLK,<OD>
																							//15: GSPI_DO_SRC3,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit37,<I/O>
																							//def: ISO_MIS_GPIO_bit37,<I/O>
#define RTD298X_BGA459_PIN_F8_UP							(1&0x01)// 0xB8060230[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F8_PD							(0&0x01)// 0xB8060230[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F8_DS							(0&0x01)// 0xB8060230[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F8_SR							(0&0x01)// 0xB8060230[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_38_io 197
#define RTD298X_BGA459_PIN_F7								(0x1F&0x1F)//0xB8060230[31:27];
																							//01: TCON_bit15,<O>
																							//02: ST_dbg_bit35,<I/O>
																							//04: TCON_bit5,<O>
																							//05: ld_spi1_p4_sdi_SRC3,<I>
																							//06: ld_spi0_p4_sdi_SRC1,<I>
																							//08: IRTX,<O>
																							//0D: iso_misc_pwm_0,<OD>
																							//14: EPI_LOCK_src3,<I>
																							//15: GSPI_DI_SRC3,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit38,<I/O>
																							//def: ISO_MIS_GPIO_bit38,<I/O>
#define RTD298X_BGA459_PIN_F7_UP							(1&0x01)// 0xB8060230[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_F7_PD							(0&0x01)// 0xB8060230[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_F7_DS							(0&0x01)// 0xB8060230[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_F7_SR							(0&0x01)// 0xB8060230[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_39_io 198
#define RTD298X_BGA459_PIN_B8								(0x1F&0x1F)//0xB806022C[13:9];
																							//01: TCON_bit16,<O>
																							//02: ST_dbg_bit36,<I/O>
																							//03: PCMCIA_WAIT1_N_SRC1,<I>
																							//04: TCON_bit6,<O>
																							//05: ld_spi1_p5_v_sync,<O>
																							//06: ld_spi0_p5_v_sync,<O>
																							//09: uart0_rXdi_src6,<I>
																							//0A: ETN_LED_LINK,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//1F: ISO_MIS_GPIO_bit39,<I/O>
																							//def: ISO_MIS_GPIO_bit39,<I/O>
#define RTD298X_BGA459_PIN_B8_UP							(1&0x01)// 0xB806022C[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_B8_PD							(0&0x01)// 0xB806022C[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_B8_DS							(0&0x01)// 0xB806022C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_B8_SR							(0&0x01)// 0xB806022C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_40_io 199
#define RTD298X_BGA459_PIN_A8								(0x1F&0x1F)//0xB806022C[22:18];
																							//01: TCON_bit17,<O>
																							//02: ST_dbg_bit37,<I/O>
																							//03: PCMCIA_CE2_N,<O>
																							//04: TCON_bit7,<O>
																							//05: ld_spi1_p6_h_sync,<O>
																							//06: ld_spi0_p6_h_sync,<O>
																							//09: uart0_tXdo,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0B: SPDIF_OUT,<O>
																							//0C: misc_uni_pwm7,<O>
																							//0D: misc_pwm_4,<OD>
																							//11: VFD_CLK,<OD>
																							//1F: ISO_MIS_GPIO_bit40,<I/O>
																							//def: ISO_MIS_GPIO_bit40,<I/O>
#define RTD298X_BGA459_PIN_A8_UP							(1&0x01)// 0xB806022C[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_A8_PD							(0&0x01)// 0xB806022C[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_A8_DS							(0&0x01)// 0xB806022C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_A8_SR							(0&0x01)// 0xB806022C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_41_io 200
#define RTD298X_BGA459_PIN_J5								(0x1F&0x1F)//0xB806022C[31:27];
																							//02: ST_dbg_bit25,<I/O>
																							//03: TCON_bit8,<O>
																							//04: TCON_bit18,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//10: P_CRS_SRC0,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit41,<I/O>
																							//def: ISO_MIS_GPIO_bit41,<I/O>
#define RTD298X_BGA459_PIN_J5_UP							(1&0x01)// 0xB806022C[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_J5_PD							(0&0x01)// 0xB806022C[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_J5_DS							(0&0x01)// 0xB806022C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_J5_SR							(0&0x01)// 0xB806022C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_42_io 201
#define RTD298X_BGA459_PIN_J4								(0x1F&0x1F)//0xB8060228[13:9];
																							//01: EMMC_CMD_SRC2,<I/O>,<HS>
																							//02: ST_dbg_bit26,<I/O>
																							//03: TCON_bit9,<O>
																							//04: TCON_bit19,<O>
																							//0C: iso_misc_uni_pwm0,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//10: P_RXDV_SRC0,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit42,<I/O>
																							//def: ISO_MIS_GPIO_bit42,<I/O>
#define RTD298X_BGA459_PIN_J4_UP							(1&0x01)// 0xB8060228[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_J4_PD							(0&0x01)// 0xB8060228[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_J4_DS							(0&0x01)// 0xB8060228[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_J4_SR							(0&0x01)// 0xB8060228[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_43_io 202
#define RTD298X_BGA459_PIN_K6								(0x1F&0x1F)//0xB8060228[22:18];
																							//01: EMMC_CLK,<O>,<HS>
																							//02: ST_dbg_bit27,<I/O>
																							//03: TCON_bit15,<O>
																							//10: P_RXD0_SRC0,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit43,<I/O>
																							//def: ISO_MIS_GPIO_bit43,<I/O>
#define RTD298X_BGA459_PIN_K6_UP							(1&0x01)// 0xB8060228[17]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_K6_PD							(0&0x01)// 0xB8060228[16]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_K6_DS							(0&0x01)// 0xB8060228[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_K6_SR							(0&0x01)// 0xB8060228[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_44_io 203
#define RTD298X_BGA459_PIN_K5								(0x1F&0x1F)//0xB8060228[31:27];
																							//02: ST_dbg_bit28,<I/O>
																							//03: TCON_bit14,<O>
																							//10: P_RXD1_SRC0,<I>,<HS>
																							//1F: ISO_MIS_GPIO_bit44,<I/O>
																							//def: ISO_MIS_GPIO_bit44,<I/O>
#define RTD298X_BGA459_PIN_K5_UP							(1&0x01)// 0xB8060228[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_K5_PD							(0&0x01)// 0xB8060228[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_K5_DS							(0&0x01)// 0xB8060228[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_K5_SR							(0&0x01)// 0xB8060228[23]: Slew rate 0:fast 1:slow


// PAD_NAME: PLT_P0_TXHN 204
#define RTD298X_BGA459_PIN_F25								(0x13&0x1F)//0xB80008B8[26:22];
																							//00: LVDS_A_HN,<AO>
																							//01: PCMCIA_ADDR_bit11,<OD>,<HS>
																							//03: TCON_bit12,<O>
																							//0C: misc_uni_pwm1,<O>
																							//0D: misc_pwm_1_src0,<I/O>
																							//0F: TCON_bit21,<O>
																							//12: I2S_out_WCLK,<O>
																							//13: I2S_out_MCLK,<O>
																							//1F: MIS_GPIO_bit140,<I/O>
																							//def: MIS_GPIO_bit140,<I/O>


// PAD_NAME: SCART_FSW_0_APAD 205
#define RTD298X_BGA459_PIN_Y9								(0x0D&0x1F)//0xB80008EC[31:27];
																							//03: TCON_bit14,<O>
																							//0C: LSADC3,<AI>
																							//0D: SCART_FSW_0,<AI>
																							//1F: MIS_GPIO_bit127,<I/O>
																							//def: SCART_FSW_0,<AI>


// PAD_NAME: VDAC_VDBSO_APAD 206
#define RTD298X_BGA459_PIN_AA4								(0x1F&0xC)//0xB80008EC[26:22];
																							//03: TCON_bit15,<O>
																							//0C: VDBS_OUT,<AO>
																							//1F: MIS_GPIO_bit128,<I/O>
																							//def: VDBS_OUT,<AO>
#define RTD298X_BGA459_PIN_AA4_UP							(1&0x01)// 0xB80008EC[21]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA4_PD							(0&0x01)// 0xB80008EC[20]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_AA4_DS							(0&0x01)// 0xB80008EC[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_AA4_SR							(0&0x01)// 0xB80008EC[18]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_10P_APAD 207
#define RTD298X_BGA459_PIN_U3								(0x0C&0x1F)//0xB80008E4[11:7];
																							//03: TCON_bit12,<O>
																							//0C: VIN_10P,<AI>
																							//1F: MIS_GPIO_bit125,<I/O>
																							//def: VIN_10P,<AI>
#define RTD298X_BGA459_PIN_U3_UP							(1&0x01)// 0xB80008E4[6]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_U3_PD							(0&0x01)// 0xB80008E4[5]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_U3_DS							(0&0x01)// 0xB80008E4[4]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_U3_SR							(0&0x01)// 0xB80008E4[3]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_6P_APAD 208
#define RTD298X_BGA459_PIN_R3								(0x0C&0x1F)//0xB80008E0[31:27];
																							//03: TCON_bit4,<O>
																							//0C: VIN_6P,<AI>
																							//1F: MIS_GPIO_bit117,<I/O>
																							//def: VIN_6P,<AI>
#define RTD298X_BGA459_PIN_R3_UP							(1&0x01)// 0xB80008E0[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_R3_PD							(0&0x01)// 0xB80008E0[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_R3_DS							(0&0x01)// 0xB80008E0[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_R3_SR							(0&0x01)// 0xB80008E0[23]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_7P_APAD 209
#define RTD298X_BGA459_PIN_T3								(0x0C&0x1F)//0xB80008E0[21:17];
																							//03: TCON_bit6,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: VIN_7P,<AI>
																							//10: I2C2_SCL_SRC0,<I/O>
																							//1F: MIS_GPIO_bit119,<I/O>
																							//def: VIN_7P,<AI>
#define RTD298X_BGA459_PIN_T3_UP							(1&0x01)// 0xB80008E0[16]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_T3_PD							(0&0x01)// 0xB80008E0[15]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_T3_DS							(0&0x01)// 0xB80008E0[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_T3_SR							(0&0x01)// 0xB80008E0[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_8P_APAD 210
#define RTD298X_BGA459_PIN_U2								(0x0C&0x1F)//0xB80008E0[16:12];
																							//03: TCON_bit7,<O>
																							//0C: VIN_8P,<AI>
																							//10: I2C2_SDA_SRC0,<I/O>
																							//1F: MIS_GPIO_bit120,<I/O>
																							//def: VIN_8P,<AI>
#define RTD298X_BGA459_PIN_U2_UP							(1&0x01)// 0xB80008E0[11]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_U2_PD							(0&0x01)// 0xB80008E0[10]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_U2_DS							(0&0x01)// 0xB80008E0[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_U2_SR							(0&0x01)// 0xB80008E0[8]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_9P_APAD 211
#define RTD298X_BGA459_PIN_W2								(0x0C&0x1F)//0xB80008E4[31:27];
																							//03: TCON_bit8,<O>
																							//09: ETN_LED_LINK,<O>
																							//0C: VIN_9P,<AI>
																							//0F: I2C0_SDA_SRC12,<I/O>
																							//1F: MIS_GPIO_bit121,<I/O>
																							//def: VIN_9P,<AI>
#define RTD298X_BGA459_PIN_W2_UP							(1&0x01)// 0xB80008E4[26]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_W2_PD							(0&0x01)// 0xB80008E4[25]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_W2_DS							(0&0x01)// 0xB80008E4[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_W2_SR							(0&0x01)// 0xB80008E4[23]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_A2N_APAD 212
#define RTD298X_BGA459_PIN_V1								(0x0C&0x1F)//0xB80008E4[16:12];
																							//03: TCON_bit11,<O>
																							//0C: VIN_A2N,<AI>
																							//1F: MIS_GPIO_bit124,<I/O>
																							//def: VIN_A2N,<AI>
#define RTD298X_BGA459_PIN_V1_UP							(1&0x01)// 0xB80008E4[11]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_V1_PD							(0&0x01)// 0xB80008E4[10]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_V1_DS							(0&0x01)// 0xB80008E4[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_V1_SR							(0&0x01)// 0xB80008E4[8]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_Y1N_APAD 213
#define RTD298X_BGA459_PIN_T2								(0x0C&0x1F)//0xB80008E0[26:22];
																							//03: TCON_bit5,<O>
																							//09: ETN_LED_LINK,<O>
																							//0C: VIN_Y1N,<AI>
																							//1F: MIS_GPIO_bit118,<I/O>
																							//def: VIN_Y1N,<AI>
#define RTD298X_BGA459_PIN_T2_UP							(1&0x01)// 0xB80008E0[21]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_T2_PD							(0&0x01)// 0xB80008E0[20]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_T2_DS							(0&0x01)// 0xB80008E0[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_T2_SR							(0&0x01)// 0xB80008E0[18]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_85_io:2
#define RTD298X_BGA459_PIN_G22								(0x1F&0x1F)//0xB8000850[13:9];
																							//02: EMMC_CLK,<O>,<HS>
																							//03: TCON_bit11,<O>
																							//04: ld_spi0_p5_v_sync,<O>
																							//05: ld_spi1_p1_cs1,<O>
																							//09: IRTX,<O>
																							//1F: MIS_GPIO_bit85,<I/O>
																							//def: MIS_GPIO_bit85,<I/O>
#define RTD298X_BGA459_PIN_G22_UP							(1&0x01)// 0xB8000850[8]: Pull Up 0:disable 1:enable
#define RTD298X_BGA459_PIN_G22_PD							(0&0x01)// 0xB8000850[7]: Pull Down 0:disable 1:enable
#define RTD298X_BGA459_PIN_G22_DS							(0&0x01)// 0xB8000850[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_BGA459_PIN_G22_SR							(0&0x01)// 0xB8000850[5]: Slew rate 0:fast 1:slow




#define PIN_BL_ON_OFF 			RTD298X_BGA459_PIN_B9_ISO_GPO_10(1, 0)
#define PIN_BL_ADJ				RTD298X_BGA459_PIN_F24_PWM_3(1, 200, 255, 255)
#define PIN_LVDS_ON_OFF			RTD298X_BGA459_PIN_E25_GPO_82(0, 1)
	
	
//#define PIN_KEYPAD_MENU		RTD299X_BGA_PIN_E2_LSADC_CURRENT_0(19, 1)
//#define PIN_KEYPAD_SOURCE		RTD299X_BGA_PIN_E2_LSADC_CURRENT_0(14, 1)
////#define PIN_KEYPAD_RIGHT		RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(0, 10)
////#define PIN_KEYPAD_LEFT			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(58, 10)
////#define PIN_KEYPAD_UP			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(125, 10)
////#define PIN_KEYPAD_DOWN			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(192, 10)
////#define PIN_KEYPAD_PWR			RTD298X_QFP176_PIN_125_LSADC_VOLTAGE_1(0, 10)
	
	// HDMI 1 reletive board information
#define PIN_HDMI1_HOTPLUG		RTD298X_BGA459_PIN_G4_ISO_GPO_22(0, 0)
#define HDMI1_DDC				PCB_DDC_0
#define HDMI1_PHY_PORT			HDMI_PHY_PORT0
#define HDMI1_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI1_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI1_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI1_MUX_IC			HDMI_MUX_NOUSED
	
	// HDMI 2 reletive board information
#define PIN_HDMI2_HOTPLUG		RTD298X_BGA459_PIN_E4_ISO_GPO_19(0, 0)
#define HDMI2_DDC				PCB_DDC_1
#define HDMI2_PHY_PORT			HDMI_PHY_PORT1
#define HDMI2_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI2_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI2_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI2_MUX_IC			HDMI_MUX_NOUSED
	
	// HDMI 3 reletive board information
#define PIN_HDMI3_HOTPLUG		(0)
#define HDMI3_DDC				PCB_DDC_2
#define HDMI3_PHY_PORT			HDMI_PHY_PORT2
#define HDMI3_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI3_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI3_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI3_MUX_IC			HDMI_MUX_NOUSED
	
#define PIN_HDMI_MHL_SELECT		RTD298X_BGA459_PIN_F9_ISO_GPO_9(0, 1)
#define PIN_HDMI_CABLE_DETECT	RTD298X_BGA459_PIN_A7_ISO_GPI_3(0)
#define PIN_MHL_CABLE_DETECT	RTD298X_BGA459_PIN_B10_ISO_GPI_13(0)
	
	// VGA DDC
#define VGA_DDC					PCB_DDC_3
	
	// Tuner I2C
#define TUNER_I2C				PCB_I2C_1
	
//#define I2C_PORT_0                      PCB_HW_I2C(PCB_I2C_PHY_0, PCB_I2C_SUB_SRC_ANY)
	
//#define I2C_PORT_1                      PCB_HW_I2C(PCB_I2C_PHY_1, PCB_I2C_SUB_SRC_ANY)
	
//#define I2C_PORT_2                      PCB_HW_I2C(PCB_I2C_PHY_2, PCB_I2C_SUB_SRC_ANY)
	
	//I2C Port 3:GPIO I2C, SDA=GPIO 169, SCL=GPIO 168 for amp
//#define PIN_I2C3_SDA                   RTD299X_BGA_PIN_A5_GPO_127(0,0)
//#define PIN_I2C3_SCL                   RTD299X_BGA_PIN_D7_GPO_124(0,0)
//#define I2C_PORT_3                      PCB_GPIO_I2C(PIN_I2C3_SDA, PIN_I2C3_SCL)
	
	//I2C Port 4:GPIO I2C, SDA=GPIO 14, SCL=GPIO 13 for eeprom
//#define PIN_I2C4_SDA                  RTD299X_BGA_PIN_AH12_GPO_14(0, 0)
//#define PIN_I2C4_SCL                   RTD299X_BGA_PIN_AG11_GPO_13(0, 0)
//#define I2C_PORT_4                      PCB_GPIO_I2C(PIN_I2C4_SDA, PIN_I2C4_SCL)
	
	// Tuner 33V for specific Tuner
	//#define TUN33V_PWM
	
	
	// AMP
//#define AMP_DEVICE_ADDR			0x1a 	//0x34 //Tas5711L_ADDR
	//#define AMP_DEVICE_ADDR				0x1b	//0x36 //Tas5707L_ADDR
#define PIN_AMP_MUTE			RTD298X_BGA459_PIN_C8_ISO_GPO_11(0,0)   // 0: unmute  1: mute
//#define AMP_I2C					PCB_I2C_3
		//CLK	0x1800_0870[31:28],   5: 0xb800_08C0[23:20] = 0x8 / 0xb806_02A0[5:4] = 0x3
		//DATA 0x1800_0870[23:20],	 5: 0xb800_08C0[23:20] = 0x8 / 0xb806_02A0[5:4] = 0x3
	
	// EEP
	//#define EEP_DEVICE_ADDR				(0XA0 >> 1)
	//#define EEP_WP
	//#define EEP_I2C							PCB_I2C_1
		//the same with AMP for test use
	
	
	
	
	// MISC
//#define PIN_MISC_2D_3D_SELECT				RTD299X_BGA_PIN_Y6_GPO_136(0, 0)
#define PIN_FLASH_WP			RTD298X_BGA459_PIN_F22_GPO_84(0, 1)   //0: enable write protection  1: disable write protection 
	//#define MISC_951_RST
#define PIN_POWER_DETECT		RTD298X_BGA459_PIN_G22_GPI_85(0)	
#define POWER_EN				RTD298X_BGA459_PIN_E9_ISO_GPO_7(0, 1)
//#define PIN_PCMCIA_EN					RTD299X_BGA_PIN_AJ12_GPO_15(0,1)
	// USB hub Reset ?
	//#define HUB_RET
	
	// USB3.0 Power Switch Control ?
	//#define USB_PWR_CTL
	
	// USB3.0 Power Flag ?
	//#define USB_PWR_FLAG
	
	// USB Hub Power Flag
	//#define USB3_PWR_FLAG 				RTD2974_LFBGA_PIN_AA21_GPO_47(1, 1)
	//#define USB2_PWR_FLAG 				RTD2974_LFBGA_PIN_L1_GPO_114(1, 1)
	//#define USB1_PWR_FLAG 				RTD2974_LFBGA_PIN_K3_GPO_115(1, 1)
	
	//#define ANDROID_USB_PORT				0x312d322e32202020	//must 8-byte,	 USB PORT 1-2.2 for E83
#define ANDROID_USB_PORT				0x312d312020202020	//must 8-byte,   USB PORT 1-1 for E650S, RTK_DEMO
	
	// for Customer to load AV_PATH
#define AV1_VPATH   VIDEO_INPUT12
#define AV1_VGND	VIDEO_GNDA0
	
	//Millet3
#define MILLET3_DEVICE_ADDR			0x70
#define MILLET3_I2C						PCB_I2C_3
	
#if 0 // FIXME
	// for audio out
#define AUDIO_OUTPUT_AVOUT			RTD299X_BGA_PIN_xx_1_VOL()
#define AUDIO_OUTPUT_SPEAKER_OUT	RTD299X_BGA_PIN_xx_2_FIXVOL()
#define AUDIO_OUTPUT_HEADPHONE_OUT	RTD299X_BGA_PIN_xx_3_VOL()
#endif


//////////////////////////////////////////////////////////////////////////////
//
// 	Enumerate all PCB staff below !!!
//
//////////////////////////////////////////////////////////////////////////////
PCB_ENUM_START()

PCB_ENUM(PIN_BL_ON_OFF)
PCB_ENUM(PIN_BL_ADJ)
PCB_ENUM(PIN_LVDS_ON_OFF)
//PCB_ENUM(PIN_KEYPAD_RIGHT)
//PCB_ENUM(PIN_KEYPAD_LEFT)
//PCB_ENUM(PIN_KEYPAD_UP)
//PCB_ENUM(PIN_KEYPAD_DOWN)
//PCB_ENUM(PIN_KEYPAD_PWR)
PCB_ENUM(PIN_HDMI1_HOTPLUG)
PCB_ENUM(HDMI1_DDC)
PCB_ENUM(HDMI1_PHY_PORT)
PCB_ENUM(HDMI1_EDID_TYPE)
PCB_ENUM(HDMI1_HPD_TYPE)
PCB_ENUM(HDMI1_MUX_PORT)
PCB_ENUM(HDMI1_MUX_IC)
PCB_ENUM(PIN_HDMI2_HOTPLUG)
PCB_ENUM(HDMI2_DDC)
PCB_ENUM(HDMI2_PHY_PORT)
PCB_ENUM(HDMI2_EDID_TYPE)
PCB_ENUM(HDMI2_HPD_TYPE)
PCB_ENUM(HDMI2_MUX_PORT)
PCB_ENUM(HDMI2_MUX_IC)
PCB_ENUM(PIN_HDMI3_HOTPLUG)
PCB_ENUM(HDMI3_DDC)
PCB_ENUM(HDMI3_PHY_PORT)
PCB_ENUM(HDMI3_EDID_TYPE)
PCB_ENUM(HDMI3_HPD_TYPE)
PCB_ENUM(HDMI3_MUX_PORT)
PCB_ENUM(HDMI3_MUX_IC)

PCB_ENUM(PIN_HDMI_MHL_SELECT)
PCB_ENUM(PIN_HDMI_CABLE_DETECT)
PCB_ENUM(PIN_MHL_CABLE_DETECT)
PCB_ENUM(VGA_DDC)
PCB_ENUM(TUNER_I2C)
PCB_ENUM(PIN_AMP_MUTE)

PCB_ENUM(PIN_POWER_DETECT)
PCB_ENUM(POWER_EN)


PCB_ENUM_END()
