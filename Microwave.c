#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#include "LCD.h"
#include <string.h>
#include "Keypad.h"
#include <stdio.h>
#include "Switch.h"

void microwave_Init(void){
	 
}
//LCD_Array function to write the whole array of chars on LCD
void LCD_Array(char arr[]){   // write a array of chars on LCD
  int l=sizeof(arr)/sizeof(arr[0]);        // l = array length
  int i=0;                    //itterator
  while(i<l){
		LCD_Write(arr[i]);        // call the function LCD_Write 
		i++;
    }
}
void Time_Display(char time[]){
	int i,j;
	while (1){
	while(1){ 
		LCD_Array(time);
		Systick_Wait_ms(1000);
		if(time[4]==0x30){
			time[4]=0x39;
			time[3]--;
		}
		else {
			time[4]--;
		}
		  LCD_Clear_Display();
		  if (time[3]==0x30){break;}
			}
	if(time[0]==0x30&&time[1]==0x30){break;}
	if(time[1]==0x30){
			time[1]=0x39;
			time[2]--;
		}
		else {
			time[1]--;
		}
			
		
}}

void Cook_Time(){
	char time[]={'0','0',':','0','0'};
	int i ,j ;
	LCD_Clear_Display();
	for (i=4;i>=0;i++){
	if (i==2){
		continue ;
	}
	time[4]=KeyScan();
	LCD_Array(time);
	for(j=4-i;j>=0;j--){
		if (j==2){
		time[0]=time[1];}
		if (j==1){
			time[1]=time[3];
		}
		time[3-j]=time[4-j];
	}
	while(SW2_Input()==1);
	if((time[0]>3)||(time[1]==0)||(time[0]==3&&time[1]>0)){
		LCD_String("Invalid value, please enter a value between (1 to 30)min");
		Cook_Time();
	}
	Time_Display(time);
	
}


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
	
			char time[]={'0','0',':','6','0'};
			LCD_Array (time);
}
void cook_Beef_or_Chicken(char No_kiloes , char choose){
	int min;
	int no_seconds;
	double time;
	char time_array[5]={'\0'};
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
	time_array[2]=':';
  time_array[3]=Int_to_char(no_seconds)[0];
	time_array[4]=Int_to_char(no_seconds)[1];
	LCD_Array (time_array);
	
}

void Cooking(char choose ){
	  char no_kiloes;
		if ( choose =='A'){       // A for popcorn
			LCD_String("popcorn");  // show popcorn in lcd
			Systick_Wait_ms(1000);  // make a delay
			LCD_Clear_Display();    // to clear the display
		  cook_Popcorn();	        // to call the function cook_popcorn
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
