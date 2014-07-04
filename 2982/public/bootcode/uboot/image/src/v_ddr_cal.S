/* Assigned Company values for bits 23:16 of the PRId Register
   (CP0 register 15, select 0).  As of the MIPS32 and MIPS64 specs from
   MTI, the PRId register is defined in this (backwards compatible)
   way:

   +----------------+----------------+----------------+----------------+
   | Company Options| Company ID     | Processor ID   | Revision       |
   +----------------+----------------+----------------+----------------+
   31            24 23            16 15             8 7

   I don't have docs for all the previous processors, but my impression is
   that bits 16-23 have been 0 for all MIPS processors before the MIPS32/64
   spec.
*/


/* Register */
#define REG_UART0_BASE			0xb8062300
#define REG_UART1_BASE			0xb801bc00
#define DEFAULT_UART			REG_UART0_BASE

/* Value */
#define PRID_LX_5280_VCPU1		0x01A5C601
#define PRID_LX_5280_VCPU2		0x01A6C601
#define KSEG_MSK          		0xE0000000
#define KSEG0BASE				0x80000000
#define KSEG1BASE				0xA0000000
#define V_ENTRY_CODE			0xa0000200
#define DDR_CAL_FLAG			0xb8060108

/* DI sram */
#define DI_SRAM_BASE			0xb8064000
#define DI_SRAM_SIZE			0x3FF0	/* total: 0x4000 */

/* C entry code */
#define C_ENTRY_CODE_ADDR		0xb8064100

#define KSEG0A(reg)     and reg, ~KSEG_MSK; or reg, KSEG0BASE

	.section ".text", "ax"
	.globl	v_ddr_cal
	.ent	v_ddr_cal
v_ddr_cal:
	.set noreorder
/* LEAF(v_ddr_cal) */

	/***************************************/
	/* distinguish between VCPU1 and VCPU2 */
	/***************************************/
	mfc0	$17, $15
	li		$18, PRID_LX_5280_VCPU1
	bne		$17, $18, v2_wait_ddr_cal
	nop
	b		v1_go_ddr_cal
	nop

v1_go_ddr_cal:
	li		$18, DDR_CAL_FLAG
	lw		$16, 0($18)
	nop
	andi	$16, $16, 0x0001
	li		$17, 0x0000001
	bne		$16, $17, v1_go_ddr_cal		/* wait Reg(A).bit0 = 1 */
	nop

	/***************************
	 * setup c code environment
	 ***************************/
setup_sp:
	/* setup stack pointer on sram */
	li		$18, DI_SRAM_BASE
	addiu	$18, $18, DI_SRAM_SIZE
	move	$29, $18
	nop

jump_to_c_entry:
	/* jump to c_entry code */
	li		$18, C_ENTRY_CODE_ADDR
	jalr	$18
	nop

v1_ddr_cal_done:
	/***************************
	 * ddr calibration done
	 ***************************/
	li		$18, DDR_CAL_FLAG
	lw      $16, 0($18)
	nop
	ori		$16, $16, 0x00000002		/* set Reg(A).bit1 = 1 after ddr calibration done */
	sw		$16, 0($18)

	/***************************
	 * trigger int_vs
	 ***************************/
	li		$18, 0xb801a104
	li		$16, 0x00000081				/* set CPU_INT.int_vs(bit7) = 1 to notice scpu */
	sw		$16, 0($18)
	b		v12_go_v_entry
	nop

v2_wait_ddr_cal:
	li		$18, DDR_CAL_FLAG
	lw		$16, 0($18)
	nop
	andi	$16, $16, 0x0002
	li		$17, 0x00000002
	bne		$16, $17, v2_wait_ddr_cal	/* wait Reg(A).bit1 = 1 */
	nop

v12_go_v_entry:
	li		$17, V_ENTRY_CODE
	jalr	$17
	nop

/* END(v_ddr_cal) */
	.set reorder
	.end v_ddr_cal

