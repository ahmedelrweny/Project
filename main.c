#include "Tiva.h"
#include "Switch.h"
#include "Buzzer.h"
#include "keypad.h"
#include "LCD.h"


int main(void){
	System_Init();
	LCD_Init();
	keypad_Init();
	
	while(1){
		LCD_String("Hello");
		/*switch(input){
		case 1:
			cook_Popcorn();
			break;
		case 2:
			cook_Chiken();
			break;
		case 3:
			cook_Beef();
			break;
		case 4:
			cook_Time();
			break;
		default:
			LCD_Show("Please enter a choice");
			break;
		}*/
	}	
}
