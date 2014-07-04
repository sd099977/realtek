#ifndef RTD_USB_H_
#define RTD_USB_H_

//#define RTD_EHCI_BASE		(0xB80F0000)
//#define RTD_OHCI_BASE		(0xB80F0400)
//#define RTD_WRAP_BASE		(0xB80F0800)
#if 1
#define USB_PHY_CTRL 		(0xb8000000)
#else
#define USB_PHY_CTRL 		(0xb8000000)
#endif
#define RTD_EHCI_BASE		(0xb8013000)
#define RTD_EHCI1_BASE		(0xb8012000)

#define RTD_OHCI_BASE		(0xb8013400)
#define RTD_WRAP_BASE		(0xb8013800)

#define  EHCI_INSNREG01                               (RTD_EHCI_BASE + 0x94)
#define  INSNREG01_IN_THRESHOLD(x)			(x&0xffff)
#define  INSNREG01_OUT_THRESHOLD(x)			((x&0xffff)<<16)

#define  EHCI_INSNREG03                               (RTD_EHCI_BASE + 0x9C)
#define  INSNREG03_BREAK_MEM_TRAN_EN		(1)

#define  EHCI_INSNREG05                               (RTD_EHCI_BASE + 0xa4)
#define  EHCI_INSNREG05_set_VPort(data)               (0x0001E000&((data)<<13))
#define  EHCI_INSNREG05_bit_VLoadM                    (0x00001000)
#define  EHCI_INSNREG05_set_VLoadM(data)              (0x00001000&((data)<<12))
#define  EHCI_INSNREG05_bit_VCtrl                     (0x00000F00)
#define  EHCI_INSNREG05_set_VCtrl(data)               (0x00000F00&((data)<<8))
#define  EHCI_INSNREG05_get_VBusy(data)               ((0x00020000&(data))>>17)
#define  EHCI_INSNREG05_get_VStatus(data)             (0x000000FF&(data))

// #define SYSCTRL_LXBUS_TIMEOUT_STATUS		(0xB8001018)
// #define SYSCTRL_LXBUS_TIMEOUT_ADDRESS 		(0xb800101c)
// #define SYSCTRL_LXBUS_PRIORITY_COUNT_3		(0xB8001008)
#define LX_USB_PRICNT_STA(x)			((x&0xff)<<24)
#define LX_USB_PRICNT_END(x)			((x&0xff)<<16)

#define LX_USB_ID                          (4)

#endif /*RTD_USB_H_*/
