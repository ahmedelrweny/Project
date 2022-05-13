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

char Int_to_char0(int x){   // to transfer the int num to char and get tens
	 int num1= x/10;          // to get tens 
	 int num2= x-(num1*10);    // to get ones
	 char required[2];          //define array of 2 chars
	   required[0] = num1 +0x30;   // transfer tens into char
	return required[0];          // return tens char
}
char Int_to_char1(int x){ // to transfer the int num to char and get ones
	 int num1= x/10;        // to get tens
	 int num2= x-(num1*10); // to get ones
	 char required[2];      //define array of 2 chars
	 required[1] = num2 +0x30;     // transfer ones into char
	return required[1];         // return ones char
}
	
void cook_Popcorn(){
	char time[]={'0','0',':','6','0'};  // to set time min
	    LCD_String("popcorn");  // show popcorn in lcd
			Systick_Wait_ms(1000);  // make a delay      
			Time_Display(time);     // to display time
}
void cook_Beef_or_Chicken(char choose){
	int min;
	int no_seconds;
	double Time;
	int no_kiloes ;
	if(choose =='B'){     // check if the choose is B
		LCD_String("Beef weight?");    // show Beef weight on lcd
		Systick_Wait_ms(1000);     // make delay 
	  LCD_Clear_Display();}      // to clear the lcd
	else if(choose =='C'){       // check if the choose is C
		LCD_String("Chicken  weight?");  // show Chicken weight on lcd
		Systick_Wait_ms(1000);     // make delay 
		LCD_Clear_Display();}      // to clear the lcd
l:  LCD_String("value 1 to 9");  // show value 1 to 9 on lcd
		Systick_Wait_ms(1000);     // make delay 
		LCD_Clear_Display();       // to clear the lcd 
		No_kiloes =KeyScan();      // take num of kiloes from the user
		if( No_kiloes<'1' || No_kiloes>'9'){   // check if the user enters a vaild num
			LCD_String("Err");  //show Err in lcd if the condition is true
			Systick_Wait_ms(2000);  // wait 2 seconds 
			LCD_Clear_Display(); // clear the lcd 
			goto l ;            //go to label l to enter a new value 
		}
		 LCD_String("value is ");   // show value is  in lcd
		 LCD_Write(No_kiloes);     // show num of kiloes in lcd
		 Systick_Wait_ms(2000);    // make delay 
		 LCD_Clear_Display();      // to clear lcd 
		if (choose =='B'){         //check if the choose is B
			no_kiloes=Char_to_int(No_kiloes);   // transfer the num of kiloes from char to int
			Time=0.5*no_kiloes;                 // cacl time
		}
		else if(choose == 'C'){         //check if the choose is C
			no_kiloes=Char_to_int(No_kiloes);   // transfer the num of kiloes from char to int
			Time=0.2*no_kiloes;             // cacl time
		}
	  	min= (int)Time;            // Get number of mins
		no_seconds= (Time-min) * 60;   // Get number of  seconds
		time[0]=Int_to_char0(min);     // Get tens of min
		time[1]=Int_to_char1(min);     // Get ones of min 
		time[2]=':';                   // Get : 
		time[3]=Int_to_char0(no_seconds);  // Get tens of seconds
		time[4]=Int_to_char1(no_seconds);   // Get ones of seconds
		Time_Display(time);                 // to display time
}
