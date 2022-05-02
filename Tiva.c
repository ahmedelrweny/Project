#include "defines.h"
#include <inttypes.h>

void System_Init(void){	
		SYSCTL_RCGCGPIO_R  |= 0x3F;  					//activating ports A B C D E F
		while ((SYSCTL_PRGPIO_R &0x3F)==0);
}
