#ifndef __SED_DRV_PINMUX_H__
#define __SED_DRV_PINMUX_H__

/* "PMM_Sirius_PinMux.doc page5" */
#define ST_PINMUX_REG_BASE	0xb8060200

#define GPIO_ST_MUXCFG_0	(ST_PINMUX_REG_BASE + 0x00)
#define GPIO_ST_MUXCFG_1	(ST_PINMUX_REG_BASE + 0x04)
#define GPIO_ST_MUXCFG_2	(ST_PINMUX_REG_BASE + 0x08)
#define GPIO_ST_MUXCFG_3	(ST_PINMUX_REG_BASE + 0x0c)
#define GPIO_ST_MUXCFG_4	(ST_PINMUX_REG_BASE + 0x10)
#define GPIO_ST_MUXCFG_5	(ST_PINMUX_REG_BASE + 0x14)
#define GPIO_ST_MUXCFG_6	(ST_PINMUX_REG_BASE + 0x18)
#define GPIO_ST_MUXCFG_7	(ST_PINMUX_REG_BASE + 0x1c)
#define GPIO_ST_MUXCFG_8	(ST_PINMUX_REG_BASE + 0x24)
#define GPIO_ST_MUXCFG_9	(ST_PINMUX_REG_BASE + 0x28)
#define GPIO_ST_MUXCFG_10	(ST_PINMUX_REG_BASE + 0x2c)
#define GPIO_ST_MUXCFG_11	(ST_PINMUX_REG_BASE + 0x30)
#define GPIO_ST_MUXCFG_12	(ST_PINMUX_REG_BASE + 0x34)
#define GPIO_ST_MUXCFG_13	(ST_PINMUX_REG_BASE + 0x38)
#define GPIO_ST_MUXCFG_14	(ST_PINMUX_REG_BASE + 0x3c)
#define GPIO_ST_MUXCFG_15	(ST_PINMUX_REG_BASE + 0x40)
#define GPIO_ST_MUXCFG_16	(ST_PINMUX_REG_BASE + 0x44)
#define GPIO_ST_MUXCFG_17	(ST_PINMUX_REG_BASE + 0x48)
#define GPIO_ST_MUXCFG_18	(ST_PINMUX_REG_BASE + 0x4c)

#define ST_PIN_MUX_CTRL0	(ST_PINMUX_REG_BASE + 0xa0)

/* "Main_Sirius_PinMux.doc" */
#define PINMUX_REG_BASE	0xb8000800

#define GPIO_MUXCFG_0	(PINMUX_REG_BASE + 0x00)
#define GPIO_MUXCFG_1	(PINMUX_REG_BASE + 0x04)
#define GPIO_MUXCFG_2	(PINMUX_REG_BASE + 0x08)
#define GPIO_MUXCFG_3	(PINMUX_REG_BASE + 0x0c)
#define GPIO_MUXCFG_4	(PINMUX_REG_BASE + 0x10)
#define GPIO_MUXCFG_5	(PINMUX_REG_BASE + 0x14)
#define GPIO_MUXCFG_6	(PINMUX_REG_BASE + 0x18)
#define GPIO_MUXCFG_7	(PINMUX_REG_BASE + 0x1c)
#define GPIO_MUXCFG_8	(PINMUX_REG_BASE + 0x20)
#define GPIO_MUXCFG_9	(PINMUX_REG_BASE + 0x24)
#define GPIO_MUXCFG_10	(PINMUX_REG_BASE + 0x28)
#define GPIO_MUXCFG_11	(PINMUX_REG_BASE + 0x2c)
#define GPIO_MUXCFG_12	(PINMUX_REG_BASE + 0x30)
#define GPIO_MUXCFG_13	(PINMUX_REG_BASE + 0x34)
#define GPIO_MUXCFG_14	(PINMUX_REG_BASE + 0x38)
#define GPIO_MUXCFG_15	(PINMUX_REG_BASE + 0x3c)
#define GPIO_MUXCFG_16	(PINMUX_REG_BASE + 0x40)
#define GPIO_MUXCFG_17	(PINMUX_REG_BASE + 0x44)
#define GPIO_MUXCFG_18	(PINMUX_REG_BASE + 0x48)
#define GPIO_MUXCFG_19	(PINMUX_REG_BASE + 0x4c)
#define GPIO_MUXCFG_20	(PINMUX_REG_BASE + 0x50)
#define GPIO_MUXCFG_21	(PINMUX_REG_BASE + 0x54)
#define GPIO_MUXCFG_22	(PINMUX_REG_BASE + 0x58)
#define GPIO_MUXCFG_23	(PINMUX_REG_BASE + 0x5c)
#define GPIO_MUXCFG_24	(PINMUX_REG_BASE + 0x60)
#define GPIO_MUXCFG_25	(PINMUX_REG_BASE + 0x64)
#define GPIO_MUXCFG_26	(PINMUX_REG_BASE + 0x68)
#define GPIO_MUXCFG_27	(PINMUX_REG_BASE + 0x6c)
#define GPIO_MUXCFG_28	(PINMUX_REG_BASE + 0x70)
#define GPIO_MUXCFG_29	(PINMUX_REG_BASE + 0x74)
#define GPIO_MUXCFG_30	(PINMUX_REG_BASE + 0x78)
#define GPIO_MUXCFG_31	(PINMUX_REG_BASE + 0x7c)
#define GPIO_MUXCFG_32	(PINMUX_REG_BASE + 0x80)
#define GPIO_MUXCFG_33	(PINMUX_REG_BASE + 0x84)
#define GPIO_MUXCFG_34	(PINMUX_REG_BASE + 0x88)
#define GPIO_MUXCFG_35	(PINMUX_REG_BASE + 0x8c)
#define GPIO_MUXCFG_36	(PINMUX_REG_BASE + 0x90)
#define GPIO_MUXCFG_37	(PINMUX_REG_BASE + 0x94)
#define GPIO_MUXCFG_38	(PINMUX_REG_BASE + 0x98)
#define GPIO_MUXCFG_39	(PINMUX_REG_BASE + 0x9c)
#define GPIO_MUXCFG_40	(PINMUX_REG_BASE + 0xa0)
#define GPIO_MUXCFG_41	(PINMUX_REG_BASE + 0xa4)
#define GPIO_MUXCFG_42	(PINMUX_REG_BASE + 0xa8)
#define GPIO_MUXCFG_43	(PINMUX_REG_BASE + 0xac)
#define GPIO_MUXCFG_44	(PINMUX_REG_BASE + 0xb0)
#define GPIO_MUXCFG_45	(PINMUX_REG_BASE + 0xb4)

#define PIN_MUX_CTRL0 	(PINMUX_REG_BASE + 0xc0)
#define PIN_MUX_CTRL1 	(PINMUX_REG_BASE + 0xc4)
#define PIN_MUX_CTRL2 	(PINMUX_REG_BASE + 0xc8)

#define BB_USB_CFG_1	(PINMUX_REG_BASE + 0xf8)

void sed_pinmux_uart (void);
void sed_pinmux_spi(void);

#endif
