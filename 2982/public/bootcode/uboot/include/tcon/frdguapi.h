#ifndef FRDGUAPI_H
#define FRDGUAPI_H

/**
 * @file frdguapi.h
 *
 * @brief GuavaFRC����
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
#include "frdapi.h"//�ʤ�.c¦�ǤޤȤ��include����Τˡ�guava����.c��.h��ξ����include���Ƥ���Τ�Err�ˤʤäƤ���
#endif //0			//��äơ�.h¦��include�Ϻ������
#endif //TURNKEY1


/* **
 * ** define
 * **/
/* RegAddr Offset */
#define GU_REGADDR_FRC	0x8000

/**********/
/* ����� */
/**********/

/**
 * @brief ��ʿ3ʬ�䥹������®������������
 */
typedef enum{
	FRDGU_AREA3_RIGHT,			/*!< ������ */
	FRDGU_AREA3_LEFT,			/*!< ������ */
	FRDGU_AREA3_STOP,			/*!< ��� */
	FRDGU_AREA3_PROHIBIT,		/*!< �ػ� */
} dFrdGuArea3Mov_e;
#define FRDGU_AREA3_MOV_NUMMAX (FRDGU_AREA3_PROHIBITION+1)


/**
 * @brief �ǥ�����⡼������¢�ѥ���⡼������������
 */
typedef enum{
	FRDGU_VIDEO_MODE,		/*!< video�⡼�� */
	FRDGU_22_MODE,			/*!< 22�⡼�� */
	FRDGU_32_MODE,			/*!< 32�⡼�� */
	FRDGU_PROHIBIT_MODE,	/*!< �ػ� */
} dFrdGuFilmMode_e;
#define FRDGU_FILM_MODE_NUMMAX (FRDGU_PROHIBIT_MODE+1)


/**
 * @brief ���Բ���������������
 */
typedef enum{
	FRDGU_SVMODE_H,		/*!< ���⡼�� */
	FRDGU_SVMODE_M,		/*!< ��⡼�� */
	FRDGU_SVMODE_L,		/*!< ��⡼�� */
	FRDGU_SVMODE_DEMO,	/*!< ���Բ� �ǥ��� */
	FRDGU_SVMODE_OFF,		/*!< ���� */
} dFrdGuSvMode_e;
#define FRDGU_SV_MODE_NUMMAX (FRDGU_SVMODE_HIGH+1)


/**
 * @brief �ǥ������Ĵ����������
 */
typedef enum{
	FRDGU_DJ_ADJ_H,		/*!< �ǥ������ */
	FRDGU_DJ_ADJ_M,		/*!< �ǥ������ */
	FRDGU_DJ_ADJ_L,		/*!< �ǥ������ */
	FRDGU_DJ_ADJ_55,	/*!< �ǥ����5-5 */
	FRDGU_DJ_ADJ_DEMO,	/*!< �ǥ���� �ǥ��� */
	FRDGU_DJ_ADJ_OFF,	/*!< �ǥ����OFF */
}dFrdGuDjAdj_e;
#define FRDGU_DJ_ADJ_NUMMAX (FRDGU_DJ_ADJ_OFF+1)


#if TURNKEY1	//Plaice��Ʊ�ͤ�API�ˤ��뤿��ˡ�Plaice��Ʊ�ͤ���������
/**
 * @brief	�ǥ�⡼������������
 */
typedef enum{
	FRDGU_DEMO_OFF,		/*!< �ǥ�⡼��OFF */
	FRDGU_DEMO_NORMAL,	/*!< �̾�����ǥ�(����ʬ�䡢��������ʤ�) */
}dFrdGuDemoMode_e;
#define FRDGU_DEMO_NUMMAX (FRDGU_DEMO_NORMAL+1)
#endif //TURNKEY1


/**********/
/* ��¤�� */
/**********/

/**
 * @brief ��ʿ3ʬ���ư�������깽¤�����
 */
typedef struct {
	dFrdGuArea3Mov_e	eArea1Mov;	/*!< �ΰ�1�ΰ�ư���� */
	dFrdGuArea3Mov_e	eArea2Mov;	/*!< �ΰ�2�ΰ�ư���� */
	dFrdGuArea3Mov_e	eArea3Mov;	/*!< �ΰ�3�ΰ�ư���� */
} dFrdGuArea3Mov_t;


/**
 * @brief ��ʿ3ʬ�䥹������®�����깽¤�����
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< �ΰ�1��������®�� (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< �ΰ�2��������®�� (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< �ΰ�3��������®�� (0x00-0x3F) */
} dFrdGuArea3Speed_t;


/**
 * @brief ��ʿ3ʬ�����깽¤�����
 */
typedef struct {
	uint16	usArea2Y;		/*!< ��ʿ3ʬ�䡦�ΰ�2���ϥ饤���ֹ� (0x00-0x437) */
	uint16	usArea3Y;		/*!< ��ʿ3ʬ�䡦�ΰ�3���ϥ饤���ֹ� (0x00-0x437) */
	dFrdGuArea3Speed_t	*ptArea3Speed;	/*!< ��ʿ3ʬ�䥹������®������ */
	dFrdGuArea3Mov_t	*ptArea3Mov;	/*!< ��ʿ3ʬ���ư�������� */
} dFrdGuArea3TestPtn_t;


/**
 * @brief ư��ѥ������ư����/®�����깽¤����� (ʬ�䥹����������)
 */
typedef struct {
	flag	fQsMovLR;		/*!< ��¢�ѥ����ư���� (TRUE:��, FALSE:��) */
	uint8	ucQsMovSpeed;	/*!< ��¢�ѥ����ư®�� (0x00-0x3F)*/
	uint8	ucHScroll;		/*!< ���ϲ�����������®�� (0x00-0x3F)*/
} dFrdGuMovTestPtn_t;


/**
 * @brief �ƥ��ȥѥ�����debug���깽¤�����
 */
typedef struct {
	flag				fEnforce;	/*!< ������������ե饰 (TRUE:����3ʬ�䥹������, FALSE:�̾�ɽ��) */
	uint16				usBitMapY;	/*!< AQUOSɽ�����ϥ饤���ֹ� */
	dFrdGuFilmMode_e	eFilmMode;	/*!< �ǥ�����⡼������¢�ѥ���⡼�� */
} dFrdGuDebugTestPtn_t;


/**
 * @brief �ƥ��ȥѥ�����ܺ����깽¤�����
 */
typedef struct {
	dFrdGuArea3TestPtn_t	*ptArea3TestPtn;	/*!< ��ʿ3ʬ������ */
	dFrdGuMovTestPtn_t		*ptMovTestPtn;		/*!< ư��ѥ������ư����/®������ */
	dFrdGuDebugTestPtn_t	*ptDebugTestPtn;	/*!< �ƥ��ȥѥ�����debug���� */
} dFrdGuAdjTestPtn_t;


/**
 * @brief ���ϲ��ǥǡ������깽¤����� (�ɹ��ߤΤ�)
 */
typedef struct
{
	uint16	usCvV0;	/*!< Red/V/Cr  �ϰ�: 0x00��0x3F */
	uint16	usCvV1;	/*!< Green/Y/Y �ϰ�: 0x00��0x3F */
	uint16	usCvV2;	/*!< Blue/U/Cb �ϰ�: 0x00��0x3F */
} dFrdGuPixelDat_t;


/**
 * @brief	���������͹�¤����� (�ܺ�����˴ؤ��븽���������ѿ��򼨤�)
 */
typedef struct
{
	dFrdGuAdjTestPtn_t	tCurrentAdjTestPtn;	/*!< �ƥ��ȥѥ�����ܺ�������֤򼨤� */
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
