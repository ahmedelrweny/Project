#include "defines.h"
#define NVIC_ST_CTRL_R     (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R   (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R  (*((volatile unsigned long *)0xE000E018))


void Systick_Wait_1ms(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 80000-1;   //0x00fffffffff;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R = 0x05;
	while((NVIC_ST_CTRL_R & 0x00010000)==0){}
}	
void Systick_Wait_ms(unsigned int time)
{
	unsigned int j;
	for(j=0;j<time;j++)
	{
		Systick_Wait_1ms();
	}
}

void Systick_Wait_1s(void)
{
	unsigned int j;
	for(j=0;j<1000;j++)
	{
		Systick_Wait_1ms();
	}
}

void Systick_Wait_s(unsigned int time)
{
	unsigned int j;
	for(j=0;j<time;j++)
	{
		Systick_Wait_1s();
	}
}
