#ifndef __SED_TYPES_H__
#define __SED_TYPES_H__

#include <sysdefs.h>

#if defined (SIRIUS) || defined (FPGA)
#define NULL		          ((void *)0)
#endif

/* Type define */
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	addr64;
typedef unsigned long long	uint64;
typedef long long			int64;

typedef int			__kernel_ptrdiff_t;
typedef __kernel_ptrdiff_t	ptrdiff_t;

//for mtd interface
typedef long long      __kernel_loff_t;
typedef __kernel_loff_t		loff_t;

typedef unsigned long phys_addr_t;
typedef unsigned long phys_size_t;

#define __bitwise

typedef __u16 __bitwise __le16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __le32;
typedef __u32 __bitwise __be32;

typedef		__u8		uint8_t;
typedef		__u16		uint16_t;
typedef		__u32		uint32_t;
typedef		__u64		uint64_t;

#endif
