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

#if 0
	/* get semaphore */
	li		$18, 0xb801a000			// semaphore address
get_semaphore:
	li      $17, 1000
delay1:	
	subu    $17, 1
	bnez    $17, delay1
	nop
	lw		$16, 0($18)
	nop
	beqz	$16, get_semaphore		// wait untill get semaphore
	#get semaphore now
#endif
	li      $17, 0x100
delay2:	
	subu    $17, 1
	bnez    $17, delay2
	nop
	li		$17, 1
	li		$18, 0xb801a000			// semaphore address
	sw		$17, ($18)				// lock semaphore by itself
	nop
lock:
	li      $17, 0x100
delay3:	
	subu    $17, 1
	bnez    $17, delay3
	nop
	lw		$16, 0($18)
	nop
	beqz	$16, lock				// wait untill get semaphore
	nop
	#get semaphore now
a1:
	li		$17, 0xa00000e0
	nop
	lw		$16, 0($17)
	nop
	bnez	$16, 1f
	nop
	b		a1						// 0xa00000e0 is null, polling again
	nop
1:
	jalr	$16

	.set	reorder
	.end	a_entry
