/************************************************************************
 *
 *  otp_reg.h
 *
 *  Public header file for Nike OTP module
 *
 ************************************************************************/
#ifndef OTP_REG_H
#define OTP_REG_H

#define MAX_OTP_OFST              0x380
#define OTP_PROG_MAGIC            0x15
#define OTP_REG_BASE              (0xb8017400)
#define OTP_DDR_MAP_BASE          (0xb8017000)

/************************************************************************
 *  Definition
 ************************************************************************/


#define OTP_DATA                  (OTP_REG_BASE + 0x00)
#define OTP_CTRL                  (OTP_REG_BASE + 0x00)
#define OTP_CTRL1                 (OTP_REG_BASE + 0x04)
#define OTP_STATUS                (OTP_REG_BASE + 0x08)
#define OTP_CRC                   (OTP_REG_BASE + 0x0c)
#define OTP_RW1                   (OTP_REG_BASE + 0x10)
#define OTP_RW2                   (OTP_REG_BASE + 0x14)
#define OTP_RD                    (OTP_REG_BASE + 0x18)
#define OTP_PROG1                 (OTP_REG_BASE + 0x1c)
#define OTP_PROG2                 (OTP_REG_BASE + 0x20)
#define OTP_BC                    (OTP_REG_BASE + 0x24)
#define OTP_TD                    (OTP_REG_BASE + 0x28)

#define OTP_DEBUG                 (OTP_REG_BASE + 0x30)

/* OTP_CTRL */
#define S_OTP_CTRL_WRITE_EN2                 31
#define S_OTP_CTRL_AUTO_RD_OTP_ALL           24
#define S_OTP_CTRL_WRITE_EN1                 23
#define S_OTP_CTRL_MAX_PROG_NUM              16
#define S_OTP_CTRL_PROG                      13
#define S_OTP_CTRL_A                         0
#define MASK_OTP_CTRL_WRITE_EN2              (0X1 << S_OTP_CTRL_WRITE_EN2)
#define MASK_OTP_CTRL_AUTO_RD_OTP_ALL        (0X1 << S_OTP_CTRL_AUTO_RD_OTP_ALL)
#define MASK_OTP_CTRL_WRITE_EN1              (0X1 << S_OTP_CTRL_WRITE_EN1)
#define MASK_OTP_CTRL_PROG                   (0X1 << S_OTP_CTRL_PROG)
#define MASK_OTP_CTRL_A                      (0X1FFF << S_OTP_CTRL_A)
#define SET_OTP_CTRL_WRITE_EN2(BIT)          ((BIT &  0X1) << S_OTP_CTRL_WRITE_EN2)
#define SET_OTP_CTRL_AUTO_RD_OTP_ALL(BIT)    ((BIT &  0X1) << S_OTP_CTRL_AUTO_RD_OTP_ALL)
#define SET_OTP_CTRL_WRITE_EN1(BIT)          ((BIT &  0X1) << S_OTP_CTRL_WRITE_EN1)
#define SET_OTP_CTRL_MAX_PROG_NUM(VAL)       ((VAL & 0X1F) << S_OTP_CTRL_MAX_PROG_NUM)
#define SET_OTP_CTRL_PROG(BIT)               ((BIT &  0X1) << S_OTP_CTRL_PROG)
#define SET_OTP_CTRL_A(VAL)                  ((VAL & 0X1FFF) << S_OTP_CTRL_A)

/* OTP_CTRL1 */
#define S_OTP_CTRL1_WRITE_EN2                 13
#define S_OTP_CTRL1_CRC_EN                    12
#define S_OTP_CTRL1_WRITE_EN1                 8
#define S_OTP_CTRL1_EN_PROG_FUNC              0
#define MASK_OTP_CTRL1_WRITE_EN2              (0X1 << S_OTP_CTRL1_WRITE_EN2)
#define MASK_OTP_CTRL1_CRC_EN                 (0X1 << S_OTP_CTRL1_CRC_EN)
#define MASK_OTP_CTRL1_WRITE_EN1              (0X1 << S_OTP_CTRL1_WRITE_EN1)
#define MASK_OTP_CTRL1_EN_PROG_FUNC           (0XFF << S_OTP_CTRL1_EN_PROG_FUNC)
#define SET_OTP_CTRL1_WRITE_EN2(BIT)          ((BIT &  0X1) << S_OTP_CTRL1_WRITE_EN2)
#define SET_OTP_CTRL1_CRC_EN(BIT)             ((BIT &  0X1) << S_OTP_CTRL1_CRC_EN)
#define SET_OTP_CTRL1_WRITE_EN1(BIT)          ((BIT &  0X1) << S_OTP_CTRL1_WRITE_EN1)
#define SET_OTP_CTRL1_EN_PROG_FUNC(VAL)       ((VAL & 0XFF) << S_OTP_CTRL1_EN_PROG_FUNC)


/* OTP_STATUS */
#define S_OTP_STATUS_OTP_FAIL_REG_WR         27
#define S_OTP_STATUS_OTP_DONE_REG_WR         19
#define MASK_OTP_STATUS_OTP_FAIL_REG_WR      (0X1 << S_OTP_STATUS_OTP_FAIL_REG_WR)
#define MASK_OTP_STATUS_OTP_DONE_REG_WR      (0X1 << S_OTP_STATUS_OTP_DONE_REG_WR)

/* OTP_CRC */
#define S_OTP_CRC_CRC_INI                    16
#define S_OTP_CRC_CRC_OUT                    0
#define MASK_OTP_CRC_CRC_INI                 (0XFFFF << S_OTP_CRC_CRC_INI)
#define MASK_OTP_CRC_CRC_OUT                 (0XFFFF << S_OTP_CRC_CRC_OUT)
#define SET_OTP_CRC_CRC_INI(VAL)             ((VAL &0XFFFF) << S_OTP_CRC_CRC_INI)

/************************************************************************
 *  Public functions
 ************************************************************************/

#endif /* #ifndef OTP_REG_H */

