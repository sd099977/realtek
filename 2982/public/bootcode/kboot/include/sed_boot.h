#ifndef __SED_BOOT_H__
#define __SED_BOOT_H__

#include "sysdefs.h"

/* Register definition */
#define KCPU_WAIT_HW_SEM_REG			(0xb801a630)
#define KCPU_WAIT_JUMP_DUMMY_REG		(0xb8060124)
#define MIPS_KSEG0BASE					(0x80000000)

/* Memory address related (MIPS need use KSEG0 address) */
#define KCPU_CMDLINE_ADDR				(0x000fff00)	// 000f_ff00~0010_0000 (need to sync with linux)
#define KCPU_CMDLINE_SIZE				(0x00000100)	// 256B
#define K_RESCUE_LINUX_ENTRY			(0x00108000)	// 0010_8000~
#define ENCRYPTED_FW_IMAGE_ADDR			(0x16000000)	// 1600_0000~1700_0000 (16M)
#define COMPRESSED_FW_IMAGE_ADDR		(0x17000000)	// 1700_0000~1800_0000 (16M)

#define KCPU_BOOT_TEXT_ADDR				(0x19f00000)	// 19f0_0000~
#define KCPU_BOOT_HEAP_START			(_app_heap_start)
#define KCPU_BOOT_HEAP_SIZE				(0x00040000)	// _app_heap_start~ (256K)
#define KCPU_FIRMWARE_TABLE_ADDR		(0x19ff0000)	// 19ff_0000~1a00_0000 (64K)
#define K_NORMAL_LINUX_ENTRY			(0x1a001000)	// 1a00_1000~

/* Nand related */
#define NAND_EXTERN_PARAM_BLOCK_NO		(0x10)
#define NAND_EXTERN_PARAM_BYTE_SIZE		(0x00000800)
#define NAND_RESCURE_LOGO_BLK_ADDR		(NAND_EXTERN_PARAM_BLOCK_NO+1)
#define RESCUE_LINUX_HEADER_SIZE		(0x10)
#define RESCUE_LINUX_HEADER_MAGICNO		(0x6330beef)

/*********************** Pre-defined magic number ***********************/
// for specific operation
#define MAGIC_KCPU_OP_MASK			(0xcafe1000)
#define MAGIC_KCPU_OP_SETUP_NORMAL	(0xcafe1001)	/* boot normal */
#define MAGIC_KCPU_OP_SETUP_RESCUE	(0xcafe1002)	/* boot rescue */
#define MAGIC_KCPU_OP_GO_NORMAL		(0xcafe1010)	/* go normal linux */
#define MAGIC_KCPU_OP_GO_RESCUE		(0xcafe1011)	/* go rescue linux */

// for status report
#define MAGIC_KCPU_ST_MASK			(0xcafe2000)
#define MAGIC_KCPU_ST_OK			(0xcafe2000)	/* status ok */
#define MAGIC_KCPU_ST_FAIL			(0xcafe2001)	/* status fail */

// for test only
#define MAGIC_KCPU_TEST_DECRYPT		(0x0001cafe)
#define MAGIC_KCPU_TEST_LZMA		(0x1001cafe)
/*********************** Pre-defined magic number end ***********************/

/* fw desc table */
#define FW_DESC_TABLE_V1_T_VERSION_1	(0x1)
#define FW_DESC_TABLE_V1_T_VERSION_11	(0x11)
#define FW_DESC_TABLE_V1_T_VERSION_21	(0x21)

#define FIRMWARE_DESCRIPTION_TABLE_SIGNATURE	"VERONA__" /* 8 bytes signature. */


/* move to mcp? */
#define DEFAULT_KEY_PTR					(NULL)

/* Move to common? */
#define CONFIG_SYS_RTK_NAND_FLASH

/* PIN info hardcode here (may changed by different pcb) */
#define PIN_FLASH_WP_STRING "0x0000000100015403"

#if defined(CONFIG_RTK_SECURE)
#define CONFIG_SYS_RTK_SECURE_BOOT
#endif

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)
	#define BOOT_FLASH_TYPE	BOOT_EMMC
#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
	#define BOOT_FLASH_TYPE	BOOT_NAND
#else
	#define BOOT_FLASH_TYPE BOOT_NOR_SERIAL
#endif

extern ulong _app_heap_start;

typedef enum {
	BOOT_NOR_SERIAL,
	BOOT_NAND,
	BOOT_EMMC
} BOOT_FLASH_T;

typedef enum {
	NONE_SECURE_BOOT = 0,
	NDS_SECURE_BOOT,
	RTK_SECURE_BOOT,
	DCAS_SECURE_BOOT
} SECUTE_BOOT_T;

typedef enum {
	FW_TYPE_RESERVED = 0,
	FW_TYPE_BOOTCODE,
	FW_TYPE_KERNEL,
	FW_TYPE_AUDIO,
	FW_TYPE_VIDEO,
	FW_TYPE_VIDEO_2,
	FW_TYPE_ECPU,
	FW_TYPE_JFFS2,
	FW_TYPE_SQUASH,
	FW_TYPE_EXT3,
	FW_TYPE_ODD,
	FW_TYPE_YAFFS2,
	FW_TYPE_AUDIO_FILE,
	FW_TYPE_VIDEO_FILE,
	FW_TYPE_IMAGE_FILE,
	FW_TYPE_ISO, //15
   FW_TYPE_SWAP,
   FW_TYPE_NTFS,
   FW_TYPE_RESCUE2,
   FW_TYPE_KCPU,
   FW_TYPE_UNKNOWN
} fw_type_code_t;

typedef struct{
	unchar bIsEncrypted;			/* must fill this value before we call get layout */
	unchar bIsCompressed;		/* must fill this value before we call get layout */

	uint flash_to_ram_addr;		/* will get this result at least */
	uint encrpyted_addr;		/* option result */
	uint decrypted_addr;		/* option result */
	uint compressed_addr;		/* option result */
	uint decompressed_addr;		/* option result */
	uint image_target_addr;		/* must fill this value before we call get layout */
} MEM_LAYOUT_WHEN_READ_IMAGE_T;

 /* Rescue linux information */
typedef struct {
	uint	dwMagicNumber;
	uint	dwImageSize;
	uint	dwReserved[2];
} rescue_linux_info_t;

typedef struct {
	unchar	signature[8];
	uint	checksum;
	unchar	version;
	unchar	reserved[7];
	uint	paddings;
	uint	part_list_len;
	uint	fw_list_len;
} __attribute__((packed)) fw_desc_table_v1_t;

typedef struct {
	unchar	type;
#ifdef LITTLE_ENDIAN
	unchar	reserved:7,
			ro:1;
#else
	unchar	ro:1,
			reserved:7;
#endif
	uint	length;
	unchar	fw_count;
	unchar	fw_type;
	unchar	reserved_1[8];
	unchar	mount_point[32];
} __attribute__((packed)) part_desc_entry_v1_t;

// for fw_desc_table_v1_t.version = FW_DESC_TABLE_V1_T_VERSION_1
typedef struct {
	unchar	type;
#ifdef LITTLE_ENDIAN
	unchar	reserved:6,
			lzma:1,
			ro:1;
#else
	unchar	ro:1,
			lzma:1,
			reserved:6;
#endif
	uint	version;
	uint	target_addr;
	uint	offset;
	uint	length;
	uint	paddings;
	uint	checksum;
	unchar	reserved_1[6];
} __attribute__((packed)) fw_desc_entry_v1_t;

// for fw_desc_table_v1_t.version = FW_DESC_TABLE_V1_T_VERSION_11
typedef struct {
	fw_desc_entry_v1_t v1;
	uint	act_size;
	unchar	hash[32];
	unchar	part_num;
	unchar	reserved[27];
} __attribute__((packed)) fw_desc_entry_v11_t;


// for fw_desc_table_v1_t.version = FW_DESC_TABLE_V1_T_VERSION_21
typedef struct {
	fw_desc_entry_v1_t v1;
	uint	act_size;
	unchar	part_num;
	unchar	RSA_sign[256];
	unchar	reserved[27];
} __attribute__((packed)) fw_desc_entry_v21_t;


int kboot_setup_rescue(void);
int kboot_setup_kernel(void);
int kboot_go_linux(void);

#endif	/* __SED_BOOT_H__ */

