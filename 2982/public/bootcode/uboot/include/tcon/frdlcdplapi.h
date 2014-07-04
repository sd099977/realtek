#ifndef FRDLCDPLAPI_H
#define FRDLCDPLAPI_H

/**
 * @file frdlcdplapi.h
 *
 * @brief PlaiceLCD制御
 *
 * Copyright (c) 2009 SHARP CORPORATION
 *
 * @author 
 */


/* **
 * ** include
 * **/
#ifdef TURNKEY1
#include "sysapi.h"
#ifdef TURNKEY2				//sakata20110920
//#include "frdDriverRegistFunction.h"	//sakata20110920
#endif //TURNKEY2				//sakata20110920
#else //TURNKEY1
//?#include "sousa2.h"
//?#include "advapi.h"
#endif //TURNKEY1

//#include "frdDriverRegistFunction.h"

/* **
 * ** define
 * **/
#define PL_RIGION_JP1	10	/* 国内 */
#define PL_RIGION_US1	20	/* 北米miniLVDS */
#define PL_RIGION_US2	21	/* 北米PPDS */
#define PL_RIGION_EU1	30	/* 欧州 */
#define PL_RIGION_AS1	40	/* アジア */
#define PL_RIGION_AS2	50	/* アジア(外販パネル) */

#ifdef TURNKEY1
#define PL_REGION_INFO	PL_RIGION_AS2
#else //TURNKEY1
#define PL_REGION_INFO	PL_RIGION_JP1
#endif //TURNKEY1

/* 090409 ohashi: frdplapi.cでも使用の可能性があるマクロはこちらに記載 */

/* RegAddr Offset */
//#define LCDPL_REGADDR_CTL			0x00
#define LCDPL_REGADDR_CGN			0x80
#define LCDPL_REGADDR_EDC			0x100
#define LCDPL_REGADDR_IDF			0x200
#define LCDPL_REGADDR_PNL			0x300
#define LCDPL_REGADDR_OSD			0x400
#define LCDPL_REGADDR_IMC			0x600
#define LCDPL_REGADDR_PCCUVL		0x800
#define LCDPL_REGADDR_SBR			0x1000
#define LCDPL_REGADDR_PPDS			0x2000

#define LCDPL_REGADDR_FR_GAMLUTR	0x4000
#define LCDPL_REGADDR_FR_GAMLUTG	0x4600
#define LCDPL_REGADDR_FR_GAMLUTB	0x4C00
#define LCDPL_REGADDR_FR_DECLUT		0x5200
#define LCDPL_REGADDR_FR_DATAPATH	0x5300
#define LCDPL_REGADDR_FR_BITMAP		0x5380
#define LCDPL_REGADDR_DATAPATH		0x6400
#define LCDPL_REGADDR_QSLUT			0x6600
#define LCDPL_REGADDR_TIMGEN		0x6A00
#define LCDPL_REGADDR_BITMAP		0x6B00
#define LCDPL_REGADDR_DAC			0x6C80
#define LCDPL_REGADDR_ETC			0x6CC0
#define LCDPL_REGADDR_SBRPARAM		0x7000
/* 090408 ohashi: FRCはfrdplapi.hで宣言されている */
#define LCDPL_REGADDR_FSB			0x9000
#define LCDPL_REGADDR_BDLUT			0xA000

#define LCDPL_DBG_LEVEL				10

/**********/
/* 列挙体 */
/**********/
typedef enum {
	LCDPL_AB,		/*!< AB */
	LCDPL_CD,		/*!< CD */
} dFrdLcdPlCh_e;
#define FRDLCDPL_CH_NUMMAX (FRDLCDPL_CD+1)

typedef enum{
	LCDPL_CPWB_DIREC_NORMAL,	/*!< 正スキャン */
	LCDPL_CPWB_DIREC_ROTATION,	/*!< 逆スキャン */
} dLcdPlCpwbDirec_e;
#define LCDPL_CPWB_DIREC_NUM (LCDPL_CPWB_DIREC_ROTATION+1)


/**********/
/* 構造体 */
/**********/
typedef struct
{
	dLcdPlCpwbDirec_e	eCpwbDirec;
} dLcdPlRegionAndInchInfo_t;


/***********************************************************/
/* 下記構造体はいつでも上位層に公開できるよう"dFrdLcdPl〜" */
/***********************************************************/
/**
 * @brief 輝度,彩度,色相のON/OFF設定構造体
 */
typedef struct {
	flag fBriEn;	/*!< 輝度のON/OFF */
	flag fSatEn;	/*!< 彩度のON/OFF */
	flag fHueEn;	/*!< 色相のON/OFF */
} dFrdLcdPlBshEn_t;


/**
 * @brief 色領域の中心及び範囲設定構造体
 */
typedef struct {
	uint16 usCenter;	/*!< 領域の中心,
							輝度,彩度:	[0x0000(0.0)〜0xFFFF(1.0)],
							色相:		[0x0000(0)〜0xFFFF(359)] */
							
	uint16 usDelta;		/*!< 中心からの距離,
							輝度,彩度:	[0x0000(0.0)〜0xFFFF(1.0)],
							色相:		[0x0000(0)〜0xFFFF(180)] */
} dFrdLcdPlPccArea_t;


/**
 * @brief 輝度,彩度,色相の領域設定構造体
 */
typedef struct {
	dFrdLcdPlPccArea_t		*ptBriArea;		/*!< 輝度の領域設定 */
	dFrdLcdPlPccArea_t		*ptSatArea;		/*!< 彩度の領域設定 */
	dFrdLcdPlPccArea_t		*ptHueArea;		/*!< 色相の領域設定 */
} dFrdLcdPlBshArea_t;


/**
 * @brief 輝度,彩度,色相のレベル設定構造体 (11bit,2の補数設定)
 */
typedef struct {
	uint16 usBriLvl;	/*!< 輝度レベル [0x400(0倍)〜0x000(1倍)〜0x3FF(約2倍)] */
	uint16 usSatLvl;	/*!< 彩度レベル [0x400(0倍)〜0x000(1倍)〜0x3FF(約2倍)] */
	uint16 usHueLvl;	/*!< 色相レベル [0x400(-180°)〜0x000(0°)〜0x3FF(約180°)] */
} dFrdLcdPlBshLvl_t;


/**
 * @brief PCC詳細設定構造体
 */
typedef struct {
	dFrdLcdPlBshEn_t	*ptBshEn;		/*!< 輝度,彩度,色相のON/OFF */
	dFrdLcdPlBshArea_t	*ptBshArea;		/*!< 輝度,彩度,色相の領域設定 */
	dFrdLcdPlBshLvl_t	*ptBshLvl;		/*!< 輝度,彩度,色相のレベル設定 */
} dFrdLcdPlPcc_t;


/* **
 * ** variable
 * **/

/* **
 * ** prototype
 * **/
extern dResult_e eFrdLcdPlRegWs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats );
extern dResult_e eFrdLcdPlRegRs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats );
extern dResult_e eFrdLcdPlRegW( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 usVal );
extern dResult_e eFrdLcdPlRegR( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 *pusVal );
extern dResult_e eFrdLcdPlSetSize( dFrdLcdPnlSize_e ePnlSize );
extern dResult_e eFrdLcdPlGetSize( dFrdLcdPnlSize_e *pePnlSize );
extern dResult_e eFrdLcdPlChkRomLoadEnd( void );
extern dResult_e eFrdLcdPlGetRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdPlGetUnifiedRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdPlGetRevStr( int8 *pcRevInfo );
extern dResult_e eFrdLcdPlInit( void );
extern dResult_e eFrdLcdPlSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr );
extern dResult_e eFrdLcdPlSetOutput( flag fOutEn );
extern dResult_e eFrdLcdPlSetTestPtn( dFrdLcdTestPtn_e eTestPtn );
extern dResult_e eFrdLcdPlSetAgingPtn( uint8 ucAgingPtn );
extern dResult_e eFrdLcdPlSetEvaPtn( uint8 ucEvaPtn );
extern dResult_e eFrdLcdPlSetQsEn( flag fQsEn, flag fYuv );
extern dResult_e eFrdLcdPlSetQsHalf( flag fLonRoff );
extern dResult_e eFrdLcdPlSetQsFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdLcdPlSetQsTemp( uint8 ucTemp );
extern dResult_e eFrdLcdPlSetSbr( uint8 ucTemp );
extern dResult_e eFrdLcdPlRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats );
extern dResult_e eFrdLcdPlRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats );
extern dResult_e eFrdLcdPlRomErase( void );
extern dResult_e eFrdLcdPlSetVerUp( uint8 *pucDats, flag fVerify );
extern dResult_e eFrdLcdPlSetFreeRun( flag fFreeRunEn );
extern dResult_e eFrdLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn );
extern dResult_e eFrdLcdPlGetErrInfo( dFrdLcdError_t *ptError );
extern dResult_e eFrdLcdPlAllManualLoad( void );
//extern dResult_e eFrdLcdPlSetGammaEn( flag fGammaEn );
//extern dResult_e eFrdLcdPlSetDecontEn( flag fDecontEn );
//extern dResult_e eFrdLcdPlSetCckEn( flag fCckEn );
extern dResult_e eFrdLcdPlSetFrAgingPtn( uint8 ucFrAgingPtn );
extern dResult_e eFrdLcdPlSetFrEvaPtn( uint8 ucFrEvaPtn );
extern dResult_e eFrdLcdPlSetUvlEn( flag fUvlEn );
extern dResult_e eFrdLcdPlSetUvlMode( uint8 ucUvlMode );
extern dResult_e eFrdLcdPlSetBdEn( flag fBdEn );
extern dResult_e eFrdLcdPlSetNrMode( dFrdLcdNrMode_e eNrMode );
extern dResult_e eFrdLcdPlSetNrMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame );
extern dResult_e eFrdLcdPlSetPccEn( flag fPccEn );
extern dResult_e eFrdLcdPlSetPccCol( uint8 ucColNo, flag fColEn, dFrdLcdPlPcc_t *ptPccParam );
extern dResult_e eFrdLcdPlSetPccColEn( uint8 ucColNo, flag fColEn );
extern dResult_e eFrdLcdPlSetPccBshEn( uint8 ucColNo, flag fBriEn, flag fSatEn, flag fHueEn );
extern dResult_e eFrdLcdPlSetPccBshArea( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usCenter, uint16 usDelta );
extern dResult_e eFrdLcdPlSetPccBshLvl( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usLvl );
extern dResult_e eFrdLcdPlChgGamLut( flag fChgEn );
#endif  /* FRDLCDPLAPI_H */
