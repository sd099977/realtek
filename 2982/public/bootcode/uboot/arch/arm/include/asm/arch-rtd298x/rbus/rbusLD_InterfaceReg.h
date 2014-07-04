#ifndef  __RBUS_LD_INTERFACE_REG_H_
#define  __RBUS_LD_INTERFACE_REG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "rbusTypes.h"

// DEFAULT Register Address

#define LD_INTERFACE_LD_CTRL_VADDR                      	(0xb802c900)
#define LD_INTERFACE_DB_CTRL_VADDR                      	(0xb802c95c)
#define LD_INTERFACE_OUT_DATA_CTRL_VADDR                (0xb802c904)
#define LD_INTERFACE_TIMING_CTRL_VADDR                  	(0xb802c908)
#define LD_INTERFACE_SEND_DELAY_VADDR                   	(0xb802c90c)
#define LD_INTERFACE_DATA_UNIT_DELAY_VADDR              (0xb802c910)
#define LD_INTERFACE_V_SYNC_DUTY_VADDR                  (0xb802c914)
#define LD_INTERFACE_DATA_H_TIME_VADDR                  (0xb802c918)
#define LD_INTERFACE_LD_SPI_V_SYNC_DELAY_VADDR   (0xb802c964)
#define LD_INTERFACE_LD_SPI_H_TOTAL_VADDR               (0xb802c968)
#define LD_INTERFACE_OUTINDEX_ADDR_CTRL_VADDR           (0xb802c91c)
#define LD_INTERFACE_OUTINDEX_RWPORT_VADDR              (0xb802c920)
#define LD_INTERFACE_DATA_ADDR_CTRL_VADDR               (0xb802c924)
#define LD_INTERFACE_DATA_RWPORT_VADDR                  (0xb802c928)
#define LD_INTERFACE_AS_WR_CTRL_VADDR                   (0xb802c92c)
#define LD_INTERFACE_WCLR_CTRL_VADDR                    (0xb802c960)
#define LD_INTERFACE_RX_DATA_CTRL_VADDR                 (0xb802c930)
#define LD_INTERFACE_RX_DATAW0_VADDR                    (0xb802c934)
#define LD_INTERFACE_RX_DATAW1_VADDR                    (0xb802c938)
#define LD_INTERFACE_RX_DATAW2_VADDR                    (0xb802c93c)
#define LD_INTERFACE_RX_DATAW3_VADDR                    (0xb802c940)
#define LD_INTERFACE_RX_DATAW4_VADDR                    (0xb802c944)
#define LD_INTERFACE_RX_DATAW5_VADDR                    (0xb802c948)
#define LD_INTERFACE_RX_DATAW6_VADDR                    (0xb802c94c)
#define LD_INTERFACE_RX_DATAW7_VADDR                    (0xb802c950)
#define LD_INTERFACE_BIST_CTRL0_VADDR                   (0xb802c954)

typedef enum {
	LD_CMO_MODE = 0,
	LD_LGD_MODE,
	LD_AS_MODE,
	LD_FORBIDDEN
}LD_MODE;

typedef enum {
	LD_WRITE_MODE_NOT_FOLLOW_VSYNC = 0,
	LD_WRITE_MODE_FOLLOW_VSYNC	
}LD_WRITE_MODE;


#ifndef LITTLE_ENDIAN	// apply BIG_ENDIAN

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_mode:2;
        RBus_UInt32  res1:20;
        RBus_UInt32  out_data_align:1;
        RBus_UInt32  in_data_align:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  ld_pin_port_sel:1;
        RBus_UInt32  separate_two_block:1;
        RBus_UInt32  send_follow_vsync:1;
        RBus_UInt32  send_trigger:1;
        RBus_UInt32  start_enable:1;
    };
}ld_interface_ld_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  double_buf_en:1;
        RBus_UInt32  double_buf_set:1;
        RBus_UInt32  double_buf_read_level:1;
        RBus_UInt32  res1:29;
    };
}ld_interface_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  data_endian:1;
        RBus_UInt32  res1:17;
        RBus_UInt32  output_units:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  output_data_format:2;
    };
}ld_interface_out_data_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  sck_h:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  sck_l:8;
    };
}ld_interface_timing_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  data_send_delay:24;
        RBus_UInt32  res1:8;
    };
}ld_interface_send_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  each_unit_delay:24;
        RBus_UInt32  res1:8;
    };
}ld_interface_data_unit_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_d:8;
        RBus_UInt32  hsync_d:8;
        RBus_UInt32  res1:16;
    };
}ld_interface_v_sync_duty_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  data_hold_time:9;
        RBus_UInt32  res2:16;
    };
}ld_interface_data_h_time_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_delay:24;
        RBus_UInt32  res1:8;
    };
}ld_interface_ld_spi_v_sync_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_spi_dh_total:13;
        RBus_UInt32  res1:19;
    };
}ld_interface_ld_spi_h_total_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  outindex_rw_pointer_set:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  outindex_rw_pointer:10;
    };
}ld_interface_outindex_addr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  outindex_rw_data_port:10;
    };
}ld_interface_outindex_rwport_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  data_rw_pointer_set:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  data_rw_pointer:10;
    };
}ld_interface_data_addr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  data_rw_data_port:16;
    };
}ld_interface_data_rwport_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  bit_swap:1;
        RBus_UInt32  res2:9;
        RBus_UInt32  rw_bit_sent_sel:1;
        RBus_UInt32  rw_cmd_sel:1;
        RBus_UInt32  rwcmd:1;
        RBus_UInt32  w_package_repeater:4;
    };
}ld_interface_as_wr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rx_done:1;
        RBus_UInt32  rx_done_ld_spi1:1;
        RBus_UInt32  rx_time_out_pending:1;
        RBus_UInt32  rx_ld_spi1_pending:1;
        RBus_UInt32  res1:16;
        RBus_UInt32  cmd_error_status:1;
        RBus_UInt32  res2:11;
    };
}ld_interface_wclr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  time_out_period:8;
        RBus_UInt32  res2:7;
        RBus_UInt32  rx_units:5;
        RBus_UInt32  res3:1;
        RBus_UInt32  rx1_timeout_int_en:1;
        RBus_UInt32  rx0_timeout_int_en:1;
        RBus_UInt32  rx_data_format:1;
    };
}ld_interface_rx_data_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte0:8;
        RBus_UInt32  input_data_byte1:8;
        RBus_UInt32  input_data_byte2:8;
        RBus_UInt32  input_data_byte3:8;
    };
}ld_interface_rx_dataw0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte4:8;
        RBus_UInt32  input_data_byte5:8;
        RBus_UInt32  input_data_byte6:8;
        RBus_UInt32  input_data_byte7:8;
    };
}ld_interface_rx_dataw1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte8:8;
        RBus_UInt32  input_data_byte9:8;
        RBus_UInt32  input_data_byte10:8;
        RBus_UInt32  input_data_byte11:8;
    };
}ld_interface_rx_dataw2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte12:8;
        RBus_UInt32  input_data_byte13:8;
        RBus_UInt32  input_data_byte14:8;
        RBus_UInt32  input_data_byte15:8;
    };
}ld_interface_rx_dataw3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte16:8;
        RBus_UInt32  input_data_byte17:8;
        RBus_UInt32  input_data_byte18:8;
        RBus_UInt32  input_data_byte19:8;
    };
}ld_interface_rx_dataw4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte20:8;
        RBus_UInt32  input_data_byte21:8;
        RBus_UInt32  input_data_byte22:8;
        RBus_UInt32  input_data_byte23:8;
    };
}ld_interface_rx_dataw5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte24:8;
        RBus_UInt32  input_data_byte25:8;
        RBus_UInt32  input_data_byte26:8;
        RBus_UInt32  input_data_byte27:8;
    };
}ld_interface_rx_dataw6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte28:8;
        RBus_UInt32  input_data_byte29:8;
        RBus_UInt32  input_data_byte30:8;
        RBus_UInt32  input_data_byte31:8;
    };
}ld_interface_rx_dataw7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ld_spi_rme_1:1;
        RBus_UInt32  ld_spi_rm_1:4;
        RBus_UInt32  ld_spi_ls_1:1;
        RBus_UInt32  ld_spi_rme_0:1;
        RBus_UInt32  ld_spi_rm_0:4;
        RBus_UInt32  ld_spi_ls_0:1;
        RBus_UInt32  res2:10;
        RBus_UInt32  ld_spi_drf_bist_fail_1:1;
        RBus_UInt32  ld_spi_drf_bist_fail_0:1;
        RBus_UInt32  ld_spi_bist_fail_1:1;
        RBus_UInt32  ld_spi_bist_fail_0:1;
    };
}ld_interface_bist_ctrl0_RBUS;

#else	// apply LITTLE_ENDIAN

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start_enable:1;
        RBus_UInt32  send_trigger:1;
        RBus_UInt32  send_follow_vsync:1;
        RBus_UInt32  separate_two_block:1;
        RBus_UInt32  ld_pin_port_sel:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  in_data_align:1;
        RBus_UInt32  out_data_align:1;
        RBus_UInt32  res1:20;
        RBus_UInt32  ld_mode:2;
    };
}ld_interface_ld_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  double_buf_read_level:1;
        RBus_UInt32  double_buf_set:1;
        RBus_UInt32  double_buf_en:1;
    };
}ld_interface_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_data_format:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  output_units:10;
        RBus_UInt32  res1:17;
        RBus_UInt32  data_endian:1;
    };
}ld_interface_out_data_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sck_l:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  sck_h:8;
        RBus_UInt32  res1:8;
    };
}ld_interface_timing_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  data_send_delay:24;
    };
}ld_interface_send_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  each_unit_delay:24;
    };
}ld_interface_data_unit_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  hsync_d:8;
        RBus_UInt32  vsync_d:8;
    };
}ld_interface_v_sync_duty_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:16;
        RBus_UInt32  data_hold_time:9;
        RBus_UInt32  res1:7;
    };
}ld_interface_data_h_time_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  vsync_delay:24;
    };
}ld_interface_ld_spi_v_sync_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  ld_spi_dh_total:13;
    };
}ld_interface_ld_spi_h_total_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  outindex_rw_pointer:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  outindex_rw_pointer_set:10;
        RBus_UInt32  res1:6;
    };
}ld_interface_outindex_addr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  outindex_rw_data_port:10;
        RBus_UInt32  res1:22;
    };
}ld_interface_outindex_rwport_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  data_rw_pointer:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  data_rw_pointer_set:10;
        RBus_UInt32  res1:6;
    };
}ld_interface_data_addr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  data_rw_data_port:16;
        RBus_UInt32  res1:16;
    };
}ld_interface_data_rwport_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  w_package_repeater:4;
        RBus_UInt32  rwcmd:1;
        RBus_UInt32  rw_cmd_sel:1;
        RBus_UInt32  rw_bit_sent_sel:1;
        RBus_UInt32  res2:9;
        RBus_UInt32  bit_swap:1;
        RBus_UInt32  res1:15;
    };
}ld_interface_as_wr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:11;
        RBus_UInt32  cmd_error_status:1;
        RBus_UInt32  res1:16;
        RBus_UInt32  rx_ld_spi1_pending:1;
        RBus_UInt32  rx_time_out_pending:1;
        RBus_UInt32  rx_done_ld_spi1:1;
        RBus_UInt32  rx_done:1;
    };
}ld_interface_wclr_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rx_data_format:1;
        RBus_UInt32  rx0_timeout_int_en:1;
        RBus_UInt32  rx1_timeout_int_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  rx_units:5;
        RBus_UInt32  res2:7;
        RBus_UInt32  time_out_period:8;
        RBus_UInt32  res1:8;
    };
}ld_interface_rx_data_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte3:8;
        RBus_UInt32  input_data_byte2:8;
        RBus_UInt32  input_data_byte1:8;
        RBus_UInt32  input_data_byte0:8;
    };
}ld_interface_rx_dataw0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte7:8;
        RBus_UInt32  input_data_byte6:8;
        RBus_UInt32  input_data_byte5:8;
        RBus_UInt32  input_data_byte4:8;
    };
}ld_interface_rx_dataw1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte11:8;
        RBus_UInt32  input_data_byte10:8;
        RBus_UInt32  input_data_byte9:8;
        RBus_UInt32  input_data_byte8:8;
    };
}ld_interface_rx_dataw2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte15:8;
        RBus_UInt32  input_data_byte14:8;
        RBus_UInt32  input_data_byte13:8;
        RBus_UInt32  input_data_byte12:8;
    };
}ld_interface_rx_dataw3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte19:8;
        RBus_UInt32  input_data_byte18:8;
        RBus_UInt32  input_data_byte17:8;
        RBus_UInt32  input_data_byte16:8;
    };
}ld_interface_rx_dataw4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte23:8;
        RBus_UInt32  input_data_byte22:8;
        RBus_UInt32  input_data_byte21:8;
        RBus_UInt32  input_data_byte20:8;
    };
}ld_interface_rx_dataw5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte27:8;
        RBus_UInt32  input_data_byte26:8;
        RBus_UInt32  input_data_byte25:8;
        RBus_UInt32  input_data_byte24:8;
    };
}ld_interface_rx_dataw6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_data_byte31:8;
        RBus_UInt32  input_data_byte30:8;
        RBus_UInt32  input_data_byte29:8;
        RBus_UInt32  input_data_byte28:8;
    };
}ld_interface_rx_dataw7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_spi_bist_fail_0:1;
        RBus_UInt32  ld_spi_bist_fail_1:1;
        RBus_UInt32  ld_spi_drf_bist_fail_0:1;
        RBus_UInt32  ld_spi_drf_bist_fail_1:1;
        RBus_UInt32  res2:10;
        RBus_UInt32  ld_spi_ls_0:1;
        RBus_UInt32  ld_spi_rm_0:4;
        RBus_UInt32  ld_spi_rme_0:1;
        RBus_UInt32  ld_spi_ls_1:1;
        RBus_UInt32  ld_spi_rm_1:4;
        RBus_UInt32  ld_spi_rme_1:1;
        RBus_UInt32  res1:6;
    };
}ld_interface_bist_ctrl0_RBUS;


#endif

//extern int lsadc_init(int index, int voltage_mode);
//extern int lsdac_get(int index);

#ifdef __cplusplus
}
#endif
#endif

