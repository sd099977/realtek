#ifndef __PCB_H__
#define __PCB_H__

#include <platform_lib/board/pcb_mgr.h>

/* TV001 *//*QFP176*/
#if defined(CONFIG_BOARD_298X_TV001_QFP176_EMMC)
	#include "pcb/pcb_rtd298x_tv001_qfp176.h"
#elif defined(CONFIG_BOARD_298X_TV001_QFP176_NAND)
	#include "pcb/pcb_rtd298x_tv001_qfp176_nand.h"
#elif defined(CONFIG_BOARD_298X_TV001_QFP176_V3_EMMC)
	#include "pcb/pcb_rtd298x_tv001_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV001_QFP176_V3_NAND)
	#include "pcb/pcb_rtd298x_tv001_qfp176_v3_nand.h"

/* TV001 *//*BGA459*/
#elif defined(CONFIG_BOARD_298X_TV001_BGA459_EMMC)
	#include "pcb/pcb_rtd298x_tv001_bga459.h"
#elif defined(CONFIG_BOARD_298X_TV001_BGA459_NAND)
	#include "pcb/pcb_rtd298x_tv001_bga459_nand.h"

/* BOX001 *//*BGA459*/	
#elif defined(CONFIG_BOARD_18X5_BOX001_BGA459_EMMC)
	#include "pcb/pcb_rtd18x5_box001_bga459.h"	

/* customers */
#elif defined(CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC)
	#include "pcb/pcb_rtd298x_tv010_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV010_OVERSEAS_QFP176_V3_EMMC)
	#include "pcb/pcb_rtd298x_tv010_overseas_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV010_OVERSEAS_BGA459)
	#include "pcb/pcb_rtd298x_tv010_overseas_bga459.h"
#elif defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)
	#include "pcb/pcb_rtd298x_tv013_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV030_QFP176_EMMC)
	#include "pcb/pcb_rtd298x_tv030_qfp176.h"	
#elif defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC)
    #include "pcb/pcb_rtd298x_tv035_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)
	#include "pcb/pcb_rtd298x_tv035_bga459.h"
#elif defined(CONFIG_BOARD_298X_TV003_QFP176_NAND)|| defined (CONFIG_BOARD_298X_TV003_QFP176_V2_NAND)
	#include "pcb/pcb_rtd298x_tv003_qfp176_nand.h"
#elif defined (CONFIG_BOARD_298X_TV003_OEM_QFP176_V2_NAND)
	#include "pcb/pcb_rtd298x_tv003_oem_qfp176_nand.h"
#elif defined(CONFIG_BOARD_298X_TV003_MEMC_QFP176_V3_NAND)
	#include "pcb/pcb_rtd298x_tv003_memc_qfp176_v3_nand.h"
#elif defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)
	#include "pcb/pcb_rtd298x_tv015_qfp176_v3.h"
#elif defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	#include "pcb/pcb_rtd298x_tv015_qfp176_v3_ver1.h"
#elif defined(CONFIG_BOARD_298X_TV038_QFP176_V3_EMMC_VER1)
	#include "pcb/pcb_rtd298x_tv038_qfp176_v3_ver1.h"
#elif defined(CONFIG_BOARD_298X_TV032_ATSC_QFP176_NAND)
	#include "pcb/pcb_rtd298x_qfp176_TV032_ATSC_nand_v1.h"
#else
	#error "pcbMgr no support this board."
#endif

#endif	// __PCB_H__
