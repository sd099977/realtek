/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/
#ifndef __EMCU_H__
#define __EMCU_H__

#define _ZERO   						(0x00)
#define _BIT0   						(0x01UL)
#define _BIT1   						(0x02UL)
#define _BIT2   						(0x04UL)
#define _BIT3   						(0x08UL)
#define _BIT4   						(0x10UL)
#define _BIT5   						(0x20UL)
#define _BIT6   						(0x40UL)
#define _BIT7   						(0x80UL)
#define _BIT8   						(0x0100UL)
#define _BIT9   						(0x0200UL)
#define _BIT10  						(0x0400UL)
#define _BIT11  						(0x0800UL)
#define _BIT12  						(0x1000UL)
#define _BIT13  						(0x2000UL)
#define _BIT14  						(0x4000UL)
#define _BIT15  						(0x8000UL)
#define _BIT16   						(0x00010000UL)
#define _BIT17  						(0x00020000UL)
#define _BIT18   						(0x00040000UL)
#define _BIT19   						(0x00080000UL)
#define _BIT20   						(0x00100000UL)
#define _BIT21   						(0x00200000UL)
#define _BIT22   						(0x00400000UL)
#define _BIT23   						(0x00800000UL)
#define _BIT24   						(0x01000000UL)
#define _BIT25   						(0x02000000UL)
#define _BIT26  						(0x04000000UL)
#define _BIT27  						(0x08000000UL)
#define _BIT28  						(0x10000000UL)
#define _BIT29  						(0x20000000UL)
#define _BIT30  						(0x40000000UL)
#define _BIT31  						(0x80000000UL)

#define IMAGE_SIZE_BLK      (16)	                //size  8K
#define IMAGE_SIZE_WOW_BLK  (16)	                //size  8K {physical is 12k but use 8k here }
#define IMAGE_SIZE_K        (8)	                //size  8K
#define IMAGE_SIZE_WOW_K    (8)	                //size  8K {physical is 12k but use 8k here }
#define IMAGE_SIZE          (1024*IMAGE_SIZE_K)	//size  8K
#define IMAGE_SIZE_WOW      (1024*IMAGE_SIZE_WOW_K)	//size  8K
#define EMMC_EMCU_BLK       0xE0    //ecpu.bin located at eMMC blk(addr 0x1c000 byte)
#define EMMC_EMCU_BLK_WOW   0xF0    //ecpu_wow.bin located at eMMC blk(addr 0x1E000 byte)

#if 0
#define EMMC_SRAM_BUF       (0xB8075000)
#define EMMC_SRAM_BUF_WOW   (0xB8077000)
#else
#define EMMC_SRAM_BUF       (0xB8076000)
#define EMMC_SRAM_BUF_WOW   (0xB8078000)
#endif

#define EMCU_RESET_REG  0xB8060034
#define EMCU_CLKEN_REG  0xb8060044


#define RELEASE_EMCU_TOP()  \
        rtd_outl(EMCU_RESET_REG, rtd_inl(EMCU_RESET_REG)| RSTN_EMCU_TOP)


/* 0x1806_0034 */
#define RSTN_OSC        _BIT12
#define RSTN_EMCU_TOP   _BIT10
#define RSTN_EMCU_CORE  _BIT9
#define RSTN_ALU        _BIT3

/* 0x1806_0044 */
#define CLKEN_OSC       _BIT12
#define CLKEN_EMCU_CORE _BIT9
#define CLKEN_ALU       _BIT3

#define EMCU_BASE (0xb8060400)
#define EMCU1_BASE (0xb8016800)

#define EMCU_WRAPPER_8051               (EMCU_BASE+0x00)  //0x18060400
#define EMCU_DEBUG_8051                 (EMCU_BASE+0x10)  //0x18060410
#define EMCU_MEM_RME                    (EMCU_BASE+0x14)  //0x18060414
#define EMCU_MEM_RM                     (EMCU_BASE+0x20)  //0x18060420
#define EMCU_MEM_LIGHT_SLEEP            (EMCU_BASE+0x24)  //0x18060424
#define EMCU_DEBUG_8051_4               (EMCU_BASE+0x28)  //0x18060428
#define EMCU_SYSTEM_CPU_PROGRAM_ENABLE  (EMCU_BASE+0x30)  //0x18060430
#define EMCU_IMEM_CONTROL               (EMCU_BASE+0x34)  //0x18060434
#define EMCU_IMEM_DATA                  (EMCU_BASE+0x38)  //0x18060438
#define EMCU_DMEM_CONTROL               (EMCU_BASE+0x3C)  //0x1806043C
#define EMCU_DMEM_DATA                  (EMCU_BASE+0x40)  //0x18060440

#define EMCU1_WRAPPER_8051               (EMCU1_BASE+0x00)  //0x18016800
#define EMCU1_DEBUG_8051                 (EMCU1_BASE+0x10)  //0x18016810
#define EMCU1_MEM_RME                    (EMCU1_BASE+0x14)  //0x18016814
#define EMCU1_MEM_RM                     (EMCU1_BASE+0x20)  //0x18016820
#define EMCU1_MEM_LIGHT_SLEEP            (EMCU1_BASE+0x24)  //0x18016824
#define EMCU1_DEBUG_8051_4               (EMCU1_BASE+0x28)  //0x18016828
#define EMCU1_SYSTEM_CPU_PROGRAM_ENABLE  (EMCU1_BASE+0x30)  //0x18016830
#define EMCU1_IMEM_CONTROL               (EMCU1_BASE+0x34)  //0x18016834
#define EMCU1_IMEM_DATA                  (EMCU1_BASE+0x38)  //0x18016838
#define EMCU1_DMEM_CONTROL               (EMCU1_BASE+0x3C)  //0x1801683C
#define EMCU1_DMEM_DATA                  (EMCU1_BASE+0x40)  //0x18016840

#define EMCU_ST_IP                      (EMCU_BASE+0x50)  //0x18060450
#define EMCU_ST_IE                      (EMCU_BASE+0x54)  //0x18060454
#define EMCU_BIST_MODE                  (EMCU_BASE+0x60)  //0x18060460
#define EMCU_BIST_DONE                  (EMCU_BASE+0x64)  //0x18060464
#define EMCU_BIST_FAIL_GROUP            (EMCU_BASE+0x68)  //0x18060468
#define EMCU_BIST_MCU_DMEM_FAIL         (EMCU_BASE+0x6C)  //0x1806046C
#define EMCU_BIST_MCU_IRAM_FAIL         (EMCU_BASE+0x74)  //0x18060474
#define EMCU_BIST_MCU_ALWAYS_ON_FAIL    (EMCU_BASE+0x78)  //0x18060478
#define EMCU_DRF_MODE                   (EMCU_BASE+0x7C)  //0x1806047C
#define EMCU_DRF_RESUME                 (EMCU_BASE+0x80)  //0x18060480
#define MCU_DRF_DONE                    (EMCU_BASE+0x84)  //0x18060484
#define EMCU_DRF_PAEUSE                 (EMCU_BASE+0x88)  //0x18060488
#define EMCU_DRF_FAIL_GROUP             (EMCU_BASE+0x8C)  //0x1806048C
#define EMCU_DRF_MCU_DMEM_FAIL          (EMCU_BASE+0x90)  //0x18060490
#define EMCU_DRF_MCU_IRAM_FAIL          (EMCU_BASE+0x98)  //0x18060498
#define EMCU_DRF_MCU_ALWAYS_ON_FAIL     (EMCU_BASE+0x9C)  //0x1806049C
#define EMCU_BISR_SECOND_RUN_EN         (EMCU_BASE+0xA0)  //0x180604A0
#define EMCU_BISR_FAIL_GROUP            (EMCU_BASE+0xA4)  //0x180604A4
#define EMCU_BISR_MCU_IMEM_STATUS       (EMCU_BASE+0xA8)  //0x180604A8
#define EMCU_DRF_BISR_MODE              (EMCU_BASE+0xAC)  //0x180604AC
#define EMCU_DRF_BISR_RESUME            (EMCU_BASE+0xB0)  //0x180604B0
#define EMCU_DRF_BISR_DONE              (EMCU_BASE+0xB4)  //0x180604B4
#define EMCU_DRF_BISR_PAUSE             (EMCU_BASE+0xB8)  //0x180604B8
#define EMCU_DRF_BISR_FAIL_GROUP        (EMCU_BASE+0xBC)  //0x180604BC
#define EMCU_DRF_BISR_MCU_IMEM_FAIL     (EMCU_BASE+0xC0)  //0x180604C0

#define BLOCK_BAD               0x00
#define BLOCK_HWSETTING         0x23 // tag for Certificate/Params Area/Aux code image in Sirius
#define BLOCK_EMCU							0x51 // tag for emcu firmware

//
#define EMCU_IMAGE_START_BLOCK_NO	0x5		//ecpu.bin store at block0x5
#define EMCU_CERT_PAGE_COUNT	0x1		//cert need 1page

#endif //?#define __EMCU_H__
