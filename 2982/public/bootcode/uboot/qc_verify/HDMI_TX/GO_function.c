#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "TVE_reg.h"


extern void BusyWaiting(UINT32);

void GO_function(UINT32 display_mode, UINT8 DVI_or_HDMI, UINT8 Timing_Gen)
{
    if(Timing_Gen)
    {
        //0xb800d020
        rtd_outl(HDMI_CHNL_SEL_reg, rtd_inl(HDMI_CHNL_SEL_reg)|HDMI_CHNL_SEL_timing_gen_en_mask);
    }

    switch(display_mode)
    {
        case 1 ://480i
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(0)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(0)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 2 ://480p
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(0)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(0)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 3 ://576i
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(0)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(0)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 4 ://576p
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(0)|TVE_SYNCGEN_RST_p_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en1(0)|TVE_SYNCGEN_RST_h_sync_go(0));
            break;
        case 5 ://720p60
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 6 ://1080i50
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 7 ://1080i60
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 18 ://1080p24
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 20 ://720p50
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 21 ://1080p50
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
            break;
        case 22 ://1080p60
            //0xb8018000
            rtd_outl(TVE_SYNCGEN_RST_reg,
                             TVE_SYNCGEN_RST_write_en5(0)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en4(0)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en3(0)|TVE_SYNCGEN_RST_i_sync_go(0)|
                             TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(1)|
                             TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(1));
	     break;
        default:
            break;
    } //switch(display_mode)

    //0xb800d158
    rtd_outl(HDMI_DPC1_reg,
                     HDMI_DPC1_write_en2(1)|HDMI_DPC1_dp_vfch(1)|
                     HDMI_DPC1_write_en1(0)|HDMI_DPC1_pp(0));

    BusyWaiting(1000);

    if(DVI_or_HDMI == 1)
    {
        //HDMI Audio GO=================================================================================
        //0xb800d0bc
        rtd_outl(HDMI_ICR_reg,
                         HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(1)| //1:enable HDMI audio data path
                         HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                         HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));
    }
    //0xb8006304
    /* temperately mark by kist
    rtd_outl(AIO_O_GO_reg,
                     AIO_O_GO_goacdac(0)|
                     AIO_O_GO_gohdmi(1)|
                     AIO_O_GO_goi2s(1)| //enable I2S output
                     AIO_O_GO_gospf(1)); //S-PDIF output*/
    
    return;
}
