.section .arm.pattern,"a"

.globl __arm_advsimd_start
.globl __arm_advsimd_end
__arm_advsimd_start:
.incbin "./SCPU/ca7_advsimd_functional"
__arm_advsimd_end:

.globl __arm_vfp_start
.globl __arm_vfp_end
__arm_vfp_start:
.incbin "./SCPU/ca7_vfp_functional"
__arm_vfp_end:

