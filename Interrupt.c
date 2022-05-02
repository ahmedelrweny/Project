#include "defines.h"
#include <inttypes.h>

void interrupt_Init(void){
	NVIC_EN0_R |= (1<<30); /*Enable PORTF Interrupt IRQ30 */
	GPIO_PORTF_IM_R |= (1<<4)|(1<<0);
	GPIO_PORTF_IS_R  &= ~(1<<4)|~(1<<0); /* make bit 4, 0 edge sensitive */
	GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);  /*PF0, PF4 falling edge trigger */

}
