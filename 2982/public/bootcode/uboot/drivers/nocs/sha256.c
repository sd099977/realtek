#include "nocs_bsd_env.h"
#include "print_rpc.h"
#include "mcp.h"
#include "mcp_buff.h"
#include "mcp_dgst.h"


typedef struct {
    mcp_buff*               tmp;
    unsigned long long      byte_count;
    unsigned char           hash[SHA256_DIGEST_SIZE];
}SHA256_CTX;

extern void rtk_show_data(unsigned char ch_line,unsigned int d_len,
                   void* d_buf,unsigned int type_ctl,unsigned char * message );
void SHA256_CTX_Init(SHA256_CTX* ctx)
{
	BDPRINT_FUNC();
	BD_INFO("ctx = 0x%p\n",ctx);
	BD_INFO("head=0x%p; data=0x%p; tail=0x%p; end=0x%p; len=%ld\n",
			ctx->tmp->head,
			ctx->tmp->data,
			ctx->tmp->tail,
			ctx->tmp->end,
			ctx->tmp->len);

    static const unsigned char SHA256InitHash[SHA256_DIGEST_SIZE] = {
        0x6a, 0x09, 0xe6, 0x67, 0xbb, 0x67, 0xae, 0x85,
        0x3c, 0x6e, 0xf3, 0x72, 0xa5, 0x4f, 0xf5, 0x3a,
        0x51, 0x0e, 0x52, 0x7f, 0x9b, 0x05, 0x68, 0x8c,
        0x1f, 0x83, 0xd9, 0xab, 0x5b, 0xe0, 0xcd, 0x19,
    };

    memcpy(ctx->hash, SHA256InitHash, SHA256_DIGEST_SIZE);     // Init Hash value
    ctx->byte_count = 0;
    BD_INFO("ctx->tmp=0x%p\n",ctx->tmp);
    mcpb_purge(ctx->tmp);
    BD_INFO("\n");
}

/*------------------------------------------------------------------
 * Func : SHA256_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
//#define CONFIG_USE_BOOT_MCP
int SHA256_DigestInit(MCP_MD_CTX* ctx)
{
    SHA256_CTX* p_SHA256 = NULL;
    BDPRINT_FUNC();

	p_SHA256 = (SHA256_CTX*)malloc(sizeof(SHA256_CTX));
	ctx->md_data = p_SHA256;

	//p_SHA256 = (SHA256_CTX*) ctx->md_data;
	BD_INFO("p_SHA256 = 0x%p\n",p_SHA256);
    if (p_SHA256)
    {
    	BD_INFO("\n");
    	// alloc a buffer that used to restore short block
        p_SHA256->tmp = alloc_mcpb(64);	//64 is kernel setting
/*
p_SHA256->tmp 基本上配置了一個  mcp_buff 要用的記憶體,
前面是struct mcp_buff,後面緊接著預先配置的記憶空間,
struct mcp_buff中的成員指標用來標示出記憶體不同位置的用途,
*/
        BD_INFO("p_SHA256->tmp=0x%p\n",p_SHA256->tmp);
        if (!p_SHA256->tmp)
            return -1;

        SHA256_CTX_Init(p_SHA256);
        return 0;
    }
	BD_INFO("\n");
    return -1;
}


/*------------------------------------------------------------------
 * Func : SHA256_DigestUpdate
 *
 * Desc : Update SHA256 Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   :
 *        DataLen : Data Length
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
extern int SHA256_hash( unsigned char * src_addr,
						unsigned int 	length,
						unsigned char *	dst_addr,
						unsigned int 	iv[8]);

int SHA256_DigestUpdate(
    MCP_MD_CTX*             ctx,
    MCP_BUFF*               mcpb
    )
{
	//int i;
	int ret = 0;
	//unsigned char * ptr8;
    SHA256_CTX* p_SHA256 = (SHA256_CTX*) ctx->md_data;
    mcp_desc *desc = malloc(128);

	BDPRINT_FUNC();

	BD_INFO("ctx  = 0x%p\n",ctx);
	BD_INFO("mcpb = 0x%p\n",mcpb);
	BD_INFO("p_SHA256 = 0x%p\n",p_SHA256);
	BD_INFO("p_SHA256->hash = 0x%p\n",p_SHA256->hash);

	BD_INFO("\n");

	rtk_show_data(8,32,(void *)(p_SHA256->hash),0,
       			  (unsigned char *)"show p_SHA256->hash");

    MCP_SHA256_HASH_INIT(desc);

    MCP_SHA256_IV_UPDATE(desc, p_SHA256->hash);    // Setup the initial value of SHA256 Hash Value

    //-----------------------------------------------
    // short block handling
    //-----------------------------------------------
	BD_INFO("p_SHA256->tmp->len = %ld\n",p_SHA256->tmp->len);
	BD_INFO("mcpb->len = %ld\n",mcpb->len);
    if (p_SHA256->tmp->len)
    {
    	BD_INFO("\n");
        mcpb_push(mcpb, p_SHA256->tmp->len);
        memcpy(mcpb->data, p_SHA256->tmp->data, p_SHA256->tmp->len);
        mcpb_purge(p_SHA256->tmp);                                     // clean data buffer
    }

    if (mcpb->len > 64)
    {
        //mcp_dump_data_with_text(mcpb->data, mcpb->len, "data to proc ...");
		BD_INFO("\n");

		BD_INFO("desc=0x%p; p_in=0x%p; p_out=0x%p; len=%ld[0x%lx] \n",
    		     desc,mcpb->data,p_SHA256->hash,
    		     (mcpb->len) & ~0x3F,(mcpb->len) & ~0x3F);

		// compute new hash value
#ifndef CONFIG_USE_BOOT_MCP
        ret = MCP_SHA256_Hashing(desc, mcpb->data, mcpb->len & ~0x3F, p_SHA256->hash);
#else
		ret = SHA256_hash( mcpb->data,(unsigned int)(mcpb->len & ~0x3F),p_SHA256->hash,NULL);
#endif
		if(ret){
			BD_INFO("SHA256_hash fail!!!\n");
		}else{
			BD_INFO("p_SHA256->hash=0x%p\n",p_SHA256->hash);
			rtk_show_data(8,32,(void *)(p_SHA256->hash),0,
       			          (unsigned char *)"show p_SHA256->hash");
		}

        p_SHA256->byte_count += mcpb->len & ~0x3F;
        mcpb_pull(mcpb, mcpb->len & ~0x3F);
    }

    //-----------------------------------------------
    // short block handling - backup imcomplete data block
    //-----------------------------------------------
    if (mcpb->len)
    {
    	BD_INFO("\n");
        memcpy(p_SHA256->tmp->data, mcpb->data ,mcpb->len);
        mcpb_put(p_SHA256->tmp, mcpb->len);
    }
	if(desc)
		free(desc);

    return 0;
}

/*------------------------------------------------------------------
 * Func : SHA256_DigestFinal
 *
 * Desc : Finished SHA256 Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
#if 1

int SHA256_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    )
{
	//int i;
	//int ret = 0;
	//unsigned char * ptr8;
    SHA256_CTX* p_SHA256 = (SHA256_CTX*) ctx->md_data;
    int pad_sz;

	BDPRINT_FUNC();

    mcp_desc *desc = malloc(128);

    // Setup the initial value of SHA256 Hash Value
    MCP_SHA256_HASH_INIT(desc);

    // resetting the initial value if last SHA operation active.
    MCP_SHA256_IV_UPDATE(desc, p_SHA256->hash);

    pad_sz = MCP_SHA256_PADDING(p_SHA256->tmp->tail,
    							mcpb_tailroom(p_SHA256->tmp),
    							p_SHA256->byte_count + p_SHA256->tmp->len);           // byte count = proccessed byte count + unproced byte count

    mcpb_put(p_SHA256->tmp, pad_sz);

    if(1){
    	BDPRINT("p_SHA256->tmp->len=%d\n",(unsigned int)(p_SHA256->tmp->len));
    	rtk_show_data(8,(unsigned int)(p_SHA256->tmp->len),
    				  (void *)(p_SHA256->tmp->data),0,
    				  (unsigned char *)"Show p_SHA256->tmp->data");
    }

#ifndef CONFIG_USE_BOOT_MCP
    MCP_SHA256_Hashing( desc,
    					p_SHA256->tmp->data,
    					p_SHA256->tmp->len,
    					p_SHA256->hash);     // compute new hash value

    BD_INFO("p_SHA256->hash[0x%p]\n",p_SHA256->hash);
    rtk_show_data(8,32,(void *)(p_SHA256->hash),0,
       			  (unsigned char *)"Show p_SHA256->hash");
#else

    if(1){
    	unsigned char* sha_arry;
		unsigned char* sha_arry_ali = malloc(100);
		//unsigned char* sha_arry_ali = malloc_noncache(100);

//#define CONFIG_USE_TEST_ARRY
#ifdef CONFIG_USE_TEST_ARRY

    	unsigned char* sha_out 		= malloc(64);
		//unsigned char* sha_out 		= malloc_noncache(64);

    	memset(sha_out,0,64);
#endif
		memset(sha_arry_ali,0,100);

		sha_arry = (unsigned char*)((unsigned int)sha_arry_ali & 0xfffffff8);

#ifdef CONFIG_USE_TEST_ARRY
    	unsigned char sha_buf[64]={
		0x0e, 0x77, 0xf3, 0xc8, 0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20};

		BD_INFO("sha_buf= 0x%p;sha_arry=0x%p;sha_arry_ali=0x%p\n",
				sha_buf,sha_arry,sha_arry_ali);
		memcpy((void*)sha_arry,(void*)sha_buf,64);
#else
		memcpy((void*)sha_arry,(void*)p_SHA256->tmp->data,64);
#endif

		BD_INFO("\n");
		rtk_show_data(8,64,(void *)(sha_arry),0,
       			  	  (unsigned char *)"show sha_arry");

#ifdef CONFIG_USE_TEST_ARRY
		rtk_show_data(8,32,(void *)(sha_out),0,
       			  	  (unsigned char *)"show sha_out");
#else
		rtk_show_data(8,32,(void *)(p_SHA256->hash),0,
       			  	  (unsigned char *)"Show p_SHA256->hash[]");
#endif

#ifdef BSD_HANDEL_CACHE
		flush_cache((unsigned long)sha_arry, 64);
		invalidate_dcache_range((unsigned long)sha_out,
						(unsigned long)((unsigned int)sha_out+32 ));
#endif

#ifdef CONFIG_USE_TEST_ARRY
    	ret = SHA256_hash( sha_arry,32,sha_out,NULL);
#else
    	ret = SHA256_hash( sha_arry,32,p_SHA256->hash,NULL);
#endif

	    if(ret){
			BD_INFO("SHA256_hash fail!!!\n");
		}else{
			BD_INFO("p_SHA256->hash=0x%p\n",p_SHA256->hash);

			BD_INFO("\n");
#ifdef CONFIG_USE_TEST_ARRY
			BD_INFO("sha_out[0x%p]\n",sha_out);
			rtk_show_data(8,32,(void *)(sha_out),0,
       			  	  (unsigned char *)"Show sha_out[]");
#else
			BD_INFO("p_SHA256->hash[0x%p]\n",p_SHA256->hash);
			rtk_show_data(8,32,(void *)(p_SHA256->hash),0,
       			  	  (unsigned char *)"p_SHA256->hash[]");
#endif
		}

#ifdef CONFIG_USE_TEST_ARRY
		if(sha_out)
			free(sha_out);
#endif
    	if(sha_arry_ali)
    		free(sha_arry_ali);

	}
#endif	//?CONFIG_USE_BOOT_MCP
	BD_INFO("\n");
    memcpy(pHash, p_SHA256->hash, SHA256_DIGEST_SIZE);
	BD_INFO("\n");

    //---------------------- reset ctx -------------------
    SHA256_CTX_Init(p_SHA256);

	BD_INFO("why\n");
	if(desc)
    	free(desc);
	BD_INFO("why why\n");
    return 0;
}

#endif

#if 1
/*------------------------------------------------------------------
 * Func : SHA256_DigestCleanup
 *
 * Desc : Clean up SHA256 context
 *
 * Parm : ctx  : context of md ctx
 *
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestCleanup(MCP_MD_CTX* ctx)
{
    SHA256_CTX* p_SHA256 = (SHA256_CTX*) ctx->md_data;

    BDPRINT_FUNC();
    memset(p_SHA256, 0, sizeof(SHA256_CTX));
    free_mcpb(p_SHA256->tmp);

    return 0;
}
#endif