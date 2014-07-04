
#include <command.h>
#include <asm/io.h>
#include <asm/arch/flash_writer_u/otp_reg.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <common.h>
#include <burn.h>

extern unsigned char buffer[512];

#define REG32( addr )         (*(volatile UINT32 *)(addr))

#define DRY_RUN
#define rtprintf printf

#define PROGRAM_RSA_START_BYTE          	0
#define PROGRAM_DCAS_RSA_START_BYTE     	0

#define PROGRAM_ACPU_AES_START_BYTE     	256
#define PROGRAM_SCPU_AES_START_BYTE     	256 + 16

// TODO: FIX ME
//#define EFUSE_KEY_MODE_BIT_NUM  			3785
//#define SECURITY_BOOT_BIT_NUM   			3787

//#define EFUSE_TEST_BIT_NUM      			3792
/************************************************************************
 *  Definition
 ************************************************************************/
#define OTP_EF_CTRL         (OTP_REG_BASE + 0x200)
#define OTP_EF_CTRL_ST      (OTP_REG_BASE + 0x204)

// TODO: FIX ME
//#define OTP_EFUSE_SECUREBOOT            0xb80381d8
//#define OTP_EFUSE_BACKDOOR              0xb80381d8


#define EF_CTRL_WRITE_EN1           (1 << 12)

static unsigned int deviceID_addr[4];
static unsigned int deviceID_enc_addr[4];
static unsigned int deviceID_flag=0;

/************************************************************************
 *  Function Body
 ************************************************************************/
int start_bit_program (UINT32 bitnum)
{
    UINT32 prog_addr_val, data_bit_select, address_input;

#ifndef DRY_RUN
    // enable program OTP
    rtd_outl(OTP_EF_CTRL, 0x00C00401);
#endif

    udelay(5);


    data_bit_select = (bitnum & 0x7) << 9;              //[11:9]
    address_input = (bitnum >> 3) & 0x1ff;              //[8:0]
    prog_addr_val = EF_CTRL_WRITE_EN1 | address_input | data_bit_select;    //[8:0][11:9]
    rtprintf("bitnum:%d, prog_addr:0x%x, address_input:0x%x, data_bit_select:0x%x\n", bitnum, prog_addr_val, address_input, data_bit_select);

#ifndef DRY_RUN
    //check bit 16, to make sure "program efuse active"
    while((rtd_inl(OTP_EF_CTRL_ST) >> 16) & 0x1 == 0)
        ;

    // fill the address bit which we want to program
    rtd_outl(OTP_EF_CTRL, prog_addr_val);

    // enable strobe
    rtd_outl(OTP_EF_CTRL, 0x00406401);
    //udelay(10);



    // disable program OTP
    rtd_outl(OTP_EF_CTRL, 0x00800401);
#endif

// TODO: FIX ME
#if defined(_FIXME)
    rtprintf("[%s]start_bit_program 0x%x\n",__FUNCTION__, rtd_inl(OTP_EFUSE_SECUREBOOT));
#endif

}


int start_program (UINT32 startbyte, UINT32 totalbytes, UINT8 * src_array)
{
    UINT32 i, j;
    UINT32 addr, value;
    UINT32 prog_addr_val, data_bit_select, address_input;
    UINT32 total = 0;       // number of bits successfully programmed

#ifndef DRY_RUN
    // enable program OTP
    rtd_outl(OTP_EF_CTRL, 0x00C00401);
    udelay(5);
#endif
    for (i = startbyte; i < (startbyte + totalbytes); i += 4)
    {
        value = REG32(src_array + i - startbyte);//value = (*(volatile UINT32 *)(src_array + i - startbyte));
        rtprintf("[%s]value:0x%x\n", __FUNCTION__,value);

        // for each bit in the word
        for (j = 0; j < 32; j++)
        {

            //rtprintf("addr:%d, [%x]\n",(i * 8 + j), (value >> j) & 0x1);
            // check if need to program
            if ((value >> j) & 0x1)
            {
                addr = i * 8 + j;   // bit address

                data_bit_select = (addr & 0x7) << 9;                //[11:9]
                address_input = (addr >> 3) & 0x1ff;                //[8:0]
                prog_addr_val = EF_CTRL_WRITE_EN1 | address_input | data_bit_select;    //[8:0][11:9]
                //rtprintf("addr:0x%x, prog_addr:0x%x, address_input:0x%x, data_bit_select:0x%x\n", addr, prog_addr_val, address_input, data_bit_select);
#ifndef DRY_RUN

                //check bit 16, to make sure "program efuse active"
                while((rtd_inl(OTP_EF_CTRL_ST) >> 16) & 0x1 == 0)
                    ;

                // fill the address bit which we want to program
                rtd_outl(OTP_EF_CTRL, prog_addr_val);

                // enable strobe
                rtd_outl(OTP_EF_CTRL, 0x00406401);
#endif
                udelay(10);
                total++;
            }
        }
    }

#ifndef DRY_RUN
    // disable program OTP
    rtd_outl(OTP_EF_CTRL, 0x00800401);
    rtprintf("[%s]total %d bits programmed\n",__FUNCTION__, total);
#endif
    rtprintf("\n");

}

int do_efuse_deviceID_encrypt (unsigned char * src_addr, unsigned char * dst_addr, unsigned int key[4])
{
    unsigned char * pimage_src_addr;
    unsigned char * pimage_src_addr2;
    //pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFF20UL );
    pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFFE0UL );
    pimage_src_addr += 0x20; // 32-byte alignment
    pimage_src_addr2 = pimage_src_addr + 0x20; // 32-byte alignment

    //printf("*** %s %s %d, pimage_src_addr     = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr);
    //printf("*** %s %s %d, pimage_src_addr2    = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr2);

    //0x44425354  0x30303331 0x30303030 0x31303030

    memcpy( pimage_src_addr, src_addr, deviceID_ARRAY_SIZE );
    memset( pimage_src_addr2, 0, 32 );

    flush_cache( pimage_src_addr, deviceID_ARRAY_SIZE );
    flush_cache( pimage_src_addr2, deviceID_ARRAY_SIZE );
    if (key)
    {
        flush_cache( key, deviceID_ARRAY_SIZE );
    }

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    AES_ECB_encrypt( pimage_src_addr, deviceID_ARRAY_SIZE, pimage_src_addr2, key);
    memcpy( dst_addr, pimage_src_addr2, deviceID_ARRAY_SIZE );
    flush_cache( dst_addr, deviceID_ARRAY_SIZE );
    return 0;
}

int do_efuse_deviceID_decrypt (unsigned char * dst_addr,unsigned char * src_addr,unsigned int key[4])
{
    unsigned char * pimage_src_addr;
    unsigned char * pimage_src_addr2;
    //pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFF20UL );
    pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFFE0UL );
    pimage_src_addr += 0x20; // 32-byte alignment
    pimage_src_addr2 = pimage_src_addr + 0x20; // 32-byte alignment

    //printf("*** %s %s %d, pimage_src_addr     = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr);
    //printf("*** %s %s %d, pimage_src_addr2    = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr2);

    //0x44425354  0x30303331 0x30303030 0x31303030

    memcpy( pimage_src_addr, src_addr, deviceID_ARRAY_SIZE );
    memset( pimage_src_addr2, 0, 32 );

    flush_cache( pimage_src_addr, deviceID_ARRAY_SIZE );
    flush_cache( pimage_src_addr2, deviceID_ARRAY_SIZE );
    if (key)
    {
        flush_cache( key, deviceID_ARRAY_SIZE );
    }

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    AES_ECB_decrypt( pimage_src_addr, deviceID_ARRAY_SIZE, pimage_src_addr2, key);
    memcpy( dst_addr, pimage_src_addr2, deviceID_ARRAY_SIZE );
    flush_cache( dst_addr, deviceID_ARRAY_SIZE );
    return 0;
}

int do_get_efuse_deviceID (void)
{
    unsigned int Kh_key[4];
    int rcode = CMD_RET_SUCCESS;
    rcode = read_efuse_deviceID(Kh_key);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
        goto FAIL;
    }

    //printf("%08x    %08x    %08x    %08x\n",Kh_key[0],Kh_key[1],Kh_key[2],Kh_key[3]);
    printf("read deviceID success\n");
    return CMD_RET_SUCCESS;

FAIL:
    printf("read deviceID fail\n");
    return CMD_RET_FAILURE;
}

int do_burn_efuse_deviceID (void)
{
    char *cmd = NULL;
    unsigned int Kh_key[4] = {0,0,0,0};
    unsigned int image_src_addr,image_size=0,* addr;
    int rcode = CMD_RET_SUCCESS;

    image_src_addr = TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    //1. load deviceID in efuse!
    rcode = read_efuse_deviceID(Kh_key);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"read_efuse_deviceID");
        goto FAIL;
    }

    //2. upload deviceID file:16 byte
    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        goto FAIL;
    }
    memset(cmd,0,SRING_SIZE);

    snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode = run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    //3.1 check deviceID from tool
    memcpy(deviceID_addr,image_src_addr,deviceID_ARRAY_SIZE);
    if ((deviceID_addr[0] != 0x44425354) ) //TSBD
    {
        printf("deviceID from TOOL is NOT OK! %s  %d\n",__func__,__LINE__);
        goto FAIL;
    }

    //3.2 compare ,check whether deviceID has burned or not
    if ( (Kh_key[0]==0)&&(Kh_key[1]==0)&&(Kh_key[2]==0)&&(Kh_key[3]==0) )
    {
        printf("efuse is empty !%s  %d\n",__func__,__LINE__);
    }
    else if (memcmp(Kh_key,deviceID_addr,deviceID_ARRAY_SIZE)==0)
    {
        printf("deviceID is the same! %s  %d\n",__func__,__LINE__);
        printf("deviceID is %08x  %08x  %08x  %08x\n",Kh_key[0],Kh_key[1],Kh_key[2],Kh_key[3]);
        goto SUCCESS;
    }
    else
    {
        printf("deviceID is NOT the same! %s  %d\n",__func__,__LINE__);
        printf("ORIGINAL:       deviceID is %08x  %08x  %08x  %08x\n",Kh_key[0],Kh_key[1],Kh_key[2],Kh_key[3]);
        printf("TOOL:              deviceID is %08x  %08x  %08x  %08x\n",deviceID_addr[0],deviceID_addr[1],deviceID_addr[2],deviceID_addr[3]);
        goto FAIL;
    }

    //4. encrpyt deviceID with AES_128 (efuse AES key)
    rcode=do_efuse_deviceID_encrypt(image_src_addr, deviceID_enc_addr, NULL);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,"AES_ECB_encrypt");
        goto FAIL;
    }
    addr=(unsigned int *)image_src_addr;
    PRINT_DEBUG("1.     0x%x    0x%x    0x%x    0x%x\n",addr[0],addr[1],addr[2],addr[3]);
    PRINT_DEBUG("2.     0x%x    0x%x    0x%x    0x%x\n",
                deviceID_enc_addr[0],deviceID_enc_addr[1],deviceID_enc_addr[2],deviceID_enc_addr[3]);

    //5. burn deviceID after encrption
    start_program(PROGRAM_DEVICE_ID_START_BYTE, DEVICE_ID_LENGTH, (unsigned char *)deviceID_enc_addr);

SUCCESS:
    printf("save deviceID success\n");

    deviceID_flag=1;//indicate burning efuse deviceID
#if 0
    //4. reset EFUSE/OTP
    snprintf(cmd, sizeof(cmd),"reset");
    rcode=run_command(cmd,0);
#endif
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    printf("save deviceID fail\n");
    return CMD_RET_FAILURE;

}

int do_burn_efuse_aes_key_exist (void)
{
    int ret=0;
    unsigned char data[deviceID_ARRAY_SIZE] = {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};
    unsigned char data_enc[deviceID_ARRAY_SIZE] = {0x36,0x58,0xc6,0x84,0x9f,0x4d,0xd4,0xce,0x48,0x42,0x70,0xcc,0xcd,0xd7,0x7b,0x0b};
    unsigned char *image_src_addr,*image_dst_addr,buffer[128];

    image_src_addr=(unsigned char *)((((unsigned int)buffer)&(0xFFFFFFE0))+0x20);
    image_dst_addr=image_src_addr+0x20;

    memcpy(image_src_addr,data,sizeof(data));
    memset( image_dst_addr, 0, deviceID_ARRAY_SIZE );

    flush_cache( image_src_addr, deviceID_ARRAY_SIZE );
    flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    ret = AES_ECB_encrypt(image_src_addr, deviceID_ARRAY_SIZE, image_dst_addr, NULL);
    if (ret)
    {
        return 0;//indicate enc fail!
    }
    return memcmp(data_enc,image_dst_addr,deviceID_ARRAY_SIZE);
}

// TODO: FIX ME
int do_burn_efuse_aes_check (void)
{
#if defined(_FIXME)
    int ret = do_burn_efuse_aes_key_exist();
#else
	int ret = 1;
#endif
	if (ret == 0)
    {
        printf("aes key match fail\n");
    }
    else
    {
        printf("aes key match success\n");
    }
    return CMD_RET_SUCCESS;
}

// TODO: FIX ME
int do_burn_efuse_secure_mode_enable_bit (void)
{
#if defined(_FIXME)
    if (do_burn_efuse_aes_key_exist() == 0)
    {
        printf("save secure boot bit fail\n");
        return CMD_RET_FAILURE;
    }
    //start_bit_program(EFUSE_KEY_MODE_BIT_NUM);
    //start_bit_program(SECURITY_BOOT_BIT_NUM);
    printf("save secure boot bit success\n");
#endif	
    return CMD_RET_SUCCESS;
}

int read_efuse_deviceID (unsigned int * Kh_key)
{
    unsigned int value,i;
    unsigned int Kh_local_key[4];

    if (Kh_key == NULL)
    {
        return 1;
    }

#if 0
    if (deviceID_flag)
    {
        for (i=0; i<4; i++)
        {
            Kh_key[i]=deviceID_addr[i];
            //PRINT_DEBUG("deviceID_addr   1       key[%d]=%x\n",i,Kh_key[i]);
            PRINT_DEBUG("1   [%d]=%x\n",i,Kh_key[i]);
        }
    }
    else
#endif
    {
        //TSBD130000000001
        for (i = 0;i < 4;i++)
        {
            value = OTP_DEVICEID + i*4;
            Kh_local_key[i] = rtd_inl(value);
            //printf("OTP_DEVICEID    key[%d]=%x\n",i,Kh_local_key[i]);
            PRINT_DEBUG("1   [%d]=%08x\n", i, Kh_local_key[i]);
        }

        if ((Kh_local_key[0] == 0 )&&(Kh_local_key[1] == 0)&&(Kh_local_key[2] == 0)&&(Kh_local_key[3] == 0))
        {
            PRINT_DEBUG("deviceID is EMPTY! Just return direct\n");
            return 0;
        }

        //do_efuse_deviceID_decrypt(Kh_key,Kh_local_key,burn_aes_key);
        do_efuse_deviceID_decrypt(Kh_key, Kh_local_key, NULL);
        for (i = 0;i < 4;i++)
        {
            PRINT_DEBUG("2   [%d]=%08x\n",i,Kh_key[i]);
        }
    }

    return 0;
}

int read_efuse_sn(unsigned char * pcSN)
{
	unsigned int i;
	unsigned int otp_address;
    unsigned int * piSN;

    if (pcSN == NULL)
    {
        return 1;
    }
    
    piSN = (unsigned int *)pcSN;

    {
        for (i = 0;i < 4;i++)
        {
            otp_address = OTP_DEVICEID + i*4;
            piSN[i] = rtd_inl(otp_address);
            //printf("OTP ID [%d]=0x%08x\n",i, piSN[i]);
        }
    }

    return 0;
}


#if 0 // not compile, reduce code size
int do_cp_test0 (void)
{
    unsigned int i, enc_ret,dec_ret;
    unsigned char *image_src_addr,*image_dst_addr,*image_src1_addr,buffer[128];
    unsigned char data[deviceID_ARRAY_SIZE]= {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};

    image_src_addr=(unsigned char *)((((unsigned int)buffer)&(0xFFFFFFE0))+0x20);
    image_dst_addr=image_src_addr+0x20;
    image_src1_addr=image_src_addr+0x40;

    memcpy(image_src_addr,data,sizeof(data));
    memset( image_dst_addr, 0, deviceID_ARRAY_SIZE );
    memset( image_src1_addr, 0, deviceID_ARRAY_SIZE );

    printf("*** %s %s %d, buffer                = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, buffer);
    printf("*** %s %s %d, pimage_src_addr       = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)image_src_addr);
    printf("*** %s %s %d, image_dst_addr        = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)image_dst_addr);
    printf("*** %s %s %d, image_src1_addr       = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)image_src1_addr);

    //0x44425354  0x30303331 0x30303030 0x31303030

    flush_cache( image_src_addr, deviceID_ARRAY_SIZE );
    flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    enc_ret=AES_ECB_encrypt( image_src_addr, deviceID_ARRAY_SIZE, image_dst_addr, NULL);

    flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );
    flush_cache( image_src1_addr, deviceID_ARRAY_SIZE );
    dec_ret=AES_ECB_decrypt( image_dst_addr, deviceID_ARRAY_SIZE, image_src1_addr, NULL);
    flush_cache( image_src1_addr, deviceID_ARRAY_SIZE );

    printf("-----------------------------------------------------------\n");
    printf("    ret=%d, source data    =",enc_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_src_addr[i]);
    }

    printf("\n");
    printf("    ret=%d, encrypted data =",enc_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_dst_addr[i]);
    }
    printf("\n");

    printf("    ret=%d, decrypted data =",dec_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_src1_addr[i]);
    }

    printf("\n");
    return 0;
}


int do_cp_test1 (void)
{
    unsigned char *image_src_addr,*image_dst_addr,*image_src1_addr,buffer[128];
    printf("*** %s %s %d, buffer       = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, buffer);
    return 0;
}


int AES_CBC_decrypt1
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],unsigned int ini_key[4]);
int AES_CBC_encrypt1
(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4],unsigned int ini_key[4]);
void do_cp_aes_128_cbc_test (void)
{
    unsigned int i, enc_ret,dec_ret;
    unsigned char *image_src_addr,*image_dst_addr,*image_src1_addr,buffer[128];
    unsigned char data[deviceID_ARRAY_SIZE]= {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};
    unsigned char iv_key[deviceID_ARRAY_SIZE]= {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};
    image_src_addr=(unsigned char *)((((unsigned int)buffer)&(0xFFFFFFE0))+0x20);
    image_dst_addr=image_src_addr+0x20;
    image_src1_addr=image_src_addr+0x40;

    memcpy(image_src_addr,data,sizeof(data));
    memset( image_dst_addr, 0, deviceID_ARRAY_SIZE );
    memset( image_src1_addr, 0, deviceID_ARRAY_SIZE );

    flush_cache( image_src_addr, deviceID_ARRAY_SIZE );
    flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );
    printf("    ret=%d, orignal   data =",enc_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_src_addr[i]);
    }
    printf("\n");

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    enc_ret=AES_CBC_encrypt1( image_src_addr, deviceID_ARRAY_SIZE, image_dst_addr, burn_aes_key, burn_aes_key );
    flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );

    printf("    ret=%d, encrypted data =",enc_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_dst_addr[i]);
    }
    printf("\n");

    enc_ret=AES_CBC_decrypt1( image_dst_addr, deviceID_ARRAY_SIZE, image_src_addr, burn_aes_key, burn_aes_key );
    flush_cache( image_src_addr, deviceID_ARRAY_SIZE );

    printf("    ret=%d, decrypted data =",enc_ret);
    for (i=0; i<deviceID_ARRAY_SIZE; i++)
    {
        printf(" %02x", image_src_addr[i]);
    }
    printf("\n");

    return 0;
}

static void test (void)
{
    int do_burn_hdcp_21 (void);
    unsigned int Kh_key[4];
    do_get_hdcp2x_key(Kh_key);
    int i;
    for (i=0; i<4; i++)
    {
        printf("%x\n",Kh_key[i]);
    }
}

int do_cp_test (void)
{
    //do_cp_aes_128_cbc_test();
    test();
#if 0
    {
        unsigned int i, enc_ret,dec_ret;
        unsigned char *image_src_addr,*image_dst_addr,*image_src1_addr,buffer[128];
        unsigned char data[deviceID_ARRAY_SIZE]= {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};

        image_src_addr=(unsigned char *)((((unsigned int)buffer)&(0xFFFFFFE0))+0x20);
        image_dst_addr=image_src_addr+0x20;
        image_src1_addr=image_src_addr+0x40;

        memcpy(image_src_addr,data,sizeof(data));
        memset( image_dst_addr, 0, deviceID_ARRAY_SIZE );
        memset( image_src1_addr, 0, deviceID_ARRAY_SIZE );

        //0x44425354  0x30303331 0x30303030 0x31303030

        flush_cache( image_src_addr, deviceID_ARRAY_SIZE );
        flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );

        //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
        enc_ret=AES_ECB_encrypt( image_src_addr, deviceID_ARRAY_SIZE, image_dst_addr, NULL);

        flush_cache( image_dst_addr, deviceID_ARRAY_SIZE );
        flush_cache( image_src1_addr, deviceID_ARRAY_SIZE );
        dec_ret=AES_ECB_decrypt( image_dst_addr, deviceID_ARRAY_SIZE, image_src1_addr, NULL);
        flush_cache( image_src1_addr, deviceID_ARRAY_SIZE );

        printf("-----------------------------------------------------------\n");
        printf("    ret=%d, source data    =",enc_ret);
        for (i=0; i<deviceID_ARRAY_SIZE; i++)
        {
            printf(" %02x", image_src_addr[i]);
        }

        printf("\n");
        printf("    ret=%d, encrypted data =",enc_ret);
        for (i=0; i<deviceID_ARRAY_SIZE; i++)
        {
            printf(" %02x", image_dst_addr[i]);
        }
        printf("\n");

        printf("    ret=%d, decrypted data =",dec_ret);
        for (i=0; i<deviceID_ARRAY_SIZE; i++)
        {
            printf(" %02x", image_src1_addr[i]);
        }

        printf("\n");
        return 0;
    }
#if 0
    if (do_burn_efuse_aes_key_exist())
    {
        printf("save secure boot bit fail\n");
        return CMD_RET_FAILURE;
    }
    else
    {
        printf("save secure boot bit success\n");
        return CMD_RET_SUCCESS;
    }
#endif

#endif
}

#else
int do_cp_test (void)
{
#define ARRAY_SIZE 16

    unsigned int i, enc_ret;
    unsigned int Kh_key_local[4];
    unsigned char buffer[512];
    unsigned char image_src_addr[ARRAY_SIZE]     = {'T','S','B','D','1','3','0','0','0','0','0','0','0','0','0','1'};
    unsigned char * pimage_src_addr;
    unsigned char * pimage_src_addr2;
    //pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFF20UL );
    pimage_src_addr = (unsigned char *) ( ((unsigned int)buffer)&0xFFFFFFE0UL );
    pimage_src_addr += 0x20; // 32-byte alignment
    pimage_src_addr2 = pimage_src_addr + 0x20; // 32-byte alignment

    printf("*** %s %s %d, pimage_src_addr     = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr);
    printf("*** %s %s %d, pimage_src_addr2    = 0x%08x\n", __FILE__, __FUNCTION__, __LINE__, (unsigned int)pimage_src_addr2);

    //0x44425354  0x30303331 0x30303030 0x31303030
#if 1
    Kh_key_local[0] = SECURE_KH_KEY0;
    Kh_key_local[1] = SECURE_KH_KEY1;
    Kh_key_local[2] = SECURE_KH_KEY2;
    Kh_key_local[3] = SECURE_KH_KEY3;
#else
    Kh_key_local[0] = 0x44425354;
    Kh_key_local[1] = 0x30303331;
    Kh_key_local[2] = 0x30303030;
    Kh_key_local[3] = 0x31303030;
#endif

    memcpy( pimage_src_addr, image_src_addr, 32 );
    memset( pimage_src_addr2, 0, 32 );

    flush_cache( pimage_src_addr, ARRAY_SIZE );
    flush_cache( pimage_src_addr2, ARRAY_SIZE );
    flush_cache( Kh_key_local, ARRAY_SIZE );

    //invalidate_dcache_range(image_src_addr2, ARRAY_SIZE);
    enc_ret=AES_ECB_encrypt( pimage_src_addr, ARRAY_SIZE, pimage_src_addr2, Kh_key_local);
    //flush_cache(image_src_addr2, ARRAY_SIZE);

    printf("-----------------------------------------------------------\n");
    printf("    ret=%d, source data    =",enc_ret);
    for (i=0; i<ARRAY_SIZE; i++)
    {
        printf(" %02x", pimage_src_addr[i]);
    }

    printf("\n");
    printf("    ret=%d, encrypted data =",enc_ret);

    for (i=0; i<ARRAY_SIZE; i++)
    {
        printf(" %02x", pimage_src_addr2[i]);
    }

    printf("\n");
    return 0;
}
#endif

static int otp_init_once;

int otp_init()
{
    
    if( otp_init_once == 0 ) {
	    // Change SB2 Timeout to maximum value to prevent RBUS Timeout
		rtd_outl(0xb801A004, 0x30);
		//rtd_outl(0xb801A010, 0x1F);    // origion setting
		printf("0xb801A004 = 0x%08x, 0xb801A010 = 0x%08x\n", rtd_inl(0xb801A004), rtd_inl(0xb801A010));
		otp_init_once++;
	}

    return 0;            
}

int otp_read( unsigned int ofst, unsigned int * pval )
{
    if (ofst & 0x3)
    {
        printf("read otp failed, ofst 0x%08x is not 4 bytes alignments\n", ofst);        
        return -1;
    }

    *pval = rtd_inl(OTP_DATA + ofst);
    
    return 0;
}

int otp_write( unsigned int ofst, unsigned int val, int check_readable )
{       
    unsigned int org;
    unsigned int status;
    unsigned int addr;
    int i;
    int wait_count;
    int ret = 0;    
        
    //otp_init();
    
    if (ofst & 0x3)
    {
        printf("write OTP failed, ofst 0x%08x is not 4 bytes alignments\n", ofst);      
        return -1;
    }
    
    if (ofst >= MAX_OTP_OFST)
    {
        printf("write OTP failed, ofst 0x%08x >= MAX_OTP_OFST(0x%08x)\n", ofst, MAX_OTP_OFST);      
        return -1;
    }          

    // check readable?? It seems is not necessary.
    if( check_readable ) {
	    otp_read(ofst, &org);
	    if (org==0xdeaddead)
	    {
	        printf("otp[0x%08x] is non readable, no re-program check\n", ofst);
	        return -1;
	    }
	}
	else {
		org = 0;	
	}

	rtd_outl(OTP_STATUS,0);		

	rtd_outl(OTP_CTRL1, SET_OTP_CTRL1_WRITE_EN1(1) | SET_OTP_CTRL1_EN_PROG_FUNC(OTP_PROG_MAGIC));					        	                    

    //printf("val=0x%08x\n", val);	                    
     
    for (i = 0; i < 32; i++) 
    {        

        addr = (ofst <<3) + i;
                                        
        if ((val & (1<<i))==0) {
            continue;
        }
                        
        //printf("program otp bit %d (0x%08x, 0x%08x)\n", addr, val, (1<<i));            
            
        if (org & (1<<i))                                
        {
            //printf("otp bit %d has been programmed, process next bit\n", addr);
            continue;
        }
                
        //printf("start otp bit %d programing\n", addr);            
        //fflush(stdout);
            
        rtd_outl(OTP_CTRL,  SET_OTP_CTRL_WRITE_EN1(1) |
					        SET_OTP_CTRL_MAX_PROG_NUM(0x14) |
					        SET_OTP_CTRL_PROG(1) |
					        SET_OTP_CTRL_A(addr));					
                               
        wait_count = 0;          
        do 
        {     
            status = rtd_inl(OTP_STATUS);
            //printf("Status = 0x%08x\n", status);            
            
        	if (status & MASK_OTP_STATUS_OTP_FAIL_REG_WR) 
            {
        		printf("[ERROR] program OTP bit %d failed, status: 0x%08x\n", addr, status);
        		ret = -1;
        		goto final;
        	}
        	    
        	//if (wait_count++ > 0)
        	//    break;        	    
        	mdelay(1);
        	        
        }
        while((status & MASK_OTP_STATUS_OTP_DONE_REG_WR)==0);
		
		//printf("otp bit %d programing completed\n", addr);            
				        
        rtd_outl(OTP_STATUS, status & ~(MASK_OTP_STATUS_OTP_FAIL_REG_WR | MASK_OTP_STATUS_OTP_DONE_REG_WR));									
	}	  		

final:	

	rtd_outl(OTP_CTRL1, 0);	
	rtd_outl(OTP_STATUS, 0);  

    return ret;
}

