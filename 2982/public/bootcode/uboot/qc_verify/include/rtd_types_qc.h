#ifndef _RTD_TYPES_H
#define _RTD_TYPES_H

/*
 * Internal names for basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
*/
#ifndef NULL
#define NULL (void *)0
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILED
#define FAILED -1
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char	UINT8;
typedef signed char		INT8;
typedef unsigned short	UINT16;
typedef signed short	INT16;
typedef unsigned int	UINT32;
typedef signed int		INT32;
typedef unsigned long long	UINT64;
typedef signed long long	INT64;

#define CLEARBITS(a,b)  		((a) &= ~(b))
#define SETBITS(a,b)    		((a) |= (b))
#define ISSET(a,b)      		(((a) & (b))!=0)
#define ISCLEARED(a,b)  		(((a) & (b))==0)

#ifndef MAX             		
#define MAX(a,b)        		(((a) > (b)) ? (a) : (b))
#endif                  		/* max */
                        		
#ifndef MIN             		
#define MIN(a,b)        		(((a) < (b)) ? (a) : (b))
#endif                  		/* min */

#if 0
#define rtd_inb(Address)			(*(volatile UINT8 *) (Address))			//Read 8-bit Data from Specific Memory Address
#define rtd_inw(Address)			(*(volatile UINT16 *) (Address))		//Read 16-bit Data from Specific Memory Address
#define rtd_inl(Address)			(*(volatile UINT32 *) (Address))		//Read 32-bit Data from Specific Memory Address

#define rtd_outb(Address, Data)		(*(volatile UINT8 *) (Address) = Data)	//Write 8-bit Data to Specific Memory Address
#define rtd_outw(Address, Data)		(*(volatile UINT16 *) (Address) = Data)	//Write 16-bit Data to Specific Memory Address
#define rtd_outl(Address, Data)		(*(volatile UINT32 *) (Address) = Data)	//Write 32-bit Data to Specific Memory Address
#endif

#define rtd_maskl(offset, andMask, orMask) rtd_outl(offset, ((rtd_inl(offset) & (andMask)) | (orMask)))
#endif
