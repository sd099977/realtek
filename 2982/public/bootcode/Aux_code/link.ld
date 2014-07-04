OUTPUT_ARCH(mips)

ENTRY(RESET_EntryPoint)

MEMORY
{
	ram : org = 0x80000000, len = 64M
	dmem : org = 0x90000000, len = 8K
	sram_cp : org = 0xb8070000, len = 42K
}

SECTIONS
{
    .text_loader  0xb8070000 : { loader.o( section0 ) } > sram_cp
    .text        ALIGN(0x10) : { *(.text) } > sram_cp
    _e_text = ABSOLUTE(.);	/* end of text */

    .rodata                  : {
                                 _f_rodata = ABSOLUTE(.);
                                 *(.rodata .rodata.*)
                                 . = ALIGN(4); 
                                 _e_rodata = ABSOLUTE(.);
    } > sram_cp

    _e_text_rodata = _e_text + SIZEOF(.rodata);

    .data                    : {
                                 _f_data = ABSOLUTE(.);
                                 *(.data .sdata)
                                 . = ALIGN(4);

				 /* space for ARM redirect image */
				 _f_arm_start = ABSOLUTE(.);
				 empty.o (.arm_start_img)
                                 . = ALIGN(4); 
				 _e_arm_start = ABSOLUTE(.);

				 _f_arm_start2 = ABSOLUTE(.);
				 empty.o (.arm_start2_img)
                                 . = ALIGN(4); 
				 _e_arm_start2 = ABSOLUTE(.);

                                 . = ALIGN(64); 
                                 _e_data = ABSOLUTE(.);
     } > sram_cp

    .bss                     : {
                                 __bss_start = .;
                                 *(.bss .sbss .scommon COMMON) 
                                 . = ALIGN(4); 
                                 __bss_end = .;
    } > sram_cp 

/*
    .final        0xb8073ffc : { loader.o( final ) } > sram_cp
*/
    __heap_start_addr = (ADDR(.bss) + SIZEOF ( .bss ) + 0x10 - 1) & ~ (0x10 - 1);
    __gp = ADDR(.rodata);
    __Size_Of_SDRAM = 64M;
    __Start_Of_SDRAM = 0x80000000;

    __Start_Of_DMEM = 0x90000000;
    __Size_Of_DMEM = 8K;

    __Start_Of_CP42K = 0xb8070000;
    __Size_Of_CP42K = 42K;
}

