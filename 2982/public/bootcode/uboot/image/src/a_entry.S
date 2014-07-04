/* Register */
#define REG_HW_SEMAPHORE		0xb801a000
#define REG_UART0_BASE			0xb8062300
#define REG_UART1_BASE			0xb801bc00
#define DEFAULT_UART			REG_UART0_BASE


	.section ".text", "ax"
	.globl	a_entry
	.ent	a_entry
a_entry:
	.set 	noreorder

	/* set 5280 CP0 status register and vector interrupt address */
#if 1
	.word 0x40106000,0x3c118000,0x36310001,0x02118025,\
		 0x3c11ffbf,0x3631ffff,0x02118024,0x40906000,\
		 0x3c108000,0x36101900,0x40f01000,0x00000000,\
		 0x3c1000ff,0x40f00000,0x00000000
#else

	mfc0	s0, $12
	lui 	s1,0x8000
	ori 	s1,s1,0x1
	or		s0,s0,s1
	lui 	s1,0xffbf
	ori 	s1,s1,0xffff
	and 	s0,s0,s1
	mtc0	s0,$12
	lui 	s0,0x8000
	ori 	s0,s0,0x1900
	mtlxc0	s0,INTVEC
	nop
	lui 	s0,0xff
	mtlxc0	s0,ESTATUS
	nop

#endif

	/* audio */

	/* Print Await */
	li		$8, 'A'	/* A */
	sw		$8, DEFAULT_UART

	li		$8, 0x77	/* w */
	sw		$8, DEFAULT_UART

	li		$8, 0x61	/* a */
	sw		$8, DEFAULT_UART

	li		$8, 0x69	/* i */
	sw		$8, DEFAULT_UART

	li		$8, 0x74	/* t */
	sw		$8, DEFAULT_UART

	li		$8, 0x20
	sw		$8, DEFAULT_UART

	li    $8, REG_HW_SEMAPHORE
get_hw_semaphore :
   # delay a while (reduce bus traffic)
   li    $10, 100
wait:
   subu  $10, 0x1
   bnez  $10, wait
   nop

   # check if HW semaphore is available
   lw    $9, 0($8)
   nop      /* 5181 need nop after lw */
   beq      $9, $0, get_hw_semaphore
   nop

	li		$17, 0xa00000e0
	li		$18, REG_HW_SEMAPHORE
	nop
	lw		$16, 0($17)
	nop
	bnez	$16, 1f
	sw		$0, ($18)
a_loop:
	b		a_loop
	nop
1:
	/* Print Ago */
	li		$8, 'A'	/* A */
	sw		$8, DEFAULT_UART
	
	li		$8, 0x67	/* g */
	sw		$8, DEFAULT_UART
	
	li		$8, 0x6F	/* o */
	sw		$8, DEFAULT_UART
	
	li		$8, 0x20
	sw		$8, DEFAULT_UART

	jalr	$16
	sw		$0, ($18)

	.set	reorder
	.end	a_entry
