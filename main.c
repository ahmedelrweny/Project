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

bool START = 0;
bool PAUSE = 0;
bool RESET = 0;
bool SW1_Press_Counts = 0;
bool valid_Input = 0;
bool Cook_Time_f = 0;
bool Cook_Time_Again = 0;

int main(void){
	microwave_Init();
	
	
	while(1){
		
		LCD_Show("Enter a Choice");	
		
		switch(KeyScan()){
			case 'A':
				valid_Input = 1;
				LCD_Clear_Display();
				cook_Popcorn();
			break;
			case 'B':
				valid_Input = 1;
				LCD_Clear_Display();
				cook_Beef_or_Chicken('B');
			break;
			case 'C':
				valid_Input = 1;
				LCD_Clear_Display();
				cook_Beef_or_Chicken('C');
			break;
			case 'D':
				valid_Input = 1;
				LCD_Clear_Display();
				do{
					Cook_Time_Again = 0;
					Cook_Time();
				}
				while(Cook_Time_Again);
			break;
			default:
				valid_Input = 0;
				LCD_Clear_Display();
				LCD_Show("Not valid");
				Systick_Wait_ms(1000);
				LCD_Clear_Display();
				break;
		}
		while(valid_Input){
			if(START == 1){	
				start();
				break;
			}
		}
	}
}

void GPIOF_Handler(void)
{	
	if ((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==0) && (!Cook_Time_f) )
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
	else if((GPIO_PORTF_MIS_R & 0x10) && (Cook_Time_f)){
		Cook_Time_Again = 1;
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

