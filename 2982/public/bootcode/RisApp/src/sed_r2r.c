#include "sed_common.h"
#include "sed_drv_gpio.h"
#include "sed_drv_kt.h"
#include "sed_drv_md.h"

/* Support algorithm list */
#define AES		0x0
#define TDES	0x1

#define ENC	0x01
#define DEC	0x10

//#define R2R_CMD_DEBUG
#define R2R_DES_DATA_LEN	8
#define R2R_TDES_DATA_LEN	8
#define R2R_AES_DATA_LEN	16

#ifndef SKIP_SED_FUNC
/* Config usage for KT & MD usage register */
static int sed_cmd_r2r_configuration (
    uint8                   op,
    uint8                   algoId,
    uint32*                 kt_rdkey_usage,
    uint32*                 kt_htkey_usage,
    uint32*                 md_usage,
    uint32*                 md_type
    )
{

#if 0
	uint32 u1 = 0, u2 = 0, u3 = 0;
	uint32 type = MD_DSC_DATATYPE_WRITE_EN2 | MD_DSC_DATATYPE_DSC_M2M_TYPE_DATA;

	switch (algoId)
	{
	case AES:
		u1    = KT_RDKEY_USAGE_CE_AES|KT_RDKEY_USAGE_AES_ECB;
		u2    = KT_HTKEY_USAGE_CE_AES|KT_HTKEY_USAGE_KS_128;
		u3    = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_AES |
                MD_KT_CTRL_WRITE_EN4 | MD_KT_CTRL_MD_KT_AES_MODE_ECB; ;
		type |= MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_AES;
		break;

	case TDES:
		u1    = KT_RDKEY_USAGE_CE_TDES|KT_RDKEY_USAGE_TDES_ECB;
		u2    = KT_HTKEY_USAGE_CE_TDES|KT_HTKEY_USAGE_KS_128;
		u3    = MD_KT_CTRL_WRITE_EN5 | MD_KT_CTRL_MD_KT_CRYPTO_TDES |
                MD_KT_CTRL_WRITE_EN3 | MD_KT_CTRL_MD_KT_TDES_MODE_ECB;
		type |= MD_DSC_DATATYPE_WRITE_EN1 | MD_DSC_DATATYPE_DSC_TYPE_TDES;
		break;

	default:
		return -1;
	}

	if (op == ENC)  {
		u1 |= KT_RDKEY_USAGE_ENC;
		u2 |= KT_HTKEY_USAGE_ENC;
		u3 |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_ENCRYPT;
	} else {
		u1 |= KT_RDKEY_USAGE_DEC;
		u2 |= KT_HTKEY_USAGE_DEC;
		u3 |= MD_KT_CTRL_WRITE_EN2 | MD_KT_CTRL_MD_KT_DECRYPT;
	}

	if (kt_rdkey_usage)
		*kt_rdkey_usage = u1;

	if (kt_htkey_usage)
		*kt_htkey_usage = u2;

	if (md_usage)
		*md_usage = u3;

	if (md_type)
		*md_type = type;

#endif
	return 0;
}

int sed_cmd_r2r_cert_key (uint8 *ibuf, uint8 *obuf)
{
	return 0;
#if 0
	uint8 op = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX);
	uint8 algoId = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 1);
	uint16 dLen = get_cmd_data_len(ibuf) - 2;
	uint32 kt_usage = 0, md_usage = 0, md_type = 0, i;
	uint8 sts = R2R_NO_ERROR;
	uint8 *idata, *odata;

	idata = (uint32 *) 0xa0010000;
	odata  = (uint32 *) 0xa0020000;

	/* Initial buffer */
	for (i = 0; i < 128; i++) {
		idata[i] = 0;
		odata[i] = 0;
	}

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Should we check data in length here ??? */

	GPIO_toggle();


#define NULL		          ((void *)0)

	/* Initialize crypto engine according to algoID */

#ifdef R2R_CMD_DEBUG
	sed_printf("OP: %s\n", (op == ENC)? "ENC": "DEC");
#endif
	if (sed_cmd_r2r_configuration(op, algoId, &kt_usage, NULL, &md_usage, &md_type)) {
		sts = R2R_ERROR_OPERATION_NOT_SUPPORTED;
		goto done;
	}

	/* Config MD */

	REG32(MD_KT_CTRL) = md_usage|KT_CERT_KEY_IDX;

	GPIO_toggle();

	/* Set DataIn to crypto engine data registers */
#ifdef R2R_CMD_DEBUG
	sed_printf("DATA(%d)\n", dLen);
	sed_format_print(&(ibuf[CMD_DATA_IN_IDX + 2]), dLen);
#endif

	/* Handle input data endian order */
	for (i=0; i<dLen;i++)
		idata[i] = ibuf[CMD_DATA_IN_IDX + 2 + i ];

	REG32(MD_DSC_SADDR) = (uint32)(&(idata[0])) & 0x3FFFFFF;
	REG32(MD_DSC_DESTADDR) = (uint32)(&(odata[0])) & 0x3FFFFFF;

	REG32(MD_DSC_TOTLENGTH) = dLen;
	REG32(MD_DSC_HEADERLEN) = 0;
	REG32(MD_DSC_DATATYPE)  = md_type;
	REG32(MD_DSC_CNTL) = MD_DSC_CNTL_DSC_GO;

	GPIO_toggle();

	/* Get Key from key table and set to crypto engine */

	REG32(KT_RDKEY_USAGE) = kt_usage|KT_RDKEY_USAGE_CERT_KEY_IDX|KT_RDKEY_USAGE_EN;
	while(REG32(KT_RDKEY_USAGE) & KT_RDKEY_USAGE_EN);

	GPIO_pulse();

	/* Start cipher */

	REG32(MD_DSC_CNTL) = MD_DSC_CNTL_DSC_GO | MD_DSC_CNTL_WRITE_DATA;

	GPIO_toggle();

	/* Wait cipher done */

	while (!(REG32(MD_DSC_CNTL) & MD_DSC_CNTL_DSC_IDEL));

	GPIO_pulse();

	/* Copy result from crypto engine to CPU internal registers */

	GPIO_toggle();

	/* Copy result from CPU internal registers to response buffer */

	for (i=0; i<dLen;i++)
		obuf[RSP_DATA_OUT_IDX + i] = odata[i];

	GPIO_pulse();

done:
	return sed_command_exit(obuf, C_R2R_CERT_KEY, dLen, sts);
#endif

}

#define R2R_CMD_KEY_LEN		16
#define R2R_DES_KEY_LEN		8
#define R2R_TDES_KEY_LEN	16
#define R2R_AES_KEY_LEN		16


int sed_cmd_r2r_host_key (uint8 *ibuf, uint8 *obuf)
{
	return 0;
#if 0
	uint8 op = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX);
	uint16 dLen=0, kLen;
	uint8 algoId;
	uint32 kt_usage = 0, kt_htkey_usage = 0, md_usage = 0, md_type = 0, i;
	//uint8 idata[128], odata[128];
	uint8 sts = R2R_NO_ERROR;
	uint8 *idata, *odata;

	idata = (uint32 *) 0xa0010000;
	odata  = (uint32 *) 0xa0020000;

	/* Initial buffer */
	for (i = 0; i < 128; i++)
	{
		idata[i] = 0;
		odata[i] = 0;
	}

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Key length in command is 16, padding zero if needed */
	algoId = get_cmd_data_uint8(ibuf, CMD_DATA_IN_IDX + 1 + R2R_CMD_KEY_LEN);

	switch (algoId)
	{
#if 0 //Not support
	case DES:
		kLen = R2R_DES_KEY_LEN;
		dLen = R2R_DES_DATA_LEN;
		break;
#endif

	case TDES:
		kLen = R2R_TDES_KEY_LEN;
		dLen = R2R_TDES_DATA_LEN;
		break;

	case AES:
		kLen = R2R_AES_KEY_LEN;
		dLen = R2R_AES_DATA_LEN;
		break;
	}

	/* Write input parameters value in internal RAM */
	//Already in ibuf...

	GPIO_pulse();

	/* Initialize crypto engine according to algoID */
#ifdef R2R_CMD_DEBUG
	sed_printf("OP: %s\n", (op == ENC)? "ENC": "DEC");
#endif

	if (sed_cmd_r2r_configuration(op, algoId, &kt_usage, &kt_htkey_usage, &md_usage, &md_type)) {
		sts = R2R_ERROR_OPERATION_NOT_SUPPORTED;
		goto done;
	}

	/* Config MD */

	REG32(MD_KT_CTRL) = md_usage | MD_KT_CTRL_WRITE_EN1 | MD_KT_CTRL_MD_KT_KEY_INDEX(KT_HOST_KEY_IDX);

	GPIO_toggle();

	/* Set clear host key to key table */ //TODO: check hostkey endian order
#ifdef R2R_CMD_DEBUG
	sed_printf("KEY(%d)\n", kLen);
	sed_format_print(&(ibuf[CMD_DATA_IN_IDX + 1 + (R2R_CMD_KEY_LEN - kLen)]), dLen);
#endif

	// 1. Update Host Key to KeyTable

#ifdef R2R_CMD_DEBUG
	sed_printf("Load Key to KT\n");
#endif

	REG32(KT_WADR)     = KT_HOST_KEY_IDX;	//0xB8035804

	REG32(KT_HOSTKEY4) = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 1); //[127:96]
	REG32(KT_HOSTKEY3) = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 5); //[95:64]
	REG32(KT_HOSTKEY2) = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 9); //[63:32]
	REG32(KT_HOSTKEY1) = get_cmd_data_uint32(ibuf, CMD_DATA_IN_IDX + 13); //[31:0]

	REG32(KT_HTKEY_USAGE) = kt_htkey_usage;	//0xB8035830

	REG32(KT_HTKEY_USAGE) = kt_htkey_usage|KT_HTKEY_USAGE_VALID;

	while(REG32(KT_HTKEY_USAGE) & KT_HTKEY_USAGE_VALID);

	GPIO_toggle();

    // 2. Load Key from Key Table to DSC
#ifdef R2R_CMD_DEBUG
	sed_printf("Load Key from KT to DSC\n");
#endif

	REG32(KT_RDKEY_USAGE) = kt_usage | KT_RDKEY_USAGE_HOST_KEY_IDX | KT_RDKEY_USAGE_EN;

	while(REG32(KT_RDKEY_USAGE) & KT_RDKEY_USAGE_EN);

	GPIO_toggle();

	/* Set DataIn to crypto engine data registers */

#ifdef R2R_CMD_DEBUG
	sed_printf("DATA(%d)\n", dLen);
	sed_format_print(&(ibuf[CMD_DATA_IN_IDX + 1 + R2R_CMD_KEY_LEN + 1]), dLen);
#endif

	/* Handle input data endian order */
	for (i=0; i<dLen;i++)
		idata[i] = ibuf[CMD_DATA_IN_IDX + 1 + R2R_CMD_KEY_LEN + 1 +i];

	// 3. Call MD to Start Encryption/Decryption

#ifdef R2R_CMD_DEBUG
	sed_printf("Call MD to DSC\n");
#endif

	REG32(MD_DSC_SADDR) = (uint32)(&(idata[0])) & 0x3FFFFFF;
	REG32(MD_DSC_DESTADDR) = (uint32)(&(odata[0])) & 0x3FFFFFF;

	REG32(MD_DSC_TOTLENGTH) = dLen;
	REG32(MD_DSC_HEADERLEN) = 0;
	REG32(MD_DSC_DATATYPE)  = md_type;
	REG32(MD_DSC_CNTL)   = MD_DSC_CNTL_DSC_GO;

#ifdef R2R_CMD_DEBUG
    sed_printf("DSC SADDR=%08lx, DADER=%08lx, TOTLEN=%d, HDRLEN=%d, TYPE=%08lx\n",
        REG32(MD_DSC_SADDR),
        REG32(MD_DSC_DESTADDR),
        REG32(MD_DSC_TOTLENGTH),
        REG32(MD_DSC_HEADERLEN),
        REG32(MD_DSC_DATATYPE));
#endif

	GPIO_pulse();

#ifdef R2R_CMD_DEBUG
    sed_printf("GO\n");
#endif

	REG32(MD_DSC_CNTL) = MD_DSC_CNTL_DSC_GO | MD_DSC_CNTL_WRITE_DATA;

#ifdef R2R_CMD_DEBUG
    sed_printf("Wait Complete\n");
#endif
	while (!(REG32(MD_DSC_CNTL) & MD_DSC_CNTL_DSC_IDEL));
	{
#ifdef R2R_CMD_DEBUG
	    sed_printf("DSC State=%08lx\n", REG32(MD_DSC_CNTL));
#endif
	}

#ifdef R2R_CMD_DEBUG
	sed_printf("DSC Complete\n");
#endif

	GPIO_pulse();

	/* Copy result from crypto engine to CPU internal registers */
	GPIO_toggle();

    // 4. copy output data from CPU internal registers to response buffer

	for (i=0; i<dLen;i++)
		obuf[RSP_DATA_OUT_IDX + i] = odata[i];

	GPIO_toggle();

done:
	return sed_command_exit(obuf, C_R2R_HOST_KEY, dLen, sts);
#endif
}

#endif	//?#ifndef SKIP_SED_FUNC
