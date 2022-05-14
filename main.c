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
#include "stdbool.h"

char input;
static int SW1_Pressed=0;
static bool started=false;
int main(void){
	microwave_Init();
	LCD_Show("Enter a Choice");
	
	while(1){
	
	switch(KeyScan())
	{
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
  /*SW1 interrupts handling*/
	if (GPIO_PORTF_MIS_R & 0x10 && SW1_Pressed==0) /* check if interrupt causes by PF4/SW1 for one time*/
    {   
      pause();
			started=false; //which means that you are stopped
			SW1_Pressed=1;
      GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
    }
	else if(GPIO_PORTF_MIS_R & 0x10 && SW1_Pressed==1)
		{
			reset();
			started=false; //which means that you are stopped
			SW1_Pressed=0;
      GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
    }
	 /*SW2 interrupts handling*/	
	if((!started)&&(GPIO_PORTF_MIS_R & 0x01) && (SW3_Input() != 0x04)) /* check if interrupt is caused by PF0/SW2 and the door is closed*/
		{
			start();
			started=true;
			GPIO_PORTF_ICR_R |= 0x01; /* clear the interrupt flag */
		}	
	else if ((GPIO_PORTF_MIS_R & 0x01) && (SW3_Input() == 0x04))/* check if interrupt is caused by PF0/SW2 and the door is open*/
		{
			LCD_Show("close door & push SW2"); /*close the door to be able to start then push SW2 to start*/
			GPIO_PORTF_ICR_R |= 0x01; /* clear the interrupt flag */
		}
}

void GPIOD_Handler(void)
{
	/*SW3 interrupts handling*/	
  if (GPIO_PORTD_MIS_R & 0x04) /* check if interrupt is caused by PD2/SW3*/
    {
      pause();
			started=false; //which means that you are stopped
      GPIO_PORTD_ICR_R |= 0x04; /* clear the interrupt flag */
    }
}