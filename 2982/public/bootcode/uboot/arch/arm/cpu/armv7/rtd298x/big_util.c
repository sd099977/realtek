#include <common.h>
#include <command.h>
#include <asm/arch/system.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/flash_writer_u/big_int.h>
#include <asm/arch/flash_writer_u/big_util.h>

#ifndef Config_Secure_RSA_MODULUS
#define Config_Secure_RSA_MODULUS ""
#endif

/************************************************************************
 *  Public variables
 ************************************************************************/
static unsigned int alloc_count;

/************************************************************************
 *  Static variables
 ************************************************************************/
static unsigned int alloc_current;

/************************************************************************
 *  Function body
 ************************************************************************/
void * my_malloc(unsigned int NBYTES)
{
    void *p;

    if ((alloc_count + NBYTES) > SECURE_MAX_ALLOC_SIZE) {
        return NULL;
    }

    if (alloc_count == 0) {
        alloc_current = SECURE_MALLOC_BASE;
    }

    p = (void *)(alloc_current);

    if (NBYTES & 0x3) {
        NBYTES = ((NBYTES >> 2) << 2) + 0x4;
    }

    alloc_current += NBYTES;
    alloc_count += NBYTES;

    return p;
}

void my_freeAll(void)
{
    alloc_count = 0;
    alloc_current = SECURE_MALLOC_BASE;
}

unsigned int do_RSA( const unsigned int signature_addr,
                     const unsigned int rsa_key_addr,
                     const unsigned int output_addr )
{
    BI *base, *exp, *mod, *res;
    unsigned int t1, tmp;
    int i;
    unsigned char * ptr;
    const char algo_id[19] = {
        0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
        0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
        0x00, 0x04, 0x20};

    // necessary
    alloc_count = 0;
    alloc_current = SECURE_MALLOC_BASE;

    base = InPutFromAddr((unsigned char *)signature_addr, RSA_SIGNATURE_LENGTH);
    if(base == NULL) {
        my_freeAll();
        return 0;
    }

	if (rsa_key_addr == 0)
		mod = InPutFromStr(Config_Secure_RSA_MODULUS, 16);
	else
	    mod = InPutFromAddr((unsigned char *)rsa_key_addr, RSA_SIGNATURE_LENGTH);
	
	if(mod == NULL) {
        my_freeAll();
        return 0;
    }

    // public exponent is always 65537
    exp = move_p(65537);
    if(exp == NULL) {
        my_freeAll();
        return 0;
    }

    res = Exp_Mod(base, exp, mod);
    if(res == NULL) {
        my_freeAll();
        return 0;
    }

    OutPutToAddr(res, (unsigned char *)output_addr, 1);

    // bypass PKCS#1 v1.5 block format
    t1 = output_addr;
    ptr = (unsigned char *)t1;
    if ((*ptr == 0) && (*(ptr+1) == 0x1)) {
        // skip padding
        // (padding format: 00 01 ff ff ff ... 00)
        t1 += 2;
        ptr += 2;

        while (*ptr == 0xff) {
            ptr++;
            t1++;
        }

        if (*ptr == 0) {
            ptr++;
            t1++;
        }

        tmp = t1;

        // skip digest algorithm identifier
        for (i = 0; i < sizeof(algo_id); i++) {
            if (*ptr != algo_id[i]) {
                t1 = tmp;   // restore to previous postition
                break;
            }
            ptr++;
            t1++;
        }
    }

    my_freeAll();

    return t1;
}

#ifdef CONFIG_NOCS_BSD
//#define DO_RSA_DEBUG

#ifdef DO_RSA_DEBUG
#define RSA_INFO(fmt, args...)          \
            printf(fmt,## args)
#else
#define RSA_INFO(fmt, args...)
#endif

unsigned int do_RSA_BSD(
    unsigned char       enc,
    unsigned int        key_len,
    const unsigned int  signature_addr,
    const unsigned int  rsa_key_addr,
    const unsigned int  rsa_exp_addr,
    const unsigned int  output_addr )
{
    BI *base, *exp, *mod, *res;
    unsigned int    t1, tmp;
    unsigned int    rsa_len;
    int             i;
    unsigned char * ptr;
    unsigned int    t_exp;

    alloc_count     = 0;
    alloc_current   = SECURE_MALLOC_BASE;
    rsa_len         = key_len;

    base = InPutFromAddr((unsigned char *)signature_addr, rsa_len);
    if(base == NULL) {
        my_freeAll();
        return 0;
    }

    mod = InPutFromAddr((unsigned char *)rsa_key_addr, rsa_len);
    if(mod == NULL) {
        my_freeAll();
        return 0;
    }

    if(enc){
        RSA_INFO("%s(%d)Encrypt...\n",__func__,__LINE__);
        exp = InPutFromAddr((unsigned char *)rsa_exp_addr, rsa_len);
    }else{

        t_exp = *((unsigned int *)rsa_exp_addr);
        RSA_INFO("%s(%d)Decrypt...(exp=0x%x)\n",__func__,__LINE__,t_exp);
        exp = move_p(t_exp);
    }

    if(exp == NULL) {
        my_freeAll();
        return 0;
    }

#if  0
    //following is golden sample
    //2048 bits
    //sig = InPutFromStr("0001ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00176ea0b4c829d9ae4aa3b2a056467c810a649d5b7250de9177dfffbed1839278", HEX);
    //base = InPutFromStr("64712C6494BC4F9318475FB68868BFA3CA3B22450315A9E23F21A383AFB91754E330FA40FB76C06FFE68968E0D7E6E0E0EB4AADFDA953DAAE7C75EDFCF36AE95E05AE6BE1482DBB36D2E5C51CA686D645207451115AB650E766AA04CDFA26C556C6C9D9109D839761B1E634C0B2BE98CF7F054DEB38F4D978EDCE887D4B51C198AB3FF9C5A0A5618519C1160E67AFAE56F5358058A18591A24288AEA85F9116393B28A698467D8ECB7AC78DEDE9B6518062E01493A7663AE98CD89A9F48DAAB3459C0A66FD5D13C1F854564FB7056E7253E058B819E09E21B7F35AF206705E4E7FAF0CB498BD9F614274BBF632F966F3CA05A07183DAC7953CF4B079B60BB9AD", 16);
    //public key
    //mod  = InPutFromStr("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", 16);
    //exp = move_p(65537);

    /* 1024 bits */
    //base = InPutFromStr("bda3f2de28508f92a4c7c8423dc7a6d40638fb2b292b9ffce77d22f91e2b8976163f641d7cbbea10d0c0b75e63a3b143823bc0f966773b8298c37dc5083dfda9faee65d5c506250ff4637a35c73571806e2cfc2fd6259603244f8d15e6a39fae0f4530b10965fe114848fc32c045e2ce86f46373f28a9677f411b5319182993e", 16);
    //mod  = InPutFromStr("f2f9465b41765e6e954343a4108a8e6588fb0899a9b0cb9fc87e16be33efbf086371c5717dedfefb2df795d7eec59fd3d031806ed306cfdce0b359c3766a95c1cd926dbf94af5955af584364bf03e48aa7900447e38790972ef964ad3444c32976e58a49a112ab094b668f9f06df23848c87d3965a8248965376f7e9a0d254b5", 16);

    /* exp=17 */
  //base = InPutFromStr("0002af78c6a2882830090000001f63dcd0479d5d09b068295cd3e9252c5ab6dededf8a7134f73ea9d66ff46832d59648863a7f813b37770e752ee50be8d24062edeac7a6d552723f7d4228c822d232b577bef039f567ca67731b6a97f696280bcac9c6d2d2da5eed1c6b98b1b81f206ccb5a584bdf494a7b7d23e08ffeae5722", 16);
#endif

    res = Exp_Mod(base, exp, mod);
    if(res == NULL) {
        my_freeAll();
        return 0;
    }
    OutPutToAddr(res, (unsigned char *)output_addr, 1);
    RSA_INFO("exp = 0x%x  =====>\n",t_exp);
    ptr = (unsigned char *)output_addr;
    for(i=0;i<rsa_len;i++){
        RSA_INFO("%02x",(unsigned char *)ptr[i]);
    }
    RSA_INFO("\n");

    my_freeAll();

    return t1;
}

#endif
