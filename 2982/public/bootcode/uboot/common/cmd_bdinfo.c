/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <linux/compiler.h>
#if defined(CONFIG_RTD299X)
#include <rbus/crt_reg.h>
#elif defined(CONFIG_RTD298X)
#include <rbus/crt_sys_reg.h>
#endif

#include <asm/arch/io.h>
#include <asm/arch/system.h>

DECLARE_GLOBAL_DATA_PTR;

__maybe_unused
static void print_num(const char *name, ulong value)
{
	printf("%-12s= 0x%08lX\n", name, value);
}

__maybe_unused
static void print_eth(int idx)
{
	char name[10], *val;
	if (idx)
		sprintf(name, "eth%iaddr", idx);
	else
		strcpy(name, "ethaddr");
	val = getenv(name);
	if (!val)
		val = "(not set)";
	printf("%-12s= %s\n", name, val);
}

__maybe_unused
static void print_lnum(const char *name, u64 value)
{
	printf("%-12s= 0x%.8llX\n", name, value);
}

__maybe_unused
static void print_mhz(const char *name, unsigned long hz)
{
	char buf[32];

	printf("%-12s= %6s MHz\n", name, strmhz(buf, hz));
}

#if defined(CONFIG_PPC)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

#ifdef DEBUG
	print_num("bd address",		(ulong)bd);
#endif
	print_num("memstart",		bd->bi_memstart);
	print_lnum("memsize",		bd->bi_memsize);
	print_num("flashstart",		bd->bi_flashstart);
	print_num("flashsize",		bd->bi_flashsize);
	print_num("flashoffset",	bd->bi_flashoffset);
	print_num("sramstart",		bd->bi_sramstart);
	print_num("sramsize",		bd->bi_sramsize);
#if	defined(CONFIG_5xx)  || defined(CONFIG_8xx) || \
	defined(CONFIG_8260) || defined(CONFIG_E500)
	print_num("immr_base",		bd->bi_immr_base);
#endif
	print_num("bootflags",		bd->bi_bootflags);
#if	defined(CONFIG_405CR) || defined(CONFIG_405EP) || \
	defined(CONFIG_405GP) || \
	defined(CONFIG_440EP) || defined(CONFIG_440EPX) || \
	defined(CONFIG_440GR) || defined(CONFIG_440GRX) || \
	defined(CONFIG_440SP) || defined(CONFIG_440SPE) || \
	defined(CONFIG_XILINX_405)
	print_mhz("procfreq",		bd->bi_procfreq);
	print_mhz("plb_busfreq",	bd->bi_plb_busfreq);
#if	defined(CONFIG_405EP) || defined(CONFIG_405GP) || \
	defined(CONFIG_440EP) || defined(CONFIG_440EPX) || \
	defined(CONFIG_440GR) || defined(CONFIG_440GRX) || \
	defined(CONFIG_440SPE) || defined(CONFIG_XILINX_405)
	print_mhz("pci_busfreq",	bd->bi_pci_busfreq);
#endif
#else	/* ! CONFIG_405GP, CONFIG_405CR, CONFIG_405EP, CONFIG_XILINX_405, CONFIG_440EP CONFIG_440GR */
#if defined(CONFIG_CPM2)
	print_mhz("vco",		bd->bi_vco);
	print_mhz("sccfreq",		bd->bi_sccfreq);
	print_mhz("brgfreq",		bd->bi_brgfreq);
#endif
	print_mhz("intfreq",		bd->bi_intfreq);
#if defined(CONFIG_CPM2)
	print_mhz("cpmfreq",		bd->bi_cpmfreq);
#endif
	print_mhz("busfreq",		bd->bi_busfreq);
#endif /* CONFIG_405GP, CONFIG_405CR, CONFIG_405EP, CONFIG_XILINX_405, CONFIG_440EP CONFIG_440GR */
#if defined(CONFIG_MPC8220)
	print_mhz("inpfreq",		bd->bi_inpfreq);
	print_mhz("flbfreq",		bd->bi_flbfreq);
	print_mhz("pcifreq",		bd->bi_pcifreq);
	print_mhz("vcofreq",		bd->bi_vcofreq);
	print_mhz("pevfreq",		bd->bi_pevfreq);
#endif

#ifdef CONFIG_ENABLE_36BIT_PHYS
#ifdef CONFIG_PHYS_64BIT
	puts("addressing  = 36-bit\n");
#else
	puts("addressing  = 32-bit\n");
#endif
#endif

	print_eth(0);
#if defined(CONFIG_HAS_ETH1)
	print_eth(1);
#endif
#if defined(CONFIG_HAS_ETH2)
	print_eth(2);
#endif
#if defined(CONFIG_HAS_ETH3)
	print_eth(3);
#endif
#if defined(CONFIG_HAS_ETH4)
	print_eth(4);
#endif
#if defined(CONFIG_HAS_ETH5)
	print_eth(5);
#endif

#ifdef CONFIG_HERMES
	print_mhz("ethspeed",		bd->bi_ethspeed);
#endif
	printf("IP addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %6ld bps\n", bd->bi_baudrate);
	print_num("relocaddr", gd->relocaddr);
	return 0;
}

#elif defined(CONFIG_NIOS2)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("mem start",		(ulong)bd->bi_memstart);
	print_lnum("mem size",		(u64)bd->bi_memsize);
	print_num("flash start",	(ulong)bd->bi_flashstart);
	print_num("flash size",		(ulong)bd->bi_flashsize);
	print_num("flash offset",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_SYS_SRAM_BASE)
	print_num ("sram start",	(ulong)bd->bi_sramstart);
	print_num ("sram size",		(ulong)bd->bi_sramsize);
#endif

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif

	printf("baudrate    = %ld bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_MICROBLAZE)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;
	print_num("mem start      ",	(ulong)bd->bi_memstart);
	print_lnum("mem size       ",	(u64)bd->bi_memsize);
	print_num("flash start    ",	(ulong)bd->bi_flashstart);
	print_num("flash size     ",	(ulong)bd->bi_flashsize);
	print_num("flash offset   ",	(ulong)bd->bi_flashoffset);
#if defined(CONFIG_SYS_SRAM_BASE)
	print_num("sram start     ",	(ulong)bd->bi_sramstart);
	print_num("sram size      ",	(ulong)bd->bi_sramsize);
#endif
#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %ld bps\n", (ulong)bd->bi_baudrate);
	return 0;
}

#elif defined(CONFIG_SPARC)

int do_bdinfo(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

#ifdef DEBUG
	print_num("bd address             ", (ulong) bd);
#endif
	print_num("memstart               ", bd->bi_memstart);
	print_lnum("memsize                ", bd->bi_memsize);
	print_num("flashstart             ", bd->bi_flashstart);
	print_num("CONFIG_SYS_MONITOR_BASE       ", CONFIG_SYS_MONITOR_BASE);
	print_num("CONFIG_ENV_ADDR           ", CONFIG_ENV_ADDR);
	printf("CONFIG_SYS_RELOC_MONITOR_BASE = 0x%lx (%d)\n", CONFIG_SYS_RELOC_MONITOR_BASE,
	       CONFIG_SYS_MONITOR_LEN);
	printf("CONFIG_SYS_MALLOC_BASE        = 0x%lx (%d)\n", CONFIG_SYS_MALLOC_BASE,
	       CONFIG_SYS_MALLOC_LEN);
	printf("CONFIG_SYS_INIT_SP_OFFSET     = 0x%lx (%d)\n", CONFIG_SYS_INIT_SP_OFFSET,
	       CONFIG_SYS_STACK_SIZE);
	printf("CONFIG_SYS_PROM_OFFSET        = 0x%lx (%d)\n", CONFIG_SYS_PROM_OFFSET,
	       CONFIG_SYS_PROM_SIZE);
	printf("CONFIG_SYS_GBL_DATA_OFFSET    = 0x%lx (%d)\n", CONFIG_SYS_GBL_DATA_OFFSET,
	       GENERATED_GBL_DATA_SIZE);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate               = %6ld bps\n", bd->bi_baudrate);
	return 0;
}

#elif defined(CONFIG_M68K)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);
#if defined(CONFIG_SYS_INIT_RAM_ADDR)
	print_num("sramstart",		(ulong)bd->bi_sramstart);
	print_num("sramsize",		(ulong)bd->bi_sramsize);
#endif
#if defined(CONFIG_SYS_MBAR)
	print_num("mbar",		bd->bi_mbar_base);
#endif
	print_mhz("cpufreq",		bd->bi_intfreq);
	print_mhz("busfreq",		bd->bi_busfreq);
#ifdef CONFIG_PCI
	print_mhz("pcifreq",		bd->bi_pcifreq);
#endif
#ifdef CONFIG_EXTRA_CLOCK
	print_mhz("flbfreq",		bd->bi_flbfreq);
	print_mhz("inpfreq",		bd->bi_inpfreq);
	print_mhz("vcofreq",		bd->bi_vcofreq);
#endif
#if defined(CONFIG_CMD_NET)
	print_eth(0);
#if defined(CONFIG_HAS_ETH1)
	print_eth(1);
#endif
#if defined(CONFIG_HAS_ETH2)
	print_eth(2);
#endif
#if defined(CONFIG_HAS_ETH3)
	print_eth(3);
#endif

	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %ld bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_BLACKFIN)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	printf("U-Boot      = %s\n", bd->bi_r_version);
	printf("CPU         = %s\n", bd->bi_cpu);
	printf("Board       = %s\n", bd->bi_board_name);
	print_mhz("VCO",	bd->bi_vco);
	print_mhz("CCLK",	bd->bi_cclk);
	print_mhz("SCLK",	bd->bi_sclk);

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %d bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_MIPS)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %d bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_AVR32)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("memstart",		(ulong)bd->bi_memstart);
	print_lnum("memsize",		(u64)bd->bi_memsize);
	print_num("flashstart",		(ulong)bd->bi_flashstart);
	print_num("flashsize",		(ulong)bd->bi_flashsize);
	print_num("flashoffset",	(ulong)bd->bi_flashoffset);

	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	printf("baudrate    = %lu bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_ARM)

#if 0 // cklai@mark unused code
static int do_bdinfo_dss(void)
{
	uint regValue = 0;

	printf("*** bdinfo dss ***\n");

	//DSS1 dc_phy 0xb8008f50
	rtd_outl(SS_12T_LVT_0_reg, 0x00000000); //DSS1 reset
	rtd_outl(SS_12T_LVT_0_reg, 0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_12T_LVT_0_reg, 0x00000013); //DSS1 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_12T_LVT_1_reg); //count_out[23:4]
	printf("DSS1 DC_PHY   = 0x%05x\n", ((regValue & SS_12T_LVT_1_count_out_mask) >> SS_12T_LVT_1_count_out_shift));

	//DSS2 dc2_phy 0xb8003f50
	rtd_outl(0xb8003f50,0x00000000); //DSS2 reset
	rtd_outl(0xb8003f50,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb8003f50,0x00000013); //DSS2 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb8003f54); //count_out[23:4]
	printf("DSS2 DC2_PHY  = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS3 SCPU_phy 0xb805_c008
	rtd_outl(0xb805c008,0x00000000); //DSS3 reset
	rtd_outl(0xb805c008,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb805c008,0x00000013); //DSS3 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb805c010); //count_out[23:4]
	printf("DSS3 SCPU_PHY = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS4 SCPU_phy 0xb805_c000
	rtd_outl(0xb805c000,0x00000000); //DSS4 reset
	rtd_outl(0xb805c000,0x00000012); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(0xb805c000,0x00000013); //DSS4 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(0xb805c004); //count_out[23:4]
	printf("DSS4 SCPU_PHY = 0x%05x\n", ((regValue & 0x00FFFFF0) >> 4));

	//DSS5 VCPU 0xb800_0298
	rtd_outl(SS_12T_RVT_0_reg,0x00000000); //DSS5 reset
	rtd_outl(SS_12T_RVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_12T_RVT_0_reg,0x83000000); //DSS5 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_12T_RVT_0_reg); //count_out[19:0]
	printf("DSS5 VCPU     = 0x%05x\n", ((regValue & SS_12T_RVT_0_rvt_12t_count_out_mask) >> SS_12T_RVT_0_rvt_12t_count_out_shift));

	//DSS6 VCPU2 0xb800_0340
	rtd_outl(SS_9T_LVT_0_reg,0x00000000); //DSS6 reset
	rtd_outl(SS_9T_LVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_9T_LVT_0_reg,0x83000000); //DSS6 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_9T_LVT_0_reg); //count_out[19:0]
	printf("DSS6 VCPU2    = 0x%05x\n", ((regValue & SS_9T_LVT_0_lvt_9t_count_out_mask) >> SS_9T_LVT_0_lvt_9t_count_out_shift));

	//DSS7 VCPU2 0xb800_0348
	rtd_outl(SS_9T_RVT_0_reg,0x00000000); //DSS7 reset
	rtd_outl(SS_9T_RVT_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_9T_RVT_0_reg,0x83000000); //DSS7 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_9T_RVT_0_reg); //count_out[19:0]
	printf("DSS7 VCPU2    = 0x%05x\n", ((regValue & SS_9T_RVT_0_rvt_9t_count_out_mask) >> SS_9T_RVT_0_rvt_9t_count_out_shift));

	//DSS8 tv_sb1 0xb801_c3f0
	rtd_outl(SS_7T_0_reg,0x00000000); //DSS8 reset
	rtd_outl(SS_7T_0_reg,0x03000000); //wire_sel=1'b1, ro_sel=3'b001
	rtd_outl(SS_7T_0_reg,0x83000000); //DSS8 enable
	mdelay(500);		// wait done
	regValue = rtd_inl(SS_7T_0_reg); //count_out[19:0]
	printf("DSS8 TV_SB1   = 0x%05x\n", ((regValue & SS_7T_0_rlvt_7t_count_out_mask) >> SS_7T_0_rlvt_7t_count_out_shift));

	return 0;
}
#endif

static int do_bdinfo_ddr(void)
{
	printf("*** bdinfo ddr ***\n");
	printf("DDR    SIZE  = %4d MB  (Evaluated from DC1 0x%x)\n", get_ddr_size(0) >> 20, DC_SYS_MISC_reg);
#if defined(CONFIG_RTD299X)
	printf("DDR    SIZE  = %4d MB  (Evaluated from DC2 0x%x)\n", get_ddr_size(1) >> 20, DC2_SYS_MISC_reg);
#endif
	return 0;
}

static int do_bdinfo_pll(void)
{
	char   msg[64];
	uint value_m, value_n, value_o;
	uint freq, tmp;
	uint div;

	printf("*** bdinfo pll ***\n");

	// get SCPU PLL MNO value
	if ((rtd_inl(SYS_PLL_SCPU2_reg) & SYS_PLL_SCPU2_pllscpu_oeb_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_SCPU1_reg);
		value_m = ((tmp & SYS_PLL_SCPU1_pllscpu_m_mask) >> SYS_PLL_SCPU1_pllscpu_m_shift);
		value_n = ((tmp & SYS_PLL_SCPU1_pllscpu_n_mask) >> SYS_PLL_SCPU1_pllscpu_n_shift);
		value_o = ((tmp & SYS_PLL_SCPU1_pllscpu_o_mask) >> SYS_PLL_SCPU1_pllscpu_o_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
#if defined(CONFIG_BOARD_298X_TV038_QFP176_V3_EMMC_VER1)
	sprintf( msg, "%4d MHz", freq+100 );
#else
	sprintf( msg, "%4d MHz", freq );
#endif
	printf("SCPU   PLL   = %s\n", msg);

	// get GPU PLL MNO value
	if ((rtd_inl(SYS_PLL_GPU2_reg) & SYS_PLL_GPU2_pllgpu_oeb_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_GPU1_reg);
		value_m = ((tmp & SYS_PLL_GPU1_pllgpu_m_mask) >> SYS_PLL_GPU1_pllgpu_m_shift);
		value_n = ((tmp & SYS_PLL_GPU1_pllgpu_n_mask) >> SYS_PLL_GPU1_pllgpu_n_shift);
		value_o = ((tmp & SYS_PLL_GPU1_pllgpu_o_mask) >> SYS_PLL_GPU1_pllgpu_o_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
	sprintf( msg, "%4d MHz", freq );
	printf("GPU    PLL   = %s\n", msg);

	// get GCPU_L2 PLL MNO value
	if ((rtd_inl(SYS_PLL_2_GPU2_reg) & SYS_PLL_2_GPU2_pllgpu_oeb_2_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_2_GPU1_reg);
		value_m = ((tmp & SYS_PLL_2_GPU1_pllgpu_m_2_mask) >> SYS_PLL_2_GPU1_pllgpu_m_2_shift);
		value_n = ((tmp & SYS_PLL_2_GPU1_pllgpu_n_2_mask) >> SYS_PLL_2_GPU1_pllgpu_n_2_shift);
		value_o = ((tmp & SYS_PLL_2_GPU1_pllgpu_o_2_mask) >> SYS_PLL_2_GPU1_pllgpu_o_2_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
	sprintf( msg, "%4d MHz", freq );
	printf("GPU_L2 PLL   = %s\n", msg);

	// get BUS PLL MNO value
#if defined(CONFIG_RTD299X)
	if ((rtd_inl(ST_BUSCLK_reg) & ST_BUSCLK_bus_clksel_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_BUS1_reg);
		value_m = ((tmp & SYS_PLL_BUS1_pllbus_m_mask) >> SYS_PLL_BUS1_pllbus_m_shift);
		value_n = ((tmp & SYS_PLL_BUS1_pllbus_n_mask) >> SYS_PLL_BUS1_pllbus_n_shift);

		tmp = rtd_inl(SYS_PLL_BUS3_reg);
		value_o = ((tmp & SYS_PLL_BUS3_pllbus_o_mask) >> SYS_PLL_BUS3_pllbus_o_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
#elif defined(CONFIG_RTD298X)
	if ((rtd_inl(SYS_PLL_BUS3_reg) & SYS_PLL_BUS3_REG_PLLBUS_OEB_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_BUS1_reg);
		value_m = ((tmp & SYS_PLL_BUS1_REG_PLLBUS_M_mask) >> SYS_PLL_BUS1_REG_PLLBUS_M_shift);
		value_n = ((tmp & SYS_PLL_BUS1_REG_PLLBUS_N_mask) >> SYS_PLL_BUS1_REG_PLLBUS_N_shift);
		value_o = ((tmp & SYS_PLL_BUS1_REG_PLLBUS_O_mask) >> SYS_PLL_BUS1_REG_PLLBUS_O_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
#endif
	sprintf( msg, "%4d MHz", freq );
	printf("BUS    PLL   = %s (RBus = %d MHz)\n", msg, freq / 2);

	// get BUSH PLL MNO value
#if defined(CONFIG_RTD299X)
	if ((rtd_inl(ST_BUSCLK_reg) & ST_BUSCLK_bus_clksel_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_H_BUS1_reg);
		value_m = ((tmp & SYS_PLL_H_BUS1_pllbus_m_h_mask) >> SYS_PLL_H_BUS1_pllbus_m_h_shift);
		value_n = ((tmp & SYS_PLL_H_BUS1_pllbus_n_h_mask) >> SYS_PLL_H_BUS1_pllbus_n_h_shift);

		tmp = rtd_inl(SYS_PLL_H_BUS3_reg);
		value_o = ((tmp & SYS_PLL_H_BUS3_pllbus_o_h_mask) >> SYS_PLL_H_BUS3_pllbus_o_h_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
#elif defined(CONFIG_RTD298X)
	if ((rtd_inl(SYS_PLL_DCSB3_reg) & SYS_PLL_DCSB3_REG_PLLBUS_OEB_H_mask) == 0) {
		tmp = rtd_inl(SYS_PLL_DCSB1_reg);
		value_m = ((tmp & SYS_PLL_DCSB1_REG_PLLBUS_M_H_mask) >> SYS_PLL_DCSB1_REG_PLLBUS_M_H_shift);
		value_n = ((tmp & SYS_PLL_DCSB1_REG_PLLBUS_N_H_mask) >> SYS_PLL_DCSB1_REG_PLLBUS_N_H_shift);
		value_o = ((tmp & SYS_PLL_DCSB1_REG_PLLBUS_O_H_mask) >> SYS_PLL_DCSB1_REG_PLLBUS_O_H_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
#endif
	sprintf( msg, "%4d MHz", freq );
	printf("BUSH   PLL   = %s\n", msg);

	// get DDR PLL N value and div
#if defined(CONFIG_RTD299X)
	tmp = rtd_inl(SYS_PLL_DDR2_reg);
	div = ((tmp & SYS_PLL_DDR2_reg_pdiv_mask) >> SYS_PLL_DDR2_reg_pdiv_shift);
	tmp = rtd_inl(SYS_PLL_DDR_SSC2_reg);
	value_n = ((tmp & SYS_PLL_DDR_SSC2_reg_n_code_mask) >> SYS_PLL_DDR_SSC2_reg_n_code_shift);
	freq = (27 * (value_n + 2)) >> div;
#elif defined(CONFIG_RTD298X)
	tmp = rtd_inl(SYS_PLL_DDR_SSC2_reg);
	value_n = ((tmp & SYS_PLL_DDR_SSC2_reg_dpi_n_code_mask) >> SYS_PLL_DDR_SSC2_reg_dpi_n_code_shift);
	freq = (27 * (value_n + 3));
#endif

	if (freq != 0)
		sprintf( msg, "%4d MHz", freq / 2);
	else
		sprintf( msg, "--- MHz");

	printf("DDR    PLL   = %s (DC1 VCO Freq = %4d MHz)\n", msg, freq);

	// get DDR2 PLL N value and div
#if defined(CONFIG_RTD299X)
	tmp = rtd_inl(SYS_PLL_DDR2_2_reg);
	div = ((tmp & SYS_PLL_DDR2_2_reg_pdiv_mask) >> SYS_PLL_DDR2_2_reg_pdiv_shift);
	tmp = rtd_inl(SYS_PLL_DDR_SSC2_2_reg);
	value_n = ((tmp & SYS_PLL_DDR_SSC2_2_reg_n_code_mask) >> SYS_PLL_DDR_SSC2_2_reg_n_code_shift);
	freq = (27 * (value_n + 2)) >> div;

	if (freq != 0)
		sprintf( msg, "%4d MHz", freq / 2);
	else
		sprintf( msg, "--- MHz");

	printf("DDR    PLL   = %s (DC2 VCO Freq = %4d MHz)\n", msg, freq);
#endif

	// get ACPU PLL MNO value
#if defined(CONFIG_RTD299X)
	if ((rtd_inl(SYS_CPUSEL_reg) & SYS_CPUSEL_acpu_clksel_mask) == 0)
#elif defined(CONFIG_RTD298X)
	if ((rtd_inl(SYS_PLL_ACPU2_reg) & SYS_PLL_ACPU2_pllacpu_oeb_mask) == 0)
#endif
	{
		tmp = rtd_inl(SYS_PLL_ACPU1_reg);
		value_m = ((tmp & SYS_PLL_ACPU1_pllacpu_m_mask) >> SYS_PLL_ACPU1_pllacpu_m_shift);
		value_n = ((tmp & SYS_PLL_ACPU1_pllacpu_n_mask) >> SYS_PLL_ACPU1_pllacpu_n_shift);
		value_o = ((tmp & SYS_PLL_ACPU1_pllacpu_o_mask) >> SYS_PLL_ACPU1_pllacpu_o_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
	}
	else {
		freq = 27;
	}
	sprintf( msg, "%4d MHz", freq );
	printf("ACPU   PLL   = %s\n", msg);

	// get VCPU PLL MNO value
	if ((rtd_inl(SYS_PLL_VCPU2_reg) & SYS_PLL_VCPU2_pllvcpu_oeb_mask) == 0)
	{
		tmp = rtd_inl(SYS_PLL_VCPU1_reg);
		value_m = ((tmp & SYS_PLL_VCPU1_pllvcpu_m_mask) >> SYS_PLL_VCPU1_pllvcpu_m_shift);
		value_n = ((tmp & SYS_PLL_VCPU1_pllvcpu_n_mask) >> SYS_PLL_VCPU1_pllvcpu_n_shift);
		value_o = ((tmp & SYS_PLL_VCPU1_pllvcpu_o_mask) >> SYS_PLL_VCPU1_pllvcpu_o_shift);
		freq = 27 * (value_m+2) / (value_n+1) / (value_o+1);
		sprintf( msg, "%4d MHz", freq );
	}
	else {
		sprintf( msg, "--- MHz");
	}
	printf("VCPU   PLL   = %s\n", msg);

	return 0;
}

void do_bdinfo_spi (void);
static int do_bdinfo_flash (void)
{
#ifdef CONFIG_CMD_SPI_FLASH_DRIVER
	do_bdinfo_spi();
#endif

	return 0;
}


int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	if (argc == 2) {
		if (strcmp(argv[1], "rtpll") == 0) {
			return do_bdinfo_pll();
		}
		else if (strcmp(argv[1], "rtddr") == 0) {
			return do_bdinfo_ddr();
		}
		else if (strcmp(argv[1], "rtflash") == 0) {
			return do_bdinfo_flash();
		}
//		else if (strcmp(argv[1], "dss") == 0) {
//			return do_bdinfo_dss();
//		}
		else {
			return CMD_RET_USAGE;
		}
	}

	print_num("arch_number",	bd->bi_arch_number);
	print_num("boot_params",	(ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %d bps\n", bd->bi_baudrate);
#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	print_num("TLB addr", gd->tlb_addr);
#endif
#ifndef CONFIG_BSP_REALTEK
	print_num("relocaddr", gd->relocaddr);
	print_num("reloc off", gd->reloc_off);
	print_num("irq_sp", gd->irq_sp);	/* irq stack pointer */
	print_num("sp start ", gd->start_addr_sp);
	print_num("FB base  ", gd->fb_base);
#endif
	/*
	 * TODO: Currently only support for davinci SOC's is added.
	 * Remove this check once all the board implement this.
	 */
#ifdef CONFIG_CLOCKS
	printf("ARM frequency = %ld MHz\n", gd->bd->bi_arm_freq);
	printf("DSP frequency = %ld MHz\n", gd->bd->bi_dsp_freq);
	printf("DDR frequency = %ld MHz\n", gd->bd->bi_ddr_freq);
#endif

//	do_bdinfo_pll();
//	do_bdinfo_ddr();
//	do_bdinfo_flash();
//	do_bdinfo_dss();

	return 0;
}

#elif defined(CONFIG_SH)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;
	print_num("mem start      ",	(ulong)bd->bi_memstart);
	print_lnum("mem size       ",	(u64)bd->bi_memsize);
	print_num("flash start    ",	(ulong)bd->bi_flashstart);
	print_num("flash size     ",	(ulong)bd->bi_flashsize);
	print_num("flash offset   ",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %ld bps\n", (ulong)bd->bi_baudrate);
	return 0;
}

#elif defined(CONFIG_X86)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("boot_params",	(ulong)bd->bi_boot_params);
	print_num("bi_memstart",	bd->bi_memstart);
	print_num("bi_memsize",		bd->bi_memsize);
	print_num("bi_flashstart",	bd->bi_flashstart);
	print_num("bi_flashsize",	bd->bi_flashsize);
	print_num("bi_flashoffset",	bd->bi_flashoffset);
	print_num("bi_sramstart",	bd->bi_sramstart);
	print_num("bi_sramsize",	bd->bi_sramsize);
	print_num("bi_bootflags",	bd->bi_bootflags);
	print_mhz("cpufreq",		bd->bi_intfreq);
	print_mhz("busfreq",		bd->bi_busfreq);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
	print_mhz("ethspeed",	    bd->bi_ethspeed);
#endif
	printf("baudrate    = %d bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_SANDBOX)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("boot_params", (ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank", i);
		print_num("-> start", bd->bi_dram[i].start);
		print_num("-> size", bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	print_num("FB base  ", gd->fb_base);
	return 0;
}

#elif defined(CONFIG_NDS32)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	bd_t *bd = gd->bd;

	print_num("arch_number",	bd->bi_arch_number);
	print_num("boot_params",	(ulong)bd->bi_boot_params);

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; ++i) {
		print_num("DRAM bank",	i);
		print_num("-> start",	bd->bi_dram[i].start);
		print_num("-> size",	bd->bi_dram[i].size);
	}

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %d bps\n", bd->bi_baudrate);

	return 0;
}

#elif defined(CONFIG_OPENRISC)

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	bd_t *bd = gd->bd;

	print_num("mem start",		(ulong)bd->bi_memstart);
	print_lnum("mem size",		(u64)bd->bi_memsize);
	print_num("flash start",	(ulong)bd->bi_flashstart);
	print_num("flash size",		(ulong)bd->bi_flashsize);
	print_num("flash offset",	(ulong)bd->bi_flashoffset);

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif

	printf("baudrate    = %ld bps\n", bd->bi_baudrate);

	return 0;
}

#else
 #error "a case for this architecture does not exist!"
#endif

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	bdinfo,	2,	1,	do_bdinfo,
	"print Board Info structure",
	""
);