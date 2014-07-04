#include "sysdefs.h"
#include "sed_drv_common.h"

/*
 * CCTL: CP0 General Register Address = 20
 *  +---------+---------+---------+----------+--------+----------+--------+
 *  |  31-21  |    20   |  19-12  |     11   |   10   |     9    |  8     |
 *  +---------+---------+---------+----------+--------+----------+--------+
 *  |  Rsrvd  | WBMerge |  Rsrvd  |  DMEMOff | DMEMOn | DWBInval |   DWB  |
 *  +---------+---------+---------+----------+--------+----------+--------+
 *  |    7    |    6    |    5    |     4    |   3-2  |    1     |    0   |
 *  +---------+---------+---------+----------+--------+----------+--------+
 *  | DWAlloc |  Rsrvd  | IMEMOff | IMEMFill |  ILock |  IInval  | DInval |
 *  +---------+---------+---------+----------+--------+----------+--------+
 */

// write back the dcache and invalidate
void dcache_flush_invalidate(void)
{
	asm volatile (
         "mfc0  $8, $20\n"
         "nop\n"
         "and   $8, 0xfffffdff\n"	/* DWBInval */
         "mtc0  $8, $20\n"
         "nop\n"
         "or    $9, $8, 0x00000200\n"
         "mtc0  $9, $20\n"
         "nop\n"
         "mtc0  $8, $20\n"
         "nop\n"
   );
}

// write back the dcache
void dcache_flush(void)
{
   asm volatile (
         "mfc0  $8, $20\n"
         "nop\n"
         "and   $8, 0xfffffeff\n"	/* DWB */
         "mtc0  $8, $20\n"
         "nop\n"
         "or    $9, $8, 0x00000100\n"
         "mtc0  $9, $20\n"
         "nop\n"
         "mtc0  $8, $20\n"
         "nop\n"
   );
}

int compare_memory(void *s1, void *s2, unsigned int size)
{
	unsigned int i;
	char *p1, *p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	for (i = 0; i < size; i++) {
		if (p1[i] != p2[i])
			return (int)p1[i] - (int)p2[i];
	}

	return 0;
}

void copy_memory(void *dst, void *src, unsigned int size)
{
	unsigned int i;

	// word copy if all arguments are word-aligned
	if ( (((UINT32)dst & 0x3) == 0) && (((UINT32)src & 0x3) == 0) && ((size & 0x3) == 0) ) {
		for (i = 0; i < size; i += 4)
			REG32(((UINT32)dst) + i) = REG32(((UINT32)src) + i);
	}
	else {	// byte copy
		for (i = 0; i < size; i++)
			REG8(((UINT32)dst) + i) = REG8(((UINT32)src) + i);
	}
}

void get_flash_shared_semaphore(void)
{
	unsigned int i;

	while(1)
	{
		if (REG32(KCPU_FLASH_SHARED_SEM_REG) == 0x1)
		{
			break;
		}

		for(i = 0;i < 1024;i++); //reduce rbus traffic
	}
}

void release_flash_shared_semaphore(void)
{
	REG32(KCPU_FLASH_SHARED_SEM_REG) = 0x0;
}

