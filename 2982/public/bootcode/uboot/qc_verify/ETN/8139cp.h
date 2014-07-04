/*============================================================*
 * Copyright (c)      Realtek Semiconductor Corporation, 2007 *
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/
/**
 * @file 8139cp.h
 * RTL8139CP H/W register , Tx/Rx descriptor define.
 * 
 * @author Moya Yu
 * @date 2007/3/19
 * @version 0.1
 */
 
#ifndef __8139CP_H__
#define __8139CP_H__

// #define CONFIG_FPGA 			1

#define RTD2885_SIC_M_GIR3		(0xb800300C)
#define RTD2885_LAN_IRQ(irq)	((irq & 0xf)<<12)

#define RTD2885_SIC_M_GIE0		(0xb8003020)
#define SIC_M_GIE0_NIC_IE		(1<<3)

#define RTD2885_LAN_BASE	(0xb8016000)
#define RTD2885_LAN_BASE2	(0xb8016800)

#define bus_to_phys(a)		(a)

//#define RTD2885_LAN_PHY_ID	       	(0x1)
#define RTD2885_LAN_PHY1_ID	      	(0x1)
#define RTD2885_LAN_PHY2_ID		(0x1)


enum {
	/* NIC register offsets */
	IDR0 = 0,			/* Ethernet ID */
	IDR1 = 0x1,			/* Ethernet ID */
	IDR2 = 0x2,			/* Ethernet ID */
	IDR3 = 0x3,			/* Ethernet ID */
	IDR4 = 0x4,			/* Ethernet ID */
	IDR5 = 0x5,			/* Ethernet ID */
	MAR0 = 0x8,			/* Multicast register */
	MAR1 = 0x9,
	MAR2 = 0xa,
	MAR3 = 0xb,
	MAR4 = 0xc,
	MAR5 = 0xd,
	MAR6 = 0xe,
	MAR7 = 0xf,
	TXOKCNT=0x10,
	RXOKCNT=0x12,
	TXERR = 0x14,
	RXERR = 0x16,
	MISSPKT = 0x18,
	FAE=0x1A,
	TX1COL = 0x1c,
	TXMCOL=0x1e,
	RXOKPHY=0x20,
	RXOKBRD=0x22,
	RXOKMUL=0x24,
	TXABT=0x26,
	TXUNDRN=0x28,
	TRSR=0x34,
	CMD=0x3B,
	IMR=0x3C,
	ISR=0x3E,
	TCR=0x40,
	RCR=0x44,
	/* Media Status Register. */
	MSR=0x58,
	MIIAR=0x5C,	
    /* RTL, Fox, 080326 */
	RXFIFOPROTECT=0x80,
    /* End RTL, Fox, 080326 */	
	// CPU Interface Registers
	TxFDP1=0x100,
	TxCDO1=0x104,
	TXCPO1=0x108,
	TXPSA1=0x10A,
	TXCPA1=0x10C,
	LastTxCDO1=0x110,
	TXPAGECNT1=0x112,
	Tx1ScratchDes=0x150,
	TxFDP2=0x180,
	TxCDO2=0x184,
	TXCPO2=0x188,
	TXPSA2=0x18A,
	TXCPA2=0x18C,
	LASTTXCDO2=0x190,
	TXPAGECNT2=0x192,
	Tx2ScratchDes=0x1A0,
	RxFDP=0x1F0,
	RxCDO=0x1F4,
	RxRingSize=0x1F6,
	RxCPO=0x1F8,
	RxPSA=0x1FA,
	RxCPA=0x1FC,
	RXPLEN=0x200,
	LASTRXCDO=0x1402,
	RXPFDP=0x204,
	RxPageCNT=0x208,
	RxScratchDes=0x210,
	EthrntRxCPU_Des_Num  = 0x230,
	EthrntRxCPU_Des_Wrap = 0x231,
	#if 1  //Giga Eth
	Rx_Pse_Des_Thres = 	0x231,
	#else
	Rx_Pse_Des_Thres = 	0x232,
	#endif
	ETHER_IO_CMD = 0x234,

	// Add for Rx FIFO overflow error handle.
	RX_FIFO_PROTECT = 0x80,
};

#define RX_FIFO_PROTECT_EN	(1<<6)
/* RTL, Fox, 080326 */
enum {
	RX_FIFO_BIST = (1<<0),
	RX_FIFO_BIST_RESULT = (1<<2),
};
/* End RTL, Fox, 080326 */	
enum {
	RX_IntNum_Shift = 0x8,             /// ????
	TX_OWN = (1<<5),
	RX_OWN = (1<<4),
	MII_RE = (1<<3),
	MII_TE = (1<<2),
	TX_FNL = (1<1),
	TX_FNH = (1),
	/*TX_START= MII_RE | MII_TE | TX_FNL | TX_FNH,
	TX_START = 0x8113c,*/
	RXMII = MII_RE,
	TXMII= MII_TE,
};

// CMD register.
enum {
	CMD_RST		 = (1<<0),
	CMD_RxChkSum = (1<<1),
	CMD_RxVLAN 	 = (1<<2),	
};

// IMR register. (1:enable interrupt)
enum {
	IMR_ROK      	= (1<<0),
	IMR_RER_RUNT 	= (1<<2),
	IMR_RER_OVF  	= (1<<4),
	IMR_RDU  	 	= (1<<5),
	IMR_TOK_TI   	= (1<<6),
	IMR_TER   	 	= (1<<7),
	IMR_PUN_LinkChg	= (1<<8),
	IMR_TDU   		= (1<<9),
	IMR_SWInt   	= (1<<10),
	/* 11:15 bits are reserved. */
	IMR_DISABLE_ALL_INTR = (0x0),	
};

// ISR register.
enum {
	ISR_ROK      	= (1<<0),
	ISR_RER_RUNT 	= (1<<2),
	ISR_RER_OVF  	= (1<<4),
	ISR_RDU  	 	= (1<<5),
	ISR_TOK_TI   	= (1<<6),
	ISR_TER   	 	= (1<<7),
	ISR_PUN_LinkChg	= (1<<8),
	ISR_TDU   		= (1<<9),
	ISR_SWInt   	= (1<<10),	
	ISR_CLEAR_ALL_INTR = (0x7ff),
};

// RCR register.
enum {
	RCR_AAP     = (1<<0),
	RCR_APM 	= (1<<1),
	RCR_AM  	= (1<<2),
	RCR_AB  	= (1<<3),
	RCR_AR   	= (1<<4),
	RCR_AER   	= (1<<5),
	RCR_NoErrAccept = (RCR_AB|RCR_AM|RCR_APM/*|RCR_AAP*/),
	RCR_ALL		= (RCR_AER|RCR_AR|RCR_AB|RCR_AM|RCR_APM|RCR_AAP),
};

// RxRingSize register.
enum {
	RxRingSize_16 = (0x0),  /* b00 : 16 descriptors. */
	RxRingSize_32 = (0x1),	/* b01 : 32 descriptors. */
	RxRingSize_64 = (0x2),  /* b10 : 64 descriptors. */
};


enum {
	PHY_LOOP_BACK = 0x0,
	MAC_LOOP_BACK,
	NORMAL,
};

/* TCR register. */
enum {
	TCR_IFG_B011 			= 0x3,
	TCR_LBK1_LBK0_NORMAL 	= 0x0,
	TCR_LBK1_LBK0_LOOPBACK 	= 0x3, 
};

#define TCR_IFG(x)			((x&0x7)<<10)
#define TCR_LBK1_LBK0(x)	((x&0x3)<<8)


/* TRSR register. */
enum {
	TRSR_TX_OK	 			= (1<<3),
	
};


/* MSR register. */
enum {
	MSR_RXPF 		= (1<<0),
	MSR_TXPF 		= (1<<1),
	MSR_LINKB 		= (1<<2),
	MSR_SPEED_10 	= (1<<3), 	
	MSR_TXFCE 		= (1<<5),
	MSR_RXFCE 		= (1<<6),	
};

// ETHER_IO_CMD register.
enum {
	ETHER_IO_CMD_TXFNH   		 		= (1<<0),
	ETHER_IO_CMD_TXFNL 	 		 		= (1<<1),
	ETHER_IO_CMD_TE  	 		 		= (1<<2),	
	ETHER_IO_CMD_RE  	 		 		= (1<<3),	
	ETHER_IO_CMD_RxDesOwnCh  	 		= (1<<4),
	ETHER_IO_CMD_TxDesOwnCh  	 		= (1<<5),
	ETHER_IO_CMD_EthernetRxPageOffset	= (1<<6),	
};


#define ETHER_IO_CMD_RxIntMitigation(x)			((x & 7)<<8)
#define ETHER_IO_CMD_RXFTH1_0(x)				((x & 3)<<11)
#define ETHER_IO_CMD_RXPktTimer(x)				((x & 7)<<13)
//#define ETHER_IO_CMD_MXRXDMA2_1_0(x)				((x & 7)<<16)

#define ETHER_IO_CMD_TxIntMitigation(x)			((x & 7)<<16)
#define ETHER_IO_CMD_TXTH1_0(x)					((x & 3)<<19)
//#define ETHER_IO_CMD_MXTXDMA2_1_0(x)			((x & 7)<<24)





enum {
	GETHER_IO_CMD_TXFN1   		 		= (1<<0),
	GETHER_IO_CMD_TXFN2 	 		 		= (1<<1),
	GETHER_IO_CMD_TE  	 		 		= (1<<4),	
	GETHER_IO_CMD_RE  	 		 		= (1<<5),
	GETHER_IO_CMD_EARLY_TX				= (1<<28),
	GETHER_IO_CMD_SHORTDES_FORMAT         = (1<<30),
};




#define GETHER_IO_CMD_RxIntMitigation(x)			((x & 7)<<8)
//#define GETHER_IO_CMD_RXFTH1_0(x)				((x & 3)<<11)
#define GETHER_IO_CMD_RXPktTimer(x)				((x & 7)<<13)
//#define ETHER_IO_CMD_MXRXDMA2_1_0(x)				((x & 7)<<16)

#define GETHER_IO_CMD_TxIntMitigation(x)			((x & 7)<<16)
#define GETHER_IO_CMD_TXTH1_0(x)					((x & 3)<<19)




/* MIIAR register. */
enum {
	MIIAR_Flag_Write 	= (1<<31),	
};

#define MIIAR_PHYAddress(x) 		((x&0x1f)<<26)
#define MIIAR_RegAddr4_0(x) 		((x&0x1f)<<16)
#define MIIAR_Data15_0(x) 			(x&0xffff)

/* PHY register. */
enum {
	MII_REG0 	= 0,	
	MII_REG1 	= 1,
	MII_REG2 	= 2,
	MII_REG3 	= 3,
	MII_REG4 	= 4,
	MII_REG5 	= 5,
	MII_REG6 	= 6,
	MII_REG7 	= 7,
	MII_REG8 	= 8,
	MII_REG9 	= 9,
			
	MII_REG16 	= 16,
	//DSP register.
	MII_REG17	= 17,
	MII_REG18	= 18,
	MII_REG19	= 19,
	MII_REG20	= 20,
	MII_REG21	= 21,	
	MII_REG22	= 22,	
	MII_REG23	= 23,
	MII_REG24	= 24,
	MII_REG25	= 25,
	MII_REG26	= 26,
	MII_REG27	= 27,
	MII_REG28	= 28,
	MII_REG29	= 29,
	MII_REG30       = 30,
	MII_REG31       = 31,
};


/* PHY : MII_REG0 register. */
enum {
	MII_REG0_Reset							= (1<<15),
	MII_REG0_Loopback						= (1<<14),
	MII_REG0_Speed_Select_100M			= (1<<13),	
	MII_REG0_Auto_Negotiation_Enable 		= (1<<12),
	MII_REG0_Power_Down 					= (1<<11),
	MII_REG0_Isolate	 					= (1<<10),
	MII_REG0_Restart_Auto_Negotiation	 	= (1<<9),
	MII_REG0_Duplex_Mode	 				= (1<<8),
};




/* GPHY : GMII_REG0 register. */
enum {
	GMII_REG0_Reset							= (1<<15),
	GMII_REG0_Loopback						= (1<<14),
	GMII_REG0_Speed_0						= (1<<13),
	GMII_REG0_Auto_Negotiation_Enable 		= (1<<12),
	GMII_REG0_Power_Down 					= (1<<11),
	GMII_REG0_Isolate	 					= (1<<10),
	GMII_REG0_Restart_Auto_Negotiation	 	= (1<<9),
	GMII_REG0_Duplex_Mode	 				= (1<<8),
	GMII_REG0_Speed_1						= (1<<6),
};


/* PHY : MII_REG1 register. */
enum {
	MII_REG1_LINK_OK		 				= (1<<2),
	MII_REG1_AUTO_NEG_COMPLETE				= (1<<5),
};

/* PHY : MII_REG4 register. */
enum {
	MII_REG4_100BASE_TX_FD					= (1<<8),
	MII_REG4_100BASE_TX  					= (1<<7),
	MII_REG4_10BASE_TX_FD  					= (1<<6),
	MII_REG4_10BASE_TX  					= (1<<5),
};	

enum {
	PHY_1000M = 2,
	PHY_100M = 1,
	PHY_10M = 0,
};

enum {
	PHY_Full_Duplex = 1,
	PHY_Half_Duplex = 0,
};

enum {
	PHY_LBK_Enable = 1,
	PHY_LBK_Disable = 0,
};

#define OWN_BIT					(1<<31) //0x80000000
#define EOR_BIT					(1<<30) // 0x40000000
#define FS_BIT					(1<<29) // 0x20000000
#define LS_BIT					(1<<28) // 0x10000000


enum {
	TX_DESC_CMD_OWN  = (1<<31),
	TX_DESC_CMD_EOR  = (1<<30),
	TX_DESC_CMD_FS   = (1<<29),
	TX_DESC_CMD_LS   = (1<<28),
	TX_DESC_CMD_CRC  = (1<<23),	
};

#define TX_DESC_DATA_LEN_MASK		(0xfff)
#define TX_DESC_DATA_LEN(x)			(x & TX_DESC_DATA_LEN_MASK)

enum {
	TX_DESC_STATS_UNF  = (1<<25),
	TX_DESC_STATS_TES  = (1<<23),
	TX_DESC_STATS_OWC  = (1<<22),
	TX_DESC_STATS_LNKF = (1<<21),
	TX_DESC_STATS_EXC  = (1<<20),	
};


#define TX_DESC_STATS_CC(x)  ((x>>16) & 0xf)

enum {
	RX_DESC_STATS_FAE     = (1<<27),
	RX_DESC_STATS_MAR     = (1<<26),
	RX_DESC_STATS_PAM     = (1<<25),
	RX_DESC_STATS_BAR     = (1<<24),
	RX_DESC_STATS_PPPOE   = (1<<23),	
	RX_DESC_STATS_E802_3  = (1<<22),
	RX_DESC_STATS_RWT     = (1<<21),
	RX_DESC_STATS_RES     = (1<<20),
	RX_DESC_STATS_RUNT    = (1<<19),
	RX_DESC_STATS_CRC     = (1<<18),
	RX_DESC_STATS_IPF     = (1<<15),
	RX_DESC_STATS_UDPF    = (1<<14),
	RX_DESC_STATS_TCPF    = (1<<13),
};

#define RX_DESC_STATS_PID(x)  ((x>>16) & 0x3)
#define RX_DESC_DATA_LEN_MASK		(0xfff)
#define RX_DESC_DATA_LEN(x)			(x & RX_DESC_DATA_LEN_MASK)

#define PID_NONE_IP			(0x0)
#define PID_TCP_IP			(0x1)
#define PID_UDP_IP			(0x2)
#define PID_IP				(0x3)

#define ETH_FRAME_LEN		1514
#define ETH_ALEN			6

/***************************************************************************/
/*
 *  data structure
 */
typedef volatile struct _nic_frame_descriptor_
{
	unsigned long    StsLen;
	unsigned long    DataPtr;
	unsigned long    VLan;
	unsigned long    Reserved;
} NIC_FD_T;


typedef struct _test_endian
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;

}test_endian;

/* Descriptor setting */
//#define TX_DESC_NUM				32			// must be exponent of 2
//#define RX_DESC_NUM				32			// must be exponent of 2

#define TX_DESC_NUM				(32)			// must be exponent of 2
#define RX_DESC_NUM				(32)			// must be exponent of 2

#define RX_FC_THRESHOLD	        (8)

#define TX_MAX_SIZE						(1518)
#define MAX_PKT_SIZE			        (2048)
#define RX_DESC_BUFFER_SIZE		        0x800 // 2048 bytes
#define TX_BUF_SIZE						ETH_FRAME_LEN	/* FCS is added by the chip */

/* For Verify. */
#define LAN_10M_HALF_MODE		(0x1)
#define LAN_10M_FULL_MODE		(0x2)
#define LAN_100M_HALF_MODE		(0x3)
#define LAN_100M_FULL_MODE		(0x4)

#endif /* __8139CP_H__ */

