#ifndef __RTKMMC_H__
#define __RTKMMC_H__

/************************************************************************
 * DEBUG CONTROL
*************************************************************************/
#define EMMC_RTD299X
#define EMMC_DEBUG
//#define EMMC_DEBUG_SHOWCMD
//#define EMMC_SHOW_CSD
//#define EMMC_SHOW_CID
//#define EMMC_SHOW_EXTCSD
#define EMMC_MAX_XFER_BLKCNT 256

/************************************************************************
 * PRINT MESSAGE CONTROL
*************************************************************************/
//#define THIS_IS_FLASH_WRITE_U_ENV

#define EMMC_DRVNAME "emmc:"
#ifdef THIS_IS_FLASH_WRITE_U_ENV
	#include "sysdefs.h"
	#include "dvrboot_inc/util.h"
	#define UPRINTF(fmt, args...)			\
				if( rtprintf ) {			\
					rtprintf(fmt,## args);	\
				}
	#define EXT_CSD_CMD_SET_NORMAL		(1 << 0)
	#define EXT_CSD_CMD_SET_SECURE		(1 << 1)
	#define EXT_CSD_CMD_SET_CPSECURE	(1 << 2)
	#define EXT_CSD_CARD_TYPE_26		(1 << 0)
	#define EXT_CSD_CARD_TYPE_52		(1 << 1)
	#define EXT_CSD_BUS_WIDTH_1			0
	#define EXT_CSD_BUS_WIDTH_4			1
	#define EXT_CSD_BUS_WIDTH_8			2
#else
	#include <config.h>
	#include <common.h>
	#include <command.h>
	#include <mmc.h>
	#include <part.h>
	#include <malloc.h>
	#include <mmc.h>
	#include <asm/errno.h>
	#include <asm/io.h>
	#define UPRINTF(fmt, args...)			\
				printf(fmt,## args)
#endif

#ifdef EMMC_DEBUG
    #define mmcinfo(fmt, args...) \
               UPRINTF(EMMC_DRVNAME fmt,## args)
#else
    #define mmcinfo(fmt, args...)
#endif

#ifdef EMMC_DEBUG_SHOWCMD
	#define mmcinfo_cmd(fmt, args...) \
				UPRINTF(EMMC_DRVNAME fmt,## args)
#else
	#define mmcinfo_cmd(fmt, args...)
#endif

/************************************************************************
 * MMC BIT DATA READING
*************************************************************************/
#define UNSTUFF_BITS(resp,start,size)                   						\
    ({                              											\
        const int __size = size;                								\
        const unsigned int __mask = (__size < 32 ? 1 << __size : 0) - 1; 		\
        const int __off = 3 - ((start) / 32);           						\
        const int __shft = (start) & 31;            							\
        unsigned int __res;                      								\
                                    											\
        __res = resp[__off] >> __shft;              							\
        if (__size + __shft > 32)               								\
            __res |= resp[__off-1] << ((32 - __shft) % 32); 					\
        __res & __mask;                     									\
    })

/************************************************************************
 * REALTEK CONTROL REGISTER ACCESSING METHOD
*************************************************************************/
#define cr_writel(value,addr)   	rtd_outl(addr,value)
#define cr_readl(addr)          	rtd_inl(addr)

/************************************************************************
 *
*************************************************************************/
#define EMMC_VDD_30_31  			(0x00040000UL)  /* VDD voltage 3.0 ~ 3.1 */
#define EMMC_VDD_31_32  			(0x00080000UL)  /* VDD voltage 3.1 ~ 3.2 */
#define EMMC_VDD_32_33  			(0x00100000UL)  /* VDD voltage 3.2 ~ 3.3 */
#define EMMC_VDD_33_34  			(0x00200000UL)  /* VDD voltage 3.3 ~ 3.4 */
#define EMMC_VDD_34_35  			(0x00400000UL)  /* VDD voltage 3.4 ~ 3.5 */
#define EMMC_VDD_35_36  			(0x00800000UL)  /* VDD voltage 3.5 ~ 3.6 */
#define MMC_CARD_READY   			(0x80000000UL)  /* Card Power up status bit */
#define MMC_SECTOR_ADDR  			(0x40000000UL)

#define EMMC_VDD_REQ    			(EMMC_VDD_35_36|EMMC_VDD_34_35|EMMC_VDD_33_34|EMMC_VDD_32_33|EMMC_VDD_31_32|EMMC_VDD_30_31)

/* MMC response type */
#define SD_R0                   	RESP_TYPE_NON|CRC7_CHK_DIS
#define SD_R1                   	RESP_TYPE_6B
#define SD_R1b                  	RESP_TYPE_6B|WAIT_BUSY_EN
#define SD_R2                   	RESP_TYPE_17B
#define SD_R3                   	RESP_TYPE_6B|CRC7_CHK_DIS
#define SD_R4                   	RESP_TYPE_6B
#define SD_R5                   	RESP_TYPE_6B

/* send status event */
#define STATE_IDLE      			0
#define STATE_READY     			1
#define STATE_IDENT     			2
#define STATE_STBY      			3
#define STATE_TRAN      			4
#define STATE_DATA      			5
#define STATE_RCV       			6
#define STATE_PRG       			7
#define STATE_DIS       			8
#define STATE_BTST      			9
#define STATE_SLP       			10

/* eMMC control register definition */
#define CR_IP_RESET_REG             CRT_SOFT_RESET2_VADDR
#define CR_IP_RESET_REG_BIT			(11)

#define CR_IP_CLKEN_REG		 	CRT_CLOCK_ENABLE1_VADDR
#define CR_IP_CLKEN_REG_BIT		(24)

#define GPIO_MUXCFG_0   PINMUX_GPIO_CFG_0_VADDR
#define GPIO_MUXCFG_1   PINMUX_GPIO_CFG_1_VADDR
#define GPIO_MUXCFG_2   PINMUX_GPIO_CFG_2_VADDR
#define GPIO_MUXCFG_3   PINMUX_GPIO_CFG_3_VADDR
#define GPIO_MUXCFG_4   PINMUX_GPIO_CFG_4_VADDR
#define GPIO_MUXCFG_5   PINMUX_GPIO_CFG_5_VADDR
#define GPIO_MUXCFG_6   PINMUX_GPIO_CFG_6_VADDR
#define GPIO_MUXCFG_7   PINMUX_GPIO_CFG_7_VADDR
#define GPIO_MUXCFG_8   PINMUX_GPIO_CFG_8_VADDR
#define GPIO_MUXCFG_9   PINMUX_GPIO_CFG_9_VADDR
#define GPIO_MUXCFG_10  PINMUX_GPIO_CFG_10_VADDR
#define GPIO_MUXCFG_11  PINMUX_GPIO_CFG_11_VADDR
#define GPIO_MUXCFG_12  PINMUX_GPIO_CFG_12_VADDR
#define GPIO_MUXCFG_13  PINMUX_GPIO_CFG_13_VADDR
#define GPIO_MUXCFG_14  PINMUX_GPIO_CFG_14_VADDR
#define GPIO_MUXCFG_15  PINMUX_GPIO_CFG_15_VADDR
#define GPIO_MUXCFG_16  PINMUX_GPIO_CFG_16_VADDR
#define GPIO_MUXCFG_17  PINMUX_GPIO_CFG_17_VADDR
#define GPIO_MUXCFG_18  PINMUX_GPIO_CFG_18_VADDR
#define GPIO_MUXCFG_19  PINMUX_GPIO_CFG_19_VADDR
#define GPIO_MUXCFG_20  PINMUX_GPIO_CFG_20_VADDR
#define GPIO_MUXCFG_21  PINMUX_GPIO_CFG_21_VADDR
#define GPIO_MUXCFG_22  PINMUX_GPIO_CFG_22_VADDR
#define GPIO_MUXCFG_23  PINMUX_GPIO_CFG_23_VADDR
#define GPIO_MUXCFG_24  PINMUX_GPIO_CFG_24_VADDR
#define GPIO_MUXCFG_25  PINMUX_GPIO_CFG_25_VADDR
#define GPIO_MUXCFG_26  PINMUX_GPIO_CFG_26_VADDR
#define GPIO_MUXCFG_27  PINMUX_GPIO_CFG_27_VADDR
#define GPIO_MUXCFG_28  PINMUX_GPIO_CFG_28_VADDR
#define GPIO_MUXCFG_29  PINMUX_GPIO_CFG_29_VADDR
#define GPIO_MUXCFG_30  PINMUX_GPIO_CFG_30_VADDR
#define GPIO_MUXCFG_31  PINMUX_GPIO_CFG_31_VADDR
#define GPIO_MUXCFG_32  PINMUX_GPIO_CFG_32_VADDR
#define GPIO_MUXCFG_33  PINMUX_GPIO_CFG_33_VADDR

#define ISO_GPDIR1  ISO_GPDIR_1_reg
#define ISO_GPDATO1 ISO_GPDATO_1_reg
#define ISO_GPDATI1 ISO_GPDATI_1_reg


#define CR_BASE_ADDR             	0xb8010800

#define SD_STAT                 	( CR_BASE_ADDR  + 0x00 )        //0xb8010800
#define SD_CONFIGURE1           	( CR_BASE_ADDR  + 0x04 )        //0xb8010804
#define SD_TRANSFER             	( CR_BASE_ADDR  + 0x08 )        //0xb8010808
#define SD_CONFIGURE2           	( CR_BASE_ADDR  + 0x0c )        //0xb801080c
#define SD_CMD0                 	( CR_BASE_ADDR  + 0x10 )        //0xb8010810
#define SD_CMD1                 	( CR_BASE_ADDR  + 0x14 )        //0xb8010814
#define SD_CMD2                 	( CR_BASE_ADDR  + 0x18 )        //0xb8010818
#define SD_CMD3                 	( CR_BASE_ADDR  + 0x1c )        //0xb801081c
#define SD_CMD4                 	( CR_BASE_ADDR  + 0x20 )        //0xb8010820
#define SD_BYTE_CNT_L           	( CR_BASE_ADDR  + 0x24 )        //0xb8010824
#define SD_BYTE_CNT_H           	( CR_BASE_ADDR  + 0x28 )        //0xb8010828
#define SD_BLOCK_CNT_L          	( CR_BASE_ADDR  + 0x2c )        //0xb801082c
#define SD_BLOCK_CNT_H          	( CR_BASE_ADDR  + 0x30 )        //0xb8010830
#define SDIO_INT_CTRL           	( CR_BASE_ADDR  + 0x34 )        //0xb8010834
#define SD_CONFIGURE3           	( CR_BASE_ADDR  + 0x38 )        //0xb8010838
#define CR_DMA_PTR_STATUS       	( CR_BASE_ADDR  + 0x3c )        //0xb801083c
#define CR_DMA_IN_ADDR          	( CR_BASE_ADDR  + 0x40 )        //0xb8010840
#define CR_DMA_OUT_ADDR         	( CR_BASE_ADDR  + 0x44 )        //0xb8010844
#define CR_INT_STATUS           	( CR_BASE_ADDR  + 0x48 )        //0xb8010848
#define CR_INT_MASK             	( CR_BASE_ADDR  + 0x4c )        //0xb801084c
#define CR_REG_MODE_CTRL        	( CR_BASE_ADDR  + 0x50 )        //0xb8010850
#define CR_DES_MODE_CTRL        	( CR_BASE_ADDR  + 0x54 )        //0xb8010854
#define DES_CMD_WR_PORT         	( CR_BASE_ADDR  + 0x58 )        //0xb8010858
#define CR_BIST_0               	( CR_BASE_ADDR  + 0x5c )        //0xb801085c
#define CR_BIST_1               	( CR_BASE_ADDR  + 0x60 )        //0xb8010860
#define CR_BIST_MODE            	( CR_BASE_ADDR  + 0x64 )        //0xb8010864
#define CR_BIST_DONE            	( CR_BASE_ADDR  + 0x68 )        //0xb8010868
#define CR_BIST_FAIL            	( CR_BASE_ADDR  + 0x6c )        //0xb801086c
#define CR_BIST_DRF_MODE        	( CR_BASE_ADDR  + 0x70 )        //0xb8010870
#define CR_BIST_DRF_RESUME      	( CR_BASE_ADDR  + 0x74 )        //0xb8010874
#define CR_BIST_DRF_DONE        	( CR_BASE_ADDR  + 0x78 )        //0xb8010878
#define CR_BIST_PAUSE           	( CR_BASE_ADDR  + 0x7c )        //0xb801087c
#define CR_BIST_DRF_FAIL        	( CR_BASE_ADDR  + 0x80 )        //0xb8010880
#define CP_CTRL                 	( CR_BASE_ADDR  + 0x84 )        //0xb8010884
#define EXT_RSP_0               	( CR_BASE_ADDR  + 0x88 )        //0xb8010888
#define EXT_RSP_1               	( CR_BASE_ADDR  + 0x8c )        //0xb801088c
#define EXT_RSP_2               	( CR_BASE_ADDR  + 0x90 )        //0xb8010890
#define EXT_RSP_3               	( CR_BASE_ADDR  + 0x94 )        //0xb8010894
#define EXT_RSP_4               	( CR_BASE_ADDR  + 0x98 )        //0xb8010898
#define EXT_RSP_5               	( CR_BASE_ADDR  + 0x9c )        //0xb801089c
#define EXT_RSP_6               	( CR_BASE_ADDR  + 0xa0 )        //0xb80108a0
#define EXT_RSP_7               	( CR_BASE_ADDR  + 0xa4 )        //0xb80108a4
#define EXT_RSP_8               	( CR_BASE_ADDR  + 0xa8 )        //0xb80108a8
#define EXT_RSP_9               	( CR_BASE_ADDR  + 0xac )        //0xb80108ac
#define EXT_RSP_10              	( CR_BASE_ADDR  + 0xb0 )        //0xb80108b0
#define EXT_RSP_11              	( CR_BASE_ADDR  + 0xb4 )        //0xb80108b4
#define EXT_RSP_12              	( CR_BASE_ADDR  + 0xb8 )        //0xb80108b8
#define EXT_RSP_13              	( CR_BASE_ADDR  + 0xbc )        //0xb80108bc
#define EXT_RSP_14              	( CR_BASE_ADDR  + 0xc0 )        //0xb80108c0
#define ARB_STS                 	( CR_BASE_ADDR  + 0xc4 )        //0xb80108c4
#define CR_SRAM_BASE            	( CR_BASE_ADDR  + 0xc8 )        //0xb80108c8

#define CR_CARD_RESP6_0         	SD_CMD0                         //0xb8010810
#define CR_CARD_RESP6_1         	SD_CMD1                         //0xb8010814
#define CR_CARD_RESP6_2         	SD_CMD2                         //0xb8010818
#define CR_CARD_RESP6_3         	SD_CMD3                         //0xb801081c
#define CR_CARD_RESP6_4         	SD_CMD4                         //0xb8010820

/* SD_CONFIGURE1 0xb8010804 */
#define MASK_CLOCK_DIV          	(0x00000003UL<<5)
#define CLOCK_DIV_NON           	(0x00000000UL<<5)
#define CLOCK_DIV_256           	(0x00000001UL<<5)
#define CLOCK_DIV_128           	(0x00000002UL<<5)

#define SPEED_MOD_HIGH          	(0x00000001UL<<4)
#define SPEED_MOD_NORM          	(0x00000000UL)
#define DELAY_PHA_NORM          	(0x00000001UL<<3)
#define DELAY_PHA_HIGH          	(0x00000001UL<<2)

#define MASK_BUS_WIDTH          	(0x00000003UL)
#define BUS_WIDTH_1             	(0x00000000UL)
#define BUS_WIDTH_4             	(0x00000001UL)
#define BUS_WIDTH_8             	(0x00000002UL)

/* SD_CONFIGURE2 0xb801080C */
#define CRC7_CAL_DIS            	(0x00000001UL<<7)
#define CRC16_CAL_DIS           	(0x00000001UL<<6)
#define WAIT_BUSY_EN            	(0x00000001UL<<3)
#define CRC7_CHK_DIS            	(0x00000001UL<<2)

#define MASK_RESP_TYPE          	(0x00000003UL)
#define RESP_TYPE_NON           	(0x00000000UL)
#define RESP_TYPE_6B            	(0x00000001UL)
#define RESP_TYPE_17B           	(0x00000002UL)

/* SD_CONFIGURE3 0xb8010838 */
#define RESP_TIMEOUT            	(0x00000001UL<<3)
#define RESP_TIMEOUT_EN         	(0x00000001UL<<2)
#define IGNORE_WRT_ERR          	(0x00000001UL<<1)
#define CLK_TOGGLE_EN           	(0x00000001UL<<0)

/* SD_TRANSFER 0xb8010808 */
#define START_EN                	(0x00000001UL<<7)
#define END_STATE               	(0x00000001UL<<6)
#define ERR_STATUS              	(0x00000001UL<<4)

#define MASK_CMD_CODE           	(0x0000000FUL)
#define SD_NORMALWRITE          	(0x00000000UL)
#define SD_AUTOWRITE3           	(0x00000001UL)
#define SD_AUTOWRITE4           	(0x00000002UL)
#define SD_AUTOREAD3            	(0x00000005UL)
#define SD_AUTOREAD4            	(0x00000006UL)
#define SD_SENDCMDGETRSP        	(0x00000008UL)
#define SD_AUTOWRITE1           	(0x00000009UL)
#define SD_AUTOWRITE2           	(0x0000000AUL)
#define SD_NORMALREAD           	(0x0000000CUL)
#define SD_AUTOREAD1            	(0x0000000DUL)
#define SD_AUTOREAD2            	(0x0000000EUL)

/* SD_STAT 0xb8010800 */
#define CRC7_STATUS             	(0x00000001UL<<7)
#define CRC16_STATUS            	(0x00000001UL<<6)
#define WRT_ERR_BIT             	(0x00000001UL<<5)
#define MASK_WRT_ERR_STA        	(0x00000007UL<<2)
#define DAT0_LEVEL              	(0x00000001UL<<1)
#define MASK_SD_STAT_ERR            (CRC7_STATUS|CRC16_STATUS|WRT_ERR_BIT)

/*
about MASK_WRT_ERR_STA :
 write error bit: reference MMC spec 4.0 P103
    010 ==> data accepted
    101 ==> data rejected due to a CRC error
    110 ==> data rejected due to a write error
*/

/* SD_INT_STATUS 0xb8010848 */
#define RTKCR_INT_WRT_PROTEC    	(0x1UL<<5)
#define RTKCR_INT_CARD_DETEC    	(0x1UL<<4)
#define RTKCR_INT_DECODE_ERROR  	(0x1UL<<2)
#define RTKCR_INT_DECODE_FINISH 	(0x1UL<<1)
#define RTKCR_INT_STATUS_CHANGE 	(0x1UL<<0)
#define RTKCR_INT_CLEAR_ALL     	(RTKCR_INT_DECODE_ERROR|RTKCR_INT_DECODE_FINISH|RTKCR_INT_STATUS_CHANGE)

/* SD_INT_MASK 0xb801084C */
#define RTKCR_CARD_DET_MASK         (0x01UL<<7)
#define RTKCR_DECODE_ERR_MASK       (0x01UL<<6)
#define RTKCR_DECODE_FINISH_MASK    (0x01UL<<5)
#define RTKCR_CARD_STATUS_MASK      (0x01UL<<4)
#define RTKCR_DBUS_OPTION           (0x01UL<<3)
#define RTKCR_GET_PIN_OPTION        (0x01UL<<2)
#define RTKCR_READ_BUS_BUSY_STATUS  (0x01UL<<1)  // no more use at sirius
#define RTKCR_WRITE_OPTION          (0x01UL<<0)

/* CP_CTRL 0xb8010884 */
#define MAP_SEL                 (0x00000001UL<<8)   // data=0x12345678; 0: 0x8765,0x4321; 1:0x5678,0x1234
#define BOOT_FROM_CR            (0x00000001UL<<3)
#define MASK_BUFF_TIMING        (0x00000003UL<<1)   //if value bigger the delay longer
#define BUFF_TIMING_0           (0x00000000UL<<1)
#define BUFF_TIMING_1           (0x00000001UL<<1)
#define BUFF_TIMING_2           (0x00000002UL<<1)
#define BUFF_TIMING_3           (0x00000003UL<<1)
#define CP_EN                   (0x00000001UL)


/* CP_CTRL 0xb8010884 */
#define BOOT_FROM_CR            	(0x00000001UL<<3)
#define MASK_BUFF_TIMING        	(0x00000003UL<<1)
#define BUFF_TIMING_0           	(0x00000000UL<<1)
#define BUFF_TIMING_1           	(0x00000001UL<<1)
#define BUFF_TIMING_2           	(0x00000002UL<<1)
#define BUFF_TIMING_3           	(0x00000003UL<<1)
#define CP_EN                   	(0x00000001UL)

//CRT spec(RTD299X DesignSpec-CRT)


/* *** Realtek CRT register *** */
//#define SYS_CLKSEL          	SYS_CR_CKSEL_reg
#define SYS_CLKSEL          	CRT_CR_CKSEL_VADDR


/* SYS_CR_CKSEL setting bit *** */
#define EMMC_CLKSHT_BIT         	(4)
#define EMMC_CLKSEL_MASK         	(0x07UL<<EMMC_CLKSHT_BIT)

#define CARD_SWITCHCLOCK_50MHZ  	(0x00UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_33MHZ  	(0x01UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_25MHZ  	(0x02UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_20MHZ 	    (0x03UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_16MHZ  	(0x04UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_12MHZ  	(0x05UL<<EMMC_CLKSHT_BIT)
#define CARD_SWITCHCLOCK_10MHZ  	(0x06UL<<EMMC_CLKSHT_BIT)

#define CLOCK_SPEED_GAP          	CARD_SWITCHCLOCK_25MHZ

#define EMMC_DIV_EN                 (0x01UL<<7)
#define CR_DIV_EN                   (0x01UL<<3)

/************************************************************************
 * CLOCK CONTROL
*************************************************************************/
#define EMMC_SOURCE_CLK         CARD_SWITCHCLOCK_16MHZ
#define EMMC_SOURCE_CLK_HI		CARD_SWITCHCLOCK_25MHZ

//#define EMMC_INIT_CLOCK_DIV		CLOCK_DIV_256
#define EMMC_INIT_CLOCK_DIV		CLOCK_DIV_128
#define EMMC_NORMAL_CLOCK_DIV	CLOCK_DIV_NON


/* Standard MMC commands (4.1)              type    argument            response */
/* class 1 */
#define MMC_GO_IDLE_STATE           0       /* bc                           */
#define MMC_SEND_OP_COND            1       /* bcr  [31:0] OCR          R3  */
#define MMC_ALL_SEND_CID            2       /* bcr                      R2  */
#define MMC_SET_RELATIVE_ADDR       3       /* ac   [31:16] RCA         R1  */
#define MMC_SET_DSR                 4       /* bc   [31:16] RCA             */
#define MMC_SLEEP_AWAKE             5       /* ac   [31:16] RCA 15:flg  R1b */
#define MMC_SWITCH                  6       /* ac   [31:0] See below    R1b */
#define MMC_SELECT_CARD             7       /* ac   [31:16] RCA         R1  */
#define MMC_SEND_EXT_CSD            8       /* adtc                     R1  */
#define MMC_SEND_CSD                9       /* ac   [31:16] RCA         R2  */
#define MMC_SEND_CID                10      /* ac   [31:16] RCA         R2  */
#define MMC_READ_DAT_UNTIL_STOP     11      /* adtc [31:0] dadr         R1  */
#define MMC_STOP_TRANSMISSION       12      /* ac                       R1b */
#define MMC_SEND_STATUS             13      /* ac   [31:16] RCA         R1  */
#define MMC_GO_INACTIVE_STATE       15      /* ac   [31:16] RCA             */
#define MMC_SPI_READ_OCR            58      /* spi                      spi_R3 */
#define MMC_SPI_CRC_ON_OFF          59      /* spi  [0:0] flag          spi_R1 */

  /* class 2 */
#define MMC_SET_BLOCKLEN            16      /* ac   [31:0] block len    R1  */
#define MMC_READ_SINGLE_BLOCK       17      /* adtc [31:0] data addr    R1  */
#define MMC_READ_MULTIPLE_BLOCK     18      /* adtc [31:0] data addr    R1  */

  /* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP    20      /* adtc [31:0] data addr    R1  */

  /* class 4 */
#define MMC_SET_BLOCK_COUNT         23      /* adtc [31:0] data addr    R1  */
#define MMC_WRITE_BLOCK             24      /* adtc [31:0] data addr    R1  */
#define MMC_WRITE_MULTIPLE_BLOCK    25      /* adtc                     R1  */
#define MMC_PROGRAM_CID             26      /* adtc                     R1  */
#define MMC_PROGRAM_CSD             27      /* adtc                     R1  */

  /* class 6 */
#define MMC_SET_WRITE_PROT          28      /* ac   [31:0] data addr    R1b */
#define MMC_CLR_WRITE_PROT          29      /* ac   [31:0] data addr    R1b */
#define MMC_SEND_WRITE_PROT         30      /* adtc [31:0] wpdata addr  R1  */

  /* class 5 */
#define MMC_ERASE_GROUP_START       35      /* ac   [31:0] data addr    R1  */
#define MMC_ERASE_GROUP_END         36      /* ac   [31:0] data addr    R1  */
#define MMC_ERASE                   38      /* ac                       R1b */

  /* class 9 */
#define MMC_FAST_IO                 39      /* ac   <Complex>           R4  */
#define MMC_GO_IRQ_STATE            40      /* bcr                      R5  */

  /* class 7 */
#define MMC_LOCK_UNLOCK             42      /* adtc                     R1b */

  /* class 8 */
#define MMC_APP_CMD                 55      /* ac   [31:16] RCA         R1  */
#define MMC_GEN_CMD                 56      /* adtc [0] RD/WR           R1  */
#if 0
#define R1_OUT_OF_RANGE         	(0x01UL << 31)   /* er, c */
#define R1_ADDRESS_ERROR        	(0x01UL << 30)   /* erx, c */
#define R1_BLOCK_LEN_ERROR      	(0x01UL << 29)   /* er, c */
#define R1_ERASE_SEQ_ERROR      	(0x01UL << 28)   /* er, c */
#define R1_ERASE_PARAM          	(0x01UL << 27)   /* ex, c */
#define R1_WP_VIOLATION         	(0x01UL << 26)   /* erx, c */
#define R1_CARD_IS_LOCKED       	(0x01UL << 25)   /* sx, a */
#define R1_LOCK_UNLOCK_FAILED   	(0x01UL << 24)   /* erx, c */
#define R1_COM_CRC_ERROR        	(0x01UL << 23)   /* er, b */
#define R1_ILLEGAL_COMMAND      	(0x01UL << 22)   /* er, b */
#define R1_CARD_ECC_FAILED      	(0x01UL << 21)   /* ex, c */
#define R1_CC_ERROR             	(0x01UL << 20)   /* erx, c */
#define R1_ERROR                	(0x01UL << 19)   /* erx, c */
#define R1_UNDERRUN             	(0x01UL << 18)   /* ex, c */
#define R1_OVERRUN              	(0x01UL << 17)   /* ex, c */
#define R1_CID_CSD_OVERWRITE    	(0x01UL << 16)   /* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP        	(0x01UL << 15)   /* sx, c */
#define R1_CARD_ECC_DISABLED    	(0x01UL << 14)   /* sx, a */
#define R1_ERASE_RESET          	(0x01UL << 13)   /* sr, c */
#endif
#define R1_STATUS(x)            	(x & 0xFFFFE000)
#define R1_CURRENT_STATE(x)     	((x & 0x00001E00) >> 9) /* sx, b (4 bits) */
#define R1_READY_FOR_DATA       	(0x01UL << 8)    /* sx, a */
#define R1_SWITCH_ERROR         	(0x01UL << 7)    /* sx, c */
//#define R1_APP_CMD              	(0x01UL << 5)    /* sr, c */

#define R1_ERR_CUR_WINDOW       	R1_OUT_OF_RANGE         |\
                                	R1_ADDRESS_ERROR        |\
                                	R1_BLOCK_LEN_ERROR      |\
                                	R1_ERASE_SEQ_ERROR      |\
                                	R1_ERASE_PARAM          |\
                                	R1_WP_VIOLATION         |\
                                	R1_LOCK_UNLOCK_FAILED   |\
                                	R1_COM_CRC_ERROR        |\
                                	R1_ILLEGAL_COMMAND      |\
                                	R1_CARD_ECC_FAILED      |\
                                	R1_CC_ERROR             |\
                                	R1_ERROR                |\
                                	R1_UNDERRUN             |\
                                	R1_OVERRUN              |\
                                	R1_CID_CSD_OVERWRITE    |\
                                	R1_WP_ERASE_SKIP        |\
                                	R1_ERASE_RESET


#define R1_ERR_PER_WINDOW      		R1_OUT_OF_RANGE         |\
                               		R1_ADDRESS_ERROR        |\
                               		R1_ERASE_PARAM          |\
                               		R1_WP_VIOLATION         |\
                               		R1_LOCK_UNLOCK_FAILED   |\
                               		R1_CARD_ECC_FAILED      |\
                               		R1_ERROR                |\
                               		R1_UNDERRUN             |\
                               		R1_OVERRUN              |\
                               		R1_CID_CSD_OVERWRITE    |\
                               		R1_WP_ERASE_SKIP


/*
 * EXT_CSD fields
 */
#define EXT_CSD_BUS_WIDTH       	183     /* R/W */
#define EXT_CSD_HS_TIMING       	185     /* R/W */
#define EXT_CSD_CARD_TYPE       	196     /* RO */
#define EXT_CONT_CSD_VER        	194     /* RO */
#define EXT_CSD_REV             	192     /* RO */
#define EXT_CSD_SEC_CNT         	212     /* RO, 4 bytes */
#define EXT_CSD_S_A_TIMEOUT     	217

/*
 * MMC_SWITCH access modes
 */
#define MMC_SWITCH_MODE_CMD_SET     0x00    /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS    0x01    /* Set bits which are 1 in value */
#define MMC_SWITCH_MODE_CLEAR_BITS  0x02    /* Clear bits which are 1 in value */
#define MMC_SWITCH_MODE_WRITE_BYTE  0x03    /* Set target to value */

/************************************************************************
 *  Structure
 ************************************************************************/
struct rtk_mmc_command {
    unsigned int opcode;
    unsigned int arg;
    unsigned int resp[4];
};


struct rtk_cmd_info {
    struct rtk_mmc_command * 		cmd;
    unsigned char *          		data_buffer;
    unsigned int      		 		byte_count;
    unsigned int      		 		block_count;
    unsigned int      		 		xfer_flag;
		#define RTK_MMC_DATA_DIR_MASK   (0x03UL << 6)    /* bit 6~7 */
		#define RTK_MMC_DATA_SRAM       (0x01UL << 7)
		#define RTK_MMC_DATA_WRITE      (0x01UL << 6)
		#define RTK_MMC_DATA_READ       (0x00UL << 6)    /* can't use this flag to check status, because its value is zero */
		#define RTK_MMC_SRAM_WRITE      (RTK_MMC_DATA_SRAM | RTK_MMC_DATA_WRITE)
		#define RTK_MMC_SRAM_READ       (RTK_MMC_DATA_SRAM | RTK_MMC_DATA_READ)
		#define RTK_MMC_DATA_DIR(pkt)  (pkt->xfer_flag & RTK_MMC_DATA_DIR_MASK)
    unsigned int       				rsp_para;
    unsigned int       				rsp_len;
};

/*
 * emmc profile
 */
struct rtk_mmc_cid {
	unsigned int					manfid;
	char			    			prod_name[8];
	unsigned int					serial;
	unsigned int					oemid;
	unsigned int					year;
	unsigned char					hwrev;
	unsigned char					fwrev;
	unsigned char					month;
};

struct rtk_mmc_csd {
	unsigned char					csd_ver;
	unsigned char					csd_ver2;// from EXT_CSD
	unsigned char					mmca_vsn;
	unsigned short					cmdclass;
	unsigned short					tacc_clks;
	unsigned int					tacc_ns;
	unsigned int					r2w_factor;
	unsigned int					max_dtr;
	unsigned int					read_blkbits;
	unsigned int					write_blkbits;
	unsigned int					capacity;
	unsigned int					read_partial:1,
				        			read_misalign:1,
				        			write_partial:1,
				        			write_misalign:1;
};

struct rtk_mmc_ext_csd {
	unsigned int 					rev;
	unsigned int 					sa_timeout;
	unsigned int 					hs_max_dtr;
	unsigned int 					sectors;
};

typedef struct {
	unsigned int					sector_addressing;
	unsigned int					rca;		    		/* relative card address of device */
	unsigned int					raw_cid[4];	            /* raw card CID */
	unsigned int					raw_csd[4];	            /* raw card CSD */
	struct rtk_mmc_cid	    		cid;					/* card identification */
	struct rtk_mmc_csd	    		csd;					/* card specific */
	struct rtk_mmc_ext_csd  		ext_csd;				/* mmc v4 extended card specific */
} e_device_type;

#ifdef __RTKMMC_C__
	#define EXTERN_CALL
#else
	#define EXTERN_CALL extern
#endif

EXTERN_CALL e_device_type emmc_card;
EXTERN_CALL void mmccr_set_bits_width( unsigned int set_bit );
EXTERN_CALL int rtk_eMMC_init( void );
EXTERN_CALL int rtk_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer );
EXTERN_CALL int rtk_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer );

#endif /* end of file */
