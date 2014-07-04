/**
* @file rbusDFILTERReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2010/12/8
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_DFILTER_REG_H_
#define _RBUS_DFILTER_REG_H_

#include "rbusTypes.h"




// DFILTER Register Address

#define DFILTER_ICH1_DFILTER_PH_SMR_PRING_VADDR    (0xb8023500)
#define DFILTER_ICH1_DFILTER_NRING_MIS_NOS_YPBPR_VADDR  (0xb8023504)
#define DFILTER_ICH2_DFILTER_PH_SMR_PRING_VADDR    (0xb8023508)
#define DFILTER_ICH2_DFILTER_NRING_MIS_NOS_YPBPR_VADDR  (0xb802350c)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======DFILTER register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch1_pring_div:2;
        RBus_UInt32  ch1_thd_pring:3;
        RBus_UInt32  ch1_pring_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_nsmr_div:2;
        RBus_UInt32  ch1_thd_nsmr:3;
        RBus_UInt32  ch1_nsmr_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch1_psmr_div:2;
        RBus_UInt32  ch1_thd_psmr:3;
        RBus_UInt32  ch1_psmr_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch1_ph_div:2;
        RBus_UInt32  ch1_thd_ph:3;
        RBus_UInt32  ch1_ph_en:1;
    };
}ich1_dfilter_ph_smr_pring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  ch1_fight_sel:2;
        RBus_UInt32  ch1_nos_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch1_pr_en:1;
        RBus_UInt32  ch1_pb_en:1;
        RBus_UInt32  ch1_y_en:1;
        RBus_UInt32  ch1_thd_nos:3;
        RBus_UInt32  ch1_nos_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch1_thd_mis:1;
        RBus_UInt32  ch1_mis_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch1_nring_div:2;
        RBus_UInt32  ch1_thd_nring:3;
        RBus_UInt32  ch1_nring_en:1;
    };
}ich1_dfilter_nring_mis_nos_ypbpr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_pring_div:2;
        RBus_UInt32  ch2_thd_pring:3;
        RBus_UInt32  ch2_pring_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_nsmr_div:2;
        RBus_UInt32  ch2_thd_nsmr:3;
        RBus_UInt32  ch2_nsmr_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch2_psmr_div:2;
        RBus_UInt32  ch2_thd_psmr:3;
        RBus_UInt32  ch2_psmr_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch2_ph_div:2;
        RBus_UInt32  ch2_thd_ph:3;
        RBus_UInt32  ch2_ph_en:1;
    };
}ich2_dfilter_ph_smr_pring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  ch2_fight_sel:2;
        RBus_UInt32  ch2_nos_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch2_pr_en:1;
        RBus_UInt32  ch2_pb_en:1;
        RBus_UInt32  ch2_y_en:1;
        RBus_UInt32  ch2_thd_nos:3;
        RBus_UInt32  ch2_nos_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch2_thd_mis:1;
        RBus_UInt32  ch2_mis_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch2_nring_div:2;
        RBus_UInt32  ch2_thd_nring:3;
        RBus_UInt32  ch2_nring_en:1;
    };
}ich2_dfilter_nring_mis_nos_ypbpr_RBUS;





#else //apply LITTLE_ENDIAN


//======DFILTER register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_ph_en:1;
        RBus_UInt32  ch1_thd_ph:3;
        RBus_UInt32  ch1_ph_div:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch1_psmr_en:1;
        RBus_UInt32  ch1_thd_psmr:3;
        RBus_UInt32  ch1_psmr_div:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch1_nsmr_en:1;
        RBus_UInt32  ch1_thd_nsmr:3;
        RBus_UInt32  ch1_nsmr_div:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_pring_en:1;
        RBus_UInt32  ch1_thd_pring:3;
        RBus_UInt32  ch1_pring_div:2;
        RBus_UInt32  res1:2;
    };
}ich1_dfilter_ph_smr_pring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_nring_en:1;
        RBus_UInt32  ch1_thd_nring:3;
        RBus_UInt32  ch1_nring_div:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch1_mis_en:1;
        RBus_UInt32  ch1_thd_mis:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch1_nos_en:1;
        RBus_UInt32  ch1_thd_nos:3;
        RBus_UInt32  ch1_y_en:1;
        RBus_UInt32  ch1_pb_en:1;
        RBus_UInt32  ch1_pr_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch1_nos_sel:1;
        RBus_UInt32  ch1_fight_sel:2;
        RBus_UInt32  res1:9;
    };
}ich1_dfilter_nring_mis_nos_ypbpr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_ph_en:1;
        RBus_UInt32  ch2_thd_ph:3;
        RBus_UInt32  ch2_ph_div:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch2_psmr_en:1;
        RBus_UInt32  ch2_thd_psmr:3;
        RBus_UInt32  ch2_psmr_div:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch2_nsmr_en:1;
        RBus_UInt32  ch2_thd_nsmr:3;
        RBus_UInt32  ch2_nsmr_div:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_pring_en:1;
        RBus_UInt32  ch2_thd_pring:3;
        RBus_UInt32  ch2_pring_div:2;
        RBus_UInt32  res1:2;
    };
}ich2_dfilter_ph_smr_pring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_nring_en:1;
        RBus_UInt32  ch2_thd_nring:3;
        RBus_UInt32  ch2_nring_div:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  ch2_mis_en:1;
        RBus_UInt32  ch2_thd_mis:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  ch2_nos_en:1;
        RBus_UInt32  ch2_thd_nos:3;
        RBus_UInt32  ch2_y_en:1;
        RBus_UInt32  ch2_pb_en:1;
        RBus_UInt32  ch2_pr_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch2_nos_sel:1;
        RBus_UInt32  ch2_fight_sel:2;
        RBus_UInt32  res1:9;
    };
}ich2_dfilter_nring_mis_nos_ypbpr_RBUS;


#endif







#endif //_RBUS_DFILTER_REG_H_
