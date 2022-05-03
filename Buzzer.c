#include "defines.h"
#include <inttypes.h>


void buzzer_Init(void){
		GPIO_PORTD_CR_R |= 0x80; 						//repeat without unlocking
		GPIO_PORTD_AMSEL_R &= ~0x80;
		GPIO_PORTD_PCTL_R &= ~0xf0000000;
		GPIO_PORTD_AFSEL_R &= ~0x80;
		GPIO_PORTD_DIR_R |= 0x80;
		GPIO_PORTD_DEN_R |= 0x80;
}

void beep(void){
	GPIO_PORTD_DATA_R |= 0x80;
}

void stop_Beep(void){
	GPIO_PORTD_DATA_R &= ~0x80;
}
