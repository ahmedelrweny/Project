#include "defines.h"
#include <inttypes.h>

void LED_Init(void){
	
		GPIO_PORTF_LOCK_R = 0x4C4F434B; //Repeat
		GPIO_PORTF_CR_R |= 0x0E;
		GPIO_PORTF_AMSEL_R &= ~0x0E;
		GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
		GPIO_PORTF_AFSEL_R &= ~0x0E;
		GPIO_PORTF_DIR_R |= 0x0E;
		GPIO_PORTF_DEN_R |=0x0E;
		GPIO_PORTF_DATA_R &= ~0x0E;
}
void LED_Clear(void){
		GPIO_PORTF_DATA_R &= ~0x0E;
}

void RedOn(void){
		GPIO_PORTF_DATA_R |= 0x2;
}

void BlueOn(void){
		GPIO_PORTF_DATA_R |= 0x4;
}

void GreenOn(void){
		GPIO_PORTF_DATA_R |= 0x8;
}

void WhiteOn(void){
		GPIO_PORTF_DATA_R |= 0xE;
}

void RedToggle(void){
		GPIO_PORTF_DATA_R ^= 0x2;
}

void BlueToggle(void){
		GPIO_PORTF_DATA_R ^= 0x4;
}

void GreenToggle(void){
		GPIO_PORTF_DATA_R ^= 0x8;
}
