/*
 * Copyright (c) 2001-2002 by David Brownell
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
* Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LINUX_EHCI_HCD_H
#define __LINUX_EHCI_HCD_H

#include <linux/list.h>
#include <usb/usb_defs.h>


// From Linux 2.6 drivers/usb/core/hcd.h
/* class requests from the USB 2.0 hub spec, table 11-15 */
/* GetBusState and SetHubDescriptor are optional, omitted */

/* USB HUB CONSTANTS (not OHCI-specific; see hub.h) */
/* Requests: bRequest << 8 | bmRequestType */

/* destination of request */
#define RH_INTERFACE               0x01
#define RH_ENDPOINT                0x02
#define RH_OTHER                   0x03

#define RH_CLASS                   0x20
#define RH_VENDOR                  0x40

/* Requests: bRequest << 8 | bmRequestType */
#define RH_GET_STATUS           0x0080
#define RH_CLEAR_FEATURE        0x0100
#define RH_SET_FEATURE          0x0300
#define RH_SET_ADDRESS		0x0500
#define RH_GET_DESCRIPTOR	0x0680
#define RH_SET_DESCRIPTOR       0x0700
#define RH_GET_CONFIGURATION	0x0880
#define RH_SET_CONFIGURATION	0x0900
#define RH_GET_STATE            0x0280
#define RH_GET_INTERFACE        0x0A80
#define RH_SET_INTERFACE        0x0B00
#define RH_SYNC_FRAME           0x0C80
/* Our Vendor Specific Request */
#define RH_SET_EP               0x2000


/* Hub port features */
#define RH_PORT_CONNECTION         0x00
#define RH_PORT_ENABLE             0x01
#define RH_PORT_SUSPEND            0x02
#define RH_PORT_OVER_CURRENT       0x03
#define RH_PORT_RESET              0x04
#define RH_PORT_POWER              0x08
#define RH_PORT_LOW_SPEED          0x09

#define RH_C_PORT_CONNECTION       0x10
#define RH_C_PORT_ENABLE           0x11
#define RH_C_PORT_SUSPEND          0x12
#define RH_C_PORT_OVER_CURRENT     0x13
#define RH_C_PORT_RESET            0x14

/* Hub features */
#define RH_C_HUB_LOCAL_POWER       0x00
#define RH_C_HUB_OVER_CURRENT      0x01

#define RH_DEVICE_REMOTE_WAKEUP    0x00
#define RH_ENDPOINT_STALL          0x01

#define RH_ACK                     0x01
#define RH_REQ_ERR                 -1
#define RH_NACK                    0x00



struct urb;

/* Virtual Root HUB */
struct virt_root_hub {
	int devnum; /* Address of Root Hub endpoint */
	void *dev;  /* was urb */
	void *int_addr;
	int send;
	int interval;
};

/* definitions used for the EHCI driver */

/* statistics can be kept for for tuning/monitoring */
//struct ehci_stats {
//	/* irq usage */
//	unsigned long		normal;
//	unsigned long		error;
//	unsigned long		reclaim;
//	unsigned long		lost_iaa;
//
//	/* termination of urbs from core */
//	unsigned long		complete;
//	unsigned long		unlink;
//};


/* ehci_hcd->lock guards shared data against other CPUs:
 *   ehci_hcd:	async, reclaim, periodic (and shadow), ...
 *   usb_host_endpoint: hcpriv
 *   ehci_qh:	qh_next, qtd_list
 *   ehci_qtd:	qtd_list
 *
 * Also, hold this lock when talking to HC registers or
 * when updating hw_* fields in shared qh/qtd/... structures.
 */

#define	EHCI_MAX_ROOT_PORTS	15		/* see HCS_N_PORTS */
#define __iomem
#define __le32			UINT32
#define dma_addr_t		UINT32
//#define	u64				UINT64
//#define	u8				UINT8
//#define u32				UINT32

struct ehci_hcd {			/* one per controller */
	int irq;
	int disabled;			/* e.g. got a UE, we're hung */	
	/* glue to PCI and HCD framework */
	struct ehci_caps __iomem *caps;
	struct ehci_regs __iomem *regs;
	struct ehci_dbg_port __iomem *debug;

	__u32			hcs_params;	/* cached register copy */

	/* async schedule support */
	struct ehci_qh		*async;
	struct ehci_qh		*reclaim;
	
	/* per root hub port */
	// unsigned long		reset_done [EHCI_MAX_ROOT_PORTS];
	
	int intrstatus;
	__u32 hc_control;		/* copy of the hc control reg */
	struct usb_device *dev[32];
	struct virt_root_hub rh;
	
	unsigned long           stamp;
	u32			command;
	const char	*slot_name;
};

enum ehci_timer_action {
	TIMER_IO_WATCHDOG,
	TIMER_IAA_WATCHDOG,
	TIMER_ASYNC_SHRINK,
	TIMER_ASYNC_OFF,
};

/*-------------------------------------------------------------------------*/

/* EHCI register interface, corresponds to EHCI Revision 0.95 specification */

/* Section 2.2 Host Controller Capability Registers */
struct ehci_caps {
	/* these fields are specified as 8 and 16 bit registers,
	 * but some hosts can't perform 8 or 16 bit PCI accesses.
	 */
	u32		hc_capbase;
#define HC_LENGTH(p)		(((p)>>00)&0x00ff)	/* bits 7:0 */
#define HC_VERSION(p)		(((p)>>16)&0xffff)	/* bits 31:16 */
	u32		hcs_params;     /* HCSPARAMS - offset 0x4 */
#define HCS_DEBUG_PORT(p)	(((p)>>20)&0xf)	/* bits 23:20, debug port? */
#define HCS_INDICATOR(p)	((p)&(1 << 16))	/* true: has port indicators */
#define HCS_N_CC(p)		(((p)>>12)&0xf)	/* bits 15:12, #companion HCs */
#define HCS_N_PCC(p)		(((p)>>8)&0xf)	/* bits 11:8, ports per CC */
#define HCS_PORTROUTED(p)	((p)&(1 << 7))	/* true: port routing */
#define HCS_PPC(p)		((p)&(1 << 4))	/* true: port power control */
#define HCS_N_PORTS(p)		(((p)>>0)&0xf)	/* bits 3:0, ports on HC */

	u32		hcc_params;      /* HCCPARAMS - offset 0x8 */
#define HCC_EXT_CAPS(p)		(((p)>>8)&0xff)	/* for pci extended caps */
#define HCC_ISOC_CACHE(p)       ((p)&(1 << 7))  /* true: can cache isoc frame */
#define HCC_ISOC_THRES(p)       (((p)>>4)&0x7)  /* bits 6:4, uframes cached */
#define HCC_CANPARK(p)		((p)&(1 << 2))  /* true: can park on async qh */
#define HCC_PGM_FRAMELISTLEN(p) ((p)&(1 << 1))  /* true: periodic_size changes*/
#define HCC_64BIT_ADDR(p)       ((p)&(1))       /* true: can use 64-bit addr */
	u8		portroute [8];	 /* nibbles for routing - offset 0xC */
} __attribute__ ((packed));


/* Section 2.3 Host Controller Operational Registers */
struct ehci_regs {

	/* USBCMD: offset 0x00 */
	u32		command;
/* 23:16 is r/w intr rate, in microframes; default "8" == 1/msec */
#define CMD_PARK	(1<<11)		/* enable "park" on async qh */
#define CMD_PARK_CNT(c)	(((c)>>8)&3)	/* how many transfers to park for */
#define CMD_LRESET	(1<<7)		/* partial reset (no ports, etc) */
#define CMD_IAAD	(1<<6)		/* "doorbell" interrupt async advance */
#define CMD_ASE		(1<<5)		/* async schedule enable */
#define CMD_PSE		(1<<4)		/* periodic schedule enable */
/* 3:2 is periodic frame list size */
#define CMD_RESET	(1<<1)		/* reset HC not bus */
#define CMD_RUN		(1<<0)		/* start/stop HC */

	/* USBSTS: offset 0x04 */
	u32		status;
#define STS_ASS		(1<<15)		/* Async Schedule Status */
#define STS_PSS		(1<<14)		/* Periodic Schedule Status */
#define STS_RECL	(1<<13)		/* Reclamation */
#define STS_HALT	(1<<12)		/* Not running (any reason) */
/* some bits reserved */
	/* these STS_* flags are also intr_enable bits (USBINTR) */
#define STS_IAA		(1<<5)		/* Interrupted on async advance */
#define STS_FATAL	(1<<4)		/* such as some PCI access errors */
#define STS_FLR		(1<<3)		/* frame list rolled over */
#define STS_PCD		(1<<2)		/* port change detect */
#define STS_ERR		(1<<1)		/* "error" completion (overflow, ...) */
#define STS_INT		(1<<0)		/* "normal" completion (short, ...) */

	/* USBINTR: offset 0x08 */
	u32		intr_enable;

	/* FRINDEX: offset 0x0C */
	u32		frame_index;	/* current microframe number */
	/* CTRLDSSEGMENT: offset 0x10 */
	u32		segment;	/* address bits 63:32 if needed */
	/* PERIODICLISTBASE: offset 0x14 */
	u32		frame_list;	/* points to periodic list */
	/* ASYNCLISTADDR: offset 0x18 */
	u32		async_next;	/* address of next async queue head */

	u32		reserved [9];

	/* CONFIGFLAG: offset 0x40 */
	u32		configured_flag;
#define FLAG_CF		(1<<0)		/* true: we'll support "high speed" */

	/* PORTSC: offset 0x44 */
	u32		port_status [0];	/* up to N_PORTS */
/* 31:23 reserved */
#define PORT_WKOC_E	(1<<22)		/* wake on overcurrent (enable) */
#define PORT_WKDISC_E	(1<<21)		/* wake on disconnect (enable) */
#define PORT_WKCONN_E	(1<<20)		/* wake on connect (enable) */
/* 19:16 for port testing */
#define PORT_LED_OFF	(0<<14)
#define PORT_LED_AMBER	(1<<14)
#define PORT_LED_GREEN	(2<<14)
#define PORT_LED_MASK	(3<<14)
#define PORT_OWNER	(1<<13)		/* true: companion hc owns this port */
#define PORT_POWER	(1<<12)		/* true: has power (see PPC) */
#define PORT_USB11(x) (((x)&(3<<10))==(1<<10))	/* USB 1.1 device */
/* 11:10 for detecting lowspeed devices (reset vs release ownership) */
/* 9 reserved */
#define PORT_RESET	(1<<8)		/* reset port */
#define PORT_SUSPEND	(1<<7)		/* suspend port */
#define PORT_RESUME	(1<<6)		/* resume it */
#define PORT_OCC	(1<<5)		/* over current change */
#define PORT_OC		(1<<4)		/* over current active */
#define PORT_PEC	(1<<3)		/* port enable change */
#define PORT_PE		(1<<2)		/* port enable */
#define PORT_CSC	(1<<1)		/* connect status change */
#define PORT_CONNECT	(1<<0)		/* device connected */
#define PORT_RWC_BITS   (PORT_CSC | PORT_PEC | PORT_OCC)
} __attribute__ ((packed));

/* Appendix C, Debug port ... intended for use with special "debug devices"
 * that can help if there's no serial console.  (nonstandard enumeration.)
 */
struct ehci_dbg_port {
	u32	control;
#define DBGP_OWNER	(1<<30)
#define DBGP_ENABLED	(1<<28)
#define DBGP_DONE	(1<<16)
#define DBGP_INUSE	(1<<10)
#define DBGP_ERRCODE(x)	(((x)>>7)&0x07)
#	define DBGP_ERR_BAD	1
#	define DBGP_ERR_SIGNAL	2
#define DBGP_ERROR	(1<<6)
#define DBGP_GO		(1<<5)
#define DBGP_OUT	(1<<4)
#define DBGP_LEN(x)	(((x)>>0)&0x0f)
	u32	pids;
#define DBGP_PID_GET(x)		(((x)>>16)&0xff)
#define DBGP_PID_SET(data,tok)	(((data)<<8)|(tok))
	u32	data03;
	u32	data47;
	u32	address;
#define DBGP_EPADDR(dev,ep)	(((dev)<<8)|(ep))
} __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

#define	QTD_NEXT(dma)	cpu_to_le32((u32)dma)

/*
 * EHCI Specification 0.95 Section 3.5
 * QTD: describe data transfer components (buffer, direction, ...)
 * See Fig 3-6 "Queue Element Transfer Descriptor Block Diagram".
 *
 * These are associated only with "QH" (Queue Head) structures,
 * used with control, bulk, and interrupt transfers.
 */
struct ehci_qtd {
	/* first part defined by EHCI spec */
	__le32			hw_next;	  /* see EHCI 3.5.1 */
	__le32			hw_alt_next;      /* see EHCI 3.5.2 */
	__le32			hw_token;         /* see EHCI 3.5.3 */
#define	QTD_TOGGLE	(1 << 31)	/* data toggle */
#define	QTD_LENGTH(tok)	(((tok)>>16) & 0x7fff)
#define	QTD_IOC		(1 << 15)	/* interrupt on complete */
#define	QTD_CERR(tok)	(((tok)>>10) & 0x3)
#define	QTD_PID(tok)	(((tok)>>8) & 0x3)
#define	QTD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#define	QTD_STS_HALT	(1 << 6)	/* halted on error */
#define	QTD_STS_DBE	(1 << 5)	/* data buffer error (in HC) */
#define	QTD_STS_BABBLE	(1 << 4)	/* device was babbling (qtd halted) */
#define	QTD_STS_XACT	(1 << 3)	/* device gave illegal response */
#define	QTD_STS_MMF	(1 << 2)	/* incomplete split transaction */
#define	QTD_STS_STS	(1 << 1)	/* split transaction state */
#define	QTD_STS_PING	(1 << 0)	/* issue PING? */
	__le32			hw_buf [5];        /* see EHCI 3.5.4 */
	__le32			hw_buf_hi [5];        /* Appendix B */

	// u8				reserved[0x20];
	/* the rest is HCD-private */
	dma_addr_t		qtd_dma;		/* qtd address */
	struct list_head qtd_list;		/* sw qtd list */
	struct urb	*urb;			/* qtd's urb */
	size_t			length;			/* length of buffer */
	// cyhuang
	struct usb_device *usb_dev;
} __attribute__ ((aligned (32)));

/* mask NakCnt+T in qh->hw_alt_next */
#define QTD_MASK __constant_cpu_to_le32 (~0x1f)

#define IS_SHORT_READ(token) (QTD_LENGTH (token) != 0 && QTD_PID (token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag from {qh,itd,sitd,fstn}->hw_next */
#define Q_NEXT_TYPE(dma) ((dma) & __constant_cpu_to_le32 (3 << 1))

/* values for that type tag */
#define Q_TYPE_ITD	__constant_cpu_to_le32 (0 << 1)
#define Q_TYPE_QH	__constant_cpu_to_le32 (1 << 1)
#define Q_TYPE_SITD	__constant_cpu_to_le32 (2 << 1)
#define Q_TYPE_FSTN	__constant_cpu_to_le32 (3 << 1)

/* next async queue entry, or pointer to interrupt/periodic QH */
#define QH_NEXT(dma)    (cpu_to_le32(((u32)dma)&~0x01f)|Q_TYPE_QH)

/* for periodic/async schedules and qtd lists, mark end of list */
#define	EHCI_LIST_END	__constant_cpu_to_le32(1) /* "null pointer" to hw */

/*
 * Entries in periodic shadow table are pointers to one of four kinds
 * of data structure.  That's dictated by the hardware; a type tag is
 * encoded in the low bits of the hardware's periodic schedule.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * For entries in the async schedule, the type tag always says "qh".
 */
union ehci_shadow {
	struct ehci_qh		*qh;		/* Q_TYPE_QH */
//	struct ehci_itd		*itd;		/* Q_TYPE_ITD */
//	struct ehci_sitd	*sitd;		/* Q_TYPE_SITD */
//	struct ehci_fstn	*fstn;		/* Q_TYPE_FSTN */
	__le32			*hw_next;	/* (all types) */
	void			*ptr;
};

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.6
 * QH: describes control/bulk/interrupt endpoints
 * See Fig 3-7 "Queue Head Structure Layout".
 *
 * These appear in both the async and (for interrupt) periodic schedules.
 */

struct ehci_qh {
	/* first part defined by EHCI spec */
	__le32			hw_next;	 /* see EHCI 3.6.1 */	
	__le32			hw_info1;        /* see EHCI 3.6.2 */
#define	QH_HEAD		0x00008000
	__le32			hw_info2;        /* see EHCI 3.6.2 */
#define	QH_SMASK	0x000000ff
#define	QH_CMASK	0x0000ff00
#define	QH_HUBADDR	0x007f0000
#define	QH_HUBPORT	0x3f800000
#define	QH_MULT		0xc0000000
	__le32			hw_current;	 /* qtd list - see EHCI 3.6.4 */

	/* qtd overlay (hardware parts of a struct ehci_qtd) */
	__le32			hw_qtd_next;
	__le32			hw_alt_next;
	__le32			hw_token;
	__le32			hw_buf [5];
	__le32			hw_buf_hi [5];

	// u8				reserved[0x200];
	/* the rest is HCD-private */
	dma_addr_t		qh_dma;		/* address of qh */
	union ehci_shadow	qh_next;	/* ptr to qh; or periodic */
	struct list_head	qtd_list;	/* sw qtd list */
	struct ehci_qtd		*dummy;
	struct ehci_qh		*reclaim;	/* next to reclaim */

	struct ehci_hcd		*ehci;
// 	struct kref		kref;
	unsigned		stamp;

	u8			qh_state;
#define	QH_STATE_LINKED		1		/* HC sees this */
#define	QH_STATE_UNLINK		2		/* HC may still see this */
#define	QH_STATE_IDLE		3		/* HC doesn't see this */
#define	QH_STATE_UNLINK_WAIT	4		/* LINKED and on reclaim q */
#define	QH_STATE_COMPLETING	5		/* don't touch token.HALT */

	/* periodic schedule info */
//	u8			usecs;		/* intr bandwidth */
//	u8			gap_uf;		/* uframes split/csplit gap */
//	u8			c_usecs;	/* ... split completion bw */
//	u16			tt_usecs;	/* tt downstream bandwidth */
//	unsigned short		period;		/* polling interval */
//	unsigned short		start;		/* where polling starts */
#define NO_FRAME ((unsigned short)~0)			/* pick new start */
// 	struct usb_device	*dev;		/* access to TT */
	struct usb_device *dev;
//} __attribute__ ((aligned (4096), packed));
} __attribute__ ((aligned (32), packed));

/*-------------------------------------------------------------------------*/




/*
 * Some EHCI controllers have a Transaction Translator built into the
 * root hub. This is a non-standard feature.  Each controller will need
 * to add code to the following inline functions, and call them as
 * needed (mostly in root hub code).
 */
#define	ehci_is_TDI(e)			(0)
#define	ehci_port_speed(ehci, portsc)	(1<<USB_PORT_FEAT_HIGHSPEED)


/*-------------------------------------------------------------------------*/

#ifndef DEBUG
#define STUB_DEBUG_FILES
#endif	/* DEBUG */

/*
 * URB support, for asynchronous request completions
 */

/*
 * urb->transfer_flags:
 */
#define URB_SHORT_NOT_OK        0x0001  /* report short reads as errors */
#define URB_ISO_ASAP            0x0002  /* iso-only, urb->start_frame ignored */
#define URB_NO_TRANSFER_DMA_MAP 0x0004  /* urb->transfer_dma valid on submit */
#define URB_NO_SETUP_DMA_MAP    0x0008  /* urb->setup_dma valid on submit */
#define URB_ASYNC_UNLINK        0x0010  /* usb_unlink_urb() returns asap */
#define URB_NO_FSBR             0x0020  /* UHCI-specific */
#define URB_ZERO_PACKET         0x0040  /* Finish bulk OUTs with short packet */
#define URB_NO_INTERRUPT        0x0080  /* HINT: no non-error interrupt needed */

/*-------------------------------------------------------------------------*/
/* urb */
// #define N_URB_QTD 48
struct urb
{
	struct usb_device *dev;
	struct ehci_qh  *qh;
	__u16 length;	/* number of qtds associated with this request */
	__u16 qtd_cnt;	/* number of qtds already serviced */
	int   state;
	unsigned long pipe;
	int actual_length;
	UINT32 setup_dma;
	UINT32 transfer_dma;
	int transfer_buffer_length;
	 unsigned int transfer_flags;
	// struct ehci_qtd *qtd[N_URB_QTD];	/* list pointer to all corresponding TDs associated with this request */
};
#define URB_DEL 1

#define NUM_QHS		(16)		/* num of preallocated endpoint descriptors */


struct ehci_device {
	struct ehci_qh 	qh[NUM_QHS];
	int qh_cnt;
} __attribute__ ((aligned (32)));


/* we need more QTDs than QHs */
#define NUM_QTD (64 * 2)// (64 * 2)

static inline void
qh_free (struct ehci_qh *qh)
{
	memset (qh, 0, sizeof *qh);	
	qh->dev = NULL;
}

#endif /* __LINUX_EHCI_HCD_H */
