/**
* @file rbusIFD_ANALOGReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2011/12/12
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_IFD_ANALOG_REG_H_
#define _RBUS_IFD_ANALOG_REG_H_

#include "rbusTypes.h"




// IFD_ANALOG_ Register Address

#define IFD_ANALOG_VDAC_BSO_VADDR                 (0xb8033000)
#define IFD_ANALOG_VDAC_VADDR                     (0xb8033004)
#define IFD_ANALOG_VDAC_TV_CTRL1_VADDR            (0xb8033008)
#define IFD_ANALOG_VDAC_TV_CTRL2_VADDR            (0xb803300c)
#define IFD_ANALOG_VDAC_TV_STATUS_VADDR           (0xb8033010)
#define IFD_ANALOG_VDAC_YPP_CTRL1_VADDR           (0xb8033014)
#define IFD_ANALOG_VDAC_YPP_CTRL2_VADDR           (0xb8033018)
#define IFD_ANALOG_VDAC_YPP_CTRL3_VADDR           (0xb803301c)
#define IFD_ANALOG_VDAC_YPP_STATUS_VADDR          (0xb8033020)
#define IFD_ANALOG_VDAC_TV_SRC_SEL_VADDR          (0xb8033024)
#define IFD_ANALOG_IFADC_CTRL1_VADDR              (0xb8033100)
#define IFD_ANALOG_IFADC_CTRL2_VADDR              (0xb8033104)
#define IFD_ANALOG_IFADC_SERVO_VADDR              (0xb8033108)
#define IFD_ANALOG_IFADC_MBIAS_VADDR              (0xb803310c)
#define IFD_ANALOG_IFADC_POW_VADDR                (0xb8033110)
#define IFD_ANALOG_LSADC_RSSI_CTRL_VADDR          (0xb8033200)
#define IFD_ANALOG_LSADC_RSSI_POW_MBIAS_VADDR     (0xb8033204)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======IFD_ANALOG_ register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  reg_vdac_powbuf:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_buf_dcc:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_buf_gain:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_buf_ldv_bias:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_buf_ldv_iq:3;
        RBus_UInt32  res6:2;
        RBus_UInt32  reg_vdac_buf_vcmref_sel:2;
    };
}VDAC_BSO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  reg_vdac_envr:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_powmbias:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_vr15sel:2;
        RBus_UInt32  res4:16;
    };
}VDAC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_vdac_cal75_en_tv:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_draw_en_tv:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_plugin_en_tv:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_vdac_res75_en_tv:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_vdac_res75_sel_tv:1;
        RBus_UInt32  res6:3;
        RBus_UInt32  reg_vdac_res75_setup_tv:5;
        RBus_UInt32  res7:4;
    };
}VDAC_TV_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  reg_vdac_vdac_clkedge_tv:1;
        RBus_UInt32  reg_vdac_vdac_cur_tv:4;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_vdac_en_tv:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_vref_adj_tv:2;
    };
}VDAC_TV_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  reg_vdac_drawout_tv:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_vdac_plugin_tv:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  reg_vdac_rescal_tv:5;
    };
}VDAC_TV_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_vdac_cal75_en:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_vdac_draw_en:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_vdac_plugin_en:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_res75_en:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_res75_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  reg_vdac_vdac_clkedge:3;
        RBus_UInt32  res7:8;
    };
}VDAC_YPP_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_vdac_res75_setup0:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_res75_setup1:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_res75_setup2:5;
        RBus_UInt32  res4:8;
    };
}VDAC_YPP_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_vdac_cur0:4;
        RBus_UInt32  reg_vdac_vdac_cur1:4;
        RBus_UInt32  reg_vdac_vdac_cur2:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_vdac_vdac_en:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_vdac_vref_adj0:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_vref_adj1:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_vdac_vref_adj2:2;
        RBus_UInt32  res5:4;
    };
}VDAC_YPP_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_vdac_rescal0:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_rescal1:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_rescal2:5;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_drawout:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_plugin:3;
    };
}VDAC_YPP_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  reg_vdac_clk_polar:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_vdac_src_sel:3;
    };
}VDAC_TV_SRC_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_adc2x_bg_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_adc2x_ckout_div:2;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_adc2x_ckout_edge:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_adc2x_delay:2;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_adc2x_en_reuse:1;
	 RBus_UInt32  reg_adc2x_fixgain_en:1;
        RBus_UInt32  reg_adc2x_fixgain_ctrl:3;
        RBus_UInt32  res6:2;
        RBus_UInt32  reg_adc2x_ifbw:2;
        RBus_UInt32  res7:3;
        RBus_UInt32  reg_adc2x_insel:1;
    };
}IFADC_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_adc2x_ldo_sel:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_adc2x_pga_cf1:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_adc2x_vref_sel:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_ifcmp_isel:3;
        RBus_UInt32  res5:2;
        RBus_UInt32  reg_ifd_ckin_sel:2;
        RBus_UInt32  reg_ifd_reserved:8;
        RBus_UInt32  res6:4;
    };
}IFADC_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_adc2x_servo2:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_adc2x_svbwc:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_adc2x_svbwr:2;
    };
}IFADC_SERVO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mbias_ifpga:12;
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_mbias_isel:2;
        RBus_UInt32  res2:16;
    };
}IFADC_MBIAS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_adc2x_adcpow:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_adc2x_difpow:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_adc2x_ifpgapow:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_adc2x_meta_pow:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_adc2x_servopow2:1;
        RBus_UInt32  res6:3;
        RBus_UInt32  reg_pow_mbias:1;
        RBus_UInt32  res7:8;
    };
}IFADC_POW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  reg_lsadc_cksel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_lsadc_div:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_rssi_bias:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_rssi_cl:2;
    };
}LSADC_RSSI_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  reg_rssi_lsadc_pow:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_mbias_lsadc:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_mbias_rssi:2;
    };
}LSADC_RSSI_POW_MBIAS_RBUS;





#else //apply LITTLE_ENDIAN


//======IFD_ANALOG_ register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_buf_vcmref_sel:2;
        RBus_UInt32  res6:2;
        RBus_UInt32  reg_vdac_buf_ldv_iq:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_buf_ldv_bias:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_buf_gain:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_buf_dcc:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_powbuf:1;
        RBus_UInt32  res1:11;
    };
}VDAC_BSO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res4:16;
        RBus_UInt32  reg_vdac_vr15sel:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_powmbias:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_envr:1;
        RBus_UInt32  res1:7;
    };
}VDAC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res7:4;
        RBus_UInt32  reg_vdac_res75_setup_tv:5;
        RBus_UInt32  res6:3;
        RBus_UInt32  reg_vdac_res75_sel_tv:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_vdac_res75_en_tv:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_vdac_plugin_en_tv:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_draw_en_tv:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_cal75_en_tv:1;
        RBus_UInt32  res1:3;
    };
}VDAC_TV_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_vref_adj_tv:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_vdac_en_tv:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_vdac_cur_tv:4;
        RBus_UInt32  reg_vdac_vdac_clkedge_tv:1;
        RBus_UInt32  res1:19;
    };
}VDAC_TV_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_rescal_tv:5;
        RBus_UInt32  res3:4;
        RBus_UInt32  reg_vdac_plugin_tv:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_vdac_drawout_tv:1;
        RBus_UInt32  res1:19;
    };
}VDAC_TV_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res7:8;
        RBus_UInt32  reg_vdac_vdac_clkedge:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  reg_vdac_res75_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_res75_en:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_plugin_en:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_vdac_draw_en:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_vdac_cal75_en:3;
        RBus_UInt32  res1:1;
    };
}VDAC_YPP_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res4:8;
        RBus_UInt32  reg_vdac_res75_setup2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_res75_setup1:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_res75_setup0:5;
        RBus_UInt32  res1:3;
    };
}VDAC_YPP_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res5:4;
        RBus_UInt32  reg_vdac_vref_adj2:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_vdac_vref_adj1:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_vdac_vref_adj0:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_vdac_vdac_en:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_vdac_vdac_cur2:4;
        RBus_UInt32  reg_vdac_vdac_cur1:4;
        RBus_UInt32  reg_vdac_vdac_cur0:4;
    };
}VDAC_YPP_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_plugin:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_vdac_drawout:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_vdac_rescal2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_vdac_rescal1:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_vdac_rescal0:5;
        RBus_UInt32  res1:3;
    };
}VDAC_YPP_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_vdac_src_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_vdac_clk_polar:1;
        RBus_UInt32  res1:27;
    };
}VDAC_TV_SRC_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_adc2x_insel:1;
        RBus_UInt32  res7:3;
        RBus_UInt32  reg_adc2x_ifbw:2;
        RBus_UInt32  res6:2;
        RBus_UInt32  reg_adc2x_fixgain_ctrl:3;
	 RBus_UInt32  reg_adc2x_fixgain_en:1;
        RBus_UInt32  reg_adc2x_en_reuse:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_adc2x_delay:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_adc2x_ckout_edge:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_adc2x_ckout_div:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_adc2x_bg_sel:2;
        RBus_UInt32  res1:2;
    };
}IFADC_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res6:4;
        RBus_UInt32  reg_ifd_reserved:8;
        RBus_UInt32  reg_ifd_ckin_sel:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  reg_ifcmp_isel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_adc2x_vref_sel:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_adc2x_pga_cf1:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_adc2x_ldo_sel:2;
        RBus_UInt32  res1:2;
    };
}IFADC_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_adc2x_svbwr:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_adc2x_svbwc:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_adc2x_servo2:3;
        RBus_UInt32  res1:21;
    };
}IFADC_SERVO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:16;
        RBus_UInt32  reg_mbias_isel:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_mbias_ifpga:12;
    };
}IFADC_MBIAS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res7:8;
        RBus_UInt32  reg_pow_mbias:1;
        RBus_UInt32  res6:3;
        RBus_UInt32  reg_adc2x_servopow2:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  reg_adc2x_meta_pow:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_adc2x_ifpgapow:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  reg_adc2x_difpow:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_adc2x_adcpow:1;
        RBus_UInt32  res1:3;
    };
}IFADC_POW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_rssi_cl:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_rssi_bias:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_lsadc_div:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_lsadc_cksel:1;
        RBus_UInt32  res1:19;
    };
}LSADC_RSSI_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mbias_rssi:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_mbias_lsadc:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_rssi_lsadc_pow:1;
        RBus_UInt32  res1:23;
    };
}LSADC_RSSI_POW_MBIAS_RBUS;


#endif




#endif //_RBUS_IFD_ANALOG_REG_H_

