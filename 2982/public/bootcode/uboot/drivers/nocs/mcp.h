#ifndef __MCP_H__
#define __MCP_H__

#define MCP_DEV_FILE_NAME       			"mcp/core"
#define MCP_DEVICE_NAME         			"mcp"
#define MCP_DESC_ENTRY_COUNT                64
//#define MCP_INTERRUPT_ENABLE

#define RTD299x_REG_BASE					(0xB8000000)

/* =============================================================================== */
/*  REGISTER MAP																   */
/* =============================================================================== */
#define RTD299x_MCP_CTRL             		(RTD299x_REG_BASE + 0x15100)
    #define MCP_GO                			(0x01<<1)
    #define MCP_IDEL              			(0x01<<2)
    #define MCP_SWAP              			(0x01<<3)
    #define MCP_CLEAR             			(0x01<<4)
	/* 0 : run-robin for all
	*  1 : run-robin for TP0/1 and put priotity as TP > MD > NF > MCP
	*/
    #define MCP_ARB_MODE(x)       			((x & 0x01)<<6)

#define RTD299x_MCP_STATUS          		(RTD299x_REG_BASE + 0x15104)
    #define MCP_WRITE_DATA        			(0x01 << 0)
    #define MCP_RING_EMPTY        			(0x01 <<1)
    #define MCP_ERROR             			(0x01 <<2)
    #define MCP_COMPARE           			(0x01 <<3)
    #define MCP_ACP_ERR           			(0x01 <<6)

#define RTD299x_MCP_EN               		(RTD299x_REG_BASE + 0x15108)
#define RTD299x_MCP_CTRL1        		(RTD299x_REG_BASE + 0x15198)
    #define MCP_AES_PAD_OFF(x)   			((x & 0x1) << 10)
    #define MCP_CSA_ENTROPY(x)    		((x & 0x3) << 8)
        #define ORIGIONAL_MODE    			(0x0)
        #define CSA_MODE_1        			(0x1)
        #define CSA_MODE_2        			(0x2)
    #define MCP_ROUND_NO(x)       			((x & 0xFF))

#define RTD299x_MCP_BASE             		(RTD299x_REG_BASE + 0x1510C)
#define RTD299x_MCP_LIMIT            	(RTD299x_REG_BASE + 0x15110)
#define RTD299x_MCP_RDPTR            	(RTD299x_REG_BASE + 0x15114)
#define RTD299x_MCP_WRPTR            	(RTD299x_REG_BASE + 0x15118)
#define RTD299x_MCP_DES_COUNT     		(RTD299x_REG_BASE + 0x15134)
#define RTD299x_MCP_DES_COMPARE   		(RTD299x_REG_BASE + 0x15138)
/* DES/TDES/MULTI2 Initial Vector */
#define RTD299x_MCP_DES_INI_KEY0   	(RTD299x_REG_BASE + 0x1511C)
#define RTD299x_MCP_DES_INI_KEY1   	(RTD299x_REG_BASE + 0x15120)
/* AES Initial Vector */
#define RTD299x_MCP_AES_INI_KEY0   	(RTD299x_REG_BASE + 0x15124)
#define RTD299x_MCP_AES_INI_KEY1   	(RTD299x_REG_BASE + 0x15128)
#define RTD299x_MCP_AES_INI_KEY2   	(RTD299x_REG_BASE + 0x1512C)
#define RTD299x_MCP_AES_INI_KEY3   	(RTD299x_REG_BASE + 0x15130)
/* Multi2 System Key */
#define RTD299x_MCP_MULTI2_SYS_KEY0	(RTD299x_REG_BASE + 0x15178)
#define RTD299x_MCP_MULTI2_SYS_KEY1	(RTD299x_REG_BASE + 0x1517C)
#define RTD299x_MCP_MULTI2_SYS_KEY2	(RTD299x_REG_BASE + 0x15180)
#define RTD299x_MCP_MULTI2_SYS_KEY3	(RTD299x_REG_BASE + 0x15184)
#define RTD299x_MCP_MULTI2_SYS_KEY4	(RTD299x_REG_BASE + 0x15188)
#define RTD299x_MCP_MULTI2_SYS_KEY5	(RTD299x_REG_BASE + 0x1518C)
#define RTD299x_MCP_MULTI2_SYS_KEY6	(RTD299x_REG_BASE + 0x15190)
#define RTD299x_MCP_MULTI2_SYS_KEY7	(RTD299x_REG_BASE + 0x15194)
#define RTD299x_CP_OTP_LOAD       		(RTD299x_REG_BASE + 0x1519C)
	#define OTP_LOAD							(0x01 << 0)

#define RTD299x_CP_REG_KEY0				(RTD299x_REG_BASE + 0x15034)
#define RTD299x_CP_REG_KEY1				(RTD299x_REG_BASE + 0x15038)
#define RTD299x_CP_REG_KEY2				(RTD299x_REG_BASE + 0x1503C)
#define RTD299x_CP_REG_KEY3				(RTD299x_REG_BASE + 0x15040)
#define RTD299x_CP_REG_DATA_IN0			(RTD299x_REG_BASE + 0x15044)
#define RTD299x_CP_REG_DATA_IN1			(RTD299x_REG_BASE + 0x15048)
#define RTD299x_CP_REG_DATA_IN2			(RTD299x_REG_BASE + 0x1504C)
#define RTD299x_CP_REG_DATA_IN3			(RTD299x_REG_BASE + 0x15050)
#define RTD299x_CP_REG_DATA_OUT0		(RTD299x_REG_BASE + 0x15054)
#define RTD299x_CP_REG_DATA_OUT1		(RTD299x_REG_BASE + 0x15058)
#define RTD299x_CP_REG_DATA_OUT2		(RTD299x_REG_BASE + 0x1505C)
#define RTD299x_CP_REG_DATA_OUT3		(RTD299x_REG_BASE + 0x15060)
#define RTD299x_CP_REG_DATA_OUT4		(RTD299x_REG_BASE + 0x15064)
#define RTD299x_CP_REG_DATA_OUT5		(RTD299x_REG_BASE + 0x15068)
#define RTD299x_CP_REG_DATA_OUT6		(RTD299x_REG_BASE + 0x1506C)
#define RTD299x_CP_REG_DATA_OUT7		(RTD299x_REG_BASE + 0x15070)
#define RTD299x_CP_REG_IV0				(RTD299x_REG_BASE + 0x150D0)
#define RTD299x_CP_REG_IV1				(RTD299x_REG_BASE + 0x150D4)
#define RTD299x_CP_REG_IV2				(RTD299x_REG_BASE + 0x150D8)
#define RTD299x_CP_REG_IV3				(RTD299x_REG_BASE + 0x150DC)
#define RTD299x_CP_REG_IV4				(RTD299x_REG_BASE + 0x150E0)
#define RTD299x_CP_REG_IV5				(RTD299x_REG_BASE + 0x150E4)
#define RTD299x_CP_REG_IV6				(RTD299x_REG_BASE + 0x150E8)
#define RTD299x_CP_REG_IV7				(RTD299x_REG_BASE + 0x150EC)
#define RTD299x_CP_REG_SET				(RTD299x_REG_BASE + 0x15074)
#define RTD299x_CP_REG_SET1				(RTD299x_REG_BASE + 0x15078)
#define RTD299x_CP_REG_SET2				(RTD299x_REG_BASE + 0x1507C)

#define RTD299x_CP_TP_KEY_INFO0			(RTD299x_REG_BASE + 0x14058)
#define RTD299x_CP_TP_KEY_INFO1			(RTD299x_REG_BASE + 0x1405C)
#define RTD299x_CP_TP_KEY_CTRL			(RTD299x_REG_BASE + 0x14060)


/* =============================================================================== */
/*  Descriptor Definition														   */
/* =============================================================================== */
//#define MCP_BCM(x)     			((x & 0x03) << 6)
//#define MCP_BCM_ECB          					(0x00) //AES, DES/TDES
//#define MCP_BCM_CBC          					(0x01) //AES, DES/TDES
//#define MCP_BCM_CTR          					(0x02) //AES
//#define MCP_BCM_RCBC_CS					(0x03) //AES for Irdeto only
//#define MCP_ENC(x)     			((x & 0x01) << 5)
//#define MCP_MODE(x)     			(x & 0x1F)
//#define MCP_ALGO_DES         					(0x00)
//#define MCP_ALGO_3DES        				(0x01)
//#define MCP_ALGO_MD5         					(0x03)
//#define MCP_ALGO_SHA_1       				(0x04)
//#define MCP_ALGO_AES         					(0x05)
//#define MCP_ALGO_AES_G       				(0x06)
//#define MCP_ALGO_AES_H       				(0x07)
//#define MCP_ALGO_CMAC        				(0x08)
//#define MCP_ALGO_CSA        					(0x09)
//#define MCP_ALGO_MULTI2        				(0x0A)
//#define MCP_ALGO_SHA_256        				(0x0B)
//#define MCP_ALGO_LOAD_MICRO_CODE        	(0x0E)
//#define MCP_ALGO_MICRO_CODE        			(0x0F)

#define MCP_KEY_SEL(x) 			((x & 0x03) << 12)
#define MCP_KEY_SEL_CW      				(0x02)
#define MCP_KEY_SEL_OTP      				(0x01)
#define MCP_KEY_SEL_DESC     				(0x00)

#define MCP_IV_SEL(x)  			((x & 0x01) << 11)
#define MCP_IV_SEL_REG      				(0x01)
#define MCP_IV_SEL_DESC     				(0x00)

#define MCP_CW_KEY(x)        				(((x) & 0x7F)<<8)

/* =============================================================================== */
/*  MACROS														   				   */
/* =============================================================================== */
#define MCP_CTRL                  			RTD299x_MCP_CTRL
#define MCP_STATUS                			RTD299x_MCP_STATUS
#define MCP_EN                    			RTD299x_MCP_EN
#define MCP_BASE                  			RTD299x_MCP_BASE
#define MCP_LIMIT                 			RTD299x_MCP_LIMIT
#define MCP_RDPTR                 			RTD299x_MCP_RDPTR
#define MCP_WRPTR                 			RTD299x_MCP_WRPTR
#define MCP_CTRL1                 			RTD299x_MCP_CTRL1
#define MCP_OTP_LOAD              			RTD299x_CP_OTP_LOAD
#define MCP_AES_INI_KEY0          			RTD299x_MCP_AES_INI_KEY0
#define MCP_AES_INI_KEY1          			RTD299x_MCP_AES_INI_KEY1
#define MCP_AES_INI_KEY2          			RTD299x_MCP_AES_INI_KEY2
#define MCP_AES_INI_KEY3          			RTD299x_MCP_AES_INI_KEY3

#define SET_MCP_CTRL(x)           			rtd_outl(MCP_CTRL, x)
#define SET_MCP_STATUS(x)         			rtd_outl(MCP_STATUS, x)
#define SET_MCP_EN(x)             			rtd_outl(MCP_EN, x)
#define SET_MCP_BASE(x)           			rtd_outl(MCP_BASE, x)
#define SET_MCP_LIMIT(x)         			rtd_outl(MCP_LIMIT, x)
#define SET_MCP_RDPTR(x)         			rtd_outl(MCP_RDPTR, x)
#define SET_MCP_WRPTR(x)          			rtd_outl(MCP_WRPTR, x)
#define SET_MCP_CTRL1(x)          			rtd_outl(MCP_CTRL1, x)
#define SET_MCP_OTP_LOAD(x)      			rtd_outl(MCP_OTP_LOAD, x)

#define GET_MCP_CTRL()            			rtd_inl(MCP_CTRL)
#define GET_MCP_STATUS()         			rtd_inl(MCP_STATUS)
#define GET_MCP_EN()              			rtd_inl(MCP_EN)
#define GET_MCP_BASE()            			rtd_inl(MCP_BASE)
#define GET_MCP_LIMIT()           			rtd_inl(MCP_LIMIT)
#define GET_MCP_RDPTR()           			rtd_inl(MCP_RDPTR)
#define GET_MCP_WRPTR()           			rtd_inl(MCP_WRPTR)
#define GET_MCP_CTRL1()           			rtd_inl(MCP_CTRL1)
#define GET_MCP_OTP_LOAD()        		rtd_inl(MCP_OTP_LOAD)
#define GET_MCP_AES_INI_KEY0()  			rtd_inl(MCP_AES_INI_KEY0)
#define GET_MCP_AES_INI_KEY1()  			rtd_inl(MCP_AES_INI_KEY1)
#define GET_MCP_AES_INI_KEY2()  			rtd_inl(MCP_AES_INI_KEY2)
#define GET_MCP_AES_INI_KEY3() 			rtd_inl(MCP_AES_INI_KEY3)

//==================================== Debug ===================================


#define dbg_char(x)

//./linux-3.7.2/arch/arm/bsp-realtek/mach-rtd298x/include/mach/mcp.h

#define MCP_MAX_CW_ENTRY     128
#define MCP_MODE(x) 		 (x & 0x1F)

#define MCP_ALGO_DES         0x00
#define MCP_ALGO_3DES        0x01
#define MCP_ALGO_RC4         0x02
#define MCP_ALGO_MD5         0x03
#define MCP_ALGO_SHA_1       0x04
#define MCP_ALGO_AES         0x05
#define MCP_ALGO_AES_G       0x06
#define MCP_ALGO_AES_H       0x07
#define MCP_ALGO_CMAC        0x08
#define MCP_ALGO_CSA         0x09
#define MCP_ALGO_MULTI2      0x0A
#define MCP_ALGO_SHA256      0x0B


#define MCP_BCM(x)  ((x & 0x3) << 6)
#define MCP_BCM_ECB          	0x0
#define MCP_BCM_CBC          	0x1
#define MCP_BCM_CTR          	0x2

#define MCP_ENC(x)     ((x & 0x1) << 5)


typedef struct
{
    unsigned long flags;
    unsigned long key[6];
    unsigned long iv[4];
    unsigned long data_in;      // data in : physical address
    unsigned long data_out;     // data out : physical address
    unsigned long length;       // data length
}mcp_desc;

typedef struct
{
    mcp_desc*     	p_desc;
    unsigned long 		n_desc;
}mcp_desc_set;

#define MCP_IOCTL_DO_COMMAND    0x70000001
#define MCP_IOCTL_TEST_AES_H    0x71000001


#define FIRST_BLOCK                 0x80
#define LAST_BLOCK                  0x08
#define SINGLE_CLOCK               (FIRST_BLOCK | LAST_BLOCK)

/***************************************************************************
               ------------------- APIS ----------------
****************************************************************************/

#define FILE_HASHING_BUFFER_SIZE                (512 * 1024)

/********************************************************************************
 AES_H Hashing
 ********************************************************************************/
#define AES_H_FILE_HASHING_BUFFER_SIZE        FILE_HASHING_BUFFER_SIZE

int MCP_AES_H_HASH_INIT(mcp_desc* p_desc);
int MCP_AES_H_IV_UPDATE(mcp_desc* p_desc, unsigned char Hash[16]);
int MCP_AES_H_PADDING(unsigned char* p_buff, unsigned long buff_len, unsigned long data_len);
int MCP_AES_H_Hashing(mcp_desc* p_desc, unsigned char* p_in, unsigned long len, unsigned char* p_out);
int MCP_AES_H_DataHash(unsigned char* p_data, unsigned long data_len, unsigned char hash[16], unsigned long block_size, unsigned char first_block);


/********************************************************************************
 DES
 ********************************************************************************/
int MCP_DES_DESC_INIT(mcp_desc* pDesc, unsigned char EnDe, unsigned char Mode, unsigned char Key[7], unsigned char IV[8]);
int MCP_DES_Decryption(unsigned char mode, unsigned char key[7], unsigned char iv[8], unsigned char* p_in, unsigned char* p_out, unsigned long len);
int MCP_DES_Encryption(unsigned char mode, unsigned char key[7], unsigned char iv[8], unsigned char* p_in, unsigned char* p_out, unsigned long len);
#define MCP_DES_ECB_Decryption(key, p_in, p_out, len)       	MCP_TDES_Decryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_DES_ECB_Encryption(key, p_in, p_out, len)       	MCP_TDES_Encryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_DES_CBC_Decryption(key, iv, p_in, p_out, len)   	MCP_TDES_Decryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_DES_CBC_Encryption(key, iv, p_in, p_out, len)   	MCP_TDES_Encryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_DES_CTR_Decryption(key, iv, p_in, p_out, len)   	MCP_TDES_Decryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)
#define MCP_DES_CTR_Encryption(key, iv, p_in, p_out, len)   	MCP_TDES_Encryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)


/********************************************************************************
 TDES
 ********************************************************************************/
int MCP_TDES_DESC_INIT(mcp_desc* pDesc, unsigned char EnDe, unsigned char Mode, unsigned char Key[21], const unsigned char IV[8]);
int MCP_TDES_Decryption(unsigned char mode, unsigned char key[21], const unsigned char iv[8], const unsigned char* p_in, unsigned char* p_out, unsigned long len);
int MCP_TDES_Encryption(unsigned char mode, unsigned char key[21], const unsigned char iv[8], const unsigned char* p_in, unsigned char* p_out, unsigned long len);
#define MCP_TDES_ECB_Decryption(key, p_in, p_out, len)       	MCP_TDES_Decryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_TDES_ECB_Encryption(key, p_in, p_out, len)       	MCP_TDES_Encryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_TDES_CBC_Decryption(key, iv, p_in, p_out, len)   	MCP_TDES_Decryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_TDES_CBC_Encryption(key, iv, p_in, p_out, len)   	MCP_TDES_Encryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_TDES_CTR_Decryption(key, iv, p_in, p_out, len)   	MCP_TDES_Decryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)
#define MCP_TDES_CTR_Encryption(key, iv, p_in, p_out, len)   	MCP_TDES_Encryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)


/********************************************************************************
 AES
 ********************************************************************************/
int MCP_AES_DESC_INIT(mcp_desc* pDesc, unsigned char EnDe, unsigned char Mode, unsigned char Key[16], const unsigned char IV[16]);
int MCP_AES_Decryption(unsigned char mode, unsigned char key[16], const unsigned char iv[16], const unsigned char* p_in, unsigned char* p_out, unsigned long len);
int MCP_AES_Encryption(unsigned char mode, unsigned char key[16], const unsigned char iv[16], const unsigned char* p_in, unsigned char* p_out, unsigned long len);
int MCP_AES_PeekIV(unsigned char IV[16]);

#define MCP_AES_ECB_Decryption(key, p_in, p_out, len)       	MCP_AES_Decryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_AES_ECB_Encryption(key, p_in, p_out, len)       	MCP_AES_Encryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_AES_CBC_Decryption(key, iv, p_in, p_out, len)   	MCP_AES_Decryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_AES_CBC_Encryption(key, iv, p_in, p_out, len)   	MCP_AES_Encryption(MCP_BCM_CBC, key, iv, p_in, p_out, len)
#define MCP_AES_CTR_Decryption(key, iv, p_in, p_out, len)   	MCP_AES_Decryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)
#define MCP_AES_CTR_Encryption(key, iv, p_in, p_out, len)   	MCP_AES_Encryption(MCP_BCM_CTR, key, iv, p_in, p_out, len)


/********************************************************************************
 SHA-1 Hashing
 ********************************************************************************/
#define SHA1_FILE_HASHING_BUFFER_SIZE        FILE_HASHING_BUFFER_SIZE
#define SHA1_DIGEST_SIZE                     20
#define SHA1_BLOCK_SIZE                      64
#define SHA1_ALIGNMENT_CHECK                 0x3F

int MCP_SHA1_HASH_INIT(mcp_desc* p_desc);
int MCP_SHA1_IV_UPDATE(mcp_desc* p_desc, unsigned char hash[SHA1_DIGEST_SIZE]);
int MCP_SHA1_PADDING(unsigned char* p_buff, unsigned long buff_len, unsigned long data_len);
int MCP_SHA1_Hashing(mcp_desc* p_desc, unsigned char* p_in, unsigned long len, unsigned char* p_out);
int MCP_SHA1_DataHash(unsigned char* p_data, unsigned long data_len, unsigned char hash[SHA1_DIGEST_SIZE], unsigned long block_size, unsigned char first_block);

/********************************************************************************
 SHA-256 Hashing
 ********************************************************************************/
#define SHA256_FILE_HASHING_BUFFER_SIZE        FILE_HASHING_BUFFER_SIZE
#define SHA256_DIGEST_SIZE                     32
#define SHA256_BLOCK_SIZE                      64
#define SHA256_ALIGNMENT_CHECK                 0x3F

int MCP_SHA256_HASH_INIT(mcp_desc* p_desc);
int MCP_SHA256_IV_UPDATE(mcp_desc* p_desc, unsigned char hash[SHA256_DIGEST_SIZE]);
int MCP_SHA256_PADDING(unsigned char* p_buff, unsigned long buff_len, unsigned long data_len);
int MCP_SHA256_Hashing(mcp_desc* p_desc, unsigned char* p_in, unsigned long len, unsigned char* p_out);
int MCP_SHA256_DataHash(unsigned char* p_data, unsigned long data_len, unsigned char hash[SHA256_DIGEST_SIZE], unsigned long block_size, unsigned char first_block);


/********************************************************************************
 misc
 ********************************************************************************/
void* mcp_malloc(unsigned long size);
void  mcp_free(void* addr, unsigned long size);
void  mcp_dump_mem(unsigned char* data, unsigned int len);
#define mcp_dump_data_with_text(data, len ,fmt, args...)  do {\
                                                            printk(fmt, ## args);\
                                                            mcp_dump_mem(data, len);\
                                                        }while(0)



#endif  // __MCP_REG_H__
