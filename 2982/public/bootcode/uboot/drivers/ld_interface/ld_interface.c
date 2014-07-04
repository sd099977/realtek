#include <common.h>
//#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/rbusLD_InterfaceReg.h>
#include <asm/arch/ld_interface.h>
//#include <platform_lib/board/lsadc.h>
#include <asm/arch/io.h>

/*========================Functions===============================*/


void ld_Init(void)
{
		ld_interface_out_data_ctrl_RBUS  ld_interface_out_data_ctrl_reg;
		ld_interface_timing_ctrl_RBUS ld_interface_timing_ctrl_reg;
		ld_interface_send_delay_RBUS ld_interface_send_delay_reg;
		ld_interface_data_unit_delay_RBUS ld_interface_data_unit_delay_reg;
		ld_interface_v_sync_duty_RBUS  ld_interface_v_sync_duty_reg;
		ld_interface_data_h_time_RBUS 	ld_interface_data_h_time_reg;
		ld_interface_ld_ctrl_RBUS ld_interface_ld_ctrl_reg;


		ld_interface_out_data_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_OUT_DATA_CTRL_VADDR);
		ld_interface_out_data_ctrl_reg.data_endian = 1;
		ld_interface_out_data_ctrl_reg.output_data_format = 2;
		ld_interface_out_data_ctrl_reg.output_units = 0;
		rtd_outl(LD_INTERFACE_OUT_DATA_CTRL_VADDR, ld_interface_out_data_ctrl_reg.regValue);

		ld_interface_timing_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_TIMING_CTRL_VADDR);
		ld_interface_timing_ctrl_reg.sck_h = 0xff;
		ld_interface_timing_ctrl_reg.sck_l = 0xff;
		rtd_outl(LD_INTERFACE_TIMING_CTRL_VADDR,ld_interface_timing_ctrl_reg.regValue);

		ld_interface_send_delay_reg.regValue = rtd_inl(LD_INTERFACE_SEND_DELAY_VADDR);
		ld_interface_send_delay_reg.data_send_delay = 0x6c8;
		rtd_outl(LD_INTERFACE_SEND_DELAY_VADDR, ld_interface_send_delay_reg.regValue);

		ld_interface_data_unit_delay_reg.regValue = rtd_inl(LD_INTERFACE_DATA_UNIT_DELAY_VADDR);
		ld_interface_data_unit_delay_reg.each_unit_delay = 0;
		rtd_outl(LD_INTERFACE_DATA_UNIT_DELAY_VADDR, ld_interface_data_unit_delay_reg.regValue);

		ld_interface_v_sync_duty_reg.regValue = rtd_inl(LD_INTERFACE_V_SYNC_DUTY_VADDR);
		ld_interface_v_sync_duty_reg.vsync_d = 0xff;
		ld_interface_v_sync_duty_reg.hsync_d = 0;
		rtd_outl(LD_INTERFACE_V_SYNC_DUTY_VADDR,ld_interface_v_sync_duty_reg.regValue);

		ld_interface_data_h_time_reg.regValue = rtd_inl(LD_INTERFACE_DATA_H_TIME_VADDR);
		ld_interface_data_h_time_reg.data_hold_time = 0xff;//0x1fd;
		rtd_outl(LD_INTERFACE_DATA_H_TIME_VADDR,ld_interface_data_h_time_reg.regValue);

		ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
		ld_interface_ld_ctrl_reg.ld_mode = LD_AS_MODE;
		ld_interface_ld_ctrl_reg.start_enable = 0;
		ld_interface_ld_ctrl_reg.send_trigger = 0;
		ld_interface_ld_ctrl_reg.ld_pin_port_sel = 1;
		ld_interface_ld_ctrl_reg.send_follow_vsync = 0;
		rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);

}

int ld_Write(unsigned int* data, unsigned int length,LD_WRITE_MODE mode)
{
	ld_interface_ld_ctrl_RBUS ld_interface_ld_ctrl_reg;
	ld_interface_out_data_ctrl_RBUS  ld_interface_out_data_ctrl_reg;
	ld_interface_as_wr_ctrl_RBUS ld_interface_as_wr_ctrl_reg;
	unsigned int  i = 0;
	unsigned int timeoutcount = 0;

	printf("\n ld_Write !!! \n");

	rtd_outl(LD_INTERFACE_OUTINDEX_ADDR_CTRL_VADDR,0x00000000);  //Reset OUT Inedx addr
	for(i=0;i<length;i++)
		rtd_outl(LD_INTERFACE_OUTINDEX_RWPORT_VADDR,i);  //OUT Inedx RW port

	rtd_outl(LD_INTERFACE_DATA_ADDR_CTRL_VADDR,0x00000000);  //Reset Data addr
	for(i=0;i<length;i++)
		rtd_outl(LD_INTERFACE_DATA_RWPORT_VADDR,*(data+i));

	ld_interface_out_data_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_OUT_DATA_CTRL_VADDR);
	ld_interface_out_data_ctrl_reg.output_units = (length-1); // data units
	rtd_outl(LD_INTERFACE_OUT_DATA_CTRL_VADDR, ld_interface_out_data_ctrl_reg.regValue);

	ld_interface_as_wr_ctrl_reg.regValue = rtd_inl(	LD_INTERFACE_AS_WR_CTRL_VADDR);
	ld_interface_as_wr_ctrl_reg.rwcmd = 0;
	ld_interface_as_wr_ctrl_reg.rw_cmd_sel = 0;
	ld_interface_as_wr_ctrl_reg.rw_bit_sent_sel = 0;
	rtd_outl(LD_INTERFACE_AS_WR_CTRL_VADDR,ld_interface_as_wr_ctrl_reg.regValue);

	ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
	ld_interface_ld_ctrl_reg.start_enable = 1;
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);

	ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
	if(mode == LD_WRITE_MODE_FOLLOW_VSYNC){
		printf("\n ld_Write LD_WRITE_MODE_FOLLOW_VSYNC !!! \n");

		ld_interface_ld_ctrl_reg.send_follow_vsync = 1;
	}else{
		printf("\n ld_Write  LD_WRITE_MODE_NOT_FOLLOW_VSYNC!!! \n");

		ld_interface_ld_ctrl_reg.send_follow_vsync = 0;
		ld_interface_ld_ctrl_reg.send_trigger = 1;
	}
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);


	if(mode == LD_WRITE_MODE_FOLLOW_VSYNC)
		mdelay(30);	// wait v-sync occurt
	else{


		timeoutcount = 0x7ffff;
		do {
			ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
			if(ld_interface_ld_ctrl_reg.send_trigger == 0) {
				break;
			}
		} while(timeoutcount-- != 0);

		if(timeoutcount == 0)
			printf("\n local dimming Write Error !!!\n ");

		ld_interface_ld_ctrl_reg.start_enable = 0;
		rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);	// disable local dimming interface
	}


	return 0;
}

#if 0 // cklai@mark unused code
unsigned int ld_Read(unsigned int addr)
{
	ld_interface_ld_ctrl_RBUS ld_interface_ld_ctrl_reg;
	ld_interface_out_data_ctrl_RBUS  ld_interface_out_data_ctrl_reg;
	ld_interface_as_wr_ctrl_RBUS ld_interface_as_wr_ctrl_reg;
	ld_interface_rx_dataw0_RBUS ld_interface_rx_dataw0_reg;
	ld_interface_rx_dataw1_RBUS ld_interface_rx_dataw1_reg;
	unsigned int  i = 0, ReadData = 0;
	unsigned int timeoutcount = 0;

	printf("\n ld_Read !!! \n");

	ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
	ld_interface_ld_ctrl_reg.start_enable = 0;
	ld_interface_ld_ctrl_reg.send_trigger = 0;
	ld_interface_ld_ctrl_reg.send_follow_vsync = 0;
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);	// disable local dimming interface

	rtd_outl(LD_INTERFACE_OUTINDEX_ADDR_CTRL_VADDR,0x00000000);  //Reset OUT Inedx addr
	rtd_outl(LD_INTERFACE_OUTINDEX_RWPORT_VADDR,0x00);  //OUT Inedx RW port
	rtd_outl(LD_INTERFACE_OUTINDEX_RWPORT_VADDR,0x01);

	rtd_outl(LD_INTERFACE_DATA_ADDR_CTRL_VADDR,0x00000000);  //Reset Data addr
	rtd_outl(LD_INTERFACE_DATA_RWPORT_VADDR,addr);
	rtd_outl(LD_INTERFACE_DATA_RWPORT_VADDR,0x00);

	ld_interface_out_data_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_OUT_DATA_CTRL_VADDR);
	ld_interface_out_data_ctrl_reg.output_units = 1; // data units
	rtd_outl(LD_INTERFACE_OUT_DATA_CTRL_VADDR, ld_interface_out_data_ctrl_reg.regValue);

	ld_interface_as_wr_ctrl_reg.regValue = rtd_inl(	LD_INTERFACE_AS_WR_CTRL_VADDR);
	ld_interface_as_wr_ctrl_reg.rwcmd = 1;
	ld_interface_as_wr_ctrl_reg.rw_cmd_sel = 1;
	ld_interface_as_wr_ctrl_reg.rw_bit_sent_sel = 1;
	rtd_outl(LD_INTERFACE_AS_WR_CTRL_VADDR,ld_interface_as_wr_ctrl_reg.regValue);

	ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
	ld_interface_ld_ctrl_reg.start_enable = 1;
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);	// enable local dimming


	ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
	ld_interface_ld_ctrl_reg.send_follow_vsync = 0;
	ld_interface_ld_ctrl_reg.send_trigger = 1;
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);

	timeoutcount = 0x7ffff;
	do {
		ld_interface_ld_ctrl_reg.regValue = rtd_inl(LD_INTERFACE_LD_CTRL_VADDR);
		if(ld_interface_ld_ctrl_reg.send_trigger == 0) {
			break;
		}
	} while(timeoutcount-- != 0);

	if(timeoutcount == 0)
		printf("\n local dimming Read Error !!!\n ");

	ld_interface_ld_ctrl_reg.start_enable = 0;
	rtd_outl(LD_INTERFACE_LD_CTRL_VADDR, ld_interface_ld_ctrl_reg.regValue);	// disable local dimming interface

	ld_interface_rx_dataw0_reg.regValue = rtd_inl(LD_INTERFACE_RX_DATAW0_VADDR);
	ReadData =  (ld_interface_rx_dataw0_reg.regValue >> 16 ) & 0xffff;

	return ReadData;
}
#endif

