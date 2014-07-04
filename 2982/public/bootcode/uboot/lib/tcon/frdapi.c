/**
 * @file frdapi.c
 *
 * @brief FRC����
 *
 * Copyright (c) 2008 SHARP CORPORATION
 *
 * @author 
 */

/* NOTE : ���Υե�����ϡ��ġ���FRC�ѥإå��ե�����ؤ�
          Wrapper�Ȥ��Ƥ��ޤ���
          �ºݤε��Ҥ��ɲä�����ϡ����̤Υإå��ե�������ɵ�����������
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

#include <tcon/frdlcdapi.h>		/* ��ܥ���ȥ�����������ɬ�� */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//#include "frdlcdzyapi.h"/* Zucchini��YellowTail�ѥإå��ե����� */
#endif //TURNKEY1

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef FRASER_VALID

//?#include "frdfrapi.h"	/* Fraser�ѥإå��ե����� */
#endif //TURNKEY1

#endif

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
#ifdef YELLOWTAIL_VALID
//?#include "frdtmapi.h"	/* YellowTail�ѥإå��ե����� */
#endif //TURNKEY1

#endif


#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
//?#include "frdicecapi.h"	/* Icec�ѥإå��ե����� */
//?#include "frdarapi.h"	/* Arugula�ѥإå��ե����� */
//?#include "frdlcdarapi.h"/* Arugula��(T-CON��)�إå��ե����� */
#endif //TURNKEY1


#include <tcon/frdplapi.h>	/* Plaice�ѥإå��ե����� */
#include <tcon/frdguapi.h>	/* Guava�ѥإå��ե����� */
#include <tcon/frdlcdguapi.h>	/* Guava��VCOMĴ����API(eFrdLcdGuSetFreeRun)�������ۣ��ʰ�Warning��ȯ�����Ƥ��롣��äơ�Warning��ä��٤ˡ�include */	//sakata20110920

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

/* ���� */
extern dFrdLcdControler_e eFrdLcdControler;

/* ���� */

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
static dFrc_TestPat_e eCurrentTestPtn = FRC_TESTPAT_OFF;	/* Fraser���� */
#endif //TURNKEY1

static uint8 ucCurrentTemp = 4;		/* ����LCD¦�β�������ˤ�빹�����θ�������ˤ���Ĥ����ä�����
									���ѿ���eFrdSetPF()��ɬ�פ����٤ʤΤǡ�static��α��� */

/* **
 * ** func
 * **/

/*!
********************************************************************************
** @brief	���������API (FRC¦)
** @param	fLrDrive		: �ѥͥ��ư����������, TRUE = ��¦��ư, FALSE = ξ¦��ư (�����: flag)
** @param	eInputFreq		: ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
			/* ��¦�Τ� */			
			eResult |= eFrdPlInit(eInputFreq);
			break;
		case FRDLCD_GUAVA:
			/* ��¦�Τ� */
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
** @brief	������Х�����API (FRC¦)
** @param	fPipelineEnable	: ������Х�(�ѥ��ץ饤��)����, 
**							TRUE = ON, FALSE = OFF(������Х�����) (�����: flag)
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
//			eResult |= eFrdArStandby(fPipelineEnable);/* Arugula�Ǥϡ�UPDATE OFF���Ȥ��ʤ��Τ� */
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
			//VCOM�и�Ĵ�������к�	�ޥ����󥽥ե��ѹ�Ϣ�����б�(No.YKIC-003)	//sakata20110627
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
** @brief	��®�⡼������API
** @param	fFrcEnable	: ��®�⡼������, TRUE = ON, FALSE = OFF (�����: flag)
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
** @brief	��®�⡼�ɾ��ּ���API
** @param	pfFrcStatus	: ��®�⡼�ɾ��֤򼨤��ե饰 (�����: flag *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			������˥塼"FRC���ּ������˻��Ѥ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
			/* YellowTail�ˤϡ�FRC(3rdMethod)�ξ��֤��������ѤϤʤ�
			  �����Ǥϡ�3rdMethod ON/OFF��ǧ���Ͼ��ON�������ξ��ȴ������OFF */
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
** @brief	����üOFF����API
** @param	ptEdgeFrame	: �ΰ���� (�����: dFrdFrame *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	��®�⡼�ɥޥ�������API
** @param	ucMaskNo	: �ޥ����ֹ���� [1-8] (�����: uint8)
** @param	fMaskEnable	: �ޥ�������, TRUE = ON, FALSE = OFF (�����: flag)
** @param	ptMaskFrame	: �ΰ���� (�����: dFrdFrame *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Yellowtail��Pliace�ξ�硢4�ս�ޤǤ����ޥ����Ǥ��ޤ���\n
**			YellowTail��Plaice(3rdMethod)�Ǥ���þ��ȯ�����ʤ��Τǡ�
**			����Ū�˥ޥ�������ɬ�פϤ���ޤ���\n
**			YellowTail, Pliace�Ǥϡ���®Ⱦ��������ǥޥ���No4����Ѥ��Ƥ���Τǡ�
**			No4�϶��ϻ��Ѥ��ʤ��Ǥ���������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
**			Guava:				����\n
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
** @brief	�ƥ��ȥѥ���������API (FRC¦)
** @param	eTestPtn		: ɽ���⡼������ (�����: dFrdTestPtn_e)
** @param	pvAdjTestPtn	: �ƥ��ȥѥ�����ܺ����� (�����: void *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�ƥǥХ����ˤ�äơ��ܺ������ѹ�¤�Τη����ۤʤ�ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ϼ��ȿ��������API
** @param	eInputFreq	: ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
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
** @brief	�ե꡼�������API (FRC¦)
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
** @brief	FRC���ơ������ǡ�������API
** @param	pvFrcStatusDat	: FRC���ơ������ǡ��� (�����: void *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�ƥǥХ����ˤ�äơ����ơ������ǡ��������ۤʤ�ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����Ϣ³�����API (FRC¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDatas	: ����ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�쥸��������256�ĤޤǤ��������ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����Ϣ³�ɹ���API (FRC¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDatas	: �ɹ��ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�쥸��������256�ĤޤǤ����ɹ���ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
** @brief	���ѥ쥸����ñ������API (FRC¦)
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
** @brief	���ѥ쥸����ñ���ɹ���API (FRC¦)
** @param	usAddr	: ���ɥ쥹����			(�����: uint16)
** @param	pusVal	: �ɹ����ͤΥݥ���	(�����: uint16)
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
** @brief	PF����������API
** @param	ucTemp	: ���ٻ���[0-7] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Plaice�Ǥ�Gain�ǤϤʤ�3rdMethod��ON/OFF�ˤʤ�ޤ�
**			(�ɥ饤�����SetMode��Ϣư���Ƥ��ޤ�)��
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
	
	/* ���� */
	ucCurrentTemp = ucTemp;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	�����������API
** @param	fLineEnable		:����������ꡥON��TRUE��OFF��FALSE (�����: flag)
** @param	eLineColor		:����ΰ�ο����� (�����: dFrdLineColor_e)
** @param	ptLineArea		:�ΰ���� (�����: dFrdFrame_t)
**							�ѹ����ʤ����ϡ��ݥ��󥿤�NULL���ꤹ�롣\n
**							X���ϰϡ�0��1919, Y���ϰϡ�0��1079���ޤ�X��0, Y��0�ξ�硢W���ϰϡ� 0��1920, H���ϰϡ�0��1080
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
** @brief	��®Ⱦ��������API
** @param	eModeHalf	: ��®Ⱦ�������� (�����: dFrdModeHalf_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			��API�����ꤹ����ϡ������� eFrdSetMode( TRUE ) �ˤ��Ƥ���������\n
**			YellowTail, Pliace�ξ�硢�ޥ���No4�ˤ�Ⱦ���̤�ޥ������Ƥ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			����\n
**			Arugula:			����\n
**			Plaice:				����\n
**			Guava:				����\n
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
			/* QS half������뤫��... */
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
** @brief	�ݥ��ȥե��륿����API
** @param	fPFEnable	: �ݥ��ȥե��륿����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			������˥塼"POSTFILTER ON/OFF"���Τ߻��Ѥ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	�ݥ��ȥե��륿���ּ���API
** @param	pfPFStatus	: �ݥ��ȥե��륿���֤򼨤��ե饰 (�����: flag *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			������˥塼"POSTFILTER ON/OFF"���Τ߻��Ѥ��ޤ���
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	�����ٵ���������API
** @param	fCtaEnable	: �����ٵ��������� TRUE = ON, FALSE = OFF (�����: flag)
** @param	ptCtPoint	: �����ٵ�����������֥ݥ��� (�����: dFrdCtPoint_t*)
**						�ѹ����ʤ�����NULL���ꡣ
** @param	ptCtVal		: ����������������ݥ��� (�����: dFrdCtVal_t**)
**						�ѹ����ʤ�����NULL���ꡣ
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** 			AV�ݥ������, �����������ǥۥ磻�ȥХ��Ĵ����, �����٥��ե��å���
**			���ѹ�������ϡ���API�򥳡��뤷�Ƥ���������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	ȩ������ȥ���API
** @param	sHue		: ���� �ϰ�: -2048��+2048 (�����: int16)
** @param	sSat		: ���� �ϰ�: 0��+4096 (�����: int16)
** @param	sVal		: ���� �ϰ�: 0��+4096 (�����: int16)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** 			��API�򥳡��뤹����ϡ������˿����ٵ���������API
**			eFrdSetCtaParam()�򥳡��뤷�Ƥ����Ƥ���������
** @note
**			Fraser+Zucchini:	����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	DDR2 ���������å�API
** @param	pusErrInfo :	���ɥ쥹��³����, �ǡ����Х���³�����ˤ�
**							����줿��̤��Ǽ��������Υݥ��� (�����: uint16)
** @retval	dFrdDdr2Res_e�����
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				̤����\n
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

#ifdef TURNKEY2	//Warning��ä��٤ˤ�����#ifdef���ɲ�	//sakata20110920
	return eResult = FRD_DDR2_RES1;						//sakata20110920
#else //TURNKEY2											//sakata20110920
	return eResult;										//sakata20110920
#endif //TURNKEY2											//sakata20110920
}


/*!
********************************************************************************
** @brief	Film�⡼������API
** @param	eMode	: Film�⡼������ (�����: dFrdMode_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	Qs�⡼������API
** @param	eMode	: Qs�⡼������ (�����: dFrdMode_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	�Ż߲�ɽ��API
** @param	fStill : �Ż߲�ɽ�����ꡥON��TRUE��OFF��FALSE (�����: flag)
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
** @brief	���ٻ���API
** @param	ucTemp : ���ٻ��� [0-255] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			1����ˡ������ǥХ����Υ����ߥ����ˤ�������0-255���ͤ�
**			��API���Ϥ��Ƥ���������\n
**			��API����Ѥ���С��ҥ��ƥꥷ�������䡢����API�򥳡��뤹��ɬ��
**			�Ϥʤ��ʤ�ޤ���\n
**			- eFrdSetGain()\n
**			- eFrdLcdSetSbr()\n
**			- eFrdLcdSetQsTemp()\n
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
*******************************************************************************/
dResult_e eFrdSetTemp( uint8 ucTemp )
{
	dResult_e eResult = S_SUCCESS;
	switch(eFrdLcdControler){
		case FRDLCD_PLAICE:
			eResult = eFrdPlSetTemp(ucTemp);
			break;

//GUAVA��QS�ڤ��ؤ���ư��Ƥ��ʤ��ä��Τǡ�TURNKEY2��ǥ����ɲ�
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
** @brief	���ϲ����ͥ���ץ���API
** @param	ptInputRgb[1920][1080] : ���ϲ����ͳ�Ǽ���� (�����: dFrdPixelDat_t)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			��API�ˤϡ�ɬ��[1920][1080]�����ǿ����Ѱդ��Ƥ���������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
					/* 10->8bit���Ѵ� */
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
** @brief	���� FRC ON/OFF ����API
** @param	eModeChk		: ���� FRC ON/OFF������	(�����: dFrdModeChk_e)
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
** @brief	����������� API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			�����μ��ȿ�, ����, FRC, QS �����ͤ����
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				����\n
**			Guava:				̤����\n
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
** @brief	3�ΰ襹���������� API
** @param	fArea3En		:3�ΰ����ꡥON��TRUE��OFF��FALSE (�����: flag)
** @param	ptArea3Scrl		:�ƥ��ȥѥ�����ܺ����깽¤�ΤΥݥ��� (�����: dFrdArea3Scrl_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	������� API
** @param	eInputFreq	: ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	�����ȿ����� API
** @param	eInputFreq	: ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	���� �ƥ��ȥѥ�����ɽ�� API
** @param	ePtnSel	:�ƥ��ȥѥ�������̻��� (�����: dFrdPtnSel_e)
** @param	ucPtn	:�ƥ��ȥѥ������ֹ���� (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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
** @brief	TypvGain���� API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			eFrdLcdSetLvl()���Ѥ�����ϡ���API�Υ����뤬���פǤ���
** @note	1����˥����뤷�Ƥ���������
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			̤����\n
**			Plaice:				̤����\n
**			Guava:				����\n
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



//������������������������������������������������������������������������������������������������������������������������������
#ifdef TURNKEY1 //���Ĥδ֤ˤ��������Ƥ���APIã
				//���Ū�Ǥ�饤�֥�꤬�Ǥ���褦�˽���
/*!
********************************************************************************
** @brief	DemoMode���� API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			���ꤷ����Demo����
** @note
**			Fraser+Zucchini:	̤����\n
**			Yellowtail:			̤����\n
**			Arugula:			����\n
**			Plaice:				����\n
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
