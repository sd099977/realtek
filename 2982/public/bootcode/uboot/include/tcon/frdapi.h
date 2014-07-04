#ifndef FRDAPI_H
#define FRDAPI_H


#ifdef __cplusplus
extern "C"
{
#endif //cplusplus

/**
 * @file frdapi.h
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
 * @brief	FRC(3rdMethod)�ƥ��ȥѥ���������������
 */
typedef enum
{
	FRD_TESTPTN_OFF,				/*!< �ƥ��ȥѥ�����OFF(�̾�ɽ��) */
	FRD_TESTPTN_HRAMP,				/*!< ��ʿ���� */
	FRD_TESTPTN_VRAMP,				/*!< ��ľ���� */
	FRD_TESTPTN_CROSSHATCH,			/*!< �����ϥå� */
	FRD_TESTPTN_ALLOVER,			/*!< �٥� */
	FRD_TESTPTN_VSTRIPE_1LINE,		/*!< �ĥ��ȥ饤�ס�1�饤���*/
	FRD_TESTPTN_VSTRIPE_2LINE,		/*!< �ĥ��ȥ饤�ס�2�饤���*/
	FRD_TESTPTN_HSTRIPE_1LINE,		/*!< �����ȥ饤�ס�1�饤���*/
	FRD_TESTPTN_HSTRIPE_2LINE,		/*!< �����ȥ饤�ס�2�饤���*/
	FRD_TESTPTN_CHECK_1DOT,			/*!< 1�ɥå���Ļ */
	FRD_TESTPTN_CHECK_2DOT,			/*!< 2�ɥå���Ļ */
	FRD_TESTPTN_CHECK_RGB,			/*!< RGB��Ļ */
	FRD_TESTPTN_QS,					/*!< QS�ѥ����� */
	FRD_TESTPTN_MPRT,					/*!< MPRT�ѥ����� */
	FRD_TESTPTN_SCROLL,				/*!< ���ϲ��������������������FIFO_R_adrs���եȡ�*/ 
	FRD_TESTPTN_FLICKER_2H,			/*!< �ɥå�ȿž�ե�å��ѥ������2Hȿž�� */
	FRD_TESTPTN_FLICKER_1H,			/*!< �ɥå�ȿž�ե�å��ѥ������1Hȿž�� */
	FRD_TESTPTN_SHARP,				/*!< "SHARP AQUOS"ʸ���������� */
	FRD_TESTPTN_X,					/*!< �Хåƥ�ޡ��� */
	FRD_TESTPTN_HVRAMP_ALTERNATE,		/*!< ��ʿ����ľ���׸�� ��ʿ->��ľ (����¦�Τ�) */
	FRD_TESTPTN_VHRAMP_ALTERNATE,		/*!< ��ʿ����ľ���׸�� ��ľ->��ʿ (����¦�Τ�) */
	FRD_TESTPTN_ALLOVER_ALTERNATE,	/*!< �٥���� (����¦�Τ�) */
	/* �ʹ� Fraser(Zucchini)�Ǥ�ɽ������ʤ� */
	FRD_TESTPTN_SHARP2,				/*!< "SHARP AQUOS"ʸ����������2 (�طʲ��) */
	FRD_TESTPTN_AREA3,				/*!< ��ʿ3ʬ�䥹������ */
	FRD_TESTPTN_QS_BAR,				/*!< QS�С� (QS¬���ѥѥ�����) */
	FRD_TESTPTN_PF,					/*!< PF���̳�ǧ�ѥѥ����� */
	FRD_TESTPTN_3RD_METHOD,			/*!< 3rdMethod��Ĵlut��ǧ�ѥ����� */
} dFrdTestPtn_e;
#define FRD_TESTPTN_NUMMAX (FRD_TESTPTN_3RD_METHOD+1)

/**
 * @brief ���ϼ��ȿ�������
 */
typedef enum{
	FRD_INPUT_FREQ_48HZ,	/*!< 48Hz */
	FRD_INPUT_FREQ_50HZ,	/*!< 50Hz */
	FRD_INPUT_FREQ_60HZ,	/*!< 60Hz */
} dFrdInputFreq_e;
#define FRD_INPUT_FREQ_NUMMAX (FRD_INPUT_FREQ_60HZ+1)


/**
 * @brief	�����������
 */
typedef enum{
	FRD_LINE_COLOR_GRAY,	/*!< ���쥤 */
	FRD_LINE_COLOR_BLUE,	/*!< �֥롼 */
	FRD_LINE_COLOR_WHITE,	/*!< �ۥ磻�� */
	FRD_LINE_COLOR_BLACK,	/*!< �֥�å� */
	FRD_LINE_COLOR_US_WHITE,	/*!< �����ѥۥ磻�� */
}dFrdLineColor_e;
#define FRD_LINE_COLOR_NUMMAX (FRD_LINE_COLOR_BLACK+1)


/**
 * @brief	��®Ⱦ��������������
 */
typedef enum{
	FRD_MODE_HALF_NORMAL,		/*!< Ⱦ����ON/OFF�ʤ� */
	FRD_MODE_HALF_BOTTOM_ON,	/*!< ������ON+�����OFF */
	FRD_MODE_HALF_UP_ON,		/*!< �����ON+������OFF */
	FRD_MODE_HALF_RIGHT_ON,		/*!< ������ON+������OFF */
	FRD_MODE_HALF_LEFT_ON,		/*!< ������ON+������OFF */
}dFrdModeHalf_e;
#define FRD_MODE_HALF_NUMMAX (FRD_MODE_HALF_LEFT_ON+1)


/**
 * @brief	DDR2�����������������
 */
typedef enum{
	FRD_DDR2_RES1,		/*!< DDR2 CHECK OK (���ｪλ) */
	FRD_DDR2_RES2,		/*!< CONNECTION NG (���ɥ쥹��³����[A1], �ǡ����Х���³����[A2]) */
	FRD_DDR2_RES3,		/*!< DDR2 NG (DDR2�ǥХ����ΰ�����[B]) */
	FRD_DDR2_RES4,		/*!< OTHERS NG (�ǥХ�����������[C], Ƚ����ǽ[X]) */
}dFrdDdr2Res_e;
#define FRD_DDR2_RES_NUMMAX (FRD_DDR2_RES4+1)


/* 090223 ohashi */
/**
 * @brief	QS&Film�⡼������������
 */
typedef enum{
	FRD_MODE_OFF,		/*!< QS&Film�⡼�� OFF */
	FRD_MODE_STD,		/*!< QS&Film�⡼�� Standard */
	FRD_MODE_ADL,		/*!< QS&Film�⡼�� Advance (Low) */
	FRD_MODE_ADH,		/*!< QS&Film�⡼�� Advance (High) */
}dFrdMode_e;
#define FRD_MODE_NUMMAX (FRD_MODE_HIGH+1)


/**
 * @brief	���� FRC ON/OFF����������
 */
typedef enum{
	FRD_MODE_CHK_OFF,		/*!< ���� FRC OFF */
	FRD_MODE_CHK_MPRT,		/*!< ���� FRC ON: MPRT */
	FRD_MODE_CHK_AQUOS,		/*!< ���� FRC ON: QUOS */
}dFrdModeChk_e;
#define FRD_MODE_CHK_NUMMAX (FRD_MODE_CHK_AQUOS+1)


/**
 * @brief	���� �ƥ��ȥѥ�������̻���������
 */
typedef enum{
	FRD_PTN_FRC,		/*!< FRC�ѥ����� */
	FRD_PTN_AGING,		/*!< AGING�ѥ����� */
	FRD_PTN_EVA,		/*!< EVA(ɾ��)�ѥ����� */
}dFrdPtnSel_e;
#define FRD_PTN_NUMMAX (FRD_PTN_EVA+1)


/**********/
/* ��¤�� */
/**********/
/**
 * @brief �쥸�����ǡ����������ѹ�¤����� (FRC¦)
 */
typedef struct {
	uint16	usAddr;		/*!< ���ɥ쥹[16ibt] */
	uint16	usVal;		/*!< �ǡ���  [16ibt] */
} dFrdRegVar_t;


/**
 * @brief	�ΰ���깽¤�����
 */
typedef struct
{
	uint16	usXPos;		/*!< ����X��ɸ */
	uint16	usYPos;		/*!< ����Y��ɸ */
	uint16	usWidth;	/*!< �� */
	uint16	usHeight;	/*!< �⤵ */
} dFrdFrame_t;


/**
 * @brief	�����ٵ�����������ֹ�¤�����
 */
typedef struct
{
	uint16	usCtPoint1;	/*!< �����ٵ������������1 �ϰ�: 0x00��0x3FF */
	uint16	usCtPoint2;	/*!< �����ٵ������������2 �ϰ�: 0x00��0x3FF */
	uint16	usCtPoint3;	/*!< �����ٵ������������3 �ϰ�: 0x00��0x3FF */
	uint16	usCtPoint4;	/*!< �����ٵ������������4 �ϰ�: 0x00��0x3FF */
	uint16	usCtPoint5;	/*!< �����ٵ������������5 �ϰ�: 0x00��0x3FF */
	uint16	usCtPoint6;	/*!< �����ٵ������������6 �ϰ�: 0x00��0x3FF */
} dFrdCtPoint_t;


/**
 * @brief	������������RGB���깽¤�����
 */
typedef struct
{
	uint16	usCtVal1;	/*!< ����1�ο����������� �ϰ�: 0x00��0x3FF */
	uint16	usCtVal2;	/*!< ����2�ο����������� �ϰ�: 0x00��0x3FF */
	uint16	usCtVal3;	/*!< ����3�ο����������� �ϰ�: 0x00��0x3FF */
	uint16	usCtVal4;	/*!< ����4�ο����������� �ϰ�: 0x00��0x3FF */
	uint16	usCtVal5;	/*!< ����5�ο����������� �ϰ�: 0x00��0x3FF */
	uint16	usCtVal6;	/*!< ����6�ο����������� �ϰ�: 0x00��0x3FF */
} dFrdCtValRgb_t;


/**
 * @brief	���������������깽¤�����
 */
typedef struct
{
	dFrdCtValRgb_t	*ptCtRedVal;	/*!< Red�ѿ����������ͤؤΥݥ��� */
	dFrdCtValRgb_t	*ptCtGrnVal;	/*!< Grn�ѿ����������ͤؤΥݥ��� */
	dFrdCtValRgb_t	*ptCtBluVal;	/*!< Blu�ѿ����������ͤؤΥݥ��� */
} dFrdCtVal_t;


/**
 * @brief ���������깽¤����� (8bit)
 */
typedef struct
{
	uint8	ucR;	/*!< Red */
	uint8	ucG;	/*!< Green */
	uint8	ucB;	/*!< Blue */
} dFrdPixelDat_t;


/**
 * @brief ���������͹�¤�����
 */
typedef struct
{
	dFrdInputFreq_e	eFreq;		/*!< �����μ��ȿ� */
	uint8			ucLvl;		/*!< �����β���Lvl */
	flag			fFrcEn;		/*!< ������FRC���� */
	flag			fQsEn;		/*!< ������QS���� */
} dFrdCurrentVal_t;


/*********************/
/* ��ʿ3���������� */
/*********************/
/**
 * @brief ��ʿ3ʬ�䥹������®������������
 */
typedef enum{
	FRD_AREA3_RIGHT,		/*!< ������ */
	FRD_AREA3_LEFT,			/*!< ������ */
	FRD_AREA3_STOP,			/*!< ��� */
	FRD_AREA3_PROHIBIT,		/*!< �ػ� */
} dFrdArea3Mov_e;
#define FRD_AREA3_MOV_NUMMAX (FRD_AREA3_PROHIBITION+1)


/**
 * @brief ��ʿ3ʬ���ư�������깽¤�����
 */
typedef struct {
	dFrdArea3Mov_e	eArea1Mov;	/*!< �ΰ�1�ΰ�ư���� */
	dFrdArea3Mov_e	eArea2Mov;	/*!< �ΰ�2�ΰ�ư���� */
	dFrdArea3Mov_e	eArea3Mov;	/*!< �ΰ�3�ΰ�ư���� */
} dFrdArea3Mov_t;


/**
 * @brief ��ʿ3ʬ�䥹������®�����깽¤�����
 */
typedef struct {
	uint8	ucArea1Speed;	/*!< �ΰ�1��������®�� (0x00-0x3F) */
	uint8	ucArea2Speed;	/*!< �ΰ�2��������®�� (0x00-0x3F) */
	uint8	ucArea3Speed;	/*!< �ΰ�3��������®�� (0x00-0x3F) */
} dFrdArea3Speed_t;


/**
 * @brief ��ʿ3ʬ�����깽¤�����
 */
typedef struct {
	uint16	usArea2Y;		/*!< ��ʿ3ʬ�䡦�ΰ�2���ϥ饤���ֹ� (0x00-0x437) */
	uint16	usArea3Y;		/*!< ��ʿ3ʬ�䡦�ΰ�3���ϥ饤���ֹ� (0x00-0x437) */
	dFrdArea3Speed_t	tArea3Speed;	/*!< ��ʿ3ʬ�䥹������®������ */
	dFrdArea3Mov_t		tArea3Mov;	/*!< ��ʿ3ʬ���ư�������� */
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
/* 100310 ohashi: ����������˾������ */
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
