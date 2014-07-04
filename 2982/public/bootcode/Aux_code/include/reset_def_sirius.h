/************************************************************************
 *
 *  reset_def.h
 *
 *  Startup code define for Sirius internal ROM
 *
 *
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/


/************************************************************************
 *  Definitions
 ************************************************************************/

//modify by Andy Teng 20130218 20130329
#define DEFAULT_ENCRYPT_ADDR	0xa0200000	/* default encrypted bootcode address (32 bit) */

//modify by Andy Teng 20130218 20130329
#define DEFAULT_DECRYPT_ADDR	0xa0020000	/* default decrypted bootcode address (32 bit) */

/* format in little endian */
#define BOOTCODE_REE_HEADER_SCPU_LOAD_ADDR_OFFSET 0x20
#define BOOTCODE_REE_HEADER_SCPU_JUMP_ADDR_OFFSET 0x24
#define BOOTCODE_REE_HEADER_TEE_IN_REE_START_ADDR_OFFSET 0x28
#define BOOTCODE_REE_HEADER_TEE_LENGTH_OFFSET 0x2c

/* format in big endian */
#define BOOTCODE_TEE_HEADER_TEE_LENGTH_OFFSET 0x20
#define BOOTCODE_TEE_HEADER_AVCPU_LOAD_ADDR_OFFSET 0x24
#define BOOTCODE_TEE_HEADER_AVCPU_JUMP_ADDR_OFFSET 0x28
#define BOOTCODE_TEE_HEADER_VERSION 0x2c


#define HW_SETTING_MAGIC_NUM	0x23		/* identify SCS NOCS Certificate/Params/Aux_code in NAND flash spare area */
#define SEC_FW_MAGIC_NUM	0x24		/* identify SEC FW images in NAND flash spare area */
#define KBOOT_MAGIC_NUM	0x78		/* identify kboot in NAND flash spare area */
#define BOOTCODE_MAGIC_NUM	0x79		/* identify bootcode in NAND flash spare area */

//modify by Andy Teng 20130218 20130329
#define CP_DSCPT_POOL_BASE_ADDR	0xa0010000	/* CP descriptor pool base address */
#define CP_DSCPT_POOL_SIZE	0x800		/* CP descriptor pool size */
#define CP_DSCPT_POOL_MAX_ADDR	(CP_DSCPT_POOL_BASE_ADDR + CP_DSCPT_POOL_SIZE)

//modify by Andy Teng 20130305
#define DEFAULT_DECRYPT_HEADER_SIZE 256

//used for hwsetting verify
#define HWSETTING_MAX_SIZE	8192

//modify by Andy Teng 20130218 20130329
#define CHECKSUM_DEST		0xa000ff80	/* calculated checksum address */

#define SPI_BASE_ADDR		0xbdc00000	/* NOR flash start addess */

#define DEFAULT_KBOOT_ADDR	0x19f00000

#if defined(ENV_MACARTHUR)
#define SPI_HW_SETTING_DATA_ADDR	(SPI_BASE_ADDR + 0x3000)	/* HW setting start address in NOR flash for MacArthur 1*/
#else
//modify by Andy Teng 20130218 20130329
#define SPI_RESETROM_SIZE_ADDR (SPI_BASE_ADDR + 0x28)
#define SPI_HW_SETTING_HEADER_SIZE	0x4


#endif
#define SPI_KEY_SIG_MAX_SIZE	0x800		/* maximum size of DCAS key or hwsetting signature in NOR flash */

#define RECOVERY_MODE_KEY1	0x11		/* press the special key to enter recovery mode */
#define RECOVERY_MODE_KEY2	0x81		/* press the special key to enter recovery mode */
#define SPECIAL_KEY_THRESHOLD	0x3		/* threshold of consecutive special key to enter recovery mode */


#if defined(ENV_SIMULATION)
#define READ_UART_TIMEOUT	1		/* timoue value of read one byte from UART */
#else
#define READ_UART_TIMEOUT	150		/* timoue value of read one byte from UART */
#endif


#define DETECT_UART_INPUT_LOOP_CNT	0x5	/* loop count when detecting UART1 RX input */

#define RECOVERY_LOAD_ADDR	0x80100000	/* DDR start address for download binary in recovery mode */

#define NAND_START_BLOCK		0x6		/* start block */
#define NAND_HW_SETTING_RETRY	0x100		/* search HW setting in NAND flash retry count (blocks) */
#define NAND_BOOTCODE_RETRY	0X100		/* search bootcode in NAND flash retry count (blocks) */
#define NAND_PROFILE_LIMIT	0x100		/* limit of search profile in NAND flash (pages) */
#define NAND_PROFILE_INCREMENT	0x40		/* increment count when search profile in NAND flash retry count (pages) */

#define EMMC_BLOCK_SIZE		0x200
#define EMMC_KEY_SIG_SIZE	SPI_KEY_SIG_MAX_SIZE
#define EMMC_KSY_SIG_OFFSET	0x00020000	/* offset of HW setting signature or DCAS key1 in eMMC flash */
#define EMMC_HW_SETTING_OFFSET	0x00020800	/* offset of HW setting in eMMC flash */
#define EMMC_HW_SETTING_MAX_LEN	512		/* maximum number of HW setting block in eMMC flash */

#define BOOTCODE_OPTION_ADDR	0xb801a604	/* address of copy bootcode method (copy from NOR flash to DDR) */
#define BOOTCODE_OPTION_BIT_MD	1		/* bit position of use MD to copy bootcode from NOR flash to DDR */

#define KCPU_JUMP_ADDR		0xb801a608	/* register which represent KCPU jump address (specified in Aux code or DTE Bootcode) */
// Shadow register for 3 CPU hand shake used, see "Mac2_SB2_ARCH-page26"
#define SCPU_JUMP_ADDR		0xb801a610	/* register which represent SCPU jump address (specified in Aux code or DTE Bootcode) */
#define SCPU_LOAD_ADDR		0xb801a614	/* register which represent SCPU load address (specified in Aux code or DTE Bootcode) */
#define VCPU_JUMP_ADDR		0xb801a61c	/* register which represent VCPU jump address (specified in Aux code or DTE Bootcode) */
#define ACPU_LOAD_ADDR		0xb801a614	/* register which represent ACPU load address (specified in HW setting) */
#if defined(FPGA) || defined(CONFIG_ENV_FPGA)
#define ACPU_JUMP_ADDR		VCPU_JUMP_ADDR	/* register which represent ACPU jump address (FPGA does not include ISO registers) */
#else
#define ACPU_JUMP_ADDR		ST_WDOG_DATA12	/* register which represent ACPU jump address (specified in Aux code or DTE Bootcode) */
#endif

#define HW_SETTING_CUR_FLAG_MAGIC_HI	0x6319	/* magic number for NAND flash HW setting current page flag */
#define HW_SETTING_CUR_FLAG_ADDR	0xb8060104	/* address of NAND flash HW setting current page flag, original value is 0xb801a608 */
#if defined(FPGA)
#define HW_SETTING_VERSION_ADDR		0xa0000120	/* used for rtk secure boot only */
#else
#define HW_SETTING_VERSION_ADDR		0xb8060120	/* used for rtk secure boot only */
#endif

//#define HW_SEMAPHORE_ADDRESS		0xb801a000
//see "MacArthur2-DesignSpec-TOP_BIST.doc"
#define REG_CPU_BISR_RSTN			0xb8000f08
#define REG_CPU_BISR_REMAP			0xb8000f18
#define REG_CPU_BISR_DONE			0xb8000f28


#define FLAG_PRIMARY_HW_SETTING_FAIL	0x1	/* indicate primary HW setting read ECC failed (bit 0 = 1) */
#define FLAG_PRIMARY_BOOTCODE_FAIL	0x10	/* indicate primary bootcode read ECC failed (bit 1 = 1) */

#define DMEM_BASE_PHY 		0x10000000	/* Physical address (for setup DMEM) */
#define DMEM_SIZE 		0x00002000	/* to set size to 8KB (for setup DMEM) */

//#define STACK_POINTER_ADDR	0x8000eff0	/* address of sp register for C environment use (for RSA use) */
//#define STACK_POINTER_ADDR_un	0x80011000	/* address of sp register for C environment use (for ignore DMEM) */

#define RSA_SIGNATURE_LENGTH	256		/* RSA signature length (2048 bit) */
#define RSA_2048_KEY_LENGTH	256		/* RSA 2048 key length (2048 bit) */
#define RSA_2048_KEY_PADDING_LENGTH	64		/* RSA 2048 key padding length (64 byte) */


#define RSA_KEY_OEM 0
#define RSA_KEY_RTK 1


#define NONE_SECURE_BOOT	0
#define NAGRA_SECURE_BOOT	1
#define RTK_SECURE_BOOT		2
#define DCAS_SECURE_BOOT	3

#define NAND_FLASH_BOOT		0
#define SPI_FLASH_BOOT		1
#define EMMC_BOOT		2
#define SPI_NAND_FLASH_BOOT	3
#define UNKNOWN_BOOT		(-1)

/* for debug use */
#define SET_DEBUG_REG(r)	sw	r, 0xb801a600
#define SET_DEBUG_VAL(x)	li	k1, (x);	sw	k1, 0xb801a600
#define DEBUG_PRINT_VAL(x)	li	k1, (x);	sw	k1, U0RBR_THD_DLL; \
				li	k1, 0xd;	sw	k1, U0RBR_THD_DLL; \
				li	k1, 0xa;	sw	k1, U0RBR_THD_DLL

#define MAGIC_SYNC_ADDRESS 0x1801a020

#define CP42K_SRAM_ADDR		0xb8070000
#define CP42K_SRAM_SIZE		0xa800

//#define HAS_RECOVERY_FUNCTION		// recovery mode console function move to ACPU_recovery

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
