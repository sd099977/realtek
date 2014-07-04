
#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "TV.h"
#include "TVE_reg.h"
#include "hdmi_tx_struct_def.h"

//#######################################################################################################
//
//  File Name:      HDMI_function.C
//  Description:    HDMI function 
//
//#######################################################################################################
//extern void UART_WRITE(unsigned int *, UINT32);
//extern void UART_WRITECH(unsigned int *);
extern void BusyWaiting(UINT32);

extern UINT8 AudioCodingType;
extern UINT8 AudioChannelCount;
extern UINT8 SamplingFrequency;
extern UINT8 SampleSize;
extern UINT8 Test_Mode;

extern unsigned int *sumbuf;

void HDMI_SetRamPacket(unsigned int pkt_no, unsigned char *pkt)
{
    unsigned char tpkt[36];
    unsigned long *reg = (unsigned long *)tpkt;
    unsigned int addr = pkt_no*14;
	    //printf("HDMI test start........32_03_01\n");
	
	*sumbuf=0;
		    //printf("HDMI test start........32_03_02\n");
	*sumbuf=pkt[3];
	//printf("HDMI test start........32_03_03\n");
	tpkt[3]  =	0;
	tpkt[2]  =	pkt[2];
	tpkt[1]  =	pkt[1];
	tpkt[0]  =	pkt[0];

	tpkt[7]  =	pkt[6];
	tpkt[6]  =	pkt[5];
	tpkt[5]  =	pkt[4];
	tpkt[4]  =	pkt[3];

	tpkt[11] =  0;
	tpkt[10] =  pkt[9];
	tpkt[9]  =	pkt[8];
	tpkt[8]  =	pkt[7];

	tpkt[15] =  pkt[13];
	tpkt[14] =  pkt[12];
	tpkt[13] =  pkt[11];
	tpkt[12] =  pkt[10];

	tpkt[19] =  0;
	tpkt[18] =  pkt[16];
	tpkt[17] =  pkt[15];
	tpkt[16] =  pkt[14];

	tpkt[23] =  pkt[20];
	tpkt[22] =  pkt[19];
	tpkt[21] =  pkt[18];
	tpkt[20] =  pkt[17];

	tpkt[27] =  0;
	tpkt[26] =  pkt[23];
	tpkt[25] =  pkt[22];
	tpkt[24] =  pkt[21];

	tpkt[31] =  pkt[27];
	tpkt[30] =  pkt[26];
	tpkt[29] =  pkt[25];
	tpkt[28] =  pkt[24];

	tpkt[35] =  0;
	tpkt[34] =  pkt[30];
	tpkt[33] =  pkt[29];
	tpkt[32] =  pkt[28];
	    //printf("HDMI test start........32_03_04\n");
	//write mode===============================================================	
	/*adam setting
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
	*/
	// 0xb800d07c
	rtd_outl(HDMI_ORP6PH_reg, HDMI_ORP6PH_once_pkt(reg[0]));
	// 0xb800d080
	rtd_outl(HDMI_ORP6W_0_reg, HDMI_ORP6W_once_pkt(reg[1]));
	// 0xb800d084
	rtd_outl(HDMI_ORP6W_1_reg, HDMI_ORP6W_once_pkt(reg[2]));
	// 0xb800d088
	rtd_outl(HDMI_ORP6W_2_reg, HDMI_ORP6W_once_pkt(reg[3]));
	// 0xb800d08c
	rtd_outl(HDMI_ORP6W_3_reg, HDMI_ORP6W_once_pkt(reg[4]));
	// 0xb800d090
	rtd_outl(HDMI_ORP6W_4_reg, HDMI_ORP6W_once_pkt(reg[5]));
	// 0xb800d094
	rtd_outl(HDMI_ORP6W_5_reg, HDMI_ORP6W_once_pkt(reg[6]));
	// 0xb800d098
	rtd_outl(HDMI_ORP6W_6_reg, HDMI_ORP6W_once_pkt(reg[7]));
	// 0xb800d09c
	rtd_outl(HDMI_ORP6W_7_reg, HDMI_ORP6W_once_pkt(reg[8]));
	//0xb800d0b0
	rtd_outl(HDMI_OPCR_reg,
	                 HDMI_OPCR_write_en4(1)|HDMI_OPCR_enrbpktsram(1)|
					 HDMI_OPCR_write_en3(1)|HDMI_OPCR_wrdes(0)|
					 HDMI_OPCR_write_en2(1)|HDMI_OPCR_rprwcmd(1)|
					 HDMI_OPCR_write_en1(1)|HDMI_OPCR_rpadd(addr&0x0ff));
	//printf("HDMI test start........32_03_05\n");
	BusyWaiting(10000);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HDMI_gen_audio_infoframe(UINT8 ChannelNumber)
{
    UINT8  pkt[32];
    UINT32 checksum=0;
    UINT32 i;
	UINT8  InforFrameType = 0x84;
	UINT8  InforFrameVersion = 0x01;
	UINT8  InforFrameLength = 10;
	//UINT8  CC2CC1CC0 = 0; //Audio Channel Count
	//UINT8  CT3CT2CT1CT0 = 0; //Audio Coding Type 
	//UINT8  SS1SS0 = 0; //
	//UINT8  SF2SF1SF0 = 0; //
	//UINT8  CA70 = 0; //
	UINT8  LSV30 = 0; //
	UINT8  DM_INH = 0; //

	//clear buffer=============================================================	
	for(i=0; i<31; i++)
	{
		pkt[i]=0;
	}
	//header===================================================================	
	pkt[0] = InforFrameType;
	pkt[1] = InforFrameVersion;
	pkt[2] = InforFrameLength;
	pkt[3] = checksum;	
	//data=================================================================	
	if(Test_Mode==1) //for Panasonic Analyzer
	{
		pkt[4] = 0x07&ChannelNumber;
		pkt[5] = 0;
		pkt[6] = 0;
	    switch(AudioChannelCount)
	    {
		    case 1: //2ch
			    pkt[7] = 0x0;
			    break;
		    case 2: //3ch
			    pkt[7] = 0x1;
			    break;
		    case 3: //4ch
			    pkt[7] = 0x8;
			    break;
		    case 4: //5ch
			    pkt[7] = 0x9;
			    break;
		    case 5: //6ch
			    pkt[7] = 0xb;
			    break;
		    case 6: //7ch
			    pkt[7] = 0xf;
			    break;
		    case 7: //8ch
			    pkt[7] = 0x13;
			    break;
		    default:
			    break;
	    }
		pkt[8] = 0;
	}
	else
	{
	    pkt[4] =0xf7&((AudioCodingType<<4)|(AudioChannelCount));
	    pkt[5] =0x1f&((SamplingFrequency<<2)|(SampleSize));
	    pkt[6] =0x0;
	    switch(AudioChannelCount)
	    {
		    case 1: //2ch
			    pkt[7] = 0x0;
			    break;
		    case 2: //3ch
			    pkt[7] = 0x1;
			    break;
		    case 3: //4ch
			    pkt[7] = 0x8;
			    break;
		    case 4: //5ch
			    pkt[7] = 0x16;
			    break;
		    case 5: //6ch
			    pkt[7] = 0xb;
			    break;
		    case 6: //7ch
			    pkt[7] = 0xf;
			    break;
		    case 7: //8ch
			    pkt[7] = 0x13;
			    break;
		    default: //2ch
			    break;
	    }
	    pkt[8] =0xf8&((DM_INH<<7)|(LSV30<<3));
	}

	//count checksum===========================================================	
	for(i=0; i<31; i++)
		checksum +=	pkt[i];
	pkt[3] = (~checksum	+ 1) & 0xff;

	//set to RAM Packet========================================================
	HDMI_SetRamPacket(1, pkt);
	
    //set======================================================================
    //0xb800d0a0
    rtd_outl(HDMI_RPCR_reg,
                     HDMI_RPCR_write_en6(0)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(0)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(0)|HDMI_RPCR_prp3period(0)|
                     HDMI_RPCR_write_en3(0)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(1)|HDMI_RPCR_prp1period(1)|
                     HDMI_RPCR_write_en1(0)|HDMI_RPCR_prp0period(0));
    //0xb800d0a4
    rtd_outl(HDMI_RPEN_reg,
                     HDMI_RPEN_enprpkt5(0)|
                     HDMI_RPEN_enprpkt4(0)|
                     HDMI_RPEN_enprpkt3(0)|
                     HDMI_RPEN_enprpkt2(0)|
                     HDMI_RPEN_enprpkt1(1)|
                     HDMI_RPEN_enprpkt0(0)|
                     HDMI_RPEN_write_data(1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HDMI_gen_avi_infoframe(UINT8 Video_Code, UINT8 RGB_YCbCr, UINT8 xv_YCC)
{
    UINT8  pkt[32];
    UINT8  checksum = 0;
    UINT8  i;
    UINT8  InforFrameType = 0x82;
    UINT8  InforFrameVersion = 0x02;
    UINT8  InforFrameLength = 13;
    UINT8  S1S0 = 0; //0=>No data, 1=>overscanned, 2=>underscanned
    UINT8  B1B0 = 0; //0=>No data, 1=>V Bar Info valid, 2=>H Bar Info valid, 3=>V&H Bar Info valid 
    UINT8  A0 = 1; //0=>No data, 1=>Active Format Infomation present
    UINT8  Y1Y0 = RGB_YCbCr; //0=>RGB, 1=>YCbCr422, 2=>YCbCr444
    UINT8  F7 = 0;
    UINT8  R3R2R1R0 = 8; //8=>Same as picture aspect ratio, 9=>4:3, 10=>16:9, 11=>14:9
    UINT8  M1M0; //0=>No Data, 1=>4:3, 2=>16:9
    UINT8  C1C0; //0=>No Data, 1=>ITU601, 2=>ITU709, 3=>Extended Colorimetry Valid
    UINT8  SC1SC0 = 0; //0=>unknown, 1=>Scaled H, 2=>Scaled V, 3=>Scaled V&H
    UINT8  Q1Q0 = 0; //0=>default, 1=>Limited Range, 2=>Full Range
    UINT8  EC2EC1EC0 = 2; //0=>xvYCC601, 1=>xvYCC709, 2=>reserved
    UINT8  ITC = 0; //0=>No data, 1=>IT content
    UINT8  PR3PR2PR1PR0; //0:Pixel No Repetition, 1:Pixel sent 2 times

	   // printf("HDMI test start........32_01\n");
    switch(Video_Code)
    {
        //SD display mode===================================
        case 6: //480i
        case 21: //576i
            M1M0 = 1;
            if(xv_YCC)
            {
                C1C0 = 3;
                EC2EC1EC0 = 0;
                //Q1Q0 = 2;
            }
            else C1C0 = 1;
            PR3PR2PR1PR0 = 1;
            break;
        case 2: //480P
        case 17: //576P
            M1M0 = 1;
            if(xv_YCC)
            {
                C1C0 = 3;
                EC2EC1EC0 = 0;
                //Q1Q0 = 2;
            }
            else C1C0 = 1;
            PR3PR2PR1PR0 = 0;
            break;
        //HD Display mode===================================
        case 4: //720p60
        case 5: //1080i60
        case 19: //720p50
        case 20: //1080i50
        case 32: //1080p24
        case 31: //1080p50
        case 16: //1080p60
        case 95: //4k2k@30
            M1M0 = 2;
            if(xv_YCC)
            {
                C1C0 = 3;
                EC2EC1EC0 = 1;
                //Q1Q0 = 2;
            }
            else C1C0 = 2;
            PR3PR2PR1PR0 = 0;
            break;
        default:
            break;
    }

	   // printf("HDMI test start........32_02\n");
    if(Y1Y0==3) Y1Y0=1;

    //clear buffer=============================================================
    for(i=0; i<31; i++)	 pkt[i]=0;

    //header===================================================================
    pkt[0] = InforFrameType;
    pkt[1] = InforFrameVersion;
    pkt[2] = InforFrameLength;
    pkt[3] = checksum;
    //data=====================================================================
    pkt[4] = 0x7f&((F7<<7)|(Y1Y0<<5)|(A0<<4)|(B1B0<<2)|(S1S0));
    pkt[5] = (C1C0<<6)|(M1M0<<4)|(R3R2R1R0);
    pkt[6] = (ITC<<7)|(EC2EC1EC0<<4)|(Q1Q0<<2)|(SC1SC0);
    pkt[7] = 0x7f&Video_Code;
    pkt[8] = 0x0f&PR3PR2PR1PR0; //480i,576i=1,others:0
    pkt[9] = 0;
    pkt[10] = 0;
    pkt[11] = 0;
    pkt[12] = 0;
    pkt[13] = 0;
    pkt[14] = 0;
    pkt[15] = 0;
    pkt[16] = 0;

	    //printf("HDMI test start........32_03\n");
    for(i=0; i<31; i++)  checksum += pkt[i];
    pkt[3] = (~checksum	+ 1) & 0xff;

    //set to RAM Packet========================================================
    HDMI_SetRamPacket(0,pkt);

	/*adam setting
    rtd_outl(0xb800d0a0, 0x00000011);  // write trnsmission period of periodic island packet SRAM
	rtd_outl(0xb800d0a4, 0x00000003);  // enable transmission periodic island packet (active when [0]=1)
	*/
	    //printf("HDMI test start........32_04\n");
    //set======================================================================
    // 0xb801d0a0
    rtd_outl(HDMI_RPCR_reg,
                     HDMI_RPCR_write_en6(0)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(0)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(0)|HDMI_RPCR_prp3period(0)|
                     HDMI_RPCR_write_en3(0)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)|
                     HDMI_RPCR_write_en1(1)|HDMI_RPCR_prp0period(1));
    // 0xb801d0a4
    rtd_outl(HDMI_RPEN_reg,
                     HDMI_RPEN_enprpkt5(0)|
                     HDMI_RPEN_enprpkt4(0)|
                     HDMI_RPEN_enprpkt3(0)|
                     HDMI_RPEN_enprpkt2(0)|
                     HDMI_RPEN_enprpkt1(0)|
                     HDMI_RPEN_enprpkt0(1)|
                     HDMI_RPEN_write_data(1));
	
	    //printf("HDMI test start........32_05\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HDMI_gen_vendor_Specific_infoframe(UINT8 ext_video, UINT8 format)
{
    UINT8  pkt[32];
    UINT8  checksum = 0;
    UINT8  i;
    UINT8  InforFrameType = 0x81;
    UINT8  InforFrameVersion = 0x01;
    UINT8  vsif_byte4, vsif_byte5, Format_3D;
    //clear buffer=============================================================
    for(i=0; i<31; i++)	 pkt[i]=0;

    vsif_byte4 = ext_video << VSIF_VIDEO_FORMAT_BIT;
    if (ext_video == HDMI_TX_EXTENDED_RESOLUTION_3D_FORMAT)
    {
        vsif_byte5 = format << VSIF_3D_FORMAT_BIT;
        Format_3D = format;
    }
    else
    {
        vsif_byte5 = format;
    }
    //header===================================================================
    pkt[0] = InforFrameType;
    pkt[1] = InforFrameVersion;

    if ((ext_video == HDMI_TX_EXTENDED_RESOLUTION_3D_FORMAT) &&
        (Format_3D == 8))
    {
        pkt[2] = 0x06;//InforFrameLength;
        pkt[9] = 0x0; //3D Ext Data
    }
    else
    {
        pkt[2] = 0x05;//InforFrameLength;
    }

    if(Format_3D==8)
    {
        pkt[2] = 0x06;//InforFrameLength;
    }
    else
    {
        pkt[2] = 0x05;//InforFrameLength;
    }    
    pkt[3] = checksum;
    //data=====================================================================
    pkt[4] = 0x03;
    pkt[5] = 0x0c;
    pkt[6] = 0x00;
    pkt[7] = vsif_byte4;
    pkt[8] = vsif_byte5;

    for(i=0; i<31; i++)  checksum += pkt[i];
    pkt[3] = (~checksum	+ 1) & 0xff;

    //set to RAM Packet========================================================
    HDMI_SetRamPacket(3,pkt);

    //set======================================================================
    // 0xb801d0a0
    rtd_outl(HDMI_RPCR_reg,
                     HDMI_RPCR_write_en6(0)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(0)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(1)|HDMI_RPCR_prp3period(1)|
                     HDMI_RPCR_write_en3(0)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)|
                     HDMI_RPCR_write_en1(0)|HDMI_RPCR_prp0period(0));
    // 0xb801d0a4
    rtd_outl(HDMI_RPEN_reg,
                     HDMI_RPEN_enprpkt5(0)|
                     HDMI_RPEN_enprpkt4(0)|
                     HDMI_RPEN_enprpkt3(1)|
                     HDMI_RPEN_enprpkt2(0)|
                     HDMI_RPEN_enprpkt1(0)|
                     HDMI_RPEN_enprpkt0(0)|
                     HDMI_RPEN_write_data(1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HDMI_gen_metadata()
{
    UINT8   pkt[32];
    UINT32  checksum=0;
    UINT32  i;

    UINT32 Next_Field = 1;
    UINT32 GBD_profile = 0;
    UINT32 Affected_Gamut_Seq_Num = 0;
    UINT32 Current_Gamut_Seq_Num = 0;
    UINT32 Packet_Seq = 3;
    UINT32 No_Current_DBG = 0;

	//clear buffer=============================================================
	for(i=0; i<31; i++) pkt[i]=0;

	//header===================================================================
	pkt[0] = 0xa;
	pkt[1] = (Next_Field << 7) | (GBD_profile << 4) | (Affected_Gamut_Seq_Num);
	pkt[2] = (No_Current_DBG << 7) | (Packet_Seq<<4) | (Current_Gamut_Seq_Num);
	pkt[3] = checksum;
	//data===================================================================== 
	pkt[4] = 0x1;
 	pkt[5] = 0x0;
 	pkt[6] = 0x4;
 	pkt[7] = 16;    //black
 	pkt[8] = 128;
 	pkt[9] = 128;
 	pkt[10] = 81;   // red
 	pkt[11] = 90;
 	pkt[12] = 240;
 	pkt[13] = 144;    // green
 	pkt[14] = 53;
 	pkt[15] = 34;
 	pkt[16] = 40;     // blue
 	pkt[17] = 240;
 	pkt[18] = 109;
 	*sumbuf = 0;

	//count checksum===========================================================	
	for(i=0; i<31; i++)
	{
		checksum +=	pkt[i];
		*sumbuf=checksum;
	}
	*sumbuf	= (~checksum + 1) & 0xff;
	pkt[3] = (~checksum	+ 1) & 0xff;
	*sumbuf=0;
	*sumbuf=pkt[3];

	//set to RAM Packet========================================================
	HDMI_SetRamPacket(2,pkt);

	//set======================================================================
	//0xb801d0a0
	rtd_outl(HDMI_RPCR_reg,
	            	 HDMI_RPCR_write_en6(0)|HDMI_RPCR_prp5period(0)|
					 HDMI_RPCR_write_en5(0)|HDMI_RPCR_prp4period(0)|
					 HDMI_RPCR_write_en4(0)|HDMI_RPCR_prp3period(0)|
					 HDMI_RPCR_write_en3(1)|HDMI_RPCR_prp2period(1)|
					 HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)|
					 HDMI_RPCR_write_en1(0)|HDMI_RPCR_prp0period(0));
    //0xb801d0a4
	rtd_outl(HDMI_RPEN_reg,	HDMI_RPEN_enprpkt5(0)|
					 HDMI_RPEN_enprpkt4(0)|
					 HDMI_RPEN_enprpkt3(0)|
					 HDMI_RPEN_enprpkt2(1)|
					 HDMI_RPEN_enprpkt1(0)|
					 HDMI_RPEN_enprpkt0(0)|
					 HDMI_RPEN_write_data(1));
}

