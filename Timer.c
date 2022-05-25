#include "defines.h"
#include <inttypes.h>

// a function waits for generic delay
void SysTick_Wait (unsigned int delay) {
	NVIC_ST_CTRL_R = 0;												 //disable control 
	NVIC_ST_RELOAD_R = delay-1; 							 //assign the reload value to reload register
	NVIC_ST_CURRENT_R = 0; 										 //write anything to the current register to clear it
	NVIC_ST_CTRL_R = 0x05; 										 // enable control and CLK_SRC
	while ((NVIC_ST_CTRL_R&0x00010000)==0){}   // wait until the counter is finished
}

void Systick_Wait_1ms(void)
{
	SysTick_Wait(16000);
}	

/* a function waits multiples of milli-seconds */
void Systick_Wait_ms(unsigned int time)
{
	unsigned int j;
	for(j=0;j<time;j++)  											 // the variable time is used to indicate the multiples of milli-seconds you want
	{
		Systick_Wait_1ms();
	}

}

