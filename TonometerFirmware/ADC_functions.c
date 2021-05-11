/*
 * ADC_functions.c
 *
 * Created: 4/19/2021 7:51:26 AM
 *  Author: Home
 */ 
#include "ADC_functions.h"


void ADC_init ()
{
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // выбор внутреннего источника опорного напряжения
	ADMUX |= (1 << REFS1); // номиналом 2.56V
	ADMUX |= (1 << ADLAR); // выравнивание по левому краю
	// сначала выбираем канал ADC0, измеряющий давление в манжете:
	ADC_select_cuff();
	// ADMUX &= ~((1 << MUX1) | (1<<MUX2) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
	
	ADCSRA |= (1 << ADIE);  // разрешение прерывания по окончанию преобразования
	ADCSRA |= (1 << ADFR);  // непрерывный режим
	ADCSRA |= (1 << ADPS0);
	ADCSRA &= ~(1 << ADPS1);  // частота АЦП в 32 раза ниже
	ADCSRA |= (1 << ADPS2);   // тактовой частоты МК
	ADCSRA |= (1 << ADEN);  // включение АЦП
}

void ADC_select_cuff() {
	ADMUX |= (1 << MUX1);
}

void ADC_select_osc() {
	ADMUX &= ~(1 << MUX1);
}
