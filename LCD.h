#ifndef LCD_H_
#define LCD_H_

void delay_1ms(void);
void LCD_CMD(unsigned char signal);
void LCD_Clear_Display(void);
void LCD_Init(void);
void SetCursorToRight(void);
void ShiftDisplayLeft(void);
void LCD_Write(unsigned char Data);
void LCD_String(char *str);
void LCD_Array(char arr[]);




#endif
