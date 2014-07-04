#ifndef FRDPLAPI_H
#define FRDPLAPI_H

/**
 * @file frdplapi.h
 *
 * @brief PlaiceFRC����
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
/* ����� */
/**********/

/**
 * @brief ��ʿ3ʬ�䥹������®������������
 */
typedef enum{
	FRDPL_AREA3_RIGHT,			/*!< ������ */
	FRDPL_AREA3_LEFT,			/*!< ������ */
	FRDPL_AREA3_STOP,			/*!< ��� */
	FRDPL_AREA3_PROHIBIT,		/*!< �ػ� */
} dFrdPlArea3Mov_e;
#define FRDPL_AREA3_MOV_NUMMAX (FRDPL_AREA3_PROHIBITION+1)


/**
 * @brief ���Բ���������������
 */
typedef enum{
	FRDPL_SVMODE_H,		/*!< ���⡼�� */
	FRDPL_SVMODE_M,		/*!< ���⡼�� */
	FRDPL_SVMODE_L,		/*!< ��⡼�� */
	FRDPL_SVMODE_DEMO,	/*!< ���Բ� �ǥ��� */
	FRDPL_SVMODE_OFF,	/*!< ���� */
} dFrdPlSvMode_e;
#define FRDPL_SV_MODE_NUMMAX (FRDPL_SVMODE_HIGH+1)


/**
 * @brief	�ǥ�⡼������������
 */
typedef enum{
	FRDPL_DEMO_OFF,		/*!< �ǥ�⡼��OFF */
	FRDPL_DEMO_NORMAL,	/*!< �̾�����ǥ�(����ʬ�䡢��������ʤ�) */
	FRDPL_DEMO_SCROLL,	/*!< �Ż߲襹������ǥ�(����ʬ��ܥ�������) */
}dFrdPlDemoMode_e;
#define FRDPL_DEMO_NUMMAX (FRDPL_DEMO_SCROLL+1)


/**********/
/* ��¤�� */
/**********/

/**
 * @brief ��ʿ3ʬ���ư�������깽¤�����
 */
typedef struct {
	dFrdPlArea3Mov_e	eArea1Mov;	/*!< �ΰ�1�ΰ�ư���� */
	dFrdPlArea3Mov_e	eArea2Mov;	/*!< �ΰ�2�ΰ�ư���� */
	dFrdPlArea3Mov_e	eArea3Mov;	/*!< �ΰ�3�ΰ�ư���� */
} dFrdPlArea3Mov_t;


/**
 * @brief ��ʿ3ʬ�䥹������®�����깽¤�����
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< �ΰ�1��������®�� (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< �ΰ�2��������®�� (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< �ΰ�3��������®�� (0x00-0x3F) */
} dFrdPlArea3Speed_t;


/**
 * @brief ��ʿ3ʬ�����깽¤�����
 */
typedef struct {
	uint16	usArea2Y;		/*!< ��ʿ3ʬ�䡦�ΰ�2���ϥ饤���ֹ� (0x00-0x437) */
	uint16	usArea3Y;		/*!< ��ʿ3ʬ�䡦�ΰ�3���ϥ饤���ֹ� (0x00-0x437) */
	dFrdPlArea3Speed_t	*ptArea3Speed;	/*!< ��ʿ3ʬ�䥹������®������ */
	dFrdPlArea3Mov_t	*ptArea3Mov;	/*!< ��ʿ3ʬ���ư�������� */
} dFrdPlArea3TestPtn_t;


/**
 * @brief ư��ѥ������ư����/®�����깽¤����� (ʬ�䥹����������)
 */
typedef struct {
	flag	fQsMovLR;		/*!< ��¢�ѥ����ư���� (TRUE:��, FALSE:��) */
	uint8	ucQsMovSpeed;	/*!< ��¢�ѥ����ư®�� (0x00-0x3F)*/
	uint8	ucHScroll;		/*!< ���ϲ�����������®�� (0x00-0x3F)*/
} dFrdPlMovTestPtn_t;


/**
 * @brief �ƥ��ȥѥ�����ܺ����깽¤�����
 */
typedef struct {
	dFrdPlArea3TestPtn_t	*ptArea3TestPtn;	/*!< ��ʿ3ʬ������ */
	dFrdPlMovTestPtn_t		*ptMovTestPtn;		/*!< ư��ѥ������ư����/®������ */
} dFrdPlAdjTestPtn_t;


/**
 * @brief	���������͹�¤����� (�ܺ�����˴ؤ��븽���������ѿ��򼨤�)
 */
typedef struct
{
	dFrdPlAdjTestPtn_t	tCurrentAdjTestPtn;	/*!< �ƥ��ȥѥ�����ܺ�������֤򼨤� */
} dFrdPlInternalDat_t;


/**
 * @brief ���ϲ����ͥ���ץ������깽¤����� (10bit)
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
