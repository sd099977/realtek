#include <common.h>
#include <command.h>
#include <linux/compiler.h>
#if defined(CONFIG_RTD299X)
#include <rbus/crt_reg.h>
#elif defined(CONFIG_RTD298X)
#include <rbus/crt_sys_reg.h>
#endif
#include <asm/arch/io.h>

#define	SETBIT(x,n)		x = x | (1<<n)
#define	CLRBIT(x,n)		x = x & ~(1<<n)
#define SetBit(addr, nbit)	  	*((volatile unsigned int *) (addr-0xa0000000)) |= 1<<nbit
#define ResetBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) &= ~(1<<nbit)
#define ToggleBit(addr, nbit)	*((volatile unsigned int *) (addr-0xa0000000)) ^= 1<<nbit
#define WReg(addr, data)		*((volatile unsigned int *) (addr-0xa0000000)) = data
#define RReg(addr) 		    	*((volatile unsigned int *) (addr-0xa0000000))

#define rtd_inl		RReg
#define rtd_outl	WReg

#define WIRE_SEL		2
#define RO_SEL			5
//DSS1_DC_PHY type1
#define DSS1_REG_CTRL1	0xb8008f50
#define DSS1_REG_CTRL2	0xb8008f54
//DSS2_DC2_PHY type1
#define DSS2_REG_CTRL1	0xb8003f50
#define DSS2_REG_CTRL2	0xb8003f54
//DSS3_SCPU	type1
#define DSS3_REG_CTRL1	0xb805c008
#define DSS3_REG_CTRL2	0xb805c010
//DSS4_SCPU	type1
#define DSS4_REG_CTRL1	0xb805c000
#define DSS4_REG_CTRL2	0xb805c004
//DSS5_VCPU type2
#define DSS5_REG_CTRL1	0xb8000298
#define DSS5_REG_CTRL2	0xb800029C
//DSS6_VCPU2 type2
#define DSS6_REG_CTRL1	0xb8000340
#define DSS6_REG_CTRL2	0xb8000344
//DSS7_VCPU2 type2
#define DSS7_REG_CTRL1	0xb8000348
#define DSS7_REG_CTRL2	0xb800034C
//DSS8_TV_SB1 type2
#define DSS8_REG_CTRL1	0xb801C3F0
#define DSS8_REG_CTRL2	0xb801C3F4

//addr = simple_strtoul(argv[1], NULL, 16);
//	        x = simple_strtoul(argv[2], NULL, 10);
//	        y = simple_strtoul(argv[3], NULL, 10);

void rtd_part_outl(unsigned int addr, unsigned int B, unsigned int C, unsigned int D)
{
    unsigned int X,A,value;
	X=(1<<(B-C+1))-1;
	A=RReg(addr);
	value = (A & (~(X<<C))) | (D<<C);
	WReg(addr,value);	

//    return ((A&(~(X<<C)))|(D<<C));
}


unsigned int rtd_part_inl(unsigned int addr, unsigned int B, unsigned int C)
{
    unsigned int X,A;
	X=(1<<(B-C+1))-1;
	A=RReg(addr);
    return (A>>C)&X;
}

unsigned int part_value(unsigned int value, unsigned int B, unsigned int C)
{
	unsigned int X,A;
	X=(1<<(B-C+1))-1;
	A=value;
    return (A>>C)&X;
}

void do_dss_type1_cal(unsigned int REG_CRTL1, unsigned int REG_CRTL2, int DSS_CLK)
{
	int wire_sel,ro_sel;
	unsigned int DSS[WIRE_SEL][RO_SEL]={{0}};

//	float value1,value2;
	int value;
	printf("DSS_CLK = %dMHz delay_time=CNT/(DSS_CLK*16384)\n",DSS_CLK);
	for(wire_sel=0;wire_sel<2;wire_sel++){
		ResetBit(REG_CRTL1,0); //DSS  reset
		rtd_part_outl(REG_CRTL1,4,4,wire_sel); //wire_sel

		for(ro_sel=1;ro_sel<6;ro_sel++){
			rtd_part_outl(REG_CRTL1,3,1,ro_sel); //ro_sel
			SetBit(REG_CRTL1,0);
			while(1){
				if(rtd_part_inl(REG_CRTL2,0,0) == 1){
					DSS[wire_sel][ro_sel] = rtd_part_inl(REG_CRTL2,23,4);
					break;
				}
			}
		}
	}



	for(wire_sel=0;wire_sel<2;wire_sel++){
		for(ro_sel=1;ro_sel<6;ro_sel++){
			value = DSS[wire_sel][ro_sel]*1000/DSS_CLK*1000/16384;
			printf("CNT[%d][%d]=%05d  delay_time=%04d ps\n",wire_sel,ro_sel,DSS[wire_sel][ro_sel],value);
		}
	}

}


void do_dss_type2_cal(unsigned int REG_CRTL1, unsigned int REG_CRTL2, unsigned int DSS_CLK)
{
	int wire_sel,ro_sel;
	unsigned int DSS[WIRE_SEL][RO_SEL]={{0}};

//	float value1,value2;
	int value;
	printf("DSS_CLK = %dMHz delay_time=CNT/(DSS_CLK*16384)\n",DSS_CLK);
	for(wire_sel=0;wire_sel<2;wire_sel++){
		ResetBit(REG_CRTL1,31); //DSS  reset
		rtd_part_outl(REG_CRTL1,24,24,wire_sel); //wire_sel
		for(ro_sel=1;ro_sel<6;ro_sel++){
			rtd_part_outl(REG_CRTL1,27,25,ro_sel); //ro_sel
			SetBit(REG_CRTL1,31);
			while(1){
				if(rtd_part_inl(REG_CRTL1,20,20) == 1){
					DSS[wire_sel][ro_sel] = rtd_part_inl(REG_CRTL1,19,0);
					break;
				}
			}
		}
	}

	for(wire_sel=0;wire_sel<2;wire_sel++){
		for(ro_sel=1;ro_sel<6;ro_sel++){
			value = DSS[wire_sel][ro_sel]*1000/DSS_CLK*1000/16384;
			printf("CNT[%d][%d]=%05d  delay_time=%04d ps\n",wire_sel,ro_sel,DSS[wire_sel][ro_sel],value);
		}
	}

}

unsigned int pll_bus_freq(void)
{
	unsigned int M, N, O, FOUT;
	M = rtd_part_inl(0xb8000420,24,18);
	N = rtd_part_inl(0xb8000420,26,25);
	O = rtd_part_inl(0xb8000428,3,3);

	//printf("M=%d N=%d O=%d\n",M,N,O);
	//printf("FOUT = 27*(M+2)/(N+1)/(O+1)\n");
	FOUT = (unsigned int) (27*(M+2)/(N+1)/(O+1));
    return FOUT;
}

unsigned int pll_ddr_freq(void)
{
	unsigned int N_CODE, F_CODE, FOUT;
	N_CODE = rtd_part_inl(0xb8000514,27,20);
	F_CODE = rtd_part_inl(0xb8000514,16,4);

	//printf("N_CODE=%d F_CODE=%d \n",N_CODE,F_CODE);
	//printf("FOUT = 13.5*(N_CODE+2+F_CODE/8192)\n");
	FOUT = (unsigned int) (13.5*(N_CODE+2+F_CODE/8192));
    return FOUT;
}


int do_dssinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int PLL_BUS_CLK, PLL_DDR_CLK;
//	unsigned int DSS_CLK1, DSS_CLK2;
	/*
	int i;
	bd_t *bd = gd->bd;

	if (argc == 2) {
		if (strcmp(argv[1], "pll") == 0) {
			return do_bdinfo_pll();
		}
		else if (strcmp(argv[1], "ddr") == 0) {
			return do_bdinfo_ddr();
		}
		else if (strcmp(argv[1], "dss") == 0) {
			return do_bdinfo_dss();
		}
		else {
			return CMD_RET_USAGE;
		}
	}
	*/

	PLL_BUS_CLK = pll_bus_freq();
	PLL_DDR_CLK = pll_ddr_freq();
//	DSS_CLK1 = PLL_BUS_CLK/2;
//	DSS_CLK2 = PLL_DDR_CLK/2;

	printf("\nPLL BUS FREQ = %dMHz\n",PLL_BUS_CLK);
	printf("PLL DDR FREQ = %dMHz\n",PLL_DDR_CLK);

	printf("\nDSS1 DC_PHY(12T,LVT)\n");
	printf("start\n");
	do_dss_type1_cal(DSS1_REG_CTRL1,DSS1_REG_CTRL2,(PLL_DDR_CLK/2));
	printf("done\n");

	printf("\nDSS2 DC2_PHY(12T,LVT)\n");
	printf("start\n");
	do_dss_type1_cal(DSS2_REG_CTRL1,DSS2_REG_CTRL2,(PLL_DDR_CLK/2));
	printf("done\n");

	printf("\nDSS3 SCPU(12T,LVT)\n");
	printf("start\n");
	do_dss_type1_cal(DSS3_REG_CTRL1,DSS3_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");

	printf("\nDSS4 SCPU(12T,RVT)\n");
	printf("start\n");
	do_dss_type1_cal(DSS4_REG_CTRL1,DSS4_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");


	printf("\nDSS5 VCPU(12T,RVT)\n");
	printf("start\n");
	do_dss_type2_cal(DSS5_REG_CTRL1,DSS5_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");


	printf("\nDSS6 VCPU2(9T,LVT)\n");
	printf("start\n");
	do_dss_type2_cal(DSS6_REG_CTRL1,DSS6_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");


	printf("\nDSS7 VCPU2(9T,RVT)\n");
	printf("start\n");
	do_dss_type2_cal(DSS7_REG_CTRL1,DSS7_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");


	printf("\nDSS8 TV_SB1(7T)\n");
	printf("start\n");
	do_dss_type2_cal(DSS8_REG_CTRL1,DSS8_REG_CTRL2,(PLL_BUS_CLK/2));
	printf("done\n");

	return CMD_RET_SUCCESS;
}


U_BOOT_CMD(
	dssinfo, 2,	1,	do_dssinfo,
	"print dss",
	"dss information\n"
);
