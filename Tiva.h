#ifndef Tiva_H_
#define Tiva_H_

#include "stdbool.h"

#define popcorn 'A'
#define beef 'B'
#define chicken 'C'
#define cookTime 'D'


void System_Init(void);

extern bool START;
extern bool PAUSE;
extern bool RESET; 
extern bool SW1_Press_Counts;
extern bool Cook_Time_f;
extern bool Cook_Time_Again;
extern bool Start_Cook_Time;


#endif


