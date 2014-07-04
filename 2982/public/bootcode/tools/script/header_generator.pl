#! /usr/bin/perl -w

###############################################################################
# generate binary header data from input config file
# 
# Usage:
#	./header_generator.pl <input_config> <output_binary>
#
# Note:
#	1. each entry is unsigned int value (4B)
#	2. Output order will be the same as in config file
#
###############################################################################
if( !defined(@ARGV) ) {
	print "Usage:\n\t ./header_generator.pl <input_config> <output_binary>\n";
	exit;
}

open CONFIG, $ARGV[0] or die $!;
open OUTPUT, '>', $ARGV[1] or die $!;

# traverse each line
while (<CONFIG>) {
	#print $_. '\n';
	next if /^[ \t]*$/;	# skip blank line
	next if /^#/;		# skip line begin with '#'
	next if /^\/\//;	# skip line begin with '//'

	s/\r?\n$//;	# remove CR/LF
	s/\s+//;	# remove whitespace (including TAB)
	#s/^\s+//;	# remove leading whitespace
	#s/\s+$//;	# remove trailing whitespace
	next unless length;	# next line unless anything left

	# parse attribute value pair
	@token = split /=/, $_;
	#printf "%s => %s\n" , $token[0], $token[1];

	# output unsigned int (4B)
	print OUTPUT pack ('L', hex($token[1]));	# little endian
	#print OUTPUT pack ('N', hex($token[1]));	# big endian
}

close CONFIG;
close OUTPUT;