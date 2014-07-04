#ifndef __QC_VERIFY_H__
#define __QC_VERIFY_H__

#define GETCHAR_ESC (0x1B == rtd_inl(0x18062300)) //UART0
//#define GETCHAR_ESC (0x1B == rtd_inl(0x1801bc00)) //UART1


#include "qc_verify_common.h"

extern void qc_verify(int option);

//timer
#define TC7TVR 0x1801B61C
#define TC7CVR 0x1801B63C
#define TC7CR  0x1801B65C
#define TC7ICR 0x1801B67C
#define TCWCR  0x1801B6F0
#define TCWTR  0x1801B6F4
#define TCWOV  0x1801B6FC

//for TVE/HDMI/AUDIO RX test
#define HDMI_EQC 0
#define VDC_EQC  1
#define IMD_EQC  2
#define AUDIO_EQC 3

/* extern QC related functions */
#if CONFIG_QC_DDR
extern int QC_Verifier_DDR(void);
#endif	

#if CONFIG_QC_PERIPHERAL
extern int QC_Verifier_PERIPHERAL(void);
#endif

#if CONFIG_QC_STANDBY
extern int QC_Verifier_Standby(void);		
#endif	

#if CONFIG_QC_NAND
extern int QC_Verifier_NAND(void);
#endif	

#if CONFIG_QC_AUDIO
extern int QC_Verifier_AUDIO(void);
#endif

#if CONFIG_QC_HDMI_TX
extern int QC_Verifier_HDMI_TX(void);
#endif

#if CONFIG_QC_HDMI_RX
extern int QC_Verifier_HDMI_RX(void);
#endif

#if CONFIG_QC_IFD
extern int QC_Verifier_IFD(void);
#endif

#if CONFIG_QC_VDC
extern int QC_Verifier_VDC(void);
#endif

#if CONFIG_QC_CEC
extern int QC_Verifier_CEC(void);
#endif

#if CONFIG_QC_USB
extern int QC_Verifier_USB(void);
#endif

#if CONFIG_QC_DTV_Demod
extern int QC_Verifier_DTV_Demod(void);
#endif	

#if CONFIG_QC_EMMC
extern int QC_Verifier_EMMC(void);		
#endif

#if CONFIG_QC_CARDREADER
extern int QC_Verifier_CardReader(void);		
#endif

#if CONFIG_QC_SPI
extern int QC_Verifier_SPI(void);		
#endif	

#if CONFIG_QC_EPI
extern int QC_Verifier_EPI(void);		
#endif

#if CONFIG_QC_GETN
extern int QC_Verifier_GETN(void);		
#endif

#if CONFIG_QC_I_DOMAIN
extern int QC_Verifier_I_Domain(void);		
#endif

#if CONFIG_QC_MD_DOMAIN
extern int QC_Verifier_MD_Domain(void);		
#endif

#if CONFIG_QC_MHL
extern int QC_Verifier_MHL(void);		
#endif

#if CONFIG_QC_VBI
extern int QC_Verifier_VBI(void);		
#endif

#if CONFIG_QC_VIP
extern int QC_Verifier_VIP(void);		
#endif

#if CONFIG_QC_BISR
extern int QC_Verifier_BISR(void);		
#endif

#if CONFIG_QC_BIST
extern int QC_Verifier_BIST(void);		
#endif

#if CONFIG_QC_TVE_TV
extern int QC_Verifier_TVE_TV(void);		
#endif

#if CONFIG_QC_TVE_BOX
extern int QC_Verifier_TVE_BOX(void);		
#endif

#if CONFIG_QC_I3DDMA
extern int QC_Verifier_I3DDMA(void);		
#endif

#if CONFIG_QC_SPI_NAND
extern int QC_Verifier_SPI_Nand(void);		
#endif

#if CONFIG_QC_YPPADC
extern int QC_Verifier_YPPADC(void);
#endif

#if CONFIG_QC_VE
extern int QC_Verifier_VE(void);
#endif	

#if CONFIG_QC_SCPU
extern int QC_Verifier_SCPU(void);
#endif	

#if CONFIG_QC_GPU
extern int QC_Verifier_GPU(void);
#endif	

#if CONFIG_QC_8051
extern int QC_Verifier_8051(void);
#endif	

#if CONFIG_QC_TVE_CGMS_YPP_OUTPUT_TEST
extern int QC_Verifier_TVE_TEST_CGMS(void);
#endif



typedef struct 
{
	char entry_name[64];
	int (*entry_function)(void);
} QC_IP_VERIFY_ENTRY_T;

#define QC_IP_VERIFY_ENTRY(x)		QC_IP_VERIFY_ENTRY_T __qc_verify_entry__ x##entery = {	\
										#x,						\
										x						\
								};	


#endif /* __QC_VERIFY_H__ */

