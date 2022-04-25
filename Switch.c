#include "defines.h"
#include <inttypes.h>
//*init functions*

void SW1_Init(void){
	
		GPIO_PORTF_LOCK_R = 0x4C4F434B; 		//unlocking port f
		GPIO_PORTF_CR_R |= 0x10; 						//allows changes in bits
		GPIO_PORTF_AMSEL_R &= ~0x10;				//disable analog functions
		GPIO_PORTF_PCTL_R &= ~0x000F0000;		//clearing wanted pin
		GPIO_PORTF_AFSEL_R &= ~0x10;		 		//disable alternate func.
		GPIO_PORTF_DIR_R &= ~0x10;			 		//assign as input
		GPIO_PORTF_PUR_R |= 0x10;				 		//turn on pull up Resistance
		GPIO_PORTF_DEN_R |=0x10; 				 		//digital enable pins
}

void SW2_Init(void){
	
		GPIO_PORTF_LOCK_R = 0x4C4F434B; 		//repeat
		GPIO_PORTF_CR_R |= 0x01;
		GPIO_PORTF_AMSEL_R &= ~0x01;
		GPIO_PORTF_PCTL_R &= ~0x0000000F;
		GPIO_PORTF_AFSEL_R &= ~0x01;
		GPIO_PORTF_DIR_R &= ~0x01;
		GPIO_PORTF_PUR_R |= 0x01;
		GPIO_PORTF_DEN_R |=0x01;
}

void SW3_Init(void){
	
		GPIO_PORTE_CR_R |= 0x01; 						//repeat without unlocking
		GPIO_PORTE_AMSEL_R &= ~0x01;
		GPIO_PORTE_PCTL_R &= ~0x0000000F;
		GPIO_PORTE_AFSEL_R &= ~0x01;
		GPIO_PORTE_DIR_R &= ~0x01;
		GPIO_PORTE_DEN_R |=0x01;
}

//*input functions*

unsigned char SW1_Input(void){
	
		return GPIO_PORTF_DATA_R & 0x10; 		
}

unsigned char SW2_Input(void){
	
		return GPIO_PORTF_DATA_R & 0x01;
}

unsigned char SW3_Input(void){
	
		return GPIO_PORTE_DATA_R & 0x01;
}
