CUR_DIR=${PWD}
NOCS_DIR=../../../../../../../..
BOOTCODE_DIR=../../../../../../../../../..
LIB_NAME=libbsdserver
make clean
#rm ./distrib/libbsdserver.a
rm -f ${NOCS_DIR}/${LIB_NAME}.bp
make all
cp  ./distrib/${LIB_NAME}.a ${NOCS_DIR}/${LIB_NAME}.bp