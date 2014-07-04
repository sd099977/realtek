#! /usr/bin/perl

#########################################################################
#
#  bin2str.pl
#
#  Convert byte file into string
#
#########################################################################
#
#  Usage:
#  	./bin2str.pl <binary file>
#
#  Example:
#  	./bin2str.pl key_img_seed.bin
#
#  Output:
# 	2DC2DF39420321D0CEF1FE2374029D95
#
#
#  Note:
#	
#
#########################################################################

open INPUT, $ARGV[0] or die $!;
$size = -s INPUT;
$idx = 0;

while ($idx < $size)
{
	read(INPUT, $bytes, 1);
	@a = map ord, split //, $bytes;
	printf "%02X", @a;
	$idx++;
}
