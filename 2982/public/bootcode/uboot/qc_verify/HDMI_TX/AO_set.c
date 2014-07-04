#include "AO_set.h"
#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "AIO_reg.h"
#include <qc_verify_common.h>
#include <rtd_types_qc.h>


extern void BusyWaiting(UINT32);

void SET_AO(UINT8 ASamplingFrequency, UINT8 ASampleSize, UINT8 AChannelNumber, UINT8 AType)
{
    UINT8 CS_PCMsamples;
    UINT8 CS_SoftwareCopyright=1;
    UINT8 CS_ClcokAccuracy=0;
    UINT8 CS_ChannelNumber;
    UINT8 CS_SourceChannelNumber=0;
    UINT8 CS_SamplingFrequency;
    UINT8 CS_SampleWordLength;
    UINT8 CS_OriginalSamplingFrequency=0;
    UINT32 AO_CS1;
    UINT32 AO_CS2;

    //Disable AO=============================================================================================
    //0xb8006304
    rtd_outl(AIO_O_GO_reg,
                     AIO_O_GO_goacdac(0)|
                     AIO_O_GO_gohdmi(0)| //Disable HDMI output
                     AIO_O_GO_goi2s(0)| //Disable I2S output
                     AIO_O_GO_gospf(0)); //Disable SPDIF output

    //AO FIFO Control & DMA disable==========================================================================
    //0xb8006090
    rtd_outl(AIO_O_FIFOCTL_reg,
                     AIO_O_FIFOCTL_emptystopen(0)|
                     AIO_O_FIFOCTL_thd(0)|
                     AIO_O_FIFOCTL_en10(0)|
                     AIO_O_FIFOCTL_en9(0)|
                     AIO_O_FIFOCTL_en8(0)|
                     AIO_O_FIFOCTL_en7(0)|
                     AIO_O_FIFOCTL_en6(0)|
                     AIO_O_FIFOCTL_en5(0)|
                     AIO_O_FIFOCTL_en4(0)|
                     AIO_O_FIFOCTL_en3(0)|
                     AIO_O_FIFOCTL_en2(0)|
                     AIO_O_FIFOCTL_en1(0)|
                     AIO_O_FIFOCTL_en0(0));

    //AO Frequency setting====================================================================================
#if 1
 	switch(ASamplingFrequency)
    //register only for Jupiter-FPGA using
    {
        case 1: //fs=32k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (1<<8)| //384x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (2<<1)| //32k
                                                     (1))); //enable


            CS_SamplingFrequency=3;
            break;
        case 2: //fs=44.1k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (1<<1)| //44.1k
                                                     (1))); //enable
            CS_SamplingFrequency=0;
            break;
        case 3: //fs=48k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                    (0<<8)| //256x
                                                    (ASampleSize<<5)| //Audio Sample Size
                                                    (0<<1)| //48k
                                                    (1))); //enable
            CS_SamplingFrequency=2;
            break;
        case 4: //fs=88.2k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (8<<1)| //88.2k
                                                     (1))); //enable
            CS_SamplingFrequency=8;
            break;
        case 5: //fs=96k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (3<<1)| //96k
                                                     (1))); //enable
            CS_SamplingFrequency=0xa;
            break;
        case 6: //fs=176.4k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (2<<8)| //128x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (10<<1)| //176.4k
                                                     (1))); //enable
            CS_SamplingFrequency=0xc;
            break;
        case 7: //fs=192k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (2<<8)| //128x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (9<<1)| //192k
                                                     (1))); //enable
            CS_SamplingFrequency=0xe;
            break;
        default: 
            break;
    }
    if(AType == 4)
    {
        rtd_outl(AIO_O_ACANA_GCTL2_reg,
                         AIO_O_ACANA_GCTL2_write_en2(1)|
                         AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs) 
                                                 (2<<8)| //128x
                                                 (ASampleSize<<5)| //Audio Sample Size
                                                 (9<<1)| //192k
                                                 (1))); //enable
        CS_SamplingFrequency=0x9;
    }
#else
 	switch(ASamplingFrequency)
    	{
    	
        case 1: //fs=32k
            rtd_outl(0xB8000070,
                                                     (1<<5)| //384x
                                                     (2<<1)| //32k
                                                     (1)); //enable
            CS_SamplingFrequency=3;
            break;
        case 2: //fs=44.1k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (1<<1)| //44.1k
                                                     (1))); //enable
            CS_SamplingFrequency=0;
            break;
        case 3: //fs=48k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                    (0<<8)| //256x
                                                    (ASampleSize<<5)| //Audio Sample Size
                                                    (0<<1)| //48k
                                                    (1))); //enable
            CS_SamplingFrequency=2;
            break;
        case 4: //fs=88.2k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (8<<1)| //88.2k
                                                     (1))); //enable
            CS_SamplingFrequency=8;
            break;
        case 5: //fs=96k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (0<<8)| //256x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (3<<1)| //96k
                                                     (1))); //enable
            CS_SamplingFrequency=0xa;
            break;
        case 6: //fs=176.4k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (2<<8)| //128x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (10<<1)| //176.4k
                                                     (1))); //enable
            CS_SamplingFrequency=0xc;
            break;
        case 7: //fs=192k
            rtd_outl(AIO_O_ACANA_GCTL2_reg,
                             AIO_O_ACANA_GCTL2_write_en2(1)|
                             AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs)
                                                     (2<<8)| //128x
                                                     (ASampleSize<<5)| //Audio Sample Size
                                                     (9<<1)| //192k
                                                     (1))); //enable
            CS_SamplingFrequency=0xe;
            break;
        default: 
            break;
    	}
    	if(AType == 4)
    	{
	        rtd_outl(AIO_O_ACANA_GCTL2_reg,
	                         AIO_O_ACANA_GCTL2_write_en2(1)|
	                         AIO_O_ACANA_GCTL2_ct_bias((0<<11)| //0:direct play, 1:count-down play(F=64fs) 
	                                                 (2<<8)| //128x
	                                                 (ASampleSize<<5)| //Audio Sample Size
	                                                 (9<<1)| //192k
	                                                 (1))); //enable
	        CS_SamplingFrequency=0x9;
    	}
#endif
    //AO Channel Control======================================================================================
    switch(ASampleSize)
    {
        case 1://16bit, max 20bit
            CS_SampleWordLength=0x2;
            break;
        case 2://20bit, max 24bit
            CS_SampleWordLength=0x3;
            break;
        case 3://24bit, max 24bit
            CS_SampleWordLength=0xb;
            break;
    }

    if(ASampleSize==1) ASampleSize=0;

    switch(AType)
    {
        case 0: //I2S 8ch-PCM
            //0xB8006070
            rtd_outl(AIO_O_HDMI_GCTL_reg,
                             AIO_O_HDMI_GCTL_pkt(0)|
                             AIO_O_HDMI_GCTL_sample_flat(0)|
                             AIO_O_HDMI_GCTL_8ch(1)|
                             AIO_O_HDMI_GCTL_bit(ASampleSize)| //PCM bit number
                             AIO_O_HDMI_GCTL_wait_en(0)|
                             AIO_O_HDMI_GCTL_rmute(0)|
                             AIO_O_HDMI_GCTL_lmute(0)|
                             AIO_O_HDMI_GCTL_switch_wait_en(0)|
                             AIO_O_HDMI_GCTL_sel(2)| //8ch PCM from HDMI FIFO
                             AIO_O_HDMI_GCTL_en(1));
            CS_ChannelNumber = AChannelNumber;
            CS_PCMsamples = 0;
            break;
        case 1: //I2S 2ch-PCM
            //0xb8006070
            rtd_outl(AIO_O_HDMI_GCTL_reg,
                             AIO_O_HDMI_GCTL_pkt(1)|//20120713 kist
                             AIO_O_HDMI_GCTL_sample_flat(0)|
                             AIO_O_HDMI_GCTL_8ch(0)|
                             AIO_O_HDMI_GCTL_bit(ASampleSize)| //PCM bit number
                             AIO_O_HDMI_GCTL_wait_en(0)|
                             AIO_O_HDMI_GCTL_rmute(0)|
                             AIO_O_HDMI_GCTL_lmute(0)|
                             AIO_O_HDMI_GCTL_switch_wait_en(0)|
                             AIO_O_HDMI_GCTL_sel(0)| //2ch PCM from PCM FIFO
                             AIO_O_HDMI_GCTL_en(1));
            CS_ChannelNumber = AChannelNumber;
            CS_PCMsamples = 0;
            break;
        case 2: //SPDIF PCM
            //0xb8006070
            rtd_outl(AIO_O_HDMI_GCTL_reg,
                             AIO_O_HDMI_GCTL_pkt(1)|
                             AIO_O_HDMI_GCTL_sample_flat(0)|
                             AIO_O_HDMI_GCTL_8ch(0)|
                             AIO_O_HDMI_GCTL_bit(ASampleSize)| //PCM bit number
                             AIO_O_HDMI_GCTL_wait_en(0)|
                             AIO_O_HDMI_GCTL_rmute(0)|
                             AIO_O_HDMI_GCTL_lmute(0)|
                             AIO_O_HDMI_GCTL_switch_wait_en(0)|
                             AIO_O_HDMI_GCTL_sel(0)| //2ch PCM from PCM FIFO
                             AIO_O_HDMI_GCTL_en(1));
            CS_ChannelNumber = AChannelNumber;
            CS_PCMsamples = 0;
            break;
        case 3: //SPDIF RAW
            //0xb8006070
            rtd_outl(AIO_O_HDMI_GCTL_reg,
                             AIO_O_HDMI_GCTL_pkt(1)|
                             AIO_O_HDMI_GCTL_sample_flat(0)|
                             AIO_O_HDMI_GCTL_8ch(0)|
                             AIO_O_HDMI_GCTL_bit(ASampleSize)| //PCM bit number
                             AIO_O_HDMI_GCTL_wait_en(0)|
                             AIO_O_HDMI_GCTL_rmute(0)|
                             AIO_O_HDMI_GCTL_lmute(0)|
                             AIO_O_HDMI_GCTL_switch_wait_en(0)|
                             AIO_O_HDMI_GCTL_sel(1)| //RAW from RAW FIFO
                             AIO_O_HDMI_GCTL_en(1));
            CS_ChannelNumber = 0;
            CS_PCMsamples = 1;
            break;
        case 4: //HBR RAW
            //0xb8006070
            rtd_outl(AIO_O_HDMI_GCTL_reg,
                             AIO_O_HDMI_GCTL_pkt(0)|
                             AIO_O_HDMI_GCTL_sample_flat(0)|
                             AIO_O_HDMI_GCTL_8ch(0)|
                             AIO_O_HDMI_GCTL_bit(ASampleSize)| //PCM bit number
                             AIO_O_HDMI_GCTL_wait_en(0)|
                             AIO_O_HDMI_GCTL_rmute(0)|
                             AIO_O_HDMI_GCTL_lmute(0)|
                             AIO_O_HDMI_GCTL_switch_wait_en(0)|
                             AIO_O_HDMI_GCTL_sel(3)| //HBR from HDMI FIFO
                             AIO_O_HDMI_GCTL_en(1));
            CS_ChannelNumber = 0;
            CS_PCMsamples = 1;
            break;
        default:
            break;
    }

    //AO Channel status setting===============================================================================
    AO_CS1 = (CS_ClcokAccuracy<<28)| //CS[31:0]
             (CS_SamplingFrequency<<24)|
             (CS_ChannelNumber<<20)|
             (CS_SourceChannelNumber<<16)|
             (CS_SoftwareCopyright<<2)|
             (CS_PCMsamples<<1);
    AO_CS2 = (CS_OriginalSamplingFrequency<<4)| //CS[39:32]
             (CS_SampleWordLength);

    //0xb800600c
    rtd_outl(AIO_O_PCM_CS1_reg, AIO_O_PCM_CS1_cs1(AO_CS1));
    //0xb8006010
    rtd_outl(AIO_O_PCM_CS2_reg, AIO_O_PCM_CS2_cs2(AO_CS2));
    //0xb8006058
    rtd_outl(AIO_O_RAW_CS1_reg, AIO_O_RAW_CS1_cs1(AO_CS1));
    //0xb800605c
    rtd_outl(AIO_O_RAW_CS2_reg, AIO_O_RAW_CS2_cs2(AO_CS2));
    //0xb8006078
    rtd_outl(AIO_O_HDMI_CS1_reg, AIO_O_HDMI_CS1_cs1(AO_CS1));
    //0xb800607c
    rtd_outl(AIO_O_HDMI_CS2_reg, AIO_O_HDMI_CS2_cs2(AO_CS2));

    //AO FIFO address setting=================================================================================
    //I2S 8-ch FIFO-------------------------------------------------------------
    if(AType == 0)
    {
        switch(ASamplingFrequency)
        {
            case 1: //32k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_32k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_32k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_32k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_32k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_32k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_32k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_32k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_32k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_32k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_32k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_32k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_32k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_32k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_32k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_32k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_32k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_32k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_32k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_32k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_32k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_32k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_32k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_32k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_32k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_32k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_32k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_32k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_32k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_32k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_32k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_32k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_32k_FIFO_WP)>>3));
                break;
            case 2: //44.1k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_44k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_44k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_44k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_44k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_44k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_44k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_44k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_44k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_44k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_44k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_44k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_44k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_44k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_44k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_44k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_44k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_44k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_44k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_44k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_44k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_44k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_44k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_44k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_44k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_44k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_44k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_44k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_44k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_44k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_44k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_44k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_44k_FIFO_WP)>>3));
                break;
            case 3: //48k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_48k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_48k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_48k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_48k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_48k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_48k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_48k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_48k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_48k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_48k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_48k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_48k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_48k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_48k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_48k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_48k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_48k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_48k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_48k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_48k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_48k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_48k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_48k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_48k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_48k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_48k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_48k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_48k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_48k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_48k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_48k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_48k_FIFO_WP)>>3));
                break;
            case 4: //88.2k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_88k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_88k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_88k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_88k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_88k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_88k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_88k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_88k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_88k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_88k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_88k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_88k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_88k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_88k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_88k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_88k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_88k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_88k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_88k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_88k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_88k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_88k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_88k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_88k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_88k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_88k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_88k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_88k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_88k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_88k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_88k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_88k_FIFO_WP)>>3));
                break;
            case 5: //96k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_96k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_96k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_96k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_96k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_96k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_96k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_96k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_96k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_96k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_96k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_96k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_96k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_96k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_96k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_96k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_96k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_96k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_96k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_96k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_96k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_96k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_96k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_96k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_96k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_96k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_96k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_96k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_96k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_96k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_96k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_96k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_96k_FIFO_WP)>>3));
                break;
            case 6: //176.4k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_176k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_176k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_176k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_176k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_176k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_176k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_176k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_176k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_176k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_176k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_176k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_176k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_176k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_176k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_176k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_176k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_176k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_176k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_176k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_176k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_176k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_176k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_176k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_176k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_176k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_176k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_176k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_176k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_176k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_176k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_176k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_176k_FIFO_WP)>>3));
                break;
            case 7: //192k
                //0xb8006190
                rtd_outl(AIO_O_SA_4_reg, AIO_O_SA_addr((PCM2L_192k_FIFO_SA)>>3));
                //0xb8006194
                rtd_outl(AIO_O_SA_5_reg, AIO_O_SA_addr((PCM2R_192k_FIFO_SA)>>3));
                //0xb8006198
                rtd_outl(AIO_O_SA_6_reg, AIO_O_SA_addr((PCM2L_192k_FIFO_SA)>>3));
                //0xb800619c
                rtd_outl(AIO_O_SA_7_reg, AIO_O_SA_addr((PCM2R_192k_FIFO_SA)>>3));
                //0xb80061a0
                rtd_outl(AIO_O_SA_8_reg, AIO_O_SA_addr((PCM2L_192k_FIFO_SA)>>3));
                //0xb80061a4
                rtd_outl(AIO_O_SA_9_reg, AIO_O_SA_addr((PCM2R_192k_FIFO_SA)>>3));
                //0xb80061a8
                rtd_outl(AIO_O_SA_10_reg, AIO_O_SA_addr((PCM2L_192k_FIFO_SA)>>3));
                //0xb80061ac
                rtd_outl(AIO_O_SA_11_reg, AIO_O_SA_addr((PCM2R_192k_FIFO_SA)>>3));
                //0xb80061c0
                rtd_outl(AIO_O_EA_4_reg, AIO_O_EA_addr((PCM2L_192k_FIFO_EA)>>3));
                //0xb80061c4
                rtd_outl(AIO_O_EA_5_reg, AIO_O_EA_addr((PCM2R_192k_FIFO_EA)>>3));
                //0xb80061c8
                rtd_outl(AIO_O_EA_6_reg, AIO_O_EA_addr((PCM2L_192k_FIFO_EA)>>3));
                //0xb80061cc
                rtd_outl(AIO_O_EA_7_reg, AIO_O_EA_addr((PCM2R_192k_FIFO_EA)>>3));
                //0xb80061d0
                rtd_outl(AIO_O_EA_8_reg, AIO_O_EA_addr((PCM2L_192k_FIFO_EA)>>3));
                //0xb80061d4
                rtd_outl(AIO_O_EA_9_reg, AIO_O_EA_addr((PCM2R_192k_FIFO_EA)>>3));
                //0xb80061d8
                rtd_outl(AIO_O_EA_10_reg, AIO_O_EA_addr((PCM2L_192k_FIFO_EA)>>3));
                //0xb80061dc
                rtd_outl(AIO_O_EA_11_reg, AIO_O_EA_addr((PCM2R_192k_FIFO_EA)>>3));
                //0xb80061f0
                rtd_outl(AIO_O_RP_4_reg, AIO_O_RP_addr((PCM2L_192k_FIFO_RP)>>3));
                //0xb80061f4
                rtd_outl(AIO_O_RP_5_reg, AIO_O_RP_addr((PCM2R_192k_FIFO_RP)>>3));
                //0xb80061f8
                rtd_outl(AIO_O_RP_6_reg, AIO_O_RP_addr((PCM2L_192k_FIFO_RP)>>3));
                //0xb80061fc
                rtd_outl(AIO_O_RP_7_reg, AIO_O_RP_addr((PCM2R_192k_FIFO_RP)>>3));
                //0xb8006200
                rtd_outl(AIO_O_RP_8_reg, AIO_O_RP_addr((PCM2L_192k_FIFO_RP)>>3));
                //0xb8006204
                rtd_outl(AIO_O_RP_9_reg, AIO_O_RP_addr((PCM2R_192k_FIFO_RP)>>3));
                //0xb8006208
                rtd_outl(AIO_O_RP_10_reg, AIO_O_RP_addr((PCM2L_192k_FIFO_RP)>>3));
                //0xb800620c
                rtd_outl(AIO_O_RP_11_reg, AIO_O_RP_addr((PCM2R_192k_FIFO_RP)>>3));
                //0xb8006230
                rtd_outl(AIO_O_WP_4_reg, AIO_O_WP_addr((PCM2L_192k_FIFO_WP)>>3));
                //0xb8006234
                rtd_outl(AIO_O_WP_5_reg, AIO_O_WP_addr((PCM2R_192k_FIFO_WP)>>3));
                //0xb8006238
                rtd_outl(AIO_O_WP_6_reg, AIO_O_WP_addr((PCM2L_192k_FIFO_WP)>>3));
                //0xb800623c
                rtd_outl(AIO_O_WP_7_reg, AIO_O_WP_addr((PCM2R_192k_FIFO_WP)>>3));
                //0xb8006240
                rtd_outl(AIO_O_WP_8_reg, AIO_O_WP_addr((PCM2L_192k_FIFO_WP)>>3));
                //0xb8006244
                rtd_outl(AIO_O_WP_9_reg, AIO_O_WP_addr((PCM2R_192k_FIFO_WP)>>3));
                //0xb8006248
                rtd_outl(AIO_O_WP_10_reg, AIO_O_WP_addr((PCM2L_192k_FIFO_WP)>>3));
                //0xb800624c
                rtd_outl(AIO_O_WP_11_reg, AIO_O_WP_addr((PCM2R_192k_FIFO_WP)>>3));
                break;
            default:
                break;
        }
    }

    //I2S 2-ch FIFO-------------------------------------------------------------
    //SPDIF PCM FIFO------------------------------------------------------------
    if(AType == 1 || AType == 2)
    {
        switch(ASamplingFrequency)
        {
            case 1: //32k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_32k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_32k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_32k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_32k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_32k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_32k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_32k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_32k_FIFO_WP)>>3));
                break;
            case 2: //44.1k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_44k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_44k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_44k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_44k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_44k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_44k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_44k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_44k_FIFO_WP)>>3));
                break;
            case 3: //48k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_48k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_48k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_48k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_48k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_48k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_48k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_48k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_48k_FIFO_WP)>>3));
                break;
            case 4: //88.2k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_88k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_88k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_88k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_88k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_88k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_88k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_88k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_88k_FIFO_WP)>>3));
                break;
            case 5: //96k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_96k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_96k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_96k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_96k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_96k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_96k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_96k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_96k_FIFO_WP)>>3));
                break;
            case 6: //176.4k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_176k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_176k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_176k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_176k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_176k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_176k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_176k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_176k_FIFO_WP)>>3));
                break;
            case 7: //192k
                //0xb8006180
                rtd_outl(AIO_O_SA_0_reg, AIO_O_SA_addr((PCM2L_192k_FIFO_SA)>>3));
                //0xb8006184
                rtd_outl(AIO_O_SA_1_reg, AIO_O_SA_addr((PCM2R_192k_FIFO_SA)>>3));
                //0xb80061b0
                rtd_outl(AIO_O_EA_0_reg, AIO_O_EA_addr((PCM2L_192k_FIFO_EA)>>3));
                //0xb80061b4
                rtd_outl(AIO_O_EA_1_reg, AIO_O_EA_addr((PCM2R_192k_FIFO_EA)>>3));
                //0xb80061e0
                rtd_outl(AIO_O_RP_0_reg, AIO_O_RP_addr((PCM2L_192k_FIFO_RP)>>3));
                //0xb80061e4
                rtd_outl(AIO_O_RP_1_reg, AIO_O_RP_addr((PCM2R_192k_FIFO_RP)>>3));
                //0xb8006220
                rtd_outl(AIO_O_WP_0_reg, AIO_O_WP_addr((PCM2L_192k_FIFO_WP)>>3));
                //0xb8006224
                rtd_outl(AIO_O_WP_1_reg, AIO_O_WP_addr((PCM2R_192k_FIFO_WP)>>3));
                break;
            default:
                break;
        }
    }

    //SPDIF Non-PCM FIFO--------------------------------------------------------
    if(AType == 3)
    {
        switch(ASamplingFrequency)
        {
            case 1: //32k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_32k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_32k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_32k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_32k_FIFO_WP)>>3));
                break;
            case 2: //44.1k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_44k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_44k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_44k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_44k_FIFO_WP)>>3));
                break;
            case 3: //48k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_48k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_48k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_48k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_48k_FIFO_WP)>>3));
                break;
            case 4: //88.2k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_88k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_88k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_88k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_88k_FIFO_WP)>>3));
                break;
            case 5: //96k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_96k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_96k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_96k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_96k_FIFO_WP)>>3));
                break;
            case 6: //176.4k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_176k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_176k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_176k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_176k_FIFO_WP)>>3));
                break;
            case 7: //192k
                //0xb8006188
                rtd_outl(AIO_O_SA_2_reg, AIO_O_SA_addr((RAW_192k_FIFO_SA)>>3));
                //0xb80061b8
                rtd_outl(AIO_O_EA_2_reg, AIO_O_EA_addr((RAW_192k_FIFO_EA)>>3));
                //0xb80061e8
                rtd_outl(AIO_O_RP_2_reg, AIO_O_RP_addr((RAW_192k_FIFO_RP)>>3));
                //0xb8006228
                rtd_outl(AIO_O_WP_2_reg, AIO_O_WP_addr((RAW_192k_FIFO_WP)>>3));
                break;
            default:
                break;
        }
    }

    //HBR FIFO------------------------------------------------------------------
    if(AType == 4)
    {
        //0xb800618c
        rtd_outl(AIO_O_SA_3_reg, AIO_O_SA_addr((HBR_FIFO_SA)>>3));
        //0xb80061bc
        rtd_outl(AIO_O_EA_3_reg, AIO_O_EA_addr((HBR_FIFO_EA)>>3));
        //0xb80061ec
        rtd_outl(AIO_O_RP_3_reg, AIO_O_RP_addr((HBR_FIFO_RP)>>3));
        //0xb800622c
        rtd_outl(AIO_O_WP_3_reg, AIO_O_WP_addr((HBR_FIFO_WP)>>3));
    }

    //AO Control Flow=========================================================================================
    //0xB800630c
    //kist
    rtd_outl(AIO_O_PAUSE_reg,
                     AIO_O_PAUSE_pause2(0)|
                     AIO_O_PAUSE_pause1(0)|
                     AIO_O_PAUSE_pause0(0));

    //AO Interrupts setting===================================================================================
    //0xB8006400
    rtd_outl(AIO_O_PCM_DDRTHD_reg, AIO_O_PCM_DDRTHD_thd(0));
    //0xB8006404
    rtd_outl(AIO_O_PCM_TIMCNT_reg, AIO_O_PCM_TIMCNT_count(0));
    //0xB8006408
    rtd_outl(AIO_O_PCM_TIMTHD_reg, AIO_O_PCM_TIMTHD_thd(0xffffffff));

    //0xB8006410
    rtd_outl(AIO_O_RAW_DDRTHD_reg, AIO_O_RAW_DDRTHD_thd(0));
    //0xB8006414
    rtd_outl(AIO_O_RAW_TIMCNT_reg, AIO_O_RAW_TIMCNT_count(0));
    //0xB8006418
    rtd_outl(AIO_O_RAW_TIMTHD_reg, AIO_O_RAW_TIMTHD_thd(0xffffffff));

    //0xB8006420
    rtd_outl(AIO_O_HDMI_DDRTHD_reg, AIO_O_HDMI_DDRTHD_thd(0));
    //0xB8006424
    rtd_outl(AIO_O_HDMI_TIMCNT_reg, AIO_O_HDMI_TIMCNT_count(0));
    //0xB8006428
    rtd_outl(AIO_O_HDMI_TIMTHD_reg, AIO_O_HDMI_TIMTHD_thd(0xffffffff));

    //0xB8006440
    rtd_outl(AIO_O_INTE_reg,
                     AIO_O_INTE_draminte11(1)|
                     AIO_O_INTE_draminte10(1)|
                     AIO_O_INTE_draminte9(1)|
                     AIO_O_INTE_draminte8(1)| 
                     AIO_O_INTE_draminte7(1)|
                     AIO_O_INTE_draminte6(1)|
                     AIO_O_INTE_draminte5(1)|
                     AIO_O_INTE_draminte4(1)| 
                     AIO_O_INTE_fifointe11(1)|
                     AIO_O_INTE_fifointe10(1)|
                     AIO_O_INTE_fifointe9(1)|
                     AIO_O_INTE_fifointe8(1)|
                     AIO_O_INTE_fifointe7(1)|
                     AIO_O_INTE_fifointe6(1)|
                     AIO_O_INTE_fifointe5(1)|
                     AIO_O_INTE_fifointe4(1)|
                     AIO_O_INTE_pcmtiminte(1)|
                     AIO_O_INTE_rawtiminte(1)|
                     AIO_O_INTE_hdmitiminte(1)|
                     AIO_O_INTE_pcmthdinte(1)|
                     AIO_O_INTE_rawthdinte(1)|
                     AIO_O_INTE_hdmithdinte(1)|
                     AIO_O_INTE_draminte3(1)|
                     AIO_O_INTE_draminte2(1)|
                     AIO_O_INTE_draminte1(1)|
                     AIO_O_INTE_draminte0(1)| 
                     AIO_O_INTE_fifointe3(1)|
                     AIO_O_INTE_fifointe2(1)|
                     AIO_O_INTE_fifointe1(1)|
                     AIO_O_INTE_fifointe0(1)|
                     AIO_O_INTE_write_data(1));

    //0xb8006444
    rtd_outl(AIO_O_INTS_reg,
                     AIO_O_INTS_dramints11(1)|
                     AIO_O_INTS_dramints10(1)|
                     AIO_O_INTS_dramints9(1)|
                     AIO_O_INTS_dramints8(1)| 
                     AIO_O_INTS_dramints7(1)|
                     AIO_O_INTS_dramints6(1)|
                     AIO_O_INTS_dramints5(1)|
                     AIO_O_INTS_dramints4(1)| 
                     AIO_O_INTS_fifoints11(1)|
                     AIO_O_INTS_fifoints10(1)|
                     AIO_O_INTS_fifoints9(1)|
                     AIO_O_INTS_fifoints8(1)|
                     AIO_O_INTS_fifoints7(1)|
                     AIO_O_INTS_fifoints6(1)|
                     AIO_O_INTS_fifoints5(1)|
                     AIO_O_INTS_fifoints4(1)|
                     AIO_O_INTS_pcmtimints(1)|
                     AIO_O_INTS_rawtimints(1)|
                     AIO_O_INTS_hdmitimints(1)|
                     AIO_O_INTS_pcmthdints(1)|
                     AIO_O_INTS_rawthdints(1)|
                     AIO_O_INTS_hdmithdints(1)|
                     AIO_O_INTS_dramints3(1)|
                     AIO_O_INTS_dramints2(1)|
                     AIO_O_INTS_dramints1(1)|
                     AIO_O_INTS_dramints0(1)| 
                     AIO_O_INTS_fifoints3(1)|
                     AIO_O_INTS_fifoints2(1)|
                     AIO_O_INTS_fifoints1(1)|
                     AIO_O_INTS_fifoints0(1)|
                     AIO_O_INTS_write_data(0));

    //AO FIFO Control & DMA Enable============================================================================

    BusyWaiting(1000);

    switch(AType)
    {
        case 0: //I2S 8ch-PCM
            //0xb8006090
            rtd_outl(AIO_O_FIFOCTL_reg,
                             AIO_O_FIFOCTL_emptystopen(0)|
                             AIO_O_FIFOCTL_thd(8)|
                             AIO_O_FIFOCTL_en10(1)| //enable HDMI DMA(FIFO7),kist modify
                             AIO_O_FIFOCTL_en9(1)|//enable HDMI DMA(FIFO6),kist modify
                             AIO_O_FIFOCTL_en8(1)|//enable HDMI DMA(FIFO5),kist modify
                             AIO_O_FIFOCTL_en7(1)|//enable HDMI DMA(FIFO4),kist modify
                             AIO_O_FIFOCTL_en6(1)|//enable HDMI DMA(FIFO3),kist modify
                             AIO_O_FIFOCTL_en5(1)|//enable HDMI DMA(FIFO2),kist modify
                             AIO_O_FIFOCTL_en4(1)|//enable HDMI DMA(FIFO1),kist modify
                             AIO_O_FIFOCTL_en3(1)|//enable HDMI DMA(FIFO0),kist modify
                             AIO_O_FIFOCTL_en2(0)|
                             AIO_O_FIFOCTL_en1(0)|
                             AIO_O_FIFOCTL_en0(0));
            break;
        case 1: //I2S 2ch-PCM
            //0xb8006090
            rtd_outl(AIO_O_FIFOCTL_reg,
                             AIO_O_FIFOCTL_emptystopen(0)|
                             AIO_O_FIFOCTL_thd(8)|
                             AIO_O_FIFOCTL_en10(0)|
                             AIO_O_FIFOCTL_en9(0)|
                             AIO_O_FIFOCTL_en8(0)|
                             AIO_O_FIFOCTL_en7(0)|
                             AIO_O_FIFOCTL_en6(0)|
                             AIO_O_FIFOCTL_en5(0)|
                             AIO_O_FIFOCTL_en4(0)|
                             AIO_O_FIFOCTL_en3(0)|
                             AIO_O_FIFOCTL_en2(0)|
                             AIO_O_FIFOCTL_en1(0)|
                             AIO_O_FIFOCTL_en0(1));//Enable PCM DMA(FIFO1),kist modify
            break;
        case 2: //SPDIF PCM
            //0xb8006090
            rtd_outl(AIO_O_FIFOCTL_reg,
                             AIO_O_FIFOCTL_emptystopen(0)|
                             AIO_O_FIFOCTL_thd(8)|
                             AIO_O_FIFOCTL_en10(0)|
                             AIO_O_FIFOCTL_en9(0)|
                             AIO_O_FIFOCTL_en8(0)|
                             AIO_O_FIFOCTL_en7(0)|
                             AIO_O_FIFOCTL_en6(0)|
                             AIO_O_FIFOCTL_en5(0)|
                             AIO_O_FIFOCTL_en4(0)|
                             AIO_O_FIFOCTL_en3(0)|
                             AIO_O_FIFOCTL_en2(0)|
                             AIO_O_FIFOCTL_en1(0)|
                             AIO_O_FIFOCTL_en0(1));//Enable PCM DMA(FIFO1),kist modify
            break;
        case 3: //SPDIF Non-PCM
            //0xb8006090
            rtd_outl(AIO_O_FIFOCTL_reg,
                             AIO_O_FIFOCTL_emptystopen(0)|
                             AIO_O_FIFOCTL_thd(8)|
                             AIO_O_FIFOCTL_en10(0)|
                             AIO_O_FIFOCTL_en9(0)|
                             AIO_O_FIFOCTL_en8(0)|
                             AIO_O_FIFOCTL_en7(0)|
                             AIO_O_FIFOCTL_en6(0)|
                             AIO_O_FIFOCTL_en5(0)|
                             AIO_O_FIFOCTL_en4(0)|
                             AIO_O_FIFOCTL_en3(0)|
                             AIO_O_FIFOCTL_en2(0)|
                             AIO_O_FIFOCTL_en1(1)|//Enable RAW DMA(FIFO2),kist modify
                             AIO_O_FIFOCTL_en0(0));
            break;
        case 4: //HBR
            //0xb8006090
            rtd_outl(AIO_O_FIFOCTL_reg,
                             AIO_O_FIFOCTL_emptystopen(0)|
                             AIO_O_FIFOCTL_thd(8)|
                             AIO_O_FIFOCTL_en10(0)|
                             AIO_O_FIFOCTL_en9(0)|
                             AIO_O_FIFOCTL_en8(0)|
                             AIO_O_FIFOCTL_en7(0)|
                             AIO_O_FIFOCTL_en6(0)|
                             AIO_O_FIFOCTL_en5(0)|
                             AIO_O_FIFOCTL_en4(0)|
                             AIO_O_FIFOCTL_en3(0)|
                             AIO_O_FIFOCTL_en2(1)| //enable HDMI DMA(FIFO3),kist modify
                             AIO_O_FIFOCTL_en1(0)|
                             AIO_O_FIFOCTL_en0(0));
            break;
        default:
            break;
    }

    return;
}
