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
;      Checked In          : $Date: 2010-04-23 12:15:15 +0100 (Fri, 23 Apr 2010) $
;
;      Revision            : $Revision: 137202 $
;
;      Release Information : CORTEX-A7-r0p4-00rel0
;
;-------------------------------------------------------------------------------
;
; Description
; -----------
;
; Generic macros.
;
; Macros defined in this file:
; ---------------------------
;
;       DEFAULT_VAR
;       DEFAULT_SETS
;       DEFAULT_SETL
;       DEFAULT_SETA
;       CONFIG_SETS
;       CONFIG_SETL
;       CONFIG_SETA
;       LOCAL
;       LOCAL_END
;       LOCAL_REFER
;       MESSAGE
;       TEST_PASS
;       TEST_FAIL
;       TEST_FINISH
;       FPU_PRESENT
;       ENABLE_FPU
;       NEON_PRESENT
;       INVALIDATE_DCACHE
;       INVALIDATE_DCACHE_LINE
;       CLEAN_INVALIDATE_DCACHE_LINE
;       ENABLE_MMU
;       DISABLE_MMU
;       DISABLE_CACHES
;       ENABLE_CACHES
;       TT_SECTION_WRITE
;       NEON_TEST
;       NEON_INTLK_TEST
;       CPU_CACHE_SIZE
;       CPU_EXTENSION
;       CPU_NBCORE
;       CPU_READ_DBGROM
;       BST
;       BST_END
;       BST_START
;       BST_BEGIN
;       NOPx
;       SET_EXCEPTION
;       RESTORE_EXCEPTION
;
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Macro:        <variable> DEFAULT_VAR <type>, <value>, [override]
;
; Purpose:      Define a variable if undefined, or if override specified
;		and the variable was previously defined by a DEFAULT_VAR
;
; Internally:   No registers, simply uses precompile directives
;-------------------------------------------------------------------------------

                MACRO
$variable       DEFAULT_VAR  $type, $value, $override
		[		:LNOT::DEF: $variable
		GBLL		DEFINED_$variable
		GBL$type	$variable
		[	"$type" = "S"
$variable	SET$type	"$value"
		|
$variable	SET$type	$value
		]
		|
		[	"$override" /= "" :LAND::DEF: DEFINED_$variable
		[	"$type" = "S"
$variable	SET$type	"$value"
		|
$variable	SET$type	$value
		]
		]
		]
		MEND

;-------------------------------------------------------------------------------
; Macro:        <variable> DEFAULT_SETS <value>
;               <variable> DEFAULT_SETL <value>
;               <variable> DEFAULT_SETA <value>
;
; Purpose:      Wrapper for DEFAULT_VAR, defining precompile directives
;
;
; Internally:   No registers, simply uses precompile directives
;-------------------------------------------------------------------------------

                MACRO
$variable       DEFAULT_SETS $value
$variable       DEFAULT_VAR  S, $value
		MEND

                MACRO
$variable       DEFAULT_SETL $value
$variable       DEFAULT_VAR  L, $value
                MEND

                MACRO
$variable       DEFAULT_SETA $value
$variable       DEFAULT_VAR  A, $value
                MEND

;-------------------------------------------------------------------------------
; Macro:        <variable> CONFIG_SETS <value>
;               <variable> CONFIG_SETL <value>
;               <variable> CONFIG_SETA <value>
;
; Purpose:      Wrapper for DEFAULT_VAR, defining precompile directives,
;               overwrite if previously defined.
;
;
; Internally:   No registers, simply uses precompile directives
;-------------------------------------------------------------------------------

                MACRO
$variable       CONFIG_SETS $value
$variable       DEFAULT_VAR  S, $value, 1
		MEND

                MACRO
$variable       CONFIG_SETL $value
$variable       DEFAULT_VAR  L, $value, 1
                MEND

                MACRO
$variable       CONFIG_SETA $value
$variable       DEFAULT_VAR  A, $value, 1
                MEND

;-------------------------------------------------------------------------------
; Macro:        LOCAL
;               LOCAL_END
;               LOCAL_REFER <symbol> [,<offset>]
;               <label>$l
;
; Purpose:      Local label generation for functions and macros. For each new
;               routine or macro desiring local labelling use, for example:
;
;                       LOCAL           ; enters a deeper nesting level
;               Rout    [code]          ; globally visible label
;               loop$l  [code]          ; local label declaration
;                       BNE     loop$l  ; local label usage
;                       [code]
;                       LOCAL_END       ; restore to previous nesting level
;
;               Local labelling can be nested down to 16 levels (including no
;               nesting). Each LOCAL --MUST-- have a corresponding LOCAL_END,
;               so care must be taken when using conditional assembly and in
;               macros when using MEXIT.
;
;               The scope of labels is only within the current and global
;               (ie normal labelling) contexts. To refer to a higher nesting
;               level use (with a relative offset), for example:
;
;                       LOCAL_REFER foo         ; foo=$l using current nesting
;               val$l   DCD     0
;                       LOCAL
;                       LOCAL_REFER bar, 1        ; bar=$l of previous nesting
;                       STR     r0,val$foo        ; refer to val$l
;                       LDR     r0,val$bar        ; refer to val$l
;                       LOCAL_END
;                       LDR     r0,val$l
;
; Internally:   No registers, simply increments a counter for each use
;-------------------------------------------------------------------------------

LocalNesting    DEFAULT_SETA 0
LocalCount      DEFAULT_SETA 0
LocalTemp       DEFAULT_SETA 0
l               DEFAULT_SETS "_$LocalCount"

                WHILE       LocalTemp <= 15
                GBLA        LocalArray$LocalTemp
LocalTemp       SETA        LocalTemp + 1
                WEND

SECTION         EQU   (0x00000002)
FAULT           EQU   (0x00000000)

GLOBAL          EQU   (0x00000000)
NONGLOBAL       EQU   (0x00020000)

EXE             EQU   (0x00000000)
NON_EXE         EQU   (0x00000010)

RW              EQU   (0x00000C00)   ; Both user and priv, read/write
RO              EQU   (0x00008800)   ; Both user and priv, read only
PRIV_ONLY       EQU   (0x00000400)   ; Priv read/write, user no access
PRIV_USER_RO    EQU   (0x00000800)   ; Priv read/write, user read-only
NOACCESS        EQU   (0x00000000)

WB              EQU   (0x0000000C)   ; Write back
WT              EQU   (0x00000008)   ; Write through
NO_CACHE        EQU   (0x00001000)   ; no cache or buffer
SDEVICE         EQU   (0x00000004)   ; shared device
NSDEVICE        EQU   (0x00002000)   ; non shared device
SORDERED        EQU   (0x00000000)   ; strongly ordered

SHARED          EQU   (0x00010000)    ; Used for NORMAL types only
NON_SHARED      EQU   (0x00000000)    ; Used for NORMAL types only

;-------------------------------------------------------------------------------
; Macro:        LOCAL
;-------------------------------------------------------------------------------
                MACRO
$label          LOCAL
                OPT        32+8192                                ; no vars and conditionals
$label
                [ LocalNesting > 15
                !        1, "\n\n\tLOCAL label nesting too deep (max 16)."
                MEXIT
                ]
LocalNesting    SETA        LocalNesting + 1
LocalCount      SETA        LocalCount + 1
LocalArray$LocalNesting SETA LocalCount
l               SETS        "_$LocalCount"
                MEND

;-------------------------------------------------------------------------------
; Macro:        LOCAL_END
;-------------------------------------------------------------------------------
                MACRO
$label          LOCAL_END
                OPT        32+8192                                ; no vars and conditionals
$label
                [ LocalNesting <= 0
                !        1, "\n\n\tLOCAL_END has no matching LOCAL."
                MEXIT
                ]
LocalNesting    SETA        LocalNesting - 1
LocalTemp       SETA        LocalArray$LocalNesting
l               SETS        "_$LocalTemp"
                MEND

;-------------------------------------------------------------------------------
; Macro:        LOCAL_REFER
;-------------------------------------------------------------------------------
                MACRO
$label          LOCAL_REFER $sym, $offset
$label
                GBLS        $sym
                [        "$offset" = ""
LocalTemp       SETA        LocalNesting
                |
                [ (LocalNesting - $offset) <= 0
                !        1, "\n\n\tLOCAL_REFER to bad nesting level."
                MEXIT
                ]
LocalTemp       SETA        LocalNesting - $offset
                ]
LocalTemp       SETA        LocalArray$LocalTemp
$sym            SETS        "_$LocalTemp"
                MEND

;-------------------------------------------------------------------------------
; MACRO:        MESSAGE
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                MESSAGE $string, $force
                LOCAL
                [ :LNOT:SUPPRESS_MESSAGES:LOR:"$force" != ""
                ; Save used registers.
                PUSH    {r0-r5}
                B start$l
                ALIGN 4
str$l           DCB "$string",0
                ALIGN 4
start$l

;;                MRC     p15, 0, r0, c0, c0, 5        ; read MPIDR
;;                AND     r0, r0, #0x3                 ; extract bits [1:0] (CPU ID)
;;                LSL     r0, #0x2

;;                LDR     r1, =TBVAL_SYSADDR
									LDR			r1, =0x18062300
;mask in our testbed
;due to only one address for uart print for all cpus
                ;ORR     r1, r1, r0
                LDR     r0, =str$l
loop$l
                ; Load in 4 bytes at a time
                LDR     r2, [r0], #4
                [ BIGENDIAN
                MOV     r5, r2
                MOV     r4, r2, LSR #8
                MOV     r3, r2, LSR #16
                MOV     r2, r2, LSR #24
                |
                MOV     r3, r2, LSR #8
                MOV     r4, r2, LSR #16
                MOV     r5, r2, LSR #24
                ]
                ; Compare each value with NULL terminator
                ; and finish the loop if found
                ANDS    r2, r2, #0xFF
                BEQ     skip$l
                STRB    r2, [r1]               
                CMPS		r2,#13
                BEQ			skip$l
                ANDS    r3, r3, #0xFF
                BEQ     skip$l
                STRB    r3, [r1]
                CMPS		r3,#13
                BEQ			skip$l
                ANDS    r4, r4, #0xFF
                BEQ     skip$l
                STRB    r4, [r1]
                CMPS		r4,#13
                BEQ			skip$l
                ANDS    r5, r5, #0xFF
                BEQ     skip$l
                STRB    r5, [r1]
                CMPS		r5,#13
                BEQ			skip$l
                B       loop$l               
                LTORG
skip$l
                ; Restore used registers.            
                POP     {r0-r5}
                ]
                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        TEST_PASS
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                TEST_PASS
                ;TEST_FINISH "** TEST PASSED OK **\n"
                MOV     r0, #0
                POP     {r4-r12,pc}
                MEND

;-------------------------------------------------------------------------------
; MACRO:        TEST_FAIL
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                TEST_FAIL
                ;TEST_FINISH "** TEST FAILED **\n"
                MOV     r0, #-1
                POP     {r4-r12,pc}
                MEND

;-------------------------------------------------------------------------------
; MACRO:        TEST_FINISH
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                TEST_FINISH $msg
                LOCAL
                [ "$msg" /= ""	;TODO
                MESSAGE $msg, 1
                ]
skip$l
                MRC     p15, 0, r0, c0, c0, 5        ; read MPIDR
                AND     r0, r0, #0x3                 ; extract bits [1:0] (CPU ID)
                LSL     r0, #0x2

                LDR     r1, =TBVAL_SYSADDR
                ORR     r1, r1, r0
                MOV     r0, #0x04
                STRB    r0, [r1]                
here$l
                B here$l
                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        FPU_PRESENT
;
; Purpose:      Checks if FPU is present
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                FPU_PRESENT $reg

                MOV     $reg,#0xf00000               ; Write CPACR (Coprocessor Access Control Register)
                MCR     p15,0,$reg,c1,c0,2           ; to enable coprocessors cp10 & cp11
                MRC     p15,0,$reg,c1,c0,2           ; Read CPACR
                UBFX    $reg, $reg, #20, #1          ; if bit 20 is zero then so the bits 23:21 so FPU present
                MEND

;-------------------------------------------------------------------------------
; MACRO:        ENABLE_FPU
;
; Purpose:      Enable FPU and initialise FPSR and d0-d15 registers
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                ENABLE_FPU
                PUSH    {r0}
                MOV	r0,#1<<30
                MCR     p10, #7, r0, c8, c0, 0                 ; enable FPU by writing FPEXC
                MOV	r0,#0
                MCR     p10, #7, r0, c1, c0, 0                 ; init FPSR
                LDC	p11, c0, [r0], {32}                    ; init registers d0-d15
                POP     {r0}
		MEND
		
;-------------------------------------------------------------------------------
; MACRO:        NEON_PRESENT
;
; Purpose:      Checks if NEON is present
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                NEON_PRESENT $reg

                MOV     $reg,#0xf00000               ; Write CPACR (Coprocessor Access Control Register)
                MCR     p15,0,$reg,c1,c0,2           ; to enable coprocessors cp10 & cp11
                MRC     p15,0,$reg,c1,c0,2           ; Read CPACR;
 		CMP     $reg, #0x00f00000            ; if cp10 & cp11 are enabled and bit 31 is zero then NEON present
                MOVEQ   $reg, #1
                MOVNE   $reg, #0
                MEND


;-------------------------------------------------------------------------------
; MACRO:        INVALIDATE_DCACHE
;
; Purpose:      Invalidate and clean DCache
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                INVALIDATE_DCACHE
                MRC     p15, 1, r0, c0, c0, 0       ; Read the Cache Size Identification register (CCSIDR)
                MOV     r0, r0, LSL #10
                MOV     r0, r0, LSR #23             ; Mask off to leave the NumSets

                MOV     r2, #0x0                    ; Set r2 to initial MVA (Way=0, Set=0)
                MOV     r1, #0                      ; Use r1 as loop counter for WAYs
                MOV     r3, #0x0                    ; Use r3 as a loop counter for SETs

invalidate_cache_loop
                MCR     p15, 0, r2, c7, c6, 2       ; DCISW - Invalidate data cache by set/way
                ADD     r2, r2, #0x0020             ; Increment the SET field

                ADD     r3, r3, #1                  ; Increment loop counter
                CMP     r3, r0                      ; Compare loop counter with num_sets
                BLE     invalidate_cache_loop       ; If (loop_counter =< num_sets) branch
                                                    ; Prepare register for next pass
                ADD     r2, r2, #0x40000000         ; Increment WAY field
                AND     r2, r2, #0xC0000000         ; Clear the rest of the register (clear the SET field)
                MOV     r3, #0                      ; Reset loop counter

                ADD     r1, r1, #1
                CMP     r1, #4
                BNE     invalidate_cache_loop
                MEND

;-------------------------------------------------------------------------------
; MACRO:        INVALIDATE_DCACHE_LINE
;
; Purpose:      Invalidate a line from the data cache by virtual address
;
; Parameters:   Register containing the Virtual Address to invalidate
;-------------------------------------------------------------------------------
                MACRO
                INVALIDATE_DCACHE_LINE $va
		MCR	p15, 0, $va, c7, c6, 1
                MEND

;-------------------------------------------------------------------------------
; MACRO:        CLEAN_INVALIDATE_DCACHE_LINE
;
; Purpose:      Clean and Invalidate a line from the data cache by virtual address
;
; Parameters:   Register containing the Virtual Address to invalidate
;-------------------------------------------------------------------------------
                MACRO
                CLEAN_INVALIDATE_DCACHE_LINE $va
		MCR	p15, 0, $va, c7, c14, 1
                MEND

;-------------------------------------------------------------------------------
; MACRO:        ENABLE_MMU
;
; Purpose:      Enable MMU
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
		ENABLE_MMU
                DSB
                MRC     p15, 0, r0, c1, c0, 0       ; Read SCTLR - System Control Register
                ORR     r0, r0, #0x01               ; Set M bit (bit 0)
                MCR     p15, 0, r0, c1, c0, 0       ; Write SCTLR
		ISB
		MEND

;-------------------------------------------------------------------------------
; MACRO:        DISABLE_MMU
;
; Purpose:      Disable MMU
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
		DISABLE_MMU
                DSB
                MRC     p15, 0, r0, c1, c0, 0       ; Read SCTLR - System Control Register
                BIC     r0, r0, #1                  ; Clear M bit (bit 0)
                MCR     p15, 0, r0, c1, c0, 0       ; Write SCTLR
		ISB
		MEND

;-------------------------------------------------------------------------------
; MACRO:        DISABLE_CACHES
;
; Purpose:      Disable instruction and data caches
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
		DISABLE_CACHES
                MRC     p15, 0, r0, c1, c0, 0       ; Read SCTLR into r0
                BIC     r0, r0, #0x00004            ; disable data cache
                BIC     r0, r0, #0x01000            ; disable instruction cache
                MCR     p15, 0, r0, c1, c0, 0
		MEND

;-------------------------------------------------------------------------------
; MACRO:        ENABLE_CACHES
;
; Purpose:      Enable instruction and data caches
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
		ENABLE_CACHES
                MRC     p15, 0, r0, c1, c0, 0       ; Read System Control Register configuration data
                ORR     r0, r0, #0x0004             ; Set C bit
                ORR     r0, r0, #0x1000             ; Set I bit
                MCR     p15, 0, r0, c1, c0, 0       ; Write System Control Register configuration data
		MEND

;-------------------------------------------------------------------------------
; MACRO:        OS_UNLOCK $faillabel
;
; Purpose:      Unlock OS
;-------------------------------------------------------------------------------
                MACRO
                OS_UNLOCK $faillabel
                LOCAL
                PUSH    {r0}
                LDR     r0, =0x0
                MCR     p14,0,r0,c1,c0,4           ; remove OS lock by writing to DBGOSLAR register
                MRC     p14,0,r0,c1,c1,4           ; read DBGOSLSR[1] to check if unlocked
                UBFX    r0, r0, #1, #1
                CMP     r0, #0x0
                BNE     macro_fail$l
                B       macro_end$l
macro_fail$l
                POP     {r0}
                B       $faillabel
macro_end$l
                POP   {r0}
                LOCAL_END
                MEND


;-------------------------------------------------------------------------------
; MACRO:        TT_SECTION_WRITE
;
; Purpose:      Create a translation table section
;
; Parameters:   x
;-------------------------------------------------------------------------------
	
; -----------------------------------------------------------------------------------------------
; 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
; -----------------------------------------------------------------------------------------------
; | Address                         | 0  0  nG S  AP|  TEX   | AP  |P |  Domain   |XN| B C | 1  0   - Section
; -----------------------------------------------------------------------------------------------
; | Ignored                                                                                | 0  0   - Abort
; -----------------------------------------------------------------------------------------------
		MACRO	
    		TT_SECTION_WRITE $pa, $va, $mem_attr

		LDR     r0, =$pa
		LDR     r1, =$va
		LDR     r2, =$mem_attr 		
                MRC     p15, 0, r3, c2, c0 ,0       ; read ttb
                ORR     r0, r0, r2                  ; add control bits to physical address
		ORR     r0, r0, #2
                STR     r0,[r3, r1, LSR #18]        ; obtain MB offset from page (LSR), add to ttb and store page to this location
                DMB
		MEND

;-------------------------------------------------------------------------------
; MACRO:        NEON_TEST
;
; Purpose:      Move values into Neon register
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
$Label          NEON_TEST \
                $fail_label, \
                $sFlag, $eFlag, \
                $i_dval1, $i_dval2, \
                $i_dval3, $i_dval4, \
                $i_reg1, $i_reg2, $i_reg3, $i_reg4, \
                $e_dval1, $e_dval2, \
                $e_dval3, $e_dval4, \
                $e_reg1, $e_reg2, $e_reg3, $e_reg4, \
                $e_rval0, $e_rval1, $e_rval2, \
                $instr0, \
                $instr1, \
                $instr2, \
                $instr3, \
                $instr4, \
                $instr5, \
                $instr6, \
                $instr7

                LOCAL

                PUSH    {r0-r12}
        ; Program flag bits of CPSR register
                [       "$sFlag" /= "-"
                LDR     r0,=$sFlag
                MSR     CPSR_sf,r0                      ; Set flags
                |
                MOV     r0,#0
                MSR     CPSR_sf,r0                      ; Reset flags
                ]

        ; Initialise registers to zero
                MOV     r0, #0x0
                MOV     r1, #0x0
                MOV     r2, #0x0
                MOV     r3, #0x0
                MOV     r4, #0x0
                MOV     r5, #0x0
                MOV     r6, #0x0
                MOV     r7, #0x0
                MOV     r8, #0x0
                MOV     r9, #0x0
                MOV     r10, #0x0
                MOV     r11, #0x0
                MOV     r12, #0x0

;               RESET_D0_TO_D31
                LDR r0,  =zero
		VLD1.32  { d0[],d1[]}, [r0]
		VLD1.32  { d2[],d3[]}, [r0]
		VLD1.32  { d4[],d5[]}, [r0]
		VLD1.32  { d6[],d7[]}, [r0]
		VLD1.32  { d8[],d9[]}, [r0]
		VLD1.32  {d10[],d11[]}, [r0]
		VLD1.32  {d12[],d13[]}, [r0]
		VLD1.32  {d14[],d15[]}, [r0]
		VLD1.32  {d16[],d17[]}, [r0]
		VLD1.32  {d18[],d19[]}, [r0]
		VLD1.32  {d20[],d21[]}, [r0]
		VLD1.32  {d22[],d23[]}, [r0]
		VLD1.32  {d24[],d25[]}, [r0]
		VLD1.32  {d26[],d27[]}, [r0]
		VLD1.32  {d28[],d29[]}, [r0]
		VLD1.32  {d30[],d31[]}, [r0]

        ; Initialise the value of input register1
                [       "$i_reg1" /= "-" :LAND: "$i_dval1" /= "-"
                ADR r0, i_dval1$l
                VLDR $i_reg1, [r0]
                ]

        ; Initialise the value of input register2
                [       "$i_reg2" /= "-" :LAND: "$i_dval2" /= "-"
                ADR r0, i_dval2$l
                VLDR $i_reg2, [r0]
                ]

        ; Initialise the value of input register3
                [       "$i_reg3" /= "-" :LAND: "$i_dval3" /= "-"
                ADR r0, i_dval3$l
                VLDR $i_reg3, [r0]
                ]

        ; Initialise the value of input register4
                [       "$i_reg4" /= "-" :LAND: "$i_dval4" /= "-"
                ADR r0, i_dval4$l
                VLDR $i_reg4, [r0]
                ]

        ; Execute the instruction sequence

0               $instr0
1               $instr1
2               $instr2
3               $instr3
4               $instr4
5               $instr5
6               $instr6
7               $instr7

                MRS     r12,CPSR                        ; Copy CPSR in R2 just after
                                                        ; executing the IUT
        ; Check CPSR flags
                [       "$eFlag" /= "-"
                LDR     r10,=$eFlag
                LDR     r11,=CPSR_FLGS_MASK
                AND     r11,r11,r12
                TEQ     r10,r11
                BNE     $fail_label
                ]

        ; Check value of R0 register
                [       "$e_rval0" /= "-"
                LDR     r10,=$e_rval0
                TEQ     r0,r10
                BNE     $fail_label
                ]

        ; Check value of R1 register
                [       "$e_rval1" /= "-"
                LDR     r10,=$e_rval1
                TEQ     r1,r10
                BNE     $fail_label
                ]

        ; Check value of R2 register
                [       "$e_rval2" /= "-"
                LDR     r10,=$e_rval2
                TEQ     r2,r10
                BNE     $fail_label
                ]

        ; Check the value of the first output dw register
                [       "$e_dval1" /= "-" :LAND: "$e_reg1" /= "-"
                LDR     r0,=store_DW1$l
                LDRD    r10, [r0]
                VMOV    r0, r1, $e_reg1
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the second output dw register
                [       "$e_dval2" /= "-" :LAND: "$e_reg2" /= "-"
                LDR     r0,=store_DW2$l
                LDRD    r10, [r0]
                VMOV    r0, r1, $e_reg2
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the third output dw register
                [       "$e_dval3" /= "-" :LAND: "$e_reg3" /= "-"
                LDR     r0,=store_DW3$l
                LDRD    r10, [r0]
                VMOV    r0, r1, $e_reg3
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the fourth output dw register
                [       "$e_dval4" /= "-" :LAND: "$e_reg4" /= "-"
                LDR     r0,=store_DW4$l
                LDRD    r10, [r0]
                VMOV    r0, r1, $e_reg4
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

                B       TestEnd$l

                LTORG
                ALIGN 4

                [       "$e_dval1" /= "-" :LAND: "$e_reg1" /= "-"
store_DW1$l     DCQ     $e_dval1
                ]
                [       "$e_dval2" /= "-" :LAND: "$e_reg2" /= "-"
store_DW2$l     DCQ     $e_dval2
                ]
                [       "$e_dval3" /= "-" :LAND: "$e_reg3" /= "-"
store_DW3$l     DCQ     $e_dval3
                ]
                [       "$e_dval4" /= "-" :LAND: "$e_reg4" /= "-"
store_DW4$l     DCQ     $e_dval4
                ]
                [       "$i_reg1" /= "-" :LAND: "$i_dval1" /= "-"
i_dval1$l       DCQ     $i_dval1
                ]
                [       "$i_reg2" /= "-" :LAND: "$i_dval2" /= "-"
i_dval2$l       DCQ     $i_dval2
                ]
                [       "$i_reg3" /= "-" :LAND: "$i_dval3" /= "-"
i_dval3$l       DCQ     $i_dval3
                ]
                [       "$i_reg4" /= "-" :LAND: "$i_dval4" /= "-"
i_dval4$l       DCQ     $i_dval4
                ]

                ALIGN

TestEnd$l       
                POP     {r0-r12}
		LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        NEON_INTLK_TEST
;
; Purpose:      Check if the destination registers have the expected results
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
$Label          NEON_INTLK_TEST \
                $fail_label, \
                $sFlag, $eFlag, \
                $e_dval1, $e_dval2, \
                $e_dval3, $e_dval4, \
                $e_dval5, $e_dval6, \
                $e_reg1, $e_reg2, $e_reg3, $e_reg4, $e_reg5, $e_reg6, \
                $e_rval1,$e_rval2,$e_rval3,$e_rval4, \
                $e_rreg1,$e_rreg2,$e_rreg3,$e_rreg4, \
                $instr0, \
                $instr1, \
                $instr2, \
                $instr3, \
                $instr4, \
                $instr5, \
                $instr6, \
                $instr7

                LOCAL

                PUSH    {r0-r12}
        ; Program flag bits of CPSR register
                [       "$sFlag" /= "-"
                LDR     r0,=$sFlag
                MSR     CPSR_sf,r0                      ; Set flags
                |
                MOV     r0,#0
                MSR     CPSR_sf,r0                      ; Reset flags
                ]

        ; Reset ARM registers
                MOV     r0, #0x0
                MOV     r1, #0x0
                MOV     r2, #0x0
                MOV     r3, #0x0
                MOV     r4, #0x0
                MOV     r5, #0x0
                MOV     r6, #0x0
                MOV     r7, #0x0
                MOV     r8, #0x0
                MOV     r9, #0x0
                MOV     r10, #0x0
                MOV     r11, #0x0
                MOV     r12, #0x0

        ; Initialize neon registers
                LDR     r0, =INTL_DATA_ADDR
		VLD1.32 {d0,  d1,  d2,  d3 }, [r0]!
		VLD1.32 {d4,  d5,  d6,  d7 }, [r0]!
		VLD1.32 {d8,  d9,  d10, d11}, [r0]!
		VLD1.32 {d12, d13, d14, d15}, [r0]!
		VLD1.32 {d16, d17, d18, d19}, [r0]!
		VLD1.32 {d20, d21, d22, d23}, [r0]!
		VLD1.32 {d24, d25, d26, d27}, [r0]!
		VLD1.32 {d28, d29, d30, d31}, [r0]!
		
        ; Execute the instruction sequence

0               $instr0
1               $instr1
2               $instr2
3               $instr3
4               $instr4
5               $instr5
6               $instr6
7               $instr7

                MRS     r2,CPSR                         ; Copy CPSR in R2 just after
                                                        ; executing the IUT
        ; Check CPSR flags
                [       "$eFlag" /= "-"
                LDR     r0,=$eFlag
                LDR     r1,=CPSR_FLGS_MASK
                AND     r1,r1,r2
                TEQ     r0,r1
                BNE     $fail_label
                ]

        ; Check for the first ARM destination register
                [       "$e_rreg1" /= "-" :LAND: "$e_rval1" /= "-"
                MOV     r5,$e_rreg1
                LDR     r4,=$e_rval1
                LDR     r11, =e_rreg1$l
                TEQ     r4,r5
                BNE     $fail_label
                ]

        ; Check for the second ARM destination register
                [       "$e_rreg2" /= "-" :LAND: "$e_rval2" /= "-"
                MOV     r5,$e_rreg2
                LDR     r4,=$e_rval2
                LDR     r11, =e_rreg2$l
                TEQ     r4,r5
                BNE     $fail_label
                ]

        ; Check for the third ARM destination register
                [       "$e_rreg3" /= "-" :LAND: "$e_rval3" /= "-"
                MOV     r5,$e_rreg3
                LDR     r4,=$e_rval3
                LDR     r11, =e_rreg3$l
                TEQ     r4,r5
                BNE     $fail_label
                ]

        ; Check for the fourth ARM destination register
                [       "$e_rreg4" /= "-" :LAND: "$e_rval4" /= "-"
                MOV     r5,$e_rreg4
                LDR     r4,=$e_rval4
                LDR     r11, =e_rreg4$l
                TEQ     r4,r5
                BNE     $fail_label
                ]

        ; Check the value of the first output dw register
                [       "$e_dval1" /= "-" :LAND: "$e_reg1" /= "-"
                LDR     r0,=store_DW1$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg1
		|
                VMOV    r0, r1, $e_reg1
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the second output dw register
                [       "$e_dval2" /= "-" :LAND: "$e_reg2" /= "-"
                LDR     r0,=store_DW2$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg2
		|
                VMOV    r0, r1, $e_reg2
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the third output dw register
                [       "$e_dval3" /= "-" :LAND: "$e_reg3" /= "-"
                LDR     r0,=store_DW3$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg3
		|
                VMOV    r0, r1, $e_reg3
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the fourth output dw register
                [       "$e_dval4" /= "-" :LAND: "$e_reg4" /= "-"
                LDR     r0,=store_DW4$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg4
		|
                VMOV    r0, r1, $e_reg4
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the fifth output dw register
                [       "$e_dval5" /= "-" :LAND: "$e_reg5" /= "-"
                LDR     r0,=store_DW5$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg5
		|
                VMOV    r0, r1, $e_reg5
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

        ; Check the value of the sixth output dw register
                [       "$e_dval6" /= "-" :LAND: "$e_reg6" /= "-"
                LDR     r0,=store_DW6$l
                LDRD    r10, [r0]
		[ BIGENDIAN
		VMOV    r1, r0, $e_reg6
		|
                VMOV    r0, r1, $e_reg6
		]
                TEQ     r0,r10
                TEQEQ   r1,r11
                BNE     $fail_label
                ]

                B       TestDone$l

                ALIGN 4

                [       "$e_dval1" /= "-" :LAND: "$e_reg1" /= "-"
store_DW1$l     DCQ     $e_dval1
                ]
                [       "$e_dval2" /= "-" :LAND: "$e_reg2" /= "-"
store_DW2$l     DCQ     $e_dval2
                ]
                [       "$e_dval3" /= "-" :LAND: "$e_reg3" /= "-"
store_DW3$l     DCQ     $e_dval3
                ]
                [       "$e_dval4" /= "-" :LAND: "$e_reg4" /= "-"
store_DW4$l     DCQ     $e_dval4
                ]
                [       "$e_dval5" /= "-" :LAND: "$e_reg5" /= "-"
store_DW5$l     DCQ     $e_dval5
                ]
                [       "$e_dval6" /= "-" :LAND: "$e_reg6" /= "-"
store_DW6$l     DCQ     $e_dval6
                ]

                ALIGN
		
TestDone$l
                POP     {r0-r12}
                LOCAL_END
                MEND


;-------------------------------------------------------------------------------
; MACRO:        CPU_CACHE_SIZE
;
; Purpose:      Report Cache Size configuration
;
; Parameters:   $cpuid     : CPU ID (0, 1, 2 or 3)
;               $type      : cache type, either "I" or "D"
;               $data_size : optional label, storing cache size information
;               $error_run : optional label, handling erroneous cache size
;               $error_cfg : optional label, handling erroneous test configuration
;-------------------------------------------------------------------------------

                MACRO
                CPU_CACHE_SIZE $type, $data_size, $error_run, $error_cfg
                LOCAL

       ; Macro parameter check
                [ "$type" /= ""
                |
                !        1, "\nError, missing macro input parameter"
                MEXIT
                ]
                [ "$type" /= "I" :LAND: "$type" /= "D"
                !        1, "\nError, wrong macro input type parameter"
                MEXIT
                ]

       ; Local strings
                LCLS    cpu_cache_size
cpu_cache_size  SETS    "L1":CC:"_":CC:"$type":CC:"CACHE_SIZE"

       ; Ensure registers are not corrupted
                PUSH    {r0-r2}
       ; Get Cache size: First, writing the Cache Size Selection Register
       ; (CSSELR) to select ICache or DCache, then reading Cache Size
       ; Identification Register (CSIDR) to extract the NumSets field
       ; (bit[27:13])
                [ "$type" == "I"
                MOV     r0, #1
                |
                MOV     r0, #0
                ]
                MCR     p15, 2, r0, c0, c0, 0        ; write Cache Size Selection Register - CSSELR
                MRC     p15, 1, r1, c0, c0, 0        ; read Cache Size Identification Register - CCSIDR
                UBFX    r2, r1, #13, #15
                [ "$type" == "I"
                LDR     r1, =0x3ff
                |
                LDR     r1, =0x0ff
                ]
                LDR     r0, =$cpu_cache_size

       ; Common message (1rst part)
                MESSAGE "   . $type-Cache Size: "
       ; Cache size message (2nd part)
                CMP     r2, r1
                BEQ     msg_64k$l
                CMP     r2, r1, LSR #1
                BEQ     msg_32k$l
                CMP     r2, r1, LSR #2
                BEQ     msg_16k$l
                CMP     r2, r1, LSR #3
                BEQ     msg_8k$l
                
       ; This code should not be reached
                [ "$error_run" /= ""
                B       $error_run
                |
                MESSAGE "UNKNOWN\n"
                MESSAGE "This code should not be reached\n"
                TEST_FAIL
                ]

msg_64k$l
                MESSAGE "64KB\n"
                CMP     r0, #64
                BNE     msg_err$l
                B       cache_size_end$l

msg_32k$l
                MESSAGE "32KB\n"
                CMP     r0, #32
                BNE     msg_err$l
                B       cache_size_end$l
msg_16k$l
                MESSAGE "16KB\n"
                CMP     r0, #16
                BNE     msg_err$l
                B       cache_size_end$l
msg_8k$l
                MESSAGE "8KB\n"
                CMP     r0, #8
                BNE     msg_err$l
                B       cache_size_end$l

msg_err$l
                [ "$error_cfg" /= ""
                B       $error_cfg
                |
                MESSAGE "\nConfiguration mismatch between test and RTL\n"
                TEST_FAIL
                ]
cache_size_end$l
                [ "$data_size" /= ""
                LDR     r0, =$data_size
                STR     r2, [r0]
                DSB
                ]
                POP     {r0-r2}

                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        CPU_EXTENSION
;
; Purpose:      Report the presence of a given CPU extension (VFP, Advanced
;               SIMD)
;
; Parameters:   $cpuid     : CPU ID (0, 1, 2 or 3)
;               $type      : Extension type, "FPU","NEON"
;               $data      : optional label, storing extension configuration
;               $error_run : optional label, handling erroneous extension configuration
;               $error_cfg : optional label, handling erroneous test configuration
;-------------------------------------------------------------------------------
                MACRO
                CPU_EXTENSION $cpuid, $type, $data, $error_run, $error_cfg
                LOCAL

       ; Macro parameter check
                [ "$cpuid" /= "" :LAND: "$type" /= ""
                |
                !        1, "\nError, missing macro input parameter"
                MEXIT
                ]
                [ "$cpuid" /= "0" :LAND: "$cpuid" /= "1" :LAND: \
                  "$cpuid" /= "2" :LAND: "$cpuid" /= "3"
                !        1, "\nError, wrong macro input parameter"
                MEXIT
                ]
                [ "$type" /= "FPU" :LAND: "$type" /= "NEON"
                !        1, "\nError, wrong macro input parameter"
                MEXIT
                ]

       ; Local strings
                LCLS    cpu_ext_flag
                LCLS    cpu_ext_macro
cpu_ext_macro   SETS    "$type":CC:"_PRESENT"
cpu_ext_flag    SETS    "CPU":CC:"$cpuid":CC:"_":CC:"$cpu_ext_macro"

       ; Ensure registers are not corrupted
                PUSH    {r0-r1}
       ; Check extension present
                $cpu_ext_macro r0
                [ $cpu_ext_flag
                MOV     r1, #1
                |
                MOV     r1, #0
                ]
       ; Common message (1rst part)
                MESSAGE "   . $type present: "
       ; CPU extension message (2nd part)
                CMP     r0,#1
                BEQ     msg_present$l
                BNE     msg_absent$l

       ; This code should not be reached
                [ "$error_ext" /= ""
                B       $error_run
                |
                MESSAGE "UNKNOWN\n"
                MESSAGE "This code should not be reached\n"
                TEST_FAIL
                ]

msg_present$l
                MESSAGE "YES\n"
                B       ext_end$l
msg_absent$l
                MESSAGE "NO\n"
                B       ext_end$l
msg_err$l
                [ "$error_cfg" /= ""
                B       $error_cfg
                |
                MESSAGE "Configuration mismatch between test and RTL\n"
                TEST_FAIL
                ]
ext_end$l
                CMP     r0, r1
                BNE     msg_err$l
                [ "$data" /= ""
                LDR     r1, =$data
                STR     r0, [r1]
                DSB
                ]
                POP     {r0-r1}

                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        CPU_NBCORE
;
; Purpose:      Report the number of CPU in an MPCore configuration
;
; Parameters:   $data_cpunb: optional label, storing CPU nb configuration information
;               $error_run : optional label, handling erroneous CPU configuration
;               $error_cfg : optional label, handling erroneous test configuration
;-------------------------------------------------------------------------------
                MACRO
                CPU_NBCORE $data_cpunb, $error_run, $error_cfg
                LOCAL

       ; Ensure registers are not corrupted
                PUSH    {r0-r2}
                MOV     r0, #0
                MOV     r1, #1
                [ CPU1_PRESENT
                ADD     r1, r1, #1
                [ CPU2_PRESENT
                ADD     r1, r1, #1
                [ CPU3_PRESENT
                ADD     r1, r1, #1
                ]
                ]
                ]
       ; Read bit[25:24] of L2CTLR register to determine the number of CPU 
       ; supported by the SCU.
               MRC     p15, 1, r0, c9, c0, 2
               UBFX    r0, r0, #24, #2
               ADD     r0, r0, #1

       ; Common message (1rst part)
               ;MESSAGE "- Number of Core(s): "

                CMP     r0, #1
                BEQ     msg_cpu1$l
                CMP     r0, #2
                BEQ     msg_cpu2$l
                CMP     r0, #3
                BEQ     msg_cpu3$l
                CMP     r0, #4
                BEQ     msg_cpu4$l

       ; This code should not be reached
                [ "$error_run" /= ""
                B       $error_run
                |
                MESSAGE "UNKNOWN\n"
                MESSAGE "This code should not be reached\n"
                TEST_FAIL
                ]

msg_cpu1$l
                ;MESSAGE "1\n"
                B       cfg_cpunb_end$l
msg_cpu2$l
                ;MESSAGE "2\n"
                B       cfg_cpunb_end$l
msg_cpu3$l
                ;MESSAGE "3\n"
                B       cfg_cpunb_end$l
msg_cpu4$l
                ;MESSAGE "4\n"
                B       cfg_cpunb_end$l

cfg_cpunb_end$l							
                CMP     r0, r1
                [ "$error_cfg" /= ""
                BNE     $error_cfg
                |
                MESSAGE "\nConfiguration mismatch between test and RTL\n"
                TEST_FAIL
                ]
                [ "$data_cpunb" /= ""
                LDR     r1, =$data_cpunb
                STR     r0, [r1]
                DSB
                ]
                POP     {r0-r2}

                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        CPU_READ_DBGROM
;
; Purpose:      Read recursively, report and check the content of the Debug APB
;               ROM Table(s) in a given system. The macro performs the following
;               tasks:
;
;               - Extract the DAPROM table system base address.
;               - For each ROM table present in the system it will:
;                        . Extract, identify and check the ROM system base address
;               - For each ROM entry, it will:
;                        . construct the debug component system base address
;                        . identify the debug component
;                        . check the debug component system base address with the
;                          test configuration
;                        . report the components found via a message display
;
;               Each input label (macro input parameter) enables the check of a
;               particular debug component so that this macro can be used to check the
;               presence of one or more CS Compliant debug components. Those labels holds
;               the count of a particular debug component and are used by the test
;               using this macro for further checking if needed.
;
;               This macro supports available Cortex-A7 CPU debug components. You will
;               need to care of modifying this macro for further support.
;
;               Code expects the ROM tables content to comply with the original APB 
;               memory map provided with the integration kit and its configuration through
;               the following test flags defined in ikvalidate.cfg.
;               Debug system test flags:
;               - DM_DAPROM_SYSADDR  : DAPROM system memory map base address
;               - DM_A7DEBUG_SYSADDR : Integration layer ROM table system memory map base address
;               CPU integration layer test flags:
;               - DM_CPUDBGn_SYSADDR : CPUn (where 0<n<4) debug system memory map base address
;               - DM_CPUPMUn_SYSADDR : CPUn (where 0<n<4) PMU system memory map base address
;
;               Should you change the APB memory map or the integration layer,
;               you will need to take care this macro is modified accordingly.
;
; Parameters:   $data_rom    : optional label, storing the number of ROM tables
;               $data_cpudbg : optional label, storing the number of CPU-DBG interfaces
;               $data_cpupmu : optional label, storing the number of CPU_PMU interfaces
;               $error_run   : optional label, handling erroneous extension configuration
;               $error_cfg   : optional label, handling erroneous test configuration
;-------------------------------------------------------------------------------
                MACRO
                CPU_READ_DBGROM $data_rom, $data_cpudbg, $data_cpupmu, \
                                $error_run, $error_cfg

                LOCAL

       ; Macro parameters: there must be one or more parameters for the macro to be used
                [ "$data_rom"    /= "" :LOR: "$data_cpudbg" /= "" :LOR: \
                  "$data_cpupmu" /= ""
                |
                !        1, "\nError, missing macro input parameter"
                MEXIT
                ]

                MESSAGE "\nInside\n"
       ; Ensure registers are not corrupted
                PUSH    {r0-r3}

       ; Read Debug ROM Address Register (DBGDRAR) to determine the DAPROM
       ; system base address bit[31:12] (set by RTL tie-off)
                MRC     p14, 0, r1, c1, c0, 0
                LDR     r0, =0xfffff000
                AND     r0, r0, r1
                LDR     r1, =DM_DAPROM_SYSADDR
       ; Check the value read matches the test configuration
                CMP     r0, r1
                [ "$error_cfg" /= ""
                BNE     $error_cfg
                |
                MESSAGE "\nConfiguration mismatch between test and RTL\n"
                TEST_FAIL
                ]
       ; Move the entry into r3 (read_rom function expects the entry in r3)
                MOV     r3, r1
       ; Start ROM table recursive read
                BL      read_rom$l
       ; End of macro
                B       read_rom_entry_end$l


       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ; Read ROM entry. Recursively:
       ;   - detect the data format (8- or 32-bit) and read the entry appropriately
       ;   - construct the mapped peripheral System address base
       ;   - analyse the peripheral Component ID Register 1
       ;   - check, print and store the results in the according memory location
       ;
       ; If another ROM is mapped, it will go through the same process.

read_rom_entry$l
                PUSH    {r0-r4, lr}
       ; Copy ROM entry
                MOV     r1, r0
entry_format$l
                LDR     r2, [r1]
                AND     r2, #0x000000FF

                UBFX    r2, r2, #1, #1
                CMP     r2, #1
                BNE     entry_8$l
entry_32$l
                LDR     r2, [r1]
                B       entry_analysis$l
entry_8$l
                LDR     r2, [r1]
                AND     r2, #0x000000FF
                LDR     r3, [r1,#0x4]!
                AND     r3, #0x000000FF
                ORR     r2, r2, r3, LSL #8
                LDR     r3, [r1, #0x4]!
                AND     r3, #0x000000FF
                ORR     r2, r2, r3, LSL #0x10
                LDR     r3, [r1, #0x4]!
                AND     r3, #0x000000FF
                ORR     r2, r2, r3, LSL #0x18
entry_analysis$l
       ; check end of ROM table entry
                CMP     r2, #0
                BEQ     read_entry_end$l
       ; check entry component is present, else skip entry
                AND     r3, r2, #1
                CMP     r3, #1
                BNE     entry_analysis_end$l
       ; construct System base address for component CID1 and read its content
       ; (ComponentSystemAddress = ROMSystemAddress + EntryAddressOffset)
                LDR     r3, =0xfffff000
                AND     r2, r2, r3
                ADD     r3, r0, r2
                LDR     r4, [r3, #0xff4]
cid_analysis$l
       ; extract CID1 bit[7:4] to see the component's class
                UBFX    r4, r4, #4, #4
       ; ROM table detection
                CMP     r4, #1
                BLEQ    read_rom$l
       ; Debug component detection
                CMP     r4, #9
                BLEQ    read_cs_entry$l
       ; PrimeCell component detection
                CMP     r4, #0xf
                BLEQ    read_pc_entry$l
       ; Next entry lookup
entry_analysis_end$l
                ADD     r1, r1, #0x4
                B       entry_format$l
read_entry_end$l
                POP     {r0-r4, pc}

       ; Components checks sub-routines
       ; PrimeCell/System components: simply print a message
read_pc_entry$l
                PUSH    {lr}
                MESSAGE "- PrimeCell or System Component detected\n"
                POP     {pc}


       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ; ROM table: Read Peripheral ID registers and detect DAPROM or
       ; Cortex-A7 integration layer ROM table.
       ; - read_rom$l function expects the ROM entry (component debug memory map
       ; offset) in r3.
       ; - {r1,r0} store the 64-bit Peripheral ID read.
       ; - {r3,r2} store the 64-bit Peripheral ID from the test configuration.
       ; - The revision nibble is masked (PID2 bit[7:4]).

read_rom$l
                PUSH    {r0-r4,lr}
       ; ROM entry into r4
                MOV     r4, r3
       ; Read the Peripheral ID from RTL
                MOV     r1, #0
                LDR     r0, [r3, #0xfd0]!       ;PID4
                AND     r0, #0x000000FF
                ORR     r1, r1, r0

                LDR     r0, [r3, #4]!           ;PID5
                AND     r0, #0x000000FF
                ORR     r1, r1, r0, LSL #0x8

                LDR     r0, [r3, #4]!           ;PID6
                AND     r0, #0x000000FF
                ORR     r1, r1, r0, LSL #0x10

                LDR     r0, [r3, #4]!           ;PID7
                AND     r0, #0x000000FF
                ORR     r1, r1, r0, LSL #0x18

                MOV     r0, #0
                LDR     r2, [r3, #4]!           ;PID0
                AND     r2, #0x000000FF
                ORR     r0, r0, r2

                LDR     r2, [r3, #4]!           ;PID1
                AND     r2, #0x000000FF
                ORR     r0, r0, r2, LSL #0x8

                LDR     r2, [r3, #4]!           ;PID2
                AND     r2, #0x000000FF
                ORR     r0, r0, r2, LSL #0x10

                LDR     r2, [r3, #4]!           ;PID3
                AND     r2, #0x000000FF
                ORR     r0, r0, r2, LSL #0x18

                MESSAGE "- ROM Table: "

       ; Peripheral ID from test configuration
       ; Check if DAPROM table
                LCLS    dap_perifid
                LCLS    dap_perifid0
                LCLS    dap_perifid1
dap_perifid     SETS    DAPROMID
dap_perifid0    SETS    "0x":CC:("$dap_perifid":RIGHT:8)
dap_perifid1    SETS    "0x":CC:("$dap_perifid":LEFT:8)
                LDR     r3, =$dap_perifid1
                LDR     r2, =$dap_perifid0

                CMP     r3, r0
                CMPEQ   r2, r1
                BEQ     msg_daprom$l

       ; Check if A7ROM table
                LCLA    rom_perifid0
                LCLA    rom_perifid1
rom_perifid0    SETA    0x00000004
rom_perifid1    SETA    0x000bb4a7
                LDR     r3, =0x$rom_perifid1
                LDR     r2, =0x$rom_perifid0
                CMP     r3, r0
                CMPEQ   r2, r1
                BEQ     msg_a7rom$l

       ; ROM Table not recognised expected A7ROM or DAPROM table
                [ "$error_run" /= ""
                B       $error_run
                |
                MESSAGE "UNKNOWN\n"
                TEST_FAIL
                ]

msg_daprom$l
                MESSAGE "DAPROM\n"
                MOV     r0, r4
                B       read_rom_end$l
msg_a7rom$l
                MESSAGE "A7ROM\n"
                LDR     r0, =DM_A7DEBUG_SYSADDR
                CMP     r4, r0
                [ "$error_cfg" /= ""
                BNE     $error_cfg
                |
                MESSAGE "\nConfiguration mismatch between test and RTL\n"
                TEST_FAIL
                ]
                B       read_rom_end$l

read_rom_end$l
       ; Update the ROM table count
                [ "$data_rom" /= ""
                LDR     r1, =$data_rom
                LDR     r2, [r1]
                ADD     r2, r2, #1
                STR     r2, [r1]
                DSB
                ]
                BL      read_rom_entry$l
                POP     {r0-r4,pc}

       ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       ; Read the Device Type Identifier register, and report the device being
       ; detected. The following only detects: ETM, CTI, CPU (debug or PMU).

read_cs_entry$l
                PUSH    {r0-r5,lr}
       ; Load component APB system memory mapped based address
                MOV     r0, r3
       ; Read CS Device Type Identifier register (offset 0xfcc)
                LDR     r1, [r0,#0xfcc]
                UBFX    r1, r1, #0, #8

       ; Check if TPIU component
                CMP     r1, #0x11
                BEQ     read_cs_tpiu$l
       ; Check if Funnel component
                CMP     r1, #0x12
                BEQ     read_cs_funnel$l
       ; Check if ETM component
                CMP     r1, #0x13
                BEQ     read_cs_etm$l
       ; Check if CTI component
                CMP     r1, #0x14
                BEQ     read_cs_cti$l
       ; Check if CPU debug interface
                CMP     r1, #0x15
                BEQ     read_cs_cpudbg$l
       ; Check if CPU PMU nterface
                CMP     r1, #0x16
                BEQ     read_cs_cpupmu$l
       ; Other unknown component
                B       read_cs_x$l

       ; Components Configuration checks and report

; Testing of TPIU is not within the scope of IK
read_cs_tpiu$l
                B       read_cs_entry_end$l
; Testing of Funnel is not within the scope of IK
read_cs_funnel$l
                B       read_cs_entry_end$l
; Testing of CTI is not within the scope of IK
read_cs_cti$l
                B       read_cs_entry_end$l

; Testing of ETM is not within the scope of IK
read_cs_etm$l
                B       read_cs_entry_end$l

read_cs_cpudbg$l
                [ "$data_cpudbg" /= ""
                LDR     r1, =DM_CPUDBG0_SYSADDR
                LDR     r2, =DM_CPUDBG1_SYSADDR
                LDR     r3, =DM_CPUDBG2_SYSADDR
                LDR     r4, =DM_CPUDBG3_SYSADDR
                CMP     r0, r1
                BEQ     read_cs_cpudbg0$l
                CMP     r0, r2
                BEQ     read_cs_cpudbg1$l
                CMP     r0, r3
                BEQ     read_cs_cpudbg2$l
                CMP     r0, r4
                BEQ     read_cs_cpudbg3$l
                B       read_cs_err$l
read_cs_cpudbg0$l
                MESSAGE "- CPU Debug Component: CPUDBG0\n"
                B       read_cs_cpudbg_end$l
read_cs_cpudbg1$l
                MESSAGE "- CPU Debug Component: CPUDBG1\n"
                B       read_cs_cpudbg_end$l
read_cs_cpudbg2$l
                MESSAGE "- CPU Debug Component: CPUDBG2\n"
                B       read_cs_cpudbg_end$l
read_cs_cpudbg3$l
                MESSAGE "- CPU Debug Component: CPUDBG3\n"
read_cs_cpudbg_end$l
                LDR     r0, =$data_cpudbg
                LDR     r1, [r0]
                ADD     r1, r1, #1
                STR     r1, [r0]
                DSB
                ]
                B       read_cs_entry_end$l

read_cs_cpupmu$l
                [ "$data_cpupmu" /= ""
                LDR     r1, =DM_CPUPMU0_SYSADDR
                LDR     r2, =DM_CPUPMU1_SYSADDR
                LDR     r3, =DM_CPUPMU2_SYSADDR
                LDR     r4, =DM_CPUPMU3_SYSADDR
                CMP     r0, r1
                BEQ     read_cs_cpupmu0$l
                CMP     r0, r2
                BEQ     read_cs_cpupmu1$l
                CMP     r0, r3
                BEQ     read_cs_cpupmu2$l
                CMP     r0, r4
                BEQ     read_cs_cpupmu3$l
                B       read_cs_err$l
read_cs_cpupmu0$l
                MESSAGE "- CPU Debug Component: CPUPMU0\n"
                B       read_cs_cpupmu_end$l
read_cs_cpupmu1$l
                MESSAGE "- CPU Debug Component: CPUPMU1\n"
                B       read_cs_cpupmu_end$l
read_cs_cpupmu2$l
                MESSAGE "- CPU Debug Component: CPUPMU2\n"
                B       read_cs_cpupmu_end$l
read_cs_cpupmu3$l
                MESSAGE "- CPU Debug Component: CPUPMU3\n"
read_cs_cpupmu_end$l
                LDR     r0, =$data_cpupmu
                LDR     r1, [r0]
                ADD     r1, r1, #1
                STR     r1, [r0]
                DSB
                ]
                B       read_cs_entry_end$l

read_cs_x$l
                [ "$error_run" /= ""
                B       $error_run
                |
                MESSAGE "- Component: UNKNOWN\n"
                TEST_FAIL
                ]

read_cs_err$l
                [ "$error_cfg" /= ""
                MESSAGE "UNKNOWN\n"
                B       $error_cfg
                |
                B       read_cs_x$l
                ]

read_cs_entry_end$l
                POP     {r0-r5,pc}

read_rom_entry_end$l

                POP     {r0-r3}
                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; Macro:        BST
;
; Purpose:      The BST Macro
;-------------------------------------------------------------------------------
                MACRO
$label          BST     $txt
$label          DCB     "$txt\n"
                MEND


;-------------------------------------------------------------------------------
; Macro:        BST_END
;
; Purpose:      Indicator for end of Boundary Scan Toolbox instructions,
;               -bin2bst searches for this value so beware changing it.
;-------------------------------------------------------------------------------
                MACRO
                BST_END
                ALIGN
        ; define BSI ending delimeter (must be word aligned)
                DCD        0xE610B510
        ; label branched to by BST_BEGIN
1234
                NOP
                MEND

;-------------------------------------------------------------------------------
; Macro:        BST_START
;
; Purpose:      macro used to initialise the BST after reset, for example,
;               enabling halting mode.
;-------------------------------------------------------------------------------
                MACRO
                BST_START
                BST_BEGIN
                MEND

;-------------------------------------------------------------------------------
; Macro:        BST_BEGIN
;
; Purpose:      Indicator for start of Boundary Scan Toolbox instructions,
;               -bin2bst searches for this value so beware changing it.
;-------------------------------------------------------------------------------
                MACRO
                BST_BEGIN
        ; label to skip BST code
                B        %F1234
        ; place any outstanding literals
                LTORG
        ; define BSI starting delimeter (must be word aligned)
                DCD        0xE600B510
                MEND

;-------------------------------------------------------------------------------
; Macro:        NOPx <count>
;
; Purpose:      Inserts <count> NOPs
;-------------------------------------------------------------------------------

                MACRO
$label          NOPx    $n
$label
                LOCAL
                LCLA    count$l
count$l         SETA    $n
                WHILE   count$l > 0
count$l         SETA    count$l - 1
                NOP
                WEND
                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        SET_EXCEPTION
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                SET_EXCEPTION $excp, $label, $retreg
                LOCAL
                LDR     r0, =ExcpTable
                LDR     r1, =$label
                [ "$excp" = ""
                ! 0, "No exception type defined on call to SET_EXCEPTION"
                |
                [ "$excp" = "RESET"
                ADD     r0, r0, #0x0
                |
                [ "$excp" = "UNDEF"
                ADD     r0, r0, #0x4
                |
                [ "$excp" = "SWI"
                ADD     r0, r0, #0x8
                |
                [ "$excp" = "PABORT"
                ADD     r0, r0, #0xC
                |
                [ "$excp" = "DABORT"
                ADD     r0, r0, #0x10
                |
                [ "$excp" = "IRQ"
                ADD     r0, r0, #0x18
                |
                [ "$excp" = "FIQ"
                ADD     r0, r0, #0x1C
                |
                ]
                ]
                ]
                ]
                ]
                ]
                ]
                ]
                [ "$retreg" != ""
                LDR     $retreg, [r0]
                ]
                STR     r1, [r0]
                DSB
                LOCAL_END
                MEND

;-------------------------------------------------------------------------------
; MACRO:        POWER_UP_CORES
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
$label          POWER_UP_CORES
                ;LOCAL
                PUSH    {r0,r1,r2}

;;For CA7

; CS3_CPU_CTRL1
;clkcore_off              <4:0>       5'b1111       0X20[4:0] //clkcore_off[4] is for L2 and debug clock 
;clkatb_off                           1'b1          0X20[8:8] 
;clkapb_off                           1'b1          0X20[9:9] 
;clktrace_off                         1'b1          0X20[10:10] 
;clkts_off                            1'b1          0X20[11:11] 
;
; CS3_CPU_CTRL2
;nCOREPORESET_i           <3:0>       4'b0000      0X21[3:0] 
;nCORERESET_i             <3:0>       4'b0000      0X21[7:4] 
;nETMRESET_i              <3:0>       4'b0000      0X21[11:8] 
;nDBGRESET_i              <3:0>       4'b0000      0X21[ 15: 12] 
;nL2RESET_i                           1'b0         0X21[16:16] 
;nSOCDBGRESET_i                       1'b0         0X21[17:17] 
;RESETPORn_0_i                        1'b0         0X21[18:18] 
;RESETATn_3_i                         1'b0         0X21[19:19] 
;RESETAPBn_4_i                        1'b0         0X21[20:20] 
;RESETTRCn_5_i                        1'b0         0X21[21:21] 
;
; CS3_CPU_CTRL3
;PWRUP_HAMMER_i           <3:0>       4'b0000      0X22[3 : 0] 
;PWRUP_TRICKLE_i          <3:0>       4'b0000      0X22[7:4] 
;ISOLATE_i                <3:0>       4'b0000      0X22[11:8] 
;
;  CS3_CPU_STATUS1
;PWRUP_HAMMER_READY_o     <3:0>       4'b0000      0X30[3:0] 
;PWRUP_TRICKLE_READY_o    <3:0>       4'b0000      0X30[7:4] 
;STANDBYWFI_o             <3:0>       4'b0000      0X30[15:12] 

;only cpu0 do powering up
        MRC     p15,0,r0,c0,c0,5
        AND     r0, r0, #0xf
        CMP     r0, #0
        BNE     skip_power_up

        ;clock off
        LDR     r1, =CS3_CTRL1_ADDR
        LDR     r2, =0xf0e
        STR     r2, [r1]
        ;reset assert
        LDR     r1, =CS3_CTRL2_ADDR
        LDR     r2, =0x10011
        STR     r2, [r1]

       ;skip iso/psw when it is phoenix
       ; Read bit[25:24] of L2CTLR register to determine the number of CPU 
       ; supported by the SCU.
        MRC     p15, 1, r0, c9, c0, 2
        UBFX    r0, r0, #24, #2
        ADD     r0, r0, #1
        ;phoenix:2 cores, no iso/psw
        CMP     r0, #2
        BEQ     skip_iso_psw

        ;iso on
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0xe11
        STR     r2, [r1]
        ;power sw on
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0xeff
        STR     r2, [r1]

      ;dealy to avoid CPU read unknown in gatesim
      ;need to delay about 600ns
        LDR r2, =0x2bc

;delay_loop
$label.delay_loop
        SUB r2, #1
        CMP r2, #0
        BNE delay_loop

;wait_psw_ready
$label.wait_psw_ready
        ;wait power sw ready
        LDR     r1, =CS3_STS1_ADDR
        LDR     r2, [r1]
        AND     r2, r2 , #0xff
        CMP     r2, #0xff
        BNE     wait_psw_ready

        ;iso off
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0x0ff
        STR     r2, [r1]

;skip_iso_psw
$label.skip_iso_psw
        ;clock on
        LDR     r1, =CS3_CTRL1_ADDR
        MOV     r2, #0x0
        STR     r2, [r1]
        ;clock off
        LDR     r1, =CS3_CTRL1_ADDR
        LDR     r2, =0xf0e
        STR     r2, [r1]
        ;reset de-assert
        LDR     r1, =CS3_CTRL2_ADDR
        LDR     r2, =0x3fffff
        STR     r2, [r1]
        ;clock on
        LDR     r1, =CS3_CTRL1_ADDR
        MOV     r2, #0x0
        STR     r2, [r1]

;skip_power_up
$label.skip_power_up
        POP    {r0,r1,r2}
        ;LOCAL_END
        MEND
;-------------------------------------------------------------------------------
; MACRO:        RESTORE_EXCEPTION
;
; Purpose:      x
;
; Parameters:   x
;-------------------------------------------------------------------------------
                MACRO
                RESTORE_EXCEPTION $excp, $reg
                LOCAL
                LOCAL
                LDR     r0, =ExcpTable
                [ "$excp" = ""
                ! 0, "No exception type defined on call to SET_EXCEPTION"
                |
                [ "$excp" = "RESET"
                ADD     r0, r0, #0x0
                |
                [ "$excp" = "UNDEF"
                ADD     r0, r0, #0x4
                |
                [ "$excp" = "SWI"
                ADD     r0, r0, #0x8
                |
                [ "$excp" = "PABORT"
                ADD     r0, r0, #0xC
                |
                [ "$excp" = "DABORT"
                ADD     r0, r0, #0x10
                |
                [ "$excp" = "IRQ"
                ADD     r0, r0, #0x18
                |
                [ "$excp" = "FIQ"
                ADD     r0, r0, #0x1C
                |
                ]
                ]
                ]
                ]
                ]
                ]
                ]
                ]
                STR     $reg, [r0]
                DSB
                LOCAL_END
                MEND
        END
