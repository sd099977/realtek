#ifndef  __LD_INTERFACE_H_
#define  __LD_INTERFACE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <asm/arch/rbus/rbusLD_InterfaceReg.h>


extern void ld_Init(void);
extern int ld_Write(unsigned int* data, unsigned int length,LD_WRITE_MODE mode);
extern unsigned int ld_Read(unsigned int addr);




#ifdef __cplusplus
}
#endif
#endif

