#include "defines.h"
#include <inttypes.h>


void buzzer_Init(void){
	GPIO_PORTD_CR_R |= 0x08; 						//repeat without unlocking
	GPIO_PORTD_AMSEL_R &= ~0x08;				//analog disable for PD3
	GPIO_PORTD_PCTL_R &= ~0x0000F000;		//use PD3 as GPIO
	GPIO_PORTD_AFSEL_R &= ~0x08;				//disable alternate function of PD3
	GPIO_PORTD_DIR_R |= 0x08;						//use PD3 as output
	GPIO_PORTD_DEN_R |= 0x08;						//digital enable for PD3
}
// a function is used when the countdown ends
void beep(void){
	GPIO_PORTD_DATA_R |= 0x08;
}

// used after function beeb every time 
void stop_Beep(void){
	GPIO_PORTD_DATA_R &= ~0x08;
}
