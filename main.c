#include "Tiva.h"
#include "Switch.h"
#include "LED.h"

unsigned char SW3=1;

int main(void){
	
	System_Init();
	LED_Init();
	SW3_Init();
	
	while(1){
		
		SW3 = SW3_Input();
		
		if(SW3 == 0){
			
			BlueOn();
			
		}
		else RedOn();
		
	}
}
