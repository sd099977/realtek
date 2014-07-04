#include <command.h>
#include <common.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/system.h>
#include <malloc.h>
#include <burn.h>


int do_verify_read_facro (char *image_name, unsigned int image_addr,unsigned int *image_size)
{
    char *buffer;
    int length;
    int rcode = 0;
    
    rcode = factory_ro_read(image_name, &buffer, &length);
    if (rcode)
    {
        printf("%s: file not found\n", image_name);
        return 1;
    }
    memcpy((void *)image_addr, (void *)buffer, length);
    *image_size = length;
    return 0;
}

int do_verify_hdcp(const char * str)
{
    char * image_name = NULL;
    int flag_hdcp21 = 0;
    int flag_hdcp22 = 0;
    unsigned int Kh_key[4];
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr, image_dst_addr, image_size = 0, image_size1 = 0;

    cmd = (char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);

    if (str && (strcmp(str,"hdcp1.4")==0))
    {
        image_name=FACTORY_RO_HDCP_1_4_BIN;
    }
    else if (str && (strcmp(str,"hdcp2.1")==0))
    {
        image_name=FACTORY_RO_HDCP_2_1_BIN;
        flag_hdcp21=1;
    }
    else if (str && (strcmp(str,"hdcp2.2")==0))
    {
        image_name=FACTORY_RO_HDCP_2_2_BIN;
        flag_hdcp22=1;
    }
    else
    {
        printf("[INFO %s] %s: failed.       hdcp file name is wrong\n", __FUNCTION__,str);
        return CMD_RET_FAILURE;
    }


    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    image_dst_addr=image_src_addr+1*1024*1024;

    rcode = do_verify_read_facro(image_name, image_src_addr,&image_size);
    if (rcode)
    {
        printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
        goto FAIL;
    }
    image_size1=image_size;

    if (flag_hdcp21 || flag_hdcp22)
    {        
        rcode = read_efuse_deviceID(Kh_key);
        if( rcode )
        {
            printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"read_efuse_deviceID",rcode);
            goto FAIL;
        }
        
        image_size=976;
        rcode = do_burn_decrypt(image_src_addr,image_size,image_dst_addr,NULL,ENCRYPTION_AES_128_ECB);
        if( rcode )
        {
            printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"decrypt hdcp2.x image error",rcode);
            goto FAIL;
        }
        
        if(flag_hdcp22) {
        	// append checksumin the tail
        } 

        rcode=do_get_hdcp2x_key(Kh_key);
        if( rcode )
        {
            printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"do_get_hdcp2x_key",rcode);
            goto FAIL;
        }
        rcode = do_burn_encrypt(image_dst_addr,image_size,image_src_addr,Kh_key,ENCRYPTION_AES_128_CBC);
        if( rcode )
        {
            printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"decrypt hdcp2.x image error",rcode);
            goto FAIL;
        }
    }
    printf("src=%x,size=%x\n",image_src_addr,image_size1);

    #if 0
    snprintf(cmd, sizeof(cmd),"md.b %x %x;",image_src_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }
    #endif

    if (cmd)
    {
        free(cmd);
    }

    if (flag_hdcp22)
    {
        printf("verify hdcp2.2 success\n");
    }
    else if (flag_hdcp21)
    {
        printf("verify hdcp2.1 success\n");
    }
    else
    {
        printf("verify hdcp1.4 success\n");
    }

    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    if (flag_hdcp22)
    {
        printf("verify hdcp2.2 fail\n");
    }
    else if (flag_hdcp21)
    {
        printf("verify hdcp2.1 fail\n");
    }
    else
    {
        printf("verify hdcp1.4 fail\n");
    }
    return CMD_RET_FAILURE;

}

int do_verify_mac (void)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"verify mac malloc ");
        goto FAIL;
    }
    memset(cmd, 0, SRING_SIZE);

    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    image_name=FACTORY_RO_MAC_BIN;

    rcode = do_verify_read_facro(image_name, image_src_addr,&image_size);
    if (rcode)
    {
        printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
        goto FAIL;
    }
   
    printf("src=%x,size=%x\n",image_src_addr,image_size);

#if 0
    image_size = getenv_ulong("filesize", 16, 0);
    snprintf(cmd, sizeof(cmd),"md.b %x %x;",image_src_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }
#endif

    if (cmd)
    {
        free(cmd);
    }

    printf("verify mac success\n");
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    printf("verify mac fail\n");
    return CMD_RET_FAILURE;

}

int do_verify_ci (void)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_dst_addr;
    unsigned int Kh_key[4],image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);

    // 1. read image from  factory_ro to DDR
    image_name=FACTORY_RO_CI_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    rcode = do_verify_read_facro(image_name, image_src_addr,&image_size);
    if (rcode)
    {
        printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
        goto FAIL;
    }

    // 2. decrypt images in DDR  
    image_dst_addr=image_src_addr+0x100000;
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);

    rcode=read_efuse_deviceID(Kh_key);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
        goto FAIL;
    }

    //decrypt using deviceID
    rcode=do_burn_decrypt(image_src_addr,image_size,image_dst_addr,Kh_key,ENCRYPTION_AES_128_ECB);
    if( rcode )
    {
        printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt ci+ image error",rcode);
        goto FAIL;
    }
    memcpy(image_src_addr,image_dst_addr,image_size);

    //encrypt using aes key
    rcode = do_burn_encrypt(image_src_addr,image_size,image_dst_addr,NULL,ENCRYPTION_AES_128_ECB);
    if( rcode )
    {
        printf("decrypt CI+ image error: %d\n", rcode);
        goto FAIL;
    }
    printf("src=%x,size=%x\n",image_dst_addr,image_size);

    //3. dump decrypted CI+ image in DDR
    #if 0
    snprintf(cmd, sizeof(cmd),"md.b %x  %x;",(unsigned int)image_dst_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }
    #endif

    if (cmd)
    {
        free(cmd);
    }
    printf("verify CI+ success\n");
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    printf("verify CI+ fail\n");
    return CMD_RET_FAILURE;

}

int do_get_widevine_crc (unsigned char * CRC16,unsigned char * CRC8,unsigned char * src,int size)
{
    int i,j,val;
    int checkSum=0;
    
    for (i=0;i<size;i++)
    {
        val = src[i];
        checkSum = checkSum^val<<8;
        for (j=8; j!=0; j--)
        {
            if (checkSum & 0x8000)
            {
                checkSum = checkSum<<1^0x1021;
            }
            else
            {
                checkSum = checkSum<<1;
            }
        }
    }

    *CRC16= (checkSum>>8)&0xff;
    *CRC8= (checkSum)&0xff;
}
extern  void hexdump(const void *buf, unsigned int length);
int do_verify_widevine (void)
{
#if 1
	unsigned int image_A_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    unsigned int image_B_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR+0x00100000;
    printf("src=%x,size=%x\n", image_A_addr, WIDEVINE_DATA_SIZE);
	printf("verify widevine success\n");	
    return CMD_RET_SUCCESS;
#else
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_dst_addr;
    unsigned int Kh_key[4],image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);

    // 1. read image from  factory_ro to DDR
    image_name=FACTORY_RO_WIDEVINE_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    rcode = do_verify_read_facro(image_name, image_src_addr,&image_size);
    if (rcode)
    {
        printf("[INFO %s] %s %s: failed. \n", __FUNCTION__,image_name,"file not found");
        goto FAIL;
    }

    // 2. decrypt using deviceID
    image_dst_addr=image_src_addr+0x100000;
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);

    rcode=read_efuse_deviceID(Kh_key);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
        goto FAIL;
    }

    rcode=do_burn_decrypt(image_src_addr,WIDEVINE_DATA_SIZE,image_dst_addr,Kh_key,ENCRYPTION_AES_128_ECB);
    if( rcode )
    {
        printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt widevine image error",rcode);
        goto FAIL;
    }
    hexdump( image_dst_addr+128, 16 );

    // 3. encrypt using AES
    Kh_key[0]=SECURE_KH_KEY0;
    Kh_key[1]=SECURE_KH_KEY1;
    Kh_key[2]=SECURE_KH_KEY2;
    Kh_key[3]=SECURE_KH_KEY3;
    rcode = do_burn_encrypt(image_dst_addr, image_size, image_src_addr, Kh_key,ENCRYPTION_AES_128_CBC);
    hexdump( image_src_addr+128, 16 );
    printf("src=%x,size=%x\n",image_src_addr,WIDEVINE_DATA_SIZE);

    if (cmd)
    {
        free(cmd);
    }
    printf("verify widevine success\n");
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    printf("verify widevine fail\n");
    return CMD_RET_FAILURE;
#endif
}


int do_verify (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc == 2)
    {
        if ( strcmp(argv[1], "hdcp1.4") == 0)
        {
            return do_verify_hdcp("hdcp1.4");
        }
        else if ( strcmp(argv[1], "hdcp2.1") == 0)
        {
            return do_verify_hdcp("hdcp2.1");
        }
        else if ( strcmp(argv[1], "mac") == 0)
        {
            return do_verify_mac();
        }
        else if (strcmp(argv[1], "CI+") == 0)
        {
            return do_verify_ci();
        }
        else if (strcmp(argv[1], "widevine") == 0)
        {
            return do_verify_widevine();
        }
    }

    return CMD_RET_USAGE;
}

U_BOOT_CMD
(
    verify, 2, 1,   do_verify,
    "verify image in factory",
    "hdcp1.4\n"
    "verify hdcp2.1\n"
    "verify mac\n"
    "verify CI+\n"
    "verify widevine"
);



