#! /usr/bin/perl -w

################################################################################
#
# print input binary in byte-reversed order
#
# Usage:
#	./reverse.pl <input_file>
#
################################################################################

if( defined(@ARGV) ) {

	open TXT, $ARGV[0] or die $!;
	my $size = -s TXT;
	my $current = 0;
	
	# read each byte
	while ($current++ < $size) {
		read(TXT, $byte, 2);
		push(@in, $byte);
	}
		
	# print reversely
	@in = reverse @in;
	foreach (@in) {
		print $_;
	}

	close TXT;

}
else {
	die "Usage:\n\treverse <input_file>\n";
}
