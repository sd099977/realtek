/************************************************************************
 *
 *  strtoul.c
 *
 ************************************************************************/

#include "dvrboot_inc/string.h"
#include "dvrboot_inc/ctype.h"

unsigned long
strtoul(
	const 	char 	*str,
	char 	**endptr,
	int 	base)
{
	const char *s;
	unsigned long acc, cutoff;
	int c;
	int neg, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	s = str;
	do {
		c = (unsigned char) *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

	cutoff = MAXUINT(sizeof(UINT32)) / (unsigned long)base;
	cutlim = MAXUINT(sizeof(UINT32)) % (unsigned long)base;
	for (acc = 0, any = 0;; c = (unsigned char) *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if ((acc > cutoff) || (acc == cutoff && c > cutlim)) {
			any = -1;
			acc = MAXUINT(sizeof(UINT32));
			//errno = ERANGE;
		} else {
			any = 1;
			acc *= (unsigned long)base;
			acc += c;
		}
	}
	if (neg && any > 0)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : (char *) str);
	return (acc);
}






