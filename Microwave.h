#ifndef Microwave_H_
#define Microwave_H_

void microwave_Init(void);
void cook_Popcorn(void);
void cook_Beef_or_Chicken(char choose);
char IntToChar_Tens(int x);
char IntToChar_Units(int x);
int Char_to_int(char x);
void Cook_Time(void);
void Time_Display(char time[]);
void start(void);
void pause(void);
void reset(void);


#endif

