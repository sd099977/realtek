#ifndef FRDLCDGUAPI_H
#define FRDLCDGUAPI_H

/**
 * @file frdlcdguapi.h
 *
 * @brief GuavaLCD制御
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
#define GU_RIGION_JP1	10	/* 国内 */
#define GU_RIGION_US1	20	/* 北米 */
#define GU_RIGION_EU1	30	/* 欧州 */
#define GU_RIGION_AS1	40	/* アジア */

#define GU_REGION_INFO	GU_RIGION_JP1

/* RegAddr Offset */
#define LCDGU_REGADDR_CGN			0x80
#define LCDGU_REGADDR_EDC			0x100
#define LCDGU_REGADDR_PNL			0x300
#define LCDGU_REGADDR_OSD			0x400
#define LCDGU_REGADDR_IMC			0x600
#define LCDGU_REGADDR_IMC			0x600

#define LCDGU_REGADDR_DP			0xA00
#define LCDGU_REGADDR_CS_SUB		0xC00

#define LCDGU_REGADDR_SBR			0x1000

#define LCDGU_REGADDR_GAMLUTR	0x4000
#define LCDGU_REGADDR_GAMLUTG	0x4600
#define LCDGU_REGADDR_GAMLUTB	0x4C00
#define LCDGU_REGADDR_QSLUT			0x6600
#define LCDGU_REGADDR_TIMGEN		0x6A00
#define LCDGU_REGADDR_BITMAP		0x6B00
#define LCDGU_REGADDR_DAC			0x6C80
#define LCDGU_REGADDR_ETC			0x6CC0
#define LCDGU_REGADDR_SBRPARAM		0x7000
#define LCDGU_REGADDR_FSB			0x9000
#define LCDGU_REGADDR_BDLUT			0xA000

#define LCDGU_DBG_LEVEL				10

/**********/
/* 列挙体 */
/**********/
typedef enum {
	LCDGU_AB,		/*!< AB */
	LCDGU_CD,		/*!< CD */
} dFrdLcdGuCh_e;
#define FRDLCDGU_CH_NUMMAX (FRDLCDGU_CD+1)

typedef enum{
	LCDGU_CPWB_DIREC_NORMAL,	/*!< 正スキャン */
	LCDGU_CPWB_DIREC_ROTATION,	/*!< 逆スキャン */
} dLcdGuCpwbDirec_e;
#define LCDGU_CPWB_DIREC_NUM (LCDGU_CPWB_DIREC_ROTATION+1)


/**********/
/* 構造体 */
/**********/
typedef struct
{
	dLcdGuCpwbDirec_e	eCpwbDirec;
} dLcdGuRegionAndInchInfo_t;


/* **
 * ** variable
 * **/

/* **
 * ** prototype
 * **/
extern dResult_e eFrdLcdGuRegWs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats );
extern dResult_e eFrdLcdGuRegRs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats );
extern dResult_e eFrdLcdGuRegW( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 usVal );
extern dResult_e eFrdLcdGuRegR( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 *pusVal );
//extern dResult_e eFrdLcdGuSetSize( dFrdLcdPnlSize_e ePnlSize );
//extern dResult_e eFrdLcdGuGetSize( dFrdLcdPnlSize_e *pePnlSize );
extern dResult_e eFrdLcdGuChkRomLoadEnd( void );
extern dResult_e eFrdLcdGuGetRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdGuGetUnifiedRevInfo( uint8 *pucRevInfo );
extern dResult_e eFrdLcdGuGetRevStr( int8 *pcRevInfo );
extern dResult_e eFrdLcdGuInit( void );
extern dResult_e eFrdLcdGuSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr );
extern dResult_e eFrdLcdGuSetOutput( flag fOutEn );
extern dResult_e eFrdLcdGuSetTestPtn( dFrdLcdTestPtn_e eTestPtn );
extern dResult_e eFrdLcdGuSetAgingPtn( uint8 ucAgingPtn );
extern dResult_e eFrdLcdGuSetEvaPtn( uint8 ucEvaPtn );
extern dResult_e eFrdLcdGuSetQsEn( flag fQsEn );
extern dResult_e eFrdLcdGuSetQsHalf( flag fLonRoff );
extern dResult_e eFrdLcdGuSetQsFreq( dFrdInputFreq_e eInputFreq );
extern dResult_e eFrdLcdGuSetQsLvl( uint8 ucLvl );
extern dResult_e eFrdLcdGuSetSbr( uint8 ucLvl );
extern dResult_e eFrdLcdGuRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats );
extern dResult_e eFrdLcdGuRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats );
extern dResult_e eFrdLcdGuRomErase( void );
extern dResult_e eFrdLcdGuSetVerUp( uint8 *pucDats, flag fVerify );
extern dResult_e eFrdLcdGuSetFreeRun( flag fFreeRunEn );
extern dResult_e eFrdLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn );
extern dResult_e eFrdLcdGuGetErrInfo( dFrdLcdError_t *ptError );
extern dResult_e eFrdLcdGuAllManualLoad( void );
extern dResult_e eFrdLcdGuSetBdEn( flag fBdEn );
extern dResult_e eFrdLcdGuSetDac( flag fMemEn, uint16 usDat );
extern dResult_e eFrdLcdGuGetDac( uint16 *pusDat );
extern dResult_e eFrdLcdGuSetLvl( uint8 ucLvl );
extern dResult_e eFrdLcdGuSetVcomPtn( flag fVcomEn );
extern dResult_e eFrdLcdGuSetTemp( uint8 ucTemp );		//sakata20110921
#endif  /* FRDLCDGUAPI_H */
