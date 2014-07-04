#ifndef FRDLCDAPI_H
#define FRDLCDAPI_H


#ifdef __cplusplus
extern "C"
{
#endif //cplusplus

/**
 * @file frdlcdapi.h
 *
 * @brief LCDC����
 *
 * Copyright (c) 2008 SHARP CORPORATION
 *
 * @author 
 */

/* NOTE : ���Υե�����ϡ��ġ���LCD�ѥإå��ե�����ؤ�
          Wrapper�Ȥ��Ƥ��ޤ���
          �ºݤε��Ҥ��ɲä�����ϡ����̤Υإå��ե�������ɵ�����������
 */

/* **
 * ** include
 * **/
#include "frdapi.h"			/* dFrdRegVar_t���ˤ�ɬ�� */

#if 0						//̤����
#include "frdlcdzyapi.h"	/* Yellowtail/Zucchini�� */
#include "frdarapi.h"		/* Arugula�� */
#endif //0

#if 0						//�ʤ�.c¦�ǤޤȤ��include����Τˡ�guava����.c��.h��ξ����include���Ƥ���Τ�Err�ˤʤäƤ���
							//��äơ�.h¦��include�Ϻ������
#include "frdguapi.h"		/* Guava�� */
#endif //0

//#include "DriverRegistFunction.h"

/* **
 * ** variable
 * **/


/**
 * @brief ��ܥ���ȥ���������
 */
typedef enum {
	FRDLCD_SOUSA,		/*!< SousaII */
	FRDLCD_ZUCCHINI,	/*!< Zucchini */
	FRDLCD_YELLOWTAIL,	/*!< YellowTail */
	FRDLCD_ZUCCHINI_P,	/*!< Zucchini_P */
	FRDLCD_ARUGULA,		/*!< Arugula */
	FRDLCD_PLAICE,		/*!< Plaice */
	FRDLCD_GUAVA,		/*!< Guava */
	FRDLCD_UNKNOWN		/*!<  ������ */
} dFrdLcdControler_e;
#define FRDLCD_LSI_NUMMAX (FRDLCD_UNKNOWN+1)

/**
 * @brief ����ȿž����������
 */
typedef enum {
	FRDLCD_TRN_OVR_NORMAL,		/*!< �Ρ��ޥ� */
	FRDLCD_TRN_OVR_MIRROR,		/*!< ����ȿž */
	FRDLCD_TRN_OVR_UPSIDE_DOWN,	/*!< �岼ȿž */
	FRDLCD_TRN_OVR_ROTATE,		/*!< �岼����ȿž */
} dFrdLcdTrnOvr_e;
#define FRDLCD_TRN_OVR_NUMMAX (FRDLCD_TRN_OVR_ROTATE+1)


/**
 * @brief LCD�ƥ��ȥѥ��������
 */
typedef enum {
	FRDLCD_TESTPTN_OFF			= 0,	/*!< OFF */
	FRDLCD_TESTPTN_WB1LINE		= 1,	/*!< �����1�饤�� */
	FRDLCD_TESTPTN_BW1LINE		= 2,	/*!< ����1�饤�� */
	FRDLCD_TESTPTN_HGLAY1		= 3,	/*!< �����졼��������1 */
	FRDLCD_TESTPTN_HGLAY2		= 4,	/*!< �����졼��������2 */
	FRDLCD_TESTPTN_GREEN		= 5,	/*!< ��(255)�٥� */
	FRDLCD_TESTPTN_BLUE			= 6,	/*!< ��(255)�٥� */
	FRDLCD_TESTPTN_RED			= 7,	/*!< ��(255)�٥� */
	FRDLCD_TESTPTN_WHITE		= 8,	/*!< ��(255)�٥� */
	FRDLCD_TESTPTN_BLACK		= 9,	/*!< ��(0)�٥� */
	FRDLCD_TESTPTN_GLAY215		= 10,	/*!< ���졼(215)�٥� */
	FRDLCD_TESTPTN_GLAY147		= 11,	/*!< ���졼(147)�٥� */
	FRDLCD_TESTPTN_GLAY96		= 12,	/*!< ���졼(96)�٥� */
	FRDLCD_TESTPTN_GLAY60		= 13,	/*!< ���졼(60)�٥� */
	FRDLCD_TESTPTN_GLAY47		= 14,	/*!< ���졼(47)�٥� */
	FRDLCD_TESTPTN_FLICKERBMP	= 15,	/*!< �ե�å���BITMAP */

	FRDLCD_TESTPTN_SHADOWING	= 16,	/*!< ����ɡ����󥰥ѥ�����  */
	FRDLCD_TESTPTN_QS1			= 17,	/*!< QS�ƥ��ȥѥ�����1 */
	FRDLCD_TESTPTN_QS2			= 18,	/*!< QS�ƥ��ȥѥ�����2 */
	FRDLCD_TESTPTN_FLICKER1H	= 19,	/*!< �ե�å��ѥ�����(1H) */
	FRDLCD_TESTPTN_FLICKER2H	= 20,	/*!< �ե�å��ѥ�����(2H+1) */

	FRDLCD_TESTPTN_GLAY30		= 21,	/*!< ���졼(30)�٥� */
	FRDLCD_TESTPTN_GLAY44		= 22,	/*!< ���졼(44)�٥� */
	FRDLCD_TESTPTN_GLAY128		= 23,	/*!< ���졼(128)�٥� */
	FRDLCD_TESTPTN_GLAY168		= 24,	/*!< ���졼(168)�٥� */
	FRDLCD_TESTPTN_GLAY212		= 25,	/*!< ���졼(212)�٥� */
	FRDLCD_TESTPTN_RED128		= 26,	/*!< ��(128)�٥� */
	FRDLCD_TESTPTN_GREEN128		= 27,	/*!< ��(128)�٥� */
	FRDLCD_TESTPTN_BLUE128		= 28,	/*!< ��(128)�٥� */
	FRDLCD_TESTPTN_LMD			= 29,	/*!< LMD��ǧ�ѥ����� */
	FRDLCD_TESTPTN_FORECAST_OS	= 30,	/*!< ͽ¬OS����(�������)�⡼�� */

	FRDLCD_TESTPTN_MONOCHRO		= 31,	/*!< ��Υ���ɽ�� */
	FRDLCD_TESTPTN_GRADATION	= 32,	/*!< ��Ĵ�ƥ���ɽ�� */
	FRDLCD_TESTPTN_BETA			= 33,	/*!< �٥�ɽ�� */
	FRDLCD_TESTPTN_STRIPE		= 34,	/*!< �ĥ��ȥ饤�� */
	FRDLCD_TESTPTN_GRAYSCALE_H	= 35,	/*!< ��ʿ�������졼�������� */
	FRDLCD_TESTPTN_GRAYSCALE_V	= 36,	/*!< ��ľ�������졼�������� */
	FRDLCD_TESTPTN_COLOR_CHART	= 37,	/*!< ���顼���㡼�� */
	FRDLCD_TESTPTN_FLICKER1		= 38,	/*!< �ե�å��ѥ�����1 */
	FRDLCD_TESTPTN_FLICKER2		= 39,	/*!< �ե�å��ѥ�����2 */
	FRDLCD_TESTPTN_AD_ADJUST	= 40,	/*!< A/DĴ���ѥѥ����� */
	FRDLCD_TESTPTN_BETA_UD		= 41,	/*!< �岼ʬ��٥� */
	FRDLCD_TESTPTN_BETA_LR		= 42,	/*!< ����ʬ��٥� */
	FRDLCD_TESTPTN_FLICKER		= 43,	/*!< �饤��ȿž�ѥե�å��ѥ����� */
	FRDLCD_TESTPTN_SANDSTORM	= 44,	/*!< ����ѥ����� */
	FRDLCD_TESTPTN_LINE			= 45,	/*!< 1�饤��ɽ���ѥ����� */
	FRDLCD_TESTPTN_VERTICAL_LINE= 46,	/*!< 1��ɽ���ѥ����� */
} dFrdLcdTestPtn_e;
#define FRDLCD_TESTPTN_NUMMAX (FRDLCD_TESTPTN_VERTICAL_LINE+1)


/**
 * @brief Revision�������
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
 * @brief ����Revision�������
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
 * @brief �ѥͥ륵�������
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
 * @brief ����ȿž����������
 */
typedef enum {
	FRDLCD_DECONT_OFF,		/*!< �ǥ����OFF */
	FRDLCD_DECONT_V_ON,		/*!< ��ľ�ǥ���ȤΤ�ON */
	FRDLCD_DECONT_H_ON,		/*!< ��ʿ�ǥ���ȤΤ�ON */
	FRDLCD_DECONT_VH_ON,	/*!< ��ľ��ʿ�ǥ����ON */
} dFrdLcdDecont_e;


/**
 * @brief ��°������������
 */
typedef enum
{
	FRDLCD_BRI,	/*!< ����  */
	FRDLCD_SAT,	/*!< ����  */
	FRDLCD_HUE,	/*!< ����  */
} dFrdLcdBsh_e;
#define FRDLCD_BSH_NUMMAX (FRDLCD_HUE+1)


/**
 * @brief NR�⡼������������
 */
typedef enum
{
	FRDLCD_NR_OFF,	/*!< NR OFF  */
	FRDLCD_NR_MIN,	/*!< NR ��  */
	FRDLCD_NR_MID,	/*!< NR ��  */
	FRDLCD_NR_MAX,	/*!< NR ��  */
} dFrdLcdNrMode_e;
#define FRDLCD_NR_MODE_NUMMAX (FRDLCD_NR_MAX+1)


/**
 * @brief RGB���ѹ�¤��
 */
typedef struct {
	uint16 usR;	/*!< R��Ĵ[0-4095] */
	uint16 usG;	/*!< G��Ĵ[0-4095] */
	uint16 usB;	/*!< B��Ĵ[0-4095] */
} dFrdLcdRgb_t;


/**
 * @brief �ƥ��ȥѥ������������ѹ�¤��
 */
typedef struct {
	int32 iTPDAR;	/*!< R��Ĵ[0-1023] */
	int32 iTPDAG;	/*!< G��Ĵ[0-1023] */
	int32 iTPDAB;	/*!< B��Ĵ[0-1023] */
} dFrdLcdTpColor_t;


/**
 * @brief ���顼�������깽¤��
 */
typedef struct {
	uint8 ucErrCode;	/*!< ���顼������  */
	uint8 ucErrBlock;	/*!< ���ɥ��顼�֥�å��ֹ� */
	uint16 usAddr;		/*!< �б��쥸�������ɥ쥹 */
	uint8 ucCrcExp;		/*!< CRC������ */
	uint8 ucCrcCal;		/*!< CRC�黻�� */
} dFrdLcdError_t;

#define FRDLCD_ERR_LOG_NUM_MAX		64		/* ���顼���������Υ����� */


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
