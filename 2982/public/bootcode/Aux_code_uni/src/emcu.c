/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "reset_def.h"
#include "error_type.h"
#include "mcp.h"
//#include "aux_print.h"
#include "emcu.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int s_PageSize;
extern unsigned int s_BlockSize;
extern unsigned int s_PagePerBlock;

/************************************************************************
 *  Public variables
 ************************************************************************/


/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int nf_read_image(unsigned int dst_addr,
                unsigned int *page_addr,
                unsigned int length,
                unsigned int page_count,
                const unsigned char magic);
extern int (*rom_nf_read_image)(unsigned int dst_addr,
                                unsigned int *page_addr,
                                unsigned int length,
                                unsigned int page_count,
                                const unsigned char magic);
extern int mmc_blk_read( unsigned int blk_addr,
                unsigned int blk_cnt,
                unsigned char * data_buffer );

extern int (*rom_mmc_blk_read)(unsigned int blk_addr, unsigned int blk_cnt, unsigned char * data_buffer);


/************************************************************************
 *  Public function prototype
 ************************************************************************/
//extern void ax_print(char *format, ...);

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

/*
#define EMMC_EMCU_BLK       0xE0    //ecpu.bin located at eMMC blk(addr 0x1c000 byte)
#define EMMC_EMCU_BLK_WOW   0xF0    //ecpu_wow.bin located at eMMC blk(addr 0x1E000 byte)

#define EMMC_SRAM_BUF       (0xB8075000)
#define EMMC_SRAM_BUF_WOW   (0xB8077000)

mmc write "DDR_ADDR_HEX_SOURCE" "EMMC_BLK_HEX" "BLK_LEN_HEX"
mmc read  "DDR_ADDR_HEX_TARGET" "EMMC_BLK_HEX" "BLK_LEN_HEX"
tftpput 1000000 20000 test

Example
1. write ecpu.bin(8k) from DDR 0x4000 to eMMC 0xE0 block
mmc write 0x4000 0xE0 0x10
mmc read  0x1000000 0xE0 0x10
tftpput 0x1000000 0x2000 ecpu_bin.bin

2. write ecpu_wow.bin(8k) from DDR 0x6000 to eMMC 0xF0 block
mmc write 0x6000 0xF0 0x10
mmc read  0x1000000 0xF0 0x10
tftpput 0x1000000 0x20000 ecpu_wow_bin.bin

*/
int download_8051_imem(const int flash_type)
{
    int i;
    int res = 0;
    unsigned int value;
    unsigned int reginfo;
    unsigned char *buf;
    unsigned int sys_flash_current_pos;
    unsigned int pagesize = s_PageSize;
    unsigned int blocksize = s_BlockSize;
    unsigned int pageperblock = s_PagePerBlock;

    RELEASE_EMCU_TOP();
    printf("\r\n%s(%d)\r\n",
                __func__,__LINE__);

    /* === Standby51 operation start === */
    switch (flash_type) {
        //case SPI_FLASH_BOOT:
        //  res = get_dte_bootcode_spi(target_addr, g_dte_bootcode_area_size);
        //  break;

        //case SPI_NAND_FLASH_BOOT:
        //  res = get_dte_bootcode_spi_n(target_addr, g_dte_bootcode_area_size);
        //  break;

        case NAND_FLASH_BOOT:
            printf("\r\nget ecpu.bin from Nand !!!\r\n");
            sys_flash_current_pos = EMCU_IMAGE_START_BLOCK_NO*pageperblock + EMCU_CERT_PAGE_COUNT;		// from (block5 page1)
            if( nf_read_image(EMMC_SRAM_BUF,
                                  &sys_flash_current_pos,
                                  IMAGE_SIZE, 0, BLOCK_EMCU))
            {
                res = ERR_GET_EMCU_FW_FAILED;
            }
            break;

        case EMMC_BOOT:
            /* get standby51 code from eMMC */
            printf("\r\nget ecpu.bin from eMMC !!!\r\n");
            REG32(0xb801084c) &= ~0x8;  // switch Dbus to DDR
            if(mmc_blk_read(EMMC_EMCU_BLK,
                                IMAGE_SIZE_BLK,
                                (unsigned char *)EMMC_SRAM_BUF))
            {
                res = ERR_GET_EMCU_FW_FAILED;
            }
            break;

        case UNKNOWN_BOOT:
        default:
            printf("\r\nUnknow flash type!!!\r\n");
            res = ERR_UNKNOWN_TYPE;
            break;
    }

    if(res){
        goto ERR_OUT;
    }

    buf = (unsigned char *)EMMC_SRAM_BUF;

    /*
     * reference rtd298X-DesignSpec-CRT.doc
     * rtd298X can load emcu one time every power on cycle
     * we can load emcu code again until suspend.
     */
    //assert EMCU reset
    rtd_outl(EMCU_RESET_REG, rtd_inl(EMCU_RESET_REG) & ~(RSTN_EMCU_CORE|RSTN_EMCU_TOP));	//RSTN_EMCU_TOP &  RSTN_EMCU_CORE= 0//for re-load code concern
	rtd_outl(EMCU_RESET_REG, rtd_inl(EMCU_RESET_REG) | RSTN_EMCU_TOP);    //reset release (bit9)
    rtd_outl(EMCU_CLKEN_REG, rtd_inl(EMCU_CLKEN_REG) & ~CLKEN_EMCU_CORE);   //clock off (bit9)
    rtd_outl(EMCU_RESET_REG, rtd_inl(EMCU_RESET_REG) & ~RSTN_EMCU_CORE);   //reset alert (bit9)
    rtd_outl(EMCU_RESET_REG, rtd_inl(EMCU_RESET_REG) | RSTN_EMCU_CORE);    //reset release (bit9)
    rtd_outl(EMCU_SYSTEM_CPU_PROGRAM_ENABLE, 1);  //enable CPU_PGM_EN

    // Write to standby mode
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL) & ~0x3fff ); //set address(bit[13:0) is 0x0000
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL)| (_BIT16));  //set reload is 1
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL)& ~(_BIT16)); //set reload is 0, then address will be set to IP
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL)| (_BIT15));

    for (i=0; i<(IMAGE_SIZE/4); i++){
        value = (((unsigned int) buf[3 + i*4])<<24) |
                (((unsigned int) buf[2 + i*4])<<16) |
                (((unsigned int) buf[1 + i*4])<< 8) |
                buf[0+ i*4];
        /*
        value = (((unsigned int) buf[0 + i*4])<<24)  |
                (((unsigned int) buf[1+ i*4])<<16) |
                (((unsigned int) buf[2+ i*4])<<8) |
                buf[3+ i*4];
        */

        //if(i%4 == 0)
        //    printf("\r\n");
        //printf("[%x]%x ",(i*4),value);

        rtd_outl(EMCU_IMEM_DATA, value);
    }

    printf("\r\nwrite to imem for standby mode done\r\n");


#if 0 //disable net51 to avoid some problem
    /* === Net51 operation start === */

    switch (flash_type) {
        //case SPI_FLASH_BOOT:
        //  res = get_dte_bootcode_spi(target_addr, g_dte_bootcode_area_size);
        //  break;

        //case SPI_NAND_FLASH_BOOT:
        //  res = get_dte_bootcode_spi_n(target_addr, g_dte_bootcode_area_size);
        //  break;

        case NAND_FLASH_BOOT:
            sys_flash_current_pos = EMCU_IMAGE_START_BLOCK_NO*pageperblock + EMCU_CERT_PAGE_COUNT + IMAGE_SIZE/pagesize;
            if( nf_read_image(EMMC_SRAM_BUF_WOW,
                                &sys_flash_current_pos,
                                IMAGE_SIZE_WOW, IMAGE_SIZE/pagesize, BLOCK_EMCU))
            {
                res = ERR_GET_EMCU_FW_FAILED;
            }
            break;

        case EMMC_BOOT:
            /* get net51 code from eMMC */
            REG32(0xb801084c) &= ~0x8;  // switch Dbus to DDR
            if( mmc_blk_read( EMMC_EMCU_BLK_WOW,
                                    IMAGE_SIZE_WOW_BLK,
                                    (unsigned char *)EMMC_SRAM_BUF_WOW))
            {
                res = ERR_GET_EMCU_FW_FAILED;
            }
            break;

        case UNKNOWN_BOOT:
        default:
            res = ERR_UNKNOWN_TYPE;
            printf("\r\nUnknow flash type!!!\r\n");
            break;
    }

    if(res)
        goto ERR_OUT;
#endif

    //assert NET51 reset
#define GETN_RST 			0xb8016C00
#define RSTN_GETN_OSC		(0x01UL<<4)
#define RSTN_GETN_PHY		(0x01UL<<3)
#define RSTN_GETN			(0x01UL<<2)
#define RSTN_EMCU2_CORE		(0x01UL<<1)
#define RSTN_EMCU2_TOP		(0x01UL<<0)

#define GETN_CLKEN 			0xb8016C04
#define CLKEN_GETN_OSC		(0x01UL<<4)
#define CLKEN_GETN			(0x01UL<<2)
#define CLKEN_EMCU2_CORE	(0x01UL<<1)

	rtd_outl(GETN_RST,	 rtd_inl(GETN_RST)	 & ~(RSTN_EMCU2_CORE));		//**RSTN_EMCU2_CORE=0 @ 0x1801_6C00
	rtd_outl(GETN_CLKEN, rtd_inl(GETN_CLKEN) & ~(CLKEN_EMCU2_CORE));	//CLKEN_EMCU2_CORE = 0
	rtd_outl(GETN_RST,   rtd_inl(GETN_RST) 	 & ~(RSTN_EMCU2_TOP));		//RSTN_EMCU_TOP = 0
	rtd_outl(GETN_RST,   rtd_inl(GETN_RST) 	 |   RSTN_EMCU2_TOP);		//RSTN_EMCU_TOP = 0
	rtd_outl(GETN_CLKEN, rtd_inl(GETN_CLKEN) |   CLKEN_EMCU2_CORE); 	//**CLKEN_EMCU2_CORE=1 @0x1801_6C04

#if 0 //disable net51 to avoid some problem
	rtd_outl(EMCU1_SYSTEM_CPU_PROGRAM_ENABLE, 1);
    // Write to GTEN mode
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL) & ~0x3fff ); //set address(bit[13:0) is 0x0000
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL)| (_BIT16));  //set reload is 1
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL)& ~(_BIT16)); //set reload is 0, then address will be set to IP
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL)| (_BIT15));

    buf = (unsigned char *)EMMC_SRAM_BUF_WOW;
    for (i=0; i<(IMAGE_SIZE_WOW/4); i++){
        value = (((unsigned int) buf[3 + i*4])<<24) |
                (((unsigned int) buf[2 + i*4])<<16) |
                (((unsigned int) buf[1 + i*4])<< 8) |
                buf[0+ i*4];

                rtd_outl(EMCU1_IMEM_DATA, value);
    }
    printf("\r\nwrite to imem for GTEN done\r\n");
#endif

    //Readback IMEM for checking
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL) & ~0x3fff );   //set address is 0x0000
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL) | (_BIT16));     //set reload is 1
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL) & ~(_BIT16));    //set reload is 0, then address will be set to IP
    rtd_outl(EMCU_IMEM_CONTROL, rtd_inl(EMCU_IMEM_CONTROL) | (_BIT15));

    buf = (unsigned char *)EMMC_SRAM_BUF;
    for (i=0; i<(IMAGE_SIZE / 4); i++) {
        reginfo = rtd_inl(EMCU_IMEM_DATA);
        value = (((unsigned int) buf[3 + i*4])<<24) |
                (((unsigned int) buf[2 + i*4])<<16) |
                (((unsigned int) buf[1 + i*4])<< 8) |
                buf[0+ i*4];
        /*
        value = (((unsigned int) buf[0 + i*4])<<24) |
                (((unsigned int) buf[1+ i*4])<<16) |
                (((unsigned int) buf[2+ i*4])<<8) |
                buf[3+ i*4];
        */
        //if(i%4 == 0)
        //    printf("\r\n");
        //printf("[%x]%x(%x) ",(i*4),value,reginfo);

        if( reginfo  != value)
        {
            printf("\r\nI_mem compare fail for standby mode\r\n");
            rtd_outl(EMCU_SYSTEM_CPU_PROGRAM_ENABLE, 0);  //disable CPU_PGM_EN
            res = ERR_GET_EMCU_FW_FAILED;
            goto ERR_OUT;
        }
    }	
    rtd_outl(EMCU_SYSTEM_CPU_PROGRAM_ENABLE, 0);  //disable CPU_PGM_EN
	//hexdump("EMCU buf", (void *)EMMC_SRAM_BUF, IMAGE_SIZE);
	printf("\r\ncheck imem for standby ok\r\n");

#if 0 //disable net51 to avoid some problem
    //Readback IMEM for GTEN for checking
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL) & ~0x3fff );   //set address is 0x0000
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL) | (_BIT16));     //set reload is 1
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL) & ~(_BIT16));    //set reload is 0, then address will be set to IP
    rtd_outl(EMCU1_IMEM_CONTROL, rtd_inl(EMCU1_IMEM_CONTROL) | (_BIT15));

    buf = (unsigned char *)EMMC_SRAM_BUF_WOW;
    for (i=0; i<(IMAGE_SIZE_WOW/4); i++) {
        value = (((unsigned int) buf[3 + i*4])<<24) |
                (((unsigned int) buf[2 + i*4])<<16) |
                (((unsigned int) buf[1 + i*4])<< 8) |
                buf[0+ i*4];
        if( rtd_inl(EMCU1_IMEM_DATA)  != value)
        {
            rtd_outl(EMCU1_SYSTEM_CPU_PROGRAM_ENABLE, 0);  //disable CPU_PGM_EN
            printf("\r\nI_mem compare fail for GTEN\r\n");
            res = ERR_GET_EMCU_FW_FAILED;
            goto ERR_OUT;
        }
    }
    rtd_outl(EMCU1_SYSTEM_CPU_PROGRAM_ENABLE, 0);  //disable CPU_PGM_EN
	//hexdump("EMCU WOW buf", (void *)EMMC_SRAM_BUF_WOW, IMAGE_SIZE_WOW);
	//hexdump("CP 42K end", (void *) CP42K_SRAM_ADDR + CP42K_SRAM_SIZE, IMAGE_SIZE_WOW);
    rtd_outl(GETN_RST,	 rtd_inl(GETN_RST)	 | (RSTN_EMCU2_CORE));	// RSTN_EMCU_CORE = 1
    printf("\r\ncheck imem for GTEN ok\r\n");
#endif
    /* hold on reset until kernel to wakeup 51 */
    //rtd_outl(0xb8060044, rtd_inl(0xb8060044) | _BIT9);    //clock off
    //rtd_outl(0xb8060034, rtd_inl(0xb8060034) | _BIT9);    //reset bit9
    //rtd_outl(0xb8016c10, rtd_inl(0xb8016c10) | _BIT0);    //bit0: WOW_GMAC_CKLSEL = 1
    //rtd_outl(0xb8016c00, rtd_inl(0xb8016c00) | _BIT1);    //bit1: RSTN_EMCU2_CORE = 1
ERR_OUT:
    return res;
}


/* end of file */

