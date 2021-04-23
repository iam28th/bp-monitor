/*
 * SD_functions.c
 *
 * Created: 4/19/2021 7:54:51 AM
 *  Author: Home
 */ 

#include "SD_functions.h"

const char SD_MOSI = 2;
const char SD_MISO = 3;
const char SD_SCK = 1;
const char SD_SS = 0;

const unsigned char SD_CMD0[] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
const unsigned char SD_CMD1[] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x95};

void SPI_send_byte(unsigned char byte) {
	for (uint8_t i=0; i < 8; ++i) {
		if ((byte & 0x80) == 0x00) { 
			PORTB &= ~(1 << SD_MOSI);
		} else {
			PORTB |= (1 << SD_MOSI);
		}
		byte <<= 1;
		PORTB |= (1 << SD_SCK);
		asm("nop");
		PORTB &= ~(1 << SD_SCK);
	}
}

unsigned char SPI_recieve_byte() {
	unsigned result = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		PORTB |= (1 << SD_SCK);
		result <<= 1;
		if ( (PINB & (1 << SD_MISO)) != 0x00)
		result |= 0x01;
		PORTB &= ~(1 << SD_SCK);
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
	if (count == 0xFFFF) return 29;
	return result;
};

unsigned char SD_init() {
	unsigned char tmp;
	unsigned int count;
	for (uint8_t i = 0; i < 10; ++i) {
		SPI_send_byte(0xFF); 
	}  // 80 импульсов - переключение карты на работу по SPI
	
	PORTB &= ~(1 << SD_SS);
	tmp = SD_send_cmd(SD_CMD0);
	if (tmp != 1) return 1;
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

unsigned char SD_write_block(char *bf, 
	unsigned char ad1, unsigned char ad2,
	unsigned char ad3, unsigned char ad4) {
	
	unsigned char cmd[6] = {0};
	cmd[0] = 0x58;
	cmd[1] = ad1; cmd[2] = ad2; cmd[3] = ad3; cmd[4] = ad4;
	cmd[5] = 0x95;
	
	unsigned char result = SD_send_cmd(cmd);
	if (result != 0x00) return 1;
	SPI_send_byte(0xFF);
	
	SPI_send_byte(0xFE);
	for (int i = 0; i < 512; ++i) {
		SPI_send_byte(bf[i]);
	}
	SPI_send_byte(0xFF);  // control sum
	SPI_send_byte(0xFF);
	unsigned char result2 = SPI_recieve_byte();
	if ( (result2 & 0x05) != 0x05) return result2;
	
	long int count = 0;
	do {
		result = SPI_recieve_byte();
		++count;
	} while ( (result != 0xFF) && (count < 0xFFFF) );
	if (count == 0xFFFF) return 3;
	return 0;
}

unsigned char SD_read_block(char * bf, unsigned char ad1, 
	unsigned char ad2, unsigned char ad3, unsigned char ad4) {
	
	unsigned char cmd[6] = {0};
	cmd[0] = 0x51;
	cmd[1] = ad1; cmd[2] = ad2; cmd[3] = ad3; cmd[4] = ad4;
	cmd[5] = 0x95;
	
	unsigned char result = SD_send_cmd(cmd);
	if (result != 0x00) return 1;
	SPI_send_byte(0xFF);
	
	long int count = 0;
	do {
		result = SPI_recieve_byte();
		++count;
	} while ( (result != 0xFE) && (count < 0xFFFF));
	
	if (count == 0xFFFF) return 2;
	
	for (int i = 0; i < 512; ++i) {
		bf[i] = SPI_recieve_byte();
	}
	SPI_recieve_byte();
	SPI_recieve_byte();
	return 0;
}
