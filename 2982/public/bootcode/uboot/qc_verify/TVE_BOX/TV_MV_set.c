//#######################################################################################################
//
//  File Name:      MV_set.C
//  Description:    Microvision Copy Protection mode setting
//
//#######################################################################################################

#include "TVE_reg.h"
#include "qc_verify.h"
#include "TVE.h"
#include "crt_sys_reg.h"
//extern unsigned int *RGB_flag;
 
void MV_set(UINT32 RGB_mode, UINT32 mv_mode)
{
    switch(mv_mode)
	{
        //MV_525i_Type1========================================================================================================
        case 0:	
		//Macrovision Copy Protection for 525i Type 1	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x36)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x3a)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x11)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x4b)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x11)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x1)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x7)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1b)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1b)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x24)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x7)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0x0f8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x0)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x0)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x0f)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x0f)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x40)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x0a)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x5)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x4)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xff)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            	// 0xb8018300, dummy
                	rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                 	 TVE_MV_CTRL_mv_g_ebl(1)|
                                 	 TVE_MV_CTRL_mv_ebl(0)|
                                 	 TVE_MV_CTRL_write_data(0)); //N22  
		else //YUV mode
		    {
	            	// 0xb8018300, dummy
                	rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                 	 TVE_MV_CTRL_mv_g_ebl(0)|
                                 	 TVE_MV_CTRL_mv_ebl(0)|
                                 	 TVE_MV_CTRL_write_data(0)); //N22 
		    }
		break;

//MV_525i_Type2========================================================================================================
	case 1:	
		//Macrovision Copy Protection for 525i Type 2	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x3a)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x11)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x4b)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x11)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x1)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x7)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1b)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1b)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x24)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x7)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0x0f8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x0)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x0)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x0f)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x0f)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x60)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x0a)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x5)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x4)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xff)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
		    }
		break;					

//MV_525i_Type3========================================================================================================
	case 2:	
		//Macrovision Copy Protection for 525i Type 3	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x2e)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x15)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x43)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x15)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x5)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x2)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1b)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1b)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x24)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x7)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0x0f8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x0)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x0)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x0f)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x0f)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x50)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x0a)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x5)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x4)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xff)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
		    }		
		break;

//MV_525i_TestN01======================================================================================================
	case 3:	
		//Macrovision Copy Protection for 525i Test N01	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x2e)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x15)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x43)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x15)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x5)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x3)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x19)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1c)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x23)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0xf)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0x0f8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x7e)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x07)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x0f)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x0e)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x91)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x05)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0xf)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x3)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x2)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xc3)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(1)|
                                     TVE_MV_CTRL_write_data(1)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22 
		    }
		break;					

//MV_525i_TestN02======================================================================================================
	case 4:	
		//Macrovision Copy Protection for 525i Test N02	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x5e)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x2a)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x35)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x36)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x2)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x4)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x3)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x24)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x25)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x1d)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x36)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xb8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x6d)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0xcf)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x23)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x13)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x70)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x02)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x3)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0xa)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x0)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x5)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xc0)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22 
		    }
		break;

//MV_625i_TestP01======================================================================================================
	case 5:	
		//Macrovision Copy Protection for 625i Test P01	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x39)); //N1*2+5
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x22)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x4a)); //N3*2+6
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x22)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x2)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1c)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x3d)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x14)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x03)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xfe)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x01)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x54)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0xfe)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x7e)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x60)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x08)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x4)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x0)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x7)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0x55)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x1)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22 
		    }
		break;

//MV_625i_TestP02======================================================================================================
	case 6:	
		//Macrovision Copy Protection for 625i Test P02	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x3e)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x39)); //N1*2+5
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x22)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x5a)); //N3*2+6
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x22)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x2)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x3)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x23)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x12)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x2b)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x78)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xc6)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x1f)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x43)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x53)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0xa3)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0xf0)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x07)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0xc)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x3)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x2)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0x85)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22  
		else //YUV mode
		    {
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(1)); //N22 
		    }
		break;

//MV_PAL_Type123, PAL-N, PAL_NC========================================================================================
	case 7:	
		//Macrovision Copy Protection for 625i Type 123	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x36)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x39)); //N1*2+5
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x22)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x5a)); //N3*2+6
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x22)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x2)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1c)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x3d)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x14)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x03)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xfe)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x01)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x54)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0xfe)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x7e)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x40)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x08)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x4)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x0)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x7)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0x55)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x1)); //N21(MSB)
            
	        if(RGB_mode==0) //RGB mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(1)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22  
		else //YUV mode
	            // 0xb8018300, dummy
                    rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                     TVE_MV_CTRL_mv_g_ebl(0)|
                                     TVE_MV_CTRL_mv_ebl(0)|
                                     TVE_MV_CTRL_write_data(0)); //N22 
		break;

//MV_525p==============================================================================================================
	case 8:	
	        //0xb8018300
             rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                 TVE_MV_CTRL_mv_g_ebl(0)|
                                 TVE_MV_CTRL_mv_ebl(1)|
                                 TVE_MV_CTRL_write_data(1));
		// 0xb801813c	
		rtd_outl(TVE_MV_RD_reg, TVE_MV_RD_mv_rd(78125));
		// 0xb8018140	
		rtd_outl(TVE_MV_DN_reg, TVE_MV_DN_mv_dn(93750));
		// 0xb8018144
		rtd_outl(TVE_MV_RU_reg, TVE_MV_RU_mv_ru(78125));
		// 0xb8018148
		rtd_outl(TVE_MV_UP_reg, TVE_MV_UP_mv_up(406250));
		// 0xb8018138	
		rtd_outl(TVE_MV_LEN_reg, TVE_MV_LEN_write_en4(1)|
						 TVE_MV_LEN_mv_st_ps(137)|
						 TVE_MV_LEN_write_en3(1)|
						 TVE_MV_LEN_mv_ps_len(29)|
						 TVE_MV_LEN_write_en2(1)|
						 TVE_MV_LEN_mv_agc_len(39)|
						 TVE_MV_LEN_write_en1(1)|
						 TVE_MV_LEN_mv_blnk_len(17));
		// 0xb8018134	
		rtd_outl(TVE_MV_VPOS_reg, TVE_MV_VPOS_write_en2(1)|
						 TVE_MV_VPOS_mv_end_line(19)|
						 TVE_MV_VPOS_write_en1(1)|
						 TVE_MV_VPOS_mv_st_line(12));
		// 0xb801814c	
		rtd_outl(TVE_MV_LVL_reg, TVE_MV_LVL_write_en3(1)|
						 TVE_MV_LVL_mv_ru_dlt(15)|
						 TVE_MV_LVL_write_en2(1)|
						 TVE_MV_LVL_mv_rd_dlt(15)|
						 TVE_MV_LVL_write_en1(1)|
						 TVE_MV_LVL_mv_stn(3500));//3200

		break;

//MV_625p==============================================================================================================
	case 9:	
	        // 0xb8018130
                rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(0)|
                                   TVE_MV_CTRL_mv_g_ebl(0)|
                                   TVE_MV_CTRL_mv_ebl(1)|
                                   TVE_MV_CTRL_write_data(1));
		// 0xb801813c	
		rtd_outl(TVE_MV_RD_reg, TVE_MV_RD_mv_rd(78125));
		// 0xb8018140	
		rtd_outl(TVE_MV_DN_reg, TVE_MV_DN_mv_dn(93750));
		// 0xb8018144
		rtd_outl(TVE_MV_RU_reg, TVE_MV_RU_mv_ru(78125));
		// 0xb8018148
		rtd_outl(TVE_MV_UP_reg, TVE_MV_UP_mv_up(406250));
		// 0xb8018138	
		rtd_outl(TVE_MV_LEN_reg, TVE_MV_LEN_write_en4(1)|
						 TVE_MV_LEN_mv_st_ps(125)|
						 TVE_MV_LEN_write_en3(1)|
						 TVE_MV_LEN_mv_ps_len(29)|
						 TVE_MV_LEN_write_en2(1)|
						 TVE_MV_LEN_mv_agc_len(39)|
						 TVE_MV_LEN_write_en1(1)|
						 TVE_MV_LEN_mv_blnk_len(17));
		// 0xb8018134	
		rtd_outl(TVE_MV_VPOS_reg,TVE_MV_VPOS_write_en2(1)|
						 TVE_MV_VPOS_mv_end_line(12)|
						 TVE_MV_VPOS_write_en1(1)|
						 TVE_MV_VPOS_mv_st_line(5));
		// 0xb801814c	
		rtd_outl(TVE_MV_LVL_reg, TVE_MV_LVL_write_en3(1)|
						 TVE_MV_LVL_mv_ru_dlt(18)|
						 TVE_MV_LVL_write_en2(1)|
						 TVE_MV_LVL_mv_rd_dlt(18)|
						 TVE_MV_LVL_write_en1(1)|
						 TVE_MV_LVL_mv_stn(3500));//3200

		break;

//MV_625i_Typeip=======================================================================================================
	case 10: 
		//Macrovision Copy Protection for 625i Type 123	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x36)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x39)); //N1*2+5
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x22)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x5a)); //N3*2+6
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x22)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x5)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x2)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1c)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x3d)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x14)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x03)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xfe)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x01)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x54)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0xfe)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x7e)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x40)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x08)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x4)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x0)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x7)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0x55)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x1)); //N21(MSB)

		break;

//Microvision off======================================================================================================
	case 11:
		// 0xb8018920
		rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x0)); //N0,MV OFF
		break;										

//MV_PAL60_Type123=====================================================================================================
	case 12: 
		//Macrovision Copy Protection for PAL-60 Type 123	
	        // 0xb8018520 
	        rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x36)); //N0
	        // 0xb8018524 
	        rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x3a)); //N1*2
	        // 0xb8018528 
	        rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x11)); //N2
	        // 0xb801852c 
	        rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x4b)); //N3*2+1
	        // 0xb8018530 
	        rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x11)); //N4
	        // 0xb8018534 
	        rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x1)| //N5
	                         TVE_IP_MVCSSP_mvcsnum(0x7)| //N6
				 TVE_IP_MVCSSP_mvcsln(0x0)); //N7
	        // 0xb8018538 
	        rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1b)); //N8
	        // 0xb801853c 
	        rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1b)); //N9
	        // 0xb8018540 
	        rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x24)); //N10
	        // 0xb8018544 
	        rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x07)); //N11(MSB)
	        // 0xb8018548 
	        rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xf8)); //N11(LSB)
	        // 0xb801854c 
	        rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x0)); //N12(MSB)
	        // 0xb8018550 
	        rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x0)); //N12(LSB)
	        // 0xb8018554 
	        rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0x1e)); //N13
	        // 0xb8018558 
	        rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0x1e)); //N14
	        // 0xb801855c 
	        rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x40)); //N15
	        // 0xb8018560 
	        rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0x0a)| //N17
				 TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
	        // 0xb8018564 
	        rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x5)| //N19
		       		 TVE_IP_MVPBZ3_mvpadvbsen(0x1)| //N16
		       		 TVE_IP_MVPBZ3_mvpzninvrt(0x4)); //N20
	        // 0xb8018568 
	        rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xff)); //N21(LSB)
	        // 0xb801856c 
	        rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x3)); //N21(MSB)
            
/*	        if(RGB_mode==0) //RGB mode
	            // 0xb8018130
                rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                 TVE_MV_CTRL_mv_g_ebl(1)|
                                 TVE_MV_CTRL_mv_ebl(0)|
                                 TVE_MV_CTRL_write_data(0)); //N22  
		else //YUV mode
	            // 0xb8018130
                rtd_outl(TVE_MV_CTRL_reg, TVE_MV_CTRL_mv_rb_ebl(1)|
                                 TVE_MV_CTRL_mv_g_ebl(0)|
                                 TVE_MV_CTRL_mv_ebl(0)|
                                 TVE_MV_CTRL_write_data(0)); //N22 
*/
		break;

//=====================================================================================================================
	default:
		// 0xb8018920
		rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x0)); //N0,MV OFF
		break;		
    } //switch(mv_mode)
    rtd_outl(0xa1001004,mv_mode);
}
