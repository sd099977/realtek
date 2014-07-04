/**
 * @file frdapi.c
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
//@@@@@@@@@@@@@@@@@@@@@@@@
#define TURNKEY1 1
#define printf(...)
#include <common.h>
//@@@@@@@@@@@@@@@@@@@@@@@@

/* **
 * ** include
 * **/
//?#include "frdapi.h"
#include <tcon/frdapi.h>

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#define YELLOWTAIL_VALID
#define FRASER_VALID
#endif //TURNKEY1

#include <tcon/frdlcdapi.h>		/* 搭載コントローラ列挙型定義が必要 */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//#include "frdlcdzyapi.h"/* Zucchini・YellowTail用ヘッダファイル */
#endif //TURNKEY1

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRASER_VALID

//?#include "frdfrapi.h"	/* Fraser用ヘッダファイル */
#endif //TURNKEY1

#endif

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef YELLOWTAIL_VALID
//?#include "frdtmapi.h"	/* YellowTail用ヘッダファイル */
#endif //TURNKEY1

#endif


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "frdicecapi.h"	/* Icec用ヘッダファイル */
//?#include "frdarapi.h"	/* Arugula用ヘッダファイル */
//?#include "frdlcdarapi.h"/* Arugula用(T-CON部)ヘッダファイル */
#endif //TURNKEY1


#include <tcon/frdplapi.h>	/* Plaice用ヘッダファイル */
#include <tcon/frdguapi.h>	/* Guava用ヘッダファイル */
#include <tcon/frdlcdguapi.h>	/* GuavaのVCOM調整用API(eFrdLcdGuSetFreeRun)の定義が曖昧な為Warningが発生している。よって、Warningを消す為に、include */	//sakata20110920

#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/

/* 外部 */
extern dFrdLcdControler_e eFrdLcdControler;

/* 内部 */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
static dFrc_TestPat_e eCurrentTestPtn = FRC_TESTPAT_OFF;	/* Fraser専用 */
#endif //TURNKEY1

static uint8 ucCurrentTemp = 4;		/* 本来LCD側の温度設定による更新も考慮し外部にするつもりだったが、
									本変数はeFrdSetPF()に必要な程度なので、staticに留める */

/* **
 * ** func
 * **/

/*!
********************************************************************************
** @brief	初期化設定API (FRC側)
** @param	fLrDrive		: パネル駆動方式の設定, TRUE = 片側駆動, FALSE = 両側駆動 (型定義: flag)
** @param	eInputFreq		: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdInit( flag fLrDrive, dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //KUAJAKU
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			switch(eInputFreq){
				case FRD_INPUT_FREQ_48HZ:
					eResult |= eFrcInitialize((dFrc_PanelSystem_e)fLrDrive, FRC_INPUT_V_FREQ_48HZ, TRUE);
					break;
				case FRD_INPUT_FREQ_50HZ:
					eResult |= eFrcInitialize((dFrc_PanelSystem_e)fLrDrive, FRC_INPUT_V_FREQ_50HZ, TRUE);
					break;
				case FRD_INPUT_FREQ_60HZ:
					eResult |= eFrcInitialize((dFrc_PanelSystem_e)fLrDrive, FRC_INPUT_V_FREQ_60HZ, TRUE);
					break;
				default:
					eResult |= S_SPEC_ERROR;
					break;
			}
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			//eResult |= eFrcTmInitStatus();
			eResult |= eFrcTmSetOutFreq((dFrcTmInputFreq_e)eInputFreq);
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArInit(fLrDrive, eInputFreq);
			break;
#endif //TURNKEY1
			
		case FRDLCD_PLAICE:
			/* 片側のみ */			
			eResult |= eFrdPlInit(eInputFreq);
			break;
		case FRDLCD_GUAVA:
			/* 片側のみ */
			printf("eFrdGuInit(eInputFreq)\r\n");
			eResult |= eFrdGuInit(eInputFreq);
			printf("eFrdSetFilmMode(FRD_MODE_OFF)\r\n");
			eResult |= eFrdSetFilmMode( FRD_MODE_OFF );	//20130124
			printf("eFrdSetQsMode(FRD_MODE_ADH)\r\n");
			eResult |= eFrdSetQsMode( FRD_MODE_ADH );	//20130124
			
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdStandby( flag fPipelineEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			if(fPipelineEnable == TRUE){
				eResult |= eFrcStandby(FALSE);
			}
			else{
				eResult |= eFrcStandby(TRUE);
			}
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetFrcReset(fPipelineEnable);
#endif
			break;
			
		case FRDLCD_ARUGULA:
//			eResult |= eFrdArStandby(fPipelineEnable);/* Arugulaでは、UPDATE OFFが使えないので */
			if(fPipelineEnable == TRUE){
				eResult |= eFrdLcdArSetFreeRun(FALSE);
			}
			else{
				eResult |= eFrdLcdArSetFreeRun(TRUE);
			}
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdPlStandby(fPipelineEnable);
			break;
		case FRDLCD_GUAVA:
			//VCOM対向調整ずれ対策	マイコンソフト変更連絡書の対応(No.YKIC-003)	//sakata20110627
//sakata20110627			eResult |= eFrdGuStandby(fPipelineEnable);
			if(fPipelineEnable == TRUE){					//sakata20110627
				eResult |= eFrdLcdGuSetFreeRun(FALSE);		//sakata20110627
			}												//sakata20110627
			else{											//sakata20110627
				eResult |= eFrdLcdGuSetFreeRun(TRUE);		//sakata20110627
			}												//sakata20110627
			break;
		default:
			return S_FAILURE;
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetMode( flag fFrcEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcLowDelay((dFrc_LowDelayMode_e)(!fFrcEnable));
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmSetMode((dFrcTmMode_e)fFrcEnable);
#endif
			break;

		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetMode(fFrcEnable);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetMode(fFrcEnable);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetMode(fFrcEnable);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdGetMode( flag *pfFrcStatus )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	dFrc_InternalData_t tFrcStatusDat;
	
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcGetStatus(&tFrcStatusDat);
			switch(tFrcStatusDat.eCurrentLowDelayMode){
				case FRC_NORMAL_DELAY_MODE:
					*pfFrcStatus = TRUE;
					break;
				case FRC_LOW_DELAY_MODE:
					*pfFrcStatus = FALSE;
					break;
				default:
					return S_FAILURE;
			}
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			/* YellowTailには、FRC(3rdMethod)の状態を取得する術はない
			  工程では、3rdMethod ON/OFF確認時は常にONし、その場を抜けたらOFF */
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArGetMode(pfFrcStatus);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdPlGetMode(pfFrcStatus);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuGetMode(pfFrcStatus);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetEdge( dFrdFrame_t *ptEdgeFrame )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcEdgeCtl(FRC_EDGE_DISABLED, FRC_EDGE_WEIGHT_10, (dFrc_Frame_t *)ptEdgeFrame);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetEdge(ptEdgeFrame);
			break;
		case FRDLCD_PLAICE:
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetEdge(ptEdgeFrame);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			YellowtailとPliaceの場合、4箇所までしかマスクできません。\n
**			YellowTailとPlaice(3rdMethod)では破綻が発生しないので、
**			基本的にマスクする必要はありません。\n
**			YellowTail, Pliaceでは、倍速半画面設定でマスクNo4を使用しているので、
**			No4は極力使用しないでください。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetMask( uint8 ucMaskNo, flag fMaskEnable, dFrdFrame_t *ptMaskFrame )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1

	if(ucMaskNo == 0)	return S_FAILURE;
	
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcMaskCtl((dFrc_MaskNo_e)(ucMaskNo-1), fMaskEnable, (dFrc_Frame_t *)ptMaskFrame);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			if(ucMaskNo < 5){
				eResult |= eFrcTmSetMask((dFrcTmMaskNo_e)(ucMaskNo-1), fMaskEnable, (dFrcTmFrame_t *)ptMaskFrame);
			}else{
				return S_FAILURE;
			}
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetMask(ucMaskNo, fMaskEnable, ptMaskFrame);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetMask(ucMaskNo, fMaskEnable, ptMaskFrame);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetMask(ucMaskNo, fMaskEnable, ptMaskFrame);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	ミュート設定API
** @param	fMuteEnable	: ミュート設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetMute( flag fMuteEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcMuteCtl(fMuteEnable);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmSetMute(fMuteEnable);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetMute(fMuteEnable);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetMute(fMuteEnable);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetMute(fMuteEnable);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetTestPtn( dFrdTestPtn_e eTestPtn, void *pvAdjTestPtn )
{
	dResult_e eResult = S_SUCCESS;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	dFrc_TestPat_e	eZTmp;
#ifdef YELLOWTAIL_VALID
	dFrcTmTestPat_e	eYTmp;
#endif
#endif //TURNKEY1

	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			if(eTestPtn >= FRD_TESTPTN_SHARP2)	return S_FAILURE;
			if(eTestPtn == FRD_TESTPTN_OFF)	eZTmp = FRC_TESTPAT_OFF;
			else							eZTmp = (dFrc_TestPat_e)(eTestPtn -1);
			
			eResult |= eFrcTestPatternCtl(FRC_HALFTEST_NORMAL, eZTmp, (dFrc_AdjTestPat_t *)pvAdjTestPtn );
			
			eCurrentTestPtn = eZTmp;
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			if(eTestPtn == FRD_TESTPTN_OFF)	eYTmp = FRCTM_TESTPAT_OFF;
			else							eYTmp = (dFrcTmTestPat_e)(eTestPtn -1);
			
			eResult |= eFrcTmSetTestPat( eYTmp, (dFrcTmAdjTestPat_t *)pvAdjTestPtn );
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetTestPtn(eTestPtn, (dFrdArAdjTestPtn_t *)pvAdjTestPtn);
			break;
#endif //TURNKEY1
		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetTestPtn(eTestPtn, (dFrdPlAdjTestPtn_t *)pvAdjTestPtn);
			break;
			
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetTestPtn(eTestPtn, (dFrdGuAdjTestPtn_t *)pvAdjTestPtn);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetOutFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	dFrc_InputVFreq_e eTmp = FRC_INPUT_V_FREQ_60HZ;
#endif //TURNKEY1
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			switch(eInputFreq){
				case FRD_INPUT_FREQ_48HZ:
					eTmp = FRC_INPUT_V_FREQ_48HZ;	break;
				case FRD_INPUT_FREQ_50HZ:
					eTmp = FRC_INPUT_V_FREQ_50HZ;	break;
				case FRD_INPUT_FREQ_60HZ:
					eTmp = FRC_INPUT_V_FREQ_60HZ;	break;
				default:
					eResult |= S_SPEC_ERROR;		break;
			}
			
			eResult |= eFrcOutFreq(eTmp);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmSetOutFreq((dFrcTmInputFreq_e)eInputFreq);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetOutFreq(eInputFreq);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetOutFreq(eInputFreq);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetOutFreq(eInputFreq);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetFreeRun( flag fFreeRunEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcFreeRun(fFreeRunEnable);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmSetFreeRun(fFreeRunEnable);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetFreeRun(fFreeRunEnable);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetFreeRun(fFreeRunEnable);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetFreeRun(fFreeRunEnable);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	FRCステータスデータ取得API
** @param	pvFrcStatusDat	: FRCステータスデータ (型定義: void *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			各デバイスによって、ステータスデータ型が異なります。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdGetStatus( void *pvFrcStatusDat )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcGetStatus((dFrc_InternalData_t *)pvFrcStatusDat);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmGetStatus((dFrcTmInternalDat_t *)pvFrcStatusDat);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArGetStatus((dFrdArInternalDat_t *)pvFrcStatusDat);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdPlGetStatus((dFrdPlInternalDat_t *)pvFrcStatusDat);
			break;

		case FRDLCD_GUAVA:
			eResult |= eFrdGuGetStatus((dFrdGuInternalDat_t *)pvFrcStatusDat);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
//sakata20110916 warning_erase	uint16	i;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	dAdvI2cFrc2Reg_t atTmp1[0x100];
#endif //TURNKEY1

	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			for(i=0; i<iRegNum; i++){
				atTmp1[i].usSub =  ptDatas[i].usAddr;
				atTmp1[i].ucVal =  (uint8)ptDatas[i].usVal;
			}
			
			eResult |= eFrcRegWriteDatas2(iRegNum, atTmp1);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			eResult |= eFrcLcdRegWriteDatas(FRCLCD_MASTER, iRegNum, (dFrcLcdRegVar_t *)ptDatas);
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArRegWs(iRegNum, ptDatas);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdPlRegWs(iRegNum, ptDatas);
			break;

		case FRDLCD_GUAVA:
			eResult |= eFrdGuRegWs(iRegNum, ptDatas);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
//sakata20110916 warning_erase	uint16	i;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	dAdvI2cFrcReg_t atTmp1[0x100];
#endif //TURNKEY1
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			for(i=0; i<iRegNum; i++){
				atTmp1[i].usSub =  ptDatas[i].usAddr;
			}
			
			eResult |= eFrcRegReadDatas2(iRegNum, atTmp1);
			
			for(i=0; i<iRegNum; i++){
				ptDatas[i].usAddr = atTmp1[i].usSub;
				ptDatas[i].usVal  = (uint16)atTmp1[i].ucVal;
			}
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			eResult |= eFrcLcdRegReadDatas(FRCLCD_MASTER, iRegNum, (dFrcLcdRegVar_t *)ptDatas);
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArRegRs(iRegNum, ptDatas);
			break;
#endif //TURNKEY1
		case FRDLCD_PLAICE:
			eResult |= eFrdPlRegRs(iRegNum, ptDatas);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuRegRs(iRegNum, ptDatas);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdRegW( uint16 usAddr, uint16 usVal)
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcRegWrite2(usAddr, (uint8)usVal);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			eResult |= eFrcLcdRegWriteZ(usAddr, usVal);
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArRegW(usAddr, usVal);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdPlRegW(usAddr, usVal);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuRegW(usAddr, usVal);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdRegR( uint16 usAddr, uint16 *pusVal)
{
	dResult_e eResult = S_SUCCESS;
//sakata20110916 warning_erase	uint8 ucVal;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcRegRead2(usAddr, &ucVal);
			*pusVal = (uint16)ucVal;
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			eResult |= eFrcLcdRegReadZ(usAddr, pusVal);
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArRegR(usAddr, pusVal);
			break;
#endif

		case FRDLCD_PLAICE:
			eResult |= eFrdPlRegR(usAddr, pusVal);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuRegR(usAddr, pusVal);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	PFゲイン設定API
** @param	ucTemp	: 温度指定[0-7] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			PlaiceではGainではなく3rdMethodのON/OFFになります
**			(ドライバ内でSetModeと連動しています)。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetGain( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcPostFilGain(ucTemp);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetGain(ucTemp);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetGain(ucTemp);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetGain(ucTemp);
			break;
		default:
			return S_FAILURE;
	}
	
	/* 暫定 */
	ucCurrentTemp = ucTemp;
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdDrawLine( flag fLineEnable, dFrdLineColor_e eLineColor, dFrdFrame_t *ptLineArea )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRASER_VALID
	dFrc_DemoColor_t  tTmp1;
#endif
#ifdef YELLOWTAIL_VALID
	dFrcTmLineColor_t tTmp2;
#endif

	switch(eLineColor){
		case FRD_LINE_COLOR_GRAY:

#ifdef FRASER_VALID
			tTmp1.ucDemoColorR = tTmp1.ucDemoColorG = tTmp1.ucDemoColorB = 0x08;
#endif
#ifdef YELLOWTAIL_VALID
			tTmp2.ucLineColorR = tTmp2.ucLineColorG = tTmp2.ucLineColorB = 0x08;
#endif
			break;
		case FRD_LINE_COLOR_BLUE:
#ifdef FRASER_VALID
			tTmp1.ucDemoColorR = tTmp1.ucDemoColorG = 0x00;
			tTmp1.ucDemoColorB = 0x0F;
#endif
#ifdef YELLOWTAIL_VALID
			tTmp2.ucLineColorR = tTmp2.ucLineColorG = 0x00;
			tTmp2.ucLineColorB = 0x0F;
#endif
			break;
		case FRD_LINE_COLOR_WHITE:
#ifdef FRASER_VALID
			tTmp1.ucDemoColorR = tTmp1.ucDemoColorG = tTmp1.ucDemoColorB = 0x0F;
#endif
#ifdef YELLOWTAIL_VALID
			tTmp2.ucLineColorR = tTmp2.ucLineColorG = tTmp2.ucLineColorB = 0x0F;
#endif
			break;
		case FRD_LINE_COLOR_BLACK:
#ifdef FRASER_VALID
			tTmp1.ucDemoColorR = tTmp1.ucDemoColorG = tTmp1.ucDemoColorB = 0x00;
#endif
#ifdef YELLOWTAIL_VALID
			tTmp2.ucLineColorR = tTmp2.ucLineColorG = tTmp2.ucLineColorB = 0x00;
#endif
			break;
		case FRD_LINE_COLOR_US_WHITE:
#ifdef FRASER_VALID
			tTmp1.ucDemoColorR = tTmp1.ucDemoColorG = tTmp1.ucDemoColorB = 0x0d;
#endif
#ifdef YELLOWTAIL_VALID
			tTmp2.ucLineColorR = tTmp2.ucLineColorG = tTmp2.ucLineColorB = 0x0d;
#endif
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
#endif //TURNKEY1
	
	switch(eFrdLcdControler){


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcDrawLine(fLineEnable, (dFrc_Frame_t *)ptLineArea, &tTmp1);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcTmDrawLine(fLineEnable, (dFrcTmFrame_t *)ptLineArea, &tTmp2);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArDrawLine(fLineEnable, eLineColor, ptLineArea);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlDrawLine(fLineEnable, eLineColor, ptLineArea);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuDrawLine(fLineEnable, eLineColor, ptLineArea);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	倍速半画面設定API
** @param	eModeHalf	: 倍速半画面設定 (型定義: dFrdModeHalf_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			本APIを設定する場合は、事前に eFrdSetMode( TRUE ) にしてください。\n
**			YellowTail, Pliaceの場合、マスクNo4にて半画面をマスクしています。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetModeHalf( dFrdModeHalf_e eModeHalf )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
//KUAJAKU nothing
#else //TURNKEY1
#ifdef YELLOWTAIL_VALID
	dFrcTmFrame_t tTmp;
#endif
#endif //TURNKEY1
	switch(eFrdLcdControler){


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcTestPatternCtl((dFrc_HalfFrc_e)eModeHalf, eCurrentTestPtn, NULL );;
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			/* QS halfを入れるかも... */
			switch(eModeHalf){
				case FRD_MODE_HALF_NORMAL:
					eResult |= eFrcTmSetMask(FRCTM_MASK_NO4, FALSE, NULL);
					break;
				case FRD_MODE_HALF_BOTTOM_ON:
					tTmp.usXPos = 0;
					tTmp.usYPos = 0;
					tTmp.usWidth = 1920;
					tTmp.usHeight = 540;
					
					eResult |= eFrcTmSetMask(FRCTM_MASK_NO4, TRUE, &tTmp);
					break;
				case FRD_MODE_HALF_UP_ON:
					tTmp.usXPos = 0;
					tTmp.usYPos = 540;
					tTmp.usWidth = 1920;
					tTmp.usHeight = 540;
					
					eResult |= eFrcTmSetMask(FRCTM_MASK_NO4, TRUE, &tTmp);
					break;
				case FRD_MODE_HALF_RIGHT_ON:
					tTmp.usXPos = 0;
					tTmp.usYPos = 0;
					tTmp.usWidth = 960;
					tTmp.usHeight = 1080;
					
					eResult |= eFrcTmSetMask(FRCTM_MASK_NO4, TRUE, &tTmp);
					break;
				case FRD_MODE_HALF_LEFT_ON:
					tTmp.usXPos = 960;
					tTmp.usYPos = 0;
					tTmp.usWidth = 960;
					tTmp.usHeight = 1080;
					
					eResult |= eFrcTmSetMask(FRCTM_MASK_NO4, TRUE, &tTmp);
					break;
				default:
					eResult |= S_SPEC_ERROR;
					break;
			}
			break;
#endif
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetModeHalf(eModeHalf);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdPlSetModeHalf(eModeHalf);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetModeHalf(eModeHalf);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetPF( flag fPFEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcSetPostFil(fPFEnable, ucCurrentTemp);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetPF(fPFEnable);
			break;
#endif //TURNKEY1

		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetPF(fPFEnable);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdGetPF( flag *pfPFStatus )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRASER_VALID
	dFrc_InternalData_t tFrcStatusDat;
#endif
#endif //TURNKEY1
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcGetStatus(&tFrcStatusDat);
			*pfPFStatus = tFrcStatusDat.fCurrentPostFilEnable;
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArGetPF(pfPFStatus);
			break;
#endif //TURNKEY1

		case FRDLCD_GUAVA:
			eResult |= eFrdGuGetPF(pfPFStatus);
			break;
		default:
			return S_FAILURE;
	}
	
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
** 			AVポジション, 入力切替等でホワイトバランス調整値, 色温度オフセット値
**			が変更する場合は、本APIをコールしてください。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetCtaParam( flag fCtaEnable, dFrdCtPoint_t *ptCtPoint, dFrdCtVal_t *ptCtVal )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcIcecSetCtaParameter(fCtaEnable, (dFrcIcecCtPoint_t *)ptCtPoint, (dFrcIcecCtVal_t *)ptCtVal);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetCtaParam(fCtaEnable, ptCtPoint, ptCtVal);
			break;
		case FRDLCD_PLAICE:
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetCtaParam(fCtaEnable, ptCtPoint, ptCtVal);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
** 			本APIをコールする場合は、事前に色温度逆補正設定API
**			eFrdSetCtaParam()をコールしておいてください。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetSkinCtl( int16 sHue, int16 sSat, int16 sVal )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef FRASER_VALID
			eResult |= eFrcIcecSkinCtl(sHue, sSat, sVal);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdArSetSkinCtl(sHue, sSat, sVal);
			break;
		case FRDLCD_PLAICE:
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuSetSkinCtl(sHue, sSat, sVal);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	DDR2 工程チェックAPI
** @param	pusErrInfo :	アドレス接続検査, データバス接続検査にて
**							得られた結果を格納する配列のポインタ (型定義: uint16)
** @retval	dFrdDdr2Res_e列挙体
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				未使用\n
*******************************************************************************/
dFrdDdr2Res_e eFrdChkDdr2( uint16 *pusErrInfo )
{
	dFrdDdr2Res_e eResult;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult = eFrdArChkDdr2(pusErrInfo);
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return FRD_DDR2_RES4;
	}

#endif //TURNKEY1

#ifdef TURNKEY2	//Warningを消す為にここの#ifdefを追加	//sakata20110920
	return eResult = FRD_DDR2_RES1;						//sakata20110920
#else //TURNKEY2											//sakata20110920
	return eResult;										//sakata20110920
#endif //TURNKEY2											//sakata20110920
}


/*!
********************************************************************************
** @brief	Filmモード設定API
** @param	eMode	: Filmモード設定 (型定義: dFrdMode_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetFilmMode( dFrdMode_e eMode )
{
	dResult_e eResult = S_SUCCESS;
	switch(eFrdLcdControler){


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ARUGULA:
			eResult = eFrdArSetFilmMode(eMode);
			break;
#endif //TURNKEY1

		case FRDLCD_GUAVA:
			eResult = eFrdGuSetFilmMode(eMode);
			break;
		default:
			break;
	}
	
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetQsMode( dFrdMode_e eMode )
{
	printf("eFrdSetQsMode1\r\n");
	dResult_e eResult = S_SUCCESS;
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ARUGULA:
			eResult = eFrdArSetQsMode(eMode);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
		printf("eFrdSetQsMode(FRDLCD_PLAICE)\r\n");
			switch( eMode ){
				case FRD_MODE_ADL:
				case FRD_MODE_ADH:
					eResult |= eFrdPlSetMode(TRUE);
					break;
				default:
					eResult |= eFrdPlSetMode(FALSE);
					break;
			}
			break;
		case FRDLCD_GUAVA:
		printf("eFrdSetQsMode(FRDLCD_GUAVA)\r\n");
			eResult = eFrdGuSetQsMode(eMode);
			break;
		default:
			break;
	}
	printf("eFrdSetQsMode2\r\n");
	
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdSetStill( flag fStill )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult = eFrdPlSetStill(fStill);
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			本APIに渡してください。\n
**			本APIを使用すれば、ヒステリシス処理や、下記APIをコールする必要
**			はなくなります。\n
**			- eFrdSetGain()\n
**			- eFrdLcdSetSbr()\n
**			- eFrdLcdSetQsTemp()\n
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdSetTemp( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult = eFrdPlSetTemp(ucTemp);
			break;

//GUAVAでQS切り替えが動作していなかったので、TURNKEY2モデルより追加
		case FRDLCD_GUAVA:								//sakata20110921


			eResult = eFrdLcdGuSetTemp(ucTemp);			//sakata20110921

			break;										//sakata20110921

		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	入力画素値キャプチャAPI
** @param	ptInputRgb[1920][1080] : 入力画素値格納配列 (型定義: dFrdPixelDat_t)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			本APIには、必ず[1920][1080]の要素数を用意してください。
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdGetInputRgb( dFrdPixelDat_t ptInputRgb[1920][1080] )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	uint16 i, j;
	dFrdPlPixelDat_t tTmp;
	
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			
			for(i=0; i<1920; i++){
				for(j=0; j<1080; j++){
					eResult = eFrdPlGetInputRgb(i, j, &tTmp);
					/* 10->8bitへ変換 */
					ptInputRgb[i][j].ucR = (uint8)((tTmp.usCvR & 0x3fc) >> 2);
					ptInputRgb[i][j].ucG = (uint8)((tTmp.usCvG & 0x3fc) >> 2);
					ptInputRgb[i][j].ucB = (uint8)((tTmp.usCvB & 0x3fc) >> 2);
					//eDbgPrintf(0, "[%04d][%04d] R: %04X, G: %04X, B: %04X\n", i, j, ptInputRgb[i][j].ucR, ptInputRgb[i][j].ucG, ptInputRgb[i][j].ucB);
				}
			}
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	工程 FRC ON/OFF 設定API
** @param	eModeChk		: 工程 FRC ON/OFF設定値	(型定義: dFrdModeChk_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetModeChk( dFrdModeChk_e eModeChk )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult = eFrdPlSetModeChk(eModeChk);
			break;
		case FRDLCD_GUAVA:
			eResult = eFrdGuSetModeChk(eModeChk);
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdGetCurrentVal( dFrdCurrentVal_t *ptCurrentVal )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult = eFrdPlGetCurrentVal(ptCurrentVal);
			break;
		case FRDLCD_GUAVA:
			eResult = eFrdGuGetCurrentVal(ptCurrentVal);
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "API ERROR\n");
#endif //TURNKEY1
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetArea3Scrl( flag fArea3En, dFrdArea3Scrl_t *ptArea3Scrl )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult = eFrdGuSetArea3Scrl(fArea3En, ptArea3Scrl);
			break;
		default:
			break;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	総合初期化 API
** @param	eInputFreq	: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetInit( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eResult |= eFrdLcdChkEepLoadEnd();
	eResult |= eFrdInit(TRUE, eInputFreq);
	eResult |= eFrdLcdInit(TRUE);

#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	総合周波数切替 API
** @param	eInputFreq	: 入力周波数設定 (型定義: dFrdInputFreq_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eResult |= eFrdSetOutFreq(eInputFreq);
	eResult |= eFrdLcdSetQsFreq(eInputFreq);
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	工程 テストパターン表示 API
** @param	ePtnSel	:テストパターン種別指定 (型定義: dFrdPtnSel_e)
** @param	ucPtn	:テストパターン番号指定 (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetPtn( dFrdPtnSel_e ePtnSel, uint8 ucPtn )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(ePtnSel){
		case FRD_PTN_FRC:
			eResult = eFrdSetTestPtn((dFrdTestPtn_e)ucPtn, NULL);
			break;
		case FRD_PTN_AGING:
			eResult = eFrdLcdSetAgingPtn(ucPtn);
			break;
		case FRD_PTN_EVA:
			eResult = eFrdLcdSetEvaPtn(ucPtn);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


#ifdef TURNKEY1
/*!
********************************************************************************
** @brief	TypvGain設定 API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			eFrdLcdSetLvl()を用いる場合は、本APIのコールが不要です。
** @note	1秒毎にコールしてください。
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				未使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdSetTypvGain( void )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult = eFrdGuSetTypvGain();
			break;
		default:
			break;
	}
	
	return eResult;
}
#endif //TURNKEY1



//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
#ifdef TURNKEY1 //いつの間にか削除されていたAPI達
				//一時的でもライブラリができるように修正
/*!
********************************************************************************
** @brief	DemoMode設定 API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			設定したいDemo情報
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
*******************************************************************************/
dResult_e eFrdSetDemoMode( dFrdDemoMode_e eDemoMode )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eFrdPlSetDemoMode(eDemoMode);
			break;
#ifdef TURNKEY1
		case FRDLCD_GUAVA:
			eFrdGuSetDemoMode(eDemoMode);
			break;
#endif //TURNKEY1
		case FRDLCD_ARUGULA:
			break;
		default:
		
			return S_FAILURE;
	}
	
	return eResult;
	
}


#endif //TURNKEY1

/* end of file */
