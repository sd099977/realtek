/**
 * @file frdlcdguapi.c
 *
 * @brief GuavaLCD������
 *
 * Copyright (c) 2010 SHARP CORPORATION
 *
 * @author 
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
#include <tcon/frdlcdguapi.h>
#include <tcon/frdguapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/
//#define DEBUG_LCDGU_MANULOAD_SBR

/* RomAddr */
#define LCDGU_ROMADDR_REVISION	0x300
#define LCDGU_ROMADDR_UNIFIED_REVISION	0x3FFF0
#define LCDGU_ROMADDR_SBRPARAM	0xE500

#define LCDGU_ROMADDR_GHOSTLUT1	0x2E500
#define LCDGU_ROMADDR_GHOSTLUT2	0x38080
#define LCDGU_ROMADDR_QSLUT		0x0A500
#define LCDGU_ROMADDR_UVLMODE	0x7700
#define LCDGU_ROMADDR_NRMODE	0x1060

#define LCDGU_ROMSIZE_SBRPARAM	0x2000
//#define LCDGU_ROMSIZE_SBRPARAM	0x1000

#define LCDGU_ROMSIZE_GHOSTLUT1	0x09B8
#define LCDGU_ROMSIZE_GHOSTLUT2	272
#define LCDGU_ROMSIZE_QSLUT		0x400
#define LCDGU_ROMSIZE_UVLMODE	0x80
#define LCDGU_ROMSIZE_NRMODE	0x10

/* ROM���� */
#define LCDGU_ROMSIZE_TOTAL_8M		0x100000/* 8Mbit */
#define LCDGU_ROMSIZE_TOTAL_2M		0x40000	/* 2Mbit */
#define LCDGU_ROM_PAGE_SIZE_2M		256		/* 2Mbit */

/* ROM���ơ������쥸���� */
#define LCDGU_ROM_STATUS_WIP		0x01	/* Write In Progress */
#define LCDGU_ROM_STATUS_WEL		0x02	/* Write Enable Latch */
#define LCDGU_ROM_STATUS_BP10		0x0C	/* Block Protect(BP0, BP1) */
#define LCDGU_ROM_STATUS_BP210		0x1C	/* Block Protect(BP0, BP1, BP2) */
#define LCDGU_ROM_STATUS_SRDW		0x80	/* Status Register Write Disable */

#define LCDGU_ROM_BURST_LEN_W		256		/* ROM�С����ȥ饤���ѥХåե�(LCDC�쥸����)Ĺ */
#define LCDGU_ROM_BURST_LEN_R		256		/* ROM�С����ȥ꡼���ѥХåե�(LCDC�쥸����)Ĺ */

/* SPI���ޥ����� */
#define LCDGU_ROM_CMD_WRSR			1		/* ���ơ������쥸�����ؤν񤭹��� */
#define LCDGU_ROM_CMD_WRITE			2		/* �ǡ����񤭹��� */
#define LCDGU_ROM_CMD_READ			3		/* �ǡ����ɤ߹��� */
#define LCDGU_ROM_CMD_WRDI			4		/* �񤭹��߶ػ߾��֤ˤ��� */
#define LCDGU_ROM_CMD_RDSR			5		/* ���ơ������쥸�������ɤ߹��� */
#define LCDGU_ROM_CMD_WREN			6		/* �񤭹��߲�ǽ�ˤ��� */
#define LCDGU_ROM_CMD_SE			0xD8	/* Sector Erase */
#define LCDGU_ROM_CMD_BE			0xC7	/* Bulk Erase */

#define LCDGU_EVA_PTN_NUM_MAX		0x12
#define LCDGU_AGI_PTN_NUM_MAX		0x1F

#define LCDGU_I2C_DATA_LEN_MAX 		96		/* I2C�쥸����ž������Ĺ���(iic.h�Ǥ� MAX_DATAS �����(����256)�ˤ��) */


#if 0/* ROM���������顼�����å���̵���ˤ���Ȥ���'1'�ˤ��� */
#define LCDGU_ROM_SIZE_ERROR_BYPASS
#endif

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
//sakata20111013 extern dFrdLcdPnlSize_e eFrdLcdPnlSize;	//sakata20110921

const static uint8 ucAdGuTbl[FRDLCD_PNL_NUMMAX][7] = {			//sakata20110921
/* 32inch */	{89, 105, 115, 125, 135, 145, 154},				//sakata20110921
/* 40inch *///�����	{87, 106, 118, 130, 141, 153, 165},		//sakata20110921
/* 40inch */	{41,  46,  48,  50,  53,  54,  56},//DS5��		//sakata20110921
/* 46inch *///�����	{88, 106, 116, 127, 138, 148, 159},		//sakata20110921
/* 46inch */	{42,  46,  49,  51,  53,  55,  56},	//DS5��		//sakata20110921
/* 52inch */	{94, 112, 123, 133, 144, 155, 166},				//sakata20110921
/* 60inch *///�����	{97, 116, 128, 141, 155, 168, 183},		//sakata20110921
/* 60inch */	{43,  47,  49,  51,  53,  55,  57},//DS5��		//sakata20110921
};																//sakata20110921


/* static const�ѿ� */
static const dFrdLcdTrnOvr_e aeLcdGuConvTrnOvr[LCDGU_CPWB_DIREC_NUM][FRDLCD_TRN_OVR_NUMMAX] =
{
	{/* ������������� */
		FRDLCD_TRN_OVR_NORMAL,
		FRDLCD_TRN_OVR_MIRROR,
		FRDLCD_TRN_OVR_UPSIDE_DOWN,
		FRDLCD_TRN_OVR_ROTATE
	},
	
	{/* �ե���������� */
		FRDLCD_TRN_OVR_ROTATE,
		FRDLCD_TRN_OVR_UPSIDE_DOWN,
		FRDLCD_TRN_OVR_MIRROR,
		FRDLCD_TRN_OVR_NORMAL
	}
};

/* LCD�ƥ��ȥѥ������ֹ�ơ��֥� */
static const uint8 aucLcdGuTestPtnTbl[FRDLCD_TESTPTN_NUMMAX] =
{
	0x00,										/* OFF */
	0x05,										/* ��������饤�� */
	0x06,										/* ���򲣣��饤�� */
	0x07,										/* �����졼�������룱 */
	0x08,										/* �����졼�������룲 */
	0x09,										/* �С�255�˥٥� */
	0x0A,										/* �ġ�255�˥٥� */
	0x0B,										/* �֡�255�˥٥� */
	0x0C,										/* ���255�˥٥� */
	0x0D,										/* ����0�˥٥� */
	0x0E,										/* ���졼��215�˥٥� */
	0x0F,										/* ���졼��147�˥٥� */
	0x10,										/* ���졼��96�˥٥� */
	0x11,										/* ���졼��60�˥٥� */
	0x12,										/* ���졼��47�˥٥� */
	0x13,										/* �ե�å��� �� bitmap */
	LCDGU_AGI_PTN_NUM_MAX + 0xA,				/* ����ɡ����󥰥ѥ�����(ɾ���ѥѥ�����) */
	0x3,										/* QS�ƥ��ȥѥ����� */
	0x4,										/* QS�ƥ��ȥѥ����� */
	0x1,										/* �ե�å��ѥ�����(1H) */
	0x2,										/* �ե�å��ѥ�����(2H+1) */
	0x14,										/* ���졼��30�˥٥� */
	0x15,										/* ���졼��44�˥٥� */
	0x16,										/* ���졼��128�˥٥� */
	0x17,										/* ���졼��168�˥٥� */
	0x18,										/* ���졼��212�˥٥� */
	0x19,										/* �֡�128�˥٥� */
	0x1A,										/* �С�128�˥٥� */
	0x1B,										/* �ġ�128�˥٥� */
	0x1D,										/* LMD��ǧ�ѥ����� */
	0x1E,										/* ͽ¬OS����(�������)�⡼�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x1,				/* ��Υ���ɽ�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x2,				/* ��Ĵ�ƥ���ɽ�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x3,				/* �٥�ɽ�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x4,				/* �ĥ��ȥ饤�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x5,				/* ��ʿ�������졼�������� */
	LCDGU_AGI_PTN_NUM_MAX + 0x6,				/* ��ľ�������졼�������� */
	LCDGU_AGI_PTN_NUM_MAX + 0x7,				/* ���顼���㡼�� */
	LCDGU_AGI_PTN_NUM_MAX + 0x8,				/* �ե�å��ѥ����� */
	LCDGU_AGI_PTN_NUM_MAX + 0x9,				/* �ե�å��ѥ����� */
	LCDGU_AGI_PTN_NUM_MAX + 0xB,				/* A/DĴ���ѥѥ����� */
	LCDGU_AGI_PTN_NUM_MAX + 0xC,				/* �岼ʬ��٥� */
	LCDGU_AGI_PTN_NUM_MAX + 0xD,				/* ����ʬ��٥� */
	LCDGU_AGI_PTN_NUM_MAX + 0xE,				/* �饤��ȿž�ѥե�å��ѥ����� */
	LCDGU_AGI_PTN_NUM_MAX + 0xF,				/* ����ѥ����� */
	LCDGU_AGI_PTN_NUM_MAX + 0x10,				/* 1�饤��ɽ���ѥ�����(Zucchini) */
	LCDGU_AGI_PTN_NUM_MAX + 0x11				/* 1��ɽ���ѥ�����(Zucchini) */
};

/****************/
/* ����ȿž���� */
/****************/
/* miniLVDS only */
static const uint16 aucLcdGuTrnOvr[7][FRDLCD_TRN_OVR_NUMMAX] = {
/* CSS		0xAD0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
/* CSS		0xBD0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
/* DP		0xA31 */			{0x0000, 0x0001, 0x0000, 0x0001},	/* bit2 �Τ� */
/* TIMGEN	0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* TIMGEN	0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},
/* CCK		0xA2E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* CCK		0xB2E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
};


/* static�ѿ� */
static uint8 aucLcdGuRevInfo[FRDLCD_REVISION_DATA_MAX];			/* ROM Revision�ǡ�����¸������ */
static uint8 aucLcdGuUnifiedRevInfo[FRDLCD_REVISION_DATA_MAX];	/* ROM Revision(����)�ǡ�����¸������ */
static dLcdGuRegionAndInchInfo_t tRegionAndInchInfo;/* �Ÿ����������������������¸���ѿ� */

static flag				fGetRevInfo		= FALSE;
static dFrdLcdTrnOvr_e	eLcdGuTrnOvr	= FRDLCD_TRN_OVR_NORMAL;
static dFrdInputFreq_e	eLcdGuInputFreq	= FRD_INPUT_FREQ_60HZ;
//static uint8			ucLcdGuLvl		= 4;
uint8			ucLcdGuLvl		= 4;

static dFrdLcdError_t		atLcdGuErrInfo[FRDLCD_ERR_LOG_NUM_MAX];
static uint8				ucLcdGuErrInfoInCnt  = 0;
static uint8				ucLcdGuErrInfoOutCnt = 0;

static uint8			ucLcdGuPnlSizeNo	= 0;/* 8Mbit ROM�б� : 0:32��,  1:40��,  2:46��,  3:52��  */
static uint32			uiLcdGuRomOffset	= 0;/*               : 0x00000, 0x40000, 0x80000, 0xC0000 */
static uint32			uiLcdGuRomSize		= LCDGU_ROMSIZE_TOTAL_8M;

static uint8 ucNegCnt = 0;
static uint8 ucPosCnt = 0;
static flag f1stCycle;

/* **
 * ** prototype
 * **/
dResult_e eFrdLcdGuSetOutFreq( dFrdInputFreq_e eInputFreq );	//<- 2011/02/24	�ͳ�ȯ�ɲ�
static dResult_e eLcdGuChkRomLoadEnd( void );
static void vAddrConv(dFrdLcdGuCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats);
static uint16 usAddrConv(dFrdLcdGuCh_e *peCh, uint16 usAddr);
static dResult_e eLcdGuChkCrcForRomLoad( void );
static dResult_e eLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn , flag fOffset);
static flag fLcdGuRegDepth16bit( uint32 uiAddr );
static dResult_e eLcdGuRomStatusChk( uint16 *pusStatus );
static dResult_e eLcdGuSetTpDat( dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb );
static dResult_e eLcdGuRomToWProtectMode( flag fWPMEn );
static dResult_e eLcdGuGetRegionAndInchInfo( dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo );
static dResult_e eLcdGuSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr );
static dResult_e eLcdGuSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl );
#ifdef DEBUG_LCDGU_MANULOAD_SBR
static void vLcdGuDbgMnl( void );
#endif
static dResult_e eLcdGuGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuGetGhostLut2RomAddr( dFrdLcdGuCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr);
static dResult_e eLcdGuSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucLvl );
static dResult_e eLcdGuGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdGuRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats );
static dResult_e eLcdGuSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr );
static dResult_e eLcdGuReloadAll( uint8 ucPnlSizeNo );					/* 8Mbit ROM�б� */
static dResult_e eLcdGuGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr );	/* 8Mbit ROM�б� */

/* **
 * ** func
 * **/

/*!
********************************************************************************
** @brief	���ѥ쥸����Ϣ³�����API (LCD¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDats	: ����ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRegWs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32 i;
//sakata20110627	uint16 tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1

	vAddrConv(&eCh, iRegNum, ptDats);

#ifdef TURNKEY1
	for( i=0; i<iRegNum; i++ )
	{
//sakata20110627		tmp_addr = ptDats[0].usAddr + (uint16)i;
//sakata20110627		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDats[i].usVal);
	eResult = eI2CWrite( IIC_SLV_ADDR_TCON, ptDats[i].usAddr, ptDats[i].usVal);	//sakata20110627
		if( eResult == S_FAILURE )	break;
	}

#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, iRegNum, ptDats );
	eAdvClose( pvDevice );
#endif //TURNKEY1

	return eResult;
}


/*!
********************************************************************************
** @brief	���ѥ쥸����Ϣ³�ɹ���API (LCD¦)
** @param	iRegNum	: �쥸������ (�����: int32)
** @param	ptDats	: �ɹ��ߥǡ�������(�����: dFrdRegVar_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRegRs( dFrdLcdGuCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32		i;
	uint16		tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1

	vAddrConv(&eCh, iRegNum, ptDats);

#ifdef TURNKEY1
	for(  i=0; i<iRegNum; i++ )
	{		
		tmp_addr = ptDats[0].usAddr + (uint16)i;
		eResult = eI2CRead( IIC_SLV_ADDR_TCON, tmp_addr, &(ptDats[i].usVal));
		ptDats[i].usAddr = ptDats[0].usAddr + i;								//sakata20110627

		if( eResult == S_FAILURE )	break;
	}
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, iRegNum, ptDats);
	eAdvClose( pvDevice );
#endif //TURNKEY1

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
*******************************************************************************/
dResult_e eFrdLcdGuRegW( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 usVal )
{
	dResult_e		eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	const void		*pvDevice;
#endif //TURNKEY1
	dFrdRegVar_t	tData;
	
	tData.usAddr = usAddrConv(&eCh, usAddr);
	tData.usVal  = usVal;

#ifdef TURNKEY1
		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tData.usAddr, tData.usVal );
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvWriteDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	
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
*******************************************************************************/
dResult_e eFrdLcdGuRegR( dFrdLcdGuCh_e eCh, uint16 usAddr, uint16 *pusVal )
{
	dResult_e		eResult = S_SUCCESS;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	const void		*pvDevice;
#endif //TURNKEY1
	dFrdRegVar_t	tData;

	if(pusVal == NULL) return S_SPEC_ERROR;
	
	tData.usAddr = usAddrConv(&eCh, usAddr);

#ifdef TURNKEY1
	eResult = eI2CRead( IIC_SLV_ADDR_TCON, tData.usAddr, &(tData.usVal));
#else //TURNKEY1
	pvDevice = pvAdvOpen( SOUSA2_MASTER );
	eResult = eAdvReadDatas( pvDevice, 1, &tData );
	eAdvClose( pvDevice );
#endif //TURNKEY1
	*pusVal = tData.usVal;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM�������ｪλ�����å�API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	
*******************************************************************************/
dResult_e eFrdLcdGuChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	dResult_e	eResultTmp;
	
	/* �����ɤΥ��ɽ�λ��ǧ */
	eResult |= eLcdGuChkRomLoadEnd();
	
	/* �����ӥ����μ��� */
	eResultTmp = eLcdGuGetRevInfo( aucLcdGuUnifiedRevInfo, LCDGU_ROMADDR_UNIFIED_REVISION );
	if( aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE] == 0x08 ){
	/* ROM��8Mbit�ǡ��� */
		
		/* 8Mbit��Ƚ�̤��줿�����ǡ�Offset�ͤ����ꤹ�� */
		uiLcdGuRomOffset = ucLcdGuPnlSizeNo * LCDGU_ROMSIZE_TOTAL_2M;
		
		/* �ѥͥ륵�������б�����ǡ���2Mbit������All */
		eResult |= eLcdGuReloadAll( ucLcdGuPnlSizeNo );
		
		/* �����ܥ��ɤΥ��ɽ�λ��ǧ */
		eResult |= eLcdGuChkRomLoadEnd();
		
		eResult |= eResultTmp;
		
		uiLcdGuRomSize = LCDGU_ROMSIZE_TOTAL_8M;
	}
	else{
	/* ROM��2Mbit�ǡ��� �� �����ɤΤߤ��ɲý�����ɬ��̵�� */
		uiLcdGuRomOffset = 0;
		uiLcdGuRomSize = LCDGU_ROMSIZE_TOTAL_2M;
	}
	
	/* �������̥�ӥ����μ��� */
	eResult |= eLcdGuGetRevInfo( aucLcdGuRevInfo, LCDGU_ROMADDR_REVISION );
	
	fGetRevInfo = TRUE;/* �������̥�ӥ�������μ����Ѥߤ򼨤��ե饰 */
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM Revision�ǡ�������API
** @param	pucRevInfo : Revision�ǡ������Ǽ��������Υݥ���(�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	����Υ�������ɬ��16�Х��Ȥ���ݤ��뤳�ȡ�
*******************************************************************************/
dResult_e eFrdLcdGuGetRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdGuRevInfo[i];
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	ROM Revision ɽ����API
** @param	pcRevInfo : Revision�ǡ���ɽ����ʸ������Ǽ��������Υݥ���(�����: int8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	����Υ�������ɬ��16�Х��Ȥ���ݤ��뤳�ȡ�(ʸ�����14 or 15ʸ���Ǥ�)
*******************************************************************************/
dResult_e eFrdLcdGuGetRevStr( int8 *pcRevInfo )
{
//sakata20110920 warning_erase	int8 acPanelType[] = "FM";/* FM ��MiniLVDS�ѥͥ� */	//sakata20110920
	int8 cFrcType;										//sakata20110920
//sakata20110920 warning_erase	int8 cTestVer = 'T';								//sakata20110920
	
	if( pcRevInfo == NULL ) return S_SPEC_ERROR;
	
	if( uiLcdGuRomSize == LCDGU_ROMSIZE_TOTAL_2M ){
	/* 2Mbit�ǡ��� */
		if(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4){
		/* MiniLVDS */
		}
		else{
			/* PPDS */
			return S_FAILURE;
		}
		switch (aucLcdGuRevInfo[FRDLCD_REVISION_FRC]){
			case 0x00: cFrcType = 'E'; break;/* Easter */
			case 0x01: cFrcType = 'F'; break;/* Fraser */
			case 0x02: cFrcType = 'Y'; break;/* Yellowtail */
			case 0x04: cFrcType = 'A'; break;/* Arugula */
			case 0x05: cFrcType = 'P'; break;/* Guava */
			case 0x07: cFrcType = 'G'; break;/* Guava */
			case 0x08: cFrcType = 'T'; break;/* Turnip */	//sakata20111220
			default:   cFrcType = '?'; break;/* ���� */
		}
		if( aucLcdGuRevInfo[FRDLCD_REVISION_VER] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �ƥ��ȥС������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%c%02X",
					aucLcdGuRevInfo[FRDLCD_REVISION_YEAR_L],/* ǯ */
					aucLcdGuRevInfo[FRDLCD_REVISION_MONTH],	/* �� */
					aucLcdGuRevInfo[FRDLCD_REVISION_DAY],	/* �� */
					acPanelType,							/* �ѥͥ��ư���� */
					cFrcType,								/* T-CON�ǥХ��� */
					aucLcdGuRevInfo[FRDLCD_REVISION_INCHI],	/* ����������� */
					aucLcdGuRevInfo[FRDLCD_REVISION_MISC],	/* ��ǥ� */
					cTestVer,
					aucLcdGuRevInfo[FRDLCD_REVISION_VER] & 0x7F	/* �С������ */
				);
#endif //TURNKEY1
		}
		else{
		/* �����С������ */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%02X",
					aucLcdGuRevInfo[FRDLCD_REVISION_YEAR_L],/* ǯ */
					aucLcdGuRevInfo[FRDLCD_REVISION_MONTH],	/* �� */
					aucLcdGuRevInfo[FRDLCD_REVISION_DAY],	/* �� */
					acPanelType,							/* �ѥͥ��ư���� */
					cFrcType,								/* T-CON�ǥХ��� */
					aucLcdGuRevInfo[FRDLCD_REVISION_INCHI],	/* ����������� */
					aucLcdGuRevInfo[FRDLCD_REVISION_MISC],	/* ��ǥ� */
					aucLcdGuRevInfo[FRDLCD_REVISION_VER]	/* �С������ */
				);
#endif //TURNKEY1
		}
	}
	else{
	/* 8Mbit�ǡ��� */
		if( aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �ƥ��ȥС������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%c%02X%02X",
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* ǯ */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* �� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* �� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* �Ÿ��� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* ��ǥ� */
					cTestVer,									/* �ƥ��ȥС������ */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x7F,	/* �С�������ֹ�(H) */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* �С�������ֹ�(L) */
				);
#endif //TURNKEY1
		}
		else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �����С������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%02X%02X",
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* ǯ */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* �� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* �� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* �Ÿ��� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* ��ǥ� */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H],	/* �С�������ֹ�(H) */
					aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* �С�������ֹ�(L) */
				);
#endif //TURNKEY1
		}
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	(����)ROM Revision�ǡ�������API
** @param	pucRevInfo : Revision�ǡ������Ǽ��������Υݥ���(�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	����Υ�������ɬ��16�Х��Ȥ���ݤ��뤳�ȡ�
*******************************************************************************/
dResult_e eFrdLcdGuGetUnifiedRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdGuUnifiedRevInfo[i];
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	���������API(LCD¦)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuInit( void )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ROM��饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
	/* �Ÿ�������������������� */
	eResult |= eLcdGuGetRegionAndInchInfo(&tRegionAndInchInfo);
	if(eResult != S_SUCCESS ) return eResult;
	
	/* static�ѿ��ν�������� */
	eLcdGuTrnOvr	= aeLcdGuConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][FRDLCD_TRN_OVR_NORMAL];
	eLcdGuInputFreq	= FRD_INPUT_FREQ_60HZ;
	ucLcdGuLvl		= 4;
	f1stCycle = TRUE;
	
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
*******************************************************************************/
dResult_e eFrdLcdGuSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e eResult = S_SUCCESS;
	
	if(eTrnOvr >= FRDLCD_TRN_OVR_NUMMAX){

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eTrnOvr = %d\n", (int8)eTrnOvr);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eTrnOvr = aeLcdGuConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][eTrnOvr];
	
	eResult |= eLcdGuSetTrnOvrReg(eTrnOvr);
	
	eResult |= eLcdGuSetSbr(eTrnOvr, ucLcdGuLvl);
	
	eLcdGuTrnOvr = eTrnOvr;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	������������API
** @param	fOutEn	: ����(ON/OFF)����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	PPDS����ON/OFF����
*******************************************************************************/
dResult_e eFrdLcdGuSetOutput( flag fOutEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD;
	flag		fMiniL = (flag)(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	
	if(fMiniL){
	/* miniLVDS */
		/* LS����Hi-Z��� (default��1�Ǥʤ��Ȳ���Ǥ��ʤ�??) */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_PNL +0x2B, 0);
		
		/* ODS�ǡ������ϥߥ塼��ON/OFF */
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x04, &usDatAB);
		eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x04, &usDatCD);
		if(fOutEn){
		/* �ߥ塼��OFF(���) �� bit4 �� 0 */
			eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x04, usDatAB & 0xEF);
			eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x04, usDatCD & 0xEF);
		}else{
		/* �ߥ塼��ON �� bit4 �� 1 */
			eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x04, usDatAB | 0x10);
			eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x04, usDatCD | 0x10);
		}
	}
	else{
	/* PPDS */
		return S_FAILURE;
	}
	
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
*******************************************************************************/
dResult_e eFrdLcdGuSetTestPtn( dFrdLcdTestPtn_e eTestPtn )
{
	dResult_e		eResult = S_SUCCESS;
	uint8			ucTestPtn;
	
	if((eTestPtn < FRDLCD_TESTPTN_OFF) || (eTestPtn >= FRDLCD_TESTPTN_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eTestPtn = %d\n", (int8)eTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	ucTestPtn = aucLcdGuTestPtnTbl[eTestPtn];
	
	if(ucTestPtn == 0){
		/* �ƥ��ȥѥ�����OFF */
		eResult |= eFrdLcdGuSetAgingPtn(0);	/* ���������ѥƥ��ȥѥ������OFF */
		eResult |= eFrdLcdGuSetEvaPtn(0);		/* ɾ���ѥƥ��ȥѥ������OFF */
	}
	else if(ucTestPtn <= (LCDGU_AGI_PTN_NUM_MAX + LCDGU_EVA_PTN_NUM_MAX)){
		/* �ƥ��ȥѥ�����ON */
		
		/* ��˾�Υƥ��ȥѥ�����⡼�ɤ����� */
		if(ucTestPtn <= LCDGU_AGI_PTN_NUM_MAX){
			/* �������󥰥ѥ��������� */
			eResult |= eFrdLcdGuSetAgingPtn(ucTestPtn);
			/* ɾ���ѥƥ��ȥѥ������OFF */
			eResult |= eFrdLcdGuSetEvaPtn(0);
		}else{
			/* ɾ���ѥѥ��������� */
			eResult |= eFrdLcdGuSetEvaPtn(ucTestPtn - LCDGU_AGI_PTN_NUM_MAX);
			/* ���������ѥƥ��ȥѥ������OFF */
			eResult |= eFrdLcdGuSetAgingPtn(0);
		}
	}
	else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucTestPtn = %d\n", (int8)ucTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD�������󥰥ѥ���������API
** @param	ucAgingPtn : �������󥰥ѥ������ֹ� [0x00-0x1F] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetAgingPtn( uint8 ucAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usBmpEnab = 0;
	
	if(ucAgingPtn > LCDGU_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucAgingPtn = %d\n", (int8)ucAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucAgingPtn == 0x13){
	/* �ɥå�ȿž�ե�å� + BITMAP */
		usBmpEnab = 1;/* BitMapɽ���ӥåȤ�Ω�Ƥ� */
	}
	
	/* BitMapɽ������ + �ѥ��������� */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x03, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x03, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	
	if((ucAgingPtn == 3) || (ucAgingPtn == 0x1F)){
	/* QS�ѥƥ��ȥѥ�����1 �ξ�硢�С���Ʊ�����碌��١������ǥꥻ�åȤ�Ԥ� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDC�ꥻ�å� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDC�ꥻ�åȲ�� */
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDɾ���ѥѥ���������API
** @param	ucEvaPtn : ɾ���ѥѥ������ֹ� [0x00-0x11] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetEvaPtn( uint8 ucEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB���� */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB���� */
	
	if(ucEvaPtn > LCDGU_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucEvaPtn = %d\n", (int8)ucEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB��)���� */
	eResult |= eLcdGuSetTpDat(LCDGU_AB, &tTpda, &tTpdb);
	eResult |= eLcdGuSetTpDat(LCDGU_CD, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x05, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x05, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS ON/OFF����API
** @param	fQsEn	: QS ON/OFF����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			QS ON�����ˡ����ȿ������٤˹�ä�QS LUT��ޥ˥奢����ɤ��Ƥ���������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetQsEn( flag fQsEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usOsOn=0;
	
	if(fQsEn){
			usOsOn = 0x10;	/* ON/OFF�� bit4 */
	}
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x08, &usDatAB);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x08, &usDatCD);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x08, (usDatAB & 0xCF) | usOsOn);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x08, (usDatCD & 0xCF) | usOsOn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QSȾ����ON/OFF����API
** @param	fLonRoff : Ⱦ����ON/OFF����, TRUE = ��ON��OFF, FALSE = ��OFF��ON (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			  miniLVDS�ξ�硢ȿž������QS�����ǹԤ���١�QS���꤬ȿž����ˤĤ��Ʋ��ޤ���
**			  TV���ͤȤ��Ƥϡ�����ȿž���֤Τޤޥǥ�⡼�� �Ϥ���ޤ������ǥ�⡼�ɾ��֤Τޤޱ���ȿž ��̵���١�
**			  �ɥ饤�ФȤ��Ƥϡ����Ԥξ��Τ��б�(���ߤα���ȿž���֤˱�����QS��ON/OFF�ΰ�����)���Ƥ��ޤ���
** @note
**			RegAddr:0x6408 ��bit4 ��ON���Ƥ�Τ�
*******************************************************************************/
dResult_e eFrdLcdGuSetQsHalf( flag fLonRoff )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usAB=0, usCD=0;
	
	if(!(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4)){
	/* PPDS(����ȿž������QS�θ��) */
		return S_FAILURE;
	}
	else{
	/* miniLVDS(����ȿž������QS����) */
		switch( eLcdGuTrnOvr ){
			default:
			case FRDLCD_TRN_OVR_NORMAL:
			case FRDLCD_TRN_OVR_UPSIDE_DOWN:
				if( fLonRoff == TRUE ){
					usAB = 0x10;
				}
				else{
					usCD = 0x10;
				}
				break;
			case FRDLCD_TRN_OVR_MIRROR:
			case FRDLCD_TRN_OVR_ROTATE:
				if( fLonRoff == TRUE ){
					usCD = 0x10;
				}
				else{
					usAB = 0x10;
				}
				break;
		}
	}
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x08, &usDatAB);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x08, &usDatCD);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x08, (usDatAB & 0xEF) | usAB);
	eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x08, (usDatCD & 0xEF) | usCD);
	
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
*******************************************************************************/
dResult_e eFrdLcdGuSetQsFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult;
	
	if((eInputFreq < FRD_INPUT_FREQ_48HZ) || (eInputFreq >= FRD_INPUT_FREQ_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR eInputFreq = %d\n", (int8)eInputFreq);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetQsFreqTemp(eInputFreq, ucLcdGuLvl);
	eLcdGuInputFreq = eInputFreq;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS���٥�٥�����API
** @param	ucLvl : ���ٻ��� [0(�㲹)-7(�ⲹ)] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetQsLvl( uint8 ucLvl )
{
	dResult_e eResult;
	
	if(ucLvl > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucLvl = %d\n", (int8)ucLvl);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetQsFreqTemp(eLcdGuInputFreq, ucLvl);
	ucLcdGuLvl = ucLvl;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	SBR����API
** @param	ucLvl : ���ٻ��� [0(�㲹)-7(�ⲹ)] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetSbr( uint8 ucLvl )
{
	dResult_e eResult;
	
	if(ucLvl > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR ucLvl = %d\n", (int8)ucLvl);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdGuSetSbr(eLcdGuTrnOvr, ucLvl);
	ucLcdGuLvl = ucLvl;
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM�ǡ���Ϣ³�����API
** @param	uiAddr		: ROM������襢�ɥ쥹			(�����: uint32)
** @param	usLength	: ����ߥǡ���Ĺ				(�����: uint16)
** @param	pucDats	: ����ߥǡ�������Ƭ�ݥ���	(�����: uint8*)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usBurstLen;
	uint16		usLenToNextPage;
	
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + uiLength) > uiLcdGuRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiLength = %d\n", uiLength);
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* �����ޤ�ñ�ʤ���������å� */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ��� */
	eResult |= eLcdGuRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	while(1){
		if(uiLength > LCDGU_I2C_DATA_LEN_MAX){
			usBurstLen = LCDGU_I2C_DATA_LEN_MAX;
		}
		else if(uiLength > 0){
			usBurstLen = uiLength;
		}
		else{
		/* uiLength == 0 */
			break;
		}
		
		/* ���Υڡ��������ޤǤΥХ��ȿ� */
		usLenToNextPage = LCDGU_ROM_PAGE_SIZE_2M - (uiAddr % LCDGU_ROM_PAGE_SIZE_2M);
		
		/* "usBurstLen" ���ڡ�����٤����ϡ������ޤǤ�ʬ�䤹�� */
		if(usBurstLen > usLenToNextPage) {
			usBurstLen = usLenToNextPage;
		}
		
		eResult |= eLcdGuRomWs(uiAddr, usBurstLen, pucDats);
		uiAddr += usBurstLen;
		uiLength -= usBurstLen;
		pucDats += usBurstLen;
	}
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM�ǡ���Ϣ³�ɹ���API
** @param	uiAddr		: ROM�ɹ����襢�ɥ쥹			(�����: uint32)
** @param	usLength	: �ɹ��ߥǡ���Ĺ				(�����: uint16)
** @param	pucDats		: �ɹ��ߥǡ�������Ƭ�ݥ���	(�����: uint8*)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t	atRDats[LCDGU_ROM_BURST_LEN_R];
	uint16			i;
	
	/* ��������ñ�ʤ���������å� */
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if(usLength > LCDGU_ROM_BURST_LEN_R){/* ����ž��Ĺ */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + usLength) > uiLcdGuRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* �����ޤ�ñ�ʤ���������å� */
	
	eResult = eLcdGuRomManualLoad(uiAddr, LCDGU_REGADDR_ETC +0x140, usLength, FALSE, FALSE);
	
	/* �ǡ����ɤ߹��� */
	atRDats[0].usAddr = LCDGU_REGADDR_ETC +0x140;
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, (int32)usLength, atRDats);
	for(i=0; i<usLength; i++){
		pucDats[i] = (uint8)atRDats[i].usVal;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM�ǡ����õ�API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRomErase( void )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fGetRevInfo != TRUE) return S_FAILURE;
	
	if((aucLcdGuRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0) return S_SPEC_ERROR;/* EEPROM�ξ��ϥ��顼�꥿���� */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ��� */
	eResult |= eLcdGuRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
		
	/* �񤭹��ߥ��͡��֥륳�ޥ�ɤ�ȯ�� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WREN);
	
	/* BE(Bulk Erase)���ޥ��ȯ�� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_BE);
	
	MDrv_Timer_Delayms(10000);/* Bulk Erase �λ���(8Mbit�б�������) */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdGuRomToWProtectMode(TRUE);
	
	return eResult;
}


static	uint8 aucRDats[256];
/*!
********************************************************************************
** @brief	ROM�С�����󥢥å�API
** @param	pucDats	: ROM�ǡ�������Ƭ�ݥ��� (�����: uint8 *)
** @param	fVerify	: �٥�ե�������, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetVerUp( uint8 *pucDats, flag fVerify )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiTotalLen, uiReadNum, i, j;
	uint32 uiBufLen = 0x100;
	uint8 ucRomSizeR1,ucRomSizeR2,ucRomSizeW1,ucRomSizeW2;
	
	/* Guava��Ƚ�̤���Ƥ���Ȳ��� */
	
	if(pucDats == NULL) return S_FAILURE;
	
	/* �ǡ��������� : �񤫤�Ƥ���ǡ����������ӥ����򻲾� */
	ucRomSizeR1 = aucLcdGuUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE];
	/* �ǡ��������� : �񤳤��Ȥ��Ƥ���ǡ����������ӥ����򻲾� */
	ucRomSizeW1 = pucDats[LCDGU_ROMADDR_UNIFIED_REVISION + FRDLCD_UNI_REVISION_ROM_SIZE];
	
	/* �ǡ��������� : �񤫤�Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	ucRomSizeR2 = aucLcdGuRevInfo[FRDLCD_REVISION_ROM_SIZE];
	/* �ǡ��������� : �񤳤��Ȥ��Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	ucRomSizeW2 = pucDats[LCDGU_ROMADDR_REVISION + FRDLCD_REVISION_ROM_SIZE];
#if 1
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf( 0, "ucRomSizeR1 : %0x\n", ucRomSizeR1 );
	eDbgPrintf( 0, "ucRomSizeW1 : %0x\n", ucRomSizeW1 );
	eDbgPrintf( 0, "ucRomSizeR2 : %0x\n", ucRomSizeR2 );
	eDbgPrintf( 0, "ucRomSizeW2 : %0x\n", ucRomSizeW2 );
#endif //TURNKEY1
#endif
	/* �񤭹��ߥǡ��������������� */
	if( ( ucRomSizeW1 != 0xFF ) && ( ucRomSizeW1 != 0x00 ) ){
		switch(ucRomSizeW1){
		case 0x01:/* 1M */
			uiTotalLen = 0x20000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[1M]\n" );
#endif //TURNKEY1
			break;
		case 0x02:/* 2M */
			uiTotalLen = 0x40000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[2M]\n" );
#endif //TURNKEY1
			break;
		case 0x04:/* 4M */
			uiTotalLen = 0x80000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[4M]\n" );
#endif //TURNKEY1
			break;
		case 0x08:/* 8M */
			uiTotalLen = 0x100000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[8M]\n" );
#endif //TURNKEY1
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL !! (FRDLCD_REVISION_ROM_SIZE):%0x\n", ucRomSizeW1);
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
		}

		if( ucRomSizeR1 != ucRomSizeW1 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
		if( ucRomSizeR2 != ucRomSizeW2 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
	}
	else{
	/* 8Mbit�ǡ����ǤϤʤ���� �� �����ӥ����ǥǡ���������Ƚ�� */
		/* ROM�ǡ��������� */
		switch(ucRomSizeW2){
		case 0x05:/* 512K */
			uiTotalLen = 0x10000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[512k]\n" );
#endif //TURNKEY1
			break;
		case 0x10:/* 1M */
			uiTotalLen = 0x20000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[1M]\n" );
#endif //TURNKEY1
			break;
		case 0x20:/* 2M */
			uiTotalLen = 0x40000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[2M]\n" );
#endif //TURNKEY1
			break;
		case 0x40:/* 4M */
			uiTotalLen = 0x80000;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FRDLCD_REVISION_ROM_SIZE[4M]\n" );
#endif //TURNKEY1
			break;
		default:
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL !! (FRDLCD_REVISION_ROM_SIZE):%0x\n", ucRomSizeW2);
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
		}
		
		if( ucRomSizeR1 != ucRomSizeW1 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
		
		if( ucRomSizeR2 != ucRomSizeW2 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "[Guava] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(0, "ROM WRITE is NOT executed.\n");
#endif //TURNKEY1
			return S_FAILURE;
#endif
		}
	}
	
	/* ROM����(Flash or EEPROM)��Ƚ�̡�ROM�˽񤫤�Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	if((aucLcdGuRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash �ξ�� �� ��ö���õ� */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Erase......\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRomErase();
		if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL!!(RomErase)\n" );
#endif //TURNKEY1
			return eResult;
		}
	}
	
	/* ����� */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(0, "Write......\n");
#endif //TURNKEY1
	eResult |= eFrdLcdGuRomWs(0, uiTotalLen, pucDats);
	if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Error (RomWs)\n");
#endif //TURNKEY1
		return eResult;
	}
	
	/* �٥�ե��� */
	if(fVerify == TRUE){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Verify......\n");
#endif //TURNKEY1
		uiReadNum = (uiTotalLen/uiBufLen);
		
		for(i=0; i<uiReadNum; i++){
			eFrdLcdGuRomRs(i*uiBufLen, uiBufLen, aucRDats);
			for(j=0; j< uiBufLen; j++){
				if(aucRDats[j] != pucDats[j+(uiBufLen*i)]){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
					eDbgPrintf(0, "Verify Error!! at address %0x\n", j+(uiBufLen*i));
					eDbgPrintf(0, "Verify Error!! Write Val = %0x\n", pucDats[j+(uiBufLen*i)]);
					eDbgPrintf(0, "Verify Error!! Read Val =  %0x\n", aucRDats[j]);
#endif //TURNKEY1
					return S_FAILURE;
				}
			}
			uiTotalLen -= uiBufLen;
		}
		
		if(uiTotalLen != 0){
			eFrdLcdGuRomRs(uiReadNum*uiBufLen, uiTotalLen, aucRDats);
			for(j=0; j< uiTotalLen; j++){
				if(aucRDats[j] != pucDats[j+(uiBufLen*uiReadNum)]){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
					eDbgPrintf(0, "Verify Error!! at address %0x\n", j+(uiBufLen*uiReadNum));
					eDbgPrintf(0, "Verify Error!! Write Val =  %0x\n", pucDats[j+(uiBufLen*uiReadNum)]);
					eDbgPrintf(0, "Verify Error!! Read Val =  %0x\n", aucRDats[j]);
#endif //TURNKEY1
					return S_FAILURE;
				}
			}
		}
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1		
		eDbgPrintf(0, "VERIFY SUCCESS!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	�ե꡼�������API (LCD¦)
** @param	fFreeEn	: �ե꡼�������, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	T-CON���ζ����ե꡼���ǽ����Ѥ��ޤ���
*******************************************************************************/
dResult_e eFrdLcdGuSetFreeRun( flag fFreeEn )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fFreeEn){
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x06, 0x07);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x06, 0x07);
	}else{
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x06, 0x06);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x06, 0x06);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	ROM�ޥ˥奢���������API
** @param	uiRomAddr	: ROM���ɹ����襢�ɥ쥹 (�����: uint32)
** @param	uiRegAddr	: �쥸�����ؤΥ����襢�ɥ쥹 (�����: uint32)
** @param	usByteLen	: ����Ĺ (�����: uint16)
** @param	fCrcEn		: CRC��ǧ, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn )
{
	dResult_e eResult;
	eResult = eLcdGuRomManualLoad(uiRomAddr, uiRegAddr, usByteLen, fCrcEn, TRUE);
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
********************************************************************************/
dResult_e eFrdLcdGuGetErrInfo( dFrdLcdError_t *ptError )
{
	*ptError = atLcdGuErrInfo[ ucLcdGuErrInfoOutCnt ];
	if( atLcdGuErrInfo[ ucLcdGuErrInfoOutCnt ].ucErrCode != 0 ){
		ucLcdGuErrInfoOutCnt++;
		ucLcdGuErrInfoOutCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	}
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	�ޥ˥奢��������ѥ�����¹�API(LCDC¦)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������: 
** @note
********************************************************************************/
dResult_e eFrdLcdGuAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i, j;
	
	/* ����ȿž��SBR�������� */
	for(i=0; i<4; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdLcdTrnOvr_e)i != eLcdGuTrnOvr ) || ( j != ucLcdGuLvl ) ){
				eResult |= eLcdGuSetSbr( (dFrdLcdTrnOvr_e)i, j );
			}
		}
	}
	eResult |= eLcdGuSetSbr( eLcdGuTrnOvr, ucLcdGuLvl );/* �����᤹ */
	
	
	/* QS���ȿ����ꡢQS�������� */
	for(i=0; i<3; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdInputFreq_e)i != eLcdGuInputFreq ) || ( j != ucLcdGuLvl ) ){
				eResult |= eLcdGuSetQsFreqTemp( (dFrdInputFreq_e)i, j );
			}
		}
	}
	eResult |= eLcdGuSetQsFreqTemp( eLcdGuInputFreq, ucLcdGuLvl );/* �����᤹ */
	
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
*******************************************************************************/
dResult_e eFrdLcdGuSetBdEn( flag fBdEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fBdEn){
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x50, 0);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x50, 0);
	}else{
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_DP +0x50, 1);
		eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_DP +0x50, 1);
	}
	
	return eResult;
}


#define FRD_VCOM_ADJ_VAL_MAX   		0x3FF
#define FRD_VCOM_ADJ_VAL_CENTRE		373
#define FRD_VCOM_ADJ_VAL_CENTRE60 	452
/*!
********************************************************************************
** @brief	DAC������API (VCOM������)
** @param	fMemEn : ���������� TRUE: ���꡼, FALSE: �쥸���� (�����: flag)
** @param	usDat  : VCOMĴ���ǡ��� (�����: uint16)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetDac( flag fMemEn, uint16 usDat )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp1 = 0x12, usTmp2 = 0, usCentre;
	uint8 ucCnt = 0;
	
	/* ���󥿡��� */
	//if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] == 0x60 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment
	//else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
		
	if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] <= 0x52 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment

	if( usDat <= ( FRD_VCOM_ADJ_VAL_MAX - (usCentre -64) ) ){
		usDat += (usCentre -64);
	}
	else{
		usDat = FRD_VCOM_ADJ_VAL_MAX;/* MAX�ǻߤ�� */
		eResult |= S_SPEC_ERROR;
	}
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x01, 0xe8);	/* Slv Addr */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x02, 2);		/* �С�����Ĺ */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x03, 0);		/* write */
	
	/* 0x608�Ǥ�[15:14]01�ǥ���, 10�ǥ쥸�����˥��å�, 
	   [9:8]VCOM���, [7:0]RegisterAddress(0x12) */
	if(fMemEn)	usTmp1 |= 0x4000;
	else		usTmp1 |= 0x8000;
	usTmp1 |= usDat & 0x0300;
	usTmp2 |= usDat & 0x00FF;
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, usTmp1);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x09, usTmp2);
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x2c, 1);		/* ���ޥ�ɥ����ƥ��ּ¹� */
	
	MDrv_Timer_Delayms(100);
	
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x30, &usTmp1);
		
		if((eResult == S_SUCCESS) && ((usTmp1 & 0x02) == 0x00)){
			break;
		}else{
			MDrv_Timer_Delayms(5);
		}
		ucCnt++;
		
		if(ucCnt > 15){
			eResult |= S_FAILURE;
			break;
		}
	}
	
	if(usTmp1 & 0x01){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] VCOM I2C ERROR !!\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x31, 1);
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	DAC��ǧ��API (VCOM������)
** @param	pusDat  : VCOMĴ���ǡ��� (�����: uint16 *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			������ͤ��äƤ��Ƥ����ͻҡ�
** @note
*******************************************************************************/
dResult_e eFrdLcdGuGetDac( uint16 *pusDat )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp, usCentre;
//	dFrdRegVar_t	atTmp[2];
	uint8 ucCnt = 0;
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x01, 0xe8);	/* Slv Addr */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x02, 1);		/* �С�����Ĺ */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x03, 2);		/* write */
	
//	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, 0x112);	// [7:0]VCOM RegisterAddress
	/* ��������λ���(100309 17:04)���̤���ѹ� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x08, 0x012);	// [7:0]VCOM RegisterAddress
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x2c, 1);		/* ���ޥ�ɥ����ƥ��ּ¹� */
	
	MDrv_Timer_Delayms(10);
	
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x30, &usTmp);
		
		if((eResult == S_SUCCESS) && ((usTmp & 0x04) == 0x04)){// bit2:r_rdy 1��read��λ
			break;
		}else{
			MDrv_Timer_Delayms(5);
		}
		ucCnt++;
		
		if(ucCnt > 15){
			eResult |= S_FAILURE;
			break;
		}
	}
	
	if(usTmp & 0x01){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] VCOM I2C ERROR !!\n");
#endif //TURNKEY1
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_IMC +0x31, 1);
	}else{
//		atTmp[0].usAddr = LCDGU_REGADDR_IMC +0x38;
//		eResult |= eFrdLcdGuRegRs(LCDGU_AB, 2, atTmp);
//		
//		*pusDat = ((atTmp[0].usVal & 0x03) << 8) | ((atTmp[0].usVal & 0xff00) >> 8);
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_IMC +0x38, &usTmp);
		
		*pusDat = ((usTmp & 0x03) << 8) | ((usTmp & 0xff00) >> 8);
	}
	
	/* ���󥿡����б� */
	//if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] == 0x60 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment
	//else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	
	if( aucLcdGuRevInfo[FRDLCD_REVISION_INCHI] <= 0x52 )	usCentre = FRD_VCOM_ADJ_VAL_CENTRE;//serd mby 20130116 for 70inch VCOM adjustment
	else													usCentre = FRD_VCOM_ADJ_VAL_CENTRE60;//serd mby 20130116 for 70inch VCOM adjustment

	if(*pusDat >= (usCentre -64)){
		*pusDat -= (usCentre -64);
	}else{
		*pusDat = 0;
		eResult |= S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	���ٻ���API
** @param	ucLvl : ���ٻ��� [0-255] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			1����ˡ������ǥХ����Υ����ߥ����ˤ�������0-255���ͤ�
**			��API���Ϥ��Ƥ���������
** @note
*******************************************************************************/
dResult_e eFrdLcdGuSetLvl( uint8 ucLvl )
{
	dResult_e eResult = S_SUCCESS;
	uint8 *pucCntAddr1, *pucCntAddr2;
	
	/* ����¨��ȿ�� */
	if(f1stCycle){
		eResult |= eFrdGuSetGain(ucLvl);
		eResult |= eFrdLcdGuSetQsLvl(ucLvl);
		eResult |= eFrdLcdGuSetSbr(ucLvl);
		
//		ucLcdGuLvl = ucLvl;
		
		f1stCycle = FALSE;
	}
	
	/* ľ���β��٥�٥��Ʊ�� */
	if(ucLvl == ucLcdGuLvl){
		ucNegCnt = 0;
		ucPosCnt = 0;
	}
	/* �Ѳ����� */
	else{
		/* +�������Ѳ� */
		if(ucLvl > ucLcdGuLvl){
			pucCntAddr1 = &ucNegCnt;
			pucCntAddr2 = &ucPosCnt;
		}else
		/* -�������Ѳ� */
		{
			pucCntAddr1 = &ucPosCnt;
			pucCntAddr2 = &ucNegCnt;
		}
		*pucCntAddr1 = 0;
		(*pucCntAddr2)++;
		
		/* �ǽ���Ѳ��ʹ�3��³������ȿ�� */
		if(*pucCntAddr2 > 3){
			*pucCntAddr2 = 0;
			if(pucCntAddr2 == &ucPosCnt){
				ucLcdGuLvl++;	/* ��٥�+1������ */
			}else{
				ucLcdGuLvl--;	/* ��٥�-1������ */
			}
			eResult |= eFrdGuSetGain(ucLcdGuLvl);
			eResult |= eFrdLcdGuSetQsLvl(ucLcdGuLvl);
			eResult |= eFrdLcdGuSetSbr(ucLcdGuLvl);
		}
	}
	/* �ǥХå��� */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(0, "Lvl: %d\n", ucLcdGuLvl);
#endif //TURNKEY1

	/* 1�����Typ_V_Gain������ */
	eResult |= eFrdGuSetTypvGain();
	
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
dResult_e eFrdLcdGuSetVcomPtn( flag fVcomEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fVcomEn){
		eResult |= eFrdLcdGuSetAgingPtn(0x13);
		eResult |= eFrdStandby(FALSE);
	}else{
		eResult |= eFrdLcdGuSetAgingPtn(0);
		eResult |= eFrdStandby(TRUE);
	}
	return eResult;
}


/*!	//<- 2011/02/24	�ͳ�ȯ�ɲ�
********************************************************************************
** @brief	���ϼ��ȿ��������API
** @param	eInputFreq	: ���ϼ��ȿ����� (�����: dFrdInputFreq_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note 101129 H.Nishimura: W����������ν������ɲ�(�������Ǥ�52V5����)
*******************************************************************************/
dResult_e eFrdLcdGuSetOutFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult = S_SUCCESS;
	
	if( aucLcdGuRevInfo[FRDLCD_REVISION_CPWB] & 0x10 ){

#ifdef TURNKEY1
		//�����������б�<- 2011/03/03	�ͳ�ȯ�ɲ�
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x81cd, 0x0002 );
		eI2CWrite( IIC_SLV_ADDR_TCON, 0x8005, 0x0001 );
		//-> 2011/03/03	�ͳ�ȯ�ɲ�
#endif //TURNKEY1

	/* W����������bit=1 */
		if( eInputFreq == FRD_INPUT_FREQ_48HZ ){
			eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x0E, 0x4A);
			eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x0E, 0x4A);
		}
		else{
			eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x0E, 0x23);
			eResult |= eFrdLcdGuRegW(LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x0E, 0x23);
		}
	}
	
	return eResult;
}

/*!																					//sakata20110921
********************************************************************************	//sakata20110921
** @brief	���ٻ���API																//sakata20110921
** @param	ucTemp : ���ٻ��� [0-255] (�����: uint8)								//sakata20110921
** @retval	S_SUCCESS ���ｪλ														//sakata20110921
** @retval	other ���顼������														//sakata20110921
** @par ������																	//sakata20110921
**			1����ˡ������ǥХ����Υ����ߥ����ˤ�������0-255���ͤ�				//sakata20110921
**			��API���Ϥ��Ƥ���������													//sakata20110921
** @note																			//sakata20110921
*******************************************************************************/	//sakata20110921
dResult_e eFrdLcdGuSetTemp( uint8 ucTemp )											//sakata20110921
{																					//sakata20110921
	dResult_e eResult = S_SUCCESS;													//sakata20110921
	uint8 i = 0, ucLvl;																//sakata20110921

//sakata20111013			while(ucTemp > ucAdGuTbl[eFrdLcdPnlSize][i]){								//sakata20110921
//sakata20111013				i++;																//sakata20110921
//sakata20111013				if(i == 7){															//sakata20110921
//sakata20111013					break;															//sakata20110921
//sakata20111013				}																	//sakata20110921
//sakata20111013			}																		//sakata20110921

			/* ���٥�٥������ε� */												//sakata20110921
			ucLvl = ~i & 0x07;														//sakata20110921

//			eResult |= eFrdLcdSetQsTemp(ucLvl);										//sakata20110921
			eResult |= eFrdLcdSetLvl(ucLvl);										//sakata20110921
																					//sakata20110921
	return eResult;																	//sakata20110921
}																					//sakata20110921

//-> 2011/02/24	�ͳ�ȯ�ɲ�

/**
 * @brief	���ɽ�λ��ǧ�ѻҴؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdGuChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucTimeOutCnt = 0;
	
	while(1){
		/* ROM���ɽ�λ�ӥåȤγ�ǧ */
		eResult = eFrdLcdGuRegR(LCDGU_AB, 0x01, &usDat);
		/* ROM load end�γ�ǧ */
		if((eResult == S_SUCCESS) && ((usDat & 0x04) == 0x04)){
			break;
		}
		
		ucTimeOutCnt++;
		if(ucTimeOutCnt > 15){
		/* 16��(16��15[ms])�ޤ路�Ƥ����ʾ�硢���ԤȤߤʤ��ޤ� */
			eResult |= S_FAILURE;
			break;
		}
		MDrv_Timer_Delayms(15);
	}
	
	if(eResult == S_SUCCESS){
	/* CRC ERROR�ӥåȤγ�ǧ */
		eResult |= eLcdGuChkCrcForRomLoad();
	}
	
	return eResult;
}


/**
 * @brief	����ͥ�ˤ�륢�ɥ쥹�Ѵ��Ҵؿ�(���)
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static void vAddrConv(dFrdLcdGuCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats)
{
	uint32 i;
	if(*peCh == LCDGU_CD){
		for(i=0; i<iRegNum; i++){
			*peCh = LCDGU_CD;/* �����ؿ����"LCDGU_AB"�˽񤭴������Ƥ��ޤ��١����ٸ����ᤷ�ޤ� */
			ptDats[i].usAddr = usAddrConv(peCh, ptDats[i].usAddr);
		}
	}
	return;
}


/**
 * @brief	����ͥ�ˤ�륢�ɥ쥹�Ѵ��Ҵؿ�(����)
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static uint16 usAddrConv(dFrdLcdGuCh_e *peCh, uint16 usAddr)
{
	if(*peCh == LCDGU_CD){
		/* 100121 ohashi: guava�� */
		if(usAddr < 0xA00){
		}
		else if(usAddr < 0x2000){
		/* DataPath */
			if((usAddr >= 0xA00) && (usAddr < 0xB00)){
				usAddr += 0x100;
			}
		/* CsSub */
			else if((usAddr >= 0xC00) && (usAddr < 0xD00)){
				usAddr += 0x100;
			}
		/* LCDC(SBR) */
			else if((usAddr >= 0x1000) && (usAddr < 0x1080)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x1100) && (usAddr < 0x1700)){
				usAddr += 0x600;
			}
		/* LCDC(CCK)�Ͽ��� */
			else if((usAddr >= 0x1D00) && (usAddr < 0x1DC0)){
				usAddr += 0xC0;
			}
			else if((usAddr >= 0x1E80) && (usAddr < 0x1F40)){
				usAddr += 0xC0;
			}
		}
		else if(usAddr < 0x4000){
		}
		else if(usAddr < 0x8000){
		/* GamLut */
			if((usAddr >= 0x4000) && (usAddr < 0x5200)){
				usAddr += 0x1200;
			}
		/* Decont */	
			if((usAddr >= 0x6400) && (usAddr < 0x6500)){
				usAddr += 0x100;
			}
		/* QsLut */
			else if((usAddr >= 0x6600) && (usAddr < 0x6800)){
				usAddr += 0x200;
			}
		/* TimGen */
			else if((usAddr >= 0x6A00) && (usAddr < 0x6A80)){
				usAddr += 0x80;
			}
		/* BitMap */
			else if((usAddr >= 0x6B00) && (usAddr < 0x6B80)){
				usAddr += 0x80;
			}
		/* SbrTim */
			else if((usAddr >= 0x6F00) && (usAddr < 0x6F80)){
				usAddr += 0x80;
			}
		/* SbrParam */
			else if((usAddr >= 0x7000) && (usAddr < 0x7800)){
				usAddr += 0x800;
			}
		}
		else if(usAddr < 0xC000){
			if((usAddr >= 0xA000) && (usAddr < 0xB000)){
				usAddr += 0x1000;
			}
		}
		*peCh = LCDGU_AB;
	}/* if(*peCh == LCDGU_CD) */
	
	return usAddr;
}


/**
 * @brief	ROM LOAD CRC�����å��Ҵؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdGuChkCrcForRomLoad( void )
{
	dResult_e		eResult = S_SUCCESS;
	uint16			usDat;
	dFrdRegVar_t	atDats[8];
	uint8			i, j;
	/* int_crc_error[3]: EEPROM CRC���顼(���Τ�CRC�����å�) */
	eResult = eFrdLcdGuRegR(LCDGU_AB, 0x01, &usDat);
	if(eResult == S_SUCCESS){
	/* ������Guava�����ʤΤǡ����顼���ε��ܤʤ� */
		if((usDat & 0x08) == 0x08){
			eResult = S_FAILURE;
		}
	}
	
	/* reg_load_error_flag[63:0] : �ƥ�������CRC���顼 */
	atDats[0].usAddr = LCDGU_REGADDR_ETC + 0x20;
	
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, 8, atDats);
	if(eResult == S_SUCCESS){
		for(i=0; i<8; i++){
			if(atDats[i].usVal != 0){
			/* ���顼�ξ�硢����Ĥ� */
				for(j=0; j<8; j++){
					if(atDats[i].usVal & (1<<j)){
						eLcdGuSetErrLog(2, i*8+j, 0); /* ucErrCode, ucErrBlock, usAddr */
					}
				}
				eResult = S_FAILURE;
			}
		}
	}
	
	/* init_load_error_flag[0] : Header��CRC���顼 */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x28, &usDat);
	if(eResult == S_SUCCESS){
		if((usDat & 0x01) == 0x01){
		/* ���顼�ξ�硢����Ĥ� */
			eLcdGuSetErrLog(1, 0, 0); /* ucErrCode, ucErrBlock, usAddr */
			return S_FAILURE;
		}
	}
	
	return eResult;
}


/**
 * @brief	ROM�ޥ˥奢������ѻҴؿ�
 * @param	uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn, flag fOffset )
{
	dResult_e		eResult = S_SUCCESS;
	flag			f16bit;
	uint16			usWordLen;
	dFrdRegVar_t	atSetUpDats[6];
	uint8 			ucParam = 0;
	uint16			usRDat;
	uint8			ucCnt = 0;

	f16bit = fLcdGuRegDepth16bit(uiRegAddr);
	if(f16bit)	usWordLen = (usByteLen >> 1);
	else		usWordLen =  usByteLen;
	
	eResult = eLcdGuRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if( fOffset ) uiRomAddr += uiLcdGuRomOffset;				/* ROM 8Mbit�б� */
	
	/* ���ɸ�ROM���ɥ쥹������ */
	atSetUpDats[0].usVal = (uint16)((uiRomAddr >> 8) & 0xFF);	/* ROM���ɥ쥹���[15:8] */
	atSetUpDats[1].usVal = (uint16)(uiRomAddr & 0xFF);			/* ROM���ɥ쥹����[7:0]  */
	atSetUpDats[0].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x10);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[1].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x11);	/* �쥸�������ɥ쥹���� */

	/* ������쥸�������ɥ쥹������ */
	atSetUpDats[2].usVal = (uint16)((uiRegAddr >> 8) & 0xFF);	/* ������쥸�������ɥ쥹���[15:8]  */
	atSetUpDats[3].usVal = (uint16)(uiRegAddr & 0xFF);			/* ������쥸�������ɥ쥹����[7:0] */
	atSetUpDats[2].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x12);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[3].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x13);	/* �쥸�������ɥ쥹���� */

	/* ���ɥǡ���Ĺ������ */
	atSetUpDats[4].usVal = (uint16)((usWordLen >> 8) & 0xFF);	/* �ǡ���Ĺ���[15:8]  */
	atSetUpDats[5].usVal = (uint16)(usWordLen & 0xFF);			/* �ǡ���Ĺ����[7:0] */
	atSetUpDats[4].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x14);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[5].usAddr = (uint16)(LCDGU_REGADDR_ETC +0x15);	/* �쥸�������ɥ쥹���� */

	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 6, atSetUpDats);		/* �쥸�����ؤν񤭹��� */

	/* �ޥ˥奢�����V�ե��å�OFF */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x3f, &usRDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3f, (usRDat | 1));

	/* ���ɥ�������bit���ö����� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x17, 0);

	ucParam |= ((f16bit << 1) | (fCrcEn << 2));

	/* ROM���ɥ쥹���[19:16] + CRC Enable/Disable + bit��(8bit or 16bit) + ���ɥ������ȥӥå� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x17, ((uiRomAddr >> 12) & 0xF0) | ucParam | 1);

	/* �ӥ��������å� */
	while(1){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC+0x2A, &usRDat);
		if((usRDat & 1) == 1){
//			eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] MANUAL LOAD BUSY COUNT = %d\n", ucCnt);
			break;/* Ω�äƤ���Хӥ����Ǥʤ� */
		}
		ucCnt++;
		if(ucCnt > 100){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] MANUAL LOAD ERROR !!!!!\n");
#endif //TURNKEY1
			break;
		}
		MDrv_Timer_Delayms(1);
	}
	
	/* ž�����顼(CRC���顼�ʤ�)�����å� */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC+0x29, &usRDat);
	if(usRDat & 1){
	/* ���顼�ξ�硢����Ĥ� */
		eLcdGuSetErrLog( 3, 0, (uint16)uiRegAddr ); /* ucErrCode, ucErrBlock, usAddr */
		eResult = S_FAILURE;
	}
	
	return eResult;
}


/**
 * @brief	�쥸�����ǡ�����Ƚ��Ҵؿ�
 * @param	uint32 uiAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static flag fLcdGuRegDepth16bit( uint32 uiAddr )
{
	flag f16bit = TRUE;/* ����͡�16bit�� */
	
	/* 090409 ohashi�ɲ� */
	if((uiAddr >= LCDGU_REGADDR_OSD) && (uiAddr < LCDGU_REGADDR_IMC)){
	/* 0x400-0x600 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if((uiAddr >= LCDGU_REGADDR_DP) && (uiAddr < LCDGU_REGADDR_CS_SUB)){
	/* 0xA00 - 0xC00 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if((uiAddr >= LCDGU_REGADDR_GAMLUTR) && (uiAddr < LCDGU_REGADDR_SBRPARAM)){
	/* 0x4000 - 0x7000 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if( (uiAddr >= GU_REGADDR_FRC) && (uiAddr < LCDGU_REGADDR_FSB) ){
	/* 0x8000 - 0x9000 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if( (uiAddr >= LCDGU_REGADDR_BDLUT) && (uiAddr < 0xC000) ){
	/* 0xA000 - 0xC000 */
		f16bit = FALSE;/* 8bit�� */
	}
	
	return f16bit;
}


/**
 * @brief	ROM�ؤΥ�����������STATUS�����å��Ҵؿ�
 * @param	uint16 *pusStatus
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdGuRomStatusChk( uint16 *pusStatus )
{
	uint16	  usStatus;
	uint16	  usWaitCnt = 0;
	dResult_e eResult = S_SUCCESS;
	
	while(1){
		/* ���ơ������쥸�����ɤ߹��ߥ��ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_RDSR);
		
		/* ROM �� LCDC�쥸���� ���ɤ߽Ф����֤ϡ�EEPCLK(4.6MHz)��16clk����(4us����)�ʤΤ�
		   ������Wait������ʤ��Ƥ�쥸�����ͤϳ��ꤷ�Ƥ��ޤ� */
		
		/* ���ơ������쥸�������ɤ߹��� */
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x35, &usStatus);
		if((usStatus & 0x01) != 0){/*ROM�񤭹����椫�ݤ�*/
			usWaitCnt++;
			if(usWaitCnt == 100){
				eResult = S_FAILURE;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
				eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM ACCESS TIMEOUT ERROR!!!!!!!!\n");
#endif //TURNKEY1
				break;
			}
			MDrv_Timer_Delayms(1);/* �񤭹�����ΰ١�Wait������ޤ� */
		}
		else{
			break;
		}
	}

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM STATUS REGISTER = %0x\n", usStatus);
#endif //TURNKEY1
	
	if(pusStatus != NULL){
		*pusStatus = usStatus;
	}
	return eResult;
}


/**
 * @brief	TPDA, TPDB �����ѻҴؿ�
 * @param	dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdGuSetTpDat( dFrdLcdGuCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdRegVar_t	atDats[12];
	
	atDats[0].usAddr = LCDGU_REGADDR_DP +0xD;
	
	if((ptTpda == NULL) && (ptTpdb == NULL)) return S_SPEC_ERROR;
	
	/* �������ͤ���� */
	eResult |= eFrdLcdGuRegRs(eCh, 12, atDats);
	
	/* TPDA���� */
	if(ptTpda != NULL){
		/* �����������ѹ� */
		atDats[0].usVal = (ptTpda->iTPDAR & 0xFF);
		atDats[1].usVal = (atDats[1].usVal & 0xFC) | ((ptTpda->iTPDAR >> 8) & 0x3);
		atDats[2].usVal = (ptTpda->iTPDAG & 0xFF);
		atDats[3].usVal = (atDats[3].usVal & 0xFC) | ((ptTpda->iTPDAG >> 8) & 0x3);
		atDats[4].usVal = (ptTpda->iTPDAB & 0xFF);
		atDats[5].usVal = (atDats[5].usVal & 0xFC) | ((ptTpda->iTPDAB >> 8) & 0x3);
	}
	
	/* TPDB���� */
	if(ptTpdb != NULL){
		/* �����������ѹ� */
		atDats[6].usVal  = (ptTpdb->iTPDAR & 0xFF);
		atDats[7].usVal  = (atDats[7].usVal & 0xFC) | ((ptTpdb->iTPDAR >> 8) & 0x3);
		atDats[8].usVal  = (ptTpdb->iTPDAG & 0xFF);
		atDats[9].usVal  = (atDats[9].usVal & 0xFC) | ((ptTpdb->iTPDAG >> 8) & 0x3);
		atDats[10].usVal = (ptTpdb->iTPDAB & 0xFF);
		atDats[11].usVal = (atDats[11].usVal & 0xFC) | ((ptTpdb->iTPDAB >> 8) & 0x3);
	}
	
	/* �񤭹��� */
	eResult |= eFrdLcdGuRegWs(eCh, 12, atDats);
	
	return eResult;
}


/**
 * @brief	ROM�饤�ȥץ�ƥ��ȥ⡼��ͭ��/̵���ڤ��ؤ��Ҵؿ�
 * @param	flag fWPMEn
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdGuRomToWProtectMode( flag fWPMEn )
{
	uint16		usStatus;
	uint16		usBP, usData;
	dResult_e	eResult = S_SUCCESS;
	
	eResult |= eLcdGuRomStatusChk(&usStatus);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if((usStatus & LCDGU_ROM_STATUS_SRDW) != 0){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ROM SRDW BIT HI!!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	if( uiLcdGuRomSize == LCDGU_ROMSIZE_TOTAL_2M )	usBP = LCDGU_ROM_STATUS_BP10;	/* 2MbitROM�ǡ����ξ�� */
	else  											usBP = LCDGU_ROM_STATUS_BP210;	/* 8MbitROM�ǡ����ξ�� */
	
	if(fWPMEn == TRUE)	usData = usBP;	/* �ץ�ƥ������� */
	else				usData = 0;		/* �ץ�ƥ��Ȳ������ */
	
	if((usStatus & usBP) != usData){
	/* ��˾�ξ��֤Ǥʤ���� */
		
		/* �񤭹��ߥǡ�����쥸���������� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x40, usData);	/* WDATA_START */
		
		/* �ǡ���Ĺ������(ǰ�ΰ١�����) */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x36, 1);		/* LENGTH_L */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x37, 0);		/* LENGTH_H */

		/* �񤭹��ߥ��͡��֥륳�ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WREN);

		/* ���ơ������쥸�����񤭹��ߥ��ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WRSR);
	}
	else{
	/* ��˾�ξ��֤ʤΤǡ����⤷�ޤ��� */
	}
	
	eResult |= eLcdGuRomStatusChk(&usStatus);
	
	return eResult;
}


/**
 * @brief	�Ÿ����������������Ҵؿ�
 * @param	dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	eFrdLcdGuGetRevInfo()��ɬ����˥����뤷�Ƥ���������
 * @memo	��������ROM������Ԥ�ͽ��ʤΤǡ��ܻҴؿ��ϴ���Ū�˻Ÿ���������Ǥ���
 */
static dResult_e eLcdGuGetRegionAndInchInfo( dLcdGuRegionAndInchInfo_t *ptRegionAndInchInfo )
{
	uint8 ucPnlSize = aucLcdGuRevInfo[FRDLCD_REVISION_INCHI];
	
	if(fGetRevInfo != TRUE) return S_FAILURE;

	switch(ucPnlSize){
		case 0x32:
		case 0x37:
		case 0x40:
		case 0x42:
		case 0x46:
		case 0x52:
		case 0x60:
			ptRegionAndInchInfo->eCpwbDirec  = LCDGU_CPWB_DIREC_ROTATION;
			break;
		case 0x65:
			ptRegionAndInchInfo->eCpwbDirec = LCDGU_CPWB_DIREC_NORMAL;
			break;
		case 0x70:																//��ȯ20121205
			ptRegionAndInchInfo->eCpwbDirec  = LCDGU_CPWB_DIREC_ROTATION;		//��ȯ20121205
			break;																//��ȯ20121205
		default:
			ptRegionAndInchInfo->eCpwbDirec = LCDGU_CPWB_DIREC_NORMAL;
			return S_FAILURE;
	}
	
	return S_SUCCESS;
}


/**
 * @brief	�岼����ȿž����Ҵؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e	eResult = S_SUCCESS;
	flag		fMiniL = (flag)(aucLcdGuRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	uint16		ausTmp[5];
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0xD0,&ausTmp[0]);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0xD0,&ausTmp[1]);
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x31,&ausTmp[2]);
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_DP +0x2E,&ausTmp[3]);
	eResult |= eFrdLcdGuRegR(LCDGU_CD, LCDGU_REGADDR_DP +0x2E,&ausTmp[4]);
	ausTmp[0] &= 0xFF7F;
	ausTmp[1] &= 0xFF7F;
	ausTmp[2] &= 0xFFFB;
	ausTmp[3] &= 0xFFDF;
	ausTmp[4] &= 0xFFDF;
	
	if(fMiniL == FALSE){
		/* Guava�Ǥ�PPDS���ʤ���� */
		return S_FAILURE;
	}else{
	/* miniLVDS */
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0xD0,	((aucLcdGuTrnOvr[0][eTrnOvr] << 7) | ausTmp[0]));
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_DP +0xD0,	((aucLcdGuTrnOvr[1][eTrnOvr] << 7) | ausTmp[1]));
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0x31,	((aucLcdGuTrnOvr[2][eTrnOvr] << 2) | ausTmp[2]));
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_TIMGEN +0x00,		aucLcdGuTrnOvr[3][eTrnOvr]);
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_TIMGEN +0x00,		aucLcdGuTrnOvr[4][eTrnOvr]);
		eResult |= eFrdLcdGuRegW (LCDGU_AB, LCDGU_REGADDR_DP +0x2E,	((aucLcdGuTrnOvr[5][eTrnOvr] << 5) | ausTmp[3]));
		eResult |= eFrdLcdGuRegW (LCDGU_CD, LCDGU_REGADDR_DP +0x2E,	((aucLcdGuTrnOvr[6][eTrnOvr] << 5) | ausTmp[4]));
	}
	
	return eResult;
}


/**
 * @brief	SBR����Ҵؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	�������֥�å�ȿž(SBR)�˴�Ϣ����ѥ�᡼��(SBR PARAM, SBR GHOST LUT1, LUT2, CCK LUT)
 *          ���ڤ��ؤ���ޥ˥奢����ɤǹԤ��ޤ���
 */
static dResult_e eLcdGuSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr, uiCrcAddr;
	dFrdRegVar_t atDats[3] = {{0x165d, 0x1}, {0x165e, 0x1}, {0x165f, 0x0}};/* SBR GHOST LUT UPDATE�� */
	
	/* SBR PARAM (���٥�٥���Υѥ�᡼���Ϥʤ��ʤä�) */
	eResult |= eLcdGuGetSbrParamRomAddr(eTrnOvr, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBRPARAM +0x00, LCDGU_ROMSIZE_SBRPARAM, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	/* SBR GHOST LUT1 */
	eResult |= eLcdGuGetGhostLut1RomAddr(eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* �� AB¦ */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x100, LCDGU_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* �� CD¦(AB¦��Ʊ���ǡ�������ä�CRC�ͤ�Ʊ��) */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x700, LCDGU_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	/* SBR GHOST LUT2(�� AB¦) */
	eResult |= eLcdGuGetGhostLut2RomAddr(LCDGU_AB, eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* 090416 ohashi: SIZE-10�Ǥ����Τ��ޤ����� */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0x5DA, LCDGU_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* SBR GHOST LUT2(�� CD¦) */
	eResult |= eLcdGuGetGhostLut2RomAddr(LCDGU_CD, eTrnOvr, ucLvl, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* 090416 ohashi: SIZE-10�Ǥ����Τ��ޤ����� */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_SBR +0xBDA, LCDGU_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	
	/* SBR GHOST LUT UPDATE */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 3, atDats);
	eResult |= eFrdLcdGuRegWs(LCDGU_CD, 3, atDats);

#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif

	return eResult;
}

#ifdef DEBUG_LCDGU_MANULOAD_SBR
/**
 * @brief	MNL�ǥХå����ϻҴؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static void vLcdGuDbgMnl( void )
{
	uint16 usReadData;
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] CRC_EXP_VAL  = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x2B, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] CRC_CALC_VAL = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x29, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava][MANUAL LOAD] ERROR BIT    = %0x\n", usReadData);
#endif //TURNKEY1
	return;
}
#endif

/**
 * @brief	SBR PARAM�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_SBRPARAM;
	uint32		uiCrcAddr	= 0x210;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += LCDGU_ROMSIZE_SBRPARAM;
			uiCrcAddr += 1;
			break;
		default:
			break;
	}
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT1�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_GHOSTLUT1;
	uint32		uiCrcAddr	= 0x230;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ( LCDGU_ROMSIZE_GHOSTLUT1 * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDGU_ROMSIZE_GHOSTLUT1 * ucLvl);
	uiCrcAddr += ucLvl;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT2�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdArCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuGetGhostLut2RomAddr( dFrdLcdGuCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr)
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_GHOSTLUT2;
	uint32		uiCrcAddr	= 0x240;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_NORMAL:
			break;
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
			uiRomAddr +=  (LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8);
			uiCrcAddr += (2*8);
			break;
		case FRDLCD_TRN_OVR_MIRROR:
			uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8) * 2);
			uiCrcAddr += ((2*8) * 2);
			break;
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * 8) * 3);
			uiCrcAddr += ((2*8) * 3);
			break;
		default:
			break;
	}
	
	uiRomAddr += ((LCDGU_ROMSIZE_GHOSTLUT2 * 2 * ucLvl) + (LCDGU_ROMSIZE_GHOSTLUT2 * eCh));
	uiCrcAddr += ((2 * ucLvl) + eCh);
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	QS ���ȿ������������ѻҴؿ�
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucLvl
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucLvl )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] QS FREQ = %0d\n", eInputFreq);
	eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] QS TEMP = %0d\n", ucLvl);
#endif //TURNKEY1

	eResult = eLcdGuGetQsLutRomAddr(eInputFreq, ucLvl, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdGuRomManualLoad(uiCrcAddr, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);						/* CRC�ͤ�ž�� */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_QSLUT +0x00, LCDGU_ROMSIZE_QSLUT, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDGU_MANULOAD_QS
	vLcdGuDbgMnl();
#endif

	return eResult;
}


/**
 * @brief	QS LUT�ޥ˥奢������ѻҴؿ�
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucLvl, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDGU_ROMADDR_QSLUT;
	uint32		uiCrcAddr	= 0x200;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_60HZ:
			uiRomAddr += (LCDGU_ROMSIZE_QSLUT * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDGU_ROMSIZE_QSLUT * ucLvl);
	uiCrcAddr += ucLvl;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	���顼�������ѻҴؿ�
 * @param	uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usCrcCal, usCrcExp;
	
	if( ucErrCode == 1 ){
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x06, &usCrcExp);/* CRC������(�إå����ɻ�) */
	}
	else{
		eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usCrcExp);/* CRC������(�ޥ˥奢����ɻ�) */
	}
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x2B, &usCrcCal);/* CRC�黻�� */
	
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucErrCode		= ucErrCode;		/* ���顼������  */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucErrBlock	= ucErrBlock;		/* ���ɥ��顼�֥�å��ֹ� */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].usAddr		= usAddr;			/* �б��쥸�������ɥ쥹 */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucCrcExp		= (uint8)usCrcExp;	/* CRC������ */
	atLcdGuErrInfo[ ucLcdGuErrInfoInCnt ].ucCrcCal		= (uint8)usCrcCal;	/* CRC�黻�� */
	
	ucLcdGuErrInfoInCnt++;
	ucLcdGuErrInfoInCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	
	return eResult;
}


/**
 * @brief	ROM�񤭹����ѻҴؿ�
 * @param	uint32 uiAddr, uint16 usLength, uint8 *pucDats
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats )
{
	dResult_e		eResult;
	dFrdRegVar_t	atSetUpDats[4];
	dFrdRegVar_t	atWDats[LCDGU_ROM_BURST_LEN_W];
	int i;
	
	/* ��������ñ�ʤ���������å� */
	if(usLength > LCDGU_ROM_BURST_LEN_W)				return S_SPEC_ERROR;
	if(usLength > LCDGU_ROM_PAGE_SIZE_2M)				return S_SPEC_ERROR;
#ifndef LCDGU_ROM_SIZE_ERROR_BYPASS
	if((uiAddr + usLength) > uiLcdGuRomSize)			return S_SPEC_ERROR;
#endif
	/* �����ޤ�ñ�ʤ���������å� */
	
	eResult = eLcdGuRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	atSetUpDats[0].usVal = LCDGU_ROM_CMD_WREN;			/* �񤭹��ߥ��͡��֥����� */
	atSetUpDats[1].usVal = (uiAddr & 0xFF);				/* ROM���ɥ쥹���� */
	atSetUpDats[2].usVal = ((uiAddr >> 8) & 0xFF);		/* ROM���ɥ쥹��� */
	atSetUpDats[3].usVal = ((uiAddr >> 16) & 0xFF);		/* ROM���ɥ쥹���  */
	for(i=0; i<4; i++){
		atSetUpDats[i].usAddr = LCDGU_REGADDR_ETC +0x30 +i;	/* �쥸�������ɥ쥹���� */
	}
	/* WREN���ޥ�ɡ�ROM���ɥ쥹������ */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 4, atSetUpDats);
	
	atSetUpDats[0].usVal = (usLength & 0xFF);			/* �񤭹��ߥǡ���Ĺ���� */
	atSetUpDats[1].usVal = ((usLength >> 8) & 0xFF);	/* �񤭹��ߥǡ���Ĺ��� */
	atSetUpDats[0].usAddr = LCDGU_REGADDR_ETC +0x36;	/* �쥸�������ɥ쥹���� */
	atSetUpDats[1].usAddr = LCDGU_REGADDR_ETC +0x37;	/* �쥸�������ɥ쥹���� */
	/* �ǡ���Ĺ������ */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, 2, atSetUpDats);
	
	for(i=0; i<usLength; i++){
		atWDats[i].usVal  = (uint16)pucDats[i];			/* �񤭹��ߥǡ������� */
		atWDats[i].usAddr = LCDGU_REGADDR_ETC +0x40 +i;	/* �쥸�������ɥ쥹���� */
	}
	
	/* �񤭹��ߥǡ����Хåե������� */
	eResult |= eFrdLcdGuRegWs(LCDGU_AB, usLength, atWDats);
	
	/* WRITE���ޥ��ȯ�� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x30, LCDGU_ROM_CMD_WRITE);
	
	return eResult;
}


/**
 * @brief	������ѻҴؿ�
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuReloadAll( uint8 ucPnlSizeNo )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usAddr = ucPnlSizeNo * 4;
	uint16		usDat;
	
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3A, 0x01 );				/* ����ɥ��ɥ쥹��� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x3B, usAddr );			/* ����ɥ��ɥ쥹��� */
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, &usDat);
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, (usDat & 0x7F));	/* ����ɥӥåȢ��� */
	eResult |= eFrdLcdGuRegW(LCDGU_AB, LCDGU_REGADDR_ETC +0x39, (usDat | 0x80));	/* ����ɥӥåȢ��� */
	
	MDrv_Timer_Delayms(20);																/* ���ɻ��֤γ���(��¬) */
	
	return eResult;
}


/**
 * @brief	Revision�ǡ����ɤ߹����ѻҴؿ�
 * @param	uint8 *pucRevInfo, uint32 uiRomAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdGuGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr )
{
	dResult_e	 eResult = S_SUCCESS;
	dFrdRegVar_t atRDat[FRDLCD_REVISION_DATA_MAX-1];
	uint16		 usCrcExp, i;
	
	if(pucRevInfo == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDGU_DBG_LEVEL, "[Guava] ERROR pucRevInfo = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult |= eLcdGuRomManualLoad(uiRomAddr +0xF, LCDGU_REGADDR_ETC +0x16, 1, FALSE, TRUE);					/* CRC�ͤ�ž�� */
	eResult |= eLcdGuRomManualLoad(uiRomAddr, LCDGU_REGADDR_ETC +0x140, FRDLCD_REVISION_DATA_MAX-1, TRUE, TRUE);/* �ǡ�����ž�� */
#ifdef DEBUG_LCDGU_MANULOAD_SBR
	vLcdGuDbgMnl();
#endif
	/* �ǡ����ɤ߹��� */
	atRDat[0].usAddr = LCDGU_REGADDR_ETC +0x140;
	eResult |= eFrdLcdGuRegRs(LCDGU_AB, FRDLCD_REVISION_DATA_MAX-1, atRDat);
	for(i=0; i<FRDLCD_REVISION_DATA_MAX-1; i++){
		pucRevInfo[i] = (uint8)atRDat[i].usVal;
	}
	
	eResult |= eFrdLcdGuRegR(LCDGU_AB, LCDGU_REGADDR_ETC +0x16, &usCrcExp);
	pucRevInfo[FRDLCD_REVISION_DATA_MAX-1] = (uint8)usCrcExp;
	
	return eResult;
}
/* end of file */
