/******************************************************************************
 * $Id: rtk_nand.c 337905 2010-10-18 01:32:27Z alexchang2131 $
 * drivers/mtd/nand/rtk_nand.c
 * Overview: Realtek NAND Flash Controller Driver
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2010-07-02 AlexChang   create file
 *
 *
 *******************************************************************************/
#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include <sed_common.h>
#include <nand/rtk_nand.h>
#include <nand/mtd.h>

#include <nand/sed_nand_reg.h>
#include <sys_param_nand.h>
#include <sed_boot.h>

#define RTK_NAND_INTERRUPT (0)


#define BANNER  "Realtek NAND Flash Driver"
#define VERSION  "$Id: rtk_nand.c 337905 2013-12-1 01:32:27Z alexchang2131 $"
#define RTK_NAND_INTERRUPT	(0)
#define MTDSIZE	(sizeof (struct mtd_info) + sizeof (struct nand_chip))
#define MAX_PARTITIONS	16
#define BOOTCODE	16*1024*1024	//16MB
#define FACT_PARAM_SIZE 4*1024*1024 //4MB for TV factory parameter use.
#define DRIVER_NAME "rtkNF"
#define NF_INIT	(0)
#define NF_READ_TRIGGER 	(1)
#define NF_WRITE_TRIGGER 	(2)
#define NF_ERASE_TRIGGER 	(3)
#define NF_POLL_STATUS 	(4)
#define NF_WAKE_UP	(5)

#define NF_AUTO_IRQ_MASK	(0x08)
#define NF_DMA_IRQ_MASK		(0x10)
#define NF_POLL_IRQ_MASK	(0x80)
#define NF_XFER_IRQ_MASK	(0x04)
#define NF_IRQ_MASK	(NF_XFER_IRQ_MASK|NF_AUTO_IRQ_MASK|NF_DMA_IRQ_MASK|NF_POLL_IRQ_MASK)

#define NF_RESET_IRQ	REG_WRITE_U32(REG_NAND_ISREN,(0xff<<1|0x00));\
						REG_WRITE_U32(REG_NAND_ISR,(0xff<<1|0x00))

//#define NF_RESET_IRQ	NULL

#define NF_ENABLE_IRQ(mask)	REG_WRITE_U32(REG_NAND_ISREN,(mask|0x01))


static int g_nfFlag = NF_INIT ;

#define CLR_REG_NAND_ISR REG_WRITE_U32(REG_NAND_ISR,(0xFF<<1))

#define ISR_EN_READ (0x10)
#define ISR_EN_WRITE (0x08)

#define MODULE_AUTHOR(x)	/* x */
#define MODULE_DESCRIPTION(x)	/* x */

//static struct semaphore sem_NF_CARDREADER;

static int g_enReadRetrial = 0;
static unsigned char regVal1=0;
static unsigned char regVal2=0;
static unsigned char regVal3=0;
static unsigned char regVal4=0;
static unsigned char map_sel;				// PP mapping endian select

static unsigned char nRun=0;
static unsigned char nInc=0;

static void rtk_xfer_GetParameter(void);
static void rtk_xfer_SetParameter(unsigned char val1,unsigned char val2,unsigned char val3,unsigned char val4);

//static void rtk_SetVal( char val1, char val2, char val3, char val4);
static void rtk_SetReadRetrialMode(unsigned int run);
static int rtk_read_ecc_page_reTrial (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf);

extern int pcb_mgr_get_enum_info_byname(char *enum_name, unsigned long long *value);

#if RTK_NAND_INTERRUPT
static wait_queue_head_t	g_irq_waitq;

//#define RTK_WAIT_EVENT wait_event_interruptible(g_host->irq_waitq,g_nfFlag==NF_WAKE_UP)
#define RTK_WAIT_EVENT wait_event_interruptible(g_irq_waitq,g_nfFlag==NF_WAKE_UP)

#define CHECK_IRQ(flag,reg,mask,value) ((g_nfFlag==flag)&&((REG_READ_U32(reg)&mask)==value))
#define CHECK_REG(reg,mask,value) (REG_READ_U32(reg)&mask==value)
//#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,(REG_READ_U32(reg)|mask)&0xfffffffe))
#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,mask))
#define NF_AUTO_TRIG_ISR	(0x08)
#define NF_DMA_ISR	(0x10)
#define NF_POLL_STATUS_ISR	(0x80)
#endif

#define RETRY_COUNT	(0x20)

//Add for GPIO Setting
#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
static unsigned int g_regGPIODirBase = 0;
static unsigned int g_regGPIOOutBase = 0;
static struct rtk_nand_host *g_host;

static unsigned int g_NFWP_no = 0;
static unsigned int g_NFWP_index = 0;
static int g_NFWP_pinType = 0;

static unsigned int g_NFWP_value_INV = 0;
static unsigned int g_NFWP_value_en = 0;
static unsigned int g_NFWP_value_dis = 0;

typedef enum {
	PCB_PIN_TYPE_UNUSED = 0,
	PCB_PIN_TYPE_LSADC,
	PCB_PIN_TYPE_EMCU_GPIO,
	PCB_PIN_TYPE_GPIO,
	PCB_PIN_TYPE_ISO_GPIO,
	PCB_PIN_TYPE_UNIPWM,
	PCB_PIN_TYPE_ISO_UNIPWM,
	PCB_PIN_TYPE_PWM,
	PCB_PIN_TYPE_ISO_PWM,
	PCB_PIN_TYPE_UNDEF,
} PCB_PIN_TYPE_T;


#define NF_GPIO_OUT	(1)
#define NF_GPIO_IN	(0)
//#define NF_WP_ENABLE	(0)
//#define NF_WP_DISABLE	(1)

static unsigned int g_BootcodeSize = 0;
static unsigned int g_Secure_store_Size = 0;
static unsigned int g_Factory_param_size = 0;
static unsigned int g_Factory_ro_param_size = 0;

static int g_WP_en = 0;
unsigned int g_NF_pageSize = 0;
unsigned char g_isRandomize = 0;

#define NF_OOB_SIZE 512

const char *ptypes[] = {"cmdlinepart", NULL};

/* nand driver low-level functions */
static int rtk_read_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *buf);
static int rtk_read_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			u_char *data, u_char *oob_buf);
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *buf);
static int rtk_write_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data, const u_char *oob_buf, int isBBT);
static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page);
unsigned long long simple_strtoull (const char *cp, char **endp, unsigned int base);

static int page_size, oob_size, ppb;
//for whole nand flash
static int RBA_PERCENT = 5;

#ifdef CONFIG_MTD_NAND_IBT
//for whole nand flash
static int I_KERNEL_RBA_PERCENT = 1;
//for bootcode area
static int I_BOOTCODE_RBA_PERCENT = 10;
#endif

static char is_NF_CP_Enable_read = 0;
static char is_NF_CP_Enable_write = 0;

static unsigned int u32CP_mode = 0;
static unsigned int cpSel = 0;
static char u8regKey0[4];
static char u8regKey1[4];
static char u8regKey2[4];
static char u8regKey3[4];
static unsigned int *regKey0;
static unsigned int *regKey1;
static unsigned int *regKey2;
static unsigned int *regKey3;

//DECLARE_MUTEX (sem_NF_CARDREADER);
//EXPORT_SYMBOL(sem_NF_CARDREADER);

#if RTK_ARD_ALGORITHM //Variable declartion
	#define TOTAL_BLK_NUM	8192
	const unsigned int g_RecBlkStart = 64;
	const unsigned int g_RecBlkEnd   = 7389;

	const unsigned int g_PorcWindowSize = 64;
	const unsigned int g_ReadCntThrshld = 0x200000;
	//const unsigned int g_ReadCntThrshld = 0x400000;

	const unsigned int g_MaxMinDist = 8192;
	const unsigned int g_DistInc = 1;

	const unsigned int g_WinTrigThrshld = 8192;
	static unsigned int g_WinTrigCnt = 0;

	static unsigned int g_RecArray[8192]={0};

	static unsigned int g_u32WinStart = 0;
	static unsigned int g_u32WinEnd = 0;

	int whichBlk= 0;
	int pagePerBlk = 0;

#endif
struct rtk_nand_host {
	struct mtd_info		mtd;
	struct nand_chip	nand;
	struct mtd_partition	*parts;
	struct device		*dev;

	void			*spare0;
	void			*main_area0;
	void			*main_area1;

	void __iomem		*base;
	void __iomem		*regs;
	int			status_request;
	struct clk		*clk;
	int			clk_act;
	int			irq;

#if RTK_NAND_INTERRUPT
	wait_queue_head_t	irq_waitq;
#endif
	uint8_t			*data_buf;
	unsigned int		buf_start;
	int			spare_len;
};


//----------------------------------------------------------------------------

void setGPIOBit(unsigned int nGPIOBase, unsigned int nGPIOnum, unsigned int uBit)
{
        unsigned int whichReg = 0;
        unsigned int whichBit = 0;
	unsigned int temp;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
        whichBit = nGPIOnum%32;

	 temp = REG_READ_U32(whichReg);
        if(uBit)
                REG_WRITE_U32(whichReg,SETBIT(temp,whichBit));
        else
                REG_WRITE_U32(whichReg,CLEARBIT(temp,whichBit));
}
//----------------------------------------------------------------------------
unsigned int getGPIOBit(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        unsigned int whichReg = 0;
        unsigned int whichBit = 0;
        unsigned int ret=0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
        whichBit = nGPIOnum%32;
        ret = REG_READ_U32(whichReg);
        ret>>=whichBit;
        ret&=(0x1);
        return ret;
}
//----------------------------------------------------------------------------

unsigned int getGPIORegVal(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        unsigned int whichReg = 0;
//        unsigned int whichBit = 0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
		//printk("\tgetRegister 0x%x\n",whichReg);
        return REG_READ_U32(whichReg);
}


#if 1
//----------------------------------------------------------------------------
int is_jupiter_cpu(void)
{
	return 0;
}
//----------------------------------------------------------------------------
int is_saturn_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_darwin_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------

int is_macarthur_cpu(void)
{
	return 0;
}

int is_macarthur2_cpu(void)
{
	return 0;
}


//----------------------------------------------------------------------------
int is_nike_cpu(void)
{
	return 0;
}
int is_magellan_cpu(void)
{
	return 0;
}

int is_sirius_cpu(void)
{
	return 1;
}

//----------------------------------------------------------------------------
int is_venus_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_neptune_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_mars_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------

static unsigned char nf_is_random_mode(void)
{
	return REG_READ_U32(REG_RND_EN) & 0x1;
}

static void nf_enable_random_mode(void)
{
	//REG32(REG_RND_EN) |= 0x1;
	REG_WRITE_U32(REG_RND_EN,REG_READ_U32(REG_RND_EN) | 0x1);
}

static void nf_disable_random_mode(void)
{
	//REG32(REG_RND_EN) &= ~0x1;
	REG_WRITE_U32(REG_RND_EN,REG_READ_U32(REG_RND_EN) & (~0x1));
}

static void nf_set_random_read(unsigned int pagesize,unsigned int spare_col)
{
	REG_WRITE_U32(REG_RND_CMD1, 0x5);
	REG_WRITE_U32(REG_RND_CMD2, 0xe0);
	REG_WRITE_U32(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
	REG_WRITE_U32(REG_RND_SPR_STR_COL_H, (spare_col+ pagesize) >> 8);	// spare start address MSB
	REG_WRITE_U32(REG_RND_SPR_STR_COL_L, (spare_col+ pagesize) & 0xff);	// spare start address LSB
}

static void nf_set_random_write(unsigned int pagesize,unsigned int spare_col)
{
	REG_WRITE_U32(REG_RND_CMD1, 0x85);
	REG_WRITE_U32(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
	REG_WRITE_U32(REG_RND_SPR_STR_COL_H, (spare_col+ pagesize) >> 8);	// spare start address MSB
	REG_WRITE_U32(REG_RND_SPR_STR_COL_L, (spare_col+ pagesize) & 0xff);	// spare start address LSB
}


#if RTK_ARD_ALGORITHM //function declartion
//----------------------------------------------------------------------------
void RTK_ARD_DumpProcWin(int nStartBlk, int nSize)
{
	int i=0;
	unsigned int nSysStartBlk = g_RecBlkStart;
	for(i=0;i<nSize;i++)
	{
		if(nStartBlk<=g_RecBlkEnd)
		{
			printk("[%u] %u \n",nStartBlk,g_RecArray[nStartBlk]);
			nStartBlk++;
		}
		else
		{
			printk("[%u] %u \n",nSysStartBlk,g_RecArray[nSysStartBlk]);
			nSysStartBlk++;
		}
	}
}
//----------------------------------------------------------------------------
void slideProcWindowPtr()
{
	int tmp=0;
	g_u32WinStart = g_u32WinEnd;
	if(((g_u32WinEnd+g_PorcWindowSize-1)>g_RecBlkEnd))//reverse
	{
		tmp =  g_RecBlkEnd - g_u32WinEnd+1;
		g_u32WinEnd = g_RecBlkStart + (g_PorcWindowSize - tmp)-1;
	}
	else
	{
		g_u32WinEnd+=(g_PorcWindowSize-1);
	}
}
//----------------------------------------------------------------------------
void resetBlock(int nBlkNo)
{
	static unsigned int tmpCnt = 0;
//Reser block....TBD...
////////////////////////////
	tmpCnt++;

printk("\n");
printk("\t[AT]Reset block [%u] : %u\n",nBlkNo,g_RecArray[nBlkNo]);
printk("\t[AT]Total reset %u blocks\n",tmpCnt);
	g_RecArray[nBlkNo]=0;

}
//----------------------------------------------------------------------------
void travelProcWindow()//When WinTrigCnt > WinTrigThrshld
{
	int maxVal[2];
	int minVal[2];
	int i=0;
	int idx=g_u32WinStart;

	if(g_RecArray[g_u32WinEnd] > g_RecArray[g_u32WinStart])
	{
		minVal[0]=g_u32WinStart;
		minVal[1]=g_RecArray[g_u32WinStart];
		maxVal[0]=g_u32WinEnd;
		maxVal[1]=g_RecArray[g_u32WinEnd];
	}
	else
	{
		maxVal[0]=g_u32WinStart;
		maxVal[1]=g_RecArray[g_u32WinStart];
		minVal[0]=g_u32WinEnd;
		minVal[1]=g_RecArray[g_u32WinEnd];
	}

	printk("++++Before Travel++++\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);
	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	for(i=0;i<g_PorcWindowSize;i++)
	{
		if(g_RecArray[idx]>=g_ReadCntThrshld)
			resetBlock(idx);
		if(idx<=g_RecBlkEnd)
		{
			if(g_RecArray[idx]<minVal[1])//Process minimun value
			{
				minVal[0]=idx;
				minVal[1]=g_RecArray[idx];
			}
			if(g_RecArray[idx]>maxVal[1])//Process maximun value
			{
				maxVal[0]=idx;
				maxVal[1]=g_RecArray[idx];
			}
			if(idx==g_RecBlkEnd)
				idx = g_RecBlkStart;
			else
				idx++;
		}

	}
	printk("----After Travel w/o Grouping ----\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);

	//Grouping
	g_RecArray[minVal[0]] += g_DistInc;
	if((maxVal[1]-minVal[1]) < g_MaxMinDist)
	{
		g_RecArray[maxVal[0]] += g_MaxMinDist;
	}

	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	slideProcWindowPtr();
	g_WinTrigCnt = 0; //Reset windows trigger count
}
#endif

#endif

//----------------------------------------------------------------------------

void WAIT_DONE(unsigned int addr, unsigned int mask, unsigned int value)
{
	while ( (REG_READ_U32(addr) & mask) != value )
	{
		asm("nop");
	}
}
//----------------------------------------------------------------------------

static void rtk_nand_resumeReg(void)
{
	REG_WRITE_U32( 0xb801032c,0x01);	//Enable NAND/CardReader arbitrator
	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(0xb800000c)& (~0x00800000));
	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
		REG_WRITE_U32( REG_NF_CKSEL,0x02 );
	else if(is_saturn_cpu()||is_darwin_cpu())
		REG_WRITE_U32( (0xb8000038),0x02 );
	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(REG_CLOCK_ENABLE1)| (0x00800000));

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL,0x7<<26);
	else
		REG_WRITE_U32(REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1) | NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0)); //set spare2ddr func. 4=>0.5k spe2ddr_ena at A000F000

	REG_WRITE_U32( REG_PD,~(0x1 << 0) );
	REG_WRITE_U32( REG_ND_CMD,CMD_RESET );

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
		REG_WRITE_U32( REG_ND_CTL,(0x80 | 0x00));
	else
		REG_WRITE_U32( REG_ND_CTL,(NF_ND_CTL_xfer(0x01) | NF_ND_CTL_tran_mode(0)) );

	WAIT_DONE(REG_ND_CTL,0x80,0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);

	REG_WRITE_U32( REG_TIME_PARA1,NF_TIME_PARA1_T1(0x0));
	REG_WRITE_U32( REG_TIME_PARA2,NF_TIME_PARA2_T2(0x0));
	REG_WRITE_U32( REG_TIME_PARA3,NF_TIME_PARA3_T3(0x0));

	if(!is_jupiter_cpu()||!is_saturn_cpu()||!is_darwin_cpu()||!is_macarthur_cpu()||!is_nike_cpu()||!is_sirius_cpu())
		REG_WRITE_U32( REG_DELAY_CTL,NF_DELAY_CTL_T_WHR_ADL(0x09) );

	REG_WRITE_U32( REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(0x01));
	REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

}
//----------------------------------------------------------------------------

/*
 * RTK NAND suspend:
 */
static void rtk_nand_suspend (struct mtd_info *mtd)
{
	printk("[%s]Enter..\n",__FUNCTION__);
	if(g_enReadRetrial)
	{
		rtk_xfer_SetParameter(regVal1,regVal2,regVal3,regVal4);
	}
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
	printk("[%s]Exit..\n",__FUNCTION__);

}
//----------------------------------------------------------------------------
static void rtk_nand_resume (struct mtd_info *mtd)
{
	printk("[%s]\n",__FUNCTION__);
	if(g_enReadRetrial)
	{
		if((regVal1==0)&&(regVal2==0)&&(regVal3==0)&&(regVal4==0))
			rtk_xfer_GetParameter();
	}
	rtk_nand_resumeReg();
	printk("[%s]Exit..\n",__FUNCTION__);

}
//----------------------------------------------------------------------------
static void rtk_read_oob_from_SRAM(struct mtd_info *mtd, __u8 *r_oobbuf)
{
	unsigned int reg_oob, reg_num;
	int i;
	unsigned int sram_base_addr;
	if(is_macarthur2_cpu()||is_sirius_cpu())
		sram_base_addr = REG_NF_BASE_ADDR + 0x400;
	else
		sram_base_addr = REG_NF_BASE_ADDR;
	//printk("mtd->ecctype 0x%x\n",mtd->ecctype);
//	if ( mtd->ecctype == MTD_ECC_NONE )
	if ( mtd->ecctype == MTD_ECC_NONE ||(mtd->ecctype!=MTD_ECC_RTK_HW))
	{
		reg_num = sram_base_addr;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[0] = reg_oob & 0xff;
		r_oobbuf[1] = (reg_oob >> 8) & 0xff;
		r_oobbuf[2] = (reg_oob >> 16) & 0xff;
		r_oobbuf[3] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+4;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[4] = reg_oob & 0xff;

		reg_num = sram_base_addr+16;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[5] = reg_oob & 0xff;
		r_oobbuf[6] = (reg_oob >> 8) & 0xff;
		r_oobbuf[7] = (reg_oob >> 16) & 0xff;
		r_oobbuf[8] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+16*2;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[9] = reg_oob & 0xff;
		r_oobbuf[10] = (reg_oob >> 8) & 0xff;
		r_oobbuf[11] = (reg_oob >> 16) & 0xff;
		r_oobbuf[12] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+16*3;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[13] = reg_oob & 0xff;
		r_oobbuf[14] = (reg_oob >> 8) & 0xff;
		r_oobbuf[15] = (reg_oob >> 16) & 0xff;
		r_oobbuf[16] = (reg_oob >> 24) & 0xff;

	}
	else
	{
		for ( i=0; i < 16; i++)
			{
				reg_num = sram_base_addr + i*4;
				reg_oob = REG_READ_U32(reg_num);
				r_oobbuf[i*4+0] = reg_oob & 0xff;
				r_oobbuf[i*4+1] = (reg_oob >> 8) & 0xff;
				r_oobbuf[i*4+2] = (reg_oob >> 16) & 0xff;
				r_oobbuf[i*4+3] = (reg_oob >> 24) & 0xff;
			}
	}
}


//----------------------------------------------------------------------------
static void rtk_nand_read_id(struct mtd_info *mtd, u_char id[6])
{
	int id_chain;

#if 1
#define XFER_MODE
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0x06) );
	REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(0x01));

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0x0));
	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));

	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_READ_ID));
#ifdef XFER_MODE
	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(0x01));
	WAIT_DONE(REG_ND_CTL,0x80,0);
#endif
	REG_WRITE_U32(REG_ND_PA0,NF_ND_PA0_page_addr0(0));
	REG_WRITE_U32(REG_ND_PA2,NF_ND_PA2_addr_mode(0x07));

#ifdef XFER_MODE

	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(1));
	WAIT_DONE(REG_ND_CTL,0x80,0);
#else
    REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)| NF_AUTO_TRIG_auto_case(1));
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
#endif
	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(4));
	WAIT_DONE(REG_ND_CTL,0x80,0);

	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_reset(1));

	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(1)|NF_SRAM_CTL_mem_region(0));

	if(is_macarthur2_cpu()||is_sirius_cpu())
		id_chain = REG_READ_U32(REG_ND_PA0+0x400);
	else
		id_chain = REG_READ_U32(REG_ND_PA0);
	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;
	if(id_chain==0xDA94D7AD)
	{
		printk("Detect H27UBG8T2B and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
		g_isRandomize = 1;
		printk("Enable Read-retrial mode...\n");
		printk("Enable Randomized mechanism\n");
	}
	if(is_macarthur2_cpu()||is_sirius_cpu())
		id_chain = REG_READ_U32(REG_ND_PA1+0x400);
	else
		id_chain = REG_READ_U32(REG_ND_PA1);

	id[4] = id_chain & 0xff;
	id[5] = (id_chain >> 8) & 0xff;

	REG_WRITE_U32(REG_SRAM_CTL,0x0);	//# no omitted
#else
if(!rtk_tmp)
	id_chain=0xDA94D7AD;
else
	id_chain=0x20202020;

	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;


	if(id_chain==0xDA94D7AD)
	{
		printk("Detect H27UBG8T2B and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
		id[4] = 0x74;
		id[5] = 0xc3;
	}

else
{
	id[4] = 0x20;
	id[5] = 0x20;

}
#endif
}

//----------------------------------------------------------------------------
#if 1
static void reverse_to_Tags(char *r_oobbuf, int eccBits)
{
	int k,j;

	if(is_jupiter_cpu())
	{
		for ( k=0; k<4; k++ )
				r_oobbuf[5+k] = r_oobbuf[16+k];

			memcpy(&r_oobbuf[9],&r_oobbuf[32],4);//add by alexchang for improve nand read 0225-2010
			memcpy(&r_oobbuf[13],&r_oobbuf[48],4);//add by alexchang for improve nand read 0225-2010
	}

	else
	{

		if(eccBits==0)
		{
	    for ( k=0; k<4; k++ )
			r_oobbuf[5+k] = r_oobbuf[8+k];

		memcpy(&r_oobbuf[9],&r_oobbuf[16],4);//add by alexchang for improve nand read 0225-2010
		memcpy(&r_oobbuf[13],&r_oobbuf[24],4);//add by alexchang for improve nand read 0225-2010
		}
		else if(eccBits==0x18)
		{
			for(k=0,j=1;k<28;k+=4,j++)
				memcpy(&r_oobbuf[1+k],&r_oobbuf[8*j],4);
		}
	}
}
#endif
//----------------------------------------------------------------------------
static int rtk_Process_Buf(unsigned char* oob_buf)
{
	int j=0,k=0;
	unsigned int reg_oob, reg_num;

	REG_WRITE_U32(REG_READ_BY_PP,0x00);
	REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);

	for ( j=0; j < 12; j++)
	{
		reg_num = REG_NF_BASE_ADDR + j*4;
		reg_oob = REG_READ_U32(reg_num);
		oob_buf[j*4+0] = reg_oob & 0xff;
		oob_buf[j*4+1] = (reg_oob >> 8) & 0xff;
		if(j==11)
			break;
		oob_buf[j*4+2] = (reg_oob >> 16) & 0xff;
		oob_buf[j*4+3] = (reg_oob >> 24) & 0xff;
	}

	for ( j=16,k=0; j < 28; j++,k++)
	{
		reg_num = REG_NF_BASE_ADDR + j*4;
		reg_oob = REG_READ_U32(reg_num);
		oob_buf[46+k*4+0] = reg_oob & 0xff;
		oob_buf[46+k*4+1] = (reg_oob >> 8) & 0xff;
		if(j==27)
			break;
		oob_buf[46+k*4+2] = (reg_oob >> 16) & 0xff;
		oob_buf[46+k*4+3] = (reg_oob >> 24) & 0xff;
	}

	REG_WRITE_U32(REG_SRAM_CTL, 0x00);
	REG_WRITE_U32(REG_READ_BY_PP,0x80);
	return 0;
}
//----------------------------------------------------------------------------

static int rtk_read_regTrigger(int isCPdisable,int page_size,int triggerMode)
{
#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
	if(is_NF_CP_Enable_read&&(!isCPdisable))
	{
		REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
		REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
		REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
		REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

		REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
	}
	else
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(triggerMode));

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif
	if(is_NF_CP_Enable_read&&(!isCPdisable))//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}
	return 0;
}


//----------------------------------------------------------------------------
static int rtk_read_ecc_page_withLargeECC (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf)
{

	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;
	int r_unit = 2048;
	int i=0,cnt=0;
//	unsigned int reg_oob, reg_num;
	unsigned char *ptr_oob;
	unsigned int  *ptr_data;

	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;

	ptr_oob = kmalloc(128,GFP_KERNEL);
	ptr_data = kmalloc(2048,GFP_KERNEL);
//printk("ptr_oob 0x%x\n",ptr_oob);
//printk("ptr_data 0x%x\n",ptr_data);

	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;
	cnt = page_size/r_unit;
    if(page_size%r_unit)
    {
		printk("[%s]ERROR page_size not alignment...\n",__FUNCTION__);
		return -1;
    }

	page_size = 2048;

	REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));

	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
	}
	REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));
	REG_WRITE_U32(REG_PP_CTL0,0);

 	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
 		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//dram_sa = ( (uint32_t)data_buf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(data_buf)) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	if (ptr_oob){
		//spare_dram_sa = ( (uint32_t)ptr_oob >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(ptr_oob)) >> 3);
	}else{
		//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(this->g_oobbuf)) >> 3);
	}

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL,(0x7<<26) | (spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	rtk_read_regTrigger(mtd->isCPdisable_R, page_size,auto_trigger_mode);

	rtk_Process_Buf(oob_buf);
	for(;i<cnt-1;i++)
	{
		data_buf+=2048;
		oob_buf+=92;
		//dram_sa = ( (uint32_t)data_buf >> 3);
		dram_sa = (((unsigned int)PHYSADDR(data_buf)) >> 3);

		if (ptr_oob){
			//spare_dram_sa = ( (uint32_t)ptr_oob >> 3);
			spare_dram_sa = (((unsigned int)PHYSADDR(ptr_oob)) >> 3);
		}else{
			//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
			spare_dram_sa = (((unsigned int)PHYSADDR(this->g_oobbuf)) >> 3);
		}

			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				REG_WRITE_U32( REG_SPR_DDR_CTL,(0x7<<26) | (spare_dram_sa&0x3ffffff));
			else
				REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
		REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));
		rtk_read_regTrigger(mtd->isCPdisable_R, page_size,0x04);
		rtk_Process_Buf(oob_buf);
	}

	if(ptr_oob)
	{
		kfree(ptr_oob);
		ptr_oob=NULL;
	}
	if(ptr_data)
	{
		kfree(ptr_data);
		ptr_data=NULL;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK)>>1) & 0x01;

	mtd->nEccMaxValue = REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM));
	if (blank_all_one)
	{
		if(this->erase_page_flag)
			this->erase_page_flag[chip_section+section] =  (1<< index);
	}

	if(blank_all_one == 1){
		// return OK if all data bit is 1 (page is not written yet)
		return 0;
	}
	if (REG_READ_U32(REG_ND_ECC) & 0x0C){
		if(!this->erase_page_flag)
		{
			if (REG_READ_U32(REG_ND_ECC) & 0x08){
				if ( chipnr == 0 && (page < (g_BootcodeSize/page_size)) )
				{
					return 0;
				}
				else
				{
					return -1;
				}
			}
		}
		else
		{
			if (this->erase_page_flag[chip_section+section] & (1<< index) ){
				;
			}else
			{
				if (REG_READ_U32(REG_ND_ECC) & 0x08){
					if ( chipnr == 0 && (page < (g_BootcodeSize/page_size)) )
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
			}
		}
	}
#if RTK_ARD_ALGORITHM
	g_WinTrigCnt++;
	whichBlk = page / ppb;
	g_RecArray[whichBlk]++;
	if(g_WinTrigCnt > g_WinTrigThrshld)
		travelProcWindow();
#endif
	mtd->isCPdisable_R = 0;
	return rc;
}

//----------------------------------------------------------------------------
//Add read retrial mechanism
//static int nRun,regVal1,regVal2,regVal3,regVal4,nInc;
static void rtk_xfer_SetParameter(unsigned char val1,unsigned char val2,unsigned char val3,unsigned char val4)
{
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;
			g_nfFlag = NF_INIT;
#endif


	//rtk_xfer_GetParameter();
	REG_WRITE_U32(REG_DATA_TL0, 0x1);				//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(1) | NF_DATA_TL1_sram_path(0) | NF_DATA_TL1_length1(0x0));				//Set data transfer count[13:8], SRAM path and access mode

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD, 0x36);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Transfer Reg#1 address
	REG_WRITE_U32(REG_ND_PA0, 0xa7);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7) | NF_ND_PA2_page_addr2(0x0));				//Set address mode & PA[20:16]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//Data read to DRAM from NAND through PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, val1);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	//Transfer Reg#2 address
	REG_WRITE_U32(REG_ND_PA0, 0xad);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, val2);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done


	//Transfer Reg#3 address
	REG_WRITE_U32(REG_ND_PA0, 0xae);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, val3);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done


	//Transfer Reg#4 address
	REG_WRITE_U32(REG_ND_PA0, 0xaf);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, val4);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD, 0x16);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	//printk("Set and Get value...\n");
	//rtk_xfer_GetParameter();
//	printk("[%s]%d,%d,%d,%d\n",__FUNCTION__,val1,val2,val3,val4);
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;
			g_nfFlag = NF_INIT;
#endif

}
//----------------------------------------------------------------------------
static void rtk_xfer_GetParameter()
{
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;
			g_nfFlag = NF_INIT;
#endif

#if 1 //Get parameter from DRAM

	regVal1=(REG_READ_U32(0xb8007660)>>24)&0x000000ff ;
    regVal2=(REG_READ_U32(0xb8007660)>>16)&0x000000ff ;
    regVal3=(REG_READ_U32(0xb8007660)>>8)&0x000000ff ;
    regVal4=REG_READ_U32(0xb8007660)&0x000000ff ;


#else

	REG_WRITE_U32(REG_DATA_TL0, 0x1);				//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(1) | NF_DATA_TL1_sram_path(0) | NF_DATA_TL1_length1(0x0));				//Set data transfer count[13:8], SRAM path and access mode

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//Data read to DRAM from NAND through PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL1, 0x0);				//Set PP starting assdress[7:0]
	//Set table sram
	//REG_WRITE_U32(NF_TABLE_CTL_reg, NF_TABLE_CTL_table_start_addr(0x0) | NF_TABLE_CTL_table_enable(0));				//Set table SRAM starting assdress ( 0 ~ A) and enable table SRAM

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD, 0x37);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
//test hang

	//Transfer Reg#1 address
	REG_WRITE_U32(REG_ND_PA0, 0xa7);
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7) | NF_ND_PA2_page_addr2(0x0));	//Set reg#1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
//test ok
	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80,0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal1, REG_READ_U32(REG_ND_DAT));
//test err


	//Transfer Reg#2 address
	REG_WRITE_U32(REG_ND_PA0, 0xad);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal2, REG_READ_U32(REG_ND_DAT));

	//Transfer Reg#3 address
	REG_WRITE_U32(REG_ND_PA0, 0xae);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80,0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal3, REG_READ_U32(REG_ND_DAT));


	//Transfer Reg#4 address
	REG_WRITE_U32(REG_ND_PA0, 0xaf);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal4, REG_READ_U32(REG_ND_DAT));

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0)); 			//Set PP starting address[9:8], PP reset and PP enable
	#endif

//	printk("[%s]%d,%d,%d,%d\n",__FUNCTION__,regVal1,regVal2,regVal3,regVal4);
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;

			g_nfFlag = NF_INIT;
#endif

}
//----------------------------------------------------------------------------
#if 0
static void rtk_SetVal( char val1, char val2, char val3, char val4)
{
	rtk_xfer_GetParameter();
	regVal1+=val1;
	regVal2+=val2;
	regVal3+=val3;
	regVal4+=val4;
	rtk_xfer_SetParameter(regVal1,regVal2,regVal3,regVal4);
}
#endif
//----------------------------------------------------------------------------
static void rtk_SetReadRetrialMode(unsigned int run)
{

	if((regVal1==0)&&(regVal2==0)&&(regVal3==0)&&(regVal4==0))
		rtk_xfer_GetParameter();
	run%=7;

	if(run!=nRun)
		printk("\n\n$$run %d,[Run %d]\n",run,nRun);
	switch(run)
	{

	#if 1
		case 1:
			//rtk_SetVal(0x00,0x06,0x0A,0x06);
			rtk_xfer_SetParameter(regVal1,regVal2+0x06,regVal3+0x0A,regVal4+0x06);

		break;

		case 2:
			//rtk_SetVal(0xff,-0x03,-0x07,-0x08);
			rtk_xfer_SetParameter(0x00,regVal2-0x03,regVal3-0x07,regVal4-0x08);

		break;

		case 3:
			//rtk_SetVal(0xff,-0x06,-0x0D,-0x0F);
			rtk_xfer_SetParameter(0x00,regVal2-0x06,regVal3-0x0D,regVal4-0x0F);

		break;

		case 4:
			//rtk_SetVal(0xff,-0x09,-0x14,-0x17);
			rtk_xfer_SetParameter(0x00,regVal2-0x09,regVal3-0x14,regVal4-0x17);
		break;

		case 5:
			//rtk_SetVal(0xff,0xff,-0x1A,-0x1E);
			rtk_xfer_SetParameter(0x00,0x00,regVal3-0x1A,regVal4-0x1E);

		break;

		case 6:

			//rtk_SetVal(0xff,0xff,-0x20,-0x25);
			rtk_xfer_SetParameter(0x00,0x00,regVal3-0x20,regVal4-0x25);

		break;
#endif
		default:
			//rtk_xfer_SetParameter(regVal1,regVal2,regVal3,regVal4);
		break;
	}
}
//----------------------------------------------------------------------------
static int rtk_read_ecc_page_reTrial (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf)
{

	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;

	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);
	#if RTK_NAND_INTERRUPT
		NF_RESET_IRQ;
		NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
		g_nfFlag = NF_READ_TRIGGER;
#endif
	nInc=0;
	while(nInc<7)
	{


		rtk_SetReadRetrialMode(nInc+nRun);

		this = (struct nand_chip *) mtd->priv;
		page_size = mtd->oobblock;
		oob_size = mtd->oobsize;
		ppb = mtd->erasesize/mtd->oobblock;

		if ( chipnr == 0 && page < (g_BootcodeSize/page_size))
		{
			mtd->isCPdisable_R = 1;
			mtd->isScramble=MTD_SCRAMBLE_DISABLE;
		}
		else
			mtd->isScramble=1;

		if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
		{
			if(!oob_buf)
			{
				rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,this->g_oobbuf);
			}
			else
				rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,oob_buf);
			if(rc==0)
			{
				nRun+=nInc;
				nRun%=7;
				return rc;
			}
			else
			{
				nInc++;
				rc=-1;
				continue;
			}
		}

;

		//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
		REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );
		REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));

		if(this->ecc_select == 0x18)
		{
			page_len = page_size >> 10;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
		}
		else
		{
			page_len = page_size >> 9;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

		REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0,0);

	 	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
	 		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
		else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
			REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
		else
			REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

		REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
		REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
		REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));

		REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
		REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
		REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
		REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
		REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
		REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

		//dram_sa = ( (uint32_t)data_buf >> 3);
		dram_sa = (((unsigned int)PHYSADDR(data_buf)) >> 3);

		REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

		if (oob_buf){
			//spare_dram_sa = ( (uint32_t)oob_buf >> 3);
			spare_dram_sa = (((unsigned int)PHYSADDR(oob_buf)) >> 3);
		}else{
			//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
			spare_dram_sa = (((unsigned int)PHYSADDR(this->g_oobbuf)) >> 3);
		}

		if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
			REG_WRITE_U32( REG_SPR_DDR_CTL,(0x7<<26) | (spare_dram_sa&0x3ffffff));
		else
			REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));


#if RTK_NAND_INTERRUPT
		NF_RESET_IRQ;
		NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
		g_nfFlag = NF_READ_TRIGGER;
#endif
		//printk("Retry[%s]Ran 0x%x, scr 0x%x, flag 0x%x\n",__FUNCTION__,g_isRandomize,mtd->isScramble,mtd->isCPdisable_R);
		//printk("R blk:%u, page:%u\n",page/ppb,page%ppb);

		if((g_isRandomize&&(!mtd->isCPdisable_R))||(mtd->isScramble!=MTD_SCRAMBLE_DISABLE))
		{
			//printk("Ran 0x%x\n",g_isRandomize);
			//printk("isCPdisable_R 0x%x\n",mtd->isCPdisable_R);
			//printk("isScramble 0x%x\n",mtd->isScramble);
	                //printk("page 0x%x\n",page);
			//printk("@");
			if(u32CP_mode==0)//CBC initial key setting.
			{
				REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
			}
			REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			else
				RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{

			if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
			{
				//printk("X");
				REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
				REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
				REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
				REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

				REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
				REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
				RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
				if ( oob_buf )
					RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
				else
					RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
				REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
			}
			else
			{//printk("/");
				RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
				if ( oob_buf )
					RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
				else
					RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
				REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
			}
		}

		REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
		RTK_WAIT_EVENT;
#else
		WAIT_DONE(REG_AUTO_TRIG,0x80,0);
		WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif


		if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
		{
			REG_WRITE_U32(REG_CP_NF_SET,0);
		}

		if(oob_buf)
		{
			if(this->ecc_select==0x18||this->ecc_select==0x0c)
				reverse_to_Tags(oob_buf,this->ecc_select);
			else
			{
				REG_WRITE_U32(REG_READ_BY_PP,0x00);
				if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
				else
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
				rtk_read_oob_from_SRAM(mtd, oob_buf);
				REG_WRITE_U32(REG_SRAM_CTL, 0x00);
				REG_WRITE_U32(REG_READ_BY_PP,0x80);
			}
		}

		chip_section = (chipnr * this->page_num) >> 5;
		section = page >> 5;
		index = page & (32-1);
		blank_all_one = (REG_READ_U32(REG_BLANK_CHK)>>1) & 0x01;


		// add by alexchang 01-28-2011
		mtd->nEccMaxValue = REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM));
		if (blank_all_one)
		{
			if(this->erase_page_flag)
			this->erase_page_flag[chip_section+section] =  (1<< index);
		}

		if(blank_all_one == 1){
		// return OK if all data bit is 1 (page is not written yet)
		return 0;
		}

		if (REG_READ_U32(REG_ND_ECC) & 0x0C){
					if(!this->erase_page_flag)
					{
						if (REG_READ_U32(REG_ND_ECC) & 0x08){
							if ( chipnr == 0 && page < g_BootcodeSize/page_size )
							{
								nRun+=nInc;
								nRun%=7;
							    return 0;
							}
							else
							{
								//printk("0[%s]nInc %d,nRun %d\n",__FUNCTION__,nInc,nRun);
								nInc++;
								rc=-1;
								printk("!!!Read Fail page NO. 0x%x\n",page);
								continue;
							}
						}
					}
					else
					{
						if (this->erase_page_flag[chip_section+section] & (1<< index) ){
							;
						}else
						{
							if (REG_READ_U32(REG_ND_ECC) & 0x08){
								if ( chipnr == 0 && page < g_BootcodeSize/page_size )
								{
									nRun+=nInc;
									nRun%=7;
									return 0;
								}
								else
								{
									//printk("1[%s]nInc %d,nRun %d\n",__FUNCTION__,nInc,nRun);
									nInc++;
									rc=-1;
									printk("!!!Read Fail page NO. 0x%x\n",page);
									continue;
								}
							}
						}
					}
				}

#if RTK_ARD_ALGORITHM
		whichBlk = page / ppb;
		g_RecArray[whichBlk]++;
		if(g_WinTrigCnt > g_WinTrigThrshld)
			travelProcWindow();
#endif
		mtd->isCPdisable_R = 0;
		rc=0;
		break;

	}
	//printk("return rc %d\n",rc);
	nRun+=nInc;
	nRun%=7;

	return rc;
}


//----------------------------------------------------------------------------


static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page)
{
	struct nand_chip *this = NULL;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int retryCnt = RETRY_COUNT;
	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;

	this = (struct nand_chip *) mtd->priv;
//	printk("AT[%s]:page %d, ppb %d, mtd->erasesize %u, mtd->oobblock %u\n",__FUNCTION__,page,ppb,mtd->erasesize,mtd->oobblock);
	if ( page & (ppb-1) ){
		printk("%s: page %d is not block alignment !!\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		return -1;
	}

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Disable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		//no audio pin type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_dis);
					break;
			#endif
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_dis);//Set Value
					break;
			}
            		REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3));
            		REG_WRITE_U32( REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(0x07)|NF_POLL_FSTS_trig_poll(1));
			WAIT_DONE(REG_POLL_FSTS,0x1,0);
		}
	}

#if RTK_NAND_INTERRUPT
	g_nfFlag = NF_ERASE_TRIGGER;
	NF_RESET_IRQ;
#endif

	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32( REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));

	REG_WRITE_U32( REG_ND_CMD,NF_ND_CMD_cmd(CMD_BLK_ERASE_C1) );
	REG_WRITE_U32( REG_CMD2,NF_CMD2_cmd2(CMD_BLK_ERASE_C2) );
	REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3) );

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(0x04)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>> 21)&0x7) );

	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)|NF_AUTO_TRIG_auto_case(2) );
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_ERASE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_IRQ_MASK);
#else
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
#endif

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		//no audio pin type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_en);
					break;
			#endif
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_en);//Set Value
					break;
			}
		}
	}

	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printk("[%s] erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
		if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
			return 0;
		else
			return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	if(this->erase_page_flag)
		memset ( (__u32 *)(this->erase_page_flag)+ chip_section + section, 0xff, ppb>>3);
	//printk("[AT]Erase block : %u  \n",page/ppb);
	//up (&sem_NF_CARDREADER);
#if RTK_ARD_ALGORITHM
	g_RecArray[page/ppb]=0;
//	printk("[AT]Erase block : %u  \n",page/ppb);
#endif
	return 0;
}
//----------------------------------------------------------------------------
unsigned char *malloc_aligned(size_t size,int alignment)
{
   unsigned char *ptr = kmalloc(size + alignment-1,GFP_KERNEL);
   if (!ptr) return NULL;
   ptr = (unsigned char *)(((unsigned int)(ptr) + alignment-1) & ~alignment);
   return ptr;
}
//----------------------------------------------------------------------------
#ifdef CONFIG_MTD_NAND_IBT
//add blank block check
static int rtk_read_oob_ibt (struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *oob_buf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one=0;
	int page_len;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	uint8_t auto_trigger_mode = 2;
	uint8_t addr_mode = 1;
	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;

	//------------------------set random mode-------------------
	if (nf_is_random_mode()){
		nf_set_random_read(mtd->oobblock, 0);
	}

	if(g_enReadRetrial)
	{
		if(!oob_buf)
		{
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,this->g_oobbuf);
		}
		else
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,oob_buf);
		//up(&sem_NF_CARDREADER);
		return rc;
	}

	if ( len>oob_size || !oob_buf ){
		printf("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		return -1;
	}

	if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
		mtd->isCPdisable_R = 1;

	if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
	{
		rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,this->g_databuf,oob_buf);
		return rc;
	}

	REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1));
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0)); //REG:0x100

	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
	}
	REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7) );

	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010

	//Set ECC
	REG_WRITE_U32(REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(1));//add by alexchang0223-2010

	//Set DMA
	//dram_sa = ( (uint32_t) this->g_databuf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(this->g_databuf )) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//spare_dram_sa = ( (uint32_t)oob_buf >> 3);		//oob
	spare_dram_sa = (((unsigned int)PHYSADDR(oob_buf)) >> 3);

	if(is_jupiter_cpu())
		REG_WRITE_U32(REG_SPR_DDR_CTL,(0x07<<26)|(spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
	if(g_isRandomize&&(!mtd->isCPdisable_R))
	{
		if(u32CP_mode==0)//CBC initial key setting.
        {
                REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
        }
		REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

		REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
		RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
		if ( oob_buf )
			RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));

	}
	else
	{
		//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
		if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
		{
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);

			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);

			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
		}
	}
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

	WAIT_DONE(REG_AUTO_TRIG,0x80,0);

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif

	if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}

	if(oob_buf)
	{
		if(this->ecc_select==0x18||this->ecc_select==0xc||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
			reverse_to_Tags(oob_buf,this->ecc_select);
		else
		{
			REG_WRITE_U32(REG_READ_BY_PP,0x00);
			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
			else
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
			rtk_read_oob_from_SRAM(mtd, oob_buf);
			REG_WRITE_U32(REG_SRAM_CTL, 0x00);
			REG_WRITE_U32(REG_READ_BY_PP,0x80);

			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				reverse_to_Tags(oob_buf,this->ecc_select);
		}
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK)>>1) & 0x01;
	if (blank_all_one)
	{
		if(this->erase_page_flag)
		this->erase_page_flag[chip_section+section] =  (1<< index);
	}

	if(blank_all_one == 1){
		// return OK if all data bit is 1 (page is not written yet)
		return DATA_ALL_ONE;
	}

	if (REG_READ_U32(REG_ND_ECC) & 0x0C){
				if(!this->erase_page_flag)
				{
					if (REG_READ_U32(REG_ND_ECC) & 0x08){
						if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
						{
							//up (&sem_NF_CARDREADER);
							return 0;
						}
						else
						{
							//up (&sem_NF_CARDREADER);
							printk("[%s][%d]blk %d, page %d fail\n",__FUNCTION__,__LINE__,page/ppb,page%ppb);
							return -1;
						}
					}
				}
				else
				{
					if (this->erase_page_flag[chip_section+section] & (1<< index) ){
						;
					}else
					{
						if (REG_READ_U32(REG_ND_ECC) & 0x08){
							if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
							{
								//up (&sem_NF_CARDREADER);
								return 0;
							}
							else
							{
								//up (&sem_NF_CARDREADER);
								printk("[%s][%d]blk %d, page %d fail\n",__FUNCTION__,__LINE__,page/ppb,page%ppb);
								return -1;
							}
						}
					}
				}
			}

	mtd->isCPdisable_R = 0;
	return rc;
}

#endif

static int rtk_read_oob (struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *oob_buf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one=0;
	int page_len;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	uint8_t auto_trigger_mode = 2;
	uint8_t addr_mode = 1;
	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;

#if 0
	while (down_interruptible (&sem_NF_CARDREADER)) {
		printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
		if(retryCnt<=0)
		{
			printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
			return -ERESTARTSYS;
		}
		retryCnt--;
	}
#endif

	//------------------------set random mode-------------------
	if (nf_is_random_mode()){
		nf_set_random_read(mtd->oobblock, 0);
	}


	if(g_enReadRetrial)
	{
		if(!oob_buf)
		{
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,this->g_oobbuf);
		}
		else
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,oob_buf);
		//up(&sem_NF_CARDREADER);
		return rc;
	}
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
	if ( len>oob_size || !oob_buf ){
		printf("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		return -1;
	}
	if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
		mtd->isCPdisable_R = 1;

	if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
	{
		rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,this->g_databuf,oob_buf);
		//up(&sem_NF_CARDREADER);
		return rc;
	}
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
	REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1));
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0)); //REG:0x100
	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
	}
	REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7) );

	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010

	//Set ECC
	REG_WRITE_U32(REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(1));//add by alexchang0223-2010

	//Set DMA
	//dram_sa = ( (uint32_t) this->g_databuf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(this->g_databuf)) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//spare_dram_sa = ( (uint32_t)oob_buf >> 3);		//oob
	spare_dram_sa = (((unsigned int)PHYSADDR(oob_buf)) >> 3);
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	if(is_jupiter_cpu())
		REG_WRITE_U32(REG_SPR_DDR_CTL,(0x07<<26)|(spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
	if(g_isRandomize&&(!mtd->isCPdisable_R))
	{
		//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
		if(u32CP_mode==0)//CBC initial key setting.
        {
                REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
        }
		REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

		REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
		RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
		if ( oob_buf )
			RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));

	}
	else
	{
		//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
		if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
		{
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);

			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
			//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
		}
	}
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}

	if(oob_buf)
	{
		//printf("new:[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
		if(this->ecc_select==0x18||this->ecc_select==0xc||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
			reverse_to_Tags(oob_buf,this->ecc_select);
		else
		{
			//printf("new:[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);
			REG_WRITE_U32(REG_READ_BY_PP,0x00);
			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
			else
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
			rtk_read_oob_from_SRAM(mtd, oob_buf);
			REG_WRITE_U32(REG_SRAM_CTL, 0x00);
			REG_WRITE_U32(REG_READ_BY_PP,0x80);

			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				reverse_to_Tags(oob_buf,this->ecc_select);
		}
	}
//oobReadCnt++;
//printk("\t oob read cnt %u\n",oobReadCnt);
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK)>>1) & 0x01;
	if (blank_all_one)
	{
		if(this->erase_page_flag)
		this->erase_page_flag[chip_section+section] =  (1<< index);
	}
	//printf("[%s] [%d]test code, rc = %d\n", __FUNCTION__,__LINE__,rc);

	if(blank_all_one == 1){
		// return OK if all data bit is 1 (page is not written yet)
		return 0;
	}

	if (REG_READ_U32(REG_ND_ECC) & 0x0C){
				if(!this->erase_page_flag)
				{
					if (REG_READ_U32(REG_ND_ECC) & 0x08){
						if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
						{
							//up (&sem_NF_CARDREADER);
							return 0;
						}
						else
						{
							//up (&sem_NF_CARDREADER);
							printk("[%s][%d]blk %d, page %d fail\n",__FUNCTION__,__LINE__,page/ppb,page%ppb);
							return -1;
						}
					}
				}
				else
				{
					if (this->erase_page_flag[chip_section+section] & (1<< index) ){
						;
					}else
					{
						if (REG_READ_U32(REG_ND_ECC) & 0x08){
							if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
							{
								//up (&sem_NF_CARDREADER);
								return 0;
							}
							else
							{
								//up (&sem_NF_CARDREADER);
								printk("[%s][%d]blk %d, page %d fail\n",__FUNCTION__,__LINE__,page/ppb,page%ppb);
								return -1;
							}
						}
					}
				}
			}

	mtd->isCPdisable_R = 0;
	//printf("[%s] [%d]test code, rc = %d::::[oob_buf0=%x]\n", __FUNCTION__,__LINE__,rc,oob_buf[0]);
	//up (&sem_NF_CARDREADER);
	return rc;
}

//----------------------------------------------------------------------------
static int rtk_read_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf)
{
//static unsigned int eccReadCnt = 0;
	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;

	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;

	//printf("mtd = %x|chipnr = %d|page =0x%x|data_buf =%x|oob_buf =%x\n",mtd, chipnr,page,data_buf,oob_buf);
	//printf("page_size = %x|oob_size =%x|ppb = %x\n",page_size,oob_size,ppb);
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);
#if 0
	while (down_interruptible (&sem_NF_CARDREADER)) {
		printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
		if(retryCnt<=0)
		{
			printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
			return -ERESTARTSYS;
		}
		retryCnt--;
	}
#endif

        if(((uint32_t)data_buf&0x7)!=0)
        {
                printf("[%s]data_buf must 8 byte alignmemt!!\n",__FUNCTION__);
                BUG();
        }
#if 0
	if ( chipnr == 0 && page < (g_BootcodeSize+g_Factory_param_size)/page_size+ppb )
	{
		  printf("[%s][%d]test code!!\n",__FUNCTION__,__LINE__);
                mtd->isCPdisable_R = 1;
                mtd->isScramble=MTD_SCRAMBLE_DISABLE;
	}
#endif

	//-------------------set random mode -----------------------
	if (nf_is_random_mode()){
		nf_set_random_read(mtd->oobblock, 0);
	}

	if(g_enReadRetrial)
	{
		if(!oob_buf)
		{
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,data_buf,this->g_oobbuf);
		}
		else
			rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,data_buf,oob_buf);
		//up(&sem_NF_CARDREADER);
		return rc;
	}
	//if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
	//	mtd->isCPdisable_R = 1;

#if 0
	if ( chipnr == 0 && page < (g_BootcodeSize+g_Factory_param_size)/page_size+ppb )
		mtd->isCPdisable_R = 1;
#endif

	if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
	{
		if(!oob_buf)
		{
			rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,this->g_oobbuf);
		}
		else
			rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,oob_buf);
		//up(&sem_NF_CARDREADER);
		return rc;
	}

	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));

	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
	}
	REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));
	REG_WRITE_U32(REG_PP_CTL0,0);

 	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
 		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//dram_sa = ( (uint32_t)data_buf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(data_buf)) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	if (oob_buf){
		//spare_dram_sa = ( (uint32_t)oob_buf >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(oob_buf)) >> 3);
	}else{
		//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(this->g_oobbuf)) >> 3);
	}

	//patch
	RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
	if ( oob_buf )
		RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
	else
		RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);

	if(is_jupiter_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL,(0x7<<26) | (spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
//printk("[%s]Ran 0x%x, scr 0x%x, flag 0x%x\n",__FUNCTION__,g_isRandomize,mtd->isScramble,mtd->isCPdisable_R);
	if(g_isRandomize&&(!mtd->isCPdisable_R))
	{

		if(u32CP_mode==0)//CBC initial key setting.
        {
                REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
        }
		REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

		REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));

		RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
		if ( oob_buf )
			RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
		else
			RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
	}
	else
	{
		if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
		{
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			else
				RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			else
				RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}

	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif
	if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}

	if(oob_buf)
	{
		if(this->ecc_select==0x18||this->ecc_select==0x0c||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
		{
			if(mtd->ecctype!=MTD_ECC_RTK_HW)
				reverse_to_Tags(oob_buf,this->ecc_select);
			else
			{
				REG_WRITE_U32(REG_READ_BY_PP,0x00);
				#if 1
				if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
				else
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
				#else
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
				#endif
				rtk_read_oob_from_SRAM(mtd, oob_buf);
				REG_WRITE_U32(REG_SRAM_CTL, 0x00);
				REG_WRITE_U32(REG_READ_BY_PP,0x80);
			}
		}
		else
		{
			REG_WRITE_U32(REG_READ_BY_PP,0x00);
			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
			else
				REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
			rtk_read_oob_from_SRAM(mtd, oob_buf);
			REG_WRITE_U32(REG_SRAM_CTL, 0x00);
			REG_WRITE_U32(REG_READ_BY_PP,0x80);

			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())
				reverse_to_Tags(oob_buf,this->ecc_select);
		}
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK)>>1) & 0x01;

	// add by alexchang 01-28-2011
	mtd->nEccMaxValue = REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM));
	if (blank_all_one)
	{
		if(this->erase_page_flag)
		this->erase_page_flag[chip_section+section] =  (1<< index);
	}

	if(blank_all_one == 1){
		// return OK if all data bit is 1 (page is not written yet)
		return 0;
	}

	if (REG_READ_U32(REG_ND_ECC) & 0x0C){
				if(!this->erase_page_flag)
				{
					if (REG_READ_U32(REG_ND_ECC) & 0x08){
						if ( chipnr == 0 && page < g_BootcodeSize/page_size )
						{
							//up (&sem_NF_CARDREADER);
							return 0;
						}
						else
						{
							//up (&sem_NF_CARDREADER);
							return -1;
						}
					}
				}
				else
				{
					if (this->erase_page_flag[chip_section+section] & (1<< index) ){
						;
					}else
					{
						if (REG_READ_U32(REG_ND_ECC) & 0x08){
							if ( chipnr == 0 && page < g_BootcodeSize/page_size )
							{
								//up (&sem_NF_CARDREADER);
								return 0;
							}
							else
							{
								//up (&sem_NF_CARDREADER);
								return -1;
							}
						}
					}
				}
			}


#if RTK_ARD_ALGORITHM
	g_WinTrigCnt++;
//	printk("mtd->erasesize %u  mtd->oobblock %u\n",mtd->erasesize,mtd->oobblock);
//	printk("ppb %u \n",ppb);
	whichBlk = page / ppb;
	g_RecArray[whichBlk]++;
	if(g_WinTrigCnt > g_WinTrigThrshld)
		travelProcWindow();
#endif
	mtd->isCPdisable_R = 0;
	//up (&sem_NF_CARDREADER);
	//printk("R blk:%u, page:%u\n",page/ppb,page%ppb);
	return rc;
}

//----------------------------------------------------------------------------
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *oob_buf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;
	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	unsigned char oob_1stB;
	unsigned int chip_section = 0;
	unsigned int section =0;
	unsigned int index =0;
	unsigned int retryCnt = RETRY_COUNT;
	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	memset(this->g_databuf, 0xff, page_size);

	page_size = mtd->oobblock;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->oobblock;
#if 0
	while (down_interruptible (&sem_NF_CARDREADER)) {
		printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
			if(retryCnt<=0)
			{
				printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
				return -ERESTARTSYS;
			}
			retryCnt--;
	}

	if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size ){
		printk("[%s] You have no permission to write this page %d\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		return -2;
	}
#endif

	if ( len>oob_size || !oob_buf ){
		printk("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		return -1;
	}

	//----------------set random mode --------------------
	if (nf_is_random_mode()){
		nf_set_random_write(mtd->oobblock,0);
	}

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		// no audio pin-type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_dis);
				break;
			#endif
				
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_dis);//Set Value
					break;
			}
            		REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3));
            		REG_WRITE_U32( REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(0x07)|NF_POLL_FSTS_trig_poll(1));
            		WAIT_DONE(REG_POLL_FSTS,0x1,0);
		}
	}

#ifdef CONFIG_MTD_NAND_IBT
		if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
			oob_1stB = BBT_TAG;
		else if(( page>=IBT_BLOCK_ADDR*ppb )&&(page<(IBT_BAK_BLOCK_ADDR+1)*ppb)){
			oob_1stB =IBT_TAG;
		}else if(page<g_BootcodeSize/page_size ){
			if(oob_buf)
				oob_1stB = oob_buf[0];
			else
				oob_1stB = 0xFF;
		}else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Secure_store_Size)/page_size))
			oob_1stB = 0xFF;
		else if((page>=(g_BootcodeSize+g_Secure_store_Size)/page_size) && \
				(page<(g_BootcodeSize+g_Secure_store_Size+g_Factory_param_size+g_Factory_ro_param_size)/page_size))
			oob_1stB = TAG_FACTORY_PARAM;		//test code
		else
			oob_1stB = 0xFF;
#else
		if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
			oob_1stB = BBT_TAG;
		else if(page<g_BootcodeSize/page_size ){
			if(oob_buf)
				oob_1stB = oob_buf[0];
			else
				oob_1stB = 0xFF;
		}else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Secure_store_Size)/page_size))
			oob_1stB = 0xFF;
		else if((page>=(g_BootcodeSize+g_Secure_store_Size)/page_size) && \
			(page<(g_BootcodeSize+g_Secure_store_Size+g_Factory_param_size+g_Factory_ro_param_size)/page_size))
			oob_1stB = TAG_FACTORY_PARAM;		//test code
		else
			oob_1stB = 0xFF;
#endif

//end of alexchang 0208-2010
	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32(REG_SRAM_CTL,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
 	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	REG_WRITE_U32( REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
 		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

 	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//dram_sa = ( (uint32_t)this->g_databuf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(this->g_databuf )) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	//spare_dram_sa = ( (uint32_t)oob_buf >> 3);
	spare_dram_sa = (((unsigned int)PHYSADDR(oob_buf)) >> 3);

	if(is_jupiter_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL,(0x7<<26) | (spare_dram_sa&0x3ffffff));
	else
	REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_AUTO_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
#endif
	if(g_isRandomize&&(!mtd->isCPdisable_W))
	{
		if(mtd->isScramble!=MTD_SCRAMBLE_DISABLE)
		{
			//printk("&");
			if(u32CP_mode==0)//CBC initial key setting.
			{
					REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
			}
			REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);


			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			//add by alexchang 0208-2010
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			//printk("%");
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}
	else
	{
		if(is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))
		{//printk("#");
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);


			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			//add by alexchang 0208-2010
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{//printk("@");
			//add by alexchang 0208-2010
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
#endif

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		// no audio pin type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_en);
				break;
			#endif
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_en);//Set Value
				break;
			}
		}
	}

	if((is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}

	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printk("[%s] write oob is not completed at page %d\n", __FUNCTION__, page);

		return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	mtd->isCPdisable_W = 0;
	//printk("[AT]WO block : %u ,page : %d  \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);
//int k= 0;
//for(k=0;k<32;k++)
//printk("[WO][%u,%u][%d]0x%x\n",page/ppb,page%ppb,k,oob_buf[k]);
//printk("----------------------------\n");

	return rc;
}

//----------------------------------------------------------------------------
//char bbbbb[4096];
unsigned char nf_oob_buf_temp[64*4];		//allocate
static int rtk_write_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data_buf, const  u_char *oob_buf, int isBBT)
{
	unsigned int ppb = mtd->erasesize/mtd->oobblock;
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;
	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	unsigned char oob_1stB;
	unsigned char *nf_oob_buf = (unsigned long)nf_oob_buf_temp-(unsigned long)nf_oob_buf_temp%8+8;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int i,retryCnt = RETRY_COUNT;

        if(((uint32_t)data_buf&0x7)!=0)
        {
                printf("[%s]data_buf must 8 byte alignmemt!![data_buf = %x]\n",__FUNCTION__,data_buf);
                BUG();
        }
        if(((uint32_t)oob_buf&0x7)!=0)
        {
                printf("[%s]oob_buf must 8 byte alignmemt!![oob_buf = %x]\n",__FUNCTION__,oob_buf);
                BUG();
        }
	if(((uint32_t)nf_oob_buf&0x7)!=0)
        {
                printf("[%s]oob_buf must 8 byte alignmemt!![oob_buf = %x]\n",__FUNCTION__,oob_buf);
                BUG();
        }

	memset(nf_oob_buf, 0xff, oob_size);
	//----------------set random mode --------------------
	if (nf_is_random_mode()){
		nf_set_random_write(mtd->oobblock,0);
	}

#if 0
	if ( chipnr == 0 && page < g_BootcodeSize/page_size ){
		if ( isBBT && page<3*ppb ){
			printf("[%s] &&&&&&&Updating BBT %d page=%d\n", __FUNCTION__, page/ppb, page%ppb);
		}
		else
		{
			printf("[%s] You have no permission to write page %d\n", __FUNCTION__, page);
			//up (&sem_NF_CARDREADER);
			return -2;
		}
		mtd->isCPdisable_W = 1;
	}

	if ( chipnr == 0 && page >= g_BootcodeSize/page_size){
		if(page<(g_BootcodeSize+g_Factory_param_size)/page_size+ppb)
		{
			  mtd->isCPdisable_W = 1;
		}
	}
#endif

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		// no audio pin-type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_dis);
				break;
			#endif
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_dis);//Set Value
					break;
			}
            		REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3));
           		REG_WRITE_U32( REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(0x07)|NF_POLL_FSTS_trig_poll(1));
            		WAIT_DONE(REG_POLL_FSTS,0x1,0);
		}
	}

#ifdef CONFIG_MTD_NAND_IBT
	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(( page>=IBT_BLOCK_ADDR*ppb )&&(page<(IBT_BAK_BLOCK_ADDR+1)*ppb)){
		oob_1stB =IBT_TAG;
	}else if(page<g_BootcodeSize/page_size ){
		if(oob_buf)
			oob_1stB = oob_buf[0];
		else
			oob_1stB = 0xFF;
	}else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Secure_store_Size)/page_size))
		oob_1stB = 0xFF;
	else if((page>=(g_BootcodeSize+g_Secure_store_Size)/page_size) && \
		(page<(g_BootcodeSize+g_Secure_store_Size+g_Factory_param_size+g_Factory_ro_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;		//test code
	else
		oob_1stB = 0xFF;
#else
	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(page<g_BootcodeSize/page_size ){
		if(oob_buf)
			oob_1stB = oob_buf[0];
		else
			oob_1stB = 0xFF;
	}else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Secure_store_Size)/page_size))
		oob_1stB = 0xFF;
	else if((page>=(g_BootcodeSize+g_Secure_store_Size)/page_size) && \
		(page<(g_BootcodeSize+g_Secure_store_Size+g_Factory_param_size+g_Factory_ro_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;		//test code
	else
		oob_1stB = 0xFF;
#endif
	//REG_WRITE_U32(0xb801032c,0x01);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010

	if ( oob_buf )	{
		int i,j;
		//memset(nf_oob_buf,0xff,oob_size);
		nf_oob_buf[0] = oob_1stB;

		if(this->ecc_select == 0x18)
		{
			for(i=1,j=0; i<8; i++)
			{
				nf_oob_buf[8*i] = oob_buf[j];
				nf_oob_buf[8*i+1] = oob_buf[j+1];
				nf_oob_buf[8*i+2] = oob_buf[j+2];
				nf_oob_buf[8*i+3] = oob_buf[j+3];
				j+=4;
			}
		}
		else
		{
			for(i=0; i<4; i++)
				nf_oob_buf[1+i] = oob_buf[i];
			for(i=2,j=4; i<8; i+=2)
			{
				nf_oob_buf[4*i] = oob_buf[j];
				nf_oob_buf[4*i+1] = oob_buf[j+1];
				nf_oob_buf[4*i+2] = oob_buf[j+2];
				nf_oob_buf[4*i+3] = oob_buf[j+3];
				j+=4;
			}
		}
	}else
		nf_oob_buf[0] = oob_1stB;

	REG_WRITE_U32(REG_SRAM_CTL,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
 	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32( REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));
	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
 		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));


 	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(0));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

	//dram_sa = ( (uint32_t)data_buf >> 3);
	dram_sa = (((unsigned int)PHYSADDR(data_buf)) >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));

	if (oob_buf){
		//spare_dram_sa = ( (uint32_t)nf_oob_buf >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(nf_oob_buf)) >> 3);
	}else{
		//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
		spare_dram_sa = (((unsigned int)PHYSADDR(this->g_oobbuf)) >> 3);
	}


	//patch
	RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
	RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);

	if(is_jupiter_cpu())
		REG_WRITE_U32(REG_SPR_DDR_CTL, (0x7<<26) | (spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32(REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_AUTO_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
#endif
	//printk("11[%s]Ran 0x%x, scr 0x%x, flag 0x%x\n",__FUNCTION__,g_isRandomize,mtd->isScramble,mtd->isCPdisable_W);

	if(g_isRandomize&&(!mtd->isCPdisable_W))
	{
//		if(mtd->isScramble!=MTD_SCRAMBLE_DISABLE)
//		{
			//printk("$");
			if(u32CP_mode==0)//CBC initial key setting.
			{
					REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
			}
			REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
//		}
//		else
//		{//printk("=");
//			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
//			RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);
//			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
//		}
	}
	else
	{
		if(is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))
		{//printk("+");
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{//printk("-");
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));


#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
#endif

	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_sirius_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
			#if 0		//no audio pin type
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_en);
				break;
			#endif
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_en);//Set Value
				break;
			}
		}
	}

	if((is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))||g_isRandomize)//Clear register
	{
			//REG_WRITE_U32(REG_CP_NF_SET,0);
	}


	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printf("[%s] write is not completed at page %d\n", __FUNCTION__, page);
		return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);

	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	mtd->isCPdisable_W = 0;
	//printk("[AT]W block : %u , page: %u \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);
#if 0
	//char *ppptr = (unsigned long)bbbbb-(unsigned long)bbbbb%8+8;
	char *ppptr;
	ppptr = (char *)malloc(2048);
	memset(ppptr , 0x00, 2048);
	rtk_read_ecc_page (mtd, chipnr, page, ppptr, oob_buf);
	if(memcmp(ppptr,data_buf, 2048))
		{
			int i, count=0;
			for(i=0;i<2048;i++)
		 		if(ppptr[i] != data_buf[i])
				 count++;
				printf("Data compare error! %d %x %x %x %p\n", count, ppptr[0],
				ppptr[1], ppptr[2], ppptr); //BUG();

				for(i = 0; i< 2048; i++){
						if((i%16)==0)
							printk("\n");

						printk("0x%x\t", data_buf[i]);
					}

				printf("\n----------------------------------------line-------------------------------------\n");
				for(i = 0; i< 2048; i++){
						if((i%16)==0)
							printk("\n");

						printk("0x%x\t", ppptr[i]);
					}




				}
	else
		printf("write check OK!\n");

	free(ppptr);
#endif

	//printf("[%s][%d] rc = %d\n", __FUNCTION__, __LINE__,rc);
	return rc;
}

//----------------------------------------------------------------------------
static int rtk_nand_profile (struct mtd_info *rtk_mtd)
{
	int maxchips = 4;
	struct nand_chip *this = (struct nand_chip *)rtk_mtd->priv;
	int retRba=0;

	rtk_mtd->u32RBApercentage = this->RBA_PERCENT = RBA_PERCENT;		//default value 5%
	printf("[**Default**]RBA percentage: %d%%\n",this->RBA_PERCENT);

#ifdef CONFIG_MTD_NAND_IBT
	this->I_KERNEL_RBA_PERCENT = I_KERNEL_RBA_PERCENT;		//default value 1%
	printf("[**Default**]IBT-RBA percentage of kernel-area: %d%%\n",this->I_KERNEL_RBA_PERCENT);

	this->I_BOOTCODE_RBA_PERCENT = I_BOOTCODE_RBA_PERCENT;		//default value 10% of bootcode-area
	printf("[**Default**]IBT-RBA percentage of bootcode-area: %d%%\n", this->I_BOOTCODE_RBA_PERCENT);
#endif

	if (rtk_nand_scan (rtk_mtd, maxchips) < 0 || rtk_mtd->size == 0){
		printf("%s: Error, cannot do nand_scan(on-board)\n", __FUNCTION__);
		return -ENODEV;
	}

	if ( !(rtk_mtd->oobblock&(0x200-1)) )
		REG_WRITE_U32( REG_PAGE_LEN,rtk_mtd->oobblock >> 9);
	else{
		printk("Error: pagesize is not 512B Multiple");
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------
void endian_swap(unsigned int* x)
{
	*x = (*x>>24) |((*x<<8) & 0x00FF0000) |((*x>>8) & 0x0000FF00) |(*x<<24);
}

static int nf_ctrler_init()
{
	int count;

	/*******************************
	 * init NAND flash start
	 *******************************/
	// setup nf controller frequency
	REG_WRITE_U32(0xb8010234,0x2);
	REG_WRITE_U32(0xb8010238,0x2);
	REG_WRITE_U32(0xb801023c,0x2);

	// setup T_WHR_ADL delay clock
	REG_WRITE_U32(0xb8010260,0x9);

	// disable all interrupt from nf controller
	REG_WRITE_U32(0xb8010328,0x1);


#if 0
	// enable spare DMA to DDR (8B unit)
	REG32(REG_SPR_DDR_CTL) = 0x30000000 | (PHYS(SPARE_DMA_ADDR) >> 3);
#else
	REG_WRITE_U32(0xb8010348,~0x20000000);
#endif

	// determine PP SRAM mapping endian in 0xb8010300[5]
	map_sel = 0x1 << 5;	// little endian
	//map_sel = 0x0 << 5;	// big endian

	/*******************************
	 * reset NAND flash start
	 *******************************/
	REG_WRITE_U32(0xb8010130,0x0);

	// set 'reset' command
	REG_WRITE_U32(0xb8010010,0xff);

	// issue command
	REG_WRITE_U32(0xb8010018,0x80);

	// polling go bit to until go bit de-assert (command completed)
	count = 0;
	while ( REG_READ_U32(0xb8010018) & 0x80) {
		count++;
		if (count == 0x10000)
			return -1;	// time-out
	}

	// check ready/busy pin of NAND flash
	count = 0;
	while ((REG_READ_U32(0xb8010018)&0x40) == 0) {
		count++;
		if (count == 0x10000)
			return -1;	// time-out
	}

	return 0;
}

//----------------------------------------------------------------------------
static int  rtk_nand_init (struct mtd_info *rtk_mtd)
{
	struct nand_chip *this=(struct nand_chip *)rtk_mtd->priv;
	int rc = 0;
	unsigned int temp;
	unsigned long long pin_WP_info;

	//switch dst address from sram to ddr
	//REG32(0xb801035c) &= ~0x1;
	temp = REG_READ_U32(0xb801035c)&(~0x1);
	REG_WRITE_U32(0xb801035c,temp);
	//init nf controler
	nf_ctrler_init();

	if(nf_is_random_mode()){
		printf("Nand flash : Random access mode!\n");
	}else{
		printf("Nand flash : Sequential access mode!\n");
	}

#ifdef CONFIG_MTD_NAND_IBT
	printf("ibt open......\n");
#endif

	//default value
	g_BootcodeSize = SYS_PARAM_BOOTCODE_SIZE;
	g_Secure_store_Size = SYS_PARAM_SECURE_STORE_SIZE;
	g_Factory_param_size = SYS_PARAM_FACTORY_SIZE;
	g_Factory_ro_param_size = SYS_PARAM_FACTORY_RO_SIZE;

	//wp setting
	//g_WP_en = rtkNF_getWPSettingval();
	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu()||is_magellan_cpu()||is_sirius_cpu())
	{
		if(is_sirius_cpu()){
			g_regGPIODirBase = 0xb801b100;
		}else{
			g_regGPIODirBase = 0xb801bc00;
		}

		if(is_sirius_cpu()){
			g_regGPIOOutBase = 0xb801b11c;
		}else{
			if(is_macarthur2_cpu())
				g_regGPIOOutBase = 0xb801bc18;
			else
				g_regGPIOOutBase = 0xb801bc14;
		}
		
	
//#if defined(CONFIG_REALTEK_PCBMGR)
#if defined(PIN_FLASH_WP_STRING)
    #if 0
		if(pcb_mgr_get_enum_info_byname("PIN_FLASH_WP",&pin_WP_info)!=0)
		{
			g_WP_en = 0;
			printk("PIN_FLASH_WP is not defined\n");
		}
        else
    #endif
		{
            
            pin_WP_info = simple_strtoull(PIN_FLASH_WP_STRING,NULL,16);;
			g_WP_en = 1;
			printk("PIN_FLASH_WP defined value 0x%llx\n",pin_WP_info);
	
			g_NFWP_no = ((unsigned char) ((pin_WP_info >> 8) & 0xFF));
			g_NFWP_value_INV = ((unsigned char) ((pin_WP_info >> 24) & 0xFF));
			g_NFWP_pinType = (PCB_PIN_TYPE_T) (pin_WP_info & 0xFF);
			if(g_NFWP_pinType==4 && is_macarthur2_cpu())
			{
				g_regGPIODirBase = 0xB8061100;
				g_regGPIOOutBase = 0xB8061108;		
			}
            
            if(is_sirius_cpu())
            {
                g_regGPIODirBase = 0xb801b100;
                g_regGPIOOutBase = 0xb801b11c;
            }
            
			if(is_darwin_cpu())
			{
				if(g_NFWP_value_INV==0)
				{
					g_NFWP_value_en = 1;
					g_NFWP_value_dis = 0;
				}else{
					g_NFWP_value_en = 0;
					g_NFWP_value_dis = 1;
				}
	
			}else{
				if(g_NFWP_value_INV==0)
				{
					g_NFWP_value_en = 0;
					g_NFWP_value_dis = 1;
				}else{
					g_NFWP_value_en = 1;
					g_NFWP_value_dis = 0;
				}
			}
		}
#else
		 printk("Force disable FLASH_WP!!\n");
		 g_WP_en=0;
#endif
		printk("g_regGPIODirBase = 0x%x\n",g_regGPIODirBase);
		printk("g_regGPIOOutBase = 0x%x\n",g_regGPIOOutBase);
		printk("g_NFWP_no = %d\n",g_NFWP_no);
		printk("g_NFWP_value_en = %d\n",g_NFWP_value_en);
		printk("g_NFWP_value_dis = %d\n",g_NFWP_value_dis);
		printk("g_NFWP_pinType = %d\n",g_NFWP_pinType);
	}

	this->read_id		= rtk_nand_read_id;
	this->read_ecc_page 	= rtk_read_ecc_page;
	this->read_oob 		= rtk_read_oob;
	this->write_ecc_page	= rtk_write_ecc_page;
	this->write_oob		= rtk_write_oob;

#ifdef CONFIG_MTD_NAND_IBT
	this->read_oob_ibt 	= rtk_read_oob_ibt;
#endif

	this->erase_block 	= rtk_erase_block;
	this->suspend		= rtk_nand_suspend;
	this->resume		= rtk_nand_resume;
	this->sync		= NULL;

	if( rtk_nand_profile(rtk_mtd) < 0 ){
		rc = -1;
		return rc;
	}

	g_NF_pageSize = page_size = rtk_mtd->oobblock;
	oob_size = rtk_mtd->oobsize;
	ppb = (rtk_mtd->erasesize)/(rtk_mtd->oobblock);

	return rc;
}

int board_nand_init(struct mtd_info *mtd)
{
	int rc = 0;
	if((mtd==NULL)||(mtd->priv == NULL))
	{
		printf(" error: board nand init failed!\n");
		rc = -1;
		return rc;

	}

	rc = rtk_nand_init (mtd);

	if(rc == 0)
		printf("Realtek Nand Flash Driver is successfully installing.\n");

	return rc;
}

