#include "loader.h"

/* ------------------------ */
/* .bss section declaration */
/* ------------------------ */
   .bss

/* _app_stack: Application's stack */
   .globl  _app_stack
_app_stack:
   .space  APP_STACK_SIZE

/* _appisr_stack: stack of Application ISR */
   .globl  _appisr_stack
_appisr_stack:
   .space APPISR_STACK_SIZE

/* Heap pointers: Values for these are calculated at run-time from */
/*                the application configuration data above.        */
   .globl _app_heap_start
_app_heap_start:
   .space 4
   .globl _app_heap_end
_app_heap_end:
   .space 4

/* STATUS register for ISR using */
   .globl _isr_status_reg
_isr_status_reg:
   .space 4

/* CAUSE register for ISR using */
   .globl _isr_cause_reg
_isr_cause_reg:
   .space 4
   
/* return ra */
   .globl _return_ra
_return_ra:
   .space 4
   
/* return s0 */
   .globl _return_s0
_return_s0:
   .space 4

/* return s1 */
   .globl _return_s1
_return_s1:
   .space 4

/* return s2 */
   .globl _return_s2
_return_s2:
   .space 4

/* return s3 */
   .globl _return_s3
_return_s3:
   .space 4

/* return s4 */
   .globl _return_s4
_return_s4:
   .space 4

/* return s5 */
   .globl _return_s5
_return_s5:
   .space 4

/* return s6 */
   .globl _return_s6
_return_s6:
   .space 4

/* return s7 */
   .globl _return_s7
_return_s7:
   .space 4

/* return s8 */
   .globl _return_s8
_return_s8:
   .space 4


/* ------------------------- */
/* .text section declaration */
/* ------------------------- */

/* ======== Section 0 ======== */
/* Reset exception entry Point */
   .text
   .section "section0", "ax"   /* allocatable, executable section "section0" */
   .set noreorder
   .ent   loader_asm_code0
   .globl loader_asm_code0
loader_asm_code0:
   .globl RESET_EntryPoint
RESET_EntryPoint:

	# clear uninitialised data section
	la	t0, __bss_start
	la	t1, __bss_end
1:
	sw	zero, 0(t0)
	bne	t0, t1, 1b
	addiu	t0, t0, 0x4

/* save return registers */
   sw    ra, _return_ra
   sw    s0, _return_s0
   sw    s1, _return_s1
   sw    s2, _return_s2
   sw    s3, _return_s3
   sw    s4, _return_s4
   sw    s5, _return_s5
   sw    s6, _return_s6
   sw    s7, _return_s7
   sw    s8, _return_s8

/* initialize the global pointer register     */
/* __gp = linker supplied global data pointer */
   .extern __gp
   la    gp,__gp

/* initialize heap for application                                 */
/* calculate heap start and adjust it up to 16-bytes alignment     */
/* __heap_start_addr = end address of program, assigned by Linker  */
   .extern __heap_start_addr
   .extern __Size_Of_SDRAM
   .extern __Start_Of_SDRAM

   la    t1, __heap_start_addr
   add   t1, 16 - 1
   srl   t1, 4
   sll   t1, 4
   sw    t1, _app_heap_start
   la    t0, __Size_Of_SDRAM
   subu  t0, 1
   la    t1, __Start_Of_SDRAM
   add   t0, t0, t1
   sw    t0, _app_heap_end

/* initialize stack for application */
   la    sp, _app_stack + APP_STACK_SIZE

/* jump to application */
   la    t0, APP_START_ADDR
   jalr  t0
   nop

/* return from application */
   la    t0, _return_ra
   lw    ra, 0(t0)
   la    t0, _return_s0
   lw    s0, 0(t0)
   la    t0, _return_s1
   lw    s1, 0(t0)
   la    t0, _return_s2
   lw    s2, 0(t0)
   la    t0, _return_s3
   lw    s3, 0(t0)
   la    t0, _return_s4
   lw    s4, 0(t0)
   la    t0, _return_s5
   lw    s5, 0(t0)
   la    t0, _return_s6
   lw    s6, 0(t0)
   la    t0, _return_s7
   lw    s7, 0(t0)
   la    t0, _return_s8
   lw    s8, 0(t0)
   jr    ra
   nop   


   .end  loader_asm_code0

/*   
      .globl Get_Count_Reg
Get_Count_Reg:
   mfc0  v0, C0_COUNT, 0
   nop
   jr    ra
   nop
*/
