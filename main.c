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
	keypad_Init();
	LCD_Init();
	//LED_Init();
	SW1_Init();
	SW2_Init();
	SW3_Init();
	interrupt_Init();
	
	while(1){
		/*switch( KeyScan()){
		case 'A':
			cook_Popcorn();
			break;
		case 'B';
			cook_Chiken();
			break;
		case 'C':
			cook_Beef();
			break;
		case 'D':
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
  if (GPIO_PORTD_MIS_R & 0x04) /* check if interrupt causes by PD6/SW3*/
    {   
      //YOUR CODE HERE MONGED & REDA (SW3)
      GPIO_PORTD_ICR_R |= 0x04; /* clear the interrupt flag */
		}    
}
