
#include <common.h>
#include "linux/compat.h"
#include <asm/arch/system.h>
#include <rtd_types_qc.h>

#if defined(CONFIG_BOOT_TIMER)
#include <timer.h>
#endif

#if !defined(CONFIG_FPGA)
//#include <rtd2885_pll.h>
#endif

#include "rl6233_reg.h"
#include "rtd_usb.h"

#define  WRAP_BASE                           RTD_WRAP_BASE
#define  WRAP_VStatusOut                     (WRAP_BASE + 0x04)
#define  WRAP_VStatusOut_set_vstatus(data)   (0x000000FF&(data))
#define  USBIPINPUT_REG						(WRAP_BASE + 0x8)
#define  RESET_UTMI_REG						(WRAP_BASE + 0xC)

#define  WRAP_BASE1                           (RTD_WRAP_BASE+0x20)
#define  WRAP_VStatusOut1                     (WRAP_BASE1 + 0x04)
#define  USBIPINPUT_REG1					  (WRAP_BASE1 + 0x8)
#define  RESET_UTMI_REG1					  (WRAP_BASE1 + 0xC)

#define  EHCI_INSNREG01                       (RTD_EHCI_BASE + 0x94)
#define  INSNREG01_IN_THRESHOLD(x)			  (x&0xffff)
#define  INSNREG01_OUT_THRESHOLD(x)			  ((x&0xffff)<<16)

#define  EHCI_INSNREG03                       (RTD_EHCI_BASE + 0x9C)
#define  INSNREG03_BREAK_MEM_TRAN_EN		  (1)

#define  EHCI_INSNREG05                               (RTD_EHCI_BASE + 0xa4)
#define  EHCI_INSNREG05_set_VPort(data)               (0x0001E000&((data)<<13))
#define  EHCI_INSNREG05_bit_VLoadM                    (0x00001000)
#define  EHCI_INSNREG05_set_VLoadM(data)              (0x00001000&((data)<<12))
#define  EHCI_INSNREG05_bit_VCtrl                     (0x00000F00)
#define  EHCI_INSNREG05_set_VCtrl(data)               (0x00000F00&((data)<<8))
#define  EHCI_INSNREG05_get_VBusy(data)               ((0x00020000&(data))>>17)
#define  EHCI_INSNREG05_get_VStatus(data)             (0x000000FF&(data))



void USBPHY_Register_Setting(void)
{
//	rtd_outl(0xb801380c,0x00000001);         //Mac0 UTMI reset
//	rtd_outl(0xb801380c,0x00000000);         //Mac0 UTMI reset

//	rtd_outl(0xb801280c,0x00000001);         //Mac1 UTMI reset
//	rtd_outl(0xb801280c,0x00000000);         //Mac1 UTMI reset


	printk("load phy parameter...\n");


	/////////////////////0xE0 手動調整Z0//////////////////////
	//Mac0 Write Port 0 manual mode
	rtd_outl(0xb8013804,0x60);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);
	rtd_outl(0xb8013804,0xa1);        //調整參數[5:2]
	udelay(10);
	rtd_outl(0xb80130a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);
	rtd_inl(0xb80130a4);

	//Mac0 Write Port 1 manual mode
	rtd_outl(0xb8013824,0x60);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);
	rtd_outl(0xb8013824,0xa1);        //調整參數[5:2]
	udelay(10);
	rtd_outl(0xb80130a4,0x00024000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);
	rtd_inl(0xb80130a4);

	//Mac1 Write Port 0 manual mode
	rtd_outl(0xb8012804,0x60);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);
	rtd_outl(0xb8012804,0xa1);        //調整參數[5:2]
	udelay(10);
	rtd_outl(0xb80120a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);
	rtd_inl(0xb80120a4);
	////////////////E1//////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x2e);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022100);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write port1 E1
	rtd_outl(0xb8013824,0x2e);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024100);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write port0 E1
	rtd_outl(0xb8012804,0x2e);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022100);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	///////////////E2影響EOP width& Bit 結果/////////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x9a);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022200);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1 E2
	rtd_outl(0xb8013824,0x9a);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024200);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9a);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022200);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	///////////////  E 3 /////////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x8b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022300);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x8b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024300);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0
	rtd_outl(0xb8012804,0x8b);                   
	udelay(10);
	rtd_outl(0xb80120a4,0x00022300);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	///////////////////E4調整Output Swing////////////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x8c);    //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x8c);     //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0 
	rtd_outl(0xb8012804,0x8c);     //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);



	///////   E7  ////////////////
	//Mac0 Write Port 0 E7  
	rtd_outl(0xb8013804,0x81);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1

	rtd_outl(0xb8013824,0x81);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x81);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	/////////////////////MAC0 P0調整RX 0xE0/Page1//////////////////////
	//Mac0 Write Port 0/page1
	rtd_outl(0xb8013804,0xbb);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0x21);        //先對Bit2校正歸零
	udelay(10);
	rtd_outl(0xb80130a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);
	rtd_outl(0xb8013804,0x25);        //再設定參數
	udelay(10);
	rtd_outl(0xb80130a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port1/page1
	rtd_outl(0xb8013824,0xbb);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0x21);        //先對Bit2校正歸零
	udelay(10);
	rtd_outl(0xb80130a4,0x00024000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);
	rtd_outl(0xb8013824,0x25);        //再設定參數
	udelay(10);
	rtd_outl(0xb80130a4,0x00024000);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0 /page1
	rtd_outl(0xb8012804,0xbb);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0x21);        //先對Bit2校正歸零
	udelay(10);
	rtd_outl(0xb80120a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);
	rtd_outl(0xb8012804,0x25);        //再設定參數
	udelay(10);
	rtd_outl(0xb80120a4,0x00022000);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);


	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8012804,0x9b);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);


///////////////////E4調整Output Swing////////////////////////////////
	//ac0 Write Port 0
	rtd_outl(0xb8013804,0xdc);     //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);
	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0xdc);    //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);
	//Mac1 Write Port 0 
	rtd_outl(0xb8012804,0xdc);     //調整參數[3:0]
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	///////   E7  ////////////////
	//Mac0 Write Port 0 E7  
	rtd_outl(0xb8013804,0x71);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);
	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x71);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);
	rtd_inl(0xb80130a4);

	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x71);
	 udelay(10);
	rtd_outl(0xb80120a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);



	///////////////   E5  ////////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x1d);
	rtd_outl(0xb80130a4,0x00022500);
	rtd_outl(0xb80130a4,0x00022e00);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x1d);
	rtd_outl(0xb80130a4,0x00024500);    
	rtd_outl(0xb80130a4,0x00024e00);

	//Mac1 Write Port 0
	rtd_outl(0xb8012804,0x1d);
	rtd_outl(0xb80120a4,0x00022500);    
	rtd_outl(0xb80120a4,0x00022e00);



	///////////////   E5  ////////////////////////////
	//Mac0 Write Port 0
	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0x1d);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022500);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0x1d);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024500);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9b);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0x1d);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022500);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

	///////   E6  ////////////////
	//Mac0 Write Port 0  
	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0xca);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022600);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0xca);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024600);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9b);
	 udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0xca);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022600);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);

#if 0
	///////   E7  ////////////////
	//Mac0 Write Port 0 E7  
	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0x71);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0x71);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024700);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9b);
	 udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0x71);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022700);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022e00);
	udelay(10);
#endif
	////////////////////調整Slew rate 0xE1/Page1//////////////////////
	//Mac0 Write Port 0/page1
	rtd_outl(0xb8013804,0xbb);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0xaf);        //調整參數[7:5]
	udelay(10);
	rtd_outl(0xb80130a4,0x00022100);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022e00);
	udelay(10);

	//Mac0 Write Port 1/page1
	rtd_outl(0xb8013824,0xbb);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0xaf);        //調整參數[7:5]
	udelay(10);
	rtd_outl(0xb80130a4,0x00024100);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024e00);
	udelay(10);

	//Mac1 Write Port 0/page1
	rtd_outl(0xb8012804,0xbb);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0xaf);        //調整參數[7:5]
	udelay(10);
	rtd_outl(0xb80120a4,0x00024100);
	udelay(10);
	rtd_outl(0xb80120a4,0x00024e00);
	udelay(10);


	///////   F2  ////////////////
	//Mac0 Write Port 0 F2 
	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0x00);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022200);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(10);

	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0x00);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024200);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(10);
	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9b);
	 udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0x00);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022200);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(10);


	///////   F6  ////////////////
	//Mac0 Write Port 0 F2 
	rtd_outl(0xb8013804,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8013804,0x00);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022600);
	udelay(10);
	rtd_outl(0xb80130a4,0x00022f00);
	udelay(10);
	//Mac0 Write Port 1
	rtd_outl(0xb8013824,0x9b);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024400);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(100);
	rtd_outl(0xb8013824,0x00);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024600);
	udelay(10);
	rtd_outl(0xb80130a4,0x00024f00);
	udelay(10);
	 //Mac1 Write Port 0
	rtd_outl(0xb8012804,0x9b);
	 udelay(10);
	rtd_outl(0xb80120a4,0x00022400);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(100);
	rtd_outl(0xb8012804,0x00);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022600);
	udelay(10);
	rtd_outl(0xb80120a4,0x00022f00);
	udelay(10);
		
}



#if 0
void USBPHY_Register_Setting1(void)
{

/////////////////////0xE0 手動調整Z0//////////////////////

#if 0
//manual mode  port1
rtd_outl(0xb8013824,0x60);
udelay(500);
rtd_outl(0xb80130a4,0x00024000);
udelay(500);
rtd_outl(0xb80130a4,0x00024e00);
udelay(500);
rtd_outl(0xb8013824,0x84);        //調整參數[5:2]
udelay(500);
rtd_outl(0xb80130a4,0x00024000);
udelay(500);
rtd_outl(0xb80130a4,0x00024e00);
udelay(5000);
#endif


////////////////E1不要設定//////////////////////////////////
//Mac0 Write Port 0  E1
#if 1
rtd_outl(0xb8013804,0x06);
udelay(10);
rtd_outl(0xb80130a4,0x00022100);
udelay(10);
rtd_outl(0xb80130a4,0x00022e00);
udelay(10);
#endif
//Mac0 Write port1 E1
//rtd_outl(0xb8013824,0x2e);
//rtd_outl(0xb80130a4,0x00024100);
//rtd_outl(0xb80130a4,0x00024e00);

//Mac1 Write port0 E1
//rtd_outl(0xb8012804,0x2e);
//rtd_outl(0xb80120a4,0x00022100);
//rtd_outl(0xb80120a4,0x00022e00);

///////////////E2影響EOP width& Bit 結果/////////////////////////////
//Mac0 Write Port 1 E2

#if 1
rtd_outl(0xb8013824,0xb5);  // default (0x94)
udelay(10);
rtd_outl(0xb80130a4,0x00024200);
udelay(10);
rtd_outl(0xb80130a4,0x00024e00);
udelay(10);
rtd_outl(0xb80130a4,0x00024200);
udelay(10);
rtd_outl(0xb80130a4,0x00024c00);
udelay(10);
printk("debug %x\n",rtd_inl(0xb80130a4));
#endif
///////////////  E 3 /////////////////////////////

#if 1
//Mac0 Write Port 1 E3
rtd_outl(0xb8013824,0x8b); //   ; default (0x85)
udelay(5);
rtd_outl(0xb80130a4,0x00024200);
udelay(5);
rtd_outl(0xb80130a4,0x00024e00);
udelay(5);
#endif

///////////////////E4調整Output Swing////////////////////////////////

#if 1
//Mac0 Write Port 0 E4
rtd_outl(0xb8013804,0x99); //     //調整參數[3:0]
udelay(10);
rtd_outl(0xb80130a4,0x00022400);
udelay(10);
rtd_outl(0xb80130a4,0x00022e00);
udelay(10);
#endif

//Mac0 Write Port 1 E4
//rtd_outl(0xb8013824,0x9b)     //調整參數[3:0]
//rtd_outl(0xb80130a4,0x00024400)       
//rtd_outl(0xb80130a4,0x00024e00)
//rtd_outl(0xb80130a4,0x00024400)       
//rtd_outl(0xb80130a4,0x00024c00)
//rtd_inl(0xb80130a4)

//Mac1 Write Port 0 E4
//rtd_outl(0xb8012804,0x9b)     //調整參數[3:0]//
//rtd_outl(0xb80120a4,0x00022400)       
//rtd_outl(0xb801230a4,0x00022e00)
//rtd_outl(0xb80130a4,0x00022400)       
//rtd_outl(0xb80130a4,0x00022c00)
//rtd_inl(0xb80120a4)

///////////////   E5  ////////////////////////////
#if 1
//MAC0 Write Port 0 E5
rtd_outl(0xb8013804,0x5d);
udelay(10);
rtd_outl(0xb80130a4,0x00022500);
udelay(10);
rtd_outl(0xb80130a4,0x00022e00);
udelay(10);


//MAC0 Write Port 1 E5
rtd_outl(0xb8013824,0x5d);
udelay(10);
rtd_outl(0xb80130a4,0x00024500);
udelay(10);
rtd_outl(0xb80130a4,0x00024e00);
udelay(10);
#endif

//Mac1 Write Port 0 E5
//rtd_outl(0xb8012804,0x5d)
//rtd_outl(0xb80120a4,0x00022500)       
//rtd_outl(0xb80120a4,0x00022e00)
//rtd_outl(0xb80120a4,0x00022500)       
//rtd_outl(0xb80120a4,0x00022c00)
//rtd_inl(0xb80120a4)

///////   E6  ////////////////

#if 1
 //Mac0 Write Port 0 E6  
rtd_outl(0xb8013804,0xca);
udelay(10);
rtd_outl(0xb80130a4,0x00022600);
udelay(10);
rtd_outl(0xb80130a4,0x00022e00);

//Mac0 Write Port 1 E6
rtd_outl(0xb8013824,0xca);
udelay(10);
rtd_outl(0xb80130a4,0x00024600);
udelay(10);
rtd_outl(0xb80130a4,0x00024e00);
udelay(10);
#endif

 //Mac1 Write Port 0 E6
//rtd_outl(0xb8012804,0x98)   
//rtd_outl(0xb80120a4,0x00022600)       
//rtd_outl(0xb80120a4,0x00022e00)

/////////////////////MAC0 P0調整RX 0xE0/Page1//////////////////////
//Mac0 Write Port 0 E0/page1
#if 1
rtd_outl(0xb8013804,0xbb);
udelay(10);
rtd_outl(0xb80130a4,0x00022400);
udelay(10);
rtd_outl(0xb80130a4,0x00022f00);
udelay(100);
rtd_outl(0xb8013804,0x25);        //調整參數[4:3]
udelay(10);
rtd_outl(0xb80130a4,0x00022000);
udelay(10);
rtd_outl(0xb80130a4,0x00022e00);
udelay(10);
#endif

//Mac0 Write Port1 E0/page1
rtd_outl(0xb8013824,0xbb);
udelay(10);
rtd_outl(0xb80130a4,0x00024400);
udelay(10);
rtd_outl(0xb80130a4,0x00024f00); // page change must delay 100
udelay(100);
rtd_outl(0xb8013824,0x25);        //調整參數[4:3]
udelay(10);
rtd_outl(0xb80130a4,0x00024000);
udelay(10);
rtd_outl(0xb80130a4,0x00024e00);
udelay(10);


//Mac1 Write Port 0 E0/page1
//rtd_outl(0xb8012804,0xbb)
//rtd_outl(0xb80120a4,0x00022400)       
//rtd_outl(0xb80120a4,0x00022f00)
//rtd_outl(0xb8012804,0x25);        //調整參數[4:3]
//rtd_outl(0xb80120a4,0x00022000)       
//rtd_outl(0xb80120a4,0x00022e00)
//rtd_outl(0xb80120a4,0x00022000)       
//rtd_outl(0xb80120a4,0x00022c00)
//rtd_inl(0xb80120a4)

////////////////////調整Slew rate 0xE1/Page1//////////////////////

#if 1
rtd_outl(0xb8013824,0xbb);
udelay(5);
rtd_outl(0xb80130a4,0x00024400);
udelay(5);
rtd_outl(0xb80130a4,0x00024f00);
udelay(5);
rtd_outl(0xb8013824,0xef);        //調整參數[7:5]
udelay(5);
rtd_outl(0xb80130a4,0x00024100);
udelay(5);
rtd_outl(0xb80130a4,0x00024e00);
udelay(5);
#endif

}

#endif

