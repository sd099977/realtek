# ********************************************************************
# Board Components
# ********************************************************************
# flag                      value
# ********************************************************************
##Chip Version [Ver_A | Ver_B]
Config_Chip_Version = Ver_B

##Package type [EMMC_TV176_LQFP | EMMC_TV_BGA_CA]
##             [NAND_TV176_LQFP | NAND_TV_BGA]
##             [SPI]
Config_Package_type = NAND_TV176_LQFP

# ********************************************************************
# Config
# ********************************************************************
# flag                      value
# ********************************************************************
Config_Aux_Code_HW_SETTING = QFP176_demo
Config_Aux_Code_Image_File = "Aux_code_realchip_b_hw_parser.img"

# ********************************************************************
# Config
# ********************************************************************
# flag                      value
# ********************************************************************
Config_DTE_Bootcode_Config_Value = rtd298x_tv003_memc_qfp176_ddr_512m_x16_v3_nand
Config_DTE_Bootcode_Board_name_Value = tv001
Config_DTE_Bootcode_SOC_Value = rtd298x
Config_DTE_Bootcode_Image_File = "dte_bootcode.img"

# ********************************************************************
# Config
# ********************************************************************
# flag                      value
# ********************************************************************
Config_Process_DTE_KBoot = FALSE
Config_DTE_KBoot_Image_File = "dte_kboot.img"

# ********************************************************************
# Rescue Linux attribute
# ********************************************************************
# flag                      value
# ********************************************************************
##Rescue_Switch =           [FLASH | USB | NULL]
Rescue_Source =             FLASH
#Rescue_File_Name =     vmlinux.rescue.rtd298x.bin
Rescue_File_Name =     vmlinux.rescue.rtd298x.bin.lzma

# ********************************************************************
# RSA key file & AES key file (under bin/image)
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_OTP_Secure_Boot =   [TRUE | FALSE]
Config_OTP_Secure_Boot =     FALSE
Config_Secure_RSA_Root_Key_File = "rsa_root_key.pem"
Config_Secure_RSA_Ext_Key_File = "rsa_ext_key.pem"
Config_Secure_AES_Root_K_Key_File = "key_root_k.bin"
Config_Secure_AES_Root_S_Key_File = "key_root_s.bin"
Config_Secure_AES_Root_AUX_Key_File = "key_root_aux.bin"
Config_Secure_AES_Ext_FPK_Key_File = "key_ext_fpk.bin"
Config_Secure_RSA_Key_File = "rsa_key_2048.pem"

# ********************************************************************
# Boot parameters
# ********************************************************************
# flag                      value
# ********************************************************************
##Param_companyID =         [value]
Param_companyID =           "0000"
##Param_boardID =           [value]
Param_boardID =             "0000"
##Param_version =           [value]
Param_version =             "0002"

# ********************************************************************
# user defined 
# ********************************************************************
# flag                      value
# ********************************************************************

