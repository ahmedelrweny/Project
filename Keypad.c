#include "defines.h"
#include <inttypes.h>
void keypad_Init(){
	SYSCTL_RCGCGPIO_R |= 0x14;            //Enable clock to PORTC and PORTE  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be setted
  GPIO_PORTC_CR_R |= 0xF0;              //Allow settings for all pins of PORTC
  GPIO_PORTE_CR_R  |= 0x1E;             //Allow settings for all pins of PORTD
  GPIO_PORTE_DIR_R &=~(0x1E);           //PE1-PE4 are used with row and set them as digital input pins
	GPIO_PORTC_DIR_R |= 0xF0;            	//PC4-PC7 are used with coulum and set them as digital output pins
	GPIO_PORTC_AMSEL_R&=~(0xF0);          //Disable the analog function for port C
	GPIO_PORTE_AMSEL_R&=~(0x1E);          //Disable the analog function for port E
	GPIO_PORTC_AFSEL_R&=~(0xF0);          //Disable alternate function for port C
	GPIO_PORTE_AFSEL_R&=~(0x1E);          //Disable alternate function for port E
	GPIO_PORTC_PCTL_R&=~(0x11110000);     //using pins as GPIO
	GPIO_PORTE_PCTL_R&=~(0x00011110);     //using pins as GPIO
  GPIO_PORTE_PDR_R |= 0x1E;             //Enable pull down resistor on PORTE
  GPIO_PORTC_DEN_R |= 0xF0;             //Set PORTC as digital pins
  GPIO_PORTE_DEN_R |= 0x1E;             //Set PORTE as digital pins
	GPIO_PORTE_DATA_R|=0x1E;              //Intializaion of Port E
}
