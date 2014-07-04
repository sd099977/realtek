MEMORY
{
	ram : org = 0x01500000, len = 0x200000   
/*	rom : org = 0xbfc00000, len = 0x200000 */
}
SECTIONS
{
	.text 0x01500000 :  
	{ 
		_ftext = .;
		ram_boot.o(.text)  
		*(.rodata)
		dvrmain.o(.text)
		etext = .;
	}
	
	.data	      ALIGN(0x4) : 
	{
		_fdata = .;
	       	*(.data) *(.sdata) *(.lit4) *(.lit8)
		_edata = .;

		/* NOCS Certificate image */
		_f_scs_nocs_cert_tdb = .;
		dvrload.o(.scs_nocs_cert_tdb);
		_e_scs_nocs_cert_tdb = .;

		_f_scs_nocs_cert_em = .;
		dvrload.o(.scs_nocs_cert_em);
		_e_scs_nocs_cert_em = .;

		_f_scs_nocs_cert_sig = .;
		dvrload.o(.scs_nocs_cert_sig);
		_e_scs_nocs_cert_sig = .;

		/* Params Area image */
		_f_scs_params_area_tdb = .;
		dvrload.o(.scs_params_area_tdb);
		_e_scs_params_area_tdb = .;

		_f_scs_params_area_em = .;
		dvrload.o(.scs_params_area_em);
		_e_scs_params_area_em = .;

		_f_scs_params_area_sig = .;
		dvrload.o(.scs_params_area_sig);
		_e_scs_params_area_sig = .;

		/* Aux Code image */
		_f_scs_aux_code_tdb = .;
		dvrload.o(.scs_aux_code_tdb);
		_e_scs_aux_code_tdb = .;

		_f_scs_aux_code_em = .;
		dvrload.o(.scs_aux_code_em);
		_e_scs_aux_code_em = .;

		_f_scs_aux_code_sig = .;
		dvrload.o(.scs_aux_code_sig);
		_e_scs_aux_code_sig = .;

		/* DTE Bootcode image */
		_f_scs_dte_bootcode_tdb = .;
		dvrload.o(.scs_dte_bootcode_tdb);
		_e_scs_dte_bootcode_tdb = .;

		_f_scs_dte_bootcode_em = .;
		dvrload.o(.scs_dte_bootcode_em);
		_e_scs_dte_bootcode_em = .;

		_f_scs_dte_bootcode_sig = .;
		dvrload.o(.scs_dte_bootcode_sig);
		_e_scs_dte_bootcode_sig = .;

		/* DTE KBoot image */
		_f_scs_dte_kboot_tdb = .;
		dvrload.o(.scs_dte_kboot_tdb);
		_e_scs_dte_kboot_tdb = .;

		_f_scs_dte_kboot_em = .;
		dvrload.o(.scs_dte_kboot_em);
		_e_scs_dte_kboot_em = .;

		_f_scs_dte_kboot_sig = .;
		dvrload.o(.scs_dte_kboot_sig);
		_e_scs_dte_kboot_sig = .;

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
