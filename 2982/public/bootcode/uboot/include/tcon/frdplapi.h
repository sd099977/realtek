#ifndef FRDPLAPI_H
#define FRDPLAPI_H

/**
 * @file frdplapi.h
 *
 * @brief PlaiceFRC制御
 *
 * Copyright (c) 2009 SHARP CORPORATION
 *
 * @author 
 */

/* **
 * ** include
 * **/
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "sousa2.h"
//?#include "advapi.h"
#endif //TURNKEY1

/* **
 * ** define
 * **/
/* RegAddr Offset */
#define PL_REGADDR_FRC	0x8000

/**********/
/* 列挙体 */
/**********/

/**
 * @brief 水平3分割スクロール速度選択列挙型定義
 */
typedef enum{
	FRDPL_AREA3_RIGHT,			/*!< 右方向 */
	FRDPL_AREA3_LEFT,			/*!< 左方向 */
	FRDPL_AREA3_STOP,			/*!< 停止 */
	FRDPL_AREA3_PROHIBIT,		/*!< 禁止 */
} dFrdPlArea3Mov_e;
#define FRDPL_AREA3_MOV_NUMMAX (FRDPL_AREA3_PROHIBITION+1)


/**
 * @brief 鮮鋭化設定選択列挙型定義
 */
typedef enum{
	FRDPL_SVMODE_H,		/*!< 強モード */
	FRDPL_SVMODE_M,		/*!< 強モード */
	FRDPL_SVMODE_L,		/*!< 弱モード */
	FRDPL_SVMODE_DEMO,	/*!< 鮮鋭化 デモ用 */
	FRDPL_SVMODE_OFF,	/*!< オフ */
} dFrdPlSvMode_e;
#define FRDPL_SV_MODE_NUMMAX (FRDPL_SVMODE_HIGH+1)


/**
 * @brief	デモモード設定列挙型定義
 */
typedef enum{
	FRDPL_DEMO_OFF,		/*!< デモモードOFF */
	FRDPL_DEMO_NORMAL,	/*!< 通常映像デモ(左右分割、スクロールなし) */
	FRDPL_DEMO_SCROLL,	/*!< 静止画スクロールデモ(左右分割＋スクロール) */
}dFrdPlDemoMode_e;
#define FRDPL_DEMO_NUMMAX (FRDPL_DEMO_SCROLL+1)


/**********/
/* 構造体 */
/**********/

/**
 * @brief 水平3分割移動方向設定構造体定義
 */
typedef struct {
	dFrdPlArea3Mov_e	eArea1Mov;	/*!< 領域1の移動方向 */
	dFrdPlArea3Mov_e	eArea2Mov;	/*!< 領域2の移動方向 */
	dFrdPlArea3Mov_e	eArea3Mov;	/*!< 領域3の移動方向 */
} dFrdPlArea3Mov_t;


/**
 * @brief 水平3分割スクロール速度設定構造体定義
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< 領域1スクロール速度 (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< 領域2スクロール速度 (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< 領域3スクロール速度 (0x00-0x3F) */
} dFrdPlArea3Speed_t;


/**
 * @brief 水平3分割設定構造体定義
 */
typedef struct {
	uint16	usArea2Y;		/*!< 水平3分割・領域2開始ライン番号 (0x00-0x437) */
	uint16	usArea3Y;		/*!< 水平3分割・領域3開始ライン番号 (0x00-0x437) */
	dFrdPlArea3Speed_t	*ptArea3Speed;	/*!< 水平3分割スクロール速度設定 */
	dFrdPlArea3Mov_t	*ptArea3Mov;	/*!< 水平3分割移動方向設定 */
} dFrdPlArea3TestPtn_t;


/**
 * @brief 動画パターン移動方向/速度設定構造体定義 (分割スクロールを除く)
 */
typedef struct {
	flag	fQsMovLR;		/*!< 内蔵パタン移動方向 (TRUE:左, FALSE:右) */
	uint8	ucQsMovSpeed;	/*!< 内蔵パタン移動速度 (0x00-0x3F)*/
	uint8	ucHScroll;		/*!< 入力画像スクロール速度 (0x00-0x3F)*/
} dFrdPlMovTestPtn_t;


/**
 * @brief テストパターン詳細設定構造体定義
 */
typedef struct {
	dFrdPlArea3TestPtn_t	*ptArea3TestPtn;	/*!< 水平3分割設定 */
	dFrdPlMovTestPtn_t		*ptMovTestPtn;		/*!< 動画パターン移動方向/速度設定 */
} dFrdPlAdjTestPtn_t;


/**
 * @brief	現在設定値構造体定義 (詳細設定に関する現状の内部変数を示す)
 */
typedef struct
{
	dFrdPlAdjTestPtn_t	tCurrentAdjTestPtn;	/*!< テストパターン詳細設定状態を示す */
} dFrdPlInternalDat_t;


/**
 * @brief 入力画素値キャプチャ設定構造体定義 (10bit)
 */
typedef struct
{
	uint16	usCvR;	/*!< Red */
	uint16	usCvG;	/*!< Green */
	uint16	usCvB;	/*!< Blue */
} dFrdPlPixelDat_t;


/* **
 * ** variable
 * **/

/* **
 * ** prototype
 * **/
extern dResult_e eFrdPlRegWs( int32 iRegNum, dFrdRegVar_t *ptDatas );
extern dResult_e eFrdPlRegRs( int32 iRegNum, dFrdRegVar_t *ptDatas );
extern dResult_e eFrdPlRegW( uint16 usAddr, uint16 usVal );
extern dResult_e eFrdPlRegR( uint16 usAddr, uint16 *pusVal );
extern dResult_e eFrdPlInit( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdPlStandby( flag fPipelineEn );
extern dResult_e eFrdPlSetMode( flag fFrcEn );
extern dResult_e eFrdPlGetMode( flag *pfFrcStatus );
extern dResult_e eFrdPlSetEdge( dFrdFrame_t *ptEdgeFrame );
extern dResult_e eFrdPlSetMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame);
extern dResult_e eFrdPlSetMute( flag fMuteEn );
extern dResult_e eFrdPlSetTestPtn( dFrdTestPtn_e eTestPtn, dFrdPlAdjTestPtn_t *pvAdjTestPtn);
extern dResult_e eFrdPlSetOutFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdPlSetFreeRun( flag fFreeRunEn );
extern dResult_e eFrdPlGetStatus( dFrdPlInternalDat_t *pvFrcStatusDat );
extern dResult_e eFrdPlDrawLine( flag fLineEn, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea );
extern dResult_e eFrdPlSetModeHalf( dFrdModeHalf_e eModeHalf );
extern dResult_e eFrdPlSetGain( uint8 ucLevel );
extern dResult_e eFrdPlSetTemp( uint8 ucTemp );
extern dResult_e eFrdPlAllManualLoad( void );
extern dResult_e eFrdPlSetStill( flag fStill );
extern dResult_e eFrdPlGetInputRgb( uint16 usCvH, uint16 usCvV, dFrdPlPixelDat_t *ptInputRgb );
extern dResult_e eFrdPlSetModeChk( dFrdModeChk_e eModeChk );
extern dResult_e eFrdPlSetDemoMode( dFrdPlDemoMode_e eDemoMode );
extern dResult_e eFrdPlGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal );
#endif /* FRDPLAPI_H */
