/**
* @file rbusColorReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/11/25
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_COLOR_REG_H_
#define _RBUS_COLOR_REG_H_

#include "rbusTypes.h"



//  COLOR Register Address



#define  COLOR_D_VC_GLOBAL_CTRL_VADDR 		(0xb802a000)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======COLOR register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_vc_en:1;
        RBus_UInt32  m_vc_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  highlightwin_inv:1;
        RBus_UInt32  res2:11;
        RBus_UInt32  icm_dcc_swap:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  s_sharp_en:1;
        RBus_UInt32  s_icm_en:1;
        RBus_UInt32  s_dcti_en:1;
        RBus_UInt32  dummy1802a000_9:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  m_edgesmooth_en:1;
        RBus_UInt32  m_sharp_en:1;
        RBus_UInt32  m_icm_en:1;
        RBus_UInt32  m_dcti_en:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dcc_en:1;
    };
}d_vc_global_ctrl_RBUS;

#else //apply LITTLE_ENDIAN

//======COLOR register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dcc_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  m_dcti_en:1;
        RBus_UInt32  m_icm_en:1;
        RBus_UInt32  m_sharp_en:1;
        RBus_UInt32  m_edgesmooth_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  dummy1802a000_9:1;
        RBus_UInt32  s_dcti_en:1;
        RBus_UInt32  s_icm_en:1;
        RBus_UInt32  s_sharp_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  icm_dcc_swap:1;
        RBus_UInt32  res4:11;
        RBus_UInt32  highlightwin_inv:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  m_vc_en:1;
        RBus_UInt32  s_vc_en:1;
    };
}d_vc_global_ctrl_RBUS;




#endif 


#endif 
