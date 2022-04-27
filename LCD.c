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

}
