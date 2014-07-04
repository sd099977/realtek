#include <common.h>
#include <command.h>
#include <asm/arch/io.h>
#include <asm/arch/system.h>

#define KCPU_WAIT_HW_SEM_REG			(0xb801a630)
#define KCPU_WAIT_JUMP_DUMMY_REG		(0xb8060124)

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

//#define KBOOT_TEST_KCPU_DECRYPT
//#define KBOOT_TEST_KCPU_LZMA

void release_kcpu_hw_semaphore(void)
{
	rtd_outl(KCPU_WAIT_HW_SEM_REG, 0x0);
}

uint wait_kcpu_done_status(void)
{
	uint regValue;
	int i = 0;

	while(1) {
		regValue = rtd_inl(KCPU_WAIT_JUMP_DUMMY_REG);

		if ((regValue & MAGIC_KCPU_ST_MASK) == MAGIC_KCPU_ST_MASK) {
			break;
		}

		// reduce rbus traffic
		for (i = 0;i < 0x2000;i++)
			;
	}

	return regValue;
}

int do_kboot_wait(void)
{
	uint status;

	printf("wait kcpu done ...\n");

	status = wait_kcpu_done_status();

	if (status == MAGIC_KCPU_ST_OK) {
		printf("status: ok\n");
		return 0;
	}
	else {
		printf("status: failed\n");
		return 1;
	}
}

int do_kboot_normal(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_OP_SETUP_NORMAL);

	release_kcpu_hw_semaphore();

	return 0;
}

int do_kboot_rescue(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_OP_SETUP_RESCUE);

	release_kcpu_hw_semaphore();

	return 0;
}

int do_kboot_go_normal(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_OP_GO_NORMAL);

	release_kcpu_hw_semaphore();

	return 0;
}

int do_kboot_go_rescue(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_OP_GO_RESCUE);

	release_kcpu_hw_semaphore();

	return 0;
}

#ifdef KBOOT_TEST_KCPU_LZMA
int do_kboot_t_lzma(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_TEST_LZMA);

	release_kcpu_hw_semaphore();

	return 0;
}
#endif

#ifdef KBOOT_TEST_KCPU_DECRYPT
int do_kboot_t_decrypt(void)
{
	rtd_outl(KCPU_WAIT_JUMP_DUMMY_REG, MAGIC_KCPU_TEST_DECRYPT);

	release_kcpu_hw_semaphore();

	return 0;
}
#endif

int do_kboot(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	int ret = CMD_RET_SUCCESS;

	if (argc == 2) {
		if (strcmp(argv[1], "normal") == 0) {
			if (do_kboot_normal() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
		else if (strcmp(argv[1], "rescue") == 0) {
			if (do_kboot_rescue() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
		else if (strcmp(argv[1], "go_k") == 0) {
			if (do_kboot_go_normal() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
		else if (strcmp(argv[1], "go_r") == 0) {
			if (do_kboot_go_rescue() != 0) {
				ret = CMD_RET_FAILURE;
			}
			else {
				printf("start k rescue. (s enter infinite loop)\n");

				while(1){
					; // enter infinite loop
				}
			}
		}
		else if (strcmp(argv[1], "wait") == 0) {
			if (do_kboot_wait() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
#ifdef KBOOT_TEST_KCPU_LZMA
		else if (strcmp(argv[1], "t_lzma") == 0) {
			if (do_kboot_t_lzma() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
#endif
#ifdef KBOOT_TEST_KCPU_DECRYPT
		else if (strcmp(argv[1], "t_dec") == 0) {
			if (do_kboot_t_decrypt() != 0) {
				ret = CMD_RET_FAILURE;
			}
		}
#endif
		else {
			return CMD_RET_USAGE;
		}
	}
	else {
		return CMD_RET_USAGE;
	}

	return ret;
}

U_BOOT_CMD(
	kboot,	CONFIG_SYS_MAXARGS,	1,	do_kboot,
	"start kboot function",
	"[normal | rescue | go_k | go_r"
#ifdef KBOOT_TEST_KCPU_LZMA
	" | t_lzma"
#endif
#ifdef KBOOT_TEST_KCPU_DECRYPT
	" | t_dec"
#endif
	"]\n"
	"   normal  - read normal linux from flash\n"
	"   rescue  - read rescue linux from flash\n"
	"   go_k    - enter normal linux\n"
	"   go_r    - enter rescue linux\n"
	"   wait    - wait kboot status\n"
#ifdef KBOOT_TEST_KCPU_LZMA
	"   t_lzma  - test lzma function\n"
#endif
#ifdef KBOOT_TEST_KCPU_DECRYPT
	"   t_dec   - test decrypt function\n"
#endif
);

