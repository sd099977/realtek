/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>
#if defined(CONFIG_RTD299X)
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/panelConfigParameter.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/rbus/crt_sys_reg.h>
#include <asm/arch/panel_config_parameter.h>
#endif
#include <asm/arch/system.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/extern_param.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <watchdog.h>

#ifdef CONFIG_LZMA
#include <lzma/LzmaTypes.h>
#include <lzma/LzmaDec.h>
#include <lzma/LzmaTools.h>
#endif /* CONFIG_LZMA */
#include "linux/lzo.h"

#define SPI_BASE_ADDR					(0xB8100000UL)

extern int decrypt_image(char *src, char *dst, uint length, uint *key);

void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );

static void spi_switch_read_mode(void)
{
    rtd_outl(0xb801a800, 0x00000003); //switch flash to read mode
    rtd_outl(0xb801a804, 0x00000018); //command cycle
}

#if 0 // cklai@mark unused code
static void rtkspi_hexdump( const char * str, unsigned int start_address, unsigned int length )
{
	unsigned int i, j, rows, count;
	volatile unsigned char tmp;
	printf("======================================================\n");
	printf("%s(base=0x%08x)\n", str, start_address);
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		printf("%03x :", i<<4 );
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			tmp = rtd_inb(start_address);
			printf(" %02x",  tmp );
			count++;
			start_address++;
		}
		printf("\n");
	}
}
#endif

#if 0 // cklai@mark unused code
static void rtkspi_memcpy( unsigned int target_address, unsigned int source_address, unsigned int byte_length )
{
	volatile unsigned char * pcTarge = (volatile unsigned char *)target_address;
	while( byte_length-- ) {
		*pcTarge++ = rtd_inb(source_address++);
	}
}
#endif

static void rtkspi_memcpy32( unsigned int target_address, unsigned int source_address, unsigned int byte_length )
{
	volatile unsigned int * piTarge = (volatile unsigned int *)target_address;
	unsigned int word_length = (byte_length+3)>>2;
	while( word_length-- ) {
		*piTarge++ = rtd_inl(source_address);
		source_address += 4;
	}
}

int do_rtkspi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int cmd;
	unsigned int _iSPI_base_addr;
	unsigned int _iDDR_base_addr;
	unsigned int _iDataByteSize;

	cmd = -1;

	// parse command
	if( argc >= 2 ) {
		if( strncmp( argv[1], "dump", 4 ) ==0 ) {
			cmd = 1;
		}
	}

	if( cmd < 0 ) {
		printf("Error: command %s not support\n", argv[1]);
		return -1;
	}

	if( cmd == 1 ) { // dump
		if( argc != 5 ) {
			return -1;
		}
		_iSPI_base_addr = simple_strtoul(argv[2], NULL, 16);
		_iDDR_base_addr = simple_strtoul(argv[3], NULL, 16);
		_iDataByteSize = simple_strtoul(argv[4], NULL, 16);

		// sanity check
		if( _iDataByteSize == 0 ) {
			printf("Warning: no data will be dumped\n");
			return -1;
		}

		if( _iDataByteSize > 0x00800000 ) {
			printf("Error: no support SPI size larger than 8MB\n");
			return -1;
		}

		if( _iDataByteSize & 0x3 ) {
			printf("Error: data size is not 4-byte alignment\n");
			return -1;
		}

		if( _iDDR_base_addr < 0x01500000 ) {
			printf("Error: the target DDR address must be larger than 0x01500000\n");
			return -1;
		}

		printf("\n");
		printf("SPI start addr(phy)   = 0x%08x\n",_iSPI_base_addr);
		_iSPI_base_addr += SPI_BASE_ADDR;
		printf("SPI start addr(remap) = 0x%08x\n",_iSPI_base_addr);
		printf("DDR start addr        = 0x%08x\n",_iDDR_base_addr);
		printf("dumping byte size     = 0x%08x\n",_iDataByteSize);
	}

	do {
		// free spi nor
		printf("\nRelease HW semaphore....");
	    *((volatile unsigned int *)0x000000E0) = 0;
		rtd_outl(0xB801A000, 0x0);
		printf("Done\n");

		// set SPI as read mode
		spi_switch_read_mode();

		rtkspi_memcpy32( _iDDR_base_addr, _iSPI_base_addr, _iDataByteSize);

		// flush data
		flush_cache(_iDDR_base_addr, _iDataByteSize );
	}
	while(0);

	return 0;
}

U_BOOT_CMD(
	rtkspi, 5, 0,	do_rtkspi,
	"dump data from spi flash",
	"rtkspi dump spi_start_address ddr_start_address data_size\n"
	"rtkspi dump 0x00000000 0x01500000 0x00100000\n"
	"\t- SPI start address\n"
	"\t- DDR start address ( > 0x01500000 )\n"
	"\t- data bytes ( should be 4-byte alignment )\n"
);
