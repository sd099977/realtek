if [ $# -eq 1 ] ; then
echo "Selected link file is link.$1"
fi

DIR_TOP=${PWD}
DIR_TFTP_ROOT=/home/alexkh/tftproot_OS
DIR_FLASH_MAKER=${DIR_TOP}/tools/flash_image_maker

FILE_QQ=qq_ris.bin
FILE_AP=ap_template.bin
FILE_TAG_LINK=link.ld
FILE_SOR_LINK=link.ld.$1
FILE_DEF_LINK=link.ld.ram

if [ -f ${FILE_SOR_LINK} ] ; then
echo "cp ${FILE_SOR_LINK} to  ${FILE_TAG_LINK}"
cp -f ${FILE_SOR_LINK} ${FILE_TAG_LINK}
fi

rm -rf ${DIR_TOP}/out/${FILE_AP}
rm -rf ${DIR_TFTP_ROOT}/${FILE_QQ}

make -C ./bin
cp ${DIR_FLASH_MAKER}/qq.bin ${DIR_TFTP_ROOT}/${FILE_QQ}
cp ${DIR_TOP}/out/${FILE_AP} ${DIR_TFTP_ROOT}/${FILE_AP}
cp -f ${FILE_DEF_LINK} ${FILE_TAG_LINK}

if [ -f ${FILE_SOR_LINK} ] ; then
echo ""
echo "======================================================="
echo "Selected link file is ${FILE_SOR_LINK}"
echo "Original link file ${FILE_DEF_LINK} have been restored."
echo "======================================================="
echo ""
echo ""
fi

