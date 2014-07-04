#ifndef __SED_TYPES_H__
#define __SED_TYPES_H__

#if defined (SIRIUS) || defined (FPGA)
#define NULL		          ((void *)0)
#endif

/* Type define */
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	addr64;

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	addr64_t;

#endif
