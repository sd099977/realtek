#include "nocs_bsd_env.h"
#include "print_rpc.h"
#include "mcp.h"
#include "mcp_buff.h"

void CHECK_BOUNDRARY(mcp_buff* mcpb)
{
	BDPRINT_FUNC();
	BD_INFO("mcpb = 0x%p; \n",mcpb);
    if (mcpb->data < mcpb->head || mcpb->tail > mcpb->end  || mcpb->tail < mcpb->data)
    {

        BD_INFO("Errrrrrrrrrrrr mcpb(%p) : head=%p, data=%p, tail=%p, end=%p\n",
                mcpb, mcpb->head, mcpb->data, mcpb->tail, mcpb->end);

    }
}


/*----------------------------------------------------------------------
 * Func : __alloc_mcpb
 *
 * Desc : alloc a mcp buffer with specified length
 *
 * Parm : len : size of mcp buffer
 *
 * Retn : handle of mcp buffer
 *----------------------------------------------------------------------*/
static mcp_buff* __alloc_mcpb(unsigned int len)
{
/*
這裏將會實際配置記憶體,而且除了傳入的長度,會再加上 struct mcp_buff的大小
記憶體配置完成後,會對結構中的一些指標進行賦值
*/

	unsigned int mcp_buff_len;
	BDPRINT_FUNC();
	BD_INFO("len = %d\n",len);
    mcp_buff* p_buff;

	mcp_buff_len = sizeof(mcp_buff);
    len += sizeof(mcp_buff);
/*

*/
    BD_INFO("len = %d[%d]\n",len,mcp_buff_len);

    //p_buff = (mcp_buff*) mcp_malloc(len);
    p_buff = (mcp_buff*) malloc(len);
    BD_INFO("p_buff = 0x%p\n",p_buff);

    if (p_buff)
    {
        BD_INFO("[MCP][BUF] Alloc Buffer %p (len = %d)\n", p_buff, len);
        p_buff->head = (unsigned char*) p_buff + sizeof(mcp_buff);
        p_buff->data = p_buff->head;
        p_buff->tail = p_buff->head;
        p_buff->end  = (p_buff->head + len) - sizeof(mcp_buff);
        p_buff->len  = 0;
        BD_INFO("head=0x%p; data=0x%p; tail=0x%p; end=0x%p; len=%d\n",
        		 p_buff->head,p_buff->data,p_buff->tail,p_buff->end,len);
    }

/*
p_buff裏幾個指標的賦值是從 struct mcp_buff長度的位置之後開始賦值

*/
    return p_buff;
}




/*----------------------------------------------------------------------
 * Func : alloc_mcpb
 *
 * Desc : alloc a mcp buffer with specified length
 *
 * Parm : len : size of mcp buffer
 *
 * Retn : handle of mcp buffer
 *----------------------------------------------------------------------*/
mcp_buff* alloc_mcpb(unsigned int len)
{
/*
這裏會呼叫 __alloc_mcpb()函式,配置的記憶體為原本的設定值,
再加上 MCP_BUFF_RESERVE_AREA(256)
*/
    mcp_buff* mcpb = __alloc_mcpb(len + MCP_BUFF_RESERVE_AREA);
    BDPRINT_FUNC();
	BD_INFO("MCP_BUFF_RESERVE_AREA = %d\n",MCP_BUFF_RESERVE_AREA);

    if (!mcpb)
    {
        BD_INFO("Errrr Alloc MCP Buffer failed, size to request = %d", (int) len + MCP_BUFF_RESERVE_AREA);
        return NULL;
    }

	BD_INFO("\n");

/*
mcpb_reserve()函式,會將
mcpb->data += len;
mcpb->tail += len
這裏的len是MCP_BUFF_HEAD_RESERVE(128),也就是預留128 bytes給head的範圍
*/

    mcpb_reserve(mcpb, MCP_BUFF_HEAD_RESERVE);
	BD_INFO("\n");
    return mcpb;

/*
呼叫這個函式後,會配置 "指定大小+MCP_BUFF_RESERVE_AREA(256)+sizeof(mcp_buff)"
大小的記憶體區塊,同對初始化mcp_buff 資料結構的的指標,
mcpb->head = mcpb+sizeof(mcp_buff)
mcpb->data = mcpb->head + MCP_BUFF_HEAD_RESERVE(128)
mcpb->tail = mcpb->head + MCP_BUFF_HEAD_RESERVE(128)
mcpb->end  = mcpb->head + total_len - sizeof(mcp_buff); <==用來指示此記憶體區段的最後位置
*/
}




/*----------------------------------------------------------------------
 * Func : free_mcpb
 *
 * Desc : free a mcp buffer with specified length
 *
 * Parm : mcpb : mcp buffer to be free
 *
 * Retn : N/A
 *----------------------------------------------------------------------*/
void free_mcpb(mcp_buff* mcpb)
{
    unsigned long len;
	BDPRINT_FUNC();
    if (mcpb)
    {
        len = (unsigned long) mcpb->end - (unsigned long) mcpb;

        //mcpb_dbg("Free Buffer %p (len = %ul)\n", mcpb, len);

        mcp_free((void*)mcpb, len);
    }
}



/*----------------------------------------------------------------------
 * Func : mcpb_reserve
 *
 * Desc : reserve an area in front of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *        len : size to reserve
 *
 * Retn : N/A
 *----------------------------------------------------------------------*/
void mcpb_reserve(mcp_buff* mcpb, unsigned int len)
{
	BDPRINT_FUNC();
	BD_INFO("len = %d[0x%x]\n",len,len);
	BD_INFO("mcpb = 0x%p; \n",mcpb);
	BD_INFO("data = 0x%p; tail=0x%p\n",mcpb->data,mcpb->tail);
    mcpb->data += len;
    mcpb->tail += len;
    BD_INFO("data = 0x%p; tail=0x%p\n",mcpb->data,mcpb->tail);
    CHECK_BOUNDRARY(mcpb);
}



/*----------------------------------------------------------------------
 * Func : mcpb_put
 *
 * Desc : put data from tail of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *        len : size to put
 *
 * Retn : previous buffer tail
 *----------------------------------------------------------------------*/
unsigned char* mcpb_put(mcp_buff* mcpb, unsigned int len)
{
    unsigned char* ptr = mcpb->tail;

    BDPRINT_FUNC();
    mcpb->tail += len;
    mcpb->len  += len;
    CHECK_BOUNDRARY(mcpb);
    return ptr;
}



///*----------------------------------------------------------------------
// * Func : mcpb_trim
// *
// * Desc : remove data from tail of mcp buffer
// *
// * Parm : mcpb : mcp buffer
// *        len : size to remove
// *
// * Retn : N/A
// *----------------------------------------------------------------------*/
//void mcpb_trim(mcp_buff* mcpb, unsigned int len)
//{
//    mcpb->tail -= len;
//    mcpb->len  -= len;
//    CHECK_BOUNDRARY(mcpb);
//}
//
//
//
/*----------------------------------------------------------------------
 * Func : mcpb_push
 *
 * Desc : push data to the front of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *        len : size to push
 *
 * Retn : new start address of mcp buffer data
 *----------------------------------------------------------------------*/
unsigned char* mcpb_push(mcp_buff *mcpb, unsigned int len)
{
	BDPRINT_FUNC();

    mcpb->data -= len;
    mcpb->len  += len;
    CHECK_BOUNDRARY(mcpb);
    return mcpb->data;
}



/*----------------------------------------------------------------------
 * Func : mcpb_pull
 *
 * Desc : remove data from the front of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *        len : size to pull
 *
 * Retn : new start address of mcp buffer data
 *----------------------------------------------------------------------*/
unsigned char* mcpb_pull(mcp_buff *mcpb, unsigned int len)
{
	BDPRINT_FUNC();

    if (len <= mcpb->len)
    {
        mcpb->data += len;
        mcpb->len  -= len;
        return mcpb->data;
    }
    return NULL;
}



/*----------------------------------------------------------------------
 * Func : __mcpb_purge
 *
 * Desc : clear all data of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *
 * Retn : N/A
 *----------------------------------------------------------------------*/
void __mcpb_purge(mcp_buff* mcpb)
{
	BDPRINT_FUNC();
	BD_INFO("mcpb = 0x%p\n",mcpb);
	BD_INFO("mcpb->head = 0x%p\n",mcpb->head);
	BD_INFO("mcpb->data = 0x%p\n",mcpb->data);
	BD_INFO("mcpb->tail = 0x%p\n",mcpb->tail);
    mcpb->data = mcpb->head;
    mcpb->tail = mcpb->head;
    BD_INFO("mcpb->data = 0x%p\n",mcpb->data);
	BD_INFO("mcpb->tail = 0x%p\n",mcpb->tail);
    mcpb->len  = 0;
}


/*----------------------------------------------------------------------
 * Func : mcpb_purge
 *
 * Desc : clear all data of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *
 * Retn : N/A
 *----------------------------------------------------------------------*/
void mcpb_purge(mcp_buff* mcpb)
{
	BDPRINT_FUNC();
	BD_INFO("mcpb = 0x%p\n",mcpb);
	BD_INFO("head=0x%p; data=0x%p; tail=0x%p; end=0x%p; len=%ld\n",
			mcpb->head,
			mcpb->data,
			mcpb->tail,
			mcpb->end,
			mcpb->len);

    __mcpb_purge(mcpb);
    mcpb_reserve(mcpb, MCP_BUFF_HEAD_RESERVE);
}



///*----------------------------------------------------------------------
// * Func : mcpb_headroom
// *
// * Desc : get head room of mcp buffer
// *
// * Parm : mcpb : mcp buffer
// *
// * Retn : size of head room of mcpb
// *----------------------------------------------------------------------*/
//int mcpb_headroom(mcp_buff* mcpb)
//{
//    return mcpb->data - mcpb->head;
//}
//
//
//
/*----------------------------------------------------------------------
 * Func : mcpb_tail_room
 *
 * Desc : get tail room of mcp buffer
 *
 * Parm : mcpb : mcp buffer
 *
 * Retn : size of tail room of mcpb
 *----------------------------------------------------------------------*/
int mcpb_tailroom(mcp_buff* mcpb)
{
	BDPRINT_FUNC();
    return (int) (mcpb->end - mcpb->tail);
}
//
//
////////////////////////////////////////////////////////////////////////////////
//// for debug .........
////////////////////////////////////////////////////////////////////////////////
//
//
//
///*----------------------------------------------------------------------
// * Func : _dump_data
// *
// * Desc : dump data in memory
// *
// * Parm : data : start address of data
// *        len  : length of data
// *
// * Retn : N/A
// *----------------------------------------------------------------------*/
//static void _dump_data(unsigned char* data, unsigned int len)
//{
//    int i;
//    for (i=0; i<len; i++)
//    {
//        if ((i & 0xF)==0)
//            printk("\n %04x | ", i);
//        printk("%02x ", data[i]);
//    }
//}
//
//
//
///*----------------------------------------------------------------------
// * Func : dump_mcpb_data
// *
// * Desc : dump data in mcp buffer
// *
// * Parm : mcpb : mcp buffer
// *
// * Retn : N/A
// *----------------------------------------------------------------------*/
//void dump_mcpb_data(mcp_buff* mcpb)
//{
//    printk("****************** mcpb (%p) ************************\n", mcpb);
//    _dump_data(mcpb->data, mcpb->len);
//    printk("\n\n");
//}
//
//
//
///*----------------------------------------------------------------------
// * Func : dump_mcpb_tail
// *
// * Desc : dump tail data in mcp buffer
// *
// * Parm : mcpb : mcp buffer
// *
// * Retn : N/A
// *----------------------------------------------------------------------*/
//void dump_mcpb_tail(mcp_buff* mcpb)
//{
//    printk("****************** mcpb (%p) ************************\n", mcpb);
//    _dump_data(mcpb->tail, mcpb_tailroom(mcpb));
//    printk("\n\n");
//}
