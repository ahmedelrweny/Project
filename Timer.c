#include "defines.h"
#include <inttypes.h>

void SysTick_Wait (unsigned int delay) {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = delay-1; 
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x05;
	while ((NVIC_ST_CTRL_R&0x00010000)==0){} 
}


void Systick_Wait_1ms(void)
{
	SysTick_Wait(16000);
}	
void Systick_Wait_ms(unsigned int time)
{
	unsigned int j;
	for(j=0;j<time;j++)
	{
		Systick_Wait_1ms();
	}
}

