#include <project_config.h>
#include <stdio.h>
#include <sysdefs.h>
#include "flashdev_e.h"
#include <util.h>

/************************************************************************
 *  Definitions
*************************************************************************/
/* mmc spec definition */
static const unsigned int tran_exp[] = {
    10000,      100000,     1000000,    10000000,
    0,      0,      0,      0
};

static const unsigned char tran_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

static const unsigned int tacc_exp[] = {
    1,  10, 100,    1000,   10000,  100000, 1000000, 10000000,
};

static const unsigned int tacc_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

#define UNSTUFF_BITS(resp,start,size)                   \
    ({                              \
        const int __size = size;                \
        const UINT32 __mask = (__size < 32 ? 1 << __size : 0) - 1; \
        const int __off = 3 - ((start) / 32);           \
        const int __shft = (start) & 31;            \
        UINT32 __res;                      \
                                    \
        __res = resp[__off] >> __shft;              \
        if (__size + __shft > 32)               \
            __res |= resp[__off-1] << ((32 - __shft) % 32); \
        __res & __mask;                     \
    })

/* realtek definition */
#define cr_writel(value,addr)   REG32(addr) = value;
                                //sync()

#define cr_readl(addr)          REG32(addr)

#define ON                  0
#define OFF                 1

#define R_W_CMD             2   //read/write command
#define INN_CMD             1   //command work chip inside
#define UIN_CMD             0   //no interrupt rtk command

#define RTK_FAIL            3  /* DMA error & cmd parser error */
#define RTK_RMOV            2  /* card removed */
#define RTK_TOUT            1  /* time out include DMA finish & cmd parser finish */
#define RTK_SUCC            0

#define BYTE_CNT            0x200
#define DMA_BUFFER_SIZE     128*512
#define RTK_NORM_SPEED      0x00
#define RTK_HIGH_SPEED      0x01
#define RTK_1_BITS          0x00
#define RTK_4_BITS          0x10
#define RTK_8_BITS          0x11
#define RTK_BITS_MASK       0x30
#define RTK_SPEED_MASK      0x01
#define RTK_PHASE_MASK      0x06

/* send status event */
#define STATE_IDLE      0
#define STATE_READY     1
#define STATE_IDENT     2
#define STATE_STBY      3
#define STATE_TRAN      4
#define STATE_DATA      5
#define STATE_RCV       6
#define STATE_PRG       7
#define STATE_DIS       8

#define EMMC_VDD_30_31  0x00040000  /* VDD voltage 3.0 ~ 3.1 */
#define EMMC_VDD_31_32  0x00080000  /* VDD voltage 3.1 ~ 3.2 */
#define EMMC_VDD_32_33  0x00100000  /* VDD voltage 3.2 ~ 3.3 */
#define EMMC_VDD_33_34  0x00200000  /* VDD voltage 3.3 ~ 3.4 */
#define EMMC_VDD_34_35  0x00400000  /* VDD voltage 3.4 ~ 3.5 */
#define EMMC_VDD_35_36  0x00800000  /* VDD voltage 3.5 ~ 3.6 */
#define EMMC_CARD_BUSY  0x80000000  /* Card Power up status bit */

#define ROM_EMMC_VDD    EMMC_VDD_35_36|EMMC_VDD_34_35|EMMC_VDD_33_34|EMMC_VDD_32_33|EMMC_VDD_31_32|EMMC_VDD_30_31

#define EMMC_SCT_ACC    0x40000000  /* host support sector mode access */

#define romcr_get_int_sta(status_addr) \
            *(UINT32 *)status_addr = cr_readl(CR_INT_STATUS)

#define romcr_get_sd_sta(status_addr) \
            *(UINT32 *)status_addr = cr_readl(SD_STAT)

#define romcr_clr_int_sta() \
            cr_writel( RTKCR_INT_DECODE_ERROR |  \
                       RTKCR_INT_DECODE_FINISH  |  \
                       RTKCR_INT_STATUS_CHANGE,    \
                       CR_INT_STATUS)

#define romcr_hold_int_all() cr_writel(0x00, CR_INT_MASK)

/* static UINT8    addr_mode */
#define ADDR_MODE_BIT   1
#define ADDR_MODE_SEC   0

/* log display option */
//#define SHOW_CID
//#define SHOW_CSD
//#define SHOW_EXT_CSD
//#define SHOW_SRAM_REG
//#define SHOW_SRAM_BUFF

/* mmcinfo define */
//#define EMMC_DEBUG
#ifdef EMMC_DEBUG
    #define mmcinfo(fmt, args...) \
               printf("emmc:" fmt,## args)
#else
    #define mmcinfo(fmt, args...)
#endif

#define EMMC_MSG1
#ifdef EMMC_MSG1
    #define mmcmsg1(fmt, args...) \
               printf("emmc:" fmt,## args)
#else
    #define mmcmsg1(fmt, args...)
#endif


/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static UINT32   int_status;
static UINT32   sd_status;
e_device_type  emmc_card;   //eMMC device data structure

const char *const state_tlb[9] = {
    "STATE_IDLE",
    "STATE_READY",
    "STATE_IDENT",
    "STATE_STBY",
    "STATE_TRAN",
    "STATE_DATA",
    "STATE_RCV",
    "STATE_PRG",
    "STATE_DIS"
};
const char *const bit_tlb[4] = {
    "1bit",
    "4bits",
    "8bits",
    "unknow"
};

const char *const clk_tlb[8] = {
    "30MHz",
    "40MHz",
    "49MHz",
    "49MHz",
    "15MHz",
    "20MHz",
    "24MHz",
    "24MHz"
};

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int sys_bootcode_address;
extern unsigned int sys_bootcode_size;

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int get_secure_boot_type(void);
extern int parse_hw_setting_c(unsigned int *ptr, const unsigned int limit,
                              unsigned int *parsed_bytes, const char skip);
extern int is_bootcode_encrypted(void);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static void wait_loop(unsigned int count)
{
    while (count--);
}

/************************************************************************
 *  Function body
 ************************************************************************/

void mmccr_reset_cr_state( unsigned char save_en )
{
    volatile unsigned int reginfo;
    volatile unsigned int org_config1;
    volatile unsigned int org_config2;
    volatile unsigned int org_config3;

    if(save_en){
        // save current configuration
        org_config1 = cr_readl(SD_CONFIGURE1);
        org_config2 = cr_readl(SD_CONFIGURE2);
        org_config3 = cr_readl(SD_CONFIGURE3);
    }

    /* reset emmc host ip */
    cr_writel(0xe0,0x18000040);
    reginfo =cr_readl(0x1800000c) & ~(0x01UL<<24);
    cr_writel(reginfo,0x1800000c);

    reginfo =cr_readl(0x18000004) & ~(0x01UL<<11);
    cr_writel(reginfo,0x18000004);

    mdelay(2);

    reginfo =cr_readl(0x18000004) | (0x01UL<<11);
    cr_writel(reginfo,0x18000004);

    reginfo =cr_readl(0x1800000c) | (0x01UL<<24);
    cr_writel(reginfo,0x1800000c);

    if(save_en){
        cr_writel( org_config1, SD_CONFIGURE1);
        cr_writel( org_config2, SD_CONFIGURE2);
        cr_writel( org_config3, SD_CONFIGURE3);
    }
}

static int romcr_wait_opt_end(UINT8 cmdcode,UINT32 cmd_type)
{
    UINT32 timeend = 0;
    unsigned int sd_transfer_reg = 0;
    unsigned int sd_stat_reg;
    unsigned int sd_int_stat_reg;
    int err;

    mmcinfo("romcr_wait_opt_end\n");

    timeend = 50000;

    cr_writel(cr_readl(CR_INT_MASK)|
              (RTKCR_GET_PIN_OPTION|RTKCR_WRITE_OPTION),
              CR_INT_MASK);

    romcr_clr_int_sta();
    cr_writel(cmdcode|START_EN, SD_TRANSFER);

    wait_loop(5000);

    err = -RTK_TOUT;

    while(timeend )
    {
        sd_int_stat_reg = cr_readl(CR_INT_STATUS);
        sd_stat_reg     = cr_readl(SD_STAT);
        //if((cr_readl(CR_INT_STATUS) & RTKCR_INT_DECODE_FINISH) &&
        //   (cr_readl(SD_STAT) & DAT0_LEVEL))
        if( (sd_int_stat_reg & RTKCR_INT_DECODE_FINISH) &&
            (sd_stat_reg & DAT0_LEVEL) )
        {
            cr_writel(RTKCR_INT_DECODE_FINISH,CR_INT_STATUS);
            sd_stat_reg     = cr_readl(SD_STAT);
            sd_transfer_reg = cr_readl(SD_TRANSFER);

            int_status = sd_int_stat_reg;
            sd_status  = sd_stat_reg;
            if((sd_transfer_reg & END_STATE) == 0){
                err = -1;
            }
            else if( sd_int_stat_reg & RTKCR_INT_DECODE_ERROR ||
                     sd_stat_reg & MASK_SD_STAT_ERR )
            {
                mmcinfo("sd_stat(40h)   =0x%02x(error bit[7:5])\n", sd_stat_reg);
                mmcinfo("int_status(48h)=0x%02x(decode error[bit2])\n", cr_int_status_reg);
                err = -2;
            }else{
                err = 0;
            }
            break;
        }
        wait_loop(30000);
        timeend--;
    }

    mmcinfo("opterr=%d\n",err);
    if(err)
        mmccr_reset_cr_state(1);
    return err;
}

#define romcr_set_config1(set_cfg)   \
            cr_writel(set_cfg,SD_CONFIGURE1)

#define romcr_get_config1()     cr_readl(SD_CONFIGURE1)

#define romcr_set_config2(set_cfg)   \
            cr_writel(set_cfg,SD_CONFIGURE2)

#define romcr_get_config2()     cr_readl(SD_CONFIGURE2)

#define romcr_set_config3(set_cfg)   \
            cr_writel(set_cfg,SD_CONFIGURE3)

#define romcr_get_config3()     cr_readl(SD_CONFIGURE3)

static void romcr_set_div(UINT32 set_div)
{
    UINT32 tmp_div;

    tmp_div = cr_readl(SD_CONFIGURE1) & ~MASK_CLOCK_DIV;
    cr_writel(tmp_div|set_div,SD_CONFIGURE1);
}

static void romcr_set_bits(UINT32 set_bit)
{
    UINT32 tmp_bits;

    tmp_bits = cr_readl(SD_CONFIGURE1) & ~MASK_BUS_WIDTH;
    cr_writel(tmp_bits|set_bit,SD_CONFIGURE1);
}

static void romcr_set_speed(UINT32 para)
{
    UINT32 tmp_para;

    tmp_para = cr_readl(SD_CONFIGURE1)& ~SPEED_MOD_HIGH;
    cr_writel(tmp_para|para,SD_CONFIGURE1);
}

static void romcr_set_clk(UINT8 mmc_clk)
{
/*
    UINT32 tmp_clk = cr_readl(SYS_CLKSEL) & ~EMMC_CLKSEL_MASK;
    mmcinfo("romcr_set_clk\n"
           "clk change to %s\n",clk_tlb[mmc_clk]);

    cr_writel(tmp_clk|mmc_clk,   SYS_CLKSEL);

    if(mmc_clk > CLOCK_SPEED_GAP){
        romcr_set_speed(SPEED_MOD_NORM);
    }else{
        romcr_set_speed(SPEED_MOD_HIGH);
    }
*/
}

static void romcr_read_rsp(UINT32 *rsp, int reg_count)
{
    mmcinfo("*rsp=0x%p; reg_count=%u\n",rsp,reg_count);

    if ( reg_count == 6 ){
        rsp[0] = cr_readl(CR_CARD_RESP6_1) << 24 |
                 cr_readl(CR_CARD_RESP6_2) << 16 |
                 cr_readl(CR_CARD_RESP6_3) << 8 |
                 cr_readl(CR_CARD_RESP6_4);

    }else if(reg_count == 16){
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

UINT8 romcr_get_rsp_len(UINT8 rsp_para)
{
    mmcinfo("romcr_get_rsp_len\n");
    switch (rsp_para & 0x3) {
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 16;
    default:
        return 0;
    }
}

/*******************************************************

********************************************************/
UINT8 get_rsp_type(struct mmc_command* cmd ){

    UINT8 rsp_type = 0;
    mmcinfo("get_rsp_type\n");

    /* the marked case are used. */
    switch(cmd->opcode)
    {
        case 3:
        case 7:     // select_card
        //case 12:  // stop_transmission-read case
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
        //case 7:   // deselect_card
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
        //case 39:
        //  rsp_type = SD_R4;
        //  break;
        //case 40:
        //  rsp_type = SD_R5;
        //  break;
        default:
            rsp_type = SD_R0;
            break;
    }
    return rsp_type;
}

static int romcr_SendCMDGetRSP_Cmd(UINT8 cmd_idx,
                                   UINT32 sd_arg,
                                   UINT8 rsp_para,
                                   UINT32 *rsp)
{
    UINT8 rsp_len;
    int err;
    mmcinfo("romcr_SendCMDGetRSP_Cmd\n");
    rsp_len = romcr_get_rsp_len(rsp_para);

    mmcinfo("cmd_idx=%u\n"
           "sd_arg=0x%08x; rsp_para=0x%x\n",
            cmd_idx,sd_arg,rsp_para);

    cr_writel(0x40| cmd_idx,        SD_CMD0);
    cr_writel(sd_arg>>24,           SD_CMD1);
    cr_writel(sd_arg>>16,           SD_CMD2);
    cr_writel(sd_arg>>8,            SD_CMD3);
    cr_writel(sd_arg,               SD_CMD4);
    cr_writel(rsp_para,             SD_CONFIGURE2);

    err = romcr_wait_opt_end(SD_SENDCMDGETRSP,R_W_CMD);

    if(err == RTK_SUCC){
        romcr_read_rsp(rsp, rsp_len);
    }else{
        /*
        if error happend,reset Host and card
        magellan maybe need new flow
        */
        err = -RTK_FAIL;
    }

    return err;
}

static int romcr_wait_status(UINT8 state)
{
    UINT32 rom_resp[4];
    UINT32 timeend;
    int rom_err = 0;
    mmcinfo("romcr_wait_status\n");
    timeend = 150;

    while(timeend--)
    {
        rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SEND_STATUS,
                                       emmc_card.rca << RCA_SHIFTER,
                                       SD_R1|CRC16_CAL_DIS,
                                       rom_resp);

        if(rom_err){
            //prints("wait %s fail\n",state_tlb[state]);
            break;
        }else{
            UINT8 cur_state = R1_CURRENT_STATE(rom_resp[0]);
            //prints("cur_state=%s\n",state_tlb[cur_state]);
            rom_err = -1;
            if(cur_state == state){
                if(rom_resp[0] & R1_READY_FOR_DATA){
                    rom_err = 0;
                    break;
                }
            }
        }
        wait_loop(2000);
    }

    return rom_err;
}

static int romcr_send_status(UINT8* state)
{
    UINT32 rom_resp[4];
    int rom_err = 0;
    mmcinfo("romcr_send_status\n");
    rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SEND_STATUS,
                                   emmc_card.rca << RCA_SHIFTER,
                                   SD_R1|CRC16_CAL_DIS,
                                   rom_resp);
    if(rom_err){
        //prints("MMC_SEND_STATUS fail\n");
    }else{
        UINT8 cur_state = R1_CURRENT_STATE(rom_resp[0]);
        *state = cur_state;
        //prints("cur_state=%s\n",state_tlb[cur_state]);

    }

    return rom_err;
}

static int romcr_chk_status(UINT8 state)
{
    int err=0;
    mmcinfo("rtksd_chk_status\n");
    romcr_send_status(&state);

    if(state != STATE_TRAN){
/*
        if(state == STATE_DATA || state == STATE_RCV){
            if(cmd_idx != 17 && cmd_idx != 24){
                rtksd_stop_transmission(host->card);
            }
        }
*/
        err = romcr_wait_status(STATE_TRAN);
    }

    return err;

}

static int romcr_Stream_Cmd(UINT16 cmdcode,struct sd_cmd_pkt *cmd_info)
{
    UINT8 cmd_idx       =   cmd_info->cmd->opcode;
    UINT32 sd_arg       =   cmd_info->cmd->arg;
    UINT32 *rsp         =   cmd_info->cmd->resp;
    UINT8 rsp_para      =   cmd_info->rsp_para;
    int rsp_len         =   cmd_info->rsp_len;
    UINT16 byte_count   =   cmd_info->byte_count;
    UINT32 block_count  =   cmd_info->block_count;
    void *data          =   cmd_info->dma_buffer;
    int err;

    mmcinfo("romcr_Stream_Cmd => cmdcode=0x%x\n",cmdcode);
    mmcinfo("2.cmd_info->flags=0x%x\n",cmd_info->flags);

    /* for SD_NORMALWRITE/SD_NORMALREAD can't check CRC16 issue */
    if((cmdcode==SD_NORMALWRITE) || (cmdcode==SD_NORMALREAD))
    {
        byte_count = 512;
    }

    /* clear data at sram and trun-off boot mode */
    cr_writel(cr_readl(CP_CTRL) & ~BOOT_FROM_CR,  CP_CTRL);

    if(mmc_data_dir(cmd_info) & MMC_DATA_RAM){
        mmcinfo("SRAM mode\n");
        if(block_count == 1 ){
            /* enable boot mode */
           cr_writel(cr_readl(CP_CTRL)|BOOT_FROM_CR,  CP_CTRL);
            sync();
        }else{

            mmcinfo("SRAM mode support single sector only\n");
            err = -RTK_FAIL;
            goto err_out;
        }

    }else if(mmc_data_dir(cmd_info) & MMC_DATA_WRITE){
        mmcinfo("data write to card\n");
        cr_writel((unsigned int) data, CR_DMA_OUT_ADDR);

    }else{
        mmcinfo("data read from card\n");
        cr_writel((unsigned int) data, CR_DMA_IN_ADDR);
    }

    mmcinfo("cmd_idx=%u\n"
           "sd_arg=0x%08x; rsp_para=0x%x\n"
           "byte_count=0x%x; block_count=0x%x; buf=0x%p\n",
            cmd_idx,sd_arg,rsp_para,byte_count,block_count,data);

    cr_writel(0x40| cmd_idx,    SD_CMD0);           //0x10
    cr_writel(sd_arg>>24,       SD_CMD1);           //0x14
    cr_writel(sd_arg>>16,       SD_CMD2);           //0x18
    cr_writel(sd_arg>>8,        SD_CMD3);           //0x1C
    cr_writel(sd_arg,           SD_CMD4);           //0x20
    cr_writel(rsp_para,         SD_CONFIGURE2);     //0x0C
    cr_writel(byte_count,       SD_BYTE_CNT_L);     //0x24
    cr_writel(byte_count>>8,    SD_BYTE_CNT_H);     //0x28
    cr_writel(block_count,      SD_BLOCK_CNT_L);    //0x2C
    cr_writel(block_count>>8,   SD_BLOCK_CNT_H);    //0x30

    err = romcr_wait_opt_end(cmdcode,R_W_CMD);

    if(err == RTK_SUCC){
        if(cmdcode==SD_AUTOREAD1 || cmdcode==SD_AUTOWRITE1){
            mmcinfo("SD_AUTOREAD1/SD_AUTOWRITE1\n");
        }else if(cmdcode==SD_AUTOREAD2 || cmdcode==SD_AUTOWRITE2 ){
            mmcinfo("SD_AUTOREAD2/SD_AUTOWRITE2\n");
        }else{
            mmcinfo("SD_NORMALREAD/SD_NORMALWRITE\n");
            romcr_read_rsp(rsp, rsp_len);
        }

        if( block_count == 1 &&
            mmc_data_dir(cmd_info) & MMC_DATA_RAM)
        {
            UINT8 i;
            UINT32 * sram_buf = data;

#ifdef SHOW_SRAM_REG
            for(i=0;i<16;i++){
                printf("[%03x]=0x%08x [%03x]=0x%08x [%03x]=0x%08x [%03x]=0x%08x\n"
                       "[%03x]=0x%08x [%03x]=0x%08x [%03x]=0x%08x [%03x]=0x%08x\n",
                        (i*32)+  0,cr_readl(CR_SRAM_BASE+(i*32)+ 0),
                        (i*32)+  4,cr_readl(CR_SRAM_BASE+(i*32)+ 4),
                        (i*32)+  8,cr_readl(CR_SRAM_BASE+(i*32)+ 8),
                        (i*32)+ 12,cr_readl(CR_SRAM_BASE+(i*32)+12),
                        (i*32)+ 16,cr_readl(CR_SRAM_BASE+(i*32)+16),
                        (i*32)+ 20,cr_readl(CR_SRAM_BASE+(i*32)+20),
                        (i*32)+ 24,cr_readl(CR_SRAM_BASE+(i*32)+24),
                        (i*32)+ 28,cr_readl(CR_SRAM_BASE+(i*32)+28) );
            }
#endif

            if(sram_buf){
                UINT32 fifo_tmp;

                mmcinfo("SRAM copy dtat\n");
                for(i=0;i<128;i++){
                    fifo_tmp = cr_readl(CR_SRAM_BASE);
                    sram_buf[i]= fifo_tmp;
                }
            }
            //cr_writel(0,  CR_BOOT_CTRL);    //trun-off boot mode, data still keep in SRAM
        }

    }

err_out:
    return err;
}

/******************************************************
 UINT32 tar_addr = target accress address
 UINT32 blk_cnt  = block count you want.
 UINT8 acc_mod   = MMC_DATA_RAM     <== acress form SRAM
                   MMC_DATA_WRITE   <== write data to MMC
                   MMC_DATA_READ    <== read data from MMC
 UINT8 *dma_buffer = address point of data buffer
 ******************************************************/
static int romcr_Stream(UINT32 tar_addr,
                        UINT32 blk_cnt,
                        UINT8 acc_mod,
                        UINT8 *dma_buffer)
{
    struct sd_cmd_pkt cmd_info;
    struct mmc_command  cmd;
    UINT16 cmdcode;
    int err = -1;
    UINT8 rsp_type;
    mmcinfo("romcr_Stream\n");
    mmcinfo("tar_addr=0x%x; blk_cnt=0x%x; acc_mod=0x%x; dma_buffer=0x%p\n",
            tar_addr,blk_cnt,acc_mod,dma_buffer);

    cmd_info.cmd = &cmd;
    cmd.arg      = tar_addr;

    if(acc_mod & MMC_DATA_WRITE ){
        cmdcode = SD_AUTOWRITE2;
        cmd.opcode = 24;
    }else{
        cmdcode = SD_AUTOREAD2;
        cmd.opcode = 17;
    }

    /* multi sector accress opcode */
    if(blk_cnt > 1){
        cmd.opcode++;
        cmdcode -= 1;
    }

    rsp_type = get_rsp_type(&cmd);

    cmd_info.rsp_para       = rsp_type;
    cmd_info.rsp_len        = romcr_get_rsp_len(rsp_type);
    cmd_info.byte_count     = 0x200;
    cmd_info.block_count    = blk_cnt;
    cmd_info.dma_buffer     = dma_buffer;
    cmd_info.flags          = acc_mod;

    err = romcr_Stream_Cmd(cmdcode,&cmd_info);

    if(err){
        mmcinfo("2. romcr_Stream\n");
    }

    return err;
}

void ini_cmd_pkt(struct sd_cmd_pkt * pkt){
    pkt->cmd            = 0;
    pkt->dma_buffer     = 0;
    pkt->byte_count     = 0;
    pkt->block_count    = 0;
    pkt->flags          = 0;
    pkt->rsp_para       = 0;
    pkt->rsp_len        = 0;
    pkt->timeout        = 0;
    pkt->resp_buf       = 0;
    pkt->err_case       = 0;
}

int endian_chg(UINT32 * addr ,UINT32 len )
{
    UINT32 i;
    UINT32 * ptr32;
    UINT32 tmp1;

    if((((UINT32)addr) & 0x3) | (len & 0x3))
        return -1;

    for(i=0;i<len/4;i++){
        ptr32 = addr+i;
        tmp1 = *ptr32;
        *ptr32 = (tmp1 & 0xff000000)>>24|
                 (tmp1 & 0x00ff0000)>>8|
                 (tmp1 & 0x0000ff00)<<8|
                 (tmp1 & 0x000000ff)<<24;

    }
    return 0;
}

#define ARRY_BUFF
static int mmc_read_ext_csd(e_device_type *card){
    struct sd_cmd_pkt cmd_info;
    struct mmc_command  cmd;
    UINT16 cmdcode;
    UINT8 rsp_type;
    int err;
    int tryloop;

#ifdef ARRY_BUFF
    UINT8 ext_csd[0x200];
#else
    UINT8 *ext_csd;
    ext_csd = (UINT8 *) simple_malloc(0x200);
    //ext_csd = (UINT8 *)0xa2000000;
#endif

    tryloop = 3;
RETRY:
    mmcinfo("mmc_read_ext_csd\n");
    //memset(ext_csd, 0, 0x200);
    //memset(&cmd_info, 0, sizeof(cmd_info));
    //memset(&cmd, 0, sizeof(cmd));

    cmd_info.cmd  = &cmd;
    cmd.arg       = 0;
    cmd.opcode    = MMC_SEND_EXT_CSD;

    rsp_type = get_rsp_type(&cmd);

    mmcinfo("ext_csd at 0x%p\n",ext_csd);
    cmd_info.rsp_para       = rsp_type;
    cmd_info.rsp_len        = romcr_get_rsp_len(rsp_type);
    cmd_info.byte_count     = 0x200;
    cmd_info.block_count    = 1;
    cmd_info.dma_buffer     = ext_csd;
    cmd_info.flags          = MMC_SRAM_READ;
    //cmd_info.flags          = MMC_DATA_READ;
    cmdcode = SD_NORMALREAD;

    err = romcr_Stream_Cmd(cmdcode,&cmd_info);

    if(err){
        mmcinfo("unable to read EXT_CSD ");

        if(tryloop){
            tryloop-- ;
            goto RETRY;
        }

    }else{
        endian_chg((UINT32*)ext_csd ,0x200 );

#ifdef SHOW_EXT_CSD
        printf("SHOW EXT CSD\n");
        printf("[504]S_CMD_SET = 0x%02x\n",             ext_csd[504]);
        printf("[503]HPI_FEATURES = 0x%02x\n",          ext_csd[503]);
        printf("[502]BKOPS_SUPPORT = 0x%02x\n",         ext_csd[502]);
        printf("[246]BKOPS_STATUS = 0x%02x\n",          ext_csd[246]);
        printf("[245-242]CORRECTLY_PRG_SECTORS_NUM = 0x%02x%02x%02x%02x\n",
                ext_csd[245],ext_csd[244],ext_csd[243],ext_csd[242]);
        printf("[241]INI_TIMEOUT_AP = 0x%02x\n",        ext_csd[241]);
        printf("[239]PWR_CL_DDR_52_360 = 0x%02x\n",     ext_csd[239]);
        printf("[238]PWR_CL_DDR_52_195 = 0x%02x\n",     ext_csd[238]);
        printf("[235]MIN_PERF_DDR_W_8_52 = 0x%02x\n",   ext_csd[235]);
        printf("[234]MIN_PERF_DDR_R_8_52 = 0x%02x\n",   ext_csd[234]);
        printf("[232]TRIM_MULT = 0x%02x\n",             ext_csd[232]);
        printf("[231]SEC_FEATURE_SUPPORT = 0x%02x\n",   ext_csd[231]);
        printf("[230]SEC_ERASE_MULTI = 0x%02x\n",       ext_csd[230]);
        printf("[229]SEC_TRIM_MULT = 0x%02x\n",         ext_csd[229]);
        printf("[228]BOOT_INFO = 0x%02x\n",             ext_csd[228]);
        printf("[226]BOOT_SIZE_MULTI = 0x%02x\n",       ext_csd[226]);
        printf("[225]ACC_SIZE = 0x%02x\n",              ext_csd[225]);
        printf("[224]HC_ERASE_GRP_SIZE = 0x%02x\n",     ext_csd[224]);
        printf("[223]ERASE_TIMEOUT_MULT = 0x%02x\n",    ext_csd[223]);
        printf("[222]REL_WR_SEC_C = 0x%02x\n",          ext_csd[222]);
        printf("[221]HC_WP_GRP_SIZE = 0x%02x\n",        ext_csd[221]);
        printf("[220]S_C_VCC = 0x%02x\n",               ext_csd[220]);
        printf("[219]S_C_VCCQ = 0x%02x\n",              ext_csd[219]);
        printf("[217]S_A_TIMEOUT = 0x%02x\n",           ext_csd[217]);
        printf("[215-212]SEC_COUNT = 0x%02x%02x%02x%02x\n",
                ext_csd[215],ext_csd[214],ext_csd[213],ext_csd[212]);
        printf("[210]MIN_PERF_W_8_52 = 0x%02x\n",       ext_csd[210]);
        printf("[209]MIN_PERF_R_8_52 = 0x%02x\n",       ext_csd[209]);
        printf("[208]MIN_PERF_W_8_26_4_52 = 0x%02x\n",  ext_csd[208]);
        printf("[207]MIN_PERF_R_8_26_4_52 = 0x%02x\n",  ext_csd[207]);
        printf("[206]MIN_PERF_W_4_26 = 0x%02x\n",       ext_csd[206]);
        printf("[205]MIN_PERF_R_4_26 = 0x%02x\n",       ext_csd[205]);
        printf("[203]PWR_CL_26_360 = 0x%02x\n",         ext_csd[203]);
        printf("[202]PWR_CL_52_360 = 0x%02x\n",         ext_csd[202]);
        printf("[201]PWR_CL_26_195 = 0x%02x\n",         ext_csd[201]);
        printf("[200]PWR_CL_52_195 = 0x%02x\n",         ext_csd[200]);
        printf("[199]PARTITION_SWITCH_TIME = 0x%02x\n", ext_csd[199]);
        printf("[198]OUT_OF_INTERRUPT_TIME = 0x%02x\n", ext_csd[198]);
        printf("[196]CARD_TYPE = 0x%02x\n",             ext_csd[196]);
        printf("[194]CSD_STRUCTURE = 0x%02x\n",         ext_csd[194]);
        printf("[192]EXT_CSD_REV = 0x%02x\n",           ext_csd[192]);
        printf("[191]CMD_SET = 0x%02x\n",               ext_csd[191]);
        printf("[189]CMD_SET_REV = 0x%02x\n",           ext_csd[189]);
        printf("[187]POWER_CLASS = 0x%02x\n",           ext_csd[187]);
        printf("[185]HS_TIMING = 0x%02x\n",             ext_csd[185]);
        printf("[183]BUS_WIDTH = 0x%02x\n",             ext_csd[183]);
        printf("[181]ERASED_MEM_CONT = 0x%02x\n",       ext_csd[181]);
        printf("[179]PARTITION_CONFIG = 0x%02x\n",      ext_csd[179]);
        printf("[178]BOOT_CONFIG_PROT = 0x%02x\n",      ext_csd[178]);
        printf("[177]BOOT_BUS_WIDTH = 0x%02x\n",        ext_csd[177]);
        printf("[175]ERASE_GROUP_DEF = 0x%02x\n",       ext_csd[175]);
        printf("[173]BOOT_WP = 0x%02x\n",               ext_csd[173]);
        printf("[171]USER_WP = 0x%02x\n",               ext_csd[171]);
        printf("[169]FW_CONFIG = 0x%02x\n",             ext_csd[169]);
        printf("[168]RPMB_SIZE_MULT = 0x%02x\n",        ext_csd[168]);
        printf("[167]WR_REL_SET = 0x%02x\n",            ext_csd[167]);
        printf("[166]WR_REL_PARAM = 0x%02x\n",          ext_csd[166]);
        printf("[164]BKOPS_START = 0x%02x\n",           ext_csd[164]);
        printf("[163]BKOPS_EN = 0x%02x\n",              ext_csd[163]);
        printf("[162]RST_n_FUNCTION = 0x%02x\n",        ext_csd[162]);
        printf("[161]HPI_MGMT = 0x%02x\n",              ext_csd[161]);
        printf("[160]PARTITIONING_SUPPORT = 0x%02x\n",  ext_csd[160]);
        printf("[159-157]MAX_ENH_SIZE_MULT = 0x%02x%02x%02x\n",
                ext_csd[159],ext_csd[158],ext_csd[157]);
        printf("[156]PARTITIONS_ATTRIBUTE = 0x%02x\n",  ext_csd[156]);
        printf("[155]PARTITION_SETTING_COMPLETED = 0x%02x\n",  ext_csd[155]);
        printf("GP_SIZE_MULT:\n");
        printf(" [143]-GP_SIZE_MULT_1_0 = 0x%02x\n",     ext_csd[143]);
        printf(" [144]-GP_SIZE_MULT_1_1 = 0x%02x\n",     ext_csd[144]);
        printf(" [145]-GP_SIZE_MULT_1_2 = 0x%02x\n",     ext_csd[145]);
        printf(" [146]-GP_SIZE_MULT_2_0 = 0x%02x\n",     ext_csd[146]);
        printf(" [147]-GP_SIZE_MULT_2_1 = 0x%02x\n",     ext_csd[147]);
        printf(" [148]-GP_SIZE_MULT_2_2 = 0x%02x\n",     ext_csd[148]);
        printf(" [149]-GP_SIZE_MULT_3_0 = 0x%02x\n",     ext_csd[149]);
        printf(" [150]-GP_SIZE_MULT_3_1 = 0x%02x\n",     ext_csd[150]);
        printf(" [151]-GP_SIZE_MULT_3_2 = 0x%02x\n",     ext_csd[151]);
        printf(" [152]-GP_SIZE_MULT_4_0 = 0x%02x\n",     ext_csd[152]);
        printf(" [153]-GP_SIZE_MULT_4_1 = 0x%02x\n",     ext_csd[153]);
        printf(" [154]-GP_SIZE_MULT_4_2 = 0x%02x\n",     ext_csd[154]);
        printf("[142-140]ENH_SIZE_MULT = 0x%02x%02x%02x\n",
                ext_csd[142],ext_csd[142],ext_csd[140]);
        printf("[139-136]ENH_START_ADDR = 0x%02x%02x%02x%02x\n",
                ext_csd[139],ext_csd[138],ext_csd[137],ext_csd[136]);
        printf("[134]SEC_BAD_BLK_MGMNT = 0x%02x\n",     ext_csd[134]);
#endif

        card->ext_csd.rev = ext_csd[EXT_CSD_REV];

        if (card->ext_csd.rev > 5) {
            mmcinfo("unrecognised EXT_CSD structure version %d\n",
                    card->ext_csd.rev);

            /* mark it! no matter what happened, try to turn on system */
            //err = -1;
            //goto err_out;
        }

        if (card->ext_csd.rev >= 2) {
            card->ext_csd.sectors =
                ext_csd[EXT_CSD_SEC_CNT + 0] <<  0 |
                ext_csd[EXT_CSD_SEC_CNT + 1] <<  8 |
                ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
                ext_csd[EXT_CSD_SEC_CNT + 3] << 24;
            if (card->ext_csd.sectors){
                mmc_card_set_blockaddr(card);
            }
        }

        switch (ext_csd[EXT_CSD_CARD_TYPE] & EXT_CSD_CARD_TYPE_MASK) {
        case EXT_CSD_CARD_TYPE_52 | EXT_CSD_CARD_TYPE_26:
            card->ext_csd.hs_max_dtr = 52000000;
            break;
        case EXT_CSD_CARD_TYPE_26:
            card->ext_csd.hs_max_dtr = 26000000;
            break;
        default:
            /* MMC v4 spec says this cannot happen */
            mmcinfo("card is mmc v4 but doesn't "
                "support any high-speed modes.\n");
        }

        if (card->ext_csd.rev >= 3) {
            UINT8 sa_shift = ext_csd[EXT_CSD_S_A_TIMEOUT];

            /* Sleep / awake timeout in 100ns units */
            if (sa_shift > 0 && sa_shift <= 0x17){

                card->ext_csd.sa_timeout =
                        1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
            }
        }
    }

//err_out:
    mmcinfo("mmc_read_ext_csd ==> err=%d\n",err);
    return err;

}

static int mmc_send_csd(e_device_type *card){
    int rom_err;
    mmcinfo("mmc_send_csd\n");

    /* Read CSD ==> CMD9 */
    rom_err = 0;
    rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SEND_CSD,
                                card->rca << RCA_SHIFTER,
                                SD_R2,
                                card->raw_csd);
    return rom_err;

}

static int mmc_decode_csd(e_device_type *card)
{
    struct mmc_csd *csd = &card->csd;
    unsigned int e, m, csd_struct;
    UINT32 *resp = card->raw_csd;
    int err = 0;
    mmcinfo("mmc_decode_csd\n");

    /*
     * We only understand CSD structure v1.1 and v1.2.
     * v1.2 has extra information in bits 15, 11 and 10.
     * We also support eMMC v4.4 & v4.41.
     */
    csd_struct = UNSTUFF_BITS(resp, 126, 2);

    if(csd_struct == 3){
        mmcinfo("eMMC device detected.\n");
    }else{
        err = -1;
        goto err_out;
    }

    csd->mmca_vsn       = UNSTUFF_BITS(resp, 122, 4);
    m = UNSTUFF_BITS(resp, 115, 4);
    e = UNSTUFF_BITS(resp, 112, 3);
    csd->tacc_ns        = (tacc_exp[e] * tacc_mant[m] + 9) / 10;
    csd->tacc_clks      = UNSTUFF_BITS(resp, 104, 8) * 100;

    m = UNSTUFF_BITS(resp, 99, 4);
    e = UNSTUFF_BITS(resp, 96, 3);
    csd->max_dtr        = tran_exp[e] * tran_mant[m];
    csd->cmdclass       = UNSTUFF_BITS(resp, 84, 12);

    e = UNSTUFF_BITS(resp, 47, 3);
    m = UNSTUFF_BITS(resp, 62, 12);
    csd->capacity       = (1 + m) << (e + 2);

    csd->read_blkbits   = UNSTUFF_BITS(resp, 80, 4);
    csd->read_partial   = UNSTUFF_BITS(resp, 79, 1);
    csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
    csd->read_misalign  = UNSTUFF_BITS(resp, 77, 1);
    csd->r2w_factor     = UNSTUFF_BITS(resp, 26, 3);
    csd->write_blkbits  = UNSTUFF_BITS(resp, 22, 4);
    csd->write_partial  = UNSTUFF_BITS(resp, 21, 1);

    mmcinfo("capacity :%u\n",csd->capacity);
    mmcinfo("blkbits :%u\n" ,csd->read_blkbits);
err_out:
    return err;
}

static int mmc_decode_cid(e_device_type *card)
{
    UINT32 *resp = card->raw_cid;
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

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_erase_e(void  *dev,
               unsigned int* dest,
               unsigned int   rem_size)
{
    return 0;
}

#ifdef FAKE_EMMC_API
int do_write_e(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset)
{
    return 0;
}

int do_read_e(void *dev,
               unsigned int*  src,
               unsigned char* dest,
               unsigned int   rem_size,
               unsigned int   signature)
{
    return 0;
}

int do_identify_e(void **dev)
{
    return 0;
}

int do_init_e(void *dev)
{
    return 0;
}

#else
/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :    dest      = target address that want to write to card.(block base)
 *                  array_ptr = address of pool of write data source.
 *                  rem_size = total size you want to get.(bytes)
 *                  signature & page_offset <== NO USE
 *  ------------
 *  Return values :
 ************************************************************************/
#define MAX_BLOCK_CNT 0x800
int do_write_e(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset)
{
    UINT32 tar_addr;
    UINT32 blk_cont;

    UINT32 tmp_tar_addr;
    unsigned char* tmp_buf_addr;
    UINT32 tmp_blk_cont;
    UINT32 res_blk_cont;

    int err = 0;

    e_device_type *card = (e_device_type *)dev;
    mmcinfo("do_write_e\n");

    //romcr_wait_status(STATE_TRAN);
    mmcinfo("1. do_write_e err=%d\n",err);

    mmcinfo("array_ptr=0x%p; dest=0x%x; rem_size=0x%x\n",
            array_ptr,*dest,rem_size);

    if(!mmc_card_blockaddr(card)){
        mmcinfo("byte addressing card\n");
        tar_addr = *dest<<9;
    }else{
        tar_addr = *dest;
    }
    blk_cont = rem_size>>9;
    if(rem_size & 0x1ff)
        blk_cont+=1;


    tmp_tar_addr = tar_addr;
    res_blk_cont = blk_cont;
    tmp_buf_addr = array_ptr;

    mmcinfo("tmp_tar_addr=0x%x tar_addr=0x%x\n",tmp_tar_addr,tar_addr);
    mmcinfo("res_blk_cont=0x%x blk_cont=0x%x\n",res_blk_cont,blk_cont);
    mmcinfo("tmp_buf_addr=0x%p array_ptr=0x%x\n",tmp_buf_addr,array_ptr);
    while(res_blk_cont){

        if(res_blk_cont > MAX_BLOCK_CNT)
            tmp_blk_cont = MAX_BLOCK_CNT;
        else
            tmp_blk_cont = res_blk_cont;

        mmcinfo("tmp_blk_cont=%d\n",tmp_blk_cont);

        romcr_wait_status(STATE_TRAN);
    	//sys_dcache_flush((unsigned long) array_ptr,(unsigned long) (blk_cont << 9));
        //err = romcr_Stream( tar_addr,blk_cont,MMC_DATA_WRITE,array_ptr);
        sys_dcache_flush((unsigned long) tmp_buf_addr,
                         (unsigned long) (tmp_blk_cont << 9));
        err = romcr_Stream( tmp_tar_addr,tmp_blk_cont,MMC_DATA_WRITE,tmp_buf_addr);
        if(err){
            mmcinfo("2. do_write_e err=%d\n",err);
            break;
        }
        tmp_tar_addr += tmp_blk_cont;
        res_blk_cont -= tmp_blk_cont;
        tmp_buf_addr += (tmp_blk_cont<<9);

        mmcinfo("tmp_tar_addr=%d\n",tmp_tar_addr);
        mmcinfo("res_blk_cont=%d\n",res_blk_cont);
        mmcinfo("tmp_buf_addr=%p\n",tmp_buf_addr);
        romcr_wait_status(STATE_TRAN);
    }
    mmcinfo("3. do_write_e err=%d\n",err);
    return err;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :    src      = target address that want to read from card.
 *                  dest     = pool of read data from card.
 *                  rem_size = total size you want to get.
 *                  signature <== NO USE
 *  ------------
 *  Return values :
 ************************************************************************/
int do_read_e(void *dev,
               unsigned int*  src,
               unsigned char* dest,
               unsigned int   rem_size,
               unsigned int   signature)
{
    UINT32 tar_addr;
    UINT32 blk_cont;
    int err;

    UINT32 tmp_tar_addr;
    unsigned char* tmp_buf_addr;
    UINT32 tmp_blk_cont;
    UINT32 res_blk_cont;


    e_device_type *card = (e_device_type *)dev;
    mmcinfo("do_read_e\n");
    mmcinfo("src=0x%p; dest=0x%p; rem_size=0x%x\n",
            src,dest,rem_size);

    if(!mmc_card_blockaddr(card)){
        mmcinfo("byte addressing card\n");
        tar_addr = *src<<9;
    }else{
        tar_addr = *src;
    }
    blk_cont = rem_size>>9;
    if(rem_size & 0x1ff)
        blk_cont+=1;

    tmp_tar_addr = tar_addr;
    res_blk_cont = blk_cont;
    tmp_buf_addr = dest;
    err = 0;
    while(res_blk_cont){
        if(res_blk_cont > MAX_BLOCK_CNT)
            tmp_blk_cont = MAX_BLOCK_CNT;
        else
            tmp_blk_cont = res_blk_cont;

    	//sys_dcache_flush_invalidate_range((unsigned long) dest,(unsigned long) (dest + (blk_cont << 9)));
    	//err = romcr_Stream( tar_addr,blk_cont,MMC_DATA_READ,dest);
    	sys_dcache_flush_invalidate_range((unsigned long) tmp_buf_addr,
    	                    (unsigned long) (tmp_buf_addr + (tmp_blk_cont << 9)));
    	err = romcr_Stream( tmp_tar_addr,tmp_blk_cont,MMC_DATA_READ,tmp_buf_addr);
	    if(err)
	        break;

        tmp_tar_addr += tmp_blk_cont;
        res_blk_cont -= tmp_blk_cont;
        tmp_buf_addr += (tmp_blk_cont<<9);

        mmcinfo("tmp_tar_addr=%d\n",tmp_tar_addr);
        mmcinfo("res_blk_cont=%d\n",res_blk_cont);
        mmcinfo("tmp_buf_addr=%p\n",tmp_buf_addr);
    }

    return err;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_identify_e(void **dev)
{
    int rom_err;
    int i;
    int rty_cnt;
    int idle_cnt;
    UINT32 timeend;
    UINT32 rom_resp[4];
    UINT32 reginfo;

	print_uart("\nflash id [0x");
	//print_val(chipid,4);
	print_uart("]\n");

    /* set emmc pin mux */
//    REG32(0x18000914) = (REG32(0x18000914) & 0x000000ff) |0x10000000;       // EMMC_Source control reg(176/256 QFP)
//    REG32(0x18060248) = (REG32(0x18060248) & 0x00ffffff) |0x08000000;       // EMMC_CLK st_gpio_12
//    REG32(0x18000844) = (REG32(0x18000844) & 0xffffc000) |0x00000400;       // EMMC_CMD gpio_56
//    REG32(0x18000834) = (REG32(0x18000834) & 0xffffc000) |0x00000400;       // EMMC_DAT0 gpio_44
//    REG32(0x18000838) = (REG32(0x18000838) & 0x00000000) |0x10080400;       // EMMC_DAT1/2/3 gpio_45/46/47
//    REG32(0x1800083c) = (REG32(0x1800083c) & 0x00000000) |0x10080400;       // EMMC_DAT4/5/6 gpio_48/49/50
//    REG32(0x18000840) = (REG32(0x18000840) & 0x007fffff) |0x10000000;       // EMMC_DAT7 gpio_51
//    REG32(0x180008F8) = (REG32(0x180008F8) & 0xffc1ffff) |0x003e0000;

    mmccr_reset_cr_state(0);

    *dev = &emmc_card;
    printf("eMMC bootcode burning tool 2014/01/20 11:00\n");
    printf("(build at %s %s )\n",__DATE__,__TIME__);

    rty_cnt = 0;
    emmc_card.rca = 1;

    /* card reset holdinig */
    /* card power enable */
    /* host rest */
    /* card reset release */
    romcr_hold_int_all();
    romcr_clr_int_sta();


//make for FPGA    romcr_set_clk(CARD_SWITCHCLOCK_30MHZ);
    romcr_set_div(CLOCK_DIV_128);

    /* CMD0 ==> Idle state */
    idle_cnt = 3;
RE_IDLE:
    for(i=0;i<idle_cnt;i++){
        wait_loop(1000);
        romcr_SendCMDGetRSP_Cmd(MMC_GO_IDLE_STATE,
                                0x00000000,
                                SD_R0,
                                rom_resp);
    }

    /* Idle state ==> CMD1 */
    mmcinfo("cmd1\n");
    rom_err = 0;
    timeend = 100;
    while (timeend--){
        if(timeend == 0){
            rom_err = -1;
            goto err_out;
        }

        wait_loop(5000);
        rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SEND_OP_COND,
                                ROM_EMMC_VDD|EMMC_SCT_ACC,
                                SD_R3,
                                rom_resp);

        if(rom_err || (rom_resp[0] == 0xffffffff)){
            if(rty_cnt>3){
                rom_err = -1;
                break;
            }

            rty_cnt++;
            idle_cnt = rty_cnt*2;
            goto RE_IDLE;
        }

        if (rom_resp[0] & MMC_CARD_BUSY){
            break;
        }

    }

    /* Ready state ==> CMD2 */
    mmcinfo("cmd2\n");
    wait_loop(100);
    rom_err = 0;
    rom_err = romcr_SendCMDGetRSP_Cmd(MMC_ALL_SEND_CID,
                                0x00000000,
                                SD_R2,
                                emmc_card.raw_cid);
    if(rom_err)
        goto err_out;

    /* Indentification state ==> CMD3 */
    mmcinfo("cmd3\n");
    wait_loop(100);
    rom_err = 0;
    rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SET_RELATIVE_ADDR,
                                emmc_card.rca << RCA_SHIFTER,
                                SD_R1|CRC16_CAL_DIS,
                                rom_resp);
    if(rom_err)
        goto err_out;


    /* Send CSD  ==> CMD9 */
    wait_loop(100);
    rom_err = mmc_send_csd(&emmc_card);
    if(rom_err)
        goto err_out;

    /* change divider to non */
    romcr_set_div(CLOCK_DIV_NON);

    /* Standy-by state ==> CMD7 */
    mmcinfo("cmd7\n");
    wait_loop(100);
    rom_err = 0;
    rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SELECT_CARD,
                                emmc_card.rca << RCA_SHIFTER,
                                SD_R1b|CRC16_CAL_DIS,
                                rom_resp);

    if(rom_err){
        mmcinfo("cmd7 error\n");
        goto err_out;
    }

    rom_err = R1_CURRENT_STATE(rom_resp[0]);
    if(rom_resp[0] & R1_READY_FOR_DATA){
        wait_loop(100);
    }else{
        wait_loop(3000);
    }

    /* speed up to 40MHz */
    //mmcinfo("set clock 40MHz\n");
    //romcr_set_clk(CARD_SWITCHCLOCK_40MHZ);

    /* Read ext CSD ==> cmd8 */
    //wait_loop(100);
    mmcinfo("cmd8\n");
    rom_err = mmc_read_ext_csd(&emmc_card);

    if(rom_err){
        goto err_out;
    }

    /* change to 4bits width ==> CMD6 */
    mmcinfo("cmd6\n");
    mmcinfo("change to 4bits\n");
    if(1){
        UINT32 arg;
        wait_loop(100);
        rom_err = 0;
        arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24)|
              (EXT_CSD_BUS_WIDTH          << 16)|
              (EXT_CSD_BUS_WIDTH_4        << 8)|
              EXT_CSD_CMD_SET_NORMAL;

        rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SWITCH,
                                    arg,
                                    SD_R1b|CRC16_CAL_DIS,
                                    rom_resp);
        if(rom_err)
            goto err_out;

        /* To wait status change complete */
        rom_err = 0;
        timeend = 100;
        do {
            wait_loop(1000);
            rom_err = romcr_SendCMDGetRSP_Cmd(MMC_SEND_STATUS,
                                              emmc_card.rca << RCA_SHIFTER,
                                              SD_R1|CRC16_CAL_DIS,
                                              rom_resp);

            if(rom_err)
                goto err_out;

            timeend--;

        }while((R1_CURRENT_STATE(rom_resp[0]) == STATE_PRG) && timeend);

        if ((rom_resp[0] & R1_SWITCH_ERROR) ||
            (timeend==0) )
        {
            rom_err = -1;
            goto err_out;
        }else{
            romcr_set_bits(BUS_WIDTH_4);
        }
    }
err_out:
    return rom_err;

}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int do_init_e(void *dev)
{
    //UINT32 *resp;
    int err = 0;

    e_device_type *card = (e_device_type *)dev;
    printf("do_init_e\n");
    /*
     *  decode  CID
     *  get     CSD     : mmc_send_csd(card, card->raw_csd);
     *  decode  CSD
     *  get ext_CSD     : mmc_send_ext_csd(struct mmc_card *card, UINT8 *ext_csd)
     *  decode ext_CSD
     */

#ifdef SHOW_CID
    resp = card->raw_cid;
    printf("SHOW CID:\n");
    printf("Manufacturer ID:%u\n",      UNSTUFF_BITS(resp, 120, 8));
    printf("CARD/BGA:%u\n",             UNSTUFF_BITS(resp, 112, 2));
    printf("OEM/Application ID:%u\n",   UNSTUFF_BITS(resp, 104, 8));
    {
    unsigned char product_name[6];
    product_name[0] = UNSTUFF_BITS(resp, 96, 8);
    product_name[1] = UNSTUFF_BITS(resp, 88, 8);
    product_name[2] = UNSTUFF_BITS(resp, 80, 8);
    product_name[3] = UNSTUFF_BITS(resp, 72, 8);
    product_name[4] = UNSTUFF_BITS(resp, 64, 8);
    product_name[5] = UNSTUFF_BITS(resp, 56, 8);
    printf("Product name:%s\n",product_name);
    printf("product_name[0]:0x%x\n",   product_name[0]);
    printf("product_name[1]:0x%x\n",   product_name[1]);
    printf("product_name[2]:0x%x\n",   product_name[2]);
    printf("product_name[3]:0x%x\n",   product_name[3]);
    printf("product_name[4]:0x%x\n",   product_name[4]);
    printf("product_name[5]:0x%x\n",   product_name[5]);
    }
    printf("Product revison:%u\n",      UNSTUFF_BITS(resp, 48, 8));
    {
    unsigned char product_serial[4];
    product_serial[0]   = UNSTUFF_BITS(resp, 40, 8);
    product_serial[1]   = UNSTUFF_BITS(resp, 32, 8);
    product_serial[2]   = UNSTUFF_BITS(resp, 24, 8);
    product_serial[3]   = UNSTUFF_BITS(resp, 16, 8);
    printf("Product serial number:%s\n",product_serial);
    printf("product_serial[0]:0x%x\n",   product_serial[0]);
    printf("product_serial[1]:0x%x\n",   product_serial[1]);
    printf("product_serial[2]:0x%x\n",   product_serial[2]);
    printf("product_serial[3]:0x%x\n",   product_serial[3]);
    }
    printf("Manufacturer date:%u/%u (month/year)\n",
            UNSTUFF_BITS(resp, 12, 4),
            UNSTUFF_BITS(resp,  8, 4)+1997);
    printf("CRC7:%u\n",                 UNSTUFF_BITS(resp, 1, 7));
#endif

#ifdef SHOW_CSD
    resp = card->raw_csd;
    printf("%s(%u)SHOW CSD\n",__func__,__LINE__);
    printf("CSD_STRUCTURE = %u\n",      UNSTUFF_BITS(resp, 126, 2));
    printf("SPEC_VERS = %u\n",          UNSTUFF_BITS(resp, 122, 4));
    printf("TAAC = %u\n",               UNSTUFF_BITS(resp, 112, 8));
    printf("NSAC = %u\n",               UNSTUFF_BITS(resp, 104, 8));
    printf("TRAN_SPEED = %u\n",         UNSTUFF_BITS(resp,  96, 8));
    printf("CCC = %u\n",                UNSTUFF_BITS(resp,  84,12));
    printf("READ_BL_LEN = %u\n",        UNSTUFF_BITS(resp,  80, 4));
    printf("READ_BL_PARTIAL = %u\n",    UNSTUFF_BITS(resp,  79, 1));
    printf("WRITE_BLK_MISALIGN = %u\n", UNSTUFF_BITS(resp,  78, 1));
    printf("READ_BL_MISALIGN = %u\n",   UNSTUFF_BITS(resp,  77, 1));
    printf("DSR_IMP = %u\n",            UNSTUFF_BITS(resp,  76, 1));
    printf("C_SIZE = %u\n",             UNSTUFF_BITS(resp,  62,12));
    printf("VDD_R_CURR_MIN = %u\n",     UNSTUFF_BITS(resp,  59, 3));
    printf("VDD_W_CURR_MIN = %u\n",     UNSTUFF_BITS(resp,  53, 3));
    printf("VDD_R_CURR_MAX = %u\n",     UNSTUFF_BITS(resp,  56, 3));
    printf("VDD_W_CURR_MAX = %u\n",     UNSTUFF_BITS(resp,  50, 3));
    printf("C_SIZE_MULTI = %u\n",       UNSTUFF_BITS(resp,  47, 3));
    printf("ERASE_GRP_SIZE = %u\n",     UNSTUFF_BITS(resp,  42, 5));
    printf("ERASE_GRP_MULTI = %u\n",    UNSTUFF_BITS(resp,  37, 5));
    printf("WP_GRP_SIZE = %u\n",        UNSTUFF_BITS(resp,  32, 5));
    printf("WP_GRP_ENABLE = %u\n",      UNSTUFF_BITS(resp,  31, 1));
    printf("DEFAULT_ECC = %u\n",        UNSTUFF_BITS(resp,  29, 2));
    printf("R2W_FACTOR = %u\n",         UNSTUFF_BITS(resp,  26, 3));
    printf("WRITE_BL_LEN = %u\n",       UNSTUFF_BITS(resp,  22, 4));
    printf("CONTENT_PROT_APP = %u\n",   UNSTUFF_BITS(resp,  16, 1));
    printf("FILE_FORMAT_GRP = %u\n",    UNSTUFF_BITS(resp,  15, 1));
    printf("COPY = %u\n",               UNSTUFF_BITS(resp,  14, 1));
    printf("PERM_WRITE_PROTECT = %u\n", UNSTUFF_BITS(resp,  13, 1));
    printf("TMP_WRITE_PROTECT = %u\n",  UNSTUFF_BITS(resp,  12, 1));
    printf("FILE_FORMAT = %u\n",        UNSTUFF_BITS(resp,  10, 2));
    printf("ECC = %u\n",                UNSTUFF_BITS(resp,   8, 2));
    printf("CRC = %u\n",                UNSTUFF_BITS(resp,   1, 7));
#endif

    err = mmc_decode_csd(card);
    if(err)
        goto err_out;

    err = mmc_decode_cid(card);

err_out:
    return err;
}
#endif
/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
void do_exit_e(void *dev)
{
    mmcinfo("do_exit_e\n");
    //return 0;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int get_env_e(void *dev, unsigned char *buf)
{
    mmcinfo("get_env_e\n");
    return 0;
}

/************************************************************************
 *
 *  Description :
 *  -------------
 *  Parameters :
 *  ------------
 *  Return values :
 ************************************************************************/
int save_env_e(void *dev, unsigned char *buf)
{
    mmcinfo("save_env_e\n");
    return 0;
}


/* end of file */


