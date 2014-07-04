/**
* @file rbusMagellan-DesignSpec-D-Domain_2D_to_3DReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/2/5
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_MAGELLAN_DESIGNSPEC_D_DOMAIN_2D_TO_3D_REG_H_
#define _RBUS_MAGELLAN_DESIGNSPEC_D_DOMAIN_2D_TO_3D_REG_H_

#include "rbusTypes.h"



//  MAGELLAN-DESIGNSPEC-D-DOMAIN_2D_TO_3D Register Address



#define  D_2D_TO_3D_D_2D3D_DOUBLE_BUFFER_CONTROL_VADDR 		(0xb8029600)
#define  D_2D_TO_3D_D_2D3D_CONTROL_VADDR 		(0xb8029604)
#define  D_2D_TO_3D_D_2D3D_OBJECT1_OPERATION_VADDR 		(0xb8029608)
#define  D_2D_TO_3D_D_2D3D_OBJECT2_OPERATION_VADDR 		(0xb802960c)
#define  D_2D_TO_3D_D_2D3D_OBJECT3_OPERATION_VADDR 		(0xb8029610)
#define  D_2D_TO_3D_D_2D3D_TILT_OPERATION_VADDR 		(0xb8029614)
#define  D_2D_TO_3D_D_2D3D_HISTO_OPERATION_VADDR 		(0xb8029618)
#define  D_2D_TO_3D_D_2D3D_B_BORDER_VADDR 		(0xb8029620)
#define  D_2D_TO_3D_D_2D3D_TILT_DEPTH_VADDR 		(0xb8029630)
#define  D_2D_TO_3D_D_2D3D_OBJECT1_DEPTH1_VADDR 		(0xb8029634)
#define  D_2D_TO_3D_D_2D3D_OBJECT1_DEPTH2_VADDR 		(0xb8029638)
#define  D_2D_TO_3D_D_2D3D_OBJECT2_DEPTH1_VADDR 		(0xb802963c)
#define  D_2D_TO_3D_D_2D3D_OBJECT2_DEPTH2_VADDR 		(0xb8029640)
#define  D_2D_TO_3D_D_2D3D_OBJECT3_DEPTH1_VADDR 		(0xb8029644)
#define  D_2D_TO_3D_D_2D3D_OBJECT3_DEPTH2_VADDR 		(0xb8029648)
#define  D_2D_TO_3D_D_2D3D_DEPTH_FIL_VADDR 		(0xb8029660)
#define  D_2D_TO_3D_D_2D3D_SHIFTER_VADDR 		(0xb8029664)
#define  D_2D_TO_3D_D_2D3D_BOUNDARY_SCALING_VADDR 		(0xb8029668)
#define  D_2D_TO_3D_D_2D3D_HOLE_FILL_VADDR 		(0xb8029670)
#define  D_2D_TO_3D_D_2D3D_BIST0_VADDR 		(0xb8029680)
#define  D_2D_TO_3D_D_2D3D_BIST1_VADDR 		(0xb8029684)
#define  D_2D_TO_3D_D_2D3D_OUTPUT_FIL_Y_VADDR 		(0xb8029690)
#define  D_2D_TO_3D_D_2D3D_OUTPUT_FIL_C_VADDR 		(0xb8029694)
#define  D_2D_TO_3D_D_2D3D_HISTO_CTRL0_VADDR 		(0xb8029700)
#define  D_2D_TO_3D_D_2D3D_HISTO_CTRL1_VADDR 		(0xb8029704)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_0_VADDR 		(0xb8029710)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_1_VADDR 		(0xb8029714)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_2_VADDR 		(0xb8029718)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_3_VADDR 		(0xb802971c)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_4_VADDR 		(0xb8029720)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_DISPREAD_5_VADDR 		(0xb8029724)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP2_0_VADDR 		(0xb8029730)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP2_1_VADDR 		(0xb8029734)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP3_0_VADDR 		(0xb8029738)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP3_1_VADDR 		(0xb802973c)
#define  D_2D_TO_3D_D_2D3D_HISTO_COLOR_4_VADDR 		(0xb8029740)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP4_0_VADDR 		(0xb8029744)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP4_1_VADDR 		(0xb8029748)
#define  D_2D_TO_3D_D_2D3D_HISTO_COLOR_5_VADDR 		(0xb802974c)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP5_0_VADDR 		(0xb8029750)
#define  D_2D_TO_3D_D_2D3D_HISTO_WEIGHT_UP5_1_VADDR 		(0xb8029754)
#define  D_2D_TO_3D_D_2D3D_HISTO_COLOR_6_VADDR 		(0xb8029758)
#define  D_2D_TO_3D_D_2D3D_HISTO_DEPTH_WEIGHT_0_VADDR 		(0xb802975c)
#define  D_2D_TO_3D_D_2D3D_HISTO_DEPTH_WEIGHT_1_VADDR 		(0xb8029760)
#define  D_2D_TO_3D_D_2D3D_HISTO_DIFF_DEPTH_0_VADDR 		(0xb8029770)
#define  D_2D_TO_3D_D_2D3D_HISTO_DIFF_DEPTH_1_VADDR 		(0xb8029774)
#define  D_2D_TO_3D_D_2D3D_HISTO_DIFF_DEPTH_2_VADDR 		(0xb8029778)
#define  D_2D_TO_3D_D_2D3D_HISTO_TEMP_0_VADDR 		(0xb8029780)
#define  D_2D_TO_3D_D_2D3D_HISTO_TEMP_1_VADDR 		(0xb8029784)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_CTRL0_VADDR 		(0xb80297b0)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_CTRL2_VADDR 		(0xb80297b4)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF0_VADDR 		(0xb80297b8)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF1_VADDR 		(0xb80297bc)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF2_VADDR 		(0xb80297c0)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF3_VADDR 		(0xb80297c4)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF4_VADDR 		(0xb80297c8)
#define  D_2D_TO_3D_D_2D3D_HISTO_SU_COEF5_VADDR 		(0xb80297cc)
#define  D_2D_TO_3D_D_2D3D_HISTO_SRAM_CTRL_VADDR 		(0xb80297d0)
#define  D_2D_TO_3D_D_2D3D_HISTO_SRAM_AP_VADDR 		(0xb80297d4)
#define  D_2D_TO_3D_D_2D3D_HISTO_SRAM_DP_VADDR 		(0xb80297d8)
#define  D_2D_TO_3D_D_2D3D_HISTO_MAX_MIN_VADDR 		(0xb80297f0)
#define  D_2D_TO_3D_D_2D3D_HISTO_IIR_VADDR 		(0xb80297f4)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======MAGELLAN-DESIGNSPEC-D-DOMAIN_2D_TO_3D register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_apply:1;
    };
}d_2d3d_double_buffer_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  depth_src_mux:1;
        RBus_UInt32  render_method:1;
        RBus_UInt32  input_sbs_render_mode:1;
        RBus_UInt32  obj_y_src_sel:1;
        RBus_UInt32  output_format:1;
        RBus_UInt32  d_2d3d_depth_frac_en:1;
        RBus_UInt32  depth_debug_mode:1;
        RBus_UInt32  l_frame_shift_en:1;
        RBus_UInt32  r_frame_shift_en:1;
        RBus_UInt32  l_flag_inv:1;
        RBus_UInt32  tilt_depth_en:1;
        RBus_UInt32  object3_depth_en:1;
        RBus_UInt32  object2_depth_en:1;
        RBus_UInt32  object1_depth_en:1;
        RBus_UInt32  res2:1;
    };
}d_2d3d_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  object1_thd:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  object1_offset:9;
        RBus_UInt32  object1_gain:8;
    };
}d_2d3d_object1_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  object2_thd:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  object2_offset:9;
        RBus_UInt32  object2_gain:8;
    };
}d_2d3d_object2_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  object3_thd:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  object3_offset:9;
        RBus_UInt32  object3_gain:8;
    };
}d_2d3d_object3_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  tilt_thd:8;
        RBus_UInt32  tilt_offset:8;
        RBus_UInt32  tilt_gain:8;
    };
}d_2d3d_tilt_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  histo_thd:8;
        RBus_UInt32  histo_offset:8;
        RBus_UInt32  histo_gain:8;
    };
}d_2d3d_histo_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  border_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  border_den_start:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  border_den_end:12;
    };
}d_2d3d_b_border_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tilt_depth_step:12;
        RBus_UInt32  res2:8;
        RBus_UInt32  initial_depth:8;
    };
}d_2d3d_tilt_depth_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object1_depth_weight1:3;
        RBus_UInt32  object1_depth_ref1:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  object1_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object1_depth_gain:7;
        RBus_UInt32  res4:3;
        RBus_UInt32  object1_depth_dir:1;
    };
}d_2d3d_object1_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object1_depth_weight3:3;
        RBus_UInt32  object1_depth_ref3:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  object1_depth_weight2:3;
        RBus_UInt32  object1_depth_ref2:8;
    };
}d_2d3d_object1_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object2_depth_weight1:3;
        RBus_UInt32  object2_depth_ref1:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  object2_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object2_depth_gain:7;
        RBus_UInt32  res4:3;
        RBus_UInt32  object2_depth_dir:1;
    };
}d_2d3d_object2_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object2_depth_weight3:3;
        RBus_UInt32  object2_depth_ref3:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  object2_depth_weight2:3;
        RBus_UInt32  object2_depth_ref2:8;
    };
}d_2d3d_object2_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object3_depth_weight1:3;
        RBus_UInt32  object3_depth_ref1:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  object3_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object3_depth_gain:7;
        RBus_UInt32  res4:3;
        RBus_UInt32  object3_depth_dir:1;
    };
}d_2d3d_object3_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  object3_depth_weight3:3;
        RBus_UInt32  object3_depth_ref3:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  object3_depth_weight2:3;
        RBus_UInt32  object3_depth_ref2:8;
    };
}d_2d3d_object3_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  d_2d3d_depth_lpf_c0:4;
        RBus_UInt32  d_2d3d_depth_lpf_c1:4;
        RBus_UInt32  d_2d3d_depth_lpf_c2:4;
        RBus_UInt32  res2:11;
        RBus_UInt32  d_2d3d_depth_lpf_en:1;
    };
}d_2d3d_depth_fil_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  shifter_thd:6;
        RBus_UInt32  shifter_offset:8;
        RBus_UInt32  shifter_gain:8;
    };
}d_2d3d_shifter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  dbs_seg_num:2;
        RBus_UInt32  dbs_en:1;
    };
}d_2d3d_boundary_scaling_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  hf_new_en:1;
        RBus_UInt32  hole_fil_sel:3;
    };
}d_2d3d_hole_fill_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  render_1p_rme_3:1;
        RBus_UInt32  render_1p_rme_2:1;
        RBus_UInt32  render_1p_rme_1:1;
        RBus_UInt32  render_1p_rme_0:1;
        RBus_UInt32  render_2p_rmea_1:1;
        RBus_UInt32  render_2p_rmeb_1:1;
        RBus_UInt32  render_2p_rmea_0:1;
        RBus_UInt32  render_2p_rmeb_0:1;
        RBus_UInt32  render_1p_ls_3:1;
        RBus_UInt32  render_1p_ls_2:1;
        RBus_UInt32  render_1p_ls_1:1;
        RBus_UInt32  render_1p_ls_0:1;
        RBus_UInt32  render_2p_ls_1:1;
        RBus_UInt32  render_2p_ls_0:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  render_1p_drf_bist_fail_3:1;
        RBus_UInt32  render_1p_drf_bist_fail_2:1;
        RBus_UInt32  render_1p_drf_bist_fail_1:1;
        RBus_UInt32  render_1p_drf_bist_fail_0:1;
        RBus_UInt32  render_2p_drf_bist_fail_1:1;
        RBus_UInt32  render_2p_drf_bist_fail_0:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  render_1p_bist_fail_3:1;
        RBus_UInt32  render_1p_bist_fail_2:1;
        RBus_UInt32  render_1p_bist_fail_1:1;
        RBus_UInt32  render_1p_bist_fail_0:1;
        RBus_UInt32  render_2p_bist_fail_1:1;
        RBus_UInt32  render_2p_bist_fail_0:1;
        RBus_UInt32  res3:2;
    };
}d_2d3d_bist0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  render_1p_rm_3:4;
        RBus_UInt32  render_1p_rm_2:4;
        RBus_UInt32  render_1p_rm_1:4;
        RBus_UInt32  render_1p_rm_0:4;
        RBus_UInt32  render_2p_rma_1:4;
        RBus_UInt32  render_2p_rmb_1:4;
        RBus_UInt32  render_2p_rma_0:4;
        RBus_UInt32  render_2p_rmb_0:4;
    };
}d_2d3d_bist1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  d_2d3d_output_y_lpf_c0:4;
        RBus_UInt32  d_2d3d_output_y_lpf_c1:4;
        RBus_UInt32  d_2d3d_output_y_lpf_c2:4;
        RBus_UInt32  res2:15;
        RBus_UInt32  d_2d3d_output_lpf_y_en:1;
    };
}d_2d3d_output_fil_y_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  d_2d3d_output_c_lpf_c0:4;
        RBus_UInt32  d_2d3d_output_c_lpf_c1:4;
        RBus_UInt32  d_2d3d_output_c_lpf_c2:4;
        RBus_UInt32  res2:15;
        RBus_UInt32  d_2d3d_output_lpf_c_en:1;
    };
}d_2d3d_output_fil_c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  histo_depth_weight:4;
        RBus_UInt32  res1:3;
        RBus_UInt32  h_grid_size:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  v_grid_size:9;
        RBus_UInt32  res3:3;
        RBus_UInt32  histo_en:1;
    };
}d_2d3d_histo_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  color6_y_act:1;
        RBus_UInt32  color5_y_act:1;
        RBus_UInt32  color4_y_act:1;
        RBus_UInt32  color3_y_act:1;
        RBus_UInt32  color2_y_act:1;
        RBus_UInt32  color1_y_act:1;
    };
}d_2d3d_histo_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_up7:4;
        RBus_UInt32  weight_dis_up6:4;
        RBus_UInt32  weight_dis_up5:4;
        RBus_UInt32  weight_dis_up4:4;
        RBus_UInt32  weight_dis_up3:4;
        RBus_UInt32  weight_dis_up2:4;
        RBus_UInt32  weight_dis_up1:4;
        RBus_UInt32  weight_dis_up0:4;
    };
}d_2d3d_histo_weight_dispread_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_up15:4;
        RBus_UInt32  weight_dis_up14:4;
        RBus_UInt32  weight_dis_up13:4;
        RBus_UInt32  weight_dis_up12:4;
        RBus_UInt32  weight_dis_up11:4;
        RBus_UInt32  weight_dis_up10:4;
        RBus_UInt32  weight_dis_up9:4;
        RBus_UInt32  weight_dis_up8:4;
    };
}d_2d3d_histo_weight_dispread_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr7:4;
        RBus_UInt32  weight_dis_lr6:4;
        RBus_UInt32  weight_dis_lr5:4;
        RBus_UInt32  weight_dis_lr4:4;
        RBus_UInt32  weight_dis_lr3:4;
        RBus_UInt32  weight_dis_lr2:4;
        RBus_UInt32  weight_dis_lr1:4;
        RBus_UInt32  weight_dis_lr0:4;
    };
}d_2d3d_histo_weight_dispread_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr15:4;
        RBus_UInt32  weight_dis_lr14:4;
        RBus_UInt32  weight_dis_lr13:4;
        RBus_UInt32  weight_dis_lr12:4;
        RBus_UInt32  weight_dis_lr11:4;
        RBus_UInt32  weight_dis_lr10:4;
        RBus_UInt32  weight_dis_lr9:4;
        RBus_UInt32  weight_dis_lr8:4;
    };
}d_2d3d_histo_weight_dispread_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr23:4;
        RBus_UInt32  weight_dis_lr22:4;
        RBus_UInt32  weight_dis_lr21:4;
        RBus_UInt32  weight_dis_lr20:4;
        RBus_UInt32  weight_dis_lr19:4;
        RBus_UInt32  weight_dis_lr18:4;
        RBus_UInt32  weight_dis_lr17:4;
        RBus_UInt32  weight_dis_lr16:4;
    };
}d_2d3d_histo_weight_dispread_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr31:4;
        RBus_UInt32  weight_dis_lr30:4;
        RBus_UInt32  weight_dis_lr29:4;
        RBus_UInt32  weight_dis_lr28:4;
        RBus_UInt32  weight_dis_lr27:4;
        RBus_UInt32  weight_dis_lr26:4;
        RBus_UInt32  weight_dis_lr25:4;
        RBus_UInt32  weight_dis_lr24:4;
    };
}d_2d3d_histo_weight_dispread_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up2_7:4;
        RBus_UInt32  weight_up2_6:4;
        RBus_UInt32  weight_up2_5:4;
        RBus_UInt32  weight_up2_4:4;
        RBus_UInt32  weight_up2_3:4;
        RBus_UInt32  weight_up2_2:4;
        RBus_UInt32  weight_up2_1:4;
        RBus_UInt32  weight_up2_0:4;
    };
}d_2d3d_histo_weight_up2_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up2_15:4;
        RBus_UInt32  weight_up2_14:4;
        RBus_UInt32  weight_up2_13:4;
        RBus_UInt32  weight_up2_12:4;
        RBus_UInt32  weight_up2_11:4;
        RBus_UInt32  weight_up2_10:4;
        RBus_UInt32  weight_up2_9:4;
        RBus_UInt32  weight_up2_8:4;
    };
}d_2d3d_histo_weight_up2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up3_7:4;
        RBus_UInt32  weight_up3_6:4;
        RBus_UInt32  weight_up3_5:4;
        RBus_UInt32  weight_up3_4:4;
        RBus_UInt32  weight_up3_3:4;
        RBus_UInt32  weight_up3_2:4;
        RBus_UInt32  weight_up3_1:4;
        RBus_UInt32  weight_up3_0:4;
    };
}d_2d3d_histo_weight_up3_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up3_15:4;
        RBus_UInt32  weight_up3_14:4;
        RBus_UInt32  weight_up3_13:4;
        RBus_UInt32  weight_up3_12:4;
        RBus_UInt32  weight_up3_11:4;
        RBus_UInt32  weight_up3_10:4;
        RBus_UInt32  weight_up3_9:4;
        RBus_UInt32  weight_up3_8:4;
    };
}d_2d3d_histo_weight_up3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  weight_01_on_color4:3;
        RBus_UInt32  color4_v1:4;
        RBus_UInt32  color4_u1:4;
        RBus_UInt32  color4_y1:4;
        RBus_UInt32  color4_v0:4;
        RBus_UInt32  color4_u0:4;
        RBus_UInt32  color4_y0:4;
    };
}d_2d3d_histo_color_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up4_7:4;
        RBus_UInt32  weight_up4_6:4;
        RBus_UInt32  weight_up4_5:4;
        RBus_UInt32  weight_up4_4:4;
        RBus_UInt32  weight_up4_3:4;
        RBus_UInt32  weight_up4_2:4;
        RBus_UInt32  weight_up4_1:4;
        RBus_UInt32  weight_up4_0:4;
    };
}d_2d3d_histo_weight_up4_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up4_15:4;
        RBus_UInt32  weight_up4_14:4;
        RBus_UInt32  weight_up4_13:4;
        RBus_UInt32  weight_up4_12:4;
        RBus_UInt32  weight_up4_11:4;
        RBus_UInt32  weight_up4_10:4;
        RBus_UInt32  weight_up4_9:4;
        RBus_UInt32  weight_up4_8:4;
    };
}d_2d3d_histo_weight_up4_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  color5_v:4;
        RBus_UInt32  color5_u:4;
        RBus_UInt32  color5_y:4;
    };
}d_2d3d_histo_color_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up5_7:4;
        RBus_UInt32  weight_up5_6:4;
        RBus_UInt32  weight_up5_5:4;
        RBus_UInt32  weight_up5_4:4;
        RBus_UInt32  weight_up5_3:4;
        RBus_UInt32  weight_up5_2:4;
        RBus_UInt32  weight_up5_1:4;
        RBus_UInt32  weight_up5_0:4;
    };
}d_2d3d_histo_weight_up5_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up5_15:4;
        RBus_UInt32  weight_up5_14:4;
        RBus_UInt32  weight_up5_13:4;
        RBus_UInt32  weight_up5_12:4;
        RBus_UInt32  weight_up5_11:4;
        RBus_UInt32  weight_up5_10:4;
        RBus_UInt32  weight_up5_9:4;
        RBus_UInt32  weight_up5_8:4;
    };
}d_2d3d_histo_weight_up5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  color6_v:8;
        RBus_UInt32  color6_u:8;
        RBus_UInt32  color6_y:8;
    };
}d_2d3d_histo_color_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  depth_weight_4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  depth_weight_3:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  depth_weight_2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  depth_weight_1:6;
    };
}d_2d3d_histo_depth_weight_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  depth_weight_6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  depth_weight_5:6;
    };
}d_2d3d_histo_depth_weight_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  slope_2:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  margin_2:7;
        RBus_UInt32  res3:5;
        RBus_UInt32  slope_1:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  margin_1:7;
    };
}d_2d3d_histo_diff_depth_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  slope_4:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  margin_4:7;
        RBus_UInt32  res3:5;
        RBus_UInt32  slope_3:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  margin_3:7;
    };
}d_2d3d_histo_diff_depth_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  slope_6:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  margin_6:7;
        RBus_UInt32  res3:5;
        RBus_UInt32  slope_5:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  margin_5:7;
    };
}d_2d3d_histo_diff_depth_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  temporal_2_th_s:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  temporal_2_th_l:3;
        RBus_UInt32  res3:3;
        RBus_UInt32  temporal_2_en:1;
        RBus_UInt32  res4:5;
        RBus_UInt32  temporal_1_th_s:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  temporal_1_th_l:3;
        RBus_UInt32  res6:3;
        RBus_UInt32  temporal_1_en:1;
    };
}d_2d3d_histo_temp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  temporal_3_th_s:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  temporal_3_th_l:3;
        RBus_UInt32  res3:3;
        RBus_UInt32  temporal_3_en:1;
    };
}d_2d3d_histo_temp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_en:1;
        RBus_UInt32  res1:11;
        RBus_UInt32  su_hfactor:20;
    };
}d_2d3d_histo_su_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  su_vfactor:20;
    };
}d_2d3d_histo_su_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_htab_coef0:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  su_scaleup_htab_coef1:10;
    };
}d_2d3d_histo_su_coef0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_htab_coef3:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  su_scaleup_htab_coef2:10;
    };
}d_2d3d_histo_su_coef1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  su_scaleup_htab_coef4:10;
    };
}d_2d3d_histo_su_coef2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_vtab_coef0:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  su_scaleup_vtab_coef1:10;
    };
}d_2d3d_histo_su_coef3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_vtab_coef3:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  su_scaleup_vtab_coef2:10;
    };
}d_2d3d_histo_su_coef4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  su_scaleup_vtab_coef4:10;
    };
}d_2d3d_histo_su_coef5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  depth_update_en:1;
        RBus_UInt32  depth_sw_mode:1;
    };
}d_2d3d_histo_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  depth_adr:9;
    };
}d_2d3d_histo_sram_ap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  depth_dat:8;
    };
}d_2d3d_histo_sram_dp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_max:8;
        RBus_UInt32  depth_min:8;
        RBus_UInt32  res1:13;
        RBus_UInt32  max_min_mux:2;
        RBus_UInt32  max_min_en:1;
    };
}d_2d3d_histo_max_min_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  iir_weight:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  iir_en:1;
    };
}d_2d3d_histo_iir_RBUS;

#else //apply LITTLE_ENDIAN

//======MAGELLAN-DESIGNSPEC-D-DOMAIN_2D_TO_3D register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_apply:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  res1:29;
    };
}d_2d3d_double_buffer_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  object1_depth_en:1;
        RBus_UInt32  object2_depth_en:1;
        RBus_UInt32  object3_depth_en:1;
        RBus_UInt32  tilt_depth_en:1;
        RBus_UInt32  l_flag_inv:1;
        RBus_UInt32  r_frame_shift_en:1;
        RBus_UInt32  l_frame_shift_en:1;
        RBus_UInt32  depth_debug_mode:1;
        RBus_UInt32  d_2d3d_depth_frac_en:1;
        RBus_UInt32  output_format:1;
        RBus_UInt32  obj_y_src_sel:1;
        RBus_UInt32  input_sbs_render_mode:1;
        RBus_UInt32  render_method:1;
        RBus_UInt32  depth_src_mux:1;
        RBus_UInt32  res2:17;
    };
}d_2d3d_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object1_gain:8;
        RBus_UInt32  object1_offset:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  object1_thd:8;
        RBus_UInt32  res2:4;
    };
}d_2d3d_object1_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object2_gain:8;
        RBus_UInt32  object2_offset:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  object2_thd:8;
        RBus_UInt32  res2:4;
    };
}d_2d3d_object2_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object3_gain:8;
        RBus_UInt32  object3_offset:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  object3_thd:8;
        RBus_UInt32  res2:4;
    };
}d_2d3d_object3_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tilt_gain:8;
        RBus_UInt32  tilt_offset:8;
        RBus_UInt32  tilt_thd:8;
        RBus_UInt32  res1:8;
    };
}d_2d3d_tilt_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  histo_gain:8;
        RBus_UInt32  histo_offset:8;
        RBus_UInt32  histo_thd:8;
        RBus_UInt32  res1:8;
    };
}d_2d3d_histo_operation_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  border_den_end:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  border_den_start:12;
        RBus_UInt32  res2:3;
        RBus_UInt32  border_en:1;
    };
}d_2d3d_b_border_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  initial_depth:8;
        RBus_UInt32  res1:8;
        RBus_UInt32  tilt_depth_step:12;
        RBus_UInt32  res2:4;
    };
}d_2d3d_tilt_depth_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object1_depth_dir:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  object1_depth_gain:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  object1_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object1_depth_ref1:8;
        RBus_UInt32  object1_depth_weight1:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_object1_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object1_depth_ref2:8;
        RBus_UInt32  object1_depth_weight2:3;
        RBus_UInt32  res1:5;
        RBus_UInt32  object1_depth_ref3:8;
        RBus_UInt32  object1_depth_weight3:3;
        RBus_UInt32  res2:5;
    };
}d_2d3d_object1_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object2_depth_dir:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  object2_depth_gain:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  object2_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object2_depth_ref1:8;
        RBus_UInt32  object2_depth_weight1:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_object2_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object2_depth_ref2:8;
        RBus_UInt32  object2_depth_weight2:3;
        RBus_UInt32  res1:5;
        RBus_UInt32  object2_depth_ref3:8;
        RBus_UInt32  object2_depth_weight3:3;
        RBus_UInt32  res2:5;
    };
}d_2d3d_object2_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object3_depth_dir:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  object3_depth_gain:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  object3_depth_shift:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  object3_depth_ref1:8;
        RBus_UInt32  object3_depth_weight1:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_object3_depth1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  object3_depth_ref2:8;
        RBus_UInt32  object3_depth_weight2:3;
        RBus_UInt32  res1:5;
        RBus_UInt32  object3_depth_ref3:8;
        RBus_UInt32  object3_depth_weight3:3;
        RBus_UInt32  res2:5;
    };
}d_2d3d_object3_depth2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d_2d3d_depth_lpf_en:1;
        RBus_UInt32  res1:11;
        RBus_UInt32  d_2d3d_depth_lpf_c2:4;
        RBus_UInt32  d_2d3d_depth_lpf_c1:4;
        RBus_UInt32  d_2d3d_depth_lpf_c0:4;
        RBus_UInt32  res2:8;
    };
}d_2d3d_depth_fil_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  shifter_gain:8;
        RBus_UInt32  shifter_offset:8;
        RBus_UInt32  shifter_thd:6;
        RBus_UInt32  res1:10;
    };
}d_2d3d_shifter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dbs_en:1;
        RBus_UInt32  dbs_seg_num:2;
        RBus_UInt32  res1:29;
    };
}d_2d3d_boundary_scaling_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hole_fil_sel:3;
        RBus_UInt32  hf_new_en:1;
        RBus_UInt32  res1:28;
    };
}d_2d3d_hole_fill_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  render_2p_bist_fail_0:1;
        RBus_UInt32  render_2p_bist_fail_1:1;
        RBus_UInt32  render_1p_bist_fail_0:1;
        RBus_UInt32  render_1p_bist_fail_1:1;
        RBus_UInt32  render_1p_bist_fail_2:1;
        RBus_UInt32  render_1p_bist_fail_3:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  render_2p_drf_bist_fail_0:1;
        RBus_UInt32  render_2p_drf_bist_fail_1:1;
        RBus_UInt32  render_1p_drf_bist_fail_0:1;
        RBus_UInt32  render_1p_drf_bist_fail_1:1;
        RBus_UInt32  render_1p_drf_bist_fail_2:1;
        RBus_UInt32  render_1p_drf_bist_fail_3:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  render_2p_ls_0:1;
        RBus_UInt32  render_2p_ls_1:1;
        RBus_UInt32  render_1p_ls_0:1;
        RBus_UInt32  render_1p_ls_1:1;
        RBus_UInt32  render_1p_ls_2:1;
        RBus_UInt32  render_1p_ls_3:1;
        RBus_UInt32  render_2p_rmeb_0:1;
        RBus_UInt32  render_2p_rmea_0:1;
        RBus_UInt32  render_2p_rmeb_1:1;
        RBus_UInt32  render_2p_rmea_1:1;
        RBus_UInt32  render_1p_rme_0:1;
        RBus_UInt32  render_1p_rme_1:1;
        RBus_UInt32  render_1p_rme_2:1;
        RBus_UInt32  render_1p_rme_3:1;
    };
}d_2d3d_bist0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  render_2p_rmb_0:4;
        RBus_UInt32  render_2p_rma_0:4;
        RBus_UInt32  render_2p_rmb_1:4;
        RBus_UInt32  render_2p_rma_1:4;
        RBus_UInt32  render_1p_rm_0:4;
        RBus_UInt32  render_1p_rm_1:4;
        RBus_UInt32  render_1p_rm_2:4;
        RBus_UInt32  render_1p_rm_3:4;
    };
}d_2d3d_bist1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d_2d3d_output_lpf_y_en:1;
        RBus_UInt32  res1:15;
        RBus_UInt32  d_2d3d_output_y_lpf_c2:4;
        RBus_UInt32  d_2d3d_output_y_lpf_c1:4;
        RBus_UInt32  d_2d3d_output_y_lpf_c0:4;
        RBus_UInt32  res2:4;
    };
}d_2d3d_output_fil_y_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d_2d3d_output_lpf_c_en:1;
        RBus_UInt32  res1:15;
        RBus_UInt32  d_2d3d_output_c_lpf_c2:4;
        RBus_UInt32  d_2d3d_output_c_lpf_c1:4;
        RBus_UInt32  d_2d3d_output_c_lpf_c0:4;
        RBus_UInt32  res2:4;
    };
}d_2d3d_output_fil_c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  histo_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  v_grid_size:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  h_grid_size:9;
        RBus_UInt32  res3:3;
        RBus_UInt32  histo_depth_weight:4;
    };
}d_2d3d_histo_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  color1_y_act:1;
        RBus_UInt32  color2_y_act:1;
        RBus_UInt32  color3_y_act:1;
        RBus_UInt32  color4_y_act:1;
        RBus_UInt32  color5_y_act:1;
        RBus_UInt32  color6_y_act:1;
        RBus_UInt32  res1:26;
    };
}d_2d3d_histo_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_up0:4;
        RBus_UInt32  weight_dis_up1:4;
        RBus_UInt32  weight_dis_up2:4;
        RBus_UInt32  weight_dis_up3:4;
        RBus_UInt32  weight_dis_up4:4;
        RBus_UInt32  weight_dis_up5:4;
        RBus_UInt32  weight_dis_up6:4;
        RBus_UInt32  weight_dis_up7:4;
    };
}d_2d3d_histo_weight_dispread_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_up8:4;
        RBus_UInt32  weight_dis_up9:4;
        RBus_UInt32  weight_dis_up10:4;
        RBus_UInt32  weight_dis_up11:4;
        RBus_UInt32  weight_dis_up12:4;
        RBus_UInt32  weight_dis_up13:4;
        RBus_UInt32  weight_dis_up14:4;
        RBus_UInt32  weight_dis_up15:4;
    };
}d_2d3d_histo_weight_dispread_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr0:4;
        RBus_UInt32  weight_dis_lr1:4;
        RBus_UInt32  weight_dis_lr2:4;
        RBus_UInt32  weight_dis_lr3:4;
        RBus_UInt32  weight_dis_lr4:4;
        RBus_UInt32  weight_dis_lr5:4;
        RBus_UInt32  weight_dis_lr6:4;
        RBus_UInt32  weight_dis_lr7:4;
    };
}d_2d3d_histo_weight_dispread_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr8:4;
        RBus_UInt32  weight_dis_lr9:4;
        RBus_UInt32  weight_dis_lr10:4;
        RBus_UInt32  weight_dis_lr11:4;
        RBus_UInt32  weight_dis_lr12:4;
        RBus_UInt32  weight_dis_lr13:4;
        RBus_UInt32  weight_dis_lr14:4;
        RBus_UInt32  weight_dis_lr15:4;
    };
}d_2d3d_histo_weight_dispread_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr16:4;
        RBus_UInt32  weight_dis_lr17:4;
        RBus_UInt32  weight_dis_lr18:4;
        RBus_UInt32  weight_dis_lr19:4;
        RBus_UInt32  weight_dis_lr20:4;
        RBus_UInt32  weight_dis_lr21:4;
        RBus_UInt32  weight_dis_lr22:4;
        RBus_UInt32  weight_dis_lr23:4;
    };
}d_2d3d_histo_weight_dispread_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_dis_lr24:4;
        RBus_UInt32  weight_dis_lr25:4;
        RBus_UInt32  weight_dis_lr26:4;
        RBus_UInt32  weight_dis_lr27:4;
        RBus_UInt32  weight_dis_lr28:4;
        RBus_UInt32  weight_dis_lr29:4;
        RBus_UInt32  weight_dis_lr30:4;
        RBus_UInt32  weight_dis_lr31:4;
    };
}d_2d3d_histo_weight_dispread_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up2_0:4;
        RBus_UInt32  weight_up2_1:4;
        RBus_UInt32  weight_up2_2:4;
        RBus_UInt32  weight_up2_3:4;
        RBus_UInt32  weight_up2_4:4;
        RBus_UInt32  weight_up2_5:4;
        RBus_UInt32  weight_up2_6:4;
        RBus_UInt32  weight_up2_7:4;
    };
}d_2d3d_histo_weight_up2_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up2_8:4;
        RBus_UInt32  weight_up2_9:4;
        RBus_UInt32  weight_up2_10:4;
        RBus_UInt32  weight_up2_11:4;
        RBus_UInt32  weight_up2_12:4;
        RBus_UInt32  weight_up2_13:4;
        RBus_UInt32  weight_up2_14:4;
        RBus_UInt32  weight_up2_15:4;
    };
}d_2d3d_histo_weight_up2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up3_0:4;
        RBus_UInt32  weight_up3_1:4;
        RBus_UInt32  weight_up3_2:4;
        RBus_UInt32  weight_up3_3:4;
        RBus_UInt32  weight_up3_4:4;
        RBus_UInt32  weight_up3_5:4;
        RBus_UInt32  weight_up3_6:4;
        RBus_UInt32  weight_up3_7:4;
    };
}d_2d3d_histo_weight_up3_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up3_8:4;
        RBus_UInt32  weight_up3_9:4;
        RBus_UInt32  weight_up3_10:4;
        RBus_UInt32  weight_up3_11:4;
        RBus_UInt32  weight_up3_12:4;
        RBus_UInt32  weight_up3_13:4;
        RBus_UInt32  weight_up3_14:4;
        RBus_UInt32  weight_up3_15:4;
    };
}d_2d3d_histo_weight_up3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  color4_y0:4;
        RBus_UInt32  color4_u0:4;
        RBus_UInt32  color4_v0:4;
        RBus_UInt32  color4_y1:4;
        RBus_UInt32  color4_u1:4;
        RBus_UInt32  color4_v1:4;
        RBus_UInt32  weight_01_on_color4:3;
        RBus_UInt32  res1:5;
    };
}d_2d3d_histo_color_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up4_0:4;
        RBus_UInt32  weight_up4_1:4;
        RBus_UInt32  weight_up4_2:4;
        RBus_UInt32  weight_up4_3:4;
        RBus_UInt32  weight_up4_4:4;
        RBus_UInt32  weight_up4_5:4;
        RBus_UInt32  weight_up4_6:4;
        RBus_UInt32  weight_up4_7:4;
    };
}d_2d3d_histo_weight_up4_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up4_8:4;
        RBus_UInt32  weight_up4_9:4;
        RBus_UInt32  weight_up4_10:4;
        RBus_UInt32  weight_up4_11:4;
        RBus_UInt32  weight_up4_12:4;
        RBus_UInt32  weight_up4_13:4;
        RBus_UInt32  weight_up4_14:4;
        RBus_UInt32  weight_up4_15:4;
    };
}d_2d3d_histo_weight_up4_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  color5_y:4;
        RBus_UInt32  color5_u:4;
        RBus_UInt32  color5_v:4;
        RBus_UInt32  res1:20;
    };
}d_2d3d_histo_color_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up5_0:4;
        RBus_UInt32  weight_up5_1:4;
        RBus_UInt32  weight_up5_2:4;
        RBus_UInt32  weight_up5_3:4;
        RBus_UInt32  weight_up5_4:4;
        RBus_UInt32  weight_up5_5:4;
        RBus_UInt32  weight_up5_6:4;
        RBus_UInt32  weight_up5_7:4;
    };
}d_2d3d_histo_weight_up5_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  weight_up5_8:4;
        RBus_UInt32  weight_up5_9:4;
        RBus_UInt32  weight_up5_10:4;
        RBus_UInt32  weight_up5_11:4;
        RBus_UInt32  weight_up5_12:4;
        RBus_UInt32  weight_up5_13:4;
        RBus_UInt32  weight_up5_14:4;
        RBus_UInt32  weight_up5_15:4;
    };
}d_2d3d_histo_weight_up5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  color6_y:8;
        RBus_UInt32  color6_u:8;
        RBus_UInt32  color6_v:8;
        RBus_UInt32  res1:8;
    };
}d_2d3d_histo_color_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_weight_1:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  depth_weight_2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  depth_weight_3:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  depth_weight_4:6;
        RBus_UInt32  res4:2;
    };
}d_2d3d_histo_depth_weight_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_weight_5:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  depth_weight_6:6;
        RBus_UInt32  res2:18;
    };
}d_2d3d_histo_depth_weight_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  margin_1:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  slope_1:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  margin_2:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  slope_2:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_histo_diff_depth_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  margin_3:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  slope_3:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  margin_4:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  slope_4:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_histo_diff_depth_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  margin_5:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  slope_5:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  margin_6:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  slope_6:3;
        RBus_UInt32  res4:5;
    };
}d_2d3d_histo_diff_depth_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temporal_1_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  temporal_1_th_l:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  temporal_1_th_s:3;
        RBus_UInt32  res3:5;
        RBus_UInt32  temporal_2_en:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  temporal_2_th_l:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  temporal_2_th_s:3;
        RBus_UInt32  res6:5;
    };
}d_2d3d_histo_temp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temporal_3_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  temporal_3_th_l:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  temporal_3_th_s:3;
        RBus_UInt32  res3:21;
    };
}d_2d3d_histo_temp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_hfactor:20;
        RBus_UInt32  res1:11;
        RBus_UInt32  su_en:1;
    };
}d_2d3d_histo_su_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_vfactor:20;
        RBus_UInt32  res1:12;
    };
}d_2d3d_histo_su_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_htab_coef1:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_htab_coef0:10;
        RBus_UInt32  res2:6;
    };
}d_2d3d_histo_su_coef0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_htab_coef2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_htab_coef3:10;
        RBus_UInt32  res2:6;
    };
}d_2d3d_histo_su_coef1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_htab_coef4:10;
        RBus_UInt32  res1:22;
    };
}d_2d3d_histo_su_coef2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_vtab_coef1:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_vtab_coef0:10;
        RBus_UInt32  res2:6;
    };
}d_2d3d_histo_su_coef3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_vtab_coef2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  su_scaleup_vtab_coef3:10;
        RBus_UInt32  res2:6;
    };
}d_2d3d_histo_su_coef4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  su_scaleup_vtab_coef4:10;
        RBus_UInt32  res1:22;
    };
}d_2d3d_histo_su_coef5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_sw_mode:1;
        RBus_UInt32  depth_update_en:1;
        RBus_UInt32  res1:30;
    };
}d_2d3d_histo_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_adr:9;
        RBus_UInt32  res1:23;
    };
}d_2d3d_histo_sram_ap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth_dat:8;
        RBus_UInt32  res1:24;
    };
}d_2d3d_histo_sram_dp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_min_en:1;
        RBus_UInt32  max_min_mux:2;
        RBus_UInt32  res1:13;
        RBus_UInt32  depth_min:8;
        RBus_UInt32  depth_max:8;
    };
}d_2d3d_histo_max_min_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iir_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  iir_weight:8;
        RBus_UInt32  res2:20;
    };
}d_2d3d_histo_iir_RBUS;




#endif 


#endif 
