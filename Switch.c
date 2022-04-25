#include "defines.h"
#include <inttypes.h>

void SW1_Init(){
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R |= 0x10;
		GPIO_PORTF_AMSEL_R &= ~0x10;
		GPIO_PORTF_PCTL_R &= ~0x000F0000;
		GPIO_PORTF_AFSEL_R &= ~0x10;
		GPIO_PORTF_DIR_R &= ~0x10;
		GPIO_PORTF_PUR_R |= 0x10;
		GPIO_PORTF_DATA_R &= ~0x0E;
		GPIO_PORTF_DEN_R |=0x10;
}

void SW2_Init(){
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R |= 0x01;
		GPIO_PORTF_AMSEL_R &= ~0x01;
		GPIO_PORTF_PCTL_R &= ~0x0000000F;
		GPIO_PORTF_AFSEL_R &= ~0x01;
		GPIO_PORTF_DIR_R &= ~0x01;
		GPIO_PORTF_PUR_R |= 0x01;
		GPIO_PORTF_DATA_R &= ~0x0E;
		GPIO_PORTF_DEN_R |=0x01;
}

unsigned char SW1_Input(){
		return GPIO_PORTF_DATA_R & 0x10;
}

unsigned char SW2_Input(){
		return GPIO_PORTF_DATA_R & 0x01;
}