#include <common.h>
#include <asm/io.h>

#include <qc_verify.h>
#include <qc_verify_common.h>
#include <qc_verify_def.h>

struct hex_data
{
    unsigned int addr; 
    unsigned int data; 
};

#include "CAMACI3_Sony_C.jsv.hex.h"

#define SWAP(DATA) (((DATA>>24)&0xff)|((DATA>>8)&0xff00)|((DATA<<8)&0x00ff0000)|((DATA<<24)&0xff000000))

#define VIDEO_FW_ENTRY_PTR_V1	0x00001ffc
#define REG_HW_SEMAPHORE		0xb801a000

/* v_entry when vcpu jump form romcode */
#define MIPS_V_ENTRY_QC_CODE_ADDR 0x310000
#define V_ENTRY_FROM_ROMCODE	(0xa0000000|MIPS_V_ENTRY_QC_CODE_ADDR)

/* v entry from dv pattern */
#define V_ENTRY_VE_PARTTEN		0x80004000

#define VE_DEBUG
#ifdef VE_DEBUG
#define debug(fmt,args...)	printf (fmt ,##args)
#else
#define debug(fmt,args...)	
#endif

extern int _f_v_entry_qc_img, _e_v_entry_qc_img;

#ifdef VE_DEBUG
void hexdump(const char *str, const void *buf, unsigned int length)
{
	unsigned int i;
	unsigned char *ptr = (unsigned char *)buf;
	
	if ((buf == NULL) || (length == 0)) {
		printf("NULL\n");
		return;
	}

	printf("\n%s (0x%x)\n", (str == NULL ? __FUNCTION__ : str), (unsigned int )buf);

	for (i = 0; i < length; i++) {
		printf("%02x ", ptr[i]);

		if ((i & 0xf) == 0xf)
			printf("\n");
	}
	printf("\n\n");
}
#endif

void ddr_debug_01 (void)
{
	debug("\n%s\n", __FUNCTION__);

    unsigned long addr = 0x01fff000;
	unsigned int check_status;

#ifdef VE_DEBUG
	unsigned int i;

	for (i = 0;i < 0x100; i += 4) {
		rtd_outl(0x11000000 + i, 0x0);
	}
#endif
	
	while(1)
	{
		check_status = rtd_inl(addr);
		
		if (check_status == 0)
		{
			//debug("ve_idle       %x\n", check_status);
		}
		else if (check_status == 0x02000000)
		{
			debug("ve_done?       %x\n", check_status);
			break;
		}
		else if (check_status == 0x03000000)
		{
			debug("ve_crc_err?       %x\n", check_status);
			break;
		}
		else if (check_status == 0x01000000)
		{
			//debug("ve_busy?       %x\n", check_status);
			udelay(200);
		}
		else
		{
			//debug("VE other ?       %x\n", check_status);
		}
	}
}

void enable_vcpu (void)
{
	debug("%s\n", __FUNCTION__);

	//hold hw semaphore
	rtd_outl(REG_HW_SEMAPHORE, 0x1);

	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); 
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// rst = 1
	rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); 
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);

	//release hw semaphore
	rtd_outl(REG_HW_SEMAPHORE, 0x0);
	
	return;
}

void disable_vcpu(void)
{
	debug("%s\n", __FUNCTION__);

	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);

	return;
}

void prepare_binary(struct hex_data * hex_addr, int len)
{
	debug("%s\n", __FUNCTION__);

	unsigned int i;

	rtd_outl(0x00002120,0x01000000); //vcpu-only test
	//rtd_outl(0xb800e420,0x00800000); //this will hang @ Sirius
	rtd_outl(0x01fff080,0x00000000); //ve計算CRC需要用到 
	rtd_outl(0x01fff084,0x00000000); //ve計算CRC需要用到 
	rtd_outl(0x01fff000,0xFFFF0000); //ve計算CRC需要用到 

	for (i = 0;i < len; i++) {
		//printf("%08d 0x%08x(0x%08x) = 0x%08x(0x%08x)\n", i, hex_addr[i].addr, &(hex_addr[i].addr), hex_addr[i].data, &(hex_addr[i].data));
		rtd_outl(hex_addr[i].addr, hex_addr[i].data);
	}

	debug("write word count: %d\n", i);

	rtd_outl(0x01fff040,0x00000000); //frame decode cnt
	rtd_outl(0x01fff06c,0x00000000); //frame display cnt
	rtd_outl(0x01fff41c,0x00000000); //start_frame
	rtd_outl(0x00002f40,0x00000000); //end_frame
	rtd_outl(0x00002f4c,0x00000000); //0:decoding order
	rtd_outl(0x00002f50,0x04000000); //decoder configuration word
	rtd_outl(0x00002f54,0x01000000); //crc check

	rtd_outl(0x00002104,0xbabebabe); //先設定成test pass 
	rtd_outl(0x00002120,0x01000000);
	rtd_outl(0x0000210c,SWAP(V_ENTRY_FROM_ROMCODE)); //when finish vcpu will jump to this entry again
	rtd_outl(0x00002100,0x01000000); //開始run 

	return;
}

void prepare_ventry(void)
{
	unsigned char *a,*b;

	// copy .v_entry_qc  (VCPU)
	debug("copy v_entry_qc 0x%x\n", MIPS_V_ENTRY_QC_CODE_ADDR);
	a = (unsigned char *)&_e_v_entry_qc_img;
	b = (unsigned char *)&_f_v_entry_qc_img;
	memcpy((unsigned char *)MIPS_V_ENTRY_QC_CODE_ADDR, b, a-b);

	rtd_outl(VCPU_JUMP_ADDR_reg, V_ENTRY_FROM_ROMCODE);
	debug("video from romcode entry = 0x%08x\n", rtd_inl(VCPU_JUMP_ADDR_reg));

	rtd_outl(VIDEO_FW_ENTRY_PTR_V1, SWAP(V_ENTRY_VE_PARTTEN));
	debug("video dv entry = 0x%08x\n", rtd_inl(VIDEO_FW_ENTRY_PTR_V1));

	return;
}

int run_hex (struct hex_data * hex_addr, int len, char * str)
{
	debug("%s\n", __FUNCTION__);

	unsigned int tMs;

	prepare_binary(hex_addr, len);
	prepare_ventry();

	flush_dcache_all();
	timer_7_reset();
	
	enable_vcpu();

	ddr_debug_01();
	
	disable_vcpu();

	tMs = rtd_inl(TC7CVR);
	tMs = tMs/27000;
	
	printf("\n%s	finish!		tMs=%d\n", str, tMs);
	printf("test result = 0x%x\n", rtd_inl(0x00002104));

	if (0xbabebabe != rtd_inl(0x00002104))
	{
		printf("FAIL\n");
		return 1; 
	}
	else
	{
		printf("PASS\n");
		return 0;
	}
}

int QC_Verifier_VE(void)
{
	int ret = 0;

	debug("%s\n", __FUNCTION__);

	ret = run_hex(CAMACI3_Sony_C, (sizeof(CAMACI3_Sony_C)/sizeof(struct hex_data)), "CAMACI3_Sony_C");
	
	debug("%s %d\n", __FUNCTION__, ret);

	return (ret == 0) ? SUCCESS:FAILED;
} 
