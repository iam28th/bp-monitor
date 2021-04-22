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
	ADMUX |= (1 << REFS0); // ����� ����������� ��������� �������� ����������
	ADMUX |= (1 << REFS1); // ��������� 2.56V
	ADMUX |= (1 << ADLAR); // ������������ �� ������ ����
	// ������� �������� ����� ADC0, ���������� �������� � �������:
	ADC_select_cuff();
	// ADMUX &= ~((1 << MUX1) | (1<<MUX2) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
	
	ADCSRA |= (1 << ADIE);  // ���������� ���������� �� ��������� ��������������
	ADCSRA |= (1 << ADFR);  // ����������� �����
	ADCSRA |= (1 << ADPS0);
	ADCSRA &= ~(1 << ADPS1);  // ������� ��� � 32 ���� ����
	ADCSRA |= (1 << ADPS2);   // �������� ������� ��
	ADCSRA |= (1 << ADEN);  // ��������� ���
}

void ADC_select_cuff() {
	ADMUX |= (1 << MUX1);
}

void ADC_select_osc() {
	ADMUX &= ~(1 << MUX1);
}
