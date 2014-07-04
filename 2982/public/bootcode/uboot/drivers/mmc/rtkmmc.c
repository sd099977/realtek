/*
 *  This is a driver for the eMMC controller found in Realtek RTD299X
 *  SoCs.
 *
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

//#include "mmc.h"
#include "rtkmmc.h"
#include "rbus/mis_reg.h"
#include "rbus/iso_reg.h"
#include "rbus/crt_sys_reg.h"
#include "rbus/rbusPinmuxReg.h"

#define __RTKMMC_C__

unsigned char ext_csd[0x200];
unsigned char dummy_512B[0x200];

extern int mmc_had_been_initialized;;
extern int mmc_ready_to_use;

#ifdef THIS_IS_FLASH_WRITE_U_ENV
static unsigned int rtkmmc_debug_msg;
static unsigned int rtkmmc_off_error_msg_in_init_flow;
#else
unsigned int rtkmmc_debug_msg;
unsigned int rtkmmc_off_error_msg_in_init_flow;
#endif

#ifdef IS_298X_FPGA
#define FPGA_SIRIUS_TEST
#endif

/* mmc spec definition */
const unsigned int tran_exp[] = {
    10000, 100000, 1000000, 10000000,
    0,     0,      0,       0
};

const unsigned char tran_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

const unsigned int tacc_exp[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

const unsigned int tacc_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

extern int mmccr_SendCmd( unsigned int cmd_idx,
                   unsigned int cmd_arg,
                   unsigned int rsp_para,
                   unsigned int * rsp_buffer );

extern void force_set_pinmux(void);
extern void show_pinmux(void);

/************************************************************************
 *  global variable
 ************************************************************************/
unsigned cr_int_status_reg;
e_device_type emmc_card;

/*******************************************************
 *
 *******************************************************/
int mmccr_TriggerXferCmd( unsigned int xferCmdCode, unsigned int max_mdelay_cnt )
{
    unsigned int loops;
    unsigned int sd_transfer_reg = 0;
    unsigned int sd_stat_reg;
    unsigned int sd_int_stat_reg;
    int ret_err;

    //mmcinfo("mmccr_TriggerCmd(0x%02x)\n", xferCmdCode);
    cr_writel( cr_readl(CR_INT_MASK) |
               (RTKCR_GET_PIN_OPTION |RTKCR_WRITE_OPTION),
               CR_INT_MASK);

    cr_writel( RTKCR_INT_CLEAR_ALL, CR_INT_STATUS );
    cr_writel( xferCmdCode|START_EN, SD_TRANSFER );

    udelay(50);

    ret_err = -19; // TIMEOUT ( defined in include/mmc.h )
    loops = max_mdelay_cnt;
    while( loops )
    {
        sd_int_stat_reg = cr_readl(CR_INT_STATUS);
        if( sd_int_stat_reg & RTKCR_INT_DECODE_FINISH ) {
            cr_writel(RTKCR_INT_DECODE_FINISH,CR_INT_STATUS);
            sd_stat_reg     = cr_readl(SD_STAT);
            sd_transfer_reg = cr_readl(SD_TRANSFER);
            if((sd_transfer_reg & END_STATE) == 0){
                ret_err = -19;
            }
            else if( cr_int_status_reg & RTKCR_INT_DECODE_ERROR ||
                     sd_stat_reg & MASK_SD_STAT_ERR )
            {
                mmcinfo("sd_stat(40h)   =0x%02x(error bit[7:5])\n", sd_stat_reg);
                mmcinfo("int_status(48h)=0x%02x(decode error[bit2])\n", cr_int_status_reg);
                ret_err = -18;
            }else{
                ret_err = 0;
            }
            break;
        }
        udelay(1000);
        loops--;
    }

    if( ret_err < 0 && !rtkmmc_off_error_msg_in_init_flow ) {
        UPRINTF("sd_xfer(08h)=0x%02x; loops=%d/%d\n", sd_transfer_reg, loops, max_mdelay_cnt);
        UPRINTF("    : ret_err=%d, sd_stat_reg(00h)=0x%02x, cr_int_status_reg(48h)=0x%02x\n", ret_err, sd_stat_reg, cr_int_status_reg);
        UPRINTF("    : SD_TRANSFER(08h)=0x%02x\n", cr_readl(SD_TRANSFER));
        UPRINTF("    : SD_CONFIGURE2(0Ch)=0x%02x\n", cr_readl(SD_CONFIGURE2));
        UPRINTF("    : SD_BYTE_CNT(28h-24h)=0x%02x%02x\n", cr_readl(SD_BYTE_CNT_H), cr_readl(SD_BYTE_CNT_L));
        UPRINTF("    : SD_BLOCK_CNT(30h-2Ch)=0x%02x%02x\n", cr_readl(SD_BLOCK_CNT_H), cr_readl(SD_BLOCK_CNT_L));
        UPRINTF("    : CP_CTRL(84h)=0x%02x\n", cr_readl(CP_CTRL));
    }

    if(ret_err)
        mmccr_reset_cr_state(1);

    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
void mmccr_set_div( unsigned int set_div, unsigned int show_msg )
{
    unsigned int tmp_div;
    //mmcinfo("mmccr_set_div; switch to 0x%08x\n", set_div);

    tmp_div = cr_readl(SD_CONFIGURE1);

    if((tmp_div & MASK_CLOCK_DIV) == set_div){
        //mmcinfo("%s: skip!!!\n",__func__);
        return;
    }else{
        tmp_div &= ~MASK_CLOCK_DIV;
        //show_msg = 1;
    }

    cr_writel(tmp_div|set_div,SD_CONFIGURE1);

    if( show_msg )
        mmcinfo("%s: 0x%08x=0x%08x\n",
                __func__,SD_CONFIGURE1,cr_readl(SD_CONFIGURE1));
}

/*******************************************************
 *
 *******************************************************/
void mmccr_set_bits_width( unsigned int set_bit )
{
    unsigned int tmp_bits;
    //mmcinfo("mmccr_set_bits_width; switch to 0x%08x\n",set_bit);

    tmp_bits = cr_readl(SD_CONFIGURE1);
    if((tmp_bits & MASK_BUS_WIDTH) == set_bit){
        //mmcinfo("%s: skip!!!\n",__func__);
        return;
    }else{
        tmp_bits &= ~MASK_BUS_WIDTH;
    }

    cr_writel(tmp_bits|set_bit,SD_CONFIGURE1);
    //mmcinfo("%s: 0x%08x=0x%08x\n",
    //        __func__,SD_CONFIGURE1, cr_readl(SD_CONFIGURE1));
}

/*******************************************************
 *
 *******************************************************/
#ifndef FPGA_SIRIUS_TEST
void mmccr_set_speed( unsigned int para )
{
    unsigned int tmp_para;
    tmp_para = cr_readl(SD_CONFIGURE1)& ~SPEED_MOD_HIGH;
    cr_writel(tmp_para|para,SD_CONFIGURE1);
}
#endif

/*******************************************************
 *
 *******************************************************/
static const char *const clk_tlb[7] = {
    "50MHz",
    "33MHz",
    "25MHz",
    "20MHz",
    "16MHz",
    "12MHz",
    "10MHz"
};

void mmccr_set_clk( unsigned int mmc_clk, unsigned int show_msg )
{
#ifndef FPGA_SIRIUS_TEST
    unsigned int tmp_clk;

    tmp_clk = cr_readl(SYS_CLKSEL);

    if((tmp_clk & EMMC_CLKSEL_MASK ) == mmc_clk)
        return;

    printf("emmc: clock switch to %s,", clk_tlb[mmc_clk>>EMMC_CLKSHT_BIT]);

    tmp_clk &= ~EMMC_CLKSEL_MASK;
    cr_writel(tmp_clk|mmc_clk|EMMC_DIV_EN, SYS_CLKSEL);

    if( CLOCK_SPEED_GAP > mmc_clk ){
        printf("(high)\n");
        mmccr_set_speed(SPEED_MOD_HIGH);
    }else{
        printf("(normal)\n");
        mmccr_set_speed(SPEED_MOD_NORM);
    }

    if( show_msg ) {
        mmcinfo("%s: 0x%08x=0x%08x\n",
                __func__,SYS_CLKSEL,cr_readl(SYS_CLKSEL));
    }
#endif
}

/*******************************************************
 *
 *******************************************************/
void mmccr_reset_cr_state( unsigned char save_en )
{
    volatile unsigned int tmp;
    volatile unsigned int org_config1;
    volatile unsigned int org_config2;
    volatile unsigned int org_config3;

#ifndef FPGA_SIRIUS_TEST
    //volatile unsigned int org_clksel;
#endif

    if(save_en){
        // save current configuration
        org_config1 = cr_readl(SD_CONFIGURE1);
        org_config2 = cr_readl(SD_CONFIGURE2);
        org_config3 = cr_readl(SD_CONFIGURE3);
        //mmcinfo("0xb8010804=0x%08x\n", org_config1);
    }

#ifndef FPGA_SIRIUS_TEST
    //org_clksel = cr_readl(SYS_CLKSEL);
    //mmcinfo("0xb8000204=0x%08x\n", org_clksel);

    /* reset mmc ip */
    //UPRINTF("emmc:clear 0x%08x[23]\n", CR_IP_CLKEN_REG);
    tmp = cr_readl( CR_IP_CLKEN_REG );
    tmp &= ~(1UL<<CR_IP_CLKEN_REG_BIT);
    cr_writel( tmp, CR_IP_CLKEN_REG );

    //UPRINTF("emmc:clear 0x%08x[23]\n", CR_IP_RESET_REG);
    tmp = cr_readl( CR_IP_RESET_REG );
    tmp &= ~(1UL<<CR_IP_RESET_REG_BIT);
    cr_writel( tmp, CR_IP_RESET_REG );

    //UPRINTF("emmc:set 0x%08x[23]\n", CR_IP_RESET_REG);
    tmp = cr_readl( CR_IP_RESET_REG );
    tmp |= (1UL<<CR_IP_RESET_REG_BIT);
    cr_writel( tmp, CR_IP_RESET_REG );

    //UPRINTF("emmc:set 0x%08x[23]\n", CR_IP_CLKEN_REG);
    tmp = cr_readl( CR_IP_CLKEN_REG );
    tmp |= (1UL<<CR_IP_CLKEN_REG_BIT);
    cr_writel( tmp, CR_IP_CLKEN_REG );

    // disable & clear interrupt pending bit
    cr_writel(0x00, CR_INT_MASK);
    cr_writel( RTKCR_INT_CLEAR_ALL, CR_INT_STATUS);

    //mmcinfo("0xb8000204=0x%08x\n", cr_readl(SYS_CLKSEL));
    //mmcinfo("0xb8010804=0x%08x\n", cr_readl(SD_CONFIGURE1));

    /* reset mmc control is not infelect system clock . */
    //cr_writel( org_clksel, SYS_CLKSEL);
#endif

    if(save_en){
        cr_writel( org_config1, SD_CONFIGURE1);
        cr_writel( org_config2, SD_CONFIGURE2);
        cr_writel( org_config3, SD_CONFIGURE3);
    }

    //mmcinfo("0xb8000204=0x%08x\n", cr_readl(SYS_CLKSEL));
    //mmcinfo("0xb8010804=0x%08x\n", cr_readl(SD_CONFIGURE1));
}

/*******************************************************
 *
 *******************************************************/
void mmccr_read_rsp( unsigned int * rsp, int reg_count )
{
    //mmcinfo("*rsp=0x%p; reg_count=%u\n",rsp,reg_count);

    if ( reg_count == 6 ){
        rsp[0] = cr_readl(CR_CARD_RESP6_1) << 24 |
                 cr_readl(CR_CARD_RESP6_2) << 16 |
                 cr_readl(CR_CARD_RESP6_3) << 8 |
                 cr_readl(CR_CARD_RESP6_4);

        //mmcinfo("rsp[0]=0x%x\n",rsp[0]);
//      mmcinfo("48-bit rsp data(hex) = [%02X] [%02X %02X %02X %02X] [crc]\n",
//              cr_readl(CR_CARD_RESP6_0),
//              cr_readl(CR_CARD_RESP6_1),
//              cr_readl(CR_CARD_RESP6_2),
//              cr_readl(CR_CARD_RESP6_3),
//              cr_readl(CR_CARD_RESP6_4) );
    }
    else if( reg_count == 17 ){
        rsp[0] = cr_readl(EXT_RSP_0) << 24 |
                 cr_readl(EXT_RSP_1) << 16 |
                 cr_readl(EXT_RSP_2) << 8 |
                 cr_readl(EXT_RSP_3);

        rsp[1] = cr_readl(EXT_RSP_4) << 24 |
                 cr_readl(EXT_RSP_5) << 16 |
                 cr_readl(EXT_RSP_6) << 8 |
                 cr_readl(EXT_RSP_7);

        rsp[2] = cr_readl(EXT_RSP_8) << 24 |
                 cr_readl(EXT_RSP_9) << 16 |
                 cr_readl(EXT_RSP_10) << 8 |
                 cr_readl(EXT_RSP_11);

        rsp[3] = cr_readl(EXT_RSP_12) << 24 |
                 cr_readl(EXT_RSP_13) << 16 |
                 cr_readl(EXT_RSP_14) << 8 |
                 0xff;
        //128-bit rsp data
        //mmcinfo("rsp[0]=0x%x\n",rsp[0]);
        //mmcinfo("rsp[1]=0x%x\n",rsp[1]);
        //mmcinfo("rsp[2]=0x%x\n",rsp[2]);
        //mmcinfo("rsp[3]=0x%x\n",rsp[3]);
    }
}

/*******************************************************
 *
 *******************************************************/
int mmc_state_is_transfer_and_ready( e_device_type * card )
{

    unsigned int rsp_buffer[4];
    unsigned int  curr_state;
    int ret_err = 0;
    unsigned int retry_cnt;

    //mmcinfo("mmc_state_is_transfer_and_ready()\n");

    retry_cnt = 0;
    while( retry_cnt++ < 3 ) {
        ret_err = mmccr_SendCmd(MMC_SEND_STATUS, card->rca, SD_R1|CRC16_CAL_DIS, rsp_buffer);
        if( !ret_err ) {
            if( retry_cnt == 3 ) {
                curr_state = R1_CURRENT_STATE(rsp_buffer[0]);
                if( curr_state == STATE_TRAN /*4*/ ) {
                    if(rsp_buffer[0] & R1_READY_FOR_DATA){
                        return 1;
                    }
                }
                else {
                    return 0;
                }
            }
        }
        else {
            return -1;
        }
    }
    return -1;
}

/*******************************************************
 *
 *******************************************************/
unsigned int mmc_get_rsp_len( unsigned char rsp_para )
{
    //mmcinfo("mmc_get_rsp_len\n");

    switch (rsp_para & 0x3) {
        case 0:
            return 0; // hw bug ??
        case 1:
            return 6;
        case 2:
            return 17;
        default:
            return 0;
    }
}

/*******************************************************
 *
 *******************************************************/
unsigned int mmc_get_rsp_type( struct rtk_mmc_command * cmd )
{
    unsigned int rsp_type = 0;

    //mmcinfo("get_rsp_type\n");

    /* the marked case are used. */
    switch( cmd->opcode )
    {
        case 3:
        case 7:
        case 13:
        case 16:
        case 23:
        case 35:
        case 36:
        case 55:
            rsp_type |= CRC16_CAL_DIS;
        case 8:
        case 11:
        case 14:
        case 19:
        case 17:
        case 18:
        case 20:
        case 24:
        case 25:
        case 26:
        case 27:
        case 30:
        case 42:
        case 56:
            rsp_type |= SD_R1;
            break;
        case 6:
        case 12:
        case 28:
        case 29:
        case 38:
            rsp_type = SD_R1b|CRC16_CAL_DIS;
            break;
        case 2:
        case 9:
        case 10:
            rsp_type = SD_R2;
            break;
        case 1:
            rsp_type = SD_R3;
            break;
        default:
            rsp_type = SD_R0;
            break;
    }
    return rsp_type;
}

/*******************************************************
 *
 *******************************************************/
int mmccr_SendCmd( unsigned int cmd_idx,
                   unsigned int cmd_arg,
                   unsigned int rsp_para,
                   unsigned int * rsp_buffer )
{
    unsigned int rsp_len;
    int ret_err;

    mmcinfo_cmd("Cmd=0x%02x, Argu=0x%08x\n", cmd_idx, cmd_arg);

    rsp_len = mmc_get_rsp_len(rsp_para);

    if( rtkmmc_debug_msg ) {
        mmcinfo("%s(%u) cmd_idx(10h)=%u arg(14h-20h)=0x%08x rsp_para(0Ch)=0x%02x\n",
                __func__,__LINE__,
                cmd_idx, cmd_arg, rsp_para);
    }

    //if( cmd_idx == MMC_CMD_READ_SINGLE_BLOCK ||
    //  cmd_idx == MMC_CMD_READ_MULTIPLE_BLOCK ||
    //  cmd_idx == MMC_CMD_WRITE_SINGLE_BLOCK ||
    //  cmd_idx == MMC_CMD_WRITE_MULTIPLE_BLOCK )
    //{
    //  mmcinfo("cmd_idx(10h)=%u arg(14h-20h)=0x%08x rsp_para(0Ch)=0x%02x\n", cmd_idx, cmd_arg, rsp_para);
    //}

    cr_writel(0x40|cmd_idx, SD_CMD0);
    cr_writel(cmd_arg>>24,  SD_CMD1);
    cr_writel(cmd_arg>>16,  SD_CMD2);
    cr_writel(cmd_arg>>8,   SD_CMD3);
    cr_writel(cmd_arg,      SD_CMD4);
    cr_writel(rsp_para,     SD_CONFIGURE2);

    ret_err = mmccr_TriggerXferCmd( SD_SENDCMDGETRSP, ( rsp_para & WAIT_BUSY_EN ? 1000 : 500 ) );

    if( !ret_err ){
        mmccr_read_rsp(rsp_buffer, rsp_len);
    }

    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int mmc_send_stop( e_device_type * card )
{
    unsigned int rsp_buffer[4];

    //mmcinfo("mmc_send_stop\n");

    return mmccr_SendCmd(MMC_STOP_TRANSMISSION, card->rca, SD_R1|CRC16_CAL_DIS, rsp_buffer);
}

/*******************************************************
 *
 *******************************************************/
int mmccr_Stream_Cmd( unsigned int xferCmdCode, struct rtk_cmd_info * cmd_info )
{
    unsigned int cmd_idx      = cmd_info->cmd->opcode;
    unsigned int cmd_arg      = cmd_info->cmd->arg;
    unsigned int * rsp        = cmd_info->cmd->resp;
    unsigned int rsp_para     = cmd_info->rsp_para;
    int rsp_len               = cmd_info->rsp_len;
    unsigned int byte_count = cmd_info->byte_count;
    unsigned int block_count  = cmd_info->block_count;
    unsigned int phy_buf_addr = (unsigned int) cmd_info->data_buffer;
    unsigned int timeout;
    int ret_err;

    //mmcinfo("mmccr_Stream_Cmd(XferCmdCode(08h)=0x%02x)\n",xferCmdCode);
    //mmcinfo("cmd_info->xfer_flag=0x%02x\n",cmd_info->xfer_flag);

    /* clear data at sram and trun-off boot mode */
    cr_writel(cr_readl(CP_CTRL) & ~BOOT_FROM_CR,  CP_CTRL);

    if( RTK_MMC_DATA_DIR(cmd_info) & RTK_MMC_DATA_SRAM ) {
        if( block_count != 1 ) {
            mmcinfo("SRAM mode support single sector only\n");
            return -1;
        }
        mmcinfo("SRAM mode on\n");
        cr_writel(cr_readl(CP_CTRL)|BOOT_FROM_CR, CP_CTRL);
    }

    if( RTK_MMC_DATA_DIR(cmd_info) & RTK_MMC_DATA_WRITE){
        cr_writel( phy_buf_addr, CR_DMA_OUT_ADDR);
    }
    else{
        cr_writel( phy_buf_addr, CR_DMA_IN_ADDR);
    }

    if( rtkmmc_debug_msg ) {
        mmcinfo("%s(%u) cmd_idx(10h)=%u arg(14h-20h)=0x%08x rsp_para(0Ch)=0x%02x\n"
                "     byte_count=0x%04x; block_count=0x%04x; phy addr=0x%08x\n",
                __func__,__LINE__,
                cmd_idx, cmd_arg, rsp_para, byte_count, block_count, phy_buf_addr);

        switch( xferCmdCode ) {
            case SD_AUTOREAD1:      UPRINTF("     XferCmdCode(08h)=0x%02x, SD_AUTOREAD1\n", xferCmdCode);   break;
            case SD_AUTOWRITE1:     UPRINTF("     XferCmdCode(08h)=0x%02x, SD_AUTOWRITE1\n", xferCmdCode);  break;
            case SD_AUTOREAD2:      UPRINTF("     XferCmdCode(08h)=0x%02x, SD_AUTOREAD2\n", xferCmdCode);   break;
            case SD_AUTOWRITE2:     UPRINTF("     XferCmdCode(08h)=0x%02x, SD_AUTOWRITE2\n", xferCmdCode);  break;
            case SD_NORMALREAD:     UPRINTF("     XferCmdCode(08h)=0x%02x, SD_NORMALREAD\n", xferCmdCode);  break;
            case SD_NORMALWRITE:    UPRINTF("     XferCmdCode(08h)=0x%02x, SD_NORMALWRITE\n", xferCmdCode); break;
            default:                UPRINTF("     XferCmdCode(08h)=0x%02x, unknown\n", xferCmdCode);
        }
    }

    cr_writel(0x40| cmd_idx,  SD_CMD0);           //0x10
    cr_writel(cmd_arg>>24,    SD_CMD1);           //0x14
    cr_writel(cmd_arg>>16,    SD_CMD2);           //0x18
    cr_writel(cmd_arg>>8,     SD_CMD3);           //0x1C
    cr_writel(cmd_arg,        SD_CMD4);           //0x20
    cr_writel(rsp_para,       SD_CONFIGURE2);     //0x0C
    cr_writel(byte_count,     SD_BYTE_CNT_L);     //0x24
    cr_writel(byte_count>>8,  SD_BYTE_CNT_H);     //0x28
    cr_writel(block_count,    SD_BLOCK_CNT_L);    //0x2C
    cr_writel(block_count>>8, SD_BLOCK_CNT_H);    //0x30

    if( block_count <= 3000 ) {
        timeout = 3000;
    }
    else {
        timeout = block_count;
    }

    ret_err = mmccr_TriggerXferCmd( xferCmdCode, timeout/*3000*/ );

    if( !ret_err ){
        mmccr_read_rsp(rsp, rsp_len);
        if( rsp[0] == 0xFFFFFFFF ) {
            mmcinfo("RSP data fmt error\n");
            ret_err = -1;
        }

        if( !ret_err ) {
            if( RTK_MMC_DATA_DIR(cmd_info) ==  RTK_MMC_SRAM_READ ) {
                unsigned int i;
                unsigned int * sram_buf = (unsigned int *) phy_buf_addr;
                unsigned int fifo_tmp;
                if(sram_buf){
                    mmcinfo("Read data from SRAM FIFO\n");
                    for( i=0; i<128; i++ ){
                        fifo_tmp = cr_readl(CR_SRAM_BASE);
                        sram_buf[i]= fifo_tmp;
                    }
                }
                udelay(1000);
            }
        }
    }

//err_out:
    if( ret_err ){
        mmcinfo("ret_err=%d\n", ret_err);
    }
    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int mmccr_Stream( unsigned int address,
                  unsigned int blk_cnt,
                  unsigned int xfer_flag,
                  unsigned int * data_buffer )
{
    struct rtk_cmd_info cmd_info;
    struct rtk_mmc_command  cmd;
    unsigned int xferCmdCode;
    unsigned int cmd_retry_cnt;
    unsigned int counter;
    int rw_cmd_err;
    int card_state;
    int err = -1;
    int send_stop_cmd = 0;
    unsigned int rsp_type;

    cmd_retry_cnt = 5;

    do {
        //mmcinfo("mmccr_Stream(%d)\n", cmd_retry_cnt);
        //mmcinfo("address=0x%08x; blk_cnt=0x%04x; xfer_flag=0x%02x; data_buffer=0x%p\n", address, blk_cnt, xfer_flag, data_buffer);

        cmd_info.cmd = &cmd;
        cmd.arg      = address;

        if( xfer_flag & RTK_MMC_DATA_WRITE ){
            xferCmdCode = SD_AUTOWRITE2; // cmd + data
            cmd.opcode = 24;
        }else{
            xferCmdCode = SD_AUTOREAD2; // cmd + data
            cmd.opcode = 17;
        }

        /* multi sector accress opcode */
        if( blk_cnt > 1 ){
            send_stop_cmd = 1;
            cmd.opcode++; // 25 or 18 ( multi_block_xxxx )
        }

        rsp_type = mmc_get_rsp_type(&cmd);

        cmd_info.rsp_para    = rsp_type;
        cmd_info.rsp_len     = mmc_get_rsp_len(rsp_type);
        cmd_info.byte_count  = 0x200;
        cmd_info.block_count = blk_cnt;
        cmd_info.data_buffer = (unsigned char *)data_buffer;
        cmd_info.xfer_flag   = xfer_flag;

        rw_cmd_err = err = mmccr_Stream_Cmd( xferCmdCode, &cmd_info );

        if( err ){
            mmcinfo("mmccr_Stream done but err=%d\n", err);

            if( send_stop_cmd ) {
                send_stop_cmd = 0;
                err = mmc_send_stop(&emmc_card);
                if( err < 0 ) {
                    err = -1;
                    mmcinfo("send stop cmd fail\n");
                }
            }
        }

        if( send_stop_cmd ) {
            send_stop_cmd = 0;
            err = mmc_send_stop(&emmc_card);
            if( err < 0 ) {
                mmcinfo("send stop cmd fail\n");
            }
        }

        counter = 1500; // time out 1500 ms
        while( counter-- ) {
            err = -1;
            card_state = mmc_state_is_transfer_and_ready(&emmc_card);
            if( card_state < 0 ) {
                err = -1;
                mmcinfo("get card status fail\n");
                break;
            }
            if( card_state == 0 /* suppose card in DATA,RCV or PRG state */ && send_stop_cmd ) {
                // send stop command
                send_stop_cmd = 0;
                err = mmc_send_stop(&emmc_card);
                if( err < 0 ) {
                    err = -1;
                    mmcinfo("send stop cmd fail\n");
                    break;
                }
            }
            if( card_state == 1 ) {
                err = 0;
                break;
            }
            udelay(1000);
        }

        if( !err && !rw_cmd_err ) {
            break;
        }
    }
    while(cmd_retry_cnt--);

    return rw_cmd_err;
}

/*******************************************************
 *
 *******************************************************/
#if 0
int mmccr_Stream_SRAM_DummyRead( unsigned int address /* 0 */,
                  unsigned int blk_cnt/* 1 */,
                  unsigned int xfer_flag/* RTK_MMC_SRAM_READ */,
                  void * data_buffer )
{
    struct rtk_cmd_info cmd_info;
    struct rtk_mmc_command  cmd;
    unsigned int xferCmdCode;

    //UPRINTF("mmccr_Stream_SRAM_DummyRead\n");

    do {
        xferCmdCode = SD_AUTOREAD3;

        cmd_info.cmd = &cmd;
        cmd.opcode   = MMC_GO_IDLE_STATE; // we don't care in this case
        cmd.arg      = 0; // we don't care in this case

        cmd_info.rsp_para    = SD_R0; // we don't care in this case
        cmd_info.rsp_len     = 0; // we don't care in this case
        cmd_info.byte_count  = 0x200;
        cmd_info.block_count = blk_cnt;
        cmd_info.data_buffer = data_buffer;
        cmd_info.xfer_flag   = xfer_flag; // we don't care in this case ( force to read date to SRAM )

        cr_writel(cr_readl(CP_CTRL)|BOOT_FROM_CR, CP_CTRL);

        cr_writel( (unsigned int)cmd_info.data_buffer,    CR_DMA_IN_ADDR);
        cr_writel( cmd_info.byte_count,     SD_BYTE_CNT_L);     //0x24
        cr_writel( cmd_info.byte_count>>8,  SD_BYTE_CNT_H);     //0x28
        cr_writel( cmd_info.block_count,    SD_BLOCK_CNT_L);    //0x2C
        cr_writel( cmd_info.block_count>>8, SD_BLOCK_CNT_H);    //0x30

        cr_writel(cr_readl(CP_CTRL) & ~BOOT_FROM_CR,  CP_CTRL);

        mmccr_TriggerXferCmd( xferCmdCode, 1 );

    }
    while( 0 );

    return 0;
}
#endif

int mmccr_toggle_clk_us(unsigned int clk_us)
{
    cr_writel(cr_readl(SD_CONFIGURE3)|CLK_TOGGLE_EN,SD_CONFIGURE3);
    udelay(clk_us);
    cr_writel(cr_readl(SD_CONFIGURE3)&~CLK_TOGGLE_EN,SD_CONFIGURE3);
}

/*******************************************************
 *
 *******************************************************/
int mmccr_Stream_Only( unsigned int address,
                  unsigned int blk_cnt,
                  unsigned int xfer_flag,
                  unsigned int * data_buffer )
{
    struct rtk_cmd_info cmd_info;
    struct rtk_mmc_command  cmd;
    unsigned int xferCmdCode;
    unsigned int phy_buf_addr = (unsigned int) data_buffer;
    unsigned int timeout;
    int ret_err = -1;

    //UPRINTF("mmccr_Stream_Only(%d, %d, 0x%08x, 0x%08x\n", address, blk_cnt, xfer_flag, phy_buf_addr);

    do {
        cmd_info.cmd = &cmd;
        cmd.opcode   = MMC_GO_IDLE_STATE; // we don't care in this case
        cmd.arg      = 0; // we don't care in this case
        cmd_info.rsp_para    = SD_R0; // we don't care in this case
        cmd_info.rsp_len     = 0; // we don't care in this case
        cmd_info.byte_count  = 0x200;
        cmd_info.block_count = blk_cnt;
        cmd_info.data_buffer = (unsigned char *)phy_buf_addr;
        cmd_info.xfer_flag   = xfer_flag; // we don't care in this case ( force to read date to SRAM )

        if( xfer_flag & RTK_MMC_DATA_WRITE){
            cr_writel( phy_buf_addr, CR_DMA_OUT_ADDR);
            xferCmdCode = SD_AUTOWRITE3;
        }else{
            cr_writel( phy_buf_addr, CR_DMA_IN_ADDR);
            xferCmdCode = SD_AUTOREAD3;
        }

        cr_writel( cmd_info.byte_count,    SD_BYTE_CNT_L);     //0x24
        cr_writel( cmd_info.byte_count>>8, SD_BYTE_CNT_H);     //0x28
        cr_writel( cmd_info.block_count,   SD_BLOCK_CNT_L);    //0x2C
        cr_writel( cmd_info.block_count>>8,SD_BLOCK_CNT_H);    //0x30

        if( cmd_info.block_count <= 3000 ) {
            timeout = 3000;
        }
        else {
            timeout = cmd_info.block_count;
        }

        cr_writel(cr_readl(CP_CTRL) & ~BOOT_FROM_CR,  CP_CTRL);

        ret_err = mmccr_TriggerXferCmd( xferCmdCode, timeout/*3000*/ );
    }
    while( 0 );

    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int mmc_show_cid( e_device_type *card )
{
    int i;
    unsigned int sn;
    unsigned char cid[16];
    for( i = 0; i < 4; i++ ) {
        cid[(i<<2)]   = ( card->raw_cid[i]>>24 ) & 0xFF;
        cid[(i<<2)+1] = ( card->raw_cid[i]>>16 ) & 0xFF;
        cid[(i<<2)+2] = ( card->raw_cid[i]>>8  ) & 0xFF;
        cid[(i<<2)+3] = ( card->raw_cid[i]     ) & 0xFF;
    }
#ifdef EMMC_SHOW_CID
    UPRINTF("emmc:CID");
    for( i = 0; i < 16; i++ ) {
        UPRINTF(" %02x", cid[i]);
    }
    UPRINTF("\n");
#endif
    mmcinfo("CID    0x%02x\n", cid[0]);
    switch( (cid[1] & 0x3) ) {
        case 0:
            mmcinfo("CBX    Card\n");       break;
        case 1:
            mmcinfo("CBX    BGA\n");        break;
        case 2:
            mmcinfo("CBX    POP\n");        break;
        case 3:
            mmcinfo("CBX    Unknown\n");    break;
    }
    mmcinfo("OID    0x%02x\n", cid[2]);
    mmcinfo("PNM    %c%c%c%c%c%c\n", cid[3], cid[4], cid[5], cid[6], cid[7], cid[8]);
    mmcinfo("PRV    %d.%d\n", (cid[9]>>4)&0xf, cid[9]&0xf);
    sn = cid[13];
    sn = (sn<<8) | cid[12];
    sn = (sn<<8) | cid[11];
    sn = (sn<<8) | cid[10];
    mmcinfo("PSN    %u(0x%08x)\n", sn, sn);
    if( cid[9] ) {
        mmcinfo("MDT    %02d/%d)", (cid[9]>>4)&0xf, (cid[14]&0xf)+1997);
    }
    else {
        mmcinfo("MDT    --/----\n");
    }

    return 0;
}

/*******************************************************
 *
 *******************************************************/
int mmc_decode_csd( e_device_type * card )
{
    struct rtk_mmc_csd * csd = &card->csd;
    unsigned int e, m;
    unsigned int * resp = card->raw_csd;
    int err = 0;

    mmcinfo("mmc_decode_csd\n");

  /*
     * We only understand CSD structure v1.1 and v1.2.
     * v1.2 has extra information in bits 15, 11 and 10.
     * We also support eMMC v4.4 & v4.41.
     */
    csd->csd_ver2 = 0xff;
    csd->csd_ver = UNSTUFF_BITS(resp, 126, 2);

    // 0, CSD Ver. 1.0
    // 1, CSD Ver. 1.1
    // 2, CSD Ver. 1.2, define in spec. 4.1-4.3
    // 3, CSD Ver define in EXT_CSD[194]
    //    EXT_CSD[194] 0, CSD Ver. 1.0
    //                 1, CSD Ver. 1.1
    //                 2, CSD Ver. 1.2, define in spec. 4.1-4.51
    //                 others, RSV

    csd->mmca_vsn       = UNSTUFF_BITS(resp, 122, 4);
    m = UNSTUFF_BITS(resp, 115, 4);
    e = UNSTUFF_BITS(resp, 112, 3);
    csd->tacc_ns        = (tacc_exp[e] * tacc_mant[m] + 9) / 10;
    csd->tacc_clks      = UNSTUFF_BITS(resp, 104, 8) * 100;

    m = UNSTUFF_BITS(resp, 99, 4);
    e = UNSTUFF_BITS(resp, 96, 3);
    csd->max_dtr        = tran_exp[e] * tran_mant[m];
    csd->cmdclass       = UNSTUFF_BITS(resp, 84, 12);

    m = UNSTUFF_BITS(resp, 62, 12);
    e = UNSTUFF_BITS(resp, 47, 3);
    csd->capacity       = (1 + m) << (e + 2);
    csd->read_blkbits   = UNSTUFF_BITS(resp, 80, 4);
    csd->read_partial   = UNSTUFF_BITS(resp, 79, 1);
    csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
    csd->read_misalign  = UNSTUFF_BITS(resp, 77, 1);
    csd->r2w_factor     = UNSTUFF_BITS(resp, 26, 3);
    csd->write_blkbits  = UNSTUFF_BITS(resp, 22, 4);
    csd->write_partial  = UNSTUFF_BITS(resp, 21, 1);

    mmcinfo("C_SIZE      :%u\n",m);
    mmcinfo("C_SIZE_MULT :%u\n",e);
    mmcinfo("Block Num   :%u\n",csd->capacity);
    mmcinfo("Block Len   :%u\n" ,1<<csd->read_blkbits);
    mmcinfo("Total Bytes :%u\n",csd->capacity*(1<<csd->read_blkbits));
//err_out:
    return err;
}

/*******************************************************
 *
 *******************************************************/
int mmc_decode_cid( e_device_type * card )
{
    unsigned int * resp = card->raw_cid;

    mmcinfo("mmc_decode_cid\n");
    /*
     * The selection of the format here is based upon published
     * specs from sandisk and from what people have reported.
     */
    switch (card->csd.mmca_vsn) {
    case 0: /* MMC v1.0 - v1.2 */
    case 1: /* MMC v1.4 */
        card->cid.manfid        = UNSTUFF_BITS(resp, 104, 24);
        card->cid.prod_name[0]  = UNSTUFF_BITS(resp, 96, 8);
        card->cid.prod_name[1]  = UNSTUFF_BITS(resp, 88, 8);
        card->cid.prod_name[2]  = UNSTUFF_BITS(resp, 80, 8);
        card->cid.prod_name[3]  = UNSTUFF_BITS(resp, 72, 8);
        card->cid.prod_name[4]  = UNSTUFF_BITS(resp, 64, 8);
        card->cid.prod_name[5]  = UNSTUFF_BITS(resp, 56, 8);
        card->cid.prod_name[6]  = UNSTUFF_BITS(resp, 48, 8);
        card->cid.hwrev         = UNSTUFF_BITS(resp, 44, 4);
        card->cid.fwrev         = UNSTUFF_BITS(resp, 40, 4);
        card->cid.serial        = UNSTUFF_BITS(resp, 16, 24);
        card->cid.month         = UNSTUFF_BITS(resp, 12, 4);
        card->cid.year          = UNSTUFF_BITS(resp, 8,  4) + 1997;
        break;

    case 2: /* MMC v2.0 - v2.2 */
    case 3: /* MMC v3.1 - v3.3 */
    case 4: /* MMC v4 */
        card->cid.manfid        = UNSTUFF_BITS(resp, 120, 8);
        card->cid.oemid         = UNSTUFF_BITS(resp, 104, 16);
        card->cid.prod_name[0]  = UNSTUFF_BITS(resp, 96, 8);
        card->cid.prod_name[1]  = UNSTUFF_BITS(resp, 88, 8);
        card->cid.prod_name[2]  = UNSTUFF_BITS(resp, 80, 8);
        card->cid.prod_name[3]  = UNSTUFF_BITS(resp, 72, 8);
        card->cid.prod_name[4]  = UNSTUFF_BITS(resp, 64, 8);
        card->cid.prod_name[5]  = UNSTUFF_BITS(resp, 56, 8);
        card->cid.serial        = UNSTUFF_BITS(resp, 16, 32);
        card->cid.month         = UNSTUFF_BITS(resp, 12, 4);
        card->cid.year          = UNSTUFF_BITS(resp, 8, 4) + 1997;
        break;

    default:
        mmcinfo("card has unknown MMCA version %d\n",
                card->csd.mmca_vsn);
        return -1;
    }

    return 0;
}

/*******************************************************
 *
 *******************************************************/
int mmc_show_csd( e_device_type * card )
{
#ifdef EMMC_SHOW_CSD
    int i;
    unsigned char csd[16];
    for( i = 0; i < 4; i++ ) {
        csd[(i<<2)]   = ( card->raw_csd[i]>>24 ) & 0xFF;
        csd[(i<<2)+1] = ( card->raw_csd[i]>>16 ) & 0xFF;
        csd[(i<<2)+2] = ( card->raw_csd[i]>>8  ) & 0xFF;
        csd[(i<<2)+3] = ( card->raw_csd[i]     ) & 0xFF;
    }
    UPRINTF("emmc:CSD(hex)");
    for( i = 0; i < 16; i++ ) {
        UPRINTF(" %02x", csd[i]);
    }
    UPRINTF("\n");
#endif
    mmc_decode_csd(card);

    return 0;
}

/*******************************************************
 *
 *******************************************************/
int mmc_show_ext_csd( e_device_type * card, unsigned char * pext_csd )
{
    unsigned int sec_cnt;
    unsigned int boot_size_mult;
#ifdef EMMC_SHOW_EXTCSD
    int i,j,k;
    UPRINTF("emmc:EXT CSD\n");
    k = 0;
    for( i = 0; i < 32; i++ ) {
        UPRINTF("    : %03d - ", i<<4);
        for( j = 0; j < 16; j++ ) {
            UPRINTF(" %02x", pext_csd[k++]);
        }
        UPRINTF("\n");
    }
    UPRINTF("    :k=%d\n",k);
#endif
    boot_size_mult = pext_csd[226];
    UPRINTF("emmc:BOOT PART %u Kbytes(0x%02x)\n", (boot_size_mult<<7), boot_size_mult);
    sec_cnt = pext_csd[215];
    sec_cnt = (sec_cnt<<8) | pext_csd[214];
    sec_cnt = (sec_cnt<<8) | pext_csd[213];
    sec_cnt = (sec_cnt<<8) | pext_csd[212];
    UPRINTF("emmc:SEC_COUNT %u(0x%08x)\n", sec_cnt, sec_cnt);

    return 0;
}

/*******************************************************
 *
 *******************************************************/
int mmc_read_ext_csd( e_device_type * card )
{
    struct rtk_cmd_info cmd_info;
    struct rtk_mmc_command  cmd;
    unsigned int xferCmdCode;
    unsigned int rsp_type;
    int ret_err;

    mmcinfo("mmc_read_ext_csd\n");

    cmd_info.cmd= &cmd;
    cmd.arg     = 0;
    cmd.opcode = MMC_SEND_EXT_CSD;

    rsp_type = mmc_get_rsp_type(&cmd);

    mmcinfo("ext_csd ptr 0x%p\n",ext_csd);

    cmd_info.rsp_para    = rsp_type;
    cmd_info.rsp_len     = mmc_get_rsp_len(rsp_type);
    cmd_info.byte_count  = 0x200;
    cmd_info.block_count = 1;
    cmd_info.data_buffer = ext_csd;
    cmd_info.xfer_flag   = RTK_MMC_SRAM_READ;
    xferCmdCode          = SD_NORMALREAD;

    ret_err = mmccr_Stream_Cmd( xferCmdCode, &cmd_info);

    if(ret_err){
        mmcinfo("unable to read EXT_CSD(ret_err=%d)", ret_err);
    }
    else{
        mmc_show_ext_csd(card, ext_csd);

        card->csd.csd_ver2 = ext_csd[EXT_CONT_CSD_VER];
        card->ext_csd.rev = ext_csd[EXT_CSD_REV];

        if (card->ext_csd.rev > 6) {
            mmcinfo("unrecognized EXT_CSD structure version %d, please update fw\n", card->ext_csd.rev);
        }

        if (card->ext_csd.rev >= 2) {
            //card->ext_csd.sectors = *((unsigned int *)(&ext_csd[EXT_CSD_SEC_CNT]));
            card->ext_csd.sectors =
                ext_csd[EXT_CSD_SEC_CNT + 0] << 0 |
                ext_csd[EXT_CSD_SEC_CNT + 1] << 8 |
                ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
                ext_csd[EXT_CSD_SEC_CNT + 3] << 24;

        }

        switch (ext_csd[EXT_CSD_CARD_TYPE] & (EXT_CSD_CARD_TYPE_26|EXT_CSD_CARD_TYPE_52)) {
            case EXT_CSD_CARD_TYPE_52 | EXT_CSD_CARD_TYPE_26:
                card->ext_csd.hs_max_dtr = 52000000;
                break;
            case EXT_CSD_CARD_TYPE_26:
                card->ext_csd.hs_max_dtr = 26000000;
                break;
            default:
                /* MMC v4 spec says this cannot happen */
                mmcinfo("card is mmc v4 but doesn't " "support any high-speed modes.\n");
        }

        if (card->ext_csd.rev >= 3) {
            unsigned int sa_shift = ext_csd[EXT_CSD_S_A_TIMEOUT];
            /* Sleep / awake timeout in 100ns units */
            if (sa_shift > 0 && sa_shift <= 0x17){
                card->ext_csd.sa_timeout = 1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
            }
        }
    }

    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int mmc_send_csd( e_device_type * card )
{
    mmcinfo("mmc_send_csd\n");

    /* Read CSD ==> CMD9 */
    return mmccr_SendCmd(MMC_SEND_CSD, card->rca, SD_R2, card->raw_csd);
}

/*******************************************************
 *
 *******************************************************/
#ifndef FPGA_SIRIUS_TEST
unsigned char get_emmc_type_select(void)
{
#define FORCE_PIN_MUX_TYPE
#ifdef FORCE_PIN_MUX_TYPE
    return 0;
#else
    int res;
    unsigned int pin_mux;
    unsigned int gpio_dir;
    /*
     * from "Sirius ROM CODE.ppt"
     *-----------------------------------------
     * BOOT_TYPE_bit0 from PAD_GPIO_20 as bit0
     * BOOT_TYPE_bit1 from PAD_GPIO_21 as bit1
     * BOOT_TYPE_bit2 from PAD_GPIO_22 as bit2
     *-----------------------------------------
     * 000 -> EMMC: TV256_LQFP Case 2,3,4,5
     *              TV_BGA
     * 001 -> NAND: TV256_LQFP Case 2,3,5
     *              TV_BGA
     *        EMMC: TV256_LQFP Case 1
     * 010 -> NAND: BOX176_LQFP Case 1,4,5,6,8
     *        EMMC: BOX176_LQFP Case 2
     * 011 -> EMMC: BOX176_LQFP Case 4,5
     * 100 -> EMMC: BOX176_LQFP Case 7
     * 101 -> EMMC: BOX176_LQFP Case 8
     * 110 -> EMMC: TV_BGA_LGE
     * 111 -> EMMC: TV_BGA_CHINA
     */
    /* get boot_type (from GPIO) */
    pin_mux  = cr_readl(GPIO_MUXCFG_7); // save pin mux
    gpio_dir = cr_readl(MIS_GP0DIR);    // save GPIO direction
    //REG32(GPIO_MUXCFG_7) = pin_mux | (0x1f << 27) | (0x1f << 18) | (0x1f << 9);   // set gpio_20_ps = 0x1f, gpio_21_ps = 0x1f, gpio_22_ps = 0x1f
    //REG32(MIS_GP0DIR) &= ~(0x7 << 22);    // set GPIO 20/21/22 as input pin, [22:20] = 0
    cr_writel(pin_mux | (0x1f << 27) | (0x1f << 18) | (0x1f << 9),GPIO_MUXCFG_7);
    cr_writel(cr_readl(MIS_GP0DIR) & ~(0x7 << 22),MIS_GP0DIR);
    res = (cr_readl(MIS_GP0DATI) >> 20) & 0x7;  // get boot_type type from GPIO [22:20]
    //REG32(MIS_GP0DIR) = gpio_dir; // restore GPIO direction
    //REG32(GPIO_MUXCFG_7) = pin_mux;   // restore pin mux
    cr_writel(gpio_dir,MIS_GP0DIR);
    cr_writel(pin_mux,GPIO_MUXCFG_7);
    return res;
#endif
}

static const unsigned int rtk_data_pin_mux_tbl[8][2] = {
    {GPIO_MUXCFG_13, 9  }, //D0
    {GPIO_MUXCFG_14, 27 }, //D1
    {GPIO_MUXCFG_14, 18 }, //D2
    {GPIO_MUXCFG_14, 9  }, //D3
    {GPIO_MUXCFG_15, 27 }, //D4
    {GPIO_MUXCFG_15, 18 }, //D5
    {GPIO_MUXCFG_15, 9  }, //D6
    {GPIO_MUXCFG_16, 27 }  //D7
};

static const unsigned int rtk_data_pin_mux7_tbl[8][2] = {
    {0xb8000888, 18 }, //D0
    {0xb8000888,  9 }, //D1
    {0xb8000884, 18 }, //D2
    {0xb80008a0, 18 }, //D3
    {0xb80008a0, 27 }, //D4
    {0xb800088c,  9 }, //D5
    {0xb8000874, 18 }, //D6
    {0xb8000884,  9 }  //D7
};
#define D_MUX(pin) rtk_data_pin_mux_tbl[pin][0]
#define D_SHT(pin) rtk_data_pin_mux_tbl[pin][1]
#define D_MUX7(pin) rtk_data_pin_mux7_tbl[pin][0]
#define D_SHT7(pin) rtk_data_pin_mux7_tbl[pin][1]

#define INPUT_MUX_MASK ((0x07UL<<28)|(0x03UL<<26)|(0x03UL<<24)| \
                        (0x03UL<<22)|(0x03UL<<20)|(0x03UL<<18)| \
                        (0x03UL<<15)|(0x03UL<<13)|(0x03UL<<11))
#define INPUT_MUX_VAL  (0x01UL<<28)
#define INPUT_MUX_VAL7 ((0x06UL<<28)|(0x02UL<<26)|(0x02UL<<24)| \
                        (0x02UL<<22)|(0x02UL<<20)|(0x02UL<<18)| \
                        (0x02UL<<15)|(0x02UL<<13)|(0x02UL<<11))

#define SET_RTK_INPUT_MUX_VAL(val)   \
        cr_writel((cr_readl(0xb8000914)&~INPUT_MUX_MASK)|val,0xb8000914);

/*
#define SET_RTK_INPUT_MUX()   \
        cr_writel((cr_readl(0xb8000914)&~INPUT_MUX_MASK)|INPUT_MUX_VAL,0xb8000914);
#define SET_RTK_INPUT_MUX7()  \
        cr_writel((cr_readl(0xb8000914)&~INPUT_MUX_MASK)|INPUT_MUX_VAL7,0xb8000914);
*/
void set_data_pin_mux(unsigned char mod)
{
    unsigned int i;
    unsigned int reginfo;
    if(mod == 7){
        //SET_RTK_INPUT_MUX7();
        SET_RTK_INPUT_MUX_VAL(INPUT_MUX_VAL7);
        for(i=0; i<8; i++){
            reginfo = cr_readl(D_MUX7(i)) & ~(0x1f<<D_SHT7(i));
            cr_writel(reginfo | 0x02UL<<D_SHT7(i), D_MUX7(i));
        }

    }else{
        //SET_RTK_INPUT_MUX();
        SET_RTK_INPUT_MUX_VAL(INPUT_MUX_VAL);
        for(i=0; i<8; i++){
            reginfo = cr_readl(D_MUX(i)) & ~(0x1f<<D_SHT(i));
            cr_writel(reginfo | 0x02UL<<D_SHT(i), D_MUX(i));
        }
    }
}

static const unsigned int rtk_cmd_pin_mux_tbl[8][3] = {
    {0xb8000844,  9, 2 }, //mod0
    {0xb8000844,  9, 2 }, //mod1
    {0xb8000844,  9, 2 }, //mod2
    {0xb8000844,  9, 2 }, //mod3
    {0xb8000844,  9, 2 }, //mod4
    {0xb8060228,  9, 1 }, //mod5
    {0xb8000844,  9, 2 }, //mod6
    {0xb8000958, 18, 2 }  //mod7
};
#define CMD_MUX(mod) rtk_cmd_pin_mux_tbl[mod][0]
#define CMD_SHT(mod) rtk_cmd_pin_mux_tbl[mod][1]
#define CMD_VAL(mod) rtk_cmd_pin_mux_tbl[mod][2]

void set_cmd_pin_mux(unsigned char mod)
{
    unsigned int reginfo;

    reginfo = cr_readl(CMD_MUX(mod)) & ~(0x1f<<CMD_SHT(mod));
    cr_writel(reginfo | CMD_VAL(mod)<<CMD_SHT(mod), CMD_MUX(mod));
}

static const unsigned int rtk_clk_pin_mux_tbl[8][3] = {
    {0xb8060248, 27, 0x01 }, //mod0
    {0xb8000840, 18, 0x02 }, //mod1
    {0xb8000848, 27, 0x02 }, //mod2
    {0xb8060248, 27, 0x01 }, //mod3
    {0xb8060830, 27, 0x02 }, //mod4
    {0xb8000228, 18, 0x01 }, //mod5
    {0xb8000850,  9, 0x02 }, //mod6
    {0xb80008a4,  9, 0x02 }  //mod7
};
#define CLK_MUX(mod) rtk_clk_pin_mux_tbl[mod][0]
#define CLK_SHT(mod) rtk_clk_pin_mux_tbl[mod][1]
#define CLK_VAL(mod) rtk_clk_pin_mux_tbl[mod][2]

void set_clk_pin_mux(unsigned char mod)
{
    unsigned int reginfo;

    reginfo = cr_readl(CLK_MUX(mod)) & ~(0x1f<<CLK_SHT(mod));
    cr_writel(reginfo | CLK_VAL(mod)<<CLK_SHT(mod), CLK_MUX(mod));
}

static const unsigned int rtk_rst_pin_mux_tbl[8][3] = {
    {0xb80008f8, 17, 0x1f }, //mod0
    {0xb8000844, 18, 0x1f }, //mod1
    {0xb8000830, 18, 0x1f }, //mod2
    {0xb8000860,  9, 0x1f }, //mod3
    {0xb8000834, 27, 0x1f }, //mod4
    {0xb8060228, 27, 0x1f }, //mod5
    {0xb80008f8, 17, 0x1f }, //mod6
    {0xb8000858,  9, 0x1f }  //mod7
};
#define RST_MUX(mod) rtk_rst_pin_mux_tbl[mod][0]
#define RST_SHT(mod) rtk_rst_pin_mux_tbl[mod][1]
#define RST_VAL(mod) rtk_rst_pin_mux_tbl[mod][2]

void set_rst_pin_mux(unsigned char mod)
{
    unsigned int reginfo;

    reginfo = cr_readl(RST_MUX(mod)) & ~(0x1f<<RST_SHT(mod));
    cr_writel(reginfo | RST_VAL(mod)<<RST_SHT(mod), RST_MUX(mod));
}

void mmccr_set_pin_mux()
{
    unsigned char mod;
    mod = get_emmc_type_select();

    set_data_pin_mux(mod);
    set_cmd_pin_mux(mod);
    set_rst_pin_mux(mod);
    set_clk_pin_mux(mod);
}


static const unsigned int rtk_rstn_tbl[8][3] = {
    {MIS_GP6DIR_reg,  MIS_GP6DATO_reg,   4 },    //mode 0; mis_gpio_196 == 6:4
    {MIS_GP1DIR_reg,  MIS_GP1DATO_reg,  23 },    //mode 1; mis_gpio_55  == 1:23
    {MIS_GP1DIR_reg,  MIS_GP1DATO_reg,   8 },    //mode 2; mis_gpio_40  == 1:8
    {MIS_GP3DIR_reg,  MIS_GP3DATO_reg,   1 },    //mode 3; mis_gpio_97  == 3:1
    {MIS_GP1DIR_reg,  MIS_GP1DATO_reg,  10 },    //mode 4; mis_gpio_42  == 1:10
    {ISO_GPDIR_1_reg, ISO_GPDATO_1_reg, 12 },    //mode 5; iso_gpio_44  == 1:12
    {MIS_GP6DIR_reg,  MIS_GP6DATO_reg,   4 },    //mode 6; mis_gpio_196 == 6:4
    {MIS_GP4DIR_reg,  MIS_GP4DATO_reg,  23 }     //mode 7; mis_gpio_151 == 4:23
};
#define R_GPD(mod) rtk_rstn_tbl[mod][0]
#define R_GPO(mod) rtk_rstn_tbl[mod][1]
#define R_BIT(mod) rtk_rstn_tbl[mod][2]
#endif

/* HW reset of eMMC */
int mmccr_hw_reset_signal( void )
{
#ifndef FPGA_SIRIUS_TEST
    int mod;
    //unsigned int tmp_mux;
    //unsigned int tmp_dir;
    //unsigned int tmp_dat;

    mod = get_emmc_type_select();
    UPRINTF("Pin mux mode %u\n",mod);
    UPRINTF("R_GPD=0x%08x R_GPO=0x%08x R_BIT=0x%08x\n",
            R_GPD(mod),R_GPO(mod),R_BIT(mod));

    cr_writel(cr_readl(R_GPO(mod)) & ~(0x01<<R_BIT(mod)), R_GPO(mod));  //MIS_GP0DATO
    cr_writel(cr_readl(R_GPD(mod)) |  (0x01<<R_BIT(mod)), R_GPD(mod));  //MIS_GP0DIR
    set_rst_pin_mux(mod);

    udelay(100);
    cr_writel(cr_readl(R_GPO(mod)) |  (0x01<<R_BIT(mod)), R_GPO(mod));  //MIS_GP0DATO
#endif

    return 0;
}

/*******************************************************
 *
 *******************************************************/
int mmccr_init_setup( void )
{
    mmccr_reset_cr_state(0);
    //emmc_card.rca = 1<<16; //setting at rtkmmc_generic.c int mmc_data_sync( struct mmc * mmc );
    emmc_card.sector_addressing = 0;
    cr_writel(0x00, CR_INT_MASK);
    cr_writel( RTKCR_INT_CLEAR_ALL, CR_INT_STATUS);
    mmccr_set_clk(EMMC_SOURCE_CLK, 0);
    mmccr_set_div(EMMC_INIT_CLOCK_DIV, 0);
    return 0;
}

/*******************************************************
 *
 *******************************************************/
void force_set_pinmux(void)
{
    /*
    rtd_maskl(0xb8000914,0x000000ff,0x10000000); // EMMC_Source control reg(176/256 QFP)
    rtd_maskl(0xb8060248,0x00ffffff,0x08000000); // EMMC_CLK st_gpio_12
    rtd_maskl(0xb8000844,0xffffc000,0x00000400); // EMMC_CMD gpio_56
    rtd_maskl(0xb8000834,0xffffc000,0x00000400); // EMMC_DAT0 gpio_44
    rtd_maskl(0xb8000838,0x00000000,0x10080400); // EMMC_DAT1/2/3 gpio_45/46/47
    rtd_maskl(0xb800083c,0x00000000,0x10080400); // EMMC_DAT4/5/6 gpio_48/49/50
    rtd_maskl(0xb8000840,0x007fffff,0x10000000); // EMMC_DAT7 gpio_51
    rtd_maskl(0xb80008F8,0xffc0ffff,0x003e0000); // EMMC_RST_N 0x1800_08F8[21:17]=0x1F  bb_dio3_ps  GPIO196
    */
    cr_writel( (cr_readl(0xb8000914)&0x000000ff)|0x10000000, 0xb8000914 );
    cr_writel( (cr_readl(0xb8060248)&0x00ffffff)|0x08000000, 0xb8060248 );
    cr_writel( (cr_readl(0xb8000844)&0xffffc000)|0x00000400, 0xb8000844 );
    cr_writel( (cr_readl(0xb8000834)&0xffffc000)|0x00000400, 0xb8000834 );
    cr_writel( (cr_readl(0xb8000838)&0x00000000)|0x10080400, 0xb8000838 );
    cr_writel( (cr_readl(0xb800083c)&0x00000000)|0x10080400, 0xb800083c );
    cr_writel( (cr_readl(0xb8000840)&0x007fffff)|0x10000000, 0xb8000840 );
    cr_writel( (cr_readl(0xb80008F8)&0xffc0ffff)|0x003e0000, 0xb80008F8 );
}

void show_pinmux(void)
{
    UPRINTF("emmc:0xb8000914=0x%08x\n",cr_readl(0xb8000914));
    UPRINTF("emmc:0xb8060248=0x%08x\n",cr_readl(0xb8060248));
    UPRINTF("emmc:0xb8000844=0x%08x\n",cr_readl(0xb8000844));
    UPRINTF("emmc:0xb8000834=0x%08x\n",cr_readl(0xb8000834));
    UPRINTF("emmc:0xb8000838=0x%08x\n",cr_readl(0xb8000838));
    UPRINTF("emmc:0xb800083c=0x%08x\n",cr_readl(0xb800083c));
    UPRINTF("emmc:0xb8000840=0x%08x\n",cr_readl(0xb8000840));
    UPRINTF("emmc:0xb80008F8=0x%08x\n",cr_readl(0xb80008F8));
}

#define CRT_SYS_CLKSEL  0xb8000040
#define mmc_reset_clk() cr_writel(0xe0,CRT_SYS_CLKSEL)

int mmc_initial( int reset_only )
{
    int ret_err;
    unsigned int tmp;
    unsigned int arg;
    unsigned int counter;
    unsigned int rsp_buffer[4];

    UPRINTF("\nemmc:%s(%d) %s %s\n", __FUNCTION__, reset_only, __DATE__, __TIME__);


#ifdef CONFIG_BOARD_298X_TV001_QFP176_EMMC

#ifndef FPGA_SIRIUS_TEST
    UPRINTF("emmc set pinmux\n");
#define USE_PIN_MUX_FUNC
#ifdef USE_PIN_MUX_FUNC
    mmccr_set_pin_mux();
#else
    force_set_pinmux();
#endif
    show_pinmux();

#else   //?#ifndef FPGA_SIRIUS_TEST
    UPRINTF("FPGA skip eMMC pinmux setting...\n");
#endif  //?#ifndef FPGA_SIRIUS_TEST
#endif  //?#ifdef CONFIG_BOARD_298X_TV001_QFP176_EMMC
    mmc_reset_clk();

    if( reset_only ) {
        UPRINTF("reset finish...\n");
        return 0;
    }

    /* reset mmc ip */
    mmccr_init_setup();

#ifndef FPGA_SIRIUS_TEST
    /* control reset pin, high -> low -> high */
    mmccr_hw_reset_signal();
    mmccr_toggle_clk_us(2000);
#else   //?#ifndef FPGA_SIRIUS_TEST
    UPRINTF("FPGA skip eMMC hardware reset...\n");
#endif  //?#ifndef FPGA_SIRIUS_TEST

    UPRINTF("run eMMC init flow..................................................\n");

    /* Reset command ==> CMD0 */
    mmccr_SendCmd(MMC_GO_IDLE_STATE, 0, SD_R0, rsp_buffer);

    /* Idle state ==> CMD1 */
    ret_err = 0;
    counter = 200;
    while( counter-- ) {
        udelay(100);
        //UPRINTF("EMMC_VDD_REQ = 0x%x, MMC_SECTOR_ADDR = 0x%x\n",EMMC_VDD_REQ,MMC_SECTOR_ADDR);
        ret_err = mmccr_SendCmd(MMC_SEND_OP_COND, EMMC_VDD_REQ|MMC_SECTOR_ADDR, SD_R3, rsp_buffer);

        if( ret_err || (rsp_buffer[0] == 0xffffffff) ) {
            UPRINTF("err out_1\n");
            ret_err = -1;
            break;
        }

        if( rsp_buffer[0] & MMC_CARD_READY ) {
            if( rsp_buffer[0] & MMC_SECTOR_ADDR ) {
                emmc_card.sector_addressing = 1;
                UPRINTF("sector ");
            }else{
                emmc_card.sector_addressing = 0;
                UPRINTF("bytes ");
            }
            UPRINTF("addressing mode.\n");
            //UPRINTF("CMD1 ready(0x%x)\n",rsp_buffer[0]);
            break;
        }
    }

    if( counter == 0 || ret_err ) {
        ret_err = -1;
        UPRINTF("err out_3\n");
        goto err_out;
    }

    /* Ready state ==> CMD2 */
    udelay(100);
    ret_err = 0;
    ret_err = mmccr_SendCmd(MMC_ALL_SEND_CID, 0, SD_R2, emmc_card.raw_cid);
    if(ret_err)
        goto err_out;

    mmc_show_cid(&emmc_card);

    /* Indentification state ==> CMD3 */
    udelay(100);
    ret_err = 0;
    ret_err = mmccr_SendCmd(MMC_SET_RELATIVE_ADDR, emmc_card.rca, SD_R1|CRC16_CAL_DIS, rsp_buffer);
    if(ret_err)
        goto err_out;

#if 0 // just for debuging, CMD9's RSP data will be shift left 1 if clock is too quickly.
    /* card initial done, apply for higher clock */
    mmccr_set_div(EMMC_NORMAL_CLOCK_DIV, 1);
#endif
    /* Send CSD  ==> CMD9 */
    udelay(100);
    ret_err = 0;
    ret_err = mmccr_SendCmd(MMC_SEND_CSD, emmc_card.rca, SD_R2, emmc_card.raw_csd);
    if(ret_err)
        goto err_out;

    mmc_show_csd(&emmc_card);

    /* card initial done, apply for higher clock */
    mmccr_set_div(EMMC_NORMAL_CLOCK_DIV, 1);

    /* Enter Transfer State ==> CMD7 */
    udelay(100);
    ret_err = 0;
    ret_err = mmccr_SendCmd(MMC_SELECT_CARD, emmc_card.rca, SD_R1b|CRC16_CAL_DIS, rsp_buffer);
    if(ret_err){
        mmcinfo("cmd7 error\n");
        goto err_out;
    }

    /* Read Ext CSD ==> cmd8 */
    mmcinfo("cmd8\n");
    udelay(100);
    ret_err = 0;
    ret_err = mmc_read_ext_csd(&emmc_card);
    if(ret_err){
        goto err_out;
    }

    /* change to 4bits width ==> CMD6 */
    if(0){
        mmcinfo("change to 4bits....\n");
        udelay(100);
        ret_err = 0;
        arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24)|
              (EXT_CSD_BUS_WIDTH          << 16)|
              (EXT_CSD_BUS_WIDTH_4        << 8)|
              EXT_CSD_CMD_SET_NORMAL;
        arg = 0x03 << 24 |
              0xb7 << 16 |
              0x01 << 8 |
              0x00;
        ret_err = mmccr_SendCmd(MMC_SWITCH, arg, SD_R1b|CRC16_CAL_DIS, rsp_buffer);
        if(ret_err) {
            mmcinfo("cmd6 fail, ret_err=%d\n", ret_err);
            goto err_out;
        }

        /* To wait status change complete */
        ret_err = 0;
        counter = 100;
        do {
            udelay(1000);
            ret_err = mmccr_SendCmd(MMC_SEND_STATUS, emmc_card.rca, SD_R1|CRC16_CAL_DIS, rsp_buffer);
            if(ret_err) {
                mmcinfo("cmd13 fail, ret_err=%d\n", ret_err);
                goto err_out;
            }

            counter--;

        }
        while((R1_CURRENT_STATE( rsp_buffer[0] ) == STATE_PRG) && counter);

        if( ( rsp_buffer[0] & R1_SWITCH_ERROR ) || ( counter == 0 ) )
        {
            mmcinfo("cmd6 response error\n");
            ret_err = -1;
            goto err_out;
        }
        else{
            mmccr_set_bits_width(BUS_WIDTH_4);
        }
    }

err_out:
    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int rtk_eMMC_init( void )
{
    int ret_err;
    int retry_counter;

    ret_err = -1;
    retry_counter = 3;
    rtkmmc_debug_msg = 1;
    rtkmmc_off_error_msg_in_init_flow = 0;
    while( retry_counter-- ) {
        ret_err = mmc_initial(0);
        if( ret_err ) {
            UPRINTF("\nemmc: init fail(%d)\n", ret_err);
        }
        else {
            return ret_err;
        }
    }
    return ret_err;
}

/*******************************************************
 *
 *******************************************************/
int rtk_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    e_device_type * card = &emmc_card;

    //UPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    if( !mmc_ready_to_use ) {
        UPRINTF("emmc: not ready to use\n");
        return 0;
    }

    total_blk_cont = data_size>>9;
    if(data_size & 0x1ff) {
        total_blk_cont+=1;
    }

    if( card->sector_addressing ) {
        address = blk_addr;
    }
    else {
        address = blk_addr << 9;
    }
#if 1
    while( total_blk_cont ) {
        if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
            curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
        }
        else {
            curr_xfer_blk_cont = total_blk_cont;
        }

        flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);
        ret_err = mmccr_Stream( address, curr_xfer_blk_cont, RTK_MMC_DATA_WRITE, buffer );

        if( ret_err ) {
            return 0;
        }
        total_blk_cont -= curr_xfer_blk_cont;
        buffer += (curr_xfer_blk_cont<<(9-2));
        if( card->sector_addressing ) {
            address += curr_xfer_blk_cont;
        }
        else {
            address += (curr_xfer_blk_cont<<9);
        }
    }

    total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }
    return total_blk_cont;
#else
    ret_err = mmccr_Stream( address, total_blk_cont, RTK_MMC_DATA_WRITE, buffer );

    return !ret_err ?  total_blk_cont : 0;
#endif
}

/*******************************************************
 *
 *******************************************************/
int rtk_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    e_device_type * card = &emmc_card;

    //UPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    if( !mmc_ready_to_use ) {
        UPRINTF("emmc: not ready to use\n");
        return 0;
    }

    total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }

    if( card->sector_addressing ) {
        address = blk_addr;
    }
    else {
        address = blk_addr << 9;
    }
#if 1
    while( total_blk_cont ) {
        if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
            curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
        }
        else {
            curr_xfer_blk_cont = total_blk_cont;
        }

        flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);
        ret_err = mmccr_Stream( address, curr_xfer_blk_cont, RTK_MMC_DATA_READ, buffer );

        if( ret_err ) {
            return 0;
        }
        total_blk_cont -= curr_xfer_blk_cont;
        buffer += (curr_xfer_blk_cont<<(9-2));
        if( card->sector_addressing ) {
            address += curr_xfer_blk_cont;
        }
        else {
            address += (curr_xfer_blk_cont<<9);
        }

        EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

    }

    total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }
    return total_blk_cont;
#else
    ret_err = mmccr_Stream( address, total_blk_cont, RTK_MMC_DATA_READ, buffer );

    return !ret_err ?  total_blk_cont : 0;
#endif
}

int do_rtkmmc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = CMD_RET_USAGE;
    unsigned int blk_addr, byte_size;
    void * mem_addr;

    if( argc == 5 ) {
        mem_addr   = (void *)simple_strtoul(argv[2], NULL, 16);
        blk_addr   = simple_strtoul(argv[3], NULL, 16);
        byte_size  = simple_strtoul(argv[4], NULL, 16)*512;
        if( strncmp( argv[1], "read", 4 ) == 0 ) {
            ret = rtk_eMMC_read( blk_addr, byte_size, mem_addr);
            return (ret ? 0 : 1);
        }
        else if( strncmp( argv[1], "write", 5 ) == 0 ) {
            ret = rtk_eMMC_write( blk_addr, byte_size, mem_addr);
            return (ret ? 0 : 1);
        }
    }else if( argc == 2 ) {
        if( strncmp( argv[1], "init", 4 ) == 0 ) {
            ret = rtk_eMMC_init();
            return (ret ? 0 : 1);
        }
    }

    return  ret;
}

U_BOOT_CMD(
    rtkmmc, 5, 0, do_rtkmmc,
    "RTK MMC direct function",
    ": all argument in HEX tpye.\n"
    "rtkmmc read  DDR_addr_byte MMC_blk_addr blk_cnt\n"
    "rtkmmc write DDR_addr_byte MMC_blk_addr blk_cnt\n"
    "rtkmmc init : execute re-initial flow\n"
    "\n"
);

