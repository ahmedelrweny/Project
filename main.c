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
	LCD_Show("Enter a Choice");
	
	while(1){
		switch(KeyScan()){
			case 'A':
				LCD_Clear_Display();
				cook_Popcorn();
			break;
			case 'B':
				LCD_Clear_Display();
				cook_Beef_or_Chicken('B');
			break;
			case 'C':
				LCD_Clear_Display();
				cook_Beef_or_Chicken('C');
			break;
			case 'D':
				LCD_Clear_Display();
				Cook_Time();
			break;
			default:
				LCD_Clear_Display();
				LCD_Show("Not valid");
				Systick_Wait_ms(1000);
				LCD_Clear_Display();
			break;
		}	
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
  if (GPIO_PORTD_MIS_R & 0x04) /* check if interrupt causes by PD2/SW3*/
    {   
      //YOUR CODE HERE MONGED & REDA (SW3)
      GPIO_PORTD_ICR_R |= 0x04; /* clear the interrupt flag */
		}    
}
