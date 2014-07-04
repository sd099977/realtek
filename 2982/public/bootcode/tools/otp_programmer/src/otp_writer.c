/****************************************************************************************
* Direct Test Name:     OTP Programmer 
* Author:               
* Date:                 2014/06/xx
* Description:          RTD298x OTP Programmer
* Copyright (C) 2014 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "mis_reg_saturn.h"
#include "mcp.h"
#include "otp_reg.h"
#include "otp_info.h"
#include "io.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
//#define OTP_DDR_BASE	0xa3017000	
#define OTP_DDR_BASE	0x02000000	//for rtd298x

#define RBUS_CHIP_ID_REG	0xb8060000

/* print more debug msg */
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG 1
#else
#define DEBUG_MSG 0
#endif

#define debug_print(fmt, ...) \
	do { if (DEBUG_MSG) printf(fmt, __VA_ARGS__); } while (0)

#define REG_OR(reg, val)    						\
        do{											\
        	INT32U tmpREG=0;						\
        	tmpREG = REG32(reg);					\
        	tmpREG &= ~val;							\
        	tmpREG |= val;							\
        	INITIAL_DDR((INT32U*)reg, 0x1, tmpREG);	\
        }while(0);
        	//printf("REG_OR: reg=0x%08x, val=0x%08x, tmpREG=0x%08x\n", reg, val, tmpREG);	\

#define REG_SET(reg, val)							\
		do{ 										\
			INITIAL_DDR((INT32U*)reg, 0x1, val);	\
		}while(0);
			//printf("REG_SET: reg=0x%08x, val=0x%08x\n", reg, val);	\

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void encode_ecc_byte(unsigned short int crc_data_in);
extern void crc_init(bool all_reset);
extern unsigned short int crc_get(void);
extern void init_uart(void);
extern int IsHexStr(char *s);

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned short int data_buf[];
extern unsigned short int crc_result;

extern unsigned char builtin_otp_map[];
extern unsigned char builtin_otp_map_end;


extern unsigned int UartReg;
/************************************************************************
 *  Public variables
 ************************************************************************/
INT32U g_OTP_KEY[4];
//INT32U g_RSA_KEY[32];
INT32U g_RSA_KEY_LENGTH = 2048 / 8;
INT32U uID[2];
INT32U g_dry_run = 0;
INT32U g_program = 0;
INT32U g_original_value[OTP_BIT_NUM / 32];	// OTP bit value before program

unsigned int builtin_otp_map_size;
/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Public function prototype
 ************************************************************************/
unsigned short int get_hw_crc(bool init_state);
unsigned short int calculate_sw_crc(const void *base, unsigned int byte_len);

/************************************************************************
 *  Static function
 ************************************************************************/
#if 0 //not used	
static void wait(int us)
{
	sys_wait_us(us);
}

static void WAIT_DONE(INT32U addr, INT32U mask, INT32U value)
{
	while ( (REG32(addr)& mask) != value ){
		asm("nop");      
	}   	
}

static void auto_read(INT32U DDR)
{
	INT32U* addr1;	

	WRITE_REG_INT32U(MIS_EF_CTRL_reg, MIS_EF_CTRL_write_enable3(1)
		| MIS_EF_CTRL_auto_rd_req(0));
	WRITE_REG_INT32U(MIS_EF_CTRL_reg, MIS_EF_CTRL_write_enable3(1)
		| MIS_EF_CTRL_auto_rd_req(1));

	while (READ_REG_INT32U(((MIS_EF_CTRL_reg)|0x100000) != 0)) {
	   // wait for auto_read_done==0
	}

	addr1 = (void*)(DDR);
	*addr1 = READ_REG_INT32U(MIS_EF_DATA_70);
	*(addr1+1) = READ_REG_INT32U(MIS_EF_DATA_71);
}

static void pgm_fuse(INT32U A, INT32U B)
{
//	 //check progarm status	
//   WAIT_DONE(MIS_EF_CTRL_ST_reg, 0x10000, 0);
//   
//   // enable program efuse
//   WRITE_REG_INT32U(MIS_EF_CTRL_reg, 
//   MIS_EF_CTRL_write_enable4(1)|
//   MIS_EF_CTRL_en_pro_efuse(1));
//   
//	 //check progarm status	   
//   WAIT_DONE(MIS_EF_CTRL_ST_reg, 0x10000, 0x10000);

	// program procedure 

	// assert program and issue address,[7:0]={A=0, B=[7:0]}, [15:8]= { A=1, B=[7:0]}...
	WRITE_REG_INT32U(
	MIS_EF_CTRL_reg, 
	MIS_EF_CTRL_write_enable1(1)|
	MIS_EF_CTRL_program(1)|
	MIS_EF_CTRL_enb(0)|
	MIS_EF_CTRL_a(A)|
	MIS_EF_CTRL_b(B));
	
	wait(0x10); 				// DELAY 10us
	
	// disassert program
	WRITE_REG_INT32U(
	MIS_EF_CTRL_reg, MIS_EF_CTRL_write_enable1(1)|
	MIS_EF_CTRL_program(0));

//   //disable program mode
//   WRITE_REG_INT32U(MIS_EF_CTRL_reg, 
//   MIS_EF_CTRL_write_enable4(1)|
//   MIS_EF_CTRL_en_pro_efuse(0));
}
#endif

static void INITIAL_DDR(INT32U* DDR_BASE, int size, INT32U value)
{
	int i;
	for ( i = 0 ; i < size ; i++ ) {
		*(DDR_BASE + i) = value;
	}
}	        

int check_cp_key(void)
{
	INT32U src_len;
	INT8U *src_addr, *dst1_addr, *dst2_addr;
	int res;
	
	// prepare test data
	src_len = 0x80;
	src_addr = (INT8U *) 0xa4000000;
	INITIAL_DDR((INT32U *)src_addr, src_len, 0xffffffff);
	
	// encrypt test data with E-fuse key
	dst1_addr = (INT8U *) 0xa4010000;
	res = AES_CBC_encrypt(src_addr, src_len, dst1_addr, NULL);
	if (res)
		return res;
	
	// encrypt test data with CP key
	dst2_addr = (INT8U *) 0xa4020000;
	res = AES_CBC_encrypt(src_addr, src_len, dst2_addr, g_OTP_KEY);
	if (res)
		return res;
	
	return compare_memory(dst1_addr, dst2_addr, src_len);
}

static int get_options(int argc, char **argv)
{

#if 0
	int i,j, input_otp_key=0, input_uid_key=0, ret;

	for (i = 0, input_otp_key = 0; i < argc; i++) {
		//Kh
		if (strstr(argv[i], "Kh=") != 0) {
			int j;
			char *key_str, piece[9];
			
			key_str = argv[i] + 3;		// skip "Kh=" characters
			if (strlen(key_str) != 32) {
				printf("kh key length invalid\n");
				return -1;
			}
			
			for (j = 0; j < 4; j++, key_str+=8) {
				memset(piece, 0, sizeof(piece));
				copy_memory(piece, key_str, 8);
				//check non-hex character
				ret = IsHexStr(piece);
				if (ret == -1)
				{
					printf("Wrong input key, must be hex format \n");
					return -1;
				}
				g_OTP_KEY[j] = hexstr2int(piece);
				//printf("%d: %s\n", j, piece);
			}
			
			//check all zero case
			if (g_OTP_KEY[0]==0&&g_OTP_KEY[1]==0&&g_OTP_KEY[2]==0&&g_OTP_KEY[3]==0)
			{
				printf("Wrong input key, can't be all zero \n");
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
				printf("unique chip ID length invalid\n");
				return -1;
			}

			for (j = 0; j < 2; j++, key_str+=8) {
				memset(piece, 0, sizeof(piece));
				copy_memory(piece, key_str, 8);
				//check non-hex character
				ret = IsHexStr(piece);
				if (ret == -1)
				{
					printf("Wrong input key, must be hex format \n");
					return -1;
				}
				printf("uID%d=%s\n", j,piece);
				uID[j] = hexstr2int(piece);
			}
			//check all zero case
			if (uID[0]==0&&uID[1]==0)
			{
				printf("Wrong unique chip id, can not be all zero format \n");
				return -1;
			}
			input_uid_key = 1;
		}


#else
		int i;
	for (i = 0; i < argc; i++) {
#endif
		// dry-run (do not program OTP, just check crc)
		if (strstr(argv[i], "dry-run") != 0) {
			g_dry_run = 1;
		}

		// program OTP
		if (strstr(argv[i], "program") != 0) {
			g_program = 1;
		}
	}

	return 1;
}


static void print_keys(const char *name, unsigned int base, unsigned int len)
{
	unsigned int i;

	printf("%s:\n", name);
	for (i = 0; i < len; i += 4) {
		printf("\t0x%x = 0x%08x\n", (base + i), REG32(base + i));
	}
}

void do_init(const unsigned int otp_map_base)
{
	printf("%s...\n", __FUNCTION__);

	print_keys("RSA key (in DDR)", 
		otp_map_base, LEN_2048BIT);
	print_keys("NDS LFSR primitive polynomial (in DDR)", 
		otp_map_base + 0x100, LEN_64BIT);
	print_keys("RTK LFSR primitive polynomial (in DDR)", 
		otp_map_base + 0x108, LEN_64BIT);
	print_keys("KCPU AES key (in DDR)", 
		otp_map_base + 0x110, LEN_128BIT);
	print_keys("SCPU AES key (in DDR)", 
		otp_map_base + 0x120, LEN_128BIT);
	print_keys("ESCK (in DDR)", 
		otp_map_base + 0x130, LEN_128BIT);
	print_keys("ESCK LFSR primitive polynomial (in DDR)", 
		otp_map_base + 0x140, LEN_128BIT);
	print_keys("ESCK LFSR primitive polynomial initial value (in DDR)", 
		otp_map_base + 0x150, LEN_128BIT);
	print_keys("SMK (in DDR)", 
		otp_map_base + 0x160, LEN_128BIT);
	print_keys("Debug port password (in DDR)", 
		otp_map_base + 0x170, LEN_64BIT);
	print_keys("Chip id (in DDR)", 
		otp_map_base + 0x198, LEN_64BIT);
    print_keys("HDCP part1 (in DDR)", 
		otp_map_base + 0x1B4, LEN_552BIT);
    print_keys("AUX key (in DDR)", 
		otp_map_base + 0x258, LEN_128BIT);	
    print_keys("HDCP part2 (in DDR)", 
		otp_map_base + 0x280, LEN_2048BIT);

	return;
}

int do_program(const unsigned int otp_map_base)
{
	int i, j;
	int addr, value;
	int reg_value, original_value;
	int res = -1;
	int wait_count;
	int total = 0;		// number of bits successfully programmed
	int estimated_count = 0;

	printf("%s...\n", __FUNCTION__);

	// Change SB2 Timeout to maximum value to prevent RBUS Timeout
	rtd_outl(0xb801A004, 0x30);
	// printf("SB2 0xb801A004=0x%08x\n",rtd_inl(0xb801A004));
	// get original OTP value from register
	for (i = j = 0; j < OTP_SIZE; i++, j+=4)
		g_original_value[i] = rtd_inl(OTP_DDR_MAP_BASE + j);
	//printf("ofset(0x%x):0x%08x\n",j,g_original_value[i]);

	// clear status
	rtd_outl(OTP_STATUS, 0);

	// enable program OTP
	rtd_outl(OTP_CTRL1, 
		SET_OTP_CTRL1_WRITE_EN1(1) | 
		SET_OTP_CTRL1_EN_PROG_FUNC(OTP_PROG_MAGIC));
	//printf("enable program OTP finished!\n");
	for (i = 0; i < OTP_SIZE; i += 4) {
		value = rtd_inl(otp_map_base + i);	// from memory
		original_value = g_original_value[i / 4];
		//debug_print("OTP[%d:%d] (Rbus 0x%x): 0x%08x\n", (i * 8 + 31), (i * 8), (OTP_REG_BASE + i), original_value);

		// for each bit in the word
		for (j = 0; j < 32; j++) {
			addr = i * 8 + j;	// bit address

			// check if need to program
			if ((value >> j) & 0x1) {
				estimated_count++;

				// char if bit address in CPU readable range
				if (original_value != 0xdeaddead) {
					// make sure if OTP bit has already been programmed before
					if ((original_value >> j) & 0x1) {
						debug_print("OTP bit %d already programmed, skip\n", addr);
						continue;
					}
				}

				debug_print("\tprogram OTP bit %d\n", addr);
				rtd_outl( OTP_CTRL, 
					SET_OTP_CTRL_WRITE_EN1(1) |
					SET_OTP_CTRL_MAX_PROG_NUM(0x14) |
					SET_OTP_CTRL_PROG(1) |
					SET_OTP_CTRL_A(addr) );
				wait_count = 0x1000;

				// polling status
				do {
					reg_value = rtd_inl(OTP_STATUS);

					// check fail flag
					if (reg_value & MASK_OTP_STATUS_OTP_FAIL_REG_WR) {
						printf("[ERROR] program OTP bit %d failed, status: 0x%x\n", addr, reg_value);
						res = -addr;
						goto final;
					}

					if (--wait_count == 0) {
						printf(".");
						wait_count = 0x1000;	// reset counter
					}

				} while ((reg_value & MASK_OTP_STATUS_OTP_DONE_REG_WR) == 0);

				// clear status
				reg_value = rtd_inl(OTP_STATUS);
				//debug_print("\tread OTP_STATUS: 0x%x\n", reg_value);
				rtd_outl(OTP_STATUS, 
					reg_value & ~(MASK_OTP_STATUS_OTP_FAIL_REG_WR | MASK_OTP_STATUS_OTP_DONE_REG_WR));
				total++;
			}
		}
	}

	res = 0;	// complete without failure

	final:
	// disable program OTP
	rtd_outl(OTP_CTRL1, 0);

	// clear status (program fail case)
	rtd_outl(OTP_STATUS, 0);

	debug_print("estimated %d bits programmed\n", estimated_count);
	debug_print("total %d bits programmed\n", total);
	return res;
	}

bool check_crc(bool init_state)
{	
	unsigned short int SwCRC_allZero, SwCRC, SwCRC_CP_Set, HwCRC;

	SwCRC_allZero = SwCRC = SwCRC_CP_Set = HwCRC=0xffff;

	printf("%s...\n", __FUNCTION__);

	memset(data_buf, 0, OTP_SIZE);	// reset data buffer
	SwCRC_allZero = calculate_sw_crc(data_buf, OTP_SIZE);
	printf("crc value of all OTP bits zero (by sw): 0x%08x\n", SwCRC_allZero);

	set_data_buf_bit(BIT_OFFSET(3275), BIT_SHIFT(3275));	// set MP test bit: OTP[3275]
	SwCRC_CP_Set = calculate_sw_crc(data_buf, OTP_SIZE);
	printf("crc value with MP test bit burned (by sw): 0x%08x\n", SwCRC_CP_Set);

	SwCRC = calculate_sw_crc((void *)OTP_DDR_BASE, OTP_SIZE);
	printf("crc value of DDR input (by sw): 0x%08x\n", SwCRC);

	HwCRC = get_hw_crc(init_state);
	printf("OTP crc value (by hw): 0x%08x\n", HwCRC);

	if (SwCRC_allZero == HwCRC)
		return(HwCRC == SwCRC_allZero);

	if (SwCRC_CP_Set == HwCRC)
		return(HwCRC == SwCRC_CP_Set);
	else
		return(HwCRC == SwCRC);
}

unsigned short int calculate_sw_crc(const void *base, unsigned int byte_len)
{
	int i;
	int short_int_len = byte_len / 2;
	unsigned short int *buf = (unsigned short int *)base;

	if ((base == NULL) || (byte_len & 0x1)) {
		printf("[ERROR] invalid argument: %s(%x, %d)\n", __FUNCTION__, (int)base, byte_len);
		return 0xffff;
	}

	crc_init(false);
	for (i = 0;i < short_int_len; i++)
		encode_ecc_byte(buf[i]);
	
	return crc_get();
}

int do_check(void)
{	
	printf("%s...\n", __FUNCTION__);
	
	if (check_crc(true))
	{
		printf("crc comparing pass !!\n");
	}
	else
	{
		printf("crc comparing fail !!\n");
		return -1;
	}
	return 0;
}

unsigned short int get_hw_crc(bool init_state)
{
	int tmp;
	unsigned short int result = 0xffff;
	
	debug_print("%s\n", __FUNCTION__);

	// disable crc_en
	rtd_outl(OTP_CTRL1,
		SET_OTP_CTRL1_WRITE_EN2(1) |
		SET_OTP_CTRL1_CRC_EN(0));

	// set crc_ini value
	rtd_outl(OTP_CRC, SET_OTP_CRC_CRC_INI(0xffff));

	// enable crc_en
	rtd_outl(OTP_CTRL1,
		SET_OTP_CTRL1_WRITE_EN2(1) |
		SET_OTP_CTRL1_CRC_EN(1));

	// enable auto_read and polling done
	rtd_outl(OTP_CTRL, 
		SET_OTP_CTRL_WRITE_EN2(1) |
		SET_OTP_CTRL_AUTO_RD_OTP_ALL(1));
	do {
		tmp = rtd_inl(OTP_CTRL) & MASK_OTP_CTRL_AUTO_RD_OTP_ALL;
	} while (tmp != 0);

	// get result from crc_out
	result = rtd_inl(OTP_CRC) & 0xffff;
 	debug_print("HW_CRC: 0x%08x\n", result);

	// disable crc_en
	rtd_outl(OTP_CTRL1,
		SET_OTP_CTRL1_WRITE_EN2(1) |
		SET_OTP_CTRL1_CRC_EN(0));

 	return result;
}

static void show_help(void)
{
	printf("\nUsage:\n");
	printf("   go 0x1500000 [program|dry-run]\n");
	printf("\nOption:\n");
	printf("   program: program OTP bits (get %d OTP bit map starting from 0x%08x)\n", OTP_BIT_NUM, OTP_DDR_BASE);
	printf("   dry-run: just calculate crc value, do not program OTP\n");
}


static int check_program_validation(void)
{
	int ret = 0;
	// check chip is rtd298x
	if (((rtd_inl(RBUS_CHIP_ID_REG) >> 16) & 0xffff) != 0x6330)
	{
		printf("wrong chip!\n");
		ret = -998;
		return ret;
	}

	//bypass verA	
	if ((rtd_inl(RBUS_CHIP_ID_REG) & 0xffff) == 0x0)
	{
		printf("not support in VerA chip!\n");
		ret = -997;
	}

	//skip already programmed
	//check HDCP
	if (rtd_inl(OTP_DDR_MAP_BASE + 0x280) != 0x0)
	{
		printf("OTP had already been programmed\n");
		ret = -997;
	}

	return ret;
}


int app_main(int argc, char **argv)
{
	int ret = -1;
	unsigned int tmp;
	unsigned int LSR;
	int i;

	//get builtin otp map size
	builtin_otp_map_size = (unsigned int)((char *)&builtin_otp_map_end) - (unsigned int)((char *)&builtin_otp_map);

	//auto-detect uart mode
	init_uart();

	printf("\nprogram RTD298x OTP utility v0.7 (%s %s)\n", __DATE__, __TIME__);

	// check if can program OTP or not
	if ((ret = check_program_validation())) {
		printf("error! stop program process!\n");
		goto finally;
	}

	
	// reset key array & read input key from argument
	set_memory(g_OTP_KEY, 0xff, sizeof(g_OTP_KEY));
	uID[0]=0;
	uID[1]=0;
	g_dry_run = g_program = 0;
	
	if ((ret = get_options(argc, argv)) < 0)
	{
		goto finally;
	}

	if ((g_program == 0) && (g_dry_run == 0) && (builtin_otp_map_size != OTP_SIZE)) {
		show_help();
		goto exit;
	}

//start:
	//------------------------------------------//

#if defined(DEBUG)
	printf("\nWarning !!! You are going to program efuse...\n");
	for (i = 10; i >= 0; i--) {
		udelay(1000000);
		printf("\rwait %2d seconds...", i);
	}
	printf("\r                       \n");
#endif

#if defined(DEBUG)
	do_init((unsigned int)&builtin_otp_map);
#endif

	// true program
	if ((ret = do_program((unsigned int)&builtin_otp_map)) != 0) {
		goto finally;
	}

#if 0
	do_init(OTP_DDR_BASE);

	if (g_dry_run) {
		check_crc(true);
		goto exit;
	}
	//------------------------------------------//
	if(g_program)
	{
		if ((ret = do_program(OTP_DDR_BASE)) != 0) {
			goto finally;
		}
	}
	//------------------------------------------//
#endif

finally:
	//------------------------------------------//	
	//Efuse burn ok and fail must be the same length -> for secure mp tool checking
	if (ret == 0) {
		printf("program OTP OKOKOKOKOKOK!!!!!!!\n");
		printf("\nFinish\n");
	}
	else {
		printf("program OTP failfailfail(%d)!!!\n", ret);
		printf("\nEXP\n");
	}
	
exit:
	printf("\npress ESC to exit\n");

	while(1){
		tmp = 0;
		while (((LSR = READ_REG_INT32U(UartReg+0x14)) & LSR_DR) == LSR_DR){
			if ((LSR & (LSR_OE | LSR_PE | LSR_FE | LSR_BI)) != 0x00){
				tmp = READ_REG_INT32U(UartReg+0x0);  // discard the garbage byte
				if ((LSR & LSR_OE) != 0x00) tx_byte((INT8U)'o');
				if ((LSR & LSR_PE) != 0x00) tx_byte((INT8U)'p');
				if ((LSR & LSR_FE) != 0x00) tx_byte((INT8U)'f');
				if ((LSR & LSR_BI) != 0x00) tx_byte((INT8U)'b');
			}
			else {
				tmp = READ_REG_INT32U(UartReg+0x0);  // get data from UART
				
				if (0x0D == tmp) tx_byte(0x0A);  // emulate new line
				if (0x1B == tmp) return(0x12345678);   // "ESC" to exit
				tx_byte((INT8U)tmp);   // others, echo back to UART
			}
		}
	}
}
