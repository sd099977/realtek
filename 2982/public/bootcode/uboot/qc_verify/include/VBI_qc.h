
//=====================================================
#define QC_test

#ifdef QC_test
#define Slicer_CC_test
#define Slicer_CGMS_test
#define Slicer_mbist_test
#define Slicer_mbist_drf_test
#else

//#define CC_Verify_item
//#define TT_Verify_item
//#define WSS_Verify_item
//#define VPS_Verify_item
//#define CGMS_Verify_item

#ifdef CC_Verify_item
#define AV_Input
////#define IFD_Input
#define CC_verify_test
#endif

#ifdef TT_Verify_item
#define AV_Input
////#define IFD_Input
#define TT_WSS_VPS_test
#define TT_test
//#define TT_DMA_test
#endif

#ifdef WSS_Verify_item
#define AV_Input
#define TT_WSS_VPS_test
#define WSS_test
#endif

#ifdef VPS_Verify_item
#define AV_Input
#define TT_WSS_VPS_test
#define VPS_test
#endif

#ifdef CGMS_Verify_item
//#define AV_Input
#define YPP_Input
#define CGMS_test
#define YPPin_480i
//#define YPPin_480p
//#define YPPin_720p
//#define YPPin_1080i
#endif
///// Others setting  /////
#define Odd_parity_recovery
//#define AGC_slicer_level
//#define WSS_from_CC_path
//#define Pattern6_setting
#endif
//=====================================================
#define first_delay  30000
#define two_delay  10000
#define CC_VALUE  0x00009420
#define CGMS_VALUE  0x80001


#define SYSTEM_SOFT_RESET3_VADDR                  (0xb8000008)	// [9] is VBI soft reset
#define SYSTEM_GROUP1_CK_EN_VADDR                 (0xb8000014)	// [20] is VBI reset

#define _BIT0	0x00000001
#define _BIT1	0x00000002
#define _BIT2	0x00000004
#define _BIT3	0x00000008
#define _BIT4	0x00000010
#define _BIT5	0x00000020
#define _BIT6	0x00000040
#define _BIT7	0x00000080
#define _BIT8	0x00000100
#define _BIT9	0x00000200
#define _BIT10	0x00000400
#define _BIT11	0x00000800
#define _BIT12	0x00001000
#define _BIT13	0x00002000
#define _BIT14	0x00004000
#define _BIT15	0x00008000
#define _BIT16	0x00010000
#define _BIT17	0x00020000
#define _BIT18	0x00040000
#define _BIT19	0x00080000
#define _BIT20	0x00100000
#define _BIT21	0x00200000
#define _BIT22	0x00400000
#define _BIT23	0x00800000
#define _BIT24	0x01000000
#define _BIT25	0x02000000
#define _BIT26	0x04000000
#define _BIT27	0x08000000
#define _BIT28	0x10000000
#define _BIT29	0x20000000
#define _BIT30	0x40000000
#define _BIT31	0x80000000

#define _SUCCESS	0
#define _FAIL		1

#define VBIPPR_CTRL_REG				(0xb8030000)
#define VBIPPR_PG_LINE_ACT_REG		(0xb8030304)
#define VBIPPR_PGDATA_B1B4_REG	(0xb8030308)
#define VBIPPR_PGDATA_B5B8_REG	(0xb803030C)
#define VBIPPR_PGDATA_B9B12_REG	(0xb8030310)

void vbi_delay(UINT32 count);
int QC_Verifier_VBI(void);


