#include <qc_verify_common.h>

void dpll_297MHz(void)
{
    rtd_outl(0xb8000190, 0x02101216);		        // DPLL M, N, RS=28K, Ip=2.5uA
    rtd_maskl(0xb8000194,0xFFCFCFFE,0x00300001);	// DPLL DIV_A/1
    rtd_maskl(0xb8028294,0xFFFFFFFC,0x00000000);	// DPLL DIV_D/1
    rtd_maskl(0xb8000300,0xF000FFFA,0x07500001);	// DPLL OFFSET
    rtd_maskl(0xb8000300,0xF000FFFA,0x07500005);	// DPLL OFFSET Load in
}

void dpg_fhd(void)
{
    rtd_maskl(0xb8029038, 0xFFFEFFFF, 0);// b802_9038,Peaking control disable, enable on VIP test 
    rtd_outl(0xb8029000, 0x00000031);	// DPG Color Bar
    rtd_outl(0xb8029074, 0x000000EF);	// DPG Color Width
    rtd_outl(0xb8029028, 0x07800438);	// Input Size
}

void dtg_fhd_frc(void)
{
    rtd_outl(0xb8028000, 0x01000000);	// Free Run Mode
    rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
    rtd_outl(0xb802800C, 0x08970897);	// DH_total
    rtd_outl(0xb8028010, 0x00000005);	// DV_sync width
    rtd_outl(0xb8028014, 0x00000464);	// DV_total
    rtd_outl(0xb8028018, 0x008C080C);	// DH_den_sta, DH_den_end
    rtd_outl(0xb802801C, 0x0016044E);	// DV_den_sta, DV_den_end		
    rtd_outl(0xb8028024, 0x000000FF);	// Display Background Color
    rtd_outl(0xb8028028, 0x00000002);	// Disable Buffer
}

void mtg_fhd(void)
{
    rtd_outl(0xb8028100, 0x00000001);   // Main Display enable
    rtd_outl(0xb8028108, 0x0CD40000);   // Main Border Color
    rtd_outl(0xb802810C, 0x00000000);   // Main Background Color
    rtd_outl(0xb8028110, 0x00000780);   // Main DEN_H_str,Main DEN_H_end
    rtd_outl(0xb8028114, 0x00000438);   // Main DEN_V_str,Main DEN_V_end
    rtd_outl(0xb8028118, 0x00000780);   // Main Background_H_str,Main Background_H_end
    rtd_outl(0xb802811C, 0x00000438);   // Main Background_V_str,Main Background_V_end
    rtd_outl(0xb8028120, 0x00000780);   // Main Active_H_str,Main Active_H_end
    rtd_outl(0xb8028124, 0x00000438);   // Main Active_V_str,Main Active_V_end

}

void vgip_dma_dpg_1080p(void)
{
    //-----------DMA VGIP setting-------------//
    rtd_outl(0xb8022710, 0xB0050001);   //011:DISPD,analog mode, SRC_Clock_Enbale
    rtd_outl(0xb8022718, 0x00AE0780); //29:16==>Ch3_ih_act_sta/13:0==>Ch3_ih_act_wid
    rtd_outl(0xb802271c, 0x00160438);   //28:16==>Ch3_iv_act_sta/12:0==>Ch3_iv_act_len
    //rtd_outl(0xb8022720, 0x00000000); //29:16==>Ch3_IHS_DLY/12:0==>Ch3_IVS_DLY
    rtd_outl(0xb8022790, 0x00000406);   //CTS FIFO 

}

void i3ddma_1080p_to_576p(void)
{
    // VSD, HSD
    rtd_outl(0xb8025600, 0x0100000B);// keep bit8 = 0, 444 to 422
    //rtd_outl(0xb8025900, 0x00000001);
    rtd_outl(0xb8025904, 0x002AAAAA); // HOR_FAC
    rtd_outl(0xb8025608, 0x001E0000); // I3DDMA_VSD
    //rtd_outl(0xb8025608, 0x00240000); // I3DDMA_VSD
    rtd_outl(0xb8025910, 0x000002D0); // I3DDMA_HSD_Hor_Segment 
    rtd_outl(0xb8025900, 0x00000001);
    
    
    // dispi hdmi_3ddma
    //rtd_outl(b8025ad0=00000002); // 444 to 422 in hdmi rgb2yuv dither spec. if hsd & vsd not bypass, do 444 to 422 at VSD
    rtd_outl(0xb8025800, 0x001A0000); //  progressive input, 2D frame 
    rtd_outl(0xb8025804, 0x024002D0); // 576 720
    
    //Capture
    rtd_outl(0xb8025814, 0x00002002); // FIFO water level = 16, number of  length to fill in DDR NUM = 2
    rtd_outl(0xb8025810, 0x80C1201A); // why enable tripple buffer?, reset FIFO address at VS fall, HW auto set memory address, pixel encode 422,
    // length of data to fill in DDR LEN= 32, remaining part REM= 26
    rtd_outl(0xb802583c, 0x00000202);// 2:2 pull up disable, first VS falling edge pixel num = 2, first VS falling edge line num = 2
    // because input is a 2D signal, the value here is important here, just don't be equal to 0?
    rtd_outl(0xb8025870, 0x0000000F);// FRC, timing gen, 3D LR separate, Capture enable
    rtd_outl(0xb8025874, 0x00000008); //8 bytes swap, why ??
    
    rtd_outl(0xb8025820, 0x02000000);  // block0, DDR buffer L1 start address
    rtd_outl(0xb8025824, 0x03000000);  // block1, DDR buffer L2 start address
    rtd_outl(0xb8025884, 0x04000000);  // block2, DDR buffer L3 start address
    rtd_outl(0xb802588c, 0x05000000);  // block3, DDR buffer L4 start address

}


int QC_Verifier_I3DDMA(void)
{
    dpll_297MHz();
    //printk("dpll_297MHz OK! \r\n");
    dpg_fhd();
    //printk("dpg_fhd OK! \r\n");
    dtg_fhd_frc();
    //printk("dtg_fhd_frc OK! \r\n");

    //-------- PLL DISP -------------------------------------------------
    rtd_outl(0xb8000190,0x02601336);	// max 540, set 360MHz
    rtd_outl(0xb8000194,0x11020001);	// DPLL power on
    rtd_outl(0xb8000194,0x11020043);	// release DPLL reset 

    mtg_fhd();
    //printk("mtg_fhd OK! \r\n");
    rtd_part_outl(0xb8000c54, 15, 15, 0x1);//Enable signal of 3.3V -> 1.05V LDO for Analog Core Power
    rtd_part_outl(0xb8000c78, 31, 31, 0x1);//Enable signal of Panel Link TX

    rtd_part_outl(0xb8028004, 17, 16, 0);// Dispd to i3ddma src sel:uzu output
    
    vgip_dma_dpg_1080p();
    //printk("vgip_dma_dpg_1080p OK! \r\n");
    
    i3ddma_1080p_to_576p();
    //printk("i3ddma_1080p_to_576p OK! \r\n");
    
    rtd_outl(0xb8025860, 0x00000303); // enable CRC continuous mode
    
    udelay(100000); // delay for CRC calculation duration
    
    if(rtd_inl(0xb8025864) == 0x92CAF82D && rtd_inl(0xb8025868) == 0)
    	{
    		//printk("rtd_inl(0xb8025864) = 0x%x\n", rtd_inl(0xb8025864));
            //printk("rtd_inl(0xb8025868) = 0x%x\n", rtd_inl(0xb8025868));
        	return SUCCESS;
      }
    else
        {
            printk("rtd_inl(0xb8025864) = 0x%x\n", rtd_inl(0xb8025864));
            printk("rtd_inl(0xb8025868) = 0x%x\n", rtd_inl(0xb8025868));
	        return FAILED;
        }
} 
