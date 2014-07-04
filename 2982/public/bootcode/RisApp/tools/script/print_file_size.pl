#! /usr/bin/perl -w

###############################################################################
# print file size (in hex format)
# 
# Usage:
#	./print_file_size.pl <file_name>
#
#
###############################################################################
die "no_input_file\n" if( !defined(@ARGV) );

open BINARY, $ARGV[0] or die "unknown($!)\n";

my $size = -s BINARY;
printf "0x%08x\n", $size;

close BINARY;

