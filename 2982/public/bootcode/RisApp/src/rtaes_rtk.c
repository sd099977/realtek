/** \file
 * This file contains the function definitions for crypto operations, triggering and
 * OTP read operations.
 *
 * Crypto operations and OTP reading are described in more detail below.
 *
 * \section crypto Hardware crypto engines
 *
 * Crypto operations can be split in two parts.
 * There is a preparation phase, where input data and/or key data is set and
 * there is a computation phase where the actual cryptographic operation is
 * performed. These phases are split so that there is fine grained control
 * over the power or EMA measurements.
 *
 * In our tests we focus on the cryptographic engines that are related to the
 * chip internal root keys. Typically in a chip one can perform hardware
 * accelerated crypto operations, or one can use key ladder operations.
 * If physically the same hardware is used between hardware accelerated crypto
 * and key ladder operations, then the hardware accelerated crypto should be used
 * to implement the crypto operations with user-settable key, input, and observable
 * output.
 *
 * If physically not the same hardware engine is used, the (first step) of a
 * key ladder operation should be used to implement the crypto operations with user-settable input. If the decrypt output is not available, no output is returned to the test tool.
 *
 * Commonly a chipset supports the acceleration of several cryptographic algorithms
 * and could be interesting to test. However, only the cryptographic algorithms
 * used for descrambling and PVR are relevant (usually DES and AES). The vendor is
 * responsible for identifying the relevant cryptographic operations using the
 * relevant crypto engines and relevant hardware embedded keys and implement the API
 * calls in the accordingly.
 *
 * During our test setup and power analysis we need the lowest level of control
 * over the user code before the hardware crypto operations are started. The
 * source of the code path from the crypto call in our test application to
 * trigger the start of the hardware crypto must be available in source form
 * (no calls into binary libraries are allowed).
 *
 * \section otp OTP reading
 *
 * The target test application contains API calls for OTP fuse reads. This code is used in fault
 * injection tests. During the fault injection tests on the OTP fuse reads, faults are introduced
 * into the chipset that may cause the chipset to return OTP fuse values from another OTP fuse bank
 * or area than it is supposed to, such as the key ladder root keys, which are normally unreadable.
 *
 * For implementing the OTP fuse reads, it is assumed that there is a mechanism or API in the chipset
 * to read fuse values (either direct, or through RAM or flipflops) by some addressing or indexing
 * mechanism. If the only publicly readable OTP fuse values are hardwired to registers, this part
 * of the API does not have to be implemented.
 *
 */

#include "sed_common.h"
#include "sed_setup.h"
#include "sed_cert.h"
#include "sed_r2r.h"
#include "sed_otp.h"
#include "sed_char.h"
#include "sed_rtk.h"
#include "sed_drv_uart.h"
#include "sed_drv_sfc.h"
#include "sed_drv_rng.h"
#include "sed_drv_gpio.h"
#include "sed_types.h"
#include "otp_util.h"
#include "rtaes_testapp.h"
#include "rtaes_testfunctions.h"
#include "sed_drv_md.h"
#include "sed_drv_kt.h"
//#include "big_util.h"

/* ==========================================================================*/
/* reference doc */
/* ==========================================================================*/
/*
 NOCS Key Table and Management Overview :
    ==> http://dtdinfo.realtek.com.tw/svn/MM/RL6330_PC/trunk/doc/Hardware/arch_spec_for_CA/Sirius_NOCS_KeyTable_arch_spec.doc
 Riscure
    ==> Y:\nfs\kernel\sirius\NAGRA\Riscus\test-app-1.1\test-app-1.1\doc\index.html

*/
/* ==========================================================================*/
/* local veriable */
/* ==========================================================================*/
static uint32_t kt_rdkey_usage;
static uint32_t kt_htkey_usage;
static uint32_t md_usage;
static uint32_t md_type;

static uint16_t tdes_data_len;
static uint16_t aes_data_len;
static uint16_t rsa_data_len;
static uint16_t rsa_key_len;

static uint32_t fact_status;

/* ==========================================================================*/
/* Debug define */
/* ==========================================================================*/
#define DEBUG_DES_FLOW
#define DEBUG_TDES_FLOW
#define DEBUG_AES_FLOW
#define DEBUG_RSA_FLOW

#define DISABLE_OTP_FLOW
#define DISABLE_DES_FLOW
#define DISABLE_TDES_FLOW
#define DISABLE_AES_FLOW
//#define DISABLE_RSA_FLOW


/* ==========================================================================*/
/* local define */
/* ==========================================================================*/
#define AES                 0x0
#define TDES                0x1

//#define R2R_CMD_DEBUG
#define RIS_DES_DATA_LEN    8
#define RIS_TDES_DATA_LEN   8
#define RIS_AES_DATA_LEN    16

#define RIS_CMD_KEY_LEN     16
#define RIS_DES_KEY_LEN     8
#define RIS_TDES_KEY_LEN    16
#define RIS_AES_KEY_LEN     16

#define RIS_TDES            0x1
#define RIS_AES             0x2
#define RIS_RSA             0x3

#define TDES_KEY_SET    (0x01UL<<0)
#define TDES_DATA_SET   (0x01UL<<1)
#define AES_KEY_SET     (0x01UL<<2)
#define AES_DATA_SET    (0x01UL<<3)
#define RSA_KEY_SET     (0x01UL<<4)
#define RSA_DATA_SET    (0x01UL<<5)

/* ==========================================================================*/
/* external function proto */
/* ==========================================================================*/
//extern unsigned int do_RSA( const unsigned int signature_addr,
//                            const unsigned int rsa_key_addr,
//                            const unsigned int output_addr);

extern unsigned int do_RSA(unsigned char op,
					const unsigned int text_addr,
					const unsigned int rsa_key_addr,
					const unsigned int output_addr);

/* ==========================================================================*/
/* function body */
/* ==========================================================================*/
/**
 * This function must configure the UART to be running at 115200 baud
 * and 8N1 mode (8 data bits, no parity, 1 stop bit).
 */
void initSerial(void)
{
    /* sed_drv_uart.c void sed_uart_init (void) */
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);
}


/**
 * The test application must configure the chipset as efficient as possible
 * for testing. All noise should be kept at a minimum to increase the efficiency
 * of the measurements.
 *
 * If possible, power saving modes should be activated to decrease the noise
 * while taking measurements. Preferably the chip is put into a standby mode
 * where the main core and crypto operations still run.
 *
 * All unused clocks of the chipset increase the noise in the measurements made
 * during DPA and DEMA testing. They should be switched off if not required for
 * the test application to run.
 *
 * All unused peripherals (e.g. USB, Ethernet, Descrambler, etc) increase the
 * noise in the measurements made during DPA and DEMA testing.
 *
 */
void initBoard(void)
{
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    kt_rdkey_usage = 0;
    kt_htkey_usage = 0;
    md_usage       = 0;
    md_type        = 0;

    tdes_data_len  = 0;
    aes_data_len   = 0;
    rsa_data_len   = 0;
    rsa_key_len	   = 0;

    /* clear all action flag */
    fact_status = 0;
}

/**
 * Sends one character over the line and returns the status to the caller.

 * @param data byte to send
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t serial_send(uint8_t data)
{
    uint8_t rstatus = STATUS_OK;
    //sed_printf1("%s: 0x%x\n", __func__,data);
    rtk_putc(data,UART0_REG_BASE);

    return rstatus;
}

/**
 * Receives 1 byte and stores it in the data argument. This function must be blocking.
 *
 * @param data pointer to where to store the byte
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t serial_recv(uint8_t* data)
{
    uint8_t rstatus = STATUS_ERROR;
    if(rtk_getc(data,UART0_REG_BASE) == 0){
        //sed_printf0("%s",data);
        //sed_printf1("%s: 0x%x\n", __func__,*data);
        rstatus = STATUS_OK;
    }
    return rstatus;
}

/**
 * Enable the output that is used as trigger (e.g. a GPIO pin). Care must be taken that
 * the code that enables or disables the trigger is time constant and has a delay
 * (between calling the routine and performing the trigger operation) as small as
 * possible.
 */
void enableTrigger(void)
{
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);
    GPIO_pulse();
    //GPIO_reset;
}

/**
 * Disable the output that is used as trigger (the same one previously enabled with enableTrigger())
 */
void disableTrigger(void)
{
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);
    GPIO_pulse();
    //GPIO_toggle;
}

/**
 * This function receives an input a byte array address of length addressLength which encodes
 * the offset or index into OTP data that should be returned in parameter data. If for example the
 * chipset only supports indexed access to OTP blocks of a fixed size, address may only contain a
 * single byte (assumed that there are no more than 256 indexes). See also \ref otp.
 *
 * The length of the returned data has to be written in dataLength. If the read operation fails,
 * this function must return an error.
 *
 * @param address pointing to OTP data
 * @param addressLength length of the address
 * @param data (output parameter) OTP data read at the specified address
 * @param dataLength (output parameter) length of OTP data read.
 * @return
 */
uint8_t readOTP( uint16_t*  address,
                 uint16_t  addressLength,
                 uint8_t*  data,
                 uint16_t* dataLength )
{
#ifndef DISABLE_OTP_FLOW
    int i;
    int res;
    uint8_t rstatus = STATUS_OK;
    uint16_t star_adr;
    uint16_t temp_adr;
    //uint8_t temp_len;
    //uint32_t *otp_buf;
    uint8_t  *otp_buf8;
    uint32 val;
    uint8_t sht;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);
    //otp_buf = (uint32_t*)OTP_BUF_ADR;

    *dataLength = 0;
    for(i=0;i<addressLength;i++){

        temp_adr = address[i];
        star_adr = temp_adr & 0xfffc;
        otp_buf8 = (uint8_t*)&val;
        sed_printf1("address[%d] = 0x%04x; star_adr=0x%04x\n",i,address[i],star_adr);

        if(1){
            res = otp_read(star_adr,&val);
        }else{  //test only
            res = 0;
            val = 0x12345678;
        }

        if(res){
            sed_printf1("otp_read fail!!!\n");
            break;
        }else{
            sht = temp_adr%4;
            data[i] = *(otp_buf8+3-sht);
            sed_printf1("val = 0x%08x; sht = %d\n",val,sht);
            sed_printf1("data[%d] = 0x%02x\n",i,data[i]);
            *dataLength += 1;
        }
    }

    if(*dataLength != addressLength){
        rstatus = STATUS_ERROR;
    }
    return rstatus;


#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}


/**
 * @param address pointing to OTP data
 * @param addressLength length of the address
 * @param data (output parameter) OTP data will be write to specified address
 * @param dataLength (output parameter) length of OTP data write.
 * @return
 */
uint8_t writeOTP( uint16_t*  address,
                 uint16_t  addressLength,
                 uint8_t*  data,
                 uint16_t* dataLength )
{
#ifndef DISABLE_OTP_FLOW
    int i;
    int res;
    uint8_t rstatus = STATUS_OK;
    uint16_t star_adr;
    uint16_t temp_adr;
    //uint8_t temp_len;
    //uint32_t *otp_buf;
    //uint8_t  *otp_buf8;
    uint32 tmp_val;
    uint8_t sht;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    *dataLength = 0;
    for(i=0;i<addressLength;i++){

        temp_adr = address[i];
        star_adr = temp_adr & 0xfffc;
        sed_printf1("address[%d] = 0x%04x; star_adr=0x%04x; data=0x%02x\n",
                     i,address[i],star_adr,data[i]);

        sht = (8 * (3-(temp_adr%4)));
        tmp_val = (uint32 )data[i] << sht;

        sed_printf1(" val = 0x%08x\n",tmp_val);

        if(1){
            res = otp_write(star_adr,tmp_val);
        }else{
            res = 0;
        }

        if(res)
            break;

        *dataLength+=1;
    }

    if(*dataLength != addressLength){
        rstatus = STATUS_ERROR;
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

#if defined(DISABLE_DES_FLOW) && defined(DISABLE_DES_FLOW) && defined(DISABLE_AES_FLOW)
#define rtk_r2r_configuration ()
#define rtk_md_dsc_active()

#else
static int rtk_r2r_configuration (
    uint8                   op,
    uint8                   algoId,
    uint32*                 ikt_rdkey_usage,
    uint32*                 ikt_htkey_usage,
    uint32*                 imd_usage,
    uint32*                 imd_type
    )
{
    uint32 u1 = 0, u2 = 0, u3 = 0;
    uint32 type = MD_DSC_DATATYPE_WRITE_EN2 | MD_DSC_DATATYPE_DSC_M2M_TYPE_DATA;

    switch (algoId)
    {
    case AES:
    	sed_printf1("%s(%d)AES\n",__func__,__LINE__);
        u1    = KT_RDKEY_USAGE_CE_AES|KT_RDKEY_USAGE_AES_ECB;
        u2    = KT_HTKEY_USAGE_CE_AES|KT_HTKEY_USAGE_KS_128;
        u3    = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_ECB;
        type |= MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
        break;

    case TDES:
    	sed_printf1("%s(%d)TDES\n",__func__,__LINE__);
        u1    = KT_RDKEY_USAGE_CE_TDES|KT_RDKEY_USAGE_TDES_ECB;
        u2    = KT_HTKEY_USAGE_CE_TDES|KT_HTKEY_USAGE_KS_128;
        u3    = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_ECB;
        type |= MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
        break;

    default:
        return -1;
    }

    if (op == RTK_ENC)  {
    	sed_printf1("%s(%d)ENC\n",__func__,__LINE__);
        u1 |= KT_RDKEY_USAGE_ENC;
        u2 |= KT_HTKEY_USAGE_ENC;
        u3 |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_ENCRYPT;
    } else {
		sed_printf1("%s(%d)DEC\n",__func__,__LINE__);
        u1 |= KT_RDKEY_USAGE_DEC;
        u2 |= KT_HTKEY_USAGE_DEC;
        u3 |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_DECRYPT;
    }

    if (ikt_rdkey_usage)
        *ikt_rdkey_usage = u1;

    if (ikt_htkey_usage)
        *ikt_htkey_usage = u2;

    if (imd_usage)
        *imd_usage = u3;

    if (imd_type)
        *imd_type = type;

    return 0;
}

uint8_t rtk_md_dsc_active(uint8_t op,uint8 algoId,uint8_t* response, uint16_t* length)
{
    uint8_t 	rstatus = STATUS_OK;
    uint8_t* 	p_idata;
    uint8_t* 	p_odata;
    uint32_t* 	p_key;
    uint16_t    i;
    uint16_t    data_len;
    uint16_t    key_len;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if (rtk_r2r_configuration(op, algoId, &kt_rdkey_usage, &kt_htkey_usage, &md_usage, &md_type)) {
        sed_printf1("config error\n");
        rstatus = STATUS_ERROR;
    }else{

        if(algoId == TDES){
        	key_len = RIS_TDES_KEY_LEN;
        	data_len = tdes_data_len;
        	p_key   = (uint32_t*)TDES_KEY_BUF;
			p_idata = (uint8_t*)TDES_IDATA_BUF;
        	p_odata = (uint8_t*)TDES_ODATA_BUF;
		}else{
			key_len = RIS_AES_KEY_LEN;
			data_len = aes_data_len;
			p_key   = (uint32_t*)AES_KEY_BUF;
			p_idata = (uint8_t*)AES_IDATA_BUF;
        	p_odata = (uint8_t*)AES_ODATA_BUF;
		}

#if defined(DEBUG_DES_FLOW) || defined(DEBUG_TDES_FLOW) || defined(DEBUG_AES_FLOW)
        if(1){
            uint8_t* p_key8 = (uint8_t*)p_key;
            sed_printf1("key :\n");
            for(i=0;i<key_len;i++){
                sed_printf1("%02x ",p_key8[i]);
            }
            sed_printf1("\n");
            sed_printf1("data :");
            for(i=0;i<data_len;i++){
                if((i%8) == 0)
                    sed_printf1("\n");
                sed_printf1("%02x ",p_idata[i]);
            }
            sed_printf1("\n");
        }
#endif

        /* Config MD */
        REG32(MD_KT_CTRL) = md_usage | MD_KT_CTRL_WRITE_EN1 | MD_KT_CTRL_MD_KT_KEY_INDEX(KT_HOST_KEY_IDX);

        // 1. Update Host Key to KeyTable
        sed_printf1("Update Host Key to KeyTable\n");
        REG32(KT_WADR)     = KT_HOST_KEY_IDX;

        REG32(KT_HOSTKEY4) = p_key[0]; //[127:96]
        REG32(KT_HOSTKEY3) = p_key[1]; //[95:64]
        REG32(KT_HOSTKEY2) = p_key[2]; //[63:32]
        REG32(KT_HOSTKEY1) = p_key[3]; //[31:0]

        REG32(KT_HTKEY_USAGE) = kt_htkey_usage;//0xB8035830

        REG32(KT_HTKEY_USAGE) = kt_htkey_usage|KT_HTKEY_USAGE_VALID;
        while(REG32(KT_HTKEY_USAGE) & KT_HTKEY_USAGE_VALID);

        // 2. Load Key from Key Table to DSC
        sed_printf1("Load Key from Key Table to DSC\n");
        REG32(KT_RDKEY_USAGE) = kt_rdkey_usage | KT_RDKEY_USAGE_HOST_KEY_IDX | KT_RDKEY_USAGE_EN;
        while(REG32(KT_RDKEY_USAGE) & KT_RDKEY_USAGE_EN);

        /* Set DataIn to crypto engine data registers */
        sed_printf1("Set DataIn to crypto engine data registers\n");

        REG32(MD_DSC_SADDR)    = (uint32)p_idata & 0x3FFFFFF;
        REG32(MD_DSC_DESTADDR) = (uint32)p_odata & 0x3FFFFFF;

        REG32(MD_DSC_TOTLENGTH) = data_len;
        REG32(MD_DSC_HEADERLEN) = 0;
        REG32(MD_DSC_DATATYPE)  = md_type;
        REG32(MD_DSC_CNTL)      = MD_DSC_CNTL_DSC_GO;

        sed_printf1("DSC SADDR=%08lx, DADER=%08lx, TOTLEN=%d, HDRLEN=%d, TYPE=%08lx\n",
                     REG32(MD_DSC_SADDR),
                     REG32(MD_DSC_DESTADDR),
                     REG32(MD_DSC_TOTLENGTH),
                     REG32(MD_DSC_HEADERLEN),
                     REG32(MD_DSC_DATATYPE));

        sed_printf1("GO!!! \n");
        REG32(MD_DSC_CNTL) = MD_DSC_CNTL_DSC_GO | MD_DSC_CNTL_WRITE_DATA;

        sed_printf1("Wait Complete\n");
        while (!(REG32(MD_DSC_CNTL) & MD_DSC_CNTL_DSC_IDEL)){
            /* for ccheck status */
            sed_printf1("DSC State=%08lx\n", REG32(MD_DSC_CNTL));
        }
        sed_printf1("DSC Complete\n");

        // 4. copy output data from CPU internal registers to response buffer
        *length = data_len;
        for (i=0; i<data_len;i++){
            response[i] = p_odata[i];
#if defined(DEBUG_DES_FLOW) || defined(DEBUG_TDES_FLOW) || defined(DEBUG_AES_FLOW)
            if(1){
                if(i == 0)
                    sed_printf1("result :");
                if((i%8) == 0)
                    sed_printf1("\n");
                sed_printf1("%02x ",response[i]);
            }
#endif
        }
        sed_printf1("\n");

#if defined(DEBUG_DES_FLOW) || defined(DEBUG_TDES_FLOW) || defined(DEBUG_AES_FLOW)
		sed_printf1("result string:\n");
        for (i=0; i<data_len;i++){
			sed_printf1("%02x",response[i]);
        }
        sed_printf1("\n");
#endif

    }

    return rstatus;
}
#endif
/**
 * Sets the input for the DES operation. For applicability of this method,
 * see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */

uint8_t desSetData(uint8_t* data, uint16_t length)
{
#ifndef DISABLE_DES_FLOW
    uint16_t    i;
    uint8_t rstatus = STATUS_OK;
    uint8_t* p_idata;

    sed_printf1("RISCURS %s(%d) length = %d\n", __func__, __LINE__,length);

    if(length % RIS_DES_DATA_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of data not align to %d\n",RIS_DES_DATA_LEN);
    }else{
#ifdef DEBUG_DES_FLOW
        sed_printf1("data :");
        for(i=0;i<length;i++){
            if(i%8 == 0)
                sed_printf1("\n");
            sed_printf1("%02x ",data[i]);
        }
        sed_printf1("\n");
#endif
        fact_status |= TDES_DATA_SET;

        tdes_data_len = length;
        p_idata = (uint8_t*)TDES_IDATA_BUF;	//use TDES buffeer as DES buffer
        for (i=0; i<length;i++){
            p_idata[i] = data[i];
        }

    }
    return rstatus;
#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desSetKey(uint8_t* key, uint16_t length)
{
#ifndef DISABLE_DES_FLOW
    uint8_t rstatus = STATUS_OK;
    uint16_t    i;
    uint8_t* p_key;

    sed_printf1("RISCURS %s(%d) length = %d\n", __func__, __LINE__,length);

    if(length != RIS_DES_KEY_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of key more then %d\n",RIS_DES_KEY_LEN);
    }else{
#ifdef DEBUG_DES_FLOW
        sed_printf1("key08 : [");
        for(i=0;i<RIS_DES_KEY_LEN;i++){
            sed_printf1("%02x ",key[i]);
        }
        sed_printf1("]\n");
#endif
        fact_status |= TDES_KEY_SET;
        p_key = (uint8_t*)TDES_KEY_BUF;	//use TDES buffeer as DES buffer
        for (i=0; i<length;i++)
            p_key[i] = p_key[i+8] = key[i];

#ifdef DEBUG_DES_FLOW
        sed_printf1("key16 : [");
        for(i=0;i<(RIS_DES_KEY_LEN*2);i++){
            sed_printf1("%02x ",p_key[i]);
        }
        sed_printf1("]\n");
#endif
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Runs a DES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desEncrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_DES_FLOW
    uint8_t rstatus = STATUS_OK;
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if((fact_status & (TDES_KEY_SET|TDES_DATA_SET)) !=
       (TDES_KEY_SET|TDES_DATA_SET))
	{
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(TDES_KEY_SET|TDES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_ENC,TDES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Runs a DES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t desDecrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_DES_FLOW
   uint8_t rstatus = STATUS_OK;
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if((fact_status & (TDES_KEY_SET|TDES_DATA_SET)) !=
       (TDES_KEY_SET|TDES_DATA_SET))
	{
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(TDES_KEY_SET|TDES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_DEC,TDES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}


/**
 * Sets the input for the TDES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesSetData(uint8_t* data, uint16_t length)
{
#ifndef DISABLE_TDES_FLOW
    uint16_t    i;
    uint8_t rstatus = STATUS_OK;
    uint8_t* p_idata;

    sed_printf1("RISCURS %s(%d) length = %d\n", __func__, __LINE__,length);

    if(length % RIS_TDES_DATA_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of data not align to %d\n",RIS_TDES_DATA_LEN);
    }else{
#ifdef DEBUG_TDES_FLOW
        sed_printf1("data :");
        for(i=0;i<length;i++){
            if(i%8 == 0)
                sed_printf1("\n");
            sed_printf1("%02x ",data[i]);
        }
        sed_printf1("\n");
#endif
        fact_status |= TDES_DATA_SET;

        tdes_data_len = length;
        p_idata = (uint8_t*)TDES_IDATA_BUF;
        for (i=0; i<length;i++){
            p_idata[i] = data[i];
        }

    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesSetKey(uint8_t* key, uint16_t length)
{
#ifndef DISABLE_TDES_FLOW
    uint8_t rstatus = STATUS_OK;
    uint16_t    i;
    uint8_t* p_key;

    sed_printf1("RISCURS %s(%d) length = %d\n", __func__, __LINE__,length);

    if(length != RIS_TDES_KEY_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of key more then %d\n",RIS_TDES_KEY_LEN);
    }else{
#ifdef DEBUG_TDES_FLOW
        sed_printf1("key : [");
        for(i=0;i<RIS_TDES_KEY_LEN;i++){
            sed_printf1("%02x ",key[i]);
        }
        sed_printf1("]\n");
#endif
        fact_status |= TDES_KEY_SET;
        p_key = (uint8_t*)TDES_KEY_BUF;
        for (i=0; i<length;i++)
            p_key[i] = key[i];
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}



/**
 * Runs a TDES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesEncrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_TDES_FLOW
    uint8_t rstatus = STATUS_OK;

    if((fact_status & (TDES_KEY_SET|TDES_DATA_SET)) !=
       (TDES_KEY_SET|TDES_DATA_SET)){
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(TDES_KEY_SET|TDES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_ENC,TDES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}



/**
 * Runs a TDES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t tdesDecrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_TDES_FLOW
    uint8_t rstatus = STATUS_OK;
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if((fact_status & (TDES_KEY_SET|TDES_DATA_SET)) !=
       (TDES_KEY_SET|TDES_DATA_SET)){
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(TDES_KEY_SET|TDES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_DEC,TDES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Sets the input for the AES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesSetData(uint8_t* data, uint16_t length)
{
#ifndef DISABLE_AES_FLOW
    uint16_t    i;
    uint8_t rstatus = STATUS_OK;
    uint8_t* p_idata;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if(length % RIS_AES_DATA_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of data not align to %d\n",RIS_AES_DATA_LEN);
    }else{
#ifdef DEBUG_AES_FLOW
        sed_printf1("data :");
        for(i=0;i<length;i++){
            if(i%8 == 0)
                sed_printf1("\n");
            sed_printf1("%02x ",data[i]);
        }
        sed_printf1("\n");
#endif

        fact_status |= AES_DATA_SET;
        aes_data_len = length;
        p_idata = (uint8_t*)AES_IDATA_BUF;
        for (i=0; i<length;i++){
            p_idata[i] = data[i];
        }
    }

    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesSetKey(uint8_t* key, uint16_t length)
{
#ifndef DISABLE_AES_FLOW
    uint8_t rstatus = STATUS_OK;
    uint16_t    i;
    uint8_t* p_key;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if(length != RIS_AES_KEY_LEN){
        rstatus = STATUS_ERROR;
        sed_printf1("length of key more then %d\n",RIS_AES_KEY_LEN);
    }else{
#ifdef DEBUG_TDES_FLOW
        sed_printf1("key : [");
        for(i=0;i<RIS_AES_KEY_LEN;i++){
            sed_printf1("%02x ",key[i]);
        }
        sed_printf1("]\n");
#endif
        fact_status |= AES_KEY_SET;
        p_key = (uint8_t*)AES_KEY_BUF;
        for (i=0; i<length;i++)
            p_key[i] = key[i];
    }

    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Runs a AES encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesEncrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_AES_FLOW
    uint8_t rstatus = STATUS_OK;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if((fact_status & (AES_KEY_SET|AES_DATA_SET)) !=
       (AES_KEY_SET|AES_DATA_SET)){
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(AES_KEY_SET|AES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_ENC,AES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Runs a AES decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t aesDecrypt(uint8_t* response, uint16_t* length)
{
#ifndef DISABLE_AES_FLOW
    uint8_t rstatus = STATUS_OK;
    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    if((fact_status & (AES_KEY_SET|AES_DATA_SET)) !=
       (AES_KEY_SET|AES_DATA_SET)){
        sed_printf1("key or data not have not set.\n");
        rstatus = STATUS_ERROR;
    }else{
        fact_status &= ~(AES_KEY_SET|AES_DATA_SET);
        rstatus = rtk_md_dsc_active(RTK_DEC,AES,response,length);
    }
    return rstatus;

#else
	uint8_t rstatus = STATUS_OK;
    sed_printf1("Disable %s function\n",__func__);
    return rstatus;
#endif

}

/**
 * Sets the input for the AES operation. For applicability of this method, see \ref crypto.
 *
 * @param data to use as input for the crypto operation.
 * @param length of the data (8 for DES).
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaSetData(uint8_t* data, uint16_t length)
{
    uint16_t    i;
    uint8_t rstatus = STATUS_OK;//STATUS_OK;
    uint8_t* p_idata;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);

    /* should to check length of RSA data ? */

    fact_status |= RSA_DATA_SET;

    rsa_data_len = length;
    sed_printf1("length of RSA data is %d\n",rsa_data_len);
    p_idata = (uint8_t*)RSA_IDATA_BUF;
    for (i=0; i<length;i++)
        p_idata[i] = data[i];

    return rstatus;
}

/**
 * Sets the key for the crypto operation. For applicability of this method, see \ref crypto.
 *
 * @param key data to set as key
 * @param length of the key
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaSetKey(uint8_t* key, uint16_t length)
{
    uint8_t rstatus = STATUS_OK;
    uint16_t    i;
    uint8_t* p_key;

    sed_printf1("RISCURS %s(%d)\n", __func__, __LINE__);
	rsa_key_len = length;

    fact_status |= RSA_KEY_SET;
    sed_printf1("length of RSA key is %d\n",length);
    p_key = (uint8_t*)RSA_KEY_BUF;
    for (i=0; i<length;i++)
        p_key[i] = key[i];

    return rstatus;
}


uint8_t rtk_rsa_op(uint8_t op,uint8_t* response, uint16_t* length)
{
    uint16_t    i;
    uint8_t rstatus = STATUS_OK;

    sed_printf1("RISCURS %s(%d)[fact_status=0x%08x]\n",
    			 __func__, __LINE__,fact_status);

	sed_printf1("RSA %srypt operation",(op == RTK_ENC)? "Enc":"Dec");

#ifdef DEBUG_RSA_FLOW
	rsa_data_len = 256;
	if(1){
#else
    if((fact_status & (RSA_KEY_SET|RSA_DATA_SET)) == (RSA_KEY_SET|RSA_DATA_SET)){
		if(((op == RTK_ENC) && (rsa_key_len != 768)) ||
		   ((op == RTK_DEC) && (rsa_key_len != 512))){
			sed_printf1("RSA %srypt lose key.",(op == RTK_ENC)? "Enc":"Dec");
			rstatus = STATUS_ERROR;
			goto ERR_OUT;
		}
#endif

        do_RSA(op|RSA_HW,RSA_IDATA_BUF,RSA_KEY_BUF,(unsigned int)response);
        *length = rsa_data_len;

        sed_printf1("\n\nRSA %srypted Data:",(op == RTK_ENC)? "Enc":"Dec");
        for(i=0;i<*length;i++){
            if((i%16)==0)
                sed_printf1("\n");
            sed_printf1("%02x ",response[i]);
        }

        sed_printf1("\n\nRSA %srypted Data string:\n",(op == RTK_ENC)? "Enc":"Dec");
        for(i=0;i<*length;i++){
            sed_printf1("%02x",response[i]);
        }
        sed_printf1("\n\n");
        sed_printf1("%srypt finish!!(%d)\n",(op == RTK_ENC)? "Enc":"Dec",*length);
    }else{
        rstatus = STATUS_ERROR;
        sed_printf1("Have not set RSA key or DATA.\n");
    }

ERR_OUT:
    fact_status &= ~(RSA_KEY_SET|RSA_DATA_SET);
    return rstatus;
}

/**
 * Runs a RSA encrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */

uint8_t rsaEncrypt(uint8_t* response, uint16_t* length)
{
    return rtk_rsa_op(RTK_ENC,response,length);

}

/**
 * Runs a RSA decrypt operation. For applicability of this method, see \ref crypto.
 *
 * @param response (output parameter) data of the crypto operation, if applicable.
 * @param length (output parameter) length of the response, if applicable.
 * @return status code. For status codes, see STATUS_* defines.
 */
uint8_t rsaDecrypt(uint8_t* response, uint16_t* length)
{
	return rtk_rsa_op(RTK_DEC,response,length);
}


/* end of file */
