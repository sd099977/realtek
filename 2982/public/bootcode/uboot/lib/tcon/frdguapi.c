/**
 * @file frdguapi.c
 *
 * @brief GuavaFRC部制御
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

#include <tcon/frdapi.h> 		/* dFrdRegVar_tのためやけど、これをincludeするかは暫定 */
#include <tcon/frdguapi.h>
//#include <math.h>		/* 090323 ohashi: fabs()がまだある */
#include <tcon/frdlcdapi.h>
#include <tcon/frdlcdguapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/
/* レジスタアドレス */
#define GU_REGADDR_OSD		0x400
#define GU_REGADDR_IMC		0x600
#define GU_REGADDR_PPDS		ADV_LCDC_ADDR_PPDS							/* 0x2000 */
#define GU_REGADDR_ETC		ADV_LCDC_ADDR_LCDC+ADV_LCDC_ADDR_ETC		/* 0x6CC0 */
#define GU_REGADDR_SBRPARAM	ADV_LCDC_ADDR_LCDC+ADV_LCDC_ADDR_SBR_PARAM	/* 0x7000 */
//#define GU_REGADDR_FRC		0x8000
#define GU_REGADDR_FSB		0x9000

/* ROMアドレス */
#define GU_ROMADDR_TBC		0x9a10	/* 60Hz */
#define GU_ROMADDR_PFLUT	0x94d0	/* 60Hz, sub5,6 */
#define GU_ROMADDR_DJADJ	0x9ab8	/* Dj H */
#define GU_ROMADDR_SV		0x9b80	/* 鮮鋭化 */
/* ROMサイズ */
#define GU_ROMSIZE_TBC		0x38
#define GU_ROMSIZE_PFLUT56	0x128
#define GU_ROMSIZE_PFLUT7	0x88
#define GU_ROMSIZE_DJADJ	0x28
#define GU_ROMSIZE_SV		0x40

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
static dFrdGuInternalDat_t tFrcInternalDat;
static dFrdInputFreq_e	eCurrentInputFreq;
static uint16 usCurrentKSat = 0x8A;		/* Init時に格納される */
static uint16 usCurrentKHue = 0x8A;		/* Init時に格納される */
static dFrdMode_e eCurrentQsMode   = FRD_MODE_ADL;
static dFrdMode_e eCurrentFilmMode = FRD_MODE_ADL;
static flag fHWR = FALSE;
static dFrdGuSvMode_e eCurrentSvMode;	/* eFrdGuAllManualLoad() からの参照用。初期値はDon't Careでよい */
static dFrdGuDjAdj_e eCurrentDjAdj;		/* 同上 */
// Stan test
//static float fRate = 1.0;
static int fRate = 1;
static flag f1stSkinCtlCall;

static uint8			ucCurrentLvl		= 4;
#ifdef TURNKEY1
static flag				fCurrentMode		=FALSE;
#endif //TURNKEY1
extern uint8			ucLcdGuLvl;
static flag				fCurrentModeChk		= FALSE;
static uint8			aucRomVer[FRDLCD_REVISION_DATA_MAX];

const static uint8 aucPFGain[8] = {0x00, 0x06, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

									/*  48    50    60 Hz */
const static uint8 aucBintDelay[3]	= {0x39, 0x21, 0x21};
const static uint8 aucVdp[3]		= {0x4a, 0x23, 0x23};

/* **
 * ** prototype
 * **/
static dResult_e	eGuEntryChk( void );
static dResult_e	eGuRegUpd( void );
static dResult_e	eGuInitStatus( void );
static dResult_e	eGuReflectAspectSize( dFrdFrame_t *ptEdgeFrame );
static dResult_e	eGuGetTbcRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e	eGuGetPfLutRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static uint16		usGuChgDblToUs(double Val);
static dResult_e	eGuGetDjAdjRomAddr( dFrdGuDjAdj_e eDjAdj, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e	eGuSetPFHalf( dFrdModeHalf_e eModeHalf );
static dResult_e	eGuChgAdvParam( flag fLow );
static dResult_e	eGuSetQsMode( dFrdMode_e eMode );
static dResult_e	eGuSetFilmMode( dFrdMode_e eMode );
static dResult_e	eGuGetSvRomAddr( dFrdGuSvMode_e eSvMode, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static double		dGuSqrt( double x );
static dResult_e	eGuSetTypvGain( void );

/* **
 * ** func
 * **/
extern dResult_e eFrdLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn );
extern dResult_e eFrdLcdGuRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDatas );
extern dResult_e eFrdLcdGuSetOutFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdLcdGuSetQsEn( flag fQsEn );
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
dResult_e eFrdGuRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	printf("eFrdGuRegWs1\r\n");
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
	uint32 i;
//sakata20110627	uint16 tmp_addr;
	
	for( i=0; i<iRegNum; i++ )
	{
//sakata20110627		tmp_addr = ptDatas[0].usAddr + (uint16)i;
//sakata20110627		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDatas[i].usVal);
		printf("eFrdGuRegWs, IIC_SLV_ADDR_TCON=%x\r\n",IIC_SLV_ADDR_TCON);
		printf("eFrdGuRegWs, ptDatas[%d].usAddr=%x\r\n",i,ptDatas[i].usAddr);
		printf("eFrdGuRegWs, ptDatas[%d].usVal=%x\r\n",i,ptDatas[i].usVal);
		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, ptDatas[i].usAddr, ptDatas[i].usVal);	//sakata2011062
		
		if( eResult == S_FAILURE )	break;
	}
#else //TURNKEY1
	const void	*pvDevice;
	
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, iRegNum, ptDatas );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	printf("eFrdGuRegWs2\r\n");
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
dResult_e eFrdGuRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32		i;
	uint16		tmp_addr;
	

	for(  i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDatas[0].usAddr + (uint16)i;
		eResult = eI2CRead( IIC_SLV_ADDR_TCON, tmp_addr, &(ptDatas[i].usVal));
		ptDatas[i].usAddr = ptDatas[0].usAddr + i;								//sakata20110627

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
dResult_e eFrdGuRegW( uint16 usAddr, uint16 usVal )
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
dResult_e eFrdGuRegR( uint16 usAddr, uint16 *pusVal)
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


/*!
********************************************************************************
** @brief	初期化設定API (FRC側)
** @param	eInputFreq		: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			起動時にやっておきたい事(A-F)を細々と設定する程度
** @note
*******************************************************************************/
dResult_e eFrdGuInit( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	printf("eFrdGuInit\r\n");
	printf("eGuInitStatus\r\n");
	/* A: InitStatus */	
	eResult |= eGuInitStatus();
	printf("eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x426, &usCurrentKSat)\r\n");
	/* B: KSatとKHueのROM値取得 */
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x426, &usCurrentKSat);
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x427, &usCurrentKHue);
	printf("eFrdGuSetOutFreq\r\n");
	/* C: 周波数設定 */
	eCurrentInputFreq = FRD_INPUT_FREQ_NUMMAX;	/* 起動時は必ずSetOutFreqが実行されるように */
	eResult |= eFrdGuSetOutFreq( eInputFreq );

	/* 既にOutFreqでパイプラインONにしている */
	printf("eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x405, 1)\r\n");
	/* F: sub4のINIREGUP */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x405, 1);
	
	/* static変数の初期化 */
	eCurrentQsMode		= FRD_MODE_ADL;	/* ROM初期値に合わせる */
	eCurrentFilmMode	= FRD_MODE_ADL;	/* ROM初期値に合わせる */
	fHWR				= FALSE;		/* ROM初期値に合わせる */
	f1stSkinCtlCall		= TRUE;			/* eFrdGuSetSkinCtl()で参照 */
	
	ucCurrentLvl		= 4;
	fCurrentModeChk		= FALSE;
#ifdef TURNKEY1
	fCurrentMode		= FALSE;
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	スタンバイ設定API (FRC側)
** @param	fPipelineEnable	: スタンバイ(パイプライン)設定, 
**							TRUE = ON, FALSE = OFF(スタンバイ状態) (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuStandby( flag fPipelineEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ON */
	if(fPipelineEnable){
		eResult = eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x04, 0x02);
	}
	/* OFF */
	else{
		eResult = eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x04, 0x00);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	倍速モード設定API
** @param	fFrcEnable	: 倍速モード設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetMode( flag fFrcEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	eResult |= eGuEntryChk();
	
	/* 0xc0(INTP_MODE)はdefault 0x03(FRC有効)と仮定 */
	if(fFrcEnable){
		/* ON */
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1df, 0x00);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ad, 0x01);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ae, 0x01);
	}else{
		/* OFF */
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ad, 0x00);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ae, 0x00);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1df, 0x01);
	}
	
	eResult |= eGuRegUpd();
	
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
*******************************************************************************/
dResult_e eFrdGuGetMode( flag *pfFrcStatus )
{
	dResult_e eResult = S_SUCCESS;
	uint16	usTmp;
	
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x1df, &usTmp);
	
	if(usTmp)	*pfFrcStatus = FALSE;
	else		*pfFrcStatus = TRUE;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	画面端OFF設定API
** @param	ptEdgeFrame	: 領域指定 (型定義: dFrdFrame *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetEdge( dFrdFrame_t *ptEdgeFrame )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t		tTmpFrame;
	dFrdRegVar_t	atTmp[8];
	uint16			i;
	
	eResult |= eGuEntryChk();
	
	/* 基本 eFrcEdgeCtl( FRC_EDGE_DISABLED, FRC_EDGE_WEIGHT_10, &tEdgeFrame ); */
	/* よって0xc1(INTP_EDGE)のbit0がdefault 0(完全無効)と仮定(Fraser defaultではやっぱり0x00) */
	
	/* 丸め補正なし */
	tTmpFrame.usXPos	= ptEdgeFrame->usXPos >> 2;
	tTmpFrame.usYPos	= ptEdgeFrame->usYPos >> 1;
	tTmpFrame.usWidth	= ptEdgeFrame->usWidth >> 2;
	tTmpFrame.usHeight	= ptEdgeFrame->usHeight >> 1;
	
	if(( 0x1E0 < ((tTmpFrame.usXPos) + (tTmpFrame.usWidth))) ||( 0x21C < ((tTmpFrame.usYPos) + (tTmpFrame.usHeight)))){
		return S_SPEC_ERROR;
	}
	
	/* 設定領域より4pixel内側になるよう補正 */
	if(tTmpFrame.usXPos <= 0x1DF)	tTmpFrame.usXPos	+= 0x01;	/* ×4 */
	if(tTmpFrame.usYPos <= 0x21A)	tTmpFrame.usYPos	+= 0x02;	/* ×2 */
	if(tTmpFrame.usWidth  >= 0x02)	tTmpFrame.usWidth	-= 0x02;	/* ×4(両端分) */
	if(tTmpFrame.usHeight >= 0x04)	tTmpFrame.usHeight	-= 0x04;	/* ×2(両端分) */
	
	for(i=0; i<8; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0xc3+i;
	
	atTmp[0].usVal = (tTmpFrame.usXPos & 0x100) >> 8;
	atTmp[1].usVal = tTmpFrame.usXPos & 0xff;
	atTmp[2].usVal = (tTmpFrame.usYPos & 0x300) >> 8;
	atTmp[3].usVal = tTmpFrame.usYPos & 0xff;
	atTmp[4].usVal = (tTmpFrame.usWidth & 0x100) >> 8;
	atTmp[5].usVal = tTmpFrame.usWidth & 0xff;
	atTmp[6].usVal = (tTmpFrame.usHeight & 0x300) >> 8;
	atTmp[7].usVal = tTmpFrame.usHeight & 0xff;
	
	eResult |= eFrdGuRegWs(8, atTmp);
	
	/* 各種詳細設定 */
	eResult |= eGuReflectAspectSize(ptEdgeFrame);
	
	eResult |= eGuRegUpd();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	倍速モードマスク設定API
** @param	ucMaskNo	: マスク番号指定 [1-8] (型定義: uint8)
** @param	fMaskEnable	: マスク設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @param	ptMaskFrame	: 領域指定 (型定義: dFrdFrame *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetMask( uint8 ucMaskNo, flag fMaskEnable, dFrdFrame_t *ptMaskFrame )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t		tTmpFrame;
	dFrdRegVar_t	atTmp[8];
	uint16			usTmp, i;
	
	if(ucMaskNo == 0)	return S_FAILURE;
	
	eResult |= eGuEntryChk();
	
	if(ptMaskFrame != NULL){
		tTmpFrame.usXPos	= ptMaskFrame->usXPos >> 2;
		tTmpFrame.usYPos	= ptMaskFrame->usYPos >> 1;
		tTmpFrame.usWidth	= (ptMaskFrame->usWidth  + (ptMaskFrame->usXPos % 4) + 3) >> 2;
		tTmpFrame.usHeight	= (ptMaskFrame->usHeight + (ptMaskFrame->usYPos % 2) + 1) >> 1;
		
		/* マスク領域をx方向のみ 1ブロック外側に広げる。
			(上で算出したマスク領域が引数指定座標より 2pixel以上外側になる場合は除外) */
		/* 始点を広げる */
		if(tTmpFrame.usXPos != 0){	/* 端っこの場合を除外 */
			if((ptMaskFrame->usXPos % 4) < 2){
				tTmpFrame.usXPos -= 1;
				tTmpFrame.usWidth += 1;	/* 始点が-1ずれた分、幅を+1 */
			}
		}
		/* 終点を広げる */
		if( tTmpFrame.usXPos + tTmpFrame.usWidth < (1920/4) ){	/* 端っこの場合を除外 */
			if( ((ptMaskFrame->usXPos + ptMaskFrame->usWidth) % 4) == 0 ||
				((ptMaskFrame->usXPos + ptMaskFrame->usWidth) % 4) == 3 ){	/* 始点の設定と同様 */
				tTmpFrame.usWidth += 1;
			}
		}
		
		if(( 0x1E0 < ((tTmpFrame.usXPos) + (tTmpFrame.usWidth))) ||( 0x21C < ((tTmpFrame.usYPos) + (tTmpFrame.usHeight)))){
			return S_SPEC_ERROR;
		}
		
		switch(ucMaskNo){
			case 1:
				for(i=0; i<8; i++) atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0xE3+i;	break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				for(i=0; i<8; i++) atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x15B+(0x08*(ucMaskNo-2))+i;	break;
			default:
				return S_SPEC_ERROR;
		}
		atTmp[0].usVal = (tTmpFrame.usXPos & 0x100) >> 8;
		atTmp[1].usVal = tTmpFrame.usXPos & 0xff;
		atTmp[2].usVal = (tTmpFrame.usYPos & 0x300) >> 8;
		atTmp[3].usVal = tTmpFrame.usYPos & 0xff;
		atTmp[4].usVal = (tTmpFrame.usWidth & 0x100) >> 8;
		atTmp[5].usVal = tTmpFrame.usWidth & 0xff;
		atTmp[6].usVal = (tTmpFrame.usHeight & 0x300) >> 8;
		atTmp[7].usVal = tTmpFrame.usHeight & 0xff;
		
		eResult |= eFrdGuRegWs(8, atTmp);
	}
	
	/* 現状のマスク設定状態の確認 */
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xE2, &usTmp) == S_FAILURE)	return S_FAILURE;
	usTmp &= ~((uint16)(0x01 << (ucMaskNo-1)));
	usTmp |= (uint16)(fMaskEnable << (ucMaskNo-1));
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xE2, usTmp);
	
	eResult |= eGuRegUpd();
	
	return eResult;
}


static dFrdRegVar_t atCurrentQsBkg[6] = {
	{ADV_LCDC_ADDR_FRC+0x20A, 0x00}, {ADV_LCDC_ADDR_FRC+0x20B, 0x80},
	{ADV_LCDC_ADDR_FRC+0x20C, 0x00}, {ADV_LCDC_ADDR_FRC+0x20D, 0x80},
	{ADV_LCDC_ADDR_FRC+0x20E, 0x00}, {ADV_LCDC_ADDR_FRC+0x20F, 0x80},
};
/*!
********************************************************************************
** @brief	ミュート設定API
** @param	fMuteEnable	: ミュート設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetMute( flag fMuteEnable )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atQsBkg[6] = {
		{ADV_LCDC_ADDR_FRC+0x20A, 0x00}, {ADV_LCDC_ADDR_FRC+0x20B, 0x00},
		{ADV_LCDC_ADDR_FRC+0x20C, 0x00}, {ADV_LCDC_ADDR_FRC+0x20D, 0x00},
		{ADV_LCDC_ADDR_FRC+0x20E, 0x00}, {ADV_LCDC_ADDR_FRC+0x20F, 0x00},
	};
	
	eResult = eGuEntryChk();

	if(fMuteEnable){
		/* 現状のレジスタ値read */
		eResult |= eFrdGuRegRs(6, atCurrentQsBkg);
		
		/* 黒 */
		eResult |= eFrdGuRegWs(6, atQsBkg);
		
		/* ベタ選択 */
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x201,0x03);	/* できれば列挙体がいいなあ */
	}else{
		//VCOM対向調整ずれ対策	マイコンソフト変更連絡書の対応(No.YKIC-003)	//sakata20110627
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x6a07, 0x0014 );						//sakata20110627

		MDrv_Timer_Delayms(80);											//sakata20110627

		eI2CWrite( IIC_SLV_ADDR_TCON, 0x00b5, 0x03fb );						//sakata20110627
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x00b5, 0x03ff );						//sakata20110627
		
		/* 色を元に戻す */
		eResult |= eFrdGuRegWs(6, atCurrentQsBkg);
	}
	
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x200, (uint16)fMuteEnable);
	
	eResult |= eGuRegUpd();
	
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
**			各デバイスによって、詳細設定用構造体の型が異なります。
** @note
*******************************************************************************/
dResult_e eFrdGuSetTestPtn( dFrdTestPtn_e eTestPtn, dFrdGuAdjTestPtn_t *ptAdjTestPtn )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp, i;
	dFrdRegVar_t atTmp[8];
	
	if(eTestPtn >= FRD_TESTPTN_NUMMAX)	return S_SPEC_ERROR;
	
	eResult |= eGuEntryChk();
	
	/* 詳細設定から(テストパターンdebug設定内 usBitMapYのレジスタバグより) */
	if(ptAdjTestPtn != NULL){
		
		/* 水平3分割設定 */
		if(ptAdjTestPtn->ptArea3TestPtn != NULL){
			for(i=0; i<8; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x2c2+i;
			
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
			
			eResult |= eFrdGuRegWs(8, atTmp);
			
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
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x210, (uint16)ptAdjTestPtn->ptMovTestPtn->fQsMovLR);
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x211, (uint16)ptAdjTestPtn->ptMovTestPtn->ucQsMovSpeed);
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x214, (uint16)ptAdjTestPtn->ptMovTestPtn->ucHScroll);
			
			/* Internal登録 */
			if(eResult == S_SUCCESS){
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->fQsMovLR		= ptAdjTestPtn->ptMovTestPtn->fQsMovLR;
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucQsMovSpeed	= ptAdjTestPtn->ptMovTestPtn->ucQsMovSpeed;
				tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucHScroll		= ptAdjTestPtn->ptMovTestPtn->ucHScroll;
			}
		}
		
		/* テストパターンdebug設定 */
		if(ptAdjTestPtn->ptDebugTestPtn != NULL){
			if(ptAdjTestPtn->ptDebugTestPtn->fEnforce)	usTmp = 0x04;
			else										usTmp = 0x00;
			
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x200, usTmp);
			
			for(i=0; i<3; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x2CA + i;
			
			atTmp[0].usVal = (ptAdjTestPtn->ptDebugTestPtn->usBitMapY & 0x700) >> 8;
			atTmp[1].usVal =  ptAdjTestPtn->ptDebugTestPtn->usBitMapY & 0xFF;
			atTmp[2].usVal = (uint16)ptAdjTestPtn->ptDebugTestPtn->eFilmMode;
			
			eResult |= eFrdGuRegWs(3, atTmp);
			
			/* Internal登録 */
			if(eResult == S_SUCCESS){
				tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->fEnforce		= ptAdjTestPtn->ptDebugTestPtn->fEnforce;
				tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->usBitMapY	= ptAdjTestPtn->ptDebugTestPtn->usBitMapY;
				tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->eFilmMode	= ptAdjTestPtn->ptDebugTestPtn->eFilmMode;
			}
#if 1	/* Arugulaでも */
			/* usBitMapY(0x821E, 0x821Fのバグ, 一旦別の内臓パターンへ) */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x201, FRD_TESTPTN_ALLOVER-1);
			eResult |= eGuRegUpd();
			eResult |= eGuEntryChk();
#endif
		}
	}
	
	/* テストパターン選択 */
	if(eTestPtn != FRD_TESTPTN_OFF){
		if((FRD_TESTPTN_HVRAMP_ALTERNATE <= eTestPtn) && (eTestPtn <= FRD_TESTPTN_ALLOVER_ALTERNATE)){
			usTmp = 0x02;	/* 出力側のみ */
		}else{
			usTmp = 0x01;	/* 入力側のみ */
		}
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x201, (uint16)(eTestPtn-1));
		
		/* フリッカパターンの場合 */
		if((eTestPtn == FRD_TESTPTN_FLICKER_2H) || (eTestPtn == FRD_TESTPTN_FLICKER_1H)){
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x215, 0xd0);
		}
	}
	else{
		usTmp = 0x00;	/* 通常表示 */
		
		/* フリッカパターンレジスタ戻し(別に戻す必要はないが...) */
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x215, 0x00);
		
		/* 水平3分割(レジスタ0x201=0x16)状態からの解除時に
		   3領域の位相を合わせるための措置(通常表示に戻すときに
		   左スクロール(レジスタ0x201=0x0D)を設定)。
		   特に弊害無いので常に行う */
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x201, 0x0D);
	}
	
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x200, usTmp);
	
	/* REGUPD */
	eResult |= eGuRegUpd();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	FRCステータスデータ取得API
** @param	pvFrcStatusDat	: FRCステータスデータ (型定義: dFrdGuInternalDat_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			各デバイスによって、ステータスデータ型が異なります。
** @note
*******************************************************************************/
dResult_e eFrdGuGetStatus( dFrdGuInternalDat_t *pvFrcStatusDat )
{
	/* 現状の内部管理変数をステータスデータとして返す */
	*pvFrcStatusDat = tFrcInternalDat;

	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	PFゲイン設定API
** @param	ucTemp	: 温度指定[0-7] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetGain( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	
	eResult |= eGuEntryChk();
	
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1B8, (uint16)aucPFGain[ucTemp]);
	
	eResult |= eGuSetTypvGain();
	
	eResult |= eGuRegUpd();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	矩形描画設定API
** @param	fLineEnable		:矩形描画設定．ONはTRUE、OFFはFALSE (型定義: flag)
** @param	eLineColor		:矩形領域の色指定 (型定義: dFrdLineColor_e)
** @param	ptLineArea		:領域指定 (型定義: dFrdFrame_t)
**							変更がない場合は、ポインタをNULL設定する。\n
**							Xの範囲：0〜1919, Yの範囲：0〜1079．またXが0, Yが0の場合、Wの範囲： 0〜1920, Hの範囲：0〜1080
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuDrawLine( flag fLineEnable, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atTmp[8];
	uint8 i;

	eResult = eGuEntryChk();

	/* 矩形領域設定 */
	if(ptLineArea != NULL){
		if(ptLineArea->usXPos + ptLineArea->usWidth > 1920 || 
		ptLineArea->usYPos + ptLineArea->usHeight > 1080){
			return S_SPEC_ERROR;
		}

		for(i=0; i<8; i++) atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x1d3+i;
		atTmp[0].usVal = ((ptLineArea->usXPos & 0x700) >> 8);
		atTmp[1].usVal = (ptLineArea->usXPos & 0xff);
		atTmp[2].usVal = ((ptLineArea->usYPos & 0x700) >> 8);
		atTmp[3].usVal = (ptLineArea->usYPos & 0xff);
		atTmp[4].usVal = ((ptLineArea->usWidth & 0x700) >> 8);
		atTmp[5].usVal = (ptLineArea->usWidth & 0xff);
		atTmp[6].usVal = ((ptLineArea->usHeight & 0x700) >> 8);
		atTmp[7].usVal = (ptLineArea->usHeight & 0xff);

		eResult |= eFrdGuRegWs(8, atTmp);
	}
	
	/* 矩形領域の色指定 */
	for(i=0; i<3; i++) atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x1db+i;
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
	eResult |= eFrdGuRegWs(3, atTmp);
	
	/* 矩形描画のON/OFF設定 */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1d2, (uint16)fLineEnable);

	eResult |= eGuRegUpd();

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
dResult_e eFrdGuSetModeHalf( dFrdModeHalf_e eModeHalf )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp=0x00;
	
	if(eModeHalf >= FRD_MODE_HALF_NUMMAX)	return S_FAILURE;
	
	switch(eModeHalf){
		case FRD_MODE_HALF_NORMAL:
			usTmp = 0x00;
			break;
		case FRD_MODE_HALF_BOTTOM_ON:
			usTmp = 0x04;
			break;
		case FRD_MODE_HALF_UP_ON:
			usTmp = 0x05;
			break;
		case FRD_MODE_HALF_RIGHT_ON:
			usTmp = 0x06;
			break;
		case FRD_MODE_HALF_LEFT_ON:
			usTmp = 0x07;
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eResult |= eGuEntryChk();
	
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xd4, usTmp);
	/* PF半分ON/OFFもここで〜 */
	eResult |= eGuSetPFHalf(eModeHalf);
	
	eResult |= eGuRegUpd();

	return eResult;
}


/*!
********************************************************************************
** @brief	ポストフィルタ設定API
** @param	fPFEnable	: ポストフィルタ設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			工程メニュー"POSTFILTER ON/OFF"時のみ使用します。
** @note
**			低遅延モード時はONできません。
*******************************************************************************/
dResult_e eFrdGuSetPF( flag fPFEnable )
{
	dResult_e eResult = S_SUCCESS;
	uint16	usTmp;
	
	eResult = eGuEntryChk();
	
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x1df, &usTmp);
	
	if((usTmp == 1) && (fPFEnable == 1)){
		;;	/* 何もしない */
	}else{
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ad, (uint16)fPFEnable);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x1ae, (uint16)fPFEnable);
	}
	
	eResult |= eGuRegUpd();
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ポストフィルタ状態取得API
** @param	pfPFStatus	: ポストフィルタ状態を示すフラグ (型定義: flag *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			工程メニュー"POSTFILTER ON/OFF"時のみ使用します。
** @note
*******************************************************************************/
dResult_e eFrdGuGetPF( flag *pfPFStatus )
{
	dResult_e eResult = S_SUCCESS;
	uint16	usTmp;
	
	/* 1adのみ */
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x1ad, &usTmp);
	
	*pfPFStatus = (flag)usTmp;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	色温度逆補正設定API
** @param	fCtaEnable	: 色温度逆補正設定 TRUE = ON, FALSE = OFF (型定義: flag)
** @param	ptCtPoint	: 色温度逆補正設定位置ポインタ (型定義: dFrdCtPoint_t*)
**						変更がない場合はNULL設定。
** @param	ptCtVal		: 色温度補正値設定ポインタ (型定義: dFrdCtVal_t**)
**						変更がない場合はNULL設定。
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
** 			AVポジション, 入力切替等でホワイトバランス調整値, 色温度オフセット値
**			が変更する場合は、本APIをコールしてください。
*******************************************************************************/
dResult_e eFrdGuSetCtaParam( flag fCtaEnable, dFrdCtPoint_t *ptCtPoint, dFrdCtVal_t *ptCtVal )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atTmp[36];
	uint16 i;
	uint16 usCurrentCta;
	
	if(ptCtPoint != NULL){
		/* アドレス設定 */
		for(i=0; i<12; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x440+i;
		
		/* 位置設定 */
		atTmp[0].usVal = (ptCtPoint->usCtPoint1 & 0x300) >> 8;
		atTmp[1].usVal = ptCtPoint->usCtPoint1 & 0xff;
		atTmp[2].usVal = (ptCtPoint->usCtPoint2 & 0x300) >> 8;
		atTmp[3].usVal = ptCtPoint->usCtPoint2 & 0xff;
		atTmp[4].usVal = (ptCtPoint->usCtPoint3 & 0x300) >> 8;
		atTmp[5].usVal = ptCtPoint->usCtPoint3 & 0xff;
		atTmp[6].usVal = (ptCtPoint->usCtPoint4 & 0x300) >> 8;
		atTmp[7].usVal = ptCtPoint->usCtPoint4 & 0xff;
		atTmp[8].usVal = (ptCtPoint->usCtPoint5 & 0x300) >> 8;
		atTmp[9].usVal = ptCtPoint->usCtPoint5 & 0xff;
		atTmp[10].usVal = (ptCtPoint->usCtPoint6 & 0x300) >> 8;
		atTmp[11].usVal = ptCtPoint->usCtPoint6 & 0xff;

		/* 書込み */
		eResult = eFrdGuRegWs(12, atTmp);
	}
	
	/* 色温度補正値設定 */
	if(ptCtVal != NULL){
		/* アドレス設定 */
		for(i=0; i<36; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x44C+i;

		/* RED */
		atTmp[0].usVal = (ptCtVal->ptCtRedVal->usCtVal1 & 0x300) >> 8;
		atTmp[1].usVal = ptCtVal->ptCtRedVal->usCtVal1 & 0xff;
		atTmp[2].usVal = (ptCtVal->ptCtRedVal->usCtVal2 & 0x300) >> 8;
		atTmp[3].usVal = ptCtVal->ptCtRedVal->usCtVal2 & 0xff;
		atTmp[4].usVal = (ptCtVal->ptCtRedVal->usCtVal3 & 0x300) >> 8;
		atTmp[5].usVal = ptCtVal->ptCtRedVal->usCtVal3 & 0xff;
		atTmp[6].usVal = (ptCtVal->ptCtRedVal->usCtVal4 & 0x300) >> 8;
		atTmp[7].usVal = ptCtVal->ptCtRedVal->usCtVal4 & 0xff;
		atTmp[8].usVal = (ptCtVal->ptCtRedVal->usCtVal5 & 0x300) >> 8;
		atTmp[9].usVal = ptCtVal->ptCtRedVal->usCtVal5 & 0xff;
		atTmp[10].usVal = (ptCtVal->ptCtRedVal->usCtVal6 & 0x300) >> 8;
		atTmp[11].usVal = ptCtVal->ptCtRedVal->usCtVal6 & 0xff;
		/* GREEN */
		atTmp[12].usVal = (ptCtVal->ptCtGrnVal->usCtVal1 & 0x300) >> 8;
		atTmp[13].usVal = ptCtVal->ptCtGrnVal->usCtVal1 & 0xff;
		atTmp[14].usVal = (ptCtVal->ptCtGrnVal->usCtVal2 & 0x300) >> 8;
		atTmp[15].usVal = ptCtVal->ptCtGrnVal->usCtVal2 & 0xff;
		atTmp[16].usVal = (ptCtVal->ptCtGrnVal->usCtVal3 & 0x300) >> 8;
		atTmp[17].usVal = ptCtVal->ptCtGrnVal->usCtVal3 & 0xff;
		atTmp[18].usVal = (ptCtVal->ptCtGrnVal->usCtVal4 & 0x300) >> 8;
		atTmp[19].usVal = ptCtVal->ptCtGrnVal->usCtVal4 & 0xff;
		atTmp[20].usVal = (ptCtVal->ptCtGrnVal->usCtVal5 & 0x300) >> 8;
		atTmp[21].usVal = ptCtVal->ptCtGrnVal->usCtVal5 & 0xff;
		atTmp[22].usVal = (ptCtVal->ptCtGrnVal->usCtVal6 & 0x300) >> 8;
		atTmp[23].usVal = ptCtVal->ptCtGrnVal->usCtVal6 & 0xff;
		/* BLUE */
		atTmp[24].usVal = (ptCtVal->ptCtBluVal->usCtVal1 & 0x300) >> 8;
		atTmp[25].usVal = ptCtVal->ptCtBluVal->usCtVal1 & 0xff;
		atTmp[26].usVal = (ptCtVal->ptCtBluVal->usCtVal2 & 0x300) >> 8;
		atTmp[27].usVal = ptCtVal->ptCtBluVal->usCtVal2 & 0xff;
		atTmp[28].usVal = (ptCtVal->ptCtBluVal->usCtVal3 & 0x300) >> 8;
		atTmp[29].usVal = ptCtVal->ptCtBluVal->usCtVal3 & 0xff;
		atTmp[30].usVal = (ptCtVal->ptCtBluVal->usCtVal4 & 0x300) >> 8;
		atTmp[31].usVal = ptCtVal->ptCtBluVal->usCtVal4 & 0xff;
		atTmp[32].usVal = (ptCtVal->ptCtBluVal->usCtVal5 & 0x300) >> 8;
		atTmp[33].usVal = ptCtVal->ptCtBluVal->usCtVal5 & 0xff;
		atTmp[34].usVal = (ptCtVal->ptCtBluVal->usCtVal6 & 0x300) >> 8;
		atTmp[35].usVal = ptCtVal->ptCtBluVal->usCtVal6 & 0xff;
	
		/* 書込み */
		eResult = eFrdGuRegWs(36, atTmp);
	}
	
	/* 色温度逆補正のON/OFF設定 */
	/* 現状のON/OFF設定と同じ要求かを確認 */
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x424, &usCurrentCta) == S_FAILURE)	return S_FAILURE;
	if((flag)usCurrentCta != fCtaEnable)	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x424, (uint16)fCtaEnable);
	
	/* REGUPD */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x403, 1);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	肌色コントロールAPI
** @param	sHue		: 色相 範囲: -2048〜+2048 (型定義: int16)
** @param	sSat		: 彩度 範囲: 0〜+4096 (型定義: int16)
** @param	sVal		: 明度 範囲: 0〜+4096 (型定義: int16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
** 			本APIをコールする場合は、事前に色温度逆補正設定API
**			をコールしておいてください。
*******************************************************************************/
dResult_e eFrdGuSetSkinCtl( int16 sHue, int16 sSat, int16 sVal )
{
	dResult_e eResult = S_SUCCESS;
	uint8	i, j, k;
	/* 行、列の順 */
	double SkinCtlMtx1[3][3] = {
		{1,			0,			1.5748	},
		{1,			-0.1873,		-0.4681	},
		{1,			1.8556,		0		},
	};
	double SkinCtlMtx2[3][3] = {
		{1,			0,			0		},
		{0,			0,			0		},
		{0,			0,			0		},
	};
	double SkinCtlMtx3[3][3] = {
		{0.2126,	0.7152,		0.0722	},
		{-0.1146,	-0.3854,	0.5		},
		{0.5,		-0.4542,	-0.0458	},
	};
	double ResMtx1[3][3], ResMtx2[3][3];
	double LVal, SinElem, CosElem, SElem;
	dFrdRegVar_t atTmp[18];
	uint16 usPreVal, usTmp[2];
	double CoefM[3];

	/* 本APIがコールされている = 肌色コントロールが有効 */
	if(f1stSkinCtlCall){
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x47f, 0x02);
		eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x402, 0x00);
		
		f1stSkinCtlCall = FALSE;
	}

	/* 第4点の色温度補正値RGBより白色点補正係数の計算 */
	/* Red */
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x452, &usTmp[0]) == S_FAILURE)	return S_FAILURE;
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x453, &usTmp[1]) == S_FAILURE)	return S_FAILURE;
	CoefM[0] = (double)((usTmp[0] << 8) | usTmp[1]);
	/* Grn */
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x45E, &usTmp[0]) == S_FAILURE)	return S_FAILURE;
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x45F, &usTmp[1]) == S_FAILURE)	return S_FAILURE;
	CoefM[1] = (double)((usTmp[0] << 8) | usTmp[1]);
	/* Blu */
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x46A, &usTmp[0]) == S_FAILURE)	return S_FAILURE;
	if(eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x46B, &usTmp[1]) == S_FAILURE)	return S_FAILURE;
	CoefM[2] = (double)((usTmp[0] << 8) | usTmp[1]);

	for(i=0; i<3; i++) CoefM[i] /= (double)(164*16);
	
	/* hue, sat, valの変換 */
	if(-2048 <= sHue && sHue <= 2048) SinElem = ((double)sHue) * 0.7071 / 2048;
	else return S_SPEC_ERROR;
	
	//CosElem = pow((1 - pow(SinElem, 2)), 0.5);
	CosElem = dGuSqrt((double)(1 - (SinElem*SinElem)));
	
	if(0 <= sSat && sSat <= 4096) SElem = 2*((double)sSat)/4096;
	else return S_SPEC_ERROR;
	
	if(0 <= sVal && sVal <= 4096) LVal = 0.5 + ((double)sVal)/4096;
	else return S_SPEC_ERROR;

	/* SkinCtlMtx2に代入 */
	SkinCtlMtx2[1][1] = SkinCtlMtx2[2][2] = SElem * CosElem;
	SkinCtlMtx2[1][2] = -SElem * SinElem;
	SkinCtlMtx2[2][1] =  SElem * SinElem;
	
	/* MTX演算 */
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			ResMtx1[i][j] = 0.0;
			for(k=0; k<3; k++){
				ResMtx1[i][j] += SkinCtlMtx1[i][k] * SkinCtlMtx2[k][j];
			}
		}
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			ResMtx2[i][j] = 0.0;
			for(k=0; k<3; k++){
				ResMtx2[i][j] += ResMtx1[i][k] * SkinCtlMtx3[k][j];
			}
			/* MTX全体に明度の係数を掛けて調整 */
			ResMtx2[i][j] *= LVal;
			
			/* 白色点補正係数を掛ける */
			if(1.0 >= SElem){
				CoefM[i] = CoefM[i] * (1-SElem) + SElem;
				ResMtx2[i][j] *= CoefM[i];
			}
		}
	}
	
	/* ResMtx2内の成分を 符号、整数部(1bit)、小数部(12bit)の2の補数に変換して代入 */
	for(i=0; i<18; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x480+i;
	/* 値代入 */
	i = 0;
	for(j=0; j<3; j++){
		for(k=0; k<3; k++){
			usPreVal = usGuChgDblToUs(ResMtx2[j][k]);
			atTmp[ i ].usVal = (usPreVal & 0x3f00) >> 8;
			atTmp[i+1].usVal = usPreVal & 0xff;
			i += 2;
		}
	}
	/* MTX書込み */
	eResult |= eFrdGuRegWs(18, atTmp);
	
	/* REGUPD */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x403, 1);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	肌色領域表示API
** @param	fDispEnable	: 肌色領域表示設定 TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuDispScore( flag fDispEnable )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usKSat, usKHue;
	
	if(fDispEnable){
		/* ON */
		eResult  = eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x42B, 0x03);
		usKSat = usKHue = 0x7F;
	}else{
		/* OFF */
		eResult  = eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x42B, 0x00);
		usKSat = usCurrentKSat;
		usKHue = usCurrentKHue;
	}
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x426, usKSat);
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x427, usKHue);
	
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x403, 1);
	
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
dResult_e eFrdGuSetOutFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	uint32 auiRomAddr[2], auiCrcAddr[2];
	
	if(eCurrentInputFreq == eInputFreq)	return S_SUCCESS;
	
	/* パイプラインOFF */
	eResult |= eFrdGuStandby(FALSE);
	
	/* パラメータload(subB) */
	eResult |= eGuGetTbcRomAddr(eInputFreq, &auiRomAddr[0], &auiCrcAddr[0]);
	
	eResult |= eFrdLcdGuRomManualLoad(auiCrcAddr[0], GU_REGADDR_ETC +0x16, 1, FALSE);
	eResult |= eFrdLcdGuRomManualLoad(auiRomAddr[0], ADV_LCDC_ADDR_FRC+0xb00, GU_ROMSIZE_TBC, TRUE);

	/* 101129 H.Nishimura: Wソース限定の処理を追加 */	//<-2011/02/24	四開発追加
	eResult |= eFrdLcdGuSetOutFreq( eInputFreq );

	/* Arugula アプリケーションノート[HW] 5.2.入力数端数に応じた制御と同様の処理 */
	eResult |= eFrdGuRegW(0x1005, aucBintDelay[eInputFreq]);
	eResult |= eFrdGuRegW(0x1085, aucBintDelay[eInputFreq]);
	eResult |= eFrdGuRegW(0x1002, 0x01);
	eResult |= eFrdGuRegW(0x1082, 0x01);
	
	/* 100329 ohashi: 60inchのみレジスタVDPを設定 */
	eResult |= eFrdLcdGuGetRevInfo(aucRomVer);
	if(aucRomVer[FRDLCD_REVISION_INCHI] == 0x60){
		eResult |= eFrdGuRegW(0x6a0e, aucVdp[eInputFreq]);
		eResult |= eFrdGuRegW(0x6a8e, aucVdp[eInputFreq]);
	}
	
	/* PF LUTのload */
	switch(eInputFreq){
		case FRD_INPUT_FREQ_48HZ:
		case FRD_INPUT_FREQ_50HZ:
			if((eCurrentInputFreq != FRD_INPUT_FREQ_48HZ) && (eCurrentInputFreq != FRD_INPUT_FREQ_50HZ)){
				eResult |= eGuGetPfLutRomAddr(eInputFreq, auiRomAddr, auiCrcAddr);
				
				eResult |= eFrdLcdGuRomManualLoad(auiCrcAddr[0], GU_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdGuRomManualLoad(auiRomAddr[0], ADV_LCDC_ADDR_FRC+0x500, GU_ROMSIZE_PFLUT56, TRUE);
				eResult |= eFrdLcdGuRomManualLoad(auiCrcAddr[1], GU_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdGuRomManualLoad(auiRomAddr[1], ADV_LCDC_ADDR_FRC+0x700, GU_ROMSIZE_PFLUT7, TRUE);
			}
			break;
		case FRD_INPUT_FREQ_60HZ:
			if(eCurrentInputFreq != FRD_INPUT_FREQ_60HZ){
				eResult |= eGuGetPfLutRomAddr(eInputFreq, auiRomAddr, auiCrcAddr);
				
				eResult |= eFrdLcdGuRomManualLoad(auiCrcAddr[0], GU_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdGuRomManualLoad(auiRomAddr[0], ADV_LCDC_ADDR_FRC+0x500, GU_ROMSIZE_PFLUT56, TRUE);
				eResult |= eFrdLcdGuRomManualLoad(auiCrcAddr[1], GU_REGADDR_ETC +0x16, 1, FALSE);
				eResult |= eFrdLcdGuRomManualLoad(auiRomAddr[1], ADV_LCDC_ADDR_FRC+0x700, GU_ROMSIZE_PFLUT7, TRUE);
			}
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eCurrentInputFreq = eInputFreq;
	
	/* パイプラインON */
	eResult |= eFrdGuStandby(TRUE);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	フリーラン設定API (FRC側)
** @param	fFreeRunEnable	: フリーラン設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetFreeRun( flag fFreeRunEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	/* パイプラインOFF */
	eResult |= eFrdGuStandby(FALSE);
	
	/* ON/OFF */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x00, fFreeRunEnable);
	
	/* パイプラインON */
	eResult |= eFrdGuStandby(TRUE);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	入力データ確認API
** @param	usCvV		: 画面垂直方向指定位置 範囲: 0〜1079 (型定義: uint16)
** @param	usCvH		: 画面水平方向指定位置 範囲: 0〜1919 (型定義: uint16) ※水平方向は偶数画素
** @param	ptPixelData	: 取得データ (読込みのみ)	(型定義: dFrdPixelData_t*)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント:
** @note	
********************************************************************************/
dResult_e eFrdGuGetRgb( uint16 usCvV, uint16 usCvH, dFrdGuPixelDat_t *ptPixelDat )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atTmp[6];
	uint8	i;
	
	/* 指定位置範囲確認 */
	if(usCvV >= 1080 || usCvH >= 1920)	return S_FAILURE;
	
	/* 画面方向指定位置設定 */
	for(i=0; i<4; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x42C+i;
	atTmp[0].usVal = (usCvV & 0x700) >> 8;
	atTmp[1].usVal = usCvV & 0xff;
	atTmp[2].usVal = (usCvH & 0x700) >> 8;
	atTmp[3].usVal = usCvH & 0xff;
	
	eResult = eFrdGuRegWs(4, atTmp);
	
	/* REGUPD */
	eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x405, 1);
	
	/* 22msec（48Hzを考慮）のwaitを挿入 */
	
	MDrv_Timer_Delayms(22);

	/* 読込み */
	for(i=0; i<6; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x470+i;
	eResult |= eFrdGuRegRs(6, atTmp);
	
	/* 読込んだ値を渡す */
	ptPixelDat->usCvV0 = ((atTmp[0].usVal) << 8) | atTmp[1].usVal ;
	ptPixelDat->usCvV1 = ((atTmp[2].usVal) << 8) | atTmp[3].usVal ;
	ptPixelDat->usCvV2 = ((atTmp[4].usVal) << 8) | atTmp[5].usVal ;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	鮮鋭化設定API
** @param	eSvMode	: 鮮鋭化設定 (型定義: dFrdGuSvMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetSv( dFrdGuSvMode_e eSvMode )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	eResult = eGuEntryChk();
	
	switch(eSvMode){
		case FRDGU_SVMODE_OFF:
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x948, 0);
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x949, 0);
			break;
		case FRDGU_SVMODE_H:
		case FRDGU_SVMODE_M:
		case FRDGU_SVMODE_L:
		case FRDGU_SVMODE_DEMO:
			/* ROMアドレス探索 */
			eResult |= eGuGetSvRomAddr(eSvMode, &uiRomAddr, &uiCrcAddr);
			
			/* マニュアルロード */
			eResult |= eFrdLcdGuRomManualLoad(uiCrcAddr, GU_REGADDR_ETC +0x16, 1, FALSE);
			eResult |= eFrdLcdGuRomManualLoad(uiRomAddr, ADV_LCDC_ADDR_FRC+0x94D, GU_ROMSIZE_SV, TRUE);
			
			/* ON設定 */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x948, 1);
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x949, 1);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eResult |= eGuRegUpd();
	
	eCurrentSvMode = eSvMode;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	デジャダ設定API
** @param	eDjAdj	: デジャダ強調設定 (型定義: dFrdGuDjAdj_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			低遅延モード時は強, 中, 弱, 5-5の設定ができません。
*******************************************************************************/
dResult_e eFrdGuSetDjMode( dFrdGuDjAdj_e eDjAdj )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	printf("eFrdGuSetDjMode1\r\n");
	eResult = eGuEntryChk();
	printf("eFrdGuSetDjMode2\r\n");
	switch(eDjAdj){
		case FRDGU_DJ_ADJ_H:
		case FRDGU_DJ_ADJ_M:
		case FRDGU_DJ_ADJ_L:
		case FRDGU_DJ_ADJ_55:
		case FRDGU_DJ_ADJ_DEMO:
			printf("eFrdGuSetDjMode:FRDGU_DJ_ADJ_DEMO\r\n");
			/* ROMアドレス探索 */
			eResult |= eGuGetDjAdjRomAddr(eDjAdj, &uiRomAddr, &uiCrcAddr);
			
			/* マニュアルロード */
			eResult |= eFrdLcdGuRomManualLoad(uiCrcAddr, GU_REGADDR_ETC +0x16, 1, FALSE);
			eResult |= eFrdLcdGuRomManualLoad(uiRomAddr, ADV_LCDC_ADDR_FRC+0x830, GU_ROMSIZE_DJADJ-0x21, TRUE);
			
			if((eDjAdj==FRDGU_DJ_ADJ_DEMO) || (eDjAdj==FRDGU_DJ_ADJ_H)){
//				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xAE, 0x60);/* SCENE_HIS */
				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xAE, 0x00);/* SCENE_HIS *//* bit[5:6]が別のレジスタに移動しました */
				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x128, 0x06);/* SCENE_HIS *//* bit[5:6]が別のレジスタに移動しました */	//<- 2011/02/24	四開発追加
			}
			else{
//				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xAE, 0x6A);/* SCENE_HIS */
				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0xAE, 0x0A);/* SCENE_HIS *//* bit[5:6]が別のレジスタに移動しました */
				eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x128, 0x06);/* SCENE_HIS *//* bit[5:6]が別のレジスタに移動しました */	//<- 2011/02/24	四開発追加
			}
			
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x800, 0x01);	/* FRC_FILM_MODE */
			
			break;
		case FRDGU_DJ_ADJ_OFF:
		printf("eFrdGuSetDjMode:FRDGU_DJ_ADJ_OFF\r\n");
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x800, 0x00);	/* FRC_FILM_MODE */
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	printf("eFrdGuSetDjMode3\r\n");
	eResult |= eGuRegUpd();
	printf("eFrdGuSetDjMode4\r\n");
	eCurrentDjAdj = eDjAdj;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	Filmモード設定API
** @param	eMode	: Filmモード設定 (型定義: dFrdMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetFilmMode( dFrdMode_e eMode )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eMode){
		case FRD_MODE_OFF:
		printf("eFrdGuSetFilmMode:FRD_MODE_OFF\r\n");
			if(eCurrentFilmMode != FRD_MODE_OFF){
				eResult |= eGuSetFilmMode(FRD_MODE_OFF);
			}
			/* HW制約解除 */
			if(fHWR){
				eResult |= eGuSetQsMode(eCurrentQsMode);
				fHWR = FALSE;
			}
			break;
		case FRD_MODE_STD:
			printf("eFrdGuSetFilmMode:FRD_MODE_STD\r\n");
			if((eCurrentQsMode == FRD_MODE_OFF) || (eCurrentQsMode == FRD_MODE_STD)){
				/* FILM STDの55を強制OFF */
				eResult |= eGuSetFilmMode(FRD_MODE_OFF);
			}else{
				eResult |= eGuSetFilmMode(FRD_MODE_STD);
			}
			/* HW制約解除 */
			if(fHWR){
				eResult |= eGuSetQsMode(eCurrentQsMode);
				fHWR = FALSE;
			}
			break;
		case FRD_MODE_ADL:
		case FRD_MODE_ADH:
			printf("eFrdGuSetFilmMode:FRD_MODE_ADL\r\n");
			eResult |= eGuSetFilmMode(eMode);
			if((eCurrentQsMode == FRD_MODE_OFF) || (eCurrentQsMode == FRD_MODE_STD)){
				if(!fHWR){
					/* HW制約設定 */
					eResult |= eFrdGuSetSv(FRDGU_SVMODE_OFF);
					eResult |= eFrdGuSetMode(TRUE);
					eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x837, 0);
					fHWR = TRUE;
				}
			}
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	eCurrentFilmMode = eMode;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	Qsモード設定API
** @param	eMode	: Qsモード設定 (型定義: dFrdMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetQsMode( dFrdMode_e eMode )
{
	dResult_e eResult = S_SUCCESS;
	printf("eFrdGuSetQsMode++, eMode=%x\r\n",eMode);
	switch(eMode){
		case FRD_MODE_OFF:
		case FRD_MODE_STD:
			printf("eFrdGuSetQsMode, FRD_MODE_OFF, eCurrentFilmMode=%x\r\n",eCurrentFilmMode);
			/* Filmは？ */
			switch(eCurrentFilmMode){		
				case FRD_MODE_OFF:
					eResult |= eGuSetQsMode(eMode);
					break;
				case FRD_MODE_STD:
					eResult |= eGuSetQsMode(eMode);
					if((eCurrentQsMode == FRD_MODE_ADL) || (eCurrentQsMode == FRD_MODE_ADH)){
						/* FILM STDの55を強制OFF */
						eResult |= eGuSetFilmMode(FRD_MODE_OFF);
						//f55toOff = TRUE;
					}
					break;
				case FRD_MODE_ADL:
				case FRD_MODE_ADH:
					/* QS ON/OFF設定 : 通常は関数eGuSetQsMode内での設定だが呼ばれないのでここで設定する */
					if(eMode == FRD_MODE_OFF)	eResult |= eFrdLcdGuSetQsEn(FALSE);
					else						eResult |= eFrdLcdGuSetQsEn(TRUE);
					
					/* HW制約設定 */
					if(!fHWR){
						eResult |= eFrdGuSetSv(FRDGU_SVMODE_OFF);
						eResult |= eFrdGuSetMode(TRUE);
						eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x837, 0);
						fHWR = TRUE;
					}
					break;
				default:
					eResult |= S_SPEC_ERROR;
					break;
			}
			break;
		case FRD_MODE_ADL:
		case FRD_MODE_ADH:
			printf("eFrdGuSetQsMode, FRD_MODE_ADH, eCurrentFilmMode=%x\r\n",eCurrentFilmMode);
			/* Filmは？ */
			switch(eCurrentFilmMode){
				case FRD_MODE_OFF:
					printf("eFrdGuSetQsMode, FRD_MODE_OFF\r\n");
					eResult |= eGuSetQsMode(eMode);
					break;
				case FRD_MODE_STD:
					eResult |= eGuSetQsMode(eMode);
					if((eCurrentQsMode == FRD_MODE_OFF) || (eCurrentQsMode == FRD_MODE_STD)){
						/* FILM STDの強制OFFを解除 */
						eResult |= eGuSetFilmMode(FRD_MODE_STD);
						//f55toOff = TRUE;
					}
					break;
				case FRD_MODE_ADL:
				case FRD_MODE_ADH:
					eResult |= eGuSetQsMode(eMode);
					break;
				default:
					eResult |= S_SPEC_ERROR;
					break;
			}
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	printf("eFrdGuSetQsMode--\r\n");
	eCurrentQsMode = eMode;
	
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
dResult_e eFrdGuAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i;
	
	/* FRC周波数設定 */
	for(i=0; i<3; i++){
		if( (dFrdInputFreq_e)i != eCurrentInputFreq ){
			eResult |= eFrdGuSetOutFreq( (dFrdInputFreq_e)i );
		}
	}
	eResult |= eFrdGuSetOutFreq( eCurrentInputFreq );/* 元に戻す */
	
	/* 鮮鋭化設定 */
	for(i=0; i<5; i++){
		if( (dFrdGuSvMode_e)i != eCurrentSvMode ){
			eResult |= eFrdGuSetSv( (dFrdGuSvMode_e)i );
		}
	}
	eResult |= eFrdGuSetSv( eCurrentSvMode );/* 元に戻す */
	
	/* デジャダ設定 */
	for(i=0; i<6; i++){
		if( (dFrdGuDjAdj_e)i != eCurrentDjAdj ){
			eResult |= eFrdGuSetDjMode( (dFrdGuDjAdj_e)i );
		}
	}
	eResult |= eFrdGuSetDjMode( eCurrentDjAdj );/* 元に戻す */
	
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
dResult_e eFrdGuSetModeChk( dFrdModeChk_e eModeChk )
{
	dResult_e eResult = S_SUCCESS;
	dFrdModeHalf_e eModeHalf = FRD_MODE_HALF_NORMAL;
	dFrdTestPtn_e eTestPtn = FRD_TESTPTN_OFF;
	dFrdGuInternalDat_t tFrcStatusDat;
	dFrdGuAdjTestPtn_t tAdjustTestPtn;
	flag fMode = FALSE;
	
	/* FRC ON/OFFテスト直前のFRC状態の確保 */
	if(!fCurrentModeChk) eFrdGuGetMode(&fTmpMode);
	
	eResult |= eFrdGuGetStatus(&tFrcStatusDat);
	tFrcStatusDat.tCurrentAdjTestPtn.ptArea3TestPtn = NULL;
	
	tAdjustTestPtn = tFrcStatusDat.tCurrentAdjTestPtn;
	
	switch(eModeChk){
		case FRD_MODE_CHK_OFF:
			if((3 <= ucCurrentLvl) && (ucCurrentLvl <= 7)){
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
	
	eResult |= eFrdGuSetMode(fMode);
	eResult |= eFrdGuSetModeHalf(eModeHalf);
	eResult |= eFrdGuSetTestPtn(eTestPtn, &tAdjustTestPtn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	3領域スクロール設定 API
** @param	fArea3En		:3領域設定．ONはTRUE、OFFはFALSE (型定義: flag)
** @param	ptArea3Scrl		:テストパターン詳細設定構造体のポインタ (型定義: dFrdArea3Scrl_t *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetArea3Scrl( flag fArea3En, dFrdArea3Scrl_t *ptArea3Scrl )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fArea3En){
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea2Y = ptArea3Scrl->usArea2Y;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea3Y = ptArea3Scrl->usArea3Y;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea1Speed = ptArea3Scrl->tArea3Speed.ucArea1Speed;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea2Speed = ptArea3Scrl->tArea3Speed.ucArea2Speed;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea3Speed = ptArea3Scrl->tArea3Speed.ucArea3Speed;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea1Mov = (dFrdGuArea3Mov_e)ptArea3Scrl->tArea3Mov.eArea1Mov;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea2Mov = (dFrdGuArea3Mov_e)ptArea3Scrl->tArea3Mov.eArea2Mov;
		tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea3Mov = (dFrdGuArea3Mov_e)ptArea3Scrl->tArea3Mov.eArea3Mov;
		
		tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn = NULL;
		tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn = NULL;
		
		eResult |= eFrdGuSetTestPtn(FRD_TESTPTN_AREA3, &(tFrcInternalDat.tCurrentAdjTestPtn));
	}else{
		eResult |= eFrdGuSetTestPtn(FRD_TESTPTN_OFF, NULL);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	TypvGain設定 API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	1秒毎にコールしてください。
*******************************************************************************/
dResult_e eFrdGuSetTypvGain( void )
{
	return (eGuSetTypvGain());
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
dResult_e eFrdGuGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp;
	
	ptCurrentVal->eFreq		= eCurrentInputFreq;
//	ptCurrentVal->ucLvl		= ucCurrentLvl;
	ptCurrentVal->ucLvl		= ucLcdGuLvl;
	eResult |= eFrdGuRegR(GU_REGADDR_FRC+0x1df, &usTmp);
	ptCurrentVal->fFrcEn	= (flag)(!usTmp);
	eResult |= eFrdGuRegR(0xa08, &usTmp);
	ptCurrentVal->fQsEn		= (flag)((usTmp & 0x10) >> 4);
	
	return eResult;
}


/**
 * @brief	REGUPD確認子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuEntryChk( void )
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
		eResult = eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x05, &usGetVal);
		
		ucGardCnt++;
		
		if(ucGardCnt > 10){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "[GU]: REGUPD remains 1 !!\n");
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
static dResult_e eGuRegUpd( void )
{
	dResult_e eResult = S_SUCCESS;
	
	eResult = eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x05, 1);
	
	return eResult;
}


/* InitStatusに必要 */
static dFrdGuArea3TestPtn_t	tArea3TestPtn;
static dFrdGuMovTestPtn_t	tMovTestPtn;
static dFrdGuDebugTestPtn_t	tDebugTestPtn;

static dFrdGuArea3Speed_t	tArea3Speed;
static dFrdGuArea3Mov_t		tArea3Mov;

/* 080829 ohashi: 構造体にする必要はないが、暫定でまとめている */
typedef struct{
	/* sub0 */
	uint32	uiHdiffThld;
	uint16	usBetaThldHigh;
	uint16	usBetaThldLow;
	uint16	usOverThldHigh;
	uint16	usOverThldLow;
	uint16	usBetaOverThldHigh;
	uint16	usBetaOverThldLow;
	
	uint32	uiDrHistThld;
	uint16	usDrBetaThldHigh;
	uint16	usDrOverThldHigh;
	uint16	usDrBetaOverThldHigh;
	
	uint32	uiFdiffThldHigh;
	uint16	usIntpAlpaLimitHigh;
	/* sub1 */
	uint32	uiScFdiffThldHigh;
	uint32	uiScFdiffThldLow;
	
	uint16	usDrBetaThldLow;
	uint16	usDrOverThldLow;
	uint16	usDrBetaOverThldLow;
	
	uint32	uiFdiffThldLow;
	uint16	usAdapZThldHigh;
	uint16	usAdapZThldLow;
	uint16	usIntpAlpaLimitLow;
	/* sub0 0xff */
	uint8	ucTypvGain;
#if 0	/* この2つは直接値を代入するので必要ない */
	uint16	usVhistPeakThldLow;
	uint16	usVhistPeakThldHigh;
#endif
} dArAspectSizeParam_t;

static dArAspectSizeParam_t tAspectSizeParam;

/**
 * @brief	ステータスデータを初期化する子関数
 * @param	void
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuInitStatus( void )
{
	printf("eGuInitStatus1\r\n");
	dResult_e eResult = S_SUCCESS;
	uint16	usTmp, i;
	dFrdRegVar_t atTmp[33];
	
	/*************/
	/* TestPtn分 */
	/*************/
	/* 箱詰め(前準備) */
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn	= &tArea3TestPtn;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn		= &tMovTestPtn;
	tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn	= &tDebugTestPtn;

	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed	= &tArea3Speed;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov	= &tArea3Mov;

	/* テストパターン詳細設定状態を初期化 */
	/* tDebugTestPtnのtDispTp */
	eResult = eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x200, &usTmp);

	tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->fEnforce	= (flag)((usTmp & 0x04) >>2);

	for(i=0; i<5; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x210+i;
	eResult |= eFrdGuRegRs(5, atTmp);
	
	/* tMovTestPtn */
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->fQsMovLR		= (flag)atTmp[0].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucQsMovSpeed	= (uint8)atTmp[1].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptMovTestPtn->ucHScroll		= (uint8)atTmp[4].usVal;
	
	for(i=0; i<11; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x2c2+i;
	eResult |= eFrdGuRegRs(11, atTmp);
	
	/* tArea3TestPtn */
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea2Y = ((atTmp[0].usVal & 0x07) << 8) | (atTmp[1].usVal & 0xff);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->usArea3Y = ((atTmp[2].usVal & 0x07) << 8) | (atTmp[3].usVal & 0xff);
	
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea1Speed = (uint8)atTmp[4].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea2Speed = (uint8)atTmp[5].usVal;
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Speed->ucArea3Speed = (uint8)atTmp[6].usVal;
	
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea1Mov = (dFrdGuArea3Mov_e)(atTmp[7].usVal & 0x03);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea2Mov = (dFrdGuArea3Mov_e)((atTmp[7].usVal & 0x0c) >> 2);
	tFrcInternalDat.tCurrentAdjTestPtn.ptArea3TestPtn->ptArea3Mov->eArea3Mov = (dFrdGuArea3Mov_e)((atTmp[7].usVal & 0x30) >> 4);
	
	/* tDebugTestPtnの残り */
	tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->usBitMapY	= ((atTmp[8].usVal & 0x07) << 8) | (atTmp[9].usVal & 0xff);
	tFrcInternalDat.tCurrentAdjTestPtn.ptDebugTestPtn->eFilmMode	= (dFrdGuFilmMode_e)atTmp[10].usVal;
	
	printf("eGuInitStatus2\r\n");
	/**********/
	/* Edge分 */
	/**********/
	
	/* sub0 */
	for(i=0; i<33; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x9f +i;
	eResult |= eFrdGuRegRs(33, atTmp);
	
	tAspectSizeParam.uiHdiffThld		= (((atTmp[0].usVal << 16) & 0x0f0000) | ((atTmp[1].usVal << 8) & 0x00ff00) | (atTmp[2].usVal & 0x0000ff));
	tAspectSizeParam.usBetaThldHigh			= (((atTmp[3].usVal << 8) & 0x7f00) | (atTmp[4].usVal & 0x00ff));
	tAspectSizeParam.usBetaThldLow			= (((atTmp[5].usVal << 8) & 0x7f00) | (atTmp[6].usVal & 0x00ff));
	tAspectSizeParam.usOverThldHigh			= (((atTmp[7].usVal << 8) & 0x7f00) | (atTmp[8].usVal & 0x00ff));
	tAspectSizeParam.usOverThldLow			= (((atTmp[9].usVal << 8) & 0x7f00) | (atTmp[10].usVal & 0x00ff));
	tAspectSizeParam.usBetaOverThldHigh		= (((atTmp[11].usVal << 8) & 0xff00) | (atTmp[12].usVal & 0x00ff));
	tAspectSizeParam.usBetaOverThldLow		= (((atTmp[13].usVal << 8) & 0xff00) | (atTmp[14].usVal & 0x00ff));
	
	tAspectSizeParam.uiDrHistThld		= (((atTmp[17].usVal << 16) & 0x0f0000) | ((atTmp[18].usVal << 8) & 0x00ff00) | (atTmp[19].usVal & 0x0000ff));
	tAspectSizeParam.usDrBetaThldHigh		= (((atTmp[20].usVal << 8) & 0x7f00) | (atTmp[21].usVal & 0x00ff));
	tAspectSizeParam.usDrOverThldHigh		= (((atTmp[22].usVal << 8) & 0x7f00) | (atTmp[23].usVal & 0x00ff));
	tAspectSizeParam.usDrBetaOverThldHigh	= (((atTmp[24].usVal << 8) & 0xff00) | (atTmp[25].usVal & 0x00ff));
	
	tAspectSizeParam.uiFdiffThldHigh	= (((atTmp[28].usVal << 16) & 0x070000) | ((atTmp[29].usVal << 8) & 0x00ff00) | (atTmp[30].usVal & 0x0000ff));
	tAspectSizeParam.usIntpAlpaLimitHigh	= (((atTmp[31].usVal << 8) & 0x0700) | (atTmp[32].usVal & 0x00ff));
	
	/* sub1 */
	for(i=0; i<20; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x122 +i;
	eResult |= eFrdGuRegRs(20, atTmp);
	
	tAspectSizeParam.uiScFdiffThldHigh	= (((atTmp[0].usVal << 16) & 0x070000) | ((atTmp[1].usVal << 8) & 0x00ff00) | (atTmp[2].usVal & 0x0000ff));
	tAspectSizeParam.uiScFdiffThldLow	= (((atTmp[3].usVal << 16) & 0x070000) | ((atTmp[4].usVal << 8) & 0x00ff00) | (atTmp[5].usVal & 0x0000ff));
	
	tAspectSizeParam.usDrBetaThldLow		= (((atTmp[14].usVal << 8) & 0x7f00) | (atTmp[15].usVal & 0x00ff));
	tAspectSizeParam.usDrOverThldLow		= (((atTmp[16].usVal << 8) & 0x7f00) | (atTmp[17].usVal & 0x00ff));
	tAspectSizeParam.usDrBetaOverThldLow	= (((atTmp[18].usVal << 8) & 0xff00) | (atTmp[19].usVal & 0x00ff));
	printf("eGuInitStatus3\r\n");
	/* 次sub1の2から */
	for(i=0; i<18; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x148 +i;
	eResult |= eFrdGuRegRs(18, atTmp);

	tAspectSizeParam.uiFdiffThldLow		= (((atTmp[0].usVal << 16) & 0x070000) | ((atTmp[1].usVal << 8) & 0x00ff00) | (atTmp[2].usVal & 0x0000ff));
	tAspectSizeParam.usAdapZThldHigh		= (((atTmp[9].usVal << 8) & 0x7f00) | (atTmp[10].usVal & 0x00ff));
	tAspectSizeParam.usAdapZThldLow			= (((atTmp[11].usVal << 8) & 0x7f00) | (atTmp[12].usVal & 0x00ff));
	tAspectSizeParam.usIntpAlpaLimitLow		= (((atTmp[16].usVal << 8) & 0x0700) | (atTmp[17].usVal & 0x00ff));
	
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xff, &usTmp);
	tAspectSizeParam.ucTypvGain = (uint8)usTmp;
	printf("eGuInitStatus4\r\n");
	return S_SUCCESS;
}


/**
 * @brief	アスペクトサイズに依存するパラメータ群の設定子関数
 * @param	dFrdFrame_t *ptEdgeFrame
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuReflectAspectSize( dFrdFrame_t *ptEdgeFrame )
{
	dResult_e eResult = S_SUCCESS;
	uint32			uiTmp;
	dFrdRegVar_t	atTmp[33];
	uint8			i, ucAspect;
									/* 4:3			16:9  */
	uint16 usTmp, usVhlst[2][2] = {{0x00, 0xe1}, {0x01, 0x2c}};
	
	
	fRate = ((float)ptEdgeFrame->usWidth / (float)1920) * ((float)ptEdgeFrame->usHeight / (float)1080);
	
	if(fRate < 0)	return S_FAILURE;
	
	/************/
	/* sub0から */
	/************/
	for(i=0; i<33; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x9f +i;
	
	/* HDIFF_THLD */
	uiTmp = tAspectSizeParam.uiHdiffThld;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[0].usVal = (uint16)((uiTmp & 0x0f0000) >> 16);
	atTmp[1].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[2].usVal = (uint16)(uiTmp & 0x0000ff);
	
	/* BETA_THLD_HIGH */
	uiTmp = tAspectSizeParam.usBetaThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[3].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[4].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* BETA_THLD_LOW */
	uiTmp = tAspectSizeParam.usBetaThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[5].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[6].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* OVER_THLD_HIGH */
	uiTmp = tAspectSizeParam.usOverThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[7].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[8].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* OVER_THLD_LOW */
	uiTmp = tAspectSizeParam.usOverThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[9].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[10].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* BETA_OVER_THLD_HIGH */
	uiTmp = tAspectSizeParam.usBetaOverThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[11].usVal = (uint16)((uiTmp & 0xff00) >> 8);
	atTmp[12].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* BETA_OVER_THLD_LOW */
	uiTmp = tAspectSizeParam.usBetaOverThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[13].usVal = (uint16)((uiTmp & 0xff00) >> 8);
	atTmp[14].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* 0xae, 0xaf飛ばし */
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xae, &atTmp[15].usVal);
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xaf, &atTmp[16].usVal);
	
	/* DR_HIST_THLD */
	uiTmp = tAspectSizeParam.uiDrHistThld;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[17].usVal = (uint16)((uiTmp & 0x0f0000) >> 16);
	atTmp[18].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[19].usVal = (uint16)(uiTmp & 0x0000ff);
	
	/* DR_BETA_THLD_HIGH */
	uiTmp = tAspectSizeParam.usDrBetaThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[20].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[21].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* DR_OVER_THLD_HIGH */
	uiTmp = tAspectSizeParam.usDrOverThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[22].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[23].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* DR_BETA_OVER_THLD_HIGH */
	uiTmp = tAspectSizeParam.usDrBetaOverThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[24].usVal = (uint16)((uiTmp & 0xff00) >> 8);
	atTmp[25].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* 0xb9, 0xba飛ばし */
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xb9, &atTmp[26].usVal);
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0xba, &atTmp[27].usVal);
	
	/* FDIFF_THLD_HIGH */
	uiTmp = tAspectSizeParam.uiFdiffThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[28].usVal = (uint16)((uiTmp & 0x070000) >> 16);
	atTmp[29].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[30].usVal = (uint16)(uiTmp & 0x0000ff);
	
	/* INTP_ALPA_LIMIT_HIGH */
	uiTmp = tAspectSizeParam.usIntpAlpaLimitHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[31].usVal = (uint16)((uiTmp & 0x0700) >> 8);
	atTmp[32].usVal = (uint16)(uiTmp & 0x00ff);
	
	eResult |= eFrdGuRegWs(33, atTmp);
	
	/**************/
	/* 次sub1から */
	/**************/
	for(i=0; i<20; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x122 +i;
	
	/* SC_FDIFF_THLD_HIGH */
	uiTmp = tAspectSizeParam.uiScFdiffThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[0].usVal = (uint16)((uiTmp & 0x070000) >> 16);
	atTmp[1].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[2].usVal = (uint16)(uiTmp & 0x0000ff);
	
	/* SC_FDIFF_THLD_LOW */
	uiTmp = tAspectSizeParam.uiScFdiffThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[3].usVal = (uint16)((uiTmp & 0x070000) >> 16);
	atTmp[4].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[5].usVal = (uint16)(uiTmp & 0x0000ff);
	
	/* 0x128-0x12fは無視 */
	for(i=6; i<14; i++)	atTmp[i].usVal = 0;
	
	/* DR_BETA_THLD_LOW */
	uiTmp = tAspectSizeParam.usDrBetaThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[14].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[15].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* DR_OVER_THLD_LOW */
	uiTmp = tAspectSizeParam.usDrOverThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[16].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[17].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* DR_BETA_OVER_THLD_LOW */
	uiTmp = tAspectSizeParam.usDrBetaOverThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[18].usVal = (uint16)((uiTmp & 0xff00) >> 8);
	atTmp[19].usVal = (uint16)(uiTmp & 0x00ff);
	
	eResult |= eFrdGuRegWs(20, atTmp);
	
	/* 次sub1の2から */
	for(i=0; i<18; i++)	atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+0x148 +i;
	
	/* FDIFF_THLD_LOW */
	uiTmp = tAspectSizeParam.uiFdiffThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[0].usVal = (uint16)((uiTmp & 0x070000) >> 16);
	atTmp[1].usVal = (uint16)((uiTmp & 0x00ff00) >> 8);
	atTmp[2].usVal = (uint16)(uiTmp & 0x0000ff);
	
	for(i=3; i<8; i++)	atTmp[i].usVal = 0;
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x150, &atTmp[8].usVal);
	
	/* ADAP_Z_THLD_HIGH */
	uiTmp = tAspectSizeParam.usAdapZThldHigh;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[9].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[10].usVal = (uint16)(uiTmp & 0x00ff);
	
	/* ADAP_Z_THLD_LOW */
	uiTmp = tAspectSizeParam.usAdapZThldLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[11].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[12].usVal = (uint16)(uiTmp & 0x00ff);
	
	for(i=13; i<16; i++)	atTmp[i].usVal = 0;
	
	/* INTP_ALPA_LIMIT_LOW */
	uiTmp = tAspectSizeParam.usIntpAlpaLimitLow;
	uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	atTmp[16].usVal = (uint16)((uiTmp & 0x0700) >> 8);
	atTmp[17].usVal = (uint16)(uiTmp & 0x00ff);
	
	eResult |= eFrdGuRegWs(18, atTmp);
	
	/*************/
	/* TYPV_GAIN */
	/*************/
	usTmp = tAspectSizeParam.ucTypvGain;
	if(fRate > 0.0f){
		usTmp = (uint16)((float)(usTmp/(float)fRate));
		if(usTmp > 0xff)	usTmp = 0xff;
	}else{
		/* 0なら */
		usTmp = 0x40;
	}
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0xff, usTmp);
	
	/***************/
	/* 最後にVHIST */
	/***************/
	if(((double)(ptEdgeFrame->usHeight))/((double)(ptEdgeFrame->usWidth)) > 0.60 )	ucAspect = 0;	/* 4:3  */
	else																			ucAspect = 1;	/* 16:9 */
	
	/* sub0 */
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0xf6, usVhlst[ucAspect][0]);
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0xf7, usVhlst[ucAspect][1]);
	
	/* sub1 */
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0x1a0, usVhlst[ucAspect][0]);
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0x1a1, usVhlst[ucAspect][1]);
	
	return eResult;
}


/**
 * @brief	TBC ROMアドレス探索子関数 (FreeRunパラメータも更新)
 * @param	dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuGetTbcRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	uiRomAddr = GU_ROMADDR_TBC +(FRD_INPUT_FREQ_60HZ -eInputFreq)*GU_ROMSIZE_TBC;
	uiCrcAddr = 0x2c0 + (FRD_INPUT_FREQ_60HZ -eInputFreq);
	
	*puiRomAddr = uiRomAddr;
	*puiCrcAddr = uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	PF LUT ROMアドレス探索子関数
 * @param	dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuGetPfLutRomAddr( dFrdInputFreq_e eInputFreq, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 auiRomAddr[2], auiCrcAddr[2];
	uint8 i;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_60HZ:
			for(i=0; i<2; i++){
				auiRomAddr[i] = GU_ROMADDR_PFLUT + i*(2*GU_ROMSIZE_PFLUT56);
				auiCrcAddr[i] = 0x2c8 +2*i;
			}
			break;
		case FRD_INPUT_FREQ_48HZ:
		case FRD_INPUT_FREQ_50HZ:
			for(i=0; i<2; i++){
				auiRomAddr[i] = GU_ROMADDR_PFLUT +GU_ROMSIZE_PFLUT56 + i*(GU_ROMSIZE_PFLUT56+GU_ROMSIZE_PFLUT7);
				auiCrcAddr[i] = 0x2c8 +1 +2*i;
			}
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	for(i=0; i<2; i++){
		puiRomAddr[i] = auiRomAddr[i];
		puiCrcAddr[i] = auiCrcAddr[i];
	}
	
	return eResult;
}


/**
 * @brief	符号付小数点を符号、整数部(1bit)、小数部(12bit)の2の補数に変換する子関数
 * @param	double Val
 * @return	uint16
 */

static uint16 usGuChgDblToUs(double Val)
{
	uint8 i;
	flag fMinus = FALSE;
	uint16 usRes = 0;
	
	/* 負数かどうかの確認 */
	if(Val < 0){
		fMinus = TRUE;
		/* 絶対値取得 */
//		Val = fabs(Val);
		Val = -Val;
	}
	
	/* 整数1bit (13bit目) */
	if(1.0 <= Val){
		usRes = 0x1000;
		Val -= 1.0;
	}
	
	/* 少数bit変換 */
	for(i=0; i<12; i++){
		Val *= 2;
		if(Val >= 1.0){
			usRes |= (0x01 << (11-i));
			Val -= 1.0;
		}
	}
	
	/* 負数の場合の処理 */
	if(fMinus){
		/* bit反転 */
		usRes = ~usRes;
		usRes += 0x01;
		//usRes |= 0x2000;
	}
	
	/* 15,16bitを"0"にする */
	usRes = usRes & 0x3FFF;
	
	return usRes;
}


/**
 * @brief	デジャダ強調 ROMアドレス探索子関数
 * @param	dFrdDjAdj_e eDjAdj, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuGetDjAdjRomAddr( dFrdGuDjAdj_e eDjAdj, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	uiRomAddr = GU_ROMADDR_DJADJ +eDjAdj*GU_ROMSIZE_DJADJ;
	uiCrcAddr = 0x2d0 + eDjAdj;
	
	*puiRomAddr = uiRomAddr;
	*puiCrcAddr = uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	ポストフィルタ半画面設定子関数
 * @param	dFrdModeHalf_e eModeHalf
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuSetPFHalf( dFrdModeHalf_e eModeHalf )
{
	dResult_e eResult = S_SUCCESS;
	dFrdFrame_t tFrame1;
	dFrdFrame_t tFrame2;
	flag fMask = FALSE;
	dFrdRegVar_t atTmp[9];
	uint8 i;
	
	/* eGuEntryChk()なし */
	
	switch(eModeHalf){
		default:
		case FRD_MODE_HALF_NORMAL:
			fMask = FALSE;
			tFrame1.usXPos = 0;
			tFrame1.usYPos = 0;
			tFrame1.usWidth = 0;
			tFrame1.usHeight = 0;
			break;
		case FRD_MODE_HALF_BOTTOM_ON:
			fMask = TRUE;
			tFrame1.usXPos = 0;
			tFrame1.usYPos = 0;
			tFrame1.usWidth = 1920;
			tFrame1.usHeight = 540;
			break;
		case FRD_MODE_HALF_UP_ON:
			fMask = TRUE;
			tFrame1.usXPos = 0;
			tFrame1.usYPos = 540;
			tFrame1.usWidth = 1920;
			tFrame1.usHeight = 540;
			break;
		case FRD_MODE_HALF_RIGHT_ON:
			fMask = TRUE;
			tFrame1.usXPos = 0;
			tFrame1.usYPos = 0;
			tFrame1.usWidth = 960;
			tFrame1.usHeight = 1080;
			break;
		case FRD_MODE_HALF_LEFT_ON:
			fMask = TRUE;
			tFrame1.usXPos = 960;
			tFrame1.usYPos = 0;
			tFrame1.usWidth = 960;
			tFrame1.usHeight = 1080;
			break;
	}
	
	/* フレーム設定/4 */
	tFrame2.usXPos =	(tFrame1.usXPos >> 2) & 0x1FF;
	tFrame2.usYPos =	(tFrame1.usYPos >> 2) & 0x1FF;
	tFrame2.usWidth =	((tFrame1.usWidth   + (tFrame1.usXPos % 4) + 3) >> 2) & 0x1FF;
	tFrame2.usHeight =	((tFrame1.usHeight  + (tFrame1.usYPos % 4) + 3) >> 2) & 0x1FF;
	
	for(i=0; i<9; i++)	atTmp[i].usAddr	= ADV_LCDC_ADDR_FRC +0x1ba +i;
	atTmp[0].usVal = (uint8)fMask;
	atTmp[1].usVal = (uint8)((tFrame2.usXPos & 0x100) >> 8);
	atTmp[2].usVal = (uint8)(tFrame2.usXPos & 0xff);
	atTmp[3].usVal = (uint8)((tFrame2.usYPos & 0x100) >> 8);
	atTmp[4].usVal = (uint8)(tFrame2.usYPos & 0xff);
	atTmp[5].usVal = (uint8)((tFrame2.usWidth & 0x100) >> 8);
	atTmp[6].usVal = (uint8)(tFrame2.usWidth & 0xff);
	atTmp[7].usVal = (uint8)((tFrame2.usHeight & 0x100) >> 8);
	atTmp[8].usVal = (uint8)(tFrame2.usHeight & 0xff);
	
	eResult |= eFrdGuRegWs(9, atTmp);
	
	/* eGuRegUpd()なし */
	
	return eResult;
}

/* DS6より 0x8b, 0xaf の値は同一となりました */
const static uint16 ausAdvParam[3][6] = 	{{ 0x8b,  0xaf,  0xb3,  0xb4, 0x130, 0x131},		/* Addr */
											 { 0x0E,  0x76,  0x0B,  0x24,  0x00,  0x05},		/* Adv Low */
											 { 0x0E,  0x76,  0x15,  0x24,  0x15,  0x00}};		/* Adv High */
/**
 * @brief	QS Advanceパラメータ設定子関数
 * @param	flag fLow
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuChgAdvParam( flag fLow )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i, ucNo;
	dFrdRegVar_t atTmp[6];
	uint32 uiTmp;
	printf("eGuChgAdvParam1\r\n");
	
//	eResult |= eGuEntryChk();
	printf("eGuChgAdvParam2\r\n");
	/* レジスタ設定 */
	for(i=0; i<6; i++) atTmp[i].usAddr = ADV_LCDC_ADDR_FRC+ ausAdvParam[0][i];
	
	if(fLow)	ucNo = 1;
	else		ucNo = 2;
	printf("eGuChgAdvParam3\r\n");
	for(i=0; i<2; i++) atTmp[i].usVal = ausAdvParam[ucNo][i];	/* atTmp[0]-[1](0x8b, 0xaf) のみ設定 */
	printf("eGuChgAdvParam4\r\n");
	/* atTmp[2]-[5](0xb3-b4, 0x130-131) は画面サイズ状態によって変わるので、以下処理を行う */
	
	/* 内部変数変更 */
	tAspectSizeParam.usDrBetaThldHigh = (((ausAdvParam[ucNo][2] << 8) & 0x7f00) | (ausAdvParam[ucNo][3] & 0x00ff));
	tAspectSizeParam.usDrBetaThldLow  = (((ausAdvParam[ucNo][4] << 8) & 0x7f00) | (ausAdvParam[ucNo][5] & 0x00ff));
	printf("eGuChgAdvParam5\r\n");
	/* DR_BETA_THLD_HIGH */
	uiTmp = tAspectSizeParam.usDrBetaThldHigh;
	printf("eGuChgAdvParam5+\r\n");
	printf("eGuChgAdvParam5, uiTmp =%d\r\n",uiTmp);
	printf("eGuChgAdvParam5, fRate =%d\r\n",fRate);
	//printf("eGuChgAdvParam5, uiTmp =%f\r\n",uiTmp);
	//printf("eGuChgAdvParam5, fRate =%f\r\n",fRate);
	//uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	uiTmp = (uint32)(fRate*uiTmp);
	printf("eGuChgAdvParam5, uiTmp =%d\r\n",uiTmp);
	printf("eGuChgAdvParam5++\r\n");
	atTmp[2].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	printf("eGuChgAdvParam5+++\r\n");
	atTmp[3].usVal = (uint16)(uiTmp & 0x00ff);
	printf("eGuChgAdvParam5++++\r\n");
	printf("eGuChgAdvParam6\r\n");
	/* DR_BETA_THLD_LOW */
	uiTmp = tAspectSizeParam.usDrBetaThldLow;
	//uiTmp = (uint32)(fRate * (float)uiTmp +0.5);
	uiTmp = (uint32)(fRate*uiTmp);
	atTmp[4].usVal = (uint16)((uiTmp & 0x7f00) >> 8);
	atTmp[5].usVal = (uint16)(uiTmp & 0x00ff);
	printf("eGuChgAdvParam7\r\n");
	eResult |= eFrdGuRegWs(6, atTmp);
	printf("eGuChgAdvParam8\r\n");
//	eResult |= eGuRegUpd();
	
	return eResult;
}


/**
 * @brief	Main側Qsモード設定子関数
 * @param	dFrdMode_e eMode
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuSetQsMode( dFrdMode_e eMode )
{
	dResult_e eResult = S_SUCCESS;
#if 0/* 解除の場合に戻す状態が FRD_MODE_ADL or FRD_MODE_ADH で異なる為、caseの方へ移動。
        fHWR == TRUE の場合は、必ず eMode == FRD_MODE_ADL or FRD_MODE_ADH
        また、FRD_MODE_OFF or FRD_MODE_STD の場合は、0x8837 の値はもともと Don't Care */	
	/* HW制約解除 */
	if(fHWR){
		eResult |= eFrdGuRegW(0x8837, 0x20);
		fHWR = FALSE;
	}
#endif	
	switch(eMode){
		case FRD_MODE_OFF:
		case FRD_MODE_STD:
			/* QS */
			if(eMode == FRD_MODE_OFF)	eResult |= eFrdLcdGuSetQsEn(FALSE);
			else						eResult |= eFrdLcdGuSetQsEn(TRUE);	/* STD */
			/* FRC */
			eResult |= eFrdGuSetMode(FALSE);
			/* 鮮鋭化 */
			eResult |= eFrdGuSetSv(FRDGU_SVMODE_OFF);
			break;
		case FRD_MODE_ADL:
			/* QS */
			eResult |= eFrdLcdGuSetQsEn(TRUE);
			/* FRC */
			eResult |= eFrdGuSetMode(TRUE);
			eResult |= eGuChgAdvParam(TRUE);/* RXパラメータ */
			
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x9E, 0x22); /* SCENE */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x837, 0x19);/* VIDEO_MV_MAG *//* 090925 H.Nishimura:"0x20"を強と同じ"0x19"に変更 */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x850, 0x01);/* DR_SEAMLESS_ALGO */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x880, 0x03);/* VLIM_ON *//* 090925 H.Nishimura:"0x01"を強と同じ"0x03"に変更 */
			
			/* 090925 H.Nishimura: 下記の２つのレジスタについてはアドバンス強と標準で値を変える仕様に変更 */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC +0x4D, 0x03);/*  */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC +0x10E, 0x00);
			
			fHWR = FALSE;/* HW制約解除 */
			
			/* 鮮鋭化 */
			eResult |= eFrdGuSetSv(FRDGU_SVMODE_L);
			break;
		case FRD_MODE_ADH:
			printf("eGuSetQsMode1\r\n");
			/* QS */
			eResult |= eFrdLcdGuSetQsEn(TRUE);
			printf("eGuSetQsMode2\r\n");
			/* FRC */
			eResult |= eFrdGuSetMode(TRUE);
			printf("eGuSetQsMode3\r\n");
			eResult |= eGuChgAdvParam(FALSE);/* GXパラメータ */
			printf("eGuSetQsMode4\r\n");
			
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x9E, 0x26); /* SCENE */
			printf("eGuSetQsMode5\r\n");
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x837, 0x19);/* VIDEO_MV_MAG */
			printf("eGuSetQsMode6\r\n");
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x850, 0x03);/* DR_SEAMLESS_ALGO */
			printf("eGuSetQsMode7\r\n");
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC+0x880, 0x03);/* VLIM_ON */
			printf("eGuSetQsMode8\r\n");
			
			/* 090925 H.Nishimura: 下記の２つのレジスタについてはアドバンス強と標準で値を変える仕様に変更 */
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC +0x4D, 0x00);
			printf("eGuSetQsMode9\r\n");
			eResult |= eFrdGuRegW(ADV_LCDC_ADDR_FRC +0x10E, 0x01);
			printf("eGuSetQsMode10\r\n");
			
			fHWR = FALSE;/* HW制約解除 */
			
			/* 鮮鋭化 */
			eResult |= eFrdGuSetSv(FRDGU_SVMODE_M);
			printf("eGuSetQsMode11\r\n");
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	return eResult;
}


/**
 * @brief	Main側Qsモード設定子関数
 * @param	dFrdMode_e eMode
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuSetFilmMode( dFrdMode_e eMode )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eMode){
		case FRD_MODE_OFF:
			printf("eGuSetFilmMode:FRD_MODE_OFF\r\n");
			eResult |= eFrdGuSetDjMode(FRDGU_DJ_ADJ_OFF);
			break;
		case FRD_MODE_STD:
		printf("eGuSetFilmMode:FRD_MODE_STD\r\n");
			eResult |= eFrdGuSetDjMode(FRDGU_DJ_ADJ_55);
			break;
		case FRD_MODE_ADL:
		printf("eGuSetFilmMode:FRD_MODE_ADL\r\n");
			eResult |= eFrdGuSetDjMode(FRDGU_DJ_ADJ_M);
			break;
		case FRD_MODE_ADH:
		printf("eGuSetFilmMode:FRD_MODE_ADH\r\n");
			eResult |= eFrdGuSetDjMode(FRDGU_DJ_ADJ_H);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	return eResult;
}


/**
 * @brief	鮮鋭化設定 ROMアドレス探索子関数
 * @param	dFrdGuSvMode_e eSvMode eDjAdj, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static dResult_e eGuGetSvRomAddr( dFrdGuSvMode_e eSvMode, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiRomAddr, uiCrcAddr;
	
	uiRomAddr = GU_ROMADDR_SV +eSvMode*GU_ROMSIZE_SV;
	uiCrcAddr = 0x2d5 + eSvMode;
	
	*puiRomAddr = uiRomAddr;
	*puiCrcAddr = uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	平方根演算子関数
 * @param	double x
 * @return	S_SUCCESS 成功
 * @return	S_FAILURE 失敗
 */
static double dGuSqrt( double x )
{
	double s,last;
	
	if(x<=0.0) return 0.0;
	
	if(x > 1)	s = x;
	else		s = 1;
	
	do{
		last = s;
		s = (x / s + s) * 0.5;
	} while (s < last);
	
	return last;
}

static dResult_e eGuSetTypvGain( void )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usTmp;
	
	eResult |= eFrdGuRegR(ADV_LCDC_ADDR_FRC+0x8B5, &usTmp);
	usTmp >>= 4;
	usTmp &= 7;
	if( ( usTmp == 0x02 ) || ( usTmp == 0x03 ) ){
	/* Film */
		tAspectSizeParam.ucTypvGain = 0x20;
	}
	else{
	/* Video */
		tAspectSizeParam.ucTypvGain = 0x40;
	}
	
	/*************/
	/* TYPV_GAIN */
	/*************/
	usTmp = tAspectSizeParam.ucTypvGain;
	if(fRate > 0.0f){
		usTmp = (uint16)((float)(usTmp/(float)fRate));
		if(usTmp > 0xff)	usTmp = 0xff;
	}else{
		/* 0なら */
		usTmp = 0x40;
	}
	eResult |= eFrdGuRegW( ADV_LCDC_ADDR_FRC+0xff, usTmp);
	
	return eResult;
}

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
#ifdef TURNKEY1 //Guava用のDemoが存在しなかった(Plaiceと同じものがあると聞いていたが)ので
				//Plaiceと同等のものを作成

static flag fTmpQsEn;
static flag Demo_flag=FALSE;	//20130124
/*!
********************************************************************************
** @brief	デモモード設定API
** @param	eDemoMode		: FRCデモモード設定	(型定義: dFrdPGuDemoMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdGuSetDemoMode( dFrdGuDemoMode_e eDemoMode )
{
	dResult_e eResult = S_SUCCESS;
	flag fMode = FALSE;
	dFrdModeHalf_e eModeHalf = FRD_MODE_HALF_NORMAL;
	flag fLine = FALSE;
	dFrdTestPtn_e eTestPtn = FRD_TESTPTN_OFF;
	uint16 usTmp;
	
	dFrdFrame_t tLine = {958, 260, 4, 820};
	
	
	/* とりあえずModeChkと同様 FRC ON設定 */

	eFrdGuGetMode(&fTmpMode);
			
	/* ついでにQS状態確保 */
	eFrdGuRegR(0xA08, &usTmp);
	fTmpQsEn = (flag)((usTmp & 0x10) >> 4);


	switch(eDemoMode){
		case FRDGU_DEMO_OFF:		/*!< デモモードOFF */
#ifdef TURNKEY1
			if( Demo_flag == TRUE){	//20130124
				Demo_flag = FALSE;	//20130124
				if( fCurrentMode == TRUE )	fMode = TRUE;	//20130124
				else						fMode = FALSE;	//20130124
			}						//20130124
			else{					//20130124
				fMode = fTmpMode;
			}						//20130124
#endif //TURNKEY1

			//fMode = fTmpMode;
			eModeHalf = FRD_MODE_HALF_NORMAL;
			eTestPtn = FRD_TESTPTN_OFF;
//			fMask = FALSE;
			fLine = FALSE;
			
			/* QS Halfを戻す */
			eFrdLcdGuSetQsHalf(FALSE);
			eFrdLcdGuSetQsEn(fTmpQsEn);
			break;
		case FRDGU_DEMO_NORMAL:	/*!< 通常映像デモ(左右分割、スクロールなし) */
			Demo_flag = TRUE;		//20130124
			fMode = TRUE;
			eModeHalf = FRD_MODE_HALF_LEFT_ON;
			eTestPtn = FRD_TESTPTN_OFF;
//			fMask = TRUE;
			fLine = FALSE;
			
#ifdef TURNKEY1
			fCurrentMode = fTmpMode;
#endif //TURNKEY1
			/* QS Half */
			eFrdLcdGuSetQsEn(TRUE);
			eFrdLcdGuSetQsHalf(TRUE);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
	eResult  = eFrdGuSetMode(fMode);
	eResult |= eFrdGuSetModeHalf(eModeHalf);
	eResult |= eFrdGuSetTestPtn(eTestPtn, NULL);

	eResult |= eFrdGuDrawLine(fLine, FRD_LINE_COLOR_BLACK, &tLine);
	
	return eResult;
}
#endif //TURNKEY1

/* end of file */
