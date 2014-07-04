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
#include "NOCS.h"
#include "reset_def.h"
#include "error_type.h"
#include "emmc_boot.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define EMMC_BLOCK_BOUNDARY_SIZE    0x100
#define MAX_BLOCK_CNT               0x100

#define ERR_EMMC_DECODE_ERROR       18
#define ERR_EMMC_XFER_TIMEOUT       19

#define CR_IP_RESET_REG2            0xb800000C
#define CR_IP_RESET_REG2_BIT        24
#define CR_IP_RESET_REG             0xb8000004
#define CR_IP_RESET_REG_BIT         11

#define CP42K_SRAM_ADDR             0xb8070000
#define CP_SRAM_BASE                CP42K_SRAM_ADDR
#define CP_SRAM_SIZE                0xa800
#define PHYS_CP_SRAM(addr)          (addr - CP_SRAM_BASE)
#define IS_IN_CP_SRAM(addr)         ((unsigned int)PHYS_CP_SRAM(addr) < CP_SRAM_SIZE)

#define mmc_udelay(s) aux_mmc_udelay(s)

//#define EMMC_DEGUG

#ifdef EMMC_DEGUG
#define EMMC_PRINT(fmt, args...)            \
            printf(fmt,## args)

#define EMMC_FUNC(fmt, args...)         \
            printf("%s(%d)\n" fmt,__func__ ,__LINE__,## args)

#define EMMC_INFO(fmt, args...)         \
            printf("%s(%d)" fmt,__func__ ,__LINE__,## args)
#else

#define EMMC_PRINT(fmt, args...)
#define EMMC_FUNC(fmt, args...)
#define EMMC_INFO(fmt, args...)

#endif
/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int *rom_sys_flash_current_pos;
extern unsigned int aux_sys_flash_curent_pos;
/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/


/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int (*rom_mmc_blk_read)(unsigned int blk_addr, unsigned int blk_cnt, unsigned char * data_buffer);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
static
void aux_mmc_udelay(volatile unsigned int us)
{
    volatile unsigned int i;
    volatile unsigned int j;
    volatile unsigned int loop;

    loop = 10;
    for(i=0;i<us;i++){
        for(j=0;j<loop;j++){}
    }

}

static
void mmccr_reset_cr_state(void)
{
    unsigned int tmp;
    unsigned int reginfo;
    unsigned int old_config1;
    unsigned int old_config2;
    unsigned int old_config3;

    EMMC_FUNC();
    old_config1 = cr_readl(SD_CONFIGURE1);
    old_config2 = cr_readl(SD_CONFIGURE2);
    old_config3 = cr_readl(SD_CONFIGURE3);

    tmp = cr_readl( CR_IP_RESET_REG2 );
    tmp &= ~(1UL<<CR_IP_RESET_REG2_BIT);
    cr_writel( tmp, CR_IP_RESET_REG2 );

    //UPRINTF("emmc:clear 0x%08x[%u]\n", CR_IP_RESET_REG,CR_IP_RESET_REG_BIT);
    tmp = cr_readl( CR_IP_RESET_REG );
    tmp &= ~(1UL<<CR_IP_RESET_REG_BIT);
    cr_writel( tmp, CR_IP_RESET_REG );

    //UPRINTF("emmc:set 0x%08x[%u]\n", CR_IP_RESET_REG,CR_IP_RESET_REG_BIT);
    tmp = cr_readl( CR_IP_RESET_REG );
    tmp |= (1UL<<CR_IP_RESET_REG_BIT);
    cr_writel( tmp, CR_IP_RESET_REG );

    //UPRINTF("emmc:set 0x%08x[%u]\n", CR_IP_RESET_REG2,CR_IP_RESET_REG2_BIT);
    tmp = cr_readl( CR_IP_RESET_REG2 );
    tmp |= (1UL<<CR_IP_RESET_REG2_BIT);
    cr_writel( tmp, CR_IP_RESET_REG2 );

    cr_writel(old_config1,SD_CONFIGURE1);
    cr_writel(old_config2,SD_CONFIGURE2);
    cr_writel(old_config3,SD_CONFIGURE3);
}

static
int mmccr_TriggerXferCmd( unsigned int xferCmdCode, unsigned int max_mdelay_cnt )
{
    unsigned int loops;
    unsigned int sd_transfer_reg;
    unsigned int sd_stat_reg;
    unsigned int sd_int_stat_reg;
    int ret_err = 0;

    EMMC_FUNC();

    loops = 10000;
    while((cr_readl(SD_STAT) & (0x01UL<<1) == 0) && loops--){
        EMMC_INFO("wait EMMC ready....(%u)\n",loops);
        mmc_udelay(1);
    }
    if(loops == 0){
        EMMC_PRINT("EMMC always busy....\n");
        ret_err = -ERR_EMMC_XFER_TIMEOUT;
        goto ERR_OUT;
    }

	cr_writel( cr_readl(CR_INT_MASK) |
               (RTKCR_GET_PIN_OPTION |RTKCR_WRITE_OPTION),
               CR_INT_MASK);

    cr_writel( RTKCR_INT_CLEAR_ALL, CR_INT_STATUS );
    cr_writel( xferCmdCode|START_EN, SD_TRANSFER );

    mmc_udelay(10);

    ret_err = -ERR_EMMC_XFER_TIMEOUT; // TIMEOUT ( defined in include/mmc.h )
    loops   = max_mdelay_cnt;
    while( loops )
    {
        sd_int_stat_reg = cr_readl(CR_INT_STATUS);
        if(sd_int_stat_reg & RTKCR_INT_DECODE_FINISH){
            cr_writel(RTKCR_INT_DECODE_FINISH,CR_INT_STATUS);   //clear decode finish
            sd_stat_reg     = cr_readl(SD_STAT);
            sd_transfer_reg = cr_readl(SD_TRANSFER);
            if((sd_transfer_reg & END_STATE) == 0){
                ret_err = -ERR_EMMC_XFER_TIMEOUT;
            }
            else if( sd_int_stat_reg & RTKCR_INT_DECODE_ERROR ||
                     sd_stat_reg & MASK_SD_STAT_ERR )
            {
                EMMC_INFO("sd_stat(40h)   =0x%02x(error bit[7:5])\n", sd_stat_reg);
                EMMC_INFO("int_status(48h)=0x%02x(decode error[bit2])\n", sd_int_stat_reg);
                ret_err = -ERR_EMMC_DECODE_ERROR;
            }else{
                ret_err = 0;
            }
            break;
        }
        mmc_udelay(10);
        loops--;
    }

    if(ret_err){
        EMMC_PRINT("ret_err=%d\n",ret_err);
        mmccr_reset_cr_state();
    }
ERR_OUT:
    return ret_err;
}


static
void mmccr_read_rsp( unsigned int * rsp, unsigned int reg_count )
{
    EMMC_FUNC();
    if ( reg_count == 6 ){
        rsp[0] = cr_readl(CR_CARD_RESP6_1) << 24 |
                 cr_readl(CR_CARD_RESP6_2) << 16 |
                 cr_readl(CR_CARD_RESP6_3) << 8 |
                 cr_readl(CR_CARD_RESP6_4);
    }
    else if(reg_count == 17 ){
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
    }
}


static
unsigned int mmc_get_rsp_len( unsigned char rsp_para )
{
    EMMC_FUNC();
    switch (rsp_para & 0x3)
    {
        case 0:
            return 0;
        case 1:
            return 6;
        case 2:
            return 17;
        default:
            return 0;
    }
}


static
unsigned int mmc_get_rsp_type( struct rtk_mmc_command * cmd ){

    unsigned int rsp_type = 0;

    EMMC_FUNC();
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
        case 12:    // stop_transmission-write case
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

static
int mmccr_SendCmd( unsigned char    cmd_idx,
                   unsigned int     cmd_arg,
                   unsigned char    rsp_para,
                   unsigned int *   rsp )
{
    unsigned char rsp_len;
    int ret_err;

    EMMC_FUNC();
    rsp_len = mmc_get_rsp_len(rsp_para);

    cr_writel(0x40| cmd_idx,        SD_CMD0);
    cr_writel(cmd_arg>>24,          SD_CMD1);
    cr_writel(cmd_arg>>16,          SD_CMD2);
    cr_writel(cmd_arg>>8,           SD_CMD3);
    cr_writel(cmd_arg,              SD_CMD4);
    cr_writel(rsp_para,             SD_CONFIGURE2);

    ret_err = mmccr_TriggerXferCmd(SD_SENDCMDGETRSP, 1000);

    if( !ret_err ){
        mmccr_read_rsp(rsp, rsp_len);

    }else{
        /*
        if error happend,reset Host and card
        magellan maybe need new flow
        */
        ret_err = ERR_EMMC_CMD_TOUT_RSP;
    }

    return ret_err;
}

static
int mmccr_Stream_Cmd( unsigned int          xferCmdCode,
                      struct rtk_cmd_info * cmd_info )
{
    unsigned int cmd_idx      = cmd_info->cmd->opcode;
    unsigned int cmd_arg      = cmd_info->cmd->arg;
    unsigned int * rsp        = cmd_info->cmd->resp;
    unsigned int rsp_para     = cmd_info->rsp_para;
    int rsp_len               = cmd_info->rsp_len;
    unsigned int byte_count   = cmd_info->byte_count;
    unsigned int block_count  = cmd_info->block_count;
    unsigned int phy_buf_addr;
    unsigned int timeout;
    int ret_err;

    EMMC_FUNC();

    EMMC_INFO("cmd_idx=%x arg=0x%08x rsp_para=0x%02x\n"
               "    byte_count=0x%04x; block_count=0x%04x; phy addr=0x%08x\n",
            cmd_idx, cmd_arg, rsp_para,
            byte_count, block_count, phy_buf_addr);

    cr_writel(cr_readl(CP_CTRL) & ~BOOT_FROM_CR, CP_CTRL);
    if(IS_IN_CP_SRAM(cmd_info->data_buffer)){
        EMMC_INFO("CP_SRAM Hit\n");
        // if CP_SRAM mode enable,skip local sram mode
        cr_writel(cr_readl(CR_INT_MASK)|(0x01UL<<3),  CR_INT_MASK);
    }
    else{
        EMMC_INFO("NOT CP_SRAM Hit\n");
          cr_writel(cr_readl(CR_INT_MASK) & ~(0x01UL<<3),  CR_INT_MASK);
    }

    phy_buf_addr = PHYS(cmd_info->data_buffer);
    EMMC_INFO("%s(%d)Addr=0x%08x\n",__func__,__LINE__,phy_buf_addr);

    if( RTK_MMC_DATA_DIR(cmd_info) & RTK_MMC_DATA_WRITE ){
        EMMC_INFO("DMA out\n");
        cr_writel( phy_buf_addr, CR_DMA_OUT_ADDR);
    }
    else{
        EMMC_INFO("DMA in\n");
        cr_writel( phy_buf_addr, CR_DMA_IN_ADDR);
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

    ret_err = mmccr_TriggerXferCmd( xferCmdCode, timeout );

    if( !ret_err ){
        mmccr_read_rsp( rsp, rsp_len);
        if( rsp[0] == 0xFFFFFFFF ) {
            //EMMC_INFO("RSP data fmt error\n");
            ret_err = -1;
        }

        if( !ret_err ) {
            //EMMC_INFO("get data to buffer\n");
            if( RTK_MMC_DATA_DIR(cmd_info) & RTK_MMC_DATA_SRAM ) {
                unsigned int i;
                unsigned int * sram_buf = (unsigned int *)cmd_info->data_buffer;
                unsigned int fifo_tmp;
                if(sram_buf){
                    for( i=0; i<128; i++){
                        fifo_tmp = cr_readl(CR_SRAM_BASE);
                        sram_buf[i]= fifo_tmp;
                    }
                }
                mmc_udelay(1000);
            }
            //EMMC_INFO("get data finish\n");
        }

    }else{
        //EMMC_INFO("error occur\n");
    }

err_out:
    if( ret_err ){
        //EMMC_INFO("mmccr_Stream_Cmd fail");
    }
    return ret_err;
}


static
int mmccr_Stream( unsigned int      address,
                  unsigned int      blk_cnt,
                  unsigned int      xfer_flag,
                  unsigned char *   data_buffer )
{
    struct rtk_cmd_info     cmd_info;
    struct rtk_mmc_command  cmd;
    unsigned int            xferCmdCode;
    int                     err = -1;
    unsigned int            rsp_type;

    EMMC_FUNC();
    cmd_info.cmd    = &cmd;
    cmd.arg         = address;


    if( xfer_flag & RTK_MMC_DATA_WRITE ){
        xferCmdCode = SD_AUTOWRITE2;
        cmd.opcode  = 24;
    }else{
        xferCmdCode = SD_AUTOREAD2;
        cmd.opcode  = 17;
    }

    /* multi sector accress opcode */
    if(blk_cnt > 1){
        cmd.opcode++;
        xferCmdCode -= 1;
    }

    rsp_type = mmc_get_rsp_type(&cmd);

    cmd_info.rsp_para    = rsp_type;
    cmd_info.rsp_len     = mmc_get_rsp_len(rsp_type);
    cmd_info.byte_count  = 0x200;
    cmd_info.block_count = blk_cnt;
    cmd_info.data_buffer = data_buffer;
    cmd_info.xfer_flag   = xfer_flag;

    err = mmccr_Stream_Cmd( xferCmdCode, &cmd_info );
    if(err){
        EMMC_PRINT("stream cmd fail\n");
    }
    return err;
}


int mmc_blk_read( unsigned int      blk_addr,
                  unsigned int      blk_cnt,
                  unsigned char *   data_buffer )
{
    unsigned int tar_dest;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned char*  tmp_buf_addr;
    int ret_err = 0;

    EMMC_FUNC();
    EMMC_INFO("%s(%d)total_blk_cont=0x%08x\n",
                __func__,__LINE__,total_blk_cont);

    tar_dest        = blk_addr;
    total_blk_cont  = blk_cnt;
    tmp_buf_addr    = data_buffer;

    while( total_blk_cont ) {

        if(total_blk_cont > MAX_BLOCK_CNT)
            curr_xfer_blk_cont = MAX_BLOCK_CNT;
        else
            curr_xfer_blk_cont = total_blk_cont;

        ret_err = mmccr_Stream( tar_dest,
                                curr_xfer_blk_cont,
                                RTK_MMC_DATA_READ,
                                tmp_buf_addr);
        if(ret_err){
            break;
        }

        tar_dest        += curr_xfer_blk_cont;
        total_blk_cont	-= curr_xfer_blk_cont;
        tmp_buf_addr    += (curr_xfer_blk_cont<<9);

    }

    return ret_err;
}


int mmc_blk_write( unsigned int     blk_addr,
                   unsigned int     blk_cnt,
                   unsigned char *  data_buffer )
{
    unsigned int    tar_dest;
    unsigned int    total_blk_cont;
    unsigned int    curr_xfer_blk_cont;
    unsigned char*  tmp_buf_addr;
    int             ret_err = 0;

    EMMC_FUNC();
    EMMC_INFO("%s(%d)total_blk_cont=0x%08x\n",
                __func__,__LINE__,total_blk_cont);

    tar_dest        = blk_addr;
    total_blk_cont  = blk_cnt;
    tmp_buf_addr    = data_buffer;

    while( total_blk_cont ) {

        if(total_blk_cont > MAX_BLOCK_CNT)
            curr_xfer_blk_cont = MAX_BLOCK_CNT;
        else
            curr_xfer_blk_cont = total_blk_cont;

        ret_err = mmccr_Stream( tar_dest,
                                curr_xfer_blk_cont,
                                RTK_MMC_DATA_WRITE,
                                tmp_buf_addr);
        if(ret_err){
            break;
        }

		tar_dest 		+= curr_xfer_blk_cont;
        total_blk_cont  -= curr_xfer_blk_cont;
        tmp_buf_addr    += (curr_xfer_blk_cont<<9);

    }

    return ret_err;
}

/* mmc function &&& */

static unsigned int align_block_count(unsigned int length)
{
    unsigned int block_count;

    block_count = length / EMMC_BLOCK_SIZE;
    if (length % EMMC_BLOCK_SIZE)
        block_count++;

    return block_count;
}

int get_dte_kboot_emmc(unsigned int dst_addr, unsigned int size)
{
    unsigned int blk_cnt = align_block_count(size);
    unsigned int blk_no = aux_sys_flash_curent_pos;
    unsigned int read_cnt;

    debug("total blk_no = 0x%x, blk_cnt = 0x%x, size = 0x%x\n", blk_no, blk_cnt, size);

    REG32(0xb801084c) &= ~0x8;  // switch Dbus to DDR

    while (blk_cnt > 0) {
        //change read block cnt to word around emmc driver bug
        read_cnt = (blk_cnt > EMMC_BLOCK_BOUNDARY_SIZE) ? EMMC_BLOCK_BOUNDARY_SIZE : blk_cnt;
        if (((blk_no + read_cnt) & (EMMC_BLOCK_BOUNDARY_SIZE - 1)) && (blk_cnt > EMMC_BLOCK_BOUNDARY_SIZE)) {
            read_cnt = EMMC_BLOCK_BOUNDARY_SIZE - ((blk_no + read_cnt) & (EMMC_BLOCK_BOUNDARY_SIZE - 1));
        }

        debug("blk_no = 0x%x, read_cnt = 0x%x, dst_addr = 0x%x, remain blk_cnt = 0x%x\n", blk_no, read_cnt, dst_addr, blk_cnt);

		if( rom_mmc_blk_read(blk_no, read_cnt, (unsigned char *)dst_addr) )
            return ERR_GET_DTE_KBOOT_FAILED;

        blk_no += read_cnt;
        blk_cnt -= read_cnt;
        dst_addr += read_cnt * EMMC_BLOCK_SIZE;
    }

	aux_sys_flash_curent_pos = blk_no; // save the current pos

    return 0;
}

int get_dte_bootcode_emmc(unsigned int dst_addr, unsigned int size)
{
    unsigned int blk_cnt = align_block_count(size);
    unsigned int blk_no = *rom_sys_flash_current_pos + align_block_count(SCS_UNCHECK_AREA);
    unsigned int read_cnt;

    debug("total blk_no = 0x%x, blk_cnt = 0x%x, size = 0x%x\n", blk_no, blk_cnt, size);

    REG32(0xb801084c) &= ~0x8;  // switch Dbus to DDR

    while (blk_cnt > 0) {
        //change read block cnt to word around emmc driver bug
        read_cnt = (blk_cnt > EMMC_BLOCK_BOUNDARY_SIZE) ? EMMC_BLOCK_BOUNDARY_SIZE : blk_cnt;
        if (((blk_no + read_cnt) & (EMMC_BLOCK_BOUNDARY_SIZE - 1)) && (blk_cnt > EMMC_BLOCK_BOUNDARY_SIZE)) {
            read_cnt = EMMC_BLOCK_BOUNDARY_SIZE - ((blk_no + read_cnt) & (EMMC_BLOCK_BOUNDARY_SIZE - 1));
        }

        debug("blk_no = 0x%x, read_cnt = 0x%x, dst_addr = 0x%x, remain blk_cnt = 0x%x\n", blk_no, read_cnt, dst_addr, blk_cnt);

		if( rom_mmc_blk_read(blk_no, read_cnt, (unsigned char *)dst_addr) )
            return ERR_GET_DTE_BOOTCODE_FAILED;

        blk_no += read_cnt;
        blk_cnt -= read_cnt;
        dst_addr += read_cnt * EMMC_BLOCK_SIZE;
    }

	aux_sys_flash_curent_pos = blk_no; // save the current pos

    return 0;
}

int get_hwsetting_emmc(unsigned int dst_addr,  int size)
{
    unsigned int blk_cnt = align_block_count(size);
    unsigned int blk_no = *rom_sys_flash_current_pos ;

	if( rom_mmc_blk_read(blk_no, blk_cnt, (unsigned char *)dst_addr) )
        return ERR_HWSETTING_FAILED;

    return 0;
}
