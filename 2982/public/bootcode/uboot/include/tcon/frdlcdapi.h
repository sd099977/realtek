#ifndef FRDLCDAPI_H
#define FRDLCDAPI_H


#ifdef __cplusplus
extern "C"
{
#endif //cplusplus

/**
 * @file frdlcdapi.h
 *
 * @brief LCDC制御
 *
 * Copyright (c) 2008 SHARP CORPORATION
 *
 * @author 
 */

/* NOTE : このファイルは、個々のLCD用ヘッダファイルへの
          Wrapperとしています。
          実際の記述を追加する場合は、個別のヘッダファイルに追記ください。
 */

/* **
 * ** include
 * **/
#include "frdapi.h"			/* dFrdRegVar_t等にて必要 */

#if 0						//未使用
#include "frdlcdzyapi.h"	/* Yellowtail/Zucchini用 */
#include "frdarapi.h"		/* Arugula用 */
#endif //0

#if 0						//なぜ.c側でまとめてincludeするのに、guavaだけ.c、.hの両方でincludeしているのでErrになっている
							//よって、.h側のincludeは削除する
#include "frdguapi.h"		/* Guava用 */
#endif //0

//#include "DriverRegistFunction.h"

/* **
 * ** variable
 * **/


/**
 * @brief 搭載コントローラ列挙型定義
 */
typedef enum {
	FRDLCD_SOUSA,		/*!< SousaII */
	FRDLCD_ZUCCHINI,	/*!< Zucchini */
	FRDLCD_YELLOWTAIL,	/*!< YellowTail */
	FRDLCD_ZUCCHINI_P,	/*!< Zucchini_P */
	FRDLCD_ARUGULA,		/*!< Arugula */
	FRDLCD_PLAICE,		/*!< Plaice */
	FRDLCD_GUAVA,		/*!< Guava */
	FRDLCD_UNKNOWN		/*!<  ・・・ */
} dFrdLcdControler_e;
#define FRDLCD_LSI_NUMMAX (FRDLCD_UNKNOWN+1)

/**
 * @brief 映像反転設定列挙型定義
 */
typedef enum {
	FRDLCD_TRN_OVR_NORMAL,		/*!< ノーマル */
	FRDLCD_TRN_OVR_MIRROR,		/*!< 左右反転 */
	FRDLCD_TRN_OVR_UPSIDE_DOWN,	/*!< 上下反転 */
	FRDLCD_TRN_OVR_ROTATE,		/*!< 上下左右反転 */
} dFrdLcdTrnOvr_e;
#define FRDLCD_TRN_OVR_NUMMAX (FRDLCD_TRN_OVR_ROTATE+1)


/**
 * @brief LCDテストパターン列挙型
 */
typedef enum {
	FRDLCD_TESTPTN_OFF			= 0,	/*!< OFF */
	FRDLCD_TESTPTN_WB1LINE		= 1,	/*!< 白黒横1ライン */
	FRDLCD_TESTPTN_BW1LINE		= 2,	/*!< 黒白横1ライン */
	FRDLCD_TESTPTN_HGLAY1		= 3,	/*!< 横グレースケール1 */
	FRDLCD_TESTPTN_HGLAY2		= 4,	/*!< 横グレースケール2 */
	FRDLCD_TESTPTN_GREEN		= 5,	/*!< 緑(255)ベタ */
	FRDLCD_TESTPTN_BLUE			= 6,	/*!< 青(255)ベタ */
	FRDLCD_TESTPTN_RED			= 7,	/*!< 赤(255)ベタ */
	FRDLCD_TESTPTN_WHITE		= 8,	/*!< 白(255)ベタ */
	FRDLCD_TESTPTN_BLACK		= 9,	/*!< 黒(0)ベタ */
	FRDLCD_TESTPTN_GLAY215		= 10,	/*!< グレー(215)ベタ */
	FRDLCD_TESTPTN_GLAY147		= 11,	/*!< グレー(147)ベタ */
	FRDLCD_TESTPTN_GLAY96		= 12,	/*!< グレー(96)ベタ */
	FRDLCD_TESTPTN_GLAY60		= 13,	/*!< グレー(60)ベタ */
	FRDLCD_TESTPTN_GLAY47		= 14,	/*!< グレー(47)ベタ */
	FRDLCD_TESTPTN_FLICKERBMP	= 15,	/*!< フリッカ＋BITMAP */

	FRDLCD_TESTPTN_SHADOWING	= 16,	/*!< シャドーイングパターン  */
	FRDLCD_TESTPTN_QS1			= 17,	/*!< QSテストパターン1 */
	FRDLCD_TESTPTN_QS2			= 18,	/*!< QSテストパターン2 */
	FRDLCD_TESTPTN_FLICKER1H	= 19,	/*!< フリッカパターン(1H) */
	FRDLCD_TESTPTN_FLICKER2H	= 20,	/*!< フリッカパターン(2H+1) */

	FRDLCD_TESTPTN_GLAY30		= 21,	/*!< グレー(30)ベタ */
	FRDLCD_TESTPTN_GLAY44		= 22,	/*!< グレー(44)ベタ */
	FRDLCD_TESTPTN_GLAY128		= 23,	/*!< グレー(128)ベタ */
	FRDLCD_TESTPTN_GLAY168		= 24,	/*!< グレー(168)ベタ */
	FRDLCD_TESTPTN_GLAY212		= 25,	/*!< グレー(212)ベタ */
	FRDLCD_TESTPTN_RED128		= 26,	/*!< 赤(128)ベタ */
	FRDLCD_TESTPTN_GREEN128		= 27,	/*!< 緑(128)ベタ */
	FRDLCD_TESTPTN_BLUE128		= 28,	/*!< 青(128)ベタ */
	FRDLCD_TESTPTN_LMD			= 29,	/*!< LMD確認パターン */
	FRDLCD_TESTPTN_FORECAST_OS	= 30,	/*!< 予測OS出力(メモリ出力)モード */

	FRDLCD_TESTPTN_MONOCHRO		= 31,	/*!< モノクロ表示 */
	FRDLCD_TESTPTN_GRADATION	= 32,	/*!< 階調テスト表示 */
	FRDLCD_TESTPTN_BETA			= 33,	/*!< ベタ表示 */
	FRDLCD_TESTPTN_STRIPE		= 34,	/*!< 縦ストライプ */
	FRDLCD_TESTPTN_GRAYSCALE_H	= 35,	/*!< 水平方向グレースケール */
	FRDLCD_TESTPTN_GRAYSCALE_V	= 36,	/*!< 垂直方向グレースケール */
	FRDLCD_TESTPTN_COLOR_CHART	= 37,	/*!< カラーチャート */
	FRDLCD_TESTPTN_FLICKER1		= 38,	/*!< フリッカパターン1 */
	FRDLCD_TESTPTN_FLICKER2		= 39,	/*!< フリッカパターン2 */
	FRDLCD_TESTPTN_AD_ADJUST	= 40,	/*!< A/D調整用パターン */
	FRDLCD_TESTPTN_BETA_UD		= 41,	/*!< 上下分割ベタ */
	FRDLCD_TESTPTN_BETA_LR		= 42,	/*!< 左右分割ベタ */
	FRDLCD_TESTPTN_FLICKER		= 43,	/*!< ライン反転用フリッカパターン */
	FRDLCD_TESTPTN_SANDSTORM	= 44,	/*!< 砂嵐パターン */
	FRDLCD_TESTPTN_LINE			= 45,	/*!< 1ライン表示パターン */
	FRDLCD_TESTPTN_VERTICAL_LINE= 46,	/*!< 1列表示パターン */
} dFrdLcdTestPtn_e;
#define FRDLCD_TESTPTN_NUMMAX (FRDLCD_TESTPTN_VERTICAL_LINE+1)


/**
 * @brief Revision情報列挙型
 */
typedef enum {
	FRDLCD_REVISION_YEAR_H   = 0,
	FRDLCD_REVISION_YEAR_L   = 1,
	FRDLCD_REVISION_MONTH    = 2,
	FRDLCD_REVISION_DAY      = 3,
	FRDLCD_REVISION_VER      = 4,
	FRDLCD_REVISION_INCHI    = 5,
	FRDLCD_REVISION_PANEL    = 6,
	FRDLCD_REVISION_SBR      = 7,
	FRDLCD_REVISION_CS       = 8,
	FRDLCD_REVISION_ROM_SIZE = 9,
	FRDLCD_REVISION_ROM      = 10,
	FRDLCD_REVISION_FRC      = 11,
	FRDLCD_REVISION_ZUC_REV  = 12,
	FRDLCD_REVISION_CPWB     = 13,	
	FRDLCD_REVISION_MISC     = 14,
	FRDLCD_REVISION_CRC      = 15
} dFrdLcdRevisionInfo_e;
#define FRDLCD_REVISION_DATA_MAX (FRDLCD_REVISION_CRC + 1)


/**
 * @brief 統合Revision情報列挙型
 */
typedef enum {
	FRDLCD_UNI_REVISION_YEAR_H   = 0,
	FRDLCD_UNI_REVISION_YEAR_L   = 1,
	FRDLCD_UNI_REVISION_MONTH    = 2,
	FRDLCD_UNI_REVISION_DAY      = 3,
	FRDLCD_UNI_REVISION_DEST     = 4,
	FRDLCD_UNI_REVISION_MODEL    = 5,
	FRDLCD_UNI_REVISION_VER_H    = 6,
	FRDLCD_UNI_REVISION_VER_L    = 7,
/*	FRDLCD_UNI_REVISION_RESERVE  = 8,*/
	FRDLCD_UNI_REVISION_ROM_SIZE = 9,
	FRDLCD_UNI_REVISION_ROM      = 10,
	FRDLCD_UNI_REVISION_CRC32    = 11,
	FRDLCD_UNI_REVISION_CRC40    = 12,
	FRDLCD_UNI_REVISION_CRC46    = 13,	
	FRDLCD_UNI_REVISION_CRC52    = 14,
	FRDLCD_UNI_REVISION_CRC      = 15
} dFrdLcdUnifideRevisionInfo_e;


/**
 * @brief パネルサイズ列挙型
 */
typedef enum
{
	FRDLCD_PNL_32,	/*!< 32inch  */
	FRDLCD_PNL_40,	/*!< 40inch  */
	FRDLCD_PNL_46,	/*!< 46inch  */
	FRDLCD_PNL_52,	/*!< 52inch  */
	FRDLCD_PNL_60,	/*!< 60inch  */
	FRDLCD_PNL_70,	/*!< 60inch  */
} dFrdLcdPnlSize_e;
#define FRDLCD_PNL_NUMMAX (FRDLCD_PNL_70+1)


/**
 * @brief 映像反転設定列挙型定義
 */
typedef enum {
	FRDLCD_DECONT_OFF,		/*!< デコントOFF */
	FRDLCD_DECONT_V_ON,		/*!< 垂直デコントのみON */
	FRDLCD_DECONT_H_ON,		/*!< 水平デコントのみON */
	FRDLCD_DECONT_VH_ON,	/*!< 垂直水平デコントON */
} dFrdLcdDecont_e;


/**
 * @brief 色属性指定列挙型定義
 */
typedef enum
{
	FRDLCD_BRI,	/*!< 輝度  */
	FRDLCD_SAT,	/*!< 彩度  */
	FRDLCD_HUE,	/*!< 色相  */
} dFrdLcdBsh_e;
#define FRDLCD_BSH_NUMMAX (FRDLCD_HUE+1)


/**
 * @brief NRモード設定列挙型定義
 */
typedef enum
{
	FRDLCD_NR_OFF,	/*!< NR OFF  */
	FRDLCD_NR_MIN,	/*!< NR 弱  */
	FRDLCD_NR_MID,	/*!< NR 中  */
	FRDLCD_NR_MAX,	/*!< NR 強  */
} dFrdLcdNrMode_e;
#define FRDLCD_NR_MODE_NUMMAX (FRDLCD_NR_MAX+1)


/**
 * @brief RGB値用構造体
 */
typedef struct {
	uint16 usR;	/*!< R階調[0-4095] */
	uint16 usG;	/*!< G階調[0-4095] */
	uint16 usB;	/*!< B階調[0-4095] */
} dFrdLcdRgb_t;


/**
 * @brief テストパターン色設定値用構造体
 */
typedef struct {
	int32 iTPDAR;	/*!< R階調[0-1023] */
	int32 iTPDAG;	/*!< G階調[0-1023] */
	int32 iTPDAB;	/*!< B階調[0-1023] */
} dFrdLcdTpColor_t;


/**
 * @brief エラー情報設定構造体
 */
typedef struct {
	uint8 ucErrCode;	/*!< エラーコード  */
	uint8 ucErrBlock;	/*!< ロードエラーブロック番号 */
	uint16 usAddr;		/*!< 対応レジスタアドレス */
	uint8 ucCrcExp;		/*!< CRC期待値 */
	uint8 ucCrcCal;		/*!< CRC演算値 */
} dFrdLcdError_t;

#define FRDLCD_ERR_LOG_NUM_MAX		64		/* エラー情報ログ配列のサイズ */


/* **
 * ** variable
 * **/
//sakata20110921 static dFrdLcdPnlSize_e eFrdLcdPnlSize = FRDLCD_PNL_32;	//sakata20110921

/* **
 * ** prototype
 * **/
extern dResult_e eFrdLcdRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdLcdRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas );
extern dResult_e eFrdLcdRegW( uint16 usAddr, uint16 usVal );
extern dResult_e eFrdLcdRegR( uint16 usAddr, uint16 *pusVal );
extern dResult_e eFrdLcdSetSize( dFrdLcdPnlSize_e ePnlSize );
extern dResult_e eFrdLcdGetSize( dFrdLcdPnlSize_e *pePnlSize );
extern dFrdLcdControler_e eFrdLcdGetLsiInfo( void );
extern dResult_e eFrdLcdChkEepLoadEnd( void );
extern dResult_e eFrdLcdInit( flag fLrDrive );
extern dResult_e eFrdLcdSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr );
extern dResult_e eFrdLcdSetOutput( flag fOutEnable );
extern dResult_e eFrdLcdSetTestPtn( dFrdLcdTestPtn_e eTestPtn );
extern dResult_e eFrdLcdSetAgingPtn( uint8 ucAgingPtn );
extern dResult_e eFrdLcdSetEvaPtn( uint8 ucEvaPtn );
extern dResult_e eFrdLcdSetQsEnable( flag fQsEnable, flag fYuv );
extern dResult_e eFrdLcdSetQsHalf( flag fLonRoff );
extern dResult_e eFrdLcdSetQsFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdLcdSetQsTemp( uint8 ucTemp );
extern dResult_e eFrdLcdSetSbr( uint8 ucTemp );
extern dResult_e eFrdLcdGetRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdGetUnifiedRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdGetRevStr( int8 *pcRevInfo );
extern dResult_e eFrdLcdEepWs( uint32 uiAddr, uint32 uiLength, uint8* pucDatas );
extern dResult_e eFrdLcdEepRs( uint32 uiAddr, uint32 uiLength, uint8* pucDatas );
extern dResult_e eFrdLcdEepErase( void );
extern dResult_e eFrdLcdSetVerUp( uint8 *pucDats, flag fVerify );
extern dResult_e eFrdLcdOutSource( dFrdLcdPnlSize_e ePnlSize );
extern dResult_e eFrdLcdSetFreeRun( flag fFreeRunEnable );
extern dResult_e eFrdLcdSetDecontEnable( dFrdLcdDecont_e eDecontEnable );
extern dResult_e eFrdLcdGetRgb(uint16 x, uint16 y, dFrdLcdRgb_t *ptRgbColor);
extern dResult_e eFrdLcdSetBetaPtn(dFrdLcdTpColor_t *ptColor);
extern dResult_e eFrdLcdSetLumaAdjU(int32 iLevel);
extern dResult_e eFrdLcdGetLumaAdjU(int32 *piLevel);
extern dResult_e eFrdLcdGetErrInfo( dFrdLcdError_t *ptError );
extern dResult_e eFrdLcdAllManualLoad( void );
extern dResult_e eFrdLcdSetFrAgingPtn( uint8 ucFrAgingPtn );
extern dResult_e eFrdLcdSetFrEvaPtn( uint8 ucFrEvaPtn );
extern dResult_e eFrdLcdSetUvlEn( flag fUvlEn );
extern dResult_e eFrdLcdSetUvlMode( uint8 ucUvlMode );
extern dResult_e eFrdLcdSetBdEn( flag fBdEn );
extern dResult_e eFrdLcdSetNrMode( dFrdLcdNrMode_e eNrMode );
extern dResult_e eFrdLcdSetNrMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame );
extern dResult_e eFrdLcdSetPccEn( flag fPccEn );
extern dResult_e eFrdLcdSetPccColEn( uint8 ucColNo, flag fColEn );
extern dResult_e eFrdLcdSetPccBshEn( uint8 ucColNo, flag fBriEn, flag fSatEn, flag fHueEn );
extern dResult_e eFrdLcdSetPccBshArea( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usCenter, uint16 usDelta );
extern dResult_e eFrdLcdSetPccBshLvl( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usLvl );
extern dResult_e eFrdLcdChgGamLut( flag fChgEn );
extern dResult_e eFrdLcdSetDac( flag fMemEn, uint16 usDat );
extern dResult_e eFrdLcdGetDac( flag fMemEn, uint16 *pusDat );
extern dResult_e eFrdLcdSetLvl( uint8 ucLvl );
extern dResult_e eFrdLcdSetMute( flag fMuteEnable );
extern dResult_e eFrdLcdSetVcomPtn( flag fVcomEn );
extern dResult_e eFrdLcdGetLibVer( uint8* pucLibVer );		//Global20120507

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* FRDLCDAPI_H */
