/*============================================================*
 * Copyright (c)      Realtek Semiconductor Corporation, 2007 *
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/
/**
 * @file 8139cp_verify.c
 * To verify 8139cp NIC H/W. Create Test Case by verify plan.
 * @author Ching-Yuh Huang
 * @date 2007/03/19
 * @version 0.1
 */
/*====================== Include files ========================*/



#include <common.h>
#include "linux/compat.h"
#include <asm/arch/system.h>
#include <rtd_types_qc.h>

//#define CONFIG_GETH_VERIFY


#ifndef BOOL
#define BOOL 					bool
#endif

/* cyhuang (2006/9/28) : Add for TFTP function.  */
#if defined(CONFIG_BOOT_TIMER)
#include <timer.h>
#endif
#if defined(CONFIG_BOOT_NET)
#include <net.h>
#endif

#include "8139cp.h"
//#include "getn.h"

//#include <qc.h>
#define VERIFY_PASS			(0)
#define VERIFY_FAIL			(1)
#define TX_QC_DESC_NUM          (32)
#define RX_QC_DESC_NUM          (32)
#define LAN_QC_VERIFY_LEN		(0x40) // 0x2ff
//#define LAN_10M_TX_VERIFY_LEN		(0x500) // 0x2ff
#define LAN_10M_TX_VERIFY_LEN		(0x40) 

#define PHYSADDR
#define BYTE_ENDIAN_BUG

//check after
#define KSEG1ADDR
#define sys_dcache_flush_and_invalidate_all flush_dcache_all

#define adjust_CM_Voltage 1
#define adjust_Swing_Amp 1
#define two_byte_align_test 0
#define auto_n_way 1

#if CONFIG_BGA
#define QC_test_1000M	1
#define nway_sel_100M    0
#define nway_sel_10M      0
#else
#define QC_test_1000M	0
#define nway_sel_100M    1
#define nway_sel_10M      0
#endif

#define QC_test_100M	1
#define QC_test_10M		1
#define ONLY_TX_VERIFY 0

typedef int (_rx_handle_func_t) (volatile void *packet, int length);

static UINT32 ioaddr=RTD2885_LAN_BASE;
static UINT32 RTD2885_LAN_PHY_ID;

// Tx/Rx Dsecript only use [31:8]
static NIC_FD_T Tx_Desc[TX_QC_DESC_NUM] __attribute__((aligned(256)));
static NIC_FD_T Rx_Desc[RX_QC_DESC_NUM] __attribute__((aligned(256)));

static NIC_FD_T *pTxBDPtr=NULL;
static NIC_FD_T *pRxBDPtr=NULL;

static unsigned int	txBDtail = 0;	// index for system to set buf to BD
static unsigned int	rxBDtail = 0;	// index for system to set buf to BD

static unsigned char tx_buffer[TX_BUF_SIZE] __attribute__((aligned(256)));
//static unsigned char rx_ring[RX_QC_DESC_NUM * RX_DESC_BUFFER_SIZE] __attribute__((aligned(256)));

#ifdef two_byte_align_test 
static unsigned char rx_ring[RX_QC_DESC_NUM * (RX_DESC_BUFFER_SIZE + 2) ] __attribute__((aligned(256)));
#else
static unsigned char rx_ring[RX_QC_DESC_NUM * (RX_DESC_BUFFER_SIZE) ] __attribute__((aligned(256)));
#endif




#if ONLY_TX_VERIFY
static unsigned char tx_ring[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring1[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring2[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring3[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring4[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring5[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring6[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring7[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring8[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring9[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring10[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring11[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring12[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring13[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
static unsigned char tx_ring14[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));	
static unsigned char tx_ring15[2* RX_DESC_BUFFER_SIZE]__attribute__((aligned(256)));
#endif







static UINT8  txbuffer[TX_BUF_SIZE] __attribute__((aligned(32)));

static int QC_Result = VERIFY_FAIL;

int loopback_mode = PHY_LOOP_BACK;

extern int memcmp(const void * cs,const void * ct,size_t count);
extern void sys_dcache_flush_and_invalidate_all(void);

void rtl8139cp_smartbit_test_tx(int num,int size,int mod);

// #define udelay(x)    {int i=0; for(i=0;i<0xffff;i++);}



#define at_swap_16(x) \
	({ unsigned short x_ = (unsigned short)x; \
	 (unsigned short)( \
		((x_ & 0x00FFU) << 8) | ((x_ & 0xFF00U) >> 8) ); \
	})
#define at_swap_32(x) \
	({ unsigned long x_ = (unsigned long)x; \
	 (unsigned long)( \
		((x_ & 0x000000FFUL) << 24) | \
		((x_ & 0x0000FF00UL) <<	 8) | \
		((x_ & 0x00FF0000UL) >>	 8) | \
		((x_ & 0xFF000000UL) >> 24) ); \
	})
#define LITTLEENDIA_ETH (0)

#define ETH_CLKEN (1<<16)
#define ETH_PHY_CLKEN (1<<17)
#define PLLETN_OEB (1<<2)
#define PLLETN_POW (1<<0)
#define PLLETN_RSTB (1<<1)
#define SC_CLKEN1 0xb8000114
#define SC_CLKEN2 0xb8000118
#define SYS_PLL_ETN2 0xb80004a8

enum {
	FD_TX_DESC = 0,
	FD_RX_DESC = 1,
	
};

#if 1


void __inline__ ms_delay(unsigned long ms)
{
	while(ms-->0)
		udelay(1000);
}

static UINT16 inline rtl6330cp_verify_mdio_read(UINT8 PhyID,UINT8 RegAddr)
{	
	unsigned int i=0;

	rtd_outl(ioaddr+MIIAR,(MIIAR_RegAddr4_0(RegAddr)| MIIAR_PHYAddress(PhyID)));
	// Wait 5 ms
	udelay(5000);
	
	// 50 ms
	i = 5000;	
	while (!(rtd_inl(ioaddr+MIIAR) & MIIAR_Flag_Write) && (--i) )
	{
		udelay(10);
	};
	
	if (i==0) 
    	printk("rtl6330cp_verify_mdio_read() TimeOut (Reg = %d, PhyID = %d).\n",RegAddr,PhyID); 
			
	return MIIAR_Data15_0(rtd_inl(ioaddr+MIIAR));
}






static void inline rtl8139cp_verify_mdio_write(UINT8 PhyID,UINT8 RegAddr ,UINT16 data)
{
	unsigned int i=0;

	rtd_outl(ioaddr+MIIAR,(MIIAR_Flag_Write|MIIAR_Data15_0(data)|MIIAR_RegAddr4_0(RegAddr)| MIIAR_PHYAddress(PhyID)));
	// Wait 5 ms
	udelay(5000);	
	
	// 50 ms
	i = 5000;
	while (rtd_inl(ioaddr+MIIAR) & MIIAR_Flag_Write && (--i))
    {
		udelay(10);
	}; 
	
	if (i==0) 
    		printk("rtl8139cp_verify_mdio_write() TimeOut (Reg = %d, PhyID = %d).\n",RegAddr,PhyID); 
}



static void inline rtl6330cp_verify_mdio_write(UINT8 PhyID,UINT8 RegAddr ,UINT16 data)
{
	unsigned int i=0;

	rtd_outl(ioaddr+MIIAR,(MIIAR_Flag_Write|MIIAR_Data15_0(data)|MIIAR_RegAddr4_0(RegAddr)| MIIAR_PHYAddress(PhyID)));
	// Wait 5 ms
	//udelay(5000);	
	udelay(100);
	// 50 ms
	i = 5000;
	while ((rtd_inl(ioaddr+MIIAR) & MIIAR_Flag_Write) && (--i))
    	{
		udelay(10);
	}; 
	
	if (i==0) 
    		printk("rtl6330cp_verify_mdio_write() TimeOut (Reg = %d, PhyID = %d).\n",RegAddr,PhyID); 
}
void GETN_CRT(void)
{


#if 0
//PLL_27X
rtd_outl(0xb8000240,0x0225000E); // max = 432, set 27*16 = 432MHz 
rtd_outl(0xb8000244,0x00105401); // 1.1V LDO power on & output 1.0V, LDO XTAL power on & output 1.76V
rtd_outl(0xb8000248,0x00000001); // release PLL_27X & VCO reset & power on
rtd_outl(0xb8000248,0x00000007); // release PLL_27X & VCO reset & power on
udelay(100); // at least > 5us

//PLL_ETN
rtd_outl(0xb8016d00,0x0230370a);         // 25M
rtd_outl(0xb8016d04,0x00008035); // power on         
rtd_outl(0xb8016d04,0x00008037); // release reset
udelay(1); // at least > 5us
rtd_outl(0xb8016d04,0x00008033); //PLLETN output enable


	//rtd_outl(0xb8016c04,0x00000004);
	rtd_outl(0xb8016c00,0x00000000);
//	udelay(2000);
	rtd_outl(0xb8016c00,0x0000001d);
//	udelay(2000);
	rtd_outl(0xb8016c04,0x00000006);
//	udelay(2000);
	//Mac
	
	udelay(6000);
	rtd_maskl(0xb800000c,0xfffffdff,0x00000200); // eth clock 0xb800000c[9] = 1
	udelay(6000);
	rtd_maskl(0xb800000c,0xfffffdff,0x00000000); // eth clock 0xb800000c[9] = 0
	udelay(6000);
	rtd_maskl(0xb8000000,0xffffdfff,0x00002000); // eth reset 0xb8000000[13] = 1
	udelay(6000);
	rtd_maskl(0xb800000c,0xfffffdff,0x00000200); // eth clock 0xb800000c[9] = 1
	udelay(6000);
	
#endif


#if CONFIG_BGA
	//do nothing
#else
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	udelay(100);
	printk("[a]%x\n",rtd_inl(0xb801605c));
	
	rtd_outl(0xb801605c,0x04100000);// polling rg_phy_status = 1
	udelay(100);
	printk("[0]%x\n",rtd_inl(0xb801605c));

	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
       udelay(100);
       rtd_outl(0xb801605c,0x84090000);// disable giga capability
	udelay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
#endif


#ifdef CONFIG_GETH_VERIFY
	ms_delay(5000);
#else
	ms_delay(60);
#endif

}
#endif

void SET_FUSE_READY(void)
{
	printk("ID=%x\n",RTD2885_LAN_PHY_ID);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a46);// change Page to a46
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x0003);// set fuse_rdy = 1 , set ext_ini_done = 1, to skip ext_ini
	printk("read fuse_ready=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG20)); // --> 0x84140003;
}

void PHY_STATUS(void)
{
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a42);// change Page to a42
	printk("rg_phy_status=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16)); // --> 0x84100023; 
}


void PHY_RESET(void)
{
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a46);// change Page to a46
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1040);
	ms_delay(500);
}

void LINK_STATUS(void)
{

	UINT32 i=0;
	 //printk(" read link status=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG1)); // --> 0x840179ed;
	
	 #if 1 //for loop back

	 while(1){
		if (rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG1)&_BIT2){
			 printk(" Link OK ...\n");
			break;
		}
	 	ms_delay(10);
		i++;
		if (i>550){
			break;
		}
	 };

	printk("i=%d\n",i);

	 if (i>550)
	 	printk(" Link Fail ...\n");

	 #endif

}




void LINK_SPEED(void)
{
	UINT32 temp=0;
	//rtd_outl(0xb801605c,0x841f0000);// change Page to 0
	//ms_delay(0x10);
	//rtd_outl(0xb801605c,0x041a0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);// change Page to 0
	temp = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26);//read status
	
	if ((temp&0x34)==0x04)
		printk("10M Link.......\n");
	else if ((temp&0x34)==0x14)
		printk("100M Link.......\n");
	else if ((temp&0x34)==0x24)
		printk("1G Link.......\n");
	else
		printk("No Link=%x\n",temp);
}

void PHY_SETTING(void)
{
	//rtd_outl(0xb801605c,0x84004140);  ///--- set gphy 1000M mode && loopback && full-duplex
	//ew 0xb801605c=0x840b0002  ///---set gphy 1000M mode && loopback && full-duplex
	//ew 0xb8016058=0x00020400  ///--- set Mac 1000M mode

//	rtd_outl(0xb801605c,0x84004140);///--- set gphy 1000M mode && loopback && full-duplex
	//1000M normal mode
	rtd_outl(0xb801605c,0x84000140); ///--- set gphy 1000M mode && normal && full-duplex
	//rtd_outl(0xb801605c,0x84001140); ///--- set gphy auto mode && normal && full-duplex

	//100M normal mode
//	rtd_outl(0xb801605c,0x84002100); ///--- set gphy 100M mode && normal && full-duplex

	//10M normal mode
	//rtd_outl(0xb801605c,0x84000100); ///--- set gphy 10M mode  && normal && full-duplex
//	rtd_outl(0xb801605c,0x84004100); ///--- set gphy 10M mode  && loopback && full-duplex
	 ms_delay(3000);
}

void RX_DESCRIPTOR(void)
{
	//for big endian
	//rx  descriptor  ddr
#ifdef big_endian
	rtd_outl(0x00408000,0x00080080); // 80000800
	//rtd_outl(0xa00f8004,0x00000f00); // 000f0000  
	rtd_outl(0x00408004,0x00004000);//00400000

	rtd_outl(0x00408010,0x00080080); //80000800
	//rtd_outl(0xa00f8014,0x00010f00); //000f0100
	rtd_outl(0x00408014,0x00014000); //00400100

	rtd_outl(0x00408020,0x00080080);  //80000800
	//rtd_outl(0xa00f8024,0x00020f00);  //000f0200
	rtd_outl(0x00408024,0x00024000); //00400200

	rtd_outl(0x00408030,0x00080000);  //00000800
	//rtd_outl(0xa00f8034,0x00080f00);  //000f0800
	rtd_outl(0x00408034,0x00084000); //00400800
#else

	rtd_outl(0x00408000,0x80000800); // 80000800
	//rtd_outl(0xa00f8004,0x00000f00); // 000f0000  
	rtd_outl(0x00408004,0x00400000);//00400000

	rtd_outl(0x00408010,0x80000800); //80000800
	//rtd_outl(0xa00f8014,0x00010f00); //000f0100
	rtd_outl(0x00408014,0x00400100); //00400100

	rtd_outl(0x00408020,0x80000800);  //80000800
	//rtd_outl(0xa00f8024,0x00020f00);  //000f0200
	rtd_outl(0x00408024,0x00400200); //00400200

	rtd_outl(0x00408030,0x80000800);  //80000800
	//rtd_outl(0xa00f8034,0x00080f00);  //00080f00
	rtd_outl(0x00408034,0x00400300); //00400f00

	rtd_outl(0x00408040,0x80000800);  //80000800
	//rtd_outl(0xa00f8044,0x00080f00);  //00080f00
	rtd_outl(0x00408044,0x00400400); //00400f00

	rtd_outl(0x00408050,0x80000800);  //80000800
	//rtd_outl(0xa00f8054,0x00080f00);  //00080f00
	rtd_outl(0x00408054,0x00400400); //00400f00

	rtd_outl(0x00408060,0x80000800);  //80000800
	//rtd_outl(0xa00f8064,0x00080f00);  //00080f00
	rtd_outl(0x00408064,0x00400400); //00400f00

	rtd_outl(0x00408070,0x80000800);  //80000800
	//rtd_outl(0xa00f8074,0x00080f00);  //00080f00
	rtd_outl(0x00408074,0x00400400); //00400f00

	rtd_outl(0x00408080,0x80000800);  //80000800
	//rtd_outl(0xa00f8084,0x00080f00);  //00080f00
	rtd_outl(0x00408084,0x00400400); //00400f00

	rtd_outl(0x00408090,0x00000800);  //80000800
	//rtd_outl(0xa00f8094,0x00080f00);  //00080f00
	rtd_outl(0x00408094,0x00400400); //00400f00
#endif
}

void TX_DESCRIPTOR(void)
{
#ifdef big_endian
	//ddr address tx
	rtd_outl(0x0040c000,0x100080a0);	//own, fs,  //a0800010
	rtd_outl(0x0040c004,0x00104000);  //00401000
	rtd_outl(0x0040c008,0x00000000);
	rtd_outl(0x0040c00c,0x00000000);


	rtd_outl(0x0040c010,0x10008080);	//own  //80800010
	rtd_outl(0x0040c014,0x10104000);   //00401010
	rtd_outl(0x0040c018,0x00000000);
	rtd_outl(0x0040c01c,0x00000000);

	rtd_outl(0x0040c020,0x10008090);	//own   //90800010
	rtd_outl(0x0040c024,0x20104000);   //00401020
	rtd_outl(0x0040c028,0x00000000);
	rtd_outl(0x0040c02c,0x00000000);

	// 2nd  packet
	rtd_outl(0x0040c030,0x100080a0);	//own, fs, 
	rtd_outl(0x0040c034,0x30104000);  //00401030
	rtd_outl(0x0040c038,0x00000000);
	rtd_outl(0x0040c03c,0x00000000);

	rtd_outl(0x0040c040,0x10008080);	//own
	rtd_outl(0x0040c044,0x40104000);  //00401040
	rtd_outl(0x0040c048,0x00000000);
	rtd_outl(0x0040c04c,0x00000000);

	rtd_outl(0x0040c050,0x10008090);	//own
	rtd_outl(0x0040c054,0x50104000);   //00401050
	rtd_outl(0x0040c058,0x00000000);
	rtd_outl(0x0040c05c,0x00000000);

	// 3rd  packet
	rtd_outl(0x0040c060,0x100080a0);	//own, fs, 
	rtd_outl(0x0040c064,0x60104000);   //00401060
	rtd_outl(0x0040c068,0x00000000);
	rtd_outl(0x0040c06c,0x00000000);

	rtd_outl(0x0040c070,0x10008080);	//own
	rtd_outl(0x0040c074,0x70104000);   //00401070
	rtd_outl(0x0040c078,0x00000000);
	rtd_outl(0x0040c07c,0x00000000);

	rtd_outl(0x0040c080,0x10008090);	//own
	rtd_outl(0x0040c084,0x80104000);   //00401080
	rtd_outl(0x0040c088,0x00000000);
	rtd_outl(0x0040c08c,0x00000000);

	rtd_outl(0x0040c090,0x80008000);	//own,0
#else  //little endian
	//ddr address tx
	rtd_outl(0x0040c000,0xa0800100);	//own, fs,  //a0800010
	rtd_outl(0x0040c004,0x00401000);  //00401000
	rtd_outl(0x0040c008,0x00000000);
	rtd_outl(0x0040c00c,0x00000000);

	rtd_outl(0x0040c010,0x80800100);	//own  //80800010
	rtd_outl(0x0040c014,0x00401100);   //00401100
	rtd_outl(0x0040c018,0x00000000);
	rtd_outl(0x0040c01c,0x00000000);

	rtd_outl(0x0040c020,0x90800100);	//own   //90800010
	rtd_outl(0x0040c024,0x00401200);   //00401200
	rtd_outl(0x0040c028,0x00000000);
	rtd_outl(0x0040c02c,0x00000000);

	rtd_outl(0x0040c030,0x00800080);	//own,0 //00800080
#endif

}

void TX_DATA(void)
{
#if 0
	//tx data in ddr
	rtd_outl(0xa00f1000,0x03020100);
	rtd_outl(0xa00f1004,0x07060504);
	rtd_outl(0xa00f1008,0x11100908);
	rtd_outl(0xa00f100c,0x15141312);
	rtd_outl(0xa00f1010,0x19181716);
	rtd_outl(0xa00f1014,0x23222120);
	rtd_outl(0xa00f1018,0x27262524);
	rtd_outl(0xa00f101c,0x31302928);
	rtd_outl(0xa00f1020,0x35343332);
	rtd_outl(0xa00f1024,0x39383736);
	rtd_outl(0xa00f1028,0x43424140);
	rtd_outl(0xa00f102c,0x47464544);
	rtd_outl(0xa00f1030,0x51504948);
	rtd_outl(0xa00f1034,0x55545352);
	rtd_outl(0xa00f1038,0x59585756);
	rtd_outl(0xa00f103c,0x63626160);
	rtd_outl(0xa00f1040,0x67666564);
	rtd_outl(0xa00f1044,0x71706968);
	rtd_outl(0xa00f1048,0x75747372);
	rtd_outl(0xa00f104c,0x79787776);
	rtd_outl(0xa00f1050,0x83828180);
	rtd_outl(0xa00f1054,0x87868584);
	rtd_outl(0xa00f1058,0x91908988);
	rtd_outl(0xa00f105c,0x95949392);
	rtd_outl(0xa00f1060,0x99989796);
	rtd_outl(0xa00f1064,0x03020100);
	rtd_outl(0xa00f1068,0x07060504);
	rtd_outl(0xa00f106c,0x11100908);
	rtd_outl(0xa00f1070,0x15141312);
	rtd_outl(0xa00f1074,0x19181716);
	rtd_outl(0xa00f1078,0x23222120);
	rtd_outl(0xa00f107c,0x27262524);
	rtd_outl(0xa00f1080,0x31302928);
	rtd_outl(0xa00f1084,0x35343332);
	rtd_outl(0xa00f1088,0x39383736);
	rtd_outl(0xa00f108c,0x43424140);
#else
 	//tx
	unsigned int ptrstart = 0x00401000, ptrend;
	int size = 0x600;

	printk("cache1 test...\n");
	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		rtd_outl(ptrstart, 0x55555555);
	}
#endif
}

void MAC_SETTING(void)
{
	rtd_outl(0xb8016000,0x52544c00);
	rtd_outl(0xb8016004,0x00080000);
	rtd_outl(0xb8016008,0xffffffff);
	rtd_outl(0xb801600c,0xffffffff);

	 rtd_outl(0xb8016038,0x06060606); // CR_reg, enrxcs,1, enrxvlan,1
	 rtd_outl(0xb801603c,0x0000ffff); // IMR_reg, enable IMR, clear ISR
	 
	 rtd_outl(0xb8016040,0x00000c00); // TCR_reg, ifg,3, lbk,0, txrr,0
	 rtd_outl(0xb8016044,0x0000000f); // RCR_reg, accept phy/bdr/mar
	// rtd_outl(0xb80161f0,0x000f8000); // RxFDP_reg
	 rtd_outl(0xb80161f0,0x00408000); // RxFDP_reg

	 rtd_outl(0xb80161f4,0x0f000f00); // RxRingSize_reg

	 rtd_outl(0xb8016230,0x0f000000); // ETNRXCPU_Des_Num_reg,0x0f
	//					# Des_Thres_on  , 0x00
	//					# Des_Thres_off , 0x00
	rtd_outl(0xb8016100,0x0040c000); // TXFDP1_reg
	rtd_outl(0xb8016110,0x0040d000); // TXFDP2_reg
	rtd_outl(0xb8016120,0x0040e000); // TXFDP3_reg
	rtd_outl(0xb8016130,0x0040f000); // TXFDP4_reg
}



void MAC1_SETTING(void)

{


#if 1
	unsigned int value;

	rtd_outl(0xb8016800,0x52544c00);  //eth address
	rtd_outl(0xb8016804,0x00080000);
	rtd_outl(0xb8016808,0xffffffff);
	rtd_outl(0xb801680c,0xffffffff);

//--	 rtd_outl(0xb8016838,0x06060606); // CR_reg, enrxcs,1, enrxvlan,1

	
	rtd_outl(0xb8016838,0x00000006);      	                // bits[2] 	:Receive VLAN de-tagging enable

	

	 rtd_outl(0xb801683c,0x0000ffff); // IMR_reg, enable IMR, clear ISR


	 rtd_outl(0xb8016840,0x00000f00); // TCR_reg, ifg,3, lbk,0, txrr,0    loopback



	
	 
	 rtd_outl(0xb8016844,0x0000000f); // RCR_reg, accept phy/bdr/mar
	// rtd_outl(0xb80161f0,0x000f8000); // RxFDP_reg
	 rtd_outl(0xb80169f0,0x00408000); // RxFDP_reg

	//-- rtd_outl(0xb80169f4,0x0f000f00); // RxRingSize_reg (256 descriptor)

rtd_outl(0xb80169f4,0x00000100); //32 descriptor  (cdo??)

	 rtd_outl(0xb8016a30,0x0f000800); // ETNRXCPU_Des_Num_reg,0x0f  & RX_FC_THRESHOLD
	//					# Des_Thres_on  , 0x00
	//					# Des_Thres_off , 0x00
	rtd_outl(0xb8016900,0x0040c000); // TXFDP1_reg


//rtd_outl(0xb8016980,0x0040c000);                    	// bits[31:8]	:TxFPD2	Tx First Descriptor Pointer to the Tx Ping 

	
//	rtd_outl(0xb8016910,0x0040d000); // TXFDP2_reg
//	rtd_outl(0xb8016920,0x0040e000); // TXFDP3_reg
//	rtd_outl(0xb8016930,0x0040f000); // TXFDP4_reg

    
    /* setup rx descriptor */	

//    rtd_outl(0xb8016800  + RxFDP,PHYSADDR((UINT32) pRxBDPtr));
//    rtd_outl(0xb8016800 + RxCDO,0);
    
    /* setup tx descriptor */
    /* Use Tx First Descriptor Pointer (FDP) for high priority queue. */
 //   rtd_outl(ioaddr + TxFDP1,PHYSADDR((UINT32) pTxBDPtr));
   // rtd_outl(ioaddr + TxCDO1,0);
    
    /* RCR (Rx config register) , don't accept error packet */
 //   rtd_outl(ioaddr + RCR,RCR_ALL);
        
    // Rx_Pse_Des_Thres = RX_FC_THRESHOLD;
  //  rtd_outb(ioaddr + Rx_Pse_Des_Thres,RX_FC_THRESHOLD);
    
    /* Rx descriptor Size */    
  //  rtd_outb(ioaddr + EthrntRxCPU_Des_Num,0);
        
    /* 32 descriptors */
 //   rtd_outb(ioaddr + RxRingSize,RxRingSize_32);
    
    /* TCR: IFG, Mode */
 //   rtd_outl(ioaddr + TCR,TCR_IFG(TCR_IFG_B011) | TCR_LBK1_LBK0(TCR_LBK1_LBK0_NORMAL) );
    
    /* Enable Tx/Rx Flow Control */    
	

	printk("debug0 %x\n",rtd_inl(0xb8016858));
	
 //--     rtd_outb(0xb8016858 + 3, (MSR_TXFCE | MSR_RXFCE));  //speed 100M

	printk("debug1 %x\n",rtd_inl(0xb8016858));


    value  = (ETHER_IO_CMD_RE|ETHER_IO_CMD_TE);
    // 2 pkts.
    value |= ETHER_IO_CMD_RxIntMitigation(0x1);
    // 128 byts
    value |= ETHER_IO_CMD_RXFTH1_0(0x3);
    // 1 x 82 us
    value |= ETHER_IO_CMD_RXPktTimer(0x1);
    
//    value |=  ETHER_IO_CMD_MXRXDMA2_1_0(0x1);
    
    value |=  ETHER_IO_CMD_TxIntMitigation(0x7);
    value |=  ETHER_IO_CMD_TXTH1_0(0X02);
//    value |=  ETHER_IO_CMD_MXTXDMA2_1_0(0X04);



    printk("ETHER_IO_CMD : value = 0x%x\n",value );

	printk("3....\n");
	 
 	rtd_outl(0xb8016a34, value);

	  printk("ETHER_IO_CMD : value = 0x%x\n",value );

	value = value | ETHER_IO_CMD_TXFNH;

	rtd_outl(0xb8016a34, value);

	  printk("ETHER_IO_CMD : value = 0x%x\n",value );

#else
rtd_outl(0xb8016800,0x52544c00);                      	// bits[31:24]	:IDR0 (ID Register 0)		
                                                // bits[23:16]	:IDR1 (ID Register 1)
                                                // bits[15:8]	:IDR2 (ID Register 2)
                                                // bits[7:0]	:IDR3 (ID Register 3)


rtd_outl(0xb8016804,0x00080000);                     	// bits[31:24]	:IDR4 (ID Register 4)
                                                // bits[23:16]	:IDR5 (ID Register 5)

					
rtd_outl(0xb8016808,0xffffffff);                      	// bits[31:24]	:MR0 (Multicast Register 0)
                                                // bits[23:16]	:MR1 (Multicast Register 1)
                                                // bits[15:8]	:MR2 (Multicast Register 2)
                                                // bits[7:0]	:MR3 (Multicast Register 3)

rtd_outl(0xb801680c,0xffffffff);                	// bits[31:24]	:MR4 (Multicast Register 0) 
                                        	// bits[23:16]	:MR5 (Multicast Register 1)
                                        	// bits[15:8]	:MR6 (Multicast Register 2)
		                        	            // bits[7:0]	:MR7 (Multicast Register 3)

//rtd_outl(0xb8016038,0x00000002)
rtd_outl(0xb8016838,0x00000006);      	                // bits[2] 	:Receive VLAN de-tagging enable
                                                //		1'b1 -> Enable
                                                //		1'b0 -> Disable		
                                                // bits[1]	:Receive cgecksum offload
                                                //		1'b1 -> Enable
                                                //		1'b0 -> Disable		
                                                // bits[0]	:Software Reset
                                                //		1'b1 -> Reset
                                                //		1'b0 -> Non-reset		

//rtd_outl(0xb8016040,0x00000c00)                      	// bits[12:10] 	:Interframe Gap Time 
rtd_outl(0xb8016840,0x00000f00);                      	// bits[12:10] 	:Interframe Gap Time 
                                                // 		2'b11 -> 960 ns
                                                // bits[9:8]   	:Loopback Test Mode
                                                // 		2'b00 -> Normal Mode                 
                                                // 		2'b11 -> MII Loopback Mode (TXD -> RXV)
                                                // 		Others,> Reserved			

rtd_outl(0xb8016844,0x0000000f);                      	// bits[6] 	:AFL 
																								// bits[5]	:AER
																								// bits[4]	:AR
																								// bits[3]	:AB
																								//		1'b1 -> Accept Broadcast packets
																								// bits[2] 	:AM
																								//		1'b1 -> Accept Multicast packets		
																								// bits[1]	:APM
																								//		1'b1 -> Accept physical match packets
																								// bits[0]	:AAP
																								//		1'b1 -> Accept all packets with physical destination address
	  
rtd_outl(0xb80169f0,0x00408000);												// bits[31:8]	:RX First Descriptor Pointer to the Tx Ring
rtd_outl(0xb80169f4,0x00000000);												// bits[21:16]	:Rx Current Descriptor Offset
                                                // bits[9:8]	:RX Ring Size
                                                //		2'b00 -> 16 descriptors
                                                //		2'b01 -> 32 descriptors
                                                //		2'b10 -> 64 descriptors		
					
rtd_outl(0xb8016a30,0x0f000000);          							// bits[29:24]	:EthrntRxCPU_Des_Num	
                                                // bits[16]	:WRAP
                                                // bits[12:8]	:Rx_Pse_Des_Thres	
					
rtd_outl(0xb8016980,0x0040c000);                    	// bits[31:8]	:TxFPD2	Tx First Descriptor Pointer to the Tx Ping 



//rtd_outl(0xb8016238,s0,0x00000003,s1)	// rx/tx endian swap

rtd_outl(0xb8016a34,0x0019390c);                      	// bits[31],1'b1:speed up MDC clk
                                    						// bits[20:19]	:Tx Threshold
						                                    //		2'b00 -> 64 bytes
						                                    //		2'b01 -> 128 bytes
						                                    // 		2'b11 -> 256 bytes
						                                    //		others-> Reserved 
						                                    // bits[18:16]	:Packets received before TxOK
						                                    //		3'b000-> Not allowed
						                                    //		3'b001-> 1 pkts
						                                    //		3'b010-> 2 pkts
						                                    // bits[15:13]	:Time to trigger RxOK
						                                    //		3'b000-> No time setting
						                                    //		3'b001-> the timer interval defining a multiple of 82 us
				        	                              // bits[12:11]  :RXFTH RX FIFO Threshold
						                                    //		2'b00 -> N/A
						                                    //		2'b01 -> 64 bytes
						                                    //		2'b10 -> 128 bytes
						                                    //		2'b11 -> 256 bytes
				                                    		// bits[10:8]	:RxIntMiti
						                                    //		3'b000-> not allowed
						                                    //		3'b001-> 1 pkts
						                                    //		3'b010-> 2 pkts
						                                    // bits[3]	:MII Rx Enable
						                                    //		1'b1 : Enable
						                                    //		1'b0 : Disable
						                                    // bits[2]	:MII Tx Enable
						                                    //		1'b1 : Enable
						                                    //		1'b0 : Disable
						                                    // bits[1]	:TxFNL Low Priority DMA Enable
						                                    // bits[0]	:HxFNL Low Priority DMA Enable


rtd_outl(0xb8016a34,0x0019390e);                      // bits[1],1'b1 : enable TxFDP2, start!



	#endif



}



BOOL LOOPBACK_CHECK(void)
{
	unsigned int ptrstart,ptrend,size;
	int i=0;
	while(1){
		if ((rtd_inl(0x00408000)&_BIT31)==0){
			printk("ETN RX1 received \n");
			break;
		}
		ms_delay(10);
		i++;
		if (i>300){
			break;
		}
	};
	
	ptrstart = 0x00400000;
	//ptrstart = 0x00401000;
	size = 0x300;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0x55555555)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
			return 0;
		}
		else
			return 1;
	}

	return 1;
}


void QC_Eth_MacLoopBack(void)
{
	printk("crt init...\n");

	unsigned int ptrstart1 = 0x00400000, ptrend1;
	//unsigned int ptrstart,ptrend,size;
	int i=0;

	//ddr access test
	int size1 = 0x100;

	ptrend1 = ptrstart1 + size1;
	for( ; ptrstart1 < ptrend1 ; ptrstart1 +=4)
	{
		rtd_outl(ptrstart1, 0xaaaaaaaa);
	}

	ptrstart1 = 0x00400000;
	ptrend1 = ptrstart1 + size1;
	for( ; ptrstart1 < ptrend1 ; ptrstart1 +=4)
	{
		if (rtd_inl(ptrstart1) != 0xaaaaaaaa)
		{
			printk("error1.... %x\n",rtd_inl(ptrstart1));
		}

	}


	//pinmux

	rtd_outl(0xb8000820,0xf0000000);
	rtd_outl(0xb8000824,0x000000f0);
	rtd_outl(0xb8000828,0xf0000000);
	rtd_outl(0xb800082c,0x00000000);
	rtd_outl(0xb8000830,0x00000000);

ms_delay(200);


	GETN_CRT();
#if 0
	SET_FUSE_READY();

	PHY_STATUS();

	LINK_STATUS();

	LINK_SPEED();

	PHY_SETTING();

	LINK_SPEED();
#endif




// add by sychang 2007.09.19

rtd_outl(0xb8016860,0x00000408);      // turn-off PWRDN_PLL_L , debug_4byte_write 
rtd_outl(0xb8016838,0x00000001);     // ethernet reset  
rtd_outl(0xb8016838,0x0000000a);      // ethernet reset
//rtd_outl(0xb8016200,0x000002d8)      // enable etn debug port on FPGA  

ms_delay(100);


	RTD2885_LAN_PHY_ID = 1; 
	      ioaddr=RTD2885_LAN_BASE2;

		 


	rtd_outl(0xb801685c, RTD2885_LAN_PHY_ID << 26 | 0x10000);
	printk("c............\n");
	 ms_delay(2000);
	  printk(" i = %d read link status=%x\n",i,rtd_inl(0xb801685c)); // --> 0x840179ed;


	

	 


#if 1

//--	PHY_SETTING();
	

	RX_DESCRIPTOR();

	TX_DESCRIPTOR();

	TX_DATA();

	MAC1_SETTING();


//	rtd_outl(0xb8016a34,0x70140031);	// RX/TX enable

  

	
	ms_delay(1000);

      printk("own bit.. %x %x\n",rtd_inl(0x0040c000),rtd_inl(0x0040c010));


	i=0;
	while(1){
		if ((rtd_inl(0x0040c020)&_BIT31)==0){//wait Tx own bit ->0
			printk("ETN TX sent OK... \n");
			break;
		}
		ms_delay(10);
		i++;
		if (i>300){
			printk("ETN TX sent FAIL... \n");
			break;
		}
	}	

//	printk("@@@@@@@%x\n",rtd_inl(0x0040c000));

//--	LINK_SPEED();


	LOOPBACK_CHECK();

#endif

#if 0
	//test 
	ptrstart = 0x00408000;
	for (i=0;i<10;i++){
		while(1){
			if ((rtd_inl(ptrstart)&_BIT31)==0){
				printk("ETN RX received = %d\n",i);
				printk("0xb801603c=%x\n",rtd_inl(0xb801603c));
				break;
			}
			ms_delay(10);
		};
		ptrstart = (ptrstart+0x10);
	}
#endif
#if 0
	//RX Descriptor 1 Received
	i=0;
	while(1){
		if ((rtd_inl(0x00408000)&_BIT31)==0){
			printk("ETN RX1 received \n");
			break;
		}
		ms_delay(10);
		i++;
		if (i>300){
			break;
		}
	};

	//printk("0xb801603c=%x\n",rtd_inl(0xb801603c));
	
	ptrstart = 0x00400000;
	size = 0x300;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0x55555555)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
		
	}

	//RX Descriptor 2 Received
	while(1){
		if ((rtd_inl(0x00408010)&_BIT31)==0){
			printk("ETN RX2 received \n");
			break;
		}
		ms_delay(10);
	};

	printk("0xb801603c=%x\n",rtd_inl(0xb801603c));

	ptrstart = 0x00400100;
	size = 0x455;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0xaaaaaaaa)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
	}

	//RX Descriptor 3 Received
	while(1){
		if ((rtd_inl(0x00408020)&_BIT31)==0){
			printk("ETN RX3 received \n");
			break;
		}
		ms_delay(10);
	};

	printk("0xb801603c=%x\n",rtd_inl(0xb801603c));

	ptrstart = 0x00400200;
	size = 0x80;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0x55555555)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
	}	
#endif
	printk("ETN script end!!!\n");


}


BOOL QC_GETN_Script(void)
{
	printk("crt init...\n");

	unsigned int ptrstart1 = 0x00400000, ptrend1;
	//unsigned int ptrstart,ptrend,size;
	int i=0;

	//ddr access test
	int size1 = 0x100;

	ptrend1 = ptrstart1 + size1;
	for( ; ptrstart1 < ptrend1 ; ptrstart1 +=4)
	{
		rtd_outl(ptrstart1, 0xaaaaaaaa);
	}

	ptrstart1 = 0x00400000;
	ptrend1 = ptrstart1 + size1;
	for( ; ptrstart1 < ptrend1 ; ptrstart1 +=4)
	{
		if (rtd_inl(ptrstart1) != 0xaaaaaaaa)
		{
			printk("error1.... %x\n",rtd_inl(ptrstart1));
		}
		
	}

	GETN_CRT();

	SET_FUSE_READY();

	PHY_STATUS();

	LINK_STATUS();

	LINK_SPEED();

	PHY_SETTING();

	LINK_SPEED();

	RX_DESCRIPTOR();

	TX_DESCRIPTOR();

	TX_DATA();

	MAC_SETTING();

	rtd_outl(0xb8016234,0x70140031);	// RX/TX enable

	ms_delay(1000);

	i=0;
	while(1){
		if ((rtd_inl(0x0040c020)&_BIT31)==0){//wait Tx own bit ->0
			printk("ETN TX sent OK... \n");
			break;
		}
		ms_delay(10);
		i++;
		if (i>300){
			printk("ETN TX sent FAIL... \n");
			break;
		}
	}	

	//printk("@@@@@@@%x\n",rtd_inl(0x0040c000));

	LINK_SPEED();


	if (LOOPBACK_CHECK())
		return 1;
	else
		return 0;
		
#if 0
	//test 
	ptrstart = 0x00408000;
	for (i=0;i<10;i++){
		while(1){
			if ((rtd_inl(ptrstart)&_BIT31)==0){
				printk("ETN RX received = %d\n",i);
				printk("0xb801603c=%x\n",rtd_inl(0xb801603c));
				printk("data length=%d\n",(rtd_inl(ptrstart)&0x7ff));
				break;
			}
			ms_delay(10);
			if (rtd_inl(0xb801603c)&_BIT4)
				printk("rx fifo overflow \n");
		};
		ptrstart = (ptrstart+0x10);
	}
#endif
#if 0
	//RX Descriptor 1 Received
	i=0;
	while(1){
		if ((rtd_inl(0x00408000)&_BIT31)==0){
			printk("ETN RX1 received \n");
			break;
		}
		ms_delay(10);
		i++;
		if (i>300){
			break;
		}
	};

	//printk("0xb801603c=%x\n",rtd_inl(0xb801603c));
	
	ptrstart = 0x00400000;
	size = 0x300;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0x55555555)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
		
	}

	//RX Descriptor 2 Received
	while(1){
		if ((rtd_inl(0x00408010)&_BIT31)==0){
			printk("ETN RX2 received \n");
			break;
		}
		ms_delay(10);
	};

	printk("0xb801603c=%x\n",rtd_inl(0xb801603c));

	ptrstart = 0x00400100;
	size = 0x455;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0xaaaaaaaa)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
	}

	//RX Descriptor 3 Received
	while(1){
		if ((rtd_inl(0x00408020)&_BIT31)==0){
			printk("ETN RX3 received \n");
			break;
		}
		ms_delay(10);
	};

	printk("0xb801603c=%x\n",rtd_inl(0xb801603c));

	ptrstart = 0x00400200;
	size = 0x80;

	ptrend = ptrstart + size;
	for( ; ptrstart < ptrend ; ptrstart +=4)
	{
		if (rtd_inl(ptrstart) != 0x55555555)
		{
			printk("error.... %x %x\n",rtd_inl(ptrstart),ptrstart);
		}
	}	
#endif

	printk("ETN script end!!!\n");
}




static int mac_loopback(void)
{

#if 0
	//#include "darwin_debug_pin-1.tbl"   // top debug port

// system_CLK_EN disable
rtd_outl(0xb800000c,0xfffffdff)
// system_ENET reset
rtd_outl(0xb8000000,0xffff9fff)
//HDMI band gap
ScalerTimer_DelayXms(100); 

// system_CLK_EN
rtd_outl(0xb800000c,0xffffffff)
// system_CLK_EN disable
rtd_outl(0xb800000c,0xfffffdff)

// system_ENET not reset
rtd_outl(0xb8000000,0xffffffff)
// system_CLK_EN
rtd_outl(0xb800000c,0xffffffff)
//ScalerTimer_DelayXms(100);
#endif


GETN_CRT();



//---------------------------------------------------------------------// 
// Load 256 bytes data to DMEM
//---------------------------------------------------------------------// 
//#include "Darwin_ENET_LBK_DDRdata.tbl"
//#include "Darwin_ENET_LBK_DDRdata1.tbl"
//#include "Darwin_ENET_LBK_DDRdata2.tbl"
//#include "Darwin_ENET_LBK_DDRdata3.tbl"
//#include "Darwin_ENET_LBK_DDRdata4.tbl"
//#include "Darwin_ENET_LBK_DDRdata5.tbl"
//#include "Darwin_ENET_LBK_DDRdata00.tbl"


rtd_outl(0x00401000, 0x1234567);


//---------------------------------------------------------------------//
// ethernet_phy POWER setting
//---------------------------------------------------------------------//

// add by sychang 2007.09.19

rtd_outl(0xb8016860,0x00000408);      // turn-off PWRDN_PLL_L , debug_4byte_write 
rtd_outl(0xb8016838,0x00000001);     // ethernet reset  
rtd_outl(0xb8016838,0x0000000a);      // ethernet reset
//rtd_outl(0xb8016200,0x000002d8)      // enable etn debug port on FPGA  

ms_delay(100);



//---------------------------------------------------------------------// 
// PHY Setting
//---------------------------------------------------------------------// 

//rtd_outl(0xb801605c,0x84004100)				// 10MHZ

//rtd_outl(0xb801605c,0x84040061)				// 10MHZ

//rtd_outl(0xb801605c,0x84006100)				// 100MHZ PHY digital LBK

#if 0  //chengying
rtd_outl(0xb801605c,0x84002100)				// 100MHZ

rtd_outl(0xb801605c,0x84040181)				// 100MHZ
#endif

//rtd_outl(0xb801605c,0x84100300)				// write to phy_dig through MII IF

//rtd_outl(0xb801605c,0x84110280)				// write to phy_dig through MII IF set DIGLBK


//---------------------------------------------------------------------// 
// Tx Descriptor
//---------------------------------------------------------------------// 
//先把資料放到 Memory 0xa0001000
// 1th Descriptor


//	RX_DESCRIPTOR();

//	TX_DESCRIPTOR();

//	TX_DATA();



#if 0
// CPU need virtual address, HW need physical address
rtd_outl(0x0000f000,0xb0800100)      	// 256 Bytes	
rtd_outl(0x0000f004,0x00001000)      	// Packet Storage Address
rtd_outl(0x0000f008,0x00011234)
rtd_outl(0x0000f00c,0x00000000)

// 2th Descriptor

rtd_outl(0xa000f010,0x00800100)      	// 256 Bytes
rtd_outl(0xa000f014,0x00001000)     	// Packet Storage Address	
rtd_outl(0xa000f018,0x00011234)
rtd_outl(0xa000f01c,0x00000000)
#else


	rtd_outl(0x0040c000,0xb0800100);	//own, fs,  //a0800010
	rtd_outl(0x0040c004,0x00401000);  //00401000
	rtd_outl(0x0040c008,0x00011234);
	rtd_outl(0x0040c00c,0x00000000);

	rtd_outl(0x0040c010,0x00800100);	//own  //80800010
	rtd_outl(0x0040c014,0x00401000);   //00401100
	rtd_outl(0x0040c018,0x00011234);
	rtd_outl(0x0040c01c,0x00000000);


#endif

//---------------------------------------------------------------------// 
// Rx Descriptor
//---------------------------------------------------------------------// 
//先把資料放回到 Memory 0xa000f200

#if 0
// 1th Descriptor

rtd_outl(0xa000f100,0x80000800)
rtd_outl(0xa000f104,0x0000f200)
rtd_outl(0xa000f108,0x00000000)
rtd_outl(0xa000f10c,0x00000000)

// 2th Descriptor

rtd_outl(0xa000f110,0x00000100)
rtd_outl(0xa000f114,0x0000f800)
rtd_outl(0xa000f118,0x00000000)
rtd_outl(0xa000f11c,0x00000000)
#else


	rtd_outl(0x00408000,0x80000800); // 80000800
	//rtd_outl(0xa00f8004,0x00000f00); // 000f0000  
	rtd_outl(0x00408004,0x00400000);//00400000

	rtd_outl(0x00408010,0x00000100); //80000800
	//rtd_outl(0xa00f8014,0x00010f00); //000f0100
	rtd_outl(0x00408014,0x00400100); //00400100


#endif

//---------------------------------------------------------------------// 
// Main Code
//---------------------------------------------------------------------// 


rtd_outl(0xb8016800,0x52544c00);                      	// bits[31:24]	:IDR0 (ID Register 0)		
                                                // bits[23:16]	:IDR1 (ID Register 1)
                                                // bits[15:8]	:IDR2 (ID Register 2)
                                                // bits[7:0]	:IDR3 (ID Register 3)


rtd_outl(0xb8016804,0x00080000);                     	// bits[31:24]	:IDR4 (ID Register 4)
                                                // bits[23:16]	:IDR5 (ID Register 5)

					
rtd_outl(0xb8016808,0xffffffff);                      	// bits[31:24]	:MR0 (Multicast Register 0)
                                                // bits[23:16]	:MR1 (Multicast Register 1)
                                                // bits[15:8]	:MR2 (Multicast Register 2)
                                                // bits[7:0]	:MR3 (Multicast Register 3)

rtd_outl(0xb801680c,0xffffffff);                	// bits[31:24]	:MR4 (Multicast Register 0) 
                                        	// bits[23:16]	:MR5 (Multicast Register 1)
                                        	// bits[15:8]	:MR6 (Multicast Register 2)
		                        	            // bits[7:0]	:MR7 (Multicast Register 3)

//rtd_outl(0xb8016038,0x00000002)
rtd_outl(0xb8016838,0x00000006);      	                // bits[2] 	:Receive VLAN de-tagging enable
                                                //		1'b1 -> Enable
                                                //		1'b0 -> Disable		
                                                // bits[1]	:Receive cgecksum offload
                                                //		1'b1 -> Enable
                                                //		1'b0 -> Disable		
                                                // bits[0]	:Software Reset
                                                //		1'b1 -> Reset
                                                //		1'b0 -> Non-reset		

//rtd_outl(0xb8016040,0x00000c00)                      	// bits[12:10] 	:Interframe Gap Time 
rtd_outl(0xb8016840,0x00000f00);                      	// bits[12:10] 	:Interframe Gap Time 
                                                // 		2'b11 -> 960 ns
                                                // bits[9:8]   	:Loopback Test Mode
                                                // 		2'b00 -> Normal Mode                 
                                                // 		2'b11 -> MII Loopback Mode (TXD -> RXV)
                                                // 		Others,> Reserved			

rtd_outl(0xb8016844,0x0000000f);                      	// bits[6] 	:AFL 
																								// bits[5]	:AER
																								// bits[4]	:AR
																								// bits[3]	:AB
																								//		1'b1 -> Accept Broadcast packets
																								// bits[2] 	:AM
																								//		1'b1 -> Accept Multicast packets		
																								// bits[1]	:APM
																								//		1'b1 -> Accept physical match packets
																								// bits[0]	:AAP
																								//		1'b1 -> Accept all packets with physical destination address
	  
rtd_outl(0xb80169f0,0x00408000);												// bits[31:8]	:RX First Descriptor Pointer to the Tx Ring
rtd_outl(0xb80169f4,0x00000000);												// bits[21:16]	:Rx Current Descriptor Offset
                                                // bits[9:8]	:RX Ring Size
                                                //		2'b00 -> 16 descriptors
                                                //		2'b01 -> 32 descriptors
                                                //		2'b10 -> 64 descriptors		
					
rtd_outl(0xb8016a30,0x0f000000);          							// bits[29:24]	:EthrntRxCPU_Des_Num	
                                                // bits[16]	:WRAP
                                                // bits[12:8]	:Rx_Pse_Des_Thres	
					
rtd_outl(0xb8016980,0x0040c000);                    	// bits[31:8]	:TxFPD2	Tx First Descriptor Pointer to the Tx Ping 



//rtd_outl(0xb8016238,s0,0x00000003,s1)	// rx/tx endian swap

rtd_outl(0xb8016a34,0x0019390c);                      	// bits[31],1'b1:speed up MDC clk
                                    						// bits[20:19]	:Tx Threshold
						                                    //		2'b00 -> 64 bytes
						                                    //		2'b01 -> 128 bytes
						                                    // 		2'b11 -> 256 bytes
						                                    //		others-> Reserved 
						                                    // bits[18:16]	:Packets received before TxOK
						                                    //		3'b000-> Not allowed
						                                    //		3'b001-> 1 pkts
						                                    //		3'b010-> 2 pkts
						                                    // bits[15:13]	:Time to trigger RxOK
						                                    //		3'b000-> No time setting
						                                    //		3'b001-> the timer interval defining a multiple of 82 us
				        	                              // bits[12:11]  :RXFTH RX FIFO Threshold
						                                    //		2'b00 -> N/A
						                                    //		2'b01 -> 64 bytes
						                                    //		2'b10 -> 128 bytes
						                                    //		2'b11 -> 256 bytes
				                                    		// bits[10:8]	:RxIntMiti
						                                    //		3'b000-> not allowed
						                                    //		3'b001-> 1 pkts
						                                    //		3'b010-> 2 pkts
						                                    // bits[3]	:MII Rx Enable
						                                    //		1'b1 : Enable
						                                    //		1'b0 : Disable
						                                    // bits[2]	:MII Tx Enable
						                                    //		1'b1 : Enable
						                                    //		1'b0 : Disable
						                                    // bits[1]	:TxFNL Low Priority DMA Enable
						                                    // bits[0]	:HxFNL Low Priority DMA Enable


rtd_outl(0xb8016a34,0x0019390e);                      // bits[1],1'b1 : enable TxFDP2, start!



printk("%x\n",rtd_inl(0x0040c000));
ms_delay(100);
printk("%x\n",rtd_inl(0x0040c000));

ms_delay(100);
printk("rx receive = %x\n",rtd_inl(0x00400000));

}





void MAC_Pad_PinMux_Setting(void)
{
	rtd_outl(0xb8000820,0xf0000000);
	rtd_outl(0xb8000824,0x000000f0);
	rtd_outl(0xb8000828,0xf0000000);
	rtd_outl(0xb800082c,0x00000000);
	rtd_outl(0xb8000830,0x00000000);
	ms_delay(10);

}



BOOL QC_Verifier_GETN(void)
{
      int ret=0;

	 ioaddr=RTD2885_LAN_BASE;
	RTD2885_LAN_PHY_ID=RTD2885_LAN_PHY1_ID;

#if 0 //def CONFIG_GETH_VERIFY
	//reg_power_test();
	//enter_aldps_mode();
	//EEEP_test();
	//EEE_test_10M();
	//EEE_test_100M();
	//EEE_test_1000M();
//	performance_test_10M();
	//performance_test_100M();
//	performance_test_1000M();
//	performance_test_TX_10M();
	//wake_on_lan();
	//wake_on_lan_aldps_reset_pmeb();
	
	//getn_efuse_write();
//	test1();
#if 0
	GETN_CRT();
	getn_load_efusedata2dout();
	SET_FUSE_READY();
	PHY_STATUS();
	GreenTable_Modify();
#endif
#else

#if CONFIG_EQC// output loopback, for QC test
	
	printf("ETN1 PHY outputpad LBK\n");

	
	if(lan_qc_verify() == VERIFY_FAIL)
	{
		if(lan_qc_verify() == VERIFY_FAIL)	
			ret=1;
	}
#else
	printf("FT ETN1 PHY outputpad LBK\n");
	if(lan_ft_verify() == VERIFY_FAIL)
	{
		if(lan_ft_verify() == VERIFY_FAIL)	
			ret=1;
	}
#endif
	
#if 0
	MAC_Pad_PinMux_Setting();
//	GETN_CRT();
	ioaddr=RTD2885_LAN_BASE2;
	RTD2885_LAN_PHY_ID=RTD2885_LAN_PHY2_ID;  
	loopback_mode = MAC_LOOP_BACK;
	//loopback_mode = PHY_LOOP_BACK;
	//loopback_mode = NORMAL;

	if (loopback_mode == MAC_LOOP_BACK)
		printf("ETN2(10/100M) mode =>MAC_LOOP_BACK\n");
	else if (loopback_mode == PHY_LOOP_BACK)
		printf("ETN2(10/100M) mode =>PHY_LOOP_BACK\n");
	else
		printf("ETN2(10/100M) mode =>NORMAL\n");
	

#if two_byte_align_test
	two_byte_align_100M_test();
#else	
      if(lan_qc_verify_MacLBK_100M() == VERIFY_FAIL)
	{
		if(lan_qc_verify_MacLBK_100M() == VERIFY_FAIL)	
			ret=1;
	}	  
#endif
#endif
#endif	  

#if 0
      
      ioaddr=RTD2885_LAN_BASE2;
	RTD2885_LAN_PHY_ID=RTD2885_LAN_PHY2_ID;  

	loopback_mode = MAC_LOOP_BACK;

      if(lan_qc_verify_DLBK_100M() == VERIFY_FAIL)
	{
		if(lan_qc_verify_DLBK_100M() == VERIFY_FAIL)	
			ret=1;
	}	  

#endif	  

//PHY verification - 10M pattern
#if 0
      if(rtl8139cp_10M_tx_verify() != 1)
            {
                printk("rtl8139cp_10M_tx_verify fail.\n");
            }
#endif
	  
//smartbits LBK testing
#if 0
            if(rtl8139cp_smartbit_test_export() != 1)
            {
                printk("rtl8139cp_smartbit_modify_export fail.\n");
            }
#endif	  
      return ret;  
}


static void rtl8139cp_verify_dump_desc_none(UINT8 mode)
{
	NIC_FD_T *ptr=NULL;
	int i=0,num=0;	
	unsigned int tmp;
    if (mode == 1) {
       ptr = pRxBDPtr;
       num = RX_QC_DESC_NUM;       
    }   
    else {
       ptr = pTxBDPtr;
       num = TX_QC_DESC_NUM;       
    }   
    
    if (!ptr)
    	return;
    	    	
    printk("---------------------------\n");
    	
    for (i=0;i<num;i++) {
    	tmp = at_swap_32(ptr[i].StsLen)+at_swap_32(ptr[i].DataPtr)+at_swap_32(ptr[i].VLan);
    }	
          
}

static void rtl8139cp_verify_dump_desc(UINT8 mode)
{
	NIC_FD_T *ptr=NULL;
	int i=0,num=0;	
	
    if (mode == 1) {
       ptr = pRxBDPtr;
       num = RX_QC_DESC_NUM;       
       printk("Dump Rx Desc : (pRxBDPtr = 0x%x,rxBDtail = %d)\n",pRxBDPtr,rxBDtail);
    }   
    else {
       ptr = pTxBDPtr;
       num = TX_QC_DESC_NUM;       
       printk("Dump Tx Desc : (pTxBDPtr = 0x%x,txBDtail = %d)\n",pTxBDPtr,txBDtail);
    }   
    
    if (!ptr)
    	return;
    	    	
    printk("---------------------------\n");
    	
    for (i=0;i<num;i++) {
#if LITTLEENDIA_ETH
		
    	printk("ptr[%d].StsLen = 0x%lu\n",i,at_swap_32(ptr[i].StsLen));
    	printk("ptr[%d].DataPtr = 0x%lu\n",i,at_swap_32(ptr[i].DataPtr));	 
    	printk("ptr[%d].VLan = 0x%lu\n",i,at_swap_32(ptr[i].VLan));
    	printk("---------------------------\n");
#else
	printk("ptr[%d].StsLen = 0x%x\n",i,ptr[i].StsLen);
    	printk("ptr[%d].DataPtr = 0x%x\n",i,ptr[i].DataPtr);	 
    	printk("ptr[%d].VLan = 0x%x\n",i,ptr[i].VLan);
    	printk("---------------------------\n");
#endif
    }	
          
}

/*======================= PHY/MDIO control ========================*/
static UINT16 inline rtl8139cp_verify_mdio_read(UINT8 PhyID,UINT8 RegAddr)
{	
	unsigned int i=0;

	rtd_outl(ioaddr+MIIAR,(MIIAR_RegAddr4_0(RegAddr)| MIIAR_PHYAddress(PhyID)));
	// Wait 5 ms
	udelay(5000);
	
	// 50 ms
	i = 5000;	
	while (!(rtd_inl(ioaddr+MIIAR) & MIIAR_Flag_Write) && (--i) )
	{
		udelay(10);
	};
	
	if (i==0) 
    	printk("rtl8139cp_verify_mdio_read() TimeOut (Reg = %d, PhyID = %d).\n",RegAddr,PhyID); 
			
	return MIIAR_Data15_0(rtd_inl(ioaddr+MIIAR));
}

//gphy
static void inline rtl6330cp_verify_phy_set_speed(UINT8 phyID,UINT8 mode)
{
        UINT16 value=0; 
        unsigned int i=0;
               

        value = rtl6330cp_verify_mdio_read(phyID,MII_REG0);
	 value &= ~GMII_REG0_Loopback;
        value &= ~GMII_REG0_Reset;
        value &= ~GMII_REG0_Auto_Negotiation_Enable;     
	 value &= ~GMII_REG0_Speed_1;
	 value &= ~GMII_REG0_Speed_0;

        // Set speed.
        if (mode == PHY_100M)
                value |= GMII_REG0_Speed_0;
	else if (mode == PHY_1000M)
		 value |= GMII_REG0_Speed_1;


        rtl6330cp_verify_mdio_write(phyID,MII_REG0,value);

	// 50 ms
	i = 5000;
	// while ((rtl8139cp_verify_mdio_read(phyID,MII_REG1) & MII_REG1_LINK_OK) & (--i));

#if 0
	#ifdef BYTE_ENDIAN_BUG
	while ((rtd_inb(ioaddr + MSR + 3) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};	

	#else
	while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};	
	#endif

	
	if (i==0) 
    		printk("rtl6330cp_verify_phy_set_speed() link fail\n");		

#endif

	
        
}



static void inline rtl8139cp_verify_phy_set_speed(UINT8 phyID,UINT8 mode)
{
        UINT16 value=0; 
        unsigned int i=0;
               

        value = rtl8139cp_verify_mdio_read(phyID,MII_REG0);
        value &= ~MII_REG0_Reset;
        value &= ~MII_REG0_Speed_Select_100M;
        value &= ~MII_REG0_Auto_Negotiation_Enable;        

        // Set speed.
        if (mode == PHY_100M)
                value |= MII_REG0_Speed_Select_100M;

	 rtd_outl(0xb801685c, 0x04010000);       // read link status
	 ms_delay(0x10);
	 printk(" read link status=%x\n",rtd_inl(0xb801685c)); // --> 0x840179ed;
		

        rtl8139cp_verify_mdio_write(phyID,MII_REG0,value);


	// 50 ms
	i = 5000;
	// while ((rtl8139cp_verify_mdio_read(phyID,MII_REG1) & MII_REG1_LINK_OK) & (--i));

	#ifdef BYTE_ENDIAN_BUG
	while ((rtd_inb(ioaddr + MSR + 3) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};	

	#else
	while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};	
	#endif
	
	if (i==0) 
    		printk("rtl8139cp_verify_phy_set_speed() link fail\n");		



	
        
}

static void inline rtl8139cp_verify_phy_set_lbk(UINT8 phyID,UINT8 mode)
{
        UINT16 value=0; 
   
               

        value = rtl8139cp_verify_mdio_read(phyID,MII_REG0);
  	  value &= ~MII_REG0_Reset;
        value &= ~MII_REG0_Loopback;

	 // Set LBK.
        if (mode == PHY_LBK_Enable)
                value |= MII_REG0_Loopback;

        rtl8139cp_verify_mdio_write(phyID,MII_REG0,value);        
        
}


static void inline rtl6330cp_verify_phy_set_duplex_mode(UINT8 phyID,UINT8 mode)
{
        UINT16 value=0;

        value = rtl8139cp_verify_mdio_read(phyID,MII_REG0);
        value &= ~GMII_REG0_Reset;
        value &= ~GMII_REG0_Auto_Negotiation_Enable;
        value &= ~GMII_REG0_Duplex_Mode;
        // Set duplex mode.
        if (mode == PHY_Full_Duplex)
                value |= GMII_REG0_Duplex_Mode;

        rtl6330cp_verify_mdio_write(phyID,MII_REG0,value);        

    	// 50 ms
/*
    	i = 5000;
    	while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
    	{
        	udelay(10);
    	};


    	if (i==0)
            printk("rtl8139cp_verify_phy_set_duplex_mode() link fail\n");
*/
}


static void inline rtl8139cp_verify_phy_set_duplex_mode(UINT8 phyID,UINT8 mode)
{
        UINT16 value=0;
	 //unsigned int i=0;

        value = rtl8139cp_verify_mdio_read(phyID,MII_REG0);
        value &= ~MII_REG0_Reset;
        value &= ~MII_REG0_Auto_Negotiation_Enable;
        value &= ~MII_REG0_Duplex_Mode;
        // Set duplex mode.
        if (mode == PHY_Full_Duplex)
                value |= MII_REG0_Duplex_Mode;

        rtl8139cp_verify_mdio_write(phyID,MII_REG0,value);        

    	// 50 ms
/*
    	i = 5000;
    	while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
    	{
        	udelay(10);
    	};


    	if (i==0)
            printk("rtl8139cp_verify_phy_set_duplex_mode() link fail\n");
*/
}
#if 1
static void inline rtl8139cp_verify_phy_restart_auto_negotiation(UINT8 phyID)
{
	unsigned int i=0;

	rtl8139cp_verify_mdio_write(phyID,MII_REG0,(rtl8139cp_verify_mdio_read(phyID,MII_REG0)|MII_REG0_Restart_Auto_Negotiation));
	// Wait 5 ms
	udelay(5000);
	//i = 5000;
	i = 100;
	while (!(rtl8139cp_verify_mdio_read(phyID,MII_REG1)&MII_REG1_AUTO_NEG_COMPLETE) && (--i)) ;

	if (i==0)
    	printk("rtl8139cp_verify_phy_restart_auto_negotiation() no complete\n");
}


static void inline rtl8139cp_verify_phy_auto_negotiation(UINT8 phyID)
{
	unsigned int i=0;
	// Phy reset.
	//rtl8139cp_verify_mdio_write(RL8139CP_LAN_PHY_ID,MII_REG0,MII_REG0_Reset);
	//rtl8139cp_verify_mdio_write(phyID,MII_REG0,MII_REG0_Auto_Negotiation_Enable);
	rtl8139cp_verify_phy_restart_auto_negotiation(phyID);

	// 50 ms
	i = 500;
	//i = 10;
	while (!(rtl8139cp_verify_mdio_read(phyID,MII_REG1) & MII_REG1_LINK_OK) && (--i))
	//while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};
	
	//printk("rtl8139cp_verify_mdio_read(phyID,MII_REG1)=%x\n",rtl8139cp_verify_mdio_read(phyID,MII_REG1));
	if (i==0)
		printk("rtl8139cp_verify_phy_auto_negotiation() link fail\n");
}
#else
static void inline rtl8139cp_verify_phy_auto_negotiation(UINT8 phyID)
{		
	unsigned int i=0;
	// Phy reset. 
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,MII_REG0_Reset);
			
	rtl8139cp_verify_mdio_write(phyID,MII_REG0,MII_REG0_Auto_Negotiation_Enable);
			    
	// 50 ms
	i = 5000;
	// while ((rtl8139cp_verify_mdio_read(phyID,MII_REG1) & MII_REG1_LINK_OK) & (--i));	
	while ((rtd_inb(ioaddr + MSR) & MSR_LINKB) && (--i))
	{
		udelay(10);
	};	
	
	if (i==0) 
    		printk("rtl8139cp_verify_phy_auto_negotiation() link fail\n");		
}
#endif
/*======================= RTL8139CP H/W control ========================*/
static void  rtl8139cp_verify_mac_reset(void)
{
//	unsigned int i=0;
	/* Reset */	 
	rtd_outb(ioaddr + CMD,CMD_RST|(1<<3));		
      rtd_outb(ioaddr + CMD,CMD_RST);		
	while ( rtd_inb(ioaddr + CMD) & CMD_RST);
  
  //dz mark  for(i=0;i<10;i++)		
	//dz mark    udelay(20000);
	
	rtd_outb(ioaddr + CMD,(1<<3));
	
  //dz mark  for(i=0;i<30;i++)	
 	//dz mark    udelay(20000);
	//dz mark	
}


static void  rtl6330cp_verify_mac_reset(void)
{
//	unsigned int i=0;
	/* Reset */	 

	

	#ifdef BYTE_ENDIAN_BUG
	rtd_outb(ioaddr + CMD -3 ,CMD_RST|(1<<3));		
      rtd_outb(ioaddr + CMD - 3,CMD_RST);	
	while ( rtd_inb(ioaddr + CMD - 3) & CMD_RST);
	rtd_outb(ioaddr + CMD - 3,(1<<3));

	#else
	rtd_outb(ioaddr + CMD,CMD_RST|(1<<3));	
	
       rtd_outb(ioaddr + CMD,CMD_RST);	
	  
	while ( rtd_inb(ioaddr + CMD) & CMD_RST);
	rtd_outb(ioaddr + CMD,(1<<3));
	#endif

}


 
static unsigned char enetaddr[6];

static void rtl8139cp_verify_SetEthAddr(void) 
{
	int i=0;
	UINT32 ID0_3=0,ID4_5=0;	
	 test_endian little;
	UINT32 addr = 0x18016000;
	for (i = 0; i < ETH_ALEN; i++)
		enetaddr[i] = (i<<4)| i;

	enetaddr[3] = 0x79;

	ID0_3 = enetaddr[3] | (enetaddr[2] << 8) | (enetaddr[1] << 16) | (enetaddr[0] << 24);	 
	ID4_5 = (enetaddr[5]<<16) | (enetaddr[4] << 24);   

	   
	rtd_outl(ioaddr + IDR0,ID0_3);
	rtd_outl(ioaddr + IDR4,ID4_5);

	rtd_outl(ioaddr + MAR0, 0xffffffff);
	rtd_outl(ioaddr + MAR4, 0xffffffff);

	
#ifdef BYTE_ENDIAN_BUG


#else

	for (i = 0; i < ETH_ALEN; i++)
	{
		printk("%x %x\n",enetaddr[i], rtd_inb(ioaddr+ IDR0 + i));
		if(enetaddr[i] != rtd_inb(ioaddr+ IDR0 + i)) {
	 		printk("Set Ethernet Address error.\n");
	 		break;
	 	}
	}
	
#endif
		
} 

static void rtl8139cp_verify_init_tx(void)
{
	int i=0;

	pTxBDPtr = (NIC_FD_T *) KSEG1ADDR(&Tx_Desc[0]);

	for(i=0;i<TX_QC_DESC_NUM;i++) {
#if LITTLEENDIA_ETH
		pTxBDPtr[i].StsLen = 0;
		pTxBDPtr[i].VLan = 0;
		pTxBDPtr[i].DataPtr = 0;
#else
		pTxBDPtr[i].StsLen = 0;
		pTxBDPtr[i].VLan = 0;
		pTxBDPtr[i].DataPtr = 0;
#endif
	}
#if LITTLEENDIA_ETH
	pTxBDPtr[TX_QC_DESC_NUM-1].StsLen = at_swap_32(at_swap_32(pTxBDPtr[TX_QC_DESC_NUM-1].StsLen)|EOR_BIT);
#else
	pTxBDPtr[TX_QC_DESC_NUM-1].StsLen |= (EOR_BIT);    
#endif        
	txBDtail = 0; 

flush_cache((unsigned long)Tx_Desc, sizeof(NIC_FD_T) * TX_QC_DESC_NUM);

}


static void rtl6330cp_verify_init_tx(void)
{
	int i=0;

	pTxBDPtr = (NIC_FD_T *) KSEG1ADDR(&Tx_Desc[0]);
	
	for(i=0;i<TX_QC_DESC_NUM;i++) {
#if LITTLEENDIA_ETH
		pTxBDPtr[i].StsLen = 0;
		pTxBDPtr[i].VLan = 0;
		pTxBDPtr[i].DataPtr = 0;
#else
		pTxBDPtr[i].StsLen = 0;
		pTxBDPtr[i].VLan = 0;
		pTxBDPtr[i].DataPtr = 0;
#endif
    }
 #if LITTLEENDIA_ETH
     pTxBDPtr[TX_QC_DESC_NUM-1].StsLen = at_swap_32(at_swap_32(pTxBDPtr[TX_QC_DESC_NUM-1].StsLen)|EOR_BIT);
#else
   pTxBDPtr[TX_QC_DESC_NUM-1].StsLen |= (EOR_BIT);    
#endif        
    txBDtail = 0; 

	flush_cache((unsigned long)Tx_Desc, sizeof(NIC_FD_T) * TX_QC_DESC_NUM);



}

static void rtl8139cp_verify_init_rx(void) 
{
	int i=0;

#ifdef two_byte_align_test
	unsigned char *rx_ptr = (&rx_ring[0] + 2);
#else
	unsigned char *rx_ptr = (&rx_ring[0]);
#endif

	pRxBDPtr = (NIC_FD_T *) KSEG1ADDR(&Rx_Desc[0]);

#if LITTLEENDIA_ETH	
	for(i=0;i<RX_QC_DESC_NUM;i++) {	   
		pRxBDPtr[i].StsLen  = at_swap_32((OWN_BIT | RX_DESC_BUFFER_SIZE)); 
		pRxBDPtr[i].VLan    = 0;     
		pRxBDPtr[i].DataPtr = at_swap_32(PHYSADDR((UINT32) rx_ptr)); // KSEG1ADDR((UINT32) rx_ptr); 

		rx_ptr += RX_DESC_BUFFER_SIZE;     
	}

	pRxBDPtr[RX_QC_DESC_NUM-1].StsLen = at_swap_32(at_swap_32(pRxBDPtr[RX_QC_DESC_NUM-1].StsLen)|(EOR_BIT));

#else
	for(i=0;i<RX_QC_DESC_NUM;i++) {	   
		pRxBDPtr[i].StsLen  = (OWN_BIT | RX_DESC_BUFFER_SIZE); 
		pRxBDPtr[i].VLan    = 0;     
		pRxBDPtr[i].DataPtr = PHYSADDR((UINT32) rx_ptr); // KSEG1ADDR((UINT32) rx_ptr); 

		rx_ptr += RX_DESC_BUFFER_SIZE;     
	}

	pRxBDPtr[RX_QC_DESC_NUM-1].StsLen |= (EOR_BIT);
#endif    
	rxBDtail = 0;

	flush_cache((unsigned long)Rx_Desc, sizeof(NIC_FD_T) * RX_QC_DESC_NUM);

}


//wait phy link finish and speed is gaga
static void rtl6330cp_link_speed_status(void)
{
	int count = 0;
	rtd_outl(0xb801605c,0x841f0000);// change Page to 0
	ms_delay(0x10);
	

	for(count = 1000; count > 0 ; count--)
	{
		ms_delay(50);
		rtd_outl(0xb801605c,0x041a0000);
		while((rtd_inl(0xb801605c)&_BIT31)==0);
		if ( (rtd_inl(0xb801605c) & 0x34) == 0x24)
			break;
	}

	printk("count=%d\n",count);
	if (count == 0)
	{
		printk("giga speed status timeout\n");
	}
	else
		printk("1G Link\n");


}




static void rtl6330cp_verify_init_rx(void) 
{
	int i=0;
	unsigned char *rx_ptr = &rx_ring[0];
	
	pRxBDPtr = (NIC_FD_T *) KSEG1ADDR(&Rx_Desc[0]);
	
#if LITTLEENDIA_ETH	
	for(i=0;i<RX_QC_DESC_NUM;i++) {	   
      pRxBDPtr[i].StsLen  = at_swap_32((OWN_BIT | RX_DESC_BUFFER_SIZE)); 
      pRxBDPtr[i].VLan    = 0;     
      pRxBDPtr[i].DataPtr = at_swap_32(PHYSADDR((UINT32) rx_ptr)); // KSEG1ADDR((UINT32) rx_ptr); 
     
      rx_ptr += RX_DESC_BUFFER_SIZE;     
    }
    
    pRxBDPtr[RX_QC_DESC_NUM-1].StsLen = at_swap_32(at_swap_32(pRxBDPtr[RX_QC_DESC_NUM-1].StsLen)|(EOR_BIT));

#else
	for(i=0;i<RX_QC_DESC_NUM;i++) {	   
      pRxBDPtr[i].StsLen  = (OWN_BIT | RX_DESC_BUFFER_SIZE); 
      pRxBDPtr[i].VLan    = 0;     
      pRxBDPtr[i].DataPtr = PHYSADDR((UINT32) rx_ptr); // KSEG1ADDR((UINT32) rx_ptr); 
     
      rx_ptr += RX_DESC_BUFFER_SIZE;     
    }
    
    pRxBDPtr[RX_QC_DESC_NUM-1].StsLen |= (EOR_BIT);
#endif    
    rxBDtail = 0;

	flush_cache((unsigned long)Rx_Desc, sizeof(NIC_FD_T) * RX_QC_DESC_NUM);

}


static void rtl8139cp_verify_hw_init(void) 
{
	UINT32 value = 0;

	#if 0
	UINT32 page;
	UINT16 mii_value=0;
	#endif
	
 //  if (loopback_mode != PHY_LOOP_BACK)
	//	rtd_outl(0xb8016860,0x00000408);      // turn-off PWRDN_PLL_L , debug_4byte_write 
	/* MAC Reset */	 
	rtl8139cp_verify_mac_reset();
	// Phy reset. 
	//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,MII_REG0_Reset);

	rtl8139cp_verify_SetEthAddr();

#ifdef BYTE_ENDIAN_BUG
		/* receive checksum */
	rtd_outb(ioaddr + CMD - 3,CMD_RxChkSum|(1<<3));
//	rtd_outl(0xb8016838,0x6); //chengying patch
#else
	/* receive checksum */
	rtd_outb(ioaddr + CMD,CMD_RxChkSum|(1<<3));	
#endif


	/* Interrupt Register, ISR, IMR */    
#ifdef BYTE_ENDIAN_BUG		
    rtd_outw(ioaddr + IMR+ 2,IMR_DISABLE_ALL_INTR);
    rtd_outw(ioaddr + ISR -2,ISR_CLEAR_ALL_INTR);
#else
    rtd_outw(ioaddr + IMR,IMR_DISABLE_ALL_INTR);
    rtd_outw(ioaddr + ISR,ISR_CLEAR_ALL_INTR);
#endif

	
    /* setup rx descriptor */	

    rtd_outl(ioaddr + RxFDP,PHYSADDR((UINT32) pRxBDPtr));
    rtd_outl(ioaddr + RxCDO,0);
    
    /* setup tx descriptor */
    /* Use Tx First Descriptor Pointer (FDP) for high priority queue. */
    rtd_outl(ioaddr + TxFDP1,PHYSADDR((UINT32) pTxBDPtr));
    rtd_outl(ioaddr + TxCDO1,0);
    
    /* RCR (Rx config register) , don't accept error packet */
    rtd_outl(ioaddr + RCR,RCR_ALL);

#ifdef BYTE_ENDIAN_BUG		
    // Rx_Pse_Des_Thres = RX_FC_THRESHOLD;
    rtd_outb(ioaddr + Rx_Pse_Des_Thres + 1,RX_FC_THRESHOLD);
    
    /* Rx descriptor Size */    
    rtd_outb(ioaddr + EthrntRxCPU_Des_Num + 3,0);


    rtd_outl(0xb8016a30,0x0f000800); // ETNRXCPU_Des_Num_reg,0x0f  & RX_FC_THRESHOLD  //chengying patch

	
		
    /* 32 descriptors */
    rtd_outb(ioaddr + RxRingSize - 1,RxRingSize_32);

#else
 // Rx_Pse_Des_Thres = RX_FC_THRESHOLD;
    rtd_outb(ioaddr + Rx_Pse_Des_Thres,RX_FC_THRESHOLD);
    
    /* Rx descriptor Size */    
    rtd_outb(ioaddr + EthrntRxCPU_Des_Num,0);
        
    /* 32 descriptors */
    rtd_outb(ioaddr + RxRingSize,RxRingSize_32);

#endif

      
    /* TCR: IFG, Mode*/

    if ((loopback_mode == PHY_LOOP_BACK)||(loopback_mode == NORMAL))
    	rtd_outl(ioaddr + TCR,TCR_IFG(TCR_IFG_B011) | TCR_LBK1_LBK0(TCR_LBK1_LBK0_NORMAL) );
    else
    {
    	printk("mac loopback...\n");
	rtd_outl(ioaddr + TCR,TCR_IFG(TCR_IFG_B011) | TCR_LBK1_LBK0(TCR_LBK1_LBK0_LOOPBACK) );
    }

#ifdef BYTE_ENDIAN_BUG	
	  /* Enable Tx/Rx Flow Control */    
    rtd_outb(ioaddr + MSR + 3, (MSR_TXFCE | MSR_RXFCE));
#else
    /* Enable Tx/Rx Flow Control */    
    rtd_outb(ioaddr + MSR, (MSR_TXFCE | MSR_RXFCE));
#endif

            
  value  = (ETHER_IO_CMD_RE|ETHER_IO_CMD_TE /*| ETHER_IO_CMD_TXFNH*/);
    // 2 pkts.
    value |= ETHER_IO_CMD_RxIntMitigation(0x1);
    // 128 byts
    value |= ETHER_IO_CMD_RXFTH1_0(0x3);
    // 1 x 82 us
    value |= ETHER_IO_CMD_RXPktTimer(0x1);
    
 //   value |=  ETHER_IO_CMD_MXRXDMA2_1_0(0x1);
    
    value |=  ETHER_IO_CMD_TxIntMitigation(0x2);
    value |=  ETHER_IO_CMD_TXTH1_0(0X02);
	
    rtd_outl(ioaddr + ETHER_IO_CMD, value);   

	//rtd_outl(0xb8016234,0x70140031);	// RX/TX enable

}

static void rtl6330cp_verify_phy_init(void)
{
	GETN_CRT();
	SET_FUSE_READY();
	PHY_STATUS();
//--	LINK_STATUS();

}



static void rtl6330cp_verify_hw_init(void) 
{
	UINT32 value = 0;

	#if 0
	UINT32 page;
	UINT16 mii_value=0;
	#endif
	printk("hw init...\n");

	/* MAC Reset */	 
	rtl6330cp_verify_mac_reset();
	// Phy reset. 
	//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,MII_REG0_Reset);

	rtl8139cp_verify_SetEthAddr();

	//disable dma anr rx,tx
	rtd_outl(ioaddr + ETHER_IO_CMD, 0x0);   

#ifdef BYTE_ENDIAN_BUG
		/* receive checksum */
	rtd_outb(ioaddr + CMD - 3,CMD_RxChkSum|(1<<3));
#else
	/* receive checksum */
	rtd_outb(ioaddr + CMD,CMD_RxChkSum|(1<<3));	
#endif


	/* Interrupt Register, ISR, IMR */    
#ifdef BYTE_ENDIAN_BUG		
    rtd_outw(ioaddr + IMR+ 2,IMR_DISABLE_ALL_INTR);
    rtd_outw(ioaddr + ISR -2,ISR_CLEAR_ALL_INTR);
#else
    rtd_outw(ioaddr + IMR,IMR_DISABLE_ALL_INTR);
    rtd_outw(ioaddr + ISR,ISR_CLEAR_ALL_INTR);
#endif

    /* setup rx descriptor */	

    rtd_outl(ioaddr + RxFDP,PHYSADDR((UINT32) pRxBDPtr));
    rtd_outl(ioaddr + RxCDO,0);
    
    /* setup tx descriptor */
    /* Use Tx First Descriptor Pointer (FDP) for high priority queue. */
    rtd_outl(ioaddr + TxFDP1,PHYSADDR((UINT32) pTxBDPtr));
    rtd_outl(ioaddr + TxCDO1,0);
    
    /* RCR (Rx config register) , don't accept error packet */
    rtd_outl(ioaddr + RCR,  RCR_ALL);

#ifdef BYTE_ENDIAN_BUG		
    // Rx_Pse_Des_Thres = RX_FC_THRESHOLD;
    rtd_outb(ioaddr + Rx_Pse_Des_Thres + 1,RX_FC_THRESHOLD);
    
    /* Rx descriptor Size */    
    rtd_outb(ioaddr + EthrntRxCPU_Des_Num + 3,0);

    /* 32 descriptors */
    rtd_outb(ioaddr + RxRingSize - 1,RxRingSize_32);

#else
 // Rx_Pse_Des_Thres = RX_FC_THRESHOLD;
    rtd_outb(ioaddr + Rx_Pse_Des_Thres,RX_FC_THRESHOLD);
    
    /* Rx descriptor Size */    
    rtd_outb(ioaddr + EthrntRxCPU_Des_Num,0);
    /* 32 descriptors */
    rtd_outb(ioaddr + RxRingSize,RxRingSize_32);
	
#endif
    /* TCR: IFG, Mode */
    rtd_outl(ioaddr + TCR,TCR_IFG(TCR_IFG_B011) | TCR_LBK1_LBK0(TCR_LBK1_LBK0_NORMAL) );

#ifdef BYTE_ENDIAN_BUG	
	  /* Enable Tx/Rx Flow Control */    
    rtd_outb(ioaddr + MSR + 3, (MSR_TXFCE | MSR_RXFCE));
#else
    /* Enable Tx/Rx Flow Control */    
    rtd_outb(ioaddr + MSR, (MSR_TXFCE | MSR_RXFCE));
#endif
	
    // Phy reset.    
 //--    rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,MII_REG0_Reset);




    /* FPGA : Manual setup. 10M capability only*/ 
    #if 0
    //rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);
    //rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex);

    rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG4,0x0c61); //10M capability only
   
	
    #endif
        
    //rtl8139cp_verify_phy_auto_negotiation(RTD2885_LAN_PHY_ID);
	#if 0 //1.  RG18X<6:4>=010, RG17X<2:0>=000  fail  
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;
	/* change to page 3 */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x03);
	
	/* page3 REG 8 RG17X[2:0] 000 */
	/*    8:<15- 8>:   RG17X[7:0] 8:< 7- 0>:   RG16X[7:0] */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8);
	mii_value &= ~(0x7<<8);	
	//mii_value |= (1<<8);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG8,mii_value);
	/* page3 REG 9:< 7- 0> RG18X[6:4] 010 */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9);
	mii_value &= ~(0x7<<4);			
	mii_value |= (0x2<<4);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,mii_value);

    printk("1 page3 REG 8 RG17X[2-0] <15- 8> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8));
    printk("1 page3 REG 9 RG18X[6-4] <7 - 0> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9));
	
	/* change to original page  */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,page);
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;

	//2.  RG18X<6:4>=011 RG17X<2:0>=001 fail unknown condition 
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;
	/* change to page 3 */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x03);
	
	/* page3 REG 8 RG17X[2:0] 001 */
	/*    8:<15- 8>:   RG17X[7:0] 8:< 7- 0>:   RG16X[7:0] */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8);
	mii_value &= ~(0x7<<8);	
	mii_value |= (1<<8);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG8,mii_value);
	/* page3 REG 9:< 7- 0> RG18X[6:4] 011 */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9);
	mii_value &= ~(0x7<<4);			
	mii_value |= (0x3<<4);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,mii_value);

    printk("2 page3 REG 8 RG17X[2-0] <15- 8> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8));
    printk("2 page3 REG 9 RG18X[6-4] <7 - 0> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9));
	
	/* change to original page  */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,page);
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;	
	#endif
	
	#if 0
	//3  RG18X<6:4>=011 RG17X<2:0>=100 
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;
	/* change to page 3 */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x03);
	
	/* page3 REG 8 RG17X[2:0] 001 */
	/*    8:<15- 8>:   RG17X[7:0] 8:< 7- 0>:   RG16X[7:0] */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8);
	mii_value &= ~(0x7<<8);	
	mii_value |= (4<<8);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG8,mii_value);
	/* page3 REG 9:< 7- 0> RG18X[6:4] 011 */
	mii_value = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9);
	mii_value &= ~(0x7<<4);			
	mii_value |= (0x3<<4);
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,mii_value);

    printk("3 page3 REG 8 RG17X[2-0] <15- 8> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG8));
    printk("3 page3 REG 9 RG18X[6-4] <7 - 0> mii_value=%x\n",rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG9));
	
	/* change to original page  */
	rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,page);
	page = rtl8139cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG31)&0x3;
	#endif
    /* Ethernet IO CMD */
  
    value  = (GETHER_IO_CMD_SHORTDES_FORMAT | GETHER_IO_CMD_EARLY_TX | GETHER_IO_CMD_RE|GETHER_IO_CMD_TE /*| GETHER_IO_CMD_TXFN1*/ );
    // 2 pkts.
    value |= GETHER_IO_CMD_RxIntMitigation(0x1);
    // 128 byts
 //   value |= GETHER_IO_CMD_RXFTH1_0(0x3);
    // 1 x 82 us
    value |= GETHER_IO_CMD_RXPktTimer(0x1);    
    value |=  GETHER_IO_CMD_TxIntMitigation(0x2);
    value |=  GETHER_IO_CMD_TXTH1_0(0X02); //TX 512B


   // printk("ETHER_IO_CMD : value = 0x%x\n",value );

	
    rtd_outl(ioaddr + ETHER_IO_CMD, value);   

	//rtd_outl(0xb8016234,0x70140031);	// RX/TX enable


}



void rtl8139cp_verify_reset(void)
{
	rtd_outl(ioaddr + ETHER_IO_CMD, 0x10100);  // disable ETHER_IO_CMD_RE , ETHER_IO_CMD_TE 
	rtl8139cp_verify_init_tx();
	rtl8139cp_verify_init_rx();
	rtl8139cp_verify_hw_init();
	
	// rtl8139cp_verify_dump_all_reg();
}


void rtl6330cp_verify_reset(void)
{

	rtl6330cp_verify_init_tx();
	rtl6330cp_verify_init_rx();
	rtl6330cp_verify_hw_init();	
}





static int rtl6330cp_verify_transmit(volatile void *packet, int length)
{
	int i=0;
	unsigned int len = length;
	UINT32 tx_status=0;
	
	/*
	UINT16 status=0;
	
	status = rtd_inw(ioaddr+ISR);
	// Clear Interrupt status bits.	
 	rtd_outw(ioaddr+ISR,status & 0x07C0);
	*/


	memcpy((char *)tx_buffer, (char *)packet, (int)length);

#if LITTLEENDIA_ETH
  
	
	pTxBDPtr[txBDtail].DataPtr = at_swap_32(PHYSADDR((UINT32) tx_buffer)); // KSEG1ADDR((UINT32) tx_buffer); 

	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) & (~TX_DESC_DATA_LEN_MASK)); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) | (len));

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen)|(OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC));
#else	 	 
	pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32) tx_buffer); // KSEG1ADDR((UINT32) tx_buffer); 
	//printf("pTxBDPtr[%d].DataPtr =%x\n",txBDtail, pTxBDPtr[txBDtail].DataPtr);
	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen &= (~TX_DESC_DATA_LEN_MASK); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen |= (len);

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen |= (OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC);
    //printf("pTxBDPtr[%d].StsLen =%x\n", txBDtail,pTxBDPtr[txBDtail].StsLen);
    //printf("pTxBDPtr[%d].StsLen add=%x\n",txBDtail, &pTxBDPtr[txBDtail].StsLen);   	
#endif    


    //flush_dcache();
    sys_dcache_flush_and_invalidate_all();
    // High Priority DMA-Ethernet Transmit enable.
    rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | GETHER_IO_CMD_TXFN1);

    //udelay(100000); 
    udelay(1000); 
    
	// 50 ms
    i = 5000;
#if LITTLEENDIA_ETH
    while((at_swap_32(pTxBDPtr[txBDtail].StsLen) & (OWN_BIT)) && (i--) )
#else
    while((pTxBDPtr[txBDtail].StsLen & (OWN_BIT)) && (i--) )
#endif
	{
		udelay(10);
	};
    
    // debug
    if (i==-1) {
    	printk("Tx TimeOut : Status = 0x%x\n",pTxBDPtr[txBDtail].StsLen);
    	return 0;
    }

#if LITTLEENDIA_ETH    
     tx_status = at_swap_32(pTxBDPtr[txBDtail].StsLen);

#else
     tx_status = pTxBDPtr[txBDtail].StsLen;

#endif    



#if 1  //spec not define
    if (tx_status & TX_DESC_STATS_UNF)
        printk("Tx FIFO Underrun : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_TES)
        printk("Tx Error Summary : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_LNKF)
        printk("Link Failure : Status = 0x%x\n",tx_status);

        if (tx_status & TX_DESC_STATS_EXC)
        printk("Excessive Collision , aborted (Over 16 collisions): Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_OWC)
        printk("Out of Window Collision : Status = 0x%x\n",tx_status);

    //if (TX_DESC_STATS_CC(tx_status))
	//printk("Tx Collision Counter = 0x%x\n",TX_DESC_STATS_CC(tx_status));
#endif		
    
	// printk("packet = 0x%x, len = 0x%x\n",tx_buffer,len);
	
	
#if defined(_RTL8139CP_VERIFY_DEBUG_TX) 	
    printk("S ");   	
    printk("TXOKCNT = 0x%x\n",rtd_inw(TXOKCNT+ioaddr));
    printk("TRSR = 0x%x\n",rtd_inl(TRSR+ioaddr));
#endif

    /* advance one */
    txBDtail++;
    txBDtail %= TX_QC_DESC_NUM;

		
    return 1;
}





static int rtl8139cp_verify_transmit(volatile void *packet, int length)
{
	int i=0;
	unsigned int len = length;
	UINT32 tx_status=0;
	
	/*
	UINT16 status=0;
	
	status = rtd_inw(ioaddr+ISR);
	// Clear Interrupt status bits.	
 	rtd_outw(ioaddr+ISR,status & 0x07C0);
	*/


	memcpy((char *)tx_buffer, (char *)packet, (int)length);

#if LITTLEENDIA_ETH
  
	
	pTxBDPtr[txBDtail].DataPtr = at_swap_32(PHYSADDR((UINT32) tx_buffer)); // KSEG1ADDR((UINT32) tx_buffer); 

	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) & (~TX_DESC_DATA_LEN_MASK)); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) | (len));

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen)|(OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC));
#else	 	 
	pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32) tx_buffer); // KSEG1ADDR((UINT32) tx_buffer); 
	//printf("pTxBDPtr[%d].DataPtr =%x\n",txBDtail, pTxBDPtr[txBDtail].DataPtr);
	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen &= (~TX_DESC_DATA_LEN_MASK); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen |= (len);

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen |= (OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC);
    //printf("pTxBDPtr[%d].StsLen =%x\n", txBDtail,pTxBDPtr[txBDtail].StsLen);
    //printf("pTxBDPtr[%d].StsLen add=%x\n",txBDtail, &pTxBDPtr[txBDtail].StsLen);   	
#endif    


    //flush_dcache();
    sys_dcache_flush_and_invalidate_all();
    // High Priority DMA-Ethernet Transmit enable.
    rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

    ms_delay(100);    
	// 200 ms
    i = 20000;
#if LITTLEENDIA_ETH
    while((at_swap_32(pTxBDPtr[txBDtail].StsLen) & (OWN_BIT)) && (i--) )
#else
    while((pTxBDPtr[txBDtail].StsLen & (OWN_BIT)) && (i--) )
#endif
	{
		udelay(10);
	}

    // debug
    if (i== -1) {
    	printk("Tx TimeOut : Status = 0x%x\n",pTxBDPtr[txBDtail].StsLen);
    	return 0;
    }

 
#if LITTLEENDIA_ETH    
     tx_status = at_swap_32(pTxBDPtr[txBDtail].StsLen);

#else
     tx_status = pTxBDPtr[txBDtail].StsLen;

#endif    




    if (tx_status & TX_DESC_STATS_UNF)
        printk("Tx FIFO Underrun : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_TES)
        printk("Tx Error Summary : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_LNKF)
        printk("Link Failure : Status = 0x%x\n",tx_status);

        if (tx_status & TX_DESC_STATS_EXC)
        printk("Excessive Collision , aborted (Over 16 collisions): Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_OWC)
        printk("Out of Window Collision : Status = 0x%x\n",tx_status);

    //if (TX_DESC_STATS_CC(tx_status))
	//printk("Tx Collision Counter = 0x%x\n",TX_DESC_STATS_CC(tx_status));
		
    
	// printk("packet = 0x%x, len = 0x%x\n",tx_buffer,len);
	
	
#if defined(_RTL8139CP_VERIFY_DEBUG_TX) 	
    printk("S ");   	
    printk("TXOKCNT = 0x%x\n",rtd_inw(TXOKCNT+ioaddr));
    printk("TRSR = 0x%x\n",rtd_inl(TRSR+ioaddr));
#endif

    /* advance one */
    txBDtail++;
    txBDtail %= TX_QC_DESC_NUM;

		
    return 1;
}


static int rtl6330cp_verify_poll(_rx_handle_func_t handle_func)
{
	UINT16 status=0;
	UINT8  *rxdata=NULL;
	UINT32 blen=0;	
	UINT16	pkt_count=0;
	
     int i=0;
    // 50 ms
    i = 5000;

	/* Interrupt Register, ISR, IMR */    

	printk("rx poll...\n");

#ifdef BYTE_ENDIAN_BUG
	while(!(rtd_inw(ioaddr+ISR - 2) & (ISR_ROK)) && (i--))
#else
	while(!(rtd_inw(ioaddr+ISR) & (ISR_ROK)) && (i--))
#endif
	{
		udelay(10);
	}


    // debug

	
    if (i==-1) {
#ifdef BYTE_ENDIAN_BUG
	printk("Rx TimeOut : Status = 0x%x\n",rtd_inw(ioaddr+ISR - 2));
#else
        printk("Rx TimeOut : Status = 0x%x\n",rtd_inw(ioaddr+ISR));
#endif
        return 0;
    }
    else
		printk("rx i = %d\n", i);

#ifdef BYTE_ENDIAN_BUG
	status = rtd_inw(ioaddr+ISR - 2);
#else
	status = rtd_inw(ioaddr+ISR);
#endif
	   
	if (!status || (status == 0xFFFF))
	{
		printk("status = %x\n",status);
		return 0;
	}
   
    if (status & 0x20)  	   	
    	printk("error:RX desc. unavailable ,status = 0x%x \n",status); 
    	
    if (status & 0x04)  	
    	printk("error:RX runt ,status = 0x%x \n",status); 	
    	
    if (status & 0x10) {
    	printk("error:RX ovf ,status = 0x%x , reset\n",status);
    	rtl6330cp_verify_reset();
    }	
 
    // Clear Interrupt status bits.
 #ifdef BYTE_ENDIAN_BUG
	rtd_outw(ioaddr+ISR - 2,status);
 #else
 	rtd_outw(ioaddr+ISR,status);
#endif
	

    //flush_dcache();
    sys_dcache_flush_and_invalidate_all();
	  
	  
	  //dump_cache_setting();

#if LITTLEENDIA_ETH
    while((at_swap_32(pRxBDPtr[rxBDtail].StsLen) & OWN_BIT) ==0)
 #else
   while(((pRxBDPtr[rxBDtail].StsLen & OWN_BIT) ==0))    
#endif
    {
       //flush_dcache();
       sys_dcache_flush_and_invalidate_all();


#if LITTLEENDIA_ETH
       rxdata = (char*)at_swap_32(pRxBDPtr[rxBDtail].DataPtr);          /*cyhuang modified 1019 */
#else
       rxdata = (char*)pRxBDPtr[rxBDtail].DataPtr;          /*cyhuang modified 1019 */
#endif
              
       rxdata = (char*) KSEG1ADDR((UINT32) rxdata);
   
#if LITTLEENDIA_ETH
       blen = at_swap_32(pRxBDPtr[rxBDtail].StsLen);
#else
       blen = (pRxBDPtr[rxBDtail].StsLen);
#endif

       // blen = (blen & 0xfff) - 4;
       blen = RX_DESC_DATA_LEN(blen)-4;
       
       // Debug
       /*
       if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_FAE)  
       	  printk("Rx Frame Alignment Error: Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);      
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_RES)
       	  printk("Rx Error Summary : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_IPF)	  
          printk("Rx IP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_UDPF)
 	      printk("Rx UDP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_TCPF)	  
 	      printk("Rx TCP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       */

	   if (handle_func) {
			if (handle_func(rxdata,blen))
				pkt_count++;
	   }
	   else		
  	   		pkt_count++;
 #if LITTLEENDIA_ETH
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) & (~RX_DESC_DATA_LEN_MASK));// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) | (RX_DESC_BUFFER_SIZE));
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen)|(OWN_BIT));
#else 	   		  	   	
       pRxBDPtr[rxBDtail].StsLen &= (~RX_DESC_DATA_LEN_MASK);// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen |= (RX_DESC_BUFFER_SIZE);
       pRxBDPtr[rxBDtail].StsLen |= (OWN_BIT);
#endif           

#ifdef BYTE_ENDIAN_BUG	
	rtd_outb(ioaddr + EthrntRxCPU_Des_Num + 3,rxBDtail);
#else
       rtd_outb(ioaddr + EthrntRxCPU_Des_Num,rxBDtail);
#endif

       rxBDtail++;
       rxBDtail %= RX_QC_DESC_NUM;       
    } // End of while

    return pkt_count;
}





static int rtl8139cp_verify_poll(_rx_handle_func_t handle_func)
{
	UINT16 status=0;
	UINT8  *rxdata=NULL;
	UINT32 blen=0;	
	UINT16	pkt_count=0;
	
     int i=0;
    // 150 ms

    i = 15000;

#ifdef BYTE_ENDIAN_BUG
	while(!(rtd_inw(ioaddr+ISR - 2) & (ISR_ROK)) && (i--))
#else
	while(!(rtd_inw(ioaddr+ISR) & (ISR_ROK)) && (i--))
#endif
	{
		udelay(10);
	}


    // debug

    if (i==-1) {

#ifdef BYTE_ENDIAN_BUG
	printk("Rx TimeOut : Status = 0x%x\n",rtd_inw(ioaddr+ISR - 2));
#else
        printk("Rx TimeOut : Status = 0x%x\n",rtd_inw(ioaddr+ISR));
#endif

        return 0;
    }


#ifdef BYTE_ENDIAN_BUG
	status = rtd_inw(ioaddr+ISR - 2);
#else
	status = rtd_inw(ioaddr+ISR);
#endif

	   
	if (!status || (status == 0xFFFF))
		return 0;
   
    if (status & 0x20)  	   	
    	printk("error:RX desc. unavailable ,status = 0x%x \n",status); 
    	
    if (status & 0x04)  	
    	printk("error:RX runt ,status = 0x%x \n",status); 	
    	
    if (status & 0x10) {
    	printk("error:RX ovf ,status = 0x%x , reset\n",status);
    	rtl8139cp_verify_reset();
    }	

     
 
    // Clear Interrupt status bits.	
 	rtd_outw(ioaddr+ISR,status);

	
 
    //flush_dcache();
    sys_dcache_flush_and_invalidate_all();
	  
	  
	  //dump_cache_setting();

#if LITTLEENDIA_ETH
    while((at_swap_32(pRxBDPtr[rxBDtail].StsLen) & OWN_BIT) ==0)
 #else
   while(((pRxBDPtr[rxBDtail].StsLen & OWN_BIT) ==0))    
#endif
    {
       //flush_dcache();
       sys_dcache_flush_and_invalidate_all();


#if LITTLEENDIA_ETH
       rxdata = (char*)at_swap_32(pRxBDPtr[rxBDtail].DataPtr);          /*cyhuang modified 1019 */
#else
       rxdata = (char*)pRxBDPtr[rxBDtail].DataPtr;          /*cyhuang modified 1019 */
#endif
              
       rxdata = (char*) KSEG1ADDR((UINT32) rxdata);
   
#if LITTLEENDIA_ETH
       blen = at_swap_32(pRxBDPtr[rxBDtail].StsLen);
#else
       blen = (pRxBDPtr[rxBDtail].StsLen);
#endif
       // blen = (blen & 0xfff) - 4;
       blen = RX_DESC_DATA_LEN(blen)-4;
       
       // Debug
       /*
       if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_FAE)  
       	  printk("Rx Frame Alignment Error: Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);      
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_RES)
       	  printk("Rx Error Summary : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_IPF)	  
          printk("Rx IP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_UDPF)
 	      printk("Rx UDP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_TCPF)	  
 	      printk("Rx TCP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       */

	   if (handle_func) {
			if (handle_func(rxdata,blen))
				pkt_count++;
	   }
	   else		
  	   		pkt_count++;
 #if LITTLEENDIA_ETH
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) & (~RX_DESC_DATA_LEN_MASK));// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) | (RX_DESC_BUFFER_SIZE));
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen)|(OWN_BIT));
#else 	   		  	   	
       pRxBDPtr[rxBDtail].StsLen &= (~RX_DESC_DATA_LEN_MASK);// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen |= (RX_DESC_BUFFER_SIZE);
       pRxBDPtr[rxBDtail].StsLen |= (OWN_BIT);
#endif           
       rtd_outb(ioaddr + EthrntRxCPU_Des_Num,rxBDtail);
   
       rxBDtail++;
       rxBDtail %= RX_QC_DESC_NUM;       
    } // End of while
    return pkt_count;
}


//Gphy
static int rtl6330cp_verify_pkt_handle(volatile void *inpkt, int len)
{
	if (!memcmp((void *) inpkt,txbuffer,LAN_QC_VERIFY_LEN)) {
		printk("PASS\n");
		QC_Result =  VERIFY_PASS;	
	}	
	else {
		printk("FAIL : inpkt = 0x%x , txbuffer = 0x%x\n", (UINT32) inpkt , (UINT32) txbuffer);
		QC_Result =  VERIFY_FAIL;
	}
	
	return 0;	
				
}



static int rtl8139cp_verify_pkt_handle(volatile void *inpkt, int len)
{
	if (!memcmp((void *) inpkt,txbuffer,LAN_QC_VERIFY_LEN)) {
		printk("PASS\n");
		QC_Result =  VERIFY_PASS;	
	}	
	else {
		printk("FAIL : inpkt = 0x%x , txbuffer = 0x%x\n", (UINT32) inpkt , (UINT32) txbuffer);
		QC_Result =  VERIFY_FAIL;
	}
	
	return 0;	
				
}




#define ARMV7_DCACHE_INVAL_ALL      1
#define ARMV7_DCACHE_CLEAN_INVAL_ALL    2
#define ARMV7_DCACHE_INVAL_RANGE    3
#define ARMV7_DCACHE_CLEAN_INVAL_RANGE  4


#define CP15DSB asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))




static u32 get_ccsidr1(void)
{
    u32 ccsidr;

    /* Read current CP15 Cache Size ID Register */
    asm volatile ("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
    return ccsidr;
}


static void v7_dcache_clean_inval_range1(u32 start,
                    u32 stop, u32 line_len)
{
    u32 mva;

    /* Align start to cache line boundary */
    start &= ~(line_len - 1);
    for (mva = start; mva < stop; mva = mva + line_len) {
        /* DCCIMVAC - Clean & Invalidate data cache by MVA to PoC */
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" : : "r" (mva));
    }
}



#define CCSIDR_LINE_SIZE_MASK               0x7
#define CCSIDR_LINE_SIZE_OFFSET             0


static void v7_dcache_maint_range1(u32 start, u32 stop, u32 range_op)
{
    u32 line_len, ccsidr;

    ccsidr = get_ccsidr1();
    line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>
            CCSIDR_LINE_SIZE_OFFSET) + 2;
    /* Converting from words to bytes */
    line_len += 2;
    /* converting from log2(linelen) to linelen */
    line_len = 1 << line_len;

    switch (range_op) {
    case ARMV7_DCACHE_CLEAN_INVAL_RANGE:
        v7_dcache_clean_inval_range1(start, stop, line_len);
        break;
/*		
    case ARMV7_DCACHE_INVAL_RANGE:
        v7_dcache_inval_range(start, stop, line_len);
        break;
 */
    }

    /* DSB to make sure the operation is complete */
    CP15DSB;
}


void flush_dcache_range1(unsigned long start, unsigned long stop)
{
    v7_dcache_maint_range1(start, stop, ARMV7_DCACHE_CLEAN_INVAL_RANGE);

    //v7_outer_cache_flush_range(start, stop);
}


void  flush_cache1(unsigned long start, unsigned long size)
{
    flush_dcache_range1(start, start + size);
}


void flush_cache3(unsigned long start, unsigned long size)
{
    u32 line_len = 32, ccsidr;
    u32 mva;
    u32 stop = start + size;

#if 0
    /* Read current CP15 Cache Size ID Register */
    asm volatile ("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
	
    line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>CCSIDR_LINE_SIZE_OFFSET) + 2;


//    printk("line_len=%d\n",line_len);
	
    /* Converting from words to bytes */
    line_len += 2;
    /* converting from log2(linelen) to linelen */
    line_len = 1 << line_len;
#else

    
#endif
    

      
     
    /* Align start to cache line boundary */
    start &= ~(line_len - 1);

 //   printk("start=%d line_len=%d\n", start, line_len);
	
    for (mva = start; mva < stop; mva = mva + line_len) {
        /* DCCIMVAC - Clean & Invalidate data cache by MVA to PoC */
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" : : "r" (mva));
    }
}



void flush_cache2(unsigned long start, unsigned long size)
{
    u32 line_len, ccsidr;
    u32 mva;
    u32 stop = start + size;


    /* Read current CP15 Cache Size ID Register */
    asm volatile ("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
	
    line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>CCSIDR_LINE_SIZE_OFFSET) + 2;


//    printk("line_len=%d\n",line_len);
	
    /* Converting from words to bytes */
    line_len += 2;
    /* converting from log2(linelen) to linelen */
    line_len = 1 << line_len;

    /* Align start to cache line boundary */
    start &= ~(line_len - 1);

 //   printk("start=%d line_len=%d\n", start, line_len);
	
    for (mva = start; mva < stop; mva = mva + line_len) {
        /* DCCIMVAC - Clean & Invalidate data cache by MVA to PoC */
        asm volatile ("mcr p15, 0, %0, c7, c14, 1" : : "r" (mva));
    }
}


void EEE_10M_setting(void)
{
	rtd_outl(0xb801605c,0x841f0a43);// change Page to a43
    ms_delay(0x100);
    rtd_outl(0xb801605c,0x84190073);//eee10_en  enable phymode eee
    ms_delay(0x10);

    rtd_outl(0xb801605c,0x04190000);
    ms_delay(0x10);
    printk("eee mode=%x\n", rtd_inl(0xb801605c));

}

void EEE_setting(void)
{

	rtd_outl(0xb801605c,0x841f0a43);// change Page to a43
	ms_delay(0x100);
	rtd_outl(0xb801605c,0x84190063);// enable phymode eee 
	ms_delay(0x10);

	rtd_outl(0xb801605c,0x04190000);
	ms_delay(0x10);
	printk("eee mode=%x\n", rtd_inl(0xb801605c));

	
	
	
	//(write a43, reg25, '0063'),polling a60, reg16, bit [7:0] = 0x44->0x48 來確定 DUT 有進 1000M eee state

}

void EEE_status(void)
{
	rtd_outl(0xb801605c,0x841f0a60);// change Page to a60
	ms_delay(0x100);
	rtd_outl(0xb801605c,0x04100000);
	ms_delay(0x10); 
	
	

}


void EEEP_setting(void)
{
#if 1
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(1000);
	rtd_outl(0xb801605c,0x84090000);// disable giga capability
	ms_delay(1000);

	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(1000);
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability 
	ms_delay(1000);


	
	
#else
	//10M normal mode
	rtd_outl(0xb801605c,0x84000100); ///--- set gphy 10M mode  && normal && full-duplex

       ms_delay(5000);
#endif
	//10M eeep
	rtd_outl(0xb801605c,0x841f0a43);// change Page to a43
	ms_delay(100);
	rtd_outl(0xb801605c,0x84190067);// phy mode = 10M eeep
	ms_delay(10);

	//10M eeep
//	rtd_outl(0xb801605c,0x841f0a44);// change Page to a44
//	ms_delay(100);
//	rtd_outl(0xb801605c,0x84150002);// Mac mode = 10M eeep
//	ms_delay(10);


	rtd_outl(0xb801605c,0x841f0a43);// change Page to a43
	ms_delay(100);
	rtd_outl(0xb801605c,0x84182199);// bit0 (en_10m_plloff) = 1
	ms_delay(10);

	//rtd_outl(0xb801605c,0x841f0a44);// change Page to a44
	//ScalerTimer_DelayXms(100);
	//rtd_outl(0xb801605c,0x841104bc);// bit7 (en_10m_bgoff) = 1
	//ScalerTimer_DelayXms(10);	

	rtd_outl(0xb801605c,0x84009200);// page0 reg0 = 0x9200 (reautonegotiation) (don't plug cable)
	ms_delay(5000);



}

void EEEP_init(void)
{
	GETN_CRT();
	SET_FUSE_READY();
	green_function_close();
	PHY_STATUS();
	LINK_STATUS();
	EEEP_setting();

	
}

void pkt_gen_tx_enable(void)
{
	rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
	ms_delay(100);


	rtd_outl(0xb801605c,0x84130040);
	ms_delay(0x10);

	//rtd_outl(0xb801605c,0x8414ffff); // send 16 packet
	//ms_delay(0x10);

	rtd_outl(0xb801605c, 0x84105a21);   //set pgtx_enable
	ms_delay(0x10);





}


void pkt_gen_rx_enable(void)
{

	rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
	ms_delay(100);
	rtd_outl(0xb801605c, 0x84105a02);   //set pgrx_enable
	ms_delay(0x10);

}


void pkt_gen_tx_rx_enable(void)
{
	rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
	ms_delay(100);


	rtd_outl(0xb801605c,0x84130040);  //one packet 64byte with crc
	ms_delay(0x10);

	//0x(2000000000) 7735 9600
//	rtd_outl(0xb801605c,0x84149600); // send 2000000000
//	ms_delay(0x10);
//	rtd_outl(0xb801605c,0x84157735);
//	ms_delay(0x10);
rtd_outl(0xb801605c,0x8414ffff); // send 16 packet
	ms_delay(0x10);

	rtd_outl(0xb801605c, 0x84105a02);   //set rx_enable
	ms_delay(0x100);

	rtd_outl(0xb801605c, 0x84105a23);   //set pgtx_enable pgrx_enable
	ms_delay(0x10);


}

void wait_phy_read_finish(void)
{
	while((rtd_inl(0xb801605c)&_BIT31)==0)
	{

	}
}



int EEEP_test(void)
{
	  volatile unsigned char *pkt=NULL;
	      unsigned int i = 0 ; 
		  unsigned int j = 0;
        int count = 0;
    UINT32 pkt_size=64;

	
     //test must plug out ethernet cable
     EEEP_init();
	
   
//     pkt_gen_rx_enable();

   
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;



#if 0 //phy only mode
rtd_outl(0xB8000910,0x00000020);	//ETN
rtd_outl(0xB801605c,0x02000000);	//mdio phy only mode
//rtd_outl(0xB8016240,0x00011717);	//debug port SEL
rtd_outl(0xB8016240,0x00010a0a);	//debug port SEL

rtd_outl(0xb801605c,0x861f0d00);// change Page to d00
ms_delay(100);
rtd_outl(0xb801605c,0x86110504);// set debug mode
ms_delay(10);
rtd_outl(0xb801605c,0x06110000);
ms_delay(10);
rtd_inl(0xb801605c);


//pin share
rtd_outl(0xB8000854,0xe0000000);	//D[0]
rtd_outl(0xB8000830,0xe0e0e0e0);	//D[33:36]
rtd_outl(0xB8000834,0xe0e0e0e0);	//D[29:33]
rtd_outl(0xB8000838,0xe0e0e0e0);	//D[25:28]
rtd_outl(0xB800083c,0xe0e0e0e0);	//D[21:24]
rtd_outl(0xB8000840,0xe0e0e0e0);	//D[17:20]
rtd_outl(0xB8000844,0xe0e0e0e0);	//D[13:16]
rtd_outl(0xB8000848,0xe0e0e0e0);	//D[9:12]
rtd_outl(0xB800084c,0xe0e0e0e0);	//D[5:8]
rtd_outl(0xB8000850,0xe0e0e0e0);	//D[1:4]
#endif



	ms_delay(3000);
	rtd_outl(0xb801605c,0x841f0a43);// change Page to a43
	ms_delay(100);
	rtd_outl(0xb801605c,0x041a0000);
	ms_delay(100);
	printk("@@@@@@@@@ %x\n",rtd_inl(0xb801605c));



	 rtd_outl(0xb801605c,0x841f0a40);
       ms_delay(100);
	rtd_outl(0xb801605c,0x04050000);
	ms_delay(100);
	printk("@@@@@@@@@reg5= %x\n",rtd_inl(0xb801605c));
	


       rtd_outl(0xb801605c,0x841f0a41);
       ms_delay(100);
	rtd_outl(0xb801605c,0x04090000);
	ms_delay(100);
	printk("@@@@@@@@@reg9= %x\n",rtd_inl(0xb801605c));


       rtd_outl(0xb801605c,0x841f0a40);
       ms_delay(100);
	rtd_outl(0xb801605c,0x04040000);
	ms_delay(100);
	printk("@@@@@@@@@reg4= %x\n",rtd_inl(0xb801605c));




	rtd_outl(0xb801605c,0x841f0a60);// change Page to a60
	ms_delay(100);


      //plug in ethernet cable 
	while(1)
	{
		rtd_outl(0xb801605c,0x04100000);// read  bit [7:0] = 27 (EEEP_BGOFF) 
		ms_delay(10);

		//enable pll clock become 0x26
		if ( ((rtd_inl(0xb801605c) & 0xff) == 0x26) || ((rtd_inl(0xb801605c) & 0xff) == 0x25))
			++count;
			
		printk("status = %x\n",rtd_inl(0xb801605c));
		ms_delay(10);

		if (count == 20)
			break;
	}





	 //100M
    rtl6330cp_verify_reset();

	
//    udelay(10);

    //rtd_outl(0xb80160b0,0xe0000000);

	ms_delay(200);
	
	//LINK_SPEED();


/*
	  QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0x5c,LAN_QC_VERIFY_LEN);
    udelay(10);
ms_delay(100);

    rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  


	ms_delay(200);
	    rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
ms_delay(200);
		    rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
ms_delay(200);
    printk("transmit....\n");            


     while(1)
     {

     }
*/
    /*
	
    udelay(100);  
    rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 

	*/

	
	
#if 0
	rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	ms_delay(100);
	while(1)
	{
		rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
		wait_phy_read_finish();
		printk("reg_16=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
		wait_phy_read_finish();
		printk("reg_17=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("reg_18=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);

	}
#endif	


	while(1)
	{

		//flush_cache1((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
	//		printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

	 //              if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
	//			   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
	       } 

	}


}

void green_function_close(void)
{

	
	//write page 0, reg27, 0x8011
	//write page 0, reg28, 0x9537


	 rtd_outl(0xb801605c, 0x841f0000);       // change Page to 0
	 ms_delay(0x200);
	 
	 rtd_outl(0xb801605c, 0x841b8011); 
	 ms_delay(0x200);


        rtd_outl(0xb801605c, 0x041c0000);
	 ms_delay(0x200);
	 printk("[data] %x\n", rtd_inl(0xb801605c));

	 
	 rtd_outl(0xb801605c, 0x841c9537); 
	 ms_delay(0x200);

	printk("reauto negotiation\n");
	 rtd_outl(0xb801605c,0x84009200);// page0 reg0 = 0x9200 (reautonegotiation) (don't plug cable)

	 ms_delay(1000);

}



#if 0  // for magellan

void adjust_CM_SwingAmp(void)
{
	int count = 0;
	
	#if adjust_CM_Voltage
	//adjust common mode voltage
	printk("adjust common mode voltage\n");	
	rtd_outl(0xb801605c,0x841f0bc0);// change Page to bc0
	ms_delay(100);
	rtd_outl(0xb801605c,0x84170001);// bit[1:0]:common mode voltage => 0x2->0x1
	ms_delay(10);

	#endif

	#if adjust_Swing_Amp
	//adjust swing amp from 1200mV-->1000mV
	printk("adjust swing amp...\n");

	rtd_outl(0xb801605c,0x841f0000); //change page to 0
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b8078);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841ca704);
	ms_delay(100);

	rtd_outl(0xb801605c,0x841f0bcc);// change Page to bcc
	ms_delay(100);
	rtd_outl(0xb801605c,0x8410a40a);// bit[2:0]:amp_dn => 000:100% 001:90% 010:80%
	ms_delay(10);

//	rtd_outl(0xb801605c,0x04100000);
//	ms_delay(100);
//	printk("%x\n", rtd_inl(0xb801605c));

	rtd_outl(0xb801605c,0x84120055);// bit[1:0]:up  => 000:100% 001:102.5% 010:105%
	ms_delay(10);



	for(count = 0 ; count < 20 ; ++count)
	{
		rtd_outl(0xb801605c,0x841f0bcc);// change Page to bcc
		ms_delay(100);
		
		rtd_outl(0xb801605c,0x04100000);
		ms_delay(500);
		printk("%x\n", rtd_inl(0xb801605c));
	}


	#endif

}



#endif



#if ONLY_TX_VERIFY


static unsigned int x = 123456789;

void srand2(unsigned int seed)
{
   x = seed;
}

unsigned int rand2(void)
{
   static unsigned int y = 362436;
   static unsigned int z = 521288629;
   static unsigned int c = 7654321;

   unsigned long long t, a= 698769069;

   x = 69069 * x + 12345;
   y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5);
   t = a * z + c; c = (t >> 32); z = t;

   return x + y + z;
}


int get_random_count()
{

	int range = 1514;
	srand2(get_timer(0));
	return 64 + (rand2() % (range - 64 /*1450*/));

}


int performance_test_TX_10M()
{
	volatile unsigned char *pkt=NULL;
	      unsigned int i = 0 ; 
		  unsigned int count = 0;
		  unsigned char testvar = 1;
		  unsigned int tx_status;
    //printk(" LAN QC test start...\n ");  

	int psize = 0;
    UINT32 pkt_size=64;
    unsigned char data = 0; 
	

     rtl6330cp_verify_phy_init();


#if auto_n_way  //avoid link partner to enter half duplex mode not full duplex mode 
 	rtd_outl(0xb801605c,0x841f0a42);
	 ms_delay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000); //clear 1000T half & full cap.
	ms_delay(10);
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability
	ms_delay(10);
#else
   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);

   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
#endif	
   ms_delay(5000);
	 
    rtl6330cp_verify_reset();
    udelay(10);




    for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring[i] = data;
	    ++data;
    }


     data = 1;

      for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring1[i] = data;
	    ++data;
    }

    data = 2;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring2[i] = data;
	    ++data;
    }
	

     data = 3;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring3[i] = data;
	    ++data;
    }

   data = 4;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring4[i] = data;
	    ++data;
    }

	    data = 5;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring5[i] = data;
	    ++data;
    }


	    data = 6;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring6[i] = data;
	    ++data;
    }


	    data = 7;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring7[i] = data;
	    ++data;
    }

	    data = 8;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring8[i] = data;
	    ++data;
    }


	    data = 9;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring9[i] = data;
	    ++data;
    }


	    data = 10;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring10[i] = data;
	    ++data;
    }


	    data = 11;


     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring11[i] = data;
	    ++data;
    }


	    data = 12;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring12[i] = data;
	    ++data;
    }


	    data = 13;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring13[i] = data;
	    ++data;
    }


	    data = 14;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring14[i] = data;
	    ++data;
    }

	    data = 15;

     for(i = 0 ; i < 2*RX_DESC_BUFFER_SIZE ; ++i)
    {
	    tx_ring15[i] = data;
	    ++data;
    }
	
	

    LINK_SPEED();

  
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(1000);
//for(i = 0 ; i < 50 ; ++i)
//		printk("%d\n",get_random_count());




	printk("10M\n");

	while(1)
	{
		
	//	flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
	//	while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	//      	{      		
			#if 1
			//printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

//	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
//				   	printk(" RX descriptor CRC status error\n");
//		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size

		     pkt_size = get_random_count() & 0x00000fff;

		//	printk("packet size=%d\n",pkt_size);

			if ((pkt_size & 0x7) == 0)
	            		pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring);
			else if ((pkt_size & 0x7) == 1)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring1);
			else if ((pkt_size & 0x7) == 2)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring2);
			else if ((pkt_size & 0x7) == 3)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring3);
			else if ((pkt_size & 0x7) == 4)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring4);
			else if ((pkt_size & 0x7) == 5)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring5);
			else if ((pkt_size & 0x7) == 6)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring6);
			else if ((pkt_size & 0x7) == 7)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring7);

			/*
			else if ((pkt_size & 0xf) == 8)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring8);
			else if ((pkt_size & 0xf) == 9)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring9);
			else if ((pkt_size & 0xf) == 10)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring10);
			else if ((pkt_size & 0xf) == 11)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring11);
			else if ((pkt_size & 0xf) == 12)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring12);
			else if ((pkt_size & 0xf) == 13)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring13);
			else if ((pkt_size & 0xf) == 14)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring14);
			else if ((pkt_size & 0xf) == 15)
				pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)&tx_ring15);
	*/		
			
		     // pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32)tx_ring);
	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0800000+pkt_size);  //Own=1 EOR=1 
					
	 //--               flush_cache2((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
					
			  //txBDtail=0;
			   while((pTxBDPtr[TX_QC_DESC_NUM -1].StsLen & 0x80000000) ==0x0) 
					break;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0800000+pkt_size);  //own=1 EOR=0 

			 while((pTxBDPtr[txBDtail - 1].StsLen & 0x80000000) ==0x0) 
					break;
	//--                flush_cache2((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));	
	
			  //++txBDtail;
	            }                       

		//      pTxBDPtr[txBDtail].StsLen |= (OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC);
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 


	           rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

		      //i = 5000;

//		     while((pTxBDPtr[txBDtail].StsLen & (OWN_BIT)) && (i--) )
//		    {
//				udelay(10);
//		     };

/*
		         if (i==-1) {
    				printk("Tx TimeOut : Status = 0x%x\n",pTxBDPtr[txBDtail].StsLen);
    				return 0;
    		     }
*/
			//#define __arch_putl(v,a)        (*(volatile unsigned int *)(a) = (v))

			//(*(volatile unsigned int *)(0x18016234) = (0x50122131));
			//	(*(volatile unsigned int *)(0x18016234) = (0x501f21f1));



/*
    			 tx_status = pTxBDPtr[txBDtail].StsLen;


			    if (tx_status & TX_DESC_STATS_UNF)
			        printk("Tx FIFO Underrun : Status = 0x%x\n",tx_status);

			    if (tx_status & TX_DESC_STATS_TES)
			        printk("Tx Error Summary : Status = 0x%x\n",tx_status);

			    if (tx_status & TX_DESC_STATS_LNKF)
			        printk("Link Failure : Status = 0x%x\n",tx_status);

			        if (tx_status & TX_DESC_STATS_EXC)
			        printk("Excessive Collision , aborted (Over 16 collisions): Status = 0x%x\n",tx_status);

			    if (tx_status & TX_DESC_STATS_OWC)
			        printk("Out of Window Collision : Status = 0x%x\n",tx_status);
*/

			  if(txBDtail == (TX_QC_DESC_NUM -1))
	                {
				txBDtail=0;
			  }
			  else
			  {
				++txBDtail;
			  }

			++count;
			  if (0x1B == rtd_inl(0x18062300)) // ESC key
				goto msg;


			#endif
	       } 


msg:
	printk("packet count=%d\n",count );


}




#endif



void getn_debug_pin()
{

///============== getn debug sel ========================///
//rtd_outl(0xb8016240,0x00012020);
rtd_outl(0xb8016240,0x00011717);
ms_delay(100);

///============== crt ip debug sel ======================///
rtd_outl(0xb8000c78,0xffff0000);
ms_delay(100);
rtd_outl(0xb8000944,0x0000004f);
ms_delay(100);
///=========== chip debug pinmux setting ==========================///

rtd_outl(0xb8000800,0xb85c0000);  //0
ms_delay(100);

rtd_outl(0xb8000804,0xb8000000);  // 1
ms_delay(100);

rtd_outl(0xb8000814,0x00002e00); // 2
ms_delay(100);

rtd_outl(0xb8000818,0xb85c2e00); // 3
ms_delay(100);

rtd_outl(0xb8000828,0x00002e00); // 4
ms_delay(100);

rtd_outl(0xb8000830,0xb85c2e00); //5
ms_delay(100);

rtd_outl(0xb8000834,0xb8002e00); //6
ms_delay(100);



rtd_outl(0xb8000838,0xb85c2e00); //7  txe10
ms_delay(100);



rtd_outl(0xb800083c,0xb85c2e00); //8
ms_delay(100);

rtd_outl(0xb8000840,0xb8000000); //9
ms_delay(100);



rtd_outl(0xb8000844,0x00002e00); //10
ms_delay(100);



}



int performance_test_10M(void)
{
	volatile unsigned char *pkt=NULL;
	      unsigned int i = 0 ; 
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;
	
    rtl6330cp_verify_phy_init();


    QC_AutoK_shift();
    QC_Delay_RH_100m_1000M();
    QC_RC_R_Amplitude_10();

#if 0 //auto_n_way   // avoid link partner only to enter half duplex not full duplex
	rtd_outl(0xb801605c,0x841f0a42);
	 ms_delay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000); //clear 1000T half & full cap.
	ms_delay(10);
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability
	ms_delay(10);
#else
   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);
   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
#endif	

    rtl6330cp_verify_reset();
    udelay(10);


//   printk(" 100M: ");    

    LINK_SPEED();




    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(1000);

	pkt_gen_rx_enable();
//       getn_debug_pin();
#if 1
	printk("10M\n");

	printk("start test3....\n");
	printk("reg=%x\n",rtd_inl(0xb8016058)); //bit22 check mac enter full duplex mode
	
	while(1)
	{

		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
			//udelay(100);
			//printk("%d %x\n", rtd_inl(0x18016010), rtd_inl(0xb801603c));
			//printk("%d %d %x\n", (rtd_inl(0x18016010) & 0xffff0000) >> 16, rtd_inl(0xb8016010) & 0x0000ffff,rtd_inl(0xb801603c));
//	      	        printk("888aaaaaaaaaaaaaaaaaaaaaaa\n");
	//		printk("rx=%d tx=%d\n",rxBDtail, txBDtail);
//	      	        printk("%x %x\n",pRxBDPtr[rxBDtail].StsLen,pRxBDPtr[rxBDtail + 1].StsLen);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
				   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

//	          	memcpy(rx_ring1,  pTxBDPtr[txBDtail].DataPtr,pkt_size);

		

	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
//				 while((pTxBDPtr[TX_QC_DESC_NUM -1].StsLen & 0x80000000) ==0x0) 
//					break;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
//			flush_dcache_all();
//			ms_delay(10);
			  ++txBDtail;

//			    while((pTxBDPtr[txBDtail - 1].StsLen & 0x80000000) ==0x0) 
//					break;
	            }                       
	 
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		//     udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	         //   rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 

			(*(volatile unsigned int *)(0x18016234) = (((*(volatile unsigned int *)(0x18016234)) | 0x1)));

		 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

		    if (0x1B == rtd_inl(0x18062300)) // ESC key
				goto msg;


		     #endif
	       } 

	}


#endif


msg:
	rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
	wait_phy_read_finish();
	printk("reg_16=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
	wait_phy_read_finish();
	printk("reg_17=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
	wait_phy_read_finish();
	printk("reg_18=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);


   return QC_Result;


}


void disable_100_giga_ability(void)
{
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000);// disable giga capability  (a40 normal see phy data sheet)
	ms_delay(10);
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability 
	ms_delay(10);//10M normal mode
	//rtd_outl(0xb801605c,0x84000100); ///--- set gphy 10M mode  && normal && full-duplex
	//ScalerTimer_DelayXms(10);



}


void disable_giga_ability(void)
{
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42

	ms_delay(100);

	rtd_outl(0xb801605c,0x84090000);// disable giga capability

	ms_delay(10);

	rtd_outl(0xb801605c,0x04090000);
	

	printk("close giga %x....\n",rtd_inl(0xb801605c));

}



int EEE_test_10M(void)
{

	volatile unsigned char *pkt=NULL;
	unsigned int i = 0 ;
	int count = 0;	  
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;

	
   // rtl6330cp_verify_phy_init();


	GETN_CRT();
	SET_FUSE_READY();
	green_function_close();
	disable_100_giga_ability();
	PHY_STATUS();
	LINK_STATUS();
   
   

   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
   rtl6330cp_verify_reset();
  //  udelay(10);



     ms_delay(1000);
//   printk(" 100M: ");    

    LINK_SPEED();
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(5000);
       

	printk("10M EEE\n");

	printk("start....\n");

#if 1
	EEE_10M_setting();

	while(1)
	{
		EEE_status();
		printk("eee status=%x\n",rtd_inl(0xb801605c));

		//if ( (rtd_inl(0xb801605c) & 0xff) == 0x34)
			++count;

		if (count == 10)
			break;
	}
#endif


       QC_RC_R_Amplitude_10();


	printk("10M Tx/Rx start \n");

	printk("start....\n");



#if 1
	
	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
			
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

//	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
//				   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
	       } 

	}

#endif






	//pkt_gen_rx_enable();

	#if 0
	printk("start tx rx enable.......\n");
	
 	pkt_gen_tx_rx_enable();

	while(1)
	{
		rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04160000);       // read txcnt_15_0
		wait_phy_read_finish();
		printk("txcnt_15_0 =%x\n", rtd_inl(0xb801605c));
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04170000);       // read txcnt_31_16
		wait_phy_read_finish();
		printk("txcnt_31_16=%x\n", rtd_inl(0xb801605c));
		ms_delay(100);

		rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
		wait_phy_read_finish();
		printk(" rxcnt_15_0=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
		wait_phy_read_finish();
		printk("rxcnt_31_16=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("rxerr_15_0=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);

		
	/*	
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("reg_18=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
       */
	}
#endif	


   return QC_Result;

}






int EEE_test_100M(void)
{

	volatile unsigned char *pkt=NULL;
	unsigned int i = 0 ;
	int count = 0;	  
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;

	
   // rtl6330cp_verify_phy_init();


	GETN_CRT();
	SET_FUSE_READY();
	green_function_close();
	disable_giga_ability();
	PHY_STATUS();
	LINK_STATUS();
   
   

   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
   rtl6330cp_verify_reset();
  //  udelay(10);



     ms_delay(1000);
//   printk(" 100M: ");    

    LINK_SPEED();
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(5000);
       

	printk("100M EEE\n");

	printk("start1....\n");

#if 1
	EEE_setting();

	while(1)
	{
		EEE_status();
		printk("eee status=%x\n",rtd_inl(0xb801605c)); // 0x44--> 0x48 //enter 1000M eee mode  0x31->0x34 enter 100M eee mode

		if ( (rtd_inl(0xb801605c) & 0xff) == 0x34)
			++count;

		if (count == 10)
			break;
	}
#endif


     QC_RC_R_Amplitude_100_1000();

	printk("100M\n");

	printk("start1....\n");





#if 1
	
	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
			
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

//	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
//				   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
	       } 

	}

#endif






	//pkt_gen_rx_enable();

	#if 0
	printk("start tx rx enable.......\n");
	
 	pkt_gen_tx_rx_enable();

	while(1)
	{
		rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04160000);       // read txcnt_15_0
		wait_phy_read_finish();
		printk("txcnt_15_0 =%x\n", rtd_inl(0xb801605c));
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04170000);       // read txcnt_31_16
		wait_phy_read_finish();
		printk("txcnt_31_16=%x\n", rtd_inl(0xb801605c));
		ms_delay(100);

		rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
		ms_delay(100);
		rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
		wait_phy_read_finish();
		printk(" rxcnt_15_0=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
		wait_phy_read_finish();
		printk("rxcnt_31_16=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("rxerr_15_0=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);

		
	/*	
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("reg_18=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
       */
	}
#endif	


   return QC_Result;

}


int EEE_test_1000M(void)
{

	volatile unsigned char *pkt=NULL;
	unsigned int i = 0 ; 
       int count = 0;	 
	UINT32 pkt_size=64;

	
	GETN_CRT();
	SET_FUSE_READY();
	green_function_close();
	PHY_STATUS();
	LINK_STATUS();
	
	
   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);

   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	

    rtl6330cp_verify_reset();

    LINK_SPEED();
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(5000);
       

	EEE_setting();

	while(1)
	{
		EEE_status();
		printk("eee status=%x\n",rtd_inl(0xb801605c)); // 0x44--> 0x48 //enter 1000M eee mode  0x31->0x34 enter 100M eee mode

		if ( (rtd_inl(0xb801605c) & 0xff) == 0x48)
			++count;

		if (count == 10)
			break;
	}


	 QC_RC_R_Amplitude_100_1000();

	printk("1000M EEE\n");
	printk("start....\n");
	

#if 1
	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
			//printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

//	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
//				   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
	       } 

	}

#endif


   return QC_Result;

}




#if 0
void wake_on_lan(void)
{
	int i=0;
	
	   
//	rtd_outl(0xb8016000,0x11223344);
//	rtd_outl(0xb8016004,0x55660000);

     rtl6330cp_verify_phy_init();


   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);

   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	
   ms_delay(5000);
	 
    rtl6330cp_verify_reset();
    udelay(10);



//   printk(" 100M: ");    

    LINK_SPEED();
    QC_Result = VERIFY_FAIL;
 //   pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(1000);

	rtd_outl(0xb8016000,0x11223344);
	rtd_outl(0xb8016004,0x55660000);
	rtd_outl(0xb8016268,0x1);
	

	
}
#endif



void wake_on_lan_aldps_reset_pmeb()
{
	int i=0;
	UINT32 temp=0;


     rtl6330cp_verify_phy_init();


   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);

   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	
   ms_delay(5000);
	 
    rtl6330cp_verify_reset();
    udelay(10);

    QC_Result = VERIFY_FAIL;
 //   pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);



#if auto_n_way  //avoid link partner to enter half duplex mode not full duplex mode 

#if n_way_100M
// 100M
	rtd_outl(0xb801605c,0x841f0a42);
	 ms_delay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000); //clear 1000T half & full cap.
	ms_delay(10);

#if n_way_10M
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability
	ms_delay(10);
	rtd_outl(0xb801605c,0x84001040); //set Nway enable
	ms_delay(10);
	rtd_outl(0xb801605c,0x84001240); //set Nway restart
	ms_delay(100);

#endif
	
		
#endif

	

#else

   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    printk(" 100M:\n "); 
#endif	

	
    ms_delay(1000);

	LINK_SPEED();

	//mac magic packet 
	/*rtd_outl(0xb8016000,0x11223344);
	rtd_outl(0xb8016004,0x55660000);
	rtd_outl(0xb8016268,0x1);*/
	//11 22 33 44 55 66 00 00 00 00 00 00 08 06 00 01 08 00 06 04 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
       //uni cast packet
	
	//ff ff ff ff ff ff 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66
	//uni phy address for magic packet
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8c);//page0x0d8c
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x2211);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x4433);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,0x6655);	

	//multicast "0"th 
	//pattern "0" : 01 02 3C 00 00 00 ....
	//01 02 3C 00 00 00 00 00 00 00 00 08 06 00 01 08 00 06 04 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8c);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG19,0x0000);//第 0 組	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG22,0x0100);

	//wake up frame packet (smartbits send) for wake up frame(106 byte)
	//FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6 C7 31 BE 3C C9 ED 1C 09 C5 4F 1E 64 FA 2C CA 33 FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6 C7 31 BE 3C C9 ED FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6
	//wake up frame 0 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d80);//page 0xd80
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 1 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d81);//page 0xd81
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 2 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d82);//page 0xd82
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 3 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d83);//page 0xd83
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 4 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d84);//page 0xd84
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 5 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d85);//page 0xd85
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 6 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d86);//page 0xd86
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 7 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d87);//page 0xd87
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);

	//wake up frame CRC
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d88);//page 0xd88
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x1f6a);//frame 0
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x1f6a);//frame 1
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,0x1f6a);//frame 2
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG19,0x1f6a);//frame 3
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x1f6a);//frame 4
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x1f6a);//frame 5
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG22,0x1f6a);//frame 6
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG23,0x1f6a);//frame 7	


	//enter LDPS mode  A43 , reg24 , bit2
	rtd_outl(0xb801605c ,0x841f0a43);
	ms_delay(0x10);
	rtd_outl(0xb801605c, 0x8418218c);
	ms_delay(0x10);

	
   	printk("LINK start .....\n");
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0);//page0

	while(!(rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG1)&_BIT2))
	{
		udelay(100);
	}
   	printk("LINK OK .....\n");
	
	LINK_SPEED();
	LINK_SPEED();
	
	for (i=0;i<14;i++){

		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8a);//page0d8a
		//PME will be asserted due to ...
		if (i==0){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x2000);//link change
			printk("link change test .....\n");
		}
		else if (i==1){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x1000);//magic packet
			printk("magic packet test .....\n");
		}
		else if (i==2){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0800);//normal packet	
			printk("normal packet test .....\n");
		}
		else if (i==3){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0400);//uni-cast packet
			printk("uni-cast packet test .....\n");
		}
		else if (i==4){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0200);//multi-cast packet
			printk("multi-cast packet test .....\n");
		}
		else if (i==5){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0100);//broadcast packet
			printk("broadcast packet test .....\n");
		}
		else if (i==6){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0080);//wake up frame 7 
			printk("wake up frame 7 test .....\n");
		}
		else if (i==7){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0040);//wake up frame 6
			printk("wake up frame 6 test .....\n");
		}
		else if (i==8){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0020);//wake up frame 5
			printk("wake up frame 5 test .....\n");
		}
		else if (i==9){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0010);//wake up frame 4
			printk("wake up frame 4 test .....\n");
		}
		else if (i==10){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0008);//wake up frame 3
			printk("wake up frame 3 test .....\n");
		}
		else if (i==11){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0004);//wake up frame 2
			printk("wake up frame 2 test .....\n");
		}
		else if (i==12){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0002);//wake up frame 1
			printk("wake up frame 1 test .....\n");
		}
		else if (i==13){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0001);//wake up frame 0
			printk("wake up frame 0 test .....\n");
		}
		
		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x1fff);//reset wol
		udelay(100);
		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x9fff);//max packet length
		

		while(1){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0da0);//page 0da0

			temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);
		
			if (temp&_BIT1){
				printk("Link Change.....\n");
				//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,_BIT1);
				break;
			}
				
			if (temp&_BIT2){
				printk("Received Magic Packet .....\n");
				
				//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,_BIT2);
				break;
			}

			if ((temp&_BIT0) == 0){
				printk("Received wake up frame or uni/multi cast or normal Packet %d\n",i);
				break;
			}

		//	if (i == 3)
		//		return;
			
			if (i==2)
				break;
			
		}

		printk("temp1=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16));


		printk("plug out cable to enter aldps mode\n");
		
		while(1)
		{
			//LDPS state A43 reg26,bit14
			rtd_outl(0xb801605c,0x841f0a43);
			ms_delay(0x10);
			rtd_outl(0xb801605c,0x041a0000);
			ms_delay(0x10);

			printk("@@@@@@ %x\n",rtd_inl(0xb801605c));
			if ((rtd_inl(0xb801605c) & 0x4000))
			{
				printk("reg power off enter LDPS \n");
				rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8a);
				rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x1fff);//reset wol
				udelay(100);
				rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x9fff);//max packet length

				rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0da0);//page 0da0
				temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);
		
				if ((temp&_BIT0))
				{
					printk("WOL reset ok...\n");
					break;
				}
				
			}
			else
				printk("reg power on leave LDPS\n");

			ms_delay(1000);
		}
		
	} 



}

void wake_on_lan()
{
	int i=0;
	UINT32 temp=0;


     rtl6330cp_verify_phy_init();


   //rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);

   //rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	
   ms_delay(5000);
	 
    rtl6330cp_verify_reset();
    udelay(10);

    QC_Result = VERIFY_FAIL;
 //   pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);



#if auto_n_way  //avoid link partner to enter half duplex mode not full duplex mode 

#if 1 //n_way_100M
// 100M
	rtd_outl(0xb801605c,0x841f0a42);
	 ms_delay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000); //clear 1000T half & full cap.
	ms_delay(10);

#if 1//n_way_10M
	rtd_outl(0xb801605c,0x84040061);// disable 100M capability
	ms_delay(10);
	rtd_outl(0xb801605c,0x84001040); //set Nway enable
	ms_delay(10);
	rtd_outl(0xb801605c,0x84001240); //set Nway restart
	ms_delay(100);

#endif
	
		
#endif

	

#else

   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    printk(" 100M:\n "); 
#endif	

	
    ms_delay(1000);

	LINK_SPEED();

	//mac magic packet 
	/*rtd_outl(0xb8016000,0x11223344);
	rtd_outl(0xb8016004,0x55660000);
	rtd_outl(0xb8016268,0x1);*/
	//11 22 33 44 55 66 00 00 00 00 00 00 08 06 00 01 08 00 06 04 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
       //uni cast packet
	
	//ff ff ff ff ff ff 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66 11 22 33 44 55 66
	//uni phy address for magic packet
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8c);//page0x0d8c
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x2211);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x4433);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,0x6655);	

	//multicast "0"th 
	//pattern "0" : 01 02 3C 00 00 00 ....
	//01 02 3C 00 00 00 00 00 00 00 00 08 06 00 01 08 00 06 04 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8c);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG19,0x0000);//第 0 組	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG22,0x0100);

	//wake up frame packet (smartbits send) for wake up frame(106 byte)
	//FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6 C7 31 BE 3C C9 ED 1C 09 C5 4F 1E 64 FA 2C CA 33 FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6 C7 31 BE 3C C9 ED FF FF FF FF FF FF 49 44 A0 77 ED 26 F3 99 1E F9 5F 12 13 7B 28 F6 19 D0 40 7B 14 D6
	//wake up frame 0 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d80);//page 0xd80
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 1 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d81);//page 0xd81
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 2 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d82);//page 0xd82
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 3 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d83);//page 0xd83
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 4 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d84);//page 0xd84
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 5 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d85);//page 0xd85
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 6 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d86);//page 0xd86
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);
	//wake up frame 7 mask
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d87);//page 0xd87
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x03ff);

	//wake up frame CRC
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d88);//page 0xd88
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x1f6a);//frame 0
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x1f6a);//frame 1
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,0x1f6a);//frame 2
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG19,0x1f6a);//frame 3
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x1f6a);//frame 4
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x1f6a);//frame 5
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG22,0x1f6a);//frame 6
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG23,0x1f6a);//frame 7	



	
   	printk("LINK start .....\n");
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0);//page0

	while(!(rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG1)&_BIT2))
	{
		udelay(100);
	}
   	printk("LINK OK .....\n");
	
	LINK_SPEED();
	LINK_SPEED();
	
	for (i=0;i<14;i++){

		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0d8a);//page0d8a
		//PME will be asserted due to ...
		if (i==0){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x2000);//link change
			printk("link change test .....\n");
		}
		else if (i==1){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x1000);//magic packet
			printk("magic packet test .....\n");
		}
		else if (i==2){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0800);//normal packet	
			printk("normal packet test .....\n");
		}
		else if (i==3){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0400);//uni-cast packet
			printk("uni-cast packet test .....\n");
		}
		else if (i==4){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0200);//multi-cast packet
			printk("multi-cast packet test .....\n");
		}
		else if (i==5){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0100);//broadcast packet
			printk("broadcast packet test .....\n");
		}
		else if (i==6){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0080);//wake up frame 7 
			printk("wake up frame 7 test .....\n");
		}
		else if (i==7){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0040);//wake up frame 6
			printk("wake up frame 6 test .....\n");
		}
		else if (i==8){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0020);//wake up frame 5
			printk("wake up frame 5 test .....\n");
		}
		else if (i==9){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0010);//wake up frame 4
			printk("wake up frame 4 test .....\n");
		}
		else if (i==10){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0008);//wake up frame 3
			printk("wake up frame 3 test .....\n");
		}
		else if (i==11){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0004);//wake up frame 2
			printk("wake up frame 2 test .....\n");
		}
		else if (i==12){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0002);//wake up frame 1
			printk("wake up frame 1 test .....\n");
		}
		else if (i==13){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0001);//wake up frame 0
			printk("wake up frame 0 test .....\n");
		}
		
		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x1fff);//reset wol
		udelay(100);
		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x9fff);//max packet length
		

		while(1){
			rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0da0);//page 0da0

			temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);
		
			if (temp&_BIT1){
				printk("Link Change.....\n");
				//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,_BIT1);
				break;
			}
				
			if (temp&_BIT2){
				printk("Received Magic Packet .....\n");
				
				//rtl8139cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG18,_BIT2);
				break;
			}

			if ((temp&_BIT0) == 0){
				printk("Received wake up frame or uni/multi cast or normal Packet %d\n",i);
				break;
			}

		//	if (i == 3)
		//		return;
			
			if (i==2)
				break;
			
		}

		
		rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0000);//clr 

		printk("temp1=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16));
		
	} 

}



int two_byte_align_100M_test(void)
{

	volatile unsigned char *pkt=NULL;
	      unsigned int i = 0 ; 
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;
   // UINT16 status = 0;
  //  UINT8 *ptx_buffer;
 //   UINT32 tx_count=0xff000000;
	

   rtl8139cp_verify_reset();
	
    udelay(10);	

    if (loopback_mode == PHY_LOOP_BACK)
    {
	
    	rtl8139cp_verify_phy_set_lbk(RTD2885_LAN_PHY_ID,PHY_LBK_Enable);	  
    	rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    	rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    }
    else if (loopback_mode == NORMAL)
    {
    	rtl8139cp_verify_phy_set_lbk(RTD2885_LAN_PHY_ID,PHY_LBK_Disable);	  
    	rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    	rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    }
    printk(" 100M: ");    
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;

#if 0//for single time test
    memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
	
    udelay(10);
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    
    udelay(100);

	printk("ddr address 0: %x\n",pRxBDPtr[0].DataPtr);
	printk("ddr address 1: %x\n",pRxBDPtr[1].DataPtr);		
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
    
    if(QC_Result == VERIFY_FAIL)
    {

	    printk(" 100M_retry: ");    
	    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	    udelay(100);  
	    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
	    if(QC_Result == VERIFY_FAIL){
	        return VERIFY_FAIL;  
	    }
    }

    return QC_Result;

#else//for long time test
	printk("100M\n");

	printk("ddr address 0: %x\n",pRxBDPtr[0].DataPtr);
	printk("ddr address 1: %x\n",pRxBDPtr[1].DataPtr);	
	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			#if 1
			//printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

//	               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
//				   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
	       } 
	}
#endif

	

}



#if 1
void QC_RC_R_Amplitude_100_1000()
{
//A 路   amplitude=8
//B 路   amplitude=b
//C 路   amplitude=a
//D 路   amplitude=7


	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bca);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x8cc9);
	
//set R value
//rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
//ms_delay(100);
//rtd_outl(0xb801605c,0x8410cccc);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0
}

#else

void QC_RC_R_Amplitude_100_1000()
{

#if 0
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
	ms_delay(10);
	rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0bcd);  //adjust RC (for rising and falling time)
	ms_delay(100);
	rtd_outl(0xb801605c,0x84174444);
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x8415fffd);
	ms_delay(10);

#endif

//A 路   amplitude=8
//B 路   amplitude=b
//C 路   amplitude=a
//D 路   amplitude=7


	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x84158cc9);
	ms_delay(10);


	rtd_outl(0xb801605c,0x04150000);
	ms_delay(100);
	printk("amplitude=%x\n",rtd_inl(0xb801605c));
//set R value
//rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
//ms_delay(100);
//rtd_outl(0xb801605c,0x8410cccc);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0
}
#endif


#if 1
void QC_RC_R_Amplitude_100_QFP()
{
	 // amplitude adjust
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bca);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x8cc9);
	
	//set R value
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bce);// change Page to bce
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0xcccc);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0

}

#else
void QC_RC_R_Amplitude_100_QFP()
{

#if 0
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
	ms_delay(10);
	rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0bcd);  //adjust RC (for rising and falling time)
	ms_delay(100);
	rtd_outl(0xb801605c,0x84174444);
	ms_delay(10);
#endif

	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x84158cc9);
	ms_delay(10);

	//set R value
	rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
	ms_delay(100);
	rtd_outl(0xb801605c,0x8410cccc);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0
}

#endif
#if 0
void QC_AutoK_shift()
{
	rtd_outl(0xb801605c,0x841f0a43);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b81de);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841cfc00); //  #  [15:8] tapbin tx #  [7:0] tapbin rx          -4
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a43);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b81e0);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841cfc00);  //  #  [15:8] rlen  #  [7:0] len        -3
	ms_delay(10);

	
	rtd_outl(0xb801605c,0x841f0a43);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b81e2);
	ms_delay(100);
	rtd_outl(0xb801605c,0x841c0000);  //   #  [15:8] rlen_100 ( 100M 的 rlen沒調整)
	ms_delay(10);

     

//tapbin      rlen
//ff -1       ff 0
//fe -2       fe -1
//fd -3       fd -2
//fc -4       fc -3

//tapbin is R (return loss)
//bce reg 16  (C --> 8) 12 - 4

//RC (IOL)
//bcd reg 23  (7 -->4 ) 7 -  3


}
#else
void QC_AutoK_shift()
{

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81de);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfc00);  //  #  [15:8] tapbin tx #  [7:0] tapbin rx          -4

	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81e0);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfc00); //  #  [15:8] rlen  #  [7:0] len        -3
	

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81e2);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);  //   #  [15:8] rlen_100 ( 100M 的 rlen沒調整)

//tapbin      rlen
//ff -1       ff 0
//fe -2       fe -1
//fd -3       fd -2
//fc -4       fc -3

//tapbin is R (return loss)
//bce reg 16  (C --> 8) 12 - 4

//RC (IOL)
//bcd reg 23  (7 -->4 ) 7 -  3


}

#endif


void QC_Delay_RH_100m_1000M()
{

	unsigned int temp;
	printk("delay_rh...\n");
	
//green disable	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8011);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x1737);

	
	//abiq 4444 (default = 5555, 1000M link abiq = 4444 , test mode 4 abiq = 7575)
//rtd_outl(0xb801605c,0x841f0bcc);	
//ms_delay(100);
//rtd_outl(0xb801605c,0x84115555);


//autok-disable


rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8013);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0f08);



rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bce);

temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);

printk("R tapbin=%x\n",temp);  //BGA best value is 9 (shift +-2, 7~b ) for 100 & 1000M


rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcd);  //adjust RC (for rising and falling time)
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG23,0x4444);  //tx rlen  (改用 autoK , 正常1000M/10M 需K到 4444, 100M K 到 4444 但其實不看是看 rlen100)


temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG23);

printk("rlen=%x\n",temp);



//rtd_outl(0xb801605c,0x84160000);    //rx len  細調 (可以中間去調)
//rtd_outl(0xb801605c,0x84167777);    //rx len  細調 (可以中間去調 ok)
//ms_delay(10);


rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bc0);       //bc0 reg21 [9:6] (100M, 不需 link) 的 rlen

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x01a0); //[9:6]   default = 7  set rlen = 6

 temp=rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG21);

printk("rlen100=%x\n",temp); //[9:6]   default = 9



//delay-cap force 15

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8011);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x1337);


rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bc0);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x3461);

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcd);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0xffff);



//set pga disable

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bce);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x0f15); // 20 * 5 = 100m


//ecx2

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a42);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG22,0x0f10);


//rh force 0

rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bc0);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG23,0x0002);



rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81bd);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0101); // LPF cable length  > 1 就開 en70  //rx len 的 粗調



rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8012);
rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xb70F);  // enable LPF B[15] 

//memory set 0x18016060 32 0x801f0bcc	#write en70[3] / en90[2]
//memory set 0x18016060 32 0x00130000	#read

}

void QC_Delay_RH_100m_1000M_1() 
{

printk("delay_rh...\n");
	
//green disable	
rtd_outl(0xb801605c,0x841f0a43);	
ms_delay(100);
rtd_outl(0xb801605c,0x841b8011);
ms_delay(10);
rtd_outl(0xb801605c,0x841c1737);	

//abiq 4444 (default = 5555, 1000M link abiq = 4444 , test mode 4 abiq = 7575)
//rtd_outl(0xb801605c,0x841f0bcc);	
//ms_delay(100);
//rtd_outl(0xb801605c,0x84115555);


//autok-disable

ms_delay(10);
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(100);
rtd_outl(0xb801605c,0x841b8013);	
ms_delay(100);
rtd_outl(0xb801605c,0x841c0f08);
ms_delay(10);


rtd_outl(0xb801605c,0x841f0bce);
ms_delay(100);
//rtd_outl(0xb801605c,0x84108888); //R code word
//ms_delay(10);
rtd_outl(0xb801605c,0x04100000);
ms_delay(10);
printk("R tapbin=%x\n",rtd_inl(0xb801605c));  //BGA best value is 9 (shift +-2, 7~b ) for 100 & 1000M

rtd_outl(0xb801605c,0x841f0bcd);   //adjust RC (for rising and falling time)
ms_delay(100);
rtd_outl(0xb801605c,0x84174444);	 //tx rlen  (改用 autoK , 正常1000M/10M 需K到 4444, 100M K 到 4444 但其實不看是看 rlen100)
ms_delay(10);

rtd_outl(0xb801605c,0x04170000);
ms_delay(10);
printk("rlen=%x\n",rtd_inl(0xb801605c));




//rtd_outl(0xb801605c,0x84160000);    //rx len  細調 (可以中間去調)
//rtd_outl(0xb801605c,0x84167777);    //rx len  細調 (可以中間去調 ok)
//ms_delay(10);


 rtd_outl(0xb801605c,0x841f0bc0);         //bc0 reg21 [9:6] (100M, 不需 link) 的 rlen
 ms_delay(100);
 rtd_outl(0xb801605c,0x841501a0);  // set rlen = 6 [6:9]
ms_delay(100);
 rtd_outl(0xb801605c,0x04150000);
 ms_delay(10);
printk("rlen100=%x\n",rtd_inl(0xb801605c)); //[9:6]   default = 9


//delay-cap force 15

rtd_outl(0xb801605c,0x841f0a43);
ms_delay(100);
rtd_outl(0xb801605c,0x841b8011);	
ms_delay(100);
rtd_outl(0xb801605c,0x841c1337);
ms_delay(100);


rtd_outl(0xb801605c,0x041c0000);
ms_delay(100);
printk("%x\n",rtd_inl(0xb801605c));

rtd_outl(0xb801605c,0x841f0bc0);
ms_delay(100);
rtd_outl(0xb801605c,0x84143461);	
ms_delay(10);
rtd_outl(0xb801605c,0x841f0bcd);
ms_delay(10);
rtd_outl(0xb801605c,0x8415ffff);	
ms_delay(10);


printk("set pga2...\n");
//set pga disable
rtd_outl(0xb801605c,0x841f0bce);
ms_delay(100);
rtd_outl(0xb801605c,0x84150f15);  // 20 * 5 = 100m
//rtd_outl(0xb801605c,0x84150f10);  
ms_delay(10);

//ecx2


rtd_outl(0xb801605c,0x841f0a42);
ms_delay(100);
rtd_outl(0xb801605c,0x84160f10);
ms_delay(10);
//rh force 0
rtd_outl(0xb801605c,0x841f0bc0);
ms_delay(100);
rtd_outl(0xb801605c,0x84170002);	
ms_delay(10);


rtd_outl(0xb801605c,0x841f0a43);
ms_delay(100);
rtd_outl(0xb801605c,0x841b81BD);
ms_delay(100);
rtd_outl(0xb801605c,0x841c0101); // LPF cable length  > 1 就開 en70  //rx len 的 粗調
ms_delay(10);




rtd_outl(0xb801605c,0x841f0a43);
ms_delay(100);
rtd_outl(0xb801605c,0x841b8012);
ms_delay(100);
rtd_outl(0xb801605c,0x841cb70F); // enable LPF B[15] 
ms_delay(100);




rtd_outl(0xb801605c,0x841f0bcc);
ms_delay(100);
rtd_outl(0xb801605c,0x04130000);
ms_delay(10);

printk("en70=%x\n",rtd_inl(0xb801605c));


//memory set 0x18016060 32 0x801f0bcc	#write en70[3] / en90[2]
//memory set 0x18016060 32 0x00130000	#read
   
	
}
void QC_RC_R_Amplitude_1000()
{

#if 0
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
	ms_delay(10);
	rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0bcd);  //adjust RC (for rising and falling time)
	ms_delay(100);
	rtd_outl(0xb801605c,0x84174444);
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x8415fffd);
	ms_delay(10);
#endif

	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x84158cc9);
	ms_delay(10);

#if 0
//set R value
rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
ms_delay(100);
rtd_outl(0xb801605c,0x84109999);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0
#endif

//Delay_RH_100m_1000M();

}



void QC_RC_R_Amplitude_10()
{

#if 0
	rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
	ms_delay(100);
	rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
	ms_delay(10);
	rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
	ms_delay(100);

	rtd_outl(0xb801605c,0x841f0bcd);  //adjust RC (for rising and falling time)
	ms_delay(100);
	rtd_outl(0xb801605c,0x84174444);
	ms_delay(10);
#endif

	rtd_outl(0xb801605c,0x841f0bca); // amplitude adjust
	ms_delay(100);
	rtd_outl(0xb801605c,0x84157b7b);
	ms_delay(10);


	rtd_outl(0xb801605c,0x841f0bcc); // line driver bias current
	ms_delay(100);
	rtd_outl(0xb801605c,0x84112222); // plug out cable will reset
	ms_delay(100);

	//set R value
	//rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
	//ScalerTimer_DelayXms(100);
	//rtd_outl(0xb801605c,0x8410aaaa);// [15:12] => Port 3;   [11:8] => Port 2;  [7:4] => Port 1 [3:0] => Port 0
}




int performance_test_100M(void)
{

	volatile unsigned char *pkt=NULL;
	      unsigned int i = 0 ; 
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;
   // UINT16 status = 0;
  //  UINT8 *ptx_buffer;
 //   UINT32 tx_count=0xff000000;

     rtl6330cp_verify_phy_init();


    QC_AutoK_shift();
    QC_Delay_RH_100m_1000M();
#ifdef CONFIG_BGA
   QC_RC_R_Amplitude_100_1000();
#else
  QC_RC_R_Amplitude_100_QFP();
#endif
   

#if 0 // auto_n_way  //avoid link partner to enter half duplex mode not full duplex mode 
	rtd_outl(0xb801605c,0x841f0a42);
	 ms_delay(100);
	rtd_outl(0xb801605c,0x84140000); //clear 500M full cap
	ms_delay(10);

	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(100);
	rtd_outl(0xb801605c,0x84090000); //clear 1000T half & full cap.
	ms_delay(10);
#else  // for smartbits (must use force mode avoid enter half duplex mode)
   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);

   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
#endif	
   ms_delay(5000);



    rtl6330cp_verify_reset();
    udelay(10);


//	green_function_close();
//   printk(" 100M: ");    

    LINK_SPEED();

    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(1/0);

    printk("wait tx...\n");
    ms_delay(1000);
 //   green_function_close(); // green close will enter n-way mode

    pkt_gen_rx_enable();

//	rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
   // ms_delay(100);


//	rtd_outl(0xb801605c, 0x84105a06);   //set pgtx_enable
//	ms_delay(0x10);
	
	
#if 1
	printk("100M start\n");
	printk("reg=%x\n",rtd_inl(0xb8016058));  //check bit22 , Mac enter full duplex

	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
//--		printk("%x\n",pRxBDPtr[rxBDtail].StsLen);
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
			
			#if 1
			//printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);
		//      printk("%d %x %x\n",rtd_inl(0x18016010),pRxBDPtr[rxBDtail].StsLen,pRxBDPtr[rxBDtail + 1].StsLen);
	      //         if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
	//			   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;
				 

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 

			(*(volatile unsigned int *)(0x18016234) = (((*(volatile unsigned int *)(0x18016234)) | 0x1  )));
	
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
	 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			  if (0x1B == rtd_inl(0x18062300)) // ESC key
				goto msg;
			#endif
	       } 

	}

msg:
	rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
	wait_phy_read_finish();
	printk("reg_16=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
	wait_phy_read_finish();
	printk("reg_17=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
	wait_phy_read_finish();
	printk("reg_18=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);

	

	

#endif

	

}


//become link partner
void reg_power_test(void)
{

	rtl6330cp_verify_phy_init();

	while(1)
	{

	printk("reg power down ....\n");
	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(0x10);
	rtd_outl(0xb801605c,0x84001840);
	ms_delay(0x10);


	ms_delay(20000);
	

	printk("reg power on ....\n");
	rtd_outl(0xb801605c,0x841f0a40);
	ms_delay(0x10);
	rtd_outl(0xb801605c,0x84001040);
	ms_delay(0x10);

	ms_delay(20000);

	}

}


//DUT
int enter_aldps_mode(void)
{
	 rtl6330cp_verify_phy_init();


//enter LDPS mode  A43 , reg24 , bit2
	rtd_outl(0xb801605c ,0x841f0a43);
	ms_delay(0x10);
	rtd_outl(0xb801605c, 0x8418218c);
	ms_delay(0x10);

	while(1)
	{
		//LDPS state A43 reg26,bit14
		rtd_outl(0xb801605c,0x841f0a43);
		ms_delay(0x10);
		rtd_outl(0xb801605c,0x041a0000);
		ms_delay(0x10);

		printk("@@@@@@ %x\n",rtd_inl(0xb801605c));
		if ((rtd_inl(0xb801605c) & 0x4000))
			printk("reg power off enter LDPS %x\n");
		else
			printk("reg power on leave LDPS\n");

		ms_delay(1000);
	}
	

}




int performance_test_1000M(void)
{
      volatile unsigned char *pkt=NULL;
	//unsigned int i = 0 ; 
    //printk(" LAN QC test start...\n ");  

    UINT32 pkt_size=64;
    int count = 0;
   // UINT16 status = 0;
  //  UINT8 *ptx_buffer;
 //   UINT32 tx_count=0xff000000;
	
     rtl6330cp_verify_phy_init();


  QC_AutoK_shift();
  QC_Delay_RH_100m_1000M();
    QC_RC_R_Amplitude_100_1000();
	 
   rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_1000M);
   rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	

//rtd_outl(0xb801605c,0x84004140);///--- set gphy 1000M mode && loopback && full-duplex
	//1000M normal mode
	//rtd_outl(0xb801605c,0x84000140); ///--- set gphy 1000M mode && normal && full-duplex
	//rtd_outl(0xb801605c,0x84001140); ///--- set gphy auto mode && normal && full-duplex

	//100M normal mode
//	rtd_outl(0xb801605c,0x84002100); ///--- set gphy 100M mode && normal && full-duplex

	//10M normal mode
	//rtd_outl(0xb801605c,0x84000100); ///--- set gphy 10M mode  && normal && full-duplex
//	rtd_outl(0xb801605c,0x84004100); ///--- set gphy 10M mode  && loopback && full-duplex

	 
    rtl6330cp_verify_reset();
    udelay(10);
  
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
  //  memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
  //  udelay(10);

    printk("wait tx...\n");
    ms_delay(1000);
 //   green_function_close();

     LINK_SPEED();

/*

   QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0x5c,LAN_QC_VERIFY_LEN);
    udelay(10);


    for(;;)
    {
    	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    }
*/	 

//    green_function_close();
//    pkt_gen_tx_rx_enable();
	

//	rtd_outl(0xb801605c,0x841f0a40);// change Page to a40
//	ms_delay(100);
//	rtd_outl(0xb801605c,0x84009200);// page0 reg0 = 0x9200 (reautonegotiation) (don't plug cable)

//green_function_close();
 //   ms_delay(1000);
//    pkt_gen_tx_enable();

  //  rtd_outl(0xb801605c,0x841f0c80);// change Page to c80
  //  ms_delay(100);

  //  rtd_outl(0xb801605c,0x84130040);
 //   ms_delay(0x10);

	//rtd_outl(0xb801605c,0x8414ffff); // send 16 packet
	//ms_delay(0x10);

//	rtd_outl(0xb801605c, 0x84105a06);   //set pgtx_enable
//	ms_delay(0x10);


#if 0
	//rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	//ms_delay(100);
	
	while(1)
	{
		rtd_outl(0xb801605c, 0x04160000);       // read txcnt_15_0
		wait_phy_read_finish();
		printk("reg_22=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04170000);       // read txcnt_31_16
		wait_phy_read_finish();
		printk("reg_23=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
	/*	
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("reg_18=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
       */
	}
#endif	

 	pkt_gen_rx_enable();
#if 0
  // green_function_close();

pkt_gen_rx_enable();



	rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	ms_delay(100);
	while(1)
	{
		rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
		wait_phy_read_finish();
		printk("reg_16=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
		wait_phy_read_finish();
		printk("reg_17=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);
		
		rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
		wait_phy_read_finish();
		printk("reg_18=%x\n", rtd_inl(0xb801605c));

		ms_delay(100);

	}
#endif	


	rtd_outl(0xb801605c,0x841f0bcc);
ms_delay(100);
rtd_outl(0xb801605c,0x04130000);
ms_delay(10);
printk("en70=%x\n",rtd_inl(0xb801605c));

       
#if 1
	printk("1000M\n");
	printk("reg1=%x\n",rtd_inl(0xb8016058));  //check bit22 , Mac enter full duplex
	rtd_outl(0xb801605c,0x041a0000);
	ms_delay(10);
	printk("status=%x\n",rtd_inl(0xb801605c));
	printk("start....\n");

	while(1)
	{
		
		flush_cache2((unsigned long)&pRxBDPtr[rxBDtail], sizeof(NIC_FD_T));
		while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0) 
	      	{      
	
			#if 1
			//printk("rxBDtail=%d\n",rxBDtail);
	      	       // printk("888\n");
	      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
			 // printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

	         //      if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
		//		   	printk(" RX descriptor CRC status error\n");
		       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
				  
	             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

	   //         rtl8139cp_verify_dump_desc(FD_RX_DESC);

	          	
	            if(txBDtail == (TX_QC_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOR=1 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  txBDtail=0;
	            }
	            else 
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOR=0 
	                flush_cache((unsigned long)& pTxBDPtr[txBDtail], sizeof(NIC_FD_T));
			  ++txBDtail;
	            }                       

	             
	            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

	            //FlushCache(); 
	            //  flush_dcache_all();
			
		     //udelay(200); 	 	 
	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

	            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
	  		(*(volatile unsigned int *)(0x18016234) = (((*(volatile unsigned int *)(0x18016234)) | 0x1  )));
	           	   	 
	             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
	            //rtl8139cp_verify_dump_all_reg();
			 
	            if(rxBDtail== (RX_QC_DESC_NUM -1))
	            {
	                pRxBDPtr[rxBDtail].StsLen =0xf0000800;
	                rxBDtail=0;
	            }
	            else
	            {
	                pRxBDPtr[rxBDtail].StsLen =0x80000800;
	                ++rxBDtail;
	            } 

			#endif
			
			  if (0x1B == rtd_inl(0x18062300)) // ESC key
				goto msg;
	       } 

	}

#endif

	msg:
	rtd_outl(0xb801605c,0x841f0c81);// change Page to c81
	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04100000);       // read rxcnt_15_0
	wait_phy_read_finish();
	printk("reg_16=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04110000);       // read rxcnt_31_16
	wait_phy_read_finish();
	printk("reg_17=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);
	
	rtd_outl(0xb801605c, 0x04120000);       // read rxerr_15_0
	wait_phy_read_finish();
	printk("reg_18=%x\n", rtd_inl(0xb801605c));

	ms_delay(100);


   return QC_Result;

}


void giga_mdio_loopback(void)
{
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);//page0a43
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG24,0xad98);// set mdio loopback and mdio loopback short cable
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a4a);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0181);
//	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a40);
//	  rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1240);
//	  wait_ms(50);
	 
}

//force giga
void giga_mdio_loopback1(void)
{
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a40);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG4,0x0001);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a42);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG20,0x0000);

	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a40);//page0a43
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,0x0300);// set mdio loopback and mdio loopback short cable
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1040);

       rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);//page0a43
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG24,0xad98);// set mdio loopback and mdio loopback short cable
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a4a);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0181);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a40);//page0a43
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1240);
}


int lan_qc_verify(void)
{  
    volatile unsigned char *pkt=NULL;
	
    //printk(" LAN QC test start...\n ");  
	
    
     rtl6330cp_verify_phy_init(); 


   QC_AutoK_shift();
   // QC_Delay_RH_100m_1000M();
#ifdef CONFIG_BGA
   QC_RC_R_Amplitude_100_1000();
#else
  QC_RC_R_Amplitude_100_QFP();
#endif


#if QC_test_1000M
	 giga_mdio_loopback();
      // LINK_STATUS();
	rtl6330cp_verify_reset();
	udelay(10);
	
#if auto_n_way 
#else
	rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_1000M);
	rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex);
#endif
	LINK_STATUS();
	printk(" 1000M: ");    
	LINK_SPEED();

	QC_Result = VERIFY_FAIL;
	pkt = txbuffer;
	memset((void *) pkt,0x5c,LAN_QC_VERIFY_LEN);
	udelay(10);
	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	udelay(100);  
	rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 

	if(QC_Result == VERIFY_FAIL)
	{
		printk(" 1000M_retry: ");    
		rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
		udelay(100);  
		rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 
		if(QC_Result == VERIFY_FAIL){
			return VERIFY_FAIL;  
		}
	}  
#endif


#if QC_test_100M
	rtl6330cp_verify_reset();
	udelay(10);
#if nway_sel_100M  //avoid link partner to enter half duplex mode not full duplex mode 
	//rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,0x0000);// disable giga capability
	//rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1200);// re-auto negotiation
#else
	rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
	rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
#endif	
	LINK_STATUS();

	printk(" 100M: ");    
	LINK_SPEED();
	
	QC_Result = VERIFY_FAIL;
	pkt = txbuffer;
	memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
	udelay(10);
	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	udelay(100);
	rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 

	if(QC_Result == VERIFY_FAIL)
	{
		printk(" 100M_retry: ");    
		rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
		udelay(100);  
		rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 
		if(QC_Result == VERIFY_FAIL){
			return VERIFY_FAIL;  
		}
	}
#endif 

#if QC_test_10M 
	rtl6330cp_verify_reset();
	udelay(10);  
	
#if nway_sel_10M   // avoid link partner only to enter half duplex not full duplex
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG9,0x0000);// disable giga capability
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG4,0x0061);// disable 100M capability
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x1200);// re-auto negotiation
#else
	rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);
	rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
#endif	
	LINK_STATUS();
	
	printk("  10M: ");
	LINK_SPEED();

	QC_Result = VERIFY_FAIL;
	pkt = txbuffer;
	memset((void *) pkt,0x3f,LAN_QC_VERIFY_LEN);
	udelay(10);  
	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	udelay(100); 
	rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	

	if(QC_Result == VERIFY_FAIL)
	{
		printk(" 10M_retry: ");    
		rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
		udelay(100);  
		rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 
		if(QC_Result == VERIFY_FAIL){
			return VERIFY_FAIL;  
		}
	}	
#endif	
    return QC_Result;
    	 		
}


int test1()
{

	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);//page0a43
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG24,0xad98);// set mdio loopback and mdio loopback short cable
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a4a);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0181);
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);//page0a43
	 rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,0x0140);

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);


	

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	

	ms_delay(2000);

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);

	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	printk("debug = %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG26));
	ms_delay(50);
	


}

int lan_ft_verify(void)
{  

    volatile unsigned char *pkt=NULL;
	

    rtl6330cp_verify_phy_init();


   QC_AutoK_shift();
   // QC_Delay_RH_100m_1000M();
#ifdef CONFIG_BGA
   QC_RC_R_Amplitude_100_1000();
#else
  QC_RC_R_Amplitude_100_QFP();
#endif


#if CONFIG_BGA
	giga_mdio_loopback();
	rtl6330cp_verify_reset();
	udelay(10);
	rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_1000M);
	rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex);
	
	LINK_STATUS();
	printk(" 1000M: ");    
	LINK_SPEED();

	QC_Result = VERIFY_FAIL;
	pkt = txbuffer;
	memset((void *) pkt,0x5c,LAN_QC_VERIFY_LEN);
	udelay(10);
	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	udelay(100);  
	rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 

	if(QC_Result == VERIFY_FAIL)
	{
		printk(" 1000M_retry: ");    
		rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
		udelay(100);  
		rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 
		if(QC_Result == VERIFY_FAIL){
			return VERIFY_FAIL;  
		}
	}  
#endif



#if QC_test_100M
	rtl6330cp_verify_reset();
	udelay(10);
	rtl6330cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
	rtl6330cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
	
	LINK_STATUS();

	printk(" 100M: ");    
	LINK_SPEED();
	
	QC_Result = VERIFY_FAIL;
	pkt = txbuffer;
	memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
	udelay(10);
	rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	udelay(100);
	rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 

	if(QC_Result == VERIFY_FAIL)
	{
		printk(" 100M_retry: ");    
		rtl6330cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
		udelay(100);  
		rtl6330cp_verify_poll(rtl6330cp_verify_pkt_handle);	 
		if(QC_Result == VERIFY_FAIL){
			return VERIFY_FAIL;  
		}
	}
#endif 
	 

    return QC_Result;
    	 		
}






#if 0
int lan_qc_verify_MacLBK_100M(void)
{  
    
    volatile unsigned char *pkt=NULL;
  
    //100M
   
    rtl8139cp_verify_reset();
	
    udelay(10);	

    if (loopback_mode == PHY_LOOP_BACK)
    {
	
    	rtl8139cp_verify_phy_set_lbk(RTD2885_LAN_PHY_ID,PHY_LBK_Enable);	  
    	rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    	rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    }
    else //if (loopback_mode == NORMAL)
    {
    	rtl8139cp_verify_phy_set_lbk(RTD2885_LAN_PHY_ID,PHY_LBK_Disable);	  
    	rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    	rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    }
    printk(" 100M: ");    
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
	
    memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
	
    udelay(10);
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    
    udelay(100);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
    
    if(QC_Result == VERIFY_FAIL)
    {

	    printk(" 100M_retry: ");    
	    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
	    udelay(100);  
	    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
	    if(QC_Result == VERIFY_FAIL){
	        return VERIFY_FAIL;  
	    }
    }

    return QC_Result;
    	 		
}



int lan_qc_verify_DLBK_100M(void)
{  
    
    volatile unsigned char *pkt=NULL;
    //printk(" LAN QC test start...\n ");  
  
    //100M
    rtl8139cp_verify_reset();
    udelay(10);	
    rtl8139cp_verify_phy_set_lbk(RTD2885_LAN_PHY_ID,PHY_LBK_Enable);	  
    rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 

    printk(" 100M: ");    
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
    udelay(10);
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    
    //printk(" B\n");
    
    udelay(100);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
    
    if(QC_Result == VERIFY_FAIL)
    	{

    printk(" 100M_retry: ");    
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    udelay(100);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
     if(QC_Result == VERIFY_FAIL){
        return VERIFY_FAIL;  
        }
    	}
	
    return QC_Result;
    	 		
}


int lan_qc_verify_ft(void)
{

    volatile unsigned char *pkt=NULL;
    //rtd_outl(0xb8016234, ((rtd_inl(0xb8016234)&(0xffe7e7ff))|0x2<<11)|0x01<<19);  

    //100M
    rtl8139cp_verify_reset();
    udelay(1000);  
    rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_100M);
    rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex); 
    printk(" 100M:\n ");    
    QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0x97,LAN_QC_VERIFY_LEN);
    udelay(10);    
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    
    //printk(" B\n");
    
    udelay(100);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
    
    if(QC_Result == VERIFY_FAIL)
    	{

    printk(" 100M_retry:\n ");    
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    udelay(100);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
     if(QC_Result == VERIFY_FAIL){
        return VERIFY_FAIL;  
      }
    	}
	
// 10M        
    rtl8139cp_verify_reset();
    udelay(1000);  
    rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);
    rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex);
    printk(" 10M: \n");

	QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0x3f,LAN_QC_VERIFY_LEN);

    //rtl8139cp_verify_dump_desc(1);
    //rtl8139cp_verify_dump_desc(0);
    udelay(30000); 
    
   rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    udelay(10000); 
    //rtl8139cp_verify_dump_desc(1);
    //rtl8139cp_verify_dump_desc(0);
    
		//printk(" A\n");
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	
      

    if(QC_Result == VERIFY_FAIL)
    	{
    printk(" 10M_retry: \n");    
    rtl8139cp_verify_transmit(txbuffer, LAN_QC_VERIFY_LEN);  
    udelay(100000);  
    rtl8139cp_verify_poll(rtl8139cp_verify_pkt_handle);	 
     if(QC_Result == VERIFY_FAIL){
        return VERIFY_FAIL;  
      }
    }	

 return QC_Result;
    	 		
}




void rtl8139cp_smartbit_test_tx(int num,int size,int mod)
{
    UINT32 count=0;
    UINT32 pkt_size=64;
    UINT16 status = 0;
    UINT8 *ptx_buffer;
    UINT32 tx_count=0xff000000;
	  
    rtl8139cp_verify_reset();
	
    //udelay(1000000);


    // 10M        
    printk("rtl8139cp_smartbit_test_tx start\n");

    ptx_buffer=KSEG1ADDR(&tx_buffer[0]);

    memset(ptx_buffer,0xff,6);
    memset(ptx_buffer+12,0xff,TX_BUF_SIZE-12);
    sys_dcache_flush_and_invalidate_all();
    if(num == 0){
    printk("rtl8139cp_smartbit_test_tx num=0\n");		
	    while(1)
	    {
	      //udelay(1000);
              /*  
             while((pTxBDPtr[txBDtail-1].StsLen & 0x80000000)==0x80000000)
            	{
                udelay(10);
		  //printk(".=0x%x\n", pTxBDPtr[txBDtail-1]);
            	}  		   

                */  
		 while(tx_count==(rtd_inl(0xb8016010)&0xffff0000))
            	{
                udelay(5);
		  //printk(".=0x%x\n", pTxBDPtr[txBDtail-1]);
            	}
             tx_count=(rtd_inl(0xb8016010)&0xffff0000);
			 
		  
	        if(size == 0)
	            pkt_size = (pkt_size+777)%mod;
	        else
	            pkt_size = size;
	    #if LITTLEENDIA_ETH
	        if((at_swap_32(pTxBDPtr[txBDtail].StsLen) & 0x80000000) ==0)
	        {
	            if(txBDtail == (TX_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =at_swap_32((0xf0000000|pkt_size)|(1<<23));  //Own=1 EOS=1 
			  pTxBDPtr[txBDtail].DataPtr = at_swap_32(PHYSADDR((UINT32) ptx_buffer));
	                txBDtail=0;           
	            }
	            else
	            {
	                pTxBDPtr[txBDtail].StsLen =at_swap_32(0xb0000000|pkt_size)|(1<<23);  //own=1 EOS=0 
					pTxBDPtr[txBDtail].DataPtr = at_swap_32(PHYSADDR((UINT32) ptx_buffer));
	                txBDtail++;
	            }
	    #else 
		     if((pTxBDPtr[txBDtail].StsLen & 0x80000000) ==0)
	              {
	            if(txBDtail == (TX_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000|pkt_size)|(1<<23);  //Own=1 EOS=1 
      			 pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32) ptx_buffer);
	                txBDtail=0;           
	            }
	            else
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000|pkt_size)|(1<<23);  //own=1 EOS=0 
			  pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32) ptx_buffer);
	                txBDtail++;
	            }
         	#endif   
	            //rtd_inl(0xa0000000);           
		     //printk("TX_DEC_LEN = 0x%x\n", pTxBDPtr[txBDtail-1].StsLen);
	            //printk("TX_DEC_ADD = 0x%x\n", pTxBDPtr[txBDtail-1].DataPtr); 	
		     		
	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1);
                   //printk(".");		
                   //udelay(1000);
                     //printk("TX_DEC_LEN = 0x%x\n", pTxBDPtr[txBDtail-1].StsLen);
			//   printk("TX_DEC_offset_6104 = 0x%x\n", rtd_inl(0xb8016104));
	    	}
	    	else
	    	{
	            status = rtd_inw(ioaddr+ISR);
	            rtd_outw(ioaddr+ISR,0xffff);
	    	    if (status & (0x20|0x04|0x10|0x80|0x200))  	   	
	    		    printk("line=%d error:status = 0x%x \n",__LINE__,status);
	    	}
		}    
    }
    else{
	    for(count=0;count<num;count++)
	    {
	        if(size == 0)
	            pkt_size = (pkt_size+777)%mod;
	        else
	            pkt_size = size;
	     #if LITTLEENDIA_ETH
	        if((at_swap_32(pTxBDPtr[txBDtail].StsLen) & 0x80000000) ==0)
	        {
	            if(txBDtail == (TX_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =at_swap_32((0xf0000000|pkt_size)|(1<<23));  //Own=1 EOS=1 
	                txBDtail=0;           
	            }
	            else
	            {
	                pTxBDPtr[txBDtail].StsLen =at_swap_32((0xb0000000|pkt_size)|(1<<23));  //own=1 EOS=0 
	                txBDtail++;
	            }
           #else 
         	if((pTxBDPtr[txBDtail].StsLen & 0x80000000) ==0)
	        {
	            if(txBDtail == (TX_DESC_NUM -1))
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xf0000000|pkt_size)|(1<<23);  //Own=1 EOS=1 
	                txBDtail=0;           
	            }
	            else
	            {
	                pTxBDPtr[txBDtail].StsLen =(0xb0000000|pkt_size)|(1<<23);  //own=1 EOS=0 
	                txBDtail++;
	            }
            #endif  		
	            rtd_inl(0xa0000000);           
	            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1);
	    	}
	    	else
	    	{
	            status = rtd_inw(ioaddr+ISR);
	            rtd_outw(ioaddr+ISR,0xffff);
	    	    if (status & (0x20|0x04|0x10|0x80|0x200))  	   	
	    		    printk("line=%d error:status = 0x%x \n",__LINE__,status);
	    	}
		}
	}
}


static int rtl8139_SD10M_verify_transmit(volatile void *packet, int length)
{
	unsigned int i=0;
	unsigned int len = length;
//	UINT32 tx_status=0;
	
	//memcpy((char *)tx_buffer, (char *)packet, (int)length);

#if LITTLEENDIA_ETH
  
	
	pTxBDPtr[txBDtail].DataPtr = at_swap_32(PHYSADDR((UINT32) tx_buffer)); // KSEG1ADDR((UINT32) tx_buffer); 

	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) & (~TX_DESC_DATA_LEN_MASK)); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen) | (len));

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen = at_swap_32(at_swap_32(pTxBDPtr[txBDtail].StsLen)|(OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC));
#else	 	 
	pTxBDPtr[txBDtail].DataPtr = PHYSADDR((UINT32) tx_buffer); // KSEG1ADDR((UINT32) tx_buffer); 
	
    if(len < 60)
	   	len = 60;
	   
    pTxBDPtr[txBDtail].StsLen &= (~TX_DESC_DATA_LEN_MASK); // (~0x00000fff);
    pTxBDPtr[txBDtail].StsLen |= (len);

    /* trigger to send */
    pTxBDPtr[txBDtail].StsLen |= (OWN_BIT|FS_BIT|LS_BIT|TX_DESC_CMD_CRC);
#endif    


    //flush_dcache();
    sys_dcache_flush_and_invalidate_all();
    //sys_dcache_flush_and_invalidate_all();
    // High Priority DMA-Ethernet Transmit enable.
    rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);

    udelay(100); 
    
    
	// 50 ms
    i = 5000;
#if LITTLEENDIA_ETH
    while((at_swap_32(pTxBDPtr[txBDtail].StsLen) & (OWN_BIT)) && (--i) )
#else
    while((pTxBDPtr[txBDtail].StsLen & (OWN_BIT)) && (--i) )
#endif

	
  if(lan_qc_verify() == VERIFY_FAIL)
	{
		udelay(10);
	};
    
    // debug
    /*
    if (i==0) {
    	printk("Tx TimeOut : Status = 0x%x\n",pTxBDPtr[txBDtail].StsLen);
    	return 0;
    }

#if LITTLEENDIA_ETH    
     tx_status = at_swap_32(pTxBDPtr[txBDtail].StsLen);

#else
     tx_status = pTxBDPtr[txBDtail].StsLen;

#endif    


    if (tx_status & TX_DESC_STATS_UNF)
        printk("Tx FIFO Underrun : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_TES)
        printk("Tx Error Summary : Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_LNKF)
        printk("Link Failure : Status = 0x%x\n",tx_status);

        if (tx_status & TX_DESC_STATS_EXC)
        printk("Excessive Collision , aborted (Over 16 collisions): Status = 0x%x\n",tx_status);

    if (tx_status & TX_DESC_STATS_OWC)
        printk("Out of Window Collision : Status = 0x%x\n",tx_status);

    //if (TX_DESC_STATS_CC(tx_status))
	//printk("Tx Collision Counter = 0x%x\n",TX_DESC_STATS_CC(tx_status));
		
    
	// printk("packet = 0x%x, len = 0x%x\n",tx_buffer,len);
	
	
#if defined(_RTL8139CP_VERIFY_DEBUG_TX) 	
    printk("S ");   	
    printk("TXOKCNT = 0x%x\n",rtd_inw(TXOKCNT+ioaddr));
    printk("TRSR = 0x%x\n",rtd_inl(TRSR+ioaddr));
#endif

    /* advance one */
    txBDtail++;
    txBDtail %= TX_QC_DESC_NUM;
		
    return 1;
}
	

int rtl8139cp_verify_poll_nocheck(void)
{
	UINT16 status=0;
	UINT8  *rxdata=NULL;
//	UINT32 blen=0;	
//	UINT16	pkt_count=0;
	
    unsigned int i=0;
    // 50 ms
    i = 5000;
	while(!(rtd_inw(ioaddr+ISR) & (ISR_ROK)) && (--i))
	{
		udelay(10);
					
	}

/*	
    // debug
    if (i==0) {
        printk("Rx TimeOut : Status = 0x%x\n",rtd_inw(ioaddr+ISR));
        return 0;
    }

    */

	status = rtd_inw(ioaddr+ISR);

	/*
	   
	if (!status || (status == 0xFFFF))
		return 0;
   
    if (status & 0x20)  	   	
    	printk("error:RX desc. unavailable ,status = 0x%x \n",status); 
    	
    if (status & 0x04)  	
    	printk("error:RX runt ,status = 0x%x \n",status); 	
    	
    if (status & 0x10) {
    	printk("error:RX ovf ,status = 0x%x , reset\n",status);
    	rtl8139cp_verify_reset();
    }	

          
 */
    // Clear Interrupt status bits.	
 	rtd_outw(ioaddr+ISR,status);

	
 
    //flush_dcache();
    //sys_dcache_flush_and_invalidate_all();

#if LITTLEENDIA_ETH
    while((at_swap_32(pRxBDPtr[rxBDtail].StsLen) & OWN_BIT) ==0)
 #else
   while(((pRxBDPtr[rxBDtail].StsLen & OWN_BIT) ==0))    
#endif
    {
       //flush_dcache();
       //sys_dcache_flush_and_invalidate_all();

/*

#if LITTLEENDIA_ETH
       rxdata = (char*)at_swap_32(pRxBDPtr[rxBDtail].DataPtr);          //*cyhuang modified 1019 
#else
       rxdata = (char*)pRxBDPtr[rxBDtail].DataPtr;          //*cyhuang modified 1019 
#endif
              
       rxdata = (char*) KSEG1ADDR((UINT32) rxdata);
   
#if LITTLEENDIA_ETH
       blen = at_swap_32(pRxBDPtr[rxBDtail].StsLen);
#else
       blen = (pRxBDPtr[rxBDtail].StsLen);
#endif
       // blen = (blen & 0xfff) - 4;
       blen = RX_DESC_DATA_LEN(blen)-4;

*/
       
       // Debug
       /*
       if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_FAE)  
       	  printk("Rx Frame Alignment Error: Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);      
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_RES)
       	  printk("Rx Error Summary : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_IPF)	  
          printk("Rx IP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_UDPF)
 	      printk("Rx UDP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
 	   else if (pRxBDPtr[rxBDtail].StsLen & RX_DESC_STATS_TCPF)	  
 	      printk("Rx TCP checksum failure : Status = 0x%x\n",pRxBDPtr[rxBDtail].StsLen);
       */
 

	   /*
	   if (handle_func) {
			if (handle_func(rxdata,blen))
				pkt_count++;
	   }
	   else		
  	   		pkt_count++;

*/
 #if LITTLEENDIA_ETH
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) & (~RX_DESC_DATA_LEN_MASK));// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen) | (RX_DESC_BUFFER_SIZE));
       pRxBDPtr[rxBDtail].StsLen = at_swap_32(at_swap_32(pRxBDPtr[rxBDtail].StsLen)|(OWN_BIT));
#else 	   		  	   	
       pRxBDPtr[rxBDtail].StsLen &= (~RX_DESC_DATA_LEN_MASK);// (~0xfff);
       pRxBDPtr[rxBDtail].StsLen |= (RX_DESC_BUFFER_SIZE);
       pRxBDPtr[rxBDtail].StsLen |= (OWN_BIT);
#endif           
       rtd_outb(ioaddr + EthrntRxCPU_Des_Num,rxBDtail);
   
       rxBDtail++;
       rxBDtail %= RX_QC_DESC_NUM;       
    } // End of while
   // return pkt_count;
	
      return 0;
      
    

}

int rtl8139cp_10M_tx_verify(void)
{   
    volatile unsigned char *pkt=NULL;
    int LAN_10M_TX_VERIFY_LEN_tmp=0x180;
    int LAN_10M_TX_VERIFY_LEN_tmp2=0x500;	

    rtl8139cp_verify_reset(); 
    udelay(1000);
     

    // 10M        
    printk(" 10M pattern 0xff\n");
    rtl8139cp_verify_phy_set_duplex_mode(RTD2885_LAN_PHY_ID,PHY_Full_Duplex);
    rtl8139cp_verify_phy_set_speed(RTD2885_LAN_PHY_ID,PHY_10M);

     // PHY 10M LBK setting    
     rtd_outl(ioaddr +MIIAR, 0x84180330);


	QC_Result = VERIFY_FAIL;
    pkt = txbuffer;
    memset((void *) pkt,0xff,LAN_10M_TX_VERIFY_LEN_tmp2);

    //rtl8139cp_verify_dump_desc(1);
    //rtl8139cp_verify_dump_desc(0);
    udelay(100);      

    while(1)
    {
   rtl8139_SD10M_verify_transmit(txbuffer, LAN_10M_TX_VERIFY_LEN_tmp);  
    udelay(10);      

    //rtl8139cp_verify_dump_desc(1);
    //rtl8139cp_verify_dump_desc(0);

    rtl8139cp_verify_poll_nocheck();	  
           //printk(".");	

    }
    if(QC_Result == VERIFY_FAIL){
        return VERIFY_FAIL;  
    }
    //rtl8139cp_verify_dump_desc(1);
    //rtl8139cp_verify_dump_desc(0);
    // 100M    


    return QC_Result;
    	 		
}


/**
*      Function: rtl8139cp_smartbit_test_export
*      Description: 
*      Parameter: 
**/
void rtl8139cp_smartbit_test(void) {
    UINT32 pkt_size=0;	
 //   UINT16 status = 0;
    //UINT32 test_index=0;
    //UINT32 tx_count=0xff000000;	
    //int tdi=0;
    //int toddi=0; 	
 
    rtl8139cp_verify_reset();   
    sys_dcache_flush_and_invalidate_all();
    udelay(1000);	
    printk(" \nSmartbit test ready.... \n");	

	/*
    for (toddi=0; toddi<64;toddi++)	
    memset(pRxBDPtr[toddi].DataPtr,0x00,0x800); 
    */
	
    rtd_outl(0xb8016234, ((rtd_inl(0xb8016234)&(0xffe7e7ff))|0x2<<11)|0x01<<19); 
    rtd_outl(0xb8016238, (rtd_inl(0xb8016238)|0x01<<11));  	
  
    printk("0xb8016238=%x \n", rtd_inl(0xb8016238));
    printk("0xb8016234=%x \n", rtd_inl(0xb8016234)); 
    printk("0xb8016230=%x \n", rtd_inl(0xb8016230)); 	
 


     //debug port
    //rtd_outl(0xb8016200, 0x00000208); 


       
    while(1)
   {
      
     #if LITTLEENDIA_ETH
	 
      	while(((at_swap_32(pRxBDPtr[rxBDtail].StsLen)) & 0x80000000) ==0)      	
      	{      		      		         		  
            pkt_size = at_swap_32(pRxBDPtr[rxBDtail].StsLen) & (0x00000fff);   //Rx buffer_size
            pkt_size =64;

            pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

            //rtl8139cp_verify_dump_desc(FD_RX_DESC);
            
            if(txBDtail == (TX_DESC_NUM -1))
            {
                pTxBDPtr[txBDtail].StsLen =at_swap_32(0xf0000000+pkt_size);  //Own=1 EOS=1 
                txBDtail=0;
            }
            else 
            {
                pTxBDPtr[txBDtail].StsLen =at_swap_32(0xb0000000+pkt_size);  //own=1 EOS=0 
                txBDtail++;
            }                       
    	    //rtd_inl(0xa0000000);
           //rtl8139cp_verify_dump_desc(FD_TX_DESC);
            
            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH); 
            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/);               
               
            //while((at_swap_32(pTxBDPtr[txBDtail].StsLen) & (OWN_BIT)));               
            
            //rtl8139cp_verify_dump_desc(FD_TX_DESC);
            //rtl8139cp_verify_dump_all_reg();
            
            if(rxBDtail== (RX_DESC_NUM -1))
            {
                pRxBDPtr[rxBDtail].StsLen =at_swap_32(0xf0000800); 
                rxBDtail=0;
            }
            else
            {
                pRxBDPtr[rxBDtail].StsLen =at_swap_32(0xb0000800);
                rxBDtail++;
            }            
            #if 0
            //rtd_inl(0xa0000000);
			status = rtd_inw(ioaddr+ISR);
	    	printk("status = 0x%x \n",status);			   		   
		    if (status & 0x20)  	   	
		    	printk("error:RX desc. unavailable ,status = 0x%x \n",status); 
		    	
		    if (status & 0x04)  	
		    	printk("error:RX runt ,status = 0x%x \n",status); 	
		    	
		    if (status & 0x10) {
		    	printk("error:RX ovf ,status = 0x%x , reset\n",status);
		    }
		#endif
        }
    #else

     	while((pRxBDPtr[rxBDtail].StsLen & 0x80000000) ==0x0)      	
      	{      
      	        //printk("888\n");
      	       // printk("pRxBDPtr[rxBDtail+1].StsLen = 0x%x, rxBDtai=%d \n",pRxBDPtr[rxBDtail+1].StsLen, rxBDtail);
		//  printk("pRxBDPtr[rxBDtail+2].StsLen = 0x%x \n",pRxBDPtr[rxBDtail+2].StsLen);

               if( pRxBDPtr[rxBDtail].StsLen &0x00040000)
			   	printk(" RX descriptor CRC status error\n");
	       pkt_size = pRxBDPtr[rxBDtail].StsLen & (0x00000fff);   //Rx buffer_size
              
             pTxBDPtr[txBDtail].DataPtr = pRxBDPtr[rxBDtail].DataPtr;

            //rtl8139cp_verify_dump_desc(FD_RX_DESC);

          	
            if(txBDtail == (TX_DESC_NUM -1))
            {
                pTxBDPtr[txBDtail].StsLen =(0xf0000000+pkt_size);  //Own=1 EOS=1 
		  txBDtail=0;
            }
            else 
            {
                pTxBDPtr[txBDtail].StsLen =(0xb0000000+pkt_size);  //own=1 EOS=0 
		  txBDtail++;
            }                       

             
            //rtl8139cp_verify_dump_desc(FD_TX_DESC);

   
	   
            //FlushCache(); 
            //sys_dcache_flush_and_invalidate_all();
	     //udelay(200); 	 	 
            //rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | ETHER_IO_CMD_TXFNH);
            #if 1
            rtd_outl(ioaddr + ETHER_IO_CMD, rtd_inl(ioaddr + ETHER_IO_CMD) | 0x1/*0x000f170d*/); 
       	#endif
           	   	 
             //rtl8139cp_verify_dump_desc(FD_TX_DESC);
            //rtl8139cp_verify_dump_all_reg();
  
		 
            if(rxBDtail== (RX_DESC_NUM -1))
            {
                //pRxBDPtr[rxBDtail].StsLen =0xf0000800; 
                pRxBDPtr[rxBDtail].StsLen =0xc0000800; 
                rxBDtail=0;
            }
            else
            {
                //pRxBDPtr[rxBDtail].StsLen =0xb0000800;
                pRxBDPtr[rxBDtail].StsLen =0x80000800;
                rxBDtail++;
            } 

    
          
           

			
            #if 0
            //rtd_inl(0xa0000000);
			status = rtd_inw(ioaddr+ISR);
	    	    //printk("status = 0x%x \n",status);			   		   
		    if (status & 0x20)  	   	
		    	printk("error:RX desc. unavailable ,status = 0x%x \n",status); 
		    	
		    if (status & 0x04)  	
		    	printk("error:RX runt ,status = 0x%x \n",status); 	
		    	
		    if (status & 0x10) {
		    	printk("error:RX ovf ,status = 0x%x , reset\n",status);
		    }
		//rtd_outw(ioaddr+ISR,status);
		#endif
	
       } 
     #endif 


    }
}


int rtl8139cp_smartbit_test_export(void)
{
    rtl8139cp_smartbit_test();
    return 1;
}

int rtl8139cp_smartbit_test_tx_export(int num,int size,int mod)
{
    rtl8139cp_smartbit_test_tx(num,size,mod);
    return 1;
}

#endif






#if 0 //magellan setting 

void set_R_RC_manual(void)
{
	printk("set_R_RC_manual\n");
	//R,RC can be overwrite
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8013); //write reg27 = 0x8013
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0f08); //wrtie reg28 bit[15]=0,let R/RC can be written over
	udelay(100);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a46);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG21,0x0300);
	printk("page a46 reg21= %x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG21)); 
	udelay(100);
}

void uc_patch_for_ampcal(void)
{
	printk("uc_patch_for_ampcal\n");
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0b82);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0010);// reg16 bit4=1

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0b80);
	while (!(rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16)& _BIT6))
	{
		udelay(10);
	};

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8146);// Set patch key
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x2700);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb82e);// Set patch lock
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0001);

	//content start
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8421);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xaf84);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x2daf);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8433);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xaf84);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x36af);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8439);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0284);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x3caf);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x37ca);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xaf84);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x33af);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8436);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xaf84);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x39f8);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xf9fa);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xef69);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfafb);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x5cd7);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bfa);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd006);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x024d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x161f);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x66a6);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0003);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x03af);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x84db);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xef46);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6b02);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd100);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6202);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd100);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6502);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd100);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6802);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x34d7);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x834f);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd028);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x024d);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x16ee);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x832a);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4002);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x384e);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf83);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4fda);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x19db);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf83);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x57d8);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x19d9);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x1b54);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xac37);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x02ae);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x06bf);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x834f);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd819);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd9bf);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bfa);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xda19);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xdb1b);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x54ac);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x372a);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf8b);
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfadc);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x19dd);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6b02);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d5b);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe58b);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfcbf);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8562);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x024d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x5be5);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bfd);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6502);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d5b);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe58b);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfebf);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8568);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x024d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x5be5);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x16af);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8450);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe18b);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfcbf);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x856b);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x024d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x1def);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x010e);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x01e4);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8079);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe480);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x82e4);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x808b);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe480);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x94e4);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x809d);

	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe480);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xa6e4);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x80af);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x79ff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe580);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x22e1);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bfd);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6202);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x79ff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe580);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x25e1);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bfe);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6502);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x79ff);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe580);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x24e1);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x8bff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbf85);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x6802);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x4d1d);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x79ff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe580);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x23ff);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfeef);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x96fe);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfdfc);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0401);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff01);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff00);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0001);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xff00);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0070);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbcc4);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xf8bc);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xc470);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbcc8);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x20bc);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xc000);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb818);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x37c7);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb81a);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x02f3);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb81c);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x3c66);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb81e);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfff6);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0xb832);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0001);	
	//content end
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x0000);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);
	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0b82);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG23,0x0000);	// Clear patch lock

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8146);	// Clear patch key
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0000);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0b82);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG16,0x0000);	// reg16 bit4=0	
	
}

int uc_patch_for_Rcal(void) //for manual
{
	printk("uc_patch_for_Rcal\n");
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x819e);// Rout,R0
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xbec4);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81a0);// R1,R2
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xccd2);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81a2);// R3,R4
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xd8de);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81a4);// R5,R6
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xe4ec);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81a6);// R7,R8
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xf2f8);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81a8);// R9,R10
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0xfe04);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81aa);// R11,R12
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0c12);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81ac);// R13,R14
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x181e);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81ad);// R15
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x1e24);
	return 0;
}

void ampcal(void)
{
	printk("ampcal\n");
	UINT32 i = 0;
	// amp cal start
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a47); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0800);     // amp_cal_en

	i=0;
	while (!((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)&(0x3800))==0x3800))	// wait data=0x3800 then External +2.15V
	{
		i++;
		udelay(10);
	};
	printk("External +2.15V = %d\n",i); 

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0800);     // amp_cal_en	

	i=0;
	while (!((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)&(0x5800))==0x5800))	// wait data=0x5800 then External -2.15V
	{
		i++;		
		udelay(10);
	};
	printk("External -2.15V = %d\n",i); 

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0800);     // amp_cal_en

	i=0;
	while (!((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)&(0x1800))==0x1800))	// wait data=0x1800 then remove power
	{
		i++;
		udelay(10);
	};	
	printk("Remove power = %d\n",i); 

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0800);     // amp_cal_en
	
	// wait amp_cal done
	i = 5000;	
	 while ((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)& _BIT11) && (--i) )// r_cal_en=1'b0 (bit11)
	{
		udelay(50);
	};
	if (i<=0) 
    		printk("amp_cal fail \n"); 
	else
		printk("amp_cal i= %d\n",i);

	// amp cal start
//rtd_outl(0xb801605c,0x841f0a47);         
//ScalerTimer_DelayXms(100);
//rtd_outl(0xb801605c,0x84110800);        // amp_cal_en
//ScalerTimer_DelayXms(10);
//rtd_outl(0xb801605c,0x04110000);
//ScalerTimer_DelayXms(10);
//rtd_inl(0xb801605c);                    // wait data=0x3800 then External +2.15V
//ScalerTimer_DelayXms(10);

//rtd_outl(0xb801605c,0x84110800);        // after external +2.15V ready,write bit12->0
//ScalerTimer_DelayXms(10);

//rtd_outl(0xb801605c,0x04110000);
//ScalerTimer_DelayXms(10);
//rtd_inl(0xb801605c);                    // wait data=0x5800 then External -2.15V
//ScalerTimer_DelayXms(10);

//rtd_outl(0xb801605c,0x84110800);        // after external -2.15V ready,write bit12->0
//ScalerTimer_DelayXms(10);

//rtd_outl(0xb801605c,0x04110000);
//ScalerTimer_DelayXms(10);
//rtd_inl(0xb801605c);                    // wait data=0x1800 then remove power
//ScalerTimer_DelayXms(10);

//rtd_outl(0xb801605c,0x84110800);        // after external power remove,write bit12->0
//ScalerTimer_DelayXms(10);

// wait amp_cal done
//rtd_outl(0xb801605c,0x04110000);
//ScalerTimer_DelayXms(10);
//rtd_inl(0xb801605c);                    // amp_cal_en=1'b0 (bit11)
//ScalerTimer_DelayXms(10);

}

int getn_efuse_write(void)
{
	UINT32 i = 0,j =0;
	UINT16 temp_value = 0;
	//rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG0,value); 
    	printk("getn_efuse_write start \n"); 	
	rtl6330cp_verify_phy_init();
	ms_delay(60);//must >60ms
	set_R_RC_manual();
	//ms_delay(100);x
	uc_patch_for_ampcal();
	uc_patch_for_Rcal();
	//ms_delay(100);x
    	printk("0xb80381e4=%x\n",rtd_inl(0xb80381e4)); 
    	printk("0xb80381e8=%x\n",rtd_inl(0xb80381e8));

	rtd_outl(0xb8016284,0x80000080);	 // set gphy_key dummy = 32'h80000080
	udelay(10);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8198);	
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG28,0x0100);	// force rcal_agc_gain = 0	
	printk("8198=%x\n",rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28));
		
	PHY_STATUS();
	//------------------- r cal start--------------------//
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a47); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0400);   // r_cal_en

	// wait r_cal done	
	i = 500;	
	 while ((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)& _BIT10) && (--i) )// r_cal_en=1'b0 (bit10)
	{
		udelay(10);
	};
	if (i<=0) 
    		printk("r_cal fail \n"); 
	else
		printk("r_cal i= %d\n",i); 

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x81af);
	i = 500;		
	while ((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28)& _BIT8) && (--i) )
	{
		udelay(10);
	};	
	if (i<=0) 
    		printk("r_cal 01 fail \n"); 
	else
		printk("r_cal 01 i= %d\n",i); 

	//rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);  		// sram address = 0x8020 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28);	// read R_cal value
	printk("for R_default/RC_default  NOR value=%x \n", temp_value); 				//bit [3:0]=R NOR
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bce); 
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);// read R_cal value
	printk("R2 value=%x \n", temp_value);
	//------------------- r cal end--------------------//

	
	//------------------- rc cal start--------------------//
	PHY_STATUS();
	// rc cal start
	/*rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a47); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG17,0x0200);     // rc_cal_en

	// wait rc_cal done	
	i = 500;	
	 while ((rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG17)& _BIT9) && (--i) )// rc_cal_en=1'b0 (bit9)
	{
		udelay(10);
	};
	if (i<=0) 
    		printk("rc_cal fail \n"); 
	else
		printk("rc_cal i= %d\n",i); 

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43);
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);
	i = 500;		
	while ((!(rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28)& _BIT8)) && (--i) )//rc cali done
	{
		udelay(10);
	};	
	if (i<=0) 
    		printk("rc_cal 01 fail \n"); 
	else
		printk("rc_cal 01 i= %d\n",i); */

	//rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);  		// sram address = 0x8020 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28);	// read R_cal value
	printk("for R_default/RC_default  NOR value=%x \n", temp_value); 				//bit [15:12]=RC NOR
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcd); 
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG22);	// read RC_cal value
	printk("RC value=%x \n", temp_value);	
	//------------------- rc cal end--------------------//
		 
	PHY_STATUS();
	ampcal();
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8022);  		// sram address = 0x8022 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28); 	// read amp_cal high byte value[23:16]
	printk("amp_cal high byte NOR value=%x \n", temp_value);						//bit[10:8] amp_dn bit [7:0]amp_dn_fine [1:0]port A ...[7:6]port D

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8024);  		// sram address = 0x8024 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28); 	// read amp_cal low byte value[15:0]
	printk("amp_cal low byte NOR value=%x \n", temp_value);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);
	printk("amp_dn value=%x \n", temp_value);									//bit [2:0] amp_dn

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG20);
	printk("amp_cal high byte value=%x \n", temp_value);							//amp_dn_fine bit [1:0]:A, [3:2]:B, [5:4]:C, [7:6]:D

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG18);	// gdac_ip_dn bit[9:8] :A, [11:10]:B, [13:12]:C, [15:14]:D
	printk("amp_cal low byte value=%x \n", temp_value);							// gdac_ip_up bit[1:0] :A, [3:2] : B, [5:4]: C, [7:6]: D

PHY_STATUS();

#if 1
	////--- gmac read cal data --- ////
	// R cal
#if 1
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);  // sram address = 0x8020 rega 27

	rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016280,0x0000000f);        // bit number 3:0
#else
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000); 	

	rtd_outl(0xb8016274,0x00000000);        // auto read reg 28 
	rtd_outl(0xb8016278,0x00000000);        // auto read reg 28 
	rtd_outl(0xb801627c,0x00000000);        // auto read reg 28 
	rtd_outl(0xb8016280,0x000000f0);        // bit number 3:0
#endif


	rtd_outl(0xb8016270,0x00000101);        // r_cal_en , phy_addr=5'h01
	udelay(10000);
	rtd_outl(0xb8016270,0x00000001);        // turn off r_cal_en 

	udelay(10000);
	//RC cal
#if 0
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);  // sram address = 0x8020 rega 27

	rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016280,0x0000f000);        // bit number 15:12
#else//amp_dn
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8022);  // sram address = 0x8020 rega 27

	rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016280,0x00000f00);        // bit number 10:8
#endif
	rtd_outl(0xb8016270,0x00000201);        // rc_cal_en , phy_addr=5'h01
	udelay(10000);
	rtd_outl(0xb8016270,0x00000001);        // turn off rc_cal_en 

	udelay(10000);
	//amp high byte cal 23:16
#if 1
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8022);  // sram address = 0x8022 rega 27

	rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
	//rtd_outl(0xb8016280,0xfffff000);        // bit number
#else
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);	

	rtd_outl(0xb8016274,0x00000000);        // auto read reg 28 
	rtd_outl(0xb8016278,0x00000000);        // auto read reg 28 
	rtd_outl(0xb801627c,0x00000000);        // auto read reg 28 
#endif

	rtd_outl(0xb8016270,0x00000801);        // amp_h_b_cal_en , phy_addr=5'h01
	udelay(10000);
	rtd_outl(0xb8016270,0x00000001);        // turn off amp_h_b_en 

	udelay(10000);
	//amp low byte cal 15:0
#if 1
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8024);  // sram address = 0x8024 rega 27
	
	rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
	rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
	//rtd_outl(0xb8016280,0xfffff000);        // bit number
#else
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0000);	

	rtd_outl(0xb8016274,0x00000000);        // auto read reg 28 
	rtd_outl(0xb8016278,0x00000000);        // auto read reg 28 
	rtd_outl(0xb801627c,0x00000000);        // auto read reg 28 
#endif
	

	rtd_outl(0xb8016270,0x00000401);        // amp_l_b_en , gphy_key_req
#if 0
	/*i = 50000;	
	 while (!(rtd_inl(0xb8016270)&_BIT30) && (--i) )
	{
		udelay(10);
	};*/	 

	//udelay(1);
	j= 50000;	
	 while (!(rtd_inl(0xb8016270)&_BIT31) && (--j) )
	{
		udelay(10);
	};
#else
	//udelay(40);fail
	//udelay(45);fail&ok
	//udelay(50);ok
	udelay(60);//ok
	//udelay(65);ok
	//udelay(70);fail
#endif
	rtd_outl(0xb8016270,0x00000001);        // turn off amp_l_b_en 

/*	if (i<=0) 
    		printk("gphy_key fail\n"); 
	else
		printk("gphy_key i= %d\n",i); 
*/
	if (j<=0) 
    		printk("gphy_key fail\n"); 
	else
		printk("gphy_key j= %d\n",j); 

	ms_delay(1000);

    	printk("0xb80381e4=%x\n",rtd_inl(0xb80381e4)); 
    	printk("0xb80381e8=%x\n",rtd_inl(0xb80381e8)); 		

#endif
PHY_STATUS();
    	printk("getn_efuse_write end \n"); 
	return 1;
	
}



void getn_load_efusedata2dout(void)
{


	UINT32 temp,temp1,temp2;
	UINT32 R_cal_value,RC_cal_value;
	UINT32 ib_up,ib_dn,amp_dn_fine,amp_dn;

	//amp_cal value[23:16]= amp_dn_fine [1:0]port A ...[7:6]port D page bcc/reg20 [7:0]
	//amp_cal value[15:8]= gdac_ib_dn page bcc/reg18 [15:8]
	//amp_cal value[7:0]= gdac_ib_up page bcc/reg18 [7:0]
printk("0xb80381e4=%x\n",rtd_inl(0xb80381e4)); 
printk("0xb80381e8=%x\n",rtd_inl(0xb80381e8)); 		
	temp1 = rtd_inl(0xb80381e4);
	temp2 = rtd_inl(0xb80381e8);

	if ((temp1&_BIT31)&&(temp2&_BIT31)){//efuse have burned
		//R,RC can be overwrite
		rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
		ms_delay(10);
		rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
		ms_delay(1);
		rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
		ms_delay(1);
		
		R_cal_value = ((temp2>>15)&0xf);
		//RC_cal_value = ((temp2>>19)&0xf);
		amp_dn =  ((temp2>>19)&0x7);
		amp_dn_fine = (temp1&0xff);//amp_cal value[23:16]
		ib_dn = ((temp1>>17)&0xff);//amp_cal value[15:8]
		ib_up = ((temp1>>9)&0xff);//amp_cal value[7:0]
		printk("R_cal_NOR value =%x\n",R_cal_value);
		//printk("RC_cal_NOR value =%x\n",RC_cal_value);	
		printk("amp_dn_NOR =%x\n",amp_dn);			
		printk("amp_dn_fine_NOR =%x\n",amp_dn_fine);	
		printk("ib_dn_NOR =%x\n",ib_dn);	
		printk("ib_up_NOR =%x\n",ib_up);			
		//write DOUT data
		rtd_outl(0xb801605c,0x841f0a46);// change Page to a46
		ms_delay(10);
		temp = (((ib_dn&0x7f)<<9)|ib_up);
		rtd_outl(0xb801605c,(0x84100100)|temp);// bit[15:9]=Fuse_DOUT[14:8](amp_cal value[14:8]),bit[7:0]=Fuse_DOUT[7:0](amp_cal value[7:0])
		ms_delay(1);
		rtd_outl(0xb801605c,0x04100000);
		ms_delay(1);
		//printk("reg 16 =%x\n",rtd_inl(0xb801605c));
		ms_delay(1);
		temp = (amp_dn_fine<<1)|(ib_dn>>7);
		rtd_outl(0xb801605c,0x8411fe00|temp);// bit[8:1]=Fuse_DOUT[24:17](amp_cal value[23:16]),bit[0]=Fuse_DOUT[16](amp_cal value[15])
		ms_delay(1);
		rtd_outl(0xb801605c,0x04110000);
		ms_delay(1);
		//printk("reg 17 =%x\n",rtd_inl(0xb801605c));
		ms_delay(1);
		temp = ((R_cal_value&0x1)<<15);
		rtd_outl(0xb801605c,0x84127fff|temp);// bit[15]=Fuse_DOUT[47](R value [0])
		ms_delay(1);
		rtd_outl(0xb801605c,0x04120000);
		ms_delay(1);
		//printk("reg 18 =%x\n",rtd_inl(0xb801605c)); 
		ms_delay(1);
		//temp = (RC_cal_value<<3)|(R_cal_value>>1);
		//rtd_outl(0xb801605c,0x8413ff80|temp);// bit[6:3]=Fuse_DOUT[54:51](RC value),bit[2:0]=Fuse_DOUT[50:48](R value [3:1])
		temp = (R_cal_value>>1);
		rtd_outl(0xb801605c,0x8413fff8|temp);// bit[6:3]=Fuse_DOUT[54:51](RC value),bit[2:0]=Fuse_DOUT[50:48](R value [3:1])
		ms_delay(1);
		rtd_outl(0xb801605c,0x04130000);
		ms_delay(1);
		//printk("reg 19 =%x\n",rtd_inl(0xb801605c)); 	
	}
	else{
		rtd_outl(0xb801605c,0x841f0a46);// change Page to a46
		ms_delay(1);
		ib_up =  0xaa;
		rtd_outl(0xb801605c,(0x8410ff00|ib_up));// bit[7:0]=Fuse_DOUT[7:0](amp_cal value[7:0])
		ms_delay(1);
	}


}


void GreenTable_Modify(void){
	UINT32 temp,temp1,temp2;
	UINT32 amp_dn;

    	printk("GreenTable_Modify start \n"); 	

	//adjust common mode voltage
	rtd_outl(0xb801605c,0x841f0bc0);// change Page to bc0
	ms_delay(1);
	rtd_outl(0xb801605c,0x84170001);// bit[1:0]:common mode voltage => 0x2->0x1
	ms_delay(1);

	temp1 = rtd_inl(0xb80381e4);
	temp2 = rtd_inl(0xb80381e8);

	if ((temp1&_BIT31)&&(temp2&_BIT31)){//efuse have burned
		amp_dn = ((temp2>>19)&0x7);//from efuse [53:51]
		amp_dn = (amp_dn^0x7);
		amp_dn = (amp_dn<<9);
		printk("efuse had been written\n");
	}else{
		amp_dn = (0x2<<9); // bit[2:0]:amp_dn => 00:100% 01:90% 10:80%
		printk("efuse had NOT been written\n");
	}
	
	//printk("amp_dn = %x\n",(amp_dn>>9));
	//grntbl_0_03
	rtd_outl(0xb801605c,0x841b8079);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_0_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_1_03
	rtd_outl(0xb801605c,0x841b8082);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_1_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_2_03
	rtd_outl(0xb801605c,0x841b808B);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_2_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_3_03
	rtd_outl(0xb801605c,0x841b8094);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_3_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_4_03
	rtd_outl(0xb801605c,0x841b809d);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_4_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_5_03
	rtd_outl(0xb801605c,0x841b80A6);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_5_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);
	
	//grntbl_6_03
	rtd_outl(0xb801605c,0x841b80AF);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	temp = ((temp&0xf1ff)|amp_dn);		//amp_dn = bit[11:9]
	rtd_outl(0xb801605c,0x841c0000|temp);
	ms_delay(1);
	rtd_outl(0xb801605c,0x041c0000);
	ms_delay(1);		
	//printk("grntbl_6_03 =%x\n",rtd_inl(0xb801605c)); 
	ms_delay(1);


	ms_delay(2000);

	rtd_outl(0xb801605c,0x841f0bcc);// change Page to bcc
	ms_delay(1);
	rtd_outl(0xb801605c,0x04100000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	ms_delay(1);
	printk(" amp_dn = %x\n",temp&0x7); 

	rtd_outl(0xb801605c,0x04140000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	ms_delay(1);	
	printk(" amp_dn_fine = %x\n",temp&0xff);
	
	rtd_outl(0xb801605c,0x04120000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	ms_delay(1);	
	printk(" ib_up = %x\n",temp&0xff);//bit[1:0]:up  => 00:100% 01:102.5% 10:105%
	printk(" ib_dn = %x\n",(temp>>8)&0xff);	

	rtd_outl(0xb801605c,0x841f0bce);// change Page to bce
	ms_delay(1);
	rtd_outl(0xb801605c,0x04100000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	ms_delay(1);	
	printk(" R = %x\n",temp&0xffff);	 

	rtd_outl(0xb801605c,0x841f0bcd);// change Page to bcd
	ms_delay(1);
	rtd_outl(0xb801605c,0x04160000);
	ms_delay(1);
	temp = rtd_inl(0xb801605c);
	ms_delay(1);	
	printk(" RC = %x\n",temp&0xffff);	

}

void test1(void){
printk("test1 start\n");
GETN_CRT();

//GPHY////////set_fuse_rdy start
rtd_outl(0xb801605c,0x841f0a46);// change Page to a46
ms_delay(1);
rtd_outl(0xb801605c,0x84140003);// set fuse_rdy = 1 , set ext_ini_done = 1, to skip ext_ini
ms_delay(1);
////////set_fuse_rdy end

////CM_voltage_adjust start
rtd_outl(0xb801605c,0x841f0bc0);// change Page to bc0
ms_delay(1);
rtd_outl(0xb801605c,0x84170001);// bit[1:0]:common mode voltage => 0x2->0x1
ms_delay(1);
////CM_voltage_adjust end

//R,RC can be overwrite
rtd_outl(0xb801605c,0x841f0a42);// change Page to a42
ms_delay(1);
rtd_outl(0xb801605c,0x841b8013);//write reg27 = 0x8013
ms_delay(1);
rtd_outl(0xb801605c,0x841c0f08);//wrtie reg28 bit[15]=0,let R/RC can be written over
ms_delay(1);

//#include "uc_patch_for_ampcal.tbl"
////uc_patch_for_Rcal start
rtd_outl(0xb801605c,0x841f0000);// change Page to 0
ms_delay(1);
rtd_outl(0xb801605c,0x841b819e);// Rout,R0
ms_delay(1);
rtd_outl(0xb801605c,0x841cbec4);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81a0);// R1,R2
ms_delay(1);
rtd_outl(0xb801605c,0x841cccd2);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81a2);// R3,R4
ms_delay(1);
rtd_outl(0xb801605c,0x841cd8de);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81a4);// R5,R6
ms_delay(1);
rtd_outl(0xb801605c,0x841ce4ec);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81a6);// R7,R8
ms_delay(1);
rtd_outl(0xb801605c,0x841cf2f8);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81a8);// R9,R10
ms_delay(1);
rtd_outl(0xb801605c,0x841cfe04);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81aa);// R11,R12
ms_delay(1);
rtd_outl(0xb801605c,0x841c0c12);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81ac);// R13,R14
ms_delay(1);
rtd_outl(0xb801605c,0x841c181e);
ms_delay(1);
rtd_outl(0xb801605c,0x841b81ad);// R15
ms_delay(1);
rtd_outl(0xb801605c,0x841c1e24);
ms_delay(1);
////uc_patch_for_Rcal end

// r cal start
rtd_outl(0xb801605c,0x841f0000);// change Page to 0
ms_delay(1);
rtd_outl(0xb801605c,0x841b8198);// 
ms_delay(1);
rtd_outl(0xb801605c,0x841c0100);// force rcal_agc_gain = 0
ms_delay(1);
rtd_outl(0xb801605c,0x841f0a47);         
ms_delay(1);
rtd_outl(0xb801605c,0x84110400);        // r_cal_en
ms_delay(1);// wait r_cal done
ms_delay(1);                //600us

// amp cal start
rtd_outl(0xb801605c,0x841f0a47);         
ms_delay(1);
rtd_outl(0xb801605c,0x84110800);        // amp_cal_en
ms_delay(1);
// set amp_dn = 0x2
rtd_outl(0xb801605c,0x841f0bcc);
ms_delay(1);
rtd_outl(0xb801605c,0x8410a40a);        // reg16
ms_delay(1);                                        // bit [2:0] amp_dn// delay 40us  
// wait data=0x3800 then External (cmvolt+swing/2)
ms_delay(1);                // -> (1.7+2.15/2) MDI_P約為2.8V,(1.7-2.15/2) MDI_N約為0.65V
// input voltage 1
// input voltage 1
ms_delay(5);
rtd_outl(0xb801605c,0x841f0a47);         
ms_delay(1);
rtd_outl(0xb801605c,0x84110800);        // after 2.8V/0.65V ready,write bit12->0
ms_delay(1);                                        // wait data=0x5800 then 
ms_delay(10);               // -> (1.7-2.15/2) MDI_P約為0.65V,(1.7+2.15/2) MDI_N約為2.8V
// input voltage 2
// input voltage 2
ms_delay(5);
rtd_outl(0xb801605c,0x84110800);        // after 0.65V/2.8V ready,write bit12->0
ms_delay(1);                                        // wait data=0x1800 then remove power
ms_delay(10);
// remove voltage 
// remove voltage 
ms_delay(5);
rtd_outl(0xb801605c,0x84110800);        // after external power remove,write bit12->0
ms_delay(1);// wait amp_cal done                                        // amp_cal_en=1'b0 (bit11)
ms_delay(50);

rtd_outl(0xb801605c,0x04110000);
ms_delay(1);
printk("amp_cal done=%x\n",rtd_inl(0xb801605c));
ms_delay(1);

printk("0xb80381e4=%x\n",rtd_inl(0xb80381e4)); 
printk("0xb80381e8=%x\n",rtd_inl(0xb80381e8)); 	


////--- gmac read cal data --- ////
rtd_outl(0xb8016284,0x80000080);	 // set gphy_key dummy = 32'h80000080
// R cal
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(1);
rtd_outl(0xb801605c,0x841b8020);        // sram address = 0x8020 rega 27
ms_delay(1);
rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016280,0x0000000f);        // bit number 3:0
rtd_outl(0xb8016270,0x00000101);        // r_cal_en , phy_addr=5'h01// delay 60x4x400ns=96us                          
ms_delay(1);
rtd_outl(0xb8016270,0x00000001);        // turn off r_cal_en 
ms_delay(1);

//must be after R cal 
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(1);
rtd_outl(0xb801605c,0x841b8021);        // set amp_dn_NOR = 0x5
ms_delay(1);
rtd_outl(0xb801605c,0x841c0005);
ms_delay(1);

//amp_dn
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(1);
rtd_outl(0xb801605c,0x841b8022);        // sram address = 0x8022 rega 27
ms_delay(1);
rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016280,0x00000f00);        // bit number 10:8
rtd_outl(0xb8016270,0x00000201);        // amp_dn_cal_en , phy_addr=5'h01
// delay 60x4x400ns=96us                          
ms_delay(1);
rtd_outl(0xb8016270,0x00000001);        // turn off amp_dn_cal_en 
ms_delay(1);

//amp high byte cal 23:16
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(1);
rtd_outl(0xb801605c,0x841b8022);        // sram address = 0x8022 rega 27
ms_delay(1);
rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
//rtd_outl(0xb8016280,0xfffff000);        // bit number
rtd_outl(0xb8016270,0x00000801);        // amp_h_b_cal_en , phy_addr=5'h01// delay 60x4x400ns=96us    
ms_delay(1);
rtd_outl(0xb8016270,0x00000001);        // turn off amp_h_b_en 
ms_delay(1);

//amp low byte cal 15:0
rtd_outl(0xb801605c,0x841f0a43);
ms_delay(1);
rtd_outl(0xb801605c,0x841b8024);        // sram address = 0x8024 rega 27
ms_delay(1);
rtd_outl(0xb8016274,0x0000001c);        // auto read reg 28 
rtd_outl(0xb8016278,0x0000001c);        // auto read reg 28 
rtd_outl(0xb801627c,0x0000001c);        // auto read reg 28 
//rtd_outl(0xb8016280,0xfffff000);        // bit number
rtd_outl(0xb8016270,0x00000401);        // amp_l_b_en , gphy_key_req// delay 60us                          
udelay(60);              //wait bit31->1 or =60us;
rtd_outl(0xb8016270,0x00000001);        // turn off amp_l_b_en 


ms_delay(10);

	UINT32 temp_value=0;
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8020);  		// sram address = 0x8020 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28);	// read R_cal value
	printk("for R_default/RC_default  NOR value=%x \n", temp_value); 				//bit [3:0]=R NOR
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bce); 
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);// read R_cal value
	printk("R2 value=%x \n", temp_value);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8022);  		// sram address = 0x8022 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28); 	// read amp_cal high byte value[23:16]
	printk("amp_cal high byte NOR value=%x \n", temp_value);						//bit[10:8] amp_dn bit [7:0]amp_dn_fine [1:0]port A ...[7:6]port D

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0a43); 
	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG27,0x8024);  		// sram address = 0x8024 rega 27
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG28); 	// read amp_cal low byte value[15:0]
	printk("amp_cal low byte NOR value=%x \n", temp_value);

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG16);
	printk("amp_dn value=%x \n", temp_value);									//bit [2:0] amp_dn

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG20);
	printk("amp_cal high byte value=%x \n", temp_value);							//amp_dn_fine bit [1:0]:A, [3:2]:B, [5:4]:C, [7:6]:D

	rtl6330cp_verify_mdio_write(RTD2885_LAN_PHY_ID,MII_REG31,0x0bcc); 	
	temp_value = rtl6330cp_verify_mdio_read(RTD2885_LAN_PHY_ID,MII_REG18);	// gdac_ip_dn bit[9:8] :A, [11:10]:B, [13:12]:C, [15:14]:D
	printk("amp_cal low byte value=%x \n", temp_value);							// gdac_ip_up bit[1:0] :A, [3:2] : B, [5:4]: C, [7:6]: D



printk("0xb80381e4=%x\n",rtd_inl(0xb80381e4)); 
printk("0xb80381e8=%x\n",rtd_inl(0xb80381e8)); 	

}
#endif


