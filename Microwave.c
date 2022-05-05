#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#include "LCD.h"
#include <string.h>
#include "Keypad.h"


void microwave_Init(void){
	 
}
int Char_to_int(char x){
	int number = x-0x30;
	return number;
}
char* Int_to_char(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	   required[0] = num1 +0x30;
	 required[1] = num2 +0x30;
	
	return required;}

void cook_Popcorn(){
	int i=60;
	char no[] = {'6','0'};

	while(i>=0){ 
		
		LCD_String("00:");
			LCD_Write(no[0]);
			LCD_Write(no[1]);
		i--;
				Systick_Wait_ms(1000);
		if(no[1]==0x30){
			no[1]=0x39;
			no[0]--;
		}
		else {
			no[1]--;
		}
		  
		    LCD_Clear_Display();
			}
	
}
