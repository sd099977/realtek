/**
* @file rbusTVE_DMAReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2012/12/25
* @version 802
* @ingroup model_rbus
*
*/

#ifndef _RBUS_TVE_DMA_REG_H_
#define _RBUS_TVE_DMA_REG_H_

#include "rbusTypes.h"




// TVE_DMA Register Address

#define TVE_DMA_TVE_VDDMA_CTRL_VADDR               (0xb800A400)
#define TVE_DMA_TVE_VDDMA_VADDR                    (0xb800A404)
#define TVE_DMA_TVEVDDMA_LINESTEP_VADDR            (0xb800A408)
#define TVE_DMA_TVEVDDMA_SATRT0_VADDR              (0xb800A410)
#define TVE_DMA_TVEVDDMA_SATRT1_VADDR              (0xb800A414)
#define TVE_DMA_TVEVDDMA_SATRT2_VADDR              (0xb800A418)
#define TVE_DMA_TVEVDDMA_SATRT3_VADDR              (0xb800A41c)
#define TVE_DMA_TVEVBIDMA_CTRL_VADDR               (0xb800A420)
#define TVE_DMA_TVEVBIDMA_START_VADDR              (0xb800A424)
#define TVE_DMA_TVEVBIDMA_READ_WINDOW_VADDR        (0xb800A428)
#define TVE_DMA_TVEVBIDMA_START_STATUS_VADDR       (0xb800A42c)
#define TVE_DMA_TVEDMA_FIFOSTATUS_VADDR            (0xb800A430)
#define TVE_DMA_TVEDMA_BIST_DVS_VADDR              (0xb800A440)
#define TVE_DMA_TVEDMA_BIST_MODE_VADDR             (0xb800A444)
#define TVE_DMA_TVEDMA_DRF_BIST_MODE_VADDR         (0xb800A448)
#define TVE_DMA_TVEDMA_DRF_TEST_RESUME_VADDR       (0xb800A44c)
#define TVE_DMA_TVEDMA_LS_CNTL_VADDR               (0xb800A450)
#define TVE_DMA_TVEDMA_BIST_DONE_VADDR             (0xb800A454)
#define TVE_DMA_TVEDMA_DRF_BIST_DONE_VADDR         (0xb800A458)
#define TVE_DMA_TVEDMA_BIST_FAIL_VADDR             (0xb800A45c)
#define TVE_DMA_TVEDMA_DRF_BIST_FAIL_VADDR         (0xb800A460)
#define TVE_DMA_TVEDMA_DRF_BIST_PAUSE_VADDR        (0xb800A464)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======TVE_DMA register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  tve_vddma_output_4byte_swap:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  tve_vddma_output_y_cr_swap:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tve_vddma_output_seq_sel:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tve_vddma_buf_ctrl:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  tve_vddma_buf_sel:1;
    };
}TVE_VDDMA_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  tve_vddma_waterlvl:6;
        RBus_UInt32  tve_vddma_num:8;
        RBus_UInt32  tve_vddma_length:8;
        RBus_UInt32  tve_vddma_remain:8;
    };
}TVE_VDDMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vddma_line_step:29;
    };
}TVEVDDMA_LINESTEP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vddma_start_addr0:29;
    };
}TVEVDDMA_SATRT0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vddma_start_addr1:29;
    };
}TVEVDDMA_SATRT1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vddma_start_addr2:29;
    };
}TVEVDDMA_SATRT2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vddma_start_addr3:29;
    };
}TVEVDDMA_SATRT3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  tve_vbidma_output_4byte_swap:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  tve_vbidma_endian:1;
        RBus_UInt32  tve_vbidma_buf_num:4;
        RBus_UInt32  res3:3;
        RBus_UInt32  tve_vbidma_fetch_num:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tve_vbidma_total_line:1;
    };
}TVEVBIDMA_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  tve_vbidma_edge_trig:1;
        RBus_UInt32  tve_vbidma_start_addr:29;
    };
}TVEVBIDMA_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  tve_vbi_read_start:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  tve_vbi_read_end:11;
    };
}TVEVBIDMA_READ_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tve_vbidma_start_addr_now:29;
    };
}TVEVBIDMA_START_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vbidma_fifo_full_int:1;
        RBus_UInt32  vbidma_fifo_empty_int:1;
        RBus_UInt32  vbidma_fifo_full:1;
        RBus_UInt32  vbidma_fifo_empty:1;
        RBus_UInt32  vddma_fifo_full_int:1;
        RBus_UInt32  vddma_fifo_empty_int:1;
        RBus_UInt32  vddma_fifo_full:1;
        RBus_UInt32  vddma_fifo_empty:1;
    };
}TVEDMA_FIFOSTATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  mbist_tve_dvse:1;
        RBus_UInt32  mbist_tve_dvs:4;
    };
}TVEDMA_BIST_DVS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  bist_mode_vbidma:1;
        RBus_UInt32  bist_mode_vddma:1;
    };
}TVEDMA_BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  drf_bist_mode_vbidma:1;
        RBus_UInt32  drf_bist_mode_vddma:1;
    };
}TVEDMA_DRF_BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  drf_test_resume_vbidma:1;
        RBus_UInt32  drf_test_resume_vddma:1;
    };
}TVEDMA_DRF_TEST_RESUME_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  mbist_ls_cntl:1;
    };
}TVEDMA_LS_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  bist_done_vbidma:1;
        RBus_UInt32  bist_done_vddma:1;
    };
}TVEDMA_BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  drf_bist_done_vbidma:1;
        RBus_UInt32  drf_bist_done_vddma:1;
    };
}TVEDMA_DRF_BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  bist_fail_vbidma:1;
        RBus_UInt32  bist_fail_vddma:1;
    };
}TVEDMA_BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  drf_bist_fail_vbidma:1;
        RBus_UInt32  drf_bist_fail_vddma:1;
    };
}TVEDMA_DRF_BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  drf_start_pause_vbidma:1;
        RBus_UInt32  drf_start_pause_vddma:1;
    };
}TVEDMA_DRF_BIST_PAUSE_RBUS;





#else //apply LITTLE_ENDIAN


//======TVE_DMA register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_buf_sel:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  tve_vddma_buf_ctrl:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tve_vddma_output_seq_sel:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tve_vddma_output_y_cr_swap:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  tve_vddma_output_4byte_swap:1;
        RBus_UInt32  res1:15;
    };
}TVE_VDDMA_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_remain:8;
        RBus_UInt32  tve_vddma_length:8;
        RBus_UInt32  tve_vddma_num:8;
        RBus_UInt32  tve_vddma_waterlvl:6;
        RBus_UInt32  res1:2;
    };
}TVE_VDDMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_line_step:29;
        RBus_UInt32  res1:3;
    };
}TVEVDDMA_LINESTEP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_start_addr0:29;
        RBus_UInt32  res1:3;
    };
}TVEVDDMA_SATRT0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_start_addr1:29;
        RBus_UInt32  res1:3;
    };
}TVEVDDMA_SATRT1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_start_addr2:29;
        RBus_UInt32  res1:3;
    };
}TVEVDDMA_SATRT2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vddma_start_addr3:29;
        RBus_UInt32  res1:3;
    };
}TVEVDDMA_SATRT3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vbidma_total_line:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tve_vbidma_fetch_num:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tve_vbidma_buf_num:4;
        RBus_UInt32  tve_vbidma_endian:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  tve_vbidma_output_4byte_swap:1;
        RBus_UInt32  res1:15;
    };
}TVEVBIDMA_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vbidma_start_addr:29;
        RBus_UInt32  tve_vbidma_edge_trig:1;
        RBus_UInt32  res1:2;
    };
}TVEVBIDMA_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vbi_read_end:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  tve_vbi_read_start:11;
        RBus_UInt32  res1:9;
    };
}TVEVBIDMA_READ_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_vbidma_start_addr_now:29;
        RBus_UInt32  res1:3;
    };
}TVEVBIDMA_START_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vddma_fifo_empty:1;
        RBus_UInt32  vddma_fifo_full:1;
        RBus_UInt32  vddma_fifo_empty_int:1;
        RBus_UInt32  vddma_fifo_full_int:1;
        RBus_UInt32  vbidma_fifo_empty:1;
        RBus_UInt32  vbidma_fifo_full:1;
        RBus_UInt32  vbidma_fifo_empty_int:1;
        RBus_UInt32  vbidma_fifo_full_int:1;
        RBus_UInt32  res1:24;
    };
}TVEDMA_FIFOSTATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mbist_tve_dvs:4;
        RBus_UInt32  mbist_tve_dvse:1;
        RBus_UInt32  res1:27;
    };
}TVEDMA_BIST_DVS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mode_vddma:1;
        RBus_UInt32  bist_mode_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_bist_mode_vddma:1;
        RBus_UInt32  drf_bist_mode_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_DRF_BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_test_resume_vddma:1;
        RBus_UInt32  drf_test_resume_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_DRF_TEST_RESUME_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mbist_ls_cntl:1;
        RBus_UInt32  res1:31;
    };
}TVEDMA_LS_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_done_vddma:1;
        RBus_UInt32  bist_done_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_bist_done_vddma:1;
        RBus_UInt32  drf_bist_done_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_DRF_BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_vddma:1;
        RBus_UInt32  bist_fail_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_bist_fail_vddma:1;
        RBus_UInt32  drf_bist_fail_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_DRF_BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_start_pause_vddma:1;
        RBus_UInt32  drf_start_pause_vbidma:1;
        RBus_UInt32  res1:30;
    };
}TVEDMA_DRF_BIST_PAUSE_RBUS;


#endif







#endif //_RBUS_TVE_DMA_REG_H_

