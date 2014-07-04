/************************************************************************
 *  Include files
 ************************************************************************/
#include <project_config.h>
#include <extern_param.h>
#include <shell_golinux.h>
#include <stdio.h>
//#include <string.h>
#include <platform_iso.h>
#include "flashdev_n.h"
#include "flashdev_e.h"
#include "flashdev_s.h"
#include "flashdev_sn.h"

#include "nand_mgr.h"
#include "NOCS.h"
#include "util.h"
#include "mcp.h"
#include "kimg_seed.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
//#define SPI_HWSETTING_FROM_32K


#define RBUS_SC_VERID			0x18060000

#define PARAMETER_TMP_ADDR		(0xa2400000 - UBOOT_DDR_OFFSET)
#define ARRAY_TMP_ADDR			(0xa2500000 - UBOOT_DDR_OFFSET)	// temporary space for storing final bootcode image
#define DATA_TMP_ADDR			(0xa2600000 - UBOOT_DDR_OFFSET)

#define DATA_TMP_SIZE			0x10000

//#define IS_SECURE_BOOT			0x0


//#define BOOTCODE_DDR_BASE		0xa00d0004	// bootcode address on DDR
#define EXT_PARA_DDR_BASE		(0xa0a00000 - UBOOT_DDR_OFFSET)	// t_extern_param + logo + rescue base address on DDR
#define NAND_ENV_DDR_BASE		(0xa0040000 - UBOOT_DDR_OFFSET)	//modify by angus, original value is0xa0010000

#define BOOTCODE_SIZE_ADDR		0xb801a60c
#define SIMULATION_DUMP_ADDR		(0xa2800000	- UBOOT_DDR_OFFSET) /* dump hwsetting/bootcode related to DDR */
#define NAND_BOOT_BACKUP_COUNT		3		// number of backup bootcode in NAND flash

#define HWSETTING_FIX_SIZE	4096

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned char resetrom[];		//rom data : 0xbfc00000 ~ 0xbfc01fff
extern unsigned char resetrom_end;
extern unsigned char hwsetting[];
extern unsigned char hwsetting_end;
extern unsigned char hasharray[];
extern unsigned char hasharray_end;
extern unsigned char signature[];
extern unsigned char signature_end;
extern unsigned char ecbarray[];
extern unsigned char ecbarray_end;
extern unsigned char rescuelinux[];
extern unsigned char rescuelinux_end;
extern unsigned char cbc_linux[];
extern unsigned char cbc_linux_end;
extern unsigned char hwsetting_sig_image[];
extern unsigned char hwsetting_sig_image_end;
extern unsigned char dcas_key_sig_image[];
extern unsigned char dcas_key_sig_image_end;
extern unsigned char logo[];
extern unsigned char logo_end;
extern unsigned char logo2[];
extern unsigned char logo2_end;
extern unsigned char logo3[];
extern unsigned char logo3_end;
extern unsigned char logo4[];
extern unsigned char logo4_end;
extern unsigned char logo5[];
extern unsigned char logo5_end;
extern unsigned char logo6[];
extern unsigned char logo6_end;
extern unsigned char logo7[];
extern unsigned char logo7_end;
extern unsigned char logo8[];
extern unsigned char logo8_end;

//extern UINT32 pages_per_block;
//extern UINT32 blocks_per_flash;

// extern symbol from linker script
extern unsigned int _f_scs_nocs_cert_tdb, _e_scs_nocs_cert_tdb;
extern unsigned int _f_scs_nocs_cert_em,  _e_scs_nocs_cert_em;
extern unsigned int _f_scs_nocs_cert_sig, _e_scs_nocs_cert_sig;
extern unsigned int _f_scs_params_area_tdb, _e_scs_params_area_tdb;
extern unsigned int _f_scs_params_area_em,  _e_scs_params_area_em;
extern unsigned int _f_scs_params_area_sig, _e_scs_params_area_sig;
extern unsigned int _f_scs_aux_code_tdb, _e_scs_aux_code_tdb;
extern unsigned int _f_scs_aux_code_em,  _e_scs_aux_code_em;
extern unsigned int _f_scs_aux_code_sig, _e_scs_aux_code_sig;
extern unsigned int _f_scs_dte_bootcode_tdb, _e_scs_dte_bootcode_tdb;
extern unsigned int _f_scs_dte_bootcode_em,  _e_scs_dte_bootcode_em;
extern unsigned int _f_scs_dte_bootcode_sig, _e_scs_dte_bootcode_sig;



/************************************************************************
 *  Public variables
 ************************************************************************/
UINT8  verify_after_write;
UINT8  force_secure;
UINT8  test_secure;
UINT8  preserve_original_param;
UINT8  input_kh_key;
UINT32  Kh_key[4];
UINT8  noreset;

#if defined(DUMP_NAND_FLASH) || defined(DUMP_SPI_NAND_FLASH) || defined(DUMP_EMMC_FLASH)
UINT32 gdst_data_addr = SIMULATION_DUMP_ADDR;
#endif

/************************************************************************
 *  Static variables
 ************************************************************************/
static UINT8 *cert_buf;
static UINT8 *params_buf;
static UINT8 *aux_buf;
static UINT8 *bootcode_buf;
static UINT32 cert_buf_size;
static UINT32 params_buf_size;
static UINT32 aux_buf_size;
static UINT32 bootcode_buf_size;

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int get_boot_flash_type(void);
extern unsigned char get_secure_boot_type(void);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
#ifdef FPGA
static int get_Efuse_secure_state(void);
#endif
static int check_secure_boot(void);
static int check_bonding(void);
static int get_options(UINT32 argc, char **argv, UINT8 *force_flash_type, UINT8 *flash_type, UINT8 *verify_after_write,
	UINT8 *force_secure, UINT8 *test_secure, UINT8 *preserve_original_param,
	UINT8 *input_kh_key, UINT32 *efuse_key, UINT8 *noreset);
static int bootcode_encrypted(void);
static const char * get_secure_type(void);
static unsigned int align_to_boundary(unsigned int size, unsigned int block_size);
#ifdef DUMP_EMMC_FLASH
static void dump_data(const char *str, unsigned int dst, unsigned int src, unsigned int len);
#endif

/************************************************************************
 *  Function body
 ************************************************************************/

void dump_memroy(void *dst, UINT32 size) {

	UINT32 i;
	UINT8 value;
	for (i=0; i<size; i++) {
		value = REG8(((UINT32)dst) + i);
		print_val(value, 2);
		print_uart(" ");
		if (i%8 == 7) print_uart("\n");
	}

}
/************************************************************************
 *
 *                          dvrmain
 *  Description :
 *  -------------
 *  main function of flash writer
 *  attention: 1. since 0xbfc0_0000 ~ 0xbfc0_1fff occupied by ROM code,
 *  space from 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash can not be utilized.
 *  In order to write data to the space, we shift writing address space from
 *  0xbed0_0000 ~ 0xbfcf_ffff to 0xbdd0_0000 ~ 0xbecf_ffff. So that we can
 *  access to space 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash.
 *  2. we left 0xbecf_f000 ~ 0xbecf_ffff for ext_param.
 *  3. ext_param is located from 0xbecf_f800.
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
int dvrmain(UINT32 argc, char **argv)
{
    UINT8 *key_sig_addr/*   = (UINT8 *)0xb8107800*/;		//assign bootcode start address
#if 0 // mod for adding resetrom by andyteng
#ifdef SPI_HWSETTING_FROM_32K
    UINT8 *resetrom_addr  = (UINT8 *)0xb8100000;		//assign bootcode start address
    UINT8 *hwsetting_addr = (UINT8 *)0xb8108000;		//assign hw setting start address, moidfy by angus, original value is 0xb8108000
#else
    UINT8 *hwsetting_addr = (UINT8 *)0xb8100000;		//assign hw setting start address, moidfy by angus, original value is 0xb8108000
#endif
#else
    UINT8 *resetrom_addr  = (UINT8 *)0xbfc00000; 	  //assign bootcode start address
    UINT8 *hwsetting_addr;
#endif
    UINT8 *array_addr;
    UINT8 *logo_addr;
    UINT8 *logo2_addr;
    UINT8 *logo3_addr;
    UINT8 *logo4_addr;
    UINT8 *logo5_addr;
    UINT8 *logo6_addr;
    UINT8 *logo7_addr;
    UINT8 *logo8_addr;
    UINT8 *linux_sec1_addr;
    UINT8 *linux_sec2_addr;
    UINT8 *env_param_addr = (UINT8 *)0xb8200000;
    UINT8 *array;					// pointer to bootcode binary
    UINT8 *linux_ptr;				// pointer to rescue binary
    UINT32  boot_size;

#if 0 // mod for adding resetrom by andyteng
#ifdef SPI_HWSETTING_FROM_32K
    UINT32  resetrom_size  = (unsigned int )(&resetrom_end  - resetrom);
#endif
#else
    UINT32  resetrom_size  = (unsigned int )(&resetrom_end  - resetrom);
#endif
    UINT32  hwsetting_size = (unsigned int )(&hwsetting_end - hwsetting);
    UINT32  array_size     = (unsigned int )(&hasharray_end - hasharray);
    UINT32  logo_size      = (unsigned int )(&logo_end      - logo);
    UINT32  logo2_size     = (unsigned int )(&logo2_end     - logo2);
    UINT32  logo3_size     = (unsigned int )(&logo3_end     - logo3);
    UINT32  logo4_size     = (unsigned int )(&logo4_end     - logo4);
    UINT32  logo5_size     = (unsigned int )(&logo5_end     - logo5);
    UINT32  logo6_size     = (unsigned int )(&logo6_end     - logo6);
    UINT32  logo7_size     = (unsigned int )(&logo7_end     - logo7);
    UINT32  logo8_size     = (unsigned int )(&logo8_end     - logo8);
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) || defined(Rescue_Source_NULL)
    UINT32  linux_size     = (unsigned int ) 0;
#else /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
    UINT32  linux_size     = (unsigned int )(&rescuelinux_end     - rescuelinux);
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */


    UINT32  hwsetting_sig_size = (unsigned int )(&hwsetting_sig_image_end - hwsetting_sig_image);
    UINT32  dcas_key_sig_size = (unsigned int )(&dcas_key_sig_image_end - dcas_key_sig_image);


	UINT32 scs_nocs_cert_tdb_size = (UINT32)((char *)&_e_scs_nocs_cert_tdb - (char *)&_f_scs_nocs_cert_tdb);
	UINT32 scs_nocs_cert_em_size = (UINT32)((char *)&_e_scs_nocs_cert_em - (char *)&_f_scs_nocs_cert_em);
	UINT32 scs_nocs_cert_sig_size = (UINT32)((char *)&_e_scs_nocs_cert_sig - (char *)&_f_scs_nocs_cert_sig);
	UINT32 scs_params_area_tdb_size = (UINT32)((char *)&_e_scs_params_area_tdb - (char *)&_f_scs_params_area_tdb);
	UINT32 scs_params_area_em_size = (UINT32)((char *)&_e_scs_params_area_em - (char *)&_f_scs_params_area_em);
	UINT32 scs_params_area_sig_size = (UINT32)((char *)&_e_scs_params_area_sig - (char *)&_f_scs_params_area_sig);
	UINT32 scs_aux_code_tdb_size = (UINT32)((char *)&_e_scs_aux_code_tdb - (char *)&_f_scs_aux_code_tdb);
	UINT32 scs_aux_code_em_size = (UINT32)((char *)&_e_scs_aux_code_em - (char *)&_f_scs_aux_code_em);
	UINT32 scs_aux_code_sig_size = (UINT32)((char *)&_e_scs_aux_code_sig - (char *)&_f_scs_aux_code_sig);
	UINT32 scs_dte_bootcode_tdb_size = (UINT32)((char *)&_e_scs_dte_bootcode_tdb - (char *)&_f_scs_dte_bootcode_tdb);
	UINT32 scs_dte_bootcode_em_size = (UINT32)((char *)&_e_scs_dte_bootcode_em - (char *)&_f_scs_dte_bootcode_em);
	UINT32 scs_dte_bootcode_sig_size = (UINT32)((char *)&_e_scs_dte_bootcode_sig - (char *)&_f_scs_dte_bootcode_sig);


    UINT32  linux_sec1_size;
    UINT32  linux_sec2_size;

    int (*do_erase)(void  *, UINT32 * , UINT32);
    int (*do_write)(void *, UINT8 *, UINT32 *, UINT32, UINT32, const UINT32);
    int (*do_identify)(void **);
    int (*do_init)(void *);
    int (*do_read)(void *, UINT32 *, UINT8 *, UINT32, INT32);
    void (*do_exit)(void *dev);


    UINT8 flash_type;
    UINT32 idx, i;
    UINT32 temp, reg_addr;
    t_extern_param param;
    t_extern_param *orignal_param;
    UINT8 *temp_ptr;
	void *device;
    int res, save_nand_env;
    UINT32 *ptr;
    UINT8 force_flash_type;
    //UINT32 kimg_key[4];
    UINT32 aux_protection_key[4];


    //define minimal erase block size and total block from 0xbec0_0000~0xbecf_ffff
    int  block_size = 0x1000;
    int  total_block_cnt = 0x100000 / block_size;

	init_uart();
	printf("%s %s %s\n", __FUNCTION__, __DATE__, __TIME__);
#ifndef FPGA
    // check chip is Sirius
    if ((REG32(RBUS_SC_VERID) >> 16) != 0x6330)
    {
    	print_uart("wrong chip!\n");
    	return -998;
    }
#endif
#if 0
    // check chip bonding is correct before writing bootcode
    if (check_bonding())
    {
    	print_uart("board & bootcode not match!\n");
    	return -999;
    }

#endif /* #ifndef FPGA */


    //modify by angus, magellan didn't have reset rom
    /* reserve 32K (0xbfc0_0000 ~ 0xbfc0_7fff) for reset_rom code section */
    //total_block_cnt = total_block_cnt - (32 * 1024) / block_size;

    /* reserve one block in 0xbecf_f000 ~ 0xbecf_ffff for ext_param */
    total_block_cnt = total_block_cnt - 1;


    force_flash_type = verify_after_write = force_secure = test_secure = preserve_original_param = input_kh_key = noreset = 0;
    flash_type = FLASH_TYPE_NAND;

#ifdef FPGA
    force_flash_type = 1;
    verify_after_write = 1;

#ifdef FGPA_SECURE_BOOT_AES_KEY0
	Kh_key[0] = hexstr2int(FGPA_SECURE_BOOT_AES_KEY0);
	Kh_key[1] = hexstr2int(FGPA_SECURE_BOOT_AES_KEY1);
	Kh_key[2] = hexstr2int(FGPA_SECURE_BOOT_AES_KEY2);
	Kh_key[3] = hexstr2int(FGPA_SECURE_BOOT_AES_KEY3);

	for (i = 0; i < 4; i++)
		printf("Kh_key[%d]: 0x%x\n", i, Kh_key[i]);
#endif

#ifdef FGPA_SECURE_BOOT_AUX_PROTECTION_KEY0
	aux_protection_key[0] = hexstr2int(FGPA_SECURE_BOOT_AUX_PROTECTION_KEY0);
	aux_protection_key[1] = hexstr2int(FGPA_SECURE_BOOT_AUX_PROTECTION_KEY1);
	aux_protection_key[2] = hexstr2int(FGPA_SECURE_BOOT_AUX_PROTECTION_KEY2);
	aux_protection_key[3] = hexstr2int(FGPA_SECURE_BOOT_AUX_PROTECTION_KEY3);

	for (i = 0; i < 4; i++)
		printf("aux_protection_key[%d]: 0x%x\n", i, aux_protection_key[i]);
#endif

#ifdef FPGA_BOOT_NAND
    temp = flash_type = FLASH_TYPE_NAND;

#elif defined(FPGA_BOOT_SPI_NAND)
    temp = flash_type = FLASH_TYPE_SPI_NAND;

#elif defined(FPGA_BOOT_EMMC)
    temp = flash_type = FLASH_TYPE_EMMC;
#else
    temp = FLASH_TYPE_SPI;
#endif

#else

	// force boot from emmc
    force_flash_type = 1;
    verify_after_write = 1;
    temp = flash_type = FLASH_TYPE_EMMC;

	//clear extern param
	memset(&param, 0, sizeof(param));


    /* get argument options */
    //Kh_key[0] = Kh_key[1] = Kh_key[2] = Kh_key[3] = 0;
    res = get_options(argc, argv, &force_flash_type, &flash_type, &verify_after_write, &force_secure, &test_secure,
    	&preserve_original_param, &input_kh_key, Kh_key, &noreset);
    if (res)
    {
    	print_uart("wrong parameters\n");
    	return -55;
    }

    /***************************************************
     * determine flash type on DUT and correspond tools
     ***************************************************/
    /* if 2: eMMC. 1: serial flash. 0: NAND flash*/


    temp = force_flash_type ? flash_type : get_boot_flash_type();

#endif /* #ifdef FPGA */

    if (force_flash_type)
    	print_uart("\n\nforce ");

    print_uart("flash type: ");
    switch( temp )
    {

    	case FLASH_TYPE_SPI:
	    	print_uart("SPI\n");
	    	flash_type = FLASH_TYPE_SPI;
	    	do_erase = do_erase_s;
	    	do_write = do_write_s;
	    	do_identify = do_identify_s;
	    	do_init = do_init_s;
	    	do_exit = do_exit_s;
	    	env_param_addr = (UINT8 *)0xb8200000;
    		break;

    	case FLASH_TYPE_EMMC:
	    	print_uart("eMMC\n");
	    	flash_type = FLASH_TYPE_EMMC;
	    	do_erase = do_erase_e;
	    	do_write = do_write_e;
	    	do_identify = do_identify_e;
	    	do_init = do_init_e;
	    	do_read = do_read_e;
	    	do_exit = do_exit_e;
	    	env_param_addr = (UINT8 *)NAND_ENV_DDR_BASE;
    		break;

    	case FLASH_TYPE_NAND:
#if defined(Config_NOR_BOOT_NAND_TRUE)
		if (force_flash_type)
			printf("\nwrong parameters\n");
		printf("this bootcode is for NOR flash!\n");
		return -1;
#endif
	    	print_uart("NAND\n");
	    	flash_type = FLASH_TYPE_NAND;
	    	do_erase = do_erase_n;
	    	do_write = do_write_n;
	    	do_identify = do_identify_n;
	    	do_init = do_init_n;
	    	do_exit = do_exit_n;
	    	env_param_addr = (UINT8 *)NAND_ENV_DDR_BASE;
    		break;

	case FLASH_TYPE_SPI_NAND:
	    	print_uart("SPI-NAND\n");
	    	flash_type = FLASH_TYPE_SPI_NAND;
	    	do_erase = do_erase_sn;
	    	do_write = do_write_sn;
	    	do_identify = do_identify_sn;
	    	do_init = do_init_sn;
	    	do_exit = do_exit_sn;
	    	env_param_addr = (UINT8 *)0xb8200000;
    		break;

    	default:
    		print_uart("unknown!\n");
    		return -1;

    		break;
    }


	/****************************************************
	 * allocate buffer for images to write into flash
	 ****************************************************/
	cert_buf_size = scs_nocs_cert_tdb_size + scs_nocs_cert_sig_size;
	params_buf_size = scs_params_area_tdb_size + scs_params_area_sig_size;
	aux_buf_size = scs_aux_code_tdb_size + scs_aux_code_sig_size;
	bootcode_buf_size = scs_dte_bootcode_tdb_size + scs_dte_bootcode_sig_size;

	cert_buf = (UINT8 *) simple_malloc(cert_buf_size);
	params_buf = (UINT8 *) simple_malloc(params_buf_size);
	aux_buf = (UINT8 *) simple_malloc(aux_buf_size);
	temp = align_to_boundary(bootcode_buf_size, 4096) * 4096;	// estimated largest page size of 12-bit ECC NAND flash is 4KB
	bootcode_buf = (UINT8 *) simple_malloc(temp);

	if ((cert_buf == NULL) || (params_buf == NULL) || (aux_buf == NULL)|| (bootcode_buf == NULL))
		return -2;
	else {
		// reset bootcode buffer to un-programmed value for later use
		// NAND/SPI-NAND: page-based R/W
		// eMMC: sector-based R/W
		memset(bootcode_buf, 0xff, temp);
	}

	printf("NOCS Certificate Area buffer: 0x%x, size 0x%x\n", (UINT32)cert_buf, cert_buf_size);
	printf("Params Area buffer: 0x%x, size 0x%x\n", (UINT32)params_buf, params_buf_size);
	printf("Aux Code Area buffer: 0x%x, size 0x%x\n", (UINT32)aux_buf, aux_buf_size);
	printf("DTE Bootcode Area buffer: 0x%x, size 0x%x\n", (UINT32)bootcode_buf, bootcode_buf_size);

    /****************************************************
     * determine encrypt bootcode or executable bootcode
     ****************************************************/
	printf("image for %s\n", get_secure_type());

	if (check_secure_boot() != NONE_SECURE_BOOT)
	{
		UINT32  signature_size;
		unsigned char *ptr_enc;
		// Note: MCP src/dst address must be 8B aligned
		__attribute__((aligned(8))) UINT32  FPK_raw[4];	// flash protection key (not encrypted)
		__attribute__((aligned(8))) UINT32  FPK_enc[4];	// flash protection key (encrypted)
		__attribute__((aligned(8))) UINT32  FPK_test[4];	// flash protection key (decrypted)

#if defined(Config_Secure_Key_FALSE)
		printf("wrong bootcode image (not secure bootcode)\n");
		return -1;
#endif

		/* 1: prepare Certificate buffer = TDB + signature */
		copy_memory(cert_buf, (char *)&_f_scs_nocs_cert_tdb, scs_nocs_cert_tdb_size);
		copy_memory(cert_buf + scs_nocs_cert_tdb_size, (char *)&_f_scs_nocs_cert_sig, scs_nocs_cert_sig_size);

		/* 2.1: prepare Params buffer = TDB + signature */
		copy_memory(params_buf, (char *)&_f_scs_params_area_tdb, scs_params_area_tdb_size);
		copy_memory(params_buf + scs_params_area_tdb_size, (char *)&_f_scs_params_area_sig, scs_params_area_sig_size);

		/* 2.2: encrypt flash protection key in Params buffer */
		temp = offsetof(NOCS_Params, Flash_Protection_Key);
		ptr_enc = (unsigned char *)(params_buf + temp);
		copy_memory(FPK_raw, ptr_enc, 16);
		memset(FPK_enc, 0, sizeof(FPK_enc));
#if 1
		hexdump("Params buffer before replacement", params_buf, params_buf_size);
		hexdump("raw flash protection key", FPK_raw, sizeof(FPK_raw));
#endif

		res = AES_ECB_encrypt((UINT8 *)FPK_raw, sizeof(FPK_raw), (UINT8 *)FPK_enc, Kh_key);
		if (res) {
			printf("AES_ECB_encrypt return error: %x\n", res);
			return -66;
		}
		/* 2.3: replace with encrypted flash protection key in Params buffer */
		copy_memory(ptr_enc, FPK_enc, 16);
#if 1
		hexdump("encrypted flash protection key", FPK_enc, sizeof(FPK_enc));
		//hexdump("encrypted flash protection key", KSEG1(FPK_enc), sizeof(FPK_enc));
		hexdump("Params buffer after replacement", params_buf, params_buf_size);
#endif

#if 0	// test for flash protection key
		memset(FPK_test, 0, sizeof(FPK_test));
		res = AES_ECB_decrypt_key_in_CW(FPK_enc, sizeof(FPK_enc), FPK_test, 126);
		if (res) {
			printf("AES_ECB_decrypt_key_in_CW return error: %x\n", res);
			return -63;
		}
		hexdump("MCP decrypted flash protection key (AES key in CW)", FPK_test, sizeof(FPK_test));
/*
		res = RCP_AES_ECB_encrypt(FPK_raw, FPK_test);
		if (res) {
			printf("RCP_AES_ECB_encrypt return error: %x\n", res);
			return -64;
		}
		hexdump("RCP encrypted flash protection key", FPK_test, sizeof(FPK_test));

		res = RCP_AES_decrypt_flash_protection_key(FPK_enc, FPK_test);
		if (res) {
			printf("RCP_AES_decrypt_flash_protection_key return error: %x\n", res);
			return -65;
		}
		hexdump("RCP decrypted flash protection key", FPK_test, sizeof(FPK_test));
*/
		memset(FPK_test, 0, sizeof(FPK_test));
		res = AES_ECB_decrypt((UINT8 *)FPK_enc, sizeof(FPK_enc), (UINT8 *)FPK_test, Kh_key);
		if (res) {
			printf("AES_ECB_decrypt return error: %x\n", res);
			return -66;
		}
		hexdump("MCP decrypted flash protection key", FPK_test, sizeof(FPK_test));
#endif

		/* 3.1: prepare Aux code buffer = TDB + signature */
		copy_memory(aux_buf, (char *)&_f_scs_aux_code_tdb, scs_aux_code_tdb_size);
		copy_memory(aux_buf + scs_aux_code_tdb_size, (char *)&_f_scs_aux_code_sig, scs_aux_code_sig_size);

		/* 3.2: encrypt Aux code binary in TDB */
		temp = aux_buf_size - sizeof(NOCS_Aux_Code_Tail);
		ptr_enc = (unsigned char *) simple_malloc(temp);
		res = AES_CBC_encrypt((UINT8 *)aux_buf, temp, ptr_enc, aux_protection_key);
		if (res) {
			printf("AES_CBC_encrypt Aux code error: %x\n", res);
			return -67;
		}

		/* 3.3: replace with encrypted aux code binary in Aux buffer */
		copy_memory(aux_buf, ptr_enc, temp);

		/* 4.1: prepare DTE bootcode buffer = TDB + signature */
		copy_memory(bootcode_buf, (char *)&_f_scs_dte_bootcode_tdb, scs_dte_bootcode_tdb_size);
		copy_memory(bootcode_buf + scs_dte_bootcode_tdb_size, (char *)&_f_scs_dte_bootcode_sig, scs_dte_bootcode_sig_size);

		/* 4.2: encrypt DTE bootcode binary by flash protection key */
		temp = bootcode_buf_size - sizeof(NOCS_DTE_Bootcode_Tail);
		ptr_enc = (unsigned char *) simple_malloc(temp);
		res = AES_CBC_encrypt((UINT8 *)bootcode_buf, temp, ptr_enc, FPK_raw);
		if (res) {
			printf("AES_CBC_encrypt DTE bootcode error: %x\n", res);
			return -68;
		}

		/* 4.3: replace with encrypted DTE code binary in buffer */
		copy_memory(bootcode_buf, ptr_enc, temp);
	}
	else
	{
		printf("none secure boot\n");
		array = hasharray;
		array_size = (unsigned int )(&hasharray_end - hasharray);
		linux_ptr = rescuelinux;
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		linux_size     = (unsigned int ) 0;
#else /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
		linux_size     = (unsigned int )(&rescuelinux_end - rescuelinux);
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */

		// none secure image  = TDB + EM (hash)
		copy_memory(cert_buf, (char *)&_f_scs_nocs_cert_tdb, scs_nocs_cert_tdb_size);
		copy_memory(cert_buf + scs_nocs_cert_tdb_size, (char *)&_f_scs_nocs_cert_em, scs_nocs_cert_em_size);
		copy_memory(params_buf, (char *)&_f_scs_params_area_tdb, scs_params_area_tdb_size);
		copy_memory(params_buf + scs_params_area_tdb_size, (char *)&_f_scs_params_area_em, scs_params_area_em_size);
		copy_memory(aux_buf, (char *)&_f_scs_aux_code_tdb, scs_aux_code_tdb_size);
		copy_memory(aux_buf + scs_aux_code_tdb_size, (char *)&_f_scs_aux_code_em, scs_aux_code_em_size);
		copy_memory(bootcode_buf, (char *)&_f_scs_dte_bootcode_tdb, scs_dte_bootcode_tdb_size);
		copy_memory(bootcode_buf + scs_dte_bootcode_tdb_size, (char *)&_f_scs_dte_bootcode_em, scs_dte_bootcode_em_size);
	}

//#endif /* #ifdef FPGA */


    //dump 'Begin' string to RS232 to notify uset that flash write start to program
    print_uart("Begin:");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////NAND
	if ((flash_type == FLASH_TYPE_NAND) || (flash_type == FLASH_TYPE_SPI_NAND))
	{
		UINT32 current_block = 0;
		UINT32 end_page;
		UINT32 buf_start = DATA_TMP_ADDR;
		UINT32 data_length;
		UINT32 pagesize, blocksize, pagePerBlock;
		UINT32 supposed_block;
		UINT32 backup_number;
		UINT32 sparePerPage = 0;

		// magellan/Sirius start block 6   // we leave block empty: 0 for nand profile, 1, 2 (for BBT use), 3, 4 for GBT , 5 reversed
		// macarthur 1 start block 3   // we leave block empty: 0 for nand profile, 1, 2 (for BBT use)
		// we leave block empty: 0 for nand profile, 1, 2 (for BBT use)
		current_block += 6;

	    /*******************************************************
	     * identyfy flash type
	     *******************************************************/

		 if (flash_type == FLASH_TYPE_NAND)
			set_pin_mux(NAND_FLASH_BOOT);
		 else
			set_pin_mux(SPI_NAND_FLASH_BOOT);

		if ((*do_identify)(&device) < 0)
		{
			print_uart("error identify flash!!\n");
			return -2;
		}

		backup_number = 3;

		// init (setup block state table and erase old bootcode blocks)
		if (do_init(device))
		{
			print_uart("do_init falied\n");
			return -2;
		}

		if (flash_type == FLASH_TYPE_NAND) {
			pagesize = ((n_device_type *)device)->PageSize;
			blocksize = ((n_device_type *)device)->BlockSize;
			pagePerBlock = blocksize / pagesize;

			// calculate spare area size per page (for dump data)
			temp = ((n_device_type *)device)->ecc_bit;
			if (temp == ECC_6BIT)
				sparePerPage = (pagesize / 512) * 16;
			else if (temp == ECC_12BIT)
				sparePerPage = (pagesize / 512) * 26;
		}
		else {
			pagesize = ((spi_n_device_type *)device)->PageSize;
			blocksize = ((spi_n_device_type *)device)->BlockSize;
			pagePerBlock = blocksize / pagesize;
			sparePerPage = 64;
		}

	    /******************************
	     * prepare buffer for NOCS Certificate + Params Area + Aux_code + Unchecked area (4KB)
	     ******************************/
		// calculate actual data length
		temp_ptr = NULL;
		data_length = 0;
		data_length += align_to_boundary(cert_buf_size, pagesize) * pagesize;
		data_length += align_to_boundary(params_buf_size, pagesize) * pagesize;
		data_length += align_to_boundary(aux_buf_size, pagesize) * pagesize;
		data_length += 4096;	// don't forget SCS_Unchecked_Area
		if (data_length > blocksize) {
			printf("data size(0x%x) > blocksize(0x%x)\n", data_length, blocksize);
			return -3;
		}

		temp_ptr = (UINT8 *)simple_malloc(data_length);
		if (temp_ptr == NULL) {
			printf("simple_malloc(0x%x) failed\n", data_length);
			return -4;
		}
		// reset buffer to un-programmed state
		memset(temp_ptr, 0xff, data_length);
		idx = 0;

		// put NOCS Certificate, Params Area, Aux_code in buffer
		printf("copy NOCS Certificate in buffer offset 0x%x\n", idx);
		copy_memory(temp_ptr + idx, cert_buf, cert_buf_size);
		idx += align_to_boundary(cert_buf_size, pagesize) * pagesize;
		printf("copy Params Area in buffer offset 0x%x\n", idx);
		copy_memory(temp_ptr + idx, params_buf, params_buf_size);
		idx += align_to_boundary(params_buf_size, pagesize) * pagesize;
		printf("copy Aux_code in buffer offset 0x%x\n", idx);
		copy_memory(temp_ptr + idx, aux_buf, aux_buf_size);
		idx += align_to_boundary(aux_buf_size, pagesize) * pagesize;
		idx += 4096;
		printf("data_length: 0x%x, idx: 0x%x\n", data_length, idx);

#if defined(DUMP_NAND_FLASH) || defined(DUMP_SPI_NAND_FLASH)
		// clear block 0~5 to un-programmed state for simulation
		idx = (pagesize + sparePerPage) * pagePerBlock * 6;
		memset((UINT8 *)gdst_data_addr, 0xff, idx);
#endif
	    /******************************
	     * start to program NOCS Certificate + Params Area + Aux_code + Unchecked area (4KB)
	     ******************************/
		temp = current_block;
		end_page = (*do_write)(device, temp_ptr, &current_block, data_length, BLOCK_HWSETTING, 0);
		if (end_page == -1) {
			printf("write block(0x%x) error\n", temp);
			return -101;
		}

		printf("\ndump %s flash page 0x%x~0x%x\n",
			(flash_type == FLASH_TYPE_NAND ? "NAND" : "SPI-NAND"),
			(current_block * pagePerBlock),
			end_page);
		temp = end_page - current_block * pagePerBlock + 1;	// number of pages need to dump
		data_length = (6 * pagePerBlock + temp) * (pagesize + sparePerPage);

#if defined(DUMP_NAND_FLASH) || defined(DUMP_SPI_NAND_FLASH)
		printf("SCS flash data for simulation\n\taddr: 0x%x, size: 0x%x\n", gdst_data_addr, data_length);
#endif
		if (flash_type == FLASH_TYPE_NAND) {
#if defined(DUMP_NAND_FLASH)
			NF_dump_flash(device, gdst_data_addr + idx, (current_block * pagePerBlock), temp);
#endif
		}
		else if (flash_type == FLASH_TYPE_SPI_NAND) {
#if defined(DUMP_SPI_NAND_FLASH)
			SFC_dump_spi_nand_flash(device, gdst_data_addr + idx, (current_block * pagePerBlock), temp);
#endif
		}

		// calculate next block no
		current_block = (end_page / pagePerBlock) + 1;
		// align next dump address (1MB boundary)
		temp = align_to_boundary(data_length, 1024*1024) * (1024*1024);
#if defined(DUMP_NAND_FLASH) || defined(DUMP_SPI_NAND_FLASH)
		memset((UINT8 *)(gdst_data_addr + data_length), 0xff, (temp - data_length));
		gdst_data_addr += temp;
		printf("current_block:0x%x, data_length: 0x%x, gdst_data_addr: 0x%x\n", current_block, data_length, gdst_data_addr);
#else
		printf("current_block:0x%x, data_length: 0x%x\n", current_block, data_length);
#endif
	    /******************************
	     * start to program DTE bootcode
	     ******************************/
		data_length = align_to_boundary(bootcode_buf_size, pagesize) * pagesize;
		temp = current_block;
		end_page = (*do_write)(device, bootcode_buf, &current_block, data_length, BLOCK_BOOTCODE, 0);
		if (end_page == -1) {
			printf("write block(0x%x) error\n", temp);
			return -102;
		}

#if defined(DUMP_NAND_FLASH) || defined(DUMP_SPI_NAND_FLASH)
		printf("\ndump DTE bootcode from %s flash page 0x%x~0x%x\n",
			(flash_type == FLASH_TYPE_NAND ? "NAND" : "SPI-NAND"),
			(current_block * pagePerBlock),
			end_page);
		temp = end_page - current_block * pagePerBlock + 1;	// number of pages need to dump
		printf("flash data of DTE bootcode\n\taddr: 0x%x, size: 0x%x\n", gdst_data_addr, temp * (pagesize + sparePerPage));
#endif
		if (flash_type == FLASH_TYPE_NAND) {
#if defined(DUMP_NAND_FLASH)
			NF_dump_flash(device, gdst_data_addr, (current_block * pagePerBlock), temp);
#endif
		}
		else if (flash_type == FLASH_TYPE_SPI_NAND) {
#if defined(DUMP_SPI_NAND_FLASH)
			SFC_dump_spi_nand_flash(device, gdst_data_addr, (current_block * pagePerBlock), temp);
#endif
		}

		/* Reset Command */
		(*do_exit)(device);

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////SPI
	else if (flash_type == FLASH_TYPE_SPI)
	{
		UINT32 flash_pos, flash_base;

		if (check_secure_boot() == NONE_SECURE_BOOT) {
			flash_base = 0xbfc00000;
			flash_pos = flash_base + 0x8000;
		}
		else {
			flash_base = 0xbec00000;
			flash_pos = flash_base;
		}

	    /*******************************************************
	     * identyfy flash type and program code to flash device
	     *******************************************************/
		set_pin_mux(SPI_FLASH_BOOT);
	    if ((*do_identify)(&device) < 0)
	    {
	    	print_uart("error identify flash!!\n");
	    	return -2;
	    }

	    (*do_init)(device);

		/* erase first 1M byte area */
		printf("\nerase flash 0x%x, size 0x%x\n", (UINT32)resetrom_addr, 0x100000);
		if ((*do_erase)(device, (UINT32 *)resetrom_addr, 0x100000) !=0 )
			return -3;

		printf("\nwrite NOCS Certificate Area: 0x%x, size 0x%x to flash 0x%x\n", (UINT32)cert_buf, cert_buf_size, flash_pos);
		if ((*do_write)(device, cert_buf, (UINT32 *)flash_pos, cert_buf_size, 0, 0) != 0)
			return -4;

		flash_pos += cert_buf_size;
		printf("\nwrite Params Area: 0x%x, size 0x%x to flash 0x%x\n", (UINT32)params_buf, params_buf_size, flash_pos);
		if ((*do_write)(device, params_buf, (UINT32 *)flash_pos, params_buf_size, 0, 0) != 0)
			return -5;

		flash_pos += params_buf_size;
		printf("\nwrite Aux Code Area: 0x%x, size 0x%x, to flash 0x%x\n", (UINT32)aux_buf, aux_buf_size, flash_pos);
		if ((*do_write)(device, aux_buf, (UINT32 *)flash_pos, aux_buf_size, 0, 0) != 0)
			return -6;

		flash_pos += aux_buf_size;
		flash_pos += 4096;	// don't forget SCS_Unchecked_Area
		printf("\nwrite DTE Bootcode: 0x%x, size 0x%x to flash 0x%x\n", (UINT32)bootcode_buf, bootcode_buf_size, flash_pos);
		if ((*do_write)(device, bootcode_buf, (UINT32 *)flash_pos, bootcode_buf_size, 0, 0) != 0)
			return -7;
		//flash_pos += bootcode_buf_size;	// no need to dump DTE bootcode for simulation


#ifdef DUMP_SPI_FLASH
		printf("\ndump SPI flash 0x%x~0x%x => 0x%x\n", flash_base, flash_pos, SIMULATION_DUMP_ADDR);
		copy_memory((UINT8 *)SIMULATION_DUMP_ADDR, (UINT8 *)flash_base, (flash_pos - flash_base));
#endif

	    (*do_exit)(device);

#ifdef FPGA
	    return 0;
#endif

	    /* Reset Command */
	    (*do_exit)(device);

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////EMMC
	else if (flash_type == FLASH_TYPE_EMMC)
	{
#define EMMC_BLOCK_SIZE		512
#define EMMC_LAYOUT_BASE_START	0x20800

		UINT32 block_no;
		UINT8 *read_buf, *write_buf;
		//UINT32 buf_start;
		UINT32 data_length = 0;
		UINT32 sim_data_len = 0;
		block_size = EMMC_BLOCK_SIZE;
		block_no = EMMC_LAYOUT_BASE_START / block_size;
		/*******************************************************
		 * identyfy flash type
		 *******************************************************/
		set_pin_mux(EMMC_BOOT);

		if ((*do_identify)(&device) < 0)
		{
			print_uart("error identify flash!!\n");
			return -2;
		}

		if ((*do_init)(device))
		{
			print_uart("do_init falied\n");
			return -2;
		}

#ifndef SKIP_PROGRAM_BOOTCODE
	    /******************************
	     * prepare buffer for NOCS Certificate + Params Area + Aux_code + Unchecked area (4KB)
	     ******************************/
		// calculate actual data length
		data_length = 0;
		data_length += align_to_boundary(cert_buf_size, block_size) * block_size;
		data_length += align_to_boundary(params_buf_size, block_size) * block_size;
		data_length += align_to_boundary(aux_buf_size, block_size) * block_size;
		sim_data_len = data_length;
		data_length += 4096;	// don't forget SCS_Unchecked_Area
#ifdef PROGRAM_HWSETTING
		data_length += HWSETTING_FIX_SIZE;
#endif
		data_length += align_to_boundary(bootcode_buf_size, block_size) * block_size;

		// prepare buffer for image write to flash
		write_buf = (UINT8 *) simple_malloc(data_length);
		if (write_buf == NULL) {
			print_uart("simple_malloc failed\n");
			return -3;
		}
		// reset buffer to un-programmed state
		memset(write_buf, 0xff, data_length);

		if (verify_after_write) {
			// prepare buffer for image read from flash
			read_buf = (UINT8 *) simple_malloc(data_length);
			if (read_buf == NULL) {
				print_uart("simple_malloc failed\n");
				return -3;
			}
			printf("\nread_buf: %x\n", (UINT32)read_buf);
			memset(read_buf, 0xff, data_length);
		}

#ifdef DUMP_EMMC_FLASH
		// dump for simulation (start from head of flash)
		temp = EMMC_LAYOUT_BASE_START + data_length;
		printf("\tclear area for dump_data: 0x%x, size 0x%x\n", gdst_data_addr, temp);
		set_memory((UINT8 *)gdst_data_addr, 0xff, temp);
#endif

		// put NOCS Certificate, Params Area, Aux_code in buffer
		temp = 0;
		printf("copy NOCS Certificate in buffer offset 0x%x\n", temp);
		copy_memory(write_buf + temp, cert_buf, cert_buf_size);
		temp += align_to_boundary(cert_buf_size, block_size) * block_size;
		printf("copy Params Area in buffer offset 0x%x\n", temp);
		copy_memory(write_buf + temp, params_buf, params_buf_size);
		temp += align_to_boundary(params_buf_size, block_size) * block_size;
		printf("copy Aux_code in buffer offset 0x%x\n", temp);
		copy_memory(write_buf + temp, aux_buf, aux_buf_size);
		temp += align_to_boundary(aux_buf_size, block_size) * block_size;
		temp += 4096;

#ifdef PROGRAM_HWSETTING
		printf("copy hwsetting in buffer offset 0x%x\n", temp);
		copy_memory(write_buf + temp, hwsetting, hwsetting_size);
		temp += HWSETTING_FIX_SIZE;
#endif

		printf("copy DTE Bootcode Area in buffer offset 0x%x\n", temp);
		copy_memory(write_buf + temp, bootcode_buf, bootcode_buf_size);
		temp += align_to_boundary(bootcode_buf_size, block_size) * block_size;
		if (data_length != temp) {
			printf("size not match!\n\tdata_length: 0x%x, temp: 0x%x\n", data_length, temp);
			return -4;
		}

	    /******************************
	     * start to program NOCS Certificate + Params Area + Aux_code + Unchecked area (4KB) + DTE bootcode
	     ******************************/
		printf("start to program bootcode...\n");
		printf("do_write(write_buf=0x%x, block_no=0x%x, data_length=0x%x)\n", (UINT32)write_buf, block_no, data_length);
		if ((*do_write)( device, write_buf, &block_no, data_length, 0, 0)) {
			print_uart("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
			printf("read back: block 0x%x, size 0x%x\n", block_no, data_length);
			if ((*do_read)(device, &block_no, read_buf, data_length, 0)) {
				print_uart("do_read falied\n");
				return -5;
			}

			if (compare_memory(write_buf, read_buf, data_length)) {
				printf("compare_memory(0x%x, 0x%x, 0x%x) falied\n", (UINT32)write_buf, (UINT32)read_buf, data_length);
				return -6;
			}
		}
#endif /* End of #ifndef SKIP_PROGRAM_BOOTCODE */


		/***********************************************************************
		 * start to read extern_param structure
		 ***********************************************************************/
		data_length = 0;
		data_length += align_to_boundary(EMMC_EXT_PARAM_BYTE_SIZE, block_size) * block_size;
			 
		// prepare buffer to read from flash
		read_buf = (UINT8 *) simple_malloc(data_length);
		if (read_buf == NULL) {
			print_uart("simple_malloc failed\n");
			return -3;
		}
		// reset buffer
		memset(read_buf, 0xff, data_length);

		block_no = EMMC_EXT_PARAM_BLK_ADDR;

		printf("read back extern_param: block 0x%x, size 0x%x\n", block_no, data_length);
		if ((*do_read)(device, &block_no, read_buf, data_length, 0)) {
			printf("do_read check falied\n");
			return -5;
		}

		copy_memory((unsigned char *)&param, read_buf, sizeof(param));
		printf("\nextern param\nrescue img addr=0x%x\nparam data start blk=0x%x\nrescue img size=0x%x\n", param.rescue_img_addr, param.data_start_blk, param.rescue_img_size);

#ifndef SKIP_PROGRAM_RESCUE_LINUX
		data_length = 0;
		data_length += align_to_boundary(linux_size, block_size) * block_size;
		if( data_length != 0 ) {
			// prepare buffer for image write to flash
			write_buf = (UINT8 *) simple_malloc(data_length);
			if (write_buf == NULL) {
				print_uart("simple_malloc failed\n");
				return -3;
			}
			// reset buffer to un-programmed state
			memset(write_buf, 0xff, data_length);
			
			if (verify_after_write) {
				// prepare buffer for image read from flash
				read_buf = (UINT8 *) simple_malloc(data_length);
				if (read_buf == NULL) {
					print_uart("simple_malloc failed\n");
					return -3;
				}
				printf("\nread_buf: %x\n", (UINT32)read_buf);
				memset(read_buf, 0xff, data_length);
			}

			/***********************************************************************
			 * prepare data for linux rescue image
			 ***********************************************************************/
			printf("copy rescue linux Area in buffer offset 0x%x\n", write_buf);
			copy_memory(write_buf, rescuelinux, data_length);
		

			/***********************************************************************
			 * start to program data(rescue linux)
			 ***********************************************************************/
			block_no = EMMC_RESCURE_LOGO_BLK_ADDR;
			printf("start to program rescue linux...\n");
			printf("do_write(write_buf=0x%x, block_no=0x%x, data_length=0x%x)\n", (UINT32)write_buf, block_no, data_length);
			if ((*do_write)( device, write_buf, &block_no, data_length, 0, 0)) {
				print_uart("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
				printf("read back: block 0x%x, size 0x%x\n", block_no, data_length);
				if ((*do_read)(device, &block_no, read_buf, data_length, 0)) {
					print_uart("do_read falied\n");
					return -5;
				}

				if (compare_memory(write_buf, read_buf, data_length)) {
					printf("compare_memory(0x%x, 0x%x, 0x%x) falied\n", (UINT32)write_buf, (UINT32)read_buf, data_length);
					return -6;
				}
			}
			
			param.rescue_img_addr = EMMC_RESCURE_LOGO_BLK_ADDR;
			param.data_start_blk = EMMC_RESCURE_LOGO_BLK_ADDR;
			param.rescue_img_size = linux_size;
			printf("\nrenew extern param\nrescue img addr=0x%x\nparam data start blk=0x%x\nrescue img size=0x%x\n", param.rescue_img_addr, param.data_start_blk, param.rescue_img_size);


			/***********************************************************************
			 * start to program extern_param structure
			 ***********************************************************************/	
			data_length = 0;
			data_length += align_to_boundary(EMMC_EXT_PARAM_BYTE_SIZE, block_size) * block_size;
				 
			// prepare buffer for image write to flash
			write_buf = (UINT8 *) simple_malloc(data_length);
			if (write_buf == NULL) {
				print_uart("simple_malloc failed\n");
				return -3;
			}
			// reset buffer to un-programmed state
			memset(write_buf, 0xff, data_length);
			
			if (verify_after_write) {
				// prepare buffer for image read from flash
				read_buf = (UINT8 *) simple_malloc(data_length);
				if (read_buf == NULL) {
					print_uart("simple_malloc failed\n");
					return -3;
				}
				printf("\nread_buf: %x\n", (UINT32)read_buf);
				memset(read_buf, 0xff, data_length);
			}
			
			set_memory((char *)write_buf, 0xff, data_length);
			copy_memory((unsigned char *)write_buf, &param, sizeof(param));
			block_no = EMMC_EXT_PARAM_BLK_ADDR;
			
			printf("write extern_param: block 0x%x, size 0x%x, vali size 0x%04x\n", block_no, data_length, sizeof(param) );
			if ((*do_write)( device, (unsigned char *)write_buf, &block_no, data_length, 0, 0)) {
				printf("do_write falied\n");
				return -4;
			}
			
			if(verify_after_write) {
				printf("read back extern_param: block 0x%x, size 0x%x\n", block_no, data_length);
				if ((*do_read)(device, &block_no, read_buf, data_length, 0)) {
					printf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)write_buf, read_buf, data_length)) {
					printf("verify extern_param falied\n");
					return -6;
				}
			}
			
		}
		else {
			printf("\nskip program rescue linux\n");
			//param.rescue_img_addr = 0;
			//param.data_start_blk = 0;
			//param.rescue_img_size = 0;
		}
#endif
	


	    /******************************
	     * start to program DTE bootcode
	     ******************************/
/*
		//TODO: write DTE bootcode
		block_no += align_to_boundary(data_length, block_size);
		temp = align_to_boundary(bootcode_buf_size, block_size) * block_size;
		printf("DTE bootcode buffer: 0x%x\n", (UINT32)bootcode_buf);
		if ((*do_write)( device, bootcode_buf, &block_no, temp, 0, 0)) {
			printf("do_write(0x%x, 0x%x, 0x%x) falied\n", bootcode_buf, block_no, temp);
			return -7;
		}

		if (verify_after_write) {
			printf("read back: block 0x%x, size 0x%x\n", block_no, temp);
			if ((*do_read)(device, &block_no, read_buf, temp, 0)) {
				printf("do_read falied\n");
				return -8;
			}

			if (compare_memory(bootcode_buf, read_buf, temp)) {
				printf("compare_memory(0x%x, 0x%x, 0x%x) falied\n", (UINT32)bootcode_buf, (UINT32)read_buf, temp);
				return -9;
			}
		}
*/
#ifdef DUMP_EMMC_FLASH
		// dump for simulation (not including DTE bootcode)
		dump_data("Sirius eMMC data",
			(gdst_data_addr + EMMC_LAYOUT_BASE_START),
			write_buf, sim_data_len);
#endif

		(*do_exit)(device);
	}

    //dump 'Finish' string to RS232
    print_uart("\nFinish\n");

	//while(1);
    return 0;
}

#ifdef FPGA
static int get_Efuse_secure_state(void)
{
#ifdef FPGA_SECURE_BOOT_TYPE
	return (FPGA_SECURE_BOOT_TYPE);
#else
	return (NONE_SECURE_BOOT);
#endif
}
#endif /* #ifdef FPGA */

static int check_secure_boot(void)
{
#ifdef FPGA
/*
	// check user specified argument
	if (force_secure || test_secure)
		return (IS_SECURE_BOOT);
	else
*/
		return get_Efuse_secure_state();
#else

	return get_secure_boot_type();
#endif
}

static int check_bonding(void)
{
	return 0;
}

static int get_options(UINT32 argc, char **argv, UINT8 *force_flash_type, UINT8 *flash_type, UINT8 *verify_after_write,
	UINT8 *force_secure, UINT8 *test_secure, UINT8 *preserve_original_param,
	UINT8 *input_kh_key, UINT32 *efuse_key, UINT8 *noreset)
{
	UINT8 i;

	for (i = 1; i < argc; i++)
	{
		if (compare_str(argv[i], "nand") == 0)
		{
			*force_flash_type = 1;
			*flash_type = FLASH_TYPE_NAND;
		}

		if (compare_str(argv[i], "spi") == 0)
		{
			*force_flash_type = 1;
			*flash_type = FLASH_TYPE_SPI;
		}

		if (compare_str(argv[i], "emmc") == 0)
		{
			*force_flash_type = 1;
			*flash_type = FLASH_TYPE_EMMC;
		}

		if (compare_str(argv[i], "verify") == 0)
			*verify_after_write = 1;

		if (compare_str(argv[i], "secure") == 0)
			*force_secure = 1;

		if (compare_str(argv[i], "test_secure") == 0)
			*test_secure = 1;

		if (compare_str(argv[i], "preserve") == 0)
			*preserve_original_param = 1;

		if (compare_str(argv[i], "noreset") == 0)
			*noreset = 1;



		if (strstr(argv[i], "Kh=") != NULL) {
			int j;
			char *key_str, piece[9];

			key_str = argv[i] + 3;		// skip "Kh=" characters
			if (strlen(key_str) != 32)
				return -1;
			for (j = 0; j < 32; j++) {
				if (is_hex_digit(key_str[j]) != 0)
					return -1;
			}

			for (j = 0; j < 4; j++, key_str+=8) {
				memset(piece, 0, sizeof(piece));
				copy_memory(piece, key_str, 8);
				*(efuse_key+j) = hexstr2int(piece);
				//printf("%d: %s\n", j, piece);
			}
			*input_kh_key = 1;
		}

	}

	// both parameters "secure" and "test_secure" cannot appear at the same time
	if ((*force_secure == 1) && (*test_secure == 1))
		return -1;

	return 0;
}

static int bootcode_encrypted(void)
{
	//always return 1, if secure boot, bootcode always encrypted
//#ifdef FPGA_BOOTCODE_ENCRYPTED
	return 1;
//#else
//	return 0;
//#endif
}

static const char * get_secure_type(void)
{
	int type;

#ifdef FPGA

#ifdef FPGA_SECURE_BOOT_TYPE
	type = FPGA_SECURE_BOOT_TYPE;
#else
	type = NONE_SECURE_BOOT;
#endif

#else

	type = get_secure_boot_type();

#endif
	switch (type) {
		case NONE_SECURE_BOOT:
			return "NONE_SECURE_BOOT";
		case NAGRA_SECURE_BOOT:
			return "NAGRA_SECURE_BOOT";
		case RTK_SECURE_BOOT:
			return "RTK_SECURE_BOOT";
		case DCAS_SECURE_BOOT:
			return "DCAS_SECURE_BOOT";
		default:
			return "unknown";
	}

}

static unsigned int align_to_boundary(unsigned int size, unsigned int block_size)
{
	return (size % block_size ? size / block_size + 1 : size / block_size);
}
#ifdef DUMP_EMMC_FLASH
static void dump_data(const char *str, unsigned int dst, unsigned int src, unsigned int len)
{
	printf("\tdump %s from 0x%x to 0x%x, size 0x%x\n", str, src, dst, len);
	copy_memory((UINT8 *)dst, (UINT8 *)src, len);
}
#endif

