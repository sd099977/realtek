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
;      Checked In          : $Date: 2007-07-04 19:16:27 +0100 (Wed, 04 Jul 2007) $
;
;      Revision            : $Revision: 60190 $
;
;      Release Information : CORTEX-A7-r0p4-00rel0
;
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
; Description:
;
; The purpose of the ca7_max_power test is to implement a setup and instruction
; stream that will draw more power than the Dhrystone benchmark. The test is
; configured to enable features likely to draw as much power as possible
; as follows:
;
; All caches are enabled
; Breakpoints and Watchpoints are enabled
; By enabling Breakpoints and Watchpoints, address comparisons will constantly
; be carried out, therefore consuming power.
;
; Invasive Debug is enabled
;
; Main Power Measurement Loop: power_loop
;
; The measurement should start from the fifth loop of CPU0 and either done
; for one loop or on multiple loops.
; Loops are identify by the instruction: SUBS r10,r10,#1
;
; The reason why loop 5 is a safe starting point is due to the fact that
; at that point everything will run from L1 and if more than one CPU is used
; they will also run from L1 at that time.
; 
; Prior to enter the loops all the present CPU will synchronize to each other
; The synchronisation mechanism relies on a  memory-mapped component able to
; trigger EVENTI when all CPUs present are in standby-WFI state.
;
;
; The main loop begins at the following instruction
;       SUBS r10, r10, #1 ;
;
; This instruction is used purely to decrement the number of remaining test
; iterations. 
;
;       LDR     r0,=0x00000000
;       LDR     r1,=0xfffffffd
;       LDR     r2,=0xfffffffc
;       LDR     r3,=0x00000006
;       LDR     r4,=0x00000000
;       LDR     r5,=0xfffffffd
;       LDR     r6,=0xfffffffc
;       LDR     r7,=0x00000006
;
; The main power-hungry instructions are then sent down the pipeline in groups
; of dual issued pairs as follows:
;
;       LDR     r8, [r0,+r1,LSL #1]! ; Dual Issue Pair 0, Instruction 0
;       MOV     r6, r2               ; Dual Issue Pair 0, Instruction 1
;
;       LDR     r8, [r2,+r3]!        ; Dual Issue Pair 1, Instruction 0
;       ADD     r0, r1, #0x003       ; Dual Issue Pair 1, Instruction 1
;
;       LDR     r8, [r4,+r5,LSL #1]! ; Dual Issue Pair 2, Instruction 0
;       SUB     r2, r3, #0x00a       ; Dual Issue Pair 2, Instruction 1
;
;       LDR     r8, [r6,+r7]!        ; Dual Issue Pair 3, Instruction 0
;       ADD     r4, r5, #0x003       ; Dual Issue Pair 3, Instruction 1
;
; It is during the execution of these instruction pairs that the max sustained 
; power will be observed, as all caches will be firing simultaneously and the
; shifting logic will be toggling all bits.
;
; Following completion of the first iteration of the power_loop which loads
; the caches, the power drawn by this test should be measured from one
; execution the SUBS instruction to the next.
;-------------------------------------------------------------------------------

       ; Include macros
                ;GET     test_header.hs
                GET     macros.hs
                GET     configuration
                ;GET     testenv.h

                AREA  Init, CODE, READONLY
                PRESERVE8

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

num_iteration   EQU   0xA  ; power loop iteration number

;for our testbed
TST_FAIL_ADDR   EQU     0x13000288  ;?????
TST_PASS_ADDR   EQU     0x1300028C  ;?????

                ENTRY

Vectors
                B       Reset_Handler
                B       Undefined_Handler
                B       SWI_Handler
                B       Prefetch_Handler
                B       Abort_Handler
                NOP     ;Reserved vector
                B       IRQ_Handler
                B       FIQ_Handler

;-------------------------------------------------------------------------------
; Handlers for unused exceptions
;-------------------------------------------------------------------------------

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

;-------------------------------------------------------------------------------
; Reset Handler
;-------------------------------------------------------------------------------

zero_mem        % 56


Reset_Handler
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

        ; Initialise memory locations
                MOV     r1,#0
                MOV     r2,#0
                MOV     r3,#0
                MOV     r4,#0
                MOV     r5,#0
                MOV     r6,#0
                MOV     r7,#0
                MOV     r8,#0

       ; Read Multiprocessor Affinity Register MPIDR to determine which CPU
       ; is running the code.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2

       ; Set up stack pointer(s)
                CMP     r0, #0
                BEQ     init_cpu0
                CMP     r0, #1
                BEQ     init_cpu1
                CMP     r0, #2
                BEQ     init_cpu2
                CMP     r0, #3
                BEQ     init_cpu3
       ; This code should not be reached
                B       err_run

       ; CPU Physical memory init
init_cpu0
                LDR     r0,=0xffffffc0
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
                STMIA   r0,{r1-r8}
       ; Initialise system configuration flags
                MOV     r0, #0
                LDR     r1, =data_cpuid
                LDR     r3, =data_cpunb
                LDR     r4, =setup_flag
                LDR     r5, =sync_flag 
                STR     r0, [r1]
                ;STR     r0, [r2] ; r2=0, it will overwritten instructions that are not fetched by other cpus
                STR     r0, [r3]
                STR     r0, [r4]
                STR     r0, [r5]
                LDR     sp, =stack0
  ;cpu0 powers up others
                POWER_UP_CORES

                B       start
init_cpu1
                LDR     r0,=0xffffffc0
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
                STMIA   r0,{r1-r8}		
                LDR     sp, =stack1
                B       cpu_wait
init_cpu2
                LDR     r0,=0xffffffc0
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
                STMIA   r0,{r1-r8}		
                LDR     sp, =stack2
                B       cpu_wait
init_cpu3
                LDR     r0,=0xffffffc0
                STMIA   r0,{r1-r8}
                ADD     r0, r0, #0x20
                STMIA   r0,{r1-r8}		
                LDR     sp, =stack3
                B       cpu_wait
start
                ;MESSAGE "ca7_max_power.s\n"

       ; Store CPU ID
       ; Read Multiprocessor Affinity Register MPIDR to determine which CPU
       ; is running the code.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2
                LDR     r1, =data_cpuid
                STR     r0, [r1]
                DSB

cfg_mp
       ; Cortex-A7 MPCore Configuration
                CPU_NBCORE data_cpunb, err_x, err_cfg

run_setup
                MESSAGE "Running Setup:\n"
                BL      setup

       ; If not running CPU go to wait
                LDR     r4, =setup_flag
                LDR     r5, [r4]
                CMP     r5, r0
                BNE     cpu_wait

       ; Update the setup_flag to enable the next Core to run the code.
       ; If last CPU running the setup then branch to cpu_wait_end
                LDR     r7, =data_cpunb
                LDR     r8, [r7]
                SUB     r9, r8, #1
                CMP     r9, r0
                BEQ     cpu_sync

                ADD     r5, #1
                STR     r5, [r4]
                DSB

cpu_wait
       ; Read Multiprocessor Affinity Register MPIDR to determine which CPU
       ; is running the code.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2
       ; Idle loop
                LDR     r4, =setup_flag
                LDR     r5, [r4]
                CMP     r0, r5
                BLT     cpu_sync
                BEQ     cpu_wait_end
                BGT     cpu_wait

cpu_wait_end
       ; Store CPU ID
                LDR     r1, =data_cpuid
                STR     r0, [r1]
                DSB
                B       run_setup

cpu_sync
       ; working out the sync_flag update based on CPU ID
                MOV     r6, #1
                LSL     r6, r0
       ; working out the synchronising value to expect in the sync_flag
                LDR     r7, =data_cpunb
                LDR     r8, [r7]
                MOV     r9, #1
                LSL     r9, r8
                SUB     r9, #1
       ; updating sync_flag
                LDR     r10, =sync_flag
                LDR     r11, [r10]
                ORR     r11, r6
                STR     r11, [r10]
       ; check sync_flag value: branch to main if matching the expected value
cpu_sync_loop
                LDR     r11, [r10]
                CMP     r11, r9
                BEQ     main
                B       cpu_sync_loop

;-------------------------------------------------------------------------------
; Test Setup
;-------------------------------------------------------------------------------
setup
                PUSH    {r0-r12,lr}

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
; Invalidate caches and TLB if required
; ------------------------------------------------------------

      ; Check the status of L1RSTDISABLE and only
      ; run the invalidate sequence if it has not been
      ; carried at at reset in hardware.

      ; get CPU ID
               ;LDR     r12, =data_cpuid
               ;LDR     r12, [r12]
               ;LDR     r6,=TBVAL_CFGL1
               ;LDR     r0, [r6]
               ;LSR     r0, r12
               ;TST     r0, #1:SHL:16
               ;BEQ     skip_inval
        ;just branch to skip_inval
        ;since in ca7 local, cs3_ctrl gives 4'b0 to L1RSTDISABLE
               BL     skip_inval

               MESSAGE "- Invalidate caches\n"
      ; Invalidate the I Cache
               MOV     r0, #0
               MCR     p15, 0, r0, c7, c5, 0   ; ICIALLU - Invalidate entire I Cache, and flushes branch target cache
      ; Invalidate the D Cache
               INVALIDATE_DCACHE

      ; Invalidate TLBs
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

                MRC     p15, 0, r1, c0, c0, 5  ; Read Multiprocessor Affinity Register
                AND     r1, r1, #0x03          ; Mask off, leaving the CPU ID field

                CMP     r1, #0
                BEQ     cpu0_table
                CMP     r1, #1
                BEQ     cpu1_table
                CMP     r1, #2
                BEQ     cpu2_table
                CMP     r1, #3
                BEQ     cpu3_table
       ; This code should not be reached
                B       err_run

cpu0_table
; ------------------------------------------------------------
; Set location of level 1 page table
; ------------------------------------------------------------
                LDR     r0, =table_base0       ; Location of master copy of TLB
                MCR     p15, 0, r0, c2, c0 ,0
; ------------------------------------------------------------
;  Create sections for translation table
; ------------------------------------------------------------
                TT_SECTION_WRITE  0x0, 0x0, WB :OR: RW :OR: SHARED
                TT_SECTION_WRITE  0x100000, 0x100000, SHARED :OR: WB :OR: RW :OR: EXE
                TT_SECTION_WRITE  TBVAL_SYSADDR, TBVAL_SYSADDR, SDEVICE :OR: RW :OR: NON_EXE
                TT_SECTION_WRITE  0xfff00000, 0xfff00000, WB :OR: RW :OR: SHARED
                B       enable_mmu

cpu1_table
; ------------------------------------------------------------
; Set location of level 1 page table
; ------------------------------------------------------------
                LDR     r0, =table_base1       ; Location of master copy of TLB
                MCR     p15, 0, r0, c2, c0 ,0
; ------------------------------------------------------------
;  Create sections for translation table
; ------------------------------------------------------------
                TT_SECTION_WRITE  0x0, 0x0, WB :OR: RW :OR: SHARED
                TT_SECTION_WRITE  0x100000, 0x100000, SHARED :OR: WB :OR: RW :OR: EXE
                TT_SECTION_WRITE  TBVAL_SYSADDR, TBVAL_SYSADDR, SDEVICE :OR: RW :OR: NON_EXE
                TT_SECTION_WRITE  0xfff00000, 0xfff00000, WB :OR: RW :OR: SHARED
                B       enable_mmu

cpu2_table
; ------------------------------------------------------------
; Set location of level 1 page table
; ------------------------------------------------------------
                LDR     r0, =table_base2       ; Location of master copy of TLB
                MCR     p15, 0, r0, c2, c0 ,0
; ------------------------------------------------------------
;  Create sections for translation table
; ------------------------------------------------------------
                TT_SECTION_WRITE  0x0, 0x0, WB :OR: RW :OR: SHARED
                TT_SECTION_WRITE  0x100000, 0x100000, SHARED :OR: WB :OR: RW :OR: EXE
                TT_SECTION_WRITE  TBVAL_SYSADDR, TBVAL_SYSADDR, SDEVICE :OR: RW :OR: NON_EXE
                TT_SECTION_WRITE  0xfff00000, 0xfff00000, WB :OR: RW :OR: SHARED
                B       enable_mmu

cpu3_table
; ------------------------------------------------------------
; Set location of level 1 page table
; ------------------------------------------------------------
                LDR     r0, =table_base3       ; Location of master copy of TLB
                MCR     p15, 0, r0, c2, c0 ,0
; ------------------------------------------------------------
;  Create sections for translation table
; ------------------------------------------------------------
                TT_SECTION_WRITE  0x0, 0x0, WB :OR: RW :OR: SHARED
                TT_SECTION_WRITE  0x100000, 0x100000, SHARED :OR: WB :OR: RW :OR: EXE
                TT_SECTION_WRITE  TBVAL_SYSADDR, TBVAL_SYSADDR, SDEVICE :OR: RW :OR: NON_EXE
                TT_SECTION_WRITE  0xfff00000, 0xfff00000, WB :OR: RW :OR: SHARED

enable_mmu
; ------------------------------------------------------------
; Enable the MMU
; ------------------------------------------------------------

       ; Set SCTLR bit 0 to enable MMU and to activate virtual address
       ; system
                MESSAGE "- Enable MMU\n"
                ENABLE_MMU

; ------------------------------------------------------------
; Branch Prediction Init
; ------------------------------------------------------------
                MESSAGE "- Enable Caches\n"
                ENABLE_CACHES
				
                POP     {r0-r12,pc}

;-------------------------------------------------------------------------------
; Main body of code
;-------------------------------------------------------------------------------
                ALIGN 8
main

                ;-----------------------
                ; ENABLE INVASIVE DEBUG
                ;-----------------------
                MRC     p14, 0, r0, c0, c2, 2   ; Read DBGDSCR into r0
                ORR     r0, r0, #0x4000         ; Set HDBGen bit (bit 14)
                MCR     p14, 0, r0, c0, c2, 2   ; Write DBGDSCR

                ;-----------------------
                ; ENABLE WATCHPOINTS &
                ; BREAKPOINTS
                ;-----------------------
                MOV     r0, #0x1110
                MCR     p14, 0, r0, c0, c0, 4   ; Write DBGDBVR0

                MOV     r0, #0x2220
                MCR     p14, 0, r0, c0, c1, 4   ; Write DBGDBVR1

                MOV     r0, #0x3330
                MCR     p14, 0, r0, c0, c2, 4   ; Write DBGDBVR2

                MOV     r0, #0x444
                MCR     p14, 0, r0, c0, c0, 6   ; Write DBGDWVR0

                MOV     r0, #0x5550
                MCR     p14, 0, r0, c0, c1, 6   ; Write DBGDWVR1

                MOV     r0, #0x00000007
                MCR     p14, 0, r0, c0, c0, 5   ; Write DBGDBCR0
                MCR     p14, 0, r0, c0, c1, 5   ; Write DBGDBCR1
                MCR     p14, 0, r0, c0, c2, 5   ; Write DBGDBCR2
                MCR     p14, 0, r0, c0, c0, 7   ; Write DBGDWCR0
                MCR     p14, 0, r0, c0, c1, 7   ; Write DBGDWCR1

		; SMP Enable
  		MRC     p15, 0, r0, c1, c0, 1
                ORR     r0, r0, #1<<6
                MCR     p15, 0, r0, c1, c0, 1
		
                ;------------------------------------------------------------------
                ; SET UP MEMORY MAPPED COMPONENT FOR MP SYNCHRONISING TRIGGER
                ;------------------------------------------------------------------
                ; In MPCore config, only CPU0 needs to access the memory mapped
                ; validation component.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2
                CMP     r0, #0
                BNE     skip_event
		
                ; Disable all previously programmed interrupt/event generation
                ; (inc. EVENTI, register VAL_INTSEL)
                LDR     r7, =TBVAL_INTSEL
                MOV     r0, #0
                STR     r0, [r7]
                DSB

                ; Trigger condition: "All CPU's WFE must be set in order to set EVENTI"
                ; NB: depends on the number of CPUs implemented
                LDR     r7, =TBVAL_INTTRIG
                LDR     r1, =data_cpunb
                LDR     r0, [r1]
                MOV     r1, #1
                LSL     r1, r0
                SUB     r0, r1, #1
                LSL     r0, #4
                STR     r0, [r7]
                DSB

                ; EVENTI generation enabled (held until programmed trigger condition is true)
                LDR     r7, =TBVAL_INTSEL
                MOV     r0, #1<<8
                STR     r0, [r7]
                DSB

                ; Schedule trigger now (delay == 0 cycle)
                LDR     r7, =TBVAL_INTSCHED
                MOV     r0, #0
                STR     r0, [r7]
                DSB

                MESSAGE "\nRunning Power Loops\n\n"

                B       skip_event; branch over alignement padding
                
;-------------------------------------------------------------------------------
; Main code loop to measure max power
;-------------------------------------------------------------------------------
                ALIGN 32 ; align to $ line
skip_event		
                LDR     r0,=0x00000000
                LDR     r1,=0xfffffffd
                LDR     r2,=0xfffffffc
                LDR     r3,=0x00000006
                LDR     r4,=0x00000000
                LDR     r5,=0xfffffffd
                LDR     r6,=0xfffffffc
                LDR     r7,=0x00000006
		
                LDR     r10,=num_iteration; num of iterations round power_loop

		; Wait For Event
                ; Use two WFE instructions to make sure the event register is
                ; clear so that STANDBYWFE will be raise and then used as a
                ; trigger to generate EVENTI
                WFE
                WFE
				
power_loop
                SUBS     r10, r10, #1	

                ; Group-1
                LDR     r8, [r0,+r1,LSL #1]! ; Dual Issue Pair 0, Instruction 0
                MOV     r6, r2               ; Dual Issue Pair 0, Instruction 1

                LDR     r8, [r2,+r3]!        ; Dual Issue Pair 1, Instruction 0
                ADD     r0, r1, #0x003       ; Dual Issue Pair 1, Instruction 1

                LDR     r8, [r4,+r5,LSL #1]! ; Dual Issue Pair 2, Instruction 0
                SUB     r2, r3, #0x00a       ; Dual Issue Pair 2, Instruction 1

                LDR     r8, [r6,+r7]!        ; Dual Issue Pair 3, Instruction 0
                ADD     r4, r5, #0x003       ; Dual Issue Pair 3, Instruction 1

                ; Group-2
                LDR     r8, [r0,+r1,LSL #1]! ; Dual Issue Pair 0, Instruction 0
                MOV     r6, r2               ; Dual Issue Pair 0, Instruction 1

                LDR     r8, [r2,+r3]!        ; Dual Issue Pair 1, Instruction 0
                ADD     r0, r1, #0x003       ; Dual Issue Pair 1, Instruction 1

                LDR     r8, [r4,+r5,LSL #1]! ; Dual Issue Pair 2, Instruction 0
                SUB     r2, r3, #0x00a       ; Dual Issue Pair 2, Instruction 1

                LDR     r8, [r6,+r7]!        ; Dual Issue Pair 3, Instruction 0
                ADD     r4, r5, #0x003       ; Dual Issue Pair 3, Instruction 1

                ; Group-3
                LDR     r8, [r0,+r1,LSL #1]! ; Dual Issue Pair 0, Instruction 0
                MOV     r6, r2               ; Dual Issue Pair 0, Instruction 1

                LDR     r8, [r2,+r3]!        ; Dual Issue Pair 1, Instruction 0
                ADD     r0, r1, #0x003       ; Dual Issue Pair 1, Instruction 1

                LDR     r8, [r4,+r5,LSL #1]! ; Dual Issue Pair 2, Instruction 0
                SUB     r2, r3, #0x00a       ; Dual Issue Pair 2, Instruction 1

                LDR     r8, [r6,+r7]!        ; Dual Issue Pair 3, Instruction 0
                ADD     r4, r5, #0x003       ; Dual Issue Pair 3, Instruction 1

                ; Group-4
                LDR     r8, [r0,+r1,LSL #1]! ; Dual Issue Pair 0, Instruction 0
                MOV     r6, r2               ; Dual Issue Pair 0, Instruction 1

                LDR     r8, [r2,+r3]!        ; Dual Issue Pair 1, Instruction 0
                ADD     r0, r1, #0x003       ; Dual Issue Pair 1, Instruction 1

                LDR     r8, [r4,+r5,LSL #1]! ; Dual Issue Pair 2, Instruction 0
                SUB     r2, r3, #0x00a       ; Dual Issue Pair 2, Instruction 1

                LDR     r8, [r6,+r7]!        ; Dual Issue Pair 3, Instruction 0
                ADD     r4, r5, #0x003       ; Dual Issue Pair 3, Instruction 1		

		BNE	power_loop

exit
       ; Read Multiprocessor Affinity Register MPIDR to determine which CPU
       ; is running the code.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2
                CMP     r0, #0
                BEQ     pass

                WFI

;-------------------------------------------------------------------------------
; End of test
;-------------------------------------------------------------------------------

pass
; for our testbed, write pass addr will finish simulation
        LDR     r0,=TST_PASS_ADDR
        MOV     r1, #0xabcd
        STR     r1,[r0]
                TEST_PASS
fail
; for our testbed, write fail addr will finish simulation
        LDR     r0,=TST_FAIL_ADDR
        MOV     r1, #0xabcd
        STR     r1,[r0]
                TEST_FAIL

;-------------------------------------------------------------------------------
; Error Messages
;-------------------------------------------------------------------------------

err_x
                MESSAGE "UNKNOWN\n"
err_run
                MESSAGE "\nThis code should not be reached\n"
                B       fail
err_cfg
                MESSAGE "\nConfiguration mismatch between test and RTL\n"
                B       fail

;-------------------------------------------------------------------------------
; Pagetable Data
;-------------------------------------------------------------------------------
                AREA    TT0,DATA,READONLY, ALIGN=14
table_base0
                % 16384

                AREA    TT1,DATA,READONLY, ALIGN=14
table_base1
                % 16384

                AREA    TT2,DATA,READONLY, ALIGN=14
table_base2
                % 16384

                AREA    TT3,DATA,READONLY, ALIGN=14
table_base3
                % 16384

;-------------------------------------------------------------------------------
; Stack Data
;-------------------------------------------------------------------------------

                AREA    Stack, DATA, READWRITE, ALIGN=12

                % 256
stack0
                % 256
stack1
                % 256
stack2
                % 256
stack3
                % 256

;-------------------------------------------------------------------------------
; Test Data
;-------------------------------------------------------------------------------

                AREA    Misc, DATA, READWRITE, ALIGN=12

data_cpuid      DCD     0
data_cpunb      DCD     0
setup_flag      DCD     0
sync_flag       DCD     0

;-------------------------------------------------------------------------------
; BST instructions
;-------------------------------------------------------------------------------

                AREA    |~BST CODE|, CODE, ALIGN=12

                BST_START
                BST "EXIT"
                BST "PRINTF ERROR: Should not be reached"
                BST_END

                END


