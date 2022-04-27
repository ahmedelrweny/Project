#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"

void LCD_Init(){

    System_Init(); // Port A - B
    //Enable PortA bits 0-2 for EN Rw RS
    GPIO_PORTA_CR_R |= 0x07;
		GPIO_PORTA_AMSEL_R &= ~0x07;
		GPIO_PORTA_PCTL_R &= ~0x0000FFF;
		GPIO_PORTA_AFSEL_R &= ~0x07;
		GPIO_PORTA_DIR_R |= 0x07;						
		GPIO_PORTA_DEN_R |= 0x07;	
		//Enable port B bits 0-7 for LCD Data
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;
		GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		GPIO_PORTB_AFSEL_R &= ~0xFF;
		GPIO_PORTB_DIR_R |= 0xFF;						
		GPIO_PORTB_DEN_R |= 0xFF;	
}
//LCD_Write a function that writes character on LCD
void LCD_Write(unsigned char Data)
{
	GPIO_PORTA_DATA_R = 0x04; //which means RS=1, RW=0, EN=0 to control that the entered is data not command
	GPIO_PORTB_DATA_R = Data; //LCD has the data entered on port B 
	GPIO_PORTA_DATA_R |= 0x01; //which means RS=1, RW=0, EN=1 to secure data entered 
	GPIO_PORTA_DATA_R = 0x00; //which means RS=0, RW=0, EN=0 to stop changing data on LCD after writing the desired data
	SysTick_Wait(80); // 1 us
}

//LCD_String function to write the whole string on LCD
void LCD_String(unsigned char *str)   // write a string on LCD 
{
  int l = strlen(str);         // l = string length
  int i=0;                    //itterator
  while(i<l)
		{
			LCD_Write(str[i]);            // call the function LCD_Write 
			i++;
    }
}
