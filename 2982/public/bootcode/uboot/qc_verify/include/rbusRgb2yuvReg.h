/**
* @file rbusRgb2yuvReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/11/25
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_RGB2YUV_REG_H_
#define _RBUS_RGB2YUV_REG_H_

#include "rbusTypes.h"



//  RGB2YUV Register Address



#define  RGB2YUV_ICH1_RGB2YUV_CTRL_VADDR 		(0xb8023000)
#define  RGB2YUV_ICH2_RGB2YUV_CTRL_VADDR 		(0xb8023004)
#define  RGB2YUV_TAB1_M1_VADDR 		(0xb8023008)
#define  RGB2YUV_TAB1_M2_VADDR 		(0xb802300c)
#define  RGB2YUV_TAB1_M3_VADDR 		(0xb8023010)
#define  RGB2YUV_TAB1_YO_AND_Y_GAIN_VADDR 		(0xb8023014)
#define  RGB2YUV_TAB2_M1_VADDR 		(0xb8023018)
#define  RGB2YUV_TAB2_M2_VADDR 		(0xb802301c)
#define  RGB2YUV_TAB2_M3_VADDR 		(0xb8023020)
#define  RGB2YUV_TAB2_YO_AND_Y_GAIN_VADDR 		(0xb8023024)
#define  RGB2YUV_ICH1_422TO444_CTRL_VADDR 		(0xb8023028)
#define  RGB2YUV_ICH2_422TO444_CTRL_VADDR 		(0xb802302c)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======RGB2YUV register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  sel_2x_gain:1;
        RBus_UInt32  sel_y_gain:1;
        RBus_UInt32  matrix_bypass:1;
        RBus_UInt32  sel_uv_off:1;
        RBus_UInt32  set_uv_out_offset:1;
        RBus_UInt32  set_r_in_offset:1;
        RBus_UInt32  sel_rgb:1;
        RBus_UInt32  sel_sign:1;
        RBus_UInt32  sel_table:1;
        RBus_UInt32  en_rgb2yuv:2;
    };
}ich1_rgb2yuv_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  truncationctrl_en:1;
        RBus_UInt32  sel_2x_gain:1;
        RBus_UInt32  sel_y_gain:1;
        RBus_UInt32  matrix_bypass:1;
        RBus_UInt32  sel_uv_off:1;
        RBus_UInt32  set_uv_out_offset:1;
        RBus_UInt32  set_r_in_offset:1;
        RBus_UInt32  sel_rgb:1;
        RBus_UInt32  sel_sign:1;
        RBus_UInt32  sel_table:1;
        RBus_UInt32  en_rgb2yuv:2;
    };
}ich2_rgb2yuv_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m13:11;
        RBus_UInt32  m12:10;
        RBus_UInt32  m11:11;
    };
}tab1_m1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  m23:9;
        RBus_UInt32  m22:10;
        RBus_UInt32  m21:10;
    };
}tab1_m2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  m33:10;
        RBus_UInt32  m32:11;
        RBus_UInt32  m31:10;
    };
}tab1_m3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  y_gain:9;
        RBus_UInt32  yo_odd:11;
        RBus_UInt32  yo_even:11;
    };
}tab1_yo_and_y_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m13:11;
        RBus_UInt32  m12:10;
        RBus_UInt32  m11:11;
    };
}tab2_m1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  m23:9;
        RBus_UInt32  m22:10;
        RBus_UInt32  m21:10;
    };
}tab2_m2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  m33:10;
        RBus_UInt32  m32:11;
        RBus_UInt32  m31:10;
    };
}tab2_m3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  y_gain:9;
        RBus_UInt32  yo_odd:11;
        RBus_UInt32  yo_even:11;
    };
}tab2_yo_and_y_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  dup:1;
        RBus_UInt32  en_422to444:1;
    };
}ich1_422to444_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  dup:1;
        RBus_UInt32  en_422to444:1;
    };
}ich2_422to444_ctrl_RBUS;

#else //apply LITTLE_ENDIAN

//======RGB2YUV register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_rgb2yuv:2;
        RBus_UInt32  sel_table:1;
        RBus_UInt32  sel_sign:1;
        RBus_UInt32  sel_rgb:1;
        RBus_UInt32  set_r_in_offset:1;
        RBus_UInt32  set_uv_out_offset:1;
        RBus_UInt32  sel_uv_off:1;
        RBus_UInt32  matrix_bypass:1;
        RBus_UInt32  sel_y_gain:1;
        RBus_UInt32  sel_2x_gain:1;
        RBus_UInt32  res1:21;
    };
}ich1_rgb2yuv_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_rgb2yuv:2;
        RBus_UInt32  sel_table:1;
        RBus_UInt32  sel_sign:1;
        RBus_UInt32  sel_rgb:1;
        RBus_UInt32  set_r_in_offset:1;
        RBus_UInt32  set_uv_out_offset:1;
        RBus_UInt32  sel_uv_off:1;
        RBus_UInt32  matrix_bypass:1;
        RBus_UInt32  sel_y_gain:1;
        RBus_UInt32  sel_2x_gain:1;
        RBus_UInt32  truncationctrl_en:1;
        RBus_UInt32  res1:20;
    };
}ich2_rgb2yuv_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m11:11;
        RBus_UInt32  m12:10;
        RBus_UInt32  m13:11;
    };
}tab1_m1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m21:10;
        RBus_UInt32  m22:10;
        RBus_UInt32  m23:9;
        RBus_UInt32  res1:3;
    };
}tab1_m2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m31:10;
        RBus_UInt32  m32:11;
        RBus_UInt32  m33:10;
        RBus_UInt32  res1:1;
    };
}tab1_m3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  yo_even:11;
        RBus_UInt32  yo_odd:11;
        RBus_UInt32  y_gain:9;
        RBus_UInt32  res1:1;
    };
}tab1_yo_and_y_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m11:11;
        RBus_UInt32  m12:10;
        RBus_UInt32  m13:11;
    };
}tab2_m1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m21:10;
        RBus_UInt32  m22:10;
        RBus_UInt32  m23:9;
        RBus_UInt32  res1:3;
    };
}tab2_m2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m31:10;
        RBus_UInt32  m32:11;
        RBus_UInt32  m33:10;
        RBus_UInt32  res1:1;
    };
}tab2_m3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  yo_even:11;
        RBus_UInt32  yo_odd:11;
        RBus_UInt32  y_gain:9;
        RBus_UInt32  res1:1;
    };
}tab2_yo_and_y_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_422to444:1;
        RBus_UInt32  dup:1;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  res1:29;
    };
}ich1_422to444_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_422to444:1;
        RBus_UInt32  dup:1;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  res1:29;
    };
}ich2_422to444_ctrl_RBUS;




#endif 


#endif 
