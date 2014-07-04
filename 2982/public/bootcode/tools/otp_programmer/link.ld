MEMORY
{
	ram : org = 0x01500000, len = 0x200000   
}

SECTIONS
{
	.text 0x01500000 :  
	{ 
		_ftext = .;
		loader.o(.text)  
		*(.rodata)
		etext = .;
	}

	.data	      ALIGN(0x4) : 
	{
		_fdata = .;
	       	*(.data) *(.sdata) *(.lit4) *(.lit8)
		_edata = .;
	}

	.bss	      ALIGN(0x4) : 
	{ 
		. = ALIGN(4);
		__bss_start = .; 
		*(.sbss) *(.bss) *(.scommon)
		. = ALIGN(4);
		__bss_end = .; 
	} /* 64KB */

	__cache_line_size = 0x20;
	__heap_start_addr = (ADDR(.bss) + SIZEOF ( .bss ) + __cache_line_size - 1) & ~ (__cache_line_size - 1);
}

