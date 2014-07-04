#! /usr/bin/perl

open(IFILE, $ARGV[0]) || die $!;
$size = -s IFILE;
print "file size = " . $size . " bytes\n";
$output_file = "$ARGV[0]" . ".filesize";

open(OFILE, ">$output_file") || die $!;
print OFILE pack('l<',$size);

close(OFILE);