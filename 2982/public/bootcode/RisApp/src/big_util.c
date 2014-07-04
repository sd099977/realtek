
/************************************************************************
 *  Include files
 ************************************************************************/
#include <sysdefs.h>
#include "string.h"
#include "sed_common.h"
#include "sed_setup.h"
#include "sed_cert.h"
#include "sed_r2r.h"
#include "sed_otp.h"
#include "sed_char.h"
#include "sed_rtk.h"
#include "sed_drv_uart.h"
#include "sed_drv_sfc.h"
#include "sed_drv_rng.h"
#include "sed_drv_gpio.h"
#include "sed_types.h"
#include "otp_util.h"
#include "big_util.h"
#include "big_int.h"
//#include "reset_def.h"
//#include "uart.h"
//#include "uart_reg.h"
//#include "auto_config.h"
//#include "otp_reg.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
//#define SKIP_skip_pkcs_v1_5_padding

#if defined(MEMORY_POOL)

#ifndef SKIP_SED_FUNC
	//used for  RSA
	#define MEMORY_POOL_SIZE	(5*1024)

	// Aux code decryption will reuse this memory for original data
	// I would like it align the the _f_data_cp_sram address. (It is 0xb8079000 now)
	unsigned char memory_pool[MEMORY_POOL_SIZE];
	#define MAX_ALLOC_SIZE MEMORY_POOL_SIZE
	#define MALLOC_BASE (UINT32)memory_pool
#else
	#define MEMORY_POOL_SIZE	(64*1024)
	#define MALLOC_BASE (UINT32)RSA_MEM_POOL
	#define MAX_ALLOC_SIZE MEMORY_POOL_SIZE
	unsigned char* memory_pool = (unsigned char*)RSA_MEM_POOL;

#endif
#else

	#define MAX_ALLOC_SIZE	32*1024*1024
	#define MALLOC_BASE 0x82000000
#endif

/************************************************************************
 *  Public variables
 ************************************************************************/
static UINT32 alloc_count = 0;
//extern volatile UARTREG		*UartReg;

/************************************************************************
 *  Static variables
 ************************************************************************/
static UINT32 alloc_current;

/************************************************************************
 *  External function prototypes
 ************************************************************************/
//extern int compare_memory(void *s1, void *s2, unsigned int size);
//extern void copy_memory(void *dst, void *src, unsigned int size);

/************************************************************************
 *  Function body
 ************************************************************************/
void copy_memory(void *dst, void *src, UINT32 size)
{
        UINT32 i;
        for (i=0; i<size; i++)
                REG8(((UINT32)dst) + i) = REG8(((UINT32)src) + i);
}

int compare_memory(void *s1, void *s2, UINT32 size)
{
        UINT32 i;
        char *p1, *p2;

        p1 = (char *)s1;
        p2 = (char *)s2;
        for (i = 0; i < size; i++)
        {
                if (p1[i] != p2[i])
                        return (int)p1[i] - (int)p2[i];
        }

        return 0;
}

void *my_malloc(UINT32 NBYTES)
{
	void *p;
	if ((alloc_count + NBYTES) > MAX_ALLOC_SIZE) {	// exceed limit
		//print_val(NBYTES);
		return NULL;
	}

	if (alloc_count == 0)
		alloc_current = MALLOC_BASE;

	p = (void *)(alloc_current);
	// always aligned to word boundary
	if (NBYTES & 0x3)
		NBYTES = ((NBYTES >> 2) << 2) + 0x4;

	alloc_current += NBYTES;
	alloc_count += NBYTES;
	//print_val((UINT32)p);
	return p;
}

//dennistuan add start 20130222
void my_free(UINT32 NBYTES)
{
	// always aligned to word boundary
	if (NBYTES & 0x3)
		NBYTES = ((NBYTES >> 2) << 2) + 0x4;

	alloc_count -= NBYTES;
	alloc_current -= NBYTES;
}
//dennistuan add end 20130222

void my_freeAll(void)
{
	// reset all memory allocated by my_malloc()
	alloc_count = 0;
	alloc_current = MALLOC_BASE;
}

//int strlen(const char *str)
int rsa_strlen(const char *str)
{
	int count = 0;
	while (*str++ != '\0')
		count++;

	return count;
}

void set_memory(void *dst, UINT8 value, UINT32 size)
{
	UINT32 i;

	// write faster if both start address and size are word-aligned
	if ( (((UINT32)dst & 0x3) == 0) && ((size & 0x3) == 0) ) {
		// fill with word value
		UINT32 word = (value << 8) | value;

		word = (word << 16) | word;
		for (i=0; i<size; i+=4)
			REG32(((UINT32)dst) + i) = word;
	}
	else {
		for (i=0; i<size; i++)
			REG8(((UINT32)dst) + i) = value;
	}
}

//For HW RSA utility function===========================================
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#define TYPE_HW_MONT	0
#define TYPE_HW_IMONT	1
static void hwsu_get_data (void *addr, BI *bi, UINT8 type)
{
	int i, j, max_idx;
	unsigned int *reg = (unsigned int *) addr;

	if (type == TYPE_HW_MONT)
		max_idx = 63; //Max: 64 * 32 = 2048 bit
	else
		max_idx = 12; //Max: 13 * 32 = 416 bit

	/* Skip MSB zero */
	i = max_idx;
	while (i && (REG32(reg + i) == 0)) {
		i--;
	}

	/* Fill BI */
	bi->m_nLength = i + 1;
	j = 1;
	for (; i >= 0; i--) {
		bi->m_ulValue[bi->m_nLength - j] = REG32(reg + i);
		j++;
	}

	return;
}
//-----------------------------------------------------------------------------
static void hwsu_set_data (void *addr, BI *bi, UINT8 type)
{
	int i, max_idx;
	unsigned int *reg = (unsigned int *) addr;

	if (type == TYPE_HW_MONT)
		max_idx = 63; //Max: 64 * 32 = 2048 bit
	else
		max_idx = 12; //Max: 13 * 32 = 416 bit

	for (i = 0; i < bi->m_nLength; i++)
		REG32(reg + i) = bi->m_ulValue[i];

	/* Handle rest bytes (clear to 0) */
	for (; i <= max_idx; i++)
		REG32(reg + i) = 0x0;

	return;
}
//-----------------------------------------------------------------------------
static void hwsu_set_bitnum (unsigned int bsize)
{
	REG32(REG_RSA_CTRL1) = (bsize >> 2) - 1;
}
//-----------------------------------------------------------------------------
static void hwsu_chk_mont_engine_ready (void)
{
	while (REG32(REG_RSA_CTRL) == 1);
}
//-----------------------------------------------------------------------------
static void hwsu_mont_engine_go (void)
{
	REG32(REG_RSA_CTRL) = 1;
}
//-----------------------------------------------------------------------------
static void hwsu_mont (BI *resl, BI *a, BI *b, BI *m, UINT32 bsize)
{
	hwsu_chk_mont_engine_ready();

	hwsu_set_data((void *)REG_RSA_X, a, TYPE_HW_MONT);
	hwsu_set_data((void *)REG_RSA_Y, b, TYPE_HW_MONT);
	hwsu_set_data((void *)REG_RSA_M, m, TYPE_HW_MONT);

	hwsu_set_bitnum(bsize);

	hwsu_mont_engine_go();

	hwsu_chk_mont_engine_ready();

	hwsu_get_data((void *)REG_RSA_A, resl, TYPE_HW_MONT);

	return;
}

//-----------------------------------------------------------------------------
static void hwsu_mul_mod (BI *resl, BI *r2, BI *x, BI *y, BI *m, UINT32 bsize)
{
	hwsu_mont (resl, x, y, m, bsize);
	hwsu_mont (resl, resl, r2, m, bsize);

	return;
}
//-----------------------------------------------------------------------------
//End of HW RSA utility funciton=========================================
#define RSA_SIGNATURE_LENGTH    		256             /* RSA signature length (2048 bit) */
#define RSA_2048_KEY_LENGTH     		256             /* RSA 2048 key length (2048 bit) */
#define RSA_2048_KEY_PADDING_LENGTH     64              /* RSA 2048 key padding length (64 byte) */


//////////


/////////
BI *set_bit_p(unsigned int num)
{
	int i,j;
	BI *p;

	p = init();
	if (p == NULL)
		return NULL;

	i = num/32;
	j = num%32;

	p->m_ulValue[i]= (1<<j);

	p->m_nLength = i+1;

	return p;
}

#if 1
//Use hardware RSA to speedup.
unsigned int do_RSA(unsigned char op,
					const unsigned int text_addr,
					const unsigned int rsa_key_addr,
					const unsigned int output_addr)
{
	BI *sig, *exp, *mod, *r2, *res;
	unsigned int t1, tmp,count,space;
	unsigned char* ptr_txt;
	unsigned char* ptr_pub;
	unsigned char* ptr_pri;
	unsigned char* ptr_r2;
	unsigned char  r2_enable = 0;

	int i;
	//RSA_HW
	ptr_txt = (unsigned char*)text_addr;
	ptr_pub = (unsigned char*)rsa_key_addr;
	ptr_r2  = ptr_pub+RSA_2048_KEY_LENGTH;

	if(op & RSA_HW){
		r2_enable = 1;
		op = op & ~RSA_HW;
	}

	//r2_enable = 0;

	if(op == RTK_ENC){
		ptr_pri = ptr_r2+RSA_2048_KEY_LENGTH;
	}

#if 1

	sed_printf1("%srypt Data:",(op == RTK_ENC)? "Enc":"Dec");
	for(i=0;i<RSA_SIGNATURE_LENGTH;i++){
		if((i%16)==0)
			sed_printf1("\n");
		sed_printf1("%02x ",ptr_txt[i]);
	}

	sed_printf1("\n\nPublic Key:");
	for(i=0;i<RSA_2048_KEY_LENGTH;i++){
		if((i%16)==0)
			sed_printf1("\n");
		sed_printf1("%02x ",ptr_pub[i]);
	}
	sed_printf1("\n\n");

	if(r2_enable){
		sed_printf1("\n\nPublic R2:");
		for(i=0;i<RSA_2048_KEY_LENGTH;i++){
			if((i%16)==0)
				sed_printf1("\n");
			sed_printf1("%02x ",ptr_r2[i]);
		}
		sed_printf1("\n\n");
	}
	if(op == RTK_ENC){
		sed_printf1("Private Key:");
		for(i=0;i<RSA_2048_KEY_LENGTH;i++){
			if((i%16)==0)
				sed_printf1("\n");
			sed_printf1("%02x ",ptr_pri[i]);
		}
		sed_printf1("\n\n");
	}
#endif

	if(op == RTK_ENC){
		/*
		//encrypt Example :
		//plainText :
		sig = InPutFromStr("0001ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00176ea0b4c829d9ae4aa3b2a056467c810a649d5b7250de9177dfffbed1839278", HEX);
		//public key
		mod  = InPutFromStr("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", HEX);
		r2   = InPutFromStr("A09CC11BC8E1D05D468FABF4FCB62AA861FC15A4FE49E53EA7568172625F79B40E04F1545BF52A1C940998AA5301FED02A4BC12FAEE58D920CFE5CF7A5F0ADC3C57E3D527C7F3FCEC95C7E427BD813656E04E5FECFEAA998A7BE51FB83F3995B767D2454C92FAA2D73734B474BF15B7526FD15104F606B5B102D6B7934C348882E810289C4EB492C1F31FC70E85FF7C94D5C466E3A999DFD453BAAE4FD1E166C7F6C194098F27D3E0451AA8CB035459633EA5369760EF1ED20338C20F45E62E66369460C6DA71B4BF9C4E67314DB080606F945F0DF092932FDF550E444ED184CC418DB5A12C6DCA28FE3B5BD1581BD19F235D9C61D02DBD2C8058D547DA7D897", HEX);
		//exponent private
		exp  = InPutFromStr("96829865E411F18D2E083A39B1A4160B980285DF633CAF0953F520F5F7CD299C504B702D0B6A4E31F655F75EA3DF257FD70B6CA7FEAD2A96703C2C95A75FEAFF03DFC14E707C007876373EA571FC50C3F1C13FCEF2FF8C7988E9E4D9E2A636AF0A15BAC94D4B65E79DCCEE6D30E536EB3A0A6FFF56B84743A38D088D30DB3603DDC91EDF9697F764DEB659B172D6907267FE62429891DFBA1C573347911C088F5D0C45A467816316120D893C88224F136EA9B98970D564C34C238D45DADF56F70DC7918DB9C350EDD9782E111D4E6174FD67A1487D91AE343653342BC02EBDD0FDB59A75DC425F8F0D0D1EECABE2C4F337CF6F3594B3FFA3C3057B79AF422149", HEX);
		*/
		exp  = InPutFromAddr(ptr_pri, RSA_2048_KEY_LENGTH);
	}else{
		/*
		//decrypt Example :
		//CipherText :
		sig = InPutFromStr("64712C6494BC4F9318475FB68868BFA3CA3B22450315A9E23F21A383AFB91754E330FA40FB76C06FFE68968E0D7E6E0E0EB4AADFDA953DAAE7C75EDFCF36AE95E05AE6BE1482DBB36D2E5C51CA686D645207451115AB650E766AA04CDFA26C556C6C9D9109D839761B1E634C0B2BE98CF7F054DEB38F4D978EDCE887D4B51C198AB3FF9C5A0A5618519C1160E67AFAE56F5358058A18591A24288AEA85F9116393B28A698467D8ECB7AC78DEDE9B6518062E01493A7663AE98CD89A9F48DAAB3459C0A66FD5D13C1F854564FB7056E7253E058B819E09E21B7F35AF206705E4E7FAF0CB498BD9F614274BBF632F966F3CA05A07183DAC7953CF4B079B60BB9AD", HEX);
		//public key
		mod  = InPutFromStr("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", HEX);
		r2   = InPutFromStr("A09CC11BC8E1D05D468FABF4FCB62AA861FC15A4FE49E53EA7568172625F79B40E04F1545BF52A1C940998AA5301FED02A4BC12FAEE58D920CFE5CF7A5F0ADC3C57E3D527C7F3FCEC95C7E427BD813656E04E5FECFEAA998A7BE51FB83F3995B767D2454C92FAA2D73734B474BF15B7526FD15104F606B5B102D6B7934C348882E810289C4EB492C1F31FC70E85FF7C94D5C466E3A999DFD453BAAE4FD1E166C7F6C194098F27D3E0451AA8CB035459633EA5369760EF1ED20338C20F45E62E66369460C6DA71B4BF9C4E67314DB080606F945F0DF092932FDF550E444ED184CC418DB5A12C6DCA28FE3B5BD1581BD19F235D9C61D02DBD2C8058D547DA7D897", HEX);
		//exponent public
		exp = move_p(65537);
		*/
		exp  = move_p(65537);
	}

	sig = InPutFromAddr((unsigned char *)ptr_txt, RSA_SIGNATURE_LENGTH);

	if(r2_enable){
		r2  = InPutFromAddr((unsigned char *)ptr_r2,  RSA_2048_KEY_LENGTH);
		//r2   = InPutFromStr("A09CC11BC8E1D05D468FABF4FCB62AA861FC15A4FE49E53EA7568172625F79B40E04F1545BF52A1C940998AA5301FED02A4BC12FAEE58D920CFE5CF7A5F0ADC3C57E3D527C7F3FCEC95C7E427BD813656E04E5FECFEAA998A7BE51FB83F3995B767D2454C92FAA2D73734B474BF15B7526FD15104F606B5B102D6B7934C348882E810289C4EB492C1F31FC70E85FF7C94D5C466E3A999DFD453BAAE4FD1E166C7F6C194098F27D3E0451AA8CB035459633EA5369760EF1ED20338C20F45E62E66369460C6DA71B4BF9C4E67314DB080606F945F0DF092932FDF550E444ED184CC418DB5A12C6DCA28FE3B5BD1581BD19F235D9C61D02DBD2C8058D547DA7D897", HEX);
	}
	mod = InPutFromAddr((unsigned char *)ptr_pub, RSA_2048_KEY_LENGTH);

	sed_printf1("Start to %srypt ...\n",(op == RTK_ENC)? "Enc":"Dec");
	if(r2_enable){
		sed_printf1("Hardware\n");
		res = move_p(1);
		for ( i = BI_chkmsbbit (exp); i >= 0; i-- )
	    {
	        hwsu_mul_mod ( res, r2, res, res, mod, RSA_SIGNATURE_LENGTH);

	        if ( BI_is_bit_set (exp, i) == 1 )
	        {
	            //hwsu_mont ( res, res, sig, mod, RSA_SIGNATURE_LENGTH);
				hwsu_mul_mod ( res, r2, res, sig, mod, RSA_SIGNATURE_LENGTH);
	        }
	    }

	}else{
		sed_printf1("Software\n");

		res = Exp_Mod(sig, exp, mod);
	}

	OutPutToAddr(res, (unsigned char *)output_addr, 1);
	t1 = output_addr;

	// bypass PKCS#1 v1.5 block format
#ifndef SKIP_skip_pkcs_v1_5_padding //skip skip_pkcs_v1_5_padding
	tmp = skip_pkcs_v1_5_padding((char *)output_addr);
	t1 += tmp;
#endif
	my_freeAll();

	// RSA result address (without padding bytes)
	return t1;
}

#else

unsigned int do_RSA(unsigned char op,
					const unsigned int text_addr,
					const unsigned int rsa_key_addr,
					const unsigned int output_addr)
{
	BI *base, *exp, *mod, *res;
	unsigned int t1;
	unsigned char* ptr_txt;
	unsigned char* ptr_pub;
	unsigned char* ptr_pri;
	//unsigned int tmp;
	unsigned int i;

	ptr_txt = (unsigned char*)text_addr;
	ptr_pub = (unsigned char*)rsa_key_addr;
	if(op == RTK_ENC){
		ptr_pri = ptr_pub+RSA_2048_KEY_LENGTH;
	}

#if 1
	if(1){
		sed_printf1("%s(%d)\n\n",__func__,__LINE__);
		sed_printf1("%srypt Data:",(op == RTK_ENC)? "Enc":"Dec");
		for(i=0;i<RSA_SIGNATURE_LENGTH;i++){
			if((i%16)==0)
				sed_printf1("\n");
			sed_printf1("%02x ",ptr_txt[i]);
		}

		sed_printf1("\n\nPublic Key:");
		for(i=0;i<RSA_2048_KEY_LENGTH;i++){
			if((i%16)==0)
				sed_printf1("\n");
			sed_printf1("%02x ",ptr_pub[i]);
		}
		sed_printf1("\n\n");

		if(op == RTK_ENC){
			sed_printf1("Private Key:");
			for(i=0;i<RSA_2048_KEY_LENGTH;i++){
				if((i%16)==0)
					sed_printf1("\n");
				sed_printf1("%02x ",ptr_pri[i]);
			}
			sed_printf1("\n\n");
		}
	}
#endif

	if(op == RTK_ENC){
		/*
		//encrypt Example :
		//plainText :
		base = InPutFromStr("0001ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00176ea0b4c829d9ae4aa3b2a056467c810a649d5b7250de9177dfffbed1839278", HEX);
		//public key
		mod  = InPutFromStr("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", HEX);
		//private key
		exp  = InPutFromStr("96829865E411F18D2E083A39B1A4160B980285DF633CAF0953F520F5F7CD299C504B702D0B6A4E31F655F75EA3DF257FD70B6CA7FEAD2A96703C2C95A75FEAFF03DFC14E707C007876373EA571FC50C3F1C13FCEF2FF8C7988E9E4D9E2A636AF0A15BAC94D4B65E79DCCEE6D30E536EB3A0A6FFF56B84743A38D088D30DB3603DDC91EDF9697F764DEB659B172D6907267FE62429891DFBA1C573347911C088F5D0C45A467816316120D893C88224F136EA9B98970D564C34C238D45DADF56F70DC7918DB9C350EDD9782E111D4E6174FD67A1487D91AE343653342BC02EBDD0FDB59A75DC425F8F0D0D1EECABE2C4F337CF6F3594B3FFA3C3057B79AF422149", HEX);
		*/
		//sed_printf1("skip encrypt!!!");
		//return 256;
		//exp  = InPutFromAddr((unsigned char *)(rsa_key_addr+RSA_2048_KEY_LENGTH), RSA_2048_KEY_LENGTH);
		exp  = InPutFromAddr(ptr_pri, RSA_2048_KEY_LENGTH);

	}else{
		/*
		//decrypt Example :
		//CipherText :
		//base = InPutFromStr("64712C6494BC4F9318475FB68868BFA3CA3B22450315A9E23F21A383AFB91754E330FA40FB76C06FFE68968E0D7E6E0E0EB4AADFDA953DAAE7C75EDFCF36AE95E05AE6BE1482DBB36D2E5C51CA686D645207451115AB650E766AA04CDFA26C556C6C9D9109D839761B1E634C0B2BE98CF7F054DEB38F4D978EDCE887D4B51C198AB3FF9C5A0A5618519C1160E67AFAE56F5358058A18591A24288AEA85F9116393B28A698467D8ECB7AC78DEDE9B6518062E01493A7663AE98CD89A9F48DAAB3459C0A66FD5D13C1F854564FB7056E7253E058B819E09E21B7F35AF206705E4E7FAF0CB498BD9F614274BBF632F966F3CA05A07183DAC7953CF4B079B60BB9AD", HEX);
		//public key
		//mod  = InPutFromStr("B9975438AF3F83EB3F74DBA10DB8B8C3DAD35F89AB81B7EC7A64A9A841054302F148B0B72A5E716511FD65C89374B09CA8C593D32EC53A8183944DBFDEF72263FA80CB0FA86D03D4DB14383925D2F0666EEEE2649D305A0EA8AF95BE629DD42548D88A99642F509C8A24E3112618C91B56CF0EE80CDE44D9486BE9A4675E00481579EC0A62C0FF8838C2CCFAAD9060F376ED8476894305D8FFEF1D469EF62B743DBA11FA5481C3828EC0883F12FF9440FCBFC6A418F463030C3D19711719B66E9F9B925AACF87A982710E6621F9473D801E5958F7C2C34C7304C7F481D77452BEC2A71C3D2FE52AC00DB5C17E32EE3DFBD4FA5DD8465BB720016E5DDEC39E4AF", HEX);
		//exp = move_p(65537);
		*/
		exp  = move_p(65537);
	}
	base = InPutFromAddr(ptr_txt, RSA_SIGNATURE_LENGTH);
	mod  = InPutFromAddr(ptr_pub, RSA_2048_KEY_LENGTH);

	sed_printf1("Start to %srypt ...\n",(op == RTK_ENC)? "Enc":"Dec");

#if 1
	res = Exp_Mod(base, exp, mod);
#else
	res = move_p(1);
	res = Mod(res, mod);
	while (!isZero(exp)) {
		t1 = Mod_p(exp, 2);

		if (t1 != 0) {
			res = Mul(res, base);
			res = Mod(res, mod);
		}

		base = Mul(base, base);
		base = Mod(base, mod);
		exp = Div_p(exp, 2);
	}

#endif

	OutPutToAddr(res, (unsigned char *)output_addr, 1);

	t1 = output_addr;

	// bypass PKCS#1 v1.5 block format
#ifndef SKIP_skip_pkcs_v1_5_padding //skip skip_pkcs_v1_5_padding
	tmp = skip_pkcs_v1_5_padding((char *)output_addr);
	t1 += tmp;
#endif
	my_freeAll();

	// RSA result address (without padding bytes)
	return t1;
}
#endif

/*
 * bypass PKCS#1 v1.5 block format
 */
#ifndef SKIP_skip_pkcs_v1_5_padding
unsigned int skip_pkcs_v1_5_padding(char *ptr)
{
	unsigned int skipped;
	int i;
	const char algo_id[19] = {
		0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
		0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
		0x00, 0x04, 0x20};
	char pkcs_padding[0xe0];

	// construct padding header
	pkcs_padding[0] = 0;
	pkcs_padding[1] = 0x1;
	i = sizeof(pkcs_padding) - sizeof(algo_id);
	memset(pkcs_padding + 2, 0xff, i - 3);
	pkcs_padding[i - 1] = 0;
	copy_memory(pkcs_padding + i, (char *)algo_id, sizeof(algo_id));

	if (compare_memory(pkcs_padding, ptr, sizeof(pkcs_padding)) == 0)
		skipped = sizeof(pkcs_padding);
	else
		skipped = 0;

	return skipped;
}
#endif //?#ifndef SKIP_skip_pkcs_v1_5_padding

void *get_RSA_memory_pool(void)
{
	return (void *)MALLOC_BASE;
}
