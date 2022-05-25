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

void pause(void){ /*pause time on LCD*/
	START =0; // reset start flag
	SW1_Press_Counts = 1;
	LCD_Clear_Display();//clear LCD 
	LCD_Show(time); //display on LCD 
	
	while(1)
		{
			WhiteOn(); // turns leds on 
			Systick_Wait_ms(500); // wait 0.5 second
			LED_Clear(); // clear LCD 
			Systick_Wait_ms(500);// wait 0.5 second
			if((SW3_Input() != 0x04) && (START ==1) )//check if sw2 and sw3 pressed together
			{
				LCD_Clear_Display(); //clear LCD
				LCD_Show("Close The Door");//display on LCD 
				START =0; // reset start flag
			}
			
			if(((SW3_Input() == 0x04) && START ==1) || (RESET == 1 ))//check if sw2 pressed and sw3 not pressed or reset flag is set
			{	
				SW1_Press_Counts = 0;// reset count flag
				LCD_Clear_Display();// clear LCD
				break;
			}
		}
	PAUSE =0;// reset pause flag
}

void reset(void){/*reset timer array */
	time[0] = '0';
	time[1] = '0';
	time[3] = '0';
	time[4] = '0';
	LED_Clear();// clear LCD
	RESET=0; // Reset the flag
}


bool Check_Invalid(void){ /*check if the input is vaild or not */
	if(	time[0]>'3' ) //  check if tens of mins is more than 3 
		{
			 return true;
		}
	if(	time[0]=='3' && ( time[1]!='0' || time[3] !='0' || time[4] !='0') 	)// check if time is more than 30 min
		{
			 return true;
		}
	if(	time[3]>'5'	 )// check if tens of seconds is more than five
		{
			 return true;
		}
	if(time[0]=='0' &&  time[1] =='0')//check if time is less than 1 min 
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
	START=0; // reset the value of flags 
	Start_Cook_Time = 0;
	SW1_Press_Counts=0;
	LCD_Clear_Display(); // clear LCD 
	LCD_Show("End");    // display end on LCD 
	
	for(i=0; i<3; i++){ 
			beep(); // turn buzzer on 
			WhiteOn(); // turn leds on 
			Systick_Wait_ms(500); // wait 0.5 second 
			LED_Clear(); // clear LCD 
			stop_Beep(); //turn buzzer off
			Systick_Wait_ms(500);//wait 0.5 second 
			
		}		
	LCD_Clear_Display();//clear LCD
}

void Time_Display(char time[]){ /* disply the countdown timer on LCD*/
	
	LCD_Clear_Display(); 
	while(time[0]!='0' || time[1]!='0' || time[3]!='0' ||  time[4]!='0') 	//check the timer is not equal zero
		{ 
			WhiteOn();  // turn leds on
			LCD_Clear_Display();  //clear LCD
			LCD_Show(time);  //  display time on LCD
			
			if((PAUSE == 1) || (SW3_Input() !=0x04)){	//check if SW1 pressed or the door opened  
				pause(); // pause time on LCD
			}
			if(RESET == 1){	 // check if sw1 pressed twice
				reset();  // reset the timer array 
				break;
			}
			
			Systick_Wait_ms(1000); //wait 1 second 
		
			if(time[4]!='0' ) // check if units of seconds not equal zero
			{
				time[4]--;	//decrease the units of seconds
			}
			else if(time[4]=='0' && time[3]!='0')//check if tens of seconds not equal zero and units of seconds equal zero
			{
				time[4]='9'; //units of seconds equal nine
				time[3]--; //decrease the tens of seconds
			}

			else if(time[4]=='0' && time[3]=='0' && time[1]!='0')//check if seconds equal zero and units of mins not equal zero 
			{
				time[4]='9';//units of seconds equal nine
				time[3]='5';//tens of seconds equal five
				time[1]--;//decrease the units of mins
			}
			else if(time[4]=='0' && time[3]=='0' && time[1]=='0' && time[0]!='0')//check if seconds equal zero and tens of mins not equal zero 
			{
				time[4]='9';//units of seconds equal nine
				time[3]='5';//tens of seconds equal five
				time[1]='9';//units of mins equal nine
				time[0]--;//decrease the tens of mins
			}

			LCD_Clear_Display(); //clear LCD 
		}
	End_Operation();
}

void start(void){ /*start countdown of timer*/
	RESET=0; 
	PAUSE =0;
	Time_Display(time);
}


void Cook_Time(void){ /* take time from user*/
	char x; 
	int i ;
	bool invalid= false; 
	Cook_Time_f = 1; // set flag (get in function cook time) 
	time[4]='0'; // reset the time array
	time[3]='0'; 
	time[1]='0';
	time[0]='0';
	LCD_Show("Cooking Time?");
	Systick_Wait_ms(1000); //wait 1 second 
  for(i=4;i>0;i--) 
	{	
    x= KeyScan(); // take input from user 
		LCD_Clear_Display();
		if(Cook_Time_Again || Start_Cook_Time){ // check if SW2 or SW1 pressed
			LCD_Clear_Display(); //clear LCD
			break; 
		}
		if( x<'0' ||  x>'9' )//check if the input is among 0 to 9 
		{
			invalid= true; // set the  invaild flag 
			break;
		}
			
    time[0]=time[1]; // make shift left to timer array 
    time[1]=time[3];
    time[3]=time[4];
    time[4]=x;
		LCD_Show(time); // display time on LCD
		Systick_Wait_ms(500);//wait 0.5 seconds
			
  }
	
	while(1)
	{
		if(Cook_Time_Again == 1 || Start_Cook_Time == 1){//check if SW2 or SW1 pressed
			LCD_Clear_Display();//clear LCD
			break;
		}
	}
	
	Cook_Time_f = 0; // reset flag (get out from function cook time) 
	
	if((Check_Invalid() || invalid	)&& (!Cook_Time_Again))// check if input is not valid or time is reset
	{
		LCD_Clear_Display(); // clear LCD 
		LCD_Show("Invalid value");//display on LCD
		Systick_Wait_ms(2000);//wait 2 seconds 
		LCD_Clear_Display(); //clear LCD
		Start_Cook_Time = 0;//reset the flag
		Cook_Time(); //back again to function until input is valid 
	}

}

int Char_to_int(char x){/* to convert char to integer */
	int number = x-'0'; //to get the number that is between 0 and 9 
	return number;
}

char IntToChar_Tens(int x){/* to convert integer to char and get tens*/
	int Tens= x/10;  // to get tens
	char required;  
	required = Tens +'0'; //convert to char
	return required;
}

char IntToChar_Units(int x){/* to convert integer to char and get units*/
	int Units= x%10; //to get ones 
	char required;
	required = Units +'0';//convert to char
	return required;
}
	
void cook_Popcorn(void){
	time[1]='1';  // to make time equal 1 min
	LCD_Show("Popcorn");  // show popcorn in lcd
	Systick_Wait_ms(1000);  // wait 1 second
	LCD_Clear_Display(); // clear display 
	LCD_Show(time); // show time on LCD 
}
 
void cook_Beef_or_Chicken(char choice){/*take num of kilos and count time to display*/
	int minutes;
	int seconds;
	double TimeInMinutes_d;
	char No_kilos;
	int no_kilos ;
	
	if(choice ==beef)// check if the choose is B  
		{
			LCD_Show("Beef weight?"); // display on LCD
			Systick_Wait_ms(500); //wait 0.5 second 
			LCD_Clear_Display();// clear LCD
		}
	else if(choice ==chicken) // check if the choose is C
		{
			LCD_Show("Chicken weight?"); // display on LCD
			Systick_Wait_ms(500);//wait 0.5 second 
			LCD_Clear_Display();// clear LCD
		}
	do
	{
		LCD_Show("Kilos? 1 to 9"); // display on LCD
		Systick_Wait_ms(300);// wait 0.3 second
		No_kilos =KeyScan(); // take input from kaypad 
		LCD_Clear_Display(); // clear LCD
		
		if(No_kilos<'1' || No_kilos>'9' ) //check if num of kilos not is between 1 and 9
		{ 
			LCD_Show("Err");// display on LCD
			Systick_Wait_ms(2000);// wait 2 seconds 
			LCD_Clear_Display();// clear LCD
		}
	}
	while(No_kilos<'1' || No_kilos>'9'); // wait until num of kilos is between 1 and 9

	LCD_Show("Weight is "); //display on LCD 
	LCD_Write(No_kilos); //writes char on LCD
	Systick_Wait_ms(500);//wait 0.5 second
		
	if (choice ==beef)// check if the choose is B  
	{
		no_kilos=Char_to_int(No_kilos); // convert char to int 
		TimeInMinutes_d=0.5*no_kilos ; // count time 
	}
	else if(choice == chicken)// check if the choose is C
	{
		no_kilos=Char_to_int(No_kilos);// convert char to int
		TimeInMinutes_d=0.2*no_kilos;// count time
	}
	minutes= (int)TimeInMinutes_d; // count the num of mins
	seconds= (TimeInMinutes_d-minutes) * 60;// count the num of seconds
	time[0]=IntToChar_Tens(minutes); // convert int to char to display it on LCD
	time[1]=IntToChar_Units(minutes);
	time[3]=IntToChar_Tens(seconds);
	time[4]=IntToChar_Units(seconds);
	LCD_Clear_Display(); //clear LCD
	LCD_Show(time);//display on LCD 
}



