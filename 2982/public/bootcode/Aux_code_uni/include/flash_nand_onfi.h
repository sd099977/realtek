/************************************************************************
 *
 *  flash_nand_onfi.h
 *
 *  NAND flash profile structure
 * 
 *
 ************************************************************************/

#ifndef _FLASH_NAND_ONFI_H_
#define _FLASH_NAND_ONFI_H_

/************************************************************************
 *  Include files
 ************************************************************************/

/************************************************************************
 *  Definitions
*************************************************************************/
typedef unsigned char ___u8;
typedef unsigned short int __le16;
typedef unsigned int __le32;

#define ONFI_CRC_BASE	0x4F4E

/************************************************************************
 *  Structures
*************************************************************************/
struct nand_onfi_params {
	/* rev info and features block */
	/* 'O' 'N' 'F' 'I'  */
	___u8 sig[4];
	__le16 revision;
	__le16 features;
	__le16 opt_cmd;
	___u8 reserved[22];

	/* manufacturer information block */
	char manufacturer[12];
	char model[20];
	___u8 jedec_id;
	__le16 date_code;
	___u8 reserved2[13];

	/* memory organization block */
	__le32 byte_per_page;
	__le16 spare_bytes_per_page;
	__le32 data_bytes_per_ppage;
	__le16 spare_bytes_per_ppage;
	__le32 pages_per_block;
	__le32 blocks_per_lun;
	___u8 lun_count;
	___u8 addr_cycles;
	___u8 bits_per_cell;
	__le16 bb_per_lun;
	__le16 block_endurance;
	__u8 guaranteed_good_blocks;
	__le16 guaranteed_block_endurance;
	___u8 programs_per_page;
	___u8 ppage_attr;
	___u8 ecc_bits;
	___u8 interleaved_bits;
	___u8 interleaved_ops;
	___u8 reserved3[13];

	/* electrical parameter block */
	___u8 io_pin_capacitance_max;
	__le16 async_timing_mode;
	__le16 program_cache_timing_mode;
	__le16 t_prog;
	__le16 t_bers;
	__le16 t_r;
	__le16 t_ccs;
	__le16 src_sync_timing_mode;
	__le16 src_ssync_features;
	__le16 clk_pin_capacitance_typ;
	__le16 io_pin_capacitance_typ;
	__le16 input_pin_capacitance_typ;
	___u8 input_pin_capacitance_max;
	___u8 driver_strenght_support;
	__le16 t_int_r;
	__le16 t_ald;
	___u8 reserved4[7];

	/* vendor */
	___u8 reserved5[90];

	__le16 crc;
} __attribute__((packed));


#endif /* #ifndef _FLASH_NAND_ONFI_H_ */
