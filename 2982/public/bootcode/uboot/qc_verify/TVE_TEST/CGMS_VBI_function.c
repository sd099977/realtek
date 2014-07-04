#include "TVE_reg.h"
#include "qc_verify.h"
#include "TVE.h"
#include "crt_sys_reg.h"
void	CGMS_enable(UINT32 mode)
{
	//UINT32	cgms_data = 0xaaaaa;
	   UINT32	       cgms_data = 0x12abc;
//            mode = 1; // NTSC-M/525i
//            mode = 2; // 525p-700
//            mode = 3; // PAL-B/625i
//            mode = 4; // 625p
//            mode = 5; // 720p_60
//            mode = 6; // 1080_50i
//            mode = 7; // 1080_60i
//            mode = 8;
//            mode = 9; // NTSC_J
//            mode = 10; // NTSC_443
//            mode = 11; // PAL_M
//            mode = 12; // PAL_N
//            mode = 13; // PAL_60
//            mode = 14; // PAL_CN
//            mode = 15; // 1080_50p
//            mode = 16; // 1080_60p
//            mode = 17; // 525p-714
//            mode = 18; // 1080_24p
//            mode = 19;
//            mode = 20; // 720p_50
	//disable CGMS type A
	rtd_outl(TVE_CGMS_CTRL_reg,
	                 TVE_CGMS_CTRL_write_en3(1)|TVE_CGMS_CTRL_cgms_i_ebl(0)|
	                 TVE_CGMS_CTRL_write_en2(1)|TVE_CGMS_CTRL_cgms_p_ebl(0)|
	                 TVE_CGMS_CTRL_write_en1(1)|TVE_CGMS_CTRL_cgms_data(cgms_data));
  //0xb8018310
  rtd_outl(TVE_CGMS_CTRL1_reg, TVE_CGMS_CTRL1_cgms_data(cgms_data));
	//disable CGMS type B
	rtd_outl(TVE_CGMS_P2_VPOS_reg,
	  	   					 TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(0)|
	   							 TVE_CGMS_P2_VPOS_write_en2(0) | TVE_CGMS_P2_VPOS_cgms_p2_vpos2(0)|
	   							 TVE_CGMS_P2_VPOS_write_en1(0) | TVE_CGMS_P2_VPOS_cgms_p2_vpos1(0));
	switch(mode)
	{
		case	1:	// NTSC-M/525i
		case	9: 	// NTSC_J     
		case	10:	// NTSC_443  
        //0xb8018164
        rtd_outl(TVE_CGMS_I_VPOS_reg,
                         TVE_CGMS_I_VPOS_write_en2(1)|TVE_CGMS_I_VPOS_cgms_i_vpos1(19)|
                         TVE_CGMS_I_VPOS_write_en1(1)|TVE_CGMS_I_VPOS_cgms_i_vpos2(282));
        //0xb801816c
        rtd_outl(TVE_CGMS_I_HPOS_reg,
                         TVE_CGMS_I_HPOS_write_en2(1)|TVE_CGMS_I_HPOS_cgms_i_hst(167)|
                         TVE_CGMS_I_HPOS_write_en1(1)|TVE_CGMS_I_HPOS_cgms_i_len(59));
/*
        //0xb8018168
        rtd_outl(TVE_CGMS_P_VPOS_reg,
                         TVE_CGMS_P_VPOS_write_en2(1)|TVE_CGMS_P_VPOS_cgms_p_vpos1(40)|
                         TVE_CGMS_P_VPOS_write_en1(1)|TVE_CGMS_P_VPOS_cgms_p_vpos2(40));
        //0xb801817c
        rtd_outl(TVE_CGMS_P_HPOS_reg,
                         TVE_CGMS_P_HPOS_write_en3(1)|TVE_CGMS_P_HPOS_cgms_p_lvl(240)|
                         TVE_CGMS_P_HPOS_write_en2(1)|TVE_CGMS_P_HPOS_cgms_p_hst(169)|
                         TVE_CGMS_P_HPOS_write_en1(1)|TVE_CGMS_P_HPOS_cgms_p_len(25));
        //Component gain and offset control----------------
        //0xb8018104
        rtd_outl(TVE_BLNK_COEFF_reg,
 		                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0xd00)|
                         TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x1000));
*/
				//enable CGMS type A
				rtd_outl(TVE_CGMS_CTRL_reg,
	      			           TVE_CGMS_CTRL_write_en3(1)|TVE_CGMS_CTRL_cgms_i_ebl(1));		
	      break;
		case 2:		// 525p-700
        //0xb8018164
        rtd_outl(TVE_CGMS_I_VPOS_reg,
                         TVE_CGMS_I_VPOS_write_en2(1)|TVE_CGMS_I_VPOS_cgms_i_vpos1(19)|
                         TVE_CGMS_I_VPOS_write_en1(1)|TVE_CGMS_I_VPOS_cgms_i_vpos2(282));
        //0xb801816c
        rtd_outl(TVE_CGMS_I_HPOS_reg,
                         TVE_CGMS_I_HPOS_write_en2(1)|TVE_CGMS_I_HPOS_cgms_i_hst(167)|
                         TVE_CGMS_I_HPOS_write_en1(1)|TVE_CGMS_I_HPOS_cgms_i_len(59));
        //0xb8018168
        rtd_outl(TVE_CGMS_P_VPOS_reg,
                         TVE_CGMS_P_VPOS_write_en2(1)|TVE_CGMS_P_VPOS_cgms_p_vpos1(40)|
                         TVE_CGMS_P_VPOS_write_en1(1)|TVE_CGMS_P_VPOS_cgms_p_vpos2(40));
        //0xb801817c
        rtd_outl(TVE_CGMS_P_HPOS_reg,
                         TVE_CGMS_P_HPOS_write_en3(1)|TVE_CGMS_P_HPOS_cgms_p_lvl(240)|
                         TVE_CGMS_P_HPOS_write_en2(1)|TVE_CGMS_P_HPOS_cgms_p_hst(169)|
                         TVE_CGMS_P_HPOS_write_en1(1)|TVE_CGMS_P_HPOS_cgms_p_len(25));
        //Component gain and offset control----------------
        //0xb8018104
        rtd_outl(TVE_BLNK_COEFF_reg,
 		                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0xd00)|
                         TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x1000));
				//enable CGMS Type A
				rtd_outl(TVE_CGMS_CTRL_reg,
				 			           TVE_CGMS_CTRL_write_en3(1)|TVE_CGMS_CTRL_cgms_i_ebl(1)|
				      			     TVE_CGMS_CTRL_write_en2(1)|TVE_CGMS_CTRL_cgms_p_ebl(1)|
				          			 TVE_CGMS_CTRL_write_en1(0)|TVE_CGMS_CTRL_cgms_data(cgms_data));
				//Type B
				//disable typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
													TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(0)|
													TVE_CGMS_P2_VPOS_write_en2(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos2(39)|
													TVE_CGMS_P2_VPOS_write_en1(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos1(39));
				rtd_outl(TVE_CGMS_P2_HPOS_reg,
													TVE_CGMS_P2_HPOS_write_en3(1) | TVE_CGMS_P2_HPOS_cgms_p2_lvl(240)|
													TVE_CGMS_P2_HPOS_write_en2(1) | TVE_CGMS_P2_HPOS_cgms_p2_hst(171)|
													TVE_CGMS_P2_HPOS_write_en1(1) | TVE_CGMS_P2_HPOS_cgms_p2_len(3));
				rtd_outl(TVE_CGMS_B_HDR_reg,
													TVE_CGMS_B_HDR_cgms_hdr(0x14));
				rtd_outl(TVE_CGMS_B_DATA_0_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_1_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_2_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_3_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				//enable CGMS typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
												 TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(1));
				break;
		case 20:	// 720p_50
	  case 5:		// 720p_60
				//Type A
        //0xb8018164
        rtd_outl(TVE_CGMS_I_VPOS_reg,
                         TVE_CGMS_I_VPOS_write_en2(1)|TVE_CGMS_I_VPOS_cgms_i_vpos1(19)|
                         TVE_CGMS_I_VPOS_write_en1(1)|TVE_CGMS_I_VPOS_cgms_i_vpos2(282));
        //0xb8018168
        rtd_outl(TVE_CGMS_P_VPOS_reg,
                         TVE_CGMS_P_VPOS_write_en2(1)|TVE_CGMS_P_VPOS_cgms_p_vpos2(23)|
                         TVE_CGMS_P_VPOS_write_en1(1)|TVE_CGMS_P_VPOS_cgms_p_vpos1(23));
        //0xb801816c
        rtd_outl(TVE_CGMS_I_HPOS_reg,
                         TVE_CGMS_I_HPOS_write_en2(1)|TVE_CGMS_I_HPOS_cgms_i_hst(170)|
                         TVE_CGMS_I_HPOS_write_en1(1)|TVE_CGMS_I_HPOS_cgms_i_len(59));
        //0xb8018170
        rtd_outl(TVE_CGMS_P_HPOS_reg,
                         TVE_CGMS_P_HPOS_write_en3(1)|TVE_CGMS_P_HPOS_cgms_p_lvl(240)|
                         TVE_CGMS_P_HPOS_write_en2(1)|TVE_CGMS_P_HPOS_cgms_p_hst(340)|
                         TVE_CGMS_P_HPOS_write_en1(1)|TVE_CGMS_P_HPOS_cgms_p_len(57));
        //Component Gain and Offset Control-----------------------------------------------
        //0xb8018104
        rtd_outl(TVE_BLNK_COEFF_reg,
                         TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0xd00)|
                         TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x1000));
				//enable CGMS Type A
				rtd_outl(TVE_CGMS_CTRL_reg,
				 			           TVE_CGMS_CTRL_write_en3(1)|TVE_CGMS_CTRL_cgms_i_ebl(1)|
				      			     TVE_CGMS_CTRL_write_en2(1)|TVE_CGMS_CTRL_cgms_p_ebl(1)|
				          			 TVE_CGMS_CTRL_write_en1(0)|TVE_CGMS_CTRL_cgms_data(cgms_data));
				//Type B
				//disable typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
													TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(0)|
													TVE_CGMS_P2_VPOS_write_en2(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos2(22)|
													TVE_CGMS_P2_VPOS_write_en1(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos1(22));
				rtd_outl(TVE_CGMS_P2_HPOS_reg,
													TVE_CGMS_P2_HPOS_write_en3(1) | TVE_CGMS_P2_HPOS_cgms_p2_lvl(240)|
													TVE_CGMS_P2_HPOS_write_en2(1) | TVE_CGMS_P2_HPOS_cgms_p2_hst(340)|
													TVE_CGMS_P2_HPOS_write_en1(1) | TVE_CGMS_P2_HPOS_cgms_p2_len(7));
				rtd_outl(TVE_CGMS_B_HDR_reg,
													TVE_CGMS_B_HDR_cgms_hdr(0x14));
				rtd_outl(TVE_CGMS_B_DATA_0_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_1_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_2_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_3_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				//enable CGMS typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
												 TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(1));
	      break;				
		case	6:	//1080_50i
		case	7:	//1080_60i
				//Type A
        //0xb8018164
        rtd_outl(TVE_CGMS_I_VPOS_reg,
                         TVE_CGMS_I_VPOS_write_en2(1)|TVE_CGMS_I_VPOS_cgms_i_vpos1(19)|
                         TVE_CGMS_I_VPOS_write_en1(1)|TVE_CGMS_I_VPOS_cgms_i_vpos2(282));
        //0xb8018168
        rtd_outl(TVE_CGMS_P_VPOS_reg,
                         TVE_CGMS_P_VPOS_write_en2(1)|TVE_CGMS_P_VPOS_cgms_p_vpos1(18)|
                         TVE_CGMS_P_VPOS_write_en1(1)|TVE_CGMS_P_VPOS_cgms_p_vpos2(581));
        //0xb801816c
        rtd_outl(TVE_CGMS_I_HPOS_reg,
                         TVE_CGMS_I_HPOS_write_en2(1)|TVE_CGMS_I_HPOS_cgms_i_hst(170)|
                         TVE_CGMS_I_HPOS_write_en1(1)|TVE_CGMS_I_HPOS_cgms_i_len(59));
        //0xb8018170
        rtd_outl(TVE_CGMS_P_HPOS_reg,
                         TVE_CGMS_P_HPOS_write_en3(1)|TVE_CGMS_P_HPOS_cgms_p_lvl(240)|
                         TVE_CGMS_P_HPOS_write_en2(1)|TVE_CGMS_P_HPOS_cgms_p_hst(376)|
                         TVE_CGMS_P_HPOS_write_en1(1)|TVE_CGMS_P_HPOS_cgms_p_len(76));
        //Component Gain and Offset Control-----------------------------------------------
        // 0xb8018104
        rtd_outl(TVE_BLNK_COEFF_reg,
                         TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0xd00)|
                         TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x1000));
				//enable CGMS Type A
				rtd_outl(TVE_CGMS_CTRL_reg,
				 			           TVE_CGMS_CTRL_write_en3(1)|TVE_CGMS_CTRL_cgms_i_ebl(1)|
				      			     TVE_CGMS_CTRL_write_en2(1)|TVE_CGMS_CTRL_cgms_p_ebl(1)|
				          			 TVE_CGMS_CTRL_write_en1(0)|TVE_CGMS_CTRL_cgms_data(cgms_data));
				//Type B
				//disable typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
													TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(0)|
													TVE_CGMS_P2_VPOS_write_en2(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos2(17)|
													TVE_CGMS_P2_VPOS_write_en1(1) | TVE_CGMS_P2_VPOS_cgms_p2_vpos1(580));
				rtd_outl(TVE_CGMS_P2_HPOS_reg,
													TVE_CGMS_P2_HPOS_write_en3(1) | TVE_CGMS_P2_HPOS_cgms_p2_lvl(240)|
													TVE_CGMS_P2_HPOS_write_en2(1) | TVE_CGMS_P2_HPOS_cgms_p2_hst(376)|
													TVE_CGMS_P2_HPOS_write_en1(1) | TVE_CGMS_P2_HPOS_cgms_p2_len(9));
				rtd_outl(TVE_CGMS_B_HDR_reg,
													TVE_CGMS_B_HDR_cgms_hdr(0x14));
				rtd_outl(TVE_CGMS_B_DATA_0_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_1_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_2_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				rtd_outl(TVE_CGMS_B_DATA_3_reg,
													TVE_CGMS_B_DATA_cgms_data(0xaaaaaaaa));
				//enable CGMS typeB
				rtd_outl(TVE_CGMS_P2_VPOS_reg,
												 TVE_CGMS_P2_VPOS_write_en3(1) | TVE_CGMS_P2_VPOS_cgms_p_b_ebl(1));
	      break;				
		default:	break;
	}

	return;
}