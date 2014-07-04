
.text
.global start2

#define LEN_USR_STACK 0
#define LEN_ABT_STACK 0
#define LEN_UND_STACK 0
#define LEN_SYS_STACK 0
#define LEN_IRQ_STACK 0
#define LEN_FIQ_STACK 0
#define LEN_SVC_STACK 64

#define OFFSET_USR_STACK 	(0)
#define OFFSET_SVC_STACK 	(OFFSET_USR_STACK + LEN_USR_STACK)
#define OFFSET_FIQ_STACK 	(OFFSET_SVC_STACK + LEN_SVC_STACK)
#define OFFSET_IRQ_STACK 	(OFFSET_FIQ_STACK + LEN_FIQ_STACK)
#define OFFSET_ABT_STACK 	(OFFSET_IRQ_STACK + LEN_IRQ_STACK)
#define OFFSET_UND_STACK 	(OFFSET_ABT_STACK + LEN_ABT_STACK)
#define OFFSET_SYS_STACK 	(OFFSET_UND_STACK + LEN_UND_STACK)

#define STACK_BASE			0x00020000
#define STACK_UPPER_BOUND	(STACK_BASE-LEN_SVC_STACK-LEN_SVC_STACK)
#define STACK_SIZE			(LEN_SVC_STACK+LEN_SVC_STACK)
#define MAGIC_TAG1   		0x1801a610
#define MAGIC_TAG2   		0x1801a614
#define MAGIC_TAG3   		0x1801a618
#define JUMP_ADDRESS			0x00020000

#define IS_298X_FPGA

CPU0_MAGIC_TAG:
	.word	0xdeadbeef
CPU1_MAGIC_TAG:
	.word	0xdeadbeef

start2:
@ -- clear the content of magic tag
     LDR  r1 , =0x00000000
     LDR  r0 , =MAGIC_TAG1
     STR  r1 , [r0]
	  LDR  r0 , =MAGIC_TAG2
     STR  r1 , [r0]
     LDR  r0 , =MAGIC_TAG2
     STR  r1 , [r0]

#if 0 // simulate 2nd CPU
     B     run_secondary
#endif

     MRC   p15, 0, r0, c0, c0, 5
     AND   r0, r0, #0x3
     CMP   r0, #1
     BEQ   run_secondary

	  CMP   r0, #2
	  BEQ	  run_third

	  CMP   r0, #3
	  BEQ   run_fourth

@ -- set default stack of super visor mdoe
@ -- also update line 124
     LDR  r0, =STACK_BASE
     MOV  SP, r0

@ -- NOP
     MOV  r0 , #0
     MOV  r0 , #0
     MOV  r0 , #0

@ -- Clear RAM
@ -- r0  start address
@ -- r1  zero
@ -- r2  end address
     LDR  r0 , =STACK_UPPER_BOUND
     MOV  r1 , #0
     ADD  r2 , r0 , #(STACK_SIZE)
INIT_SRAM:
     CMP  r0 , r2
     STRLO r1 , [r0]
     ADDLO r0 , r0 , #4
     BLO  INIT_SRAM

@ -- initial cpu register ( heap, stack... )
@ -- set stack base address
     LDR     r0, =STACK_BASE

     MSR     CPSR_c, #0xD3 ; #MODE_SVC:OR:DIS_IRQ:OR:DIS_FIRQ
     SUB     r3, r0, #OFFSET_SVC_STACK
     MOV     SP, r3

     MSR     CPSR_c, #0xD1 ; #MODE_FIQ:OR:DIS_IRQ:OR:DIS_FIRQ
     SUB     r3, r0, #OFFSET_FIQ_STACK
     MOV     SP, r3

     MSR     CPSR_c, #0xD2 ; #MODE_IRQ:OR:DIS_IRQ:OR:DIS_FIRQ
     SUB     r3, r0, #OFFSET_IRQ_STACK
     MOV     SP, r3

@ -- MSR     CPSR_c, #0xD7 ; #MODE_ABT:OR:DIS_IRQ:OR:DIS_FIRQ
@ -- SUB     r3, r0, #OFFSET_ABT_STACK
@ -- MOV     SP, r3

@ -- MSR     CPSR_c, #0xDB ; #MODE_UND:OR:DIS_IRQ:OR:DIS_FIRQ
@ -- SUB     r3, r0, #OFFSET_UND_STACK
@ -- MOV     SP, r3

     MSR     CPSR_c, #0xDF ; #MODE_SYS:OR:DIS_IRQ:OR:DIS_FIRQ
     SUB     r3, r0, #OFFSET_SYS_STACK
     MOV     SP, r3

@ -- please not set CPSR_c to user mode
@ -- MSR     CPSR_c, #0xD0 ; #MODE_USR:OR:DIS_IRQ:OR:DIS_FIRQ
@ -- SUB     r3, r0, #OFFSET_USR_STACK
@ -- MOV     SP, r3

@ -- back to supervisor mode
     MSR     CPSR_c, #0xD3 ; #MODE_SVC:OR:DIS_IRQ:OR:DIS_FIRQ

@ -- Jump to bootcode
check_cpu0_tag:
     LDR     r0 , =0x0001F800
     LDR     r1, [r0]
     LDR     r2 , =0xdeadbeef
     CMP     r1, r2
     BNE     check_cpu0_tag

@ -- Jump to bootcode
     LDR     r0, =JUMP_ADDRESS
     MOV     PC, r0

run_secondary:
     MSR   CPSR_c, #0xD3 ; #MODE_SVC:OR:DIS_IRQ:OR:DIS_FIRQ
loop2:
	  WFE
     LDR   r0 , =MAGIC_TAG1
     LDR   r1, [r0]
     CMP   r1, #0
     BEQ   loop2
     @load adddress to run
     MOV   PC, r1

run_third:
     MSR   CPSR_c, #0xD3 ; #MODE_SVC:OR:DIS_IRQ:OR:DIS_FIRQ
loop3:
	  WFE
     LDR   r0 , =MAGIC_TAG2
     LDR   r1, [r0]
     CMP   r1, #0
     BEQ   loop3
     @load adddress to run
     MOV   PC, r1

run_fourth:
     MSR   CPSR_c, #0xD3 ; #MODE_SVC:OR:DIS_IRQ:OR:DIS_FIRQ
loop4:
	  WFE
     LDR   r0 , =MAGIC_TAG3
     LDR   r1, [r0]
     CMP   r1, #0
     BEQ   loop4
     @load adddress to run
     MOV   PC, r1

