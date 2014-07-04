#ifndef GPIO_USERSPACE_ACCESS_LIBRARY
#define GPIO_USERSPACE_ACCESS_LIBRARY

#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/mis_reg.h>

//#define MIS_PSELH	((volatile int)0xb801b000)
//#define MIS_PSELL	((volatile int)0xb801b004)

int getGPIO(int GPIO_NUM);
int setGPIO(int GPIO_NUM, int value);
int getISOGPIO(int ISOGPIO_NUM);
int setISOGPIO(int ISOGPIO_NUM, int value);


#endif
