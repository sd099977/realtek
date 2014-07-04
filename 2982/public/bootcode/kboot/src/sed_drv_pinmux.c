#include "sed_drv_common.h"
#include "sed_drv_pinmux.h"
#include "sed_common.h"

void sed_pinmux_spi(void)
{
	// set the spi pin mux
	REG32(GPIO_MUXCFG_12)= 0x08040200;
	REG32(GPIO_MUXCFG_13)= 0x087C3E00;
}

void sed_pinmux_uart (void)
{
#if !defined(FPGA)
	uint32 inverse;

	/* RX */
	/* set uart0_rxdi_in_sel pin mux */
	/* UART0_rxdi_sel [18:16] -> "0: uart0_rxdi_src0 (vddc_scl_ps)" */
	inverse = (0x7 << 16);
	bitwise_AND_OR(ST_PIN_MUX_CTRL0, ~inverse, 0);

	/* set vddc_scl_ps pin mux */
	/* vddc_scl_ps [13:9 ] -> "9: uart0_rxdi_src0,<I>" */
	inverse = (0x1f << 9);
	bitwise_AND_OR(GPIO_ST_MUXCFG_0, ~inverse, (0x9 << 9));

	/* set uart1_rxdi_in_sel pin mux */
	/* uart1_rxdi_sel [22:20] -> "0: uart1_rxdi_src0(gpio_53_ps)" */
	inverse = (0x7 << 20);
	bitwise_AND_OR(PIN_MUX_CTRL0, ~inverse, 0);

	/* set gpio_53_ps  pin mux */
	/* gpio_53_ps  [13:9 ] -> "2: uart1_rxdi_src0,<I>" */
	inverse = (0x1f << 9);
	bitwise_AND_OR(GPIO_MUXCFG_16, ~inverse, (0x2 << 9));

	/* TX */
	/* set vddc_sda_ps pin mux */
	/* vddc_sda_ps [31:27] -> "9: uart0_txdo,<O> */
	inverse = (0x1f << 27);
	bitwise_AND_OR(GPIO_ST_MUXCFG_1, ~inverse, (0x9 << 27));

	/* set gpio_54_ps pin mux */
	/* gpio_54_ps [31:27] -> "2: uart1_txdo,<O>" */
	bitwise_AND_OR(GPIO_MUXCFG_17, ~inverse, (0x2 << 27));
#endif
}

