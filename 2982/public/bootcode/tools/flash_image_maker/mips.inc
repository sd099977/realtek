
#define zero	$0
#define z0	$0
#define v0	$2
#define v1	$3
#define a0	$4
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24
#define t9	$25
#define k0	$26	/* kernel private register 0 */
#define k1	$27	/* kernel private register 1 */
#define gp	$28	/* global data pointer */
#define sp 	$29	/* stack-pointer */
#define fp	$30	/* frame-pointer */
#define ra	$31	/* return address */
#define pc	$pc	/* pc, used on mips16 */

/*
#define f0	$f0
#define f1	$f1
#define f2	$f2
#define f3	$f3
#define f4	$f4
#define f5	$f5
#define f6	$f6
#define f7	$f7
#define f8	$f8
#define f9	$f9
#define f10	$f10
#define f11	$f11
#define f12	$f12
#define f13	$f13
#define f14	$f14
#define f15	$f15
#define f16	$f16
#define f17	$f17
#define f18	$f18
#define f19	$f19
#define f20	$f20
#define f21	$f21
#define f22	$f22
#define f23	$f23
#define f24	$f24
#define f25	$f25
#define f26	$f26
#define f27	$f27
#define f28	$f28
#define f29	$f29
#define f30	$f30
#define f31	$f31
*/

/* Coprocessor 0 registers*/

#define	index		$0	// TLB entry index register
#define random		$1	// TLB random index register
#define	tlblo0		$2	// TLB even page entry register
#define	tlblo1		$3	// TLB odd page entry register
/*#define config		$3	// Configuration register (TX39 only)*/
#define	context		$4	// TLB context register
#define pagemask	$5	// TLB page size mask
#define	wired		$6	// TLB wired boundary
#define cachectrl	$7	// Cache control
#define badvr		$8	// Bad virtual address
/*#define count		$9	// Timer cycle count register*/
#define	tlbhi		$10	// TLB virtual address match register
/*#define compare		$11	// Timer compare register*/
#define status		$12	// Status register	
#define cause		$13	// Exception cause
#define	epc		$14	// Exception pc value
#define prid		$15	// processor ID
/*#define config0		$16	// Config register 0*/

#define CP0_CCTL		$20 //add for magellan lx5281


#define FUNC_START(name)	\
        .type name,@function;	\
        .globl name;		\
        .ent   name;		\
name:

#define FUNC_END(name)		\
name##_end:			\
        .end name		


/*  We use ssnop instead of nop operations in order to handle 
 *  superscalar CPUs.
 *  The "sll zero,zero,1" notation is compiler backwards compatible.
 */
#define SSNOP   sll zero,zero,1
#define NOPS	SSNOP; SSNOP; SSNOP; SSNOP

#define MTC0(src, dst)       \
		nop;	     \
	        mtc0 src,dst;\
		NOPS

#define DMTC0(src, dst)       \
		nop;	      \
	        dmtc0 src,dst;\
		NOPS

#define MFC0(dst, src)       \
	  	mfc0 dst,src

#define DMFC0(dst, src)       \
	  	dmfc0 dst,src

#define MFC0_SEL_OPCODE(dst, src, sel)\
	  	.word (0x40000000 | ((dst)<<16) | ((src)<<11) | (sel))

#define MTC0_SEL_OPCODE(src, dst, sel)\
	  	.##word (0x40800000 | ((src)<<16) | ((dst)<<11) | (sel));\
		NOPS


/* cache operations */

#define CACHE_OP( code, type )			( ((code) << 2) | (type) )

#define ICACHE_INDEX_INVALIDATE			CACHE_OP(0x0, 0)
#define ICACHE_INDEX_LOAD_TAG			CACHE_OP(0x1, 0)
#define ICACHE_INDEX_STORE_TAG			CACHE_OP(0x2, 0)
#define DCACHE_INDEX_WRITEBACK_INVALIDATE	CACHE_OP(0x0, 1)
#define DCACHE_INDEX_LOAD_TAG			CACHE_OP(0x1, 1)
#define DCACHE_INDEX_STORE_TAG			CACHE_OP(0x2, 1)
#define SCACHE_INDEX_STORE_TAG			CACHE_OP(0x2, 3)

#define ICACHE_ADDR_HIT_INVALIDATE		CACHE_OP(0x4, 0)
#define ICACHE_ADDR_FILL			CACHE_OP(0x5, 0)
#define ICACHE_ADDR_FETCH_LOCK			CACHE_OP(0x7, 0)
#define DCACHE_ADDR_HIT_INVALIDATE		CACHE_OP(0x4, 1)
#define DCACHE_ADDR_HIT_WRITEBACK_INVALIDATE	CACHE_OP(0x5, 1)
#define DCACHE_ADDR_HIT_WRITEBACK		CACHE_OP(0x6, 1)
#define DCACHE_ADDR_FETCH_LOCK			CACHE_OP(0x7, 1)

#define SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE	CACHE_OP(0x5, 3)

/*  Workaround for bug in early revisions of MIPS 4K family of 
 *  processors. Only relevant in early engineering samples of test
 *  chips (RTL revision <= 3.0).
 *
 *  The bug is described in :
 *
 *  MIPS32 4K(tm) Processor Core Family RTL Errata Sheet
 *  MIPS Document No: MD00003
 *
 *  The bug is identified as : C16
 */
#ifndef SET_MIPS0
#define SET_MIPS3()
#define SET_MIPS0()
#define SET_PUSH()
#define SET_POP()
#endif
#define ICACHE_INVALIDATE_WORKAROUND(reg) \
SET_PUSH();				  \
SET_MIPS0();				  \
	la     reg, 999f;		  \
SET_POP();				  \
	cache  ICACHE_ADDR_FILL, 0(reg);  \
	sync;				  \
	nop; nop; nop; nop;		  \
999:

#define ICACHE_INDEX_INVALIDATE_OP(index,scratch)		  \
	    ICACHE_INVALIDATE_WORKAROUND(scratch);		  \
	    cache ICACHE_INDEX_INVALIDATE, 0(index)

#define ICACHE_ADDR_INVALIDATE_OP(addr,scratch)			  \
	    ICACHE_INVALIDATE_WORKAROUND(scratch);		  \
	    cache ICACHE_ADDR_HIT_INVALIDATE, 0(addr)

#define SCACHE_ADDR_HIT_WB_INVALIDATE_OP(reg)			  \
	    cache   SCACHE_ADDR_HIT_WRITEBACK_INVALIDATE, 0(reg);


/*
** LEAF: start of a leaf routine define
*/
#define	LEAF(proc)	\
	.globl	proc;	\
	.ent	proc;	\
proc:;				\
	.frame	sp,0,ra

/*
** END: end of the procedure define
*/
#define	END(proc) .end	proc



#define KUSEG_MSK		  0x80000000
#define KSEG_MSK		  0xE0000000
#define KUSEGBASE		  0x00000000
#define KSEG0BASE		  0x80000000
#define KSEG1BASE		  0xA0000000
#define KSSEGBASE		  0xC0000000
#define KSEG3BASE		  0xE0000000
