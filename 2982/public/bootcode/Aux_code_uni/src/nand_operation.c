
/************************************************************************
 *
 *  nand_operation.c
 *
 *  NAND flash operation for Sirius internal ROM
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include header
 ************************************************************************/
#include "sysdefs.h"
#include "nf_reg.h"
#include "mcp.h"
#include "util.h"
#include "reset_def.h"

/************************************************************************
 *  Definitions
*************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern void sync(void);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int polling_timeout(const unsigned int addr, const unsigned int mask, 
	const unsigned int value, volatile unsigned int timeout);

/************************************************************************
 *  Function body
 ************************************************************************/
static int polling_timeout(const unsigned int addr, const unsigned int mask, 
	const unsigned int value, volatile unsigned int timeout)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("\n");
#endif

	if (timeout == 0) {	// no timeout, use polling_done instead
		while ((REG32(addr) & mask) != value)
			;
		return 0;
	}

	while (((REG32(addr) & mask) != value) && timeout) {
		timeout--;
	}

	return (timeout == 0 ? -1 : 0);
}

static int nand_op_xfer_mode_read(unsigned int cmd, unsigned int addr, unsigned int *p_out, unsigned int len)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(cmd=");
	print_hex(cmd);
	prints(", addr=");
	print_hex(addr);
	prints(", p_out=");
	print_hex((UINT32)p_out);
	prints(", len=");
	print_hex(len);
	prints(")\n");
#endif
	unsigned int i, mem_region, idx;

	if ((p_out == NULL) || (len > 1024))
		return -1;

	//Set data transfer count, SRAM path and access mode		
	REG32(NF_DATA_TL0) = len & 0xff;
	REG32(NF_DATA_TL1) = ((len >> 8) & 0x3f) | 0x80;	// transfer mode
	
	//Set PP
	REG32(NF_PP_RDY) = 0;		// NOt through PP
	REG32(NF_PP_CTL0) = 0x01;	
	REG32(NF_PP_CTL1) = 0;
	
	//Set command
	REG32(NF_CMD1) = cmd & 0xff;
	REG32(NF_ND_CTL) = 0x80;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -1;
	}
	
	//Set address	
	REG32(NF_PAGE_ADR0) = addr & 0xff;
	REG32(NF_PAGE_ADR2) = 0x7<<5;
	REG32(NF_ND_CTL) = 0x81;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -2;
	}
	
	//Enable MultiByteRead XFER mode
	REG32(NF_ND_CTL) = 0x84;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -3;
	}
	
	//Reset PP
	REG32(NF_PP_CTL0) = 0x2;
	
	//Move data to DRAM from PP
	//set 0x30 to enable bit[5] (map_sel), due to out nand list table are implemented for little endian
	for (idx = mem_region = 0; mem_region < 2; mem_region++) {
		REG32(NF_SRAM_CTL) = 0x30 | mem_region;	// PP #1 or PP #2
		for (i = 0; i < 512; i += 4) {
			p_out[idx++] = REG32(NF_SRAM_BASE + i);
			// check copy finish
			if ((idx * 4) >= len)
				goto disable_PP_access;
		}
	}

disable_PP_access:
	REG32(NF_SRAM_CTL) = 0x00;	//# no omitted

#if 0 //defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	hexdump("p_out", p_out, len);
	print_hex(idx);
	prints("\n");
#endif
	return 0;
}

/*
 * NAND operation - read one page
 *
 * input argument:
 *	page_no: page address
 *	dest_addr: DDR address
 *	page_ize: NAND flash page size
 * return:
 *	0 means success, others means failed
 */
int nand_op_read_page(const unsigned int page_no, char *dest_addr, const unsigned int page_size)
{
	unsigned int unit_len;
	unsigned int dma_addr = (unsigned int)dest_addr;
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(page_no=");
	print_hex(page_no);
	prints(", dest_addr=");
	print_hex(dma_addr);
	prints(", page_size=");
	print_hex(page_size);
	prints(")\n");
#endif


#if 0 //removed by Andy Teng, MacArthur2 does not support 24bit ecc or 40bit ecc
	if (nand_op_is_24bit_ecc() || nand_op_is_40bit_ecc())
		unit_len = 1024;	// ECC type 24-bit or 40-bit (1KB unit)
	else
		unit_len = 512;
#else
	unit_len = 512;
#endif

	REG32(NF_DATA_TL0) = unit_len & 0xff;
	REG32(NF_DATA_TL1) = (unit_len >> 8) | 0x80;	// set length1, access_mode = 1

	// set page_len (in unit)
	REG32(NF_PAGE_LEN) = page_size / unit_len;

	// set PP
	REG32(NF_PP_RDY) = 0x80;	//NAND --> PP --> DRAM
	REG32(NF_PP_CTL0) = 0x1;
	REG32(NF_PP_CTL1) = 0;

	// enable blank check
	REG32(NF_BLANK_CHK) = 0x1;

	// set command
	REG32(NF_CMD1) = 0x00;
	REG32(NF_CMD2) = 0x30;
	REG32(NF_CMD3) = 0x70;

	// set address
	REG32(NF_PAGE_ADR0) =  (page_no & 0xff);
	REG32(NF_PAGE_ADR1) =  (page_no >> 8 ) & 0xff;
	REG32(NF_PAGE_ADR2) = ((page_no >> 16) & 0x1f) | (0x1 << 5);	// addr_mode = 001
	REG32(NF_PAGE_ADR3) = ((page_no >> 21) & 0x7) << 5;
	REG32(NF_COL_ADR0)  = 0;
	REG32(NF_COL_ADR1)  = 0;

	// set ECC
	REG32(NF_MULTI_CH_MODE) = 0x0;
	REG32(NF_ECC_STOP) = 0x80;	// set ecc_n_stop

	// set DMA
	if (IS_IN_CP_SRAM(dma_addr)) {
		REG32(NF_DBUS_MUX) |= 0x1;	// dbus path NF -> CP42k
		dma_addr = PHYS_CP_SRAM(dma_addr);
	}
	else {
		REG32(NF_DBUS_MUX) &= ~0x1;	// dbus path NF -> sb1
		dma_addr = PHYS(dma_addr);
	}
	REG32(NF_DMA_ADR) = dma_addr >> 3;	// 8 bytes unit
	
	REG32(NF_DMA_LEN) = page_size / 0x200;	// 512B unit
	REG32(NF_DMA_CONF) = 0x3;

	sync();

	// enable Auto mode
	REG32(NF_AUTO_TRIG) = 0x82;	// read in 2K page size
	while( REG32(NF_AUTO_TRIG) & 0x80 )
		;

	// wait DMA done
	while( REG32(NF_DMA_CONF) & 0x1 )
		;

	// return OK if all data bit is 1 (page is not written yet)
	if (REG32(NF_BLANK_CHK) & 0x2)
		return 0;
	else if (REG32(NF_ECC_STATE) & 0x8)
		return -1;	// ECC not correctable
	else
		return 0;
}


/*
 * NAND operation - read from NAND into internal Ping-Pong buffer (auto read mode)
 *
 * input:
 *  col_addr: column address
 *	page_addr: page no.
 *	length: read length
 * return:
 *	0 means read to PP ok, others mean ECC failed
 *
 */
int nand_op_read_to_PP_first(const unsigned int col_addr, const unsigned int page_addr, const unsigned int length)
{
	unsigned int unit_len, res;

#if 0 //removed by Andy Teng, MacArthur2 does not support 24bit ecc
	//To do: add ecc 24 & 40 bits support for magellan
	if (nand_op_is_24bit_ecc() || nand_op_is_40bit_ecc())
		unit_len = 1024;	// ECC type 24 bit or 40 bit (1KB unit)
	else
		unit_len = 512;
#else
	unit_len = 512;
#endif

	REG32(NF_DATA_TL0) = unit_len & 0xff;
	REG32(NF_DATA_TL1) = (unit_len >> 8) | 0x80;	// set length1, access_mode = 1

	// set page_len (in unit)
	REG32(NF_PAGE_LEN) = length / unit_len;

	// reset PP
	REG32(NF_PP_CTL0) = 0x2;
	REG32(NF_PP_CTL1) = 0;

	// NAND --> PP --> DRAM
	REG32(NF_PP_RDY) = 0x80;

	// enable blank check
	REG32(NF_BLANK_CHK) = 0x1;

	// set command
	REG32(NF_CMD1) = 0;
	REG32(NF_CMD2) = 0x30;
	REG32(NF_CMD3) = 0x70;

	// set address
	REG32(NF_PAGE_ADR0) =  (page_addr & 0xff);
	REG32(NF_PAGE_ADR1) =  (page_addr >> 8 ) & 0xff;
	REG32(NF_PAGE_ADR2) = ((page_addr >> 16) & 0x1f) | (0x1 << 5);	// addr_mode = 001
	REG32(NF_PAGE_ADR3) = ((page_addr >> 21) & 0x7) << 5;
	REG32(NF_COL_ADR0)  =  (col_addr & 0xff);
	REG32(NF_COL_ADR1)  =  (col_addr >> 8) & 0xff;

	// set ECC
	REG32(NF_MULTI_CH_MODE) = 0;
	REG32(NF_ECC_STOP) = 0x80;	// set ecc_n_stop

	// no DMA (data remains in PP)
	REG32(NF_DMA_CONF) = 0;

	sync();

	// enable Auto mode
	REG32(NF_AUTO_TRIG) = 0x80 | 0x2;	// read in 2K page size
	while( REG32(NF_AUTO_TRIG) & 0x80 )
		;

	// return OK if all data bit is 1 (page is not written yet)
	if (REG32(NF_BLANK_CHK) & 0x2)
		res = 0;
	else if (REG32(NF_ECC_STATE) & 0x8)
		res = -1;	// ECC not correctable
	else
		res = 0;

	// reset PP
	REG32(NF_PP_CTL0) = 0x2;

	return res;
}


#if defined(CONFIG_CHIP_MACARTHUR2)
/*
 * NAND operation - read 1KB from NAND into internal Ping-Pong buffer (using D read in sequential mode)
 *
 * input:
 *	none
 * return:
 *	v0: 0 means read ok, others mean ECC failed
 */ 
int nand_op_D_read_to_PP(void)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

	int res;

	// reset PP
	REG32(NF_PP_CTL0) = 0x2;

	// enable read_by_pp
	REG32(NF_PP_RDY) = 0x80;

	// enable blank check
	REG32(NF_BLANK_CHK) = 0x1;
	sync();

	// enable auto mode (auto_case = D read)
	REG32(NF_AUTO_TRIG) = 0x84;
	while( REG32(NF_AUTO_TRIG) & 0x80 )
		;

	// return OK if all data bit is 1 (page is not written yet)
	if (REG32(NF_BLANK_CHK) & 0x2)
		res = 0;
	else	// get ECC state
		res = REG32(NF_ECC_STATE) & 0x8;

	// reset PP
	REG32(NF_PP_CTL0) = 0x2;

	return res;
}
#endif /* end of #if defined(CONFIG_CHIP_MACARTHUR2) */

int nand_op_is_6bit_ecc(void)
{
    return (REG32(NF_ECC_SEL) & 0x1) ? 0:1;
}

int nand_op_is_12bit_ecc(void)
{
	return (REG32(NF_ECC_SEL) & 0x1);
}

int nand_op_spare_ddr_enabled(void)
{
	return ((REG32(NF_SPR_DDR_CTL) >> 29) & 0x1);
}

/*
 * NAND operation - get 4B from internal Ping-Pong buffer
 *
 * input:
 *	mapping: sram mapping in NF controller (0~4)
 *	offset: byte offset (must word alignment)
 * return:
 *	4B data
 */
unsigned int nand_op_get_sram(const int mapping, const unsigned int offset)
{
	unsigned int data;

	if (nand_op_spare_ddr_enabled()) {
		/* NF_SPR_DDR_CTL[27:0] Dram start address for DMA transfer. (8 Bytes Unit) */
		data = (REG32(NF_SPR_DDR_CTL) & 0x0fffffff) << 3;	// physical address
		data = REG32(KSEG0(data + offset));
	}
	else {
		// configure spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
		REG32(NF_PP_RDY) = 0; // disable read_by_pp
		REG32(NF_SRAM_CTL) = 0x30 | mapping; // enable direct access to PP

		data = REG32(NF_SRAM_BASE + offset);

		REG32(NF_SRAM_CTL) = 0x0; // disable direct access
	}

#if 0
	prints("{");
	print_hex(data);
	prints("}");
#endif
	return data;
}

#if 0	//FIXME: needs some cleanup (not use it in Sirius)
unsigned int nand_op_get_spare(void)
{
	/* swap endian */
	/* the data in spare is ex. 23 00 00 00, but the magic number 23 is in LSB */
	return swap_endian(nand_op_get_sram(0x2, 0));
}
#endif

int nand_op_is_random_mode(void)
{
	return REG32(NF_RND_RW_EN) & 0x1;
}

void nand_op_set_random_col_addr(unsigned int data_col, unsigned int spare_col)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("set random col(");
	print_hex(data_col);
	prints(", ");
	print_hex(spare_col);
	prints(")\n");
#endif

	REG32(NF_RND_DATASTR_COL_H) = data_col >> 8;
	REG32(NF_RND_SPR_STR_COL_H) = spare_col >> 8;
	REG32(NF_RND_SPR_STR_COL_L) = spare_col & 0xff;
}

/*
 * set timing parameter to NF controller
 */
void nand_op_set_timing(const int t1, const int t2, const int t3, const int delay_cnt)
{
	REG32(NF_T1) = t1;
	REG32(NF_T2) = t2;
	REG32(NF_T3) = t3;
	REG32(NF_DELAY_CNT) = delay_cnt;
}

/*
 * issue RESET command to nand flash
 */
int nand_op_reset(void)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

	REG32(NF_CHIP_EN) = NAND_CHIP_SELECT;
	
	// set 'reset' command
	REG32(NF_CMD1) = 0xff;
	
	// issue command
	REG32(NF_ND_CTL) = 0x80;
	
	// polling go bit to until go bit de-assert (command completed)
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#ifdef ROM_INFO
		prints("nand_op_reset timeout\n");
#endif

		return -1;	// time-out
	}

	// check ready/busy pin of NAND flash
	if (polling_timeout(NF_ND_CTL, 0x40, 0x40, 0x10000)) {

#ifdef ROM_INFO
		prints("nand_op_reset timeout\n");
#endif

		return -2;	// time-out
	}

	return 0;		
}

int nand_op_read_id(unsigned int addr, unsigned int *id)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
	prints("(addr=");
	print_hex(addr);
	prints(")\n");
#endif

#if 1
	if (nand_op_xfer_mode_read(0x90, addr, id, 4))
		return -1;
#else
	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode		
	REG32(NF_DATA_TL0) = 5;
	REG32(NF_DATA_TL1) = 0x80;	// transfer mode
	
	//Set PP
	REG32(NF_PP_RDY) = 0;		// NOt through PP
	REG32(NF_PP_CTL0) = 0x01;	
	REG32(NF_PP_CTL1) = 0;
	
	//Set command
	REG32(NF_CMD1) = 0x90;
	REG32(NF_ND_CTL) = 0x80;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -1;
	}
	
	//Set address	
	REG32(NF_PAGE_ADR0) = addr & 0xff;
	REG32(NF_PAGE_ADR2) = 0x7<<5;
	REG32(NF_ND_CTL) = 0x81;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -2;
	}
	
	//Enable MultiByteRead XFER mode
	REG32(NF_ND_CTL) = 0x84;
	if (polling_timeout(NF_ND_CTL, 0x80, 0, 0x10000)) {

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
		prints("nand_op_read_id timeout\n");
#endif

		return -3;
	}
	
	//Reset PP
	REG32(NF_PP_CTL0) = 0x2;
	
	//Move data to DRAM from SRAM
	REG32(NF_SRAM_CTL) = 0x30; //set 0x30 to enable bit[5] ()map_sel, due to out nand list table are implemented for little endian
	*id = REG32(NF_SRAM_BASE);
	REG32(NF_SRAM_CTL) = 0x00;	//# no omitted
#endif /* #if 1 */

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("id=0x");
	print_hex(*id);
	prints("\n");
#endif
	return 0;
}

#ifdef NF_WRITE_FUNCTION
int nand_op_write_page(const unsigned int page_no, const char *buf, const unsigned int page_size)
{	
	unsigned int data_unit;

#if 0
	printf("%s(page_no=0x%x, buf=0x%x)\n", __FUNCTION__, page_no, (unsigned int)buf);
#endif

	if (nand_op_is_random_mode()) {
		REG32(NF_RND_CMD1) = 0x85;
		nand_op_set_random_col_addr(0, page_size);
	}

#if 0 // MacArthur2 does not support 24bit ecc or 40bit ecc
	if (nand_op_is_24bit_ecc() || nand_op_is_40bit_ecc())
		data_unit = 1024;	// ECC type 24-bit or 40-bit (1KB unit)
	else
		data_unit = 512;
#else
	data_unit = 512;
#endif

#if 0
#define NF_CHIP_SEL(x)	( (~(1<<(x))) & 0x1f )
	// Set chip select
	REG32(NF_CHIP_EN) = NF_CHIP_SEL(chip_sel);
#endif

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode	
	REG32(NF_DATA_TL0) = data_unit & 0xff;
	REG32(NF_DATA_TL1) = (data_unit >> 8) & 0x3f;	// transfer mode
	
	//Set page length at auto mode
	REG32(NF_PAGE_LEN) = page_size / data_unit;	//Set page length (in unit)
	
	//Set PP
	REG32(NF_PP_RDY) = 0x0;	//NAND --> PP --> DRAM
	REG32(NF_PP_CTL0) = 0x0;
	REG32(NF_PP_CTL1) = 0;		
	
	//Set command
	REG32(NF_CMD1) = 0x80;	
	REG32(NF_CMD2) = 0x10;	
	REG32(NF_CMD3) = 0x70;	
	
	//Set address	
	REG32(NF_PAGE_ADR0) =  page_no & 0xff;
	REG32(NF_PAGE_ADR1) =  page_no >> 8 ;
	REG32(NF_PAGE_ADR2) = ((page_no >>16 ) & 0x1f) | (0x1 << 5);
	REG32(NF_PAGE_ADR3) = ((page_no >> 21) & 0x7) << 5;
	REG32(NF_COL_ADR0)  = 0;
	REG32(NF_COL_ADR1)  = 0;

	//Set ECC
	REG32(NF_MULTI_CH_MODE) = 0x0;
	REG32(NF_ECC_STOP) = 0x80;	
	
	//Set DMA
	REG32(NF_DMA_ADR) = PHYS((unsigned int)buf) >> 3;	// 8 bytes unit
	REG32(NF_DMA_LEN) = page_size / 0x200;	// DMA transfer unit is 512 bytes
	REG32(NF_DMA_CONF) = 0x01;
	sync();
	
	//Enable Auto mode
	REG32(NF_AUTO_TRIG) = 0x8 | 0x1;	//0x1: write in 2K page size
	while( REG32(NF_AUTO_TRIG) & 0x80 )
		;
	
	//Wait DMA done
	while( REG32(NF_DMA_CONF) & 0x1 );

	
	// execute command3 register and wait for executed completion
	REG32(NF_POLL_STATUS) = (0x6<<1) | 0x1; 
	while ( REG32(NF_POLL_STATUS) & 0x1)
		;

	if ((REG32(NF_DATA) & 0x1) == 0) {
#if 0
		/* show '.' in console */
		printf(".");
#endif

		return 0;
	}

#if 0
	/* show '!' in console */
	printf("!(%x) ", page_no);
#endif

	return -1;
}
#endif

#ifdef NF_ERASE_FUNCTION
int nand_op_erase_block(const unsigned int page_addr)
{
	//Set command
	REG32(NF_CMD1) = 0x60;		//Set CMD1
	REG32(NF_CMD2) = 0xd0;		//Set CMD2
	REG32(NF_CMD3) = 0x70;		//Set CMD3		

	//Set address
	//note. page_addr[5:0] is ignored to be truncated as block
	REG32(NF_PAGE_ADR0) =  page_addr & 0xff;
	REG32(NF_PAGE_ADR1) =  page_addr >> 8;
	REG32(NF_PAGE_ADR2) = ((page_addr >>16 ) & 0x1f) | (0x4 << 5);	// addr_mode: 100
	REG32(NF_PAGE_ADR3) = ((page_addr >> 21) & 0x7) << 5;
	REG32(NF_COL_ADR0)  = 0;
	REG32(NF_COL_ADR1)  = 0;


	//Set ECC: Set HW no check ECC, no_wait_busy
	REG32(NF_MULTI_CH_MODE) = 0x1 << 4;
		
	//Enable Auto mode: Set and enable auto mode
	// and wait until auto mode done
	REG32(NF_AUTO_TRIG) = 0x8a;
	while ( REG32(NF_AUTO_TRIG) & 0x80)
		;
	
	// execute command3 register and wait for executed completion
	REG32(NF_POLL_STATUS) = (0x6<<1) | 0x1; 
	while ( REG32(NF_POLL_STATUS) & 0x1)
		;

	if ((REG32(NF_DATA) & 0x1) == 0) {
#if 0
		/* show '/' in console */
		printf("/(%x)", page_addr/pages_per_block);
#endif
		return 0;
	}
#if 0
	/* show 'X' in console */
	printf("X(%x) ", page_addr);	
#endif
	return -1;
}
#endif

#ifdef NF_WRITE_FUNCTION
void nand_op_set_spare(const unsigned int spare, const unsigned int offset, const int page_size)
{
	unsigned int i, count, increment, mem_region;
	mem_region = 2;

	if (nand_op_spare_ddr_enabled()) {
		unsigned int spare_ddr_addr;

		spare_ddr_addr = REG32(NF_SPR_DDR_CTL) & 0x0fffffff;	// get phyiscal address
		spare_ddr_addr <<= 3;	// it's 8 bytes unit
		spare_ddr_addr = KSEG0(spare_ddr_addr);	// change to virtual address

		//if (nand_op_is_24bit_ecc())
		//	increment = 4;	// 4B for software
		//else
			increment = 8;	// 6B for software (8B spacing)

		// spare/data: 6B/512B based
		count = page_size / 512;
		for (i = 0; i < count; i++) {
			// (only 6 byte is for software)
#ifdef SPARE_SWAP_ENDIAN			
			REG32(spare_ddr_addr + i*increment) = swap_endian(spare);
#else
			REG32(spare_ddr_addr + i*increment) = spare;
#endif
			//REG8(spare_ddr_addr + i*increment + 4) = 0xff;
			//REG8(spare_ddr_addr + i*increment + 5) = 0xff;
		}
	}
	else {
		// size of spare area
		if (nand_op_is_6bit_ecc())
			increment = 0x10;		// 16B/512B (6B for software)
		else if (nand_op_is_12bit_ecc())
			increment = 0x20;		// 26B/512B (6B for software)
		else
			increment = 0x10;	

		// configure spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
		REG32(NF_PP_RDY) = 0; // disable read_by_pp
		REG32(NF_SRAM_CTL) = 0x10 | mem_region; // enable direct access to PP #5
		
		for (i = 0; i < 0x80; i += increment) {
#ifdef SPARE_SWAP_ENDIAN			
			REG32(NF_SRAM_BASE + offset + i) = swap_endian(spare); // set spare area of first PP
#else
			REG32(NF_SRAM_BASE + offset + i) = spare; // set spare area of first PP
#endif
			// (only first 6 byte is user-defined)
			//REG8(NF_SRAM_BASE + i + 0x4) = 0xff;
			//REG8(NF_SRAM_BASE + i + 0x5) = 0xff;
		}
		
		REG32(NF_SRAM_CTL) = 0x0; // disable direct access
	}
}
#endif

int nand_op_read_onfi_params(unsigned int *buffer, unsigned int len)
{
	return nand_op_xfer_mode_read(0xec, 0, buffer, len);
}

