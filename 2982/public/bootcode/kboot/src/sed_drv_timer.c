#include "sed_common.h"
#include "sed_drv_timer.h"

void sed_timer_start()
{
	/* Use MISC timer6 to get tick SIRIUS(27MHz) */
	/* One tick: Sirius(37ns)  */
	REG32(0xb801b618) = 0xffffffff;
	REG32(0xb801b658) = 0x80000000;
}

// it is start form 0
// the timer tick will be 27M/per second
uint32 sed_timer_getstamp()
{
	return REG32(0xb801b638);	
}

void sed_timer_stop()
{
	REG32(0xb801b658) = 0x00000000;	
}

void sed_timer_1s_delay_example()
{
	uint32 tick1=0, tick2=0;
	sed_timer_start();
	tick1 = sed_timer_getstamp();
	//sed_printf("start\n");
	tick2 = sed_timer_getstamp();
	// counting to 27M
	while(tick2-tick1<27000000)
	{
		tick2 = sed_timer_getstamp();
	}
	sed_printf("after 1s\n");
}

