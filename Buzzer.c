#include "defines.h"
#include <inttypes.h>


void buzzer_Init(void){
	GPIO_PORTD_CR_R |= 0x08; 						//repeat without unlocking
	GPIO_PORTD_AMSEL_R &= ~0x08;
	GPIO_PORTD_PCTL_R &= ~0x0000F000;
	GPIO_PORTD_AFSEL_R &= ~0x08;
	GPIO_PORTD_DIR_R |= 0x08;
	GPIO_PORTD_DEN_R |= 0x08;
}

void beep(void){
	GPIO_PORTD_DATA_R |= 0x08;
}

void stop_Beep(void){
	GPIO_PORTD_DATA_R &= ~0x08;
}
