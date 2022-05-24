#include "defines.h"
#include "Extern.h"
#include "stdbool.h"
#include <inttypes.h>


bool START = 0;
bool PAUSE = 0;
bool RESET = 0;
bool SW1_Press_Counts = 0;
bool valid_Input = 0;
bool z=0;

void System_Init(void){	
	
	
		SYSCTL_RCGCGPIO_R  |= 0x3F;  					//activating ports A B C D E F
		while ((SYSCTL_PRGPIO_R &0x3F)==0);
		
}
