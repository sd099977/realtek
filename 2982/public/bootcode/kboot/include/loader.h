/* BAL: GNU tools do not allow the target of a bal to */
/*      be external to a module so must use a jal.    */
#define BAL jal

#define zero $0
#define AT   $at   /* assembler temp */
#define v0   $2    /* function return value0 */
#define v1   $3    /* function return value1 */
#define a0   $4    /* argument registers 0-3 */
#define a1   $5
#define a2   $6
#define a3   $7
#define t0   $8
#define t1   $9
#define t2   $10
#define t3   $11
#define t4   $12
#define t5   $13
#define t6   $14
#define t7   $15
#define s0   $16
#define s1   $17
#define s2   $18
#define s3   $19
#define s4   $20
#define s5   $21
#define s6   $22
#define s7   $23
#define t8   $24
#define t9   $25
#define k0   $26      /* kernel temporary */
#define k1   $27      /* kernel reserved */
#define gp   $28      /* global data pointer */
#define sp   $29      /* stack pointer */
#define s8   $30      /* one more callee saved */
#define ra   $31      /* return address */

/* define frame for ISR register saving */
#define e_AT       1
#define e_v0       2
#define e_v1       3
#define e_a0       4
#define e_a1       5
#define e_a2       6
#define e_a3       7
#define e_t0       8
#define e_t1       9
#define e_t2       10
#define e_t3       11
#define e_t4       12
#define e_t5       13
#define e_t6       14
#define e_t7       15
#define e_s0       16
#define e_s1       17
#define e_s2       18
#define e_s3       19
#define e_s4       20
#define e_s5       21
#define e_s6       22
#define e_s7       23
#define e_t8       24
#define e_t9       25
#define e_k0       26
#define e_k1       27
#define e_gp       28
#define e_sp       29
#define e_s8       30
#define e_ra       31
#define e_CAUSE    32
#define e_BADVADDR 33
#define e_SR       34
#define e_EPC      35
#define e_size     36

#define C0_BADVADDR  $8
#define C0_COUNT     $9
#define C0_COMPARE   $11
#define C0_SR        $12
#define C0_STATUS    $12
#define C0_CAUSE     $13
#define C0_EPC       $14
#define C0_PRID      $15
#define C0_WatchLo   $18
#define C0_WatchHi   $19
#define C0_CCTL      $20      /* Cache control for LX4180 core */


/* definition for Status Register */
#define SR_CU3       0x80000000
#define SR_CU2       0x40000000
#define SR_CU1       0x20000000
#define SR_CU0       0x10000000
#define SR_RP        0x08000000
#define SR_RE        0x02000000
#define SR_BEV       0x00400000  /* Bootstrap Exception Vector */
#define SR_TS        0x00200000
#define SR_IPMASK    0x0000ff00  /* Interrupt Mask */
#define SR_IP7       0x00008000  /*  (Intr5) */
#define SR_IP6       0x00004000  /*  (Intr4) */
#define SR_IP5       0x00002000  /*  (Intr3) */
#define SR_IP4       0x00001000  /*  (Intr2) */
#define SR_IP3       0x00000800  /*  (Intr1) */
#define SR_IP2       0x00000400  /*  (Intr0) */
#define SR_IP1       0x00000200  /*  (Software Interrupt 1) */
#define SR_IP0       0x00000100  /*  (Software Interrupt 0) */
#define SR_KU        0x00000018  /* UM and R0 */
#define SR_ERL       0x00000004  /* Interrupt Enable, previous */
#define SR_EXL       0x00000002  /* Kernel/User mode, current */
#define SR_IE        0x00000001  /* Interrupt Enable, current */

/* Cause Register */
#define CAUSE_BD        0x80000000  /* Branch Delay */
#define CAUSE_TI        0x40000000  /* Timer Interrupt Pending */
#define CAUSE_DC        0x08000000  /* Disable Count */
#define CAUSE_IV        0x00800000  /*  */
#define CAUSE_WP        0x00400000  /*  */
#define CAUSE_IPMASK    0x0000ff00  /* Interrupt Pending */
#define CAUSE_IP7       0x00008000  /*  (Intr5) */
#define CAUSE_IP6       0x00004000  /*  (Intr4) */
#define CAUSE_IP5       0x00002000  /*  (Intr3) */
#define CAUSE_IP4       0x00001000  /*  (Intr2) */
#define CAUSE_IP3       0x00000800  /*  (Intr1) */
#define CAUSE_IP2       0x00000400  /*  (Intr0) */
#define CAUSE_IP1       0x00000200  /*  (Software Interrupt 1) */
#define CAUSE_IP0       0x00000100  /*  (Software Interrupt 0) */
#define CAUSE_EXCMASK   0x0000007c  /* Exception Code */
#define CAUSE_EXCSHIFT  2           /* Right justify EXC */

/* Exception Code */
#define EXC_INT      (0 << 2)    /* External interrupt */
#define EXC_ADEL     (4 << 2)    /* Address error (Load or Ifetch) */
#define EXC_ADES     (5 << 2)    /* Address error (Store) */
#define EXC_SYS      (8 << 2)    /* System call */
#define EXC_BP       (9 << 2)    /* Break point */
#define EXC_RI       (10 << 2)   /* Reserved instruction */
#define EXC_CPU      (11 << 2)   /* Coprocessor unusable */
#define EXC_OVF      (12 << 2)   /* Arithmetic overflow */

/* Normalized Exception Codes */
#define EX_UNKNOWN_INTERRUPT       0
#define EX_ADDRESS_ERROR_LF        4
#define EX_ADDRESS_ERROR_S         5
#define EX_UNKNOWN_SYSCALL         8
#define EX_UNKNOWN_BREAK           9
#define EX_RESERVED_INSTRUCTION    10
#define EX_COPROCESSOR_UNUSABLE    11
#define EX_OVERFLOW                12

/* Environment information of application */
#define APP_START_ADDR    app_main
#define APPISR_START_ADDR app_isr_main
//#define APP_STACK_SIZE    0x00002000    /* 8K bytes */
#define APP_STACK_SIZE    0x00010000    /* 64K bytes */
#define APPISR_STACK_SIZE 0x00002000    /* 8K bytes */
