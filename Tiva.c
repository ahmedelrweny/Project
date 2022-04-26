#include "defines.h"
#include <inttypes.h>

void System_Init(void){	
	
		SYSCTL_RCGCGPIO_R  |= 0x33;  					//activating ports A B E F
		while ((SYSCTL_PRGPIO_R &0x33)==0);

}
