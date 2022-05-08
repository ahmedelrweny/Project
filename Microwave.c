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


char No_kiloes;

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
	while(time[0]!=0x30 || time[1]!=0x30 || time[3]!=0x30 ||  time[4]!=0x30){ 
		LCD_Array(time);
		Systick_Wait_ms(1000);
		if(time[4]==0x30 && time[3]!=0x30){
			time[4]=0x39;
			time[3]--;
		}
		else if(time[4]!=0x30 && time[3]!=0x30 ) {
			time[4]--;
		}
		else if(time[4]==0x30 && time[3]==0x30 ){
			if(time[1]!=0x30){
			time[4]=0x39;
			time[3]=0x35;
			time[1]--;}
		else if(time[1]==0x30 && time[0]!=0x30){
			time[4]=0x39;
			time[3]=0x35;
				time[1]=0x39;
				time[0]--;}
		else if(time[1]==0x30 && time[0]==0x30){
				break;
			}
			}
		else if(time[4]!=0x30 && time[3]==0x30){
				time[4]--;
			}
			 LCD_Clear_Display();
		}
	}

void Cook_Time(){
 char time[]={'0','0',':','0','0'};
 char x;
 int i ;
 LCD_String("Time?");
 Systick_Wait_ms(1000);
 LCD_Clear_Display();
    for(i=4;i>0;i--){
			
				LCD_Clear_Display();
        x= KeyScan();
        time[0]=time[1];
        time[1]=time[3];
        time[3]=time[4];
        time[4]=x;
        if(i != 1){
					LCD_Array(time);
				}	
			  Systick_Wait_ms(500);
			
    }
	if((time[0]>'3')||(time[0]=='3' && time[1]!='0')||(((time[1]<'1')&& time[0]=='0' )|| time[3]>='6' )){
		LCD_String("Invalid value");
    Systick_Wait_ms(2000);
	  LCD_Clear_Display();
		Cook_Time();
	}
	Time_Display(time);
	
	
}

int Char_to_int(char x){
	int number = x-0x30;
	return number;
}

char Int_to_char0(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	   required[0] = num1 +0x30;
	 required[1] = num2 +0x30;
	
	return required[0];
}

char Int_to_char1(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	 required[1] = num2 +0x30;
	
	return required[1];
}
	
void cook_Popcorn(){
	char time[]={'0','0',':','6','0'};  // to set time min
	    LCD_String("popcorn");  // show popcorn in lcd
			Systick_Wait_ms(1000);  // make a delay
			LCD_Clear_Display();    // to clear the display	      
			Time_Display(time);     // to display time
}
 
void cook_Beef_or_Chicken(char choose){
	int min;
	int no_seconds;
	double time;
	char time_array[5]={'\0'};
	int no_kiloes ;
	if(choose =='B'){
		LCD_String("Beef weight?");    
		Systick_Wait_ms(1000);
	  LCD_Clear_Display();}
	else if(choose =='C'){
		LCD_String("Chicken  weight?"); 
		Systick_Wait_ms(1000);
		LCD_Clear_Display();}
l:  LCD_String("value 1 to 9"); 
		Systick_Wait_ms(1000);
		LCD_Clear_Display();
		No_kiloes =KeyScan();
		if( No_kiloes<'1' || No_kiloes>'9'){ 
			LCD_String("Err");
			Systick_Wait_ms(2000);
			LCD_Clear_Display();
			goto l ;}
		  LCD_String("value is"); 
		  LCD_Write(No_kiloes);
		  Systick_Wait_ms(2000);
		  LCD_Clear_Display();
			if (choose =='B'){
				no_kiloes=Char_to_int(No_kiloes);
			time=0.5*no_kiloes;}
			else if(choose == 'C'){
				no_kiloes=Char_to_int(No_kiloes);
				time=0.2*no_kiloes;
	}
			min= (int)time;
	no_seconds= (time-min)*60;
	time_array[0]=Int_to_char0(min);
	time_array[1]=Int_to_char1(min);
	time_array[2]=':';
  time_array[3]=Int_to_char0(no_seconds);
	time_array[4]=Int_to_char1(no_seconds);
	Time_Display(time_array);
}


unsigned int CurrentTime;

void start(unsigned int timer){
    NVIC_ST_RELOAD_R = timer;
    NVIC_ST_CTRL_R |= 0x05;
}
void pause(void){
    CurrentTime = NVIC_ST_CURRENT_R;
    NVIC_ST_CTRL_R &= ~(0x05);
    //Show Time
}
void resume(void){
    NVIC_ST_RELOAD_R = CurrentTime;
    NVIC_ST_CTRL_R |= 0x05;
}
void reset(void){
    NVIC_ST_CURRENT_R = 0x0;
    NVIC_ST_CTRL_R &= ~(0x05);
}
