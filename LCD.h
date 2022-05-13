#ifndef LCD_H_
#define LCD_H_


void LCD_CMD(unsigned char signal);
void LCD_Clear_Display(void);
void LCD_Init(void);
void LCD_Write(unsigned char Data);
void LCD_Show(char *str);




#endif
