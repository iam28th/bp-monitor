#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"

volatile uint8_t i = 0;
// $флаг для переключения входов АЦП$
volatile bool measure_cuff = true;

void PORTS_init() {
	DDRF &= ((1 << PF0) | (1 << PF1)); // $входы АЦП$

	PORTB|=(1<<SD_SS)|(1<<SD_MISO)|(1<<SD_MOSI); // $SD карта$
	DDRB|= ( (1<<SD_SS)|(1<<SD_MOSI)|(1<<SD_SCK) );
	DDRB |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_E);

	DDRA = 0xFF; // $LCD$
	PORTA = 1;
}

ISR(ADC_vect) {
    unsigned char result = 0;
    if (measure_cuff) {
        // $записать значение давления в манжете$
        ADC_select_osc();
        measure_cuff = false;
    } else {
        // $записать значение осцилляции$
        ADC_select_cuff();
        measure_cuff = true;
    }
   SPI_send_byte(ADCH) // $запись результата на карту$
}

int main(void)
{
    cli();
    PORTS_init();
    ADC_init();
    LCD_init();
    LCD_send_cmd(LCD_ON);
    sei();

    ADCSRA |= (1 << ADSC); // $начать преобразование$

    while (1) {}
}
