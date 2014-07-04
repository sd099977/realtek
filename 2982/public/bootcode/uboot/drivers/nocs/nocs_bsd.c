/*
 *  This is a driver for the NOCS3 Bare Security Driver API
 *  in Realtek RTD298X SoCs.
 *
 *  Copyright (C) 2014 Realtek Semiconductors, All Rights Reserved.
 *
 *
 *
 */

/* ==========================================================================

1. SVN Path:
   ==> http://cadinfo.realtek.com.tw/svn/col/DVR/sirius/software/system/bootcode/uboot/drivers/nocs
2. Open the compiler options, head first into uboot
  http://cadinfo.realtek.com.tw/svn/col/DVR/sirius/software/system/bootcode/uboot/
  ==> vi ./uboot/include/configs/rtd298x_common.h +13
  //NOCS BSD support
  #define CONFIG_NOCS_BSD       1
3. Adding the following settings at Makefile
  http://cadinfo.realtek.com.tw/svn/col/DVR/sirius/software/system/bootcode/uboot/Makefile
  ==> vi Makefile
LIBS-$(CONFIG_NOCS_BSD) += drivers/nocs/nocs_bsd.o

3.0 關閉bootcode cache
vi ./uboot/include/configs/rtd298x_common.h +213

3.1 編譯指令
    The target board used is QFP176 ver1,
    So I chosen complier option "RTD298X_tv001_qfp176_ddr_512m_x16"
    ./bootcode_NOCS/bin
    ==> make PRJ=RTD298X_tv001_qfp176_ddr_512m_x16; cp ../tools/flash_image_maker/qq.bin /home/alexkh/tftproot_OS/qq_nocs.bin

4. OTP driver
http://172.21.0.100/svn/col/DVR/branches/software/system/src/Platform_Lib/OTPControl

5. Spec for CERT/KeyTable/Key Ladder
CERT : NOCS3_IP_Block_NSR_Realtek_v010004.docx
  ==> local at : D:\Spec\Nagra\NOCS3_IP_Block_NSR_Realtek_v010004.docx
Key Ladder:
  ==> http://cadinfo/svn/MM/RL6330_PC/trunk/doc/Hardware/arch_spec_for_CA/Sirius_Nagxx_SCE_Arch_Spec.doc
Key Table :
  ==> http://cadinfo/svn/MM/RL6330_PC/trunk/doc/Hardware/arch_spec_for_CA/Sirius_NOCS_KeyTable_arch_spec.doc
DSC:
  ==> 使用MD做, 因此只要看MD的Spec即可
      http://cadinfo/svn/MM/RL6330_PC/trunk/doc/Hardware/arch_spec/Sirius_MD_Arch_Spec.doc

6. SEC API AVN path
  ==> http://cadinfo/svn/col/DVR/sirius/doc/software/nagra/drivers/NOCS3/

7. Test Harness 相關訊息
http://cadinfo.realtek.com/svn/col/DVR/sirius/software/nagra/NOCS_Test_Harness

 解開之後
    可以進入Test_Harness 目錄打
    ./Install.sh -b baseline.txt -o xxxx
    就會產生在 xxxx 目錄下

    可以進入Realtek_SiriusA0_Test_Harness_delivery_v2.0.0/
    打 bash Install.bash -b siriusA0_baseline_2.0.0.txt -o xxxx
    就會產生 for PC 的相關資訊於 xxxx 目錄下

    可以看一下兩個目錄下面的 Readme.txt
    裡面有詳細的解說

8. toolchain path
    PATH="/home/alexkh/nfs/kernel/sirius/bootcode_NOCS/tmp/asdk-4.8.2-a7-EL-3.7-0.9.33-a32nt-131122/bin/:"$PATH

9. rpc server 的位置
    /nfs/kernel/sirius/bootcode_NOCS/uboot/drivers/nocs/rpc/chipset/server/lib/BSD/TAGS/3.3.1/distrib
    編譯的指令
    ==> make all

10. 關於 BSD,參考一下
    http://cadinfo.realtek.com/svn/col/DVR/sirius/software/nagra/NOCS3_Integration_Certification_Kit_v1.2.2/4.NOCS Functional Certification Documents/CC_SPE_NOCS3xTestMaterialSpecification.pdf
    裡面的第五章,看看是否跟現在實作和認知的相同

11. Encryption Method Indicator (EMI)
    BSD中會用的EMI如下
    Algorithm       EMI
    AES-128-ECB     0x4021
    AES-128-CBC     0x4026
    TDES-128-ECB    0x4041
    TDES-128-CBC    0x4043

====================================================================
測試環境設定與實作
0. ==> startup of target board, push key "ESC" then
       push reset bottum of target board to enter bootcode console.
   ==> type "rtkbsd rpc" entry RPC mode

1. VM host
    VM的登入帳密
    ID= user; PW=pwduser
2. VM的環境中己經將host的RPC server安裝完成,放罝的位罝
    /home/user/Realtek_SiriusA0_Test_Harness_delivery_v2.0.0/host/Tools
3. BSD測試 要執行./bsd
4. BSD使用uart port1 做為RPC server 所以要編寫如下的設定檔
    ==> echo "term:/dev/ttyS1@115200" > bsd.ipccfg
    用/dev/ttyS2 是因為目前使用uart1 做為RPC port, uart0 仍做為debug port
5. 一些指令的範例在以下的位置可以找到,相關的測試scripter
    ==> me/user/Realtek_SiriusA0_Test_Harness_delivery_v2.0.0/host/TestVectors/TestScripts
    例如 ./API_M-NOCS30-BSD-FN-0000.txt
         ./TC_M-NOCS30-VALSFT-FN-0045.txt
         ./TC_M-NOCS30-VALSFT-FN-0070.txt
         ./TC_M-NOCS30-VALSFT-FN-0091.txt

===============================================
測試的scripter
BSD_CMD_LIST.txt  ==> grep出來的原始資料
BSD_CMD_LIST2.txt ==> 去掉重覆命令的部份
BSD_CMD_LIST3.txt ==> 完整的測試scripter,包含輸出檔案的設定,以及通過測試的註記
BSD_CMD_LIST4.txt ==> 去掉輸出檔案的設定,進行實驗時比較方便,平時用這個檔案

===============================================
Cygwin 環境的 Test Harnest測試

1. Cygwin環境 host的RPC server 放罝的位罝
    /cygdrive/y/TMP/NTHAPPs_PKG_EXT-02_06_00

2. 開RPC log的指令 --enable_nht_ftrace --enable_ftrace


===========================================================================*/
#include "nocs_bsd_env.h"
#include <linux/crc32.h>
#include "print_rpc.h"

#include "nocs_bsd.h"
#include "rtk_bsd.h"
#include "emi.h"
#include "kt_reg.h"
#include "key_ladder_reg.h"
#include "md_dsc_reg.h"

#include "otp_util.h"
#include "otp_tbl.h"
#include "otp_reg.h"
#include "otp_debug.h"
#include "otp_cp_reg.h"
#include "nocs_bsd_impl.h"
#include "test_bsd_header.h"
#include "bsd_server.h"
#include "ca_cert.h"
#include "mcp_buff.h"
#include "mcp.h"
#include "./rpc/chipset/EAPI/nht_term/TAGS/1.2.0/distrib/inc/nht_term.h"

/****************************************************************************/
/*                                                                          */
/* ==================== LOCAL DEFINE ==================== */
/*                                                                          */
/****************************************************************************/

#define BSD_DRVNAME         "NOCS_BSD:"
#define MANUFACTURE_NAME    "ARTK"
#define RTK_BSD_CM          MANUFACTURE_NAME

#define MAX_KEY_TABLE_ENTRY     64
#define SESSION_HANDLE_NUM      MAX_KEY_TABLE_ENTRY

/*bit definition of  "u32 rtk_bsd_state". */
#define BSD_INITIAL             BIT0
#define BSD_STBCASN             BIT1
#define BSD_STMSID              BIT2    // MarketSegmentId
#define BSD_INIT_SEC_HANDLE     BIT3
#define BSD_SHOW_RPC            BIT31

//reference Sirius_TP_Arch_Spec.doc
#define TP_KEY_INFO_1   0xb8014058
#define TP_KEY_INFO_0   0xb801405C
#define TP_KEY_CTRL     0xb8014060

#define TP_ENTRY_WRT    (0x01UL<<7)
#define TP_ENTRY_RED    (0)
#define FLASH_PROTECT_ENTRY_0           120
#define FLASH_PROTECT_ENTRY_1           (FLASH_PROTECT_ENTRY_0+1)
#define FLASH_PROTECT_ROOT_ENTRY        126
#define CP_CW_FLASH_PROTECT_KEY_ENTRY   (FLASH_PROTECT_ENTRY_0+1)

//for Nagxx initial
#define GROUP1_CK_EN    0xb8000014
#define NAGXX_CLK       (0xfUL<<7)

#define SOFT_RESET3     0xb8000008
#define NAGXX_RST       (0x1fUL<<27)


/****************************************************************************/
/*                                                                          */
/* ==================== external function ================================= */
/*                                                                          */
/****************************************************************************/
//vi ./uboot/arch/arm/lib/reset.c +50
extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
extern int SHA256_DigestInit(MCP_MD_CTX* ctx);
extern int SHA256_DigestUpdate(MCP_MD_CTX* ctx,MCP_BUFF* mcpb);
extern int SHA256_DigestFinal(MCP_MD_CTX* ctx,unsigned char* pHash);
extern int SHA256_DigestCleanup(MCP_MD_CTX* ctx);
extern int mcp_init(void);

extern unsigned int do_RSA_BSD(
                        unsigned char enc,
                        unsigned int key_len,
                        const unsigned int signature_addr,
                        const unsigned int rsa_key_addr,
                        const unsigned int rsa_exp_addr,
                        const unsigned int output_addr );


/****************************************************************************/
/*                                                                          */
/* ==================== Local function ================================= */
/*                                                                          */
/****************************************************************************/
void rtk_show_data(
    unsigned char   ch_line,
    unsigned int    d_len,
    void*           d_buf,
    unsigned int    type_ctl,
    unsigned char * message );

static
void rtk_rev_bytes(
    const unsigned char *   sor,
    unsigned char *         des,
    unsigned int            len);

TBsdStatus  bsdSet2LevelProtectedKey (
    TBsdCipherSession       xSession,
    TUnsignedInt16          xEmi,
    TSize                   xCipheredContentKeySize,
    const TUnsignedInt8*    pxCipheredContentKey,
    TSize                   xCipheredProtectingKeySize,
    const TUnsignedInt8*    pxL1CipheredProtectingKey,
    const TUnsignedInt8*    pxL2CipheredProtectingKey );

/****************************************************************************/
/*                                                                          */
/* ==================== LOCAL Veriable ==================== */
/*                                                                          */
/****************************************************************************/
u32 rtk_bsd_state = 0;
struct SBsdCipherSession gSessionHandle[SESSION_HANDLE_NUM];

static const char *const status_tlb[8] = {
  "BSD_NO_ERROR",
  "BSD_ERROR",
  "BSD_ERROR_DRIVER_ALREADY_INITIALIZED",
  "BSD_ERROR_INVALID_PARAMETERS",
  "BSD_ERROR_NOT_SUPPORTED",
  "BSD_ERROR_BAD_USAGE",
  "BSD_ERROR_NOT_IMPLEMENTED",
  "LAST_BSD_STATUS"
};

u32 fake_cert_flag = 0;

/****************************************************************************/
/*                                                                          */
/* ==================== Realtek function ====================                */
/*                                                                          */
/****************************************************************************/

static void rtk_nagxx_init(void)
{
/* rference to "Sirius_CRT_Arch_Spec.doc" */
    unsigned int reginfo;

    reginfo = rtd_inl(GROUP1_CK_EN);
    rtd_outl(GROUP1_CK_EN, reginfo & ~NAGXX_CLK);
    reginfo = rtd_inl(SOFT_RESET3);
    rtd_outl(SOFT_RESET3, reginfo & ~NAGXX_RST);

    udelay(100);

    reginfo = rtd_inl(SOFT_RESET3);
    rtd_outl(SOFT_RESET3, reginfo | NAGXX_RST);
    reginfo = rtd_inl(GROUP1_CK_EN);
    rtd_outl(GROUP1_CK_EN, reginfo | NAGXX_CLK);

    BD_INFO("0x%x=0x%x\n",GROUP1_CK_EN,rtd_inl(GROUP1_CK_EN));

}

/*-------------------------------------------------------------------
 * FUNC : rtk_show_data
 *
 * DESC : show data from specific pointer
 *
 * PARM :
 *      ch_line: how many words(bytes/4bytes) change line
 *      d_len  : total data will be print
 *      d_buf  : data pointer
 *      type_ctl : control flag.
 *                  TCLOSE => show data closely.
 *                  TYPE32 => show data in 32bit mode.
 *      message: message from caller.
 * RET  : SEC_NO_ERROR / SEC_ERROR_BAD_PARAMETER / SEC_ERROR_BAD_EMI/ SEC_ERROR_BAD_USAGE / SEC_ERROR
 *-------------------------------------------------------------------*/
void rtk_show_data(
    unsigned char   ch_line,
    unsigned int    d_len,
    void *          d_buf,
    unsigned int    type_ctl,
    unsigned char * message )
{
    unsigned int i;
    unsigned int* ptr32;
    unsigned char* ptr8;
    unsigned int loop = d_len;

    if(d_buf){
        if(type_ctl & TYPE32){
            loop = loop/4;
            ptr32 = (unsigned int*)d_buf;
        }else{
            ptr8 = (unsigned char*)d_buf;
        }
        BDPRINT("\n"
                "=== %s ===\n",message);

        for(i=0;i<loop; i++){
            if(i == 0 ||
               (ch_line && (i%ch_line) == 0))
            {
                BDPRINT("\n");
            }
            if(type_ctl & TYPE32){
                BDPRINT("%08x",ptr32[i]);
            }else{
                BDPRINT("%02x",ptr8[i]);
            }
            if((type_ctl & TCLOSE) == 0)
                BDPRINT(" ");
        }
    }else{
        BDPRINT("\n"
                "=== %s ===(0x%p)\n",message,d_buf);
    }
    BDPRINT("\n\n");


}


void rtk_rev_bytes(
    const unsigned char *   sor,
    unsigned char *         des,
    unsigned int            len )
{
    unsigned int i;
    for(i=0;i<len;i++){
        des[len-1-i] = sor[i];
    }
    return;
}


int rtk_rev_bytes_local(
    unsigned char * sor,
    unsigned int    len )
{
    int ret = 0;
    unsigned int i;
    unsigned char* des = NULL;

    des = malloc(len);
    if(des){
        for(i=0;i<len;i++){
            des[len-1-i] = sor[i];
        }
        memcpy((void*)sor,(void*)des,len);
    }else{
        ret = -1;
    }
    return ret;
}


/* initialize and allocate necessary resource for BSD */
static
u32 rtk_init_resource_BSD(void)
{
    BDPRINT("%s: It's nothing to do now!!!\n",__func__);

    /* request memory */
    /* initial hardware */

    return 0;
}

/* free resource for BSD */
int rtk_free_resource_BSD(void)
{
    /* release memory */
    /* release hardware */

    return 0;
}

static
int rtk_findSessionHandle(struct SBsdCipherSession* pSec)
{
    int i;

    for (i=0; i<SESSION_HANDLE_NUM; i++)
    {
        if (&gSessionHandle[i]==pSec)
            return i;
    }

    return -1;
}


static
int rtk_chkSessionHandle(TBsdCipherSession xSession)
{
    if (rtk_findSessionHandle(xSession) < 0)
    {
        BDPRINT("_chkSessionHandle failed, invalid seesion parameter\n");
        return -1;
    }

    if (xSession->KeyTableIndex >= MAX_KEY_TABLE_ENTRY)
    {
        BDPRINT("_chkSessionHandle failed, invalid key table index - %d\n", xSession->KeyTableIndex);
        return -1;
    }

    return 0;
}


static
void rtk_init_SessionHandle(int session_handle_num)
{
    int i;

    BD_INFO("gSessionHandle=0x%p;session_handle_num=%d\n",
             gSessionHandle,session_handle_num);
    if ((rtk_bsd_state & BSD_INIT_SEC_HANDLE) == 0)
    {
        rtk_bsd_state |= BSD_INIT_SEC_HANDLE;
        BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);

        for (i=0; i<session_handle_num; i++){
            //BD_INFO("loop%d\n",i);
            gSessionHandle[i].KeyTableIndex = BSD_KEY_TBL_FREE;
            gSessionHandle[i].en_de         = 0;
            gSessionHandle[i].Emi           = 0;
            gSessionHandle[i].last_key      = BSD_UNSET_KEY;
        }
    }
}


struct
SBsdCipherSession* rtk_allocSessionHandle(TUnsignedInt8   en_de)
{
    int i;
    struct SBsdCipherSession* rtn_ptr = NULL;

    // find free section handle
    for (i=0; i<SESSION_HANDLE_NUM; i++)
    {
        //BD_INFO("gSessionHandle=0x%p;session_handle_num=%d\n",
        //   gSessionHandle,i);
        //BD_INFO("KeyTableIndex=0x%x\n",gSessionHandle[i].KeyTableIndex);

        if (gSessionHandle[i].KeyTableIndex == BSD_KEY_TBL_FREE)
        {
            BD_INFO("loop%d set parameter\n",i);
            gSessionHandle[i].en_de         = en_de;
            gSessionHandle[i].KeyTableIndex = i;

            rtn_ptr =  &gSessionHandle[i];
            BD_INFO("gSessionHandle at 0x%p\n",rtn_ptr);
            break;
        }
    }

    BD_INFO("rtn_ptr is 0x%p\n",rtn_ptr);
    return rtn_ptr;
}


/****************************************************************************/
/*                                                                          */
/* ==================== Driver Settings ====================                */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdInitialize (struct SBsdInitParameters *pxInitParameters)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    if(pxInitParameters){
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if( rtk_bsd_state & BSD_INITIAL){
        BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);
        bsdStatus = BSD_ERROR_DRIVER_ALREADY_INITIALIZED;
        goto TRY_INIT;
    }else{
TRY_INIT:
        while(1){
            /* Reset the chipset */
            bsdStatus = BSD_ERROR;
            if(rtk_init_resource_BSD())
                break;

            /* success */
            bsdStatus = BSD_NO_ERROR;
            rtk_bsd_state |= BSD_INITIAL;
            pxInitParameters = (struct SBsdInitParameters *)&rtk_bsd_state;
            BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);
            break;
        }
    }

    BD_INFO("\n");
    return bsdStatus;
}


TBsdStatus bsdGetApiVersion( TUnsignedInt32 *pxBsdApiVersion )
{
    TBsdStatus bsdStatus = BSD_ERROR;

    BDPRINT_FUNC();
    while(1){
        if(!pxBsdApiVersion){
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        *pxBsdApiVersion = BSDAPI_VERSION_INT;

        bsdStatus = BSD_NO_ERROR;
        break;
    }

    return bsdStatus;
}


TBsdStatus bsdGetSoftwareVersion  ( TBsd20CharsString  xSoftwareVersion )
{
    TBsdStatus bsdStatus = BSD_ERROR;
    const char tmp20Char[20] = RTK_BSD_SOFTWARE_VERSION;

    BDPRINT_FUNC();

    while(1){
        if(!xSoftwareVersion){
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        strcpy((char*)xSoftwareVersion, tmp20Char);
        bsdStatus = BSD_NO_ERROR;
        break;
    }

    return bsdStatus;
}


TBsdStatus bsdTerminate(TBsdTerminateParameters *pxTerminateParameters)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    if(pxTerminateParameters)
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else if( (rtk_bsd_state & BSD_INITIAL) == 0 )
        bsdStatus = BSD_ERROR;
    else{
        while(1){
            /* free resource the chipset */
            bsdStatus = BSD_ERROR;
            if(rtk_free_resource_BSD())
                break;

            /* success */
            bsdStatus = BSD_NO_ERROR;
            rtk_bsd_state &= ~BSD_INITIAL;
            BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);
            break;
        }
    }

    return bsdStatus;
}


/****************************************************************************/
/*                                                                          */
/* ==================== Chipset Information ====================            */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdGetNuid (TBsd4BytesVector xNuid)
{
    unsigned int reginfo;
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    if(!xNuid){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if( (rtk_bsd_state & BSD_INITIAL) == 0 ){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR;
    }else{
        BD_INFO("\n");
        reginfo = rtd_inl(DP_NA_MRK_NUID64_H);
        BD_INFO("DP_NA_MRK_NUID64_H(%x)=0x%x\n",(u32)DP_NA_MRK_NUID64_H,reginfo);
        *(u32*)xNuid = rtd_inl(DP_NA_MRK_NUID64_H);
    }

    BD_INFO("\n");
    return bsdStatus;

}


TBsdStatus  bsdGetNuid64 (TBsd8BytesVector xNuid64)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();
    unsigned int reginfo1;
    unsigned int reginfo2;



    if(!xNuid64){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if( (rtk_bsd_state & BSD_INITIAL) == 0 ){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR;
    }else{
        BD_INFO("\n");
        reginfo1 = rtd_inl(DP_NA_MRK_NUID64_L);
        reginfo2 = rtd_inl(DP_NA_MRK_NUID64_H);
        rtk_rev_bytes_local((unsigned char *)&reginfo1,4);
        rtk_rev_bytes_local((unsigned char *)&reginfo2,4);
        BD_INFO("DP_NA_MRK_NUID64 = 0x%08x%08x\n",reginfo2,reginfo1);
        *(u64*)xNuid64 = ((u64)reginfo2) <<32 |
                         (u64)reginfo1;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdSetStbCaSn (const TBsd4BytesVector xStbCaSn)
{
    static u32 bpStbCaSnRef32    = 0;
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    if(!xStbCaSn)
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else if( (rtk_bsd_state & BSD_INITIAL) == 0 )
        bsdStatus = BSD_ERROR;
    else if(rtk_bsd_state & BSD_STBCASN){
        if(otp_read_ex(OTP_StbCaSnRef32,&bpStbCaSnRef32))
            bsdStatus = BSD_ERROR;
        else{
            if(bpStbCaSnRef32 != *(u32*)xStbCaSn)
                bsdStatus = BSD_ERROR;
        }
    }else{
        if(otp_write_ex(OTP_StbCaSnRef32,*((u32*)xStbCaSn)))
            bsdStatus = BSD_ERROR;
        else{
            if(otp_write_ex(OTP_StbCaSnRef32Lock,1))
            {
                bsdStatus = BSD_ERROR;
            }else{
                rtk_bsd_state |= BSD_STBCASN;
                BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);
            }
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdGetStbCaSn (TBsd4BytesVector xStbCaSn)
{
    TBsdStatus bsdStatus = BSD_ERROR;

    BDPRINT_FUNC();
    BD_INFO("rtk_bsd_state=0x%x; xStbCaSn=0x%p\n",
                rtk_bsd_state,xStbCaSn);

    if(!xStbCaSn){
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if(rtk_bsd_state & BSD_INITIAL){
        BD_INFO("ofst=%d msb=%d lsb=%d\n",
            OTP_StbCaSnRef32.ofst,OTP_StbCaSnRef32.msb,OTP_StbCaSnRef32.lsb);
        if(otp_read_ex(OTP_StbCaSnRef32,(u32*)xStbCaSn) == 0){
            BD_INFO("\n");
            bsdStatus = BSD_NO_ERROR;
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdSetMarketSegmentId (const TBsd4BytesVector xMarketSegmentId)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    static u32 bpMarketSegmentID = 0;

    BDPRINT_FUNC();

    if(!xMarketSegmentId){
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if( (rtk_bsd_state & BSD_INITIAL) == 0 ){
        bsdStatus = BSD_ERROR;
    }else if (rtk_bsd_state & BSD_STMSID){   //MarketSegmentID has been write
        if(otp_read_ex(OTP_MsidRef,&bpMarketSegmentID))
        {
            bsdStatus = BSD_ERROR;
        }else{
             if(bpMarketSegmentID != *(u32*)xMarketSegmentId)
                bsdStatus = BSD_ERROR;
        }
    }else{
        if(otp_write_ex(OTP_MsidRef,*(u32*)xMarketSegmentId))
        {
            //write fail
            bsdStatus = BSD_ERROR;
        }else{
            if(otp_write_ex(OTP_MsidRefLock,1)){
                // lock fail
                bsdStatus = BSD_ERROR;
            }else
                rtk_bsd_state |= BSD_STMSID;
                BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdGetMarketSegmentId (TBsd4BytesVector xMarketSegmentId)
{
    TBsdStatus bsdStatus = BSD_ERROR;

    BDPRINT_FUNC();
    BD_INFO("rtk_bsd_state=0x%x; xMarketSegmentId=0x%p\n",
                rtk_bsd_state,xMarketSegmentId);

    if(!(rtk_bsd_state & BSD_STMSID) && xMarketSegmentId){
        BD_INFO("for test force get!!!\n");
        goto FORCE_GET;
    }

    if(!xMarketSegmentId){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if(rtk_bsd_state & BSD_STMSID){
FORCE_GET:
        BD_INFO("\n");
        if(otp_read_ex(OTP_MsidRef,(u32*)xMarketSegmentId) == 0){
            BD_INFO("\n");
            bsdStatus = BSD_NO_ERROR;
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;

}


TBsdStatus  bsdGetNUIDCheckNumber (TBsd4BytesVector xNUIDCheckNumber)
{
    TBsdStatus bsdStatus = BSD_ERROR;
    u32 reginfo;

    BDPRINT_FUNC();

    if(!xNUIDCheckNumber){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else if(rtk_bsd_state & BSD_INITIAL)
    {
        BD_INFO("DP_NA_MRK_MRK1=0x%x\n",(u32)DP_NA_MRK_MRK1);
        reginfo =  htonl(rtd_inl(DP_NA_MRK_MRK1));
        *((u32*)xNUIDCheckNumber) = reginfo;

        BD_INFO("xNUIDCheckNumber=0x%08x\n",*((u32*)xNUIDCheckNumber));
        bsdStatus = BSD_NO_ERROR;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;

}

extern const unsigned int bsdram2ram_emi_4041_CipheredContentKey_size;
extern const unsigned int bsdram2ram_emi_4041_CipheredContentKey_number;
extern const unsigned int bsdram2ram_emi_4041_CipheredProtectingKeyL1_size;
extern const unsigned int bsdram2ram_emi_4041_CipheredProtectingKeyL1_number;
extern const unsigned char bsdram2ram_emi_4041_CipheredProtectingKeyL1[128][16];
extern const unsigned char bsdram2ram_emi_4041_CipheredProtectingKeyL2[128][16];
extern const unsigned char bsdram2ram_emi_4041_CipheredContentKey[128][16];
#define INT_CHK_NU_CAL_SIZE 16

TBsdStatus  bsdGetDataIntegrityCheckNumber(
    const TUnsignedInt8 *   pxData,
    TUnsignedInt32          xDataSize,
    TBsd4BytesVector        xDataIntegrityCheckNumber )
{

    TBsdCipherSession r2rSession;
    TBsdStatus bsdStatus = BSD_ERROR;
    u8 i;
    u32 bsd_crc;

    BDPRINT_FUNC();

    if((!xDataIntegrityCheckNumber) && xDataSize && xDataSize<=16 )
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else{
        TUnsignedInt16      xEmi;
        unsigned long int   intNuid;
        TSize               xCipheredContentKeySize;
        TUnsignedInt8 *     pxCipheredContentKey;    //Provided by Nagra
        TSize               xCipheredProtectingKeySize;
        TUnsignedInt8 *     pxL1CipheredProtectingKey;   //Provided by Nagra
        TUnsignedInt8 *     pxL2CipheredProtectingKey;   //Provided by Nagra
        TUnsignedInt8 *     pxInput  = NULL;
        TUnsignedInt8 *     pxOutput = NULL;

        //pxInput = (TUnsignedInt8*)malloc(INT_CHK_NU_CAL_SIZE);
        //memset(pxInput, 0, INT_CHK_NU_CAL_SIZE);

        /* pad leading zero */
        //for(i=0;i<xDataSize;i++)
        //    pxInput[i] = pxData[i];

        if((bsdOpenRam2RamDecryptSession (&r2rSession)) != BSD_NO_ERROR )
            goto ERR_OUT;

        xEmi = 0x4041;
        intNuid = 0;
        xCipheredContentKeySize    = bsdram2ram_emi_4041_CipheredContentKey_size;
        xCipheredProtectingKeySize = bsdram2ram_emi_4041_CipheredProtectingKeyL1_size;
        pxL2CipheredProtectingKey  = (TUnsignedInt8*)&bsdram2ram_emi_4041_CipheredProtectingKeyL2[intNuid][0];
        pxL1CipheredProtectingKey  = (TUnsignedInt8*)&bsdram2ram_emi_4041_CipheredProtectingKeyL1[intNuid][0];
        pxCipheredContentKey       = (TUnsignedInt8*)&bsdram2ram_emi_4041_CipheredContentKey[intNuid][0];

        bsdStatus = bsdSet2LevelProtectedKey(r2rSession, xEmi,
                                             xCipheredContentKeySize,
                                             pxCipheredContentKey,
                                             xCipheredProtectingKeySize,
                                             pxL1CipheredProtectingKey,
                                             pxL2CipheredProtectingKey);

        if(bsdStatus != BSD_NO_ERROR)
            goto ERR_OUT;

        pxInput = (TUnsignedInt8*)malloc(INT_CHK_NU_CAL_SIZE);

        if(pxInput == NULL )
            goto ERR_OUT;

        memset(pxInput, 0, INT_CHK_NU_CAL_SIZE);

        for(i=0;i<xDataSize;i++)
            pxInput[i] = pxData[i];

        bsdStatus = bsdSessionEncrypt (r2rSession,
                                       pxInput, pxOutput, INT_CHK_NU_CAL_SIZE,
                                       NULL, 0);

        free(pxInput);

        if(bsdStatus != BSD_NO_ERROR)
            goto ERR_OUT;

        bsdCloseSession(r2rSession);

        bsd_crc = crc32(0,pxOutput,16);

        *(u32*)xDataIntegrityCheckNumber = bsd_crc;

    }

ERR_OUT:
    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdChipsetInformation (TBsdInfoChipset *pxInfoChipset)
{
    TBsdStatus bsdStatus = BSD_ERROR;
    u32 Info_tmp;
    //unsigned char tmp20Char[20];
    BDPRINT_FUNC();
    //BSD_TOOL_STRINGIFY()
    if(!pxInfoChipset)
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else{

        strcpy((char*)pxInfoChipset->BSD_CM, "RTK");
        BD_INFO("BSD_CT = %s\n",pxInfoChipset->BSD_CM);

        Info_tmp = rtd_inl(DP_NA_MRK_CHIP_ID);
        Info_tmp &= (0xFFFFFFUL);
        strcpy((char*)pxInfoChipset->BSD_CT, "SIRIUS");
        BD_INFO("BSD_CT = %s(%x)\n",pxInfoChipset->BSD_CT,Info_tmp);

        Info_tmp = rtd_inl(DP_NA_MRK_CHIP_REV);
        Info_tmp &= (0xFFUL);

        if(Info_tmp == 0x00)
            strcpy((char*)pxInfoChipset->BSD_CUT, "A0");
        else
            strcpy((char*)pxInfoChipset->BSD_CUT, BSD_TOOL_STRINGIFY(Info_tmp));
//            tmp20Char = BSD_TOOL_STRINGIFY(Info_tmp);
        BD_INFO("BSD_CUT = %s(%x)\n",pxInfoChipset->BSD_CUT,Info_tmp);

        Info_tmp = rtd_inl(DP_NA_MRK_CHIP_ID);
        Info_tmp = ((Info_tmp & 0xFF000000 ) >> 24);
        strcpy((char*)pxInfoChipset->BSD_EXT, "00");
        BD_INFO("BSD_EXT = %s(%x)\n",pxInfoChipset->BSD_EXT,Info_tmp);

        bsdStatus = BSD_NO_ERROR;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== Debug Print   ====================                  */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdPrint (const TChar *pxString)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    if(!pxString)
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else{
        BDPRINT("%s",pxString);
    }

    BD_INFO("\n");
    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== Chipset Reset ====================                  */
/*                                                                          */
/****************************************************************************/

void  bsdChipReset (void)
{
    BDPRINT_FUNC();
    flush_dcache_all();
    invalidate_dcache_all();

    /* reset SYSTEM */
    rtd_outl(0xb8060500,0xbeaa2379);
    do_reset (NULL, 0, 0, NULL);

/*
TO check  0xb8060500 after reset back;
./uboot/common/main.c +273
*/
}

/****************************************************************************/
/*                                                                          */
/* ==================== Flash Protection ====================               */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdEncryptFlashProtKey(
    const TUnsignedInt8 * pxInput,
    TUnsignedInt8 *       pxOutput,
    size_t                xSize )
{
    int i;
    //int ret = 0;
    u32             reginfo     = 0;
    TBsdStatus      bsdStatus   = BSD_ERROR;
    unsigned char*  Input_buf   = NULL;;

    BDPRINT_FUNC();

    BDPRINT("pxInput=0x%p; pxOutput=0x%p; xSize=%d\n",
             pxInput,pxOutput,xSize);

    rtk_show_data(xSize,xSize,
                  (void *)pxInput,TCLOSE,
                  (unsigned char*)"show pxInput");

    if((!pxInput) || (!pxOutput) || (xSize != 16)){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if(rtd_inl(CW_AGENT)& KEY_IN_CW){


#define SHOW_FLASH_PROTECT_ROOT_KEY
//#define FAKE_FLASH_PROTECT_ROOT_KEY

#ifdef SHOW_FLASH_PROTECT_ROOT_KEY
/* show flash key here *** */
        if(1){
        unsigned reginfo1;
        unsigned reginfo0;

#ifdef FAKE_FLASH_PROTECT_ROOT_KEY
        rtd_outl(TP_KEY_INFO_1,0x01020506);
        rtd_outl(TP_KEY_INFO_0,0x03040708);

        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ROOT_ENTRY |TP_ENTRY_WRT );

        rtd_outl(TP_KEY_INFO_1,0x01020304);
        rtd_outl(TP_KEY_INFO_0,0x05060708);
#endif
        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ROOT_ENTRY |TP_ENTRY_RED );
        reginfo1 = rtd_inl(TP_KEY_INFO_1);
        reginfo0 = rtd_inl(TP_KEY_INFO_0);

        BD_INFO("FLASH_PROTECT_ROOT KEY(%d): %08x%08x\n",
                FLASH_PROTECT_ROOT_ENTRY,reginfo1,reginfo0);

#ifdef FAKE_FLASH_PROTECT_ROOT_KEY
        rtd_outl(TP_KEY_INFO_1,0x0a0b1234);
        rtd_outl(TP_KEY_INFO_0,0x0c0d5678);

        rtd_outl(TP_KEY_CTRL,(FLASH_PROTECT_ROOT_ENTRY+1) |TP_ENTRY_WRT );

        rtd_outl(TP_KEY_INFO_1,0xdddd5678);
        rtd_outl(TP_KEY_INFO_0,0x3344ccdd);
#endif
        rtd_outl(TP_KEY_CTRL,(FLASH_PROTECT_ROOT_ENTRY+1) |TP_ENTRY_RED );
        reginfo1 = rtd_inl(TP_KEY_INFO_1);
        reginfo0 = rtd_inl(TP_KEY_INFO_0);

        BD_INFO("FLASH_PROTECT_ROOT KEY(%d): %08x%08x\n",
                (FLASH_PROTECT_ROOT_ENTRY+1),reginfo1,reginfo0);
        }
#endif

        BD_INFO("RCP Mode !!!\n");

        Input_buf = malloc(16);

        if(Input_buf == NULL){
            BD_INFO("request fail !!!\n");
            bsdStatus = BSD_ERROR;
            goto ERR_OUT;
        }else{
            memcpy((void*)Input_buf,(void*)pxInput,16);
            rtk_show_data(xSize,xSize,
                  (void *)Input_buf,TCLOSE,
                  (unsigned char*)"show Input_buf");
        }

        reginfo  = rtd_inl(K_CP_REG_SET);
        reginfo &= ~(CP_MODE_MASK );
        reginfo |= (CP_AES_DCAS|WRT_EN3)|(CBC_ECB|WRT_EN2)|
                   (REG_1ST|WRT_EN1)|(REG_ENDE|WRT_EN0);
        BD_INFO("K_CP_REG_SET=0x%08x\n",reginfo);
        rtd_outl(K_CP_REG_SET,reginfo);

        reginfo  = rtd_inl(K_CP_REG_SET1);
        reginfo &= ~(CP_KEY_MODE_MASK | INPUT_MODE_MASK |OUTPUT_MODE_MASK);
        reginfo |= (KEY_MODE_CW|INPUT_MODE_REG|OUTPUT_MODE_REG);
        BD_INFO("K_CP_REG_SET1=0x%08x\n",reginfo);
        rtd_outl(K_CP_REG_SET1,reginfo);

        reginfo  = rtd_inl(K_CP_REG_SET2);
        reginfo &= ~(KEY_ENTRY_MASK);
        reginfo |= (FLASH_PROTECT_ROOT_ENTRY<<KEY_ENTRY_SHT);
        BD_INFO("K_CP_REG_SET2=0x%08x\n",reginfo);
        rtd_outl(K_CP_REG_SET2,reginfo);

        for(i=0 ;i<4;i++)
            rtk_rev_bytes_local(Input_buf+(i<<2) ,4);

        for(i=0 ;i<4;i++){
            rtd_outl(K_CP_REG_DATAIN+((i<<2)),*((unsigned int *)(Input_buf+ (i<<2))));
        }

        udelay(500);
        BD_INFO("\n");

        for(i=0 ;i<4;i++){
            *((unsigned int *)(pxOutput+(i<<2))) = rtd_inl(K_CP_REG_DATAOUT+(i<<2));
        }

        for(i=0 ;i<4;i++){
            rtk_rev_bytes_local(pxOutput+(i<<2) ,4);
        }

        rtk_show_data(xSize,xSize,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"show pxOutput");

        bsdStatus = BSD_NO_ERROR;

        free(Input_buf);

    }

ERR_OUT:

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== Buffers Management ====================             */
/*                                                                          */
/****************************************************************************/
TUnsignedInt8 *  bsdAllocateBuffer (size_t xBufferSize)
{
    TUnsignedInt8 * bsdbuf;
    BDPRINT_FUNC();

    bsdbuf = (TUnsignedInt8 *)malloc(xBufferSize);
    //bsdbuf = (TUnsignedInt8 *)malloc_noncache_align(xBufferSize, 4);

    //BD_INFO("xBufferSize=%d; bsdbuf=0x%p\n",xBufferSize,bsdbuf);
    //BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdbuf;
}


TBsdStatus  bsdFreeBuffer (TUnsignedInt8 *pxBuffer)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;;

    BDPRINT_FUNC();
    //BDPRINT("pxBuffer=0x%p\n",pxBuffer);

    if(pxBuffer){
        free(pxBuffer);
    }

    //BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== Block Ciphers (RAM2RAM) ====================        */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdOpenRam2RamEncryptSession (TBsdCipherSession *pxSession)
{
    TBsdStatus bsdStatus = BSD_ERROR;

    BDPRINT_FUNC();
    /*
    Note :
        *pxSession == (struct SBsdCipherSession*)
        *pxSession是一個指向 struct SBsdCipherSession 的指標
    */
    if( pxSession == NULL){
        BD_INFO("\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        BD_INFO("\n");
        rtk_init_SessionHandle(SESSION_HANDLE_NUM);

//#define CONFIG_FAKE_DECRYPTION
#ifndef CONFIG_FAKE_DECRYPTION
        *pxSession = rtk_allocSessionHandle(BSD_ENCRYPTION);
#else
        *pxSession = rtk_allocSessionHandle(BSD_DECRYPTION);
#endif

        if(*pxSession){
            BD_INFO("*pxSession = 0x%p\n",*pxSession);
            bsdStatus = BSD_NO_ERROR;
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdOpenRam2RamDecryptSession (TBsdCipherSession *pxSession)
{
    TBsdStatus bsdStatus = BSD_ERROR;

    BDPRINT_FUNC();
        if(!pxSession)
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    else{
        rtk_init_SessionHandle(SESSION_HANDLE_NUM);
        *pxSession = rtk_allocSessionHandle(BSD_DECRYPTION);
        if(*pxSession)
            bsdStatus = BSD_NO_ERROR;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdCloseSession (TBsdCipherSession xSession)
{
    int res = 0;
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    res = rtk_findSessionHandle(xSession);
    if (res < 0)
    {
        BDPRINT("_chkSessionHandle failed, invalid seesion parameter\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        gSessionHandle[res].KeyTableIndex = BSD_KEY_TBL_FREE;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdSetClearTextKey(
    TBsdCipherSession       xSession,
    TUnsignedInt16          xEmi,
    TSize                   xClearTextKeySize,
    const TUnsignedInt8*    pxClearTextKey )
{
    unsigned int wait_loop = 0;
    unsigned int Usage = 0;
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    if (xClearTextKeySize != 16){
        BDPRINT("bsdSetClearTextKey failed, invalid key size %04x\n", xClearTextKeySize);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if (pxClearTextKey == NULL){
        BDPRINT("bsdSetClearTextKey failed, Clear Text Key should not be NULL\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if (rtk_chkSessionHandle(xSession) < 0){
        BDPRINT("bsdSetClearTextKey failed, invalid seesion parameter\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        BD_INFO("xSession = 0x%p\n",xSession);

        Usage = (xSession->en_de==BSD_ENCRYPTION) ?
              KT_HOSTKEY_USAGE_ENCRYPT_EN : KT_HOSTKEY_USAGE_DECRYPT_EN;

        //Usage = KT_HOSTKEY_USAGE_DECRYPT_EN;

        BD_INFO("xEmi=0x%x\n",xEmi);
        switch(xEmi)
        {
        //0x4021
        case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KT_HOSTKEY_USAGE_ALGO_AES;
            Usage |= KT_HOSTKEY_USAGE_KEY_LEN_128;
        break;

        //0x4026
        case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KT_HOSTKEY_USAGE_ALGO_AES;
            Usage |= KT_HOSTKEY_USAGE_KEY_LEN_128;
            break;

        //0x4041
        case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KT_HOSTKEY_USAGE_ALGO_TDES;
            Usage |= KT_HOSTKEY_USAGE_KEY_LEN_128;
            break;

        //0x4043
        case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KT_HOSTKEY_USAGE_ALGO_TDES;
            Usage |= KT_HOSTKEY_USAGE_KEY_LEN_128;
            break;

        default:
            BD_INFO("\n");
            BDPRINT("bsdSetClearTextKey failed, invalid EMI %04x\n", xEmi);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }
        if(bsdStatus == BSD_NO_ERROR){
            BD_INFO("\n");
            xSession->Emi       = xEmi;   // store Emi
            xSession->last_key  = BSD_USE_CLEAR_TEXT_KEY;
            BD_INFO("xEmi=0x%x, last_key=%d; KeyTableIndex=%d\n",
                    xSession->Emi,xSession->last_key,xSession->KeyTableIndex);

            rtk_show_data(xClearTextKeySize,xClearTextKeySize,
                  (void *)pxClearTextKey,TCLOSE,
                  (unsigned char*)"show pxClearTextKey");

            rtd_outl(KT_WADR_REG, xSession->KeyTableIndex);       // write key table address

            BD_INFO("\n");
            rtd_outl(KT_HOSTKEY1_REG, (pxClearTextKey[12]<<24) | (pxClearTextKey[13]<<16) | (pxClearTextKey[14]<<8) | pxClearTextKey[15]);   // [31:0]
            rtd_outl(KT_HOSTKEY2_REG, (pxClearTextKey[ 8]<<24) | (pxClearTextKey[ 9]<<16) | (pxClearTextKey[10]<<8) | pxClearTextKey[11]);   // [63:32]
            rtd_outl(KT_HOSTKEY3_REG, (pxClearTextKey[ 4]<<24) | (pxClearTextKey[ 5]<<16) | (pxClearTextKey[ 6]<<8) | pxClearTextKey[ 7]);   // [95:64]
            rtd_outl(KT_HOSTKEY4_REG, (pxClearTextKey[ 0]<<24) | (pxClearTextKey[ 1]<<16) | (pxClearTextKey[ 2]<<8) | pxClearTextKey[ 3]);   // [127:96]

            BDPRINT("Key REG = %08x %08x %08x %08x\n",
                rtd_inl(KT_HOSTKEY4_REG),
                rtd_inl(KT_HOSTKEY3_REG),
                rtd_inl(KT_HOSTKEY2_REG),
                rtd_inl(KT_HOSTKEY1_REG));

            rtd_outl(KT_HOSTKEY_IV1_REG, 0);   // [31:0]
            rtd_outl(KT_HOSTKEY_IV2_REG, 0);   // [63:32]
            rtd_outl(KT_HOSTKEY_IV3_REG, 0);   // [95:64]
            rtd_outl(KT_HOSTKEY_IV4_REG, 0);   // [127:96]

            BDPRINT("IV  REG = %08x %08x %08x %08x\n",
                    rtd_inl(KT_HOSTKEY_IV4_REG),
                    rtd_inl(KT_HOSTKEY_IV3_REG),
                    rtd_inl(KT_HOSTKEY_IV2_REG),
                    rtd_inl(KT_HOSTKEY_IV1_REG));

            rtd_outl(KT_HOSTKEY_USAGE_REG, Usage);   // write usage
            rtd_outl(KT_HOSTKEY_USAGE_REG, Usage | KT_HOSTKEY_USAGE_HOSTKEY_VALID);

            // wait complete
            BD_INFO("wait complete...\n");
            wait_loop = 2000;
            while(wait_loop &&
                  (rtd_inl(KT_HOSTKEY_USAGE_REG) & KT_HOSTKEY_USAGE_HOSTKEY_VALID))
            {
                udelay(1000);
                wait_loop--;
            }

            BD_INFO("\n");
            if(wait_loop ==0){
                bsdStatus = BSD_ERROR;
                BDPRINT("BSD wait KT_HOSTKEY_USAGE_HOSTKEY_VALID fail.\n");
            }
        }
    }

    BD_INFO("\n");
    return bsdStatus;
}

/*
Chip ID:                      00 00 00 00 00 00 00 16
Nagra Data:                   CE F8 94 0E 0E 45 76 54 AD F7 3E 94 0B DC A7 79
MasterRootKey1_storage(OTP) : D0 FE 28 B7 FD 8C 45 DA 7A 8D D3 DA C9 4C 4A 75
MasterRootKey_CHECKSUM      : 59 B8 24 9D
Debug_PASSWORD:               C4 FC CF 5D 31 2E 8F 77 D6 DE 88 47 E6 6E B3 FF
Flash_Rootkey:                0E D5 35 89 2E 8D 6B C5 C8 E6 38 94 A4 0C D8 6B
AES_Rootkey:                  EE 6A 1F EB 89 E4 C2 85 32 FE 75 2C E9 4A 2E 7C
TDES_Rootkey:                 F9 B8 B7 26 89 D7 EB E5 2A 7F A2 77 CE C8 50 F1
CSA2_Rootkey:                 D1 E4 2D 52 8A DB 99 1F FC 68 CF F8 D6 D7 A2 05
CSA3_Rootkey:                 A3 34 C5 38 55 0E 8F E8 AC C5 76 90 23 D5 25 87

*/

static
unsigned int B42L(unsigned char B4[4])
{
    unsigned long val;
    val  =  B4[ 3]<<24;
    val +=  B4[ 2]<<16;
    val +=  B4[ 1]<<8;
    val +=  B4[ 0];
    return val;
}


static
unsigned int B42L_LE(unsigned char B4[4])
{
    unsigned long val;
    val  =  B4[ 0]<<24;
    val +=  B4[ 1]<<16;
    val +=  B4[ 2]<<8;
    val +=  B4[ 3];
    return val;
}

TBsdStatus  bsdSet2LevelProtectedKey (
    TBsdCipherSession       xSession,
    TUnsignedInt16          xEmi,
    TSize                   xCipheredContentKeySize,
    const TUnsignedInt8*    pxCipheredContentKey,
    TSize                   xCipheredProtectingKeySize,
    const TUnsignedInt8*    pxL1CipheredProtectingKey,
    const TUnsignedInt8*    pxL2CipheredProtectingKey )
{
    unsigned int Usage = 0;

    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    BD_INFO("xEmi=0x%x, xCipheredContentKeySize=%d; xCipheredProtectingKeySize=%d\n",
                    xEmi,xCipheredContentKeySize,xCipheredProtectingKeySize);


    rtk_show_data(xCipheredProtectingKeySize,xCipheredProtectingKeySize,
                  (void *)pxL2CipheredProtectingKey,TCLOSE,
                  (unsigned char*)"show pxL2CipheredProtectingKey");

    rtk_show_data(xCipheredProtectingKeySize,xCipheredProtectingKeySize,
                  (void *)pxL1CipheredProtectingKey,TCLOSE,
                  (unsigned char*)"show pxL1CipheredProtectingKey");

    rtk_show_data(xCipheredContentKeySize,xCipheredContentKeySize,
                  (void *)pxCipheredContentKey,TCLOSE,
                  (unsigned char*)"show pxCipheredContentKey");

    if (xCipheredContentKeySize!=16)
    {
        BDPRINT("bsdSet2LevelProtectedKey failed, invalid ciphered content key size %04x\n", xCipheredContentKeySize);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if (pxCipheredContentKey==NULL)
    {
        BDPRINT("bsdSet2LevelProtectedKey failed, invalid ciphered content Key should not be NULL\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else if (rtk_chkSessionHandle(xSession) < 0)
    {
        BDPRINT("bsdSet2LevelProtectedKey failed, invalid seesion parameter\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        BD_INFO("xEmi = 0x%x\n",xEmi);

        Usage = (xSession->en_de==BSD_ENCRYPTION) ?
                KL_CTRL1_ALLOW_ENCRYPT : KL_CTRL1_ALLOW_DECRYPT;

        switch(xEmi)
        {
        //0x4021
        case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
        //0x4026
        case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KL_CTRL1_KDF_K1_KEY_GEN_SEL_AES;
            break;

        //0x4041
        case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
        //0x4043
        case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            BD_INFO("\n");
            Usage |= KL_CTRL1_KDF_K1_KEY_GEN_SEL_TDES;
            break;

        default:
            BDPRINT("bsdSet2LevelProtectedKey failed, invalid EMI %04x\n", xEmi);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        if(bsdStatus == BSD_NO_ERROR){
            unsigned int try_loop;
            BD_INFO("\n");

            rtd_outl(KT_HOSTKEY_USAGE_REG, 0);
            rtd_outl(KT_WADR_REG, xSession->KeyTableIndex);       // write key table address

            // pool state machine to generate key
            try_loop = 1000;    //wait 10ms
            while((KL_STATUS_SCE_SM_STATUS(rtd_inl(KL_STATUS_1))!=16 )
                  && try_loop-- )
            {
                udelay(10);
            }

            if (KL_STATUS_SCE_SM_STATUS(rtd_inl(KL_STATUS_1))!=16)
            {
                BDPRINT("%s failed, wait key ladder ready timeout!!\n",__func__);
                bsdStatus = BSD_ERROR;
                goto ERR_OUT;
            }

            BD_INFO("\n");
            rtd_outl(KL_CIPHER_PROTECT_KEY_L2_0, B42L_LE(pxL2CipheredProtectingKey+12));   // [31:0]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L2_1, B42L_LE(pxL2CipheredProtectingKey+ 8));   // [63:32]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L2_2, B42L_LE(pxL2CipheredProtectingKey+ 4));   // [95:64]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L2_3, B42L_LE(pxL2CipheredProtectingKey+ 0));   // [127:96]

            rtd_outl(KL_CIPHER_PROTECT_KEY_L1_0, B42L_LE(pxL1CipheredProtectingKey+12));   // [31:0]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L1_1, B42L_LE(pxL1CipheredProtectingKey+ 8));   // [63:32]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L1_2, B42L_LE(pxL1CipheredProtectingKey+ 4));   // [95:64]
            rtd_outl(KL_CIPHER_PROTECT_KEY_L1_3, B42L_LE(pxL1CipheredProtectingKey+ 0));   // [127:96]

            rtd_outl(KL_CIPHER_CONTENT_KEY_0, B42L_LE(pxCipheredContentKey+12));   // [31:0]
            rtd_outl(KL_CIPHER_CONTENT_KEY_1, B42L_LE(pxCipheredContentKey+ 8));   // [63:32]
            rtd_outl(KL_CIPHER_CONTENT_KEY_2, B42L_LE(pxCipheredContentKey+ 4));   // [95:64]
            rtd_outl(KL_CIPHER_CONTENT_KEY_3, B42L_LE(pxCipheredContentKey+ 0));   // [127:96]

            rtd_outl(KL_CONTENT_KEY_IV_0, 0);   // [31:0]
            rtd_outl(KL_CONTENT_KEY_IV_1, 0);   // [63:32]
            rtd_outl(KL_CONTENT_KEY_IV_2, 0);   // [95:64]
            rtd_outl(KL_CONTENT_KEY_IV_3, 0);   // [127:96]

            BD_INFO("Usage=0x%08x\n",Usage);
            rtd_outl(KL_CTRL1, Usage);   // write usage

            rtd_outl(KL_CTRL2, KL_CTRL2_KDF_K1_KEY_GEN_START);   // generate key on

            // pool state machine to wait for key ready
            try_loop = 1000;    //wait 10ms
            while((KL_STATUS_SCE_SM_STATUS(rtd_inl(KL_STATUS_1))!=16 )
                  && try_loop-- )
            {
                udelay(10);
            }

            if (KL_STATUS_SCE_SM_STATUS(rtd_inl(KL_STATUS_1))!=16)
            {
                BDPRINT("%s failed, wait key ladder ready timeout!!\n",__func__);
                bsdStatus = BSD_ERROR;
                goto ERR_OUT;
            }

            xSession->Emi       = xEmi;   // store Emi
            xSession->last_key  = BSD_USE_KEY_LADDER_KEY;
            BD_INFO("\n");
        }
    }

ERR_OUT:
    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdUseFlashProtKey (TBsdCipherSession xSession, TUnsignedInt16 xEmi)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    if (rtk_chkSessionHandle(xSession) < 0)
    {
        BDPRINT("bsdUseFlashProtKey failed, invalid seesion parameter\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{

#define SHOW_FLASH_PROTECT_KEY
//#define FAKE_FLASH_PROTECT_KEY

#ifdef SHOW_FLASH_PROTECT_KEY
/* show flash key here *** */
        unsigned reginfo1;
        unsigned reginfo0;

#ifdef FAKE_FLASH_PROTECT_KEY

/*
For clearTest decrypt test
0123456789abcdef23456789abcdef01
*/
        //rtd_outl(TP_KEY_INFO_1,0x01020506);
        //rtd_outl(TP_KEY_INFO_0,0x03040708);
        rtd_outl(TP_KEY_INFO_1,0x01234567);
        rtd_outl(TP_KEY_INFO_0,0x89abcdef);

        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ENTRY_0 |TP_ENTRY_WRT );

        rtd_outl(TP_KEY_INFO_1,0x01020304);
        rtd_outl(TP_KEY_INFO_0,0x05060708);
#endif
        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ENTRY_0 |TP_ENTRY_RED );
        reginfo1 = rtd_inl(TP_KEY_INFO_1);
        reginfo0 = rtd_inl(TP_KEY_INFO_0);

        BD_INFO("FLASH_PROTECT KEY(%d): %08x%08x\n",
                FLASH_PROTECT_ENTRY_0,reginfo1,reginfo0);

#ifdef FAKE_FLASH_PROTECT_KEY
        //rtd_outl(TP_KEY_INFO_1,0x0a0b1234);
        //rtd_outl(TP_KEY_INFO_0,0x0c0d5678);
        rtd_outl(TP_KEY_INFO_1,0x23456789);
        rtd_outl(TP_KEY_INFO_0,0xabcdef01);

        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ENTRY_1 |TP_ENTRY_WRT );

        rtd_outl(TP_KEY_INFO_1,0xdddd5678);
        rtd_outl(TP_KEY_INFO_0,0x3344ccdd);
#endif
        rtd_outl(TP_KEY_CTRL,FLASH_PROTECT_ENTRY_1 |TP_ENTRY_RED );
        reginfo1 = rtd_inl(TP_KEY_INFO_1);
        reginfo0 = rtd_inl(TP_KEY_INFO_0);

        BD_INFO("FLASH_PROTECT KEY(%d): %08x%08x\n",
                FLASH_PROTECT_ENTRY_1,reginfo1,reginfo0);

#endif

        ////// test only //////
#if 0
        rtd_outl(TP_KEY_INFO_1,0);
        rtd_outl(TP_KEY_INFO_0,0);

        rtd_outl(TP_KEY_CTRL,(FLASH_PROTECT_ENTRY_1+1) |TP_ENTRY_WRT );

        rtd_outl(TP_KEY_INFO_1,0xdddd5678);
        rtd_outl(TP_KEY_INFO_0,0x3344ccdd);

        rtd_outl(TP_KEY_CTRL,(FLASH_PROTECT_ENTRY_1+1) |TP_ENTRY_RED );
        reginfo1 = rtd_inl(TP_KEY_INFO_1);
        reginfo0 = rtd_inl(TP_KEY_INFO_0);

        BD_INFO("FLASH_PROTECT KEY(%d): 0x%08x 0x%08x\n",
                FLASH_PROTECT_ENTRY_1+1,reginfo1,reginfo0);
#endif

        switch(xEmi)
        {
        //0x4021
        case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
        //0x4026
        case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        //0x4041
        case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
        //0x4043
        case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            break;

        default:
            BDPRINT("bsdUseFlashProtKey failed, invalid EMI %04x\n", xEmi);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        if(bsdStatus == BSD_NO_ERROR){
            xSession->Emi = xEmi;
            xSession->last_key = BSD_USE_FLASH_PROTECTION_KEY;
            BD_INFO("xEmi=0x%x; last_key=%d\n",
                    xSession->Emi,xSession->last_key);
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

#ifdef CONGIG_FAKE_CERT_TEST

#if FAKE_GEN_KEY_600
#define FAKE_CERT_NAME      "FAKE_GEN_KEY_600"
#define CERT_CMD_SET_NUM    23
unsigned int FAKE_DATA_ARY[CERT_CMD_SET_NUM][9] =
{
    {   0x00000000,0x00000000,0xD0000000,0x01000000,    //cmd0
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10010001  },
    {   0x000EB765,0xFC444444,0x44890000,0x00000000,    //cmd1
        0x201F8CD0,0xCD5ADDA3,0x108630F2,0x8D4DAFCB,
        0x10020001  },
    {   0x01234567,0x89ABCDEF,0x01234567,0x89ABCDEF,    //cmd2
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10025001  },
    {   0x2C62D1E9,0x5CD6E49F,0x2961092B,0xB669DF57,    //cmd3
        0xAE4530F6,0x310D8885,0x34ED5110,0x1188B02E,
        0x10100001  },
    {   0x000E1565,0xFC22E47E,0x1F000000,0x00000000,    //cmd4
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10020001  },
    {   0x01234567,0x89ABCDEF,0x01234567,0x89ABCDEF,    //cmd5
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10024001  },
    {   0x86A54A3A,0x6446C61C,0x00000000,0x00000000,    //cmd6
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10200001  },
    {   0x000E8A65,0xFC89ABCD,0xEF22E47D,0xEC7D9B77,    //cmd7
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10020001  },
    {   0x05D1F500,0xA5EBB1D4,0xA0E532EB,0x7268FF2B,    //cmd8
        0x1B904166,0x883B3B5D,0xE469009D,0x9098C536,
        0x10020001  },
    {   0xF39A79E6,0xE1943B60,0x4E053A08,0x6B15D833,    //cmd9
        0x420119A0,0x7D34C396,0x6DFAC635,0x693E1B69,
        0x10020001  },
    {   0x4EE6F7A7,0x597018F2,0x00000000,0x00000000,    //cmd10
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10020001  },
    {   0x000E0000,0x00000000,0x00000000,0x00000000,    //cmd11
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10020001  },
    {   0xA72150B1,0x3559F307,0x757E8DEF,0x6B266B62,    //cmd12
        0xA6BE3D92,0x5B399D43,0x84A949ED,0xA988D0CC,
        0x10020001  },
    {   0x000EEB00,0xD03F94B1,0x9D9C4BCC,0x613C5218,    //cmd13
        0x949C17B0,0xA0C47C58,0x304809EC,0xE979C5A1,
        0x10020001  },
    {   0xE905D8DF,0x757CE6AD,0x06C86E96,0x83270E04,    //cmd14
        0x43BC6C10,0xCF68E6E9,0xB9986FED,0x692FD8B5,
        0x10020001  },
    {   0x000EA9E1,0x98F1CBBB,0x45A221D9,0x502EA250,    //cmd15
        0x30117783,0x2E1890A8,0x2AC7ED0C,0xB641409B,
        0x10020001  },
    {   0xC1D9E1FE,0x9099DB65,0x53645CF8,0xF8BA8861,    //cmd16
        0x544EA08A,0xE71FDA6F,0x6026299F,0x11DD85A6,
        0x10020001  },
    {   0x000E1E65,0xFC012345,0x670111D0,0x00000000,    //cmd17
        0x00000000,0x1D19F41E,0xB3EC6504,0xEBA2202B,
        0x10020001  },
    {   0x09AFCE95,0x8AD59B31,0x63C82613,0xF9637C9C,    //cmd18
        0x157FFB2C,0x1BB59869,0x95AC3A3A,0xFB17313A,
        0x10020001  },
    {   0x88538DD0,0xA89F61CB,0xF948AC4D,0x633B944D,    //cmd19
        0x4B977FFC,0x21E4E66B,0x114C1F84,0xB3468C9A,
        0x10020001  },
    {   0x01234567,0x89ABCDEF,0x01234567,0x89ABCDEF,    //cmd20
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10025001  },
    {   0x2EA23492,0xEB112578,0x00000000,0x00000000,    //cmd21
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x10040001  },
    {   0x00000000,0x00000000,0x00000000,0x00000000,    //cmd22
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x06010201  }
};
#endif


#if FAKE_GEN_KEY_700
#define FAKE_CERT_NAME      "FAKE_GEN_KEY_700"
#define CERT_CMD_SET_NUM    4
unsigned int FAKE_DATA_ARY[CERT_CMD_SET_NUM][9] =
{
    {   0x000E0000,0x00000000,0x00000000,0x00000000,    //cmd0
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x0E010001
    },
    {   0xD10011CE,0x9FDE1F59,0x850B0678,0xD5D3B96E,    //cmd1
        0x61084447,0xAD4EB0A0,0x83549428,0x30CADBC8,
        0x0E020001
    },
    {   0x00000000,0x00000000,0x00000000,0x00000000,    //cmd2
        0xB7B8E3D3,0xB13A3A0B,0x60499F98,0x089F08B3,
        0x0E040001
    },
    {   0x00000000,0x00000000,0x00000000,0x00000000,    //cmd3
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x0601B001
    }

};
#endif


#if FAKE_CERT_NATIVE_RPC
#define FAKE_CERT_NAME      "FAKE_CERT_NATIVE_RPC"
#define CERT_CMD_SET_NUM    7
unsigned int FAKE_DATA_ARY[CERT_CMD_SET_NUM][9] =
{
    {   0x00000400,0xe3000000,0x0000af31,0x00000000,    //cmd0
        0x00000000,0x00000000,0x00000000,0x09040000,
        0x0100010f  },
    {   0x16000000,0x16000000,0x16000000,0x16000000,    //cmd1
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x0120020f  },
    {   0xbbfd805e,0x7bf9d48c,0x00000000,0x00000000,    //cmd2
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x0100040f  },
    {   0x00000400,0x00000000,0x00000000,0x00000000,    //cmd3
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x0100010e  },
    {   0x000001d0,0x00000000,0xf2679ca0,0x9744aa10,    //cmd4
        0xeae26415,0x223a0db0,0x74eee997,0x399efb6e,
        0x0100020e  },
    {   0x00000000,0x00000000,0x00000000,0x00000000,    //cmd5
        0x1a7c30f5,0x911dde17,0x358967de,0xa3a54615,
        0x0100040e  },
    {   0x00000000,0x00000000,0x00000000,0x00000000,    //cmd6
        0x00000000,0x00000000,0x00000000,0x00000000,
        0x01000106  }
};
#endif

#endif //?#ifdef CONGIG_FAKE_CERT_TEST

TBsdStatus  bsdUseCertKey (
    TBsdCipherSession   xSession,
    TUnsignedInt16      xEmi )
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    int retry = 0;

    BDPRINT_FUNC();

    if (rtk_chkSessionHandle(xSession) < 0)
    {
        BDPRINT("bsdUseCertKey failed, invalid seesion parameter\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{

#ifdef CONGIG_FAKE_CERT_TEST
    if(1){
        TCertCommand fake_cert_cmd;
        unsigned int* ptr32_1;
        unsigned int* ptr32_2;
        unsigned int  i;
        unsigned int  j;

        /* --- Fake CERT CMD  --- */
        BD_INFO("\n\n"
                "***** USE %s[%u] *****\n",
                FAKE_CERT_NAME,CERT_CMD_SET_NUM);

        ptr32_1 = fake_cert_cmd.opcodes;
        ptr32_2 = fake_cert_cmd.inputData;

        for(i=0;i<CERT_CMD_SET_NUM;i++){

            BD_INFO("CHECK CONGIG_FAKE_CERT_TEST[%u]\n",i);

            memset(&fake_cert_cmd,0,sizeof(TCertCommand));
            fake_cert_cmd.timeout = 300;
            ptr32_1[0] = FAKE_DATA_ARY[i][8];
            if(CERT_CMD_SET_NUM != 7)
                rtk_rev_bytes_local(&ptr32_1[0],4);

            for(j=0;j<8;j++){
                ptr32_2[j] = FAKE_DATA_ARY[i][j];
                if(CERT_CMD_SET_NUM != 7)
                    rtk_rev_bytes_local(&ptr32_2[j],4);
            }
            _certDoCommand(&fake_cert_cmd);
        }

    }
#endif
        switch(xEmi)
        {
        //0x4021
        case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
        //0x4026
        case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        //0x4041
        case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
        //0x4043
        case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
            break;

        default:
            BDPRINT("bsdUseCertKey failed, invalid EMI %04x\n", xEmi);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        if(bsdStatus == BSD_NO_ERROR){
            xSession->Emi       = xEmi;
            xSession->last_key  = BSD_USE_CERT_KEY;
        }
    }

    /* The CERT block must be acknowledged even in case the EMI provided is not
     *      supported (#SEC_ERROR_BAD_EMI) or in case of bad key usage
     *      (#SEC_ERROR_BAD_USAGE). Otherwise the CERT block will no longer be able
     *      output keys on the key output interface.
     */
    BDPRINT("Load Cert Key to KT %d\n", xSession->KeyTableIndex);

    rtd_outl(KT_HOSTKEY_USAGE_REG, 0);
    rtd_outl(KT_WADR_REG, xSession->KeyTableIndex);

    udelay(10);

    rtd_outl(KT_WADR_REG, KT_WADR_AKL_WT_EN | xSession->KeyTableIndex);      // ack to store keys

    retry = 100;
    while((rtd_inl(KT_WADR_REG) & KT_WADR_AKL_WT_EN) && retry--){
        BD_INFO("wait KT AKL\n");
        udelay(10);
    }
    if (rtd_inl(KT_WADR_REG) & KT_WADR_AKL_WT_EN)
    {
        BD_INFO("Load Cert Key to KT %d failed\n"
                "wait KT_WADR_AKL_WT_EN done timeout (STATUS=%08lx)>>>>>>>>>>>>>\n",
                xSession->KeyTableIndex, rtd_inl(0xb801D040));
        bsdStatus = BSD_ERROR;
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/* reference Sirius_TP_Arch_Spec.doc
    ADDR::0x1801_4058
    ADDR::0x1801_4060
*/

static
TBsdStatus rtk_bsdFlashProtectKeyEncryption(
    TUnsignedInt16          xEmi,
    const TUnsignedInt8*    pxInput,
    TUnsignedInt8*          pxOutput,
    size_t                  xMessageSize,
    const TUnsignedInt8*    pxInitVector,
    size_t                  xInitVectorSize
    )
{
    int ret = 0;
    unsigned char* tmp_key;
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    tmp_key = malloc(24);
    memset(tmp_key,0,24);

    BDPRINT("xEmi=0x%08x; xMessageSize=%d; xInitVectorSize=%d\n"
            "pxInput=0x%p; pxOutput=0x%p; pxInitVector0x%p\n",
             xEmi,xMessageSize,xInitVectorSize,
             pxInput,pxOutput,pxInitVector);

    rtk_show_data(xMessageSize,xMessageSize,
                  (void *)pxInput,TCLOSE,
                  (unsigned char*)"show pxInput");

    rtk_show_data(xInitVectorSize,xInitVectorSize,
                  (void *)pxInitVector,TCLOSE,
                  (unsigned char*)"show pxInitVector");

    switch(xEmi)
    {
    //0x4021
    case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
        BD_INFO("\n");
        ret = MCP_AES_Encryption(MCP_BCM_ECB,
                           (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,//tmp_key,
                           NULL,
                           pxInput, pxOutput, xMessageSize);
        break;

    //0x4026
    case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        BD_INFO("\n");
        ret = MCP_AES_Encryption(MCP_BCM_CBC,
                           (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,
                           pxInitVector,
                           pxInput, pxOutput, xMessageSize);
        break;

    //0x4041
    case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
        BD_INFO("RTK MCP CW have not support TDES vector!!\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
//        ret = MCP_TDES_Encryption(MCP_BCM_ECB,
//                            (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,//tmp_key
//                            NULL,
//                            pxInput, pxOutput, xMessageSize);
        break;

    //0x4043
    case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        BD_INFO("RTK MCP CW have not support TDES vector!!\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
//        ret = MCP_TDES_Encryption(MCP_BCM_CBC,
//                            (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,//tmp_key,
//                            pxInitVector,
//                            pxInput, pxOutput, xMessageSize);
        break;

    default:
        BDPRINT("%s failed, invalid EMI %04x\n", __func__,xEmi);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
        break;
    }

    if(ret){
        bsdStatus = BSD_ERROR;
    }

    if(bsdStatus == BSD_NO_ERROR){
        rtk_show_data(xMessageSize,xMessageSize,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"show pxOutput");
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


static
TBsdStatus rtk_bsdFlashProtectKeyDecryption(
    TUnsignedInt16          xEmi,
    const TUnsignedInt8*    pxInput,
    TUnsignedInt8*          pxOutput,
    size_t                  xMessageSize,
    const TUnsignedInt8*    pxInitVector,
    size_t                  xInitVectorSize
    )
{
    int ret;
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();
    BDPRINT("xEmi=0x%08x; xMessageSize=%d; xInitVectorSize=%d\n"
            "pxInput=0x%p; pxOutput=0x%p; pxInitVector0x%p\n",
             xEmi,xMessageSize,xInitVectorSize,
             pxInput,pxOutput,pxInitVector);

    rtk_show_data(xMessageSize,xMessageSize,
                  (void *)pxInput,TCLOSE,
                  (unsigned char*)"show pxInput");

    rtk_show_data(xMessageSize,xInitVectorSize,
                  (void *)pxInitVector,TCLOSE,
                  (unsigned char*)"show pxInitVector");

    switch(xEmi)
    {
    //0x4021
    case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
        MCP_AES_Decryption(MCP_BCM_ECB,
                           (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,
                           NULL, pxInput, pxOutput, xMessageSize);
        break;

    //0x4026
    case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        MCP_AES_Decryption(MCP_BCM_CBC,
                           (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,
                           pxInitVector, pxInput, pxOutput, xMessageSize);
        break;

    //0x4041
    case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
        BD_INFO("RTK MCP CW have not support TDES vector!!\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
        //MCP_TDES_Decryption(MCP_BCM_ECB,
        //                    (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,
        //                    NULL, pxInput, pxOutput, xMessageSize);
        break;

    //0x4043
    case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
        BD_INFO("RTK MCP CW have not support TDES vector!!\n");
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
        //MCP_TDES_Decryption(MCP_BCM_CBC,
        //                    (unsigned char*)CP_CW_FLASH_PROTECT_KEY_ENTRY,
        //                    pxInitVector, pxInput, pxOutput, xMessageSize);
        break;

    default:
        BDPRINT("secUseFlashProtKey failed, BAD EMI %04x\n", xEmi);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }

    if(ret){
        bsdStatus = BSD_ERROR;
    }else{
        rtk_show_data(8,xMessageSize,(void *)pxOutput,0,
                      (unsigned char*)"show pxOutput");
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdSessionEncrypt (
    TBsdCipherSession       xSession,
    const TUnsignedInt8*    pxInput,
    TUnsignedInt8*          pxOutput,
    TSize                   xMessageSize,
    const TUnsignedInt8*    pxInitVector,
    TSize                   xInitVectorSize )
{
    TBsdStatus      bsdStatus = BSD_NO_ERROR;
    unsigned int    KeyUsage  = 0;
    unsigned int    MdCtrl    = 0;
    unsigned int    DataType  = 0;
    unsigned char*  data_buf  = NULL;

    BDPRINT_FUNC();

    BDPRINT("xSession=0x%p\n",xSession);
    BDPRINT("xEmi=0x%08x; xMessageSize=%d; xInitVectorSize=%d\n"
            "pxInput=0x%p; pxOutput=0x%p; pxInitVector0x%p\n",
             xSession->Emi,xMessageSize,xInitVectorSize,
             pxInput,pxOutput,pxInitVector);

    rtk_show_data(xMessageSize,xMessageSize,
                  (void *)pxInput,TCLOSE,
                  (unsigned char*)"show pxInput");

    rtk_show_data(xInitVectorSize,xInitVectorSize,
                  (void *)pxInitVector,TCLOSE,
                  (unsigned char*)"show pxInitVector");

    if (xSession->en_de != BSD_ENCRYPTION)
    {
        BDPRINT("%s failed, current session is not a encryption session\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else if (pxInput==NULL || pxOutput==NULL)
    {
        BDPRINT("%s failed, pxInput/pxOutput should not be NULL\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else if (rtk_chkSessionHandle(xSession) < 0)
    {
        BDPRINT("%s failed, invalid seesion parameter\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        BD_INFO("last_key=%d\n",xSession->last_key);
        switch(xSession->last_key)
        {
            case BSD_USE_CERT_KEY:          //0
            case BSD_USE_KEY_LADDER_KEY:    //1
            case BSD_USE_CLEAR_TEXT_KEY:    //2
            case BSD_USE_LEGACY_KEY:        //4
            BD_INFO("\n");
            // TODO: call MD to encrypt data with Nagra DSC engine
            // at this point, the key has been loaded to key table at entry specified by .

            // 1. Update IV to Key Table
            rtd_outl(KT_WADR_REG, xSession->KeyTableIndex);       // write key table address
            if (pxInitVector==NULL)
            {
                BD_INFO("\n");
                rtd_outl(KT_HOSTKEY_IV1_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV2_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV3_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV4_REG, 0x00000000);
            }
            else
            {
                BD_INFO("\n");
                if(xSession->Emi == 0x4026){
                    rtd_outl(KT_HOSTKEY_IV1_REG, (pxInitVector[12]<<24) | (pxInitVector[13]<<16) | (pxInitVector[14]<<8) | pxInitVector[15]);   // [31:0]
                    rtd_outl(KT_HOSTKEY_IV2_REG, (pxInitVector[ 8]<<24) | (pxInitVector[ 9]<<16) | (pxInitVector[10]<<8) | pxInitVector[11]);   // [63:32]
                    rtd_outl(KT_HOSTKEY_IV3_REG, (pxInitVector[ 4]<<24) | (pxInitVector[ 5]<<16) | (pxInitVector[ 6]<<8) | pxInitVector[ 7]);   // [95:64]
                    rtd_outl(KT_HOSTKEY_IV4_REG, (pxInitVector[ 0]<<24) | (pxInitVector[ 1]<<16) | (pxInitVector[ 2]<<8) | pxInitVector[ 3]);   // [127:96]
                }else{
                    rtd_outl(KT_HOSTKEY_IV1_REG, (pxInitVector[ 4]<<24) | (pxInitVector[ 5]<<16) | (pxInitVector[ 6]<<8) | pxInitVector[ 7]);   // [31:0]
                    rtd_outl(KT_HOSTKEY_IV2_REG, (pxInitVector[ 0]<<24) | (pxInitVector[ 1]<<16) | (pxInitVector[ 2]<<8) | pxInitVector[ 3]);   // [63:32]
                    rtd_outl(KT_HOSTKEY_IV3_REG, 0);
                    rtd_outl(KT_HOSTKEY_IV4_REG, 0);
                }
            }
            rtd_outl(KT_HOSTKEY_USAGE_REG, KT_HOSTKEY_USAGE_HOSTKEY_IV_ONLY | KT_HOSTKEY_USAGE_HOSTKEY_VALID);

            // 2. set load key to DSC
            BD_INFO("Emi=0x%x\n",xSession->Emi);
            switch(xSession->Emi)
            {
            //0x4021
            case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_AES_MODE_ECB | KT_RDKEY_USAGE_CRYPTO_ENGINE_AES;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                           MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_ECB;
                break;

            //0x4026
            case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_AES_MODE_CBC | KT_RDKEY_USAGE_CRYPTO_ENGINE_AES;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                           MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_CBC_TERMINATE_IN_CLEAR;
                break;

            //0x4041
            case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_TDES_MODE_ECB | KT_RDKEY_USAGE_CRYPTO_ENGINE_TDES;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                           MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_ECB;
                break;

            //0x4043
            case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_TDES_MODE_CBC | KT_RDKEY_USAGE_CRYPTO_ENGINE_TDES;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                           MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_CBC;
                break;

            default:
                BDPRINT("%s failed, invalid EMI %04x\n", __func__,xSession->Emi);
                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
                break;
            }

            if(bsdStatus == BSD_NO_ERROR){
                BD_INFO("\n");
                KeyUsage |= KT_RDKEY_USAGE_KEY_INDEX(xSession->KeyTableIndex);
                KeyUsage |= KT_RDKEY_USAGE_ENCRYPT_EN(1);

                rtd_outl(KT_RDKEY_USAGE_REG, KeyUsage);
                udelay(10);
                rtd_outl(KT_RDKEY_USAGE_REG, KeyUsage | KT_RDKEY_USAGE_RD_KEY_EN);   // Write Key to DSC IP

            // 3. trigger
                DataType |= MD_DSC_DATATYPE_WRITE_EN2 | MD_DSC_DATATYPE_DSC_M2M_TYPE_DATA;
                MdCtrl   |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_ENCRYPT |
                            MD_KT_CTRL_WRITE_EN1 | MD_KT_CTRL_MD_KT_KEY_INDEX(xSession->KeyTableIndex);

                data_buf = malloc(xMessageSize);
                if(data_buf == NULL)
                {
                     BDPRINT("%s failed, request section buffer failed (size=%d)\n", __func__,xMessageSize);
                     bsdStatus = BSD_ERROR;
                }else{
                    BD_INFO("\n");
                    memcpy(data_buf, pxInput, xMessageSize);

                    rtd_outl(MD_DSC_SADDR,    (unsigned int)data_buf);
                    rtd_outl(MD_DSC_DESTADDR, (unsigned int)data_buf);
                    rtd_outl(MD_DSC_TOTLENGTH, xMessageSize);
                    rtd_outl(MD_DSC_HEADERLEN, 0);
                    rtd_outl(MD_KT_CTRL, MdCtrl);
                    rtd_outl(MD_DSC_DATATYPE, DataType);

                    rtd_outl(MD_DSC_CNTL,0);

                    rtd_outl(MD_DSC_CNTL, MD_DSC_CNTL_WRITE_DATA | MD_DSC_CNTL_DSC_GO);

                    while((rtd_inl(MD_DSC_CNTL) & MD_DSC_CNTL_DSC_IDEL)==0)
                        udelay(1000);

                    memcpy(pxOutput, data_buf, xMessageSize);
                    free(data_buf);

                    rtk_show_data(xMessageSize,xMessageSize,
                        (void *)pxOutput,TCLOSE,
                        (unsigned char*)"show pxOutput");

                }
            }

            break;
        case BSD_USE_FLASH_PROTECTION_KEY:
            BD_INFO("\n");
            bsdStatus = rtk_bsdFlashProtectKeyEncryption(
                            xSession->Emi,
                            pxInput,
                            pxOutput,
                            xMessageSize,
                            pxInitVector,
                            xInitVectorSize);
            break;

        default:
            BDPRINT("%s failed, invalid last_key\n",__func__);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }


    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

TBsdStatus  bsdSessionDecrypt (
    TBsdCipherSession       xSession,
    const TUnsignedInt8*    pxInput,
    TUnsignedInt8*          pxOutput,
    TSize                   xMessageSize,
    const TUnsignedInt8*    pxInitVector,
    TSize                   xInitVectorSize)
{
    TBsdStatus      bsdStatus = BSD_NO_ERROR;
    unsigned long   KeyUsage  = 0;
    unsigned long   MdCtrl    = 0;
    unsigned long   DataType  = 0;
    unsigned char*  data_buf  = NULL;

    BDPRINT_FUNC();

    BDPRINT("xSession=0x%p\n",xSession);
    BDPRINT("xEmi=0x%08x; xMessageSize=%d; xInitVectorSize=%d\n"
            "pxInput=0x%p; pxOutput=0x%p; pxInitVector0x%p\n",
             xSession->Emi,xMessageSize,xInitVectorSize,
             pxInput,pxOutput,pxInitVector);

    rtk_show_data(xMessageSize,xMessageSize,
                  (void *)pxInput,TCLOSE,
                  (unsigned char*)"show pxInput");

    rtk_show_data(xInitVectorSize,xInitVectorSize,
                  (void *)pxInitVector,TCLOSE,
                  (unsigned char*)"show pxInitVector");

//#define SKIP_RPC_DECRYPT_ISSUE
    if (pxInput==NULL || pxOutput==NULL)
    {
        BDPRINT("%s failed, pxInput/pxOutput should not be NULL\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else if (rtk_chkSessionHandle(xSession) < 0)
    {
        BDPRINT("%s failed, invalid seesion parameter\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else if (xSession->en_de != BSD_DECRYPTION)
    {
        BDPRINT("%s failed, current session is not a decryption session\n",__func__);
#ifndef SKIP_RPC_DECRYPT_ISSUE
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
#else
        BDPRINT("For RTK test Skip this issue and reset DECRYPTION \n");
        xSession->en_de = BSD_DECRYPTION;
        goto SKIP_BSD_DEC_ERR;
#endif
    }else{

SKIP_BSD_DEC_ERR:
        BD_INFO("last_key=%d\n",xSession->last_key);
        switch(xSession->last_key)
        {
        case BSD_USE_CERT_KEY:
        case BSD_USE_KEY_LADDER_KEY:
        case BSD_USE_CLEAR_TEXT_KEY:
        case BSD_USE_LEGACY_KEY:
            BD_INFO("\n");
            // TODO: call MD to encrypt data with Nagra DSC engine
            // at this point, the key has been loaded to key table at entry specified by .

            // 1. Update IV to Key Table
            rtd_outl(KT_WADR_REG, xSession->KeyTableIndex);       // write key table address
            if (pxInitVector==NULL)
            {
                BD_INFO("\n");
                rtd_outl(KT_HOSTKEY_IV1_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV2_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV3_REG, 0x00000000);
                rtd_outl(KT_HOSTKEY_IV4_REG, 0x00000000);
            }
            else
            {
                if(xSession->Emi == 0x4026){
                    BD_INFO("\n");
                    rtd_outl(KT_HOSTKEY_IV1_REG, (pxInitVector[12]<<24) | (pxInitVector[13]<<16) | (pxInitVector[14]<<8) | pxInitVector[15]);   // [31:0]
                    rtd_outl(KT_HOSTKEY_IV2_REG, (pxInitVector[ 8]<<24) | (pxInitVector[ 9]<<16) | (pxInitVector[10]<<8) | pxInitVector[11]);   // [63:32]
                    rtd_outl(KT_HOSTKEY_IV3_REG, (pxInitVector[ 4]<<24) | (pxInitVector[ 5]<<16) | (pxInitVector[ 6]<<8) | pxInitVector[ 7]);   // [95:64]
                    rtd_outl(KT_HOSTKEY_IV4_REG, (pxInitVector[ 0]<<24) | (pxInitVector[ 1]<<16) | (pxInitVector[ 2]<<8) | pxInitVector[ 3]);   // [127:96]
                }else{
                    BD_INFO("\n");
                    rtd_outl(KT_HOSTKEY_IV1_REG, (pxInitVector[ 4]<<24) | (pxInitVector[ 5]<<16) | (pxInitVector[ 6]<<8) | pxInitVector[ 7]);   // [31:0]
                    rtd_outl(KT_HOSTKEY_IV2_REG, (pxInitVector[ 0]<<24) | (pxInitVector[ 1]<<16) | (pxInitVector[ 2]<<8) | pxInitVector[ 3]);   // [63:32]
                    rtd_outl(KT_HOSTKEY_IV3_REG, 0);
                    rtd_outl(KT_HOSTKEY_IV4_REG, 0);
                }
            }


#ifndef SKIP_RPC_DECRYPT_ISSUE
            {
            unsigned int reg_usage;
            reg_usage = rtd_inl(KT_HOSTKEY_USAGE_REG);
            BD_INFO("KT_HOSTKEY_USAGE_REG = 0x%08x\n",reg_usage);
            rtd_outl(KT_HOSTKEY_USAGE_REG,
                     KT_HOSTKEY_USAGE_HOSTKEY_IV_ONLY |
                     KT_HOSTKEY_USAGE_HOSTKEY_VALID);
            reg_usage = rtd_inl(KT_HOSTKEY_USAGE_REG);
            BD_INFO("KT_HOSTKEY_USAGE_REG = 0x%08x\n",reg_usage);
            }
#else
            {
            unsigned int reg_usage;
            reg_usage = rtd_inl(KT_HOSTKEY_USAGE_REG);
            BD_INFO("KT_HOSTKEY_USAGE_REG = 0x%08x\n",reg_usage);
            reg_usage &= ~KT_HOSTKEY_USAGE_ENCRYPT_EN;
            rtd_outl(KT_HOSTKEY_USAGE_REG,
                     reg_usage|
                     KT_HOSTKEY_USAGE_DECRYPT_EN|
                     KT_HOSTKEY_USAGE_HOSTKEY_VALID);
            reg_usage = rtd_inl(KT_HOSTKEY_USAGE_REG);
            BD_INFO("KT_HOSTKEY_USAGE_REG = 0x%08x\n",reg_usage);
            }
#endif

            // 2. set load key to DSC
            BD_INFO("Emi=0x%x\n",xSession->Emi);
            switch(xSession->Emi)
            {
            //0x4021
            case EMI_NORMAL_AES_128_ECB_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_AES_MODE_ECB | KT_RDKEY_USAGE_CRYPTO_ENGINE_AES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                           MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_ECB;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
                break;

            //0x4026
            case EMI_NORMAL_AES_128_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_AES_MODE_CBC | KT_RDKEY_USAGE_CRYPTO_ENGINE_AES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                           MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_CBC_TERMINATE_IN_CLEAR;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
                break;

            //0x4041
            case EMI_NORMAL_TES_K1K2_ECB_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_TDES_MODE_ECB | KT_RDKEY_USAGE_CRYPTO_ENGINE_TDES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                           MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_ECB;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
                break;

            //0x4043
            case EMI_NORMAL_TES_K1K2_CBC_IV_MODIFIABLE_TERMINATION_IN_CLEAR:
                BD_INFO("\n");
                KeyUsage = KT_RDKEY_USAGE_TDES_MODE_CBC | KT_RDKEY_USAGE_CRYPTO_ENGINE_TDES;
                MdCtrl   = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                           MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_CBC;
                DataType = MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
                break;

            default:
                BDPRINT("%s failed, invalid EMI %04x\n", __func__,xSession->Emi);
                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
                break;
            }

            if(bsdStatus == BSD_NO_ERROR){
                BD_INFO("\n");
                KeyUsage |= KT_RDKEY_USAGE_KEY_INDEX(xSession->KeyTableIndex);
                KeyUsage |= KT_RDKEY_USAGE_ENCRYPT_EN(0);

                rtd_outl(KT_RDKEY_USAGE_REG, KeyUsage);
                udelay(10);
                rtd_outl(KT_RDKEY_USAGE_REG, KeyUsage | KT_RDKEY_USAGE_RD_KEY_EN);   // Write Key to DSC IP

                // 3. trigger
                MdCtrl   |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_DECRYPT |
                            MD_KT_CTRL_WRITE_EN1 | MD_KT_CTRL_MD_KT_KEY_INDEX(xSession->KeyTableIndex);

                DataType |=  MD_DSC_DATATYPE_WRITE_EN2 | MD_DSC_DATATYPE_DSC_M2M_TYPE_DATA;

                data_buf = malloc(xMessageSize);
                if(data_buf == NULL)
                {
                     BDPRINT("%s failed, request section buffer failed (size=%d)\n", __func__,xMessageSize);
                     bsdStatus = BSD_ERROR;
                }else{
                    BD_INFO("\n");
                    memcpy(data_buf, pxInput, xMessageSize);
                    rtd_outl(MD_DSC_SADDR,      (unsigned int)data_buf);
                    rtd_outl(MD_DSC_DESTADDR,   (unsigned int)data_buf);
                    rtd_outl(MD_DSC_TOTLENGTH,  xMessageSize);
                    rtd_outl(MD_DSC_HEADERLEN,  0);
                    rtd_outl(MD_KT_CTRL,        MdCtrl);
                    rtd_outl(MD_DSC_DATATYPE,   DataType);

                    rtd_outl(MD_DSC_CNTL,0);

                    rtd_outl(MD_DSC_CNTL, MD_DSC_CNTL_WRITE_DATA | MD_DSC_CNTL_DSC_GO);

                    while((rtd_inl(MD_DSC_CNTL) & MD_DSC_CNTL_DSC_IDEL)==0)
                        udelay(1000);

                    memcpy(pxOutput, data_buf, xMessageSize);
                    free(data_buf);

                    rtk_show_data(xMessageSize,xMessageSize,
                        (void *)pxOutput,TCLOSE,
                        (unsigned char*)"show pxOutput");

                }
            }

            break;
        case BSD_USE_FLASH_PROTECTION_KEY:
            BD_INFO("\n");
            bsdStatus = rtk_bsdFlashProtectKeyDecryption(
                            xSession->Emi,
                            pxInput,
                            pxOutput,
                            xMessageSize,
                            pxInitVector,
                            xInitVectorSize);
            break;

        default:
            BDPRINT("%s failed, invalid last_key\n",__func__);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;

        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

TBsdStatus bsdEncryptDataWithSecretContentKey
(
        TBsdR2RAlgorithm    xAlgorithm,
  const TUnsignedInt8*      pxInputData,
        TUnsignedInt8*      pxOutputData,
        TUnsignedInt32      xDataSize)
{
    TBsdStatus bsdStatus = BSD_ERROR_INVALID_PARAMETERS;

    BDPRINT("%s: In case of NOCS3.0 level, this API shall not be implemented",__func__);

    return bsdStatus;
}


TBsdStatus bsdDecryptDataWithSecretContentKey
(
        TBsdR2RAlgorithm    xAlgorithm,
  const TUnsignedInt8*      pxInputData,
        TUnsignedInt8*      pxOutputData,
        TUnsignedInt32      xDataSize )
{
    TBsdStatus bsdStatus = BSD_ERROR_INVALID_PARAMETERS;

    BDPRINT("%s: In case of NOCS3.0 level, this API shall not be implemented",__func__);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== RSA ====================                            */
/*                                                                          */
/****************************************************************************/
#define USE_RBUS_RNG
#ifdef  USE_RBUS_RNG
#define RNG_OUT_RDY     0xb800182C  //RNG_READY_REG
#define RNG_RAN_OUT     0xb8001838      //RNG_RANDOM_OUT_REG
#else
#define RNG_OUT_RDY     0xb8001804
#define RNG_RAN_OUT     0xb8001810
#endif

#define OUT_RDY         (0x01UL)

static
unsigned int rtk_get_rng(void)
{
    unsigned int limit = 0x10000;
    unsigned int rtn;

    while(((rtd_inl(RNG_OUT_RDY) & OUT_RDY) != OUT_RDY) && limit ){
            udelay(100);
            limit--;
    }
    if(limit == 0){
        BDPRINT("random generator time out!!\n");
        rtn = 0xffffffff;
    }else{
        rtn = rtd_inl(RNG_RAN_OUT);
    }

    return rtn;
}

static
int rtk_rand_bytes(unsigned char *buf,unsigned int num)
{
    unsigned int i;

	BD_INFO("buf=0x%p; num=%d\n",buf,num);

	for(i=0;i<num;i++){
		buf[i] = (unsigned char)rtk_get_rng();
	}
	return num;
}

#if 0
#define RSA_PKCS1_PADDING_SIZE  11
/* for private encrypt */
static
int RSA_padding_add_PKCS1_type_1(
    unsigned char *         to,
    int                     tlen,
    const unsigned char *   from,
    int                     flen )
{
    int j;
    unsigned char *p;

    if (flen > (tlen-RSA_PKCS1_PADDING_SIZE))
    {
        return(0);
    }

    p=(unsigned char *)to;

    *(p++)=0;
    *(p++)=1; /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    j=tlen-3-flen;
    memset(p,0xff,j);
    p+=j;
    *(p++)='\0';
    memcpy(p,from,(unsigned int)flen);
    return(1);
}

/* for private decrypt */
static
int RSA_padding_check_PKCS1_type_1(
    unsigned char *         to,
    int                     tlen,
    const unsigned char *   from,
    int                     flen,
    int                     num )
{
    int i,j;
    const unsigned char *p;

    p=from;
    if ((num != (flen+1)) || (*(p++) != 01))
    {
        return(-1);
    }

    /* scan over padding data */
    j=flen-1; /* one for type. */
    for (i=0; i<j; i++)
    {
        if (*p != 0xff) /* should decrypt to 0xff */
        {
            if (*p == 0){
                p++; break;
            }else{
                return(-1);
            }
        }
        p++;
    }

    if (i == j)
    {
        return(-1);
    }

    if (i < 8)
    {
        return(-1);
    }
    i++; /* Skip over the '\0' */
    j-=i;
    if (j > tlen)
    {
        return(-1);
    }
    memcpy(to,p,(unsigned int)j);

    return(j);
}
#endif

/* for public encrypt */
static
int RSA_padding_add_PKCS1_type_2(
    unsigned char *         to,
    int                     tlen,
    const unsigned char *   from,
    int                     flen )
{
    int i,j;
    unsigned char *p;

    if (flen > (tlen-11))
    {
        BD_INFO("\n");
        return 0;
    }

    p = (unsigned char *)to;

    *(p++)=0;
    *(p++)=2; /* Public Key BT (Block Type) */
	BD_INFO("\n");
    /* pad out with non-zero random data */
    j=tlen-3-flen;

    if (rtk_rand_bytes(p,j) <= 0){
        return 0;
    }

    for (i=0; i<j; i++)
    {
        if (*p == '\0')
            do{
                if (rtk_rand_bytes(p,1) <= 0){
                    return 0;
                }
            } while (*p == '\0');
        p++;
    }

    *(p++)='\0';

    memcpy(p,from,(unsigned int)flen);

    return 1;
}

/* for public decrypt */
int RSA_padding_check_PKCS1_type_2(
    unsigned char *         to,
    int                     tlen,
    const unsigned char *   from,
    int                     flen,
    int                     num)
{
    int i,j;
    const unsigned char *p;

    p=from;
    if ((num != (flen+1)) || (*(p++)!= 0)|| (*(p++) != 2))
    {
        return(-1);
    }

    /* scan over padding data */
    j=flen-1; /* one for type. */
    for (i=0; i<j; i++){
        if (*(p++) == 0) break;
    }

    if (i == j)
    {
        return -1;
    }

    if (i < 8)
    {
        return -1;
    }

    i++; /* Skip over the '\0' */
    j-=i;
    if (j > tlen)
    {
        return -1;
    }
    memcpy(to,p,(unsigned int)j);

    return(j);
}

#define CONFIG_RSA_DEGUG
TBsdStatus  bsdRsaPublicEncrypt (
    const TUnsignedInt8*    pxInput,
    TSize                   xInputSize,
    TUnsignedInt8*          pxOutput,
    TUnsignedInt32          xE,
    const TUnsignedInt8*    pxN,
    TSize                   xKeySize,
    TBsdRsaPadding          xPadding)
{
    int ret = 0;
    unsigned char *pad_buf = NULL;
    unsigned char *buf_ptr = NULL;

    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();
    BDPRINT("xInputSize=%u; xKeySize=%u\n",xInputSize,xKeySize);

    // check pinter
    if (pxN == NULL || pxInput==NULL || pxOutput==NULL)
    {
        BDPRINT("%s : error parametern pxN/pxInput/pxOutput\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }// check Exp
    else if (xE!=3 && xE!=17 && xE!=65537)
    {
        BDPRINT("%s : error parametern xE\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }// check key size
    else if (xKeySize!=128 && xKeySize!=256)
    {
        BDPRINT("%s : error xKeySize\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }
    else
    {
        // check padding scheme
        switch(xPadding)
        {
        case BSD_RSA_PKCS1_V1_5_PADDING:
            BDPRINT("BSD_RSA_PKCS1_V1_5_PADDING\n");
            if (xInputSize + 11 > xKeySize){

                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
                break;
            }
            pad_buf = (unsigned char *)malloc(xKeySize);

            if(pad_buf == NULL){
                BDPRINT("mallocate memory fail..\n");
                bsdStatus = BSD_ERROR;
                break;
            }
            memset(pad_buf,0,xKeySize);
            BDPRINT("make padding...\n");

#ifdef CONFIG_RSA_DEGUG
            rtk_show_data(xInputSize,xInputSize,
                      (void *)pxInput,TCLOSE,
                      (unsigned char*)"show pxInput");

            rtk_show_data(xKeySize,xKeySize,
                      (void *)pad_buf,TCLOSE,
                      (unsigned char*)"show pad_buf(before)");
#endif
            ret = RSA_padding_add_PKCS1_type_2(pad_buf,xKeySize,pxInput,xInputSize);

#ifdef CONFIG_RSA_DEGUG
            rtk_show_data(xKeySize,xKeySize,
                      (void *)pad_buf,TCLOSE,
                      (unsigned char*)"show pad_buf(after)");
#endif
            buf_ptr = pad_buf;
            BDPRINT("padding finish\n");
            if (ret <= 0){
                bsdStatus = BSD_ERROR;
            }

            break;

        case BSD_RSA_OAEP_SHA_1_PADDING:
            BDPRINT("BSD_RSA_OAEP_SHA_1_PADDING\n");
            if (xInputSize + 42 > xKeySize){
                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            }
            BDPRINT("BSD_RSA_OAEP_SHA_1_PADDING not support!\n");
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;

        case BSD_RSA_OAEP_SHA_256_PADDING:
            BDPRINT("BSD_RSA_OAEP_SHA_256_PADDING\n");
            if (xInputSize + 66 > xKeySize){
                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            }
            BDPRINT("BSD_RSA_OAEP_SHA_1_PADDING not support!\n");
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;

        case BSD_RSA_NO_PADDING:
            BDPRINT("BSD_RSA_NO_PADDING\n");
            if (xInputSize != xKeySize){
                BDPRINT("xInputSize=%d; xKeySize=%d\n",xInputSize,xKeySize);
                bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            }
            buf_ptr = pxInput;
            break;

        default:
            BDPRINT("unknow padding type 0x%x\n",xPadding);
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        if(bsdStatus == BSD_NO_ERROR)
        {
            unsigned int i;
            unsigned int ptr_idata;
            unsigned int ptr_key;
            unsigned int exp       = xE;
            unsigned int ptr_exp   = (unsigned int )(&exp);
            unsigned int ptr_odata = (unsigned int )pxOutput;
            unsigned char *idata_buf = NULL;
            unsigned char *key_buf   = NULL;

            idata_buf = (unsigned char *)malloc(xKeySize);
            key_buf   = (unsigned char *)malloc(xKeySize);

            if(idata_buf == NULL || key_buf == NULL){
                bsdStatus = BSD_ERROR;
            }else{
                //rtk_rev_bytes(pxInput,idata_buf, xKeySize);
                rtk_rev_bytes(buf_ptr,idata_buf, xKeySize);
                rtk_rev_bytes(pxN,key_buf, xKeySize);

#ifdef CONFIG_RSA_DEGUG
                rtk_show_data(xKeySize,xKeySize,
                      (void *)pxInput,TCLOSE,
                      (unsigned char*)"Input data=====>");

                rtk_show_data(xKeySize,xKeySize,
                      (void *)idata_buf,TCLOSE,
                      (unsigned char*)"Input data(rev)=====>");

                rtk_show_data(xKeySize,xKeySize,
                      (void *)pxN,TCLOSE,
                      (unsigned char*)"key data=====>");

                rtk_show_data(xKeySize,xKeySize,
                      (void *)key_buf,TCLOSE,
                      (unsigned char*)"key data(rev)=====>");

                rtk_show_data(256,256,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"Output data(before) =====>");
#endif

                ptr_idata = (unsigned int )idata_buf;
                ptr_key   = (unsigned int )key_buf;

                ret = do_RSA_BSD(0, xKeySize,
                                 ptr_idata,ptr_key,ptr_exp,ptr_odata);
                if(ret < 0){
                    BD_INFO("do_RSA_BSD fail(ret=%d)\n",ret);
                    bsdStatus = BSD_ERROR;
                }
#ifdef CONFIG_RSA_DEGUG
                rtk_show_data(128,128,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"Output data(after) =====>");
#endif

                free(idata_buf);
                free(key_buf);
            }
        }
    }

    if(pad_buf)
        free(pad_buf);

    BDPRINT("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

TBsdStatus  bsdRsaPublicDecrypt (
    const TUnsignedInt8*    pxInput,
    TUnsignedInt8*          pxOutput,
    TSize*                  pxOutputSize,
    TUnsignedInt32          xE,
    const TUnsignedInt8*    pxN,
    TSize                   xKeySize,
    TBsdRsaPadding          xPadding)
{

    int ret;

    BDPRINT_FUNC();
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT("xKeySize=%u\n",xKeySize);
    // check pinter
    if (pxN == NULL || pxInput==NULL || pxOutput==NULL){
        BDPRINT("%s : error parametern pxN/pxInput/pxOutput\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    // check Exp
    }else if (xE!=3 && xE!=17 && xE!=65537){
        BDPRINT("%s : error parametern xE (0x%x)\n",__func__,(unsigned int)xE);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    // check key size
    }else if (xKeySize!=128 && xKeySize!=256){
        BDPRINT("%s : error xKeySize\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{

        // check padding scheme
        switch(xPadding)
        {
        case BSD_RSA_PKCS1_V1_5_PADDING:
            BDPRINT("BSD_RSA_PKCS1_V1_5_PADDING\n");
            //PaddingAlgo = RSA_PKCS1_PADDING;
            break;

        case BSD_RSA_OAEP_SHA_1_PADDING:
            BDPRINT("RSA_PKCS1_OAEP_PADDING not support!\n");
            //PaddingAlgo = RSA_PKCS1_OAEP_PADDING;
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;

        case BSD_RSA_OAEP_SHA_256_PADDING:
            BDPRINT("RSA_PKCS1_OAEP_PADDING not support!\n");
            //PaddingAlgo = RSA_PKCS1_OAEP_PADDING;
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;

        case BSD_RSA_NO_PADDING:
            BDPRINT("BSD_RSA_NO_PADDING\n");
            //PaddingAlgo = RSA_NO_PADDING;
            break;

        default:
            bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
            break;
        }

        if(bsdStatus == BSD_NO_ERROR)
        {
            unsigned int i;
            unsigned int exp       = xE;
            unsigned int ptr_idata;
            unsigned int ptr_key;
            unsigned int ptr_exp   = (unsigned int )(&exp);
            unsigned int ptr_odata = (unsigned int )pxOutput;
            //unsigned int ptr_odata = (unsigned int )malloc(256);
            unsigned char *idata_buf = NULL;
            unsigned char *key_buf   = NULL;

            idata_buf = (unsigned char *)malloc(xKeySize);
            key_buf   = (unsigned char *)malloc(xKeySize);

            if(idata_buf ==NULL || key_buf ==NULL ){
                bsdStatus = BSD_ERROR;
            }else{

                rtk_rev_bytes(pxInput,idata_buf, xKeySize);
                rtk_rev_bytes(pxN,key_buf, xKeySize);

#ifdef CONFIG_RSA_DEGUG

				rtk_show_data(xKeySize,xKeySize,
                      (void *)pxInput,TCLOSE,
                      (unsigned char*)"Input data=====>");


				rtk_show_data(xKeySize,xKeySize,
                      (void *)idata_buf,TCLOSE,
                      (unsigned char*)"Input data(rev)=====>");


				rtk_show_data(xKeySize,xKeySize,
                      (void *)pxN,TCLOSE,
                      (unsigned char*)"key data=====>");

				rtk_show_data(xKeySize,xKeySize,
                      (void *)key_buf,TCLOSE,
                      (unsigned char*)"key data(rev)=====>");

				rtk_show_data(256,256,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"Output data(before) =====>");

#endif

                ptr_idata = (unsigned int )idata_buf;
                ptr_key   = (unsigned int )key_buf;

                ret = do_RSA_BSD(0, xKeySize,
                                 ptr_idata,ptr_key,ptr_exp,ptr_odata);


#ifdef CONFIG_RSA_DEGUG

				rtk_show_data(xKeySize,xKeySize,
                      (void *)pxOutput,TCLOSE,
                      (unsigned char*)"Output data(after) =====>");

#endif
				if(ret < 0){
                    BD_INFO("do_RSA_BSD fail(ret=%d)\n",ret);
                    bsdStatus = BSD_ERROR;
                }else{
					memcpy( (void *)idata_buf, (void *)pxOutput, xKeySize );
#ifdef CONFIG_RSA_DEGUG

				rtk_show_data(xKeySize,xKeySize,
                      (void *)idata_buf,TCLOSE,
                      (unsigned char*)"check padding(before) =====>");

#endif

	                if(xPadding == BSD_RSA_PKCS1_V1_5_PADDING){
	                    BDPRINT("BSD_RSA_PKCS1_V1_5_PADDING\n");
	                    ret = RSA_padding_check_PKCS1_type_2(pxOutput, xKeySize,idata_buf, xKeySize-1, xKeySize);
	                }else if(xPadding == BSD_RSA_OAEP_SHA_1_PADDING){
	                    BDPRINT("RSA_PKCS1_OAEP_PADDING not support!\n");
	                    ret = -1;
	                }else if(xPadding == BSD_RSA_OAEP_SHA_256_PADDING){
	                    BDPRINT("BSD_RSA_OAEP_SHA_256_PADDING not support!\n");
	                    ret = -1;
	                }else{
	                    BDPRINT("BSD_RSA_NO_PADDING\n");
	                    ret = xKeySize;
	                }
				}
                if(ret < 0){
                    BD_INFO("ret=%d\n",ret);
                    bsdStatus = BSD_ERROR;
                }else{
                    //ret = 128;    // for tset temp
                    *pxOutputSize = ret;
                }

                free(idata_buf);
                free(key_buf);
            }

        }
    }

    BDPRINT("bsdStatus = %s\n",status_tlb[bsdStatus]);

    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== Digest ====================                         */
/*                                                                          */
/****************************************************************************/
/* SHA-256 */
#define SHA256_INIT_LEN 512
TBsdStatus  bsdSha256Init (TBsdHashContext *pxContext)
{
    struct SBsdHashContext* BsdHashContext;
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    if (pxContext==NULL){
        BDPRINT("%s fail, , pxInput/pxOutput should not be NULL\n",__func__);
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
    }else{
        struct SBsdHashContext * BsdHashContext;
        MCP_MD_CTX  *pmcp_ctx;

        BsdHashContext = (TBsdHashContext)malloc(sizeof(struct SBsdHashContext));
        BD_INFO("BsdHashContext = 0x%p\n",BsdHashContext);

        if(BsdHashContext == NULL ){
            bsdStatus = BSD_ERROR;
        }else{

            memset(BsdHashContext, 0, sizeof(struct SBsdHashContext));

            //./arch/arm/bsp-realtek/mach-rtd298x/mcp/mcp_dgst.c:17:void MCP_MD_CTX_init()
            pmcp_ctx = &(BsdHashContext->mcp_ctx);
            pmcp_ctx->digest       = NULL;
            pmcp_ctx->md_data      = NULL;
            pmcp_ctx->private_data = NULL;

            BD_INFO("pmcp_ctx = 0x%p\n",pmcp_ctx);

            if(SHA256_DigestInit(pmcp_ctx)){
                BDPRINT("%s fail, MCP_DigestInit fail\n",__func__);
                if(pmcp_ctx->md_data)
                    free(pmcp_ctx->md_data);
                bsdStatus = BSD_ERROR;
            }else{
                *pxContext = BsdHashContext;
                BD_INFO("*pxContext = 0x%p\n",BsdHashContext);
                BD_INFO("%s SHA256_DigestInit success\n",__func__);
            }
        }
    }
    if(bsdStatus == BSD_ERROR  && BsdHashContext ){
        BD_INFO("\n");
        free(BsdHashContext);
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


/*
typedef struct SBsdHashContext* TBsdHashContext;

kernel :
vi ./arch/arm/bsp-realtek/mach-rtd298x/mcp/sha256.c +199
./arch/arm/bsp-realtek/mach-rtd298x/mcp/sha256.c:68 :int SHA256_DigestUpdate()
*/
TBsdStatus  bsdSha256Update (
    TBsdHashContext         xContext,
    const TUnsignedInt8*    pxMessageChunk,
    TSize                   xChunkSize)
{
    //int i;
    TBsdStatus bsdStatus = BSD_ERROR;
    BDPRINT_FUNC();

    if (xContext==NULL || pxMessageChunk==NULL)
    {
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
        BDPRINT("%s fail, , xContext/xContext->hHandle/pxMessageChunk should not be NULL\n",__func__);
    }else{
        MCP_BUFF *   kmcpb;
        MCP_MD_CTX * p_ctx;
        //unsigned char * des = malloc(xChunkSize);

        BD_INFO("xContext = 0x%p; xChunkSize = %d\n",xContext,xChunkSize);

        //rtk_rev_bytes(pxMessageChunk,des,xChunkSize);
        rtk_show_data(8,xChunkSize,(void *)pxMessageChunk,0,(unsigned char*)"Show SHA256 data" );

        p_ctx = &(xContext->mcp_ctx);
        kmcpb = (MCP_BUFF*)p_ctx->private_data;

        BD_INFO("p_ctx = 0x%p\n",p_ctx);
        BD_INFO("kmcpb = 0x%p\n",kmcpb);

        if (kmcpb)
        {
            mcpb_purge(kmcpb);

            if (mcpb_tailroom(kmcpb) < xChunkSize)
            {
                if (kmcpb)
                    free_mcpb(kmcpb);

                kmcpb = alloc_mcpb(xChunkSize);

                p_ctx->private_data = (void*) kmcpb;
            }
        }
        else
        {
            kmcpb = alloc_mcpb(xChunkSize);
            p_ctx->private_data = (void*) kmcpb;
            BD_INFO("md_data = 0x%p\n",p_ctx->md_data);
            BD_INFO("private_data = 0x%p\n",p_ctx->private_data);

        }

        if (kmcpb==NULL)
        {
            BDPRINT("[MCP][DGST] WARNING, do dgst update failed, alloc mcpb buffer failed\n");

        }else{
            memcpy((void *) kmcpb->data, (void *)pxMessageChunk, xChunkSize);

            mcpb_put(kmcpb, xChunkSize);
            if(SHA256_DigestUpdate(p_ctx,kmcpb))
            {
                BDPRINT("MCP_DigestUpdate fial\n");
            }else{
                bsdStatus = BSD_NO_ERROR;
            }
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/*
kernel :
vi ./arch/arm/bsp-realtek/mach-rtd298x/mcp/sha256.c +199
./arch/arm/bsp-realtek/mach-rtd298x/mcp/sha256.c:123:int SHA256_DigestFinal()
*/
TBsdStatus  bsdSha256Final (
    TBsdHashContext xContext,
    TUnsignedInt8 * pxMessageDigest )
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    if (xContext==NULL || pxMessageDigest==NULL)
    {
        bsdStatus = BSD_ERROR_INVALID_PARAMETERS;
        BDPRINT("%s fail, , xContext/pxMessageDigest should not be NULL\n",__func__);
    }else{
        MCP_MD_CTX  * p_ctx;

        p_ctx = &(xContext->mcp_ctx);

        if(SHA256_DigestFinal(p_ctx,pxMessageDigest)){
            bsdStatus = BSD_ERROR;
            BDPRINT("%s fail, , xContext/pxMessageDigest should not be NULL\n",__func__);
        }else{
            BDPRINT("%s Success1~~\n",__func__);
            SHA256_DigestCleanup(p_ctx);
            free(xContext);
            BDPRINT("%s Success2~~\n",__func__);
        }
    }

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/* HMAC-SHA-256 */
/* Message Authentication Code ==> MAC */
TBsdStatus  bsdHmacSha256Init (
    const TUnsignedInt8 *   pxKey,
    TSize                   xKeySize,
    TBsdHashContext *       pxContext )
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();
    return bsdStatus;
}


TBsdStatus  bsdHmacSha256Update (
    TBsdHashContext         xContext,
    const TUnsignedInt8 *   pxMessageChunk,
    TSize                   xChunkSize)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}


TBsdStatus  bsdHmacSha256Final (
    TBsdHashContext xContext,
    TUnsignedInt8 * pxMessageDigest)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    BD_INFO("bsdStatus = %s\n",status_tlb[bsdStatus]);
    return bsdStatus;
}

/****************************************************************************/
/*                                                                          */
/* ==================== True Random Number Generator ====================   */
/*                                                                          */
/****************************************************************************/
TBsdStatus  bsdGenerateRandomBytes (
    TSize           xNumOfBytes,
    TUnsignedInt8 * pxRandomBytes )
{
    int i;
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();

    BDPRINT("xNumOfBytes is %u\n",xNumOfBytes);
    rtk_rand_bytes(pxRandomBytes, xNumOfBytes);

    for(i=0;i<xNumOfBytes; i++){
        if(i%16 == 0) BDPRINT("\n");
        BDPRINT("%02x ",pxRandomBytes[i]);
    }
    BDPRINT("\n\n");

    return bsdStatus;
}


/*==========================================================================*/
/* =====  EBSD - Chipset specific extended BSD test harness RPC API   ===== */
/*==========================================================================*/

/****************************************************************************/
/*                                                                          */
/* ==================== Driver Setting  ====================   */
/*                                                                          */
/****************************************************************************/
TBsdStatus nhtBsdInitialize (void)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();
    bsdStatus = bsdInitialize(NULL);

    return bsdStatus;
}


TBsdStatus nhtBsdTerminate (void)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    BDPRINT_FUNC();
    bsdStatus = bsdTerminate(NULL);

    return bsdStatus;
}


TBsdStatus nhtBsdGetBsdProtectingKeyNumber(
    TUnsignedInt32 * pxProtectingKeyNumber)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    *pxProtectingKeyNumber = 1;
    return bsdStatus;

}


TBsdStatus nhtBsdGetSoftwareVersion(
    TBsd20CharsString  xSoftwareVersion )
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    const char tmp20Char[20] = "RTK_BSD_0_0_1";

    BDPRINT_FUNC();

    strcpy((char*)xSoftwareVersion, tmp20Char);
    BD_INFO("xSoftwareVersion = %s\n",xSoftwareVersion);

    //xSoftwareVersion = 'RTK_BSD_0_0_1\0';
    return bsdStatus;
}


TBsdStatus nhtBsdGetCertificationNOCSVersion(
    TUnsignedInt32 * pxVersion)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    BDPRINT_FUNC();

    *pxVersion = BSD_TOOL_VERSION_INT(3,1,0);
    return bsdStatus;
}


TBsdStatus nhtBsdGetChipManufacturerName(
    TBsd20CharsString xChipManufacturerName)
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;

    const char tmp20Char[20] = "Realtek Corp.";

    BDPRINT_FUNC();

    //xChipManufacturerName = 'Realtek Corp.\0';
    strcpy((char*)xChipManufacturerName, tmp20Char);
    BD_INFO("xChipManufacturerName = %s\n",xChipManufacturerName);
    return bsdStatus;
}

#define BSD_CHIP_NAME "SIRIUS"

TBsdStatus nhtBsdGetChipName(
    TBsd20CharsString xChipName )
{
    TBsdStatus bsdStatus = BSD_NO_ERROR;
    const char tmp20Char[20] = "Sirius";

    BDPRINT_FUNC();
    //xChipName = 'Sirius\0';
    strcpy((char*)xChipName, tmp20Char);
    BD_INFO("xChipName = %s\n",xChipName);
    return bsdStatus;
}

#define CONFIG_USE_CA_CERT
#ifndef CONFIG_USE_CA_CERT
TCertFunctionTable* certGetFunctionTable(void)
{
    BDPRINT_FUNC();
    return NULL;
}
#endif

/****************************************************************************/
/*                                                                          */
/* ========= Chipset OS-free harness test RPC communication API =========== */
/*                                                                          */
/****************************************************************************/
//unsigned int read_cnt;
int nht_term_portOpen (void)
{
    BDPRINT_FUNC();
    return 0;
}


#define WAIT_LOOP_10U (4*1000*100)
int nht_term_portRead(
    void * pxBuffer,
    int    xBufferSize)
{
    unsigned int uart_cnt = 0;
    unsigned char* pbsd_buf;
    unsigned int loop;

    pbsd_buf = (unsigned char*)pxBuffer;

    /* wait 4S */
    loop = WAIT_LOOP_10U;
    while(loop--){
        if(rtk_getc(pbsd_buf+uart_cnt,RPC_DEV)){
            uart_cnt++;
        }

        if(uart_cnt ==xBufferSize)
            break;

        udelay(10);
    }

    if(rtk_bsd_state & BSD_SHOW_RPC){
        if(uart_cnt){
            BDPRINT_FUNC();
            loop = 0;
            while(loop < uart_cnt){
                BDPRINT("%x ",*(pbsd_buf+loop));
                loop++;
            }
            BDPRINT("\n");
        }
    }
    return uart_cnt;
}

int nht_term_portWrite(
    const void * pxBuffer,
    int          xBufferSize)
{
    int i;
    unsigned char* pbsd_buf;

    pbsd_buf = (unsigned char*)pxBuffer;

    if(rtk_bsd_state & BSD_SHOW_RPC){
        BDPRINT_FUNC();
        BDPRINT("xBufferSiz=%d; pxBuffer=0x%p(0x%p)\n",
            xBufferSize,pxBuffer,pbsd_buf);

        for(i=0;i<xBufferSize;i++){
            BDPRINT("%x ",pbsd_buf[i]);
        }

        BDPRINT("\n");
    }
    rtkbsd_rpc_puts(pbsd_buf,xBufferSize);

    return xBufferSize;
}



void rtk_print_call_back(const TChar *pxString)
{
    BDPRINT_FUNC();

    if(!pxString)
        BDPRINT_FUNC();
    else{
        if(CON_DEV == UART0_BASE)
            printf1("%s(%d) TEST.....",__func__,__LINE__);
        else
            printf("%s(%d) TEST.....",__func__,__LINE__);
    }
}



void nht_term_register_printout_cbfct  (
    TNhtTerm_printOutCallBack  xStdoutCallBack,
    TNhtTerm_printOutCallBack  xStderrCallBack  )
{
    BDPRINT_FUNC();
    xStdoutCallBack = rtk_print_call_back;
    xStderrCallBack = rtk_print_call_back;
}


/****************************************************************************/
/*                                                                          */
/* ==================== BSD test app interface ====================         */
/*                                                                          */
/****************************************************************************/
#define DSB_API_VERSION "2014/04/15 16:05"
int do_rtkbsd (
    cmd_tbl_t *     cmdtp,
    int             flag,
    int             argc,
    char * const    argv[] )
{
    int ret = CMD_RET_USAGE;


    printf("BSD driver API %s \n",DSB_API_VERSION);
    printf("(build at %s %s)\n",__DATE__,__TIME__);

    if(RPC_PORT == UART0_BASE ){
        printf("Uart0 have been Occupied by BSD RPC. check log at Uart1!!\n");

        BDPRINT("BSD driver API %s \n",DSB_API_VERSION);
        BDPRINT("(build at %s %s)\n",__DATE__,__TIME__);
    }

    ret = 0;
    if( argc >= 2 ) {
        if( strncmp( argv[1], "rpc", 3 ) == 0 ) {
//            read_cnt = 0;
            printf("starting NOXX RPC server..\n");
            BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);

            if(argc>=3){
                if( strncmp( argv[2], "don", 3 ) == 0 ) {
                    rtk_bsd_state |= BSD_SHOW_RPC;
                }
            }
            mcp_init();
            rtk_nagxx_init();
            bsd_startServer(1);
            rtk_bsd_state = 0;
            BD_INFO("rtk_bsd_state=0x%x\n",rtk_bsd_state);

        }else if(strncmp( argv[1], "reset", 5 ) == 0 ){
            BD_INFO("reset test...\n");
            do_reset (NULL, 0, 0, NULL);
        }else{
            goto UNKNOW_CMD;
        }

    }else{
UNKNOW_CMD:
        printf("no support function\n");
    }
    return  ret;
}


U_BOOT_CMD(
    rtkbsd, 5, 0, do_rtkbsd,
    "RTK NOCS BSD test function",
    "          - rtkbsd test\n"
    "rtkbsd rpc\n"
    "  ==> enable NAXXX BSD RPC Server \n"
    "rtkbsd rpc don\n"
    "  ==> display RPC bus data.\n"
    ""
);


#if 0
/*
// informance about BSD
==> unsigned int do_RSA( const unsigned int signature_addr,
                     const unsigned int rsa_key_addr,
                     const unsigned int output_addr );
vi ./arch/arm/cpu/armv7/rtd298x/big_util.c +51


./crypto/rsa/rsa_eay.c:197:     case RSA_PKCS1_PADDING:
./crypto/rsa/rsa_eay.c:378:     case RSA_PKCS1_PADDING:
./crypto/rsa/rsa_eay.c:597:     case RSA_PKCS1_PADDING:
./crypto/rsa/rsa_eay.c:707:     case RSA_PKCS1_PADDING:


static int RSA_eay_public_encrypt(int flen, const unsigned char *from,
             unsigned char *to, RSA *rsa, int padding)
==> i=RSA_padding_add_PKCS1_type_2(buf,num,from,flen);

static int RSA_eay_private_encrypt(int flen, const unsigned char *from,
             unsigned char *to, RSA *rsa, int padding)
==> i=RSA_padding_add_PKCS1_type_1(buf,num,from,flen);

static int RSA_eay_private_decrypt(int flen, const unsigned char *from,
             unsigned char *to, RSA *rsa, int padding)
==> r=RSA_padding_check_PKCS1_type_2(to,num,buf,j,num);

static int RSA_eay_public_decrypt(int flen, const unsigned char *from,
             unsigned char *to, RSA *rsa, int padding)
==> r=RSA_padding_check_PKCS1_type_1(to,num,buf,i,num);


=======================================
測試使用指令
==RSA==
nopadding 編碼
./bsd -rsa -pub -enc -expE 0x11 -modN ./BinIn/rsa_padding_no_padding_pub_enc_n.bin -pad NO -if ./BinIn/rsa_padding_no_padding_pub_enc_in.bin

nopadding 解碼
./bsd -rsa -pub -dec -expE 0x11 -modN ./BinIn/rsa_padding_no_padding_pub_dec_n.bin -pad NO -if ./BinIn/rsa_padding_no_padding_pub_dec_in.bin


==========================================

=== show pxInput ===

c1b77ed52521525f0a4ba341bdaf51d9



=== show pxInitVector ===

1b1ebd1fc45ec43037fd4844241a437f


echo dca44d587fa8a55ee0539dc7e0a8808a | ./RtSSL enc -d -aes_128_cbc -k dc4a3e152818fe95a7df230117b083a1 -iv 0 -i stdin -o stdout
echo c1b77ed52521525f0a4ba341bdaf51d9 | ./RtSSL enc -d -aes_128_cbc -k 0 -iv 1b1ebd1fc45ec43037fd4844241a437f -i stdin -o stdout

=== show pxInput ===

d951afbd41a34b0a5f522125d57eb7c1


=== show pxInitVector ===

7f431a244448fd3730c45ec41fbd1e1b

*/
#endif

