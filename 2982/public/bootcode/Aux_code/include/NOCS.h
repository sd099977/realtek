/************************************************************************
 *
 *  NOCS.h
 *
 *  Public header file for NOCS data structure
 *
 ************************************************************************/

#ifndef NOCS_H
#define NOCS_H

/************************************************************************
 *  Definition
 ************************************************************************/

typedef struct T_NOCS_CONTROLLING_DATA
{
	unsigned int Market_SegmentID_EXT;
	unsigned int Mask_MSID;
	unsigned int Versioning_EXT;
	unsigned int Mask_Vers;
} NOCS_Controlling_Data;

typedef struct T_NOCS_CERTIFICATE
{
	unsigned int External_Public_RSA_Key[64];	// 2048 bit
	unsigned int Key_Rights;
	unsigned int Size_Of_SCS_Params_Area;
	unsigned int Address_Of_SCS_Param_Area;
	unsigned int External_R2_Public_RSA_Key[64];	// 2048 bit
	NOCS_Controlling_Data Controlling_Data;
	unsigned int Signature[64];
} NOCS_Certificate;

typedef struct T_NOCS_PARAMS
{
	unsigned int Key_Rights_CheckID;
	unsigned int External_Flash_Device_Params;
	unsigned int External_RAM_Params;
	unsigned int External_Boot_Specific_Params;
	unsigned int STR_Default_Region_Min_Size;
	unsigned int Address_of_Aux_Code_Area;	// patched this field as the size of kboot
	unsigned int Size_of_Aux_Code_Area;
	unsigned int Address_of_Boot_Code_Area;
	unsigned int Total_Area_Size[4];
	unsigned int Total_Area_Size_Selection;
	NOCS_Controlling_Data Controlling_Data;
	unsigned int Flash_Protection_Key[4];
	unsigned int Signature[64];
} NOCS_Params;

typedef struct T_NOCS_AUX_CODE_TAIL
{
	unsigned int Key_Rights;
	NOCS_Controlling_Data Controlling_Data;
	unsigned int Signature[64];
} NOCS_Aux_Code_Tail, DTE_BOOTCODE_AREA_Tail, EXT_SEC_FW_Tail, DTE_KBOOT_AREA_Tail;

#define SCS_UNCHECK_AREA	4096

typedef struct T_SEC_FW_NOCS_CERTIFICATE
{
	unsigned int External_Public_RSA_Key[64];	// 2048 bit
	unsigned int Key_Rights;
	NOCS_Controlling_Data Controlling_Data;
	unsigned int Signature[64];
} SEC_FW_NOCS_Certificate;


/************************************************************************
 *  Public function prototypes
 ************************************************************************/

#endif /* #ifndef NOCS_H */

