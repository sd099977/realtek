#ifndef __OTP_TBL_H__
#define __OTP_TBL_H__

/****************************************************************************/
/*                                                                          */
/* ==================== OTP Register DEFINE ==================== */
/*                                                                          */
/****************************************************************************/
#define RTK_OTP_BASE        (0xb8017000)

#define OTP_CHIP_ID         (0x198UL)   //0xb8017198; RTK_Chip_ID
#define OTP_NUID64_1_H      (0x208UL)   //0xb8017208; Nagra_NUID64_1 [63:32]
#define OTP_NUID64_1_L      (0x20CUL)   //0xb801720C; Nagra_NUID64_1 [31: 0]
#define OTP_CHIP_REV        (0x218UL)   //0xb8017218; Nagra_ChipsetRevisioin
#define OTP_CaSnRef32       (0x21CUL)   //0xb801721C
#define OTP_CaSnRef32Lock   (0x220UL)   //0xb8017220
#define OTP_sidRef          (0x270UL)   //0xb8017270
#define OTP_sidRefLock      (0x274UL)   //0xb8017274
#define OTP_MRK1            (0xB10UL)   //0xb8017B10

#define DP_NA_MRK_CHIP_ID       (RTK_OTP_BASE+OTP_CHIP_ID       )
#define DP_NA_MRK_NUID64_H      (RTK_OTP_BASE+OTP_NUID64_1_H    )
#define DP_NA_MRK_NUID64_L      (RTK_OTP_BASE+OTP_NUID64_1_L    )
#define DP_NA_MRK_CHIP_REV      (RTK_OTP_BASE+OTP_CHIP_REV      )
#define DP_NA_MRK_CaSnRef32     (RTK_OTP_BASE+OTP_CaSnRef32     )
#define DP_NA_MRK_CaSnRef32Lock (RTK_OTP_BASE+OTP_CaSnRef32Lock )
#define DP_NA_MRK_sidRef        (RTK_OTP_BASE+OTP_sidRef        )
#define DP_NA_MRK_sidRefLock    (RTK_OTP_BASE+OTP_sidRefLock    )
#define DP_NA_MRK_MRK1          (RTK_OTP_BASE+OTP_MRK1          )

/****************************************************************************/
/*                                                                          */
/* ==================== OTP TABLE ====================                      */
/*                                                                          */
/****************************************************************************/
const OTP_PARAM OTP_RtkChipID           = {OTP_CHIP_ID,          7,  0};    //Nagra_ChipsetRevisioin
const OTP_PARAM OTP_StbCaSnRef32        = {OTP_CaSnRef32,       31,  0};    //Set-To -Box serial Number
const OTP_PARAM OTP_StbCaSnRef32Lock    = {OTP_CaSnRef32Lock,    0,  0};    //Set-To -Box serial Number flag programming lock bit
const OTP_PARAM OTP_MsidRef             = {OTP_sidRef,          31,  0};    //Marketing segment ID
const OTP_PARAM OTP_MsidRefLock         = {OTP_sidRefLock,       0,  0};    //Marketing segment ID flag programming lock bit





#endif  //?#ifndef __OTP_TBL_H__