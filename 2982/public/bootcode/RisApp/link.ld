OUTPUT_ARCH(mips)

ENTRY(RESET_EntryPoint)

MEMORY
{
	ram : org = 0xa0020000, len = 42K
}

SECTIONS
{
    .text_loader  0xa0020000 : { loader.o( section0 ) } > ram
    .text        ALIGN(0x10) : { *(.text) } > ram
    .rodata      ALIGN(0x10) : { *(.rodata .rodata.*) } > ram
    .data        ALIGN(0x10) : { *(.data .sdata) } > ram
    .bss         ALIGN(0x10) : {
                                 __bss_start = .;
                                 *(.bss .sbss .scommon COMMON)
                                 . = ALIGN(4);
                                 __bss_end = .;
                               } > ram

    __heap_start_addr = (ADDR(.bss) + SIZEOF ( .bss ) + 0x10 - 1) & ~ (0x10 - 1);
    __gp = ADDR(.rodata);

	__Size_Of_SDRAM = 42K;
    __Start_Of_SDRAM = 0xa0020000;

}

