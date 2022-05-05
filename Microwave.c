#include "Tiva.h"
#include "Switch.h"
#include "Buzzer.h"
#include "keypad.h"
#include "LCD.h"
#include "Timer.h"
#include "LED.h"
#include "Switch.h"
#include "defines.h"
#include <inttypes.h>
#include "Interrupt.h"

unsigned int CurrentTime;

void microwave_Init(void){
	System_Init();
	buzzer_Init();
	keypad_Init();
	LCD_Init();
	LED_Init();
	SW1_Init();
	SW2_Init();
	SW3_Init();
	interrupt_Init();
}
void start(unsigned int timer){
    NVIC_ST_RELOAD_R = timer;
    NVIC_ST_CTRL_R |= 0x05;
}
void pause(void){
    CurrentTime = NVIC_ST_CURRENT_R;
    NVIC_ST_CTRL_R &= ~(0x05);
    //Show Time
}
void resume(void){
    NVIC_ST_RELOAD_R = CurrentTime;
    NVIC_ST_CTRL_R |= 0x05;
}
void reset(void){
    NVIC_ST_CURRENT_R = 0x0;
    NVIC_ST_CTRL_R &= ~(0x05);
}