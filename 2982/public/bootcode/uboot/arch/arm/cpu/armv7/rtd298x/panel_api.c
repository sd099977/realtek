#include <common.h>
#include <asm/arch/panel_config_parameter.h>
#include <rbusPpOverlayReg.h>
#include <crt_sys_reg.h>
#include <rbusPinmuxReg.h>
#include <rbusPifReg.h>
#include <rbusSfgReg.h>
#include <rbusVby1Reg.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pcb.h>
#include <asm/io.h>
#include <bootparam.h>
#include <asm/arch/factorylib.h>
#include <panel.h>
#include <asm/arch/rbus/rbusLD_InterfaceReg.h>
#include <asm/arch/ld_interface.h>
#include <rtk_g2c_lib.h>
#include <asm/arch/fw_info.h>
#include <rtk_i2c_lib.h>



extern struct _PANEL_CONFIG_PARAMETER  default_panel_parameter;

static void  panel_vby1_custom_setting(void);
static void  panel_epi_custom_setting(void);
static void  panel_lvds_custom_setting(void);
//Tcon Control Api
unsigned char panel_Tcon_PA168_Enable(void);
void PA168_i2c_cmd(void);
void Millet4_i2c_cmd(void);
#if defined(CONFIG_PANEL_SHARP_NT71912_MEMC)
void Sharp_NT71912_i2c_cmd(void);
#endif

//////////////////////// Panel Interface Related Cunstomized Setting ////////////////////////////////////////

/*************************** Please Be Note The Following Rule ************************************
/////////////////////////////////////////////////////////////////////////////////////////////
The register address of panel interface  TXPHY between  0xb800_0C00 ~ 0xb800_0CC8,
only the follwing are allow to be modify, if your changes are out of this range, please contact with
dick0329@realtek.com, or yungfanmu@realtek.com first.

Allowed Modify Registers:
---------------------------------------------------------------------------------------------
0xb800_0c00[31:20][18:7]
0xb800_0c04[31:20][18:7]
0xb800_0c0c[27:26][25:18]
0xb800_0c10[25:24][18:17]
0xb800_0c14[25:24][18:17]
0xb800_0c18[25:24][18:17]
0xb800_0c1c[25:24][18:17]
0xb800_0c20[25:24][18:17]
0xb800_0c24[25:24][18:17]
0xb800_0c28[25:24][18:17]
0xb800_0c2c[25:24][18:17]
0xb800_0c30[26:19]
0xb800_0c34[25:24][18:17]
0xb800_0c38[25:24][18:17]
0xb800_0c3c[25:24][18:17]
0xb800_0c40[25:24][18:17]
0xb800_0c44[25:24][18:17]
0xb800_0c48[25:24][18:17]
0xb800_0c4c[25:24][18:17]
0xb800_0c50[26:19]
0xb800_0c54[25:22][21:17]
0xb800_0c58[12:5]
0xb800_0c60[14:8]
0xb800_0c78[30:23][22:16][15:8][6:0]
0xb800_0c80[23:20]
0xb800_0c84[23:20]
0xb800_0c88[23:20]
0xb800_0c8c[23:20]
0xb800_0c90[23:20]
0xb800_0c94[23:20]
0xb800_0c98[23:20]
0xb800_0c9c[23:20]
0xb800_0ca4[23:20]
0xb800_0ca8[23:20]
0xb800_0cac[23:20]
0xb800_0cb0[23:20]
0xb800_0cb4[23:20]
0xb800_0cb8[23:20]
0xb800_0cbc[23:20]
0xb800_0cc4[24]

*********************************************************************************************/

void panel_customized_setting(void)
{
	printf("=== Panel Index : %x ===\n", default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX);

	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		panel_vby1_custom_setting();
	}
	else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		panel_epi_custom_setting();
	}
	else{
		panel_lvds_custom_setting();
	}

}

static void  panel_vby1_custom_setting(void)
{
}

static void  panel_epi_custom_setting(void)
{
	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_EPI_LG_47_ART5){
		sfg_ctrl_0_RBUS    sfg_ctrl_0_reg;
		// enable h flip
		sfg_ctrl_0_reg.regValue = rtd_inl(SFG_SFG_CTRL_0_VADDR);
		sfg_ctrl_0_reg.h_flip_en = 1;
		rtd_outl(SFG_SFG_CTRL_0_VADDR, sfg_ctrl_0_reg.regValue);
	}
}

static void  panel_lvds_custom_setting(void)
{

}

//////////////////////// END of Panel Interface Related Cunstomized Setting ////////////////////////////////////////



//////////////////////// Panel TCON I2C Cunstomized Setting ////////////////////////////////////////


UINT8 panel_tcon_i2c_control(void)
{
	// PA168 init via I2C command
	if(panel_Tcon_PA168_Enable()){
		mdelay(500);  // wait TCON ready //500ms
		PA168_i2c_cmd(); // PA168 init via I2C command
	}else if(Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES()){
		mdelay(500);  // wait TCON ready //500ms
		if((default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_4k2k) ||
			(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k)){
			//Millet4_i2c_cmd();
			Millet4_INX8903_i2c_cmd();
		}
	}
#if defined(CONFIG_PANEL_SHARP_NT71912_MEMC)
	else
		Sharp_NT71912_i2c_cmd();
#endif

	return 1;
}

// PixelWorks PA168 MEMC control
#define PA168_I2C_SLAVE_ID			(0x22 >> 1)	// 1 bit R-shift for Darwin I2C bug?
#define PA168_I2C_CMD_LVDS_FMT	(0x18)
// PixelWorks PA168 4k2k TCON control
typedef enum _PA168_LVDS_INPUT_FMT{
	LVDS_FMT_8BIT_JEIDA	= 0,
	LVDS_FMT_8BIT_VESA	= 1,
	LVDS_FMT_10BIT_JEIDA	= 2,
	LVDS_FMT_10BIT_VESA	= 3,
	LVDS_FMT_10BIT_MIX	= 4
}PA168_LVDS_INPUT_FMT;

void PA168_i2c_cmd(void)
{
#ifdef CONFIG_REALTEK_I2C
//	unsigned long long value=0;
	UINT8 msg[2];

	G2C_Init(0x3);

	msg[0] = PA168_I2C_CMD_LVDS_FMT;
	msg[1] = LVDS_FMT_10BIT_VESA; //
	G2C_Write_EX(3, PA168_I2C_SLAVE_ID, 0, 0, 2, msg);
#endif

	printf("[PA168] Send I2C command!\n");

	return;
}

unsigned char panel_Tcon_PA168_Enable(void)
{

	if((default_panel_parameter.iCONFIG_PANEL_TYPE == 2) && (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_PA168_AU_55))
		return 1;

	return 0;
}

static unsigned long long m_TCON_I2C_MASTER = 4;

void Millet4_i2c_cmd(void)
{
	static unsigned long long m_TCON_I2C_DEVICE_ADDR = 0x65;	//millet4 slave address

	UINT8 TCON_MILLET4_I2C_CMD_TABLE[2][1][9] =
	{
		{
			// 2k1k120
			{0x26, 0x38, 0x50, 0x6e, 0x00, 0x00, 0x10, 0x00, 0x01},
		},
		{
			// 4k2k30
			{0x26, 0x38, 0x50, 0x6e, 0x00, 0x00, 0x10, 0x00, 0x03},
		}
	};

	printf("Millet4_i2c_cmd\n");

	G2C_Init(m_TCON_I2C_MASTER);

	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k){
		printf("mode 2k1k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE));
	}else if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_4k2k){
		printf("mode 4k2k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE+9));
	}


}


void Millet4_INX8903_i2c_cmd(void)
{
	static unsigned long long m_TCON_I2C_DEVICE_ADDR = 0x1C;	//millet4 slave address
	int i=0;

	UINT8 TCON_IN8903_I2C_CMD_TABLE[2][10][7] =
	{
		{
			// 2k1k120
			{0x80, 0x01, 0x02, 0x00, 0x00, 0x55, 0x00},
			{0x80, 0x02, 0x00, 0x00, 0x02, 0x01, 0x03},
			{0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
			//CDR Training
			{0x23, 0x1B, 0x10, 0x27, 0xC2, 0xEE, 0xD0},
			{0x33, 0x1B, 0x10, 0x27, 0x40, 0x71, 0xD0},
			{0x33, 0x1B, 0x10, 0x27, 0xC3, 0xEE, 0xD0},
			// 2k1k120
			{0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00},
			{0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
			//new cmd
			{0x33, 0x1c, 0x13, 0x00, 0x04, 0x40, 0x40},
			{0x33, 0x1c, 0x13, 0x00, 0x04, 0x00, 0x40},
		},
		{
			// 4k2k30
			{0x80, 0x01, 0x02, 0x00, 0x00, 0x55, 0x00},
			{0x80, 0x02, 0x00, 0x00, 0x02, 0x01, 0x03},
			{0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},			
			//CDR Training
			{0x23, 0x1B, 0x10, 0x27, 0xC2, 0xEE, 0xD0},
			{0x33, 0x1B, 0x10, 0x27, 0x40, 0x71, 0xD0},
			{0x33, 0x1B, 0x10, 0x27, 0xC3, 0xEE, 0xD0},
			// 2k1k120
			{0xc1, 0x05, 0x0F, 0x00, 0x08, 0x70, 0x00},
			{0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
			//new cmd
			{0x33, 0x1c, 0x13, 0x00, 0x04, 0x40, 0x40},
			{0x33, 0x1c, 0x13, 0x00, 0x04, 0x00, 0x40},
		}

	};

	printf("INX8903_i2c_cmd\n");

	G2C_Init(m_TCON_I2C_MASTER);

	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k){
		printf("mode 2k1k\n");
		for(i=0; i<10; i++){
			G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 7, ((UINT8*) TCON_IN8903_I2C_CMD_TABLE+(i*7)));
			mdelay(10);
		}
	}else if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_4k2k){
		printf("mode 4k2k\n");		
		for(i=0; i<10; i++){
			G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 7, ((UINT8*) TCON_IN8903_I2C_CMD_TABLE+(70+i*7)));			
			mdelay(10);
		}
	}
}

#if defined(CONFIG_PANEL_SHARP_NT71912_MEMC)

#define NT71912_ADDR 0x1a
void Sharp_NT71912_I2C_CFG_UNLOCK(void)
{
	unsigned char UNLOCK1[2] = { 0xFE, 0x31};
	unsigned char UNLOCK2[2] = { 0xFF, 0x72};

	I2C_Write_EX(1, NT71912_ADDR, 2, ((UINT8*) UNLOCK1));
	I2C_Write_EX(1, NT71912_ADDR, 2, ((UINT8*) UNLOCK2));
}

bool Sharp_NT71912_I2C_FRC_INIT_STATE_CHECK(void)
{
	unsigned char FRC_INIT_STATE_CHECK[5] = { 0x08, 0x5c, 0x01, 0x0A, 0x9F};
	unsigned char I2C_FRC_STATUS[4] = {0, 0, 0, 0};
	unsigned char w_data = 0;

	w_data = 0x0C;
	I2C_Write_EX(1, NT71912_ADDR, 5, ((UINT8*) FRC_INIT_STATE_CHECK));
	if(S_OK != I2C_Read_EX(1, NT71912_ADDR, 1, &w_data, 4, I2C_FRC_STATUS))
	{
		printf("Panel_I2C_FRC_STATE_STATUS_CHECK read NG\n");
		return false;
	}

	if(I2C_FRC_STATUS[0] != 0x01) return false;
	else	return true;
}

bool Sharp_NT71912_I2C_FIFO_STATUS_CHECK(void)
{
	unsigned char FIFO_CHECK[5] = { 0x08, 0x20, 0x01, 0x0A, 0x9F};
	unsigned char READ_FIFO_STATUS[4] = {0, 0, 0, 0};
	unsigned char w_data = 0;
	int i = 0;

	w_data = 0x0C;
	I2C_Write_EX(1, NT71912_ADDR, 5, ((UINT8*) FIFO_CHECK));
	if(S_OK != I2C_Read_EX(1, NT71912_ADDR, 1, &w_data, 4, READ_FIFO_STATUS))
	{
		printf("Panel_I2C_FIFO_STATUS_CHECK read NG\n");
		return false;
	}

	for(i=0; i<4; i++)
	{
		if(READ_FIFO_STATUS[i] != 0xFF) return false;
	}

	return true;
}

bool Sharp_NT71912_I2C_STATUS_CHECK(void)
{
	unsigned char STATUS_CHECK[5] = { 0x08, 0x24, 0x01, 0x0A, 0x9F};
	unsigned char I2C_STATUS[4] = {0, 0, 0, 0};
	unsigned char w_data = 0;

	w_data = 0x0C;
	I2C_Write_EX(1, NT71912_ADDR, 5, ((UINT8*) STATUS_CHECK));
	if(S_OK != I2C_Read_EX(1, NT71912_ADDR, 1, &w_data, 4, I2C_STATUS))
	{
		printf("Panel_I2C_STATUS_CHECK read NG\n");
		return false;
	}

	if(I2C_STATUS[0] != 0x01) return false;
	else	return true;
}

bool Sharp_NT71912_I2C_ROM_REVISON(UINT32* nDate, UINT32* nInfor)
{
	unsigned char PANEL_ROM_REVISION1_CMD[5] = { 0x08, 0xf0, 0xff, 0x00, 0x00};
	unsigned char PANEL_ROM_REVISION2_CMD[5] = { 0x08, 0xf8, 0xff, 0x00, 0x00};
	unsigned char I2C_INFORMATION_STATUS[4] = {0, 0, 0, 0};
	unsigned char w_data = 0;

	w_data = 0x0C;
	I2C_Write_EX(1, NT71912_ADDR, 5, ((UINT8*) PANEL_ROM_REVISION1_CMD));
	if(S_OK != I2C_Read_EX(1, NT71912_ADDR, 1, &w_data, 4, I2C_INFORMATION_STATUS)) {
		printf("PANEL_ROM_REVISION1_CMD read NG\n");
		return false;
	}
	*nDate = I2C_INFORMATION_STATUS[0];
	*nDate = (*nDate << 8) | I2C_INFORMATION_STATUS[1];
	*nDate = (*nDate << 8) | I2C_INFORMATION_STATUS[2];
	*nDate = (*nDate << 8) | I2C_INFORMATION_STATUS[3];
	mdelay(5);

	w_data = 0x0C;
	I2C_Write_EX(1, NT71912_ADDR, 5, ((UINT8*) PANEL_ROM_REVISION2_CMD));
	if(S_OK != I2C_Read_EX(1, NT71912_ADDR, 1, &w_data, 4, I2C_INFORMATION_STATUS)) {
		printf("PANEL_ROM_REVISION2_CMD read NG\n");
		return false;
	}

	*nInfor = I2C_INFORMATION_STATUS[0];
	*nInfor = (*nInfor << 8) | I2C_INFORMATION_STATUS[1];
	*nInfor = (*nInfor << 8) | I2C_INFORMATION_STATUS[2];
	*nInfor = (*nInfor << 8) | I2C_INFORMATION_STATUS[3];

	return true;
}

void Sharp_NT71912_i2c_cmd(void)
{
	#define PANEL_WAIT_TIME 10

	int i = 0;
	unsigned char PANEL_MUTE_OFF[9] = { 0x00, 0x20, 0x01, 0x0A, 0x9F, 0x00, 0x00, 0x00, 0x00};
	unsigned char PANEL_BACKLIGHT_ON[9] = { 0x00, 0x20, 0x01, 0x0A, 0x9F, 0xEF, 0x10, 0x31, 0x05};
	UINT32 nDateInformaiton, nSpecInformation;
//	int nYear, nMonth, nDay, nInch, nPanelInfo, nVer;

	printf("Sharp_NT71912_i2c_cmd\n");

	// CFG Unlock
	Sharp_NT71912_I2C_CFG_UNLOCK();

	mdelay(5);
	if(Sharp_NT71912_I2C_ROM_REVISON(&nDateInformaiton, &nSpecInformation) == true) {
//		nYear = (nDateInformaiton & 0xffff0000) >> 16;
//		nMonth = (nDateInformaiton & 0x0000ff00) >> 8;
//		nDay = (nDateInformaiton & 0x000000ff);
//		nInch = (nSpecInformation & 0xff000000) >> 24;
//		nPanelInfo = (nSpecInformation & 0x00ffff00) >> 8;
//		nVer = (nSpecInformation & 0x000000ff);
		printf("ROM_REVISON: Date: 0x%x, Information: 0x%x\n", nDateInformaiton, nSpecInformation);
//		printf("Date: %d/%d/%d\n", nYear, nMonth, nDay);
//		printf("Infomation: inch(%d), Panel(%d), Ver(%d)\n", nInch, nPanelInfo, nVer);
	}

	mdelay(5);
	for(i=0; i<PANEL_WAIT_TIME; i++) {
		if(Sharp_NT71912_I2C_FRC_INIT_STATE_CHECK() == true)
			break;
		else if(i == PANEL_WAIT_TIME -1)
			printf("1.Panel_I2C_FRC_INIT_STATUS_CHECK is NG\n");
		else
			mdelay(100);
	}
	mdelay(5);

	for(i=0; i<PANEL_WAIT_TIME; i++) {
		if(Sharp_NT71912_I2C_FIFO_STATUS_CHECK() == true)
			break;
		else if(i == PANEL_WAIT_TIME -1)
			printf("1.Panel_I2C_FIFO_STATUS_CHECK is NG\n");
		else
			mdelay(100);
	}
	mdelay(5);

	for(i=0; i<PANEL_WAIT_TIME; i++) {
		if(Sharp_NT71912_I2C_STATUS_CHECK() == true)
			break;
		else if(i == PANEL_WAIT_TIME -1)
			printf("1.Panel_I2C_STATUS_CHECK is NG\n");
		else
			mdelay(100);
	}
	mdelay(5);

	// Mute off
	I2C_Write_EX(1, NT71912_ADDR, 9, ((UINT8*) PANEL_MUTE_OFF));
	for(i=0; i<PANEL_WAIT_TIME; i++) {
		if(Sharp_NT71912_I2C_FIFO_STATUS_CHECK() == true)
			break;
		else if(i == PANEL_WAIT_TIME -1)
			printf("2.Panel_I2C_FIFO_STATUS_CHECK is NG\n");
		else
			mdelay(100);
	}
	mdelay(5);

	for(i=0; i<PANEL_WAIT_TIME; i++) {
		if(Sharp_NT71912_I2C_STATUS_CHECK() == true)
			break;
		else if(i == PANEL_WAIT_TIME -1)
			printf("2.Panel_I2C_STATUS_CHECK is NG\n");
		else
			mdelay(100);
	}
	mdelay(5);

	// BL ON
	I2C_Write_EX(1, NT71912_ADDR, 9, ((UINT8*) PANEL_BACKLIGHT_ON));
/*
	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k){
		printf("mode 2k1k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE));
	}else if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_4k2k){
		printf("mode 4k2k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE+9));
	}

*/
}
#endif

////////////////////////END of Panel TCON I2C Cunstomized Setting ////////////////////////////////////////


