#ifndef FRDAPI_H
#define FRDAPI_H


#ifdef __cplusplus
extern "C"
{
#endif //cplusplus

/**
 * @file frdapi.h
 *
 * @brief FRC制御
 *
 * Copyright (c) 2008 SHARP CORPORATION
 *
 * @author 
 */

/* NOTE : このファイルは、個々のFRC用ヘッダファイルへの
          Wrapperとしています。
          実際の記述を追加する場合は、個別のヘッダファイルに追記ください。
 */

/* **
 * ** include
 * **/
 
//?#include <stdio.h>
//?#define NULL 0
#if 1	//TURNKEY1
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned long uint32;
typedef signed long int32;
typedef unsigned char flag;

typedef enum {
	S_SUCCESS,
	S_FAILURE,
   S_SPEC_ERROR,
} dResult_e;

typedef enum{
	FRD_DEMO_OFF,		/*!< DEMO OFF */
	FRD_DEMO_NORMAL,	/*!< DEMO ON */
	FRD_DEMO_SCROLL,	/*!< DEMO ON(scroll the internal image )*/
}dFrdDemoMode_e;
#endif //TURNKEY1


/**
 * @brief	FRC(3rdMethod)テストパターン選択列挙型定義
 */
typedef enum
{
	FRD_TESTPTN_OFF,				/*!< テストパターンOFF(通常表示) */
	FRD_TESTPTN_HRAMP,				/*!< 水平ランプ */
	FRD_TESTPTN_VRAMP,				/*!< 垂直ランプ */
	FRD_TESTPTN_CROSSHATCH,			/*!< クロスハッチ */
	FRD_TESTPTN_ALLOVER,			/*!< ベタ */
	FRD_TESTPTN_VSTRIPE_1LINE,		/*!< 縦ストライプ（1ライン）*/
	FRD_TESTPTN_VSTRIPE_2LINE,		/*!< 縦ストライプ（2ライン）*/
	FRD_TESTPTN_HSTRIPE_1LINE,		/*!< 横ストライプ（1ライン）*/
	FRD_TESTPTN_HSTRIPE_2LINE,		/*!< 横ストライプ（2ライン）*/
	FRD_TESTPTN_CHECK_1DOT,			/*!< 1ドット千鳥 */
	FRD_TESTPTN_CHECK_2DOT,			/*!< 2ドット千鳥 */
	FRD_TESTPTN_CHECK_RGB,			/*!< RGB千鳥 */
	FRD_TESTPTN_QS,					/*!< QSパターン */
	FRD_TESTPTN_MPRT,					/*!< MPRTパターン */
	FRD_TESTPTN_SCROLL,				/*!< 入力画像左スクロール（入力段FIFO_R_adrsシフト）*/ 
	FRD_TESTPTN_FLICKER_2H,			/*!< ドット反転フリッカパターン（2H反転） */
	FRD_TESTPTN_FLICKER_1H,			/*!< ドット反転フリッカパターン（1H反転） */
	FRD_TESTPTN_SHARP,				/*!< "SHARP AQUOS"文字スクロール */
	FRD_TESTPTN_X,					/*!< バッテンマーク */
	FRD_TESTPTN_HVRAMP_ALTERNATE,		/*!< 水平・垂直ランプ交互 水平->垂直 (出力側のみ) */
	FRD_TESTPTN_VHRAMP_ALTERNATE,		/*!< 水平・垂直ランプ交互 垂直->水平 (出力側のみ) */
	FRD_TESTPTN_ALLOVER_ALTERNATE,	/*!< ベタ交互 (出力側のみ) */
	/* 以降 Fraser(Zucchini)では表示されない */
	FRD_TESTPTN_SHARP2,				/*!< "SHARP AQUOS"文字スクロール2 (背景画上) */
	FRD_TESTPTN_AREA3,				/*!< 水平3分割スクロール */
	FRD_TESTPTN_QS_BAR,				/*!< QSバー (QS測定用パターン) */
	FRD_TESTPTN_PF,					/*!< PF効果確認用パターン */
	FRD_TESTPTN_3RD_METHOD,			/*!< 3rdMethod強調lut確認パターン */
} dFrdTestPtn_e;
#define FRD_TESTPTN_NUMMAX (FRD_TESTPTN_3RD_METHOD+1)

/**
 * @brief 入力周波数列挙型定義
 */
typedef enum{
	FRD_INPUT_FREQ_48HZ,	/*!< 48Hz */
	FRD_INPUT_FREQ_50HZ,	/*!< 50Hz */
	FRD_INPUT_FREQ_60HZ,	/*!< 60Hz */
} dFrdInputFreq_e;
#define FRD_INPUT_FREQ_NUMMAX (FRD_INPUT_FREQ_60HZ+1)


/**
 * @brief	矩形色列挙型定義
 */
typedef enum{
	FRD_LINE_COLOR_GRAY,	/*!< グレイ */
	FRD_LINE_COLOR_BLUE,	/*!< ブルー */
	FRD_LINE_COLOR_WHITE,	/*!< ホワイト */
	FRD_LINE_COLOR_BLACK,	/*!< ブラック */
	FRD_LINE_COLOR_US_WHITE,	/*!< 北米用ホワイト */
}dFrdLineColor_e;
#define FRD_LINE_COLOR_NUMMAX (FRD_LINE_COLOR_BLACK+1)


/**
 * @brief	倍速半画面設定列挙型定義
 */
typedef enum{
	FRD_MODE_HALF_NORMAL,		/*!< 半画面ON/OFFなし */
	FRD_MODE_HALF_BOTTOM_ON,	/*!< 下画面ON+上画面OFF */
	FRD_MODE_HALF_UP_ON,		/*!< 上画面ON+下画面OFF */
	FRD_MODE_HALF_RIGHT_ON,		/*!< 右画面ON+左画面OFF */
	FRD_MODE_HALF_LEFT_ON,		/*!< 左画面ON+右画面OFF */
}dFrdModeHalf_e;
#define FRD_MODE_HALF_NUMMAX (FRD_MODE_HALF_LEFT_ON+1)


/**
 * @brief	DDR2工程検査結果列挙型定義
 */
typedef enum{
	FRD_DDR2_RES1,		/*!< DDR2 CHECK OK (正常終了) */
	FRD_DDR2_RES2,		/*!< CONNECTION NG (アドレス接続不良[A1], データバス接続不良[A2]) */
	FRD_DDR2_RES3,		/*!< DDR2 NG (DDR2デバイス領域不良[B]) */
	FRD_DDR2_RES4,		/*!< OTHERS NG (デバイス特性不良[C], 判別不能[X]) */
}dFrdDdr2Res_e;
#define FRD_DDR2_RES_NUMMAX (FRD_DDR2_RES4+1)


/* 090223 ohashi */
/**
 * @brief	QS&Filmモード設定列挙型定義
 */
typedef enum{
	FRD_MODE_OFF,		/*!< QS&Filmモード OFF */
	FRD_MODE_STD,		/*!< QS&Filmモード Standard */
	FRD_MODE_ADL,		/*!< QS&Filmモード Advance (Low) */
	FRD_MODE_ADH,		/*!< QS&Filmモード Advance (High) */
}dFrdMode_e;
#define FRD_MODE_NUMMAX (FRD_MODE_HIGH+1)


/**
 * @brief	工程 FRC ON/OFF設定列挙型定義
 */
typedef enum{
	FRD_MODE_CHK_OFF,		/*!< 工程 FRC OFF */
	FRD_MODE_CHK_MPRT,		/*!< 工程 FRC ON: MPRT */
	FRD_MODE_CHK_AQUOS,		/*!< 工程 FRC ON: QUOS */
}dFrdModeChk_e;
#define FRD_MODE_CHK_NUMMAX (FRD_MODE_CHK_AQUOS+1)


/**
 * @brief	工程 テストパターン種別指定列挙型定義
 */
typedef enum{
	FRD_PTN_FRC,		/*!< FRCパターン */
	FRD_PTN_AGING,		/*!< AGINGパターン */
	FRD_PTN_EVA,		/*!< EVA(評価)パターン */
}dFrdPtnSel_e;
#define FRD_PTN_NUMMAX (FRD_PTN_EVA+1)


/**********/
/* 構造体 */
/**********/
/**
 * @brief レジスタデータ設定値用構造体定義 (FRC側)
 */
typedef struct {
	uint16	usAddr;		/*!< アドレス[16ibt] */
	uint16	usVal;		/*!< データ  [16ibt] */
} dFrdRegVar_t;


/**
 * @brief	領域指定構造体定義
 */
typedef struct
{
	uint16	usXPos;		/*!< 始点X座標 */
	uint16	usYPos;		/*!< 始点Y座標 */
	uint16	usWidth;	/*!< 幅 */
	uint16	usHeight;	/*!< 高さ */
} dFrdFrame_t;


/**
 * @brief	色温度逆補正設定位置構造体定義
 */
typedef struct
{
	uint16	usCtPoint1;	/*!< 色温度逆補正設定位置1 範囲: 0x00〜0x3FF */
	uint16	usCtPoint2;	/*!< 色温度逆補正設定位置2 範囲: 0x00〜0x3FF */
	uint16	usCtPoint3;	/*!< 色温度逆補正設定位置3 範囲: 0x00〜0x3FF */
	uint16	usCtPoint4;	/*!< 色温度逆補正設定位置4 範囲: 0x00〜0x3FF */
	uint16	usCtPoint5;	/*!< 色温度逆補正設定位置5 範囲: 0x00〜0x3FF */
	uint16	usCtPoint6;	/*!< 色温度逆補正設定位置6 範囲: 0x00〜0x3FF */
} dFrdCtPoint_t;


/**
 * @brief	色温度補正値RGB設定構造体定義
 */
typedef struct
{
	uint16	usCtVal1;	/*!< 位置1の色温度補正値 範囲: 0x00〜0x3FF */
	uint16	usCtVal2;	/*!< 位置2の色温度補正値 範囲: 0x00〜0x3FF */
	uint16	usCtVal3;	/*!< 位置3の色温度補正値 範囲: 0x00〜0x3FF */
	uint16	usCtVal4;	/*!< 位置4の色温度補正値 範囲: 0x00〜0x3FF */
	uint16	usCtVal5;	/*!< 位置5の色温度補正値 範囲: 0x00〜0x3FF */
	uint16	usCtVal6;	/*!< 位置6の色温度補正値 範囲: 0x00〜0x3FF */
} dFrdCtValRgb_t;


/**
 * @brief	色温度補正値設定構造体定義
 */
typedef struct
{
	dFrdCtValRgb_t	*ptCtRedVal;	/*!< Red用色温度補正値へのポインタ */
	dFrdCtValRgb_t	*ptCtGrnVal;	/*!< Grn用色温度補正値へのポインタ */
	dFrdCtValRgb_t	*ptCtBluVal;	/*!< Blu用色温度補正値へのポインタ */
} dFrdCtVal_t;


/**
 * @brief 画素値設定構造体定義 (8bit)
 */
typedef struct
{
	uint8	ucR;	/*!< Red */
	uint8	ucG;	/*!< Green */
	uint8	ucB;	/*!< Blue */
} dFrdPixelDat_t;


/**
 * @brief 現状設定値構造体定義
 */
typedef struct
{
	dFrdInputFreq_e	eFreq;		/*!< 現状の周波数 */
	uint8			ucLvl;		/*!< 現状の温度Lvl */
	flag			fFrcEn;		/*!< 現状のFRC設定 */
	flag			fQsEn;		/*!< 現状のQS設定 */
} dFrdCurrentVal_t;


/*********************/
/* 水平3スクロール用 */
/*********************/
/**
 * @brief 水平3分割スクロール速度選択列挙型定義
 */
typedef enum{
	FRD_AREA3_RIGHT,		/*!< 右方向 */
	FRD_AREA3_LEFT,			/*!< 左方向 */
	FRD_AREA3_STOP,			/*!< 停止 */
	FRD_AREA3_PROHIBIT,		/*!< 禁止 */
} dFrdArea3Mov_e;
#define FRD_AREA3_MOV_NUMMAX (FRD_AREA3_PROHIBITION+1)


/**
 * @brief 水平3分割移動方向設定構造体定義
 */
typedef struct {
	dFrdArea3Mov_e	eArea1Mov;	/*!< 領域1の移動方向 */
	dFrdArea3Mov_e	eArea2Mov;	/*!< 領域2の移動方向 */
	dFrdArea3Mov_e	eArea3Mov;	/*!< 領域3の移動方向 */
} dFrdArea3Mov_t;


/**
 * @brief 水平3分割スクロール速度設定構造体定義
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< 領域1スクロール速度 (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< 領域2スクロール速度 (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< 領域3スクロール速度 (0x00-0x3F) */
} dFrdArea3Speed_t;


/**
 * @brief 水平3分割設定構造体定義
 */
typedef struct {
	uint16	usArea2Y;		/*!< 水平3分割・領域2開始ライン番号 (0x00-0x437) */
	uint16	usArea3Y;		/*!< 水平3分割・領域3開始ライン番号 (0x00-0x437) */
	dFrdArea3Speed_t	tArea3Speed;	/*!< 水平3分割スクロール速度設定 */
	dFrdArea3Mov_t		tArea3Mov;	/*!< 水平3分割移動方向設定 */
} dFrdArea3Scrl_t;


/* **
 * ** variable
 * **/

/* **
 * ** prototype
 * **/
extern dResult_e eFrdInit( flag fLrDrive, dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdStandby( flag fPipelineEnable );
extern dResult_e eFrdSetMode( flag fFrcEnable );
extern dResult_e eFrdGetMode( flag *pfFrcStatus );
extern dResult_e eFrdSetEdge( dFrdFrame_t *ptEdgeFrame );
extern dResult_e eFrdSetMask( uint8 ucMaskNo, flag fMaskEnable, dFrdFrame_t *ptMaskFrame );
extern dResult_e eFrdSetMute( flag fMuteEnable );
extern dResult_e eFrdSetTestPtn( dFrdTestPtn_e eTestPtn, void *pvAdjTestPtn );
extern dResult_e eFrdSetOutFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdSetFreeRun( flag fFreeRunEnable );
extern dResult_e eFrdGetStatus( void *pvFrcStatusDat );
extern dResult_e eFrdRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdRegW( uint16 usAddr, uint16 usVal);
extern dResult_e eFrdRegR( uint16 usAddr, uint16 *pusVal);
extern dResult_e eFrdSetGain( uint8 ucTemp );
extern dResult_e eFrdDrawLine( flag fLineEnable, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea );
extern dResult_e eFrdSetModeHalf( dFrdModeHalf_e eModeHalf );
extern dResult_e eFrdSetPF( flag fPFEnable );
extern dResult_e eFrdGetPF( flag *pfPFStatus );
extern dResult_e eFrdSetCtaParam( flag fCtaEnable, dFrdCtPoint_t *ptCtPoint, dFrdCtVal_t *ptCtVal );
extern dResult_e eFrdSetSkinCtl( int16 sHue, int16 sSat, int16 sVal );
extern dFrdDdr2Res_e eFrdChkDdr2( uint16 *pusErrInfo );
extern dResult_e eFrdSetFilmMode( dFrdMode_e eMode );
extern dResult_e eFrdSetQsMode( dFrdMode_e eMode );
extern dResult_e eFrdSetStill( flag fStill );
extern dResult_e eFrdSetTemp( uint8 ucTemp );
extern dResult_e eFrdGetInputRgb( dFrdPixelDat_t ptInputRgb[1920][1080] );
extern dResult_e eFrdSetModeChk( dFrdModeChk_e eModeChk );
extern dResult_e eFrdGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal );
extern dResult_e eFrdSetArea3Scrl( flag fArea3En, dFrdArea3Scrl_t *ptArea3Scrl );
extern dResult_e eFrdSetDemoMode( dFrdDemoMode_e eDemoMode );	//20110920
/* 100310 ohashi: 阿部さん要望統合版 */
extern dResult_e eFrdSetInit( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdSetFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdSetPtn( dFrdPtnSel_e ePtnSel, uint8 ucPtn );
extern dResult_e eFrdSetTypvGain( void );

extern int ifrdSetDriver(	int (*I2C_READ)(uint16, uint8, uint8 *, uint16, uint8 *),
							int (*I2C_WRITE)(uint16, uint8, uint8 *, uint16, uint8 *), 
							int (*MS_WAIT)(int) );

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* FRDAPI_H */
