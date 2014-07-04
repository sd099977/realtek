OUTPUT_DIR=./output
PRJ_DIR=$(PWD)/../..
PRJ_BIN_DIR=$(PRJ_DIR)/bin
PRJ_IMG_DIR=$(PRJ_BIN_DIR)/image

##############################################################################
#
# Includes
#
##############################################################################
ifneq ($(origin PRJ), undefined)
include $(PRJ_BIN_DIR)/$(PRJ).inc
endif

##############################################################################
#
# Commands
#
##############################################################################
SHA_EXE=../do_sha256/do_sha256
RTSSL_EXE=../RSA_Tool/RtSSL
RTSSL2_EXE=../RtSSL/RtSSL2
R2MODM_EXE=../r2modm/r2modm
OTP_BITMAP_GEN_EXE=../otp_bitmap_generator/otp_bitmap_generator
REVERSE=perl ../script/reverse.pl
STR2BIN=perl ../script/str2bin.pl
#BIN2STR=perl ../script/bin2str.pl
HEADER_GENERATOR=perl ../script/header_generator.pl
GEN_AUX_CODE_AREA_SIZE=perl ../script/gen_aux_code_area_size.pl
PRINT_FILE_SIZE=perl ../script/print_file_size.pl

##############################################################################
#
# Input/Output files
#
##############################################################################
ifeq ($(origin PRJ), undefined)
# no inc file specified, use default instead
RSA_ROOT_KEY=rsa_root_key.pem
RSA_EXT_KEY=rsa_ext_key.pem
else
# from inc file
#RSA_ROOT_KEY=$(PRJ_IMG_DIR)/$(Config_Secure_RSA_Root_Key_File)
#RSA_EXT_KEY=$(PRJ_IMG_DIR)/$(Config_Secure_RSA_Ext_Key_File)
# get from customer folder
RSA_ROOT_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_RSA_Root_Key_File)
RSA_EXT_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_RSA_Ext_Key_File)
AES_ROOT_K_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_AES_Root_K_Key_File)
AES_ROOT_S_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_AES_Root_S_Key_File)
AES_ROOT_AUX_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_AES_Root_AUX_Key_File)
AES_EXT_FPK_KEY=$(PRJ_BIN_DIR)/customer/$(Config_DTE_Bootcode_Board_name_Value)/$(Config_Secure_AES_Ext_FPK_Key_File)
endif

ifeq ($(Config_OTP_Secure_Boot), TRUE)
IMAGE_ENCRYPT=TRUE
else
IMAGE_ENCRYPT=FALSE
endif

ifeq ($(Config_Process_DTE_KBoot), TRUE)
GENERATE_KBOOT_SIZE=TRUE
else
GENERATE_KBOOT_SIZE=FALSE
endif

PKCS_PADDING=pkcs_padding.dat

KEY_RIGHTS_PREFIX=key_rights
KEY_RIGHTS_INC=$(KEY_RIGHTS_PREFIX).inc
KEY_RIGHTS_BIN=$(OUTPUT_DIR)/.$(KEY_RIGHTS_PREFIX).bin

SCS_NOCS_CERT_KEY_R2_BIN=$(OUTPUT_DIR)/cert_r2.bin

AES_ROOT_K_KEY_AP=$(OUTPUT_DIR)/key_root_k_ap.bin
AES_ROOT_K_KEY_ROM=$(OUTPUT_DIR)/key_root_k_rom.bin


CONTROLLING_DATA_PREFIX=controlling_data
CONTROLLING_DATA_INC=$(CONTROLLING_DATA_PREFIX).inc
CONTROLLING_DATA_BIN=$(OUTPUT_DIR)/.$(CONTROLLING_DATA_PREFIX).bin

FLASH_PROTECTION_KEY_PREFIX=flash_protection_key
FLASH_PROTECTION_KEY_INC=flash_protection_key.inc
FLASH_PROTECTION_KEY_BIN=$(OUTPUT_DIR)/.flash_protection_key.bin

RSA_ROOT_KEY_PREFIX=rsa_root_key
RSA_ROOT_KEY_RAW=$(OUTPUT_DIR)/.$(RSA_ROOT_KEY_PREFIX).raw
RSA_ROOT_KEY_BIN=$(OUTPUT_DIR)/$(RSA_ROOT_KEY_PREFIX).bin
RSA_ROOT_KEY_R2_BIN=$(OUTPUT_DIR)/$(RSA_ROOT_KEY_PREFIX)_r2.bin

SCS_NOCS_CERT_PREFIX=scs_nocs_certificate
SCS_NOCS_CERT_KEY_RAW=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_key.raw
SCS_NOCS_CERT_KEY_BIN=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_key.bin
SCS_NOCS_CERT_PARAM_INC=$(SCS_NOCS_CERT_PREFIX)_param.inc
SCS_NOCS_CERT_PARAM_BIN=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_param.bin
SCS_NOCS_CERT_PARAM_DATA=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_param.data.bin
SCS_NOCS_CERT_PARAM_BIN_PAD=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_param.bin.pad
SCS_NOCS_CERT_TDB=$(OUTPUT_DIR)/$(SCS_NOCS_CERT_PREFIX).tdb
SCS_NOCS_CERT_PADDING=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX).pad
SCS_NOCS_CERT_HASH=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX).hash
SCS_NOCS_CERTITICATE_EM=$(OUTPUT_DIR)/$(SCS_NOCS_CERT_PREFIX).em
SCS_NOCS_CERT_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_sig.raw
SCS_NOCS_CERT_SIG_BIN=$(OUTPUT_DIR)/$(SCS_NOCS_CERT_PREFIX)_sig.bin
#SCS_NOCS_CERT_IMG=$(SCS_NOCS_CERT_PREFIX).img

SCS_PARAMS_AREA_PREFIX=scs_params_area
#SCS_PARAMS_AREA_BIN=$(SCS_PARAMS_AREA_PREFIX).bin
SCS_PARAMS_AREA_PARAM_INC_PART0=$(SCS_PARAMS_AREA_PREFIX)_param_0.inc
SCS_PARAMS_AREA_PARAM_INC_PART1=$(SCS_PARAMS_AREA_PREFIX)_param_1.inc
SCS_PARAMS_AREA_PARAM_INC_PART2=$(SCS_PARAMS_AREA_PREFIX)_param_2.inc
SCS_PARAMS_AREA_PARAM_INC=$(SCS_PARAMS_AREA_PREFIX)_param.inc
SCS_PARAMS_AREA_PARAM_BIN=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX)_param.bin
SCS_PARAMS_AREA_PARAM_BIN_TMP=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX)_param.bin.tmp
SCS_PARAMS_AREA_PARAM_BIN_PAD=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX).bin.pad
SCS_PARAMS_AREA_TDB=$(OUTPUT_DIR)/$(SCS_PARAMS_AREA_PREFIX).tdb
SCS_PARAMS_AREA_PADDING=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX).pad
SCS_PARAMS_AREA_HASH=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX).hash
SCS_PARAMS_AREA_EM=$(OUTPUT_DIR)/$(SCS_PARAMS_AREA_PREFIX).em
SCS_PARAMS_AREA_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_PARAMS_AREA_PREFIX)_sig.raw
SCS_PARAMS_AREA_SIG_BIN=$(OUTPUT_DIR)/$(SCS_PARAMS_AREA_PREFIX)_sig.bin
#SCS_PARAMS_AREA_IMG=$(SCS_PARAMS_AREA_PREFIX).img
SCS_PARAMS_AREA_BOOT_SPECIFIC_TEMPLATE=$(SCS_PARAMS_AREA_PREFIX)_boot_specific_params_template
SCS_PARAMS_AREA_BOOT_SPECIFIC_INC=$(SCS_PARAMS_AREA_PREFIX)_boot_specific_params.inc
SCS_PARAMS_AREA_AUX_AREA_SIZE_INC=$(SCS_PARAMS_AREA_PREFIX)_aux_area_size.inc
SCS_PARAMS_AREA_ADDRESS_OF_AUXILIARY_CODE_AREA_TEMPLATE=$(SCS_PARAMS_AREA_PREFIX)_address_of_auxiliary_code_area_template
SCS_PARAMS_AREA_ADDRESS_OF_AUXILIARY_CODE_AREA_INC=$(SCS_PARAMS_AREA_PREFIX)_address_of_auxiliary_code_area.inc
SCS_PARAMS_AREA_PARAM_HWSETTING_BIN=../flash_image_maker/hw_setting.bin

SCS_AUX_CODE_PREFIX=scs_aux_code
SCS_AUX_CODE_BIN=$(SCS_AUX_CODE_PREFIX).bin
SCS_AUX_CODE_INC=$(SCS_AUX_CODE_PREFIX).inc
#SCS_AUX_CODE_PARAM_INC=$(SCS_AUX_CODE_PREFIX)_param.inc
#SCS_AUX_CODE_PARAM_BIN=$(SCS_AUX_CODE_PREFIX)_param.bin
SCS_AUX_CODE_BIN_PAD=$(OUTPUT_DIR)/.$(SCS_AUX_CODE_PREFIX).bin.pad
SCS_AUX_CODE_TDB=$(OUTPUT_DIR)/$(SCS_AUX_CODE_PREFIX).tdb
SCS_AUX_CODE_PADDING=$(OUTPUT_DIR)/.$(SCS_AUX_CODE_PREFIX).pad
SCS_AUX_CODE_HASH=$(OUTPUT_DIR)/.$(SCS_AUX_CODE_PREFIX).hash
SCS_AUX_CODE_EM=$(OUTPUT_DIR)/$(SCS_AUX_CODE_PREFIX).em
SCS_AUX_CODE_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_AUX_CODE_PREFIX)_sig.raw
SCS_AUX_CODE_SIG_BIN=$(OUTPUT_DIR)/$(SCS_AUX_CODE_PREFIX)_sig.bin
#SCS_AUX_CODE_IMG=$(SCS_AUX_CODE_PREFIX).img

SCS_DTE_BOOTCODE_PREFIX=scs_dte_bootcode
SCS_DTE_BOOTCODE_BIN=$(SCS_DTE_BOOTCODE_PREFIX).bin
#SCS_DTE_BOOTCODE_PARAM_INC=$(SCS_DTE_BOOTCODE_PREFIX)_param.inc
#SCS_DTE_BOOTCODE_PARAM_BIN=$(SCS_DTE_BOOTCODE_PREFIX)_param.bin
SCS_DTE_BOOTCODE_BIN_PAD=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).bin.pad
SCS_DTE_BOOTCODE_TDB=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).tdb
SCS_DTE_BOOTCODE_PADDING=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX).pad
SCS_DTE_BOOTCODE_HASH=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX).hash
SCS_DTE_BOOTCODE_EM=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).em
SCS_DTE_BOOTCODE_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX)_sig.raw
SCS_DTE_BOOTCODE_SIG_BIN=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX)_sig.bin
#SCS_DTE_BOOTCODE_IMG=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).img
TMP_FILE=$(OUTPUT_DIR)/.tmp_file

SCS_DTE_KBOOT_PREFIX=scs_dte_kboot
SCS_DTE_KBOOT_BIN=$(SCS_DTE_KBOOT_PREFIX).bin
SCS_DTE_KBOOT_BIN_PAD=$(OUTPUT_DIR)/$(SCS_DTE_KBOOT_PREFIX).bin.pad
SCS_DTE_KBOOT_TDB=$(OUTPUT_DIR)/$(SCS_DTE_KBOOT_PREFIX).tdb
SCS_DTE_KBOOT_PADDING=$(OUTPUT_DIR)/.$(SCS_DTE_KBOOT_PREFIX).pad
SCS_DTE_KBOOT_HASH=$(OUTPUT_DIR)/.$(SCS_DTE_KBOOT_PREFIX).hash
SCS_DTE_KBOOT_EM=$(OUTPUT_DIR)/$(SCS_DTE_KBOOT_PREFIX).em
SCS_DTE_KBOOT_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_DTE_KBOOT_PREFIX)_sig.raw
SCS_DTE_KBOOT_SIG_BIN=$(OUTPUT_DIR)/$(SCS_DTE_KBOOT_PREFIX)_sig.bin

OTP_CONFIG=$(OUTPUT_DIR)/OTP.config
OTP_BITMAP=$(OUTPUT_DIR)/otp_map.bin
OTP_PROGAMMER_DIR=$(PRJ_DIR)/tools/otp_programmer

##############################################################################
#
# Function
#
##############################################################################

# rsa-sign (
#	input_binary,
#	output_padding,
#	output_digest,
#	output_encode_msg,
#	input_rsa_key_file,
#	output_signature
# )
#
#rsa-sign =                                                             \
#     	$(SHA_EXE) $(1) $(2) $(3);                                     \
#	cat $(PKCS_PADDING) $(3) > $(4);                               \
#	openssl rsautl -sign -raw -in $(4) -inkey $(5) -out $(6);
#	#$(RTSSL_EXE) enc -e -rsa -i $(4) -k $(5) -o $(6);

# sign_trusted_data_blk (
#	in_rsa_key,		-> $(1)
#	in_trusted_data_blk,	-> $(2)
#	out_padding,		-> $(3)
#	out_hash,		-> $(4)
#	out_encoding_msg,	-> $(5)
#	out_signature_raw,	-> $(6)
#	out_signature_reversed	-> $(7)
# )
#
# intermediate file:
#	.signature.rev
#
sign_trusted_data_blk = 						\
	$(SHA_EXE) $(2) $(3) $(4);					\
	cat $(PKCS_PADDING) $(4) > $(5);				\
	openssl rsautl -sign -raw -in $(5) -inkey $(1) -out $(6);	\
	$(REVERSE) $(6) > $(7);					

pad_data_blk = 						\
	$(SHA_EXE) $(2) $(3) $(4);					\
	cat $(PKCS_PADDING) $(4) > $(5);				\
	dd if=/dev/urandom of=$(6) bs=256 count=1;	\
	$(REVERSE) $(6) > $(7);	

##############################################################################
#
# Rules
#
##############################################################################
.PHONEY: all clean key_rights controlling_data cert param aux_code dte_bootcode dte_kboot prepare_img build_param_inc


all: clean checkfile prepare_img key_rights controlling_data otp cert param aux_code dte_bootcode dte_kboot

checkfile:
ifeq ($(IMAGE_ENCRYPT), TRUE)
	@test -f $(RSA_ROOT_KEY) || { echo "RSA_ROOT_KEY $(RSA_ROOT_KEY) does not exist! Exiting..."; exit 1; }
	@test -f $(RSA_EXT_KEY) || { echo "RSA_EXT_KEY $(RSA_EXT_KEY) does not exist! Exiting..."; exit 1; }
	@test -f $(AES_EXT_FPK_KEY) || { echo "AES_EXT_FPK_KEY $(AES_EXT_FPK_KEY) does not exist! Exiting..."; exit 1; }
	@test -f $(AES_ROOT_K_KEY) || { echo "AES_ROOT_K_KEY $(AES_ROOT_K_KEY) does not exist! Exiting..."; exit 1; }
	@test -f $(AES_ROOT_S_KEY) || { echo "AES_ROOT_S_KEY $(AES_ROOT_S_KEY) does not exist! Exiting..."; exit 1; }
	@test -f $(AES_ROOT_AUX_KEY) || { echo "AES_ROOT_AUX_KEY $(AES_ROOT_AUX_KEY) does not exist! Exiting..."; exit 1; }	
endif
	
	
prepare_img:
ifneq ($(origin PRJ), undefined)
ifneq ($(origin Config_Aux_Code_Image_File), undefined)
	@# image from inc file
	cp $(PRJ_IMG_DIR)/$(Config_Aux_Code_Image_File) $(SCS_AUX_CODE_BIN)
endif
ifneq ($(origin Config_DTE_Bootcode_Image_File), undefined)
	@# image from inc file
	cp $(PRJ_IMG_DIR)/$(Config_DTE_Bootcode_Image_File) $(SCS_DTE_BOOTCODE_BIN)
endif
ifneq ($(origin Config_DTE_KBoot_Image_File), undefined)
	@# image from inc file
	cp $(PRJ_IMG_DIR)/$(Config_DTE_KBoot_Image_File) $(SCS_DTE_KBOOT_BIN)
endif
endif

key_rights: $(KEY_RIGHTS_INC)
	$(HEADER_GENERATOR) $(KEY_RIGHTS_INC) $(KEY_RIGHTS_BIN)


controlling_data:$(CONTROLLING_DATA_INC)
	$(HEADER_GENERATOR) $(CONTROLLING_DATA_INC) $(CONTROLLING_DATA_BIN)

otp:	
ifeq ($(IMAGE_ENCRYPT), TRUE)
	@# geenerate root key binary & R2
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_ROOT_KEY)` > $(RSA_ROOT_KEY_RAW)
	@# reverse binary (LSB first)
	$(REVERSE) $(RSA_ROOT_KEY_RAW) > $(RSA_ROOT_KEY_BIN)

	$(R2MODM_EXE) $(RSA_ROOT_KEY_RAW) $(RSA_ROOT_KEY_R2_BIN) > /dev/null 2>&1
	@# reverse binary (MSB first)
	$(REVERSE) $(RSA_ROOT_KEY_R2_BIN) > $(RSA_ROOT_KEY_R2_BIN).rev		

	@# reverse key
	$(REVERSE) $(AES_ROOT_K_KEY) > $(TMP_FILE)
	hexdump -e '4/4 "%08X"' $(TMP_FILE) | xxd -r -p > $(AES_ROOT_K_KEY_ROM)

	@# generate otp bitmap config
	@# all string format is LSB first
	echo CONFIG_RSA_PUBLIC_KEY=\"`$(RTSSL_EXE) rsa -print -modulous -i $(RSA_ROOT_KEY)`\" > $(OTP_CONFIG)
	echo CONFIG_HDCP_KEY=\"`hexdump -e '256/1 "%02X"' $(RSA_ROOT_KEY_R2_BIN).rev`\" >> $(OTP_CONFIG)
	echo CONFIG_KCPU_CP_AES_KEY=\"`hexdump -e '16/1 "%02X"' $(AES_ROOT_K_KEY)`\" >> $(OTP_CONFIG)
	echo CONFIG_SCPU_CP_AES_KEY=\"`hexdump -e '16/1 "%02X"' $(AES_ROOT_S_KEY)`\" >> $(OTP_CONFIG)
	echo CONFIG_NAGRA_AUX_PROTECTION_KEY=\"`hexdump -e '16/1 "%02X"' $(AES_ROOT_AUX_KEY)`\" >> $(OTP_CONFIG)
	echo CONFIG_SECURE_BOOT_EN=1 >> $(OTP_CONFIG)
	echo CONFIG_SECURE_BOOT_TYPE=2 >> $(OTP_CONFIG)
	
	@# generate otp bitmap
	$(OTP_BITMAP_GEN_EXE) generate $(OTP_CONFIG) $(OTP_BITMAP) > /dev/null 2>&1
	
	cp -f $(OTP_BITMAP) $(OTP_PROGAMMER_DIR)
endif
	
cert: $(SCS_NOCS_CERT_PARAM_INC) key_rights controlling_data
	@# convert public key modulus string into binary
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_EXT_KEY)` > $(SCS_NOCS_CERT_KEY_RAW)
else
	dd if=/dev/urandom of=$(SCS_NOCS_CERT_KEY_RAW) bs=256 count=1
endif
	@# reverse binary (LSB first)
	$(REVERSE) $(SCS_NOCS_CERT_KEY_RAW) > $(SCS_NOCS_CERT_KEY_BIN)
	@# build data parameter binary
	$(HEADER_GENERATOR) $(SCS_NOCS_CERT_PARAM_INC) $(SCS_NOCS_CERT_PARAM_BIN)
	@# generate ext key R2
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(R2MODM_EXE) $(SCS_NOCS_CERT_KEY_RAW) $(SCS_NOCS_CERT_KEY_R2_BIN) > /dev/null 2>&1
else
	dd if=/dev/urandom of=$(SCS_NOCS_CERT_KEY_R2_BIN) bs=256 count=1
endif
	@# combine data	
	cat $(SCS_NOCS_CERT_KEY_BIN) $(KEY_RIGHTS_BIN) $(SCS_NOCS_CERT_PARAM_BIN) $(SCS_NOCS_CERT_KEY_R2_BIN) > $(SCS_NOCS_CERT_PARAM_DATA)
	@# generate padding data
	dd if=/dev/zero ibs=1 count=752 | tr "\000" "\377" > $(SCS_NOCS_CERT_PARAM_BIN_PAD)
	@# insert binary to the beginning of the file
	dd if=$(SCS_NOCS_CERT_PARAM_DATA) of=$(SCS_NOCS_CERT_PARAM_BIN_PAD) conv=notrunc		
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_NOCS_CERT_PARAM_BIN_PAD) $(CONTROLLING_DATA_BIN) > $(SCS_NOCS_CERT_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(call sign_trusted_data_blk, $(RSA_ROOT_KEY), $(SCS_NOCS_CERT_TDB), $(SCS_NOCS_CERT_PADDING), $(SCS_NOCS_CERT_HASH), $(SCS_NOCS_CERTITICATE_EM), $(SCS_NOCS_CERT_SIG_RAW), $(SCS_NOCS_CERT_SIG_BIN))
	cp -f $(SCS_NOCS_CERT_SIG_BIN) $(SCS_NOCS_CERTITICATE_EM)
else
	$(call pad_data_blk,$(RSA_ROOT_KEY),$(SCS_NOCS_CERT_TDB),$(SCS_NOCS_CERT_PADDING),$(SCS_NOCS_CERT_HASH),$(SCS_NOCS_CERTITICATE_EM),$(SCS_NOCS_CERT_SIG_RAW),$(SCS_NOCS_CERT_SIG_BIN))
endif

build_param_inc: $(SCS_PARAMS_AREA_PARAM_INC_PART1) aux_code dte_bootcode dte_kboot $(SCS_PARAMS_AREA_PARAM_INC_PART2)
	@# get bootcode size
	$(PRINT_FILE_SIZE) $(SCS_DTE_BOOTCODE_BIN_PAD) > $(OUTPUT_DIR)/.temp_size
	cat $(SCS_PARAMS_AREA_BOOT_SPECIFIC_TEMPLATE) $(OUTPUT_DIR)/.temp_size > $(SCS_PARAMS_AREA_BOOT_SPECIFIC_INC)
	@# get kboot size or 0x0
ifeq ($(GENERATE_KBOOT_SIZE), TRUE)
	$(PRINT_FILE_SIZE) $(SCS_DTE_KBOOT_BIN_PAD) > $(OUTPUT_DIR)/.temp_size_kboot
else
	echo "0x0" > $(OUTPUT_DIR)/.temp_size_kboot
endif
	cat $(SCS_PARAMS_AREA_ADDRESS_OF_AUXILIARY_CODE_AREA_TEMPLATE) $(OUTPUT_DIR)/.temp_size_kboot > $(SCS_PARAMS_AREA_ADDRESS_OF_AUXILIARY_CODE_AREA_INC)
	@# generate aux code size
	$(GEN_AUX_CODE_AREA_SIZE) $(SCS_AUX_CODE_BIN_PAD) > $(SCS_PARAMS_AREA_AUX_AREA_SIZE_INC)
	@# cat all parts into single param inc file
	cat $(SCS_PARAMS_AREA_PARAM_INC_PART0) $(SCS_PARAMS_AREA_BOOT_SPECIFIC_INC) $(SCS_PARAMS_AREA_PARAM_INC_PART1) $(SCS_PARAMS_AREA_ADDRESS_OF_AUXILIARY_CODE_AREA_INC) $(SCS_PARAMS_AREA_AUX_AREA_SIZE_INC) $(SCS_PARAMS_AREA_PARAM_INC_PART2) > $(SCS_PARAMS_AREA_PARAM_INC)

param: build_param_inc $(SCS_PARAMS_AREA_PARAM_INC) $(FLASH_PROTECTION_KEY_INC) key_rights controlling_data
	@# generate param binary
	$(HEADER_GENERATOR) $(SCS_PARAMS_AREA_PARAM_INC) $(SCS_PARAMS_AREA_PARAM_BIN_TMP)
	@# insert hwsetting binary to param
	cat $(SCS_PARAMS_AREA_PARAM_BIN_TMP) $(SCS_PARAMS_AREA_PARAM_HWSETTING_BIN) > $(SCS_PARAMS_AREA_PARAM_BIN)
	@# generate flash protection key binary
#	$(HEADER_GENERATOR) $(FLASH_PROTECTION_KEY_INC) $(FLASH_PROTECTION_KEY_BIN)
ifeq ($(IMAGE_ENCRYPT), TRUE)
	hexdump -e '4/4 "%08x"' $(AES_EXT_FPK_KEY) | xxd -r -p > $(FLASH_PROTECTION_KEY_BIN)
else
	dd if=/dev/urandom of=$(FLASH_PROTECTION_KEY_BIN) bs=16 count=1
endif
	@# generate padding data
	dd if=/dev/zero ibs=1 count=3804 | tr "\000" "\377" > $(SCS_PARAMS_AREA_PARAM_BIN_PAD)
	@# insert binary to the beginning of the file
	dd if=$(SCS_PARAMS_AREA_PARAM_BIN) of=$(SCS_PARAMS_AREA_PARAM_BIN_PAD) conv=notrunc	
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(KEY_RIGHTS_BIN) $(SCS_PARAMS_AREA_PARAM_BIN_PAD) $(CONTROLLING_DATA_BIN) $(FLASH_PROTECTION_KEY_BIN) > $(SCS_PARAMS_AREA_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_PARAMS_AREA_TDB), $(SCS_PARAMS_AREA_PADDING), $(SCS_PARAMS_AREA_HASH), $(SCS_PARAMS_AREA_EM), $(SCS_PARAMS_AREA_SIG_RAW), $(SCS_PARAMS_AREA_SIG_BIN))
	cp -f $(SCS_PARAMS_AREA_SIG_BIN) $(SCS_PARAMS_AREA_EM)
else
	$(call pad_data_blk,$(RSA_EXT_KEY),$(SCS_PARAMS_AREA_TDB),$(SCS_PARAMS_AREA_PADDING),$(SCS_PARAMS_AREA_HASH),$(SCS_PARAMS_AREA_EM),$(SCS_PARAMS_AREA_SIG_RAW),$(SCS_PARAMS_AREA_SIG_BIN))
endif
	@# generate encrypted image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(RTSSL2_EXE) enc -e -aes_128_ecb -k `hexdump -e '16/1 "%02x"' $(AES_ROOT_K_KEY_ROM)` -i $(FLASH_PROTECTION_KEY_BIN) -o $(FLASH_PROTECTION_KEY_BIN).aes
	cat $(KEY_RIGHTS_BIN) $(SCS_PARAMS_AREA_PARAM_BIN_PAD) $(CONTROLLING_DATA_BIN) $(FLASH_PROTECTION_KEY_BIN).aes > $(SCS_PARAMS_AREA_TDB)
	rm -f $(FLASH_PROTECTION_KEY_BIN).aes
endif
	
aux_code: $(SCS_AUX_CODE_BIN) key_rights controlling_data
	@# generate padding data
	dd if=/dev/zero ibs=1 count=28396 | tr "\000" "\377" > $(SCS_AUX_CODE_BIN_PAD)
	@# insert binary to the beginning of the file
	dd if=$(SCS_AUX_CODE_BIN) of=$(SCS_AUX_CODE_BIN_PAD) conv=notrunc
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_AUX_CODE_BIN_PAD) $(KEY_RIGHTS_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_AUX_CODE_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_AUX_CODE_TDB), $(SCS_AUX_CODE_PADDING), $(SCS_AUX_CODE_HASH), $(SCS_AUX_CODE_EM), $(SCS_AUX_CODE_SIG_RAW), $(SCS_AUX_CODE_SIG_BIN))
	cp -f $(SCS_AUX_CODE_SIG_BIN) $(SCS_AUX_CODE_EM)
else
	$(call pad_data_blk,$(RSA_EXT_KEY),$(SCS_AUX_CODE_TDB),$(SCS_AUX_CODE_PADDING),$(SCS_AUX_CODE_HASH),$(SCS_AUX_CODE_EM),$(SCS_AUX_CODE_SIG_RAW),$(SCS_AUX_CODE_SIG_BIN))
endif
	@# generate encrypted image	
ifeq ($(IMAGE_ENCRYPT), TRUE)
	cat $(SCS_AUX_CODE_BIN_PAD) $(KEY_RIGHTS_BIN) > $(SCS_AUX_CODE_TDB).tmp
	$(RTSSL2_EXE) enc -e -aes_128_ecb -k `hexdump -e '16/1 "%02x"' $(AES_ROOT_AUX_KEY)` -i $(SCS_AUX_CODE_TDB).tmp -o $(SCS_AUX_CODE_TDB).aes
	cat $(SCS_AUX_CODE_TDB).aes $(CONTROLLING_DATA_BIN) > $(SCS_AUX_CODE_TDB)
	rm -f $(SCS_AUX_CODE_TDB).tmp $(SCS_AUX_CODE_TDB).aes
endif

dte_bootcode: $(SCS_DTE_BOOTCODE_BIN) key_rights controlling_data
	@# generate padding data
	dd if=/dev/zero ibs=1 count=486124 | tr "\000" "\377" > $(SCS_DTE_BOOTCODE_BIN_PAD)
	@# insert binary to the beginning of the file
	dd if=$(SCS_DTE_BOOTCODE_BIN) of=$(SCS_DTE_BOOTCODE_BIN_PAD) conv=notrunc
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_DTE_BOOTCODE_BIN_PAD) $(KEY_RIGHTS_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_DTE_BOOTCODE_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_DTE_BOOTCODE_TDB), $(SCS_DTE_BOOTCODE_PADDING), $(SCS_DTE_BOOTCODE_HASH), $(SCS_DTE_BOOTCODE_EM), $(SCS_DTE_BOOTCODE_SIG_RAW), $(SCS_DTE_BOOTCODE_SIG_BIN))
	@# generate encrypted image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	cat $(SCS_DTE_BOOTCODE_BIN_PAD) $(KEY_RIGHTS_BIN) > $(SCS_DTE_BOOTCODE_TDB).tmp
	$(RTSSL2_EXE) enc -e -aes_128_cbc -k `hexdump -e '16/1 "%02x"' $(AES_EXT_FPK_KEY)` -i $(SCS_DTE_BOOTCODE_TDB).tmp -o $(SCS_DTE_BOOTCODE_TDB).aes
	cat $(SCS_DTE_BOOTCODE_TDB).aes $(CONTROLLING_DATA_BIN) > $(SCS_DTE_BOOTCODE_TDB)
	rm -f $(SCS_DTE_BOOTCODE_TDB).tmp $(SCS_DTE_BOOTCODE_TDB).aes
endif

dte_kboot: $(SCS_DTE_KBOOT_BIN) key_rights controlling_data
	@# generate padding data
	dd if=/dev/zero ibs=1 count=486124 | tr "\000" "\377" > $(SCS_DTE_KBOOT_BIN_PAD)
	@# insert binary to the beginning of the file
	dd if=$(SCS_DTE_KBOOT_BIN) of=$(SCS_DTE_KBOOT_BIN_PAD) conv=notrunc
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_DTE_KBOOT_BIN_PAD) $(KEY_RIGHTS_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_DTE_KBOOT_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_DTE_KBOOT_TDB), $(SCS_DTE_KBOOT_PADDING), $(SCS_DTE_KBOOT_HASH), $(SCS_DTE_KBOOT_EM), $(SCS_DTE_KBOOT_SIG_RAW), $(SCS_DTE_KBOOT_SIG_BIN))
	@# generate encrypted image
ifeq ($(IMAGE_ENCRYPT), TRUE)
	cat $(SCS_DTE_KBOOT_BIN_PAD) $(KEY_RIGHTS_BIN) > $(SCS_DTE_KBOOT_TDB).tmp
	$(RTSSL2_EXE) enc -e -aes_128_cbc -k `hexdump -e '16/1 "%02x"' $(AES_EXT_FPK_KEY)` -i $(SCS_DTE_KBOOT_TDB).tmp -o $(SCS_DTE_KBOOT_TDB).aes
	cat $(SCS_DTE_KBOOT_TDB).aes $(CONTROLLING_DATA_BIN) > $(SCS_DTE_KBOOT_TDB)
	rm -f $(SCS_DTE_KBOOT_TDB).tmp $(SCS_DTE_KBOOT_TDB).aes
endif

clean:
	if [ -e $(OUTPUT_DIR) ]; then	\
		cd $(OUTPUT_DIR);	\
		rm -rf *;		\
	fi


