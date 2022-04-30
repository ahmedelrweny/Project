#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#include <string.h>
#define RS 0x10 //Pin 4 in Port A
#define RW 0x08 //Pin 3 in Port A
#define EN 0x04 //Pin 2 in Port A

//LCD Control
void LCD_CMD(unsigned char signal){
		GPIO_PORTA_DATA_R = 0x00; //Set RS,RW to 0 to Enable write
		GPIO_PORTA_DATA_R |= 0x04; //Enable write data
	  GPIO_PORTB_DATA_R = signal; //Set Data of PortB
		SysTick_Wait(80);        //waits 1 micro sec
		/*Commands of code 0000 --> 0111 Requires 2ms to be sure they are executed
		Commands above that Requires 40 microsec to be sure they are executed*/
		if(signal < 4) SysTick_Wait(160000); // 2ms
		else SysTick_Wait(3200); // 40 micro sec
}

void LCD_Clear_Display(void){
	LCD_CMD(0x01);             //Remove Chars
	LCD_CMD(0x02);             //Return cursor to zero position
}

void LCD_Init(void){

    //Enable PortA bits 2-4 for Rs Rw Enable
    GPIO_PORTA_CR_R |= 0x1C;
		GPIO_PORTA_AMSEL_R &= ~0x1C;
		GPIO_PORTA_PCTL_R &= ~0x000FFF00;
		GPIO_PORTA_AFSEL_R &= ~0x1C;
		GPIO_PORTA_DIR_R |= 0x1C;						
		GPIO_PORTA_DEN_R |= 0x1C;	
		//Enable port B bits 0-7 for
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;
		GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		GPIO_PORTB_AFSEL_R &= ~0xFF;
		GPIO_PORTB_DIR_R |= 0xFF;						
		GPIO_PORTB_DEN_R |= 0xFF;	

		LCD_CMD(0x38);           // Enable 8 bit mode
		LCD_CMD(0x0F);           // Turn on Display
		LCD_Clear_Display();
}

void SetCursorToRight(void){
	int i;
	LCD_CMD(0x80);
	for (i = 0; i < 16; i++)
	{
		LCD_CMD(0x14);
	}
}

void ShiftDisplayLeft(void){
	LCD_CMD(0x07);             //used to Handle Time Entry Required in Project from Right To Left
}

//LCD_Write a function that writes character on LCD
void LCD_Write(unsigned char Data){
	GPIO_PORTA_DATA_R = 0x10;  //which means RS=1, RW=0, EN=0 to control that the entered is data not command
	GPIO_PORTA_DATA_R |= 0x04; //which means RS=1, RW=0, EN=1 to secure data entered	
	GPIO_PORTB_DATA_R = Data;  //LCD has the data entered on port B 
	LCD_CMD(0x06);             //Increment from left to right
	SysTick_Wait(80);          // 1 us
}

//LCD_String function to write the whole string on LCD
void LCD_String(char *str){   // write a string on LCD
  int l=strlen(str);          // l = string length
  int i=0;                    //itterator
  while(i<l){
		LCD_Write(str[i]);        // call the function LCD_Write 
		i++;
    }
}
