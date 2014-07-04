/**
* @file rbusGammaReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/31
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_GAMMA_REG_H_
#define _RBUS_GAMMA_REG_H_

#include "rbusTypes.h"



//  GAMMA Register Address



#define  GAMMA_GAMMA_PORT_VADDR 		(0xb802c100)
#define  GAMMA_GAMMA_CTRL_1_VADDR 		(0xb802c104)
#define  GAMMA_GAMMA_CTRL_2_VADDR 		(0xb802c108)
#define  GAMMA_GAMMA_SRGB_BIST_CTRL_1_VADDR 		(0xb802c10c)
#define  GAMMA_GAMMA_SRGB_BIST_CTRL_3_VADDR 		(0xb802c114)
#define  GAMMA_ADAPT_GAMMA_VADDR 		(0xb802c120)
#define  GAMMA_DSTAT_CTRL_R_VADDR 		(0xb802c180)
#define  GAMMA_DSTAT_CTRL_G_VADDR 		(0xb802c184)
#define  GAMMA_DSTAT_CTRL_B_VADDR 		(0xb802c188)
#define  GAMMA_DSTAT_O_R1_VADDR 		(0xb802c18c)
#define  GAMMA_DSTAT_O_R2_VADDR 		(0xb802c190)
#define  GAMMA_DSTAT_O_G1_VADDR 		(0xb802c194)
#define  GAMMA_DSTAT_O_G2_VADDR 		(0xb802c198)
#define  GAMMA_DSTAT_O_B1_VADDR 		(0xb802c19c)
#define  GAMMA_DSTAT_O_B2_VADDR 		(0xb802c1a0)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======GAMMA register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  gamma_tab_index:12;
        RBus_UInt32  res2:1;
        RBus_UInt32  gamma_tab_d0:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  gamma_tab_d1:7;
    };
}gamma_port_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  gamma_ax_rw_sel:2;
        RBus_UInt32  gamma_ax_tab_sel:1;
        RBus_UInt32  gamma_ax_ch_sel:2;
        RBus_UInt32  gamma_fifo_empty:1;
        RBus_UInt32  gamma_fifo_full:1;
        RBus_UInt32  gamma_wr_error:1;
        RBus_UInt32  gamma_ax_type_sel:1;
    };
}gamma_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  gamma_tab_size_sel:1;
        RBus_UInt32  gamma_m_tab_sel:2;
        RBus_UInt32  gamma_s_tab_sel:2;
        RBus_UInt32  gamma_overlap:1;
        RBus_UInt32  dummy1802c108_2_0:3;
    };
}gamma_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  ls:1;
        RBus_UInt32  rme:1;
        RBus_UInt32  rm:4;
    };
}gamma_srgb_bist_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  inv_gamma_r_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_g_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_b_drf_bist_fail:1;
        RBus_UInt32  srgb_r_drf_bist_fail:1;
        RBus_UInt32  srgb_g_drf_bist_fail:1;
        RBus_UInt32  srgb_b_drf_bist_fail:1;
        RBus_UInt32  gamma_r_drf_bist_fail:1;
        RBus_UInt32  gamma_g_drf_bist_fail:1;
        RBus_UInt32  gamma_b_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_r_bist_fail:1;
        RBus_UInt32  inv_gamma_g_bist_fail:1;
        RBus_UInt32  inv_gamma_b_bist_fail:1;
        RBus_UInt32  srgb_r_bist_fail:1;
        RBus_UInt32  srgb_g_bist_fail:1;
        RBus_UInt32  srgb_b_bist_fail:1;
        RBus_UInt32  gamma_r_bist_fail:1;
        RBus_UInt32  gamma_g_bist_fail:1;
        RBus_UInt32  gamma_b_bist_fail:1;
    };
}gamma_srgb_bist_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gamma_adapt_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  sat_thl:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  sat_thl_mul:12;
    };
}adapt_gamma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d_stat_enable:1;
        RBus_UInt32  d_stat_srcsel:1;
        RBus_UInt32  r_low:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_high:14;
    };
}dstat_ctrl_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  g_low:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  g_high:14;
    };
}dstat_ctrl_g_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  b_low:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  b_high:14;
    };
}dstat_ctrl_b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  r_cnt:24;
    };
}dstat_o_r1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  r_min:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  r_max:14;
    };
}dstat_o_r2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  g_cnt:24;
    };
}dstat_o_g1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  g_min:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  g_max:14;
    };
}dstat_o_g2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  b_cnt:24;
    };
}dstat_o_b1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  b_min:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  b_max:14;
    };
}dstat_o_b2_RBUS;

#else //apply LITTLE_ENDIAN

//======GAMMA register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gamma_tab_d1:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  gamma_tab_d0:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  gamma_tab_index:12;
        RBus_UInt32  res3:4;
    };
}gamma_port_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gamma_ax_type_sel:1;
        RBus_UInt32  gamma_wr_error:1;
        RBus_UInt32  gamma_fifo_full:1;
        RBus_UInt32  gamma_fifo_empty:1;
        RBus_UInt32  gamma_ax_ch_sel:2;
        RBus_UInt32  gamma_ax_tab_sel:1;
        RBus_UInt32  gamma_ax_rw_sel:2;
        RBus_UInt32  res1:23;
    };
}gamma_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802c108_2_0:3;
        RBus_UInt32  gamma_overlap:1;
        RBus_UInt32  gamma_s_tab_sel:2;
        RBus_UInt32  gamma_m_tab_sel:2;
        RBus_UInt32  gamma_tab_size_sel:1;
        RBus_UInt32  res1:23;
    };
}gamma_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm:4;
        RBus_UInt32  rme:1;
        RBus_UInt32  ls:1;
        RBus_UInt32  res1:26;
    };
}gamma_srgb_bist_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gamma_b_bist_fail:1;
        RBus_UInt32  gamma_g_bist_fail:1;
        RBus_UInt32  gamma_r_bist_fail:1;
        RBus_UInt32  srgb_b_bist_fail:1;
        RBus_UInt32  srgb_g_bist_fail:1;
        RBus_UInt32  srgb_r_bist_fail:1;
        RBus_UInt32  inv_gamma_b_bist_fail:1;
        RBus_UInt32  inv_gamma_g_bist_fail:1;
        RBus_UInt32  inv_gamma_r_bist_fail:1;
        RBus_UInt32  gamma_b_drf_bist_fail:1;
        RBus_UInt32  gamma_g_drf_bist_fail:1;
        RBus_UInt32  gamma_r_drf_bist_fail:1;
        RBus_UInt32  srgb_b_drf_bist_fail:1;
        RBus_UInt32  srgb_g_drf_bist_fail:1;
        RBus_UInt32  srgb_r_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_b_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_g_drf_bist_fail:1;
        RBus_UInt32  inv_gamma_r_drf_bist_fail:1;
        RBus_UInt32  res1:14;
    };
}gamma_srgb_bist_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_thl_mul:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  sat_thl:12;
        RBus_UInt32  res2:3;
        RBus_UInt32  gamma_adapt_en:1;
    };
}adapt_gamma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_high:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_low:14;
        RBus_UInt32  d_stat_srcsel:1;
        RBus_UInt32  d_stat_enable:1;
    };
}dstat_ctrl_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  g_high:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  g_low:14;
        RBus_UInt32  res2:2;
    };
}dstat_ctrl_g_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  b_high:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  b_low:14;
        RBus_UInt32  res2:2;
    };
}dstat_ctrl_b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_cnt:24;
        RBus_UInt32  res1:8;
    };
}dstat_o_r1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_max:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_min:14;
        RBus_UInt32  res2:2;
    };
}dstat_o_r2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  g_cnt:24;
        RBus_UInt32  res1:8;
    };
}dstat_o_g1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  g_max:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  g_min:14;
        RBus_UInt32  res2:2;
    };
}dstat_o_g2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  b_cnt:24;
        RBus_UInt32  res1:8;
    };
}dstat_o_b1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  b_max:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  b_min:14;
        RBus_UInt32  res2:2;
    };
}dstat_o_b2_RBUS;




#endif 


#endif 
