/*
//-----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2008-2012  ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//
//      SVN Information
//
//      Checked In          : $Date: 2009-12-07 16:50:12 +0000 (Mon, 07 Dec 2009) $
//
//      Revision            : $Revision: 126049 $
//
//      Release Information : CORTEX-A7-r0p4-00rel0
//
//-----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <time.h>

extern void $Super$$main(void);

extern unsigned int get_core_id(void);
extern void test_finish(void);

void $Sub$$main(void)
{
  unsigned int tmp = get_core_id();

  printf("#\n");
  printf("# CPU %d - Running Dhrystone\n", tmp);
  printf("#\n");

  $Super$$main();  // calls original main()

  return;
}

//    semihosting retargets
struct __FILE { int handle;};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  unsigned int tmp = (get_core_id())*4;
  volatile unsigned char* tube_addr = (unsigned char*)(TBVAL_SYSADDR+tmp);
  *tube_addr = (unsigned char)ch;
  return ch;
}

int fputs(const char* str, FILE *f)
{
  while (*str != 0)
  fputc(*str++, f);

  return 0;
}

 void _ttywrch(int ch)
{
  unsigned int tmp = (get_core_id())*4;
  int *ptr_tube;
  ptr_tube = (int*)(TBVAL_SYSADDR+tmp);
  *ptr_tube = (char)ch;
}

void _sys_exit(int return_code)
{
  test_finish();
}

int fgetc(FILE *f)
{
  return 0;
}
 
clock_t clock(void)
{
  return (clock_t)0;
}
