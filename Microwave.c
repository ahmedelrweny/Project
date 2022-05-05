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

void cook_Beef_or_Chicken(char No_kiloes , char choose){
	int min;
	int no_seconds;
	double time;
	char time_array[10]={'\0'};
	int no_kiloes =Char_to_int(No_kiloes);
	if (choose =='B'){
	  time=0.5*No_kiloes;}
	if(choose == 'C'){
		time=0.2*No_kiloes;
	}
	 min= (int)time;
	 no_seconds= (time-min)*60;
	time_array[0]=Int_to_char(min)[0];
	time_array[1]=Int_to_char(min)[1];
  time_array[2]=Int_to_char(no_seconds)[0];
	time_array[3]=Int_to_char(no_seconds)[1];
	
}

void Cooking(char choose ){
	  char no_kiloes;
		if ( choose =='A'){
			LCD_String("popcorn");
		cook_Popcorn();	
		}
		if(choose =='B' ||choose =='C'){
			LCD_String("Beef weight?");
			Systick_Wait_ms(1000);
			LCD_Clear_Display();
			LCD_String("Chicken  weight?"); 
	l:	LCD_Clear_Display();
			LCD_String("please value between 1 and 9"); 
			LCD_Clear_Display();
		  no_kiloes =KeyScan();
			if( no_kiloes<'1' || no_kiloes>'9'){ 
			LCD_String("Err");
			Systick_Wait_ms(2000);
			goto l ;}
		  LCD_String("the entered value is"); 
		  LCD_Write(no_kiloes);
		  Systick_Wait_ms(2000);
		  LCD_Clear_Display();
		  cook_Beef_or_Chicken(no_kiloes,choose);
		}
			
	
	}

