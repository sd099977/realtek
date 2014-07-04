#ifndef __NAND_MGR_H__
#define __NAND_MGR_H__

/* bad block table structure */
typedef struct  __attribute__ ((__packed__)){
    unsigned short BB_die;		// chip number where bad block reside in
    unsigned short bad_block;		// block no. marked as bad
    unsigned short RB_die;		// chip number where remapping block reside in
    unsigned short remap_block;		// remapping block no.
} BB_t;

/* block state */
#define BLOCK_BAD               0x00
#define BLOCK_EMCU			0x51 // tag for emcu firmware
#define BLOCK_HWSETTING         0X23
#define BLOCK_KEY_SIG		0x24
#define BLOCK_KBOOT             0x78
#define BLOCK_BOOTCODE          0x79
#define BLOCK_DATA              0x80
#define BLOCK_ENVPARAM_MAGICNO  0X81
#define BLOCK_FACTORY_SETTING   0X82
#define BLOCK_OTHER_DATA	0xd0	// unknown data (user program into flash)
#define BLOCK_BBT		0xbb	// bad block table
#define BLOCK_CLEAN		0xff	// block is empty
#define BLOCK_UNDETERMINE	0x55	// block state is undetermined
#define BLOCK_IBT		0x11

// (NOTE: BLOCK_UNDETERMINE is a fake state, all blocks in the flash SHALL NOT have this state or it will cause some problem)

#define DATA_ALL_ONE		1		// read one page and all bit is '1'
#define NULL		          ((void *)0)

#define NAND_BOOTCODE_AREA_12MB			0xc00000	// bootcode blocks in NAND flash (first 16MB)
#define NAND_BOOTCODE_AREA_30MB			0x1e00000
#define NAND_BOOTCODE_AREA_50MB			0x3200000
#define DEFAULT_NAND_BOOTCODE_SIZE		NAND_BOOTCODE_AREA_12MB

#define NAND_ENV_SIZE		0x10000		// size of env param + magic no

/* bad block table related */
#define RBA_PERCENTAGE 		5		// percentage of blocks reserved for bad block remapping
#define BB_INIT 		0xFFFE		// initial bad_block value in bad block table
#define RB_INIT			0xFFFD		// initial remap_block value in bad block table
#define BB_DIE_INIT		0xEEEE		// initial bad_block chip value in bad block table
#define RB_DIE_INIT		BB_DIE_INIT	// initial remap_block chip value in bad block table
#endif
