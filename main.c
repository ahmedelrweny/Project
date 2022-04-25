#include "Tiva.h"
#include "Switch.h"
#include "LED.h"


unsigned char SW1;
unsigned char SW2;
unsigned char SW3;
int main(void){
	
	System_Init();
	LED_Init();
	
	SW1_Init();
	SW2_Init();
	SW3_Init();
	
	while(1){
		
		//SW1 = SW1_Input();
		//SW2 = SW2_Input();	
		SW3 = SW3_Input();
		
		if(SW3 != 0x01){
			BlueOn();
		}
	}
		
}
