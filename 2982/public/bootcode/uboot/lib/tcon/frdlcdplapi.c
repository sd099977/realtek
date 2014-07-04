/**
 * @file frdlcdplapi.c
 *
 * @brief PlaiceLCD部制御
 *
 * Copyright (c) 2009 SHARP CORPORATION
 *
 * @author 
 */

/* **
 * ** include
 * **/
//@@@@@@@@@@@@@@@@@@@@@@@@
#define TURNKEY1 1
#define printf(...)
#include <common.h>
//@@@@@@@@@@@@@@@@@@@@@@@@
#include <tcon/frdlcdapi.h>
#include <tcon/frdlcdplapi.h>
#include <tcon/frdplapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/

#define FRDLCD_BUG_FIX1/* 起動時映像異常対策 2009.08.20 */

/* RomAddr */
#define LCDPL_ROMADDR_REVISION	0x2F0
#define LCDPL_ROMADDR_UNIFIED_REVISION	0x3FFF0
#define LCDPL_ROMADDR_SBRPARAM	0xC100
#define LCDPL_ROMADDR_GHOSTLUT1	0x2C100
#define LCDPL_ROMADDR_GHOSTLUT2	0x35C80
#define LCDPL_ROMADDR_QSLUT		0x08100
#define LCDPL_ROMADDR_UVLMODE	0x7700
#define LCDPL_ROMADDR_NRMODE	0x1060

#define LCDPL_ROMSIZE_SBRPARAM	0x2000
#define LCDPL_ROMSIZE_GHOSTLUT1	0x09B8
#define LCDPL_ROMSIZE_GHOSTLUT2	272
#define LCDPL_ROMSIZE_QSLUT		0x400
#define LCDPL_ROMSIZE_UVLMODE	0x80
#define LCDPL_ROMSIZE_NRMODE	0x10

/* ROM仕様 */
#define LCDPL_ROMSIZE_TOTAL_8M		0x100000/* 8Mbit */
#define LCDPL_ROMSIZE_TOTAL_2M		0x40000	/* 2Mbit */
#define LCDPL_ROM_PAGE_SIZE_2M		256		/* 2Mbit */

/* ROMステータスレジスタ */
#define LCDPL_ROM_STATUS_WIP		0x01	/* Write In Progress */
#define LCDPL_ROM_STATUS_WEL		0x02	/* Write Enable Latch */
#define LCDPL_ROM_STATUS_BP10		0x0C	/* Block Protect(BP0, BP1) */
#define LCDPL_ROM_STATUS_BP210		0x1C	/* Block Protect(BP0, BP1, BP2) */
#define LCDPL_ROM_STATUS_SRDW		0x80	/* Status Register Write Disable */

#define LCDPL_ROM_BURST_LEN_W		256		/* ROMバーストライト用バッファ(LCDCレジスタ)長 */
#define LCDPL_ROM_BURST_LEN_R		256		/* ROMバーストリード用バッファ(LCDCレジスタ)長 */

/* SPIコマンド定義 */
#define LCDPL_ROM_CMD_WRSR			1		/* ステータスレジスタへの書き込み */
#define LCDPL_ROM_CMD_WRITE			2		/* データ書き込み */
#define LCDPL_ROM_CMD_READ			3		/* データ読み込み */
#define LCDPL_ROM_CMD_WRDI			4		/* 書き込み禁止状態にする */
#define LCDPL_ROM_CMD_RDSR			5		/* ステータスレジスタの読み込み */
#define LCDPL_ROM_CMD_WREN			6		/* 書き込み可能にする */
#define LCDPL_ROM_CMD_SE			0xD8	/* Sector Erase */
#define LCDPL_ROM_CMD_BE			0xC7	/* Bulk Erase */

#define LCDPL_EVA_PTN_NUM_MAX		0x12
#define LCDPL_AGI_PTN_NUM_MAX		0x21

#define LCDPL_I2C_DATA_LEN_MAX 		96		/* I2Cレジスタ転送最大長定義(iic.hでの MAX_DATAS の定義(現状256)による) */


#if 0/* ROMサイズエラーチェックを無効にするときは'1'にする */
#define LCDPL_ROM_SIZE_ERROR_BYPASS
#endif

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
/* static const変数 */
static const dFrdLcdTrnOvr_e aeLcdPlConvTrnOvr[LCDPL_CPWB_DIREC_NUM][FRDLCD_TRN_OVR_NUMMAX] =
{
	{/* 正スキャン配置 */
		FRDLCD_TRN_OVR_NORMAL,
		FRDLCD_TRN_OVR_MIRROR,
		FRDLCD_TRN_OVR_UPSIDE_DOWN,
		FRDLCD_TRN_OVR_ROTATE
	},
	
	{/* 逆スキャン配置 */
		FRDLCD_TRN_OVR_ROTATE,
		FRDLCD_TRN_OVR_UPSIDE_DOWN,
		FRDLCD_TRN_OVR_MIRROR,
		FRDLCD_TRN_OVR_NORMAL
	}
};

/* LCDテストパターン番号テーブル */
static const uint8 aucLcdPlTestPtnTbl[FRDLCD_TESTPTN_NUMMAX] =
{
	0x00,										/* OFF */
	0x05,										/* 白黒横１ライン */
	0x06,										/* 黒白横１ライン */
	0x07,										/* 横グレースケール１ */
	0x08,										/* 横グレースケール２ */
	0x09,										/* 緑（255）ベタ */
	0x0A,										/* 青（255）ベタ */
	0x0B,										/* 赤（255）ベタ */
	0x0C,										/* 白（255）ベタ */
	0x0D,										/* 黒（0）ベタ */
	0x0E,										/* グレー（215）ベタ */
	0x0F,										/* グレー（147）ベタ */
	0x10,										/* グレー（96）ベタ */
	0x11,										/* グレー（60）ベタ */
	0x12,										/* グレー（47）ベタ */
	0x13,										/* フリッカー ＋ bitmap */
	LCDPL_AGI_PTN_NUM_MAX + 0xA,				/* シャドーイングパターン(評価用パターン) */
	0x3,										/* QSテストパターン１ */
	0x4,										/* QSテストパターン２ */
	0x1,										/* フリッカパターン(1H) */
	0x2,										/* フリッカパターン(2H+1) */
	0x14,										/* グレー（30）ベタ */
	0x15,										/* グレー（44）ベタ */
	0x16,										/* グレー（128）ベタ */
	0x17,										/* グレー（168）ベタ */
	0x18,										/* グレー（212）ベタ */
	0x19,										/* 赤（128）ベタ */
	0x1A,										/* 緑（128）ベタ */
	0x1B,										/* 青（128）ベタ */
	0x1D,										/* LMD確認パターン */
	0x1E,										/* 予測OS出力(メモリ出力)モード */
	LCDPL_AGI_PTN_NUM_MAX + 0x1,				/* モノクロ表示 */
	LCDPL_AGI_PTN_NUM_MAX + 0x2,				/* 階調テスト表示 */
	LCDPL_AGI_PTN_NUM_MAX + 0x3,				/* ベタ表示 */
	LCDPL_AGI_PTN_NUM_MAX + 0x4,				/* 縦ストライプ */
	LCDPL_AGI_PTN_NUM_MAX + 0x5,				/* 水平方向グレースケール */
	LCDPL_AGI_PTN_NUM_MAX + 0x6,				/* 垂直方向グレースケール */
	LCDPL_AGI_PTN_NUM_MAX + 0x7,				/* カラーチャート */
	LCDPL_AGI_PTN_NUM_MAX + 0x8,				/* フリッカパターン１ */
	LCDPL_AGI_PTN_NUM_MAX + 0x9,				/* フリッカパターン２ */
	LCDPL_AGI_PTN_NUM_MAX + 0xB,				/* A/D調整用パターン */
	LCDPL_AGI_PTN_NUM_MAX + 0xC,				/* 上下分割ベタ */
	LCDPL_AGI_PTN_NUM_MAX + 0xD,				/* 左右分割ベタ */
	LCDPL_AGI_PTN_NUM_MAX + 0xE,				/* ライン反転用フリッカパターン */
	LCDPL_AGI_PTN_NUM_MAX + 0xF,				/* 砂嵐パターン */
	LCDPL_AGI_PTN_NUM_MAX + 0x10,				/* 1ライン表示パターン(Zucchini) */
	LCDPL_AGI_PTN_NUM_MAX + 0x11				/* 1列表示パターン(Zucchini) */
};

/****************/
/* 映像反転設定 */
/****************/
/* PPDS */
static const uint16 aucLcdPlTrnOvrPpds[10][FRDLCD_TRN_OVR_NUMMAX] = {
/* PNL  0x300 or 0x301 */	{0x00E4, 0xF04E, 0x00E4, 0xF04E},
/* PNL  0x2003or0x200C */	{0x0020, 0x002A, 0x0020, 0x002A},
/* PNL  0x2004or0x200D */	{0x0006, 0x0000, 0x0006, 0x0000},
/* PNL  0x2005or0x200E */	{0x0050, 0x0056, 0x0050, 0x0056},

/* LCDC 0x6A00(AB) */		{0x0081, 0x0081, 0x0083, 0x0083},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0001, 0x0003, 0x0003},
/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
};

/* miniLVDS */
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* 外販パネル */
static const uint16 aucLcdPlTrnOvrMiniL[13][FRDLCD_TRN_OVR_NUMMAX] = {
/* LCDC 0x6400 */			{0x0040, 0x0042, 0x0040, 0x0042},
/* LCDC 0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},

/* LCDC 6404[6]/6504[6] */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 6404[5]/6504[5] */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x6427(AB&414) */	{0x0014, 0x0090, 0x0014, 0x0090},
/* LCDC 0x6428(AB&414) */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 0x6527(CD&414) */	{0x0090, 0x0014, 0x0090, 0x0014},
/* LCDC 0x6528(CD&414) */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
#else
static const uint16 aucLcdPlTrnOvrMiniL[11][FRDLCD_TRN_OVR_NUMMAX] = {
/* LCDC 0x6400 */			{0x0040, 0x0042, 0x0040, 0x0042},
/* LCDC 0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},

/* LCDC 0x6427(AB&414) */	{0x001A, 0x008A, 0x001A, 0x008A},
/* LCDC 0x6428(AB&414) */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 0x6527(CD&414) */	{0x008A, 0x001A, 0x008A, 0x001A},
/* LCDC 0x6528(CD&414) */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
#endif
};

/* static変数 */
static uint8 aucLcdPlRevInfo[FRDLCD_REVISION_DATA_MAX];			/* ROM Revisionデータ保存用配列 */
static uint8 aucLcdPlUnifiedRevInfo[FRDLCD_REVISION_DATA_MAX];	/* ROM Revision(統合)データ保存用配列 */
static dLcdPlRegionAndInchInfo_t tRegionAndInchInfo;/* 仕向け・インチサイズ情報保存用変数 */

static flag				fGetRevInfo		= FALSE;
static flag				fKmBypass		= TRUE;
static dFrdLcdTrnOvr_e	eLcdPlTrnOvr	= FRDLCD_TRN_OVR_NORMAL;
static dFrdInputFreq_e	eLcdPlInputFreq	= FRD_INPUT_FREQ_60HZ;
static uint8			ucLcdPlTemp		= 4;
static uint8			ucLcdPlUvlMode	= 7;
/* 090608 ohashi */
static dFrdLcdPnlSize_e	eLcdPlPnlSize	= FRDLCD_PNL_32;	/* 暫定初期値 */

static dFrdLcdError_t		atLcdPlErrInfo[FRDLCD_ERR_LOG_NUM_MAX];
static uint8				ucLcdPlErrInfoInCnt  = 0;
static uint8				ucLcdPlErrInfoOutCnt = 0;

static uint8			ucLcdPlPnlSizeNo	= 0;/* 8Mbit ROM対応 : 0:32型,  1:40型,  2:46型,  3:52型  */
static uint32			uiLcdPlRomOffset	= 0;/*               : 0x00000, 0x40000, 0x80000, 0xC0000 */
static uint32			uiLcdPlRomSize		= LCDPL_ROMSIZE_TOTAL_8M;

/* **
 * ** prototype
 * **/
static dResult_e eLcdPlChkRomLoadEnd( void );
static void vAddrConv(dFrdLcdPlCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats);
static uint16 usAddrConv(dFrdLcdPlCh_e *peCh, uint16 usAddr);
static dResult_e eLcdPlChkCrcForRomLoad( void );
static dResult_e eLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn , flag fOffset);
static flag fLcdPlRegDepth16bit( uint32 uiAddr );
static dResult_e eLcdPlRomStatusChk( uint16 *pusStatus );
static dResult_e eLcdPlSetTpDat( flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb );
static dResult_e eLcdPlRomToWProtectMode( flag fWPMEn );
static dResult_e eLcdPlGetRegionAndInchInfo( dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo );
static dResult_e eLcdPlSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr );
static dResult_e eLcdPlSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp );
#ifdef DEBUG_LCDPL_MANULOAD_SBR
static void vLcdPlDbgMnl( void );
#endif
static dResult_e eLcdPlGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlGetGhostLut2RomAddr( dFrdLcdPlCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr);
static dResult_e eLcdPlSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucTemp );
static dResult_e eLcdPlGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats );
static dResult_e eLcdPlSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr );
static dResult_e eLcdPlGetUvlModeRomAddr( uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlReloadAll( uint8 ucPnlSizeNo );					/* 8Mbit ROM対応 */
static dResult_e eLcdPlGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr );	/* 8Mbit ROM対応 */
static dResult_e eLcdPlGetNrModeRomAddr( dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlInitSkinCtlLut( void );
dResult_e eFrdLcdPlVerify( uint32 uiRomAddr, uint16 usRegAddr, uint16 usLen );
/* **
 * ** func
 * **/

/*!
********************************************************************************
** @brief	汎用レジスタ連続書込みAPI (LCD側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDats	: 書込みデータ配列(型定義: dFrdRegVar_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRegWs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32 i;
	uint16 tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1
	
	vAddrConv(&eCh, iRegNum, ptDats);
	
#ifdef TURNKEY1
	for( i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDats[0].usAddr + (uint16)i;
		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDats[i].usVal);
		
		if( eResult == S_FAILURE )	break;
	}

#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, iRegNum, ptDats );
	eAdvClose( pvDevice );
#endif //TURNKEY1

	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ連続読込みAPI (LCD側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDats	: 読込みデータ配列(型定義: dFrdRegVar_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRegRs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32		i;
	uint16		tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1

	vAddrConv(&eCh, iRegNum, ptDats);

#ifdef TURNKEY1
	for(  i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDats[0].usAddr + (uint16)i;
		eResult = eI2CRead( IIC_SLV_ADDR_TCON, tmp_addr, &(ptDats[i].usVal));

		if( eResult == S_FAILURE )	break;
	}
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, iRegNum, ptDats);
	eAdvClose( pvDevice );
#endif //TURNKEY1

	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ単一書込みAPI (LCD側)
** @param	usAddr	: アドレス指定	(型定義: uint16)
** @param	usVal	: 書込み値	(型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRegW( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 usVal )
{
	dResult_e		eResult = S_SUCCESS;
#ifdef TURNKEY1	
//TURNKEY1 nothing
#else //TURNKEY1
	const void		*pvDevice;
#endif //TURNKEY1
	dFrdRegVar_t	tData;
	
	tData.usAddr = usAddrConv(&eCh, usAddr);
	tData.usVal  = usVal;

#ifdef TURNKEY1
	eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tData.usAddr, tData.usVal );
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
#endif //TURNKEY1

	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ単一読込みAPI (LCD側)
** @param	usAddr	: アドレス指定	(型定義: uint16)
** @param	pusVal	: 読込み値	(型定義: uint16 *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRegR( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 *pusVal )
{
	dResult_e		eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	const void		*pvDevice;
#endif //TURNKEY1
	dFrdRegVar_t	tData;
	
	if(pusVal == NULL) return S_SPEC_ERROR;
	
	tData.usAddr = usAddrConv(&eCh, usAddr);

#ifdef TURNKEY1
	printf("In eFrdLcdPlRegR, IIC_SLV_ADDR_TCON=%x\r\n",IIC_SLV_ADDR_TCON);
	printf("In eFrdLcdPlRegR, tData.usAddr=%x\r\n",tData.usAddr);
	printf("In eFrdLcdPlRegR, &(tData.usVal)=%x\r\n",&(tData.usVal));
	eResult = eI2CRead( IIC_SLV_ADDR_TCON, tData.usAddr, &(tData.usVal));
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	*pusVal = tData.usVal;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	パネルサイズ設定用API
** @param	ePnlSize	: パネルサイズ設定(型定義: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	必ず eFrdLcdPlChkRomLoadEnd より先に呼ぶこと
*******************************************************************************/
dResult_e eFrdLcdPlSetSize( dFrdLcdPnlSize_e ePnlSize )
{
	dResult_e eResult = S_SUCCESS;
	
	/* オフセット設定 */
	switch( ePnlSize ){
		case FRDLCD_PNL_32:
			ucLcdPlPnlSizeNo = 0;
			break;
		case FRDLCD_PNL_40:
			ucLcdPlPnlSizeNo = 1;
			break;
		case FRDLCD_PNL_46:
			ucLcdPlPnlSizeNo = 2;
			break;
		case FRDLCD_PNL_52:
			ucLcdPlPnlSizeNo = 3;
			break;
		case FRDLCD_PNL_60:
			ucLcdPlPnlSizeNo = 0;
			break;
		default:
			ucLcdPlPnlSizeNo = 0;
			eResult = S_SPEC_ERROR;
			break;
	}
	eLcdPlPnlSize = ePnlSize;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	パネルサイズ設定確認用API
** @param	pePnlSize	: パネルサイズ状態 (型定義: dFrdLcdPnlSize_e *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlGetSize( dFrdLcdPnlSize_e *pePnlSize )
{
	*pePnlSize = eLcdPlPnlSize;
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	ROMロード正常終了チェックAPI
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	必ず eFrdLcdPlSetSize を先に呼ぶこと
*******************************************************************************/
dResult_e eFrdLcdPlChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	dResult_e	eResultTmp;
	
#ifdef FRDLCD_BUG_FIX1/* 起動時映像異常対策 2009.08.20 */
	MDrv_Timer_Delayms(20);
#endif
	
	/* 初回ロードのロード終了確認 */
	eResult |= eLcdPlChkRomLoadEnd();
	
	/* 統合リビジョンの取得 */
	eResultTmp = eLcdPlGetRevInfo( aucLcdPlUnifiedRevInfo, LCDPL_ROMADDR_UNIFIED_REVISION );
	if( aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE] == 0x08 ){
	/* ROM：8Mbitデータ */
		
		/* 8Mbitと判別された時点で、Offset値を設定する */
		uiLcdPlRomOffset = ucLcdPlPnlSizeNo * LCDPL_ROMSIZE_TOTAL_2M;
		
		/* パネルサイズに対応するデータ2MbitをリロードAll */
		eResult |= eLcdPlReloadAll( ucLcdPlPnlSizeNo );
		
		/* ２回目ロードのロード終了確認 */
		eResult |= eLcdPlChkRomLoadEnd();
		
		eResult |= eResultTmp;
		
		uiLcdPlRomSize = LCDPL_ROMSIZE_TOTAL_8M;
	}
	else{
	/* ROMが2Mbitデータ → 初回ロードのみで追加処理は必要無し */
		uiLcdPlRomOffset = 0;
		uiLcdPlRomSize = LCDPL_ROMSIZE_TOTAL_2M;
#ifdef FRDLCD_BUG_FIX1/* 起動時映像異常対策 2009.08.20 */
		/* パネルサイズに対応するデータ2MbitをリロードAll */
		eResult |= eLcdPlReloadAll( 0 );
		
		/* ２回目ロードのロード終了確認 */
		eResult |= eLcdPlChkRomLoadEnd();
#endif
	}
	
	/* サイズ別リビジョンの取得 */
	eResult |= eLcdPlGetRevInfo( aucLcdPlRevInfo, LCDPL_ROMADDR_REVISION );
	
	fGetRevInfo = TRUE;/* サイズ別リビジョン情報の取得済みを示すフラグ */
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM Revisionデータ取得API
** @param	pucRevInfo : Revisionデータを格納する配列のポインタ(型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	配列のサイズは必ず16バイトを確保すること。
*******************************************************************************/
dResult_e eFrdLcdPlGetRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdPlRevInfo[i];
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	ROM Revision 表示用API
** @param	pcRevInfo : Revisionデータ表示用文字列を格納する配列のポインタ(型定義: int8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	配列のサイズは必ず16バイトを確保すること。(文字列は14 or 15文字です)
*******************************************************************************/
dResult_e eFrdLcdPlGetRevStr( int8 *pcRevInfo )
{
	int8 acPanelType[] = "FM";/* FM はMiniLVDSパネル */
	int8 cFrcType;
//sakata20110920 warning_erase	int8 cTestVer = 'T';
	
	if( pcRevInfo == NULL ) return S_SPEC_ERROR;
	
	if( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M ){
	/* 2Mbitデータ */
		if(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4){
		/* MiniLVDS */
		}
		else{
		/* PPDS */
			switch (aucLcdPlRevInfo[FRDLCD_REVISION_PANEL])
			{
				case 0x00: acPanelType[1] = 'S'; break;/* 片出し */
				case 0x01: acPanelType[1] = 'D'; break;/* 両出し */
				default:   acPanelType[1] = '?'; break;/* 不明 */
			}
		}
		switch (aucLcdPlRevInfo[FRDLCD_REVISION_FRC]){
			case 0x00: cFrcType = 'E'; break;/* Easter */
			case 0x01: cFrcType = 'F'; break;/* Fraser */
			case 0x02: cFrcType = 'Y'; break;/* Yellowtail */
			case 0x04: cFrcType = 'A'; break;/* Arugula */
			case 0x05: cFrcType = 'P'; break;/* Plaice */
			default:   cFrcType = '?'; break;/* 不明 */
		}
		if( aucLcdPlRevInfo[FRDLCD_REVISION_VER] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* テストバージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%c%02X",
					aucLcdPlRevInfo[FRDLCD_REVISION_YEAR_L],/* 年 */
					aucLcdPlRevInfo[FRDLCD_REVISION_MONTH],	/* 月 */
					aucLcdPlRevInfo[FRDLCD_REVISION_DAY],	/* 日 */
					acPanelType,							/* パネル駆動方式 */
					cFrcType,								/* T-CONデバイス */
					aucLcdPlRevInfo[FRDLCD_REVISION_INCHI],	/* インチサイズ */
					aucLcdPlRevInfo[FRDLCD_REVISION_MISC],	/* モデル */
					cTestVer,
					aucLcdPlRevInfo[FRDLCD_REVISION_VER] & 0x7F	/* バージョン */
				);
#endif //TURNKEY1
		}
		else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* 正式バージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%02X",
					aucLcdPlRevInfo[FRDLCD_REVISION_YEAR_L],/* 年 */
					aucLcdPlRevInfo[FRDLCD_REVISION_MONTH],	/* 月 */
					aucLcdPlRevInfo[FRDLCD_REVISION_DAY],	/* 日 */
					acPanelType,							/* パネル駆動方式 */
					cFrcType,								/* T-CONデバイス */
					aucLcdPlRevInfo[FRDLCD_REVISION_INCHI],	/* インチサイズ */
					aucLcdPlRevInfo[FRDLCD_REVISION_MISC],	/* モデル */
					aucLcdPlRevInfo[FRDLCD_REVISION_VER]	/* バージョン */
				);
#endif //TURNKEY1
		}
	}
	else{
	/* 8Mbitデータ */
		if( aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* テストバージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%c%02X%02X",
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* 年 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* 月 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* 日 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* 仕向け */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* モデル */
					cTestVer,									/* テストバージョン */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x7F,	/* バージョン番号(H) */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* バージョン番号(L) */
				);
#endif //TURNKEY1
		}
		else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* 正式バージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%02X%02X",
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* 年 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* 月 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* 日 */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* 仕向け */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* モデル */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H],	/* バージョン番号(H) */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* バージョン番号(L) */
				);
#endif //TURNKEY1
		}
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	(統合)ROM Revisionデータ取得API
** @param	pucRevInfo : Revisionデータを格納する配列のポインタ(型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	配列のサイズは必ず16バイトを確保すること。
*******************************************************************************/
dResult_e eFrdLcdPlGetUnifiedRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdPlUnifiedRevInfo[i];
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	初期化設定API(LCD側)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlInit( void )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ROMをライトプロテクトモードへ */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
	/* 仕向け・インチサイズ情報 */
	eResult |= eLcdPlGetRegionAndInchInfo(&tRegionAndInchInfo);
	if(eResult != S_SUCCESS ) return eResult;
	
	/* 色沈み対策 */
	eResult |= eFrdLcdPlChgGamLut(TRUE);
	
	/* 肌色補正LUT書換え (ルビコンの特定ROMまでに対し) */
	if(uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_8M){
		if((aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L] <= 0x09) && (aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH] <= 0x06)){
			eResult |= eLcdPlInitSkinCtlLut();
		}else{
			;;
		}
	}else{
		;;
	}
	
	/* static変数の初期値設定 */
	eLcdPlTrnOvr	= aeLcdPlConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][FRDLCD_TRN_OVR_NORMAL];
	eLcdPlInputFreq	= FRD_INPUT_FREQ_60HZ;
	ucLcdPlTemp		= 4;
	ucLcdPlUvlMode	= 7;
	/* 090519 ohashi: ここで初期化すべきか難しいところ */
	fKmBypass		= TRUE;

#ifdef FRDLCD_BUG_FIX1/* 起動時映像異常対策 2009.08.20 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, 0x87 );/* Gamma LUTへロード */
#endif

	return eResult;
}


/*!
********************************************************************************
** @brief	映像反転設定API
** @param	eTrnOvr : 映像反転指定(型定義: dFrdLcdTrnOvr_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e eResult = S_SUCCESS;
	
	if(eTrnOvr >= FRDLCD_TRN_OVR_NUMMAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eTrnOvr = %d\n", (int8)eTrnOvr);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eTrnOvr = aeLcdPlConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][eTrnOvr];
	
	eResult |= eLcdPlSetTrnOvrReg(eTrnOvr);
	
	eResult |= eLcdPlSetSbr(eTrnOvr, ucLcdPlTemp);
	
	eLcdPlTrnOvr = eTrnOvr;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	映像出力設定API
** @param	fOutEn	: 出力(ON/OFF)設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	PPDS出力ON/OFF制御
*******************************************************************************/
dResult_e eFrdLcdPlSetOutput( flag fOutEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usDatAB, usDatCD;
	flag		fMiniL = (flag)(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	
	if(fMiniL){
	/* miniLVDS */
		/* LS出力Hi-Z解除 (defaultが1でないと解除できない??) */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x2B, 0);
		
		/* ODSデータ出力ミュートON/OFF */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, &usDatAB);
		eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, &usDatCD);
		if(fOutEn){
		/* ミュートOFF(解除) → bit4 を 0 */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, usDatAB & 0xEF);
			eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, usDatCD & 0xEF);
		}else{
		/* ミュートON → bit4 を 1 */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, usDatAB | 0x10);
			eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, usDatCD | 0x10);
		}
	}
	else{
	/* PPDS */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, &usDat);
		if(fOutEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, ((usDat & 0xFFFE) | 1));
		else		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, ((usDat & 0xFFFE) | 0));
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDテストパターン設定API
** @param	eTestPtn : テストパターン番号(型定義: dFrdLcdTestPtn_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetTestPtn( dFrdLcdTestPtn_e eTestPtn )
{
	dResult_e		eResult = S_SUCCESS;
	uint8			ucTestPtn;
	
	if((eTestPtn < FRDLCD_TESTPTN_OFF) || (eTestPtn >= FRDLCD_TESTPTN_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eTestPtn = %d\n", (int8)eTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	ucTestPtn = aucLcdPlTestPtnTbl[eTestPtn];
	
	if(ucTestPtn == 0){
		/* テストパターンOFF */
		eResult |= eFrdLcdPlSetAgingPtn(0);	/* エージング用テストパターンをOFF */
		eResult |= eFrdLcdPlSetEvaPtn(0);		/* 評価用テストパターンをOFF */
	}
	else if(ucTestPtn <= (LCDPL_AGI_PTN_NUM_MAX + LCDPL_EVA_PTN_NUM_MAX)){
		/* テストパターンON */
		
		/* 所望のテストパターンモードに設定 */
		if(ucTestPtn <= LCDPL_AGI_PTN_NUM_MAX){
			/* エージングパターン設定 */
			eResult |= eFrdLcdPlSetAgingPtn(ucTestPtn);
			/* 評価用テストパターンをOFF */
			eResult |= eFrdLcdPlSetEvaPtn(0);
		}else{
			/* 評価用パターン設定 */
			eResult |= eFrdLcdPlSetEvaPtn(ucTestPtn - LCDPL_AGI_PTN_NUM_MAX);
			/* エージング用テストパターンをOFF */
			eResult |= eFrdLcdPlSetAgingPtn(0);
		}
	}
	else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTestPtn = %d\n", (int8)ucTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDエージングパターン設定API
** @param	ucAgingPtn : エージングパターン番号 [0x00-0x21] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetAgingPtn( uint8 ucAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usBmpEnab = 0;
	
	if(ucAgingPtn > LCDPL_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucAgingPtn = %d\n", (int8)ucAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucAgingPtn == 0x13){
	/* ドット反転フリッカ + BITMAP */
		usBmpEnab = 1;/* BitMap表示ビットを立てる */
	}
	
	/* BitMap表示設定 + パターン設定 */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x03, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x03, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	
	if(ucAgingPtn == 3){
	/* QS用テストパターン1 の場合、バーの同期を合わせる為、ここでリセットを行う */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDCリセット */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDCリセット解除 */
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD評価用パターン設定API
** @param	ucEvaPtn : 評価用パターン番号 [0x00-0x11] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetEvaPtn( uint8 ucEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB設定 */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB設定 */
	
	if(ucEvaPtn > LCDPL_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucEvaPtn = %d\n", (int8)ucEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB色)設定 */
	eResult |= eLcdPlSetTpDat(FALSE, LCDPL_AB, &tTpda, &tTpdb);
	eResult |= eLcdPlSetTpDat(FALSE, LCDPL_CD, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS ON/OFF設定API
** @param	fQsEn	: QS ON/OFF設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @param	fYuv	: YUV ON(=TRUE)/OFF(=FALSE)指定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			QS ONの前に、周波数・温度に合ったQS LUTをマニュアルロードしてください。
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetQsEn( flag fQsEn, flag fYuv )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usOsOn=0;
	
	if(fQsEn){
		if(fYuv){
			usOsOn = 0x10;
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x46, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x47, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x48, 0x01);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x46, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x47, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x48, 0x01);
		}else{
			usOsOn = 0x30;
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x46, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x47, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x48, 0x00);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x46, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x47, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x48, 0x00);
		}
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, &usDatCD);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, (usDatAB & 0xCF) | usOsOn);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, (usDatCD & 0xCF) | usOsOn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS半画面ON/OFF設定API
** @param	fLonRoff : 半画面ON/OFF設定, TRUE = 左ON右OFF, FALSE = 左OFF右ON (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			左右反転、上下左右反転 状態の場合、映像とともにQS ON/OFF領域も左右入れ替わります(PPDSの場合)。
**			※miniLVDSの場合、反転処理がQSの前で行われる為、QS設定が反転制御について回りません。
**			  TV仕様としては、映像反転状態のままデモモード はありますが、デモモード状態のまま映像反転 は無い為、
**			  ドライバとしては、前者の場合のみ対応(現在の映像反転状態に応じてQSのON/OFF領域を決める)しています。
** @note
**			RegAddr:0x6408 のbit4 をONしてるのみ
*******************************************************************************/
dResult_e eFrdLcdPlSetQsHalf( flag fLonRoff )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usAB=0, usCD=0;
	
	if(!(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4)){
	/* PPDS(左右反転処理がQSの後ろ) */
		if( fLonRoff == TRUE ){
			usAB = 0x10;
		}
		else{
			usCD = 0x10;
		}
	}
	else{
	/* miniLVDS(左右反転処理がQSの前) */
		switch( eLcdPlTrnOvr ){
			default:
			case FRDLCD_TRN_OVR_NORMAL:
			case FRDLCD_TRN_OVR_UPSIDE_DOWN:
				if( fLonRoff == TRUE ){
					usAB = 0x10;
				}
				else{
					usCD = 0x10;
				}
				break;
			case FRDLCD_TRN_OVR_MIRROR:
			case FRDLCD_TRN_OVR_ROTATE:
				if( fLonRoff == TRUE ){
					usCD = 0x10;
				}
				else{
					usAB = 0x10;
				}
				break;
		}
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, &usDatCD);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, (usDatAB & 0xEF) | usAB);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, (usDatCD & 0xEF) | usCD);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS周波数設定API
** @param	eInputFreq : 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetQsFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult;
	
	if((eInputFreq < FRD_INPUT_FREQ_48HZ) || (eInputFreq >= FRD_INPUT_FREQ_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eInputFreq = %d\n", (int8)eInputFreq);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetQsFreqTemp(eInputFreq, ucLcdPlTemp);
	eLcdPlInputFreq = eInputFreq;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS温度設定API
** @param	ucTemp : 温度指定 [0(低温)-7(高温)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetQsTemp( uint8 ucTemp )
{
	dResult_e eResult;
	
	if(ucTemp > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTemp = %d\n", (int8)ucTemp);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetQsFreqTemp(eLcdPlInputFreq, ucTemp);
	ucLcdPlTemp = ucTemp;
	
	/* 090414 ohashi: 温度(ってかLUT)によって静止画判定の閾値が変更 */
	/* 090414 ohashi: 設定値はまだ暫定 */
	if(ucTemp == 0){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x40, 0x10);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x40, 0x10);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x40, 0x08);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x40, 0x08);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	SBR設定API
** @param	ucTemp : 温度指定 [0(低温)-7(高温)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetSbr( uint8 ucTemp )
{
	dResult_e eResult;
	
	if(ucTemp > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTemp = %d\n", (int8)ucTemp);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetSbr(eLcdPlTrnOvr, ucTemp);
	ucLcdPlTemp = ucTemp;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ連続書込みAPI
** @param	uiAddr		: ROM書込み先アドレス			(型定義: uint32)
** @param	usLength	: 書込みデータ長				(型定義: uint16)
** @param	pucDats	: 書込みデータの先頭ポインタ	(型定義: uint8*)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usBurstLen;
	uint16		usLenToNextPage;
	
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + uiLength) > uiLcdPlRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiLength = %d\n", uiLength);
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* ここまで単なる引数チェック */
	
	/* ライトプロテクトモードを解除 */
	eResult |= eLcdPlRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	while(1){
		if(uiLength > LCDPL_I2C_DATA_LEN_MAX){
			usBurstLen = LCDPL_I2C_DATA_LEN_MAX;
		}
		else if(uiLength > 0){
			usBurstLen = uiLength;
		}
		else{
		/* uiLength == 0 */
			break;
		}
		
		/* 次のページ境界までのバイト数 */
		usLenToNextPage = LCDPL_ROM_PAGE_SIZE_2M - (uiAddr % LCDPL_ROM_PAGE_SIZE_2M);
		
		/* "usBurstLen" がページを跨ぐ場合は、境界までで分割する */
		if(usBurstLen > usLenToNextPage) {
			usBurstLen = usLenToNextPage;
		}
		
		eResult |= eLcdPlRomWs(uiAddr, usBurstLen, pucDats);
		uiAddr += usBurstLen;
		uiLength -= usBurstLen;
		pucDats += usBurstLen;
	}
	/* ライトプロテクトモードへ */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ連続読込みAPI
** @param	uiAddr		: ROM読込み先アドレス			(型定義: uint32)
** @param	usLength	: 読込みデータ長				(型定義: uint16)
** @param	pucDats		: 読込みデータの先頭ポインタ	(型定義: uint8*)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t	atRDats[LCDPL_ROM_BURST_LEN_R];
	uint16			i;
	
	/* ここから単なる引数チェック */
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if(usLength > LCDPL_ROM_BURST_LEN_R){/* 最大転送長 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + usLength) > uiLcdPlRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* ここまで単なる引数チェック */
	
	eResult = eLcdPlRomManualLoad(uiAddr, LCDPL_REGADDR_ETC +0x140, usLength, FALSE, FALSE);
	
	/* データ読み込み */
	atRDats[0].usAddr = LCDPL_REGADDR_ETC +0x140;
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, (int32)usLength, atRDats);
	for(i=0; i<usLength; i++){
		pucDats[i] = (uint8)atRDats[i].usVal;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ消去API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRomErase( void )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fGetRevInfo != TRUE) return S_FAILURE;
	
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0) return S_SPEC_ERROR;/* EEPROMの場合はエラーリターン */
	
	/* ライトプロテクトモードを解除 */
	eResult |= eLcdPlRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
		
	/* 書き込みイネーブルコマンドを発行 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WREN);
	
	/* BE(Bulk Erase)コマンド発行 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_BE);
	
	MDrv_Timer_Delayms(10000);/* Bulk Erase の時間(8Mbit対応で増加) */
	
	/* ライトプロテクトモードへ */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
	return eResult;
}


static	uint8 aucRDats[256];
/*!
********************************************************************************
** @brief	ROMバージョンアップAPI
** @param	pucDats	: ROMデータの先頭ポインタ (型定義: uint8 *)
** @param	fVerify	: ベリファイ設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetVerUp( uint8 *pucDats, flag fVerify )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiTotalLen, uiReadNum, i, j;
	uint32 uiBufLen = 0x100;
	uint8 ucRomSizeR1,ucRomSizeR2,ucRomSizeW1,ucRomSizeW2;
	
	/* Plaiceと判別されていると仮定 */
	
	if(pucDats == NULL) return S_FAILURE;
#if 0
	/* Revision情報取得 */
	if(eFrdLcdPlGetRevInfo(aucLcdPlRevInfo) != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf( 0, "FAIL !! (GetRevInfo)\n" );
#endif //TURNKEY1
		return S_FAILURE;
	}
#endif
#if 0	/* Plaiceは片側固定のため */
	if(pucDats[LCDPL_ROMADDR_REVISION + FRDLCD_REVISION_PANEL] != aucLcdPlRevInfo[FRDLCD_REVISION_PANEL]){
	/* 書こうとしているROMデータ上のパネル駆動方式と、書かれているROMデータ上のパネル駆動方式が異なる場合 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf( 0, "aucRevInfo[FRDLCD_REVISION_PANEL] = %d\n", aucLcdPlRevInfo[FRDLCD_REVISION_PANEL] );
#endif //TURNKEY1
		return S_FAILURE;
	}
#endif
	/* Lcd側初期化 */
	//eResult |= eFrdLcdPlInit();
#if 0/* エラーチェックの後に移動 */
	/* ROM種類(Flash or EEPROM)の判別。ROMに書かれているデータのサイズ別リビジョンを参照 */
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash の場合 → 一旦全消去 */
		eResult |= eFrdLcdPlRomErase();
		if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL!!(RomErase)\n" );
#endif //TURNKEY1
			return eResult;
		}
	}
#endif
	/* データサイズ : 書かれているデータの統合リビジョンを参照 */
	ucRomSizeR1 = aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE];
	/* データサイズ : 書こうとしているデータの統合リビジョンを参照 */
	ucRomSizeW1 = pucDats[LCDPL_ROMADDR_UNIFIED_REVISION + FRDLCD_UNI_REVISION_ROM_SIZE];
	
	/* データサイズ : 書かれているデータのサイズ別リビジョンを参照 */
	ucRomSizeR2 = aucLcdPlRevInfo[FRDLCD_REVISION_ROM_SIZE];
	/* データサイズ : 書こうとしているデータのサイズ別リビジョンを参照 */
	ucRomSizeW2 = pucDats[LCDPL_ROMADDR_REVISION + FRDLCD_REVISION_ROM_SIZE];
#if 1
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf( 0, "ucRomSizeR1 : %0x\n", ucRomSizeR1 );
	eDbgPrintf( 0, "ucRomSizeW1 : %0x\n", ucRomSizeW1 );
	eDbgPrintf( 0, "ucRomSizeR2 : %0x\n", ucRomSizeR2 );
	eDbgPrintf( 0, "ucRomSizeW2 : %0x\n", ucRomSizeW2 );
#endif //TURNKEY1
#endif
	/* 書き込みデータサイズの設定 */
	if( ( ucRomSizeW1 != 0xFF ) && ( ucRomSizeW1 != 0x00 ) ){
		switch(ucRomSizeW1){
		case 0x01:/* 1M */
			uiTotalLen = 0x20000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[1M]\n" );
#endif //TURNKEY1
			break;
		case 0x02:/* 2M */
			uiTotalLen = 0x40000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[2M]\n" );
#endif //TURNKEY1
			break;
		case 0x04:/* 4M */
			uiTotalLen = 0x80000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[4M]\n" );
#endif //TURNKEY1
			break;
		case 0x08:/* 8M */
			uiTotalLen = 0x100000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[8M]\n" );
#endif //TURNKEY1
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL !! (FRDLCD_REVISION_ROM_SIZE):%0x\n", ucRomSizeW1);
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
		}

		if( ucRomSizeR1 != ucRomSizeW1 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
		if( ucRomSizeR2 != ucRomSizeW2 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
	}
	else{
	/* 8Mbitデータではない場合 → 従来リビジョンでデータサイズ判別 */
		/* ROMデータサイズ */
		switch(ucRomSizeW2){
		case 0x05:/* 512K */
			uiTotalLen = 0x10000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[512k]\n" );
#endif //TURNKEY1
			break;
		case 0x10:/* 1M */
			uiTotalLen = 0x20000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[1M]\n" );
#endif //KUKJAKU
			break;
		case 0x20:/* 2M */
			uiTotalLen = 0x40000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[2M]\n" );
#endif //TURNKEY1
			break;
		case 0x40:/* 4M */
			uiTotalLen = 0x80000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[4M]\n" );
#endif //TURNKEY1
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL !! (FRDLCD_REVISION_ROM_SIZE):%0x\n", ucRomSizeW2);
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
		}
		
		if( ucRomSizeR1 != ucRomSizeW1 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
		
		if( ucRomSizeR2 != ucRomSizeW2 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
	}
	
	/* ROM種類(Flash or EEPROM)の判別。ROMに書かれているデータのサイズ別リビジョンを参照 */
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash の場合 → 一旦全消去 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Erase......\n");
#endif //TURNKEY1
		eResult |= eFrdLcdPlRomErase();
		if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL!!(RomErase)\n" );
#endif //TURNKEY1
			return eResult;
		}
	}
	
	/* 書込み */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(0, "Write......\n");
#endif //TURNKEY1
	eResult |= eFrdLcdPlRomWs(0, uiTotalLen, pucDats);
	if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Error (RomWs)\n");
#endif //TURNKEY1
		return eResult;
	}
	
	/* ベリファイ */
	if(fVerify == TRUE){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Verify......\n");
#endif //TURNKEY1
		uiReadNum = (uiTotalLen/uiBufLen);
		
		for(i=0; i<uiReadNum; i++){
			eFrdLcdPlRomRs(i*uiBufLen, uiBufLen, aucRDats);
			for(j=0; j< uiBufLen; j++){
				if(aucRDats[j] != pucDats[j+(uiBufLen*i)]){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
					eDbgPrintf(0, "Verify Error!! at address %0x\n", j+(uiBufLen*i));
					eDbgPrintf(0, "Verify Error!! Write Val = %0x\n", pucDats[j+(uiBufLen*i)]);
					eDbgPrintf(0, "Verify Error!! Read Val =  %0x\n", aucRDats[j]);
#endif //TURNKEY1
					return S_FAILURE;
				}
			}
			uiTotalLen -= uiBufLen;
		}
		
		if(uiTotalLen != 0){
			eFrdLcdPlRomRs(uiReadNum*uiBufLen, uiTotalLen, aucRDats);
			for(j=0; j< uiTotalLen; j++){
				if(aucRDats[j] != pucDats[j+(uiBufLen*uiReadNum)]){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
					eDbgPrintf(0, "Verify Error!! at address %0x\n", j+(uiBufLen*uiReadNum));
					eDbgPrintf(0, "Verify Error!! Write Val =  %0x\n", pucDats[j+(uiBufLen*uiReadNum)]);
					eDbgPrintf(0, "Verify Error!! Read Val =  %0x\n", aucRDats[j]);
#endif //TURNKEY1
					return S_FAILURE;
				}
			}
		}
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1		
		eDbgPrintf(0, "VERIFY SUCCESS!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ, レジスタデータのVerify API
** @param	uiRomAddr	: ROMの先頭アドレス			(型定義: uint32)
** @param	usRegAddr	: レジスタの先頭アドレス	(型定義: uint16)
** @param	usLen		: Verify長					(型定義: uint16)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント:
** @note
********************************************************************************/
dResult_e eFrdLcdPlVerify( uint32 uiRomAddr, uint16 usRegAddr, uint16 usLen )
{
	dResult_e eResult = S_SUCCESS;
	flag f16bit = TRUE, fFail = FALSE;
	uint16	usLimit, usTmp, i;
	uint8	aucRomDat[0x100];
	dFrdRegVar_t atTmp[0x100];
	
	/* 8 or 16bit箇所かの判定 */
	f16bit = fLcdPlRegDepth16bit(usRegAddr);
	
	if(f16bit)	usLimit = 0x80;
	else		usLimit = 0x100;
	
	do{
		
		if(usLen > usLimit)	usTmp = usLimit;
		else				usTmp = usLen;
		
		if(f16bit){
			eResult |= eFrdLcdPlRomRs(uiRomAddr, usTmp*2, aucRomDat);
		}else{
			eResult |= eFrdLcdPlRomRs(uiRomAddr, usTmp, aucRomDat);
		}
		/* 先頭アドレスだけ指定 */
		atTmp[0].usAddr = usRegAddr;
		eResult |= eFrdLcdPlRegRs(LCDPL_AB, usTmp, atTmp);
		
		for(i=0; i<usTmp; i++){
			if(f16bit){
				if((aucRomDat[2*i] <<8 | aucRomDat[2*i+1]) != atTmp[i].usVal){
					/* Read Only */
					/* CTL */
					if(atTmp[i].usAddr == 0x0001){
						;;
#if 0
					/* DMA */
					}else if(atTmp[i].usAddr == 0x0048){
						;;
					/* CGN */
					}else if(atTmp[i].usAddr == 0x00BE){
						;;
					/* EDC */
					}else if(atTmp[i].usAddr == 0x0103){
						;;
					}else if(atTmp[i].usAddr == 0x0113){
						;;
					/* PNL */
					}else if((0x030B <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x030D)){
						;;
					}else if(atTmp[i].usAddr == 0x030F){
						;;
					/* IMC */
					}else if(atTmp[i].usAddr == 0x0630){
						;;
					}else if((0x0638 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0657)){
						;;
					/* CRC */
					}else if((0x0700 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0702)){
						;;
					}else if((0x070A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0789)){
						;;
					/* LCDC(SBR) */
					}else if((0x1030 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1038)){
						;;
					}else if(atTmp[i].usAddr == 0x103C){
						;;
					}else if((0x103D <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x103F)){
						;;
					}else if((0x1730 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1738)){
						;;
					}else if(atTmp[i].usAddr == 0x173C){
						;;
					}else if((0x173D <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x173F)){
						;;
					/* FSB */
					}else if(atTmp[i].usAddr == 0x9000){
						;;
					}else if((0x9002 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x9007)){
						;;
					}else if(atTmp[i].usAddr == 0x9010){
						;;
					}else if((0x9012 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x9029)){
						;;
					/* Write Only */
					/*CTL */
					}else if(atTmp[i].usAddr == 0x0002){
						;;
					/* CRC */
					}else if((0x0790 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x079A)){
						;;
					/* LCDC(SBR) */
					}else if(atTmp[i].usAddr == 0x103C){
						;;
					}else if((0x1080 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x10FF)){
						;;
					}else if(atTmp[i].usAddr == 0x173C){
						;;
					}else if((0x1700 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1CFF)){
						;;
					/* sbr_reg */
					}else if((0x7780 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x77FF)){
						;;
					}else if((0x7F80 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x7FFF)){
						;;
					/* FSB */
					}else if(atTmp[i].usAddr == 0x9010){
						;;
#endif
					/* Not Use */
					/*CTL */
					}else if((0x0003 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x000F)){
						;;
					}else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
						eDbgPrintf(0, "Verify Error [Reg Addr: 0x%x] !!\n", atTmp[i].usAddr);
						eDbgPrintf(0, "Rom: 0x%x,   Reg: 0x%x\n", (aucRomDat[2*i] <<8 | aucRomDat[2*i+1]), atTmp[i].usVal);
#endif //TURNKEY1
						fFail = TRUE;
					}
				}
			}else{
				if(aucRomDat[i] != atTmp[i].usVal){
#if 0
					/* Read Only */
					/* TMGEN */
					if(atTmp[i].usAddr == 0x6A00){
						;;
					}else if(atTmp[i].usAddr == 0x6A05){
						;;
					}else if(atTmp[i].usAddr == 0x6A06){
						;;
					}else if(atTmp[i].usAddr == 0x6A80){
						;;
					}else if(atTmp[i].usAddr == 0x6A85){
						;;
					}else if(atTmp[i].usAddr == 0x6A86){
						;;
					/* FLASHIF */
					}else if(atTmp[i].usAddr == 0x6CEF){
						;;
					/* FRC */
					}else if((0x81DE <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x81E3)){
						;;
					}else if((0x836A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x836D)){
						;;
					}else if((0x8470 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8475)){
						;;
					/* sub8 */
					}else if((0x8801 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x880F)){
						;;
					}else if((0x8820 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x882F)){
						;;
					}else if((0x8838 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x883F)){
						;;
					}else if((0x8854 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x885F)){
						;;
					}else if((0x8867 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x886F)){
						;;
					/* subA */
					}else if((0x8A0A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A0C)){
						;;
					}else if((0x8A27 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A2E)){
						;;
					}else if(atTmp[i].usAddr == 0x8A35){
						;;
					}else if((0x8A39 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A3B)){
						;;
					}else if((0x8A48 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A49)){
						;;
					}else if((0x8A5F <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A68)){
						;;
					/* Write Only */
					/* GMA_LUT */
					}else if((0x2286 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x23C7)){
						;;
					}else if((0x23D2 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x2513)){
						;;
					}else if((0x251E <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x265F)){
						;;
					}else if((0x266A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x27AB)){
						;;
					}else if((0x27B6 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x28F7)){
						;;
					}else if((0x2902 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x2A43)){
						;;
					}else{
#endif
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
						eDbgPrintf(0, "Verify Error [Reg Addr: 0x%x] !!\n", atTmp[i].usAddr);
						eDbgPrintf(0, "Rom: 0x%x,   Reg: 0x%x\n", aucRomDat[i], atTmp[i].usVal);
#endif //TURNKEY1
						fFail = TRUE;
//					}
				}
			}
		}
		
		if(usTmp == usLimit){
			usLen -= usLimit;
			if(f16bit)	uiRomAddr += usLimit*2;
			else		uiRomAddr += usLimit;
			usRegAddr += usLimit;
		}else{
			usLen = 0;
		}
		
	}while(usLen);

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	if((eResult == S_SUCCESS) && (!fFail))	eDbgPrintf(0, "Verify Success !!\n");
	else									eDbgPrintf(0, "Verify Error !!\n");
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	フリーラン設定API (LCD側)
** @param	fFreeEn	: フリーラン設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	T-CON部の強制フリーラン機能を使用します。
*******************************************************************************/
dResult_e eFrdLcdPlSetFreeRun( flag fFreeEn )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fFreeEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x06, 0x07);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x06, 0x07);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x06, 0x06);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x06, 0x06);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMマニュアルロード設定API
** @param	uiRomAddr	: ROMの読込み先アドレス (型定義: uint32)
** @param	uiRegAddr	: レジスタへのロード先アドレス (型定義: uint32)
** @param	usByteLen	: ロード長 (型定義: uint16)
** @param	fCrcEn		: CRC確認, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn )
{
	dResult_e eResult;
	eResult = eLcdPlRomManualLoad(uiRomAddr, uiRegAddr, usByteLen, fCrcEn, TRUE);
	return eResult;
}


/*!
********************************************************************************
** @brief	エラーログ取得用API
** @param	ptError : 調整値 (型定義: dFrdLcdError_t)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 
** @note
********************************************************************************/
dResult_e eFrdLcdPlGetErrInfo( dFrdLcdError_t *ptError )
{
	*ptError = atLcdPlErrInfo[ ucLcdPlErrInfoOutCnt ];
	if( atLcdPlErrInfo[ ucLcdPlErrInfoOutCnt ].ucErrCode != 0 ){
		ucLcdPlErrInfoOutCnt++;
		ucLcdPlErrInfoOutCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	マニュアルロード全パターン実行API(LCDC側)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 
** @note
********************************************************************************/
dResult_e eFrdLcdPlAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i, j;
	
	/* 映像反転、SBR温度設定 */
	for(i=0; i<4; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdLcdTrnOvr_e)i != eLcdPlTrnOvr ) || ( j != ucLcdPlTemp ) ){
				eResult |= eLcdPlSetSbr( (dFrdLcdTrnOvr_e)i, j );
			}
		}
	}
	eResult |= eLcdPlSetSbr( eLcdPlTrnOvr, ucLcdPlTemp );/* 元に戻す */
	
	
	/* QS周波数設定、QS温度設定 */
	for(i=0; i<3; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdInputFreq_e)i != eLcdPlInputFreq ) || ( j != ucLcdPlTemp ) ){
				eResult |= eLcdPlSetQsFreqTemp( (dFrdInputFreq_e)i, j );
			}
		}
	}
	eResult |= eLcdPlSetQsFreqTemp( eLcdPlInputFreq, ucLcdPlTemp );/* 元に戻す */
	
	/* Unveil 強弱設定 */
	for(i=0; i<0xF; i++){
		if( i != ucLcdPlUvlMode ){
			eResult |= eFrdLcdPlSetUvlMode(i);
		}
	}
	eResult |= eFrdLcdPlSetUvlMode(ucLcdPlUvlMode);	/* 元に戻す */
	
	return eResult;
}

#if 0
/*!
********************************************************************************
** @brief	デジタルγ(LCDCガンマ) ON/OFF設定用API
** @param	fGammaEn	: デジタルγ ON/OFF設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			PlaiceよりFR側のためチャネル毎設定がない
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetGammaEn( flag fGammaEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucLcdPlGammaEnBit;
	
	if(fGammaEn)	ucLcdPlGammaEnBit = 0x80;/* ON/OFFは bit7 */
	else			ucLcdPlGammaEnBit = 0x00;
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, (usDat & 0x7F) | ucLcdPlGammaEnBit);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	水平垂直デコント ON/OFF設定用API
** @param	fDecontEn	: デコントON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			PlaiceよりFR側のためチャネル毎設定がない
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetDecontEn( flag fDecontEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fDecontEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x32, 0x0F);
	else			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x32, 0x00);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	クロストーク補正 ON/OFF設定用API
** @param	fCckEn	: クロストーク補正 ON/OFF設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			映像反転時に0x642E, 0x652Eの固定設定を行っているため、本APIは使用できない。
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetCckEn( flag fCckEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD;
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E, &usDatCD);
	usDatAB &= 0x7F;
	usDatCD &= 0x7F;
	
	if(fCckEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x2E, (usDatAB | 0x80));
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_FR_DATAPATH +0x2E, (usDatCD | 0x80));
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x2E, usDatAB);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_FR_DATAPATH +0x2E, usDatCD);
	}
	
	return eResult;
}
#endif


/*!
********************************************************************************
** @brief	LCDエージングパターン設定API (FR部)
** @param	ucFrAgingPtn : エージングパターン番号 [0x00-0x21] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Fr部はAB側, CD側がない
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetFrAgingPtn( uint8 ucFrAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usData, usBmpEnab = 0;
	
	if(ucFrAgingPtn > LCDPL_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucFrAgingPtn = %d\n", (int8)ucFrAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucFrAgingPtn == 0x13){
	/* ドット反転フリッカ + BITMAP */
		usBmpEnab = 1;/* BitMap表示ビットを立てる */
	}
	
	/* BitMap表示設定 + パターン設定 */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x03, &usData);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x03, (usData & 0x40) | (usBmpEnab << 7) | ucFrAgingPtn);
	
	if(ucFrAgingPtn == 3){
	/* QS用テストパターン1 の場合、バーの同期を合わせる為、ここでリセットを行う */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDCリセット */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDCリセット解除 */
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD評価用パターン設定API (FR側)
** @param	ucFrEvaPtn : 評価用パターン番号 [0x00-0x12] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Fr部はAB側, CD側がない
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetFrEvaPtn( uint8 ucFrEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB設定 */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB設定 */
	
	if(ucFrEvaPtn > LCDPL_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucFrFrEvaPtn = %d\n", (int8)ucFrEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucFrEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB色)設定 */
	eResult |= eLcdPlSetTpDat(TRUE, LCDPL_AB, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x05, (usDat & 0x60) | ucFrEvaPtn | usTspatEn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	Unveil ON/OFF設定用API
** @param	fUvlEn : Unveil ON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetUvlEn( flag fUvlEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	if(fKmBypass){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);
		fKmBypass = FALSE;
	}
	
	if(fUvlEn){
		/* 090602 ohashi: Uvlが万が一Bypassになっている場合も考慮して */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, &usTmp);
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, usTmp & 0xFE);
		
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x00, 0);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x00, 1);	/* Unveil Bypass */
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	Unveil 強弱設定用API
** @param	ucUvlMode : Unveil 強弱設定 [0x0(弱)-0xF(強)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			各強度に応じた輝度連動ゲインのパラメーターをMNLします。
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetUvlMode( uint8 ucUvlMode )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
	if(0xF < ucUvlMode){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucUvlMode = %x\n", (uint8)ucUvlMode);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlGetUvlModeRomAddr(ucUvlMode, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);							/* CRC値の転送 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_PCCUVL +0x23, LCDPL_ROMSIZE_UVLMODE, TRUE, TRUE);	/* データの転送 */
	
	ucLcdPlUvlMode = ucUvlMode;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	視野角補正 ON/OFF設定用API
** @param	fBdEn : 視野角補正 ON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			グレースケールに見えるYellow band低減です。
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetBdEn( flag fBdEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fBdEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 1);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 1);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ノイズリダクション モード設定用API
** @param	eNrMode : ノイズリダクション ON/OFF設定 (型定義: dFrdLcdNrMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			欧州向けセットなど、画質の悪い映像ソースのノイズを平滑化します。
**			国内などのディジタルテレビでは使用しないでください。
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetNrMode( dFrdLcdNrMode_e eNrMode )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usTmp;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, &usTmp);
	usTmp &= 0x7F;
	
	switch(eNrMode){
		case FRDLCD_NR_MIN:
		case FRDLCD_NR_MID:
		case FRDLCD_NR_MAX:
			/* パラメータ設定 */
			eResult = eLcdPlGetNrModeRomAddr(eNrMode, &uiRomAddr, &uiCrcAddr);
			
			eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
			eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_FR_DATAPATH +0x60, LCDPL_ROMSIZE_NRMODE, TRUE, TRUE);	/* データの転送 */
			/* ON設定 */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, (usTmp|0x80));
			break;
		case FRDLCD_NR_OFF:
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, usTmp);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ノイズリダクション マスク設定用API
** @param	ucMaskNo	: マスク番号指定 [1-4] (型定義: uint8)
** @param	fMaskEn	: マスク設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @param	ptMaskFrame	: 領域指定 (型定義: dFrdFrame *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetNrMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 ausTmp[4], usTmp, i;
	dFrdRegVar_t atTmp[8];
	
	if((ucMaskNo == 0) || (ucMaskNo > 4))	return S_FAILURE;
	
	/* 領域指定 */
	if(ptMaskFrame != NULL){
		ausTmp[0] = ptMaskFrame->usXPos;
		ausTmp[1] = ptMaskFrame->usYPos;
		ausTmp[2] = ptMaskFrame->usWidth  + ptMaskFrame->usXPos;
		ausTmp[3] = ptMaskFrame->usHeight + ptMaskFrame->usYPos;
		
		/* 090519 ohashi: いまいちな処理 */
		if(ausTmp[0] == 1920) ausTmp[0] -= 1;
		if(ausTmp[1] == 1080) ausTmp[1] -= 1;
		if(ausTmp[2] == 1920) ausTmp[2] -= 1;
		if(ausTmp[3] == 1080) ausTmp[3] -= 1;
		
		if(( 0x77F < ausTmp[2]) ||( 0x437 < ausTmp[3])){
			return S_SPEC_ERROR;
		}
		
		atTmp[0].usVal =  ausTmp[0] & 0xff;
		atTmp[1].usVal = (ausTmp[0] & 0xff00) >> 8;
		atTmp[2].usVal =  ausTmp[1] & 0xff;
		atTmp[3].usVal = (ausTmp[1] & 0xff00) >> 8;
		atTmp[4].usVal =  ausTmp[2] & 0xff;
		atTmp[5].usVal = (ausTmp[2] & 0xff00) >> 8;
		atTmp[6].usVal =  ausTmp[3] & 0xff;
		atTmp[7].usVal = (ausTmp[3] & 0xff00) >> 8;
		
		for(i=0; i<8; i++) atTmp[i].usAddr = LCDPL_REGADDR_FR_DATAPATH +0x40 + 8*(ucMaskNo-1) +i;
		
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, 8, atTmp);
	}
	
	/* ON/OFF設定 */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, &usTmp);
	usTmp &= ~((uint16)(0x01 << (ucMaskNo-1)));
	usTmp |= (uint16)(fMaskEn << (ucMaskNo-1));
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, usTmp);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	PCC 全体ON/OFF設定用API
** @param	fPccEn : PCC 全体ON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccEn( flag fPccEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	if(fKmBypass){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);
		fKmBypass = FALSE;
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, &usTmp);
	usTmp &= 0xFD;
	if(fPccEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, usTmp);
	else		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, (usTmp | 0x02));	/* PCC Bypass */
	
	return eResult;
}


/*!
********************************************************************************
** @brief	PCC 詳細設定用API
** @param	ucColNo		: 領域番号指定 [1-6] (型定義: uint8)
** @param	fColEn		: 指定領域のON/OFF設定 (型定義: flag)
** @param	ptPccParam	: 詳細設定 (型定義: dFrdLcdPlPcc_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			いつでも上位層に公開できるよう子関数にはしない
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccCol( uint8 ucColNo, flag fColEn, dFrdLcdPlPcc_t *ptPccParam )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	/* 一旦バイパス */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 0);
	
	/* 領域ON/OFF設定 */
	if((ucColNo < 1) || (6 < ucColNo)){
		return S_FAILURE;
	}else
	if((1 <= ucColNo) && (ucColNo <= 4)){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, &usTmp);
		usTmp &= ~((uint16)0x01 << (4*(ucColNo-1)));
		usTmp |= (uint16)fColEn << (4*(ucColNo-1));
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, usTmp);
	}else
	if((5 <= ucColNo) && (ucColNo <= 6)){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, &usTmp);
		usTmp &= ~((uint16)0x01 << (4*(ucColNo-5)));
		usTmp |= (uint16)fColEn << (4*(ucColNo-5));
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, usTmp);
	}
	
	/* 詳細設定 */
	if(ptPccParam != NULL){
		
		/* 設定領域の輝度,彩度,色相のON/OFF設定 */
		if(ptPccParam->ptBshEn != NULL){
			/* usTmpを再利用 */
			if((1 <= ucColNo) && (ucColNo <= 4)){
				usTmp &= ~((uint16)0x07 << (1+(4*(ucColNo-1))));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fBriEn) << (1+(4*(ucColNo-1)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fSatEn) << (2+(4*(ucColNo-1)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fHueEn) << (3+(4*(ucColNo-1)));
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, usTmp);
			}else
			if((5 <= ucColNo) && (ucColNo <= 6)){
				usTmp &= ~((uint16)0x07 << (1+(4*(ucColNo-5))));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fBriEn) << (1+(4*(ucColNo-5)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fSatEn) << (2+(4*(ucColNo-5)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fHueEn) << (3+(4*(ucColNo-5)));
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, usTmp);
			}
		}
		
		/* 輝度,彩度,色相の領域設定 */
		if(ptPccParam->ptBshArea != NULL){
			
			/* 輝度の領域設定 */
			if(ptPccParam->ptBshArea->ptBriArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x83 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptBriArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8a +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptBriArea->usDelta);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptBriArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x89 +0x0d*(ucColNo-1),
										 usTmp);
			}
			
			/* 彩度の領域設定 */
			if(ptPccParam->ptBshArea->ptSatArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x86 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptSatArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8c +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptSatArea->usDelta);
				/* inv_center */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptSatArea->usCenter;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x85 +0x0d*(ucColNo-1),
										 usTmp);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptSatArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8b +0x0d*(ucColNo-1),
										 usTmp);
			}
			
			/* 色相の領域設定 */
			if(ptPccParam->ptBshArea->ptHueArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x88 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptHueArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8e +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptHueArea->usDelta);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptHueArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8d +0x0d*(ucColNo-1),
										 usTmp);
			}
		}
		
		/* 輝度,彩度,色相のレベル設定 */
		if(ptPccParam->ptBshLvl != NULL){
			/* 輝度のレベル */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usBriLvl);
			/* 彩度のレベル */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usSatLvl);
			/* 色相のレベル */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usHueLvl);
		}
	}
	/* バイパス解除 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);

	return eResult;
}


/*!
********************************************************************************
** @brief	PCC 各領域のON/OFF設定用API
** @param	ucColNo		: 領域番号指定 [1-6] (型定義: uint8)
** @param	fColEn		: 指定領域のON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			指定領域の輝度,彩度,色相もON/OFFします。
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccColEn( uint8 ucColNo, flag fColEn )
{
	dResult_e			eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshEn_t	tBshEn;
	
	tPcc.ptBshEn	= &tBshEn;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= NULL;
	
	if(fColEn){
		tPcc.ptBshEn->fBriEn	= TRUE;
		tPcc.ptBshEn->fSatEn	= TRUE;
		tPcc.ptBshEn->fHueEn	= TRUE;
	}else{
		tPcc.ptBshEn->fBriEn	= FALSE;
		tPcc.ptBshEn->fSatEn	= FALSE;
		tPcc.ptBshEn->fHueEn	= FALSE;
	}
	eResult = eFrdLcdPlSetPccCol(ucColNo, fColEn, &tPcc);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	指定領域の輝度,彩度,色相 ON/OFF設定用API
** @param	ucColNo		: 領域番号指定 [1-6] (型定義: uint8)
** @param	fBriEn		: 指定領域の輝度ON/OFF設定 (型定義: flag)
** @param	fSatEn		: 指定領域の彩度ON/OFF設定 (型定義: flag)
** @param	fHueEn		: 指定領域の色相ON/OFF設定 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshEn( uint8 ucColNo, flag fBriEn, flag fSatEn, flag fHueEn )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t	tPcc;
	dFrdLcdPlBshEn_t	tBshEn;
	
	tPcc.ptBshEn	= &tBshEn;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= NULL;
	
	tPcc.ptBshEn->fBriEn	= fBriEn;
	tPcc.ptBshEn->fSatEn	= fSatEn;
	tPcc.ptBshEn->fHueEn	= fHueEn;
	
	if((fBriEn == FALSE) && (fSatEn == FALSE) && (fHueEn == FALSE)){
		eResult = eFrdLcdPlSetPccCol(ucColNo, FALSE, &tPcc);
	}else{
		eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	}
	return eResult;
}


/*!
********************************************************************************
** @brief	指定 領域, 色属性の領域設定用API
** @param	ucColNo		: 領域番号指定 [1-6] (型定義: uint8)
** @param	eBsh		: 色領域指定 (型定義: dFrdLcdBsh_e)
** @param	usCenter	: 領域の中心位置			[0x0000-0xFFFF] (型定義: uint16)
** @param	usDelta		: 中心から領域端までの距離	[0x0000-0xFFFF] (型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			事前に指定領域をONしてください。
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshArea( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usCenter, uint16 usDelta )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshArea_t	tBshArea;
	dFrdLcdPlPccArea_t	tTmpArea;
	
	tPcc.ptBshEn	= NULL;
	tPcc.ptBshLvl	= NULL;
	tPcc.ptBshArea	= &tBshArea;
	
	switch(eBsh){
		case FRDLCD_BRI:
			tBshArea.ptBriArea = &tTmpArea;
			tBshArea.ptSatArea = NULL;
			tBshArea.ptHueArea = NULL;
			break;
		case FRDLCD_SAT:
			tBshArea.ptBriArea = NULL;
			tBshArea.ptSatArea = &tTmpArea;
			tBshArea.ptHueArea = NULL;
			break;
		case FRDLCD_HUE:
			tBshArea.ptBriArea = NULL;
			tBshArea.ptSatArea = NULL;
			tBshArea.ptHueArea = &tTmpArea;
			break;
		default:
			return S_FAILURE;
	}
	
	tTmpArea.usCenter = usCenter;
	tTmpArea.usDelta  = usDelta;
	
	eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	指定 領域, 色属性のレベル設定用API
** @param	ucColNo		: 領域番号指定 [1-6] (型定義: uint8)
** @param	eBsh		: 色領域指定 (型定義: dFrdLcdBsh_e)
** @param	usLvl		: 調整レベル (型定義: uint16), 
**						輝度,彩度:	[0x400(0倍)〜0x000(1倍)〜0x3FF(約2倍)], 
**						色相:		[0x400(-180°)〜0x000(0°)〜0x3FF(約180°)]
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
**			事前に指定領域をONしてください。
** @par コメント
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshLvl( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usLvl )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshLvl_t	tBshLvl;
	
	tPcc.ptBshEn	= NULL;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= &tBshLvl;
	
	switch(eBsh){
		case FRDLCD_BRI:
			tPcc.ptBshLvl->usBriLvl = usLvl;
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usSatLvl));
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usHueLvl));
			break;
		case FRDLCD_SAT:
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usBriLvl));
			tPcc.ptBshLvl->usSatLvl = usLvl;
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usHueLvl));
			break;
		case FRDLCD_HUE:
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usBriLvl));
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usSatLvl));
			tPcc.ptBshLvl->usHueLvl = usLvl;
			break;
		default:
			return S_FAILURE;
	}
	
	eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	
	return eResult;
}


/* 2009.06.29 色沈み対策(起動時、映像調整コントラストMAXから抜ける時/出るとき) */
uint8 aucGamDat[] = {
0xA1, 0xFF, 0xA1, 0xA2, 0xFF,
0xA2, 0xA3, 0xFF, 0xA3, 0xA4, 0xFF, 0xA4, 0xA5,
0xFF, 0xA5, 0xA6, 0xFF, 0xA6, 0xA7, 0xFF, 0xA7,
0xA8, 0xFF, 0xA8, 0xA9, 0xFF, 0xA9, 0xAA, 0xFF,
0xAA, 0xAB, 0xFF, 0xAB, 0xAC, 0xFF, 0xAC, 0xAD,
0xFF, 0xAD, 0xAE, 0xFF, 0xAE, 0xAF, 0xFF, 0xAF,
0xB0, 0xFF, 0xB0, 0xB1, 0xFF, 0xB1, 0xB2, 0xFF,
0xB2, 0xB3, 0xFF, 0xB3, 0xB4, 0xFF, 0xB4, 0xB5,
0xFF, 0xB5, 0xB6, 0xFF, 0xB6, 0xB7, 0xFF, 0xB7,
0xB8, 0xFF, 0xB8, 0xB9, 0xFF, 0xB9, 0xBA, 0xFF,
0xBA, 0xBB, 0xFF, 0xBB, 0xBC, 0xFF, 0xBC, 0xBD,
0xFF, 0xBD, 0xBE, 0xFF, 0xBE, 0xBF, 0xFF, 0xC0
};
#define LCDPL_GAM_DATA_SIZE (sizeof(aucGamDat)/sizeof(aucGamDat[0]))
/*!
********************************************************************************
** @brief	Gamma LUT 書き換え用API (色沈み対策 2009.06.29)
** @param	fChgEn		: 書換えON/OFF (型定義: falg)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdPlChgGamLut( flag fChgEn )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atWDats[ LCDPL_GAM_DATA_SIZE ];
	uint8 i;
	
	if( eLcdPlPnlSize != FRDLCD_PNL_40 ) return S_SUCCESS;/* 40型以外は対策不要 */
	if( ( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M ) ||	  /* ルビコン(8bit)以外や、モデルNo=1以降は対策不要 */
		( ( ( aucLcdPlRevInfo[ FRDLCD_REVISION_CPWB ] >> 5 ) & 0x7) != 0 )
		) return S_SUCCESS;
	
	if( fChgEn == TRUE ){
	/* 起動時、映像調整コントラスト:MAXから抜ける時 */
	
	/* 40inchのデジタルγカーブの高階調側を4032（10bit値で1008）にクリップする。
       -> 圧縮誤差が発生した場合でも画素レベルの減少幅を抑えることで、 色沈みノイズが視認されにくくする */
	
		/* Gamma LUTの高階調側を書き換え(R, G, B に同じ値を書く) */
		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usVal = (uint16)aucGamDat[i];
			atWDats[i].usAddr = 0x45A3 + i;/* R */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);
		
		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usAddr = 0x4BA3 + i;/* G */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);

		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usAddr = 0x51A3 + i;/* B */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);
	}
	else{
	/* 映像調整コントラスト:MAXの時 -> デフォルトLUT値をリロード */
		eResult |= eLcdPlRomManualLoad(0xD6, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
		eResult |= eLcdPlRomManualLoad(0x5B00, LCDPL_REGADDR_FR_GAMLUTR, 0x1200, TRUE, TRUE);
	}
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, 0x87 );/* Gamma LUTへロード */
	
	return eResult;
}


/**
 * @brief	ロード終了確認用子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdPlChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucTimeOutCnt = 0;
	
	while(1){
		/* ROMロード終了ビットの確認 */
		eResult = eFrdLcdPlRegR(LCDPL_AB, 0x01, &usDat);
		/* ROM load endの確認 */
		if((eResult == S_SUCCESS) && ((usDat & 0x04) == 0x04)){
			break;
		}
		
		ucTimeOutCnt++;
		if(ucTimeOutCnt > 15){
		/* 16回(16×15[ms])まわしてもダメな場合、失敗とみなします */
			eResult |= S_FAILURE;
			break;
		}
		MDrv_Timer_Delayms(15);
	}
	
	if(eResult == S_SUCCESS){
	/* CRC ERRORビットの確認 */
		eResult |= eLcdPlChkCrcForRomLoad();
	}
	
	return eResult;
}


/**
 * @brief	チャネルによるアドレス変換子関数(上位)
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static void vAddrConv(dFrdLcdPlCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats)
{
	uint32 i;
	if(*peCh == LCDPL_CD){
		for(i=0; i<iRegNum; i++){
			*peCh = LCDPL_CD;/* 下記関数内で"LCDPL_AB"に書き換えられてしまう為、都度元に戻します */
			ptDats[i].usAddr = usAddrConv(peCh, ptDats[i].usAddr);
		}
	}
	return;
}


/**
 * @brief	チャネルによるアドレス変換子関数(下位)
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static uint16 usAddrConv(dFrdLcdPlCh_e *peCh, uint16 usAddr)
{
	if(*peCh == LCDPL_CD){
		if(usAddr < 0x1000){
		}
		else if(usAddr < 0x2000){
		/* LCDC(SBR) */
			if((usAddr >= 0x1000) && (usAddr < 0x1080)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x1100) && (usAddr < 0x1700)){
				usAddr += 0x600;
			}
		/* LCDC(CCK)は新規 */
			else if((usAddr >= 0x1D00) && (usAddr < 0x1DC0)){
				usAddr += 0xC0;
			}
			else if((usAddr >= 0x1E80) && (usAddr < 0x1F40)){
				usAddr += 0xC0;
			}
		}
		else if(usAddr < 0x4000){
		}
		else if(usAddr < 0x6000){
		}
		else if(usAddr < 0x8000){
			if((usAddr >= 0x6400) && (usAddr < 0x6500)){
				usAddr += 0x100;
			}
			else if((usAddr >= 0x6600) && (usAddr < 0x6800)){
				usAddr += 0x200;
			}
			else if((usAddr >= 0x6A00) && (usAddr < 0x6A80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x6B00) && (usAddr < 0x6B80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x6F00) && (usAddr < 0x6F80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x7000) && (usAddr < 0x7800)){
				usAddr += 0x800;
			}
		}
		else if(usAddr < 0xC000){
			if((usAddr >= 0xA000) && (usAddr < 0xB000)){
				usAddr += 0x1000;
			}
		}
		*peCh = LCDPL_AB;
	}/* if(*peCh == LCDPL_CD) */
	
	return usAddr;
}


/**
 * @brief	ROM LOAD CRCチェック子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdPlChkCrcForRomLoad( void )
{
	dResult_e		eResult = S_SUCCESS;
	uint16			usDat;
	dFrdRegVar_t	atDats[8];
	uint8			i, j;
#if 0	/* 090423 ohashi: 既にアドレス0x01にて確認している */	
	/* int_crc_error[3]: EEPROM CRCエラー(全体のCRCチェック) */
	eResult = eFrdLcdPlRegR(LCDPL_AB, 0x01, &usDat);
	if(eResult == S_SUCCESS){
	/* ここはPlaice新規なので、エラーログの記載なし */
		if((usDat & 0x08) == 0x08){
			eResult = S_FAILURE;
		}
	}
#endif	
	/* reg_load_error_flag[63:0] : 各ローダーのCRCエラー */
	atDats[0].usAddr = LCDPL_REGADDR_ETC + 0x20;
	
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, 8, atDats);
	if(eResult == S_SUCCESS){
		for(i=0; i<8; i++){
			if(atDats[i].usVal != 0){
			/* エラーの場合、ログを残す */
				for(j=0; j<8; j++){
					if(atDats[i].usVal & (1<<j)){
						eLcdPlSetErrLog(2, i*8+j, 0); /* ucErrCode, ucErrBlock, usAddr */
					}
				}
				eResult = S_FAILURE;
			}
		}
	}
	
	/* init_load_error_flag[0] : HeaderのCRCエラー */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x28, &usDat);
	if(eResult == S_SUCCESS){
		if((usDat & 0x01) == 0x01){
		/* エラーの場合、ログを残す */
			eLcdPlSetErrLog(1, 0, 0); /* ucErrCode, ucErrBlock, usAddr */
			return S_FAILURE;
		}
	}
	
	return eResult;
}


/**
 * @brief	ROMマニュアルロード用子関数
 * @param	uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn, flag fOffset )
{
	dResult_e		eResult = S_SUCCESS;
	flag			f16bit;
	uint16			usWordLen;
	dFrdRegVar_t	atSetUpDats[6];
	uint8 			ucParam = 0;
	uint16			usRDat;
	uint8			ucCnt = 0;

	f16bit = fLcdPlRegDepth16bit(uiRegAddr);
	if(f16bit)	usWordLen = (usByteLen >> 1);
	else		usWordLen =  usByteLen;
	
	eResult = eLcdPlRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if( fOffset ) uiRomAddr += uiLcdPlRomOffset;				/* ROM 8Mbit対応 */
	
	/* ロード元ROMアドレスの設定 */
	atSetUpDats[0].usVal = (uint16)((uiRomAddr >> 8) & 0xFF);	/* ROMアドレス中位[15:8] */
	atSetUpDats[1].usVal = (uint16)(uiRomAddr & 0xFF);			/* ROMアドレス下位[7:0]  */
	atSetUpDats[0].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x10);	/* レジスタアドレス設定 */
	atSetUpDats[1].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x11);	/* レジスタアドレス設定 */

	/* ロード先レジスタアドレスの設定 */
	atSetUpDats[2].usVal = (uint16)((uiRegAddr >> 8) & 0xFF);	/* ロード先レジスタアドレス上位[15:8]  */
	atSetUpDats[3].usVal = (uint16)(uiRegAddr & 0xFF);			/* ロード先レジスタアドレス下位[7:0] */
	atSetUpDats[2].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x12);	/* レジスタアドレス設定 */
	atSetUpDats[3].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x13);	/* レジスタアドレス設定 */

	/* ロードデータ長の設定 */
	atSetUpDats[4].usVal = (uint16)((usWordLen >> 8) & 0xFF);	/* データ長上位[15:8]  */
	atSetUpDats[5].usVal = (uint16)(usWordLen & 0xFF);			/* データ長下位[7:0] */
	atSetUpDats[4].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x14);	/* レジスタアドレス設定 */
	atSetUpDats[5].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x15);	/* レジスタアドレス設定 */

	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 6, atSetUpDats);		/* レジスタへの書き込み */

	/* マニュアルロードVフェッチOFF */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x3f, &usRDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3f, (usRDat | 1));

	/* ロードスタートbitを一旦ゼロに */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x17, 0);

	ucParam |= ((f16bit << 1) | (fCrcEn << 2));

	/* ROMアドレス上位[19:16] + CRC Enable/Disable + bit幅(8bit or 16bit) + ロードスタートビット */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x17, ((uiRomAddr >> 12) & 0xF0) | ucParam | 1);

	/* ビジーチェック */
	while(1){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC+0x2A, &usRDat);
		if((usRDat & 1) == 1){
//			eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] MANUAL LOAD BUSY COUNT = %d\n", ucCnt);
			break;/* 立っていればビジーでない */
		}
		ucCnt++;
		if(ucCnt > 100){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] MANUAL LOAD ERROR !!!!!\n");
#endif //TURNKEY1
			break;
		}
		MDrv_Timer_Delayms(1);
	}
	
	/* 転送エラー(CRCエラーなど)チェック */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC+0x29, &usRDat);
	if(usRDat & 1){
	/* エラーの場合、ログを残す */
		eLcdPlSetErrLog( 3, 0, (uint16)uiRegAddr ); /* ucErrCode, ucErrBlock, usAddr */
		eResult = S_FAILURE;
	}
	
	return eResult;
}


/**
 * @brief	レジスタデータ幅判定子関数
 * @param	uint32 uiAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static flag fLcdPlRegDepth16bit( uint32 uiAddr )
{
	flag f16bit = TRUE;/* 初期値：16bit幅 */
	
	/* 090409 ohashi追加 */
	if((uiAddr >= LCDPL_REGADDR_OSD) && (uiAddr < LCDPL_REGADDR_IMC)){
	/* 0x400-0x600 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if((uiAddr >= LCDPL_REGADDR_PPDS) && (uiAddr < LCDPL_REGADDR_SBRPARAM)){
	/* 0x2000 - 0x7000 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if( (uiAddr >= PL_REGADDR_FRC) && (uiAddr < LCDPL_REGADDR_FSB) ){
	/* 0x8000 - 0x9000 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if( (uiAddr >= LCDPL_REGADDR_BDLUT) && (uiAddr < 0xC000) ){
	/* 0xA000 - 0xC000 */
		f16bit = FALSE;/* 8bit幅 */
	}
	
	return f16bit;
}


/**
 * @brief	ROMへのアクセス時のSTATUSチェック子関数
 * @param	uint16 *pusStatus
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdPlRomStatusChk( uint16 *pusStatus )
{
	uint16	  usStatus;
	uint16	  usWaitCnt = 0;
	dResult_e eResult = S_SUCCESS;
	
	while(1){
		/* ステータスレジスタ読み込みコマンドを発行 */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_RDSR);
		
		/* ROM → LCDCレジスタ の読み出し時間は、EEPCLK(4.6MHz)で16clk程度(4us程度)なので
		   ここでWaitは入れなくてもレジスタ値は確定しています */
		
		/* ステータスレジスタの読み込み */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x35, &usStatus);
		if((usStatus & 0x01) != 0){/*ROM書き込み中か否か*/
			usWaitCnt++;
			if(usWaitCnt == 100){
				eResult = S_FAILURE;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
				eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM ACCESS TIMEOUT ERROR!!!!!!!!\n");
#endif //TURNKEY1
				break;
			}
			MDrv_Timer_Delayms(1);/* 書き込み中の為、Waitを入れます */
		}
		else{
			break;
		}
	}

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM STATUS REGISTER = %0x\n", usStatus);
#endif //TURNKEY1

	if(pusStatus != NULL){
		*pusStatus = usStatus;
	}
	return eResult;
}


/**
 * @brief	TPDA, TPDB 設定用子関数
 * @param	flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdPlSetTpDat( flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdRegVar_t	atDats[12];
	
	if(fFr)	atDats[0].usAddr = LCDPL_REGADDR_FR_DATAPATH + 0xD;
	else	atDats[0].usAddr = LCDPL_REGADDR_DATAPATH + 0xD;
	
	if((ptTpda == NULL) && (ptTpdb == NULL)) return S_SPEC_ERROR;
	
	/* 現状の値を取得 */
	eResult |= eFrdLcdPlRegRs(eCh, 12, atDats);
	
	/* TPDA設定 */
	if(ptTpda != NULL){
		/* 該当場所だけ変更 */
		atDats[0].usVal = (ptTpda->iTPDAR & 0xFF);
		atDats[1].usVal = (atDats[1].usVal & 0xFC) | ((ptTpda->iTPDAR >> 8) & 0x3);
		atDats[2].usVal = (ptTpda->iTPDAG & 0xFF);
		atDats[3].usVal = (atDats[3].usVal & 0xFC) | ((ptTpda->iTPDAG >> 8) & 0x3);
		atDats[4].usVal = (ptTpda->iTPDAB & 0xFF);
		atDats[5].usVal = (atDats[5].usVal & 0xFC) | ((ptTpda->iTPDAB >> 8) & 0x3);
	}
	
	/* TPDB設定 */
	if(ptTpdb != NULL){
		/* 該当場所だけ変更 */
		atDats[6].usVal  = (ptTpdb->iTPDAR & 0xFF);
		atDats[7].usVal  = (atDats[7].usVal & 0xFC) | ((ptTpdb->iTPDAR >> 8) & 0x3);
		atDats[8].usVal  = (ptTpdb->iTPDAG & 0xFF);
		atDats[9].usVal  = (atDats[9].usVal & 0xFC) | ((ptTpdb->iTPDAG >> 8) & 0x3);
		atDats[10].usVal = (ptTpdb->iTPDAB & 0xFF);
		atDats[11].usVal = (atDats[11].usVal & 0xFC) | ((ptTpdb->iTPDAB >> 8) & 0x3);
	}
	
	/* 書き込み */
	eResult |= eFrdLcdPlRegWs(eCh, 12, atDats);
	
	return eResult;
}


/**
 * @brief	ROMライトプロテクトモード有効/無効切り替え子関数
 * @param	flag fWPMEn
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdPlRomToWProtectMode( flag fWPMEn )
{
	uint16		usStatus;
	uint16		usBP, usData;
	dResult_e	eResult = S_SUCCESS;
	
	eResult |= eLcdPlRomStatusChk(&usStatus);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if((usStatus & LCDPL_ROM_STATUS_SRDW) != 0){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM SRDW BIT HI!!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	if( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M )	usBP = LCDPL_ROM_STATUS_BP10;	/* 2MbitROMデータの場合 */
	else  											usBP = LCDPL_ROM_STATUS_BP210;	/* 8MbitROMデータの場合 */
	
	if(fWPMEn == TRUE)	usData = usBP;	/* プロテクト設定 */
	else				usData = 0;		/* プロテクト解除設定 */
	
	if((usStatus & usBP) != usData){
	/* 所望の状態でない場合 */
		
		/* 書き込みデータをレジスタに設定 */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x40, usData);	/* WDATA_START */
		
		/* データ長を設定(念の為。。。) */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x36, 1);		/* LENGTH_L */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x37, 0);		/* LENGTH_H */

		/* 書き込みイネーブルコマンドを発行 */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WREN);

		/* ステータスレジスタ書き込みコマンドを発行 */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WRSR);
	}
	else{
	/* 所望の状態なので、何もしません */
	}
	
	eResult |= eLcdPlRomStatusChk(&usStatus);
	
	return eResult;
}


/**
 * @brief	仕向け・インチ別設定子関数
 * @param	dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	eFrdLcdPlGetRevInfo()を必ず先にコールしてください．
 * @memo	インチ毎にROM管理を行う予定なので、本子関数は基本的に仕向け毎設定です．
 */
static dResult_e eLcdPlGetRegionAndInchInfo( dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo )
{
	uint8 ucPnlSize = aucLcdPlRevInfo[FRDLCD_REVISION_INCHI];
	
	if(fGetRevInfo != TRUE) return S_FAILURE;

	switch(ucPnlSize){
		case 0x32:
		case 0x37:
		case 0x42:
		case 0x60:
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
			break;
		case 0x52:
#if (PL_REGION_INFO == PL_RIGION_US2)
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
			/* 090706 ohashi: Gdelay設定(52"正スキャン EMI対策) */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x41, 0x0c);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x43, 0x0a);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x45, 0x08);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x47, 0x06);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x49, 0x04);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4b, 0x02);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4d, 0x00);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4f, 0x00);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x51, 0x02);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x53, 0x04);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x55, 0x06);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x57, 0x08);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x59, 0x0a);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x5b, 0x0c);
#elif (PL_REGION_INFO == PL_RIGION_AS2)	/* 外販パネル */
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
#else
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
#endif
			break;
		case 0x40:
		case 0x46:
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* 外販パネル */
#ifdef TURNKEY1

			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;

#else //TURNKEY1
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
#endif //TURNKEY1
#else
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
#endif
			break;
		case 0x65:
			ptRegionAndInchInfo->eCpwbDirec = LCDPL_CPWB_DIREC_NORMAL;
			break;
		default:
			ptRegionAndInchInfo->eCpwbDirec = LCDPL_CPWB_DIREC_NORMAL;
			return S_FAILURE;
	}
	
	return S_SUCCESS;
}


/**
 * @brief	上下左右反転設定子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTmp1, usTmp2, usBit12 = 0x1000;
	flag		fMiniL = (flag)(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	/* 090612 ohashi */
	uint16		ausTmp[4];
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* 外販パネル */
	uint16		ausTmp2[2];
	uint8 i;
#endif
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,&ausTmp[0]);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,&ausTmp[1]);
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,&ausTmp[2]);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,&ausTmp[3]);
	ausTmp[0] &= 0xFFDF;
	ausTmp[1] &= 0xFFDF;
	ausTmp[2] &= 0xFF7F;
	ausTmp[3] &= 0xFF7F;
	
	if(fMiniL == FALSE){
	/* PPDS */
		/* 0x0302 のbit12が "0" → ページ２(0x301, 0x200C, 0x200D, 0x200E)のデータを書き換えてからスワップ(bit12を 1 に)
		                    "1" → ページ１(0x300, 0x2003, 0x2004, 0x2005)                    〃          (bit12を 0 に) */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PNL +0x02, &usDat);
		
		if((usDat & usBit12) == 0){
			usTmp1 = 0x01;	/* → ページ2使用 */
			usTmp2 = 0x0C;
		}else{
			usTmp1 = 0x00;	/* → ページ1使用 */
			usTmp2 = 0x03;
		}
		
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PNL  +usTmp1,		aucLcdPlTrnOvrPpds[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+0,	aucLcdPlTrnOvrPpds[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+1,	aucLcdPlTrnOvrPpds[2][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+2,	aucLcdPlTrnOvrPpds[3][eTrnOvr]);
		
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrPpds[4][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrPpds[5][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrPpds[6][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrPpds[7][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrPpds[8][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrPpds[9][eTrnOvr] << 7) | ausTmp[3]));
		/* ページスワップ */
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PNL +0x02, ((usDat & ~usBit12) | (usTmp1<<12)));

	}else{
	/* miniLVDS */
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* 外販パネル */
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x00,	aucLcdPlTrnOvrMiniL[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[2][eTrnOvr]);
		
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, &ausTmp2[0]);
		eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, &ausTmp2[1]);
		for(i=0; i<2; i++){
			ausTmp2[i] &= 0x9f;
			ausTmp2[i] |= aucLcdPlTrnOvrMiniL[3][eTrnOvr] << 6;
			ausTmp2[i] |= aucLcdPlTrnOvrMiniL[4][eTrnOvr] << 5;
		}
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, ausTmp2[0]);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, ausTmp2[1]);
		
		/* MiniLVDS Output CH が 414 の場合のみ */
		if((aucLcdPlRevInfo[12] & 0x03) == 0x01){
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[5][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[6][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[7][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[8][eTrnOvr]);
		}
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[9][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[10][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[11][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[12][eTrnOvr] << 7) | ausTmp[3]));
#else
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x00,	aucLcdPlTrnOvrMiniL[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[2][eTrnOvr]);
		/* MiniLVDS Output CH が 414 の場合のみ */
		if((aucLcdPlRevInfo[12] & 0x03) == 0x01){
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[3][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[4][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[5][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[6][eTrnOvr]);
		}
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[7][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[8][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[9][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[10][eTrnOvr] << 7) | ausTmp[3]));
#endif
	}
	
	return eResult;
}


/**
 * @brief	SBR設定子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	ソースブロック反転(SBR)に関連するパラメータ(SBR PARAM, SBR GHOST LUT1, LUT2, CCK LUT)
 *          の切り替えをマニュアルロードで行います。
 */
static dResult_e eLcdPlSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr, uiCrcAddr;
//	dFrdRegVar_t atDats[3] = {{0x161B, 0x1}, {0x161C, 0x1}, {0x161D, 0x0}};/* SBR GHOST LUT UPDATE用 */
	dFrdRegVar_t atDats[3] = {{0x165d, 0x1}, {0x165e, 0x1}, {0x165f, 0x0}};/* SBR GHOST LUT UPDATE用 */
	
	/* SBR PARAM */
	eResult |= eLcdPlGetSbrParamRomAddr(eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBRPARAM +0x00, LCDPL_ROMSIZE_SBRPARAM, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	/* SBR GHOST LUT1 */
	eResult |= eLcdPlGetGhostLut1RomAddr(eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* → AB側 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x100, LCDPL_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* → CD側(AB側と同じデータ。よってCRC値も同じ) */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x700, LCDPL_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	/* SBR GHOST LUT2(→ AB側) */
	eResult |= eLcdPlGetGhostLut2RomAddr(LCDPL_AB, eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* 090416 ohashi: SIZE-10でいいのかまだ不明 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x5DA, LCDPL_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* SBR GHOST LUT2(→ CD側) */
	eResult |= eLcdPlGetGhostLut2RomAddr(LCDPL_CD, eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* 090416 ohashi: SIZE-10でいいのかまだ不明 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0xBDA, LCDPL_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* SBR GHOST LUT UPDATE */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 3, atDats);
	eResult |= eFrdLcdPlRegWs(LCDPL_CD, 3, atDats);

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	return eResult;
}

#ifdef DEBUG_LCDPL_MANULOAD_SBR
/**
 * @brief	MNLデバッグ出力子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static void vLcdPlDbgMnl( void )
{
	uint16 usReadData;
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] CRC_EXP_VAL  = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x2B, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] CRC_CALC_VAL = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x29, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] ERROR BIT    = %0x\n", usReadData);
#endif //TURNKEY1
	return;
}
#endif

/**
 * @brief	SBR PARAMマニュアルロード用子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_SBRPARAM;
	uint32		uiCrcAddr	= 0x210;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += (LCDPL_ROMSIZE_SBRPARAM * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_SBRPARAM * ucTemp);
	uiCrcAddr += ucTemp;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT1マニュアルロード用子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_GHOSTLUT1;
	uint32		uiCrcAddr	= 0x230;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ( LCDPL_ROMSIZE_GHOSTLUT1 * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_GHOSTLUT1 * ucTemp);
	uiCrcAddr += ucTemp;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT2マニュアルロード用子関数
 * @param	dFrdLcdArCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetGhostLut2RomAddr( dFrdLcdPlCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr)
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_GHOSTLUT2;
	uint32		uiCrcAddr	= 0x240;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_NORMAL:
			break;
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
			uiRomAddr +=  (LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8);
			uiCrcAddr += (2*8);
			break;
		case FRDLCD_TRN_OVR_MIRROR:
			uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8) * 2);
			uiCrcAddr += ((2*8) * 2);
			break;
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8) * 3);
			uiCrcAddr += ((2*8) * 3);
			break;
		default:
			break;
	}
	
	uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * ucTemp) + (LCDPL_ROMSIZE_GHOSTLUT2 * eCh));
	uiCrcAddr += ((2 * ucTemp) + eCh);
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	QS 周波数、温度設定用子関数
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucTemp
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucTemp )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] QS FREQ = %0d\n", eInputFreq);
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] QS TEMP = %0d\n", ucTemp);
#endif //TURNKEY1

	eResult = eLcdPlGetQsLutRomAddr(eInputFreq, ucTemp, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);						/* CRC値の転送 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_QSLUT +0x00, LCDPL_ROMSIZE_QSLUT, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDPL_MANULOAD_QS
	vLcdPlDbgMnl();
#endif

	return eResult;
}


/**
 * @brief	QS LUTマニュアルロード用子関数
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_QSLUT;
	uint32		uiCrcAddr	= 0x200;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_60HZ:
			uiRomAddr += (LCDPL_ROMSIZE_QSLUT * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_QSLUT * ucTemp);
	uiCrcAddr += ucTemp;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	エラーログ設定用子関数
 * @param	uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usCrcCal, usCrcExp;
	
	if( ucErrCode == 1 ){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x06, &usCrcExp);/* CRC期待値(ヘッダロード時) */
	}
	else{
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usCrcExp);/* CRC期待値(マニュアルロード時) */
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x2B, &usCrcCal);/* CRC演算値 */
	
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucErrCode		= ucErrCode;		/* エラーコード  */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucErrBlock	= ucErrBlock;		/* ロードエラーブロック番号 */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].usAddr		= usAddr;			/* 対応レジスタアドレス */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucCrcExp		= (uint8)usCrcExp;	/* CRC期待値 */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucCrcCal		= (uint8)usCrcCal;	/* CRC演算値 */
	
	ucLcdPlErrInfoInCnt++;
	ucLcdPlErrInfoInCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	
	return eResult;
}


/**
 * @brief	ROM書き込み用子関数
 * @param	uint32 uiAddr, uint16 usLength, uint8 *pucDats
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats )
{
	dResult_e		eResult;
	dFrdRegVar_t	atSetUpDats[4];
	dFrdRegVar_t	atWDats[LCDPL_ROM_BURST_LEN_W];
	int i;
	
	/* ここから単なる引数チェック */
	if(usLength > LCDPL_ROM_BURST_LEN_W)				return S_SPEC_ERROR;
	if(usLength > LCDPL_ROM_PAGE_SIZE_2M)				return S_SPEC_ERROR;
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
	if((uiAddr + usLength) > uiLcdPlRomSize)			return S_SPEC_ERROR;
#endif
	/* ここまで単なる引数チェック */
	
	eResult = eLcdPlRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	atSetUpDats[0].usVal = LCDPL_ROM_CMD_WREN;			/* 書き込みイネーブル設定 */
	atSetUpDats[1].usVal = (uiAddr & 0xFF);				/* ROMアドレス下位 */
	atSetUpDats[2].usVal = ((uiAddr >> 8) & 0xFF);		/* ROMアドレス中位 */
	atSetUpDats[3].usVal = ((uiAddr >> 16) & 0xFF);		/* ROMアドレス上位  */
	for(i=0; i<4; i++){
		atSetUpDats[i].usAddr = LCDPL_REGADDR_ETC +0x30 +i;	/* レジスタアドレス設定 */
	}
	/* WRENコマンド、ROMアドレスを設定 */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 4, atSetUpDats);
	
	atSetUpDats[0].usVal = (usLength & 0xFF);			/* 書き込みデータ長下位 */
	atSetUpDats[1].usVal = ((usLength >> 8) & 0xFF);	/* 書き込みデータ長上位 */
	atSetUpDats[0].usAddr = LCDPL_REGADDR_ETC +0x36;	/* レジスタアドレス設定 */
	atSetUpDats[1].usAddr = LCDPL_REGADDR_ETC +0x37;	/* レジスタアドレス設定 */
	/* データ長を設定 */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 2, atSetUpDats);
	
	for(i=0; i<usLength; i++){
		atWDats[i].usVal  = (uint16)pucDats[i];			/* 書き込みデータ設定 */
		atWDats[i].usAddr = LCDPL_REGADDR_ETC +0x40 +i;	/* レジスタアドレス設定 */
	}
	
	/* 書き込みデータバッファに設定 */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, usLength, atWDats);
	
	/* WRITEコマンド発行 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WRITE);
	
	return eResult;
}


/**
 * @brief	Unveil 強弱パラメータマニュアルロード用子関数
 * @param	uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetUvlModeRomAddr( uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_UVLMODE;
	uint32		uiCrcAddr	= 0x2A0;
	dResult_e	eResult		= S_SUCCESS;
	
	uiRomAddr += (LCDPL_ROMSIZE_UVLMODE * (ucUvlMode));
	uiCrcAddr += ucUvlMode;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	リロード用子関数
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlReloadAll( uint8 ucPnlSizeNo )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usAddr = ucPnlSizeNo * 4;
	uint16		usDat;
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3A, 0x01 );				/* リロードアドレス中位 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3B, usAddr );			/* リロードアドレス上位 */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, (usDat & 0x7F));	/* リロードビット→０ */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, (usDat | 0x80));	/* リロードビット→１ */
	
	MDrv_Timer_Delayms(20);																/* ロード時間の確保(実測) */
	
	return eResult;
}


/**
 * @brief	Revisionデータ読み込み用子関数
 * @param	uint8 *pucRevInfo, uint32 uiRomAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr )
{
	dResult_e	 eResult = S_SUCCESS;
	dFrdRegVar_t atRDat[FRDLCD_REVISION_DATA_MAX-1];
	uint16		 usCrcExp, i;
	
	if(pucRevInfo == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucRevInfo = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult |= eLcdPlRomManualLoad(uiRomAddr +0xF, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);					/* CRC値の転送 */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_ETC +0x140, FRDLCD_REVISION_DATA_MAX-1, TRUE, TRUE);/* データの転送 */
	
	/* データ読み込み */
	atRDat[0].usAddr = LCDPL_REGADDR_ETC +0x140;
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, FRDLCD_REVISION_DATA_MAX-1, atRDat);
	for(i=0; i<FRDLCD_REVISION_DATA_MAX-1; i++){
		pucRevInfo[i] = (uint8)atRDat[i].usVal;
	}
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usCrcExp);
	pucRevInfo[FRDLCD_REVISION_DATA_MAX-1] = (uint8)usCrcExp;
	
	return eResult;
}


/**
 * @brief	Nr 強中弱パラメータマニュアルロード用子関数
 * @param	dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdPlGetNrModeRomAddr( dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_NRMODE;
	uint32		uiCrcAddr	= 0x2B0;
	dResult_e	eResult		= S_SUCCESS;
	
	uiRomAddr += (LCDPL_ROMSIZE_NRMODE * (FRDLCD_NR_MAX -eNrMode));
	uiCrcAddr += FRDLCD_NR_MAX -eNrMode;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/* 090630 ohashi: 肌色補正LUT */
static uint8 aucSkinCtlLutAc00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07,
	0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D,
	0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F,
	0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2A,
	0x2C, 0x2D, 0x2F, 0x31, 0x32, 0x34, 0x36, 0x38,
	0x39, 0x3B, 0x3D, 0x3F, 0x41, 0x43, 0x45, 0x47,
	0x49, 0x4B, 0x4D, 0x4F, 0x51, 0x53, 0x55, 0x58,
	0x5A, 0x5C, 0x5E, 0x61, 0x63, 0x66, 0x68, 0x6A,
	0x6D, 0x6F, 0x72, 0x74, 0x77, 0x7A, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static uint8 aucSkinCtlLutBc00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07,
	0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D,
	0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F,
	0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2A,
	0x2C, 0x2D, 0x2F, 0x31, 0x32, 0x34, 0x36, 0x38,
	0x39, 0x3B, 0x3D, 0x3F, 0x41, 0x43, 0x45, 0x47,
	0x49, 0x4B, 0x4D, 0x4F, 0x51, 0x53, 0x55, 0x58,
	0x5A, 0x5C, 0x5E, 0x61, 0x63, 0x66, 0x68, 0x6A,
	0x6D, 0x6F, 0x72, 0x74, 0x77, 0x7A, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static uint8 aucSkinCtlLutAe00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x04, 0x07, 0x09, 0x0C, 0x0E, 0x10, 0x13, 0x15,
	0x18, 0x1A, 0x1C, 0x1F, 0x21, 0x24, 0x26, 0x28,
	0x2B, 0x2D, 0x30, 0x32, 0x34, 0x37, 0x39, 0x3C,
	0x3E, 0x40, 0x43, 0x45, 0x48, 0x4A, 0x4C, 0x4F,
	0x51, 0x54, 0x56, 0x59, 0x5B, 0x5D, 0x60, 0x62,
	0x65, 0x67, 0x69, 0x6C, 0x6E, 0x71, 0x73, 0x75,
	0x78, 0x7A, 0x7D, 0x7F, 0x81, 0x84, 0x86, 0x89,
	0x8B, 0x8D, 0x90, 0x92, 0x95, 0x97, 0x99, 0x9C,
	0x9E, 0xA1, 0xA3, 0xA5, 0xA8, 0xAA, 0xAD, 0xAF,
	0xB2, 0xB4, 0xB6, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2,
	0xC5, 0xC7, 0xCA, 0xCC, 0xCE, 0xD1, 0xD3, 0xD6,
	0xD8, 0xDA, 0xDD, 0xDF, 0xE2, 0xE4, 0xE6, 0xE9,
	0xEB, 0xEE, 0xF0, 0xF2, 0xF5, 0xF7, 0xFA, 0xFF,
};

static uint8 aucSkinCtlLutBe00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x04, 0x07, 0x09, 0x0C, 0x0E, 0x10, 0x13, 0x15,
	0x18, 0x1A, 0x1C, 0x1F, 0x21, 0x24, 0x26, 0x28,
	0x2B, 0x2D, 0x30, 0x32, 0x34, 0x37, 0x39, 0x3C,
	0x3E, 0x40, 0x43, 0x45, 0x48, 0x4A, 0x4C, 0x4F,
	0x51, 0x54, 0x56, 0x59, 0x5B, 0x5D, 0x60, 0x62,
	0x65, 0x67, 0x69, 0x6C, 0x6E, 0x71, 0x73, 0x75,
	0x78, 0x7A, 0x7D, 0x7F, 0x81, 0x84, 0x86, 0x89,
	0x8B, 0x8D, 0x90, 0x92, 0x95, 0x97, 0x99, 0x9C,
	0x9E, 0xA1, 0xA3, 0xA5, 0xA8, 0xAA, 0xAD, 0xAF,
	0xB2, 0xB4, 0xB6, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2,
	0xC5, 0xC7, 0xCA, 0xCC, 0xCE, 0xD1, 0xD3, 0xD6,
	0xD8, 0xDA, 0xDD, 0xDF, 0xE2, 0xE4, 0xE6, 0xE9,
	0xEB, 0xEE, 0xF0, 0xF2, 0xF5, 0xF7, 0xFA, 0xFF,
};
#define LCDPL_SKIN_CTL_LUT_SIZE (sizeof(aucSkinCtlLutAc00)/sizeof(aucSkinCtlLutAc00[0]))

/**
 * @brief	肌色補正LUT起動時書換え用子関数 (本来はROMによる設定)
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	LCDPL_REGADDR_DATAPATH +0x50 はeFrdLcdPlSetBdEn()でも使用されている
 */
static dResult_e eLcdPlInitSkinCtlLut( void )
{
	dResult_e	eResult	= S_SUCCESS;
	uint16 i;
	dFrdRegVar_t atTmp[LCDPL_SKIN_CTL_LUT_SIZE];
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0x01);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0x01);
	
	/* 090701 ohashi: 田中さん依頼の追加 */
	eResult |= eLcdPlRomManualLoad(0xF6, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
	eResult |= eLcdPlRomManualLoad(0x3D700, LCDPL_REGADDR_BDLUT,         0xF00, TRUE, TRUE);
	eResult |= eLcdPlRomManualLoad(0xFE, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
	eResult |= eLcdPlRomManualLoad(0x3D700, LCDPL_REGADDR_BDLUT +0x1000, 0xF00, TRUE, TRUE);
	
	/* 0xAC00〜 */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xAC00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutAc00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xBC00〜 */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xBC00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutBc00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xAE00〜 */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xAE00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutAe00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xBE00〜 */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xBE00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutBe00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0x08);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0x08);
	
	return eResult;
}
/* end of file */
