
/* @version 	$Revision: 0.1 $
 * @ingroup 		TVE
 */

/**
 * @addtogroup VIDEO_ENCODER
 * @{
 */

/*================ Module dependency  =============== */
#include <qc_verify_common.h>
#define __TVE__

#if 1 
#include "../include/tve_tv_reg.h"
#include "../include/rbusTVE_DMAReg_TV.h"
#include "../include/rbusIFD_AnalogReg.h"
#include "../include/TVE_TV_qc.h"
#include "../include/rbusIFD_AnalogReg.h"	//////////////
//#include "../include/qc_verify.h"	
#include "qc_verify.h"
#include "../VDC/vdc_qc.h"
#include "../VDC/rbusAdcReg.h"	
#include "../VDC/rbusVDIFDinReg.h"
#include "../VDC/rbusVDPQReg.h"
#include "../VDC/rbusVDTopReg.h"
//#include "../include/rbusVDIFDinReg.h"
//#include "../include/rbusVDPQReg.h"
//#include "../include/rbusVDTopReg.h"
//#include "../include/rbusSYSTEMReg.h"
#else
#include <tve_tv_reg.h>
#include <rbusTVE_DMAReg_TV.h>
#include <rbusIFD_AnalogReg.h>
#include <TVE_TV_qc.h>
#include <rbusAdcReg.h>	//////////////
#include <rbusVDIFDinReg.h>
#include <rbusVDPQReg.h>
#include <rbusVDTopReg.h>
#endif

#define _SUCCESS		0
#define _FAIL			1
#define _ENABLE 			1
#define _DISABLE			0
#define _TRUE			1
#define _FALSE			0

/*==================== Definitions ================ */
typedef unsigned char BIT;
/*
#define ScalerTimer_DelayXms(mSec)		udelay(mSec)
#define rtd_outl(offset, val)				rtd_outl(offset,val)
#define rtdf_inl(offset)					rtd_inl(offset)
#define rtdf_maskl(offset, andMask, orMask)	rtd_maskl(offset,andMask,orMask)
*/
/*==================== Variables ================== */



/*=====================function=====================*/

//=================================================================
/**
 * drv_tve_set_video_ntsc_m
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_ntsc_m(void)
{
		rtd_outl(VIDEO_DAC_CTRL_0_reg,0x00785145);  
		rtd_outl(VIDEO_DAC_CTRL_1_reg,0x00785145);  
		rtd_outl(DAC_MUX_reg,0x00001fc0);  
		rtd_outl(CMP_DLY_reg,0x00000124);  
		rtd_outl(DAC_MISC_reg,0x00000020);  
		rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x0000591e);  
		rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x0000591e);  
		rtd_outl(SYNCGEN_RST_reg,0x000002AA);  
		rtd_outl(IP_Y_GAIN_reg,0x00000200);  
		rtd_outl(IP_PHS_0_reg,0x0000001f);  
		rtd_outl(IP_PHS_1_reg,0x0000007c);  
		rtd_outl(IP_PHS_2_reg,0x000000f0);  
		rtd_outl(IP_PHS_3_reg,0x00000021);  
		rtd_outl(IP_SCTOH_0_reg,0x00000000);  
		rtd_outl(IP_SCTOH_1_reg,0x00000002);  
		rtd_outl(IP_SCTOH_2_reg,0x00000002);  
		rtd_outl(IP_SCTOH_3_reg,0x00000044);  
		rtd_outl(IP_F_CTRL_reg,0x00000002);  
		rtd_outl(IP_BLCK_LVL_reg,0x0000008d);  
		rtd_outl(IP_BLNK_LVL_reg,0x00000078);  
		rtd_outl(IP_CLAMP_LVL_reg,0x00000010);  
		rtd_outl(IP_SYNC_LVL_reg,0x00000007);  
		rtd_outl(IP_Y_CTRL_reg,0x0000001c);  
		rtd_outl(IP_TEST_PARAM_reg,0x00000020);  
		rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);  
		rtd_outl(IP_O_CTRL_reg,0x00000000);  
		rtd_outl(IP_NBA_reg,0x000000bb);//0xc8  
		rtd_outl(IP_PBA_reg,0x00000000);  
		rtd_outl(IP_C_CTRL_reg,0x00000000);  
		rtd_outl(IP_S_CTRL_reg,0x00000008);  
		rtd_outl(IP_VSO0_reg,0x00000031);  
		rtd_outl(IP_VSO1_reg,0x00000006);  
		rtd_outl(IP_HSO0_reg,0x00000006);  
		rtd_outl(IP_HSO1_reg,0x000000b3);  
		rtd_outl(IP_HLC0_reg,0x00000003);  
		rtd_outl(IP_HLC1_reg,0x00000059);  
		rtd_outl(IP_SYNC_LVL2_reg,0x00000069); //0x64 
		rtd_outl(IP_SYNC_LVL3_reg,0x0000002d);  
		rtd_outl(IP_SYNC_LVL4_reg,0x00000007);  
		rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000014);  
		rtd_outl(IP_MVFCR_reg,0x00000000);  
		rtd_outl(IP_MVCSL1_reg,0x0000003a);  
		rtd_outl(IP_MVCLS1_reg,0x00000011);  
		rtd_outl(IP_MVCSL2_reg,0x0000004b);  
		rtd_outl(IP_MVCLS2_reg,0x00000011);  
		rtd_outl(IP_MVCSSP_reg,0x0000003c);  
		rtd_outl(IP_MVPSD_reg,0x0000001b);  
		rtd_outl(IP_MVPSL_reg,0x0000001b);  
		rtd_outl(IP_MVPSS_reg,0x00000024);  
		rtd_outl(IP_MVPSLS0_reg,0x00000007);  
		rtd_outl(IP_MVPSLS1_reg,0x000000f8);  
		rtd_outl(IP_MVPSFS0_reg,0x00000000);  
		rtd_outl(IP_MVPSFS1_reg,0x00000000);  
		rtd_outl(IP_MVPSAGCA_reg,0x0000000f);  
		rtd_outl(IP_MVPSAGCB_reg,0x0000000f);  
		rtd_outl(IP_MVEOFBPC_reg,0x00000060);  
		rtd_outl(IP_MVPBZ1_reg,0x000000a0);  
		rtd_outl(IP_MVPBZ3_reg,0x00000054);  
		rtd_outl(IP_MVPCSLIMD0_reg,0x000000ff);  
		rtd_outl(IP_MVPCSLIMD1_reg,0x00000003);  
		rtd_outl(IP_MV_CTRL_reg,0x00000010);  
		rtd_outl(IP_SYNC_STRT_reg,0x0000000c);  
		rtd_outl(IP_SYNC_END_reg,0x0000004b);  
		rtd_outl(IP_SYNC_SREND_reg,0x0000007a);  
		rtd_outl(IP_SYNC_EQEND_reg,0x0000002b);  
		rtd_outl(IP_ACTV_STRT_reg,0x00000089);//85  
		rtd_outl(IP_ACTV_END_reg,0x000000a6); //aa 
		rtd_outl(IP_WBRST_STRT_reg,0x0000005a);  
		rtd_outl(IP_NBRST_STRT_reg,0x00000062);  
		rtd_outl(IP_NBRST_END_reg,0x00000084);  
		rtd_outl(SYNCGEN_I_reg,0x02832359);  
		rtd_outl(IP_VSYNCPOS_reg,0x00306505);  
		rtd_outl(IP_HSYNCPOS_reg,0x00000359);  
		rtd_outl(AV_I_HPOS_reg,0x08212353);  
		rtd_outl(SLEW_I_HPOS_reg,0x00242753);  
		rtd_outl(ITOP_VPOS_reg,0x00815904);  
		rtd_outl(IBOT_VPOS_reg,0x0091ca0b);  
		rtd_outl(AV_SLEW_reg,0x00000330);  
		rtd_outl(AV_CTRL_reg,0x0000007E);     // 0x19   pattern gen enable    7E patterngen disable
		rtd_outl(I_COLORBAR_HPOS_reg,0x0022cc82);  
		rtd_outl(COMP_CTRL_reg,0x00003ffe);      //  control
		rtd_outl(COMP_CTRL_reg,0x00003409);      //  vbi_mux_on Y/G  hsync high active component oru enable SDTV on
		rtd_outl(SRSTN_reg,0x00000001);	
		rtd_outl(SYNCGEN_RST_reg,0x000002aa);		  //  syncgen rst
		rtd_outl(SYNCGEN_RST_reg,0x000003c0);		  //  syncgen rst
		//rtd_outl(TVE_DMA_TVE_VDDMA_VADDR,0x20052014);	
		//rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00400000);	  //  dma addr
		//rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00600000);	  //  dma addr
		//rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00800000);	  //  dma addr
		//rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00a00000);	  //  dma addr

}


//=================================================================
/**
 * drv_tve_set_video_ntsc_443
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_ntsc_443(void)
{
	rtd_outl(VIDEO_DAC_CTRL_0_reg,0x00785145);  
	rtd_outl(VIDEO_DAC_CTRL_1_reg,0x00485145);  
	rtd_outl(CMP_DLY_reg,0x00000124);  
	rtd_outl(DAC_MUX_reg,0x00001fc0);  
	rtd_outl(DAC_MISC_reg,0x00200000);  
	rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x0000591e);  
	rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x0000591e);  
	rtd_outl(IP_Y_GAIN_reg,0x00000200);  
	rtd_outl(IP_PHS_0_reg,0x000000cb);  
	rtd_outl(IP_PHS_1_reg,0x0000008a);  
	rtd_outl(IP_PHS_2_reg,0x00000009);  
	rtd_outl(IP_PHS_3_reg,0x0000002a);  
	rtd_outl(IP_SCTOH_0_reg,0x00000000);  
	rtd_outl(IP_SCTOH_1_reg,0x00000000);  
	rtd_outl(IP_SCTOH_2_reg,0x00000000);  
	rtd_outl(IP_SCTOH_3_reg,0x00000000);  
	rtd_outl(IP_F_CTRL_reg,0x00000000);  
	rtd_outl(IP_BLCK_LVL_reg,0x0000008d);  
	rtd_outl(IP_BLNK_LVL_reg,0x00000078);  
	rtd_outl(IP_CLAMP_LVL_reg,0x00000010);  
	rtd_outl(IP_SYNC_LVL_reg,0x00000004);  
	rtd_outl(IP_Y_CTRL_reg,0x0000001c);  
	rtd_outl(IP_Y_CTRL_reg,0x0000001c);  
	rtd_outl(IP_TEST_PARAM_reg,0x00000020);  
	rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);  
	rtd_outl(IP_O_CTRL_reg,0x00000000);  
	rtd_outl(IP_NBA_reg,0x000000c8);  
	rtd_outl(IP_PBA_reg,0x00000000);  
	rtd_outl(IP_C_CTRL_reg,0x00000000);  
	rtd_outl(IP_S_CTRL_reg,0x00000008);  
	rtd_outl(IP_VSO0_reg,0x00000031);  
	rtd_outl(IP_VSO1_reg,0x00000006);  
	rtd_outl(IP_HSO0_reg,0x00000006);  
	rtd_outl(IP_HSO1_reg,0x000000b3);  
	rtd_outl(IP_HLC0_reg,0x00000003);  
	rtd_outl(IP_HLC1_reg,0x00000059);  
	rtd_outl(IP_SYNC_LVL2_reg,0x00000064);  
	rtd_outl(IP_SYNC_LVL3_reg,0x0000002d);  
	rtd_outl(IP_SYNC_LVL4_reg,0x00000007);  
	rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000018);  
	rtd_outl(IP_SYNC_STRT_reg,0x0000000c);  
	rtd_outl(IP_SYNC_END_reg,0x0000004b);  
	rtd_outl(IP_SYNC_SREND_reg,0x0000007a);  
	rtd_outl(IP_SYNC_EQEND_reg,0x0000002b);  
	rtd_outl(IP_ACTV_STRT_reg,0x00000085);  
	rtd_outl(IP_ACTV_END_reg,0x000000aa);  
	rtd_outl(IP_WBRST_STRT_reg,0x0000005a);  
	rtd_outl(IP_NBRST_STRT_reg,0x00000062);  
	rtd_outl(IP_NBRST_END_reg,0x00000084);  
	rtd_outl(SYNCGEN_I_reg,0x02832359);  
	rtd_outl(SYNCGEN_P_reg,0x0e832359);  
	rtd_outl(SYNCGEN_HDMI_reg,0x0e832359);  
	rtd_outl(IP_VSYNCPOS_reg,0x00306505);  
	rtd_outl(IP_HSYNCPOS_reg,0x00000319);  
	rtd_outl(AV_I_HPOS_reg,0x08112313);  
	rtd_outl(SLEW_I_HPOS_reg,0x00222713);  
	rtd_outl(ITOP_VPOS_reg,0x00815904);  
	rtd_outl(IBOT_VPOS_reg,0x0091ca0b);  
	rtd_outl(AV_P_HPOS1_reg,0x38222358);  
	rtd_outl(P_VPOS1_reg,0x0082aa09);  
	rtd_outl(AV_H_HPOS1_reg,0x28222358);  
	rtd_outl(H_VPOS1_reg,0x00815904);  
	rtd_outl(H_VPOS2_reg,0x0091ca0b);  
	rtd_outl(AV_SLEW_reg,0x000003b4);  
	rtd_outl(AV_CTRL_reg,0x0000007E);  
	rtd_outl(I_COLORBAR_HPOS_reg,0x0022d450);  
	rtd_outl(COMP_SYNCLVL_reg,0x1a081000);  
	rtd_outl(COMP_PBPR_SYNCLVL_reg,0x02081bb0);  
	rtd_outl(AV_COEFF1_reg,0x80008800);  
	rtd_outl(AV_COEFF2_reg,0x80008000);  
	rtd_outl(AV_COEFF3_reg,0x937c937c);  
	rtd_outl(AV_COEFF4_reg,0x8380a003);  
	rtd_outl(AV_COEFF5_reg,0x0000a003);  
	rtd_outl(BLNK_COEFF_reg,0x88008380);  
	rtd_outl(COMP_PBPR_BLNKLVL_reg,0x02781800);  
	rtd_outl(COMP_CTRL_reg,0x00003ffe);  
	rtd_outl(MV_CTRL_reg,0x0000000c);  
	rtd_outl(COMP_CTRL_reg,0x00003149);  
	rtd_outl(MV_CTRL_reg,0x00000005);  
	rtd_outl(SRSTN_reg,0x00000001);  
	rtd_outl(SYNCGEN_RST_reg,0x000002aa);  
	rtd_outl(SYNCGEN_RST_reg,0x000003d5);  
	rtd_outl(SYNCGEN_RST_reg,0x000003c0);	  //  syncgen rst
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00010000);	  //  dma addr

}






//=================================================================
/**
 * drv_tve_set_video_ntsc_j
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_ntsc_j()
{
		rtd_outl(VIDEO_DAC_CTRL_0_reg,0x00785145);  
		rtd_outl(VIDEO_DAC_CTRL_1_reg,0x00785145);  
		rtd_outl(DAC_MUX_reg,0x00001fc0);  
		rtd_outl(CMP_DLY_reg,0x00000124);  
		rtd_outl(DAC_MISC_reg,0x00200000);  
		rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x0000591e);  
		rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x0000591e);  
		rtd_outl(IP_Y_GAIN_reg,0x00000224);  
		rtd_outl(IP_PHS_0_reg,0x0000001f);  
		rtd_outl(IP_PHS_1_reg,0x0000007c);  
		rtd_outl(IP_PHS_2_reg,0x000000f0);  
		rtd_outl(IP_PHS_3_reg,0x00000021);  
		rtd_outl(IP_SCTOH_0_reg,0x00000000);  
		rtd_outl(IP_SCTOH_1_reg,0x00000002);  
		rtd_outl(IP_SCTOH_2_reg,0x00000002);  
		rtd_outl(IP_SCTOH_3_reg,0x00000044);  
		rtd_outl(IP_F_CTRL_reg,0x00000002);  
		rtd_outl(IP_BLCK_LVL_reg,0x00000070);  
		rtd_outl(IP_BLNK_LVL_reg,0x00000070);  
		rtd_outl(IP_CLAMP_LVL_reg,0x00000010);  
		rtd_outl(IP_SYNC_LVL_reg,0x00000007);  
		rtd_outl(IP_Y_CTRL_reg,0x0000001c);  
		rtd_outl(IP_TEST_PARAM_reg,0x00000020);  
		rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);  
		rtd_outl(IP_O_CTRL_reg,0x00000000);  
		rtd_outl(IP_NBA_reg,0x000000c8);  
		rtd_outl(IP_PBA_reg,0x00000000);  
		rtd_outl(IP_C_CTRL_reg,0x00000000);  
		rtd_outl(IP_S_CTRL_reg,0x00000008);  
		rtd_outl(IP_VSO0_reg,0x00000031);  
		rtd_outl(IP_VSO1_reg,0x00000006);  
		rtd_outl(IP_HSO0_reg,0x00000006);  
		rtd_outl(IP_HSO1_reg,0x000000b3);  
		rtd_outl(IP_HLC0_reg,0x00000003);  
		rtd_outl(IP_HLC1_reg,0x00000059);  
		rtd_outl(IP_SYNC_LVL2_reg,0x00000064);  
		rtd_outl(IP_SYNC_LVL3_reg,0x0000002d);  
		rtd_outl(IP_SYNC_LVL4_reg,0x00000007);  
		rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000014);  
		rtd_outl(IP_SYNC_STRT_reg,0x0000000c);  
		rtd_outl(IP_SYNC_END_reg,0x0000004b);  
		rtd_outl(IP_SYNC_SREND_reg,0x0000007a);  
		rtd_outl(IP_SYNC_EQEND_reg,0x0000002b);  
		rtd_outl(IP_ACTV_STRT_reg,0x00000085);  
		rtd_outl(IP_ACTV_END_reg,0x000000aa);  
		rtd_outl(IP_WBRST_STRT_reg,0x0000005a);  
		rtd_outl(IP_NBRST_STRT_reg,0x00000062);  
		rtd_outl(IP_NBRST_END_reg,0x00000084);  
		rtd_outl(SYNCGEN_I_reg,0x02832359);  
		rtd_outl(IP_VSYNCPOS_reg,0x00306505);  
		rtd_outl(IP_HSYNCPOS_reg,0x00000359);  
		rtd_outl(AV_I_HPOS_reg,0x08212353);  
		rtd_outl(ITOP_VPOS_reg,0x00815904);  
		rtd_outl(SLEW_I_HPOS_reg,0x00242753);  
		rtd_outl(IBOT_VPOS_reg,0x0091ca0b);  
		rtd_outl(AV_SLEW_reg,0x00000330);  
		rtd_outl(AV_CTRL_reg,0x0000007E);  
		rtd_outl(I_COLORBAR_HPOS_reg,0x0022cc82);  
		rtd_outl(COMP_CTRL_reg,0x00003ffe);      //  control
		rtd_outl(COMP_CTRL_reg,0x00003409);      //  vbi_mux_on Y/G  hsync high active component oru enable SDTV on
		rtd_outl(SRSTN_reg,0x00000001);  
		rtd_outl(SYNCGEN_RST_reg,0x000002aa);  
		rtd_outl(SYNCGEN_RST_reg,0x000003c0);  	  //  syncgen rst
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00010000);  	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00010000);  	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00010000);  	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00010000);  	  //  dma addr
                                 
}                                
                                 
//=================================================================
/**                                
 * drv_tve_set_video_pal_60        
 *                                 
 *                                 
 * @param <mode>                   
 * @return {void}                  
 */                                
void drv_tve_set_video_pal_60()    
{                                  
		rtd_outl(CMP_DLY_reg,0x00000124);    
		rtd_outl(DAC_MUX_reg,0x00001fc0);    
		rtd_outl(DAC_MISC_reg,0x00238000);	  
		rtd_outl(VIDEO_DAC_CTRL_0_reg,0x0078b000);	  
		rtd_outl(VIDEO_DAC_CTRL_1_reg,0x0078c30c);	  
		rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x00005b1e);	  
		rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x00005b1e);  
		rtd_outl(IP_Y_GAIN_reg,0x00000200);  
		rtd_outl(IP_PHS_0_reg,0x000000cb);  
		rtd_outl(IP_PHS_1_reg,0x0000008a);  
		rtd_outl(IP_PHS_2_reg,0x00000009);  
		rtd_outl(IP_PHS_3_reg,0x0000002a);  
		rtd_outl(IP_SCTOH_0_reg,0x00000000);  
		rtd_outl(IP_SCTOH_1_reg,0x00000000);  
		rtd_outl(IP_SCTOH_2_reg,0x00000000);  
		rtd_outl(IP_SCTOH_3_reg,0x00000000);  
		rtd_outl(IP_F_CTRL_reg,0x00000000);  
		rtd_outl(IP_BLCK_LVL_reg,0x0000008d);  
		rtd_outl(IP_BLNK_LVL_reg,0x00000078);  
		rtd_outl(IP_CLAMP_LVL_reg,0x00000010);  
		rtd_outl(IP_SYNC_LVL_reg,0x00000004);  
		rtd_outl(IP_Y_CTRL_reg,0x0000001d);  
		rtd_outl(IP_Y_CTRL_reg,0x0000001d);  
		rtd_outl(IP_TEST_PARAM_reg,0x00000020);  
		rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);  
		rtd_outl(IP_O_CTRL_reg,0x00000000);  
		rtd_outl(IP_NBA_reg,0x000000d7);  
		rtd_outl(IP_PBA_reg,0x00000029);  
		rtd_outl(IP_C_CTRL_reg,0x00000003);  
		rtd_outl(IP_S_CTRL_reg,0x0000000a);  
		rtd_outl(IP_VSO0_reg,0x00000031);  
		rtd_outl(IP_VSO1_reg,0x00000006);  
		rtd_outl(IP_HSO0_reg,0x00000006);  
		rtd_outl(IP_HSO1_reg,0x000000b3);  
		rtd_outl(IP_HLC0_reg,0x00000003);  
		rtd_outl(IP_HLC1_reg,0x00000058);  
		rtd_outl(IP_SYNC_LVL2_reg,0x00000064);  
		rtd_outl(IP_SYNC_LVL3_reg,0x0000002d);  
		rtd_outl(IP_SYNC_LVL4_reg,0x00000007);  
		rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000018);  
		rtd_outl(IP_SYNC_STRT_reg,0x0000000c);  
		rtd_outl(IP_SYNC_END_reg,0x0000004b);  
		rtd_outl(IP_SYNC_SREND_reg,0x0000007a);  
		rtd_outl(IP_SYNC_EQEND_reg,0x0000002b);  
		rtd_outl(IP_ACTV_STRT_reg,0x00000085);  
		rtd_outl(IP_ACTV_END_reg,0x000000aa);  
		rtd_outl(IP_WBRST_STRT_reg,0x0000005a);  
		rtd_outl(IP_NBRST_STRT_reg,0x00000062);  
		rtd_outl(IP_NBRST_END_reg,0x00000084);  
		rtd_outl(SYNCGEN_I_reg,0x02832359);  
		rtd_outl(SYNCGEN_P_reg,0x0e832359);  
		rtd_outl(SYNCGEN_HDMI_reg,0x0e832359);  
		rtd_outl(IP_VSYNCPOS_reg,0x00306505);  
		rtd_outl(IP_HSYNCPOS_reg,0x00000319);  
		rtd_outl(AV_I_HPOS_reg,0x08112313);  
		rtd_outl(SLEW_I_HPOS_reg,0x00222713);  
		rtd_outl(ITOP_VPOS_reg,0x00815904);  
		rtd_outl(IBOT_VPOS_reg,0x0091ca0b);  
		rtd_outl(AV_P_HPOS1_reg,0x38222358);  
		rtd_outl(P_VPOS1_reg,0x0082aa09);  
		rtd_outl(AV_H_HPOS1_reg,0x28112313);  
		rtd_outl(H_VPOS1_reg,0x00815904);  
		rtd_outl(H_VPOS2_reg,0x0091ca0b);  
		rtd_outl(AV_SLEW_reg,0x000003b4);  
		rtd_outl(AV_CTRL_reg,0x0000007E);  
		rtd_outl(I_COLORBAR_HPOS_reg,0x0022d450);  
		rtd_outl(AV_COEFF1_reg,0x80008800);  
		rtd_outl(AV_COEFF2_reg,0x80008000);  
		rtd_outl(AV_COEFF3_reg,0x937c937c);  
		rtd_outl(AV_COEFF4_reg,0x8380a003);  
		rtd_outl(AV_COEFF5_reg,0x0000a003);  
		rtd_outl(BLNK_COEFF_reg,0x88008380);  
		rtd_outl(COMP_PBPR_BLNKLVL_reg,0x02781800);  
		rtd_outl(COMP_SYNCLVL_reg,0x1a081000);  
		rtd_outl(COMP_PBPR_SYNCLVL_reg,0x02081bb0);  
		rtd_outl(COMP_CTRL_reg,0x00003ffe);  
		rtd_outl(MV_CTRL_reg,0x0000000c);  
		rtd_outl(COMP_CTRL_reg,0x00003149);  
		rtd_outl(MV_CTRL_reg,0x00000005);  
		rtd_outl(SRSTN_reg,0x00000001);  
		rtd_outl(SYNCGEN_RST_reg,0x000002aa);  
		rtd_outl(SYNCGEN_RST_reg,0x000003c0);  
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00010000);		  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00010000);		  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00010000);		  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00010000);		  //  dma addr

}


//=================================================================
/**
 * drv_tve_set_video_pal_cn
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_pal_cn()
{

		rtd_outl(CMP_DLY_reg,0x00000124);
		rtd_outl(DAC_MUX_reg,0x00001fc0);
		rtd_outl(DAC_MISC_reg,0x00238000);
		rtd_outl(VIDEO_DAC_CTRL_0_reg,0x0078b000);
		rtd_outl(VIDEO_DAC_CTRL_1_reg,0x0078c30c);
		rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x00005b1e);
		rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x00005b1e);
		rtd_outl(IP_Y_GAIN_reg,0x00000205);
		rtd_outl(IP_PHS_0_reg,0x00000046);
		rtd_outl(IP_PHS_1_reg,0x00000094);
		rtd_outl(IP_PHS_2_reg,0x000000f6); 
		rtd_outl(IP_PHS_3_reg,0x00000021); 
		rtd_outl(IP_SCTOH_0_reg,0x00000000); 
		rtd_outl(IP_SCTOH_1_reg,0x00000000); 
		rtd_outl(IP_SCTOH_2_reg,0x00000000); 
		rtd_outl(IP_SCTOH_3_reg,0x00000000); 
		rtd_outl(IP_F_CTRL_reg,0x00000000); 
		rtd_outl(IP_BLCK_LVL_reg,0x00000078); 
		rtd_outl(IP_BLNK_LVL_reg,0x00000078); 
		rtd_outl(IP_CLAMP_LVL_reg,0x00000010); 
		rtd_outl(IP_SYNC_LVL_reg,0x00000003); 
		rtd_outl(IP_Y_CTRL_reg,0x0000001d); 
		rtd_outl(IP_Y_CTRL_reg,0x0000001d); 
		rtd_outl(IP_TEST_PARAM_reg,0x00000020); 
		rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002); 
		rtd_outl(IP_O_CTRL_reg,0x00000000); 
		rtd_outl(IP_NBA_reg,0x000000d7); 
		rtd_outl(IP_PBA_reg,0x00000029); 
		rtd_outl(IP_C_CTRL_reg,0x00000003); 
		rtd_outl(IP_S_CTRL_reg,0x00000009); 
		rtd_outl(IP_VSO0_reg,0x00000031); 
		rtd_outl(IP_VSO1_reg,0x00000038); 
		rtd_outl(IP_HSO0_reg,0x00000006); 
		rtd_outl(IP_HSO1_reg,0x000000bf); 
		rtd_outl(IP_HLC0_reg,0x00000003); 
		rtd_outl(IP_HLC1_reg,0x0000005f); 
		rtd_outl(IP_SYNC_LVL2_reg,0x0000005c); 
		rtd_outl(IP_SYNC_LVL3_reg,0x00000040); 
		rtd_outl(IP_SYNC_LVL4_reg,0x00000024); 
		rtd_outl(IP_SYNCLPF_GAIN_reg,0x0000002b); 
		rtd_outl(IP_SYNC_STRT_reg,0x00000000); 
		rtd_outl(IP_SYNC_END_reg,0x0000003f); 
		rtd_outl(IP_SYNC_SREND_reg,0x00000071); 
		rtd_outl(IP_SYNC_EQEND_reg,0x00000020); 
		rtd_outl(IP_ACTV_STRT_reg,0x00000080); 
		rtd_outl(IP_ACTV_END_reg,0x000000a4); 
		rtd_outl(IP_WBRST_STRT_reg,0x00000050); 
		rtd_outl(IP_NBRST_STRT_reg,0x00000057); 
		rtd_outl(IP_NBRST_END_reg,0x00000075); 
		rtd_outl(SYNCGEN_I_reg,0x029c235f); 
		rtd_outl(SYNCGEN_P_reg,0x0e9c235f); 
		rtd_outl(SYNCGEN_HDMI_reg,0x0e9c235f); 
		rtd_outl(IP_VSYNCPOS_reg,0x0029ae6d); 
		rtd_outl(IP_HSYNCPOS_reg,0x0000031b); 
		rtd_outl(AV_I_HPOS_reg,0x080fa30d); 
		rtd_outl(SLEW_I_HPOS_reg,0x0021f70d); 
		rtd_outl(ITOP_VPOS_reg,0x00816935); 
		rtd_outl(IBOT_VPOS_reg,0x0094fa6e); 
		rtd_outl(AV_P_HPOS1_reg,0x381f234c); 
		rtd_outl(P_VPOS1_reg,0x0082ca6b); 
		rtd_outl(AV_H_HPOS1_reg,0x280fa30d); 
		rtd_outl(H_VPOS1_reg,0x00816935); 
		rtd_outl(H_VPOS2_reg,0x0094fa6e); 
		rtd_outl(AV_SLEW_reg,0x000003b4); 
		rtd_outl(AV_CTRL_reg,0x0000007E); 
		rtd_outl(I_COLORBAR_HPOS_reg,0x0022d43c); 
		rtd_outl(COMP_SYNCLVL_reg,0x1a081000); 
		rtd_outl(COMP_PBPR_SYNCLVL_reg,0x02081bb0); 
		rtd_outl(COMP_CTRL_reg,0x00003ffe); 
		rtd_outl(MV_CTRL_reg,0x0000000c); 
		rtd_outl(COMP_CTRL_reg,0x00003149); 
		rtd_outl(MV_CTRL_reg,0x00000005); 
		rtd_outl(AV_COEFF1_reg,0x80008800); 
		rtd_outl(AV_COEFF2_reg,0x80008000); 
		rtd_outl(AV_COEFF3_reg,0x937c937c); 
		rtd_outl(AV_COEFF4_reg,0x8380a003); 
		rtd_outl(AV_COEFF5_reg,0x0000a003); 
		rtd_outl(BLNK_COEFF_reg,0x88008380); 
		rtd_outl(COMP_PBPR_BLNKLVL_reg,0x02781800); 
		rtd_outl(SRSTN_reg,0x00000001); 
		rtd_outl(SYNCGEN_RST_reg,0x000002aa);   
		rtd_outl(SYNCGEN_RST_reg,0x000003c0); 
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00010000);	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00010000);	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00010000);	  //  dma addr
		rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00010000);	  //  dma addr
}


//=================================================================
/**
 * drv_tve_set_video_pal_i
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_pal_i()
{
	rtd_outl(COMP_CTRL_reg,0x00003ffe);
	rtd_outl(COMP_CTRL_reg,0x00003409);
	rtd_outl(VIDEO_DAC_CTRL_0_reg,0x00785145);
	rtd_outl(VIDEO_DAC_CTRL_1_reg,0x00785145);
	rtd_outl(DAC_MUX_reg,0x00001fc0);
	rtd_outl(CMP_DLY_reg,0x00000124);
	rtd_outl(DAC_MISC_reg,0x00200000);
	rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x00005b1e);
	rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x00005b1e);
	rtd_outl(IP_Y_GAIN_reg,0x00000205);
	rtd_outl(IP_PHS_0_reg,0x000000cb);
	rtd_outl(IP_PHS_1_reg,0x0000008a);
	rtd_outl(IP_PHS_2_reg,0x00000009);
	rtd_outl(IP_PHS_3_reg,0x0000002a);
	rtd_outl(IP_SCTOH_0_reg,0x00000000);
	rtd_outl(IP_SCTOH_1_reg,0x00000000);
	rtd_outl(IP_SCTOH_2_reg,0x00000000);
	rtd_outl(IP_SCTOH_3_reg,0x00000099);
	rtd_outl(IP_F_CTRL_reg,0x00000002);
	rtd_outl(IP_BLCK_LVL_reg,0x00000078);
	rtd_outl(IP_BLNK_LVL_reg,0x00000078);
	rtd_outl(IP_CLAMP_LVL_reg,0x00000010);
	rtd_outl(IP_SYNC_LVL_reg,0x00000003);
	rtd_outl(IP_Y_CTRL_reg,0x0000001d);
	rtd_outl(IP_TEST_PARAM_reg,0x00000020);
	rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);
	rtd_outl(IP_O_CTRL_reg,0x00000000);
	rtd_outl(IP_NBA_reg,0x000000cb);//d7
	rtd_outl(IP_PBA_reg,0x00000035);//29
	rtd_outl(IP_C_CTRL_reg,0x00000003);
	rtd_outl(IP_S_CTRL_reg,0x00000009);
	rtd_outl(IP_VSO0_reg,0x00000031);
	rtd_outl(IP_VSO1_reg,0x00000038);
	rtd_outl(IP_HSO0_reg,0x00000006);
	rtd_outl(IP_HSO1_reg,0x000000bf);
	rtd_outl(IP_HLC0_reg,0x00000003);
	rtd_outl(IP_HLC1_reg,0x0000005f);
	rtd_outl(IP_SYNC_LVL2_reg,0x00000058);
	rtd_outl(IP_SYNC_LVL3_reg,0x0000003e);
	rtd_outl(IP_SYNC_LVL4_reg,0x00000028);
	rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000022);
	rtd_outl(IP_SYNC_STRT_reg,0x00000000);
	rtd_outl(IP_SYNC_END_reg,0x00000040);
	rtd_outl(IP_SYNC_SREND_reg,0x00000071);
	rtd_outl(IP_SYNC_EQEND_reg,0x00000020);
	rtd_outl(IP_ACTV_STRT_reg,0x00000080);
	rtd_outl(IP_ACTV_END_reg,0x000000a4);
	rtd_outl(IP_WBRST_STRT_reg,0x00000050);
	rtd_outl(IP_NBRST_STRT_reg,0x00000056);
	rtd_outl(IP_NBRST_END_reg,0x00000074);
	rtd_outl(SYNCGEN_I_reg,0x029c235f);
	rtd_outl(IP_VSYNCPOS_reg,0x0029ae6d);
	rtd_outl(IP_HSYNCPOS_reg,0x0000031b);
	rtd_outl(AV_I_HPOS_reg,0x080fa30d);
	rtd_outl(SLEW_I_HPOS_reg,0x0021f70d);
	rtd_outl(ITOP_VPOS_reg,0x00816935);
	rtd_outl(IBOT_VPOS_reg,0x00950a6e);////0094fa6e
	rtd_outl(AV_SLEW_reg,0x00000330);
	rtd_outl(AV_CTRL_reg,0x0000007E);
	rtd_outl(I_COLORBAR_HPOS_reg,0x0022cc3e);
	rtd_outl(SRSTN_reg,0x00000001);
	rtd_outl(SYNCGEN_RST_reg,0x000002aa);
	rtd_outl(SYNCGEN_RST_reg,0x000003c0);  //  syncgen rst
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00040000);  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00040000);  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00040000);  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00040000);  //  dma addr
	rtd_outl(WSS_CTRL_reg,0x73006aaa);
	rtd_outl(WSS_POS_reg,0x00429416);
	rtd_outl(TVE_625P_WSS_POS_reg,0x0042954f);
	rtd_outl(VPS_DATA1_reg,0x000000aa);
	rtd_outl(VPS_DATA_2_reg,0xaaaaaaaa);
	rtd_outl(VPS_DATA_1_reg,0xaaaaaaaa);
	rtd_outl(VPS_DATA_0_reg,0xaaaaaaaa);
	rtd_outl(VPS_CTRL_reg,0x0434c103);
/*
	rtd_outl(0xb801F174,0x73006aaa);
	rtd_outl(0xb801F178,0x00429416);
	rtd_outl(1801F17c,0x73006123);
	rtd_outl(1801F180,0x0042954f);
	rtd_outl(1801F1ac,0x000000aa);
	rtd_outl(1801F1a8,0xaaaaaaaa);
	rtd_outl(1801F1a4,0xaaaaaaaa);
	rtd_outl(1801F1a0,0xaaaaaaaa);
	rtd_outl(1801F198,0x0434c103);
*/
}                              
//=================================================================
/**
 * drv_tve_set_video_pal_m
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_tve_set_video_pal_m()
{
	rtd_outl(CMP_DLY_reg,0x00000124);
	rtd_outl(DAC_MUX_reg,0x00001fc0);
	rtd_outl(DAC_MISC_reg,0x00238000);
	rtd_outl(VIDEO_DAC_CTRL_0_reg,0x0078b000);
	rtd_outl(VIDEO_DAC_CTRL_1_reg,0x0078c30c);
	rtd_outl(VIDEO_DAC_CTRL2_0_reg,0x00005b1e);
	rtd_outl(VIDEO_DAC_CTRL2_1_reg,0x00005b1e);
	rtd_outl(IP_Y_GAIN_reg,0x00000200);
	rtd_outl(IP_PHS_0_reg,0x000000a3);
	rtd_outl(IP_PHS_1_reg,0x000000ef);
	rtd_outl(IP_PHS_2_reg,0x000000e6);
	rtd_outl(IP_PHS_3_reg,0x00000021);
	rtd_outl(IP_SCTOH_0_reg,0x00000000);
	rtd_outl(IP_SCTOH_1_reg,0x00000000);
	rtd_outl(IP_SCTOH_2_reg,0x00000000);
	rtd_outl(IP_SCTOH_3_reg,0x00000000);
	rtd_outl(IP_F_CTRL_reg,0x00000000);
	rtd_outl(IP_BLCK_LVL_reg,0x0000008d);
	rtd_outl(IP_BLNK_LVL_reg,0x00000078);
	rtd_outl(IP_CLAMP_LVL_reg,0x00000010);
	rtd_outl(IP_SYNC_LVL_reg,0x00000004);
	rtd_outl(IP_Y_CTRL_reg,0x0000001d);
	rtd_outl(IP_Y_CTRL_reg,0x0000001d);
	rtd_outl(IP_TEST_PARAM_reg,0x00000020);
	rtd_outl(IP_TEST_T_BYP_CUPS_reg,0x00000002);
	rtd_outl(IP_O_CTRL_reg,0x00000000);
	rtd_outl(IP_NBA_reg,0x000000d7);
	rtd_outl(IP_PBA_reg,0x00000029);
	rtd_outl(IP_C_CTRL_reg,0x00000003);
	rtd_outl(IP_S_CTRL_reg,0x0000000a);
	rtd_outl(IP_VSO0_reg,0x00000031);
	rtd_outl(IP_VSO1_reg,0x00000006);
	rtd_outl(IP_HSO0_reg,0x00000006);
	rtd_outl(IP_HSO1_reg,0x000000b3);
	rtd_outl(IP_HLC0_reg,0x00000003);
	rtd_outl(IP_HLC1_reg,0x00000058);
	rtd_outl(IP_SYNC_LVL2_reg,0x00000064);
	rtd_outl(IP_SYNC_LVL3_reg,0x0000002d);
	rtd_outl(IP_SYNC_LVL4_reg,0x00000007);
	rtd_outl(IP_SYNCLPF_GAIN_reg,0x00000018);
	rtd_outl(IP_SYNC_STRT_reg,0x0000000c);
	rtd_outl(IP_SYNC_END_reg,0x0000004b);
	rtd_outl(IP_SYNC_SREND_reg,0x0000007a);
	rtd_outl(IP_SYNC_EQEND_reg,0x0000002b);
	rtd_outl(IP_ACTV_STRT_reg,0x00000085);
	rtd_outl(IP_ACTV_END_reg,0x000000aa);
	rtd_outl(IP_WBRST_STRT_reg,0x0000005a);
	rtd_outl(IP_NBRST_STRT_reg,0x00000062);
	rtd_outl(IP_NBRST_END_reg,0x00000084);
	rtd_outl(SYNCGEN_I_reg,0x02832359);
	rtd_outl(SYNCGEN_P_reg,0x0e832359);
	rtd_outl(SYNCGEN_HDMI_reg,0x0e832359);
	rtd_outl(IP_VSYNCPOS_reg,0x00306505);
	rtd_outl(IP_HSYNCPOS_reg,0x00000319);
	rtd_outl(AV_I_HPOS_reg,0x08112313);
	rtd_outl(SLEW_I_HPOS_reg,0x00222713);
	rtd_outl(ITOP_VPOS_reg,0x00815904);
	rtd_outl(IBOT_VPOS_reg,0x0091ca0b);
	rtd_outl(AV_P_HPOS1_reg,0x38222358);
	rtd_outl(P_VPOS1_reg,0x0082aa09);
	rtd_outl(AV_H_HPOS1_reg,0x28112313);
	rtd_outl(H_VPOS1_reg,0x00815904);
	rtd_outl(H_VPOS2_reg,0x0091ca0b);
	rtd_outl(AV_SLEW_reg,0x000003b4);
	rtd_outl(AV_CTRL_reg,0x0000007E);
	rtd_outl(I_COLORBAR_HPOS_reg,0x0022d450);
	rtd_outl(AV_COEFF1_reg,0x80008800);
	rtd_outl(AV_COEFF2_reg,0x80008000);
	rtd_outl(AV_COEFF3_reg,0x937c937c);
	rtd_outl(AV_COEFF4_reg,0x8380a003);
	rtd_outl(AV_COEFF5_reg,0x0000a003);
	rtd_outl(BLNK_COEFF_reg,0x88008380);
	rtd_outl(COMP_PBPR_BLNKLVL_reg,0x02781800);
	rtd_outl(COMP_SYNCLVL_reg,0x1a081000);
	rtd_outl(COMP_PBPR_SYNCLVL_reg,0x02081bb0);
	rtd_outl(COMP_CTRL_reg,0x00003ffe);
	rtd_outl(MV_CTRL_reg,0x0000000c);
	rtd_outl(COMP_CTRL_reg,0x00003149);
	rtd_outl(MV_CTRL_reg,0x00000005);
	rtd_outl(SRSTN_reg,0x00000001);
	rtd_outl(SYNCGEN_RST_reg,0x000002aa);
	rtd_outl(SYNCGEN_RST_reg,0x000003c0);
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT0_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT1_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT2_VADDR,0x00010000);	  //  dma addr
	rtd_outl(TVE_DMA_TVEVDDMA_SATRT3_VADDR,0x00010000);	  //  dma addr

}                      
           
                             
                               
void drvif_module_tve_set_mode(TVE_VIDEO_MODE_SEL mode)
{                              
	switch(mode)
	{
	 case TVE_NTSC:
			drv_tve_set_video_ntsc_m();
	 break;
	 case TVE_NTSC_J:
			drv_tve_set_video_ntsc_j();
	 break;
	 case TVE_NTSC_443:
			drv_tve_set_video_ntsc_443();
	 break;
	 case TVE_PAL_I:
			drv_tve_set_video_pal_i();
	 break;
	 case TVE_PAL_M:
			drv_tve_set_video_pal_m();
	 break;
	 case TVE_PAL_60:
			drv_tve_set_video_pal_60();
	 break;
	 case TVE_PAL_N:
			drv_tve_set_video_pal_cn();
	 break;

	}                             
                                                              
}                              
                               
                               
                               
  /**
  drvif_module_tve_clock_enable

  @param
             < on_off >   clock on or off
  @return <void>         { void }

*/                            
                               
 void drvif_module_tve_clock_enable(TVE_CLOCK on_off)
 {
 	if(on_off==TVE_CLOCK_ENABLE)
		rtdf_maskl(0xb800000c/*CRT_SYS_CLKEN1_VADDR*/,~_BIT16, _BIT16);                              
       else                        
              rtdf_maskl(0xb800000c/*CRT_SYS_CLKEN1_VADDR*/,~_BIT16, 0);                   
 }

void drvif_module_tve_AVout_Setting()
{
	rtd_outl(IFD_ANALOG_VDAC_BSO_VADDR, 0x00001452);
	rtd_outl(IFD_ANALOG_VDAC_VADDR, 0x00120000);
	rtd_outl(IFD_ANALOG_VDAC_TV_CTRL1_VADDR, 0x000010F0);
	rtd_outl(IFD_ANALOG_VDAC_TV_CTRL2_VADDR, 0x00000601);
}								
/**
  drvif_module_tve_AVout_MODE

  @param
             < mode >   tve or vd
  @return <void>         { void }

*/

void drvif_module_tve_AVout_MODE(TVE_AVOUT_MODE mode)
{
	rtd_maskl(IFD_ANALOG_VDAC_TV_SRC_SEL_VADDR,0xf8,mode);
}
                                                             
/**
  drvif_module_TVE_AVoutEnable

  @param
             < yes_no >   { _YES : select AVout is displaying source
                                    _No : select AVout is not displaying source }
  @return <void>         { void }

*/
void drvif_module_tve_AVout_Enable(TVE_AVOUT_EN on_off)
{
	if(on_off==TVE_AVOUT_ENABLE)
		rtd_maskl(IFD_ANALOG_VDAC_TV_CTRL2_VADDR,~_BIT4, _BIT4);
	else
		rtd_maskl(IFD_ANALOG_VDAC_TV_CTRL2_VADDR,~_BIT4, 0);

}




void drvif_module_tve_init()   
{
	//PLL RST and Enable CLK
	rtd_maskl(0xb8000004, 0xffffffff, _BIT16 | _BIT17);
	//rtd_outl(0xb8000008, 0xFE0C0431); //Reset bit [19] RSTN_VDEC Reset bit of  Video Decode (active low) [4] RSTN_APLL_ADC Reset bit of APLL_ADC [10] RSTN_VDEC2
	rtd_maskl(0xb8000008, 0xffffffff, _BIT19 | _BIT4 | _BIT10);
	//rtd_outl(0xb800000c, 0x1FFFFFFF);
	rtd_maskl(0xb800000c, 0xffffffff, _BIT26);
	//rtd_outl(0xb8000014, 0x09011787);//Clock enable bit [27]Clock enable bit for ATV Input Control of Video Decoder [24] Clock enable bit for APLL_ADC
	rtd_maskl(0xb8000014, 0xffffffff, _BIT27 | _BIT24);
	//rtd_outl(0xb8000018, 0x00020001);   	//ATVIN_CLK_SEL[17], 0x0: IFD, 0x1: VD
	rtd_maskl(0xb8000018, 0xffffffff, _BIT17);
	////PLL27x Clock : 108M
	rtd_maskl(0xb8000240,0xffffff80, 0x0E);
	rtd_maskl(0xb800024C, ~(_BIT12 | _BIT17), _BIT25 | _BIT13 | _BIT16);
	rtd_outl(0xb8000248, 0x00000000);      //Power off and rst PLL27x
	rtd_outl(0xb8000248, 0x00000017);			 //Power on PLL27x
	udelay(5);
	rtd_outl(0xb8020000,0x000000FF); 

	// externel [1]LDO100MA_POW [0]VDADC power on	3.3V				// VDADC_POW_CTL
	rtd_outl(0xb802005C,0x20000003); 

	// internel [22]ADC Power On [21]LDO Power On    1.xV
	rtd_outl(0xb8020054,0x04680001); 

	// VDADC_CKOUT_SEL[1:0]
	rtd_maskl(0xb8020058, 0xfffffffc, 0x0); 

	/////tve
 	
	rtdf_maskl(0xb8000008,~_BIT16, _BIT16);   
	rtdf_maskl(0xb800000c,~_BIT16, _BIT16);   
	drvif_module_tve_AVout_Setting();
	drvif_module_tve_AVout_Enable(TVE_AVOUT_ENABLE);
       drvif_module_tve_AVout_MODE(AVOUT_MODE_TVE_FOR_TV);
      
 } 

int drvif_module_tve_test_vd_mode(TVE_VIDEO_MODE_SEL test_mode)
{
	UINT32 i, j;
	UINT8  no_signal;
	UINT8  mode_check ;
	
  	for(i=0; i<2000; i++)
 	{
		/*for(j=0; j<500; j++)
 		{
  			udelay(2000);
		}*/
		udelay(50);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		if (no_signal == 0xe)
		{
			//printk("[QC][VD][Y VDBS test] no_signal = %x @ %d\n", no_signal, i);
			j=1;
			break;
		}
		else
			{
			//	printk("[QC][VD][Y VDBS fail] no_signal = %x @ %d\n", no_signal, i);
				j=0;
			}
	}
	if(j==0)
	{
		printk("[QC][VD][Y fail] no_signal");
		return _FAIL;

		}
	mode_check = ((UINT8)rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR) & 0x0f);
	printk("[QC][VD][Y VDBS test] mode_check = %x \n", mode_check);
	udelay(500);

	if(test_mode==TVE_PAL_I)
	{
		if(mode_check==0x06)
				return _SUCCESS;

	}
	else if(test_mode==TVE_NTSC)
		{
			if(mode_check==0x00)
				return _SUCCESS;

		}


		return _FAIL;;
	



}


int drvif_module_tve_test_case()
{
	UINT8 i=0;
	 int result=0;
	printk("drvif_module_tve_test_case,tve init \n");
	//drvif_module_tve_init();
/*
	printk("drvif_module_tve_test_case,set mode=ntsc \n");
	drvif_module_tve_set_mode(TVE_NTSC);
	rtd_outl(AV_CTRL_reg,0x19);  
       rtd_outl(0xb800a038,0x01);	
*/

	vdc_open_vin7p_for_ifd_loopback_test();
	drvif_module_tve_init();
	for(i=0;i<=1;i++)
       {
	   
		printk("  mode=%d\n",i);
		switch(i)
		{
		        case 0:
				drvif_module_tve_set_mode(TVE_PAL_I);
				rtd_outl(AV_CTRL_reg,0x19);  
			       rtd_outl(0xb800a038,0x01);
				udelay(20);   
				udelay(20);   
				udelay(20);
				udelay(20);
				udelay(20);
				udelay(20);   
			  	printk(" test  cvbs pal\n");
	        		//result=UART1_to_MAC(VDC_EQC,1);
	        		//if(result==FAILED)
	        		result=drvif_module_tve_test_vd_mode(TVE_PAL_I);
				if(result==_FAIL)
					printk(" test  cvbs pal ....fail\n");
			 break;	
			   case 1:
				drvif_module_tve_set_mode(TVE_NTSC);
				rtd_outl(AV_CTRL_reg,0x19);  
			       rtd_outl(0xb800a038,0x01);	
				udelay(20);   
			   	printk(" test  cvbs ntsc\n");
				//result=UART1_to_MAC(VDC_EQC,0);
				//if(result==FAILED)
				result=drvif_module_tve_test_vd_mode(TVE_PAL_I);
				if(result==_FAIL)
					printk(" test  cvbs ntsc ....fail\n");
			 break;
		}	
		if(result==FAILED)
			return FAILED;

	}
		return  SUCCESS;
	

/*
	drvif_module_tve_set_mode(TVE_PAL_I);
	rtd_outl(AV_CTRL_reg,0x19);  
*/
/*
	if(module_tve_vdc_PathSelect(TVE_PAL_I)!=_SUCCESS)
	return _FAIL;
*/	
	return _SUCCESS;
}


int QC_Verifier_TVE_TV(void)
{

	printk("tve qc verifer\n");
#if 1
	if(drvif_module_tve_test_case()==SUCCESS)
	{
		return _SUCCESS;

	}
	else
		return FAILED;	


#endif
#if 0
	if(drvif_module_tve_test_case()==SUCCESS)
	return _SUCCESS;
	else
	return FAILED;
#else

	return _SUCCESS;
#endif


}
