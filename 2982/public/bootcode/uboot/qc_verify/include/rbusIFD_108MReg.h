/**
* @file rbusIFD_108MReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2011/12/12
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_IFD_108M_REG_H_
#define _RBUS_IFD_108M_REG_H_

#include "rbusTypes.h"




// IFD_108M Register Address

#define IFD_108M_VIDEO_BW_SEL_VADDR                 (0xb8032600)
#define IFD_108M_GRP_DELAY_EN_VADDR                 (0xb8032604)
#define IFD_108M_GRP_DELAY_READ_VADDR               (0xb8032608)
#define IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR         (0xb8032610)
#define IFD_108M_OUTPUT_LPF_READ_VADDR              (0xb8032614)
#define IFD_108M_DNLPF_TAP_VADDR                    (0xb8032618)
#define IFD_108M_DNLPF_TAP_READ_VADDR               (0xb803261c)
#define IFD_108M_EQ_FILTER_SEL_VADDR                (0xb8032620)
#define IFD_108M_EQ_FILTER_READ_VADDR               (0xb8032624)
#define IFD_108M_EQ_OUT_RMS_VADDR                   (0xb8032628)
#define IFD_108M_CRC3_CTRL_RESULT_VADDR             (0xb8032630)
#define IFD_108M_DEC_FIFOSTATUS_VADDR               (0xb8032640)
#define IFD_108M_DMA_DEBUG108_VADDR                 (0xb803264c)
#define IFD_108M_DEBUG_MODE4_VADDR                  (0xb8032650)
#define IFD_108M_VD_DAC_TEST_VADDR                  (0xb8032660)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======IFD_108M register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  video_bw_sel:4;
        RBus_UInt32  res2:8;
        RBus_UInt32  video_upsample_lp_sel:4;
    };
}video_bw_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  grp_delay_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  grp_delay_coe_en:1;
        RBus_UInt32  grp_delay_select_tap:8;
        RBus_UInt32  res3:1;
        RBus_UInt32  grp_delay_coe_modofy:11;
    };
}grp_delay_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  grp_delay_select_tap_read:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  grp_delay_coe_modofy_read:11;
    };
}grp_delay_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  output_lpf_vsync_coe_change:1;
        RBus_UInt32  output_lpf_extern_set:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  output_lpf_coe_modify_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  output_lpf_coe_tap:7;
        RBus_UInt32  res4:2;
        RBus_UInt32  output_lpf_coe:14;
    };
}output_lpf_modify_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  output_lpf_coe_read_tap:7;
        RBus_UInt32  res2:2;
        RBus_UInt32  output_lpf_coe_read:14;
    };
}output_lpf_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  dnlpf_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  dnlpf_tap_modify_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  dnlpf_tap_tap:5;
        RBus_UInt32  res4:1;
        RBus_UInt32  dnlpf_tap:11;
    };
}dnlpf_tap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  dnlpf_read_tap:5;
        RBus_UInt32  res2:1;
        RBus_UInt32  dnlpf_tap_read:11;
    };
}dnlpf_tap_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  eq_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  eq_coe_modify_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  eq_coe_tap:5;
        RBus_UInt32  res4:2;
        RBus_UInt32  eq_coe:10;
    };
}eq_filter_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  eq_coe_read_tap:5;
        RBus_UInt32  res2:2;
        RBus_UInt32  eq_coe_read:10;
    };
}eq_filter_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  eq_out_rms:22;
    };
}eq_out_rms_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  crc3_result:16;
        RBus_UInt32  res2:2;
        RBus_UInt32  crc3_en:1;
        RBus_UInt32  crc3_insel:1;
    };
}CRC3_Ctrl_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  dec_fifo_full_clear:1;
        RBus_UInt32  dec_fifo_empty_clear:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  dec_fifo_full:1;
        RBus_UInt32  dec_fifo_empty:1;
    };
}dec_fifostatus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  dma_fifo_debug108_full:1;
        RBus_UInt32  dma_fifo_debug108_empty:1;
    };
}dma_debug108_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  debug_mode4_en:1;
        RBus_UInt32  debug_mode4:7;
    };
}debug_mode4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  vddac_test:12;
    };
}vd_dac_test_RBUS;





#else //apply LITTLE_ENDIAN


//======IFD_108M register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  video_upsample_lp_sel:4;
        RBus_UInt32  res2:8;
        RBus_UInt32  video_bw_sel:4;
        RBus_UInt32  res1:16;
    };
}video_bw_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  grp_delay_coe_modofy:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  grp_delay_select_tap:8;
        RBus_UInt32  grp_delay_coe_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  grp_delay_en:1;
        RBus_UInt32  res1:7;
    };
}grp_delay_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  grp_delay_coe_modofy_read:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  grp_delay_select_tap_read:8;
        RBus_UInt32  res1:12;
    };
}grp_delay_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_lpf_coe:14;
        RBus_UInt32  res4:2;
        RBus_UInt32  output_lpf_coe_tap:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  output_lpf_coe_modify_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  output_lpf_extern_set:1;
        RBus_UInt32  output_lpf_vsync_coe_change:1;
        RBus_UInt32  res1:2;
    };
}output_lpf_modify_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_lpf_coe_read:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  output_lpf_coe_read_tap:7;
        RBus_UInt32  res1:9;
    };
}output_lpf_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dnlpf_tap:11;
        RBus_UInt32  res4:1;
        RBus_UInt32  dnlpf_tap_tap:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  dnlpf_tap_modify_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  dnlpf_en:1;
        RBus_UInt32  res1:7;
    };
}dnlpf_tap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dnlpf_tap_read:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  dnlpf_read_tap:5;
        RBus_UInt32  res1:15;
    };
}dnlpf_tap_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_coe:10;
        RBus_UInt32  res4:2;
        RBus_UInt32  eq_coe_tap:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  eq_coe_modify_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  eq_en:1;
        RBus_UInt32  res1:7;
    };
}eq_filter_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_coe_read:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  eq_coe_read_tap:5;
        RBus_UInt32  res1:15;
    };
}eq_filter_read_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_out_rms:22;
        RBus_UInt32  res1:10;
    };
}eq_out_rms_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc3_insel:1;
        RBus_UInt32  crc3_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  crc3_result:16;
        RBus_UInt32  res1:12;
    };
}CRC3_Ctrl_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dec_fifo_empty:1;
        RBus_UInt32  dec_fifo_full:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  dec_fifo_empty_clear:1;
        RBus_UInt32  dec_fifo_full_clear:1;
        RBus_UInt32  res1:26;
    };
}dec_fifostatus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dma_fifo_debug108_empty:1;
        RBus_UInt32  dma_fifo_debug108_full:1;
        RBus_UInt32  res1:30;
    };
}dma_debug108_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debug_mode4:7;
        RBus_UInt32  debug_mode4_en:1;
        RBus_UInt32  res1:24;
    };
}debug_mode4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vddac_test:12;
        RBus_UInt32  res1:20;
    };
}vd_dac_test_RBUS;


#endif







#endif //_RBUS_IFD_108M_REG_H_

