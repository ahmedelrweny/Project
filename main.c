#include "Tiva.h"
#include "Extern.h"
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



int main(void){
	microwave_Init();	  
	while(1){
		LCD_Show("Enter a Choice");	
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
				valid_Input = 1;
				LCD_Clear_Display();
				Cook_Time();
			break;
			default:
				LCD_Clear_Display();
		    LCD_Show("Not valid");
				Systick_Wait_ms(1000);
				LCD_Clear_Display();
				START=0;
				break;
		}
		while(1){
			if(START == 1){	
				start();
				break;
			}
		}
	}
}

void GPIOF_Handler(void)
{	
	if ((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==0) )
    { 
			RESET=0;
			START=0; 
			PAUSE=1;
			SW1_Press_Counts=1;	
			GPIO_PORTF_ICR_R |= 0x10;
		}
	else if((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==1))
		{
			RESET=1;
			START=0; 
			PAUSE=0;
			SW1_Press_Counts=0;
      GPIO_PORTF_ICR_R |= 0x10;
    }
	 
	if((GPIO_PORTF_MIS_R & 0x01)) 
		{
			RESET=0;
			START=1; 
			PAUSE=0;
			SW1_Press_Counts=0;
			GPIO_PORTF_ICR_R |= 0x01; 
		}	
	
}


