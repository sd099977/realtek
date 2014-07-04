#define VD_BIST_ADDR         0xb80037a0
#define VD_BIST_DONE_ADDR    0xb80037a4
#define VD_BIST_FAIL_ADDR    0xb80037a8
#define VD_BIST_SET_BIT      0x1F   //[4:0]
#define VD_BIST_DONE_BIT     0x1F   //[4:0]
#define VD_BIST_FAIL_BIT     0x1F   //[4:0]

#define AE_BIST_ADDR         0x18000500
#define AE_BIST_DONE_ADDR    0x180020E0
#define AE_BIST_FAIL_ADDR    0x180020E0
#define AE_BIST_SET_BIT      0x9   //[3],[0]:write data
#define AE_BIST_DONE_BIT    0x1   //[0]
#define AE_BIST_FAIL_BIT    0x1E   //[4:1]

#define DISP2TVE_BIST_ADDR      0x180260a0
#define DISP2TVE_BIST_DONE_ADDR 0x180260a0
#define DISP2TVE_BIST_FAIL_ADDR 0x180260a0
#define DISP2TVE_BIST_SET_BIT   0x1    //[0]
#define DISP2TVE_BIST_DONE_BIT 0x2    //[1]
#define DISP2TVE_BIST_FAIL_BIT 0x4    //[2]

#define DISP2TVE2_BIST_ADDR      0x180260a4
#define DISP2TVE2_BIST_DONE_ADDR 0x180260a4
#define DISP2TVE2_BIST_FAIL_ADDR 0x180260a4
#define DISP2TVE2_BIST_SET_BIT   0x1    //[0]
#define DISP2TVE2_BIST_DONE_BIT 0x2    //[1]
#define DISP2TVE2_BIST_FAIL_BIT 0x4    //[2]

#define DISP2TVE3_BIST_ADDR      0x180260a8
#define DISP2TVE3_BIST_DONE_ADDR 0x180260a8
#define DISP2TVE3_BIST_FAIL_ADDR 0x180260a8
#define DISP2TVE3_BIST_SET_BIT   0x1    //[0]
#define DISP2TVE3_BIST_DONE_BIT 0x2    //[1]
#define DISP2TVE3_BIST_FAIL_BIT 0x4    //[2]

#define DISPD_BIST_ADDR      0x18029f00
#define DISPD_BIST_DONE_ADDR 0x18029f04
#define DISPD_BIST_FAIL_ADDR 0x18029f08
#define DISPD_BIST_SET_BIT   0x3FFFFFF //[25:0]
#define DISPD_BIST_DONE_BIT  0x3FFFFFF //[25:0]
#define DISPD_BIST_FAIL_BIT  0x3FFFFFF //[25:0]

#define DISPI_BIST_ADDR      0x18025f00
#define DISPI_BIST_DONE_ADDR 0x18025f04
#define DISPI_BIST_FAIL_ADDR 0x18025f08
#define DISPI_BIST_SET_BIT   0xFFF //[11:0]
#define DISPI_BIST_DONE_BIT  0xFFF //[11:0]
#define DISPI_BIST_FAIL_BIT  0xFFF //[11:0]

#define DISPM_BIST_ADDR      0x180274a0
#define DISPM_BIST_DONE_ADDR 0x180274a4
#define DISPM_BIST_FAIL_ADDR 0x180274a8
#define DISPM_BIST_SET_BIT   0x2F    //[5,3:0]
#define DISPM_BIST_DONE_BIT 0x2F    //[5,3:0]
#define DISPM_BIST_FAIL_BIT 0x2F    //[5,3:0]

#define VODMA_BIST_ADDR      0x18005044
#define VODMA_BIST_DONE_ADDR 0x18005048
#define VODMA_BIST_FAIL_ADDR 0x1800504c
#define VODMA_BIST_SET_BIT   0x1    //[0]
#define VODMA_BIST_DONE_BIT  0x1    //[0]
#define VODMA_BIST_FAIL_BIT  0x1    //[0]

#define VODMA2_BIST_ADDR      0x18005444
#define VODMA2_BIST_DONE_ADDR 0x18005448
#define VODMA2_BIST_FAIL_ADDR 0x1800544c
#define VODMA2_BIST_SET_BIT   0x1    //[0]
#define VODMA2_BIST_DONE_BIT  0x1    //[0]
#define VODMA2_BIST_FAIL_BIT  0x1    //[0]

#define VODMA3_BIST_ADDR      0x18005844
#define VODMA3_BIST_DONE_ADDR 0x18005848
#define VODMA3_BIST_FAIL_ADDR 0x1800584c
#define VODMA3_BIST_SET_BIT   0x1    //[0]
#define VODMA3_BIST_DONE_BIT  0x1    //[0]
#define VODMA3_BIST_FAIL_BIT  0x1    //[0]

#define VODMA4_BIST_ADDR      0x18005c70
#define VODMA4_BIST_DONE_ADDR 0x18005c74
#define VODMA4_BIST_FAIL_ADDR 0x18005c74
#define VODMA4_BIST_SET_BIT   0x80000000    //[31]
#define VODMA4_BIST_DONE_BIT  0x80000000    //[31]
#define VODMA4_BIST_FAIL_BIT  0x40000000    //[30]

#define ACPU_BIST_ADDR       0x18000508
#define ACPU_BIST_DONE_ADDR  0x18002150
#define ACPU_BIST_FAIL_ADDR  0x18002150
#define ACPU_BIST_SET_BIT    0x3    //[1],[0]:write data
#define ACPU_BIST_DONE_BIT   0x1    //[0]
#define ACPU_BIST_FAIL_BIT   0xE    //[3:1]

#define AUDIO_BIST_ADDR      0x18006c00
#define AUDIO_BIST_DONE_ADDR 0x18006c04
#define AUDIO_BIST_FAIL_ADDR 0x18006c08
#define AUDIO_BIST_SET_BIT   0x3FF  //[9:0]
#define AUDIO_BIST_DONE_BIT  0x3FF  //[9:0]
#define AUDIO_BIST_FAIL_BIT  0x3FF  //[9:0]

#define CP_BIST_ADDR         0x18000500
#define CP_BIST_DONE_ADDR    0x180151D4
#define CP_BIST_FAIL_ADDR    0x180151D4
#define CP_BIST_SET_BIT      0x3    //[1],[0]:write data
#define CP_BIST_DONE_BIT     0x1    //[0]
#define CP_BIST_FAIL_BIT     0x7E    //[6:1]

#define DCPHY_BIST_ADDR      0x18008fc0
#define DCPHY_BIST_DONE_ADDR 0x18008fc4
#define DCPHY_BIST_FAIL_ADDR 0x18008fc8
#define DCPHY_BIST_SET_BIT   0x3F   //[5:0]
#define DCPHY_BIST_DONE_BIT  0x3F   //[5:0]
#define DCPHY_BIST_FAIL_BIT  0x3F   //[5:0]

#define DDC_BIST_ADDR        0x18061A78
#define DDC_BIST_DONE_ADDR   0x18061A7C
#define DDC_BIST_FAIL_ADDR   0x18061A80
#define DDC_BIST_SET_BIT     0x1    //[0]
#define DDC_BIST_DONE_BIT    0x1    //[0]
#define DDC_BIST_FAIL_BIT    0x1    //[0]

#define DDC2_BIST_ADDR        0x18061B78
#define DDC2_BIST_DONE_ADDR   0x18061B7C
#define DDC2_BIST_FAIL_ADDR   0x18061B80
#define DDC2_BIST_SET_BIT     0x1    //[0]
#define DDC2_BIST_DONE_BIT    0x1    //[0]
#define DDC2_BIST_FAIL_BIT    0x1    //[0]

#define DDC3_BIST_ADDR        0x18061C78
#define DDC3_BIST_DONE_ADDR   0x18061C7C
#define DDC3_BIST_FAIL_ADDR   0x18061C80
#define DDC3_BIST_SET_BIT     0x1    //[0]
#define DDC3_BIST_DONE_BIT    0x1    //[0]
#define DDC3_BIST_FAIL_BIT    0x1    //[0]

#define DDC4_BIST_ADDR        0x18061D78
#define DDC4_BIST_DONE_ADDR   0x18061D7C
#define DDC4_BIST_FAIL_ADDR   0x18061D80
#define DDC4_BIST_SET_BIT     0x1    //[0]
#define DDC4_BIST_DONE_BIT    0x1    //[0]
#define DDC4_BIST_FAIL_BIT    0x1    //[0]

#define ETN_BIST_ADDR        0x18000508
#define ETN_BIST_DONE_ADDR   0x18031190
#define ETN_BIST_FAIL_ADDR   0x18031190
#define ETN_BIST_SET_BIT     0x2001    //[13],[0]:write data
#define ETN_BIST_DONE_BIT    0x1    //[0]
#define ETN_BIST_FAIL_BIT    0xE    //[3:1]

#define GETN_BIST_ADDR        0x18016700
#define GETN_BIST_DONE_ADDR   0x18016704
#define GETN_BIST_FAIL_ADDR   0x18016708
#define GETN_BIST_SET_BIT     0x7    //[2:0]
#define GETN_BIST_DONE_BIT    0x7    //[2:0]
#define GETN_BIST_FAIL_BIT    0x7    //[2:0]

#define GETN_MCU_BIST_ADDR        0x18016860
#define GETN_MCU_BIST_DONE_ADDR   0x18016864
#define GETN_MCU_BIST_FAIL_ADDR   0x18016868
#define GETN_MCU_BIST_SET_BIT     0x7    //[2:0]
#define GETN_MCU_BIST_DONE_BIT    0x7    //[2:0]
#define GETN_MCU_BIST_FAIL_BIT    0x7    //[2:0]

#define HDMI_BIST_ADDR       0x18007184
#define HDMI_BIST_DONE_ADDR  0x18007188
#define HDMI_BIST_FAIL_ADDR  0x1800718c
#define HDMI_BIST_SET_BIT    0x3    //[1:0]
#define HDMI_BIST_DONE_BIT   0x3    //[1:0]
#define HDMI_BIST_FAIL_BIT   0x3    //[1:0]

#define HDMITX_BIST_ADDR       0x18000500
#define HDMITX_BIST_DONE_ADDR  0x1800d284
#define HDMITX_BIST_FAIL_ADDR  0x1800d284
#define HDMITX_BIST_SET_BIT    0x101    //[8],[0]:write data
#define HDMITX_BIST_DONE_BIT   0x1    //[0]
#define HDMITX_BIST_FAIL_BIT   0x2    //[1]

#define HDMITX2_BIST_ADDR       0x18000500
#define HDMITX2_BIST_DONE_ADDR  0x1800d28c
#define HDMITX2_BIST_FAIL_ADDR  0x1800d28c
#define HDMITX2_BIST_SET_BIT    0x201    //[9],[0]:write data
#define HDMITX2_BIST_DONE_BIT   0x1    //[0]
#define HDMITX2_BIST_FAIL_BIT   0x2    //[1]

#define MCU_BIST_ADDR        0x18060460
#define MCU_BIST_DONE_ADDR   0x18060464
#define MCU_BIST_FAIL_ADDR   0x18060468
#define MCU_BIST_SET_BIT     0xF    //[3:0]
#define MCU_BIST_DONE_BIT    0xF    //[3:0]
#define MCU_BIST_FAIL_BIT    0xF    //[3:0]

#define MD_BIST_ADDR         0x18000508
#define MD_BIST_DONE_ADDR    0x1800b130
#define MD_BIST_FAIL_ADDR    0x1800b130
#define MD_BIST_SET_BIT      0x401    //[10],[0]:write data
#define MD_BIST_DONE_BIT     0x1    //[0]
#define MD_BIST_FAIL_BIT     0xE    //[3:1]

#define SCPU_BIST_ADDR       0x1801ca80
#define SCPU_BIST_DONE_ADDR  0x1801caac
#define SCPU_BIST_FAIL_ADDR  0x1801cac8
#define SCPU_BIST_FAIL_ADDR2 0x1801cad0
#define SCPU_BIST_FAIL_ADDR3 0x1801cad8
#define SCPU_BIST_FAIL_ADDR4 0x1801cae0
#define SCPU_BIST_FAIL_ADDR5 0x1801cae8
#define SCPU_BIST_FAIL_ADDR6 0x1801caf0
#define SCPU_BIST_FAIL_ADDR7 0x1801caf8
#define SCPU_BIST_FAIL_ADDR8 0x1801cb00
#define SCPU_BIST_FAIL_BIT   0xFF    //[7:0]  
#define SCPU_BIST_FAIL_BIT2  0xFF	 //[7:0]
#define SCPU_BIST_FAIL_BIT3  0xFFFFFFFF	 //[31:0]  
#define SCPU_BIST_FAIL_BIT4  0xFFFF	 //[15:0]   
#define SCPU_BIST_FAIL_BIT5  0xF	 //[3:0]  
#define SCPU_BIST_FAIL_BIT6  0xFFFF	 //[15:0]   
#define SCPU_BIST_FAIL_BIT7  0xFF	 //[7:0]   
#define SCPU_BIST_FAIL_BIT8   0xFF    //[7:0]

#define KCPU_BIST_ADDR       0x18000508
#define KCPU_BIST_DONE_ADDR  0x1801a864
#define KCPU_BIST_FAIL_ADDR  0x1801a864
#define KCPU_BIST_SET_BIT    0x21    //[5],[0]:write data
#define KCPU_BIST_DONE_BIT   0x10    //[4]
#define KCPU_BIST_FAIL_BIT   0xF    //[3:0]

#define SE_BIST_ADDR         0x1800ca04
#define SE_BIST_DONE_ADDR    0x1800ca08
#define SE_BIST_FAIL_ADDR    0x1800ca0c
#define SE_BIST_SET_BIT      0x3    //[1:0]
#define SE_BIST_DONE_BIT     0x3    //[1:0]
#define SE_BIST_FAIL_BIT     0x3    //[1:0]

#define TP_BIST_ADDR         0x18000500
#define TP_BIST_DONE_ADDR    0x18014674
#define TP_BIST_FAIL_ADDR    0x18014674
#define TP_BIST_SET_BIT      0x1001    //[12],[0]:write data
#define TP_BIST_DONE_BIT     0x1    //[0]
#define TP_BIST_FAIL_BIT     0x7E    //[6:1]

#define TVE_BIST_ADDR        0x1800a444
#define TVE_BIST_DONE_ADDR   0x1800a454
#define TVE_BIST_FAIL_ADDR   0x1800a45c
#define TVE_BIST_SET_BIT     0x3    //[1:0]
#define TVE_BIST_DONE_BIT    0x3    //[1:0]
#define TVE_BIST_FAIL_BIT    0x3    //[1:0]

#define TVE_VBIDAM_BIST_ADDR       0x18019044
#define TVE_VBIDAM_BIST_DONE_ADDR  0x18019054
#define TVE_VBIDAM_BIST_FAIL_ADDR  0x1801905c
#define TVE_VBIDAM_BIST_SET_BIT    0x3    //[1:0]
#define TVE_VBIDAM_BIST_DONE_BIT   0x3    //[1:0]
#define TVE_VBIDAM_BIST_FAIL_BIT   0x3    //[1:0]

#define USB_BIST_ADDR        0x18013900
#define USB_BIST_DONE_ADDR   0x18013904
#define USB_BIST_FAIL_ADDR   0x18013908
#define USB_BIST_SET_BIT     0x3    //[1:0]
#define USB_BIST_DONE_BIT    0x3    //[1:0]
#define USB_BIST_FAIL_BIT    0x3    //[1:0]

#define USB2_BIST_ADDR       0xb8012900
#define USB2_BIST_DONE_ADDR  0xb8012904
#define USB2_BIST_FAIL_ADDR  0xb8012908
#define USB2_BIST_SET_BIT    0x3    //[1:0]
#define USB2_BIST_DONE_BIT   0x3    //[1:0]
#define USB2_BIST_FAIL_BIT   0x3    //[1:0]

#define VBI_BIST_ADDR        0x18034c20
#define VBI_BIST_DONE_ADDR   0x18034c24
#define VBI_BIST_FAIL_ADDR   0x18034c28
#define VBI_BIST_SET_BIT     0x1    //[0]
#define VBI_BIST_DONE_BIT    0x1    //[0]
#define VBI_BIST_FAIL_BIT    0x1    //[0]

#define VCPU_BIST_ADDR       0x18000508
#define VCPU_BIST_DONE_ADDR  0x18001114
#define VCPU_BIST_FAIL_ADDR  0x18001114
#define VCPU_BIST_SET_BIT    0x5    //[2],[0]:write data
#define VCPU_BIST_DONE_BIT   0x100    //[8]
#define VCPU_BIST_FAIL_BIT   0xFF    //[7:0]

#define VDE_BIST_ADDR        0x18000500
#define VDE_BIST_DONE_ADDR   0x18001104
#define VDE_BIST_FAIL_ADDR   0x18001104
#define VDE_BIST_SET_BIT     0x81    //[7],[0]:write data
#define VDE_BIST_DONE_BIT    0x1    //[0]
#define VDE_BIST_FAIL_BIT    0x2    //[1]

#define VE_BIST_ADDR          0x18000504
#define VE_BIST_DONE_ADDR     0x1800FF10 //ff10, ff18, ff20, ff28,...,ff90
#define VE_BIST_FAIL_ADDR     0x18000614
#define VE_BIST_SET_BIT       0x3FFFF   //[17:1],[0]:write data
#define VE_BIST_DONE_BIT      0x1   //[0]
#define VE_BIST_FAIL_BIT      0x1FFFF   //[16:0]

#define DCSYS_DC2_BIST_ADDR      0x18000500
#define DCSYS_DC2_BIST_DONE_ADDR 0x180081C0
#define DCSYS_DC2_BIST_FAIL_ADDR 0x180081CC
#define DCSYS_DC2_BIST_SET_BIT   0x21   //[5],[0]:write data
#define DCSYS_DC2_BIST_DONE_BIT  0x1    //[0]
#define DCSYS_DC2_BIST_FAIL_BIT  0x3    //[1:0]

#define DCSYS_DC3_BIST_ADDR      0x18000500
#define DCSYS_DC3_BIST_DONE_ADDR 0x180081C0
#define DCSYS_DC3_BIST_FAIL_ADDR 0x180081CC
#define DCSYS_DC3_BIST_SET_BIT   0x41   //[6],[0]:write data
#define DCSYS_DC3_BIST_DONE_BIT  0x2    //[1]
#define DCSYS_DC3_BIST_FAIL_BIT  0x10    //[4]

#define EMMC_BIST_ADDR       0x18010864
#define EMMC_BIST_DONE_ADDR  0x18010868
#define EMMC_BIST_FAIL_ADDR  0x1801086c
#define EMMC_BIST_SET_BIT    0x3    //[1:0]
#define EMMC_BIST_DONE_BIT   0x3    //[1:0]
#define EMMC_BIST_FAIL_BIT   0x3    //[1:0]

#define GPU_BIST_ADDR        0x1804ff58
#define GPU_BIST_DONE_ADDR   0x1804ff5c
#define GPU_BIST_FAIL_ADDR   0x1804ff60
#define GPU_BIST_SET_BIT     0x1    //[0]
#define GPU_BIST_DONE_BIT    0x1    //[0]
#define GPU_BIST_FAIL_BIT    0x1    //[0]

#define IRTX_BIST_ADDR       0x1801b848
#define IRTX_BIST_DONE_ADDR  0x1801b84c
#define IRTX_BIST_FAIL_ADDR  0x1801b850
#define IRTX_BIST_SET_BIT    0x1    //[0]
#define IRTX_BIST_DONE_BIT   0x1    //[0]
#define IRTX_BIST_FAIL_BIT   0x1    //[0]

#define KT_BIST_ADDR        0x18000500
#define KT_BIST_DONE_ADDR   0x18035840
#define KT_BIST_FAIL_ADDR   0x18035840
#define KT_BIST_SET_BIT     0x2001   //[13],[0]:write data
#define KT_BIST_DONE_BIT    0x1    //[0]
#define KT_BIST_FAIL_BIT    0x6    //[2:1]

#define MISCDDC_BIST_ADDR      0x1801b378
#define MISCDDC_BIST_DONE_ADDR 0x1801b37c
#define MISCDDC_BIST_FAIL_ADDR 0x1801b380
#define MISCDDC_BIST_SET_BIT   0x1    //[0]
#define MISCDDC_BIST_DONE_BIT  0x1    //[0]
#define MISCDDC_BIST_FAIL_BIT  0x1    //[0]

#define NAND_BIST_ADDR      0x18000500
#define NAND_BIST_DONE_ADDR 0x18010354
#define NAND_BIST_FAIL_ADDR 0x18010354
#define NAND_BIST_SET_BIT   0x5   //[2],[0]:write data
#define NAND_BIST_DONE_BIT  0x1    //[0]
#define NAND_BIST_FAIL_BIT  0xE    //[3:1]

#define OSD_BIST_ADDR       0x180350c8
#define OSD_BIST_DONE_ADDR  0x180350cc
#define OSD_BIST_FAIL_ADDR  0x180350d0
#define OSD_BIST_SET_BIT    0xF   //[3:0]
#define OSD_BIST_DONE_BIT   0xF    //[3:0]
#define OSD_BIST_FAIL_BIT   0xF    //[3:0]

#define SD_BIST_ADDR        0x18010c64
#define SD_BIST_DONE_ADDR   0x18010c68
#define SD_BIST_FAIL_ADDR   0x18010c6c
#define SD_BIST_SET_BIT     0x3    //[1:0]
#define SD_BIST_DONE_BIT    0x3    //[1:0]
#define SD_BIST_FAIL_BIT    0x3    //[1:0]

#define SENSIO_BIST_ADDR      0xb80050fc
#define SENSIO_BIST_DONE_ADDR 0xb80050f8
#define SENSIO_BIST_FAIL_ADDR 0xb80050f8
#define SENSIO_BIST_SET_BIT   0x1    //[0]
#define SENSIO_BIST_DONE_BIT  0x80    //[7]
#define SENSIO_BIST_FAIL_BIT  0x20    //[5]

#define SFG_BIST_ADDR       0xb802d1bc
#define SFG_BIST_DONE_ADDR  0xb802d1c0
#define SFG_BIST_FAIL_ADDR  0xb802d1c4
#define SFG_BIST_SET_BIT    0x3    //[1:0]
#define SFG_BIST_DONE_BIT   0x3    //[1:0]
#define SFG_BIST_FAIL_BIT   0x3    //[1:0]

#define VBY1_BIST_ADDR      0x1802d62c
#define VBY1_BIST_DONE_ADDR 0x1802d62c
#define VBY1_BIST_FAIL_ADDR 0x1802d630
#define VBY1_BIST_SET_BIT   0x1   //[0]
#define VBY1_BIST_DONE_BIT  0x8    //[3]
#define VBY1_BIST_FAIL_BIT  0xF    //[3:0]
