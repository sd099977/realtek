#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "TV.h"
#include "TVE_reg.h"
#include "crt_sys_reg.h"
#include <qc_verify_common.h>
#include <rtd_types_qc.h>
#include "mhl_tx_cbus_reg.h"

UINT8 case_mode = 22;
UINT8 rgb_mode = 1;
UINT8 DVIorHDMI_flag=1; //0:DVI, 1:HDMI
UINT8 xvYCC=0; //Extended-gamut YCC color space
UINT8 PixelColorFormat=2; //0:RGB444, 1:Reserved, 2:YCbCr444, 3:YCbCr422
UINT8 DeepColorEnable=0; //0:disable 1:enable
UINT8 DeepColorDepth=4; //0:not indicated, 4:24bits, 5:30bits, 6:36bits, other:reserved
UINT8 TimingGen=1;        //0: TVE 1:HDMI
UINT8 Enable3D=0;
UINT8 Format3D=0;         //0: frame packing 1: field alternative 2: line alternative 3: side-by-side
                           //4: l+depth 5: l+depth+graphics+graphics-depth 6: top-and-down
                           //8: side-by-side(half)
bool mhl_pp_mode_en = 0;	//only for MHL

UINT8 AudioCodingType=0; //Refer to CEA-861B table 19.
UINT8 AudioChannelCount=1; // 1:2ch, 2:3ch, 3:4ch, 4:5ch, 5:6ch, 6:7ch, 7:8ch
UINT8 SamplingFrequency=3; // 1:32k, 2:44.1k, 3:48k, 4:88.2k, 5:96k, 6:176.4k, 7:192k
UINT8 SampleSize=3; // 1:16bit, 2:20bit, 3:24bit
UINT8 AudioType=1; //0:I2S 8ch-PCM, 1:I2S 2ch-PCM, 2:SPDIF PCM, 3:SPDIF RAW, 4:HBR
UINT8 CTSSource=0; //0:by CTShw, 1:by CTSsw

UINT8 Test_Mode=1; //(Audio InfoFrame)1:Refer to Stream Header
UINT32 mode;
UINT8 RGB_flag=0;
UINT8 mv_flag=1;
unsigned int sum;
unsigned int *sumbuf = &sum;
UINT8 *UART_flag = 1;

#define CEC_CTS_7_9 1
#define GDI_POWER_SAVING 0
#define Lookback_mode 0
#define QCINFO_CMD_BUFFER_SIZE  128
//#define OUTPUT_SRC_SELECT_HDMI 1		// 1:hdmi , 0:mhl
#define QC_Code_For_Verify_Chip 0		// 1:output by key in command , 0:normal QC code flow

#define MHL_TX_CBUS_EN 1

enum hdmi_tx_cmd {
    HDMI_TX_CMD_TEST_EXIT = 0,
    HDMI_TX_CMD_TEST_PROTOCOL,
    HDMI_TX_CMD_TEST_CEC,
    HDMI_TX_CMD_TEST_SCRIPT,
    HDMI_TX_CMD_ITEM_NUM
};

enum hdmi_tx_sub_cmd {
    HDMI_TX_SUB_CMD_NONE = 0,
    HDMI_TX_SUB_CMD_CONFIG_VIDEO_PARAM,
    HDMI_TX_SUB_CMD_CONFIG_AUDIO_PARAM,
    HDMI_TX_SUB_CMD_SET_AND_GO,
    HDMI_TX_SUB_CMD_ITEM_NUM
};

INT8* cmd_str_array[HDMI_TX_CMD_ITEM_NUM] = {"exit", "hdmi", "cec", "script"};
INT8* hdmi_tx_sub_cmd[HDMI_TX_SUB_CMD_ITEM_NUM] = {"none", "video", "audio", "go"};
INT32 hdmi_tx_argc = 0;
INT8 **hdmi_tx_argv = NULL;


//###########################################################################################################################
void BusyWaiting(UINT32 count)
{
    UINT32 i=0;
    if(count>10000)
        count=10000;
    while(count>0)
    {
        i=5; //about 200uS
        while(i>0) i--;
        count--;
    }
}

//###########################################################################################################################
static void set_tve_pattern_gen(UINT32 format)
{
    switch (format)
    {
        case 1 :
            //TV_525i(colorbar, RGB_mode, video_format);
            break;
        case 2 :
            //TV_525p(colorbar);
            break;
        case 3 :
            //TV_625i(colorbar, RGB_mode);
            break;
        case 4 :
            //TV_625p(colorbar);
            break;
        case 5 :
           // TV_720p_60(colorbar);
            break;
        case 6 :
           // TV_1080_50i(colorbar);
            break;
        case 7 :
            //TV_1080_60i(colorbar);
            break;
        case 18 :
            //TV_1080_24p(colorbar);
            break;
        case 20 :
            //TV_720p_50(colorbar);
            break;
        case 21 :
            //TV_1080p_50();
            break;
        case 22 :
            TVE_TV_1080p60();
            break;
        default:
            break;
    }
}

static void phy_default_setting()
{
    //adams setting PHY
    //rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
    // 0x15f61891 = (1 << 0) + (2 << 3) + (0 << 6) + (1 << 7) + (0 << 9) + (0 << 10) + (3 << 11) +
    //              (0 << 14) + (6 << 16) + (3 << 20) + (3 << 22) + (1 << 24) + (1 << 26) + (1 << 28) +
    //              (0 << 29)
    //
    // 0x15409010 = (0 << 0) + (0 << 1) + (2 << 3) + (0 << 5) + (0 << 6) + (0 << 7) + (0 << 9) +
    //              (4 << 10) + (0 << 13) + (2 << 14) + (0 << 16) + (0 << 18) + (1 << 22) + (0 << 23) +
    //              (1 << 24) + (1 << 26) + (1 << 28)
    //
    // 0x0db10b77 = (1 << 0) + (3 << 1) + (1 << 4) + (1 << 5) + (1 << 6) + (0 << 7) + (3 << 8) + (1 << 11) +
    //              (0 << 12) + (0 << 13) + (0 << 15) + (1 << 16) + (0 << 18) + (0 << 19) + (3 << 20) +
    //              (1 << 23) + (1 << 24) + (1 << 26) + (1 << 27) + (0 << 29)
    //
    // 0x00053622 = (2 << 0) + (0 << 3) + (2 << 4) + (0 << 7) + (0 << 8) + (1 << 9) + (5 << 10) + (1 << 13) +
    //              (20 << 14) + (0 << 20)
    //
    // 0x000f0a22 = (0 << 0) + (1 << 1) + (0 << 3) + (0 << 4) + (1 << 5) + (2 << 8) + (1 << 11) + (240 << 12) +
    //              (0 << 28)
    //
    // 0x00540600 = (1 << 9) + (1 << 10) + (0 << 11) + (0 << 12) + (0 << 17) + (1 << 18) + (1 << 20) + (1 << 22) +
    //              (0 << 24)
    rtd_outl(0xb80001c0, 0x15fc6492);  //output amplitude, de-emphasis 0x15f61891->0x15fc6491
    rtd_outl(0xb80001c4, 0x15409010);  // TX_PLL_PU, VCO frequency range
    //rtd_outl(0xb80001c4, 0x15c09012);  // TX_PLL_PU, VCO frequency range
    //rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN
    rtd_outl(0xb80001cc, 0x00053622);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(20), PIXEL_DIV16(2), TMDS_DIV16(2)
    rtd_outl(0xb80001d0, 0x01800942);  // TV_PLL_PU 0x000f0a22 -> 0x000f0e22
    rtd_outl(0xb80001c8, 0xbb10b77);  // LDO_PLL_PU, LDO_TMDS_PU 0x9b10b77 -> 0xb810b71
    rtd_maskl(0xb80001c8, 0xfbffffff, 0x1 << 26);  //LDO_CCO_PU
    ////////////rtd_outl(0xb80001d4, 0x00540600);  // TV_PLL frequency tuning enable

    rtd_outl(0xb80001d4, 0x00560600);  // TV_PLL frequency tuning enable, REG_PLLDDS_DDSEN enable
    //rtd_outl(0xb8000024, 0x00004000);
    //rtd_outl(0xb8000028, 0x00000000); //reg_tve_hdmi_div_sel, reg_hdmi_tmds_div


    rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
    //rtd_outl(0xb80001d0, 0x000f0922);  // TV_PLL_PU
    //rtd_outl(0xb80001c4, 0x00c09012);  // TX_PLL_PU
    //rtd_outl(0xb80001c8, 0x05810b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
    rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN ////// take off
    //rtd_outl(0xb80001cc, 0x00051622);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(20), PIXEL_DIV16(2), TMDS_DIV16(2)
    rtd_outl(0xb8000024, 0x00004000);    //// take off
    rtd_outl(0xb8000028, 0x00000000);   //reg_tve_hdmi_div_sel, reg_hdmi_tmds_div  //// take off
#if 0
    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00dfdfdf);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00212121);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00ffffff);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00dfdfdf);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00212121);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00ffffff);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00ffffff);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00212121);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00ffffff);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00000000);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00212121);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x00000);
#elif 0
    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00555555);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00aaaaaa);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x00000);
#elif 1
    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x00000);
#else
    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00010101);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00101010);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x00000);	
#endif

/*#if OUTPUT_SRC_SELECT_HDMI
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x3c0000);    //Lane0~3 enable
#else
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x080000);    //Lane1 enable
#endif
*/
}

void Display(UINT32 mode, UINT32 colorbar, UINT32 RGB_mode, UINT32 video_format, bool pp_mode_en)
{
    if (TimingGen)
    {

    }
    else
    {
        set_tve_pattern_gen(mode);
    }

    SET_HDMI_Video(mode, PixelColorFormat, DVIorHDMI_flag, DeepColorEnable, DeepColorDepth, xvYCC, TimingGen, Enable3D, Format3D, pp_mode_en);
    ///SET_HDMI_Audio(mode, DVIorHDMI_flag, SamplingFrequency, SampleSize, AudioChannelCount, AudioType, CTSSource);
    GO_function(mode, DVIorHDMI_flag, TimingGen);
    return;
}

//###########################################################################################################################
void Run_loop(UINT8 mode, UINT32 RGB_mode, UINT32 video_format, UINT32 colorbar, UINT32 Timing_Gen, UINT8 Enable_3D, UINT8 Format_3D)
{
    int flagTopBottom = 0;
    int flagLeftRight = 0;

    switch(mode)
    {
        case 1: //525i
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(1)|
                                         VO_V1_INDEX_3D_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(480));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(240));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(240));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(480));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(0));
                    if(Timing_Gen)
                    {
                        //0xb8005000
                        rtd_outl(VO_MODE_reg,
                                         VO_MODE_ch2i(0)|
                                         VO_MODE_ch2(0)|
                                         VO_MODE_ch1i(0)|
                                         VO_MODE_ch1(1)|
                                         VO_MODE_write_data(1));
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005000
                        rtd_outl(VO_MODE_reg,
                                         VO_MODE_ch2i(0)|
                                         VO_MODE_ch2(0)|
                                         VO_MODE_ch1i(0)|
                                         VO_MODE_ch1(1)|
                                         VO_MODE_write_data(1));
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(1)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(1)|
                                     VO_V1_INDEX_y(0));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(480));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(480));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //20120413 kist sync
                    rtd_outl(VO_CH2_BUF_reg,
                                     VO_CH2_BUF_write_en2(0)|VO_CH2_BUF_th(0)|
                                     VO_CH2_BUF_write_en1(1)|VO_CH2_BUF_b(256));


                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    if(Timing_Gen)
                    {
                        //0xb80057fc
                        rtd_outl(VO_CH1_reg,
                                         VO_CH1_itop(0)|
                                         VO_CH1_ireint(0)|
                                         VO_CH1_top(0)|
                                         VO_CH1_reint(1)|
                                         VO_CH1_write_data(1));
                    }
                    else
                    {
                        //0xb80057fc
                        rtd_outl(VO_CH1_reg,
                                         VO_CH1_itop(0)|
                                         VO_CH1_ireint(0)|
                                         VO_CH1_top(0)|
                                         VO_CH1_reint(1)|
                                         VO_CH1_write_data(1));
                    }
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }

#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1) //3D----------------------------------------
                    {
                        if(Format3D==0)
                        {
                            //***L odd frame***
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(Timing_Gen)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));

                                flagTopBottom = 1;
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& flagTopBottom)
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));

                                flagTopBottom = 0;
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                        else
                        {
                            if(TVE_INTST_get_intst_i(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(1)|
                                                 TVE_INTST_intst_i(1)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                flagTopBottom = TVE_SYNCGEN_STATUS_I_get_i_field(*(volatile unsigned int *)TVE_SYNCGEN_STATUS_I_reg);
                                //0xb8018024
                                rtd_outl(TVE_INTPOS_I_reg,
                                                 TVE_INTPOS_I_write_en2(1)|TVE_INTPOS_I_int_vpos(flagTopBottom ? 2 : 270)|
                                                 TVE_INTPOS_I_write_en1(1)|TVE_INTPOS_I_int_hpos(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1-flagTopBottom));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 2: //480p
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(1)|
                                         VO_V1_INDEX_3D_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(480));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(240));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(240));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(1)|
                                         VO_V1_INDEX_y(0));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(480));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(480));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(1)|
                                     VO_V1_INDEX_y(0));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(480));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(480));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                  //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(Timing_Gen)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                        else
                        {
                            if(TVE_INTST_get_intst_p(*(volatile unsigned int *)TVE_INTST_reg))
                            {
                                //0xb8018020
                                rtd_outl(TVE_INTST_reg,
                                                 TVE_INTST_intst_h(0)|
                                                 TVE_INTST_intst_i(0)|
                                                 TVE_INTST_intst_p(1)|
                                                 TVE_INTST_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 3: //576i
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(3)|
                                         VO_V1_INDEX_3D_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(576));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(288));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(288));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(576));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(1)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(3)|
                                     VO_V1_INDEX_y(2));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(576));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(576));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(0)|
                                     VO_CH1_ireint(0)|
                                     VO_CH1_top(0)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(1));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));

                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            //***L odd frame***
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& !flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));

                            flagTopBottom = 1;
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1-flagTopBottom));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));

                            flagTopBottom = 0;
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1-flagTopBottom));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(Timing_Gen)
                        {
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                        else
                        {
                            if(VO_INTST_get_i_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(1)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 4: //576p
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(3)|
                                         VO_V1_INDEX_3D_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(576));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(720)|
                                         VO_V1_SIZE_h(288));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(720)|
                                         VO_M1_SIZE_h(288));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(3)|
                                         VO_V1_INDEX_y(2));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(360)|
                                         VO_V1_SIZE_h(576));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(360)|
                                         VO_M1_SIZE_h(576));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(3)|
                                     VO_V1_INDEX_y(2));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(720)|
                                     VO_V1_SIZE_h(576));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(720)|
                                     VO_M1_SIZE_h(576));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 5: //720p_60
        case 20: //720p_50
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(5)|
                                         VO_V1_INDEX_3D_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1280)|
                                         VO_V1_SIZE_h(720));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1280)|
                                         VO_M1_SIZE_h(720));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1280)|
                                         VO_V1_SIZE_h(360));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1280)|
                                         VO_M1_SIZE_h(360));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(640)|
                                         VO_V1_SIZE_h(720));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(640)|
                                         VO_M1_SIZE_h(720));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(0)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(5)|
                                         VO_V1_INDEX_y(4));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(1280)|
                                     VO_V1_SIZE_h(720));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(1280)|
                                     VO_M1_SIZE_h(720));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
              }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 6: //1080i_50
        case 7: //1080i_60
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(7)|
                                         VO_V1_INDEX_3D_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(540));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(270));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(270));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(1)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(960)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(960)|
                                         VO_M1_SIZE_h(540));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    if(Timing_Gen)
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(0));
                    }
                    else
                    {
                        //0xb8005004
                        rtd_outl(VO_OUT_reg,
                                         VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                         VO_OUT_write_en1(1)|VO_OUT_p(1));
                    }
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(0)|
                                     VO_V1_d3_dbw(0)|
                                     VO_V1_d3_dup(0)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(0)|
                                     VO_V1_gfx(0)|
                                     VO_V1_di(0)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(0)|
                                     VO_V1_vs_near(0)|
                                     VO_V1_vs_yodd(0)|
                                     VO_V1_vs_codd(0)|
                                     VO_V1_hs(0)|
                                     VO_V1_hs_yodd(0)|
                                     VO_V1_hs_codd(0)|
                                     VO_V1_topfield(0)|
                                     VO_V1_dmaweave(0)|
                                     VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                    //0xb8005058
                    rtd_outl(VO_V1_SIZE_reg,
                                     VO_V1_SIZE_w(1920)|
                                     VO_V1_SIZE_h(540));
                    //0xb8005788
                    rtd_outl(VO_M1_SIZE_reg,
                                     VO_M1_SIZE_w(1920)|
                                     VO_M1_SIZE_h(540));
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));

                }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb801802c
                rtd_outl(TVE_INTPOS_P2_reg,
                                 TVE_INTPOS_P2_write_en2(1)|TVE_INTPOS_P2_int_vpos(565)|
                                 TVE_INTPOS_P2_write_en1(1)|TVE_INTPOS_P2_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            //***L odd frame***
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R odd frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***L even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 1;
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            //***R even frame***
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagTopBottom)
                            {
                                flagTopBottom = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(0));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagTopBottom)
                            {
                                flagTopBottom = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005020
                                rtd_outl(VO_V1_reg,
                                                 VO_V1_d3_dbh(0)|
                                                 VO_V1_d3_dbw(0)|
                                                 VO_V1_d3_dup(0)|
                                                 VO_V1_st(0)|
                                                 VO_V1_cd(0)|
                                                 VO_V1_gfx(0)|
                                                 VO_V1_di(0)|
                                                 VO_V1_f422(0)|
                                                 VO_V1_vs(0)|
                                                 VO_V1_vs_near(0)|
                                                 VO_V1_vs_yodd(0)|
                                                 VO_V1_vs_codd(0)|
                                                 VO_V1_hs(0)|
                                                 VO_V1_hs_yodd(0)|
                                                 VO_V1_hs_codd(0)|
                                                 VO_V1_topfield(1)|
                                                 VO_V1_dmaweave(0)|
                                                 VO_V1_write_data(1));
                                //0xb80057fc
                                rtd_outl(VO_CH1_reg,
                                                 VO_CH1_itop(0)|
                                                 VO_CH1_ireint(0)|
                                                 VO_CH1_top(1)|
                                                 VO_CH1_reint(0)|
                                                 VO_CH1_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&& !flagTopBottom)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));

                            flagTopBottom = 1;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(0));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg)&&flagTopBottom==1)
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));

                            flagTopBottom = 0;
                            //0xb8005020
                            rtd_outl(VO_V1_reg,
                                             VO_V1_d3_dbh(0)|
                                             VO_V1_d3_dbw(0)|
                                             VO_V1_d3_dup(0)|
                                             VO_V1_st(0)|
                                             VO_V1_cd(0)|
                                             VO_V1_gfx(0)|
                                             VO_V1_di(0)|
                                             VO_V1_f422(0)|
                                             VO_V1_vs(0)|
                                             VO_V1_vs_near(0)|
                                             VO_V1_vs_yodd(0)|
                                             VO_V1_vs_codd(0)|
                                             VO_V1_hs(0)|
                                             VO_V1_hs_yodd(0)|
                                             VO_V1_hs_codd(0)|
                                             VO_V1_topfield(1)|
                                             VO_V1_dmaweave(0)|
                                             VO_V1_write_data(1));
                            //0xb80057fc
                            rtd_outl(VO_CH1_reg,
                                             VO_CH1_itop(0)|
                                             VO_CH1_ireint(0)|
                                             VO_CH1_top(1)|
                                             VO_CH1_reint(0)|
                                             VO_CH1_write_data(1));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                        }
                        if(Timing_Gen)
                        {
                            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(1)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                        else
                        {
                            if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                            {
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(1)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(0)|
                                                 VO_INTST_write_data(0));
                            }
                        }
                    }
                }
            }
#endif
            break;

        case 18: //1080p24
            if(colorbar==4)
            {
                if(Enable3D==1)
                {
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(1)|
                                     VO_MODE_ch2(1)|
                                     VO_MODE_ch1i(1)|
                                     VO_MODE_ch1(0)|
                                     VO_MODE_write_data(0));
                    //0xb8005000
                    rtd_outl(VO_MODE_reg,
                                     VO_MODE_ch2i(0)|
                                     VO_MODE_ch2(0)|
                                     VO_MODE_ch1i(0)|
                                     VO_MODE_ch1(1)|
                                     VO_MODE_write_data(1));
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(1)|
                                     VO_MIX1_csr(1)|
                                     VO_MIX1_osd2(1)|
                                     VO_MIX1_osd1(1)|
                                     VO_MIX1_sub1(1)|
                                     VO_MIX1_v2(1)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(1)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(0));
                    //0xb8005008
                    rtd_outl(VO_MIX1_reg,
                                     VO_MIX1_i_vbi(0)|
                                     VO_MIX1_vbi(0)|
                                     VO_MIX1_csr(0)|
                                     VO_MIX1_osd2(0)|
                                     VO_MIX1_osd1(0)|
                                     VO_MIX1_sub1(0)|
                                     VO_MIX1_v2(0)|
                                     VO_MIX1_v1(1)|
                                     VO_MIX1_pic(0)|
                                     VO_MIX1_bg(1)|
                                     VO_MIX1_write_data(1));
                    //0xb8005014
                    rtd_outl(VO_3D_reg,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
                    //0xb8005020
                    rtd_outl(VO_V1_reg,
                                     VO_V1_d3_dbh(1)|
                                     VO_V1_d3_dbw(1)|
                                     VO_V1_d3_dup(1)|
                                     VO_V1_st(1)|
                                     VO_V1_cd(1)|
                                     VO_V1_gfx(1)|
                                     VO_V1_di(1)|
                                     VO_V1_f422(1)|
                                     VO_V1_vs(1)|
                                     VO_V1_vs_near(1)|
                                     VO_V1_vs_yodd(1)|
                                     VO_V1_vs_codd(1)|
                                     VO_V1_hs(1)|
                                     VO_V1_hs_yodd(1)|
                                     VO_V1_hs_codd(1)|
                                     VO_V1_topfield(1)|
                                     VO_V1_dmaweave(1)|
                                     VO_V1_write_data(0));
                    if(Format3D==0)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005028
                        rtd_outl(VO_V1_INDEX_3D_reg,
                                         VO_V1_INDEX_3D_w_c(0)|
                                         VO_V1_INDEX_3D_w_y(0)|
                                         VO_V1_INDEX_3D_c(7)|
                                         VO_V1_INDEX_3D_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(1080));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(1080));
                    }
                    if(Format3D==6)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(1)|
                                         VO_V1_d3_dbw(0)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(1920)|
                                         VO_V1_SIZE_h(540));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(1920)|
                                         VO_M1_SIZE_h(540));
                    }
                    if(Format3D==8)
                    {
                        //0xb8005020
                        rtd_outl(VO_V1_reg,
                                         VO_V1_d3_dbh(0)|
                                         VO_V1_d3_dbw(1)|
                                         VO_V1_d3_dup(0)|
                                         VO_V1_st(0)|
                                         VO_V1_cd(0)|
                                         VO_V1_gfx(0)|
                                         VO_V1_di(0)|
                                         VO_V1_f422(1)|
                                         VO_V1_vs(0)|
                                         VO_V1_vs_near(0)|
                                         VO_V1_vs_yodd(0)|
                                         VO_V1_vs_codd(0)|
                                         VO_V1_hs(0)|
                                         VO_V1_hs_yodd(0)|
                                         VO_V1_hs_codd(0)|
                                         VO_V1_topfield(0)|
                                         VO_V1_dmaweave(0)|
                                         VO_V1_write_data(1));
                        //0xb8005024
                        rtd_outl(VO_V1_INDEX_reg,
                                         VO_V1_INDEX_w_c(0)|
                                         VO_V1_INDEX_w_y(0)|
                                         VO_V1_INDEX_c(7)|
                                         VO_V1_INDEX_y(6));
                        //0xb8005058
                        rtd_outl(VO_V1_SIZE_reg,
                                         VO_V1_SIZE_w(960)|
                                         VO_V1_SIZE_h(1080));
                        //0xb8005788
                        rtd_outl(VO_M1_SIZE_reg,
                                         VO_M1_SIZE_w(960)|
                                         VO_M1_SIZE_h(1080));
                    }
                    //0xb8005794
                    rtd_outl(VO_V1_XY_reg,
                                     VO_V1_XY_x(0)|
                                     VO_V1_XY_y(0));
                    //0xb80057f4
                    rtd_outl(VO_CHI_BUF_reg,
                                     VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                     VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                    //0xb80057fc
                    rtd_outl(VO_CH1_reg,
                                     VO_CH1_itop(1)|
                                     VO_CH1_ireint(1)|
                                     VO_CH1_top(1)|
                                     VO_CH1_reint(1)|
                                     VO_CH1_write_data(0));
                    //0xb80056e0
                    rtd_outl(VO_DMA_reg,
                                     VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                     VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                     VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                     VO_DMA_write_en1(0)|VO_DMA_l(0));
                }
                else
                {
                //0xb8005000
                rtd_outl(VO_MODE_reg,
                                 VO_MODE_ch2i(1)|
                                 VO_MODE_ch2(1)|
                                 VO_MODE_ch1i(1)|
                                 VO_MODE_ch1(0)|
                                 VO_MODE_write_data(0));
                //0xb8005000
                rtd_outl(VO_MODE_reg,
                                 VO_MODE_ch2i(0)|
                                 VO_MODE_ch2(0)|
                                 VO_MODE_ch1i(0)|
                                 VO_MODE_ch1(1)|
                                 VO_MODE_write_data(1));
                if(Timing_Gen)
                {
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(1)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(0));
                }
                else
                {
                    //0xb8005004
                    rtd_outl(VO_OUT_reg,
                                     VO_OUT_write_en3(1)|VO_OUT_h(0)|
                                     VO_OUT_write_en2(1)|VO_OUT_i(0)|
                                     VO_OUT_write_en1(1)|VO_OUT_p(1));
                }
                //0xb8005008
                rtd_outl(VO_MIX1_reg,
                                 VO_MIX1_i_vbi(1)|
                                 VO_MIX1_csr(1)|
                                 VO_MIX1_osd2(1)|
                                 VO_MIX1_osd1(1)|
                                 VO_MIX1_sub1(1)|
                                 VO_MIX1_v2(1)|
                                 VO_MIX1_v1(1)|
                                 VO_MIX1_pic(1)|
                                 VO_MIX1_bg(1)|
                                 VO_MIX1_write_data(0));
                //0xb8005008
                rtd_outl(VO_MIX1_reg,
                                 VO_MIX1_i_vbi(0)|
                                 VO_MIX1_vbi(0)|
                                 VO_MIX1_csr(0)|
                                 VO_MIX1_osd2(0)|
                                 VO_MIX1_osd1(0)|
                                 VO_MIX1_sub1(0)|
                                 VO_MIX1_v2(0)|
                                 VO_MIX1_v1(1)|
                                 VO_MIX1_pic(0)|
                                 VO_MIX1_bg(1)|
                                 VO_MIX1_write_data(1));
                //0xb8005020
                rtd_outl(VO_V1_reg,
                                 VO_V1_d3_dbh(1)|
                                 VO_V1_d3_dbw(1)|
                                 VO_V1_d3_dup(1)|
                                 VO_V1_st(1)|
                                 VO_V1_cd(1)|
                                 VO_V1_gfx(1)|
                                 VO_V1_di(1)|
                                 VO_V1_f422(1)|
                                 VO_V1_vs(1)|
                                 VO_V1_vs_near(1)|
                                 VO_V1_vs_yodd(1)|
                                 VO_V1_vs_codd(1)|
                                 VO_V1_hs(1)|
                                 VO_V1_hs_yodd(1)|
                                 VO_V1_hs_codd(1)|
                                 VO_V1_topfield(1)|
                                 VO_V1_dmaweave(1)|
                                 VO_V1_write_data(0));
                //0xb8005020
                rtd_outl(VO_V1_reg,
                                 VO_V1_d3_dbh(0)|
                                 VO_V1_d3_dbw(0)|
                                 VO_V1_d3_dup(0)|
                                 VO_V1_st(0)|
                                 VO_V1_cd(0)|
                                 VO_V1_gfx(0)|
                                 VO_V1_di(0)|
                                 VO_V1_f422(1)|
                                 VO_V1_vs(0)|
                                 VO_V1_vs_near(0)|
                                 VO_V1_vs_yodd(0)|
                                 VO_V1_vs_codd(0)|
                                 VO_V1_hs(0)|
                                 VO_V1_hs_yodd(0)|
                                 VO_V1_hs_codd(0)|
                                 VO_V1_topfield(0)|
                                 VO_V1_dmaweave(0)|
                                 VO_V1_write_data(1));
                    //0xb8005024
                    rtd_outl(VO_V1_INDEX_reg,
                                     VO_V1_INDEX_w_c(0)|
                                     VO_V1_INDEX_w_y(0)|
                                     VO_V1_INDEX_c(7)|
                                     VO_V1_INDEX_y(6));

                //0xb8005058
                rtd_outl(VO_V1_SIZE_reg,
                                 VO_V1_SIZE_w(1920)|
                                 VO_V1_SIZE_h(1080));
                //0xb8005788
                rtd_outl(VO_M1_SIZE_reg,
                                 VO_M1_SIZE_w(1920)|
                                 VO_M1_SIZE_h(1080));
                //0xb8005794
                rtd_outl(VO_V1_XY_reg,
                                 VO_V1_XY_x(0)|
                                 VO_V1_XY_y(0));
                //0xb80057f4
                rtd_outl(VO_CHI_BUF_reg,
                                 VO_CHI_BUF_write_en2(0)|VO_CHI_BUF_th(0)|
                                 VO_CHI_BUF_write_en1(1)|VO_CHI_BUF_b(256));
                //0xb80057fc
                rtd_outl(VO_CH1_reg,
                                 VO_CH1_itop(1)|
                                 VO_CH1_ireint(1)|
                                 VO_CH1_top(1)|
                                 VO_CH1_reint(1)|
                                 VO_CH1_write_data(0));
                //0xb80056e0
                rtd_outl(VO_DMA_reg,
                                 VO_DMA_write_en4(1)|VO_DMA_num_req_4(0)|
                                 VO_DMA_write_en3(1)|VO_DMA_dyn_id(0)|
                                 VO_DMA_write_en2(0)|VO_DMA_ref_mix(0)|
                                 VO_DMA_write_en1(0)|VO_DMA_l(0));
              }
                //0xb8018040
                rtd_outl(TVE_AV_CTRL_reg,
                                 TVE_AV_CTRL_h_colorbar_ebl(1)|
                                 TVE_AV_CTRL_h_black_ebl(1)|
                                 TVE_AV_CTRL_i_colorbar_ebl(1)|
                                 TVE_AV_CTRL_p_colorbar_ebl(1)|
                                 TVE_AV_CTRL_i_black_ebl(1)|
                                 TVE_AV_CTRL_p_black_ebl(1)|
                                 TVE_AV_CTRL_write_data(0));
                //0xb8018028
                rtd_outl(TVE_INTPOS_P1_reg,
                                 TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
                                 TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));
                //0xb8018020
                rtd_outl(TVE_INTST_reg,
                                 TVE_INTST_intst_h(1)|
                                 TVE_INTST_intst_i(1)|
                                 TVE_INTST_intst_p(1)|
                                 TVE_INTST_write_data(0));
            }
#if 1
            while(*UART_flag==1)
            {
                //temper mark by kist
                //UART_READ();
                if(colorbar==4)
                {
                    if(Enable3D==1)
                    {
                        if(Format3D==0)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && !flagLeftRight)
                            {
                                flagLeftRight = 1;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(0));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                            if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV_reg) && flagLeftRight)
                            {
                                flagLeftRight = 0;
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(1)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==6)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(1)|
                                                 VO_3D_side_by_side(0)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(Format3D==8)
                        {
                            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                            {
                                //0xb800d278
                                rtd_outl(HDMI_INTSTV_reg,
                                                 HDMI_INTSTV_vendupdated(0)|
                                                 HDMI_INTSTV_vsyncupdated(0));
                                //0xb8005014
                                rtd_outl(VO_3D_reg,
                                                 VO_3D_top_and_bottom(0)|
                                                 VO_3D_side_by_side(1)|
                                                 VO_3D_right(0)|
                                                 VO_3D_write_data(1));
                                //0xb8005864
                                rtd_outl(VO_INTST_reg,
                                                 VO_INTST_h_under(0)|
                                                 VO_INTST_i_under(0)|
                                                 VO_INTST_p_under(0)|
                                                 VO_INTST_sub1(0)|
                                                 VO_INTST_wbfin(0)|
                                                 VO_INTST_m2fin(0)|
                                                 VO_INTST_m1fin(1)|
                                                 VO_INTST_write_data(0));
                                //0xb8005018
                                rtd_outl(VO_FC_reg,
                                                 VO_FC_wbgo(0)|
                                                 VO_FC_m2go(0)|
                                                 VO_FC_m1go(1)|
                                                 VO_FC_write_data(1));
                            }
                        }
                        if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                        {
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(1)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(0)|
                                             VO_INTST_write_data(0));
                        }
                    }
                    else
                    {
                        if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV_reg))
                        {
                            //0xb800d278
                            rtd_outl(HDMI_INTSTV_reg,
                                             HDMI_INTSTV_vendupdated(0)|
                                             HDMI_INTSTV_vsyncupdated(0));
                            //0xb8005864
                            rtd_outl(VO_INTST_reg,
                                             VO_INTST_h_under(0)|
                                             VO_INTST_i_under(0)|
                                             VO_INTST_p_under(0)|
                                             VO_INTST_sub1(0)|
                                             VO_INTST_wbfin(0)|
                                             VO_INTST_m2fin(0)|
                                             VO_INTST_m1fin(1)|
                                             VO_INTST_write_data(0));
                            //0xb8005018
                            rtd_outl(VO_FC_reg,
                                             VO_FC_wbgo(0)|
                                             VO_FC_m2go(0)|
                                             VO_FC_m1go(1)|
                                             VO_FC_write_data(1));
                            if(Timing_Gen)
                            {
                                if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(1)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(0)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                            else
                            {
                                if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST_reg))
                                {
                                    //0xb8005864
                                    rtd_outl(VO_INTST_reg,
                                                     VO_INTST_h_under(0)|
                                                     VO_INTST_i_under(0)|
                                                     VO_INTST_p_under(1)|
                                                     VO_INTST_sub1(0)|
                                                     VO_INTST_wbfin(0)|
                                                     VO_INTST_m2fin(0)|
                                                     VO_INTST_m1fin(0)|
                                                     VO_INTST_write_data(0));
                                }
                            }
                        }
                    }
                }
            }
#endif
            break;
    }
    return;
}

static int get_hdmi_tx_sub_cmd_enum(INT8 *str)
{
    int i, ret = HDMI_TX_SUB_CMD_NONE;
    for (i = 0; i < HDMI_TX_SUB_CMD_ITEM_NUM; i++)
    {
        if (strcmp(hdmi_tx_sub_cmd[i], str) == 0)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

static void config_video_param(void)
{
    //hdmi video case_mode DeepColorEnable DeepColorDepth TimingGen Enable3D Format3D rgb_mode
    case_mode = strtoul((const INT8 *) (hdmi_tx_argv[2]), (INT8 **) NULL, 10);
    DeepColorEnable = strtoul((const INT8 *) (hdmi_tx_argv[3]), (INT8 **) NULL, 10);
    DeepColorDepth = strtoul((const INT8 *) (hdmi_tx_argv[4]), (INT8 **) NULL, 10);
    TimingGen = strtoul((const INT8 *) (hdmi_tx_argv[5]), (INT8 **) NULL, 10);
    Enable3D = strtoul((const INT8 *) (hdmi_tx_argv[6]), (INT8 **) NULL, 10);
    Format3D = strtoul((const INT8 *) (hdmi_tx_argv[7]), (INT8 **) NULL, 10);
    rgb_mode = strtoul((const INT8 *) (hdmi_tx_argv[8]), (INT8 **) NULL, 10);
    mhl_pp_mode_en = strtoul((const INT8 *) (hdmi_tx_argv[9]), (INT8 **) NULL, 10);
    printf("%d, %d, %d, %d, %d, %d, %d, %d\n",
            case_mode, DeepColorEnable, DeepColorDepth,
            TimingGen, Enable3D, Format3D, rgb_mode, mhl_pp_mode_en);
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x00000);
}

static void config_audio_param(void)
{
    //hdmi audio SamplingFrequency SampleSize AudioChannelCount AudioType CTSSource
    SamplingFrequency = strtoul((const INT8 *) (hdmi_tx_argv[2]), (INT8 **) NULL, 10);
    SampleSize = strtoul((const INT8 *) (hdmi_tx_argv[3]), (INT8 **) NULL, 10);
    AudioChannelCount = strtoul((const INT8 *) (hdmi_tx_argv[4]), (INT8 **) NULL, 10);
    AudioType = strtoul((const INT8 *) (hdmi_tx_argv[5]), (INT8 **) NULL, 10);
    CTSSource = strtoul((const INT8 *) (hdmi_tx_argv[6]), (INT8 **) NULL, 10);
    printf("%d, %d, %d, %d, %d\n",
            SamplingFrequency, SampleSize, AudioChannelCount,
            AudioType, CTSSource);
}


static int mhl_tx_cbus_connect(void)
{
    //CBUS_MSC_CMD_PARAM_ST param;
    cbus_dis1_RBUS dis1;
    cbus_phy0_RBUS phy0;
    cbus_test_RBUS test;
    cbus_RBUS cbus0;
    fw0_req_01_RBUS fw0_req_01;
    cbus_dis4_RBUS dis4;
    msc_reg_31_RBUS msc_31;
    msc_reg_30_RBUS msc_30;
    cbus_msc_06_RBUS cbus_msc_06;
    int ret, rst = 0, cnt = 5000;
    UINT32 path_en_cnt = 500;


    dis1.regValue = rtd_inl(CBUS_DIS1_VADDR);
    if (!dis1.both_path_en)
    {
        printk("- verB\n");
        test.regValue = rtd_inl(CBUS_TEST_VADDR);
        test.fw_control_r10k = 0;
        rtd_outl(CBUS_TEST_VADDR, test.regValue);

        phy0.regValue = rtd_inl(CBUS_PHY0_VADDR);
        phy0.reg_mhl_r10k_test = 1;
        phy0.reg_mhl_r1k_det = 1;
        phy0.reg_r1k_vth_sel = 1;
        phy0.reg_cbus_strc = 4;
        phy0.reg_mhl_vsel = 2;
        rtd_outl(CBUS_PHY0_VADDR, phy0.regValue);

        dis4.regValue = 0;
        rtd_outl(CBUS_DIS4_VADDR, dis4.regValue);

        printk("- status = 0x%08x, cbus_phy0 = 0x%08x\n", rtd_inl(CBUS_DIS4_VADDR), rtd_inl(CBUS_PHY0_VADDR));
        //CBUS
        fw0_req_01.regValue = rtd_inl(FW0_REQ_01_VADDR);
        fw0_req_01.check_fw0_msg_processing = 0;
        rtd_outl(FW0_REQ_01_VADDR, fw0_req_01.regValue);

        cbus0.regValue = rtd_inl(CBUS_VADDR);
        cbus0.enable = 1;
        rtd_outl(CBUS_VADDR, cbus0.regValue);

        printk("- after cbus enable status = 0x%08x, 1k stus = 0x%08x, dect = 0x%08x\n", rtd_inl(CBUS_DIS4_VADDR), rtd_inl(0xb8062c20), rtd_inl(CBUS_PHY0_VADDR));
        while (1)
        {
            dis4.regValue = rtd_inl(CBUS_DIS4_VADDR);
            if ((dis4.src3_10 == 1) ||
                (dis4.src3_09 == 1) ||
                (dis4.src3_08 == 1) ||
                (dis4.src3_07 == 1) ||
                (dis4.src3_06 == 1) ||
                (dis4.src3_05 == 1) ||
                (dis4.src3_04 == 1) ||
                (dis4.src3_03 == 1) ||
                (dis4.src3_02 == 1) ||
                (dis4.src3_01 == 1) ||
                (dis4.src3_00 == 1))
            {
                printk("- src3 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
                phy0.regValue = rtd_inl(CBUS_PHY0_VADDR);
                phy0.reg_mhl_r1k_det = 0;
                phy0.reg_r1k_vth_sel = 0;
                rtd_outl(CBUS_PHY0_VADDR, phy0.regValue);
                printk("- first off 1k det = 0x%08x, then status = 0x%08x, 1k stus = 0x%08x\n", rtd_inl(CBUS_PHY0_VADDR), rtd_inl(CBUS_DIS4_VADDR), rtd_inl(0xb8062c20));
            }
            else if (dis4.src1 == 1)
            {
                printk("- src1 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
            }
            else if (dis4.src2 == 1)
            {
                printk("- src2 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
            }
            else if (dis4.src0 == 1)
            {
                printk("- src0 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
            }
            else if ((dis4.irq_src6_7 == 0) && (dis4.src4 == 1))
            {
                printk("- src4 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
            }
            else if ((dis4.irq_src6_7 == 1) && (dis4.src5 == 0))
            {
                printk("- happen src3 / src4 time out to src7, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
                dis4.irq_src6_7 = 0;
                rtd_outl(CBUS_DIS4_VADDR, dis4.regValue);

                phy0.regValue = rtd_inl(CBUS_PHY0_VADDR);
                phy0.reg_mhl_r1k_det = 1;
                phy0.reg_r1k_vth_sel = 1;
                rtd_outl(CBUS_PHY0_VADDR, phy0.regValue);
                printk("- first on 1k det = 0x%08x, then status = 0x%08x, 1k stus = 0x%08x\n", rtd_inl(CBUS_PHY0_VADDR), rtd_inl(CBUS_DIS4_VADDR), rtd_inl(0xb8062c20));
            }
            else if ((dis4.irq_src6_7 == 1) && (dis4.src5 == 1))
            {
                printk("- happen src5 time out to src7, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
                dis4.irq_src6_7 = 0;
                rtd_outl(CBUS_DIS4_VADDR, dis4.regValue);

                phy0.regValue = rtd_inl(CBUS_PHY0_VADDR);
                phy0.reg_mhl_r1k_det = 1;
                phy0.reg_r1k_vth_sel = 1;
                rtd_outl(CBUS_PHY0_VADDR, phy0.regValue);
                printk("- first on 1k det = 0x%08x, then status = 0x%08x, 1k stus = 0x%08x\n", rtd_inl(CBUS_PHY0_VADDR), rtd_inl(CBUS_DIS4_VADDR), rtd_inl(0xb8062c20));
            }
            else if ((dis4.irq_src6_7 == 0) && (dis4.src5 == 1))
            {
                printk("- src5 state, status = 0x%08x, 1k stus = 0x%08x\n", dis4.regValue, rtd_inl(0xb8062c20));
                break;
            }
            // cnt--;
        }

        printk("- wait path enable\n");
        while (path_en_cnt)
        {
            msc_31.regValue = rtd_inl(MSC_REG_31_VADDR);
            msc_30.regValue = rtd_inl(MSC_REG_30_VADDR);
            cbus_msc_06.regValue = rtd_inl(CBUS_MSC_06_VADDR);
            if ((msc_31.path_en && cbus_msc_06.irq_path_en_chg) || 
                (msc_30.dcap_rdy && cbus_msc_06.irq_dcap_rdy_chg))
            {
                printk("- path enable flag = %d, rdy flag = %d\n", msc_31.path_en, msc_30.dcap_rdy);
                cbus_msc_06.irq_path_en_chg = 0;
                cbus_msc_06.irq_dcap_rdy_chg = 0;
                rtd_outl(CBUS_MSC_06_VADDR,cbus_msc_06.regValue);
                break;
            }
            path_en_cnt--;
        }

        // param.cmd = MSC_CMD_WRITE_STAT_SET_INT;
        // param.offset = 0x31;
        // param.data0 = 0x8;
        // param.data1 = 0;
        // param.data_len = 0;
        // ret = set_msc_cmd_case0(&param);
        // check_return_err_code(ret);

        //CBUS both_en = 1
        if (cnt)
        {
            dis1.regValue = rtd_inl(CBUS_DIS1_VADDR);
            dis1.both_path_en = 1;
            rtd_outl(CBUS_DIS1_VADDR, dis1.regValue);

            printk("- wait src6\n");
            while ((rtd_inl(CBUS_DIS4_VADDR) & 0x00002000) == 0);
        }
        else
        {
            printk("- time out\n");
            rst = -1;
        }
    }

    return rst;

}


static void system_init(void)
{
    // CRT initial start
    printf("\n- system init\n");

    //HDMI TX
    rtd_maskl(0xb8000000, 0xffffefff, 0x1000);  //HDMI TX rstn
    rtd_maskl(0xb800000c, 0xfffffeff, 0x100);   //HDMI TX clk en

    //HDMI RX
    rtd_maskl(0xb8000008, 0xfffdffff, 0x20000); //HDMI RX rstn
    rtd_maskl(0xb800000c, 0xfffffffd, 0x2); //HDMI RX clk en
    rtd_maskl(0xb8007B40, 0xFDFFFFFF,0x02000000); //HDMI bandgap power 1:on 0:off

    //HDMI AIO
    rtd_maskl(0xb8000000, 0xffff7fff, 0x8000);  //AIO rstn
    rtd_maskl(0xb800000c, 0xfffffbff, 0x400);   //AIO clk en

    //APLL ADC
    rtd_maskl(0xb8000008, 0xffffffef, 0x10);    //APLL ADC rstn
    rtd_maskl(0xb8000014, 0xfeffffff, 0x1000000);   //APLL ADC clk en

    //TVE
    /*adam
    rtd_maskl(0xb8000000, 0xfffbffff, 0x40000); //TVE rstn
    rtd_maskl(0xb800000c, 0xffffffef, 0x10);    //TVE clk en
    */
    rtd_maskl(0xb8000000, 0xfff7ffff, 0x80000); //TVE rstn
    rtd_maskl(0xb8000004, 0xfff7ffff, 0x80000); //TVE clkgen reset
    rtd_maskl(0xb800000c, 0xffffbfff, 0x4000); //TVE clk en

    //Display2Tve
    rtd_maskl(0xb8000008, 0xfffffffd, 0x2); // DISP rstn
    rtd_maskl(0xb8000014, 0xfffffff7, 0x8); //DISP clk en
    rtd_maskl(0xb8000014, 0xffbfffff, 0x400000);    //Display2TVE clk en

    rtd_outl(0xb8020104,0x00050009);  // APLL_ADC LDO power, for PLL27X

    //-------- Module Clock & Reset Enable ---------
    rtd_outl(0xb8000000, 0xffffffff); //
    rtd_outl(0xb8000004, 0xffffffff); //
    rtd_outl(0xb8000008, 0xffffffff); //
    rtd_outl(0xb800000c, 0xffffffff); //
    rtd_outl(0xb8000010, 0xffffffff); //
    rtd_outl(0xb8000014, 0xffffffff); //

    //CRT set
    rtd_maskl(0xb8060034, 0xffffffcf, 0x30); // CBUS TX rstn
    rtd_maskl(0xb8060044, 0xfffdffcf, 0x20030); // CBUS TX clk en

    // CRT initial end
    phy_default_setting();

#if !OUTPUT_SRC_SELECT_HDMI // MHL mode
    //CBUS PHY set
    printf("\n- mhl init\n");
    rtd_outl(0xb8062c1c,0x0f0a4e30); //CBUS PHY set
    rtd_maskl(0xb8062c1c,0xffffffbf,0x40); //CBUS PHY enable
    rtd_maskl(0xb8062c1c,0xfffffc7f,0x80); //CBUS mhl_r1_ok = 1
    rtd_maskl(0xb8062c1c,0xffffffe3,0x8); //CBUS mhl_r1_ok = 1
    rtd_maskl(0xb80001c8, ~0x00080000, 0x00080000); // MHL enable

   // rtd_maskl(0xb8062e64,0xffffffe3,0x00); //CBUSTX debug sel
    //*****************Test_en_bit0~ Test_en_bit35***********************************************
    //rtd_maskl(0xb806022c,0x07ffffff,0x10000000); //ST_dbg[25]
    //rtd_maskl(0xb8060228,0xffffc1ff,0x400); //ST_dbg[26]
    //rtd_maskl(0xb8060228,0xff83ffff,0x80000); //ST_dbg[27]
    //rtd_maskl(0xb8060248,0x0fffc1ff,0x400); //ST_dbg[28]

#if MHL_TX_CBUS_EN
    mhl_tx_cbus_connect();
#endif
#endif
}


static void set_and_go(void)
{
    UINT32 mode, colorbar, pattern;
    UINT32 RGB_mode, video_format;
    UINT32 T_COUNT=0;
    UINT8 i=0;
    UINT32 test_pattern[]={1,22};
    int result=0;

    //mode 1: //TV NTSC-M
    //mode 2: //TV 525p
    //mode 3: //TV PAL
    //mode 4: //TV 626p
    //mode 5: //TV 720p60Hz
    //mode 6: //TV 1080i50Hz
    //mode 7: //TV 1080i60Hz
    //mode 18: //TV 1080p24Hz
    //mode 20: //TV 720p50Hz
    //mode 21: //TV 1080p50Hz
    //mode 22: //TV 1080p60Hz
    //Default display type=============================================
    //mode = 22; //4

    mode = case_mode;
    RGB_mode = rgb_mode;
    //mode =test_pattern[1];
    //DeepColorEnable=0;
    //DeepColorDepth=4; //0:not indicated, 4:24bits, 5:30bits, 6:36bits, other:reserved
    //TimingGen=0;        //0: TVE 1:HDMI
    //Enable3D=0;
    //Format3D=0; //0:frame packing 1:field alternative 2:Line alternative 3:Side-by-Side(Full) 4:L+depth 5:L+depth+graphics... 6:Top/bottom 8:Side-by-Side(Half)
    colorbar = 4; // not use
    pattern=0; // not use
    //RGB_mode = 1;
    video_format = 1; // not use
    Display(mode, colorbar, RGB_mode, video_format, mhl_pp_mode_en);
    printf("- display\n");
}

void HDMI_Test(void){
    UINT32 mode, colorbar, pattern;
    UINT32 RGB_mode, video_format;
    UINT32 T_COUNT=0;
    UINT8 i=0;
    UINT32 test_pattern[]={1,22};
    int result=0, sub_cmd;

    sub_cmd = get_hdmi_tx_sub_cmd_enum(*(&hdmi_tx_argv[1]));

    switch (sub_cmd) {

        case HDMI_TX_SUB_CMD_CONFIG_VIDEO_PARAM:
            printf("- config video param\n");
            config_video_param();
            break;
        case HDMI_TX_SUB_CMD_CONFIG_AUDIO_PARAM:
            printf("- config audio param\n");
            config_audio_param();
            break;
        case HDMI_TX_SUB_CMD_SET_AND_GO:
            printf("- set and go\n");
            set_and_go();
            break;
        default:
            printf("- none\n");
            break;
    }

    return SUCCESS;
}
#if 0
BOOL CCec_Test(void)
{
    //Set RESET and CLOCK enable=======================================
    rtd_maskl(SYS_CLOCK_ENABLE1_reg,~_BIT8, _BIT8); //enable hdmi clock
    rtd_maskl(SYS_SOFT_RESET1_reg,~_BIT12, _BIT12); //hdmi reset disable
    rtd_maskl(SYS_CLOCK_ENABLE2_reg,~_BIT11, _BIT11); //enable cec clock
    rtd_maskl(SYS_SOFT_RESET2_reg,~_BIT21, _BIT21); //cec reset disable

#if Lookback_mode
    UINT32 CEC_DATA[2][4];
    UINT8 i,timeoutcnt=255;

    CEC_DATA[0][0]=0x00112233;
    CEC_DATA[0][1]=0x44556677;
    CEC_DATA[0][2]=0x8899aabb;
    CEC_DATA[0][3]=0xccddee00;

    //rtd_outl(HDMI_CEC_CR0_ADDR,0xc714fc1f);       //CEC loop back enable, RBUS=202MHz, addr is 0x7
    rtd_outl(HDMI_CEC_CR0_ADDR,0xc714221f);     //CEC loop back enable, RBUS=27MHz, addr is 0x7
    rtd_outl(HDMI_CEC_TxCR0_ADDR,0x0507c0);     //CEC TX addr is 0x5, dest addr is 0x7
    rtd_outl(HDMI_CEC_RxTCR0_ADDR,0x8abc2a50);      //start low 0x8c->0x8a,data period 0x52->0x50 for 27MHz
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT20,_BIT20);      //CEC TX addr enable

    rtd_outl(HDMI_CEC_TxDR1_ADDR,CEC_DATA[0][0]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR2_ADDR,CEC_DATA[0][1]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR3_ADDR,CEC_DATA[0][2]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR4_ADDR,CEC_DATA[0][3]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR0_ADDR,0xf);                  //CEC TX FIFO num


    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT14,_BIT14);      //CEC RX reset
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT14,_BIT14);      //CEC TX reset
    udelay(1000);
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT14,0x0);     //CEC RX reset
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT14,0x0);     //CEC TX reset
    udelay(1000);
    rtd_maskl(HDMI_CEC_TxDR0_ADDR,~_BIT6,_BIT6);        //CEC TX FIFO num double buffer load
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT15,_BIT15);      //CEC RX reset
    udelay(1000);
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT15,_BIT15);      //CEC TX enable
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT6,_BIT6);        //clr RX interrupt flag
    do                                          //wait RX ok flag
    {
        udelay(5000);
        if((rtd_inl(HDMI_CEC_RxCR0_ADDR) & _BIT6))
            break;
    } while (--timeoutcnt);
    if (timeoutcnt==0)
        printk("wait CEC RX timeout!!!\n");

    CEC_DATA[1][0]=rtd_inl(HDMI_CEC_RxDR1_ADDR);
    CEC_DATA[1][1]=rtd_inl(HDMI_CEC_RxDR2_ADDR);
    CEC_DATA[1][2]=rtd_inl(HDMI_CEC_RxDR3_ADDR);
    CEC_DATA[1][3]=rtd_inl(HDMI_CEC_RxDR4_ADDR);

    for (i=0;i<4;i++)
        {
        if (CEC_DATA[0][i]!=CEC_DATA[1][i])
            return FALSE;
        }
    return TRUE;
#else
#if CEC_CTS_7_9
    UINT32 CEC_DATA[2][4];
    UINT32 timeoutcnt=25500;
    UINT32 init_addr,broadcast_flag;
    UINT8  i=0,rx_len=0,j=0;

while(i<2){
    printk("CEC Init ...\n");
    i++;
    CEC_DATA[0][0]=0x00112233;
    CEC_DATA[0][1]=0x44556677;
    CEC_DATA[0][2]=0x8899aabb;
    CEC_DATA[0][3]=0xccddee00;

    //rtd_outl(HDMI_CEC_CR0_ADDR,0x4414fc1f);       //CEC enable, RBUS=202MHz, addr is 0x0
    rtd_outl(HDMI_CEC_CR0_ADDR,0x4414221f);     //CEC enable, RBUS=27MHz, addr is 0x4
    rtd_outl(HDMI_CEC_TxCR0_ADDR,0x0507c0);     //CEC TX addr is 0x5, dest addr is 0x7
    rtd_outl(HDMI_CEC_RxTCR0_ADDR,0x8abc2a50);      //start low 0x8c->0x8a,data period 0x52->0x50 for 27MHz
    //rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT20,_BIT20);        //CEC TX addr enable
    rtd_maskl(HDMI_CEC_RTCR0_ADDR,0x0000ffff,0x05670000);       //LA3=5,LA2=6,LA1=7, for DMP use

    rtd_outl(HDMI_CEC_TxDR1_ADDR,CEC_DATA[0][0]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR2_ADDR,CEC_DATA[0][1]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR3_ADDR,CEC_DATA[0][2]);       //CEC TX FIFO
    rtd_outl(HDMI_CEC_TxDR4_ADDR,CEC_DATA[0][3]);       //CEC TX FIFO
    //rtd_outl(HDMI_CEC_TxDR0_ADDR,0xf);                    //CEC TX FIFO num

    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT14,_BIT14);      //CEC RX reset
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT14,_BIT14);      //CEC TX reset
    udelay(1000);
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT14,0x0);     //CEC RX normal
    rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT14,0x0);     //CEC TX normal
    udelay(1000);
    //rtd_maskl(HDMI_CEC_TxDR0_ADDR,~_BIT6,_BIT6);      //CEC TX FIFO num double buffer load
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT15,_BIT15);      //CEC RX enable
    udelay(1000);
    //rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT15,_BIT15);        //CEC TX enable
    rtd_maskl(HDMI_CEC_RxCR0_ADDR,~_BIT6,_BIT6);        //clr RX interrupt flag

#if GDI_POWER_SAVING
    rtd_outl(GDI_CEC_COMPARE_OPCODE_01,0xff);
    rtd_outl(GDI_CEC_SEND_OPCODE_01,0x00);
    rtd_outl(GDI_CEC_COMPARE_OPCODE_02,0x83);
    rtd_outl(GDI_CEC_SEND_OPCODE_02,0x84);
    rtd_outl(GDI_CEC_OPERAND_04,0x10);
    rtd_outl(GDI_CEC_OPERAND_05,0x00);
    rtd_outl(GDI_CEC_SEND_OPERAND_NUMBER_01,0x00);      //opcode number = 0
    rtd_outl(GDI_CEC_SEND_OPERAND_NUMBER_02,0x02);      //opcode number = 2
    rtd_outl(GDI_CEC_OPCODE_ENABLE,0x03);               //compare opcode1,opcode2 enable
    rtd_maskl(GDI_POWER_SAVING_MODE,~_BIT8,_BIT8);      //Irq enable
#endif

    do                                          //wait RX ok flag
    {
        udelay(5000);
        if((rtd_inl(HDMI_CEC_RxCR0_ADDR) & _BIT6))
            break;
    } while (--timeoutcnt);
    if (timeoutcnt==0)
        printk("wait CEC RX timeout!!!\n");

    init_addr=(rtd_inl(HDMI_CEC_RxCR0_ADDR)&0x0f00);
    broadcast_flag = (rtd_inl(HDMI_CEC_RxCR0_ADDR)>>31);
    rx_len= rtd_inl(HDMI_CEC_RxCR0_ADDR)&0x1f;
    CEC_DATA[1][0]=rtd_inl(HDMI_CEC_RxDR1_ADDR);
    CEC_DATA[1][1]=rtd_inl(HDMI_CEC_RxDR2_ADDR);
    CEC_DATA[1][2]=rtd_inl(HDMI_CEC_RxDR3_ADDR);
    CEC_DATA[1][3]=rtd_inl(HDMI_CEC_RxDR4_ADDR);

    printk("init_addr = %x\n",init_addr);
    printk("broadcast_flag = %x\n",broadcast_flag);
    printk("rx_len = %d\n",rx_len);
    if (rx_len>0)
        printk("CEC_DATA[1][0] = %x\n",CEC_DATA[1][0]);

    if(rx_len>4)
        printk("CEC_DATA[1][1] = %x\n",CEC_DATA[1][1]);

    if(rx_len>8)
        printk("CEC_DATA[1][2] = %x\n",CEC_DATA[1][2]);

    if(rx_len>12)
        printk("CEC_DATA[1][3] = %x\n",CEC_DATA[1][3]);

#if GDI_POWER_SAVING
    if((rtd_inl(GDI_POWER_SAVING_MODE) & _BIT31))
        printk("GDI_POWER_SAVING_MODE IRQ PENDING\n");

    rtd_maskl(GDI_POWER_SAVING_MODE,~_BIT31,_BIT31);        //clr Irq
    j=20;
    do
    {
        udelay(5000);

    } while (--j);
#else

    if (((CEC_DATA[1][0]>>24) == 0xff)&&(broadcast_flag == 0))//cmd=Abort
    {
        CEC_DATA[0][0]=(0x00<<24);
        rtd_outl(HDMI_CEC_TxDR1_ADDR,CEC_DATA[0][0]);       //CEC TX FIFO
        rtd_outl(HDMI_CEC_TxDR0_ADDR,0x1);                  //CEC TX FIFO num=1
        rtd_maskl(HDMI_CEC_TxDR0_ADDR,~_BIT6,_BIT6);        //CEC TX FIFO num double buffer load
        rtd_maskl(HDMI_CEC_TxCR0_ADDR,~0x00000f00,init_addr);       //dest addr
        rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT15,_BIT15);      //CEC TX enable
        printk("CEC TX send <Feature Abort >\n");
        do                                          //wait TX ok flag
        {
            udelay(5000);
            if((rtd_inl(HDMI_CEC_TxCR0_ADDR) & _BIT6))
                break;
        } while (--timeoutcnt);

        if (timeoutcnt==0)
            printk("wait CEC TX timeout!!!\n");
    }
    else if (((CEC_DATA[1][0]>>24)== 0x83)&&(broadcast_flag == 0))//cmd=Give Physical Address
    {
        init_addr = (0xf<<8);//broadcast
        CEC_DATA[0][0]=(0x84<<24)|(0x10<<16)|(0x00<<8);//physical address = 0x1000
        rtd_outl(HDMI_CEC_TxDR1_ADDR,CEC_DATA[0][0]);       //CEC TX FIFO
        rtd_outl(HDMI_CEC_TxDR0_ADDR,0x3);                  //CEC TX FIFO num=3
        rtd_maskl(HDMI_CEC_TxDR0_ADDR,~_BIT6,_BIT6);        //CEC TX FIFO num double buffer load
        rtd_maskl(HDMI_CEC_TxCR0_ADDR,~0x00000f00,init_addr);       //dest addr
        rtd_maskl(HDMI_CEC_TxCR0_ADDR,~_BIT15,_BIT15);      //CEC TX enable
        printk("CEC TX send <Report Physical Address> = %x\n",CEC_DATA[0][0]);
        do                                          //wait TX ok flag
        {
            udelay(5000);
            if((rtd_inl(HDMI_CEC_TxCR0_ADDR) & _BIT6))
                break;
        } while (--timeoutcnt);

        if (timeoutcnt==0)
            printk("wait CEC TX timeout!!!\n");
    }
#endif
}
#endif//CEC_CTS_7_9

#endif
    return TRUE;
}
#endif
#if 0
BOOL MBIST_CHECK(void)
{
    UINT8 time_counter=250;
    //clk disable
    rtd_maskl(SYS_CLOCK_ENABLE1_reg,~_BIT8,0);      //hdmi clock disable
    //reset hdmi
    rtd_maskl(SYS_SOFT_RESET1_reg,~_BIT12,0);       //hdmi reset enable
    udelay(100);
    rtd_maskl(SYS_SOFT_RESET1_reg,~_BIT12,_BIT12);  //hdmi reset disable

//Bist mode start
       //hdmi1->bist0
       //hdmi2->bist1
    rtd_maskl(SYS_CRT_BIST_MODE_reg,~(_BIT14|_BIT13),(_BIT14|_BIT13));//hdmi1,hdmi2 bist enable
    //clk enable
    rtd_maskl(SYS_CLOCK_ENABLE1_reg,~_BIT8,_BIT8);  //hdmi clock enable
    do
    {
        udelay(1000);
        if ((rtd_inl(HDMI_BIST0_ST_reg)&_BIT0)&&(rtd_inl(HDMI_BIST1_ST_reg)&_BIT0))     //wait bist finish
            break;
    }
    while(--time_counter);

    if (time_counter==0)
    {
        printk("hdmi1 or hdmi2 BIST time out!!!\n");
        return FALSE;
    }

    if ((rtd_inl(HDMI_BIST0_ST_reg)&_BIT1)&&(rtd_inl(HDMI_BIST1_ST_reg)&_BIT1)) //check success or fail
        return FALSE;

    rtd_maskl(SYS_CRT_BIST_MODE_reg,~(_BIT14|_BIT13),0);//hdmi1,hdmi2 bist disable
//Bist mode end

    //clk disable
    rtd_maskl(SYS_CLOCK_ENABLE1_reg,~_BIT8,0);      //hdmi clock disable
    //reset hdmi
    rtd_maskl(SYS_SOFT_RESET1_reg,~_BIT12,0);       //hdmi reset enable
    udelay(100);
    rtd_maskl(SYS_SOFT_RESET1_reg,~_BIT12,_BIT12);  //hdmi reset disable

//Drf mode start
       //hdmi1->drf0
       //hdmi2->drf1
    rtd_maskl(SYS_CRT_BIST_EN_reg,~(_BIT14|_BIT13),(_BIT14|_BIT13));//hdmi1,hdmi2 drf enable

    //clk enable
    rtd_maskl(SYS_CLOCK_ENABLE1_reg,~_BIT8,_BIT8);  //hdmi clock enable
    do
    {
        udelay(1000);
        if ((rtd_inl(HDMI_DRF0_ST_reg)&_BIT16)&&(rtd_inl(HDMI_DRF1_ST_reg)&_BIT16))     //wait drf start pause
            break;
    }
    while(--time_counter);

    if (time_counter==0)
    {
        printk("hdmi1 or hdmi2 DRF time out!!!\n");
        return FALSE;
    }

    rtd_maskl(SYS_CRT_DRF_TEST_RESUME_reg,~(_BIT14|_BIT13),(_BIT14|_BIT13));//resume
    udelay(100);
    rtd_maskl(SYS_CRT_DRF_TEST_RESUME_reg,~(_BIT14|_BIT13),0);

    do
    {
        udelay(1000);
        if ((rtd_inl(HDMI_DRF0_ST_reg)&_BIT16)&&(rtd_inl(HDMI_DRF1_ST_reg)&_BIT16))     //wait drf start pause
            break;
    }
    while(--time_counter);

    if (time_counter==0)
    {
        printk("hdmi1 or hdmi2 DRF2 time out!!!\n");
        return FALSE;
    }

    rtd_maskl(SYS_CRT_DRF_TEST_RESUME_reg,~(_BIT14|_BIT13),(_BIT14|_BIT13));//resume
    udelay(100);
    rtd_maskl(SYS_CRT_DRF_TEST_RESUME_reg,~(_BIT14|_BIT13),0);

    do
    {
        udelay(1000);
        if ((rtd_inl(HDMI_DRF0_ST_reg)&_BIT0)&&(rtd_inl(HDMI_DRF1_ST_reg)&_BIT0))       //wait drf done
            break;
    }
    while(--time_counter);

    if (time_counter==0)
    {
        printk("hdmi1 or hdmi2 DRF3 time out!!!\n");
        return FALSE;
    }

    if ((rtd_inl(HDMI_DRF0_ST_reg)&_BIT1)||(rtd_inl(HDMI_DRF1_ST_reg)&_BIT1)){  //check success or fail
        rtd_maskl(SYS_CRT_BIST_EN_reg,~(_BIT14|_BIT13),0);//hdmi1,hdmi2 drf disable
        return FALSE;
    }
    else
    {
        rtd_maskl(SYS_CRT_BIST_EN_reg,~(_BIT14|_BIT13),0);//hdmi1,hdmi2 drf disable
        return TRUE;
    }
//Drf mode end
}
#endif

void HDMI_TX_Script(void)
{
#if 0
//-------- BUS/BUSH/ACPU clock source select to 27MHz ------------------------
rtd_outl(0x18060050,0x00000001);
BusyWaiting(10000);

//-------- SPI clk -------------------------------------------------
rtd_outl(0x1801a808,0xF); // fdiv, clk_sf = clk_sys / (fdiv+1)
BusyWaiting(10000);
rtd_outl(0x1801a814,0x1); // latch data at the rising edge
rtd_outl(0x1801a80c,0x00202020);

//-------- PLL ACPU -------------------------------------------------
rtd_outl(0x1800010c,0x00000324); // PLLACPU power down, hold reset, output disable
rtd_outl(0x18000108,0x000A3600); // max 850, set 27*37/2 = 499.5MHz
rtd_outl(0x1800010c,0x00000325); // PLLACPU power on
rtd_outl(0x1800010c,0x00000327); // release PLLACPU reset

//-------- PLL BUS -------------------------------------------------
rtd_outl(0x18000138,0x00000004); // PLLBUS power down, hold reset, output disable
rtd_outl(0x18000130,0x00351B52); // max 405, set 27*15 = 405MHz
rtd_outl(0x18000138,0x00000005); // PLLBUS power on
rtd_outl(0x18000138,0x00000007); // release PLL reset

//-------- PLL BUSH -------------------------------------------------
rtd_outl(0x18000148,0x00000004);  // PLLBUSH power down, hold reset, output disable
rtd_outl(0x18000140,0x17BD1B52); // max 384, set 27*113/2/4 = 381.375MHz
rtd_outl(0x18000148,0x00000005);  // PLLBUSH power on
rtd_outl(0x18000148,0x00000007);  // release PLLBUSH reset

BusyWaiting(10000); // wait at least > 150us
rtd_outl(0x1800010c,0x00000323); // PLLACPU output enable
rtd_outl(0x18000138,0x00000003); // PLLBUS output enable
rtd_outl(0x18000148,0x00000003); // PLLBUSH output enable

//-------- BUS/BUSH/ACPU clock source select to PLLBUS/PLLBUSH/PLLACPU ------------------------
rtd_outl(0x18060050,0x00000000);
BusyWaiting(10000);

//-------- PLL SCPU -------------------------------------------------
rtd_outl(0x18000100,0x00262400); // max 1000, set 27*100/3= 900MHz
rtd_outl(0x18000104,0x00000325); // PLLSCPU  power on
rtd_outl(0x18000104,0x00000327); // release SCPU PLL reset

//-------- PLL VCPU -------------------------------------------------
rtd_outl(0x18000110,0x00350A00); // target 472, set 27*37/2=472.5MHz
rtd_outl(0x18000114,0x00000325); // PLLVCPU power on
rtd_outl(0x18000114,0x00000327); // release VCPU PLL reset

//-------- PLL DISP -------------------------------------------------
rtd_outl(0x18000190,0x02601336);    // max 540, set 360MHz
rtd_outl(0x18000194,0x11020001);    // DPLL power on
rtd_outl(0x18000194,0x11020043);    // release DPLL reset

//-------- PLL GPU1-------------------------------------------------
rtd_outl(0x180001e0,0x00098600); // max 450, set 351MHz
rtd_outl(0x180001e4,0x00000325); // PLLGPU1 power on
rtd_outl(0x180001e4,0x00000327); // release PLLGPU1 reset

//-------- PLL GPU2-------------------------------------------------
rtd_outl(0x180001e8,0x00098600); // max 450, set 351MHz
rtd_outl(0x180001ec,0x00000325); // PLLGPU2 power on
rtd_outl(0x180001ec,0x00000327); // release PLLGPU2 reset

//-------- PLL 27X -------------------------------------------------
//rtd_outl(0x18000240,0x0225000E); // max = 432, set 27*16 = 432MHz
//rtd_outl(0x18000244,0x00105401); // 1.1V LDO power on & output 1.0V, LDO XTAL power on & output 1.76V
//rtd_outl(0x18000248,0x00000001); // release PLL_27X & VCO reset & power on
//rtd_outl(0x18000248,0x00000007); // release PLL_27X & VCO reset & power on
//ScalerTimer_DelayXms(0x1); // at least > 150us


//-------- PLL ETN -------------------------------------------------
//rtd_outl(0x18016d00,0x0230370a); // 25M
//rtd_outl(0x18016d04,0x00008035); // power on
//rtd_outl(0x18016d04,0x00008037); // release reset

BusyWaiting(10000); // at least > 150us
rtd_outl(0x18000104,0x00000323); // PLLSCPU CKOUT enable
rtd_outl(0x18000114,0x00000323); // PLLVCPU CKOUT enable
rtd_outl(0x180001e4,0x00000323); // PLLGPU1 output enable
rtd_outl(0x180001ec,0x00000323); // PLLGPU2 output enable
//rtd_outl(0x18016d04,0x00008033); // PLLETN output enable

//-------- Module Clock & Reset Enable ---------
rtd_maskl(0x18000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock
rtd_maskl(0x18000014, 0x1effffe7, 0x00000000);// disable TVSB1~3,APLL_ADC,I/M/D domain clock
rtd_maskl(0x18000008, 0xffff8fe9, 0x00000000);// hold TVSB1~3,APLL_ADC,I/M/D domain reset
rtd_maskl(0x18000008, 0xffff8fe9, 0x00007016);// release TVSB1~3,APLL_ADC,I/M/D domain reset
BusyWaiting(10000);
rtd_maskl(0x18000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock

//-------- Disable write merger, Multi write, Bypass Read ----------- price
//rtd_outl(0x1801a018, 0x00002888); // disable A/VCPU write merge, bypass read
//rtd_outl(0x18008f04, 0x00000000);// dsiable SCPU write merge, bypass read

//-------- HDMI bandgap power---------
//rtd_maskl(0x18000008, 0xFFFDFFFF, 0x00020000); // release HDMI reset
//rtd_maskl(0x1800000c, 0xFFFFFFFD, 0x00000002); // enable HDMI clock
//rtd_maskl(0x18007B40, 0xFDFFFFFF,0x02000000); //HDMI bandgap power 1:on 0:off
//ScalerTimer_DelayXms(0x1);


#endif

//HDMI TX
rtd_maskl(0xb8000000, 0xffffefff, 0x1000);  //HDMI TX rstn
rtd_maskl(0xb800000c, 0xfffffeff, 0x100);   //HDMI TX clk en


//HDMI RX
rtd_maskl(0xb8000008, 0xfffdffff, 0x20000); //HDMI RX rstn
rtd_maskl(0xb800000c, 0xfffffffd, 0x2); //HDMI RX clk en
rtd_maskl(0xb8007B40, 0xFDFFFFFF,0x02000000); //HDMI bandgap power 1:on 0:off

//HDMI AIO
rtd_maskl(0xb8000000, 0xffff7fff, 0x8000);  //AIO rstn
rtd_maskl(0xb800000c, 0xfffffbff, 0x400);   //AIO clk en

//APLL ADC
rtd_maskl(0xb8000008, 0xffffffef, 0x10);    //APLL ADC rstn
rtd_maskl(0xb8000014, 0xfeffffff, 0x1000000);   //APLL ADC clk en

//TVE
rtd_maskl(0xb8000000, 0xfffbffff, 0x40000); //TVE rstn
rtd_maskl(0xb800000c, 0xffffffef, 0x10);    //TVE clk en

//Display2Tve
rtd_maskl(0xb8000008, 0xfffffffd, 0x2); // DISP rstn
rtd_maskl(0xb8000014, 0xfffffff7, 0x8); //DISP clk en
rtd_maskl(0xb8000014, 0xffbfffff, 0x400000);    //Display2TVE clk en

//-------- Module Clock & Reset Enable ---------
//rtd_outl(0xb8000000, 0xffffffff); //
//rtd_outl(0xb8000004, 0xffffffff); //
//rtd_outl(0xb8000008, 0xffffffff); //
//rtd_outl(0xb800000c, 0xffffffff); //
//rtd_outl(0xb8000010, 0xffffffff); //
//rtd_outl(0xb8000014, 0xffffffff); //

rtd_outl(0xb8020104,0x00050009);  // APLL_ADC LDO power, for PLL27X


//adams setting PHY
//rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
rtd_outl(0xb80001c0, 0x15f61891);  //output amplitude, de-emphasis
rtd_outl(0xb80001c4, 0x15409010);  // TX_PLL_PU, VCO frequency range
//rtd_outl(0xb80001c4, 0x15c09012);  // TX_PLL_PU, VCO frequency range
rtd_outl(0xb80001c8, 0x0db10b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
//rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN
rtd_outl(0xb80001cc, 0x00053622);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(20), PIXEL_DIV16(2), TMDS_DIV16(2)
rtd_outl(0xb80001d0, 0x000f0a22);  // TV_PLL_PU
rtd_outl(0xb80001d4, 0x00540600);  // TV_PLL frequency tuning enable
//rtd_outl(0xb8000024, 0x00004000);
//rtd_outl(0xb8000028, 0x00000000); //reg_tve_hdmi_div_sel, reg_hdmi_tmds_div


rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
//rtd_outl(0xb80001d0, 0x000f0922);  // TV_PLL_PU
//rtd_outl(0xb80001c4, 0x00c09012);  // TX_PLL_PU
//rtd_outl(0xb80001c8, 0x05810b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN
//rtd_outl(0xb80001cc, 0x00051622);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(20), PIXEL_DIV16(2), TMDS_DIV16(2)
rtd_outl(0xb8000024, 0x00004000);
rtd_outl(0xb8000028, 0x00000000);   //reg_tve_hdmi_div_sel, reg_hdmi_tmds_div


// set_TVE_DUMMY_1_reg(0xf0010000); ???
rtd_outl(0xb800d234, 0x0117077f);  // horizontal blank = 280-1, horizontal data active = 1920-1
rtd_outl(0xb800d238, 0x002b0057);  // horizontal sync width = 44 -1, horizontal front porch = 88-1
rtd_outl(0xb800d23c, 0x00000093);  // horizontal back proch = 148-1
rtd_outl(0xb800d240, 0x04370437);  // vertical single field size (only active video) = 1080 -1, vertical total data active (with active space) = 1080-1
rtd_outl(0xb800d24c, 0x000a002c);  // vertical sync width = 10, vertical blank = 45-1
rtd_outl(0xb800d250, 0x00230008);  // vertical back proch = 36-1, vertical front porch = 8


// VO FIFO for HDMI video data input
rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000001);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000002);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000003);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000004);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000005);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000006);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000007);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000008);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x00000009);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000a);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000b);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000c);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000d);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000e);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c8, 0x0000000f);
rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set


rtd_outl(0xb800d034, 0x00000022);  // TMDS encoder disable, HDMI disable
rtd_outl(0xb800d0bc, 0x14000000);  // disable HDMI audio data path, off debug color path
rtd_outl(0xb800d030, 0x00000924);  // hsync/vsync delay all 0
rtd_outl(0xb800d154, 0x5280f100);  // video format change wait 1 vsync, do not use setting first deep color phase by SW, setting first deep color phase by SW, use default deep phase by SW, default phase, do not deep color mode
rtd_outl(0xb800d020, 0x00002004);  // image end signal (don't care in FPGA), progressive HD mode, HDMI timing genator enable
rtd_outl(0xb800d0a4, 0x0000007e);  // enable transmission periodic island packet (active when [0]=1)

// YCbCr mode (no transform0
rtd_outl(0xb800d024, 0x00004000);
rtd_outl(0xb800d028, 0x00000000);
rtd_outl(0xb800d02c, 0x00000000);
rtd_outl(0xb800d200, 0x00000000);
rtd_outl(0xb800d204, 0x00004000);
rtd_outl(0xb800d208, 0x00000000);
rtd_outl(0xb800d20c, 0x00000000);
rtd_outl(0xb800d210, 0x00000000);
rtd_outl(0xb800d214, 0x00004000);
rtd_outl(0xb800d218, 0x00000000);
rtd_outl(0xb800d21c, 0x00000000);
rtd_outl(0xb800d220, 0x00000000);

rtd_outl(0xb800d078, 0x00000008);  // enable GCP trnsmission
rtd_outl(0xb800d078, 0x00000009);  // enable GCP trnsmission (writen enable)
rtd_outl(0xb800d0a0, 0x21084210);  // setting periodic island packet cycle length
rtd_outl(0xb800d0b4, 0x00000c66);  // max packet length = 18-1 in vertical blanking, max packet length = 6-1 in horizontal blanking
rtd_outl(0xb800d0b8, 0x0005506b);  // YCbcr444, not repeat pixel, HDMI mode

rtd_outl(0xb800d07c, 0x000d0282);  // packet type=0x82, version=0x02, length=0x0d
rtd_outl(0xb800d080, 0x20a85047);  // no IT contect, sYCC601, RGB quantization range = default, no knonw non-uniform scaling,
                   // colorimetry=ITU709, picture aspect ratio=16:9, active format aspect ratio=same as picture aspect ratio,
                   // YCbCr444, active format vaild, bar data not vaild, no scan information
                   // checksum = ~(0x82+0x02+0x0d+0x00+0x50+0xa8+0x20+0x10+0x00)+1
rtd_outl(0xb800d084, 0x00000010);  // no pixel reperirion, video code = 16
rtd_outl(0xb800d088, 0x00000000);
rtd_outl(0xb800d08c, 0x00000000);
rtd_outl(0xb800d090, 0x00000000);
rtd_outl(0xb800d094, 0x00000000);
rtd_outl(0xb800d098, 0x00000000);
rtd_outl(0xb800d09c, 0x00000000);
rtd_outl(0xb800d0b0, 0x00007700);  // enable write periodic island packet SRAM, periodic island packet SRAM start address = 0x00
rtd_outl(0xb800d0a0, 0x00000011);  // write trnsmission period of periodic island packet SRAM
rtd_outl(0xb800d0a4, 0x00000003);  // enable transmission periodic island packet (active when [0]=1)

rtd_outl(0xb800d158, 0x00000300);  // video format change

rtd_outl(0xb800d2a4, 0x0150ffff);  // reset TMDS data output async FIFO
rtd_outl(0xb800d2a4, 0x01507fff);  // remove reset status
//set_TVE_DUMMY_1_reg(0x00000000); ???

rtd_outl(0xb800d034, 0x00000033);  // TMDS encoder enable, HDMI enable


//PHY modify by adams
rtd_maskl(0xb80001c4, 0xffc3ffff, 0x3c0000);    //Lane0~3 enable

printf("b8000000 = %x........\n",rtd_inl(0xb8000000));
printf("b8000004 = %x........\n",rtd_inl(0xb8000004));
printf("b80001c0 = %x........\n",rtd_inl(0xb80001c0));
printf("b800d020 = %x........\n",rtd_inl(0xb800d020));
//while(1);
}

void MHL_TX_Script(void)
{
#if 0
    printf("~~MHL script file display 480P60 24bit mode PHY setting !!\n");
        //adams setting PHY
    rtd_outl(0xb80001c0, 0x15f65891);  //output amplitude, de-emphasis
    rtd_outl(0xb80001c4, 0x15409012);  // TX_PLL_PU, VCO frequency range
    rtd_outl(0xb80001c8, 0x0eb94b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
    rtd_outl(0xb80001cc, 0x0005b733);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(24), PIXEL_DIV16(24), TMDS_DIV16(8)
    rtd_outl(0xb80001d0, 0x000f0a22);  // TV_PLL_PU
    rtd_outl(0xb80001d4, 0x00540600);  // TV_PLL frequency tuning enable


    rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
    //rtd_outl(0xb80001d0, 0x000f0922);  // TV_PLL_PU
    //rtd_outl(0xb80001c4, 0x00409012);  // TX_PLL_PU
    //rtd_outl(0xb80001c8, 0x04810b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
    rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN
    //rtd_outl(0xb80001cc, 0x00021688);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(8), PIXEL_DIV5(1), PIXEL_DIV16(0), TMDS_DIV5(1), TMDS_DIV16(0)
    rtd_outl(0xb8000024, 0x00004000);
    //rtd_outl(0xb8000028, 0x00001440);  // HDMI_TMDS_DIV(1), TVE_HDMI_DIV_SEL(1), TVE_PCLK_SEL(1)  ******
    rtd_outl(0xb8000028, 0x00002000);  // HDMI_TMDS_DIV(2), TVE_HDMI_DIV_SEL(0), TVE_PCLK_SEL(0)  ******

    // set_TVE_DUMMY_1_reg(0xf0010000); ???
    rtd_outl(0xb800d234, 0x008902cf);  // horizontal blank = 138-1, horizontal data active = 720-1
    rtd_outl(0xb800d238, 0x003d000f);  // horizontal sync width = 62 -1, horizontal front porch = 16-1
    rtd_outl(0xb800d23c, 0x0000003b);  // horizontal back proch = 60-1
    rtd_outl(0xb800d240, 0x01df01df);  // vertical single field size (only active video) = 480 -1, vertical total data active (with active space) = 480-1
    rtd_outl(0xb800d24c, 0x0006002c);  // vertical sync width = 6, vertical blank = 45-1
    rtd_outl(0xb800d250, 0x001d0009);  // vertical back proch = 30-1, vertical front porch = 9

    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set

    rtd_outl(0xb800d034, 0x00000022);  // TMDS encoder disable, HDMI disable
    rtd_outl(0xb800d0bc, 0x14000000);  // disable HDMI audio data path, off debug color path
    rtd_outl(0xb800d030, 0x00000924);  // hsync/vsync delay all 0
    rtd_outl(0xb800d154, 0x5280f100);  // video format change wait 1 vsync, do not use setting first deep color phase by SW, setting first deep color phase by SW, use default deep phase by SW, default phase, do not deep color mode
    rtd_outl(0xb800d020, 0x00002204);  // image end signal (don't care in FPGA), progressive SD mode, HDMI timing genator enable
    rtd_outl(0xb800d0a4, 0x0000007e);  // enable transmission periodic island packet (active when [0]=1)

    // YCbCr mode (no transform)
    rtd_outl(0xb800d024, 0x00004000);
    rtd_outl(0xb800d028, 0x00000000);
    rtd_outl(0xb800d02c, 0x00000000);
    rtd_outl(0xb800d200, 0x00000000);
    rtd_outl(0xb800d204, 0x00004000);
    rtd_outl(0xb800d208, 0x00000000);
    rtd_outl(0xb800d20c, 0x00000000);
    rtd_outl(0xb800d210, 0x00000000);
    rtd_outl(0xb800d214, 0x00004000);
    rtd_outl(0xb800d218, 0x00000000);
    rtd_outl(0xb800d21c, 0x00000000);
    rtd_outl(0xb800d220, 0x00000000);

    rtd_outl(0xb800d078, 0x00000008);  // enable GCP trnsmission
    rtd_outl(0xb800d078, 0x00000009);  // enable GCP trnsmission (writen enable)
    rtd_outl(0xb800d0a0, 0x21084210);  // setting periodic island packet cycle length
    rtd_outl(0xb800d0b4, 0x00000c61);  // max packet length = 18-1 in vertical blanking, max packet length = 2-1 in horizontal blanking
    rtd_outl(0xb800d0b8, 0x0007c07b);  // invert display vsync polarity, invert display hsync polarity, YCbCr422, not repeat pixel, HDMI mode

    rtd_outl(0xb800d07c, 0x000d0282);  // packet type=0x82, version=0x02, length=0x0d
    rtd_outl(0xb800d080, 0x205830c5);  // no IT contect, sYCC601, RGB quantization range = default, no knonw non-uniform scaling,
                       // colorimetry=ITU601, picture aspect ratio=4:3, active format aspect ratio=same as picture aspect ratio,
                       // YCbCr422, active format vaild, bar data not vaild, no scan information
                       // checksum = ~(0x82+0x02+0x0d+0x00+0x30+0x58+0x20+0x02+0x00)+1
    rtd_outl(0xb800d084, 0x02000000);  // video code = 2, no pixel reperirion
    rtd_outl(0xb800d088, 0x00000000);
    rtd_outl(0xb800d08c, 0x00000000);
    rtd_outl(0xb800d090, 0x00000000);
    rtd_outl(0xb800d094, 0x00000000);
    rtd_outl(0xb800d098, 0x00000000);
    rtd_outl(0xb800d09c, 0x00000000);
    rtd_outl(0xb800d0b0, 0x00007700);  // enable write periodic island packet SRAM, periodic island packet SRAM start address = 0x00
    rtd_outl(0xb800d0a0, 0x00000011);  // write trnsmission period of periodic island packet SRAM
    rtd_outl(0xb800d0a4, 0x00000003);  // enable transmission periodic island packet (active when [0]=1)

    //rtd_outl(0xb800d298, 0x0000026f);  // HDMI_MHLCTRL_xor_pixel_sel(1), HDMI_MHLCTRL_mhl_enc_sel(0), HDMI_MHLCTRL_mhl_pp_mode(1), HDMI_MHLCTRL_mhl_enable(1)  ******
    //rtd_outl(0xb800d298, 0x0000022b);  // HDMI_MHLCTRL_xor_pixel_sel(1), HDMI_MHLCTRL_mhl_enc_sel(0), HDMI_MHLCTRL_mhl_pp_mode(0), HDMI_MHLCTRL_mhl_enable(1)  ******

    rtd_outl(0xb800d158, 0x00000300);  // video format change

    rtd_outl(0xb800d2a4, 0x0150ffff);  // reset TMDS data output async FIFO
    rtd_outl(0xb800d2a4, 0x01503fff);  // remove reset status
    //set_TVE_DUMMY_1_reg(0x00000000); ???

    rtd_outl(0xb800d034, 0x00000033);  // TMDS encoder enable, HDMI enable
    rtd_outl(0xb800d298, 0x0000022b);  // HDMI_MHLCTRL_xor_pixel_sel(1), HDMI_MHLCTRL_mhl_enc_sel(0), HDMI_MHLCTRL_mhl_pp_mode(0), HDMI_MHLCTRL_mhl_enable(1)  ******

    //PHY modify by adams
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x080000);    //Lane1 enable

    printf("~~MHL script file display 480P60 24bit mode end !!\n");
#else
    printf("~~MHL script file display 1080P60 PP mode PHY setting !!\n");
    //adams setting PHY
    rtd_outl(0xb80001c0, 0x15f61891);  //output amplitude, de-emphasis
    rtd_outl(0xb80001c4, 0x15c09010);  // TX_PLL_PU, VCO frequency range
    rtd_outl(0xb80001c8, 0x0db98b77);  // LDO_PLL_PU, LDO_CCO_PU, LDO_TMDS_PU
    rtd_outl(0xb80001cc, 0x00053621);  // TV_PSTEP_EN(0), HDMI_CK_EN, TV_LDIV(20), PIXEL_DIV16(4), TMDS_DIV16(2)
    rtd_outl(0xb80001d0, 0x000f0a22);  // TV_PLL_PU
    rtd_outl(0xb80001d4, 0x00540600);  // TV_PLL frequency tuning enable


    rtd_outl(0xb8000174, 0x00554000);  // PLLDSS phase interpolator enable
    rtd_outl(0xb8000178, 0x00d0000a);  // PSAUD2_FUPDN, PSAUD2_DIV, PSAUD2_PSEN
    rtd_outl(0xb8000024, 0x00004000);
    rtd_outl(0xb8000028, 0x00001000);   //reg_tve_hdmi_div_sel, reg_hdmi_tmds_div*************

    // set_TVE_DUMMY_1_reg(0xf0010000); ???
    rtd_outl(0xb800d234, 0x0117077f);  // horizontal blank = 280-1, horizontal data active = 1920-1
    rtd_outl(0xb800d238, 0x002b0057);  // horizontal sync width = 44 -1, horizontal front porch = 88-1
    rtd_outl(0xb800d23c, 0x00000093);  // horizontal back proch = 148-1
    rtd_outl(0xb800d240, 0x04370437);  // vertical single field size (only active video) = 1080 -1, vertical total data active (with active space) = 1080-1
    rtd_outl(0xb800d24c, 0x000a002c);  // vertical sync width = 10, vertical blank = 45-1
    rtd_outl(0xb800d250, 0x00230008);  // vertical back proch = 36-1, vertical front porch = 8

    // VO FIFO for HDMI video data input
    rtd_outl(0xb8026000, 0xcc10000f);  // disp2tve_global
    rtd_outl(0xb80260c4, 0x0000000d);  // mp_sram_set
    rtd_outl(0xb80260c8, 0x00000000);  // mp_sram_addr
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000001);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000002);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000003);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000004);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000005);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000006);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000007);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000008);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x00000009);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000a);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000b);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000c);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000d);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000e);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c8, 0x0000000f);
    rtd_outl(0xb80260cc, 0x00c0c0c0);  // mp_sram_lsb
    rtd_outl(0xb80260c4, 0x00000001);  // mp_sram_set
    rtd_outl(0xb80260c4, 0x00000103);  // mp_sram_set

    rtd_outl(0xb800d034, 0x00000022);  // TMDS encoder disable, HDMI disable
    rtd_outl(0xb800d0bc, 0x14000000);  // disable HDMI audio data path, off debug color path
    rtd_outl(0xb800d030, 0x00000924);  // hsync/vsync delay all 0
    rtd_outl(0xb800d154, 0x5280f100);  // video format change wait 1 vsync, do not use setting first deep color phase by SW, setting first deep color phase by SW, use default deep phase by SW, default phase, do not deep color mode
    rtd_outl(0xb800d020, 0x00002004);  // image end signal (don't care in FPGA), progressive HD mode, HDMI timing genator enable
    rtd_outl(0xb800d0a4, 0x0000007e);  // enable transmission periodic island packet (active when [0]=1)

    // YCbCr mode (no transform0
    rtd_outl(0xb800d024, 0x00004000);
    rtd_outl(0xb800d028, 0x00000000);
    rtd_outl(0xb800d02c, 0x00000000);
    rtd_outl(0xb800d200, 0x00000000);
    rtd_outl(0xb800d204, 0x00004000);
    rtd_outl(0xb800d208, 0x00000000);
    rtd_outl(0xb800d20c, 0x00000000);
    rtd_outl(0xb800d210, 0x00000000);
    rtd_outl(0xb800d214, 0x00004000);
    rtd_outl(0xb800d218, 0x00000000);
    rtd_outl(0xb800d21c, 0x00000000);
    rtd_outl(0xb800d220, 0x00000000);

    rtd_outl(0xb800d078, 0x00000008);  // enable GCP trnsmission
    rtd_outl(0xb800d078, 0x00000009);  // enable GCP trnsmission (writen enable)
    rtd_outl(0xb800d0a0, 0x21084210);  // setting periodic island packet cycle length
    rtd_outl(0xb800d0b4, 0x00000c66);  // max packet length = 18-1 in vertical blanking, max packet length = 6-1 in horizontal blanking
    rtd_outl(0xb800d0b8, 0x0005506b);  // YCbcr444, not repeat pixel, HDMI mode

    rtd_outl(0xb800d07c, 0x000d0282);  // packet type=0x82, version=0x02, length=0x0d
    rtd_outl(0xb800d080, 0x20a85047);  // no IT contect, sYCC601, RGB quantization range = default, no knonw non-uniform scaling,
                       // colorimetry=ITU709, picture aspect ratio=16:9, active format aspect ratio=same as picture aspect ratio,
                       // YCbCr444, active format vaild, bar data not vaild, no scan information
                       // checksum = ~(0x82+0x02+0x0d+0x00+0x50+0xa8+0x20+0x10+0x00)+1
    rtd_outl(0xb800d084, 0x00000010);  // no pixel reperirion, video code = 16
    rtd_outl(0xb800d088, 0x00000000);
    rtd_outl(0xb800d08c, 0x00000000);
    rtd_outl(0xb800d090, 0x00000000);
    rtd_outl(0xb800d094, 0x00000000);
    rtd_outl(0xb800d098, 0x00000000);
    rtd_outl(0xb800d09c, 0x00000000);
    rtd_outl(0xb800d0b0, 0x00007700);  // enable write periodic island packet SRAM, periodic island packet SRAM start address = 0x00
    rtd_outl(0xb800d0a0, 0x00000011);  // write trnsmission period of periodic island packet SRAM
    rtd_outl(0xb800d0a4, 0x00000003);  // enable transmission periodic island packet (active when [0]=1)

    rtd_outl(0xb800d158, 0x00000300);  // video format change

    rtd_outl(0xb800d2a4, 0x0150ffff);  // reset TMDS data output async FIFO
    rtd_outl(0xb800d2a4, 0x01503fff);  // remove reset status
    //set_TVE_DUMMY_1_reg(0x00000000); ???

    rtd_outl(0xb800d034, 0x00000033);  // TMDS encoder enable, HDMI enable
    //rtd_outl(0xb800d298, 0x0000022b);  // HDMI_MHLCTRL_xor_pixel_sel(1), HDMI_MHLCTRL_mhl_enc_sel(0), HDMI_MHLCTRL_mhl_pp_mode(0), HDMI_MHLCTRL_mhl_enable(1)  ******
    rtd_outl(0xb800d298, 0x0000026f);  // HDMI_MHLCTRL_xor_pixel_sel(1), HDMI_MHLCTRL_mhl_enc_sel(0), HDMI_MHLCTRL_mhl_pp_mode(0), HDMI_MHLCTRL_mhl_enable(1)  ******

    //PHY modify by adams
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x80000); //Lane0~3 enable
    printf("~~MHL script file display 1080P60 PP mode end !!\n");
#endif

}

static int get_hdmi_tx_cmd_enum(INT8 *str)
{
    int i, ret = HDMI_TX_CMD_TEST_EXIT;
    for (i = 0; i < HDMI_TX_CMD_ITEM_NUM; i++)
    {
        if (strcmp(cmd_str_array[i], str) == 0)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

void HDMI_Loop_Back_test(void)
{
	system_init();	//CRT reset and clk enable

    	printf("Video info: %d, %d, %d, %d, %d, %d, %d\n",
            case_mode, DeepColorEnable, DeepColorDepth,
            TimingGen, Enable3D, Format3D, rgb_mode);

	printf("Audio info: %d, %d, %d, %d, %d\n",
            SamplingFrequency, SampleSize, AudioChannelCount,
            AudioType, CTSSource);

	//config_audio_param();
	set_and_go();
	printk("HDMI TX and RX loop back test, result refer to RX\n");
/*
	if (!QC_Hdmi_Main(1)) 	//RX CRC check
				{
					printk("HDMITX and RX loop back test fail\n");
				}
				else
				{
					printk("HDMITX and RX loop back test pass\n");
				}
*/
}

void QC_Code_For_Verify(void)
{
UINT8 receive_buf[QCINFO_CMD_BUFFER_SIZE];
    int i, option, tNum;
    bool loop = TRUE;

    system_init();	//CRT reset and clk enable
    while (loop) {
        printk("type hdmi tx cmd >> ");
        memset(receive_buf, 0, QCINFO_CMD_BUFFER_SIZE);
        GetLine(receive_buf, QCINFO_CMD_BUFFER_SIZE, 1);
        hdmi_tx_argc = GetArgc((const INT8 *) receive_buf);
        hdmi_tx_argv = (INT8 **) GetArgv((const INT8 *) receive_buf);

        option = get_hdmi_tx_cmd_enum(*(&hdmi_tx_argv[0]));
        ////tNum = strtoul((const INT8 *) (hdmi_tx_argv[1]), (INT8 **) NULL, 10);
        ////printk("str to int = %d\n", tNum);
        printk("\n");
        switch (option) {
            case HDMI_TX_CMD_TEST_PROTOCOL:
                printk("[test video and audio]\n");
                HDMI_Test();
                break;
            case HDMI_TX_CMD_TEST_CEC:
                printk("[test cec]\n");
                break;
            case HDMI_TX_CMD_TEST_SCRIPT:
                printk("[test script]\n");
        #if OUTPUT_SRC_SELECT_HDMI
                HDMI_TX_Script();
        #else
                MHL_TX_Script();
        #endif
                break;
            case HDMI_TX_CMD_TEST_EXIT:
                loop = FALSE;
                printk("[test exit]\n");
                break;
        }
    }

}

int QC_Verifier_HDMI_TX(void)
{
    
#if QC_Code_For_Verify_Chip
	QC_Code_For_Verify();	//QC code for chip verify , need key in command
#else
	HDMI_Loop_Back_test();	//normal QC code flow for QC Loop back test
#if 0
    HDMI_Test();
#endif
#if 0
    CCec_Test();
#endif
#if 0
    MBIST_CHECK();
#endif
#if 0
    HDMI_TX_Script();
#endif
#endif
    return SUCCESS;
}
