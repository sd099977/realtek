#! /usr/bin/perl

open(IFILE, $ARGV[0]) || die $!;
$size = -s IFILE;
print "file size = " . $size . " bytes\n";
$output_file = "$ARGV[0]" . ".filesize";

# Don't forget to add 4 to size
# Which is the length of the unsigned int
$pad_len = 64 - (($size+4) &0x3f);
if ($pad_len <= 8) {
	$pad_len = $pad_len + 64;
}
#bootcode size + padding size + sha256 size + RSA2048 key size + RSA signature length
$final_size = ($size+4) + $pad_len + 32 + 256 +256;
print "pad size = " . $pad_len . " bytes\n";
print "final size = " . $final_size . " bytes\n";
open(OFILE, ">$output_file") || die $!;
print OFILE pack('l<',$final_size);

close(OFILE);
