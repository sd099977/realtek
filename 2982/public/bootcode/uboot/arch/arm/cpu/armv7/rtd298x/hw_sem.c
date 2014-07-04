#include <common.h>
#include <asm/arch/io.h>

#define KCPU_FLASH_SHARED_SEM_REG			(0xb801a62c)

void get_flash_shared_semaphore(void)
{
	unsigned int i;

	while(1)
	{
		if (rtd_inl(KCPU_FLASH_SHARED_SEM_REG) == 0x1)
		{
			break;
		}

		for(i = 0;i < 1024;i++); //reduce rbus traffic
	}
}

void release_flash_shared_semaphore(void)
{
	rtd_outl(KCPU_FLASH_SHARED_SEM_REG, 0x0);
}


