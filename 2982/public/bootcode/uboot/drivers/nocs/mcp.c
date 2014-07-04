#include "nocs_bsd_env.h"
#include "print_rpc.h"
#include "mcp.h"

#include <asm/arch/flash_writer_u/mcp.h>
//
////===============================
//#include <linux/kernel.h>
//#include <linux/ioport.h>
//#include <linux/delay.h>
//#include <linux/slab.h>
//#include <linux/mm.h>
//#include <linux/init.h>
//#include <linux/interrupt.h>
//#include <linux/wait.h>
//#include <linux/fs.h>
//#include <linux/cdev.h>
//#include <linux/module.h>
//#include <linux/dma-mapping.h>
//#include <linux/device.h>
//#include <linux/platform_device.h>
//#include <linux/notifier.h>
//#include <linux/list.h>
//#include <linux/uaccess.h>
//
//#include "./include/mach/mcp.h"
//#include "./include/mach/platform.h"
//#include <asm/mutex.h>
//#include <asm/io.h>
//#include "mcp.h"
//
//
//
//
//
////#define USE_DVR_MALLOC
//#ifdef USE_DVR_MALLOC
//#include <linux/pageremap.h>       // for dvr_malloc / dvr_free
//#endif
//
//static struct device*   mcp_device;
//static struct cdev      mcp_dev;
//static dev_t            devno;
//
////static spinlock_t       mcp_buffer_lock = SPIN_LOCK_UNLOCKED;
//static DEFINE_SPINLOCK(mcp_buffer_lock);
//
//static DEFINE_MUTEX(mcp_mutex);
//
//
//#ifdef MCP_INTERRUPT_ENABLE
//DECLARE_WAIT_QUEUE_HEAD(mcp_wait_queue);
//#define MCP_IRQ    44 // 5
//#endif
#define _mcp_map_single(p_data, len, dir)       dma_map_single(mcp_device, (void*) p_data, (size_t) len, dir)
#define _mcp_unmap_single(p_data, len, dir)     dma_unmap_single(mcp_device, (dma_addr_t) p_data, (size_t)  len, dir)

/* ========================================================= */
/* mcp_cipher_dev.c                                          */
/* ========================================================= */
typedef struct{
    unsigned char   type;
    unsigned char   enc;
    unsigned char   key_len;
    unsigned char*  key;
    unsigned char   iv_len;
    unsigned char*  iv;
}MCP_CIPHER_PARAM;


typedef struct{
    unsigned char*  in;
    unsigned long   len;
    unsigned char*  out;
}MCP_CIPHER_DATA;


#define MCP_CIPHER_DES_ECB          0x00
#define MCP_CIPHER_DES_CBC          0x01
#define MCP_CIPHER_TDES_ECB         0x10
#define MCP_CIPHER_TDES_CBC         0x11
#define MCP_CIPHER_AES_128_ECB      0x20
#define MCP_CIPHER_AES_128_CBC      0x21
#define MCP_CIPHER_AES_128_CTR      0x22

extern void rtk_show_data(unsigned char ch_line,unsigned int d_len,
                   void* d_buf,unsigned int type_ctl,unsigned char * message );

//#ifdef MCP_INTERRUPT_ENABLE

///*------------------------------------------------------------------
// * Func : mcp_isr
// *
// * Desc : isr of mars/jupiter mcp
// *
// * Parm : p_this : handle of venus i2c
// *
// * Retn : 0
// *------------------------------------------------------------------*/
//static
//irqreturn_t mcp_isr(
//  int                 this_irq,
//  void*               dev_id,
//  struct pt_regs*     regs)
//{
//    if ((GET_MCP_STATUS() & ~(MCP_COMPARE)))
//    {
//        SET_MCP_EN(0xFE);           // disable all interrupts
//        wake_up(&mcp_wait_queue);
//        return IRQ_HANDLED;
//    }
//
//    return IRQ_NONE;
//}
//
//#endif
//
//
//
//
/*------------------------------------------------------------------
 * Func : _mcp_load_otp
 *
 * Desc : load otp key
 *
 * Parm : N/A
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
static void _mcp_load_otp(void)
{
    int i = 0;

    SET_MCP_OTP_LOAD(1);

    while(GET_MCP_OTP_LOAD())
    {
        if (i++ > 100)
        {
            BDPRINT("Load OTP Key Timeout\n");
        }

        udelay(10);
    }
}



/*------------------------------------------------------------------
 * Func : _mcp_phy_init
 *
 * Desc : init mcp engine
 *
 * Parm : N/A
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
static int _mcp_phy_init(void)
{
    BDPRINT_FUNC();
    rtd_outl(0xb80151fc, 0);     // make sure CP uses DDR not Internal SRAM

    _mcp_load_otp();

    SET_MCP_CTRL(MCP_GO);       // dessert go bit
    SET_MCP_EN(0xFE);           // disable all interrupts
    SET_MCP_STATUS(0xFE);       // clear interrupts status
    SET_MCP_BASE (0);
    SET_MCP_LIMIT(0);
    SET_MCP_RDPTR(0);
    SET_MCP_WRPTR(0);

    SET_MCP_CTRL(MCP_ARB_MODE(1) | MCP_WRITE_DATA);     // set arbitraction mode to mode 1

    SET_MCP_CTRL1(MCP_AES_PAD_OFF(1) |                  // disable AES_H auto padding
                  MCP_CSA_ENTROPY(ORIGIONAL_MODE) |     // setup csa mode
                  MCP_ROUND_NO(0));                     // set round number of multi-2 to 1

    return 0;
}


/*------------------------------------------------------------------
 * Func : mcp_init
 *
 * Desc : init mcp engine
 *
 * Parm : N/A
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
int mcp_init(void)
{
    BDPRINT_FUNC();
    if (_mcp_phy_init()<0)
        return -1;

    return 0;
}



///*------------------------------------------------------------------
// * Func : mcp_uninit
// *
// * Desc : uninit mcp engine
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//static void mcp_uninit(void)
//{
//    SET_MCP_CTRL(MCP_GO);           // dessert go bit
//    SET_MCP_EN(0xFE);               // disable all interrupts
//    msleep(10);                     // wait for hw stop
//    SET_MCP_BASE (0);
//    SET_MCP_LIMIT(0);
//    SET_MCP_RDPTR(0);
//    SET_MCP_WRPTR(0);
//#ifdef MCP_INTERRUPT_ENABLE
//    free_irq(MCP_IRQ, &mcp_wait_queue);
//#endif
//}


void _DumpDescriptor(mcp_desc * d)
{
    BD_INFO("\n\nXXXXXXXX desc (%p) XXXXXXXXXX\n",d);
    BD_INFO("flag = %08lx\n",d->flags);
    BD_INFO("Key0 = %08lx\n",d->key[0]);
    BD_INFO("Key1 = %08lx\n",d->key[1]);
    BD_INFO("Key2 = %08lx\n",d->key[2]);
    BD_INFO("Key3 = %08lx\n",d->key[3]);
    BD_INFO("Key4 = %08lx\n",d->key[4]);
    BD_INFO("Key5 = %08lx\n",d->key[5]);
    BD_INFO("IV0  = %08lx\n",d->iv[0]);
    BD_INFO("IV1  = %08lx\n",d->iv[1]);
    BD_INFO("IV2  = %08lx\n",d->iv[2]);
    BD_INFO("IV3  = %08lx\n",d->iv[3]);
    BD_INFO("di   = %08lx\n",d->data_in);
    BD_INFO("do   = %08lx\n",d->data_out);
    BD_INFO("len  = %08lx\n",d->length);
    BD_INFO("XXXXXXXX desc end XXXXXXXXXX\n\n");
}


///*------------------------------------------------------------------
// * Func : _mcp_dump_desc_buffer
// *
// * Desc : set descriptors buffer
// *
// * Parm : N/A
// *
// * Retn : dma_addr
// *------------------------------------------------------------------*/
//void _mcp_dump_desc_buffer(void)
//{
//    unsigned long event;
//
//    spin_lock_irqsave(&mcp_buffer_lock, event);
//
//    BD_INFO("BASE=%08x, RP=%08x, WP=%08x, LIMIT=%08x\n",
//                  GET_MCP_BASE(),
//                  GET_MCP_RDPTR(),
//                  GET_MCP_WRPTR(),
//                  GET_MCP_LIMIT());
//
//    spin_unlock_irqrestore(&mcp_buffer_lock, event);
//}
//
//
/*------------------------------------------------------------------
 * Func : _mcp_set_desc_buffer
 *
 * Desc : set descriptors buffer
 *
 * Parm : base  : base address of descriptor buffer
 *        limit : limit address of descriptor buffer
 *        rp    : read pointer of descriptor buffer
 *        wp    : write pointer of descriptor buffer
 *
 * Retn : 0
 *------------------------------------------------------------------*/
int _mcp_set_desc_buffer(
    unsigned long       base,
    unsigned long       limit,
    unsigned long       rp,
    unsigned long       wp
    )
{
    //unsigned long event;

    SET_MCP_BASE (base);
    SET_MCP_LIMIT(limit);
    SET_MCP_RDPTR(rp);
    SET_MCP_WRPTR(wp);

    return 0;
}

/*------------------------------------------------------------------
 * Func : _mcp_start_xfer
 *
 * Desc : Start Xfer
 *
 * Parm : N/A
 *
 * Retn : S_OK /  S_FALSE
 *------------------------------------------------------------------*/
int _mcp_start_xfer(void)
{
    int ret = -1;
    int WaitTime = 0x3FF << 2;
    int wiat_clear_timeout = 0;

    SET_MCP_CTRL(MCP_CLEAR | MCP_WRITE_DATA);    // issue clear

    while (GET_MCP_CTRL() & MCP_CLEAR && wiat_clear_timeout++<30);

    if (GET_MCP_CTRL() & MCP_CLEAR)
    {
        BD_INFO("wait clear bit deassert timeout,  force unset clear bit, (CTRL=%08x, STATUS=%08x)\n",
                    GET_MCP_CTRL(), GET_MCP_STATUS());
        SET_MCP_CTRL(MCP_CLEAR);    // issue clear
        BD_INFO("CTRL=%08x, STATUS=%08x)\n",GET_MCP_CTRL(), GET_MCP_STATUS());
    }

    SET_MCP_EN(0xFE);

    SET_MCP_STATUS(0xFE);    // clear status

    SET_MCP_CTRL(MCP_GO | MCP_WRITE_DATA);

    while (WaitTime--)
    {
        //BD_INFO("STATUS=%08x, CTRL=%08x\n",GET_MCP_STATUS(), GET_MCP_CTRL());
        if (!(GET_MCP_CTRL() & MCP_GO))
            break;

        if ((WaitTime & 0x3FF) ==0)
            mdelay(10);
    }

    //ret = ((GET_MCP_STATUS() & ~(MCP_RING_EMPTY | MCP_COMPARE))) ? -1 : 0;
    if (GET_MCP_STATUS() & 0x2){
        BD_INFO("\n");
        ret = 0;        // ring buffer is empty
    }else if(GET_MCP_STATUS() & 0x4){
        BD_INFO("\n");
        ret = -1;       // error happened
    }else{
        BD_INFO("\n");
        ret = -2;       // ???
    }

    if (ret <0)
        BD_INFO("do mcp command failed, (MCP_Status %08x)\n", GET_MCP_STATUS());

    SET_MCP_CTRL(MCP_GO);               // clear go bit

    SET_MCP_STATUS(0xFE);               // clear ring empty

    return ret;
}

/*------------------------------------------------------------------
 * Func : mcp_fixup_descriptor_jupiter
 *
 * Desc : fixup descriptor
 *
 * Parm : p_desc : descriptor to fixup
 *
 * Retn : 0
 *------------------------------------------------------------------*/
int mcp_fixup_descriptor_jupiter(
    mcp_desc*               p_desc
    )
{
#define des_key_remap(x,y)      do { y = (y & 0x00FFFFFF) + ((x & 0xFF)<<24); x >>= 8; }while(0)

    BD_INFO("flags=0x%lx\n",p_desc->flags);
    switch(MCP_MODE(p_desc->flags))
    {
        case MCP_ALGO_DES: // 56-bit
            BD_INFO("MCP_ALGO_DES\n");
            des_key_remap(p_desc->key[0], p_desc->key[1]);
            break;

        case MCP_ALGO_3DES: // 168-bit
            BD_INFO("MCP_ALGO_3DES\n");
            des_key_remap(p_desc->key[0], p_desc->key[1]);
            des_key_remap(p_desc->key[2], p_desc->key[3]);
            des_key_remap(p_desc->key[4], p_desc->key[5]);
            break;
        default:
            BD_INFO("\n");
            break;
    }

//    _DumpDescriptor(p_desc);

#undef des_key_remap

    return 0;
}



/*------------------------------------------------------------------
 * Func : mcp_fixup_descriptors
 *
 * Desc : Do Command
 *
 * Parm : p_desc  : pointer of Descriptor to be Execute
 *        n_desc  : number of Descriptor to be Execute
 *
 * Retn : 0
 *------------------------------------------------------------------*/
int mcp_fixup_descriptors(
    mcp_desc* p_desc,
    int       n_desc
    )
{
    while(n_desc-- > 0){
        BD_INFO("\n");
        mcp_fixup_descriptor_jupiter(p_desc++);
    }

    return 0;
}



/*------------------------------------------------------------------
 * Func : mcp_do_command
 *
 * Desc : Do Command
 *
 * Parm : p_desc : number of Descriptor to be Execute
 *        n_desc  : number of Descriptor to be Execute
 *
 * Retn : 0 : success, others fail
 *------------------------------------------------------------------*/
#if 0
#define MCP_DEBUG
#define K_MCP_EN     0xb8015108
#define K_MCP_CTRL   0xb8015100
#define MCP_RW_42K   0xb80151fc
#define K_MCP_BASE   0xb801510c
#define K_MCP_LIMIT  0xb8015110
#define K_MCP_RDPTR  0xb8015114
#define K_MCP_WRPTR  0xb8015118
#define K_MCP_STATUS 0xb8015104

static int rtk_do_mcp(mcp_desc*   dscpt)
{
#ifdef MCP_DEBUG
    int i;
#endif
    int res;
    int count;
    unsigned int org;

    printf("%s(%d)\n",__func__,__LINE__);
    if (dscpt == NULL){
        printf("%s(%d)dscpt == NULL\n",__func__,__LINE__);
        return -1;
    }

    // disable interrupt
    rtd_outl(K_MCP_EN, 0xfe);

    // disable go bit
    rtd_outl(K_MCP_CTRL, 0x2);

    // change to DBUS
    org = rtd_inl(MCP_RW_42K);
    rtd_outl(MCP_RW_42K, org & (~0x1));

    // set ring buffer register
    rtd_outl(K_MCP_BASE,  ((unsigned int) dscpt));
    rtd_outl(K_MCP_LIMIT, ((unsigned int) dscpt + sizeof(mcp_desc) * 2));
    rtd_outl(K_MCP_RDPTR, ((unsigned int) dscpt) );
    rtd_outl(K_MCP_WRPTR, ((unsigned int) dscpt + sizeof(mcp_desc))); // writer pointer cannot be equal to limit
/*
    rtd_outl(K_MCP_BASE,  PHYS(((unsigned int) dscpt)) );
    rtd_outl(K_MCP_LIMIT, PHYS(((unsigned int) dscpt + sizeof(mcp_desc) * 2) ));
    rtd_outl(K_MCP_RDPTR, PHYS(((unsigned int) dscpt) ));
    rtd_outl(K_MCP_WRPTR, PHYS(((unsigned int) dscpt + sizeof(mcp_desc)) )); // writer pointer cannot be equal to limit
*/
    flush_cache((unsigned long)dscpt, sizeof(mcp_desc));

#ifdef MCP_DEBUG
    printf("MCP descriptor (addr 0x%x):\n", (unsigned int) dscpt);
    printf("word 0: %x\n", dscpt->flags);
    printf("word 1~6:\n");
    for (i = 0; i < sizeof(dscpt->key)/sizeof(int); i++) {
        printf("\t%x\n", dscpt->key[i]);
    }

    printf("word 7~10:\n");
    for (i = 0; i < sizeof(dscpt->iv)/sizeof(int); i++) {
        printf("\t%x\n", dscpt->iv[i]);
    }

    printf("word 11: %x\n", dscpt->data_in);
    printf("word 12: %x\n", dscpt->data_out);
    printf("word 13: %x\n", dscpt->length);
    //printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
    printf("\nMCP ring buffer registers:\n");
    printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n",
        rtd_inl(K_MCP_BASE), rtd_inl(K_MCP_LIMIT), rtd_inl(K_MCP_RDPTR), rtd_inl(K_MCP_WRPTR));
#endif

    asm("DSB");

    // change endian
    //rtd_outl(K_MCP_CTRL, 0x8); //we don't have to do this due to SCPU is little endian

    // go
    rtd_outl(K_MCP_CTRL, 0x3);
    count = 0;
    while ((rtd_inl(K_MCP_STATUS) & 0x6) == 0) {
        count++;
        if (count == 0x800000) {
#ifdef MCP_DEBUG
            printf("%s timeout\n", __FUNCTION__);
            printf("REG32(MCP_CTRL): 0x%x\n", rtd_inl(K_MCP_CTRL));
            printf("REG32(MCP_STATUS): 0x%x\n", rtd_inl(K_MCP_STATUS));
#endif
            return -3;
        }
    }

#ifdef MCP_DEBUG
    printf("mcp done counter: 0x%x\n", count);
    printf("MCP status: 0x%x\n", rtd_inl(K_MCP_STATUS));
#endif

    // check result
    if (rtd_inl(K_MCP_STATUS) & 0x2)
        res = 0;        // ring buffer is empty
    else if (rtd_inl(K_MCP_STATUS) & 0x4)
        res = -1;       // error happened
    else
        res = -2;       // ???

    // clear MCP register
    rtd_outl(K_MCP_CTRL, 0x2);
    rtd_outl(K_MCP_STATUS, 0x6);
    //restore
    rtd_outl(MCP_RW_42K, org);

    if(res){
        printf("%s(%d)do_mcp fail[res=%d]\n",__func__,__LINE__,res);
    }
    return res;
}
#endif

int mcp_do_command(
    mcp_desc*   p_desc,
    int         n_desc
    )
{
    dma_addr_t addr;

    int ret = 0;
    int len = sizeof(mcp_desc) * n_desc;

    //ret = rtk_do_mcp(p_desc);


    BD_INFO("p_desc=0x%p; n_desc=0x%d\n",
             p_desc,n_desc);

    _DumpDescriptor(p_desc);

    if (n_desc)
    {
        BD_INFO("\n");
        mcp_fixup_descriptors(p_desc, n_desc);      // fixup descriptors

        addr = (dma_addr_t)p_desc;

        _mcp_set_desc_buffer(addr, addr + len + sizeof(mcp_desc), addr, addr + len);

        //_mcp_dump_desc_buffer();

        ret = _mcp_start_xfer();

        //_mcp_dump_desc_buffer();

        _mcp_set_desc_buffer(0, 0, 0, 0);
    }

    return ret;
}


///***************************************************************************
//               ------------------- APIS ----------------
//****************************************************************************/
//
//
///********************************************************************************
// AES Hash
// ********************************************************************************/
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_HASH_INIT
// *
// * Desc : Init AES Hashing Descriptor
// *
// * Parm : pDesc      : Descriptor to be Load
// *
// * Retn : 0 for success, others failed
// *------------------------------------------------------------------*/
//int MCP_AES_H_HASH_INIT(
//  mcp_desc*           p_desc
//  )
//{
//    memset(p_desc, 0, sizeof(mcp_desc));
//
//    p_desc->flags = MCP_MODE(MCP_ALGO_AES_H)
//                      | MCP_BCM(MCP_BCM_ECB)
//                      | MCP_ENC(1);
//
//    p_desc->iv[0]   = 0x2DC2DF39;
//    p_desc->iv[1]   = 0x420321D0;
//    p_desc->iv[2]   = 0xCEF1FE23;
//    p_desc->iv[3]   = 0x74029D95;
//    return 0;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_IV_UPDATE
// *
// * Desc : Update Initial Vector of AES Hashing Descriptor
// *
// * Parm : p_desc      : Descriptor to be Load
// *
// * Retn : 0 for success, others failed
// *------------------------------------------------------------------*/
//int MCP_AES_H_IV_UPDATE(
//  mcp_desc*           p_desc,
//  unsigned char           hash[16]
//  )
//{
//    p_desc->iv[0]   = (hash[ 0]<<24) + (hash[ 1]<<16) + (hash[ 2]<<8) + hash[ 3];
//    p_desc->iv[1]   = (hash[ 4]<<24) + (hash[ 5]<<16) + (hash[ 6]<<8) + hash[ 7];
//    p_desc->iv[2]   = (hash[ 8]<<24) + (hash[ 9]<<16) + (hash[10]<<8) + hash[11];
//    p_desc->iv[3]   = (hash[12]<<24) + (hash[13]<<16) + (hash[14]<<8) + hash[15];
//    return 0;
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_PADDING
// *
// * Desc : padding tail to the end of the last data block.
// *
// * Parm : p_buff        : data buffer
// *        buff_len      : length of buffer
// *        data_len      : total length of data in byte(from 1st block to
// *                        the last block)
// *
// * Retn : > 0 : number of bytes padded
// *------------------------------------------------------------------*/
//int MCP_AES_H_PADDING(
//    unsigned char*        p_buff,
//    unsigned long         buff_len,
//    unsigned long             data_len
//    )
//{
//    unsigned long long bit_len = ((unsigned long long) data_len) << 3;
//    int pad_sz = 16 - (data_len & 0xF);
//
//    if (pad_sz <= 8)
//        pad_sz += 16;
//
//    if (buff_len < pad_sz)
//    {
//        mcp_warning("padding AES_H data failed, no enough space left for data padding. pad_sz = %d, remain_sz = %ld\n", pad_sz, buff_len);
//        return 0;
//    }
//
//    memset(p_buff, 0, pad_sz);
//
//    *p_buff |= 0x80;
//
//    // pad bit length in big endian format
//    p_buff += pad_sz-8;
//    *p_buff++ = (bit_len >> 56) & 0xFF;
//    *p_buff++ = (bit_len >> 48) & 0xFF;
//    *p_buff++ = (bit_len >> 40) & 0xFF;
//    *p_buff++ = (bit_len >> 32) & 0xFF;
//    *p_buff++ = (bit_len >> 24) & 0xFF;
//    *p_buff++ = (bit_len >> 16) & 0xFF;
//    *p_buff++ = (bit_len >>  8) & 0xFF;
//    *p_buff++ = (bit_len)       & 0xFF;
//
//    return pad_sz;
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_Hashing
// *
// * Desc : Do AES H Hashing
// *
// * Parm : pDesc      : Descriptor to be Load
// *        DataIn     : Data to be hashing (in Physical Address)
// *        Len        : number of data to be hashing
// *        DataOut    : Physical address that used to store hash value
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//int MCP_AES_H_Hashing(
//    mcp_desc*             p_desc,
//    unsigned char*        p_in,
//    unsigned long         len,
//    unsigned char*        p_out
//    )
//{
//    int ret = 0;
//
//    dma_addr_t addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
//
//    dma_addr_t addr2 = _mcp_map_single(p_out, 16, DMA_FROM_DEVICE);
//
//    p_desc->data_in  = addr1;
//
//    p_desc->data_out = addr2;
//
//    p_desc->length   = len;
//
//    ret = mcp_do_command(p_desc, 1);
//
//    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);
//
//    _mcp_unmap_single(addr2, 16, DMA_FROM_DEVICE);
//
//    return ret;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_DataHash
// *
// * Desc : Compute hash value of Data via 128 bits AES_H_Hasing
// *
// * Parm : pData         : Start address of data
// *        DataLen       : Length of data
// *        Hash[16]      : 128 bits hash value of the file
// *        BlockSize     : Block Size that used to compute Hashing Value
// *        first_block   : 1 : this block is first block
// *                        0 : this block is not first block
// *
// *           if this block is first block, the iv of the descriptor
// *           will be reset to default. if this block is not first block
// *           then uses the hash vaule as the default iv.
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//int MCP_AES_H_DataHash(
//    unsigned char*        p_data,
//    unsigned long         data_len,
//    unsigned char         hash[16],
//    unsigned long             block_size,
//    unsigned char             first_block
//    )
//{
//    mcp_desc desc;
//    int      ret = 0;
//
//    MCP_AES_H_HASH_INIT(&desc);
//
//    if (!first_block)
//        MCP_AES_H_IV_UPDATE(&desc, hash);  // Update Hash Value
//
//    while(data_len && !ret)
//    {
//        if (data_len > block_size)
//        {
//            ret       = MCP_AES_H_Hashing(&desc, p_data, block_size, hash);
//            data_len -= block_size;
//            p_data   += block_size;
//        }
//        else
//        {
//            ret       = MCP_AES_H_Hashing(&desc, p_data, data_len, hash);
//            p_data   += data_len;
//            data_len = 0;
//        }
//
//        MCP_AES_H_IV_UPDATE(&desc, hash);  // Update Hash Value
//    }
//
//    return ret;
//}
//



/********************************************************************************
 DES
 ********************************************************************************/

/*======================================================================
 * Func : MCP_DES_DESC_INIT
 *
 * Desc : Init DES Descriptor
 *
 * Parm : pDesc      : Descriptor to be Load
 *        EnDe       : Encryption/Descryption
 *              0 for Decryption / 1 for Encryption
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_DES_DESC_INIT(
    mcp_desc*       pDesc,
    unsigned char   EnDe,
    unsigned char   Mode,
    unsigned char   Key[7],
    unsigned char   IV[8]
    )
{
    //memset(pDesc, 0, sizeof(mcp_desc));

    pDesc->flags = MCP_MODE(MCP_ALGO_DES) | MCP_BCM(Mode) | MCP_ENC(EnDe);

    if (Key == NULL)
    {
        pDesc->flags |= MCP_KEY_SEL(MCP_KEY_SEL_OTP);
    }
    else if((unsigned long)Key <= MCP_MAX_CW_ENTRY)
    {
        pDesc->flags  |= MCP_KEY_SEL(MCP_KEY_SEL_CW);
        pDesc->key[0]  = MCP_CW_KEY((unsigned long)(Key-1));
        pDesc->key[1]  = 0;
        pDesc->key[2]  = 0;
        pDesc->key[3]  = 0;
    }
    else
    {
        pDesc->key[0]  = (Key[0]<<24) + (Key[1]<<16) + (Key[2]<<8) + Key[3];
        pDesc->key[1]  = (Key[4]<<16) + (Key[5]<<8)  +  Key[6];
    }

    if (IV)
    {
        pDesc->iv[0]   = (IV[0]<<24) + (IV[1]<<16) + (IV[2]<<8) + IV[3];
        pDesc->iv[1]   = (IV[4]<<24) + (IV[5]<<16) + (IV[6]<<8) + IV[7];
    }

    return 0;
}


/*======================================================================
 * Func : MCP_DES_Decryption
 *
 * Desc : Do DES Decryption
 *
 * Parm : pDesc      : Descriptor to be Load
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *        p_in       : Data In
 *        p_out      : Data Out
 *        len        : Data Length
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_DES_Decryption(
    unsigned char   Mode,
    unsigned char   Key[7],
    unsigned char   IV[8],
    unsigned char*  p_in,
    unsigned char*  p_out,
    unsigned long   len
    )
{
    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){
        memset(desc, 0, 128);
        MCP_DES_DESC_INIT(desc, 0, Mode, Key, IV);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0x7;

        ret = mcp_do_command(desc, 1);

        free(desc);
    }else{
        ret = -1;
    }

    return ret;
}




/*======================================================================
 * Func : MCP_DES_Encryption
 *
 * Desc : Do DES Encryption
 *
 * Parm : pDesc      : Descriptor to be Load
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *        DataIn     : Data In
 *        DataOut    : Data Out
 *        Len        : Data Length
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_DES_Encryption(
    unsigned char           Mode,
    unsigned char           Key[7],
    unsigned char           IV[8],
    unsigned char*          p_in,
    unsigned char*          p_out,
    unsigned long           len
    )
{

    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){
        memset(desc, 0, 128);
        MCP_DES_DESC_INIT(desc, 1, Mode, Key, IV);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0x7;

        ret = mcp_do_command(desc, 1);
        free(desc);
    }else{
        ret = -1;
    }
    return ret;

#if 0
    mcp_desc desc;
    int ret;
    dma_addr_t addr1;
    dma_addr_t addr2;

    MCP_DES_DESC_INIT(&desc, 1, Mode, Key, IV);

    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    addr2 = _mcp_map_single(p_out, len, DMA_FROM_DEVICE);

    desc.data_in  = addr1;
    desc.data_out = addr2;
    desc.length   = len & ~0x7;

    ret = mcp_do_command(&desc, 1);

    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);

    _mcp_unmap_single(addr2, len, DMA_FROM_DEVICE);

    return ret;
#endif
}



/********************************************************************************
 TDES
 ********************************************************************************/


/*======================================================================
 * Func : MCP_TDES_DESC_INIT
 *
 * Desc : Init TDES Descriptor
 *
 * Parm : pDesc      : Descriptor to be Load
 *        EnDe       : Encryption/Descryption
 *              0 for Decryption / 1 for Encryption
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_TDES_DESC_INIT(
    mcp_desc*           pDesc,
    unsigned char       EnDe,
    unsigned char       Mode,
    unsigned char       Key[21],
    const unsigned char       IV[8] )
{
    //memset(pDesc, 0, sizeof(mcp_desc));

    pDesc->flags = MCP_MODE(MCP_ALGO_3DES) |
                   MCP_BCM(Mode) |
                   MCP_ENC(EnDe);

    if (Key == NULL)
    {
        BD_INFO("\n");
        pDesc->flags |= MCP_KEY_SEL(MCP_KEY_SEL_OTP);
    }
    else if((unsigned long)Key <= MCP_MAX_CW_ENTRY)
    {
        BD_INFO("CW key entry=0x%x(%d)\n",(unsigned int)(Key-1),(unsigned int)(Key-1));
        BD_INFO("set to key[0]=0x%08lx\n",MCP_CW_KEY((unsigned long)(Key-1)));
        pDesc->flags  |= MCP_KEY_SEL(MCP_KEY_SEL_CW);
        pDesc->key[0]  = MCP_CW_KEY((unsigned long)(Key-1));
        pDesc->key[1]  = 0;
        pDesc->key[2]  = 0;
        pDesc->key[3]  = 0;
        pDesc->key[4]  = 0;
        pDesc->key[5]  = 0;
    }
    else
    {
        if (EnDe)
        {
            BD_INFO("\n");
            // Key A
            pDesc->key[0]  = (Key[ 0]<<24) + (Key[ 1]<<16) + (Key[ 2]<<8) + Key[3];
            pDesc->key[1]  = (Key[ 4]<<16) + (Key[ 5]<<8)  +  Key[ 6];

            // Key B
            pDesc->key[2]  = (Key[ 7]<<24) + (Key[ 8]<<16) + (Key[ 9]<<8) + Key[10];
            pDesc->key[3]  = (Key[11]<<16) + (Key[12]<<8)  +  Key[13];

            // Key C
            pDesc->key[4]  = (Key[14]<<24) + (Key[15]<<16) + (Key[16]<<8) + Key[17];
            pDesc->key[5]  = (Key[18]<<16) + (Key[19]<<8)  +  Key[20];
        }
        else
        {
            BD_INFO("\n");
            // Key C
            pDesc->key[4]  = (Key[ 0]<<24) + (Key[ 1]<<16) + (Key[ 2]<<8) + Key[3];
            pDesc->key[5]  = (Key[ 4]<<16) + (Key[ 5]<<8)  +  Key[ 6];

            // Key B
            pDesc->key[2]  = (Key[ 7]<<24) + (Key[ 8]<<16) + (Key[ 9]<<8) + Key[10];
            pDesc->key[3]  = (Key[11]<<16) + (Key[12]<<8)  +  Key[13];

            // Key A
            pDesc->key[0]  = (Key[14]<<24) + (Key[15]<<16) + (Key[16]<<8) + Key[17];
            pDesc->key[1]  = (Key[18]<<16) + (Key[19]<<8)  +  Key[20];
        }
    }

    if (IV)
    {
        BD_INFO("\n");
        pDesc->iv[0]   = (IV[0]<<24) + (IV[1]<<16) + (IV[2]<<8) + IV[3];
        pDesc->iv[1]   = (IV[4]<<24) + (IV[5]<<16) + (IV[6]<<8) + IV[7];
    }

    return 0;
}




/*======================================================================
 * Func : MCP_TDES_Decryption
 *
 * Desc : Do TDES Decryption
 *
 * Parm : pDesc      : Descriptor to be Load
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *        p_in       : Data In
 *        p_out      : Data Out
 *        len        : Data Length
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_TDES_Decryption(
    unsigned char           Mode,
    unsigned char           Key[21],
    const unsigned char		IV[8],
    const unsigned char*  	p_in,
    unsigned char*          p_out,
    unsigned long           len
    )
{

    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){

        memset(desc, 0, 128);

        MCP_TDES_DESC_INIT(desc, 0, Mode, Key, IV);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0x7;

        ret = mcp_do_command(desc, 1);

        free(desc);
    }else{
        ret = -1;
    }
    return ret;
#if 0
    mcp_desc desc;
    int ret;
    dma_addr_t addr1;
    dma_addr_t addr2;

    MCP_TDES_DESC_INIT(&desc, 0, Mode, Key, IV);

    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    addr2 = _mcp_map_single(p_out, len, DMA_FROM_DEVICE);

    desc.data_in  = addr1;
    desc.data_out = addr2;
    desc.length   = len & ~0x7;

    ret = mcp_do_command(&desc, 1);

    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);
    _mcp_unmap_single(addr2, len, DMA_FROM_DEVICE);

    return ret;
#endif
}




/*======================================================================
 * Func : MCP_TDES_Encryption
 *
 * Desc : Do TDES Encryption
 *
 * Parm : pDesc      : Descriptor to be Load
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *        DataIn     : Data In
 *        DataOut    : Data Out
 *        Len        : Data Length
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_TDES_Encryption(
    unsigned char           Mode,
    unsigned char           Key[21],
    const unsigned char             IV[8],
    const unsigned char*            p_in,
    unsigned char*          p_out,
    unsigned long           len
    )
{
    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){
        BD_INFO("\n");
        memset(desc, 0, 128);

        MCP_TDES_DESC_INIT(desc, 1, Mode, Key, IV);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0x7;

        ret = mcp_do_command(desc, 1);
        free(desc);
    }else{
        BD_INFO("\n");
        ret = -1;
    }
    return ret;

#if 0
    mcp_desc desc;
    int ret;
    dma_addr_t addr1;
    dma_addr_t addr2;

    MCP_TDES_DESC_INIT(&desc, 1, Mode, Key, IV);

    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    addr2 = _mcp_map_single(p_out, len, DMA_FROM_DEVICE);

    desc.data_in  = addr1;
    desc.data_out = addr2;
    desc.length   = len & ~0x7;

    ret = mcp_do_command(&desc, 1);

    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);

    _mcp_unmap_single(addr2, len, DMA_FROM_DEVICE);

    return ret;
#endif
}





/********************************************************************************
 AES
 ********************************************************************************/

/*======================================================================
 * Func : MCP_AES_DESC_INIT
 *
 * Desc : Init AES Descriptor
 *
 * Parm : pDesc      : Descriptor to be Load
 *        EnDe       : Encryption/Descryption
 *              0 for Decryption / 1 for Encryption
 *        Mode       : Operation Mode
 *        Key        : Key Value
 *        IV         : Initial Vector
 *
 * Retn : S_OK /  S_FALSE
 *======================================================================*/
int MCP_AES_DESC_INIT(
    mcp_desc*               pDesc,
    unsigned char           EnDe,
    unsigned char           Mode,
    unsigned char           Key[16],
    const unsigned char           IV[16]
    )
{
    //memset(pDesc, 0, sizeof(mcp_desc));

    switch (Mode)
    {
    case MCP_BCM_ECB:
    case MCP_BCM_CBC:
    case MCP_BCM_CTR:

        pDesc->flags = MCP_MODE(MCP_ALGO_AES) |
                       MCP_BCM(Mode) |
                       MCP_ENC(EnDe);

        if (Key == NULL)
        {
            BD_INFO("\n");
            pDesc->flags |= MCP_KEY_SEL(MCP_KEY_SEL_OTP);
        }
        else if((unsigned long)Key <= MCP_MAX_CW_ENTRY)
        {
            BD_INFO("\n");
            pDesc->flags  |= MCP_KEY_SEL(MCP_KEY_SEL_CW);
            pDesc->key[0]  = MCP_CW_KEY((unsigned long)(Key-1));
            pDesc->key[1]  = 0;
            pDesc->key[2]  = 0;
            pDesc->key[3]  = 0;
        }
        else
        {
            BD_INFO("\n");
            pDesc->key[0]  = (Key[ 0]<<24) + (Key[ 1]<<16) + (Key[ 2]<<8) + Key[ 3];
            pDesc->key[1]  = (Key[ 4]<<24) + (Key[ 5]<<16) + (Key[ 6]<<8) + Key[ 7];
            pDesc->key[2]  = (Key[ 8]<<24) + (Key[ 9]<<16) + (Key[10]<<8) + Key[11];
            pDesc->key[3]  = (Key[12]<<24) + (Key[13]<<16) + (Key[14]<<8) + Key[15];
        }

        if (IV)
        {
            BD_INFO("\n");
            pDesc->iv[0]   = (IV[ 0]<<24) + (IV[ 1]<<16) + (IV[ 2]<<8) + IV[ 3];
            pDesc->iv[1]   = (IV[ 4]<<24) + (IV[ 5]<<16) + (IV[ 6]<<8) + IV[ 7];
            pDesc->iv[2]   = (IV[ 8]<<24) + (IV[ 9]<<16) + (IV[10]<<8) + IV[11];
            pDesc->iv[3]   = (IV[12]<<24) + (IV[13]<<16) + (IV[14]<<8) + IV[15];
        }
        else
        {
            BD_INFO("\n");
            pDesc->flags |= MCP_IV_SEL(MCP_IV_SEL_REG);
        }

        return 0;

    default:
        BD_INFO("Init AES descriptor failed - invalid mode (%d)\n", Mode);
        return -1;
    }
}

/*======================================================================
 * Func : MCP_AES_Decryption
 *
 * Desc : Do AES Decryption
 *
 * Parm : mode       : Operation Mode
 *        key        : Key Value
 *        iv         : Initial Vector
 *        p_in       : Data In
 *        p_out      : Data Out
 *        len        : Data Length
 *
 * Retn : 0 for success, others failed
 *======================================================================*/
int MCP_AES_Decryption(
    unsigned char       Mode,
    unsigned char           Key[16],
    const unsigned char     IV[16],
    const unsigned char*    p_in,
    unsigned char*          p_out,
    unsigned long           len
    )
{
    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){

        memset(desc, 0, 128);

        MCP_AES_DESC_INIT(desc, 0, Mode, Key, IV);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0xF;

        ret = mcp_do_command(desc, 1);
        free(desc);
    }else{
        ret = -1;
    }

    return ret;
#if 0
    mcp_desc desc;
    int ret;
    dma_addr_t addr1;
    dma_addr_t addr2;

    MCP_AES_DESC_INIT(&desc, 0, Mode, Key, IV);

    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    addr2 = _mcp_map_single(p_out, len, DMA_FROM_DEVICE);

    desc.data_in  = addr1;
    desc.data_out = addr2;
    desc.length   = len & ~0xF;

    ret = mcp_do_command(&desc, 1);

    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);
    _mcp_unmap_single(addr2, len, DMA_FROM_DEVICE);

    return ret;
#endif
}




/*======================================================================
 * Func : MCP_AES_Encryption
 *
 * Desc : Do AES Encryption
 *
 * Parm : mode       : Operation Mode
 *        key        : Key Value
 *        iv         : Initial Vector
 *        p_in       : Data In
 *        p_out      : Data Out
 *        len        : Data Length
 *
 * Retn : 0 for success, others failed
 *======================================================================*/
int MCP_AES_Encryption(
    unsigned char           mode,
    unsigned char           key[16],
    const unsigned char             iv[16],
    const unsigned char*            p_in,
    unsigned char*          p_out,
    unsigned long           len
    )
{

    int ret = 0;
    mcp_desc *desc = NULL;

    desc = malloc(128);

    if(desc){
        BD_INFO("\n");
        memset(desc, 0, 128);

        MCP_AES_DESC_INIT(desc, 1, mode, key, iv);

        desc->data_in  = (dma_addr_t)p_in;
        desc->data_out = (dma_addr_t)p_out;
        desc->length   = len & ~0xF;

        ret = mcp_do_command(desc, 1);

        free(desc);
    }else{
        BD_INFO("\n");
        ret = -1;
    }

    return ret;

#if 0
    mcp_desc desc;
    int ret;
    dma_addr_t addr1;
    dma_addr_t addr2;

    MCP_AES_DESC_INIT(&desc, 1, mode, key, iv);

    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    addr2 = _mcp_map_single(p_out, len, DMA_FROM_DEVICE);

    desc.data_in  = addr1;
    desc.data_out = addr2;
    desc.length   = len & ~0xF;

    ret = mcp_do_command(&desc, 1);

    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);

    _mcp_unmap_single(addr2, len, DMA_FROM_DEVICE);

    return ret;
#endif
}

//static void inline LongToByte4(
//  unsigned long           l,
//  unsigned char           b[4]
//  )
//{
//    b[0] = (l >> 24) & 0xFF;
//    b[1] = (l >> 16) & 0xFF;
//    b[2] = (l >> 8)  & 0xFF;
//    b[3] =  l        & 0xFF;
//}
//
//
///*======================================================================
// * Func : MCP_AES_PeekIV
// *
// * Desc : Do AES PeekIV
// *
// * Parm : iv         : Initial Vector
// *
// * Retn : 0 for success, others failed
// *======================================================================*/
//int MCP_AES_PeekIV(
//    unsigned char           IV[16]
//    )
//{
//    LongToByte4(GET_MCP_AES_INI_KEY0(), (unsigned char*) &IV[0]);
//    LongToByte4(GET_MCP_AES_INI_KEY1(), (unsigned char*) &IV[4]);
//    LongToByte4(GET_MCP_AES_INI_KEY2(), (unsigned char*) &IV[8]);
//    LongToByte4(GET_MCP_AES_INI_KEY3(), (unsigned char*) &IV[12]);
//    return 0;
//}
//
//
///********************************************************************************
// SHA-1 Hash
// ********************************************************************************/
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_HASH_INIT
// *
// * Desc : Init SHA1 Hashing Descriptor
// *
// * Parm : pDesc      : Descriptor to be Load
// *
// * Retn : 0 for success, others failed
// *------------------------------------------------------------------*/
//int MCP_SHA1_HASH_INIT(
//  mcp_desc*           p_desc
//  )
//{
//    memset(p_desc, 0, sizeof(mcp_desc));
//
//    p_desc->flags = MCP_MODE(MCP_ALGO_SHA_1);
//
//    //------------------------------------------------------------
//    // set up the initial value of SHA1
//    //
//    //   for mars
//    //      the initial value is hardware implemented,
//    //      no extra initial value setting is necessary.
//    //
//    //   for jupiter
//    //      use the key[0:4] to specified the initial value
//    //-----------------------------------------------------------
//    p_desc->key[0] = 0x67452301;
//    p_desc->key[1] = 0xEFCDAB89;
//    p_desc->key[2] = 0x98BADCFE;
//    p_desc->key[3] = 0x10325476;
//    p_desc->key[4] = 0xC3D2E1F0;
//
//    return 0;
//}
//
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_IV_UPDATE
// *
// * Desc : Update Initial Vector of SHA1 Hashing Descriptor
// *
// * Parm : p_desc      : Descriptor to be Load
// *
// * Retn : 0 for success, others failed
// *------------------------------------------------------------------*/
//int MCP_SHA1_IV_UPDATE(
//  mcp_desc*           p_desc,
//  unsigned char           hash[SHA1_DIGEST_SIZE])
//{
//    p_desc->key[0]   = (hash[ 0]<<24) + (hash[ 1]<<16) + (hash[ 2]<<8) + hash[ 3];
//    p_desc->key[1]   = (hash[ 4]<<24) + (hash[ 5]<<16) + (hash[ 6]<<8) + hash[ 7];
//    p_desc->key[2]   = (hash[ 8]<<24) + (hash[ 9]<<16) + (hash[10]<<8) + hash[11];
//    p_desc->key[3]   = (hash[12]<<24) + (hash[13]<<16) + (hash[14]<<8) + hash[15];
//    p_desc->key[4]   = (hash[16]<<24) + (hash[17]<<16) + (hash[18]<<8) + hash[19];
//    return 0;
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_PADDING
// *
// * Desc : padding tail to the end of the last data block.
// *
// * Parm : mcpb          : mcp buffer
// *        data_len      : total length of data in byte(from 1st block to
// *                        the last block)
// *
// * Retn : > 0 : number of bytes padded
// *------------------------------------------------------------------*/
//int MCP_SHA1_PADDING(
//    unsigned char*        p_buff,
//    unsigned long         buff_len,
//    unsigned long         data_len
//    )
//{
//    unsigned long long bit_len = ((unsigned long long) data_len) << 3;
//    int pad_sz = 64 - (data_len & SHA1_ALIGNMENT_CHECK);
//
//    if (pad_sz <= 8)
//        pad_sz += 64;
//
//    if (buff_len < pad_sz)
//    {
//        mcp_warning("padding SHA1 data failed, no enough space left for data padding. pad_sz = %d, remain_sz = %ld\n", pad_sz, buff_len);
//        return -1;
//    }
//
//    memset(p_buff, 0, pad_sz);
//
//    *p_buff |= 0x80;
//
//    // pad bit length in big endian format
//    p_buff   += pad_sz-8;
//    *p_buff++ = (bit_len >> 56) & 0xFF;
//    *p_buff++ = (bit_len >> 48) & 0xFF;
//    *p_buff++ = (bit_len >> 40) & 0xFF;
//    *p_buff++ = (bit_len >> 32) & 0xFF;
//    *p_buff++ = (bit_len >> 24) & 0xFF;
//    *p_buff++ = (bit_len >> 16) & 0xFF;
//    *p_buff++ = (bit_len >>  8) & 0xFF;
//    *p_buff++ = (bit_len)       & 0xFF;
//
//    return pad_sz;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_Hashing
// *
// * Desc : Do SHA1 Hashing
// *
// * Parm : pDesc      : Descriptor to be Load
// *        DataIn     : Data to be hashing (in Physical Address)
// *        Len        : number of data to be hashing
// *                     (for SHA1, it should be multiple of 64)
// *        DataOut    : Physical address that used to store hash value
// *                     (for SHA1, it should be 20 bytes)
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//int MCP_SHA1_Hashing(
//    mcp_desc*             p_desc,
//    unsigned char*        p_in,
//    unsigned long         len,
//    unsigned char*        p_out
//    )
//{
//    dma_addr_t addr1;
//    dma_addr_t addr2;
//    int ret = 0;
//
//    if (len & SHA1_ALIGNMENT_CHECK)
//    {
//        mcp_warning("input data length (%lu) of SHA_1 should be multiple of 64 bytes\n", len);
//        return -1;
//    }
//
//    addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
//
//    addr2 = _mcp_map_single(p_out, SHA1_DIGEST_SIZE, DMA_FROM_DEVICE);
//
//    p_desc->data_in  = addr1;
//
//    p_desc->data_out = addr2;
//
//    p_desc->length   = len;
//
//    ret = mcp_do_command(p_desc, 1);
//
//    _mcp_unmap_single(addr1, len, DMA_TO_DEVICE);
//
//    _mcp_unmap_single(addr2, SHA1_DIGEST_SIZE, DMA_FROM_DEVICE);
//
//    return ret;
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_DataHash
// *
// * Desc : Compute hash value of Data via 128 bits SHA1
// *
// * Parm : p_data        : Start address of data
// *        data_len      : Length of data
// *        hash          : 20 Bytes (160 bits) hash value of the file
// *        block_size    : Block Size that used to compute Hashing Value
// *                        for SHA1, it should be multiple of 64 bytes.
// *        block_status  : b7 : this block is the first  block
// *                        b3 : this block is the latest block
// *
// *           if this block is first block, the iv of the descriptor
// *           will be reset to default. if this block is not first block
// *           then uses the hash vaule as the default iv.
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//int MCP_SHA1_DataHash(
//    unsigned char*          p_data,
//    unsigned long           data_len,
//    unsigned char           hash[SHA1_DIGEST_SIZE],
//    unsigned long           block_size,
//    unsigned char           block_status
//    )
//{
//    mcp_desc desc;
//    int ret = 0;
//
//    MCP_SHA1_HASH_INIT(&desc);
//
//    // to simplify the implementation, we have made some constrains over here
//    // 1) the data_len must be multiple if 64 Bytes
//    // 2) the block size must be multiple if 64 Bytes
//    // 3) the data_len must be multiple if block size excepts the last block
//    if (data_len & SHA1_ALIGNMENT_CHECK)
//    {
//        mcp_warning("compute SHA1 hash value failed - data_len (%lu) should be multiple of 64 bytes\n", data_len);
//        return -1;
//    }
//
//    if (block_size & SHA1_ALIGNMENT_CHECK)
//    {
//        mcp_warning("compute SHA1 hash value failed - block size (%lu) should be multiple of 64 bytes\n", block_size);
//        return -1;
//    }
//
//    if (!(block_status & LAST_BLOCK) && (data_len % block_size))
//    {
//        mcp_warning("compute SHA1 hash value failed - data_len (%lu) should be multiple of block size (%lu) excepts the last block\n", data_len, block_size);
//        return -1;
//    }
//
//    //--------------
//    if (!(block_status & FIRST_BLOCK))
//        MCP_SHA1_IV_UPDATE(&desc, hash);    // Setup the initial value of SHA1 Hash Value
//
//    while(data_len && !ret)
//    {
//        if (data_len > block_size)
//        {
//            ret       = MCP_SHA1_Hashing(&desc, p_data, block_size, hash);
//            data_len -= block_size;
//            p_data   += block_size;
//        }
//        else
//        {
//            ret       = MCP_SHA1_Hashing(&desc, p_data, data_len, hash);
//            p_data   += data_len;
//            data_len = 0;
//        }
//
//        MCP_SHA1_IV_UPDATE(&desc, hash);  // Update Hash Value
//    }
//
//    return ret;
//}
//
//
//#ifdef CONFIG_REALTEK_MCP_SHA256
//
//
/********************************************************************************
 SHA-256 Hash
 ********************************************************************************/


/*------------------------------------------------------------------
 * Func : MCP_SHA256_HASH_INIT
 *
 * Desc : Init SHA256 Hashing Descriptor
 *
 * Parm : pDesc      : Descriptor to be Load
 *
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int MCP_SHA256_HASH_INIT(mcp_desc* p_desc)
{
    memset(p_desc, 0, sizeof(mcp_desc));

    p_desc->flags = MCP_MODE(MCP_ALGO_SHA256);

    //------------------------------------------------------------
    // set up the initial value of SHA256
    //
    //    use the key[0:5] + iv[0:1] to specified the initial value
    //-----------------------------------------------------------
    p_desc->key[0] = 0x6a09e667;
    p_desc->key[1] = 0xbb67ae85;
    p_desc->key[2] = 0x3c6ef372;
    p_desc->key[3] = 0xa54ff53a;
    p_desc->key[4] = 0x510e527f;
    p_desc->key[5] = 0x9b05688c;
    p_desc->iv[0]  = 0x1f83d9ab;
    p_desc->iv[1]  = 0x5be0cd19;
    return 0;
}



/*------------------------------------------------------------------
 * Func : MCP_SHA256_IV_UPDATE
 *
 * Desc : Update Initial Vector of SHA256 Hashing Descriptor
 *
 * Parm : p_desc      : Descriptor to be Load
 *
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int MCP_SHA256_IV_UPDATE(mcp_desc* p_desc, unsigned char hash[SHA256_DIGEST_SIZE])
{
    p_desc->key[0] = (hash[ 0]<<24) + (hash[ 1]<<16) + (hash[ 2]<<8) + hash[ 3];
    p_desc->key[1] = (hash[ 4]<<24) + (hash[ 5]<<16) + (hash[ 6]<<8) + hash[ 7];
    p_desc->key[2] = (hash[ 8]<<24) + (hash[ 9]<<16) + (hash[10]<<8) + hash[11];
    p_desc->key[3] = (hash[12]<<24) + (hash[13]<<16) + (hash[14]<<8) + hash[15];
    p_desc->key[4] = (hash[16]<<24) + (hash[17]<<16) + (hash[18]<<8) + hash[19];
    p_desc->key[5] = (hash[20]<<24) + (hash[21]<<16) + (hash[22]<<8) + hash[23];
    p_desc->iv[0]  = (hash[24]<<24) + (hash[25]<<16) + (hash[26]<<8) + hash[27];
    p_desc->iv[1]  = (hash[28]<<24) + (hash[29]<<16) + (hash[30]<<8) + hash[31];
    return 0;
}


/*------------------------------------------------------------------
 * Func : MCP_SHA256_PADDING
 *
 * Desc : padding tail to the end of the last data block.
 *
 * Parm : mcpb          : mcp buffer
 *        data_len      : total length of data in byte(from 1st block to
 *                        the last block)
 *
 * Retn : > 0 : number of bytes padded
 *------------------------------------------------------------------*/
int MCP_SHA256_PADDING(
    unsigned char*          p_buff,
    unsigned long           buff_len,
    unsigned long           data_len
    )
{
    unsigned long long bit_len = ((unsigned long long) data_len) << 3;
    int pad_sz = 64 - (data_len & SHA256_ALIGNMENT_CHECK);

    if (pad_sz <= 8)
        pad_sz += 64;

    if (buff_len < pad_sz)
    {
        //mcp_warning("padding SHA1 data failed, no enough space left for data padding. pad_sz = %d, remain_sz = %ld\n", pad_sz, buff_len);
        return -1;
    }

    memset(p_buff, 0, pad_sz);

    *p_buff |= 0x80;

    // pad bit length in big endian format
    p_buff   += pad_sz-8;
    *p_buff++ = (bit_len >> 56) & 0xFF;
    *p_buff++ = (bit_len >> 48) & 0xFF;
    *p_buff++ = (bit_len >> 40) & 0xFF;
    *p_buff++ = (bit_len >> 32) & 0xFF;
    *p_buff++ = (bit_len >> 24) & 0xFF;
    *p_buff++ = (bit_len >> 16) & 0xFF;
    *p_buff++ = (bit_len >>  8) & 0xFF;
    *p_buff++ = (bit_len)       & 0xFF;

    return pad_sz;
}



/*------------------------------------------------------------------
 * Func : MCP_SHA256_Hashing
 *
 * Desc : Do SHA256 Hashing
 *
 * Parm : pDesc      : Descriptor to be Load
 *        DataIn     : Data to be hashing (in Physical Address)
 *        Len        : number of data to be hashing
 *                     (for SHA1, it should be multiple of 64)
 *        DataOut    : Physical address that used to store hash value
 *                     (for SHA1, it should be 20 bytes)
 *
 * Retn : S_OK  /  S_FALSE
 *------------------------------------------------------------------*/
int MCP_SHA256_Hashing(
    mcp_desc*               p_desc,
    unsigned char*          p_in,
    unsigned long           len,
    unsigned char*          p_out
    )
{
    dma_addr_t addr1;
    dma_addr_t addr2;
    int ret = 0;

    BDPRINT_FUNC();

    BD_INFO("p_desc=0x%p; p_in=0x%p; p_out=0x%p; len=%ld[0x%lx] \n",
             p_desc,p_in,p_out,len,len);

    if (len & SHA1_ALIGNMENT_CHECK)
    {
        BD_INFO("input data length (%lu) of SHA_1 should be multiple of 64 bytes\n", len);
        return -1;
    }

    //addr1 = _mcp_map_single(p_in, len, DMA_TO_DEVICE);
    //addr2 = _mcp_map_single(p_out, SHA256_DIGEST_SIZE, DMA_FROM_DEVICE);

    addr1 = (dma_addr_t)p_in;

    addr2 = (dma_addr_t)p_out;

    p_desc->data_in  = addr1;

    p_desc->data_out = addr2;

    p_desc->length   = len;

    //_DumpDescriptor(p_desc);

    BD_INFO("p_desc=0x%p; p_in=0x%p; p_out=0x%p; len=%ld[0x%lx] \n",
             p_desc,p_in,p_out,len,len);
    ret = mcp_do_command(p_desc, 1);

    //_mcp_unmap_single(addr1, len, DMA_TO_DEVICE);
    //_mcp_unmap_single(addr2, SHA256_DIGEST_SIZE, DMA_FROM_DEVICE);

    return ret;
}



///*------------------------------------------------------------------
// * Func : MCP_SHA256_DataHash
// *
// * Desc : Compute hash value of Data via 128 bits SHA1
// *
// * Parm : p_data        : Start address of data
// *        data_len      : Length of data
// *        hash          : 32 Bytes (256 bits) hash value of the file
// *        block_size    : Block Size that used to compute Hashing Value
// *                        for SHA256, it should be multiple of 64 bytes (512 bits).
// *        block_status  : b7 : this block is the first  block
// *                        b3 : this block is the latest block
// *
// *           if this block is first block, the iv of the descriptor
// *           will be reset to default. if this block is not first block
// *           then uses the hash vaule as the default iv.
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//int MCP_SHA256_DataHash(
//    unsigned char*          p_data,
//    unsigned long           data_len,
//    unsigned char           hash[SHA1_DIGEST_SIZE],
//    unsigned long           block_size,
//    unsigned char           block_status
//    )
//{
//    mcp_desc desc;
//    int      ret = 0;
//
//    MCP_SHA256_HASH_INIT(&desc);
//
//    // to simplify the implementation, we have made some constrains over here
//    // 1) the data_len must be multiple if 64 Bytes
//    // 2) the block size must be multiple if 64 Bytes
//    // 3) the data_len must be multiple if block size excepts the last block
//    if (data_len & SHA256_ALIGNMENT_CHECK)
//    {
//        mcp_warning("compute SHA256 hash value failed - data_len (%lu) should be multiple of 64 bytes\n", data_len);
//        return -1;
//    }
//
//    if (block_size & SHA256_ALIGNMENT_CHECK)
//    {
//        mcp_warning("compute SHA256 hash value failed - block size (%lu) should be multiple of 64 bytes\n", block_size);
//        return -1;
//    }
//
//    if (!(block_status & LAST_BLOCK) && (data_len % block_size))
//    {
//        mcp_warning("compute SHA256 hash value failed - data_len (%lu) should be multiple of block size (%lu) excepts the last block\n", data_len, block_size);
//        return -1;
//    }
//
//    //--------------
//    if (!(block_status & FIRST_BLOCK))
//        MCP_SHA1_IV_UPDATE(&desc, hash);    // Setup the initial value of SHA1 Hash Value
//
//    while(data_len && !ret)
//    {
//        if (data_len > block_size)
//        {
//            ret       = MCP_SHA256_Hashing(&desc, p_data, block_size, hash);
//            data_len -= block_size;
//            p_data   += block_size;
//        }
//        else
//        {
//            ret       = MCP_SHA256_Hashing(&desc, p_data, data_len, hash);
//            p_data   += data_len;
//            data_len = 0;
//        }
//
//        MCP_SHA256_IV_UPDATE(&desc, hash);  // Update Hash Value
//    }
//
//    return ret;
//}
//
//
//#endif
//
//
/***************************************************************************
            ------------------- MISC ----------------
****************************************************************************/



/*------------------------------------------------------------------
 * Func : mcp_malloc
 *
 * Desc : allocate memory
 *
 * Parm : size      : size of data
 *
 * Retn : start address of data
 *------------------------------------------------------------------*/
//void* mcp_malloc(
//  unsigned long           size
//  )
//{
//#ifdef USE_DVR_MALLOC
//    return (size >= PAGE_SIZE) ? (void*) dvr_malloc(size)
//                               : (void*) kmalloc(size, GFP_KERNEL);
//#else
//    return (size >= PAGE_SIZE) ? (void*) __get_free_pages(GFP_KERNEL, get_order(size))
//                               : (void*) kmalloc(size, GFP_KERNEL) ;
//#endif
//}




/*------------------------------------------------------------------
 * Func : mcp_free
 *
 * Desc : release memory
 *
 * Parm : addr      : Start address of data
 *        size      : size of data
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
void mcp_free(
    void*                   addr,
    unsigned long           size)
{
//    if (size >= PAGE_SIZE)
//#ifdef USE_DVR_MALLOC
//        dvr_free(addr);
//#else
//        free_pages((unsigned long)addr, get_order(size));
//#endif
//    else
//        kfree(addr) ;
    free(addr);
}



///*----------------------------------------------------------------------
// * Func : mcp_dump_mem
// *
// * Desc : dump data in memory
// *
// * Parm : data : start address of data
// *        len  : length of data
// *
// * Retn : N/A
// *----------------------------------------------------------------------*/
//void mcp_dump_mem(
//  unsigned char*      data,
//  unsigned int            len)
//{
//    int i;
//    for (i=0; i<len; i++)
//    {
//        if ((i & 0xF)==0)
//            printk("\n %04x | ", i);
//        printk("%02x ", data[i]);
//    }
//    printk("\n");
//}
//
//
//
///***************************************************************************
//            ------------------- Auto Test ----------------
//****************************************************************************/
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_H_DataHashTest
// *
// * Desc : Compute hash value of Data via 128 bits AES_H_Hasing
// *
// * Parm : pData      : Start address of data
// *        DataLen    : Length of data
// *        Hash[16]   : 128 bits hash value of the file
// *        BlockSize  : Block Size that used to compute Hashing Value
// *
// * Retn : S_OK  /  S_FALSE
// *------------------------------------------------------------------*/
//void MCP_AES_H_DataHashTest(void)
//{
//    unsigned char Data[256];
//    unsigned char Hash[16];
//
//    memset(Data, 0x33, sizeof(Data));
//
//    MCP_AES_H_DataHash(Data,  sizeof(Data), Hash, AES_H_FILE_HASHING_BUFFER_SIZE, 1);
//
//    mcp_dump_data_with_text(Hash, 16, "hash value : ");
//}
//
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_128_ECB_DataEncryptTest
// *
// * Desc : Test AES 128 ECB
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//void MCP_AES_128_ECB_DataEncryptTest(void)
//{
//    unsigned char Data[16]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
//                              0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
//    unsigned char Key[16];
//
//    memset(Key, 0xff, sizeof(Key));
//
//    MCP_AES_ECB_Encryption(Key, Data, Data, 16);
//
//    mcp_dump_data_with_text(Data, 16, "encrypted value : ");
//
//    MCP_AES_ECB_Decryption(Key, Data, Data, 16);
//
//    mcp_dump_data_with_text(Data, 16, "decrypted value : ");
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_AES_128_CTR_DataEncryptTest
// *
// * Desc : Test AES 128 CTR
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//void MCP_AES_128_CTR_DataEncryptTest(void)
//{
//    unsigned char Data[16]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
//                              0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
//    unsigned char Key[16];
//    unsigned char IV[16];
//
//    memset(Key, 0xff, sizeof(Key));
//    memset(IV,    0, sizeof(IV));
//
//    mcp_dump_data_with_text(Data, 16, "org data value : ");
//    mcp_dump_data_with_text(Key,  16, "key value : ");
//    mcp_dump_data_with_text(IV,   16, "iv value : ");
//
//    //--------encryption test----------------------
//    MCP_AES_CTR_Encryption(Key, IV, Data, Data, 16);
//
//    mcp_dump_data_with_text(Data, 16, "aes_ctr_encrypted value : ");
//
//    MCP_AES_PeekIV(IV);
//
//    mcp_dump_data_with_text(IV, 16, "new iv value : ");
//
//    //--------decryption test----------------------
//    memset(IV, 0, sizeof(IV));
//
//    MCP_AES_CTR_Decryption(Key, IV, Data, Data, 16);
//
//    mcp_dump_data_with_text(Data, 16, "aes_ctr_decrypted value : ");
//
//    MCP_AES_PeekIV(IV);
//
//    mcp_dump_data_with_text(IV, 16, "new iv value : ");
//}
//
//
//
//
///*------------------------------------------------------------------
// * Func : MCP_SHA1_DataHashTest
// *
// * Desc : Compute hash value of Data via 128 bits AES_H_Hasing
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//void MCP_SHA1_DataHashTest(void)
//{
//    unsigned char data[256 + 64];
//    unsigned char hash[SHA1_DIGEST_SIZE];
//    mcp_desc desc;
//    int pad_sz;
//
//    memset(data, 0x33, 256);
//
//    MCP_SHA1_HASH_INIT(&desc);
//
//    mcp_dump_data_with_text(data, 256, "[MCP] data before padding data...\n");
//
//    pad_sz = MCP_SHA1_PADDING(&data[256], 64, 256);
//
//    mcp_dump_data_with_text(data, 256 + pad_sz, "[MCP] data after padding data...\n");
//
//    MCP_SHA1_Hashing(&desc, data, pad_sz + 256, hash);
//
//    mcp_dump_data_with_text(hash, SHA1_DIGEST_SIZE, "[MCP] SHA1 hash : ");
//}
//
//
//
///***************************************************************************
//         ------------------- File Operations ----------------
//****************************************************************************/
//
//
//
///*------------------------------------------------------------------
// * Func : mcp_dev_open
// *
// * Desc : open function of mcp dev
// *
// * Parm : inode : inode of dev
// *        file  : context of file
// *
// * Retn : 0 : success, others fail
// *------------------------------------------------------------------*/
//static
//int mcp_dev_open(
//  struct inode*       inode,
//  struct file*            file)
//{
//    file->private_data = mcp_malloc(sizeof(mcp_desc) * MCP_DESC_ENTRY_COUNT);
//    if (file->private_data==NULL)
//    {
//        mcp_warning("open mcp failed - allocate mcp descriptor buffer failed\n");
//        return -ENOMEM;
//    }
//
//    return 0;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : mcp_dev_release
// *
// * Desc : release function of mcp dev
// *
// * Parm : inode : inode of dev
// *        file  : context of file
// *
// * Retn : 0 : success, others fail
// *------------------------------------------------------------------*/
//static
//int mcp_dev_release(
//    struct inode*         inode,
//    struct file*          file
//    )
//{
//    if (file->private_data)
//        mcp_free(file->private_data, sizeof(mcp_desc) * MCP_DESC_ENTRY_COUNT);
//  return 0;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : mcp_dev_ioctl
// *
// * Desc : ioctl function of mcp dev
// *
// * Parm : inode : inode of dev
// *        file  : context of file
// *        cmd   : control command
// *        arg   : arguments
// *
// * Retn : 0 : success, others fail
// *------------------------------------------------------------------*/
//static
//long mcp_dev_ioctl(
//    struct file*          file,
//    unsigned int          cmd,
//    unsigned long         arg
//    )
//{
//    mcp_desc_set desc_set;
//    mcp_desc desc_list[MCP_DESC_ENTRY_COUNT];
//    mcp_desc* p_desc;
//    int n_desc;
//
//  switch (cmd)
//    {
//      case MCP_IOCTL_DO_COMMAND:
//      {
//          if (copy_from_user(&desc_set, (mcp_desc_set __user *)arg, sizeof(mcp_desc_set)))
//          {
//              mcp_warning("do ioctl command failed - copy desc_set from user failed\n");
//              return -EFAULT;
//              }
//          p_desc = desc_set.p_desc;
//
//          while(desc_set.n_desc)
//          {
//              n_desc = (desc_set.n_desc >= MCP_DESC_ENTRY_COUNT) ? MCP_DESC_ENTRY_COUNT
//                                                                                          : desc_set.n_desc;
//
//              if (copy_from_user(desc_list, (mcp_desc __user *)p_desc, sizeof(mcp_desc) * n_desc))
//              {
//                  mcp_warning("do ioctl command failed - copy desc from user failed\n");
//                  return -EFAULT;
//                  }
//
//              if (mcp_do_command(desc_list, n_desc)<0)
//              {
//                  mcp_warning("do command failed\n");
//                  return -EFAULT;
//              }
//
//            p_desc          += n_desc;
//              desc_set.n_desc -= n_desc;
//          }
//          break;
//      }
//      //-----------------------------------
//      // for testing only
//      //-----------------------------------
//      case MCP_IOCTL_TEST_AES_H:
//          MCP_AES_H_DataHashTest();
//          break;
//
//      default:
//          mcp_warning("do ioctl command failed - unknown ioctl command(%d)\n", cmd);
//          return -EFAULT;
//    }
//
//    return 0;
//}
//
//
//
//static struct file_operations mcp_ops =
//{
//  .owner              = THIS_MODULE,
//  .unlocked_ioctl = mcp_dev_ioctl,
//  .open               = mcp_dev_open,
//  .release            = mcp_dev_release,
//};
//
//
//
///***************************************************************************
//         ------------------- Power Management ----------------
//****************************************************************************/
//
//#ifdef CONFIG_PM
//
//
//static struct platform_device*  mcp_platform_dev = NULL;
//
//static int mcp_probe(
//  struct device       *dev
//  )
//{
//    struct platform_device  *pdev = to_platform_device(dev);
//    mcp_info("mcp device detected ...\n");
//    return strncmp(pdev->name,MCP_DEVICE_NAME, sizeof(MCP_DEVICE_NAME));
//}
//
//
//static int mcp_remove(
//  struct device       *dev
//  )
//{
//    return 0;
//}
//
//static void mcp_shutdown(
//  struct device       *dev
//  )
//{
//}
//
//static int mcp_pm_suspend_noirq(
//  struct device       *dev
//  )
//{
//    mcp_info("suspended\n");
//    return 0;
//}
//
//static int mcp_pm_resume_noirq(
//  struct device       *dev
//  )
//{
//    mcp_info("resumed\n");
//    _mcp_phy_init();        // reset MCP phy
//    return 0;
//}
//
//static const struct dev_pm_ops mcp_pm_ops = {
//    .suspend_noirq    = mcp_pm_suspend_noirq,
//    .resume_noirq         = mcp_pm_resume_noirq,
//};
//
//
//static struct platform_driver mcp_platform_drv =
//{
//    .driver = {
//        .name         = MCP_DEVICE_NAME,
//        .bus      = &platform_bus_type,
//        .probe        = mcp_probe,
//        .remove       = mcp_remove,
//        .shutdown     = mcp_shutdown,
//#ifdef CONFIG_PM
//        .pm           = &mcp_pm_ops,
//#endif
//    }
//};
//
//
//#endif
//
//
//
///***************************************************************************
//     ------------------- module init / exit stubs ----------------
//****************************************************************************/
//
//struct class *mcp_dev_class = NULL;
//
//
///*------------------------------------------------------------------
// * Func : mcp_init
// *
// * Desc : mcp module init function
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//static int __init mcp_module_init(void)
//{
//    if (mcp_init()<0)
//        return -ENODEV;
//
//    cdev_init(&mcp_dev, &mcp_ops);
//
//    if (alloc_chrdev_region(&devno, 0, 1, MCP_DEVICE_NAME)!=0)
//    {
//        cdev_del(&mcp_dev);
//        return -EFAULT;
//    }
//
//    if (cdev_add(&mcp_dev, devno, 1)<0)
//        return -EFAULT;
//
//    mcp_dev_class = class_create(THIS_MODULE, "mcp");       // create a new class for mcp
//
//    mcp_device = device_create(
//                    mcp_dev_class,      // class
//                    NULL,               // parent
//                  devno,              // dev number
//                  NULL,               // driver data
//                  "mcp_core");      // device name
//
//    //MCP_AES_128_CTR_DataEncryptTest();
//    //MCP_AES_H_DataHashTest();
//    //MCP_SHA1_DataHashTest();
//
//#ifdef CONFIG_PM
//    mcp_platform_dev = platform_device_register_simple(MCP_DEVICE_NAME, 0, NULL, 0);
//    platform_driver_register(&mcp_platform_drv);              // regist mcp driver
//#endif
//
//    return 0;
//}
//
//
//
///*------------------------------------------------------------------
// * Func : mcp_module_exit
// *
// * Desc : mcp module exit function
// *
// * Parm : N/A
// *
// * Retn : N/A
// *------------------------------------------------------------------*/
//static void __exit mcp_module_exit(void)
//{
//    device_destroy(mcp_dev_class, mcp_device->devt);       // remove device
//#ifdef CONFIG_PM
//    platform_device_unregister(mcp_platform_dev);
//    platform_driver_unregister(&mcp_platform_drv);
//#endif
//    cdev_del(&mcp_dev);
//
//    unregister_chrdev_region(devno, 1);
//
//    mcp_uninit();
//}
//
//
//module_init(mcp_module_init);
//module_exit(mcp_module_exit);
