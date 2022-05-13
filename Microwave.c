#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#include "LCD.h"
#include <string.h>
#include "Keypad.h"
#include "Switch.h"
 char No_kiloes;
 char time[]={'0','0',':','0','0'};
 typedef enum {false,true} bool_enum;
void microwave_Init(void){
	 
}


void Time_Display(char time[]){
	LCD_Clear_Display();//clear LCD
	while(time[0]!=0x30 || time[1]!=0x30 || time[3]!=0x30 ||  time[4]!=0x30){ // loop untill 00:00
		LCD_Array(time); // display time on LCD
		Systick_Wait_ms(1000); //delay 1 seconds
		if(time[4]!=0x30 && time[3]==0x30){//handle the case of tens of seconds equal zero and ones of seconds not equal zero 
				time[4]--;
			}
		else if(time[4]==0x30 && time[3]!=0x30){ //handle the case of tens of seconds not equal zero and ones of seconds equal zero 
			time[4]=0x39;
			time[3]--;
		}
		else if(time[4]!=0x30 && time[3]!=0x30 ) {//handle the case of both tens and ones of seconds not equal zero 
			time[4]--;
		}
		else if(time[4]==0x30 && time[3]==0x30 ){//handle the case of seconds equal zero and mins not equal zero 
			if(time[1]!=0x30){ //handle the case of ones of mins not equal zero
			time[4]=0x39;
			time[3]=0x35;
			time[1]--;}
		else if(time[1]==0x30 && time[0]!=0x30){//handle the case of ones of mins equal zero and tens of mins not equal zero 
			time[4]=0x39;
			time[3]=0x35;
				time[1]=0x39;
				time[0]--;}
		else if(time[1]==0x30 && time[0]==0x30){ //handle the case of mins and seconds equal zero
				break;
			}
			}
			 LCD_Clear_Display();
		}
	}
int  Check_Invaild(char time[]){
	if (time[1]>'9'||time[3]>='6'||time[4]>'9'){ // get the value of seconds between 0 to 59 only 
		                                            //get the value of ones of mins between 0 to 9 only 
	return true;
	}
	else if(time[0]>'3'){ // to prevent tens of min to be more than  3 
		return true;
	}
	else if (time[0]=='3' && (time[1]!='0'||time[3]!='0'||time[4]!='0')){  //to prevent mins to be more than 30 min 
		return true;
	}
	else if (time[0]=='0' && time[1]=='0') { //to prevent mins to be less than 1 min 
		return true;
	}
		return false;
	
}
void Cook_Time(){
 char x;
 int i ;
    for(i=4;i>0;i--){
			
			 LCD_Clear_Display(); // clear to write the value of time 
         x= KeyScan();
        time[0]=time[1];// tens of mins equal ones of mins
        time[1]=time[3]; // ones of mins equal tens of seconds
        time[3]=time[4];// tens of seconds equal ones of seconds
        time[4]=x;// ones of seconds equal the user input
        LCD_Array(time);
			  Systick_Wait_ms(500);
	if((Check_Invaild)){
		LCD_String("Invalid value");// check value of time 
    Systick_Wait_ms(2000);//disply "Invalid value" on LCD
	  LCD_Clear_Display();// clear LCD
		Cook_Time(); //call the function to get new value
	}
	Time_Display(time); //to countdown time on LCD
	
	
}
}
int Char_to_int(char x){  // to transfer the char to int
	int number = x-0x30;    // as '0'= 0x30 and '9'=0x39
	return number;          // to return the int number
}

char Int_to_char0(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	   required[0] = num1 +0x30;
	 required[1] = num2 +0x30;
	
	return required[0];}
char Int_to_char1(int x){
	 int num1= x/10;
	 int num2= x-(num1*10);
	 char required[2];
	 required[1] = num2 +0x30;
	
	return required[1];}
	
void cook_Popcorn(){
	char time[]={'0','0',':','6','0'};  // to set time min
	    LCD_String("popcorn");  // show popcorn in lcd
			Systick_Wait_ms(1000);  // make a delay      
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

