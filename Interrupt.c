#include "defines.h"
#include <inttypes.h>

void interrupt_Init(void){
	
	GPIO_PORTF_IS_R  &= ~(1<<4)|~(1<<0);        /* make bit 4, 0 edge sensitive */
  GPIO_PORTF_IBE_R &= ~(1<<4)|~(1<<0);         /* trigger is controlled by IEV */
  GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);        /* falling edge trigger */
  GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);          /* clear any prior interrupt */
  GPIO_PORTF_IM_R  |= (1<<4)|(1<<0);          /* unmask interrupt */
	
	
  NVIC_EN0_R |= (1<<30);  /* enable PORTF interrupts */

}
