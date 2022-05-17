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


char started = 0;
char SW1_Press_Counts = 0;

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
		while(1){
			if(started == 1){
				start();
				break;
			}
		}
	}
}

void GPIOF_Handler(void)
{	
	if ((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==0))
    {   
      pause();
			started=0; 
			SW1_Press_Counts=1;
      GPIO_PORTF_ICR_R |= 0x10; 
    }
	else if((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==1))
		{
			reset();
			started=0; 
			SW1_Press_Counts=0;
      GPIO_PORTF_ICR_R |= 0x10;
    }
	 
	if((!started) && (GPIO_PORTF_MIS_R & 0x01)) 
		{
			started=1;
			GPIO_PORTF_ICR_R |= 0x01; 
		}	
	
}

void GPIOD_Handler(void)
{
  if (GPIO_PORTD_MIS_R & 0x04) 
    {
      pause();
			started=0; 
      GPIO_PORTD_ICR_R |= 0x04; 
    }
}

