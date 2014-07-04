/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
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

/*
 * To match the U-Boot user interface on ARM platforms to the U-Boot
 * standard (as on PPC platforms), some messages with debug character
 * are removed from the default U-Boot build.
 *
 * Define DEBUG here if you want additional info as shown below
 * printed upon startup:
 *
 * U-Boot code: 00F00000 -> 00F3C774  BSS: -> 00FC3274
 * IRQ Stack: 00ebff7c
 * FIQ Stack: 00ebef7c
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <version.h>
#include <net.h>
#include <serial.h>
#include <nand.h>
#include <onenand_uboot.h>
#include <mmc.h>
#include <libfdt.h>
#include <fdtdec.h>
#include <post.h>
#include <logbuff.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pcb.h>
#include <system.h>
#include <fw_info.h>
#include <extern_param.h>
#include <logo_disp/logo_disp_api.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/bootparam.h>
#if defined(CONFIG_RTD299X)
#include <asm/arch/rbus/misc_reg.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/rbus/mis_reg.h>
#endif
#include <watchdog.h>
//wangzhh add for complier
#include <platform_lib/board/pcb.h>

#ifdef CONFIG_SYS_RTK_NAND_FLASH
#include <linux/mtd/nand.h>		//surport nand flash
#include <nand.h>
#endif

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

#ifdef CONFIG_DRIVER_SMC91111
#include "../drivers/net/smc91111.h"
#endif
#ifdef CONFIG_DRIVER_LAN91C96
#include "../drivers/net/lan91c96.h"
#endif

#ifdef CONFIG_SYS_PANEL_SUPPORT
#include "panel.h"
#endif

DECLARE_GLOBAL_DATA_PTR;

ulong monitor_flash_len;

uchar boot_ac_on = 0;
bool boot_on_fast_install_detect = 0;

#ifdef CONFIG_HAS_DATAFLASH
extern int  AT91F_DataflashInit(void);
extern void dataflash_print_info(void);
#endif

extern int init_customize_func(void);
extern int bringup_mmc_driver( void );

#if defined(CONFIG_HARD_I2C) || \
    defined(CONFIG_SOFT_I2C)
#include <i2c.h>
#endif

#if defined(CONFIG_CMD_KEY_BURNING)
int set_pin_mux_burn();
#endif

#if 0
#define debug(fmt,args...)	printf (fmt ,##args)
#else
#define debug(fmt,args...)
#endif

/************************************************************************
 *  External variables
 ************************************************************************/
extern int _f_exc_redirect_img, _e_exc_redirect_img;
extern int _f_exc_dispatch_img, _e_exc_dispatch_img;
extern int _f_a_entry_img, _e_a_entry_img;
extern int _f_a_entry_polling_0xa000000e_img, _e_a_entry_polling_0xa000000e_img;
extern int _f_v_entry_img, _e_v_entry_img;
extern int _f_v_ddr_cal_img, _e_v_ddr_cal_img;
extern int _f_v_ddr_cal_c_img, _e_v_ddr_cal_c_img;
extern int _f_isrvideo_img, _e_isrvideo_img;
extern int _f_rosbootvector_img, _e_rosbootvector_img;
extern int boot_power_on_mode;
extern int prev_power_on_status;

/************************************************************************
 * Coloured LED functionality
 ************************************************************************
 * May be supplied by boards if desired
 */
inline void __coloured_LED_init(void) {}
void coloured_LED_init(void)
	__attribute__((weak, alias("__coloured_LED_init")));
inline void __red_led_on(void) {}
void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
inline void __red_led_off(void) {}
void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
inline void __green_led_on(void) {}
void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
inline void __green_led_off(void) {}
void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
inline void __yellow_led_on(void) {}
void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
inline void __yellow_led_off(void) {}
void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
inline void __blue_led_on(void) {}
void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
inline void __blue_led_off(void) {}
void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));

/*
 ************************************************************************
 * Init Utilities							*
 ************************************************************************
 * Some of this code should be moved into the core functions,
 * or dropped completely,
 * but let's get it working (again) first...
 */

#if defined(CONFIG_ARM_DCC) && !defined(CONFIG_BAUDRATE)
#define CONFIG_BAUDRATE 115200
#endif

static int init_baudrate(void)
{
	gd->baudrate = getenv_ulong("baudrate", 10, CONFIG_BAUDRATE);
	return 0;
}

static int display_banner(void)
{
	printf("\n\n%s\n\n", version_string);
	debug("U-Boot code: %08lX -> %08lX  BSS: -> %08lX\n",
	       _TEXT_BASE,
	       _bss_start_ofs + _TEXT_BASE, _bss_end_ofs + _TEXT_BASE);
#ifdef CONFIG_MODEM_SUPPORT
	debug("Modem Support enabled\n");
#endif
#ifdef CONFIG_USE_IRQ
	debug("IRQ Stack: %08lx\n", IRQ_STACK_START);
	debug("FIQ Stack: %08lx\n", FIQ_STACK_START);
#endif

	return (0);
}

/*
 * WARNING: this code looks "cleaner" than the PowerPC version, but
 * has the disadvantage that you either get nothing, or everything.
 * On PowerPC, you might see "DRAM: " before the system hangs - which
 * gives a simple yet clear indication which part of the
 * initialization if failing.
 */
static int display_dram_config(void)
{
	int i;

#ifdef DEBUG
	puts("RAM Configuration:\n");

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		printf("Bank #%d: %08lx ", i, gd->bd->bi_dram[i].start);
		print_size(gd->bd->bi_dram[i].size, "\n");
	}
#else
	ulong size = 0;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
		size += gd->bd->bi_dram[i].size;

	puts("DRAM:  ");
	print_size(size, "\n");
#endif

	return (0);
}

#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
static int init_func_i2c(void)
{
	puts("I2C:   ");
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
	puts("ready\n");
	return (0);
}
#endif
#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_AD83586) || defined(CONFIG_REALTEK_AMP_TAS5707_TV013)
extern void AudioAmp_InitAudioOut2I2S_1st(void);
extern void AudioAmp_InitAudioOut2I2S_2nd(void);

static int init_amp_prepare(void)
{
#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_TAS5707_TV013) || defined(CONFIG_REALTEK_AMP_AD83586)
#if 0
printf("PIN_A7: 0xB800085C[23:20]; GPIO121   \t 0xB800085C=((xxf0xxxx))\n");
printf("PIN_A5: 0xB8000860[7:4]; GPIO127       \t 0xB8000860=((f0xxxxf0))\n");
printf("PIN_D7: 0xB8000860[31:28]; GPIO124\n");
printf("MIS_GP3DIR	((volatile int)0xb801bc0c)\n");
printf("MIS_GP3DATO	((volatile int)0xb801bc24)\n");
printf("MIS_GP3DATI	((volatile int)0xb801bc3c)\n");
printf("0xB800085C=((0x%08x))\n", rtd_inl(0xB800085C));
printf("0xB8000860=((0x%08x))\n", rtd_inl(0xB8000860));
printf("0xb801bc0c=((0x%08x))\n", rtd_inl(0xb801bc0c));
printf("0xb801bc24=((0x%08x))\n", rtd_inl(0xb801bc24));
printf("0xb801bc3c=((0x%08x))\n", rtd_inl(0xb801bc3c));
//EMMC
printf("0xb8000814 bit[23:20] & [15:12]set 1 \t 0xb8000814=((xx1010xx))\n");
printf("0xb8000814=((0x%08x))\n", rtd_inl(0xb8000814));
#endif
	printf("init_amp_prepare\n");
	AudioAmp_InitAudioOut2I2S_1st();
#endif
	return 0;
}

static int init_amp(void)
{
	if(boot_power_on_mode != POWER_OFF)
	{
		printf("init_amp\n");
#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_TAS5707_TV013) || defined(CONFIG_REALTEK_AMP_AD83586)
		AudioAmp_InitAudioOut2I2S_2nd();
		//AudioAmp_InitAudioOut2I2S_2nd();  //move to panel.c to speedup
#else
		AudioAmp_InitAudioOut2I2S_1st();
		AudioAmp_InitAudioOut2I2S_2nd();
#endif
	}
	return 0;
}
#endif

#if defined(CONFIG_CMD_PCI) || defined (CONFIG_PCI)
#include <pci.h>
static int arm_pci_init(void)
{
	pci_init();
	return 0;
}
#endif /* CONFIG_CMD_PCI || CONFIG_PCI */

/*
 * Breathe some life into the board...
 *
 * Initialize a serial port as console, and carry out some hardware
 * tests.
 *
 * The first part of initialization is running from Flash memory;
 * its main purpose is to initialize the RAM so that we
 * can relocate the monitor code to RAM.
 */

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependent #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t) (void);

int rtk_misc_init(void);
int rtk_mcu_bisr(void);
int rtk_gpu_bisr(void);
int rtk_demod_bisr( void );
int rtk_scpu_bisr(void);
int do_cp42k_bisr(void);
int print_cpuinfo(void);
int rtk_memory_info_init(void);
int rtk_package_init(void);
int rtk_bus_init(void);

#ifdef IS_BOX
int rtk_box_init(void);
#endif
#ifdef CONFIG_USE_RTK_RTC
int rtc_init(void);
#endif

void __dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size =  gd->ram_size;
}
void dram_init_banksize(void)
	__attribute__((weak, alias("__dram_init_banksize")));

int __arch_cpu_init(void)
{
	return 0;
}

int arch_cpu_init(void)
	__attribute__((weak, alias("__arch_cpu_init")));

init_fnc_t *init_sequence[] = {
	clock_init,			/* init clock, pll related */
	arch_cpu_init,		/* basic arch cpu dependent setup */
	rtk_bus_init,
#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,
#endif
#ifdef CONFIG_OF_CONTROL
	//fdtdec_check_fdt, //Need to be fixed
#endif
	timer_init,		/* initialize timer */
#ifdef CONFIG_FSL_ESDHC
	get_clocks,
#endif
	env_init,		/* initialize environment */
	init_baudrate,		/* initialze baudrate settings */
	serial_init,		/* serial communications setup */
	console_init_f,		/* stage 1 init of console */
	display_banner,		/* say that we are here */
#ifdef CONFIG_USE_RTK_RTC
	rtc_init,
#endif
#ifdef ENABLE_MCU_BISR
	//rtk_mcu_bisr, //Need to be fixed
#endif
#ifdef ENABLE_GPU_BISR
	//rtk_gpu_bisr, //Need to be fixed
#endif
#ifdef ENABLE_DEMOD_BISR
	//rtk_demod_bisr, //Need to be fixed
#endif
#ifdef ENABLE_SCPU_BISR
	rtk_scpu_bisr,
#endif
#if defined(CONFIG_DISPLAY_CPUINFO)
	print_cpuinfo,		/* display cpu info (and speed) */
#endif
//	rtk_misc_init,
#ifndef CONFIG_BSP_REALTEK
	dram_init,		/* configure available RAM banks */
#endif
	rtk_memory_info_init,		/* init memory info */
	rtk_package_init,	/* used for package */
	NULL,
};

int patch_for_low_temperature_boot(void);

init_fnc_t *init_sequence_r[] = {
#ifdef CONFIG_PATCH_FOR_LOW_TEMPERATURE_BOOT
	patch_for_low_temperature_boot,
#endif
#if defined(CONFIG_CUSTOMIZE_FUNC_REGISTER)
	init_customize_func,	/* init customize func feature */
#endif
#if defined(CONFIG_SYS_PCB_MANAGER) && !defined(CONFIG_CMD_KEY_BURNING)
	pcb_mgr_init,	/* initialize pinmux*/
#endif
#if defined(CONFIG_CMD_KEY_BURNING)
	set_pin_mux_burn,	/* initialize pinmux for burn*/
#endif
#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_AD83586) || defined(CONFIG_REALTEK_AMP_TAS5707_TV013)
	init_amp_prepare,
#endif
#if defined(CONFIG_DISPLAY_BOARDINFO)
	checkboard,		/* display board info */
#endif
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
	init_func_i2c,
#endif
	NULL,
};

void board_init_f(ulong bootflag)
{
	init_fnc_t **init_fnc_ptr;
#ifndef CONFIG_NO_RELOCATION
	bd_t *bd;
	gd_t *id;
	ulong addr_sp;
#endif
	ulong addr; /*, addr_heap; */
#ifdef CONFIG_PRAM
	ulong reg;
#endif

#ifdef CONFIG_BSP_REALTEK
	/* save the function address of printf in specified address */
	/* please find out PRINTF_ADDRESS in System.map 			*/
	/* 0x00020060~0x0002008F */
	extern unsigned int PRINTF_ADDRESS;
	extern unsigned int PRINTF_ADDRESS2;
	extern unsigned int PRINTF_ADDRESS3;
	extern unsigned int PRINTF_ADDRESS4; // printf
	extern unsigned int PRINTF_ADDRESS5;
	extern unsigned int PRINTF_ADDRESS6; // flush_dcache_all
	extern unsigned int PRINTF_ADDRESS7;
	extern unsigned int PRINTF_ADDRESS8;
#if 0 // prevent compile warning
	extern unsigned int UATAG_ADDRESS9;  // romcode update this for boot device info ( magic number 0xF9E8D7C6 )
	extern unsigned int UATAG_ADDRESS10; // romcode update this for boot device info
	extern unsigned int UATAG_ADDRESS11; //
	extern unsigned int UATAG_ADDRESS12; //
#endif
	*((unsigned int *)&PRINTF_ADDRESS)  = (unsigned int)0xF9E8D7C6;
	*((unsigned int *)&PRINTF_ADDRESS2) = (unsigned int)printf;
	*((unsigned int *)&PRINTF_ADDRESS3) = (unsigned int)0xF9E8D7C6;
	*((unsigned int *)&PRINTF_ADDRESS4) = (unsigned int)printf;
	*((unsigned int *)&PRINTF_ADDRESS5) = (unsigned int)0xF9E8D7C6;
	*((unsigned int *)&PRINTF_ADDRESS6) = (unsigned int)flush_dcache_all;
	*((unsigned int *)&PRINTF_ADDRESS7) = (unsigned int)0xF9E8D7C6;
	*((unsigned int *)&PRINTF_ADDRESS8) = (unsigned int)flush_cache;
#endif
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_F, "board_init_f");

#ifdef CONFIG_REALTEK_WATCHDOG
        WATCHDOG_ENABLE();
        //puts("WATCHDOG_ENABLE\n\n\n");
#else
        WATCHDOG_DISABLE();
        //puts("WATCHDOG_DISABLE\n\n\n");
#endif

	/* Pointer is writable since we allocated a register for it */
#ifdef CONFIG_NO_RELOCATION
	gd = (gd_t *) _irq_stack_start;
#else
	gd = (gd_t *) ((CONFIG_SYS_INIT_SP_ADDR) & ~0x07);
#endif

	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("": : :"memory");

	memset((void *)gd, 0, sizeof(gd_t));

	gd->mon_len = _bss_end_ofs;
#ifdef CONFIG_OF_EMBED
	/* Get a pointer to the FDT */
	gd->fdt_blob = _binary_dt_dtb_start;
#elif defined CONFIG_OF_SEPARATE
	/* FDT is at end of image */
	gd->fdt_blob = (void *)(_end_ofs + _TEXT_BASE);
#else
	//we do here
#endif
	/* Allow the early environment to override the fdt address */
	gd->fdt_blob = (void *)getenv_ulong("fdtcontroladdr", 16,
						(uintptr_t)gd->fdt_blob);

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}

#ifdef CONFIG_RTD299X
	if (GET_IC_VERSION() == VERSION_A)
	{
		#ifdef CONFIG_SYS_RAM_DCU1_SIZE
			gd->ram_size = CONFIG_SYS_RAM_DCU1_SIZE;
			#ifdef CONFIG_SYS_RAM_DCU2_SIZE
				gd->ram_size += CONFIG_SYS_RAM_DCU2_SIZE;
			#endif
		#else
			gd->ram_size = 0x10000000;
		#endif
	}
	else
	{
		gd->ram_size = get_ddr_size(0);
		if (gd->ram_size >= 0x20000000) // 512M
			gd->ram_size = 0x20000000;

		#if (CONFIG_NR_DRAM_BANKS > 1)
			gd->ram_size += get_ddr_size(1);
		#endif
	}
#elif defined(CONFIG_RTD298X)
	gd->ram_size = get_ddr_size(0);
#endif

#ifdef CONFIG_OF_CONTROL
	/* For now, put this check after the console is ready */
	if (fdtdec_prepare_fdt()) {
		panic("** CONFIG_OF_CONTROL defined but no FDT - please see "
			"doc/README.fdt-control");
	}
#endif

	debug("monitor len: %08lX\n", gd->mon_len);
	/*
	 * Ram is setup, size stored in gd !!
	 */
	debug("ramsize: %08lX\n", gd->ram_size);

#ifdef CONFIG_NO_RELOCATION
	debug("Reserving %ldk for U-Boot from : %08x\n", gd->mon_len >> 10, CONFIG_SYS_TEXT_BASE);
	debug("Stack Pointer is: %08lx\n", (ulong)_stack_start);
	debug("Reserving %zu Bytes for Global Data at: %08x\n", sizeof (gd_t), (unsigned int)gd);

	/* setup stackpointer for exeptions */
    gd->irq_sp = (ulong)_irq_stack_start;

	addr = (ulong) _irq_stack_start;
	addr += sizeof(gd_t);
    gd->bd = (bd_t *)addr;
    debug("Reserving %zu Bytes for Board Info at: %08x\n", sizeof (bd_t), (unsigned int)gd->bd);

	addr += sizeof(bd_t);

#ifdef CONFIG_HEAP_RELOCATION
	gd->heap_addr = rtk_mem_info->heap_relocation_addr;
#else
	// 4K aligned
	if (addr&(0x1000-1)) {
		addr &= ~(0x1000-1);
        addr += 0x1000;
	}

	gd->heap_addr = addr;

    addr += TOTAL_MALLOC_LEN;
#endif
	debug("Reserving %zu Bytes for Heap at: %08lx\n", TOTAL_MALLOC_LEN, gd->heap_addr);

#ifdef CONFIG_NONCACHE_ALLOCATION
	// 1MB alignment
	gd->noncache_addr = rtk_mem_info->noncache_mem_addr;
	debug("Reserving %zu Bytes for Non-cache allocation at: %08lx\n", CONFIG_SYS_NON_CACHE_LEN, gd->noncache_addr);
#endif

#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	/* round down to next 64 kB limit */
	addr &= ~(0x10000 - 1);
	addr += 0x10000;

	// check bootcode overlap
	if (addr + 0x4000 > LINUX_KERNEL_ADDR) // TLB needs 16 KB
	{
		printf("[ERROR] TLB was overlaped with kernel. (addr: 0x%08lx)\n", addr);
	}

    gd->tlb_addr = addr;
    debug("TLB table at: %08lx\n", gd->tlb_addr);
#endif

	gd->bd->bi_baudrate = gd->baudrate;
    /* Ram ist board specific, so move it to board code ... */
    dram_init_banksize();
    display_dram_config();  /* and display it */

	relocate_code(_stack_start, (gd_t *)gd, _TEXT_BASE);
#else	// !CONFIG_NO_RELOCATION
#if defined(CONFIG_SYS_MEM_TOP_HIDE)
	/*
	 * Subtract specified amount of memory to hide so that it won't
	 * get "touched" at all by U-Boot. By fixing up gd->ram_size
	 * the Linux kernel should now get passed the now "corrected"
	 * memory size and won't touch it either. This should work
	 * for arch/ppc and arch/powerpc. Only Linux board ports in
	 * arch/powerpc with bootwrapper support, that recalculate the
	 * memory size from the SDRAM controller setup will have to
	 * get fixed.
	 */
	gd->ram_size -= CONFIG_SYS_MEM_TOP_HIDE;
#endif

	addr = CONFIG_SYS_SDRAM_BASE + gd->ram_size;

#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
	/* reserve kernel log buffer */
	addr -= (LOGBUFF_RESERVE);
	debug("Reserving %dk for kernel logbuffer at %08lx\n", LOGBUFF_LEN,
		addr);
#endif
#endif

#ifdef CONFIG_PRAM
	/*
	 * reserve protected RAM
	 */
	reg = getenv_ulong("pram", 10, CONFIG_PRAM);
	addr -= (reg << 10);		/* size is in kB */
	debug("Reserving %ldk for protected RAM at %08lx\n", reg, addr);
#endif /* CONFIG_PRAM */

#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	/* reserve TLB table */
	addr -= (4096 * 4);

	/* round down to next 64 kB limit */
	addr &= ~(0x10000 - 1);

	gd->tlb_addr = addr;
	debug("TLB table at: %08lx\n", gd->tlb_addr);
#endif

	/* round down to next 4 kB limit */
	addr &= ~(4096 - 1);
	debug("Top of RAM usable for U-Boot at: %08lx\n", addr);

#ifdef CONFIG_LCD
#ifdef CONFIG_FB_ADDR
	gd->fb_base = CONFIG_FB_ADDR;
#else
	/* reserve memory for LCD display (always full pages) */
	addr = lcd_setmem(addr);
	gd->fb_base = addr;
#endif /* CONFIG_FB_ADDR */
#endif /* CONFIG_LCD */

	/*
	 * reserve memory for U-Boot code, data & bss
	 * round down to next 4 kB limit
	 */
	addr -= gd->mon_len;
	addr &= ~(4096 - 1);

	debug("Reserving %ldk for U-Boot at: %08lx\n", gd->mon_len >> 10, addr);

#ifndef CONFIG_SPL_BUILD
	/*
	 * reserve memory for malloc() arena
	 */
	addr_sp = addr - TOTAL_MALLOC_LEN;
	debug("Reserving %dk for malloc() at: %08lx\n",
			TOTAL_MALLOC_LEN >> 10, addr_sp);
	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof (bd_t);
	bd = (bd_t *) addr_sp;
	gd->bd = bd;
	debug("Reserving %zu Bytes for Board Info at: %08lx\n",
			sizeof (bd_t), addr_sp);

#ifdef CONFIG_MACH_TYPE
	gd->bd->bi_arch_number = CONFIG_MACH_TYPE; /* board id for Linux */
#endif

	addr_sp -= sizeof (gd_t);
	id = (gd_t *) addr_sp;
	debug("Reserving %zu Bytes for Global Data at: %08lx\n",
			sizeof (gd_t), addr_sp);

	/* setup stackpointer for exeptions */
	gd->irq_sp = addr_sp;
#ifdef CONFIG_USE_IRQ
	addr_sp -= (CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ);
	debug("Reserving %zu Bytes for IRQ stack at: %08lx\n",
		CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ, addr_sp);
#endif
	/* leave 3 words for abort-stack    */
	addr_sp -= 12;

	/* 8-byte alignment for ABI compliance */
	addr_sp &= ~0x07;
#else
	addr_sp += 128;	/* leave 32 words for abort-stack   */
	gd->irq_sp = addr_sp;
#endif

	debug("New Stack Pointer is: %08lx\n", addr_sp);

#ifdef CONFIG_POST
	post_bootmode_init();
	post_run(NULL, POST_ROM | post_bootmode_get(0));
#endif

	gd->bd->bi_baudrate = gd->baudrate;
	/* Ram ist board specific, so move it to board code ... */
	dram_init_banksize();
	display_dram_config();	/* and display it */

	gd->relocaddr = addr;
	gd->start_addr_sp = addr_sp;
	gd->reloc_off = addr - _TEXT_BASE;
	debug("relocation Offset is: %08lx\n", gd->reloc_off);
	memcpy(id, (void *)gd, sizeof(gd_t));

	relocate_code(addr_sp, id, addr);

	/* NOTREACHED - relocate_code() does not return */
#endif	//CONFIG_NO_RELOCATION
}

#ifdef CONFIG_BSP_REALTEK

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)
	#define BOOT_FLASH_TYPE	BOOT_EMMC
#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
	#define BOOT_FLASH_TYPE	BOOT_NAND
#else
	#define BOOT_FLASH_TYPE BOOT_NOR_SERIAL
#endif

BOOT_FLASH_T boot_flash_type = BOOT_FLASH_TYPE;	/* used to save extern param, logo, rescue */
t_extern_param *ext_para_ptr = NULL;

static int extern_param_from_SPI(void)
{
	int ret = 0;

#ifdef CONFIG_SYS_RTK_SPI_FLASH
	ext_para_ptr = (t_extern_param *) (*((unsigned int *)(BOARD_FLASH_ADDR_BASE)));
#else
	debug("[WARN] CONFIG_SYS_RTK_SPI_FLASH is undefined\n");
#endif

	return ret;
}

static int extern_param_from_NAND(void)
{
	int ret = 0;
//:TODO: Remove it in the future
#if 1
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev];		//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;

	uint blk_no = 0;
	uint data_bytes = 0;
	uint target_addr = 0;
	unsigned long long from;
	unsigned int retlen;
	unsigned int len;
	uint data_total_len = 0;

	/* Read extern parameter */
	blk_no = NAND_EXTERN_PARAM_BLOCK_NO;
	data_bytes = NAND_EXTERN_PARAM_BYTE_SIZE;
	target_addr = EXTERN_PARAM_FROM_FLASH_ADDR;

	ext_para_ptr = (t_extern_param *) target_addr;
	/* copy ext_param, logo, and rescue from nand flash to ram */
	/* logo and rescue data minimal block number would be 5!!
	block 0: profile
	block 1: bad block table
	block 2: bad block table backup
	block 3: IBT
	block 4: IBT backup
	block 5: resvered
	block 6: aux-code/hw-setting
	block 7~8: bootcode
	block 0xc: t_extern_param
	block 0xd: rescue
	*/

	from = blk_no * (nand->erasesize);
	len = data_bytes;

	nand->read(nand, from, len, &retlen, (unsigned char *)ext_para_ptr);
	if (retlen != len)
	{
		printf("[WARNING] Read extern parameter failed.\n");
		return ret;
		}

	if (ext_para_ptr->rescue_img_addr == 0 || ext_para_ptr->rescue_img_size == 0)
	{
		printf("## [WARN] rescue block no: 0x%x (size: 0x%x)\n", ext_para_ptr->rescue_img_addr, ext_para_ptr->rescue_img_size);
	}

#else
	printf("## [WARN] CONFIG_SYS_RTK_NAND_FLASH is undefined\n");
#endif
#endif
	return ret;
}

#ifdef CONFIG_MMC
static int extern_param_from_eMMC(void)
{
	int ret = 0;
//:TODO: Remove it in the future
#if 1
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	uint blk_no = 0;
	uint data_bytes = 0;
	uint target_addr = 0;

	/* Read extern parameter */
	blk_no = EMMC_EXTERN_PARAM_BLOCK_NO;
	data_bytes = EMMC_EXTERN_PARAM_SIZE;
	target_addr = EXTERN_PARAM_FROM_FLASH_ADDR;

	ext_para_ptr = (t_extern_param *) target_addr;
	if (!rtk_eMMC_read(blk_no, data_bytes, (unsigned int *)target_addr))
	{
		/* Read error */
		printf("[ERR] Read extern parameter failed. (0x%x, 0x%x, 0x%x)\n", blk_no, data_bytes, target_addr);
		return 1;
	}
	else
	{
		/* Read success */
//		printf("[OK] Read MMC data success.\n");
//		printf("rescue block no: 0x%x (size: 0x%x)\n", ext_para_ptr->rescue_img_addr, ext_para_ptr->rescue_img_size);
	}

	if (ext_para_ptr->rescue_img_addr == 0 || ext_para_ptr->rescue_img_size == 0)
	{
		printf("## [WARN] rescue block no: 0x%x (size: 0x%x)\n", ext_para_ptr->rescue_img_addr, ext_para_ptr->rescue_img_size);
	}

#ifdef CONFIG_SYS_LOGO_DISP
	// calculate length of logo that need to copy
	data_bytes = ext_para_ptr->logo_img_len;

	if (ext_para_ptr->logo2_img_len > 0)
		data_bytes += ext_para_ptr->logo2_img_len;

	if (ext_para_ptr->logo3_img_len > 0)
		data_bytes += ext_para_ptr->logo3_img_len;

	if (ext_para_ptr->logo4_img_len > 0)
		data_bytes += ext_para_ptr->logo4_img_len;

	if (ext_para_ptr->logo5_img_len > 0)
		data_bytes += ext_para_ptr->logo5_img_len;

	if (ext_para_ptr->logo6_img_len > 0)
		data_bytes += ext_para_ptr->logo6_img_len;

	if (ext_para_ptr->logo7_img_len > 0)
		data_bytes += ext_para_ptr->logo7_img_len;

	if (ext_para_ptr->logo8_img_len > 0)
		data_bytes += ext_para_ptr->logo8_img_len;

#if 1 // debug
	printf("extern_param:\n");
	printf("ext_para_ptr->rescue_img_saddr = 0x%08x\n", ext_para_ptr->rescue_img_addr);
	printf("ext_para_ptr->rescue_img_size  = 0x%08x\n", ext_para_ptr->rescue_img_size);
	printf("ext_para_ptr->logo_img_len     = 0x%08x\n", ext_para_ptr->logo_img_len);
	printf("ext_para_ptr->logo2_img_len    = 0x%08x\n", ext_para_ptr->logo2_img_len);
	printf("ext_para_ptr->logo3_img_len    = 0x%08x\n", ext_para_ptr->logo3_img_len);
	printf("ext_para_ptr->logo4_img_len    = 0x%08x\n", ext_para_ptr->logo4_img_len);
	printf("ext_para_ptr->logo5_img_len    = 0x%08x\n", ext_para_ptr->logo5_img_len);
	printf("ext_para_ptr->logo6_img_len    = 0x%08x\n", ext_para_ptr->logo6_img_len);
	printf("ext_para_ptr->logo7_img_len    = 0x%08x\n", ext_para_ptr->logo7_img_len);
	printf("ext_para_ptr->logo8_img_len    = 0x%08x\n", ext_para_ptr->logo8_img_len);
	printf("logo_data_bytes                = 0x%08x\n", data_bytes);

	printf("Logo1:\n");
	printf("ext_para_ptr->logo_img_saddr   = 0x%08x\n", ext_para_ptr->logo_img_saddr);
	printf("ext_para_ptr->logo_img_len     = 0x%08x\n", ext_para_ptr->logo_img_len);
	printf("ext_para_ptr->logo_type        = 0x%08x\n", ext_para_ptr->logo_type);
	printf("ext_para_ptr->logo_offset      = 0x%08x\n", ext_para_ptr->logo_offset);
	printf("ext_para_ptr->logo_reg_5370    = 0x%08x\n", ext_para_ptr->logo_reg_5370);
	printf("ext_para_ptr->logo_reg_5374    = 0x%08x\n", ext_para_ptr->logo_reg_5374);
	printf("ext_para_ptr->logo_reg_5378    = 0x%08x\n", ext_para_ptr->logo_reg_5378);
	printf("ext_para_ptr->logo_reg_537c    = 0x%08x\n", ext_para_ptr->logo_reg_537c);
#endif

	/* check logo exist */
	if (ext_para_ptr->rescue_img_part0_saddr == 0 || data_bytes == 0)
	{
		return ret;
	}

	/* Read logo data */
	blk_no = ext_para_ptr->rescue_img_part0_saddr;
	target_addr = ext_para_ptr->logo_img_saddr;

	if (!rtk_eMMC_read(blk_no, data_bytes, (unsigned int *)target_addr))
	{
		/* Read error */
		printf("[ERR] Read logo data failed. (0x%x, 0x%x, 0x%x)\n", blk_no, data_bytes, target_addr);
		return 1;
	}
	else
	{
		/* Read success */
//		printf("[OK] Read MMC data success.\n");
//		printf("rescue block no: 0x%x (size: 0x%x)\n", ext_para_ptr->rescue_img_part0_saddr, ext_para_ptr->rescue_img_size);
	}
#endif

#else
	printf("[WARN] CONFIG_SYS_RTK_EMMC_FLASH is undefined\n");
#endif
#endif

	return ret;
}
#endif

int rtk_FLASH_install(void)
{
	int ret = 0;

	switch(boot_flash_type)
	{
		/* nor serial SPI flash */
		case BOOT_NOR_SERIAL:
			puts("SPI...(CK skip)\n");
#if 0 // spi init
			FLASH_SPI_install();
#endif
			extern_param_from_SPI();
			break;

		/* nand flash */
		case BOOT_NAND:
			puts("NAND\n");
#if 0 // nand init
			FLASH_NAND_install();
#endif
			get_flash_shared_semaphore();
			extern_param_from_NAND();
			release_flash_shared_semaphore();
			break;

		/* eMMC */
		case BOOT_EMMC:
			printf("MMC blk:0x%x (to 0x%x)\n", EMMC_EXTERN_PARAM_BLOCK_NO, EXTERN_PARAM_FROM_FLASH_ADDR);
#if 0 // for simplify init flow ( for mmc only, SD not support )
	#ifdef CONFIG_MMC
			ret = rtk_eMMC_init();

			if (ret == 0)
				extern_param_from_eMMC();
			else
				printf("[ERR] rtk_eMMC_init failed.\n");
	#endif
#else // for standard init flow ( support sd, mmc and emmc )
	#ifdef CONFIG_GENERIC_MMC
			if( bringup_mmc_driver() >=0 ) {
				extern_param_from_eMMC();
			}
			else {
				printf("[ERR] bringup mmc failed.\n");
			}
	#else
			printf("!!! WARNING !!! NOT define CONFIG_GENERIC_MMC !!!\n");
	#endif
#endif
			break;

		default:
			printf("undefined flash type %d\n", boot_flash_type);
			return -1;
	}

	// copy t_extern_param structure to DDR for kernel use (within first 64KB area)
	memcpy((void *)UBOOT_EXTERN_PARAM_ADDR, ext_para_ptr, sizeof(t_extern_param));

	return ret;
}

/*
 * get_ddr_size()
 * @param dcu_id
 *       0: DCU1
 */
unsigned int get_ddr_size(unsigned int dcu_id)
{
	unsigned int dc_sys_misc_regBase;
	unsigned int dc_sys_misc_regValue;
	unsigned int dc_mem_density;
	unsigned int dc_mem_density_size = 0;
	unsigned int dc_mem_smaller_size_bit;
	unsigned int dc_mem_smaller_size = 0;
	unsigned int dc_mem_size;

	if (dcu_id > 1)
	{
		printf("[WARN] %s: not support dcu_id=%d\n", __FUNCTION__, dcu_id);
		return 0;
	}

	dc_sys_misc_regBase = DC_SYS_MISC_reg;

	// get dc sys setting
	dc_sys_misc_regValue = rtd_inl(dc_sys_misc_regBase);

	// get ddr density size
	dc_mem_density = (dc_sys_misc_regValue & 0x1E000000) >> 25;

	switch(dc_mem_density) {
		case 0x0:
			dc_mem_density_size = 1024;	// bits
			break;

		case 0x1:
			dc_mem_density_size = 2048;	// bits
			break;

		case 0x2:
			dc_mem_density_size = 512;	// bits
			break;

		case 0x4:
			dc_mem_density_size = 4096;	// bits
			break;

		case 0x8:
			dc_mem_density_size = 8192;	// bits
			break;

		default:
			printf("[ERR] %s: hw setting error. (impossible value 0x%x)\n", __FUNCTION__, dc_mem_density);
			break;
	}

	// get ddr mem number, dc_mem_num = 2
	if (dc_sys_misc_regValue & 0x00080000) {
		dc_mem_smaller_size_bit = (rtd_inl(DC_SYS_CTRL_reg) & 0x000000f0) >> 4;
		switch (dc_mem_smaller_size_bit) {
			case 0x0:
				dc_mem_smaller_size = dc_mem_density_size; break;
			case 0x1:
				dc_mem_smaller_size = 512; break;
			case 0x2:
				dc_mem_smaller_size = 1024; break;
			case 0x4:
				dc_mem_smaller_size = 2048; break;
			case 0x8:
				dc_mem_smaller_size = 4096; break;
			default:
         	printf("[ERR] %s: hw setting error. (impossible value 0x%x)\n", __FUNCTION__, dc_mem_smaller_size_bit);
         break;
		}
	}

	// compute ddr size
	dc_mem_size = dc_mem_density_size/8 + dc_mem_smaller_size/8;

	return (dc_mem_size << 20);
}

#ifdef CONFIG_PATCH_FOR_LOW_TEMPERATURE_BOOT
int patch_for_low_temperature_boot(void)
{
	int tml_val_t20, tml_val_cur;
	int is_2992 = 0;
	int cur_n;

#ifdef CONFIG_PATCH_FOR_LT_BOOT_2992
	is_2992 = 1;
#endif

	tml_val_t20 = (rtd_inl(0xb80381ec)&0x1F800000)>>23; //0xb80381ec[28:23] tml_value at 20 degrees
	printf("Tml Val@20: 0x%x\n", tml_val_t20); // debug use

	tml_val_cur = (rtd_inl(0xb8000280)&0x003f0000)>>16;
	printf("Cur Tml Val: 0x%x \n", tml_val_cur); // debug use

	cur_n = (rtd_inl(0xb8000534)& 0x0FF00000)>>20;
	printf("cur_n: 0x%x, efuse: 0x%x \n", cur_n, (rtd_inl(0xb80381F0) & 0x10000000));

	if( tml_val_t20 > 0 &&
		tml_val_cur >= (tml_val_t20-3) &&
		cur_n < 0x37 &&
		(rtd_inl(0xb80381F0) & 0x10000000) == 0x0 )
	{
		rtd_outl(0xb8003828, 0x00000008);        // Enter Self Refresh
		udelay(10);

		if((is_2992 == 0) && (tml_val_cur>=(tml_val_t20+3))) {     //36 degrees
			rtd_outl(0xb8000534, 0x03700000);	//769MHz

			rtd_outl(0xb8003800, 0x001CC819); // tCL:0xc(12nCK) / tCWL:0x8(8nCK) / tmCLRD:0x19(25/2=12.5)(12.5nCK)
			rtd_outl(0xb8003844, 0x00060D71); // MOD_REG01,  CL11/BC4&BL8/WR12/AL0, 34/60
			rtd_outl(0xb8003848, 0x00000018); // MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:8,  ASR disable,  dynamic ODT off.
			rtd_outl(0xb8003820, 0x08007fff); // ODT_CTRL
		}
		else if( tml_val_cur>=(tml_val_t20+1)) {//25 degrees
			rtd_outl(0xb8000534, 0x02f00000);	//661MHz

			rtd_outl(0xb8003800, 0x001CA715); // tCL:0xA(10nCK) / tCWL:0x7(7nCK) / tmCLRD:0x19(21/2=10.5)(10.5nCK)
			rtd_outl(0xb8003844, 0x00060b51); // MOD_REG01,  CL9/BC4&BL8/WR12/AL0, 34/60
			rtd_outl(0xb8003848, 0x00000010); // MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:7,  ASR disable,  dynamic ODT off.
			rtd_outl(0xb8003820, 0x08000fff); // ODT_CTRL
		}
		else if( tml_val_cur>=(tml_val_t20-1)) {//15 degrees
			rtd_outl(0xb8000534, 0x02b00000);	//607MHz

			rtd_outl(0xb8003800, 0x001CA715); // tCL:0xA(10nCK) / tCWL:0x7(7nCK) / tmCLRD:0x19(21/2=10.5)(10.5nCK)
			rtd_outl(0xb8003844, 0x00060b51); // MOD_REG01,  CL9/BC4&BL8/WR12/AL0, 34/60
			rtd_outl(0xb8003848, 0x00000010); // MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:7,  ASR disable,  dynamic ODT off.
			rtd_outl(0xb8003820, 0x08000fff); // ODT_CTRL
		}
		else if( tml_val_cur>=(tml_val_t20-3)) {//4 degrees
			rtd_outl(0xb8000534, 0x02600000);	//540MHz

			rtd_outl(0xb8003800, 0x001CA715); // tCL:0xA(10nCK) / tCWL:0x7(7nCK) / tmCLRD:0x19(21/2=10.5)(10.5nCK)
			rtd_outl(0xb8003844, 0x00060b51); // MOD_REG01,  CL9/BC4&BL8/WR12/AL0, 34/60
			rtd_outl(0xb8003848, 0x00000010); // MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:7,  ASR disable,  dynamic ODT off.
			rtd_outl(0xb8003820, 0x08000fff); // ODT_CTRL
		}
		udelay(2500);

		rtd_outl(0xb8003828, 0x00000004); // Exit Self Refresh
		udelay(10);

		rtd_outl(0xb8003840,0x0000000C);    // Exe MR0 Cmd
		rtd_outl(0xb8003840,0x000000C0);    // Exe MR2 2md
		udelay(10);
	}

	return 0;
}
#endif

#ifdef IS_BOX
int rtk_box_init(void)
{
	printf("%s\n",__FUNCTION__);

	unsigned int tmp;

	//disable AIO1 AIO2 ADCFE ADC HPO power
	tmp = rtd_inl(0xb8006b28) & ~(_BIT12|_BIT11|_BIT10|_BIT3);
	rtd_outl(0xb8006b28, tmp);
	debug("REG32(0xb8006b28) = 0x%x\n",  rtd_inl(0xb8006b28));

	//disable YPP VD+ADC power
	//--b8020000[7,6,5,2,1,0]=0
	tmp = rtd_inl(0xb8020000) & ~(_BIT7|_BIT6|_BIT5|_BIT2|_BIT1|_BIT0);
	rtd_outl(0xbb8020000, tmp);
	debug("REG32(0xb8020000) = 0x%x\n",  rtd_inl(0xb8020000));

	//disable LDO
	//--B802005c[1:0]=0
	tmp = rtd_inl(0xb802005c) & ~(_BIT1|_BIT0);
	rtd_outl(0xb802005c, tmp);
	debug("REG32(0xb802005c) = 0x%x\n",  rtd_inl(0xb802005c));

	//disable Hsync
	//--B8020064[9]=1
	tmp = rtd_inl(0xb8020064) | (_BIT9);
	rtd_outl(0xb8020064, tmp);
	debug("REG32(0xb8020064) = 0x%x\n",  rtd_inl(0xb8020064));

	//disable SCART ADC
	//--b802006c[0]=0
	tmp = rtd_inl(0xb802006c)  & ~(_BIT0);
	rtd_outl(0xb802006c, tmp);
	debug("REG32(0xb802006c) = 0x%x\n",  rtd_inl(0xb802006c));

	//0x1802_D010[7:6] = 0
	tmp = rtd_inl(0xb802d010)  & ~(_BIT7|_BIT6);
	rtd_outl(0xb802d010, tmp);
	debug("REG32(0xb802d010) = 0x%x\n",  rtd_inl(0xb802d010));

	//Close LVDS power
	//0xb800_0C78[6:0]=0
	//0xb800_0C78[15:8]=0
	//0xb800_0C78[22:16]=0
	//0xb800_0C78[30:23]=0
	tmp = rtd_inl(0xb8000c78)  & ~(_BIT30|_BIT29|_BIT28|_BIT27|_BIT26|_BIT25|_BIT24|_BIT23|_BIT22|_BIT21|_BIT20|_BIT19|_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12|_BIT11|_BIT10|_BIT9|_BIT8|_BIT6|_BIT5|_BIT4|_BIT3|_BIT2|_BIT1|_BIT0);
	rtd_outl(0xb8000c78, tmp);
	debug("REG32(0xb8000c78) = 0x%x\n",  rtd_inl(0xb8000c78));

	//0xb800_7b08[5:3] = 1
	tmp = rtd_inl(0xb8007b08) | (_BIT5|_BIT4|_BIT3);
	rtd_outl(0xb8007b08, tmp);
	debug("REG32(0xb8007b08) = 0x%x\n",  rtd_inl(0xb8007b08));

	//0xb800_7b00[29] = 0
	tmp = rtd_inl(0xb8007b00)& ~(_BIT29);
	rtd_outl(0xb8007b00, tmp);
	debug("REG32(0xb8007b00) = 0x%x\n",  rtd_inl(0xb8007b00));

	//0xb800_7b6c[3][0] = 0
	tmp = rtd_inl(0xb8007b6c)& ~(_BIT3|_BIT0);
	rtd_outl(0xb8007b6c, tmp);
	debug("REG32(0xb8007b6c) = 0x%x\n",  rtd_inl(0xb8007b6c));

	//0xb800_7b50[18:3] = 0
	tmp = rtd_inl(0xb8007b50)  & ~(_BIT18|_BIT17|_BIT16|_BIT15|_BIT14|_BIT13|_BIT12|_BIT11|_BIT10|_BIT9|_BIT8|_BIT7|_BIT6|_BIT5|_BIT4|_BIT3);
	rtd_outl(0xb8007b50, tmp);
	debug("REG32(0xb8007b50) = 0x%x\n",  rtd_inl(0xb8007b50));

	//0xb800_7be0[10:8] = 0
	tmp = rtd_inl(0xb8007be0)  & ~(_BIT10|_BIT9|_BIT8);
	rtd_outl(0xb8007be0, tmp);
	debug("REG32(0xb8007be0) = 0x%x\n",  rtd_inl(0xb8007be0));

	return 0;
}
#endif

int rtk_memory_info_init(void)
{
	uint kernel_rsv_mem_info_addr;
	uint tmp_addr1 = 0;
//	uint tmp_size1 = 0;
	uint tmp_addr2 = 0;
	uint tmp_size2 = 0;
	uint tmp_addr3 = 0;
//	uint tmp_size3 = 0;
	uint bAvailable = 0;
	uint i = 0;
	kernel_rsv_mem_info_t *rsv_mem_info;

#ifndef IS_298X_FPGA
	// check if boot from resume flow
	if ((rtd_inl(REG_CRT_SUSPEND_reg) == KERNEL_RSV_MEM_MAGICNO) && (rtd_inl(REG_STR_JUMP_ADDR_reg) != 0))
	{
		kernel_rsv_mem_info_addr = rtd_inl(REG_KERNEL_RSV_MEM_reg);

		if (kernel_rsv_mem_info_addr != 0)
		{
			rsv_mem_info = (kernel_rsv_mem_info_t *)kernel_rsv_mem_info_addr;

			if (rsv_mem_info->dwMagicNumber == KERNEL_RSV_MEM_MAGICNO)
			{
				if (rsv_mem_info->dwEntryCount < 3)
				{
					printf("[ERROR] kernel rsv memory is not enough(%d). (reset...)\n", rsv_mem_info->dwEntryCount);
					mdelay(50);
					// clear resume flag
					rtd_outl(REG_CRT_SUSPEND_reg, 0);
					rtd_outl(REG_STR_JUMP_ADDR_reg, 0);
					// clear kernel rsv mem flag
					rtd_outl(REG_KERNEL_RSV_MEM_reg, 0x0);
					// trigger watchdog reset
					disable_interrupts();
					mdelay(50);
               // kick the dog no matter it is enabled.
               rtd_outl(MIS_TCWTR, _BIT0);
               // give a any small number
               rtd_outl(MIS_TCWOV_reg, 0x19BFCC0); // around 1 sec
               // enable the dog
               rtd_clearbits(MIS_TCWCR_reg, 0xff);
               while(1);
				}
				if (rsv_mem_info->dwEntryCount > 0) // get the 1st memory region
				{
					if (rsv_mem_info->entry[0].address % 0x100000 != 0x0) // align MB
					{
						tmp_addr1 = rsv_mem_info->entry[0].address + 0x100000
									- rsv_mem_info->entry[0].address % 0x100000;
//						tmp_size1 = rsv_mem_info->entry[0].size - 0x100000
//									+ rsv_mem_info->entry[0].address % 0x100000;
					}
					else
					{
						tmp_addr1 = rsv_mem_info->entry[0].address;
//						tmp_size1 = rsv_mem_info->entry[0].size;
					}

					if (rsv_mem_info->dwEntryCount > 1) // get the 2nd memory region
					{
						tmp_addr2 = rsv_mem_info->entry[1].address;
						tmp_size2 = rsv_mem_info->entry[1].size;

						if (rsv_mem_info->dwEntryCount > 2) // get the 3rd memory region
						{
							tmp_addr3 = rsv_mem_info->entry[2].address;
//							tmp_size3 = rsv_mem_info->entry[2].size;
						}
						else
						{
							printf("[ERROR] kernel rsv memory is not enough. (count:%d)\n", rsv_mem_info->dwEntryCount);
						}
					}
					else
					{
						printf("[ERROR] kernel rsv memory is not enough. (count:%d)\n", rsv_mem_info->dwEntryCount);
					}

				}
				else
				{
					printf("[ERROR] kernel rsv memory is not enough. (count:%d)\n", rsv_mem_info->dwEntryCount);
				}

				bAvailable = 1;
			}
		}
	}

	// reset default value
	rtd_outl(REG_KERNEL_RSV_MEM_reg, 0x0);

#endif

	if (bAvailable)
	{
		// use kernel reserve memory
		rtk_mem_info->heap_relocation_addr = tmp_addr1;
		rtk_mem_info->noncache_mem_addr = tmp_addr1 + 0x100000;
		rtk_mem_info->factory_data_addr = rtk_mem_info->noncache_mem_addr + CONFIG_SYS_NON_CACHE_LEN;
		rtk_mem_info->factory_ro_data_addr = rtk_mem_info->factory_data_addr + CONFIG_FACTORY_SIZE;
		rtk_mem_info->fw_desc_table_base_addr = rtk_mem_info->factory_ro_data_addr + CONFIG_FACTORY_RO_SIZE;
		rtk_mem_info->encrypted_fw_image_addr = rtk_mem_info->fw_desc_table_base_addr + 0x10000;
		rtk_mem_info->secure_mcp_mem_buffer_addr = tmp_addr2;

		if (tmp_addr3 != 0)
			rtk_mem_info->temp_buffer_for_flash_data_addr = tmp_addr3; // use 32MB in region 3
		else
			rtk_mem_info->temp_buffer_for_flash_data_addr = tmp_addr2 + tmp_size2 - 0x400000; // use last 4MB in region 2

		printf("[krsv] use kernel reserve memory:\n");
		printf("[krsv] dwEntryCount = %d\n", rsv_mem_info->dwEntryCount);
		for(i = 0;i < rsv_mem_info->dwEntryCount;i++)
		{
			printf("[krsv] addr:0x%x size:0x%x\n", rsv_mem_info->entry[i].address, rsv_mem_info->entry[i].size);
		}
	}
	else
	{
		// use default memory
		rtk_mem_info->heap_relocation_addr = UBOOT_HEAP_RELOCATION_ADDR;
		rtk_mem_info->noncache_mem_addr = UBOOT_NONCACHE_MEMORY_ADDR;
		rtk_mem_info->factory_data_addr = FACTORY_DATA_ADDR;
		rtk_mem_info->factory_ro_data_addr = FACTORY_RO_DATA_ADDR;
		rtk_mem_info->fw_desc_table_base_addr = FIRMWARE_DESCRIPTION_TABLE_ADDR;
		rtk_mem_info->encrypted_fw_image_addr = ENCRYPTED_LINUX_KERNEL_ADDR;
		rtk_mem_info->secure_mcp_mem_buffer_addr = UBOOT_SECURE_MCP_MEMORY_ADDR;
		rtk_mem_info->temp_buffer_for_flash_data_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

		printf("[krsv] use default uboot memory:\n");
	}

#if 0 // dump mem info
	printf("[krsv] heap_relocation_addr       = 0x%x\n", rtk_mem_info->heap_relocation_addr);
	printf("[krsv] noncache_mem_addr          = 0x%x\n", rtk_mem_info->noncache_mem_addr);
	printf("[krsv] factory_data_addr          = 0x%x\n", rtk_mem_info->factory_data_addr);
	printf("[krsv] factory_ro_data_addr       = 0x%x\n", rtk_mem_info->factory_ro_data_addr);
	printf("[krsv] fw_desc_table_base_addr    = 0x%x\n", rtk_mem_info->fw_desc_table_base_addr);
	printf("[krsv] encrypted_fw_image_addr    = 0x%x\n", rtk_mem_info->encrypted_fw_image_addr);
	printf("[krsv] secure_mcp_mem_buffer_addr = 0x%x\n", rtk_mem_info->secure_mcp_mem_buffer_addr);
	printf("[krsv] temp_buffer_for_flash_data = 0x%x\n", rtk_mem_info->temp_buffer_for_flash_data_addr);
#endif

	return 0;
}

int rtk_package_init(void){

#if !defined(CONFIG_QC_VERIFY) && !defined(IS_298X_FPGA) && !defined(CONFIG_CMD_KEY_BURNING) && !defined(CONFIG_SKIP_PACKAGE_INIT)
	unsigned int package_type, flash_type, other_check, boot_type;

	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	#define PACKAGE_TYPE 0xb8060120
	#define PACKAGE_TYPE_MAG_NUM 0x298

	boot_type = 0;

#if defined(CONFIG_SYS_RTK_NAND_FLASH)
	flash_type = 0;
/*nand package start*/
#if defined(CONFIG_QFP176)
	other_check = 0;
#elif defined(CONFIG_BGA459)
	other_check = 1;
	boot_type = 1;
#elif defined(CONFIG_BOX_BGA459)
	other_check = 1;
	boot_type = 1;
#else
	#error "package type not defined"
#endif
/*nand package end*/
#elif defined(CONFIG_SYS_RTK_SPI_FLASH)
	flash_type = 1;
#elif defined(CONFIG_SYS_RTK_SPI_NAND_FLASH)
	flash_type = 2;
#elif defined(CONFIG_SYS_RTK_EMMC_FLASH)
	flash_type = 3;
/*emmc package start*/
#if defined(CONFIG_QFP176)
	other_check = 0;
#elif defined(CONFIG_BGA459) || defined(CONFIG_BOX_BGA459)
	other_check = 1;
	boot_type = 7;
#else
	#error "package type not defined"
#endif
/*emmc package end*/
#else
	#error "flash type not defined"
#endif

	package_type = ((PACKAGE_TYPE_MAG_NUM & 0xfff) << 20) | ((flash_type & 0x3) << 4) | ((other_check & 0x1) << 3) | (boot_type & 0x7);

	rtd_outl(PACKAGE_TYPE, package_type);

	printf("package type: 0x%08x\n", rtd_inl(PACKAGE_TYPE));

#endif

	return 0;
}

int rtk_bus_init(void)
{
	//printf("%s %d\n", __FUNCTION__, __LINE__);
	// use the maximum timeout value
	rtd_setbits(0xb801a010, _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

	return 0;
}

#endif

#if !defined(CONFIG_SYS_NO_FLASH)
static char *failed = "*** failed ***\n";
#endif

extern void greentable_status(void);

extern int rtl8139_initialize(bd_t *bis);

/*
 ************************************************************************
 *
 * This is the next part if the initialization sequence: we are now
 * running from RAM and have a "normal" C environment, i. e. global
 * data can be written, BSS has been cleared, the stack size in not
 * that critical any more, etc.
 *
 ************************************************************************
 */

void board_init_r(gd_t *id, ulong dest_addr)
{
	init_fnc_t **init_fnc_ptr_r;
	ulong malloc_start;
#if !defined(CONFIG_SYS_NO_FLASH)
	ulong flash_size;
#endif

#ifdef CONFIG_FAT_USE_EXTMEM_FOR_LARGE_ARRAY
	extern __u8 * get_vfatname_block;
	extern __u8 * get_dentfromdir_block;
	extern __u8 * do_fat_read_block;
	#define FAT_EXT_MEM_BASE 0x01300000
	get_vfatname_block = (__u8 *) (FAT_EXT_MEM_BASE);
	get_dentfromdir_block = (__u8 *) (FAT_EXT_MEM_BASE+0x10000);// MAX_CLUSTSIZE=65536
	do_fat_read_block = (__u8 *) (FAT_EXT_MEM_BASE+0x20000);
#endif

#ifdef CONFIG_REALTEK_WATCHDOG
	WATCHDOG_KICK();
	puts("Watchdog: Enabled\n");
#else
	puts("Watchdog: Disabled\n");
#endif
	for (init_fnc_ptr_r = init_sequence_r; *init_fnc_ptr_r; ++init_fnc_ptr_r) {
		if ((*init_fnc_ptr_r)() != 0) {
			hang ();
		}
	}

	EXECUTE_CUSTOMIZE_FUNC(0);

#ifdef CONFIG_VE_WORKAROUND
    #ifndef CONFIG_CMD_KEY_BURNING
	if (GET_IC_VERSION() == VERSION_A) // yow@workaround for VE decode failed issue
	{
		uint reg_value1;
//		uint reg_value2;

		reg_value1 = rtd_inl(TCWCR_reg);
//		reg_value2 = rtd_inl(TCWOV_reg);

		if (TCWCR_get_WDC(reg_value1) == 0)
		{
			printf("[Ver.A Patch] reset VE2 then trigger watchdog reset ...\n");

			//enable VE2 clock (SYS_CLKEN0)
			rtd_outl(0xb8000110, 0x3bb);

			//write VE2 regitser (clock gated)
			rtd_outl(0xb80354d8, 0x0);

			//do CRT reset (reset VE2 and VCPU2)
			rtd_outl(0xb8000110, 0x3);
			rtd_outl(0xb8000100, 0x8b);
			rtd_outl(0xb8000100, 0x7ff);
			rtd_outl(0xb8000110, 0x3bb);

			// trigger WD
			rtd_outl(TCWOV_reg, TCWOV_SEL(0xFFFFFFFF));
			rtd_outl(TCWCR_reg, TCWCR_WDEN(0x0));
			rtd_outl(TCWCR_reg, TCWCR_Im_wdog_rst(0x1));

			while(1)
				;
		}
	}
    #endif
#endif

#ifndef IS_298X_FPGA
	/* check if ac_on ; use 0xb806012c to detect */
	boot_ac_on = (rtd_inl(REG_AC_DC_ON_reg) == 0) ? 1 : 0;

        boot_on_fast_install_detect = (rtd_inl(REG_AC_DC_ON_reg) == 0x2379aacc) ? 1 : 0;

	printf("POWER ON: %s\n", boot_ac_on ? "AC" : "DC");

	/* fill 0x2379beef that sync from MacArthur */
	rtd_outl(REG_AC_DC_ON_reg, 0x2379beef);
#endif

/*
 *********************************************************
 * Realtek Patch:
 *	Copy several mips codes from .data section
 *	to specific ddr region for A/V CPU use.
 *********************************************************
 */
	unsigned char *a,*b;
	boot_av_info_t *boot_av;
#ifdef AUDIO_OUTPUT_AVOUT
	uint tmpValue;
#endif
	extern uint *uart_reg_base_ptr;
	extern uint *boot_av_info_ptr;
	extern uint *AudioFlag_ptr;
	extern uint *VideoFlag_ptr_V1;
	extern uint *VideoFlag_ptr_V2;
	extern uint *KcpuFlag_ptr;
	extern uint *AudioFW_entry_ptr;
	extern uint *VideoFW_entry_ptr_V1;
	extern uint *VideoFW_entry_ptr_V2;
	extern uint *shared_printk_buffer_ptr;
	extern uint *audio_output_info_ptr;
	extern uint	*KcpuFW_entry_ptr;

	// copy .exc_redirect (MIPS exception redirect)
	a = (unsigned char *)&_e_exc_redirect_img;
	b = (unsigned char *)&_f_exc_redirect_img;
	memcpy((unsigned char *)MIPS_EXC_REDIRECT_CODE_ADDR, b, a-b);

	// copy .exc_dispatch (MIPS exception dispatch)
	a = (unsigned char *)&_e_exc_dispatch_img;
	b = (unsigned char *)&_f_exc_dispatch_img;
	memcpy((unsigned char *)MIPS_EXC_DISPATCH_CODE_ADDR, b, a-b);

	// copy .v_entry (VCPU1/2 bootcode)
	a = (unsigned char *)&_e_v_entry_img;
	b = (unsigned char *)&_f_v_entry_img;
	memcpy((unsigned char *)MIPS_V_ENTRY_CODE_ADDR, b, a-b);

#ifdef ENABLE_DDR_CALIBRATION
	unsigned int _iDiSramBase;
	unsigned int _i;
	unsigned int _len;

	// enable DI memshare
	enable_ccdinr_memshare();

	// copy .v_ddr_cal (VCPU1/2 ddr calibration code) to DI-sram
	a = (unsigned char *)&_e_v_ddr_cal_img;
	b = (unsigned char *)&_f_v_ddr_cal_img;
	_len = (a - b) / 4;

	if (_len > DI_SRAM_MEM_SHARE_SIZE)
	{
		printf("[ERR] v_ddr_cal.img out of memory. (_len=%x)\n", _len);
	}

	_iDiSramBase = MIPS_V_DDR_CAL_CODE_reg;
	for( _i = 0 ; _i < _len; _i++ ) {
//		printf("[%03d] write 0x%08x 0x%08x\n", _i, _iDiSramBase, SWAPEND32(*((unsigned int *)b + _i)));
		rtd_outl(_iDiSramBase, SWAPEND32(*((unsigned int *)b + _i)));
		_iDiSramBase += 4;
	}

	// copy .v_ddr_cal_c (VCPU1 ddr calibration C code) to DI-sram
	a = (unsigned char *)&_e_v_ddr_cal_c_img;
	b = (unsigned char *)&_f_v_ddr_cal_c_img;
	_len = (a - b) / 4;

	if (_len > DI_SRAM_MEM_SHARE_SIZE)
	{
		printf("[ERR] v_ddr_cal_c.img out of memory. (_len=%x)\n", _len);
	}

	_iDiSramBase = MIPS_V_DDR_CAL_C_CODE_reg;
	for( _i = 0 ; _i < _len; _i++ ) {
//		printf("[%03d] write 0x%08x 0x%08x\n", _i, _iDiSramBase, SWAPEND32(*((unsigned int *)b + _i)));
		rtd_outl(_iDiSramBase, SWAPEND32(*((unsigned int *)b + _i)));
		_iDiSramBase += 4;
	}
#endif

	/*
	 * fill the VCPU jump address.
	 * ROM code will use it to decide VCPU jump address.
	 *     => if enable BISR testing, not run code in cache segment.
	 *     => if enable ddr calibration, run v_ddr_cal code in DI-sram.
	 *              after ddr calibration, v_ddr_cal will jump to v_entry.
	 */
#ifdef ENABLE_DDR_CALIBRATION
	rtd_outl(REG_DDR_CAL_FLAG_reg, 0); // clear ddr calibration flag
	rtd_outl(VCPU_JUMP_ADDR_reg, (MIPS_V_DDR_CAL_CODE_reg) | MIPS_KSEG1BASE);
#else
	#ifdef ENABLE_VCPU_BISR
		rtd_outl(VCPU_JUMP_ADDR_reg, MIPS_V_ENTRY_CODE_ADDR | MIPS_KSEG1BASE);
	#else
		rtd_outl(VCPU_JUMP_ADDR_reg, MIPS_V_ENTRY_CODE_ADDR | MIPS_KSEG0BASE);
	#endif
#endif

	// copy .isrvideoimg (video cpu isr handler)
	a = (unsigned char *)&_e_isrvideo_img;
	b = (unsigned char *)&_f_isrvideo_img;
	memcpy((unsigned char *)MIPS_ISR_VIDEO_IMG_ADDR, b, a-b);

	// copy .rosbootvectorimg (MIPS vector interrupt)
	a = (unsigned char *)&_e_rosbootvector_img;
	b = (unsigned char *)&_f_rosbootvector_img;
	memcpy((unsigned char *)MIPS_ROS_BOOT_VECTOR_IMG_ADDR, b, a-b);

	// copy .a_entry (ACPU bootcode)
	a = (unsigned char *)&_e_a_entry_img;
	b = (unsigned char *)&_f_a_entry_img;
	memcpy((unsigned char *)MIPS_A_ENTRY_CODE_ADDR, b, a-b);

#ifdef CONFIG_LOAD_AUDIO2_IMAGE // this image is used by bootloader command ( cmd_bootcodeloader.c )
	// copy .a_entry_polling_0xa000000e (ACPU bootcode)
	a = (unsigned char *)&_e_a_entry_polling_0xa000000e_img;
	b = (unsigned char *)&_f_a_entry_polling_0xa000000e_img;
	memcpy((unsigned char *)MIPS_A_ENTRY2_CODE_ADDR, b, a-b);
#endif
	// fill the ACPU jump address.
	// After ACPU got HW semaphore in rom code, it will check this register.
#ifdef ENABLE_ACPU_BISR
	rtd_outl(ACPU_JUMP_ADDR_reg, MIPS_A_ENTRY_CODE_ADDR | MIPS_KSEG1BASE);
#else
	rtd_outl(ACPU_JUMP_ADDR_reg, MIPS_A_ENTRY_CODE_ADDR | MIPS_KSEG0BASE);
#endif

	// fill the UART register base address for A/V CPU.
	*uart_reg_base_ptr = SWAPEND32(CONFIG_SYS_NS16550_COM1 | 0xb0000000);

#ifdef SHARED_CONSOLE_UART // sync from Macarthur
	if (CONSOLE_UART == PCB_UART_1) {
		*uart_reg_base_ptr = SWAPEND32(0xb801b100);
	} else if (CONSOLE_UART == PCB_UART_2) {
		*uart_reg_base_ptr = SWAPEND32(0xb801b200);
	} else if (CONSOLE_UART == PCB_UART_3) {
		*uart_reg_base_ptr = SWAPEND32(0xb801b300);
	} else {
		*uart_reg_base_ptr = SWAPEND32(0xb8061300);
	}
#endif

	*boot_av_info_ptr = 0;
	*AudioFlag_ptr = 0;
	*VideoFlag_ptr_V1 = 0;
	*VideoFlag_ptr_V2 = 0;
	memset(KcpuFlag_ptr, 0x0, sizeof(*KcpuFlag_ptr)*4);
	*AudioFW_entry_ptr = 0;
	*VideoFW_entry_ptr_V1 = 0;
	*VideoFW_entry_ptr_V2 = 0;
	*KcpuFW_entry_ptr = 0;
	memset(shared_printk_buffer_ptr, 0, MIPS_SHARED_PRINTK_BUFFER_SIZE);
	memset(audio_output_info_ptr, 0, MIPS_AUDIO_OUTPUT_INFO_SIZE);

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

#ifdef AUDIO_OUTPUT_AVOUT
	audio_output_info_ptr[0] = SWAPEND32(0x2452544B);  // magic $RTK
	tmpValue = AUDIO_OUTPUT_AVOUT | 0x41; // 'A'
	audio_output_info_ptr[1] = SWAPEND32(tmpValue);
	tmpValue = AUDIO_OUTPUT_SPEAKER_OUT | 0x53; // 'S'
	audio_output_info_ptr[2] = SWAPEND32(tmpValue);
	tmpValue = AUDIO_OUTPUT_HEADPHONE_OUT | 0x50; // 'P'
	audio_output_info_ptr[3] = SWAPEND32(tmpValue);
#endif

	gd = id;

	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_R, "board_init_r");

	monitor_flash_len = _end_ofs;

	/* Enable caches */
	enable_caches();

	debug("monitor flash len: %08lX\n", monitor_flash_len);
	board_init();	/* Setup chipselects */

	/*
	 * TODO: printing of the clock inforamtion of the board is now
	 * implemented as part of bdinfo command. Currently only support for
	 * davinci SOC's is added. Remove this check once all the board
	 * implement this.
	 */
#ifdef CONFIG_CLOCKS
	set_cpu_clk_info(); /* Setup clock information */
#endif
#ifdef CONFIG_SERIAL_MULTI
	serial_initialize();
#endif

#ifdef CONFIG_NO_RELOCATION
	debug("Now running in RAM - U-Boot at: %08lx\n", _TEXT_BASE);
#else
	debug("Now running in RAM - U-Boot at: %08lx\n", dest_addr);
#endif

#ifdef CONFIG_LOGBUFFER
	logbuff_init_ptrs();
#endif
#ifdef CONFIG_POST
	post_output_backlog();
#endif

	/* The Malloc area is immediately below the monitor copy in DRAM */
#ifdef CONFIG_NO_RELOCATION
	malloc_start = gd->heap_addr;
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN);
#else
	malloc_start = dest_addr - TOTAL_MALLOC_LEN;
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN);
#endif

#ifdef CONFIG_NONCACHE_ALLOCATION
    mem_malloc_noncache_init(gd->noncache_addr, CONFIG_SYS_NON_CACHE_LEN);
#endif

#ifdef CONFIG_ARCH_EARLY_INIT_R
	arch_early_init_r();
#endif

#if !defined(CONFIG_SYS_NO_FLASH)
	puts("Flash: ");

	flash_size = flash_init();
	if (flash_size > 0) {
# ifdef CONFIG_SYS_FLASH_CHECKSUM
		char *s = getenv("flashchecksum");

		print_size(flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		if (s && (*s == 'y')) {
			printf("  CRC: %08X", crc32(0,
				(const unsigned char *) CONFIG_SYS_FLASH_BASE,
				flash_size));
		}
		putc('\n');
# else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size(flash_size, "\n");
# endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts(failed);
		hang();
	}
#endif

#if defined(CONFIG_CMD_NAND)
	puts("NAND:  ");
	get_flash_shared_semaphore();
	nand_init();		/* go init the NAND */
	release_flash_shared_semaphore();
#endif

#if defined(CONFIG_CMD_ONENAND)
	onenand_init();
#endif

#ifdef CONFIG_GENERIC_MMC
	puts("MMC:   ");
	mmc_initialize(gd->bd);

	EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

	if(bringup_mmc_driver() < 0) {
		printf("[ERR] bringup mmc failed.\n");
	}
#endif

	EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

	puts("Extern param: ");
	rtk_FLASH_install();

#ifdef CONFIG_SYS_FACTORY
	puts("Factory: ");
	factory_init();
	get_bootparam();
	get_layout();
#endif

#if defined(CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC)
	 if(boot_power_on_mode == POWER_ON) {
                IO_Set(PIN_LED_ON_OFF, 1);
        }
#endif

#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_AD83586) || defined(CONFIG_REALTEK_AMP_TAS5707_TV013)
	init_amp();
#endif

//wangzhh add for power on pop

	EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

#ifdef CONFIG_SYS_FACTORY_READ_ONLY
	puts("Factory_RO: ");
	factory_ro_init();
#endif

#ifdef CONFIG_HAS_DATAFLASH
	AT91F_DataflashInit();
	dataflash_print_info();
#endif

	/* initialize environment */
	env_relocate();

	EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

#if defined(CONFIG_PANEL_SHARP_60_MEMC) || defined(CONFIG_PANEL_SHARP_NT71912_MEMC)
	I2C_Init();
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

	if (tstc()) {	/* we got a key press from UART */ //if key=delete, skip panel_init
		int console_key = getc();
		if (console_key == 0x7f)
			boot_mode = BOOT_CONSOLE_MODE;
	}

#if defined(CONFIG_SYS_PANEL_SUPPORT)
	/* panel parameters setting */
	panel_init();
#endif
#ifdef IS_BOX
	rtk_box_init(); /* used for box */
#endif

	EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

#ifdef CONFIG_SYS_LOGO_DISP
	puts("Logo: ");
	LOGO_DISP_init(); // after panel init
#endif

#if defined(CONFIG_CMD_PCI) || defined(CONFIG_PCI)
	arm_pci_init();
#endif

	stdio_init();	/* get the devices list going. */

	jumptable_init();

#if defined(CONFIG_API)
	/* Initialize API */
	api_init();
#endif

	console_init_r();	/* fully init console as a device */

#if defined(CONFIG_ARCH_MISC_INIT)
	/* miscellaneous arch dependent initialisations */
	arch_misc_init();
#endif
#if defined(CONFIG_MISC_INIT_R)
	/* miscellaneous platform dependent initialisations */
	misc_init_r();
#endif

	 /* set up exceptions */
	interrupt_init();
	/* enable exceptions */
	enable_interrupts();

	/* Perform network card initialisation if necessary */
#if defined(CONFIG_DRIVER_SMC91111) || defined (CONFIG_DRIVER_LAN91C96)
	/* XXX: this needs to be moved to board init */
	if (getenv("ethaddr")) {
		uchar enetaddr[6];
		eth_getenv_enetaddr("ethaddr", enetaddr);
		smc_set_mac_addr(enetaddr);
	}
#endif /* CONFIG_DRIVER_SMC91111 || CONFIG_DRIVER_LAN91C96 */

	/* Initialize from environment */
	load_addr = getenv_ulong("loadaddr", 16, load_addr);

#ifdef CONFIG_BOARD_LATE_INIT
	board_late_init();
#endif

#if 1 // move from greentable_modify() to reduce 60ms delay time
	greentable_status();
#endif

#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif
#if defined(CONFIG_CMD_NET)
	puts("Net:   ");
#ifdef CONFIG_BSP_REALTEK
	rtl8139_initialize(gd->bd);
#else
	eth_initialize(gd->bd);
#endif
#if defined(CONFIG_RESET_PHY_R)
	debug("Reset Ethernet PHY\n");
	reset_phy();
#endif
#endif

#ifdef CONFIG_POST
	post_run(NULL, POST_RAM | post_bootmode_get(0));
#endif

#if defined(CONFIG_PRAM) || defined(CONFIG_LOGBUFFER)
	/*
	 * Export available size of memory for Linux,
	 * taking into account the protected RAM at top of memory
	 */
	{
		ulong pram = 0;
		uchar memsz[32];

#ifdef CONFIG_PRAM
		pram = getenv_ulong("pram", 10, CONFIG_PRAM);
#endif
#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
		/* Also take the logbuffer into account (pram is in kB) */
		pram += (LOGBUFF_LEN + LOGBUFF_OVERHEAD) / 1024;
#endif
#endif
		sprintf((char *)memsz, "%ldk", (gd->ram_size / 1024) - pram);
		setenv("mem", (char *)memsz);
	}
#endif

      WATCHDOG_KICK();

	/* main_loop() can return to retry autoboot, if so just run it again. */
	for (;;) {
		main_loop();
	}

	/* NOTREACHED - no way out of command loop except booting */
}

void hang(void)
{
	puts("### ERROR ### Please RESET the board ###\n");
	for (;;);
}
