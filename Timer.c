#include "defines.h"
#include <inttypes.h>
void SysTick_Init (void) {
	 NVIC_ST_CTRL_R = 0; 
 	 NVIC_ST_RELOAD_R = 0x00FFFFFF; 
   NVIC_ST_CURRENT_R = 0;
	 NVIC_ST_CTRL_R = 0x00000005; }

void SysTick_Wait (uint32_t delay) {
	NVIC_ST_RELOAD_R = delay-1; 
	NVIC_ST_CURRENT_R = 0; 
	while ((NVIC_ST_CTRL_R&0x00010000)==0){} }

	void SysTick_Wait10ms (uint32_t delay) { 
		unsigned long i; 
		for (i=0; i<delay; i++) {
			SysTick_Wait(800000); }}

