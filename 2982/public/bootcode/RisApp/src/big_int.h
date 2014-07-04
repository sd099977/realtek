#ifndef _BIG_INT_H_

#define BI_MAXLEN 129
#define DEC 10
#define HEX 16


typedef struct big_int {
    int m_nSign;
    int m_nLength;
    unsigned int m_ulValue[BI_MAXLEN];
} BI;


BI *init();
BI *move(BI *A);
BI *move_p(unsigned long long b);
int Cmp(BI *A, BI *B);
int isZero(BI *A);

BI *Add(BI *A, BI *B);
BI *Sub(BI *A, BI *B);
BI *Mul(BI *A, BI *B);
BI __attribute__ ((nomips16)) * Div(BI *A, BI *B);
BI __attribute__ ((nomips16)) * Mod(BI *A, BI *B);

BI *Add_p(BI *A, int b);
BI *Sub_p(BI *A, int b);
BI *Mul_p(BI *A, int b);
BI __attribute__ ((nomips16)) * Div_p(BI *A, int b);
unsigned int __attribute__ ((nomips16)) Mod_p(BI *A, int b);

BI *Exp_Mod(BI *base, BI *exp, BI *mod);

#if 0 // (not use it in Sirius)
BI *InPutFromStr(char *str, const unsigned int system);
char *OutPutToStr(BI *A, const unsigned int system);
#endif

BI *InPutFromAddr(unsigned char *addr, int len);
void OutPutToAddr(BI *A, unsigned char *addr, char reverse);

int BI_chkmsbbit (BI *bi);
int BI_is_bit_set (BI *bi, int n);
//void debug(BI *A);

#define _BIG_INT_H_
#endif /* #ifndef _BIG_INT_H_ */
