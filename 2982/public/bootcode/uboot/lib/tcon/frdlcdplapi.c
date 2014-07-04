/**
 * @file frdlcdplapi.c
 *
 * @brief PlaiceLCD������
 *
 * Copyright (c) 2009 SHARP CORPORATION
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
#include <tcon/frdlcdplapi.h>
#include <tcon/frdplapi.h>

/* Lib Functions */
#include <tcon/Internal_RegistrationFunction.h>

/* **
 * ** define
 * **/

#define FRDLCD_BUG_FIX1/* ��ư�������۾��к� 2009.08.20 */

/* RomAddr */
#define LCDPL_ROMADDR_REVISION	0x2F0
#define LCDPL_ROMADDR_UNIFIED_REVISION	0x3FFF0
#define LCDPL_ROMADDR_SBRPARAM	0xC100
#define LCDPL_ROMADDR_GHOSTLUT1	0x2C100
#define LCDPL_ROMADDR_GHOSTLUT2	0x35C80
#define LCDPL_ROMADDR_QSLUT		0x08100
#define LCDPL_ROMADDR_UVLMODE	0x7700
#define LCDPL_ROMADDR_NRMODE	0x1060

#define LCDPL_ROMSIZE_SBRPARAM	0x2000
#define LCDPL_ROMSIZE_GHOSTLUT1	0x09B8
#define LCDPL_ROMSIZE_GHOSTLUT2	272
#define LCDPL_ROMSIZE_QSLUT		0x400
#define LCDPL_ROMSIZE_UVLMODE	0x80
#define LCDPL_ROMSIZE_NRMODE	0x10

/* ROM���� */
#define LCDPL_ROMSIZE_TOTAL_8M		0x100000/* 8Mbit */
#define LCDPL_ROMSIZE_TOTAL_2M		0x40000	/* 2Mbit */
#define LCDPL_ROM_PAGE_SIZE_2M		256		/* 2Mbit */

/* ROM���ơ������쥸���� */
#define LCDPL_ROM_STATUS_WIP		0x01	/* Write In Progress */
#define LCDPL_ROM_STATUS_WEL		0x02	/* Write Enable Latch */
#define LCDPL_ROM_STATUS_BP10		0x0C	/* Block Protect(BP0, BP1) */
#define LCDPL_ROM_STATUS_BP210		0x1C	/* Block Protect(BP0, BP1, BP2) */
#define LCDPL_ROM_STATUS_SRDW		0x80	/* Status Register Write Disable */

#define LCDPL_ROM_BURST_LEN_W		256		/* ROM�С����ȥ饤���ѥХåե�(LCDC�쥸����)Ĺ */
#define LCDPL_ROM_BURST_LEN_R		256		/* ROM�С����ȥ꡼���ѥХåե�(LCDC�쥸����)Ĺ */

/* SPI���ޥ����� */
#define LCDPL_ROM_CMD_WRSR			1		/* ���ơ������쥸�����ؤν񤭹��� */
#define LCDPL_ROM_CMD_WRITE			2		/* �ǡ����񤭹��� */
#define LCDPL_ROM_CMD_READ			3		/* �ǡ����ɤ߹��� */
#define LCDPL_ROM_CMD_WRDI			4		/* �񤭹��߶ػ߾��֤ˤ��� */
#define LCDPL_ROM_CMD_RDSR			5		/* ���ơ������쥸�������ɤ߹��� */
#define LCDPL_ROM_CMD_WREN			6		/* �񤭹��߲�ǽ�ˤ��� */
#define LCDPL_ROM_CMD_SE			0xD8	/* Sector Erase */
#define LCDPL_ROM_CMD_BE			0xC7	/* Bulk Erase */

#define LCDPL_EVA_PTN_NUM_MAX		0x12
#define LCDPL_AGI_PTN_NUM_MAX		0x21

#define LCDPL_I2C_DATA_LEN_MAX 		96		/* I2C�쥸����ž������Ĺ���(iic.h�Ǥ� MAX_DATAS �����(����256)�ˤ��) */


#if 0/* ROM���������顼�����å���̵���ˤ���Ȥ���'1'�ˤ��� */
#define LCDPL_ROM_SIZE_ERROR_BYPASS
#endif

/* **
 * ** typedef
 * **/

/* **
 * ** variable
 * **/
/* static const�ѿ� */
static const dFrdLcdTrnOvr_e aeLcdPlConvTrnOvr[LCDPL_CPWB_DIREC_NUM][FRDLCD_TRN_OVR_NUMMAX] =
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
static const uint8 aucLcdPlTestPtnTbl[FRDLCD_TESTPTN_NUMMAX] =
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
	LCDPL_AGI_PTN_NUM_MAX + 0xA,				/* ����ɡ����󥰥ѥ�����(ɾ���ѥѥ�����) */
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
	LCDPL_AGI_PTN_NUM_MAX + 0x1,				/* ��Υ���ɽ�� */
	LCDPL_AGI_PTN_NUM_MAX + 0x2,				/* ��Ĵ�ƥ���ɽ�� */
	LCDPL_AGI_PTN_NUM_MAX + 0x3,				/* �٥�ɽ�� */
	LCDPL_AGI_PTN_NUM_MAX + 0x4,				/* �ĥ��ȥ饤�� */
	LCDPL_AGI_PTN_NUM_MAX + 0x5,				/* ��ʿ�������졼�������� */
	LCDPL_AGI_PTN_NUM_MAX + 0x6,				/* ��ľ�������졼�������� */
	LCDPL_AGI_PTN_NUM_MAX + 0x7,				/* ���顼���㡼�� */
	LCDPL_AGI_PTN_NUM_MAX + 0x8,				/* �ե�å��ѥ����� */
	LCDPL_AGI_PTN_NUM_MAX + 0x9,				/* �ե�å��ѥ����� */
	LCDPL_AGI_PTN_NUM_MAX + 0xB,				/* A/DĴ���ѥѥ����� */
	LCDPL_AGI_PTN_NUM_MAX + 0xC,				/* �岼ʬ��٥� */
	LCDPL_AGI_PTN_NUM_MAX + 0xD,				/* ����ʬ��٥� */
	LCDPL_AGI_PTN_NUM_MAX + 0xE,				/* �饤��ȿž�ѥե�å��ѥ����� */
	LCDPL_AGI_PTN_NUM_MAX + 0xF,				/* ����ѥ����� */
	LCDPL_AGI_PTN_NUM_MAX + 0x10,				/* 1�饤��ɽ���ѥ�����(Zucchini) */
	LCDPL_AGI_PTN_NUM_MAX + 0x11				/* 1��ɽ���ѥ�����(Zucchini) */
};

/****************/
/* ����ȿž���� */
/****************/
/* PPDS */
static const uint16 aucLcdPlTrnOvrPpds[10][FRDLCD_TRN_OVR_NUMMAX] = {
/* PNL  0x300 or 0x301 */	{0x00E4, 0xF04E, 0x00E4, 0xF04E},
/* PNL  0x2003or0x200C */	{0x0020, 0x002A, 0x0020, 0x002A},
/* PNL  0x2004or0x200D */	{0x0006, 0x0000, 0x0006, 0x0000},
/* PNL  0x2005or0x200E */	{0x0050, 0x0056, 0x0050, 0x0056},

/* LCDC 0x6A00(AB) */		{0x0081, 0x0081, 0x0083, 0x0083},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0001, 0x0003, 0x0003},
/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
};

/* miniLVDS */
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* ���Υѥͥ� */
static const uint16 aucLcdPlTrnOvrMiniL[13][FRDLCD_TRN_OVR_NUMMAX] = {
/* LCDC 0x6400 */			{0x0040, 0x0042, 0x0040, 0x0042},
/* LCDC 0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},

/* LCDC 6404[6]/6504[6] */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 6404[5]/6504[5] */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x6427(AB&414) */	{0x0014, 0x0090, 0x0014, 0x0090},
/* LCDC 0x6428(AB&414) */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 0x6527(CD&414) */	{0x0090, 0x0014, 0x0090, 0x0014},
/* LCDC 0x6528(CD&414) */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
#else
static const uint16 aucLcdPlTrnOvrMiniL[11][FRDLCD_TRN_OVR_NUMMAX] = {
/* LCDC 0x6400 */			{0x0040, 0x0042, 0x0040, 0x0042},
/* LCDC 0x6A00(AB) */		{0x0081, 0x0085, 0x0083, 0x0087},
/* LCDC 0x6A80(CD) */		{0x0001, 0x0005, 0x0003, 0x0007},

/* LCDC 0x6427(AB&414) */	{0x001A, 0x008A, 0x001A, 0x008A},
/* LCDC 0x6428(AB&414) */	{0x0001, 0x0000, 0x0001, 0x0000},
/* LCDC 0x6527(CD&414) */	{0x008A, 0x001A, 0x008A, 0x001A},
/* LCDC 0x6528(CD&414) */	{0x0000, 0x0001, 0x0000, 0x0001},

/* LCDC 0x642E(AB) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x652E(CD) */		{0x0000, 0x0001, 0x0000, 0x0001},	/* bit5 �Τ� */
/* LCDC 0x64D0(AB) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
/* LCDC 0x65D0(CD) */		{0x0000, 0x0000, 0x0001, 0x0001},	/* bit7 �Τ� */
#endif
};

/* static�ѿ� */
static uint8 aucLcdPlRevInfo[FRDLCD_REVISION_DATA_MAX];			/* ROM Revision�ǡ�����¸������ */
static uint8 aucLcdPlUnifiedRevInfo[FRDLCD_REVISION_DATA_MAX];	/* ROM Revision(����)�ǡ�����¸������ */
static dLcdPlRegionAndInchInfo_t tRegionAndInchInfo;/* �Ÿ����������������������¸���ѿ� */

static flag				fGetRevInfo		= FALSE;
static flag				fKmBypass		= TRUE;
static dFrdLcdTrnOvr_e	eLcdPlTrnOvr	= FRDLCD_TRN_OVR_NORMAL;
static dFrdInputFreq_e	eLcdPlInputFreq	= FRD_INPUT_FREQ_60HZ;
static uint8			ucLcdPlTemp		= 4;
static uint8			ucLcdPlUvlMode	= 7;
/* 090608 ohashi */
static dFrdLcdPnlSize_e	eLcdPlPnlSize	= FRDLCD_PNL_32;	/* �������� */

static dFrdLcdError_t		atLcdPlErrInfo[FRDLCD_ERR_LOG_NUM_MAX];
static uint8				ucLcdPlErrInfoInCnt  = 0;
static uint8				ucLcdPlErrInfoOutCnt = 0;

static uint8			ucLcdPlPnlSizeNo	= 0;/* 8Mbit ROM�б� : 0:32��,  1:40��,  2:46��,  3:52��  */
static uint32			uiLcdPlRomOffset	= 0;/*               : 0x00000, 0x40000, 0x80000, 0xC0000 */
static uint32			uiLcdPlRomSize		= LCDPL_ROMSIZE_TOTAL_8M;

/* **
 * ** prototype
 * **/
static dResult_e eLcdPlChkRomLoadEnd( void );
static void vAddrConv(dFrdLcdPlCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats);
static uint16 usAddrConv(dFrdLcdPlCh_e *peCh, uint16 usAddr);
static dResult_e eLcdPlChkCrcForRomLoad( void );
static dResult_e eLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn , flag fOffset);
static flag fLcdPlRegDepth16bit( uint32 uiAddr );
static dResult_e eLcdPlRomStatusChk( uint16 *pusStatus );
static dResult_e eLcdPlSetTpDat( flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb );
static dResult_e eLcdPlRomToWProtectMode( flag fWPMEn );
static dResult_e eLcdPlGetRegionAndInchInfo( dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo );
static dResult_e eLcdPlSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr );
static dResult_e eLcdPlSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp );
#ifdef DEBUG_LCDPL_MANULOAD_SBR
static void vLcdPlDbgMnl( void );
#endif
static dResult_e eLcdPlGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlGetGhostLut2RomAddr( dFrdLcdPlCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr);
static dResult_e eLcdPlSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucTemp );
static dResult_e eLcdPlGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats );
static dResult_e eLcdPlSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr );
static dResult_e eLcdPlGetUvlModeRomAddr( uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlReloadAll( uint8 ucPnlSizeNo );					/* 8Mbit ROM�б� */
static dResult_e eLcdPlGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr );	/* 8Mbit ROM�б� */
static dResult_e eLcdPlGetNrModeRomAddr( dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr );
static dResult_e eLcdPlInitSkinCtlLut( void );
dResult_e eFrdLcdPlVerify( uint32 uiRomAddr, uint16 usRegAddr, uint16 usLen );
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
dResult_e eFrdLcdPlRegWs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
{
	dResult_e	eResult = S_SUCCESS;
#ifdef TURNKEY1
	uint32 i;
	uint16 tmp_addr;
#else //TURNKEY1
	const void	*pvDevice;
#endif //TURNKEY1
	
	vAddrConv(&eCh, iRegNum, ptDats);
	
#ifdef TURNKEY1
	for( i=0; i<iRegNum; i++ )
	{
		tmp_addr = ptDats[0].usAddr + (uint16)i;
		eResult = eI2CWrite( IIC_SLV_ADDR_TCON, tmp_addr, ptDats[i].usVal);
		
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
dResult_e eFrdLcdPlRegRs( dFrdLcdPlCh_e eCh, int32 iRegNum, dFrdRegVar_t * ptDats )
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
dResult_e eFrdLcdPlRegW( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 usVal )
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
dResult_e eFrdLcdPlRegR( dFrdLcdPlCh_e eCh, uint16 usAddr, uint16 *pusVal )
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
	printf("In eFrdLcdPlRegR, IIC_SLV_ADDR_TCON=%x\r\n",IIC_SLV_ADDR_TCON);
	printf("In eFrdLcdPlRegR, tData.usAddr=%x\r\n",tData.usAddr);
	printf("In eFrdLcdPlRegR, &(tData.usVal)=%x\r\n",&(tData.usVal));
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
** @brief	�ѥͥ륵����������API
** @param	ePnlSize	: �ѥͥ륵��������(�����: dFrdLcdPnlSize_e)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	ɬ�� eFrdLcdPlChkRomLoadEnd �����˸Ƥ֤���
*******************************************************************************/
dResult_e eFrdLcdPlSetSize( dFrdLcdPnlSize_e ePnlSize )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ���ե��å����� */
	switch( ePnlSize ){
		case FRDLCD_PNL_32:
			ucLcdPlPnlSizeNo = 0;
			break;
		case FRDLCD_PNL_40:
			ucLcdPlPnlSizeNo = 1;
			break;
		case FRDLCD_PNL_46:
			ucLcdPlPnlSizeNo = 2;
			break;
		case FRDLCD_PNL_52:
			ucLcdPlPnlSizeNo = 3;
			break;
		case FRDLCD_PNL_60:
			ucLcdPlPnlSizeNo = 0;
			break;
		default:
			ucLcdPlPnlSizeNo = 0;
			eResult = S_SPEC_ERROR;
			break;
	}
	eLcdPlPnlSize = ePnlSize;
	
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
dResult_e eFrdLcdPlGetSize( dFrdLcdPnlSize_e *pePnlSize )
{
	*pePnlSize = eLcdPlPnlSize;
	
	return S_SUCCESS;
}


/*!
********************************************************************************
** @brief	ROM�������ｪλ�����å�API
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note	ɬ�� eFrdLcdPlSetSize ����˸Ƥ֤���
*******************************************************************************/
dResult_e eFrdLcdPlChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	dResult_e	eResultTmp;
	
#ifdef FRDLCD_BUG_FIX1/* ��ư�������۾��к� 2009.08.20 */
	MDrv_Timer_Delayms(20);
#endif
	
	/* �����ɤΥ��ɽ�λ��ǧ */
	eResult |= eLcdPlChkRomLoadEnd();
	
	/* �����ӥ����μ��� */
	eResultTmp = eLcdPlGetRevInfo( aucLcdPlUnifiedRevInfo, LCDPL_ROMADDR_UNIFIED_REVISION );
	if( aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE] == 0x08 ){
	/* ROM��8Mbit�ǡ��� */
		
		/* 8Mbit��Ƚ�̤��줿�����ǡ�Offset�ͤ����ꤹ�� */
		uiLcdPlRomOffset = ucLcdPlPnlSizeNo * LCDPL_ROMSIZE_TOTAL_2M;
		
		/* �ѥͥ륵�������б�����ǡ���2Mbit������All */
		eResult |= eLcdPlReloadAll( ucLcdPlPnlSizeNo );
		
		/* �����ܥ��ɤΥ��ɽ�λ��ǧ */
		eResult |= eLcdPlChkRomLoadEnd();
		
		eResult |= eResultTmp;
		
		uiLcdPlRomSize = LCDPL_ROMSIZE_TOTAL_8M;
	}
	else{
	/* ROM��2Mbit�ǡ��� �� �����ɤΤߤ��ɲý�����ɬ��̵�� */
		uiLcdPlRomOffset = 0;
		uiLcdPlRomSize = LCDPL_ROMSIZE_TOTAL_2M;
#ifdef FRDLCD_BUG_FIX1/* ��ư�������۾��к� 2009.08.20 */
		/* �ѥͥ륵�������б�����ǡ���2Mbit������All */
		eResult |= eLcdPlReloadAll( 0 );
		
		/* �����ܥ��ɤΥ��ɽ�λ��ǧ */
		eResult |= eLcdPlChkRomLoadEnd();
#endif
	}
	
	/* �������̥�ӥ����μ��� */
	eResult |= eLcdPlGetRevInfo( aucLcdPlRevInfo, LCDPL_ROMADDR_REVISION );
	
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
dResult_e eFrdLcdPlGetRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdPlRevInfo[i];
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
dResult_e eFrdLcdPlGetRevStr( int8 *pcRevInfo )
{
	int8 acPanelType[] = "FM";/* FM ��MiniLVDS�ѥͥ� */
	int8 cFrcType;
//sakata20110920 warning_erase	int8 cTestVer = 'T';
	
	if( pcRevInfo == NULL ) return S_SPEC_ERROR;
	
	if( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M ){
	/* 2Mbit�ǡ��� */
		if(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4){
		/* MiniLVDS */
		}
		else{
		/* PPDS */
			switch (aucLcdPlRevInfo[FRDLCD_REVISION_PANEL])
			{
				case 0x00: acPanelType[1] = 'S'; break;/* �ҽФ� */
				case 0x01: acPanelType[1] = 'D'; break;/* ξ�Ф� */
				default:   acPanelType[1] = '?'; break;/* ���� */
			}
		}
		switch (aucLcdPlRevInfo[FRDLCD_REVISION_FRC]){
			case 0x00: cFrcType = 'E'; break;/* Easter */
			case 0x01: cFrcType = 'F'; break;/* Fraser */
			case 0x02: cFrcType = 'Y'; break;/* Yellowtail */
			case 0x04: cFrcType = 'A'; break;/* Arugula */
			case 0x05: cFrcType = 'P'; break;/* Plaice */
			default:   cFrcType = '?'; break;/* ���� */
		}
		if( aucLcdPlRevInfo[FRDLCD_REVISION_VER] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �ƥ��ȥС������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%c%02X",
					aucLcdPlRevInfo[FRDLCD_REVISION_YEAR_L],/* ǯ */
					aucLcdPlRevInfo[FRDLCD_REVISION_MONTH],	/* �� */
					aucLcdPlRevInfo[FRDLCD_REVISION_DAY],	/* �� */
					acPanelType,							/* �ѥͥ��ư���� */
					cFrcType,								/* T-CON�ǥХ��� */
					aucLcdPlRevInfo[FRDLCD_REVISION_INCHI],	/* ����������� */
					aucLcdPlRevInfo[FRDLCD_REVISION_MISC],	/* ��ǥ� */
					cTestVer,
					aucLcdPlRevInfo[FRDLCD_REVISION_VER] & 0x7F	/* �С������ */
				);
#endif //TURNKEY1
		}
		else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �����С������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%s%c%02X%02X%02X",
					aucLcdPlRevInfo[FRDLCD_REVISION_YEAR_L],/* ǯ */
					aucLcdPlRevInfo[FRDLCD_REVISION_MONTH],	/* �� */
					aucLcdPlRevInfo[FRDLCD_REVISION_DAY],	/* �� */
					acPanelType,							/* �ѥͥ��ư���� */
					cFrcType,								/* T-CON�ǥХ��� */
					aucLcdPlRevInfo[FRDLCD_REVISION_INCHI],	/* ����������� */
					aucLcdPlRevInfo[FRDLCD_REVISION_MISC],	/* ��ǥ� */
					aucLcdPlRevInfo[FRDLCD_REVISION_VER]	/* �С������ */
				);
#endif //TURNKEY1
		}
	}
	else{
	/* 8Mbit�ǡ��� */
		if( aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x80 ){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		/* �ƥ��ȥС������ */
			sprintf((char *)pcRevInfo,
					"%02X%02X%02X%02X%02X%c%02X%02X",
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* ǯ */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* �� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* �� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* �Ÿ��� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* ��ǥ� */
					cTestVer,									/* �ƥ��ȥС������ */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H] & 0x7F,	/* �С�������ֹ�(H) */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* �С�������ֹ�(L) */
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
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L],/* ǯ */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH],	/* �� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DAY],	/* �� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_DEST],	/* �Ÿ��� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MODEL],	/* ��ǥ� */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_H],	/* �С�������ֹ�(H) */
					aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_VER_L]	/* �С�������ֹ�(L) */
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
dResult_e eFrdLcdPlGetUnifiedRevInfo( uint8 *pucRevInfo )
{
	uint8 i;
	
	if( pucRevInfo == NULL ) return S_SPEC_ERROR;
	
	for(i=0; i<FRDLCD_REVISION_DATA_MAX; i++){
		pucRevInfo[i] = aucLcdPlUnifiedRevInfo[i];
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
dResult_e eFrdLcdPlInit( void )
{
	dResult_e eResult = S_SUCCESS;
	
	/* ROM��饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
	/* �Ÿ�������������������� */
	eResult |= eLcdPlGetRegionAndInchInfo(&tRegionAndInchInfo);
	if(eResult != S_SUCCESS ) return eResult;
	
	/* �������к� */
	eResult |= eFrdLcdPlChgGamLut(TRUE);
	
	/* ȩ������LUT�񴹤� (��ӥ��������ROM�ޤǤ��Ф�) */
	if(uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_8M){
		if((aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_YEAR_L] <= 0x09) && (aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_MONTH] <= 0x06)){
			eResult |= eLcdPlInitSkinCtlLut();
		}else{
			;;
		}
	}else{
		;;
	}
	
	/* static�ѿ��ν�������� */
	eLcdPlTrnOvr	= aeLcdPlConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][FRDLCD_TRN_OVR_NORMAL];
	eLcdPlInputFreq	= FRD_INPUT_FREQ_60HZ;
	ucLcdPlTemp		= 4;
	ucLcdPlUvlMode	= 7;
	/* 090519 ohashi: �����ǽ�������٤����񤷤��Ȥ��� */
	fKmBypass		= TRUE;

#ifdef FRDLCD_BUG_FIX1/* ��ư�������۾��к� 2009.08.20 */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, 0x87 );/* Gamma LUT�إ��� */
#endif

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
dResult_e eFrdLcdPlSetTrnOvr( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e eResult = S_SUCCESS;
	
	if(eTrnOvr >= FRDLCD_TRN_OVR_NUMMAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eTrnOvr = %d\n", (int8)eTrnOvr);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eTrnOvr = aeLcdPlConvTrnOvr[tRegionAndInchInfo.eCpwbDirec][eTrnOvr];
	
	eResult |= eLcdPlSetTrnOvrReg(eTrnOvr);
	
	eResult |= eLcdPlSetSbr(eTrnOvr, ucLcdPlTemp);
	
	eLcdPlTrnOvr = eTrnOvr;
	
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
dResult_e eFrdLcdPlSetOutput( flag fOutEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usDatAB, usDatCD;
	flag		fMiniL = (flag)(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	
	if(fMiniL){
	/* miniLVDS */
		/* LS����Hi-Z��� (default��1�Ǥʤ��Ȳ���Ǥ��ʤ�??) */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x2B, 0);
		
		/* ODS�ǡ������ϥߥ塼��ON/OFF */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, &usDatAB);
		eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, &usDatCD);
		if(fOutEn){
		/* �ߥ塼��OFF(���) �� bit4 �� 0 */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, usDatAB & 0xEF);
			eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, usDatCD & 0xEF);
		}else{
		/* �ߥ塼��ON �� bit4 �� 1 */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, usDatAB | 0x10);
			eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, usDatCD | 0x10);
		}
	}
	else{
	/* PPDS */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, &usDat);
		if(fOutEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, ((usDat & 0xFFFE) | 1));
		else		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PNL +0x06, ((usDat & 0xFFFE) | 0));
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
dResult_e eFrdLcdPlSetTestPtn( dFrdLcdTestPtn_e eTestPtn )
{
	dResult_e		eResult = S_SUCCESS;
	uint8			ucTestPtn;
	
	if((eTestPtn < FRDLCD_TESTPTN_OFF) || (eTestPtn >= FRDLCD_TESTPTN_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eTestPtn = %d\n", (int8)eTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	ucTestPtn = aucLcdPlTestPtnTbl[eTestPtn];
	
	if(ucTestPtn == 0){
		/* �ƥ��ȥѥ�����OFF */
		eResult |= eFrdLcdPlSetAgingPtn(0);	/* ���������ѥƥ��ȥѥ������OFF */
		eResult |= eFrdLcdPlSetEvaPtn(0);		/* ɾ���ѥƥ��ȥѥ������OFF */
	}
	else if(ucTestPtn <= (LCDPL_AGI_PTN_NUM_MAX + LCDPL_EVA_PTN_NUM_MAX)){
		/* �ƥ��ȥѥ�����ON */
		
		/* ��˾�Υƥ��ȥѥ�����⡼�ɤ����� */
		if(ucTestPtn <= LCDPL_AGI_PTN_NUM_MAX){
			/* �������󥰥ѥ��������� */
			eResult |= eFrdLcdPlSetAgingPtn(ucTestPtn);
			/* ɾ���ѥƥ��ȥѥ������OFF */
			eResult |= eFrdLcdPlSetEvaPtn(0);
		}else{
			/* ɾ���ѥѥ��������� */
			eResult |= eFrdLcdPlSetEvaPtn(ucTestPtn - LCDPL_AGI_PTN_NUM_MAX);
			/* ���������ѥƥ��ȥѥ������OFF */
			eResult |= eFrdLcdPlSetAgingPtn(0);
		}
	}
	else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTestPtn = %d\n", (int8)ucTestPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCD�������󥰥ѥ���������API
** @param	ucAgingPtn : �������󥰥ѥ������ֹ� [0x00-0x21] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetAgingPtn( uint8 ucAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usBmpEnab = 0;
	
	if(ucAgingPtn > LCDPL_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucAgingPtn = %d\n", (int8)ucAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucAgingPtn == 0x13){
	/* �ɥå�ȿž�ե�å� + BITMAP */
		usBmpEnab = 1;/* BitMapɽ���ӥåȤ�Ω�Ƥ� */
	}
	
	/* BitMapɽ������ + �ѥ��������� */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x03, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x03, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x03, (usDat & 0x40) | (usBmpEnab << 7) | ucAgingPtn);
	
	if(ucAgingPtn == 3){
	/* QS�ѥƥ��ȥѥ�����1 �ξ�硢�С���Ʊ�����碌��١������ǥꥻ�åȤ�Ԥ� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDC�ꥻ�å� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDC�ꥻ�åȲ�� */
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
dResult_e eFrdLcdPlSetEvaPtn( uint8 ucEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB���� */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB���� */
	
	if(ucEvaPtn > LCDPL_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucEvaPtn = %d\n", (int8)ucEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB��)���� */
	eResult |= eLcdPlSetTpDat(FALSE, LCDPL_AB, &tTpda, &tTpdb);
	eResult |= eLcdPlSetTpDat(FALSE, LCDPL_CD, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x05, (usDat & 0x60) | ucEvaPtn | usTspatEn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QS ON/OFF����API
** @param	fQsEn	: QS ON/OFF����, TRUE = ON, FALSE = OFF (�����: flag)
** @param	fYuv	: YUV ON(=TRUE)/OFF(=FALSE)���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			QS ON�����ˡ����ȿ������٤˹�ä�QS LUT��ޥ˥奢����ɤ��Ƥ���������
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetQsEn( flag fQsEn, flag fYuv )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usOsOn=0;
	
	if(fQsEn){
		if(fYuv){
			usOsOn = 0x10;
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x46, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x47, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x48, 0x01);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x46, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x47, 0x20);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x48, 0x01);
		}else{
			usOsOn = 0x30;
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x46, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x47, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x48, 0x00);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x46, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x47, 0x08);
			eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x48, 0x00);
		}
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, &usDatCD);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, (usDatAB & 0xCF) | usOsOn);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, (usDatCD & 0xCF) | usOsOn);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	QSȾ����ON/OFF����API
** @param	fLonRoff : Ⱦ����ON/OFF����, TRUE = ��ON��OFF, FALSE = ��OFF��ON (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			����ȿž���岼����ȿž ���֤ξ�硢�����ȤȤ��QS ON/OFF�ΰ�⺸�������ؤ��ޤ�(PPDS�ξ��)��
**			��miniLVDS�ξ�硢ȿž������QS�����ǹԤ���١�QS���꤬ȿž����ˤĤ��Ʋ��ޤ���
**			  TV���ͤȤ��Ƥϡ�����ȿž���֤Τޤޥǥ�⡼�� �Ϥ���ޤ������ǥ�⡼�ɾ��֤Τޤޱ���ȿž ��̵���١�
**			  �ɥ饤�ФȤ��Ƥϡ����Ԥξ��Τ��б�(���ߤα���ȿž���֤˱�����QS��ON/OFF�ΰ�����)���Ƥ��ޤ���
** @note
**			RegAddr:0x6408 ��bit4 ��ON���Ƥ�Τ�
*******************************************************************************/
dResult_e eFrdLcdPlSetQsHalf( flag fLonRoff )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD, usAB=0, usCD=0;
	
	if(!(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x4)){
	/* PPDS(����ȿž������QS�θ��) */
		if( fLonRoff == TRUE ){
			usAB = 0x10;
		}
		else{
			usCD = 0x10;
		}
	}
	else{
	/* miniLVDS(����ȿž������QS����) */
		switch( eLcdPlTrnOvr ){
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
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, &usDatCD);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x08, (usDatAB & 0xEF) | usAB);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x08, (usDatCD & 0xEF) | usCD);
	
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
dResult_e eFrdLcdPlSetQsFreq( dFrdInputFreq_e eInputFreq )
{
	dResult_e eResult;
	
	if((eInputFreq < FRD_INPUT_FREQ_48HZ) || (eInputFreq >= FRD_INPUT_FREQ_NUMMAX)){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR eInputFreq = %d\n", (int8)eInputFreq);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetQsFreqTemp(eInputFreq, ucLcdPlTemp);
	eLcdPlInputFreq = eInputFreq;
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetQsTemp( uint8 ucTemp )
{
	dResult_e eResult;
	
	if(ucTemp > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTemp = %d\n", (int8)ucTemp);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetQsFreqTemp(eLcdPlInputFreq, ucTemp);
	ucLcdPlTemp = ucTemp;
	
	/* 090414 ohashi: ����(�äƤ�LUT)�ˤ�ä��Ż߲�Ƚ������ͤ��ѹ� */
	/* 090414 ohashi: �����ͤϤޤ����� */
	if(ucTemp == 0){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x40, 0x10);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x40, 0x10);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x40, 0x08);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x40, 0x08);
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
*******************************************************************************/
dResult_e eFrdLcdPlSetSbr( uint8 ucTemp )
{
	dResult_e eResult;
	
	if(ucTemp > 0x7){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucTemp = %d\n", (int8)ucTemp);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlSetSbr(eLcdPlTrnOvr, ucTemp);
	ucLcdPlTemp = ucTemp;
	
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
dResult_e eFrdLcdPlRomWs( uint32 uiAddr, uint32 uiLength, uint8* pucDats )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usBurstLen;
	uint16		usLenToNextPage;
	
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + uiLength) > uiLcdPlRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiLength = %d\n", uiLength);
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* �����ޤ�ñ�ʤ���������å� */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ��� */
	eResult |= eLcdPlRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	while(1){
		if(uiLength > LCDPL_I2C_DATA_LEN_MAX){
			usBurstLen = LCDPL_I2C_DATA_LEN_MAX;
		}
		else if(uiLength > 0){
			usBurstLen = uiLength;
		}
		else{
		/* uiLength == 0 */
			break;
		}
		
		/* ���Υڡ��������ޤǤΥХ��ȿ� */
		usLenToNextPage = LCDPL_ROM_PAGE_SIZE_2M - (uiAddr % LCDPL_ROM_PAGE_SIZE_2M);
		
		/* "usBurstLen" ���ڡ�����٤����ϡ������ޤǤ�ʬ�䤹�� */
		if(usBurstLen > usLenToNextPage) {
			usBurstLen = usLenToNextPage;
		}
		
		eResult |= eLcdPlRomWs(uiAddr, usBurstLen, pucDats);
		uiAddr += usBurstLen;
		uiLength -= usBurstLen;
		pucDats += usBurstLen;
	}
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
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
dResult_e eFrdLcdPlRomRs( uint32 uiAddr, uint16 usLength, uint8* pucDats )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t	atRDats[LCDPL_ROM_BURST_LEN_R];
	uint16			i;
	
	/* ��������ñ�ʤ���������å� */
	if(pucDats == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucDats = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if(usLength > LCDPL_ROM_BURST_LEN_R){/* ����ž��Ĺ */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	if((uiAddr + usLength) > uiLcdPlRomSize){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR uiAddr = %d\n", uiAddr);
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR usLength = %d\n", usLength);
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
		return S_SPEC_ERROR;
#endif
	}
	/* �����ޤ�ñ�ʤ���������å� */
	
	eResult = eLcdPlRomManualLoad(uiAddr, LCDPL_REGADDR_ETC +0x140, usLength, FALSE, FALSE);
	
	/* �ǡ����ɤ߹��� */
	atRDats[0].usAddr = LCDPL_REGADDR_ETC +0x140;
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, (int32)usLength, atRDats);
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
dResult_e eFrdLcdPlRomErase( void )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fGetRevInfo != TRUE) return S_FAILURE;
	
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0) return S_SPEC_ERROR;/* EEPROM�ξ��ϥ��顼�꥿���� */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ��� */
	eResult |= eLcdPlRomToWProtectMode(FALSE);
	if(eResult != S_SUCCESS) return S_FAILURE;
		
	/* �񤭹��ߥ��͡��֥륳�ޥ�ɤ�ȯ�� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WREN);
	
	/* BE(Bulk Erase)���ޥ��ȯ�� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_BE);
	
	MDrv_Timer_Delayms(10000);/* Bulk Erase �λ���(8Mbit�б�������) */
	
	/* �饤�ȥץ�ƥ��ȥ⡼�ɤ� */
	eResult |= eLcdPlRomToWProtectMode(TRUE);
	
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
dResult_e eFrdLcdPlSetVerUp( uint8 *pucDats, flag fVerify )
{
	dResult_e eResult = S_SUCCESS;
	uint32 uiTotalLen, uiReadNum, i, j;
	uint32 uiBufLen = 0x100;
	uint8 ucRomSizeR1,ucRomSizeR2,ucRomSizeW1,ucRomSizeW2;
	
	/* Plaice��Ƚ�̤���Ƥ���Ȳ��� */
	
	if(pucDats == NULL) return S_FAILURE;
#if 0
	/* Revision������� */
	if(eFrdLcdPlGetRevInfo(aucLcdPlRevInfo) != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf( 0, "FAIL !! (GetRevInfo)\n" );
#endif //TURNKEY1
		return S_FAILURE;
	}
#endif
#if 0	/* Plaice����¦����Τ��� */
	if(pucDats[LCDPL_ROMADDR_REVISION + FRDLCD_REVISION_PANEL] != aucLcdPlRevInfo[FRDLCD_REVISION_PANEL]){
	/* �񤳤��Ȥ��Ƥ���ROM�ǡ�����Υѥͥ��ư�����ȡ��񤫤�Ƥ���ROM�ǡ�����Υѥͥ��ư�������ۤʤ��� */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf( 0, "aucRevInfo[FRDLCD_REVISION_PANEL] = %d\n", aucLcdPlRevInfo[FRDLCD_REVISION_PANEL] );
#endif //TURNKEY1
		return S_FAILURE;
	}
#endif
	/* Lcd¦����� */
	//eResult |= eFrdLcdPlInit();
#if 0/* ���顼�����å��θ�˰�ư */
	/* ROM����(Flash or EEPROM)��Ƚ�̡�ROM�˽񤫤�Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash �ξ�� �� ��ö���õ� */
		eResult |= eFrdLcdPlRomErase();
		if(eResult != S_SUCCESS){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf( 0, "FAIL!!(RomErase)\n" );
#endif //TURNKEY1
			return eResult;
		}
	}
#endif
	/* �ǡ��������� : �񤫤�Ƥ���ǡ����������ӥ����򻲾� */
	ucRomSizeR1 = aucLcdPlUnifiedRevInfo[FRDLCD_UNI_REVISION_ROM_SIZE];
	/* �ǡ��������� : �񤳤��Ȥ��Ƥ���ǡ����������ӥ����򻲾� */
	ucRomSizeW1 = pucDats[LCDPL_ROMADDR_UNIFIED_REVISION + FRDLCD_UNI_REVISION_ROM_SIZE];
	
	/* �ǡ��������� : �񤫤�Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	ucRomSizeR2 = aucLcdPlRevInfo[FRDLCD_REVISION_ROM_SIZE];
	/* �ǡ��������� : �񤳤��Ȥ��Ƥ���ǡ����Υ������̥�ӥ����򻲾� */
	ucRomSizeW2 = pucDats[LCDPL_ROMADDR_REVISION + FRDLCD_REVISION_ROM_SIZE];
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
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
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
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
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
#endif //KUKJAKU
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
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
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
			eDbgPrintf( 0, "[Plaice] Rom Data Size is not matched!!!!!\n" );
#endif //TURNKEY1
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
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
	if((aucLcdPlRevInfo[FRDLCD_REVISION_ROM] & 0x80) == 0x80){
		/* Serial Flash �ξ�� �� ��ö���õ� */
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(0, "Erase......\n");
#endif //TURNKEY1
		eResult |= eFrdLcdPlRomErase();
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
	eResult |= eFrdLcdPlRomWs(0, uiTotalLen, pucDats);
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
			eFrdLcdPlRomRs(i*uiBufLen, uiBufLen, aucRDats);
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
			eFrdLcdPlRomRs(uiReadNum*uiBufLen, uiTotalLen, aucRDats);
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
** @brief	ROM�ǡ���, �쥸�����ǡ�����Verify API
** @param	uiRomAddr	: ROM����Ƭ���ɥ쥹			(�����: uint32)
** @param	usRegAddr	: �쥸��������Ƭ���ɥ쥹	(�����: uint16)
** @param	usLen		: VerifyĹ					(�����: uint16)
** @retval	S_SUCCESS ����
** @retval	S_FAILURE ����
** @par		������:
** @note
********************************************************************************/
dResult_e eFrdLcdPlVerify( uint32 uiRomAddr, uint16 usRegAddr, uint16 usLen )
{
	dResult_e eResult = S_SUCCESS;
	flag f16bit = TRUE, fFail = FALSE;
	uint16	usLimit, usTmp, i;
	uint8	aucRomDat[0x100];
	dFrdRegVar_t atTmp[0x100];
	
	/* 8 or 16bit�ս꤫��Ƚ�� */
	f16bit = fLcdPlRegDepth16bit(usRegAddr);
	
	if(f16bit)	usLimit = 0x80;
	else		usLimit = 0x100;
	
	do{
		
		if(usLen > usLimit)	usTmp = usLimit;
		else				usTmp = usLen;
		
		if(f16bit){
			eResult |= eFrdLcdPlRomRs(uiRomAddr, usTmp*2, aucRomDat);
		}else{
			eResult |= eFrdLcdPlRomRs(uiRomAddr, usTmp, aucRomDat);
		}
		/* ��Ƭ���ɥ쥹�������� */
		atTmp[0].usAddr = usRegAddr;
		eResult |= eFrdLcdPlRegRs(LCDPL_AB, usTmp, atTmp);
		
		for(i=0; i<usTmp; i++){
			if(f16bit){
				if((aucRomDat[2*i] <<8 | aucRomDat[2*i+1]) != atTmp[i].usVal){
					/* Read Only */
					/* CTL */
					if(atTmp[i].usAddr == 0x0001){
						;;
#if 0
					/* DMA */
					}else if(atTmp[i].usAddr == 0x0048){
						;;
					/* CGN */
					}else if(atTmp[i].usAddr == 0x00BE){
						;;
					/* EDC */
					}else if(atTmp[i].usAddr == 0x0103){
						;;
					}else if(atTmp[i].usAddr == 0x0113){
						;;
					/* PNL */
					}else if((0x030B <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x030D)){
						;;
					}else if(atTmp[i].usAddr == 0x030F){
						;;
					/* IMC */
					}else if(atTmp[i].usAddr == 0x0630){
						;;
					}else if((0x0638 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0657)){
						;;
					/* CRC */
					}else if((0x0700 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0702)){
						;;
					}else if((0x070A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x0789)){
						;;
					/* LCDC(SBR) */
					}else if((0x1030 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1038)){
						;;
					}else if(atTmp[i].usAddr == 0x103C){
						;;
					}else if((0x103D <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x103F)){
						;;
					}else if((0x1730 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1738)){
						;;
					}else if(atTmp[i].usAddr == 0x173C){
						;;
					}else if((0x173D <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x173F)){
						;;
					/* FSB */
					}else if(atTmp[i].usAddr == 0x9000){
						;;
					}else if((0x9002 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x9007)){
						;;
					}else if(atTmp[i].usAddr == 0x9010){
						;;
					}else if((0x9012 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x9029)){
						;;
					/* Write Only */
					/*CTL */
					}else if(atTmp[i].usAddr == 0x0002){
						;;
					/* CRC */
					}else if((0x0790 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x079A)){
						;;
					/* LCDC(SBR) */
					}else if(atTmp[i].usAddr == 0x103C){
						;;
					}else if((0x1080 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x10FF)){
						;;
					}else if(atTmp[i].usAddr == 0x173C){
						;;
					}else if((0x1700 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x1CFF)){
						;;
					/* sbr_reg */
					}else if((0x7780 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x77FF)){
						;;
					}else if((0x7F80 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x7FFF)){
						;;
					/* FSB */
					}else if(atTmp[i].usAddr == 0x9010){
						;;
#endif
					/* Not Use */
					/*CTL */
					}else if((0x0003 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x000F)){
						;;
					}else{
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
						eDbgPrintf(0, "Verify Error [Reg Addr: 0x%x] !!\n", atTmp[i].usAddr);
						eDbgPrintf(0, "Rom: 0x%x,   Reg: 0x%x\n", (aucRomDat[2*i] <<8 | aucRomDat[2*i+1]), atTmp[i].usVal);
#endif //TURNKEY1
						fFail = TRUE;
					}
				}
			}else{
				if(aucRomDat[i] != atTmp[i].usVal){
#if 0
					/* Read Only */
					/* TMGEN */
					if(atTmp[i].usAddr == 0x6A00){
						;;
					}else if(atTmp[i].usAddr == 0x6A05){
						;;
					}else if(atTmp[i].usAddr == 0x6A06){
						;;
					}else if(atTmp[i].usAddr == 0x6A80){
						;;
					}else if(atTmp[i].usAddr == 0x6A85){
						;;
					}else if(atTmp[i].usAddr == 0x6A86){
						;;
					/* FLASHIF */
					}else if(atTmp[i].usAddr == 0x6CEF){
						;;
					/* FRC */
					}else if((0x81DE <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x81E3)){
						;;
					}else if((0x836A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x836D)){
						;;
					}else if((0x8470 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8475)){
						;;
					/* sub8 */
					}else if((0x8801 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x880F)){
						;;
					}else if((0x8820 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x882F)){
						;;
					}else if((0x8838 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x883F)){
						;;
					}else if((0x8854 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x885F)){
						;;
					}else if((0x8867 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x886F)){
						;;
					/* subA */
					}else if((0x8A0A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A0C)){
						;;
					}else if((0x8A27 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A2E)){
						;;
					}else if(atTmp[i].usAddr == 0x8A35){
						;;
					}else if((0x8A39 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A3B)){
						;;
					}else if((0x8A48 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A49)){
						;;
					}else if((0x8A5F <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x8A68)){
						;;
					/* Write Only */
					/* GMA_LUT */
					}else if((0x2286 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x23C7)){
						;;
					}else if((0x23D2 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x2513)){
						;;
					}else if((0x251E <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x265F)){
						;;
					}else if((0x266A <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x27AB)){
						;;
					}else if((0x27B6 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x28F7)){
						;;
					}else if((0x2902 <= atTmp[i].usAddr) && (atTmp[i].usAddr <= 0x2A43)){
						;;
					}else{
#endif
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
						eDbgPrintf(0, "Verify Error [Reg Addr: 0x%x] !!\n", atTmp[i].usAddr);
						eDbgPrintf(0, "Rom: 0x%x,   Reg: 0x%x\n", aucRomDat[i], atTmp[i].usVal);
#endif //TURNKEY1
						fFail = TRUE;
//					}
				}
			}
		}
		
		if(usTmp == usLimit){
			usLen -= usLimit;
			if(f16bit)	uiRomAddr += usLimit*2;
			else		uiRomAddr += usLimit;
			usRegAddr += usLimit;
		}else{
			usLen = 0;
		}
		
	}while(usLen);

#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1	
	if((eResult == S_SUCCESS) && (!fFail))	eDbgPrintf(0, "Verify Success !!\n");
	else									eDbgPrintf(0, "Verify Error !!\n");
#endif //TURNKEY1
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
dResult_e eFrdLcdPlSetFreeRun( flag fFreeEn )
{
	dResult_e eResult = S_SUCCESS;
	
	if(fFreeEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x06, 0x07);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x06, 0x07);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x06, 0x06);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x06, 0x06);
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
dResult_e eFrdLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn )
{
	dResult_e eResult;
	eResult = eLcdPlRomManualLoad(uiRomAddr, uiRegAddr, usByteLen, fCrcEn, TRUE);
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
dResult_e eFrdLcdPlGetErrInfo( dFrdLcdError_t *ptError )
{
	*ptError = atLcdPlErrInfo[ ucLcdPlErrInfoOutCnt ];
	if( atLcdPlErrInfo[ ucLcdPlErrInfoOutCnt ].ucErrCode != 0 ){
		ucLcdPlErrInfoOutCnt++;
		ucLcdPlErrInfoOutCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
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
dResult_e eFrdLcdPlAllManualLoad( void )
{
	dResult_e eResult = S_SUCCESS;
	uint8 i, j;
	
	/* ����ȿž��SBR�������� */
	for(i=0; i<4; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdLcdTrnOvr_e)i != eLcdPlTrnOvr ) || ( j != ucLcdPlTemp ) ){
				eResult |= eLcdPlSetSbr( (dFrdLcdTrnOvr_e)i, j );
			}
		}
	}
	eResult |= eLcdPlSetSbr( eLcdPlTrnOvr, ucLcdPlTemp );/* �����᤹ */
	
	
	/* QS���ȿ����ꡢQS�������� */
	for(i=0; i<3; i++){
		for(j=0; j<8; j++){
			if( ( (dFrdInputFreq_e)i != eLcdPlInputFreq ) || ( j != ucLcdPlTemp ) ){
				eResult |= eLcdPlSetQsFreqTemp( (dFrdInputFreq_e)i, j );
			}
		}
	}
	eResult |= eLcdPlSetQsFreqTemp( eLcdPlInputFreq, ucLcdPlTemp );/* �����᤹ */
	
	/* Unveil �������� */
	for(i=0; i<0xF; i++){
		if( i != ucLcdPlUvlMode ){
			eResult |= eFrdLcdPlSetUvlMode(i);
		}
	}
	eResult |= eFrdLcdPlSetUvlMode(ucLcdPlUvlMode);	/* �����᤹ */
	
	return eResult;
}

#if 0
/*!
********************************************************************************
** @brief	�ǥ������(LCDC�����) ON/OFF������API
** @param	fGammaEn	: �ǥ������ ON/OFF����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Plaice���FR¦�Τ������ͥ������꤬�ʤ�
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetGammaEn( flag fGammaEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucLcdPlGammaEnBit;
	
	if(fGammaEn)	ucLcdPlGammaEnBit = 0x80;/* ON/OFF�� bit7 */
	else			ucLcdPlGammaEnBit = 0x00;
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, (usDat & 0x7F) | ucLcdPlGammaEnBit);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	��ʿ��ľ�ǥ���� ON/OFF������API
** @param	fDecontEn	: �ǥ����ON/OFF���� (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Plaice���FR¦�Τ������ͥ������꤬�ʤ�
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetDecontEn( flag fDecontEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fDecontEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x32, 0x0F);
	else			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x32, 0x00);
	
	return eResult;
}


/*!
********************************************************************************
** @brief	�����ȡ������� ON/OFF������API
** @param	fCckEn	: �����ȡ������� ON/OFF����, TRUE = ON, FALSE = OFF (�����: flag)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			����ȿž����0x642E, 0x652E�θ��������ԤäƤ��뤿�ᡢ��API�ϻ��ѤǤ��ʤ���
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetCckEn( flag fCckEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDatAB, usDatCD;
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E, &usDatAB);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E, &usDatCD);
	usDatAB &= 0x7F;
	usDatCD &= 0x7F;
	
	if(fCckEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x2E, (usDatAB | 0x80));
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_FR_DATAPATH +0x2E, (usDatCD | 0x80));
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x2E, usDatAB);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_FR_DATAPATH +0x2E, usDatCD);
	}
	
	return eResult;
}
#endif


/*!
********************************************************************************
** @brief	LCD�������󥰥ѥ���������API (FR��)
** @param	ucFrAgingPtn : �������󥰥ѥ������ֹ� [0x00-0x21] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Fr����AB¦, CD¦���ʤ�
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetFrAgingPtn( uint8 ucFrAgingPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usData, usBmpEnab = 0;
	
	if(ucFrAgingPtn > LCDPL_AGI_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucFrAgingPtn = %d\n", (int8)ucFrAgingPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucFrAgingPtn == 0x13){
	/* �ɥå�ȿž�ե�å� + BITMAP */
		usBmpEnab = 1;/* BitMapɽ���ӥåȤ�Ω�Ƥ� */
	}
	
	/* BitMapɽ������ + �ѥ��������� */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x03, &usData);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x03, (usData & 0x40) | (usBmpEnab << 7) | ucFrAgingPtn);
	
	if(ucFrAgingPtn == 3){
	/* QS�ѥƥ��ȥѥ�����1 �ξ�硢�С���Ʊ�����碌��١������ǥꥻ�åȤ�Ԥ� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFB);	 /* LCDC�ꥻ�å� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_CGN +0x35, 0xFFFF);	 /* LCDC�ꥻ�åȲ�� */
	}
	
	return eResult;
}


/*!
********************************************************************************
** @brief	LCDɾ���ѥѥ���������API (FR¦)
** @param	ucFrEvaPtn : ɾ���ѥѥ������ֹ� [0x00-0x12] (�����: uint8)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			Fr����AB¦, CD¦���ʤ�
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetFrEvaPtn( uint8 ucFrEvaPtn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTspatEn = 0;
	dFrdLcdTpColor_t tTpda = {0x3FF, 0x3FF, 0x3FF};	/* TPDA RGB���� */
	dFrdLcdTpColor_t tTpdb = {0, 0, 0};				/* TPDB RGB���� */
	
	if(ucFrEvaPtn > LCDPL_EVA_PTN_NUM_MAX){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucFrFrEvaPtn = %d\n", (int8)ucFrEvaPtn);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	if(ucFrEvaPtn != 0)	usTspatEn = 0x80;
	
	/* TPDA, TPDB (RGB��)���� */
	eResult |= eLcdPlSetTpDat(TRUE, LCDPL_AB, &tTpda, &tTpdb);
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x05, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x05, (usDat & 0x60) | ucFrEvaPtn | usTspatEn);
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetUvlEn( flag fUvlEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	if(fKmBypass){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);
		fKmBypass = FALSE;
	}
	
	if(fUvlEn){
		/* 090602 ohashi: Uvl��������Bypass�ˤʤäƤ�������θ���� */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, &usTmp);
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, usTmp & 0xFE);
		
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x00, 0);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x00, 1);	/* Unveil Bypass */
	}
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetUvlMode( uint8 ucUvlMode )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
	if(0xF < ucUvlMode){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR ucUvlMode = %x\n", (uint8)ucUvlMode);
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult = eLcdPlGetUvlModeRomAddr(ucUvlMode, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);							/* CRC�ͤ�ž�� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_PCCUVL +0x23, LCDPL_ROMSIZE_UVLMODE, TRUE, TRUE);	/* �ǡ�����ž�� */
	
	ucLcdPlUvlMode = ucUvlMode;
	
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
dResult_e eFrdLcdPlSetBdEn( flag fBdEn )
{
	dResult_e	eResult = S_SUCCESS;
	
	if(fBdEn){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 1);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 1);
	}else{
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0);
	}
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetNrMode( dFrdLcdNrMode_e eNrMode )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usTmp;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, &usTmp);
	usTmp &= 0x7F;
	
	switch(eNrMode){
		case FRDLCD_NR_MIN:
		case FRDLCD_NR_MID:
		case FRDLCD_NR_MAX:
			/* �ѥ�᡼������ */
			eResult = eLcdPlGetNrModeRomAddr(eNrMode, &uiRomAddr, &uiCrcAddr);
			
			eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
			eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_FR_DATAPATH +0x60, LCDPL_ROMSIZE_NRMODE, TRUE, TRUE);	/* �ǡ�����ž�� */
			/* ON���� */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, (usTmp|0x80));
			break;
		case FRDLCD_NR_OFF:
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, usTmp);
			break;
		default:
			eResult |= S_SPEC_ERROR;
			break;
	}
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetNrMask( uint8 ucMaskNo, flag fMaskEn, dFrdFrame_t *ptMaskFrame )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 ausTmp[4], usTmp, i;
	dFrdRegVar_t atTmp[8];
	
	if((ucMaskNo == 0) || (ucMaskNo > 4))	return S_FAILURE;
	
	/* �ΰ���� */
	if(ptMaskFrame != NULL){
		ausTmp[0] = ptMaskFrame->usXPos;
		ausTmp[1] = ptMaskFrame->usYPos;
		ausTmp[2] = ptMaskFrame->usWidth  + ptMaskFrame->usXPos;
		ausTmp[3] = ptMaskFrame->usHeight + ptMaskFrame->usYPos;
		
		/* 090519 ohashi: ���ޤ����ʽ��� */
		if(ausTmp[0] == 1920) ausTmp[0] -= 1;
		if(ausTmp[1] == 1080) ausTmp[1] -= 1;
		if(ausTmp[2] == 1920) ausTmp[2] -= 1;
		if(ausTmp[3] == 1080) ausTmp[3] -= 1;
		
		if(( 0x77F < ausTmp[2]) ||( 0x437 < ausTmp[3])){
			return S_SPEC_ERROR;
		}
		
		atTmp[0].usVal =  ausTmp[0] & 0xff;
		atTmp[1].usVal = (ausTmp[0] & 0xff00) >> 8;
		atTmp[2].usVal =  ausTmp[1] & 0xff;
		atTmp[3].usVal = (ausTmp[1] & 0xff00) >> 8;
		atTmp[4].usVal =  ausTmp[2] & 0xff;
		atTmp[5].usVal = (ausTmp[2] & 0xff00) >> 8;
		atTmp[6].usVal =  ausTmp[3] & 0xff;
		atTmp[7].usVal = (ausTmp[3] & 0xff00) >> 8;
		
		for(i=0; i<8; i++) atTmp[i].usAddr = LCDPL_REGADDR_FR_DATAPATH +0x40 + 8*(ucMaskNo-1) +i;
		
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, 8, atTmp);
	}
	
	/* ON/OFF���� */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, &usTmp);
	usTmp &= ~((uint16)(0x01 << (ucMaskNo-1)));
	usTmp |= (uint16)(fMaskEn << (ucMaskNo-1));
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x6E, usTmp);
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetPccEn( flag fPccEn )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	if(fKmBypass){
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);
		fKmBypass = FALSE;
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, &usTmp);
	usTmp &= 0xFD;
	if(fPccEn)	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, usTmp);
	else		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0xFE, (usTmp | 0x02));	/* PCC Bypass */
	
	return eResult;
}


/*!
********************************************************************************
** @brief	PCC �ܺ�������API
** @param	ucColNo		: �ΰ��ֹ���� [1-6] (�����: uint8)
** @param	fColEn		: �����ΰ��ON/OFF���� (�����: flag)
** @param	ptPccParam	: �ܺ����� (�����: dFrdLcdPlPcc_t *)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
**			���ĤǤ����ؤ˸����Ǥ���褦�Ҵؿ��ˤϤ��ʤ�
** @note
*******************************************************************************/
dResult_e eFrdLcdPlSetPccCol( uint8 ucColNo, flag fColEn, dFrdLcdPlPcc_t *ptPccParam )
{
	dResult_e	eResult = S_SUCCESS;
	uint16 usTmp;
	
	/* ��ö�Х��ѥ� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 0);
	
	/* �ΰ�ON/OFF���� */
	if((ucColNo < 1) || (6 < ucColNo)){
		return S_FAILURE;
	}else
	if((1 <= ucColNo) && (ucColNo <= 4)){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, &usTmp);
		usTmp &= ~((uint16)0x01 << (4*(ucColNo-1)));
		usTmp |= (uint16)fColEn << (4*(ucColNo-1));
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, usTmp);
	}else
	if((5 <= ucColNo) && (ucColNo <= 6)){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, &usTmp);
		usTmp &= ~((uint16)0x01 << (4*(ucColNo-5)));
		usTmp |= (uint16)fColEn << (4*(ucColNo-5));
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, usTmp);
	}
	
	/* �ܺ����� */
	if(ptPccParam != NULL){
		
		/* �����ΰ�ε���,����,�����ON/OFF���� */
		if(ptPccParam->ptBshEn != NULL){
			/* usTmp������� */
			if((1 <= ucColNo) && (ucColNo <= 4)){
				usTmp &= ~((uint16)0x07 << (1+(4*(ucColNo-1))));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fBriEn) << (1+(4*(ucColNo-1)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fSatEn) << (2+(4*(ucColNo-1)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fHueEn) << (3+(4*(ucColNo-1)));
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x81, usTmp);
			}else
			if((5 <= ucColNo) && (ucColNo <= 6)){
				usTmp &= ~((uint16)0x07 << (1+(4*(ucColNo-5))));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fBriEn) << (1+(4*(ucColNo-5)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fSatEn) << (2+(4*(ucColNo-5)));
				usTmp |= (uint16)(ptPccParam->ptBshEn->fHueEn) << (3+(4*(ucColNo-5)));
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x80, usTmp);
			}
		}
		
		/* ����,����,������ΰ����� */
		if(ptPccParam->ptBshArea != NULL){
			
			/* ���٤��ΰ����� */
			if(ptPccParam->ptBshArea->ptBriArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x83 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptBriArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8a +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptBriArea->usDelta);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptBriArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x89 +0x0d*(ucColNo-1),
										 usTmp);
			}
			
			/* ���٤��ΰ����� */
			if(ptPccParam->ptBshArea->ptSatArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x86 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptSatArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8c +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptSatArea->usDelta);
				/* inv_center */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptSatArea->usCenter;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x85 +0x0d*(ucColNo-1),
										 usTmp);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptSatArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8b +0x0d*(ucColNo-1),
										 usTmp);
			}
			
			/* ������ΰ����� */
			if(ptPccParam->ptBshArea->ptHueArea != NULL){
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x88 +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptHueArea->usCenter);
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8e +0x0d*(ucColNo-1),
										 ptPccParam->ptBshArea->ptHueArea->usDelta);
				/* inv_delta */
				usTmp = 0x2000000/ptPccParam->ptBshArea->ptHueArea->usDelta;
				eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x8d +0x0d*(ucColNo-1),
										 usTmp);
			}
		}
		
		/* ����,����,����Υ�٥����� */
		if(ptPccParam->ptBshLvl != NULL){
			/* ���٤Υ�٥� */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usBriLvl);
			/* ���٤Υ�٥� */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usSatLvl);
			/* ����Υ�٥� */
			eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 ptPccParam->ptBshLvl->usHueLvl);
		}
	}
	/* �Х��ѥ���� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x70, 1);

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
*******************************************************************************/
dResult_e eFrdLcdPlSetPccColEn( uint8 ucColNo, flag fColEn )
{
	dResult_e			eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshEn_t	tBshEn;
	
	tPcc.ptBshEn	= &tBshEn;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= NULL;
	
	if(fColEn){
		tPcc.ptBshEn->fBriEn	= TRUE;
		tPcc.ptBshEn->fSatEn	= TRUE;
		tPcc.ptBshEn->fHueEn	= TRUE;
	}else{
		tPcc.ptBshEn->fBriEn	= FALSE;
		tPcc.ptBshEn->fSatEn	= FALSE;
		tPcc.ptBshEn->fHueEn	= FALSE;
	}
	eResult = eFrdLcdPlSetPccCol(ucColNo, fColEn, &tPcc);
	
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
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshEn( uint8 ucColNo, flag fBriEn, flag fSatEn, flag fHueEn )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t	tPcc;
	dFrdLcdPlBshEn_t	tBshEn;
	
	tPcc.ptBshEn	= &tBshEn;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= NULL;
	
	tPcc.ptBshEn->fBriEn	= fBriEn;
	tPcc.ptBshEn->fSatEn	= fSatEn;
	tPcc.ptBshEn->fHueEn	= fHueEn;
	
	if((fBriEn == FALSE) && (fSatEn == FALSE) && (fHueEn == FALSE)){
		eResult = eFrdLcdPlSetPccCol(ucColNo, FALSE, &tPcc);
	}else{
		eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	}
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
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshArea( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usCenter, uint16 usDelta )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshArea_t	tBshArea;
	dFrdLcdPlPccArea_t	tTmpArea;
	
	tPcc.ptBshEn	= NULL;
	tPcc.ptBshLvl	= NULL;
	tPcc.ptBshArea	= &tBshArea;
	
	switch(eBsh){
		case FRDLCD_BRI:
			tBshArea.ptBriArea = &tTmpArea;
			tBshArea.ptSatArea = NULL;
			tBshArea.ptHueArea = NULL;
			break;
		case FRDLCD_SAT:
			tBshArea.ptBriArea = NULL;
			tBshArea.ptSatArea = &tTmpArea;
			tBshArea.ptHueArea = NULL;
			break;
		case FRDLCD_HUE:
			tBshArea.ptBriArea = NULL;
			tBshArea.ptSatArea = NULL;
			tBshArea.ptHueArea = &tTmpArea;
			break;
		default:
			return S_FAILURE;
	}
	
	tTmpArea.usCenter = usCenter;
	tTmpArea.usDelta  = usDelta;
	
	eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	
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
**			�����˻����ΰ��ON���Ƥ���������
** @par ������
*******************************************************************************/
dResult_e eFrdLcdPlSetPccBshLvl( uint8 ucColNo, dFrdLcdBsh_e eBsh, uint16 usLvl )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdLcdPlPcc_t		tPcc;
	dFrdLcdPlBshLvl_t	tBshLvl;
	
	tPcc.ptBshEn	= NULL;
	tPcc.ptBshArea	= NULL;
	tPcc.ptBshLvl	= &tBshLvl;
	
	switch(eBsh){
		case FRDLCD_BRI:
			tPcc.ptBshLvl->usBriLvl = usLvl;
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usSatLvl));
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usHueLvl));
			break;
		case FRDLCD_SAT:
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usBriLvl));
			tPcc.ptBshLvl->usSatLvl = usLvl;
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x87 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usHueLvl));
			break;
		case FRDLCD_HUE:
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x82 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usBriLvl));
			eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PCCUVL +0x84 +0x0d*(ucColNo-1),
									 &(tPcc.ptBshLvl->usSatLvl));
			tPcc.ptBshLvl->usHueLvl = usLvl;
			break;
		default:
			return S_FAILURE;
	}
	
	eResult = eFrdLcdPlSetPccCol(ucColNo, TRUE, &tPcc);
	
	return eResult;
}


/* 2009.06.29 �������к�(��ư��������Ĵ������ȥ饹��MAX����ȴ�����/�Ф�Ȥ�) */
uint8 aucGamDat[] = {
0xA1, 0xFF, 0xA1, 0xA2, 0xFF,
0xA2, 0xA3, 0xFF, 0xA3, 0xA4, 0xFF, 0xA4, 0xA5,
0xFF, 0xA5, 0xA6, 0xFF, 0xA6, 0xA7, 0xFF, 0xA7,
0xA8, 0xFF, 0xA8, 0xA9, 0xFF, 0xA9, 0xAA, 0xFF,
0xAA, 0xAB, 0xFF, 0xAB, 0xAC, 0xFF, 0xAC, 0xAD,
0xFF, 0xAD, 0xAE, 0xFF, 0xAE, 0xAF, 0xFF, 0xAF,
0xB0, 0xFF, 0xB0, 0xB1, 0xFF, 0xB1, 0xB2, 0xFF,
0xB2, 0xB3, 0xFF, 0xB3, 0xB4, 0xFF, 0xB4, 0xB5,
0xFF, 0xB5, 0xB6, 0xFF, 0xB6, 0xB7, 0xFF, 0xB7,
0xB8, 0xFF, 0xB8, 0xB9, 0xFF, 0xB9, 0xBA, 0xFF,
0xBA, 0xBB, 0xFF, 0xBB, 0xBC, 0xFF, 0xBC, 0xBD,
0xFF, 0xBD, 0xBE, 0xFF, 0xBE, 0xBF, 0xFF, 0xC0
};
#define LCDPL_GAM_DATA_SIZE (sizeof(aucGamDat)/sizeof(aucGamDat[0]))
/*!
********************************************************************************
** @brief	Gamma LUT �񤭴�����API (�������к� 2009.06.29)
** @param	fChgEn		: �񴹤�ON/OFF (�����: falg)
** @retval	S_SUCCESS ���ｪλ
** @retval	other ���顼������
** @par ������
** @note
*******************************************************************************/
dResult_e eFrdLcdPlChgGamLut( flag fChgEn )
{
	dResult_e eResult = S_SUCCESS;
	dFrdRegVar_t atWDats[ LCDPL_GAM_DATA_SIZE ];
	uint8 i;
	
	if( eLcdPlPnlSize != FRDLCD_PNL_40 ) return S_SUCCESS;/* 40���ʳ����к����� */
	if( ( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M ) ||	  /* ��ӥ���(8bit)�ʳ��䡢��ǥ�No=1�ʹߤ��к����� */
		( ( ( aucLcdPlRevInfo[ FRDLCD_REVISION_CPWB ] >> 5 ) & 0x7) != 0 )
		) return S_SUCCESS;
	
	if( fChgEn == TRUE ){
	/* ��ư��������Ĵ������ȥ饹��:MAX����ȴ����� */
	
	/* 40inch�Υǥ�����å����֤ιⳬĴ¦��4032��10bit�ͤ�1008�ˤ˥���åפ��롣
       -> ���̸���ȯ���������Ǥ���ǥ�٥�θ��������ޤ��뤳�Ȥǡ� �����ߥΥ�������ǧ����ˤ������� */
	
		/* Gamma LUT�ιⳬĴ¦��񤭴���(R, G, B ��Ʊ���ͤ��) */
		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usVal = (uint16)aucGamDat[i];
			atWDats[i].usAddr = 0x45A3 + i;/* R */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);
		
		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usAddr = 0x4BA3 + i;/* G */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);

		for(i=0; i<LCDPL_GAM_DATA_SIZE; i++){
			atWDats[i].usAddr = 0x51A3 + i;/* B */
		}
		eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_GAM_DATA_SIZE, atWDats);
	}
	else{
	/* ����Ĵ������ȥ饹��:MAX�λ� -> �ǥե����LUT�ͤ����� */
		eResult |= eLcdPlRomManualLoad(0xD6, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
		eResult |= eLcdPlRomManualLoad(0x5B00, LCDPL_REGADDR_FR_GAMLUTR, 0x1200, TRUE, TRUE);
	}
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_FR_DATAPATH +0x02, 0x87 );/* Gamma LUT�إ��� */
	
	return eResult;
}


/**
 * @brief	���ɽ�λ��ǧ�ѻҴؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdPlChkRomLoadEnd( void )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat;
	uint8		ucTimeOutCnt = 0;
	
	while(1){
		/* ROM���ɽ�λ�ӥåȤγ�ǧ */
		eResult = eFrdLcdPlRegR(LCDPL_AB, 0x01, &usDat);
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
		eResult |= eLcdPlChkCrcForRomLoad();
	}
	
	return eResult;
}


/**
 * @brief	����ͥ�ˤ�륢�ɥ쥹�Ѵ��Ҵؿ�(���)
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static void vAddrConv(dFrdLcdPlCh_e *peCh, int32 iRegNum, dFrdRegVar_t *ptDats)
{
	uint32 i;
	if(*peCh == LCDPL_CD){
		for(i=0; i<iRegNum; i++){
			*peCh = LCDPL_CD;/* �����ؿ����"LCDPL_AB"�˽񤭴������Ƥ��ޤ��١����ٸ����ᤷ�ޤ� */
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
static uint16 usAddrConv(dFrdLcdPlCh_e *peCh, uint16 usAddr)
{
	if(*peCh == LCDPL_CD){
		if(usAddr < 0x1000){
		}
		else if(usAddr < 0x2000){
		/* LCDC(SBR) */
			if((usAddr >= 0x1000) && (usAddr < 0x1080)){
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
		else if(usAddr < 0x6000){
		}
		else if(usAddr < 0x8000){
			if((usAddr >= 0x6400) && (usAddr < 0x6500)){
				usAddr += 0x100;
			}
			else if((usAddr >= 0x6600) && (usAddr < 0x6800)){
				usAddr += 0x200;
			}
			else if((usAddr >= 0x6A00) && (usAddr < 0x6A80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x6B00) && (usAddr < 0x6B80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x6F00) && (usAddr < 0x6F80)){
				usAddr += 0x80;
			}
			else if((usAddr >= 0x7000) && (usAddr < 0x7800)){
				usAddr += 0x800;
			}
		}
		else if(usAddr < 0xC000){
			if((usAddr >= 0xA000) && (usAddr < 0xB000)){
				usAddr += 0x1000;
			}
		}
		*peCh = LCDPL_AB;
	}/* if(*peCh == LCDPL_CD) */
	
	return usAddr;
}


/**
 * @brief	ROM LOAD CRC�����å��Ҵؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdPlChkCrcForRomLoad( void )
{
	dResult_e		eResult = S_SUCCESS;
	uint16			usDat;
	dFrdRegVar_t	atDats[8];
	uint8			i, j;
#if 0	/* 090423 ohashi: ���˥��ɥ쥹0x01�ˤƳ�ǧ���Ƥ��� */	
	/* int_crc_error[3]: EEPROM CRC���顼(���Τ�CRC�����å�) */
	eResult = eFrdLcdPlRegR(LCDPL_AB, 0x01, &usDat);
	if(eResult == S_SUCCESS){
	/* ������Plaice�����ʤΤǡ����顼���ε��ܤʤ� */
		if((usDat & 0x08) == 0x08){
			eResult = S_FAILURE;
		}
	}
#endif	
	/* reg_load_error_flag[63:0] : �ƥ�������CRC���顼 */
	atDats[0].usAddr = LCDPL_REGADDR_ETC + 0x20;
	
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, 8, atDats);
	if(eResult == S_SUCCESS){
		for(i=0; i<8; i++){
			if(atDats[i].usVal != 0){
			/* ���顼�ξ�硢����Ĥ� */
				for(j=0; j<8; j++){
					if(atDats[i].usVal & (1<<j)){
						eLcdPlSetErrLog(2, i*8+j, 0); /* ucErrCode, ucErrBlock, usAddr */
					}
				}
				eResult = S_FAILURE;
			}
		}
	}
	
	/* init_load_error_flag[0] : Header��CRC���顼 */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x28, &usDat);
	if(eResult == S_SUCCESS){
		if((usDat & 0x01) == 0x01){
		/* ���顼�ξ�硢����Ĥ� */
			eLcdPlSetErrLog(1, 0, 0); /* ucErrCode, ucErrBlock, usAddr */
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
static dResult_e eLcdPlRomManualLoad( uint32 uiRomAddr, uint32 uiRegAddr, uint16 usByteLen, flag fCrcEn, flag fOffset )
{
	dResult_e		eResult = S_SUCCESS;
	flag			f16bit;
	uint16			usWordLen;
	dFrdRegVar_t	atSetUpDats[6];
	uint8 			ucParam = 0;
	uint16			usRDat;
	uint8			ucCnt = 0;

	f16bit = fLcdPlRegDepth16bit(uiRegAddr);
	if(f16bit)	usWordLen = (usByteLen >> 1);
	else		usWordLen =  usByteLen;
	
	eResult = eLcdPlRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if( fOffset ) uiRomAddr += uiLcdPlRomOffset;				/* ROM 8Mbit�б� */
	
	/* ���ɸ�ROM���ɥ쥹������ */
	atSetUpDats[0].usVal = (uint16)((uiRomAddr >> 8) & 0xFF);	/* ROM���ɥ쥹���[15:8] */
	atSetUpDats[1].usVal = (uint16)(uiRomAddr & 0xFF);			/* ROM���ɥ쥹����[7:0]  */
	atSetUpDats[0].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x10);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[1].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x11);	/* �쥸�������ɥ쥹���� */

	/* ������쥸�������ɥ쥹������ */
	atSetUpDats[2].usVal = (uint16)((uiRegAddr >> 8) & 0xFF);	/* ������쥸�������ɥ쥹���[15:8]  */
	atSetUpDats[3].usVal = (uint16)(uiRegAddr & 0xFF);			/* ������쥸�������ɥ쥹����[7:0] */
	atSetUpDats[2].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x12);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[3].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x13);	/* �쥸�������ɥ쥹���� */

	/* ���ɥǡ���Ĺ������ */
	atSetUpDats[4].usVal = (uint16)((usWordLen >> 8) & 0xFF);	/* �ǡ���Ĺ���[15:8]  */
	atSetUpDats[5].usVal = (uint16)(usWordLen & 0xFF);			/* �ǡ���Ĺ����[7:0] */
	atSetUpDats[4].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x14);	/* �쥸�������ɥ쥹���� */
	atSetUpDats[5].usAddr = (uint16)(LCDPL_REGADDR_ETC +0x15);	/* �쥸�������ɥ쥹���� */

	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 6, atSetUpDats);		/* �쥸�����ؤν񤭹��� */

	/* �ޥ˥奢�����V�ե��å�OFF */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x3f, &usRDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3f, (usRDat | 1));

	/* ���ɥ�������bit���ö����� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x17, 0);

	ucParam |= ((f16bit << 1) | (fCrcEn << 2));

	/* ROM���ɥ쥹���[19:16] + CRC Enable/Disable + bit��(8bit or 16bit) + ���ɥ������ȥӥå� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x17, ((uiRomAddr >> 12) & 0xF0) | ucParam | 1);

	/* �ӥ��������å� */
	while(1){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC+0x2A, &usRDat);
		if((usRDat & 1) == 1){
//			eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] MANUAL LOAD BUSY COUNT = %d\n", ucCnt);
			break;/* Ω�äƤ���Хӥ����Ǥʤ� */
		}
		ucCnt++;
		if(ucCnt > 100){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
			eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] MANUAL LOAD ERROR !!!!!\n");
#endif //TURNKEY1
			break;
		}
		MDrv_Timer_Delayms(1);
	}
	
	/* ž�����顼(CRC���顼�ʤ�)�����å� */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC+0x29, &usRDat);
	if(usRDat & 1){
	/* ���顼�ξ�硢����Ĥ� */
		eLcdPlSetErrLog( 3, 0, (uint16)uiRegAddr ); /* ucErrCode, ucErrBlock, usAddr */
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
static flag fLcdPlRegDepth16bit( uint32 uiAddr )
{
	flag f16bit = TRUE;/* ����͡�16bit�� */
	
	/* 090409 ohashi�ɲ� */
	if((uiAddr >= LCDPL_REGADDR_OSD) && (uiAddr < LCDPL_REGADDR_IMC)){
	/* 0x400-0x600 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if((uiAddr >= LCDPL_REGADDR_PPDS) && (uiAddr < LCDPL_REGADDR_SBRPARAM)){
	/* 0x2000 - 0x7000 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if( (uiAddr >= PL_REGADDR_FRC) && (uiAddr < LCDPL_REGADDR_FSB) ){
	/* 0x8000 - 0x9000 */
		f16bit = FALSE;/* 8bit�� */
	}
	else if( (uiAddr >= LCDPL_REGADDR_BDLUT) && (uiAddr < 0xC000) ){
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
static dResult_e eLcdPlRomStatusChk( uint16 *pusStatus )
{
	uint16	  usStatus;
	uint16	  usWaitCnt = 0;
	dResult_e eResult = S_SUCCESS;
	
	while(1){
		/* ���ơ������쥸�����ɤ߹��ߥ��ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_RDSR);
		
		/* ROM �� LCDC�쥸���� ���ɤ߽Ф����֤ϡ�EEPCLK(4.6MHz)��16clk����(4us����)�ʤΤ�
		   ������Wait������ʤ��Ƥ�쥸�����ͤϳ��ꤷ�Ƥ��ޤ� */
		
		/* ���ơ������쥸�������ɤ߹��� */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x35, &usStatus);
		if((usStatus & 0x01) != 0){/*ROM�񤭹����椫�ݤ�*/
			usWaitCnt++;
			if(usWaitCnt == 100){
				eResult = S_FAILURE;
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
				eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM ACCESS TIMEOUT ERROR!!!!!!!!\n");
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
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM STATUS REGISTER = %0x\n", usStatus);
#endif //TURNKEY1

	if(pusStatus != NULL){
		*pusStatus = usStatus;
	}
	return eResult;
}


/**
 * @brief	TPDA, TPDB �����ѻҴؿ�
 * @param	flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdPlSetTpDat( flag fFr, dFrdLcdPlCh_e eCh, dFrdLcdTpColor_t *ptTpda, dFrdLcdTpColor_t *ptTpdb )
{
	dResult_e		eResult = S_SUCCESS;
	dFrdRegVar_t	atDats[12];
	
	if(fFr)	atDats[0].usAddr = LCDPL_REGADDR_FR_DATAPATH + 0xD;
	else	atDats[0].usAddr = LCDPL_REGADDR_DATAPATH + 0xD;
	
	if((ptTpda == NULL) && (ptTpdb == NULL)) return S_SPEC_ERROR;
	
	/* �������ͤ���� */
	eResult |= eFrdLcdPlRegRs(eCh, 12, atDats);
	
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
	eResult |= eFrdLcdPlRegWs(eCh, 12, atDats);
	
	return eResult;
}


/**
 * @brief	ROM�饤�ȥץ�ƥ��ȥ⡼��ͭ��/̵���ڤ��ؤ��Ҵؿ�
 * @param	flag fWPMEn
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 */
static dResult_e eLcdPlRomToWProtectMode( flag fWPMEn )
{
	uint16		usStatus;
	uint16		usBP, usData;
	dResult_e	eResult = S_SUCCESS;
	
	eResult |= eLcdPlRomStatusChk(&usStatus);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	if((usStatus & LCDPL_ROM_STATUS_SRDW) != 0){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ROM SRDW BIT HI!!!!!!!!!!!\n");
#endif //TURNKEY1
	}
	
	if( uiLcdPlRomSize == LCDPL_ROMSIZE_TOTAL_2M )	usBP = LCDPL_ROM_STATUS_BP10;	/* 2MbitROM�ǡ����ξ�� */
	else  											usBP = LCDPL_ROM_STATUS_BP210;	/* 8MbitROM�ǡ����ξ�� */
	
	if(fWPMEn == TRUE)	usData = usBP;	/* �ץ�ƥ������� */
	else				usData = 0;		/* �ץ�ƥ��Ȳ������ */
	
	if((usStatus & usBP) != usData){
	/* ��˾�ξ��֤Ǥʤ���� */
		
		/* �񤭹��ߥǡ�����쥸���������� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x40, usData);	/* WDATA_START */
		
		/* �ǡ���Ĺ������(ǰ�ΰ١�����) */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x36, 1);		/* LENGTH_L */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x37, 0);		/* LENGTH_H */

		/* �񤭹��ߥ��͡��֥륳�ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WREN);

		/* ���ơ������쥸�����񤭹��ߥ��ޥ�ɤ�ȯ�� */
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WRSR);
	}
	else{
	/* ��˾�ξ��֤ʤΤǡ����⤷�ޤ��� */
	}
	
	eResult |= eLcdPlRomStatusChk(&usStatus);
	
	return eResult;
}


/**
 * @brief	�Ÿ����������������Ҵؿ�
 * @param	dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	eFrdLcdPlGetRevInfo()��ɬ����˥����뤷�Ƥ���������
 * @memo	��������ROM������Ԥ�ͽ��ʤΤǡ��ܻҴؿ��ϴ���Ū�˻Ÿ���������Ǥ���
 */
static dResult_e eLcdPlGetRegionAndInchInfo( dLcdPlRegionAndInchInfo_t *ptRegionAndInchInfo )
{
	uint8 ucPnlSize = aucLcdPlRevInfo[FRDLCD_REVISION_INCHI];
	
	if(fGetRevInfo != TRUE) return S_FAILURE;

	switch(ucPnlSize){
		case 0x32:
		case 0x37:
		case 0x42:
		case 0x60:
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
			break;
		case 0x52:
#if (PL_REGION_INFO == PL_RIGION_US2)
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
			/* 090706 ohashi: Gdelay����(52"��������� EMI�к�) */
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x41, 0x0c);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x43, 0x0a);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x45, 0x08);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x47, 0x06);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x49, 0x04);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4b, 0x02);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4d, 0x00);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x4f, 0x00);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x51, 0x02);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x53, 0x04);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x55, 0x06);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x57, 0x08);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x59, 0x0a);
			eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_PPDS +0x5b, 0x0c);
#elif (PL_REGION_INFO == PL_RIGION_AS2)	/* ���Υѥͥ� */
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
#else
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
#endif
			break;
		case 0x40:
		case 0x46:
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* ���Υѥͥ� */
#ifdef TURNKEY1

			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;

#else //TURNKEY1
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_NORMAL;
#endif //TURNKEY1
#else
			ptRegionAndInchInfo->eCpwbDirec  = LCDPL_CPWB_DIREC_ROTATION;
#endif
			break;
		case 0x65:
			ptRegionAndInchInfo->eCpwbDirec = LCDPL_CPWB_DIREC_NORMAL;
			break;
		default:
			ptRegionAndInchInfo->eCpwbDirec = LCDPL_CPWB_DIREC_NORMAL;
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
static dResult_e eLcdPlSetTrnOvrReg( dFrdLcdTrnOvr_e eTrnOvr )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usDat, usTmp1, usTmp2, usBit12 = 0x1000;
	flag		fMiniL = (flag)(aucLcdPlRevInfo[FRDLCD_REVISION_ZUC_REV] & 0x04) >> 2;
	/* 090612 ohashi */
	uint16		ausTmp[4];
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* ���Υѥͥ� */
	uint16		ausTmp2[2];
	uint8 i;
#endif
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,&ausTmp[0]);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,&ausTmp[1]);
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,&ausTmp[2]);
	eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,&ausTmp[3]);
	ausTmp[0] &= 0xFFDF;
	ausTmp[1] &= 0xFFDF;
	ausTmp[2] &= 0xFF7F;
	ausTmp[3] &= 0xFF7F;
	
	if(fMiniL == FALSE){
	/* PPDS */
		/* 0x0302 ��bit12�� "0" �� �ڡ�����(0x301, 0x200C, 0x200D, 0x200E)�Υǡ�����񤭴����Ƥ��饹��å�(bit12�� 1 ��)
		                    "1" �� �ڡ�����(0x300, 0x2003, 0x2004, 0x2005)                    ��          (bit12�� 0 ��) */
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_PNL +0x02, &usDat);
		
		if((usDat & usBit12) == 0){
			usTmp1 = 0x01;	/* �� �ڡ���2���� */
			usTmp2 = 0x0C;
		}else{
			usTmp1 = 0x00;	/* �� �ڡ���1���� */
			usTmp2 = 0x03;
		}
		
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PNL  +usTmp1,		aucLcdPlTrnOvrPpds[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+0,	aucLcdPlTrnOvrPpds[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+1,	aucLcdPlTrnOvrPpds[2][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PPDS +usTmp2+2,	aucLcdPlTrnOvrPpds[3][eTrnOvr]);
		
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrPpds[4][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrPpds[5][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrPpds[6][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrPpds[7][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrPpds[8][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrPpds[9][eTrnOvr] << 7) | ausTmp[3]));
		/* �ڡ�������å� */
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_PNL +0x02, ((usDat & ~usBit12) | (usTmp1<<12)));

	}else{
	/* miniLVDS */
#if (PL_REGION_INFO == PL_RIGION_AS2)	/* ���Υѥͥ� */
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x00,	aucLcdPlTrnOvrMiniL[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[2][eTrnOvr]);
		
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, &ausTmp2[0]);
		eResult |= eFrdLcdPlRegR(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, &ausTmp2[1]);
		for(i=0; i<2; i++){
			ausTmp2[i] &= 0x9f;
			ausTmp2[i] |= aucLcdPlTrnOvrMiniL[3][eTrnOvr] << 6;
			ausTmp2[i] |= aucLcdPlTrnOvrMiniL[4][eTrnOvr] << 5;
		}
		eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x04, ausTmp2[0]);
		eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x04, ausTmp2[1]);
		
		/* MiniLVDS Output CH �� 414 �ξ��Τ� */
		if((aucLcdPlRevInfo[12] & 0x03) == 0x01){
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[5][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[6][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[7][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[8][eTrnOvr]);
		}
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[9][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[10][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[11][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[12][eTrnOvr] << 7) | ausTmp[3]));
#else
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x00,	aucLcdPlTrnOvrMiniL[0][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[1][eTrnOvr]);
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_TIMGEN +0x00,		aucLcdPlTrnOvrMiniL[2][eTrnOvr]);
		/* MiniLVDS Output CH �� 414 �ξ��Τ� */
		if((aucLcdPlRevInfo[12] & 0x03) == 0x01){
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[3][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[4][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x27,	aucLcdPlTrnOvrMiniL[5][eTrnOvr]);
			eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x28,	aucLcdPlTrnOvrMiniL[6][eTrnOvr]);
		}
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[7][eTrnOvr] << 5) | ausTmp[0]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x2E,	((aucLcdPlTrnOvrMiniL[8][eTrnOvr] << 5) | ausTmp[1]));
		eResult |= eFrdLcdPlRegW (LCDPL_AB, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[9][eTrnOvr] << 7) | ausTmp[2]));
		eResult |= eFrdLcdPlRegW (LCDPL_CD, LCDPL_REGADDR_DATAPATH +0xD0,	((aucLcdPlTrnOvrMiniL[10][eTrnOvr] << 7) | ausTmp[3]));
#endif
	}
	
	return eResult;
}


/**
 * @brief	SBR����Ҵؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	�������֥�å�ȿž(SBR)�˴�Ϣ����ѥ�᡼��(SBR PARAM, SBR GHOST LUT1, LUT2, CCK LUT)
 *          ���ڤ��ؤ���ޥ˥奢����ɤǹԤ��ޤ���
 */
static dResult_e eLcdPlSetSbr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr, uiCrcAddr;
//	dFrdRegVar_t atDats[3] = {{0x161B, 0x1}, {0x161C, 0x1}, {0x161D, 0x0}};/* SBR GHOST LUT UPDATE�� */
	dFrdRegVar_t atDats[3] = {{0x165d, 0x1}, {0x165e, 0x1}, {0x165f, 0x0}};/* SBR GHOST LUT UPDATE�� */
	
	/* SBR PARAM */
	eResult |= eLcdPlGetSbrParamRomAddr(eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBRPARAM +0x00, LCDPL_ROMSIZE_SBRPARAM, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	/* SBR GHOST LUT1 */
	eResult |= eLcdPlGetGhostLut1RomAddr(eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* �� AB¦ */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x100, LCDPL_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* �� CD¦(AB¦��Ʊ���ǡ�������ä�CRC�ͤ�Ʊ��) */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x700, LCDPL_ROMSIZE_GHOSTLUT1 -4, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	/* SBR GHOST LUT2(�� AB¦) */
	eResult |= eLcdPlGetGhostLut2RomAddr(LCDPL_AB, eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* 090416 ohashi: SIZE-10�Ǥ����Τ��ޤ����� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0x5DA, LCDPL_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* SBR GHOST LUT2(�� CD¦) */
	eResult |= eLcdPlGetGhostLut2RomAddr(LCDPL_CD, eTrnOvr, ucTemp, &uiRomAddr, &uiCrcAddr);
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);								/* CRC�ͤ�ž�� */
	/* 090416 ohashi: SIZE-10�Ǥ����Τ��ޤ����� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_SBR +0xBDA, LCDPL_ROMSIZE_GHOSTLUT2 -10, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif
	
	/* SBR GHOST LUT UPDATE */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 3, atDats);
	eResult |= eFrdLcdPlRegWs(LCDPL_CD, 3, atDats);

#ifdef DEBUG_LCDPL_MANULOAD_SBR
	vLcdPlDbgMnl();
#endif

	return eResult;
}

#ifdef DEBUG_LCDPL_MANULOAD_SBR
/**
 * @brief	MNL�ǥХå����ϻҴؿ�
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static void vLcdPlDbgMnl( void )
{
	uint16 usReadData;
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] CRC_EXP_VAL  = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x2B, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] CRC_CALC_VAL = %0x\n", usReadData);
#endif //TURNKEY1
	eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x29, &usReadData);
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice][MANUAL LOAD] ERROR BIT    = %0x\n", usReadData);
#endif //TURNKEY1
	return;
}
#endif

/**
 * @brief	SBR PARAM�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetSbrParamRomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_SBRPARAM;
	uint32		uiCrcAddr	= 0x210;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += (LCDPL_ROMSIZE_SBRPARAM * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_SBRPARAM * ucTemp);
	uiCrcAddr += ucTemp;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT1�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetGhostLut1RomAddr( dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_GHOSTLUT1;
	uint32		uiCrcAddr	= 0x230;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ( LCDPL_ROMSIZE_GHOSTLUT1 * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_GHOSTLUT1 * ucTemp);
	uiCrcAddr += ucTemp;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	SBR GHOST LUT2�ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdArCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetGhostLut2RomAddr( dFrdLcdPlCh_e eCh, dFrdLcdTrnOvr_e eTrnOvr, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr)
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_GHOSTLUT2;
	uint32		uiCrcAddr	= 0x240;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eTrnOvr){
		case FRDLCD_TRN_OVR_NORMAL:
			break;
		case FRDLCD_TRN_OVR_UPSIDE_DOWN:
			uiRomAddr +=  (LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8);
			uiCrcAddr += (2*8);
			break;
		case FRDLCD_TRN_OVR_MIRROR:
			uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8) * 2);
			uiCrcAddr += ((2*8) * 2);
			break;
		case FRDLCD_TRN_OVR_ROTATE:
			uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * 8) * 3);
			uiCrcAddr += ((2*8) * 3);
			break;
		default:
			break;
	}
	
	uiRomAddr += ((LCDPL_ROMSIZE_GHOSTLUT2 * 2 * ucTemp) + (LCDPL_ROMSIZE_GHOSTLUT2 * eCh));
	uiCrcAddr += ((2 * ucTemp) + eCh);
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	QS ���ȿ������������ѻҴؿ�
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucTemp
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlSetQsFreqTemp( dFrdInputFreq_e eInputFreq, uint8 ucTemp )
{
	dResult_e	eResult = S_SUCCESS;
	uint32		uiRomAddr;
	uint32		uiCrcAddr;
	
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] QS FREQ = %0d\n", eInputFreq);
	eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] QS TEMP = %0d\n", ucTemp);
#endif //TURNKEY1

	eResult = eLcdPlGetQsLutRomAddr(eInputFreq, ucTemp, &uiRomAddr, &uiCrcAddr);
	
	eResult |= eLcdPlRomManualLoad(uiCrcAddr, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);						/* CRC�ͤ�ž�� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_QSLUT +0x00, LCDPL_ROMSIZE_QSLUT, TRUE, TRUE);	/* �ǡ�����ž�� */

#ifdef DEBUG_LCDPL_MANULOAD_QS
	vLcdPlDbgMnl();
#endif

	return eResult;
}


/**
 * @brief	QS LUT�ޥ˥奢������ѻҴؿ�
 * @param	dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetQsLutRomAddr( dFrdInputFreq_e eInputFreq, uint8 ucTemp, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_QSLUT;
	uint32		uiCrcAddr	= 0x200;
	dResult_e	eResult		= S_SUCCESS;
	
	switch(eInputFreq){
		case FRD_INPUT_FREQ_60HZ:
			uiRomAddr += (LCDPL_ROMSIZE_QSLUT * 8);
			uiCrcAddr += 8;
			break;
		default:
			break;
	}
	
	uiRomAddr += (LCDPL_ROMSIZE_QSLUT * ucTemp);
	uiCrcAddr += ucTemp;
	
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
static dResult_e eLcdPlSetErrLog( uint8 ucErrCode, uint8 ucErrBlock, uint16 usAddr )
{
	dResult_e eResult = S_SUCCESS;
	uint16 usCrcCal, usCrcExp;
	
	if( ucErrCode == 1 ){
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x06, &usCrcExp);/* CRC������(�إå����ɻ�) */
	}
	else{
		eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usCrcExp);/* CRC������(�ޥ˥奢����ɻ�) */
	}
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x2B, &usCrcCal);/* CRC�黻�� */
	
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucErrCode		= ucErrCode;		/* ���顼������  */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucErrBlock	= ucErrBlock;		/* ���ɥ��顼�֥�å��ֹ� */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].usAddr		= usAddr;			/* �б��쥸�������ɥ쥹 */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucCrcExp		= (uint8)usCrcExp;	/* CRC������ */
	atLcdPlErrInfo[ ucLcdPlErrInfoInCnt ].ucCrcCal		= (uint8)usCrcCal;	/* CRC�黻�� */
	
	ucLcdPlErrInfoInCnt++;
	ucLcdPlErrInfoInCnt &= (FRDLCD_ERR_LOG_NUM_MAX-1);
	
	return eResult;
}


/**
 * @brief	ROM�񤭹����ѻҴؿ�
 * @param	uint32 uiAddr, uint16 usLength, uint8 *pucDats
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlRomWs( uint32 uiAddr, uint16 usLength, uint8 *pucDats )
{
	dResult_e		eResult;
	dFrdRegVar_t	atSetUpDats[4];
	dFrdRegVar_t	atWDats[LCDPL_ROM_BURST_LEN_W];
	int i;
	
	/* ��������ñ�ʤ���������å� */
	if(usLength > LCDPL_ROM_BURST_LEN_W)				return S_SPEC_ERROR;
	if(usLength > LCDPL_ROM_PAGE_SIZE_2M)				return S_SPEC_ERROR;
#ifndef LCDPL_ROM_SIZE_ERROR_BYPASS
	if((uiAddr + usLength) > uiLcdPlRomSize)			return S_SPEC_ERROR;
#endif
	/* �����ޤ�ñ�ʤ���������å� */
	
	eResult = eLcdPlRomStatusChk(NULL);
	if(eResult != S_SUCCESS) return S_FAILURE;
	
	atSetUpDats[0].usVal = LCDPL_ROM_CMD_WREN;			/* �񤭹��ߥ��͡��֥����� */
	atSetUpDats[1].usVal = (uiAddr & 0xFF);				/* ROM���ɥ쥹���� */
	atSetUpDats[2].usVal = ((uiAddr >> 8) & 0xFF);		/* ROM���ɥ쥹��� */
	atSetUpDats[3].usVal = ((uiAddr >> 16) & 0xFF);		/* ROM���ɥ쥹���  */
	for(i=0; i<4; i++){
		atSetUpDats[i].usAddr = LCDPL_REGADDR_ETC +0x30 +i;	/* �쥸�������ɥ쥹���� */
	}
	/* WREN���ޥ�ɡ�ROM���ɥ쥹������ */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 4, atSetUpDats);
	
	atSetUpDats[0].usVal = (usLength & 0xFF);			/* �񤭹��ߥǡ���Ĺ���� */
	atSetUpDats[1].usVal = ((usLength >> 8) & 0xFF);	/* �񤭹��ߥǡ���Ĺ��� */
	atSetUpDats[0].usAddr = LCDPL_REGADDR_ETC +0x36;	/* �쥸�������ɥ쥹���� */
	atSetUpDats[1].usAddr = LCDPL_REGADDR_ETC +0x37;	/* �쥸�������ɥ쥹���� */
	/* �ǡ���Ĺ������ */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, 2, atSetUpDats);
	
	for(i=0; i<usLength; i++){
		atWDats[i].usVal  = (uint16)pucDats[i];			/* �񤭹��ߥǡ������� */
		atWDats[i].usAddr = LCDPL_REGADDR_ETC +0x40 +i;	/* �쥸�������ɥ쥹���� */
	}
	
	/* �񤭹��ߥǡ����Хåե������� */
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, usLength, atWDats);
	
	/* WRITE���ޥ��ȯ�� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x30, LCDPL_ROM_CMD_WRITE);
	
	return eResult;
}


/**
 * @brief	Unveil ����ѥ�᡼���ޥ˥奢������ѻҴؿ�
 * @param	uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetUvlModeRomAddr( uint8 ucUvlMode, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_UVLMODE;
	uint32		uiCrcAddr	= 0x2A0;
	dResult_e	eResult		= S_SUCCESS;
	
	uiRomAddr += (LCDPL_ROMSIZE_UVLMODE * (ucUvlMode));
	uiCrcAddr += ucUvlMode;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/**
 * @brief	������ѻҴؿ�
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlReloadAll( uint8 ucPnlSizeNo )
{
	dResult_e	eResult = S_SUCCESS;
	uint16		usAddr = ucPnlSizeNo * 4;
	uint16		usDat;
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3A, 0x01 );				/* ����ɥ��ɥ쥹��� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x3B, usAddr );			/* ����ɥ��ɥ쥹��� */
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, &usDat);
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, (usDat & 0x7F));	/* ����ɥӥåȢ��� */
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_ETC +0x39, (usDat | 0x80));	/* ����ɥӥåȢ��� */
	
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
static dResult_e eLcdPlGetRevInfo( uint8 *pucRevInfo, uint32 uiRomAddr )
{
	dResult_e	 eResult = S_SUCCESS;
	dFrdRegVar_t atRDat[FRDLCD_REVISION_DATA_MAX-1];
	uint16		 usCrcExp, i;
	
	if(pucRevInfo == NULL){
#ifdef TURNKEY1
//TURNKEY1 nothing
#else //TURNKEY1
		eDbgPrintf(LCDPL_DBG_LEVEL, "[Plaice] ERROR pucRevInfo = NULL\n");
#endif //TURNKEY1
		return S_SPEC_ERROR;
	}
	
	eResult |= eLcdPlRomManualLoad(uiRomAddr +0xF, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);					/* CRC�ͤ�ž�� */
	eResult |= eLcdPlRomManualLoad(uiRomAddr, LCDPL_REGADDR_ETC +0x140, FRDLCD_REVISION_DATA_MAX-1, TRUE, TRUE);/* �ǡ�����ž�� */
	
	/* �ǡ����ɤ߹��� */
	atRDat[0].usAddr = LCDPL_REGADDR_ETC +0x140;
	eResult |= eFrdLcdPlRegRs(LCDPL_AB, FRDLCD_REVISION_DATA_MAX-1, atRDat);
	for(i=0; i<FRDLCD_REVISION_DATA_MAX-1; i++){
		pucRevInfo[i] = (uint8)atRDat[i].usVal;
	}
	
	eResult |= eFrdLcdPlRegR(LCDPL_AB, LCDPL_REGADDR_ETC +0x16, &usCrcExp);
	pucRevInfo[FRDLCD_REVISION_DATA_MAX-1] = (uint8)usCrcExp;
	
	return eResult;
}


/**
 * @brief	Nr �����ѥ�᡼���ޥ˥奢������ѻҴؿ�
 * @param	dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	
 */
static dResult_e eLcdPlGetNrModeRomAddr( dFrdLcdNrMode_e eNrMode, uint32 *puiRomAddr, uint32 *puiCrcAddr )
{
	uint32		uiRomAddr	= LCDPL_ROMADDR_NRMODE;
	uint32		uiCrcAddr	= 0x2B0;
	dResult_e	eResult		= S_SUCCESS;
	
	uiRomAddr += (LCDPL_ROMSIZE_NRMODE * (FRDLCD_NR_MAX -eNrMode));
	uiCrcAddr += FRDLCD_NR_MAX -eNrMode;
	
	*puiRomAddr	= uiRomAddr;
	*puiCrcAddr	= uiCrcAddr;
	
	return eResult;
}


/* 090630 ohashi: ȩ������LUT */
static uint8 aucSkinCtlLutAc00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07,
	0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D,
	0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F,
	0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2A,
	0x2C, 0x2D, 0x2F, 0x31, 0x32, 0x34, 0x36, 0x38,
	0x39, 0x3B, 0x3D, 0x3F, 0x41, 0x43, 0x45, 0x47,
	0x49, 0x4B, 0x4D, 0x4F, 0x51, 0x53, 0x55, 0x58,
	0x5A, 0x5C, 0x5E, 0x61, 0x63, 0x66, 0x68, 0x6A,
	0x6D, 0x6F, 0x72, 0x74, 0x77, 0x7A, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static uint8 aucSkinCtlLutBc00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07,
	0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0B, 0x0C, 0x0D,
	0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F,
	0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2A,
	0x2C, 0x2D, 0x2F, 0x31, 0x32, 0x34, 0x36, 0x38,
	0x39, 0x3B, 0x3D, 0x3F, 0x41, 0x43, 0x45, 0x47,
	0x49, 0x4B, 0x4D, 0x4F, 0x51, 0x53, 0x55, 0x58,
	0x5A, 0x5C, 0x5E, 0x61, 0x63, 0x66, 0x68, 0x6A,
	0x6D, 0x6F, 0x72, 0x74, 0x77, 0x7A, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

static uint8 aucSkinCtlLutAe00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x04, 0x07, 0x09, 0x0C, 0x0E, 0x10, 0x13, 0x15,
	0x18, 0x1A, 0x1C, 0x1F, 0x21, 0x24, 0x26, 0x28,
	0x2B, 0x2D, 0x30, 0x32, 0x34, 0x37, 0x39, 0x3C,
	0x3E, 0x40, 0x43, 0x45, 0x48, 0x4A, 0x4C, 0x4F,
	0x51, 0x54, 0x56, 0x59, 0x5B, 0x5D, 0x60, 0x62,
	0x65, 0x67, 0x69, 0x6C, 0x6E, 0x71, 0x73, 0x75,
	0x78, 0x7A, 0x7D, 0x7F, 0x81, 0x84, 0x86, 0x89,
	0x8B, 0x8D, 0x90, 0x92, 0x95, 0x97, 0x99, 0x9C,
	0x9E, 0xA1, 0xA3, 0xA5, 0xA8, 0xAA, 0xAD, 0xAF,
	0xB2, 0xB4, 0xB6, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2,
	0xC5, 0xC7, 0xCA, 0xCC, 0xCE, 0xD1, 0xD3, 0xD6,
	0xD8, 0xDA, 0xDD, 0xDF, 0xE2, 0xE4, 0xE6, 0xE9,
	0xEB, 0xEE, 0xF0, 0xF2, 0xF5, 0xF7, 0xFA, 0xFF,
};

static uint8 aucSkinCtlLutBe00[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x04, 0x07, 0x09, 0x0C, 0x0E, 0x10, 0x13, 0x15,
	0x18, 0x1A, 0x1C, 0x1F, 0x21, 0x24, 0x26, 0x28,
	0x2B, 0x2D, 0x30, 0x32, 0x34, 0x37, 0x39, 0x3C,
	0x3E, 0x40, 0x43, 0x45, 0x48, 0x4A, 0x4C, 0x4F,
	0x51, 0x54, 0x56, 0x59, 0x5B, 0x5D, 0x60, 0x62,
	0x65, 0x67, 0x69, 0x6C, 0x6E, 0x71, 0x73, 0x75,
	0x78, 0x7A, 0x7D, 0x7F, 0x81, 0x84, 0x86, 0x89,
	0x8B, 0x8D, 0x90, 0x92, 0x95, 0x97, 0x99, 0x9C,
	0x9E, 0xA1, 0xA3, 0xA5, 0xA8, 0xAA, 0xAD, 0xAF,
	0xB2, 0xB4, 0xB6, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2,
	0xC5, 0xC7, 0xCA, 0xCC, 0xCE, 0xD1, 0xD3, 0xD6,
	0xD8, 0xDA, 0xDD, 0xDF, 0xE2, 0xE4, 0xE6, 0xE9,
	0xEB, 0xEE, 0xF0, 0xF2, 0xF5, 0xF7, 0xFA, 0xFF,
};
#define LCDPL_SKIN_CTL_LUT_SIZE (sizeof(aucSkinCtlLutAc00)/sizeof(aucSkinCtlLutAc00[0]))

/**
 * @brief	ȩ������LUT��ư���񴹤��ѻҴؿ� (�����ROM�ˤ������)
 * @param	void
 * @return	S_SUCCESS ����
 * @return	S_FAILURE ����
 * @memo	LCDPL_REGADDR_DATAPATH +0x50 ��eFrdLcdPlSetBdEn()�Ǥ���Ѥ���Ƥ���
 */
static dResult_e eLcdPlInitSkinCtlLut( void )
{
	dResult_e	eResult	= S_SUCCESS;
	uint16 i;
	dFrdRegVar_t atTmp[LCDPL_SKIN_CTL_LUT_SIZE];
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0x01);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0x01);
	
	/* 090701 ohashi: ���椵�������ɲ� */
	eResult |= eLcdPlRomManualLoad(0xF6, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
	eResult |= eLcdPlRomManualLoad(0x3D700, LCDPL_REGADDR_BDLUT,         0xF00, TRUE, TRUE);
	eResult |= eLcdPlRomManualLoad(0xFE, LCDPL_REGADDR_ETC +0x16, 1, FALSE, TRUE);
	eResult |= eLcdPlRomManualLoad(0x3D700, LCDPL_REGADDR_BDLUT +0x1000, 0xF00, TRUE, TRUE);
	
	/* 0xAC00�� */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xAC00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutAc00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xBC00�� */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xBC00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutBc00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xAE00�� */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xAE00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutAe00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	/* 0xBE00�� */
	for(i=0; i<LCDPL_SKIN_CTL_LUT_SIZE; i++){
		atTmp[i].usAddr = 0xBE00 +i;
		atTmp[i].usVal  = (uint16)aucSkinCtlLutBe00[i];
	}
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x00]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x40]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0x80]);
	eResult |= eFrdLcdPlRegWs(LCDPL_AB, LCDPL_SKIN_CTL_LUT_SIZE/4, &atTmp[0xC0]);
	
	eResult |= eFrdLcdPlRegW(LCDPL_AB, LCDPL_REGADDR_DATAPATH +0x50, 0x08);
	eResult |= eFrdLcdPlRegW(LCDPL_CD, LCDPL_REGADDR_DATAPATH +0x50, 0x08);
	
	return eResult;
}
/* end of file */
