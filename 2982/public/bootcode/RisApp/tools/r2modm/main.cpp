/***************************************************************************************************
  File   : NeptuneTP.cpp
  Author : Kevin Wang
****************************************************************************************************
    Update List :
----------------------------------------------------------------------------------------------------
    1.3     |   20080612    | Add Feature
            |               |   1) Support set section filter feature
----------------------------------------------------------------------------------------------------
    1.3a    |   20080721    | Add Feature : Support Section Filter With Callback Function
----------------------------------------------------------------------------------------------------
    1.4     |   20080804    | Add Feature : Support new Section Filter Callback Function
            |               | Add TOT / TDT / PAT Read Test
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>

short str2bin(char *in_str, unsigned char *out_buf);

#define RSA_BITS        (2048)
#define RSA_KEY_SIZE    (RSA_BITS >> 3)	//256
void test_r2modm(unsigned char* key_buf)
{
	int run;
	int j=0;
	int i=0;
	int cnt;
	unsigned char * prt8;

	run = RSA_KEY_SIZE/4;
	cnt = run;
#if 0
	printf("===== key_buf =====");
	for(i=0;i<256;i++)
	{
		if((i%8) == 0){
			printf("\n");
		}
		printf("0x%02x ",key_buf[i]);
	}
#endif

    BN_CTX*  pxCtx = BN_CTX_new();
    BIGNUM*  pxM   = BN_new();
    BIGNUM*  pxR   = BN_new();
    BIGNUM*  pxRem = BN_new();


    BN_set_bit(pxR, RSA_BITS<<1);
    BN_bin2bn((unsigned char*)key_buf, RSA_KEY_SIZE, pxM);
#if 0
    printf("\n========================pxM=======================\n");
    BN_print_fp(stdout, pxM);
    printf("\n");
    printf("\n========================pxR2=======================\n");
    BN_print_fp(stdout, pxR);
    printf("\n");
#endif
    BN_CTX_start(pxCtx);

    BN_mod(pxRem, pxR, pxM, pxCtx);
    printf("\n========================pxRem=======================\n");
    //BN_print_fp(stdout, pxRem);

	prt8 = (unsigned char *)&(pxRem->d[0]);
	//printf("\n\n===== pxRem->d_ =====\n");
	for(i=0;i<256;i++)
	{
		key_buf[i] = prt8[255-i];
		printf("%02x",key_buf[i]);
	}
	printf("\n");


    BN_CTX_free(pxCtx);
    BN_free(pxM);
    BN_free(pxR);
    BN_free(pxRem);
}

//=========================================================
unsigned char get_value(char c);
short str2bin(char *in_str, unsigned char *out_buf)
{
    short len;
    short ret = 0;
    unsigned char temp;

    len = strlen(in_str);
    while(len > 1) // process string buffer that at least have 2 chars
    {
        temp = (*in_str);
        temp = get_value(*in_str);
        if(temp == 0xFF)
        {
            return -1;
        }
        *out_buf = temp * 16;

        in_str++;
        temp = get_value(*in_str);
        if(temp == 0xFF)
        {
            return -1;
        }
        *out_buf += temp;

        in_str++;
        out_buf++;

        ret++;
        len -= 2;
    }

    if(len == 1) // if string only has 1 char left, here process
    {
        temp = get_value(*in_str);
        if(temp == 0xFF)
        {
            return -1;
        }
        *out_buf = temp;
        ret++;
    }

    return ret;
}

unsigned char get_value(char c)
{
    unsigned char temp;

    if(c >= '0' && c <= '9')
    {
        temp = c - '0';
    }
    else if(c >= 'a' && c <= 'f')
    {
        temp = (c - 'a') + 10;
    }
    else if(c >= 'A' && c <= 'F')
    {
        temp = (c - 'A') + 10;
    }
    else
    {
        temp = 0xFF;
    }

    return temp;
}

//=========================================================



/*******************************************************************************
 * FUNC : main
 * DESC : main program entry
 * PARM :
 * RET  : FUNCTION_SUCCESS / FUNCTION_ERROR
 *******************************************************************************/
#define RSA_KEY_LEN 256
int main(int argc, char *argv[])
{
	unsigned int i;
	unsigned int r_len;
	int ret;
	FILE* fd;
	//FILE* sor_fd;
	char* file_pt;
	unsigned char outBinBuf[RSA_KEY_LEN];

	printf("RealTek RSA R2 Gen Tool. (%s %s)\n",__DATE__,__TIME__);
	if(argc==2)
		file_pt   = argv[1];
	else
		file_pt   = "key_pub2.txt";

	fd = fopen(file_pt, "r");

	if(fd ){
		printf("file %s open succes!!\n",file_pt);
	}else{
		printf("file %s open fail!!\n",file_pt);
		return 0;
	}
	r_len = RSA_KEY_LEN;
	ret = fread(outBinBuf, 1, r_len, fd);

	printf("ret = %d\n",ret);

	if(ret == r_len){
		for(i=0;i<RSA_KEY_LEN;i++){
			//printf("%02x",outBinBuf[i]);
		}
		printf("\n");
	}else{
		printf("read %s fail!!\n",file_pt);
	}
	fclose (fd);

	fd = fopen("R2.bin","wb");
	if(fd ){

		/* example */
		//pubkey
		//str2bin("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", outBinBuf);
		//R2
		//str2bin("A09CC11BC8E1D05D468FABF4FCB62AA861FC15A4FE49E53EA7568172625F79B40E04F1545BF52A1C940998AA5301FED02A4BC12FAEE58D920CFE5CF7A5F0ADC3C57E3D527C7F3FCEC95C7E427BD813656E04E5FECFEAA998A7BE51FB83F3995B767D2454C92FAA2D73734B474BF15B7526FD15104F606B5B102D6B7934C348882E810289C4EB492C1F31FC70E85FF7C94D5C466E3A999DFD453BAAE4FD1E166C7F6C194098F27D3E0451AA8CB035459633EA5369760EF1ED20338C20F45E62E66369460C6DA71B4BF9C4E67314DB080606F945F0DF092932FDF550E444ED184CC418DB5A12C6DCA28FE3B5BD1581BD19F235D9C61D02DBD2C8058D547DA7D897", outBinBuf);

	    test_r2modm(outBinBuf);
	    fwrite (outBinBuf , sizeof(char), sizeof(outBinBuf), fd);
	    fclose (fd);
	}
    printf("\n");
}




#if 0
/* for study */
==> BN_CTX
/home/alexkh/NAGRA/OpenSSL/openssl-1.0.1e
./include/openssl/bn.h:311:typedef struct bignum_ctx BN_CTX;
struct bignum_ctx
        {
        /* The bignum bundles */
        BN_POOL pool;
        /* The "stack frames", if you will */
        BN_STACK stack;
        /* The number of bignums currently assigned */
        unsigned int used;
        /* Depth of stack overflow */
        int err_stack;
        /* Block "gets" until an "end" (compatibility behaviour) */
        int too_many;
        };


==> BN_CTX_new
/crypto/bn/bn_ctx.c +214


==> BN_mod()
./include/openssl/bn.h:469:#define BN_mod(rem,m,d,ctx) BN_div(NULL,(rem),(m),(d),(ctx))


==> BN_div()
vi ./crypto/bn/bn_div.c +181

==> BN_set_bit
./crypto/bn/bn_lib.c +700
int BN_set_bit(BIGNUM *a, int n)
{
	int i,j,k;

	if (n < 0)
	        return 0;

	i=n/BN_BITS2;
	j=n%BN_BITS2;
	if (a->top <= i)
    {
    	if (bn_wexpand(a,i+1) == NULL)
    		return(0);

    	for(k=a->top; k<i+1; k++)
            a->d[k]=0;

    	a->top=i+1;
    }

	a->d[i]|=(((BN_ULONG)1)<<j);
	bn_check_top(a);
	return(1);
}



#endif
