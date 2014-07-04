/************************************************************************
 *
 *  md_reg.h
 *
 *  Common header of MD registers for internal ROM
 *
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/
#include "auto_config.h"

#if defined(CONFIG_CHIP_MACARTHUR2)
#include "md_reg_mac2.h"
#elif defined(CONFIG_CHIP_SIRIUS)
#include "md_reg_sirius.h"
#else	/* default */
#include "md_reg_mac2.h"
#endif

