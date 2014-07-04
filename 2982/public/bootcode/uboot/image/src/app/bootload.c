void c_entry(void);

/*
 * Don't use global variables here.
 */

void c_entry(void)
{
	/* test code */
	unsigned int value = (unsigned int)0x23790000;
	unsigned int *reg = (unsigned int *)0xb8060118;

	*reg = value;
}
