
#ifndef LCD_FUNCTIONS_H_
#define LCD_FUNCTIONS_H_

#define F_CPU 1000000
#include <util/delay.h>

#include <avr/io.h>

const unsigned char RS, RW, E;

const unsigned char LCD_CLEAR, LCD_ON, LCD_OFF, LCD_FUNCTION_SET, 
LCD_ENTRY_MODE_SET, LCD_MOVE_CURSOR_RIGHT;

void LCD_send_byte(unsigned char byte);
void LCD_send_cmd(unsigned char cmd);
void LCD_send_char(unsigned char cmd);
void LCD_init();
void LCD_send_string(char *string);
void LCD_move_cursor_right();
void LCD_place_cursor(unsigned char a, unsigned char b); 

#endif /* LCD_FUNCTIONS_H_ */