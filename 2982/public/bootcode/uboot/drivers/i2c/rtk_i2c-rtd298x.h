#ifndef __RTK_I2C_RTD298X_H__
#define __RTK_I2C_RTD298X_H__


#if defined(CONFIG_RTD298X)
#include <asm/arch/rbus/mis_reg.h>
#endif

#define RTK_I2C_CNT               3


#define IC0_SDA_DEL                 0xB8062500

#define IC0_ADDRESS_BASE            0xB8062600

#define IC0_CON                     IC0_ADDRESS_BASE
#define IC0_TAR                     (IC0_ADDRESS_BASE + 0x4)
#define IC0_SAR                     (IC0_ADDRESS_BASE + 0x8)
#define IC0_HS_MADDR                (IC0_ADDRESS_BASE + 0xC)
#define IC0_DATA_CMD                (IC0_ADDRESS_BASE + 0x10)
#define IC0_SS_SCL_HCNT             (IC0_ADDRESS_BASE + 0x14)
#define IC0_SS_SCL_LCNT             (IC0_ADDRESS_BASE + 0x18)
#define IC0_FS_SCL_HCNT             (IC0_ADDRESS_BASE + 0x1C)
#define IC0_FS_SCL_LCNT             (IC0_ADDRESS_BASE + 0x20)
/*#define Rvd                       (IC0_ADDRESS_BASE + 0x24)*/
/*#define Rvd                       (IC0_ADDRESS_BASE + 0x28)*/
#define IC0_INTR_STAT               (IC0_ADDRESS_BASE + 0x2C)
#define IC0_INTR_MASK               (IC0_ADDRESS_BASE + 0x30)
#define IC0_RAW_INTR_STAT           (IC0_ADDRESS_BASE + 0x34)
#define IC0_RX_TL                   (IC0_ADDRESS_BASE + 0x38)
#define IC0_TX_TL                   (IC0_ADDRESS_BASE + 0x3C)
#define IC0_CLR_INTR                (IC0_ADDRESS_BASE + 0x40)
#define IC0_CLR_RX_UNDER            (IC0_ADDRESS_BASE + 0x44)
#define IC0_CLR_RX_OVER             (IC0_ADDRESS_BASE + 0x48)
#define IC0_CLR_TX_OVER             (IC0_ADDRESS_BASE + 0x4C)
#define IC0_CLR_RD_REQ              (IC0_ADDRESS_BASE + 0x50)
#define IC0_CLR_TX_ABRT             (IC0_ADDRESS_BASE + 0x54)
#define IC0_CLR_RX_DONE             (IC0_ADDRESS_BASE + 0x58)
#define IC0_CLR_ACTIVITY            (IC0_ADDRESS_BASE + 0x5C)
#define IC0_CLR_STOP_DET            (IC0_ADDRESS_BASE + 0x60)
#define IC0_CLR_START_DET           (IC0_ADDRESS_BASE + 0x64)
#define IC0_CLR_GEN_CALL            (IC0_ADDRESS_BASE + 0x68)
#define IC0_ENABLE                  (IC0_ADDRESS_BASE + 0x6C)
#define IC0_STATUS                  (IC0_ADDRESS_BASE + 0x70)
#define IC0_TXFLR                   (IC0_ADDRESS_BASE + 0x74)
#define IC0_RXFLR                   (IC0_ADDRESS_BASE + 0x78)
/*#define Rvd                       (IC0_ADDRESS_BASE + 0x7C)*/
#define IC0_TX_ABRT_SOURCE          (IC0_ADDRESS_BASE + 0x80)
/*#define Rvd                       (IC0_ADDRESS_BASE + 0x84)*/
#define IC0_DMA_CR                  (IC0_ADDRESS_BASE + 0x88)
#define IC0_DMA_TDLR                (IC0_ADDRESS_BASE + 0x8C)
#define IC0_DMA_RDLR                (IC0_ADDRESS_BASE + 0x90)
#define IC0_SDA_SETUP               (IC0_ADDRESS_BASE + 0x94)
#define IC0_COMP_PARAM_1            (IC0_ADDRESS_BASE + 0xF4)
#define IC0_COMP_VERSION            (IC0_ADDRESS_BASE + 0xF8)
#define IC0_COMP_TYPE               (IC0_ADDRESS_BASE + 0xFC)



// I2C
unsigned int IC_CON[]             = {IC0_CON            , MIS_IC1_CON_reg            , MIS_IC2_CON_reg              };
unsigned int IC_TAR[]             = {IC0_TAR            , MIS_IC1_TAR_reg            , MIS_IC2_TAR_reg              };
unsigned int IC_SAR[]             = {IC0_SAR            , MIS_IC1_SAR_reg            , MIS_IC2_SAR_reg              };
unsigned int IC_HS_MADDR[]        = {IC0_HS_MADDR       , MIS_IC1_HS_MADDR_reg       , MIS_IC2_HS_MADDR_reg         };
unsigned int IC_DATA_CMD[]        = {IC0_DATA_CMD       , MIS_IC1_DATA_CMD_reg       , MIS_IC2_DATA_CMD_reg         };
unsigned int IC_SS_SCL_HCNT[]     = {IC0_SS_SCL_HCNT    , MIS_IC1_SS_SCL_HCNT_reg    , MIS_IC2_SS_SCL_HCNT_reg      };
unsigned int IC_SS_SCL_LCNT[]     = {IC0_SS_SCL_LCNT    , MIS_IC1_SS_SCL_LCNT_reg    , MIS_IC2_SS_SCL_LCNT_reg      };
unsigned int IC_FS_SCL_HCNT[]     = {IC0_FS_SCL_HCNT    , MIS_IC1_FS_SCL_HCNT_reg    , MIS_IC2_FS_SCL_HCNT_reg      };
unsigned int IC_FS_SCL_LCNT[]     = {IC0_FS_SCL_LCNT    , MIS_IC1_FS_SCL_LCNT_reg    , MIS_IC2_FS_SCL_LCNT_reg      };
unsigned int IC_INTR_STAT[]       = {IC0_INTR_STAT      , MIS_IC1_INTR_STAT_reg      , MIS_IC2_INTR_STAT_reg        };
unsigned int IC_INTR_MASK[]       = {IC0_INTR_MASK      , MIS_IC1_INTR_MASK_reg      , MIS_IC2_INTR_MASK_reg        };
unsigned int IC_RAW_INTR_STAT[]   = {IC0_RAW_INTR_STAT  , MIS_IC1_RAW_INTR_STAT_reg  , MIS_IC2_RAW_INTR_STAT_reg    };
unsigned int IC_RX_TL[]           = {IC0_RX_TL          , MIS_IC1_RX_TL_reg          , MIS_IC2_RX_TL_reg            };
unsigned int IC_TX_TL[]           = {IC0_TX_TL          , MIS_IC1_TX_TL_reg          , MIS_IC2_TX_TL_reg            };
unsigned int IC_CLR_INTR[]        = {IC0_CLR_INTR       , MIS_IC1_CLR_INTR_reg       , MIS_IC2_CLR_INTR_reg         };
unsigned int IC_CLR_RX_UNDER[]    = {IC0_CLR_RX_UNDER   , MIS_IC1_CLR_RX_UNDER_reg   , MIS_IC2_CLR_RX_UNDER_reg     };
unsigned int IC_CLR_RX_OVER[]     = {IC0_CLR_RX_OVER    , MIS_IC1_CLR_RX_OVER_reg    , MIS_IC2_CLR_RX_OVER_reg      };
unsigned int IC_CLR_TX_OVER[]     = {IC0_CLR_TX_OVER    , MIS_IC1_CLR_TX_OVER_reg    , MIS_IC2_CLR_TX_OVER_reg      };
unsigned int IC_CLR_RD_REQ[]      = {IC0_CLR_RD_REQ     , MIS_IC1_CLR_RD_REQ_reg     , MIS_IC2_CLR_RD_REQ_reg       };
unsigned int IC_CLR_TX_ABRT[]     = {IC0_CLR_TX_ABRT    , MIS_IC1_CLR_TX_ABRT_reg    , MIS_IC2_CLR_TX_ABRT_reg      };
unsigned int IC_CLR_RX_DONE[]     = {IC0_CLR_RX_DONE    , MIS_IC1_CLR_RX_DONE_reg    , MIS_IC2_CLR_RX_DONE_reg      };
unsigned int IC_CLR_ACTIVITY[]    = {IC0_CLR_ACTIVITY   , MIS_IC1_CLR_ACTIVITY_reg   , MIS_IC2_CLR_ACTIVITY_reg     };
unsigned int IC_CLR_STOP_DET[]    = {IC0_CLR_STOP_DET   , MIS_IC1_CLR_STOP_DET_reg   , MIS_IC2_CLR_STOP_DET_reg     };
unsigned int IC_CLR_START_DET[]   = {IC0_CLR_START_DET  , MIS_IC1_CLR_START_DET_reg  , MIS_IC2_CLR_START_DET_reg    };
unsigned int IC_CLR_GEN_CALL[]    = {IC0_CLR_GEN_CALL   , MIS_IC1_CLR_GEN_CALL_reg   , MIS_IC2_CLR_GEN_CALL_reg     };
unsigned int IC_ENABLE[]          = {IC0_ENABLE         , MIS_IC1_ENABLE_reg         , MIS_IC2_ENABLE_reg           };
unsigned int IC_STATUS[]          = {IC0_STATUS         , MIS_IC1_STATUS_reg         , MIS_IC2_STATUS_reg           };
unsigned int IC_TXFLR[]           = {IC0_TXFLR          , MIS_IC1_TXFLR_reg          , MIS_IC2_TXFLR_reg            };
unsigned int IC_RXFLR[]           = {IC0_RXFLR          , MIS_IC1_RXFLR_reg          , MIS_IC2_RXFLR_reg            };
unsigned int IC_TX_ABRT_SOURCE[]  = {IC0_TX_ABRT_SOURCE , MIS_IC1_TX_ABRT_SOURCE_reg , MIS_IC2_TX_ABRT_SOURCE_reg   };
unsigned int IC_DMA_CR[]          = {IC0_DMA_CR         , MIS_IC1_DMA_CR_reg         , MIS_IC2_DMA_CR_reg           };
unsigned int IC_DMA_TDLR[]        = {IC0_DMA_TDLR       , MIS_IC1_DMA_TDLR_reg       , MIS_IC2_DMA_TDLR_reg         };
unsigned int IC_DMA_RDLR[]        = {IC0_DMA_RDLR       , MIS_IC1_DMA_RDLR_reg       , MIS_IC2_DMA_RDLR_reg         };
unsigned int IC_COMP_PARAM_1[]    = {IC0_COMP_PARAM_1   , MIS_IC1_COMP_PARAM_1_reg   , MIS_IC2_COMP_PARAM_1_reg     };
unsigned int IC_COMP_VERSION[]    = {IC0_COMP_VERSION   , MIS_IC1_COMP_VERSION_reg   , MIS_IC2_COMP_VERSION_reg     };
unsigned int IC_COMP_TYPE[]       = {IC0_COMP_TYPE      , MIS_IC1_COMP_TYPE_reg      , MIS_IC2_COMP_TYPE_reg        };

//IC_CON
#define IC_SLAVE_DISABLE    0x0040
#define IC_RESTART_EN       0x0020
#define IC_10BITADDR_MASTER 0x0010
#define IC_10BITADDR_SLAVE  0x0008
#define IC_MASTER_MODE      0x0001

#define IC_SPEED            0x0006
#define SPEED_SS            0x0002
#define SPEED_FS            0x0004
#define SPEED_HS            0x0006

//ID_DATA
#define READ_CMD            0x0100

// INT
#define GEN_CALL_BIT        0x800
#define START_DET_BIT       0x400
#define STOP_DET_BIT        0x200
#define ACTIVITY_BIT        0x100
#define RX_DONE_BIT         0x080
#define TX_ABRT_BIT         0x040
#define RD_REQ_BIT          0x020
#define TX_EMPTY_BIT        0x010
#define TX_OVER_BIT         0x008
#define RX_FULL_BIT         0x004
#define RX_OVER_BIT         0x002
#define RX_UNDER_BIT        0x001

// STATUS
#define ST_RFF_BIT          0x10
#define ST_RFNE_BIT         0x08
#define ST_TFE_BIT          0x04
#define ST_TFNF_BIT         0x02
#define ST_ACTIVITY_BIT     0x01

// MIS_ISR
// I2C0 interrupt flag. Ref doc sisius-ISO_MISC_OFF_arch_spec
#define I2C0_INT                    (0x00000001<<1)
#define I2C1_INT                    (0x00000001<<26)

// IC_TX_ABRT_SOURCE
#define ABRT_SLVRD_INTX             0x8000
#define ABRT_SLV_ARB_LOST           0x4000
#define ABRT_SLV_FLUSH_TX_FIFO      0x2000
#define ABRT_ARB_LOST               0x1000
#define ABR_MASTER_DIS              0x0800
#define ABRT_10B_RD_NORSTRT         0x0400
#define ABRT_SBYTE_NORSTRT          0x0200
#define ABRT_HS_NORSTRT             0x0100
#define ABRT_SBYTE_ACKDET           0x0080
#define ABRT_HS_ACKDET              0x0040
#define ABRT_GCALL_READ             0x0020
#define ABRT_GCALL_NOACK            0x0010
#define ABRT_TXDATA_NOACK           0x0008
#define ABRT_10ADDR2_NOACK          0x0004
#define ABRT_10ADDR1_NOACK          0x0002
#define ABRT_7ADDR_NOACK            0x0001

#endif
