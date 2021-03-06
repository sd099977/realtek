#include <sysdefs.h>
//#include "string.h"

#include "sed_common.h"
#include "sed_setup.h"
#include "sed_cert.h"
#include "sed_r2r.h"
#include "sed_otp.h"
#include "sed_char.h"
#include "sed_rtk.h"
#include "sed_drv_uart.h"
#include "sed_drv_sfc.h"
#include "sed_drv_rng.h"
#include "sed_drv_gpio.h"
#include "sed_types.h"
#include "otp_util.h"

#include "big_util.h"
#include "big_int.h"
//#include "auto_config.h"


//void * memcpy(void * out,const void *in, UINT32 count);

//extern UINT32 alloc_count;


#define do_div64_32(res, high, low, base) ({ \
        unsigned long __quot32, __mod32; \
        unsigned long __cf, __tmp, __tmp2, __i; \
        \
        __asm__(".set   push\n\t" \
                ".set   noat\n\t" \
                ".set   noreorder\n\t" \
                "move   %2, $0\n\t" \
                "move   %3, $0\n\t" \
                "b      1f\n\t" \
                " li    %4, 0x21\n" \
                "0:\n\t" \
                "sll    $1, %0, 0x1\n\t" \
                "srl    %3, %0, 0x1f\n\t" \
                "or     %0, $1, %5\n\t" \
                "sll    %1, %1, 0x1\n\t" \
                "sll    %2, %2, 0x1\n" \
                "1:\n\t" \
                "bnez   %3, 2f\n\t" \
                " sltu  %5, %0, %z6\n\t" \
                "bnez   %5, 3f\n" \
                "2:\n\t" \
                " addiu %4, %4, -1\n\t" \
                "subu   %0, %0, %z6\n\t" \
                "addiu  %2, %2, 1\n" \
                "3:\n\t" \
                "bnez   %4, 0b\n\t" \
                " srl   %5, %1, 0x1f\n\t" \
                ".set   pop" \
                : "=&r" (__mod32), "=&r" (__tmp), \
                  "=&r" (__quot32), "=&r" (__cf), \
                  "=&r" (__i), "=&r" (__tmp2) \
                : "Jr" (base), "0" (high), "1" (low)); \
        \
        (res) = __quot32; \
        __mod32; })

#define do_div(n, base) ({ \
        unsigned long long __quot; \
        unsigned long __mod; \
        unsigned long long __div; \
        unsigned long __upper, __low, __high, __base; \
		unsigned long long __tmp; \
        \
        __div = (n); \
        __base = (base); \
        \
        __high = __div >> 32; \
        __low = __div; \
        __upper = __high; \
        \
        if (__high) {\
                __asm__("divu	 $0, %z1, %z2" \
                : "=x" (__tmp) \
                : "Jr" (__high), "Jr" (__base) \
                : "$0"); \
                __high = __tmp; \
                __upper = __tmp >> 32; }\
                \
        __mod = do_div64_32(__low, __upper, __low, __base); \
        \
        __quot = __high; \
        __quot = __quot << 32 | __low; \
        __quot; })

BI *InPutFromStr(char *str, const unsigned int system);

void* rsa_memcpy(void * out,const void *in, unsigned int count)
{
	unsigned int  i;
	unsigned char * des = out;
	unsigned char * soc = in;

	for(i=0;i<count;i++)
		des[i] = soc[i];

	return out;
}

BI *init()
{
	BI *p;
	//int i;

	p = (BI *)my_malloc(sizeof(BI));
	if (p == NULL) {
		return NULL;
	}

	memset(p, 0, sizeof(BI));
	p->m_nSign=1;
	p->m_nLength=1;
	//for(i=0;i<BI_MAXLEN;i++)p->m_ulValue[i]=0;
	return p;
}

BI *move(BI *A)
{
	//int i;
	BI *p;

	p = init();
	if (p == NULL)
		return NULL;

	//memcpy(p, A, sizeof(BI));
	rsa_memcpy(p, A, sizeof(BI));
	//p->m_nLength=A->m_nLength;
	//for(i=0;i<BI_MAXLEN;i++)p->m_ulValue[i]=A->m_ulValue[i];
	return p;
}
/*
BI *set(char *str)
{
	int i;
	BI *p;

	p = init();
	if (p == NULL)
		return NULL;


	return p;
}
*/
BI *move_p(unsigned long long b)
{
	//int i;
	BI *p;

	p = init();
	if (p == NULL)
		return NULL;

	if(b > 0xffffffff)
	{
		p->m_nLength=2;
		p->m_ulValue[1]=(unsigned int)(b>>32);
		p->m_ulValue[0]=(unsigned int)b;
	}
	else
	{
		p->m_nLength=1;
		p->m_ulValue[0]=(unsigned int)b;
	}

	//for(i=p->m_nLength;i<BI_MAXLEN;i++)
	//	p->m_ulValue[i]=0;
	return p;
}

/*
void Set_p(BI *p, unsigned long long b)
{
	if (p == NULL)
		return;

	memset(p, 0, sizeof(BI));

	if(b > 0xffffffff)
	{
		p->m_nLength=2;
		p->m_ulValue[1]=(unsigned int)(b>>32);
		p->m_ulValue[0]=(unsigned int)b;
	}
	else
	{
		p->m_nLength=1;
		p->m_ulValue[0]=(unsigned int)b;
	}
}
*/

/*
 *  0: A = B
 *  1: A > B
 * -1: A < B
 *
 */
int Cmp(BI *A, BI *B)
{
	int i;

	if(A->m_nLength > B->m_nLength)return 1;
	if(A->m_nLength < B->m_nLength)return -1;
	for(i=A->m_nLength-1;i>=0;i--)
	{
		if(A->m_ulValue[i] > B->m_ulValue[i])return 1;
		if(A->m_ulValue[i] < B->m_ulValue[i])return -1;
	}
	return 0;
}

int isZero(BI *A)
{
	if ((A->m_nLength == 1) && (A->m_ulValue[0] == 0))
		return 1;
	else
		return 0;
}

BI *Add(BI *A, BI *B)
{
	int i;
	unsigned int carry;
	unsigned long long sum;
	BI *p;

	if(A->m_nSign == B->m_nSign)
	{
		//p = move(A);
		p = A;
		carry = 0;
		sum = 0;
		if(p->m_nLength < B->m_nLength)
			p->m_nLength = B->m_nLength;

		for(i=0;i<p->m_nLength;i++)
		{
			sum = B->m_ulValue[i];
			sum = sum + p->m_ulValue[i] + carry;
			p->m_ulValue[i] = (unsigned int)sum;
			carry = (sum > 0xffffffff ? 1 : 0);
		}
		if(p->m_nLength < BI_MAXLEN)
		{
			p->m_ulValue[p->m_nLength] = carry;
			p->m_nLength += carry;
		}
		return p;
	}
	else{
		//p = move(B);
		p = B;
		p->m_nSign = 1 - p->m_nSign;
		return Sub(A, p);
	}
}

BI *Add_p(BI *A, int b)
{
	int i;
	BI *p;
	unsigned long long sum;

	if((A->m_nSign*b)>=0)
	{
		//p = move(A);
		p = A;
		sum=b+p->m_ulValue[0];
		p->m_ulValue[0]=(unsigned int)sum;
		if(sum>0xffffffff)
		{
			i = 1;
			while(p->m_ulValue[i]==0xffffffff)
			{
				p->m_ulValue[i]=0;
				i++;
			}
			p->m_ulValue[i]++;
			if(i<BI_MAXLEN)
				p->m_nLength=i+1;
		}
		return p;
	}
	else
		return Sub_p(A, -b);
}

BI *Sub(BI *A, BI *B)
{
	int i, cmp, len, carry;
	BI *p;
	unsigned long long num;
	unsigned int *s,*d;

	if(A->m_nSign == B->m_nSign)
	{
		//p = move(A);
		p = A;
		cmp = Cmp(p, B);
		if(cmp == 0)
		{
			//p = move_p(0);
			memset(p, 0, sizeof(BI));	// reset BI value
			return p;
		}

		if(cmp > 0)	// p > B
		{
			s = p->m_ulValue;
			d = B->m_ulValue;
			len = p->m_nLength;
		}
		if(cmp < 0)	// p < B
		{
			s = B->m_ulValue;
			d = p->m_ulValue;
			len = B->m_nLength;
			p->m_nSign = 1 - p->m_nSign;
		}

		carry = 0;
		for(i=0;i<len;i++)
		{
			if((s[i]-carry) >= d[i])
			{
				p->m_ulValue[i] = s[i] - carry - d[i];
				carry = 0;
			}
			else	// borrow from upper digit
			{
				num = ((unsigned long long)0x1 << 32) + s[i];
				p->m_ulValue[i] = (unsigned int)(num - carry - d[i]);
				carry = 1;
			}
		}

		while(p->m_ulValue[len-1] == 0)
			len--;

		p->m_nLength = len;
		return p;
	}
	else {
		//p = move(B);
		p = B;
		p->m_nSign = 1 - p->m_nSign;
		return Add(A, p);
	}

	return p;
}

BI *Sub_p(BI *A, int b)
{
	int i;
	BI *p;
	unsigned long long num;

	if((A->m_nSign*b)>=0)
	{
		//p = move(A);
		p = A;
		if(p->m_ulValue[0]>=(unsigned int)b)
		{
			p->m_ulValue[0] -= b;
			return p;
		}
		// A < b and A has only one block
		if(p->m_nLength==1)
		{
			p->m_ulValue[0] =b - p->m_ulValue[0];
			p->m_nSign = 1 - p->m_nSign;
			return p;
		}
		// A < b
		num = ((unsigned long long)0x1 << 32) + p->m_ulValue[0];
		p->m_ulValue[0] = (unsigned int)(num-b);
		i = 1;
		while(p->m_ulValue[i]==0)
		{
			p->m_ulValue[i]=0xffffffff;
			i++;
		}

		if(p->m_ulValue[i]==1)
			p->m_nLength--;

		p->m_ulValue[i]--;
		return p;
	}
	else
		return Add_p(A, -b);
}

BI *Mul(BI *A, BI *B)
{
	int i, j, k;
	BI *p, *q;
	unsigned long long mul;
	unsigned int carry;

	p = init();
	q = init();

	for(i=0;i<B->m_nLength;i++)
	{
		q->m_nLength = A->m_nLength;
		carry = 0;
		for(j=0;j<A->m_nLength;j++)
		{
			mul = A->m_ulValue[j];
			mul = mul * B->m_ulValue[i] + carry;
			q->m_ulValue[j] = (unsigned int)mul;
			carry = (unsigned int)(mul>>32);
		}
		if(carry && (q->m_nLength<BI_MAXLEN))
		{
			q->m_nLength++;
			q->m_ulValue[q->m_nLength-1] = carry;
		}

		if(q->m_nLength < BI_MAXLEN - i)
		{
			q->m_nLength += i;
			for(k=q->m_nLength-1;k>=i;k--)
				q->m_ulValue[k]=q->m_ulValue[k-i];
			for(k=0;k<i;k++)
				q->m_ulValue[k]=0;
		}
		p = Add(p, q);
	}

	p->m_nSign = ((A->m_nSign + B->m_nSign == 1) ? 0 : 1);

/*
	for(i=0;i<A->m_nLength;i++)
	{
		q->m_nLength=B->m_nLength;
		carry=0;
		for(j=0;j<B->m_nLength;j++)
		{
			mul=B->m_ulValue[j];
			mul=mul*A->m_ulValue[i]+carry;
			q->m_ulValue[j]=(unsigned int)mul;
			carry=(unsigned int)(mul>>32);
		}

		if(carry&&(q->m_nLength<BI_MAXLEN))
		{
			q->m_nLength++;
			q->m_ulValue[q->m_nLength-1]=carry;
		}
		// shift to correct position
		if(q->m_nLength<BI_MAXLEN-i)
		{
			q->m_nLength+=i;
			for(k=q->m_nLength-1;k>=i;k--)
				q->m_ulValue[k]=q->m_ulValue[k-i];
			for(k=0;k<i;k++)
				q->m_ulValue[k]=0;
		}
		p = move(Add(p, q));
	}

	if(B->m_nSign+A->m_nSign==1)
		p->m_nSign=0;
	else
		p->m_nSign=1;
*/
    //dennistuan add start 20130222
#ifdef FREE_MEMORY
    //memcpy( A, p, sizeof(BI));
    rsa_memcpy( A, p, sizeof(BI));
    my_free(sizeof(BI));   //free p
    my_free(sizeof(BI));   //free q
	return A;
#else
	return p;
#endif
     //dennistuan add end 20130222
}

BI *Mul_p(BI *A, int b)
{
	int i;
	unsigned int carry;
	BI *p;
	unsigned long long mul;

	//p = move(A);
	p = A;
	carry = 0;
	for(i=0;i<p->m_nLength;i++)
	{
		mul = p->m_ulValue[i];
		mul = mul * b + carry;
		p->m_ulValue[i] = (unsigned int)mul;
		carry = (unsigned int)((mul-p->m_ulValue[i])>>32);
	}

	if(carry&&(p->m_nLength<BI_MAXLEN))
	{
		p->m_nLength++;
		p->m_ulValue[p->m_nLength-1] = carry;
	}

	if(b<0)
		p->m_nSign = 1 - p->m_nSign;

	return p;
}

BI __attribute__ ((nomips16)) * Div(BI *A, BI *B)
{
	int i, len;
	BI *p, *q, *r;
	unsigned int carry;
	unsigned long long num, div;

	p = init();
	//q = move(A);
	q = A;
	r = init();
	carry = 0;
	while(Cmp(q, B)>0)
	{
		// compare leading digit
		if(q->m_ulValue[q->m_nLength-1] > B->m_ulValue[B->m_nLength-1])
		{
			len = q->m_nLength - B->m_nLength;
			div = q->m_ulValue[q->m_nLength-1] / (B->m_ulValue[B->m_nLength-1] + 1);
		}
		else if(q->m_nLength > B->m_nLength)
		{
			len = q->m_nLength - B->m_nLength - 1;
			num = q->m_ulValue[q->m_nLength-1];
			num = (num<<32) + q->m_ulValue[q->m_nLength-2];
			if(B->m_ulValue[B->m_nLength-1]==0xffffffff)
				div = (num>>32);
			else
				div = do_div(num, (B->m_ulValue[B->m_nLength-1] + 1));
		}
		else
		{
			p = Add_p(p, 1);
			break;
		}

		r = move_p(div);
		r->m_nLength += len;
		for(i=r->m_nLength-1;i>=len;i--)
			r->m_ulValue[i] = r->m_ulValue[i-len];
		for(i=0;i<len;i++)
			r->m_ulValue[i]=0;

		p = Add(p, r);
		r = Mul(r, B);
		q = Sub(q, r);
	}

	if(Cmp(q, B)==0)	// no remainder
		p = Add_p(p, 1);

	p->m_nSign = ((A->m_nSign+B->m_nSign==1) ? 0 : 1);
	return p;
}

BI __attribute__ ((nomips16)) * Div_p(BI *A, int b)
{
	int i;
	unsigned int carry;
	BI *p;
	unsigned long long div, mul;

	//p = move(A);
	p = A;
	if(p->m_nLength==1)
	{
		p->m_ulValue[0] = p-> m_ulValue[0] / b;
		return p;
	}

	carry = 0;
	for(i=p->m_nLength-1;i>=0;i--)
	{
		div = carry;
		div = (div<<32) + p->m_ulValue[i];
		p->m_ulValue[i] = (unsigned int) do_div(div, b);
		mul = (do_div(div, b)) * b;
		carry = (unsigned int)(div - mul);
	}

	if(p->m_ulValue[p->m_nLength-1] == 0)
		p->m_nLength--;
	if(b < 0)
		p->m_nSign = 1 - p->m_nSign;
	return p;
}

BI __attribute__ ((nomips16)) * Mod(BI *A, BI *B)
{
	int i, len;
	unsigned int carry;
	BI *p, *q;
	unsigned long long num, div;

	//p = move(A);
	p = A;
	//q = init();
	carry = 0;
	while(Cmp(p, B)>0)
	{
		//debug(p);
		//debug(B);
		// compare leading digit
		if(p->m_ulValue[p->m_nLength-1] > B->m_ulValue[B->m_nLength-1])
		{
			len = p->m_nLength - B->m_nLength;
			div = p->m_ulValue[p->m_nLength-1] / (B->m_ulValue[B->m_nLength-1] + 1);
			//printf("len: %d, div: %lld\n", len, div);
		}
		else if(p->m_nLength > B->m_nLength)
		{
			len = p->m_nLength - B->m_nLength - 1;
			num = p->m_ulValue[p->m_nLength-1];
			//printf("len: %d, num: %lld\n", len, num);
			num = (num<<32) + p->m_ulValue[p->m_nLength-2];

			if(B->m_ulValue[B->m_nLength-1]==0xffffffff)
				div = (num>>32);
			else
				div = do_div(num, (B->m_ulValue[B->m_nLength-1] + 1));
		}
		else
		{
			//printf("here\n");
			p = Sub(p, B);
			//debug(p);
			break;
		}

		q = move_p(div);
		q = Mul(q, B);
		//printf("q:\n");
		q->m_nLength += len;
		//debug(q);
		for(i=q->m_nLength-1;i>=len;i--) {
			q->m_ulValue[i]=q->m_ulValue[i-len];
			//printf("%x, %x\n", i, i-len);
		}
		for(i=0;i<len;i++)
			q->m_ulValue[i]=0;

		//printf("p:\n");
		p = Sub(p, q);
		//debug(p);
        //dennistuan add start 20130222
#ifdef FREE_MEMORY
        my_free( sizeof(BI) );   //free q
#endif
        //dennistuan add end 20130222
	}

	if(Cmp(p, B)==0) {
		//p = move_p(0);
		memset(p, 0, sizeof(BI));	// reset BI value
	}

	return p;
}

unsigned int __attribute__ ((nomips16)) Mod_p(BI *A, int b)
{
	int i;
	unsigned int carry;
	unsigned long long div;
	unsigned long long temp;

	if(A->m_nLength==1)
		return(A->m_ulValue[0]%b);

	carry = 0;
	for(i=A->m_nLength-1;i>=0;i--)
	{
		div = carry * ((unsigned long long)0x1 << 32) + A->m_ulValue[i];
		temp = do_div(div, b);
		carry = (unsigned int)(div - (temp * b));
	}
	return carry;
}


BI *Exp_Mod(BI *base, BI *exp, BI *mod)
{
	BI *x, *y, *z;
	//printf("Mon:\n");
	x = move_p(1);
	y = move(base);
	z = move(exp);

	while ((z->m_nLength != 1) || (z->m_ulValue[0])) {
		//printf("=> ");
		if (z->m_ulValue[0] & 1) {
			//printf("1, ");
			z = Sub_p(z, 1);
			//printf("3, ");
			x = Mul(x, y);
			//printf("5\n");
			x = Mod(x, mod);
		}
		else {
			//printf("2, ");
			z = Div_p(z, 2);
			//printf("4, ");
			y = Mul(y, y);
			//printf("6\n");
			y = Mod(y, mod);
		}
	}

	return x;
}

#if 1 // (not use it in Sirius)
BI *InPutFromStr(char *str, const unsigned int system)
{
	int i, c, len;
	BI *p;

	c = 0;
	p = init();
	if (p == NULL)
		return NULL;

	len = rsa_strlen(str);
	for (i=0; i<len; i++) {
		p = Mul_p(p, system);

		if (system == DEC)
			c = str[i] - 48;
		else if (system == HEX) {
			if (str[i] >= 97)		// 'a' ~ 'f'
				c = (str[i] - 97) + 10;
			else if (str[i] >= 65)		// 'A' ~ 'F'
				c = (str[i] - 65) + 10;
			else				// '0' ~ '9'
				c = str[i] - 48;
		}
		p = Add_p(p, c);
	}

	return p;
}
#endif

BI *InPutFromAddr(unsigned char *addr, int len)
{
	int i, space, count;
	BI *p;

	p = init();
	if (p == NULL)
		return NULL;

	count = len / sizeof(unsigned int);
	space = len % sizeof(unsigned int);
	if (space)
		count++;

	if (count > BI_MAXLEN)
		return NULL;		// overflow

	p->m_nLength = count;
/*
	i = count - 1;
	if (space) {
		// highest element may be not full
		p->m_ulValue[i] = (*(unsigned int *)addr) >> (sizeof(unsigned int) - space) * 8;
		addr += space;
		i--;
	}

	while (i >= 0) {
		//p->m_ulValue[i] = *(unsigned int *)addr;
		//addr += 4;
		p->m_ulValue[i] = *addr << 24;
		addr++;
		p->m_ulValue[i] |= *addr << 16;
		addr++;
		p->m_ulValue[i] |= *addr << 8;
		addr++;
		p->m_ulValue[i] |= *addr;
		addr++;
		i--;
	}
*/
	i = 0;
	if (space) {
		// highest element may be not full
		p->m_ulValue[i] = (*(unsigned int *)addr) >> (sizeof(unsigned int) - space) * 8;
		addr += space;
		i--;
	}

	while (i < count) {
		p->m_ulValue[i] = *(unsigned int *)addr;
		addr += 4;
		//p->m_ulValue[i] = *addr << 24;
		//addr++;
		//p->m_ulValue[i] |= *addr << 16;
		//addr++;
		//p->m_ulValue[i] |= *addr << 8;
		//addr++;
		//p->m_ulValue[i] |= *addr;
		//addr++;
		i++;
	}

	return p;
}

#if 0 // (not use it in Sirius)
char *OutPutToStr(BI *A, const unsigned int system)
{
	unsigned int i, j;
	unsigned int str_size;
	BI *p;
	char ch;
	char *str;

	if (isZero(A))
		return "0";

	// an unsigned int variable approximately equals to 10 decimal digit
	str_size = 10 * A->m_nLength + 1;
	str = (char *)my_malloc(str_size);
	if (str == NULL)
		return NULL;

	//alloc_count += str_size;

	memset(str, 0, str_size);
	p = move(A);
	i = 0;
	while(p->m_ulValue[p->m_nLength-1] > 0)
	{
		ch = Mod_p(p, system);	// to ascii

		if(system == DEC)
			ch += 48;
		else if (system == HEX)
			ch += (ch < 10 ? 48 : 55);

		str[i++] = ch;
		//printf("%d ", ch);
		p = Div_p(p, system);
	}

	//printf("\n");

	if (i <= 1)	// only one digit
		return str;
	// reverse string order
	i--;
	j = 0;
	while (i > j) {
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i--;
		j++;
	}

	return str;
}
#endif

void OutPutToAddr(BI *A, unsigned char *addr, char reverse)
{
	int i;

	if (reverse) {
		for (i = A->m_nLength - 1; i >= 0; i--) {
			*addr = (A->m_ulValue[i] >> 24) & 0xff;
			addr++;
			*addr = (A->m_ulValue[i] >> 16) & 0xff;
			addr++;
			*addr = (A->m_ulValue[i] >> 8) & 0xff;
			addr++;
			*addr = (A->m_ulValue[i] >> 0) & 0xff;
			addr++;
		}
	}
	else {
		for (i = 0; i < A->m_nLength; i++, addr+=4)
			*(unsigned int *)addr = A->m_ulValue[i];
	}
}

/*
void debug(BI *A)
{

	int i;

	if (A->m_nSign == 1)
		printf("+ ");
	else
		printf("- ");

	print_hex(A->m_nLength);
	printf(" [");
	for (i=A->m_nLength-1; i>=0; i--) {
		print_hex(A->m_ulValue[i]);
		printf(", ");
	}
	printf("]\n");
}
*/
#if 1
	/******************
	 * Add for HW RSA *
	 ******************/ //Sean
	void BI_setbit (BI *bi, int n)
	{
		if (bi == NULL)
			return;

		//bi->m_nSign = 0;
		bi->m_nLength = (n >> 5) + 1;

		bi->m_ulValue[bi->m_nLength - 1] = 1 << ( n & 0x1F );

		return;
	}

	int BI_chkmsbbit (BI *bi)
	{
		UINT32 check_bit;
		int i, j;

		if (bi == NULL)
			return -1;

		for ( i = bi->m_nLength - 1; i >= 0; i-- )
		{
			check_bit = 0x80000000;

			for ( j = 0; j < 32; j++ )
			{
				if ( ( bi->m_ulValue[i] & check_bit ) == check_bit )
				{
					return ( ( ( i + 1 ) << 5 ) - ( j + 1 ) );
				}

				check_bit >>= 1;
			}
		}

		return 0;
	}

	int BI_is_bit_set (BI *bi, int n)
	{
		if (bi == NULL)
			return -1;

		if ( ( bi->m_ulValue[n >> 5] ) & ( 1 << (n & 0x1F) ) )
			return 1;
		else
			return 0;
	}
#endif
