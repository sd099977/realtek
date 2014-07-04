

#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "TV.h"
#include "TVE_reg.h"
//#include "crt_sys_reg.h"
#include <qc_verify_common.h>
#include <rtd_types_qc.h>


//#######################################################################################################
//
// File Name: HDMI_Audio_set.C
// Description: HDMI initial setting
//
//#######################################################################################################
void SET_HDMI_Audio(UINT8 Video_Format, UINT8 DVI_or_HDMI, UINT8 Sampling_Frequency, UINT8 Sample_Size, UINT8 Audio_Channel_Count, UINT8 Audio_Type, UINT8 CTS_Source)
{
    //0xb800d0bc
    rtd_outl(HDMI_ICR_reg,
                     HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(0)| //0:disable HDMI audio data path
                     HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                     HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));

	//now decided by Audioheader0(0xb800d054[23:16])
    /*if(Audio_Type == 4) //High Bitrate Audio enable
    {
        //0xb800d144
        rtd_outl(HDMI_DUMMY_0_reg, HDMI_DUMMY_dummy((rtd_inl(HDMI_DUMMY_0_reg)&0xfffffffd)|2));
    }
    else
    {
        //0xb800d144
        rtd_outl(HDMI_DUMMY_0_reg, HDMI_DUMMY_dummy((rtd_inl(HDMI_DUMMY_0_reg)&0xfffffffd)|0));
    }*/

    //0xb800d148
    rtd_outl(HDMI_DUMMY_1_reg, HDMI_DUMMY_dummy((rtd_inl(HDMI_DUMMY_1_reg)&0xfffffffe)|1)); //fix highest fs

    switch(Audio_Channel_Count)	 // 1:2ch, 2:3ch, 3:4ch, 4:5ch, 5:6ch, 6:7ch, 7:8ch
    {
        case 1:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(0)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x1)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(0)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(0));
            break;
        case 2:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(3)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x3)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
            break;
        case 3:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(3)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x3)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
             break;
        case 4:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(7)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x7)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
             break;
        case 5:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(7)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x7)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
             break;
        case 6:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(0xf)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(1)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0xf)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
             break;
        case 7:
            rtd_outl(HDMI_ASPCR1_reg,
                             HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(2)|
                             HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(0xf)|
                             HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(0)|
                             HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0xf)|
                             HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(1)|
                             HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(1));
             break;
        default:
            break;
    } //switch(Audio_Channel_Count)

    if(Audio_Type == 4)	//0:I2S 8ch-PCM, 1:I2S 2ch-PCM, 2:SPDIF PCM, 3:SPDIF RAW, 4:HBR
    {

        rtd_outl(HDMI_ASPCR1_reg,
                         HDMI_ASPCR1_write_en6(1)|HDMI_ASPCR1_Audioheader0(9)| //9)|
                         HDMI_ASPCR1_write_en5(1)|HDMI_ASPCR1_samplepresent(0)|
                         HDMI_ASPCR1_write_en4(1)|HDMI_ASPCR1_forcesamplepresent(1)| // 1)|
                         HDMI_ASPCR1_write_en3(1)|HDMI_ASPCR1_b_frame(0x1)|
                         HDMI_ASPCR1_write_en2(1)|HDMI_ASPCR1_forceb_frame(0)|
                         HDMI_ASPCR1_write_en1(1)|HDMI_ASPCR1_audiolayout(0));
     }


    rtd_outl(HDMI_ACACR_reg,
                     HDMI_ACACR_write_en4(1)|HDMI_ACACR_hdmi_pk3map(3)|
                     HDMI_ACACR_write_en3(1)|HDMI_ACACR_hdmi_pk2map(2)|
                     HDMI_ACACR_write_en2(1)|HDMI_ACACR_hdmi_pk1map(1)|
                     HDMI_ACACR_write_en1(1)|HDMI_ACACR_hdmi_pk0map(0));

    if(DVI_or_HDMI==0) //DVI mode
    {
        //0xb800d06c
        rtd_outl(HDMI_ACRPCR_reg,
                         HDMI_ACRPCR_write_en4(0)|HDMI_ACRPCR_fs_div4(0)|
                         HDMI_ACRPCR_write_en3(1)|HDMI_ACRPCR_disablecrp(1)| //1: no CRP will be sent
                         HDMI_ACRPCR_write_en2(0)|HDMI_ACRPCR_cts_source(0)|
                         HDMI_ACRPCR_write_en1(0)|HDMI_ACRPCR_n_value(0));
    }
    else //HDMI mode
    {
        //0xb800d06c
        rtd_outl(HDMI_ACRPCR_reg,
                         HDMI_ACRPCR_write_en4(0)|HDMI_ACRPCR_fs_div4(0)|
                         HDMI_ACRPCR_write_en3(1)|HDMI_ACRPCR_disablecrp(0)| //0: CRP will be sent
                         HDMI_ACRPCR_write_en2(0)|HDMI_ACRPCR_cts_source(0)|
                         HDMI_ACRPCR_write_en1(0)|HDMI_ACRPCR_n_value(0));
    }

    //========================================================================================================
    switch(Video_Format)
    {
        case 1 : //TV NTSC
        case 2 : //TV 525p
        case 3 : //TV PAL
        case 4 : //TV 625p
            switch(Sampling_Frequency)	 // 1:32k, 2:44.1k, 3:48k, 4:88.2k, 5:96k, 6:176.4k, 7:192k
            {
                case 1://32k
                case 3://48k
                case 5://96k
                case 7://192k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(27000));
                    break;
                case 2://44.1k
                case 4://88.2k
                case 6://176.4k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(30000));
                    break;
                default:
                    break;
            }
            break;
        case 5 : //TV 720p60
        case 6 : //TV 1080i50
        case 7 : // TV 1080i60
        case 18 : //TV 1080p24
        case 20 : //TV 720p50
            switch(Sampling_Frequency)
            {
                case 1://32k
                case 3://48k
                case 5://96k
                case 7://192k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(74250));
                    break;
                case 2://44.1k
                case 4://88.2k
                case 6://176.4k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(82500));
                    break;
                default:
                    break;
            }
            break;
        case 21 : //TV 1080p50
        case 22 : //TV 1080p60
            switch(Sampling_Frequency)
            {
                case 1://32k
                case 3://48k
                case 5://96k
                case 7://192k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(148500));
                    break;
                case 2://44.1k
                case 4://88.2k
                case 6://176.4k
                    //0xb800d070
                    rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(165000));
                    break;
                default:
                    break;
            }        
	     break;		
        default:
            break;
    }

    if(Audio_Type == 4)	//0:I2S 8ch-PCM, 1:I2S 2ch-PCM, 2:SPDIF PCM, 3:SPDIF RAW, 4:HBR
    {
        //0xb800d070
        rtd_outl(HDMI_ACRPCTSR_reg, HDMI_ACRPCTSR_ctssw(74250));
    }

    //========================================================================================================
    switch(Sampling_Frequency)
    {
        case 1: //32k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(4096)); //32k
            break;
        case 2: //44.1k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(6272)); //44.1k
            break;
        case 3: //48k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(6144)); //48k
            break;
        case 4: //88.2k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(12544)); //88.2k
            break;
        case 5: //96k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(12288)); //96k
            break;
        case 6: //176.4k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(25088)); //176.4k
            break;
        case 7: //192k
            //0xb800d06c
            rtd_outl(HDMI_ACRPCR_reg,
                             HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                             HDMI_ACRPCR_write_en3(0)|HDMI_ACRPCR_disablecrp(0)| //1: no CRP will be sent
                             HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)|
                             HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(24576)); //192k
            break;
        default:
            break;
        }

    if(Audio_Type == 4)
    {
        //0xb800d06c
        rtd_outl(HDMI_ACRPCR_reg,
                         HDMI_ACRPCR_write_en4(1)|HDMI_ACRPCR_fs_div4(0)|
                         HDMI_ACRPCR_write_en3(1)|HDMI_ACRPCR_disablecrp(0)| //0: Clock Recovery Package will be sent
                         HDMI_ACRPCR_write_en2(1)|HDMI_ACRPCR_cts_source(CTS_Source)| //0: use CTShw, 1: based on CTSsw 
                         HDMI_ACRPCR_write_en1(1)|HDMI_ACRPCR_n_value(24576)); //192k to 768k
    }

    //0xb800d078
    rtd_outl(HDMI_GCPCR_reg, HDMI_GCPCR_enablegcp(0)|
                     HDMI_GCPCR_gcp_clearavmute(1)|
                     HDMI_GCPCR_gcp_setavmute(1)|
                     HDMI_GCPCR_write_data(0));

    //0xb800d07c
    rtd_outl(HDMI_ORP6PH_reg, HDMI_ORP6PH_once_pkt(0));
    //0xb800d080
    rtd_outl(HDMI_ORP6W_0_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d084
    rtd_outl(HDMI_ORP6W_1_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d088
    rtd_outl(HDMI_ORP6W_2_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d08c
    rtd_outl(HDMI_ORP6W_3_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d090
    rtd_outl(HDMI_ORP6W_4_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d094
    rtd_outl(HDMI_ORP6W_5_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d098
    rtd_outl(HDMI_ORP6W_6_reg, HDMI_ORP6W_once_pkt(0));
    //0xb800d09c
    rtd_outl(HDMI_ORP6W_7_reg, HDMI_ORP6W_once_pkt(0));

    //0xb800d0a0
    rtd_outl(HDMI_RPCR_reg,
                     HDMI_RPCR_write_en6(1)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(1)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(0)|HDMI_RPCR_prp3period(0)|
                     HDMI_RPCR_write_en3(0)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(1)|HDMI_RPCR_prp1period(0)|
                     HDMI_RPCR_write_en1(0)|HDMI_RPCR_prp0period(0));

    //0xb800d0a4
    rtd_outl(HDMI_RPEN_reg,
                     HDMI_RPEN_enprpkt5(1)|
                     HDMI_RPEN_enprpkt4(1)|
                     HDMI_RPEN_enprpkt3(0)|
                     HDMI_RPEN_enprpkt2(0)| //Metadata package clear by HDMI_video_set
                     HDMI_RPEN_enprpkt1(1)| //Audio InfoFrame package clear
                     HDMI_RPEN_enprpkt0(0)| //AVI InfoFrame package clear by HDMI_video_set
                     HDMI_RPEN_write_data(0));

    if(Audio_Type==3 || Audio_Type==4) Audio_Channel_Count=0;
    HDMI_gen_audio_infoframe(Audio_Channel_Count);

    BusyWaiting(1000);

    //Enable & Config AIO
    if(DVI_or_HDMI==1) //HDMI mode
    {
        SET_AO(Sampling_Frequency, Sample_Size, Audio_Channel_Count, Audio_Type);
    }

    return;
}
