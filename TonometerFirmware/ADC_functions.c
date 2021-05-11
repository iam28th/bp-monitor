#include "ADC_functions.h"


void ADC_init ()
{
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // выбор внутреннего источника опорного напряжения
	ADMUX |= (1 << REFS1);
	ADMUX |= (1 << ADLAR); // выравнивание результата по левому краю
    // в начальный момент времени считывается давление в манжете
	ADC_select_cuff();

	ADCSRA |= (1 << ADIE);  // разрешение прерываний по окончании преобразования
	ADCSRA |= (1 << ADFR);  // непрерывный режим работы
	ADCSRA |= (1 << ADPS0); // частота АЦП в 32 раза меньше тактовой частоты МК
	ADCSRA &= ~(1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
	ADCSRA |= (1 << ADEN);  // включение АЦП
}

void ADC_select_cuff() {
	ADMUX |= (1 << MUX1); // считывание с порта ADC1
}

void ADC_select_osc() {
	ADMUX &= ~(1 << MUX1);  // считывание с порта  ADC0
}

