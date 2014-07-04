/************************************************************************
 *
 *  ctype.h
 *
 *  Definitions for control characters
 *
 ************************************************************************/

#ifndef	_CTYPE_
#define	_CTYPE_		1

#define _UPC	0x1
#define _LWR	0x2
#define _DIG	0x4
#define _SPC	0x8
#define _PUN	0x10
#define _CTR	0x20
#define _HEX	0x40
#define _BLK	0x80

extern	char	_ctype[];

#define	isalpha(c)	((_ctype)[(unsigned char)(c)]&(_UPC|_LWR))
#define	isupper(c)	((_ctype)[(unsigned char)(c)]&_UPC)
#define	islower(c)	((_ctype)[(unsigned char)(c)]&_LWR)
#define	isdigit(c)	((_ctype)[(unsigned char)(c)]&_DIG)
#define	isxdigit(c)	((_ctype)[(unsigned char)(c)]&(_DIG|_HEX))
#define	isspace(c)	((_ctype)[(unsigned char)(c)]&_SPC)
#define ispunct(c)	((_ctype)[(unsigned char)(c)]&_PUN)
#define isalnum(c)	((_ctype)[(unsigned char)(c)]&(_UPC|_LWR|_DIG))
#define isprint(c)	((_ctype)[(unsigned char)(c)]&(_PUN|_UPC|_LWR|_DIG|_BLK))
#define isgraph(c)	((_ctype)[(unsigned char)(c)]&(_PUN|_UPC|_LWR|_DIG))
#define iscntrl(c)	((_ctype)[(unsigned char)(c)]&_CTL)
#define isascii(c)	((unsigned)(c)<=0x7f)
extern int toupper(int);
extern int tolower(int);
#define toascii(c)	((unsigned char)(c)&0x7f)

#endif	/* _CTYPE_ */
