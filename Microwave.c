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
#include<stdbool.h>  


char No_kiloes;
char time[]={'0','0',':','0','0'};
char invalid= 0;

void microwave_Init(void){
	System_Init();
	buzzer_Init();
	keypad_Init();
	LCD_Init();
	LED_Init();
	SW1_Init();
	SW2_Init();
	SW3_Init();
	interrupt_Init();
}

void Time_Display(char time[]){
	LCD_Clear_Display();
	while(time[0]!='0' || time[1]!='0' || time[3]!='0' ||  time[4]!='0') 	// Ascii of 0x30 is 0
		{ 
			LCD_Show(time);
			Systick_Wait_ms(1000);
		
			if(time[4]!='0' ) 
			{
				time[4]--;	
			}
			else if(time[4]=='0' && time[3]!='0')
			{
				time[4]='9';
				time[3]--;
			}

			else if(time[4]=='0' && time[3]=='0' && time[1]!='0')
			{
				time[4]='9';
				time[3]='5';
				time[1]--;
			}
			else if(time[4]=='0' && time[3]=='0' && time[1]=='0' && time[0]!='0')
			{
				time[4]='9';
				time[3]='5';
				time[1]='9';
				time[0]--;
			}

			LCD_Clear_Display();
		}
		LCD_Show("End");
	}

void Cook_Time(void)
{
	char x;
	int i ;
	LCD_Show("Cooking Time?");
	Systick_Wait_ms(1000);
	LCD_Clear_Display();
  for(i=4;i>0;i--)
	{	
		LCD_Clear_Display();
    x= KeyScan();
		if(x=='A' || x=='B' || x=='C' || x=='D' || x=='#' || x=='*' )
		{
			invalid = 1;
			break;
		}
			
    time[0]=time[1];
    time[1]=time[3];
    time[3]=time[4];
    time[4]=x;
		LCD_Show(time);
		Systick_Wait_ms(500);
			
  }
	if(	(time[0]>'3')		||		(time[0]=='3' && ( time[1]!='0' || time[3] !='0' || time[4] !='0')) || invalid == 1	)
	{
		invalid = 0;
		
		LCD_Show("Invalid value");
		Systick_Wait_ms(2000);
		LCD_Clear_Display(); 
		Cook_Time();
		Time_Display(time);
	}
}

int Char_to_int(char x){
	int number = x-'0';
	return number;
}

char Int_to_char0(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	 required[0] = num1 +'0';
	 required[1] = num2 +'0';
	 return required[0];
}

char Int_to_char1(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	 required[1] = num2 +'0';
	 return required[1];
}
	
void cook_Popcorn(void){
	    time[3]='6';  // to set time min
	    LCD_Show("popcorn");  // show popcorn in lcd
			Systick_Wait_ms(1000);  // make a delay
			LCD_Clear_Display();    // to clear the display	      
			Time_Display(time);     // to display time
}
 
void cook_Beef_or_Chicken(char choose){
	int min;
	int no_seconds;
	double Time;
	int no_kiloes ;
	if(choose =='B'){
		LCD_Show("Beef weight?");    
		Systick_Wait_ms(1000);
	  LCD_Clear_Display();}
	else if(choose =='C'){
		LCD_Show("Chicken  weight?"); 
		Systick_Wait_ms(1000);
		LCD_Clear_Display();}
l:  LCD_Show("value 1 to 9"); 
		Systick_Wait_ms(1000);
		LCD_Clear_Display();
		No_kiloes =KeyScan();
		if( No_kiloes<'1' || No_kiloes>'9'){ 
			LCD_Show("Err");
			Systick_Wait_ms(2000);
			LCD_Clear_Display();
			goto l ;
		}
		 LCD_Show("value is "); 
		 LCD_Write(No_kiloes);
		 Systick_Wait_ms(2000);
		 LCD_Clear_Display();
		if (choose =='B'){
			no_kiloes=Char_to_int(No_kiloes);
			Time=0.5*no_kiloes;
		}
		else if(choose == 'C'){
			no_kiloes=Char_to_int(No_kiloes);
			Time=0.2*no_kiloes;
		}
	  min= (int)Time;
		no_seconds= (Time-min) * 60;
		time[0]=Int_to_char0(min);
		time[1]=Int_to_char1(min);
		time[3]=Int_to_char0(no_seconds);
		time[4]=Int_to_char1(no_seconds);
		Time_Display(time);
}



void start(void){
    //Again please
}
void pause(void){
    //Again please
}
void reset(void){
    //Again please
}
