#include "defines.h"
#include <inttypes.h>


void buzzer_Init(void){
		GPIO_PORTE_CR_R |= 0x02; 						//repeat neither unlocking nor pull up
		GPIO_PORTE_AMSEL_R &= ~0x02;
		GPIO_PORTE_PCTL_R &= ~0x000000F0;
		GPIO_PORTE_AFSEL_R &= ~0x02;
		GPIO_PORTE_DIR_R |= 0x02;						//set as output
		GPIO_PORTE_DEN_R |= 0x02;					
}

void beep(void){
	GPIO_PORTE_DATA_R |= 0x02;
}

void stop_Beep(void){
	GPIO_PORTE_DATA_R &= ~0x02;
}
