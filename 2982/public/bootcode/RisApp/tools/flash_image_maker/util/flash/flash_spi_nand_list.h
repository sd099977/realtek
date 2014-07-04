#ifndef __FLASH_SPI_NAND_LIST_H__
#define __FLASH_SPI_NAND_LIST_H__


#define GD5F1GQ4UAYIG 0xc8f1c8f1
#define GD5F2GQ4UAYIG 0xc8f2c8f2
#define MT29F1G01AAADD 0x2c122c12


/* ECC bit select (per 512 bytes) */
//#define SPI_N_ECC_6BIT		0x0
//#define SPI_N_ECC_12BIT		0x1
//#define SPI_N_ECC_24BIT		0x2	//


/* Position of initial bad block mark */
#define INITIAL_BB_POS_FIRST	0x0	// in the first page of initial bad block
#define INITIAL_BB_POS_LAST	0xff	// in the last  page of initial bad block
#define INITIAL_BB_POS_BOTH	(INITIAL_BB_POS_FIRST | INITIAL_BB_POS_LAST)	// in both first and last page of initial bad block

typedef struct 
{
    unsigned int    id;
    unsigned short  PageSize;
    unsigned int    BlockSize;
    unsigned int    size;
    unsigned char   initial_bb_pos;	// position of initial bad block mark
    //unsigned char   ecc_bit;		// ECC bit number
    const char      *string;
} spi_n_device_type;

static const spi_n_device_type spi_n_device[] =
{
    {GD5F1GQ4UAYIG,        2048, 64*2048, 0x08000000, INITIAL_BB_POS_FIRST, "GD5F1GQ4UAYIG" } , 
    {GD5F2GQ4UAYIG,        2048, 64*2048, 0x10000000, INITIAL_BB_POS_FIRST, "GD5F2GQ4UAYIG" } , 
    {MT29F1G01AAADD,       2048, 64*2048, 0x10000000, INITIAL_BB_POS_FIRST, "MT29F1G01AAADD" } , 
} ; 


#define DEV_SIZE_SPI_N	(sizeof(spi_n_device)/sizeof(spi_n_device_type))

#endif /* __FLASH_SPI_NAND_LIST_H__ */
