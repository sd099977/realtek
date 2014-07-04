
/************************************************************************
 *
 *  cpu.S
 *
 *  cpu functions
 *
 * ######################################################################
 *
 * mips_start_of_legal_notice
 * 
 * Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
 *
 *
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 *
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies"). Any copying, reproducing, modifying or use of this code
 * (in whole or in part) that is not expressly permitted in writing by MIPS
 * Technologies or an authorized third party is strictly prohibited. At a
 * minimum, this code is protected under unfair competition and copyright
 * laws. Violations thereof may result in criminal penalties and fines.
 *
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise. MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of any
 * error or omission in such code. Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the implied
 * warranties of merchantability or fitness for a particular purpose, are
 * excluded. Except as expressly provided in any written license agreement
 * from MIPS Technologies or an authorized third party, the furnishing of
 * this code does not give recipient any license to any intellectual
 * property rights, including any patent rights, that cover this code.
 *
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 *
 * This code constitutes one or more of the following: commercial computer
 * software, commercial computer software documentation or other commercial
 * items. If the user of this code, or any related documentation of any
 * kind, including related technical data or manuals, is an agency,
 * department, or other entity of the United States government
 * ("Government"), the use, duplication, reproduction, release,
 * modification, disclosure, or transfer of this code, or any related
 * documentation of any kind, is restricted in accordance with Federal
 * Acquisition Regulation 12.212 for civilian agencies and Defense Federal
 * Acquisition Regulation Supplement 227.7202 for military agencies. The use
 * of this code by the Government is further restricted in accordance with
 * the terms of the license agreement(s) and/or applicable contract terms
 * and conditions covering this code from MIPS Technologies or an authorized
 * third party.
 *
 * 
 * mips_end_of_legal_notice
 * 
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/

/*
#include <sysdefs.h>
#include <mips.h>
*/
#include "ArchDefs.h"
#include "mips.inc"
/* #include "eregdef.h" */

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/


	.set noreorder


	
			
/************************************************************************
 *
 *                          sys_icache_invalidate_index
 *  Description :
 *  -------------
 *
 *  Invalidate I cache line containing specified index
 *
 *  a0 holds the index
 *	
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_icache_invalidate_index)

SET_MIPS3()
	ICACHE_INDEX_INVALIDATE_OP(a0,a1)
SET_MIPS0()

	jr	ra
	nop
	
END(sys_icache_invalidate_index)


/************************************************************************
 *
 *                          sys_icache_invalidate_addr
 *  Note
 *  ------
 *  This function is called from user2yamon() in application context,
 *  possibly in 64 bit mode and with invalid gp.
 *  if a1 == 0, sys_icache_invalidate_addr modifies only t1.
 *
 *  Description :
 *  -------------
 *  Invalidate I cache line containing specified address.
 *
 *  We bypass the cache operations if CPU is running uncached.
 *  (We assume Config.k0 == K_CacheAttrU is the
 *  only uncached mode used).
 *	
 *  a0 holds the address
 *  a1 != 0 => flush pipeline after the invalidation
 *
 *  Address MUST be KSEG0/KSEG1
 *	
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF(sys_icache_invalidate_addr)

	MFC0( t1, C0_Config )
	#mfc0  $9, C0_Config
	andi  t1, M_ConfigK0
	xori  t1, K_CacheAttrU << S_ConfigK0
	beq   t1, zero, 2f
	nop
	
	la	t1, sys_l2cache_enabled
	lb	t1, 0(t1)
	beq	t1, zero, 1f
	nop

SET_MIPS3()
	SCACHE_ADDR_HIT_WB_INVALIDATE_OP(a0)
	sync
1:		
	ICACHE_ADDR_INVALIDATE_OP(a0,t1)
SET_MIPS0()
2:
	bne	a1, zero, sys_flush_pipeline
	nop
	jr      ra
	nop	

END(sys_icache_invalidate_addr)


/************************************************************************
 *
 *                          sys_flush_pipeline
 *  Description :
 *  -------------
 *
 *  Flush pipeline
 *
 *  a0 holds the index
 *	
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_flush_pipeline)
#if 0
	MFC0(	t0, C0_Status )
	
	/* Set STATUS in a well defined state so that we can perform
	 * a controlled eret (one without modifying shadow registers
	 * in case of a MIPS32/MIPS64 release 2 CPU).
	 *
	 * Note that we may end up here due a user application calling
	 * e.g. SYSCON through the application interface. So, STATUS
	 * is not necessarily in a well known state at this point.
	 *
	 * We need to make sure STATUS has the following settings :
	 *
	 * ERL = 0  (so EPC is used rather than ErrorEPC)
	 * BEV = 1  (so shadowsets are not shifted)
	 * IE  = 0  (so interrupts are disabled)
	 * KSU = 00 (so that we end up in kernel mode after eret)
	 */


	/* First set KSU=00, IE=0 */
	ori	t1, t0, (M_StatusKSU | M_StatusIE)
	xori	t1,     (M_StatusKSU | M_StatusIE)
	MTC0(	t1, C0_Status )
	/* Now set BEV */	
	li	t2, M_StatusBEV
	or	t1, t2
	MTC0(	t1, C0_Status )
	/* Finally, clear ERL */
	ori	t1, M_StatusERL
	xori	t1, M_StatusERL
	MTC0(	t1, C0_Status )

	/* 32 bit CPU */
	MFC0(   t1, C0_EPC ) /* Store EPC */

	/* Now setup EPC and perform eret */	
	la	t2, after_eret32
	MTC0(	t2, C0_EPC )

SET_MIPS3()
	eret
SET_MIPS0()

after_eret32 :
	MTC0(   t1, C0_EPC ) /* Restore EPC */
	b	2f
	nop
	
	
2:	
	/* Restore STATUS and return */
	MTC0(	t0, C0_Status )
#endif
	jr	ra
	nop

END(sys_flush_pipeline)
	
	
/************************************************************************
 *
 *                          sys_dcache_flush_index
 *  Description :
 *  -------------
 *
 *  Flush D cache line containing specified index
 *
 *  a0 holds the index
 *	
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_dcache_flush_index)
#modify by Angus
#if 0
SET_MIPS3()
	cache	DCACHE_INDEX_WRITEBACK_INVALIDATE, 0(a0)
SET_MIPS0()
#endif
	mtc0    zero, CP0_CCTL
	nop
 
	li      t1, 0x00000003                  #//Invalidate I-Cache and D-Cache
	mtc0    t1, CP0_CCTL
	nop
 
	mtc0    zero, CP0_CCTL                  #//Enable I-Cache and D-Cache
	nop

	sync
	jr ra
	nop	

END(sys_dcache_flush_index)

/************************************************************************
 *
 *                          sys_dcache_hit_writeback_addr
 *  Description :
 *  -------------
 *
 *  Flush D cache line containing specified address
 *
 *  a0 holds the index
 *	
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_dcache_hit_writeback_addr)

SET_MIPS3()
	cache	DCACHE_ADDR_HIT_WRITEBACK, 0(a0)
SET_MIPS0()
	sync
	jr ra
	nop	

END(sys_dcache_hit_writeback_addr)


/************************************************************************
 *
 *                          sys_dcache_flush_addr
 *  Note
 *  ------
 *  This function is called from user2yamon() in application context,
 *  possibly in 64 bit mode and with invalid gp.
 *  sys_dcache_flush_addr modifies only t1.
 *
 *  Description :
 *  -------------
 *  Flush D cache line containing specified address.
 *
 *  We bypass the cache operations if CPU is running uncached.
 *  (We assume Config.k0 == K_CacheAttrU is the
 *  only uncached mode used).
 *
 *  a0 holds the address 
 *
 *  Address MUST be KSEG0/KSEG1
 *	
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF(sys_dcache_flush_addr)

	MFC0( t1, C0_Config )
	andi  t1, M_ConfigK0
	xori  t1, K_CacheAttrU << S_ConfigK0
	beq   t1, zero, 2f
	nop
	
	la	t1, sys_l2cache_enabled
	lb	t1, 0(t1)
	beq	t1, zero, 1f
	nop

	/*  This secondary cache operation will also flush $D,
	 *  so we don't need to flush $D.
	 */
SET_MIPS3()
	cache	DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, 0(a0)
	sync
	SCACHE_ADDR_HIT_WB_INVALIDATE_OP(a0)
SET_MIPS0()
	b	2f
	nop
1:		
SET_MIPS3()
	cache	DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, 0(a0)
SET_MIPS0()
2:
	sync
	jr	ra
	lb	zero, 0(a0)

END(sys_dcache_flush_addr)

/************************************************************************
 *
 *                          sys_dcache_hit_writeback_invalidate_addr
 *  Note
 *  ------
 *  This function is called from user2yamon() in application context,
 *  possibly in 64 bit mode and with invalid gp.
 *  sys_dcache_invalidate_addr modifies only t1.
 *
 *  Description :
 *  -------------
 *  Hit Writeback Invalidate D cache line containing specified address.
 *
 *  We bypass the cache operations if CPU is running uncached.
 *  (We assume Config.k0 == K_CacheAttrU is the
 *  only uncached mode used).
 *
 *  a0 holds the address 
 *
 *  Address MUST be KSEG0/KSEG1
 *	
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF(sys_dcache_hit_writeback_invalidate_addr)

	MFC0( t1, C0_Config )
	andi  t1, M_ConfigK0
	xori  t1, K_CacheAttrU << S_ConfigK0
	beq   t1, zero, 2f
	nop
	
	la	t1, sys_l2cache_enabled
	lb	t1, 0(t1)
	beq	t1, zero, 1f
	nop

	/*  This secondary cache operation will also flush $D,
	 *  so we don't need to flush $D.
	 */
SET_MIPS3()
	cache	DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, 0(a0)
	sync
	SCACHE_ADDR_HIT_WB_INVALIDATE_OP(a0)
SET_MIPS0()
	b	2f
	nop
1:		
SET_MIPS3()
	cache	DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, 0(a0)
SET_MIPS0()
2:
	sync
	jr	ra
	lb	zero, 0(a0)

END(sys_dcache_hit_writeback_invalidate_addr)


/************************************************************************
 *
 *                          sys_scache_flush_index
 *  Description :
 *  -------------
 *
 *  Flush L2 cache line containing specified index
 *
 *  a0 holds the index
 *
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF( sys_scache_flush_index )

SET_MIPS3()
	SCACHE_ADDR_HIT_WB_INVALIDATE_OP(a0)
SET_MIPS0()
	sync
	jr ra
	nop	

END( sys_scache_flush_index )


/************************************************************************
 *
 *                          sys_enable_int
 *  Description :
 *  -------------
 *
 *  Enable interrupt: set IE in CP0-status.
 *  
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_enable_int)

    MFC0(   v0, C0_Status)   
    or      v0, M_StatusIE
    MTC0(   v0, C0_Status)
    j       ra
    nop

END(sys_enable_int)


/************************************************************************
 *
 *                          sys_disable_int
 *  Description :
 *  -------------
 *
 *  UINT32 sys_disable_int( void )
 *
 *  Disable interrupt: clear IE in CP0-status.
 *  
 *  Return values :
 *  ---------------
 *
 *  Old IE bit
 *
 ************************************************************************/
LEAF(sys_disable_int)

    MFC0(   v0, C0_Status)
    li	    t0, ~M_StatusIE
    nop
    and     v1, v0, t0
    MTC0(   v1, C0_Status)
    li	    t0, M_StatusIE
    j       ra
    and	    v0, t0

END(sys_disable_int)


/************************************************************************
 *
 *                          sys_enable_int_mask
 *  Description :
 *  -------------
 *
 *  Enable specific interrupt: set IM[x] bit in CP0-status.
 *  
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_enable_int_mask)

    MFC0(   v0, C0_Status)
    li	    t0, 1
    addiu   a0, S_StatusIM
    sllv    t0, t0, a0
    or	    v0, t0
    MTC0(   v0, C0_Status)
    j       ra
    nop

END(sys_enable_int_mask)


/************************************************************************
 *
 *                          sys_disable_int_mask
 *  Description :
 *  -------------
 *
 *  Disable specific interrupt: set IM[x] bit in CP0-status.
 *  
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF(sys_disable_int_mask)

    MFC0(   v0, C0_Status)
    li	    t0, 1
    addiu   a0, S_StatusIM
    sllv    t0, t0, a0
    li	    t1, 0xffffffff
    xor	    t0, t1
    and	    v0, t0
    MTC0(   v0, C0_Status)
    j       ra
    nop

END(sys_disable_int_mask)

	

/************************************************************************
 *
 *                          sys_sync
 *  Description :
 *  -------------
 *
 *  Issue "sync" instruction
 *
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF( sys_sync )

        sync
	jr	ra
	nop

END( sys_sync )


/************************************************************************
 *
 *                          sys_fpu_enable
 *  Description :
 *  -------------
 *
 *  Enable FPU
 *
 ************************************************************************/
LEAF( sys_fpu_enable )
	
	/* Enable FPU */
	MFC0(   t0, C0_Status )
	li	t1, M_StatusCU1
	or	t0, t1
	MTC0(   t0, C0_Status )

	/* Set up FPU Control/Status register */
	li	t0, M_FCSRFS	/* Set FS (flush to zero) bit */
	ctc1	t0, C1_FCSR

	jr	ra
	nop
	
END( sys_fpu_enable )

	
		
/******* Functions for access to CP1 (FPU) registers ******/
	

/************************************************************************
 *
 *                          sys_cp1_read
 *  Description :
 *  -------------
 *  Read CP1 register
 *
 *  a0 holds register number
 *
 *  Return values :
 *  ---------------
 *  v0 = Value read
 *
 ************************************************************************/
LEAF( sys_cp1_read )

	addiu	sp, -8
	sw	ra, 0(sp)
	
	/* Be sure to make CU1 usable */
	MFC0(   t2, C0_Status)
	sw	t2, 4(sp)
	li	v0, M_StatusCU1
	or	v0, t2
	or	v0, M_StatusIE  /* and disable interrupts */
	xor	v0, M_StatusIE
	MTC0(   v0, C0_Status)

        /*  Calc specific CFC1 opcode :
	 *
	 *  CFC1 rt, fs
	 *
	 *  010001 00010 rt fs 00000000000
	 *
	 *  rt[4:0]  = v0 ($2) 
	 *  fs[4:0]  = Value of a0
         */
        li      t0, 0x44400000 | (0x2 << 16)
	sll 	a0, 11
	or  	t0, a0

	/* Store instruction */
	la  	a0, cfc1_location
	sw 	t0, 0(a0)

	/* Whenever an instruction has been stored to KSEG0, we must
	 * make sure the instruction has been flushed to physical memory
	 * and invalidate the corresponding I-Cache line.
	 */
	jal     sys_dcache_flush_addr		/* modifies t1 only */
	nop
	jal	sys_icache_invalidate_addr
	li	a1, 1				/* Flush pipeline */

cfc1_location :
	nop	/* Placeholder for CFC1 operation */

	/* CFC1 has now been performed, so restore cp0_status and return */
	lw	t2, 4(sp)
	MTC0(   t2, C0_Status)

	lw	ra, 0(sp)
	jr	ra
	addiu	sp, 8

END( sys_cp1_read )	


/************************************************************************
 *
 *                          sys_cp1_write
 *  Description :
 *  -------------
 *  Write CP1 register
 *
 *  a0 holds CP1 register number
 *  a1 holds value to be written
 *
 *  Return values :
 *  ---------------
 *  None
 *
 ************************************************************************/
LEAF( sys_cp1_write )

	addiu	sp, -12
	sw	ra, 0(sp)
	sw	a1, 4(sp)
	
	/* Be sure to make CU1 usable */
	MFC0(   t2, C0_Status)
	sw	t2, 8(sp)	
	li	v0, M_StatusCU1
	or	v0, t2
	or	v0, M_StatusIE  /* and disable interrupts */
	xor	v0, M_StatusIE
	MTC0(   v0, C0_Status)

        /*  Calc specific CTC1 opcode :
	 *
	 *  CTC1 rt, fs 
	 *
	 *  010001 00110 rt fs 00000000000
	 *
	 *  rt[4:0]  = a1 ($5)
	 *  fs[4:0]  = Value of a0
         */
	li      t0, 0x44c00000 | (0x5 << 16)
	sll 	a0, 11
	or  	t0, a0

	/* Store instruction */
	la  	a0, ctc1_location
	sw 	t0, 0(a0)
	
	/* Whenever an instruction has been stored to KSEG0, we must
	 * make sure the instruction has been flushed to physical memory
	 * and invalidate the corresponding I-Cache line.
	 */
	jal     sys_dcache_flush_addr		/* modifies t1 only */
	nop
	jal	sys_icache_invalidate_addr
	li	a1, 1				/* Flush pipeline */

	/* Restore a1 (value to be written) */
	lw	a1, 4(sp)
	
ctc1_location :
	nop	/* Placeholder for CTC1 operation */

	/* CTC1 has now been performed, so restore cp0_status and return */
	lw	t2, 8(sp)
	MTC0(   t2, C0_Status)

	lw	ra, 0(sp)
	jr	ra
	addiu	sp, 12

END( sys_cp1_write )	


/******* Functions for access to CP0 registers ******/

	
/************************************************************************
 *
 *                          sys_cp0_read32
 *  Description :
 *  -------------
 *
 *  Read 32 bit CP0 register
 *
 *  a0 holds register number
 *  a1 holds sel field
 *
 *  Return values :
 *  ---------------
 *
 *  v0 = Value read
 *
 ************************************************************************/
LEAF( sys_cp0_read32 )

	/* Look if a0,a1 happen to be C0_Status, sel0 */
	li	t0, R_C0_Status
	bne	a0, t0, 1f
	nop
	bne	a1, zero, 1f
	nop
	MFC0(   v0, C0_Status)
	jr	ra
	nop
	
1:
	/* Reserve space on stack and store ra, C0_Status */
	addiu	sp, -2*4
	sw	ra, 0(sp)

	/* Disable interrupts */
	MFC0(   t2, C0_Status)
	sw	t2, 4(sp)
	or	t2, M_StatusIE
	xor	t2, M_StatusIE
	MTC0(   t2, C0_Status)

        /*  Calc specific MFC0 opcode :
	 *
	 *  MFC0 rt, rd 
	 *
	 *  010000 00000 rt rd 00000000 sel
	 *
	 *  rt[4:0]  = v0 ($2) 
	 *  rd[4:0]  = Value of a0
	 *  sel[2:0] = Value of a1
         */
	
	li      t0, 0x40000000 | (0x2 << 16)
	or  	t0, a1   /* sel */
	sll 	a0, 11
	or  	t0, a0

	/* Store instruction */
	la  	a0, mfc0_location
	sw 	t0, 0(a0)

	/* Whenever an instruction has been stored to KSEG0, we must
	 * make sure the instruction has been flushed to physical memory
	 * and invalidate the corresponding I-Cache line.
	 */
	jal     sys_dcache_flush_addr
	nop
	jal	sys_icache_invalidate_addr
	li	a1, 1				/* Flush pipeline */	

mfc0_location :
	nop	/* Placeholder for MFC0 operation */

	/* MFC0 has now been performed, so restore cp0_status and return */
	lw	t2, 4(sp)
	MTC0(   t2, C0_Status)

	lw      ra, 0(sp)
	jr	ra
	addiu	sp, 2*4

END( sys_cp0_read32 )	

	

/************************************************************************
 *
 *                          sys_cp0_write32
 *  Description :
 *  -------------
 *
 *  Write 32 bit CP0 register
 *
 *  a0 holds register number
 *  a1 holds sel field
 *  a2 holds value to be written
 *
 *  Return values :
 *  ---------------
 *
 *  None
 *
 ************************************************************************/
LEAF( sys_cp0_write32 )

	/* Look if a0,a1 happen to be C0_Status, sel0 */
	li	t0, R_C0_Status
	bne	a0, t0, 1f
	nop
	bne	a1, zero, 1f
	nop
	MTC0(   a2, C0_Status)
	jr	ra
	nop
	
1:
	/* Reserve space on stack and store ra, a2, C0_Status */
	addiu	sp, -3*4
	sw	ra, 0(sp)
	sw	a2, 4(sp)	

	/* Disable interrupts */
	MFC0(   t2, C0_Status)
	sw	t2, 8(sp)
	or	t2, M_StatusIE
	xor	t2, M_StatusIE
	MTC0(   t2, C0_Status)

        /*  Calc specific MTC0 opcode :
	 *
	 *  MTC0 rt, rd 
	 *
	 *  010000 00100 rt rd 00000000 sel
	 *
	 *  rt[4:0]  = a2 ($6)
	 *  rd[4:0]  = Value of a0
	 *  sel[2:0] = Value of a1
         */
	
	li      t0, 0x40800000 | (0x6 << 16)
	or  	t0, a1   /* sel */
	sll 	a0, 11
	or  	t0, a0

	/* Store instruction */
	la  	a0, mtc0_location
	sw 	t0, 0(a0)

	/* Whenever an instruction has been stored to KSEG0, we must
	 * make sure the instruction has been flushed to physical memory
	 * and invalidate the corresponding I-Cache line.
	 */
	jal     sys_dcache_flush_addr
	nop
	jal	sys_icache_invalidate_addr
	li	a1, 1				/* Flush pipeline */

	/* Restore a2 (value to be written) */
	lw	a2, 4(sp)		

mtc0_location :
	nop	/* Placeholder for MTC0 operation */

	/* MTC0 has now been performed, so restore cp0_status and return */
	lw	t2, 8(sp)
	MTC0(   t2, C0_Status)

	lw      ra, 0(sp)
	jr	ra
	addiu	sp, 3*4

END( sys_cp0_write32 )	



/************************************************************************
 *
 *                          sys_determine_dcache_linesize_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine DCACHE linesize
 *
 *  input : none
 *	
 *  Return values :
 *  ---------------
 *  v0 = DCACHE linesize in bytes
 *
 ************************************************************************/
LEAF(sys_determine_dcache_linesize_flash)	
	
	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

#define config1	t9

	/* D-cache line size */
	li	t8, M_Config1DL
	and	t8, config1
	beq	t8, zero, dcache_linesize_zero
	li	t7, S_Config1DL
	srl	t8, t7
	li	t7, 0x2
	sll	v0, t7, t8

	jr	ra
	nop

	/* Not a MIPS32/64 processor */
	/* Unknown CPU */
dcache_linesize_zero:
	jr	ra
	move	v0, zero

END(sys_determine_dcache_linesize_flash)	


/************************************************************************
 *
 *                          sys_determine_dcache_lines_flash
 *  Note :
 *  ------
 *  This routine is called also from syscon.c
 *  and must obey c calling conventions - and cannot use k0/k1
 *
 *  Description :
 *  -------------
 *  Determine number of DCACHE lines
 *
 *  input : none
 *	
 *  Return values :
 *  ---------------
 *  v0 = number of DCACHE lines
 *
 ************************************************************************/
LEAF(sys_determine_dcache_lines_flash)	

	/* Read CONFIG1 register, which holds implementation data */
	MFC0_SEL_OPCODE( R_t9, R_C0_Config1, R_C0_SelConfig1 )

#define config1	t9

	/* D-cache lines
	 * Calculated as associativity * sets per way
	 */
	li	t8, M_Config1DA
	and	t8, config1
	li	t7, S_Config1DA
	srl	t8, t7
	addiu	t8,1				/* t8 = associativity	*/

	li	t7, M_Config1DS
	and	t7, config1
	li	t9, S_Config1DS
	srl	t7, t9
	li	t9, 0x40
	sll	t7, t9, t7			/* t7 = sets per way	*/

	multu	t8, t7
	mflo    v0

	jr	ra
	nop

END(sys_determine_dcache_lines_flash)


/************************************************************************
 *
 *                          sys_uncached
 *  Description :
 *  -------------
 *  Get Kseg0 cache coherrency attribute
 *
 *  input : none
 *	
 *  Return values :
 *  ---------------
 *  v0 = 1 if uncached
 *
 ************************************************************************/
LEAF(sys_uncached)
	MFC0( a0, C0_Config )
	li	a1, M_ConfigK0
	and	a0, a1
	li	a1, K_CacheAttrU
	bne	a0, a1, 1f		# branch if NOT uncached
	move	v0, zero

	li	v0, 0x1	
1:
	jr	ra
	nop
END(sys_uncached)
