#include "dvrboot_inc/util.h"
#include "dvrboot_inc/string.h"
#include "dvrboot_inc/otp_reg.h"
#include "dvrboot_inc/io.h"

#define NDS_MODE  			1
#define RTK_MODE  			2
#define DCAS_MODE 			3
#define SECURE_BOOT_MODE 	RTK_MODE

#define BURN_DEFAULT_EFUSE_KEY

#ifdef BURN_DEFAULT_EFUSE_KEY
	#if (SECURE_BOOT_MODE == RTK_MODE) // program RTK key
		#define PROGRAM_RTK_RSA
	#elif (SECURE_BOOT_MODE == DCAS_MODE) // program DCAS key
		#define PROGRAM_DCAS_RSA
	#else
		"FIX ME - please assign valid secure mode"
	#endif

	#define PROGRAM_ACPU_AES

	#define PROGRAM_SCPU_AES

	#define PROGRAM_EFUSE_KEY_MODE_TO_DCAS // magellan_EFUSE_Table.xls
#endif

#if 0 // be careful when using this efuse bit
	#if (SECURE_BOOT_MODE == RTK_MODE) // enable RTK boot
		#define PROGRAM_SECURITYMODE_TO_RTK
	#elif (SECURE_BOOT_MODE == DCAS_MODE) // enable DCAS boot
		#define PROGRAM_SECURITYMODE_TO_DCAS
	#else
		"FIX ME - please assign valid secure mode"
	#endif
#endif
	
//#define PROGRAM_TEST

#define CHECK_RSA_EFUSE_DATA

#define DRY_RUN

#define EFUSE_KEY_MODE_BIT_NUM	3785
#define SECURITY_BOOT_BIT_NUM	3786

#define EFUSE_TEST_BIT_NUM		3792

#define PROGRAM_RSA_START_BYTE			0
#define PROGRAM_DCAS_RSA_START_BYTE		0
#define PROGRAM_ACPU_AES_START_BYTE		256
#define PROGRAM_SCPU_AES_START_BYTE		256 + 16

extern unsigned char rsa_pub_key[];
extern unsigned char rsa_pub_key_end;
extern unsigned char dcas_rsa_pub_key[];
extern unsigned char dcas_rsa_pub_key_end;
extern unsigned char aes_key_acpu[];
extern unsigned char aes_key_acpu_end;
extern unsigned char aes_key_scpu[];
extern unsigned char aes_key_scpu_end;

PrintFuncPtr_t rtprintf;
Flush_Dcache_AllPtr_t rtflush_dcache_all;

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned int g_OTP_KEY[4];
unsigned int g_RSA_KEY[32];
unsigned int g_RSA_KEY_LENGTH = 2048 / 8;
unsigned int uID[2];
unsigned int g_dry_run = 0;
unsigned int g_program = 0;

void efuse_byte_hexdump(const char *str, unsigned int addr, unsigned int length)
{
	unsigned int i;
	
	if( 0 ) {
		rtprintf("NULL\n");
		return;
	}

	rtprintf("%s (0x%08x)\n", str, addr);

	for (i = 0; i < length; i++) {
		//rtprintf("%02x", (unsigned int)(ptr[i]));
		rtprintf("%02x", rtd_inb(addr));
		addr++;
		if ((i & 0xf) == 0xf)
			rtprintf("\n");
		else
			rtprintf(" ");
	}
	rtprintf("\n");
}

static int get_options(int argc, char **argv)
{
	int i,j, input_otp_key=0, input_uid_key=0, input_rsa_key, ret;

	for (i = 0, input_otp_key = 0; i < argc; i++) {
		//Kh
		if (strstr(argv[i], "Kh=") != 0) {
			int j;
			char *key_str, piece[9];

			key_str = argv[i] + 3;		// skip "Kh=" characters
			if (strlen(key_str) != 32) {
				rtprintf("kh key length invalid\n");
				return -1;
			}

			for (j = 0; j < 4; j++, key_str+=8) {
				memset(piece, 0, sizeof(piece));
				copy_memory(piece, key_str, 8);
				//check non-hex character
				ret = IsHexStr(piece);
				if (ret == -1)
				{
					rtprintf("Wrong input key, must be hex format \n");
					return -1;
				}
				g_OTP_KEY[j] = hexstr2int(piece);
			}

			//check all zero case
			if (g_OTP_KEY[0]==0&&g_OTP_KEY[1]==0&&g_OTP_KEY[2]==0&&g_OTP_KEY[3]==0)
			{
				rtprintf("Wrong input key, can't be all zero \n");
				return -2;
			}

			input_otp_key = 1;
		}

		//unique chip id
		//for uID, it's scrambled mac + beef = 64 bits
		if (strstr(argv[i], "uID=") != 0) {
			char *key_str,piece[9];
			memset(piece, 0, sizeof(piece));
			memset(uID, 0, sizeof(uID));

			key_str = argv[i] + 4;		// skip "uID=" characters
			if (strlen(key_str) != 16) {
				rtprintf("unique chip ID length invalid\n");
				return -1;
			}

			for (j = 0; j < 2; j++, key_str+=8) {
				memset(piece, 0, sizeof(piece));
				copy_memory(piece, key_str, 8);
				//check non-hex character
				ret = IsHexStr(piece);
				if (ret == -1)
				{
					rtprintf("Wrong input key, must be hex format \n");
					return -1;
				}
				rtprintf("uID%d=%s\n", j,piece);
				uID[j] = hexstr2int(piece);
			}
			//check all zero case
			if (uID[0]==0&&uID[1]==0)
			{
				rtprintf("Wrong unique chip id, can not be all zero format \n");
				return -1;
			}
			input_uid_key = 1;
		}


		// dry-run (do not program OTP, just check crc)
		if (strstr(argv[i], "dry-run") != 0) {
			rtprintf("g_dry_run = 1 \n");
			g_dry_run = 1;
		}

		// program OTP
		if (strstr(argv[i], "program") != 0) {
			rtprintf("g_program = 1 \n");
			g_program = 1;
		}
	}

		return 1;
}

int start_bit_program(UINT32 bitnum)
{
	UINT32 prog_addr_val, data_bit_select, address_input;

#ifndef DRY_RUN
	// enable program OTP
	rtd_outl(OTP_EF_CTRL, 0x00C00401);
#endif

	udelay(5);

	data_bit_select = (bitnum & 0x7) << 9;  			//[11:9]
	address_input = (bitnum >> 3) & 0x1ff;				//[8:0]
	prog_addr_val = EF_CTRL_WRITE_EN1 | address_input | data_bit_select;	//[8:0][11:9]
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
	rtprintf("[%s]start_bit_program 0x%x\n",__FUNCTION__, rtd_inl(OTP_EFUSE_SECUREBOOT));

}

int start_program(UINT32 startbyte, UINT32 totalbytes, UINT8 * src_array)
{
	UINT32 i, j;
	UINT32 addr, value;
	UINT32 prog_addr_val, data_bit_select, address_input;
	UINT32 total = 0;		// number of bits successfully programmed

#ifndef DRY_RUN
	// enable program OTP
	rtd_outl(OTP_EF_CTRL, 0x00C00401);
	udelay(5);
#endif
	for (i = startbyte; i < (startbyte + totalbytes); i += 4) {
	value = REG32(src_array + i - startbyte);
	rtprintf("\n[%s]value:0x%x\n", __FUNCTION__,value);

		// for each bit in the word
		for (j = 0; j < 32; j++) {

			//rtprintf("addr:%d, [%x]\n",(i * 8 + j), (value >> j) & 0x1);
			// check if need to program
			if ((value >> j) & 0x1) {
				addr = i * 8 + j;	// bit address

				data_bit_select = (addr & 0x7) << 9;  				//[11:9]
				address_input = (addr >> 3) & 0x1ff;				//[8:0]
				prog_addr_val = EF_CTRL_WRITE_EN1 | address_input | data_bit_select;	//[8:0][11:9]
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
#endif
	//rtprintf("[%s]total %d bits programmed\n",__FUNCTION__, total);
}

int do_program(void)
{
 	UINT32	rsa_pub_key_size  = (unsigned int )(&rsa_pub_key_end  - rsa_pub_key);
 	UINT32	dcas_rsa_pub_key_size  = (unsigned int )(&dcas_rsa_pub_key_end  - dcas_rsa_pub_key);

    UINT32	aes_key_acpu_size = (unsigned int )(&aes_key_acpu_end - aes_key_acpu);
    UINT32	aes_key_scpu_size = (unsigned int )(&aes_key_scpu_end - aes_key_scpu);

	int res = -1;
	int wait_count;

	rtprintf("%s....\n", __FUNCTION__);

#ifdef PROGRAM_RTK_RSA
	start_program(PROGRAM_RSA_START_BYTE, rsa_pub_key_size, rsa_pub_key);
#endif

#ifdef PROGRAM_DCAS_RSA
	start_program(PROGRAM_DCAS_RSA_START_BYTE, dcas_rsa_pub_key_size, dcas_rsa_pub_key);
#endif

#ifdef PROGRAM_ACPU_AES
	start_program(PROGRAM_ACPU_AES_START_BYTE, aes_key_acpu_size, aes_key_acpu);
#endif

#ifdef PROGRAM_SCPU_AES
	start_program(PROGRAM_SCPU_AES_START_BYTE, aes_key_scpu_size, aes_key_scpu);
#endif

#ifdef PROGRAM_EFUSE_KEY_MODE_TO_DCAS
	//efuse key mode (bit number:3785)
	//0: HDCP
	//1: DCAS
	start_bit_program(EFUSE_KEY_MODE_BIT_NUM);
#endif

//Important !!!!!
//we can't program secre bit now, due to our romcode in chip  is fail
//enable these two bits will force boot from rom
	//Security boot for ACPU (bit number:[3786:3785])
	//00:security boot disable (default state)
	//10: Realtek secure boot
	//11: DCAS secure boot
#ifdef PROGRAM_SECURITYMODE_TO_RTK
	rtprintf("*** burn efuse bit %d\n", SECURITY_BOOT_BIT_NUM);
	start_bit_program(SECURITY_BOOT_BIT_NUM + 1);
#endif

#ifdef PROGRAM_SECURITYMODE_TO_DCAS
	rtprintf("*** burn efuse bit %d\n", SECURITY_BOOT_BIT_NUM);
	start_bit_program(SECURITY_BOOT_BIT_NUM);
	rtprintf("*** burn efuse bit %d\n", SECURITY_BOOT_BIT_NUM+1);
	start_bit_program(SECURITY_BOOT_BIT_NUM + 1);
#endif

#ifdef PROGRAM_TEST
		start_bit_program(EFUSE_TEST_BIT_NUM);
#endif

	res = 0;	// complete without failure

final:


	return res;
}

static void show_help(void)
{
	rtprintf("\nUsage:\n");
	rtprintf("go 0x1500000 [program|dry-run]\n");
	rtprintf("\nOption:\n");
	rtprintf("\tprogram:\nprogram OTP bit \n");
	rtprintf("\tdry-run:\n do not program OTP\n");
}

/************************************************************************
 *
 *                          efusemain
 *  Description :
 *  -------------
 *
 *  Parameters :
 *  ------------
 *
 *
 *
 *  Return values :
 *  ---------------
 *
 *
 *
 *
 ************************************************************************/
int efusemain (int argc, char * const argv[])
{
	unsigned int byte;
	unsigned int bit;
	unsigned int flag;
#if 1
	// get fun ptr of printf(...) from specified address
	#define DUMMY							(*((unsigned int *)0x00020060))
	#define DUMMY2							(*((unsigned int *)0x00020064))
	#define UBOOT_PRINTF_ADDRESS_TAG		(*((unsigned int *)0x00020068))
	#define UBOOT_PRINTF_ADDRESS 			(*((unsigned int *)0x0002006C))
	#define UBOOT_FLUSH_DCACHE_ADDRESS_TAG 	(*((unsigned int *)0x00020070))
	#define UBOOT_FLUSH_DCACHE_ADDRESS		(*((unsigned int *)0x00020074))
	#define DUMMY7							(*((unsigned int *)0x00020078))
	#define DUMMY8							(*((unsigned int *)0x0002007C))

	if( UBOOT_PRINTF_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
		rtprintf = (PrintFuncPtr_t) (UBOOT_PRINTF_ADDRESS);
		rtprintf("\n\nHello World, get printf ptr=%p\n\n", rtprintf);
	}
	else {
		rtprintf = NULL;
	}
	if( UBOOT_FLUSH_DCACHE_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
		rtflush_dcache_all = (PrintFuncPtr_t) (UBOOT_FLUSH_DCACHE_ADDRESS);
	}
	else {
		rtflush_dcache_all = NULL;
	}
#endif

	int		ret = -1;
	UINT32	tmp;
	UINT32	LSR;
	
#ifdef CHECK_RSA_EFUSE_DATA
	efuse_byte_hexdump("RSA key", 0xb8038000, 0x100);
	
	byte = 3785>>3;
	bit  = 3785-(byte<<3);
	flag = 1<<bit;
	if( rtd_inb((0xb8038000+byte)) & flag ) {
		rtprintf("efsue bit 3785 = 1, efuse byte %d = 0x%02x\n", byte, rtd_inb((0xb8038000+byte)));
	}
	else {
		rtprintf("efsue bit 3785 = 0, efuse byte %d = 0x%02x\n", byte, rtd_inb((0xb8038000+byte)));
	}
	
	byte = 3786>>3;
	bit  = 3786-(byte<<3);
	flag = 3<<bit;
	rtprintf("efsue bit 3787:3786 = 0x%02x, efuse byte %d = 0x%02x\n", (rtd_inb((0xb8038000+byte)) >> bit)&0x03, byte, rtd_inb((0xb8038000+byte)));
#endif	

#ifdef DRY_RUN
	rtprintf("\n(DRY_RUN)program Magellan EFUSE utility v0.1 (%s)\n", __DATE__);
#else
	rtprintf("\nprogram RTD299X EFUSE utility v0.1 (%s)\n", __DATE__);
#endif

	// reset key array & read input key from argument
	set_memory(g_OTP_KEY, 0xff, sizeof(g_OTP_KEY));
	uID[0]=0;
	uID[1]=0;
	g_dry_run = 0;
	g_program = 1;

	if ((ret = get_options(argc, argv)) < 0)
	{
		rtprintf("get_options: goto finally\n");
		goto finally;
	}

	if (g_dry_run) {
		goto exit;
	}

	if ((ret = do_program()) != 0) {
		goto finally;
	}

finally:
	//Efuse burn ok and fail must be the same length -> for secure mp tool checking
	if (ret == 0) {
		rtprintf("program OTP OKOKOKOKOKOK!!!!!!!\n");
	    rtprintf("Finish\n");
	}
	else {
		rtprintf("program OTP failfailfail(%d)!!!\n", ret);
	}

#ifdef CHECK_RSA_EFUSE_DATA
	efuse_byte_hexdump("RSA key", 0xb8038000, 0x100);
	
	byte = 3785>>3;
	bit  = 3785-(byte<<3);
	flag = 1<<bit;
	if( rtd_inb((0xb8038000+byte)) & flag ) {
		rtprintf("efsue bit 3785 = 1, efuse byte %d = 0x%02x\n", byte, rtd_inb((0xb8038000+byte)));
	}
	else {
		rtprintf("efsue bit 3785 = 0, efuse byte %d = 0x%02x\n", byte, rtd_inb((0xb8038000+byte)));
	}
	
	byte = 3786>>3;
	bit  = 3786-(byte<<3);
	flag = 3<<bit;
	rtprintf("efsue bit 3787:3786 = 0x%02x, efuse byte %d = 0x%02x\n", (rtd_inb((0xb8038000+byte)) >> bit)&0x03, byte, rtd_inb((0xb8038000+byte)));
#endif	

exit:
	rtprintf("\npress ESC to exit\n");

    return 0;
}
