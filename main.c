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

char input;

int main(void){
	microwave_Init();
	while(1){
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