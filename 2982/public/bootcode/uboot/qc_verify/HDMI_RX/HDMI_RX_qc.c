#include <qc_verify_common.h>
#include <rbusHDMIReg.h>
#include <rbusDFEReg.h>
#include <rbusMHLCbus.h>
#include <rbusMiscDDCReg.h>

//b8007b08
//bit31 Show Pannel
//bit26 Clock Hysterisis
//bit25 Packet Pixel mode
//bit24 CBUS Enable
//bit18 HDMI Port2
//bit17 HDMI Port1
//bit16 HDMI Port0
//bit11 checking crc to quit if any error
//bit10 MHL Port 2
//bit09 MHL Port 1
//bit08 MHL Port 0
//bit07 HDMI printf
//bit06 Auto EQ

#define HDMI_BITERROR_TEST 0
bool HDMI_Bit_Err_One_Time_Detect(UINT8 ch_sel, UINT8 period, UINT16 thd);
int DefaultValueTest(void);

#if READ_INFOFRAME
typedef enum {
    SPD_UNKNOWN,
    SPD_DIGITALSTB,
    SPD_DVDPLAYER,
    SPD_DVHS,
    SPD_HDD_VIDEORECORDER,
    SPD_DVC,
    SPD_DSC,
    SPD_VIDEOCD,
    SPD_GAME,
    SPD_PC_GENERAL,
    SPD_BD,
    SPD_SACD,
    SPD_HDDVD,
    SPD_PMP,
    SPD_RESERVED
} HDMI_SPD25_T;

UINT8 Hdmi_GetSourceDeviceInfo(void);
bool Hdmi_ReadInfoFrameRSV2(UINT8 typecode, UINT8 startpos, UINT8 len, UINT8 *buf);
#endif

bool QC_Hdmi_Main(UINT8 channel)
{
    bool crc_result=FALSE;
    UINT32 b;

    drvif_Hdmi_Init();

    if ( get_Koffset_result()!=0 )
    {
        printk("[HDMI] WARNING: Koffset result fail\n");
#if CheckKoffSetError
        return FALSE;
#endif
    }

    drvif_Hdmi_InitSrc(channel);

    b = HdmiMeasureVedioClock();
    if ( b>100 ) {
        SetupTMDSPhy(b, 0);
        mdelay(10);
        Hdmi_DetectMode(b);
    }

#if Audio_Output_Setting
    Hdmi_AudioModeDetect();
#endif

#ifdef HDMI_DisplayPanel
    if (_BIT31&(~ rtd_inl(HDMIPHY_REG_CK_9_12_reg)))
    {
        rtd_maskl(SOFT_RESET3_reg,~(RSTN_TVSB2|RSTN_DISPIM|RSTN_DISP),(RSTN_TVSB2|RSTN_DISPIM|RSTN_DISP));		//CRT
        rtd_maskl(CLOCK_ENABLE1_reg,~CLKEN_DCU,CLKEN_DCU);		//CRT
        rtd_maskl(SOFT_RESET3_reg,~(CLKEN_TVSB2|CLKEN_DISPIM|CLKEN_DISP),(CLKEN_TVSB2|CLKEN_DISPIM|CLKEN_DISP));		//CRT
#if HDMI_DisplayPanel==HDMI_1080p
        #include "1080p/case18_hdmi1080p_frc_fhd.tbl" 
#elif HDMI_DisplayPanel==HDMI_1080i
        #include "1080i/case2_hdmipg1080i_frc_fhd.tbl" 
#endif
    }
#endif

#if 0//READ_INFOFRAME
    HDMI_PRINTF("[HDMI] Source Device Info=%02X\n", Hdmi_GetSourceDeviceInfo());
#endif

    crc_result = QC_CRCCheck();
    printk("[HDMI] Port%d TMDS clock = %03dMHz, CRC checked: %s\n", channel, (b*27+128)>>8, crc_result?"PASS":"FAIL!");
    HDMI_PRINTF("[HDMI] ==================================================\n\n");

    return crc_result;
}

bool HDCP_BIST_CHECK(void)
{
	UINT8 time_counter=250;

#if 0
	HDMI_PRINTF("[HDMI] HDCP BIST start!!!\n");
	rtd_maskl(BIST_MODE_reg,~BIST_MODE_hdcp_bist_en_mask,BIST_MODE_hdcp_bist_en(1));		//HDCP bist enable
	do			
	{
		udelay(1000);
		if (rtd_inl(BIST_DONE_reg)&BIST_DONE_hdcp_bist_done_mask)		//wait bist finish
			break;
	}while(--time_counter);
	HDMI_PRINTF("111111111HDCP BIST start!!!\n");

	if (!time_counter)
	{
		HDMI_PRINTF("HDCP BIST time out!!!\n");
		return FALSE;
	}

	if (rtd_inl(BIST_FAIL_reg)&BIST_FAIL_hdcp_bist_fail_mask)
	{	//check success or fail
		HDMI_PRINTF("HDCP BIST fail!!!\n");
		return FALSE;
	}	
	HDMI_PRINTF("2222222222HDCP BIST start!!!\n");
	
	rtd_maskl(BIST_MODE_reg,~BIST_MODE_hdcp_bist_en_mask,0);  //HDCP bist disable
//Bist mode end
	//reset
	//rtd_maskl(SOFT_RESET3_reg,~rstn_hdmirx,0);		//HDMI reset
	udelay(30);
	//rtd_maskl(SOFT_RESET3_reg,~rstn_hdmirx,rstn_hdmirx);
	HDMI_PRINTF("66666HDCP BIST start!!!\n");
	//clock
	//rtd_maskl(CLOCK_ENABLE1_reg,~clk_en_hdmirx,0);		//HDMI clock enable
	udelay(30);
	//rtd_maskl(CLOCK_ENABLE1_reg,~clk_en_hdmirx,clk_en_hdmirx);
	udelay(10);
	//rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_reg,~HDMIPHY_REG_BANDGAP_Z0_bgpow_mask,HDMIPHY_REG_BANDGAP_Z0_bgpow(1));		//BG power on (Bit25)
	udelay(1000);
#else
	HDMI_PRINTF("\n[HDMI] HDCP BIST/DRF start!!!\n");
	rtd_maskl(BIST_MODE_reg,~BIST_MODE_hdcp_bist_en_mask,BIST_MODE_hdcp_bist_en(1));		//HDCP bist enable
#endif
	
	rtd_maskl(DRF_MODE_reg,
		~(DRF_MODE_hdcp_drf_mode_mask|DRF_MODE_audio_drf_mode_mask),
		(DRF_MODE_hdcp_drf_mode(1)|DRF_MODE_audio_drf_mode(1)));		//HDCP drf enable	
	do			
	{
		udelay(1000);
		if (rtd_inl(DRF_PAUSE_reg)&(DRF_PAUSE_hdcp_drf_pause_mask|DRF_PAUSE_audio_drf_pause_mask))		//DRF_START_PAUSE
			break;
	}while(--time_counter);

	if (!time_counter)
	{
		HDMI_PRINTF("HDCP DRF1 time out!!!\n");
		return FALSE;
	}
	HDMI_PRINTF("[HDMI] DRF PAUSE OK (1/2)\n");

	rtd_maskl(DRF_RESUME_reg,
		~(DRF_RESUME_hdcp_drf_resume_mask|DRF_RESUME_audio_drf_resume_mask),
		(DRF_RESUME_hdcp_drf_resume(1)|DRF_RESUME_audio_drf_resume(1)));	//DRF_TEST_RESUME
	udelay(1000);
	rtd_maskl(DRF_RESUME_reg,~(DRF_RESUME_hdcp_drf_resume_mask|DRF_RESUME_audio_drf_resume_mask),0);	
	do			
	{
		udelay(1000);
		if (rtd_inl(DRF_PAUSE_reg)&(DRF_PAUSE_hdcp_drf_pause_mask|DRF_PAUSE_audio_drf_pause_mask))		//DRF_START_PAUSE
			break;
	}while(--time_counter);

	if (!time_counter)
	{
		HDMI_PRINTF("HDCP DRF2 time out!!!\n");
		return FALSE;
	}
	HDMI_PRINTF("[HDMI] DRF PAUSE OK (2/2)\n");

	rtd_maskl(DRF_RESUME_reg,
		~(DRF_RESUME_hdcp_drf_resume_mask|DRF_RESUME_audio_drf_resume_mask),
		(DRF_RESUME_hdcp_drf_resume(1)|DRF_RESUME_audio_drf_resume(1)));	//DRF_TEST_RESUME
	udelay(1000);
	rtd_maskl(DRF_RESUME_reg,~(DRF_RESUME_hdcp_drf_resume_mask|DRF_RESUME_audio_drf_resume_mask),0);	
	do			
	{
		udelay(1000);
		if (rtd_inl(DRF_DONE_reg)&(DRF_DONE_hdcp_drf_done_mask|DRF_DONE_audio_drf_done_mask))		//DRF_BIST_DONE
			break;
	}while(--time_counter);

	if (!time_counter)
	{
		HDMI_PRINTF("HDCP DRF3 time out!!!\n");
		return FALSE;
	}
	HDMI_PRINTF("[HDMI] DRF DONE\n");
	
	if (rtd_inl(DRF_FAIL_reg)&(DRF_FAIL_hdcp_drf_fail_mask|DRF_FAIL_audio_drf_fail_mask))
	{	//check success or fail,DRF_BIST_FAIL
		HDMI_PRINTF("HDCP DRF BIST fail!!!\n");
		return FALSE;
	}
	else
	{
		rtd_maskl(DRF_MODE_reg, ~(DRF_MODE_hdcp_drf_mode_mask|DRF_MODE_audio_drf_mode_mask), 0);		//HDCP drf disable	
		HDMI_PRINTF("[HDMI] BIST/DRF PASS\n");
		return TRUE;
	}
}

bool IsHDMIPortEnable(UINT8 pt)
{
	if ( pt==0 ) {
		return (Port0!=0);
	}
	else if ( pt==1 ) {
		return (Port1!=0);
	}
	else {
		return (Port2!=0);
	}
}

int QC_Verifier_HDMI_RX(void)
{
	int Result = SUCCESS;
	bool test_flag = TRUE;
	UINT16  i=0,j=0;

	printk("Sirius HDMI Rx QC Test\n");


//-------------------------------------
//  Reset Value Test
//-------------------------------------
//
//	return DefaultValueTest();
//
//-------------------------------------

    for ( i=0; i<HDMI_QCloop; i++ )
    {
        printk("[HDMI] LOOP=#%d\n", i+1);
        for ( j=0; j<3; j++ )
        {
            if ( IsHDMIPortEnable(j) )
            {
               test_flag &= QC_Hdmi_Main(j);
            }
#if 0//CONFIG_QC_MHL
            else if ( IsMHLPortEnable(j) )
            {
                test_flag &= QC_Mhl_Main(j);
            }
#endif
        }
#if LOOP_ERROR_BREAK
        if ( !test_flag )
        {
            break;
        }
#endif
    }

    if ( !test_flag )
    {
        Result = FAILED;
    }

//-------------------------------------
//  HDMI_BITERROR_TEST
//-------------------------------------
#if 0
	mdelay(1000);
	for ( j=0; j<10; j++ )
	{
		HDMI_Bit_Err_One_Time_Detect(
			VIDEO_BIT_ERR_DET_get_ch_sel(rtd_inl(VIDEO_BIT_ERR_DET_reg)), 
			VIDEO_BIT_ERR_DET_get_period(rtd_inl(VIDEO_BIT_ERR_DET_reg)),
			VIDEO_BIT_ERR_DET_get_thd(rtd_inl(VIDEO_BIT_ERR_DET_reg)));
		HDMI_Bit_Err_GetResult();
		mdelay(10);
	}
#endif

	
#if HDCP_BIST_Check
#define rstn_hdmirx	_BIT17
	if (!HDCP_BIST_CHECK())
	{
		Result |= FAILED;
		printk("[HDMI] WARNING: HDCP BIST/DRF FAIL!!!\n");
	}

	rtd_maskl(BIST_MODE_reg,~BIST_MODE_hdcp_bist_en_mask,0);  	//HDCP bist disable
	rtd_maskl(DRF_MODE_reg,~DRF_MODE_hdcp_drf_mode_mask,0);	//HDCP drf enable
#endif
	
	return Result;
} 

#if HDMI_BITERROR_TEST
// =============================================================================
//	Input:   	ch_sel
//			period
//			thershold
//   Return:    bit_err_thd
// =============================================================================
bool HDMI_Bit_Err_One_Time_Detect(UINT8 ch_sel, UINT8 period, UINT16 thd)
{
UINT8 tout=100;
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_mode_mask, 0); //mode
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_ch_sel_mask, VIDEO_BIT_ERR_DET_ch_sel(ch_sel)); //ch_sel
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_period_mask, VIDEO_BIT_ERR_DET_period(period)); //period
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_thd_mask, VIDEO_BIT_ERR_DET_thd(thd)); //thd
	
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_en_mask, 0); // disable
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_reset_mask, VIDEO_BIT_ERR_DET_reset_mask); //reset cnt
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_reset_mask, 0);
	HDMI_DELAYMS(1);
	rtd_maskl(VIDEO_BIT_ERR_STATUS_reg, 	//wclr_out
		~(VIDEO_BIT_ERR_STATUS_no_dis_reset_mask|VIDEO_BIT_ERR_STATUS_bit_err_thd_mask|VIDEO_BIT_ERR_STATUS_bit_err_mask|VIDEO_BIT_ERR_STATUS_bit_err_cnt_of_mask),
		(VIDEO_BIT_ERR_STATUS_no_dis_reset_mask|VIDEO_BIT_ERR_STATUS_bit_err_thd_mask|VIDEO_BIT_ERR_STATUS_bit_err_mask|VIDEO_BIT_ERR_STATUS_bit_err_cnt_of_mask));
	HDMI_DELAYMS(1);
	rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_en_mask, VIDEO_BIT_ERR_DET_en_mask);
	
	while( VIDEO_BIT_ERR_DET_get_en(rtd_inl(VIDEO_BIT_ERR_DET_reg)) && tout--)
	{
		HDMI_DELAYMS(1);
	}

	return VIDEO_BIT_ERR_STATUS_get_bit_err_thd(rtd_inl(VIDEO_BIT_ERR_STATUS_reg));
}

// =============================================================================
//	Input:   	ch_sel
//			thershold
//			enable
// =============================================================================
void HDMI_Bit_Err_Conti_Detect(UINT8 ch_sel, UINT16 thd, bool en_det)
{
	if ( en_det )
	{
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_mode_mask, 1); //mode
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_ch_sel_mask, VIDEO_BIT_ERR_DET_ch_sel(ch_sel)); //ch_sel
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_thd_mask, VIDEO_BIT_ERR_DET_thd(thd)); //thd
		
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_en_mask, 0); // disable
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_reset_mask, VIDEO_BIT_ERR_DET_reset_mask); //reset cnt
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_reset_mask, 0);
		HDMI_DELAYMS(1);
		rtd_maskl(VIDEO_BIT_ERR_STATUS_reg, 	//wclr_out
			~(VIDEO_BIT_ERR_STATUS_no_dis_reset_mask|VIDEO_BIT_ERR_STATUS_bit_err_thd_mask|VIDEO_BIT_ERR_STATUS_bit_err_mask|VIDEO_BIT_ERR_STATUS_bit_err_cnt_of_mask),
			(VIDEO_BIT_ERR_STATUS_no_dis_reset_mask|VIDEO_BIT_ERR_STATUS_bit_err_thd_mask|VIDEO_BIT_ERR_STATUS_bit_err_mask|VIDEO_BIT_ERR_STATUS_bit_err_cnt_of_mask));
		HDMI_DELAYMS(1);
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_en_mask, VIDEO_BIT_ERR_DET_en_mask);
	}
	else
	{
		rtd_maskl(VIDEO_BIT_ERR_DET_reg, ~VIDEO_BIT_ERR_DET_en_mask, 0);
	}
}

bool HDMI_Bit_Err_GetErrThdFlag(void)
{
	return VIDEO_BIT_ERR_STATUS_get_bit_err_thd(rtd_inl(VIDEO_BIT_ERR_STATUS_reg));
}

void HDMI_Bit_Err_GetResult(void)
{
	printk("[HDMI][BER] === Bit Error Rate Detection result ===\n");
	printk("[HDMI][BER] set ch=%d, mode=%d, period=%d, thd=%d\n", 
		VIDEO_BIT_ERR_DET_get_ch_sel(rtd_inl(VIDEO_BIT_ERR_DET_reg)), VIDEO_BIT_ERR_DET_get_mode(rtd_inl(VIDEO_BIT_ERR_DET_reg)), VIDEO_BIT_ERR_DET_get_period(rtd_inl(VIDEO_BIT_ERR_DET_reg)), VIDEO_BIT_ERR_DET_get_thd(rtd_inl(VIDEO_BIT_ERR_DET_reg)));
	printk("[HDMI][BER] ad max=%d\n", VIDEO_BIT_ERR_STATUS_get_ad_max(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] ad min=%d\n", VIDEO_BIT_ERR_STATUS_get_ad_min(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] no_dis_reset=%d\n", VIDEO_BIT_ERR_STATUS_get_no_dis_reset(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] bit_err_thd=%d\n", VIDEO_BIT_ERR_STATUS_get_bit_err_thd(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] bit_err=%d\n", VIDEO_BIT_ERR_STATUS_get_bit_err(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] bit_err_cnt_of=%d\n", VIDEO_BIT_ERR_STATUS_get_bit_err_cnt_of(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
	printk("[HDMI][BER] bit_err_cnt=%d\n", VIDEO_BIT_ERR_STATUS_get_bit_err_cnt(rtd_inl(VIDEO_BIT_ERR_STATUS_reg)));
}
#endif

#if READ_INFOFRAME
UINT8 Hdmi_GetSourceDeviceInfo(void)
{
    UINT8 infoframebuf[1];
    if ( Hdmi_ReadInfoFrameRSV2(0x83, 28, 1, infoframebuf) )
    {
        return infoframebuf[0];
    }
    return 0x00;
}

// =============================================================================
//	Input:   	typecode =  ex:0x82 is AVI, 0x83 is SPD, 0x84 is Audio
//			startpos   = start position from 0 (added to 109)
//			len          = the length of reading buffer
//   Return:    TRUE or FALSE
// =============================================================================
bool Hdmi_ReadInfoFrameRSV2(UINT8 typecode, UINT8 startpos, UINT8 len, UINT8 *buf)
{
    UINT8 t1 = 10;
    
    rtd_maskl(HDMI_HDMI_PTRSV1_VADDR, ~0x00FF00, typecode<< 8 );
    hdmi_out(HDMI_HDMI_GPVS_VADDR, _BIT6);  // Clear RSV2 indicator

    while (t1-- && !(hdmi_in(HDMI_HDMI_GPVS_VADDR) & _BIT6)) { HDMI_DELAYMS(2); };

    if ( !t1 )
    {
        return FALSE;
    }

    hdmi_out(HDMI_HDMI_PSAP_VADDR, 109+startpos);
    HDMI_DELAYMS(3);
    for (t1=0; t1<len; t1++)
    {
        HDMI_DELAYMS(1);
        buf[t1] = hdmi_in(HDMI_HDMI_PSDP_VADDR);
    }
    
    return TRUE;
}
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	RESET VALUE TEST
//	1. use Mac2 tool: TV_Spec_Parser_1168.exe (Open Spec, gen r/w C function), then output init test c file.
//	2. copy init test function to here. (search "REPLACE FUNCTION FOR TESTING")
//	3. modify #define TEST_FUNC()
//	4. modify caller function.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEST_FUNC cbus_regsReadInitTest
int TEST_FUNC(void);

int DefaultValueTest(void)
{
	rtd_outl(0xb8000000, 0xFFFFFFFF);
	rtd_outl(0xb8000004, 0xFFFFFFFF);
	rtd_outl(0xb8000008, 0xFFFFFFFF);

	rtd_outl(0xb800000c, 0xFFFFFFFF);
	rtd_outl(0xb8000010, 0xFFFFFFFF);
	rtd_outl(0xb8000014, 0xFFFFFFFF);
	mdelay(10);
	rtd_outl(0xb8060030, 0xFFFFFFFF);
	rtd_outl(0xb8060034, 0xFFFFFFFF);

	rtd_outl(0xb8060040, 0xFFFFFFFF);
	rtd_outl(0xb8060044, 0xFFFFFFFF);

	if ( 0x00000000 == (rtd_inl(0xb8007b44) & 0xfff7ffff) ) {
		printk("\n0xb8007b44: OK\n\n");
	}
	else {
		printk("\n0xb8007b44: NG\n\n");
	}

	rtd_outl(0xb8007b44,0x00700024);		//PLL and VCO release reset
	mdelay(10);
	rtd_outl(0xb8007b44,0x7f700024);		//RGB CDR reset
	mdelay(10);

	if ( TEST_FUNC() ) {
		return FAILED;
	}
	else {
		printk("\nDefault Value Test: PASS\n\n");
		return SUCCESS;
	}

}


void WriteREG(unsigned long addr, unsigned long data)
{
	*((volatile unsigned long *)(addr)) = data;
}

unsigned long ReadREG(unsigned long addr)
{
	//return *((volatile unsigned long *)(addr));
	return rtd_inl(addr);
}

int OneRegInitTest(unsigned long addr, unsigned long expectedValue,unsigned long mask,
	unsigned char portAccess, unsigned long portAddr, unsigned long portNum, unsigned long portMask)
{
	unsigned long initValue;

	expectedValue = expectedValue & mask;
	if(portAccess)
	{
		WriteREG(portAddr, (ReadREG(portAddr)&(~(portMask)))|(portNum&portMask));  // set port number
	}
	initValue = ReadREG(addr) & mask;
	if(initValue != expectedValue)
	{
		printk("ERROR initial value from reg 0x%08x, expected=0x%08x, actual=0x%08x\n", (int)addr, (int)expectedValue, (int)initValue);
		return 1;
	}
	return 0;
}

//
// REPLACE FUNCTION FOR TESTING
//
int cbus_regsReadInitTest(void)
{
	unsigned long regAddr;
	unsigned long regExpectedValue;
	unsigned long mask;
//	unsigned char pageNum;
	unsigned char portAccess;
	unsigned long portAddr;
	unsigned long portNum;
	unsigned long portMask;
	int ret = 0;

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b00;
	regExpectedValue = 0x00000000;
	mask = 0x0000000f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b04;
	regExpectedValue = 0x00003607;
	mask = 0x00003fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b08;
	regExpectedValue = 0x00000061;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b10;
	regExpectedValue = 0x00001208;
	mask = 0x00003fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b14;
	regExpectedValue = 0x00000048;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b18;
	regExpectedValue = 0x00000085;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b1c;
	regExpectedValue = 0x00000080;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b20;
	regExpectedValue = 0x00000000;
	mask = 0x0000003d;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b24;
	regExpectedValue = 0xffff0000;
	mask = 0xffffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b30;
	regExpectedValue = 0x00000000;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b34;
	regExpectedValue = 0x88059401;
	mask = 0xffffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b38;
	regExpectedValue = 0x00000000;
	mask = 0x00000001;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb8062b3c;
	regExpectedValue = 0x00000a10;
	mask = 0x00000fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d000;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d004;
	regExpectedValue = 0x00000020;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d008;
	regExpectedValue = 0x00000031;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d00c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d010;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d014;
	regExpectedValue = 0x0000003f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d018;
	regExpectedValue = 0x00000003;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d01c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d020;
	regExpectedValue = 0x00000049;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d024;
	regExpectedValue = 0x0000000f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d028;
	regExpectedValue = 0x0000001f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d02c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d030;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d034;
	regExpectedValue = 0x00000010;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d038;
	regExpectedValue = 0x00000033;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d03c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d080;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d084;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d088;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d08c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d090;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d094;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d098;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d09c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0c0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0c4;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0c8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0cc;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0d0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0d4;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0d8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d0dc;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d100;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d104;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d108;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d10c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d110;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d114;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d118;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d11c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d120;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d124;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d128;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d12c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d130;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d134;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d138;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d13c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d140;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d144;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d148;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d14c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d150;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d154;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d158;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d15c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d160;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d164;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d168;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d16c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d170;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d174;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d178;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d17c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d200;
	regExpectedValue = 0x00018471;
	mask = 0x0003ffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d204;
	regExpectedValue = 0x00004821;
	mask = 0x0000ffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d208;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d20c;
	regExpectedValue = 0x0000004d;
	mask = 0x000001ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d210;
	regExpectedValue = 0x00000065;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d214;
	regExpectedValue = 0x0000000f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d218;
	regExpectedValue = 0x0000000d;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d21c;
	regExpectedValue = 0x00000032;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d220;
	regExpectedValue = 0x00000065;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d224;
	regExpectedValue = 0x00000074;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d228;
	regExpectedValue = 0x00000046;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d22c;
	regExpectedValue = 0x0000003f;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d230;
	regExpectedValue = 0x00000027;
	mask = 0x0000007f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d234;
	regExpectedValue = 0x00000040;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d238;
	regExpectedValue = 0x00000059;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d23c;
	regExpectedValue = 0x00000030;
	mask = 0x0000003f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d240;
	regExpectedValue = 0x00000065;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d244;
	regExpectedValue = 0x00000032;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d248;
	regExpectedValue = 0x00000084;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d24c;
	regExpectedValue = 0x00000058;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d250;
	regExpectedValue = 0x00000078;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d260;
	regExpectedValue = 0x00000010;
	mask = 0x0000003f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d264;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d268;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d26c;
	regExpectedValue = 0x00000040;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d270;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d274;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d278;
	regExpectedValue = 0x00000000;
	mask = 0x1fffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d27c;
	regExpectedValue = 0x00000000;
	mask = 0x1fffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d280;
	regExpectedValue = 0x00000000;
	mask = 0xffffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d284;
	regExpectedValue = 0x00000000;
	mask = 0xffffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d288;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d28c;
	regExpectedValue = 0x00000000;
	mask = 0x000003ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d290;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d294;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d298;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d29c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2a0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2a4;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2a8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2ac;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2b0;
	regExpectedValue = 0x0000000f;
	mask = 0x0000003f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2b4;
	regExpectedValue = 0x00000000;
	mask = 0x0000ffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2b8;
	regExpectedValue = 0x04100000;
	mask = 0x3fffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2bc;
	regExpectedValue = 0x00000000;
	mask = 0x00000007;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2c0;
	regExpectedValue = 0x00000000;
	mask = 0x00000fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2c4;
	regExpectedValue = 0x0000000f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2c8;
	regExpectedValue = 0x00000023;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2cc;
	regExpectedValue = 0x00000033;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2d0;
	regExpectedValue = 0x0000004f;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2d4;
	regExpectedValue = 0x00000000;
	mask = 0x00000003;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2d8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2dc;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2e0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2e4;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d2e8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d300;
	regExpectedValue = 0x00000022;
	mask = 0x000001ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d304;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d308;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d30c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d310;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d314;
	regExpectedValue = 0x00000000;
	mask = 0x000003ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d318;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d31c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d320;
	regExpectedValue = 0x00000000;
	mask = 0x00003fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d340;
	regExpectedValue = 0x00000022;
	mask = 0x000001ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d344;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d348;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d34c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d350;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d354;
	regExpectedValue = 0x00000000;
	mask = 0x000003ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d358;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d35c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d360;
	regExpectedValue = 0x00000000;
	mask = 0x00003fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d380;
	regExpectedValue = 0x00000022;
	mask = 0x000001ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d384;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d388;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d38c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d390;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d394;
	regExpectedValue = 0x00000000;
	mask = 0x000003ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d398;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d39c;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3a0;
	regExpectedValue = 0x00000000;
	mask = 0x00003fff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3c0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3c4;
	regExpectedValue = 0x00000012;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3c8;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3cc;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3d0;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3d4;
	regExpectedValue = 0x00000000;
	mask = 0x000000ff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3d8;
	regExpectedValue = 0x00000002;
	mask = 0x0000000f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3e0;
	regExpectedValue = 0x00000000;
	mask = 0x0000003f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3e4;
	regExpectedValue = 0x00000000;
	mask = 0x0000003f;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3e8;
	regExpectedValue = 0x00000000;
	mask = 0x000000fc;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	portAccess = 0;
	portAddr = 0;
	portNum = 0;
	portMask = 0;
	regAddr = 0xb806d3ec;
	regExpectedValue = 0x0000ffff;
	mask = 0xffffffff;
	ret |= OneRegInitTest(regAddr, regExpectedValue, mask, portAccess, portAddr, portNum, portMask);

	return ret;
}

