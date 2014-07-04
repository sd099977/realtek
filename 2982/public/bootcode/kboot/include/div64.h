#ifndef _ASM_GENERIC_DIV64_H
#define _ASM_GENERIC_DIV64_H
/*
 * Copyright (C) 2003 Bernardo Innocenti <bernie@develer.com>
 * Based on former asm-ppc/div64.h and asm-m68knommu/div64.h
 *
 * The semantics of do_div() are:
 *
 * uint32_t do_div(uint64_t *n, uint32_t base)
 * {
 *	uint32_t remainder = *n % base;
 *	*n = *n / base;
 *	return remainder;
 * }
 *
 * NOTE: macro parameter n is evaluated multiple times,
 *       beware of side effects!
 */

extern uint32 __div64_32(uint64 *dividend, uint32 divisor);

/* The unnecessary pointer compare is there
 * to check for type safety (n must be 64bit)
 */
# define do_div(n,base) ({				\
	uint32 __base = (base);			\
	uint32 __rem;					\
	(void)(((typeof((n)) *)0) == ((uint64 *)0));	\
	if (((n) >> 32) == 0) {			\
		__rem = (uint32)(n) % __base;		\
		(n) = (uint32)(n) / __base;		\
	} else						\
		__rem = __div64_32(&(n), __base);	\
	__rem;						\
 })

/* Wrapper for do_div(). Doesn't modify dividend and returns
 * the result, not reminder.
 */
static inline uint64 lldiv(uint64 dividend, uint32 divisor)
{
	uint64 __res = dividend;
	do_div(__res, divisor);
	return(__res);
}

#endif /* _ASM_GENERIC_DIV64_H */
