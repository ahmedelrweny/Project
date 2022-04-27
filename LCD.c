#include "defines.h"
#include <inttypes.h>
#include "tiva.h"

void LCD_Init(){

    System_Init(); // Port A - B
    //Enable PortA bits 0-2 for Rs Rw Enable
    GPIO_PORTA_CR_R |= 0x07;
		GPIO_PORTA_AMSEL_R &= ~0x07;
		GPIO_PORTA_PCTL_R &= ~0x0000FFF;
		GPIO_PORTA_AFSEL_R &= ~0x07;
		GPIO_PORTA_DIR_R |= 0x07;						
		GPIO_PORTA_DEN_R |= 0x07;	
		//Enable port B bits 0-7 for
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;
		GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		GPIO_PORTB_AFSEL_R &= ~0xFF;
		GPIO_PORTB_DIR_R |= 0xFF;						
		GPIO_PORTB_DEN_R |= 0xFF;	

}
