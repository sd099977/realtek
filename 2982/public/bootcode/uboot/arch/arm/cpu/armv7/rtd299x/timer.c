/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * Time initialization.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/rbus/misc_reg.h>
#include <asm/arch/system.h>

DECLARE_GLOBAL_DATA_PTR;

struct timer_reg
{
	unsigned int tvr;
	unsigned int cvr;
	unsigned int cr;
	unsigned int icr;
	unsigned char isr_bit;
};

struct timer_reg rtk_timer[8] =
{
	{TC0TVR, TC0CVR, TC0CR, TC0ICR, 6},
	{TC1TVR, TC1CVR, TC1CR, TC1ICR, 7},
	{TC2TVR, TC2CVR, TC2CR, TC2ICR, 8},
	{TC3TVR, TC3CVR, TC3CR, TC3ICR, 9},
	{TC4TVR, TC4CVR, TC4CR, TC4ICR, 10},
	{TC5TVR, TC5CVR, TC5CR, TC5ICR, 11},
	{TC6TVR, TC6CVR, TC6CR, TC6ICR, 12},
	{TC7TVR, TC7CVR, TC7CR, TC7ICR, 13}
};

static struct timer_reg *timer_base = &rtk_timer[SYSTEM_TIMER];

/*
 * Nothing really to do with interrupts, just starts up a counter.
 */

#define TIMER_OVERFLOW_VAL	0xffffffff
#define TIMER_LOAD_VAL		0xffffffff

#define TIMERINFO_TIMER_ENABLE              0xC0000000
#define TIMERINFO_TIMER_DISABLE             0x00000000
#define TIMERINFO_INTERRUPT_ENABLE          0x80000000
#define TIMERINFO_INTERRUPT_DISABLE         0x00000000

int timer_init(void)
{
	//Disable Interrupt
    rtd_outl(timer_base->icr, TIMERINFO_INTERRUPT_DISABLE);

    //Disable Timer
	rtd_outl(timer_base->cr, TIMERINFO_TIMER_DISABLE);

    //Set The Initial Value
	rtd_outl(timer_base->tvr, TIMER_LOAD_VAL);

    //Enable Timer Mode
	rtd_outl(timer_base->cr, TIMERINFO_TIMER_ENABLE);

	return 0;
}

/*
 * timer without interrupts
 */
unsigned long get_timer(unsigned long base)
{
	return get_timer_masked() - base;
}

/* delay x useconds */
void __udelay(unsigned long usec)
{
	long tmo = usec * (TIMER_CLOCK / 1000) / 1000;
	unsigned long now, last = readl(timer_base->cvr);

	while (tmo > 0) {
		now = rtd_inl(timer_base->cvr);
		if (now < last) /* count up timer overflow */
			tmo -= TIMER_OVERFLOW_VAL - last + now + 1;
		else
			tmo -= now - last;
		last = now;
	}
}

unsigned long get_timer_masked(void)
{
	/* current tick value */
	unsigned long now = rtd_inl(timer_base->cvr) / (TIMER_CLOCK / CONFIG_SYS_HZ);

	if (now >= gd->lastinc)	/* normal mode (non roll) */
		/* move stamp fordward with absoulte diff ticks */
		gd->tbl += (now - gd->lastinc);
	else	/* we have rollover of incrementer */
		gd->tbl += ((TIMER_LOAD_VAL / (TIMER_CLOCK / CONFIG_SYS_HZ))
			     - gd->lastinc) + now;
	gd->lastinc = now;
	return gd->tbl;
}

#ifndef CONFIG_BSP_REALTEK // mark unused code
/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
unsigned long get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
#endif

