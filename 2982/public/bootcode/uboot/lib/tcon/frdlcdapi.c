/**
 * @file frdlcdapi.c
 *
 * @brief LCD����
 *
 * Copyright (c) 2008 SHARP CORPORATION
 *
 * @author 
 */

/* NOTE : ���Υե�����ϡ��ġ���FRC�ѥإå��ե�����ؤ�
          Wrapper�Ȥ��Ƥ��ޤ���
          �ºݤε��Ҥ��ɲä�����ϡ����̤Υإå��ե�������ɵ�����������
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
//?#include "frdlcdzyapi.h"	/* Zucchini��YellowTail�ѥإå��ե����� */
//?#include "frdlcdarapi.h"	/* Arugula�ѥإå��ե����� */
#endif //TURNKEY1

#include <tcon/frdlcdplapi.h>	/* Plaice�ѥإå��ե�����(TCON¦) */
#include <tcon/frdplapi.h>		/* Plaice�ѥإå��ե�����(FRC¦) */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "frdfpgaapi.h"		/* FPGA(Begonia)�ѥإå��ե����� */
#endif //TURNKEY1

#include <tcon/frdguapi.h>		/* Guava�ѥإå��ե�����(FRC¦) */
#include <tcon/frdlcdguapi.h>	/* Guava�ѥإå��ե�����(TCON¦) */

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

/* �����Х��ѿ� */
dFrdLcdControler_e eFrdLcdControler = FRDLCD_PLAICE;	/* default */

//sakata20111013 static dFrdLcdPnlSize_e eFrdLcdPnlSize = FRDLCD_PNL_32;
//static uint8 aucFrdLcdRevInfo[FRDLCD_REVISION_DATA_MAX];
/* **
 * ** func
 * **/

static dResult_e eLcdGetLsiInfo(dFrdLcdControler_e *peControler);

/*!
********************************************************************************
** @brief	���ѥ쥸����Ϣ³�����API (LCD¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDatas	: ����ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����Ϣ³�ɹ���API (LCD¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDatas	: �ɹ��ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����ñ������API (LCD¦)
** @param	usAddr	: ���ɥ쥹����	(�����: uint16)
** @param	usVal	: �������	(�����: uint16)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����ñ���ɹ���API (LCD¦)
** @param	usAddr	: ���ɥ쥹����	(�����: uint16)
** @param	pusVal	: �ɹ�����	(�����: uint16 *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	�ѥͥ륵����������API
** @param	ePnlSize	: �ѥͥ륵��������(�����: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	ɬ�� eFrdLcdGetLsiInfo �����˸Ƥ֤���(��ӥ�����ͤȤ��Ƥϡ�����ʳ��ϥ������ɬ�פʤ�)
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
** @brief	�ѥͥ륵���������ǧ��API
** @param	pePnlSize	: �ѥͥ륵�������� (�����: dFrdLcdPnlSize_e *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
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
** @brief	T-con���LSIȽ��API
** @retval	FRDLCD_ZUCCHINI or FRDLCD_YELLOWTAIL or FRDLCD_ARUGULA or FRDLCD_PLAICE or FRDLCD_GUAVA
** @par ������
**			�ǽ�˥����뤹��T-conLSI�ɥ饤��API�Ǥ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n;
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
	/* 60���ξ��Τ�I2C������������wait�ɲá��ͤκ���� tI2CT > 750ms �Ȥ����ϡ�������
	   �����Ȥʤ� PE�������� ���� I2C�������졼������� �ޤ�140ms����Τǡ�750-140 = 610ms  */

		if( ePnlSize == FRDLCD_PNL_60 ) MDrv_Timer_Delayms( 610 );

#else
	/* Manager������������������Ϳ�����ʤ������θ����ȡ����wait�������Τ�����
	   �� �Ȥꤢ�������wait 610ms�Ȥ��ޤ�����ư���֤ؤαƶ��ˤĤ�����դ���ɬ�פ����롣2009.07.16 */

		MDrv_Timer_Delayms( 610 );
	
#endif
#endif
#endif //TURNKEY1

	eFrdLcdControler = FRDLCD_GUAVA; /* �����ǽ�������ʤ��ȡ���öUNKNOWN��Ƚ�̤����Ȱʹ������Ǥ��ʤ� */
	
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
	/* �ǽ�Ū�˼��Ԥξ� */
		eControler = FRDLCD_UNKNOWN;
	}
	
	eFrdLcdControler = eControler;
	
	return eControler;
}


/*!
********************************************************************************
** @brief	EEPROM�������ｪλ�����å�API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
	/* 60���Τߡ�����FPGA(Begonia)�ε�ư��λ�Ԥ���ɬ�� */
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
** @brief	���������API(LCD¦)
** @param	fLrDrive	: �ѥͥ��ư����������, TRUE = ��¦��ư, FALSE = ξ¦��ư (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
			eResult |= eFrdLcdPlInit();	/* ��¦�Τ� */
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdLcdGuInit();	/* ��¦�Τ� */
			break;
		default:
			return S_FAILURE;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	����ȿž����API
** @param	eTrnOvr : ����ȿž����(�����: dFrdLcdTrnOvr_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	������������API
** @param	fOutEnable	: ����(ON/OFF)����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Arugula������LSI�Ǥϡ�����OFF���뤳�ȤϤǤ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
	/* 60���ξ�� */
		eFrdFpgaSetOutput( fOutEnable );
	}
#endif
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD�ƥ��ȥѥ���������API
** @param	eTestPtn : �ƥ��ȥѥ������ֹ�(�����: dFrdLcdTestPtn_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	LCD���������ѥѥ���������API
** @param	ucAgingPtn : �������󥰥ѥ������ֹ� [0x00-0x21] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Zucchini��0x1F�ʹߤΥѥ������ɽ������ޤ���
**			Arugula��0x20�ʹߤΥѥ������ɽ������ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	LCDɾ���ѥѥ���������API
** @param	ucEvaPtn : �������ѥ������ֹ� [0x00-0x12] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Zucchini, Arugula�Ǥϡ�0x12�Υѥ������ɽ������ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	QS ON/OFF����API
** @param	fQsEnable	: QS ON/OFF����, TRUE = ON, FALSE = OFF (�����: flag)
** @param	fYuv 		: ���Ͽ������, TRUE = YUV����, FALSE = Y���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			YUV/Y���θ����ɬ�פ�����Τ�Yellowtail��Plaice�Ǥ�������¾��LSI�ξ�硢
**			����fYuv���ͤ�Ŭ���ǹ����ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	QSȾ����ON/OFF����API
** @param	fLonRoff : Ⱦ����ON/OFF����, TRUE = ��ON��OFF, FALSE = ��OFF��ON (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	QS���ȿ�����API
** @param	eInputFreq : ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	QS��������API
** @param	ucTemp : ���ٻ��� [0(�㲹)-7(�ⲹ)] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	SBR����API
** @param	ucTemp : ���ٻ��� [0(�㲹)-7(�ⲹ)] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				���� [������ eFrdSetTemp() �����뤿�ᥳ�����ɬ�פʤ�]\n
**			Guava:				���� [������ eFrdSetTemp() �����뤿�ᥳ�����ɬ�פʤ�]\n
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
	/* 60���ξ�� */
		switch(eFrdLcdControler){
			case FRDLCD_ARUGULA:
				eResult |= eFrdFpgaSetTemp( ucTemp );	/* Begonia�ˤ� */
				break;
			case FRDLCD_PLAICE:
				eResult |= eFrdLcdPlSetSbr(ucTemp);		/* Plaice�ˤ� */
				break;
			case FRDLCD_GUAVA:
				eResult |= eFrdLcdGuSetSbr(ucTemp);		/* Guava�ˤ� */
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
** @brief	Revision����API
** @param	pucRevInfo : Revision�ǡ������Ǽ��������Υݥ���(�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	(����)Revision����API
** @param	pucRevInfo : Revision�ǡ������Ǽ��������Υݥ���(�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	ROM Revision ɽ����API
** @param	pcRevInfo : Revision�ǡ���ɽ����ʸ������Ǽ��������Υݥ���(�����: int8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������ ����Υ�������ɬ��32�Х��Ȥ���ݤ��뤳�ȡ�
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	ROM�ǡ���Ϣ³�����API
** @param	uiAddr		: ROM������襢�ɥ쥹			(�����: uint32)
** @param	uiLength	: ����ߥǡ���Ĺ				(�����: uint32)
** @param	pucDatas	: ����ߥǡ�������Ƭ�ݥ���	(�����: uint8*)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
**			Guava:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
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
** @brief	ROM�ǡ���Ϣ³�ɹ���API
** @param	uiAddr		: ROM�ɹ����襢�ɥ쥹			(�����: uint32)
** @param	uiLength	: �ɹ��ߥǡ���Ĺ				(�����: uint32)
** @param	pucDatas	: �ɹ��ߥǡ�������Ƭ�ݥ���	(�����: uint8*)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
**			Guava:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
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
** @brief	ROM�ǡ����õ�API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
**			Guava:				���� [������ eFrdLcdSetVerUp() �����뤿�ᥳ�����ɬ�פʤ�]\n
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
** @brief	��ľ�ǥ���� ON/OFF������API
** @param	eDecontEnable	: �ǥ���� ON/OFF���� (�����: dFrdLcdDecont_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note    Arugula�Τ�
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
** @brief	ROM�С�����󥢥å�API
** @param	pucDats	: ROM�ǡ�������Ƭ�ݥ��� (�����: uint8 *)
** @param	fVerify	: �٥�ե�������, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���̽�����API
** @param	ePnlSize	: �ѥͥ륵��������(�����: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			VerUp�����β��Ф���������δؿ��Ǥ���\n
**			�б�����ѥͥ륵��������Υǡ�������ɤ��ޤ���\n
**			��API��ǡ�������API�������뤵��Ƥ��ޤ���
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	�ե꡼�������API (LCD¦)
** @param	fFreeRunEnable	: �ե꡼�������, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ϲ��ǥǡ���(RGB��)������API
** @param	x			: X��ɸ		(�����: uint16)
** @param	y			: Y��ɸ		(�����: uint16)
** @param	ptRgbColor	: RGB��		(�����: dFrdLcdRgb_t)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: PPDS�����ʤˤ�������ǥǡ�����������ޤ���
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				̤����\n
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
** @brief	�ƥ��ȥѥ�����(�٥�ɽ��)�����Ѵؿ�
** @param	ptColor : ������ (�����: dFrdLcdTpColor_t)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: 
**			LCDC¦ɾ���ѥƥ��ȥѥ������"0x03 : �٥�ɽ��"������Ǥ���\n
**			ptColor = NULL �Ȥ��ƥ����뤹����̾�⡼�ɤ����ޤ���\n
**			�岼���ٺ�Ĵ�����˻��Ѥ���뤳�Ȥ����ꤷ����ΤǤ���\n
**			��λ����NULL�Ȥ��ƥ����뤷�Ƥ���������
** @note    
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				̤����\n
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
			/* ���⤷�ޤ��� */
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	�ѥͥ�岼���ٺ�Ĵ����API(��¦)
** @param	iLevel : Ĵ���� (�����: int32)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: ����Ĵ��(��¦)��DAC�쥸������Ĵ���ˤ��Ԥ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				̤����\n
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
** @brief	�ѥͥ�岼���ٺ�Ĵ���ͼ�����API(��¦)
** @param	piLevel : Ĵ���� (�����: int32)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: ����Ĵ����(��¦)���֤��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				̤����\n
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
** @brief	���顼��������API
** @param	ptError : Ĵ���� (�����: dFrdLcdError_t)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: 
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
********************************************************************************/
dResult_e eFrdLcdGetErrInfo( dFrdLcdError_t *ptError )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	if( ptError == NULL ) return S_FAILURE;

	ptError->ucErrCode = 0;/* ����� */
	
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
** @brief	�ޥ˥奢��������ѥ�����¹�API
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: 
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
********************************************************************************/
dResult_e eFrdLcdAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	switch(eFrdLcdControler){
		case FRDLCD_ARUGULA:
			eResult |= eFrdArAllManualLoad();	/* FRC¦ */
			eResult |= eFrdLcdArAllManualLoad();/* LCDC¦ */
			break;
		case FRDLCD_PLAICE:
			eResult |= eFrdPlAllManualLoad();	/* FRC¦ */
			eResult |= eFrdLcdPlAllManualLoad();/* LCDC¦ */
			break;
		case FRDLCD_GUAVA:
			eResult |= eFrdGuAllManualLoad();	/* FRC¦ */
			eResult |= eFrdLcdGuAllManualLoad();/* LCDC¦ */
			break;
		default:
			return S_FAILURE;
	}
#endif //TURNKEY1
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD�������󥰥ѥ���������API (FR¦)
** @param	ucFrAgingPtn : �������󥰥ѥ������ֹ� [0x00-0x21] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	LCDɾ���ѥѥ���������API (FR¦)
** @param	ucFrEvaPtn : ɾ���ѥѥ������ֹ� [0x00-0x12] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	Unveil ON/OFF������API
** @param	fUvlEn : Unveil ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	Unveil ����������API
** @param	ucUvlMode : Unveil �������� [0x0(��)-0xF(��)] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�ƶ��٤˱���������Ϣư������Υѥ�᡼������MNL���ޤ���
**
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	��������� ON/OFF������API
** @param	fBdEn : ��������� ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			���졼��������˸�����Yellow band�㸺�Ǥ���
**
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	�Υ������������� �⡼��������API
** @param	eNrMode : �Υ������������� ON/OFF���� (�����: dFrdLcdNrMode_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�����������åȤʤɡ�����ΰ��������������ΥΥ�����ʿ�경���ޤ���
**			����ʤɤΥǥ�������ƥ�ӤǤϻ��Ѥ��ʤ��Ǥ���������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	�Υ������������� �ޥ���������API
** @param	ucMaskNo	: �ޥ����ֹ���� [1-4] (�����: uint8)
** @param	fMaskEn	: �ޥ�������, TRUE = ON, FALSE = OFF (�����: flag)
** @param	ptMaskFrame	: �ΰ���� (�����: dFrdFrame *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	PCC ����ON/OFF������API
** @param	fPccEn : PCC ����ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	PCC ���ΰ��ON/OFF������API
** @param	ucColNo		: �ΰ��ֹ���� [1-6] (�����: uint8)
** @param	fColEn		: �����ΰ��ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�����ΰ�ε���,����,�����ON/OFF���ޤ���
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	�����ΰ�ε���,����,���� ON/OFF������API
** @param	ucColNo		: �ΰ��ֹ���� [1-6] (�����: uint8)
** @param	fBriEn		: �����ΰ�ε���ON/OFF���� (�����: flag)
** @param	fSatEn		: �����ΰ�κ���ON/OFF���� (�����: flag)
** @param	fHueEn		: �����ΰ�ο���ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	���� �ΰ�, ��°�����ΰ�������API
** @param	ucColNo		: �ΰ��ֹ���� [1-6] (�����: uint8)
** @param	eBsh		: ���ΰ���� (�����: dFrdLcdBsh_e)
** @param	usCenter	: �ΰ���濴����			[0x0000-0xFFFF] (�����: uint16)
** @param	usDelta		: �濴�����ΰ�ü�ޤǤε�Υ	[0x0000-0xFFFF] (�����: uint16)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�����˻����ΰ��ON���Ƥ���������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	���� �ΰ�, ��°���Υ�٥�������API
** @param	ucColNo		: �ΰ��ֹ���� [1-6] (�����: uint8)
** @param	eBsh		: ���ΰ���� (�����: dFrdLcdBsh_e)
** @param	usLvl		: Ĵ����٥� (�����: uint16), 
**						����,����:	[0x400(0��)��0x000(1��)��0x3FF(��2��)], 
**						����:		[0x400(-180��)��0x000(0��)��0x3FF(��180��)]
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�����˻����ΰ��ON���Ƥ���������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	Gamma LUT �񤭴�����API (Plaice�������к� 2009.06.29)
** @param	fChgEn		: �񴹤�ON/OFF (�����: falg)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
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
** @brief	DAC������API (VCOM������)
** @param	fMemEn : ���������� TRUE: ���꡼, FALSE: �쥸���� (�����: flag)
** @param	usDat  : VCOMĴ���ǡ��� (�����: uint16)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Guava:				����\n
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
** @brief	DAC��ǧ��API (VCOM������)
** @param	fMemEn : ���������� TRUE: ���꡼, FALSE: �쥸���� (�����: flag)
** @param	pusDat  : VCOMĴ���ǡ��� (�����: uint16 *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Guava:				����(��������˥��꤫��꡼��)\n
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
** @brief	���٥�٥�����API
** @param	ucLvl	: ���٥�٥�λ��� [0(�㲹)-7(�ⲹ)] (�����: uint8 *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
**			Guava:				����\n
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
** @brief	�ߥ塼������API
** @param	fMuteEnable	: �ߥ塼������, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
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
** @brief	VCOM�ѥѥ�����ɽ������API
** @param	fVcom : VCOMɽ�� ON/OFF����(�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
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


#define FRDLCD_ADDR_ON_BOARD_LSI_HANBETSU	0x6C3D /* SousaII/ZucchiniȽ���ѥ쥸�������ɥ쥹 */
#define FRDLCD_ADDR_ON_BOARD_LSI_DETECT		0x6CEF /* ����ȥ���������LSIȽ���ѥ쥸����(YellowTail�ʹ�)���ɥ쥹 */
static dResult_e eLcdGetLsiInfo(dFrdLcdControler_e *peControler)
{
	printf("In eLcdGetLsiInfo\r\n");
	uint16		usVal;
	dResult_e	eResult = S_SUCCESS;
	
	eResult = eFrdLcdRegR(FRDLCD_ADDR_ON_BOARD_LSI_DETECT, &usVal);/* Arugula�Ѥ������ɤ߹���API����� */
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
				eResult = eFrdLcdRegR(FRDLCD_ADDR_ON_BOARD_LSI_HANBETSU, &usVal);/* Arugula�Ѥ������ɤ߹���API����� */
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
** @brief	�饤�֥��С��������֤�API											//Global20120507
** @param	dFrdLcd2Lsi_e	�С��������Ǽ����ݥ���(�����: uint8*)			//Global20120507
** @retval	S_SUCCESS ���ｪλ														//Global20120507
** @retval	other ���顼������														//Global20120507
** @par ������																	//Global20120507
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
