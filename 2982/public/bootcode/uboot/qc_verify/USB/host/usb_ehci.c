


#include <common.h>
#include "linux/compat.h"
#include <asm/arch/system.h>
#include <rtd_types_qc.h>


//--#include <linux/compiler.h>
#include <linux/list.h>



#include <asm/byteorder.h>
//#include <asm/addrspace.h>
#include <usb/usb.h>

#include <asm/errno.h>

#include "usb_ehci.h"
#include "rtd_usb.h"

#include <usb/hub.h>




//must check physical address
#define KSEG_MSK		  0xE0000000


// arm cpu must modify
#if 1
#define KSEG0BASE		  0x00000000
#define KSEG1BASE		  0x00000000
#else
//#define KSEG0BASE		  0x80000000
//#define KSEG1BASE		  0xA0000000
#endif


#ifdef _ASSEMBLER_
#define PHYS(addr)      ( (addr) & ~KSEG_MSK)
#define KSEG0(addr)     (((addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((addr) & ~KSEG_MSK)  | KSEG1BASE)

#else
#define PHYS(addr) 	((UINT32)(addr)  & ~KSEG_MSK)
#define KSEG0(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG1BASE)

#endif

#define CPHYSADDR(addr)	PHYS(addr)
#define KSEG0ADDR(addr)	KSEG0(addr)
#define KSEG1ADDR(addr)	KSEG1(addr)



#define __sync() 	//do {REG32(KSEG1(MAGIC_SYNC_ADDRESS)) = 0; } while(0)

#define sys_dcache_flush_and_invalidate_all flush_dcache_all

// extern int __test_start;
/* Initial IRQ latency:  faster than hw default */
static int log2_irq_thresh = 5;		// 0 to 6

#define min_t(type,x,y) ({ type __x = (x); type __y = (y); __x < __y ? __x: __y; })
#define OK(x) 			len = (x); break

static void ehci_work(struct ehci_hcd *ehci);
static struct ehci_qh *qh_make (struct ehci_hcd *ehci,struct urb *urb,unsigned long pipe);
static int ehci_reset (struct ehci_hcd *ehci);
static inline void ehci_qtd_free (struct ehci_hcd *ehci, struct ehci_qtd *qtd);
static int handshake (void __iomem *ptr, u32 mask, u32 done, int usec);
static void qtd_list_free (struct ehci_hcd *ehci,struct urb *urb,struct list_head *qtd_list);
static inline void ehci_qtd_init (struct ehci_qtd *qtd, dma_addr_t dma);

#undef EHCI_VERBOSE_DEBUG
// #define EHCI_VERBOSE_DEBUG	1
#undef EHCI_URB_TRACE
// #define EHCI_URB_TRACE	1

#define ehci_err		printk

#ifdef DEBUG
#define EHCI_STATS
#endif

#undef DEBUG
// #define DEBUG	1

#ifdef DEBUG
#define dbg(format, arg...) printk("DEBUG: " format "\n", ## arg)
#define ehci_dbg(addr, format, arg...) printk("DEBUG: " format "\n", ## arg)
#else
#define dbg(format, arg...) do {} while(0)
#define ehci_dbg(addr, format, arg...) do {} while(0)
#endif /* DEBUG */

#define err(format, arg...) printk("ERROR: " format "\n", ## arg)

#undef SHOW_INFO
// #define SHOW_INFO	1

#ifdef SHOW_INFO
#define info(format, arg...) printk("INFO: " format "\n", ## arg)
#else
#define info(format, arg...) do {} while(0)
#endif

#define m16_swap(x) swap_16(x)
#define m32_swap(x) swap_32(x)


/* magic numbers that can affect system performance */
#define	EHCI_TUNE_CERR		3	/* 0-3 qtd retries; 0 == don't stop */
#define	EHCI_TUNE_RL_HS		4	/* nak throttle; see 4.9 */
#define	EHCI_TUNE_RL_TT		0
#define	EHCI_TUNE_MULT_HS	1	/* 1-3 transactions/uframe; 4.10.3 */
#define	EHCI_TUNE_MULT_TT	1
#define	EHCI_TUNE_FLS		2	/* (small) 256 frame schedule */

#define EHCI_IAA_JIFFIES	(10*100)	/* arbitrary; ~10 msec */
#define EHCI_IO_JIFFIES		(100*100)		/* io watchdog > irq_thresh */
#define EHCI_ASYNC_JIFFIES	(200*100)		/* async idle timeout */
#define EHCI_SHRINK_JIFFIES	(2000*100)	/* async qh unlink delay */

#define	INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

#ifdef readl
#undef readl
#endif

#ifdef writel
#undef writel
#endif

#define readl(addr)			rtd_inl(addr)
#define writel(val,addr) 	rtd_outl(addr,val)


static struct ehci_hcd rtd_ehci;

/* This allocates QHs for all possible endpoints */
static   struct ehci_device ehci_dev;

static   struct ehci_device *pehci_dev;

/* urb_priv */
static struct urb urb_priv __attribute__ ((aligned (512)));
static struct urb *purb_priv;
/* RHSC flag */
static int got_rhsc;

static struct ehci_qh ehci_head_qh;
/* device which was disconnected */
static struct usb_device *devgone;
static struct ehci_qtd	dummy_qtd;


/* +1 so we can align the storage */
static  struct ehci_qtd g_qtd[NUM_QTD+1];
/* pointers to aligned storage */
static  struct ehci_qtd *p_qtd;

#ifdef DEBUG
static inline void dbg_status(struct ehci_hcd *ehci, const char *label, u32 status) {
	char buf[80];
	sprintf(buf, "%s%sstatus %04x%s%s%s%s%s%s%s%s%s%s",
		label, label [0] ? " " : "", status,
		(status & STS_ASS) ? " Async" : "",
		(status & STS_PSS) ? " Periodic" : "",
		(status & STS_RECL) ? " Recl" : "",
		(status & STS_HALT) ? " Halt" : "",
		(status & STS_IAA) ? " IAA" : "",
		(status & STS_FATAL) ? " FATAL" : "",
		(status & STS_FLR) ? " FLR" : "",
		(status & STS_PCD) ? " PCD" : "",
		(status & STS_ERR) ? " ERR" : "",
		(status & STS_INT) ? " INT" : ""
		);
	//printf(buf);
	ehci_dbg(ehci, "%s\n", buf);
}


/* cyhuang : Debug */
static void dbg_echi_dump_qtd(struct ehci_qtd *qtd)
{
	printk("@@ qtd 0x%x @@\n", (u32)qtd);
	printk("   hw_next\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_next));
	printk("   hw_alt_next\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_alt_next));
	printk("   hw_token\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_token));
	printk("   hw_buf[0]\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_buf[0]));
	printk("   hw_buf[1]\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_buf[1]));
	printk("   hw_buf[2]\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_buf[2]));
	printk("   hw_buf[3]\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_buf[3]));
	printk("   hw_buf[4]\t0x%x\n", (u32)le32_to_cpup(&qtd->hw_buf[4]));
}

static void dbg_echi_dump_qh(struct ehci_qh *qh)
{
	struct ehci_hcd *ehci = &rtd_ehci;
	
	printk("@@ ehci->regs->async_next = 0x%x , ehci->async = 0x%x\n",ehci->regs->async_next,(u32)ehci->async);
	printk("@@ qh 0x%x @@\n", (u32)qh);
	printk("   hw_next\t0x%x\n", (u32)le32_to_cpup(&qh->hw_next));
	printk("   hw_info1\t0x%x\n", (u32)le32_to_cpup(&qh->hw_info1));
	printk("   hw_info2\t0x%x\n", (u32)le32_to_cpup(&qh->hw_info2));
	printk("   hw_current\t0x%x\n", (u32)le32_to_cpup(&qh->hw_current));
	printk("   hw_qtd_next\t0x%x\n", (u32)le32_to_cpup(&qh->hw_qtd_next));
	printk("   hw_alt_next\t0x%x\n", (u32)le32_to_cpup(&qh->hw_alt_next));
	printk("   hw_token\t0x%x\n", (u32)le32_to_cpup(&qh->hw_token));
	printk("   hw_buf[0]\t0x%x\n", (u32)le32_to_cpup(&qh->hw_buf[0]));
	printk("   hw_buf[1]\t0x%x\n", (u32)le32_to_cpup(&qh->hw_buf[1]));
	printk("   hw_buf[2]\t0x%x\n", (u32)le32_to_cpup(&qh->hw_buf[2]));
	printk("   hw_buf[3]\t0x%x\n", (u32)le32_to_cpup(&qh->hw_buf[3]));
	printk("   hw_buf[4]\t0x%x\n", (u32)le32_to_cpup(&qh->hw_buf[4]));
		
}

static void dbg_echi_dump_all_qh(struct ehci_qh *qh)
{	
	
	struct list_head	*entry, *tmp;
	struct ehci_qtd	*qtd=NULL;
		
				
	while(qh) {		
				
		dbg_echi_dump_qh(qh);
		
		list_for_each_safe (entry, tmp, &qh->qtd_list) {
						
			qtd = list_entry (entry, struct ehci_qtd, qtd_list);
			if (qtd)
				dbg_echi_dump_qtd(qtd);	
		}	
								
		qh = qh->qh_next.qh;
		
		
		if (!((u32)qh >= 0xa0000000 && (u32)qh <= 0xa2000000)) {
			/*
			while(1) {
				printk("Error : qh = 0x%x\n",qh);
				if (qh >= 0xa0000000 && qh <= 0xa2000000)
					break;
			}
			*/
			break;
		}
			
	}
	
	if (qtd)
#ifdef ENABLE_KSEG1ADDR
		dbg_echi_dump_qtd((struct ehci_qtd *) KSEG1ADDR(le32_to_cpup(&qtd->hw_next)));	
#else /* ENABLE_KSEG1ADDR */
		dbg_echi_dump_qtd((struct ehci_qtd *) KSEG0ADDR(le32_to_cpup(&qtd->hw_next)));	
#endif /* ENABLE_KSEG1ADDR */
	
	// udelay(1000*1000*10);
	
}


/* tell us the current USB frame number */
static int sehci_get_current_frame_number (struct usb_device *usb_dev)
{
/*
	ohci_t *ohci = &gohci;

	return m16_swap (ohci->hcca->frame_no);
*/
	return (int)usb_dev;
}

/* debug| print the main components of an URB
 * small: 0) header + data packets 1) just header */

static void pkt_print (struct usb_device * dev, unsigned long pipe, void * buffer,
	int transfer_len, struct devrequest * setup, char * str, int small)
{
	struct urb *purb = &urb_priv;

	dbg("%s URB:[0x%x] dev:%ld,ep:%ld-%c,type:%s,len:%d/%d stat:0x%x#x",
			str,
			sehci_get_current_frame_number (dev),
			usb_pipedevice (pipe),
			usb_pipeendpoint (pipe),
			usb_pipeout (pipe)? 'O': 'I',
			usb_pipetype (pipe) < 2? (usb_pipeint (pipe)? "INTR": "ISOC"):
				(usb_pipecontrol (pipe)? "CTRL": "BULK"),
			purb->actual_length,
			transfer_len, (u32)dev->status);

			
#ifdef	OHCI_VERBOSE_DEBUG
	if (!small) {
		int i, len;

		if (usb_pipecontrol (pipe)) {
			printk (__FILE__ ": cmd(8):");
			for (i = 0; i < 8 ; i++)
				printk (" 0x%x", ((__u8 *) setup) [i]);
			printk ("\n");
		}
		if (transfer_len > 0 && buffer) {
			printk (__FILE__ ": data(%d/%d):",
				purb->actual_length,
				transfer_len);
			len = usb_pipeout (pipe)?
					transfer_len: purb->actual_length;
			for (i = 0; i < 16 && i < len; i++)
				printk (" 0x%x", ((__u8 *) buffer) [i]);
			printk ("%s\n", i < len? "...": "");
		}
	}
#endif
}

#endif




/*-------------------------------------------------------------------------*
 * Virtual Root Hub
 *-------------------------------------------------------------------------*/

/* Device descriptor */
static __u8 root_hub_dev_des[] =
{
	0x12,       /*  __u8  bLength; */
	0x01,       /*  __u8  bDescriptorType; Device */
	0x20,	    /*  __u16 bcdUSB; v2.0 */
	0x01,
	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x01,       /*  __u8  bDeviceProtocol; */
	64,       	/*  __u8  bMaxPacketSize0; 64 Bytes */
	0x00,       /*  __u16 idVendor; */
	0x00,
	0x00,       /*  __u16 idProduct; */
	0x00,
	0x00,       /*  __u16 bcdDevice; */
	0x00,
	0x00,       /*  __u8  iManufacturer; */
	0x01,       /*  __u8  iProduct; */
	0x00,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
};


/* Configuration descriptor */
static __u8 root_hub_config_des[] =
{
	0x09,       /*  __u8  bLength; */
	0x02,       /*  __u8  bDescriptorType; Configuration */
	0x19,       /*  __u16 wTotalLength; */
	0x00,
	0x01,       /*  __u8  bNumInterfaces; */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0x40,       /*  __u8  bmAttributes;
		 Bit 7: Bus-powered, 6: Self-powered, 5 Remote-wakwup, 4..0: resvd */
	0x00,       /*  __u8  MaxPower; */

	/* interface */
	0x09,       /*  __u8  if_bLength; */
	0x04,       /*  __u8  if_bDescriptorType; Interface */
	0x00,       /*  __u8  if_bInterfaceNumber; */
	0x00,       /*  __u8  if_bAlternateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  if_bInterfaceSubClass; */
	0x00,       /*  __u8  if_bInterfaceProtocol; */
	0x00,       /*  __u8  if_iInterface; */

	/* endpoint */
	0x07,       /*  __u8  ep_bLength; */
	0x05,       /*  __u8  ep_bDescriptorType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
	64,       /*  __u16 ep_wMaxPacketSize; ((MAX_ROOT_PORTS + 1) / 8 */
	0x00,
	0xff        /*  __u8  ep_bInterval; 255 ms */
};

static unsigned char root_hub_str_index0[] =
{
	0x04,			/*  __u8  bLength; */
	0x03,			/*  __u8  bDescriptorType; String-descriptor */
	0x09,			/*  __u8  lang ID */
	0x04,			/*  __u8  lang ID */
};

static unsigned char root_hub_str_index1[] =
{
	28,			/*  __u8  bLength; */
	0x03,			/*  __u8  bDescriptorType; String-descriptor */
	'E',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'H',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'C',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'I',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	' ',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'R',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'o',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'o',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	't',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	' ',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'H',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'u',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
	'b',			/*  __u8  Unicode */
	0,				/*  __u8  Unicode */
};


/*-------------------------------------------------------------------------*
 * URB support functions
 *-------------------------------------------------------------------------*/

/* free HCD-private data associated with this URB */

static void urb_free_priv (struct urb *urb)
{
	memset(urb,0,sizeof(*urb));	
}


/*-------------------------------------------------------------------------*
 * QH handling functions
 *-------------------------------------------------------------------------*/
#define HALT_BIT __constant_cpu_to_le32(QTD_STS_HALT)


#define	QH_ADDR_MASK	__constant_cpu_to_le32(0x7f)

/* makes sure the async qh will become idle */
/* caller must own ehci->lock */

static void start_unlink_async (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	int		cmd = readl (&ehci->regs->command);	
	struct ehci_qh	*prev;

	qh->qh_state = QH_STATE_UNLINK;	

	prev = ehci->async;
		
	/*
	if (!list_empty(&qh->qtd_list))
		printk("qtd_list not empty\n");
	*/
	
	while (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw_next = qh->hw_next;
	prev->qh_next = qh->qh_next;

	// INIT_LIST_HEAD(&qh->qtd_list);	
	
	sys_dcache_flush_and_invalidate_all();

	cmd |= CMD_IAAD;
	writel (cmd, &ehci->regs->command);
	(void) readl (&ehci->regs->command);

	/*
	while(!(readl(&ehci->regs->status) & STS_IAA)) 
	{};	
	
	writel (readl(&ehci->regs->status) | STS_IAA,&ehci->regs->status);
	*/		
}

/*
 * For control/bulk/interrupt, return QH with these TDs appended.
 * Allocates and initializes the QH if necessary.
 * Returns null if it can't allocate a QH it needs to.
 * If the QH has TDs (urbs) already, that's great.
 */
static struct ehci_qh *qh_append_tds (
	struct ehci_hcd		*ehci,
	struct urb		*urb,	
	struct list_head	*qtd_list,
	int			epnum
	// void			**ptr
)
{

	struct ehci_qh		*qh = NULL;

	
	qh = qh_make (ehci, urb, urb->pipe);
	
	if (likely (qh != NULL)) {
		struct ehci_qtd	*qtd;

		if (unlikely (list_empty (qtd_list)))
			qtd = NULL;
		else
			qtd = list_entry (qtd_list->next, struct ehci_qtd,
					qtd_list);

		/* control qh may need patching ... */
		if (unlikely (epnum == 0)) {

                        /* usb_reset_device() briefly reverts to address 0 */
                        if (usb_pipedevice (urb->pipe) == 0)
                                qh->hw_info1 &= ~QH_ADDR_MASK;
		}

		/* just one way to queue requests: swap with the dummy qtd.
		 * only hc or qh_refresh() ever modify the overlay.
		 */
		if (likely (qtd != NULL)) {			
			struct ehci_qtd		*dummy;
			dma_addr_t		dma;
			
			__le32			token;

			/* to avoid racing the HC, use the dummy td instead of
			 * the first td of our list (becomes new dummy).  both
			 * tds stay deactivated until we're done, when the
			 * HC is allowed to fetch the old dummy (4.10.2).
			 */
			token = qtd->hw_token;
			qtd->hw_token = HALT_BIT;
			// wmb ();
			
			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;
			
			
			list_del (&qtd->qtd_list);
			list_add (&dummy->qtd_list, qtd_list);
			list_splice (qtd_list, qh->qtd_list.prev);

			ehci_qtd_init (qtd, qtd->qtd_dma);
			qh->dummy = qtd;

			/* hc must see the new dummy at list end */
			dma = qtd->qtd_dma;
			qtd = list_entry (qh->qtd_list.prev,
					struct ehci_qtd, qtd_list);
			qtd->hw_next = QTD_NEXT (dma);

			/* let the hc process these next qtds */			
			dummy->hw_token = token;
			
		}
	}
	return qh;
}

/*
 * Process and free completed qtds for a qh, returning URBs to drivers.
 * Chases up to qh->hw_current.  Returns number of completions called,
 * indicating how much "real" work we did.
 */
static unsigned
qh_completions (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	struct ehci_qtd		*last = NULL, *end = qh->dummy;
	struct list_head	*entry = NULL, *tmp = NULL;
	int			stopped;
	unsigned		count = 0;
	int			do_status = 0;
	u8			state;
	
	/*
	{
		int i=0;
		for (i=0;i<0x80;i++) {
			if (qh->reserved[i] != 0xa5) {
				printk("USB write it , qh->reserved = 0x%x\n",&qh->reserved[0]);
				dbg_echi_dump_all_qh(qh);
				while(1);	
			}
		}
	}
	*/
	
	if (unlikely (list_empty (&qh->qtd_list)))
		return count;

	/* completions (or tasks on other cpus) must never clobber HALT
	 * till we've gone through and cleaned everything up, even when
	 * they add urbs to this qh's queue or mark them for unlinking.
	 *
	 * NOTE:  unlinking expects to be done in queue order.
	 */
	
	state = qh->qh_state;
	qh->qh_state = QH_STATE_COMPLETING;
	stopped = (state == QH_STATE_IDLE);
	
	/* remove de-activated QTDs from front of queue.
	 * after faults (including short reads), cleanup this urb
	 * then let the queue advance.
	 * if queue is stopped, handles unlinks.
	 */
	/*
	printk("=========================================================\n"); 
	printk("\n");
	dbg_echi_dump_all_qh(qh);
	*/

	list_for_each_safe (entry, tmp, &qh->qtd_list) {
		struct ehci_qtd	*qtd;
		struct urb	*urb;
		u32		token = 0;	
		// int		retry_count=0;

		
		/*
		printk("entry = 0x%x , tmp = 0x%x\n", entry , tmp);
		udelay(100*1000);	
		*/
		
		// retry_count = 0;
		
		qtd = list_entry (entry, struct ehci_qtd, qtd_list);
		qtd =  (struct ehci_qtd *) KSEG1ADDR(qtd);  //chengying modify , avoid hardware upqtd , but software read cache data
		
		urb = qtd->urb;	
		/* clean up any state from previous QTD ...*/
		if (last) {
			ehci_qtd_free (ehci, last);	
			count++;		
			last = NULL;
		}

		/* ignore urbs submitted during completions we reported */
		if (qtd == end)
			break;

/*
		for (retry_count=0;retry_count < 20000;retry_count++) 		{
			token = le32_to_cpu (qtd->hw_token);
			if ((token & QTD_STS_ACTIVE) == 0)
				break;
            
            		udelay(25);
		}
*/
retry :
		/* hardware copies qtd out of qh overlay */
		// rmb ();
		token = le32_to_cpu (qtd->hw_token);		
				
		/* always clean up qtds the hc de-activated */
		if ((token & QTD_STS_ACTIVE) == 0) {						
			if ((token & QTD_STS_HALT) != 0) {
				stopped = 1;
				/*
				printk("QTD_STS_HALT\n");
				dbg_echi_dump_all_qh(qh);
				*/
			/* magic dummy for some short reads; qh won't advance.
			 * that silicon quirk can kick in with this dummy too.
			 */
			} else if (IS_SHORT_READ (token)
					&& !(qtd->hw_alt_next & EHCI_LIST_END)) {
				stopped = 1;
				// printk("IS_SHORT_READ\n");
				goto halt;
			}
			
			/*
			if  (likely (QTD_PID (token) != 2)) {
 				purb_priv->actual_length += (qtd->length - QTD_LENGTH (token));
 				// printk("\nqtd->length = %d\n",qtd->length);
			}
			*/				
			
		/* stop scanning when we reach qtds the hc is using */
		} else if (likely (!stopped)) { /*(likely (!stopped
				&& HC_IS_RUNNING (ehci_to_hcd(ehci)->state))) { */
		    	int		retry_count=0;		
#ifdef DEBUG				
			printk("=========================================================\n"); 	
			printk("QTD not finish [Error1] : qtd = 0x%x  , token = 0x%x\n", (u32)qtd , token);
			// dbg_echi_dump_all_qh(qh);
						
			// udelay(1000*1000*5);
#endif			
	
						
			for (retry_count=0;retry_count < 40000;retry_count++) 		{
				
//--       			sys_dcache_flush_and_invalidate_all(); // if not add , it may fail , confused ??
				token = le32_to_cpu (qtd->hw_token);
				if ((token & QTD_STS_ACTIVE) == 0)
					goto retry;
            
            		udelay(25);
			}
						
			 printk("Timeout [1]!");	
			
			break;
		} else {			
			stopped = 1;
#ifdef DEBUG			
			printk("=========================================================\n"); 
			printk("QTD not finish [Error2] : qtd = 0x%x  , token = 0x%x\n", (u32)qtd , token);
			// dbg_echi_dump_all_qh(qh);
#endif				
			/* ignore active urbs unless some previous qtd
			 * for the urb faulted (including short read) or
			 * its urb was canceled.  we may patch qh or qtds.
			 */
			 
			
			/* issue status after short control reads */
			if (unlikely (do_status != 0)
					&& QTD_PID (token) == 0 /* OUT */) {
				do_status = 0;
				continue;
			}

			/* token in overlay may be most current */
			if (state == QH_STATE_IDLE
					&& cpu_to_le32 (qtd->qtd_dma)
						== qh->hw_current)
				token = le32_to_cpu (qh->hw_token);

			/* force halt for unlinked or blocked qh, so we'll
			 * patch the qh later and so that completions can't
			 * activate it while we "know" it's stopped.
			 */
			if ((HALT_BIT & qh->hw_token) == 0) {
halt:
				qh->hw_token |= HALT_BIT;
			}
		} 
 			
		/* remove it from the queue */
		do_status = (urb->state == -EREMOTEIO)
				&& usb_pipecontrol (urb->pipe);		

		if (stopped && qtd->qtd_list.prev != &qh->qtd_list) {
			last = list_entry (qtd->qtd_list.prev,
					struct ehci_qtd, qtd_list);
			last->hw_next = qtd->hw_next;
		}
		
		list_del (&qtd->qtd_list);
		last = qtd;
		
	}
	
	/* last urb's completion might still need calling */
	if (likely (last != NULL)) {
		count++;
		ehci_qtd_free (ehci, last);
	}
	
	/* restore original state; caller must unlink or relink */
	qh->qh_state = state;

	return count;
}

static int ehci_irq () // (struct usb_hcd *hcd , struct pt_regs *regs)
{
	struct ehci_hcd		*ehci = &rtd_ehci;
	volatile u32			status;
	int			bh;
	
#if 0
	if (((rtd_inl(SYSCTRL_LXBUS_TIMEOUT_STATUS) & 0xf0) >> 4) == LX_USB_ID) { 
		printk("%s : %d  LXBusTo = 0x%x , Address = 0x%x\n",__FUNCTION__,__LINE__,rtd_inl(SYSCTRL_LXBUS_TIMEOUT_STATUS),rtd_inl(SYSCTRL_LXBUS_TIMEOUT_ADDRESS));
		rtd_outl(SYSCTRL_LXBUS_TIMEOUT_STATUS,0xffffffff); 
	}
#endif /* 0 */

	status = readl (&ehci->regs->status);

	/* e.g. cardbus physical eject */
	if (status == ~(u32) 0) {
		ehci_dbg (ehci, "device removed\n");
		goto dead;
	}
	
		
	status &= INTR_MASK;
	
	if (status & STS_PCD) {
		got_rhsc = 1;
	}	
	
	// Warrning , but don't return error.
	if (!status) {			/* irq sharing? */
		// ehci->disabled++;
		// ehci_reset (ehci);	
		// printk("%s (Error) : IRQ_NONE (status = 0x%x , reg status = 0x%x)\n", __FUNCTION__,status,readl (&ehci->regs->status));		
		// Re-read status util time-out or action complete.
		return 0xff;		
	}
	
	/* clear (just) interrupts */
	writel (status, &ehci->regs->status);
	readl (&ehci->regs->command);	/* unblock posted write */
	bh = 0;

#ifdef	EHCI_VERBOSE_DEBUG
	/* unrequested/ignored: Frame List Rollover */
	dbg_status (ehci, "irq", status);
#endif

	/* INT, ERR, and IAA interrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */	
	if (likely ((status & (STS_INT|STS_ERR)) != 0)) {
		/* STS_ERR flag doesn't mean trasaction error. So , it is statistics counter in linux kernel. */
		// For Debug  
		/*
		if (likely ((status & STS_ERR) != 0)) {
			printk("%s (Error) :  STS_ERR (status = 0x%x)\n", __FUNCTION__,status);		
		}
		*/
		bh = 1;
	}
	
	
	/* complete the unlinking of some qh [4.15.2.3] */
	if (status & STS_IAA) {
		bh = 1;
	}

	/* PCI errors [4.15.2.4] */
	if (unlikely ((status & STS_FATAL) != 0)) {
		/* bogus "fatal" IRQs appear on some chips... why?  */
		status = readl (&ehci->regs->status);		
		if (status & STS_HALT) {
			ehci_err (/*ehci, */"fatal error\n");
dead:
			err ("EHCI FATAL Error, controller usb-%s disabled",
			ehci->slot_name);
			ehci->disabled++;
			ehci_reset (ehci);
			writel (0, &ehci->regs->configured_flag);
			/* generic layer kills/unlinks all urbs, then
			 * uses ehci_stop to clean up the rest
			 */
			bh = 1;

#ifdef DEBUG
 		
			//dbg_echi_dump_all_qh(ehci->async->qh_next.qh);
			
#endif			
			
			return -1;
		}
	}
	
	
	if (bh) {
		// udelay(10*1000);
		ehci_work (ehci);
	}
			
	return 0;		
}


/*-------------------------------------------------------------------------*
 * QTD handling functions
 *-------------------------------------------------------------------------*/
// high bandwidth multiplier, as encoded in highspeed endpoint descriptors
#define hb_mult(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))
// ... and packet size, for any kind of endpoint descriptor
#define max_packet(wMaxPacketSize) ((wMaxPacketSize) & 0x07ff) 
 
/* QTDs ... */
static inline struct ehci_qtd *ehci_qtd_alloc(struct usb_device *usb_dev)
{
	int i;
	struct ehci_qtd	*qtd;
	
	qtd = NULL;
	for (i = 0; i < NUM_QTD; i++)
	{
		if (p_qtd[i].usb_dev == NULL)
		{
			qtd = &p_qtd[i];
			qtd->usb_dev = usb_dev;
			break;
		}
	}
	
	if (qtd) {
		INIT_LIST_HEAD (&qtd->qtd_list);
		qtd->qtd_dma = CPHYSADDR(qtd);
#ifdef ENABLE_KSEG1ADDR
		return (struct ehci_qtd *) KSEG1ADDR(qtd);
#else /* ENABLE_KSEG1ADDR */
		return (struct ehci_qtd *) qtd;
#endif /* ENABLE_KSEG1ADDR */
	}
	
	printk("No qtd!\n");
	
	return NULL;
} 

/* Allocate the key transfer structures from the previously allocated pool */
static inline void ehci_qtd_init (struct ehci_qtd *qtd, dma_addr_t dma)
{
	memset (qtd, 0, sizeof *qtd);
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_le32 (QTD_STS_HALT);
	qtd->hw_next = EHCI_LIST_END;
	qtd->hw_alt_next = EHCI_LIST_END;
	INIT_LIST_HEAD (&qtd->qtd_list);
}
 
/*
 * reverse of qh_urb_transaction:  free a list of TDs.
 * used for cleanup after errors, before HC sees an URB's TDs.
 */
static void qtd_list_free (
	struct ehci_hcd		*ehci,
	struct urb		*urb,
	struct list_head	*qtd_list
) {
	struct list_head	*entry, *temp;

	list_for_each_safe (entry, temp, qtd_list) {
		struct ehci_qtd	*qtd;

		qtd = list_entry (entry, struct ehci_qtd, qtd_list);
		list_del (&qtd->qtd_list);
		ehci_qtd_free (ehci, qtd);
	}
} 
 
static inline void ehci_qtd_free (struct ehci_hcd *ehci, struct ehci_qtd *qtd)
{
	if (!qtd)
		return;
	
	memset(qtd,0,sizeof(struct ehci_qtd));
	qtd->qtd_dma = CPHYSADDR(qtd);
	ehci_qtd_init (qtd, qtd->qtd_dma);	
	
}

static inline void ehci_all_qtd_free(void)
{
	int i = 0;
	struct ehci_qtd *qtd = NULL;
	
	for (i = 0; i < NUM_QTD; i++)
	{
		qtd = &p_qtd[i];
		memset(qtd,0,sizeof(struct ehci_qtd));
		qtd->usb_dev = NULL;
		qtd->qtd_dma = CPHYSADDR(qtd);
		ehci_qtd_init (qtd, qtd->qtd_dma);	
	}
}

 
/* fill a qtd, returning how much of the buffer we were able to queue up */
static int
qtd_fill (struct ehci_qtd *qtd, dma_addr_t buf, size_t len,
		int token, int maxpacket)
{
	int	i, count;
	u64	addr = buf;

	/* one buffer entry per 4K ... first might be short or unaligned */
	qtd->hw_buf [0] = cpu_to_le32 ((u32)addr);
	qtd->hw_buf_hi [0] = cpu_to_le32 ((u32)(addr >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* rest of that page */
	
	// printk("addr = 0x%x\n",addr);
	
	if (likely (len < count))		/* ... iff needed */
		count = len;
	else {
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* per-qtd limit: from 16K to 20K (best alignment) */
		for (i = 1; count < len && i < 5; i++) {
			addr = buf;
			qtd->hw_buf [i] = cpu_to_le32 ((u32)addr);
			qtd->hw_buf_hi [i] = cpu_to_le32 ((u32)(addr >> 32));
			buf += 0x1000;
			if ((count + 0x1000) < len)
				count += 0x1000;
			else
				count = len;
			
			// printk("addr = 0x%x\n",addr);	
				
		}

		/* short packets may only terminate transfers */
		if (count != len)
			count -= (count % maxpacket);
	}
	qtd->hw_token = cpu_to_le32 ((count << 16) | token);
	qtd->length = count;

	return count;
}

/*-------------------------------------------------------------------------*/

static inline void
qh_update (struct ehci_hcd *ehci, struct ehci_qh *qh, struct ehci_qtd *qtd)
{
	/* writes to an active overlay are unsafe */
	// BUG_ON(qh->qh_state != QH_STATE_IDLE);

	qh->hw_qtd_next = QTD_NEXT (qtd->qtd_dma);
	qh->hw_alt_next = EHCI_LIST_END;

	/* Except for control endpoints, we make hardware maintain data
	 * toggle (like OHCI) ... here (re)initialize the toggle in the QH,
	 * and set the pseudo-toggle in udev. Only usb_clear_halt() will
	 * ever clear it.
	 */
	if (!(qh->hw_info1 & cpu_to_le32(1 << 14))) {
		unsigned	is_out, epnum;

		is_out = !(qtd->hw_token & cpu_to_le32(1 << 8));
		epnum = (le32_to_cpup(&qh->hw_info1) >> 8) & 0x0f;
		if (unlikely (!usb_gettoggle (qh->dev, epnum, is_out))) {
			qh->hw_token &= ~__constant_cpu_to_le32 (QTD_TOGGLE);
			usb_settoggle (qh->dev, epnum, is_out, 1);
		}
	}

	/* HC must see latest qtd and qh data before we clear ACTIVE+HALT */
	// wmb ();
	qh->hw_token &= __constant_cpu_to_le32 (QTD_TOGGLE | QTD_STS_PING);
}

/* if it weren't for a common silicon quirk (writing the dummy into the qh
 * overlay, so qh->hw_token wrongly becomes inactive/halted), only fault
 * recovery (including urb dequeue) would need software changes to a QH...
 */
static void
qh_refresh (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	struct ehci_qtd *qtd;

	if (list_empty (&qh->qtd_list))
		qtd = qh->dummy;
	else {
		qtd = list_entry (qh->qtd_list.next,
				struct ehci_qtd, qtd_list);
		/* first qtd may already be partially processed */
		if (cpu_to_le32 (qtd->qtd_dma) == qh->hw_current)
			qtd = NULL;
	}

	if (qtd)
		qh_update (ehci, qh, qtd);
}

static struct ehci_qh *ehci_qh_alloc (struct ehci_hcd *ehci,struct urb *urb,unsigned long pipe)
{
	struct ehci_qh *qh = NULL;
	qh = &pehci_dev->qh[(usb_pipeendpoint (pipe) << 1) |
			(usb_pipecontrol (pipe)? 0: usb_pipeout (pipe))];
					
	if (!qh)
		return qh;
	
#ifdef ENABLE_KSEG1ADDR
	qh = (struct ehci_qh *) KSEG1ADDR(qh);
#endif /* ENABLE_KSEG1ADDR */
	
	/* Clear qh context will not work.*/	
	// memset (qh, 0, sizeof(*qh));	
	
	qh->ehci = ehci;
	qh->qh_dma = CPHYSADDR(qh);
	// INIT_LIST_HEAD (&qh->qh_list);
	INIT_LIST_HEAD (&qh->qtd_list);
		
	/* dummy td enables safe urb queuing */
	qh->dummy = ehci_qtd_alloc (urb->dev/*ehci, flags*/);
	if (qh->dummy == NULL) {
		ehci_dbg (ehci, "no dummy td\n");
		qh_free (qh);
	}
	
	qh->qh_next.qh = NULL;
//--	sys_dcache_flush_and_invalidate_all();		
	return qh;			
}

/*
 * Each QH holds a qtd list; a QH is used for everything except iso.
 *
 * For interrupt urbs, the scheduler must set the microframe scheduling
 * mask(s) each time the QH gets scheduled.  For highspeed, that's
 * just one microframe in the s-mask.  For split interrupt transactions
 * there are additional complications: c-mask, maybe FSTNs.
 */
static struct ehci_qh *
qh_make (
	struct ehci_hcd *ehci,
	// struct usb_device *usb_dev,
	struct urb		*urb,
	unsigned long pipe
) {
	u32			info1 = 0, info2 = 0;
	int			is_input, type;
	int			maxp = 0;
	
	// struct ehci_qtd *qtd = NULL; 
	struct ehci_qh *qh_ret=NULL;
	volatile struct ehci_qh *qh=NULL;


	qh = qh_ret = ehci_qh_alloc(ehci,urb,pipe);
		
	/*
	 * init endpoint/device data for this QH
	 */
	info1 |= usb_pipeendpoint (pipe) << 8;
	info1 |= usb_pipedevice (pipe) << 0;

	is_input = usb_pipein (pipe);
	type = usb_pipetype (pipe);
	maxp = usb_maxpacket (urb->dev/*usb_dev*/, pipe /*, !is_input*/);

	/* Compute interrupt scheduling parameters just once, and save.
	 * - allowing for high bandwidth, how many nsec/uframe are used?
	 * - split transactions need a second CSPLIT uframe; same question
	 * - splits also need a schedule gap (for full/low speed I/O)
	 * - qh has a polling interval
	 *
	 * For control/bulk requests, the HC or TT handles these.
	 */
	if (type == PIPE_INTERRUPT) {
		// We don't support PIPE_INTERRUPT.
		return NULL;
	}

	/* support for tt scheduling, and access to toggles */
	qh->dev = urb->dev;// urb->usb_dev;

	/* using TT? */
	switch (urb->dev->speed/*usb_dev->speed*/) {
		case USB_SPEED_LOW:
		case USB_SPEED_FULL:
			printk("%s : We don't support TT\n", __FUNCTION__);
			return NULL;
		break;
#if 0		
	case USB_SPEED_LOW:
		info1 |= (1 << 12);	/* EPS "low" */
		/* FALL THROUGH */

	case USB_SPEED_FULL:
		/* EPS 0 means "full" */
		if (type != PIPE_INTERRUPT)
			info1 |= (EHCI_TUNE_RL_TT << 28);
		if (type == PIPE_CONTROL) {
			info1 |= (1 << 27);	/* for TT */
			info1 |= 1 << 14;	/* toggle from qtd */
		}
		info1 |= maxp << 16;

		info2 |= (EHCI_TUNE_MULT_TT << 30);
		info2 |= urb->dev->ttport << 23;

		/* set the address of the TT; for TDI's integrated
		 * root hub tt, leave it zeroed.
		 */
		
		if (!ehci_is_TDI(ehci)
				|| urb->dev->tt->hub !=
					ehci_to_hcd(ehci)->self.root_hub)
			info2 |= urb->dev->tt->hub->devnum << 16;	

		/* NOTE:  if (PIPE_INTERRUPT) { scheduler sets c-mask } */

		break;
#endif

	case USB_SPEED_HIGH:		/* no TT involved */
		info1 |= (2 << 12);	/* EPS "high" */
		if (type == PIPE_CONTROL) {
			info1 |= (EHCI_TUNE_RL_HS << 28);
			info1 |= 64 << 16;	/* usb2 fixed maxpacket */
			info1 |= 1 << 14;	/* toggle from qtd */
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		} else if (type == PIPE_BULK) {
			info1 |= (EHCI_TUNE_RL_HS << 28);
			info1 |= 512 << 16;	/* usb2 fixed maxpacket */
			info2 |= (EHCI_TUNE_MULT_HS << 30);
		} else {		/* PIPE_INTERRUPT */
			info1 |= max_packet (maxp) << 16;
			info2 |= hb_mult (maxp) << 30;
		}
		break;
	default:
 		// dbg ("bogus dev %p speed %d", urb->dev, urb->dev->speed);
// done:

		printk("%s Unknow speed = 0x%x\n",__FUNCTION__,urb->dev->speed);
		return NULL;
	}
		
	/* NOTE:  if (PIPE_INTERRUPT) { scheduler sets s-mask } */
	
	/* init as live, toggle clear, advance to dummy */
	qh->qh_state = QH_STATE_IDLE;
	qh->hw_info1 = cpu_to_le32 (info1);
	qh->hw_info2 = cpu_to_le32 (info2);
	usb_settoggle (urb->dev/*usb_dev*/, usb_pipeendpoint (pipe), !is_input, 1);
//--	sys_dcache_flush_and_invalidate_all();
	qh_refresh (ehci, (struct ehci_qh *) qh);
	return (struct ehci_qh *) qh;
}

/* move qh (and its qtds) onto async queue; maybe enable queue.  */
static void qh_link_async (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	__le32		dma = QH_NEXT (qh->qh_dma);
	struct ehci_qh	*head;	
	unsigned int *pint;
	union ehci_shadow *p_ehci_shadow;
	struct ehci_qh **p_ehci_qh;
	// int timeout = 0; 
	u32 cmd;
		
	// u32 status = readl (&ehci->regs->status);
	
/*		
	if (__test_start)		
		dbg_echi_dump_all_qh(qh);
*/	
#ifdef DEBUG
	//dbg_echi_dump_all_qh(qh);
#endif /* DEBUG */
	
	// memset(&qh->reserved,0xff,0x20);
	/*
	{
		int i=0;
		for (i=0;i<0x80;i++) {
			qh->reserved[i] = 0xa5;	
		}
	}
	*/	
		
		
	/* (re)start the async schedule? */
	sys_dcache_flush_and_invalidate_all();
	head = ehci->async;
	
	
	if (!head->qh_next.qh) {
		cmd = readl (&ehci->regs->command);

		if (!(cmd & CMD_ASE)) {
			/* in case a clear of CMD_ASE didn't take yet */
			(void) handshake (&ehci->regs->status, STS_ASS, 0, 150);
			cmd |= CMD_ASE | CMD_RUN;
			
			__sync();
			writel (cmd, &ehci->regs->command);			
			/* posted write need not be known to HC yet ... */
		}
	}
	

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	if (qh->qh_state == QH_STATE_IDLE)
		qh_refresh (ehci, qh);
	
	/*	
	if (status & STS_RECL)	{
		printk("STS_RECL\n");
		writel (STS_RECL,&ehci->regs->status);
	}
	*/	

       sys_dcache_flush_and_invalidate_all();  //chengying add

#if 1 //chengying modify
	p_ehci_shadow = (union ehci_shadow *)KSEG1ADDR(&qh->qh_next);
	*p_ehci_shadow = head->qh_next;
	pint = (unsigned int *) KSEG1ADDR(&qh->hw_next);
	*pint = head->hw_next;	
	pint =(unsigned int *) KSEG1ADDR(&head->hw_next);
	*pint = dma;
	p_ehci_qh = (struct ehci_qh **)KSEG1ADDR(&head->qh_next.qh);
	*p_ehci_qh = qh;

#else
	/* splice right after start */
	qh->qh_next = head->qh_next;
	qh->hw_next = head->hw_next;
								
	head->qh_next.qh = qh;
	head->hw_next = dma;
#endif
	sys_dcache_flush_and_invalidate_all();
	qh->qh_state = QH_STATE_LINKED;

	/* qtd completions reported later by interrupt */
		
#if defined(CONFIG_BOOT_VERIFY_VM)		
		LXBusProcess();
#endif

/*
	timeout = 0;
	while (!(readl (&ehci->regs->status) & (STS_INT|STS_ERR)))
	{	
		timeout++;
		udelay(10);
		if (timeout >= 10000)
			break;
	};
	
	
	if (timeout >= 10000)
		printk("Polling STS_INT or STS_ERR status timeout!\n");
	
	
	timeout = 0;
	while (!(readl (&ehci->regs->status) &  STS_RECL))
    {
    	timeout++;
    	udelay(10);
    	if (timeout >= 10000)
			break;
    };
    
    if (timeout >= 10000)
		printk("Polling STS_RECL status timeout!\n");
*/   
    

/*
	{
		struct ehci_qtd *qtd = list_entry ((&qh->qtd_list)->next, struct ehci_qtd, qtd_list);
		qtd->hw_next |= EHCI_LIST_END;
		qtd->hw_alt_next |= EHCI_LIST_END;

	}

	flush_dcache();
*/

/*
	head->hw_next = QH_NEXT (head->qh_dma);
	flush_dcache();


	writel (readl (&ehci->regs->command) | CMD_IAAD, &ehci->regs->command);
	(void) readl (&ehci->regs->command); 
*/
}


/*-------------------------------------------------------------------------*
 * Interface functions (URB)
 *-------------------------------------------------------------------------*/

static int
submit_async (
	struct ehci_hcd		*ehci,	
	struct usb_device *dev,
	struct urb		*urb,	
	struct list_head	*qtd_list	
) {
	struct ehci_qtd		*qtd;
	int			epnum;	
	struct ehci_qh		*qh = NULL;
	
		
	qtd = list_entry (qtd_list->next, struct ehci_qtd, qtd_list);
	epnum = dev->config.if_desc[0].ep_desc[usb_pipeendpoint(urb->pipe)].bEndpointAddress;
	
#ifdef EHCI_URB_TRACE
	ehci_dbg (ehci,
		"%s %d urb %p ep%d%s len %d, qtd %p [qh %p] state %x\n",
		__FUNCTION__, urb->dev->devnum, urb,
		epnum & 0x0f, (epnum & USB_DIR_IN) ? "in" : "out",
		urb->transfer_buffer_length,
		qtd, qh/*ep->hcpriv*/, (qh==NULL)?0:qh->qh_state);
#endif
	
	qh = qh_append_tds (ehci, urb, qtd_list, epnum /*&ep->hcpriv*/);
	
#ifdef DEBUG
	printk("-----------------------------------------\n");
	printk("ehci->regs->async_next = 0x%x ,  qh = 0x%x\n",ehci->regs->async_next,qh);
	printk("-----------------------------------------\n");
#endif /* DEBUG */

//--	sys_dcache_flush_and_invalidate_all();

	/* Control/bulk operations through TTs don't need scheduling,
	 * the HC and TT handle it when the TT has a buffer ready.
	 */
	if (likely (qh != NULL)) {
		if (likely (qh->qh_state == QH_STATE_IDLE))
			qh_link_async (ehci, qh/*qh_get (qh)*/);
	}
	
	if (unlikely (qh == NULL)) {
		qtd_list_free (ehci, urb, qtd_list);
		return -ENOMEM;
	}
	
	return 0;
}

/*
 * create a list of filled qtds for this URB; won't link into qh.
 */
static struct list_head *
qh_urb_transaction (
	struct ehci_hcd		*ehci,
	struct urb		*urb,
	struct list_head	*head	
) {
	struct ehci_qtd		*qtd, *qtd_prev;
	dma_addr_t		buf;
	int			len, maxpacket;
	int			is_input;
	u32			token;

	/*
	 * URBs map to sequences of QTDs:  one logical transaction
	 */
	qtd = ehci_qtd_alloc (urb->dev/*ehci, flags*/);
	if (unlikely (!qtd))
		return NULL;
	list_add_tail (&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CERR << 10);
	/* for split transactions, SplitXState initialized to zero */

	len = urb->transfer_buffer_length;
	is_input = usb_pipein (urb->pipe);
	if (usb_pipecontrol (urb->pipe)) {
		/* SETUP pid */
		qtd_fill (qtd, urb->setup_dma, sizeof (struct usb_ctrlrequest),
			token | (2 /* "setup" */ << 8), 8);

		/* ... and always at least one more pid */
		token ^= QTD_TOGGLE;
		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (urb->dev);
		if (unlikely (!qtd))
			goto cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT (qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);
	} 

	/*
	 * data transfer stage:  buffer setup
	 */
	if (likely (len > 0))
		buf = urb->transfer_dma;
	else
		buf = 0;
		
	

	/* for zero length DATA stages, STATUS is always IN */
	if (!buf || is_input)
		token |= (1 /* "in" */ << 8);
	/* else it's already initted to "out" pid (0 << 8) */

	maxpacket = max_packet(usb_maxpacket(urb->dev, urb->pipe/*, !is_input*/));

	/*
	 * buffer gets wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	for (;;) {
		int this_qtd_len;

		this_qtd_len = qtd_fill (qtd, buf, len, token, maxpacket);
		len -= this_qtd_len;
		buf += this_qtd_len;
		if (is_input)
			qtd->hw_alt_next = ehci->async->hw_alt_next;

		/* qh makes control packets use qtd toggle; maybe switch it */
		if ((maxpacket & (this_qtd_len + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGLE;

		if (likely (len <= 0))
			break;

		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (urb->dev/* ehci, flags*/);
		if (unlikely (!qtd))
			goto cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT (qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);
	}

	/* unless the bulk/interrupt caller wants a chance to clean
	 * up after short reads, hc should advance qh past this urb
	 */
	/* 
	if (likely ((urb->transfer_flags & URB_SHORT_NOT_OK) == 0
				|| usb_pipecontrol (urb->pipe)))
	*/
	if (usb_pipecontrol (urb->pipe))			
		qtd->hw_alt_next = EHCI_LIST_END;

	/*
	 * control requests may need a terminating data "status" ack;
	 * bulk ones may need a terminating short packet (zero length).
	 */
	if (likely (buf != 0)) {
		int	one_more = 0;

		if (usb_pipecontrol (urb->pipe)) {
			one_more = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGLE;	/* force DATA1 */
				
		} else if (usb_pipebulk (urb->pipe)
			    && (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length % maxpacket)) {
			one_more = 1;
		}		
		
		if (one_more) {
			qtd_prev = qtd;
			qtd = ehci_qtd_alloc (urb->dev /* ehci, flags*/);
			if (unlikely (!qtd))
				goto cleanup;
			qtd->urb = urb;
			qtd_prev->hw_next = QTD_NEXT (qtd->qtd_dma);
			list_add_tail (&qtd->qtd_list, head);

			/* never any data in such packets */
			qtd_fill (qtd, 0, 0, token, 0);
		}
	}

	/* by default, enable interrupt on urb completion */
	// if (likely (!(urb->transfer_flags & URB_NO_INTERRUPT)))
		qtd->hw_token |= __constant_cpu_to_le32 (QTD_IOC);

	return head;

cleanup:
	qtd_list_free (ehci, urb, head);
	return NULL;
}




/* get a transfer request */

static int ehci_submit_job(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup, int interval) 
{
	int size=0;
	struct ehci_qh *qh=NULL;
	struct ehci_hcd		*ehci = &rtd_ehci;
	// urb_priv_t *purb_priv;	
	struct list_head	qtd_list;

	/* when controller's hung, permit only roothub cleanup attempts
	 * such as powering down ports 
	 */
	if (ehci->disabled) {
		err("%s : EPIPE\n",__FUNCTION__);
		return -1;
	}
		

	INIT_LIST_HEAD (&qtd_list);
		
	/* For the private part of the URB we need the number of QTDs (size) */
	switch (usb_pipetype (pipe)) {
		case PIPE_BULK:	/* one QTD for every 4096 Byte */
			size = (transfer_len - 1) / 4096 + 1;
			break;
		case PIPE_CONTROL: /* 1 QTD for setup, 1 for ACK and 1 for every 4096 B */
			size = (transfer_len == 0)? 2:
						(transfer_len - 1) / 4096 + 3;
			break;
	}


	if (size >= (NUM_QTD - 1)) {
		err("need %d QTDs, only have %d", size, NUM_QTD);
		return -1;
	}
	
	// Prepare USB URB.		
#ifdef ENABLE_KSEG1ADDR
	purb_priv = (struct urb *) KSEG1ADDR(&urb_priv);	
#else /* ENABLE_KSEG1ADDR */
	purb_priv = (struct urb *) &urb_priv;	
#endif /* ENABLE_KSEG1ADDR */
	purb_priv->dev = dev;
	
	qh = ehci_qh_alloc(ehci,purb_priv,pipe);
	
	if (!qh)
	{
		err("%s error : qh is NULL\n",__FUNCTION__);
		return -1;
	}	
		
	purb_priv->pipe = pipe;
	
	/* fill the private part of the URB */
	purb_priv->length = size;
	purb_priv->qh = qh;
	purb_priv->actual_length = 0;
	
	purb_priv->transfer_buffer_length = transfer_len;
	purb_priv->setup_dma = CPHYSADDR(setup);
	purb_priv->transfer_dma = CPHYSADDR(buffer);
	
#if defined(CONFIG_BOOT_USB_RTL8187B_VERIFY)
	purb_priv->transfer_flags |= URB_ZERO_PACKET;
#endif
			
	switch (usb_pipetype (purb_priv->pipe)) {
	// case PIPE_CONTROL:
	// case PIPE_BULK:
	default:
#ifdef ENABLE_KSEG1ADDR
		if (!qh_urb_transaction (ehci, purb_priv, (struct list_head *) KSEG1ADDR(&qtd_list)))
#else /* ENABLE_KSEG1ADDR */
		if (!qh_urb_transaction (ehci, purb_priv, (struct list_head *) &qtd_list))
#endif /* ENABLE_KSEG1ADDR */
			return -ENOMEM;
				
#ifdef ENABLE_KSEG1ADDR
		return submit_async (ehci, dev, purb_priv, (struct list_head *) KSEG1ADDR(&qtd_list));
#else /* ENABLE_KSEG1ADDR */
		return submit_async (ehci, dev, purb_priv, (struct list_head *) &qtd_list);
#endif /* ENABLE_KSEG1ADDR */

	case PIPE_INTERRUPT:
	case PIPE_ISOCHRONOUS:
		printk("%s : Don't support INTERRUPT or ISOCHRONOUS mode\n" ,__FUNCTION__ );
		return -1;
	}
		
	
}		
 
/* De-allocate all resources.. */
static void hc_release_ehci (struct ehci_hcd *ehci)
{
	dbg ("USB HC release ohci usb-%s", ehci->slot_name);

	if (!ehci->disabled)
		ehci_reset (ehci);
}   

/*-------------------------------------------------------------------------*/

/*
 * handshake - spin reading hc until handshake completes or fails
 * @ptr: address of hc register to be read
 * @mask: bits to look at in result of read
 * @done: value of those bits when handshake succeeds
 * @usec: timeout in microseconds
 *
 * Returns negative errno, or zero on success
 *
 * Success happens when the "mask" bits have the specified value (hardware
 * handshake done).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the register reads as all-ones (hardware removed).
 *
 * That last failure should_only happen in cases like physical cardbus eject
 * before driver shutdown. But it also seems to be caused by bugs in cardbus
 * bridge shutdown:  shutting down the bridge before the devices using it.
 */

static int handshake (void __iomem *ptr, u32 mask, u32 done, int usec)
{
	u32	result;

	do {
		result = readl (ptr);
		if (result == ~(u32)0)		/* card removed */
			return -ENODEV;
		result &= mask;
		if (result == done)
			return 0;
		udelay (1);
		usec--;
	} while (usec > 0);
	return -ETIMEDOUT;
}


/*
 * ehci_work is called from some interrupts, timers, and so on.
 * it calls driver completion functions, after dropping ehci->lock.
 */
static void ehci_work (struct ehci_hcd *ehci)
{	
	struct ehci_qh		*qh;
	// UINT8  *buf;
	int timeout = 0;
	
//	UINT32	cmd = readl (&ehci->regs->command);		
//	
//	cmd &= ~(CMD_ASE /*| CMD_RUN*/);
//	(void) handshake (&ehci->regs->status, STS_ASS, 0, 150);	
//	writel (cmd, &ehci->regs->command);			
			
	timeout = 0;
	while (!(readl (&ehci->regs->status) &  STS_RECL))
    {
    	timeout++;
    	udelay(10);
    	if (timeout >= 10000)
			break;
    };
    
    if (timeout >= 10000)
		printk("Polling STS_RECL status timeout!\n");	
	
	if (!++(ehci->stamp))
        ehci->stamp++;
        
	//flush_dcache();
	//Invalid_dcache();
	//dcache_flush_and_invalidate_all();
//--	sys_dcache_flush_and_invalidate_all();
	//sync();
	//dcache_flush_and_invalidate_all();
	//sync();

	qh = ehci->async->qh_next.qh;	

//--	sys_dcache_flush_and_invalidate_all();
/*	
	if (__test_start)
		dbg_echi_dump_all_qh(qh);
*/

	qh_completions (ehci, qh);  
	start_unlink_async(ehci,qh);
	ehci_all_qtd_free();
		
	qh->qh_state = QH_STATE_IDLE;	    

//--	sys_dcache_flush_and_invalidate_all(); //chengying add , avoid hardware don't see td clear
	//sync();
	//dcache_flush_and_invalidate_all();
	//sync();
#if 0	
rescan :
	qh = ehci->async->qh_next.qh;	
	// printk("qh = 0x%x , ehci_head_qh = 0x%x\n",qh,&ehci_head_qh);
	if (likely (qh != NULL)) {	
		do {
			
			/* clean any finished work for this qh */
            if (!list_empty (&qh->qtd_list) && qh->stamp != ehci->stamp) {
            	int temp;
            	            	
            	qh->stamp = ehci->stamp;
				temp = qh_completions (ehci, qh);		
				
				if (list_empty (&qh->qtd_list)) {	
					start_unlink_async (ehci, qh);
					ehci_all_qtd_free();
				}					
				else {
					printk("qh is not empty\n");
					// dbg_echi_dump_all_qh(qh);
					// while(1);
				}				
				
				if (temp != 0) {					
                     goto rescan;
                }
				
            }
            /* unlink idle entries, reducing HC PCI usage as well
             * as HCD schedule-scanning costs.  delay for any qh
             * we just scanned, there's a not-unusual case that it
             * doesn't stay idle for long.
             * (plus, avoids some kind of re-activation race.)
             */
            
            /*
            if (list_empty (&qh->qtd_list)) {            	
                 if (qh->stamp != ehci->stamp) {                 	
                    start_unlink_async (ehci, qh);
                 }               
                printk("qh is empty\n");    
            }
            */
            
			
            qh = qh->qh_next.qh;
       } while (qh);
	}   // End of if (likely (qh != NULL))
            
	
#endif		
}

// #define  RESET_UTMI_REG						(RTD_WRAP_BASE + 0xC)
/*-------------------------------------------------------------------------*/
/* reset a non-running (STS_HALT == 1) controller */
static int ehci_reset (struct ehci_hcd *ehci)
{
	int	retval;
	u32	command = readl (&ehci->regs->command);

	command |= CMD_RESET;
	printf("[cfyeh-debug] %s(%d) command 0x%x regs 0x%x!!!!!!\n", __func__, __LINE__, command, (u32)&ehci->regs->command);
	writel (command, &ehci->regs->command);
	retval = handshake (&ehci->regs->command, CMD_RESET, 0, 250 * 1000);

	/*
	rtd_outl(RESET_UTMI_REG,0x1);   
   	udelay(10*1000);
	*/
	
	/*
	writel(0<<31,0xB80f0810);
	writel(1<<31,0xB80f0810);
	*/

	// udelay(250*1000);	
	rtd_outl(EHCI_INSNREG01,INSNREG01_IN_THRESHOLD(0x40) | INSNREG01_OUT_THRESHOLD(0x100/*0x40*/));		   
   	rtd_outl(EHCI_INSNREG03,INSNREG03_BREAK_MEM_TRAN_EN);
	
	/*
	if (retval)
		return retval;
	*/
	
	return retval;
}

static void ehci_stop (struct ehci_hcd *ehci)
{		
	writel (0, &ehci->regs->command);
	
	ehci_reset (ehci);
	writel (0, &ehci->regs->intr_enable);
	

	/* let companion controllers work when we aren't */
	writel (0, &ehci->regs->configured_flag);

	/* root hub is shut down separately (first, when possible) */
	
	if (ehci->async)
		ehci_work (ehci);

#ifdef	EHCI_STATS
	ehci_dbg (ehci, "irq normal %ld err %ld reclaim %ld (lost %ld)\n",
		ehci->stats.normal, ehci->stats.error, ehci->stats.reclaim,
		ehci->stats.lost_iaa);
	ehci_dbg (ehci, "complete %ld unlink %ld\n",
		ehci->stats.complete, ehci->stats.unlink);
#endif

}

/* force HC to halt state from unknown (EHCI spec section 2.3) */
//static int ehci_halt (struct ehci_hcd *ehci)
//{
//	u32	temp = readl (&ehci->regs->status);
//
//	if ((temp & STS_HALT) != 0)
//		return 0;
//
//	temp = readl (&ehci->regs->command);
//	temp &= ~CMD_RUN;
//	writel (temp, &ehci->regs->command);
//	return handshake (&ehci->regs->status, STS_HALT, STS_HALT, 16 * 125);
//}

/* start HC running; it's halted, ehci_init() has been run (once) */
static int ehci_run (struct ehci_hcd *ehci)
{
	int			retval;
	u32			temp;
	u32			hcc_params;
	
	int park = 1;
	
	ehci->disabled = 1;

	/* EHCI spec section 4.1 */
	if ((retval = ehci_reset(ehci)) != 0) {
		hc_release_ehci(ehci);
		return retval;
	}
	
	// writel(ehci->periodic_dma, &ehci->regs->frame_list);
	// writel((u32)ehci->async->qh_dma, &ehci->regs->async_next);	

	/*
	 * hcc_params controls whether ehci->regs->segment must (!!!)
	 * be used; it constrains QH/ITD/SITD and QTD locations.
	 * pci_pool consistent memory always uses segment zero.
	 * streaming mappings for I/O buffers, like pci_map_single(),
	 * can return segments above 4GB, if the device allows.
	 *
	 * NOTE:  the dma mask is visible through dma_supported(), so
	 * drivers can pass this info along ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so forth.  It's readonly to all
	 * host side drivers though.
	 */
	hcc_params = readl(&ehci->caps->hcc_params);
	
	/* cache this readonly data; minimize chip reads */
	ehci->hcs_params = readl (&ehci->caps->hcs_params);

	/* clear interrupt enables, set irq latency */
	if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
		
	temp = 1 << (16 + log2_irq_thresh);
	if (HCC_CANPARK(hcc_params)) {
		/* HW default park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by avoiding QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		if (park) {
			// park = min_t ((unsigned) , park,  3);
			temp |= CMD_PARK;
			temp |= park << 8;
		}
		// ehci_info (ehci, "park %d\n", park);
	}
	if (HCC_PGM_FRAMELISTLEN (hcc_params)) {
		/* periodic schedule size can be smaller than default */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
		/*
		switch (EHCI_TUNE_FLS) {			
		case 0: ehci->periodic_size = 1024; break;
		case 1: ehci->periodic_size = 512; break;
		case 2: ehci->periodic_size = 256; break;		
		default:	// BUG ();
			printk("%s : Bug\n",__FUNCTION__);
		}
		*/
	}
#ifdef ENABLE_KSEG1ADDR
	ehci->async = (struct ehci_qh *) KSEG1ADDR(&ehci_head_qh);	
	ehci->async->dummy = (struct ehci_qtd *) KSEG1ADDR(&dummy_qtd);
#else /* ENABLE_KSEG1ADDR */
	ehci->async = (struct ehci_qh *) &ehci_head_qh;	
	ehci->async->dummy = (struct ehci_qtd *) &dummy_qtd;
#endif /* ENABLE_KSEG1ADDR */
	ehci->async->qh_next.qh = NULL;
    ehci->async->hw_next = QH_NEXT (ehci->async->qh_dma);
    ehci->async->hw_info1 = cpu_to_le32 (QH_HEAD);
    ehci->async->hw_token = cpu_to_le32 (QTD_STS_HALT);
    ehci->async->hw_qtd_next = EHCI_LIST_END;
    ehci->async->qh_state = QH_STATE_LINKED;
    ehci->async->hw_alt_next = QTD_NEXT (ehci->async->dummy->qtd_dma);

//--	sys_dcache_flush_and_invalidate_all();
	
	writel((u32)ehci->async->qh_dma, &ehci->regs->async_next);

	// Philips, Intel, and maybe others need CMD_RUN before the
	// root hub will detect new devices (why?); NEC doesn't
	temp |= CMD_RUN;
//--	printf("[cfyeh-debug] %s(%d) temp 0x%x regs 0x%x!!!!!!\n", __func__, __LINE__, temp, (u32)&ehci->regs->command);
	writel (temp, &ehci->regs->command);	
	

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is integrated,
	 * and there's no companion controller unless maybe for USB OTG.)
	 */

	writel (FLAG_CF, &ehci->regs->configured_flag);
	readl (&ehci->regs->command);	/* unblock posted writes */	

	// udelay(1000);
		

	temp = HC_VERSION(readl (&ehci->caps->hc_capbase));
	/*
	ehci_info (ehci,
		"USB %x.%x started, EHCI %x.%02x, driver %s%s\n",
		((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
		temp >> 8, temp & 0xff, DRIVER_VERSION,
		ignore_oc ? ", overcurrent ignored" : "");
	*/
	//writel (INTR_MASK, &ehci->regs->intr_enable); /* Turn On Interrupts */

	/* GRR this is run-once init(), being done every time the HC starts.
	 * So long as they're part of class devices, we can't do it init()
	 * since the class device isn't created that early.
	 */
	// create_debug_files(ehci);
	
	ehci->disabled = 0;
	return 0;
}


/*-------------------------------------------------------------------------*/
static void
ehci_hub_descriptor (
	struct ehci_hcd			*ehci,
	struct usb_hub_descriptor	*desc
) {
	int		ports = HCS_N_PORTS (ehci->hcs_params);
	u16		temp;

	desc->bDescriptorType = 0x29;
	desc->bPwrOn2PwrGood = 10;	/* ehci 1.0, 2.3.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bLength = 7 + 2 * temp;

	/* two bitmaps:  ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	/*
	memset (&desc->bitmap [0], 0, temp);
	memset (&desc->bitmap [temp], 0xff, temp);
	*/
	
	temp = 0x0008;			/* per-port overcurrent reporting */
	if (HCS_PPC (ehci->hcs_params))
		temp |= 0x0001;		/* per-port power control */
	else
		temp |= 0x0002;		/* no power switching */
#if 0
// re-enable when we support USB_PORT_FEAT_INDICATOR below.
	if (HCS_INDICATOR (ehci->hcs_params))
		temp |= 0x0080;		/* per-port indicators (LEDs) */
#endif
	desc->wHubCharacteristics = (__u16)cpu_to_le16 (temp);
}


static int check_reset_complete (
	struct ehci_hcd	*ehci,
	int		index,
	int		port_status
) {
	if (!(port_status & PORT_CONNECT)) {
		// ehci->reset_done [index] = 0;
		return port_status;
	}

	/* if reset finished and it's still not enabled -- handoff */
	if (!(port_status & PORT_PE)) {

		/* with integrated TT, there's nobody to hand it to! */
		if (ehci_is_TDI(ehci)) {
			ehci_dbg (ehci,
				"Failed to enable port %d on root hub TT\n",
				index+1);
			return port_status;
		}

		ehci_dbg (ehci, "port %d full speed --> companion\n",
			index + 1);

		// what happens if HCS_N_CC(params) == 0 ?
		port_status |= PORT_OWNER;
		writel (port_status, &ehci->regs->port_status [index]);

	} else
		ehci_dbg (ehci, "port %d high speed\n", index + 1);

	return port_status;
}

/* request to virtual root hub */
static int rh_check_port_status(struct ehci_hcd *ehci)
{
	__u32 temp , ndp, i;  
	int res;

	res = -1;
	// temp = roothub_a (controller);
	// ndp = (temp & RH_A_NDP);
	ndp = HCS_N_PORTS (ehci->hcs_params);
	for (i = 0; i < ndp; i++) {
		temp = readl (&ehci->regs->port_status [i]);
		/* check for a device disconnect */
		if (/*((temp & (PORT_PEC | PORT_CSC)) ==
			(PORT_PEC | PORT_CSC)) &&*/
			((temp & PORT_CSC) == 0)) {
			res = i;
			break;
		}
	}
	return res;
}


#define	PORT_WAKE_BITS 	(PORT_WKOC_E|PORT_WKDISC_E|PORT_WKCONN_E)
static int ehci_submit_rh_msg 
(struct usb_device *dev, unsigned long pipe,
		void *buffer, int transfer_len, struct devrequest *cmd)
{
	void * data = buffer;
	int leni = transfer_len;
	int len = 0;
	int stat = 0;
	
	__u32 datab[4];
	__u8 *data_buf = (__u8 *)datab;
	__u16 bmRType_bReq;
	__u16 wValue;
	__u16 wIndex;
	__u16 wLength;
		
	struct ehci_hcd	*ehci = &rtd_ehci;
	int		ports = HCS_N_PORTS (ehci->hcs_params);
	u32		temp, status;
	// unsigned long	flags;
	int		retval = 0;
	
#ifdef DEBUG
	//urb_priv.actual_length = 0;
	pkt_print(dev, pipe, buffer, transfer_len, cmd, "SUB(rh)", usb_pipein(pipe));

#else
       wait_ms(1);
#endif

//	if ((pipe & PIPE_INTERRUPT) == PIPE_INTERRUPT) {
//		info("Root-Hub submit IRQ: NOT implemented");
//		return 0;
//	}
	
	bmRType_bReq  = cmd->requesttype | (cmd->request << 8);	
	wValue        =  m16_swap(cmd->value);
	wIndex        =  m16_swap(cmd->index);
	wLength       =  m16_swap(cmd->length);
	
	info("Root-Hub (EHCI) : adr: 0x%x cmd(0x%x): 0x%x 0x%x 0x%x 0x%x\n",
		dev->devnum, 8, bmRType_bReq, wValue, wIndex, wLength);
	/*
	 * FIXME:  support SetPortFeatures USB_PORT_FEAT_INDICATOR.
	 * HCS_INDICATOR may say we can change LEDs to off/amber/green.
	 * (track current state ourselves) ... blink for diagnostics,
	 * power, "this is the one", etc.  EHCI spec supports this.
	 */
	
	switch (bmRType_bReq) {
		// Root Hub : Get status.
		case RH_GET_STATUS:
			*(__u16 *) data_buf = m16_swap (1); OK (2);
		case RH_GET_STATUS | RH_INTERFACE:
			*(__u16 *) data_buf = m16_swap (0); OK (2);
		case RH_GET_STATUS | RH_ENDPOINT:
			*(__u16 *) data_buf = m16_swap (0); OK (2);
		// Get Root hub status	
		case RH_GET_STATUS | RH_CLASS:
			*(__u32 *) data_buf = m32_swap (0);
			OK (2);	
		// Get Port Status	
		case RH_CLEAR_FEATURE | RH_ENDPOINT:
			switch (wValue) {
				case (RH_ENDPOINT_STALL): OK (0);
			}
		break;	
		
		// ClearHubFeature
		case RH_CLEAR_FEATURE | RH_CLASS: 
			switch (wValue) {
			case C_HUB_LOCAL_POWER:
			case C_HUB_OVER_CURRENT:
				/* no hub-wide feature/status flags */
				break;
			default:
				goto error;
			}
		break;
		
		// ClearPortFeature
		case RH_CLEAR_FEATURE | RH_OTHER | RH_CLASS: 
			if (!wIndex || wIndex > ports)
				goto error;
			wIndex--;
			temp = readl (&ehci->regs->port_status [wIndex]);
			if (temp & PORT_OWNER)
				break;

			switch (wValue) {
				case USB_PORT_FEAT_ENABLE:
					writel (temp & ~PORT_PE,
						&ehci->regs->port_status [wIndex]);
				break;
				case USB_PORT_FEAT_C_ENABLE:
					writel (temp | PORT_PEC,
						&ehci->regs->port_status [wIndex]);
				break;
				case USB_PORT_FEAT_SUSPEND:
					if (temp & PORT_RESET)
						goto error;
					if (temp & PORT_SUSPEND) {
						if ((temp & PORT_PE) == 0)
							goto error;
						/* resume signaling for 20 msec */
						writel ((temp & ~PORT_WAKE_BITS) | PORT_RESUME,
							&ehci->regs->port_status [wIndex]);
						/*	
						ehci->reset_done [wIndex] = jiffies
								+ msecs_to_jiffies (20);
						*/		
					}
				break;
				case USB_PORT_FEAT_C_SUSPEND:
				/* we auto-clear this feature */
				break;
				case USB_PORT_FEAT_POWER:
					if (HCS_PPC (ehci->hcs_params))
						writel (temp & ~PORT_POWER,
							&ehci->regs->port_status [wIndex]);
				break;
				case USB_PORT_FEAT_C_CONNECTION:
					writel (temp | PORT_CSC,
						&ehci->regs->port_status [wIndex]);
				break;
				case USB_PORT_FEAT_C_OVER_CURRENT:
					writel (temp | PORT_OCC,
						&ehci->regs->port_status [wIndex]);
				break;
				case USB_PORT_FEAT_C_RESET:
					/* GetPortStatus clears reset */
				break;
				default:
				goto error;
			}
			readl (&ehci->regs->command);	/* unblock posted write */
			break;
	
			case RH_SET_ADDRESS: 
				rtd_ehci.rh.devnum = wValue; OK(0);
		
			// GetHubDescriptor	
			case RH_GET_DESCRIPTOR :
				switch ((wValue & 0xff00) >> 8) {
					case (0x01): /* device descriptor */
						len = min_t(unsigned int,
					  				leni,
					  				min_t(unsigned int,
					     			sizeof (root_hub_dev_des),
					      			wLength));
						data_buf = root_hub_dev_des; OK(len);
					case (0x02): /* configuration descriptor */
						len = min_t(unsigned int,
					  				leni,
					  				min_t(unsigned int,
					      			sizeof (root_hub_config_des),
					      			wLength));
						data_buf = root_hub_config_des; OK(len);
					case (0x03): /* string descriptors */
						if(wValue==0x0300) {
							len = min_t(unsigned int,
						  				leni,
						  				min_t(unsigned int,
						      			sizeof (root_hub_str_index0),
						      			wLength));
							data_buf = root_hub_str_index0;
							OK(len);
						}
						if(wValue==0x0301) {
							len = min_t(unsigned int,
						  				leni,
						  				min_t(unsigned int,
						      			sizeof (root_hub_str_index1),
						     			wLength));
							data_buf = root_hub_str_index1;
							OK(len);
						}
					default:
						stat = USB_ST_STALLED;
				}		    
			break;
			
			case RH_GET_DESCRIPTOR | RH_CLASS:
	    	{
				ehci_hub_descriptor (ehci, (struct usb_hub_descriptor *)
					data_buf);

				len = min_t(unsigned int, leni,
			      	min_t(unsigned int, data_buf [0], wLength));	
			    OK (len);  	
			}
					
			/*
			case GetHubStatus: 
				// no hub-wide feature/status flags
				memset (data, 0, 4);
				//cpu_to_le32s ((u32 *) buf);
			break;
			*/
			
			// GetPortStatus:
			case RH_GET_STATUS | RH_OTHER | RH_CLASS:
				if (!wIndex || wIndex > ports)
					goto error;
				wIndex--;
				status = 0;
				temp = readl (&ehci->regs->port_status [wIndex]);

				// wPortChange bits
				if (temp & PORT_CSC)
					status |= 1 << USB_PORT_FEAT_C_CONNECTION;
				if (temp & PORT_PEC)
					status |= 1 << USB_PORT_FEAT_C_ENABLE;
				if (temp & PORT_OCC)
					status |= 1 << USB_PORT_FEAT_C_OVER_CURRENT;

				/* whoever resumes must GetPortStatus to complete it!! */
				if (temp & PORT_RESUME) {
					status |= 1 << USB_PORT_FEAT_C_SUSPEND;
					// ehci->reset_done [wIndex] = 0;

					/* stop resume signaling */
					temp = readl (&ehci->regs->port_status [wIndex]);
					writel (temp & ~PORT_RESUME, &ehci->regs->port_status [wIndex]);
					retval = handshake (
						&ehci->regs->port_status [wIndex],
						PORT_RESUME, 0, 2000 /* 2msec */);
					if (retval != 0) {
						ehci_err (/*ehci,*/ "port %d resume error %d\n",
							wIndex + 1, retval);
						goto error;
					}
					temp &= ~(PORT_SUSPEND|PORT_RESUME|(3<<10));
				}

				/* whoever resets must GetPortStatus to complete it!! */
				if (temp & PORT_RESET) {
					status |= 1 << USB_PORT_FEAT_C_RESET;
					// ehci->reset_done [wIndex] = 0;

					/* force reset to complete */
					writel (temp & ~PORT_RESET,
							&ehci->regs->port_status [wIndex]);
					/* REVISIT:  some hardware needs 550+ usec to clear
			 		* this bit; seems too long to spin routinely...
			 		*/
					retval = handshake (
							&ehci->regs->port_status [wIndex],
							PORT_RESET, 0, 750);
					if (retval != 0) {
						ehci_err (/*ehci,*/ "port %d reset error %d\n",
							wIndex + 1, retval);
						goto error;
					}

					/* see what we found out */
					temp = check_reset_complete (ehci, wIndex,
					readl (&ehci->regs->port_status [wIndex]));
				}

				// don't show wPortStatus if it's owned by a companion hc
				if (!(temp & PORT_OWNER)) {
					if (temp & PORT_CONNECT) {
						status |= 1 << USB_PORT_FEAT_CONNECTION;
						// status may be from integrated TT
						status |= ehci_port_speed(ehci, temp);						
					}
					if (temp & PORT_PE)
						status |= 1 << USB_PORT_FEAT_ENABLE;
					if (temp & (PORT_SUSPEND|PORT_RESUME))
						status |= 1 << USB_PORT_FEAT_SUSPEND;
					if (temp & PORT_OC)
						status |= 1 << USB_PORT_FEAT_OVER_CURRENT;
					if (temp & PORT_RESET)
						status |= 1 << USB_PORT_FEAT_RESET;
					if (temp & PORT_POWER)
						status |= 1 << USB_PORT_FEAT_POWER;
				}

#ifndef	EHCI_VERBOSE_DEBUG
				if (status & ~0xffff)	/* only if wPortChange is interesting */
#endif
				// dbg_port (ehci, "GetStatus", wIndex + 1, temp);
				// printk("Port%d : GetStatus = 0x%x\n ", wIndex + 1, temp);
				// we "know" this alignment is good, caller used kmalloc()...
				*((__le32 *) data_buf) = cpu_to_le32 (status);
				len = 4;

			break;
			// SetHubFeature
			case RH_SET_FEATURE | RH_CLASS:
				switch (wValue) {
					case C_HUB_LOCAL_POWER:
					case C_HUB_OVER_CURRENT:
					/* no hub-wide feature/status flags */
					break;
					default:
						goto error;
				}
			break;
			// SetPortFeature
			case RH_SET_FEATURE | RH_OTHER | RH_CLASS: 
				if (!wIndex || wIndex > ports)
					goto error;
				wIndex--;
				temp = readl (&ehci->regs->port_status [wIndex]);
				if (temp & PORT_OWNER)
					break;

				switch (wValue) {
					case USB_PORT_FEAT_SUSPEND:
						if ((temp & PORT_PE) == 0
								|| (temp & PORT_RESET) != 0)
							goto error;
					/*	
					if (hcd->remote_wakeup)
						temp |= PORT_WAKE_BITS;
					*/
				
						writel (temp | PORT_SUSPEND,
							&ehci->regs->port_status [wIndex]);
					break;
					case USB_PORT_FEAT_POWER:
						if (HCS_PPC (ehci->hcs_params)) {
							writel (temp | PORT_POWER,
							&ehci->regs->port_status [wIndex]);
							#ifdef usb_speed_up
							wait_ms(10);
							#else
							wait_ms(100);
							#endif
						}
						break;
					case USB_PORT_FEAT_RESET:
						if (temp & PORT_RESUME)
							goto error;
						/* line status bits may report this as low speed,
			 		 	* which can be fine if this root hub has a
			 		 	* transaction translator built in.
			 		 	*/
						if ((temp & (PORT_PE|PORT_CONNECT)) == PORT_CONNECT
							&& !ehci_is_TDI(ehci)
							&& PORT_USB11 (temp)) {
							ehci_dbg (ehci,
								"port %d low speed --> companion\n",
								wIndex + 1);
							temp |= PORT_OWNER;

						} else {
							// ehci_vdbg (ehci, "port %d reset\n", wIndex + 1);
							temp |= PORT_RESET;
							temp &= ~PORT_PE;

							/*
				 		 	 * caller must wait, then call GetPortStatus
				 		 	 * usb 2.0 spec says 50 ms resets on root
				 		 	 */
							/* 
							ehci->reset_done [wIndex] = jiffies
							+ msecs_to_jiffies (50);
							*/		
						}
						writel (temp, &ehci->regs->port_status [wIndex]);
					break;							
					default:
						goto error;
			}
//printf("[DEBUG_MSG] %s:%d, &ehci->regs->command=%x\n", __FUNCTION__, __LINE__, (u32)&ehci->regs->command);
			readl (&ehci->regs->command);	/* unblock posted writes */
//printf("[DEBUG_MSG] %s:%d\n", __FUNCTION__, __LINE__);
			break;						
			
			case RH_GET_CONFIGURATION: 	*(__u8 *) data_buf = 0x01; OK (1);
			case RH_SET_CONFIGURATION: 	OK (0);
					
			default:
				printk("Unsupported root hub command : (bmRType_bReq = 0x%x)\n",bmRType_bReq);				
error:
				/* "stall" on error */		
				stat = USB_ST_STALLED;
		}
		
	len = min_t(int, len, leni);
	
//printf("[DEBUG_MSG] %s:%d, data=%p, data_buf=%x\n", __FUNCTION__, __LINE__, data, (u32)data_buf);
	if (data && data != data_buf)
	    memcpy (data, data_buf, len);	
	
	dev->act_len = len;
	dev->status = stat;
		
	return stat;
}

/*
static int delay = 3;
static int my_count = 0;
*/

/* common code for handling submit messages - used for all but root hub */
/* accesses. */
static int ehci_submit_common_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup, int interval)
{
	
	int stat = 0;
	int maxsize = usb_maxpacket(dev, pipe);
	int timeout;
	
	// void *buffer = (void *) KSEG1ADDR(data);
	// int forbidden = 1 , count = 0;
	
	/* device pulled? Shortcut the action. */	
//	if (devgone == dev) {
//		dev->status = USB_ST_CRC_ERR;
//		return 0;
//	}


#if defined(CONFIG_BOOT_VERIFY_VM)		
		LXBusProcess();
#endif
	
	

#ifdef DEBUG
	//urb_priv.actual_length = 0;
	pkt_print(dev, pipe, buffer, transfer_len, setup, "SUB", usb_pipein(pipe));
#else
        wait_ms(1);

#endif
	if (!maxsize) {
		err("submit_common_message: pipesize for pipe 0x%lx is zero",
			pipe);
		return -1;
	}

//retry:

	//if (ehci_submit_job(dev, pipe, buffer, transfer_len, setup, interval) < 0) {
	if (ehci_submit_job(dev, pipe, buffer, transfer_len, setup, interval) != 0) {
		err("ehci_submit_job failed");
		return -1;
	}
		

	wait_ms(10);
	/* ohci_dump_status(&gohci); */

	/* allow more time for a BULK device to react - some are slow */
#define BULK_TO	 5000	/* timeout in milliseconds */
	if (usb_pipetype (pipe) == PIPE_BULK)
		timeout = BULK_TO;
	else
		timeout = 100;			

	
	// writel(0x4,0xb8001024);
	
	
	/* wait for it to complete */
	for (;;) {
		/* check whether the controller is done */

#if defined(CONFIG_BOOT_VERIFY_VM)		
		LXBusProcess();
#endif
		
		stat = ehci_irq();
					
	
		if (stat < 0) {
			stat = USB_ST_CRC_ERR;
			break;
		}
		if (stat >= 0 && stat != 0xff) {
			/* 0xff is returned for an SF-interrupt */
			break;
		}
		
		
		if (--timeout) {
			wait_ms(1); 
		} else {
			err("CTL:TIMEOUT ");
			transfer_len = 0;
			stat = USB_ST_CRC_ERR;
						
		//	 udelay(10*1000000);			
			break;
		}
		
	}
		
		
	/* we got an Root Hub Status Change interrupt */
	if (got_rhsc) {
//printk("\n[DEBUG_MSG] Got Root Hub Status Change!\n");
#ifdef DEBUG
		// ohci_dump_roothub (&gohci, 1);
#endif
		got_rhsc = 0;
		/* abuse timeout */
		timeout = rh_check_port_status(&rtd_ehci);
		if (timeout >= 0) {
#if 0 /* this does nothing useful, but leave it here in case that changes */
			/* the called routine adds 1 to the passed value */
			usb_hub_port_connect_change(gohci.rh.dev, timeout - 1);
#endif
			/*
			 * XXX
			 * This is potentially dangerous because it assumes
			 * that only one device is ever plugged in!
			 */
			devgone = dev;
		}
	}
	
	/*
	if (readl(0xB80f0810) & (1<<31)) {		
		writel(1<<31,0xB80f0810);
		
		// Reset Wrap.
		writel(0<<29,0xB80f0810);
		writel(1<<29,0xB80f0810);
		
		printk("\n%s (Error) : Wrap Error\n", __FUNCTION__);
		goto retry;					
	}	
	*/
	
	// Reset Wrap.
	/*
	writel(0<<29,0xB80f0810);
	writel(1<<29,0xB80f0810);
	*/
		
	dev->status = stat;
	dev->act_len = transfer_len;
	// dev->act_len = purb_priv->actual_length;

#ifdef DEBUG
	pkt_print(dev, pipe, buffer, transfer_len, setup, "RET(ctlr)", usb_pipein(pipe));
#else
        wait_ms(1);
#endif

	/* free TDs in urb_priv */
	urb_free_priv (&urb_priv);
	return 0;
}

int ehci_submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup)
{
	int maxsize = usb_maxpacket(dev, pipe);
	
	info("submit_control_msg\n");
	
#ifdef DEBUG
	//urb_priv.actual_length = 0;
	pkt_print(dev, pipe, buffer, transfer_len, setup, "SUB", usb_pipein(pipe));

#else
        wait_ms(1);
#endif	

	if (!maxsize) {
		err("submit_control_message: pipesize for pipe 0x%lx is zero",
			pipe);
		return -1;
	}
	
	if (((pipe >> 8) & 0x7f) == rtd_ehci.rh.devnum) {
		rtd_ehci.rh.dev = dev;
		/* root hub - redirect */
		
		return ehci_submit_rh_msg(dev, pipe, buffer, transfer_len,setup);
	}

	dev->speed = USB_SPEED_HIGH;	
	return ehci_submit_common_msg(dev, pipe, buffer, transfer_len, setup, 0);
}

/*
#define 	TEST_ADDR			(0xA0000100)
static void *__test_buf = NULL;
*/

extern UINT32 usb_verify_download_addr;
#define USB_DOWNLOAD_TARGET_ADDR	(0xA0400000)

int ehci_submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len)
{
	// int status = 0;
	 info("submit_bulk_msg\n");
	dev->speed = USB_SPEED_HIGH;

	return ehci_submit_common_msg(dev, pipe, buffer, transfer_len, NULL, 0);


//#if !defined(CONFIG_BOOT_USB_VERIFY)	
//	return submit_common_msg(dev, pipe, buffer, transfer_len, NULL, 0);
//#else
//	status = submit_common_msg(dev, pipe, buffer, transfer_len, NULL, 0);
//	
//	if (CPHYSADDR(buffer) < CPHYSADDR(USB_DOWNLOAD_TARGET_ADDR)) {
//		char *buf = 0;
//		buf = (UINT8  *) USB_DOWNLOAD_TARGET_ADDR;
//		buf += (CPHYSADDR(buffer) - CPHYSADDR(usb_verify_download_addr));
//		if(memcmp(buf,buffer,transfer_len)) {
//			printk("Error : buffer = 0x%x , buf = 0x%x\n",buffer,buf);			
//			while(1);
//		}
//	}
//	
//	return status;
//	
//#endif	

	
	
#if 0
	if (usb_pipetype (pipe) == PIPE_BULK && usb_pipein (pipe) && transfer_len > 0) {
		// purb_priv->transfer_dma = CPHYSADDR(TEST_ADDR);
		__test_buf = buffer;
		memcpy((void *) TEST_ADDR ,__test_buf, transfer_len);	
		status = ehci_submit_common_msg(dev, pipe, (void *) TEST_ADDR /* buffer */, transfer_len, NULL, 0);		
	}
	else
		status = ehci_submit_common_msg(dev, pipe, buffer, transfer_len, NULL, 0);	
	
		
	if ((usb_pipetype (/*purb_priv->*/pipe) == PIPE_BULK &&  usb_pipein (/*purb_priv->*/pipe)) && (transfer_len > 0)) {
		// printk("\npurb_priv->transfer_buffer_length =%d ,purb_priv->transfer_dma =0x%x \n",purb_priv->transfer_buffer_length,purb_priv->transfer_dma);
		// printk("\npurb_priv->actual_length = %d\n",purb_priv->actual_length);		
		// memset(__test_buf,0,purb_priv->transfer_buffer_length);		
		memcpy(__test_buf,(void *) TEST_ADDR , transfer_len);		
	}	
	
	return status;
#endif		

}

/*
int submit_int_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, int interval)
{
	// info("submit_int_msg\n");
	return -1;
}
*/


int ehci_lowlevel_init(void)
{
	// writel(0xC,0xb8001038);
	// writel(0xffffffff,0xb8001018);
	
	memset (&rtd_ehci, 0, sizeof (struct ehci_hcd));
	rtd_ehci.caps = (struct ehci_caps *) RTD_EHCI_BASE;
	rtd_ehci.regs = (struct ehci_regs *) (RTD_EHCI_BASE + 0x10);
	
	rtd_ehci.irq = -1;
	rtd_ehci.disabled = 1;
	
	rtd_ehci.slot_name = "RTD2885_EHCI";
	
	memset(g_qtd, 0, sizeof(struct ehci_qtd) * (NUM_QTD + 1));
#ifdef ENABLE_KSEG1ADDR
	p_qtd = (struct ehci_qtd *) KSEG1ADDR(g_qtd);
#else /* ENABLE_KSEG1ADDR */
	p_qtd = (struct ehci_qtd *) g_qtd;
#endif /* ENABLE_KSEG1ADDR */
	
	memset(&ehci_dev,0,sizeof(ehci_dev));
	pehci_dev = &ehci_dev;
	
	/*
	memset(&dummy_qtd,0,sizeof(dummy_qtd));
	INIT_LIST_HEAD (&dummy_qtd.qtd_list);	
	*/
	dummy_qtd.qtd_dma = CPHYSADDR(&dummy_qtd);
	ehci_qtd_init(&dummy_qtd,dummy_qtd.qtd_dma);
	
	memset(&ehci_head_qh,0,sizeof(ehci_head_qh));

	ehci_head_qh.ehci = &rtd_ehci;
	ehci_head_qh.qh_dma = CPHYSADDR(&ehci_head_qh);	

	INIT_LIST_HEAD (&ehci_head_qh.qtd_list);
		
	/* dummy td enables safe urb queuing */
	ehci_head_qh.dummy = &dummy_qtd;

	ehci_run(&rtd_ehci);
	
	return 0;
}


int ehci_lowlevel_stop(void)
{
	memset (&rtd_ehci, 0, sizeof (struct ehci_hcd));
	rtd_ehci.caps = (struct ehci_caps *) RTD_EHCI_BASE;
	rtd_ehci.regs = (struct ehci_regs *) (RTD_EHCI_BASE + 0x10);
	ehci_stop(&rtd_ehci);
	
	return 0;
}




#ifdef CONFIG_BOOT_USB_EHCI1

int ehci1_lowlevel_init(void)
{
	// writel(0xC,0xb8001038);
	// writel(0xffffffff,0xb8001018);
	
	memset (&rtd_ehci, 0, sizeof (struct ehci_hcd));
	rtd_ehci.caps = (struct ehci_caps *) RTD_EHCI1_BASE;
	rtd_ehci.regs = (struct ehci_regs *) (RTD_EHCI1_BASE + 0x10);
	
	rtd_ehci.irq = -1;
	rtd_ehci.disabled = 1;
	
	rtd_ehci.slot_name = "RTD2885_EHCI1";
	
	memset(g_qtd, 0, sizeof(struct ehci_qtd) * (NUM_QTD + 1));
#ifdef ENABLE_KSEG1ADDR
	p_qtd = (struct ehci_qtd *) KSEG1ADDR(g_qtd);
#else /* ENABLE_KSEG1ADDR */
	p_qtd = (struct ehci_qtd *) g_qtd;
#endif /* ENABLE_KSEG1ADDR */
	
	memset(&ehci_dev,0,sizeof(ehci_dev));
	pehci_dev = &ehci_dev;
	
	/*
	memset(&dummy_qtd,0,sizeof(dummy_qtd));
	INIT_LIST_HEAD (&dummy_qtd.qtd_list);	
	*/
	dummy_qtd.qtd_dma = CPHYSADDR(&dummy_qtd);
	ehci_qtd_init(&dummy_qtd,dummy_qtd.qtd_dma);
	
	memset(&ehci_head_qh,0,sizeof(ehci_head_qh));

	ehci_head_qh.ehci = &rtd_ehci;
	ehci_head_qh.qh_dma = CPHYSADDR(&ehci_head_qh);	

	INIT_LIST_HEAD (&ehci_head_qh.qtd_list);
		
	/* dummy td enables safe urb queuing */
	ehci_head_qh.dummy = &dummy_qtd;

	ehci_run(&rtd_ehci);
	
	return 0;
}


int ehci1_lowlevel_stop(void)
{
	memset (&rtd_ehci, 0, sizeof (struct ehci_hcd));
	rtd_ehci.caps = (struct ehci_caps *) RTD_EHCI1_BASE;
	rtd_ehci.regs = (struct ehci_regs *) (RTD_EHCI1_BASE + 0x10);
	ehci_stop(&rtd_ehci);
	
	return 0;
}



#endif




