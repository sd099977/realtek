#include <common.h>
#include <rbusPinmuxReg.h>
#include <asm/arch/io.h>
#if defined(CONFIG_RTD299X)
#include <asm/arch/panelConfigParameter.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/panel_config_parameter.h>
#endif
#include <asm/arch/fw_info.h>

#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/gpio.h>

void pcb_gen_kernel_cmd_line(char *buffer, PCB_ENUM_T *ppcb_enum) {

	int i;
	char tmp[256];
//	unsigned long long k=0x1234567890;
	unsigned int value;
	i = 0;
	if (ppcb_enum == NULL) {
		ppcb_enum = pcb_enum;
	}
	buffer[0] = 0;
	do {
		if(ppcb_enum[i].name == NULL) break;
		if(ppcb_enum[i].name[0] == 0) break;
		//printf("IO Config = %s@%llx\n", ppcb_enum[i].name, ppcb_enum[i].info);
		sprintf(tmp, "pcb_enum=%s,0x", ppcb_enum[i].name);
		strcat(buffer, tmp);
		value = (unsigned int) (ppcb_enum[i].info >> 32);
		sprintf(tmp,"%08x", value);
		//printf("%s\n", tmp);
		strcat(buffer, tmp);
		value = (unsigned int) (ppcb_enum[i].info & 0xFFFFFFFF);
		sprintf(tmp,"%08x ", value);
		//printf("%s\n", tmp);
		strcat(buffer, tmp);

		//printf("%s\n", buffer);

		i ++;
	} while(1);

#ifdef ENABLE_PCBENUM_PANEL_ACTIVE_SIZE
	if ((&default_panel_parameter)->iCONFIG_DISP_ACT_END_HPOS == 1366) {
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "IS_1366X768");
		strcat(buffer, tmp);
	}
	else {
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "IS_1920X1080");
		strcat(buffer, tmp);
	}
#endif
#ifdef HISENSE_OPEN_CELL_PANEL
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "HISENSE_OPEN_CELL_PANEL");
		strcat(buffer, tmp);
#endif
}

unsigned int pcb_get_boot_flash_type(void)
{
	int state, boottype;
	int reg_val, tmp;

	/* save original settings */
	tmp = rtd_inl(PINMUX_GPIO_CFG_22_VADDR);
	state = rtd_inl(MIS_GP3DIR);

	/* set GPIO[118:117] as GPI */
	rtd_outl(PINMUX_GPIO_CFG_22_VADDR, tmp | 0x00f0f000);	// set  mux to GPIO[118:117]
	rtd_outl(MIS_GP3DIR, state & (~(_BIT21 | _BIT22)));	// set GPIO[118:117] as input pin

	/* get boottype from GPIO [118:117] */
	reg_val = rtd_inl(MIS_GP3DATI);
	boottype = (reg_val >> 21) & 0x3;

	/* restore setting */
	rtd_outl(MIS_GP3DIR, state);	// restore GPIO[118:117] direction
	rtd_outl(PINMUX_GPIO_CFG_22_VADDR, tmp);	// restore pin mux

	switch(boottype) {
		case 0:
			return FLASH_TYPE_NAND;

		case 1:
			return FLASH_TYPE_SPI;

		case 2:
			return FLASH_TYPE_EMMC;

		case 3:
			return FLASH_TYPE_SPI;

		default:	// should be impossible...
			return FLASH_TYPE_UNKNOWN;
	}

	return FLASH_TYPE_UNKNOWN;
}

char *pcb_get_boot_flash_type_string(void)
{
	FLASH_TYPE_T flash_type = FLASH_TYPE_UNKNOWN;

	flash_type = pcb_get_boot_flash_type();

	switch(flash_type) {
		case FLASH_TYPE_NAND:
			return FLASH_TYPE_NAND_STRING;

		case FLASH_TYPE_SPI:
			return FLASH_TYPE_SPI_STRING;

		case FLASH_TYPE_EMMC:
			return FLASH_TYPE_EMMC_STRING;

		default:
			return FLASH_TYPE_UNKNOWN_STRING;
	}

	return FLASH_TYPE_UNKNOWN_STRING;
}

