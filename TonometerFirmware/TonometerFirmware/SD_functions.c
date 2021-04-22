/*
 * SD_functions.c
 *
 * Created: 4/19/2021 7:54:51 AM
 *  Author: Home
 */ 

#include "SD_functions.h"

const char MOSI = 3;
const char MISO = 4;
const char SCK = 5;
const char SS = 2;

const unsigned char SD_CMD0[] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
const unsigned char SD_CMD1[] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x95};

void SPI_send_byte(unsigned char byte) {
	for (uint8_t i=0; i < 8; ++i) {
		if ((byte & 0x80) == 0x00)
		PORTB &= ~(1 << MOSI);
		else
		PORTB |= (1 << MOSI);
		
		byte <<= 1;
		PORTB |= (1 << SCK);
		asm("nop");
		PORTB &= ~(1 << SCK);
	}
}

unsigned char SPI_recieve_byte() {
	unsigned result = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		PORTB |= (1 << SCK);
		result <<= 1;
		if ( (PINB & (1 << MISO)) != 0x00)
		result |= 0x01;
		PORTB &= ~(1 << SCK);
		asm("nop");
	}
	return result;
}

unsigned char SD_send_cmd(const unsigned char *cmd) {
	for (uint8_t i = 0; i < 6; ++i) {
		SPI_send_byte(cmd[i]);
	}
	// ждём ответа
	unsigned int count = 0;
	unsigned char result;
	do {
		result = SPI_recieve_byte();
		++count;
	} while ((result & 0x80) != 0x00 && count < 0xFFFF );
	return result;
};

unsigned char SD_init() {
	unsigned char tmp;
	unsigned int count;
	for (uint8_t i = 0; i < 10; ++i)
	SPI_send_byte(0xFF);   // 80 импульсов
	PORTB &= ~(1 << SS);
	SD_send_cmd(SD_CMD0);
	count = 0;
	do {
		tmp = SD_send_cmd(SD_CMD1);
		SPI_send_byte(0xFF);
		++count;
	} while ( (tmp != 0x00) && count < 0xFFFF);
	
	if (count >= 0xFFFF) {
		return 2;
	}
	return 0;
}