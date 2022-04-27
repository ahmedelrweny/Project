#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#define RS 0x04 //Bit 2 in Port A
#define RW 0x02 //Bit 1 in Port A
#define EN 0x01 //Bit 0 in Port A

void LCD_Init(){

    System_Init(); // Port A - B
    //Enable PortA bits 0-2 for Rs Rw Enable
    	GPIO_PORTA_CR_R |= 0x07;
		GPIO_PORTA_AMSEL_R &= ~0x07;
		GPIO_PORTA_PCTL_R &= ~0x0000FFF;
		GPIO_PORTA_AFSEL_R &= ~0x07;
		GPIO_PORTA_DIR_R |= 0x07;						
		GPIO_PORTA_DEN_R |= 0x07;	
	//Enable port B bits 0-7 for
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;
		GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		GPIO_PORTB_AFSEL_R &= ~0xFF;
		GPIO_PORTB_DIR_R |= 0xFF;						
		GPIO_PORTB_DEN_R |= 0xFF;	

		LCD_CMD(0x38); // Enable 8 bit mode
		LCD_CMD(0x0F); // Turn on Display
		LCD_Clear_Display();
		LCD_CMD(0x06); //Increment from left to right
}
//LCD Control
void LCD_CMD(unsigned char signal){
		GPIO_PORTA_DATA_R = 0x00; //Set RS,RW to 0 to Enable write
		GPIO_PORTB_DATA_R = signal; //Set Data of PortB
		GPIO_PORTA_DATA_R |= EN; //Enable write data
		SysTick_Wait(80);//waits 1 micro sec
		GPIO_PORTA_DATA_R = 0x00; //To Disable changes for LCD
		/*Commands of code 0000 --> 0111 Requires 2ms to be sure they are executed
		Commands above that Requires 40 microsec to be sure they are executed*/
		if(signal < 4) SysTick_Wait(160000); // 2ms
		else SysTick_Wait(3200); // 40 micro sec
}
void LCD_Clear_Display(){
	LCD_CMD(0x01);//Remove Chars
	LCD_CMD(0x02);//Return cursor to zero position
}
void SetCursorToRight(){
	LCD_CMD(0x80);
	for (int i = 0; i < 16; i++)
	{
		LCD_CMD(0x14);
	}
}
void ShiftDisplayLeft(){
	LCD_CMD(0x07);//used to Handle Time Entry Required in Project from Right To Left
}	