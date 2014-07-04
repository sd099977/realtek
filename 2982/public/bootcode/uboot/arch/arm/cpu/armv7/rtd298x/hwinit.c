/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 */

#include <common.h>
#include <asm/armv7.h>
#include <asm/sizes.h>
#include <config.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <rbus/crt_sys_reg.h>
#include <asm/arch/rbus/iso_reg.h>

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_BSP_REALTEK // mark unused code
unsigned int cortex_rev(void)
{

    unsigned int rev;

    /* Read Main ID Register (MIDR) */
    asm ("mrc p15, 0, %0, c0, c0, 0" : "=r" (rev));

    return rev;
}
#endif

/*
 *
 */
#define MAX_MDIO_TIMEOUT 		100
#define MIIAR           		0xb801605c
#define MDIO_WRITE			0x80000000
#define SET_FUSE_RDY_CHANGE_PAGE_A46	0x041f0a46
#define SET_FUSE_RDY_INIT_DONE_FLAG	0x04140003

unsigned int mdio_read_complete(unsigned int reg) {
	unsigned int iTimeoutCounter;
	unsigned int iRegVal;
	unsigned int value = 0;

	rtd_outl(MIIAR, (reg & ~MDIO_WRITE));
	for( iTimeoutCounter = 0; iTimeoutCounter < MAX_MDIO_TIMEOUT; iTimeoutCounter++ ) {
		iRegVal = rtd_inl(MIIAR);
		//printf("cnt=%02d : Reg(MIIAR)=0x%08x\n", iTimeoutCounter, iRegVal);
		if( (reg | MDIO_WRITE) == (iRegVal & 0xffff0000))  {
			value = iRegVal & 0x0000ffff;
			break;
		}
		udelay(10);
	}
	if( iTimeoutCounter == MAX_MDIO_TIMEOUT ) {
		printf("MISC : read MIIAR with %08x fail\n", reg);
	}

	return value;
}

void mdio_write_complete(unsigned int reg) {
	unsigned int iTimeoutCounter;
	unsigned int iRegVal;

	rtd_outl(MIIAR, (reg|MDIO_WRITE));
	for( iTimeoutCounter = 0; iTimeoutCounter < MAX_MDIO_TIMEOUT; iTimeoutCounter++ ) {
		iRegVal = rtd_inl(MIIAR);
		//printf("cnt=%02d : Reg(MIIAR)=0x%08x\n", iTimeoutCounter, iRegVal);
		if( iRegVal == (reg & ~MDIO_WRITE) ) {
			break;
		}
		udelay(10);
	}
	if( iTimeoutCounter == MAX_MDIO_TIMEOUT ) {
		printf("MISC : update MIIAR with %08x fail\n", reg);
	}
}

void getn_load_efusedata2DOUT(void){

	unsigned int val, val1, val2;
	unsigned int R_cal_value;
	unsigned int ib_up, ib_dn, amp_dn_fine;
#ifdef DBG
	unsigned int RC_cal_value, amp_dn;
#endif

/****************************************************************************************
	amp_cal value[23:16]= amp_dn_fine [1:0]port A ...[7:6]port D page bcc/reg20 [7:0]
	amp_cal value[15:8]= gdac_ib_dn page bcc/reg18 [15:8]
	amp_cal value[7:0]= gdac_ib_up page bcc/reg18 [7:0]
*******************************************************************************************/

	val1 = rtd_inl(0xb80381e4);
	val2 = rtd_inl(0xb80381e8);

	if ((val1&_BIT31)&&(val2&_BIT31)){//efuse have burned
		//R,RC can be overwrite
		mdio_write_complete(0x841f0a42);// change Page to a42
		mdio_write_complete(0x841b8013);//write reg27 = 0x8013
		mdio_write_complete(0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over

		R_cal_value = ((val2>>15)&0xf);
		//RC_cal_value = ((val2>>19)&0xf);
#ifdef DBG
		amp_dn =  ((val2>>19)&0x7);
#endif
		amp_dn_fine = (val1&0xff);//amp_cal value[23:16]
		ib_dn = ((val1>>17)&0xff);//amp_cal value[15:8]
		ib_up = ((val1>>9)&0xff);//amp_cal value[7:0]
#ifdef DBG
		printf("R_cal_NOR value =%x\n",R_cal_value);
		//printf("RC_cal_NOR value =%x\n",RC_cal_value);
		printf("amp_dn_NOR =%x\n",amp_dn);
		printf("amp_dn_fine_NOR =%x\n",amp_dn_fine);
		printf("ib_dn_NOR =%x\n",ib_dn);
		printf("ib_up_NOR =%x\n",ib_up);
#endif
		/* write DOUT data */
		mdio_write_complete(0x841f0a46);// change Page to a46
		val = (((ib_dn&0x7f)<<9)|ib_up);
		mdio_write_complete((0x84100100)|val);// bit[15:9]=Fuse_DOUT[14:8](amp_cal value[14:8]),bit[7:0]=Fuse_DOUT[7:0](amp_cal value[7:0])
		mdio_read_complete(0x04100000);
		//printf("reg 16 =%x\n",rtd_inl(MIIAR));
		val = (amp_dn_fine<<1)|(ib_dn>>7);
		mdio_write_complete(0x8411fe00|val);// bit[8:1]=Fuse_DOUT[24:17](amp_cal value[23:16]),bit[0]=Fuse_DOUT[16](amp_cal value[15])
		mdio_read_complete(0x04110000);
		//printf("reg 17 =%x\n",rtd_inl(MIIAR));
		//printf("reg 17 =%x\n",rtd_inl(MIIAR));
		val = ((R_cal_value&0x1)<<15);
		mdio_write_complete(0x84127fff|val);// bit[15]=Fuse_DOUT[47](R value [0])
		mdio_read_complete(0x04120000);
		//printf("reg 18 =%x\n",rtd_inl(MIIAR));
		//val = (RC_cal_value<<3)|(R_cal_value>>1);
		//mdio_write_complete(0x8413ff80|val);// bit[6:3]=Fuse_DOUT[54:51](RC value),bit[2:0]=Fuse_DOUT[50:48](R value [3:1])
		val = (R_cal_value>>1);
		mdio_write_complete(0x8413fff8|val);// bit[6:3]=Fuse_DOUT[54:51](RC value),bit[2:0]=Fuse_DOUT[50:48](R value [3:1])
		mdio_read_complete(0x04130000);
		//printf("reg 19 =%x\n",rtd_inl(MIIAR));
	}
	else{
		mdio_write_complete(0x841f0a46);// change Page to a46
		ib_up =  0xaa;
		mdio_write_complete((0x8410ff00|ib_up));// bit[7:0]=Fuse_DOUT[7:0](amp_cal value[7:0])
	}

}

void greentable_modify(void){
	unsigned int val, val1, val2;
	unsigned int amp_dn;

	/* adjust common mode voltage */
	mdio_write_complete(0x841f0bc0);// change Page to bc0
	mdio_write_complete(0x84170001);// bit[1:0]:common mode voltage => 0x2->0x1

	val1 = rtd_inl(0xb80381e4);
	val2 = rtd_inl(0xb80381e8);

	if ((val1&_BIT31)&&(val2&_BIT31)){//efuse have burned
		amp_dn = ((val2>>19)&0x7);//from efuse [53:51]
		amp_dn = (amp_dn^0x7);
		amp_dn = (amp_dn<<9);
		printf("MISC: efuse had been written\n");
	}else{
		amp_dn = (0x2<<9); // bit[2:0]:amp_dn => 00:100% 01:90% 10:80%
		printf("MISC: efuse had NOT been written\n");
	}

	//printf("amp_dn = %x\n",(amp_dn>>9));
	/* grntbl_0_03 */
	mdio_write_complete(0x841b8079);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_0_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_1_03 */
	mdio_write_complete(0x841b8082);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_1_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_2_03 */
	mdio_write_complete(0x841b808B);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_2_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_3_03 */
	mdio_write_complete(0x841b8094);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_3_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_4_03 */
	mdio_write_complete(0x841b809d);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_4_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_5_03 */
	mdio_write_complete(0x841b80A6);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_5_03 =%x\n",rtd_inl(MIIAR));

	/* grntbl_6_03 */
	mdio_write_complete(0x841b80AF);
	val = mdio_read_complete(0x041c0000);
	val = ((val&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	mdio_write_complete(0x841c0000|val);
	mdio_read_complete(0x041c0000);
	//printf("grntbl_6_03 =%x\n",rtd_inl(MIIAR));

#if 0 // get status later that can reduce about 60ms delay time
	mdelay(60);

	greentable_status();
#endif

}

void greentable_status(void)
{
#ifdef DBG
	unsigned int val;

	mdio_write_complete(0x841f0bcc);// change Page to bcc
	val = mdio_read_complete(0x04100000);
	printf(" amp_dn = %x\n",val&0x7);

	val = mdio_read_complete(0x04140000);
	printf(" amp_dn_fine = %x\n",val&0xff);

	val = mdio_read_complete(0x04120000);
	printf(" ib_up = %x\n",val&0xff);//bit[1:0]:up  => 00:100% 01:102.5% 10:105%
	printf(" ib_dn = %x\n",(val>>8)&0xff);

	mdio_write_complete(0x841f0bce);// change Page to bce
	val = mdio_read_complete(0x04100000);
	printf(" R = %x\n",val&0xffff);

	mdio_write_complete(0x841f0bcd);// change Page to bcd
	val = mdio_read_complete(0x04160000);
	printf(" RC = %x\n",val&0xffff);
#endif
}

int rtk_misc_init(void)
{
//	unsigned int iTimeoutCounter;
	unsigned int iRegVal;
#ifdef IS_298X_FPGA
	printf("fpga skip\n");
	return 0;
#endif
	getn_load_efusedata2DOUT();

	iRegVal = rtd_inl(MIIAR);
	if( iRegVal == SET_FUSE_RDY_INIT_DONE_FLAG ) {
		return 0;
	}

	printf("MISC : set FUSE_RDY\n");

	//set_fuse_rdy.config
	mdio_write_complete(SET_FUSE_RDY_CHANGE_PAGE_A46); // change Page to a46
	mdio_write_complete(SET_FUSE_RDY_INIT_DONE_FLAG); // set fuse_rdy = 1 , set ext_ini_done = 1, to skip ext_ini

	greentable_modify();

	return 0;
}

int rtk_mcu_bisr(void)
{
	unsigned int iBISROldReg = 0;
	unsigned int iBISRFlag = 0;
	unsigned int iMaxCount = 100;

#if 0
	printf("*** REG(0xb8060014)=0x%08x\n", rtd_inl(0xb8060014));
	printf("*** REG(0xb806001c)=0x%08x\n", rtd_inl(0xb806001c));
	printf("*** REG(0xb8060018)=0x%08x\n", rtd_inl(0xb8060018));
#endif
	printf("MCU : BISR testing...\n");

	iBISRFlag = 1;
	iBISROldReg = rtd_inl(0xb8060014);
	iBISROldReg |= iBISRFlag;
	rtd_outl(0xb8060014, iBISROldReg);
	while( (rtd_inl(0xb806001c)&iBISRFlag) != iBISRFlag ) {
		iMaxCount--;
		udelay(100);
		if( iMaxCount == 0 ) {
			break;
		}
	}
	if( iMaxCount != 0 ) {
		iBISROldReg = rtd_inl(0xb8060018);
		iBISROldReg |= iBISRFlag;
		rtd_outl(0xb8060018, iBISROldReg);
	}
	printf("MCU : Finish BISR testing (%s)\n", ((iMaxCount==0)? "Fail" : "OK") );
#if 0
	printf("*** REG(0xb8060014)=0x%08x\n", rtd_inl(0xb8060014));
	printf("*** REG(0xb806001c)=0x%08x\n", rtd_inl(0xb806001c));
	printf("*** REG(0xb8060018)=0x%08x\n", rtd_inl(0xb8060018));
#endif
	return 0;
}

int rtk_gpu_bisr(void)
{
	unsigned int iBISROldReg = 0;
	unsigned int iBISRFlag = 0;
	unsigned int iMaxCount = 100;
#if 0
	printf("*** REG(0xb8000f0c)=0x%08x\n", rtd_inl(0xb8000f0c));
	printf("*** REG(0xb8000f2c)=0x%08x\n", rtd_inl(0xb8000f2c));
	printf("*** REG(0xb8000f1c)=0x%08x\n", rtd_inl(0xb8000f1c));
#endif
	printf("GPU : BISR testing...\n");
	rtd_outl(0xb804ff00, 0x0400001C);
	iBISRFlag = 3;
	iBISROldReg = rtd_inl(0xb8000f0c);
	iBISROldReg |= iBISRFlag;
	rtd_outl(0xb8000f0c, iBISROldReg);
	while( (rtd_inl(0xb8000f2c)&iBISRFlag) != iBISRFlag ) {
		iMaxCount--;
		udelay(100);
		if( iMaxCount == 0 ) {
			break;
		}
	}
	if( iMaxCount != 0 ) {
		iBISROldReg = rtd_inl(0xb8000f1c);
		iBISROldReg |= iBISRFlag;
		rtd_outl(0xb8000f1c, iBISROldReg);
	}
	printf("GPU : Finish BISR testing (%s)\n", ((iMaxCount==0)? "Fail" : "OK"));
#if 0
	printf("*** REG(0xb8000f0c)=0x%08x\n", rtd_inl(0xb8000f0c));
	printf("*** REG(0xb8000f2c)=0x%08x\n", rtd_inl(0xb8000f2c));
	printf("*** REG(0xb8000f1c)=0x%08x\n", rtd_inl(0xb8000f1c));
#endif
	return 0;
}


int rtk_dispi_bisr(void)
{
	unsigned char DispIBISRFlag = 0;//, DispDBISRFlag = 0;

	rtd_outl(0xb8005210,0x80000000);// VODMA CLKEN, MAIN
	rtd_outl(0xb8005610,0x80000000);// VODMA CLKEN
	rtd_outl(0xb8005a10,0x80000000);// VODMA CLKEN
	rtd_outl(0xb8005510,0x80000000);// VODMA CLKEN, SUB
	mdelay(1);
	rtd_outl(0xb8020000,0x000000ef);// YPbPrADC, ADC clock on, bandgap on
	rtd_outl(0xb8022284,0x0000000e); // Xcdi_clk_en=1, S1/S2 clock choose PCLK*2
	//rtd_outl(0xb8024004,0x00000001); // Cp_bist_clkmux_en=1
	rtd_outl(0xb8022210,0x40000001); // vgip iclk enable, select to VO:4, select to ADC 1
	rtd_outl(0xb8022410,0x40000001); // vgip sub  iclk enable, select to VO:4, select to ADC 2
	rtd_outl(0xb8022710,0x40000001);// vgip i3ddma iclk enable, select to VO:4, select to VODMA 3

	rtd_outl(0xb80005d0,0x0000000f); // de-assert BISR reset
	mdelay(1);

	if((rtd_inl(0xb8000700)&0x0b000000) == 0x0b000000){
		if(rtd_inl(0xb8025f24) == 0)
			DispIBISRFlag = 1;
		else
			printf("bistr fail2 0xb8025f24=%x\n",rtd_inl(0xb8025f24));
	}else{
		printf("bistr fail1 0xb8000700=%x\n",rtd_inl(0xb8000700));
	}

	rtd_outl(0xb80005d0,0x00000000);// assert BISR reset

	printf("DispI : Finish BISR testing %s\n", (DispIBISRFlag ? "done" : "fail" ) );
	return 0;
}

#ifdef ENABLE_SCPU_BISR
int rtk_scpu_bisr(void)
{
	unsigned int iMaxCount = 100;
	printf("SCPU: BISR testing ....\n");
	rtd_setbits( 0xb801ca94, _BIT0);
	rtd_setbits( 0xb801ca98, _BIT0);
	while(!(rtd_inl(0xb801cab4) & _BIT0)){
		iMaxCount--;
		udelay(100);
		if( iMaxCount == 0 ) {
			break;
		}
	}
	rtd_setbits(0xb801caa0, _BIT0);
	printf("SCPU: Finish BISR testing (%s)\n", ((iMaxCount==0)? "Fail" : "OK"));
	return 0;
}
#endif	//ENABLE_SCPU_BISR

#ifdef ENABLE_VCPU_BISR
void do_vcpu_bisr()
{
   unsigned int iMaxCount = 100;

   mdelay(10);
   printf("\nVCPU: BISR testing ....\n");
   rtd_setbits(CRT_CRT_BISR_RSTN1_VADDR, _BIT2 | _BIT0);
   rtd_setbits(CRT_CRT_BISR_PWR_RSTN1_VADDR, _BIT2 | _BIT0);
   udelay(100);
   while(!(rtd_inl(0xb8001120) & _BIT4)) {
      iMaxCount--;
      udelay(100);
      if( iMaxCount == 0 ) {
         break;
      }
   }
   rtd_setbits(CRT_CRT_BISR_HOLD_REMAP1_VADDR, _BIT2 | _BIT0);
   printf("VCPU: Finish BISR testing %s\n\n", (iMaxCount ? "done" : "fail" ) );
}
#endif	//ENABLE_VCPU_BISR

#ifdef ENABLE_ACPU_BISR
void do_acpu_bisr()
{
   unsigned int iMaxCount = 100;

   mdelay(10);
   printf("\nACPU: BISR testing ....\n");
   rtd_setbits(CRT_CRT_BISR_RSTN1_VADDR, _BIT1 | _BIT0);
   rtd_setbits(CRT_CRT_BISR_PWR_RSTN1_VADDR, _BIT1 | _BIT0);
   udelay(100);
   while(!(rtd_inl(0xb8002164) & _BIT0)) {
      iMaxCount--;
      udelay(100);
      if( iMaxCount == 0 ) {
         break;
      }
   }
   rtd_setbits(CRT_CRT_BISR_HOLD_REMAP1_VADDR, _BIT1 | _BIT0);
   printf("ACPU: Finish BISR testing %s\n\n", (iMaxCount ? "done" : "fail" ) );
}
#endif	//ENABLE_ACPU_BISR

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
    unsigned int iMedia;
	int cpu_nr;
	unsigned int hw_cpu_nr;

	hw_cpu_nr = ((rtd_inl(0xb8017194) & (_BIT16 | _BIT17)) >> 16);

    printf("CPU  : Cortex-A7 ");
	if ((CONFIG_SYS_NR_CPUS == 0) || (hw_cpu_nr != 0)) { /* 0 means auto detect */
		cpu_nr = 4 - hw_cpu_nr;
	}
	else {
		cpu_nr = CONFIG_SYS_NR_CPUS;
		//set to max count, if setting is larger than 4.
		if (cpu_nr > 4) cpu_nr = 4;
		//set to min count, if setting is smaller than 0.
		if (cpu_nr < 0) cpu_nr = 1;
	}

	switch (cpu_nr) {
		case 1:
			printf("single");
			rtd_outl(0xb801c868, 0xffe);
			rtd_outl(0xb801c868, 0x11e);
			break;
		case 2:
			printf("dual");
			rtd_outl(0xb801c868, 0xffc);
			rtd_outl(0xb801c868, 0x33c);
			break;
		case 3:
			printf("triple");
			rtd_outl(0xb801c868, 0xff8);
			rtd_outl(0xb801c868, 0x778);			
			break;
		case 4:
		default:
//			printf("quad");
			/* Requested by PM */
			printf("Dual");
			//rtd_outl(0xb801c868, 0xff0);			
			break;
	}
	printf(" core\n");

#if 1 // for boot device information
	extern unsigned int UATAG_ADDRESS9;
	extern unsigned int UATAG_ADDRESS10;
	printf("Media: ");
    if( *((unsigned int *)&UATAG_ADDRESS9) == 0xF9E8D7C6UL ){
    	iMedia = *((unsigned int *)&UATAG_ADDRESS10);
    	if( iMedia == 0 ){
    		printf("NAND\n");
    	}
    	else if( iMedia == 1 ){
    		printf("SPI\n");
    	}
    	else if( (iMedia&0xFF) == 2 ){
    		iMedia = (iMedia >> 8) & 0xFF;
    		if( iMedia == 2 ) {
    			printf("eMMC BP2\n");
    		}
    		else if( iMedia == 1 ) {
    			printf("eMMC BP1\n");
    		}
    		else if( iMedia == 0 ) {
    			printf("eMMC BP0\n");
    		}
    		else {
    			printf("eMMC (unknown BP)\n");
    		}
    	}
    	else if( *((unsigned int *)&UATAG_ADDRESS10) == 0 ){
    		printf("unknown\n");
    	}
    }
    else {
    	printf("undefined\n");
    }
	//printf("uatag9(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS9, *((unsigned int *)&UATAG_ADDRESS9));
	//printf("uatag10(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS10, *((unsigned int *)&UATAG_ADDRESS10));
	//printf("uatag11(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS11, *((unsigned int *)&UATAG_ADDRESS11));
	//printf("uatag12(add 0x%08x) = 0x%08x\n", &UATAG_ADDRESS12, *((unsigned int *)&UATAG_ADDRESS12));
#endif
    return 0;
}

#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{
    /* Enable D-cache. I-cache is already enabled in start.S */
    dcache_enable();
}
#endif

#ifndef CONFIG_SYS_L2CACHE_OFF
void v7_outer_cache_enable(void)
{
	//set_pl310_ctrl_reg(1);
}

void v7_outer_cache_disable(void)
{
	//set_pl310_ctrl_reg(0);
}
#endif

#ifdef CONFIG_USE_RTK_RTC
int rtc_init(void)
{
	uint rtcstop_regValue = 0xffffffff;

	if (rtd_inl(CRT_ST_CLKEN1_VADDR) & _BIT11)
		rtcstop_regValue = rtd_inl(D_RTCSTOP_reg);

	// check RTC status
	if ((rtcstop_regValue & _BIT0)== 0x0) // status: running
	{
		;	// RTC: Already running ... do nothing ...
	}
	else // status: stopped
	{
		// enable DRTC clock
		rtd_clearbits(CRT_ST_CLKEN1_VADDR, _BIT11);
   	rtd_clearbits(CRT_ST_SRST1_VADDR, _BIT11);
   	rtd_setbits(CRT_ST_SRST1_VADDR, _BIT11);
   	rtd_setbits(CRT_ST_CLKEN1_VADDR, _BIT11);

		// initialize RTC
		rtd_outl(D_RTCSTOP_reg, D_RTCSTOP_27Mclk_en(0x1)); // clk select

		// reset time info
		rtd_outl(D_RTCSEC_reg, D_RTCSEC_D_RTCSEC(0x0)); // sec
		rtd_outl(D_RTCMIN_reg, D_RTCMIN_D_RTCMIN(0x0)); // min
		rtd_outl(D_RTCHR_reg, D_RTCHR_D_RTCHR(0x0)); // hour
		rtd_outl(D_RTCDATE1_reg, D_RTCDATE1_D_RTCDATE1(0x0)); // date LSB
		rtd_outl(D_RTCDATE2_reg, D_RTCDATE2_D_RTCDATE2(0x0)); // date MSB

		// enable RTC
		rtd_outl(D_RTCEN_reg, D_RTCEN_D_RTCEN(0x5A));

		// check RTC status
		rtcstop_regValue = rtd_inl(D_RTCSTOP_reg);
		if ((rtcstop_regValue & _BIT0) == 0x0)
		{
			;	// RTC: Running
		}
		else
		{
			;	// RTC: Stop
		}
	}

	return 0;
}
#endif	//CONFIG_USE_RTK_RTC
