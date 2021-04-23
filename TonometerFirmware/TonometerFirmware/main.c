/*
 * TonometerFirmware.c
 *
 * Created: 4/18/2021 7:46:03 PM
 * Author : Home
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"

// #define F_CPU 1000000

volatile uint8_t i = 0;
volatile bool measure_cuff = true;

void PORTS_init() {
	DDRF &= ((1 << PF0) | (1 << PF1));  // входы ј÷ѕ
	
	PORTB|=(1<<SD_SS)|(1<<SD_MISO)|(1<<SD_MOSI);
	DDRB|= ( (1<<SD_SS)|(1<<SD_MOSI)|(1<<SD_SCK) );
	DDRB |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_E);
	
	// PORTB = 0;
	// DDRB |= ((1 << MOSI) | (1 << MISO) | (1 << SCK) | (1 << SS));
	DDRA = 0xFF;  // LCD
	PORTA = 1;
	DDRD = 1;  // test measure cuff
}

ISR(ADC_vect) {
	// PORTD = ~PORTD;
	if (measure_cuff) {
		// записать значение давлени€ в манжете
		// PORTC = 0xFF; 
		PORTD = ~PORTD;
		PORTC = 0xFF;
		ADC_select_osc();
		measure_cuff = false;
		} else {
		// записать значение осцилл€ции
		ADC_select_cuff();
		// PORTB = ~PORTB;
		PORTC = 0x00;
		measure_cuff = true;
		// PORTC = 0x00;
	}
	// SPI_send_byte(PORTB);
	// measure_cuff = ~measure_cuff;
}

int main(void)
{
	cli();
	PORTS_init();
	ADC_init();

	sei();
	
	// 
	cli();
	LCD_init();
	LCD_send_cmd(LCD_ON);
	char buffer[512]="Read operation";
	
	char str[10];
	
	unsigned char result = SD_init();
	LCD_place_cursor(1, 1);
	sprintf(str,"%d",result);
	LCD_send_string(str);
	
	
	result=SD_write_block(buffer,0x00,0x00,0x04,0x00);
	sprintf(str,"%d",result);
	LCD_place_cursor(0, 1);
	LCD_send_string(str);
	
	char buffer2[512];
	SD_read_block(buffer2, 0x00, 0x00, 0x04, 0x00);
	LCD_place_cursor(0, 1);
	LCD_send_string(buffer2);
	
	sei();
	
	ADCSRA |= (1 << ADSC); // начать преобразование
	
	while (1) {
	}
}
