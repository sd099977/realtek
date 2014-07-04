/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * DAVE Srl
 * http://www.dave-tech.it
 * http://www.wawnet.biz
 * mailto:info@wawnet.biz
 *
 * (C) Copyright 2004 Texas Insturments
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#if defined(CONFIG_RTD299X)
#include <asm/arch/rbus/misc_reg.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/rbus/mis_reg.h>
#endif
#include <asm/arch/io.h>

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	puts ("resetting ...\n");

	udelay (50000);				/* wait 50 ms */

	disable_interrupts();
	//reset_cpu(0);

	// trigger watchdog reset
#ifdef CONFIG_BSP_REALTEK
#if defined(CONFIG_RTD299X)
	unsigned int regValue;
	regValue = rtd_inl(TCWCR_reg);
	regValue |= _BIT31;
	rtd_outl(TCWCR_reg, regValue);
#elif defined(CONFIG_RTD298X)
	// kick the dog no matter it is enabled.
	rtd_outl(MIS_TCWTR, _BIT0);
	// give a any small number
	rtd_outl(MIS_TCWOV_reg, 0x19BFCC0);	// around 1 sec
	// enable the dog
	rtd_clearbits(MIS_TCWCR_reg, 0xff);	
#endif

#endif
	/*NOTREACHED*/
	return 0;
}
