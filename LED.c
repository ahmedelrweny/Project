#include "defines.h"
#include <inttypes.h>

void LED_Init(void){
	
		GPIO_PORTF_LOCK_R = 0x4C4F434B;          //unlocking port f
		GPIO_PORTF_CR_R |= 0x0E;								 //allows changes in bits
		GPIO_PORTF_AMSEL_R &= ~0x0E;						 //disable analog functions
		GPIO_PORTF_PCTL_R &= ~0x0000FFF0;				 //clearing wanted pin
		GPIO_PORTF_AFSEL_R &= ~0x0E;						 //disable alternate func.
		GPIO_PORTF_DIR_R |= 0x0E;								 //assign as input
		GPIO_PORTF_DEN_R |=0x0E;								 //turn on pull up Resistance
		GPIO_PORTF_DATA_R &= ~0x0E;							 //digital enable pins
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
