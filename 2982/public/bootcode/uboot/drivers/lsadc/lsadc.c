#include <common.h>
#include <asm/arch/rbus/iso_reg.h>
#include <platform_lib/board/lsadc.h>
#include <asm/arch/io.h>

/*========================Functions===============================*/
#if 0 // cklai@mark unused code
void lsadc_last_init(void)
{
	rtd_outl(ST_LSADC_CTRL_reg,0x16100000);  //Digital setting
	rtd_outl(ST_LSADC_CTRL_reg,0x16100001);  //Digital Enable (last enable)
}
#endif

int lsadc_init(int index, int voltage_mode)
{
	st_lsadc_ctrl_RBUS st_lsadc_ctrl_reg;
	st_pad0_RBUS st_pad0_reg;

	if (index >= 8) {
		return -1;
	}
        static int init_once = 0;
        if(init_once==0)
        {
                init_once=1;     
                puts("lsadc_init init keypad:1\n");
                //clken:1
                //rtd_outl(0xb8060040,0x00000027); //clken_iso_padmux[2]:1 clken_iso_misc[0]:1
                //rtd_outl(0xb8060044,0x00000001);//clken_Lsadc[0]:1
		rtd_setbits( 0xb8060040, _BIT2 );
		rtd_setbits( 0xb8060040, _BIT0 );
		rtd_setbits( 0xb8060044, _BIT0 );

                //clken:0
                //rtd_outl(0xb8060040,0x00000027); //clken_iso_padmux[2]:1 clken_iso_misc[0]:1
                //rtd_outl(0xb8060044,0x00000000);//clken_Lsadc[0]:0
		rtd_setbits( 0xb8060040, _BIT2 );
		rtd_setbits( 0xb8060040, _BIT0 );
		rtd_clearbits( 0xb8060044, _BIT0 );

                //RSTN:0
                //rtd_outl(0xb8060030,0x00000027); //rstn_iso_padmux[2]:0 rstn_iso_misc[0]:0
                //rtd_outl(0xb8060034,0x00000000);//rstn_Lsadc[0]:0
		rtd_setbits( 0xb8060030, _BIT2 );
		rtd_setbits( 0xb8060030, _BIT0 );
		rtd_clearbits( 0xb8060034, _BIT0 );

                //RSTN:1
                //rtd_outl(0xb8060030,0x00000027); //rstn_iso_padmux[2]:1 rstn_iso_misc[0]:1
                //rtd_outl(0xb8060034,0x00000001);//rstn_Lsadc[0]:1
		rtd_setbits( 0xb8060030, _BIT2 );
		rtd_setbits( 0xb8060030, _BIT0 );
		rtd_setbits( 0xB8060034, _BIT0 );

                //clken:1
                //rtd_outl(0xb8060040,0x00000027); //clken_iso_padmux[2]:1 clken_iso_misc[0]:1
                //rtd_outl(0xb8060044,0x00000001);//clken_Lsadc[0]:1
		rtd_setbits( 0xb8060040, _BIT2 );
		rtd_setbits( 0xb8060040, _BIT0 );
		rtd_setbits( 0xb8060044, _BIT0 );
                
                udelay(1000);
                
                //pinshare
                //rtd_outl(0xb806020c,0xFB18c630); // LSADCREF,7,6,4,2,1
                //rtd_outl(0xb8060210,0x60000000); // LSADC0
                
                //Lsadc0
                rtd_outl(0xB8061500,0x00000000);
                rtd_outl(0xB8061520,0x16000000);
                rtd_outl(0xB8061524,0x00000000);
                rtd_outl(0xB8061528,0x00011000);
                rtd_outl(0xB806152C,0x00000000);
                udelay(1000);
                //Lsadc1
                rtd_part_outl(0xB8061504,15,12,0x1); //change pad1 source.
                udelay(1000);

                rtd_outl(0xB8061500,0x80000000); //LSADC0, Voltage Mode
                rtd_outl(0xB8061528,0x00010101); //Analog Enable
                rtd_outl(0xB8061520,0x16100000); //Digital setting
                rtd_outl(0xB8061520,0x16100001); //Digital Enable
                
        }
        
#if 0 //Do not disable lsadc module.
	st_lsadc_ctrl_reg.regValue = rtd_inl(ST_LSADC_CTRL_reg);
	if (st_lsadc_ctrl_reg.enable != 0) {
		st_lsadc_ctrl_reg.enable = 0;
		rtd_outl(ST_LSADC_CTRL_reg, st_lsadc_ctrl_reg.regValue);
	}
#endif

	st_pad0_reg.regValue = 0;
	st_pad0_reg.pad0_active = 1;
	st_pad0_reg.pad0_sw = index;

	if (voltage_mode) {	// if voltage mode
		st_pad0_reg.pad0_ctrl = 0;
	}
	else {
		st_pad0_reg.pad0_ctrl = 1;
	}
	
	rtd_outl(ST_PAD0_reg + index * 4, st_pad0_reg.regValue);
	
	return 0;
}


int lsdac_get(int index)
{
	st_lsadc_ctrl_RBUS st_lsadc_ctrl_reg;
	st_pad0_RBUS st_pad0_reg;

	if (index >= 8) {
		return -1;
	}

 
        
	st_lsadc_ctrl_reg.regValue = rtd_inl(ST_LSADC_CTRL_reg);
	if (st_lsadc_ctrl_reg.enable == 0) {
		st_lsadc_ctrl_reg.enable = 1;
		rtd_outl(ST_LSADC_CTRL_reg, st_lsadc_ctrl_reg.regValue);
	}
	//add by keven_yuan begin
	udelay(1000);
	//add by keven_yuan end
	st_pad0_reg.regValue = rtd_inl(ST_PAD0_reg + index * 4);
        printf("%s get value = %d\n", __func__, st_pad0_reg.regValue);

	return st_pad0_reg.adc_val0;
}

