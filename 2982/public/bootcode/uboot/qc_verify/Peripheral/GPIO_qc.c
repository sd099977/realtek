#include <qc_verify_common.h>


#define	ew(reg_addr,para)			rtd_outl(reg_addr,para)
#define	dw(reg_addr)				rtd_inl(reg_addr)


int gpio_vs_gpio(char out_port, UINT32 out_port_num, char in_port, UINT32 in_port_num){

UINT32 gpio_err=0;
UINT32 gpo_cr_set,gpo_data_set,gpi_cr_set,gpi_data_set, tmp, gpi_tmp;
UINT32 in_data,in_int,out_data;
char *in_port_cr,*in_port_data,*in_data_value;
char *out_port_cr,*out_port_data;

	
if (in_port=='M'){
	
    in_port_cr=0xb801b100+((in_port_num/32)*4); // MIS_GPDIR
    in_port_data=0xb801b138+((in_port_num/32)*4); // GPI Read input

}
else{
 
    in_port_cr=0xb8061100+((in_port_num/32)*4); // ISO_GPDIR
    in_port_data=0xb8061110+((in_port_num/32)*4); //GPI Read input
	
}

if (out_port=='M'){
	
    out_port_cr=0xb801b100+((out_port_num/32)*4); //MIS_GPDIR
    out_port_data=0xb801b11c+((out_port_num/32)*4); //GPO	
}
else{
    out_port_cr=0xb8061100+((out_port_num/32)*4); // ISO_GPDIR
    out_port_data=0xb8061108+((out_port_num/32)*4); //GPO

}

gpi_cr_set=dw(in_port_cr)&(~(0x1<<(in_port_num%32))); // in_port_cr = GPDIR > GPI
	

gpi_data_set=dw(in_port_data)&(~(0x1<<((in_port_num%32)))); // in_port_data = GPI > GPI


gpi_tmp=dw(in_port_cr)|(0x1<<((in_port_num%32)));


ew(in_port_cr,gpi_cr_set);     //  in_port   set

ew(in_port_data,gpi_data_set);  //  in_port   set	


gpo_cr_set=dw(out_port_cr)|(0x1<<((out_port_num%32))); // GPDIR > GPO

gpo_data_set=dw(out_port_data)&(~(0x1<<((out_port_num%32)))); // > GPO

ew(out_port_cr,gpo_cr_set);   //  set  out_output 

ew(out_port_data,gpo_data_set); //  set out_output

//===============  write 1 ===================================
gpo_data_set=dw(out_port_data)|(0x1<<((out_port_num%32)));

ew(out_port_data,gpo_data_set); //  output data=1;

udelay(1000);

tmp=dw(in_port_data)&(0x1<<((in_port_num%32))); // read GPI value, in_port_data mapping bit= 1

tmp=tmp>>((in_port_num%32));

udelay(10000);
if((tmp)==0x1)  
{

gpio_err|=0;
}
else{
printk("Out port write 1 is 1 -> fail \n");

gpio_err|=1;
}
udelay(10000);


//===============  write 0 ===================================
gpo_data_set=dw(out_port_data)&(~(0x1<<((out_port_num%32))));
ew(out_port_data,gpo_data_set); 
udelay(10000);         

tmp=dw(in_port_data)&(0x1<<((in_port_num%32)));
tmp=tmp>>((in_port_num%32)); 
udelay(10000);

if((tmp)==0x0)             	
{

gpio_err|=0;
}
else{
printk("Out port write 0 is 0 -> fail \n");

//printk("GPI received data \n =%X\n", rtd_inl(0xb8061110));


gpio_err|=1;
}

gpo_cr_set = dw(out_port_cr)&(~(0x1<<((out_port_num%32))));
ew(out_port_cr,gpo_cr_set);   //  clear  output 

// ==========================================================
if(gpio_err==0)
return 0;
else
{

	return 1;
}

}


int Verifier_GPIO(void)
{
	UINT32 gpio_err=0;
	UINT32 gpio_sum=0;
	char* M;
	char* S;
	
	int tmp;
	UINT32 gpo_data_set;

#if CONFIG_BGA

	#if CONFIG_BOX 

	//-----------------------------------------------------------------------------------------------------------------------BOX_BGA

	printk("****************************************Package : BOX_BGA \n");

	// D8_ST_GPIO36_JP26_3 vs E8_ST_GPIO25_JS26_2
		
		rtd_maskl(0xb8060230,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO36
		rtd_maskl(0xb8060240,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO25

		gpio_err=gpio_vs_gpio('S',36,'S',25);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 36 vs GPI Standby 25 fail \n");
		gpio_err=gpio_vs_gpio('S',25,'S',36);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 25 vs GPI Standby 36 fail \n");

	// A3_ST_GPIO26_JP5_3 vs B3_ST_GPIO27_JS5_2
		
		rtd_maskl(0xb8060240,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO26
		rtd_maskl(0xb806023c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO27

		gpio_err=gpio_vs_gpio('S',26,'S',27);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 26 vs GPI Standby 27 fail \n");
		gpio_err=gpio_vs_gpio('S',27,'S',26);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 27 vs GPI Standby 26 fail \n");

	// A2_ST_GPIO28_JP1_3 vs B2_ST_GPIO29_JS1_2
		
		rtd_maskl(0xb806023c,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO28
		rtd_maskl(0xb806023c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO29

		gpio_err=gpio_vs_gpio('S',28,'S',29);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 28 vs GPI Standby 29 fail \n");
		gpio_err=gpio_vs_gpio('S',29,'S',28);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 29 vs GPI Standby 28 fail \n");

	// H6_ST_GPIO33_JP2_3 vs J5_ST_GPIO41_JS2_2
		
		rtd_maskl(0xb8060234,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO33
		rtd_maskl(0xb806022c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO41

		gpio_err=gpio_vs_gpio('S',33,'S',41);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 33 vs GPI Standby 41 fail \n");
		gpio_err=gpio_vs_gpio('S',41,'S',33);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 41 vs GPI Standby 33 fail \n");	

	// J6_ST_GPIO34_JP6_2 vs J4_ST_GPIO42_JS6_3

		rtd_maskl(0xb8060234,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO34
		rtd_maskl(0xb8060228,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO42

		gpio_err=gpio_vs_gpio('S',34,'S',42);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 34 vs GPI Standby 42 fail \n");
		gpio_err=gpio_vs_gpio('S',42,'S',34);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 42 vs GPI Standby 34 fail \n");	

	// K5_ST_GPIO44_JP9_2 vs K4_GPIO189_JS9_3

		rtd_maskl(0xb8060228,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO44
		rtd_maskl(0xb8000890,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO189

		gpio_err=gpio_vs_gpio('S',44,'M',189);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 44 vs GPI Main 189 fail \n");
		gpio_err=gpio_vs_gpio('M',189,'S',44);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 189 vs GPI Standby 44 fail \n");	

	// L6_GPIO190_JP15_3 vs M5_GPIO3_JS15_2

		rtd_maskl(0xb8000890,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO190
		rtd_maskl(0xb8000894,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO3

		gpio_err=gpio_vs_gpio('M',190,'M',3);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 190 vs GPI Main 3 fail \n");
		gpio_err=gpio_vs_gpio('M',3,'M',190);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 3 vs GPI Main 190 fail \n");	

	// K6_ST_GPIO43_JP12_3 vs L5_GPIO191_JS12_2

		rtd_maskl(0xb8060228,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO43
		rtd_maskl(0xb8000890,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO191

		gpio_err=gpio_vs_gpio('S',43,'M',191);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 43 vs GPI Main 191 fail \n");
		gpio_err=gpio_vs_gpio('M',191,'S',43);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 191 vs GPI Standby 43 fail \n");

	// N4_GPIO147_JP20_3 vs N5_GPIO146_JS20_2

		rtd_maskl(0xb8000898,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO147
		rtd_maskl(0xb8000898,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO146

		gpio_err=gpio_vs_gpio('M',147,'M',146);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 147 vs GPI Main 146 fail \n");
		gpio_err=gpio_vs_gpio('M',146,'M',147);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 146 vs GPI Main 147 fail \n");

	// N6_GPIO148_JP23_3 vs P5_GPIO149_JS23_2

		rtd_maskl(0xb8000898,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO148
		rtd_maskl(0xb800089c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO149

		gpio_err=gpio_vs_gpio('M',148,'M',149);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 148 vs GPI Main 149 fail \n");
		gpio_err=gpio_vs_gpio('M',149,'M',148);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 149 vs GPI Main 148 fail \n");

	// AB10_GPIO1_JP63_2 vs AA9_GPIO5_JS63_3

		rtd_maskl(0xb8000800,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO1
		rtd_maskl(0xb8000808,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO5

		gpio_err=gpio_vs_gpio('M',1,'M',5);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 1 vs GPI Main 5 fail \n");
		gpio_err=gpio_vs_gpio('M',5,'M',1);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 5 vs GPI Main 1 fail \n");

	// AD9_GPIO197_JP52_3 vs AC9_GPIO7_JS52_2

		rtd_maskl(0xb8000948,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO197
		rtd_maskl(0xb8000808,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO7
		
		gpio_err=gpio_vs_gpio('M',197,'M',7);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 197 vs GPI Main 7 fail \n");
		gpio_err=gpio_vs_gpio('M',7,'M',197);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 7 vs GPI Main 197 fail \n");

	// AE10_GPIO6_JP69_2 vs AD10_GPIO199_JS69_3

		rtd_maskl(0xb8000808,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO6
		rtd_maskl(0xb8000948,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO199
		
		gpio_err=gpio_vs_gpio('M',6,'M',199);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 6 vs GPI Main 199 fail \n");
		gpio_err=gpio_vs_gpio('M',199,'M',6);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 199 vs GPI Main 6 fail \n");

	// AA10_GPIO198_JP66_3 vs Y10_GPIO8_JS66_2

		rtd_maskl(0xb8000948,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO198
		rtd_maskl(0xb800080c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO8
		
		gpio_err=gpio_vs_gpio('M',198,'M',8);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 198 vs GPI Main 8 fail \n");
		gpio_err=gpio_vs_gpio('M',8,'M',198);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 8 vs GPI Main 198 fail \n");

	// AC10_GPIO9_JP73_3 vs AE11_GPIO201_JS73_2

		rtd_maskl(0xb800080c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO9
		rtd_maskl(0xb800094c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO201
		
		gpio_err=gpio_vs_gpio('M',9,'M',201);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 9 vs GPI Main 201 fail \n");
		gpio_err=gpio_vs_gpio('M',201,'M',9);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 201 vs GPI Main 9 fail \n");

	// AC11_GPIO200_JP75_2 vs AD11_GPIO11_JS75_3

		rtd_maskl(0xb800094c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO200
		rtd_maskl(0xb8000810,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO11
		
		gpio_err=gpio_vs_gpio('M',200,'M',11);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 200 vs GPI Main 11 fail \n");
		gpio_err=gpio_vs_gpio('M',11,'M',200);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 11 vs GPI Main 200 fail \n");

	// Y12_GPIO13_JP84_3 vs AB13_GPIO202_JS84_2

		rtd_maskl(0xb8000810,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO13
		rtd_maskl(0xb800094c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO202
		
		gpio_err=gpio_vs_gpio('M',13,'M',202);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 13 vs GPI Main 202 fail \n");
		gpio_err=gpio_vs_gpio('M',202,'M',13);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 202 vs GPI Main 13 fail \n");

	// AB12_GPIO10_JP81_2 vs AA12_GPIO15_JS81_3

		rtd_maskl(0xb800080c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO10
		rtd_maskl(0xb8000814,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO15
		
		gpio_err=gpio_vs_gpio('M',10,'M',15);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 10 vs GPI Main 15 fail \n");
		gpio_err=gpio_vs_gpio('M',15,'M',10);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 15 vs GPI Main 10 fail \n");

	// Y11_GPIO12_JP78_2 vs AA11_GPIO204_JS78_3

		rtd_maskl(0xb8000810,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO12
		rtd_maskl(0xb8000950,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO204
		
		gpio_err=gpio_vs_gpio('M',12,'M',204);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 12 vs GPI Main 204 fail \n");
		gpio_err=gpio_vs_gpio('M',204,'M',12);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 204 vs GPI Main 12 fail \n");

	// AD13_GPIO17_JP90_3 vs AE13_GPIO18_JS90_2

		rtd_maskl(0xb8000818,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO17
		rtd_maskl(0xb8000818,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO18
		
		gpio_err=gpio_vs_gpio('M',17,'M',18);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 17 vs GPI Main 18 fail \n");
		gpio_err=gpio_vs_gpio('M',18,'M',17);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 18 vs GPI Main 17 fail \n");

	// Y13_GPIO205_JP94_2 vs AA13_GPIO20_JS94_3

		rtd_maskl(0xb800081c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO20
		rtd_maskl(0xb8000950,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO205
		
		gpio_err=gpio_vs_gpio('M',205,'M',20);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 205 vs GPI Main 20 fail \n");
		gpio_err=gpio_vs_gpio('M',20,'M',205);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 20 vs GPI Main 205 fail \n");

	// Y14_GPIO16_JP53_2 vs AA14_GPIO206_JS53_3

		rtd_maskl(0xb8000954,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO206
		rtd_maskl(0xb8000814,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO16
		
		gpio_err=gpio_vs_gpio('M',16,'M',206);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 16 vs GPI Main 206 fail \n");
		gpio_err=gpio_vs_gpio('M',206,'M',16);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 206 vs GPI Main 16 fail \n");

	// AB15_GPIO23_JP60_2 vs AA15_GPIO21_JS60_3

		rtd_maskl(0xb8000820,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO23
		rtd_maskl(0xb800081c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO21
		
		gpio_err=gpio_vs_gpio('M',23,'M',21);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 23 vs GPI Main 21 fail \n");
		gpio_err=gpio_vs_gpio('M',21,'M',23);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 21 vs GPI Main 23 fail \n");

	// Y15_GPIO22_JP76_3 vs AB16_GPIO27_JS76_2

		rtd_maskl(0xb8000824,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO27
		rtd_maskl(0xb800081c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO22
		
		gpio_err=gpio_vs_gpio('M',27,'M',22);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 27 vs GPI Main 22 fail \n");
		gpio_err=gpio_vs_gpio('M',22,'M',27);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 22 vs GPI Main 27 fail \n");

	// AE14_GPIO25_JP92_2 vs AC13_GPIO35_JS92_3

		rtd_maskl(0xb8000828,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO35
		rtd_maskl(0xb8000820,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO25
		
		gpio_err=gpio_vs_gpio('M',35,'M',25);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 35 vs GPI Main 25 fail \n");
		gpio_err=gpio_vs_gpio('M',25,'M',35);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 25 vs GPI Main 35 fail \n");

	// Y17_GPIO28_JP82_2 vs AA17_GPIO30_JS82_3

		rtd_maskl(0xb8000824,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO30
		rtd_maskl(0xb8000824,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO28
		
		gpio_err=gpio_vs_gpio('M',30,'M',28);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 30 vs GPI Main 28 fail \n");
		gpio_err=gpio_vs_gpio('M',28,'M',30);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 28 vs GPI Main 30 fail \n");

	// AA16_GPIO26_JP79_3 vs Y16_GPIO31_JS79_2

		rtd_maskl(0xb8000828,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO31
		rtd_maskl(0xb8000820,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO26
		
		gpio_err=gpio_vs_gpio('M',26,'M',31);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 26 vs GPI Main 31 fail \n");
		gpio_err=gpio_vs_gpio('M',31,'M',26);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 31 vs GPI Main 26 fail \n");

	// AA18_GPIO36_JP91_3 vs AB18_GPIO37_JS91_2

		rtd_maskl(0xb800082c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO36
		rtd_maskl(0xb800082c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO37
		
		gpio_err=gpio_vs_gpio('M',36,'M',37);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 36 vs GPI Main 37 fail \n");
		gpio_err=gpio_vs_gpio('M',37,'M',36);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 37 vs GPI Main 36 fail \n");

	// AC15_GPIO38_JP64_2 vs AD15_GPIO43_JS64_3

		rtd_maskl(0xb800082c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO38
		rtd_maskl(0xb8000834,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO43
		
		gpio_err=gpio_vs_gpio('M',38,'M',43);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 38 vs GPI Main 43 fail \n");
		gpio_err=gpio_vs_gpio('M',43,'M',38);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 43 vs GPI Main 38 fail \n");
/* uart1
	// AD20_GPIO53_JP62_3 vs AC20_GPIO54_JS62_2

		rtd_maskl(0xb8000844,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO54
		rtd_maskl(0xb8000840,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO53
		
		gpio_err=gpio_vs_gpio('M',53,'M',54);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 53 vs GPI Main 54 fail \n");
		gpio_err=gpio_vs_gpio('M',54,'M',53);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 54 vs GPI Main 53 fail \n");
*/

	//H23_GPIO32_JP85_3 vs H25_GPIO142_JS85_2

		rtd_maskl(0xb800084c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO32
		rtd_maskl(0xb8000850,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO142
		
		gpio_err=gpio_vs_gpio('M',32,'M',142);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 32 vs GPI Main 142 fail \n");
		gpio_err=gpio_vs_gpio('M',142,'M',32);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 142 vs GPI Main 32 fail \n");

	// G23_GPIO29_JP83_3 vs H24_GPIO33_JS83_2

		rtd_maskl(0xb800084c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO29
		rtd_maskl(0xb800084c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO33
		
		gpio_err=gpio_vs_gpio('M',29,'M',33);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 29 vs GPI Main 33 fail \n");
		gpio_err=gpio_vs_gpio('M',33,'M',29);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 33 vs GPI Main 29 fail \n");

	// G24_GPIO24_JP80_2 vs G22_GPIO85_JS80_3

		rtd_maskl(0xb8000850,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO24
		rtd_maskl(0xb8000850,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO85
		
		gpio_err=gpio_vs_gpio('M',24,'M',85);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 24 vs GPI Main 85 fail \n");
		gpio_err=gpio_vs_gpio('M',85,'M',24);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 85 vs GPI Main 24 fail \n");

	// F24_GPIO141_JP77_2 vs F25_GPIO140_JS77_3

		rtd_maskl(0xb80008B8,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO141
		rtd_maskl(0xb80008B8,GetMaskAnd(26,22),0x1F<<22); //pinshare GPIO140

		rtd_maskl(0xb8000c2c,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO141 mode
		rtd_maskl(0xb8000c2c,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO140 mode
		
		gpio_err=gpio_vs_gpio('M',141,'M',140);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 141 vs GPI Main 140 fail \n");
		gpio_err=gpio_vs_gpio('M',140,'M',141);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 140 vs GPI Main 141 fail \n");


	// F23_GPIO81_J31_2 vs E25_GPIO82_J31_1

		rtd_maskl(0xb80008b8,0xffc1ffff,0x003e0000); //pinshare GPIO81
		rtd_maskl(0xb80008b8,0xfffe0fff,0x0001f000); //pinshare GPIO82

		rtd_maskl(0xb8000c28,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO81 mode
		rtd_maskl(0xb8000c28,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO82 mode
		
		gpio_err=gpio_vs_gpio('M',81,'M',82);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 81 vs GPI Main 82 fail \n");
		gpio_err=gpio_vs_gpio('M',82,'M',81);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 82 vs GPI Main 81 fail \n");

	// E22_GPIO83_J32_2 vs F22_GPIO84_J32_1
	
		rtd_maskl(0xb80008c0,0xfffff07f,0x00000f80); //pinshare GPIO83
		rtd_maskl(0xb80008c0,0xffffff83,0x0000007c); //pinshare GPIO84

		rtd_maskl(0xb8000c4c,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO83 mode
		rtd_maskl(0xb8000c4c,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO84 mode
		
		gpio_err=gpio_vs_gpio('M',83,'M',84);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 83 vs GPI Main 84 fail \n");
		gpio_err=gpio_vs_gpio('M',84,'M',83);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 84 vs GPI Main 83 fail \n");

	// C16_GPIO94_JP27_2 vs A15_GPIO173_JS27_3

		rtd_maskl(0xb800085c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO94
		rtd_maskl(0xb8000878,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO173
		
		gpio_err=gpio_vs_gpio('M',94,'M',173);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 94 vs GPI Main 173 fail \n");
		gpio_err=gpio_vs_gpio('M',173,'M',94);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 173 vs GPI Main 94 fail \n");

	// E9_ST_GPIO7_JP28_2 vs F9_ST_GPIO9_JS28_3

		rtd_maskl(0xb806024c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO9
		rtd_maskl(0xb806024c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO7
		
		gpio_err=gpio_vs_gpio('S',9,'S',7);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 9 vs GPI Standby 7 fail \n");
		gpio_err=gpio_vs_gpio('S',7,'S',9);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 7 vs GPI Standby 9 fail \n");

	// C10_ST_GPIO8_JP3_2 vs B9_ST_GPIO10_JS3_3

		rtd_maskl(0xb8060248,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO10
		rtd_maskl(0xb806024c,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO8
		
		gpio_err=gpio_vs_gpio('S',10,'S',8);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 10 vs GPI Standby 8 fail \n");
		gpio_err=gpio_vs_gpio('S',8,'S',10);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 8 vs GPI Standby 10 fail \n");

	// D5_ST_GPIO17_JP40_3 vs E4_ST_GPIO19_JS40_2

		rtd_maskl(0xb8060244,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO19
		rtd_maskl(0xb8060204,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO17
		
		gpio_err=gpio_vs_gpio('S',17,'S',19);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 17 vs GPI Standby 19 fail \n");
		gpio_err=gpio_vs_gpio('S',19,'S',17);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 19 vs GPI Standby 17 fail \n");

	// D4_ST_GPIO16_JP36_3 vs E5_ST_GPIO18_JS36_2

		rtd_maskl(0xb8060204,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO18
		rtd_maskl(0xb8060244,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO16
		
		gpio_err=gpio_vs_gpio('S',16,'S',18);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 16 vs GPI Standby 18 fail \n");
		gpio_err=gpio_vs_gpio('S',18,'S',16);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 18 vs GPI Standby 16 fail \n");

	//----------------------------------------------------------------------combine----------------------------

	// B8_ST_GPIO39_JP49_3 vs E6_ST_GPIO30_JS24_2

		rtd_maskl(0xb806022c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO39
		rtd_maskl(0xb8060238,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO30
		
		gpio_err=gpio_vs_gpio('S',39,'S',30);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 39 vs GPI Standby 30 fail \n");
		gpio_err=gpio_vs_gpio('S',30,'S',39);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 30 vs GPI Standby 39 fail \n");

	// F6_ST_GPIO31_JP29_3 vs G6_ST_GPIO32_JS48_3

		rtd_maskl(0xb8060238,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO32
		rtd_maskl(0xb8060238,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO31

		
		gpio_err=gpio_vs_gpio('S',32,'S',31);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 32 vs GPI Standby 31 fail \n");
		gpio_err=gpio_vs_gpio('S',31,'S',32);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 31 vs GPI Standby 32 fail \n");


	// AB4_GPIO196_JP88_2 vs AB9_GPIO2_JS59_2

		rtd_maskl(0xb8000804,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO2
		rtd_maskl(0xb80008f8,GetMaskAnd(21,17),0x1F<<17); //pinshare GPIO196

		rtd_maskl(0xb80008f8,GetMaskAnd(2,2),0x1<<2); //GPIO196 GPI EN
		
		gpio_err=gpio_vs_gpio('M',2,'M',196);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 2 vs GPI Main 196 fail \n");
		gpio_err=gpio_vs_gpio('M',196,'M',2);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 196 vs GPI Main 2 fail \n");

		rtd_maskl(0xb80008f8,GetMaskAnd(2,2),0x0<<2); //clear GPIO196 GPI EN

	// AD12_GPIO14_JP87_3 vs AD16_GPIO203_JS68_3

		rtd_maskl(0xb8000814,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO14
		rtd_maskl(0xb8000950,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO203
		
		gpio_err=gpio_vs_gpio('M',14,'M',203);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 14 vs GPI Main 203 fail \n");
		gpio_err=gpio_vs_gpio('M',203,'M',14);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 203 vs GPI Main 14 fail \n");

	// AD14_GPIO19_JP56_3 vs Y18_GPIO34_JS93_3

		rtd_maskl(0xb8000818,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO19
		rtd_maskl(0xb8000828,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO34

		gpio_err=gpio_vs_gpio('M',19,'M',34);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 19 vs GPI Main 34 fail \n");
		gpio_err=gpio_vs_gpio('M',34,'M',19);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 34 vs GPI Main 19 fail \n");

	// AC17_GPIO143_JP86_2 vs D15_GPIO92_JS43_2

		rtd_maskl(0xb8000848,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO143
		rtd_maskl(0xb800085c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO92
		
		gpio_err=gpio_vs_gpio('M',143,'M',92);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 143 vs GPI Main 92 fail \n");
		gpio_err=gpio_vs_gpio('M',92,'M',143);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 92 vs GPI Main 143 fail \n");

	// B17_GPIO93_JP32_2 vs B15_GPIO95_JS25_2

		rtd_maskl(0xb800085c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO93
		rtd_maskl(0xb8000860,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO95
		
		gpio_err=gpio_vs_gpio('M',93,'M',95);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 93 vs GPI Main 95 fail \n");
		gpio_err=gpio_vs_gpio('M',95,'M',93);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 95 vs GPI Main 93 fail \n");

	// B14_GPIO96_JP22_2 vs B16_GPIO174_JS30_2

		rtd_maskl(0xb8000860,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO96
		rtd_maskl(0xb800087c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO174
		
		gpio_err=gpio_vs_gpio('M',96,'M',174);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 96 vs GPI Main 174 fail \n");
		gpio_err=gpio_vs_gpio('M',174,'M',96);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 174 vs GPI Main 96 fail \n");

	// C11_GPIO97_JP10_3 vs F11_GPIO171_JS34_2

		rtd_maskl(0xb8000860,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO97
		rtd_maskl(0xb8000878,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO171
		
		gpio_err=gpio_vs_gpio('M',97,'M',171);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 97 vs GPI Main 171 fail \n");
		gpio_err=gpio_vs_gpio('M',171,'M',97);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 171 vs GPI Main 97 fail \n");

	// E10_ST_GPIO12_JP31_2 vs B10_ST_GPIO13_JS7_2

		rtd_maskl(0xb8060248,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO12
		rtd_maskl(0xb8060244,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO13

		
		gpio_err=gpio_vs_gpio('S',12,'S',13);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 12 vs GPI Standby 13 fail \n");
		gpio_err=gpio_vs_gpio('S',13,'S',12);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 13 vs GPI Standby 12 fail \n");


	// G4_ST_GPIO22_JP46_3 vs B10_ST_GPIO13_JS7_2

		rtd_maskl(0xb8060240,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO22
		rtd_maskl(0xb8060244,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO13

		
		gpio_err=gpio_vs_gpio('S',22,'S',13);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 22 vs GPI Standby 13 fail \n");
		gpio_err=gpio_vs_gpio('S',13,'S',22);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 13 vs GPI Standby 22 fail \n");


#else

//-----------------------------------------------------------------------------------------------------------------------TV_BGA

printk("****************************************Package : TV_BGA \n");

// D8_ST_GPIO36_JP26_3 vs E8_ST_GPIO25_JS26_2
	
	rtd_maskl(0xb8060230,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO36
	rtd_maskl(0xb8060240,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO25

	gpio_err=gpio_vs_gpio('S',36,'S',25);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 36 vs GPI Standby 25 fail \n");
	gpio_err=gpio_vs_gpio('S',25,'S',36);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 25 vs GPI Standby 36 fail \n");

// A3_ST_GPIO26_JP5_3 vs B3_ST_GPIO27_JS5_2
	
	rtd_maskl(0xb8060240,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO26
	rtd_maskl(0xb806023c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO27

	gpio_err=gpio_vs_gpio('S',26,'S',27);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 26 vs GPI Standby 27 fail \n");
	gpio_err=gpio_vs_gpio('S',27,'S',26);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 27 vs GPI Standby 26 fail \n");

// A2_ST_GPIO28_JP1_3 vs B2_ST_GPIO29_JS1_2
	
	rtd_maskl(0xb806023c,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO28
	rtd_maskl(0xb806023c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO29

	gpio_err=gpio_vs_gpio('S',28,'S',29);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 28 vs GPI Standby 29 fail \n");
	gpio_err=gpio_vs_gpio('S',29,'S',28);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 29 vs GPI Standby 28 fail \n");

// H6_ST_GPIO33_JP2_3 vs J5_ST_GPIO41_JS2_2
	
	rtd_maskl(0xb8060234,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO33
	rtd_maskl(0xb806022c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO41

	gpio_err=gpio_vs_gpio('S',33,'S',41);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 33 vs GPI Standby 41 fail \n");
	gpio_err=gpio_vs_gpio('S',41,'S',33);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 41 vs GPI Standby 33 fail \n"); 

// J6_ST_GPIO34_JP6_2 vs J4_ST_GPIO42_JS6_3

	rtd_maskl(0xb8060234,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO34
	rtd_maskl(0xb8060228,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO42

	gpio_err=gpio_vs_gpio('S',34,'S',42);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 34 vs GPI Standby 42 fail \n");
	gpio_err=gpio_vs_gpio('S',42,'S',34);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 42 vs GPI Standby 34 fail \n"); 

// K5_ST_GPIO44_JP9_2 vs K4_GPIO189_JS9_3

	rtd_maskl(0xb8060228,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO44
	rtd_maskl(0xb8000890,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO189

	gpio_err=gpio_vs_gpio('S',44,'M',189);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 44 vs GPI Main 189 fail \n");
	gpio_err=gpio_vs_gpio('M',189,'S',44);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 189 vs GPI Standby 44 fail \n");	

// L6_GPIO190_JP15_3 vs M5_GPIO3_JS15_2

	rtd_maskl(0xb8000890,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO190
	rtd_maskl(0xb8000894,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO3

	gpio_err=gpio_vs_gpio('M',190,'M',3);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 190 vs GPI Main 3 fail \n");
	gpio_err=gpio_vs_gpio('M',3,'M',190);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 3 vs GPI Main 190 fail \n");	

// K6_ST_GPIO43_JP12_3 vs L5_GPIO191_JS12_2

	rtd_maskl(0xb8060228,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO43
	rtd_maskl(0xb8000890,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO191

	gpio_err=gpio_vs_gpio('S',43,'M',191);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 43 vs GPI Main 191 fail \n");
	gpio_err=gpio_vs_gpio('M',191,'S',43);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 191 vs GPI Standby 43 fail \n");

// N4_GPIO147_JP20_3 vs N5_GPIO146_JS20_2

	rtd_maskl(0xb8000898,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO147
	rtd_maskl(0xb8000898,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO146

	gpio_err=gpio_vs_gpio('M',147,'M',146);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 147 vs GPI Main 146 fail \n");
	gpio_err=gpio_vs_gpio('M',146,'M',147);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 146 vs GPI Main 147 fail \n");

// N6_GPIO148_JP23_3 vs P5_GPIO149_JS23_2

	rtd_maskl(0xb8000898,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO148
	rtd_maskl(0xb800089c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO149

	gpio_err=gpio_vs_gpio('M',148,'M',149);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 148 vs GPI Main 149 fail \n");
	gpio_err=gpio_vs_gpio('M',149,'M',148);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 149 vs GPI Main 148 fail \n");

// AB10_GPIO1_JP63_2 vs AA9_GPIO5_JS63_3

	rtd_maskl(0xb8000800,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO1
	rtd_maskl(0xb8000808,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO5

	gpio_err=gpio_vs_gpio('M',1,'M',5);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 1 vs GPI Main 5 fail \n");
	gpio_err=gpio_vs_gpio('M',5,'M',1);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 5 vs GPI Main 1 fail \n");

// AD9_GPIO197_JP52_3 vs AC9_GPIO7_JS52_2

	rtd_maskl(0xb8000948,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO197
	rtd_maskl(0xb8000808,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO7
	
	gpio_err=gpio_vs_gpio('M',197,'M',7);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 197 vs GPI Main 7 fail \n");
	gpio_err=gpio_vs_gpio('M',7,'M',197);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 7 vs GPI Main 197 fail \n");

// AE10_GPIO6_JP69_2 vs AD10_GPIO199_JS69_3

	rtd_maskl(0xb8000808,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO6
	rtd_maskl(0xb8000948,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO199
	
	gpio_err=gpio_vs_gpio('M',6,'M',199);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 6 vs GPI Main 199 fail \n");
	gpio_err=gpio_vs_gpio('M',199,'M',6);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 199 vs GPI Main 6 fail \n");

// AA10_GPIO198_JP66_3 vs Y10_GPIO8_JS66_2

	rtd_maskl(0xb8000948,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO198
	rtd_maskl(0xb800080c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO8
	
	gpio_err=gpio_vs_gpio('M',198,'M',8);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 198 vs GPI Main 8 fail \n");
	gpio_err=gpio_vs_gpio('M',8,'M',198);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 8 vs GPI Main 198 fail \n");

// AC10_GPIO9_JP73_3 vs AE11_GPIO201_JS73_2

	rtd_maskl(0xb800080c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO9
	rtd_maskl(0xb800094c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO201
	
	gpio_err=gpio_vs_gpio('M',9,'M',201);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 9 vs GPI Main 201 fail \n");
	gpio_err=gpio_vs_gpio('M',201,'M',9);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 201 vs GPI Main 9 fail \n");

// AC11_GPIO200_JP75_2 vs AD11_GPIO11_JS75_3

	rtd_maskl(0xb800094c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO200
	rtd_maskl(0xb8000810,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO11
	
	gpio_err=gpio_vs_gpio('M',200,'M',11);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 200 vs GPI Main 11 fail \n");
	gpio_err=gpio_vs_gpio('M',11,'M',200);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 11 vs GPI Main 200 fail \n");

// Y12_GPIO13_JP84_3 vs AB13_GPIO202_JS84_2

	rtd_maskl(0xb8000810,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO13
	rtd_maskl(0xb800094c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO202
	
	gpio_err=gpio_vs_gpio('M',13,'M',202);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 13 vs GPI Main 202 fail \n");
	gpio_err=gpio_vs_gpio('M',202,'M',13);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 202 vs GPI Main 13 fail \n");

// AB12_GPIO10_JP81_2 vs AA12_GPIO15_JS81_3

	rtd_maskl(0xb800080c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO10
	rtd_maskl(0xb8000814,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO15
	
	gpio_err=gpio_vs_gpio('M',10,'M',15);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 10 vs GPI Main 15 fail \n");
	gpio_err=gpio_vs_gpio('M',15,'M',10);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 15 vs GPI Main 10 fail \n");

// Y11_GPIO12_JP78_2 vs AA11_GPIO204_JS78_3

	rtd_maskl(0xb8000810,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO12
	rtd_maskl(0xb8000950,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO204
	
	gpio_err=gpio_vs_gpio('M',12,'M',204);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 12 vs GPI Main 204 fail \n");
	gpio_err=gpio_vs_gpio('M',204,'M',12);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 204 vs GPI Main 12 fail \n");

// AD13_GPIO17_JP90_3 vs AE13_GPIO18_JS90_2

	rtd_maskl(0xb8000818,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO17
	rtd_maskl(0xb8000818,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO18
	
	gpio_err=gpio_vs_gpio('M',17,'M',18);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 17 vs GPI Main 18 fail \n");
	gpio_err=gpio_vs_gpio('M',18,'M',17);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 18 vs GPI Main 17 fail \n");

// Y13_GPIO205_JP94_2 vs AA13_GPIO20_JS94_3

	rtd_maskl(0xb800081c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO20
	rtd_maskl(0xb8000950,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO205
	
	gpio_err=gpio_vs_gpio('M',205,'M',20);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 205 vs GPI Main 20 fail \n");
	gpio_err=gpio_vs_gpio('M',20,'M',205);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 20 vs GPI Main 205 fail \n");

// Y14_GPIO16_JP53_2 vs AA14_GPIO206_JS53_3

	rtd_maskl(0xb8000954,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO206
	rtd_maskl(0xb8000814,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO16
	
	gpio_err=gpio_vs_gpio('M',16,'M',206);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 16 vs GPI Main 206 fail \n");
	gpio_err=gpio_vs_gpio('M',206,'M',16);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 206 vs GPI Main 16 fail \n");

// AB15_GPIO23_JP60_2 vs AA15_GPIO21_JS60_3

	rtd_maskl(0xb8000820,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO23
	rtd_maskl(0xb800081c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO21
	
	gpio_err=gpio_vs_gpio('M',23,'M',21);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 23 vs GPI Main 21 fail \n");
	gpio_err=gpio_vs_gpio('M',21,'M',23);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 21 vs GPI Main 23 fail \n");

// Y15_GPIO22_JP76_3 vs AB16_GPIO27_JS76_2

	rtd_maskl(0xb8000824,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO27
	rtd_maskl(0xb800081c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO22
	
	gpio_err=gpio_vs_gpio('M',27,'M',22);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 27 vs GPI Main 22 fail \n");
	gpio_err=gpio_vs_gpio('M',22,'M',27);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 22 vs GPI Main 27 fail \n");

// AE14_GPIO25_JP92_2 vs AC13_GPIO35_JS92_3

	rtd_maskl(0xb8000828,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO35
	rtd_maskl(0xb8000820,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO25
	
	gpio_err=gpio_vs_gpio('M',35,'M',25);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 35 vs GPI Main 25 fail \n");
	gpio_err=gpio_vs_gpio('M',25,'M',35);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 25 vs GPI Main 35 fail \n");

// Y17_GPIO28_JP82_2 vs AA17_GPIO30_JS82_3

	rtd_maskl(0xb8000824,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO30
	rtd_maskl(0xb8000824,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO28
	
	gpio_err=gpio_vs_gpio('M',30,'M',28);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 30 vs GPI Main 28 fail \n");
	gpio_err=gpio_vs_gpio('M',28,'M',30);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 28 vs GPI Main 30 fail \n");

// AA16_GPIO26_JP79_3 vs Y16_GPIO31_JS79_2

	rtd_maskl(0xb8000828,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO31
	rtd_maskl(0xb8000820,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO26
	
	gpio_err=gpio_vs_gpio('M',26,'M',31);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 26 vs GPI Main 31 fail \n");
	gpio_err=gpio_vs_gpio('M',31,'M',26);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 31 vs GPI Main 26 fail \n");

// AA18_GPIO36_JP91_3 vs AB18_GPIO37_JS91_2

	rtd_maskl(0xb800082c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO36
	rtd_maskl(0xb800082c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO37
	
	gpio_err=gpio_vs_gpio('M',36,'M',37);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 36 vs GPI Main 37 fail \n");
	gpio_err=gpio_vs_gpio('M',37,'M',36);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 37 vs GPI Main 36 fail \n");

// AC15_GPIO38_JP64_2 vs AD15_GPIO43_JS64_3

	rtd_maskl(0xb800082c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO38
	rtd_maskl(0xb8000834,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO43
	
	gpio_err=gpio_vs_gpio('M',38,'M',43);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 38 vs GPI Main 43 fail \n");
	gpio_err=gpio_vs_gpio('M',43,'M',38);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 43 vs GPI Main 38 fail \n");

/*uart1
// AD20_GPIO53_JP62_3 vs AC20_GPIO54_JS62_2

	rtd_maskl(0xb8000844,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO54
	rtd_maskl(0xb8000840,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO53
	
	gpio_err=gpio_vs_gpio('M',53,'M',54);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 53 vs GPI Main 54 fail \n");
	gpio_err=gpio_vs_gpio('M',54,'M',53);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 54 vs GPI Main 53 fail \n");

*/
//H23_GPIO32_JP85_3 vs H25_GPIO142_JS85_2

	rtd_maskl(0xb800084c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO32
	rtd_maskl(0xb8000850,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO142
	
	gpio_err=gpio_vs_gpio('M',32,'M',142);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 32 vs GPI Main 142 fail \n");
	gpio_err=gpio_vs_gpio('M',142,'M',32);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 142 vs GPI Main 32 fail \n");

// G23_GPIO29_JP83_3 vs H24_GPIO33_JS83_2

	rtd_maskl(0xb800084c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO29
	rtd_maskl(0xb800084c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO33
	
	gpio_err=gpio_vs_gpio('M',29,'M',33);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 29 vs GPI Main 33 fail \n");
	gpio_err=gpio_vs_gpio('M',33,'M',29);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 33 vs GPI Main 29 fail \n");

// G24_GPIO24_JP80_2 vs G22_GPIO85_JS80_3

	rtd_maskl(0xb8000850,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO24
	rtd_maskl(0xb8000850,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO85
	
	gpio_err=gpio_vs_gpio('M',24,'M',85);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 24 vs GPI Main 85 fail \n");
	gpio_err=gpio_vs_gpio('M',85,'M',24);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 85 vs GPI Main 24 fail \n");

// F24_GPIO141_JP77_2 vs F25_GPIO140_JS77_3

	rtd_maskl(0xb80008B8,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO141
	rtd_maskl(0xb80008B8,GetMaskAnd(26,22),0x1F<<22); //pinshare GPIO140

	rtd_maskl(0xb8000c2c,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO141 mode
	rtd_maskl(0xb8000c2c,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO140 mode
	
	gpio_err=gpio_vs_gpio('M',141,'M',140);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 141 vs GPI Main 140 fail \n");
	gpio_err=gpio_vs_gpio('M',140,'M',141);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 140 vs GPI Main 141 fail \n");


// F23_GPIO81_J31_2 vs E25_GPIO82_J31_1

	rtd_maskl(0xb80008b8,0xffc1ffff,0x003e0000); //pinshare GPIO81
	rtd_maskl(0xb80008b8,0xfffe0fff,0x0001f000); //pinshare GPIO82

	rtd_maskl(0xb8000c28,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO81 mode
	rtd_maskl(0xb8000c28,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO82 mode
	
	gpio_err=gpio_vs_gpio('M',81,'M',82);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 81 vs GPI Main 82 fail \n");
	gpio_err=gpio_vs_gpio('M',82,'M',81);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 82 vs GPI Main 81 fail \n");

// E22_GPIO83_J32_2 vs F22_GPIO84_J32_1

	rtd_maskl(0xb80008c0,0xfffff07f,0x00000f80); //pinshare GPIO83
	rtd_maskl(0xb80008c0,0xffffff83,0x0000007c); //pinshare GPIO84

	rtd_maskl(0xb8000c4c,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO83 mode
	rtd_maskl(0xb8000c4c,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO84 mode
	
	gpio_err=gpio_vs_gpio('M',83,'M',84);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 83 vs GPI Main 84 fail \n");
	gpio_err=gpio_vs_gpio('M',84,'M',83);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 84 vs GPI Main 83 fail \n");

// C16_GPIO94_JP27_2 vs A15_GPIO173_JS27_3

	rtd_maskl(0xb800085c,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO94
	rtd_maskl(0xb8000878,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO173
	
	gpio_err=gpio_vs_gpio('M',94,'M',173);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 94 vs GPI Main 173 fail \n");
	gpio_err=gpio_vs_gpio('M',173,'M',94);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 173 vs GPI Main 94 fail \n");

// E9_ST_GPIO7_JP28_2 vs F9_ST_GPIO9_JS28_3

	rtd_maskl(0xb806024c,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO9
	rtd_maskl(0xb806024c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO7
	
	gpio_err=gpio_vs_gpio('S',9,'S',7);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 9 vs GPI Standby 7 fail \n");
	gpio_err=gpio_vs_gpio('S',7,'S',9);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 7 vs GPI Standby 9 fail \n");

// C10_ST_GPIO8_JP3_2 vs B9_ST_GPIO10_JS3_3

	rtd_maskl(0xb8060248,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO10
	rtd_maskl(0xb806024c,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO8
	
	gpio_err=gpio_vs_gpio('S',10,'S',8);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 10 vs GPI Standby 8 fail \n");
	gpio_err=gpio_vs_gpio('S',8,'S',10);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 8 vs GPI Standby 10 fail \n");

// D5_ST_GPIO17_JP40_3 vs E4_ST_GPIO19_JS40_2

	rtd_maskl(0xb8060244,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO19
	rtd_maskl(0xb8060204,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO17
	
	gpio_err=gpio_vs_gpio('S',17,'S',19);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 17 vs GPI Standby 19 fail \n");
	gpio_err=gpio_vs_gpio('S',19,'S',17);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 19 vs GPI Standby 17 fail \n");

// D4_ST_GPIO16_JP36_3 vs E5_ST_GPIO18_JS36_2

	rtd_maskl(0xb8060204,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO18
	rtd_maskl(0xb8060244,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO16
	
	gpio_err=gpio_vs_gpio('S',16,'S',18);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 16 vs GPI Standby 18 fail \n");
	gpio_err=gpio_vs_gpio('S',18,'S',16);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 18 vs GPI Standby 16 fail \n");

/* pad of RTC 
// E7_ST_GPIO35_JP21_2 vs F8_ST_GPIO37_JS21_3

	rtd_maskl(0xb8060234,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO35
	rtd_maskl(0xb8060230,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO37

	
	gpio_err=gpio_vs_gpio('S',35,'S',37);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 35 vs GPI Standby 37 fail \n");
	gpio_err=gpio_vs_gpio('S',37,'S',35);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 37 vs GPI Standby 35 fail \n");
*/
	

//----------------------------------------------------------------------combine----------------------------

// B8_ST_GPIO39_JP49_3 vs E6_ST_GPIO30_JS24_2

	rtd_maskl(0xb806022c,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO39
	rtd_maskl(0xb8060238,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO30
	
	gpio_err=gpio_vs_gpio('S',39,'S',30);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 39 vs GPI Standby 30 fail \n");
	gpio_err=gpio_vs_gpio('S',30,'S',39);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 30 vs GPI Standby 39 fail \n");

// F6_ST_GPIO31_JP29_3 vs G6_ST_GPIO32_JS48_3

	rtd_maskl(0xb8060238,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO32
	rtd_maskl(0xb8060238,GetMaskAnd(22,18),0x1F<<18); //pinshare ST_GPIO31

	
	gpio_err=gpio_vs_gpio('S',32,'S',31);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 32 vs GPI Standby 31 fail \n");
	gpio_err=gpio_vs_gpio('S',31,'S',32);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 31 vs GPI Standby 32 fail \n");


// AB4_GPIO196_JP88_2 vs AB9_GPIO2_JS59_2

	rtd_maskl(0xb8000804,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO2
	rtd_maskl(0xb80008f8,GetMaskAnd(21,17),0x1F<<17); //pinshare GPIO196

	rtd_maskl(0xb80008f8,GetMaskAnd(2,2),0x1<<2); //GPIO196 GPI EN
	
	gpio_err=gpio_vs_gpio('M',2,'M',196);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 2 vs GPI Main 196 fail \n");
	gpio_err=gpio_vs_gpio('M',196,'M',2);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 196 vs GPI Main 2 fail \n");

	rtd_maskl(0xb80008f8,GetMaskAnd(2,2),0x0<<2); //clear GPIO196 GPI EN

// AD12_GPIO14_JP87_3 vs AD16_GPIO203_JS68_3

	rtd_maskl(0xb8000814,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO14
	rtd_maskl(0xb8000950,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO203
	
	gpio_err=gpio_vs_gpio('M',14,'M',203);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 14 vs GPI Main 203 fail \n");
	gpio_err=gpio_vs_gpio('M',203,'M',14);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 203 vs GPI Main 14 fail \n");

// AD14_GPIO19_JP56_3 vs Y18_GPIO34_JS93_3

	rtd_maskl(0xb8000818,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO19
	rtd_maskl(0xb8000828,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO34

	gpio_err=gpio_vs_gpio('M',19,'M',34);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 19 vs GPI Main 34 fail \n");
	gpio_err=gpio_vs_gpio('M',34,'M',19);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 34 vs GPI Main 19 fail \n");

// AC17_GPIO143_JP86_2 vs D15_GPIO92_JS43_2

	rtd_maskl(0xb8000848,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO143
	rtd_maskl(0xb800085c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO92
	
	gpio_err=gpio_vs_gpio('M',143,'M',92);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 143 vs GPI Main 92 fail \n");
	gpio_err=gpio_vs_gpio('M',92,'M',143);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 92 vs GPI Main 143 fail \n");

// B17_GPIO93_JP32_2 vs B15_GPIO95_JS25_2

	rtd_maskl(0xb800085c,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO93
	rtd_maskl(0xb8000860,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO95
	
	gpio_err=gpio_vs_gpio('M',93,'M',95);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 93 vs GPI Main 95 fail \n");
	gpio_err=gpio_vs_gpio('M',95,'M',93);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 95 vs GPI Main 93 fail \n");

// B14_GPIO96_JP22_2 vs B16_GPIO174_JS30_2

	rtd_maskl(0xb8000860,GetMaskAnd(22,18),0x1F<<18); //pinshare GPIO96
	rtd_maskl(0xb800087c,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO174
	
	gpio_err=gpio_vs_gpio('M',96,'M',174);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 96 vs GPI Main 174 fail \n");
	gpio_err=gpio_vs_gpio('M',174,'M',96);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 174 vs GPI Main 96 fail \n");

// C11_GPIO97_JP10_3 vs F11_GPIO171_JS34_2

	rtd_maskl(0xb8000860,GetMaskAnd(13,9),0x1F<<9); //pinshare GPIO97
	rtd_maskl(0xb8000878,GetMaskAnd(31,27),0x1F<<27); //pinshare GPIO171
	
	gpio_err=gpio_vs_gpio('M',97,'M',171);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 97 vs GPI Main 171 fail \n");
	gpio_err=gpio_vs_gpio('M',171,'M',97);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Main 171 vs GPI Main 97 fail \n");

// E10_ST_GPIO12_JP31_2 vs B10_ST_GPIO13_JS7_2

	rtd_maskl(0xb8060248,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO12
	rtd_maskl(0xb8060244,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO13

	
	gpio_err=gpio_vs_gpio('S',12,'S',13);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 12 vs GPI Standby 13 fail \n");
	gpio_err=gpio_vs_gpio('S',13,'S',12);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 13 vs GPI Standby 12 fail \n");

// G4_ST_GPIO22_JP46_3 vs B10_ST_GPIO13_JS7_2

	rtd_maskl(0xb8060240,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO22
	rtd_maskl(0xb8060244,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO13

	
	gpio_err=gpio_vs_gpio('S',22,'S',13);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 22 vs GPI Standby 13 fail \n");
	gpio_err=gpio_vs_gpio('S',13,'S',22);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 13 vs GPI Standby 22 fail \n");

	
/*only one sorting board  
// G4_ST_GPIO22_JP46_3 vs F7_ST_GPIO38_JS24_3

	rtd_maskl(0xb8060240,GetMaskAnd(13,9),0x1F<<9); //pinshare ST_GPIO22
	rtd_maskl(0xb8060230,GetMaskAnd(31,27),0x1F<<27); //pinshare ST_GPIO38
	
	gpio_err=gpio_vs_gpio('S',22,'S',38);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 22 vs GPI Standby 38 fail \n");
	gpio_err=gpio_vs_gpio('S',38,'S',22);
	gpio_sum|=gpio_err;
	if(gpio_err==1)
		printk("GPO Standby 38 vs GPI Standby 22 fail \n");
*/
#endif

#else

	//-----------------------------------------------------------------------------------------------------------------------TV_QFP

	printk("****************************************Package : TV_QFP \n");

	// pin 42_GPIO16_JS19_1 vs pin 43_GPIO17_JS19_2
		
		rtd_maskl(0xb8000814,0xffffc1ff,0x00003e00); //pinshare GPIO16
		rtd_maskl(0xb8000818,0x07ffffff,0xf8000000); //pinshare GPIO17

		gpio_err=gpio_vs_gpio('M',16,'M',17);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 16 vs GPI Main 17 fail \n");
		gpio_err=gpio_vs_gpio('M',17,'M',16);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 17 vs GPI Main 16 fail \n");


	// pin 44_GPIO18_JS22_1 vs pin 45_GPIO19_JS22_2
		
		rtd_maskl(0xb8000818,0xff83ffff,0x007c0000); //pinshare GPIO18
		rtd_maskl(0xb8000818,0xffffc1ff,0x00003e00); //pinshare GPIO19

		gpio_err=gpio_vs_gpio('M',18,'M',19);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 18 vs GPI Main 19 fail \n");
		gpio_err=gpio_vs_gpio('M',19,'M',18);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 19 vs GPI Main 18 fail \n");


	// pin 75_GPIO81_J33_2 vs pin 76_GPIO82_J33_1

		rtd_maskl(0xb80008b8,0xffc1ffff,0x003e0000); //pinshare GPIO81
		rtd_maskl(0xb80008b8,0xfffe0fff,0x0001f000); //pinshare GPIO82

		rtd_maskl(0xb8000c28,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO81 mode
		rtd_maskl(0xb8000c28,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO82 mode
		
		gpio_err=gpio_vs_gpio('M',81,'M',82);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 81 vs GPI Main 82 fail \n");
		gpio_err=gpio_vs_gpio('M',82,'M',81);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 82 vs GPI Main 81 fail \n");

	// pin 90_GPIO83_J34_2 vs pin 91_GPIO84_J34_1
	
		rtd_maskl(0xb80008c0,0xfffff07f,0x00000f80); //pinshare GPIO83
		rtd_maskl(0xb80008c0,0xffffff83,0x0000007c); //pinshare GPIO84

		rtd_maskl(0xb8000c4c,GetMaskAnd(31,29),0x2<<29); //LVDS GPIO83 mode
		rtd_maskl(0xb8000c4c,GetMaskAnd(28,26),0x2<<26); //LVDS GPIO84 mode
		
		gpio_err=gpio_vs_gpio('M',83,'M',84);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 83 vs GPI Main 84 fail \n");
		gpio_err=gpio_vs_gpio('M',84,'M',83);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 84 vs GPI Main 83 fail \n");


	// pin 111_ST_GPIO13_JS23_1 vs pin 114_ST_GPIO16_JS23_2
	
		rtd_maskl(0xb8060244,0xffffc1ff,0x00003e00); //pinshare ST_GPIO13
		rtd_maskl(0xb8060244,0xff83ffff,0x007c0000); //pinshare ST_GPIO16
		
		gpio_err=gpio_vs_gpio('S',13,'S',16);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 13 vs GPI Standby 16 fail \n");
		gpio_err=gpio_vs_gpio('S',16,'S',13);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 16 vs GPI Standby 13 fail \n");

	// pin 115_ST_GPIO17_JS29_1 vs pin 116_ST_GPIO18_JS29_2
	
		rtd_maskl(0xb8060204,0xff83ffff,0x007c0000); //pinshare ST_GPIO17
		rtd_maskl(0xb8060204,0xffffc1ff,0x00003e00); //pinshare ST_GPIO18
		
		gpio_err=gpio_vs_gpio('S',17,'S',18);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 17 vs GPI Standby 18 fail \n");
		gpio_err=gpio_vs_gpio('S',18,'S',17);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 18 vs GPI Standby 17 fail \n");
	// pin 118_ST_GPIO20_JS33_1 vs pin 119_ST_GPIO21_JS33_2

		rtd_maskl(0xb8060208,0x07ffffff,0xf8000000); //pinshare ST_GPIO20
		rtd_maskl(0xb8060208,0xff83ffff,0x007c0000); //pinshare ST_GPIO21
		
		gpio_err=gpio_vs_gpio('S',20,'S',21);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 20 vs GPI Standby 21 fail \n");
		gpio_err=gpio_vs_gpio('S',21,'S',20);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 21 vs GPI Standby 20 fail \n");
		
	//----------------------------------------------------------------------combine----------------------------
	// pin 105_ST_GPIO7_JS18_1 vs pin 107_ST_GPIO9_JS20_1
	 
		rtd_maskl(0xb806024c,0xffffc1ff,0x00003e00); //pinshare ST_GPIO7
		rtd_maskl(0xb806024c,0x07ffffff,0xf8000000); //pinshare ST_GPIO9
		
		gpio_err=gpio_vs_gpio('S',7,'S',9);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 7 vs GPI Standby 9 fail \n");
		gpio_err=gpio_vs_gpio('S',9,'S',7);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 9 vs GPI Standby 7 fail \n");
		

	// pin 62_GPIO52_JS37_1 vs pin 109_ST_GPIO11_JS21_1

		rtd_maskl(0xb8000840,0xff83ffff,0x007c0000); //pinshare GPIO52
		rtd_maskl(0xb806024c,0xff83ffff,0x007c0000); //pinshae ST_GPIO11
		
		gpio_err=gpio_vs_gpio('M',52,'S',11);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 52 vs GPI Standby 11 fail \n");
		gpio_err=gpio_vs_gpio('S',11,'M',52);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Standby 11 vs GPI Main 52 fail \n");

	// pin 62_GPIO52_JS37_1 vs pin 172_GPIO125_JS120_2
	
		rtd_maskl(0xb8000840,0xff83ffff,0x007c0000); //pinshare GPIO52
		rtd_maskl(0xb80008e4,0xfffff07f,0x00000f80); //pinshae GPIO125
		rtd_maskl(0xb80008e4,GetMaskAnd(0,0),0x1<<0); //GPIO125 GPI EN
		
		gpio_err=gpio_vs_gpio('M',52,'M',125);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 52 vs GPI Main 125 fail \n");
		gpio_err=gpio_vs_gpio('M',125,'M',52);
		gpio_sum|=gpio_err;
		if(gpio_err==1)
			printk("GPO Main 125 vs GPI Main 52 fail \n");

		rtd_maskl(0xb80008e4,GetMaskAnd(0,0),0x0<<0); //clear GPIO125 GPI EN


#endif

	if(gpio_sum==0)
		return 0;
	else
		return 1;

}
