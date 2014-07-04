
make clean;make env=fpga ver=Ver_A
cp Aux_code_fpga.img ../bin/image/Aux_code_fpga_hw_parser.img

make clean;make env=realchip ver=Ver_A
cp Aux_code_realchip.img ../bin/image/Aux_code_realchip_hw_parser.img

make clean;make env=realchip ver=Ver_B
cp Aux_code_realchip.img ../bin/image/Aux_code_realchip_b_hw_parser.img

make clean;make env=realchip ver=Ver_C
cp Aux_code_realchip.img ../bin/image/Aux_code_realchip_c_hw_parser.img
