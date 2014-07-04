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
; Description:  Test to execute Advanced SIMD instructions in
;               Cortex-A7 MPCore processor.
;
;-------------------------------------------------------------------------------

       ; Include macros and test header
                GET     test_header.hs

;-------------------------------------------------------------------------------
; Init Code
;-------------------------------------------------------------------------------

       ; Addresses and data used by this test
       ; Note: user may need to modify the address values depending on the
       ;       system memory map it run onto.
GE2Flag         EQU     0x00040000
NFlag           EQU     0x80000000
QFlag           EQU     0x08000000
CPSR_FLGS_MASK  EQU     0xf90f0000
INTL_DATA_ADDR  EQU     neon_data

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

                ;MESSAGE "ca7_advsimd_functional.s\n"                                

       ; Store CPU ID
                LDR     r1, =data_cpuid
                STR     r0, [r1]
                DSB

cfg_mp
       ; Cortex-A7 MPCore Configuration
                CPU_NBCORE data_cpunb, err_x, err_cfg
                DSB
run_test
                ;MESSAGE "Running test:\n" ; TODO
                BL      neon_test_start
								
       ; MPCore configuration: end of test if it is the last processor
                ;LDR     r2, =data_cpunb
                ;LDR     r1, [r2]
                ;SUB     r1, r1, #1
                ;LDR     r2, =data_cpuid
                ;LDR     r0, [r2]
                ;CMP     r0, r1
                ;POP     {r0-r12,pc}
                ;BEQ     end_test
                B				 end_test

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
; NEON Test
;-------------------------------------------------------------------------------

neon_test_start
                PUSH    {r0-r12,lr}
       ; Enable NEON if present
                NEON_PRESENT r0
                CMP     r0, #1
                BNE     no_neon
                LDR     r0, =test_skipped
                MOV     r1, #1
                STR     r1, [r0]
                MOV     r0, #1<<30
                MCR     p10, #7, r0, c8, c0, 0   ;Enable NEON by writing FPEXC
                MOV     r0, #0
                VLDM    r0!, {d0 -d15}
                VLDM    r0!, {d16-d31}

       ; NEON Instructions
                ;MESSAGE "- Execute VMOV Instruction\n" ;TODO
VMOV.S17_001    NEON_TEST \
                fail, \
                GE2Flag,GE2Flag,\
                0x3333fff0f1f3f2f4,-,\
                -,-,\
                d13,-,-,-,\
                -,-,\
                -,-,\
                -,-,-,-,\
                0x3333,-,-,\
                "LDR R4,=0x0a1b2c3d",\
                "VMOV.S16 R4, d13[3]",\
                "MOV R0,R4", \
                "MOV R4,R3"

VMOV.S17_002    NEON_TEST \
                fail, \
                GE2Flag,GE2Flag,\
                0x33ccafb30101f0f4,-,\
                -,-,\
                d14,-,-,-,\
                -,-,\
                -,-,\
                -,-,-,-,\
                0x33cc,-,-,\
                "LDR R5,=0x0a",\
                "VMOV.S16 R5, d14[3]",\
                "MOV R0,R5"

                ;MESSAGE "- Execute VADDW Instruction\n" ; TODO
VADD.I16.I16.S8_B2B_003 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x38361d2848d40309, 0x2416de2137570ebc, \
                0x38991da3489802b5, 0x23f9ddf437d20f1b, \
                0x38341d424885023a, 0x2386de2537790f31, \
                d6, d7, d4, d5, d0, d1, \
                -, -, -, -, \
                -, -, -, -, \
                "VADDW.I16.I16.S8  q0,q1,d5", \
                "VADDW.I16.I16.S8  q2,q0,d5", \
                "VADDW.I16.I16.S8  q3,q2,d6"

                ;MESSAGE "- Execute VSUBW Instruction\n" ; TODO
VSUB.I32.I32.U16_B2B_004 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x37cdb49a48719e75, 0x2312d98b371ed5d2, \
                0x37ce521f4871dac9, 0x2312f6b8371f5b73, \
                0x37ceb7804871ee44, 0x23136a87371fb55d, \
                d6, d7, d4, d5, d0, d1, \
                -, -, -, -, \
                -, -, -, -, \
                "VSUBW.I32.I32.U16  q0,q1,d5", \
                "VSUBW.I32.I32.U16  q2,q0,d5", \
                "VSUBW.I32.I32.U16  q3,q2,d6"

                ;MESSAGE "- Execute VMUL Instruction\n" ; TODO
VMUL.I8_B2B_005 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x1c70c090002089ff, 0xfeacb054c028bd5f, \
                0xf29474d4b834bd61, -, \
                -, -, \
                d2, d1, d0, -, -, -,\
                -, -, -, -, \
                -, -, -, -, \
                "VMUL.I8  d0,d1,d2", \
                "VMUL.I8  d1,d0,d2", \
                "VMUL.I8  d2,d1,d0"

                ;MESSAGE "- Execute VMLA Instruction\n" ; TODO
VMLA.I32.U16_B2B_006 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0xfc299fafef547a9c, 0x79b7d609e2c39f7b, \
                0x45709189e850c137, 0x3d7008bea9dad9a1, \
                0x64ae0bb54804d45c, 0xc0a854e81bc4d2b3, \
                d14, d15, d8, d9, d0, d1,\
                -, -, -, -, \
                -, -, -, -, \
                "VMLAL.I32.U16  q0,d1,d2", \
                "VMLAL.I32.U16  q4,d0,d1", \
                "VMLAL.I32.U16  q7,d8,d9"

                ;MESSAGE "- Execute VCLS Instruction\n" ; TODO
VCLS.S8_B2B_007 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x0100020000020101, 0x0100010000000001, \
                0x0201000400030200, 0x0003010301010001, \
                -, -, \
                d16, d4, d5, d1, -, -, \
                -, -, -, -, \
                -, -, -, -, \
                "VCLS.S8  d1,d15", \
                "VCLS.S8  q2,q8", \
                "VCLS.S8  d16,d12"

                ;MESSAGE "- Execute VMAX Instruction\n" ; TODO
VMAX.S32_B2B_008 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x37cf1ce1487201bf, 0x37cf1ce1487201bf, \
                0x37cf1ce1487201bf, -, \
                -, -, \
                d2, d1, d0, -, -, -, \
                -, -, -, -, \
                -, -, -, -, \
                "VMAX.S32  d0,d1,d2", \
                "VMAX.S32  d1,d0,d2", \
                "VMAX.S32  d2,d1,d0"

                ;MESSAGE "- Execute VSHL Instruction\n" ;TODO
VSHL.I64_B2B_009 NEON_INTLK_TEST \
                fail, \
                QFlag, QFlag, \
                0x369a77ffab5f0b80, 0x3a5b0b433b0a78a8, \
                -, -, \
                -, -, \
                d6, d1, -, -, -, -, \
                -, -, -, -, \
                -, -, -, -, \
                "VSHL.I64  d1,d6,#1", \
                "VSHL.I64  d6,d7,#2", \
                "VSHL.I64  d6,d13,#3"

VMOV_010        NEON_TEST \
                fail, \
                NFlag,NFlag,\
                0x5555555555555555,-,\
                -,-,\
                d0,-,-,-,\
                0xaaaaaaaaaaaaaaaa,-,\
                -,-,\
                d0,-,-,-,\
                -,-,-,\
                "LDR R0,=0xaaaaaaaa",\
                "LDR R1,=0xaaaaaaaa",\
                "VMOV   d0,R0,R1"
                B       neon_test_end

no_neon
                ;MESSAGE "- NEON not present\n" ; TODO

neon_test_end
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
                MESSAGE "No NEON present\n"
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
       ; Used to init double word registers
zero            DCD     0
                DCD     0

;-------------------------------------------------------------------------------
; Input Neon Data
;-------------------------------------------------------------------------------

                AREA    |Neon DATA|, DATA, READONLY, ALIGN=12
neon_data
                DCD     0x46B94BFB
                DCD     0x1C667E81
                DCD     0xFF6ABDDF
                DCD     0x9E2CFB54
                DCD     0x487201BF
                DCD     0x37CF1CE1
                DCD     0x37200F47
                DCD     0x2313DE56
                DCD     0x359DAA88
                DCD     0xC6756687
                DCD     0x6561137B
                DCD     0x73CF59EA
                DCD     0x9D853C54
                DCD     0x1D2D85A1
                DCD     0xAAEE655B
                DCD     0xD5502F37
                DCD     0x3988CCE3
                DCD     0x3DA10279
                DCD     0xA5F8D999
                DCD     0xF1AB768E
                DCD     0xF368EE43
                DCD     0x88F51F3F
                DCD     0x3FAFBEA6
                DCD     0xF78E4D0D
                DCD     0x48E2DC29
                DCD     0xDDA0E486
                DCD     0xF56BE170
                DCD     0xC6D34EFF
                DCD     0x4B135805
                DCD     0x6206FB8F
                DCD     0xDDCB53CD
                DCD     0x690DC509
                DCD     0x799452D3
                DCD     0x3AA73B48
                DCD     0xA9F1EAB5
                DCD     0x152E9D06
                DCD     0xB98949B2
                DCD     0x6C2C0613
                DCD     0xE3228831
                DCD     0x00171EAC
                DCD     0xA95E7136
                DCD     0x29C75246
                DCD     0xA3951D16
                DCD     0x38FD57F6
                DCD     0x8F5E987C
                DCD     0xCFA38874
                DCD     0x0BBD6D71
                DCD     0xD1765C41
                DCD     0x2593C701
                DCD     0xC8EC0F70
                DCD     0xB3D691C0
                DCD     0x91BA2F33
                DCD     0x80D6AB33
                DCD     0xA1D1A50D
                DCD     0x58F73EE6
                DCD     0x78D57E5E
                DCD     0x53A0B1C3
                DCD     0x868E74A6
                DCD     0x0642C7DB
                DCD     0x493D11A8
                DCD     0xCE14F3BF
                DCD     0x6CADE060
                DCD     0xFA2AE325
                DCD     0x60970067
                DCD     0x46B94BFB
                DCD     0x1C667E81
                DCD     0xFF6ABDDF
                DCD     0x9E2CFB54
                DCD     0x487201BF
                DCD     0x37CF1CE1
                DCD     0x37200F47
                DCD     0x2313DE56
                DCD     0x359DAA88
                DCD     0xC6756687
                DCD     0x6561137B
                DCD     0x73CF59EA
                DCD     0x9D853C54
                DCD     0x1D2D85A1
                DCD     0xAAEE655B
                DCD     0xD5502F37
                DCD     0x3988CCE3
                DCD     0x3DA10279
                DCD     0xA5F8D999
                DCD     0xF1AB768E
                DCD     0xF368EE43
                DCD     0x88F51F3F
                DCD     0x3FAFBEA6
                DCD     0xF78E4D0D
                DCD     0x48E2DC29
                DCD     0xDDA0E486
                DCD     0xF56BE170
                DCD     0xC6D34EFF
                DCD     0x4B135805
                DCD     0x6206FB8F
                DCD     0xDDCB53CD
                DCD     0x690DC509
                DCD     0x799452D3
                DCD     0x3AA73B48
                DCD     0xA9F1EAB5
                DCD     0x152E9D06
                DCD     0xB98949B2
                DCD     0x6C2C0613
                DCD     0xE3228831
                DCD     0x00171EAC
                DCD     0xA95E7136
                DCD     0x29C75246
                DCD     0xA3951D16
                DCD     0x38FD57F6
                DCD     0x8F5E987C
                DCD     0xCFA38874
                DCD     0x0BBD6D71
                DCD     0xD1765C41
                DCD     0x2593C701
                DCD     0xC8EC0F70
                DCD     0xB3D691C0
                DCD     0x91BA2F33
                DCD     0x80D6AB33
                DCD     0xA1D1A50D
                DCD     0x58F73EE6
                DCD     0x78D57E5E
                DCD     0x53A0B1C3
                DCD     0x868E74A6
                DCD     0x0642C7DB
                DCD     0x493D11A8
                DCD     0xCE14F3BF
                DCD     0x6CADE060
                DCD     0xFA2AE325
                DCD     0x60970067
                DCD     0x46B94BFB
                DCD     0x1C667E81
                DCD     0xFF6ABDDF
                DCD     0x9E2CFB54
                DCD     0x487201BF
                DCD     0x37CF1CE1
                DCD     0x37200F47
                DCD     0x2313DE56
                DCD     0x359DAA88
                DCD     0xC6756687
                DCD     0x6561137B
                DCD     0x73CF59EA
                DCD     0x9D853C54
                DCD     0x1D2D85A1
                DCD     0xAAEE655B
                DCD     0xD5502F37
                DCD     0x3988CCE3
                DCD     0x3DA10279
                DCD     0xA5F8D999
                DCD     0xF1AB768E
                DCD     0xF368EE43
                DCD     0x88F51F3F
                DCD     0x3FAFBEA6
                DCD     0xF78E4D0D
                DCD     0x48E2DC29
                DCD     0xDDA0E486
                DCD     0xF56BE170
                DCD     0xC6D34EFF
                DCD     0x4B135805
                DCD     0x6206FB8F
                DCD     0xDDCB53CD
                DCD     0x690DC509
                DCD     0x799452D3
                DCD     0x3AA73B48
                DCD     0xA9F1EAB5
                DCD     0x152E9D06
                DCD     0xB98949B2
                DCD     0x6C2C0613
                DCD     0xE3228831
                DCD     0x00171EAC
                DCD     0xA95E7136
                DCD     0x29C75246
                DCD     0xA3951D16
                DCD     0x38FD57F6
                DCD     0x8F5E987C
                DCD     0xCFA38874
                DCD     0x0BBD6D71
                DCD     0xD1765C41
                DCD     0x2593C701
                DCD     0xC8EC0F70
                DCD     0xB3D691C0
                DCD     0x91BA2F33
                DCD     0x80D6AB33
                DCD     0xA1D1A50D
                DCD     0x58F73EE6
                DCD     0x78D57E5E
                DCD     0x53A0B1C3
                DCD     0x868E74A6
                DCD     0x0642C7DB
                DCD     0x493D11A8
                DCD     0xCE14F3BF
                DCD     0x6CADE060
                DCD     0xFA2AE325
                DCD     0x60970067
                DCD     0x46B94BFB
                DCD     0x1C667E81
                DCD     0xFF6ABDDF
                DCD     0x9E2CFB54
                DCD     0x487201BF
                DCD     0x37CF1CE1
                DCD     0x37200F47
                DCD     0x2313DE56
                DCD     0x359DAA88
                DCD     0xC6756687
                DCD     0x6561137B
                DCD     0x73CF59EA
                DCD     0x9D853C54
                DCD     0x1D2D85A1
                DCD     0xAAEE655B
                DCD     0xD5502F37
                DCD     0x3988CCE3
                DCD     0x3DA10279
                DCD     0xA5F8D999
                DCD     0xF1AB768E
                DCD     0xF368EE43
                DCD     0x88F51F3F
                DCD     0x3FAFBEA6
                DCD     0xF78E4D0D
                DCD     0x48E2DC29
                DCD     0xDDA0E486
                DCD     0xF56BE170
                DCD     0xC6D34EFF
                DCD     0x4B135805
                DCD     0x6206FB8F
                DCD     0xDDCB53CD
                DCD     0x690DC509
                DCD     0x799452D3
                DCD     0x3AA73B48
                DCD     0xA9F1EAB5
                DCD     0x152E9D06
                DCD     0xB98949B2
                DCD     0x6C2C0613
                DCD     0xE3228831
                DCD     0x00171EAC
                DCD     0xA95E7136
                DCD     0x29C75246
                DCD     0xA3951D16
                DCD     0x38FD57F6
                DCD     0x8F5E987C
                DCD     0xCFA38874
                DCD     0x0BBD6D71
                DCD     0xD1765C41
                DCD     0x2593C701
                DCD     0xC8EC0F70
                DCD     0xB3D691C0
                DCD     0x91BA2F33
                DCD     0x80D6AB33
                DCD     0xA1D1A50D
                DCD     0x58F73EE6
                DCD     0x78D57E5E
                DCD     0x53A0B1C3
                DCD     0x868E74A6
                DCD     0x0642C7DB
                DCD     0x493D11A8
                DCD     0xCE14F3BF
                DCD     0x6CADE060
                DCD     0xFA2AE325
                DCD     0x60970067
        
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
; End of ca7_advsimd_functional.s
;-------------------------------------------------------------------------------
                END
