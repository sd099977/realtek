/** \file
 *
 * This file implements the test functionality in function testapp(). This code need not
 * be changed by the vendor.
 */

/*
1.  uart0 是燒code的port,進入Riscure APP後擔任RPC port的角色,因此test Vector要從這個port送進去
    uart1 進入Riscure APP後擔任debug port的角色


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
#include "rtaes_testapp.h"
#include "rtaes_testfunctions.h"

static int const BUFLEN = 65536; //!<Maximum buffer length

static uint32_t array_to_uint32(uint8_t* array) {
    return ((array)[0] << 24 | (array)[1] << 16 | (array)[2] << 8 | (array)[3]);
}


static void uint32_to_array(uint32_t number, uint8_t* array) {
    (array)[0] = (number) >> 24;
    (array)[1] = (number) >> 16;
    (array)[2] = (number) >> 8;
    (array)[3] = (number);
}

static uint8_t serial_recv_buffer(uint8_t* buffer, int length) {
    int i;
    int cnt;
    unsigned char ch;
    uint32_t loop = 10000*length;
    uint8_t status = STATUS_ERROR;
    sed_printf1("RISCURS %s(%d)length=%d\n", __func__, __LINE__,length);

    cnt = 0;
    while( loop--){
        if(serial_recv(&ch) == 0){
            buffer[cnt] = ch;
            //sed_printf1("buffer[%d]=%x\n",cnt,buffer[cnt]);
            cnt+=1;
            if(cnt == length){
                status = STATUS_OK;
                break;
            }
        }
    }


#if 0
    for (i = 0; i < length; i++) {
        uint8_t status = serial_recv(buffer + i);
        if (status != STATUS_OK)
            return status;
    }
#endif

    for (i = 0; i < cnt; i++) {
        if((i%8)==0){
            sed_printf1("\n");
            sed_printf1("%04x-%04x : ",i,i+7);
        }
        sed_printf1("0x%02x ", buffer[i]);
    }
    sed_printf1("\n");

    if(status){
        sed_printf1("buffer data lose!!!");
    }

    return status;
}

static uint8_t serial_send_buffer(uint8_t* buffer, int length) {
    uint8_t curStatus = STATUS_OK;
    int i;

    for (i = 0; i < length; i++) {
        curStatus |= serial_send(buffer[i]);
    }

    return curStatus;
}

static uint8_t serial_recv_uint16_t(uint16_t* value) {
    uint8_t status;
    uint8_t tmp;
    uint8_t cnt = 0;
    uint32_t loop = 50000;

    status = STATUS_ERROR;
    //sed_printf1("%s(%d)\n", __func__, __LINE__);
    while(loop--){
        status = serial_recv(&tmp);
        if (status == STATUS_OK){
            if(cnt == 0){
                *value = (tmp << 8);
                cnt +=1;
                //sed_printf1("%s(%d)val=%d\n", __func__, __LINE__,*value);
            }else{
                *value |= tmp;
                //sed_printf1("%s(%d)val=%d\n", __func__, __LINE__,*value);
                break;
            }
        }
    }
    if(loop==0)
        status = STATUS_ERROR;

#if 0
    status = serial_recv(&tmp);
    if (status != STATUS_OK)
        return status;
    *value = (tmp << 8);
    status = serial_recv(&tmp);
    if (status != STATUS_OK){
        return status;
    }
    *value |= tmp;
#endif

    //sed_printf1("%s(%d)val=%d\n", __func__, __LINE__,*value);
    return status;
}

static uint8_t serial_send_uint16_t(uint16_t value) {
    uint8_t curStatus;

    curStatus = serial_send((value >> 8) & 0xFF);
    curStatus |= serial_send(value & 0xFF);

    return curStatus;
}

static uint8_t loopTest(uint8_t* in_buf,
                        uint16_t in_length,
                        uint8_t* out_buf,
                        uint16_t* out_length) {
    // These variables should be declared volatile to prevent the compiler from optimizing out the loop!!
    volatile uint32_t counter = 0;
    volatile uint32_t ceiling = 0;

    if (in_length != 4) {
        *out_length = 0;
        return STATUS_ERROR;
    }

    ceiling = array_to_uint32(in_buf);

    enableTrigger();
    while (counter < ceiling) {
        counter++;
    }
    disableTrigger();

    *out_length = 8;

    uint32_to_array(counter, out_buf);
    uint32_to_array(ceiling, out_buf + 4);

    return STATUS_OK;
}

/**
 * This is the test application's loop and will call functions defined in testfunctions.h. This function does not return.
 *
 * Linux or any real-time OS must not be used to run the test application.
 *
 * The test application should be started directly from the boot loader, or
 * merged into the boot loader (e.g. as a function which can be activated
 * through some diagnostics boot menu).
 *
 * The test application must be the only process running in a single threaded
 * context. This is required so that acquired measurements are not influenced
 * by any schedulers.
 */
void testapp(void) {
    uint16_t    i;
    uint8_t cmd; // Command byte
    uint16_t cmdLen; // Length of the command's data
    uint16_t rspLen; // Length of the repsonse
    //uint8_t cmdBuf[BUFLEN]; // Buffer that contains the received data
    //uint8_t rspBuf[BUFLEN]; // Buffer that contains the response data
    uint8_t *cmdBuf; // Buffer that contains the received data
    uint8_t *rspBuf; // Buffer that contains the response data
    uint8_t status; // Status byte (0 = OK, >0 = Error)

    sed_printf0("Riscure %s %s\n", __TIME__, __DATE__);
    sed_printf1("Riscure %s %s\n", __TIME__, __DATE__);

    cmdBuf = (uint8_t*)TOP_CMD_BUF;
    rspBuf = (uint8_t*)TOP_RSP_BUF;

//#define DDR_TEST_ENABLE
#ifdef DDR_TEST_ENABLE
    for(i=0;i<0x1000;i++){
        cmdBuf[i] = 0;
    }
    for(i=0;i<0x1000;i++){
        cmdBuf[i] = i;
    }

    for(i=0;i<0x1000;i++){
        if(i%8 == 0)
            sed_printf("\n");

        sed_printf("[%03x]=%03x ",i,cmdBuf[i]);
    }
    sed_printf("\n");
#endif  //?#ifdef DDR_TEST_ENABLE

    initSerial();
    initBoard();

    sed_printf1("%s(%d)",__func__,__LINE__);
    while (1) {
        uint8_t recvStatus = STATUS_OK;

        recvStatus = serial_recv(&cmd);
        if (recvStatus == STATUS_OK) {
            recvStatus |= serial_recv_uint16_t(&cmdLen);
        }

        if (recvStatus == STATUS_OK) {
            sed_printf1("%s(%d)cmd=0x%x(len=%u [0x%x])\n",
                         __func__,__LINE__,cmd,cmdLen,cmdLen);
            status = STATUS_OK;
            rspLen = 0;

            // Handle command
            switch (cmd) {
            case CMD_TEST:  //0x74
                rspLen = 4;
                rspBuf[0] = 'O';
                rspBuf[1] = 'K';
                rspBuf[2] = '\r';
                rspBuf[3] = '\n';
                break;

            case CMD_LOOP:  //0x50
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = loopTest(cmdBuf, cmdLen, rspBuf, &rspLen);
                else
                    status = STATUS_COMM_ERR;
                break;

                // OTP related
            case CMD_OTP_READ:     //0x51
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK){
                    /*
                     OTP read cmd format :
                     cmd,                           //cmd_ID
                     data_len_h,data_len_l,         //cmd_data_length
                     otp_num_h,otp_num_l,           //number_of_OTP should be read.
                     opt_idx0_h,opt_idx0_l  //idx0_h,idx0_l
                     opt_idx1_h,opt_idx1_l  //idx1_h,idx1_l
                     opt_idx2_h,opt_idx2_l  //idx2_h,idx2_l,.......

                     note: cmd_data_length = (number_of_OTPx2)+2
                     **/
                    uint8_t* ptr;
                    uint16_t dlen;
                    uint16_t* otp_ary;

                    dlen = ((uint16_t)cmdBuf[0]<<8|cmdBuf[1]);
                    if(dlen> 1024){
                        sed_printf1("OTP length over 1K\n");
                        status = STATUS_ERROR;
                    }else{
                        sed_printf1("data number of OTP is %d\n",dlen);
                        ptr     = cmdBuf+2;
                        otp_ary = (uint16_t*)OTP_POOL;
                        for(i=0;i<dlen;i++){
                            otp_ary[i] = ((uint16_t)ptr[i*2]<<8|ptr[(i*2)+1]);
                            sed_printf1("otp_ary[%d]=0x%x(%d)\n",i,otp_ary[i],otp_ary[i]);
                        }
#if 1
                        status = readOTP( otp_ary,dlen,rspBuf,&rspLen );
#endif
                    }
                }else
                    status = STATUS_COMM_ERR;

                break;

            case CMD_OTP_WRITE:    //0x52
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK){
                   /*
                    OTP write cmd format :
                    cmd,                        //cmd ID
                    data_len_h,data_len_l,      //cmd_data_length
                    otp_num_h,otp_num_l,        //number_of_OTP should be write.
                    opt_idx0_h,opt_idx0_l  		//idx0_h,idx0_l
                    opt_idx1_h,opt_idx1_l  		//idx1_h,idx1_l
                    opt_idx2_h,opt_idx2_l  		//idx2_h,idx2_l,.......
                    .....
                    otp_data0,					//data of idx0 of OTP should be write.
                    otp_data1,					//data of idx1 of OTP should be write.
                    otp_data2           		//data of idx2 of OTP should be write.....
					.....

					note : cmd_data_length = (number_of_OTPx3)+2
                    **/
                    uint8_t* 	ptr;
                    //uint8_t* 	dptr;
					uint16_t 	dlen;
					uint16_t* 	otp_ary;

                    dlen = (uint16_t)cmdBuf[0]<<8|cmdBuf[1];

                    if(dlen> 1024){
						sed_printf1("OTP length over 1K\n");
						status = STATUS_ERROR;
					}else{
						sed_printf1("data number of OTP is %d\n",dlen);
						ptr		= cmdBuf+2;
						otp_ary = (uint16_t*)OTP_POOL;
						for(i=0;i<dlen;i++){
							otp_ary[i] = (uint16_t)ptr[i*2]<<8|ptr[(i*2)+1];
							sed_printf1("otp_ary[%d]=0x%x(%d)\n",i,otp_ary[i],otp_ary[i]);
						}
						ptr		= ptr+(dlen*2);
						for(i=0;i<dlen;i++){
							sed_printf1("data[%d]=0x%x(%d)\n",i,ptr[i],ptr[i]);
						}
#if 1
                    	status = writeOTP( otp_ary,dlen,ptr,&rspLen);
#endif
					}
                }else
                    status = STATUS_COMM_ERR;

                break;

                // DES related
            case CMD_DES_SET_KEY:   //0x10
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = desSetKey(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_DES_SET_DATA:  //0x11
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = desSetData(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_DES_ENCRYPT:   //0x12
                status = desEncrypt(rspBuf, &rspLen);
                break;
            case CMD_DES_DECRYPT:   //0x13
                status = desDecrypt(rspBuf, &rspLen);
                break;

                // TDES related
            case CMD_TDES_SET_KEY:  //0x20
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = tdesSetKey(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_TDES_SET_DATA: //0x21
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = tdesSetData(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_TDES_ENCRYPT:  //0x22
                status = tdesEncrypt(rspBuf, &rspLen);
                break;
            case CMD_TDES_DECRYPT:	//0x23
                status = tdesDecrypt(rspBuf, &rspLen);
                break;

                // AES related
            case CMD_AES_SET_KEY:   //0x30
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = aesSetKey(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_AES_SET_DATA:  //0x31
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = aesSetData(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_AES_ENCRYPT:   //0x32
                status = aesEncrypt(rspBuf, &rspLen);
                break;
            case CMD_AES_DECRYPT:   //0x33
                status = aesDecrypt(rspBuf, &rspLen);
                break;

                // RSA related
            case CMD_RSA_SET_KEY:   //0x40
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = rsaSetKey(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_RSA_SET_DATA:  //0x41
                if (serial_recv_buffer(cmdBuf, cmdLen) == STATUS_OK)
                    status = rsaSetData(cmdBuf, cmdLen);
                else
                    status = STATUS_COMM_ERR;
                break;
            case CMD_RSA_ENCRYPT:   //0x42
                status = rsaEncrypt(rspBuf, &rspLen);
                break;
            case CMD_RSA_DECRYPT:   //0x43
                status = rsaDecrypt(rspBuf, &rspLen);
                break;

            default:
                status = STATUS_NOT_IMPLEMENTED;
                break;
            }

            // Send the response
            serial_send_uint16_t(rspLen + 1);
            serial_send(status);
            serial_send_buffer(rspBuf, rspLen);
        } else {
            //serial_send_uint16_t(1);
            //serial_send(STATUS_ERROR);
        }
    }
}



#if 0
Dear Cristofaro

Have good day.

When the last time you visit, you mentioned the need Riscure API, an run at SRAM, another run on the DDR .
Do you want it to run by SCPU (arm) or KCPU (mips) about API running on DDR?  Or indifferent?

Thanks
Alex Liao

===================================
tftp 0x00108000 ap_template.bin
go c 0xa0108000


tftp 0x00020000 ap_template.bin
go c 0xa0020000

#endif
