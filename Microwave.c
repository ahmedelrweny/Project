#include "Extern.h"
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
#include <stdbool.h>  



char time[]={'0','0',':','0','0','\0'};

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

void pause(void){
	LCD_Clear_Display();
	LCD_Show(time);
	START =0;
	SW1_Press_Counts=1;
	//LCD_Clear_Display();
	//LCD_Show(time);

	while(1)
		{
			WhiteOn();
			Systick_Wait_ms(500);
			LED_Clear();
			Systick_Wait_ms(500);
			if((RESET == 1 || START ==1) && (!DOOR_OPEN))
			{	
				break;
			}
		}
	PAUSE =0;
}

void reset(void){
	time[0] = '0';
	time[1] = '0';
	time[3] = '0';
	time[4] = '0';
	LED_Clear();
	RESET=0;

}


bool Check_Invalid(void){
		
	if(	time[0]>'3' )
		{
			 return true;
		}
	if(	time[0]=='3' && ( time[1]!='0' || time[3] !='0' || time[4] !='0') 	)
		{
			 return true;
		}
	if(	time[3]>'5'	 )
		{
			 return true;
		}
	if(time[0]=='0' &&  time[1] =='0' && (time[3] !='0' || time[4] !='0'))
		{
			 return true;		
		}
	else
		{
			 return false;
		}
}

void End_Operation(){
	int i;
	LCD_Clear_Display();
	LCD_Show("End");
	z=0;
	START=0;
	PAUSE=0;
	RESET=0;
	for(i=0; i<3; i++){
			beep();
			WhiteOn();
			Systick_Wait_ms(500);
			LED_Clear();
			stop_Beep();
			Systick_Wait_ms(500);
			
		}		
	LCD_Clear_Display();
}

void Time_Display(char time[]){
	LCD_Clear_Display();
	while(time[0]!='0' || time[1]!='0' || time[3]!='0' ||  time[4]!='0') 	
		{ 
			WhiteOn();
			LCD_Clear_Display();
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
			if(PAUSE == 1){	
				pause();
			}
			if(RESET == 1){	
				reset();
				break;
			}
		}
	End_Operation();
}

void start(void){
	RESET=0;
	PAUSE =0;
	Time_Display(time);
}


void Cook_Time(void){
	char x;
	int i ;
	bool invalid= false;
	z=1;
	time[4]='0';
	time[3]='0';
	time[1]='0';
	time[0]='0';
	LCD_Show("Cooking Time?");
	Systick_Wait_ms(1000);
  for(i=4;i>0;i--)
	{	
		
    x= KeyScan();
		if(START)
		{
			break;
		}
		if(SW1_Press_Counts )
		{
			LCD_Clear_Display();
			SW1_Press_Counts = 0;
			reset();
			Cook_Time();
		}
		
		LCD_Clear_Display();
		if( x<'0' ||  x>'9' )
		{
			invalid= true;
			break;
		}
			
    time[0]=time[1];
    time[1]=time[3];
    time[3]=time[4];
    time[4]=x;
		LCD_Show(time);
		Systick_Wait_ms(500);
			
  }
	if(Check_Invalid() || invalid	)
	{
		LCD_Clear_Display();
		LCD_Show("Invalid value");
		Systick_Wait_ms(2000);
		LCD_Clear_Display(); 
		START=0;
		Cook_Time();
	}
}

int Char_to_int(char x){
	int number = x-'0';
	return number;
}

char IntToChar_Tens(int x){
	int Tens= x/10;
	char required;
	required = Tens +'0';
	return required;
}

char IntToChar_Units(int x){
	int Tens= x/10;
	int Units= x-(Tens*10);
	char required;
	required = Units +'0';
	return required;
}
	
void cook_Popcorn(void){
	time[3]='6';  // to set time minutes
	LCD_Show("Popcorn");  // show popcorn in lcd
	Systick_Wait_ms(1000);  // make a delay 
	LCD_Clear_Display();
	LCD_Show(time);
}
 
void cook_Beef_or_Chicken(char choice){
	int minutes;
	int seconds;
	double TimeInMinutes_d;
	char No_kiloes;
	int no_kiloes ;
	
	if(choice =='B')
		{
			LCD_Show("Beef weight?");    
			Systick_Wait_ms(1000);
			LCD_Clear_Display();
		}
	else if(choice =='C')
		{
			LCD_Show("Chicken weight?"); 
			Systick_Wait_ms(1000);
			LCD_Clear_Display();
		}
	do
	{
		LCD_Show("Kiloes? 1 to 9"); 
		Systick_Wait_ms(1000);
		No_kiloes =KeyScan();
		LCD_Clear_Display();
		
		if(No_kiloes<'1' || No_kiloes>'9' )
		{ 
			LCD_Show("Err");
			Systick_Wait_ms(2000);
			LCD_Clear_Display();
		}
	}
	while(No_kiloes<'1' || No_kiloes>'9');

	LCD_Show("Weight is "); 
	LCD_Write(No_kiloes);
	Systick_Wait_ms(2000);
		
	if (choice =='B')
	{
		no_kiloes=Char_to_int(No_kiloes);
		TimeInMinutes_d=0.5*no_kiloes;
	}
	else if(choice == 'C')
	{
		no_kiloes=Char_to_int(No_kiloes);
		TimeInMinutes_d=0.2*no_kiloes;
	}
	minutes= (int)TimeInMinutes_d;
	seconds= (TimeInMinutes_d-minutes) * 60;
	time[0]=IntToChar_Tens(minutes);
	time[1]=IntToChar_Units(minutes);
	time[3]=IntToChar_Tens(seconds);
	time[4]=IntToChar_Units(seconds);
	LCD_Clear_Display();
	LCD_Show(time);
}



