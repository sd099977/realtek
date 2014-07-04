/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "reset_def.h"
#include "emcu.h"
#include "svnver.h"
#include "ris_app.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define USE_HWSETTING_PARSER
#define KCPU_WAIT_HW_SEM

#define DELAY_PATCH
#define PROCESS_DTE_KBOOT

#if defined(KCPU_WAIT_HW_SEM)
#define KCPU_WAIT_HW_SEM_REG      0xb801a630
#define KCPU_WAIT_JUMP_DUMMY_REG  0xb8060124
#endif

#if defined(USE_HWSETTING_PARSER)
#define HWSETTING_STRING "HP"
#else
#define HWSETTING_STRING "CF"
#endif

#define REG_AC_DC_ON_reg		(0xb8060128) /* register which represent AC or DC on */
/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned int error_code = 0xff;

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int get_boot_flash_type(void);
extern int get_secure_boot_type(void);

extern int process_certificate(const int flash_type, const int secure_type);
extern int process_params(const int flash_type, const int secure_type);
extern int process_aux_code(const int flash_type, const int secure_type);

extern void load_rom_symbol(void);
extern int is_warm_boot(void);
extern int resume_from_suspend(void);
#if defined(USE_HWSETTING_PARSER)
extern int init_hwsetting_c(const int flash_type);
#else
extern int init_hwsetting(void);
#endif
extern int init_memory(void);
extern int process_dte_bootcode(const int flash_type, const int secure_type);
extern void go_ddr(void);
extern int download_8051_imem(const int flash_type);
extern void dcache_flush_invalidate(void);
/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/
static void kcpu_wait(void);
static void kcpu_jump_to_kboot(void);
static void init_uart(void);
#if defined(DELAY_PATCH)
static void delay_patch(void);
#endif
static void enable_scpu_clk(void);
static int boot_flow(const int flash_type, const int secure_type);

/************************************************************************
 *  Function body
 ************************************************************************/

static void kcpu_wait(void) {
#if defined(KCPU_WAIT_HW_SEM)
	unsigned int i;
	void (*jump) (void);
	//hold hw semaphore
	REG32(KCPU_WAIT_HW_SEM_REG) = 0x1;

	while(1)
	{
		if(REG32(KCPU_WAIT_HW_SEM_REG) == 0x1)
		{
			printf("\nKCPU jump to address = 0x%x\n", REG32(KCPU_WAIT_JUMP_DUMMY_REG));
			jump = (void *) (REG32(KCPU_WAIT_JUMP_DUMMY_REG));
			jump();
		}
		for (i = 0;i < 1024;i++);
	}
#else
	while(1);
#endif
}

static void kcpu_jump_to_kboot(void) {
	void (*jump) (void);

	//hold hw semaphore
	REG32(KCPU_WAIT_HW_SEM_REG) = 0x1;

	jump = (void *) (0x99f00000);
	jump();
}

static void init_uart(void)
{
	//enable uart0 tx
	rtd_maskl(0xb8060204, 0x07ffffff, 0x48000000);

	//enable uart1 tx
	rtd_maskl(0xb8000844, 0x07ffffff, 0x10000000);
}

#if defined(DELAY_PATCH)
static void delay_patch(void)
{
	unsigned int timeout_cnt;

	//bypass other (only for VerB)
	if (rtd_inl(0xb8060000) != 0x63300001)
		return;

#if 0
	//bypass DC ON
	if (rtd_inl(REG_AC_DC_ON_reg) == 0x2379beef)
		return;
#endif
	debug("%s: watch dog reg 0x%x\n", __FUNCTION__, rtd_inl(0xb801b6f0));

	timeout_cnt = (rtd_inl(0xb801b6f0) >> 8) & 0xf;

	if ((timeout_cnt & 0x1) == 0x0) {
		//for debug
		rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, 0x168);
		//trigger watchdog 4sec
		rtd_maskl(0xb801b6f0, ~0xff, 0xa5);
		rtd_outl(0xb801b6fc, 0x68d7a4d);
		rtd_maskl(0xb801b6f0, ~0xff, 0x33);
		while(1);
	}

	return;
}
#endif

static void enable_scpu_clk(void)
{
	debug("\n%s %d\n", __FUNCTION__, __LINE__);

	int cpu_nr;
	unsigned int cpu_pwr;

	// set powerup_hammer and powerup_trickle based on OTP bit
	cpu_nr = 4 - (((rtd_inl(0xb8017194) & 0x00030000)) >> 16);
	if (cpu_nr == 1) {
		cpu_pwr = 0x11e;
	}
	else if (cpu_nr == 2) {
		cpu_pwr = 0x33c;
	}
	else if (cpu_nr == 3) {
		cpu_pwr = 0x778;
	}
	else {
		cpu_pwr = 0xff0;
	}

	//enable scpu clock (only-DP)
	// clk_dis (bit 1,2,3)
	// reset   (bit 4,8)
	// reset   (bit 25,26)
	// release (bit 8)
	// clk_en  (bit 3)
	// configure wrapper
	// release (bit 4)
	// release (bit 25,26)
	// clk_en  (bit 1,2)
	rtd_clearbits(0xb8000010, _BIT1 | _BIT2 | _BIT3);
	rtd_clearbits(0xb8000004, _BIT4 | _BIT8);
	rtd_clearbits(0xb8000008, _BIT25 | _BIT26);
	rtd_setbits(0xb8000004, _BIT8);
	rtd_setbits(0xb8000010, _BIT3);
	rtd_outl(0xb801C868, 0x00000fff);
	rtd_outl(0xb801c850, 0x400ffff0);
	rtd_outl(0xb801c878, 0x00000703);
	rtd_outl(0xb801c854, 0x00001f00);
	rtd_outl(0xb801C868, cpu_pwr);
	rtd_setbits(0xb8000004, _BIT4);
	rtd_setbits(0xb8000008, _BIT25 | _BIT26);
	rtd_setbits(0xb8000010, _BIT1 | _BIT2);
}

static int boot_flow(const int flash_type, const int secure_type)
{
	int res = 0;

	/* process Certificate */
	if ((res = process_certificate(flash_type, secure_type))) {
		return res;
	}

	/* process Parameter Area */
	if ((res = process_params(flash_type, secure_type))) {
		return res;
	}

	/* process Auxiliary code */
	if ((res = process_aux_code(flash_type, secure_type))) {
		return res;
	}

	return res;
}

#ifdef CONFIG_RIS_APP
static void kcpu_jump_to_RiscureApp(void) {
	void (*jump) (void);

	//hold hw semaphore
	REG32(KCPU_WAIT_HW_SEM_REG) = 0x1;

	jump = (void *) (0xa0020000);
	jump();
}
#endif

/* main function in Aux code */
int app_main(int argc, char **argv)
{
	int res = 0;
	int flash_type, secure_type;
	unsigned int exist_kboot = 0;

	init_uart();

#if defined(DELAY_PATCH)
	delay_patch();
#endif

	// hold the semaphore to block MIPS CPUs
	rtd_inl(0xb801a000);

#if defined(DEBUG)
	// disable watch dog
	rtd_maskl(0xb801b6f0, ~0xff, 0xa5);
#endif

	printf("\nHello world!{uni}[%s]", HWSETTING_STRING);
#if defined(DELAY_PATCH)
	if (rtd_inl(KCPU_WAIT_JUMP_DUMMY_REG) == 0x168) {
		printf("@");
		rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, 0x0);
	}
#endif
	printf(" svn%s (%s %s)\n", SVN_REV, __DATE__, __TIME__);

	flash_type = get_boot_flash_type();
	secure_type = get_secure_boot_type();

	debug("flash_type = %d, secure_type = %d\n", flash_type, secure_type);

#if defined(DEBUG)
	hexdump("OTP data", (char *)0xb8017000, 0x380);
#endif

	if ((res = boot_flow(flash_type, secure_type))) {
		printf("boot_flow error: 0x%x\n", res);
	}

	if (is_warm_boot()) {
		resume_from_suspend();
	}

#if defined(USE_HWSETTING_PARSER)
	init_hwsetting_c(flash_type);
#else
	init_hwsetting();
#endif
	init_memory();

	if ((res = process_dte_bootcode(flash_type, secure_type))) {
		printf("process_dte_bootcode error: 0x%x\n", res);
		while(1);
	}

#ifdef PROCESS_DTE_KBOOT
	res = process_dte_kboot(flash_type, secure_type, &exist_kboot);
	if (res) {
		printf("process_dte_kboot error: 0x%x\n", res);
//		while(1); // temp mark for kboot test
	}

	if (exist_kboot)
		printf("[go kb]\n");
	else
		printf("[no kb]\n");
#endif

#ifndef CONFIG_RIS_APP
	if ((res = download_8051_imem(flash_type))) {
		printf("download_8051_imem error: 0x%x\n", res);
	}
#else
	printf("Skip download 8051 !!!\n");
#endif

	go_ddr();

	dcache_flush_invalidate();

	// release flash shared semaphore for kcpu/scpu access
	rtd_outl(0xb801a62c, 0x0);

	enable_scpu_clk();

#ifndef CONFIG_RIS_APP
	if (exist_kboot)
		kcpu_jump_to_kboot();
	else
		kcpu_wait();
#else
	// for Riscure test
	kcpu_jump_to_RiscureApp();

#endif


	return res;
}
