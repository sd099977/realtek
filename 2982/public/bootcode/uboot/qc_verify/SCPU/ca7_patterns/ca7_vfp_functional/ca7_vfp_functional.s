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
;      Checked In          : $Date: 2009-08-20 11:00:24 +0100 (Thu, 20 Aug 2009) $
;
;      Revision            : $Revision: 115814 $
;
;      Release Information : CORTEX-A7-r0p4-00rel0
;
;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
;
; Description:  Test to execute VFP instructions using Cortex-A7
;               MPCore processor FPU.
;               
;-------------------------------------------------------------------------------

       ; Include macros and test header
                GET     test_header.hs

;-------------------------------------------------------------------------------
; Start
;-------------------------------------------------------------------------------

       ; Addresses and data used by this test
       ; Note: user may need to modify the address values depending on the
       ;       system memory map it run onto.
                TEST_HEADER

       ; Read Multiprocessor Affinity Register MPIDR to determine which CPU
       ; is running the code.
                MRC     p15, 0, r0, c0, c0, 5
                UBFX    r0, r0, #0, #2

       ; Set up stack pointer(s)
                CMP     r0, #0
                BEQ     set_stack0
                CMP     r0, #1
                BEQ     set_stack1
                CMP     r0, #2
                BEQ     set_stack2
                CMP     r0, #3
                BEQ     set_stack3

       ; This code should not be reached
                B       err_run

set_stack0
                ;LDR     sp, =stack0
                B       start
set_stack1
                ;LDR     sp, =stack1
                B       cpu_wait
set_stack2
                ;LDR     sp, =stack2
                B       cpu_wait
set_stack3
                ;LDR     sp, =stack3
                B       cpu_wait

;-------------------------------------------------------------------------------
; Main Code
;-------------------------------------------------------------------------------

start
                ;Core0 powers up others
                POWER_UP_CORES

                ;MESSAGE "ca7_vfp_functional.s\n" ; TODO

       ; Store CPU ID
                LDR     r1, =data_cpuid
                STR     r0, [r1]
                DSB


cfg_mp
       ; Cortex-A7 MPCore Configuration
                CPU_NBCORE data_cpunb, err_x, err_cfg
                DSB
run_test
                ;MESSAGE "Running test:\n"	;TODO
                BL      vfp_test_start

       ; MPCore configuration: end of test if it is the last processor
                ;LDR     r2, =data_cpunb
                ;LDR     r1, [r2]
                ;SUB     r1, r1, #1
                ;LDR     r2, =data_cpuid
                ;LDR     r0, [r2]
                ;CMP     r0, r1
                ;BEQ     end_test
                B 			 end_test

       ; Update the syncflags to enable the next Core to run the code
                LDR     r1, =syncflags
                LDR     r2, [r1]
                ADD     r2, r2, #1
                STR     r2, [r1]
                DSB

cpu_wait
       ; Idle loop
                LDR     r1, =syncflags
                LDR     r2, [r1]
                CMP     r2, r0
                BNE     cpu_wait
       ; Store CPU ID
                LDR     r1, =data_cpuid
                STR     r0, [r1]
                DSB
                B       run_test

end_test
                LDR     r0, =test_skipped
                LDR     r1, [r0]
                CMP     r1, #0
                BEQ     skip
                B       pass

;-------------------------------------------------------------------------------
; FPU Test
;-------------------------------------------------------------------------------

vfp_test_start
                PUSH    {r0-r12,lr}
       ; Enable FPU if present
                FPU_PRESENT r0
                CMP     r0, #1
                BNE     no_fpu
                LDR     r0, =test_skipped
                MOV     r1, #1
                STR     r1, [r0]
                ENABLE_FPU
        
       ; FPU Instructions
                ;MESSAGE "- Load instructions\n" ;TODO
                LDR     r3, =INPUT_DATA
                VLDMIA   r3!, {s0-s31}

       ; Coprocessor Data Processing Single
                ;MESSAGE "- Data processing instructions (SP)\n" ;TODO
                VMLA.F32      s0, s0, s0
                VFMA.F32      s1, s1, s1
                VMUL.F32      s2, s2, s2
                VADD.F32      s3, s3, s3
                VDIV.F32      s4, s4, s4
                VSQRT.F32     s5, s5
                VNEG.F32      s6, s6
                VCVT.F64.F32  d3, s7
                VCVT.S32.F32  s8, s8
                VCVTT.F16.F32 s9, s9

       ; Coprocessor Data Processing Double
                ;MESSAGE "- Data processing instructions (DP)\n" ;TODO
                VMLA.F64      d5, d5, d5
                CDP           p11, 10, c6, c6, c6, 2 ; VFMS.F64     d6, d6, d6
                VMUL.F64      d7, d7, d7
                VADD.F64      d8, d8, d8
                VDIV.F64      d9, d9, d9
                VSQRT.F64     d10, d10
                VNEG.F64      d11, d11
                VCVT.F32.F64  s22, d12
                VCVT.U32.F64  s24, d13

       ; Register transfer
                ;MESSAGE "- Register transfer instructions\n"	;TODO
                LDR     r2, =0x01234567
                VMOV    s27, r2
                VMOV    r3, s27
                VMOV    d15, r2, r3
                VMRS    r0, FPSCR

       ; Stores
                ;MESSAGE "- Store instructions\n"	;TODO
                LDR     r1, =CALCULATED_DATA
                STR     r0, [r1], #4
                VSTMIA  r1!, {s0-s31}

       ; Checks
                ;MESSAGE "- Checking results\n"	;TODO
                MOV     r4, #33
                LDR     r0, =EXPECTED_DATA
                LDR     r2, =CALCULATED_DATA
check_loop
                LDR     r1, [r0], #4
                LDR     r3, [r2], #4
                CMP     r1, r3
                BNE     check_fail
                SUBS    r4, #1
                BNE     check_loop
                B       vfp_test_end

check_fail
                ;MESSAGE "**Error: VFP instruction check fail (r1 != r3)\n"	;TODO
                B       fail
       ; end of test
no_fpu
                ;MESSAGE "- FPU not present\n"	;TODO

vfp_test_end
                POP     {r0-r12,pc}

       ; this code should not be reached
                B       err_run

;-------------------------------------------------------------------------------
; Test Completed
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
skip
                MESSAGE "No FPU present\n"
                TEST_FINISH "** TEST SKIPPED **\n"

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
; Stack Data
;-------------------------------------------------------------------------------

                AREA    |Stack DATA|, DATA, ALIGN=12

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

                AREA    |Misc DATA|, DATA, ALIGN=12

data_cpuid      DCD     0
data_cpunb      DCD     0
syncflags       DCD     0
test_skipped    DCD     0

;-------------------------------------------------------------------------------
; FPU Data
;-------------------------------------------------------------------------------

CALCULATED_DATA
                % 256

                AREA    |FPU DATA|, DATA, READONLY, ALIGN=12
                SPACE   28

                ALIGN   64                           ; align code so exit routine is not fetched into cache
INPUT_DATA
                DCD     0xB3341F14
                DCD     0x3FCA6EF2
                DCD     0xC00075F1
                DCD     0x3FD39DDF
                DCD     0xE0003AF8
                DCD     0x3FE9CEEF
                DCD     0xE0003AF8
                DCD     0x3FE9CEEF
                DCD     0xCCCEA48F
                DCD     0x3FBB444B
                DCD     0x13336E2B
                DCD     0x3FED0223
                DCD     0xE0003AF8
                DCD     0x3FE9CEEF
                DCD     0xF0001D7C
                DCD     0x3FFCE777
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF                         
                DCD     0xFFFFFFFF
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF
                DCD     0xFFFFFFFF
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF
                DCD     0xFFFFFFFF
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF
                DCD     0xFFFFFFFF

EXPECTED_DATA
                DCD     0x00000011
                DCD     0xB3341F14
                DCD     0x4082A55F
                DCD     0x4080EC4F
                DCD     0x40539DDF
                DCD     0x3F800000
                DCD     0x3FACFEDE
                DCD     0xE0000000
                DCD     0x3FFD39DD
                DCD     0xF98ADB88
                DCD     0x3DDA444B
                DCD     0x6544BF2A
                DCD     0x3FFBA701
                DCD     0x6A56EEE7
                DCD     0x3FC3F97B
                DCD     0x315ABD4C
                DCD     0x400A1B9C
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF
                DCD     0xFFFFFFFF
                DCD     0x00000000
                DCD     0x00000000
                DCD     0x00000000
                DCD     0x7FFFFFFF
                DCD     0x00000000
                DCD     0x00000000
                DCD     0xFFFFFFFF
                DCD     0x01234567
                DCD     0x00000000
                DCD     0x00000000
                DCD     0x01234567
                DCD     0x01234567

;-------------------------------------------------------------------------------
; BST Programming
;-------------------------------------------------------------------------------

                AREA    |~BST CODE|, CODE, ALIGN=12
                BST_START

;-------------------------------------------------------------------------------
; End of BST instructions
;-------------------------------------------------------------------------------

                BST "PRINTF ***End of BST code"
                BST "EXIT"
                BST "PRINTF BST ERROR: Should not be reached: End"
                BST_END

;-------------------------------------------------------------------------------
; End of ca7_vfp_functional.s
;-------------------------------------------------------------------------------
                END

