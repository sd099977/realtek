#! /usr/bin/perl


open(IFILE, $ARGV[0]) || die $!;
$size = -s IFILE;
close(IFILE);

# RESCUE_HEADER_SIZE 0x10
# RESCUE_HEADER_MAGICNO 0x6330beef
# RESCUE_RESERVED_DATA 0x0
$magicno = 0x6330beef;
$size = $size + 0x10;
$reserved_data = 0x0;

$pad_len = 64 - ($size &0x3f);
if ($pad_len <= 8) {
	$pad_len = $pad_len + 64;
}
#final size = rescue size + pad_len + 32(hash_size) 
print pack('L',$magicno);
print pack('L',$size+$pad_len+32);
print pack('L',$reserved_data);
print pack('L',$reserved_data);

