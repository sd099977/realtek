/*
 * (C) Copyright 2001
 * Denis Peter, MPL AG Switzerland
 *
 * Most of this source has been derived from the Linux USB
 * project.
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
 *
 */

/*
 * How it works:
 *
 * Since this is a bootloader, the devices will not be automatic
 * (re)configured on hot/plug, but after a restart of the USB the
 * device should work.
 *
 * For each transfer (except "Interrupt") we wait for completion.
 */
#include <common.h>
#include "linux/compat.h"
#include <asm/arch/system.h>
#include <rtd_types_qc.h>



//#include <rtd_system.h>
#include <usb/usb.h>
//#include <misc.h>
//--#include <asm/addrspace.h>

#if defined(CONFIG_BOOT_TIMER)
#include <timer.h>
#endif



#undef	USB_DEBUG
//#define USB_DEBUG 1

#ifdef	USB_DEBUG
#define	USB_PRINTF(fmt,args...)	printk (fmt ,##args)
#else
#define USB_PRINTF(fmt,args...)
#endif

#define USB_BUFSIZ	512

static struct usb_device usb_dev[USB_MAX_DEVICE];
static struct usb_device *pusb_dev;

static int dev_index;
static int running;
static int asynch_allowed;


#if defined(CONFIG_USB_PATCH)
static struct devrequest setup_packet __attribute__ ((aligned (512)));
#else
static struct devrequest setup_packet;
#endif
// static struct devrequest *psetup_packet;

/**********************************************************************
 * some forward declerations...
 */
int usb_scan_devices(void);

int usb_hub_probe(struct usb_device *dev, int ifnum);
void usb_hub_reset(void);

/***********************************************************************
 * wait_ms
 */

void __inline__ wait_ms(unsigned long ms)
{
	while(ms-->0)
		udelay(1000);
}
/* --------------------------------------------------------------------------------------------------------- */


extern int ehci_lowlevel_init(void);
extern int ohci_lowlevel_init(void);

extern int ehci_lowlevel_stop(void);
extern int ohci_lowlevel_stop(void);

		
extern int ehci_submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup);
		
extern int ehci_submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len);	
		
		
extern int ohci_submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup);
		
extern int ohci_submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len);						

int USB_Host_Type=USB_EHCI_HOST;

/*
static int submit_common_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup, int interval)
{
	if (USB_Host_Type == USB_EHCI_HOST)
		return ehci_submit_common_msg(dev,pipe,buffer,transfer_len,setup,interval);
	else if (USB_Host_Type == USB_OHCI_HOST)
		return ohci_submit_common_msg(dev,pipe,buffer,transfer_len,setup,interval);
	else
		printk("%s() : Unknow USB host type = 0x%x\n",__FUNCTION__,USB_Host_Type);
		
	return 0;	 	
	
}
*/

int submit_control_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, struct devrequest *setup)
{


#if defined(CONFIG_BOOT_USB_EHCI1)	
if ((USB_Host_Type == USB_EHCI_HOST) || (USB_Host_Type == USB_EHCI_HOST1))	
		return ehci_submit_control_msg(dev,pipe,buffer,transfer_len,setup);
#elif  defined(CONFIG_BOOT_USB_EHCI)
	if (USB_Host_Type == USB_EHCI_HOST)	
		return ehci_submit_control_msg(dev,pipe,buffer,transfer_len,setup);
#endif		

#if defined(CONFIG_BOOT_USB_OHCI)
	if (USB_Host_Type == USB_OHCI_HOST)	
		return ohci_submit_control_msg(dev,pipe,buffer,transfer_len,setup);
#endif		
	
	printk("%s() : Unknow USB host type = 0x%x\n",__FUNCTION__,USB_Host_Type); 
		
	return 0;		
}

int submit_bulk_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len)
{
#if defined(CONFIG_BOOT_USB_EHCI1)	
if ((USB_Host_Type == USB_EHCI_HOST)	 || (USB_Host_Type == USB_EHCI_HOST1))	
		return ehci_submit_bulk_msg(dev,pipe,buffer,transfer_len);	
#elif  defined(CONFIG_BOOT_USB_EHCI)
	if (USB_Host_Type == USB_EHCI_HOST)	
		return ehci_submit_bulk_msg(dev,pipe,buffer,transfer_len);
#endif	

#if defined(CONFIG_BOOT_USB_OHCI)
	if (USB_Host_Type == USB_OHCI_HOST)	
		return ohci_submit_bulk_msg(dev,pipe,buffer,transfer_len);
#endif		
	
	printk("%s() : Unknow USB host type = 0x%x\n",__FUNCTION__,USB_Host_Type); 
		
	return 0;	
}	

int submit_int_msg(struct usb_device *dev, unsigned long pipe, void *buffer,
		int transfer_len, int interval)
{
	// info("submit_int_msg");
	printk("%s()\n",__FUNCTION__);
	return -1;
}	
/* --------------------------------------------------------------------------------------------------------- */

/***************************************************************************
 * Init USB Device
 */
#define USB_HOST_N_PORT 		(2)

int usb_start(int usb_host)
{
	int result;
	running=0;
	dev_index=0;
	asynch_allowed=1;
#if defined(CONFIG_BOOT_USB_EHCI)
	if(usb_host == USB_EHCI_HOST){
		USB_Host_Type=USB_EHCI_HOST;
		usb_hub_reset();
		/* init low_level USB */
		printk("EHCI0:   \n");
		result = ehci_lowlevel_init();
		/* if lowlevel init is OK, scan the bus for devices i.e. search HUBs and configure them */
		if(result==0) {
			printk("USB2.0 scanning bus for devices... ");
			running=1;
			if(usb_scan_devices()<2){
				//ehci_lowlevel_stop();
				printk("Could not find USB2.0 device by EHCI\n");
				return -1;
			}else
				return 0;
		}
		else {
			printk("Error, couldn't init Lowlevel part\n");
			return -1;
		}
	}
#endif	


#if defined(CONFIG_BOOT_USB_EHCI1)
	if(usb_host == USB_EHCI_HOST1){
		USB_Host_Type=USB_EHCI_HOST1;
		usb_hub_reset();
		/* init low_level USB */
		printk("EHCI1:   \n");
		result = ehci1_lowlevel_init();
		/* if lowlevel init is OK, scan the bus for devices i.e. search HUBs and configure them */
		if(result==0) {
			printk("USB2.0 scanning bus for devices... ");
			running=1;
			if(usb_scan_devices()<2){
				ehci1_lowlevel_stop();
				printk("Could not find USB2.0 device by EHCI-1\n");
				return -1;
			}else
				return 0;
		}
		else {
			printk("Error, couldn't init Lowlevel part\n");
			return -1;
		}
	}
#endif	



#if defined(CONFIG_BOOT_USB_OHCI)
	if(usb_host == USB_OHCI_HOST){
		USB_Host_Type=USB_OHCI_HOST;
		usb_hub_reset();
		result = ohci_lowlevel_init();
				
		if(result==0) {
			printk("USB1.1 scanning bus for devices... ");
			running=1;
			if(usb_scan_devices()<2){
				printk("Could not find USB1.0 device by OHCI\n");
				ohci_lowlevel_stop();
				return -1;
			}else
				return 0;
		}
		else {
			printk("Error, couldn't init Lowlevel part\n");
			return -1;
		}
	}
#endif // CONFIG_BOOT_USB_OHCI
	printk("Error, Unknow usb host type\n");
	return -1;
}

/******************************************************************************
 * Stop USB this stops the LowLevel Part and deregisters USB devices.
 */
int usb_stop(int host_type)
{
	asynch_allowed=1;
	usb_hub_reset();	
#if defined(CONFIG_BOOT_USB_EHCI)	
	if (host_type == USB_EHCI_HOST) {
		printk("EHCI stopping ..\n");
		return ehci_lowlevel_stop();
	}	
#endif	
	
#if defined(CONFIG_BOOT_USB_OHCI)	
	if (host_type == USB_OHCI_HOST) {
		printk("OHCI stopping ..\n");
		return ohci_lowlevel_stop();
	}	
#endif	

	printk("%s() : Unknow USB host type = 0x%x\n",__FUNCTION__,USB_Host_Type); 
	
	return 0;
}

/*
 * disables the asynch behaviour of the control message. This is used for data
 * transfers that uses the exclusiv access to the control and bulk messages.
 */
void usb_disable_asynch(int disable)
{
	asynch_allowed=!disable;
}


/*-------------------------------------------------------------------
 * Message wrappers.
 *
 */

/*
 * submits an Interrupt Message
 */
int usb_submit_int_msg(struct usb_device *dev, unsigned long pipe,
			void *buffer,int transfer_len, int interval)
{
#ifdef ENABLE_KSEG1ADDR
	if (buffer)
		buffer = (void *) KSEG1ADDR(buffer);
#endif /* ENABLE_KSEG1ADDR */
		
	return submit_int_msg(dev,pipe,buffer,transfer_len,interval);
}

/*
 * submits a control message and waits for comletion (at least timeout * 1ms)
 * If timeout is 0, we don't wait for completion (used as example to set and
 * clear keyboards LEDs). For data transfers, (storage transfers) we don't
 * allow control messages with 0 timeout, by previousely resetting the flag
 * asynch_allowed (usb_disable_asynch(1)).
 * returns the transfered length if OK or -1 if error. The transfered length
 * and the current status are stored in the dev->act_len and dev->status.
 */
int usb_control_msg(struct usb_device *dev, unsigned int pipe,
			unsigned char request, unsigned char requesttype,
			unsigned short value, unsigned short index,
			void *data, unsigned short size, int timeout)
{
#ifdef ENABLE_KSEG1ADDR
	struct devrequest *psetup_packet = (struct devrequest *) KSEG1ADDR(&setup_packet); 
#else /* ENABLE_KSEG1ADDR */
	struct devrequest *psetup_packet = (struct devrequest *) &setup_packet; 
#endif /* ENABLE_KSEG1ADDR */
	if((timeout==0)&&(!asynch_allowed)) /* request for a asynch control pipe is not allowed */
		return -1;
	/* set setup command */
	psetup_packet->requesttype = requesttype;
	psetup_packet->request = request;
	psetup_packet->value = swap_16(value);
	psetup_packet->index = swap_16(index);
	psetup_packet->length = swap_16(size);
 	USB_PRINTF("usb_control_msg: request: 0x%x, requesttype: 0x%x\nvalue 0x%x index 0x%x length 0x%x\n",
		request,requesttype,value,index,size);
	dev->status=USB_ST_NOT_PROC; /*not yet processed */
    
#ifdef ENABLE_KSEG1ADDR
	if (data)
		data = (void *) KSEG1ADDR(data);
#endif /* ENABLE_KSEG1ADDR */
 
	submit_control_msg(dev,pipe,data,size,psetup_packet);
	if(timeout==0) {
		return (int)size;
	}
	while(timeout--) {
		if(!((volatile unsigned long)dev->status & USB_ST_NOT_PROC))
			break;
		wait_ms(1);
	}
	if(dev->status==0)
		return dev->act_len;
	else {
		return -1;
	}
}

/*-------------------------------------------------------------------
 * submits bulk message, and waits for completion. returns 0 if Ok or
 * -1 if Error.
 * synchronous behavior
 */
int usb_bulk_msg(struct usb_device *dev, unsigned int pipe,
			void *data, int len, int *actual_length, int timeout)
{
	// printk("%s : data = 0x%x\n",__FUNCTION__,data);
	if (len < 0)
		return -1;
	dev->status=USB_ST_NOT_PROC; /*not yet processed */

#ifdef ENABLE_KSEG1ADDR
	if (data)
		data = (void *) KSEG1ADDR(data);
#endif /* ENABLE_KSEG1ADDR */		
	
	submit_bulk_msg(dev,pipe,data,len);
	while(timeout--) {
		if(!((volatile unsigned long)dev->status & USB_ST_NOT_PROC))
			break;
		wait_ms(1);
	}
	
	*actual_length=dev->act_len;
	
	if(dev->status==0)
		return 0;
	else
		return -1;
}


/*-------------------------------------------------------------------
 * Max Packet stuff
 */

/*
 * returns the max packet size, depending on the pipe direction and
 * the configurations values
 */
int usb_maxpacket(struct usb_device *dev,unsigned long pipe)
{
	if((pipe & USB_DIR_IN)==0) /* direction is out -> use emaxpacket out */
		return(dev->epmaxpacketout[((pipe>>15) & 0xf)]);
	else
		return(dev->epmaxpacketin[((pipe>>15) & 0xf)]);
}

/*
 * set the max packed value of all endpoints in the given configuration
 */
int usb_set_maxpacket(struct usb_device *dev)
{
	int i,ii,b;
	struct usb_endpoint_descriptor *ep;

	for(i=0; i<dev->config.bNumInterfaces;i++) {
		for(ii=0; ii<dev->config.if_desc[i].bNumEndpoints; ii++) {
			ep=&dev->config.if_desc[i].ep_desc[ii];
			b=ep->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;

			if((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)==USB_ENDPOINT_XFER_CONTROL) {	/* Control => bidirectional */
				dev->epmaxpacketout[b] = ep->wMaxPacketSize;
				dev->epmaxpacketin [b] = ep->wMaxPacketSize;
				USB_PRINTF("##Control EP epmaxpacketout/in[%d] = %d\n",b,dev->epmaxpacketin[b]);
			}
			else {
				if ((ep->bEndpointAddress & 0x80)==0) { /* OUT Endpoint */
					if(ep->wMaxPacketSize > dev->epmaxpacketout[b]) {
						dev->epmaxpacketout[b] = ep->wMaxPacketSize;
						USB_PRINTF("##EP epmaxpacketout[%d] = %d\n",b,dev->epmaxpacketout[b]);
					}
				}
				else  { /* IN Endpoint */
					if(ep->wMaxPacketSize > dev->epmaxpacketin[b]) {
						dev->epmaxpacketin[b] = ep->wMaxPacketSize;
						USB_PRINTF("##EP epmaxpacketin[%d] = %d\n",b,dev->epmaxpacketin[b]);
					}
				} /* if out */
			} /* if control */
		} /* for each endpoint */
	}
	return 0;
}

/*******************************************************************************
 * Parse the config, located in buffer, and fills the dev->config structure.
 * Note that all little/big endian swapping are done automatically.
 */
int usb_parse_config(struct usb_device *dev, unsigned char *buffer, int cfgno)
{
	struct usb_descriptor_header *head;
	int index,ifno,epno;
	ifno=-1;
	epno=-1;

	dev->configno=cfgno;
	head =(struct usb_descriptor_header *)&buffer[0];
	if(head->bDescriptorType!=USB_DT_CONFIG) {
		printk(" ERROR: NOT USB_CONFIG_DESC %x\n",head->bDescriptorType);
		return -1;
	}
	memcpy(&dev->config,buffer,buffer[0]);
	dev->config.wTotalLength=swap_16(dev->config.wTotalLength);
	dev->config.no_of_if=0;

	index=dev->config.bLength;
	/* Ok the first entry must be a configuration entry, now process the others */
	head=(struct usb_descriptor_header *)&buffer[index];
	while(index+1 < dev->config.wTotalLength) {
		switch(head->bDescriptorType) {
			case USB_DT_INTERFACE:
				ifno=dev->config.no_of_if;
				dev->config.no_of_if++; /* found an interface desc, increase numbers */
				memcpy(&dev->config.if_desc[ifno],&buffer[index],buffer[index]); /* copy new desc */
				dev->config.if_desc[ifno].no_of_ep=0;
				USB_PRINTF("interface..........\n");
				break;
			case USB_DT_ENDPOINT:
				epno=dev->config.if_desc[ifno].no_of_ep;
				dev->config.if_desc[ifno].no_of_ep++; /* found an endpoint */
				memcpy(&dev->config.if_desc[ifno].ep_desc[epno],&buffer[index],buffer[index]);
				
				// cyhuang : Debug WORD alignment.
				// printk("dev->config.if_desc[ifno].ep_desc[epno].wMaxPacketSize = 0x%x\n", &dev->config.if_desc[ifno].ep_desc[epno].wMaxPacketSize);
				
				dev->config.if_desc[ifno].ep_desc[epno].wMaxPacketSize
					=swap_16(dev->config.if_desc[ifno].ep_desc[epno].wMaxPacketSize);
				USB_PRINTF("if %d, ep %d\n",ifno,epno);
				break;
			default:
				if(head->bLength==0)
					return 1;
				USB_PRINTF("unknown Description Type : %x\n",head->bDescriptorType);
				{
					int i;
					unsigned char *ch;
					ch=(unsigned char *)head;
					for(i=0;i<head->bLength; i++)
						USB_PRINTF("0x%x ",*ch++);
					USB_PRINTF("\n\n\n");
				}
				break;
		}
		index+=head->bLength;
		head=(struct usb_descriptor_header *)&buffer[index];
	}
	return 1;
}

/***********************************************************************
 * Clears an endpoint
 * endp: endpoint number in bits 0-3;
 * direction flag in bit 7 (1 = IN, 0 = OUT)
 */
int usb_clear_halt(struct usb_device *dev, int pipe)
{
	int result;
	
#if defined(CONFIG_USB_PATCH)	
	static unsigned short status __attribute__ ((aligned (512)));
#else
	unsigned short status;
#endif
	
	int endp=usb_pipeendpoint(pipe)|(usb_pipein(pipe)<<7);

	result = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RECIP_ENDPOINT, 0, endp, NULL, 0, USB_CNTL_TIMEOUT * 3);

	/* don't clear if failed */
	if (result < 0)
		return result;
	result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_STATUS, USB_DIR_IN | USB_RECIP_ENDPOINT, 0, endp,
		&status, sizeof(status), USB_CNTL_TIMEOUT * 3);
	if (result < 0)
		return result;
	USB_PRINTF("usb_clear_halt: status 0x%x\n",status);
	if (status & 1)
		return -1;		/* still halted */
	usb_endpoint_running(dev, usb_pipeendpoint(pipe), usb_pipeout(pipe));
	/* toggle is reset on clear */
	usb_settoggle(dev, usb_pipeendpoint(pipe), usb_pipeout(pipe), 0);
	return 0;
}


/**********************************************************************
 * get_descriptor type
 */
int usb_get_descriptor(struct usb_device *dev, unsigned char type, unsigned char index, void *buf, int size)
{
	int res;
 	res = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
			(type << 8) + index, 0,
			buf, size, USB_CNTL_TIMEOUT);
	return res;
}

/**********************************************************************
 * gets configuration cfgno and store it in the buffer
 */
int usb_get_configuration_no(struct usb_device *dev,unsigned char *buffer,int cfgno)
{
 	int result;
	unsigned int tmp;
	struct usb_config_descriptor *config;


	config=(struct usb_config_descriptor *)&buffer[0];
	result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno, buffer, 8);
	if (result < 8) {
		if (result < 0)
			printk("unable to get descriptor, error 0x%lux\n",dev->status);
		else
			printk("config descriptor too short (expected %i, got %i)\n",8,result);
		return -1;
	}
	tmp=swap_16(config->wTotalLength);

	if (tmp > USB_BUFSIZ) {
		USB_PRINTF("usb_get_configuration_no: failed to get descriptor - too long: %d\n",
			tmp);
		return -1;
	}

	result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno, buffer, tmp);
	USB_PRINTF("get_conf_no %d Result %d, wLength %d\n",cfgno,result,tmp);
	return result;
}

/********************************************************************
 * set address of a device to the value in dev->devnum.
 * This can only be done by addressing the device via the default address (0)
 */
int usb_set_address(struct usb_device *dev)
{
	int res;

	USB_PRINTF("set address %d\n",dev->devnum);
	res=usb_control_msg(dev, usb_snddefctrl(dev),
		USB_REQ_SET_ADDRESS, 0,
		(dev->devnum),0,
		NULL,0, USB_CNTL_TIMEOUT);

	return res;
}

/********************************************************************
 * set interface number to interface
 */
int usb_set_interface(struct usb_device *dev, int interface, int alternate)
{
	struct usb_interface_descriptor *if_face = NULL;
	int ret, i;

	for (i=0; i<dev->config.bNumInterfaces; i++) {
		if (dev->config.if_desc[i].bInterfaceNumber == interface) {
			if_face = &dev->config.if_desc[i];
			break;
		}
	}
	if (!if_face) {
		printk("selecting invalid interface %d", interface);
		return -1;
	}

	if ((ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
	    USB_REQ_SET_INTERFACE, USB_RECIP_INTERFACE, alternate,
	    interface, NULL, 0, USB_CNTL_TIMEOUT * 5)) < 0)
		return ret;

	if_face->act_altsetting = (unsigned char)alternate;
	usb_set_maxpacket(dev);
	return 0;
}

/********************************************************************
 * set configuration number to configuration
 */
int usb_set_configuration(struct usb_device *dev, int configuration)
{
	int res;
	USB_PRINTF("set configuration %d\n",configuration);
	/* set setup command */
	res=usb_control_msg(dev, usb_sndctrlpipe(dev,0),
		USB_REQ_SET_CONFIGURATION, 0,
		configuration,0,
		NULL,0, USB_CNTL_TIMEOUT);
	if(res==0) {
		dev->toggle[0] = 0;
		dev->toggle[1] = 0;
		return 0;
	}
	else
		return -1;
}

/********************************************************************
 * set protocol to protocol
 */
int usb_set_protocol(struct usb_device *dev, int ifnum, int protocol)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_SET_PROTOCOL, USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		protocol, ifnum, NULL, 0, USB_CNTL_TIMEOUT);
}

/********************************************************************
 * set idle
 */
int usb_set_idle(struct usb_device *dev, int ifnum, int duration, int report_id)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_SET_IDLE, USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		(duration << 8) | report_id, ifnum, NULL, 0, USB_CNTL_TIMEOUT);
}

/********************************************************************
 * get report
 */
int usb_get_report(struct usb_device *dev, int ifnum, unsigned char type, unsigned char id, void *buf, int size)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_REPORT, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		(type << 8) + id, ifnum, buf, size, USB_CNTL_TIMEOUT);
}

/********************************************************************
 * get class descriptor
 */
int usb_get_class_descriptor(struct usb_device *dev, int ifnum,
		unsigned char type, unsigned char id, void *buf, int size)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_DESCRIPTOR, USB_RECIP_INTERFACE | USB_DIR_IN,
		(type << 8) + id, ifnum, buf, size, USB_CNTL_TIMEOUT);
}

/********************************************************************
 * get string index in buffer
 */
int usb_get_string(struct usb_device *dev, unsigned short langid, unsigned char index, void *buf, int size)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
		(USB_DT_STRING << 8) + index, langid, buf, size, USB_CNTL_TIMEOUT);
}

/********************************************************************
 * usb_string:
 * Get string index and translate it to ascii.
 * returns string length (> 0) or error (< 0)
 */
int usb_string(struct usb_device *dev, int index, char *buf, size_t size)
{
#if defined(CONFIG_USB_PATCH)	
	static unsigned char mybuf[USB_BUFSIZ] __attribute__ ((aligned (1024)));
	static unsigned char *tbuf;
#else
	unsigned char mybuf[USB_BUFSIZ];
	unsigned char *tbuf;
#endif	
	int err;
	unsigned int u, idx;

	if (size <= 0 || !buf || !index)
		return -1;
	buf[0] = 0;

#ifdef ENABLE_KSEG1ADDR
	tbuf= (unsigned char *) KSEG1ADDR(&mybuf[0]);
#else /* ENABLE_KSEG1ADDR */
	tbuf= (unsigned char *) mybuf;
#endif /* ENABLE_KSEG1ADDR */

	/* get langid for strings if it's not yet known */
	if (!dev->have_langid) {
		err = usb_get_string(dev, 0, 0, tbuf, 4);
		if (err < 0) {
			USB_PRINTF("error getting string descriptor 0 (error=%x)\n",dev->status);
			return -1;
		} else if (tbuf[0] < 4) {
			USB_PRINTF("string descriptor 0 too short\n");
			return -1;
		} else {
			dev->have_langid = -1;
			dev->string_langid = tbuf[2] | (tbuf[3]<< 8);
				/* always use the first langid listed */
			USB_PRINTF("USB device number %d default language ID 0x%x\n",
				dev->devnum, dev->string_langid);
		}
	}
	/* Just ask for a maximum length string and then take the length
	 * that was returned. */
	err = usb_get_string(dev, dev->string_langid, index, tbuf, 4);
	if (err < 0)
		return err;
	u=tbuf[0];
	USB_PRINTF("Strn Len %d, index %d\n",u,index);

	if (u > USB_BUFSIZ) {
		USB_PRINTF("usb_string: failed to get string - too long: %d\n", u);
		return -1;
	}

	err = usb_get_string(dev, dev->string_langid, index, tbuf, u);
	if (err < 0)
		return err;
	size--;		/* leave room for trailing NULL char in output buffer */
	for (idx = 0, u = 2; u < err; u += 2) {
		if (idx >= size)
			break;
		if (tbuf[u+1])			/* high byte */
			buf[idx++] = '?';  /* non-ASCII character */
		else
			buf[idx++] = tbuf[u];
	}
	buf[idx] = 0;
	err = idx;
	return err;
}


/********************************************************************
 * USB device handling:
 * the USB device are static allocated [USB_MAX_DEVICE].
 */


/* returns a pointer to the device with the index [index].
 * if the device is not assigned (dev->devnum==-1) returns NULL
 */
struct usb_device * usb_get_dev_index(int index)
{
	if(pusb_dev[index].devnum==-1)
		return NULL;
	else
		return &pusb_dev[index];
}


/* returns a pointer of a new device structure or NULL, if
 * no device struct is available
 */
struct usb_device * usb_alloc_new_device(void)
{
	int i;
	USB_PRINTF("New Device %d\n",dev_index);
	if(dev_index==USB_MAX_DEVICE) {
		printk("ERROR, too many USB Devices, max=%d\n",USB_MAX_DEVICE);
		return NULL;
	}
	pusb_dev[dev_index].devnum=dev_index+1; /* default Address is 0, real addresses start with 1 */
	pusb_dev[dev_index].maxchild=0;
	for(i=0;i<USB_MAXCHILDREN;i++)
		pusb_dev[dev_index].children[i]=NULL;
	pusb_dev[dev_index].parent=NULL;
	dev_index++;
	return &pusb_dev[dev_index-1];
}


/*
 * By the time we get here, the device has gotten a new device ID
 * and is in the default state. We need to identify the thing and
 * get the ball rolling..
 *
 * Returns 0 for success, != 0 for error.
 */
int usb_new_device(struct usb_device *dev)
{
	
	int addr, err;
	int tmp;
	
#if defined(CONFIG_USB_PATCH)
	static unsigned char tmpbuf[USB_BUFSIZ] __attribute__ ((aligned (512)));
#else
	unsigned char tmpbuf[USB_BUFSIZ];
#endif	

	dev->descriptor.bMaxPacketSize0 = 8;  /* Start off at 8 bytes  */
	dev->maxpacketsize = 0;		/* Default to 8 byte max packet size */
	dev->epmaxpacketin [0] = 8;
	dev->epmaxpacketout[0] = 8;

	/* We still haven't set the Address yet */
	addr = dev->devnum;
	dev->devnum = 0;
	
	err = usb_get_descriptor(dev, USB_DT_DEVICE, 0, &dev->descriptor, 8);

	if (err < 8) {
		printk("\n      USB device not responding, giving up (status=0x%lux)\n",dev->status);
		return 1;
	}
	dev->epmaxpacketin [0] = dev->descriptor.bMaxPacketSize0;
	dev->epmaxpacketout[0] = dev->descriptor.bMaxPacketSize0;	
	
	switch (dev->descriptor.bMaxPacketSize0) {
		case 8: dev->maxpacketsize = 0; break;
		case 16: dev->maxpacketsize = 1; break;
		case 32: dev->maxpacketsize = 2; break;
		case 64: dev->maxpacketsize = 3; break;
	}
	dev->devnum = addr;

	err = usb_set_address(dev); /* set address */
	if (err < 0) {
		printk("\n      USB device not accepting new address (error=0x%lux)\n", dev->status);
		return 1;
	}

	wait_ms(10);	/* Let the SET_ADDRESS settle */

	tmp = sizeof(dev->descriptor);


	err = usb_get_descriptor(dev, USB_DT_DEVICE, 0, &dev->descriptor, sizeof(struct usb_device_descriptor));
	if (err < tmp) {
		if (err < 0)
			printk("unable to get device descriptor (error=%d)\n",err);
		else
			printk("USB device descriptor short read (expected %d, got %d)\n",tmp,err);
		return 1;
	}
	/* correct le values */
	dev->descriptor.bcdUSB=swap_16(dev->descriptor.bcdUSB);
	dev->descriptor.idVendor=swap_16(dev->descriptor.idVendor);
	dev->descriptor.idProduct=swap_16(dev->descriptor.idProduct);
	dev->descriptor.bcdDevice=swap_16(dev->descriptor.bcdDevice);
	/* only support for one config for now */
	usb_get_configuration_no(dev,&tmpbuf[0],0);
	usb_parse_config(dev,&tmpbuf[0],0);
	usb_set_maxpacket(dev);
	/* we set the default configuration here */
	if (usb_set_configuration(dev, dev->config.bConfigurationValue)) {
		printk("failed to set default configuration len %d, status 0x%lux\n",dev->act_len,dev->status);
		return -1;
	}
	USB_PRINTF("new device strings: idVendor=0x%x, idProduct=0x%x, bcdDevice=0x%x\n",
		dev->descriptor.idVendor, dev->descriptor.idProduct, dev->descriptor.bcdDevice);
		
	USB_PRINTF("new device strings: Mfr=%d, Product=%d, SerialNumber=%d\n",
		dev->descriptor.iManufacturer, dev->descriptor.iProduct, dev->descriptor.iSerialNumber);
	memset(dev->mf, 0, sizeof(dev->mf));
	memset(dev->prod, 0, sizeof(dev->prod));
	memset(dev->serial, 0, sizeof(dev->serial));
	if (dev->descriptor.iManufacturer)
		usb_string(dev, dev->descriptor.iManufacturer, dev->mf, sizeof(dev->mf));
	if (dev->descriptor.iProduct)
		usb_string(dev, dev->descriptor.iProduct, dev->prod, sizeof(dev->prod));
	if (dev->descriptor.iSerialNumber)
		usb_string(dev, dev->descriptor.iSerialNumber, dev->serial, sizeof(dev->serial));
	USB_PRINTF("Manufacturer %s\n", dev->mf);
	USB_PRINTF("Product      %s\n", dev->prod);
	USB_PRINTF("SerialNumber %s\n", dev->serial);

	usb_hub_probe(dev,0);

	return 0;
}

/* build device Tree  */
int usb_scan_devices(void)
{
	int i;
	struct usb_device *dev;

#ifdef ENABLE_KSEG1ADDR
	pusb_dev = (struct usb_device *) KSEG1ADDR(&usb_dev[0]);
#else /* ENABLE_KSEG1ADDR */
	pusb_dev = (struct usb_device *) usb_dev;
#endif /* ENABLE_KSEG1ADDR */

	/* first make all devices unknown */
	for(i=0;i<USB_MAX_DEVICE;i++) {
		memset(&pusb_dev[i],0,sizeof(struct usb_device));
		pusb_dev[i].devnum=-1;
	}
	dev_index=0;
	/* device 0 is always present (root hub, so let it analyze) */
	dev=usb_alloc_new_device();
	usb_new_device(dev);
	printk("%d USB Devices found\n",dev_index);
	return dev_index;
	/* insert "driver" if possible */
}


/****************************************************************************
 * HUB "Driver"
 * Probes device for being a hub and configurate it
 */

#undef	USB_HUB_DEBUG
//#define	USB_HUB_DEBUG 1

#ifdef	USB_HUB_DEBUG
#define	USB_HUB_PRINTF(fmt,args...)	printk (fmt ,##args)
#else
#define USB_HUB_PRINTF(fmt,args...)
#endif


static struct usb_hub_device hub_dev[USB_MAX_HUB];
static int usb_hub_index;


int usb_get_hub_descriptor(struct usb_device *dev, void *data, int size)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_DESCRIPTOR, USB_DIR_IN | USB_RT_HUB,
		USB_DT_HUB << 8, 0, data, size, USB_CNTL_TIMEOUT);
}

int usb_clear_hub_feature(struct usb_device *dev, int feature)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RT_HUB, feature, 0, NULL, 0, USB_CNTL_TIMEOUT);
}

int usb_clear_port_feature(struct usb_device *dev, int port, int feature)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RT_PORT, feature, port, NULL, 0, USB_CNTL_TIMEOUT);
}

int usb_set_port_feature(struct usb_device *dev, int port, int feature)
{
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		USB_REQ_SET_FEATURE, USB_RT_PORT, feature, port, NULL, 0, USB_CNTL_TIMEOUT);
}

int usb_get_hub_status(struct usb_device *dev, void *data)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			USB_REQ_GET_STATUS, USB_DIR_IN | USB_RT_HUB, 0, 0,
			data, sizeof(struct usb_hub_status), USB_CNTL_TIMEOUT);
}

int usb_get_port_status(struct usb_device *dev, int port, void *data)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			USB_REQ_GET_STATUS, USB_DIR_IN | USB_RT_PORT, 0, port,
			data, sizeof(struct usb_hub_status), USB_CNTL_TIMEOUT);
}


static void usb_hub_power_on(struct usb_hub_device *hub)
{
	int i;
	struct usb_device *dev;

	dev=hub->pusb_dev;
	/* Enable power to the ports */
	USB_HUB_PRINTF("enabling power on all ports\n");
	for (i = 0; i < dev->maxchild; i++) {
		usb_set_port_feature(dev, i + 1, USB_PORT_FEAT_POWER);
		USB_HUB_PRINTF("port %d returns 0x%x\n",i+1,dev->status);
		#ifdef usb_speed_up
		wait_ms(5);
		#else
		wait_ms(hub->desc.bPwrOn2PwrGood * 2);  //hub->desc.bPwrOn2PwrGood  = 10
		#endif
		
	}
}

void usb_hub_reset(void)
{
	usb_hub_index=0;
}

struct usb_hub_device *usb_hub_allocate(void)
{
	if(usb_hub_index<USB_MAX_HUB) {
		return &hub_dev[usb_hub_index++];
	}
	printk("ERROR: USB_MAX_HUB (%d) reached\n",USB_MAX_HUB);
	return NULL;
}

#define MAX_TRIES 5

void usb_hub_port_connect_change(struct usb_device *dev, int port)
{
	struct usb_device *usb;
	struct usb_port_status portsts;
	unsigned short portstatus, portchange;
	int tries;

	/* Check status */
	if (usb_get_port_status(dev, port + 1, &portsts)<0) {
		USB_HUB_PRINTF("get_port_status failed\n");
		return;
	}	
	portstatus = swap_16(portsts.wPortStatus);
	portchange = swap_16(portsts.wPortChange);
	
	// cyhuang 
	if (portstatus&(1<<USB_PORT_FEAT_HIGHSPEED)) {
		dev->speed = USB_SPEED_HIGH;		
		USB_HUB_PRINTF("portstatus %x, change %x, %s\n", portstatus, portchange,
			 "High Speed");
	}
	else 
		USB_HUB_PRINTF("portstatus %x, change %x, %s\n", portstatus, portchange,
			portstatus&(1<<USB_PORT_FEAT_LOWSPEED) ? "Low Speed" : "Full Speed");

	

	/* Clear the connection change status */
	usb_clear_port_feature(dev, port + 1, USB_PORT_FEAT_C_CONNECTION);

	/* Disconnect any existing devices under this port */
	if (((!(portstatus & USB_PORT_STAT_CONNECTION)) &&
	     (!(portstatus & USB_PORT_STAT_ENABLE)))|| (dev->children[port])) {
		USB_HUB_PRINTF("usb_disconnect(&hub->children[port]);\n");
		/* Return now if nothing is connected */
		if (!(portstatus & USB_PORT_STAT_CONNECTION))
			return;
	}

	#ifdef usb_speed_up
	wait_ms(5);	
	#else
	wait_ms(200);
	#endif

	/* Reset the port */

	for(tries=0;tries<MAX_TRIES;tries++) {

		usb_set_port_feature(dev, port + 1, USB_PORT_FEAT_RESET);
		#if 0 //def usb_speed_up (some usb device can reduce delay time )
		wait_ms(50);	
		#else
		wait_ms(200);
		#endif
		if (usb_get_port_status(dev, port + 1, &portsts)<0) {
			USB_HUB_PRINTF("get_port_status failed status 0x%x\n",dev->status);
			return;
		}
		portstatus = swap_16(portsts.wPortStatus);
		portchange = swap_16(portsts.wPortChange);
		
		// cyhuang 
		if (portstatus&(1<<USB_PORT_FEAT_HIGHSPEED)) {
			dev->speed = USB_SPEED_HIGH;
			USB_HUB_PRINTF("portstatus %x, change %x, %s\n", portstatus, portchange,
			 	"High Speed");
		}
		else		
			USB_HUB_PRINTF("portstatus %x, change %x, %s\n", portstatus ,portchange,
				portstatus&(1<<USB_PORT_FEAT_LOWSPEED) ? "Low Speed" : "Full Speed");
				
		USB_HUB_PRINTF("STAT_C_CONNECTION = %d STAT_CONNECTION = %d  USB_PORT_STAT_ENABLE %d\n",
			(portchange & USB_PORT_STAT_C_CONNECTION) ? 1 : 0,
			(portstatus & USB_PORT_STAT_CONNECTION) ? 1 : 0,
			(portstatus & USB_PORT_STAT_ENABLE) ? 1 : 0);
		if ((portchange & USB_PORT_STAT_C_CONNECTION) ||
		    !(portstatus & USB_PORT_STAT_CONNECTION))
			return;

		if (portstatus & USB_PORT_STAT_ENABLE)
		{
			#ifdef usb_speed_up
			wait_ms(5);	
			#else
			wait_ms(200);
			#endif
			break;

		}

		#ifdef usb_speed_up
		wait_ms(5);	
		#else
		wait_ms(200);
		#endif
	}

	if (tries==MAX_TRIES) {
		USB_HUB_PRINTF("Cannot enable port %i after %i retries, disabling port.\n", port+1, MAX_TRIES);
		USB_HUB_PRINTF("Maybe the USB cable is bad?\n");
		return;
	}

	usb_clear_port_feature(dev, port + 1, USB_PORT_FEAT_C_RESET);
	#ifdef usb_speed_up
	wait_ms(5);	
	#else
	wait_ms(200);
	#endif

	/* Allocate a new device struct for it */
	usb=usb_alloc_new_device();
	usb->slow = (portstatus & USB_PORT_STAT_LOW_SPEED) ? 1 : 0;

	dev->children[port] = usb;
	usb->parent=dev;	
	
	// while(1);
	
	/* Run it through the hoops (find a driver, etc) */
	if (usb_new_device(usb)) {
		/* Woops, disable the port */
		USB_HUB_PRINTF("hub: disabling port %d\n", port + 1);
		usb_clear_port_feature(dev, port + 1, USB_PORT_FEAT_ENABLE);
	}
}


int usb_hub_configure(struct usb_device *dev)
{
#if defined(CONFIG_USB_PATCH)		
	static unsigned char buffer[USB_BUFSIZ] __attribute__ ((aligned (512)));
#else
	unsigned char buffer[USB_BUFSIZ];
#endif	
	unsigned char *bitmap;
	struct usb_hub_descriptor *descriptor;
	struct usb_hub_status *hubsts;
	int i;
	struct usb_hub_device *hub;

	/* "allocate" Hub device */
	hub=usb_hub_allocate();
	if(hub==NULL)
		return -1;
	hub->pusb_dev=dev;
	/* Get the the hub descriptor */
	if (usb_get_hub_descriptor(dev, buffer, 4) < 0) {
		USB_HUB_PRINTF("usb_hub_configure: failed to get hub descriptor, giving up 0x%x\n",dev->status);
		return -1;
	}
	descriptor = (struct usb_hub_descriptor *)buffer;

	if (descriptor->bLength > USB_BUFSIZ) {
		USB_HUB_PRINTF("usb_hub_configure: failed to get hub descriptor - too long: %d\n",
			descriptor->bLength);
		return -1;
	}

	if (usb_get_hub_descriptor(dev, buffer, descriptor->bLength) < 0) {
		USB_HUB_PRINTF("usb_hub_configure: failed to get hub descriptor 2nd giving up 0x%x\n",dev->status);
		return -1;
	}

	memcpy((unsigned char *)&hub->desc,buffer,descriptor->bLength);
	/* adjust 16bit values */
	hub->desc.wHubCharacteristics=swap_16(descriptor->wHubCharacteristics);
	/* set the bitmap */
	bitmap=(unsigned char *)&hub->desc.DeviceRemovable[0];
	memset(bitmap,0xff,(USB_MAXCHILDREN+1+7)/8); /* devices not removable by default */
	bitmap=(unsigned char *)&hub->desc.PortPowerCtrlMask[0];
	memset(bitmap,0xff,(USB_MAXCHILDREN+1+7)/8); /* PowerMask = 1B */
	for(i=0;i<((hub->desc.bNbrPorts + 1 + 7)/8);i++) {
		hub->desc.DeviceRemovable[i]=descriptor->DeviceRemovable[i];
	}
	for(i=0;i<((hub->desc.bNbrPorts + 1 + 7)/8);i++) {
		hub->desc.DeviceRemovable[i]=descriptor->PortPowerCtrlMask[i];
	}
	dev->maxchild = descriptor->bNbrPorts;
	USB_HUB_PRINTF("%d ports detected\n", dev->maxchild);

	switch (hub->desc.wHubCharacteristics & HUB_CHAR_LPSM) {
		case 0x00:
			USB_HUB_PRINTF("ganged power switching\n");
			break;
		case 0x01:
			USB_HUB_PRINTF("individual port power switching\n");
			break;
		case 0x02:
		case 0x03:
			USB_HUB_PRINTF("unknown reserved power switching mode\n");
			break;
	}

	if (hub->desc.wHubCharacteristics & HUB_CHAR_COMPOUND)
		USB_HUB_PRINTF("part of a compound device\n");
	else
		USB_HUB_PRINTF("standalone hub\n");

	switch (hub->desc.wHubCharacteristics & HUB_CHAR_OCPM) {
		case 0x00:
			USB_HUB_PRINTF("global over-current protection\n");
			break;
		case 0x08:
			USB_HUB_PRINTF("individual port over-current protection\n");
			break;
		case 0x10:
		case 0x18:
			USB_HUB_PRINTF("no over-current protection\n");
      break;
	}
	USB_HUB_PRINTF("power on to power good time: %dms\n", descriptor->bPwrOn2PwrGood * 2);
	USB_HUB_PRINTF("hub controller current requirement: %dmA\n", descriptor->bHubContrCurrent);
	
	for (i = 0; i < dev->maxchild; i++)
		USB_HUB_PRINTF("port %d is%s removable\n", i + 1,
			hub->desc.DeviceRemovable[(i + 1)/8] & (1 << ((i + 1)%8)) ? " not" : "");
	if (sizeof(struct usb_hub_status) > USB_BUFSIZ) {
		USB_HUB_PRINTF("usb_hub_configure: failed to get Status - too long: %d\n",
			descriptor->bLength);
		return -1;
	}

	if (usb_get_hub_status(dev, buffer) < 0) {
		USB_HUB_PRINTF("usb_hub_configure: failed to get Status 0x%x\n",dev->status);
		return -1;
	}

	hubsts = (struct usb_hub_status *)buffer;
	USB_HUB_PRINTF("get_hub_status returned status 0x%x, change 0x%x\n",
		swap_16(hubsts->wHubStatus),swap_16(hubsts->wHubChange));
	USB_HUB_PRINTF("local power source is %s\n",
		(swap_16(hubsts->wHubStatus) & HUB_STATUS_LOCAL_POWER) ? "lost (inactive)" : "good");
	USB_HUB_PRINTF("%sover-current condition exists\n",
		(swap_16(hubsts->wHubStatus) & HUB_STATUS_OVERCURRENT) ? "" : "no ");

	usb_hub_power_on(hub);

	/* fox add 080701 for stable power on */
	#ifdef usb_speed_up
	wait_ms(10);	
	#else
	wait_ms(200);
	#endif
	
	for (i = 0; i < dev->maxchild; i++) {
		struct usb_port_status portsts;
		unsigned short portstatus, portchange;

		if (usb_get_port_status(dev, i + 1, &portsts) < 0) {
			USB_HUB_PRINTF("get_port_status failed\n");
			continue;
		}
		portstatus = swap_16(portsts.wPortStatus);
		portchange = swap_16(portsts.wPortChange);
		USB_HUB_PRINTF("Port %d Status 0x%x Change 0x%x\n",i+1,portstatus,portchange);
		if (portchange & USB_PORT_STAT_C_CONNECTION) {
			USB_HUB_PRINTF("port %d connection change\n", i + 1);
			usb_hub_port_connect_change(dev, i);
		}

		
		if (portchange & USB_PORT_STAT_C_ENABLE) {
			USB_HUB_PRINTF("port %d enable change, status 0x%x\n", i + 1, portstatus);
			usb_clear_port_feature(dev, i + 1, USB_PORT_FEAT_C_ENABLE);

			/* EM interference sometimes causes bad shielded USB devices to
			 * be shutdown by the hub, this hack enables them again.
			 * Works at least with mouse driver */
			if (!(portstatus & USB_PORT_STAT_ENABLE) &&
				(portstatus & USB_PORT_STAT_CONNECTION) && (dev->children[i])) {
				USB_HUB_PRINTF("already running port %i disabled by hub (EMI?), re-enabling...\n",
					i + 1);
					usb_hub_port_connect_change(dev, i);
			}
		}
		if (portstatus & USB_PORT_STAT_SUSPEND) {
			USB_HUB_PRINTF("port %d suspend change\n", i + 1);
			usb_clear_port_feature(dev, i + 1,  USB_PORT_FEAT_SUSPEND);
		}

		if (portchange & USB_PORT_STAT_C_OVERCURRENT) {
			USB_HUB_PRINTF("port %d over-current change\n", i + 1);
			usb_clear_port_feature(dev, i + 1, USB_PORT_FEAT_C_OVER_CURRENT);
			usb_hub_power_on(hub);
		}

		if (portchange & USB_PORT_STAT_C_RESET) {
			USB_HUB_PRINTF("port %d reset change\n", i + 1);
			usb_clear_port_feature(dev, i + 1, USB_PORT_FEAT_C_RESET);
		}

	} /* end for i all ports */
	
	return 0;
}

int usb_hub_probe(struct usb_device *dev, int ifnum)
{
	struct usb_interface_descriptor *iface;
	struct usb_endpoint_descriptor *ep;
	int ret;

	iface = &dev->config.if_desc[ifnum];
	/* Is it a hub? */
	if (iface->bInterfaceClass != USB_CLASS_HUB)
		return 0;
	/* Some hubs have a subclass of 1, which AFAICT according to the */
	/*  specs is not defined, but it works */
	if ((iface->bInterfaceSubClass != 0) &&
	    (iface->bInterfaceSubClass != 1))
		return 0;
	/* Multiple endpoints? What kind of mutant ninja-hub is this? */
	if (iface->bNumEndpoints != 1)
		return 0;
	ep = &iface->ep_desc[0];
	/* Output endpoint? Curiousier and curiousier.. */
	if (!(ep->bEndpointAddress & USB_DIR_IN))
		return 0;
	/* If it's not an interrupt endpoint, we'd better punt! */
	if ((ep->bmAttributes & 3) != 3)
		return 0;
	/* We found a hub */
	USB_HUB_PRINTF("USB hub found\n");
	ret=usb_hub_configure(dev);
	return ret;
}
void usb_init(void)
{
	int i;
        // struct usb_device *dev;
   #ifdef ENABLE_KSEG1ADDR
        pusb_dev = (struct usb_device *) KSEG1ADDR(&usb_dev[0]);
#else /* ENABLE_KSEG1ADDR */
        pusb_dev = (struct usb_device *) usb_dev;
#endif /* ENABLE_KSEG1ADDR */

    /* first make all devices unknown */
    for(i=0;i<USB_MAX_DEVICE;i++) {
            memset(&pusb_dev[i],0,sizeof(struct usb_device));
            pusb_dev[i].devnum=-1;
    }

}
// #endif /* (CONFIG_COMMANDS & CFG_CMD_USB) */

/* EOF */
