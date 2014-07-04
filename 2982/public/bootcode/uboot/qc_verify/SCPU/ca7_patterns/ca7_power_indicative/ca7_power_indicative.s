;-------------------------------------------------------------------------------
; The confidential and proprietary information contained in this file may
; only be used by a person authorised under and to the extent permitted
; by a subsisting licensing agreement from ARM Limited.
;
;            (C) COPYRIGHT 2009-2012  ARM Limited.
;                ALL RIGHTS RESERVED
;
; This entire notice must be reproduced on all copies of this file
; and copies of this file may only be made by a person if such person is
; permitted to do so under the terms of a subsisting license agreement
; from ARM Limited.
;
;      SVN Information
;
;      Checked In          : $Date: 2010-04-16 20:38:08 +0100 (Fri, 16 Apr 2010) $
;
;      Revision            : $Revision: 136759 $
;
;      Release Information : CORTEX-A7-r0p4-00rel0
;
;-------------------------------------------------------------------------------

;-----------------------------------------------------------------------------
; Abstract :
;
; This module  initializes stack pointers and interrupts for each mode, and
; and calls main()).
;-----------------------------------------------------------------------------
       ; Include macros
                GET     macros.hs
                GET     configuration
                
                AREA  Init, CODE, READONLY
                PRESERVE8

;               IMPORT  __use_no_semihosting_swi

; - Standard definitions of mode bits and interrupt (I&F) flags in PSRs
Mode_USR        EQU   0x10
Mode_FIQ        EQU   0x11
Mode_IRQ        EQU   0x12
Mode_SVC        EQU   0x13
Mode_MON        EQU   0x16
Mode_ABT        EQU   0x17
Mode_UNDEF      EQU   0x1B
Mode_SYS        EQU   0x1F
I_Bit           EQU   0x80 ; when I bit is set, IRQ is disabled
F_Bit           EQU   0x40 ; when F bit is set, FIQ is disabled

;for our testbed
TST_FAIL_ADDR   EQU     0x13000288  ;?????
TST_PASS_ADDR   EQU     0x1300028C  ;?????

                ENTRY

                EXPORT Vectors

Vectors
                B       Reset_Handler
                B       Undefined_Handler
                B       SWI_Handler
                B       Prefetch_Handler
                B       Abort_Handler
                NOP     ;Reserved vector
                B       IRQ_Handler
                B       FIQ_Handler

; ------------------------------------------------------------
; Handlers for unused exceptions
; ------------------------------------------------------------

Undefined_Handler
                MESSAGE "Unexpected undefined instruction \n"
                TEST_FAIL
SWI_Handler
                MESSAGE "Unexpected SWI call \n"
                TEST_FAIL
Prefetch_Handler
                MESSAGE "Unexpected prefetch abort \n"
                TEST_FAIL
Abort_Handler
                MESSAGE "Unexpected data abort \n"
                TEST_FAIL
IRQ_Handler
                MESSAGE "Unexpected IRQ \n"
                TEST_FAIL
FIQ_Handler
                MESSAGE "Unexpected FIQ \n"
                TEST_FAIL

; ------------------------------------------------------------
; Reset Handler
; ------------------------------------------------------------

;                IMPORT ||Image$$FIQ_STACK$$ZI$$Limit||

zero_mem        % 56
                
                
Reset_Handler PROC

; ------------------------------------------------------------
; Clear registers
; ------------------------------------------------------------
                LDR     r0, =zero_mem
                LDM     r0, {r1-r14}

                CPS     #Mode_FIQ
                LDM     r0, {r8-r14}

                CPS     #Mode_SYS
                LDM     r0, {r13-r14}

                CPS     #Mode_IRQ
                LDM     r0, {r13-r14}

                CPS     #Mode_ABT
                LDM     r0, {r13-r14}
           
                CPS     #Mode_UNDEF
                LDM     r0, {r13-r14}
   
                CPS     #Mode_MON
                LDM     r0, {r13-r14}

; ------------------------------------------------------------
; Setup stacks
;-------------------------------------------------------------
       
                MRC     p15, 0, r0, c0, c0, 5        ; read Multiprocessor Affinity Register MPIDR

       ; Check for uniprocessor variant
                TST     r0, #1:SHL:30
                BNE     start

       ; Check for CPU 0 
                TST     r0, #3
                BNE     wfi_loop
                
                B       start                

wfi_loop
                WFI
                B       wfi_loop

start
                ;Core0 powers up others
                POWER_UP_CORES

       ; Set the same address for all the cores, the MMU ensures that they
       ; use physically different locations
       ; Application stack (and heap) set up by C library.
                MSR     CPSR_c, #Mode_SYS:OR:I_Bit:OR:F_Bit    ; No interrupts

       ; Set up stack pointer
                LDR     SP, =stack

       ; Initialise memory locations
                MOV     r1,#0
                MOV     r2,#0
                MOV     r3,#0
                MOV     r4,#0
                MOV     r5,#0
                MOV     r6,#0
                MOV     r7,#0
                MOV     r8,#0		
       ; Initialise Stack heap
		MOV     r9,#0       
                LDR     r0,=0x00100000
initialize_loop
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
		ADD	r9, r9, #1
		CMP	r9, #0x95
		BNE	initialize_loop

                LDR     r0,=0x001fc000
		MOV     r9,#0
initialize_loop_2
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
		ADD	r9, r9, #1
		CMP	r9, #0x5
		BNE	initialize_loop_2
					
                LDR     r0,=0x001fdf00
		MOV     r9,#0
initialize_loop_3
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
		ADD	r9, r9, #1
		CMP	r9, #0x8
		BNE	initialize_loop_3

		LDR     r0,=0x00014028
		STMIA   r0,{r1-r5}
		
; ------------------------------------------------------------
; if FPU is present, enable it
; ------------------------------------------------------------
                FPU_PRESENT r0
                CMP     r0,#1
                BNE     skip_fpu_neon
                ENABLE_FPU 

; ------------------------------------------------------------
; if NEON is present, enable it
; ------------------------------------------------------------
                NEON_PRESENT r0
                CMP     r0, #1
                BNE     skip_fpu_neon
                MOV     r0, #1<<30
                MCR     p10, #7, r0, c8, c0, 0       ; enable NEON by writing FPEXC
                MOV     r0, #0          
                LDC     p11, c0, [r0], {32}          ; init registers d0-d15
                LDCL    p11, c0, [r0], {32}          ; init registers d16-d31
                B       skip_fpu_neon
                
skip_fpu_neon
; ------------------------------------------------------------
; Initialize cp15 registers
; ------------------------------------------------------------
                MOV     r0, #0x0
                MCR     p15,0,r0,c5,c0,0                       ;DFSR
                MCR     p15,0,r0,c5,c0,1                       ;IFSR
                MCR     p15,0,r0,c6,c0,0                       ;DFAR
                MCR     p15,0,r0,c6,c0,2                       ;IFAR
                MCR     p15,0,r0,c9,c13,0                      ;PMCCNTR - PMU cycle Count Register
                MCR     p15,0,r0,c9,c13,2                      ;PMXEVCTR - PMU Event Count Registers

; ------------------------------------------------------------
; Disable Caches & Table Type
;-------------------------------------------------------------
                MESSAGE "Disable caches \n"
                DISABLE_CACHES

; ------------------------------------------------------------
; Invalidate caches and TLB if required
; ------------------------------------------------------------

       ; Check the status of L1RSTDISABLE and only
       ; run the invalidate sequence if it has not been
       ; carried at at reset in hardware.

       ; Test only run on CPU0
                ;LDR     r6,=TBVAL_CFGL1
                ;LDR     r0, [r6]
                ;TST     r0, #1:SHL:16
                ;BEQ     skip_inval
        ;cs3_ctrl gives 1'b0 in ca7 local, just branch to skip_inval
                B     skip_inval
         
                MESSAGE "Invalidate caches \n"
                BL      invalidate_caches

       ; Invalidate TLB
                MCR     p15, 0, r0, c8, c7, 0                  ; TLBIALL - Invalidate entire Unified TLB
  
skip_inval
; ------------------------------------------------------------
; Set up Domain Access Control Reg
; ------------------------------------------------------------
       ; b00 - No Access (abort)
       ; b01 - Client (respect table entry)
       ; b10 - RESERVED
       ; b11 - Manager (ignore access permissions)
       ; Setting D0 to client, all others to No Access

                MOV     r0, #0x01
                MCR     p15, 0, r0, c3, c0, 0                  ; DACR - Domain Access Control Register
  
; ------------------------------------------------------------
; Set Table Base Control Register
; ------------------------------------------------------------
                MOV     r0,#0x0
                MCR     p15, 0, r0, c2, c0, 2
  
; ------------------------------------------------------------
; Page table modifications
; ------------------------------------------------------------
       ; Stored in memory is a set of page tables that flat-maps memory
       ; This image works by using the same VAs across the MP, but setting different PAs
       ; If not core 0, copy to a new location....

                MRC     p15, 0, r1, c0, c0, 5                  ; Read Multiprocessor Affinity Register
                AND     r1, r1, #0x03                          ; Mask off, leaving the CPU ID field


                CMP     r1, #0
                LDREQ   r0, =table_base0                       ; Location of master copy of TTB

; ------------------------------------------------------------
; Set location of level 1 page table
;-------------------------------------------------------------
                MCR     p15, 0, r0, c2, c0 ,0

; ------------------------------------------------------------
;  Create sections for translation table
;-------------------------------------------------------------
                TT_SECTION_WRITE  0x0, 0x0, WB | RW | EXE
                TT_SECTION_WRITE  0x100000, 0x100000, SHARED | WB | RW | EXE
                TT_SECTION_WRITE  TBVAL_SYSADDR, TBVAL_SYSADDR, SDEVICE | RW | NON_EXE

; ------------------------------------------------------------
;  Set S bit in Multiprocessor mode
;-------------------------------------------------------------          
                MRC     p15, 0, r0, c0, c0, 5        ; read Multiprocessor Affinity Register MPIDR
                UBFX    r1, r0, #30, #1              ; extract bit 30
                CMP     r1,#1                        ; if one then is uniprocessor configuration
                BEQ     enable_mmu
                MRC     p15, 0, r0, c1, c0, 1
                ORR     r0, r0, #1<<6
                MCR     p15, 0, r0, c1, c0, 1

; ------------------------------------------------------------
; Enable the MMU
;-------------------------------------------------------------
enable_mmu
       ; Set SCTLR bit 0 to enable MMU and to activate virtual address
       ; system
                MESSAGE "Enable MMU \n"
                ENABLE_MMU

; ------------------------------------------------------------
; Enable Caches
; ------------------------------------------------------------		

               ENABLE_CACHES
		
; ------------------------------------------------------------
; Branch to C lib code
; ------------------------------------------------------------
               IMPORT  __main
               B       __main                                 ; Assuming flat mapping for the boot code, so no leap of faith

               ENDP
                MRC     p15, 0, r0, c1, c0, 0       ; Read System Control Register configuration data
                ORR     r0, r0, #0x0004             ; Set C bit
                ORR     r0, r0, #0x1000             ; Set I bit
                MCR     p15, 0, r0, c1, c0, 0       ; Write System Control Register configuration data
  
; ------------------------------------------------------------
; Cache Maintenance
; ------------------------------------------------------------
                EXPORT invalidate_caches
invalidate_caches PROC

       ; Invalidate the I Cache
                MOV     r0, #0
                MCR     p15, 0, r0, c7, c5, 0                  ; ICIALLU - Invalidate entire I Cache, and flushes branch target cache

       ; Invalidate the D Cache
                INVALIDATE_DCACHE
                BX      lr
                ENDP
  
                EXPORT  get_core_id

       ; unsigned int get_core_id(void)
       ; Returns the CPU ID (0 to 3) of the CPU executed on
get_core_id     PROC
                MRC     p15, 0, r0, c0, c0, 5                  ; Read CPU ID register
                ANDS    r0, r0, #0x03                          ; Mask off, leaving the CPU ID field
                BX      lr
                ENDP
		
                EXPORT  test_finish

test_finish     PROC
       ; Note: does not support MPCore

; for our testbed, write pass addr will finish simulation
        LDR     r0,=TST_PASS_ADDR
        MOV     r1, #0xabcd
        STR     r1,[r0]

                TEST_FINISH
                ENDP
                

; ------------------------------------------------------------
; Pagetable0
; ------------------------------------------------------------

                AREA    TT0,DATA,READONLY, ALIGN=14

table_base0
                % 16384
                
;-------------------------------------------------------------
; Stack Data
;-------------------------------------------------------------
                AREA    |Stack DATA|, DATA, ALIGN=12

                % 256
stack
                % 256

;-------------------------------------------------------------
; BST instructions
;-------------------------------------------------------------
                
                AREA    |~BST CODE|, CODE, ALIGN=12

                BST_START
                BST "EXIT"
                BST "PRINTF ERROR: Should not be reached"
                BST_END
  
                END

; ------------------------------------------------------------
; End of ca7_power_indicative.s
; ------------------------------------------------------------
