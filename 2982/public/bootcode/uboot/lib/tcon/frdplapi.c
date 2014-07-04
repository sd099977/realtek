/**
 * @file frdplapi.c
 *
 * @brief PlaiceFRC部制御
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

#include <tcon/frdapi.h>	/* dFrdRegVar_tのためやけど、これをincludeするかは暫定 */
#include <tcon/frdplapi.h>
#include <tcon/frdlcdapi.h>	/* 090410 ohashi: frdlcdplapi.hだけではコンパイルが通らないので */
#include <tcon/frdlcdplapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/
#define PL_ROMADDR_SYSTEM	0x3F400
#define PL_ROMADDR_PFLUT50	0x3F200
#define PL_ROMADDR_PFLUT60	0x3F000
#define PL_ROMSIZE_SYSTEM	0x40
#define PL_ROMSIZE_PFLUT	0x121


#define PL_CRCADDR_SYSTEM	0x292
#define PL_CRCADDR_PFLUT	0x290
/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
/* const */
/* 090512 ohashi: インチサイズで値が異なる */
const static uint8 ucAdTbl[FRDLCD_PNL_NUMMAX][7] = {			//sakata20110921
/* 32inch */	{89, 105, 115, 125, 135, 145, 154},				//sakata20110921
/* 40inch *///初期値	{87, 106, 118, 130, 141, 153, 165},		//sakata20110921
/* 40inch */	{41,  46,  48,  50,  53,  54,  56},//DS5用		//sakata20110921
/* 46inch *///初期値	{88, 106, 116, 127, 138, 148, 159},		//sakata20110921
/* 46inch */	{42,  46,  49,  51,  53,  55,  56},	//DS5用		//sakata20110921
/* 52inch */	{94, 112, 123, 133, 144, 155, 166},				//sakata20110921
/* 60inch *///初期値	{97, 116, 128, 141, 155, 168, 183},		//sakata20110921
/* 60inch */	{43,  47,  49,  51,  53,  55,  57},//DS5用		//sakata20110921
};																//sakata20110921


static dFrdPlInternalDat_t tFrcInternalDat;

static dFrdInputFreq_e	eCurrentInputFreq	= FRD_INPUT_FREQ_60HZ;
static flag				fCurrentFreeRunEn	= FALSE;
static uint8			ucCurrentLvl		= 4;
static flag				fCurrentMode		= TRUE;
static flag				fCurrentStill		= FALSE;
static flag				fCurrentModeChk		= FALSE;
static flag				fCurrentDemoMode	= FALSE;
/* 090626 ohashi */
static dFrdLcdPnlSize_e ePnlSize = FRDLCD_PNL_46;

static uint8 ucNegCnt = 0;
static uint8 ucPosCnt = 0;

/* 090701 ohashi */
static uint16 aucFrcParamChg[3];
static uint8  aucFrdRevInfo[FRDLCD_REVISION_DATA_MAX];

/* **
 * ** prototype
 * **/
static dResult_e ePlEntryChk( void );
static dResult_e ePlRegUpd( void );
static dResult_e ePlGetSystemRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e ePlGetPfLutRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static uint8 ucPlChgTempToLvl( dFrdLcdPnlSize_e	eSize, uint8 ucTemp );
static dResult_e ePlSetPfLutData( dFrdInputFreq_e eInputFreq );
/* **
 * ** func
 * **/

/*!
********************************************************************************
** @brief	汎用レジスタ連続書込みAPI (FRC側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDatas	: 書込みデータ配列(型定義: dFrdRegVar_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			レジスタ数は256個までしか書込めません。
** @note
*******************************************************************************/
dResult_e eFrdPlRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;


#ifdef TURNKEY1
	uint32 i;
	uint16 tmp_addr;
	
	for( i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDatas[0].usAddr + (uint16)i;
		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDatas[i].usVal);

		if( eResult == S_FAILURE )	break;
	}
#else //TURNKEY1
	const void	*pvDevice;
	
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, iRegNum, ptDatas );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ連続読込みAPI (FRC側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDatas	: 読込みデータ配列(型定義: dFrdRegVar_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			レジスタ数は256個までしか読込めません。
** @note
*******************************************************************************/
dResult_e eFrdPlRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32		i;
	uint16		tmp_addr;
	

	for(  i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDatas[0].usAddr + (uint16)i;
		eResult = eI2CRead( IIC_SLV_ADDR_TCON, tmp_addr, &(ptDatas[i].usVal));

		if( eResult == S_FAILURE )	break;
	}

#else //TURNKEY1
	const void	*pvDevice;
	
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, iRegNum, ptDatas);
	eAdvClose( pvDevice );
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ単一書込みAPI (FRC側)
** @param	usAddr	: アドレス指定	(型定義: uint16)
** @param	usVal	: 書込み値	(型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlRegW( uint16 usAddr, uint16 usVal )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
	eResult = eI2CWrite( IIC_SLV_ADDR_TCON, usAddr, usVal );
#else //TURNKEY1
	const void	*pvDevice;
	dFrdRegVar_t tData;
	
	tData.usAddr = usAddr;
	tData.usVal  = usVal;
	
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ単一読込みAPI (FRC側)
** @param	usAddr	: アドレス指定			(型定義: uint16)
** @param	pusVal	: 読込み値のポインタ	(型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlRegR( uint16 usAddr, uint16 *pusVal)
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	const void	*pvDevice;
	dFrdRegVar_t tData;
#endif //TURNKEY1

	if(pusVal == NULL) return S_SPEC_ERROR;

#ifdef TURNKEY1
	eResult = eI2CRead( IIC_SLV_ADDR_TCON, usAddr, pusVal );
#else //TURNKEY1
	tData.usAddr = usAddr;
	
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
	
	*pusVal = tData.usVal;
#endif //TURNKEY1
	return eResult;
}


/* 内部変数格納箱 */
static dFrdPlArea3TestPtn_t	tArea3TestPtn;
static dFrdPlMovTestPtn_t	tMovTestPtn;
static dFrdPlArea3Speed_t	tArea3Speed;
static dFrdPlArea3Mov_t		tArea3Mov;
/*!
********************************************************************************
** @brief	初期化設定API (FRC側)
** @param	eInputFreq		: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlInit( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	uint16 i;
	dFrdRegVar_t atTmp[17];
	
	eResult |= eFrdLcdPlGetSize(&ePnlSize);
	
	eResult |= eFrdLcdPlGetRevInfo(aucFrdRevInfo);
	/* 090701 ohashi: 3rdMethodパラメータ変更をソフトで対応 */
	if((aucFrdRevInfo[FRDLCD_REVISION_YEAR_L] <= 0x09) && (aucFrdRevInfo[FRDLCD_REVISION_MONTH] <= 0x06)){
		/* 090626 ohashi 3rdMethodパラメータ変更(仕向けやインチサイズで異なる) */
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x151, 0x04);
#if ((PL_REGION_INFO == PL_RIGION_US1) || \
	 (PL_REGION_INFO == PL_RIGION_EU1) || \
	 (PL_REGION_INFO == PL_RIGION_AS1))
		if(ePnlSize == FRDLCD_PNL_40)	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, 0x00);
		else							eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, 0x03);
#endif
	/* 090701 ohashi: 3rdMethodパラメータ変更はROMで吸収 */
	}else{
		eResult |= eFrdPlRegR(PL_REGADDR_FRC+0x151, &aucFrcParamChg[0]);
		eResult |= eFrdPlRegR(PL_REGADDR_FRC+0x11d, &aucFrcParamChg[1]);
		eResult |= eFrdPlRegR(PL_REGADDR_FRC+0x104, &aucFrcParamChg[2]);
	}
	
	/* 周波数切替 */
	eResult |= eFrdPlSetOutFreq(eInputFreq);
	
	/********************/
	/* 内部変数の初期化 */
	/********************/
	eCurrentInputFreq	= eInputFreq;
	fCurrentFreeRunEn	= FALSE;
	ucCurrentLvl		= 4;
	fCurrentMode		= TRUE;
	fCurrentStill		= FALSE;
	fCurrentModeChk		= FALSE;
	fCurrentDemoMode	= FALSE;
	
	ucNegCnt = 0;
	ucPosCnt = 0;
	
	/*-------------------*/
	
	/* 箱詰め(前準備) */
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn	= &tArea3TestPtn;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn		= &tMovTestPtn;

	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed	= &tArea3Speed;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov	= &tArea3Mov;

	/* テストパターン詳細設定状態を初期化 */
	for(i=0; i<15; i++)	atTmp[i].usAddr = PL_REGADDR_FRC+0x210+i;
	eResult |= eFrdPlRegRs(15, atTmp);
	
	/* tArea3TestPtn */
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea2Y = ((atTmp[6].usVal & 0x07) << 8) | (atTmp[7].usVal & 0xff);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea3Y = ((atTmp[8].usVal & 0x07) << 8) | (atTmp[9].usVal & 0xff);
	
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea1Speed = (uint8)atTmp[10].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea2Speed = (uint8)atTmp[11].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea3Speed = (uint8)atTmp[12].usVal;
	
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea1Mov = (dFrdPlArea3Mov_e)(atTmp[13].usVal & 0x03);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea2Mov = (dFrdPlArea3Mov_e)((atTmp[13].usVal & 0x0c) >> 2);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea3Mov = (dFrdPlArea3Mov_e)((atTmp[13].usVal & 0x30) >> 4);
	
	/* tMovTestPtn */
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->fQsMovLR		= (flag)atTmp[0].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucQsMovSpeed	= (uint8)atTmp[1].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucHScroll		= (uint8)atTmp[4].usVal;
	
	/* 2010.03.29 ROM変更は間に合わない為、ソフトで対応。。。 */
	if( ( ( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x52 ) || ( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x46 ) ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_MISC]==0x06 ) &&
#if 0
		( aucFrdRevInfo[FRDLCD_REVISION_YEAR_L]==0x10 ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_MONTH]==0x03 ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_DAY]==0x03 ) &&
#endif
		( aucFrdRevInfo[FRDLCD_REVISION_VER]==0x01 )
	)
	{
		eFrdPlRegW(PL_REGADDR_FRC+0x106, 0x0002);
		/* アップデート(0x8000を1)は、この後コールされるeFrdPlSetModeで行われることを前提として、ここでは行いません */
	}
	
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	スタンバイ設定API (FRC側)
** @param	fPipelineEn	: スタンバイ(パイプライン)設定, 
**						TRUE = ON, FALSE = OFF(スタンバイ状態) (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlStandby( flag fPipelineEn )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp;
	
	eResult  = eFrdPlRegR(0xB5, &usTmp);
	usTmp &= 0xFFFD;
	usTmp |= (uint16)fPipelineEn << 1;
	eResult |=  eFrdPlRegW(0xB5, usTmp);

	return eResult;
}


/*!
********************************************************************************
** @brief	倍速モード設定API
** @param	fFrcEn	: 倍速モード設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			強制ONができるよう、温度レベルを考慮しない構成に変更した。
** @note
*******************************************************************************/
dResult_e eFrdPlSetMode( flag fFrcEn )
{
	dResult_e eResult = S_SUCCESS;
#if 0	
	if(((3 <= ucCurrentLvl) && (ucCurrentLvl <= 7)) && (fCurrentStill == FALSE)){
		eResult |= ePlEntryChk();
		
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, (uint16)fFrcEn);
		
		eResult |= ePlRegUpd();
	}
	fCurrentMode = fFrcEn;
#else
	eResult |= ePlEntryChk();
	
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, (uint16)fFrcEn);
	
	eResult |= ePlRegUpd();
	
	fCurrentMode = fFrcEn;
#endif	
	return eResult;
}


/*!
********************************************************************************
** @brief	倍速モード状態取得API
** @param	pfFrcStatus	: 倍速モード状態を示すフラグ (型定義: flag *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			工程メニュー"FRC状態取得時に使用します。
** @note
**			Plaiceなので、PFの状態です。\n
**			SetModeの指定状態(内部変数)を取得しています。
*******************************************************************************/
dResult_e eFrdPlGetMode( flag *pfFrcStatus )
{
	*pfFrcStatus = fCurrentMode;
	
	return S_SUCCESS;
}


#define FRM_FRD_FULL_HD_W 1920
#define FRM_FRD_FULL_HD_H 1080
/*!
********************************************************************************
** @brief	画面端OFF設定API
** @param	ptEdgeFrame	: 領域指定 (型定義: dFrdFrame *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	指定矩形領域の外側の3rdMethodをOFF。(上側領域、下側領域および、
**			右or左側領域の３領域。右左領域の同時マスクは無し) 
**			
*******************************************************************************/
dResult_e eFrdPlSetEdge( dFrdFrame_t *ptEdgeFrame )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t tEdgeFrame;
	
	/* ひとつでも満たさない場合 → マスク有り */
	if( ( ptEdgeFrame->usXPos != 0 ) ||
		( ptEdgeFrame->usYPos != 0 ) ||
		( ptEdgeFrame->usWidth != FRM_FRD_FULL_HD_W ) ||
		( ptEdgeFrame->usHeight != FRM_FRD_FULL_HD_H ) ){
	/* 3領域 ( ["コの字型"＝上,下,右] or [逆"コの字型"＝上,下,左] ) マスクON */
		
		/* 指定領域の上側をマスク(マスク領域１) */
		tEdgeFrame.usXPos	= 0;
		tEdgeFrame.usYPos	= 0;
		tEdgeFrame.usWidth	= FRM_FRD_FULL_HD_W;
		tEdgeFrame.usHeight	= ptEdgeFrame->usYPos;
		eResult = eFrdPlSetMask( 1, TRUE, &tEdgeFrame );
		
		
		/* 指定領域の下側をマスク(マスク領域２) */
		tEdgeFrame.usXPos	= 0;
		tEdgeFrame.usYPos	= ptEdgeFrame->usYPos + ptEdgeFrame->usHeight;
		tEdgeFrame.usWidth	= FRM_FRD_FULL_HD_W;
		tEdgeFrame.usHeight	= FRM_FRD_FULL_HD_H - tEdgeFrame.usYPos;
		eResult = eFrdPlSetMask( 2, TRUE, &tEdgeFrame );
		
		
		/* 指定領域の右/左側をマスク(マスク領域３) */
		if( ptEdgeFrame->usXPos == 0 ){
		/* 右側 */
			tEdgeFrame.usXPos	= ptEdgeFrame->usWidth;
			tEdgeFrame.usWidth	= FRM_FRD_FULL_HD_W - tEdgeFrame.usXPos;
		}
		else{
		/* 左側 */
			tEdgeFrame.usXPos	= 0;
			tEdgeFrame.usWidth	= ptEdgeFrame->usXPos;
		}
		tEdgeFrame.usYPos	= 0;
		tEdgeFrame.usHeight	= FRM_FRD_FULL_HD_H;
		eResult = eFrdPlSetMask( 3, TRUE, &tEdgeFrame );
	}
	else{
	/* 3領域マスクOFF */
		eResult = eFrdPlSetMask( 1, FALSE, NULL );
		eResult = eFrdPlSetMask( 2, FALSE, NULL );
		eResult = eFrdPlSetMask( 3, FALSE, NULL );
	}
	
	return eResult;
}


/* 最大マスク個数は？？ */
/*!
********************************************************************************
** @brief	倍速モードマスク設定API
** @param	ucMaskNo	: マスク番号指定 [1-4] (型定義: uint8)
** @param	fMaskEn	: マスク設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @param	ptMaskFrame	: 領域指定 (型定義: dFrdFrame *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t tTmpFrame;
	uint16 usTmp, i;
	dFrdRegVar_t atTmp[8];
	
	if((ucMaskNo == 0) || (ucMaskNo > 4))	return S_FAILURE;
	
	/* REGUPDの確認 */
	eResult = ePlEntryChk();
	
	/* 領域指定 */
	if(ptMaskFrame != NULL){
		tTmpFrame.usXPos	= ((int32)ptMaskFrame->usXPos >> 2) & 0x1FF;
		tTmpFrame.usYPos	= ((int32)ptMaskFrame->usYPos >> 2) & 0x1FF;
		/* 丸められた左,上側の幅,高さを加え、かつ丸められないようにする */
		tTmpFrame.usWidth	= ((int32)(ptMaskFrame->usWidth  + (ptMaskFrame->usXPos % 4) + 3) >> 2) & 0x1FF;
		tTmpFrame.usHeight	= ((int32)(ptMaskFrame->usHeight + (ptMaskFrame->usYPos % 4) + 3) >> 2) & 0x1FF;
		
		if(( 0x1E0 < ((tTmpFrame.usXPos) + (tTmpFrame.usWidth))) ||( 0x21C < ((tTmpFrame.usYPos) + (tTmpFrame.usHeight)))){
			return S_SPEC_ERROR;
		}
		atTmp[0].usVal = (uint16)((tTmpFrame.usXPos & 0x100) >> 8);
		atTmp[1].usVal = (uint16)(tTmpFrame.usXPos & 0xff);
		atTmp[2].usVal = (uint16)((tTmpFrame.usYPos & 0x100) >> 8);
		atTmp[3].usVal = (uint16)(tTmpFrame.usYPos & 0xff);
		atTmp[4].usVal = (uint16)((tTmpFrame.usWidth & 0x100) >> 8);
		atTmp[5].usVal = (uint16)(tTmpFrame.usWidth & 0xff);
		atTmp[6].usVal = (uint16)((tTmpFrame.usHeight & 0x100) >> 8);
		atTmp[7].usVal = (uint16)(tTmpFrame.usHeight & 0xff);
		
		for(i=0; i<8; i++) atTmp[i].usAddr = PL_REGADDR_FRC+0x120 + 8*(ucMaskNo-1) +i;
		
		eResult |= eFrdPlRegWs(8, atTmp);
	}
	
	/* ON/OFF設定 */
	if(eFrdPlRegR(PL_REGADDR_FRC+0x11F, &usTmp) == S_FAILURE)	return S_FAILURE;
	usTmp &= ~((uint16)(0x01 << (ucMaskNo-1))) & 0x0F;
	usTmp |= (uint16)(fMaskEn << (ucMaskNo-1));
	
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11F, usTmp);
	
	/* REGUPD */
	eResult |= ePlRegUpd();
	
	return eResult;
}


static dFrdRegVar_t atCurrentQsBkg[6] = {
	{PL_REGADDR_FRC+0x20A, 0x00}, {PL_REGADDR_FRC+0x20B, 0x80},
	{PL_REGADDR_FRC+0x20C, 0x00}, {PL_REGADDR_FRC+0x20D, 0x80},
	{PL_REGADDR_FRC+0x20E, 0x00}, {PL_REGADDR_FRC+0x20F, 0x80},
};
/*!
********************************************************************************
** @brief	ミュート設定API
** @param	fMuteEn	: ミュート設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetMute( flag fMuteEn )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atQsBkg[6] = {
		{PL_REGADDR_FRC+0x20A, 0x00}, {PL_REGADDR_FRC+0x20B, 0x00},
		{PL_REGADDR_FRC+0x20C, 0x00}, {PL_REGADDR_FRC+0x20D, 0x00},
		{PL_REGADDR_FRC+0x20E, 0x00}, {PL_REGADDR_FRC+0x20F, 0x00},
	};

	/* REGUPDの確認 */
	eResult = ePlEntryChk();

	if(fMuteEn){
		/* 現状のレジスタ値read */
		eResult |= eFrdPlRegRs(6, atCurrentQsBkg);
		
		/* 黒 */
		eResult |= eFrdPlRegWs(6, atQsBkg);
		
		/* ベタ選択 */
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x201, FRD_TESTPTN_ALLOVER-1);
	}else{
		/* 色を元に戻す */
		eResult |= eFrdPlRegWs(6, atCurrentQsBkg);
	}
	
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x200, (uint16)fMuteEn);
	
	/* REGUPD */
	eResult |= ePlRegUpd();

	return eResult;
}


/*!
********************************************************************************
** @brief	テストパターン設定API (FRC側)
** @param	eTestPtn		: 表示モード選択 (型定義: dFrdTestPtn_e)
** @param	pvAdjTestPtn	: テストパターン詳細設定 (型定義: void *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Plaiceでは FRD_TESTPTN_QS(QSパターン) 及び FRD_TESTPTN_QS_BAR
**			 (QS測定用パターン)は搭載されていません。
** @note
*******************************************************************************/
dResult_e eFrdPlSetTestPtn( dFrdTestPtn_e eTestPtn, dFrdPlAdjTestPtn_t *ptAdjTestPtn )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTestPtnEn, i;
	dFrdRegVar_t atTmp[8];
	
	/* REGUPDの確認 */
	eResult = ePlEntryChk();
	
	/* 詳細設定 */
	if(ptAdjTestPtn != NULL){
		
		/* 水平3分割設定 */
		if(ptAdjTestPtn->ptArea3TestPtn != NULL){
			for(i=0; i<8; i++)	atTmp[i].usAddr = PL_REGADDR_FRC+0x216+i;
			
			atTmp[0].usVal = (ptAdjTestPtn->ptArea3TestPtn->usArea2Y & 0x700) >> 8;
			atTmp[1].usVal =  ptAdjTestPtn->ptArea3TestPtn->usArea2Y & 0xFF;
			atTmp[2].usVal = (ptAdjTestPtn->ptArea3TestPtn->usArea3Y & 0x700) >> 8;
			atTmp[3].usVal =  ptAdjTestPtn->ptArea3TestPtn->usArea3Y & 0xFF;
			atTmp[4].usVal = (uint16)ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea1Speed;
			atTmp[5].usVal = (uint16)ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea2Speed;
			atTmp[6].usVal = (uint16)ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea3Speed;
			atTmp[7].usVal = (uint16)((ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea1Mov & 0x03) |
									((ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea2Mov & 0x03) << 2) |
									((ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea3Mov & 0x03) << 4));
			
			eResult |= eFrdPlRegWs(8, atTmp);
			
			/* Internal登録 */
			if(eResult == S_SUCCESS){
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea2Y = ptAdjTestPtn->ptArea3TestPtn->usArea2Y;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea3Y = ptAdjTestPtn->ptArea3TestPtn->usArea3Y;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea1Speed = ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea1Speed;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea2Speed = ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea2Speed;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea3Speed = ptAdjTestPtn->ptArea3TestPtn->ptArea3Speed->ucArea3Speed;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea1Mov = ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea1Mov;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea2Mov = ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea2Mov;
				tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea3Mov = ptAdjTestPtn->ptArea3TestPtn->ptArea3Mov->eArea3Mov;
			}
		}
		
		/* 動画パターン移動方向/速度設定 */
		if(ptAdjTestPtn->ptMovTestPtn != NULL){
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x210, (uint16)ptAdjTestPtn->ptMovTestPtn->fQsMovLR);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x211, (uint16)ptAdjTestPtn->ptMovTestPtn->ucQsMovSpeed);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x214, (uint16)ptAdjTestPtn->ptMovTestPtn->ucHScroll);
			
			/* Internal登録 */
			if(eResult == S_SUCCESS){
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->fQsMovLR		= ptAdjTestPtn->ptMovTestPtn->fQsMovLR;
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucQsMovSpeed	= ptAdjTestPtn->ptMovTestPtn->ucQsMovSpeed;
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucHScroll		= ptAdjTestPtn->ptMovTestPtn->ucHScroll;
			}
		}
	}
	
	/* テストパターン選択 */
	if(eTestPtn != FRD_TESTPTN_OFF){
		if((FRD_TESTPTN_HVRAMP_ALTERNATE <= eTestPtn) && (eTestPtn <= FRD_TESTPTN_ALLOVER_ALTERNATE)){
			usTestPtnEn = 0x02;	/* 出力側のみ */
		}else{
			usTestPtnEn = 0x01;	/* 入力側のみ */
		}
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x201, (uint16)(eTestPtn-1));
		
		/* フリッカパターンの場合 */
		if((eTestPtn == FRD_TESTPTN_FLICKER_2H) || (eTestPtn == FRD_TESTPTN_FLICKER_1H)){
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x215, 0xd0);
		}
	}
	else{
		usTestPtnEn = 0x00;	/* 通常表示 */
		
		/* フリッカパターンレジスタ戻し(別に戻す必要はないが...) */
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x215, 0x00);
	}
	
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x200, usTestPtnEn);
	
	/* REGUPD */
	eResult |= ePlRegUpd();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	入力周波数毎の設定API
** @param	eInputFreq	: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetOutFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	/* パイプラインOFF */
	eResult = eFrdPlStandby(FALSE);

	/* パラメータload(システム関連全て) */
	eResult |= ePlGetSystemRomAddr(eInputFreq, &uiRomAddr, &uiCrcAddr);

	eResult |= eFrdLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE);
	eResult |= eFrdLcdPlRomManualLoad(uiRomAddr, PL_REGADDR_FRC +0x02, PL_ROMSIZE_SYSTEM, TRUE);
#if 0	
	/* 080729 ohashi: 欧州タイミング設定用 (北米も追加) */
#if ((FRCTM_REGION == RIGION_EU1) || (FRCTM_REGION ==  RIGION_US1))
	eResult |= eFrcLcdRegWriteZ(FRCTM_ADDR_SYSTEM +0x08, 0x0b);	/* Tbpv0 */
#endif
#endif
	/* FreeRun状態？ */
	if(fCurrentFreeRunEn) eResult |= eFrdPlRegW(PL_REGADDR_FRC +0x27, (uint16)fCurrentFreeRunEn);
	
	/* PF LUTのload */
	switch(eInputFreq){
		case FRD_INPUT_FREQ_48HZ:
		case FRD_INPUT_FREQ_50HZ:
			if(eCurrentInputFreq == FRD_INPUT_FREQ_60HZ){
				eResult |= ePlGetPfLutRomAddr(eInputFreq, &uiRomAddr, &uiCrcAddr);
				
				eResult |= eFrdLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdPlRomManualLoad(uiRomAddr, PL_REGADDR_FRC +0x300, PL_ROMSIZE_PFLUT, TRUE);
			}
			break;
		case FRD_INPUT_FREQ_60HZ:
			if(eCurrentInputFreq != FRD_INPUT_FREQ_60HZ){
				eResult |= ePlGetPfLutRomAddr(eInputFreq, &uiRomAddr, &uiCrcAddr);
				
				eResult |= eFrdLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdPlRomManualLoad(uiRomAddr, PL_REGADDR_FRC +0x300, PL_ROMSIZE_PFLUT, TRUE);
			}
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	/* 2010.03.29 ROM変更は間に合わない為、ソフトで対応。。。 */
	if( ( ( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x52 ) || ( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x46 ) ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_MISC]==0x06 ) &&
#if 0
		( aucFrdRevInfo[FRDLCD_REVISION_YEAR_L]==0x10 ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_MONTH]==0x03 ) &&
		( aucFrdRevInfo[FRDLCD_REVISION_DAY]==0x03 ) &&
#endif
		( aucFrdRevInfo[FRDLCD_REVISION_VER]==0x01 )
	)
	{
	/* 46型 or 52型 の場合のみ */
		eResult |= ePlSetPfLutData( eInputFreq );
	}
	
	eCurrentInputFreq = eInputFreq;
	
	/* パイプラインON */
	eResult |= eFrdPlStandby(TRUE);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	フリーラン設定API (FRC側)
** @param	fFreeRunEn	: フリーラン設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetFreeRun( flag fFreeRunEn )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp;
	
	/* 静止画モード確認 */
	eResult = eFrdPlRegR(PL_REGADDR_FRC+0x155, &usTmp);
	
	if(usTmp){	/* ON */
		eResult |= ePlEntryChk();
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x27, (uint16)fFreeRunEn);
		eResult |= ePlRegUpd();
	}else{		/* OFF */
		eResult |= eFrdPlStandby(FALSE);
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x27, (uint16)fFreeRunEn);
		eResult |= eFrdPlStandby(TRUE);
	}
	
	fCurrentFreeRunEn = fFreeRunEn;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	FRCステータスデータ取得API
** @param	pvFrcStatusDat	: FRCステータスデータ (型定義: dFrdPlInternalDat_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			各デバイスによって、ステータスデータ型が異なります。
** @note
*******************************************************************************/
dResult_e eFrdPlGetStatus( dFrdPlInternalDat_t *pvFrcStatusDat )
{
	/* 現状の内部管理変数をステータスデータとして返す */
	*pvFrcStatusDat = tFrcInternalDat;

	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	矩形描画設定API
** @param	fLineEn		:矩形描画設定．ONはTRUE、OFFはFALSE (型定義: flag)
** @param	eLineColor	:矩形領域の色指定 (型定義: dFrdLineColor_e)
** @param	ptLinePlea	:領域指定 (型定義: dFrdFrame_t)
**						変更がない場合は、ポインタをNULL設定する。\n
**						Xの範囲：0〜1919, Yの範囲：0〜1079．またXが0, Yが0の場合、Wの範囲： 0〜1920, Hの範囲：0〜1080
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlDrawLine( flag fLineEn, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atTmp[8];
	uint8 i;

	eResult = ePlEntryChk();

	/* 矩形領域設定 */
	if(ptLineArea != NULL){
		if(ptLineArea->usXPos + ptLineArea->usWidth > 1920 || 
		ptLineArea->usYPos + ptLineArea->usHeight > 1080){
			return S_SPEC_ERROR;
		}

		for(i=0; i<8; i++) atTmp[i].usAddr = PL_REGADDR_FRC+0x222+i;
		atTmp[0].usVal = ((ptLineArea->usXPos & 0x700) >> 8);
		atTmp[1].usVal = (ptLineArea->usXPos & 0xff);
		atTmp[2].usVal = ((ptLineArea->usYPos & 0x700) >> 8);
		atTmp[3].usVal = (ptLineArea->usYPos & 0xff);
		atTmp[4].usVal = ((ptLineArea->usWidth & 0x700) >> 8);
		atTmp[5].usVal = (ptLineArea->usWidth & 0xff);
		atTmp[6].usVal = ((ptLineArea->usHeight & 0x700) >> 8);
		atTmp[7].usVal = (ptLineArea->usHeight & 0xff);

		eResult |= eFrdPlRegWs(8, atTmp);
	}
	
	/* 矩形領域の色指定 */
	for(i=0; i<3; i++) atTmp[i].usAddr = PL_REGADDR_FRC+0x22a+i;
	switch(eLineColor){
		case FRD_LINE_COLOR_GRAY:
			atTmp[0].usVal = atTmp[1].usVal = atTmp[2].usVal = 0x08;
			break;
		case FRD_LINE_COLOR_BLUE:
			atTmp[0].usVal = atTmp[1].usVal = 0x00;
			atTmp[2].usVal = 0x0F;
			break;
		case FRD_LINE_COLOR_WHITE:
			atTmp[0].usVal = atTmp[1].usVal = atTmp[2].usVal = 0x0F;
			break;
		case FRD_LINE_COLOR_BLACK:
			atTmp[0].usVal = atTmp[1].usVal = atTmp[2].usVal = 0x00;
			break;
		case FRD_LINE_COLOR_US_WHITE:
			atTmp[0].usVal = atTmp[1].usVal = atTmp[2].usVal = 0x0d;
			break;
		default:
			return S_SPEC_ERROR;
	}
	eResult |= eFrdPlRegWs(3, atTmp);
	
	/* 矩形描画のON/OFF設定 */
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x221, (uint16)fLineEn);

	eResult |= ePlRegUpd();

	return eResult;
}


/*!
********************************************************************************
** @brief	倍速半画面設定API
** @param	eModeHalf	: 倍速半画面設定 (型定義: dFrdModeHalf_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetModeHalf( dFrdModeHalf_e eModeHalf )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t tTmp;
	
	/* 090521 ohashi: デモ時は本APIが必ずコールされるので */
	if(eModeHalf == FRD_MODE_HALF_NORMAL){
		
		/* 090701 ohashi: 3rdMethodパラメータ変更をソフトで対応 */
		if((aucFrdRevInfo[FRDLCD_REVISION_YEAR_L] <= 0x09) && (aucFrdRevInfo[FRDLCD_REVISION_MONTH] <= 0x06)){
		
#if ((PL_REGION_INFO == PL_RIGION_US1) || \
	 (PL_REGION_INFO == PL_RIGION_EU1) || \
	 (PL_REGION_INFO == PL_RIGION_AS1))
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x151, 0x04);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x104, 0x0f);
			if(ePnlSize == FRDLCD_PNL_40)	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, 0x00);
			else							eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, 0x03);
#elif (PL_REGION_INFO == PL_RIGION_US2)
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x151, 0x04);
#endif
		}else{
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x151, aucFrcParamChg[0]);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, aucFrcParamChg[1]);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x104, aucFrcParamChg[2]);
		}
		
		fCurrentDemoMode = FALSE;
		
	}else{
#if ((PL_REGION_INFO == PL_RIGION_US1) || \
	 (PL_REGION_INFO == PL_RIGION_EU1) || \
	 (PL_REGION_INFO == PL_RIGION_AS1))|| \
	 (PL_REGION_INFO == PL_RIGION_US2)
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x151, 0x10);
		if((aucFrdRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2){
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x11d, 0x00);
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x104, 0x03);
		}
#endif
		
		fCurrentDemoMode = TRUE;
	}
	
	switch(eModeHalf){
		case FRD_MODE_HALF_NORMAL:
			eResult |= eFrdPlSetMask(4, FALSE, NULL);
			break;
		case FRD_MODE_HALF_BOTTOM_ON:
			tTmp.usXPos = 0;
			tTmp.usYPos = 0;
			tTmp.usWidth = 1920;
			tTmp.usHeight = 540;
			
			eResult |= eFrdPlSetMask(4, TRUE, &tTmp);
			break;
		case FRD_MODE_HALF_UP_ON:
			tTmp.usXPos = 0;
			tTmp.usYPos = 540;
			tTmp.usWidth = 1920;
			tTmp.usHeight = 540;
			
			eResult |= eFrdPlSetMask(4, TRUE, &tTmp);
			break;
		case FRD_MODE_HALF_RIGHT_ON:
			tTmp.usXPos = 0;
			tTmp.usYPos = 0;
			tTmp.usWidth = 960;
			tTmp.usHeight = 1080;
			
			eResult |= eFrdPlSetMask(4, TRUE, &tTmp);
			break;
		case FRD_MODE_HALF_LEFT_ON:
			tTmp.usXPos = 960;
			tTmp.usYPos = 0;
			tTmp.usWidth = 960;
			tTmp.usHeight = 1080;
			
			eResult |= eFrdPlSetMask(4, TRUE, &tTmp);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	温度に応じた3rdMethod ON/OFF 設定API
** @param	ucLvl : 温度指定 [0(低温)-7(高温)] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetGain( uint8 ucLvl )
{
	dResult_e eResult = S_SUCCESS;
	
	eResult = ePlEntryChk();
	
	if(ucLvl <= 2){
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, 0x00);
	}
	else if(((3 <= ucLvl) && (ucLvl <= 7)) && (fCurrentStill == FALSE) && (fCurrentMode == TRUE)){
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, 0x01);
	}
	else{
		return S_FAILURE;
	}
	eResult |= ePlRegUpd();
	
	ucCurrentLvl = ucLvl;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	温度指定API
** @param	ucTemp : 温度指定 [0-255] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			1秒毎に、外部デバイスのサーミスタにて得られる0-255の値を
**			本APIに渡してください。
** @note
*******************************************************************************/
dResult_e eFrdPlSetTemp( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	uint8 ucLvl, *pucCntAddr1, *pucCntAddr2;
	static flag f1stCycle = TRUE;
	
	/* 090521 ohashi: デモ時と工程FRC ON時はスルー */
	if((fCurrentModeChk == TRUE) || (fCurrentDemoMode == TRUE)){
		;;
	}else{
		/* AD値を温度レベルに変換 */
		ucLvl = ucPlChgTempToLvl(ePnlSize, ucTemp);
		
		/* 初回は即時反映 */
		if(f1stCycle){
			eResult |= eFrdPlSetGain(ucLvl);
			eResult |= eFrdLcdPlSetQsTemp(ucLvl);
			eResult |= eFrdLcdPlSetSbr(ucLvl);
			
			ucCurrentLvl = ucLvl;
			
			f1stCycle = FALSE;
		}
		
		/* 直前の温度レベルと同じ */
		if(ucLvl == ucCurrentLvl){
			ucNegCnt = 0;
			ucPosCnt = 0;
		}
		/* 変化あり */
		else{
			/* +方向に変化 */
			if(ucLvl > ucCurrentLvl){
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
					ucCurrentLvl++;	/* レベル+1を設定 */
				}else{
					ucCurrentLvl--;	/* レベル-1を設定 */
				}
				eResult |= eFrdPlSetGain(ucCurrentLvl);
				eResult |= eFrdLcdPlSetQsTemp(ucCurrentLvl);
				eResult |= eFrdLcdPlSetSbr(ucCurrentLvl);
			}
		}
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	マニュアルロード全パターン実行API(FRC側)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 
** @note
********************************************************************************/
dResult_e eFrdPlAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i;
	
	/* FRC周波数設定 */
	for(i=0; i<3; i++){
		if( (dFrdInputFreq_e)i != eCurrentInputFreq ){
			eResult |= eFrdPlSetOutFreq( (dFrdInputFreq_e)i );
		}
	}
	eResult |= eFrdPlSetOutFreq( eCurrentInputFreq );/* 元に戻す */
	
	return eResult;
}


/*!
********************************************************************************
** @brief	静止画表示API
** @param	fStill : 静止画表示設定．ONはTRUE、OFFはFALSE (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetStill( flag fStill )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fStill){
	/* ON */
		eResult |= ePlEntryChk();
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, 0x00);
		eResult |= ePlRegUpd();
		/* 入力2フレーム以上wait→(1/48)*2*1000[msec] */
		MDrv_Timer_Delayms( 50 );
		eResult |= ePlEntryChk();
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x155, 0x01);
		eResult |= ePlRegUpd();
		/* 入力2フレーム以上wait→(1/48)*2*1000[msec] */
		MDrv_Timer_Delayms( 50 );
		eResult |= eFrdPlSetFreeRun(TRUE);
		/* 入力2フレーム以上wait→(1/48)*2*1000[msec] */
		MDrv_Timer_Delayms( 50 );
	}else{
	/* OFF */
		eResult |= eFrdPlSetFreeRun(FALSE);
		/* 入力2フレーム以上wait→(1/48)*2*1000[msec] */
		MDrv_Timer_Delayms( 50 );
		eResult |= ePlEntryChk();
		eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x155, 0x00);
		eResult |= ePlRegUpd();
		/* 入力2フレーム以上wait→(1/48)*2*1000[msec] */
		MDrv_Timer_Delayms( 50 );
		if(((3 <= ucCurrentLvl) && (ucCurrentLvl <= 7)) && (fCurrentMode == TRUE)){
			eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x100, 0x01);
			eResult |= ePlRegUpd();
		}
	}
	fCurrentStill = fStill;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	入力画素値キャプチャAPI
 * @param	usCvH		: 画面水平方向指定位置 範囲: 0〜1919 (型定義: uint16)
 * @param	usCvV		: 画面垂直方向指定位置 範囲: 0〜1079 (型定義: uint16)
** @param	ptInputRgb : 入力画素値格納配列へのポインタ (型定義: dFrdPlPixelDat_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlGetInputRgb( uint16 usCvH, uint16 usCvV, dFrdPlPixelDat_t *ptInputRgb )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i;
	dFrdRegVar_t atTmp[6];
	
	eResult |= ePlEntryChk();
	
	/* X,Y座標をセット */
	for(i=0; i<4; i++) atTmp[i].usAddr = PL_REGADDR_FRC+0x47 +i;
	atTmp[0].usVal = (usCvH & 0x700) >> 8;
	atTmp[1].usVal =  usCvH & 0xff;
	atTmp[2].usVal = (usCvV & 0x700) >> 8;
	atTmp[3].usVal =  usCvV & 0xff;
	
	eResult |= eFrdPlRegWs(4, atTmp);
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x51, 1);
	eResult |= ePlRegUpd();
	eResult |= ePlEntryChk();
	eResult |= eFrdPlRegW(PL_REGADDR_FRC+0x51, 0);
	eResult |= ePlRegUpd();
	
	atTmp[0].usAddr = PL_REGADDR_FRC+0x4b;
	eResult |= eFrdPlRegRs(6, atTmp);
	
	ptInputRgb->usCvR = (atTmp[0].usVal << 8 | atTmp[1].usVal);
	ptInputRgb->usCvG = (atTmp[2].usVal << 8 | atTmp[3].usVal);
	ptInputRgb->usCvB = (atTmp[4].usVal << 8 | atTmp[5].usVal);
	
	return eResult;
}

static flag fTmpMode;
/*!
********************************************************************************
** @brief	工程 FRC ON/OFF 設定API
** @param	eModeChk		: 工程設定値	(型定義: dFrdModeChk_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetModeChk( dFrdModeChk_e eModeChk )
{
	dResult_e eResult = S_SUCCESS;
	dFrdModeHalf_e eModeHalf = FRD_MODE_HALF_NORMAL;
	dFrdTestPtn_e eTestPtn = FRD_TESTPTN_OFF;
	dFrdPlInternalDat_t tFrcStatusDat;
	dFrdPlAdjTestPtn_t tAdjustTestPtn;
	flag fMode = FALSE;
	
	/* FRC ON/OFFテスト直前のFRC状態の確保 */
	if(!fCurrentModeChk) eFrdPlGetMode(&fTmpMode);
	
	eResult = eFrdPlGetStatus(&tFrcStatusDat);
	tFrcStatusDat.tCurrentAdjTestPtn.ptArea3TestPtn = NULL;
	
	tAdjustTestPtn = tFrcStatusDat.tCurrentAdjTestPtn;
	
	switch(eModeChk){
		case FRD_MODE_CHK_OFF:
			if(((3 <= ucCurrentLvl) && (ucCurrentLvl <= 7)) && (fCurrentStill == FALSE)){
				fMode = fTmpMode;
			}else{
				fMode = FALSE;
			}
			eModeHalf = FRD_MODE_HALF_NORMAL;
			eTestPtn = FRD_TESTPTN_OFF;
			tAdjustTestPtn.ptMovTestPtn->fQsMovLR = FALSE;
			tAdjustTestPtn.ptMovTestPtn->ucQsMovSpeed = 0x0A;
			
			fCurrentModeChk = FALSE;
			break;
		case FRD_MODE_CHK_MPRT:
			fMode = TRUE;
			eModeHalf = FRD_MODE_HALF_UP_ON;
			eTestPtn = FRD_TESTPTN_MPRT;
			tAdjustTestPtn.ptMovTestPtn->fQsMovLR = FALSE;
			tAdjustTestPtn.ptMovTestPtn->ucQsMovSpeed = 0x0C;
			
			fCurrentModeChk = TRUE;
			break;
		case FRD_MODE_CHK_AQUOS:
			fMode = TRUE;
			eModeHalf = FRD_MODE_HALF_LEFT_ON;
			eTestPtn = FRD_TESTPTN_SHARP;
			tAdjustTestPtn.ptMovTestPtn->fQsMovLR = TRUE;
			tAdjustTestPtn.ptMovTestPtn->ucQsMovSpeed = 0x0C;
			
			fCurrentModeChk = TRUE;
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eResult  = eFrdPlSetMode(fMode);
	eResult |= eFrdPlSetModeHalf(eModeHalf);
	eResult |= eFrdPlSetTestPtn(eTestPtn, &tAdjustTestPtn);
	
	return eResult;
}

static flag fTmpQsEn;
static flag fTmpYuv;
/*!
********************************************************************************
** @brief	デモモード設定API
** @param	eDemoMode		: FRCデモモード設定	(型定義: dFrdPlDemoMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdPlSetDemoMode( dFrdPlDemoMode_e eDemoMode )
{
	dResult_e eResult = S_SUCCESS;
	flag fMode = FALSE;
	dFrdModeHalf_e eModeHalf = FRD_MODE_HALF_NORMAL;
//	flag fMask = FALSE;
	flag fLine = FALSE;
	dFrdTestPtn_e eTestPtn = FRD_TESTPTN_OFF;
	uint16 usTmp;
	
//	dFrdFrame_t tMask = {0, 0, 1920, 260};
	dFrdFrame_t tLine = {958, 260, 4, 820};
	
	dFrdPlInternalDat_t tFrcStatusDat;
	dFrdPlAdjTestPtn_t tAdjustTestPtn;
	
	/* とりあえずModeChkと同様 FRC ON設定 */
	if(!fCurrentDemoMode){
		eFrdPlGetMode(&fTmpMode);
		
		/* ついでにQS状態確保 */
		eFrdPlRegR(0x6408, &usTmp);
		fTmpQsEn = (flag)((usTmp & 0x10) >> 4);
		fTmpYuv  = (flag)((usTmp & 0x20) >> 5);	/* これでは逆 */
		if(fTmpYuv)	fTmpYuv = FALSE;
		else		fTmpYuv = TRUE;
	}
	
	switch(eDemoMode){
		case FRDPL_DEMO_OFF:		/*!< デモモードOFF */
			if(((3 <= ucCurrentLvl) && (ucCurrentLvl <= 7)) && (fCurrentStill == FALSE))	fMode = fTmpMode;
			else																			fMode = FALSE;
			eModeHalf = FRD_MODE_HALF_NORMAL;
			eTestPtn = FRD_TESTPTN_OFF;
//			fMask = FALSE;
			fLine = FALSE;
			
			/* QS Halfを戻す */
			eFrdLcdPlSetQsHalf(FALSE);
			eFrdLcdPlSetQsEn(fTmpQsEn, fTmpYuv);
			break;
		case FRDPL_DEMO_NORMAL:	/*!< 通常映像デモ(左右分割、スクロールなし) */
			fMode = TRUE;
			eModeHalf = FRD_MODE_HALF_LEFT_ON;
			eTestPtn = FRD_TESTPTN_OFF;
//			fMask = TRUE;
			fLine = FALSE;
			
			/* QS Half */
			eFrdLcdPlSetQsEn(TRUE, FALSE);
			eFrdLcdPlSetQsHalf(TRUE);
			break;
		case FRDPL_DEMO_SCROLL:	/* 静止画スクロールデモ(左右分割＋スクロール) */
			
			eResult = eFrdPlGetStatus(&tFrcStatusDat);
			tFrcStatusDat.tCurrentAdjTestPtn.ptMovTestPtn   = NULL;
			
			tAdjustTestPtn = tFrcStatusDat.tCurrentAdjTestPtn;
			
			fMode = TRUE;
			eModeHalf = FRD_MODE_HALF_LEFT_ON;
			eTestPtn = FRD_TESTPTN_AREA3;
			/* 3分割スクロール設定 */
			tAdjustTestPtn.ptArea3TestPtn->usArea2Y = 260;
			tAdjustTestPtn.ptArea3TestPtn->usArea3Y = 1010;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea1Speed = 0;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea2Speed = 12;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea3Speed = 12;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Mov->eArea1Mov = FRDPL_AREA3_STOP;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Mov->eArea2Mov = FRDPL_AREA3_LEFT;
			tAdjustTestPtn.ptArea3TestPtn->ptArea3Mov->eArea3Mov = FRDPL_AREA3_LEFT;
			
//			fMask = TRUE;
			fLine = TRUE;
			
			/* QS Half */
			eFrdLcdPlSetQsEn(TRUE, FALSE);
			eFrdLcdPlSetQsHalf(TRUE);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eResult  = eFrdPlSetMode(fMode);
	eResult |= eFrdPlSetModeHalf(eModeHalf);
	if(eDemoMode == FRDPL_DEMO_SCROLL){
		eResult |= eFrdPlSetTestPtn(eTestPtn, &tAdjustTestPtn);
	}else{
		eResult |= eFrdPlSetTestPtn(eTestPtn, NULL);
	}
//	eResult |= eFrdPlSetMask(3, fMask, &tMask);
	eResult |= eFrdPlDrawLine(fLine, FRD_LINE_COLOR_WHITE, &tLine);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	現状設定取得 API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			現状の周波数, 温度, FRC, QS 設定値を取得
** @note
*******************************************************************************/
dResult_e eFrdPlGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp;
	
	ptCurrentVal->eFreq		= eCurrentInputFreq;
	ptCurrentVal->ucLvl		= ucCurrentLvl;
	eResult |= eFrdPlRegR(PL_REGADDR_FRC+0x100, &usTmp);
	ptCurrentVal->fFrcEn	= (flag)usTmp;
	eResult |= eFrdPlRegR(0x6408, &usTmp);
	ptCurrentVal->fQsEn		= (flag)((usTmp & 0x10) >> 4);
	
	return eResult;
}



static uint8 aucPfLutData46_60Hz[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x40,0x10,0x10,0x0b,0x0b,0x0b,0x0b,
0x07,0x07,0x07,0x07,0x07,0x07,0x03,0x03,
0x01,0x01,0x44,0x26,0x20,0x0c,0x0c,0x0b,
0x0b,0x07,0x07,0x07,0x07,0x07,0x07,0x03,
0x03,0x01,0x01,0x57,0x57,0x38,0x30,0x23,
0x23,0x1d,0x07,0x07,0x07,0x07,0x07,0x07,
0x03,0x03,0x01,0x01,0x6b,0x6b,0x6b,0x4d,
0x40,0x30,0x2b,0x07,0x07,0x07,0x07,0x07,
0x07,0x03,0x03,0x01,0x01,0x7d,0x7d,0x7d,
0x6e,0x64,0x50,0x43,0x30,0x0f,0x0f,0x0f,
0x0f,0x0f,0x03,0x03,0x01,0x01,0x8e,0x8e,
0x8e,0x8b,0x7b,0x6c,0x60,0x49,0x36,0x23,
0x23,0x23,0x0f,0x03,0x03,0x01,0x01,0x9e,
0x9e,0x9e,0x9e,0x93,0x89,0x7d,0x70,0x5c,
0x44,0x33,0x33,0x0f,0x03,0x03,0x01,0x01,
0xb1,0xb1,0xb0,0xb0,0xa8,0x9d,0x97,0x93,
0x80,0x73,0x4b,0x35,0x0f,0x03,0x03,0x01,
0x01,0xbd,0xbd,0xbd,0xbd,0xb8,0xb2,0xa8,
0xa4,0x9e,0x90,0x77,0x4a,0x0f,0x03,0x03,
0x01,0x01,0xd3,0xd3,0xd3,0xd3,0xca,0xbf,
0xba,0xb8,0xb0,0xab,0xa0,0x7e,0x3f,0x03,
0x03,0x01,0x01,0xf0,0xed,0xec,0xec,0xec,
0xdd,0xd7,0xd0,0xcc,0xc0,0xbc,0xb0,0x8f,
0x6d,0x42,0x01,0x01,0xfb,0xfb,0xfb,0xfb,
0xf9,0xf6,0xf2,0xef,0xe9,0xe4,0xdd,0xd0,
0xc0,0xb4,0x96,0x68,0x0b,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfd,0xf8,0xf5,0xf0,
0xea,0xdf,0xd0,0xbc,0x92,0x53,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf8,0xf3,0xeb,0xe0,0xc3,0x93,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xfa,0xf0,0xd8,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff
};

static uint8 aucPfLutData46_50Hz[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x38,0x10,0x06,0x06,0x06,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x40,0x23,0x20,0x0c,0x0c,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x02,0x57,0x57,0x38,0x30,0x23,
0x23,0x1f,0x19,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x6b,0x6b,0x6b,0x4d,
0x40,0x30,0x2b,0x19,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x7d,0x7d,0x7d,
0x6e,0x64,0x50,0x43,0x30,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x8e,0x8e,
0x8e,0x8b,0x7a,0x6c,0x60,0x49,0x35,0x27,
0x27,0x27,0x0b,0x09,0x09,0x09,0x09,0x9e,
0x9e,0x9e,0x9e,0x93,0x89,0x7d,0x70,0x5c,
0x44,0x33,0x33,0x0b,0x09,0x09,0x09,0x09,
0xb0,0xb0,0xb0,0xb0,0xa7,0x9d,0x97,0x93,
0x80,0x73,0x49,0x35,0x0b,0x09,0x09,0x09,
0x09,0xba,0xba,0xba,0xba,0xb5,0xaf,0xa4,
0xa2,0x9c,0x90,0x76,0x49,0x0b,0x09,0x09,
0x09,0x09,0xcd,0xcd,0xcd,0xcd,0xbf,0xbd,
0xb8,0xb5,0xae,0xaa,0xa0,0x7d,0x3b,0x09,
0x09,0x09,0x09,0xe7,0xe7,0xe7,0xe7,0xe0,
0xd8,0xd0,0xcc,0xca,0xbf,0xbc,0xb0,0x8e,
0x67,0x40,0x0d,0x0d,0xf7,0xf7,0xf7,0xf7,
0xf7,0xf4,0xef,0xe8,0xe8,0xe1,0xdc,0xd2,
0xc0,0xb4,0x93,0x64,0x2d,0xff,0xff,0xff,
0xff,0xff,0xff,0xfb,0xf7,0xf4,0xf0,0xec,
0xe7,0xdd,0xd0,0xbc,0x8e,0x4f,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,
0xf9,0xf5,0xef,0xea,0xe0,0xc2,0x8b,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xfa,0xf0,0xd5,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff
};

static uint8 aucPfLutData52_60Hz[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x10,0x09,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x2e,0x22,0x20,0x08,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x41,0x41,0x38,0x30,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x18,
0x18,0x18,0x09,0x09,0x57,0x57,0x57,0x4e,
0x40,0x30,0x27,0x27,0x27,0x27,0x27,0x27,
0x18,0x18,0x18,0x09,0x09,0x76,0x76,0x76,
0x76,0x60,0x50,0x41,0x32,0x32,0x32,0x32,
0x32,0x18,0x18,0x18,0x09,0x09,0x88,0x88,
0x88,0x88,0x77,0x6b,0x60,0x49,0x39,0x32,
0x32,0x32,0x18,0x18,0x18,0x09,0x09,0x9b,
0x9b,0x9b,0x9b,0x93,0x8b,0x7e,0x70,0x5e,
0x42,0x33,0x33,0x18,0x18,0x18,0x09,0x09,
0xae,0xae,0xae,0xae,0xaa,0x9e,0x97,0x93,
0x80,0x74,0x44,0x36,0x18,0x18,0x18,0x09,
0x09,0xb8,0xb8,0xb8,0xb8,0xb6,0xaf,0xa4,
0xa0,0x9b,0x90,0x6f,0x4b,0x18,0x18,0x18,
0x09,0x09,0xc6,0xc3,0xc3,0xc3,0xbf,0xbd,
0xb6,0xb5,0xad,0xa9,0xa0,0x7b,0x41,0x38,
0x25,0x09,0x09,0xe3,0xe3,0xe3,0xe3,0xe3,
0xd7,0xcc,0xcc,0xcc,0xc0,0xba,0xb0,0x8f,
0x5c,0x43,0x09,0x09,0xfa,0xfa,0xfa,0xfa,
0xfa,0xf6,0xef,0xeb,0xe9,0xe5,0xdf,0xd4,
0xc0,0xb4,0x9d,0x63,0x43,0xff,0xff,0xff,
0xff,0xff,0xff,0xfe,0xfe,0xf6,0xf4,0xef,
0xe9,0xdf,0xd0,0xbe,0xa1,0x6d,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf7,0xf2,0xea,0xe0,0xc5,0x9f,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0xd8,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff
};

static uint8 aucPfLutData52_50Hz[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x10,0x09,0x09,0x09,0x09,0x09,
0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,
0x09,0x09,0x2b,0x22,0x20,0x0e,0x0e,0x0e,
0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,
0x0e,0x0e,0x0e,0x3e,0x3e,0x38,0x30,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x15,0x15,
0x15,0x15,0x15,0x15,0x5e,0x5e,0x5e,0x55,
0x40,0x37,0x2a,0x24,0x24,0x24,0x24,0x15,
0x15,0x15,0x15,0x15,0x15,0x76,0x76,0x76,
0x6f,0x62,0x50,0x42,0x30,0x27,0x27,0x27,
0x15,0x15,0x15,0x15,0x15,0x15,0x8c,0x8c,
0x8c,0x8a,0x7b,0x6d,0x60,0x49,0x33,0x2f,
0x2f,0x15,0x15,0x15,0x15,0x15,0x15,0xa2,
0xa2,0xa2,0xa2,0x94,0x8b,0x7e,0x70,0x5e,
0x4a,0x32,0x15,0x15,0x15,0x15,0x15,0x15,
0xb5,0xb5,0xb5,0xb5,0xaa,0x9e,0x98,0x93,
0x80,0x73,0x4e,0x37,0x2c,0x1b,0x1b,0x1b,
0x1b,0xbd,0xbd,0xbd,0xbd,0xb8,0xaf,0xa5,
0xa1,0x9a,0x90,0x73,0x4f,0x2c,0x1b,0x1b,
0x1b,0x1b,0xd3,0xd3,0xd3,0xd3,0xc0,0xbd,
0xb8,0xb6,0xad,0xa9,0xa0,0x7c,0x42,0x33,
0x21,0x1f,0x1f,0xf0,0xf0,0xef,0xef,0xe6,
0xdc,0xd3,0xce,0xcb,0xc0,0xbc,0xb0,0x92,
0x76,0x44,0x1f,0x1f,0xfd,0xfd,0xfd,0xfd,
0xfb,0xf7,0xf3,0xee,0xe9,0xe3,0xdf,0xd5,
0xc0,0xb4,0x9c,0x6f,0x3d,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfb,0xf7,0xf3,0xee,
0xe8,0xdd,0xd0,0xbd,0x96,0x62,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xfc,0xf6,0xf1,0xea,0xe0,0xc3,0x9a,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xfb,0xf0,0xd7,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff
};


#define PL_REGADDR_PF_LUT_OFFSET (PL_REGADDR_FRC + 0x300)
/**
 * @brief	PF LUT 書き換え用API
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 * @ note 2010.03.29 ROM変更は間に合わない為、ソフトで対応。。。
 */
static dResult_e ePlSetPfLutData( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atTmp[0x40];
	uint8 *pucPfLutData = NULL;
	int i, j;
	
	if( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x46 ){
		if( eInputFreq == FRD_INPUT_FREQ_60HZ ){
			pucPfLutData = aucPfLutData46_60Hz;
		}
		else{
			pucPfLutData = aucPfLutData46_50Hz;
		}
	}
	else if( aucFrdRevInfo[FRDLCD_REVISION_INCHI]==0x52 ){
		if( eInputFreq == FRD_INPUT_FREQ_60HZ ){
			pucPfLutData = aucPfLutData52_60Hz;
		}
		else{
			pucPfLutData = aucPfLutData52_50Hz;
		}
	}
	
	for(i=0; i<4; i++){
		for(j=0; j<0x40; j++){
			atTmp[j].usAddr = PL_REGADDR_PF_LUT_OFFSET + (i*0x40) + j;
			atTmp[j].usVal  = pucPfLutData[(i*0x40) + j];
		}
		eResult |= eFrdPlRegWs(0x40, atTmp);
	}
	
	for(j=0; j<0x21; j++){
		atTmp[j].usAddr = PL_REGADDR_PF_LUT_OFFSET + (i*0x40) +j;
		atTmp[j].usVal  = pucPfLutData[(i*0x40) + j];
	}
	eResult |= eFrdPlRegWs(0x21, atTmp);
	
	return eResult;
}



/**
 * @brief	REGUPD確認子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e ePlEntryChk( void )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usGetVal;
	uint8 ucGardCnt = 0;
	
	/* 書き込みOKかRegUpDateを確認*/
	do {
		if(ucGardCnt != 0){
			MDrv_Timer_Delayms( 5 );
		}
		
		/* read処理 */
		eResult = eFrdPlRegR(PL_REGADDR_FRC+0x00, &usGetVal);
		
		ucGardCnt++;
		
		if(ucGardCnt > 10){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "[PL]: REGUPD remains 1 !!\n");
#endif //TURNKEY1
			return S_FAILURE;
		}
	}while(usGetVal != 0);

	return eResult;
}


/**
 * @brief	REGUPD設定子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e ePlRegUpd( void )
{
	dResult_e eResult = S_SUCCESS;
	
	eResult = eFrdPlRegW(PL_REGADDR_FRC+0x00, 1);
	
	return eResult;
}


/**
 * @brief	システム関係 ROMアドレス探索子関数(TBCとFreeRunを同時に更新)
 * @param	eResult
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e ePlGetSystemRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	/* 演算 */
	uiRomAddr = PL_ROMADDR_SYSTEM + ((FRD_INPUT_FREQ_60HZ -eInputFreq) * (PL_ROMSIZE_SYSTEM * 2));
	uiCrcAddr = PL_CRCADDR_SYSTEM + (FRD_INPUT_FREQ_60HZ -eInputFreq);
	
	*puiRomAddr = uiRomAddr;
	*puiCrcAddr = uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	PF LUT ROMアドレス探索子関数
 * @param	eResult
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e ePlGetPfLutRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr = 0x00, uiCrcAddr = 0x00;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_48HZ:
		case FRD_INPUT_FREQ_50HZ:
			uiRomAddr = PL_ROMADDR_PFLUT50;
			uiCrcAddr = PL_CRCADDR_PFLUT +1;
			break;
		case FRD_INPUT_FREQ_60HZ:
		default:
			uiRomAddr = PL_ROMADDR_PFLUT60;
			uiCrcAddr = PL_CRCADDR_PFLUT;
			break;
	}
	
	*puiRomAddr = uiRomAddr;
	*puiCrcAddr = uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	サーミスタ温度変換用子関数
 * @param	uint8 ucTemp
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static uint8 ucPlChgTempToLvl( dFrdLcdPnlSize_e	eSize, uint8 ucTemp )
{
	uint8 i = 0, ucLvl;
	
	while(ucTemp > ucAdTbl[eSize][i]){
		i++;
		if(i == 7){
			break;
		}
	}
	
	/* 温度レベルは配列の逆 */
	ucLvl = ~i & 0x07;
	
	return ucLvl;
}
/* end of file */
