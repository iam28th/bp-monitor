/*
 * TonometerFirmware.c
 *
 * Created: 4/18/2021 7:46:03 PM
 * Author : Home
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "main.h"

// #define F_CPU 1000000

volatile uint8_t i = 0;
volatile bool measure_cuff = true;

void PORTS_init() {
	DDRF &= ((1 << PF0) | (1 << PF1));  // входы АЦП
	DDRB = 0xFF;
	PORTB = 0;
	// DDRB |= ((1 << MOSI) | (1 << MISO) | (1 << SCK) | (1 << SS));
	DDRA = 1;  // LCD
	PORTA = 1;
	DDRD = 1;  // test measure cuff
}

ISR(ADC_vect) {
	// PORTD = ~PORTD;
	if (measure_cuff) {
		// записать значение давления в манжете
		// PORTC = 0xFF; 
		PORTD = ~PORTD;
		PORTC = 0xFF;
		ADC_select_osc();
		measure_cuff = false;
		} else {
		// записать значение осцилляции
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

	ADCSRA |= (1 << ADSC); // начать преобразование
	LCD_init();
	LCD_send_cmd(LCD_ON);
	LCD_place_cursor(1, 0);
	// LCD_send_string("БПАН");
	unsigned char result = SD_init();
	char str[10];
	sprintf(str, "%d", result);
	LCD_send_string(str);
	
	int i = 0;
	while (1) {
	}
}
