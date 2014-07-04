/************************************************************************
 *
 *  strstr.c
 *
 ************************************************************************/

//#include "dvrboot_inc/string.h"

char *strstr(
	const char 	*s1, 
	const char 	*s2)
{
    const char *s ;
    const char *t ;

    if (!s1 || !s2)
	return (0);

    if (!*s2)
	return ((char*)s1);

    for (; *s1; s1++) 
    {
	if (*s1 == *s2) 
        {
	    t = s1;
	    s = s2;
	    for (; *t; s++, t++) 
            {
		if (*t != *s)
		    break;
	    }
	    if (!*s)
		return ((char*)s1);
	}
    }
    return (0);
}
