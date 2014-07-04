/*============================================================================*\
 * File        : ca_cert.c
 * Description : Reference code for CERT test harness application.
 * Warning     : This code assumes a little endian 32-bit architecture.
 *
 * Classification level: Confidential
 *
 * Copyright (c) 2011 - 2012 Nagravision SA. All rights reserved.
 * NAGRA and NAGRAVISION are registered trademarks of Kudelski SA, 1033 Cheseaux, Switzerland.
 * Confidential and privileged information.
\*============================================================================*/
#include "nocs_bsd_env.h"
#include "print_rpc.h"
#include "nocs_bsd.h"
#include "rtk_bsd.h"
#include "emi.h"

#include "ca_cert.h"
#include "ca_cert_priv.h"
#include "ca_cert_impl.h"

TCertFunctionTable               certTable;
TCertResourceHandle              gCertHandle = 0;

struct SCertResourceHandle      fake_CertHandle;

extern void rtk_show_data(unsigned char ch_line,unsigned int d_len,
                   void* d_buf,unsigned int type_ctl,unsigned char * message );


/*-------------------------------------------------------------------
 * FUNC : certLock
 *
 * DESC : lock the CERT resource
 *
 * PARM : xResourceHandle :   Handle to the CERT resource.
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR
 *-------------------------------------------------------------------*/
static
TCertStatus certLock(TCertResourceHandle*    pxResourceHandle )
{

    BDPRINT_FUNC();

    *pxResourceHandle = &fake_CertHandle;
    return CERT_NO_ERROR;
}


/*-------------------------------------------------------------------
 * FUNC : certUnlock
 *
 * DESC : releases the CERT resource
 *
 * PARM : xResourceHandle :   Handle to the CERT resource.
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR
 *-------------------------------------------------------------------*/
static
TCertStatus certUnlock(TCertResourceHandle     xResourceHandle)
{

	BDPRINT_FUNC();

    if (xResourceHandle != &fake_CertHandle)
    {
        BDPRINT("certUnlock failed, Resource Handle mismatch (%p, %p)\n",
        		 xResourceHandle, &fake_CertHandle);
        return CERT_ERROR_BAD_HANDLE;
    }

    return CERT_NO_ERROR;
}


/*-------------------------------------------------------------------
 * FUNC : _certWaitCommandComplete
 *
 * DESC : wait command complete
 *
 * PARM : xResourceHandle : Handle to the CERT resource.
 *        xNumOfCommands  : Number of commands to be processed by the CERT block.
 *        pxCommands      : Buffer containing xNumOfCommands
 *        pxNumOfProcessedCommands :  Number of commands actually processed by the CERT block.
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR_TIMEOUT / CERT_ERROR
 *-------------------------------------------------------------------*/
static
TCertStatus _certWaitCommandComplete(unsigned long timeout)
{
    unsigned long loop;

    /* per timeout wait 100us */
    loop = timeout*10;

    while(GET_CERT_COMMAND() & CERT_COMMAND_BUSY)
    {
        if(loop){
            loop--;
        }else{
            return CERT_ERROR_TIMEOUT;
        }
        udelay(10);
    }

    return CERT_NO_ERROR;
}

static
const char* cert_status_str(TCertStatus status)
{
    switch(status) {
    case CERT_NO_ERROR:         return "No Error";
    case CERT_ERROR_BAD_HANDLE: return "Error - Bad Handle";
    case CERT_ERROR_BAD_EMI:    return "Error - Bad EMI";
    case CERT_ERROR_BAD_USAGE:  return "Error - Bad Usage";
    case CERT_ERROR_TIMEOUT:    return "Error - Timeout";
    case CERT_ERROR:            return "Error";
    default:                    return "Unknown Error";
    }
}

#if 0
static
void dump_array(const char* title, unsigned char* data, unsigned int len)
{
    if (title)
        printf("%s", title);

    while(len--)
        printf("%02x", *data++);
    printf("\n");

}


static
const char* dump_cert_command(const TCertCommand* pxCommand)
{
    dump_array("cmd.opcode=", pxCommand->opcodes, sizeof(pxCommand->opcodes));
    dump_array("cmd.inputData=", pxCommand->inputData, sizeof(pxCommand->inputData));
    dump_array("cmd.outputData=", pxCommand->outputData, sizeof(pxCommand->outputData));
    dump_array("cmd.status=", pxCommand->status, sizeof(pxCommand->status));
}
#endif

/*-------------------------------------------------------------------
 * FUNC : certExchange
 *
 * DESC : send a series of commands to the CERT block
 *
 * PARM : xResourceHandle : Handle to the CERT resource.
 *        xNumOfCommands  : Number of commands to be processed by the CERT block.
 *        pxCommands      : Buffer containing xNumOfCommands
 *        pxNumOfProcessedCommands :  Number of commands actually processed by the CERT block.
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR_TIMEOUT / CERT_ERROR
 *-------------------------------------------------------------------*/
extern fake_cert_flag;
//static
TCertStatus _certDoCommand(const TCertCommand*     pxCommand)
{

    TCertStatus ret = CERT_NO_ERROR;

    unsigned long  timeout;
    unsigned long* pDIn    = (unsigned long*) pxCommand->inputData;
    unsigned long* pDOut   = (unsigned long*) pxCommand->outputData;
    unsigned long* pCmd    = (unsigned long*) pxCommand->opcodes;
    //unsigned long* pStatus = (unsigned long*) pxCommand->status;
    unsigned long  status;

    BDPRINT_FUNC();

    if (pxCommand==NULL)
    {
        ret = CERT_ERROR;
        goto end_proc;
    }

    if (pxCommand->timeout == CERT_TIMEOUT_DEFAULT)
        timeout = 10;
    else
        timeout = 200;

	if(fake_cert_flag == 0x7878){
		BD_INFO("fake command skip\n");
	}else{
	    if (GET_CERT_STATUS_AKL() & CERT_STATUS_AKL_KEY_OUTPUT_PENDING)
	    {
	        BDPRINT("Key output pending : do fetch key\n");
	        WRITE_REG32(0xb8035804, READ_REG32(0xb8035804) | 0x100);     // Ask Key Table to fetch key

	        udelay(100);
	        status = GET_CERT_STATUS_AKL();
	        BDPRINT("new status : = %08lx\n", status);
	    }

	    BD_INFO("check Command\n");

	    if ((ret = _certWaitCommandComplete(timeout))!=CERT_NO_ERROR)
	    {
	        BD_INFO("command pending\n");
	        goto end_proc;
	    }

	    BD_INFO("write data\n");
	}

	if(1){
		int i;
	    BDPRINT("*pCmd=0x%lx\n",htonl(*pCmd));
		for(i=0; i<8;i++){
			BDPRINT("pDIn[%i] = 0x%08lx\n",i,htonl(pDIn[i]));
		}
	    rtk_show_data(32,32,
                  	(void *)pDIn,TYPE32,
                  	(unsigned char*)"show pDIn");
	}

	if(fake_cert_flag == 0x7878)
	{
		BD_INFO("fake command skip\n");
		pDOut[0] = 0;
	    pDOut[1] = 0;
	    pDOut[2] = 0;
	    pDOut[3] = 0;
	    pDOut[4] = 0;
	    pDOut[5] = 0;
	    pDOut[6] = 0;
	    pDOut[7] = 0;

	    if(*pCmd == 0x1000106){
	    	BD_INFO("last cmd hit!!!\n");
			status = 0x1E000000;
		}else{
			status = 0x1c000000;
		}

		BD_INFO("status = %08lx\n", htonl(status));
	}else{
	    SET_CERT_DATA_IN(0, htonl(pDIn[0]));
	    SET_CERT_DATA_IN(1, htonl(pDIn[1]));
	    SET_CERT_DATA_IN(2, htonl(pDIn[2]));
	    SET_CERT_DATA_IN(3, htonl(pDIn[3]));
	    SET_CERT_DATA_IN(4, htonl(pDIn[4]));
	    SET_CERT_DATA_IN(5, htonl(pDIn[5]));
	    SET_CERT_DATA_IN(6, htonl(pDIn[6]));
	    SET_CERT_DATA_IN(7, htonl(pDIn[7]));
	    SET_CERT_COMMAND(htonl(*pCmd));

	    BD_INFO("wait command complete\n");

	    if ((ret = _certWaitCommandComplete(timeout))!=CERT_NO_ERROR)
	        goto end_proc;

	    status = GET_CERT_STATUS_AKL();

	    BD_INFO("status = %08lx\n", htonl(status));
	    BD_INFO("read data out\n");

	    pDOut[0] = htonl(GET_CERT_DATA_OUT(0));
	    pDOut[1] = htonl(GET_CERT_DATA_OUT(1));
	    pDOut[2] = htonl(GET_CERT_DATA_OUT(2));
	    pDOut[3] = htonl(GET_CERT_DATA_OUT(3));
	    pDOut[4] = htonl(GET_CERT_DATA_OUT(4));
	    pDOut[5] = htonl(GET_CERT_DATA_OUT(5));
	    pDOut[6] = htonl(GET_CERT_DATA_OUT(6));
	    pDOut[7] = htonl(GET_CERT_DATA_OUT(7));

	    status = htonl(status);
	}

    if(1){
    	int i;

		BD_INFO("status = 0x%lx\n",status);

		for(i=0; i<8;i++){
			BDPRINT("pDOut[%i] = 0x%08lx\n",i,pDOut[i]);
		}

		rtk_show_data(32,32,
                  	  (void *)pDOut,TYPE32,
                  	  (unsigned char*)"show CERT pDOut");
	}

    memcpy((void*)pxCommand->status, (void*)&status, 4);

    if (status & CERT_STATUS_AKL_CERT_IP_ERROR)
    {
        ret = CERT_ERROR;
        goto end_proc;
    }
end_proc:

    //CERT_WARNING("CERT Status = %08lx\n", GET_CERT_STATUS_AKL());
    //dump_cert_command(pxCommand);

    if (ret != CERT_NO_ERROR)
    {
        BDPRINT("%s failed, %s\n",__func__,cert_status_str(ret));
    }
    else
    {
        BDPRINT("%s successed\n",__func__);
    }

    return ret;

}



/*-------------------------------------------------------------------
 * FUNC : certExchange
 *
 * DESC : send a series of commands to the CERT block
 *
 * PARM : xResourceHandle : Handle to the CERT resource.
 *        xNumOfCommands  : Number of commands to be processed by the CERT block.
 *        pxCommands      : Buffer containing xNumOfCommands
 *        pxNumOfProcessedCommands :  Number of commands actually processed by the CERT block.
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR_TIMEOUT / CERT_ERROR
 *-------------------------------------------------------------------*/
static TCertStatus certExchange(
    TCertResourceHandle     xResourceHandle,
    size_t                  xNumOfCommands,
    const TCertCommand*     pxCommands,
    size_t*                 pxNumOfProcessedCommands
    )
{
    TCertStatus ret = CERT_NO_ERROR;
    int i;

    BDPRINT_FUNC();

#if 1
    BDPRINT("xResourceHandle=0x%p\n",xResourceHandle);
    BDPRINT("xNumOfCommands=%d\n",xNumOfCommands);
#endif

	//if (xResourceHandle != gCertHandle)
	if (xResourceHandle != &fake_CertHandle)
    {
        //BDPRINT("certExchange failed, Resource Handle mismatch (%08lx, %08lx)\n", xResourceHandle, gCertHandle);
        BDPRINT("certExchange failed, Resource Handle mismatch (0x%p, 0x%p)\n",
        		xResourceHandle, &fake_CertHandle);
        return CERT_ERROR_BAD_HANDLE;
    }

    if (pxNumOfProcessedCommands==NULL || pxCommands==NULL)
    {
        BDPRINT("certExchange failed,Invalid Parameter\n"
        		"	(pxCommands=0x%p, pxNumOfProcessedCommands=0x%p)\n",
                pxCommands, pxNumOfProcessedCommands);
        return CERT_ERROR;
    }

    i = 0;

    BDPRINT("certExchange: xNumOfCommands=%d\n", xNumOfCommands);

    while (i < xNumOfCommands)
    {
        BDPRINT("certExchange: do command =%d/%d\n", i, xNumOfCommands);
#ifdef CONGIG_FAKE_CERT_TEST
		fake_cert_flag = 0x7878;
#else
		fake_cert_flag = 0;
#endif
        ret = _certDoCommand(&pxCommands[i]);
		fake_cert_flag = 0;
        if (ret!=CERT_NO_ERROR)
        {
            BDPRINT("do command (%d/%d) failed=%d(%s)\n",
            		i, xNumOfCommands, ret, cert_status_str(ret));
            break;
        }

        i++;
        BDPRINT("do command complete =%d/%d\n", i, xNumOfCommands);
    }
    *pxNumOfProcessedCommands = i;

    return ret;
}


/*-------------------------------------------------------------------
 * FUNC : certUseEncryptionKey
 *
 * DESC :
 *
 * PARM :
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR_TIMEOUT / CERT_ERROR
 *-------------------------------------------------------------------*/
static TCertStatus certUseEncryptionKey(
	TCertUInt16           	xEmi,
	TCertKeyPathHandle*  	pxKeyPathHandle,
	TCertKeyParity        	xKeyParity
)
{
	BDPRINT_FUNC();
    BDPRINT("certUseEncryptionKey is deprecated and replaced by SECAPI::secUseCertKey()\n");
    return CERT_ERROR;
}



/*-------------------------------------------------------------------
 * FUNC : certUseDecryptionKey
 *
 * DESC :
 *
 * PARM :
 *
 * RET  : CERT_NO_ERROR / CERT_ERROR_BAD_HANDLE / CERT_ERROR_TIMEOUT / CERT_ERROR
 *-------------------------------------------------------------------*/
static TCertStatus certUseDecryptionKey(
	TCertUInt16           	xEmi,
	TCertKeyPathHandle*  	pxKeyPathHandle,
	TCertKeyParity        	xKeyParity
)
{
	BDPRINT_FUNC();
    BDPRINT("certUseDecryptionKey is deprecated and replaced by SECAPI::secUseCertKey()\n");
    return CERT_ERROR;
}



/*-------------------------------------------------------------------
 * FUNC : certGetFunctionTable
 *
 * DESC : return function table of cert block
 *
 * PARM : N/A
 *
 * RET  : NULL : failed, others : handle of Cert Function Table
 *-------------------------------------------------------------------*/
TCertFunctionTable* certGetFunctionTable(void)
{
	BDPRINT_FUNC();

	certTable.certApiVersion    =    CERTAPI_VERSION_INT;
	certTable.certExchange          = &certExchange;
	certTable.certLock              = &certLock;
	certTable.certUnlock            = &certUnlock;
	certTable.certUseDecryptionKey  = &certUseEncryptionKey;
	certTable.certUseEncryptionKey  = &certUseDecryptionKey;

	return &certTable;
}



/*-------------------------------------------------------------------
 * FUNC : cert_operation
 *
 * DESC : performs a single operation on the CERT Common Interface.
 *        Technically, this function is not part of the CERT API.
 *        However, it may be used to implement certExchange above.
 *        It must be implemented as it is used in soccmd.c in socAklXchg
 *        function.
 *
 *        Also refer to description in soclib.h or the TestHarness
 *        documentation
 *
 *        The cert_operation function shall executes a single AKL command by
 *	        1.	wait for AKL idle state
 *	        2.	write cert_data_in the input registers
 *	        3.	write cert_cmd the command register
 *	        4.	wait for completion or timeout. The timeout cert_cmd_maxcycles is specified in CERT block clock cycles and may be converted to a time value.
 *	        5.	read the status register into cert_status
 *	        6.	read the output registers into cert_data_out
 *	        7.	if available return the number of CERT clock cycles for the operation to complete into cmd_cycles.
 *
 *	      CERT_operation may be implemented through certExchange() CERT API call. In which case
 *	        1.	cert_cmd_maxcycles may be mapped to certExchange timeout structure by setting the timeout to CERT_TIMEOUT_DEFAULT when cert_cmd_maxcycles==0 else to CERT_TIMEOUT_OTP.
 *	        2.  The timing return value cmd_cycles may be filled to zero.
 *
 * PARM : x_cmd         : cert command (CU32 = U8[4])
 *        x_cmd_maxcyc  : timeout (in CERT clcok cycle)
 *        x_din_size    : size of input data
 *        xp_din        : input data
 *        x_dout_size   : sizo of output data buffer
 *        xp_dout       : output data buffer
 *        xp_sta        : satus output (CU32 = U8[4])
 *        xp_cmd_cycles : number of cycle executed
 *
 * RET  :
 *-------------------------------------------------------------------*/
/*
int cert_operation(
	CU32                    x_cmd,
	U32                     x_cmd_maxcyc,
	U8                      x_din_size,
	U8*                     xp_din,
	U8                      x_dout_size,
	U8*                     xp_dout,
	CU32                    xp_sta,
	U32*                    xp_cmd_cycles
	)
*/

#if 0
int cert_operation(
	unsigned	x_cmd,
	U32         x_cmd_maxcyc,
	U8          x_din_size,
	U8*         xp_din,
	U8          x_dout_size,
	U8*         xp_dout,
	CU32        xp_sta,
	U32*        xp_cmd_cycles
	)
{
    TCertResourceHandle xResourceHandle;
    TCertCommand        cert_cmd;
    size_t              xNumOfProcessedCommands;
    TCertStatus         ret = CERT_ERROR;

#if 0
    CERT_TRACE();

    if (xp_din==NULL || x_din_size > 32 || xp_dout==NULL || x_dout_size==0 || xp_cmd_cycles==NULL)
    {
        CERT_WARNING("do cert_operation failed, Invalid Parameters\n");
        goto end_proc;
    }

    ret = certLock(&xResourceHandle);

    if (ret != CERT_NO_ERROR)
    {
        CERT_WARNING("do cert_operation failed, Lock Cert failed\n");
        goto end_proc;
    }

    memset(&cert_cmd, 0, sizeof(cert_cmd));

    memcpy(cert_cmd.inputData, xp_din, x_dout_size);

    memcpy(cert_cmd.opcodes, x_cmd, 4);

    cert_cmd.timeout = CERT_TIMEOUT_DEFAULT;

    ret = certExchange(xResourceHandle, 1, &cert_cmd, &xNumOfProcessedCommands);

    certUnlock(xResourceHandle);

    memcpy(xp_dout, cert_cmd.outputData ,x_dout_size);

    memcpy(xp_sta, cert_cmd.status ,4);

    *xp_cmd_cycles = 0;

end_proc:
#endif

	return ret;
}
#endif


