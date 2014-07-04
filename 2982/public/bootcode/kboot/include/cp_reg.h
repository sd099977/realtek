/************************************************************************
 *
 *  cp_reg.h
 *
 *  Defines for Sirius CP registers
 *
 ************************************************************************/

#ifndef CP_REG_H
#define CP_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define CP_REG_BASE			0xb8015000

#define CP_OTP_LOAD			(CP_REG_BASE + 0x19c)

/* MCP General Registers */
#define K_MCP_CTRL			(CP_REG_BASE + 0x900)
#define K_MCP_STATUS			(CP_REG_BASE + 0x904)
#define K_MCP_EN				(CP_REG_BASE + 0x908)

/* MCP Ring-Buffer Registers */
#define K_MCP_BASE			(CP_REG_BASE + 0x90c)
#define K_MCP_LIMIT			(CP_REG_BASE + 0x910)
#define K_MCP_RDPTR			(CP_REG_BASE + 0x914)
#define K_MCP_WRPTR			(CP_REG_BASE + 0x918)
#define K_MCP_DES_COUNT		(CP_REG_BASE + 0x934)
#define K_MCP_DES_COMPARE	(CP_REG_BASE + 0x938)

/* MCP Ini_Key Registers */
#define K_MCP_DES_INI_KEY	(CP_REG_BASE + 0x91c)
#define K_MCP_AES_INI_KEY	(CP_REG_BASE + 0x924)

/* MCP General Registers */
#define MCP_CTRL				(CP_REG_BASE + 0x100)
#define MCP_STATUS			(CP_REG_BASE + 0x104)
#define MCP_EN					(CP_REG_BASE + 0x108)

/* MCP Ring-Buffer Registers */
#define MCP_BASE				(CP_REG_BASE + 0x10c)
#define MCP_LIMIT				(CP_REG_BASE + 0x110)
#define MCP_RDPTR				(CP_REG_BASE + 0x114)
#define MCP_WRPTR				(CP_REG_BASE + 0x118)
#define MCP_DES_COUNT		(CP_REG_BASE + 0x134)
#define MCP_DES_COMPARE		(CP_REG_BASE + 0x138)

/* MCP Ini_Key Registers */
#define MCP_DES_INI_KEY		(CP_REG_BASE + 0x11c)
#define MCP_AES_INI_KEY		(CP_REG_BASE + 0x124)

/* SRAM BISR/BISR control */
#define MCP_CP_MBISR_STATUS	(CP_REG_BASE + 0x1f0)
#define MCP_CP_MBISR_DRF_STATUS	(CP_REG_BASE + 0x1f4)

/* CP Power Management */
#define MCP_PWM_CTRL		(CP_REG_BASE + 0x1e0)
#define MCP_CP_CLK_CTRL		(CP_REG_BASE + 0x0e4)
#define MCP_CP_SRAM_PWR		(CP_REG_BASE + 0x1f8)

/* 42K SCS SRAM Register */
#define MCP_RW_42K				(CP_REG_BASE + 0x1fc)

/* RCP Register */
#define RCP_REG_KEY			(CP_REG_BASE + 0x34)
#define RCP_REG_DATAIN		(CP_REG_BASE + 0x44)
#define RCP_REG_DATAOUT		(CP_REG_BASE + 0x54)
#define RCP_REG_IV			(CP_REG_BASE + 0x64)
#define RCP_REG_SET			(CP_REG_BASE + 0x74)
#define RCP_REG_SET1			(CP_REG_BASE + 0x78)
#define RCP_REG_SET2			(CP_REG_BASE + 0x7c)

/*  CW Register in TP */
#define CW_TP_REG_INFO 		(0xb8014058)
#define CW_TP_REG_CTRL 		(0xb8014060)

/*  CP NF Register */
#define CP_NF_KEY				(CP_REG_BASE + 0x84)
#define CP_NF_INIT_KEY		(CP_REG_BASE + 0x94)
#define CP_NF_SET				(CP_REG_BASE + 0xa4)

/*  CP MD Register */
#define CP_MD_KEY				(CP_REG_BASE + 0xa8)
#define CP_MD_INIT_KEY     (CP_REG_BASE + 0xb8)
#define CP_MD_SET				(CP_REG_BASE + 0xc8)

/* Nagra Key write agent register */
#define CP_CW_AGENT		(CP_REG_BASE + 0xe0)

/* KCPU's RCP Register */
#define K_RCP_REG_KEY			(CP_REG_BASE + 0x834)
#define K_RCP_REG_DATAIN		(CP_REG_BASE + 0x844)
#define K_RCP_REG_DATAOUT		(CP_REG_BASE + 0x854)
#define K_RCP_REG_IV			(CP_REG_BASE + 0x864)
#define K_RCP_REG_SET			(CP_REG_BASE + 0x874)
#define K_RCP_REG_SET1			(CP_REG_BASE + 0x878)
#define K_RCP_REG_SET2			(CP_REG_BASE + 0x87c)


#define BIT(x)               (1 <<x)
#define REG_SET_WR_EN5      BIT(17)
#define REG_SET_MODE(x)     ((x & 0x7)<<13)
#define REG_SET_MODE_AES    REG_SET_MODE(0)
#define REG_SET_MODE_TDES   REG_SET_MODE(1)
#define REG_SET_MODE_DES    REG_SET_MODE(2)
#define REG_SET_MODE_SHA256    REG_SET_MODE(3)
#define REG_SET_MODE_MASK   REG_SET_MODE(7)
#define REG_SET_WR_EN4     BIT(11)
#define REG_SET_ENDIAN_BIG       (REG_SET_WR_EN4 | 0)
#define REG_SET_ENDIAN_LITTLE  (REG_SET_WR_EN4 | BIT(10))

#define REG_SET_WR_EN2      BIT(6)
#define REG_SET_CBC         BIT(4)
#define REG_SET_ECB         0x0
#define REG_SET_WR_EN1      BIT(3)
#define REG_SET_FIRST_128   BIT(2)
#define REG_SET_WR_EN0      BIT(1)
#define REG_SET_ENC         BIT(0)
#define REG_SET_DEC         0x0

#define RCP_AES_128_ECB_ENC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_ECB_DEC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)
#define RCP_AES_128_CBC_ENC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_CBC_DEC      (REG_SET_WR_EN5 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)
#define RCP_SHA256                        (REG_SET_WR_EN5 | REG_SET_MODE_SHA256 | REG_SET_WR_EN0 | REG_SET_ENC)

#define REG_SET1_KEY_MODE(x)         ((x & 0x3)<<6)
#define REG_SET1_KEY_MODE_REGISTER   REG_SET1_KEY_MODE(0)
#define REG_SET1_KEY_MODE_CW         REG_SET1_KEY_MODE(1)
#define REG_SET1_KEY_MODE_OTP        REG_SET1_KEY_MODE(2)
#define REG_SET1_KEY_MODE_MASK       REG_SET1_KEY_MODE(3)

#define REG_SET1_IV_MODE(x)          ((x & 0x3)<<4)
#define REG_SET1_IV_MODE_REG         REG_SET1_IV_MODE(0)
#define REG_SET1_IV_MODE_CW          REG_SET1_IV_MODE(1)

#define REG_SET1_INPUT_MODE(x)       ((x & 0x3)<<2)
#define REG_SET1_INPUT_MODE_REG      REG_SET1_INPUT_MODE(0)
#define REG_SET1_INPUT_MODE_CW       REG_SET1_INPUT_MODE(1)

#define REG_SET1_OUTPUT_MODE(x)      ((x & 0x3))
#define REG_SET1_OUTPUT_MODE_REG     REG_SET1_OUTPUT_MODE(0)
#define REG_SET1_OUTPUT_MODE_CW      REG_SET1_OUTPUT_MODE(1)

#define REG_SET2_OUTPUT_ENTRY(x)     ((x & 0x7F)<<24)
#define REG_SET2_INPUT_ENTRY(x)      ((x & 0x7F)<<16)
#define REG_SET2_KEY_ENTRY(x)        ((x & 0x7F)<<8)
#define REG_SET2_IV_ENTRY(x)         ((x & 0x7F))

/* MCP descriptor define */
#define MCP_KEY_SEL(x)               ((x & 0x3) << 12)
#define MCP_KEY_FROM_DSCPT           MCP_KEY_SEL(0)
#define MCP_KEY_FROM_OTP             MCP_KEY_SEL(1)
#define MCP_KEY_FROM_CW              MCP_KEY_SEL(2)
#define MCP_KEY_FROM_DDR             MCP_KEY_SEL(3)


#define MCP_BCM_SEL(x)               ((x & 0xf) << 6)
#define MCP_BCM_ECB                  MCP_BCM_SEL(0)
#define MCP_BCM_CBC                  MCP_BCM_SEL(1)
#define MCP_BCM_CTR                  MCP_BCM_SEL(2)
#define MCP_BCM_RCBC_CS              MCP_BCM_SEL(3)

#define MCP_ENCRYPT                  BIT(5)
#define MCP_DECRYPT                  0x0

#define MCP_MODE_SEL(x)              (x & 0x1f)
#define MCP_MODE_DES                 MCP_MODE_SEL(0x0)
#define MCP_MODE_3DES                MCP_MODE_SEL(0x1)
#define MCP_MODE_MD5                 MCP_MODE_SEL(0x3)
#define MCP_MODE_SHA1                MCP_MODE_SEL(0x4)
#define MCP_MODE_AES                 MCP_MODE_SEL(0x5)
#define MCP_MODE_AES_G               MCP_MODE_SEL(0x6)
#define MCP_MODE_AES_H               MCP_MODE_SEL(0x7)
#define MCP_MODE_CMAC                MCP_MODE_SEL(0x8)
#define MCP_MODE_CSA                 MCP_MODE_SEL(0x9)
#define MCP_MODE_MULTI2              MCP_MODE_SEL(0xa)
#define MCP_MODE_SHA256              MCP_MODE_SEL(0xb)

#endif /* #ifndef CP_REG_H */
