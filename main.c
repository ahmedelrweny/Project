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

char input;

int main(void){
	System_Init();
	buzzer_Init();
	LED_Init();
	SW1_Init();
	SW2_Init();
	SW3_Init();
	interrupt_Init();
	
	while(1){
		beep();
		/*switch(input){
		case 1:
			cook_Popcorn();
			break;
		case 2:
			cook_Chiken();
			break;
		case 3:
			cook_Beef();
			break;
		case 4:
			cook_Time();
			break;
		default:
			LCD_Show("Please enter a choice");
			break;
		}*/
	}	
}

void GPIOF_Handler(void)
{	
  if (GPIO_PORTF_MIS_R & 0x10) /* check if interrupt causes by PF4/SW1*/
    {   
      //YOUR CODE HERE MONGED & REDA (SW1)
      GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
    } 
    else if (GPIO_PORTF_MIS_R & 0x01) /* check if interrupt causes by PF0/SW2 */
    {   
     //YOUR CODE HERE MONGED & REDA (SW2)
			GPIO_PORTF_ICR_R |= 0x01; /* clear the interrupt flag */
    }
}

void GPIOD_Handler(void)
{	
  if (GPIO_PORTD_MIS_R & 0x40) /* check if interrupt causes by PD6/SW3*/
    {   
      //YOUR CODE HERE MONGED & REDA (SW3)
			beep();
      GPIO_PORTD_ICR_R |= 0x40; /* clear the interrupt flag */
		}    
}
