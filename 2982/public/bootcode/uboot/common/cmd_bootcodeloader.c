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
#define SPI_CODE_PART1					(SPI_BASE_ADDR)
#define SPI_CODE_PART2					(SPI_BASE_ADDR+(1UL<<20))

#define SPI_MAX_PARAM_SIZE				(0x800UL)
#define SPI_RESETROM_SIZE				(0x8000UL)

#define SPI_ENV_PARAM_ADDR              (0xB81F0000)
#define SPI_ENV_PARAM_SIZE              (0x00010000)		// 64KB

#define SPI_ERASE_SIZE_4KB				(0x00001000UL)
#define SPI_ERASE_SIZE_32KB				(0x00008000UL)
#define SPI_ERASE_SIZE_64KB				(0x00010000UL)
#define SPI_ERASE_SIZE_256KB			(0x00040000UL)

#define SPI_ERASE_SIZE_4KB_MINUS_1		(0x00001000UL-1UL)
#define SPI_ERASE_SIZE_32KB_MINUS_1		(0x00008000UL-1UL)
#define SPI_ERASE_SIZE_64KB_MINUS_1		(0x00010000UL-1UL)
#define SPI_ERASE_SIZE_256KB_MINUS_1	(0x00040000UL-1UL)

#define SPI_ERASE_SIZE_4KB_ALIGNMENT	(0xFFFFF000UL)
#define SPI_ERASE_SIZE_32KB_ALIGNMENT	(0xFFFF8000UL)
#define SPI_ERASE_SIZE_64KB_ALIGNMENT	(0xFFFF0000UL)
#define SPI_ERASE_SIZE_256KB_ALIGNMENT	(0xFFFC0000UL)

extern int decrypt_image(char *src, char *dst, uint length, uint *key);

void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );

DECLARE_GLOBAL_DATA_PTR;

t_spi_extern_param spi_ext_parameter;

void spi_switch_read_mode(void)
{
    rtd_outl(0xb801a800, 0x00000003); //switch flash to read mode
    rtd_outl(0xb801a804, 0x00000018); //command cycle
}

void spi_hexdump( const char * str, unsigned int start_address, unsigned int length )
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

void spi_memcpy( unsigned int target_address, unsigned int source_address, unsigned int byte_length )
{
	volatile unsigned char * pcTarge = (volatile unsigned char *)target_address;
	while( byte_length-- ) {
		*pcTarge++ = rtd_inb(source_address++);
	}
}

void spi_memcpy32( unsigned int target_address, unsigned int source_address, unsigned int byte_length )
{
	volatile unsigned int * piTarge = (volatile unsigned int *)target_address;
	unsigned int word_length = (byte_length+3)>>2;
	while( word_length-- ) {
		*piTarge++ = rtd_inl(source_address);
		source_address += 4;
	}
}

int spi_read_extra_parameter( void )
{
//	unsigned char * pspi_ext_parameter;

//	pspi_ext_parameter = (unsigned char *)&spi_ext_parameter;

#if 1
	do {
		spi_memcpy32( (unsigned int)&spi_ext_parameter, (SPI_ENV_PARAM_ADDR), sizeof(t_spi_extern_param) );
		//rtk_hexdump("ext form offset 0", pspi_ext_parameter, sizeof(t_spi_extern_param));
		if( spi_ext_parameter.magic_tag != 0x29932993 ) {
			printf("Check spi ext paraeter fail(tag=0x%08x)\n", spi_ext_parameter.magic_tag);
			break;
		}
		return 1;
	}
	while(0);
#else
	do {
		spi_memcpy32( (unsigned int)&spi_ext_parameter, (SPI_CODE_PART1), sizeof(t_extern_param) );
		//rtk_hexdump("ext form offset 0", pspi_ext_parameter, sizeof(t_extern_param));
		if( !( ( 0 <= spi_ext_parameter.secure_mode ) && ( spi_ext_parameter.secure_mode <= 3 ) ) ) {
			printf("SECURE MODE not valid, Search next ext parameter block\n");
			break;
		}
		if( !( ( spi_ext_parameter.flash_type == 0xDE ) || ( spi_ext_parameter.flash_type == 0xBE ) ) ) { // FLASH_MAGICNO_NOR_SERIAL(0xDE) FLASH_MAGICNO_NOR_PARALLEL(0xBE)
			printf("FLASH TYPE not valid, Search next ext parameter block\n");
			break;
		}
		return 1;
	}
	while(0);

	do {
		spi_memcpy32( (unsigned int)&spi_ext_parameter, (SPI_CODE_PART1 + SPI_RESETROM_SIZE), sizeof(t_extern_param) );
		//rtk_hexdump("ext form offset 32K", pspi_ext_parameter, sizeof(t_extern_param));
		if( !( ( 0 <= spi_ext_parameter.secure_mode ) && ( spi_ext_parameter.secure_mode <= 3 ) ) ) {
			printf("SECURE MODE not valid, Search next ext parameter block\n");
			break;
		}
		if( !( ( spi_ext_parameter.flash_type == 0xDE ) || ( spi_ext_parameter.flash_type == 0xBE ) ) ) { // FLASH_MAGICNO_NOR_SERIAL(0xDE) FLASH_MAGICNO_NOR_PARALLEL(0xBE)
			printf("FLASH TYPE not valid, Search next ext parameter block\n");
			break;
		}
		return 1;
	}
	while(0);
#endif
	return -1;
}

int rtk_bootcodeloader(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;
	unsigned int _iBootcodeIdx = 0;
	unsigned int _iBootcodeIdx_SourceAddr;
	unsigned int _iBootcodeIdx_TextAddr;
	unsigned int _iBootcodeIdx_Size;
	unsigned int _iInputBootcodeIdx_SourceAddr;
	unsigned int _iInputBootcodeIdx_TextAddr;
	unsigned int _iInputBootcodeIdx_Size;
	unsigned int _iExtPara_SecureMode = 0;
	unsigned int _iExtPara_BootcodeIdx_Addr_in_SPI;
	unsigned int _iExtPara_BootcodeIdx_Size_in_SPI;
	unsigned int _iTagAddr;
//	volatile unsigned int _iRegVal;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;

	_iBootcodeIdx_SourceAddr = 0;
	_iBootcodeIdx_TextAddr = 0;
	_iBootcodeIdx_Size = 0;

	_iInputBootcodeIdx_SourceAddr = 0;
	_iInputBootcodeIdx_TextAddr = 0;
	_iInputBootcodeIdx_Size = 0;

	_iExtPara_BootcodeIdx_Addr_in_SPI = 0;
	_iExtPara_BootcodeIdx_Size_in_SPI = 0;

	if( argc == 2 ) {
		_iBootcodeIdx = simple_strtoul(argv[1], NULL, 16);
		if( !( ( _iBootcodeIdx == 2 ) || ( _iBootcodeIdx == 3 ) ) ) {
			return -1;
		}
	}
	else if( argc == 4 ) {
		_iInputBootcodeIdx_SourceAddr = simple_strtoul(argv[1], NULL, 16);
		_iInputBootcodeIdx_SourceAddr |= 0xB8100000UL;

		_iInputBootcodeIdx_TextAddr = simple_strtoul(argv[2], NULL, 16);

		_iInputBootcodeIdx_Size = simple_strtoul(argv[3], NULL, 16);
	}
	else {
		return -1;
	}

	//printf("\n");
	//printf("Input : Bootcode source addr = 0x%08x\n", _iInputBootcodeIdx_SourceAddr);
	//printf("Input : Bootcode text base   = 0x%08x\n", _iInputBootcodeIdx_TextAddr);
	//printf("Input : Bootcode size        = 0x%08x\n", _iInputBootcodeIdx_Size);

	do {
#ifdef CONFIG_LOAD_AUDIO2_IMAGE
		*((volatile unsigned int *)0x000000E0) = 0x0;
		rtd_outl(ACPU_JUMP_ADDR_reg, MIPS_A_ENTRY2_CODE_ADDR | MIPS_KSEG0BASE);
		flush_dcache_all();
		printf("REG(0x000000E0)=0x%08x (BE)\n", *((volatile unsigned int *)0x000000E0));
		printf("REG(0xB801A618)=0x%08x\n", rtd_inl(0xB801A618));
		mdelay(10);
		rtd_outl(0xB801A000, 0x0); // release semaphore
		mdelay(10);
#else // old style
	  // ACPU will entery busy-loop, please see a_entry fw for detail
		*((volatile unsigned int *)0x000000E0) = 0x0;
		flush_dcache_all();
		printf("REG(0x000000E0)=0x%08x (BE)\n", *((volatile unsigned int *)0x000000E0));
		printf("REG(0xB801A618)=0x%08x\n", rtd_inl(0xB801A618));
		mdelay(10);
		rtd_outl(0xB801A000, 0x0); // release semaphore
		mdelay(10);
#endif
		// set SPI as read mode
		spi_switch_read_mode();

		// read external parameter from SPI
		if( spi_read_extra_parameter() < 0 ) {
			printf("Error : can not find ext parameter\n");
			return 0;
		}

		if( _iBootcodeIdx == 2 ) {
			_iExtPara_SecureMode              = spi_ext_parameter.bootcode2_secu_mode;
			_iExtPara_BootcodeIdx_Addr_in_SPI = spi_ext_parameter.bootcode2_addr;
			_iExtPara_BootcodeIdx_Size_in_SPI = spi_ext_parameter.bootcode2_size;
		}
		if( _iBootcodeIdx == 3 ) {
			_iExtPara_SecureMode              = spi_ext_parameter.bootcode3_secu_mode;
			_iExtPara_BootcodeIdx_Addr_in_SPI = spi_ext_parameter.bootcode3_addr;
			_iExtPara_BootcodeIdx_Size_in_SPI = spi_ext_parameter.bootcode3_size;
		}

		// sanity check
		if( _iInputBootcodeIdx_SourceAddr != 0 ) {
			_iBootcodeIdx_SourceAddr = _iInputBootcodeIdx_SourceAddr;
		}
		else {
			if( ( _iExtPara_BootcodeIdx_Addr_in_SPI & 0xFF000000 ) == 0xB8000000 ) {
				_iBootcodeIdx_SourceAddr = 	_iExtPara_BootcodeIdx_Addr_in_SPI + 8; // backward compatibility to bootcode1's layout
			}
			else {
				if( _iBootcodeIdx == 2 ) {
					_iBootcodeIdx_SourceAddr = 0xB8200000UL;
				}
				else {
					_iBootcodeIdx_SourceAddr = 0xB8280000UL;
				}
			}
		}

		if( _iInputBootcodeIdx_TextAddr != 0 ) {
			_iBootcodeIdx_TextAddr = _iInputBootcodeIdx_TextAddr;
		}
		else {
			if( _iBootcodeIdx == 2 ) {
				_iBootcodeIdx_TextAddr = CONFIG_JUMP_ADDRESS_FOR_BCLDR_2;
			}
			else {
				_iBootcodeIdx_TextAddr = CONFIG_JUMP_ADDRESS_FOR_BCLDR_3;
			}
		}

		if( _iInputBootcodeIdx_Size != 0 ) {
			_iBootcodeIdx_Size = _iInputBootcodeIdx_Size;
		}
		else {
			if( _iExtPara_BootcodeIdx_Size_in_SPI > 8 ) {
				_iBootcodeIdx_Size = _iExtPara_BootcodeIdx_Size_in_SPI - 8; // backward compatibility to bootcode1's layout
			}
		}

		printf("Secure Mode = %d\n", _iExtPara_SecureMode);
		printf("Bootcode addr in SPI = 0x%08x\n", _iBootcodeIdx_SourceAddr);
		printf("Bootcode Size in SPI = 0x%08x\n", _iBootcodeIdx_Size);
		printf("Bootcode Text Base   = 0x%08x\n", _iBootcodeIdx_TextAddr);

		if( _iBootcodeIdx_Size == 0 ) {
			return 0;
		}

		// dump spi flash to ddr
		//spi_memcpy( _iBootcodeIdx_TextAddr, _iBootcodeIdx_SourceAddr, _iBootcodeIdx_Size);

		// flush data
		//flush_cache( _iBootcodeIdx_TextAddr, _iBootcodeIdx_Size );

		// show data
		//rtk_hexdump("the first 64-byte", _iBootcodeIdx_TextAddr, 64 );
		//rtk_hexdump("the last 512-byte", _iBootcodeIdx_TextAddr+_iBootcodeIdx_Size-512, 512 );

		// verify image ( SHA256 or signature )
		if( _iExtPara_SecureMode == 2 ) { // RTK
			printf("to decrypt...\n");

			mem_layout.bIsEncrypted = 1;
			mem_layout.bIsCompressed = 0;
#if 1
			mem_layout.image_target_addr = _iBootcodeIdx_TextAddr;
			get_mem_layout_when_read_image( &mem_layout );
#else
			mem_layout.flash_to_ram_addr = mem_layout.encrpyted_addr = rtk_mem_info->encrypted_fw_image_addr;
			mem_layout.decrypted_addr = mem_layout.image_target_addr = _iBootcodeIdx_TextAddr;
#endif
			spi_hexdump("the first 16-byte encrypted data(SPI)", _iBootcodeIdx_SourceAddr, 16 );

			spi_memcpy32( mem_layout.flash_to_ram_addr, _iBootcodeIdx_SourceAddr, _iBootcodeIdx_Size);

			rtk_hexdump("the first 16-byte encrypted data(DAM)", (unsigned char *)mem_layout.flash_to_ram_addr, 16 );

			//rtk_hexdump("the last 512-byte encrypted data(DAM)", (unsigned char *)mem_layout.flash_to_ram_addr+_iBootcodeIdx_Size-512, 512 );

			// flush data
			flush_cache( mem_layout.flash_to_ram_addr, _iBootcodeIdx_Size );

			if (decrypt_image((char *)mem_layout.encrpyted_addr,
						(char *)mem_layout.decrypted_addr,
						_iBootcodeIdx_Size,
						Kh_key_ptr))
			{
				printf("decrypt image error!\n");
				return 0;
			}

			// flush data
			flush_cache( mem_layout.decrypted_addr, _iBootcodeIdx_Size );

			rtk_hexdump("the first 16-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 16 );
			//rtk_hexdump("the last 512-byte decrypted data", (unsigned char *)(mem_layout.decrypted_addr+_iBootcodeIdx_Size-512), 512 );

			printf("decrypt bootcode successful\n");

			reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + _iBootcodeIdx_Size - RSA_SIGNATURE_LENGTH) );

			ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
									  _iBootcodeIdx_Size - RSA_SIGNATURE_LENGTH - SHA256_SIZE,
									  (unsigned char *)(mem_layout.decrypted_addr + _iBootcodeIdx_Size - RSA_SIGNATURE_LENGTH), 1 );
		}
		else
		{
			// dump spi flash to ddr
			spi_memcpy32( _iBootcodeIdx_TextAddr, _iBootcodeIdx_SourceAddr, _iBootcodeIdx_Size);

			// flush data
			flush_cache( _iBootcodeIdx_TextAddr, _iBootcodeIdx_Size );

			ret = Verify_SHA256_hash( (unsigned char *)_iBootcodeIdx_TextAddr,
			                          _iBootcodeIdx_Size - 32,
			                          (unsigned char *)(_iBootcodeIdx_TextAddr + _iBootcodeIdx_Size - 32), 0 );
		}

		if( ret < 0 ) {
			printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
			return 0;
		}

		// restore boot media info ( UATAG_ADDRESS9, UATAG_ADDRESS10 )
		extern unsigned int UATAG_ADDRESS9;
		extern unsigned int UATAG_ADDRESS10;

		_iTagAddr = ( (unsigned int)(&UATAG_ADDRESS9) ) & 0x000000FFUL;
		_iTagAddr |= _iBootcodeIdx_TextAddr;
		*((volatile unsigned int *)_iTagAddr) = UATAG_ADDRESS9;

		_iTagAddr = ( (unsigned int)(&UATAG_ADDRESS10) ) & 0x000000FFUL;
		_iTagAddr |= _iBootcodeIdx_TextAddr;
		*((volatile unsigned int *)_iTagAddr) = UATAG_ADDRESS10;

		// jump to selected bootcode address
#if 0
		bootm_headers_t	images;

		memset(&images, 0, sizeof(bootm_headers_t));

		images.ep = (unsigned long)_iBootcodeIdx_TextAddr;

		printf("Start bootcode at 0x%lx ...\n", images.ep);

		rtk_plat_boot_go(&images);
#else
		void (*uboot_entry)(void);
		uboot_entry = (void (*)(void))(_iBootcodeIdx_TextAddr);
		printf("Start bootcode at 0x%x ...\n", _iBootcodeIdx_TextAddr);
		cleanup_before_bootcode();
		uboot_entry();
#endif
	}
	while(0);

	return 0;
}

U_BOOT_CMD(
	bcldr, 4, 0,	rtk_bootcodeloader,
	"load u-boot from spi flash",
	"bcldr [2|3]\n"
	"bcldr SPI_OFFSET UBOOT_TEXT_BASE UBOOT_BYTE_SIZE\n"
	"bcldr 0x00280000 0x00020000 byte_length\n"
	"\t- SPI flash offset : default 0x00200000 or 0x00280000\n"
	"\t- uboot text base  : default 0x01020000 or 0x00020000\n"
	"\t- uboot byte size  : default N/A\n"
);
