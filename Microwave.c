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
			 return false;
}

void End_Operation(){
	int i;
	LCD_Show("End");
	
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
	LCD_Clear_Display();//clear LCD
	while(time[0]!='0' || time[1]!='0' || time[3]!='0' ||  time[4]!='0') // loop untill 00:00
		{
		LCD_Show(time); 																									// display time on LCD
		Systick_Wait_ms(1000); 																						//delay 1 seconds
		
			if(time[4]!='0' ) 			//Units of seconds != 0 so decrement by 1
			{
				time[4]--;	
			}
			else if(time[4]=='0' && time[3]!='0')			//Units of seconds = 0 && Tens of second !=0 (00:50)
			{
				time[4]='9';														//write 9 in units ==> ex:( 00:59	)	
				time[3]--;															//decrease tens by 1 ==> ex:( 00:49	)	
			}

			else if(time[4]=='0' && time[3]=='0' && time[1]!='0') //Units of seconds = 0 && Tens of second =0 && units in minute !=0 (01:00)
			{
				time[4]='9';														//write 9 in units ==> ex:( 01:09	)	
				time[3]='5';														//write 5 in tens ==> ex:( 01:59	)
				time[1]--;															//decrease unit of minutes by 1 ==> ex:( 00:59	)	
			}
			else if(time[4]=='0' && time[3]=='0' && time[1]=='0' && time[0]!='0') //Units of seconds = 0 && Tens of second =0 && units in minute =0 &&Tens of minutes !=0 (10:00)
			{
				time[4]='9';														//write 9 in units ==> ex:( 10:09	)
				time[3]='5';														//write 5 in tens ==> ex:( 10:59	)
				time[1]='9';														//write 9 in units ==> ex:( 19:59	)
				time[0]--;															//decrease tens of minutes by 1 ==> ex:( 09:59	)	
			}
		LCD_Clear_Display();
		}
		End_Operation();	
	}

/*	
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
	
}*/
void Cook_Time(){
	char x;
	int i;
	bool invalid= false;
	time[0]='0'; 												//Make function to reset array to zero
	time[1]='0';
	time[3]='0';
	time[4]='0';
	LCD_Show("Cooking Time?");
	Systick_Wait_ms(1000);
  for(i=4;i>0;i--)
	{
    x= KeyScan();
		LCD_Clear_Display(); 							// clear to write the value of time 
		
		if( x>'9')
		{
			invalid= true;
			break;
		}
		
        time[0]=time[1];							// tens of mins equal ones of mins
        time[1]=time[3]; 							// ones of mins equal tens of seconds
        time[3]=time[4];							// tens of seconds equal ones of seconds
        time[4]=x;										// ones of seconds equal the user input
        LCD_Show(time);
			  Systick_Wait_ms(500);
	}
		
	if(Check_Invalid() || invalid	)
	{
		LCD_Show("Invalid value");				// check value of time 
    Systick_Wait_ms(2000);						//disply "Invalid value" on LCD
	  LCD_Clear_Display();							// clear LCD
		Cook_Time(); 											//call the function to get new value
	}
}

int Char_to_int(char x){  // to transfer the char to int
	int number = x-'0';    	//subtracting '0' changed char to int
	return number;          // to return the int number
}

char IntToChar_Tens(int x){  	 // to transfer the int num to char and get tens
	 int Tens= x/10;          	 // to get tens 
	 char required;          		 //define array of 2 chars
	 required = Tens +'0';   		 // transfer tens into char
	 return required;          	 // return tens char
}

char IntToChar_Units(int x){ // to transfer the int num to char and get ones
	 int Tens= x/10;        // to get tens
	 int Units= x-(Tens*10); // to get ones
	 char required;      				//define array of 2 chars
	 required = Units +'0';     // transfer ones into char
	return required;         // return ones char
}
	
void cook_Popcorn(){
	time[3]='6';  																					// to set time minute
	LCD_Show("Popcorn");  																	// show popcorn in lcd
	Systick_Wait_ms(1000);  																// make a delay      
}
void cook_Beef_or_Chicken(char choice){
	int minutes;
	int seconds;
	double TimeInMinutes_d;
	int no_kiloes ;
	
	if(choice =='B')    																	 // check if the choice is B
	{
		LCD_Show("Beef weight?");    												// show Beef weight on lcd
		Systick_Wait_ms(1000);     														// make delay 
	  LCD_Clear_Display();																	// to clear the lcd
	}      
	else if(choice =='C')      													  // check if the choice is C
	{	
		LCD_Show("Chicken  weight?");  											// show Chicken weight on lcd
		Systick_Wait_ms(1000);    														// make delay 
		LCD_Clear_Display();																	// to clear the lcd
	}      														
	do
	{ 
		LCD_Show("Kiloes? 1 to 9");  													// show value 1 to 9 on lcd
		Systick_Wait_ms(1000);     													  // make delay 
		No_kiloes =KeyScan();      														// take num of kiloes from the user
		LCD_Clear_Display();       														// to clear the lcd 
		
		if( No_kiloes<'1' || No_kiloes>'9')   								// check if the user enters a vaild num
		{	
			LCD_Show("Err");  																//show Err in lcd if the condition is true
			Systick_Wait_ms(2000);  														// wait 2 seconds 
			LCD_Clear_Display(); 																// clear the lcd 																					 
		}
	}
	while(No_kiloes<'1' || No_kiloes>'9');
	
	  LCD_Show("Weight is "); 		  												// show value is  in lcd
		LCD_Write(No_kiloes);    													  	// show num of kiloes in lcd
		Systick_Wait_ms(2000);    														// make delay 
																		 
		if (choice =='B')        															//check if the choice is B
		{	
			no_kiloes=Char_to_int(No_kiloes);   								// transfer the num of kiloes from char to int
			TimeInMinutes_d=0.5*no_kiloes;                 			// cacl time
		}
		else if(choice == 'C')        												//check if the choice is C
		{	
			no_kiloes=Char_to_int(No_kiloes);   								// transfer the num of kiloes from char to int
			TimeInMinutes_d=0.2*no_kiloes;            				  // cacl time
		}
	  minutes= (int)TimeInMinutes_d;            						// Get number of minutess
		seconds= (TimeInMinutes_d-minutes) * 60;   						// Get number of  seconds
		time[0]=IntToChar_Tens(minutes);     									// Get tens of minutes
		time[1]=IntToChar_Units(minutes);     								// Get ones of minutes 
		time[2]=':';                   												// Get : 
		time[3]=IntToChar_Tens(seconds);  										// Get tens of seconds
		time[4]=IntToChar_Units(seconds);   									// Get ones of seconds
		LCD_Clear_Display();
		LCD_Show(time);                 											// to display time
}

/*int TimetoInteger(void){
	int min0 = Char_to_int(time[0]);
	int min1 = Char_to_int(time[1]);
	int sec0 = Char_to_int(time[3]);
	int sec1 = Char_to_int(time[4]);
	int mins = (min0 * 10 + min1);
	int secs = (sec0 * 10 + sec1);
	int time__;
	return time__ = mins * 60 + secs; // time in seconds

}*/

void start(void){
	Time_Display(time);
	RedOn();
	BlueOn();
	GreenOn();
}

void pause(void){// used to pause when user want to reset/pause
	LCD_Show(time);
	while((SW2_Input()==0x01) ||(SW1_Input()==0x010))
		{
			RedOn();
			BlueOn();
			GreenOn();
			Systick_Wait_ms(500);
			LED_Clear();
			Systick_Wait_ms(500);
		}
}

void reset(void){ // used to reset timer to 0
	time[0] = '0';
	time[1] = '0';
	time[3] = '0';
	time[4] = '0';
	LED_Clear();
}

void resume(void){ //resume after pause when resume/start switch is pressed
	Time_Display(time);
	RedOn();
	BlueOn();
	GreenOn();
}
