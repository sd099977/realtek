#! /usr/bin/perl -w

###############################################################################
# convert ROM code symbol table into define
# 
# Usage:
#	./convert_symbol.pl <input_symbol_file> > <output_header_file>
#
# Note:
#
###############################################################################
if( !defined(@ARGV) ) {
	print "Usage:\n\t ./convert_symbol.pl <input_symbol_file> > <output_header_file>\n";
	exit;
}

# This hash contains all mips32 functions in ROM code
#	key:function_name => value: 0 (value is not in use)
#
my %mips32_function = (
	# from reset.S
	__reset_vector => 0,
	func_nop => 0,
	print_str => 0,
	copy_data => 0,
	clear_memory => 0,
	sys_dcache_flush_all => 0,
	enable_uart_tx => 0,
	go_acpu_for_recovery_mode => 0,
	# from cpu_bisr.S
	do_kcpu_bisr => 0,
	do_acpu_bisr => 0,
	# from memcpy.S
	memcpy => 0,
	# from big_int.c
	Div => 0,
	Div_p => 0,
	Mod => 0,
	Mod_p => 0,
	# from crt_sirius.c
	enable_PLL => 0,
	st_enable_clock => 0,
	init_crt => 0,
	# from enable_clock.S
	enable_clock => 0,
	# from uart_sirius.c
	set_uart_rx_pin_mux => 0,
	init_uart => 0,
	# from utility.c
	wait_loop => 0,
	mask_register => 0,
);

# This hash contains static C functions
#	key:static function name => value: 0 (value is not in use)
# 
my %static_c_function = (
	# from mcp.c
	load_otp => 0,
	alloc_mcp_descriptor => 0,
	do_k_mcp => 0,
	do_s_mcp => 0,
	# from nand_operation.c
	nand_op_xfer_mode_read => 0,
	# from emmc_boot.c
	mmccr_read_rsp => 0,
	mmccr_reset_cr_state => 0,
	mmccr_TriggerXferCmd => 0,
	mmccr_SendCmd => 0,
	mmccr_Stream_Cmd => 0,
	mmc_read_ext_csd => 0,
	# from spi_n_operation.c
	sfc_read_page_to_cache_b => 0,
	# from verify_img.c
	append_padding => 0,
);

open CONFIG, $ARGV[0] or die $!;

print "#ifndef _ROM_SYMBOL_H_\n#define _ROM_SYMBOL_H_\n\n";

# traverse each line
while (<CONFIG>) {
	#print $_. '\n';
	next if /^[ \t]*$/;	# skip blank line
	next if /^#/;		# skip line begin with '#'
	next if /^\/\//;	# skip line begin with '//'

	s/\./_/;		# replace '.' with '_'
	s/\r?\n$//;	# remove CR/LF
	#s/\s+//;	# remove whitespace (including TAB)
	#s/^\s+//;	# remove leading whitespace
	#s/\s+$//;	# remove trailing whitespace
	#next unless length;	# next line unless anything left

	# parse attribute value pair
	@token = split / /, $_;
	#printf "%s => %s, %s\n" , $token[0], $token[1], $token[2];
	$addr = hex($token[0]);
	$type = $token[1];
	$name = $token[2];

	next if (($type eq 'A') || ($type eq 'a'));	# skip absolute symbol
	next if (($type eq 'R') || ($type eq 'r'));	# skip read only symbol
	next if ( ($type eq 't') && (! exists $static_c_function{$name}) );	# skip local text symbol

	# special handle of mips32/mips16 functions
	if ( ($type eq 'T') || ($type eq 't') ) {
		if (! exists $mips32_function{$name}) {
			$addr += 1;	# set ISA_mode in address bit 0 for mips16
		}
	}
	printf "#define ROM__%s__%s\t\t0x%x\n", $type, $name, $addr;
}

print "\n#endif /* _ROM_SYMBOL_H_ */\n";
close CONFIG;
