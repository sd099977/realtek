#ifndef FRDGUAPI_H
#define FRDGUAPI_H

/**
 * @file frdguapi.h
 *
 * @brief GuavaFRC制御
 *
 * Copyright (c) 2010 SHARP CORPORATION
 *
 * @author 
 */

/* **
 * ** include
 * **/


#ifdef TURNKEY1
#include "sysapi.h"
#else //TURNKEY1
//?#include "sousa2.h"
//?#include "advapi.h"
#if 0
#include "frdapi.h"//なぜ.c側でまとめてincludeするのに、guavaだけ.c、.hの両方でincludeしているのでErrになっている
#endif //0			//よって、.h側のincludeは削除する
#endif //TURNKEY1


/* **
 * ** define
 * **/
/* RegAddr Offset */
#define GU_REGADDR_FRC	0x8000

/**********/
/* 列挙体 */
/**********/

/**
 * @brief 水平3分割スクロール速度選択列挙型定義
 */
typedef enum{
	FRDGU_AREA3_RIGHT,			/*!< 右方向 */
	FRDGU_AREA3_LEFT,			/*!< 左方向 */
	FRDGU_AREA3_STOP,			/*!< 停止 */
	FRDGU_AREA3_PROHIBIT,		/*!< 禁止 */
} dFrdGuArea3Mov_e;
#define FRDGU_AREA3_MOV_NUMMAX (FRDGU_AREA3_PROHIBITION+1)


/**
 * @brief デジャダモード用内蔵パタンモード選択列挙型定義
 */
typedef enum{
	FRDGU_VIDEO_MODE,		/*!< videoモード */
	FRDGU_22_MODE,			/*!< 22モード */
	FRDGU_32_MODE,			/*!< 32モード */
	FRDGU_PROHIBIT_MODE,	/*!< 禁止 */
} dFrdGuFilmMode_e;
#define FRDGU_FILM_MODE_NUMMAX (FRDGU_PROHIBIT_MODE+1)


/**
 * @brief 鮮鋭化設定選択列挙型定義
 */
typedef enum{
	FRDGU_SVMODE_H,		/*!< 強モード */
	FRDGU_SVMODE_M,		/*!< 中モード */
	FRDGU_SVMODE_L,		/*!< 弱モード */
	FRDGU_SVMODE_DEMO,	/*!< 鮮鋭化 デモ用 */
	FRDGU_SVMODE_OFF,		/*!< オフ */
} dFrdGuSvMode_e;
#define FRDGU_SV_MODE_NUMMAX (FRDGU_SVMODE_HIGH+1)


/**
 * @brief デジャダ強調設定列挙型定義
 */
typedef enum{
	FRDGU_DJ_ADJ_H,		/*!< デジャダ強 */
	FRDGU_DJ_ADJ_M,		/*!< デジャダ中 */
	FRDGU_DJ_ADJ_L,		/*!< デジャダ弱 */
	FRDGU_DJ_ADJ_55,	/*!< デジャダ5-5 */
	FRDGU_DJ_ADJ_DEMO,	/*!< デジャダ デモ用 */
	FRDGU_DJ_ADJ_OFF,	/*!< デジャダOFF */
}dFrdGuDjAdj_e;
#define FRDGU_DJ_ADJ_NUMMAX (FRDGU_DJ_ADJ_OFF+1)


#if TURNKEY1	//Plaiceと同様のAPIにするために、Plaiceと同様の列挙帯定義
/**
 * @brief	デモモード設定列挙型定義
 */
typedef enum{
	FRDGU_DEMO_OFF,		/*!< デモモードOFF */
	FRDGU_DEMO_NORMAL,	/*!< 通常映像デモ(左右分割、スクロールなし) */
}dFrdGuDemoMode_e;
#define FRDGU_DEMO_NUMMAX (FRDGU_DEMO_NORMAL+1)
#endif //TURNKEY1


/**********/
/* 構造体 */
/**********/

/**
 * @brief 水平3分割移動方向設定構造体定義
 */
typedef struct {
	dFrdGuArea3Mov_e	eArea1Mov;	/*!< 領域1の移動方向 */
	dFrdGuArea3Mov_e	eArea2Mov;	/*!< 領域2の移動方向 */
	dFrdGuArea3Mov_e	eArea3Mov;	/*!< 領域3の移動方向 */
} dFrdGuArea3Mov_t;


/**
 * @brief 水平3分割スクロール速度設定構造体定義
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< 領域1スクロール速度 (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< 領域2スクロール速度 (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< 領域3スクロール速度 (0x00-0x3F) */
} dFrdGuArea3Speed_t;


/**
 * @brief 水平3分割設定構造体定義
 */
typedef struct {
	uint16	usArea2Y;		/*!< 水平3分割・領域2開始ライン番号 (0x00-0x437) */
	uint16	usArea3Y;		/*!< 水平3分割・領域3開始ライン番号 (0x00-0x437) */
	dFrdGuArea3Speed_t	*ptArea3Speed;	/*!< 水平3分割スクロール速度設定 */
	dFrdGuArea3Mov_t	*ptArea3Mov;	/*!< 水平3分割移動方向設定 */
} dFrdGuArea3TestPtn_t;


/**
 * @brief 動画パターン移動方向/速度設定構造体定義 (分割スクロールを除く)
 */
typedef struct {
	flag	fQsMovLR;		/*!< 内蔵パタン移動方向 (TRUE:左, FALSE:右) */
	uint8	ucQsMovSpeed;	/*!< 内蔵パタン移動速度 (0x00-0x3F)*/
	uint8	ucHScroll;		/*!< 入力画像スクロール速度 (0x00-0x3F)*/
} dFrdGuMovTestPtn_t;


/**
 * @brief テストパターンdebug設定構造体定義
 */
typedef struct {
	flag				fEnforce;	/*!< 強制スクロールフラグ (TRUE:強制3分割スクロール, FALSE:通常表示) */
	uint16				usBitMapY;	/*!< AQUOS表示開始ライン番号 */
	dFrdGuFilmMode_e	eFilmMode;	/*!< デジャダモード用内蔵パタンモード */
} dFrdGuDebugTestPtn_t;


/**
 * @brief テストパターン詳細設定構造体定義
 */
typedef struct {
	dFrdGuArea3TestPtn_t	*ptArea3TestPtn;	/*!< 水平3分割設定 */
	dFrdGuMovTestPtn_t		*ptMovTestPtn;		/*!< 動画パターン移動方向/速度設定 */
	dFrdGuDebugTestPtn_t	*ptDebugTestPtn;	/*!< テストパターンdebug設定 */
} dFrdGuAdjTestPtn_t;


/**
 * @brief 入力画素データ設定構造体定義 (読込みのみ)
 */
typedef struct
{
	uint16	usCvV0;	/*!< Red/V/Cr  範囲: 0x00〜0x3F */
	uint16	usCvV1;	/*!< Green/Y/Y 範囲: 0x00〜0x3F */
	uint16	usCvV2;	/*!< Blue/U/Cb 範囲: 0x00〜0x3F */
} dFrdGuPixelDat_t;


/**
 * @brief	現在設定値構造体定義 (詳細設定に関する現状の内部変数を示す)
 */
typedef struct
{
	dFrdGuAdjTestPtn_t	tCurrentAdjTestPtn;	/*!< テストパターン詳細設定状態を示す */
} dFrdGuInternalDat_t;

/* **
 * ** variable
 * **/

/* **
 * ** prototype
 * **/
extern dResult_e eFrdGuRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdGuRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdGuRegW( uint16 usAddr, uint16 usVal);
extern dResult_e eFrdGuRegR( uint16 usAddr, uint16 *pusVal);
extern dResult_e eFrdGuInit( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdGuStandby( flag fPipelineEnable );
extern dResult_e eFrdGuSetMode( flag fFrcEnable );
extern dResult_e eFrdGuGetMode( flag *pfFrcStatus );
extern dResult_e eFrdGuSetEdge( dFrdFrame_t *ptEdgeFrame );
extern dResult_e eFrdGuSetMask( uint8 ucMaskNo, flag fMaskEnable, dFrdFrame_t *ptMaskFrame );
extern dResult_e eFrdGuSetMute( flag fMuteEnable );
extern dResult_e eFrdGuSetTestPtn( dFrdTestPtn_e eTestPtn, dFrdGuAdjTestPtn_t *ptAdjTestPtn );
extern dResult_e eFrdGuGetStatus( dFrdGuInternalDat_t *pvFrcStatusDat );
extern dResult_e eFrdGuSetGain( uint8 ucTemp );
extern dResult_e eFrdGuDrawLine( flag fLineEnable, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea );
extern dResult_e eFrdGuSetModeHalf( dFrdModeHalf_e eModeHalf );
extern dResult_e eFrdGuSetPF( flag fPFEnable );
extern dResult_e eFrdGuGetPF( flag *pfPFStatus );
extern dResult_e eFrdGuSetCtaParam( flag fCtaEnable, dFrdCtPoint_t *ptCtPoint, dFrdCtVal_t *ptCtVal );
extern dResult_e eFrdGuSetSkinCtl( int16 sHue, int16 sSat, int16 sVal );
extern dResult_e eFrdGuDispScore( flag fDispEnable );
extern dResult_e eFrdGuSetOutFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdGuSetFreeRun( flag fFreeRunEnable );
extern dResult_e eFrdGuGetRgb( uint16 usCvV, uint16 usCvH, dFrdGuPixelDat_t *ptPixelDat );
extern dResult_e eFrdGuVerify( uint32 uiRomAddr, uint16 usRegAddr, uint16 usLen );
extern dResult_e eFrdGuSetSv( dFrdGuSvMode_e eSvMode );
extern dResult_e eFrdGuSetDjMode( dFrdGuDjAdj_e eDjAdj );
extern dResult_e eFrdGuSetFilmMode( dFrdMode_e eMode );
extern dResult_e eFrdGuSetQsMode( dFrdMode_e eMode );
extern dResult_e eFrdGuAllManualLoad( void );
extern dResult_e eFrdGuSetModeChk( dFrdModeChk_e eModeChk );
extern dResult_e eFrdGuSetArea3Scrl( flag fArea3En, dFrdArea3Scrl_t *ptArea3Scrl );
extern dResult_e eFrdGuSetTypvGain( void );
extern dResult_e eFrdGuGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal );
#ifdef TURNKEY1
extern dResult_e eFrdGuSetDemoMode( dFrdGuDemoMode_e eDemoMode );
#endif //TURNKEY1
#endif /* FRDGUAPI_H */
