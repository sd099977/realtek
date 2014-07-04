.text
.globl	_ram_boot

_ram_boot:
	/*
	 * r4, r5, r6
	 */
	LDR     r4, =__bss_start
	LDR     r5, =__bss_end
	MOV     r6, #0x00000000		/* clear */

clear_loop:
	CMP     r4, r5
	BHS     clear_end			/* if reached end of bss, exit */
	STR     r6, [r4]
	ADD     r4, r4, #4
	B       clear_loop

clear_end:
	B       dvrmain				/* C entry */

.data
.globl resetrom
.globl resetrom_end
resetrom:
.word \

resetrom_end:
.word 0
.data
.globl hwsetting
.globl hwsetting_end
hwsetting:
.word \

hwsetting_end:
.word 0
.data
.globl hasharray
.globl hasharray_end
hasharray:
.word \

hasharray_end:
.word 0
.data
.globl signature
.globl signature_end
signature:
.word \

signature_end:
.word 0
.data
.globl ecbarray
.globl ecbarray_end
ecbarray:
.word \

ecbarray_end:
.word 0
.data
.globl rescuelinux
.globl rescuelinux_end
rescuelinux:
.word \

rescuelinux_end:
.word 0
.data
.globl linux_signature
.globl linux_signature_end
linux_signature:
.word \

linux_signature_end:
.word 0
.data
.globl cbc_linux
.globl cbc_linux_end
cbc_linux:
.word \

cbc_linux_end:
.word 0
.data
.globl hwsetting_sig_image
.globl hwsetting_sig_image_end
hwsetting_sig_image:
.word \

hwsetting_sig_image_end:
.word 0
.data
.globl dcas_key_sig_image
.globl dcas_key_sig_image_end
dcas_key_sig_image:
.word \

dcas_key_sig_image_end:
.word 0
.data
.globl logo
.globl logo_end
logo:
.word \

logo_end:
.word 0
.data
.globl logo2
.globl logo2_end
logo2:
.word \

logo2_end:
.word 0
.data
.globl logo3
.globl logo3_end
logo3:
.word \

logo3_end:
.word 0
.data
.globl logo4
.globl logo4_end
logo4:
.word \

logo4_end:
.word 0
.data
.globl logo5
.globl logo5_end
logo5:
.word \

logo5_end:
.word 0
.data
.globl logo6
.globl logo6_end
logo6:
.word \

logo6_end:
.word 0
.data
.globl logo7
.globl logo7_end
logo7:
.word \

logo7_end:
.word 0
.data
.globl logo8
.globl logo8_end
logo8:
.word \

logo8_end:
.word 0
