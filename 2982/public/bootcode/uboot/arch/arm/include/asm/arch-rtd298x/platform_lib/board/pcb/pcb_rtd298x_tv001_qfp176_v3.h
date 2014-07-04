#include <platform_lib/board/pcb_rtd298x_qfp176_v3_library.h>
#include "pcb_define.h"


// PAD_NAME: VDAC_IDACO_TV_APAD 0
#define RTD298X_QFP176_PIN_1								(0x1F&0x1F)//0xB80008EC[21:17];
																							//03: TCON_bit16,<O>
																							//0C: VDAC_OUT,<AO>
																							//1F: MIS_GPIO_bit129,<I/O>
																							//def: VDAC_OUT,<AO>
// PAD_NAME: BB_AI2L_APAD 1
#define RTD298X_QFP176_PIN_5								(0x0C&0x1F)//0xB80008F0[31:27];
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

// PAD_NAME: BB_AI2R_APAD 2
#define RTD298X_QFP176_PIN_6								(0x0C&0x1F)//0xB80008F0[26:22];
																							//08: uart1_rXdi_src5,<I>
																							//09: ETN_LED_TXRX,<O>
																							//0C: BB_AI2R,<AI>
																							//0D: misc_uni_pwm1,<O>
																							//0E: misc_pwm_5,<OD>
																							//11: P_RXDV_SRC4,<I>,<HS>
																							//1F: MIS_GPIO_bit131,<I/O>
																							//def: BB_AI2R,<AI>

// PAD_NAME: BB_AI3L_APAD 3
#define RTD298X_QFP176_PIN_7								(0x0C&0x1F)//0xB80008F0[21:17];
																							//0C: BB_AI3L,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_7,<OD>
																							//1F: MIS_GPIO_bit132,<I/O>
																							//def: BB_AI3L,<AI>

// PAD_NAME: BB_AI3R_APAD 4
#define RTD298X_QFP176_PIN_8								(0x0C&0x1F)//0xB80008F0[16:12];
																							//0A: SPDIF_OUT,<O>
																							//0C: BB_AI3R,<AI>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_6,<OD>
																							//1F: MIS_GPIO_bit133,<I/O>
																							//def: BB_AI3R,<AI>

// PAD_NAME: BB_AIO1L_APAD 5
#define RTD298X_QFP176_PIN_10								(0x0C&0x1F)//0xB80008F4[26:22];
																							//03: TCON_bit19,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: BB_AIO1L,<AO>
																							//0D: misc_uni_pwm1,<O>
																							//0E: misc_pwm_5,<OD>
																							//12: I2S_out_SCLK,<O>
																							//1F: MIS_GPIO_bit136,<I/O>
																							//def: BB_AIO1L,<AO>

// PAD_NAME: BB_AIO1R_APAD 6
#define RTD298X_QFP176_PIN_11								(0x0C&0x1F)//0xB80008F4[21:17];
																							//03: TCON_bit1,<O>
																							//0C: BB_AIO1R,<AO>
																							//12: I2S_out_WCLK,<O>
																							//1F: MIS_GPIO_bit137,<I/O>
																							//def: BB_AIO1R,<AO>

// PAD_NAME: BB_HPOL_APAD:2 7
#define RTD298X_QFP176_PIN_13								(0x0C&0x1F)//0xB80008F4[16:12];
																							//03: TCON_bit2,<O>
																							//0C: BB_HPOL,<AO>
																							//0D: misc_uni_pwm4,<O>
																							//0E: misc_pwm_4,<OD>
																							//1F: MIS_GPIO_bit138,<I/O>
																							//def: BB_HPOL,<AO>

// PAD_NAME: BB_HPOR_APAD:2 8
#define RTD298X_QFP176_PIN_14								(0x0C&0x1F)//0xB80008F4[11:7];
																							//03: TCON_bit3,<O>
																							//0C: BB_HPOR,<AO>
																							//1F: MIS_GPIO_bit139,<I/O>
																							//def: BB_HPOR,<AO>

// PAD_NAME: BB_DIO3_APAD 11
#define RTD298X_QFP176_PIN_15								(0x1F&0x1F)//0xB80008F8[21:17];
																							//03: TCON_bit6,<O>
																							//04: TCON_bit22,<O>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_7,<OD>
																							//1F: MIS_GPIO_bit196,<I/O>
																							//def: MIS_GPIO_bit196,<I/O>


// PAD_NAME: HSDP_2_APAD 98
#define RTD298X_QFP176_PIN_36								(0x1F&0x1F)//0xB80008F8[16:12];
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
#define RTD298X_QFP176_PIN_36_UP							(1&0x01)// 0xB80008F8[11]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_36_PD							(0&0x01)// 0xB80008F8[10]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_36_DS							(0&0x01)// 0xB80008F8[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_36_SR							(0&0x01)// 0xB80008F8[8]: Slew rate 0:fast 1:slow


// PAD_NAME: HSDM_2_APAD 97
#define RTD298X_QFP176_PIN_37								(0x1F&0x1F)//0xB80008F8[11:7];
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
#define RTD298X_QFP176_PIN_37_UP							(1&0x01)// 0xB80008F8[6]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_37_PD							(0&0x01)// 0xB80008F8[5]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_37_DS							(0&0x01)// 0xB80008F8[4]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_37_SR							(0&0x01)// 0xB80008F8[3]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_0_io 12
#define RTD298X_QFP176_PIN_38								(0x11&0x1F)//0xB8000800[31:27];
																							//11: ATV_RF_AGC,<OD>
																							//12: DEMOD_AGC_RF,<OD>
																							//13: ATV_IF_AGC,<OD>
																							//14: DEMOD_AGC_IF,<OD>
																							//17: test_en_bit0,<I/O>
																							//1F: MIS_GPIO_bit0,<I/O>
																							//def: MIS_GPIO_bit0,<I/O>
#define RTD298X_QFP176_PIN_38_UP							(1&0x01)// 0xB8000800[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_38_PD							(0&0x01)// 0xB8000800[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_38_DS							(0&0x01)// 0xB8000800[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_38_SR							(0&0x01)// 0xB8000800[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_1_io 13
#define RTD298X_QFP176_PIN_39								(0x12&0x1F)//0xB8000800[22:18];
																							//03: DEMOD_I2C_SCL_RELAY,<OD>
																							//11: I2C0_SCL_SRC7,<I/O>
																							//12: I2C1_SCL_SRC0,<I/O>
																							//16: TP0_Data_bit4_SRC2,<I>,<HS>
																							//17: test_en_bit1,<I/O>
																							//1F: MIS_GPIO_bit1,<I/O>
																							//def: MIS_GPIO_bit1,<I/O>
#define RTD298X_QFP176_PIN_39_UP							(1&0x01)// 0xB8000800[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_39_PD							(0&0x01)// 0xB8000800[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_39_DS							(0&0x01)// 0xB8000800[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_39_SR							(0&0x01)// 0xB8000800[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_2_io 14
#define RTD298X_QFP176_PIN_40								(0x12&0x1F)//0xB8000804[31:27];
																							//03: DEMOD_I2C_SDA_RELAY,<I/O>
																							//11: I2C0_SDA_SRC7,<I/O>
																							//12: I2C1_SDA_SRC0,<I/O>
																							//16: TP0_Data_bit3_SRC2,<I>,<HS>
																							//17: test_en_bit2,<I/O>
																							//1F: MIS_GPIO_bit2,<I/O>
																							//def: MIS_GPIO_bit2,<I/O>
#define RTD298X_QFP176_PIN_40_UP							(1&0x01)// 0xB8000804[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_40_PD							(0&0x01)// 0xB8000804[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_40_DS							(0&0x01)// 0xB8000804[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_40_SR							(0&0x01)// 0xB8000804[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_16_io 15
#define RTD298X_QFP176_PIN_42								(0x09&0x1F)//0xB8000814[13:9];
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
																							//12: I2S_out_Data1,<O>
																							//13: I2S_out_MCLK,<O>
																							//15: VBY1_HTPD_src3,<I>
																							//16: TPO_Data_bit3_pad,<O>,<HS>
																							//17: test_en_bit3,<I/O>
																							//1F: MIS_GPIO_bit16,<I/O>
																							//def: MIS_GPIO_bit16,<I/O>
#define RTD298X_QFP176_PIN_42_UP							(1&0x01)// 0xB8000814[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_42_PD							(0&0x01)// 0xB8000814[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_42_DS							(0&0x01)// 0xB8000814[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_42_SR							(0&0x01)// 0xB8000814[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_17_io 16
#define RTD298X_QFP176_PIN_43								(0x01&0x1F)//0xB8000818[31:27];
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
#define RTD298X_QFP176_PIN_43_UP							(1&0x01)// 0xB8000818[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_43_PD							(0&0x01)// 0xB8000818[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_43_DS							(0&0x01)// 0xB8000818[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_43_SR							(0&0x01)// 0xB8000818[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_18_io 17
#define RTD298X_QFP176_PIN_44								(0x01&0x1F)//0xB8000818[22:18];
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
#define RTD298X_QFP176_PIN_44_UP							(1&0x01)// 0xB8000818[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_44_PD							(0&0x01)// 0xB8000818[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_44_DS							(0&0x01)// 0xB8000818[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_44_SR							(0&0x01)// 0xB8000818[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_19_io 18
#define RTD298X_QFP176_PIN_45								(0x09&0x1F)//0xB8000818[13:9];
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
#define RTD298X_QFP176_PIN_45_UP							(1&0x01)// 0xB8000818[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_45_PD							(0&0x01)// 0xB8000818[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_45_DS							(0&0x01)// 0xB8000818[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_45_SR							(0&0x01)// 0xB8000818[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_39_io 19
#define RTD298X_QFP176_PIN_46								(0x01&0x1F)//0xB8000830[31:27];
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
#define RTD298X_QFP176_PIN_46_UP							(1&0x01)// 0xB8000830[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_46_PD							(0&0x01)// 0xB8000830[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_46_DS							(0&0x01)// 0xB8000830[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_46_SR							(0&0x01)// 0xB8000830[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_40_io 20
#define RTD298X_QFP176_PIN_47								(0x01&0x1F)//0xB8000830[22:18];
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
																							//15: GSPI_DI_SRC0,<I/O>,<HS>
																							//17: test_en_bit8,<I/O>
																							//1F: MIS_GPIO_bit40,<I/O>
																							//def: MIS_GPIO_bit40,<I/O>
#define RTD298X_QFP176_PIN_47_UP							(1&0x01)// 0xB8000830[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_47_PD							(0&0x01)// 0xB8000830[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_47_DS							(0&0x01)// 0xB8000830[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_47_SR							(0&0x01)// 0xB8000830[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_41_io 21
#define RTD298X_QFP176_PIN_48								(0x1F&0x1F)//0xB8000830[13:9];
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
#define RTD298X_QFP176_PIN_48_UP							(1&0x01)// 0xB8000830[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_48_PD							(0&0x01)// 0xB8000830[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_48_DS							(0&0x01)// 0xB8000830[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_48_SR							(0&0x01)// 0xB8000830[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_42_io 22
#define RTD298X_QFP176_PIN_49								(0x01&0x1F)//0xB8000834[31:27];
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
																							//def: MIS_GPIO_bit42,
#define RTD298X_QFP176_PIN_49_UP							(1&0x01)// 0xB8000834[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_49_PD							(0&0x01)// 0xB8000834[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_49_DS							(0&0x01)// 0xB8000834[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_49_SR							(0&0x01)// 0xB8000834[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_35_io 23
#define RTD298X_QFP176_PIN_53								(0x1F&0x1F)//0xB8000828[13:9];
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
#define RTD298X_QFP176_PIN_53_UP							(1&0x01)// 0xB8000828[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_53_PD							(0&0x01)// 0xB8000828[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_53_DS							(0&0x01)// 0xB8000828[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_53_SR							(0&0x01)// 0xB8000828[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_44_io 24
#define RTD298X_QFP176_PIN_54								(0x02&0x1F)//0xB8000834[13:9];
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
#define RTD298X_QFP176_PIN_54_UP							(1&0x01)// 0xB8000834[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_54_PD							(0&0x01)// 0xB8000834[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_54_DS							(0&0x01)// 0xB8000834[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_54_SR							(0&0x01)// 0xB8000834[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_45_io 25
#define RTD298X_QFP176_PIN_55								(0x02&0x1F)//0xB8000838[31:27];
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
#define RTD298X_QFP176_PIN_55_UP							(1&0x01)// 0xB8000838[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_55_PD							(0&0x01)// 0xB8000838[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_55_DS							(0&0x01)// 0xB8000838[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_55_SR							(0&0x01)// 0xB8000838[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_46_io 26
#define RTD298X_QFP176_PIN_56								(0x02&0x1F)//0xB8000838[22:18];
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
																							//def: MIS_GPIO_
#define RTD298X_QFP176_PIN_56_UP							(1&0x01)// 0xB8000838[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_56_PD							(0&0x01)// 0xB8000838[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_56_DS							(0&0x01)// 0xB8000838[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_56_SR							(0&0x01)// 0xB8000838[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_47_io 27
#define RTD298X_QFP176_PIN_57								(0x02&0x1F)//0xB8000838[13:9];
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
#define RTD298X_QFP176_PIN_57_UP							(1&0x01)// 0xB8000838[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_57_PD							(0&0x01)// 0xB8000838[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_57_DS							(0&0x01)// 0xB8000838[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_57_SR							(0&0x01)// 0xB8000838[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_48_io 28
#define RTD298X_QFP176_PIN_58								(0x02&0x1F)//0xB800083C[31:27];
																							//00: nf_tmX_bit4,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit5,<OD>,<HS>
																							//02: EMMC_Data_bit4_SRC0,<I/O>,<HS>
																							//03: TCON_bit7,<O>
																							//0D: misc_pwm_4,<OD>
																							//13: I2S_out_Data1,<O>
																							//17: test_en_bit16,<I/O>
																							//1F: MIS_GPIO_bit48,<I/O>
																							//def: MIS_GPIO_bit48,<I/O>
#define RTD298X_QFP176_PIN_58_UP							(1&0x01)// 0xB800083C[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_58_PD							(0&0x01)// 0xB800083C[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_58_DS							(0&0x01)// 0xB800083C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_58_SR							(0&0x01)// 0xB800083C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_49_io 29
#define RTD298X_QFP176_PIN_59								(0x02&0x1F)//0xB800083C[22:18];
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
																							//1F: MIS_GPIO_bi
#define RTD298X_QFP176_PIN_59_UP							(1&0x01)// 0xB800083C[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_59_PD							(0&0x01)// 0xB800083C[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_59_DS							(0&0x01)// 0xB800083C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_59_SR							(0&0x01)// 0xB800083C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_50_io 30
#define RTD298X_QFP176_PIN_60								(0x02&0x1F)//0xB800083C[13:9];
																							//00: nf_tmX_bit6,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit4,<OD>,<HS>
																							//02: EMMC_Data_bit6_SRC0,<I/O>,<HS>
																							//03: TCON_bit13,<O>
																							//04: ld_spi0_p2_sck_src6,<I/O>
																							//05: ld_spi1_p2_sck_src6,<I/O>
																							//09: ETN_LED_LINK,<O>
																							//0D: misc_pwm_6,<OD>
																							//13: I2S_out_WCLK,<O>
																							//17: test_en_bit18,<I/
#define RTD298X_QFP176_PIN_60_UP							(1&0x01)// 0xB800083C[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_60_PD							(0&0x01)// 0xB800083C[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_60_DS							(0&0x01)// 0xB800083C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_60_SR							(0&0x01)// 0xB800083C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_51_io 31
#define RTD298X_QFP176_PIN_61								(0x02&0x1F)//0xB8000840[31:27];
																							//00: nf_tmX_bit7,<I/O>,<HS>
																							//01: PCMCIA_ADDR_bit2,<OD>,<HS>
																							//02: EMMC_Data_bit7_SRC0,<I/O>,<HS>
																							//03: TCON_bit18,<O>
																							//04: ld_spi0_p3_sdo_SRC6,<I/O>
																							//05: ld_spi1_p3_sdo_SRC6,<I/O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: misc_pwm_7,<OD>
																							//13: I2S_out_SCLK,<O>
																							//17: test_en_bit19,<I/
#define RTD298X_QFP176_PIN_61_UP							(1&0x01)// 0xB8000840[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_61_PD							(0&0x01)// 0xB8000840[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_61_DS							(0&0x01)// 0xB8000840[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_61_SR							(0&0x01)// 0xB8000840[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_52_io 32
#define RTD298X_QFP176_PIN_62								(0x1F&0x1F)//0xB8000840[22:18];
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
#define RTD298X_QFP176_PIN_62_UP							(1&0x01)// 0xB8000840[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_62_PD							(0&0x01)// 0xB8000840[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_62_DS							(0&0x01)// 0xB8000840[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_62_SR							(0&0x01)// 0xB8000840[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_56_io 33
#define RTD298X_QFP176_PIN_63								(0x02&0x1F)//0xB8000844[13:9];
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
#define RTD298X_QFP176_PIN_63_UP							(1&0x01)// 0xB8000844[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_63_PD							(0&0x01)// 0xB8000844[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_63_DS							(0&0x01)// 0xB8000844[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_63_SR							(0&0x01)// 0xB8000844[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_53_io 34
#define RTD298X_QFP176_PIN_64								(0x02&0x1F)//0xB8000840[13:9];
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
#define RTD298X_QFP176_PIN_64_UP							(1&0x01)// 0xB8000840[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_64_PD							(0&0x01)// 0xB8000840[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_64_DS							(0&0x01)// 0xB8000840[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_64_SR							(0&0x01)// 0xB8000840[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_gpio_54_io 35
#define RTD298X_QFP176_PIN_65								(0x02&0x1F)//0xB8000844[31:27];
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
#define RTD298X_QFP176_PIN_65_UP							(1&0x01)// 0xB8000844[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_65_PD							(0&0x01)// 0xB8000844[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_65_DS							(0&0x01)// 0xB8000844[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_65_SR							(0&0x01)// 0xB8000844[23]: Slew rate 0:fast 1:slow


// TODO: Fix Me
// PAD_NAME: PLT_P0_TXHP 36
#define RTD298X_QFP176_PIN_74								(0x0D&0x1F)//0xB80008B8[31:27];
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


// PAD_NAME: PLT_P0_TXGP 37
#define RTD298X_QFP176_PIN_75								(0x0A&0x1F)//0xB80008B8[21:17];
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

// PAD_NAME: PLT_P0_TXGN 38
#define RTD298X_QFP176_PIN_76								(0x1F&0x1F)//0xB80008B8[16:12];
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

// PAD_NAME: PLT_P0_TXFP 39
#define RTD298X_QFP176_PIN_77								(0x00&0x1F)//0xB80008B8[11:7];
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


// PAD_NAME: PLT_P0_TXFN 40
#define RTD298X_QFP176_PIN_78								(0x00&0x1F)//0xB80008B8[6:2];
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


// PAD_NAME: PLT_P0_TXEP 41
#define RTD298X_QFP176_PIN_79								(0x00&0x1F)//0xB80008BC[31:27];
																							//00: LVDS_A_EP,<AO>
																							//02: TTL_bout_bit5,<O>,<HS>
																							//03: TCON_bit4,<O>
																							//10: p_hif_clk_en,<I>,<HS>
																							//15: VBY1_HTPD_src1,<I>
																							//17: test_en_bit32,<I/O>
																							//1F: MIS_GPIO_bit59,<I/O>
																							//def: MIS_GPIO_bit59,<I/O>


// PAD_NAME: PLT_P0_TXEN 42
#define RTD298X_QFP176_PIN_80								(0x00&0x1F)//0xB80008BC[26:22];
																							//00: LVDS_A_EN,<AO>
																							//02: TTL_bout_bit4,<O>,<HS>
																							//03: TCON_bit5,<O>
																							//10: P_HIF_RDY,<O>
																							//15: VBY1_LOCK_src1,<I>
																							//17: test_en_bit33,<I/O>
																							//1F: MIS_GPIO_bit60,<I/O>
																							//def: MIS_GPIO_bit60,<I/O>


// PAD_NAME: PLT_P0_TXDP 43
#define RTD298X_QFP176_PIN_81								(0x00&0x1F)//0xB80008BC[21:17];
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


// PAD_NAME: PLT_P0_TXDN 44
#define RTD298X_QFP176_PIN_82								(0x00&0x1F)//0xB80008BC[16:12];
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


// PAD_NAME: PLT_P0_TXCP 45
#define RTD298X_QFP176_PIN_83								(0x00&0x1F)//0xB80008BC[11:7];
																							//00: LVDS_A_CP,<AO>
																							//02: TTL_bout_bit1,<O>,<HS>
																							//03: TCON_bit8,<O>
																							//10: P_HIF_Data_bit2,<I/O>
																							//1F: MIS_GPIO_bit63,<I/O>
																							//def: MIS_GPIO_bit63,<I/O>


// PAD_NAME: PLT_P0_TXCN 46
#define RTD298X_QFP176_PIN_84								(0x00&0x1F)//0xB80008BC[6:2];
																							//00: LVDS_A_CN,<AO>
																							//02: TTL_bout_bit0,<O>,<HS>
																							//03: TCON_bit9,<O>
																							//10: P_HIF_Data_bit3,<I/O>
																							//1F: MIS_GPIO_bit64,<I/O>
																							//def: MIS_GPIO_bit64,<I/O>


// PAD_NAME: PLT_P0_TXBP 47
#define RTD298X_QFP176_PIN_85								(0x00&0x1F)//0xB80008C0[31:27];
																							//00: LVDS_A_BP,<AO>
																							//02: TTL_gout_bit5,<O>,<HS>
																							//03: TCON_bit10,<O>
																							//10: P_HIF_Data_bit4,<I/O>
																							//15: VBY1_HTPD_src0,<I>
																							//1F: MIS_GPIO_bit65,<I/O>
																							//def: MIS_GPIO_bit65,<I/O>


// PAD_NAME: PLT_P0_TXBN 48
#define RTD298X_QFP176_PIN_86								(0x00&0x1F)//0xB80008C0[26:22];
																							//00: LVDS_A_BN,<AO>
																							//02: TTL_gout_bit4,<O>,<HS>
																							//03: TCON_bit11,<O>
																							//10: P_HIF_Data_bit5,<I/O>
																							//15: VBY1_LOCK_src0,<I>
																							//1F: MIS_GPIO_bit66,<I/O>
																							//def: MIS_GPIO_bit66,<I/O>


// PAD_NAME: PLT_P0_TXAP 49
#define RTD298X_QFP176_PIN_87								(0x00&0x1F)//0xB80008C0[21:17];
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


// PAD_NAME: PLT_P0_TXAN 50
#define RTD298X_QFP176_PIN_88								(0x00&0x1F)//0xB80008C0[16:12];
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


// PAD_NAME: PLT_P1_TXGP 51
#define RTD298X_QFP176_PIN_90								(0x1F&0x1F)//0xB80008C0[11:7];
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


// PAD_NAME: PLT_P1_TXGN 52
#define RTD298X_QFP176_PIN_91								(0x1F&0x1F)//0xB80008C0[6:2];
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


// PAD_NAME: PLT_P1_TXFP 53
#define RTD298X_QFP176_PIN_92								(0x00&0x1F)//0xB80008C4[31:27];
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


// PAD_NAME: PLT_P1_TXFN 54
#define RTD298X_QFP176_PIN_93								(0x00&0x1F)//0xB80008C4[26:22];
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


// PAD_NAME: PLT_P1_TXEP 55
#define RTD298X_QFP176_PIN_94								(0x00&0x1F)//0xB80008C4[21:17];
																							//00: LVDS_B_EP,<AO>
																							//02: TTL_gout_bit1,<O>,<HS>
																							//03: TCON_bit18,<O>
																							//10: P_HIF_Data_bit8,<I/O>
																							//1F: MIS_GPIO_bit71,<I/O>
																							//def: MIS_GPIO_bit71,<I/O>


// PAD_NAME: PLT_P1_TXEN 56
#define RTD298X_QFP176_PIN_95								(0x00&0x1F)//0xB80008C4[16:12];
																							//00: LVDS_B_EN,<AO>
																							//02: TTL_gout_bit0,<O>,<HS>
																							//03: TCON_bit19,<O>
																							//10: P_HIF_Data_bit9,<I/O>
																							//1F: MIS_GPIO_bit72,<I/O>
																							//def: MIS_GPIO_bit72,<I/O>


// PAD_NAME: PLT_P1_TXDP 57
#define RTD298X_QFP176_PIN_96								(0x00&0x1F)//0xB80008C4[11:7];
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


// PAD_NAME: PLT_P1_TXDN 58
#define RTD298X_QFP176_PIN_97								(0x00&0x1F)//0xB80008C4[6:2];
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


// PAD_NAME: PLT_P1_TXCP 59
#define RTD298X_QFP176_PIN_98								(0x00&0x1F)//0xB80008C8[31:27];
																							//00: LVDS_B_CP,<AO>
																							//02: TTL_rout_bit5,<O>,<HS>
																							//03: TCON_bit2,<O>
																							//10: P_HIF_Data_bit10,<I/O>
																							//1F: MIS_GPIO_bit75,<I/O>
																							//def: MIS_GPIO_bit75,<I/O>


// PAD_NAME: PLT_P1_TXCN 60
#define RTD298X_QFP176_PIN_99								(0x00&0x1F)//0xB80008C8[26:22];
																							//00: LVDS_B_CN,<AO>
																							//02: TTL_rout_bit4,<O>,<HS>
																							//03: TCON_bit3,<O>
																							//10: P_HIF_Data_bit11,<I/O>
																							//1F: MIS_GPIO_bit76,<I/O>
																							//def: MIS_GPIO_bit76,<I/O>


// PAD_NAME: PLT_P1_TXBP 61
#define RTD298X_QFP176_PIN_100								(0x00&0x1F)//0xB80008C8[21:17];
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


// PAD_NAME: PLT_P1_TXBN 62
#define RTD298X_QFP176_PIN_101								(0x00&0x1F)//0xB80008C8[16:12];
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
																							//def: MIS_GPIO_bit78,<I/O>																							//1


// PAD_NAME: PLT_P1_TXAP 63
#define RTD298X_QFP176_PIN_102								(0x00&0x1F)//0xB80008C8[11:7];
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


// PAD_NAME: PLT_P1_TXAN 64
#define RTD298X_QFP176_PIN_103								(0x00&0x1F)//0xB80008C8[6:2];
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

// PAD_NAME: pad_st_gpio_7_io 65
#define RTD298X_QFP176_PIN_105								(0x1F&0x1F)//0xB806024C[13:9];
																							//02: ST_dbg_bit0,<I/O>
																							//03: TCON_bit16,<O>
																							//1F: ISO_MIS_GPIO_bit7,<I/O>
																							//def: ISO_MIS_GPIO_bit7,<I/O>
#define RTD298X_QFP176_PIN_105_UP							(1&0x01)// 0xB806024C[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_105_PD							(0&0x01)// 0xB806024C[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_105_DS							(0&0x01)// 0xB806024C[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_105_SR							(0&0x01)// 0xB806024C[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_8_io 66
#define RTD298X_QFP176_PIN_106								(0x08&0x1F)//0xB806024C[22:18];
																							//02: ST_dbg_bit1,<I/O>
																							//03: PCMCIA_IREQ1_N_SRC0,<I>
																							//04: TCON_bit17,<O>
																							//08: irrX_src0,<I>
																							//09: ETN_LED_LINK,<O>
																							//11: VFD_D_SRC0,<I/O>
																							//15: GSPI_SCLK_SRC1,<I/O>,<HS>
																							//1F: ISO_MIS_GPIO_bit8,<I/O>
																							//def: ISO_MIS_GPIO_bit8,<I/O>
#define RTD298X_QFP176_PIN_106_UP							(1&0x01)// 0xB806024C[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_106_PD							(0&0x01)// 0xB806024C[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_106_DS							(0&0x01)// 0xB806024C[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_106_SR							(0&0x01)// 0xB806024C[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_9_io 67
#define RTD298X_QFP176_PIN_107								(0x1F&0x1F)//0xB806024C[31:27];
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
#define RTD298X_QFP176_PIN_107_UP							(1&0x01)// 0xB806024C[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_107_PD							(0&0x01)// 0xB806024C[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_107_DS							(0&0x01)// 0xB806024C[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_107_SR							(0&0x01)// 0xB806024C[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_10_io 68
#define RTD298X_QFP176_PIN_108								(0x1F&0x1F)//0xB8060248[13:9];
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
#define RTD298X_QFP176_PIN_108_UP							(1&0x01)// 0xB8060248[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_108_PD							(0&0x01)// 0xB8060248[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_108_DS							(0&0x01)// 0xB8060248[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_108_SR							(0&0x01)// 0xB8060248[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_11_io 69
#define RTD298X_QFP176_PIN_109								(0x1F&0x1F)//0xB8060248[22:18];
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
#define RTD298X_QFP176_PIN_109_UP							(1&0x01)// 0xB8060248[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_109_PD							(0&0x01)// 0xB8060248[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_109_DS							(0&0x01)// 0xB8060248[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_109_SR							(0&0x01)// 0xB8060248[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_12_io 70
#define RTD298X_QFP176_PIN_110								(0x01&0x1F)//0xB8060248[31:27];
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
#define RTD298X_QFP176_PIN_110_UP							(1&0x01)// 0xB8060248[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_110_PD							(0&0x01)// 0xB8060248[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_110_DS							(0&0x01)// 0xB8060248[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_110_SR							(0&0x01)// 0xB8060248[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_13_io 71
#define RTD298X_QFP176_PIN_111								(0x1F&0x1F)//0xB8060244[13:9];
																							//02: ST_dbg_bit30,<I/O>
																							//03: PCMCIA_RST1,<OD>
																							//08: IRTX,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0D: iso_misc_pwm_1,<OD>
																							//0F: I2C0_SDA_SRC4,<I/O>
																							//13: I2S_out_Data0,<O>
																							//1F: ISO_MIS_GPIO_bit13,<I/O>
																							//def: ISO_MIS_GPIO_bit13,<I/O>
#define RTD298X_QFP176_PIN_111_UP							(0&0x01)// 0xB8060244[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_111_PD							(1&0x01)// 0xB8060244[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_111_DS							(0&0x01)// 0xB8060244[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_111_SR							(0&0x01)// 0xB8060244[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_14_io 72
#define RTD298X_QFP176_PIN_112								(0x09&0x1F)//0xB8060204[31:27];
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
#define RTD298X_QFP176_PIN_112_UP							(1&0x01)// 0xB8060204[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_112_PD							(0&0x01)// 0xB8060204[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_112_DS							(0&0x01)// 0xB8060204[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_112_SR							(0&0x01)// 0xB8060204[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_15_io 73
#define RTD298X_QFP176_PIN_113								(0x09&0x1F)//0xB8060200[13:9];
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
#define RTD298X_QFP176_PIN_113_UP							(1&0x01)// 0xB8060200[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_113_PD							(0&0x01)// 0xB8060200[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_113_DS							(0&0x01)// 0xB8060200[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_113_SR							(0&0x01)// 0xB8060200[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_16_io 74
#define RTD298X_QFP176_PIN_114								(0x07&0x1F)//0xB8060244[22:18];
																							//02: ST_dbg_bit14,<I/O>
																							//06: CR_SD_CMD_SRC0,<I/O>,<HS>
																							//07: SC0_RST,<OD>
																							//08: SC1_RST,<OD>
																							//09: irrX_src1,<I>
																							//1F: ISO_MIS_GPIO_bit16,<I/O>
																							//def: ISO_MIS_GPIO_bit16,<I/O>
#define RTD298X_QFP176_PIN_114_UP							(1&0x01)// 0xB8060244[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_114_PD							(0&0x01)// 0xB8060244[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_114_DS							(0&0x01)// 0xB8060244[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_114_SR							(0&0x01)// 0xB8060244[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_17_io 75
#define RTD298X_QFP176_PIN_115								(0x04&0x1F)//0xB8060204[22:18];
																							//02: ST_dbg_bit7,<I/O>
																							//04: HDDC2_SCL,<I>
																							//06: CR_SD_CLK,<O>,<HS>
																							//07: SC0_SCLK,<OD>
																							//08: SC1_SCLK,<OD>
																							//09: ETN_LED_LINK,<O>
																							//17: test_en_bit21,<I/O>
																							//1F: ISO_MIS_GPIO_bit17,<I/O>
																							//def: ISO_MIS_GPIO_bit17,<I/O>
#define RTD298X_QFP176_PIN_115_UP							(1&0x01)// 0xB8060204[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_115_PD							(0&0x01)// 0xB8060204[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_115_DS							(0&0x01)// 0xB8060204[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_115_SR							(0&0x01)// 0xB8060204[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_18_io 76
#define RTD298X_QFP176_PIN_116								(0x04&0x1F)//0xB8060204[13:9];
																							//02: ST_dbg_bit31,<I/O>
																							//04: HDDC2_SDA,<I/O>
																							//08: irrX_src4,<I>
																							//09: ETN_LED_TXRX,<O>
																							//1F: ISO_MIS_GPIO_bit18,<I/O>
																							//def: ISO_MIS_GPIO_bit18,<I/O>
#define RTD298X_QFP176_PIN_116_UP							(1&0x01)// 0xB8060204[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_116_PD							(0&0x01)// 0xB8060204[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_116_DS							(0&0x01)// 0xB8060204[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_116_SR							(0&0x01)// 0xB8060204[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_19_io 77
#define RTD298X_QFP176_PIN_117								(0x1F&0x1F)//0xB8060244[31:27];
																							//02: ST_dbg_bit8,<I/O>
																							//06: CR_SD_WP_SRC7,<I>,<HS>
																							//07: SC0_CD_SRC0,<I>
																							//08: SC1_CD_SRC5,<I>
																							//17: test_en_bit22,<I/O>
																							//1F: ISO_MIS_GPIO_bit19,<I/O>
																							//def: ISO_MIS_GPIO_bit19,<I/O>
#define RTD298X_QFP176_PIN_117_UP							(1&0x01)// 0xB8060244[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_117_PD							(0&0x01)// 0xB8060244[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_117_DS							(0&0x01)// 0xB8060244[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_117_SR							(0&0x01)// 0xB8060244[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_20_io 78
#define RTD298X_QFP176_PIN_118								(0x04&0x1F)//0xB8060208[31:27];
																							//02: ST_dbg_bit9,<I/O>
																							//04: HDDC1_SCL,<I>
																							//06: CR_SD_CD_SRC1,<I>,<HS>
																							//0A: SPDIF_OUT,<O>
																							//17: test_en_bit24,<I/O>
																							//1F: ISO_MIS_GPIO_bit20,<I/O>
																							//def: ISO_MIS_GPIO_bit20,<I/O>
#define RTD298X_QFP176_PIN_118_UP							(1&0x01)// 0xB8060208[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_118_PD							(0&0x01)// 0xB8060208[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_118_DS							(0&0x01)// 0xB8060208[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_118_SR							(0&0x01)// 0xB8060208[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_21_io 79
#define RTD298X_QFP176_PIN_119								(0x04&0x1F)//0xB8060208[22:18];
																							//02: ST_dbg_bit10,<I/O>
																							//04: HDDC1_SDA,<I/O>
																							//06: CR_SD_Data_bit0_SRC1,<I/O>,<HS>
																							//07: SC0_DATA0_SRC0,<I/O>
																							//08: SC1_DATA0_SRC6,<I/O>
																							//17: test_en_bit25,<I/O>
																							//1F: ISO_MIS_GPIO_bit21,<I/O>
																							//def: ISO_MIS_GPIO_bit21,<I/O>
#define RTD298X_QFP176_PIN_119_UP							(1&0x01)// 0xB8060208[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_119_PD							(0&0x01)// 0xB8060208[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_119_DS							(0&0x01)// 0xB8060208[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_119_SR							(0&0x01)// 0xB8060208[14]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_22_io 80
#define RTD298X_QFP176_PIN_120								(0x1F&0x1F)//0xB8060240[13:9];
																							//02: ST_dbg_bit13,<I/O>
																							//06: CR_SD_Data_bit1_SRC1,<I/O>,<HS>
																							//08: SC1_SCLK,<OD>
																							//09: uart0_rts_n,<O>
																							//0A: uart1_rts_n,<O>
																							//1F: ISO_MIS_GPIO_bit22,<I/O>
																							//def: ISO_MIS_GPIO_bit22,<I/O>
#define RTD298X_QFP176_PIN_120_UP							(1&0x01)// 0xB8060240[8]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_120_PD							(0&0x01)// 0xB8060240[7]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_120_DS							(0&0x01)// 0xB8060240[6]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_120_SR							(0&0x01)// 0xB8060240[5]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_23_io 81
#define RTD298X_QFP176_PIN_121								(0x04&0x1F)//0xB8060200[31:27];
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
#define RTD298X_QFP176_PIN_121_UP							(1&0x01)// 0xB8060200[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_121_PD							(0&0x01)// 0xB8060200[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_121_DS							(0&0x01)// 0xB8060200[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_121_SR							(0&0x01)// 0xB8060200[23]: Slew rate 0:fast 1:slow


// PAD_NAME: pad_st_gpio_24_io 82
#define RTD298X_QFP176_PIN_122								(0x04&0x1F)//0xB8060200[22:18];
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
																							//def
#define RTD298X_QFP176_PIN_122_UP							(1&0x01)// 0xB8060200[17]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_122_PD							(0&0x01)// 0xB8060200[16]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_122_DS							(0&0x01)// 0xB8060200[15]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_122_SR							(0&0x01)// 0xB8060200[14]: Slew rate 0:fast 1:slow


// PAD_NAME: LSADC_REF_APAD 83
#define RTD298X_QFP176_PIN_123								(0x1F&0x1F)//0xB806020C[31:27];
																							//0C: LSADC_REF,<AI>
																							//1F: ISO_MIS_GPIO_bit0,<I/O>
																							//def: ISO_MIS_GPIO_bit0,<I/O>


// PAD_NAME: LSADC0_APAD 84
#define RTD298X_QFP176_PIN_124								(0x0C&0x1F)//0xB8060210[31:27];
																							//0C: LSADC0,<AI>
																							//1F: ISO_MIS_GPIO_bit1,<I/O>
																							//def: ISO_MIS_GPIO_bit1,<I/O>


// PAD_NAME: LSADC1_APAD 85
#define RTD298X_QFP176_PIN_125								(0x0C&0x1F)//0xB806020C[6:2];
																							//0C: LSADC1,<AI>
																							//1F: ISO_MIS_GPIO_bit2,<I/O>
																							//def: ISO_MIS_GPIO_bit2,<I/O>


// PAD_NAME: LSADC2_APAD 86
#define RTD298X_QFP176_PIN_126								(0x1F&0x1F)//0xB806020C[11:7];
																							//0C: LSADC2,<AI>
																							//1F: ISO_MIS_GPIO_bit3,<I/O>
																							//def: ISO_MIS_GPIO_bit3,<I/O>


// PAD_NAME: LSADC7_APAD 87
#define RTD298X_QFP176_PIN_127								(0x1F&0x1F)//0xB806020C[26:22];
																							//0C: LSADC7,<AI>
																							//1F: ISO_MIS_GPIO_bit6,<I/O>
																							//def: ISO_MIS_GPIO_bit6,<I/O>


// PAD_NAME: STB_GPIO_APAD 88
#define RTD298X_QFP176_PIN_129								(0x1F&0x1F)//0xB8060218[21:17];
																							//04: TCON_bit19,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: ETN_LED_TXRX,<O>
																							//0C: iso_misc_uni_pwm0,<O>
																							//1F: ISO_MIS_GPIO_bit47,<I/O>
																							//def: ISO_MIS_GPIO_bit47,<I/O>
#define RTD298X_QFP176_PIN_129_UP							(1&0x01)// 0xB8060218[16]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_129_PD							(0&0x01)// 0xB8060218[15]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_129_DS							(0&0x01)// 0xB8060218[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_129_SR							(0&0x01)// 0xB8060218[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VSYNC_APAD 89
#define RTD298X_QFP176_PIN_161								(0x0C&0x1F)//0xB80008D8[31:27];
																							//0C: VSYNC,<AI>
																							//1F: MIS_GPIO_bit111,<I/O>
																							//def: VSYNC,<AI>
#define RTD298X_QFP176_PIN_161_UP							(1&0x01)// 0xB80008D8[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_161_PD							(0&0x01)// 0xB80008D8[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_161_DS							(0&0x01)// 0xB80008D8[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_161_SR							(0&0x01)// 0xB80008D8[23]: Slew rate 0:fast 1:slow


// PAD_NAME: HSYNC_APAD 90
#define RTD298X_QFP176_PIN_162								(0x0C&0x1F)//0xB80008D8[26:22];
																							//0C: HSYNC,<AI>
																							//1F: MIS_GPIO_bit112,<I/O>
																							//def: HSYNC,<AI>
#define RTD298X_QFP176_PIN_162_UP							(1&0x01)// 0xB80008D8[21]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_162_PD							(0&0x01)// 0xB80008D8[20]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_162_DS							(0&0x01)// 0xB80008D8[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_162_SR							(0&0x01)// 0xB80008D8[18]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_0P_APAD 91
#define RTD298X_QFP176_PIN_163								(0x0C&0x1F)//0xB80008DC[31:27];
																							//03: TCON_bit0,<O>
																							//0C: VIN_0P,<AI>
																							//1F: MIS_GPIO_bit113,<I/O>
																							//def: VIN_0P,<AI>
#define RTD298X_QFP176_PIN_163_UP							(1&0x01)// 0xB80008DC[26]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_163_PD							(0&0x01)// 0xB80008DC[25]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_163_DS							(0&0x01)// 0xB80008DC[24]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_163_SR							(0&0x01)// 0xB80008DC[23]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_BN_APAD 92
#define RTD298X_QFP176_PIN_164								(0x1F&0xC)//0xB80008DC[26:22];
																							//03: TCON_bit1,<O>
																							//0C: VIN_BN,<AI>
																							//1F: MIS_GPIO_bit114,<I/O>
																							//def: VIN_BN,<AI>
#define RTD298X_QFP176_PIN_164_UP							(1&0x01)// 0xB80008DC[21]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_164_PD							(0&0x01)// 0xB80008DC[20]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_164_DS							(0&0x01)// 0xB80008DC[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_164_SR							(0&0x01)// 0xB80008DC[18]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_1P_APAD 93
#define RTD298X_QFP176_PIN_165								(0x1F&0xC)//0xB80008DC[21:17];
																							//03: TCON_bit2,<O>
																							//09: ETN_LED_LINK,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: VIN_1P,<AI>
																							//0D: misc_uni_pwm7,<O>
																							//0E: misc_pwm_3,<OD>
																							//1F: MIS_GPIO_bit115,<I/O>
																							//def: VIN_1P,<AI>
#define RTD298X_QFP176_PIN_165_UP							(1&0x01)// 0xB80008DC[16]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_165_PD							(0&0x01)// 0xB80008DC[15]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_165_DS							(0&0x01)// 0xB80008DC[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_165_SR							(0&0x01)// 0xB80008DC[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_2P_APAD 94
#define RTD298X_QFP176_PIN_166								(0x0C&0x1F)//0xB80008DC[16:12];
																							//03: TCON_bit3,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0C: VIN_2P,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//1F: MIS_GPIO_bit116,<I/O>
																							//def: VIN_2P,<AI>
#define RTD298X_QFP176_PIN_166_UP							(1&0x01)// 0xB80008DC[11]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_166_PD							(0&0x01)// 0xB80008DC[10]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_166_DS							(0&0x01)// 0xB80008DC[9]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_166_SR							(0&0x01)// 0xB80008DC[8]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_10P_APAD 95
#define RTD298X_QFP176_PIN_172								(0x1F&0x1F)//0xB80008E4[11:7];
																							//03: TCON_bit12,<O>
																							//0C: VIN_10P,<AI>
																							//1F: MIS_GPIO_bit125,<I/O>
																							//def: VIN_10P,<AI>
#define RTD298X_QFP176_PIN_172_UP							(1&0x01)// 0xB80008E4[6]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_172_PD							(0&0x01)// 0xB80008E4[5]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_172_DS							(0&0x01)// 0xB80008E4[4]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_172_SR							(0&0x01)// 0xB80008E4[3]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_A0N_APAD 96
#define RTD298X_QFP176_PIN_173								(0x0C&0x1F)//0xB80008E4[21:17];
																							//03: TCON_bit10,<O>
																							//0C: VIN_A0N,<AI>
																							//1F: MIS_GPIO_bit123,<I/O>
																							//def: VIN_A0N,<AI>
#define RTD298X_QFP176_PIN_173_UP							(1&0x01)// 0xB80008E4[16]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_173_PD							(0&0x01)// 0xB80008E4[15]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_173_DS							(0&0x01)// 0xB80008E4[14]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_173_SR							(0&0x01)// 0xB80008E4[13]: Slew rate 0:fast 1:slow


// PAD_NAME: VIN_12P_APAD 97
#define RTD298X_QFP176_PIN_174								(0x0C&0x1F)//0xB80008E4[26:22];
																							//03: TCON_bit9,<O>
																							//09: ETN_LED_TXRX,<O>
																							//0A: SPDIF_OUT,<O>
																							//0C: VIN_12P,<AI>
																							//0D: misc_uni_pwm5,<O>
																							//0E: misc_pwm_3,<OD>
																							//0F: I2C0_SCL_SRC12,<I/O>
																							//1F: MIS_GPIO_bit122,<I/O>
																							//def: VIN_12P,<AI>
#define RTD298X_QFP176_PIN_174_UP							(1&0x01)// 0xB80008E4[21]: Pull Up 0:disable 1:enable
#define RTD298X_QFP176_PIN_174_PD							(0&0x01)// 0xB80008E4[20]: Pull Down 0:disable 1:enable
#define RTD298X_QFP176_PIN_174_DS							(0&0x01)// 0xB80008E4[19]: Driving Strength 0:4mA 1:8mA
#define RTD298X_QFP176_PIN_174_SR							(0&0x01)// 0xB80008E4[18]: Slew rate 0:fast 1:slow




#define PIN_BL_ON_OFF 			RTD298X_QFP176_PIN_108_ISO_GPO_10(1, 0)
#define PIN_BL_ADJ				RTD298X_QFP176_PIN_74_PWM_3(1, 200, 255, 255)
#define PIN_LVDS_ON_OFF			RTD298X_QFP176_PIN_76_GPO_82(0, 1)
	
//#define PIN_KEYPAD_MENU		RTD299X_BGA_PIN_E2_LSADC_CURRENT_0(19, 1)
//#define PIN_KEYPAD_SOURCE		RTD299X_BGA_PIN_E2_LSADC_CURRENT_0(14, 1)
#define PIN_KEYPAD_RIGHT		RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(0, 5)
#define PIN_KEYPAD_LEFT			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(14, 5)
#define PIN_KEYPAD_UP			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(31, 5)
#define PIN_KEYPAD_DOWN			RTD298X_QFP176_PIN_124_LSADC_VOLTAGE_0(47, 5)
#define PIN_KEYPAD_PWR			RTD298X_QFP176_PIN_125_LSADC_VOLTAGE_1(0, 10)
	
	// HDMI 1 reletive board information
#define PIN_HDMI1_HOTPLUG		RTD298X_QFP176_PIN_120_ISO_GPO_22(0, 0)
#define HDMI1_DDC				PCB_DDC_0
#define HDMI1_PHY_PORT			HDMI_PHY_PORT0
#define HDMI1_EDID_TYPE  		HDMI_EDID_ONCHIP
#define HDMI1_HPD_TYPE			HDMI_HPD_ONCHIP
#define HDMI1_MUX_PORT			HDMI_MUX_PORT_NOTUSED
#define HDMI1_MUX_IC			HDMI_MUX_NOUSED
	
	// HDMI 2 reletive board information
#define PIN_HDMI2_HOTPLUG		RTD298X_QFP176_PIN_117_ISO_GPO_19(0, 0)
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
	
#define PIN_HDMI_MHL_SELECT		RTD298X_QFP176_PIN_107_ISO_GPO_9(0, 1)
#define PIN_HDMI_CABLE_DETECT	RTD298X_QFP176_PIN_126_ISO_GPI_3(0)
#define PIN_MHL_CABLE_DETECT	RTD298X_QFP176_PIN_111_ISO_GPI_13(0)
	
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
#define PIN_AMP_MUTE			RTD298X_QFP176_PIN_109_ISO_GPO_11(0,0)   // 0: unmute  1: mute
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
//#define PIN_FLASH_WP			RTD298X_QFP176_PIN_91_GPO_84(0, 1)   //0: enable write protection  1: disable write protection 
	//#define MISC_951_RST
#define PIN_POWER_DETECT		RTD298X_QFP176_PIN_127_ISO_GPI_6(0)
#define POWER_EN				RTD298X_QFP176_PIN_105_ISO_GPO_7(0, 1)
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
PCB_ENUM(PIN_KEYPAD_RIGHT)
PCB_ENUM(PIN_KEYPAD_LEFT)
PCB_ENUM(PIN_KEYPAD_UP)
PCB_ENUM(PIN_KEYPAD_DOWN)
PCB_ENUM(PIN_KEYPAD_PWR)
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
