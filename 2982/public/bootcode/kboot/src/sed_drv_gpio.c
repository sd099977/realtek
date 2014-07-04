#include "sed_common.h"
#include "sed_drv_gpio.h"

uint8 GPIO = 0;

#if 0
void mask_register(const unsigned int reg_addr, const unsigned int AND_filter,
	const unsigned int OR_filter)
{
	REG32(reg_addr) = (REG32(reg_addr) & AND_filter) | OR_filter;
}
#endif

void sed_gpio_init (void)
{
	//REG32(GPIO0_IE) = 0x0;

	//setting pinmux of GPIO
	REG32(0xb806023c) = (REG32(0xb806023c)&(~(0x7C0000)))|(0x7C0000);
	REG32(MIS_GPDIR) |= (0x1<<28);
}

//#define SHOW_GPIO(str)	sed_printf("[%s:%s]\n", str, (GPIO)?"H":"L"); // debug only
#define SHOW_GPIO(str)
void GPIO_reset (void)
{
	GPIO = 0;

	REG32(MIS_GPDATO) = REG32(MIS_GPDATO)&0xEFFFFFFF;

	SHOW_GPIO("reset");

	//sed_printf("REG32(MIS_GPDATO):0x%x\n",REG32(MIS_GPDATO));

}

void GPIO_toggle (void)
{
	GPIO ^= 1;

	//REG32(MIS_GPDATO) |= (GPIO<<28);

	if(GPIO)
		REG32(MIS_GPDATO) |= 0x10000000;
	else
		REG32(MIS_GPDATO) &= 0xEFFFFFFF;

	SHOW_GPIO("toggle");

	//sed_printf("REG32(MIS_GPDATO):0x%x\n",REG32(MIS_GPDATO));

}

void GPIO_pulse (void)
{
//	uint32 tick1, tick2;
	uint32 new_value, old_value = REG32(MIS_GPDATO);

	if(GPIO) {
		new_value = old_value & 0xEFFFFFFF;
	} else {
		new_value = old_value  | 0x10000000;
	}

	REG32(MIS_GPDATO) = new_value;
	REG32(MIS_GPDATO) = old_value;

	SHOW_GPIO("pulse");

#if 0
	//GPIO ^= 1;
	//	tick1 = REG32(0xb801b638);

//	SHOW_GPIO("pulse");
	//sed_printf("REG32(MIS_GPDATO):0x%x\n",REG32(MIS_GPDATO));


	/* Pulse Duration */
#if defined (SIRIUS) || defined (FPGA)
	/* Use MISC timer6 to get tick SIRIUS(27MHz) / FPGA(25MHz) */
	/* One tick: Sirius(37ns) / FPGA(40ns) */
	/* Target Pulse duration 10ns < PD < 1us => 1 ~ 27 ticks */
	REG32(0xb801b618) = 0xffffffff;
	REG32(0xb801b658) = 0x80000000;
	tick1 = REG32(0xb801b638);
	//while((tick2 = REG32(0xb801b638)) > 15);
	tick2 = REG32(0xb801b638);
#if 0
	while(tick2-tick1<1)
	{
		tick2 = REG32(0xb801b638);
	}
#endif
	REG32(0xb801b658) = 0x00000000;
#endif

#if 0 //For test pulse duration
	REG32(0xb801b618) = 0xffffffff;
	REG32(0xb801b658) = 0x80000000;
	tick1 = REG32(0xb801b638);
	tick2 = REG32(0xb801b638);
	REG32(0xb801b658) = 0x00000000;
printf("1-tick1: %08X, tick2: %08X\n", tick1, tick2);

	REG32(0xb801b618) = 0xffffffff;
	REG32(0xb801b658) = 0x80000000;
	tick1 = REG32(0xb801b638);
	while((tick2 = REG32(0xb801b638)) > 20);
	REG32(0xb801b658) = 0x00000000;
printf("2-tick1: %08X, tick2: %08X\n", tick1, tick2);
#endif


	//SHOW_GPIO("pulse");
	//sed_printf("REG32(MIS_GPDATO):0x%x\n",REG32(MIS_GPDATO));
#endif

}

