/**
 * @file frdlcdapi.c
 *
 * @brief LCD制御
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
 //@@@@@@@@@@@@@@@@@@@@@@@@
#define TURNKEY1 1
#define printf(...)
#include <common.h>
//@@@@@@@@@@@@@@@@@@@@@@@@

#include <tcon/frdlcdapi.h>

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#define YELLOWTAIL_VALID
#define FRDLCD_FPGA_VALID
#endif //TURNKEY1


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "frdlcdzyapi.h"	/* Zucchini・YellowTail用ヘッダファイル */
//?#include "frdlcdarapi.h"	/* Arugula用ヘッダファイル */
#endif //TURNKEY1

#include <tcon/frdlcdplapi.h>	/* Plaice用ヘッダファイル(TCON側) */
#include <tcon/frdplapi.h>		/* Plaice用ヘッダファイル(FRC側) */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "frdfpgaapi.h"		/* FPGA(Begonia)用ヘッダファイル */
#endif //TURNKEY1

#include <tcon/frdguapi.h>		/* Guava用ヘッダファイル(FRC側) */
#include <tcon/frdlcdguapi.h>	/* Guava用ヘッダファイル(TCON側) */

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>


//Library Version name													//Global20111227
const volatile uint8 sharp_version[]="libDoubleScan_20130129_VER16";	//Global20121205

/* **
 * ** define
 * **/

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/

/* グローバル変数 */
dFrdLcdControler_e eFrdLcdControler = FRDLCD_PLAICE;	/* default */

//sakata20111013 static dFrdLcdPnlSize_e eFrdLcdPnlSize = FRDLCD_PNL_32;
//static uint8 aucFrdLcdRevInfo[FRDLCD_REVISION_DATA_MAX];
/* **
 * ** func
 * **/

static dResult_e eLcdGetLsiInfo(dFrdLcdControler_e *peControler);

/*!
********************************************************************************
** @brief	汎用レジスタ連続書込みAPI (LCD側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDatas	: 書込みデータ配列(型定義: dFrdRegVar_t *)
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
dResult_e eFrdLcdRegWs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdRegWriteDatas(FRCLCD_MASTER, iRegNum, (dFrcLcdRegVar_t *)ptDatas);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRegWs(FRDLCDAR_AB, iRegNum, ptDatas);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRegWs(LCDPL_AB, iRegNum, ptDatas);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRegWs(LCDGU_AB, iRegNum, ptDatas);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	汎用レジスタ連続読込みAPI (LCD側)
** @param	iRegNum	: レジスタ数 (型定義: int32)
** @param	ptDatas	: 読込みデータ配列(型定義: dFrdRegVar_t *)
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
dResult_e eFrdLcdRegRs( int32 iRegNum, dFrdRegVar_t * ptDatas )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdRegReadDatas(FRCLCD_MASTER, iRegNum, (dFrcLcdRegVar_t *)ptDatas);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRegRs(FRDLCDAR_AB, iRegNum, ptDatas);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRegRs(LCDPL_AB, iRegNum, ptDatas);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRegRs(LCDGU_AB, iRegNum, ptDatas);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdRegW( uint16 usAddr, uint16 usVal )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdRegWriteZ(usAddr, usVal);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRegW(FRDLCDAR_AB, usAddr, usVal);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRegW(LCDPL_AB, usAddr, usVal);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRegW(LCDGU_AB, usAddr, usVal);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdRegR( uint16 usAddr, uint16 *pusVal )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdRegReadZ(usAddr, pusVal);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRegR(FRDLCDAR_AB, usAddr, pusVal);
			brak;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			printf("FRDLCD_PLAICE\r\n");
			eResult |= eFrdLcdPlRegR(LCDPL_AB, usAddr, pusVal);
			break;
		case FRDLCD_GUAVA:
			printf("FRDLCD_GUAVA\r\n");
			eResult |= eFrdLcdGuRegR(LCDGU_AB, usAddr, pusVal);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	パネルサイズ設定用API
** @param	ePnlSize	: パネルサイズ設定(型定義: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note	必ず eFrdLcdGetLsiInfo より先に呼ぶこと(ルビコン仕様としては。それ以外はコールの必要なし)
*******************************************************************************/
dResult_e eFrdLcdSetSize( dFrdLcdPnlSize_e ePnlSize )
{
	dResult_e eResult = S_SUCCESS;
	
	/* For test */
	//vInitI2CFunction(&MApi_SWI2C_WriteBytes, &MApi_SWI2C_ReadBytes);
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
		case FRDLCD_ARUGULA:
#endif //TURNKEY1

		case FRDLCD_GUAVA:
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetSize( ePnlSize );
			break;
		default:
			return S_FAILURE;
	}
	
//sakata20111013	eFrdLcdPnlSize = ePnlSize;
	
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
dResult_e eFrdLcdGetSize( dFrdLcdPnlSize_e *pePnlSize )
{
	dResult_e eResult = S_SUCCESS;
#if 0
	switch(eFrdLcdControler){
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
		case FRDLCD_ARUGULA:
		case FRDLCD_GUAVA:
//sakata20111013			*pePnlSize = eFrdLcdPnlSize;
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlGetSize(pePnlSize);
			break;
		default:
			return S_FAILURE;
	}
#else
//sakata20111013	*pePnlSize = eFrdLcdPnlSize;
#endif	
	return eResult;
}


/*!
********************************************************************************
** @brief	T-con搭載LSI判別API
** @retval	FRDLCD_ZUCCHINI or FRDLCD_YELLOWTAIL or FRDLCD_ARUGULA or FRDLCD_PLAICE or FRDLCD_GUAVA
** @par コメント
**			最初にコールするT-conLSIドライバAPIです。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n;
*******************************************************************************/
dFrdLcdControler_e eFrdLcdGetLsiInfo( void )
{
	dFrdLcdControler_e eControler    = FRDLCD_UNKNOWN;
	dFrdLcdControler_e eControlerTmp = FRDLCD_UNKNOWN;
	uint8 ucSuccessCnt=0;
	uint8 ucI2cErrorCnt=0;
	uint8 ucRegErrorCnt=0;
	flag fEnd = FALSE;


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
#if 0
	eFrdLcdGetSize( &ePnlSize );
	/* 60型の場合のみI2Cアクセス前にwait追加。値の根拠は tI2CT > 750ms というハード制約。
	   起点となる PEアサート から I2Cアイソレーション解除 まで140msあるので、750-140 = 610ms  */

		if( ePnlSize == FRDLCD_PNL_60 ) MDrv_Timer_Delayms( 610 );

#else
	/* Managerから正しいサイズが与えられない場合を考慮すると、常にwaitを入れるのが安全
	   → とりあえず常にwait 610msとします。起動時間への影響について注意する必要がある。2009.07.16 */

		MDrv_Timer_Delayms( 610 );
	
#endif
#endif
#endif //TURNKEY1

	eFrdLcdControler = FRDLCD_GUAVA; /* ここで初期化しないと、一旦UNKNOWNと判別されると以降復帰できない */
	
	while(1){
		
		if(eLcdGetLsiInfo(&eControler) == S_SUCCESS){
		
			if((eControler == eControlerTmp) && (eControler != FRDLCD_UNKNOWN)){
				ucSuccessCnt++;
				if(ucSuccessCnt == 2){
					fEnd = TRUE;
					break;
				}
			}
			else{
				ucSuccessCnt = 0;
				ucRegErrorCnt++;
				if(ucRegErrorCnt == 4)break;
			}

			MDrv_Timer_Delayms( 5 );

		}
		else{
			ucSuccessCnt = 0;
			ucI2cErrorCnt++;
			if(ucI2cErrorCnt == 10)break;
				MDrv_Timer_Delayms(10);
		}
		eControlerTmp = eControler;
	}
	
	if(fEnd == FALSE){
	/* 最終的に失敗の場 */
		eControler = FRDLCD_UNKNOWN;
	}
	
	eFrdLcdControler = eControler;
	
	return eControler;
}


/*!
********************************************************************************
** @brief	EEPROMロード正常終了チェックAPI
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
dResult_e eFrdLcdChkEepLoadEnd( void )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdCheckEepLoadEnd();
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArChkRomLoadEnd();
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlChkRomLoadEnd();
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuChkRomLoadEnd();
			break;
		default:
			return S_FAILURE;
	}
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	/* 60型のみ、別途FPGA(Begonia)の起動完了待ちが必要 */
	eFrdLcdGetRevInfo( aucFrdLcdRevInfo );
	if( ( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] == 0x60 ) && ( eFrdLcdControler != FRDLCD_GUAVA ) ){
		eResult = eFrdFpgaGetStatus();
	}
#endif
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	初期化設定API(LCD側)
** @param	fLrDrive	: パネル駆動方式の設定, TRUE = 片側駆動, FALSE = 両側駆動 (型定義: flag)
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
dResult_e eFrdLcdInit( flag fLrDrive )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdInitialize((dFrcLcdPanelSystem_e)fLrDrive);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArInit(fLrDrive);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlInit();	/* 片側のみ */
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuInit();	/* 片側のみ */
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetTurnOver((dFrcLcdTurnOver_e)eTrnOvr);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetTrnOvr(eTrnOvr);
			break;
#endif

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetTrnOvr(eTrnOvr);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetTrnOvr(eTrnOvr);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	映像出力設定API
** @param	fOutEnable	: 出力(ON/OFF)設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Arugula以前のLSIでは、出力OFFすることはできません。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetOutput( flag fOutEnable )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
			eResult |= eFrcLcdOutputEnable();
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetOutput(fOutEnable);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetOutput(fOutEnable);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetOutput(fOutEnable);
			break;
		default:
			return S_FAILURE;
	}
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	if( ( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] == 0x60 ) && ( eFrdLcdControler != FRDLCD_GUAVA ) ){
	/* 60型の場合 */
		eFrdFpgaSetOutput( fOutEnable );
	}
#endif
#endif //TURNKEY1
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetTestPtn( dFrdLcdTestPtn_e eTestPtn )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_SOUSA:
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetTestPattern((dFrcLcdTestPattern_e)eTestPtn);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetTestPtn(eTestPtn);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetTestPtn(eTestPtn);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetTestPtn(eTestPtn);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDエージング用パターン設定API
** @param	ucAgingPtn : エージングパターン番号 [0x00-0x21] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Zucchiniは0x1F以降のパターンは表示されません。
**			Arugulaは0x20以降のパターンは表示されません。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetAgingPtn( uint8 ucAgingPtn )
{
	dResult_e eResult = S_SUCCESS;
	
	if((eFrdLcdControler == FRDLCD_ZUCCHINI) && (ucAgingPtn >= 0x1F )) return S_FAILURE;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdAgingPattern(ucAgingPtn);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetAgingPtn(ucAgingPtn);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetAgingPtn(ucAgingPtn);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetAgingPtn(ucAgingPtn);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD評価用パターン設定API
** @param	ucEvaPtn : エヴァパターン番号 [0x00-0x12] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			Zucchini, Arugulaでは、0x12のパターンは表示されません。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetEvaPtn( uint8 ucEvaPtn )
{
	dResult_e eResult = S_SUCCESS;
	
	if((eFrdLcdControler == FRDLCD_ZUCCHINI) && (ucEvaPtn >= 0x12 )) return S_FAILURE;
	
	switch(eFrdLcdControler){


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdEvaPattern(ucEvaPtn);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetEvaPtn(ucEvaPtn);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetEvaPtn(ucEvaPtn);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetEvaPtn(ucEvaPtn);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS ON/OFF設定API
** @param	fQsEnable	: QS ON/OFF設定, TRUE = ON, FALSE = OFF (型定義: flag)
** @param	fYuv 		: 入力信号指定, TRUE = YUV信号, FALSE = Y信号 (型定義: flag)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			YUV/Yを考慮する必要があるのはYellowtailとPlaiceです。その他のLSIの場合、
**			引数fYuvの値は適当で構いません。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetQsEnable( flag fQsEnable, flag fYuv )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetQsEnable(fQsEnable);
#endif
			break;
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetEcoQsEnable(fQsEnable, fYuv);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetQsEnable(fQsEnable);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetQsEn(fQsEnable, fYuv);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetQsEn(fQsEnable);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS半画面ON/OFF設定API
** @param	fLonRoff : 半画面ON/OFF設定, TRUE = 左ON右OFF, FALSE = 左OFF右ON (型定義: flag)
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
dResult_e eFrdLcdSetQsHalf( flag fLonRoff )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetQsHalf( fLonRoff );
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetQsHalf( fLonRoff );
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetQsHalf( fLonRoff );
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetQsHalf( fLonRoff );
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetQsFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetQsFreq((dFrcLcdInputFreq_e)eInputFreq);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetQsFreq(eInputFreq);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetQsFreq(eInputFreq);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetQsFreq(eInputFreq);
			break;
		default:
			return S_FAILURE;
	}
	
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetQsTemp( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetQsTemp(ucTemp);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetQsTemp(ucTemp);
			break;
#endif //TURNKEY1


		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetQsTemp(ucTemp);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetQsLvl(ucTemp);
			break;
		default:
			return S_FAILURE;
	}

	if ( eResult == S_SUCCESS ) {
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(DBG_LOG, "FRD: QS LEVEL = %d\n", ucTemp);
#endif //TURNKEY1
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
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用 [ただし eFrdSetTemp() があるためコールの必要なし]\n
**			Guava:				使用 [ただし eFrdSetTemp() があるためコールの必要なし]\n
*******************************************************************************/
dResult_e eFrdLcdSetSbr( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	if( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] != 0x60 ){
#endif
#endif //TURNKEY1
		switch(eFrdLcdControler){


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			case FRDLCD_ZUCCHINI:
			case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
				eResult |= eFrcLcdSetSbr(ucTemp);
#endif
				break;
			case FRDLCD_ARUGULA:
				eResult |= eFrdLcdArSetSbr(ucTemp);
				break;
#endif //TURNKEY1


			case FRDLCD_PLAICE:
				eResult |= eFrdLcdPlSetSbr(ucTemp);
				break;
			case FRDLCD_GUAVA:
				eResult |= eFrdLcdGuSetSbr(ucTemp);
				break;
			default:
				return S_FAILURE;
		}

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	}
	else{
	/* 60型の場合 */
		switch(eFrdLcdControler){
			case FRDLCD_ARUGULA:
				eResult |= eFrdFpgaSetTemp( ucTemp );	/* Begoniaにて */
				break;
			case FRDLCD_PLAICE:
				eResult |= eFrdLcdPlSetSbr(ucTemp);		/* Plaiceにて */
				break;
			case FRDLCD_GUAVA:
				eResult |= eFrdLcdGuSetSbr(ucTemp);		/* Guavaにて */
				break;
			default:
				return S_FAILURE;
		}
	}
#endif
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	Revision取得API
** @param	pucRevInfo : Revisionデータを格納する配列のポインタ(型定義: uint8)
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
dResult_e eFrdLcdGetRevInfo( uint8 *pucRevInfo )
{
	dResult_e eResult = S_SUCCESS;
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdGetRevInfo(pucRevInfo);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArGetRevInfo(pucRevInfo);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlGetRevInfo(pucRevInfo);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuGetRevInfo(pucRevInfo);
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	(統合)Revision取得API
** @param	pucRevInfo : Revisionデータを格納する配列のポインタ(型定義: uint8)
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
dResult_e eFrdLcdGetUnifiedRevInfo( uint8 *pucRevInfo )
{
	dResult_e eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
		case FRDLCD_ARUGULA:
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlGetUnifiedRevInfo(pucRevInfo);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuGetUnifiedRevInfo(pucRevInfo);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM Revision 表示用API
** @param	pcRevInfo : Revisionデータ表示用文字列を格納する配列のポインタ(型定義: int8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント 配列のサイズは必ず32バイトを確保すること。
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdGetRevStr( int8 *pcRevInfo )
{
	dResult_e eResult = S_SUCCESS;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	int32	i;
#endif
#endif //TURNKEY1
	
	switch(eFrdLcdControler){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
			eResult = S_FAILURE;
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArGetRevStr(pcRevInfo);
			break;
#endif //TURNKEY1

		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlGetRevStr(pcRevInfo);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuGetRevStr(pcRevInfo);
			break;
		default:
			return S_FAILURE;
	}

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRDLCD_FPGA_VALID
	if( ( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] == 0x60 ) && ( eFrdLcdControler != FRDLCD_GUAVA ) )
	{
		for(i=0; i<32; i++)
		{
			if( *(pcRevInfo + i) == '\0' )
			{
				*(pcRevInfo + i) = '/';
				eFrdFpgaGetFlashVerStr( (pcRevInfo + i + 1) );
				break;
			}
		}
	}
#endif
#endif //TURNKEY1

	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ連続書込みAPI
** @param	uiAddr		: ROM書込み先アドレス			(型定義: uint32)
** @param	uiLength	: 書込みデータ長				(型定義: uint32)
** @param	pucDatas	: 書込みデータの先頭ポインタ	(型定義: uint8*)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
**			Guava:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
*******************************************************************************/
dResult_e eFrdLcdEepWs( uint32 uiAddr, uint32 uiLength, uint8* pucDatas )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdWriteEepDatas(FRCLCD_MASTER, uiAddr, uiLength, pucDatas);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRomWs(uiAddr, uiLength, pucDatas);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRomWs(uiAddr, uiLength, pucDatas);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRomWs(uiAddr, uiLength, pucDatas);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ連続読込みAPI
** @param	uiAddr		: ROM読込み先アドレス			(型定義: uint32)
** @param	uiLength	: 読込みデータ長				(型定義: uint32)
** @param	pucDatas	: 読込みデータの先頭ポインタ	(型定義: uint8*)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
**			Guava:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
*******************************************************************************/
dResult_e eFrdLcdEepRs( uint32 uiAddr, uint32 uiLength, uint8* pucDatas )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdReadEepDatas(uiAddr, (uint16)uiLength, pucDatas);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRomRs(uiAddr, (uint16)uiLength, pucDatas);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRomRs(uiAddr, (uint16)uiLength, pucDatas);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRomRs(uiAddr, (uint16)uiLength, pucDatas);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMデータ消去API
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			使用\n
**			Arugula:			使用\n
**			Plaice:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
**			Guava:				使用 [ただし eFrdLcdSetVerUp() があるためコールの必要なし]\n
*******************************************************************************/
dResult_e eFrdLcdEepErase( void )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSerialFlashBulkErase();
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArRomBulkErase();
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlRomErase();
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuRomErase();
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	垂直デコント ON/OFF設定用API
** @param	eDecontEnable	: デコント ON/OFF設定 (型定義: dFrdLcdDecont_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note    Arugulaのみ
*******************************************************************************/
dResult_e eFrdLcdSetDecontEnable( dFrdLcdDecont_e eDecontEnable )
{
	dResult_e	eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetDecontEnable(eDecontEnable);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	ROMバージョンアップAPI
** @param	pucDats	: ROMデータの先頭ポインタ (型定義: uint8 *)
** @param	fVerify	: ベリファイ設定, TRUE = ON, FALSE = OFF (型定義: flag)
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
dResult_e eFrdLcdSetVerUp( uint8 *pucDats, flag fVerify )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetVerUp(pucDats,fVerify);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetVerUp(pucDats,fVerify);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetVerUp(pucDats,fVerify);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	画面出力用API
** @param	ePnlSize	: パネルサイズ設定(型定義: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**			VerUp時等の画を出すためだけの関数です。\n
**			対応するパネルサイズ設定のデータをロードします。\n
**			本API内で、下記のAPIがコールされています。
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdOutSource( dFrdLcdPnlSize_e ePnlSize )
{
	dResult_e eResult = S_SUCCESS;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	uint8 aucTmp[16];
	flag fLrDrive = TRUE;
	
	eFrdLcdGetLsiInfo();
	eResult |= eFrdLcdSetSize(ePnlSize);
	eResult |= eFrdLcdChkEepLoadEnd();
	eResult |= eFrdLcdGetRevInfo(aucTmp);
	if(aucTmp[FRDLCD_REVISION_PANEL]) fLrDrive = FALSE;
	eResult |= eFrdLcdInit(fLrDrive);
	eResult |= eFrdInit(fLrDrive, FRD_INPUT_FREQ_60HZ);
	eResult |= eFrdLcdSetTrnOvr(FRDLCD_TRN_OVR_NORMAL);
	eResult |= eFrdLcdSetOutput(TRUE);
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	フリーラン設定API (LCD側)
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
dResult_e eFrdLcdSetFreeRun( flag fFreeRunEnable )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetFreeRun(fFreeRunEnable);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetFreeRun(fFreeRunEnable);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetFreeRun(fFreeRunEnable);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetFreeRun(fFreeRunEnable);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	出力画素データ(RGB値)取得用API
** @param	x			: X座標		(型定義: uint16)
** @param	y			: Y座標		(型定義: uint16)
** @param	ptRgbColor	: RGB色		(型定義: dFrdLcdRgb_t)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: PPDS出力段における画素データを取得します。
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				未使用\n
********************************************************************************/
dResult_e eFrdLcdGetRgb(uint16 x, uint16 y, dFrdLcdRgb_t *ptRgbColor)
{
	dResult_e	eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArGetRgb(x, y, ptRgbColor);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	テストパターン(ベタ表示)設定用関数
** @param	ptColor : 色指定 (型定義: dFrdLcdTpColor_t)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 
**			LCDC側評価用テストパターンの"0x03 : ベタ表示"の設定です。\n
**			ptColor = NULL としてコールすると通常モードに戻ります。\n
**			上下輝度差調整時に使用されることを想定したものです。\n
**			終了時にNULLとしてコールしてください。
** @note    
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetBetaPtn( dFrdLcdTpColor_t *ptColor )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		case FRDLCD_ZUCCHINI:
		case FRDLCD_YELLOWTAIL:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetTestPatternBeta((dFrcLcdTestPaternColor_t *)ptColor);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetBetaPtn(ptColor);
			break;
#endif //TURNKEY1
		case FRDLCD_PLAICE:
		case FRDLCD_GUAVA:
			/* 何もしません */
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	パネル上下輝度差調整用API(上側)
** @param	iLevel : 調整値 (型定義: int32)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 輝度調整(上側)をDACレジスタの調整により行います。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetLumaAdjU( int32 iLevel )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdSetLumaAdjU(iLevel);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArSetLumaAdjU(iLevel);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	パネル上下輝度差調整値取得用API(上側)
** @param	piLevel : 調整値 (型定義: int32)
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 輝度調整値(上側)を返します。
** @note
**			Fraser+Zucchini:	使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				未使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdGetLumaAdjU( int32 *piLevel )
{
	dResult_e eResult = S_SUCCESS;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ZUCCHINI:
#ifdef YELLOWTAIL_VALID
			eResult |= eFrcLcdGetLumaAdjU(piLevel);
#endif
			break;
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArGetLumaAdjU(piLevel);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
********************************************************************************/
dResult_e eFrdLcdGetErrInfo( dFrdLcdError_t *ptError )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	if( ptError == NULL ) return S_FAILURE;

	ptError->ucErrCode = 0;/* 初期化 */
	
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdLcdArGetErrInfo(ptError);
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlGetErrInfo(ptError);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuGetErrInfo(ptError);
			break;
		default:
			break;
	}
#ifdef FRDLCD_FPGA_VALID
	if( ( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] == 0x60 ) && ( eFrdLcdControler != FRDLCD_GUAVA ) ){
		if( ptError->ucErrCode == 0 ){
			eResult |= eFrdFpgaGetErrInfo(ptError);
		}
	}
#endif
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	マニュアルロード全パターン実行API
** @retval	S_SUCCESS 成功
** @retval	S_FAILURE 失敗
** @par		コメント: 
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
********************************************************************************/
dResult_e eFrdLcdAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdArAllManualLoad();	/* FRC側 */
			eResult |= eFrdLcdArAllManualLoad();/* LCDC側 */
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdPlAllManualLoad();	/* FRC側 */
			eResult |= eFrdLcdPlAllManualLoad();/* LCDC側 */
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuAllManualLoad();	/* FRC側 */
			eResult |= eFrdLcdGuAllManualLoad();/* LCDC側 */
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDエージングパターン設定API (FR側)
** @param	ucFrAgingPtn : エージングパターン番号 [0x00-0x21] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetFrAgingPtn( uint8 ucFrAgingPtn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetFrAgingPtn(ucFrAgingPtn);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD評価用パターン設定API (FR側)
** @param	ucFrEvaPtn : 評価用パターン番号 [0x00-0x12] (型定義: uint8)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetFrEvaPtn( uint8 ucFrEvaPtn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetFrEvaPtn(ucFrEvaPtn);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetUvlEn( flag fUvlEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetUvlEn(fUvlEn);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetUvlMode( uint8 ucUvlMode )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetUvlMode(ucUvlMode);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetBdEn( flag fBdEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetBdEn(fBdEn);
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetBdEn(fBdEn);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetNrMode( dFrdLcdNrMode_e eNrMode )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetNrMode(eNrMode);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetNrMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetNrMask(ucMaskNo, fMaskEn, ptMaskFrame );
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetPccEn( flag fPccEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetPccEn(fPccEn);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetPccColEn( uint8 ucColNo, flag fColEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetPccColEn(ucColNo, fColEn);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetPccBshEn( uint8 ucColNo, flag fBriEn, flag fSatEn, flag fHueEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetPccBshEn(ucColNo, fBriEn, fSatEn, fHueEn);
			break;
		default:
			return S_FAILURE;
	}

#endif //TURNKEY1
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
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetPccBshArea( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usCenter, uint16 usDelta )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetPccBshArea(ucColNo, eBsh, usCenter, usDelta);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
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
** @par コメント
**			事前に指定領域をONしてください。
** @note
**			Fraser+Zucchini:	未使用\n
**			Yellowtail:			未使用\n
**			Arugula:			未使用\n
**			Plaice:				使用\n
**			Guava:				未使用\n
*******************************************************************************/
dResult_e eFrdLcdSetPccBshLvl( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usLvl )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlSetPccBshLvl(ucColNo, eBsh, usLvl);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	Gamma LUT 書き換え用API (Plaice色沈み対策 2009.06.29)
** @param	fChgEn		: 書換えON/OFF (型定義: falg)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
** @note
*******************************************************************************/
dResult_e eFrdLcdChgGamLut( flag fChgEn )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdLcdPlChgGamLut(fChgEn);
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	DAC設定用API (VCOM設定用)
** @param	fMemEn : 書込み先指定 TRUE: メモリー, FALSE: レジスタ (型定義: flag)
** @param	usDat  : VCOM調整データ (型定義: uint16)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetDac( flag fMemEn, uint16 usDat )
{
	dResult_e eResult = S_SUCCESS;

//#ifdef TURNKEY1		//SERD zhang 2012/10/15 delete
//TURNKEY1 nothing
//#else //TURNKEY1		//SERD zhang 2012/10/15 delete
	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetDac(fMemEn, usDat);
			break;
		default:
			return S_FAILURE;
	}
//#endif //TURNKEY1		//SERD zhang 2012/10/15 delete
	return eResult;
}


/*!
********************************************************************************
** @brief	DAC確認用API (VCOM設定用)
** @param	fMemEn : 書込み先指定 TRUE: メモリー, FALSE: レジスタ (型定義: flag)
** @param	pusDat  : VCOM調整データ (型定義: uint16 *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
**			Guava:				使用(ただし常にメモリからリード)\n
*******************************************************************************/
dResult_e eFrdLcdGetDac( flag fMemEn, uint16 *pusDat )
{
	dResult_e eResult = S_SUCCESS;

//#ifdef TURNKEY1		//SERD zhang 2012/10/15 delete
//TURNKEY1 nothing
//#else //TURNKEY1		//SERD zhang 2012/10/15 delete
	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuGetDac(pusDat);
			break;
		default:
			return S_FAILURE;
	}
//#endif //TURNKEY1		//SERD zhang 2012/10/15 delete
	return eResult;
}


/*!
********************************************************************************
** @brief	温度レベル設定API
** @param	ucLvl	: 温度レベルの指定 [0(低温)-7(高温)] (型定義: uint8 *)
** @retval	S_SUCCESS 正常終了
** @retval	other エラーコード
** @par コメント
**
** @note
**			Guava:				使用\n
*******************************************************************************/
dResult_e eFrdLcdSetLvl( uint8 ucLvl )
{
	dResult_e eResult = S_SUCCESS;

	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetLvl(ucLvl);
			break;
		default:
			break;
	}
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
*******************************************************************************/
dResult_e eFrdLcdSetMute( flag fMuteEnable )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			if( fMuteEnable == TRUE ){
				eResult |= eFrdLcdArSetOutput(FALSE);
			}
			else{
				eResult |= eFrdLcdArSetOutput(TRUE);
			}
#ifdef FRDLCD_FPGA_VALID
			if( aucFrdLcdRevInfo[FRDLCD_REVISION_INCHI] == 0x60 ){
				eFrdFpgaSetMute( fMuteEnable );
			}
#endif
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetOutput(!fMuteEnable);
			break;
		default:
			break;
	}
#endif //TURNKEY1
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
dResult_e eFrdLcdSetVcomPtn( flag fVcomEn )
{
	dResult_e eResult = S_SUCCESS;

//#ifdef TURNKEY1		//SERD zhang 2012/10/15 delete
//TURNKEY1 nothing
//#else //TURNKEY1		//SERD zhang 2012/10/15 delete
	switch(eFrdLcdControler){
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuSetVcomPtn(fVcomEn);
			break;
		default:
			break;
	}
//#endif //TURNKEY1		//SERD zhang 2012/10/15 delete
	return eResult;
}


#define FRDLCD_ADDR_ON_BOARD_LSI_HANBETSU	0x6C3D /* SousaII/Zucchini判別用レジスタアドレス */
#define FRDLCD_ADDR_ON_BOARD_LSI_DETECT		0x6CEF /* コントローラ基板搭載LSI判別用レジスタ(YellowTail以降)アドレス */
static dResult_e eLcdGetLsiInfo(dFrdLcdControler_e *peControler)
{
	printf("In eLcdGetLsiInfo\r\n");
	uint16		usVal;
	dResult_e	eResult = S_SUCCESS;
	
	eResult = eFrdLcdRegR(FRDLCD_ADDR_ON_BOARD_LSI_DETECT, &usVal);/* Arugula用の汎用読み込みAPIを使用 */
	printf("In eLcdGetLsiInfo, eResult=%x\r\n",eResult);
	if(eResult != S_SUCCESS){
		printf("In eLcdGetLsiInfo, eResult != S_SUCCESS\r\n");
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "[LCDC] FAILURE(eFrdLcdGetLsiInfo)!!!!!\n");
#endif //TURNKEY1
		*peControler = FRDLCD_UNKNOWN;
	}
	else{
		switch(usVal){
			case 0x01:	/* Sousa2 or Zucchini */
				eResult = eFrdLcdRegR(FRDLCD_ADDR_ON_BOARD_LSI_HANBETSU, &usVal);/* Arugula用の汎用読み込みAPIを使用 */
				if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
					eDbgPrintf(0, "[LCDC] FAILURE(eFrdLcdGetLsiInfo)!!!!!\n");
#endif //TURNKEY1
					*peControler = FRDLCD_UNKNOWN;
				}
				else{
					if((usVal & 0xF0) == 0xF0){
						*peControler = FRDLCD_SOUSA;
					}
					else if((usVal & 0xF0) == 0x00){
						*peControler = FRDLCD_ZUCCHINI;
					}
					else{
						*peControler = FRDLCD_UNKNOWN;
					}
				}
				break;
			case 0x02:	/* YellowTail */
				*peControler = FRDLCD_YELLOWTAIL;	break;
			case 0x03:	/* Zucchini_P */
				*peControler = FRDLCD_ZUCCHINI_P;	break;
			case 0x04:	/* Arugula */
				*peControler = FRDLCD_ARUGULA;		break;
			case 0x05:	/* Plaice */
				*peControler = FRDLCD_PLAICE;		break;
			case 0x07:	/* Guava */
			case 0x08:	/* Turnip */							//sakata20111220
				*peControler = FRDLCD_GUAVA;		break;
			default:
				*peControler = FRDLCD_UNKNOWN;		break;
		}
	}
	return eResult;
}


/*!
********************************************************************************	//Global20120507
** @brief	ライブラリバージョンを返すAPI											//Global20120507
** @param	dFrdLcd2Lsi_e	バージョンを格納するポインタ(型定義: uint8*)			//Global20120507
** @retval	S_SUCCESS 正常終了														//Global20120507
** @retval	other エラーコード														//Global20120507
** @par コメント																	//Global20120507
** @note																			//Global20120507
*******************************************************************************/	//Global20120507
dResult_e eFrdLcdGetLibVer( uint8* pucLibVer )										//Global20120507>>>>>>>>>>>
{
	dResult_e eResult = S_SUCCESS;
	int version_size = sizeof(sharp_version);
	int version_i;

	for( version_i=0; version_i<version_size; version_i++)
	{
		pucLibVer[version_i] = sharp_version[version_i];
	}
#ifdef SH_DEBUG
	printf("eFrdLcdGetLibVer = %s\n", pucLibVer );
#endif //SH_DEBUG

	return eResult;
}																					//Global20120507<<<<<<<<<<<


/* end of file */
