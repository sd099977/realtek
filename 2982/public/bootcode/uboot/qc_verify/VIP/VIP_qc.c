#include <qc_verify_common.h>



#include <qc_verify.h>
#include "VIP_qc.h"

#include "../include/rbusTypes.h"
#include "../include/rbusVgipReg.h"
#include "../include/rbusVgip_ptgReg.h"
#include "../include/rbusScaledownReg.h"
#include "../include/rbusSD_DitherReg.h"
#include "../include/rbusDiReg.h"
#include "../include/rbusScaleupReg.h"
#include "../include/rbusColor_icmReg.h"
#include "../include/rbusDitherReg.h"
#include "../include/rbusColor_sharpReg.h"
#include "../include/rbusDFILTERReg.h"
#include "../include/rbusD_2d_to_3dReg.h"
#include "../include/rbusGammaReg.h"
#include "../include/rbusRgb2yuvReg.h"
#include "../include/rbusNrReg.h"
#include "../include/rbusColor_dccReg.h"
#include "../include/rbusColorReg.h"


//#ifndef udelay
//#define udelay(x) sys_wait_us(x)
//#endif

#ifndef rtdf_setBits
#define rtdf_setBits(offset, Mask) rtd_outl(offset, (rtd_inl(offset) |Mask))
#endif
#ifndef rtdf_clearBits
#define rtdf_clearBits(offset, Mask) rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#endif


#define UINT32 unsigned int
#define UINT8 unsigned char
#define PASS 0
#define FAIL 1
#define main 0
#define sub 1
#define _CHANNEL1 0


typedef	struct __CRC
{
		UINT32 VGIP;
		UINT32 RGB2YUV;
		UINT32 Peaking;
		UINT32 UZD;
		UINT32 MEM;
		UINT32 UZU;
		UINT32 VIVIC;
		UINT32 Dither;
		UINT32 OD;

		UINT32 VGIP1;
		UINT32 HSD1;
		UINT32 DI;
		UINT32 UZD1;
		UINT32 MEM1;
		UINT32 UZU1;
		UINT32 SHP1;
		UINT32 ICM1;

		struct  __GIBI
		{
			UINT32 Ch1;
			UINT32 Ch2;
			UINT32 Ch3;
			UINT32 Ch4;
		} GIBI;
} CRC;

#if 1
void module_VIP_bringup_script()
{
    printk("--case2_ipg1080i_fs_fhd---\n");

    //#include "MAC2_176_demo borad_Panel_Power_Backlight_Control.tbl"
	//udelay(100);

   	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000014, 0x1effffe7, 0x00000000);// disable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00000000);// hold TVSB1~3,APLL_ADC,I/M/D domain reset
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00007016);// release TVSB1~3,APLL_ADC,I/M/D domain reset
	udelay(8000);
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock


    //#include "case4_ipg1080i_fs_fhd/0702_mac2_crt_405.tbl"
    //        udelay(100);
    #include "case2_ipg1080i_fs_fhd.tbl"
/*
	#include "case4_ipg1080i_fs_fhd/ipg_1080i.tbl"
    udelay(100000);
    #include "case4_ipg1080i_fs_fhd/apll_ipg1080i.tbl"
    		udelay(2000);
    #include "case4_ipg1080i_fs_fhd/sp_ipg.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/vgip_ch1_ipg_1080i.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/di_en_ch1_1080i_2d.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/m_ch1_frc_1080i10b444.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/uzu_main_444_bypass1080i.tbl"
    		udelay(50);
    //--
    #include "case4_ipg1080i_fs_fhd/DPLL_297MHz.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/dtg_fhd_fs.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/mtg_fhd.tbl"
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/ivs2dvs_1080i_fhd.tbl"		// ivs2dvs delay for ipg1080p to FHD
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/m_ch1_frc_to_fs.tbl"			// mdomain change to fs mode
    		udelay(50);
    #include "case4_ipg1080i_fs_fhd/LVDS_FHD_1Seg_2Port.tbl"		// SFG, PIF, TX_PHY
    		udelay(50);
*/
    //rtd_outl(0xb800DB40, 0x02800202);	//HDMI Bandgap Enable


}
#endif


void drvif_color_digital_filter_set(UINT8 Access, UINT8 Offset, UINT8 Div, UINT8 Enable, UINT8 Display)
{

	if( Display == main)
	{
		ich1_dfilter_ph_smr_pring_RBUS ich1_dfilter_ph_smr_pring_RBUS_reg ;
		ich1_dfilter_nring_mis_nos_ypbpr_RBUS ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg ;

		ich1_dfilter_ph_smr_pring_RBUS_reg.regValue = rtd_inl(DFILTER_ICH1_DFILTER_PH_SMR_PRING_VADDR);
		ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.regValue = rtd_inl(DFILTER_ICH1_DFILTER_NRING_MIS_NOS_YPBPR_VADDR);

		switch(Access)
		{
			case _YPBPR_ACCESS_PORT:
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_y_en =0x1;
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_pb_en =0x1;
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_pr_en =0x1;
				break;
			case _PHASE_ACCESS_PORT:
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_ph_en = Enable;
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_thd_ph = Offset;
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_ph_div = Div;
				break;
			case _NEG_SMEAR_ACCESS_PORT:
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_nsmr_en= Enable;
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_thd_nsmr= Offset;
				ich1_dfilter_ph_smr_pring_RBUS_reg.ch1_nsmr_div = Div;
				break;
			case _MISMATCH_ACCESS_PORT:
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_mis_en= Enable;
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_thd_mis= Offset;
				break;
			case _NOISE_REDUCTION_PORT:
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_nos_en= Enable;
				ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch1_thd_nos= Offset;
				break;

		}

		rtd_outl(DFILTER_ICH1_DFILTER_PH_SMR_PRING_VADDR, ich1_dfilter_ph_smr_pring_RBUS_reg.regValue);
		rtd_outl(DFILTER_ICH1_DFILTER_NRING_MIS_NOS_YPBPR_VADDR, ich1_dfilter_nring_mis_nos_ypbpr_RBUS_reg.regValue);

	}
	else
	{
	///*	sub
		ich2_dfilter_ph_smr_pring_RBUS ich2_dfilter_ph_smr_pring_RBUS_reg ;
		ich2_dfilter_nring_mis_nos_ypbpr_RBUS ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg ;

		ich2_dfilter_ph_smr_pring_RBUS_reg.regValue = rtd_inl(DFILTER_ICH2_DFILTER_PH_SMR_PRING_VADDR);
		ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.regValue = rtd_inl(DFILTER_ICH2_DFILTER_NRING_MIS_NOS_YPBPR_VADDR);

		switch(Access)
		{
			case _YPBPR_ACCESS_PORT:
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_y_en =0x1;
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_pb_en =0x1;
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_pr_en =0x1;
				break;
			case _PHASE_ACCESS_PORT:
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_ph_en = Enable;
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_thd_ph = Offset;
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_ph_div = Div;
				break;
			case _NEG_SMEAR_ACCESS_PORT:
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_nsmr_en= Enable;
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_thd_nsmr= Offset;
				ich2_dfilter_ph_smr_pring_RBUS_reg.ch2_nsmr_div = Div;
				break;
			case _MISMATCH_ACCESS_PORT:
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_mis_en= Enable;
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_thd_mis= Offset;
				break;
			case _NOISE_REDUCTION_PORT:
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_nos_en= Enable;
				ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.ch2_thd_nos= Offset;
				break;

		}

		rtd_outl(DFILTER_ICH2_DFILTER_PH_SMR_PRING_VADDR, ich2_dfilter_ph_smr_pring_RBUS_reg.regValue);
		rtd_outl(DFILTER_ICH2_DFILTER_NRING_MIS_NOS_YPBPR_VADDR, ich2_dfilter_nring_mis_nos_ypbpr_RBUS_reg.regValue);
		//*/
	}
 }


void drvif_color_digital_filter_config(UINT8 display, UINT8 Enable)
{
	//sub
	rtdf_clearBits(DFILTER_ICH2_DFILTER_PH_SMR_PRING_VADDR, 0x01010101);
	rtdf_clearBits(DFILTER_ICH2_DFILTER_NRING_MIS_NOS_YPBPR_VADDR, 0x00771101);

	if(display == main)
	{
		drvif_color_digital_filter_set(_PHASE_ACCESS_PORT, _PHASE_THD_0, _DIV_VALUE_2, Enable,main);
		drvif_color_digital_filter_set(_NEG_SMEAR_ACCESS_PORT, _SMEAR_RING_THD_4, _DIV_VALUE_1, Enable,main);
		drvif_color_digital_filter_set(_MISMATCH_ACCESS_PORT, _MISMATCH_THD_0, _DIV_VALUE_0, Enable,main);
		drvif_color_digital_filter_set(_NOISE_REDUCTION_PORT, 	_NOISE_REDUCTION_THD_7, _DIV_VALUE_0, Enable,main);

		drvif_color_digital_filter_set(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, Enable,main);
	}
	else
	{
///*		// sub
		drvif_color_digital_filter_set(_PHASE_ACCESS_PORT, _PHASE_THD_0, _DIV_VALUE_2, Enable, sub );
		drvif_color_digital_filter_set(_NEG_SMEAR_ACCESS_PORT, _SMEAR_RING_THD_4, _DIV_VALUE_1, Enable, sub );
		drvif_color_digital_filter_set(_MISMATCH_ACCESS_PORT, _MISMATCH_THD_0, _DIV_VALUE_0, Enable, sub );
		drvif_color_digital_filter_set(_NOISE_REDUCTION_PORT, 	_NOISE_REDUCTION_THD_7, _DIV_VALUE_0, Enable, sub );

		drvif_color_digital_filter_set(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, Enable, sub );
//		*/
	}
}

#if 0
UINT8 RTNR_QC(UINT32 oddCRC, UINT32 evenCRC)
{
	UINT8 RTNR_done_flag=0;
	UINT8 vsync_idx=0;
	UINT8 loop_idx=0;
	UINT32 temp_crc=0;
	static UINT8 init_cnt=10;

	im_di_rtnr_control_RBUS im_di_rtnr_control_reg;
	im_di_rtnr_new_control_RBUS im_di_rtnr_new_control_reg;
	im_di_rtnr_new_sobel_th_RBUS im_di_rtnr_new_sobel_th_reg;
	im_di_rtnr_new_snr_control_RBUS im_di_rtnr_new_snr_control_reg;
	im_di_rtnr_new_mask1_ctrl2_RBUS im_di_rtnr_new_mask1_ctrl2_reg;
	im_di_rtnr_new_mask2_ctrl2_RBUS im_di_rtnr_new_mask2_ctrl2_reg;
 	//im_di_rtnr_y_th_RBUS im_di_rtnr_y_th_reg;
	//im_di_rtnr_c_th_RBUS im_di_rtnr_c_th_reg;
	//im_di_rtnr_k_RBUS im_di_rtnr_k_reg;

	im_di_rtnr_control_reg.regValue = rtd_inl(DI_IM_DI_RTNR_CONTROL_VADDR);
	im_di_rtnr_new_control_reg.regValue = rtd_inl(DI_IM_DI_RTNR_NEW_CONTROL_VADDR);
	im_di_rtnr_new_sobel_th_reg.regValue = rtd_inl(DI_IM_DI_RTNR_NEW_SOBEL_TH_VADDR);
	//im_di_rtnr_new_snr_control_reg = rtd_inl(DI_IM_DI_RTNR_NEW_SNR_CONTROL_VADDR);
	im_di_rtnr_new_mask1_ctrl2_reg.regValue=rtd_inl(DI_IM_DI_RTNR_NEW_MASK1_CTRL2_VADDR);
	im_di_rtnr_new_mask2_ctrl2_reg.regValue=rtd_inl(DI_IM_DI_RTNR_NEW_MASK2_CTRL2_VADDR);
	//im_di_rtnr_y_th_reg.regValue = rtd_inl(DI_IM_DI_RTNR_Y_TH_VADDR);
	//im_di_rtnr_c_th_reg.regValue = rtd_inl(DI_IM_DI_RTNR_C_TH_VADDR);
	//im_di_rtnr_k_reg.regValue = rtd_inl(DI_IM_DI_RTNR_K_VADDR);

	//===============================================================
	//prepare to change pattern


	 im_di_rtnr_control_reg.cp_rtnr_mad_window = 0;

	if(_INTERLACE_MODE)
	{
		im_di_rtnr_control_reg.cp_rtnr_progressive = 0; //interlace
	}
	else
	{
		im_di_rtnr_control_reg.cp_rtnr_progressive = 1;//progressive
	}

	im_di_rtnr_control_reg.cp_rtnr_rounding_correction = 0;
	im_di_rtnr_control_reg.cp_rtnr_y_enable = 1;
	im_di_rtnr_control_reg.cp_rtnr_c_enable = 1;

	im_di_rtnr_new_control_reg.rtnr_new_method_en=1;
	im_di_rtnr_new_sobel_th_reg.rtnr_sobel_method=1;
	im_di_rtnr_new_mask1_ctrl2_reg.rtnr_mask1_en=1;
	im_di_rtnr_new_mask2_ctrl2_reg.rtnr_mask2_en=1;
	rtd_outl(DI_IM_DI_RTNR_CONTROL_VADDR, im_di_rtnr_control_reg.regValue);
	rtd_outl(DI_IM_DI_RTNR_NEW_CONTROL_VADDR,im_di_rtnr_new_control_reg.regValue);
	rtd_outl(DI_IM_DI_RTNR_NEW_SOBEL_TH_VADDR,im_di_rtnr_new_sobel_th_reg.regValue);
	rtd_outl(DI_IM_DI_RTNR_NEW_MASK1_CTRL2_VADDR,im_di_rtnr_new_mask1_ctrl2_reg.regValue);
	rtd_outl(DI_IM_DI_RTNR_NEW_MASK2_CTRL2_VADDR,im_di_rtnr_new_mask2_ctrl2_reg.regValue);

	ich1_RGB2YUV_CTRL_RBUS  ich1_RGB2YUV_CTRL_REG;
	ich1_RGB2YUV_CTRL_REG.regValue = rtd_inl(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR);
	ich1_RGB2YUV_CTRL_REG.sel_uv_off =  1;
	ich1_RGB2YUV_CTRL_REG.set_r_in_offset =  1;
	//===============================================================

	Rtnr_qc_set_crc();

	do
 	{
  		vsync_idx++;


		if(RTNR_done_flag!=0)
  		{
			 //===============================================================
			//QC done, back to original setting
			im_di_rtnr_control_reg.regValue = rtd_inl(DI_IM_DI_RTNR_CONTROL_VADDR);
			im_di_rtnr_control_reg.cp_rtnr_y_enable = 0;
			im_di_rtnr_control_reg.cp_rtnr_c_enable = 0;
			im_di_rtnr_control_reg.cp_rtnr_progressive = 0; //interlace
			rtd_outl(DI_IM_DI_RTNR_CONTROL_VADDR, im_di_rtnr_control_reg.regValue);


			ich1_RGB2YUV_CTRL_REG.regValue = rtd_inl(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR);
			ich1_RGB2YUV_CTRL_REG.sel_uv_off = 0;
			ich1_RGB2YUV_CTRL_REG.set_r_in_offset = 0;
			rtd_outl(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, ich1_RGB2YUV_CTRL_REG.regValue);
 			 //===============================================================

   			if (RTNR_done_flag==1)
				return(1);//pass
			if(RTNR_done_flag==2)
				return(0);//fail
		}


		temp_crc=0;
		Scaler_WaitForEvent(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);//ori

		if(vsync_idx ==1)
		{
			rtdf_setBits(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);
			rtdf_clearBits(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);
			do {
				if(rtd_inl(VGIP_VGIP_CHN1_STATUS_VADDR) & _BIT26) {
					rtd_outl(DI_IM_DI_RTNR_CONTROL_VADDR, im_di_rtnr_control_reg.regValue);
 					rtd_outl(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, ich1_RGB2YUV_CTRL_REG.regValue);
					break;
				}
			} while(1);
		}

		if(vsync_idx ==5)
  		{
  			ich1_uzd_CRC_CTRL_RBUS ich1_uzd_CRC_CTRL_reg;
			ich1_uzd_CRC_CTRL_reg.regValue = rtd_inl(SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR);
			ich1_uzd_CRC_CTRL_reg.start = 1;


   			//==============================================================
   			//change pattern and RTNR enable

			#if 0
 				Scaler_WaitForEvent(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);  //wait ivs end
			#else
				rtdf_setBits(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);
				rtdf_clearBits(VGIP_VGIP_CHN1_STATUS_VADDR, _BIT26);
				do {
					if(rtd_inl(VGIP_VGIP_CHN1_STATUS_VADDR) & _BIT26) {
						rtd_outl(SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR, ich1_uzd_CRC_CTRL_reg.regValue) ;  //start crc
						break;
					}
				} while(1);
			#endif


   			temp_crc=Rtnr_qc_read_crc();



   			if( (temp_crc == oddCRC ) ||(temp_crc == evenCRC ) )
			{
				RTNR_done_flag=1;
				//printk("[after] RTNR setting ==> crc = %x ==> [SUCCESS ! ] \n",temp_crc);
   			}
   			else
			{
    				if(init_cnt!=10)
    					{
    				printk("[after] RTNR setting ==> crc = %x ==> [test_FAIL ! ] \n",temp_crc);
    					}
				RTNR_done_flag=2;
				init_cnt--;
   			}

			//RTNR_done_flag=1; // 1:pass, 0: fail

 		}

  		loop_idx++;


		if(loop_idx==100)
			break;

	}while(1);

}
#endif

void drvif_color_set3Dithering(void)
{
	UINT32 dither_32BIT_DATA = 0;
	UINT16 ii, jj, kk, data_shift = 0;

	dithering_ctrl_RBUS	dithering_ctrl_reg;
	temporal_offset_RBUS	temporal_offset_reg;


	//printk("<<<<<<<<<<<<<<<<<<<<<<<<<Panel_Bit=%d<<<<<<<<<<<<<<<<<<<<<<<<<\n",Panel_Bit);

	for(ii = 0; ii < 3; ii++) // rgb order
	{

		for(jj = 0; jj < 16; jj++)
		{
			if((jj == 0) ||(jj == 4) || (jj == 8) || (jj == 12))
			{
				dither_32BIT_DATA = 0;
				data_shift = 0;
			}


			dither_32BIT_DATA += tDITHER_SEQUENCE[ii][jj] << data_shift ;
			data_shift += 8;

			if(jj == 3)
			{
				switch(ii)
				{
					case 0:// red
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_RED_00_07_VADDR, dither_32BIT_DATA);
							break;
					case 1:// green
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_GREEN_00_07_VADDR, dither_32BIT_DATA);
							break;
					case 2:// blue
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_BLUE_00_07_VADDR, dither_32BIT_DATA);
							break;
				}

			}

			if(jj == 7)
			{
				switch(ii)
				{
					case 0:// red
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_RED_08_15_VADDR, dither_32BIT_DATA);
							break;
					case 1:// green
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_GREEN_08_15_VADDR, dither_32BIT_DATA);
							break;
					case 2:// blue
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_BLUE_08_15_VADDR, dither_32BIT_DATA);
							break;
				}

			}
			if(jj == 11)
			{
				switch(ii)
				{
					case 0: // red
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_RED_16_23_VADDR, dither_32BIT_DATA);
							break;
					case 1: // green
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_GREEN_16_23_VADDR, dither_32BIT_DATA);
							break;
					case 2: // blue
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_BLUE_16_23_VADDR, dither_32BIT_DATA);
							break;
				}

			}
			if(jj == 15)
			{
				switch(ii)
				{
					case 0: // red
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_RED_24_31_VADDR,dither_32BIT_DATA);
							break;
					case 1: // green
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_GREEN_24_31_VADDR, dither_32BIT_DATA);
							break;
					case 2: // blue
							rtd_outl(DITHER_DITHERING_SEQUENCE_TABLE_BLUE_24_31_VADDR, dither_32BIT_DATA);
							break;
				}

			}

		}
	}

	for(ii = 0; ii < 3; ii++)
	{
		for(jj = 0; jj < 16; jj++)
		{
			dither_32BIT_DATA = 0;
			data_shift = 0;

			for(kk = 0; kk < 6; kk++)
 	                {
				dither_32BIT_DATA += (tDITHER_LUT[ii][jj][kk] >> (Panel_Bit*2)) << data_shift;
				data_shift += 6;
	                }

			switch(ii)
			{
				case 0: // red
						rtd_outl(DITHER_DITHERING_DITHER_TABLE_RED_00_VADDR+4*jj, dither_32BIT_DATA);
						break;
				case 1: // green
						rtd_outl(DITHER_DITHERING_DITHER_TABLE_GREEN_00_VADDR+4*jj, dither_32BIT_DATA);
						break;
				case 2: // blue
						rtd_outl(DITHER_DITHERING_DITHER_TABLE_BLUE_00_VADDR+4*jj, dither_32BIT_DATA);
						break;
			}
		}
	}


	dither_32BIT_DATA = 0;


	for(ii = 0; ii < 16; ii++)
	{
		dither_32BIT_DATA += tDITHER_TEMPORAL[ii] << (ii *2);
	}


	temporal_offset_reg.regValue = dither_32BIT_DATA;
	rtd_outl(DITHER_TEMPORAL_OFFSET_VADDR, temporal_offset_reg.regValue);

	dithering_ctrl_reg.regValue = rtd_inl(DITHER_DITHERING_CTRL_VADDR);
	dithering_ctrl_reg.regValue = 0;
	dithering_ctrl_reg.function_enable = 1;
	dithering_ctrl_reg.temporal_enable = 1;
	//dithering_ctrl_reg.temporal_enable = 0;
	rtd_outl(DITHER_DITHERING_CTRL_VADDR, dithering_ctrl_reg.regValue);


}


void drvif_color_Disable_3Dithering()
{
	rtdf_clearBits(0xb802c500, _BIT4);
	rtdf_clearBits(0xb802c500, _BIT5);
}

void I_SNR_setting(void)
{
    dch1_cp_ctrl_RBUS dch1_cp_ctrl_reg;
    dch1_spatial_weight_RBUS dch1_spatial_weight_reg;
    curve_mapping_ctrl_RBUS curve_mapping_ctrl_reg;
    new_lpf_nearby_ctrl_RBUS new_lpf_nearby_ctrl_reg;
    mosquito_ctrl_RBUS mosquito_ctrl_reg;

    dch1_cp_ctrl_reg.regValue = rtd_inl(NR_DCH1_CP_CTRL_VADDR);
    dch1_spatial_weight_reg.regValue = rtd_inl(NR_DCH1_SPATIAL_WEIGHT_VADDR);
    curve_mapping_ctrl_reg.regValue = rtd_inl(NR_CURVE_MAPPING_CTRL_VADDR);
    new_lpf_nearby_ctrl_reg.regValue = rtd_inl(NR_NEW_LPF_NEARBY_CTRL_VADDR);
    mosquito_ctrl_reg.regValue = rtd_inl(NR_MOSQUITO_CTRL_VADDR);

    dch1_cp_ctrl_reg.cp_spatialenabley=1;
    dch1_cp_ctrl_reg.cp_spatialenablec=1;
    dch1_spatial_weight_reg.cp_fixedweight1y=0;
    dch1_spatial_weight_reg.cp_fixedweight2y=0;
    dch1_spatial_weight_reg.cp_weight1y=8;
    dch1_spatial_weight_reg.cp_weight2y=8;
    dch1_spatial_weight_reg.cp_ringweighty=8;
    curve_mapping_ctrl_reg.curvemappingmode_en=1;
    new_lpf_nearby_ctrl_reg.modified_lpf_enable=1;
    mosquito_ctrl_reg.mosquito_detect_en=1;

    rtd_outl(NR_DCH1_CP_CTRL_VADDR,dch1_cp_ctrl_reg.regValue);
    rtd_outl(NR_DCH1_SPATIAL_WEIGHT_VADDR,dch1_spatial_weight_reg.regValue);
    rtd_outl(NR_CURVE_MAPPING_CTRL_VADDR,curve_mapping_ctrl_reg.regValue);
    rtd_outl(NR_NEW_LPF_NEARBY_CTRL_VADDR,new_lpf_nearby_ctrl_reg.regValue);
    rtd_outl(NR_MOSQUITO_CTRL_VADDR,mosquito_ctrl_reg.regValue);






}


void D_SUPK_and_VDCTI_Setting(void)
{
	//supk
	rtdf_setBits(SCALEUP_DM_UZU_PEAKING_CORING_VADDR, _BIT16);// b802_902c

	//vcti
	rtdf_setBits(SCALEUP_DM_MEM_CRC_CTRL_VADDR, _BIT4);  // b802_9034 VCTI_EN

	//USM
	rtdf_setBits(SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR, _BIT24);// b802_90c4
	rtdf_setBits(SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR, _BIT25);
	rtdf_setBits(SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR, _BIT26);
}

void D_2Dto3D_Setting(void)
{
	d_2d3d_control_RBUS d_2d3d_control_Reg;
	d_2d3d_shifter_RBUS d_2d3d_shifter_Reg;

	d_2d3d_control_Reg.regValue = rtd_inl(D_2D_TO_3D_D_2D3D_CONTROL_VADDR);
	d_2d3d_shifter_Reg.regValue = rtd_inl(D_2D_TO_3D_D_2D3D_SHIFTER_VADDR);

	d_2d3d_control_Reg.r_frame_shift_en = 1;
	d_2d3d_control_Reg.l_frame_shift_en = 1;
	d_2d3d_control_Reg.tilt_depth_en = 1;
	d_2d3d_shifter_Reg.shifter_offset = 0x60;

	rtd_outl(D_2D_TO_3D_D_2D3D_CONTROL_VADDR, d_2d3d_control_Reg.regValue);
	rtd_outl(D_2D_TO_3D_D_2D3D_SHIFTER_VADDR, d_2d3d_shifter_Reg.regValue);
}



void D_Sharpness_Setting(UINT8 channel)
{
	dm_peaking_filter_0_RBUS          dm_peaking_filter_0_reg;
	dm_peaking_filter_1_RBUS          dm_peaking_filter_1_reg;

	if(channel == main)
	{


		// filter
		dm_peaking_filter_0_reg.regValue = rtd_inl(COLOR_SHARP_DM_PEAKING_FILTER_0_VADDR);
		dm_peaking_filter_1_reg.regValue = rtd_inl(COLOR_SHARP_DM_PEAKING_FILTER_1_VADDR);
		dm_peaking_filter_0_reg.c0	= 0x10c;	//268
		dm_peaking_filter_0_reg.c1	= 0x00f;	//15;
		dm_peaking_filter_1_reg.c2	= 0xa7;	//-89;
		dm_peaking_filter_1_reg.c3	= 0x5a;	//-38;
		dm_peaking_filter_1_reg.c4	= 0x74;	//-12;
		dm_peaking_filter_1_reg.c5	= 0x36;	//-10;
		dm_peaking_filter_0_reg.sh_b0	= 1;
		dm_peaking_filter_0_reg.sh_b1	= 1;

		rtd_outl(COLOR_SHARP_DM_PEAKING_FILTER_0_VADDR, dm_peaking_filter_0_reg.regValue);
		rtd_outl(COLOR_SHARP_DM_PEAKING_FILTER_1_VADDR, dm_peaking_filter_1_reg.regValue);

		//cds
		rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_U_BOUND_0_VADDR, 0x70000000);

		// New in AT
		rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_V_BOUND_0_VADDR, _BIT24);		// CDS-conti
		rtdf_setBits(COLOR_SHARP_DM_PEAKING_EMF_OFFSET_VADDR, _BIT28);		// Weighting sum
		rtdf_setBits(COLOR_SHARP_DM_SKIPIR_CTRL1_VADDR, _BIT0);				// SKIPIR
		rtdf_setBits(COLOR_SHARP_DM_EMFMK2_CTRL_VADDR, _BIT0);				// EMF mk2 mode
		rtdf_setBits(COLOR_SHARP_DM_DNOISE_CTRL1_VADDR, _BIT0);				// De-noise

		// New in Darwin
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT25);				// pk+dlti
		rtdf_clearBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT24);			//pk+dlti
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT4);				//texpk
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT3);				//edgpk
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT2);				// edgext
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT1);				// tex+emf
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL3_VADDR,_BIT14);				// tex gain
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_RING_VADDR,_BIT0);				// dering
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR,_BIT25);				//
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR,_BIT3);				//
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR,_BIT2);				//
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR,_BIT1);				//
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR,_BIT0);				//
		rtdf_setBits(COLOR_SHARP_DM_SEGPK_VWSUM_VADDR,_BIT0);				//V_WtSum

		rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR,_BIT4);				//SHP_DLTI
		rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR,_BIT2);
		rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR,_BIT1);
		rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR,_BIT0);



	}
	else
	{
///*		//Mac2 no sub
		rtdf_setBits(COLOR_D_VC_GLOBAL_CTRL_VADDR, 0x80001000 );

		// filter
/*		ds_peaking_filter_0_reg.regValue = rtd_inl(COLOR_SHARP_DS_PEAKING_FILTER_0_VADDR);
		ds_peaking_filter_1_reg.regValue = rtd_inl(COLOR_SHARP_DS_PEAKING_FILTER_1_VADDR);
		ds_peaking_filter_0_reg.c0	= 0x10c;	//268
		ds_peaking_filter_0_reg.c1	= 0x00f;	//15;
		ds_peaking_filter_1_reg.c2	= 0xa7;	//-89;
		ds_peaking_filter_1_reg.c3	= 0x5a;	//-38;
		ds_peaking_filter_1_reg.c4	= 0x74;	//-12;
		ds_peaking_filter_1_reg.c5	= 0x36;	//-10;
		ds_peaking_filter_0_reg.sh_b0	= 1;
		ds_peaking_filter_0_reg.sh_b1	= 1;

		rtd_outl(COLOR_SHARP_DS_PEAKING_FILTER_0_VADDR, ds_peaking_filter_0_reg.regValue);
		rtd_outl(COLOR_SHARP_DS_PEAKING_FILTER_1_VADDR, ds_peaking_filter_1_reg.regValue);
*/
	}
}


void D_Gamma_Setting(UINT8 display, UINT8 Mode)
{
	gamma_ctrl_1_RBUS gamma_ctrl_1_REG;
	gamma_ctrl_2_RBUS gamma_ctrl_2_REG;

	if(Mode > 3) // added by Jerry, for reducing code size
		return;

	gamma_ctrl_1_REG.regValue = rtd_inl(GAMMA_GAMMA_CTRL_1_VADDR);
	gamma_ctrl_2_REG.regValue = rtd_inl(GAMMA_GAMMA_CTRL_2_VADDR);


	if(display  == main ) {

		gamma_ctrl_1_REG.gamma_ax_type_sel = _Gamma_Full;
		//Mac2 no sub, only one table
		gamma_ctrl_1_REG.gamma_ax_rw_sel = 1; // writing table

	}
	else {
	/*sub
		//gamma_ctrl_2_REG.sub_tab_sel = 0;	// disable sub gamma
		// remove "disable gamma" for PIP sub flash when TV scan channel start & end , 20071228 Jerry Wu
		gamma_ctrl_1_REG.gamma_ax_type_sel = _Gamma_Full;
		gamma_ctrl_1_REG.gamma_ax_tab_sel = 1; // tab-2
		gamma_ctrl_1_REG.gamma_ax_rw_sel = 1; // writing table
	*/

	}

	rtd_outl(GAMMA_GAMMA_CTRL_2_VADDR, gamma_ctrl_2_REG.regValue);
/*
	if(Mode != 0) {
		if(Mode == 1) {
			gamma_ctrl_1_REG.gamma_ax_ch_sel = 0;
			rtd_outl(GAMMA_GAMMA_CTRL_1_VADDR, gamma_ctrl_1_REG.regValue);
			drvif_color_colorwritegamma(tGAMMA_1_R);

		//	RTD_Log(LOGGER_INFO,"write green gamma \n");
			gamma_ctrl_1_REG.gamma_ax_ch_sel = 1;
			rtd_outl(GAMMA_GAMMA_CTRL_1_VADDR, gamma_ctrl_1_REG.regValue);
			drvif_color_colorwritegamma(tGAMMA_1_G);

		//	RTD_Log(LOGGER_INFO,"write blue gamma \n");
			gamma_ctrl_1_REG.gamma_ax_ch_sel = 2;
			rtd_outl(GAMMA_GAMMA_CTRL_1_VADDR, gamma_ctrl_1_REG.regValue);
			drvif_color_colorwritegamma(tGAMMA_1_B);
		}
	}*/

	if(Mode != 0) { // not bypass

		if(display  == main )
		{

			gamma_ctrl_1_REG.gamma_ax_rw_sel = 0; // writing table
			gamma_ctrl_2_REG.gamma_m_tab_sel = 1; // use tab-1
			//sub
			//gamma_ctrl_2_REG.gamma_overlap= 0; // use main as overlay
		}
		else
		{
			/* sub
			gamma_ctrl_1_REG.gamma_ax_rw_sel = 0; // disable writing table
			gamma_ctrl_2_REG.gamma_overlap = 1; // use sub as overlay
			gamma_ctrl_2_REG.gamma_s_tab_sel = 2; // use tab-2
			*/
		}


	} else { //  bypass
		if(display  == main )
		{
			gamma_ctrl_2_REG.gamma_m_tab_sel = 0; // use tab-1
			// sub
			//gamma_ctrl_2_REG.gamma_overlap = 0; // use main as overlay

		}
		else
		{
			/*  sub
			gamma_ctrl_2_REG.gamma_s_tab_sel = 0; // use tab-2
			gamma_ctrl_2_REG.gamma_overlap = 1; // use sub as overlay
			*/

		}


	}
	rtd_outl(GAMMA_GAMMA_CTRL_1_VADDR, gamma_ctrl_1_REG.regValue);//20071217 jason for high level (white changes to megenta)
	rtd_outl(GAMMA_GAMMA_CTRL_2_VADDR, gamma_ctrl_2_REG.regValue);
}


void drvif_color_Gamma_sRGB_setTable(void)
{
	// ### Gamma, invGamma, sRGB start
	int i,m;
	unsigned short Vid; // value of index and delta

	// ### Gamma

	rtd_outl(0xb802c108,0x00000000);//diable invGamma
	rtd_outl(0xb802c104,0x000000b1);//-->ch sel[5:4]

	for(i=0;i<512;i++)
	{
		if(i==256)
		{
			rtd_outl(0xb802c104,0x000000f1);//-->ch sel[5:4]
		}
		Vid = i<<19+ 0x404;
		rtd_outl(0xb802c100,Vid);
	}
	rtd_outl(0xb802c104,0x00000071);
	rtd_outl(0xb802c108,0x00000040);

	// ### InvGamma

	rtd_outl(0xb802c018,0x00000000);//diable invGamma
	rtd_outl(0xb802c014,0x000000b1);//-->ch sel[5:4] (tbl1: R=81,  G=91,  B=a1) (tbl2:  R=c1,  G=d1,  B=e1)
	for(i=0;i<512;i++)
	{
		if(i==256)
		{
			rtd_outl(0xb802c014,0x000000f1);//-->ch sel[5:4]
		}
		Vid = i<<21+ 0x1010;
		rtd_outl(0xb802c010,Vid);
	}
	rtd_outl(0xb802c014,0x00000071);
	rtd_outl(0xb802c018,0x00000040);

	// ### sRGB

	rtd_outl(0xb802c000,0x00000020);//tab_size_=64, Bypass the sRGB coeff 1 & 2 for main & sub channels in Reg. sRGB_CTRL
	// r channel
	for(i=0;i<128;i++)
	{
		if(i==0)
			rtd_outl(0xb802c004,0x00000004);//Table1, SRGB_RGB_SEL=1
		else if(i==64)
			rtd_outl(0xb802c004,0x00000006);//Table2, SRGB_RGB_SEL=1

		Vid = i<<17+ 0x20;
		rtd_outl(0xb802c00c,0x00000000);
		rtd_outl(0xb802c00c,0x00000000);
		rtd_outl(0xb802c00c,Vid);
	}
	// g channel
	for(i=0;i<128;i++)
	{
		if(i==0)
			rtd_outl(0xb802c004,0x00000008);//Table1, SRGB_RGB_SEL=2
		else if(i==64)
			rtd_outl(0xb802c004,0x00000006);//Table2, SRGB_RGB_SEL=1

		Vid = i<<17+ 0x20;
		rtd_outl(0xb802c00c,0x00000000);
		rtd_outl(0xb802c00c,Vid);
		rtd_outl(0xb802c00c,0x00000000);
	}
	// b channel
	for(i=0;i<128;i++)
	{
		if(i==0)
			rtd_outl(0xb802c004,0x0000000c);//Table1, SRGB_RGB_SEL=3
		else if(i==64)
			rtd_outl(0xb802c004,0x0000000e);//Table2, SRGB_RGB_SEL=3

		Vid = i<<17+ 0x20;
		rtd_outl(0xb802c00c,0x00000000);
		rtd_outl(0xb802c00c,0x00000000);
		rtd_outl(0xb802c00c,Vid);
	}

	rtd_outl(0xb802c004,0x00000000);// Disable Access
	rtd_outl(0xb802c000,0x00000001);// Control tab_size, overlap, tab_sel

	// ### Gamma, invGamma, sRGB end
}

UINT32 VGIP_CRC_En(UINT8 ch)
{
	int k=0;
	if (ch == main)
	{
		//rtdf_setBits(VGIP_VGIP_CHN1_CTRL_VADDR, _BIT25);	// enable interrupt
		while(k<20)
		{
			rtdf_clearBits(VGIP_ICH1_VGIP_CRC_CTRL_VADDR, _BIT1);	// one-time mode on main
			rtdf_setBits(VGIP_ICH1_VGIP_CRC_CTRL_VADDR, _BIT0);
			udelay(60000);

			if ((rtd_inl(VGIP_ICH1_VGIP_CRC_CTRL_VADDR) & _BIT0) == 0)
				return rtd_inl(VGIP_ICH1_VGIP_CRC_RESULT_VADDR);
			else
				k++;
		}
		return 0;
	}
	else if (ch == sub)
	{
		rtdf_setBits(VGIP_VGIP_CHN2_CTRL_VADDR, _BIT25);
		rtdf_clearBits(VGIP_ICH2_VGIP_CRC_CTRL_VADDR, _BIT1);	// one-time mode on sub
		rtdf_setBits(VGIP_ICH2_VGIP_CRC_CTRL_VADDR, _BIT0);
		udelay(60000);

		if ((rtd_inl(VGIP_ICH2_VGIP_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(VGIP_ICH2_VGIP_CRC_RESULT_VADDR);
		else
			return 0;

	}
	else
		return 0;
}

UINT32 HSD_CRC_En(UINT8 ch)
{
	if (ch == main)
	{
		rtdf_clearBits(SCALEDOWN_ICH1_HSD_CRC_CTRL_VADDR, _BIT1);	// one-time mode on main
		rtdf_setBits(SCALEDOWN_ICH1_HSD_CRC_CTRL_VADDR, _BIT0);
		udelay(100000);

		if ((rtd_inl(SCALEDOWN_ICH1_HSD_CRC_CTRL_VADDR) & _BIT0) == 0)
		{
			return rtd_inl(SCALEDOWN_ICH1_HSD_CRC_RESULT_LEFT_VADDR);

		}
		else
		{
			return 0;
		}
	}
	else if (ch == sub)
	{
	//sub
		rtdf_clearBits(SCALEDOWN_ICH2_HSD_CRC_CTRL_VADDR, _BIT1);	// one-time mode on sub
		rtdf_setBits(SCALEDOWN_ICH2_HSD_CRC_CTRL_VADDR, _BIT0);
		udelay(60000);

		if ((rtd_inl(SCALEDOWN_ICH2_HSD_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(SCALEDOWN_ICH2_HSD_CRC_RESULT_VADDR);
		else
			return 0;

	}
	else
		return 0;
}

UINT32 DI_CRC_En()
{
	int k=0;


	while(k<20)
	{
		rtdf_clearBits(DI_IM_DI_SI_SUB_IN_AUTO_BALANCE_VADDR, _BIT17);	// one-time mode on main
		rtdf_setBits(DI_IM_DI_SI_SUB_IN_AUTO_BALANCE_VADDR, _BIT16);
		udelay(60000);

		if ((rtd_inl(DI_IM_DI_SI_SUB_IN_AUTO_BALANCE_VADDR) & _BIT16) == 0)
			return rtd_inl(DI_IM_DI_CRC_RESULT_VADDR);
		else
			k++;
	}
	return 0;

}

UINT32 VSD_CRC_En(UINT8 ch)
{
	if (ch == main)
	{
		rtdf_clearBits(SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR, _BIT1);	// one-time mode on main
		rtdf_setBits(SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR, _BIT0);
		udelay(90000);

		if ((rtd_inl(SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(SCALEDOWN_ICH1_UZD_CRC_RESULT_VADDR);
		else
			return 0;
	}
	else if (ch == sub)
	{
	//sub
		int k=0;
		while(k<20)
		{
			rtdf_clearBits(SCALEDOWN_ICH2_UZD_CRC_CTRL_VADDR, _BIT1);	// one-time mode on sub
			rtdf_setBits(SCALEDOWN_ICH2_UZD_CRC_CTRL_VADDR, _BIT0);
			udelay(90000);

			if ((rtd_inl(SCALEDOWN_ICH2_UZD_CRC_CTRL_VADDR) & _BIT0) == 0)
				return rtd_inl(SCALEDOWN_ICH2_UZD_CRC_RESULT_VADDR);
			else
				k++;
		}
		return 0;
	}
	else
		return 0;
}

UINT32 MEM_CRC_En(UINT8 ch)
{
	if (ch == main)
	{
		rtdf_clearBits(SCALEUP_DM_MEM_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(SCALEUP_DM_MEM_CRC_CTRL_VADDR, _BIT0);
		udelay(90000);

		if ((rtd_inl(SCALEUP_DM_MEM_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(SCALEUP_DM_MEM_CRC_RESULT_VADDR);
		else
			return 0;
	}
	else if (ch == sub)
	{
		//sub
		rtdf_clearBits(SCALEUP_DS_MEM_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(SCALEUP_DS_MEM_CRC_CTRL_VADDR, _BIT0);
		udelay(90000);

		if ((rtd_inl(SCALEUP_DS_MEM_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(SCALEUP_DS_MEM_CRC_RESULT_VADDR);
		else
			return 0;

	}
	else
		return 0;
}

UINT32 UZU_CRC_En(UINT8 ch)
{
	int k=0;
	if (ch == main)
	{
		while(k<20)
		{
			rtdf_clearBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT2);	// main
			rtdf_clearBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT1);	// one-time mode
			rtdf_setBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT0);
			udelay(90000);

			if ((rtd_inl(SCALEUP_D_UZU_CRC_CTRL_VADDR) & _BIT0) == 0)
				return rtd_inl(SCALEUP_D_UZU_CRC_RESULT_VADDR);
			else
				k++;
		}
		return 0;
	}
	else if (ch == sub)
	{
	//sub
		rtdf_setBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT2);		// sub
		rtdf_clearBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(SCALEUP_D_UZU_CRC_CTRL_VADDR, _BIT0);
		udelay(90000);

		if ((rtd_inl(SCALEUP_D_UZU_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(SCALEUP_D_UZU_CRC_RESULT_VADDR);
		else
			return 0;


	}
	else
		return 0;

}


UINT32 SHP_CRC_En(UINT8 ch)
{
 	//return 0;


	if (ch == main)
	{
		rtdf_clearBits(COLOR_SHARP_SHP_CRC_CTRL_VADDR, _BIT1); // one-time mode on main
		rtdf_setBits(COLOR_SHARP_SHP_CRC_CTRL_VADDR, _BIT0);
		udelay(200000);

		if ((rtd_inl(COLOR_SHARP_SHP_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(COLOR_SHARP_SHP_CRC_RESULT_VADDR );
		else
			return 0;
	}
	else if (ch == sub)
	{// Mac2 no sub
		rtdf_setBits(COLOR_SHARP_SHP_CRC_CTRL_VADDR, _BIT2); // sub
		rtdf_clearBits(COLOR_SHARP_SHP_CRC_CTRL_VADDR, _BIT1); // one-time mode on main
		rtdf_setBits(COLOR_SHARP_SHP_CRC_CTRL_VADDR, _BIT0);
		udelay(60000);

		if ((rtd_inl(COLOR_SHARP_SHP_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(COLOR_SHARP_SHP_CRC_RESULT_VADDR );
		else
			return 0;
	}
	else
		return 0;


}


UINT32 ICM_CRC_En(UINT8 ch)
{
	int k=0;
	if (ch == main)
	{
    	rtdf_clearBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT2);
		rtdf_clearBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT0);

		while(k<100)
		{
			udelay(200000);
			if ((rtd_inl(COLOR_ICM_ICM_CRC_CTRL_VADDR) & _BIT0) == 0)
				return rtd_inl(COLOR_ICM_ICM_CRC_RESULT_VADDR);
			else
				k++;
		}
		return 0;
	}
	else if (ch == sub)
	{// Mac2 no sub
		rtdf_setBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT2);		// sub
		rtdf_clearBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(COLOR_ICM_ICM_CRC_CTRL_VADDR, _BIT0);
		udelay(90000);

		if ((rtd_inl(COLOR_ICM_ICM_CRC_CTRL_VADDR) & _BIT0) == 0)
			return rtd_inl(COLOR_ICM_ICM_CRC_RESULT_VADDR);
		else
			return 0;
	}
	else
		return 0;
}


UINT32 Dither_CRC_En()
{

	int k=0;

	int tmp;

	while(k<20)
	{
		rtdf_clearBits(DITHER_DITHER_CRC_CTRL_VADDR, _BIT1);	// one-time mode
		rtdf_setBits(DITHER_DITHER_CRC_CTRL_VADDR, _BIT0);

		udelay(100000);


		tmp = rtd_inl(DITHER_DITHER_CRC_CTRL_VADDR) & _BIT0;
		if ( tmp == 0)
			return rtd_inl(DITHER_DITHER_CRC_RESULT_VADDR);
		else
			k++;
	}

	return 0;
}





void MAC_M_VIPSetting()
{
#if 1
//----------------------------------------------------------------------------------
// set by Jimmy, merging both settings
	printk("setting VIP register.....\n");
	//=============== I-domain settings ===============//

	//DI sub IP related
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT31|_BIT30);	//Film_sawtooth_choose
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT28);	//IP_Enable
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT27);	//di444to422Lowpass
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, 0xF87DE0);	//Enable bit 5~8, 10~14, 19~23

	//I_Digital_Filter
	drvif_color_digital_filter_config(_CHANNEL1,1);

	// rgb2yuv
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT10);	// Sel_2x_Gain
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT9);	// Sel_Y_Gain
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT6);	// Set_UV_out_offset
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT5);	// Set_R_In_offset
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT3);	// Sel_sign

	// I-domain 422to444
	rtdf_setBits(RGB2YUV_ICH1_422TO444_CTRL_VADDR, _BIT0);	// En_422to444
/*
	//UZD
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT11);	// VIDEO_COMP_EN
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT10);	// ODD_INV
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT1);	// V_ZOOM_EN
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT0);	// H_ZOOM_EN
*/
	// RTNR/New Intra/BTR/BER/Mpeg NR/Film/TNRXC
	rtdf_setBits(DI_IM_DI_RTNR_CONTROL_VADDR, _BIT30|_BIT29|_BIT28|_BIT1|_BIT0);
	rtdf_setBits(DI_IM_DI_RTNR_EDIFF_CONTROL_VADDR, _BIT1);	//CP_Temporal_edge_crct_en
	rtdf_setBits(DI_IM_DI_TNR_XC_CONTROL_VADDR, _BIT31);	//SET_SobelEdgeTypeEn
	rtdf_setBits(DI_IM_DI_HFD_CONTROL_VADDR, _BIT24|_BIT4);
	rtdf_setBits(DI_IM_DI_HFD_LINE_MOTION_COUNT_VADDR, _BIT31);
	rtdf_setBits(DI_IM_DI_HFD_MA_ERROR_RECOVERY_VADDR, _BIT28|_BIT1|_BIT0);
	rtdf_setBits(DI_IM_DI_NEW_INTRA_LOW_ANGLE_VADDR, _BIT0);	//NewIntraLowAngle_Enable
	rtdf_setBits(DI_IM_DI_INTRA_POST_PROCESS_VADDR, _BIT31|_BIT30|_BIT29|_BIT28|_BIT27|_BIT11);
	rtdf_setBits(DI_IM_DI_BTR_CONTROL_VADDR, _BIT0);	//BTR_BlendTemporalRecoveryEn
	rtdf_setBits(DI_IM_DI_BER_SPATIAL_CONTROL_VADDR, _BIT0);	//BER_BlendSpatialRecoveryEn
	rtdf_setBits(DI_IM_DI_BER_TEMPORAL_CONTROL_VADDR, _BIT0);	//BER_BlendTemporalRevoeryEn
	rtdf_setBits(DI_IM_DI_INTRA_L_CROSS_PAT_DET_CTL_VADDR, _BIT0);	//Intra_LPattern_Enable
	rtdf_setBits(DI_MPEGNR1_VADDR, _BIT1|_BIT0);	//CP_MpegEnable_Y_C, CP_MpegEnable_Y_Y
	rtdf_setBits(DI_IM_DI_PIB_CONTROL_VADDR, 0xFFFFF);	//Bit 0~19
	rtdf_setBits(DI_DI_P_FILM_CTRL0_VADDR, _BIT1|_BIT0);	//Prgfilm_32_en, Prgfilm_22_en
	rtdf_setBits(DI_IM_DI_LSB_RTNR_VADDR, _BIT0);	//LSB_RTNR_en
	rtdf_setBits(DI_IM_DI_FRAMESOBEL_STATISTIC_VADDR, _BIT9|_BIT8);	//HMC_dynamic_threshold_en, HMC_vector_delay_en
	rtdf_setBits(DI_TNRXC_MKII_CTRL_VADDR, _BIT0);	//TNRXC_MkII_en
	rtdf_setBits(DI_IM_DI_RTNR_K_DARK_VADDR, _BIT0);	//CP_Temporal_Y_Dark_K_en
	rtdf_setBits(DI_IM_DI_RTNR_EDIFF_ENABLE_VADDR, 0x7FFF);
	rtdf_setBits(DI_IM_DI_RTNR_NEW_CONTROL_VADDR, _BIT0);	//RTNR_New_Method_En
	rtdf_setBits(DI_IM_DI_PAN_DETECTION_CONTROL_1_VADDR, _BIT0);	//Pan_En
	rtdf_setBits(DI_IM_DI_FILM_NEW_FUNCTION_MAIN_VADDR, _BIT1|_BIT0);	//Fw_Film_en
	rtdf_setBits(DI_DI_SMD_CONTROL_CANDIDATELIST_VADDR, _BIT31);	//SMD_En
	rtdf_setBits(DI_IM_DI_RTNR_SC_VADDR, _BIT0);	//RTNR_New_Method_SC_En

	// SNR
    	I_SNR_setting();

	//I_MPEG_NR
	rtdf_setBits(0xb8023128,_BIT0); // hor MPEGNR en
	rtdf_setBits(0xb8024254,_BIT0); // Ver MPEGNR en

	//I-DLTI
	rtdf_setBits(0xb8023170, _BIT0|_BIT1|_BIT2|_BIT25);

	//I-DCTI
	rtdf_setBits(0xb8023118, _BIT31|_BIT0);

	//I-peaking
	rtdf_setBits(0xb8023100, _BIT26);

	//I Edge smooth
 	rtdf_setBits(0xb8025100,_BIT0);//enable

	//=============== D-domain settings ===============//

	// D-pattern gen set
	//rtd_outl(0xb8029000, 0x00000031);	// DPG Color Bar
	//rtd_outl(0xb8029074, 0x000000EF);	// DPG Color Width
	//rtd_outl(0xb8029028, 0x07800438);	// Input Size

	//D_ SUPK and VCTI and UnSharpMask
	D_SUPK_and_VDCTI_Setting();

	//vivid color
    	rtdf_setBits(0xb802a000,_BIT30);//vc en
	rtdf_setBits(0xb802a000,_BIT5);//egsm en
	rtdf_setBits(0xb802a000,_BIT4);//shp en
	rtdf_setBits(0xb802a000,_BIT3);//icm en
	rtdf_setBits(0xb802a000,_BIT2);//dcti en
	rtdf_setBits(0xb802a000,_BIT0);//dcc en

	//D_2Dto3D
	D_2Dto3D_Setting();

	// Sharpness/D-DLTI
	rtdf_setBits(COLOR_SHARP_DM_NR_SHP_CTRL_VADDR, _BIT13|_BIT11|_BIT9|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_MKIII_SHP_CTRL_VADDR, _BIT2|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_AUTO_SHP_DATA_VADDR, _BIT28);	//Auto Sharpness Enable
	rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_U_BOUND_0_VADDR, _BIT30|_BIT29|_BIT28);
	rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_V_BOUND_0_VADDR, _BIT24);	//Color Dependent Sharpness Continuity Enable
	rtdf_setBits(COLOR_SHARP_DM_PEAKING_EMF_OFFSET_VADDR, _BIT28);
	rtdf_setBits(COLOR_SHARP_DM_SKIPIR_CTRL1_VADDR, 0x1F);	// Bit 0~4 enable
	rtdf_setBits(COLOR_SHARP_DM_DNOISE_CTRL1_VADDR, _BIT1|_BIT0);	//DNoise_Gain_en, DNoise_LV_en
	rtdf_clearBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR, _BIT24);	//enhance_mode=2;
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR, _BIT25|_BIT4|_BIT3|_BIT2);	//texpk_en, edgpk_en, edgext_en
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_RING_VADDR, _BIT0);	//dering_en
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR, _BIT3|_BIT2|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_VWSUM_VADDR, _BIT0);
	rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR, _BIT4|_BIT2|_BIT1|_BIT0);

	// D_DLTI/DCTI
    	rtdf_setBits(0xb802a68c,_BIT0);//dlti en
    	rtd_outl(0xb802a00c, 0x0000AA76);//COLOR_DLCTI_DM_DLTI_OPTIONS_VADDR
	rtd_outl(0xb802a010, 0x0000001A);//COLOR_DLCTI_DM_DLTI_VALUE_VADDR
	rtd_outl(0xb802a01c, 0x00000001);//COLOR_DLCTI_DM_DCTI_OPTIONS_VADDR
	rtd_outl(0xb802a020, 0x0000002C);//COLOR_DLCTI_DM_DCTI_1ST_VALUE_VADDR
/*
	//UZU
	rtdf_setBits(SCALEUP_DM_UZU_CTRL_VADDR, _BIT9|_BIT1|_BIT0);
	rtdf_setBits(SCALEUP_DM_UZU_PEAKING_CORING_VADDR, _BIT16);	//supk_en
	rtdf_setBits(SCALEUP_DM_MEM_CRC_CTRL_VADDR, _BIT4);	//vcti_en
	rtdf_setBits(SCALEUP_DM_UZU_MAIN_V_PARTIAL_DROP_VADDR, _BIT21);	//VCTI_LOW_PASS_FILTER_EN
	rtdf_setBits(SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR, _BIT24);
	rtdf_setBits(SCALEUP_DM_UZU_V6CTRL_VADDR, _BIT0);	//V6-tap
*/
	//D_Sharpness
    	rtdf_setBits(0xb802a500,_BIT0);//en
   	D_Sharpness_Setting(main);
    	udelay(40000);

	//UV delay
	rtdf_setBits(0xb802a034, _BIT0);

	//DCC
	rtdf_setBits(COLOR_DCC_D_DCC_CTRL_VADDR, _BIT24);	//enable DCC
	rtdf_setBits(COLOR_DCC_D_DCC_SKIN_TONE_EN_VADDR, _BIT0);	//y_blending_en
/*
	//ICM
	rtdf_setBits(COLOR_ICM_DM_ICM_CTRL_VADDR, 0x7F);	// Bit 0~6 enable
	rtdf_setBits(COLOR_ICM_DM_SOFT_CLAMP_CTRL_VADDR, _BIT1|_BIT0);	// soft clamp
	rtdf_setBits(COLOR_ICM_D_AUTO_SAT_CTRL_VADDR, _BIT2);	//SAT_Enable
	rtdf_setBits(COLOR_ICM_ICM_AUTO_CTRL_VADDR, _BIT1);	//HUE_Enable
	rtdf_setBits(COLOR_ICM_DM_ADJ_BYITN_CTRL_VADDR, 0x7F7F);	// Enable bit 0~6, 8~14
	rtdf_setBits(COLOR_ICM_DM_SEG_SHY_ADJ_CTRL_VADDR, _BIT27|_BIT1|_BIT0);
	rtdf_setBits(COLOR_ICM_DM_ICM_MERGE_H_CM01_VADDR, 0x3f800);	// Enable bit 11~17
	rtdf_setBits(COLOR_ICM_DM_ICM_SI_CLIP_VADDR, _BIT31);	//SI_CLIP_EN
	printk("setting VIP register.....13\n");
*/
	//D_Edgesmooth
	rtdf_setBits(0xb802aa00,_BIT8);//Dir_LPF
	rtdf_setBits(0xb802aa14,_BIT28);//PostSHP

	//yuv2rgb
	rtdf_setBits(0xb802ac00, _BIT0);

	//Contrast/brightness
	rtdf_setBits(0xb802a800, _BIT0|_BIT1);

	//sRGB, Gamma, invGamma
	drvif_color_Gamma_sRGB_setTable();

	//OSD sharpness
	rtdf_setBits(0xb802ab00, _BIT1|_BIT0);
	rtdf_setBits(0xb802ab08, _BIT0);

	//Local dimming
	rtdf_setBits(0xb802c200, _BIT31);
	rtdf_setBits(0xb802c204, _BIT31);

	drvif_color_set3Dithering();
#endif

#if 0

// set by echang
	//=============== I-domain settings ===============//

	//DI sub IP related
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT31|_BIT30);	//Film_sawtooth_choose
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT28);	//IP_Enable
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, _BIT27);	//di444to422Lowpass
	rtdf_setBits(DI_IM_DI_CONTROL_VADDR, 0xF87DE0);	//Enable bit 5~8, 10~14, 19~23

	// rgb2yuv
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT10);	// Sel_2x_Gain
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT9);	// Sel_Y_Gain
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT6);	// Set_UV_out_offset
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT5);	// Set_R_In_offset
	rtdf_setBits(RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR, _BIT3);	// Sel_sign

	// I-domain 422to444
	rtdf_setBits(RGB2YUV_ICH1_422TO444_CTRL_VADDR, _BIT0);	// En_422to444
/*
	//UZD
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT11);	// VIDEO_COMP_EN
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT10);	// ODD_INV
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT1);	// V_ZOOM_EN
	rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR, _BIT0);	// H_ZOOM_EN
*/
	// RTNR/New Intra/BTR/BER/Mpeg NR/Film/TNRXC
	rtdf_setBits(DI_IM_DI_RTNR_CONTROL_VADDR, _BIT30|_BIT29|_BIT28|_BIT1|_BIT0);
	rtdf_setBits(DI_IM_DI_RTNR_EDIFF_CONTROL_VADDR, _BIT1);	//CP_Temporal_edge_crct_en
	rtdf_setBits(DI_IM_DI_TNR_XC_CONTROL_VADDR, _BIT31);	//SET_SobelEdgeTypeEn
	rtdf_setBits(DI_IM_DI_HFD_CONTROL_VADDR, _BIT24|_BIT4);
	rtdf_setBits(DI_IM_DI_HFD_LINE_MOTION_COUNT_VADDR, _BIT31);
	rtdf_setBits(DI_IM_DI_HFD_MA_ERROR_RECOVERY_VADDR, _BIT28|_BIT1|_BIT0);
	rtdf_setBits(DI_IM_DI_NEW_INTRA_LOW_ANGLE_VADDR, _BIT0);	//NewIntraLowAngle_Enable
	rtdf_setBits(DI_IM_DI_INTRA_POST_PROCESS_VADDR, _BIT31|_BIT30|_BIT29|_BIT28|_BIT27|_BIT11);
	rtdf_setBits(DI_IM_DI_BTR_CONTROL_VADDR, _BIT0);	//BTR_BlendTemporalRecoveryEn
	rtdf_setBits(DI_IM_DI_BER_SPATIAL_CONTROL_VADDR, _BIT0);	//BER_BlendSpatialRecoveryEn
	rtdf_setBits(DI_IM_DI_BER_TEMPORAL_CONTROL_VADDR, _BIT0);	//BER_BlendTemporalRevoeryEn
	rtdf_setBits(DI_IM_DI_INTRA_L_CROSS_PAT_DET_CTL_VADDR, _BIT0);	//Intra_LPattern_Enable
	rtdf_setBits(DI_MPEGNR1_VADDR, _BIT1|_BIT0);	//CP_MpegEnable_Y_C, CP_MpegEnable_Y_Y
	rtdf_setBits(DI_IM_DI_PIB_CONTROL_VADDR, 0xFFFFF);	//Bit 0~19
	rtdf_setBits(DI_DI_P_FILM_CTRL0_VADDR, _BIT1|_BIT0);	//Prgfilm_32_en, Prgfilm_22_en
	rtdf_setBits(DI_IM_DI_LSB_RTNR_VADDR, _BIT0);	//LSB_RTNR_en
	rtdf_setBits(DI_IM_DI_FRAMESOBEL_STATISTIC_VADDR, _BIT9|_BIT8);	//HMC_dynamic_threshold_en, HMC_vector_delay_en
	rtdf_setBits(DI_TNRXC_MKII_CTRL_VADDR, _BIT0);	//TNRXC_MkII_en
	rtdf_setBits(DI_IM_DI_RTNR_K_DARK_VADDR, _BIT0);	//CP_Temporal_Y_Dark_K_en
	rtdf_setBits(DI_IM_DI_RTNR_EDIFF_ENABLE_VADDR, 0x7FFF);
	rtdf_setBits(DI_IM_DI_RTNR_NEW_CONTROL_VADDR, _BIT0);	//RTNR_New_Method_En
	rtdf_setBits(DI_IM_DI_PAN_DETECTION_CONTROL_1_VADDR, _BIT0);	//Pan_En
	rtdf_setBits(DI_IM_DI_FILM_NEW_FUNCTION_MAIN_VADDR, _BIT1|_BIT0);	//Fw_Film_en
	rtdf_setBits(DI_DI_SMD_CONTROL_CANDIDATELIST_VADDR, _BIT31);	//SMD_En
	rtdf_setBits(DI_IM_DI_RTNR_SC_VADDR, _BIT0);	//RTNR_New_Method_SC_En

	// SNR
    I_SNR_setting();

	//I-peaking
	rtdf_setBits(0xb8023100, _BIT26);

	//I-DLTI
	rtdf_setBits(0xb8023170, _BIT0|_BIT1|_BIT2|_BIT25);

	//I-DCTI
	rtdf_setBits(0xb8023118, _BIT31|_BIT0);

	//I-new-DCTI
	rtdf_setBits(0xb80231f8, _BIT0);

	//=============== D-domain settings ===============//
	// Sharpness/D-DLTI
	rtdf_setBits(COLOR_SHARP_DM_NR_SHP_CTRL_VADDR, _BIT13|_BIT11|_BIT9|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_MKIII_SHP_CTRL_VADDR, _BIT2|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_AUTO_SHP_DATA_VADDR, _BIT28);	//Auto Sharpness Enable
	rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_U_BOUND_0_VADDR, _BIT30|_BIT29|_BIT28);
	rtdf_setBits(COLOR_SHARP_DM_CDS_CM1_V_BOUND_0_VADDR, _BIT24);	//Color Dependent Sharpness Continuity Enable
	rtdf_setBits(COLOR_SHARP_DM_PEAKING_EMF_OFFSET_VADDR, _BIT28);
	rtdf_setBits(COLOR_SHARP_DM_SKIPIR_CTRL1_VADDR, 0x1F);	// Bit 0~4 enable
	rtdf_setBits(COLOR_SHARP_DM_DNOISE_CTRL1_VADDR, _BIT1|_BIT0);	//DNoise_Gain_en, DNoise_LV_en
	rtdf_clearBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR, _BIT24);	//enhance_mode=2;
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_CTRL1_VADDR, _BIT25|_BIT4|_BIT3|_BIT2);	//texpk_en, edgpk_en, edgext_en
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_RING_VADDR, _BIT0);	//dering_en
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_VPK4_VADDR, _BIT3|_BIT2|_BIT1|_BIT0);
	rtdf_setBits(COLOR_SHARP_DM_SEGPK_VWSUM_VADDR, _BIT0);
	rtdf_setBits(COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR, _BIT4|_BIT2|_BIT1|_BIT0);
/*
	//UZU
	rtdf_setBits(SCALEUP_DM_UZU_CTRL_VADDR, _BIT9|_BIT1|_BIT0);
	rtdf_setBits(SCALEUP_DM_UZU_PEAKING_CORING_VADDR, _BIT16);	//supk_en
	rtdf_setBits(SCALEUP_DM_MEM_CRC_CTRL_VADDR, _BIT4);	//vcti_en
	rtdf_setBits(SCALEUP_DM_UZUMAIN_V_PARTIAL_DROP_VADDR, _BIT21);	//VCTI_LOW_PASS_FILTER_EN
	rtdf_setBits(SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR, _BIT24);
	rtdf_setBits(SCALEUP_DM_UZU_V6CTRL_VADDR, _BIT0);	//V6-tap
*/
	//UV delay
	rtdf_setBits(0xb802a034, _BIT0);

	//DCC
	rtdf_setBits(COLOR_DCC_D_DCC_CTRL_VADDR, _BIT24);	//enable DCC
	rtdf_setBits(COLOR_DCC_D_DCC_SKIN_TONE_EN_VADDR, _BIT0);	//y_blending_en

	//ICM

	rtdf_setBits(COLOR_ICM_DM_ICM_CTRL_VADDR, 0x7F);	// Bit 0~6 enable
	rtdf_setBits(COLOR_ICM_DM_SOFT_CLAMP_CTRL_VADDR, _BIT1|_BIT0);	// soft clamp
	rtdf_setBits(COLOR_ICM_D_AUTO_SAT_CTRL_VADDR, _BIT2);	//SAT_Enable
	rtdf_setBits(COLOR_ICM_ICM_AUTO_CTRL_VADDR, _BIT1);	//HUE_Enable
	rtdf_setBits(COLOR_ICM_DM_ADJ_BYITN_CTRL_VADDR, 0x7F7F);	// Enable bit 0~6, 8~14
	rtdf_setBits(COLOR_ICM_DM_SEG_SHY_ADJ_CTRL_VADDR, _BIT27|_BIT1|_BIT0);
	rtdf_setBits(COLOR_ICM_DM_ICM_MERGE_H_CM01_VADDR, 0x3f800);	// Enable bit 11~17
	rtdf_setBits(COLOR_ICM_DM_ICM_SI_CLIP_VADDR, _BIT31);	//SI_CLIP_EN

	//yuv2rgb
	rtdf_setBits(0xb802ac00, _BIT0);

	//Contrast/brightness
	rtdf_setBits(0xb802a800, _BIT0|_BIT1);

	//sRGB
	rtdf_setBits(0xb802c000, _BIT0);

	//Gamma
	rtdf_setBits(0xb802c108, _BIT6);

	//OSD sharpness
	rtdf_setBits(0xb802ab00, _BIT1|_BIT0);
	rtdf_setBits(0xb802ab08, _BIT0);

	//Local dimming
	rtdf_setBits(0xb802c200, _BIT31);
	rtdf_setBits(0xb802c204, _BIT31);

	//Dither
	//rtdf_setBits(DITHER_DITHERING_CTRL_VADDR, _BIT5|_BIT4);
	//rtdf_setBits(DITHER_DITHERING_CTRL2_VADDR, _BIT0);
	//rtdf_setBits(DITHER_DITHERING_DD_TH_B_VADDR, _BIT30);
#endif

//----------------------------------------------------------------------------------
// set by lydia
#if 0
    printk("setting VIP register...\n");

	//====I-domain

	//I_ptg, I_VGIP, 422to444, DI(2D) set by bringup script

	//I_Digital_Filter
	drvif_color_digital_filter_config(_CHANNEL1,1);

	// I_RGB2YUV
	rtdf_setBits(0xb8023000,_BIT0); // I rgb2yuv en
	//printk("setting VIP register.....1\n");

	//I_MPEG_NR
	rtdf_setBits(0xb8023128,_BIT0); // hor MPEGNR en
	rtdf_setBits(0xb8024254,_BIT0); // Ver MPEGNR en
	//printk("setting VIP register.....2\n");

	udelay(40);

	//HSD
	//rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR,_BIT0);

	//SD_Dither_10to8
	//rtdf_setBits(SD_DITHER_SD_DITHER_CTRL1_VADDR,_BIT4);
	//rtdf_setBits(SD_DITHER_SD_DITHER_CTRL1_VADDR,_BIT5);

	//RTNR
	rtdf_setBits(0xb80241a0,_BIT0);//enable RTNR Y
	rtdf_setBits(0xb80241a0,_BIT1);//enable RTNR C
	//printk("setting VIP register.....3\n");

    //I Edge smooth
 	rtdf_setBits(0xb8025100,_BIT0);//enable
 	//printk("setting VIP register.....4\n");

	// I_peaking
	rtdf_setBits(0xb8023100,_BIT26);//en
	//printk("setting VIP register.....6\n");
	udelay(40000);

	// VSD
	//rtdf_setBits(SCALEDOWN_ICH1_UZD_CTRL0_VADDR,_BIT1);

	// 444to422


	//====D-domain

	//D-Pattern Gen set @ bringup script

	// 422to444

	//D_ SUPK and VCTI and UnSharpMask
	D_SUPK_and_VDCTI_Setting();

	//D_2Dto3D
	D_2Dto3D_Setting();
	//printk("setting VIP register.....7\n");

	//vivid color
    rtdf_setBits(0xb802a000,_BIT30);//vc en
	rtdf_setBits(0xb802a000,_BIT5);//egsm en
	rtdf_setBits(0xb802a000,_BIT4);//shp en
	rtdf_setBits(0xb802a000,_BIT3);//icm en
	rtdf_setBits(0xb802a000,_BIT2);//dcti en
	rtdf_setBits(0xb802a000,_BIT0);//dcc en
	//printk("setting VIP register.....8\n");

	// D_DLTI/DCTI
    rtdf_setBits(0xb802a68c,_BIT0);//dlti en
    rtd_outl(0xb802a00c, 0x0000AA76);//COLOR_DLCTI_DM_DLTI_OPTIONS_VADDR
	rtd_outl(0xb802a010, 0x0000001A);//COLOR_DLCTI_DM_DLTI_VALUE_VADDR
	rtd_outl(0xb802a01c, 0x00000001);//COLOR_DLCTI_DM_DCTI_OPTIONS_VADDR
	rtd_outl(0xb802a020, 0x0000002C);//COLOR_DLCTI_DM_DCTI_1ST_VALUE_VADDR
	//printk("setting VIP register.....9\n");

	//D_Sharpness
    rtdf_setBits(0xb802a500,_BIT0);//en
   	D_Sharpness_Setting(main);
    //printk("setting VIP register.....10\n");
	udelay(40000);

	//D_Edgesmooth
	rtdf_setBits(0xb802aa00,_BIT8);//Dir_LPF
	rtdf_setBits(0xb802aa14,_BIT28);//PostSHP
	//printk("setting VIP register.....11\n");


	//DCC
	rtdf_setBits(0xb802e400, _BIT24);
	udelay(60000);

	//ICM
	//D_ICM_Setting(_MAIN_DISPLAY);

	// yuv2rgb
	rtdf_setBits(0xb802ac00, _BIT0);
	//printk("setting VIP register.....12\n");

	// Contrast,Brightness
	rtdf_setBits(0xb802a800, 0x00000003);
	//printk("setting VIP register.....13\n");


	// 3Dither
	//drvif_color_Disable_3Dithering();
	//drvif_color_set3Dithering();

	//udelay(1000);

	// mac2 no output Gamma
	//D_Gamma_Setting(_MAIN_DISPLAY, 1);

#endif

}


int HDQC_main(CRC* crc)
{
//	UINT8 rtnr_result_ch1=PASS;

	UINT32 VGIP1_CRC_template=0;
	UINT32 HSD_CRC_template=0;	//	new
	UINT32 DI_CRC_template=0;	//	new
	UINT32 UZD1_CRC_template=0;
	UINT32 MEM1_CRC_template=0;
	UINT32 UZU1_CRC_template=0;
	UINT32 SHP1_CRC_template=0;
	UINT32 ICM1_CRC_template=0;


	UINT32 VGIP1_CRC_template2=0;
	UINT32 HSD_CRC_template2=0;	//	new
	UINT32 DI_CRC_template2=0;	//	new
	UINT32 UZD1_CRC_template2=0;
	UINT32 MEM1_CRC_template2=0;
	UINT32 UZU1_CRC_template2=0;
	UINT32 SHP1_CRC_template2=0;
	UINT32 ICM1_CRC_template2=0;

	// 3Dither
	UINT32 Dither_CRC1=0;
	UINT32 Dither_CRC2=0;
	UINT32 Dither_CRC3=0;
	UINT32 Dither_CRC4=0;
	UINT32 Dither_CRC5=0;
	UINT32 Dither_CRC6=0;
	UINT32 Dither_CRC7=0;
	UINT32 Dither_CRC8=0;

	int return_value = PASS;

	//printk("into HDQC_main...\n");

	VGIP1_CRC_template=0x67a455b7;
	HSD_CRC_template=0x61074586;
	DI_CRC_template=0xd65e5986;
	DI_CRC_template2=0x9ed62d78;
	UZD1_CRC_template=0x61074586;

	MEM1_CRC_template=0x61074586;
	UZU1_CRC_template=0x68e3e293;
	SHP1_CRC_template=0xa858fa88;
	//ICM1_CRC_template=0x991be435;

	/*
	VGIP1_CRC_template2=0xcecfeccb;
	HSD_CRC_template2=0x68c75c9f;
	DI_CRC_template2=0x5b7c3122;
	UZD1_CRC_template2=0xfba35e2d;

	MEM1_CRC_template2=0xdc6ce6e0;
	UZU1_CRC_template2=0x90af4581;
	SHP1_CRC_template2=0xeb9a3629;
	ICM1_CRC_template2=0x68e3e293;
	*/

	Dither_CRC1=0x42b3e102;
	Dither_CRC2=0xf5ff2e96;
	Dither_CRC3=0xd642960c;
	Dither_CRC4=0x6bf72abf;
	/*
	Dither_CRC5=0x30264653;
	Dither_CRC6=0x95427e77;
	Dither_CRC7=0x1fbbec75;
	Dither_CRC8=0xec56e70b;
	*/

	//=============== Testing ===============//

	crc->VGIP1		= VGIP_CRC_En(_CHANNEL1);
		//printk("\n 1 ...");
	crc->HSD1		= HSD_CRC_En(_CHANNEL1);
		//printk("\n 2 ...");
	crc->DI			= DI_CRC_En();
		//printk("\n 3 ...");
	crc->UZD1		= VSD_CRC_En(_CHANNEL1);
		//printk("\n 4 ...");
	crc->MEM1		= MEM_CRC_En(_CHANNEL1);
		//printk("\n 5 ...");
	crc->UZU1		= UZU_CRC_En(_CHANNEL1);
		//printk("\n 6 ...");
	crc->SHP1		= SHP_CRC_En(_CHANNEL1);
		//printk("\n 7 ...");
	crc->ICM1		= ICM_CRC_En(_CHANNEL1);
		//printk("\n 8 ...");

	crc->Dither		= Dither_CRC_En();

	//printk("VGIP1:%x\n", crc->VGIP1);
	//printk("HSD1: %x\n", crc->HSD1);
	//printk("DI:	 %x\n", crc->DI);
	//printk("UZD1: %x\n", crc->UZD1);
	//printk("MEM1: %x\n", crc->MEM1);
	//printk("UZU1: %x\n", crc->UZU1);
	//printk("SHP1: %x\n", crc->SHP1);
	//printk("ICM1: %x\n", crc->ICM1);
 	//printk("Dither: %x\n", crc->Dither);



	#define vgip_crcmsg 1
	#if vgip_crcmsg
	if(crc->VGIP1 != VGIP1_CRC_template && crc->VGIP1 != VGIP1_CRC_template2)
	{
		printk("Main HD  crc.VGIP1 fail %x \n", crc->VGIP1);
		return_value = FAIL;
	}
	#endif


	#define hsd_crcmsg 1
	#if hsd_crcmsg
	if(crc->HSD1!= HSD_CRC_template && crc->HSD1!= HSD_CRC_template2)
	{
		printk("Main HD  crc.HSD1 fail %x \n", crc->HSD1);
		return_value = FAIL;
	}
	#endif

	#define di_crcmsg 1
	#if di_crcmsg
	if(crc->DI!= DI_CRC_template && crc->DI!= DI_CRC_template2)
	{
		printk("Main HD  crc.DI fail %x \n", crc->DI);
		return_value = FAIL;
	}
	#endif

	#define uzd_crcmsg 1
	#if uzd_crcmsg
		if(crc->UZD1 != UZD1_CRC_template &&crc->UZD1 != UZD1_CRC_template2)
		{
			printk("Main HD  crc.UZD1 fail %x \n", crc->UZD1);
			return_value = FAIL;
		}
	#endif

	#define mem_crcmsg 1
	#if mem_crcmsg
	if(crc->MEM1 != MEM1_CRC_template && crc->MEM1 != MEM1_CRC_template2)
	{
		printk("Main HD crc.MEM1 fail %x \n",crc->MEM1);
		return_value = FAIL;
	}
	#endif

	#define uzu_crcmsg 1
	#if uzu_crcmsg
	if(crc->UZU1 != UZU1_CRC_template && crc->UZU1 != UZU1_CRC_template2)
	{
		printk("Main HD  crc.UZU1 fail %x \n",crc->UZU1);
		return_value = FAIL;
	}
	#endif

	#define shp_crcmsg 1
	#if shp_crcmsg
	if(crc->SHP1 != SHP1_CRC_template && crc->SHP1 != SHP1_CRC_template2)
	{
		printk("Main HD  crc.SHP1 fail %x \n",crc->SHP1);
		return_value = FAIL;
	}
	#endif


	#define icm_crcmsg 0
	#if icm_crcmsg
	if(crc->ICM1!= ICM1_CRC_template && crc->ICM1!= ICM1_CRC_template2)
	{
		printk("Main HD  crc.ICM1 fail %x \n",crc->ICM1);
		return_value = FAIL;
	}
	#endif

	#define dither_crcmsg 1
	#if dither_crcmsg
	if (		(crc->Dither != Dither_CRC1)&& (crc->Dither != Dither_CRC2)&&(crc->Dither != Dither_CRC3)&&(crc->Dither != Dither_CRC4)
		&& 	(crc->Dither != Dither_CRC5)&& (crc->Dither != Dither_CRC6)&&(crc->Dither != Dither_CRC7)&&(crc->Dither != Dither_CRC8)	)
	{
		printk("Main HD  crc.Dither fail %x \n",crc->Dither);
		return_value = FAIL;
	}
	#endif


	return return_value;

}


int VIP_main_path()
{
    int result=0,k=0,failtime=1,runpass=0,return_value=0;
    CRC crc_hd={0};
    static int init_cnt=10;

    printk("into VIP main path\n");

   	MAC_M_VIPSetting();
    rtd_outl(0xb8022290,0x606);//CTS FIFO reset


	udelay(1000);
	do
	{
    	k++;
    	printk("%d  ",k);

        result=HDQC_main(&crc_hd);

    	if (result!=FAIL)
		{
			printk("Pass\n");
			failtime--;
			runpass++;
		}
		else
		{

			if(init_cnt!=10)
			{
				failtime++;
				printk("fail\n");
			}
			init_cnt--;
		}

    }while(k<10);



    return result;



}


int QC_Verifier_VIP(void)
{
    int errcnt=0;
    int VIPstatus=0;

    printk("o======VIP Verifier======o\n");


    module_VIP_bringup_script();


    errcnt=VIP_main_path();

    if( (errcnt==0)  )
	{
	    printk("\nVIP PASS!!!\n");
	}
	else
	{
		printk("\nVIP FAIL!!!\n");
	}

	VIPstatus=errcnt;

	//IMD domain reset
	//rtd_maskl(SYS_SRST1, 0xfffff7fc, 0x0); //[11]I_domain, [1]M, [0]D (active low)
	//rtd_maskl(SYS_SRST1, 0xfffff7fc, 0x803); //[11]I_domain, [1]M, [0]D

	return VIPstatus;
}
