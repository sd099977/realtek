/**
 * @file frdlcdguapi.c
 *
 * @brief GuavaLCD部制御
 *
 * Copyright (c) 2010 SHARP CORPORATION
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
#include <tcon/frdlcdguapi.h>
#include <tcon/frdguapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/
//#define DEBUG_LCDGU_MANULOAD_SBR

/* RomAddr */
#define LCDGU_ROMADDR_REVISION	0x300
#define LCDGU_ROMADDR_UNIFIED_REVISION	0x3FFF0
#define LCDGU_ROMADDR_SBRPARAM	0xE500

#define LCDGU_ROMADDR_GHOSTLUT1	0x2E500
#define LCDGU_ROMADDR_GHOSTLUT2	0x38080
#define LCDGU_ROMADDR_QSLUT		0x0A500
#define LCDGU_ROMADDR_UVLMODE	0x7700
#define LCDGU_ROMADDR_NRMODE	0x1060

#define LCDGU_ROMSIZE_SBRPARAM	0x2000
//#define LCDGU_ROMSIZE_SBRPARAM	0x1000

#define LCDGU_ROMSIZE_GHOSTLUT1	0x09B8
#define LCDGU_ROMSIZE_GHOSTLUT2	272
#define LCDGU_ROMSIZE_QSLUT		0x400
#define LCDGU_ROMSIZE_UVLMODE	0x80
#define LCDGU_ROMSIZE_NRMODE	0x10

/* ROM仕様 */
#define LCDGU_ROMSIZE_TOTAL_8M		0x100000/* 8Mbit */
#define LCDGU_ROMSIZE_TOTAL_2M		0x40000	/* 2Mbit */
#define LCDGU_ROM_PAGE_SIZE_2M		256		/* 2Mbit */

/* ROMステータスレジスタ */
#define LCDGU_ROM_STATUS_WIP		0x01	/* Write In Progress */
#define LCDGU_ROM_STATUS_WEL		0x02	/* Write Enable Latch */
#define LCDGU_ROM_STATUS_BP10		0x0C	/* Block Protect(BP0, BP1) */
#define LCDGU_ROM_STATUS_BP210		0x1C	/* Block Protect(BP0, BP1, BP2) */
#define LCDGU_ROM_STATUS_SRDW		0x80	/* Status Register Write Disable */

#define LCDGU_ROM_BURST_LEN_W		256		/* ROMバーストライト用バッファ(LCDCレジスタ)長 */
#define LCDGU_ROM_BURST_LEN_R		256		/* ROMバーストリード用バッファ(LCDCレジスタ)長 */

/* SPIコマンド定義 */
#define LCDGU_ROM_CMD_WRSR			1		/* ステータスレジスタへの書き込み */
#define LCDGU_ROM_CMD_WRITE			2		/* データ書き込み */
#define LCDGU_ROM_CMD_READ			3		/* データ読み込み */
#define LCDGU_ROM_CMD_WRDI			4		/* 書き込み禁止状態にする */
#define LCDGU_ROM_CMD_RDSR			5		/* ステータスレジスタの読み込み */
#define LCDGU_ROM_CMD_WREN			6		/* 書き込み可能にする */
#define LCDGU_ROM_CMD_SE			0xD8	/* Sector Erase */
#define LCDGU_ROM_CMD_BE			0xC7	/* Bulk Erase */

#define LCDGU_EVA_PTN_NUM_MAX		0x12
#define LCDGU_AGI_PTN_NUM_MAX		0x1F

#define LCDGU_I2C_DATA_LEN_MAX 		96		/* I2Cレジスタ転送最大長定義(iic.hでの MAX_DATAS の定義(現状256)による) */


#if 0/* ROMサイズエラーチェックを無効にするときは'1'にする */
#define LCDGU_ROM_SIZE_ERROR_BYPASS
#endif

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
//sakata20111013 extern dFrdLcdPnlSize_e eFrdLcdPnlSize;	//sakata20110921

const static uint8 ucAdGuTbl[FRDLCD_PNL_NUMMAX][7] = {			//sakata20110921
/* 32inch */	{89, 105, 115, 125, 135, 145, 154},				//sakata20110921
/* 40inch *///初期値	{87, 106, 118, 130, 141, 153, 165},		//sakata20110921
/* 40inch */	{41,  46,  48,  50,  53,  54,  56},//DS5用		//sakata20110921
/* 46inch *///初期値	{88, 106, 116, 127, 138, 148, 159},		//sakata20110921
/* 46inch */	{42,  46,  49,  51,  53,  55,  56},	//DS5用		//sakata20110921
/* 52inch */	{94, 112, 123, 133, 144, 155, 166},				//sakata20110921
/* 60inch *///初期値	{97, 116, 128, 141, 155, 168, 183},		//sakata20110921
/* 60inch */	{43,  47,  49,  51,  53,  55,  57},//DS5用		//sakata20110921
};																//sakata20110921


/* static const変数 */
static const dFrdLcdTrnOvr_e aeLcdGuConvTrnOvr[LCDGU_CPWB_DIREC_NUM][FRDLCD_TRN_OVR_NUMMAX] =
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
static const uint8 aucLcdGuTestPtnTbl[FRDLCD_TESTPTN_NUMMAX] =
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
	LCDGU_AGI_PTN_NUM_MAX + 0xA,				/* シャドーイングパターン(評価用パターン) */
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
	LCDGU_AGI_PTN_NUM_MAX + 0x1,				/* モノクロ表示 */
	LCDGU_AGI_PTN_NUM_MAX + 0x2,				/* 階調テスト表示 */
	LCDGU_AGI_PTN_NUM_MAX + 0x3,				/* ベタ表示 */
	LCDGU_AGI_PTN_NUM_MAX + 0x4,				/* 縦ストライプ */
	LCDGU_AGI_PTN_NUM_MAX + 0x5,				/* 水平方向グレースケール */
	LCDGU_AGI_PTN_NUM_MAX + 0x6,				/* 垂直方向グレースケール */
	LCDGU_AGI_PTN_NUM_MAX + 0x7,				/* カラーチャート */
	LCDGU_AGI_PTN_NUM_MAX + 0x8,				/* フリッカパターン１ */
	LCDGU_AGI_PTN_NUM_MAX + 0x9,				/* フリッカパターン２ */
	LCDGU_AGI_PTN_NUM_MAX + 0xB,				/* A/D調整用パターン */
	LCDGU_AGI_PTN_NUM_MAX + 0xC,				/* 上下分割ベタ */
	LCDGU_AGI_PTN_NUM_MAX + 0xD,				/* 左右分割ベタ */
	LCDGU_AGI_PTN_NUM_MAX + 0xE,				/* ライン反転用フリッカパターン */
	LCDGU_AGI_PTN_NUM_MAX + 0xF,				/* 砂嵐パターン */
	LCDGU_AGI_PTN_NUM_MAX + 0x10,				/* 1ライン表示パターン(Zucchini) */
	LCDGU_AGI_PTN_NUM_MAX + 0x11				/* 1列表示パターン(Zucchini) */
};

/****************/
/* 映像反転設定 */
/****************/
/* miniLVDS only */
static const uint16 aucLcdGuTrnOvr[7][FRDLCD_TRN_OVR_NUMMAX] = {
/* CSS		0xAD0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
/* CSS		0xBD0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 のみ */
/* DP		0xA31 */			{0x0000, 0x0001, 0x0000, 0x0001},	/* bit2 のみ */
/* TIMGEN	0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* TIMGEN	0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},
/* CCK		0xA2E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
/* CCK		0xB2E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 のみ */
};


/* static変数 */
static uint8 aucLcdGuRevInfo[FRDLCD_REVISION_DATA_MAX];			/* ROM Revisionデータ保存用配列 */
static uint8 aucLcdGuUnifiedRevInfo[FRDLCD_REVISION_DATA_MAX];	/* ROM Revision(統合)データ保存用配列 */
static dLcdGuRegionAndInchInfo_t tRegionAndInchInfo;/* 仕向け・インチサイズ情報保存用変数 */

static flag				fGetRevInfo		= FALSE;
static dFrdLcdTrnOvr_e	eLcdGuTrnOvr	= FRDLCD_TRN_OVR_NORMAL;
static dFrdInputFreq_e	eLcdGuInputFreq	= FRD_INPUT_FREQ_60HZ;
//static uint8			ucLcdGuLvl		= 4;
uint8			ucLcdGuLvl		= 4;

static dFrdLcdError_t		atLcdGuErrInfo[FRDLCD_ERR_LOG_NUM_MAX];
static uint8				ucLcdGuErrInfoInCnt  = 0;
static uint8				ucLcdGuErrInfoOutCnt = 0;

static uint8			ucLcdGuPnlSizeNo	= 0;/* 8Mbit ROM対応 : 0:32型,  1:40型,  2:46型,  3:52型  */
static uint32			uiLcdGuRomOffset	= 0;/*               : 0x00000, 0x40000, 0x80000, 0xC0000 */
static uint32			uiLcdGuRomSize		= LCDGU_ROMSIZE_TOTAL_8M;

static uint8 ucNegCnt = 0;
static uint8 ucPosCnt = 0;
static flag f1stCycle;

/* **
 * ** prototype
 * **/
dResult_e eFrdLcdGuSetOutFreq( dFrdInputFreq_e eInputFreq );	//<- 2011/02/24	四開発追加
static dResult_e eLcdGuChkRomLoadEnd( void );
static void vAddrConv(dFrdLcdGuCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats);
static uint16 usAddrConv(dFrdLcdGuCh_e *peCh, uint16 usAddr);
static dResult_e eLcdGuChkCrcForRomLoad( void );
static dResult_e eLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn , flag fOffset);
static flag fLcdGuRegDepth16bit( uint32 uiAddr );
static dResult_e eLcdGuRomStatusChk( uint16 *pusStatus );
static dResult_e eLcdGuSetTpDat( dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb );
static dResult_e eLcdGuRomToWProtectMode( flag fWPMEn );
static dResult_e eLcdGuGetRegionAndInchInfo( dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo );
static dResult_e eLcdGuSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr );
static dResult_e eLcdGuSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl );
#ifdef DEBUG_LCDGU_MANULOAD_SBR
static void vLcdGuDbgMnl( void );
#endif
static dResult_e eLcdGuGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuGetGhostLut2RomAddr( dFrdLcdGuCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr);
static dResult_e eLcdGuSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucLvl );
static dResult_e eLcdGuGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats );
static dResult_e eLcdGuSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr );
static dResult_e eLcdGuReloadAll( uint8 ucPnlSizeNo );					/* 8Mbit ROM対応 */
static dResult_e eLcdGuGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr );	/* 8Mbit ROM対応 */

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
dResult_e eFrdLcdGuRegWs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32 i;
//sakata20110627	uint16 tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1

	vAddrConv(&eCh, iRegNum, ptDats);

#ifdef TURNKEY1
	for( i=0; i<iRegNum; i++ )
	{
//sakata20110627		tmp_addr = ptDats[0].usAddr + (uint16)i;
//sakata20110627		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDats[i].usVal);
	eResult = eI2CWrite( IIC_SLV_ADDR_TCON, ptDats[i].usAddr, ptDats[i].usVal);	//sakata20110627
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
dResult_e eFrdLcdGuRegRs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
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
		ptDats[i].usAddr = ptDats[0].usAddr + i;								//sakata20110627

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
dResult_e eFrdLcdGuRegW( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 usVal )
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
dResult_e eFrdLcdGuRegR( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 *pusVal )
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
** @brief	ROMロード正常終了チェックAPI
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	
*******************************************************************************/
dResult_e eFrdLcdGuChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	dResult_e	eResultTmp;
	
	/* 初回ロードのロード終了確認 */
	eResult |= eLcdGuChkRomLoadEnd();
	
	/* 統合リビジョンの取得 */
	eResultTmp = eLcdGuGetRevInfo( aucLcdGuUnifiedRevInfo, LCDGU_ROMADDR_UNIFIED_REVISION );
	if( aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE] == 0x08 ){
	/* ROM：8Mbitデータ */
		
		/* 8Mbitと判別された時点で、Offset値を設定する */
		uiLcdGuRomOffset = ucLcdGuPnlSizeNo * LCDGU_ROMSIZE_TOTAL_2M;
		
		/* パネルサイズに対応するデータ2MbitをリロードAll */
		eResult |= eLcdGuReloadAll( ucLcdGuPnlSizeNo );
		
		/* ２回目ロードのロード終了確認 */
		eResult |= eLcdGuChkRomLoadEnd();
		
		eResult |= eResultTmp;
		
		uiLcdGuRomSize = LCDGU_ROMSIZE_TOTAL_8M;
	}
	else{
	/* ROMが2Mbitデータ → 初回ロードのみで追加処理は必要無し */
		uiLcdGuRomOffset = 0;
		uiLcdGuRomSize = LCDGU_ROMSIZE_TOTAL_2M;
	}
	
	/* サイズ別リビジョンの取得 */
	eResult |= eLcdGuGetRevInfo( aucLcdGuRevInfo, LCDGU_ROMADDR_REVISION );
	
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
dResult_e eFrdLcdGuGetRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdGuRevInfo[i];
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
dResult_e eFrdLcdGuGetRevStr( int8 *pcRevInfo )
{
//sakata20110920 warning_erase	int8 acPanelType[] = "FM";/* FM はMiniLVDSパネル */	//sakata20110920
	int8 cFrcType;										//sakata20110920
//sakata20110920 warning_erase	int8 cTestVer = 'T';								//sakata20110920
	
	if( pcRevInfo == NULL ) return S_SPEC_ERROR;
	
	if( uiLcdGuRomSize == LCDGU_ROMSIZE_TOTAL_2M ){
	/* 2Mbitデータ */
		if(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4){
		/* MiniLVDS */
		}
		else{
			/* PPDS */
			return S_FAILURE;
		}
		switch (aucLcdGuRevInfo[FRDLCD_REVISION_FRC]){
			case 0x00: cFrcType = 'E'; break;/* Easter */
			case 0x01: cFrcType = 'F'; break;/* Fraser */
			case 0x02: cFrcType = 'Y'; break;/* Yellowtail */
			case 0x04: cFrcType = 'A'; break;/* Arugula */
			case 0x05: cFrcType = 'P'; break;/* Guava */
			case 0x07: cFrcType = 'G'; break;/* Guava */
			case 0x08: cFrcType = 'T'; break;/* Turnip */	//sakata20111220
			default:   cFrcType = '?'; break;/* 不明 */
		}
		if( aucLcdGuRevInfo[FRDLCD_REVISION_VER] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* テストバージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%c%02X",
					aucLcdGuRevInfo[FRDLCD_REVISION_YEAR_L],/* 年 */
					aucLcdGuRevInfo[FRDLCD_REVISION_MONTH],	/* 月 */
					aucLcdGuRevInfo[FRDLCD_REVISION_DAY],	/* 日 */
					acPanelType,							/* パネル駆動方式 */
					cFrcType,								/* T-CONデバイス */
					aucLcdGuRevInfo[FRDLCD_REVISION_INCHI],	/* インチサイズ */
					aucLcdGuRevInfo[FRDLCD_REVISION_MISC],	/* モデル */
					cTestVer,
					aucLcdGuRevInfo[FRDLCD_REVISION_VER] & 0x7F	/* バージョン */
				);
#endif //TURNKEY1
		}
		else{
		/* 正式バージョン */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%02X",
					aucLcdGuRevInfo[FRDLCD_REVISION_YEAR_L],/* 年 */
					aucLcdGuRevInfo[FRDLCD_REVISION_MONTH],	/* 月 */
					aucLcdGuRevInfo[FRDLCD_REVISION_DAY],	/* 日 */
					acPanelType,							/* パネル駆動方式 */
					cFrcType,								/* T-CONデバイス */
					aucLcdGuRevInfo[FRDLCD_REVISION_INCHI],	/* インチサイズ */
					aucLcdGuRevInfo[FRDLCD_REVISION_MISC],	/* モデル */
					aucLcdGuRevInfo[FRDLCD_REVISION_VER]	/* バージョン */
				);
#endif //TURNKEY1
		}
	}
	else{
	/* 8Mbitデータ */
		if( aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* テストバージョン */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%c%02X%02X",
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* 年 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* 月 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* 日 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* 仕向け */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* モデル */
					cTestVer,									/* テストバージョン */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x7F,	/* バージョン番号(H) */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* バージョン番号(L) */
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
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* 年 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* 月 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* 日 */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* 仕向け */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* モデル */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H],	/* バージョン番号(H) */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* バージョン番号(L) */
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
dResult_e eFrdLcdGuGetUnifiedRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdGuUnifiedRevInfo[i];
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
dResult_e eFrdLcdGuInit( void )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ROMをライトプロテクトモードへ */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
	/* 仕向け・インチサイズ情報 */
	eResult |= eLcdGuGetRegionAndInchInfo(&tRegionAndInchInfo);
	if(eResult != S_SUCCESS ) return eResult;
	
	/* static変数の初期値設定 */
	eLcdGuTrnOvr	= aeLcdGuConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][FRDLCD_TRN_OVR_NORMAL];
	eLcdGuInputFreq	= FRD_INPUT_FREQ_60HZ;
	ucLcdGuLvl		= 4;
	f1stCycle = TRUE;
	
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
dResult_e eFrdLcdGuSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e eResult = S_SUCCESS;
	
	if(eTrnOvr >= FRDLCD_TRN_OVR_NUMMAX){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eTrnOvr = %d\n", (int8)eTrnOvr);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eTrnOvr = aeLcdGuConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][eTrnOvr];
	
	eResult |= eLcdGuSetTrnOvrReg(eTrnOvr);
	
	eResult |= eLcdGuSetSbr(eTrnOvr, ucLcdGuLvl);
	
	eLcdGuTrnOvr = eTrnOvr;
	
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
dResult_e eFrdLcdGuSetOutput( flag fOutEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD;
	flag		fMiniL = (flag)(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	
	if(fMiniL){
	/* miniLVDS */
		/* LS出力Hi-Z解除 (defaultが1でないと解除できない??) */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_PNL +0x2B, 0);
		
		/* ODSデータ出力ミュートON/OFF */
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x04, &usDatAB);
		eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x04, &usDatCD);
		if(fOutEn){
		/* ミュートOFF(解除) → bit4 を 0 */
			eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x04, usDatAB & 0xEF);
			eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x04, usDatCD & 0xEF);
		}else{
		/* ミュートON → bit4 を 1 */
			eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x04, usDatAB | 0x10);
			eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x04, usDatCD | 0x10);
		}
	}
	else{
	/* PPDS */
		return S_FAILURE;
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
dResult_e eFrdLcdGuSetTestPtn( dFrdLcdTestPtn_e eTestPtn )
{
	dResult_e		eResult = S_SUCCESS;
	uint8			ucTestPtn;
	
	if((eTestPtn < FRDLCD_TESTPTN_OFF) || (eTestPtn >= FRDLCD_TESTPTN_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eTestPtn = %d\n", (int8)eTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	ucTestPtn = aucLcdGuTestPtnTbl[eTestPtn];
	
	if(ucTestPtn == 0){
		/* テストパターンOFF */
		eResult |= eFrdLcdGuSetAgingPtn(0);	/* エージング用テストパターンをOFF */
		eResult |= eFrdLcdGuSetEvaPtn(0);		/* 評価用テストパターンをOFF */
	}
	else if(ucTestPtn <= (LCDGU_AGI_PTN_NUM_MAX + LCDGU_EVA_PTN_NUM_MAX)){
		/* テストパターンON */
		
		/* 所望のテストパターンモードに設定 */
		if(ucTestPtn <= LCDGU_AGI_PTN_NUM_MAX){
			/* エージングパターン設定 */
			eResult |= eFrdLcdGuSetAgingPtn(ucTestPtn);
			/* 評価用テストパターンをOFF */
			eResult |= eFrdLcdGuSetEvaPtn(0);
		}else{
			/* 評価用パターン設定 */
			eResult |= eFrdLcdGuSetEvaPtn(ucTestPtn - LCDGU_AGI_PTN_NUM_MAX);
			/* エージング用テストパターンをOFF */
			eResult |= eFrdLcdGuSetAgingPtn(0);
		}
	}
	else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucTestPtn = %d\n", (int8)ucTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDエージングパターン設定API
** @param	ucAgingPtn : エージングパターン番号 [0x00-0x1F] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetAgingPtn( uint8 ucAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usBmpEnab = 0;
	
	if(ucAgingPtn > LCDGU_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucAgingPtn = %d\n", (int8)ucAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucAgingPtn == 0x13){
	/* ドット反転フリッカ + BITMAP */
		usBmpEnab = 1;/* BitMap表示ビットを立てる */
	}
	
	/* BitMap表示設定 + パターン設定 */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x03, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x03, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	
	if((ucAgingPtn == 3) || (ucAgingPtn == 0x1F)){
	/* QS用テストパターン1 の場合、バーの同期を合わせる為、ここでリセットを行う */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDCリセット */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDCリセット解除 */
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
dResult_e eFrdLcdGuSetEvaPtn( uint8 ucEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB設定 */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB設定 */
	
	if(ucEvaPtn > LCDGU_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucEvaPtn = %d\n", (int8)ucEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB色)設定 */
	eResult |= eLcdGuSetTpDat(LCDGU_AB, &tTpda, &tTpdb);
	eResult |= eLcdGuSetTpDat(LCDGU_CD, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x05, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x05, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS ON/OFF設定API
** @param	fQsEn	: QS ON/OFF設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			QS ONの前に、周波数・温度に合ったQS LUTをマニュアルロードしてください。
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetQsEn( flag fQsEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usOsOn=0;
	
	if(fQsEn){
			usOsOn = 0x10;	/* ON/OFFは bit4 */
	}
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x08, &usDatAB);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x08, &usDatCD);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x08, (usDatAB & 0xCF) | usOsOn);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x08, (usDatCD & 0xCF) | usOsOn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS半画面ON/OFF設定API
** @param	fLonRoff : 半画面ON/OFF設定, TRUE = 左ON右OFF, FALSE = 左OFF右ON (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			  miniLVDSの場合、反転処理がQSの前で行われる為、QS設定が反転制御について回りません。
**			  TV仕様としては、映像反転状態のままデモモード はありますが、デモモード状態のまま映像反転 は無い為、
**			  ドライバとしては、前者の場合のみ対応(現在の映像反転状態に応じてQSのON/OFF領域を決める)しています。
** @note
**			RegAddr:0x6408 のbit4 をONしてるのみ
*******************************************************************************/
dResult_e eFrdLcdGuSetQsHalf( flag fLonRoff )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usAB=0, usCD=0;
	
	if(!(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4)){
	/* PPDS(左右反転処理がQSの後ろ) */
		return S_FAILURE;
	}
	else{
	/* miniLVDS(左右反転処理がQSの前) */
		switch( eLcdGuTrnOvr ){
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
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x08, &usDatAB);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x08, &usDatCD);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x08, (usDatAB & 0xEF) | usAB);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x08, (usDatCD & 0xEF) | usCD);
	
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
dResult_e eFrdLcdGuSetQsFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult;
	
	if((eInputFreq < FRD_INPUT_FREQ_48HZ) || (eInputFreq >= FRD_INPUT_FREQ_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eInputFreq = %d\n", (int8)eInputFreq);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetQsFreqTemp(eInputFreq, ucLcdGuLvl);
	eLcdGuInputFreq = eInputFreq;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS温度レベル設定API
** @param	ucLvl : 温度指定 [0(低温)-7(高温)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetQsLvl( uint8 ucLvl )
{
	dResult_e eResult;
	
	if(ucLvl > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucLvl = %d\n", (int8)ucLvl);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetQsFreqTemp(eLcdGuInputFreq, ucLvl);
	ucLcdGuLvl = ucLvl;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	SBR設定API
** @param	ucLvl : 温度指定 [0(低温)-7(高温)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetSbr( uint8 ucLvl )
{
	dResult_e eResult;
	
	if(ucLvl > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucLvl = %d\n", (int8)ucLvl);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetSbr(eLcdGuTrnOvr, ucLvl);
	ucLcdGuLvl = ucLvl;
	
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
dResult_e eFrdLcdGuRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usBurstLen;
	uint16		usLenToNextPage;
	
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + uiLength) > uiLcdGuRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiLength = %d\n", uiLength);
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* ここまで単なる引数チェック */
	
	/* ライトプロテクトモードを解除 */
	eResult |= eLcdGuRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	while(1){
		if(uiLength > LCDGU_I2C_DATA_LEN_MAX){
			usBurstLen = LCDGU_I2C_DATA_LEN_MAX;
		}
		else if(uiLength > 0){
			usBurstLen = uiLength;
		}
		else{
		/* uiLength == 0 */
			break;
		}
		
		/* 次のページ境界までのバイト数 */
		usLenToNextPage = LCDGU_ROM_PAGE_SIZE_2M - (uiAddr % LCDGU_ROM_PAGE_SIZE_2M);
		
		/* "usBurstLen" がページを跨ぐ場合は、境界までで分割する */
		if(usBurstLen > usLenToNextPage) {
			usBurstLen = usLenToNextPage;
		}
		
		eResult |= eLcdGuRomWs(uiAddr, usBurstLen, pucDats);
		uiAddr += usBurstLen;
		uiLength -= usBurstLen;
		pucDats += usBurstLen;
	}
	/* ライトプロテクトモードへ */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
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
dResult_e eFrdLcdGuRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t	atRDats[LCDGU_ROM_BURST_LEN_R];
	uint16			i;
	
	/* ここから単なる引数チェック */
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if(usLength > LCDGU_ROM_BURST_LEN_R){/* 最大転送長 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + usLength) > uiLcdGuRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* ここまで単なる引数チェック */
	
	eResult = eLcdGuRomManualLoad(uiAddr, LCDGU_REGADDR_ETC +0x140, usLength, FALSE, FALSE);
	
	/* データ読み込み */
	atRDats[0].usAddr = LCDGU_REGADDR_ETC +0x140;
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, (int32)usLength, atRDats);
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
dResult_e eFrdLcdGuRomErase( void )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fGetRevInfo != TRUE) return S_FAILURE;
	
	if((aucLcdGuRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0) return S_SPEC_ERROR;/* EEPROMの場合はエラーリターン */
	
	/* ライトプロテクトモードを解除 */
	eResult |= eLcdGuRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
		
	/* 書き込みイネーブルコマンドを発行 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WREN);
	
	/* BE(Bulk Erase)コマンド発行 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_BE);
	
	MDrv_Timer_Delayms(10000);/* Bulk Erase の時間(8Mbit対応で増加) */
	
	/* ライトプロテクトモードへ */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
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
dResult_e eFrdLcdGuSetVerUp( uint8 *pucDats, flag fVerify )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiTotalLen, uiReadNum, i, j;
	uint32 uiBufLen = 0x100;
	uint8 ucRomSizeR1,ucRomSizeR2,ucRomSizeW1,ucRomSizeW2;
	
	/* Guavaと判別されていると仮定 */
	
	if(pucDats == NULL) return S_FAILURE;
	
	/* データサイズ : 書かれているデータの統合リビジョンを参照 */
	ucRomSizeR1 = aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE];
	/* データサイズ : 書こうとしているデータの統合リビジョンを参照 */
	ucRomSizeW1 = pucDats[LCDGU_ROMADDR_UNIFIED_REVISION + FRDLCD_UNI_REVISION_ROM_SIZE];
	
	/* データサイズ : 書かれているデータのサイズ別リビジョンを参照 */
	ucRomSizeR2 = aucLcdGuRevInfo[FRDLCD_REVISION_ROM_SIZE];
	/* データサイズ : 書こうとしているデータのサイズ別リビジョンを参照 */
	ucRomSizeW2 = pucDats[LCDGU_ROMADDR_REVISION + FRDLCD_REVISION_ROM_SIZE];
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
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
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
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
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
#endif //TURNKEY1
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
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
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
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
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
	if((aucLcdGuRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash の場合 → 一旦全消去 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Erase......\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRomErase();
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
	eResult |= eFrdLcdGuRomWs(0, uiTotalLen, pucDats);
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
			eFrdLcdGuRomRs(i*uiBufLen, uiBufLen, aucRDats);
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
			eFrdLcdGuRomRs(uiReadNum*uiBufLen, uiTotalLen, aucRDats);
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
** @brief	フリーラン設定API (LCD側)
** @param	fFreeEn	: フリーラン設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	T-CON部の強制フリーラン機能を使用します。
*******************************************************************************/
dResult_e eFrdLcdGuSetFreeRun( flag fFreeEn )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fFreeEn){
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x06, 0x07);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x06, 0x07);
	}else{
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x06, 0x06);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x06, 0x06);
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
dResult_e eFrdLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn )
{
	dResult_e eResult;
	eResult = eLcdGuRomManualLoad(uiRomAddr, uiRegAddr, usByteLen, fCrcEn, TRUE);
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
dResult_e eFrdLcdGuGetErrInfo( dFrdLcdError_t *ptError )
{
	*ptError = atLcdGuErrInfo[ ucLcdGuErrInfoOutCnt ];
	if( atLcdGuErrInfo[ ucLcdGuErrInfoOutCnt ].ucErrCode != 0 ){
		ucLcdGuErrInfoOutCnt++;
		ucLcdGuErrInfoOutCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
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
dResult_e eFrdLcdGuAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i, j;
	
	/* 映像反転、SBR温度設定 */
	for(i=0; i<4; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdLcdTrnOvr_e)i != eLcdGuTrnOvr ) || ( j != ucLcdGuLvl ) ){
				eResult |= eLcdGuSetSbr( (dFrdLcdTrnOvr_e)i, j );
			}
		}
	}
	eResult |= eLcdGuSetSbr( eLcdGuTrnOvr, ucLcdGuLvl );/* 元に戻す */
	
	
	/* QS周波数設定、QS温度設定 */
	for(i=0; i<3; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdInputFreq_e)i != eLcdGuInputFreq ) || ( j != ucLcdGuLvl ) ){
				eResult |= eLcdGuSetQsFreqTemp( (dFrdInputFreq_e)i, j );
			}
		}
	}
	eResult |= eLcdGuSetQsFreqTemp( eLcdGuInputFreq, ucLcdGuLvl );/* 元に戻す */
	
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
dResult_e eFrdLcdGuSetBdEn( flag fBdEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fBdEn){
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x50, 0);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x50, 0);
	}else{
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x50, 1);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x50, 1);
	}
	
	return eResult;
}


#define FRD_VCOM_ADJ_VAL_MAX   		0x3FF
#define FRD_VCOM_ADJ_VAL_CENTRE		373
#define FRD_VCOM_ADJ_VAL_CENTRE60 	452
/*!
********************************************************************************
** @brief	DAC設定用API (VCOM設定用)
** @param	fMemEn : 書込み先指定 TRUE: メモリー, FALSE: レジスタ (型定義: flag)
** @param	usDat  : VCOM調整データ (型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetDac( flag fMemEn, uint16 usDat )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp1 = 0x12, usTmp2 = 0, usCentre;
	uint8 ucCnt = 0;
	
	/* センター値 */
	//if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] == 0x60 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment
	//else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
		
	if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] <= 0x52 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment

	if( usDat <= ( FRD_VCOM_ADJ_VAL_MAX - (usCentre -64) ) ){
		usDat += (usCentre -64);
	}
	else{
		usDat = FRD_VCOM_ADJ_VAL_MAX;/* MAXで止める */
		eResult |= S_SPEC_ERROR;
	}
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x01, 0xe8);	/* Slv Addr */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x02, 2);		/* バースト長 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x03, 0);		/* write */
	
	/* 0x608では[15:14]01でメモリ, 10でレジスタにセット, 
	   [9:8]VCOM上位, [7:0]RegisterAddress(0x12) */
	if(fMemEn)	usTmp1 |= 0x4000;
	else		usTmp1 |= 0x8000;
	usTmp1 |= usDat & 0x0300;
	usTmp2 |= usDat & 0x00FF;
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, usTmp1);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x09, usTmp2);
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x2c, 1);		/* コマンドアクティブ実行 */
	
	MDrv_Timer_Delayms(100);
	
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x30, &usTmp1);
		
		if((eResult == S_SUCCESS) && ((usTmp1 & 0x02) == 0x00)){
			break;
		}else{
			MDrv_Timer_Delayms(5);
		}
		ucCnt++;
		
		if(ucCnt > 15){
			eResult |= S_FAILURE;
			break;
		}
	}
	
	if(usTmp1 & 0x01){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] VCOM I2C ERROR !!\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x31, 1);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	DAC確認用API (VCOM設定用)
** @param	pusDat  : VCOM調整データ (型定義: uint16 *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			メモリの値を取ってきている様子。
** @note
*******************************************************************************/
dResult_e eFrdLcdGuGetDac( uint16 *pusDat )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp, usCentre;
//	dFrdRegVar_t	atTmp[2];
	uint8 ucCnt = 0;
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x01, 0xe8);	/* Slv Addr */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x02, 1);		/* バースト長 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x03, 2);		/* write */
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, 0x112);	// [7:0]VCOM RegisterAddress
	/* 阿部さんの資料(100309 17:04)の通りに変更 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, 0x012);	// [7:0]VCOM RegisterAddress
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x2c, 1);		/* コマンドアクティブ実行 */
	
	MDrv_Timer_Delayms(10);
	
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x30, &usTmp);
		
		if((eResult == S_SUCCESS) && ((usTmp & 0x04) == 0x04)){// bit2:r_rdy 1でread完了
			break;
		}else{
			MDrv_Timer_Delayms(5);
		}
		ucCnt++;
		
		if(ucCnt > 15){
			eResult |= S_FAILURE;
			break;
		}
	}
	
	if(usTmp & 0x01){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] VCOM I2C ERROR !!\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x31, 1);
	}else{
//		atTmp[0].usAddr = LCDGU_REGADDR_IMC +0x38;
//		eResult |= eFrdLcdGuRegRs(LCDGU_AB, 2, atTmp);
//		
//		*pusDat = ((atTmp[0].usVal & 0x03) << 8) | ((atTmp[0].usVal & 0xff00) >> 8);
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x38, &usTmp);
		
		*pusDat = ((usTmp & 0x03) << 8) | ((usTmp & 0xff00) >> 8);
	}
	
	/* センター値対応 */
	//if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] == 0x60 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment
	//else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	
	if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] <= 0x52 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment

	if(*pusDat >= (usCentre -64)){
		*pusDat -= (usCentre -64);
	}else{
		*pusDat = 0;
		eResult |= S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	温度指定API
** @param	ucLvl : 温度指定 [0-255] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			1秒毎に、外部デバイスのサーミスタにて得られる0-255の値を
**			本APIに渡してください。
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetLvl( uint8 ucLvl )
{
	dResult_e eResult = S_SUCCESS;
	uint8 *pucCntAddr1, *pucCntAddr2;
	
	/* 初回は即時反映 */
	if(f1stCycle){
		eResult |= eFrdGuSetGain(ucLvl);
		eResult |= eFrdLcdGuSetQsLvl(ucLvl);
		eResult |= eFrdLcdGuSetSbr(ucLvl);
		
//		ucLcdGuLvl = ucLvl;
		
		f1stCycle = FALSE;
	}
	
	/* 直前の温度レベルと同じ */
	if(ucLvl == ucLcdGuLvl){
		ucNegCnt = 0;
		ucPosCnt = 0;
	}
	/* 変化あり */
	else{
		/* +方向に変化 */
		if(ucLvl > ucLcdGuLvl){
			pucCntAddr1 = &ucNegCnt;
			pucCntAddr2 = &ucPosCnt;
		}else
		/* -方向に変化 */
		{
			pucCntAddr1 = &ucPosCnt;
			pucCntAddr2 = &ucNegCnt;
		}
		*pucCntAddr1 = 0;
		(*pucCntAddr2)++;
		
		/* 最初の変化以降3回続いたら反映 */
		if(*pucCntAddr2 > 3){
			*pucCntAddr2 = 0;
			if(pucCntAddr2 == &ucPosCnt){
				ucLcdGuLvl++;	/* レベル+1を設定 */
			}else{
				ucLcdGuLvl--;	/* レベル-1を設定 */
			}
			eResult |= eFrdGuSetGain(ucLcdGuLvl);
			eResult |= eFrdLcdGuSetQsLvl(ucLcdGuLvl);
			eResult |= eFrdLcdGuSetSbr(ucLcdGuLvl);
		}
	}
	/* デバッグ用 */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(0, "Lvl: %d\n", ucLcdGuLvl);
#endif //TURNKEY1

	/* 1秒毎にTyp_V_Gainを設定 */
	eResult |= eFrdGuSetTypvGain();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	VCOM用パターン表示設定API
** @param	fVcom : VCOM表示 ON/OFF設定(型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetVcomPtn( flag fVcomEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fVcomEn){
		eResult |= eFrdLcdGuSetAgingPtn(0x13);
		eResult |= eFrdStandby(FALSE);
	}else{
		eResult |= eFrdLcdGuSetAgingPtn(0);
		eResult |= eFrdStandby(TRUE);
	}
	return eResult;
}


/*!	//<- 2011/02/24	四開発追加
********************************************************************************
** @brief	入力周波数毎の設定API
** @param	eInputFreq	: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note 101129 H.Nishimura: Wソース限定の処理を追加(現時点では52V5向け)
*******************************************************************************/
dResult_e eFrdLcdGuSetOutFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	
	if( aucLcdGuRevInfo[FRDLCD_REVISION_CPWB] & 0x10 ){

#ifdef TURNKEY1
		//横スジ問題対応<- 2011/03/03	四開発追加
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x81cd, 0x0002 );
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x8005, 0x0001 );
		//-> 2011/03/03	四開発追加
#endif //TURNKEY1

	/* Wソース識別bit=1 */
		if( eInputFreq == FRD_INPUT_FREQ_48HZ ){
			eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x0E, 0x4A);
			eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x0E, 0x4A);
		}
		else{
			eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x0E, 0x23);
			eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x0E, 0x23);
		}
	}
	
	return eResult;
}

/*!																					//sakata20110921
********************************************************************************	//sakata20110921
** @brief	温度指定API																//sakata20110921
** @param	ucTemp : 温度指定 [0-255] (型定義: uint8)								//sakata20110921
** @retval	S_SUCCESS 正常終了														//sakata20110921
** @retval	other エラーコード														//sakata20110921
** @par コメント																	//sakata20110921
**			1秒毎に、外部デバイスのサーミスタにて得られる0-255の値を				//sakata20110921
**			本APIに渡してください。													//sakata20110921
** @note																			//sakata20110921
*******************************************************************************/	//sakata20110921
dResult_e eFrdLcdGuSetTemp( uint8 ucTemp )											//sakata20110921
{																					//sakata20110921
	dResult_e eResult = S_SUCCESS;													//sakata20110921
	uint8 i = 0, ucLvl;																//sakata20110921

//sakata20111013			while(ucTemp > ucAdGuTbl[eFrdLcdPnlSize][i]){								//sakata20110921
//sakata20111013				i++;																//sakata20110921
//sakata20111013				if(i == 7){															//sakata20110921
//sakata20111013					break;															//sakata20110921
//sakata20111013				}																	//sakata20110921
//sakata20111013			}																		//sakata20110921

			/* 温度レベルは配列の逆 */												//sakata20110921
			ucLvl = ~i & 0x07;														//sakata20110921

//			eResult |= eFrdLcdSetQsTemp(ucLvl);										//sakata20110921
			eResult |= eFrdLcdSetLvl(ucLvl);										//sakata20110921
																					//sakata20110921
	return eResult;																	//sakata20110921
}																					//sakata20110921

//-> 2011/02/24	四開発追加

/**
 * @brief	ロード終了確認用子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdGuChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucTimeOutCnt = 0;
	
	while(1){
		/* ROMロード終了ビットの確認 */
		eResult = eFrdLcdGuRegR(LCDGU_AB, 0x01, &usDat);
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
		eResult |= eLcdGuChkCrcForRomLoad();
	}
	
	return eResult;
}


/**
 * @brief	チャネルによるアドレス変換子関数(上位)
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static void vAddrConv(dFrdLcdGuCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats)
{
	uint32 i;
	if(*peCh == LCDGU_CD){
		for(i=0; i<iRegNum; i++){
			*peCh = LCDGU_CD;/* 下記関数内で"LCDGU_AB"に書き換えられてしまう為、都度元に戻します */
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
static uint16 usAddrConv(dFrdLcdGuCh_e *peCh, uint16 usAddr)
{
	if(*peCh == LCDGU_CD){
		/* 100121 ohashi: guava用 */
		if(usAddr < 0xA00){
		}
		else if(usAddr < 0x2000){
		/* DataPath */
			if((usAddr >= 0xA00) && (usAddr < 0xB00)){
				usAddr += 0x100;
			}
		/* CsSub */
			else if((usAddr >= 0xC00) && (usAddr < 0xD00)){
				usAddr += 0x100;
			}
		/* LCDC(SBR) */
			else if((usAddr >= 0x1000) && (usAddr < 0x1080)){
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
		else if(usAddr < 0x8000){
		/* GamLut */
			if((usAddr >= 0x4000) && (usAddr < 0x5200)){
				usAddr += 0x1200;
			}
		/* Decont */	
			if((usAddr >= 0x6400) && (usAddr < 0x6500)){
				usAddr += 0x100;
			}
		/* QsLut */
			else if((usAddr >= 0x6600) && (usAddr < 0x6800)){
				usAddr += 0x200;
			}
		/* TimGen */
			else if((usAddr >= 0x6A00) && (usAddr < 0x6A80)){
				usAddr += 0x80;
			}
		/* BitMap */
			else if((usAddr >= 0x6B00) && (usAddr < 0x6B80)){
				usAddr += 0x80;
			}
		/* SbrTim */
			else if((usAddr >= 0x6F00) && (usAddr < 0x6F80)){
				usAddr += 0x80;
			}
		/* SbrParam */
			else if((usAddr >= 0x7000) && (usAddr < 0x7800)){
				usAddr += 0x800;
			}
		}
		else if(usAddr < 0xC000){
			if((usAddr >= 0xA000) && (usAddr < 0xB000)){
				usAddr += 0x1000;
			}
		}
		*peCh = LCDGU_AB;
	}/* if(*peCh == LCDGU_CD) */
	
	return usAddr;
}


/**
 * @brief	ROM LOAD CRCチェック子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdGuChkCrcForRomLoad( void )
{
	dResult_e		eResult = S_SUCCESS;
	uint16			usDat;
	dFrdRegVar_t	atDats[8];
	uint8			i, j;
	/* int_crc_error[3]: EEPROM CRCエラー(全体のCRCチェック) */
	eResult = eFrdLcdGuRegR(LCDGU_AB, 0x01, &usDat);
	if(eResult == S_SUCCESS){
	/* ここはGuava新規なので、エラーログの記載なし */
		if((usDat & 0x08) == 0x08){
			eResult = S_FAILURE;
		}
	}
	
	/* reg_load_error_flag[63:0] : 各ローダーのCRCエラー */
	atDats[0].usAddr = LCDGU_REGADDR_ETC + 0x20;
	
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, 8, atDats);
	if(eResult == S_SUCCESS){
		for(i=0; i<8; i++){
			if(atDats[i].usVal != 0){
			/* エラーの場合、ログを残す */
				for(j=0; j<8; j++){
					if(atDats[i].usVal & (1<<j)){
						eLcdGuSetErrLog(2, i*8+j, 0); /* ucErrCode, ucErrBlock, usAddr */
					}
				}
				eResult = S_FAILURE;
			}
		}
	}
	
	/* init_load_error_flag[0] : HeaderのCRCエラー */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x28, &usDat);
	if(eResult == S_SUCCESS){
		if((usDat & 0x01) == 0x01){
		/* エラーの場合、ログを残す */
			eLcdGuSetErrLog(1, 0, 0); /* ucErrCode, ucErrBlock, usAddr */
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
static dResult_e eLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn, flag fOffset )
{
	dResult_e		eResult = S_SUCCESS;
	flag			f16bit;
	uint16			usWordLen;
	dFrdRegVar_t	atSetUpDats[6];
	uint8 			ucParam = 0;
	uint16			usRDat;
	uint8			ucCnt = 0;

	f16bit = fLcdGuRegDepth16bit(uiRegAddr);
	if(f16bit)	usWordLen = (usByteLen >> 1);
	else		usWordLen =  usByteLen;
	
	eResult = eLcdGuRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if( fOffset ) uiRomAddr += uiLcdGuRomOffset;				/* ROM 8Mbit対応 */
	
	/* ロード元ROMアドレスの設定 */
	atSetUpDats[0].usVal = (uint16)((uiRomAddr >> 8) & 0xFF);	/* ROMアドレス中位[15:8] */
	atSetUpDats[1].usVal = (uint16)(uiRomAddr & 0xFF);			/* ROMアドレス下位[7:0]  */
	atSetUpDats[0].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x10);	/* レジスタアドレス設定 */
	atSetUpDats[1].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x11);	/* レジスタアドレス設定 */

	/* ロード先レジスタアドレスの設定 */
	atSetUpDats[2].usVal = (uint16)((uiRegAddr >> 8) & 0xFF);	/* ロード先レジスタアドレス上位[15:8]  */
	atSetUpDats[3].usVal = (uint16)(uiRegAddr & 0xFF);			/* ロード先レジスタアドレス下位[7:0] */
	atSetUpDats[2].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x12);	/* レジスタアドレス設定 */
	atSetUpDats[3].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x13);	/* レジスタアドレス設定 */

	/* ロードデータ長の設定 */
	atSetUpDats[4].usVal = (uint16)((usWordLen >> 8) & 0xFF);	/* データ長上位[15:8]  */
	atSetUpDats[5].usVal = (uint16)(usWordLen & 0xFF);			/* データ長下位[7:0] */
	atSetUpDats[4].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x14);	/* レジスタアドレス設定 */
	atSetUpDats[5].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x15);	/* レジスタアドレス設定 */

	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 6, atSetUpDats);		/* レジスタへの書き込み */

	/* マニュアルロードVフェッチOFF */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x3f, &usRDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3f, (usRDat | 1));

	/* ロードスタートbitを一旦ゼロに */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x17, 0);

	ucParam |= ((f16bit << 1) | (fCrcEn << 2));

	/* ROMアドレス上位[19:16] + CRC Enable/Disable + bit幅(8bit or 16bit) + ロードスタートビット */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x17, ((uiRomAddr >> 12) & 0xF0) | ucParam | 1);

	/* ビジーチェック */
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC+0x2A, &usRDat);
		if((usRDat & 1) == 1){
//			eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] MANUAL LOAD BUSY COUNT = %d\n", ucCnt);
			break;/* 立っていればビジーでない */
		}
		ucCnt++;
		if(ucCnt > 100){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] MANUAL LOAD ERROR !!!!!\n");
#endif //TURNKEY1
			break;
		}
		MDrv_Timer_Delayms(1);
	}
	
	/* 転送エラー(CRCエラーなど)チェック */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC+0x29, &usRDat);
	if(usRDat & 1){
	/* エラーの場合、ログを残す */
		eLcdGuSetErrLog( 3, 0, (uint16)uiRegAddr ); /* ucErrCode, ucErrBlock, usAddr */
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
static flag fLcdGuRegDepth16bit( uint32 uiAddr )
{
	flag f16bit = TRUE;/* 初期値：16bit幅 */
	
	/* 090409 ohashi追加 */
	if((uiAddr >= LCDGU_REGADDR_OSD) && (uiAddr < LCDGU_REGADDR_IMC)){
	/* 0x400-0x600 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if((uiAddr >= LCDGU_REGADDR_DP) && (uiAddr < LCDGU_REGADDR_CS_SUB)){
	/* 0xA00 - 0xC00 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if((uiAddr >= LCDGU_REGADDR_GAMLUTR) && (uiAddr < LCDGU_REGADDR_SBRPARAM)){
	/* 0x4000 - 0x7000 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if( (uiAddr >= GU_REGADDR_FRC) && (uiAddr < LCDGU_REGADDR_FSB) ){
	/* 0x8000 - 0x9000 */
		f16bit = FALSE;/* 8bit幅 */
	}
	else if( (uiAddr >= LCDGU_REGADDR_BDLUT) && (uiAddr < 0xC000) ){
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
static dResult_e eLcdGuRomStatusChk( uint16 *pusStatus )
{
	uint16	  usStatus;
	uint16	  usWaitCnt = 0;
	dResult_e eResult = S_SUCCESS;
	
	while(1){
		/* ステータスレジスタ読み込みコマンドを発行 */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_RDSR);
		
		/* ROM → LCDCレジスタ の読み出し時間は、EEPCLK(4.6MHz)で16clk程度(4us程度)なので
		   ここでWaitは入れなくてもレジスタ値は確定しています */
		
		/* ステータスレジスタの読み込み */
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x35, &usStatus);
		if((usStatus & 0x01) != 0){/*ROM書き込み中か否か*/
			usWaitCnt++;
			if(usWaitCnt == 100){
				eResult = S_FAILURE;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
				eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM ACCESS TIMEOUT ERROR!!!!!!!!\n");
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
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM STATUS REGISTER = %0x\n", usStatus);
#endif //TURNKEY1
	
	if(pusStatus != NULL){
		*pusStatus = usStatus;
	}
	return eResult;
}


/**
 * @brief	TPDA, TPDB 設定用子関数
 * @param	dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdGuSetTpDat( dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdRegVar_t	atDats[12];
	
	atDats[0].usAddr = LCDGU_REGADDR_DP +0xD;
	
	if((ptTpda == NULL) && (ptTpdb == NULL)) return S_SPEC_ERROR;
	
	/* 現状の値を取得 */
	eResult |= eFrdLcdGuRegRs(eCh, 12, atDats);
	
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
	eResult |= eFrdLcdGuRegWs(eCh, 12, atDats);
	
	return eResult;
}


/**
 * @brief	ROMライトプロテクトモード有効/無効切り替え子関数
 * @param	flag fWPMEn
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eLcdGuRomToWProtectMode( flag fWPMEn )
{
	uint16		usStatus;
	uint16		usBP, usData;
	dResult_e	eResult = S_SUCCESS;
	
	eResult |= eLcdGuRomStatusChk(&usStatus);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if((usStatus & LCDGU_ROM_STATUS_SRDW) != 0){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM SRDW BIT HI!!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	if( uiLcdGuRomSize == LCDGU_ROMSIZE_TOTAL_2M )	usBP = LCDGU_ROM_STATUS_BP10;	/* 2MbitROMデータの場合 */
	else  											usBP = LCDGU_ROM_STATUS_BP210;	/* 8MbitROMデータの場合 */
	
	if(fWPMEn == TRUE)	usData = usBP;	/* プロテクト設定 */
	else				usData = 0;		/* プロテクト解除設定 */
	
	if((usStatus & usBP) != usData){
	/* 所望の状態でない場合 */
		
		/* 書き込みデータをレジスタに設定 */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x40, usData);	/* WDATA_START */
		
		/* データ長を設定(念の為。。。) */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x36, 1);		/* LENGTH_L */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x37, 0);		/* LENGTH_H */

		/* 書き込みイネーブルコマンドを発行 */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WREN);

		/* ステータスレジスタ書き込みコマンドを発行 */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WRSR);
	}
	else{
	/* 所望の状態なので、何もしません */
	}
	
	eResult |= eLcdGuRomStatusChk(&usStatus);
	
	return eResult;
}


/**
 * @brief	仕向け・インチ別設定子関数
 * @param	dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	eFrdLcdGuGetRevInfo()を必ず先にコールしてください．
 * @memo	インチ毎にROM管理を行う予定なので、本子関数は基本的に仕向け毎設定です．
 */
static dResult_e eLcdGuGetRegionAndInchInfo( dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo )
{
	uint8 ucPnlSize = aucLcdGuRevInfo[FRDLCD_REVISION_INCHI];
	
	if(fGetRevInfo != TRUE) return S_FAILURE;

	switch(ucPnlSize){
		case 0x32:
		case 0x37:
		case 0x40:
		case 0x42:
		case 0x46:
		case 0x52:
		case 0x60:
			ptRegionAndInchInfo->eCpwbDirec  = LCDGU_CPWB_DIREC_ROTATION;
			break;
		case 0x65:
			ptRegionAndInchInfo->eCpwbDirec = LCDGU_CPWB_DIREC_NORMAL;
			break;
		case 0x70:																//二開発20121205
			ptRegionAndInchInfo->eCpwbDirec  = LCDGU_CPWB_DIREC_ROTATION;		//二開発20121205
			break;																//二開発20121205
		default:
			ptRegionAndInchInfo->eCpwbDirec = LCDGU_CPWB_DIREC_NORMAL;
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
static dResult_e eLcdGuSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e	eResult = S_SUCCESS;
	flag		fMiniL = (flag)(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	uint16		ausTmp[5];
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0xD0,&ausTmp[0]);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0xD0,&ausTmp[1]);
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x31,&ausTmp[2]);
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x2E,&ausTmp[3]);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x2E,&ausTmp[4]);
	ausTmp[0] &= 0xFF7F;
	ausTmp[1] &= 0xFF7F;
	ausTmp[2] &= 0xFFFB;
	ausTmp[3] &= 0xFFDF;
	ausTmp[4] &= 0xFFDF;
	
	if(fMiniL == FALSE){
		/* GuavaではPPDSがないんよ */
		return S_FAILURE;
	}else{
	/* miniLVDS */
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0xD0,	((aucLcdGuTrnOvr[0][eTrnOvr] << 7) | ausTmp[0]));
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_DP +0xD0,	((aucLcdGuTrnOvr[1][eTrnOvr] << 7) | ausTmp[1]));
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0x31,	((aucLcdGuTrnOvr[2][eTrnOvr] << 2) | ausTmp[2]));
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x00,		aucLcdGuTrnOvr[3][eTrnOvr]);
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x00,		aucLcdGuTrnOvr[4][eTrnOvr]);
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0x2E,	((aucLcdGuTrnOvr[5][eTrnOvr] << 5) | ausTmp[3]));
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_DP +0x2E,	((aucLcdGuTrnOvr[6][eTrnOvr] << 5) | ausTmp[4]));
	}
	
	return eResult;
}


/**
 * @brief	SBR設定子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	ソースブロック反転(SBR)に関連するパラメータ(SBR PARAM, SBR GHOST LUT1, LUT2, CCK LUT)
 *          の切り替えをマニュアルロードで行います。
 */
static dResult_e eLcdGuSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr, uiCrcAddr;
	dFrdRegVar_t atDats[3] = {{0x165d, 0x1}, {0x165e, 0x1}, {0x165f, 0x0}};/* SBR GHOST LUT UPDATE用 */
	
	/* SBR PARAM (温度レベル毎のパラメータはなくなった) */
	eResult |= eLcdGuGetSbrParamRomAddr(eTrnOvr, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBRPARAM +0x00, LCDGU_ROMSIZE_SBRPARAM, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	/* SBR GHOST LUT1 */
	eResult |= eLcdGuGetGhostLut1RomAddr(eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* → AB側 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x100, LCDGU_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* → CD側(AB側と同じデータ。よってCRC値も同じ) */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x700, LCDGU_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	/* SBR GHOST LUT2(→ AB側) */
	eResult |= eLcdGuGetGhostLut2RomAddr(LCDGU_AB, eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* 090416 ohashi: SIZE-10でいいのかまだ不明 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x5DA, LCDGU_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* SBR GHOST LUT2(→ CD側) */
	eResult |= eLcdGuGetGhostLut2RomAddr(LCDGU_CD, eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC値の転送 */
	/* 090416 ohashi: SIZE-10でいいのかまだ不明 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0xBDA, LCDGU_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* SBR GHOST LUT UPDATE */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 3, atDats);
	eResult |= eFrdLcdGuRegWs(LCDGU_CD, 3, atDats);

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	return eResult;
}

#ifdef DEBUG_LCDGU_MANULOAD_SBR
/**
 * @brief	MNLデバッグ出力子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static void vLcdGuDbgMnl( void )
{
	uint16 usReadData;
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] CRC_EXP_VAL  = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x2B, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] CRC_CALC_VAL = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x29, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] ERROR BIT    = %0x\n", usReadData);
#endif //TURNKEY1
	return;
}
#endif

/**
 * @brief	SBR PARAMマニュアルロード用子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_SBRPARAM;
	uint32		uiCrcAddr	= 0x210;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += LCDGU_ROMSIZE_SBRPARAM;
			uiCrcAddr += 1;
			break;
		default:
			break;
	}
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT1マニュアルロード用子関数
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_GHOSTLUT1;
	uint32		uiCrcAddr	= 0x230;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ( LCDGU_ROMSIZE_GHOSTLUT1 * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDGU_ROMSIZE_GHOSTLUT1 * ucLvl);
	uiCrcAddr += ucLvl;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT2マニュアルロード用子関数
 * @param	dFrdLcdArCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuGetGhostLut2RomAddr( dFrdLcdGuCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr)
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_GHOSTLUT2;
	uint32		uiCrcAddr	= 0x240;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_NORMAL:
			break;
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
			uiRomAddr +=  (LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8);
			uiCrcAddr += (2*8);
			break;
		case FRDLCD_TRN_OVR_MIRROR:
			uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8) * 2);
			uiCrcAddr += ((2*8) * 2);
			break;
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8) * 3);
			uiCrcAddr += ((2*8) * 3);
			break;
		default:
			break;
	}
	
	uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * ucLvl) + (LCDGU_ROMSIZE_GHOSTLUT2 * eCh));
	uiCrcAddr += ((2 * ucLvl) + eCh);
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	QS 周波数、温度設定用子関数
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucLvl
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucLvl )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] QS FREQ = %0d\n", eInputFreq);
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] QS TEMP = %0d\n", ucLvl);
#endif //TURNKEY1

	eResult = eLcdGuGetQsLutRomAddr(eInputFreq, ucLvl, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);						/* CRC値の転送 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_QSLUT +0x00, LCDGU_ROMSIZE_QSLUT, TRUE, TRUE);	/* データの転送 */

#ifdef DEBUG_LCDGU_MANULOAD_QS
	vLcdGuDbgMnl();
#endif

	return eResult;
}


/**
 * @brief	QS LUTマニュアルロード用子関数
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_QSLUT;
	uint32		uiCrcAddr	= 0x200;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_60HZ:
			uiRomAddr += (LCDGU_ROMSIZE_QSLUT * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDGU_ROMSIZE_QSLUT * ucLvl);
	uiCrcAddr += ucLvl;
	
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
static dResult_e eLcdGuSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usCrcCal, usCrcExp;
	
	if( ucErrCode == 1 ){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x06, &usCrcExp);/* CRC期待値(ヘッダロード時) */
	}
	else{
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usCrcExp);/* CRC期待値(マニュアルロード時) */
	}
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x2B, &usCrcCal);/* CRC演算値 */
	
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucErrCode		= ucErrCode;		/* エラーコード  */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucErrBlock	= ucErrBlock;		/* ロードエラーブロック番号 */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].usAddr		= usAddr;			/* 対応レジスタアドレス */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucCrcExp		= (uint8)usCrcExp;	/* CRC期待値 */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucCrcCal		= (uint8)usCrcCal;	/* CRC演算値 */
	
	ucLcdGuErrInfoInCnt++;
	ucLcdGuErrInfoInCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	
	return eResult;
}


/**
 * @brief	ROM書き込み用子関数
 * @param	uint32 uiAddr, uint16 usLength, uint8 *pucDats
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats )
{
	dResult_e		eResult;
	dFrdRegVar_t	atSetUpDats[4];
	dFrdRegVar_t	atWDats[LCDGU_ROM_BURST_LEN_W];
	int i;
	
	/* ここから単なる引数チェック */
	if(usLength > LCDGU_ROM_BURST_LEN_W)				return S_SPEC_ERROR;
	if(usLength > LCDGU_ROM_PAGE_SIZE_2M)				return S_SPEC_ERROR;
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
	if((uiAddr + usLength) > uiLcdGuRomSize)			return S_SPEC_ERROR;
#endif
	/* ここまで単なる引数チェック */
	
	eResult = eLcdGuRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	atSetUpDats[0].usVal = LCDGU_ROM_CMD_WREN;			/* 書き込みイネーブル設定 */
	atSetUpDats[1].usVal = (uiAddr & 0xFF);				/* ROMアドレス下位 */
	atSetUpDats[2].usVal = ((uiAddr >> 8) & 0xFF);		/* ROMアドレス中位 */
	atSetUpDats[3].usVal = ((uiAddr >> 16) & 0xFF);		/* ROMアドレス上位  */
	for(i=0; i<4; i++){
		atSetUpDats[i].usAddr = LCDGU_REGADDR_ETC +0x30 +i;	/* レジスタアドレス設定 */
	}
	/* WRENコマンド、ROMアドレスを設定 */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 4, atSetUpDats);
	
	atSetUpDats[0].usVal = (usLength & 0xFF);			/* 書き込みデータ長下位 */
	atSetUpDats[1].usVal = ((usLength >> 8) & 0xFF);	/* 書き込みデータ長上位 */
	atSetUpDats[0].usAddr = LCDGU_REGADDR_ETC +0x36;	/* レジスタアドレス設定 */
	atSetUpDats[1].usAddr = LCDGU_REGADDR_ETC +0x37;	/* レジスタアドレス設定 */
	/* データ長を設定 */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 2, atSetUpDats);
	
	for(i=0; i<usLength; i++){
		atWDats[i].usVal  = (uint16)pucDats[i];			/* 書き込みデータ設定 */
		atWDats[i].usAddr = LCDGU_REGADDR_ETC +0x40 +i;	/* レジスタアドレス設定 */
	}
	
	/* 書き込みデータバッファに設定 */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, usLength, atWDats);
	
	/* WRITEコマンド発行 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WRITE);
	
	return eResult;
}


/**
 * @brief	リロード用子関数
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @memo	
 */
static dResult_e eLcdGuReloadAll( uint8 ucPnlSizeNo )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usAddr = ucPnlSizeNo * 4;
	uint16		usDat;
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3A, 0x01 );				/* リロードアドレス中位 */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3B, usAddr );			/* リロードアドレス上位 */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, (usDat & 0x7F));	/* リロードビット→０ */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, (usDat | 0x80));	/* リロードビット→１ */
	
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
static dResult_e eLcdGuGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr )
{
	dResult_e	 eResult = S_SUCCESS;
	dFrdRegVar_t atRDat[FRDLCD_REVISION_DATA_MAX-1];
	uint16		 usCrcExp, i;
	
	if(pucRevInfo == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucRevInfo = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult |= eLcdGuRomManualLoad(uiRomAddr +0xF, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);					/* CRC値の転送 */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_ETC +0x140, FRDLCD_REVISION_DATA_MAX-1, TRUE, TRUE);/* データの転送 */
#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	/* データ読み込み */
	atRDat[0].usAddr = LCDGU_REGADDR_ETC +0x140;
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, FRDLCD_REVISION_DATA_MAX-1, atRDat);
	for(i=0; i<FRDLCD_REVISION_DATA_MAX-1; i++){
		pucRevInfo[i] = (uint8)atRDat[i].usVal;
	}
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usCrcExp);
	pucRevInfo[FRDLCD_REVISION_DATA_MAX-1] = (uint8)usCrcExp;
	
	return eResult;
}
/* end of file */
