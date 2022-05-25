#include "defines.h"
#include <inttypes.h>
#include "Tiva.h"
#include "LED.h"


static char symbol[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
void keypad_Init(){
  GPIO_PORTC_CR_R |= 0xF0;                //Allow settings for all pins of PORTC
  GPIO_PORTE_CR_R  |= 0x1E;               //Allow settings for all pins of PORTE
  GPIO_PORTE_DIR_R &=~(0x1E);             //PE1-PE4 are used with row and set them as digital input pins
	GPIO_PORTC_DIR_R |= 0xF0;              	//PC4-PC7 are used with coulum and set them as digital output pins
	GPIO_PORTC_AMSEL_R&=~(0xF0);            //Disable the analog function for PORTC
	GPIO_PORTE_AMSEL_R&=~(0x1E);            //Disable the analog function for PORTE
	GPIO_PORTC_AFSEL_R&=~(0xF0);            //Disable alternate function for PORTC
	GPIO_PORTE_AFSEL_R&=~(0x1E);            //Disable alternate function for PORTE
	GPIO_PORTC_PCTL_R&=~(0xFFFF0000);       //using pins as GPIO
	GPIO_PORTE_PCTL_R&=~(0x000FFFF0);       //using pins as GPIO
  GPIO_PORTE_PDR_R |= 0x1E;               //Enable pull down resistor on PORTE
  GPIO_PORTC_DEN_R |= 0xF0;               //Set PORTC as digital pins
  GPIO_PORTE_DEN_R |= 0x1E;               //Set PORTE as digital pins
	GPIO_PORTE_DATA_R&=~0x1E;               //Intializaion of PORTE
}
char KeyScan(){
	while(1){
	int i;
	int j;
	if(Cook_Time_Again || Start_Cook_Time){ // check if sw1 or sw2 pressed when get in cook_Time function
		return '\0';
	}
	for (i=0;i<4;i++){ // set colums 
	GPIO_PORTC_DATA_R=(0x10<<i);
	for(j=0;j<4;j++){ // set rows
		if((GPIO_PORTE_DATA_R&0x1E)&(0x02<<j)){
			return symbol[j][i];
		
	}}}
}}
