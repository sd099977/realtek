#echo "\$0 ==> $0"
#echo "\$1 ==> $1"
#echo "\$2 ==> $2"
#echo "param len ==> $#"

if [ $# -eq 1 ] ; then
echo "pem file is $1.pem"
fi

if [ -f $1.pem ] ; then

PEMFILE=$1
#echo "file is $PEMFILE"
PUBFILE=${PEMFILE}_pub
PRIFILE=${PEMFILE}_pri
R2FILE=${PEMFILE}_r2

#echo "${PEMFILE}.pem"
echo ""
./RtSSL2 rsa -print -modulous -i ${PEMFILE}.pem > ${PUBFILE}.txt
./RtSSL2 rsa -print -pri_exp -i ${PEMFILE}.pem > ${PRIFILE}.txt
./str2bin.pl `cat ${PUBFILE}.txt` > ${PUBFILE}.bin
./str2bin.pl `cat ${PRIFILE}.txt` > ${PRIFILE}.bin
./r2modm ${PUBFILE}.bin
cat R2.bin ${PUBFILE}.bin > ${PUBFILE}_R2.bin
cat ${PRIFILE}.bin R2.bin ${PUBFILE}.bin > ${PRIFILE}_R2.bin
./reverse.pl ${PUBFILE}_R2.bin > ${PUBFILE}_R2_rev.bin
./reverse.pl ${PRIFILE}_R2.bin > ${PRIFILE}_R2_rev.bin
cat rsa_dec_header  ${PUBFILE}_R2_rev.bin > ${PEMFILE}_dec.bin
cat rsa_enc_header  ${PRIFILE}_R2_rev.bin > ${PEMFILE}_enc.bin
mv ${PEMFILE}_dec.bin 40_${PEMFILE}_dec.txt
mv ${PEMFILE}_enc.bin 40_${PEMFILE}_enc.txt
rm ${PUBFILE}_R2_rev.bin
rm ${PRIFILE}_R2_rev.bin

else
echo "Please select a pem file."
fi

echo ""
