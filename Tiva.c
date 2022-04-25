#include "defines.h"
#include <inttypes.h>

void System_Init(void){	
	
		SYSCTL_RCGCGPIO_R  |= 0x51;  					//activating ports A B C F
		while ((SYSCTL_PRGPIO_R &0x51)==0);
}
