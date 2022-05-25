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
bool Start_Cook_Time = 0;
char state;
int main(void){
	microwave_Init();
	
	
	while(1){
		
		LCD_Show("Enter a Choice");	 //display on LCD
		state =KeyScan();// take input from kaypad
		switch(state){ 
			case popcorn: 
				valid_Input = 1; //set vaild flag
				LCD_Clear_Display(); // clear LCD 
				cook_Popcorn(); 
				break;
			case beef:
				valid_Input = 1;//set vaild flag
				LCD_Clear_Display(); // clear LCD 
				cook_Beef_or_Chicken(beef);
				break;
			case chicken:
				valid_Input = 1;//set vaild flag
				LCD_Clear_Display(); // clear LCD 
				cook_Beef_or_Chicken(chicken);
				break;
			case cookTime:
				valid_Input = 1;//set vaild flag
				LCD_Clear_Display(); // clear LCD 
				do{
					Cook_Time_Again = 0; // reset the timer reset flag
					Cook_Time();
				}
				while(Cook_Time_Again); // wait until the timer reset flag is reset
				break;
			default:
				valid_Input = 0; //reset vaild flag
				LCD_Clear_Display(); //clear LCD 
				LCD_Show("Not valid");//display on LCD 
				Systick_Wait_ms(1000); // wait 1 second
				LCD_Clear_Display();//display on LCD 
				break;
		}
		START=0; //reset start flag
		while(valid_Input){ // wait valid input 
			if(START == 1 || Start_Cook_Time == 1){	//check if sw2 is pressed 
				start();
				break;
			}
		}
	}
}
// GPIOF_Handler: this function is used to handle interrupts made by SW1 & SW2
void GPIOF_Handler(void)
{	
	if ((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==0) && (!Cook_Time_f) )//if the interrupt flag by of is set & SW1 wasn't pressed anytime before this interruption & you aren't at the function Cook_Time
    { //pause
			RESET=0;
			START=0; 
			PAUSE=1;
			SW1_Press_Counts=1;	
			GPIO_PORTF_ICR_R |= 0x10; //clear interrupt flag
			
    }
	else if((GPIO_PORTF_MIS_R & 0x10) && (SW1_Press_Counts==1))//if the interrupt flag of SW1 is set & SW1 is pressed one time 
		{//reset
			RESET=1;
			START=0; 
			PAUSE=0;
			SW1_Press_Counts=0;
      GPIO_PORTF_ICR_R |= 0x10;//clear interrupt flag
    }
	else if((GPIO_PORTF_MIS_R & 0x10) && (Cook_Time_f)){//if the interrupt flag of SW1 is set & you are at Cook_Time function
			Cook_Time_Again = 1; // clear the Cook_Time and call Cook_Time again
			GPIO_PORTF_ICR_R |= 0x10;//clear interrupt flag of SW1
	}
	
	if((GPIO_PORTF_MIS_R & 0x01) && (!Cook_Time_f)) 
		{
			RESET=0;
			START=1; 
			PAUSE=0;
			SW1_Press_Counts=0;
			GPIO_PORTF_ICR_R |= 0x01; 
		}	
	else if((GPIO_PORTF_MIS_R & 0x01) && (Cook_Time_f)){
			Start_Cook_Time = 1;
			RESET=0;
			START=1; 
			PAUSE=0;
			SW1_Press_Counts=0;
			GPIO_PORTF_ICR_R |= 0x01; 
		}
	
}

