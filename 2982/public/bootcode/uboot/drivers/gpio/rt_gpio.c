#include <common.h>
#include <platform_lib/board/gpio.h>
#include <asm/arch/io.h>

#define gpio_assert(x)		printf("assert assert assert!!!! GPIO_NUM=%d\n", GPIO_NUM)
#define iso_gpio_assert(x)	printf("assert assert assert!!!! ISOGPIO_NUM=%d\n", ISOGPIO_NUM)

int getGPIO(int GPIO_NUM) {
	int bitOffset;
	volatile int regAddr;
	int regValue;

	if(GPIO_NUM <= 31) {
		bitOffset = GPIO_NUM;

		// Set Direction to Input
		regAddr = (MIS_GP0DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP0DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(GPIO_NUM >= 32 && GPIO_NUM <= 63) {
		bitOffset = GPIO_NUM - 32;

		// Set Direction to Input
		regAddr = (MIS_GP1DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP1DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(GPIO_NUM >= 64 && GPIO_NUM <= 95) {
		bitOffset = GPIO_NUM - 64;

		// Set Direction to Input
		regAddr = (MIS_GP2DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP2DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(GPIO_NUM >= 96 && GPIO_NUM <= 127) {
		bitOffset = GPIO_NUM - 96;

		// Set Direction to Input
		regAddr = (MIS_GP3DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP3DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(GPIO_NUM >= 128 && GPIO_NUM <= 159) {
		bitOffset = GPIO_NUM - 128;

		// Set Direction to Input
		regAddr = (MIS_GP4DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP4DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(GPIO_NUM >= 160 && GPIO_NUM <= 191) {
		bitOffset = GPIO_NUM - 160;

		// Set Direction to Input
		regAddr = (MIS_GP5DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (MIS_GP5DATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else { // no such GPIO pin!
		gpio_assert(0);
		return -1;
	}
}

int setGPIO(int GPIO_NUM, int value) {
	int bitOffset;
	volatile int regAddr;
	int regValue;

	if(GPIO_NUM <= 31) {
		bitOffset = GPIO_NUM;

		// Set Direction to Ouput
		regAddr = (MIS_GP0DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP0DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);

		return 0;
	}
	else if(GPIO_NUM >= 32 && GPIO_NUM <= 63) {
		bitOffset = GPIO_NUM - 32;

		// Set Direction to Ouput
		regAddr = (MIS_GP1DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP1DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);

		return 0;
	}
	else if(GPIO_NUM >= 64 && GPIO_NUM <= 95) {
		bitOffset = GPIO_NUM - 64;

		// Set Direction to Ouput
		regAddr = (MIS_GP2DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP2DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);
		return 0;
	}
	else if(GPIO_NUM >= 96 && GPIO_NUM <= 127) {
		bitOffset = GPIO_NUM - 96;

		// Set Direction to Ouput
		regAddr = (MIS_GP3DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP3DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);
		return 0;
	}
	else if(GPIO_NUM >= 128 && GPIO_NUM <= 159) {

		bitOffset = GPIO_NUM - 128;

		// Set Direction to Ouput
		regAddr = (MIS_GP4DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP4DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);
		return 0;
	}
	else if(GPIO_NUM >= 160 && GPIO_NUM <= 191) {

		bitOffset = GPIO_NUM - 160;

		// Set Direction to Ouput
		regAddr = (MIS_GP5DIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		// Set Value
		regAddr = (MIS_GP5DATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);	// set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);
		return 0;
	}
	else { // no such GPIO pin!
		gpio_assert(0);
		return -1;
	}
}

int getISOGPIO(int ISOGPIO_NUM)
{
	int bitOffset;
	volatile int regAddr;
	int regValue;

	if(ISOGPIO_NUM <= 31) {
		bitOffset = ISOGPIO_NUM;

		// Set Direction to Input
		regAddr = (ISO_GPDIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (ISO_GPDATI);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else if(ISOGPIO_NUM >= 32 && ISOGPIO_NUM <= 48) {
		bitOffset = ISOGPIO_NUM - 32;

		// Set Direction to Input
		regAddr = (ISO_GPDIR_1);
		regValue = rtd_inl(regAddr);
		regValue = regValue & (~(0x01 << bitOffset));
		rtd_outl(regAddr, regValue);

		// Get Value
		regAddr = (ISO_GPDATI_1);
		regValue = rtd_inl(regAddr);
		if(regValue & (0x01 << bitOffset))
			return 1;
		else
			return 0;
	}
	else { // no such ISO GPIO pin!
		iso_gpio_assert(0);
		return -1;
	}
}

int setISOGPIO(int ISOGPIO_NUM, int value)
{
	int bitOffset;
	volatile int regAddr;
	int regValue;

	if(ISOGPIO_NUM <= 31) {
		bitOffset = ISOGPIO_NUM;

		// Set Value
		regAddr = (ISO_GPDATO);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);  // set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);

		// Set Direction to Ouput
		regAddr = (ISO_GPDIR);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);

		return 0;
	}
	else if(ISOGPIO_NUM >= 32 && ISOGPIO_NUM <= 48) {
		bitOffset = ISOGPIO_NUM - 32;

		// Set Value
		regAddr = (ISO_GPDATO_1);
		regValue = rtd_inl(regAddr);

		if(value)
			regValue = regValue | (0x01 << bitOffset);  // set to 1
		else
			regValue = regValue & (~(0x01 << bitOffset)); // set to 0

		rtd_outl(regAddr, regValue);

		// Set Direction to Ouput
		regAddr = (ISO_GPDIR_1);
		regValue = rtd_inl(regAddr);
		regValue = regValue | (0x01 << bitOffset);
		rtd_outl(regAddr, regValue);
		return 0;
	}
	else { // no such ISO GPIO pin!
		iso_gpio_assert(0);
		return -1;
	}
}

