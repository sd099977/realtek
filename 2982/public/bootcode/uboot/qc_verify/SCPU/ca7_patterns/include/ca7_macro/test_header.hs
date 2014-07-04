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
;      Checked In          : $Date: 2010-03-18 10:22:30 +0000 (Thu, 18 Mar 2010) $
;
;      Revision            : $Revision: 134371 $
;
;      Release Information : CORTEX-A7-r0p4-00rel0
;
;-------------------------------------------------------------------------------

                GET     macros.hs
                ; GET     dap_macros.hs ; Chuck modified
                GET     configuration

                MACRO
                TEST_HEADER
;======================== Vector Table ====================================
                ; Make first in link order by using ascii space
                AREA    | Header CODE|, CODE

VecTable
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
                LDR     pc, [pc,#0x18]
ExcpTable
                DCD     ResetHandler
                DCD     UndefHandler
                DCD     SVCHandler
                DCD     PrefAbortHandler
                DCD     DataAbortHandler
                DCD     NotUsed
                DCD     IRQHandler
                DCD     FIQHandler

;-------------------------------------------------------------------------------
; Exception handlers
;-------------------------------------------------------------------------------

ResetHandler
                B       Main
UndefHandler
                B       DefaultHandler
SVCHandler
                B       DefaultHandler
PrefAbortHandler
                B       DefaultHandler
DataAbortHandler
                B       DefaultHandler
NotUsed
                B       DefaultHandler
IRQHandler
                B       DefaultHandler
FIQHandler
                B       DefaultHandler

DefaultHandler
                ; Switch back to supervisor mode
                CPS     #0x13
                MESSAGE "** UNEXPECTED EXCEPTION has occurred **\n"
                B       HeaderFail


;for our testbed
TST_FAIL_ADDR   EQU     0x13000288  ;?????
TST_PASS_ADDR   EQU     0x1300028C  ;?????

;TST_FAIL_ADDR   EQU     0xa1000288  ;?????
;TST_PASS_ADDR   EQU     0xa100028C  ;?????

;-------------------------------------------------------------------------------
; Failure messages
;-------------------------------------------------------------------------------
HeaderFail
                TEST_FAIL

                LTORG
;-------------------------------------------------------------------------------
; Main Area
; This is the area used for the main test code
; It can be relocated in the memory map as desired
;-------------------------------------------------------------------------------
                AREA    |Main CODE|, CODE, ALIGN=12
Main
                ; Initialize registers
                PUSH {r4-r12,lr}            
                MOV     r0,  #0
                MOV     r1,  #0
                MOV     r2,  #0
                MOV     r3,  #0
                MOV     r4,  #0
                MOV     r5,  #0
                MOV     r6,  #0
                MOV     r7,  #0
                MOV     r8,  #0
                MOV     r9,  #0
                MOV     r10, #0
                MOV     r11, #0
                MOV     r12, #0
                ;MOV     r13, #0
                MOV     r14, #0

                ; Clear CPSR I, F and A bits to enable interrupts (IRQs and FIQs)
                ; and imprecise data aborts
                CPSIE   ifa

                ; Set SCTLR A bit to enable alignment fault checking
                MRC     p15, 0, r0, c1, c0, 0
                ORR     r0, r0, #(1<<1)
                MCR     p15, 0, r0, c1, c0, 0

                MEND

        END
