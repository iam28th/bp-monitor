/*
 * LCD_functions.c
 *
 * Created: 4/19/2021 8:39:12 AM
 *  Author: Home
 */ 

#include "LCD_functions.h"



const unsigned char LCD_RS = PB4;
const unsigned char LCD_RW = PB5;
const unsigned char LCD_E = PB6;

const unsigned char LCD_CLEAR = 0b00000001;
const unsigned char LCD_OFF = 0b00001000;
// ������� �������, ������ � ��� ������� ���������
const unsigned char LCD_ON = 0b00001100;
// ������ ������ - 8 ���; ����������� �����; 5�10 �����
const unsigned char LCD_FUNCTION_SET = 0b00111000; // 0b00111100;  // ?  
// �������� ������� �����-�������; ����� �� "��������"
const unsigned char LCD_ENTRY_MODE_SET = 0b00000110;
const unsigned char LCD_MOVE_CURSOR_RIGHT = 0b00010100;


void LCD_send_byte(unsigned char byte)  {
	PORTB |= (1 << LCD_E);	//������������� �� ������������ ������ LCD (E) �������
	PORTA = byte;		//������� ������ (�� ���� ������ ��������� �������� ����������, ������� � �������� ��������� ���������� �������)
	_delay_us(100);	// ��������� �������� ��� ����, ����� �� ���� ������������ ������ ����������
	PORTB &= ~(1 << LCD_E);	// ������������ ������� ������ ������������� �������
	_delay_ms(1);		// ����� ���� 100 ����������� ��� ������ ������ � LCD
}

void LCD_send_cmd(unsigned char cmd) {
	PORTB &= ~(1 << LCD_RS);   // RS == 0 => ������ �������
	LCD_send_byte(cmd);
}

void LCD_send_char(unsigned char byte) {
	PORTB |= (1 << LCD_RS);   // RS == 1 => ������ ������
	LCD_send_byte(byte);
}

void LCD_init() {
	unsigned char cmd = 0b00110000;
	LCD_send_cmd(cmd);
	_delay_ms(5);
	LCD_send_cmd(cmd);
	_delay_ms(100);
	LCD_send_cmd(cmd);
	
	LCD_send_cmd(LCD_FUNCTION_SET); 
	LCD_send_cmd(LCD_OFF); 
	LCD_send_cmd(LCD_CLEAR);	
	LCD_send_cmd(LCD_ENTRY_MODE_SET);	
	_delay_ms(10);
	LCD_send_cmd(LCD_ON); 
}

void LCD_send_string(char *string) {
	for (uint8_t i = 0; string[i] != '\0'; ++i) {
		LCD_send_char(string[i]);
	}
}

void LCD_place_cursor(unsigned char a, unsigned char b) {
	unsigned char cmd = b + (a == 1 ? 0b10000000 : 0b11000000);
	LCD_send_cmd(cmd);
}