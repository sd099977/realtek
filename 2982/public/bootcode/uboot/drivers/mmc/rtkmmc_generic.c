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

#include "rtkmmc_generic.h"
#include "rtkmmc.h"

#define __RTKMMC_GENERIC_C__

int mmc_had_been_initialized;
int mmc_ready_to_use;
static struct mmc mmc_dev[2];

extern unsigned int rtkmmc_debug_msg;
extern unsigned int rtkmmc_off_error_msg_in_init_flow;

extern int mmc_initial( int reset_only );
extern int mmccr_init_setup( void );
extern int mmccr_SendCmd( unsigned int cmd_idx,
                   unsigned int cmd_arg,
                   unsigned int rsp_para,
                   unsigned int * rsp_buffer );
extern int mmccr_Stream_Only( unsigned int address,
                  unsigned int blk_cnt,
                  unsigned int xfer_flag,
                  unsigned int * data_buffer );
extern void mmccr_set_div( unsigned int set_div, unsigned int show_msg );

#ifdef CONFIG_GENERIC_MMC

static int rtkmmc_send_cmd(
            struct mmc * mmc,
            struct mmc_cmd * cmd,
            struct mmc_data * data )
{
    int ret_err;
    unsigned int rsp_para;

    //UPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), resp_type=0x%08x -------\n", __FILE__, __FUNCTION__, __LINE__, cmd->cmdidx, cmd->cmdidx, cmd->resp_type);
    //if( data ) {
    //  UPRINTF("*** %s %s %d, flags=0x%08x(%s), blks=%d, blksize=%d\n", __FILE__, __FUNCTION__, __LINE__, data->flags, (data->flags&MMC_DATA_READ) ? "R" : "W", data->blocks, data->blocksize);
    //}
    /*
     * CMDREG
     * CMDIDX[13:8] : Command index
     * DATAPRNT[5]  : Data Present Select
     * ENCMDIDX[4]  : Command Index Check Enable
     * ENCMDCRC[3]  : Command CRC Check Enable
     * RSPTYP[1:0]
     *  00 = No Response
     *  01 = Length 136
     *  10 = Length 48
     *  11 = Length 48 Check busy after response
     */
    /* Delay added before checking the status of frq change
     * retry not supported by mmc.c(core file)
     */
    rsp_para = 0;
    if( cmd->resp_type & MMC_RSP_PRESENT ) {
        if( cmd->resp_type & MMC_RSP_136 ) {
            rsp_para |= 0x02;  // RESP_TYPE_17B
        }
        else {
            rsp_para |= 0x01; // RESP_TYPE_6B
        }
        if( cmd->resp_type & MMC_RSP_CRC ) {

        }
        else {
            rsp_para |= ( /*(1<<7) |*/ (1<<2) ); // CRC7_CHK_DIS
        }
        if( cmd->resp_type & MMC_RSP_BUSY ) {
            rsp_para |= (1<<3); // WAIT_BUSY_EN
        }
    }

    ret_err = mmccr_SendCmd( cmd->cmdidx, cmd->cmdarg, rsp_para, cmd->response );

    if(ret_err == 0){
        if (data && (data->flags & MMC_DATA_READ)) {
            ret_err = mmccr_Stream_Only( 0, data->blocks, RTK_MMC_DATA_READ, (unsigned int *)data->dest );
        }
        else if (data && (data->flags & MMC_DATA_WRITE)) {
            ret_err = mmccr_Stream_Only( 0, data->blocks, RTK_MMC_DATA_WRITE, (unsigned int *)data->dest );
        }
    }

    return ret_err;
}

static void rtkmmc_set_ios(struct mmc * mmc)
{
    //UPRINTF("*** %s %s %d, bw=%d, clk=%d\n", __FILE__, __FUNCTION__, __LINE__, mmc->bus_width, mmc->clock);

    // mmc->clock
    if( mmc->clock <= 400000 ) {
        mmccr_set_div(EMMC_INIT_CLOCK_DIV, 0);
    }
    else {
        mmccr_set_div(EMMC_NORMAL_CLOCK_DIV, 0);
        if( mmc->clock > 25000000 ) {
            UPRINTF("emmc: warning, clock(%d) not support\n", mmc->clock );
        }
    }

    if(mmc->clock >= 25000000)
        mmccr_set_clk(CARD_SWITCHCLOCK_25MHZ, 0);
    else if(mmc->clock >= 20000000)
        mmccr_set_clk(CARD_SWITCHCLOCK_20MHZ, 0);
    else
        mmccr_set_clk(CARD_SWITCHCLOCK_16MHZ, 0);

    if( mmc->bus_width == 1 ) {
        mmccr_set_bits_width(BUS_WIDTH_1);
    }
    else if( mmc->bus_width == 4 ) {
        mmccr_set_bits_width(BUS_WIDTH_4);
        //mmccr_set_div(EMMC_NORMAL_CLOCK_DIV, 0); // hardware issue, read data timeout if clock is too slow
    }
    else if( mmc->bus_width == 8 ) {
        mmccr_set_bits_width(BUS_WIDTH_8);
        //mmccr_set_div(EMMC_NORMAL_CLOCK_DIV, 0); // hardware issue, read data timeout if clock is too slow
    }
    else {
        //UPRINTF("*** %s %s %d, ERR bw=%d, clk=%d\n", __FILE__, __FUNCTION__, __LINE__, mmc->bus_width, mmc->clock);
    }
}

static int rtkmmc_init_setup(struct mmc * mmc)
{
    //UPRINTF("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    mmccr_init_setup();
    return 0;
}

int board_mmc_init(bd_t * bis)
{
    int ret_err;
    struct mmc * pmmc;

    mmc_had_been_initialized = 0;
    mmc_ready_to_use = 0;

#if 0 // directly check eMMC device by customized init flow ( only for eMMC )
    rtkmmc_debug_msg = 1; // 1: enable debug message
    rtkmmc_off_error_msg_in_init_flow = 0; // 1: not show error message in initial stage
    ret_err = rtk_eMMC_init();
#else
    rtkmmc_debug_msg = 1; // 1: enable debug message
    rtkmmc_off_error_msg_in_init_flow = 1; // 1: not show error message in initial stage
    mmc_initial(1);
    ret_err = 0;
#endif
    if( !ret_err ) {
        pmmc = &mmc_dev[0];
        sprintf(pmmc->name, "RTD299x eMMC");
        pmmc->send_cmd = rtkmmc_send_cmd;
        pmmc->set_ios = rtkmmc_set_ios;
        pmmc->init = rtkmmc_init_setup;
        pmmc->getcd = NULL;
        pmmc->priv = NULL;
        pmmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
#ifdef CONFIG_MMC_MODE_4BIT
        pmmc->host_caps = (MMC_MODE_4BIT | MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_HC);
#else
        pmmc->host_caps = (MMC_MODE_8BIT | MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_HC);
#endif

        pmmc->f_min = 400000;
        pmmc->f_max = 25000000;
        pmmc->b_max = 256; // max transfer block size
        mmc_register(pmmc);
    }

    return ret_err;
}

int bringup_mmc_driver( void )
{
    int ret_err;
    struct mmc * mmc;
    int total_device_num = -1;
    int curr_device = -1;

    total_device_num = get_mmc_num();
    if ( total_device_num < 0 ) {
        printf("no registed mmc device\n");
        return curr_device;
    }

    if( mmc_had_been_initialized ) {
        return 0; // alwasy use slot 0
    }

    curr_device = 0; // alwasy use slot 0
    rtkmmc_debug_msg = 0; // 1: enable debug message
    rtkmmc_off_error_msg_in_init_flow = 1; // 1: not show error message in initial stage
    mmc = find_mmc_device(curr_device);
    if( mmc ) {
                EXECUTE_CUSTOMIZE_FUNC(0);
        mmc_init(mmc);
                EXECUTE_CUSTOMIZE_FUNC(0);
        printf("Device: %s\n", mmc->name);
        printf("Manufacturer ID: %x\n", mmc->cid[0] >> 24);
        printf("OEM: %x\n", (mmc->cid[0] >> 8) & 0xffff);
        printf("Name: %c%c%c%c%c \n", (mmc->cid[0] & 0xff),
                                      (mmc->cid[1] >> 24) & 0xff,
                                      (mmc->cid[1] >> 16) & 0xff,
                                      (mmc->cid[1] >> 8) & 0xff,
                                      (mmc->cid[1] >> 0) & 0xff);
        printf("Tran Speed: %d\n", mmc->tran_speed);
        printf("Rd Block Len: %d\n", mmc->read_bl_len);
        printf("%s version %d.%d\n", IS_SD(mmc) ? "SD" : "MMC", (mmc->version >> 4) & 0xf, mmc->version & 0xf);
        printf("High Capacity: %s\n", mmc->high_capacity ? "Yes" : "No");
        puts("Capacity: ");
        print_size(mmc->capacity, "\n");
        printf("Bus Width: %d-bit\n", mmc->bus_width);
        ret_err = curr_device;

        mmc_had_been_initialized = 1;
        if( mmc->capacity ) {
            mmc_ready_to_use = 1;
        }
        else {
            mmc_ready_to_use = 0;
        }
    }
    else {
        printf("no mmc device at slot %x\n", curr_device);
        ret_err = -999;
    }
    rtkmmc_debug_msg = 0; // 0: off cmd message
    rtkmmc_off_error_msg_in_init_flow = 0; // 0: show error message after init done
    return ret_err;
}

int mmc_data_sync( struct mmc * mmc )
{
    emmc_card.rca = (mmc->rca)<<16;
    emmc_card.sector_addressing = mmc->high_capacity ? 1 : 0;
    return 0;
}

#endif // end of CONFIG_GENERIC_MMC
