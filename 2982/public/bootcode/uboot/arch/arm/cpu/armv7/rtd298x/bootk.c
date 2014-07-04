#include <common.h>
#include <environment.h>
#include <asm/arch/system.h>
#include <asm/arch/factorylib_ro.h>
#include <platform_lib/board/pcb_mgr.h>

DECLARE_GLOBAL_DATA_PTR;

extern void * memset(void * s,int c,size_t count);

long *kcpi_argv = (long *)KCPU_CMDLINE_ADDR;
char *kcpu_cmdline = (char *)(KCPU_CMDLINE_ADDR + sizeof(long)*2);

#define CONFIG_SECURE_STORE_START	0x1400000

int boot_prep_linux_kcpu(void)
{
	char tmp_cmd[32];
	unsigned int memsize=0;
	int i;
	PCB_ENUM_T *ppcb_enum;

	memset((void *)kcpi_argv, 0x0, KCPU_CMDLINE_SIZE);
	kcpi_argv[1] = (long)kcpu_cmdline | MIPS_KSEG0BASE;

   for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
      memsize += gd->bd->bi_dram[i].size;
   }

	// MIPS max DDR support is 512 MB
	if (memsize >= 0x20000000)
		memsize = 0x20000000;

   sprintf(tmp_cmd, "memsize=0x%x", memsize);
   strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	// we no need to pass whole envp to kernel, and just pick up the ones we want.
	sprintf(tmp_cmd, " factory_ro=0x%x@0x%x ", CONFIG_FACTORY_RO_SIZE, CONFIG_FACTORY_RO_START);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, " ss_start=0x%x ", CONFIG_SECURE_STORE_START);
   strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	ppcb_enum = pcb_enum;
	do {
      if(ppcb_enum[i].name == NULL) break;
      if(ppcb_enum[i].name[0] == 0) break;
		if (!strncmp(ppcb_enum[i].name, "PIN_FLASH_WP", sizeof("PIN_FLASH_WP"))) {
			sprintf(tmp_cmd, "flash_wp=0x%08x%08x", (unsigned int)(ppcb_enum[i].info >> 32), (unsigned int)(ppcb_enum[i].info & 0xffffffff));
   		strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));
			break;
		}
		i++;
   } while(1);

	if (strlen(kcpu_cmdline) >= KCPU_CMDLINE_SIZE) {
		printf("KCPU's command line parameters is TOO MUCH!\n");
		return 1;
	}

	printf("kcpu_cmdline is %s...........\n", kcpu_cmdline);

	return 0;
}
