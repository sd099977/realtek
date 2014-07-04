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
REVERSE=perl ../flash_image_maker/reverse.pl
STR2BIN=perl ../script/str2bin.pl
HEADER_GENERATOR=perl ../script/header_generator.pl
GEN_AUX_CODE_AREA_SIZE= perl ../script/gen_aux_code_area_size.pl
PRINT_FILE_SIZE= perl ../script/print_file_size.pl

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
RSA_ROOT_KEY=$(PRJ_IMG_DIR)/$(Config_Secure_RSA_Root_Key_File)
RSA_EXT_KEY=$(PRJ_IMG_DIR)/$(Config_Secure_RSA_Ext_Key_File)
endif

PKCS_PADDING=pkcs_padding.dat

KEY_RIGHTS_PREFIX=key_rights
KEY_RIGHTS_INC=$(KEY_RIGHTS_PREFIX).inc
KEY_RIGHTS_BIN=$(OUTPUT_DIR)/.$(KEY_RIGHTS_PREFIX).bin

CONTROLLING_DATA_PREFIX=controlling_data
CONTROLLING_DATA_INC=$(CONTROLLING_DATA_PREFIX).inc
CONTROLLING_DATA_BIN=$(OUTPUT_DIR)/.$(CONTROLLING_DATA_PREFIX).bin

FLASH_PROTECTION_KEY_PREFIX=flash_protection_key
FLASH_PROTECTION_KEY_INC=flash_protection_key.inc
FLASH_PROTECTION_KEY_BIN=$(OUTPUT_DIR)/.flash_protection_key.bin

SCS_NOCS_CERT_PREFIX=scs_nocs_certificate
SCS_NOCS_CERT_KEY_RAW=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_key.raw
SCS_NOCS_CERT_KEY_BIN=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_key.bin
SCS_NOCS_CERT_PARAM_INC=$(SCS_NOCS_CERT_PREFIX)_param.inc
SCS_NOCS_CERT_PARAM_BIN=$(OUTPUT_DIR)/.$(SCS_NOCS_CERT_PREFIX)_param.bin
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

SCS_AUX_CODE_PREFIX=scs_aux_code
SCS_AUX_CODE_BIN=$(SCS_AUX_CODE_PREFIX).bin
SCS_AUX_CODE_INC=$(SCS_AUX_CODE_PREFIX).inc
#SCS_AUX_CODE_PARAM_INC=$(SCS_AUX_CODE_PREFIX)_param.inc
#SCS_AUX_CODE_PARAM_BIN=$(SCS_AUX_CODE_PREFIX)_param.bin
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
SCS_DTE_BOOTCODE_TDB=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).tdb
SCS_DTE_BOOTCODE_PADDING=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX).pad
SCS_DTE_BOOTCODE_HASH=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX).hash
SCS_DTE_BOOTCODE_EM=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).em
SCS_DTE_BOOTCODE_SIG_RAW=$(OUTPUT_DIR)/.$(SCS_DTE_BOOTCODE_PREFIX)_sig.raw
SCS_DTE_BOOTCODE_SIG_BIN=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX)_sig.bin
#SCS_DTE_BOOTCODE_IMG=$(OUTPUT_DIR)/$(SCS_DTE_BOOTCODE_PREFIX).img

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


##############################################################################
#
# Rules
#
##############################################################################
.PHONEY: all clean key_rights controlling_data cert param aux_code dte_bootcode prepare_img build_param_inc


all: prepare_img key_rights controlling_data cert param aux_code dte_bootcode

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
endif

key_rights: $(KEY_RIGHTS_INC)
	$(HEADER_GENERATOR) $(KEY_RIGHTS_INC) $(KEY_RIGHTS_BIN)


controlling_data:$(CONTROLLING_DATA_INC)
	$(HEADER_GENERATOR) $(CONTROLLING_DATA_INC) $(CONTROLLING_DATA_BIN)


cert: $(SCS_NOCS_CERT_PARAM_INC) key_rights controlling_data
	@# convert public key modulus string into binary
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_EXT_KEY)` > $(SCS_NOCS_CERT_KEY_RAW)
	@# reverse binary (LSB first)
	$(REVERSE) $(SCS_NOCS_CERT_KEY_RAW) > $(SCS_NOCS_CERT_KEY_BIN)
	@# build data parameter binary
	$(HEADER_GENERATOR) $(SCS_NOCS_CERT_PARAM_INC) $(SCS_NOCS_CERT_PARAM_BIN)
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_NOCS_CERT_KEY_BIN) $(KEY_RIGHTS_BIN) $(SCS_NOCS_CERT_PARAM_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_NOCS_CERT_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_ROOT_KEY), $(SCS_NOCS_CERT_TDB), $(SCS_NOCS_CERT_PADDING), $(SCS_NOCS_CERT_HASH), $(SCS_NOCS_CERTITICATE_EM), $(SCS_NOCS_CERT_SIG_RAW), $(SCS_NOCS_CERT_SIG_BIN))

build_param_inc: $(SCS_PARAMS_AREA_PARAM_INC_PART1) $(SCS_AUX_CODE_BIN) $(SCS_PARAMS_AREA_PARAM_INC_PART2)
	@# get bootcode size
	$(PRINT_FILE_SIZE) $(SCS_DTE_BOOTCODE_BIN) > $(OUTPUT_DIR)/.temp_size
	cat $(SCS_PARAMS_AREA_BOOT_SPECIFIC_TEMPLATE) $(OUTPUT_DIR)/.temp_size > $(SCS_PARAMS_AREA_BOOT_SPECIFIC_INC)
	@# generate aux code size
	$(GEN_AUX_CODE_AREA_SIZE) $(SCS_AUX_CODE_BIN) > $(SCS_PARAMS_AREA_AUX_AREA_SIZE_INC)
	@# cat all parts into single param inc file
	cat $(SCS_PARAMS_AREA_PARAM_INC_PART0) $(SCS_PARAMS_AREA_BOOT_SPECIFIC_INC) $(SCS_PARAMS_AREA_PARAM_INC_PART1) $(SCS_PARAMS_AREA_AUX_AREA_SIZE_INC) $(SCS_PARAMS_AREA_PARAM_INC_PART2) > $(SCS_PARAMS_AREA_PARAM_INC)

param: build_param_inc $(SCS_PARAMS_AREA_PARAM_INC) $(FLASH_PROTECTION_KEY_INC) key_rights controlling_data
	@# generate param binary
	$(HEADER_GENERATOR) $(SCS_PARAMS_AREA_PARAM_INC) $(SCS_PARAMS_AREA_PARAM_BIN)
	@# generate flash protection key binary
	$(HEADER_GENERATOR) $(FLASH_PROTECTION_KEY_INC) $(FLASH_PROTECTION_KEY_BIN)
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(KEY_RIGHTS_BIN) $(SCS_PARAMS_AREA_PARAM_BIN) $(CONTROLLING_DATA_BIN) $(FLASH_PROTECTION_KEY_BIN) > $(SCS_PARAMS_AREA_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_PARAMS_AREA_TDB), $(SCS_PARAMS_AREA_PADDING), $(SCS_PARAMS_AREA_HASH), $(SCS_PARAMS_AREA_EM), $(SCS_PARAMS_AREA_SIG_RAW), $(SCS_PARAMS_AREA_SIG_BIN))


aux_code: $(SCS_AUX_CODE_BIN) key_rights controlling_data
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_AUX_CODE_BIN) $(KEY_RIGHTS_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_AUX_CODE_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_AUX_CODE_TDB), $(SCS_AUX_CODE_PADDING), $(SCS_AUX_CODE_HASH), $(SCS_AUX_CODE_EM), $(SCS_AUX_CODE_SIG_RAW), $(SCS_AUX_CODE_SIG_BIN))


dte_bootcode: $(SCS_DTE_BOOTCODE_BIN) key_rights controlling_data
	@# combine all required binaries into NOCS_Trusted_Area
	cat $(SCS_DTE_BOOTCODE_BIN) $(KEY_RIGHTS_BIN) $(CONTROLLING_DATA_BIN) > $(SCS_DTE_BOOTCODE_TDB)
	@# generate hash, sign with RSA key, reverse signature, and generate final image
	$(call sign_trusted_data_blk, $(RSA_EXT_KEY), $(SCS_DTE_BOOTCODE_TDB), $(SCS_DTE_BOOTCODE_PADDING), $(SCS_DTE_BOOTCODE_HASH), $(SCS_DTE_BOOTCODE_EM), $(SCS_DTE_BOOTCODE_SIG_RAW), $(SCS_DTE_BOOTCODE_SIG_BIN))


clean:
	if [ -e $(OUTPUT_DIR) ]; then	\
		cd $(OUTPUT_DIR);	\
		rm -rf *;		\
	fi


