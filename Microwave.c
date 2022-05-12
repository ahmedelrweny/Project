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
char time[]={'0','0',':','0','0'};

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

void Cook_Time(void){
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
	
void cook_Popcorn(void){
	    time[3]='6';  // to set time min
	    LCD_String("popcorn");  // show popcorn in lcd
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
			goto l ;
		}
		 LCD_String("value is "); 
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
		time[2]=':';
		time[3]=Int_to_char0(no_seconds);
		time[4]=Int_to_char1(no_seconds);
		Time_Display(time);
}
void TimetoInteger(){
	int min0 = Char_to_int(time[0]);
	int min1 = Char_to_int(time[1]);
	int sec0 = Char_to_int(time[3]);
	int sec1 = Char_to_int(time[4]);
	int time = (min0 * 10 + min1) * 60 + (sec0 * 10 + sec1); // time in seconds

}


void start(void){

	

}

