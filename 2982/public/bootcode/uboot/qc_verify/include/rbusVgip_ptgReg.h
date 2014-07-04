/**
* @file rbusVgip_ptgReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/30
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_VGIP_PTG_REG_H_
#define _RBUS_VGIP_PTG_REG_H_

#include "rbusTypes.h"




// VGIP_PTG Register Address

#define VGIP_PTG_PTG_CTRL_VADDR                    (0xb80222c0)
#define VGIP_PTG_PTG_C0Y_CB_CR_VADDR               (0xb80222c4)
#define VGIP_PTG_PTG_C1Y_CB_CR_VADDR               (0xb80222c8)
#define VGIP_PTG_PTG_C2Y_CB_CR_VADDR               (0xb80222cc)
#define VGIP_PTG_PTG_C3Y_CB_CR_VADDR               (0xb80222d0)
#define VGIP_PTG_PTG_C4Y_CB_CR_VADDR               (0xb80222d4)
#define VGIP_PTG_PTG_C5Y_CR_CB_VADDR               (0xb80222d8)
#define VGIP_PTG_PTG_C6Y_CB_CR_VADDR               (0xb80222dc)
#define VGIP_PTG_PTG_C7Y_CB_CR_VADDR               (0xb80222e0)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======VGIP_PTG register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  color_bar_mode_en:1;
        RBus_UInt32  res2:15;
        RBus_UInt32  mask_one_eye_en:1;
        RBus_UInt32  mask_one_eye_left:1;
        RBus_UInt32  color_bar_vertical_mode:1;
        RBus_UInt32  color_bar_interlaced_mode:1;
        RBus_UInt32  color_bar_3d_mode:1;
        RBus_UInt32  color_num:2;
    };
}ptg_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c0y_92b:8;
        RBus_UInt32  i_c0cr_92b:8;
        RBus_UInt32  i_c0cb_92b:8;
    };
}ptg_c0y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c1y_92b:8;
        RBus_UInt32  i_c1cr_92b:8;
        RBus_UInt32  i_c1cb_92b:8;
    };
}ptg_c1y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c2y_92b:8;
        RBus_UInt32  i_c2cr_92b:8;
        RBus_UInt32  i_c2cb_92b:8;
    };
}ptg_c2y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c3y_92b:8;
        RBus_UInt32  i_c3cr_92b:8;
        RBus_UInt32  i_c3cb_92b:8;
    };
}ptg_c3y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c4y_92b:8;
        RBus_UInt32  i_c4cr_92b:8;
        RBus_UInt32  i_c4cb_92b:8;
    };
}ptg_c4y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c5y_92b:8;
        RBus_UInt32  i_c5cr_92b:8;
        RBus_UInt32  i_c5cb_92b:8;
    };
}ptg_c5y_cr_cb_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c6y_92b:8;
        RBus_UInt32  i_c6cr_92b:8;
        RBus_UInt32  i_c6cb_92b:8;
    };
}ptg_c6y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  i_c7y_92b:8;
        RBus_UInt32  i_c7cr_92b:8;
        RBus_UInt32  i_c7cb_92b:8;
    };
}ptg_c7y_cb_cr_RBUS;





#else //apply LITTLE_ENDIAN


//======VGIP_PTG register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  color_num:2;
        RBus_UInt32  color_bar_3d_mode:1;
        RBus_UInt32  color_bar_interlaced_mode:1;
        RBus_UInt32  color_bar_vertical_mode:1;
        RBus_UInt32  mask_one_eye_left:1;
        RBus_UInt32  mask_one_eye_en:1;
        RBus_UInt32  res2:15;
        RBus_UInt32  color_bar_mode_en:1;
        RBus_UInt32  res1:9;
    };
}ptg_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c0cb_92b:8;
        RBus_UInt32  i_c0cr_92b:8;
        RBus_UInt32  i_c0y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c0y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c1cb_92b:8;
        RBus_UInt32  i_c1cr_92b:8;
        RBus_UInt32  i_c1y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c1y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c2cb_92b:8;
        RBus_UInt32  i_c2cr_92b:8;
        RBus_UInt32  i_c2y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c2y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c3cb_92b:8;
        RBus_UInt32  i_c3cr_92b:8;
        RBus_UInt32  i_c3y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c3y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c4cb_92b:8;
        RBus_UInt32  i_c4cr_92b:8;
        RBus_UInt32  i_c4y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c4y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c5cb_92b:8;
        RBus_UInt32  i_c5cr_92b:8;
        RBus_UInt32  i_c5y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c5y_cr_cb_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c6cb_92b:8;
        RBus_UInt32  i_c6cr_92b:8;
        RBus_UInt32  i_c6y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c6y_cb_cr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_c7cb_92b:8;
        RBus_UInt32  i_c7cr_92b:8;
        RBus_UInt32  i_c7y_92b:8;
        RBus_UInt32  res1:8;
    };
}ptg_c7y_cb_cr_RBUS;


#endif







#endif //_RBUS_VGIP_PTG_REG_H_

