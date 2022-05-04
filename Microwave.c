#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#include "LCD.h"
#include <string.h>
#include "Keypad.h"


void microwave_Init(void){
	 
}
void cook_Popcorn(){
	int i = 60;
	while(i<=0){ 
		
		LCD_String("00:");
		if(i<10){
			LCD_Write('0');
			LCD_Write(i);
		}
		else{
			LCD_Write(i);
		}
		i--;
				Systick_Wait_ms(1000);
		  
		    LCD_Clear_Display();
			}
	
}
void Cooking(char choose ){
		if ( choose =='A'){
			LCD_String("popcorn");
		cook_Popcorn();	
		}
		if(choose =='B' ||choose =='C'){
			LCD_String("Beef weight?");
			LCD_Clear_Display();
			LCD_String("Chicken  weight?"); 
			char no_kiloes;
			do { 
				
				LCD_Clear_Display();
				LCD_String("please value between 1 and 9"); 
				LCD_Clear_Display();
			   no_kiloes =KeyScan();
			}while (no_kiloes<'1' && no_kiloes>'9');
			LCD_String("the entered value is"); 
			LCD_Clear_Display();
			LCD_Write(no_kiloes);
			Systick_Wait_ms(2000);
			LCD_Clear_Display();	
		}
			
	
	}

