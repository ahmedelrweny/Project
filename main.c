#include "Tiva.h"
#include "Switch.h"
#include "Buzzer.h"
#include "keypad.h"
#include "LCD.h"
#include "Timer.h"
#include "LED.h"
#include "Switch.h"
#include "defines.h"
#include <inttypes.h>
#include "Interrupt.h"
#include "Microwave.h"



int main(void){
	microwave_Init();
	while(1){
		switch(KeyScan()){
			
			case 'A':
				cook_Popcorn();
			break;
			case 'B':
				cook_Beef_or_Chicken('B');
			break;
			case 'C':
				cook_Beef_or_Chicken('C');
			break;
			case 'D':
				Cook_Time();
			break;
			default:
				LCD_String("Please enter a valid choice");
			break;
		}	
	}
}

void GPIOF_Handler(void)
{	
  if (GPIO_PORTF_MIS_R & 0x10) /* check if interrupt causes by PF4/SW1*/
    {   
      //pause
      GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
    } 
}

